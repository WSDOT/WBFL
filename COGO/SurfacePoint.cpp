///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry
// Copyright © 1999-2015  Washington State Department of Transportation
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

// SurfacePoint.cpp : Implementation of CSurfacePoint
#include "stdafx.h"
#include "WBFLCOGO.h"
#include "SurfacePoint.h"
#include <WBFLCogo\CogoHelpers.h>
#include "Station.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSurfacePoint
HRESULT CSurfacePoint::FinalConstruct()
{
   CComObject<CStation>* pStation;
   CComObject<CStation>::CreateInstance(&pStation);
   m_Station = pStation;

   m_Location.CoCreateInstance(CLSID_Point2d);

   return S_OK;
}

STDMETHODIMP CSurfacePoint::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ISurfacePoint,
		&IID_IStructuredStorage2,
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CSurfacePoint::get_Surface(ISurface* *pVal)
{
   CHECK_RETOBJ(pVal);
   if ( m_pSurface )
   {
      (*pVal) = m_pSurface;
      (*pVal)->AddRef();
   }

   return S_OK;
}

STDMETHODIMP CSurfacePoint::putref_Surface(ISurface* newVal)
{
   m_pSurface = newVal;
   return S_OK;
}

STDMETHODIMP CSurfacePoint::get_Station(IStation* *station)
{
   CHECK_RETOBJ(station);
   return m_Station->Clone(station);
}

STDMETHODIMP CSurfacePoint::put_Station(VARIANT varStation)
{
   CComPtr<IStation> objStation;
   HRESULT hr = cogoUtil::StationFromVariant(varStation,true,&objStation);
   if ( FAILED(hr) )
      return hr;

   hr = ValidateStation(objStation);
   if ( FAILED(hr) )
      return hr;

   CComPtr<IProfile> profile;
   if ( m_pSurface )
   {
      m_pSurface->get_Profile(&profile);
   }
   if ( !cogoUtil::IsEqual(profile,objStation,m_Station) )
   {
      m_Station.Release();
      objStation->Clone(&m_Station);
      //Fire_OnSurfacePointChanged(this);
   }
	return S_OK;
}

STDMETHODIMP CSurfacePoint::get_NormalOffset(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_NormalOffset;
	return S_OK;
}

STDMETHODIMP CSurfacePoint::put_NormalOffset(Float64 newVal)
{
   if ( !IsEqual(newVal,m_NormalOffset) )
   {
      m_NormalOffset = newVal;
      //Fire_OnSurfacePointChanged(this);
   }
	return S_OK;
}

STDMETHODIMP CSurfacePoint::get_CutLineOffset(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_CutLineOffset;
	return S_OK;
}

STDMETHODIMP CSurfacePoint::put_CutLineOffset(Float64 newVal)
{
   if ( !IsEqual(newVal,m_CutLineOffset) )
   {
      m_CutLineOffset = newVal;
      //Fire_OnSurfacePointChanged(this);
   }
	return S_OK;
}

STDMETHODIMP CSurfacePoint::get_Elevation(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Elevation;
	return S_OK;
}

STDMETHODIMP CSurfacePoint::put_Elevation(Float64 newVal)
{
   if ( !IsEqual(newVal,m_Elevation) )
   {
      m_Elevation = newVal;
      //Fire_OnSurfacePointChanged(this);
   }
	return S_OK;
}

STDMETHODIMP CSurfacePoint::get_Location(IPoint2d** ppLocation)
{
   return m_Location->Clone(ppLocation);
}

STDMETHODIMP CSurfacePoint::put_Location(IPoint2d* pLocation)
{
   CHECK_IN(pLocation);
   Float64 x,y;
   pLocation->Location(&x,&y);
   return m_Location->Move(x,y);
}

STDMETHODIMP CSurfacePoint::GetPoint(IPoint3d** ppPoint)
{
   CHECK_RETOBJ(ppPoint);
   if ( m_pSurface == NULL )
   {
      return E_FAIL;
   }

   CComPtr<IProfile> profile;
   m_pSurface->get_Profile(&profile);

   if ( profile == NULL )
   {
      return E_FAIL;
   }

   CComPtr<IAlignment> alignment;
   profile->get_Alignment(&alignment);

   if ( alignment == NULL )
   {
      return E_FAIL;
   }

   CComPtr<IDirection> normal;
   alignment->Normal(CComVariant(m_Station),&normal);
   CComPtr<IPoint2d> pnt;
   HRESULT hr = alignment->LocatePoint(CComVariant(m_Station),omtAlongDirection,-m_NormalOffset,CComVariant(normal),&pnt); 
   if ( FAILED(hr) )
   {
      return hr;
   }

   Float64 x,y;
   pnt->Location(&x,&y);

   CComPtr<IPoint3d> newPoint;
   newPoint.CoCreateInstance(CLSID_Point3d);
   newPoint->Move(x,y,m_Elevation);
   return newPoint.CopyTo(ppPoint);
}

STDMETHODIMP CSurfacePoint::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

STDMETHODIMP CSurfacePoint::Clone(ISurfacePoint* *clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CSurfacePoint>* pClone;
   CComObject<CSurfacePoint>::CreateInstance(&pClone);

   (*clone) = pClone;
   (*clone)->AddRef();

   (*clone)->put_Elevation(m_Elevation);
   (*clone)->put_NormalOffset(m_NormalOffset);
   (*clone)->put_CutLineOffset(m_CutLineOffset);
   (*clone)->put_Station(CComVariant(m_Station));

   return S_OK;
}

// IStructuredStorage2
STDMETHODIMP CSurfacePoint::Save(IStructuredSave2* pSave)
{
   pSave->BeginUnit(CComBSTR("SurfacePoint"),1.0);
   pSave->put_Property(CComBSTR("Station"),CComVariant(m_Station));
   pSave->put_Property(CComBSTR("NormalOffset"),CComVariant(m_NormalOffset));
   pSave->put_Property(CComBSTR("CutLineOffset"),CComVariant(m_CutLineOffset));
   pSave->put_Property(CComBSTR("Elevation"),CComVariant(m_Elevation));
   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CSurfacePoint::Load(IStructuredLoad2* pLoad)
{
   CComVariant var;
   pLoad->BeginUnit(CComBSTR("SurfacePoint"));

   pLoad->get_Property(CComBSTR("Station"),&var);
   CComPtr<IStation> station;
   _CopyVariantToInterface<IStation>::copy(&station,&var);
   m_Station = station;

   pLoad->get_Property(CComBSTR("NormalOffset"),&var);
   m_NormalOffset = var.dblVal;

   pLoad->get_Property(CComBSTR("CutLineOffset"),&var);
   m_CutLineOffset = var.dblVal;

   pLoad->get_Property(CComBSTR("Elevation"),&var);
   m_Elevation = var.dblVal;

   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   return S_OK;
}

HRESULT CSurfacePoint::ValidateStation(IStation* station)
{
   if ( m_pSurface == NULL )
   {
      // if not associated with a Surface, station must be normalized
      ZoneIndexType staEqnZoneIdx;
      station->get_StationZoneIndex(&staEqnZoneIdx);
      if ( staEqnZoneIdx != INVALID_INDEX )
      {
         return E_INVALIDARG; // station must be normalized
      }
   }

   return S_OK;
}
