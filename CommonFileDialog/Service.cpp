#define _CRT_SECURE_NO_WARNINGS

#include "Service.h"
#include "OpenDialog.h"
#include "SaveDialog.h"
#include <stdlib.h>
#include <new>

// Constructor and Destructor

CStationService::CStationService(void)
	: m_cRef( 0 )
{

}

CStationService::~CStationService(void)
{

}

// IUnknown Members

STDMETHODIMP CStationService::QueryInterface(REFIID riid, void **ppv)
{
    HRESULT hr = S_OK;
    if (ppv)
    {
        *ppv = NULL;

        if (IsEqualIID( riid, IID_IDispatch ) || IsEqualIID( riid, IID_IUnknown ))
            *ppv = (IDispatch *) (this);
        else
            hr = E_NOINTERFACE;

        if (*ppv)
            AddRef();
    }
    else
        hr = E_INVALIDARG;

    return hr;
}

STDMETHODIMP_(ULONG) CStationService::AddRef(void)
{
    return((ULONG) (InterlockedIncrement((long *) &m_cRef)));
}

STDMETHODIMP_(ULONG) CStationService::Release(void)
{
    ULONG cRef = (ULONG) (InterlockedDecrement((long *) &m_cRef));
    if (!cRef)
        delete this;

    return cRef;
}

// IDispatch Members

STDMETHODIMP CStationService::GetTypeInfoCount(UINT FAR* pctInfo)
{
    if (!pctInfo)
        return E_INVALIDARG;

    *pctInfo = 0;
    return S_OK;
}

STDMETHODIMP CStationService::GetTypeInfo(UINT iTInfo, LCID lcid, ITypeInfo FAR* FAR* ppTInfo)
{
    return E_NOTIMPL;
}

STDMETHODIMP CStationService::GetIDsOfNames(REFIID riid, OLECHAR FAR* FAR* rgszNames, UINT cNames, LCID lcid, DISPID FAR* rgDispId)
{
    HRESULT hr = S_OK;

    for (UINT i = 0; i < cNames; i++)
    {
        if (!_wcsicmp( rgszNames[i], L"ScriptRoot" ))
			rgDispId[i] = DISPID_STATION_ScriptRoot;
        else if (!_wcsicmp( rgszNames[i], L"NewFileOpenDialog" ))
			rgDispId[i] = DISPID_STATION_NewFileOpenDialog;
        else if (!_wcsicmp( rgszNames[i], L"NewFileSaveDialog" ))
			rgDispId[i] = DISPID_STATION_NewFileSaveDialog;
        else if (!_wcsicmp( rgszNames[i], L"ConsoleWindow" ))
			rgDispId[i] = DISPID_STATION_ConsoleWindow;
        else
        {
            rgDispId[i] = DISPID_UNKNOWN;
            hr = DISP_E_UNKNOWNNAME;
        }
    }

    return hr;
}

STDMETHODIMP CStationService::Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS FAR* pDispParams, VARIANT FAR* pVarResult, EXCEPINFO FAR* pExcepInfo, UINT FAR* puArgErr)
{
	try
	{
		if (!pDispParams)
			_com_issue_error( E_INVALIDARG );

		if (!IsEqualIID( riid, IID_NULL ))
			_com_issue_error( DISP_E_UNKNOWNINTERFACE );

		HRESULT hr = S_OK;
		_variant_t varTempResult;

		switch (dispIdMember)
		{
		case DISPID_STATION_ConsoleWindow :
			{
				if (!(wFlags & DISPATCH_PROPERTYGET))
					_com_issue_error( DISP_E_MEMBERNOTFOUND );

				if (pDispParams->cArgs != 0)
					_com_issue_error( DISP_E_BADPARAMCOUNT );

				varTempResult = ConsoleWindow();
				
				break;
			}
		case DISPID_STATION_NewFileOpenDialog :
			{
				if (!(wFlags & DISPATCH_METHOD))
					_com_issue_error( DISP_E_MEMBERNOTFOUND );

				if (pDispParams->cArgs != 0)
					_com_issue_error( DISP_E_BADPARAMCOUNT );

				varTempResult = NewFileOpenDialog();

				break;
			}
		case DISPID_STATION_NewFileSaveDialog :
			{
				if (!(wFlags & DISPATCH_METHOD))
					_com_issue_error( DISP_E_MEMBERNOTFOUND );

				if (pDispParams->cArgs != 0)
					_com_issue_error( DISP_E_BADPARAMCOUNT );

				varTempResult = NewFileSaveDialog();

				break;
			}
		case DISPID_STATION_ScriptRoot :
			{
				if (!(wFlags & DISPATCH_PROPERTYPUTREF))
					_com_issue_error( DISP_E_MEMBERNOTFOUND );

				if (pDispParams->cArgs != 1)
					_com_issue_error( DISP_E_BADPARAMCOUNT );

				_variant_t varWhat( pDispParams->rgvarg );
				ScriptRoot( varWhat );

				break;
			}
		default:
			{
				_com_issue_error( DISP_E_MEMBERNOTFOUND );
				break;
			}
		}

		if (pVarResult)
		{
			hr = VariantCopy( pVarResult, &varTempResult );
			if (FAILED(hr))
				_com_issue_error( hr );
		}
	}
	catch (_com_error &ce)
	{
		return ce.Error();
	}
	catch (std::bad_alloc &)
	{
		return E_OUTOFMEMORY;
	}

	return S_OK;
}

// StationService Members

LONG_PTR STDMETHODCALLTYPE CStationService::ConsoleWindow(void)
{
	return (LONG_PTR) GetConsoleWindow() ;
}

void CStationService::SetScriptVariable(LPCSTR lpszName, _variant_t varValue)
{
	DISPID diVariable = DISPID_UNKNOWN;
	_bstr_t bsVariable = lpszName;
	HRESULT hr = m_pScript->GetDispID( bsVariable.GetBSTR(), fdexNameEnsure, &diVariable );
	if (FAILED(hr))
		_com_issue_error( hr );

	DISPID diNamed = DISPID_PROPERTYPUT;
	DISPPARAMS dp = { &varValue, &diNamed, 1, 1 };
	hr = m_pScript->InvokeEx( diVariable, LOCALE_USER_DEFAULT, DISPATCH_PROPERTYPUT, &dp, NULL, NULL, NULL );
	if (FAILED(hr))
		_com_issue_error( hr );
}

void STDMETHODCALLTYPE CStationService::ScriptRoot(IDispatchExPtr pWhat)
{
	m_pScript = pWhat;

	SetScriptVariable( "FOS_OVERWRITEPROMPT", FOS_OVERWRITEPROMPT );
	SetScriptVariable( "FOS_STRICTFILETYPES", FOS_STRICTFILETYPES );
	SetScriptVariable( "FOS_NOCHANGEDIR", FOS_NOCHANGEDIR );
	SetScriptVariable( "FOS_PICKFOLDERS", FOS_PICKFOLDERS );
	SetScriptVariable( "FOS_FORCEFILESYSTEM", FOS_FORCEFILESYSTEM );
	SetScriptVariable( "FOS_ALLNONSTORAGEITEMS", FOS_ALLNONSTORAGEITEMS );
	SetScriptVariable( "FOS_NOVALIDATE", FOS_NOVALIDATE );
	SetScriptVariable( "FOS_ALLOWMULTISELECT", FOS_ALLOWMULTISELECT );
	SetScriptVariable( "FOS_PATHMUSTEXIST", FOS_PATHMUSTEXIST );
	SetScriptVariable( "FOS_FILEMUSTEXIST", FOS_FILEMUSTEXIST );
	SetScriptVariable( "FOS_CREATEPROMPT", FOS_CREATEPROMPT );
	SetScriptVariable( "FOS_SHAREAWARE", FOS_SHAREAWARE );
	SetScriptVariable( "FOS_NOREADONLYRETURN", FOS_NOREADONLYRETURN );
	SetScriptVariable( "FOS_NOTESTFILECREATE", FOS_NOTESTFILECREATE );
	SetScriptVariable( "FOS_HIDEMRUPLACES", FOS_HIDEMRUPLACES );
	SetScriptVariable( "FOS_HIDEPINNEDPLACES", FOS_HIDEPINNEDPLACES );
	SetScriptVariable( "FOS_NODEREFERENCELINKS", FOS_NODEREFERENCELINKS );
	SetScriptVariable( "FOS_DONTADDTORECENT", FOS_DONTADDTORECENT );
	SetScriptVariable( "FOS_FORCESHOWHIDDEN", FOS_FORCESHOWHIDDEN );
	SetScriptVariable( "FOS_DEFAULTNOMINIMODE", FOS_DEFAULTNOMINIMODE );
	SetScriptVariable( "FOS_FORCEPREVIEWPANEON", FOS_FORCEPREVIEWPANEON );

	SetScriptVariable( "FDAP_BOTTOM", FDAP_BOTTOM );
	SetScriptVariable( "FDAP_TOP", FDAP_TOP );

	SetScriptVariable( "FDEOR_DEFAULT", FDEOR_DEFAULT );
	SetScriptVariable( "FDEOR_ACCEPT", FDEOR_ACCEPT );
	SetScriptVariable( "FDEOR_REFUSE", FDEOR_REFUSE );

	SetScriptVariable( "FDESVR_DEFAULT", FDESVR_DEFAULT );
	SetScriptVariable( "FDESVR_ACCEPT", FDESVR_ACCEPT );
	SetScriptVariable( "FDESVR_REFUSE", FDESVR_REFUSE );
}

LPDISPATCH STDMETHODCALLTYPE CStationService::NewFileOpenDialog(void)
{
	return new CFileOpenDialogWrap( m_pScript );
}

LPDISPATCH STDMETHODCALLTYPE CStationService::NewFileSaveDialog(void)
{
	return new CFileSaveDialogWrap( m_pScript );
}