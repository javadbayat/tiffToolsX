#pragma once
#include <Windows.h>
#include <ShObjIdl.h>
#include <DispEx.h>
#include <comdef.h>

#define DISPID_FSD_Show DISPID_VALUE
#define DISPID_FSD_Close 1L
#define DISPID_FSD_HWND 2L
#define DISPID_FSD_Options 3L
#define DISPID_FSD_FileTypes 4L
#define DISPID_FSD_Filter 5L
#define DISPID_FSD_FileTypeIndex 6L
#define DISPID_FSD_DefaultFolder 7L
#define DISPID_FSD_Folder 8L
#define DISPID_FSD_SaveAsItem 128L
#define DISPID_FSD_AddPlace 9L
#define DISPID_FSD_ClientGUID 10L
#define DISPID_FSD_ClearClientData 11L
#define DISPID_FSD_Result 12L
#define DISPID_FSD_CurrentSelection 13L
#define DISPID_FSD_FileName 14L
#define DISPID_FSD_FileNameLabel 15L
#define DISPID_FSD_OKButtonLabel 16L
#define DISPID_FSD_CancelButtonLabel 17L
#define DISPID_FSD_DefaultExtension 18L
#define DISPID_FSD_Title 19L
#define DISPID_FSD_NavigationRoot 20L
#define DISPID_FSD_Advise 21L
#define DISPID_FSD_Unadvise 22L

class CFileSaveDialogWrap : public IDispatch
{
private:
	_COM_SMARTPTR_TYPEDEF( IShellItem, __uuidof(IShellItem) );
	_COM_SMARTPTR_TYPEDEF( IShellItemArray, __uuidof(IShellItemArray) );
	_COM_SMARTPTR_TYPEDEF( IFileDialog, __uuidof(IFileDialog) );
	_COM_SMARTPTR_TYPEDEF( IFileDialog2, __uuidof(IFileDialog2) );
	_COM_SMARTPTR_TYPEDEF( IFileDialogEvents, __uuidof(IFileDialogEvents) );
	_COM_SMARTPTR_TYPEDEF( IFileSaveDialog, __uuidof(IFileSaveDialog) );
	
	ULONG m_cRef;
	IDispatchExPtr m_pScript;
	IFileSaveDialogPtr m_pCore;
public:
	CFileSaveDialogWrap(IDispatchExPtr pScript);
	~CFileSaveDialogWrap(void);

    // IUnknown Members
    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppv);
    ULONG STDMETHODCALLTYPE AddRef(void);
    ULONG STDMETHODCALLTYPE Release(void);

    // IDispatch Members
    HRESULT STDMETHODCALLTYPE GetTypeInfoCount(UINT FAR* pctInfo);
    HRESULT STDMETHODCALLTYPE GetTypeInfo(UINT iTInfo, LCID lcid, ITypeInfo FAR* FAR* ppTInfo);
    HRESULT STDMETHODCALLTYPE GetIDsOfNames(REFIID riid, OLECHAR FAR* FAR* rgszNames, UINT cNames, LCID lcid, DISPID FAR* rgDispId);
	HRESULT STDMETHODCALLTYPE Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS FAR* pDispParams, VARIANT FAR* pVarResult, EXCEPINFO FAR* pExcepInfo, UINT FAR* puArgErr);

	// FileSaveDialogWrap Members
	bool STDMETHODCALLTYPE Show(LONG_PTR hwndParent = 0);
	void STDMETHODCALLTYPE Close(bool pretend = false);
	LONG_PTR STDMETHODCALLTYPE HWND(void);
	DWORD STDMETHODCALLTYPE Options(void);
	void STDMETHODCALLTYPE Options(DWORD dwWhat);
	void STDMETHODCALLTYPE FileTypes(IDispatchPtr pWhat);
	void STDMETHODCALLTYPE Filter(BSTR bsWhat);
	UINT STDMETHODCALLTYPE FileTypeIndex(void);
	void STDMETHODCALLTYPE FileTypeIndex(UINT uiWhat);
	void STDMETHODCALLTYPE DefaultFolder(BSTR bsWhat);
	void STDMETHODCALLTYPE Folder(BSTR bsWhat);
	void STDMETHODCALLTYPE Folder(_variant_t &varPath);
	void STDMETHODCALLTYPE SaveAsItem(BSTR bsWhat);
	void STDMETHODCALLTYPE AddPlace(BSTR bsFolderPath, LONG lWhere);
	void STDMETHODCALLTYPE ClientGUID(BSTR bsWhat);
	void STDMETHODCALLTYPE ClearClientData(void);
	void STDMETHODCALLTYPE Result(_variant_t &varPath);
	void STDMETHODCALLTYPE CurrentSelection(_variant_t &varPath);
	void STDMETHODCALLTYPE FileName(_variant_t &varName);
	void STDMETHODCALLTYPE FileName(BSTR bsWhat);
	void STDMETHODCALLTYPE FileNameLabel(BSTR bsWhat);
	void STDMETHODCALLTYPE OKButtonLabel(BSTR bsWhat);
	void STDMETHODCALLTYPE CancelButtonLabel(BSTR bsWhat);
	void STDMETHODCALLTYPE DefaultExtension(BSTR bsWhat);
	void STDMETHODCALLTYPE Title(BSTR bsWhat);
	void STDMETHODCALLTYPE NavigationRoot(BSTR bsWhat);
	DWORD STDMETHODCALLTYPE Advise(IDispatchExPtr pEventSink);
	void STDMETHODCALLTYPE Unadvise(DWORD dwCookie);
};