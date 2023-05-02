///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
// Copyright © 1999-2023  Washington State Department of Transportation
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

// CogoEngine.cpp : Implementation of CCogoEngine
#include "stdafx.h"
#include "WBFLCOGO.h"
#include "CogoEngine.h"
#include <WBFLCogo\CogoHelpers.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCogoEngine

HRESULT CCogoEngine::FinalConstruct()
{
   return S_OK;
}

STDMETHODIMP CCogoEngine::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ICogoEngine,
      &IID_IIntersect2,
      &IID_ILocate2,
      &IID_IMeasure2,
      &IID_IProject2,
      &IID_IDivide2,
      &IID_ITangent2,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CCogoEngine::get_Intersect(/*[out, retval]*/ IIntersect2* *pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface(IID_IIntersect2,(void**)pVal);
}

STDMETHODIMP CCogoEngine::get_Locate(/*[out, retval]*/ ILocate2* *pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface(IID_ILocate2,(void**)pVal);
}

STDMETHODIMP CCogoEngine::get_Measure(/*[out, retval]*/ IMeasure2* *pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface(IID_IMeasure2,(void**)pVal);
}

STDMETHODIMP CCogoEngine::get_Project(/*[out, retval]*/ IProject2* *pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface(IID_IProject2,(void**)pVal);
}

STDMETHODIMP CCogoEngine::get_Divide(/*[out, retval]*/ IDivide2* *pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface(IID_IDivide2,(void**)pVal);
}

STDMETHODIMP CCogoEngine::get_Tangent(/*[out, retval]*/ ITangent2* *pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface(IID_ITangent2,(void**)pVal);
}

STDMETHODIMP CCogoEngine::Angle(/*[in]*/ IPoint2d* from,/*[in]*/ IPoint2d* vertex,/*[in]*/ IPoint2d* to,/*[out,retval]*/ IAngle** angle)
{
   CHECK_IN(from);
   CHECK_IN(vertex);
   CHECK_IN(to);
   CHECK_RETOBJ(angle);

   auto pntFrom = cogoUtil::GetPoint(from);
   auto pntVertex = cogoUtil::GetPoint(vertex);
   auto pntTo = cogoUtil::GetPoint(to);
   return cogoUtil::CreateAngle(WBFL::COGO::Utilities::MeasureAngle(pntFrom, pntVertex, pntTo), angle);
}

STDMETHODIMP CCogoEngine::Area(/*[in]*/ IPoint2dCollection* points,/*[out,retval]*/ Float64* area)
{
   CHECK_IN(points);
   CHECK_RETVAL(area);

   std::vector<WBFL::Geometry::Point2d> vPoints;
   IndexType nPoints;
   points->get_Count(&nPoints);
   for (IndexType i = 0; i < nPoints; i++)
   {
      CComPtr<IPoint2d> pnt;
      points->get_Item(i, &pnt);
      auto point = cogoUtil::GetPoint(pnt);
      vPoints.emplace_back(point);
   }

   *area = WBFL::COGO::Utilities::MeasureArea(vPoints);
   return S_OK;
}

STDMETHODIMP CCogoEngine::Distance(/*[in]*/ IPoint2d* from,/*[in]*/ IPoint2d* to,/*[out,retval]*/ Float64* dist)
{
   CHECK_IN(from);
   CHECK_IN(to);
   CHECK_RETVAL(dist);

   auto pntFrom = cogoUtil::GetPoint(from);
   auto pntTo = cogoUtil::GetPoint(to);
   *dist = WBFL::COGO::Utilities::MeasureDistance(pntFrom, pntTo);
   return S_OK;
}

STDMETHODIMP CCogoEngine::Direction(/*[in]*/ IPoint2d* from,/*[in]*/ IPoint2d* to,/*[out,retval]*/ IDirection** dir)
{
   CHECK_RETOBJ(dir);
   auto pntFrom = cogoUtil::GetPoint(from);
   auto pntTo = cogoUtil::GetPoint(to);
   return cogoUtil::CreateDirection(WBFL::COGO::Utilities::MeasureDirection(pntFrom, pntTo), dir);
}

STDMETHODIMP CCogoEngine::Inverse(/*[in]*/ IPoint2d* from,/*[in]*/ IPoint2d* to,/*[out]*/ Float64* dist,/*[out]*/ IDirection** dir)
{
   CHECK_IN(from);
   CHECK_IN(to);
   CHECK_RETVAL(dist);
   CHECK_RETOBJ(dir);

   auto pntFrom = cogoUtil::GetPoint(from);
   auto pntTo = cogoUtil::GetPoint(to);

   WBFL::COGO::Direction direction;
   std::tie(*dist, direction) = WBFL::COGO::Utilities::ComputeInverse(pntFrom, pntTo);
   return cogoUtil::CreateDirection(direction, dir);
}

STDMETHODIMP CCogoEngine::ByDistAngle(/*[in]*/ IPoint2d* from,/*[in]*/ IPoint2d* to, /*[in]*/ Float64 dist, /*[in]*/ VARIANT varAngle, /*[in]*/ Float64 offset,/*[out,retval]*/IPoint2d** point)
{
   /////////////////////////////////////////////////
   // NOTE: This method is very similar to ByDistDefAngle
   //       If changes need to be made here, look at
   //       ByDistDefAngle because similar changes may need to
   //       be made there as well
   /////////////////////////////////////////////////

   CHECK_IN(from);
   CHECK_IN(to);
   CHECK_RETOBJ(point);

   auto pntFrom = cogoUtil::GetPoint(from);
   auto pntTo = cogoUtil::GetPoint(to);

   HRESULT hr;
   WBFL::COGO::Angle angle;
   std::tie(hr, angle) = cogoUtil::AngleFromVariant(varAngle);
   if (FAILED(hr)) return hr;
   return cogoUtil::CreatePoint(WBFL::COGO::Utilities::LocateByDistanceAndAngle(pntFrom, pntTo, dist, angle, offset), point);
}

STDMETHODIMP CCogoEngine::ByDistDefAngle(/*[in]*/ IPoint2d* from, /*[in]*/ IPoint2d* to, /*[in]*/ Float64 dist, /*[in]*/ VARIANT varDefAngle, /*[in]*/ Float64 offset, /*[out,retval]*/ IPoint2d** point)
{
   /////////////////////////////////////////////////
   // NOTE: This method is very similar to ByDistAngle
   //       If changes need to be made here, look at
   //       ByDistAngle because similar changes may need to
   //       be made there as well
   /////////////////////////////////////////////////

   CHECK_IN(from);
   CHECK_IN(to);
   CHECK_RETOBJ(point);

   auto pntFrom = cogoUtil::GetPoint(from);
   auto pntTo = cogoUtil::GetPoint(to);

   HRESULT hr;
   WBFL::COGO::Angle defAngle;
   std::tie(hr, defAngle) = cogoUtil::AngleFromVariant(varDefAngle);
   if (FAILED(hr)) return hr;
   return cogoUtil::CreatePoint(WBFL::COGO::Utilities::LocateByDistanceAndDeflectionAngle(pntFrom, pntTo, dist, defAngle, offset), point);
}

STDMETHODIMP CCogoEngine::ByDistDir(/*[in]*/ IPoint2d* from, /*[in]*/ Float64 dist, /*[in]*/ VARIANT varDir, /*[in]*/ Float64 offset,/*[out,retval]*/ IPoint2d** point)
{
   CHECK_IN(from);
   CHECK_RETOBJ(point);

   auto pntFrom = cogoUtil::GetPoint(from);

   HRESULT hr;
   WBFL::COGO::Direction direction;
   std::tie(hr, direction) = cogoUtil::DirectionFromVariant(varDir);
   if (FAILED(hr)) return hr;
   return cogoUtil::CreatePoint(WBFL::COGO::Utilities::LocateByDistanceAndDirection(pntFrom, dist, direction, offset), point);
}

STDMETHODIMP CCogoEngine::PointOnLine(/*[in]*/ IPoint2d* from, /*[in]*/ IPoint2d* to, /*[in]*/ Float64 dist, /*[in]*/ Float64 offset,/*[out,retval]*/ IPoint2d** point)
{
   CHECK_IN(from);
   CHECK_IN(to);
   CHECK_RETOBJ(point);

   auto pntFrom = cogoUtil::GetPoint(from);
   auto pntTo = cogoUtil::GetPoint(to);
   return cogoUtil::CreatePoint(WBFL::COGO::Utilities::LocatePointOnLine(pntFrom, pntTo, dist, offset), point);
}

STDMETHODIMP CCogoEngine::ParallelLineByPoints(/*[in]*/ IPoint2d* from,/*[in]*/ IPoint2d* to, /*[in]*/ Float64 offset,/*[out]*/IPoint2d** p1,/*[out]*/IPoint2d** p2)
{
   CHECK_IN(from);
   CHECK_IN(to);
   CHECK_RETOBJ(p1);
   CHECK_RETOBJ(p2);

   auto pntFrom = cogoUtil::GetPoint(from);
   auto pntTo = cogoUtil::GetPoint(to);

   WBFL::Geometry::Point2d pnt1, pnt2;
   std::tie(pnt1, pnt2) = WBFL::COGO::Utilities::LocateParallelLineByPoints(pntFrom, pntTo, offset);
   HRESULT hr1 = cogoUtil::CreatePoint(pnt1, p1);
   HRESULT hr2 = cogoUtil::CreatePoint(pnt2, p2);
   return (FAILED(hr1) || FAILED(hr2) ? E_FAIL : S_OK);
}

STDMETHODIMP CCogoEngine::ParallelLineSegment(/*[in]*/ ILineSegment2d* line,/*[in]*/ Float64 offset,/*[out,retval]*/ ILineSegment2d** linesegment)
{
   CHECK_IN(line);
   CHECK_RETOBJ(linesegment);

   auto ls = cogoUtil::GetLineSegment(line);
   return cogoUtil::CreateLineSegment(WBFL::COGO::Utilities::LocateParallelLineSegment(ls, offset), linesegment);
}

STDMETHODIMP CCogoEngine::Bearings(/*[in]*/ IPoint2d* p1, /*[in]*/ VARIANT varDir1, /*[in]*/ Float64 offset1,/*[in]*/ IPoint2d* p2, /*[in]*/ VARIANT varDir2, /*[in]*/ Float64 offset2, /*[out,retval]*/ IPoint2d** point)
{
   CHECK_IN(p1);
   CHECK_IN(p2);
   CHECK_RETOBJ(point);

   HRESULT hr;
   auto pnt1 = cogoUtil::GetPoint(p1);
   auto pnt2 = cogoUtil::GetPoint(p2);
   WBFL::COGO::Direction dir1, dir2;
   std::tie(hr, dir1) = cogoUtil::DirectionFromVariant(varDir1);
   if (FAILED(hr)) return hr;
   std::tie(hr, dir2) = cogoUtil::DirectionFromVariant(varDir2);
   if (FAILED(hr)) return hr;

   return cogoUtil::CreatePoint(WBFL::COGO::Utilities::IntersectBearings(pnt1, dir1, offset1, pnt2, dir2, offset2), point);
}

STDMETHODIMP CCogoEngine::BearingCircle(/*[in]*/ IPoint2d* pnt1, /*[in]*/ VARIANT varDir, /*[in]*/ Float64 offset,/*[in]*/ IPoint2d* pntCenter, /*[in]*/ Float64 radius, /*[in]*/ IPoint2d* pntNearest, /*[out,retval]*/ IPoint2d** point)
{
   CHECK_IN(pnt1);
   CHECK_IN(pntCenter);
   CHECK_IN(pntNearest);
   CHECK_RETOBJ(point);

   if ( radius <= 0.0 )
      return E_INVALIDARG;

   // Get the input data and validate
   HRESULT hr;
   WBFL::COGO::Direction direction;
   std::tie(hr, direction) = cogoUtil::DirectionFromVariant(varDir);

   auto p1 = cogoUtil::GetPoint(pnt1);
   auto pC = cogoUtil::GetPoint(pntCenter);
   auto pN = cogoUtil::GetPoint(pntNearest);

   return cogoUtil::CreatePoint(WBFL::COGO::Utilities::IntersectBearingAndCircle(p1, direction, offset, pC, radius, pN), point);
}

STDMETHODIMP CCogoEngine::Circles(/*[in]*/ IPoint2d* c1, /*[in]*/ Float64 r1, /*[in]*/ IPoint2d* c2, /*[in]*/ Float64 r2, /*[in]*/ IPoint2d* nearest, /*[out,retval]*/ IPoint2d** point)
{
   CHECK_IN(c1);
   CHECK_IN(c2);
   CHECK_IN(nearest);
   CHECK_RETOBJ(point);

   if ( r1 <= 0.0 || r2 <= 0.0 )
      return E_INVALIDARG;

   auto center1 = cogoUtil::GetPoint(c1);
   auto center2 = cogoUtil::GetPoint(c2);
   auto pntNearest = cogoUtil::GetPoint(nearest);

   return cogoUtil::CreatePoint(WBFL::COGO::Utilities::IntersectCircles(center1, r1, center2, r2, pntNearest), point);
}

STDMETHODIMP CCogoEngine::LineByPointsCircle(/*[in]*/ IPoint2d* pnt1, /*[in]*/ IPoint2d* pnt2, /*[in]*/ Float64 offset,/*[in]*/ IPoint2d* center, /*[in]*/ Float64 radius, /*[in]*/ IPoint2d* nearest, /*[out,retval]*/ IPoint2d** point)
{
   CHECK_IN(pnt1);
   CHECK_IN(pnt2);
   CHECK_IN(center);
   CHECK_IN(nearest);
   CHECK_RETOBJ(point);

   if ( radius <= 0.0 )
      return E_INVALIDARG;

   auto p1 = cogoUtil::GetPoint(pnt1);
   auto p2 = cogoUtil::GetPoint(pnt2);
   auto c = cogoUtil::GetPoint(center);
   auto n = cogoUtil::GetPoint(nearest);
   return cogoUtil::CreatePoint(WBFL::COGO::Utilities::IntersectLineByPointsAndCircle(p1, p2, offset, c, radius, n), point);
}

STDMETHODIMP CCogoEngine::LinesByPoints(/*[in]*/ IPoint2d* p11, /*[in]*/ IPoint2d* p12, /*[in]*/ Float64 offset1,/*[in]*/ IPoint2d* p21, /*[in]*/ IPoint2d* p22, /*[in]*/ Float64 offset2, /*[out,retval]*/ IPoint2d** point)
{
   CHECK_IN(p11);
   CHECK_IN(p12);
   CHECK_IN(p21);
   CHECK_IN(p22);
   CHECK_RETOBJ(point);

   auto pnt11 = cogoUtil::GetPoint(p11);
   auto pnt12 = cogoUtil::GetPoint(p12);
   auto pnt21 = cogoUtil::GetPoint(p21);
   auto pnt22 = cogoUtil::GetPoint(p22);

   return cogoUtil::CreatePoint(WBFL::COGO::Utilities::IntersectLinesByPoints(pnt11, pnt12, offset1, pnt21, pnt11, offset2), point);
}

STDMETHODIMP CCogoEngine::Lines(/*[in]*/ILineSegment2d* l1,/*[in]*/Float64 offset1,/*[in]*/ILineSegment2d* l2,/*[in]*/Float64 offset2,/*[out,retval]*/ IPoint2d** point)
{
   CHECK_IN(l1);
   CHECK_IN(l2);
   CHECK_RETOBJ(point);

   auto ls1 = cogoUtil::GetLineSegment(l1);
   auto ls2 = cogoUtil::GetLineSegment(l2);
   return cogoUtil::CreatePoint(WBFL::COGO::Utilities::IntersectLineSegments(ls1, offset1, ls2, offset2), point);
}

STDMETHODIMP CCogoEngine::LineSegmentCircle(/*[in]*/ ILineSegment2d* seg, /*[in]*/ Float64 offset,/*[in]*/ IPoint2d* center, /*[in]*/ Float64 radius, /*[in]*/ IPoint2d* nearest, /*[out,retval]*/ IPoint2d** point)
{
   CHECK_IN(seg);
   CHECK_IN(center);
   CHECK_IN(nearest);
   CHECK_RETOBJ(point);

   if ( radius <= 0 )
      return E_INVALIDARG;

   auto ls = cogoUtil::GetLineSegment(seg);
   auto c = cogoUtil::GetPoint(center);
   auto n = cogoUtil::GetPoint(nearest);

   return cogoUtil::CreatePoint(WBFL::COGO::Utilities::IntersectLineSegmentAndCircle(ls, offset, c, radius, n), point);
}

STDMETHODIMP CCogoEngine::PointOnLineByPoints(/*[in]*/ IPoint2d* pnt, /*[in]*/ IPoint2d* start, /*[in]*/ IPoint2d* end, /*[in]*/ Float64 offset,/*[out,retval]*/IPoint2d** point)
{
   CHECK_IN(pnt);
   CHECK_IN(start);
   CHECK_IN(end);
   CHECK_RETOBJ(point);

   auto p = cogoUtil::GetPoint(pnt);
   auto s = cogoUtil::GetPoint(start);
   auto e = cogoUtil::GetPoint(end);
   return cogoUtil::CreatePoint(WBFL::COGO::Utilities::ProjectPointOnLineByPoints(p, s, e, offset), point);
}

STDMETHODIMP CCogoEngine::PointOnLineSegment(/*[in]*/ IPoint2d* from,/*[in]*/ ILineSegment2d* seg, /*[in]*/ Float64 offset, /*[out,retval]*/ IPoint2d** point)
{
   CHECK_IN(from);
   CHECK_IN(seg);
   CHECK_RETOBJ(point);

   auto f = cogoUtil::GetPoint(from);
   auto ls = cogoUtil::GetLineSegment(seg);
   return cogoUtil::CreatePoint(WBFL::COGO::Utilities::ProjectPointOnLineSegment(f, ls, offset), point);
}

STDMETHODIMP CCogoEngine::Arc(/*[in]*/ IPoint2d* from, /*[in]*/ IPoint2d* vertex, /*[in]*/ IPoint2d* to,/*[in]*/ CollectionIndexType nParts,/*[out,retval]*/ IPoint2dCollection** points)
{
   CHECK_IN(from);
   CHECK_IN(vertex);
   CHECK_IN(to);
   CHECK_RETVAL(points);

   if ( nParts <= 1 )
      return E_INVALIDARG;

   auto f = cogoUtil::GetPoint(from);
   auto v = cogoUtil::GetPoint(vertex);
   auto t = cogoUtil::GetPoint(to);

   auto vPoints = WBFL::COGO::Utilities::DivideArc(f, v, t, nParts);

   CComPtr<IPoint2dCollection> pnts;
   pnts.CoCreateInstance(CLSID_Point2dCollection);
   for (auto& point : vPoints)
   {
      CComPtr<IPoint2d> p;
      cogoUtil::CreatePoint(point, &p);
      pnts->Add(p);
   }
   return pnts.CopyTo(points);
}

STDMETHODIMP CCogoEngine::BetweenPoints(/*[in]*/ IPoint2d* from, /*[in]*/ IPoint2d* to,/*[in]*/ CollectionIndexType nParts,/*[out,retval]*/ IPoint2dCollection** points)
{
   CHECK_IN(from);
   CHECK_IN(to);
   CHECK_RETOBJ(points);

   if ( nParts <= 1 )
      return E_INVALIDARG;

   auto f = cogoUtil::GetPoint(from);
   auto t = cogoUtil::GetPoint(to);
   auto vPoints = WBFL::COGO::Utilities::DivideBetweenPoints(f, t, nParts);

   CComPtr<IPoint2dCollection> pnts;
   pnts.CoCreateInstance(CLSID_Point2dCollection);
   for (auto& point : vPoints)
   {
      CComPtr<IPoint2d> p;
      cogoUtil::CreatePoint(point, &p);
      pnts->Add(p);
   }
   return pnts.CopyTo(points);
}

STDMETHODIMP CCogoEngine::LineSegment(/*[in]*/ ILineSegment2d* seg,/*[in]*/ CollectionIndexType nParts,/*[out,retval]*/ IPoint2dCollection** points)
{
   CHECK_IN(seg);
   CHECK_RETOBJ(points);

   if ( nParts <= 1 )
      return E_INVALIDARG;

   HRESULT hr;

   // Divide the line
   // The resulting collection contains the from and to points
   // Be sure not to add these points to the collection
   hr = seg->Divide(nParts,points);
   if ( FAILED(hr) )
      return hr;

   return S_OK;
}

STDMETHODIMP CCogoEngine::CompoundCurve(/*[in]*/ ICompoundCurve* curve, /*[in]*/ CollectionIndexType nParts, /*[out,retval]*/ IPoint2dCollection** points)
{
   CHECK_IN(curve);
   CHECK_RETOBJ(points);

   if ( nParts <= 1 )
      return E_INVALIDARG;

   HRESULT hr;

   // Divide the curve
   Float64 Lt; // Total length of curve
   curve->get_TotalLength(&Lt);

   hr = ::CoCreateInstance(CLSID_Point2dCollection,nullptr,CLSCTX_ALL,IID_IPoint2dCollection,(void**)points);
   ATLASSERT(SUCCEEDED(hr));

   CComQIPtr<IPathElement> element(curve);

   Float64 stepSize = Lt/nParts;
   Float64 currDist = stepSize;
   for ( CollectionIndexType i = 0; i < nParts-1; i++ )
   {
      CComPtr<IPoint2d> point;
      element->PointOnCurve(currDist,&point);

      (*points)->Add(point);

      currDist += stepSize;
   }

   return S_OK;
}

STDMETHODIMP CCogoEngine::Path(IPath* pPath,CollectionIndexType nParts,Float64 start,Float64 end,IPoint2dCollection** points)
{
   CHECK_IN(pPath);
   CHECK_RETOBJ(points);

   if ( nParts <= 1 )
      return E_INVALIDARG;

   HRESULT hr = ::CoCreateInstance(CLSID_Point2dCollection,nullptr,CLSCTX_ALL,IID_IPoint2dCollection,(void**)points);
   ATLASSERT(SUCCEEDED(hr));

   CComQIPtr<IPathElement> path_element(pPath);

   Float64 distance = end - start;
   Float64 stepSize = distance/nParts;
   Float64 location = stepSize + start;
   for ( CollectionIndexType i = 0; i < nParts-1; i++ )
   {
      CComPtr<IPoint2d> point;
      path_element->LocatePoint(location,omtNormal,0.0,CComVariant(0.00),&point);

      (*points)->Add(point);

      location += stepSize;
   }

   return S_OK;
}

STDMETHODIMP CCogoEngine::External(/*[in]*/ IPoint2d* center1, /*[in]*/ Float64 radius1,/*[in]*/ IPoint2d* center2, /*[in]*/ Float64 radius2, /*[in]*/ TangentSignType sign, /*[out]*/ IPoint2d** t1,/*[out]*/ IPoint2d** t2)
{
   // Check the radii
   if ( radius1 <= 0.0 )
      return E_INVALIDARG;

   if ( radius2 <= 0.0 )
      return E_INVALIDARG;

   auto c1 = cogoUtil::GetPoint(center1);
   auto c2 = cogoUtil::GetPoint(center2);
   WBFL::Geometry::Point2d pnt1, pnt2;
   std::tie(pnt1, pnt2) = WBFL::COGO::Utilities::ExternalTangents(c1, radius1, c2, radius2, WBFL::COGO::TangentSign(sign));
   HRESULT hr1 = cogoUtil::CreatePoint(pnt1, t1);
   HRESULT hr2 = cogoUtil::CreatePoint(pnt2, t2);
   return (FAILED(hr1) || FAILED(hr2) ? E_FAIL : S_OK);
}

STDMETHODIMP CCogoEngine::Cross(/*[in]*/ IPoint2d* center1, /*[in]*/ Float64 radius1,/*[in]*/ IPoint2d* center2, /*[in]*/ Float64 radius2, /*[in]*/ TangentSignType sign, /*[out]*/ IPoint2d** t1,/*[out]*/ IPoint2d** t2)
{
   CHECK_IN(center1);
   CHECK_IN(center2);
   CHECK_RETOBJ(t1);
   CHECK_RETOBJ(t2);

   // Check the radii
   if ( radius1 <= 0.0 )
      return E_INVALIDARG;

   if ( radius2 <= 0.0 )
      return E_INVALIDARG;

   auto c1 = cogoUtil::GetPoint(center1);
   auto c2 = cogoUtil::GetPoint(center2);
   WBFL::Geometry::Point2d pnt1, pnt2;
   std::tie(pnt1, pnt2) = WBFL::COGO::Utilities::CrossingTangents(c1, radius1, c2, radius2, WBFL::COGO::TangentSign(sign));
   HRESULT hr1 = cogoUtil::CreatePoint(pnt1, t1);
   HRESULT hr2 = cogoUtil::CreatePoint(pnt2, t2);
   return (FAILED(hr1) || FAILED(hr2) ? E_FAIL : S_OK);
}

STDMETHODIMP CCogoEngine::Point(/*[in]*/ IPoint2d* center, /*[in]*/ Float64 radius,/*[in]*/ IPoint2d* point, /*[in]*/ TangentSignType sign, /*[out]*/ IPoint2d** tangent)
{
   CHECK_IN(center);
   CHECK_IN(point);
   CHECK_RETOBJ(tangent);

   // Check the radii
   if ( radius <= 0.0 )
      return E_INVALIDARG;

   auto c = cogoUtil::GetPoint(center);
   auto p = cogoUtil::GetPoint(point);

   return cogoUtil::CreatePoint(WBFL::COGO::Utilities::TangentPoint(c, radius, p, WBFL::COGO::TangentSign(sign)), tangent);
}


