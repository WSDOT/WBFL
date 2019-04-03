///////////////////////////////////////////////////////////////////////
// GenericBridgeTools - Tools for manipluating the Generic Bridge Modeling
// Copyright © 1999-2019  Washington State Department of Transportation
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

// StrandModelBase.cpp : Implementation of CStrandModelBase
#include "stdafx.h"
#include "WBFLGenericBridgeTools.h"
#include "StrandModelBase.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CStrandModelBase

////////////////////////////////////
// IStrandModel
STDMETHODIMP CStrandModelBase::Initialize(ISuperstructureMemberSegment* pSegment,IPrecastGirder* pGirder)
{
   CHECK_IN(pSegment);
   CHECK_IN(pGirder);

   m_pSegment = pSegment;
   m_pGirder = pGirder;

   return OnInitialize();
}

STDMETHODIMP CStrandModelBase::putref_StrandMaterial(StrandType strandType,IPrestressingStrand* pMaterial)
{
   CHECK_IN(pMaterial);
   m_StrandMaterial[strandType] = pMaterial;
   return S_OK;
}

STDMETHODIMP CStrandModelBase::get_StrandMaterial(StrandType strandType,IPrestressingStrand** ppMaterial)
{
   CHECK_RETOBJ(ppMaterial);
   return m_StrandMaterial[strandType].CopyTo(ppMaterial);
}

STDMETHODIMP CStrandModelBase::SetHarpingPoints(Float64 hp1, Float64 hp2)
{
   // must be positive values... HarpPointMeasure will indicate if this is fractional
   if (hp1 < 0 || hp2 < 0)
   {
      ATLASSERT(false);
      return E_INVALIDARG;
   }

   m_HP1 = hp1;
   m_HP2 = hp2;

   m_CGs[Harped].clear();

   return S_OK;
}

STDMETHODIMP CStrandModelBase::GetHarpingPoints(Float64* hp1, Float64* hp2)
{
   CHECK_RETVAL(hp1);
   CHECK_RETVAL(hp2);

   *hp1 = m_HP1;
   *hp2 = m_HP2;

   return S_OK;
}

STDMETHODIMP CStrandModelBase::SetEndHarpingPoints(Float64 hp1, Float64 hp2)
{
   // must be positive values... HarpPointMeasure will indicate if this is fractional
   if (hp1 < 0 || hp2 < 0)
   {
      ATLASSERT(false);
      return E_INVALIDARG;
   }

   m_HPStart = hp1;
   m_HPEnd = hp2;

   m_CGs[Harped].clear();
   return S_OK;
}

STDMETHODIMP CStrandModelBase::GetEndHarpingPoints(Float64* hp1, Float64* hp2)
{
   CHECK_RETVAL(hp1);
   CHECK_RETVAL(hp2);

   *hp1 = m_HPStart;
   *hp2 = m_HPEnd;

   return S_OK;
}

STDMETHODIMP CStrandModelBase::put_HarpingPointMeasure(HarpPointMeasure measure)
{
   m_HPMeasure = measure;
   m_CGs[Harped].clear();
   return S_OK;
}

STDMETHODIMP CStrandModelBase::get_HarpingPointMeasure(HarpPointMeasure* measure)
{
   CHECK_RETVAL(measure);
   *measure = m_HPMeasure;
   return S_OK;
}

STDMETHODIMP CStrandModelBase::put_EndHarpingPointMeasure(HarpPointMeasure measure)
{
   m_EndHPMeasure = measure;
   m_CGs[Harped].clear();
   return S_OK;
}

STDMETHODIMP CStrandModelBase::get_EndHarpingPointMeasure(HarpPointMeasure* measure)
{
   CHECK_RETVAL(measure);
   *measure = m_EndHPMeasure;
   return S_OK;
}

STDMETHODIMP CStrandModelBase::put_HarpingPointReference(HarpPointReference hpRef)
{
   m_HPReference = hpRef;
   m_CGs[Harped].clear();
   return S_OK;
}

STDMETHODIMP CStrandModelBase::get_HarpingPointReference(HarpPointReference* hpRef)
{
   CHECK_RETVAL(hpRef);
   *hpRef = m_HPReference;
   return S_OK;
}

STDMETHODIMP CStrandModelBase::put_EndHarpingPointReference(HarpPointReference hpRef)
{
   m_EndHPReference = hpRef;
   m_CGs[Harped].clear();
   return S_OK;
}

STDMETHODIMP CStrandModelBase::get_EndHarpingPointReference(HarpPointReference* hpRef)
{
   CHECK_RETVAL(hpRef);
   *hpRef = m_EndHPReference;
   return S_OK;
}

STDMETHODIMP CStrandModelBase::GetHarpingPointLocations(Float64* hp1, Float64* hp2)
{
   CHECK_RETVAL(hp1);
   CHECK_RETVAL(hp2);

   GetHarpPointLocations(*hp1, *hp2);
   return S_OK;
}

STDMETHODIMP CStrandModelBase::GetEndHarpingPointLocations(Float64* hp1, Float64* hp2)
{
   CHECK_RETVAL(hp1);
   CHECK_RETVAL(hp2);

   GetEndHarpPointLocations(*hp1, *hp2);
   return S_OK;
}

STDMETHODIMP CStrandModelBase::put_UseMinHarpPointDistance(VARIANT_BOOL bUseMin)
{
   m_bUseMinHpDistance = bUseMin;
   m_CGs[Harped].clear();
   return S_OK;
}

STDMETHODIMP CStrandModelBase::get_UseMinHarpPointDistance(VARIANT_BOOL* bUseMin)
{
   CHECK_RETVAL(bUseMin);
   *bUseMin = m_bUseMinHpDistance;
   return S_OK;
}

STDMETHODIMP CStrandModelBase::put_MinHarpPointDistance(Float64 minHpDist)
{
   m_MinHpDist = minHpDist;
   m_CGs[Harped].clear();
   return S_OK;
}

STDMETHODIMP CStrandModelBase::get_MinHarpPointDistance(Float64* minHpDist)
{
   CHECK_RETVAL(minHpDist);
   *minHpDist = m_MinHpDist;
   return S_OK;
}

STDMETHODIMP CStrandModelBase::put_StraightStrandProfileType(StrandProfileType profileType)
{
   m_StraightStrandProfileType = profileType;
   return S_OK;
}

STDMETHODIMP CStrandModelBase::get_StraightStrandProfileType(StrandProfileType* pProfileType)
{
   CHECK_RETVAL(pProfileType);
   *pProfileType = m_StraightStrandProfileType;
   return S_OK;
}

STDMETHODIMP CStrandModelBase::put_TemporaryStrandProfileType(StrandProfileType profileType)
{
   m_TemporaryStrandProfileType = profileType;
   return S_OK;
}

STDMETHODIMP CStrandModelBase::get_TemporaryStrandProfileType(StrandProfileType* pProfileType)
{
   CHECK_RETVAL(pProfileType);
   *pProfileType = m_TemporaryStrandProfileType;
   return S_OK;
}


void CStrandModelBase::GetHarpPointLocations(Float64& hp1, Float64& hp2, Float64& hp3, Float64& hp4) const
{
   GetHarpPointLocations(hp2, hp3);
   GetEndHarpPointLocations(hp1, hp4);
}

void CStrandModelBase::GetHarpPointLocations(Float64& hp1, Float64& hp2) const
{
   hp1 = GetHarpPointLocation(m_HP1, m_HPReference, m_HPMeasure, false, false);
   hp2 = GetHarpPointLocation(m_HP2, m_HPReference, m_HPMeasure, true, false);
}

void CStrandModelBase::GetEndHarpPointLocations(Float64& hp1, Float64& hp2) const
{
   hp1 = GetHarpPointLocation(m_HPStart, m_EndHPReference, m_EndHPMeasure, false, true);
   hp2 = GetHarpPointLocation(m_HPEnd, m_EndHPReference, m_EndHPMeasure, true, true);
}

Float64 CStrandModelBase::GetHarpPointLocation(Float64 hp, HarpPointReference hpRef, HarpPointMeasure hpMeasure, bool bRight, bool bLocatingEndHarpPoint) const
{
   Float64 left_end_distance;
   Float64 right_end_distance;

   Float64 span_length;
   m_pGirder->get_SpanLength(&span_length);

   Float64 gdr_length;
   m_pGirder->get_GirderLength(&gdr_length);

   if (hpMeasure == hpmFractionOfGirderLength)
   {
      hp *= gdr_length;
   }

   if (hpMeasure == hpmFractionOfSpanLength)
   {
      hp *= span_length;
   }

   if (m_bUseMinHpDistance == VARIANT_TRUE && hp < m_MinHpDist && !bLocatingEndHarpPoint)
   {
      hp = m_MinHpDist;
   }

   // hp can now be considered the location of the harp point measured
   // from the point of reference. 

   // convert the hp from it's point of reference to the left end of the girder
   Float64 hp_location;
   switch (hpRef)
   {
   case hprEndOfGirder:
      hp_location = (bRight ? gdr_length - hp : hp);
      break;

   case hprCenterOfGirder:
      hp_location = (bRight ? gdr_length / 2 + hp : gdr_length / 2 - hp);
      break;

   case hprBearing:
      m_pGirder->get_LeftEndDistance(&left_end_distance);
      m_pGirder->get_RightEndDistance(&right_end_distance);
      hp_location = (bRight ? gdr_length - right_end_distance - hp : left_end_distance + hp);
      break;
   }

   hp_location = ::ForceIntoRange(0.0, hp_location, gdr_length);

   return hp_location;
}

Float64 CStrandModelBase::GetGirderWidthAdjustment(Float64 Xs) const
{
   Float64 Xadj = 0;
   CComPtr<IShape> shape;
   m_pSegment->get_PrimaryShape(Xs, sbLeft, &shape);

   CComQIPtr<IAsymmetricSection> asymmetric(shape);
   if (asymmetric)
   {
      Float64 wLeft, wRight;
      asymmetric->GetTopWidth(&wLeft, &wRight);
      // wLeft - w/2 = wLeft - (wLeft+wRight)/2 = wLeft/2 - wRight/2 = 0.5*(wLeft - wRight)
      Xadj = 0.5*(wLeft - wRight);
   }

   return Xadj;
}
