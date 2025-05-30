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

// EAFAppPluginDocumentationImpl.cpp : implementation file
//

#include "stdafx.h"
#include <EAF\PluginAppDocumentationImpl.h>
#include <EAF\EAFUtilities.h>
#include <EAF\EAFApp.h>
#include <EAF\PluginApp.h>
#include <MFCTools\VersionInfo.h>

using namespace WBFL::EAF;

// NOTE: Do not call our own methods directly... Always call them through the m_pAppPlugin. This gives the app plugin
// a chance to set module states.

PluginAppDocumentationImpl::PluginAppDocumentationImpl()
{
}

PluginAppDocumentationImpl::~PluginAppDocumentationImpl()
{
}

void PluginAppDocumentationImpl::Init(std::weak_ptr<WBFL::EAF::IPluginApp> pPluginApp)
{
   m_pPluginApp = pPluginApp;
   auto plugin = m_pPluginApp.lock();
   m_DocSetName = plugin->GetDocumentationSetName();
   plugin->LoadDocumentationMap();
}

CString PluginAppDocumentationImpl::GetDocumentationSetName()
{
   return m_DocSetName;
}

CString PluginAppDocumentationImpl::GetDocumentationURL()
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

CString PluginAppDocumentationImpl::GetDocumentationMapFile()
{
   ATLASSERT(!m_DocSetName.IsEmpty()); // did you forget to call Init()?
   CEAFApp* pApp = EAFGetApp();
   auto plugin = m_pPluginApp.lock();
   return EAFGetDocumentationMapFile(m_DocSetName,plugin->GetDocumentationURL());
}

void PluginAppDocumentationImpl::LoadDocumentationMap()
{
   EAFLoadDocumentationMap(GetDocumentationMapFile(),m_HelpTopics);
}

std::pair<WBFL::EAF::HelpResult,CString> PluginAppDocumentationImpl::GetDocumentLocation(LPCTSTR lpszDocSetName,UINT nID)
{
   if ( m_DocSetName != CString(lpszDocSetName) )
   {
      return { WBFL::EAF::HelpResult::DocSetNotFound,CString() };
   }

   std::map<UINT,CString>::iterator found(m_HelpTopics.find(nID));
   if ( found == m_HelpTopics.end() )
   {
      return { WBFL::EAF::HelpResult::TopicNotFound,CString() };
   }

   auto plugin = m_pPluginApp.lock();
   CString strBaseURL = plugin->GetDocumentationURL();

   CString strURL;
   strURL.Format(_T("%s%s"),strBaseURL,found->second);

   return { WBFL::EAF::HelpResult::OK,strURL };
}
