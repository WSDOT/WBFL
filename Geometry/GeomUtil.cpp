///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2024  Washington State Department of Transportation
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

// GeomUtil.cpp : Implementation of CGeomUtil
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "GeomUtil.h"
#include "Helper.h"
#include "Point2dCollection.h"
#include "Vector2d.h"
#include <MathEx.h>
#include <GeomModel/GeomOp2d.h>
#include <GeomModel/Arc.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGeomUtil

HRESULT CGeomUtil::FinalConstruct()
{
   HRESULT hr = S_OK;

   CComObject<CVector2d>* pVector;
   hr = CComObject<CVector2d>::CreateInstance( &pVector );
   if ( FAILED(hr) )
      return hr;
   m_Vector = pVector;

   return S_OK;
}

STDMETHODIMP CGeomUtil::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
      &IID_IGeomUtil,
		&IID_IGeomUtil2d,
	};
	for (int i = 0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

/////////////////////////////////////////////////////////////////////
// IGeomUtil
//

STDMETHODIMP CGeomUtil::get_Geom2d(IGeomUtil2d** util)
{
   CHECK_RETOBJ(util);
   return QueryInterface( IID_IGeomUtil2d, (void**)util );
}

/////////////////////////////////////////////////////////////////////
// IGeomUtil2d
//
STDMETHODIMP CGeomUtil::GenerateCircle(IndexType numPoints, IPoint2d *center, Float64 radius, Float64 initAngle, IPoint2dCollection **points)
{
   if ( numPoints < 0 || numPoints == INVALID_INDEX || center == nullptr || radius < 0 )
      return E_INVALIDARG;

   CHECK_RETOBJ(points);

   std::vector<WBFL::Geometry::Point2d> vPoints;
   WBFL::Geometry::GeometricOperations::GenerateCircle(numPoints, GetPoint(center), radius, initAngle, &vPoints);
   return CreatePointCollection(vPoints, points);
}

STDMETHODIMP CGeomUtil::Angle(IPoint2d* pStart,IPoint2d* pCenter,IPoint2d* pEnd,Float64* angle)
{
   CHECK_IN(pStart);
   CHECK_IN(pCenter);
   CHECK_IN(pEnd);
   CHECK_RETVAL(angle);

   try
   {
      *angle = WBFL::Geometry::GeometricOperations::Angle(GetPoint(pStart), GetPoint(pCenter), GetPoint(pEnd));
   }
   catch (...)
   {
      return Error(IDS_E_SAMEPOINTS, IID_IGeomUtil2d, GEOMETRY_E_SAMEPOINTS);
   }
   return S_OK;
}

STDMETHODIMP CGeomUtil::DivideArc(IPoint2d* pStart,IPoint2d* pCenter,IPoint2d* pEnd,IndexType nSpaces,IPoint2dCollection** ppPoints)
{
   CHECK_IN(pStart);
   CHECK_IN(pCenter);
   CHECK_IN(pEnd);
   CHECK_RETOBJ(ppPoints);

   std::vector<WBFL::Geometry::Point2d> points;
   try
   {
      WBFL::Geometry::Arc arc(GetPoint(pStart), GetPoint(pCenter), GetPoint(pEnd));
      points = arc.Divide(nSpaces);
   }
   catch (...)
   {
      return E_INVALIDARG;
   }

   return CreatePointCollection(points, ppPoints);
}

STDMETHODIMP CGeomUtil::SegSegIntersect(ILineSegment2d* pSeg1,ILineSegment2d* pSeg2,IPoint2d** ppPoint)
{
   CHECK_IN(pSeg1);
   CHECK_IN(pSeg2);
   CHECK_RETOBJ(ppPoint); // ppPoint is now Nothing
   *ppPoint = nullptr;
   WBFL::Geometry::Point2d intersection;
   Int16 result = WBFL::Geometry::GeometricOperations::Intersect(GetLineSegment(pSeg1), GetLineSegment(pSeg2),&intersection);
   if (result == 1)
   {
      return CreatePoint(intersection, ppPoint);
   }
   return S_FALSE;
}

STDMETHODIMP CGeomUtil::LineLineIntersect(ILine2d* l, ILine2d *m, IPoint2d **ppPoint)
{
   CHECK_IN(l);
   CHECK_IN(m);
   CHECK_RETOBJ(ppPoint);

   *ppPoint = nullptr;

   WBFL::Geometry::Point2d intersection;
   Int16 result = WBFL::Geometry::GeometricOperations::Intersect(GetLine(l), GetLine(m), &intersection);
   if (result == 1)
      return CreatePoint(intersection, ppPoint);
   else
      return S_FALSE;
}

STDMETHODIMP CGeomUtil::IntersectLineWithLineSegment(ILine2d* pLine,ILineSegment2d* pSeg,IPoint2d** ppPoint)
{
   CHECK_IN(pLine);
   CHECK_IN(pSeg);
   CHECK_RETOBJ(ppPoint); // Point is Nothing

   *ppPoint = nullptr;
   WBFL::Geometry::Point2d intersection;
   Int16 result = WBFL::Geometry::GeometricOperations::Intersect(GetLine(pLine), GetLineSegment(pSeg), &intersection);
   if (result == 1)
      return CreatePoint(intersection, ppPoint);
   else
      return S_FALSE;
}

STDMETHODIMP CGeomUtil::ShortestOffsetToPoint( ILine2d* pLine, IPoint2d* pPoint, Float64* pOffset)
{
   CHECK_IN(pLine);
   CHECK_IN(pPoint);
   CHECK_RETVAL(pOffset);

   *pOffset = WBFL::Geometry::GeometricOperations::ShortestOffsetToPoint(GetLine(pLine), GetPoint(pPoint));

   return S_OK;
}

STDMETHODIMP CGeomUtil::IsLineParallelToLineSegment(ILine2d* pLine,ILineSegment2d* pSeg,VARIANT_BOOL* pbResult)
{
   CHECK_IN(pLine);
   CHECK_IN(pSeg);
   CHECK_RETVAL(pbResult);

   *pbResult = MakeBool(WBFL::Geometry::GeometricOperations::IsParallel(GetLine(pLine), GetLineSegment(pSeg)));
   return S_OK;
}

STDMETHODIMP CGeomUtil::AreLinesParallel(ILine2d* pLine1,ILine2d* pLine2,VARIANT_BOOL* pbResult)
{
   CHECK_IN(pLine1);
   CHECK_IN(pLine2);
   CHECK_RETVAL(pbResult);

   *pbResult = MakeBool(WBFL::Geometry::GeometricOperations::IsParallel(GetLine(pLine1), GetLine(pLine2)));
   return S_OK;
}

STDMETHODIMP CGeomUtil::IsSameDirection(ILine2d* pLine1, ILine2d* pLine2, VARIANT_BOOL* pbResult)
{
   CHECK_IN(pLine1);
   CHECK_IN(pLine2);
   CHECK_RETVAL(pbResult);

   *pbResult = MakeBool(WBFL::Geometry::GeometricOperations::SameDirection(GetLine(pLine1), GetLine(pLine2)));
   return S_OK;
}

STDMETHODIMP CGeomUtil::AreLineSegmentsParallel(ILineSegment2d* pSeg1,ILineSegment2d* pSeg2,VARIANT_BOOL* pbResult)
{
   CHECK_IN(pSeg1);
   CHECK_IN(pSeg2);
   CHECK_RETVAL(pbResult);

   *pbResult = MakeBool(WBFL::Geometry::GeometricOperations::IsParallel(GetLineSegment(pSeg1), GetLineSegment(pSeg2)));
   return S_OK;
}

STDMETHODIMP CGeomUtil::CreateParallelLine(ILine2d* pLine,Float64 dist,ILine2d** ppLine)
{
   CHECK_IN(pLine);
   CHECK_RETOBJ(ppLine);

   return CreateLine(WBFL::Geometry::GeometricOperations::CreateParallelLine(GetLine(pLine), dist), ppLine);
}

STDMETHODIMP CGeomUtil::CreateParallelLineThroughPoint(ILine2d* pLine,IPoint2d* pPoint,ILine2d** ppLine)
{
   CHECK_IN(pLine);
   CHECK_IN(pPoint);
   CHECK_RETOBJ(ppLine);

   return CreateLine(WBFL::Geometry::GeometricOperations::CreateParallelLineThroughPoint(GetLine(pLine), GetPoint(pPoint)),ppLine);
}

STDMETHODIMP CGeomUtil::PointOnLineNearest(ILine2d* pLine,IPoint2d* pPoint, IPoint2d** ppPOLN)
{
   CHECK_IN(pLine);
   CHECK_IN(pPoint);
   CHECK_RETOBJ(ppPOLN);

   return CreatePoint(WBFL::Geometry::GeometricOperations::PointOnLineNearest(GetLine(pLine), GetPoint(pPoint)), ppPOLN);
}

STDMETHODIMP CGeomUtil::CreateNormalLineThroughPoint(ILine2d* pLine, IPoint2d* pPoint, ILine2d** ppLine)
{
   CHECK_IN(pLine);
   CHECK_IN(pPoint);
   CHECK_RETOBJ(ppLine);

   return CreateLine(WBFL::Geometry::GeometricOperations::CreateNormalLineThroughPoint(GetLine(pLine), GetPoint(pPoint)), ppLine);
}

STDMETHODIMP CGeomUtil::CreateParallelLineSegment(ILineSegment2d* pSeg,Float64 offset,ILineSegment2d** pNewSeg)
{
   CHECK_IN(pSeg);
   CHECK_RETOBJ(pNewSeg);
   return CreateLineSegment(WBFL::Geometry::GeometricOperations::CreateParallelLineSegment(GetLineSegment(pSeg), offset),pNewSeg);
   return S_OK;
}

STDMETHODIMP CGeomUtil::LineCircleIntersect(ILine2d *line, ICircle *circle, IPoint2d** p1, IPoint2d** p2, short *nIntersect)
{
   CHECK_IN(line);
   CHECK_IN(circle);
   CHECK_RETOBJ(p1);
   CHECK_RETOBJ(p2);
   CHECK_RETVAL(nIntersect);

   *p1 = nullptr;
   *p2 = nullptr;

   WBFL::Geometry::Point2d pnt1, pnt2;
   *nIntersect = WBFL::Geometry::GeometricOperations::Intersect(GetLine(line), GetCircle(circle), &pnt1, &pnt2);
   if (*nIntersect == 1)
   {
      CreatePoint(pnt1, p1);
   }
   else if (*nIntersect == 2)
   {
      CreatePoint(pnt1, p1);
      CreatePoint(pnt2, p2);
   }

   return S_OK;
}

// Finds the intersection of two circles. A return value of 3 indicates the circles
// are identical and intersect at all points along the circle
STDMETHODIMP CGeomUtil::CircleCircleIntersect(ICircle* circle1,ICircle* circle2,IPoint2d** p1,IPoint2d** p2,short* nIntersect)
{
   CHECK_IN(circle1);
   CHECK_IN(circle2);
   CHECK_RETOBJ(p1);
   CHECK_RETOBJ(p2);
   CHECK_RETVAL(nIntersect);

   *p1 = nullptr;
   *p2 = nullptr;

   WBFL::Geometry::Point2d pnt1, pnt2;
   *nIntersect = WBFL::Geometry::GeometricOperations::Intersect(GetCircle(circle1), GetCircle(circle2), &pnt1, &pnt2);

   if (*nIntersect == 1)
   {
      CreatePoint(pnt1, p1);
   }
   else if (*nIntersect == 2)
   {
      CreatePoint(pnt1, p1);
      CreatePoint(pnt2, p2);
   }

   return S_OK;
}

STDMETHODIMP CGeomUtil::PointInTriangle(IPoint2d* p,IPoint2d* pA,IPoint2d* pB,IPoint2d* pC,VARIANT_BOOL* pbResult)
{
   CHECK_IN(p);
   CHECK_IN(pA);
   CHECK_IN(pB);
   CHECK_IN(pC);
   CHECK_RETVAL(pbResult);
   try
   {
      *pbResult = MakeBool(WBFL::Geometry::GeometricOperations::IsPointInTriangle(GetPoint(p), GetPoint(pA), GetPoint(pB), GetPoint(pC)));
   }
   catch (...)
   {
      return E_INVALIDARG;
   }

   return S_OK;
}
