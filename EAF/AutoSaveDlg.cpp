///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2022  Washington State Department of Transportation
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

// AutoSaveDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "AutoSaveDlg.h"


// CAutoSaveDlg dialog

IMPLEMENT_DYNAMIC(CAutoSaveDlg, CDialog)

CAutoSaveDlg::CAutoSaveDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_AUTOSAVE, pParent)
{

}

CAutoSaveDlg::~CAutoSaveDlg()
{
}

void CAutoSaveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
   DDX_Check(pDX, IDC_ENABLE, bEnabled);
   DDX_Text(pDX, IDC_INTERVAL, interval);

   if (bEnabled)
   {
      DDV_MinMaxInt(pDX, interval, 1, 60);
   }
}


BEGIN_MESSAGE_MAP(CAutoSaveDlg, CDialog)
   ON_BN_CLICKED(IDC_ENABLE, &CAutoSaveDlg::OnBnClickedEnable)
END_MESSAGE_MAP()


// CAutoSaveDlg message handlers


void CAutoSaveDlg::OnBnClickedEnable()
{
   // TODO: Add your control notification handler code here
   int sw = IsDlgButtonChecked(IDC_ENABLE) == BST_CHECKED ? SW_SHOW : SW_HIDE;
   GetDlgItem(IDC_INTERVAL_LABEL)->ShowWindow(sw);
   GetDlgItem(IDC_INTERVAL)->ShowWindow(sw);
   GetDlgItem(IDC_INTERVAL_UNITS)->ShowWindow(sw);
}


BOOL CAutoSaveDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   // TODO:  Add extra initialization here
   OnBnClickedEnable();

   return TRUE;  // return TRUE unless you set the focus to a control
                 // EXCEPTION: OCX Property Pages should return FALSE
}
