///////////////////////////////////////////////////////////////////////
// MfcTools - Extension library for MFC
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
// PrintStatus.cpp : implementation file
//

#include "stdafx.h"
#include <MfcTools\PrintStatus.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern bool bGfxUserAbort;

/////////////////////////////////////////////////////////////////////////////
// CPrintStatus dialog

CPrintStatus::CPrintStatus(CWnd* pParent /*=nullptr*/)
	: CDialog(CPrintStatus::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPrintStatus)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	Create(CPrintStatus::IDD, pParent);      // modeless !
	bGfxUserAbort = false;
}


void CPrintStatus::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPrintStatus)
	DDX_Control(pDX, IDC_PROGRESS1, wndProg);
	DDX_Control(pDX, IDC_ANIMATE1, wndAnima);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPrintStatus, CDialog)
	//{{AFX_MSG_MAP(CPrintStatus)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrintStatus message handlers

BOOL CPrintStatus::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CenterWindow();
	wndAnima.Open(IDR_PRINT);
	wndAnima.Play(0,(UINT)-1,(UINT)-1);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPrintStatus::OnCancel() 
{
	bGfxUserAbort = true;	
	CDialog::OnCancel();
}
