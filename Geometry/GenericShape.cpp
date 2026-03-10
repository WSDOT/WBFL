///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2025  Washington State Department of Transportation
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

// GenericShape.cpp : Implementation of CGenericShape
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "GenericShape.h"
#include "Point2d.h"
#include "Helper.h"
#include <MathEx.h>


/////////////////////////////////////////////////////////////////////////////
// CGenericShape
HRESULT CGenericShape::FinalConstruct()
{
   CComObject<CPoint2d>* pCentroid;
   CComObject<CPoint2d>::CreateInstance(&pCentroid);

   pCentroid->SetPoint(m_Shape.GetCentroid());

   pCentroid->QueryInterface(&m_pCentroid);

   return S_OK;
}

void CGenericShape::FinalRelease()
{
}

void CGenericShape::SetShape(const WBFL::Geometry::GenericShape& shape)
{ 
   // we can't use the direct assignment of m_Shape = shape because that will
   // copy the shared pointer. we need our shape to have an independent centroid
   // so we use the CreateClone method to create the copy
   std::shared_ptr<WBFL::Geometry::Shape> clone(shape.CreateClone());
   auto clone_shape = std::dynamic_pointer_cast<WBFL::Geometry::GenericShape>(clone);
   m_Shape = *clone_shape;
   dynamic_cast<CPoint2d*>(m_pCentroid.p)->SetPoint(m_Shape.GetCentroid());
}

STDMETHODIMP CGenericShape::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
      &IID_IGenericShape,
		&IID_IShape,
		&IID_IXYPosition
	};
	for (int i = 0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CGenericShape::get_Area(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Shape.GetArea();
   return S_OK;
}

STDMETHODIMP CGenericShape::put_Area(Float64 newVal)
{
   m_Shape.SetArea(newVal);
   return S_OK;
}

STDMETHODIMP CGenericShape::put_Perimeter(Float64 newVal)
{
   m_Shape.SetPerimeter(newVal);
   return S_OK;
}

STDMETHODIMP CGenericShape::get_Centroid(IPoint2d* *pVal)
{
   CHECK_RETOBJ(pVal);
   return m_pCentroid.CopyTo(pVal);
}

STDMETHODIMP CGenericShape::putref_Centroid(IPoint2d* newVal)
{
   CHECK_IN(newVal);
   m_pCentroid = newVal;
   m_Shape.SetCentroid(GetInnerPoint(m_pCentroid));
   return S_OK;
}

STDMETHODIMP CGenericShape::get_Xleft(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Shape.GetXleft();
   return S_OK;
}

STDMETHODIMP CGenericShape::put_Xleft(Float64 newVal)
{
   m_Shape.SetXleft(newVal);
   return S_OK;
}

STDMETHODIMP CGenericShape::get_Xright(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Shape.GetXright();
   return S_OK;
}

STDMETHODIMP CGenericShape::put_Xright(Float64 newVal)
{
   m_Shape.SetXright(newVal);
   return S_OK;
}

STDMETHODIMP CGenericShape::get_Ytop(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Shape.GetYtop();
   return S_OK;
}

STDMETHODIMP CGenericShape::put_Ytop(Float64 newVal)
{
   m_Shape.SetYtop(newVal);
   return S_OK;
}

STDMETHODIMP CGenericShape::get_Ybottom(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Shape.GetYbottom();
   return S_OK;
}

STDMETHODIMP CGenericShape::put_Ybottom(Float64 newVal)
{
   m_Shape.SetYbottom(newVal);
   return S_OK;
}

STDMETHODIMP CGenericShape::get_Ixx(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Shape.GetIxx();
   return S_OK;
}

STDMETHODIMP CGenericShape::put_Ixx(Float64 newVal)
{
   m_Shape.SetIxx(newVal);
   return S_OK;
}

STDMETHODIMP CGenericShape::get_Iyy(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Shape.GetIyy();
   return S_OK;
}

STDMETHODIMP CGenericShape::put_Iyy(Float64 newVal)
{
   m_Shape.SetIyy(newVal);
   return S_OK;
}

STDMETHODIMP CGenericShape::get_Ixy(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Shape.GetIxy();
   return S_OK;
}

STDMETHODIMP CGenericShape::put_Ixy(Float64 newVal)
{
   m_Shape.SetIxy(newVal);
   return S_OK;
}

STDMETHODIMP CGenericShape::get_Shape(IShape **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IShape, (void**)pVal );
}

STDMETHODIMP CGenericShape::get_XYPosition(IXYPosition **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IXYPosition, (void**)pVal );
}

/////////////////////////////////////////////////////////////////////////////
// IShape
/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CGenericShape::get_ShapeProperties(IShapeProperties* *props)
{
   CHECK_RETOBJ(props);
   return ::CreateShapeProperties(m_Shape.GetProperties(), props);
}

STDMETHODIMP CGenericShape::get_BoundingBox(IRect2d* *rect)
{
   CHECK_RETOBJ(rect);
   return CreateRect(m_Shape.GetBoundingBox(), rect);
}

STDMETHODIMP CGenericShape::get_PolyPoints(IPoint2dCollection** ppPolyPoints)
{
   CHECK_RETOBJ(ppPolyPoints);
   return CreatePointCollection(m_Shape.GetPolyPoints(), ppPolyPoints);
}

STDMETHODIMP CGenericShape::PointInShape(IPoint2d* pPoint,VARIANT_BOOL* pbResult)
{
   CHECK_IN(pPoint);
   CHECK_RETVAL(pbResult);
   *pbResult = MakeBool(m_Shape.PointInShape(GetPoint(pPoint)));
   return S_OK;
}

STDMETHODIMP CGenericShape::Clone(IShape** pClone)
{
   CHECK_RETOBJ(pClone);

   return ::Clone<CGenericShape>(m_Shape, pClone);
}

STDMETHODIMP CGenericShape::ClipWithLine(ILine2d* pLine,IShape** pShape)
{
   CHECK_IN(pLine);
   CHECK_RETOBJ(pShape);
   return ::ClipWithLine<WBFL::Geometry::GenericShape>(m_Shape, pLine, pShape);
}

STDMETHODIMP CGenericShape::ClipIn(IRect2d* pRect,IShape** pShape)
{
   CHECK_IN(pRect);
   CHECK_RETOBJ(pShape);
   return ::ClipIn<WBFL::Geometry::GenericShape>(m_Shape, pRect, pShape);
}

STDMETHODIMP CGenericShape::get_Perimeter(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Shape.GetPerimeter();
   return S_OK;
}

STDMETHODIMP CGenericShape::FurthestDistance(ILine2d* line,Float64 *pVal)
{
   CHECK_IN(line);
   CHECK_RETVAL(pVal);
   ::GetFurthestDistance<WBFL::Geometry::GenericShape>(m_Shape, line, pVal);
   
   return S_OK;
}

STDMETHODIMP CGenericShape::FurthestPoint(ILine2d* line, IPoint2d** ppPoint, Float64* dist)
{
   CHECK_IN(line);
   CHECK_RETOBJ(ppPoint);
   CHECK_RETVAL(dist);

   ::GetFurthestPoint<WBFL::Geometry::GenericShape>(m_Shape, line, ppPoint, dist);

   return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IXYPosition
/////////////////////////////////////////////////////////////////////////////

STDMETHODIMP CGenericShape::Offset(Float64 dx,Float64 dy)
{
   m_Shape.Offset(dx, dy);
   return S_OK;
}

STDMETHODIMP CGenericShape::OffsetEx(ISize2d* pSize)
{
   CHECK_IN(pSize);
   m_Shape.Offset(GetSize(pSize));
   return S_OK;
}

STDMETHODIMP CGenericShape::get_LocatorPoint(LocatorPointType lp, IPoint2d** point)
{
   CHECK_RETOBJ(point);
   return CreatePoint(m_Shape.GetLocatorPoint(WBFL::Geometry::Shape::LocatorPoint(lp)), point);
}

STDMETHODIMP CGenericShape::put_LocatorPoint(LocatorPointType lp, IPoint2d* point)
{
   CHECK_IN(point);
   m_Shape.SetLocatorPoint(WBFL::Geometry::Shape::LocatorPoint(lp), GetPoint(point));
   return S_OK;
}

STDMETHODIMP CGenericShape::MoveEx(IPoint2d* pFrom,IPoint2d* pTo)
{
   CHECK_IN(pFrom);
   CHECK_IN(pTo);
   m_Shape.Move(GetPoint(pFrom), GetPoint(pTo)); 
   return S_OK;
}

STDMETHODIMP CGenericShape::RotateEx(IPoint2d* pPoint,Float64 angle)
{
   CHECK_IN(pPoint);
   m_Shape.Rotate(GetPoint(pPoint), angle); 
   return S_OK;
}

STDMETHODIMP CGenericShape::Rotate(Float64 cx,Float64 cy,Float64 angle)
{
   m_Shape.Rotate(WBFL::Geometry::Point2d(cx, cy), angle); 
   return S_OK;
}
