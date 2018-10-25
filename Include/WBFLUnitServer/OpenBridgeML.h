///////////////////////////////////////////////////////////////////////
// UnitServer - Unit Conversion and Display Unit Management Library
// Copyright © 1999-2016  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Open Source License as 
// published by the Washington State Department of Transportation, 
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but 
// distribution is AS IS, WITHOUT ANY WARRANTY; without even the implied 
// warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See 
// the Alternate Route Open Source License for more details.
//
// You should have received a copy of the Alternate Route Open Source 
// License along with this program; if not, write to the Washington 
// State Department of Transportation, Bridge and Structures Office, 
// P.O. Box  47340, Olympia, WA 98503, USA or e-mail 
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#pragma once

#include <WBFLUnitServer\UnitServerExp.h>
#include <OpenBridgeML_Units.hxx>
#include <WBFLUnitServer.h>

// Initializes a WBFLUnitServer with OpenBridgeML Units declaration
BOOL UNITSERVERFUNC InitializeWBFLUnitServer(OpenBridgeML::Units::UnitsDeclarationType* pDeclaration,IUnitServer* pUnitServer);

#define DECLARE_BASE_UNIT_CONVERTER(V) void UNITSERVERFUNC ConvertBetweenBaseUnits(OpenBridgeML::Units::##V& unitValueType,IUnitServer* pFromUnitServer,IUnitServer* pToUnitServer)
DECLARE_BASE_UNIT_CONVERTER(MassValueType);
DECLARE_BASE_UNIT_CONVERTER(LengthValueType);
DECLARE_BASE_UNIT_CONVERTER(TimeValueType);
DECLARE_BASE_UNIT_CONVERTER(TemperatureValueType);
DECLARE_BASE_UNIT_CONVERTER(AngleValueType);
DECLARE_BASE_UNIT_CONVERTER(MassPerLengthValueType);
DECLARE_BASE_UNIT_CONVERTER(Length2ValueType);
DECLARE_BASE_UNIT_CONVERTER(Length3ValueType);
DECLARE_BASE_UNIT_CONVERTER(Length4ValueType);
DECLARE_BASE_UNIT_CONVERTER(PressureValueType);
DECLARE_BASE_UNIT_CONVERTER(UnitWeightValueType);
DECLARE_BASE_UNIT_CONVERTER(DensityValueType);
DECLARE_BASE_UNIT_CONVERTER(ForceValueType);
DECLARE_BASE_UNIT_CONVERTER(ForcePerLengthValueType);
DECLARE_BASE_UNIT_CONVERTER(MomentValueType);
DECLARE_BASE_UNIT_CONVERTER(ThermalExpansionValueType);
