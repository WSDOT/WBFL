///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2023  Washington State Department of Transportation
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

#pragma once
#include <EAF\EAFTypes.h>
#include <WbflTypes.h>
#include <Units\Units.h>

/*****************************************************************************
INTERFACE
   IEAFDisplayUnits

   Interface for getting the display units.

DESCRIPTION
   Interface for getting the display units.
*****************************************************************************/
// {8438FE92-68ED-11d2-883C-006097C68A9C}
DEFINE_GUID(IID_IEAFDisplayUnits, 
0x8438fe92, 0x68ed, 0x11d2, 0x88, 0x3c, 0x0, 0x60, 0x97, 0xc6, 0x8a, 0x9c);
interface IEAFDisplayUnits : IUnknown
{
   virtual void                             SetUnitMode(eafTypes::UnitMode unitMode) = 0;
	virtual eafTypes::UnitMode               GetUnitMode() = 0;
	virtual const WBFL::Units::StationFormat& GetStationFormat() = 0;
   virtual const WBFL::Units::ScalarData&         GetScalarFormat() = 0;
   virtual const WBFL::Units::ScalarData&         GetPercentageFormat() = 0;
   virtual const WBFL::Units::LengthData&         GetComponentDimUnit() = 0;
   virtual const WBFL::Units::LengthData&         GetXSectionDimUnit() = 0;
   virtual const WBFL::Units::LengthData&         GetSpanLengthUnit() = 0;
   virtual const WBFL::Units::LengthData&         GetDeflectionUnit() = 0;
   virtual const WBFL::Units::LengthData&         GetAlignmentLengthUnit() = 0;
   virtual const WBFL::Units::Length2Data&        GetAreaUnit() = 0;
   virtual const WBFL::Units::Length4Data&        GetMomentOfInertiaUnit() = 0;
   virtual const WBFL::Units::Length3Data&        GetSectModulusUnit() = 0;
   virtual const WBFL::Units::PressureData&       GetStressUnit() = 0;
   virtual const WBFL::Units::PressureData&       GetModEUnit() = 0;
   virtual const WBFL::Units::ForceData&          GetGeneralForceUnit() = 0;
   virtual const WBFL::Units::ForceData&          GetTonnageUnit() = 0;
   virtual const WBFL::Units::ForceData&          GetShearUnit() = 0;
   virtual const WBFL::Units::MomentData&         GetMomentUnit() = 0;
   virtual const WBFL::Units::MomentData&         GetSmallMomentUnit() = 0;
   virtual const WBFL::Units::AngleData&          GetAngleUnit() = 0;
   virtual const WBFL::Units::AngleData&          GetRadAngleUnit() = 0;  // Radians always
   virtual const WBFL::Units::DensityData&        GetDensityUnit() = 0;
   virtual const WBFL::Units::MassPerLengthData&  GetMassPerLengthUnit() = 0;
   virtual const WBFL::Units::ForcePerLengthData& GetForcePerLengthUnit() = 0;
   virtual const WBFL::Units::MomentPerAngleData& GetMomentPerAngleUnit() = 0;
   virtual const WBFL::Units::TimeData&           GetShortTimeUnit() = 0;
   virtual const WBFL::Units::TimeData&           GetWholeDaysUnit() = 0;
   virtual const WBFL::Units::TimeData&           GetFractionalDaysUnit() = 0;
   virtual const WBFL::Units::AreaPerLengthData&  GetAvOverSUnit() = 0;
   virtual const WBFL::Units::ForceLength2Data&   GetStiffnessUnit() = 0;
   virtual const WBFL::Units::SqrtPressureData&   GetTensionCoefficientUnit() = 0;
   virtual const WBFL::Units::PerLengthData&      GetPerLengthUnit() = 0;
   virtual const WBFL::Units::PerLengthData&      GetCurvatureUnit() = 0;
   virtual const WBFL::Units::PressureData&       GetSidewalkPressureUnit() = 0;
   virtual const WBFL::Units::PressureData&       GetOverlayWeightUnit() = 0;
   virtual const WBFL::Units::PressureData&       GetWindPressureUnit() = 0;
   virtual const WBFL::Units::VelocityData&       GetVelocityUnit() = 0;
};

/*****************************************************************************
INTERFACE
   IEAFDisplayUnitsEventSink

   Callback interface for display units.

DESCRIPTION
   Callback interface for display units.
*****************************************************************************/
// {015A4130-272C-11d2-8EB0-006097DF3C68}
DEFINE_GUID(IID_IEAFDisplayUnitsEventSink,
0x015A4130, 0x272C, 0x11d2, 0x8E, 0xB0, 0x00, 0x60, 0x97, 0xDF, 0x3C, 0x68);
interface IEAFDisplayUnitsEventSink : IUnknown
{
   virtual HRESULT OnUnitsChanging() = 0;
   virtual HRESULT OnUnitsChanged(eafTypes::UnitMode newUnitsMode) = 0;
};

#define IS_US_UNITS(p) (p->GetUnitMode() == eafTypes::umUS ? true : false)
#define IS_SI_UNITS(p) !IS_US_UNITS(p)
