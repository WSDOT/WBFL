///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
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
#pragma once

#include "resource.h"       // main symbols
#include "WBFLGeometry.h"
#include "Helper.h"

template <class C,class T>
class ATL_NO_VTABLE IShapeXYPositionImpl : public IShape, public IXYPosition
{
	virtual T& GetShape() = 0;

	// IShape
	STDMETHOD(FurthestDistance)(/*[in]*/ILine2d* line,/*[out, retval]*/ Float64* pVal) override { return ::GetFurthestDistance<T>(GetShape(), line, pVal); }
	STDMETHOD(get_Perimeter)(/*[out, retval]*/ Float64* pVal) override { return ::GetPerimeter<T>(GetShape(), pVal); }
	STDMETHOD(get_ShapeProperties)(/*[out,retval]*/ IShapeProperties** pVal) override { return ::GetShapeProperties<T>(GetShape(), pVal); }
	STDMETHOD(get_BoundingBox)(/*[out, retval]*/ IRect2d** pVal) override { return ::GetBoundingBox<T>(GetShape(), pVal); }
	STDMETHOD(get_PolyPoints)(/*[out,retval]*/ IPoint2dCollection** ppPolyPoints) override { return ::GetPolyPoints<T>(GetShape(), ppPolyPoints); }
	STDMETHOD(PointInShape)(/*[in]*/ IPoint2d* pPoint,/*[out,retval]*/ VARIANT_BOOL* pbResult) override { return ::PointInShape<T>(GetShape(), pPoint, pbResult); }
	STDMETHOD(Clone)(/*[out,retval]*/ IShape** pClone) override { return ::Clone<C>(GetShape(), pClone); }
	STDMETHOD(ClipWithLine)(/*[in]*/ ILine2d* pLine,/*[out,retval]*/ IShape** pShape) override { return ::ClipWithLine<T>(GetShape(), pLine, pShape); }
	STDMETHOD(ClipIn)(/*[in]*/ IRect2d* pRect,/*[out,retval]*/ IShape** pShape) override { return ::ClipIn<T>(GetShape(), pRect, pShape); }

	// IXYPosition
	STDMETHOD(Offset)(Float64 dx, Float64 dy) override { GetShape().Offset(WBFL::Geometry::Size2d(dx, dy)); return S_OK; }
	STDMETHOD(OffsetEx)(ISize2d* pSize) override { CHECK_IN(pSize);  GetShape().Offset(::GetSize(pSize)); return S_OK; }
	STDMETHOD(get_LocatorPoint)(LocatorPointType lp, IPoint2d** point) override { CHECK_RETOBJ(point); return CreatePoint(GetShape().GetLocatorPoint(WBFL::Geometry::Shape::LocatorPoint(lp)), point); }
	STDMETHOD(put_LocatorPoint)(LocatorPointType lp, IPoint2d* point) override { CHECK_IN(point); GetShape().SetLocatorPoint(WBFL::Geometry::Shape::LocatorPoint(lp), GetPoint(point)); return S_OK; }
	STDMETHOD(MoveEx)(IPoint2d* pFrom, IPoint2d* pTo) override { CHECK_IN(pFrom); CHECK_IN(pTo); GetShape().Move(GetPoint(pFrom), GetPoint(pTo)); return S_OK; }
	STDMETHOD(RotateEx)(IPoint2d* pPoint, Float64 angle) override { CHECK_IN(pPoint); GetShape().Rotate(GetPoint(pPoint), angle); return S_OK; }
	STDMETHOD(Rotate)(Float64 cx, Float64 cy, Float64 angle) override { GetShape().Rotate(WBFL::Geometry::Point2d(cx, cy), angle); return S_OK; }
};
