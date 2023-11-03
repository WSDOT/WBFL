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

// ReportManager.cpp : Implementation of CReportManagerAgent
#include "stdafx.h"
#include "WBFLReportManagerAgent.h"
#include "ReportManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CReportManagerAgent

//
// IAgentEx
//
STDMETHODIMP CReportManagerAgent::SetBroker(IBroker* pBroker)
{
   m_pBroker = pBroker;
   return S_OK;
}

STDMETHODIMP CReportManagerAgent::RegInterfaces()
{
   CComQIPtr<IBrokerInitEx2,&IID_IBrokerInitEx2> pBrokerInit(m_pBroker);

   pBrokerInit->RegInterface(IID_IReportManager,this);

   return S_OK;
}

STDMETHODIMP CReportManagerAgent::Init()
{
   return S_OK;
}

STDMETHODIMP CReportManagerAgent::Init2()
{
   return S_OK;
}

STDMETHODIMP CReportManagerAgent::Reset()
{
   return S_OK;
}

STDMETHODIMP CReportManagerAgent::ShutDown()
{
   m_pRptMgr->ClearAll();
   return S_OK;
}

STDMETHODIMP CReportManagerAgent::GetClassID(CLSID* pCLSID)
{
   *pCLSID = CLSID_ReportManagerAgent;
   return S_OK;
}

//
// IReportManager
//
void CReportManagerAgent::AddReportBuilder(std::shared_ptr<WBFL::Reporting::ReportBuilder>& pReportBuilder)
{
   m_pRptMgr->AddReportBuilder(pReportBuilder);
}

IndexType CReportManagerAgent::GetReportBuilderCount(bool bIncludeHidden) const
{
   return m_pRptMgr->GetReportBuilderCount(bIncludeHidden);
}

std::shared_ptr<WBFL::Reporting::ReportBuilder> CReportManagerAgent::GetReportBuilder(LPCTSTR strReportName)
{
   return m_pRptMgr->GetReportBuilder(strReportName);
}

std::shared_ptr<WBFL::Reporting::ReportBuilder> CReportManagerAgent::GetReportBuilder(const std::_tstring& strReportName)
{
   return m_pRptMgr->GetReportBuilder(strReportName);
}

std::shared_ptr<WBFL::Reporting::ReportBuilder> CReportManagerAgent::RemoveReportBuilder(LPCTSTR strReportName)
{
   return m_pRptMgr->RemoveReportBuilder(strReportName);
}

std::shared_ptr<WBFL::Reporting::ReportBuilder> CReportManagerAgent::RemoveReportBuilder(const std::_tstring& strReportName)
{
   return m_pRptMgr->RemoveReportBuilder(strReportName);
}

std::vector<std::_tstring> CReportManagerAgent::GetReportNames(bool bIncludeHidden) const
{
   return m_pRptMgr->GetReportNames(bIncludeHidden);
}

WBFL::Reporting::ReportDescription CReportManagerAgent::GetReportDescription(LPCTSTR strReportName)
{
   return m_pRptMgr->GetReportDescription(strReportName);
}

WBFL::Reporting::ReportDescription CReportManagerAgent::GetReportDescription(const std::_tstring& strReportName)
{
   return m_pRptMgr->GetReportDescription(strReportName);
}

const CBitmap* CReportManagerAgent::GetMenuBitmap(LPCTSTR strReportName)
{
   return m_pRptMgr->GetMenuBitmap(strReportName);
}

const CBitmap* CReportManagerAgent::GetMenuBitmap(const std::_tstring& strReportName)
{
   return m_pRptMgr->GetMenuBitmap(strReportName);
}

std::shared_ptr<WBFL::Reporting::ReportSpecificationBuilder> CReportManagerAgent::GetReportSpecificationBuilder(LPCTSTR strReportName)
{
   return m_pRptMgr->GetReportSpecificationBuilder(strReportName);
}

std::shared_ptr<WBFL::Reporting::ReportSpecificationBuilder> CReportManagerAgent::GetReportSpecificationBuilder(const std::_tstring& strReportName)
{
   return m_pRptMgr->GetReportSpecificationBuilder(strReportName);
}

std::shared_ptr<WBFL::Reporting::ReportSpecificationBuilder> CReportManagerAgent::GetReportSpecificationBuilder(const WBFL::Reporting::ReportDescription& rptDesc)
{
   return m_pRptMgr->GetReportSpecificationBuilder(rptDesc);
}

void CReportManagerAgent::SetReportBrowserType(WBFL::Reporting::ReportBrowser::Type browserType)
{
   m_pRptMgr->SetReportBrowserType(browserType);
}

std::shared_ptr<WBFL::Reporting::ReportBrowser> CReportManagerAgent::CreateReportBrowser(HWND hwndParent, DWORD dwStyle, const std::shared_ptr<WBFL::Reporting::ReportSpecification>& pRptSpec, const std::shared_ptr<const WBFL::Reporting::ReportSpecificationBuilder>& pRptSpecBuilder)
{
   return m_pRptMgr->CreateReportBrowser(hwndParent, dwStyle, pRptSpec, pRptSpecBuilder);
}

INT_PTR CReportManagerAgent::DisplayReportDialog(DWORD flags, const std::shared_ptr<WBFL::Reporting::ReportSpecification>& pRptSpec, const std::shared_ptr<const WBFL::Reporting::ReportSpecificationBuilder>& pRptSpecBuilder)
{
   return m_pRptMgr->DisplayReportDialog(flags,pRptSpec,pRptSpecBuilder);
}
