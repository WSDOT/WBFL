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

#ifndef INCLUDED_COGO_COGOANGLE_H_
#define INCLUDED_COGO_COGOANGLE_H_
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

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   cogoAngle

   This class encapsulates an angle.


DESCRIPTION
   This class encapsulates an angle.  Angles are used to describe the angle
   between two lines.


   EXAMPLE
      Place examples here.
   END

BUGS
   There are currently no known problems with this class.

COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 06.29.1997 : Created file
*****************************************************************************/

class COGOCLASS cogoAngle
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   cogoAngle(Float64 angle = 0.);

   //------------------------------------------------------------------------
   cogoAngle(Int16 deg,Uint16 min,Float64 sec);

   //------------------------------------------------------------------------
   cogoAngle(Uint16 deg, Uint16 min,Float64 sec,Int8 dir);

   //------------------------------------------------------------------------
   // Copy constructor
   cogoAngle(const cogoAngle& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~cogoAngle();

   // GROUP: OPERATORS

   //------------------------------------------------------------------------
   // Assignment operator
   // Returns reference to itself
   cogoAngle& operator = (const cogoAngle& rOther);
   cogoAngle& operator = (Float64 angle);

   cogoAngle operator+(const cogoAngle& rOther) const;
   cogoAngle operator-(const cogoAngle& rOther) const;
   cogoAngle operator*(Float64 scalar) const;
   cogoAngle operator/(Float64 scalar) const;

   cogoAngle& operator+=(const cogoAngle& rOther);
   cogoAngle& operator-=(const cogoAngle& rOther);
   cogoAngle& operator*=(Float64 scalar);
   cogoAngle& operator/=(Float64 scalar);

   cogoAngle operator-() const;


   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Normalizes angle to the range [0, 2*PI).
   void Normalize();

   // GROUP: ACCESS

   //------------------------------------------------------------------------
   void SetAngle(Float64 angle);

   //------------------------------------------------------------------------
   void SetAngle(Int16 deg,Uint16 min,Float64 sec);

   //------------------------------------------------------------------------
   Float64 AsFloat64() const;

   //------------------------------------------------------------------------
   // Returns a string representation of the angle (DMS format).  If
   // <i>bSigned</i> is <b>true</b> the angle is signed,  otherwise it
   // is written with a Left/Right direction specifier.  If bFull is
   // true, the full DMS format is written, if false, only the degree
   // is written if minutes and seconds are zero.
   // If bSymbols is true, the degree, minute, and second symbols are
   // included in the string.
   std::string AsString(bool bSigned,bool bFull = true,bool bSymbols = false) const;

   //------------------------------------------------------------------------
   // Converts a string in the format [+|-]ddd [[mm] [ss.s]] or dd [[mm] [ss.s]] {L|R}
   // to a cogoAngle.  Returns true if successfule,  otherwise false.
   static bool AngleFromString(const char* str,cogoAngle* pCogoAngle);

   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   void MakeCopy(const cogoAngle& rOther);
   void MakeAssignment(const cogoAngle& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   Float64 m_Angle;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
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

bool COGOFUNC operator == (const cogoAngle& a,const cogoAngle& b);
bool COGOFUNC operator != (const cogoAngle& a,const cogoAngle& b);
bool COGOFUNC operator  > (const cogoAngle& a,const cogoAngle& b);
bool COGOFUNC operator  < (const cogoAngle& a,const cogoAngle& b);
bool COGOFUNC operator >= (const cogoAngle& a,const cogoAngle& b);
bool COGOFUNC operator <= (const cogoAngle& a,const cogoAngle& b);

#endif // INCLUDED_COGO_COGOANGLE_H_

