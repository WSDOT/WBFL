///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2021  Washington State Department of Transportation
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
// CConfigureReportsDlg

#pragma once

#include "FavoriteReportsPage.h"
#include "CustomReportsPage.h"

interface IBroker;

class CConfigureReportsDlg : public CPropertySheet
{
	DECLARE_DYNAMIC(CConfigureReportsDlg)

   friend CFavoriteReportsPage;
   friend CCustomReportsPage;

public:
	CConfigureReportsDlg(BOOL bFavoriteReports, CWnd* pParentWnd = nullptr, UINT iSelectPage = 0);
	virtual ~CConfigureReportsDlg();

protected:
	DECLARE_MESSAGE_MAP()

   virtual BOOL OnInitDialog() override;

   void Init(BOOL bFavoriteReports);

public:
   void SetFavorites(const std::vector<std::_tstring>& favoriteReports);
   std::vector<std::_tstring> GetFavorites();
   bool IsFavorite(const std::_tstring& rReport);
   // Set favorite from UI
   void DealWithFavorite(const std::_tstring& name, bool isFavorite);

   // return a list of report names that are already taken
   std::set<std::_tstring> GetReservedReportNames();

   CFavoriteReportsPage m_FavoriteReportsPage;
   CCustomReportsPage m_CustomReportsPage;
   IBroker* m_pBroker;

   CEAFCustomReports m_CustomReports;

   std::set<std::_tstring> m_BuiltInReports; // built in reports, not including customs

private:
   std::set<std::_tstring> m_FavoriteReports;

public:
   afx_msg void OnHelp();
};


