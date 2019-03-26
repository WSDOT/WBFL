///////////////////////////////////////////////////////////////////////
// Library - Framework for libraries
// Copyright © 1999-2018  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the Alternate Route Library Open Source License as published by 
// the Washington State Department of Transportation, Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but is distributed 
// AS IS, WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See the Alternate Route Library Open Source 
// License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License 
// along with this program; if not, write to the Washington State Department of 
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// LibraryViewer.h : Declaration of the CLibraryViewer

#ifndef __LIBRARYVIEWER_H_
#define __LIBRARYVIEWER_H_

#include "resource.h"       // main symbols
#include <atlctl.h>
#include <CommCtrl.h>


/////////////////////////////////////////////////////////////////////////////
// CLibraryViewer
class ATL_NO_VTABLE CLibraryViewer : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CStockPropImpl<CLibraryViewer, ILibraryViewer, &IID_ILibraryViewer, &LIBID_WBFLLibrary>,
	public CComCompositeControl<CLibraryViewer>,
	public IPersistStreamInitImpl<CLibraryViewer>,
	public IOleControlImpl<CLibraryViewer>,
	public IOleObjectImpl<CLibraryViewer>,
	public IOleInPlaceActiveObjectImpl<CLibraryViewer>,
	public IViewObjectExImpl<CLibraryViewer>,
	public IOleInPlaceObjectWindowlessImpl<CLibraryViewer>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CLibraryViewer>,
	public IPersistStorageImpl<CLibraryViewer>,
	public ISpecifyPropertyPagesImpl<CLibraryViewer>,
	public IQuickActivateImpl<CLibraryViewer>,
	public IDataObjectImpl<CLibraryViewer>,
	public IProvideClassInfo2Impl<&CLSID_LibraryViewer, &IID_ILibraryViewerEvents, &LIBID_WBFLLibrary>,
	public IPropertyNotifySinkCP<CLibraryViewer>,
	public CComCoClass<CLibraryViewer, &CLSID_LibraryViewer>,
	public ILibraryMgrEvents
{
public:
	CLibraryViewer()
	{
		m_bWindowOnly = TRUE;
		CalcExtent(m_sizeExtent);
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_LIBRARYVIEWER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLibraryViewer)
	COM_INTERFACE_ENTRY(ILibraryViewer)
	COM_INTERFACE_ENTRY2(IDispatch,ILibraryViewer)
	COM_INTERFACE_ENTRY(IViewObjectEx)
	COM_INTERFACE_ENTRY(IViewObject2)
	COM_INTERFACE_ENTRY(IViewObject)
	COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceObject)
	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY(IOleControl)
	COM_INTERFACE_ENTRY(IOleObject)
	COM_INTERFACE_ENTRY(IPersistStreamInit)
	COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY(IQuickActivate)
	COM_INTERFACE_ENTRY(IPersistStorage)
	COM_INTERFACE_ENTRY(IDataObject)
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)

	COM_INTERFACE_ENTRY(ILibraryMgrEvents)
END_COM_MAP()

BEGIN_PROP_MAP(CLibraryViewer)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	PROP_ENTRY("AutoSize", DISPID_AUTOSIZE, CLSID_NULL)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CLibraryViewer)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CLibraryViewer)
	CHAIN_MSG_MAP(CComCompositeControl<CLibraryViewer>)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
   NOTIFY_HANDLER(IDC_TREE,TVN_SELCHANGED,OnSelChanged_Tree)
   NOTIFY_HANDLER(IDC_LIST,NM_DBLCLK,OnDblClick)
   NOTIFY_HANDLER(IDC_LIST,NM_RCLICK,OnRightClick)
   MESSAGE_HANDLER(WM_SIZE, OnSize)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

BEGIN_SINK_MAP(CLibraryViewer)
	//Make sure the Event Handlers have __stdcall calling convention
END_SINK_MAP()

   LRESULT OnSelChanged_Tree(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
   LRESULT OnDblClick(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
   LRESULT OnRightClick(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	STDMETHOD(OnAmbientPropertyChange)(DISPID dispid)
	{
		if (dispid == DISPID_AMBIENT_BACKCOLOR)
		{
			SetBackgroundColorFromAmbient();
			FireViewChange();
		}
		return IOleControlImpl<CLibraryViewer>::OnAmbientPropertyChange(dispid);
	}


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
	{
		static const IID* arr[] = 
		{
			&IID_ILibraryViewer,
		};
		for (int i = 0; i<sizeof(arr)/sizeof(arr[0]); i++)
		{
			if (InlineIsEqualGUID(*arr[i], riid))
				return S_OK;
		}
		return S_FALSE;
	}

// IViewObjectEx
	DECLARE_VIEW_STATUS(0)

// ILibraryViewer
public:
	STDMETHOD(EditCurSel)() override;
	STDMETHOD(get_LibraryMgr)(/*[out, retval]*/ ILibraryMgr* *pVal) override;
	STDMETHOD(putref_LibraryMgr)(/*[in]*/ ILibraryMgr* newVal) override;

	enum { IDD = IDD_LIBRARYVIEWER };
   LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

private:
   CComPtr<ILibraryMgr> m_LibMgr;
   HIMAGELIST m_hTVImageList;
   HIMAGELIST m_hLVImageList;

   void PopulateListViewImageList();
   void PopulateTreeControl();
   void PopulateListControl(BSTR bstrName);

   BSTR CurLibName();
   BSTR CurEntryName();

// ILibraryMgrEvents
	STDMETHOD(OnNameChanged)(BSTR oldName, BSTR newName)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(OnChanged)(ILibraryMgr * libMgr)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(OnLibraryNameChanged)(BSTR oldName, BSTR newName)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(OnLibraryChanged)(ILibrary * lib)
	{
      PopulateListControl(CurLibName());
		return S_OK;
	}
	STDMETHOD(OnEntryNameChanged)(ILibrary * lib, BSTR oldName, BSTR newName)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(OnEntryChanged)(ILibrary * lib, ILibraryEntry * entry)
	{
		return E_NOTIMPL;
	}
};

#endif //__LIBRARYVIEWER_H_
