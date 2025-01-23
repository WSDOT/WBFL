///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry
// Copyright © 1999-2025  Washington State Department of Transportation
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
   m_SurfacePoint = WBFL::COGO::SurfacePoint::Create();
   return S_OK;
}

STDMETHODIMP CSurfacePoint::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ISurfacePoint,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
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
   return cogoUtil::CreateStation(m_SurfacePoint->GetStation(), station);
}

STDMETHODIMP CSurfacePoint::put_Station(VARIANT varStation)
{
   auto [hr, station] = cogoUtil::StationFromVariant(varStation);
   if (FAILED(hr)) return hr;
   m_SurfacePoint->SetStation(station);
	return S_OK;
}

STDMETHODIMP CSurfacePoint::get_NormalOffset(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_SurfacePoint->GetNormalOffset();
	return S_OK;
}

STDMETHODIMP CSurfacePoint::put_NormalOffset(Float64 newVal)
{
   m_SurfacePoint->SetNormalOffset(newVal);
	return S_OK;
}

STDMETHODIMP CSurfacePoint::get_CutLineOffset(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_SurfacePoint->GetCutlineOffset();
	return S_OK;
}

STDMETHODIMP CSurfacePoint::put_CutLineOffset(Float64 newVal)
{
   m_SurfacePoint->SetCutlineOffset(newVal);
	return S_OK;
}

STDMETHODIMP CSurfacePoint::get_Elevation(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_SurfacePoint->GetElevation();;
	return S_OK;
}

STDMETHODIMP CSurfacePoint::put_Elevation(Float64 newVal)
{
   m_SurfacePoint->SetElevation(newVal);
	return S_OK;
}

STDMETHODIMP CSurfacePoint::get_Location(IPoint2d** ppLocation)
{
   CHECK_RETOBJ(ppLocation);
   return cogoUtil::CreatePoint(m_SurfacePoint->GetLocation(), ppLocation);
}

STDMETHODIMP CSurfacePoint::put_Location(IPoint2d* pLocation)
{
   CHECK_IN(pLocation);
   m_SurfacePoint->SetLocation(cogoUtil::GetPoint(pLocation));
   return S_OK;
}

STDMETHODIMP CSurfacePoint::GetPoint(IPoint3d** ppPoint)
{
   CHECK_RETOBJ(ppPoint);
   return cogoUtil::CreatePoint(m_SurfacePoint->GetPoint(), ppPoint);
}
