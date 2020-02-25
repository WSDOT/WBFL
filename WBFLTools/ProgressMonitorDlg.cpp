///////////////////////////////////////////////////////////////////////
// WBFLTools - Utility Tools for the WBFL
// Copyright © 1999-2020  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Library Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// ProgressMonitorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "wbfltools.h"
#include "ProgressMonitorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProgressMonitorDlg dialog


CProgressMonitorDlg::CProgressMonitorDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(CProgressMonitorDlg::IDD, pParent),
     m_WasCancelled(VARIANT_FALSE),
     m_HasCancel(VARIANT_TRUE),
     m_HasGauge(VARIANT_TRUE)
{
	//{{AFX_DATA_INIT(CProgressMonitorDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CProgressMonitorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProgressMonitorDlg)
	DDX_Control(pDX, IDC_PROGRESS1, m_ProgressCtrl);
	DDX_Control(pDX, IDC_MESSAGE, m_MessageCtl);
	DDX_Control(pDX, IDC_CANCEL_PROGRESS, m_CancelBtn);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProgressMonitorDlg, CDialog)
	//{{AFX_MSG_MAP(CProgressMonitorDlg)
	ON_BN_CLICKED(IDCANCEL, OnCancelProgress)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_CANCEL_PROGRESS, OnCancelProgress)
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProgressMonitorDlg message handlers

void CProgressMonitorDlg::OnCancelProgress() 
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

   if (m_HasCancel!=VARIANT_FALSE)
   {
	   m_WasCancelled = VARIANT_TRUE;
      // set state to true because button push may not displayed due to slow message pumping
      m_CancelBtn.SetState( TRUE );
   }
}

BOOL CProgressMonitorDlg::OnInitDialog() 
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CDialog::OnInitDialog();

   CWnd* pParent = GetParent();
   if ( pParent && pParent->GetSafeHwnd() )
   {
      ::EnableWindow(pParent->GetSafeHwnd(),FALSE);
   }
   else
   {
   // disable the main window to keep users from using the app while we are working
      // for some reason, only the first call to this function succeeds. 
      // later calls fail so...
   	AFX_MANAGE_STATE(AfxGetAppModuleState());

      CWnd* pwnd = ::AfxGetMainWnd();
      ::EnableWindow(pwnd->GetSafeHwnd(), FALSE);
   }


   // set range of progress control
   if (m_HasGauge!=VARIANT_FALSE)
   {
      m_ProgressCtrl.SetRange(0, 100);
   }
   else
   {
      m_ProgressCtrl.ShowWindow(SW_HIDE);
   }

   // set up cancel control
   if (m_HasCancel==VARIANT_FALSE)
      m_CancelBtn.ShowWindow(SW_HIDE);

   // not cancelled yet
	m_WasCancelled = VARIANT_FALSE;

   // set cursor to waiting
   m_Cursor = LoadCursor(nullptr, IDC_APPSTARTING);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CProgressMonitorDlg::OnDestroy() 
{
   // re-enable the main application window
   CWnd* pParent = GetParent();
   if ( pParent && pParent->GetSafeHwnd() )
   {
      ::EnableWindow(pParent->GetSafeHwnd(),TRUE);
      ::SetActiveWindow(pParent->GetSafeHwnd());
   }
   else
   {
   	AFX_MANAGE_STATE(AfxGetAppModuleState());

      CWnd* pwnd = ::AfxGetMainWnd();
      ::EnableWindow(pwnd->GetSafeHwnd(),TRUE);
      ::SetActiveWindow(pwnd->GetSafeHwnd());
   }

	CDialog::OnDestroy();
}

void CProgressMonitorDlg::PumpMessage()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
   MSG msg;
   while (::PeekMessage(&msg,0,0,0,PM_NOREMOVE) )
   {
      AfxGetThread()->PumpMessage();
   }
}

void CProgressMonitorDlg::SetMessage(BSTR msg)
{

   CString csmsg(msg);
   m_MessageCtl.SetWindowText(csmsg);

}

void CProgressMonitorDlg::SetProgressValue(long val)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

   ATLASSERT(val>=0);
   ATLASSERT(val<101);

   if (m_HasGauge!=VARIANT_FALSE)
   {
      m_ProgressCtrl.SetPos(val);
   }
}


BOOL CProgressMonitorDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

   if (nHitTest== HTCLIENT)
   {
      SetCursor(m_Cursor);
      return TRUE;
   }

	return CDialog::OnSetCursor(pWnd, nHitTest, message);
}

void CProgressMonitorDlg::Close()
{
   AFX_MANAGE_STATE(AfxGetStaticModuleState());
   m_HasCancel = VARIANT_TRUE;
   m_CancelBtn.SetWindowText(_T("Close"));
   m_CancelBtn.ShowWindow(SW_SHOW);
   m_Cursor = LoadCursor(nullptr,IDC_ARROW); // set cursor to normal arrow
}