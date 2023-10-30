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

// Surface.cpp : Implementation of CSurface
#include "stdafx.h"
#include "WBFLCOGO.h"
#include "Surface.h"
#include <WBFLCogo\CogoHelpers.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSurface

HRESULT CSurface::FinalConstruct()
{
   m_Surface = WBFL::COGO::Surface::Create();
   return S_OK;
}

void CSurface::FinalRelease()
{
}

STDMETHODIMP CSurface::InterfaceSupportsErrorInfo(REFIID riid)
{
   static const IID* arr[] = 
   {
      &IID_ISurface,
   };
   for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
   {
      if (InlineIsEqualGUID(*arr[i],riid))
         return S_OK;
   }
   return S_FALSE;
}

// ISurface
STDMETHODIMP CSurface::get_Profile(IProfile* *pVal)
{
   CHECK_RETOBJ(pVal);
   if ( m_pProfile )
   {
      (*pVal) = m_pProfile;
      (*pVal)->AddRef();
   }

   return S_OK;
}

STDMETHODIMP CSurface::putref_Profile(IProfile* newVal)
{
   m_pProfile = newVal;

   return S_OK;
}


STDMETHODIMP CSurface::put_AlignmentPoint(IndexType pntIdx)
{
   if (pntIdx == INVALID_INDEX)
      return E_INVALIDARG;

   m_Surface->SetAlignmentPoint(pntIdx);

   return S_OK;
}

STDMETHODIMP CSurface::get_AlignmentPoint(IndexType* pntIdx)
{
   CHECK_RETVAL(pntIdx);
   *pntIdx = m_Surface->GetAlignmentPoint();
   return S_OK;
}

STDMETHODIMP CSurface::put_ProfileGradePoint(IndexType pntIdx)
{
   if (pntIdx == INVALID_INDEX)
      return E_INVALIDARG;

   m_Surface->SetProfileGradePoint(pntIdx);

   return S_OK;
}

STDMETHODIMP CSurface::get_ProfileGradePoint(IndexType* pntIdx)
{
   CHECK_RETVAL(pntIdx);
   *pntIdx = m_Surface->GetProfileGradePoint();
   return S_OK;
}

STDMETHODIMP CSurface::put_SurfaceTemplateSegmentCount(IndexType nSegments)
{
   m_Surface->SetSurfaceTemplateSegmentCount(nSegments);
   return S_OK;
}

STDMETHODIMP CSurface::get_SurfaceTemplateSegmentCount(IndexType* pnSegments)
{
   CHECK_RETVAL(pnSegments);
   *pnSegments = m_Surface->GetSurfaceTemplateSegmentCount();
   return S_OK;
}

STDMETHODIMP CSurface::CreateSurfaceTemplate(VARIANT varStation, ISurfaceTemplate** ppTemplate)
{
   auto [hr, station] = cogoUtil::StationFromVariant(varStation);
   if (FAILED(hr)) return hr;

   CComPtr<ISurfaceTemplate> tpl;
   hr = cogoUtil::CreateSurfaceTemplate(this, m_Surface->CreateSurfaceTemplate(station),&tpl);
   if (FAILED(hr)) return hr;

   Float64 s = m_Surface->GetProfile()->GetAlignment()->ConvertToNormalizedStation(station).GetValue();
   m_SurfaceTemplates.emplace(s,tpl);
   return tpl.CopyTo(ppTemplate);
}

STDMETHODIMP CSurface::GetSurfaceTemplate(IndexType idx, ISurfaceTemplate** ppTemplate)
{
   CHECK_RETOBJ(ppTemplate);
   auto iter = m_SurfaceTemplates.begin();
   std::advance(iter,idx);
   auto surface_template = iter->second;
   ATLASSERT(cogoUtil::GetInnerSurfaceTemplate(surface_template) == m_Surface->GetSurfaceTemplates()[idx]);
   return surface_template.CopyTo(ppTemplate);
}

STDMETHODIMP CSurface::GetSurfaceTemplateCount(IndexType* pCount)
{
   CHECK_RETVAL(pCount);
   *pCount = m_Surface->GetSurfaceTemplates().size();
   return S_OK;
}

STDMETHODIMP CSurface::ClearSurfaceTemplates()
{
   m_Surface->ClearSurfaceTemplates();
   m_SurfaceTemplates.clear();
   return S_OK;
}

STDMETHODIMP CSurface::AddSuperelevation(ISuperelevation* pSuperelevation)
{
   CHECK_IN(pSuperelevation);
   m_Surface->AddSuperelevation(cogoUtil::GetInnerSuperelevation(pSuperelevation));
   return S_OK;
}

STDMETHODIMP CSurface::FindSuperelevation(VARIANT varStation, ISuperelevation** ppSuperelevation)
{
   auto [hr, station] = cogoUtil::StationFromVariant(varStation);
   if (FAILED(hr)) return hr;

   return cogoUtil::CreateSuperelevation(m_Surface->FindSuperelevation(station), ppSuperelevation);
}

STDMETHODIMP CSurface::ClearSuperelevations()
{
   m_Surface->ClearSuperelevations();
   return S_OK;
}

STDMETHODIMP CSurface::AddWidening(IWidening* pWidening)
{
   CHECK_IN(pWidening);
   m_Surface->AddWidening(cogoUtil::GetInnerWidening(pWidening));
   return S_OK;
}

STDMETHODIMP CSurface::FindWidening(VARIANT varStation, IWidening** ppWidening)
{
   auto [hr, station] = cogoUtil::StationFromVariant(varStation);
   if (FAILED(hr)) return hr;

   return cogoUtil::CreateWidening(m_Surface->FindWidening(station), ppWidening);
}

STDMETHODIMP CSurface::ClearWidenings()
{
   m_Surface->ClearWidenings();
   return S_OK;
}

STDMETHODIMP CSurface::get_StartBoundaryLine(ILineSegment2d** ppEndLine)
{
   CHECK_RETOBJ(ppEndLine);
   return cogoUtil::CreateLineSegment(m_Surface->GetStartBoundaryLine(), ppEndLine);
}

STDMETHODIMP CSurface::get_EndBoundaryLine(ILineSegment2d** ppEndLine)
{
   CHECK_RETOBJ(ppEndLine);
   return cogoUtil::CreateLineSegment(m_Surface->GetEndBoundaryLine(), ppEndLine);
}

STDMETHODIMP CSurface::CreateSurfaceTemplateSectionCut(VARIANT varStation, VARIANT_BOOL bApplySuperelevations, ISurfaceTemplate** ppSurfaceTemplate)
{
   auto [hr, station] = cogoUtil::StationFromVariant(varStation);
   if (FAILED(hr)) return hr;
   return cogoUtil::CreateSurfaceTemplate(this, m_Surface->CreateSurfaceTemplateSectionCut(station, bApplySuperelevations == VARIANT_TRUE), ppSurfaceTemplate);
}

STDMETHODIMP CSurface::CreateSurfaceProfileSectionCut(VARIANT varStation, VARIANT varSkewAngle, VARIANT_BOOL bApplySuperelevations, ISurfaceProfile** ppSurfaceProfile)
{
   auto [hr, station] = cogoUtil::StationFromVariant(varStation);
   if (FAILED(hr)) return hr;

   WBFL::COGO::Angle skew_angle;
   std::tie(hr, skew_angle) = cogoUtil::AngleFromVariant(varSkewAngle);
   if (FAILED(hr)) return hr;

   return cogoUtil::CreateSurfaceProfile(this, m_Surface->CreateSurfaceProfileSectionCut(station, skew_angle, bApplySuperelevations == VARIANT_TRUE), ppSurfaceProfile);
}


STDMETHODIMP CSurface::GetStationRange(IStation** ppStart,IStation** ppEnd)
{
   CHECK_RETOBJ(ppStart);
   CHECK_RETOBJ(ppEnd);

   auto [start, end] = m_Surface->GetStationRange();
   HRESULT hr1 = cogoUtil::CreateStation(start, ppStart);
   HRESULT hr2 = cogoUtil::CreateStation(end, ppEnd);
   return (FAILED(hr1) || FAILED(hr2) ? E_FAIL : S_OK);
}
