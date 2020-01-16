///////////////////////////////////////////////////////////////////////
// Math - Utility library of mathematical services
// Copyright © 1999-2020  Washington State Department of Transportation
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

#ifndef INCLUDED_MATH_PWLINEARFUNCTION2D_H_
#define INCLUDED_MATH_PWLINEARFUNCTION2D_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <Math\MathExp.h>
#include <Math\Function2d.h>
#include <Math\1dRange.h>
#include <GeometricPrimitives\GeometricPrimitives.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   mathPwLinearFunction2d

   Piecewise Linear representation of a function


DESCRIPTION
   Derived from mathFunction2d

LOG
   rdp : 01.25.1999 : Created file
*****************************************************************************/

class MATHCLASS mathPwLinearFunction2d : public mathFunction2d
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   mathPwLinearFunction2d();

   //------------------------------------------------------------------------
   // Destructor
   virtual ~mathPwLinearFunction2d();

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   // Evaluates the function at x.
   Float64 Evaluate(Float64 x) const = 0;

   //------------------------------------------------------------------------
   // GetRange
   // Returns the range over which the function is valid.
   virtual math1dRange GetRange() const = 0;

   //------------------------------------------------------------------------
   // GetNumPoints
   // Returns the number of points which define the segments of the function.
   virtual CollectionIndexType GetNumPoints() const = 0;

   //------------------------------------------------------------------------
   // GetPoint
   // Returns the ith point. (zero-based)
   virtual gpPoint2d GetPoint(CollectionIndexType pnum) const = 0;

   //------------------------------------------------------------------------
   // GetPoints
   // Returns all points for the line segments which make up the function.
   virtual std::vector<gpPoint2d> GetPoints() const = 0;

protected:
   // Prevent accidental copying and assignment
   mathPwLinearFunction2d(const mathPwLinearFunction2d&) = delete;
   mathPwLinearFunction2d& operator=(const mathPwLinearFunction2d&) = delete;

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

// EXTERNAL REFERENCES
//

#endif // INCLUDED_MATH_PWLINEARFUNCTION2D_H_
