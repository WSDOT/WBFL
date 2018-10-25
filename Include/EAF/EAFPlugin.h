///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2018  Washington State Department of Transportation
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

#include <EAF\EAFTypes.h>

class CEAFPluginApp;

/////////////////////////////////////////////////////////////////////////////
// IEAFPlugin
//
// This interface must be implemented by any object plugging into a
// CEAFPluginApp-based application

// {932F4563-1E9F-4192-A13E-E12A589D7B41}
DEFINE_GUID(IID_IEAFPlugin, 
0x932f4563, 0x1e9f, 0x4192, 0xa1, 0x3e, 0xe1, 0x2a, 0x58, 0x9d, 0x7b, 0x41);
struct __declspec(uuid("{932F4563-1E9F-4192-A13E-E12A589D7B41}")) IEAFPlugin;// for __uuidof

interface IEAFPlugin : IUnknown
{
   // Called for self-initialization
   virtual BOOL Init(CEAFPluginApp* pParent) = 0;

   // Called when the application is about to terminate
   virtual void Terminate() = 0;

   // Called to give this plugin the opportunity to integrate itself
   // into the user interface. When bIntegrate is TRUE, add menus, commands, toolbars, etc
   // when FALSE, remove what you added
   virtual void IntegrateWithUI(BOOL bIntegrate) = 0;

   // return the name of the plugin. This name is used throughout the user interface
   virtual CString GetName() = 0;

   // returns the name of the documentation set used by this application plug-in
   virtual CString GetDocumentationSetName() = 0;

   // returns the URL for the documentation.
   virtual CString GetDocumentationURL() = 0;

   // Returns the name of the documentation map file
   // Call AFX_MANAGE_STATE(AfxGetStaticModuleState()) before calling this method
   virtual CString GetDocumentationMapFile() = 0;

   // Called by the framework whenever the documentation map needs to be loaded or re-loaded
   // Call AFX_MANAGE_STATE(AfxGetStaticModuleState()) before calling this method
   virtual void LoadDocumentationMap() = 0;

   // Returns the full documentation URL for the given URL
   virtual eafTypes::HelpResult GetDocumentLocation(LPCTSTR lpszDocSetName,UINT nID,CString& strURL) = 0;
};
