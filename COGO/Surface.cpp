///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry
// Copyright © 1999-2013  Washington State Department of Transportation
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
#include "SurfaceTemplate.h"
#include "SurfaceTemplateCollection.h"
#include "SuperelevationCollection.h"
#include "WideningCollection.h"
#include "CogoHelpers.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSurface

HRESULT CSurface::FinalConstruct()
{
   m_pProfile = NULL;

   CComObject<CSurfaceTemplateCollection>* pSurfaceTemplates;
   CComObject<CSurfaceTemplateCollection>::CreateInstance(&pSurfaceTemplates);
   m_SurfaceTemplates = pSurfaceTemplates;

   CComObject<CSuperelevationCollection>* pSuperelevations;
   CComObject<CSuperelevationCollection>::CreateInstance(&pSuperelevations);
   m_Superelevations = pSuperelevations;

   CComObject<CWideningCollection>* pWidenings;
   CComObject<CWideningCollection>::CreateInstance(&pWidenings);
   m_Widenings = pWidenings;

   m_AlignmentPointIdx = 0;
   m_ProfilePointIdx   = 0;

   m_SurfaceTemplates->putref_Profile(m_pProfile);
   m_Superelevations->putref_Profile(m_pProfile);
   m_Widenings->putref_Profile(m_pProfile);

   Advise();

   return S_OK;
}

void CSurface::FinalRelease()
{
   Unadvise();
}

HRESULT CSurface::Init(IProfile* pProfile,ISurfaceTemplateCollection* pSurfaceTemplates,IndexType alignmentPointIdx,IndexType profilePointIdx,ISuperelevationCollection* pSuperelevations,IWideningCollection* pWidenings)
{
   Unadvise();
   m_SurfaceTemplates.Release();
   m_Superelevations.Release();
   m_Widenings.Release();

   m_SurfaceTemplates = pSurfaceTemplates;
   m_Superelevations  = pSuperelevations;
   m_Widenings        = pWidenings;
   Advise();

   m_AlignmentPointIdx = alignmentPointIdx;
   m_ProfilePointIdx   = profilePointIdx;

   putref_Profile(pProfile);

   return S_OK;
}

void CSurface::Advise()
{
   m_SurfaceTemplates.Advise(GetUnknown(),IID_ISurfaceTemplateCollectionEvents,&m_dwSurfaceTemplatesCookie);
   InternalRelease();

   m_Superelevations.Advise(GetUnknown(),IID_ISuperelevationCollectionEvents,&m_dwSuperelevationCookie);
   InternalRelease();

   m_Widenings.Advise(GetUnknown(),IID_IWideningCollectionEvents,&m_dwWideningCookie);
   InternalRelease();
}

void CSurface::Unadvise()
{
   if ( m_dwSurfaceTemplatesCookie != 0 )
   {
      InternalAddRef();
      AtlUnadvise(m_SurfaceTemplates,IID_ISurfaceTemplateCollectionEvents,m_dwSurfaceTemplatesCookie);
   }

   if ( m_dwSuperelevationCookie != 0 )
   {
      InternalAddRef();
      AtlUnadvise(m_Superelevations,IID_ISuperelevationCollectionEvents,m_dwSuperelevationCookie);
   }

   if ( m_dwWideningCookie != 0 )
   {
      InternalAddRef();
      AtlUnadvise(m_Widenings,IID_IWideningCollectionEvents,m_dwWideningCookie);
   }
}

STDMETHODIMP CSurface::InterfaceSupportsErrorInfo(REFIID riid)
{
   static const IID* arr[] = 
   {
      &IID_ISurface,
      &IID_IStructuredStorage2
   };
   for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
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

   m_SurfaceTemplates->putref_Profile(m_pProfile);
   m_Superelevations->putref_Profile(m_pProfile);
   m_Widenings->putref_Profile(m_pProfile);

   return S_OK;
}

STDMETHODIMP CSurface::get_SurfaceTemplates(ISurfaceTemplateCollection** ppTemplates)
{
   CHECK_RETOBJ(ppTemplates);
   (*ppTemplates) = m_SurfaceTemplates;
   (*ppTemplates)->AddRef();
   return S_OK;
}

STDMETHODIMP CSurface::put_AlignmentPoint(IndexType pntIdx)
{
   if ( pntIdx == INVALID_INDEX )
      return E_INVALIDARG;

   if ( m_ProfilePointIdx != pntIdx )
   {
      m_AlignmentPointIdx = pntIdx;
      Fire_OnSurfaceChanged(this);
   }

   return S_OK;
}

STDMETHODIMP CSurface::get_AlignmentPoint(IndexType* pntIdx)
{
   CHECK_RETVAL(pntIdx);
   *pntIdx = m_AlignmentPointIdx;
   return S_OK;
}

STDMETHODIMP CSurface::put_ProfileGradePoint(IndexType pntIdx)
{
   if ( pntIdx == INVALID_INDEX )
      return E_INVALIDARG;

   if ( m_ProfilePointIdx != pntIdx )
   {
      m_ProfilePointIdx = pntIdx;
      Fire_OnSurfaceChanged(this);
   }

   return S_OK;
}

STDMETHODIMP CSurface::get_ProfileGradePoint(IndexType* pntIdx)
{
   CHECK_RETVAL(pntIdx);
   *pntIdx = m_ProfilePointIdx;
   return S_OK;
}

STDMETHODIMP CSurface::get_Superelevations(ISuperelevationCollection** ppSuperelevations)
{
   CHECK_RETOBJ(ppSuperelevations);
   (*ppSuperelevations) = m_Superelevations;
   (*ppSuperelevations)->AddRef();
   return S_OK;
}

STDMETHODIMP CSurface::get_Widenings(IWideningCollection** ppWidenings)
{
   CHECK_RETOBJ(ppWidenings);
   (*ppWidenings) = m_Widenings;
   (*ppWidenings)->AddRef();
   return S_OK;
}

STDMETHODIMP CSurface::GetStationRange(IStation** ppStart,IStation** ppEnd)
{
   IndexType count;
   m_SurfaceTemplates->get_Count(&count);
   if ( count == 0 )
   {
      // A surface needs a minimum of 2 templates
      return SurfaceError(IDS_E_SURFACELAYOUTERROR,COGO_E_SURFACELAYOUTERROR);
   }

   CComPtr<ISurfaceTemplate> startTemplate, endTemplate;
   m_SurfaceTemplates->get_Item(0,&startTemplate);
   m_SurfaceTemplates->get_Item(count-1,&endTemplate);
   HRESULT hr;
   hr = startTemplate->get_Station(ppStart);
   if ( FAILED(hr) )
      return hr;
   
   hr = endTemplate->get_Station(ppEnd);
   if ( FAILED(hr) )
      return hr;

   return S_OK;
}

STDMETHODIMP CSurface::CreateSurfaceTemplate(VARIANT varStation,VARIANT_BOOL bApplySuperelevations,ISurfaceTemplate** ppSurfaceTemplate)
{
   CHECK_RETOBJ(ppSurfaceTemplate);
   // Creates the actual surface at the specified station. If bApplySuperelevationsAndWidenings is true
   // the surface is adjusted for superelevations and widenings, otherwise the surface is based on
   // the basic templates alone.

   // Find the two surface templates that bound the station.
   CComPtr<ISurfaceTemplate> template1, template2;
   HRESULT hr = m_SurfaceTemplates->GetBoundingTemplates(varStation,&template1,&template2);
   if ( FAILED(hr) )
      return hr;
   
   // number of templates segments must be the same in both templates
   IndexType nSegments1,nSegments2;
   template1->get_Count(&nSegments1);
   template2->get_Count(&nSegments2);
   ATLASSERT(nSegments1 == nSegments2);
   if ( nSegments1 != nSegments2 )
   {
      // Number of template segments must the be the same in adjacent surface templates.
      return SurfaceError(IDS_E_SURFACEDEFINITIONERROR,COGO_E_SURFACEDEFINITIONERROR);
   }

   // interplotation factor
   CComPtr<IStation> objStation;
   hr = cogoUtil::StationFromVariant(varStation,false,&objStation);
   if ( FAILED(hr) )
      return hr;

   CComPtr<IStation> objStation1, objStation2;
   template1->get_Station(&objStation1);
   template2->get_Station(&objStation2);

   Float64 station  = cogoUtil::GetNormalizedStationValue(m_pProfile,objStation);
   Float64 station1 = cogoUtil::GetNormalizedStationValue(m_pProfile,objStation1);
   Float64 station2 = cogoUtil::GetNormalizedStationValue(m_pProfile,objStation2);
   Float64 factor = (station-station1)/(station2-station1);
   // interpolated value = (factor)(value2-value1) + value1

   CComObject<CSurfaceTemplate>* pTemplate;
   CComObject<CSurfaceTemplate>::CreateInstance(&pTemplate);
   (*ppSurfaceTemplate) = pTemplate;
   (*ppSurfaceTemplate)->AddRef();

   for ( IndexType segIdx = 0; segIdx < nSegments1; segIdx++ )
   {
      // Get these values from the Template
      Float64 width1,width2;
      Float64 slope1,slope2;
      TemplateSlopeType slopeType1, slopeType2;

      CComPtr<ITemplateSegment> segment1, segment2;
      template1->get_Item(segIdx,&segment1);
      template2->get_Item(segIdx,&segment2);

      segment1->get_Width(&width1);
      segment1->get_Slope(&slope1);
      segment1->get_SlopeType(&slopeType1);

      segment2->get_Width(&width2);
      segment2->get_Slope(&slope2);
      segment2->get_SlopeType(&slopeType2);

      if ( slopeType1 != slopeType2 && (slopeType1 == tsHorizontal || slopeType2 == tsHorizontal) )
      {
         // cannot interpolate between slopes if one is fixed and one is not
         // (what is the resulting slope? fixed/not fixed???)
         ATLASSERT(false);
         return SurfaceError(IDS_E_SURFACESLOPEMISMATCHERROR,COGO_E_SURFACESLOPEMISMATCHERROR);
      }

      // Interpolate slope
      Float64 slope = 0;
      TemplateSlopeType slopeType = tsHorizontal;
      if ( slopeType1 != tsHorizontal || slopeType2 != tsHorizontal && slopeType1 != slopeType2 )
      {
         // interpolation is a little bit tricky because one slope is fixed horizontal and one is fixed vertical
         // Convert slopes so that they are both horizontal.
         Float64 s1 = (slopeType1 == tsFixedVertical ? (IsZero(slope1,0.00001) ? ::BinarySign(slope1)*DBL_MAX : 1/slope1) : slope1);
         Float64 s2 = (slopeType2 == tsFixedVertical ? (IsZero(slope2,0.00001) ? ::BinarySign(slope2)*DBL_MAX : 1/slope2) : slope2);
         slope = factor*(s2-s1)+s1;
         slopeType = tsFixedHorizontal;
      }
      else
      {
         slopeType = slopeType1;
         slope = factor*(slope2-slope1)+slope1;
      }

      // Interpolate width
      Float64 width = factor*(width2-width1)+width1;

      // Add widening
      Float64 widening;
      hr = GetWidening(objStation,segIdx,&widening);
      if ( FAILED(hr) )
         return hr;

      width += widening;

      if ( bApplySuperelevations == VARIANT_TRUE )
      {
         // Add superelevation
         hr = GetSuperelevation(objStation,segIdx,slope,slopeType,&slope,&slopeType);
         if ( FAILED(hr) )
            return hr;
      }

      // Add to segment we are created
      (*ppSurfaceTemplate)->AddSegment(width,slope,slopeType);
   }

   return S_OK;
}

STDMETHODIMP CSurface::Clone(ISurface** ppClone)
{
   CHECK_RETOBJ(ppClone);

   CComObject<CSurface>* pClone;
   CComObject<CSurface>::CreateInstance(&pClone);

   CComPtr<ISurfaceTemplateCollection> surfaceTemplates;
   m_SurfaceTemplates->Clone(&surfaceTemplates);

   CComPtr<ISuperelevationCollection> superelevations;
   m_Superelevations->Clone(&superelevations);

   CComPtr<IWideningCollection> widenings;
   m_Widenings->Clone(&widenings);

   pClone->Init(m_pProfile,surfaceTemplates,m_AlignmentPointIdx,m_ProfilePointIdx,superelevations,widenings);

   (*ppClone) = pClone;
   (*ppClone)->AddRef();
   
   return S_OK;
}

STDMETHODIMP CSurface::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

// IStructuredStorage2
STDMETHODIMP CSurface::Save(IStructuredSave2* pSave)
{
#pragma Reminder("IMPLEMENT CSurface:Save")
   pSave->BeginUnit(CComBSTR("Surface"),1.0);
   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CSurface::Load(IStructuredLoad2* pLoad)
{
#pragma Reminder("IMPLEMENT CSurface::Load")

   CComVariant var;
   pLoad->BeginUnit(CComBSTR("Surface"));


   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   return S_OK;
}

HRESULT CSurface::GetWidening(IStation* station,IndexType templateSegmentIdx,Float64* pWidening)
{
   CComPtr<IWidening> widening;
   m_Widenings->GetWidening(CComVariant(station),&widening);
   if ( widening == NULL )
   {
      *pWidening = 0.0; // no widening at this station
      return S_OK;
   }

   return widening->GetWidening(CComVariant(station),templateSegmentIdx,pWidening);
}

HRESULT CSurface::GetSuperelevation(IStation* station,IndexType templateSegmentIdx,Float64 slope,TemplateSlopeType slopeType,Float64* pSlope,TemplateSlopeType* pSlopeType)
{
   CComPtr<ISuperelevation> superelevation;
   m_Superelevations->GetSuperelevation(CComVariant(station),&superelevation);
   if ( superelevation == NULL )
   {
      // no superelevation at this station... just return the original values
      *pSlope = slope;
      *pSlopeType = slopeType;
   }
   else
   {
      // in a superelevation region
      if ( slopeType == tsHorizontal )
      {
         // slope can be adjusted by superelevation
         HRESULT hr = superelevation->GetSlope(CComVariant(station),slope,pSlope);
         if ( FAILED(hr) )
            return hr;

         *pSlopeType = tsHorizontal;
      }
      else
      {
         // slope is one of the fixed type.... not altered by superelevation
         // just return the original values
         *pSlope = slope;
         *pSlopeType = slopeType;
      }
   }

   return S_OK;
}

HRESULT CSurface::SurfaceError(UINT nHelpString,HRESULT hRes)
{
   USES_CONVERSION;

   TCHAR str[256];
   ::LoadString( _Module.GetModuleInstance(), nHelpString, str, 256);
   CComBSTR oleMsg(str);
   return Error(oleMsg, IID_ISurface, hRes);
}
