#define _CRT_SECURE_NO_WARNINGS

#include "SaveDialog.h"
#include "DialogEvents.h"
#include <stdlib.h>
#include <new>
#include <vector>

// Constructor and Destructor

CFileSaveDialogWrap::CFileSaveDialogWrap(IDispatchExPtr pScript)
	: m_cRef( 0 ), m_pScript( pScript ), m_pCore( CLSID_FileSaveDialog )
{

}

CFileSaveDialogWrap::~CFileSaveDialogWrap(void)
{

}

// IUnknown Members

STDMETHODIMP CFileSaveDialogWrap::QueryInterface(REFIID riid, void **ppv)
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

STDMETHODIMP_(ULONG) CFileSaveDialogWrap::AddRef(void)
{
    return((ULONG) (InterlockedIncrement((long *) &m_cRef)));
}

STDMETHODIMP_(ULONG) CFileSaveDialogWrap::Release(void)
{
    ULONG cRef = (ULONG) (InterlockedDecrement((long *) &m_cRef));
    if (!cRef)
        delete this;

    return cRef;
}

// IDispatch Members

STDMETHODIMP CFileSaveDialogWrap::GetTypeInfoCount(UINT FAR* pctInfo)
{
    if (!pctInfo)
        return E_INVALIDARG;

    *pctInfo = 0;
    return S_OK;
}

STDMETHODIMP CFileSaveDialogWrap::GetTypeInfo(UINT iTInfo, LCID lcid, ITypeInfo FAR* FAR* ppTInfo)
{
    return E_NOTIMPL;
}

STDMETHODIMP CFileSaveDialogWrap::GetIDsOfNames(REFIID riid, OLECHAR FAR* FAR* rgszNames, UINT cNames, LCID lcid, DISPID FAR* rgDispId)
{
    HRESULT hr = S_OK;

    for (UINT i = 0; i < cNames; i++)
    {
        if (!_wcsicmp( rgszNames[i], L"Show" ))
			rgDispId[i] = DISPID_FSD_Show;
        else if (!_wcsicmp( rgszNames[i], L"Close" ))
			rgDispId[i] = DISPID_FSD_Close;
        else if (!_wcsicmp( rgszNames[i], L"HWND" ))
			rgDispId[i] = DISPID_FSD_HWND;
        else if (!_wcsicmp( rgszNames[i], L"Options" ))
			rgDispId[i] = DISPID_FSD_Options;
        else if (!_wcsicmp( rgszNames[i], L"FileTypes" ))
			rgDispId[i] = DISPID_FSD_FileTypes;
        else if (!_wcsicmp( rgszNames[i], L"Filter" ))
			rgDispId[i] = DISPID_FSD_Filter;
        else if (!_wcsicmp( rgszNames[i], L"FileTypeIndex" ))
			rgDispId[i] = DISPID_FSD_FileTypeIndex;
        else if (!_wcsicmp( rgszNames[i], L"FilterIndex" ))
			rgDispId[i] = DISPID_FSD_FileTypeIndex;
        else if (!_wcsicmp( rgszNames[i], L"DefaultFolder" ))
			rgDispId[i] = DISPID_FSD_DefaultFolder;
        else if (!_wcsicmp( rgszNames[i], L"Folder" ))
			rgDispId[i] = DISPID_FSD_Folder;
        else if (!_wcsicmp( rgszNames[i], L"SaveAsItem" ))
			rgDispId[i] = DISPID_FSD_SaveAsItem;
        else if (!_wcsicmp( rgszNames[i], L"AddPlace" ))
			rgDispId[i] = DISPID_FSD_AddPlace;
        else if (!_wcsicmp( rgszNames[i], L"ClientGUID" ))
			rgDispId[i] = DISPID_FSD_ClientGUID;
        else if (!_wcsicmp( rgszNames[i], L"ClearClientData" ))
			rgDispId[i] = DISPID_FSD_ClearClientData;
        else if (!_wcsicmp( rgszNames[i], L"Result" ))
			rgDispId[i] = DISPID_FSD_Result;
        else if (!_wcsicmp( rgszNames[i], L"CurrentSelection" ))
			rgDispId[i] = DISPID_FSD_CurrentSelection;
        else if (!_wcsicmp( rgszNames[i], L"FileName" ))
			rgDispId[i] = DISPID_FSD_FileName;
        else if (!_wcsicmp( rgszNames[i], L"FileNameLabel" ))
			rgDispId[i] = DISPID_FSD_FileNameLabel;
        else if (!_wcsicmp( rgszNames[i], L"OKButtonLabel" ))
			rgDispId[i] = DISPID_FSD_OKButtonLabel;
        else if (!_wcsicmp( rgszNames[i], L"CancelButtonLabel" ))
			rgDispId[i] = DISPID_FSD_CancelButtonLabel;
        else if (!_wcsicmp( rgszNames[i], L"DefaultExtension" ))
			rgDispId[i] = DISPID_FSD_DefaultExtension;
        else if (!_wcsicmp( rgszNames[i], L"Title" ))
			rgDispId[i] = DISPID_FSD_Title;
        else if (!_wcsicmp( rgszNames[i], L"NavigationRoot" ))
			rgDispId[i] = DISPID_FSD_NavigationRoot;
        else if (!_wcsicmp( rgszNames[i], L"Advise" ))
			rgDispId[i] = DISPID_FSD_Advise;
        else if (!_wcsicmp( rgszNames[i], L"Unadvise" ))
			rgDispId[i] = DISPID_FSD_Unadvise;
        else
        {
            rgDispId[i] = DISPID_UNKNOWN;
            hr = DISP_E_UNKNOWNNAME;
        }
    }

    return hr;
}

STDMETHODIMP CFileSaveDialogWrap::Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS FAR* pDispParams, VARIANT FAR* pVarResult, EXCEPINFO FAR* pExcepInfo, UINT FAR* puArgErr)
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
		case DISPID_FSD_Show :
			{
				if (!(wFlags & DISPATCH_METHOD))
					_com_issue_error( DISP_E_MEMBERNOTFOUND );

				if (pDispParams->cArgs == 0)
					varTempResult = Show();
				else if (pDispParams->cArgs == 1)
				{
					_variant_t varParent( pDispParams->rgvarg );
					varTempResult = Show( varParent );
				}
				else
					_com_issue_error( DISP_E_BADPARAMCOUNT );

				break;
			}
		case DISPID_FSD_Close :
			{
				if (!(wFlags & DISPATCH_METHOD))
					_com_issue_error( DISP_E_MEMBERNOTFOUND );

				if (pDispParams->cArgs == 0)
					Close();
				else if (pDispParams->cArgs == 1)
				{
					_variant_t varPretend( pDispParams->rgvarg );
					Close( varPretend );
				}
				else
					_com_issue_error( DISP_E_BADPARAMCOUNT );

				break;
			}
		case DISPID_FSD_AddPlace :
			{
				if (!(wFlags & DISPATCH_METHOD))
					_com_issue_error( DISP_E_MEMBERNOTFOUND );
				
				if (pDispParams->cArgs != 2)
					_com_issue_error( DISP_E_BADPARAMCOUNT );

				_variant_t varFolderPath( pDispParams->rgvarg + 1 );
				varFolderPath.ChangeType( VT_BSTR );

				_variant_t varWhere( pDispParams->rgvarg );

				AddPlace( varFolderPath.bstrVal, varWhere );
				
				break;
			}
		case DISPID_FSD_ClearClientData :
			{
				if (!(wFlags & DISPATCH_METHOD))
					_com_issue_error( DISP_E_MEMBERNOTFOUND );

				if (pDispParams->cArgs != 0)
					_com_issue_error( DISP_E_BADPARAMCOUNT );

				ClearClientData();
				
				break;
			}
		case DISPID_FSD_Advise :
			{
				if (!(wFlags & DISPATCH_METHOD))
					_com_issue_error( DISP_E_MEMBERNOTFOUND );

				if (pDispParams->cArgs != 1)
					_com_issue_error( DISP_E_BADPARAMCOUNT );

				_variant_t varEventSink( pDispParams->rgvarg );
				varTempResult = Advise( varEventSink );
				
				break;
			}
		case DISPID_FSD_Unadvise :
			{
				if (!(wFlags & DISPATCH_METHOD))
					_com_issue_error( DISP_E_MEMBERNOTFOUND );

				if (pDispParams->cArgs != 1)
					_com_issue_error( DISP_E_BADPARAMCOUNT );

				_variant_t varCookie( pDispParams->rgvarg );
				Unadvise( varCookie );
				
				break;
			}
		case DISPID_FSD_HWND :
			{
				if (!(wFlags & DISPATCH_PROPERTYGET))
					_com_issue_error( DISP_E_MEMBERNOTFOUND );

				if (pDispParams->cArgs != 0)
					_com_issue_error( DISP_E_BADPARAMCOUNT );

				varTempResult = HWND();
				
				break;
			}
		case DISPID_FSD_Result :
			{
				if (!(wFlags & DISPATCH_PROPERTYGET))
					_com_issue_error( DISP_E_MEMBERNOTFOUND );

				if (pDispParams->cArgs != 0)
					_com_issue_error( DISP_E_BADPARAMCOUNT );

				Result( varTempResult );
				
				break;
			}
		case DISPID_FSD_CurrentSelection :
			{
				if (!(wFlags & DISPATCH_PROPERTYGET))
					_com_issue_error( DISP_E_MEMBERNOTFOUND );

				if (pDispParams->cArgs != 0)
					_com_issue_error( DISP_E_BADPARAMCOUNT );

				CurrentSelection( varTempResult );
				
				break;
			}
		case DISPID_FSD_FileTypes :
			{
				if (!(wFlags & DISPATCH_PROPERTYPUTREF))
					_com_issue_error( DISP_E_MEMBERNOTFOUND );

				if (pDispParams->cArgs != 1)
					_com_issue_error( DISP_E_BADPARAMCOUNT );

				_variant_t varWhat( pDispParams->rgvarg );
				FileTypes( varWhat );

				break;
			}
		case DISPID_FSD_Filter :
			{
				if (!(wFlags & DISPATCH_PROPERTYPUT))
					_com_issue_error( DISP_E_MEMBERNOTFOUND );

				if (pDispParams->cArgs != 1)
					_com_issue_error( DISP_E_BADPARAMCOUNT );

				_variant_t varWhat( pDispParams->rgvarg );
				varWhat.ChangeType( VT_BSTR );

				Filter( varWhat.bstrVal );

				break;
			}
		case DISPID_FSD_DefaultFolder :
			{
				if (!(wFlags & DISPATCH_PROPERTYPUT))
					_com_issue_error( DISP_E_MEMBERNOTFOUND );

				if (pDispParams->cArgs != 1)
					_com_issue_error( DISP_E_BADPARAMCOUNT );

				_variant_t varWhat( pDispParams->rgvarg );
				varWhat.ChangeType( VT_BSTR );

				DefaultFolder( varWhat.bstrVal );

				break;
			}
		case DISPID_FSD_SaveAsItem :
			{
				if (!(wFlags & DISPATCH_PROPERTYPUT))
					_com_issue_error( DISP_E_MEMBERNOTFOUND );

				if (pDispParams->cArgs != 1)
					_com_issue_error( DISP_E_BADPARAMCOUNT );

				_variant_t varWhat( pDispParams->rgvarg );
				varWhat.ChangeType( VT_BSTR );

				SaveAsItem( varWhat.bstrVal );

				break;
			}
		case DISPID_FSD_ClientGUID :
			{
				if (!(wFlags & DISPATCH_PROPERTYPUT))
					_com_issue_error( DISP_E_MEMBERNOTFOUND );

				if (pDispParams->cArgs != 1)
					_com_issue_error( DISP_E_BADPARAMCOUNT );

				_variant_t varWhat( pDispParams->rgvarg );
				varWhat.ChangeType( VT_BSTR );

				ClientGUID( varWhat.bstrVal );

				break;
			}
		case DISPID_FSD_FileNameLabel :
			{
				if (!(wFlags & DISPATCH_PROPERTYPUT))
					_com_issue_error( DISP_E_MEMBERNOTFOUND );

				if (pDispParams->cArgs != 1)
					_com_issue_error( DISP_E_BADPARAMCOUNT );

				_variant_t varWhat( pDispParams->rgvarg );
				varWhat.ChangeType( VT_BSTR );

				FileNameLabel( varWhat.bstrVal );

				break;
			}
		case DISPID_FSD_OKButtonLabel :
			{
				if (!(wFlags & DISPATCH_PROPERTYPUT))
					_com_issue_error( DISP_E_MEMBERNOTFOUND );

				if (pDispParams->cArgs != 1)
					_com_issue_error( DISP_E_BADPARAMCOUNT );

				_variant_t varWhat( pDispParams->rgvarg );
				varWhat.ChangeType( VT_BSTR );

				OKButtonLabel( varWhat.bstrVal );

				break;
			}
		case DISPID_FSD_CancelButtonLabel :
			{
				if (!(wFlags & DISPATCH_PROPERTYPUT))
					_com_issue_error( DISP_E_MEMBERNOTFOUND );

				if (pDispParams->cArgs != 1)
					_com_issue_error( DISP_E_BADPARAMCOUNT );

				_variant_t varWhat( pDispParams->rgvarg );
				varWhat.ChangeType( VT_BSTR );

				CancelButtonLabel( varWhat.bstrVal );

				break;
			}
		case DISPID_FSD_DefaultExtension :
			{
				if (!(wFlags & DISPATCH_PROPERTYPUT))
					_com_issue_error( DISP_E_MEMBERNOTFOUND );

				if (pDispParams->cArgs != 1)
					_com_issue_error( DISP_E_BADPARAMCOUNT );

				_variant_t varWhat( pDispParams->rgvarg );
				varWhat.ChangeType( VT_BSTR );

				DefaultExtension( varWhat.bstrVal );

				break;
			}
		case DISPID_FSD_Title :
			{
				if (!(wFlags & DISPATCH_PROPERTYPUT))
					_com_issue_error( DISP_E_MEMBERNOTFOUND );

				if (pDispParams->cArgs != 1)
					_com_issue_error( DISP_E_BADPARAMCOUNT );

				_variant_t varWhat( pDispParams->rgvarg );
				varWhat.ChangeType( VT_BSTR );

				Title( varWhat.bstrVal );

				break;
			}
		case DISPID_FSD_NavigationRoot :
			{
				if (!(wFlags & DISPATCH_PROPERTYPUT))
					_com_issue_error( DISP_E_MEMBERNOTFOUND );

				if (pDispParams->cArgs != 1)
					_com_issue_error( DISP_E_BADPARAMCOUNT );

				_variant_t varWhat( pDispParams->rgvarg );
				varWhat.ChangeType( VT_BSTR );

				NavigationRoot( varWhat.bstrVal );

				break;
			}
		case DISPID_FSD_FileTypeIndex :
			{
				if (wFlags & DISPATCH_PROPERTYGET)
				{
					if (pDispParams->cArgs != 0)
						_com_issue_error( DISP_E_BADPARAMCOUNT );

					varTempResult = FileTypeIndex();
				}
				else if (wFlags & DISPATCH_PROPERTYPUT)
				{
					if (pDispParams->cArgs != 1)
						_com_issue_error( DISP_E_BADPARAMCOUNT );

					_variant_t varWhat( pDispParams->rgvarg );
					FileTypeIndex( varWhat );
				}
				else
					_com_issue_error( DISP_E_MEMBERNOTFOUND );

				break;
			}
		case DISPID_FSD_Options :
			{
				if (wFlags & DISPATCH_PROPERTYGET)
				{
					if (pDispParams->cArgs != 0)
						_com_issue_error( DISP_E_BADPARAMCOUNT );

					varTempResult = Options();
				}
				else if (wFlags & DISPATCH_PROPERTYPUT)
				{
					if (pDispParams->cArgs != 1)
						_com_issue_error( DISP_E_BADPARAMCOUNT );

					_variant_t varWhat( pDispParams->rgvarg );
					Options( varWhat );
				}
				else
					_com_issue_error( DISP_E_MEMBERNOTFOUND );

				break;
			}
		case DISPID_FSD_Folder :
			{
				if (wFlags & DISPATCH_PROPERTYGET)
				{
					if (pDispParams->cArgs != 0)
						_com_issue_error( DISP_E_BADPARAMCOUNT );

					 Folder( varTempResult );
				}
				else if (wFlags & DISPATCH_PROPERTYPUT)
				{
					if (pDispParams->cArgs != 1)
						_com_issue_error( DISP_E_BADPARAMCOUNT );

					_variant_t varWhat( pDispParams->rgvarg );
					varWhat.ChangeType( VT_BSTR );
					
					Folder( varWhat.bstrVal );
				}
				else
					_com_issue_error( DISP_E_MEMBERNOTFOUND );

				break;
			}
		case DISPID_FSD_FileName :
			{
				if (wFlags & DISPATCH_PROPERTYGET)
				{
					if (pDispParams->cArgs != 0)
						_com_issue_error( DISP_E_BADPARAMCOUNT );

					FileName( varTempResult );
				}
				else if (wFlags & DISPATCH_PROPERTYPUT)
				{
					if (pDispParams->cArgs != 1)
						_com_issue_error( DISP_E_BADPARAMCOUNT );

					_variant_t varWhat( pDispParams->rgvarg );
					varWhat.ChangeType( VT_BSTR );
					
					FileName( varWhat.bstrVal );
				}
				else
					_com_issue_error( DISP_E_MEMBERNOTFOUND );

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

// FileSaveDialogWrap Members

DWORD STDMETHODCALLTYPE CFileSaveDialogWrap::Options(void)
{
	FILEOPENDIALOGOPTIONS x = 0;
	HRESULT hr = m_pCore->GetOptions( &x );
	if (FAILED(hr))
		_com_issue_error( hr );

	return x;
}

void STDMETHODCALLTYPE CFileSaveDialogWrap::Options(DWORD dwWhat)
{
	HRESULT hr = m_pCore->SetOptions( FILEOPENDIALOGOPTIONS( dwWhat ) );
	if (FAILED(hr))
		_com_issue_error( hr );
}

bool STDMETHODCALLTYPE CFileSaveDialogWrap::Show(LONG_PTR hwndParent)
{
	HRESULT hr = m_pCore->Show( ::HWND( hwndParent ) );
	if (SUCCEEDED(hr))
		return true;

	if (hr != __HRESULT_FROM_WIN32(ERROR_CANCELLED))
		_com_issue_error( hr );

	return false;
}

void STDMETHODCALLTYPE CFileSaveDialogWrap::Close(bool pretend)
{
	HRESULT hr = m_pCore->Close( pretend ? S_FALSE : __HRESULT_FROM_WIN32(ERROR_CANCELLED) );
	if (FAILED(hr))
		_com_issue_error( hr );
}

LONG_PTR STDMETHODCALLTYPE CFileSaveDialogWrap::HWND(void)
{
	IOleWindowPtr pDialogWindow( m_pCore );

	::HWND x = NULL;
	HRESULT hr = pDialogWindow->GetWindow( &x );
	if (FAILED(hr))
		_com_issue_error( hr );

	return LONG_PTR( x );
}

void STDMETHODCALLTYPE CFileSaveDialogWrap::FileTypes(IDispatchPtr pWhat)
{
	_variant_t varTemp;
	DISPPARAMS dp = { 0 };
	HRESULT hr = pWhat->Invoke( DISPID_NEWENUM, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_PROPERTYGET, &dp, &varTemp, NULL, NULL );
	if (FAILED(hr))
		_com_issue_error( hr );

	IEnumVARIANTPtr pEnumFilters( varTemp );
	std::vector<COMDLG_FILTERSPEC> vec_cdfs;

	while (true)
	{
		varTemp.Clear();
		hr = pEnumFilters->Next( 1UL, &varTemp, NULL );
		if (FAILED(hr))
			_com_issue_error( hr );

		if (hr == S_FALSE)
			break;

		IDispatchPtr pFilter( varTemp );

		LPOLESTR rgszPropNames[] = { L"Name", L"Spec" };
		DISPID diProps[2];
		DISPID &diName = diProps[0];
		DISPID &diSpec = diProps[1];
		hr = pFilter->GetIDsOfNames( IID_NULL, rgszPropNames, 2, LOCALE_USER_DEFAULT, diProps );
		if (FAILED(hr))
			_com_issue_error( hr );

		_variant_t varName;
		hr = pFilter->Invoke( diName, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_PROPERTYGET, &dp, &varName, NULL, NULL );
		if (FAILED(hr))
			_com_issue_error( hr );

		COMDLG_FILTERSPEC cdfs;
		varName.ChangeType( VT_BSTR );
		cdfs.pszName = varName.Detach().bstrVal;

		_variant_t &varSpec = varName;
		hr = pFilter->Invoke( diSpec, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_PROPERTYGET, &dp, &varSpec, NULL, NULL );
		if (FAILED(hr))
			_com_issue_error( hr );

		varSpec.ChangeType( VT_BSTR );
		cdfs.pszSpec = varSpec.Detach().bstrVal;

		vec_cdfs.push_back( cdfs );
	}

	hr = m_pCore->SetFileTypes( vec_cdfs.size(), vec_cdfs.data() );
	if (FAILED(hr))
		_com_issue_error( hr );

	for (auto i = vec_cdfs.begin(); i != vec_cdfs.end(); i++)
	{
		SysFreeString( (BSTR) (i->pszName) );
		SysFreeString( (BSTR) (i->pszSpec) );
	}
}

void STDMETHODCALLTYPE CFileSaveDialogWrap::Filter(BSTR bsWhat)
{
	std::vector<COMDLG_FILTERSPEC> vec_cdfs;
	UINT c = SysStringLen( bsWhat );
	PCWSTR x = NULL, y = bsWhat;
	for (UINT i = 0; i <= c; i++)
	{
		if (!bsWhat[i])
		{
			if (x)
			{
				COMDLG_FILTERSPEC cdfs = { x, y };
				vec_cdfs.push_back( cdfs );

				x = NULL;
			}
			else
				x = y;

			y = bsWhat + i + 1;
		}
	}

	HRESULT hr = m_pCore->SetFileTypes( vec_cdfs.size(), vec_cdfs.data() );
	if (FAILED(hr))
		_com_issue_error( hr );
}

UINT STDMETHODCALLTYPE CFileSaveDialogWrap::FileTypeIndex(void)
{
	UINT x = 0;
	HRESULT hr = m_pCore->GetFileTypeIndex( &x );
	if (FAILED(hr))
		_com_issue_error( hr );

	return x;
}

void STDMETHODCALLTYPE CFileSaveDialogWrap::FileTypeIndex(UINT uiWhat)
{
	HRESULT hr = m_pCore->SetFileTypeIndex( uiWhat );
	if (FAILED(hr))
		_com_issue_error( hr );
}

void STDMETHODCALLTYPE CFileSaveDialogWrap::DefaultFolder(BSTR bsWhat)
{
	IShellItemPtr psi;
	HRESULT hr = SHCreateItemFromParsingName( bsWhat, NULL, IID_IShellItem, (PVOID *) &psi );
	if (FAILED(hr))
		_com_issue_error( hr );

	hr = m_pCore->SetDefaultFolder( psi );
	if (FAILED(hr))
		_com_issue_error( hr );
}

void STDMETHODCALLTYPE CFileSaveDialogWrap::Folder(BSTR bsWhat)
{
	IShellItemPtr psi;
	HRESULT hr = SHCreateItemFromParsingName( bsWhat, NULL, IID_IShellItem, (PVOID *) &psi );
	if (FAILED(hr))
		_com_issue_error( hr );

	hr = m_pCore->SetFolder( psi );
	if (FAILED(hr))
		_com_issue_error( hr );
}

void STDMETHODCALLTYPE CFileSaveDialogWrap::Folder(_variant_t &varPath)
{
	IShellItemPtr psi;
	HRESULT hr = m_pCore->GetFolder( &psi );
	if (FAILED(hr))
		_com_issue_error( hr );

	PWSTR pszPath = NULL;
	hr = psi->GetDisplayName( SIGDN_FILESYSPATH, &pszPath );
	if (FAILED(hr))
		_com_issue_error( hr );

	varPath = pszPath;
	CoTaskMemFree( pszPath );
}

void STDMETHODCALLTYPE CFileSaveDialogWrap::SaveAsItem(BSTR bsWhat)
{
	IShellItemPtr psi;
	HRESULT hr = SHCreateItemFromParsingName( bsWhat, NULL, IID_IShellItem, (PVOID *) &psi );
	if (FAILED(hr))
		_com_issue_error( hr );

	hr = m_pCore->SetSaveAsItem( psi );
	if (FAILED(hr))
		_com_issue_error( hr );
}

void STDMETHODCALLTYPE CFileSaveDialogWrap::AddPlace(BSTR bsFolderPath, LONG lWhere)
{
	IShellItemPtr psi;
	HRESULT hr = SHCreateItemFromParsingName( bsFolderPath, NULL, IID_IShellItem, (PVOID *) &psi );
	if (FAILED(hr))
		_com_issue_error( hr );
	
	hr = m_pCore->AddPlace( psi, FDAP( lWhere ) );
	if (FAILED(hr))
		_com_issue_error( hr );
}

void STDMETHODCALLTYPE CFileSaveDialogWrap::ClientGUID(BSTR bsWhat)
{
	GUID cguid;
	HRESULT hr = CLSIDFromString( bsWhat, &cguid );
	if (FAILED(hr))
		_com_issue_error( hr );

	hr = m_pCore->SetClientGuid( cguid );
	if (FAILED(hr))
		_com_issue_error( hr );
}

void STDMETHODCALLTYPE CFileSaveDialogWrap::ClearClientData(void)
{
	HRESULT hr = m_pCore->ClearClientData();
	if (FAILED(hr))
		_com_issue_error( hr );
}

void STDMETHODCALLTYPE CFileSaveDialogWrap::Result(_variant_t &varPath)
{
	IShellItemPtr psi;
	HRESULT hr = m_pCore->GetResult( &psi );
	if (FAILED(hr))
		_com_issue_error( hr );

	PWSTR pszPath = NULL;
	hr = psi->GetDisplayName( SIGDN_FILESYSPATH, &pszPath );
	if (FAILED(hr))
		_com_issue_error( hr );

	varPath = pszPath;
	CoTaskMemFree( pszPath );
}

void STDMETHODCALLTYPE CFileSaveDialogWrap::CurrentSelection(_variant_t &varPath)
{
	IShellItemPtr psi;
	HRESULT hr = m_pCore->GetCurrentSelection( &psi );
	if (FAILED(hr))
		_com_issue_error( hr );

	PWSTR pszPath = NULL;
	hr = psi->GetDisplayName( SIGDN_FILESYSPATH, &pszPath );
	if (FAILED(hr))
		_com_issue_error( hr );

	varPath = pszPath;
	CoTaskMemFree( pszPath );
}

void STDMETHODCALLTYPE CFileSaveDialogWrap::FileName(_variant_t &varName)
{
	PWSTR pszName = NULL;
	HRESULT hr = m_pCore->GetFileName( &pszName );
	if (FAILED(hr))
		_com_issue_error( hr );

	varName = pszName;
	CoTaskMemFree( pszName );
}

void STDMETHODCALLTYPE CFileSaveDialogWrap::FileName(BSTR bsWhat)
{
	HRESULT hr = m_pCore->SetFileName( bsWhat );
	if (FAILED(hr))
		_com_issue_error( hr );
}

void STDMETHODCALLTYPE CFileSaveDialogWrap::FileNameLabel(BSTR bsWhat)
{
	HRESULT hr = m_pCore->SetFileNameLabel( bsWhat );
	if (FAILED(hr))
		_com_issue_error( hr );
}

void STDMETHODCALLTYPE CFileSaveDialogWrap::OKButtonLabel(BSTR bsWhat)
{
	HRESULT hr = m_pCore->SetOkButtonLabel( bsWhat );
	if (FAILED(hr))
		_com_issue_error( hr );
}

void STDMETHODCALLTYPE CFileSaveDialogWrap::CancelButtonLabel(BSTR bsWhat)
{
	IFileDialog2Ptr pCoreAdvanced( m_pCore );
	HRESULT hr = pCoreAdvanced->SetCancelButtonLabel( bsWhat );
	if (FAILED(hr))
		_com_issue_error( hr );
}

void STDMETHODCALLTYPE CFileSaveDialogWrap::DefaultExtension(BSTR bsWhat)
{
	HRESULT hr = m_pCore->SetDefaultExtension( bsWhat );
	if (FAILED(hr))
		_com_issue_error( hr );
}

void STDMETHODCALLTYPE CFileSaveDialogWrap::Title(BSTR bsWhat)
{
	HRESULT hr = m_pCore->SetTitle( bsWhat );
	if (FAILED(hr))
		_com_issue_error( hr );
}

void STDMETHODCALLTYPE CFileSaveDialogWrap::NavigationRoot(BSTR bsWhat)
{
	IShellItemPtr psi;
	HRESULT hr = SHCreateItemFromParsingName( bsWhat, NULL, IID_IShellItem, (PVOID *) &psi );
	if (FAILED(hr))
		_com_issue_error( hr );

	IFileDialog2Ptr pCoreAdvanced( m_pCore );
	hr = pCoreAdvanced->SetNavigationRoot( psi );
	if (FAILED(hr))
		_com_issue_error( hr );
}

DWORD STDMETHODCALLTYPE CFileSaveDialogWrap::Advise(IDispatchExPtr pEventSink)
{
	HRESULT hr = S_OK;

	{
		DISPID diFileDialog = DISPID_UNKNOWN;
		_bstr_t bsFileDialog = "FileDialog";
		hr = pEventSink->GetDispID( bsFileDialog.GetBSTR(), fdexNameEnsure, &diFileDialog );
		if (FAILED(hr))
			_com_issue_error( hr );

		_variant_t varSelf = LPDISPATCH( this );
		DISPID diNamed = DISPID_PROPERTYPUT;
		DISPPARAMS dp = { &varSelf, &diNamed, 1, 1 };
		hr = pEventSink->InvokeEx( diFileDialog, LOCALE_USER_DEFAULT, DISPATCH_PROPERTYPUTREF, &dp, NULL, NULL, NULL );
		if (FAILED(hr))
			_com_issue_error( hr );
	}

	IFileDialogEventsPtr pfde = new CFileDialogEventsWrap( pEventSink );
	DWORD dwCookie = 0;
	hr = m_pCore->Advise( pfde, &dwCookie );
	if (FAILED(hr))
		_com_issue_error( hr );

	return dwCookie;
}

void STDMETHODCALLTYPE CFileSaveDialogWrap::Unadvise(DWORD dwCookie)
{
	HRESULT hr = m_pCore->Unadvise( dwCookie );
	if (FAILED(hr))
		_com_issue_error( hr );
}