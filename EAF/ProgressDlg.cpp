///////////////////////////////////////////////////////////////////////
// CORE - Core elements of the Agent-Broker Architecture
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

#include "stdafx.h"
//#include "ProgressDlg.h"
//#include <EAF\EAFProgress.h>
//
//CProgressDlg::CProgressDlg(CWnd* pParent /*=nullptr*/)
//	: CDialog(CProgressDlg::IDD, pParent)
//{
//   m_dwMask = 0;
//   m_bContinue = TRUE;
//	//{{AFX_DATA_INIT(CProgressDlg)
//	m_Message = _T("Working...");
//	//}}AFX_DATA_INIT
//   m_pwndFocus = nullptr;
//   m_pwndCapture = nullptr;
//}
//
//CProgressDlg::~CProgressDlg()
//{
//}
//
//void CProgressDlg::DoDataExchange(CDataExchange* pDX)
//{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState());
//	CDialog::DoDataExchange(pDX);
//	//{{AFX_DATA_MAP(CProgressDlg)
//	DDX_Control(pDX, IDC_ANIMATE, m_Animate);
//	DDX_Control(pDX, IDC_MESSAGE, m_MessageCtrl);
//	DDX_Control(pDX, IDCANCEL, m_Cancel);
//	DDX_Control(pDX, IDC_PROGRESS, m_ProgressBar);
//	DDX_Text(pDX, IDC_MESSAGE, m_Message);
//	//}}AFX_DATA_MAP
//}
//
//void CProgressDlg::GrabInput()
//{
//   // get the windows that currently have the focus and mosue capture
//   m_pwndFocus = GetFocus();
//   m_pwndCapture = GetCapture();
//
//   // set the focus and mouse capture the cancel button
//   // if it is being used, otherwise, to this window
//   if (m_Cancel.IsWindowEnabled())
//   {
//      ASSERT(m_Cancel.IsWindowVisible());
//      m_Cancel.SetFocus();
//      m_Cancel.SetCapture();
//   }
//   else
//   {
//      SetFocus();
//      SetCapture();
//   }
//}
//
//void CProgressDlg::ReleaseInput()
//{
//   // restore the focus and mouse capture
//   if ( m_pwndFocus )
//   {
//      m_pwndFocus->SetFocus();
//   }
//
//   if ( m_pwndCapture )
//   {
//      m_pwndCapture->SetCapture();
//   }
//}
//
//void CProgressDlg::UpdateMessage(LPCTSTR msg)
//{
//   // don't update the message if we are cancelling
//   if ( !m_bContinue )
//      return;
//
//	AFX_MANAGE_STATE(AfxGetStaticModuleState());
//   CWnd* pWnd = GetDlgItem(IDC_MESSAGE);
//   pWnd->SetWindowText(msg);
//   PumpMessage();
//}
//
//BEGIN_MESSAGE_MAP(CProgressDlg, CDialog)
//	//{{AFX_MSG_MAP(CProgressDlg)
//	//}}AFX_MSG_MAP
//END_MESSAGE_MAP()
//
///////////////////////////////////////////////////////////////////////////////
//// CProgressDlg message handlers
//BOOL CProgressDlg::Continue()
//{
//   PumpMessage();
//   return m_bContinue;
//}
//
//void CProgressDlg::ResetContinueState()
//{
//   PumpMessage();
//   m_bContinue = TRUE;
//   m_Cancel.EnableWindow(TRUE);
//}
//
//void CProgressDlg::PumpMessage()
//{
//   AFX_MANAGE_STATE(AfxGetStaticModuleState());
//   MSG msg;
//   while (::PeekMessage(&msg,GetSafeHwnd(),0,0,PM_NOREMOVE) )
//   {
//      AfxGetThread()->PumpMessage();
//   }
//}
//
//void CProgressDlg::OnCancel()
//{
//   AFX_MANAGE_STATE(AfxGetAppModuleState()); // want App state so that the dialog has the correc title
//   if ( AfxMessageBox(_T("Are you sure you want to cancel?"),MB_YESNO | MB_ICONQUESTION) == IDYES )
//   {
//      UpdateMessage(_T("Cancelling..."));
//      m_bContinue = FALSE;
//      m_Cancel.EnableWindow(FALSE); // doesn't need to be enabled any longer
//   }
//
//   // Don't call into the baseclass... the window will be destroyed a bit later
//   //CDialog::OnCancel();
//}
//
//BOOL CProgressDlg::OnInitDialog() 
//{
//   CDialog::OnInitDialog();
//
//   AFX_MANAGE_STATE(AfxGetStaticModuleState());
//   m_Animate.Open(IDR_ANIMATE);
//
//
//   if ( m_dwMask & PW_NOMESSAGE )
//   {
//      m_MessageCtrl.ShowWindow( SW_HIDE );
//   }
//
//   if ( m_dwMask & PW_NOGAUGE )
//   {
//      m_ProgressBar.ShowWindow( SW_HIDE );
//   }
//   
//   if ( m_dwMask & PW_NOCANCEL )
//   {
//      m_Cancel.ShowWindow( SW_HIDE );
//      m_Cancel.EnableWindow(FALSE);
//   }
//
//   return TRUE;  // return TRUE unless you set the focus to a control
//	              // EXCEPTION: OCX Property Pages should return FALSE
//}
