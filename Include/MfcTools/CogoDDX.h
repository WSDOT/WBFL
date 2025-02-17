///////////////////////////////////////////////////////////////////////
// MfcTools - Extension library for MFC
// Copyright � 1999-2025  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the Alternate Route Library Open Source License as published by 
// the Washington State Department of Transportation, Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but is distributed 
// AS IS, WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See the Alternate Route Library Open Source 
// License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License 
// along with this program; if not, write to the Washington State Department of 
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#ifndef INCLUDED_MFCTOOLS_COGODDX_H_
#define INCLUDED_MFCTOOLS_COGODDX_H_
#pragma once

#include <MfcTools\MfcToolsExp.h>
#include <Units\PhysicalT.h>

#include <Units\StationFormat.h>

#include <WBFLTools.h>
#include <WBFLGeometry.h>
#include <WBFLUnitServer.h>
#include <WBFLCogo.h>

// For AutoWBFL COGO items
void MFCTOOLSFUNC DDX_Direction(CDataExchange* pDX,int nIDC,IDirection* pDirection,IDisplayUnitFormatter* formatter);
void MFCTOOLSFUNC DDX_Angle(CDataExchange* pDX,int nIDC,IAngle* pAngle,IDisplayUnitFormatter* formatter);

void MFCTOOLSFUNC DDX_Station( CDataExchange* pDX, int nIDC, Float64& station, bool bUnitsModeSI);
void MFCTOOLSFUNC DDX_Station( CDataExchange* pDX, int nIDC, Float64& station, const WBFL::Units::StationFormat& unitStation );
void MFCTOOLSFUNC DDV_GreaterThanStation( CDataExchange* pDX, Float64 station, Float64 stationLimit, bool bUnitsModeSI);
void MFCTOOLSFUNC DDV_GreaterThanStation(CDataExchange* pDX, Float64 station, Float64 stationLimit, const WBFL::Units::StationFormat& unitStation);
void MFCTOOLSFUNC DDV_StationInRange(CDataExchange* pDX, Float64 station, Float64 minStation, Float64 maxStation, bool bUnitModeSI);
void MFCTOOLSFUNC DDV_StationInRange(CDataExchange* pDX, Float64 value, Float64 minStation, Float64 maxStation, const WBFL::Units::StationFormat& unitStation);
void MFCTOOLSFUNC DDV_Orientation(CDataExchange* pDX, std::_tstring& strOrientation);

#endif // INCLUDED_MFCTOOLS_COGODDX_H_