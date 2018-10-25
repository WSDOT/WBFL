///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
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
// Transportation, Bridge and Structures Office, 4500 3rd Ave SE - P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#ifndef INCLUDED_COGO_COGODIRECTION_H_
#define INCLUDED_COGO_COGODIRECTION_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <Cogo\CogoExp.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
class cogoAngle;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   cogoDirection

   Defines the direction of a directed line.


DESCRIPTION
   Defines the direction of a directed line.  A directed line is described by
   a point which the line passes through and the azimuth or bearing of the line.

BUGS
   There are currently no known problems with this class.

COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 06.19.1997 : Created file
*****************************************************************************/

class COGOCLASS cogoDirection
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   cogoDirection();

   //------------------------------------------------------------------------
   // Direction defined as bearing
   cogoDirection(Int8 n,Uint16 deg,Uint16 min,Float64 sec,Int8 e);

   //------------------------------------------------------------------------
   // Direction defined as azimuth
   cogoDirection(Int16 deg,Uint16 min,Float64 sec);

   //------------------------------------------------------------------------
   // Direction defined as azimuth
   cogoDirection(const cogoAngle& rAzimuth);

   //------------------------------------------------------------------------
   cogoDirection(Float64 direction);

   //------------------------------------------------------------------------
   // Copy constructor
   cogoDirection(const cogoDirection& rOther);

   //------------------------------------------------------------------------
   // Destructor
   ~cogoDirection();

   // GROUP: OPERATORS

   //------------------------------------------------------------------------
   // Assignment operator
   //
   // Returns reference to itself
   cogoDirection& operator = (const cogoDirection& rOther);

   //------------------------------------------------------------------------
   cogoDirection& operator = (Float64 direction);

   //------------------------------------------------------------------------
   bool operator == (const cogoDirection& rOther) const;

   //------------------------------------------------------------------------
   bool operator != (const cogoDirection& rOther) const;

   //------------------------------------------------------------------------
   bool operator < (const cogoDirection& rOther) const;

   //------------------------------------------------------------------------
   cogoDirection& operator+=(const cogoAngle& angle);

   //------------------------------------------------------------------------
   cogoDirection& operator-=(const cogoAngle& angle);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   cogoDirection& Increment(const cogoAngle& angle);

   //------------------------------------------------------------------------
   cogoDirection IncrementBy(const cogoAngle& angle) const;

   //------------------------------------------------------------------------
   // Converts a bearing to an angle measured clockwise from due north in
   // radians.
   static Float64 BearingToDBearing(Int8 n,Uint16 deg,Uint16 min,Float64 sec,Int8 e);

   //------------------------------------------------------------------------
   // Converts an angle measured clockwise from due north in radians to a
   // bearing.
   static void DBearingToBearing(Float64 dir,Int8& n,Uint16& deg,Uint16& min,Float64& sec,Int8& e);

   //------------------------------------------------------------------------
   static bool BearingFromString(const char* str,cogoDirection* pDir);

   //------------------------------------------------------------------------
   // Converts an azimuth to an angle measured clockwise from due north in
   // radians
   static Float64 AzimuthToDAzimuth(Int16 deg,Uint16 min,Float64 sec);

   //------------------------------------------------------------------------
   // Converts an angle measued clockwise from due north in radians to an
   // azimuth in deg-min-sec format.
   static void DAzimuthToAzimuth(Float64 angel,Int16& deg,Uint16& min,Float64& sec);

   // GROUP: ACCESS

   //------------------------------------------------------------------------
   // Returns the direction as a floating point value.  The direction is an
   // angle measured clockwise from due north, in radians.
   Float64 AsFloat64() const;

   //------------------------------------------------------------------------
   std::string AsBearingString(bool bFull = true,bool bSymbols = false) const;

   //------------------------------------------------------------------------
   std::string AsAzimuthString(bool bSymbols = false) const;

   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   void MakeCopy(const cogoDirection& rOther);
   void MakeAssignment(const cogoDirection& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   Float64 m_Direction; // Direction of line. Measured zero radians due north 
                       // and increasing in a CW direction.

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   void Normalize();

   //------------------------------------------------------------------------
   void AsDmsString(std::string& str,bool bSymbols = false) const;

   // GROUP: ACCESS
   // GROUP: INQUIRY
#if defined _DEBUG
public:
   bool AssertValid() const;
   void Dump(dbgDumpContext& os) const;
#endif // _DEBUG

#if defined _UNITTEST
public:
   static bool TestMe(dbgLog& rlog);
#endif // _UNITTEST
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

//------------------------------------------------------------------------
const cogoDirection COGOFUNC operator+(const cogoDirection& dir,const cogoAngle& angle);

//------------------------------------------------------------------------
const cogoDirection COGOFUNC operator-(const cogoDirection& dir,const cogoAngle& angle);

//------------------------------------------------------------------------
const cogoAngle COGOFUNC operator-(const cogoDirection& dir1,const cogoDirection& dir2);


#endif // INCLUDED_COGO_COGODIRECTION_H_

