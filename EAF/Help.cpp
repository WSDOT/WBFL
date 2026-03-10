///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2025  Washington State Department of Transportation
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
#include <EAF\Help.h>
#include <EAF\EAFUtilities.h>
#include <EAF\EAFDocument.h>
#include <EAF\EAFBrokerDocument.h>



void EAFHelp(LPCTSTR lpszDocSetName,UINT nHID)
{
   std::pair<WBFL::EAF::HelpResult, CString> result = { WBFL::EAF::HelpResult::DocSetNotFound,CString() }; // TRICKY... this default is important, see below

   CEAFDocument* pDoc = EAFGetDocument();
   if ( pDoc )
   {
      // there is an open document so it gets first priority
      result = pDoc->GetDocumentLocation(lpszDocSetName,nHID);
   }

   if ( result.first == WBFL::EAF::HelpResult::DocSetNotFound )
   {
      // hr == WBFL::EAF::HelpResult::OK... the document returned a valid URL
      // hr == WBFL::EAF::HelpResult::TopicNotFound... the document handles the specified documentation set, but the help id was bad
      // Either way, we don't want to search the application.
      // hr == WBFL::EAF::HelpResult::DocSetNotFound is the only reason to continue

      CEAFApp* pApp = EAFGetApp();
      result = pApp->GetDocumentLocation(lpszDocSetName,nHID);
   }

   if ( result.first == WBFL::EAF::HelpResult::OK )
   {
      CEAFApp* pApp = EAFGetApp();
      pApp->HelpWindowNavigate(result.second);
   }
   else
   {
      CString strMessage;
      if ( result.first == WBFL::EAF::HelpResult::DocSetNotFound )
      {
         strMessage.Format(_T("The documentation set %s was not found."),lpszDocSetName);
      }
      else
      {
         strMessage.Format(_T("Help topic %d not found in the %s documentation set at %s."),nHID,lpszDocSetName,result.second);
      }
      AfxMessageBox(strMessage,MB_ICONEXCLAMATION | MB_OK);
   }
}

using namespace WBFL::EAF;

HelpHandler::HelpHandler()
{
   m_nHID = 0;
}

HelpHandler::HelpHandler(LPCTSTR lpszDocSetName,UINT nHelpID) :
m_strDocSetName(lpszDocSetName),m_nHID(nHelpID)
{
}

void HelpHandler::Init(LPCTSTR lpszDocSetName,UINT nHelpID)
{
   m_strDocSetName = lpszDocSetName;
   m_nHID = nHelpID;
}

void HelpHandler::OnHelp()
{
   ATLASSERT( !m_strDocSetName.IsEmpty() ); // did you forget to initlize me?
   ATLASSERT(m_nHID != 0);
   EAFHelp(m_strDocSetName,m_nHID);
}
