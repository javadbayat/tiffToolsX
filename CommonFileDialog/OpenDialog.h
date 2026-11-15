#pragma once
#include <Windows.h>
#include <ShObjIdl.h>
#include <DispEx.h>
#include <comdef.h>

#define DISPID_FOD_Show DISPID_VALUE
#define DISPID_FOD_Close 1L
#define DISPID_FOD_HWND 2L
#define DISPID_FOD_Options 3L
#define DISPID_FOD_FileTypes 4L
#define DISPID_FOD_Filter 5L
#define DISPID_FOD_FileTypeIndex 6L
#define DISPID_FOD_DefaultFolder 7L
#define DISPID_FOD_Folder 8L
#define DISPID_FOD_AddPlace 9L
#define DISPID_FOD_ClientGUID 10L
#define DISPID_FOD_ClearClientData 11L
#define DISPID_FOD_Result 12L
#define DISPID_FOD_Results 128L
#define DISPID_FOD_CurrentSelection 13L
#define DISPID_FOD_SelectedItems 129L
#define DISPID_FOD_FileName 14L
#define DISPID_FOD_FileNameLabel 15L
#define DISPID_FOD_OKButtonLabel 16L
#define DISPID_FOD_CancelButtonLabel 17L
#define DISPID_FOD_DefaultExtension 18L
#define DISPID_FOD_Title 19L
#define DISPID_FOD_NavigationRoot 20L
#define DISPID_FOD_Advise 21L
#define DISPID_FOD_Unadvise 22L

class CFileOpenDialogWrap : public IDispatch
{
private:
	_COM_SMARTPTR_TYPEDEF( IShellItem, __uuidof(IShellItem) );
	_COM_SMARTPTR_TYPEDEF( IShellItemArray, __uuidof(IShellItemArray) );
	_COM_SMARTPTR_TYPEDEF( IFileDialog, __uuidof(IFileDialog) );
	_COM_SMARTPTR_TYPEDEF( IFileDialog2, __uuidof(IFileDialog2) );
	_COM_SMARTPTR_TYPEDEF( IFileDialogEvents, __uuidof(IFileDialogEvents) );
	_COM_SMARTPTR_TYPEDEF( IFileOpenDialog, __uuidof(IFileOpenDialog) );
	
	ULONG m_cRef;
	IDispatchExPtr m_pScript;
	IFileOpenDialogPtr m_pCore;

	void TranslateShellItemArray(const IShellItemArrayPtr &psia, LPVARIANT lpvarPathArray);
public:
	CFileOpenDialogWrap(IDispatchExPtr pScript);
	~CFileOpenDialogWrap(void);

    // IUnknown Members
    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppv);
    ULONG STDMETHODCALLTYPE AddRef(void);
    ULONG STDMETHODCALLTYPE Release(void);

    // IDispatch Members
    HRESULT STDMETHODCALLTYPE GetTypeInfoCount(UINT FAR* pctInfo);
    HRESULT STDMETHODCALLTYPE GetTypeInfo(UINT iTInfo, LCID lcid, ITypeInfo FAR* FAR* ppTInfo);
    HRESULT STDMETHODCALLTYPE GetIDsOfNames(REFIID riid, OLECHAR FAR* FAR* rgszNames, UINT cNames, LCID lcid, DISPID FAR* rgDispId);
	HRESULT STDMETHODCALLTYPE Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS FAR* pDispParams, VARIANT FAR* pVarResult, EXCEPINFO FAR* pExcepInfo, UINT FAR* puArgErr);

	// FileOpenDialogWrap Members
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
	void STDMETHODCALLTYPE AddPlace(BSTR bsFolderPath, LONG lWhere);
	void STDMETHODCALLTYPE ClientGUID(BSTR bsWhat);
	void STDMETHODCALLTYPE ClearClientData(void);
	void STDMETHODCALLTYPE Result(_variant_t &varPath);
	void STDMETHODCALLTYPE Results(_variant_t &varPathArray);
	void STDMETHODCALLTYPE CurrentSelection(_variant_t &varPath);
	void STDMETHODCALLTYPE SelectedItems(_variant_t &varPathArray);
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