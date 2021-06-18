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

#pragma once

#include <EAF\EAFTypes.h>

/////////////////////////////////////////////////////////////////////////////
// IEAFDocument
//
// Interface for providing documentation support

// {68806E25-8FEC-4652-924A-371C8FB2CFA6}
DEFINE_GUID(IID_IEAFPluginDocumentationIntegration,
   0x68806e25, 0x8fec, 0x4652, 0x92, 0x4a, 0x37, 0x1c, 0x8f, 0xb2, 0xcf, 0xa6);
struct __declspec(uuid("{68806E25-8FEC-4652-924A-371C8FB2CFA6}")) IEAFPluginDocumentationIntegration;// for __uuidof


interface IEAFPluginDocumentationIntegration : IUnknown
{
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
