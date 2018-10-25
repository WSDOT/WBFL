///////////////////////////////////////////////////////////////////////
// PGSuper - Prestressed Girder SUPERstructure Design and Analysis
// Copyright © 1999-2010  Washington State Department of Transportation
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
m_CommandLineMode(false),
m_bAbort(false)
{
}

CEAFCommandLineInfo::~CEAFCommandLineInfo()
{
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void CEAFCommandLineInfo::ParseParam(LPCTSTR lpszParam, BOOL bFlag, BOOL bLast)
{
   // this is where special processing would go if we did any
   if ( bFlag )
   {
      m_bAbort = true;
      return;
   }

   BOOL bShowSplash = m_bShowSplash;
   CCommandLineInfo::ParseParam(lpszParam,bFlag,bLast);
   m_bShowSplash = bShowSplash;
}

CString CEAFCommandLineInfo::GetUsageMessage()
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
   CEAFApp* pApp = (CEAFApp*)AfxGetApp();

   CString strMsg;
   strMsg.Format("There was an error with the command line parameters.\n%s\nRefer to the application documentation for details",pApp->m_lpCmdLine);

   return strMsg;
}