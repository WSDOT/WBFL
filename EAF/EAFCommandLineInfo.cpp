///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2019  Washington State Department of Transportation
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
m_bTargetApp(FALSE),
m_nParams(0)
{
}

CEAFCommandLineInfo::~CEAFCommandLineInfo()
{
}

void CEAFCommandLineInfo::ParseParam(LPCTSTR lpszParam,BOOL bFlag,BOOL bLast)
{
   CString strParam(lpszParam);
   if ( bFlag && m_nParams == 0 )
   {
      // first param and it is a flag... see if it is /? or /help
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

   if ( strParam.Left(3).CompareNoCase(_T("App")) == 0 )
   {
      // We've encountered the /App=<appname> option
      if ( !m_bTargetApp && m_strTargetApp.IsEmpty() )
      {
         m_bTargetApp = TRUE;
         int length = strParam.GetLength();
         m_strTargetApp = strParam.Right(length - 4); 
         m_bCommandLineMode = TRUE;
      }
   }
}

CEAFCommandLineInfo& CEAFCommandLineInfo::operator=(const CEAFCommandLineInfo& other)
{
   m_bUsageMessage    = other.m_bUsageMessage;
   m_bCommandLineMode = other.m_bCommandLineMode;
   m_bError           = other.m_bError;
   m_bShowSplash      = other.m_bShowSplash;
   m_strErrorMsg      = other.m_strErrorMsg;
   m_bTargetApp       = other.m_bTargetApp;
   m_strTargetApp     = other.m_strTargetApp;

   return *this;
}

void CEAFCommandLineInfo::SetErrorInfo(LPCTSTR strError)
{
   m_strErrorMsg = strError;
}

CString CEAFCommandLineInfo::GetUsageMessage()
{
   CEAFApp* pApp = EAFGetApp();

   CString strCommand1;
   strCommand1.Format(_T("%s filename"),pApp->m_pszAppName);

   CString strCommand2;
   strCommand2.Format(_T("%s <options>"),pApp->m_pszAppName);

   CString strOption1(_T("/? - Get command line options"));
   CString strOption2(_T("/help - Get command line options"));
   CString strOption3(_T("/<app options> filename - Opens the specified file and passes <app options> to the application associated with the file"));
   CString strOption4(_T("/App=<appname> <app options> - Passes <app options> to the application specified with <appname> for processing"));

   CString strMsg;
   strMsg.Format(_T("Usage:\n%s\n%s\n\nwhere <options> are:\n%s\n%s\n%s\n%s"),
      strCommand1,strCommand2,strOption1,strOption2,strOption3,strOption4);

   return strMsg;
}

CString CEAFCommandLineInfo::GetErrorMessage()
{
   CEAFApp* pApp = EAFGetApp();

   CString strMsg;
   if ( m_strErrorMsg.IsEmpty() )
   {
      strMsg.Format(_T("An error occured while starting %s.\n\n%s\n\nThis is likely due to an invalid command line parameter. Try using the /Help parameter to see valid options. Refer to the application documentation for details."),pApp->m_pszAppName,pApp->m_lpCmdLine);
   }
   else
   {
      strMsg.Format(_T("An error occured while starting %s.\n\n%s\n\n%s\n\nThis is likely due to an invalid command line parameter. Try using the /Help parameter to see valid options. Refer to the application documentation for details."),pApp->m_pszAppName,pApp->m_lpCmdLine,m_strErrorMsg);
   }

   return strMsg;
}

CString CEAFCommandLineInfo::GetTargetApp()
{
   return m_strTargetApp;
}
