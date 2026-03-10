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

#if !defined(AFX_EAFAPPPLUGIN_H__DC344A29_BA50_41C3_AAD4_DD3571113293__INCLUDED_)
#define AFX_EAFAPPPLUGIN_H__DC344A29_BA50_41C3_AAD4_DD3571113293__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EAFAppPlugin.h : header file
//

#include <EAF\EAFDocTemplate.h>
#include <EAF\EAFCommandLineInfo.h>
#include <EAF\EAFTypes.h>
#include "ComponentObject.h"

class CEAFApp;

namespace WBFL
{
   namespace EAF
   {
      // This interface must be implemented by any object plugging into a
      // CEAFApp-based application. This are "Plugin Applications"
      class IPluginApp
      {
      public:
         // Called for self-initialization
         virtual BOOL Init(CEAFApp * pParent) = 0;

         // Called when the application is about to terminate
         virtual void Terminate() = 0;

         // Called to give this plugin the opportunity to integrate itself
         // into the user interface. When bIntegrate is TRUE, add menus, commands, toolbars, etc
         // when FALSE, remove what you added
         virtual void IntegrateWithUI(BOOL bIntegrate) = 0;

         // Creates a document template for use in MFC's Doc/View model
         virtual std::vector<CEAFDocTemplate*> CreateDocTemplates() = 0;

         // Returns the menu handle of a shared menu. Return nullptr if this application does
         // not use a shared menu
         virtual HMENU GetSharedMenuHandle() = 0;

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
         virtual std::pair<WBFL::EAF::HelpResult,CString> GetDocumentLocation(LPCTSTR lpszDocSetName,UINT nID) = 0;
      };

      class IAppCommandLine
      {
      public:
         // Return the application name that goes with the \App= flag
         virtual CString GetCommandLineAppName() const = 0;

         virtual CString GetUsageMessage() = 0;

         // Called by the framework to give this application plugin an opportunity
         // to process command line options. The application plug-in may need to re-parse
         // the command line parameters using the parent object supplied in Init().
         // Return TRUE if the command line was processed, otherwise return FALSE.
         virtual BOOL ProcessCommandLineOptions(CEAFCommandLineInfo& cmdInfo) = 0;
      };
   };
};

#endif // !defined(AFX_EAFAPPPLUGIN_H__DC344A29_BA50_41C3_AAD4_DD3571113293__INCLUDED_)
