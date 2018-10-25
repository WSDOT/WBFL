///////////////////////////////////////////////////////////////////////
// CORE - Core elements of the Agent-Broker Architecture
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

// ProgressDlg.cpp : implementation file
//

#include "stdafx.h"
//#include "core.h"
#include "ProgressDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProgressDlg dialog


CProgressDlg::CProgressDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProgressDlg::IDD, pParent),
   m_hMainWnd(NULL)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
   m_bContinue = TRUE;
	//{{AFX_DATA_INIT(CProgressDlg)
	m_Message = _T("Working...");
	//}}AFX_DATA_INIT
}

CProgressDlg::~CProgressDlg()
{
}

void CProgressDlg::DoDataExchange(CDataExchange* pDX)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProgressDlg)
	DDX_Control(pDX, IDC_ANIMATE, m_Animate);
	DDX_Control(pDX, IDC_MESSAGE, m_MessageCtrl);
	DDX_Control(pDX, IDCANCEL, m_Cancel);
	DDX_Control(pDX, IDC_PROGRESS, m_ProgressBar);
	DDX_Text(pDX, IDC_MESSAGE, m_Message);
	//}}AFX_DATA_MAP
}

void CProgressDlg::UpdateMessage(LPCTSTR msg)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
   CWnd* pWnd = GetDlgItem(IDC_MESSAGE);
   pWnd->SetWindowText(msg);
}

BEGIN_MESSAGE_MAP(CProgressDlg, CDialog)
	//{{AFX_MSG_MAP(CProgressDlg)
	ON_WM_DESTROY()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProgressDlg message handlers
BOOL CProgressDlg::Continue()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
   PumpMessage();
   return m_bContinue;
}

void CProgressDlg::ResetContinueState()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
   PumpMessage();
   m_bContinue = TRUE;
}

void CProgressDlg::PumpMessage()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
   MSG msg;
   while (::PeekMessage(&msg,NULL,NULL,NULL, PM_NOREMOVE) )
   {
      AfxGetThread()->PumpMessage();
   }
}

void CProgressDlg::OnCancel()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
   m_bContinue = FALSE;
   CDialog::OnCancel();
}

BOOL CProgressDlg::OnInitDialog() 
{
   AFX_MANAGE_STATE(AfxGetStaticModuleState());

   CDialog::OnInitDialog();


   //// disable the main window
   //if (m_hMainWnd==0)
   //{
   //   // for some reason, only the first call to this function succeeds. 
   //   // later calls fail so...
   //	AFX_MANAGE_STATE(AfxGetAppModuleState());
   //   CWnd* pwnd = ::AfxGetMainWnd();
   //   CHECK(pwnd!=0);
   //   m_hMainWnd = pwnd->GetSafeHwnd();
   //   CHECK(m_hMainWnd!=0);
   //}

   //::EnableWindow(m_hMainWnd, FALSE);

   m_Animate.Open(IDR_ANIMATE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CProgressDlg::OnDestroy() 
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
   // re-enable the main application window
   //CHECK(m_hMainWnd);
   //::EnableWindow(m_hMainWnd, TRUE);
   //::SetActiveWindow(m_hMainWnd);

	CDialog::OnDestroy();
}

void CProgressDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
   // Gobble up all key down events
	//CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}
