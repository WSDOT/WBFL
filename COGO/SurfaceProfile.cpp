///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry
// Copyright © 1999-2021  Washington State Department of Transportation
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
#include "Station.h"
#include "Direction.h"
#include "SurfacePoint.h"
#include <WBFLCogo\CogoHelpers.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

bool SortByOffset(CComPtr<ISurfacePoint>& p1,CComPtr<ISurfacePoint>& p2)
{
   Float64 offset1, offset2;
   p1->get_CutLineOffset(&offset1);
   p2->get_CutLineOffset(&offset2);
   return offset1 < offset2 && !IsEqual(offset1,offset2);
}

bool IsEqualOffset(CComPtr<ISurfacePoint>& p1,CComPtr<ISurfacePoint>& p2)
{
   Float64 offset1, offset2;
   p1->get_CutLineOffset(&offset1);
   p2->get_CutLineOffset(&offset2);
   return IsEqual(offset1,offset2);
}

/////////////////////////////////////////////////////////////////////////////
// CSurfaceProfile

HRESULT CSurfaceProfile::FinalConstruct()
{
   m_pSurface = nullptr;

   CComObject<CStation>* pStation;
   CComObject<CStation>::CreateInstance(&pStation);
   m_Station = pStation;

   CComObject<CDirection>* pDirection;
   CComObject<CDirection>::CreateInstance(&pDirection);
   m_Direction = pDirection;

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
   for( auto& surfacePoint : m_SurfacePoints)
   {
      surfacePoint->putref_Surface(m_pSurface);
   }
   return S_OK;
}

STDMETHODIMP CSurfaceProfile::put_Station(VARIANT varStation)
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
      //Fire_OnSurfaceProfileChanged(this);
   }

   return S_OK;
}

STDMETHODIMP CSurfaceProfile::get_Station(IStation** station)
{
   return m_Station->Clone(station);
}

STDMETHODIMP CSurfaceProfile::put_Direction(VARIANT varDirection)
{
   CComPtr<IDirection> objDirection;
   HRESULT hr = cogoUtil::DirectionFromVariant(varDirection,&objDirection);
   if ( FAILED(hr) )
   {
      return hr;
   }

   m_Direction.Release();
   objDirection->Clone(&m_Direction);
   return S_OK;
}

STDMETHODIMP CSurfaceProfile::get_Direction(IDirection** direction)
{
   return m_Direction->Clone(direction);
}

STDMETHODIMP CSurfaceProfile::AddPoint(VARIANT varStation,Float64 normalOffset,Float64 cutLineOffset,Float64 elev,IPoint2d* pnt)
{
   CComObject<CSurfacePoint>* pPoint;
   CComObject<CSurfacePoint>::CreateInstance(&pPoint);
   CComPtr<ISurfacePoint> point = pPoint;
   point->put_Station(varStation);
   point->put_NormalOffset(normalOffset);
   point->put_CutLineOffset(cutLineOffset);
   point->put_Elevation(elev);
   point->put_Location(pnt);
   return AddPointEx(point);
}

STDMETHODIMP CSurfaceProfile::AddPointEx(ISurfacePoint* point)
{
   CHECK_IN(point);
   point->putref_Surface(m_pSurface);
   m_SurfacePoints.push_back(point);
   std::sort(m_SurfacePoints.begin(),m_SurfacePoints.end(),SortByOffset); // sort by offset
   m_SurfacePoints.erase(std::unique(m_SurfacePoints.begin(),m_SurfacePoints.end(),IsEqualOffset),m_SurfacePoints.end());
   return S_OK;
}

STDMETHODIMP CSurfaceProfile::RemovePoint(CollectionIndexType idx)
{
   if ( m_SurfacePoints.size() <= idx )
   {
      return E_INVALIDARG;
   }

   m_SurfacePoints.erase(m_SurfacePoints.begin() + idx);
   //Fire_OnProfileSegmentRemoved(this);
   return S_OK;
}

STDMETHODIMP CSurfaceProfile::get_Count(CollectionIndexType* count)
{
   CHECK_RETVAL(count);
   *count = m_SurfacePoints.size();
   return S_OK;
}

STDMETHODIMP CSurfaceProfile::get_Item(CollectionIndexType idx,ISurfacePoint** point)
{
   CHECK_RETOBJ(point);
   if ( m_SurfacePoints.size() <= idx )
   {
      return E_INVALIDARG;
   }

   m_SurfacePoints[idx].CopyTo(point);

   return S_OK;
}

STDMETHODIMP CSurfaceProfile::Clear()
{
   m_SurfacePoints.clear();
   //Fire_OnProfileSegmentsCleared(this);
   return S_OK;
}

STDMETHODIMP CSurfaceProfile::GetSurfacePointElevationChange(CollectionIndexType surfacePoint1Idx,CollectionIndexType surfacePoint2Idx,Float64* deltaElevation)
{
   // computes the change in elevation between two surface points
   CHECK_RETVAL(deltaElevation);
   if ( m_SurfacePoints.size() < surfacePoint1Idx || m_SurfacePoints.size() < surfacePoint2Idx )
   {
      return SurfaceProfileError(IDS_E_INVALIDRIDGEPOINT,COGO_E_INVALIDRIDGEPOINTINDEX);
   }

   CComPtr<ISurfacePoint> sp1;
   CComPtr<ISurfacePoint> sp2;
   get_Item(surfacePoint1Idx,&sp1);
   get_Item(surfacePoint2Idx,&sp2);

   Float64 elev1,elev2;
   sp1->get_Elevation(&elev1);
   sp2->get_Elevation(&elev2);
   *deltaElevation = elev2 - elev1;
   return S_OK;
}

STDMETHODIMP CSurfaceProfile::GetElevationChange(CollectionIndexType surfacePointIdx,Float64 offset,Float64* deltaElevation)
{
   // Computes the change in elevation between a surface point and an offset measured from the surface point
   CHECK_RETVAL(deltaElevation);
   if ( m_SurfacePoints.size() < surfacePointIdx )
   {
      return SurfaceProfileError(IDS_E_INVALIDRIDGEPOINT,COGO_E_INVALIDRIDGEPOINTINDEX);
   }

   Float64 sign = ::BinarySign(offset);

   Float64 delta = 0;
   if ( 0 <= offset )
   {
      // working left to right from the specified surface point
      IndexType nSurfacePoints = m_SurfacePoints.size();
      Float64 running_offset = 0;
      for ( IndexType idx = surfacePointIdx; idx < nSurfacePoints-1; idx++ )
      {
         CComPtr<ISurfacePoint> sp1,sp2;
         get_Item(idx,&sp1);
         get_Item(idx+1,&sp2);
         CComPtr<IPoint3d> pnt1,pnt2;
         sp1->GetPoint(&pnt1);
         sp2->GetPoint(&pnt2);
         Float64 dist;
         pnt2->DistanceEx(pnt1,&dist);
         Float64 z1,z2;
         pnt1->get_Z(&z1);
         pnt2->get_Z(&z2);
         Float64 dz = z2-z1;

         if ( offset < running_offset+dist )
         {
            // the second point is beyond the point we are looking for
            // get the distance to the point
            Float64 z = offset - running_offset;
            dz = ::LinInterp(z,z1,z2,dist);
            delta += dz;
            break; // don't go any furter
         }
         delta += dz;

         running_offset += dist;
      }
   }
   else
   {
      // working right to left from the specified surface point
      Float64 running_offset = 0;
      for ( IndexType idx = surfacePointIdx; 0 < idx; idx-- )
      {
         CComPtr<ISurfacePoint> sp1,sp2;
         get_Item(idx-1,&sp1);
         get_Item(idx,&sp2);
         CComPtr<IPoint3d> pnt1,pnt2;
         sp1->GetPoint(&pnt1);
         sp2->GetPoint(&pnt2);
         Float64 dist;
         pnt2->DistanceEx(pnt1,&dist);
         Float64 z1,z2;
         pnt1->get_Z(&z1);
         pnt2->get_Z(&z2);
         Float64 dz = z2-z1;


         if ( running_offset-dist < offset )
         {
            // the first point is before the point we are looking for
            // get the distance to the point
            Float64 z = running_offset - offset;
            dz = ::LinInterp(z,z2,z1,dist);
            delta += dz;
            break; // don't go any furter
         }
         delta += dz;
         running_offset -= dist;
      }
   }

   *deltaElevation = delta;
   return S_OK;
}

STDMETHODIMP CSurfaceProfile::GetSlope(CollectionIndexType surfacePointIdx,Float64 offset,Float64* pSlope)
{
   CHECK_RETVAL(pSlope);

   if ( m_SurfacePoints.size() < surfacePointIdx )
   {
      return SurfaceProfileError(IDS_E_INVALIDRIDGEPOINT,COGO_E_INVALIDRIDGEPOINTINDEX);
   }

   if ( 0 <= offset )
   {
      // working left to right from the specified surface point
      Float64 leftEdge = 0;
      IndexType nSurfacePoints = m_SurfacePoints.size();
      for ( IndexType idx = surfacePointIdx; idx < nSurfacePoints-1; idx++ )
      {
         CComPtr<ISurfacePoint> sp1,sp2;
         get_Item(idx,&sp1);
         get_Item(idx+1,&sp2);
         CComPtr<IPoint3d> pnt1,pnt2;
         sp1->GetPoint(&pnt1);
         sp2->GetPoint(&pnt2);
         Float64 dist;
         pnt2->DistanceEx(pnt1,&dist);
         Float64 z1,z2;
         pnt1->get_Z(&z1);
         pnt2->get_Z(&z2);
         Float64 dz = z2-z1;

         if ( ::InRange(leftEdge,offset,leftEdge+dist) )
         {
            *pSlope = dz/dist;
            return S_OK;
         }

         leftEdge += dist;
      }
   }
   else
   {
      // working right to left from the specified surface point
      Float64 rightEdge = 0;
      for ( IndexType idx = surfacePointIdx-1; 0 < idx; idx-- )
      {
         CComPtr<ISurfacePoint> sp1,sp2;
         get_Item(idx-1,&sp1);
         get_Item(idx,&sp2);
         CComPtr<IPoint3d> pnt1,pnt2;
         sp1->GetPoint(&pnt1);
         sp2->GetPoint(&pnt2);
         Float64 dist;
         pnt2->DistanceEx(pnt1,&dist);
         Float64 z1,z2;
         pnt1->get_Z(&z1);
         pnt2->get_Z(&z2);
         Float64 dz = z2-z1;

         if ( ::InRange(rightEdge-dist,offset,rightEdge) )
         {
            *pSlope = dz/dist;
            return S_OK;
         }

         rightEdge -= dist;
      }
   }

   // if we got this far, the offset is beyond the surface boundary so the slope is 0
   *pSlope = 0;
   return S_OK;
}

STDMETHODIMP CSurfaceProfile::GetSegmentSlope(CollectionIndexType segmentIdx,Float64* pSlope)
{
   CHECK_RETVAL(pSlope);

   CComPtr<ISurfacePoint> sp1,sp2;
   get_Item(segmentIdx,&sp1);
   get_Item(segmentIdx+1,&sp2);
   CComPtr<IPoint3d> pnt1,pnt2;
   sp1->GetPoint(&pnt1);
   sp2->GetPoint(&pnt2);
   Float64 dist;
   pnt2->DistanceEx(pnt1,&dist);
   Float64 z1,z2;
   pnt1->get_Z(&z1);
   pnt2->get_Z(&z2);
   Float64 dz = z2-z1;
   *pSlope = dz/dist;

   return S_OK;
}
   
STDMETHODIMP CSurfaceProfile::GetSurfacePointOffset(IndexType surfacePointIdx,Float64* pOffset)
{
   CComPtr<ISurfacePoint> sp;
   get_Item(surfacePointIdx,&sp);
   return sp->get_CutLineOffset(pOffset);
}

STDMETHODIMP CSurfaceProfile::GetSurfacePointElevation(IndexType surfacePointIdx,Float64* pOffset,Float64* pElev)
{
   CComPtr<ISurfacePoint> sp;
   get_Item(surfacePointIdx,&sp);
   sp->get_CutLineOffset(pOffset);
   sp->get_Elevation(pElev);
   return S_OK;
}

STDMETHODIMP CSurfaceProfile::Clone(ISurfaceProfile** ppClone)
{
   CHECK_RETOBJ(ppClone);

   CComObject<CSurfaceProfile>* pClone;
   CComObject<CSurfaceProfile>::CreateInstance(&pClone);

   pClone->putref_Surface(m_pSurface);
   pClone->put_Station(CComVariant(m_Station));
   pClone->put_Direction(CComVariant(m_Direction));

   std::vector<CComPtr<ISurfacePoint>>::iterator iter(m_SurfacePoints.begin());
   std::vector<CComPtr<ISurfacePoint>>::iterator end(m_SurfacePoints.end());
   for ( ; iter != end; iter++ )
   {
      CComPtr<ISurfacePoint> point(*iter);
      CComPtr<ISurfacePoint> clone;
      point->Clone(&clone);
      pClone->AddPointEx(clone);
   }

   (*ppClone) = pClone;
   (*ppClone)->AddRef();
   
   return S_OK;
}

STDMETHODIMP CSurfaceProfile::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

// IStructuredStorage2
STDMETHODIMP CSurfaceProfile::Save(IStructuredSave2* pSave)
{
#pragma Reminder("IMPLEMENT CSurfaceProfile:Save")
   pSave->BeginUnit(CComBSTR("SurfaceProfile"),1.0);
   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CSurfaceProfile::Load(IStructuredLoad2* pLoad)
{
#pragma Reminder("IMPLEMENT CSurfaceProfile::Load")

   CComVariant var;
   pLoad->BeginUnit(CComBSTR("SurfaceProfile"));


   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   return S_OK;
}

HRESULT CSurfaceProfile::ValidateStation(IStation* station)
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

HRESULT CSurfaceProfile::SurfaceProfileError(UINT nHelpString,HRESULT hRes)
{
   USES_CONVERSION;

   TCHAR str[256];
   ::LoadString( _Module.GetModuleInstance(), nHelpString, str, 256);
   CComBSTR oleMsg(str);
   return Error(oleMsg, IID_ISurfaceProfile, hRes);
}
