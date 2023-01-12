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
#include "Station.h"
#include "TemplateSegment.h"
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
   m_pSurface = nullptr;

   CComObject<CStation>* pStation;
   CComObject<CStation>::CreateInstance(&pStation);
   m_Station = pStation;

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
      &IID_IStructuredStorage2
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

STDMETHODIMP CSurfaceTemplate::put_Station(VARIANT varStation)
{
   CComPtr<IStation> objStation;
   HRESULT hr = cogoUtil::StationFromVariant(varStation,false,&objStation);
   if ( FAILED(hr) )
   {
      return hr;
   }

   hr = ValidateStation(objStation);
   if ( FAILED(hr) )
   {
      return hr;
   }

   CComPtr<IProfile> profile;
   if ( m_pSurface )
   {
      m_pSurface->get_Profile(&profile); 
   }
   if ( !cogoUtil::IsEqual(profile,objStation,m_Station) )
   {
      m_Station.Release();
      objStation->Clone(&m_Station);
      Fire_OnSurfaceTemplateChanged(this);
   }

   return S_OK;
}

STDMETHODIMP CSurfaceTemplate::get_Station(IStation** station)
{
   return m_Station->Clone(station);
}

STDMETHODIMP CSurfaceTemplate::AddSegment(Float64 width,Float64 slope,TemplateSlopeType slopeType)
{
   CComObject<CTemplateSegment>* pTemplateSegment;
   CComObject<CTemplateSegment>::CreateInstance(&pTemplateSegment);
   pTemplateSegment->Init(width,slope,slopeType);
   CComPtr<ITemplateSegment> segment(pTemplateSegment);
   return AddSegmentEx(segment);
}

STDMETHODIMP CSurfaceTemplate::AddSegmentEx(ITemplateSegment* segment)
{
   CHECK_IN(segment);
   m_Segments.push_back(segment);
   Fire_OnTemplateSegmentAdded(this,segment);
   return S_OK;
}

STDMETHODIMP CSurfaceTemplate::RemoveSegment(CollectionIndexType idx)
{
   if ( m_Segments.size() <= idx )
   {
      return E_INVALIDARG;
   }

   m_Segments.erase(m_Segments.begin() + idx);
   Fire_OnTemplateSegmentRemoved(this);
   return S_OK;
}

STDMETHODIMP CSurfaceTemplate::get_Count(CollectionIndexType* count)
{
   CHECK_RETVAL(count);
   *count = m_Segments.size();
   return S_OK;
}

STDMETHODIMP CSurfaceTemplate::get_Item(CollectionIndexType idx,ITemplateSegment** segment)
{
   CHECK_RETOBJ(segment);
   if ( m_Segments.size() <= idx )
   {
      return E_INVALIDARG;
   }

   m_Segments[idx].CopyTo(segment);

   return S_OK;
}

STDMETHODIMP CSurfaceTemplate::Clear()
{
   m_Segments.clear();
   Fire_OnTemplateSegmentsCleared(this);
   return S_OK;
}

STDMETHODIMP CSurfaceTemplate::GetRidgePointElevationChange(CollectionIndexType ridgePoint1Idx,CollectionIndexType ridgePoint2Idx,Float64* deltaElevation)
{
   // computes the change in elevation between two ridge points
   CHECK_RETVAL(deltaElevation);
   if ( m_Segments.size() < ridgePoint1Idx || m_Segments.size() < ridgePoint2Idx )
   {
      return SurfaceTemplateError(IDS_E_INVALIDRIDGEPOINT,COGO_E_INVALIDRIDGEPOINTINDEX);
   }

   Float64 sign = ::BinarySign((int)ridgePoint2Idx - (int)ridgePoint1Idx);
   Float64 delta = 0;
   IndexType startIdx = min(ridgePoint1Idx,ridgePoint2Idx);
   IndexType endIdx   = max(ridgePoint1Idx,ridgePoint2Idx);
   for ( IndexType idx = startIdx; idx < endIdx; idx++ )
   {
      Float64 width,slope;
      TemplateSlopeType slopeType;
      CComPtr<ITemplateSegment> segment;
      get_Item(idx,&segment);

      segment->get_Width(&width);
      segment->get_Slope(&slope);
      segment->get_SlopeType(&slopeType);

      delta += sign*width*slope;
   }

   *deltaElevation = delta;
   return S_OK;
}

STDMETHODIMP CSurfaceTemplate::GetElevationChange(CollectionIndexType ridgePointIdx,Float64 offset,Float64* deltaElevation)
{
   // Computes the change in elevation between a ridge point and an offset measured from the ridge point
   CHECK_RETVAL(deltaElevation);
   if ( m_Segments.size() < ridgePointIdx )
   {
      return SurfaceTemplateError(IDS_E_INVALIDRIDGEPOINT,COGO_E_INVALIDRIDGEPOINTINDEX);
   }

   Float64 sign = ::BinarySign(offset);

   Float64 delta = 0;
   if ( 0 <= offset )
   {
      // working left to right from the specified ridge point
      SegmentIndexType nSegments = m_Segments.size();
      Float64 running_offset = 0;
      for ( IndexType idx = ridgePointIdx; idx < nSegments; idx++ )
      {
         Float64 width,slope;
         TemplateSlopeType slopeType;
         CComPtr<ITemplateSegment> segment;
         get_Item(idx,&segment);

         segment->get_Width(&width);
         segment->get_Slope(&slope);
         segment->get_SlopeType(&slopeType);

         if ( offset < running_offset+width )
         {
            // the end of this segment is beyond the point we are looking for
            // get distance to the point
            width = offset - running_offset;
            delta += sign*width*slope;
            break; // don't go any further
         }

         delta += sign*width*slope;

         running_offset += width;
      }
   }
   else
   {
      // working right to left from the specified ridge point
      Float64 running_offset = 0;
      for ( IndexType idx = ridgePointIdx-1; idx != INVALID_INDEX; idx-- )
      {
         Float64 width,slope;
         TemplateSlopeType slopeType;
         CComPtr<ITemplateSegment> segment;
         get_Item(idx,&segment);

         segment->get_Width(&width);
         segment->get_Slope(&slope);
         segment->get_SlopeType(&slopeType);

         if ( running_offset-width < offset )
         {
            width = running_offset-offset;
            delta += sign*width*slope;
            break; // don't go any further
         }
         delta += sign*width*slope;
         running_offset -= width;
      }
   }

   *deltaElevation = delta;
   return S_OK;
}

STDMETHODIMP CSurfaceTemplate::GetSlope(CollectionIndexType ridgePointIdx,Float64 offset,Float64* pSlope)
{
   CHECK_RETVAL(pSlope);

   if ( m_Segments.size() < ridgePointIdx )
   {
      return SurfaceTemplateError(IDS_E_INVALIDRIDGEPOINT,COGO_E_INVALIDRIDGEPOINTINDEX);
   }

   if ( 0 <= offset )
   {
      // working left to right from the specified ridge point
      Float64 leftEdge = 0;
      SegmentIndexType nSegments = m_Segments.size();
      for ( IndexType idx = ridgePointIdx; idx < nSegments; idx++ )
      {
         Float64 width,slope;
         TemplateSlopeType slopeType;
         CComPtr<ITemplateSegment> segment;
         get_Item(idx,&segment);

         segment->get_Width(&width);
         segment->get_Slope(&slope);
         segment->get_SlopeType(&slopeType);

         if ( ::InRange(leftEdge,offset,leftEdge+width) )
         {
            if ( slopeType == tsFixedVertical )
            {
               *pSlope = (IsZero(slope,0.00001) ? ::BinarySign(slope)*DBL_MAX : 1/slope);
            }
            else
            {
               *pSlope = slope;
            }
            return S_OK;
         }

         leftEdge += width;
      }
   }
   else
   {
      // working right to left from the specified ridge point
      Float64 rightEdge = 0;
      for ( IndexType idx = ridgePointIdx-1; idx != INVALID_INDEX; idx-- )
      {
         Float64 width,slope;
         TemplateSlopeType slopeType;
         CComPtr<ITemplateSegment> segment;
         get_Item(idx,&segment);

         segment->get_Width(&width);
         segment->get_Slope(&slope);
         segment->get_SlopeType(&slopeType);

         if ( ::InRange(rightEdge-width,offset,rightEdge) )
         {
            if ( slopeType == tsFixedVertical )
            {
               *pSlope = (IsZero(slope,0.00001) ? ::BinarySign(slope)*DBL_MAX : 1/slope);
            }
            else
            {
               *pSlope = slope;
            }

            return S_OK;
         }

         rightEdge -= width;
      }
   }

   // if we got this far, the offset is beyond the surface boundary so the slope is 0
   *pSlope = 0;
   return S_OK;
}

STDMETHODIMP CSurfaceTemplate::GetSegmentSlope(CollectionIndexType segmentIdx,Float64* pSlope)
{
   CHECK_RETVAL(pSlope);

   CComPtr<ITemplateSegment> segment;
   HRESULT hr = get_Item(segmentIdx,&segment);
   if ( FAILED(hr) )
      return hr;

   Float64 width,slope;
   TemplateSlopeType slopeType;

   segment->get_Width(&width);
   segment->get_Slope(&slope);
   segment->get_SlopeType(&slopeType);

   if ( slopeType == tsFixedVertical )
   {
      *pSlope = (IsZero(slope,0.00001) ? ::BinarySign(slope)*DBL_MAX : 1/slope);
   }
   else
   {
      *pSlope = slope;
   }

   return S_OK;
}
   
STDMETHODIMP CSurfaceTemplate::GetRidgePointOffset(IndexType ridgePointIdx,IndexType refPointIdx,Float64* pOffset)
{
   if ( ridgePointIdx == refPointIdx )
   {
      *pOffset = 0;
      return S_OK;
   }

   IndexType startSegmentIdx = Min(refPointIdx,ridgePointIdx);
   IndexType endSegmentIdx   = Max(refPointIdx,ridgePointIdx);
   *pOffset = 0;
   for ( IndexType idx = startSegmentIdx; idx < endSegmentIdx; idx++ )
   {
      CComPtr<ITemplateSegment> segment;
      HRESULT hr = get_Item(idx,&segment);
      if ( FAILED(hr) )
      {
         return hr;
      }

      Float64 width;
      segment->get_Width(&width);
      *pOffset += width;
   }

   // ridge point is to the left of the reference point
   // so offset is to the left (negative value)
   if ( ridgePointIdx < refPointIdx )
   {
      *pOffset *= -1;
   }

   return S_OK;
}

STDMETHODIMP CSurfaceTemplate::GetRidgePointElevation(IndexType ridgePointIdx,IndexType refPointIdx,Float64* pOffset,Float64* pElev)
{
   if ( m_pSurface == nullptr )
   {
      ATLASSERT(false); // must be associated with a surface
      return E_FAIL;
   }

   // Gets the offset and elevation of the specified ridge point at the station provided. Offset is measured from the ridge point identified by refPointIdx
   HRESULT hr = GetRidgePointOffset(ridgePointIdx,refPointIdx,pOffset);
   if ( FAILED(hr) )
   {
      return hr;
   }

   CComPtr<IProfile> profile;
   m_pSurface->get_Profile(&profile);

   hr = profile->Elevation(CComVariant(m_Station),*pOffset,pElev);
   if ( FAILED(hr) )
   {
      return hr;
   }

   return S_OK;
}

STDMETHODIMP CSurfaceTemplate::Clone(ISurfaceTemplate** ppClone)
{
   CHECK_RETOBJ(ppClone);

   CComObject<CSurfaceTemplate>* pClone;
   CComObject<CSurfaceTemplate>::CreateInstance(&pClone);

   pClone->putref_Surface(m_pSurface);
   pClone->put_Station(CComVariant(m_Station));

   std::vector<CComPtr<ITemplateSegment>>::iterator iter(m_Segments.begin());
   std::vector<CComPtr<ITemplateSegment>>::iterator end(m_Segments.end());
   for ( ; iter != end; iter++ )
   {
      CComPtr<ITemplateSegment> segment(*iter);
      CComPtr<ITemplateSegment> clone;
      segment->Clone(&clone);
      pClone->AddSegmentEx(clone);
   }

   (*ppClone) = pClone;
   (*ppClone)->AddRef();
   
   return S_OK;
}

STDMETHODIMP CSurfaceTemplate::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

// IStructuredStorage2
STDMETHODIMP CSurfaceTemplate::Save(IStructuredSave2* pSave)
{
#pragma Reminder("IMPLEMENT CSurfaceTemplate:Save")
   pSave->BeginUnit(CComBSTR("SurfaceTemplate"),1.0);
   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CSurfaceTemplate::Load(IStructuredLoad2* pLoad)
{
#pragma Reminder("IMPLEMENT CSurfaceTemplate::Load")

   CComVariant var;
   pLoad->BeginUnit(CComBSTR("SurfaceTemplate"));


   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   return S_OK;
}

HRESULT CSurfaceTemplate::ValidateStation(IStation* station)
{
   CComPtr<IProfile> profile;
   if ( m_pSurface )
   {
      m_pSurface->get_Profile(&profile); 
   }
   if ( profile == nullptr )
   {
      // if not associated with a profile, station must be normalized
      ZoneIndexType staEqnZoneIdx;
      station->get_StationZoneIndex(&staEqnZoneIdx);
      if ( staEqnZoneIdx != INVALID_INDEX )
      {
         return E_INVALIDARG; // station must be normalized
      }
   }

   return S_OK;
}

HRESULT CSurfaceTemplate::SurfaceTemplateError(UINT nHelpString,HRESULT hRes)
{
   USES_CONVERSION;

   TCHAR str[256];
   ::LoadString( _Module.GetModuleInstance(), nHelpString, str, 256);
   CComBSTR oleMsg(str);
   return Error(oleMsg, IID_ISurfaceTemplate, hRes);
}
