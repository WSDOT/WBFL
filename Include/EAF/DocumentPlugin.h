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

#pragma once

class CEAFDocument;
class CEAFCommandLineInfo;


/////////////////////////////////////////////////////////////
// IEAFDocCommandLine
//
// IEAFDocumentPlugin objects may implement this interface if they process
// command line parameters.

namespace WBFL
{
   namespace EAF
   {
      /// @brief This interface must be implemented by objects that plug into and CEAFDocument object
      class IDocumentPlugin
      {
      public:
         /// @brief Called for self-initialization
         virtual BOOL Init(CEAFDocument * pParent) = 0;

         /// @brief Called when the application is about to terminate
         virtual void Terminate() = 0;

         /// @brief Called to give this plugin the opportunity to integrate itself
         /// into the user interface. When bIntegrate is TRUE, add menus, commands, toolbars, etc
         /// when FALSE, remove what you added
         virtual BOOL IntegrateWithUI(BOOL bIntegrate) = 0;

         /// @brief return the name of the plugin. This name is used throughout the user interface
         virtual CString GetName() = 0;

         /// @brief returns the name of the documentation set for this plug-in
         virtual CString GetDocumentationSetName() = 0;

         /// @brief gets the URL for the help document associated with nHID
         //// returns TRUE on success
         virtual std::pair<WBFL::EAF::HelpResult,CString> GetDocumentLocation(LPCTSTR lpszDocSetName,UINT nHID) = 0;
      };
   

      /// @brief IEAFDocumentPlugin objects may implement this interface if they process command line parameters.
      class IDocCommandLine
      {
      public:
         /// @brief Called by the framework to give this application plugin an opportunity
         /// to process command line options. The application plug-in may need to re-parse
         /// the command line parameters.
         /// Return TRUE if the command line was processed, otherwise return FALSE.
         virtual BOOL ProcessCommandLineOptions(CEAFCommandLineInfo & cmdInfo) = 0;
      };
   };
};