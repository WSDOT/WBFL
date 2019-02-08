///////////////////////////////////////////////////////////////////////
// DManipTools - Direct Manipulation Tools
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

#ifndef INCLUDED_DATAPOINTDRAWSTRATEGY_H_
#define INCLUDED_DATAPOINTDRAWSTRATEGY_H_
#pragma once

#include "DManipTools\DManipTools.h"

DEFINE_GUID(IID_iDataPointDrawStrategy, 
0xe1c61a80, 0x115f, 0x4281, 0x92, 0x6f, 0x4f, 0x7a, 0x65, 0xad, 0x33, 0x2a);
struct __declspec(uuid("{E1C61A80-115F-4281-926F-4F7A65AD332A}")) iDataPointDrawStrategy;

interface iDataPointDrawStrategy : public IUnknown
{
   // name of font face for symbol
   // "Symbol" is the default
   STDMETHOD_(void,get_SymbolFontFace)(TCHAR* *pVal) PURE;
   STDMETHOD_(void,put_SymbolFontFace)(LPCTSTR newVal) PURE;

   // character font size in 1/10 points
   STDMETHOD_(long,get_SymbolSize)() PURE;
   STDMETHOD_(void,put_SymbolSize)(long code) PURE;
   // symbol character code (ascii)
   STDMETHOD_(DWORD,get_SymbolCharacterCode)() PURE;
   STDMETHOD_(void,put_SymbolCharacterCode)(DWORD code) PURE;

   STDMETHOD_(COLORREF,get_Color)() PURE;
   STDMETHOD_(void,put_Color)(COLORREF color) PURE;
};

#endif // INCLUDED_DATAPOINTDRAWSTRATEGY_H_