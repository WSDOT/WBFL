///////////////////////////////////////////////////////////////////////
// PGSuper - Prestressed Girder SUPERstructure Design and Analysis
// Copyright © 1999-2016  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Open Source License as 
// published by the Washington State Department of Transportation, 
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but 
// distribution is AS IS, WITHOUT ANY WARRANTY; without even the implied 
// warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See 
// the Alternate Route Open Source License for more details.
//
// You should have received a copy of the Alternate Route Open Source 
// License along with this program; if not, write to the Washington 
// State Department of Transportation, Bridge and Structures Office, 
// P.O. Box  47340, Olympia, WA 98503, USA or e-mail 
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <EAF\EAFCommandLineInfo.h>
#include <EAF\EAFApp.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CEAFCommandLineInfo::CEAFCommandLineInfo() :
CCommandLineInfo(),
m_bUsageMessage(FALSE),
m_bCommandLineMode(FALSE),
m_bError(FALSE),
m_nParams(0)
{
}

CEAFCommandLineInfo::~CEAFCommandLineInfo()
{
}

void CEAFCommandLineInfo::ParseParam(LPCTSTR lpszParam,BOOL bFlag,BOOL bLast)
{
   if ( bFlag && m_nParams == 0 )
   {
      // first param and it is a flag... see if it is /? or /help
      CString strParam(lpszParam);
      if ( strParam.CompareNoCase(_T("?")) == 0 || strParam.CompareNoCase(_T("Help")) == 0 )
      {
         m_bUsageMessage = TRUE;
         m_bCommandLineMode = TRUE;
      }
   }

   CCommandLineInfo::ParseParam(lpszParam,bFlag,bLast);

   m_nParams++;

   // if this is the last parameter and there is only one parameter and it isn't a filename, then go into command line mode.
   // if this is the last parameter and there more than one paramenter and one of the parameters is a filename, go into command line mode
   if ( bLast && (1 == m_nParams && m_nShellCommand != CCommandLineInfo::FileOpen) 
              || (1 <  m_nParams && m_nShellCommand == CCommandLineInfo::FileOpen) 
      )
   {
      m_bCommandLineMode = TRUE;
   }
}

CEAFCommandLineInfo& CEAFCommandLineInfo::operator=(const CEAFCommandLineInfo& other)
{
   m_bUsageMessage    = other.m_bUsageMessage;
   m_bCommandLineMode = other.m_bCommandLineMode;
   m_bError           = other.m_bError;
   m_bShowSplash      = other.m_bShowSplash;
   m_strErrorMsg      = other.m_strErrorMsg;

   return *this;
}

void CEAFCommandLineInfo::SetErrorInfo(LPCTSTR strError)
{
   m_strErrorMsg = strError;
}

CString CEAFCommandLineInfo::GetUsageMessage()
{
   CEAFApp* pApp = EAFGetApp();

   CString strMsg;
   strMsg.Format(_T("Usage:\n%s filename\n%s /?"),pApp->m_pszAppName,pApp->m_pszAppName);
   return strMsg;
}

CString CEAFCommandLineInfo::GetErrorMessage()
{
   CEAFApp* pApp = EAFGetApp();

   CString strMsg;
   if ( m_strErrorMsg.IsEmpty() )
   {
      strMsg.Format(_T("An error occured while starting %s.\n\n%s\n\nRefer to the application documentation for details"),pApp->m_pszAppName,pApp->m_lpCmdLine);
   }
   else
   {
      strMsg.Format(_T("An error occured while starting %s.\n\n%s\n\n%s\n\nRefer to the application documentation for details"),pApp->m_pszAppName,pApp->m_lpCmdLine,m_strErrorMsg);
   }

   return strMsg;
}