///////////////////////////////////////////////////////////////////////
// ReportManagerAgent - Provides report manager as an Agent
// Copyright © 1999-2015  Washington State Department of Transportation
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
   m_RptMgr.ClearAll();
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
void CReportManagerAgent::AddReportBuilder(CReportBuilder* pReportBuilder)
{
   m_RptMgr.AddReportBuilder(pReportBuilder);
}

void CReportManagerAgent::AddReportBuilder(boost::shared_ptr<CReportBuilder>& pReportBuilder)
{
   m_RptMgr.AddReportBuilder(pReportBuilder);
}

CollectionIndexType CReportManagerAgent::GetReportBuilderCount(bool bIncludeHidden) const
{
   return m_RptMgr.GetReportBuilderCount(bIncludeHidden);
}

boost::shared_ptr<CReportBuilder> CReportManagerAgent::GetReportBuilder(LPCTSTR strReportName)
{
   return m_RptMgr.GetReportBuilder(strReportName);
}

boost::shared_ptr<CReportBuilder> CReportManagerAgent::GetReportBuilder(const std::_tstring& strReportName)
{
   return m_RptMgr.GetReportBuilder(strReportName);
}

boost::shared_ptr<CReportBuilder> CReportManagerAgent::RemoveReportBuilder(LPCTSTR strReportName)
{
   return m_RptMgr.RemoveReportBuilder(strReportName);
}

boost::shared_ptr<CReportBuilder> CReportManagerAgent::RemoveReportBuilder(const std::_tstring& strReportName)
{
   return m_RptMgr.RemoveReportBuilder(strReportName);
}

std::vector<std::_tstring> CReportManagerAgent::GetReportNames(bool bIncludeHidden) const
{
   return m_RptMgr.GetReportNames(bIncludeHidden);
}

CReportDescription CReportManagerAgent::GetReportDescription(LPCTSTR strReportName)
{
   return m_RptMgr.GetReportDescription(strReportName);
}

CReportDescription CReportManagerAgent::GetReportDescription(const std::_tstring& strReportName)
{
   return m_RptMgr.GetReportDescription(strReportName);
}

const CBitmap* CReportManagerAgent::GetMenuBitmap(LPCTSTR strReportName)
{
   return m_RptMgr.GetMenuBitmap(strReportName);
}

const CBitmap* CReportManagerAgent::GetMenuBitmap(const std::_tstring& strReportName)
{
   return m_RptMgr.GetMenuBitmap(strReportName);
}

boost::shared_ptr<CReportSpecificationBuilder> CReportManagerAgent::GetReportSpecificationBuilder(LPCTSTR strReportName)
{
   return m_RptMgr.GetReportSpecificationBuilder(strReportName);
}

boost::shared_ptr<CReportSpecificationBuilder> CReportManagerAgent::GetReportSpecificationBuilder(const std::_tstring& strReportName)
{
   return m_RptMgr.GetReportSpecificationBuilder(strReportName);
}

boost::shared_ptr<CReportSpecificationBuilder> CReportManagerAgent::GetReportSpecificationBuilder(const CReportDescription& rptDesc)
{
   return m_RptMgr.GetReportSpecificationBuilder(rptDesc);
}

boost::shared_ptr<CReportBrowser> CReportManagerAgent::CreateReportBrowser(HWND hwndParent,boost::shared_ptr<CReportSpecification>& pRptSpec,boost::shared_ptr<CReportSpecificationBuilder>& pRptSpecBuilder)
{
   return m_RptMgr.CreateReportBrowser(hwndParent,pRptSpec,pRptSpecBuilder);
}

INT_PTR CReportManagerAgent::DisplayReportDialog(DWORD flags,boost::shared_ptr<CReportSpecification>& pRptSpec,boost::shared_ptr<CReportSpecificationBuilder>& pRptSpecBuilder)
{
   return m_RptMgr.DisplayReportDialog(flags,pRptSpec,pRptSpecBuilder);
}
