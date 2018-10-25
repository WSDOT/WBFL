///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2016  Washington State Department of Transportation
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
#include <EAF\EAFHelp.h>
#include <EAF\EAFUtilities.h>
#include <EAF\EAFDocument.h>
#include <EAF\EAFBrokerDocument.h>

void EAFHelp(LPCTSTR lpszDocSetName,UINT nHID)
{
   CString strURL;
   eafTypes::HelpResult hr = eafTypes::hrDocSetNotFound; // TRICKY... this default is important, see below

   CEAFDocument* pDoc = EAFGetDocument();
   if ( pDoc )
   {
      // there is an open document so it gets first priority
      hr = pDoc->GetDocumentLocation(lpszDocSetName,nHID,strURL);
   }

   if ( hr == eafTypes::hrDocSetNotFound )
   {
      // hr == eafTypes::hrOK... the document returned a valid URL
      // hr == eafTypes::hrTopicNotFound... the document handles the specified documenation set, but the help id was bad
      // Either way, we don't want to search the application.
      // hr == eafTypes::hrDocSetNotFound is the only reason to continue

      CEAFApp* pApp = EAFGetApp();
      hr = pApp->GetDocumentLocation(lpszDocSetName,nHID,strURL);
   }

   if ( hr == eafTypes::hrOK )
   {
      ::ShellExecute(NULL,_T("open"),strURL, NULL,NULL,SW_SHOWDEFAULT);
   }
   else
   {
      CString strMessage;
      if ( hr == eafTypes::hrDocSetNotFound )
      {
         strMessage.Format(_T("The documentation set %s was not found."),lpszDocSetName);
      }
      else
      {
         strMessage.Format(_T("Help topic %d not found in the %s documentation set."),nHID,lpszDocSetName);
      }
      AfxMessageBox(strMessage,MB_ICONEXCLAMATION | MB_OK);
   }
}


CEAFHelpHandler::CEAFHelpHandler()
{
   m_nHID = 0;
}

CEAFHelpHandler::CEAFHelpHandler(LPCTSTR lpszDocSetName,UINT nHelpID) :
m_strDocSetName(lpszDocSetName),m_nHID(nHelpID)
{
}

void CEAFHelpHandler::Init(LPCTSTR lpszDocSetName,UINT nHelpID)
{
   m_strDocSetName = lpszDocSetName;
   m_nHID = nHelpID;
}

void CEAFHelpHandler::OnHelp()
{
   ATLASSERT( !m_strDocSetName.IsEmpty() ); // did you forget to initlize me?
   ATLASSERT(m_nHID != 0);
   EAFHelp(m_strDocSetName,m_nHID);
}
