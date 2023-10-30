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

// SurfaceProfile.cpp : Implementation of CSurfaceProfile
#include "stdafx.h"
#include "WBFLCOGO.h"
#include "SurfaceProfile.h"
#include <WBFLCogo\CogoHelpers.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSurfaceProfile

HRESULT CSurfaceProfile::FinalConstruct()
{
   return S_OK;
}

void CSurfaceProfile::FinalRelease()
{
}

STDMETHODIMP CSurfaceProfile::InterfaceSupportsErrorInfo(REFIID riid)
{
   static const IID* arr[] = 
   {
      &IID_ISurfaceProfile,
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

// ISurfaceProfile

STDMETHODIMP CSurfaceProfile::get_Surface(ISurface* *pVal)
{
   CHECK_RETOBJ(pVal);
   if ( m_pSurface )
   {
      (*pVal) = m_pSurface;
      (*pVal)->AddRef();
   }

   return S_OK;
}

STDMETHODIMP CSurfaceProfile::putref_Surface(ISurface* newVal)
{
   m_pSurface = newVal;
   return S_OK;
}

STDMETHODIMP CSurfaceProfile::get_Station(IStation** station)
{
   CHECK_RETOBJ(station);
   return cogoUtil::CreateStation(m_SurfaceProfile->GetStation(), station);
}

STDMETHODIMP CSurfaceProfile::get_Direction(IDirection** direction)
{
   CHECK_RETOBJ(direction);
   return cogoUtil::CreateDirection(m_SurfaceProfile->GetDirection(), direction);
}

STDMETHODIMP CSurfaceProfile::get_SkewAngle(IAngle** skewAngle)
{
   CHECK_RETOBJ(skewAngle);
   return cogoUtil::CreateAngle(m_SurfaceProfile->GetSkewAngle(), skewAngle);
}

STDMETHODIMP CSurfaceProfile::get_Count(IndexType* count)
{
   CHECK_RETVAL(count);
   *count = m_SurfaceProfile->GetSurfacePointCount();
   return S_OK;
}

STDMETHODIMP CSurfaceProfile::get_Item(IndexType idx,ISurfacePoint** point)
{
   CHECK_RETOBJ(point);
   return cogoUtil::CreateSurfacePoint(m_SurfaceProfile->GetSurfacePoint(idx), point);
}

STDMETHODIMP CSurfaceProfile::GetSurfacePointElevationChange(IndexType surfacePoint1Idx,IndexType surfacePoint2Idx,Float64* deltaElevation)
{
   // computes the change in elevation between two surface points
   CHECK_RETVAL(deltaElevation);
   *deltaElevation = m_SurfaceProfile->GetSurfacePointElevationChange(surfacePoint1Idx, surfacePoint2Idx);
   return S_OK;
}

STDMETHODIMP CSurfaceProfile::GetElevationChange(IndexType surfacePointIdx,Float64 offset,Float64* deltaElevation)
{
   // Computes the change in elevation between a surface point and an offset measured from the surface point
   CHECK_RETVAL(deltaElevation);
   *deltaElevation = m_SurfaceProfile->GetElevationChange(surfacePointIdx, offset);
   return S_OK;
}

STDMETHODIMP CSurfaceProfile::GetSlope(IndexType surfacePointIdx,Float64 offset,Float64* pSlope)
{
   CHECK_RETVAL(pSlope);
   *pSlope = m_SurfaceProfile->GetSlope(surfacePointIdx, offset);
   return S_OK;
}

STDMETHODIMP CSurfaceProfile::GetSegmentSlope(IndexType segmentIdx,Float64* pSlope)
{
   CHECK_RETVAL(pSlope);
   *pSlope = m_SurfaceProfile->GetSegmentSlope(segmentIdx);
   return S_OK;
}
   
STDMETHODIMP CSurfaceProfile::GetSurfacePointOffset(IndexType surfacePointIdx,Float64* pOffset)
{
   CHECK_RETVAL(pOffset);
   *pOffset = m_SurfaceProfile->GetSurfacePointOffset(surfacePointIdx);
   return S_OK;
}

STDMETHODIMP CSurfaceProfile::GetSurfacePointElevation(IndexType surfacePointIdx,Float64* pOffset,Float64* pElev)
{
   CHECK_RETVAL(pOffset);
   CHECK_RETVAL(pElev);
   std::tie(*pOffset, *pElev) = m_SurfaceProfile->GetSurfacePointOffsetAndElevation(surfacePointIdx);
   return S_OK;
}
