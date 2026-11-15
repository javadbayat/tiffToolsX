#pragma once
#include <Windows.h>
#include <ShObjIdl.h>
#include <comdef.h>

class CFileDialogEventsWrap : public IFileDialogEvents
{
private:
	ULONG m_cRef;
	IDispatchPtr m_pCore;
public:
	CFileDialogEventsWrap(IDispatchPtr pCore);
	~CFileDialogEventsWrap(void);

    // IUnknown Members
    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppv);
    ULONG STDMETHODCALLTYPE AddRef(void);
    ULONG STDMETHODCALLTYPE Release(void);

	// FileDialogEventsWrap Members
	HRESULT STDMETHODCALLTYPE OnFileOk(IFileDialog *);
	HRESULT STDMETHODCALLTYPE OnFolderChange(IFileDialog *);
	HRESULT STDMETHODCALLTYPE OnFolderChanging(IFileDialog *, IShellItem *psiFolder);
	HRESULT STDMETHODCALLTYPE OnOverwrite(IFileDialog *, IShellItem *psi, FDE_OVERWRITE_RESPONSE *pResponse);
	HRESULT STDMETHODCALLTYPE OnSelectionChange(IFileDialog *);
	HRESULT STDMETHODCALLTYPE OnShareViolation(IFileDialog *, IShellItem *psi, FDE_SHAREVIOLATION_RESPONSE *pResponse);
	HRESULT STDMETHODCALLTYPE OnTypeChange(IFileDialog *);
};