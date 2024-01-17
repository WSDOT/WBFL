///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
// Copyright © 1999-2024  Washington State Department of Transportation
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

// Station.h : Declaration of the CStation

#ifndef __STATION_H_
#define __STATION_H_
#pragma once

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CStation
class ATL_NO_VTABLE CStation : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CStation, &CLSID_Station>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CStation,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IStation
{
public:
	CStation()
	{
	}

   void SetStation(const WBFL::COGO::Station& station) { m_Station = station; }
   WBFL::COGO::Station& GetStation() { return m_Station; }

DECLARE_REGISTRY_RESOURCEID(IDR_STATION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CStation)
	COM_INTERFACE_ENTRY(IStation)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IStation
public:
   STDMETHOD(Clone)(/*[out,retval]*/ IStation* *clone) override;
	STDMETHOD(AsString)(/*[in]*/ UnitModeType unitMode,/*[in]*/ VARIANT_BOOL vbIncludeStationZone, /*[out,retval]*/ BSTR* station) override;
	STDMETHOD(FromString)(/*[in]*/ BSTR station,/*[in]*/ UnitModeType unitMode) override;
	STDMETHOD(get_Value)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Value)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(Offset)(/*[in]*/Float64 offset) override;
   STDMETHOD(GetStation)(ZoneIndexType* pZoneIdx,Float64* pStation) override;
   STDMETHOD(SetStation)(ZoneIndexType zoneIdx,Float64 station) override;
   STDMETHOD(FromVariant)(/*[in]*/ VARIANT varStation) override;
   STDMETHOD(get_StationZoneIndex)(ZoneIndexType *pVal) override;
	STDMETHOD(put_StationZoneIndex)(ZoneIndexType newVal) override;

private:
   WBFL::COGO::Station m_Station;
};

#endif //__STATION_H_
