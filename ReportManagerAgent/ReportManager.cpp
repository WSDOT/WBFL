///////////////////////////////////////////////////////////////////////
// ReportManagerAgent - Provides report manager as an Agent
// Copyright (C) 1999  Washington State Department of Transportation
//                     Bridge and Structures Office
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

// ReportManager.cpp : Implementation of CReportManager
#include "stdafx.h"
#include "WBFLReportManagerAgent.h"
#include "ReportManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CReportManager

//
// IAgentEx
//
STDMETHODIMP CReportManager::SetBroker(IBroker* pBroker)
{
   m_pBroker = pBroker;
   return S_OK;
}

STDMETHODIMP CReportManager::RegInterfaces()
{
   CComQIPtr<IBrokerInitEx2,&IID_IBrokerInitEx2> pBrokerInit(m_pBroker);

   pBrokerInit->RegInterface(IID_IReportManager,this);

   return S_OK;
}

STDMETHODIMP CReportManager::Init()
{
   return S_OK;
}

STDMETHODIMP CReportManager::Init2()
{
   return S_OK;
}

STDMETHODIMP CReportManager::Reset()
{
   return S_OK;
}

STDMETHODIMP CReportManager::ShutDown()
{
   m_RptMgr.ClearAll();
   return S_OK;
}

STDMETHODIMP CReportManager::GetClassID(CLSID* pCLSID)
{
   *pCLSID = CLSID_ReportManager;
   return S_OK;
}

//
// IReportManager
//
void CReportManager::AddReportBuilder(CReportBuilder* pReportBuilder)
{
   m_RptMgr.AddReportBuilder(pReportBuilder);
}

Uint32 CReportManager::GetReportBuilderCount(bool bIncludeHidden) const
{
   return m_RptMgr.GetReportBuilderCount(bIncludeHidden);
}

boost::shared_ptr<CReportBuilder> CReportManager::GetReportBuilder(const char* strReportName)
{
   return m_RptMgr.GetReportBuilder(strReportName);
}

boost::shared_ptr<CReportBuilder> CReportManager::GetReportBuilder(const std::string& strReportName)
{
   return m_RptMgr.GetReportBuilder(strReportName);
}

std::vector<std::string> CReportManager::GetReportNames(bool bIncludeHidden) const
{
   return m_RptMgr.GetReportNames(bIncludeHidden);
}

CReportDescription CReportManager::GetReportDescription(const char* strReportName)
{
   return m_RptMgr.GetReportDescription(strReportName);
}

CReportDescription CReportManager::GetReportDescription(const std::string& strReportName)
{
   return m_RptMgr.GetReportDescription(strReportName);
}

boost::shared_ptr<CReportSpecificationBuilder> CReportManager::GetReportSpecificationBuilder(const char* strReportName)
{
   return m_RptMgr.GetReportSpecificationBuilder(strReportName);
}

boost::shared_ptr<CReportSpecificationBuilder> CReportManager::GetReportSpecificationBuilder(const std::string& strReportName)
{
   return m_RptMgr.GetReportSpecificationBuilder(strReportName);
}

boost::shared_ptr<CReportSpecificationBuilder> CReportManager::GetReportSpecificationBuilder(const CReportDescription& rptDesc)
{
   return m_RptMgr.GetReportSpecificationBuilder(rptDesc);
}

boost::shared_ptr<CReportBrowser> CReportManager::CreateReportBrowser(HWND hwndParent,boost::shared_ptr<CReportSpecification>& pRptSpec)
{
   return m_RptMgr.CreateReportBrowser(hwndParent,pRptSpec);
}

Int16 CReportManager::DisplayReportDialog(DWORD flags,boost::shared_ptr<CReportSpecification>& pRptSpec)
{
   return m_RptMgr.DisplayReportDialog(flags,pRptSpec);
}
