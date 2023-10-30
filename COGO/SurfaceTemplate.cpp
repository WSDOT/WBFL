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

// SurfaceTemplate.cpp : Implementation of CSurfaceTemplate
#include "stdafx.h"
#include "WBFLCOGO.h"
#include "SurfaceTemplate.h"
#include <WBFLCogo\CogoHelpers.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSurfaceTemplate

HRESULT CSurfaceTemplate::FinalConstruct()
{
   return S_OK;
}

void CSurfaceTemplate::FinalRelease()
{
}

STDMETHODIMP CSurfaceTemplate::InterfaceSupportsErrorInfo(REFIID riid)
{
   static const IID* arr[] = 
   {
      &IID_ISurfaceTemplate,
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

// ISurfaceTemplate

STDMETHODIMP CSurfaceTemplate::get_Surface(ISurface* *pVal)
{
   CHECK_RETOBJ(pVal);
   if ( m_pSurface )
   {
      (*pVal) = m_pSurface;
      (*pVal)->AddRef();
   }

   return S_OK;
}

STDMETHODIMP CSurfaceTemplate::putref_Surface(ISurface* newVal)
{
   m_pSurface = newVal;
   return S_OK;
}

STDMETHODIMP CSurfaceTemplate::get_Station(IStation** station)
{
   CHECK_RETOBJ(station);
   return cogoUtil::CreateStation(m_Template->GetStation(), station);
}

STDMETHODIMP CSurfaceTemplate::GetSegmentParameters(IndexType segmentIdx, Float64* pWidth, Float64* pSlope, TemplateSlopeType* pSlopeType)
{
   WBFL::COGO::SurfaceTemplateSegment::SlopeType slopeType;
   std::tie(*pWidth, *pSlope, slopeType) = m_Template->GetSegmentParameters(segmentIdx);
   *pSlopeType = TemplateSlopeType(slopeType);
   return S_OK;
}

STDMETHODIMP CSurfaceTemplate::UpdateSegmentParameters(IndexType segmentIdx, Float64 width,Float64 slope,TemplateSlopeType slopeType)
{
   m_Template->UpdateSegmentParameters(segmentIdx, width, slope, WBFL::COGO::SurfaceTemplateSegment::SlopeType(slopeType));
   return S_OK;
}

STDMETHODIMP CSurfaceTemplate::get_Count(IndexType* count)
{
   CHECK_RETVAL(count);
   *count = m_Template->GetCount();
   return S_OK;
}

STDMETHODIMP CSurfaceTemplate::get_Item(IndexType idx,ISurfaceTemplateSegment** segment)
{
   CHECK_RETOBJ(segment);
   return cogoUtil::CreateSurfaceTemplateSegment(m_Template->GetSegment(idx), segment);
}

STDMETHODIMP CSurfaceTemplate::Clear()
{
   m_Template->Clear();
   return S_OK;
}

STDMETHODIMP CSurfaceTemplate::GetRidgePointElevationChange(IndexType ridgePoint1Idx,IndexType ridgePoint2Idx,Float64* deltaElevation)
{
   CHECK_RETVAL(deltaElevation);
   *deltaElevation = m_Template->GetRidgePointElevationChange(ridgePoint1Idx, ridgePoint2Idx);
   return S_OK;
}

STDMETHODIMP CSurfaceTemplate::GetElevationChange(IndexType ridgePointIdx,Float64 offset,Float64* deltaElevation)
{
   CHECK_RETVAL(deltaElevation);
   *deltaElevation = m_Template->GetElevationChange(ridgePointIdx, offset);
   return S_OK;
}

STDMETHODIMP CSurfaceTemplate::GetSlope(IndexType ridgePointIdx,Float64 offset,Float64* pSlope)
{
   CHECK_RETVAL(pSlope);
   *pSlope = m_Template->GetSlope(ridgePointIdx, offset);
   return S_OK;
}

STDMETHODIMP CSurfaceTemplate::GetSegmentSlope(IndexType segmentIdx,Float64* pSlope)
{
   CHECK_RETVAL(pSlope);
   *pSlope = m_Template->GetSegmentSlope(segmentIdx);
   return S_OK;
}
   
STDMETHODIMP CSurfaceTemplate::GetRidgePointOffset(IndexType ridgePointIdx,IndexType refPointIdx,Float64* pOffset)
{
   CHECK_RETVAL(pOffset);
   *pOffset = m_Template->GetRidgePointOffset(ridgePointIdx, refPointIdx);
   return S_OK;
}

STDMETHODIMP CSurfaceTemplate::GetRidgePointElevation(IndexType ridgePointIdx, Float64* pElev)
{
   CHECK_RETVAL(pElev);
   *pElev = m_Template->GetRidgePointElevation(ridgePointIdx);
   return S_OK;
}

STDMETHODIMP CSurfaceTemplate::GetRidgePointOffsetAndElevation(IndexType ridgePointIdx,IndexType refPointIdx,Float64* pOffset,Float64* pElev)
{
   CHECK_RETVAL(pOffset);
   CHECK_RETVAL(pElev);
   std::tie(*pOffset, *pElev) = m_Template->GetRidgePointOffsetAndElevation(ridgePointIdx, refPointIdx);
   return S_OK;
}
