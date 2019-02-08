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
///////////////////////////////////////////////////////////////////////

#pragma once

class CEAFDocument;

#include <EAF\EAFCommandLineInfo.h>

/////////////////////////////////////////////////////////////
// IEAFDocumentPlugin
//
// This interface must be implemented by objects that plug into
// and CEAFDocument object

// {34D0ED97-FBCF-44a6-A187-C66B3C015B7F}
DEFINE_GUID(IID_IEAFDocumentPlugin, 
0x34d0ed97, 0xfbcf, 0x44a6, 0xa1, 0x87, 0xc6, 0x6b, 0x3c, 0x1, 0x5b, 0x7f);
struct __declspec(uuid("{34D0ED97-FBCF-44a6-A187-C66B3C015B7F}")) IEAFDocumentPlugin;// for __uuidof

interface IEAFDocumentPlugin : IUnknown
{
   // Called for self-initialization
   virtual BOOL Init(CEAFDocument* pParent) = 0;

   // Called when the application is about to terminat
   virtual void Terminate() = 0;

   // Called to give this plugin the opportunity to integrate itself
   // into the user interface. When bIntegrate is TRUE, add menus, commands, toolbars, etc
   // when FALSE, remove what you added
   virtual BOOL IntagrateWithUI(BOOL bIntegrate) = 0;

   // return the name of the plugin. This name is used throughout the user interface
   virtual CString GetName() = 0;

   // returns the name of the documentation set for this plug-in
   virtual CString GetDocumentationSetName() = 0;

   // gets the URL for the help document associated with nHID
   // returns TRUE on success
   virtual eafTypes::HelpResult GetDocumentLocation(LPCTSTR lpszDocSetName,UINT nHID,CString& strURL) = 0;
};


/////////////////////////////////////////////////////////////
// IEAFDocCommandLine
//
// IEAFDocumentPlugin objects may implement this interface if they process
// command line parameters.


// {D1D07B6D-1ED6-44e7-A615-1B03CD04E827}
DEFINE_GUID(IID_IEAFDocCommandLine, 
0xd1d07b6d, 0x1ed6, 0x44e7, 0xa6, 0x15, 0x1b, 0x3, 0xcd, 0x4, 0xe8, 0x27);
struct __declspec(uuid("{D1D07B6D-1ED6-44e7-A615-1B03CD04E827}")) IEAFDocCommandLine;// for __uuidof

interface IEAFDocCommandLine : IUnknown
{
   // Called by the framework to give this application plugin an opportinuity
   // to process command line options. The application plug-in may need to re-parse
   // the command line parameters.
   // Return TRUE if the command line was processed, otherwise return FALSE.
   virtual BOOL ProcessCommandLineOptions(CEAFCommandLineInfo& cmdInfo) = 0;
};