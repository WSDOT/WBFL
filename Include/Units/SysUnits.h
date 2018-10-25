///////////////////////////////////////////////////////////////////////
// Units - Unit conversion and system unit management service
// Copyright (C) 1999  Washington State Department of Transportation
//                     Bridge and Structures Office
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

#ifndef INCLUDED_UNITS_SYSUNITS_H_
#define INCLUDED_UNITS_SYSUNITS_H_
#pragma once

#include <Units\UnitsExp.h>
#include <Units\Convert.h>
#include <Units\SysUnitsMgr.h>

// PROJECT INCLUDES
//

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

void UNITSFUNC convert_from( Float64* pValue, Float64 preTerm, Float64 cf, Float64 postTerm, Float64 dim );
void UNITSFUNC convert_to( Float64* pValue, Float64 preTerm, Float64 cf, Float64 postTerm, Float64 dim );

// INLINE METHODS
//

template <class T>
Float64 ConvertFromSysUnits( Float64 value, const T& to )
{
   const unitMass& um = unitSysUnitsMgr::GetMassUnit();
   convert_from( &value,
                 um.GetPreTerm(),
                 um.GetConvFactor(),
                 um.GetPostTerm(),
                 T::MassDim() );

   const unitLength& ul = unitSysUnitsMgr::GetLengthUnit();
   convert_from( &value,
                 ul.GetPreTerm(),
                 ul.GetConvFactor(),
                 ul.GetPostTerm(),
                 T::LengthDim() );

   const unitTime& ut = unitSysUnitsMgr::GetTimeUnit();
   convert_from( &value,
                 ut.GetPreTerm(),
                 ut.GetConvFactor(),
                 ut.GetPostTerm(),
                 T::TimeDim() );

   const unitTemperature& uk = unitSysUnitsMgr::GetTemperatureUnit();
   convert_from( &value,
                 uk.GetPreTerm(),
                 uk.GetConvFactor(),
                 uk.GetPostTerm(),
                 T::TemperatureDim() );

   const unitAngle& ua = unitSysUnitsMgr::GetAngleUnit();
   convert_from( &value,
                 ua.GetPreTerm(),
                 ua.GetConvFactor(),
                 ua.GetPostTerm(),
                 T::AngleDim() );

   T from(0,1,0,""); // A dummy conversion factor

   return Convert( value, from, to );
}

template <class T>
Float64 ConvertToSysUnits(Float64 value,const T& from)
{
   const unitMass& um = unitSysUnitsMgr::GetMassUnit();
   convert_to( &value,
               um.GetPreTerm(),
               um.GetConvFactor(),
               um.GetPostTerm(),
               T::MassDim() );

   const unitLength& ul = unitSysUnitsMgr::GetLengthUnit();
   convert_to( &value,
               ul.GetPreTerm(),
               ul.GetConvFactor(),
               ul.GetPostTerm(),
               T::LengthDim() );

   const unitTime& ut = unitSysUnitsMgr::GetTimeUnit();
   convert_to( &value,
               ut.GetPreTerm(),
               ut.GetConvFactor(),
               ut.GetPostTerm(),
               T::TimeDim() );

   const unitTemperature& uk = unitSysUnitsMgr::GetTemperatureUnit();
   convert_to( &value,
               uk.GetPreTerm(),
               uk.GetConvFactor(),
               uk.GetPostTerm(),
               T::TemperatureDim() );

   const unitAngle& ua = unitSysUnitsMgr::GetAngleUnit();
   convert_to( &value,
               ua.GetPreTerm(),
               ua.GetConvFactor(),
               ua.GetPostTerm(),
               T::AngleDim() );

   T to(0,1,0,"");

   return Convert( value, from, to );
}

// EXTERNAL REFERENCES
//

#endif // INCLUDED_UNITS_SYSUNITS_H_

