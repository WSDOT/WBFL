///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
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

#ifndef INCLUDED_SIMPLEDRAWLINESTRATEGY_H_
#define INCLUDED_SIMPLEDRAWLINESTRATEGY_H_
#pragma once

#include <DManip\DrawLineStrategy.h>
#include <DManip\LineStyles.h>

typedef enum LineEndType
{
   leNone   = 0,
   leCircle = 1,
   leDot    = 2
} LineEndType;

interface iSimpleDrawLineStrategy : public iDrawLineStrategy
{
   STDMETHOD_(void,SetWidth)(UINT nWidth) PURE;
   STDMETHOD_(UINT,GetWidth)() PURE;
   STDMETHOD_(void,SetColor)(COLORREF crColor) PURE;
   STDMETHOD_(COLORREF,GetColor)() PURE;
   STDMETHOD_(void,SetBeginType)(LineEndType type) PURE;
   STDMETHOD_(LineEndType,GetBeginType)() PURE;
   STDMETHOD_(int,GetBeginSize)() PURE;
   STDMETHOD_(void,SetBeginSize)(int size) PURE;
   STDMETHOD_(void,SetEndType)(LineEndType type) PURE;
   STDMETHOD_(LineEndType,GetEndType)() PURE;
   STDMETHOD_(int,GetEndSize)() PURE;
   STDMETHOD_(void,SetEndSize)(int size) PURE;
   STDMETHOD_(void,SetLineStyle)(LineStyleType style) PURE;
   STDMETHOD_(LineStyleType,GetLineStyle)() PURE;
};

#endif // INCLUDED_SIMPLEDRAWLINESTRATEGY_H_
