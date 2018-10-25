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

#ifndef INCLUDED_COGO_COGOUTIL_H_
#define INCLUDED_COGO_COGOUTIL_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <Cogo\CogoExp.h>
#include <Cogo\CogoDirection.h>
#include <Cogo\CogoAngle.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//
#define COGO_SI_STATION 3,3
#define COGO_US_STATION 2,2

/*****************************************************************************
CLASS 
   cogoUtil

   Utility class for cogo related operations.


DESCRIPTION
   Utility class for cogo related operations.  This classes handles things like
   converting to and from DMS format and stationing format.

COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 06.19.1997 : Created file
*****************************************************************************/

class COGOCLASS cogoUtil
{
public:
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Converts an angle given in radians to deg-min-sec format
   static void ToDMS(Float64 value,Int16* deg,Uint16* min,Float64* sec);

   //------------------------------------------------------------------------
   // Converts an angle given in deg-min-sec format to an angle in radians
   static Float64 FromDMS(Int16 deg,Uint16 min = 0,Float64 sec = 0.0);

   //------------------------------------------------------------------------
   // Converts a floating point number to a station string.  station must
   // be a positive number.  Unit conversions are not performed on station.
   // nDigOffset is the number of digits between the + sign and the decimal 
   // place. nDec is the number of digits after the decimal place. The macros 
   // COGO_US_STATION and COGO_SI_STATION can be used in place of the second 
   // and third parameters.
   //
   // Example
   // retval = cogoUtil::StationToString( station, COGO_US_STATION, buffer, sizeof(buffer) );
   //
   // The resulting string is stored in str.  cch is the size of str.
   //
   // Returns zero on success, required size of str if it is too small, or -1 on
   // an other error.
   static Int16 StationToString(Float64 station,Uint16 nDigOffset,Uint16 nDec,char* str,Uint16 cch);

   //------------------------------------------------------------------------
   // Converts a station string to a floating point number.  nDigOffset is the 
   // number of digits between the + sign and the decimal place. nDec is the 
   // number of digits after the decimal place.  The macros COGO_US_STATION and
   // COGO_SI_STATION can be used in place of the second and third parameters.
   //
   // Returns false if the station string was not correctly formed.
   //
   // Unit conversions are not performed on the resulting station.
   static bool StringToStation(const char* str,Uint16 nDigOffset,Uint16 nDec,Float64* pStation);

   // GROUP: ACCESS
   // GROUP: INQUIRY

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

   //------------------------------------------------------------------------
   cogoUtil();
   cogoUtil(const cogoUtil& rOther);
   cogoUtil& operator = (const cogoUtil& rOther);

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
#if defined _UNITTEST
public:
   static bool TestMe(dbgLog& rlog);
#endif // _UNITTEST
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_COGO_COGOUTIL_H_

