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

#include "stdafx.h"
#include "EAFHelpWindowThread.h"
#include "EAFHelpWindow.h"
#include "resource.h"

#include <EAF\EAFApp.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CProgressThread

IMPLEMENT_DYNCREATE(CEAFHelpWindowThread, CWinThread)

CEAFHelpWindowThread::CEAFHelpWindowThread() :
m_Event(FALSE/*default*/,TRUE/*Don't want the event to automatically reset*/,_T("HelpWindowInitialized"))
{
   TRACE0("EAFHelpWindowThread created");
}

CEAFHelpWindowThread::~CEAFHelpWindowThread()
{
   TRACE0("EAFHelpWindowThread destroyed");
}

BOOL CEAFHelpWindowThread::InitInstance()
{
   BOOL bResult = TRUE;
   m_pMainWnd = new CEAFHelpWindow;
   if ( !((CEAFHelpWindow*)m_pMainWnd)->LoadFrame(IDR_HELP,WS_OVERLAPPEDWINDOW) )
   {
      m_pMainWnd = nullptr;
      bResult = FALSE;
   }

   // this must always be called or there where be a deadlock
   m_Event.SetEvent(); // now that this thread has been initialized, we can signal Navigate that it can continue

   TRACE0("EAFHelpWindowThread initialized");
   return bResult;
}

int CEAFHelpWindowThread::ExitInstance()
{
   int result = CWinThread::ExitInstance();
   EAFGetApp()->m_pHelpWindowThread = nullptr;

   TRACE0("EAFHelpWindowThread exiting");

   return result;
}

BEGIN_MESSAGE_MAP(CEAFHelpWindowThread, CWinThread)
   ON_THREAD_MESSAGE(WM_TERMINATE_HELP_WINDOW_THREAD,OnKillThread)
END_MESSAGE_MAP()

void CEAFHelpWindowThread::Navigate(LPCTSTR lpszURL)
{
   ::WaitForSingleObject(m_Event.m_hObject,INFINITE); // wait here until the help window initialization is complete, otherwise *crash*
   if ( m_pMainWnd )
   {
      ((CEAFHelpWindow*)m_pMainWnd)->Navigate(lpszURL);
   }
}

void CEAFHelpWindowThread::OnKillThread(WPARAM wParam,LPARAM lParam)
{
   // close the main window... this will eventually call PostQuitMessage and the thread will terminate
   if ( m_pMainWnd )
   {
      ((CEAFHelpWindow*)m_pMainWnd)->CanClose(TRUE);
      m_pMainWnd->SendMessage(WM_CLOSE);
   }
}
