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

// PolyShape.cpp : Implementation of CPolyShape
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "PolyShape.h"
#include <MathEx.h>
#include "Helper.h"
#include "Point2d.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPolyShape
HRESULT CPolyShape::FinalConstruct()
{
   CComObject<CPoint2d>* pHookPt;
   CComObject<CPoint2d>::CreateInstance(&pHookPt);

   pHookPt->SetPoint(m_Polygon.GetHookPoint());

   pHookPt->QueryInterface(&m_HookPoint);

   return S_OK;
}

void CPolyShape::FinalRelease()
{
}

STDMETHODIMP CPolyShape::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IPolyShape,
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

STDMETHODIMP CPolyShape::AddPoint(Float64 x,Float64 y)
{
   m_Polygon.AddPoint(x, y);
   return S_OK;
}

STDMETHODIMP CPolyShape::AddPointEx(IPoint2d *pPoint)
{
   CHECK_IN(pPoint);
   m_Polygon.AddPoint(::GetPoint(pPoint));
   return S_OK;
}

STDMETHODIMP CPolyShape::AddPoints(IPoint2dCollection *pPoints)
{
   CHECK_IN(pPoints);

   IndexType cPoints;
   pPoints->get_Count(&cPoints);

   for (IndexType i = 0; i < cPoints; i++)
   {
      CComPtr<IPoint2d> pPoint;
      pPoints->get_Item(i, &pPoint);
      m_Polygon.AddPoint(::GetPoint(pPoint));
   }

   return S_OK;
}

STDMETHODIMP CPolyShape::SetPoints(IPoint2dCollection* pPoints)
{
   CHECK_IN(pPoints);

   IndexType cPoints;
   pPoints->get_Count(&cPoints);

   m_Polygon.Clear();
   for (IndexType i = 0; i < cPoints; i++)
   {
      CComPtr<IPoint2d> pPoint;
      pPoints->get_Item(i, &pPoint);
      m_Polygon.AddPoint(::GetPoint(pPoint));
   }

   return S_OK;
}

STDMETHODIMP CPolyShape::ChangePoint(IndexType index, Float64 x, Float64 y)
{
   try
   {
      m_Polygon.ReplacePoint(index, x, y);
   }
   catch (...)
   {
      return E_INVALIDARG;
   }
   return S_OK;
}

STDMETHODIMP CPolyShape::ChangePointEx(IndexType index, IPoint2d* pPoint)
{
   CHECK_IN(pPoint);
   Float64 x, y;
   pPoint->Location(&x, &y);
   return ChangePoint(index, x, y);
}

STDMETHODIMP CPolyShape::RemovePoint(IndexType index)
{
   try 
   {
      m_Polygon.RemovePoint(index);
   }
   catch (...)
   {
      return E_INVALIDARG;
   }
   return S_OK;
}

STDMETHODIMP CPolyShape::get_Count(IndexType *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Polygon.GetCount();
   return S_OK;
}


STDMETHODIMP CPolyShape::GetPoint(IndexType index, Float64* pX, Float64* pY)
{
   CHECK_RETVAL(pX);
   CHECK_RETVAL(pY);

   try
   {
      const auto& point = m_Polygon.GetPoint(index);
      std::tie(*pX,*pY) = point.GetLocation();
   }
   catch (...)
   {
      return E_INVALIDARG;
   }
   return S_OK;
}

STDMETHODIMP CPolyShape::get_Point(IndexType index, IPoint2d **ppPoint)
{
   CHECK_RETOBJ(ppPoint);
   try
   {
      CreatePoint(m_Polygon.GetPoint(index), ppPoint);
   }
   catch (...)
   {
      return E_INVALIDARG;
   }
   return S_OK;
}

STDMETHODIMP CPolyShape::Clear()
{
   m_Polygon.Clear();
   return S_OK;
}

STDMETHODIMP CPolyShape::get_Points(IPoint2dCollection** coll)
{
   CHECK_RETOBJ(coll);
   return CreatePointCollection(m_Polygon.GetPolyPoints(), coll);
   return S_OK;
}

STDMETHODIMP CPolyShape::get_HookPoint(IPoint2d** hookPnt)
{
   CHECK_RETOBJ(hookPnt);
   return m_HookPoint.CopyTo(hookPnt);
}

STDMETHODIMP CPolyShape::putref_HookPoint(IPoint2d* hookPnt)
{
   CHECK_IN(hookPnt);
   m_HookPoint = hookPnt;
   m_Polygon.SetHookPoint(GetInnerPoint(m_HookPoint));
   return S_OK;
}

STDMETHODIMP CPolyShape::get_Shape(IShape **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IShape, (void**)pVal );
}

STDMETHODIMP CPolyShape::get_XYPosition(IXYPosition **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IXYPosition, (void**)pVal );
}

/////////////////////////////////////////////////////////////////////////////
// IShape
/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CPolyShape::get_ShapeProperties(IShapeProperties* *pVal)
{
   CHECK_RETOBJ(pVal);
   return CreateShapeProperties(m_Polygon.GetProperties(), pVal);
}

STDMETHODIMP CPolyShape::get_BoundingBox(IRect2d* *pVal)
{
   CHECK_RETOBJ(pVal);
   return CreateRect(m_Polygon.GetBoundingBox(), pVal);
}

STDMETHODIMP CPolyShape::get_PolyPoints(IPoint2dCollection** ppPolyPoints)
{
   CHECK_RETOBJ(ppPolyPoints);
   return CreatePointCollection(m_Polygon.GetPolyPoints(), ppPolyPoints);
   return S_OK;
}

STDMETHODIMP CPolyShape::PointInShape(IPoint2d* pPoint,VARIANT_BOOL* pbResult)
{
   CHECK_IN(pPoint);
   CHECK_RETVAL(pbResult);

   *pbResult = m_Polygon.PointInShape(::GetPoint(pPoint)) ? VARIANT_TRUE : VARIANT_FALSE;
   return S_OK;
}

STDMETHODIMP CPolyShape::Clone(IShape** pClone)
{
   CHECK_RETOBJ(pClone);

   CComObject<CPolyShape>* pTheClone;
   HRESULT hr = CComObject<CPolyShape>::CreateInstance(&pTheClone);
   if (FAILED(hr))
      return hr;

   pTheClone->m_Polygon = m_Polygon;

   CComPtr<IPolyShape> pcClone(pTheClone);
   return pcClone.QueryInterface(pClone);
}

STDMETHODIMP CPolyShape::ClipWithLine(ILine2d* pLine,IShape** pShape)
{
   // Clips on the right side of the line (clip away the left side, the right side remains)
   CHECK_IN(pLine);
   CHECK_RETOBJ(pShape);
   *pShape = nullptr;

   auto shape = m_Polygon.CreateClippedShape(GetLine(pLine), WBFL::Geometry::Line2d::Side::Left);
   if (shape)
   {
      CComPtr<IPolyShape> polyShape;
      HRESULT hr = ::CreatePolyShape(shape.get(), &polyShape);
      if (FAILED(hr))
         return hr;

      polyShape->get_Shape(pShape);
   }
   return S_OK;
}

STDMETHODIMP CPolyShape::ClipIn(IRect2d* pRect,IShape** pShape)
{
   CHECK_IN(pRect);
   CHECK_RETOBJ(pShape);
   *pShape = nullptr;

   auto shape = m_Polygon.CreateClippedShape(GetRect(pRect), WBFL::Geometry::Shape::ClipRegion::In);
   if (shape)
   {
      CComPtr<IPolyShape> polyShape;
      HRESULT hr = ::CreatePolyShape(shape.get(), &polyShape);
      if (FAILED(hr))
         return hr;

      polyShape->get_Shape(pShape);
   }
   return S_OK;
}

STDMETHODIMP CPolyShape::get_Perimeter(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Polygon.GetPerimeter();
   return S_OK;
}

STDMETHODIMP CPolyShape::FurthestDistance(ILine2d* line, Float64 *pVal)
{
   CHECK_IN(line);
   CHECK_RETVAL(pVal);
   *pVal = m_Polygon.GetFurthestDistance(GetLine(line),WBFL::Geometry::Line2d::Side::Right);
   return S_OK;
}

STDMETHODIMP CPolyShape::FurthestPoint(ILine2d* line, IPoint2d** ppPoint, Float64* dist)
{
   CHECK_IN(line);
   CHECK_RETOBJ(ppPoint);
   CHECK_RETVAL(dist);
   auto [point,fd] = m_Polygon.GetFurthestPoint(GetLine(line), WBFL::Geometry::Line2d::Side::Right);
   CreatePoint(point, ppPoint);
   *dist = fd;
   return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IXYPosition
/////////////////////////////////////////////////////////////////////////////

STDMETHODIMP CPolyShape::Offset(Float64 dx,Float64 dy)
{
   m_Polygon.Offset(dx, dy);
   return S_OK;
}

STDMETHODIMP CPolyShape::OffsetEx(ISize2d* pSize)
{
   CHECK_IN(pSize);

   Float64 dx, dy;
   pSize->Dimensions(&dx, &dy);
   return Offset(dx, dy);
}

STDMETHODIMP CPolyShape::get_LocatorPoint(LocatorPointType lp, IPoint2d** point)
{
   CHECK_RETOBJ(point);
   return CreatePoint(m_Polygon.GetLocatorPoint(WBFL::Geometry::Shape::LocatorPoint(lp)), point);
}

STDMETHODIMP CPolyShape::put_LocatorPoint(LocatorPointType lp, IPoint2d* point)
{
   CHECK_IN(point);
   m_Polygon.SetLocatorPoint(WBFL::Geometry::Shape::LocatorPoint(lp), ::GetPoint(point));
   return S_OK;
}

STDMETHODIMP CPolyShape::MoveEx(IPoint2d* pFrom,IPoint2d* pTo)
{
   CHECK_IN(pFrom);
   CHECK_IN(pTo);

   Float64 x1, y1;
   Float64 x2, y2;

   GetCoordinates(pFrom, &x1, &y1);
   GetCoordinates(pTo, &x2, &y2);

   Float64 dx, dy;
   dx = x2 - x1;
   dy = y2 - y1;

   return Offset(dx, dy);
}

STDMETHODIMP CPolyShape::RotateEx(IPoint2d* pPoint,Float64 angle)
{
   CHECK_IN(pPoint);
   m_Polygon.Rotate(::GetPoint(pPoint), angle);
   return S_OK;
}


STDMETHODIMP CPolyShape::Rotate(Float64 cx,Float64 cy,Float64 angle)
{
   m_Polygon.Rotate(cx, cy, angle);
   return S_OK;
}
