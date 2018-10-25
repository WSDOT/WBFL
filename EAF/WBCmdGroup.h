///////////////////////////////////////////////////////////////////////
// ReportManager - Manages report definitions
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

#if !defined(_WBCGID_H_)
#define _WBCGID_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define INITGUID
#include <objbase.h>
#include <initguid.h>

//#ifndef CGID_IWebBrowser
// CGID_WebBrowser: {ED016940-BD5B-11cf-BA4E-00C04FD70816}
DEFINE_GUID(CGID_IWebBrowserPriv,0xED016940L,0xBD5B,0x11cf,0xBA,0x4E,0x00,0xC0,0x4F,0xD7,0x08,0x16);
//#endif

//
// Utility class for the WebBrowser Command Group
class CWBCmdGroup
{
public:
   // CommandTarget ids for menu driving
   enum 
   {
      HTMLID_FIND         = 1,
      HTMLID_VIEWSOURCE   = 2,
      HTMLID_OPTIONS      = 3,
   };
};

#endif // _WBCGID_H_
