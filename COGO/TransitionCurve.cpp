///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry
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

// TransitionCurve.cpp : Implementation of CTransitionCurve
#include "stdafx.h"
#include "WBFLCOGO.h"
#include "TransitionCurve.h"
#include "Angle.h"
#include "Direction.h"
#include <WBFLCogo\CogoHelpers.h>
#include <WBFLGeometry\GeomHelpers.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CTransitionCurve
HRESULT CTransitionCurve::FinalConstruct()
{
   m_Curve = WBFL::COGO::TransitionCurve::Create();
   return S_OK;
}

void CTransitionCurve::FinalRelease()
{
}

STDMETHODIMP CTransitionCurve::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITransitionCurve,
      & IID_IPathElement,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

HRESULT CTransitionCurve::Init(IPoint2d* pStartPoint, VARIANT varStartDirection, Float64 R1, Float64 R2, Float64 L,TransitionCurveType type)
{
   ATLASSERT(!IsEqual(R1,R2)); // both can't same number
   ATLASSERT(!IsZero(L)); // curve must have a length

   HRESULT hr;
   WBFL::COGO::Direction startDirection;
   std::tie(hr, startDirection) = cogoUtil::DirectionFromVariant(varStartDirection);
   if (FAILED(hr)) return hr;

   auto startPoint = pStartPoint ? cogoUtil::GetPoint(pStartPoint) : WBFL::Geometry::Point2d(0, 0);;
   m_Curve->Init(startPoint, startDirection, R1, R2, L, WBFL::COGO::TransitionCurveType(type));
   return S_OK;
}

/////////////////////////////////////////////////////////////////
// ITransitionCurve
STDMETHODIMP CTransitionCurve::get_Type(TransitionCurveType* pType)
{
   CHECK_RETVAL(pType);
   *pType = TransitionCurveType(m_Curve->GetTransitionType());
   return S_OK;
}
STDMETHODIMP CTransitionCurve::get_R1(Float64* pR1)
{
   CHECK_RETVAL(pR1);
   *pR1 = m_Curve->GetStartRadius();
   return S_OK;
}

STDMETHODIMP CTransitionCurve::get_R2(Float64* pR2)
{
   CHECK_RETVAL(pR2);
   *pR2 = m_Curve->GetEndRadius();
   return S_OK;
}

STDMETHODIMP CTransitionCurve::GetRadius(Float64 distance, Float64* pRadius)
{
   CHECK_RETOBJ(pRadius);
   *pRadius = m_Curve->GetRadius(distance);
   return S_OK;
}

STDMETHODIMP CTransitionCurve::get_X(Float64* x)
{
   CHECK_RETVAL(x);
   *x = m_Curve->GetX();
   return S_OK;
}

STDMETHODIMP CTransitionCurve::get_Y(Float64* y)
{
   CHECK_RETVAL(y);
   *y = m_Curve->GetY();
   return S_OK;
}

STDMETHODIMP CTransitionCurve::get_LongTangent(Float64* u)
{
    CHECK_RETVAL(u);
    *u = m_Curve->GetLongTangent();
    return S_OK;
}

STDMETHODIMP CTransitionCurve::get_ShortTangent(Float64* v)
{
    CHECK_RETVAL(v);
    *v = m_Curve->GetShortTangent();
    return S_OK;
}

STDMETHODIMP CTransitionCurve::get_PI(IPoint2d** pPI)
{
   CHECK_RETOBJ(pPI);
   return cogoUtil::CreatePoint(m_Curve->GetPI(), pPI);
}

STDMETHODIMP CTransitionCurve::get_Angle(/*[out, retval]*/IAngle** ppAngle)
{
   CHECK_RETOBJ(ppAngle);
   return cogoUtil::CreateAngle(m_Curve->GetAngle(), ppAngle);
}

STDMETHODIMP CTransitionCurve::get_Direction(CurveDirectionType* dir)
{
   CHECK_RETVAL(dir);
   *dir = CurveDirectionType(m_Curve->GetCurveDirection());
   return S_OK;
}

STDMETHODIMP CTransitionCurve::get_StartDirection(/*[out, retval]*/IDirection** pStartDirection)
{
   CHECK_RETOBJ(pStartDirection);
   return cogoUtil::CreateDirection(m_Curve->GetStartDirection(), pStartDirection);
}

STDMETHODIMP CTransitionCurve::get_EndDirection(/*[out, retval]*/IDirection** pEndDirection)
{
   CHECK_RETOBJ(pEndDirection);
   return cogoUtil::CreateDirection(m_Curve->GetEndDirection(), pEndDirection);
}

STDMETHODIMP CTransitionCurve::DistanceFromStart(IPoint2d* point, Float64* dist)
{
   CHECK_IN(point);
   CHECK_RETVAL(dist);
   *dist = m_Curve->DistanceFromStart(cogoUtil::GetPoint(point));
   return S_OK;
}


// IPathElement
STDMETHODIMP CTransitionCurve::Clone(IPathElement** clone)
{
   CHECK_RETOBJ(clone);
   auto backing_clone = WBFL::COGO::TransitionCurve::Create(*m_Curve);
   return cogoUtil::CreatePathElement(backing_clone, clone);
}

STDMETHODIMP CTransitionCurve::Move(Float64 dist, VARIANT varDirection)
{
   HRESULT hr;
   WBFL::COGO::Direction direction;
   std::tie(hr, direction) = cogoUtil::DirectionFromVariant(varDirection);
   if (FAILED(hr)) return hr;

   m_Curve->Move(dist, direction);
   return S_OK;
}

STDMETHODIMP CTransitionCurve::Offset(Float64 dx, Float64 dy)
{
   m_Curve->Offset(dx, dy);
   return S_OK;
}

STDMETHODIMP CTransitionCurve::PointOnCurve(Float64 distanceFromStart, IPoint2d** point)
{
   CHECK_RETOBJ(point);
   return cogoUtil::CreatePoint(m_Curve->PointOnCurve(distanceFromStart), point);
}

STDMETHODIMP CTransitionCurve::GetStartPoint(IPoint2d** ppPoint)
{
   CHECK_RETOBJ(ppPoint);
   return cogoUtil::CreatePoint(m_Curve->GetStart(), ppPoint);
   return S_OK;
}

STDMETHODIMP CTransitionCurve::GetEndPoint(IPoint2d** ppPoint)
{
   CHECK_RETOBJ(ppPoint);
   return cogoUtil::CreatePoint(m_Curve->GetEnd(), ppPoint);
   return S_OK;
}

STDMETHODIMP CTransitionCurve::GetLength(Float64* pLength)
{
   CHECK_RETVAL(pLength);
   *pLength = m_Curve->GetLength();
   return S_OK;
}

STDMETHODIMP CTransitionCurve::GetKeyPoints(IPoint2dCollection** ppPoints)
{
   CHECK_RETOBJ(ppPoints);
   return cogoUtil::CreatePoints(m_Curve->GetKeyPoints(), ppPoints);
}

STDMETHODIMP CTransitionCurve::LocatePoint(Float64 distFromStart, OffsetMeasureType offsetType, Float64 offset, VARIANT varDirection, IPoint2d** ppPoint)
{
   CHECK_RETOBJ(ppPoint);

   HRESULT hr;
   WBFL::COGO::Direction direction;
   std::tie(hr, direction) = cogoUtil::DirectionFromVariant(varDirection);
   if (FAILED(hr)) return hr;

   return cogoUtil::CreatePoint(m_Curve->LocatePoint(distFromStart, WBFL::COGO::OffsetType(offsetType), offset, direction), ppPoint);
}

STDMETHODIMP CTransitionCurve::GetBearing(Float64 distance, IDirection** pVal)
{
   CHECK_RETOBJ(pVal);
   return cogoUtil::CreateDirection(m_Curve->GetBearing(distance), pVal);
}

STDMETHODIMP CTransitionCurve::GetNormal(Float64 distance, IDirection** pVal)
{
   CHECK_RETOBJ(pVal);
   return cogoUtil::CreateDirection(m_Curve->GetNormal(distance), pVal);
}

STDMETHODIMP CTransitionCurve::ProjectPoint(IPoint2d* point, IPoint2d** pNewPoint, Float64* pDistFromStart, VARIANT_BOOL* pvbOnProjection)
{
   CHECK_IN(point);
   CHECK_RETVAL(pDistFromStart);
   CHECK_RETVAL(pvbOnProjection);
   CHECK_RETOBJ(pNewPoint);

   WBFL::Geometry::Point2d newPoint;
   Float64 distFromStart;
   bool bOnProjection;
   std::tie(newPoint, distFromStart, bOnProjection) = m_Curve->ProjectPoint(cogoUtil::GetPoint(point));

   *pDistFromStart = distFromStart;
   *pvbOnProjection = (bOnProjection ? VARIANT_TRUE : VARIANT_FALSE);
   return cogoUtil::CreatePoint(newPoint, pNewPoint);
}

STDMETHODIMP CTransitionCurve::Intersect(ILine2d* pLine, VARIANT_BOOL bProjectBack, VARIANT_BOOL bProjectAhead, IPoint2dCollection** points)
{
   CHECK_IN(pLine);
   CHECK_RETOBJ(points);

   auto line = cogoUtil::GetLine(pLine);
   auto vIntersections = m_Curve->Intersect(line, bProjectBack == VARIANT_TRUE, bProjectAhead == VARIANT_TRUE);

   CComPtr<IPoint2dCollection> objPoints;
   objPoints.CoCreateInstance(CLSID_Point2dCollection);
   for (const auto& p : vIntersections)
   {
      CComPtr<IPoint2d> pnt;
      cogoUtil::CreatePoint(p, &pnt);
      objPoints->Add(pnt);
   }

   (*points) = objPoints;
   (*points)->AddRef();

   return S_OK;
}

STDMETHODIMP CTransitionCurve::CreateOffsetPath(Float64 offset, IPath** ppPath)
{
   CHECK_RETOBJ(ppPath);
   auto path_elements = m_Curve->CreateOffsetPath(offset);
   auto path = WBFL::COGO::Path::Create();
   for (auto& element : path_elements)
   {
      path->AddPathElement(element);
   }
   return cogoUtil::CreatePath(path, ppPath);
}

STDMETHODIMP CTransitionCurve::CreateSubpath(Float64 start, Float64 end, IPath** ppPath)
{
   CHECK_RETOBJ(ppPath);
   auto path_elements = m_Curve->CreateSubpath(start, end);
   auto path = WBFL::COGO::Path::Create();
   for (auto& element : path_elements)
   {
      path->AddPathElement(element);
   }
   return cogoUtil::CreatePath(path, ppPath);
}
