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

// CompoundCurve.cpp : Implementation of CCompoundCurve
#include "stdafx.h"
#include "WBFLCOGO.h"
#include "CompoundCurve.h"
#include <WBFLCogo\CogoHelpers.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCompoundCurve
HRESULT CCompoundCurve::FinalConstruct()
{
   m_Curve = WBFL::COGO::CompoundCurve::Create();
   return S_OK;
}

void CCompoundCurve::FinalRelease()
{
}

STDMETHODIMP CCompoundCurve::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ICompoundCurve,
      &IID_IPathElement,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CCompoundCurve::get_PBT(IPoint2d **pVal)
{
   CHECK_RETOBJ(pVal);
   return cogoUtil::CreatePoint(m_Curve->GetPBT(), pVal);
}

STDMETHODIMP CCompoundCurve::put_PBT(IPoint2d *newVal)
{
   CHECK_IN(newVal);
   m_Curve->SetPBT(cogoUtil::GetPoint(newVal));
   return S_OK;

}

STDMETHODIMP CCompoundCurve::get_PI(IPoint2d **pVal)
{
   CHECK_RETOBJ(pVal);
   return cogoUtil::CreatePoint(m_Curve->GetPI(), pVal);
}

STDMETHODIMP CCompoundCurve::put_PI(IPoint2d *newVal)
{
   CHECK_IN(newVal);
   m_Curve->SetPI(cogoUtil::GetPoint(newVal));
   return S_OK;
}

STDMETHODIMP CCompoundCurve::get_PFT(IPoint2d **pVal)
{
   CHECK_RETOBJ(pVal);
   return cogoUtil::CreatePoint(m_Curve->GetPFT(), pVal);
}

STDMETHODIMP CCompoundCurve::put_PFT(IPoint2d *newVal)
{
   CHECK_IN(newVal);
   m_Curve->SetPFT(cogoUtil::GetPoint(newVal));
   return S_OK;
}

STDMETHODIMP CCompoundCurve::get_Radius(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Curve->GetRadius();
   return S_OK;
}

STDMETHODIMP CCompoundCurve::put_Radius(Float64 newVal)
{
   if ( newVal <= 0 )
      return E_INVALIDARG;

   m_Curve->SetRadius(newVal);

   return S_OK;
}

STDMETHODIMP CCompoundCurve::get_SpiralLength(SpiralType spType,Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   if (spType == spEntry)
      *pVal = m_Curve->GetSpiralLength(WBFL::COGO::CompoundCurve::SpiralLocation::Entry);
   else
      *pVal = m_Curve->GetSpiralLength(WBFL::COGO::CompoundCurve::SpiralLocation::Exit);

	return S_OK;
}

STDMETHODIMP CCompoundCurve::put_SpiralLength(SpiralType spType,Float64 newVal)
{
   if ( newVal < 0 )
      return E_INVALIDARG;

   if (spType == spEntry)
      m_Curve->SetSpiralLength(WBFL::COGO::CompoundCurve::SpiralLocation::Entry, newVal);
   else
      m_Curve->SetSpiralLength(WBFL::COGO::CompoundCurve::SpiralLocation::Exit, newVal);

	return S_OK;
}

STDMETHODIMP CCompoundCurve::get_SpiralAngle(SpiralType spType,IAngle **pVal)
{
   CHECK_RETOBJ(pVal);
   auto spiral_location = (spType == spEntry ? WBFL::COGO::CompoundCurve::SpiralLocation::Entry : WBFL::COGO::CompoundCurve::SpiralLocation::Exit);
   return cogoUtil::CreateAngle(m_Curve->GetSpiralAngle(spiral_location),pVal);
}

STDMETHODIMP CCompoundCurve::get_X(SpiralType spType,Float64* x)
{
   CHECK_RETVAL(x);
   auto spiral_location = (spType == spEntry ? WBFL::COGO::CompoundCurve::SpiralLocation::Entry : WBFL::COGO::CompoundCurve::SpiralLocation::Exit);
   *x = m_Curve->GetX(spiral_location);
   return S_OK;
}

STDMETHODIMP CCompoundCurve::get_Y(SpiralType spType,Float64* y)
{
   CHECK_RETVAL(y);
   auto spiral_location = (spType == spEntry ? WBFL::COGO::CompoundCurve::SpiralLocation::Entry : WBFL::COGO::CompoundCurve::SpiralLocation::Exit);
   *y = m_Curve->GetY(spiral_location);
   return S_OK;
}

STDMETHODIMP CCompoundCurve::get_Q(SpiralType spType,Float64* q)
{
   CHECK_RETVAL(q);
   auto spiral_location = (spType == spEntry ? WBFL::COGO::CompoundCurve::SpiralLocation::Entry : WBFL::COGO::CompoundCurve::SpiralLocation::Exit);
   *q = m_Curve->GetQ(spiral_location);
   return S_OK;
}

STDMETHODIMP CCompoundCurve::get_T(SpiralType spType,Float64* t)
{
   CHECK_RETVAL(t);
   auto spiral_location = (spType == spEntry ? WBFL::COGO::CompoundCurve::SpiralLocation::Entry : WBFL::COGO::CompoundCurve::SpiralLocation::Exit);
   *t = m_Curve->GetT(spiral_location);
   return S_OK;
}

STDMETHODIMP CCompoundCurve::get_FwdTangentBrg(IDirection **pVal)
{
   CHECK_RETOBJ(pVal);
   return cogoUtil::CreateDirection(m_Curve->GetForwardTangentBearing(), pVal);
}

STDMETHODIMP CCompoundCurve::get_BkTangentBrg(IDirection **pVal)
{
   CHECK_RETOBJ(pVal);
   return cogoUtil::CreateDirection(m_Curve->GetBackTangentBearing(), pVal);
}

STDMETHODIMP CCompoundCurve::get_CurveAngle(IAngle* *pVal)
{
   // Total curve angle
   CHECK_RETOBJ(pVal);
   return cogoUtil::CreateAngle(m_Curve->GetCurveAngle(), pVal);
}

STDMETHODIMP CCompoundCurve::get_BkTangentLength(Float64* t)
{
   CHECK_RETVAL(t);
   *t = m_Curve->GetBackTangentLength();
   return S_OK;
}

STDMETHODIMP CCompoundCurve::get_FwdTangentLength(Float64* t)
{
   CHECK_RETVAL(t);
   *t = m_Curve->GetForwardTangentLength();
   return S_OK;
}

STDMETHODIMP CCompoundCurve::get_TS(IPoint2d* *pVal)
{
   CHECK_RETOBJ(pVal);
   return cogoUtil::CreatePoint(m_Curve->GetTS(), pVal);
}

STDMETHODIMP CCompoundCurve::get_ST(IPoint2d* *pVal)
{
   CHECK_RETOBJ(pVal);
   return cogoUtil::CreatePoint(m_Curve->GetST(), pVal);
}

STDMETHODIMP CCompoundCurve::get_SC(IPoint2d* *pVal)
{
   CHECK_RETOBJ(pVal);
   return cogoUtil::CreatePoint(m_Curve->GetSC(), pVal);
}

STDMETHODIMP CCompoundCurve::get_CS(IPoint2d* *pVal)
{
   CHECK_RETOBJ(pVal);
   return cogoUtil::CreatePoint(m_Curve->GetCS(), pVal);
}

STDMETHODIMP CCompoundCurve::get_Chord(Float64* chord)
{
   CHECK_RETVAL(chord);
   *chord = m_Curve->GetChord();
   return S_OK;
}

STDMETHODIMP CCompoundCurve::get_CircularCurveAngle(IAngle** pVal)
{
   CHECK_RETOBJ(pVal);
   WBFL::COGO::Angle angle;
   try { angle = m_Curve->GetCircularCurveAngle(); }
   catch (...) { return E_FAIL; }
   return cogoUtil::CreateAngle(angle, pVal);
}

STDMETHODIMP CCompoundCurve::get_Tangent(Float64* tangent)
{
   CHECK_RETVAL(tangent);
   try { *tangent = m_Curve->GetTangent(); }
   catch (...) { return E_FAIL; }
   return S_OK;
}

STDMETHODIMP CCompoundCurve::get_MidOrdinate(Float64* mo)
{
   CHECK_RETVAL(mo);
   try { *mo = m_Curve->GetMidOrdinate(); }
   catch (...) { return E_FAIL; }
   return S_OK;
}

STDMETHODIMP CCompoundCurve::get_External(Float64* external)
{
   CHECK_RETVAL(external);
   try { *external = m_Curve->GetExternal(); }
   catch (...) { return E_FAIL; }
   return S_OK;
}

STDMETHODIMP CCompoundCurve::get_DE(SpiralType spType,IAngle** pDE)
{
   CHECK_RETOBJ(pDE);
   auto spiral_location = (spType == spEntry ? WBFL::COGO::CompoundCurve::SpiralLocation::Entry : WBFL::COGO::CompoundCurve::SpiralLocation::Exit);
   return cogoUtil::CreateAngle(m_Curve->GetDE(spiral_location), pDE);
}

STDMETHODIMP CCompoundCurve::get_LongTangent(SpiralType spType,Float64* u)
{
   CHECK_RETVAL(u);
   auto spiral_location = (spType == spEntry ? WBFL::COGO::CompoundCurve::SpiralLocation::Entry : WBFL::COGO::CompoundCurve::SpiralLocation::Exit);
   *u = m_Curve->GetLongTangent(spiral_location);
   return S_OK;
}

STDMETHODIMP CCompoundCurve::get_ShortTangent(SpiralType spType,Float64* v)
{
   CHECK_RETVAL(v);
   auto spiral_location = (spType == spEntry ? WBFL::COGO::CompoundCurve::SpiralLocation::Entry : WBFL::COGO::CompoundCurve::SpiralLocation::Exit);
   *v = m_Curve->GetShortTangent(spiral_location);
   return S_OK;
}

STDMETHODIMP CCompoundCurve::get_CC(IPoint2d** pVal)
{
   CHECK_RETOBJ(pVal);
   return cogoUtil::CreatePoint(m_Curve->GetCC(), pVal);
}

STDMETHODIMP CCompoundCurve::get_SPI(SpiralType spType,IPoint2d** pSPI)
{
   CHECK_RETOBJ(pSPI);
   auto spiral_location = (spType == spEntry ? WBFL::COGO::CompoundCurve::SpiralLocation::Entry : WBFL::COGO::CompoundCurve::SpiralLocation::Exit);
   return cogoUtil::CreatePoint(m_Curve->GetSPI(spiral_location), pSPI);
}

STDMETHODIMP CCompoundCurve::get_CurveBkTangentBrg(IDirection* *brg)
{
   CHECK_RETOBJ(brg);
   return cogoUtil::CreateDirection(m_Curve->GetCurveBackTangentBearing(), brg);
}

STDMETHODIMP CCompoundCurve::get_CurveFwdTangentBrg(IDirection* *brg)
{
   CHECK_RETOBJ(brg);
   return cogoUtil::CreateDirection(m_Curve->GetCurveForwardTangentBearing(), brg);
}

STDMETHODIMP CCompoundCurve::get_PCI(IPoint2d **pVal)
{
   CHECK_RETOBJ(pVal);
   return cogoUtil::CreatePoint(m_Curve->GetPCI(), pVal);
}

STDMETHODIMP CCompoundCurve::get_CCC(IPoint2d **pVal)
{
   CHECK_RETOBJ(pVal);
   return cogoUtil::CreatePoint(m_Curve->GetCCC(), pVal);
	return S_OK;
}

STDMETHODIMP CCompoundCurve::get_SpiralChord(SpiralType spType,Float64* cs)
{
   CHECK_RETVAL(cs);
   auto spiral_location = (spType == spEntry ? WBFL::COGO::CompoundCurve::SpiralLocation::Entry : WBFL::COGO::CompoundCurve::SpiralLocation::Exit);
   *cs = m_Curve->GetSpiralChord(spiral_location);
   return S_OK;
}

STDMETHODIMP CCompoundCurve::get_DF(SpiralType spType,IAngle** pDF)
{
   CHECK_RETOBJ(pDF);
   auto spiral_location = (spType == spEntry ? WBFL::COGO::CompoundCurve::SpiralLocation::Entry : WBFL::COGO::CompoundCurve::SpiralLocation::Exit);
   return cogoUtil::CreateAngle(m_Curve->GetDF(spiral_location), pDF);
}

STDMETHODIMP CCompoundCurve::get_DH(SpiralType spType,IAngle** pDH)
{
   CHECK_RETOBJ(pDH);
   auto spiral_location = (spType == spEntry ? WBFL::COGO::CompoundCurve::SpiralLocation::Entry : WBFL::COGO::CompoundCurve::SpiralLocation::Exit);
   return cogoUtil::CreateAngle(m_Curve->GetDH(spiral_location), pDH);
}

STDMETHODIMP CCompoundCurve::get_Direction(CurveDirectionType* dir)
{
   CHECK_RETVAL(dir);
   *dir = (m_Curve->GetCurveDirection() == WBFL::COGO::CurveDirection::Left ? cdLeft : cdRight);
   return S_OK;
}

STDMETHODIMP CCompoundCurve::get_CurveLength(Float64* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Curve->GetCurveLength();
   return S_OK;
}

STDMETHODIMP CCompoundCurve::get_TotalLength(Float64* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Curve->GetTotalLength();
   return S_OK;
}

STDMETHODIMP CCompoundCurve::get_DegreeCurvature(Float64 D,DegreeCurvatureType dcMethod,IAngle** pDC)
{
   CHECK_RETVAL(pDC);
   WBFL::COGO::DegreeCurvature dc = (dcMethod == dcArc ? WBFL::COGO::DegreeCurvature::Arc : WBFL::COGO::DegreeCurvature::Chord);
   return cogoUtil::CreateAngle(m_Curve->GetDegreeOfCurvature(D, dc), pDC);
}

// IPathElement

STDMETHODIMP CCompoundCurve::Clone(IPathElement* *clone)
{
   CHECK_RETOBJ(clone);
   auto backing_clone = WBFL::COGO::CompoundCurve::Create(*m_Curve);
   return cogoUtil::CreatePathElement(backing_clone, clone);
}

STDMETHODIMP CCompoundCurve::Move(Float64 dist, VARIANT varDirection)
{
   auto [hr, direction] = cogoUtil::DirectionFromVariant(varDirection);
   if (FAILED(hr)) return hr;
   m_Curve->Move(dist, direction);
   return S_OK;
}

STDMETHODIMP CCompoundCurve::Offset(Float64 dx, Float64 dy)
{
   m_Curve->Offset(dx, dy);
   return S_OK;
}

STDMETHODIMP CCompoundCurve::PointOnCurve(Float64 distance, IPoint2d** pVal)
{
   CHECK_RETOBJ(pVal);
   return cogoUtil::CreatePoint(m_Curve->PointOnCurve(distance), pVal);
}

STDMETHODIMP CCompoundCurve::GetStartPoint(IPoint2d** ppPoint)
{
   CHECK_RETOBJ(ppPoint);
   return cogoUtil::CreatePoint(m_Curve->GetTS(), ppPoint);
}

STDMETHODIMP CCompoundCurve::GetEndPoint(IPoint2d** ppPoint)
{
   CHECK_RETOBJ(ppPoint);
   return cogoUtil::CreatePoint(m_Curve->GetST(), ppPoint);
}

STDMETHODIMP CCompoundCurve::GetLength(Float64* pLength)
{
   CHECK_RETVAL(pLength);
   *pLength = m_Curve->GetTotalLength();
   return S_OK;
}

STDMETHODIMP CCompoundCurve::GetKeyPoints(IPoint2dCollection** ppPoints)
{
   CHECK_RETOBJ(ppPoints);
   return cogoUtil::CreatePoints(m_Curve->GetKeyPoints(), ppPoints);
}

STDMETHODIMP CCompoundCurve::LocatePoint(Float64 distFromStart, OffsetMeasureType offsetType, Float64 offset, VARIANT varDirection, IPoint2d** ppPoint)
{
   CHECK_RETOBJ(ppPoint);

   auto [hr, direction] = cogoUtil::DirectionFromVariant(varDirection);
   if (FAILED(hr)) return hr;

   return cogoUtil::CreatePoint(m_Curve->LocatePoint(distFromStart, WBFL::COGO::OffsetType(offsetType), offset, direction), ppPoint);
}

STDMETHODIMP CCompoundCurve::GetBearing(Float64 distance, IDirection** pVal)
{
   CHECK_RETOBJ(pVal);
   return cogoUtil::CreateDirection(m_Curve->GetBearing(distance), pVal);
}

STDMETHODIMP CCompoundCurve::GetNormal(Float64 distance, IDirection** pVal)
{
   CHECK_RETOBJ(pVal);
   return cogoUtil::CreateDirection(m_Curve->GetNormal(distance), pVal);
}

STDMETHODIMP CCompoundCurve::ProjectPoint(IPoint2d* point, IPoint2d** pNewPoint, Float64* pDistFromStart, VARIANT_BOOL* pvbOnProjection)
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

STDMETHODIMP CCompoundCurve::Intersect(ILine2d* pLine, VARIANT_BOOL vbProjectBack, VARIANT_BOOL vbProjectAhead, IPoint2dCollection** ppPoints)
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
   return vPoints.empty() ? S_FALSE : S_OK;
}

STDMETHODIMP CCompoundCurve::CreateOffsetPath(Float64 offset, IPath** ppPath)
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

STDMETHODIMP CCompoundCurve::CreateSubpath(Float64 start, Float64 end, IPath** ppPath)
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

