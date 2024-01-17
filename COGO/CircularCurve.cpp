///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry
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

// CircularCurve.cpp : Implementation of CCircularCurve
#include "stdafx.h"
#include "WBFLCOGO.h"
#include "CircularCurve.h"
#include <WBFLCogo\CogoHelpers.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCircularCurve
HRESULT CCircularCurve::FinalConstruct()
{
   m_Curve = WBFL::COGO::CircularCurve::Create();
   return S_OK;
}

void CCircularCurve::FinalRelease()
{
}

STDMETHODIMP CCircularCurve::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ICircularCurve,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CCircularCurve::get_PBT(IPoint2d **pVal)
{
   CHECK_RETOBJ(pVal);
   return cogoUtil::CreatePoint(m_Curve->GetPBT(), pVal);
}

STDMETHODIMP CCircularCurve::put_PBT(IPoint2d *newVal)
{
   CHECK_IN(newVal);
   m_Curve->SetPBT(cogoUtil::GetPoint(newVal));
	return S_OK;
}

STDMETHODIMP CCircularCurve::get_PI(IPoint2d **pVal)
{
   CHECK_RETOBJ(pVal);
   return cogoUtil::CreatePoint(m_Curve->GetPI(), pVal);
}

STDMETHODIMP CCircularCurve::put_PI(IPoint2d *newVal)
{
   CHECK_IN(newVal);
   m_Curve->SetPI(cogoUtil::GetPoint(newVal));
	return S_OK;
}

STDMETHODIMP CCircularCurve::get_PFT(IPoint2d **pVal)
{
   CHECK_RETOBJ(pVal);
   return cogoUtil::CreatePoint(m_Curve->GetPFT(), pVal);
}

STDMETHODIMP CCircularCurve::put_PFT(IPoint2d *newVal)
{
   CHECK_IN(newVal);
   m_Curve->SetPFT(cogoUtil::GetPoint(newVal));
	return S_OK;
}

STDMETHODIMP CCircularCurve::get_Radius(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Curve->GetRadius();
   return S_OK;
}

STDMETHODIMP CCircularCurve::put_Radius(Float64 newVal)
{
   if ( newVal <= 0 )
      return E_INVALIDARG;

   m_Curve->SetRadius(newVal);

   return S_OK;
}

STDMETHODIMP CCircularCurve::get_PC(IPoint2d** pVal)
{
    CHECK_RETOBJ(pVal);
    return cogoUtil::CreatePoint(m_Curve->GetPC(),pVal);
}

STDMETHODIMP CCircularCurve::get_PT(IPoint2d** pVal)
{
    CHECK_RETOBJ(pVal);
    return cogoUtil::CreatePoint(m_Curve->GetPT(), pVal);
    return S_OK;
}

STDMETHODIMP CCircularCurve::get_FwdTangentBrg(IDirection **pVal)
{
   CHECK_RETOBJ(pVal);
   return cogoUtil::CreateDirection(m_Curve->GetForwardTangentBearing(), pVal);
	return S_OK;
}

STDMETHODIMP CCircularCurve::get_BkTangentBrg(IDirection **pVal)
{
   CHECK_RETOBJ(pVal);
   return cogoUtil::CreateDirection(m_Curve->GetBackTangentBearing(), pVal);
}

STDMETHODIMP CCircularCurve::get_Angle(IAngle* *pVal)
{
   // Total curve angle
   CHECK_RETOBJ(pVal);
   return cogoUtil::CreateAngle(m_Curve->GetAngle(), pVal);
}

STDMETHODIMP CCircularCurve::get_TangentLength(Float64* t)
{
   CHECK_RETVAL(t);
   *t = m_Curve->GetTangent();
   return S_OK;
}

STDMETHODIMP CCircularCurve::get_Chord(Float64* chord)
{
   CHECK_RETVAL(chord);
   *chord = m_Curve->GetChord();
   return S_OK;
}


STDMETHODIMP CCircularCurve::get_Tangent(Float64* tangent)
{
   CHECK_RETVAL(tangent);
   *tangent = m_Curve->GetTangent();
   return S_OK;
}

STDMETHODIMP CCircularCurve::get_MidOrdinate(Float64* mo)
{
   CHECK_RETVAL(mo);
   *mo = m_Curve->GetMidOrdinate();
   return S_OK;
}

STDMETHODIMP CCircularCurve::get_External(Float64* external)
{
   CHECK_RETVAL(external);
   *external = m_Curve->GetExternal();
   return S_OK;
}

STDMETHODIMP CCircularCurve::get_Center(IPoint2d** pVal)
{
   CHECK_RETOBJ(pVal);
   return cogoUtil::CreatePoint(m_Curve->GetCenter(), pVal);
	return S_OK;
}

STDMETHODIMP CCircularCurve::get_Direction(CurveDirectionType* dir)
{
   CHECK_RETVAL(dir);
   *dir = (m_Curve->GetCurveDirection() == WBFL::COGO::CurveDirection::Left ? cdLeft : cdRight);
   return S_OK;
}

STDMETHODIMP CCircularCurve::get_DegreeCurvature(Float64 D,DegreeCurvatureType dcMethod,IAngle** pDC)
{
   CHECK_RETVAL(pDC);
   WBFL::COGO::DegreeCurvature dc = (dcMethod == dcArc ? WBFL::COGO::DegreeCurvature::Arc : WBFL::COGO::DegreeCurvature::Chord);
   return cogoUtil::CreateAngle(m_Curve->GetDegreeOfCurvature(D, dc), pDC);
}

// IPathElement

STDMETHODIMP CCircularCurve::Clone(IPathElement** clone)
{
   CHECK_RETOBJ(clone);
   auto backing_clone = WBFL::COGO::CircularCurve::Create(*m_Curve);
   return cogoUtil::CreatePathElement(backing_clone, clone);

}

STDMETHODIMP CCircularCurve::GetStartPoint(IPoint2d** ppPoint)
{
   CHECK_RETOBJ(ppPoint);
   return cogoUtil::CreatePoint(m_Curve->GetStartPoint(), ppPoint);
}

STDMETHODIMP CCircularCurve::GetEndPoint(IPoint2d** ppPoint)
{
   CHECK_RETOBJ(ppPoint);
   return cogoUtil::CreatePoint(m_Curve->GetEndPoint(), ppPoint);
}

STDMETHODIMP CCircularCurve::GetLength(Float64* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Curve->GetLength();
   return S_OK;
}

STDMETHODIMP CCircularCurve::GetKeyPoints(IPoint2dCollection** ppPoints)
{
   CHECK_RETOBJ(ppPoints);
   return cogoUtil::CreatePoints(m_Curve->GetKeyPoints(), ppPoints);
}

STDMETHODIMP CCircularCurve::GetBearing(Float64 distance, IDirection** pVal)
{
   CHECK_RETOBJ(pVal);
   return cogoUtil::CreateDirection(m_Curve->GetBearing(distance), pVal);
}

STDMETHODIMP CCircularCurve::GetNormal(Float64 distance, IDirection** pVal)
{
   CHECK_RETOBJ(pVal);
   return cogoUtil::CreateDirection(m_Curve->GetNormal(distance), pVal);
}

STDMETHODIMP CCircularCurve::PointOnCurve(Float64 distance, IPoint2d** pVal)
{
   CHECK_RETOBJ(pVal);
   return cogoUtil::CreatePoint(m_Curve->PointOnCurve(distance), pVal);
}

STDMETHODIMP CCircularCurve::LocatePoint(Float64 distFromStart, OffsetMeasureType offsetType, Float64 offset, VARIANT varDirection, IPoint2d** ppPoint)
{
   CHECK_RETVAL(ppPoint);

   auto [hr,direction] = cogoUtil::DirectionFromVariant(varDirection);
   if (FAILED(hr)) return hr;

   return cogoUtil::CreatePoint(m_Curve->LocatePoint(distFromStart, WBFL::COGO::OffsetType(offsetType), offset, direction), ppPoint);
}

STDMETHODIMP CCircularCurve::ProjectPoint(IPoint2d* point, IPoint2d** pNewPoint, Float64* pDistFromStart, VARIANT_BOOL* pvbOnProjection)
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

STDMETHODIMP CCircularCurve::Intersect(ILine2d* pLine, VARIANT_BOOL bProjectBack, VARIANT_BOOL bProjectAhead, IPoint2dCollection** ppPoints)
{
   CHECK_IN(pLine);
   CHECK_RETOBJ(ppPoints);

   auto vPoints = m_Curve->Intersect(cogoUtil::GetLine(pLine), bProjectBack == VARIANT_TRUE, bProjectAhead == VARIANT_TRUE);
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

STDMETHODIMP CCircularCurve::Move(Float64 dist, VARIANT varDirection)
{
   HRESULT hr;
   WBFL::COGO::Direction direction;
   std::tie(hr, direction) = cogoUtil::DirectionFromVariant(varDirection);
   if (FAILED(hr)) return hr;
   m_Curve->Move(dist, direction);
   return S_OK;
}

STDMETHODIMP CCircularCurve::Offset(Float64 dx, Float64 dy)
{
   m_Curve->Offset(dx, dy);
   return S_OK;
}

STDMETHODIMP CCircularCurve::CreateOffsetPath(Float64 offset, IPath** ppPath)
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

STDMETHODIMP CCircularCurve::CreateSubpath(Float64 start, Float64 end, IPath** ppPath)
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
