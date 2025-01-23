///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
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
// ConfigureReportsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ConfigureReportsDlg.h"

#include <AgentTools.h>
#include <IReportManager.h>
#include <EAF\EAFBrokerDocument.h>

#include <iterator>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// CConfigureReportsDlg

IMPLEMENT_DYNAMIC(CConfigureReportsDlg, CPropertySheet)

CConfigureReportsDlg::CConfigureReportsDlg(BOOL bFavoriteReports, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(_T("Configure Reports"), pParentWnd, iSelectPage)
{
   Init(bFavoriteReports);
}

CConfigureReportsDlg::~CConfigureReportsDlg()
{
}


BEGIN_MESSAGE_MAP(CConfigureReportsDlg, CPropertySheet)
   ON_COMMAND(ID_HELP, &CConfigureReportsDlg::OnHelp)
END_MESSAGE_MAP()


// CConfigureReportsDlg message handlers

void CConfigureReportsDlg::Init(BOOL bFavoriteReports)
{
   // Turn on help for the property sheet
   m_psh.dwFlags |= PSH_HASHELP | PSH_NOAPPLYNOW;

   m_FavoriteReportsPage.m_psp.dwFlags  |= PSP_HASHELP;
   m_CustomReportsPage.m_psp.dwFlags    |= PSP_HASHELP;

   m_FavoriteReportsPage.m_pParentDlg = this;
   m_CustomReportsPage.m_pParentDlg = this;

   if ( bFavoriteReports )
   {
      AddPage(&m_FavoriteReportsPage);
   }

   AddPage(&m_CustomReportsPage);
}

BOOL CConfigureReportsDlg::OnInitDialog()
{
   // Build list of built-in reports
   GET_IFACE(IReportManager,pReportMgr);
   std::vector<std::_tstring> rptNames = pReportMgr->GetReportNames();

   CEAFCustomReport stub;
   std::vector<std::_tstring>::const_iterator it = rptNames.begin();
   while (it != rptNames.end())
   {
      // Report is built in if it is not a custom report
      stub.m_ReportName = *it;
      CEAFCustomReports::ReportConstIterator itc = m_CustomReports.m_Reports.find(stub);
      if (itc == m_CustomReports.m_Reports.end())
      {
         m_BuiltInReports.insert(*it);
      }

      it++;
   }

   BOOL bResult = CPropertySheet::OnInitDialog();

   return bResult;
}

void CConfigureReportsDlg::SetFavorites(const std::vector<std::_tstring>& FavoriteReports)
{
   m_FavoriteReports.clear();
   std::copy(FavoriteReports.begin(), FavoriteReports.end(), std::inserter(m_FavoriteReports, m_FavoriteReports.end()));
}

std::vector<std::_tstring> CConfigureReportsDlg::GetFavorites()
{
   std::vector<std::_tstring> tmp;
   std::copy(m_FavoriteReports.begin(), m_FavoriteReports.end(), std::back_inserter(tmp));
   return tmp;
}

bool CConfigureReportsDlg::IsFavorite(const std::_tstring& rReportName)
{
   return m_FavoriteReports.end() != m_FavoriteReports.find(rReportName);
}

void CConfigureReportsDlg::DealWithFavorite(const std::_tstring& name, bool isFavorite)
{
   std::set<std::_tstring> ::iterator itf = m_FavoriteReports.find(name);
   bool isFound = m_FavoriteReports.end() != itf; 
   if (isFavorite)
   {
      if (!isFound)
      {
         m_FavoriteReports.insert(name);
      }
   }
   else
   {
      if (isFound)
      {
         m_FavoriteReports.erase(itf);
      }
   }
}

std::set<std::_tstring> CConfigureReportsDlg::GetReservedReportNames()
{
   std::set<std::_tstring> reserved;
   // first built-ins
   std::copy(m_BuiltInReports.begin(), m_BuiltInReports.end(), std::inserter(reserved, reserved.end()));

   // current customs
   CEAFCustomReports::ReportConstIterator itc = m_CustomReports.m_Reports.begin();
   while (itc != m_CustomReports.m_Reports.end())
   {
      reserved.insert(itc->m_ReportName);
      itc++;
   }

   return reserved;
}

void CConfigureReportsDlg::OnHelp()
{
   CEAFMainFrame* pFrame = EAFGetMainFrame();
   CEAFDocument* pDoc = pFrame->GetDocument();

   if ( pDoc && pDoc->IsKindOf(RUNTIME_CLASS(CEAFBrokerDocument)) )
   {
      CEAFBrokerDocument* pBrokerDoc = (CEAFBrokerDocument*)pDoc;

      eafTypes::CustomReportHelp helpType = (0 == GetActiveIndex()) ? eafTypes::crhFavoriteReport : eafTypes::crhCustomReport;

      pBrokerDoc->ShowCustomReportHelp(helpType);
   }
   else
      ATLASSERT(false);
}
