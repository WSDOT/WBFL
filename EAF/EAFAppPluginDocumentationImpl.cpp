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

// EAFAppPluginDocumentationImpl.cpp : implementation file
//

#include "stdafx.h"
#include <EAF\EAFAppPluginDocumentationImpl.h>
#include <EAF\EAFUtilities.h>
#include <EAF\EAFApp.h>
#include <EAF\EAFAppPlugin.h>
#include <MFCTools\VersionInfo.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// NOTE: Do not call our own methods directly... Always call them through the m_pAppPlugin. This gives the app plugin
// a chance to set modulue states.

CEAFAppPluginDocumentationImpl::CEAFAppPluginDocumentationImpl()
{
}

CEAFAppPluginDocumentationImpl::~CEAFAppPluginDocumentationImpl()
{
}

void CEAFAppPluginDocumentationImpl::Init(IEAFAppPlugin* pAppPlugin)
{
   m_pAppPlugin = pAppPlugin;
   m_DocSetName = m_pAppPlugin->GetDocumentationSetName();
   m_pAppPlugin->LoadDocumentationMap();
}

CString CEAFAppPluginDocumentationImpl::GetDocumentationSetName()
{
   return m_DocSetName;
}

CString CEAFAppPluginDocumentationImpl::GetDocumentationURL()
{
   ATLASSERT(!m_DocSetName.IsEmpty()); // did you forget to call Init()?
   CEAFApp* pApp = EAFGetApp();

   CString strBaseURL;
   strBaseURL.Format(_T("%s%s/"),pApp->GetDocumentationRootLocation(),m_DocSetName);

   CVersionInfo verInfo;

   CWinApp* pMe = AfxGetApp();
   CString strAppName = pMe->m_pszExeName;
   //CString strAppName = AfxGetAppName(); // needs module state
   strAppName += _T(".dll");
   verInfo.Load(strAppName);

   CString strVersion = verInfo.GetProductVersionAsString();
   std::_tstring v(strVersion);
   auto count = std::count(std::begin(v), std::end(v), _T('.'));

   // remove the hot fix and build/release number
   for (auto i = 0; i < count-1; i++)
   {
      int pos = strVersion.ReverseFind(_T('.')); // find the last '.'
      strVersion = strVersion.Left(pos);
   }

   CString strURL;
   strURL.Format(_T("%s%s/"),strBaseURL,strVersion);
   return strURL;
}

CString CEAFAppPluginDocumentationImpl::GetDocumentationMapFile()
{
   ATLASSERT(!m_DocSetName.IsEmpty()); // did you forget to call Init()?
   CEAFApp* pApp = EAFGetApp();
   return EAFGetDocumentationMapFile(m_DocSetName,m_pAppPlugin->GetDocumentationURL());
}

void CEAFAppPluginDocumentationImpl::LoadDocumentationMap()
{
   EAFLoadDocumentationMap(GetDocumentationMapFile(),m_HelpTopics);
}

eafTypes::HelpResult CEAFAppPluginDocumentationImpl::GetDocumentLocation(LPCTSTR lpszDocSetName,UINT nID,CString& strURL)
{
   if ( m_DocSetName != CString(lpszDocSetName) )
   {
      return eafTypes::hrDocSetNotFound;
   }

   std::map<UINT,CString>::iterator found(m_HelpTopics.find(nID));
   if ( found == m_HelpTopics.end() )
   {
      return eafTypes::hrTopicNotFound;
   }

   CString strBaseURL = m_pAppPlugin->GetDocumentationURL();

   strURL.Format(_T("%s%s"),strBaseURL,found->second);

   return eafTypes::hrOK;
}
