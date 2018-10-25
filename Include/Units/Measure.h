///////////////////////////////////////////////////////////////////////
// Units - Unit conversion and system unit management service
// Copyright © 1999-2015  Washington State Department of Transportation
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

#ifndef INCLUDED_UNITS_MEASURE_H_
#define INCLUDED_UNITS_MEASURE_H_
#pragma once

#include <Units\PhysicalT.h>
#include <Units\UnitsExp.h>


// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   unitMeasure

   Encapsulates some specific units of measure.


DESCRIPTION
   Encapsulates the instantiation of the physical unit object.  This is a
   utility class that contains only public static constant data members.


COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 10.29.1997 : Created file
*****************************************************************************/

class UNITSCLASS unitMeasure
{
public:
   // GROUP: DATA MEMBERS
   static const unitMass Kilogram;
   static const unitMass Gram;
   static const unitMass MetricTon;
   static const unitMass Slug;
   static const unitMass PoundMass;
   static const unitMass KSlug;
   static const unitMass _12Slug;
   static const unitMass _12KSlug;

   static const unitMassPerLength KgPerMeter;
   static const unitMassPerLength LbmPerFeet;
   static const unitMassPerLength SlugPerFeet;
   static const unitMassPerLength LbfPerFeet;  // This is a minor hack to make the
                                               // use of mass in SI mode the same
                                               // as force in US mode

   static const unitLength Meter;
   static const unitLength Millimeter;
   static const unitLength Centimeter;
   static const unitLength Kilometer;
   static const unitLength Feet;
   static const unitLength USSurveyFoot;
   static const unitLength Inch;
   static const unitLength Mile;
   static const unitLength Yard;
   static const unitLength USSurveyYard;

   static const unitLength2 Meter2;
   static const unitLength2 Millimeter2;
   static const unitLength2 Centimeter2;
   static const unitLength2 Kilometer2;
   static const unitLength2 Feet2;
   static const unitLength2 Inch2;
   static const unitLength2 Mile2;
   static const unitLength2 Yard2;

   static const unitLength3 Meter3;
   static const unitLength3 Millimeter3;
   static const unitLength3 Centimeter3;
   static const unitLength3 Kilometer3;
   static const unitLength3 Feet3;
   static const unitLength3 Inch3;
   static const unitLength3 Mile3;
   static const unitLength3 Yard3;

   static const unitLength4 Meter4;
   static const unitLength4 Millimeter4;
   static const unitLength4 Centimeter4;
   static const unitLength4 Kilometer4;
   static const unitLength4 Feet4;
   static const unitLength4 Inch4;
   static const unitLength4 Mile4;
   static const unitLength4 Yard4;

   static const unitAreaPerLength Meter2PerMeter;
   static const unitAreaPerLength Millimeter2PerMillimeter;
   static const unitAreaPerLength Millimeter2PerMeter;
   static const unitAreaPerLength Feet2PerFoot;
   static const unitAreaPerLength Inch2PerInch;
   static const unitAreaPerLength Inch2PerFoot;

   static const unitPerLength PerMeter;
   static const unitPerLength PerMillimeter;
   static const unitPerLength PerInch;
   static const unitPerLength PerFeet;

   static const unitTime Second;
   static const unitTime Minute;
   static const unitTime Hour;
   static const unitTime Day;

   static const unitTemperature Celcius;
   static const unitTemperature Fahrenheit;

   static const unitAngle Radian;
   static const unitAngle Degree;

   static const unitPressure Pa;
   static const unitPressure kPa;
   static const unitPressure MPa;
   static const unitPressure PSI;
   static const unitPressure PSF;
   static const unitPressure KSI;
   static const unitPressure KSF;

   static const unitUnitWeight NewtonPerMeter3;
   static const unitUnitWeight PCI;
   static const unitUnitWeight PCF;

   static const unitDensity KgPerMeter3;
   static const unitDensity LbmPerFeet3;
   static const unitDensity SlugPerFeet3;
   static const unitDensity LbfPerFeet3;
   static const unitDensity KipPerFeet3;

   static const unitForce Newton;
   static const unitForce Kilonewton;
   static const unitForce Pound;
   static const unitForce Kip;
   static const unitForce Ton;

   static const unitForcePerLength NewtonPerMeter;
   static const unitForcePerLength KilonewtonPerMeter;
   static const unitForcePerLength NewtonPerMillimeter;
   static const unitForcePerLength LbfPerFoot;
   static const unitForcePerLength LbfPerInch;
   static const unitForcePerLength KipPerFoot;
   static const unitForcePerLength KipPerInch;

   static const unitMoment NewtonMeter;
   static const unitMoment KilonewtonMeter;
   static const unitMoment NewtonMillimeter;
   static const unitMoment InchLbf;
   static const unitMoment KipFeet;
   static const unitMoment KipInch;

   static const unitMomentPerAngle NewtonMeterPerRadian;
   static const unitMomentPerAngle KiloNewtonMeterPerRadian;
   static const unitMomentPerAngle KipInchPerRadian;
   static const unitMomentPerAngle KipFeetPerRadian;

   static const unitSqrtPressure SqrtPa;
   static const unitSqrtPressure SqrtMPa;
   static const unitSqrtPressure SqrtKSI;

   static const unitAcceleration MeterPerSec2;
   static const unitAcceleration FeetPerSec2;

   static const unitForceLength2 KipInch2;
   static const unitForceLength2 KipFoot2;
   static const unitForceLength2 LbfInch2;
   static const unitForceLength2 LbfFoot2;
   static const unitForceLength2 NewtonMeter2;
   static const unitForceLength2 NewtonMillimeter2;
   static const unitForceLength2 KilonewtonMeter2;


   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
   // GROUP: DEBUG
#if defined _UNITTEST
   //------------------------------------------------------------------------
   // Self-diagnostic test function.  Returns <b>true</b> if the test passes,
   // otherwise return <b>false</b>.
   static bool TestMe(dbgLog& rlog);
#endif // _UNITTEST

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE

   unitMeasure();
   unitMeasure& operator=(const unitMeasure&);

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_UNITS_MEASURE_H_

