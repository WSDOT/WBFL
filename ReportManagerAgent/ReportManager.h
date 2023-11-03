///////////////////////////////////////////////////////////////////////
// ReportManagerAgent - Provides report manager as an Agent
// Copyright © 1999-2024  Washington State Department of Transportation
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
class ATL_NO_VTABLE CReportManagerAgent : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CReportManagerAgent, &CLSID_ReportManagerAgent>,
   public IAgentEx,
	public IReportManager
{
public:
	CReportManagerAgent()
	{
      m_pRptMgr = WBFL::Reporting::ReportBuilderManager::Create();
	}

DECLARE_REGISTRY_RESOURCEID(IDR_REPORTMANAGER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CReportManagerAgent)
	COM_INTERFACE_ENTRY(IAgent)
	COM_INTERFACE_ENTRY(IAgentEx)
	COM_INTERFACE_ENTRY(IReportManager)
END_COM_MAP()

private:
   std::shared_ptr<WBFL::Reporting::ReportBuilderManager> m_pRptMgr;
   IBroker* m_pBroker; // weak reference

// IAgentEx
public:
   STDMETHOD(SetBroker)(/*[in]*/ IBroker* pBroker) override;
   STDMETHOD(RegInterfaces)() override;
	STDMETHOD(Init)() override;
	STDMETHOD(Init2)() override;
	STDMETHOD(Reset)() override;
	STDMETHOD(ShutDown)() override;
   STDMETHOD(GetClassID)(CLSID* pCLSID) override;


// IReportManager
public:
   virtual void AddReportBuilder(std::shared_ptr<WBFL::Reporting::ReportBuilder>& pReportBuilder) override;
   virtual IndexType GetReportBuilderCount(bool bIncludeHidden) const override;
   virtual std::shared_ptr<WBFL::Reporting::ReportBuilder> GetReportBuilder(LPCTSTR strReportName) override;
   virtual std::shared_ptr<WBFL::Reporting::ReportBuilder> GetReportBuilder(const std::_tstring& strReportName) override;
   virtual std::shared_ptr<WBFL::Reporting::ReportBuilder> RemoveReportBuilder(LPCTSTR strReportName) override;
   virtual std::shared_ptr<WBFL::Reporting::ReportBuilder> RemoveReportBuilder(const std::_tstring& strReportName) override;
   virtual std::vector<std::_tstring> GetReportNames(bool bIncludeHidden) const override;
   virtual WBFL::Reporting::ReportDescription GetReportDescription(LPCTSTR strReportName) override;
   virtual WBFL::Reporting::ReportDescription GetReportDescription(const std::_tstring& strReportName) override;
   virtual const CBitmap* GetMenuBitmap(LPCTSTR strReportName) override;
   virtual const CBitmap* GetMenuBitmap(const std::_tstring& strReportName) override;
   virtual std::shared_ptr<WBFL::Reporting::ReportSpecificationBuilder> GetReportSpecificationBuilder(LPCTSTR strReportName) override;
   virtual std::shared_ptr<WBFL::Reporting::ReportSpecificationBuilder> GetReportSpecificationBuilder(const std::_tstring& strReportName) override;
   virtual std::shared_ptr<WBFL::Reporting::ReportSpecificationBuilder> GetReportSpecificationBuilder(const WBFL::Reporting::ReportDescription& rptDesc) override;
   virtual void SetReportBrowserType(WBFL::Reporting::ReportBrowser::Type browserType) override;
   virtual std::shared_ptr<WBFL::Reporting::ReportBrowser> CreateReportBrowser(HWND hwndParent, DWORD dwStyle, const std::shared_ptr<WBFL::Reporting::ReportSpecification>& pRptSpec, const std::shared_ptr<const WBFL::Reporting::ReportSpecificationBuilder>& pRptSpecBuilder) override;
   virtual INT_PTR DisplayReportDialog(DWORD flags, const std::shared_ptr<WBFL::Reporting::ReportSpecification>& pRptSpec, const std::shared_ptr<const WBFL::Reporting::ReportSpecificationBuilder>& pRptSpecBuilder) override;
};

