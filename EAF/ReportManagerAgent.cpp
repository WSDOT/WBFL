///////////////////////////////////////////////////////////////////////
// ReportManagerAgent - Provides report manager as an Agent
// Copyright © 1999-2025  Washington State Department of Transportation
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
#include "ReportManagerAgent.h"
#include "AgentTools.h"

using namespace WBFL::EAF;

bool ReportManagerAgent::RegisterInterfaces()
{
   EAF_AGENT_REGISTER_INTERFACES;
   return REGISTER_INTERFACE(IEAFReportManager);
}

CLSID ReportManagerAgent::GetCLSID() const
{
   return CLSID_ReportManagerAgent;
}

//
// IReportManager
//
void ReportManagerAgent::AddReportBuilder(std::shared_ptr<WBFL::Reporting::ReportBuilder>& pReportBuilder)
{
   m_pRptMgr->AddReportBuilder(pReportBuilder);
}

IndexType ReportManagerAgent::GetReportBuilderCount(bool bIncludeHidden) const
{
   return m_pRptMgr->GetReportBuilderCount(bIncludeHidden);
}

std::shared_ptr<WBFL::Reporting::ReportBuilder> ReportManagerAgent::GetReportBuilder(LPCTSTR strReportName)
{
   return m_pRptMgr->GetReportBuilder(strReportName);
}

std::shared_ptr<WBFL::Reporting::ReportBuilder> ReportManagerAgent::GetReportBuilder(const std::_tstring& strReportName)
{
   return m_pRptMgr->GetReportBuilder(strReportName);
}

std::shared_ptr<WBFL::Reporting::ReportBuilder> ReportManagerAgent::RemoveReportBuilder(LPCTSTR strReportName)
{
   return m_pRptMgr->RemoveReportBuilder(strReportName);
}

std::shared_ptr<WBFL::Reporting::ReportBuilder> ReportManagerAgent::RemoveReportBuilder(const std::_tstring& strReportName)
{
   return m_pRptMgr->RemoveReportBuilder(strReportName);
}

std::vector<std::_tstring> ReportManagerAgent::GetReportNames(bool bIncludeHidden) const
{
   return m_pRptMgr->GetReportNames(bIncludeHidden);
}

WBFL::Reporting::ReportDescription ReportManagerAgent::GetReportDescription(LPCTSTR strReportName)
{
   return m_pRptMgr->GetReportDescription(strReportName);
}

WBFL::Reporting::ReportDescription ReportManagerAgent::GetReportDescription(const std::_tstring& strReportName)
{
   return m_pRptMgr->GetReportDescription(strReportName);
}

const CBitmap* ReportManagerAgent::GetMenuBitmap(LPCTSTR strReportName)
{
   return m_pRptMgr->GetMenuBitmap(strReportName);
}

const CBitmap* ReportManagerAgent::GetMenuBitmap(const std::_tstring& strReportName)
{
   return m_pRptMgr->GetMenuBitmap(strReportName);
}

std::shared_ptr<WBFL::Reporting::ReportSpecificationBuilder> ReportManagerAgent::GetReportSpecificationBuilder(LPCTSTR strReportName)
{
   return m_pRptMgr->GetReportSpecificationBuilder(strReportName);
}

std::shared_ptr<WBFL::Reporting::ReportSpecificationBuilder> ReportManagerAgent::GetReportSpecificationBuilder(const std::_tstring& strReportName)
{
   return m_pRptMgr->GetReportSpecificationBuilder(strReportName);
}

std::shared_ptr<WBFL::Reporting::ReportSpecificationBuilder> ReportManagerAgent::GetReportSpecificationBuilder(const WBFL::Reporting::ReportDescription& rptDesc)
{
   return m_pRptMgr->GetReportSpecificationBuilder(rptDesc);
}

void ReportManagerAgent::SetReportBrowserType(WBFL::Reporting::ReportBrowser::Type browserType)
{
   m_pRptMgr->SetReportBrowserType(browserType);
}

WBFL::Reporting::ReportBrowser::Type ReportManagerAgent::GetReportBrowserType() const
{
   return m_pRptMgr->GetReportBrowserType();
}

std::shared_ptr<WBFL::Reporting::ReportBrowser> ReportManagerAgent::CreateReportBrowser(HWND hwndParent, DWORD dwStyle, const std::shared_ptr<WBFL::Reporting::ReportSpecification>& pRptSpec, const std::shared_ptr<const WBFL::Reporting::ReportSpecificationBuilder>& pRptSpecBuilder)
{
   return m_pRptMgr->CreateReportBrowser(hwndParent, dwStyle, pRptSpec, pRptSpecBuilder);
}

INT_PTR ReportManagerAgent::DisplayReportDialog(DWORD flags, const std::shared_ptr<WBFL::Reporting::ReportSpecification>& pRptSpec, const std::shared_ptr<const WBFL::Reporting::ReportSpecificationBuilder>& pRptSpecBuilder)
{
   return m_pRptMgr->DisplayReportDialog(flags,pRptSpec,pRptSpecBuilder);
}
