///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
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

#ifndef INCLUDED_SHAPEDRAWSTRATEGY_H_
#define INCLUDED_SHAPEDRAWSTRATEGY_H_
#pragma once

#include <DManip\DrawPointStrategy.h>
#include <DManip\LineStyles.h>

interface IShape;

interface iShapeDrawStrategy : public iDrawPointStrategy
{
   STDMETHOD_(void,SetShape)(IShape* pShape) PURE;
   STDMETHOD_(void,GetShape)(IShape** ppShape) PURE;
   STDMETHOD_(void,SetSolidLineStyle)(LineStyleType lineStyle) PURE;
   STDMETHOD_(LineStyleType,GetSolidLineStyle)() PURE;
   STDMETHOD_(void,SetSolidLineColor)(COLORREF crColor) PURE;
   STDMETHOD_(COLORREF,GetSolidLineColor)() PURE;
   STDMETHOD_(void,SetSolidFillColor)(COLORREF crColor) PURE;
   STDMETHOD_(COLORREF,GetSolidFillColor)() PURE;
   STDMETHOD_(void,SetSolidLineWidth)(UINT nPixels) PURE;
   STDMETHOD_(UINT,GetSolidLineWidth)() PURE;
   STDMETHOD_(void,SetVoidLineStyle)(LineStyleType lineStyle) PURE;
   STDMETHOD_(LineStyleType,GetVoidLineStyle)() PURE;
   STDMETHOD_(void,SetVoidLineColor)(COLORREF crColor) PURE;
   STDMETHOD_(COLORREF,GetVoidLineColor)() PURE;
   STDMETHOD_(void,SetVoidFillColor)(COLORREF crColor) PURE;
   STDMETHOD_(COLORREF,GetVoidFillColor)() PURE;
   STDMETHOD_(void,SetVoidLineWidth)(UINT nPixels) PURE;
   STDMETHOD_(UINT,GetVoidLineWidth)() PURE;
   STDMETHOD_(void,DoFill)(bool doFill) PURE;
   STDMETHOD_(bool,DoFill)() PURE;
   STDMETHOD_(void,HasBoundingShape)(bool bHasBoundingShape) PURE;
   STDMETHOD_(bool,HasBoundingShape)() PURE;
};


#include <GeomModel/Shape.h>
interface iShapeDrawStrategy2 : public iDrawPointStrategy
{
   STDMETHOD_(void, SetShape)(const std::shared_ptr<const WBFL::Geometry::Shape>& shape) PURE;
   STDMETHOD_(const std::shared_ptr<const WBFL::Geometry::Shape>&, GetShape)() PURE;
   STDMETHOD_(void, SetSolidLineStyle)(LineStyleType lineStyle) PURE;
   STDMETHOD_(LineStyleType, GetSolidLineStyle)() PURE;
   STDMETHOD_(void, SetSolidLineColor)(COLORREF crColor) PURE;
   STDMETHOD_(COLORREF, GetSolidLineColor)() PURE;
   STDMETHOD_(void, SetSolidFillColor)(COLORREF crColor) PURE;
   STDMETHOD_(COLORREF, GetSolidFillColor)() PURE;
   STDMETHOD_(void, SetSolidLineWidth)(UINT nPixels) PURE;
   STDMETHOD_(UINT, GetSolidLineWidth)() PURE;
   STDMETHOD_(void, SetVoidLineStyle)(LineStyleType lineStyle) PURE;
   STDMETHOD_(LineStyleType, GetVoidLineStyle)() PURE;
   STDMETHOD_(void, SetVoidLineColor)(COLORREF crColor) PURE;
   STDMETHOD_(COLORREF, GetVoidLineColor)() PURE;
   STDMETHOD_(void, SetVoidFillColor)(COLORREF crColor) PURE;
   STDMETHOD_(COLORREF, GetVoidFillColor)() PURE;
   STDMETHOD_(void, SetVoidLineWidth)(UINT nPixels) PURE;
   STDMETHOD_(UINT, GetVoidLineWidth)() PURE;
   STDMETHOD_(void, DoFill)(bool doFill) PURE;
   STDMETHOD_(bool, DoFill)() PURE;
   STDMETHOD_(void, HasBoundingShape)(bool bHasBoundingShape) PURE;
   STDMETHOD_(bool, HasBoundingShape)() PURE;
};

#endif // INCLUDED_SHAPEDRAWSTRATEGY_H_
