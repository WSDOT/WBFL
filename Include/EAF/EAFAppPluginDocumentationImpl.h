///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2017  Washington State Department of Transportation
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

#pragma once

#include <EAF\EAFExp.h>
#include <map>

class CEAFApp;
interface IEAFAppPlugin;

// This class provides a ready-to-use implementation for IEAFAppPlugin methods
// associated with application documentation.
//
// Create an instance of this class in your IEAFAppPlugin implementation
// and call the Init function with the documenation set name. Delegate
// the calls to the application documentation related methods in IEAFAppPlugin
// to the methods implemented in this class
class EAFCLASS CEAFAppPluginDocumentationImpl
{
public:
   CEAFAppPluginDocumentationImpl();
   ~CEAFAppPluginDocumentationImpl();

   // Initialize with a documentation set name
   void Init(IEAFAppPlugin* pAppPlugin);

   // Returns the documenation set name
   CString GetDocumentationSetName();

   // Returns the default URL for this app plug-in's documentation
   // lpszName is typically the name of the app plug-in
   // Call AFX_MANAGE_STATE(AfxGetStaticModuleState()) before calling this method
   CString GetDocumentationURL();

   // Call AFX_MANAGE_STATE(AfxGetStaticModuleState()) before calling this method
   CString GetDocumentationMapFile();
   void LoadDocumentationMap();

   // Returns the full documentation URL for the given URL
   eafTypes::HelpResult GetDocumentLocation(LPCTSTR lpszDocSetName,UINT nID,CString& strURL);

private:
   IEAFAppPlugin* m_pAppPlugin; // weak reference

   CString m_DocSetName;
   std::map<UINT,CString> m_HelpTopics;
   CString m_strOnlineDocumentationMapFile;
};
