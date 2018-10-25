///////////////////////////////////////////////////////////////////////
// Units - Unit conversion and system unit management service
// Copyright © 1999-2016  Washington State Department of Transportation
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

#ifndef INCLUDED_UNITS_AUTOSYSUNITS_H_
#define INCLUDED_UNITS_AUTOSYSUNITS_H_
#pragma once

#include <Units\UnitsExp.h>
#include <Units\SysUnitsMgr.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   unitAutoSysUnits

   Automatic object used to reset system units.


DESCRIPTION
   Automatic object used to reset system units.


COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 12.03.1997 : Created file
*****************************************************************************/

class UNITSCLASS unitAutoSysUnits
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor.
   // Resets system units to the current values.
   unitAutoSysUnits();

   //------------------------------------------------------------------------
   unitAutoSysUnits(const unitMass& um,
                    const unitLength& ul,
                    const unitTime& ut,
                    const unitTemperature& uk,
                    const unitAngle& ua);

   //------------------------------------------------------------------------
   // Copy constructor
   unitAutoSysUnits(const unitAutoSysUnits& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~unitAutoSysUnits();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   unitAutoSysUnits& operator = (const unitAutoSysUnits& rOther);

   // GROUP: OPERATIONS
   // GROUP: ACCESS

   //------------------------------------------------------------------------
   // Sets the unit of measure for mass that the system units will be set to
   // when this object is destroyed.
   void SetMassUnit(const unitMass& u);

   //------------------------------------------------------------------------
   // Sets the unit of measure for length that the system units will be set to
   // when this object is destroyed.
   void SetLengthUnit(const unitLength& u);

   //------------------------------------------------------------------------
   // Sets the unit of measure for time that the system units will be set to
   // when this object is destroyed.
   void SetTimeUnit(const unitTime& u);

   //------------------------------------------------------------------------
   // Sets the unit of measure for temperature that the system units will be set to
   // when this object is destroyed.
   void SetTemperatureUnit(const unitTemperature& u);

   //------------------------------------------------------------------------
   // Sets the unit of measure for angle that the system units will be set to
   // when this object is destroyed.
   void SetAngleUnit(const unitAngle& u);

   // GROUP: INQUIRY
   // GROUP: DEBUG
#if defined _DEBUG
   //------------------------------------------------------------------------
   // Returns <b>true</b> if the class is in a valid state, otherwise returns
   // <b>false</b>.
   virtual bool AssertValid() const;

   //------------------------------------------------------------------------
   // Dumps the contents of the class to the given stream.
   virtual void Dump(dbgDumpContext& os) const;
#endif // _DEBUG

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
   void MakeCopy(const unitAutoSysUnits& rOther);

   //------------------------------------------------------------------------
   virtual void MakeAssignment(const unitAutoSysUnits& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   unitMass        m_Mass;
   unitLength      m_Length;
   unitTime        m_Time;
   unitTemperature m_Temperature;
   unitAngle       m_Angle;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_UNITS_AUTOSYSUNITS_H_
