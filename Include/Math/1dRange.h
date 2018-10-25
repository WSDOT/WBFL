///////////////////////////////////////////////////////////////////////
// Math - Utility library of mathematical services
// Copyright © 1999-2010  Washington State Department of Transportation
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

#ifndef INCLUDED_MATH_1DRANGE_H_
#define INCLUDED_MATH_1DRANGE_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <Math\MathExp.h>


// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   math1dRange

   Class which defines a range in the real (Float64) number system


DESCRIPTION
   real range


COPYRIGHT
   Copyright © 1997-1998
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 01.20.1999 : Created file
*****************************************************************************/

class MATHCLASS math1dRange
{
   friend MATHFUNC bool operator==(const math1dRange& lhs, const math1dRange& rhs);

public:
   // BoundType
   // This enumeration encapsulates all types of range boundaries in the real domain
   enum BoundType { Bound,     // range has defined value at bound location
                    Limit};    // range defined up to, but not at, at this location (eg, Tan(90))

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor. Defines the null range: from (0,Limit) to (0,Limit)
   math1dRange();

   //------------------------------------------------------------------------
   // Construct a range explicitely
   math1dRange(Float64 leftLocation, BoundType leftBound, Float64 rightLocation, BoundType rightBound);

   //------------------------------------------------------------------------
   // Copy constructor
   math1dRange(const math1dRange& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~math1dRange();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   math1dRange& operator = (const math1dRange& rOther);

   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   // IsInRange
   // Returns true if the value is within the range
   bool IsInRange(Float64 value) const;

   //------------------------------------------------------------------------
   // IsNull
   // Returns true if the range is the empty set.
   bool IsNull() const;

   //------------------------------------------------------------------------
   // SetNull
   // Sets the left and right bounds to (0,Limit).
   void SetNull();

   //------------------------------------------------------------------------
   // IsIntersection
   // Returns true if the two ranges overlap
   bool IsIntersection(const math1dRange& rOther) const;

   //------------------------------------------------------------------------
   // Intersection
   // Returns the intersection (overlapping part) of the two ranges.
   math1dRange Intersection(const math1dRange& rOther) const;

   //------------------------------------------------------------------------
   // Union
   // Returns the union (enclosing boundary) of two ranges. The two ranges do not have to overlap.
   math1dRange Union(const math1dRange& rOther) const;

   // GROUP: ACCESS
   //------------------------------------------------------------------------
   // Set all parameters at once
   void Set(Float64 leftLocation, BoundType leftBound, Float64 rightLocation, BoundType rightBound);

   //------------------------------------------------------------------------
   // GetLeftBoundLocation
   // Returns the location of the left bound of the range. 
   Float64 GetLeftBoundLocation() const;

   //------------------------------------------------------------------------
   // SetLeftBoundLocation
   // Sets the left bound of the range.
   void SetLeftBoundLocation(Float64 bound);

   //------------------------------------------------------------------------
   // GetLeftBoundType
   // Returns the type of the left bound of the range.
   math1dRange::BoundType GetLeftBoundType() const;

   //------------------------------------------------------------------------
   // SetLeftBoundType
   // Sets the type of the left bound of the range.
   void SetLeftBoundType(math1dRange::BoundType type);

   //------------------------------------------------------------------------
   // GetRightBoundLocation
   // Returns the location of the Right bound of the range. 
   Float64 GetRightBoundLocation() const;

   //------------------------------------------------------------------------
   // SetRightBoundLocation
   // Sets the Right bound of the range.
   void SetRightBoundLocation(Float64 bound);

   //------------------------------------------------------------------------
   // GetRightBoundType
   // Returns the type of the Right bound of the range.
   math1dRange::BoundType GetRightBoundType() const;

   //------------------------------------------------------------------------
   // SetRightBoundType
   // Sets the type of the Right bound of the range.
   void SetRightBoundType(math1dRange::BoundType type);

   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const math1dRange& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const math1dRange& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   Float64 m_LeftLocation;
   BoundType m_LeftBound;
   Float64 m_RightLocation;
   BoundType m_RightBound;
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

public:
   // GROUP: DEBUG
   #if defined _DEBUG
   //------------------------------------------------------------------------
   // Returns true if the object is in a valid state, otherwise returns false.
   virtual bool AssertValid() const;

   //------------------------------------------------------------------------
   // Dumps the contents of the object to the given dump context.
   virtual void Dump(dbgDumpContext& os) const;
   #endif // _DEBUG

   #if defined _UNITTEST
   //------------------------------------------------------------------------
   // Runs a self-diagnostic test.  Returns true if the test passed,
   // otherwise false.
   static bool TestMe(dbgLog& rlog);
   #endif // _UNITTEST
};

// INLINE METHODS
//
//------------------------------------------------------------------------
// Returns true if lhs is equal to rhs,  otherwise false.
MATHFUNC bool operator==(const math1dRange& lhs, const math1dRange& rhs);

// EXTERNAL REFERENCES
//

#endif // INCLUDED_MATH_1DRANGE_H_
