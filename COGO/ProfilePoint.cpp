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

// ProfilePoint.cpp : Implementation of CProfilePoint
#include "stdafx.h"
#include "WBFLCOGO.h"
#include "ProfilePoint.h"
#include <WBFLCogo\CogoHelpers.h>
#include "Station.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProfilePoint
HRESULT CProfilePoint::FinalConstruct()
{
   return S_OK;
}

STDMETHODIMP CProfilePoint::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IProfilePoint,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CProfilePoint::get_Station(IStation* *station)
{
   CHECK_RETOBJ(station);
   return cogoUtil::CreateStation(m_ProfilePoint->GetStation(), station);
}

STDMETHODIMP CProfilePoint::put_Station(VARIANT varStation)
{
   auto [hr, station] = cogoUtil::StationFromVariant(varStation);
   if (FAILED(hr)) return hr;

   m_ProfilePoint->SetStation(station);
	return S_OK;
}

STDMETHODIMP CProfilePoint::get_Elevation(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_ProfilePoint->GetElevation();
	return S_OK;
}

STDMETHODIMP CProfilePoint::put_Elevation(Float64 newVal)
{
   m_ProfilePoint->SetElevation(newVal);
	return S_OK;
}

STDMETHODIMP CProfilePoint::Location(IStation** pStation, Float64* pElevation)
{
   CHECK_RETOBJ(pStation);
   CHECK_RETVAL(pElevation);
   WBFL::COGO::Station station;
   std::tie(station,*pElevation) = m_ProfilePoint->GetLocation();
   return cogoUtil::CreateStation(station, pStation);
}

STDMETHODIMP CProfilePoint::Move(VARIANT varStation, Float64 elevation)
{
   auto [hr, station] = cogoUtil::StationFromVariant(varStation);
   if (FAILED(hr)) return hr;

   m_ProfilePoint->Move(station, elevation);
   return S_OK;
}

STDMETHODIMP CProfilePoint::Clone(IProfilePoint** ppClone)
{
   CHECK_RETOBJ(ppClone);
   auto clone = std::make_shared<WBFL::COGO::ProfilePoint>(*m_ProfilePoint);
   return cogoUtil::CreateProfilePoint(clone, ppClone);
}
