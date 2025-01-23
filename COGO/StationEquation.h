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

// StationEquation.h : Declaration of the CStationEquation

#ifndef __StationEquation_H_
#define __StationEquation_H_
#pragma once

#include "resource.h"       // main symbols
//#include "StationEquationCollection.h"

/////////////////////////////////////////////////////////////////////////////
// CStationEquation
class ATL_NO_VTABLE CStationEquation : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CStationEquation, &CLSID_StationEquation>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CStationEquation,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IStationEquation
{
public:
	CStationEquation()
	{
	}

   void SetEquation(const WBFL::COGO::StationEquation& equation) { m_Equation = equation; }

DECLARE_REGISTRY_RESOURCEID(IDR_STATIONEQUATION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CStationEquation)
	COM_INTERFACE_ENTRY(IStationEquation)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IStationEquation
public:
   STDMETHOD(GetEquation)(Float64* pBackStation,Float64* pAheadStation) override;
   STDMETHOD(get_Back)(Float64* pBack) override;
   STDMETHOD(get_Ahead)(Float64* pAhead) override;
   STDMETHOD(get_NormalizedValue)(Float64* pNormalizedValue) override;

private:
   WBFL::COGO::StationEquation m_Equation;
};

#endif //__StationEquation_H_
