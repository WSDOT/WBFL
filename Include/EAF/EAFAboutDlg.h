///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2017  Washington State Department of Transportation
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

#pragma once

#include <EAF\EAFExp.h>

// CEAFAboutDlg dialog

class EAFCLASS CEAFAboutDlg : public CDialog
{
	DECLARE_DYNAMIC(CEAFAboutDlg)

public:
   CEAFAboutDlg(HICON hIcon = nullptr,UINT nIDTemplate=0,CWnd* pParent = nullptr);   // standard constructor
	virtual ~CEAFAboutDlg();

protected:
	virtual void DoDataExchange(CDataExchange* pDX) override;    // DDX/DDV support

   afx_msg void OnAppListSelChanged();
   afx_msg void OnMoreInfo();
   afx_msg HBRUSH OnCtlColor(CDC*, CWnd*, UINT);


   CListBox m_AppList;
   CStatic m_Description;
   HICON m_hIcon;

	DECLARE_MESSAGE_MAP()
public:
   virtual BOOL OnInitDialog() override;
};
