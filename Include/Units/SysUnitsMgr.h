///////////////////////////////////////////////////////////////////////
// Units - Unit conversion and system unit management service
// Copyright © 1999-2017  Washington State Department of Transportation
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

#ifndef INCLUDED_UNITS_SYSUNITSMGR_H_
#define INCLUDED_UNITS_SYSUNITSMGR_H_
#pragma once

#include <Units\UnitsExp.h>
#include <Units\PhysicalT.h>
#include <Units\Measure.h>
#include <list>

// PROJECT INCLUDES
//

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
class unitSysUnitsMgrListener;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   unitSysUnitsMgr

   System Units manager.


DESCRIPTION
   System Units manager.  Provides methods to access and modify the internal
   system units.

LOG
   rab : 11.03.1997 : Created file
*****************************************************************************/

class UNITSCLASS unitSysUnitsMgr
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Destructor
   ~unitSysUnitsMgr();

   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   static void BeginDamage();
   //------------------------------------------------------------------------
   static void EndDamage();
   //------------------------------------------------------------------------
   static bool IsDamaged();

   //------------------------------------------------------------------------
   static void RegisterListener(unitSysUnitsMgrListener* pListener);

   //------------------------------------------------------------------------
   static void UnregisterListener(unitSysUnitsMgrListener* pListener);

   //------------------------------------------------------------------------
   static CollectionIndexType ListenerCount();

   // GROUP: ACCESS

   //------------------------------------------------------------------------
   // Sets the system unit for mass
   static unitMass SetMassUnit(const unitMass& u);

   //------------------------------------------------------------------------
   // Returns the current system unit for mass
   static unitMass GetMassUnit();

   //------------------------------------------------------------------------
   // Sets the system unit for length
   static unitLength SetLengthUnit(const unitLength& u);

   //------------------------------------------------------------------------
   // Returns the current system unit for length
   static unitLength GetLengthUnit();

   //------------------------------------------------------------------------
   // Sets the system unit for time
   static unitTime SetTimeUnit(const unitTime& u);

   //------------------------------------------------------------------------
   // Returns the current system unit for time
   static unitTime GetTimeUnit();

   //------------------------------------------------------------------------
   // Sets the system unit for temperature
   static unitTemperature SetTemperatureUnit(const unitTemperature& u);

   //------------------------------------------------------------------------
   // Returns the current system unit for temperature
   static unitTemperature GetTemperatureUnit();

   //------------------------------------------------------------------------
   // Sets the system unit for angle
   static unitAngle SetAngleUnit(const unitAngle& u);

   //------------------------------------------------------------------------
   // Returns the current system unit for angle
   static unitAngle GetAngleUnit();

   //------------------------------------------------------------------------
   // Sets the gravitational acceleration for this unit system
   static void SetGravitationalAcceleration(Float64 gravity);

   //------------------------------------------------------------------------
   // Returns the gravitational acceleration for this unit system
   static Float64 GetGravitationalAcceleration();

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

   //------------------------------------------------------------------------
   static void NotifyAllListeners();

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   static unitMass        ms_Mass;
   static unitLength      ms_Length;
   static unitTime        ms_Time;
   static unitTemperature ms_Temperature;
   static unitAngle       ms_Angle;

   static Float64 ms_Gravity;
   static unitAcceleration ms_GravityUnit;

   static bool    ms_IsDamaged;

   typedef std::list<unitSysUnitsMgrListener*, std::allocator<unitSysUnitsMgrListener*> > Listeners;
   static  Listeners ms_Listeners;

   // GROUP: LIFECYCLE

   // Prevent construction
   unitSysUnitsMgr();

   // Prevent accidental copying and assignment
   unitSysUnitsMgr(const unitSysUnitsMgr&);
   unitSysUnitsMgr& operator=(const unitSysUnitsMgr&);

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_UNITS_SYSUNITSMGR_H_


