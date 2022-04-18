///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2022  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Library Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////


#if !defined FEM2D_FEMALL_H_
#define FEM2D_FEMALL_H_
#pragma once

#include <string>

// This include file has stuff that is needed by all fem files

#define NUM_DOF 3
#define MAX_ELEMENT_DOF 6 // used to avoid dynamic memory allocation

#undef  EPS
#define EPS  0.10
#undef   zero_val
#define  zero_val( x )     (((-EPS)<=(x)) && ((x)<=(EPS)))


inline CComBSTR CreateErrorMsg1(UINT nid, CollectionIndexType someInt)
{
   TCHAR str[256];
   ::LoadString( _Module.GetModuleInstance(), nid, str, 256);
   TCHAR msg[256];
   int cOut = _stprintf_s( msg, 256, str, someInt);
   ATLASSERT( cOut < 256 );
   return CComBSTR(msg);
}

inline CComBSTR CreateErrorMsg2(UINT nid, CollectionIndexType someInt1, CollectionIndexType someInt2)
{
   TCHAR str[256];
   ::LoadString( _Module.GetModuleInstance(), nid, str, 256);
   TCHAR msg[256];
   int cOut = _stprintf_s( msg, 256, str, someInt1, someInt2);
   ATLASSERT( cOut < 256 );
   return CComBSTR(msg);
}

inline LPCOLESTR GetHelpFile()
{
   USES_CONVERSION;
   return A2OLE("WBFLFem2d.chm");
}

inline void CheckLoadOrientation(Fem2dLoadOrientation or)
{
   if (or!=lotGlobal && or!=lotMember && or!=lotGlobalProjected)
   {
      THROW_IDS(IDS_E_INVALID_LOAD_ORIENTATION,FEM2D_E_INVALID_LOAD_ORIENTATION,IDH_E_INVALID_LOAD_ORIENTATION);
   }
}
#endif // FEM2D_FEMALL_H_
