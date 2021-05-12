///////////////////////////////////////////////////////////////////////
// WBFLTools - Utility Tools for the WBFL
// Copyright © 1999-2021  Washington State Department of Transportation
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
// ProgressThread.cpp : implementation file
//

#include "stdafx.h"
#include "ProgressThread.h"
#include <WBFLCore.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


const UINT g_ShowProgressWndTimerID = 1;
const UINT g_PumpProgressWndTimerID = 2;

CProgressDlg* g_pTimerWnd = 0;

void CALLBACK EXPORT PumpProgressWndTimerProc(HWND hWnd,UINT nMsg,UINT_PTR nIDEvent,DWORD dwTime)
{
   CHECK( g_pTimerWnd != 0 );
   CHECK( g_pTimerWnd->GetSafeHwnd() == hWnd );
   CHECK( nIDEvent == g_PumpProgressWndTimerID );
   g_pTimerWnd->PumpMessage();
}

void CALLBACK EXPORT ShowProgressWndTimerProc(HWND hWnd,UINT nMsg,UINT_PTR nIDEvent,DWORD dwTime)
{
   CHECK( g_pTimerWnd != 0 );
   CHECK( g_pTimerWnd->GetSafeHwnd() == hWnd );
   CHECK( nIDEvent == g_ShowProgressWndTimerID );

   g_pTimerWnd->KillTimer( g_ShowProgressWndTimerID );
   g_pTimerWnd->ShowWindow( SW_SHOW );
   g_pTimerWnd->GrabInput();
   
   // make the progress window pump its message queue every 5 seconds so
   // it doesn't look like the application is stuck
   g_pTimerWnd->SetTimer(g_PumpProgressWndTimerID,5000,&PumpProgressWndTimerProc);
}

// CProgressThread

IMPLEMENT_DYNCREATE(CProgressThread, CWinThread)

CProgressThread::CProgressThread()
{
}

CProgressThread::~CProgressThread()
{
}

BOOL CProgressThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int CProgressThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CProgressThread, CWinThread)
   ON_THREAD_MESSAGE(WM_KILLTHREAD,OnKillThread)
END_MESSAGE_MAP()

void CProgressThread::OnKillThread(WPARAM wParam,LPARAM lParam)
{
   AFX_MANAGE_STATE(AfxGetStaticModuleState());
   AfxPostQuitMessage(0);
}

HRESULT CProgressThread::CreateProgressWindow(CWnd* pParentWnd,DWORD dwMask,UINT nDelay)
{
   AFX_MANAGE_STATE(AfxGetStaticModuleState());

   BOOL bCreated;
   m_ProgressDlg.m_dwMask = dwMask;
   bCreated = m_ProgressDlg.Create( CProgressDlg::IDD, pParentWnd );
   ATLASSERT( bCreated == TRUE );
   if ( !bCreated )
   {
      return PROGRESS_E_CREATE;
   }

   // Make sure the visible flag isn't set in the dialog resource.
   ATLASSERT( m_ProgressDlg.IsWindowVisible() == false );

   g_pTimerWnd = &(m_ProgressDlg);
   m_ProgressDlg.SetTimer( g_ShowProgressWndTimerID, nDelay, &ShowProgressWndTimerProc );
   m_ProgressDlg.PumpMessage();
   
   return S_OK;
}


// CProgressThread message handlers
void CProgressThread::Init(short begin, short end, short inc)
{
   m_ProgressDlg.PumpMessage();
   m_ProgressDlg.m_ProgressBar.ShowWindow( SW_SHOW );
   m_ProgressDlg.m_ProgressBar.SetRange( begin, end );
   m_ProgressDlg.m_ProgressBar.SetStep( inc );
   m_ProgressDlg.m_ProgressBar.SetPos( begin );
}

void CProgressThread::Increment()
{
   m_ProgressDlg.PumpMessage();
   m_ProgressDlg.m_ProgressBar.StepIt();
}

void CProgressThread::UpdateMessage( LPCTSTR msg)
{
   m_ProgressDlg.PumpMessage();
   m_ProgressDlg.m_Message = msg;
   m_ProgressDlg.UpdateMessage(msg);
}

BOOL CProgressThread::Continue()
{
   return m_ProgressDlg.Continue();
}

void CProgressThread::ResetContinueState()
{
   m_ProgressDlg.ResetContinueState();
}

void CProgressThread::DestroyProgressWindow()
{
   AFX_MANAGE_STATE(AfxGetStaticModuleState());
   m_ProgressDlg.KillTimer( g_ShowProgressWndTimerID );
   m_ProgressDlg.KillTimer( g_PumpProgressWndTimerID );
   g_pTimerWnd = 0;
   m_ProgressDlg.ReleaseInput();
   m_ProgressDlg.DestroyWindow();
}
