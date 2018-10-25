///////////////////////////////////////////////////////////////////////
// CORE - Core elements of the Agent-Broker Architecture
// Copyright © 1999-2014  Washington State Department of Transportation
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

// SysAgent.cpp : implementation file
//

#include "stdafx.h"
#include <WBFLCore.h>
//#include "Core.h"
#include "SysAgent.h"
#include <System\Time.h>
#include <memory>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSysAgent

CSysAgent::CSysAgent()
{
}

CSysAgent::~CSysAgent()
{
}

HRESULT CSysAgent::FinalConstruct()
{
   m_pBroker = 0;
   m_bEndLines = TRUE;
   m_cProgressRef = 0;
   m_pThread = NULL;
   return S_OK;
}

void CSysAgent::FinalRelease()
{
}

/////////////////////////////////////////////////////////////////////////////
// CSysAgent message handlers

///////////////////////////////////////////////////////////////////////////////////////////////
// IAgent
//
STDMETHODIMP CSysAgent::SetBroker(IBroker* pBroker)
{
   m_pBroker = pBroker;

   return S_OK;
}

STDMETHODIMP CSysAgent::RegInterfaces()
{
   IBrokerInit* pInit;
   IBrokerInitEx* pInitEx;
   if ( SUCCEEDED(m_pBroker->QueryInterface( IID_IBrokerInit, (void**)&pInit) ) )
   {
      pInit->RegInterface(IID_IProgress,this);
      pInit->RegInterface(IID_ILogFile,this);

      pInit->Release();

      return S_OK;
   }
   else if ( SUCCEEDED(m_pBroker->QueryInterface( IID_IBrokerInitEx, (void**)&pInitEx) ) )
   {
      pInitEx->RegInterface(IID_IProgress,this);
      pInitEx->RegInterface(IID_ILogFile,this);

      pInitEx->Release();

      return S_OK;
   }

   return E_FAIL;
}

STDMETHODIMP CSysAgent::Init()
{
   // No special initialization

   return S_OK;
}

STDMETHODIMP CSysAgent::Init2()
{
   // No special initialization

   return S_OK;
}

STDMETHODIMP CSysAgent::Reset()
{
   // No data to reset

   return S_OK;
}

STDMETHODIMP CSysAgent::ShutDown()
{
   // Nothing to do here

   return S_OK;
}

STDMETHODIMP CSysAgent::GetClassID(CLSID* pCLSID)
{
   *pCLSID = CLSID_SysAgent;

   return S_OK;
}


///////////////////////////////////////////////////////////////////////////////////////////////
// IProgress
//
STDMETHODIMP CSysAgent::CreateProgressWindow(DWORD dwMask,UINT nDelay)
{
//   AFX_MANAGE_STATE(AfxGetStaticModuleState());

   m_cProgressRef++;

   if ( m_cProgressRef > 1 )
   {
      //m_ProgressDlg.ResetContinueState();
      m_ProgressMsgMarker.push_back(m_Messages.size());
      return S_OK;
   }

   // Run the progress window in a UI thread
   m_pThread = (CProgressThread*)AfxBeginThread(RUNTIME_CLASS(CProgressThread),THREAD_PRIORITY_NORMAL,0,CREATE_SUSPENDED);
   m_pThread->m_bAutoDelete = TRUE;
   m_pThread->ResumeThread();

   m_pActiveWnd = CWnd::GetActiveWindow();
   CWnd* pMainWnd;
   {
      AFX_MANAGE_STATE(AfxGetAppModuleState());
      pMainWnd = AfxGetMainWnd();
   }

   HRESULT hr = m_pThread->CreateProgressWindow(pMainWnd,dwMask,nDelay);
   ATLASSERT( SUCCEEDED(hr) );
   if ( FAILED(hr) )
   {
      m_cProgressRef--;
      m_pThread->EndThread();
      m_pThread = NULL;
      return PROGRESS_E_CREATE;
   }

   m_ProgressMsgMarker.push_back(0);
   UpdateMessage(_T("Working..."));

   // disable the main window
   pMainWnd->EnableWindow(FALSE);
   return S_OK;
}

STDMETHODIMP CSysAgent::Init(short begin, short end, short inc)
{
   m_pThread->Init(begin,end,inc);
   return S_OK;
}

STDMETHODIMP CSysAgent::Increment()
{
   m_pThread->Increment();
   return S_OK;
}

STDMETHODIMP CSysAgent::UpdateMessage( LPCTSTR msg)
{
   m_Messages.push_back(msg);

   if ( m_pThread )
      m_pThread->UpdateMessage(msg);

   return S_OK;
}

STDMETHODIMP CSysAgent::Continue()
{
   HRESULT hr = S_OK;

   if ( m_pThread )
      return m_pThread->Continue() ? S_OK : S_FALSE;

   return hr;
}

STDMETHODIMP CSysAgent::get_EnableCancel(BOOL* pbEnable)
{
   *pbEnable = m_pThread->EnableCancel();
   return S_OK;
}

STDMETHODIMP CSysAgent::put_EnableCancel(BOOL bEnable)
{
   m_pThread->EnableCancel(bEnable);
   return S_OK;
}

STDMETHODIMP CSysAgent::DestroyProgressWindow()
{
   m_cProgressRef--;
   ATLASSERT( m_cProgressRef >= 0 );

   if ( m_cProgressRef == 0 )
   {
      m_pThread->DestroyProgressWindow();
      m_pThread->EndThread();
      m_pThread = NULL;

      // enable the main window
      {
         AFX_MANAGE_STATE(AfxGetAppModuleState());
         AfxGetMainWnd()->EnableWindow(TRUE);
         if ( m_pActiveWnd )
         {
            m_pActiveWnd->EnableWindow(TRUE);
            m_pActiveWnd->SetActiveWindow();
         }
      }
   }
   else
   {
      m_Messages.erase(m_Messages.begin()+m_ProgressMsgMarker.back(),m_Messages.end());
      m_ProgressMsgMarker.pop_back();
      m_pThread->UpdateMessage(m_Messages.back().c_str());
   }

   return S_OK;
}


///////////////////////////////////////////////////////////////////////////////////////////////
// ILogFile
//
STDMETHODIMP CSysAgent::Open(LPCTSTR name,DWORD* pdwCookie)
{
   // User passed us a bad pointer
   if ( pdwCookie == 0 )
      return E_POINTER;

   // Try to create a stream... Could fail in one of two ways.  Failed allocation could throw
   // and bad_alloc exception or return NULL.
   boost::shared_ptr<std::_tofstream> pofile;
   try
   {
      pofile = boost::shared_ptr<std::_tofstream>( new std::_tofstream(name) );
   }
   catch ( ... )
   {
      return E_OUTOFMEMORY;
   }
   if ( pofile.get() == 0 )
   {
      return E_OUTOFMEMORY;
   }

   // Do we have a good stream?
   if ( !(*pofile) )
      return LOGFILE_E_CANTOPEN;

   // Turn exceptions on for the stream
   pofile->exceptions( std::ios_base::badbit | std::ios_base::failbit | std::ios_base::eofbit );

   // Set buffering off for stream so we get all of our data
   pofile->setf(std::ios_base::unitbuf);

   // Save the stream for future reference
   m_LogFiles.push_back( pofile );

   // Get a cookie
   // This have to come after push_back. Cookie must be > 0.
   *pdwCookie = (DWORD)m_LogFiles.size();

   // Write a little preamble
   sysTime now;
   now.PrintDate( true );
   try
   {
      *pofile << _T("Log opened ") << now << std::endl;
      *pofile << std::endl;
   }
   catch (...)
   {
      return LOGFILE_E_BADWRITE;
   }

   return S_OK;
}

bool is_valid_cookie( DWORD dwCookie, size_t size )
{
   return ( dwCookie > (DWORD)size ) ? false : true;
}

int idx_from_cookie( DWORD dwCookie )
{
   return dwCookie - 1;
}

STDMETHODIMP CSysAgent::put_EndLines(BOOL bEndLines)
{
   m_bEndLines = bEndLines;
   return S_OK;
}

STDMETHODIMP CSysAgent::get_EndLines(BOOL* pbEndLines)
{
   *pbEndLines = m_bEndLines;
   return S_OK;
}

STDMETHODIMP CSysAgent::LogMessage(DWORD dwCookie,LPCTSTR msg)
{
   // Is the cookie valid?
   if ( !is_valid_cookie( dwCookie, m_LogFiles.size() ) )
      return LOGFILE_E_NOLOGFILE;

   boost::shared_ptr<std::_tofstream>& pofile = m_LogFiles[ idx_from_cookie(dwCookie) ];

   try
   {
      *pofile << msg;
      if ( m_bEndLines )
         *pofile << std::endl;
   }
   catch(...)
   {
      return LOGFILE_E_BADWRITE;
   }

   return S_OK;
}

STDMETHODIMP CSysAgent::Close(DWORD dwCookie)
{
   // Is the cookie valid?
   if ( !is_valid_cookie( dwCookie, m_LogFiles.size() ) )
      return LOGFILE_E_NOLOGFILE;

   boost::shared_ptr<std::_tofstream>& pofile = m_LogFiles[ idx_from_cookie(dwCookie) ];

   // Write a little postscript
   sysTime now;
   now.PrintDate( true );
   try
   {
      *pofile << std::endl;
      *pofile << _T("Log closed ") << now << std::endl;
   }
   catch(...)
   {
      return LOGFILE_E_BADWRITE;
   }

   pofile->close();

   return S_OK;
}
