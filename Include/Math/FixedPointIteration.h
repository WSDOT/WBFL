///////////////////////////////////////////////////////////////////////
// Math - Utility library of mathematical services
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

#ifndef INCLUDED_MATH_FIXEDPOINTITERATION_H_
#define INCLUDED_MATH_FIXEDPOINTITERATION_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <Math\MathExp.h>
#include <Math\Function2d.h>

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//
class MATHCLASS mathXFixedPointIterationFailed : public sysXBase
{
public:
   // GROUP: ENUMERATIONS
   enum Reason {
      Unknown,        // The reason is unknown
      MaxIterExceeded // The maximum number of iterations were exceeded
   };

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   mathXFixedPointIterationFailed(Reason reason,Float64 last,LPCTSTR file,Int16 line);

   //------------------------------------------------------------------------
   // Default constructor
   mathXFixedPointIterationFailed(const mathXFixedPointIterationFailed& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~mathXFixedPointIterationFailed();

   // GROUP: OPERATORS

   //------------------------------------------------------------------------
   // Assignment operator
   mathXFixedPointIterationFailed& operator=(const mathXFixedPointIterationFailed& rOther);

   // GROUP: OPERATIONS
   // GROUP: ACCESS

   //------------------------------------------------------------------------
   void Throw() const;
   //------------------------------------------------------------------------
   Float64 GetLast() const;
   //------------------------------------------------------------------------
   Int32 GetReason() const;
   //------------------------------------------------------------------------
   Reason GetReasonCode() const;

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
   Reason m_Reason;
   Float64 m_Last;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

/*****************************************************************************
CLASS 
   mathFixedPointIteration

   This class implements a fixed-point iteration method for finding a solution
   to a function of the form  g(x) = x

DESCRIPTION
   This class implements a fixed-point iteration method for finding a solution
   to a function of the form  g(x) = x

   Reference: Numerical Analysis, 4th Edition, Burden & Faires

COPYRIGHT
   Copyright (c) 2005
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 06.28.2005 : Created file
*****************************************************************************/

class MATHCLASS mathFixedPointIteration
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   mathFixedPointIteration();

   //------------------------------------------------------------------------
   // Destructor
   virtual ~mathFixedPointIteration();

   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Finds the solution to g(x) = x starting at xo
   virtual Float64 Solve(const mathFunction2d& f,Float64 xo,Float64 tol,long maxIter=100);

   // GROUP: ACCESS
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
   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
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

#endif // INCLUDED_MATH_FIXEDPOINTITERATION_H_
