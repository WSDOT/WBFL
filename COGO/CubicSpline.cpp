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

// CubicSpline.cpp : Implementation of CCubicSpline
#include "stdafx.h"
#include "WBFLCOGO.h"
#include "CubicSpline.h"

#include <WBFLCogo\CogoHelpers.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCubicSpline

STDMETHODIMP CCubicSpline::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ICubicSpline,
      &IID_IPathElement,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
      {
			return S_OK;
      }
	}
	return S_FALSE;
}

HRESULT CCubicSpline::FinalConstruct()
{
   m_Curve = WBFL::COGO::CubicSpline::Create();
   return S_OK;
}

void CCubicSpline::FinalRelease()
{
}

// ICubicSpline
STDMETHODIMP CCubicSpline::AddPoints(IPoint2dCollection* points)
{
   CHECK_IN(points);

   IndexType nPoints;
   points->get_Count(&nPoints);
   for ( IndexType i = 0; i < nPoints; i++ )
   {
      CComPtr<IPoint2d> p;
      points->get_Item(i,&p);

      Float64 x, y; p->Location(&x, &y);

      m_Curve->AddPoint(x, y);
   }

   return S_OK;
}

STDMETHODIMP CCubicSpline::AddPoint(Float64 x,Float64 y)
{
   m_Curve->AddPoint(x, y);
   return S_OK;
}

STDMETHODIMP CCubicSpline::AddPointEx(IPoint2d* point)
{
   CHECK_IN(point);

   Float64 x, y; point->Location(&x, &y);
   m_Curve->AddPoint(x, y);
   return S_OK;
}

STDMETHODIMP CCubicSpline::get_PointCount(IndexType* nPoints)
{
   CHECK_RETVAL(nPoints);
   *nPoints = m_Curve->GetPointCount();
   return S_OK;
}

STDMETHODIMP CCubicSpline::get_Point(IndexType idx,IPoint2d** point)
{
   return cogoUtil::CreatePoint(m_Curve->GetPoint(idx), point);
}

STDMETHODIMP CCubicSpline::get_Points(IPoint2dCollection** ppPoints)
{
   CHECK_RETOBJ(ppPoints);

   CComPtr<IPoint2dCollection> points;
   points.CoCreateInstance(CLSID_Point2dCollection);

   const auto& vPoints = m_Curve->GetPoints();
   for (const auto& p : vPoints)
   {
      CComPtr<IPoint2d> newPoint;
      newPoint.CoCreateInstance(CLSID_Point2d);
      newPoint->Move(p.X(), p.Y());
      points->Add(newPoint);
   }

   (*ppPoints) = points;
   (*ppPoints)->AddRef();
   return S_OK;
}

STDMETHODIMP CCubicSpline::Clear()
{
   m_Curve->Clear();
   return S_OK;
}

STDMETHODIMP CCubicSpline::put_StartDirection(VARIANT varDirection)
{
   auto [hr, direction] = cogoUtil::DirectionFromVariant(varDirection);
   if (FAILED(hr)) return hr;

   m_Curve->SetStartDirection(direction);
   return S_OK;
}

STDMETHODIMP CCubicSpline::get_StartDirection(IDirection** dir)
{
   return cogoUtil::CreateDirection(m_Curve->GetStartDirection(), dir);
}

STDMETHODIMP CCubicSpline::put_EndDirection( VARIANT varDirection)
{
   auto [hr, direction] = cogoUtil::DirectionFromVariant(varDirection);
   if (FAILED(hr)) return hr;

   m_Curve->SetEndDirection(direction);
   return S_OK;
}

STDMETHODIMP CCubicSpline::get_EndDirection(IDirection** dir)
{
   return cogoUtil::CreateDirection(m_Curve->GetEndDirection(), dir);
}

STDMETHODIMP CCubicSpline::BearingAtPoint(IndexType idx,IDirection** pDir)
{
   CHECK_RETVAL(pDir);
   return cogoUtil::CreateDirection(m_Curve->GetBearingAtPoint(idx), pDir);
}

STDMETHODIMP CCubicSpline::NormalAtPoint(IndexType idx,IDirection** pDir)
{
   CHECK_RETVAL(pDir);
   return cogoUtil::CreateDirection(m_Curve->GetNormalAtPoint(idx), pDir);
}

STDMETHODIMP CCubicSpline::DistanceFromStartAtPoint(IndexType idx,Float64* dist)
{
   CHECK_RETVAL(dist);
   *dist = m_Curve->DistanceFromStartAtPoint(idx);
   return S_OK;
}

// IPathElement
STDMETHODIMP CCubicSpline::Clone(IPathElement** clone)
{
   CHECK_RETOBJ(clone);
   auto backing_clone = WBFL::COGO::CubicSpline::Create(*m_Curve);
   return cogoUtil::CreatePathElement(backing_clone, clone);
}

STDMETHODIMP CCubicSpline::Move(Float64 dist, VARIANT varDirection)
{
   auto [hr, direction] = cogoUtil::DirectionFromVariant(varDirection);
   if (FAILED(hr)) return hr;

   m_Curve->Move(dist, direction);
   return S_OK;
}

STDMETHODIMP CCubicSpline::Offset(Float64 dx, Float64 dy)
{
   m_Curve->Offset(dx, dy);
   return S_OK; 
}

STDMETHODIMP CCubicSpline::PointOnCurve(Float64 distance, IPoint2d** pVal)
{
   CHECK_RETOBJ(pVal);
   return cogoUtil::CreatePoint(m_Curve->PointOnCurve(distance), pVal);
}

STDMETHODIMP CCubicSpline::GetStartPoint(IPoint2d** ppPoint)
{
   CHECK_RETOBJ(ppPoint);
   return cogoUtil::CreatePoint(m_Curve->GetStartPoint(), ppPoint);
}

STDMETHODIMP CCubicSpline::GetEndPoint(IPoint2d** ppPoint)
{
   CHECK_RETOBJ(ppPoint);
   return cogoUtil::CreatePoint(m_Curve->GetEndPoint(), ppPoint);
}

STDMETHODIMP CCubicSpline::GetLength(Float64* pLength)
{
   CHECK_RETVAL(pLength);
   *pLength = m_Curve->GetLength();
   return S_OK;
}

STDMETHODIMP CCubicSpline::GetKeyPoints(IPoint2dCollection** ppPoints)
{
   CHECK_RETOBJ(ppPoints);
   return cogoUtil::CreatePoints(m_Curve->GetKeyPoints(), ppPoints);
}

STDMETHODIMP CCubicSpline::LocatePoint(Float64 distFromStart, OffsetMeasureType offsetType, Float64 offset, VARIANT varDirection, IPoint2d** ppPoint)
{
   CHECK_RETOBJ(ppPoint);

   auto [hr, direction] = cogoUtil::DirectionFromVariant(varDirection);
   if (FAILED(hr)) return hr;


   return cogoUtil::CreatePoint(m_Curve->LocatePoint(distFromStart, WBFL::COGO::OffsetType(offsetType), offset, direction), ppPoint);
}

STDMETHODIMP CCubicSpline::GetBearing(Float64 distance, IDirection** pVal)
{
   CHECK_RETOBJ(pVal);
   return cogoUtil::CreateDirection(m_Curve->GetBearing(distance), pVal);
}

STDMETHODIMP CCubicSpline::GetNormal(Float64 distance, IDirection** pVal)
{
   CHECK_RETVAL(pVal);
   return cogoUtil::CreateDirection(m_Curve->GetNormal(distance), pVal);
}

STDMETHODIMP CCubicSpline::ProjectPoint(IPoint2d* point, IPoint2d** pNewPoint, Float64* pDistFromStart, VARIANT_BOOL* pvbOnProjection)
{
   CHECK_IN(point);
   CHECK_RETVAL(pDistFromStart);
   CHECK_RETVAL(pvbOnProjection);
   CHECK_RETOBJ(pNewPoint);

   auto [newPoint, distFromStart, bOnProjection] = m_Curve->ProjectPoint(cogoUtil::GetPoint(point));

   *pDistFromStart = distFromStart;
   *pvbOnProjection = (bOnProjection ? VARIANT_TRUE : VARIANT_FALSE);
   return cogoUtil::CreatePoint(newPoint, pNewPoint);
}

STDMETHODIMP CCubicSpline::Intersect(ILine2d* pLine, VARIANT_BOOL bProjectBack, VARIANT_BOOL bProjectAhead, IPoint2dCollection** points)
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

STDMETHODIMP CCubicSpline::CreateOffsetPath(Float64 offset, IPath** ppPath)
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

STDMETHODIMP CCubicSpline::CreateSubpath(Float64 start, Float64 end, IPath** ppPath)
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
