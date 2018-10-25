// ProgressThread.cpp : implementation file
//

#include "stdafx.h"
#include "ProgressThread.h"
#include <WBFLCore.h>


const UINT g_TimerID = 1;
CWnd* g_pTimerWnd = 0;
void CALLBACK EXPORT TimerProc(HWND hWnd,UINT nMsg,UINT_PTR nIDEvent,DWORD dwTime)
{
   CHECK( g_pTimerWnd != 0 );
   CHECK( g_pTimerWnd->GetSafeHwnd() == hWnd );
   CHECK( nIDEvent == g_TimerID );

   g_pTimerWnd->KillTimer( g_TimerID );
   g_pTimerWnd->ShowWindow( SW_SHOW );
   g_pTimerWnd = 0;
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
   m_bTerminate = FALSE;
	return TRUE;
}

int CProgressThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BOOL CProgressThread::OnIdle(LONG lCount)
{
   if ( m_bTerminate )
      AfxPostQuitMessage(0);

   return FALSE;
}

void CProgressThread::EndThread()
{
   m_bTerminate = TRUE;
}

BEGIN_MESSAGE_MAP(CProgressThread, CWinThread)
END_MESSAGE_MAP()

HRESULT CProgressThread::CreateProgressWindow(CWnd* pParentWnd,DWORD dwMask,UINT nDelay)
{
   AFX_MANAGE_STATE(AfxGetStaticModuleState());

   BOOL bCreated;
   bCreated = m_ProgressDlg.Create( CProgressDlg::IDD, pParentWnd );
   ATLASSERT( bCreated == TRUE );
   if ( !bCreated )
      return PROGRESS_E_CREATE;

   // Make sure the visible flag isn't set in the dialog resource.
   ATLASSERT( m_ProgressDlg.IsWindowVisible() == false );

   if ( dwMask & PW_NOMESSAGE )
      m_ProgressDlg.m_MessageCtrl.ShowWindow( SW_HIDE );

//   if ( dwMask & PW_NOGAUGE ) // Always hide
      m_ProgressDlg.m_ProgressBar.ShowWindow( SW_HIDE );
   
   m_bCancelEnabled = TRUE;
   if ( dwMask & PW_NOCANCEL )
   {
      m_ProgressDlg.m_Cancel.ShowWindow( SW_HIDE );
      m_ProgressDlg.m_Cancel.EnableWindow(FALSE);
      m_bCancelEnabled = FALSE;
   }

   g_pTimerWnd = &(m_ProgressDlg);
   m_ProgressDlg.SetTimer( g_TimerID, nDelay, &TimerProc );
   m_ProgressDlg.PumpMessage();

   return S_OK;
}


// CProgressThread message handlers
void CProgressThread::Init(short begin, short end, short inc)
{
   m_ProgressDlg.PumpMessage();
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

BOOL CProgressThread::EnableCancel()
{
   return m_bCancelEnabled;
}

void CProgressThread::EnableCancel(BOOL bEnable)
{
   m_bCancelEnabled = bEnable;
   m_ProgressDlg.m_Cancel.ShowWindow( bEnable ? SW_SHOW : SW_HIDE );
   m_ProgressDlg.m_Cancel.EnableWindow(bEnable);
}

void CProgressThread::DestroyProgressWindow()
{
   m_ProgressDlg.KillTimer( g_TimerID );
   g_pTimerWnd = 0;

   m_ProgressDlg.DestroyWindow();
}
