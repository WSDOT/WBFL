///////////////////////////////////////////////////////////////////////
// ReportManagerAgent - Provides report manager as an Agent
// Copyright © 1999-2013  Washington State Department of Transportation
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

// ReportManager.h : Declaration of the CReportManager

#pragma once

#include "resource.h"       // main symbols
#include "IReportManager.h"
#include <ReportManager\ReportBuilderManager.h>
#include <ReportManager\ReportBuilder.h>

/////////////////////////////////////////////////////////////////////////////
// CReportManager
class ATL_NO_VTABLE CReportManager : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CReportManager, &CLSID_ReportManager>,
   public IAgentEx,
	public IReportManager
{
public:
	CReportManager()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_REPORTMANAGER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CReportManager)
	COM_INTERFACE_ENTRY(IAgent)
	COM_INTERFACE_ENTRY(IAgentEx)
	COM_INTERFACE_ENTRY(IReportManager)
END_COM_MAP()

private:
   CReportBuilderManager m_RptMgr;
   IBroker* m_pBroker; // weak reference

// IAgentEx
public:
   STDMETHOD(SetBroker)(/*[in]*/ IBroker* pBroker);
   STDMETHOD(RegInterfaces)();
	STDMETHOD(Init)();
	STDMETHOD(Init2)();
	STDMETHOD(Reset)();
	STDMETHOD(ShutDown)();
   STDMETHOD(GetClassID)(CLSID* pCLSID);


// IReportManager
public:
   virtual void AddReportBuilder(CReportBuilder* pReportBuilder);
   virtual void AddReportBuilder(boost::shared_ptr<CReportBuilder>& pReportBuilder);
   virtual CollectionIndexType GetReportBuilderCount(bool bIncludeHidden) const;
   virtual boost::shared_ptr<CReportBuilder> GetReportBuilder(LPCTSTR strReportName);
   virtual boost::shared_ptr<CReportBuilder> GetReportBuilder(const std::_tstring& strReportName);
   virtual boost::shared_ptr<CReportBuilder> RemoveReportBuilder(LPCTSTR strReportName);
   virtual boost::shared_ptr<CReportBuilder> RemoveReportBuilder(const std::_tstring& strReportName);
   virtual std::vector<std::_tstring> GetReportNames(bool bIncludeHidden) const;
   virtual CReportDescription GetReportDescription(LPCTSTR strReportName);
   virtual CReportDescription GetReportDescription(const std::_tstring& strReportName);
   virtual const CBitmap* GetMenuBitmap(LPCTSTR strReportName);
   virtual const CBitmap* GetMenuBitmap(const std::_tstring& strReportName);
   virtual boost::shared_ptr<CReportSpecificationBuilder> GetReportSpecificationBuilder(LPCTSTR strReportName);
   virtual boost::shared_ptr<CReportSpecificationBuilder> GetReportSpecificationBuilder(const std::_tstring& strReportName);
   virtual boost::shared_ptr<CReportSpecificationBuilder> GetReportSpecificationBuilder(const CReportDescription& rptDesc);
   virtual boost::shared_ptr<CReportBrowser> CreateReportBrowser(HWND hwndParent,boost::shared_ptr<CReportSpecification>& pRptSpec,boost::shared_ptr<CReportSpecificationBuilder>& pRptSpecBuilder);
   virtual INT_PTR DisplayReportDialog(DWORD flags,boost::shared_ptr<CReportSpecification>& pRptSpec,boost::shared_ptr<CReportSpecificationBuilder>& pRptSpecBuilder);
};

