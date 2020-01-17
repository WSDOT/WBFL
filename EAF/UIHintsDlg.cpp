///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2020  Washington State Department of Transportation
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

// UIHintsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UIHintsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUIHintsDlg dialog

IMPLEMENT_DYNAMIC(CUIHintsDlg, CDialog)


CUIHintsDlg::CUIHintsDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(CUIHintsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUIHintsDlg)
	m_strText = _T("");
	m_bDontShowAgain = FALSE;
	//}}AFX_DATA_INIT
}


CUIHintsDlg::~CUIHintsDlg()
{
}

void CUIHintsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUIHintsDlg)
	DDX_Text(pDX, IDC_TEXT, m_strText);
	DDX_Check(pDX, IDC_DONTSHOWAGAIN, m_bDontShowAgain);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUIHintsDlg, CDialog)
	//{{AFX_MSG_MAP(CUIHintsDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUIHintsDlg message handlers

BOOL CUIHintsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
   SetWindowText(m_strTitle); // sets the title bar text
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
