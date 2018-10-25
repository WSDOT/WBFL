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

#ifndef INCLUDED_MATH_CUBICSOLVER_H_
#define INCLUDED_MATH_CUBICSOLVER_H_
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
   mathCubicSolver

   Utility class to solve quadratic equations.


DESCRIPTION
   Utility class to solve quadratic equations. 

   Finds the roots of equations having the form ax^3 + bx^2 + cx + d = 0


COPYRIGHT
   Copyright © 1997-2008
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 06.25.2008 : Created file
*****************************************************************************/

class MATHCLASS mathCubicSolver
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   mathCubicSolver(Float64 a,Float64 b,Float64 c,Float64 d);

   //------------------------------------------------------------------------
   // Copy constructor
   mathCubicSolver(const mathCubicSolver& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~mathCubicSolver();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   mathCubicSolver& operator = (const mathCubicSolver& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Solves the cubic equation.  Returns number of roots found
   int Solve(Float64* x1, Float64* x2,Float64* x3) const;

   // GROUP: ACCESS

   //------------------------------------------------------------------------
   // Sets the coefficient a
   void SetA(Float64 a);

   //------------------------------------------------------------------------
   // Gets the coefficient a
   Float64 GetA() const;

   //------------------------------------------------------------------------
   // Sets the coefficient b
   void SetB(Float64 b);

   //------------------------------------------------------------------------
   // Gets the coefficient b
   Float64 GetB() const;

   //------------------------------------------------------------------------
   // Sets the coefficient c
   void SetC(Float64 c);

   //------------------------------------------------------------------------
   // Gets the coefficient c
   Float64 GetC() const;

   //------------------------------------------------------------------------
   // Sets the coefficient d
   void SetD(Float64 d);

   //------------------------------------------------------------------------
   // Gets the coefficient d
   Float64 GetD() const;


   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const mathCubicSolver& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const mathCubicSolver& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   Float64 m_A;
   Float64 m_B;
   Float64 m_C;
   Float64 m_D;

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

// EXTERNAL REFERENCES
//

#endif // INCLUDED_MATH_CUBICSOLVER_H_
