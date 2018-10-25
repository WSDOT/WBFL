///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
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

#ifndef INCLUDED_RECTANGLEDRAWDRAWLINESTRATEGY_H_
#define INCLUDED_RECTANGLEDRAWDRAWLINESTRATEGY_H_
#pragma once

#include <DManip\DrawLineStrategy.h>
#include <DManip\LineStyles.h>

interface iRectangleDrawLineStrategy : public iDrawLineStrategy
{
   STDMETHOD_(void,SetWidth)(Float64 width) PURE;
   STDMETHOD_(Float64,GetWidth)() PURE;
   STDMETHOD_(void,SetLineWidth)(UINT nWidth) PURE;
   STDMETHOD_(UINT,GetLineWidth)() PURE;
   STDMETHOD_(void,SetColor)(COLORREF crColor) PURE;
   STDMETHOD_(COLORREF,GetColor)() PURE;
   STDMETHOD_(void,SetLineStyle)(LineStyleType style) PURE;
   STDMETHOD_(LineStyleType,GetLineStyle)() PURE;
   STDMETHOD_(void,PerimeterGravityWell)(BOOL bPerimeterGravityWell) PURE;
   STDMETHOD_(void,SetFillColor)(COLORREF crColor) PURE;
   STDMETHOD_(COLORREF,GetFillColor)() PURE;
   STDMETHOD_(void,DoFill)(BOOL doFill) PURE;
   STDMETHOD_(BOOL,DoFill)() PURE;
};

#endif // INCLUDED_RECTANGLEDRAWDRAWLINESTRATEGY_H_
