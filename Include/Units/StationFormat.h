///////////////////////////////////////////////////////////////////////
// Units - Unit conversion and system unit management service
// Copyright © 1999-2014  Washington State Department of Transportation
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

#ifndef INCLUDED_UNITS_STATIONFORMAT_H_
#define INCLUDED_UNITS_STATIONFORMAT_H_
#pragma once

#include <System\Exception.h>
#include <Units\UnitsExp.h>


// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   unitStationFormat

   Converts a floating point number into stationing format.


DESCRIPTION
   Converts a floating point number into stationing format.


COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 11.13.1997 : Created file
*****************************************************************************/

class UNITSCLASS unitStationFormat
{
public:
   // GROUP: ENUMERATIONS
   enum UnitOfMeasure { Meter, // Stations are in meters
                        Feet   // Stations are in feet
   };
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   unitStationFormat();

   //------------------------------------------------------------------------
   unitStationFormat(UnitOfMeasure unitOfMeasure);

   //------------------------------------------------------------------------
   // Copy constructor
   unitStationFormat(const unitStationFormat& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~unitStationFormat();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   unitStationFormat& operator = (const unitStationFormat& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Returns the station as a floating point number in system units.
   // If station is ill-formed, an unitXUnit exception will
   // be thrown.
   Float64 FromString(const std::_tstring& station) const;

   //------------------------------------------------------------------------
   // Returns a string that represents <i>station</i> in station format.
   std::_tstring AsString(Float64 station) const;

   // GROUP: ACCESS

   //------------------------------------------------------------------------
   void SetUnitOfMeasure(UnitOfMeasure unitOfMeasure);

   //------------------------------------------------------------------------
   UnitOfMeasure GetUnitOfMeasure() const;

   // GROUP: INQUIRY

   //------------------------------------------------------------------------
   // Returns <b>true</b> if the string is in a valid format, otherwise
   // <b>false</b>.  If the unit of measure is Meter, the string format is
   // x+yyy.zzzzzz (there must be at least one digit before the +, exactly
   // three digits between the + and the . and any number of digits after
   // the decimal point).  If the unit of measure is Feet, the string format
   // is x+yy.zzzz (basically the same as for Meter, except the number if
   // digits between the + and . is exactly two).  x, y, and z must be
   // digits 0-9.
   bool IsValidString(const std::_tstring& station) const;

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

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const unitStationFormat& rOther);

   //------------------------------------------------------------------------
   virtual void MakeAssignment(const unitStationFormat& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   UnitOfMeasure m_UnitOfMeasure;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};


/*****************************************************************************
CLASS 
   unitStationFormats

   Encapsulates instatiations of station formats for SI and US unit systems.


DESCRIPTION
   Encapsulates instatiations of station formats for SI and US unit systems.

COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 11.13.1997 : Created file
*****************************************************************************/

class UNITSCLASS unitStationFormats
{
public:
   // GROUP: DATA MEMBERS
   static const unitStationFormat SI;
   static const unitStationFormat US;

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Destructor
   virtual ~unitStationFormats();

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
   // GROUP: DEBUG

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
   unitStationFormats();

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_UNITS_STATIONFORMAT_H_
