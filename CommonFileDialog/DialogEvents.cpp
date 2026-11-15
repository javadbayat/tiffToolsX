#define _CRT_SECURE_NO_WARNINGS

#include "DialogEvents.h"
#include <stdlib.h>

// Constructor and Destructor

CFileDialogEventsWrap::CFileDialogEventsWrap(IDispatchPtr pCore)
	: m_cRef( 0 ), m_pCore( pCore )
{
	
}

CFileDialogEventsWrap::~CFileDialogEventsWrap(void)
{
	
}

// IUnknown Members

STDMETHODIMP CFileDialogEventsWrap::QueryInterface(REFIID riid, void **ppv)
{
    HRESULT hr = S_OK;
    if (ppv)
    {
        *ppv = NULL;

		if (IsEqualIID( riid, IID_IFileDialogEvents ) || IsEqualIID( riid, IID_IUnknown ))
			*ppv = (IFileDialogEvents *) (this);
        else
            hr = E_NOINTERFACE;

        if (*ppv)
            AddRef();
    }
    else
        hr = E_INVALIDARG;

    return hr;
}

STDMETHODIMP_(ULONG) CFileDialogEventsWrap::AddRef(void)
{
    return((ULONG) (InterlockedIncrement((long *) &m_cRef)));
}

STDMETHODIMP_(ULONG) CFileDialogEventsWrap::Release(void)
{
    ULONG cRef = (ULONG) (InterlockedDecrement((long *) &m_cRef));
    if (!cRef)
        delete this;

    return cRef;
}

// FileDialogEventsWrap Members

STDMETHODIMP CFileDialogEventsWrap::OnFileOk(IFileDialog *)
{
	try
	{
		PWSTR pszWrapped = L"OnFileOk";
		DISPID diWrapped = DISPID_UNKNOWN;
		HRESULT hr = m_pCore->GetIDsOfNames( IID_NULL, &pszWrapped, 1U, LOCALE_USER_DEFAULT, &diWrapped );
		if (FAILED(hr))
			_com_issue_error( E_NOTIMPL );

		DISPPARAMS dp = { 0 };
		_variant_t varResponse;
		hr = m_pCore->Invoke( diWrapped, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &dp, &varResponse, NULL, NULL );
		if (FAILED(hr))
			_com_issue_error( hr );

		return varResponse ? S_OK : S_FALSE;
	}
	catch (_com_error &ce)
	{
		return ce.Error();
	}

	return S_OK;
}

STDMETHODIMP CFileDialogEventsWrap::OnShareViolation(IFileDialog *, IShellItem *psi, FDE_SHAREVIOLATION_RESPONSE *pResponse)
{
	try
	{
		PWSTR pszWrapped = L"OnShareViolation";
		DISPID diWrapped = DISPID_UNKNOWN;
		HRESULT hr = m_pCore->GetIDsOfNames( IID_NULL, &pszWrapped, 1U, LOCALE_USER_DEFAULT, &diWrapped );
		if (FAILED(hr))
			_com_issue_error( E_NOTIMPL );
		
		PWSTR pszPath = NULL;
		hr = psi->GetDisplayName( SIGDN_FILESYSPATH, &pszPath );
		if (FAILED(hr))
			_com_issue_error( hr );

		_variant_t varPath( pszPath );
		CoTaskMemFree( pszPath );

		DISPPARAMS dp = { &varPath, NULL, 1, 0 };
		_variant_t varResponse;
		hr = m_pCore->Invoke( diWrapped, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &dp, &varResponse, NULL, NULL );
		if (FAILED(hr))
			_com_issue_error( hr );

		*pResponse = FDE_SHAREVIOLATION_RESPONSE( (long) varResponse );
	}
	catch (_com_error &ce)
	{
		return ce.Error();
	}

	return S_OK;
}

STDMETHODIMP CFileDialogEventsWrap::OnOverwrite(IFileDialog *, IShellItem *psi, FDE_OVERWRITE_RESPONSE *pResponse)
{
	try
	{
		PWSTR pszWrapped = L"OnOverwrite";
		DISPID diWrapped = DISPID_UNKNOWN;
		HRESULT hr = m_pCore->GetIDsOfNames( IID_NULL, &pszWrapped, 1U, LOCALE_USER_DEFAULT, &diWrapped );
		if (FAILED(hr))
			_com_issue_error( E_NOTIMPL );
		
		PWSTR pszPath = NULL;
		hr = psi->GetDisplayName( SIGDN_FILESYSPATH, &pszPath );
		if (FAILED(hr))
			_com_issue_error( hr );

		_variant_t varPath( pszPath );
		CoTaskMemFree( pszPath );

		DISPPARAMS dp = { &varPath, NULL, 1, 0 };
		_variant_t varResponse;
		hr = m_pCore->Invoke( diWrapped, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &dp, &varResponse, NULL, NULL );
		if (FAILED(hr))
			_com_issue_error( hr );

		*pResponse = FDE_OVERWRITE_RESPONSE( (long) varResponse );
	}
	catch (_com_error &ce)
	{
		return ce.Error();
	}

	return S_OK;
}

STDMETHODIMP CFileDialogEventsWrap::OnSelectionChange(IFileDialog *)
{
	try
	{
		PWSTR pszWrapped = L"OnSelectionChange";
		DISPID diWrapped = DISPID_UNKNOWN;
		HRESULT hr = m_pCore->GetIDsOfNames( IID_NULL, &pszWrapped, 1U, LOCALE_USER_DEFAULT, &diWrapped );
		if (FAILED(hr))
			_com_issue_error( E_NOTIMPL );

		DISPPARAMS dp = { 0 };
		hr = m_pCore->Invoke( diWrapped, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &dp, NULL, NULL, NULL );
		if (FAILED(hr))
			_com_issue_error( hr );
	}
	catch (_com_error &ce)
	{
		return ce.Error();
	}

	return S_OK;
}

STDMETHODIMP CFileDialogEventsWrap::OnTypeChange(IFileDialog *)
{
	try
	{
		PWSTR pszWrapped = L"OnTypeChange";
		DISPID diWrapped = DISPID_UNKNOWN;
		HRESULT hr = m_pCore->GetIDsOfNames( IID_NULL, &pszWrapped, 1U, LOCALE_USER_DEFAULT, &diWrapped );
		if (FAILED(hr))
			_com_issue_error( E_NOTIMPL );

		DISPPARAMS dp = { 0 };
		hr = m_pCore->Invoke( diWrapped, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &dp, NULL, NULL, NULL );
		if (FAILED(hr))
			_com_issue_error( hr );
	}
	catch (_com_error &ce)
	{
		return ce.Error();
	}

	return S_OK;
}

STDMETHODIMP CFileDialogEventsWrap::OnFolderChange(IFileDialog *)
{
	try
	{
		PWSTR pszWrapped = L"OnFolderChange";
		DISPID diWrapped = DISPID_UNKNOWN;
		HRESULT hr = m_pCore->GetIDsOfNames( IID_NULL, &pszWrapped, 1U, LOCALE_USER_DEFAULT, &diWrapped );
		if (FAILED(hr))
			_com_issue_error( E_NOTIMPL );

		DISPPARAMS dp = { 0 };
		hr = m_pCore->Invoke( diWrapped, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &dp, NULL, NULL, NULL );
		if (FAILED(hr))
			_com_issue_error( hr );
	}
	catch (_com_error &ce)
	{
		return ce.Error();
	}

	return S_OK;
}

STDMETHODIMP CFileDialogEventsWrap::OnFolderChanging(IFileDialog *, IShellItem *psiFolder)
{
	try
	{
		PWSTR pszWrapped = L"OnFolderChanging";
		DISPID diWrapped = DISPID_UNKNOWN;
		HRESULT hr = m_pCore->GetIDsOfNames( IID_NULL, &pszWrapped, 1U, LOCALE_USER_DEFAULT, &diWrapped );
		if (FAILED(hr))
			_com_issue_error( E_NOTIMPL );
		
		PWSTR pszPath = NULL;
		hr = psiFolder->GetDisplayName( SIGDN_FILESYSPATH, &pszPath );
		if (FAILED(hr))
			_com_issue_error( hr );

		_variant_t varPath( pszPath );
		CoTaskMemFree( pszPath );

		DISPPARAMS dp = { &varPath, NULL, 1, 0 };
		hr = m_pCore->Invoke( diWrapped, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &dp, NULL, NULL, NULL );
		if (FAILED(hr))
			_com_issue_error( hr );
	}
	catch (_com_error &ce)
	{
		return ce.Error();
	}

	return S_OK;
}