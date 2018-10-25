///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
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
// FavoriteReportsPage.cpp : implementation file
//

#include "stdafx.h"
#include "FavoriteReportsPage.h"

#include "ConfigureReportsDlg.h"

// CFavoriteReportsPage dialog

IMPLEMENT_DYNAMIC(CFavoriteReportsPage, CPropertyPage)

CFavoriteReportsPage::CFavoriteReportsPage()
	: CPropertyPage(CFavoriteReportsPage::IDD)
   , m_bShowFavoritesInMenus(FALSE)
{
}

CFavoriteReportsPage::~CFavoriteReportsPage()
{
}

void CFavoriteReportsPage::DoDataExchange(CDataExchange* pDX)
{
   CPropertyPage::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_FAVORITE_LIST, m_FavoritesList);

   if (pDX->m_bSaveAndValidate)
   {
      m_pParentDlg->m_FavoriteReports.clear();
      for (int cnt = 0; cnt <m_FavoritesList.GetCount(); cnt++)
      {
         int chk = m_FavoritesList.GetCheck(cnt);
         TCHAR str[128];
         m_FavoritesList.GetText(cnt, str);
         m_pParentDlg->DealWithFavorite(str, chk!=0); 
      }
   }
   else
   {
      m_FavoritesList.ResetContent();

      std::set<std::_tstring> reports = m_pParentDlg->GetReservedReportNames();
      std::set<std::_tstring>::iterator it = reports.begin();
      while(it != reports.end())
      {
         int cnt = m_FavoritesList.AddString(it->c_str());

         bool isFav = m_pParentDlg->IsFavorite(*it);
         int chk = isFav ? 1 : 0;
         m_FavoritesList.SetCheck( cnt, chk );
         it++;
      }
   }

   DDX_Check(pDX, IDC_CHECK1, m_bShowFavoritesInMenus);
}

BEGIN_MESSAGE_MAP(CFavoriteReportsPage, CPropertyPage)
END_MESSAGE_MAP()

// CFavoriteReportsPage message handlers

BOOL CFavoriteReportsPage::OnInitDialog()
{
   CPropertyPage::OnInitDialog();

   m_FavoritesList.SetCheckStyle( BS_AUTOCHECKBOX );

   return TRUE;  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}



