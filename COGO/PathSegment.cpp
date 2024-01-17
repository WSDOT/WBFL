///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
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

// PathSegment.cpp : Implementation of CPathSegment
#include "stdafx.h"
#include "WBFLCOGO.h"
#include "PathSegment.h"
#include <WBFLCogo\CogoHelpers.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPathSegment
HRESULT CPathSegment::FinalConstruct()
{
   m_Curve = WBFL::COGO::PathSegment::Create();
   return S_OK;
}

void CPathSegment::FinalRelease()
{
}

STDMETHODIMP CPathSegment::InterfaceSupportsErrorInfo(REFIID riid)
{
   static const IID* arr[] = 
   {
      &IID_IPathSegment,
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

STDMETHODIMP CPathSegment::ThroughPoints(IPoint2d* pStart, IPoint2d* pEnd)
{
   CHECK_IN(pStart);
   CHECK_IN(pEnd);
   m_Curve->ThroughPoints(cogoUtil::GetPoint(pStart), cogoUtil::GetPoint(pEnd));
   return S_OK;
}

STDMETHODIMP CPathSegment::Offset(Float64 offset)
{
   m_Curve->Offset(offset);
   return S_OK;
}

STDMETHODIMP CPathSegment::Clone(IPathElement** clone)
{
   CHECK_RETOBJ(clone);
   auto backing_clone = WBFL::COGO::PathSegment::Create(*m_Curve);
   return cogoUtil::CreatePathElement(backing_clone, clone);
}

STDMETHODIMP CPathSegment::Move(Float64 dist, VARIANT varDirection)
{
   auto [hr, direction] = cogoUtil::DirectionFromVariant(varDirection);
   if (FAILED(hr)) return hr;

   m_Curve->Move(dist, direction);
   return S_OK;
}

STDMETHODIMP CPathSegment::Offset(Float64 dx, Float64 dy)
{
   m_Curve->Offset(dx, dy);
   return S_OK;
}

STDMETHODIMP CPathSegment::PointOnCurve(Float64 distance, IPoint2d** pVal)
{
   CHECK_RETOBJ(pVal);
   return cogoUtil::CreatePoint(m_Curve->PointOnCurve(distance), pVal);
}

STDMETHODIMP CPathSegment::GetStartPoint(IPoint2d** ppPoint)
{
   CHECK_RETOBJ(ppPoint);
   return cogoUtil::CreatePoint(m_Curve->GetStartPoint(), ppPoint);
}

STDMETHODIMP CPathSegment::GetEndPoint(IPoint2d** ppPoint)
{
   CHECK_RETOBJ(ppPoint);
   return cogoUtil::CreatePoint(m_Curve->GetEndPoint(), ppPoint);
}

STDMETHODIMP CPathSegment::GetLength(Float64* pLength)
{
   CHECK_RETVAL(pLength);
   *pLength = m_Curve->GetLength();
   return S_OK;
}

STDMETHODIMP CPathSegment::GetKeyPoints(IPoint2dCollection** ppPoints)
{
   CHECK_RETOBJ(ppPoints);
   return cogoUtil::CreatePoints(m_Curve->GetKeyPoints(), ppPoints);
}

STDMETHODIMP CPathSegment::LocatePoint(Float64 distFromStart, OffsetMeasureType offsetType, Float64 offset, VARIANT varDirection, IPoint2d** ppPoint)
{
   CHECK_RETOBJ(ppPoint);

   auto [hr, direction] = cogoUtil::DirectionFromVariant(varDirection);
   if (FAILED(hr)) return hr;

   return cogoUtil::CreatePoint(m_Curve->LocatePoint(distFromStart, WBFL::COGO::OffsetType(offsetType), offset, direction), ppPoint);
}

STDMETHODIMP CPathSegment::GetBearing(Float64 distFromStart, IDirection** ppDirection)
{
   CHECK_RETOBJ(ppDirection);
   return cogoUtil::CreateDirection(m_Curve->GetBearing(distFromStart), ppDirection);
}

STDMETHODIMP CPathSegment::GetNormal(Float64 distFromStart, IDirection** ppNormal)
{
   CHECK_RETOBJ(ppNormal);
   return cogoUtil::CreateDirection(m_Curve->GetNormal(distFromStart), ppNormal);
}

STDMETHODIMP CPathSegment::ProjectPoint(IPoint2d* point, IPoint2d** ppProjPoint, Float64* pDistFromStart, VARIANT_BOOL* pvbOnProjection)
{
   CHECK_IN(point);
   CHECK_RETOBJ(ppProjPoint);
   CHECK_RETVAL(pDistFromStart);
   CHECK_RETVAL(pvbOnProjection);

   auto [prjPoint, distFromStart, bOnProjection] = m_Curve->ProjectPoint(cogoUtil::GetPoint(point));
   *pDistFromStart = distFromStart;
   *pvbOnProjection = (bOnProjection ? VARIANT_TRUE : VARIANT_FALSE);
   return cogoUtil::CreatePoint(prjPoint, ppProjPoint);
}

STDMETHODIMP CPathSegment::Intersect(ILine2d* pLine, VARIANT_BOOL vbProjectBack, VARIANT_BOOL vbProjectAhead, IPoint2dCollection** ppPoints)
{
   CHECK_IN(pLine);
   CHECK_RETOBJ(ppPoints);

   auto vPoints = m_Curve->Intersect(cogoUtil::GetLine(pLine), vbProjectBack == VARIANT_TRUE, vbProjectAhead == VARIANT_TRUE);
   CComPtr<IPoint2dCollection> points;
   points.CoCreateInstance(CLSID_Point2dCollection);
   for (auto& point : vPoints)
   {
      CComPtr<IPoint2d> pnt;
      cogoUtil::CreatePoint(point, &pnt);
      points->Add(pnt);
   }

   points.CopyTo(ppPoints);
   return S_OK;
}

STDMETHODIMP CPathSegment::CreateOffsetPath(Float64 offset, IPath** ppPath)
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

STDMETHODIMP CPathSegment::CreateSubpath(Float64 start, Float64 end, IPath** ppPath)
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
