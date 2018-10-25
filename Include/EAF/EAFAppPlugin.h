///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2010  Washington State Department of Transportation
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

class CEAFApp;

// {78D5872C-663A-4920-B1A1-E2E2528D5E3F}
DEFINE_GUID(IID_IEAFAppPlugin, 
0x78d5872c, 0x663a, 0x4920, 0xb1, 0xa1, 0xe2, 0xe2, 0x52, 0x8d, 0x5e, 0x3f);
struct __declspec(uuid("{78D5872C-663A-4920-B1A1-E2E2528D5E3F}")) IEAFAppPlugin;// for __uuidof

interface IEAFAppPlugin : IUnknown
{
   virtual BOOL Init(CEAFApp* pParent) = 0;
   virtual void Terminate() = 0;
   virtual CEAFDocTemplate* CreateDocTemplate() = 0;
   virtual CCmdTarget* GetCommandTarget() = 0;
   virtual HMENU GetSharedMenuHandle() = 0;
   virtual UINT GetDocumentResourceID() = 0;
   virtual CString GetName() = 0;
};

#endif // !defined(AFX_EAFAPPPLUGIN_H__DC344A29_BA50_41C3_AAD4_DD3571113293__INCLUDED_)
