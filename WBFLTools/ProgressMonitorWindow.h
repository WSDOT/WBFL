///////////////////////////////////////////////////////////////////////
// WBFLTools - Utility Tools for the WBFL
// Copyright © 1999-2017  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Library Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// ProgressMonitorWindow.h : Declaration of the CProgressMonitorWindow

#ifndef __PROGRESSMONITORWINDOW_H_
#define __PROGRESSMONITORWINDOW_H_

#include "resource.h"       // main symbols
#include "ProgressMonitorDlg.h"
 
#include <memory>
#include <fstream>

/////////////////////////////////////////////////////////////////////////////
// CProgressMonitorWindow
class ATL_NO_VTABLE CProgressMonitorWindow : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CProgressMonitorWindow, &CLSID_ProgressMonitorWindow>,
	public ISupportErrorInfo,
	public IProgressMonitorWindow,
	public IProgressMonitor,
	public ILogProgressToFile
{
public:
	CProgressMonitorWindow();
	~CProgressMonitorWindow();

DECLARE_REGISTRY_RESOURCEID(IDR_PROGRESSMONITORWINDOW)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CProgressMonitorWindow)
	COM_INTERFACE_ENTRY(IProgressMonitorWindow)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IProgressMonitor)
	COM_INTERFACE_ENTRY(ILogProgressToFile)
END_COM_MAP()

   HRESULT FinalConstruct();
   void FinalRelease();

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IProgressMonitorWindow
public:
   STDMETHOD(Close)() override;
	STDMETHOD(Hide)() override;
	STDMETHOD(Show)(/*[in]*/BSTR msg,/*[in]*/HWND hParent) override;
	STDMETHOD(get_HasCancel)(/*[out, retval]*/ VARIANT_BOOL *pVal) override;
	STDMETHOD(put_HasCancel)(/*[in]*/ VARIANT_BOOL newVal) override;
	STDMETHOD(get_HasGauge)(/*[out, retval]*/ VARIANT_BOOL *pVal) override;
	STDMETHOD(put_HasGauge)(/*[in]*/ VARIANT_BOOL newVal) override;

// IProgressMonitor
	STDMETHOD(put_GaugeValue)(LONG cookie, LONG ) override;
	STDMETHOD(put_Message)(LONG cookie, BSTR ) override;
	STDMETHOD(get_WasCancelled)(VARIANT_BOOL * pVal) override;

// ILogProgressToFile
	STDMETHOD(OpenLogFile)(BSTR fileName) override;
	STDMETHOD(CloseLogFile)() override;

private:
   std::unique_ptr<CProgressMonitorDlg> m_pDlg;
   CWnd m_wndParent;

   std::_tofstream m_FileStream;
   bool m_IsFileOpen;

};

#endif //__PROGRESSMONITORWINDOW_H_
