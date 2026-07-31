///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright � 1999-2026  Washington State Department of Transportation
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

// NOTE: See the comment at the top of ProgressDlg.cpp - use AfxGetAppModuleState(),
// never AfxGetAppModuleState().

#include "stdafx.h"
#include <EAF\ProgressWindow.h>
#include "ProgressThread.h"

using namespace WBFL::EAF;

ProgressWindow::ProgressWindow(CWnd* pParentWnd, DWORD dwMask, UINT nDelay)
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());

   m_pThread = (CProgressThread*)AfxBeginThread(RUNTIME_CLASS(CProgressThread));
   ATLASSERT(m_pThread != nullptr);

   HRESULT hr = m_pThread->CreateProgressWindow(pParentWnd, dwMask, nDelay);
   ATLASSERT(SUCCEEDED(hr));
}

ProgressWindow::~ProgressWindow()
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());

   m_pThread->ResetContinueState();
   m_pThread->DestroyProgressWindow();

   m_pThread->PostThreadMessage(WM_KILLTHREAD,0,0);
   DWORD result = ::WaitForSingleObject(m_pThread->m_hThread,10000/*INFINITE*/); // wait for thread to terminate
   if ( result == WAIT_TIMEOUT || result == WAIT_FAILED )
   {
      ATLASSERT(false); // for some reason, the WM_KILLTHREAD message never got to the message handler
      m_pThread->OnKillThread(0,0);
   }
}

void ProgressWindow::Init(short begin, short end, short inc)
{
   m_pThread->Init(begin, end, inc);
}

void ProgressWindow::Increment()
{
   m_pThread->Increment();
}

void ProgressWindow::UpdateMessage(LPCTSTR msg)
{
   m_pThread->UpdateMessage(msg);
}

bool ProgressWindow::Continue()
{
   return m_pThread->Continue() ? true : false;
}
