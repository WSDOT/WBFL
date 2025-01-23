///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
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

// Station.cpp : Implementation of CStation
#include "stdafx.h"
#include "WBFLCOGO.h"
#include "Station.h"
#include <stdio.h>
#include <WBFLCogo\CogoHelpers.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define E_BADSTATIONSTRING CComCoClass<CStation,&CLSID_Station>::Error(IDS_E_BADSTATIONSTRING,IID_IStation,COGO_E_BADSTATIONSTRING)

/////////////////////////////////////////////////////////////////////////////
// CStation

STDMETHODIMP CStation::InterfaceSupportsErrorInfo(REFIID riid)
{
   static const IID* arr[] = 
   {
      &IID_IStation,
   };
   for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
   {
      if (InlineIsEqualGUID(*arr[i],riid))
         return S_OK;
   }
   return S_FALSE;
}

STDMETHODIMP CStation::get_StationZoneIndex(ZoneIndexType *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Station.GetStationZoneIndex();
   return S_OK;
}

STDMETHODIMP CStation::put_StationZoneIndex(ZoneIndexType newVal)
{
   m_Station.SetStationZoneIndex(newVal);
   return S_OK;
}

STDMETHODIMP CStation::get_Value(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Station.GetValue();
	return S_OK;
}

STDMETHODIMP CStation::put_Value(Float64 newVal)
{
   m_Station.SetValue(newVal);
	return S_OK;
}

STDMETHODIMP CStation::Offset(Float64 offset)
{
   m_Station.Offset(offset);
   return S_OK;
}

STDMETHODIMP CStation::GetStation(ZoneIndexType* pZoneIdx,Float64* pStation)
{
   CHECK_RETVAL(pZoneIdx);
   CHECK_RETVAL(pStation);
   std::tie(*pStation,*pZoneIdx) = m_Station.GetStation();
   return S_OK;
}

STDMETHODIMP CStation::SetStation(ZoneIndexType zoneIdx,Float64 station)
{
   m_Station.SetStation(zoneIdx, station);
   return S_OK;
}

STDMETHODIMP CStation::FromVariant(VARIANT varStation)
{
   auto [hr, station] = cogoUtil::StationFromVariant(varStation);
   if (FAILED(hr)) return hr;

   m_Station = station;
   return S_OK;
}

STDMETHODIMP CStation::FromString(BSTR station, UnitModeType unitMode)
{
   USES_CONVERSION;
   std::_tstring strStation(OLE2T(station));

   try
   {
      m_Station.FromString(strStation, unitMode == umUS ? WBFL::Units::StationFormats::US : WBFL::Units::StationFormats::SI);
   }
   catch(...)
   {
      return E_INVALIDARG;
   }

   return S_OK;
}

STDMETHODIMP CStation::AsString(UnitModeType unitMode,VARIANT_BOOL vbIncludeStationZone, BSTR *station)
{
   USES_CONVERSION;
   auto strStation = m_Station.AsString(unitMode == umUS ? WBFL::Units::StationFormats::US : WBFL::Units::StationFormats::SI, vbIncludeStationZone == VARIANT_TRUE);
   *station = CComBSTR(strStation.c_str());
   return S_OK;
}

STDMETHODIMP CStation::Clone(IStation* *clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CStation>* pClone;
   CComObject<CStation>::CreateInstance(&pClone);

   (*clone) = pClone;
   (*clone)->AddRef();

   (*clone)->SetStation(m_Station.GetStationZoneIndex(),m_Station.GetValue());

   return S_OK;
}
