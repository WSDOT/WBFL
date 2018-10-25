///////////////////////////////////////////////////////////////////////
// Math - Utility library of mathematical services
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
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#ifndef INCLUDED_MATH_FUNCTION2D_H_
#define INCLUDED_MATH_FUNCTION2D_H_
#pragma once

// SYSTEM INCLUDES
//
#include <Math\MathExp.h>
#include <System\Exception.h>

// PROJECT INCLUDES
//

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
class MATHCLASS mathFunction2d;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   mathXEvalError

   Math function evaluation error exception.


DESCRIPTION
   Math function evaluation error exception.  Thrown from 
   mathFunction2d::Evaluate() if an error occurs.

COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 11.17.1997 : Created file
*****************************************************************************/

class MATHCLASS mathXEvalError : public sysXBase
{
public:
   // GROUP: ENUMERATIONS

   //------------------------------------------------------------------------
   enum Reason {
      Unknown,     // Evaluation failed for an unknown reason
      Undefined,   // Function is not defined at the evalation point
      MultiValued, // Function is multivalued at the evaluation point
      PosInfinity, // Function evaluation is positive infinity
      NegInfinity  // Function evaluation is negative infinity
   };

   // GROUP: LIFECYCLE


   //------------------------------------------------------------------------
   mathXEvalError(Reason reason,const char* file, Int16 line);

   //------------------------------------------------------------------------
   // Copy constructor
   mathXEvalError(const mathXEvalError& rOther);

   //------------------------------------------------------------------------
   // Destructor
   ~mathXEvalError();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   mathXEvalError& operator=(const mathXEvalError& rOther);

   // GROUP: OPERATIONS
   // GROUP: ACCESS

   void Throw() const;
   Int32 GetReason() const;
   //------------------------------------------------------------------------
   // Returns the reason for the evaluation error.
   Reason GetReasonCode() const;

   // GROUP: INQUIRY
   // GROUP: DEBUG

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   void MakeCopy( const mathXEvalError& rOther );

   //------------------------------------------------------------------------
   void MakeAssignment( const mathXEvalError& rOther );

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   Reason  m_Reason;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

/*****************************************************************************
CLASS 
   mathFunction2d

   Defines an abstract interface for a continuous single variable, single
   value function.


DESCRIPTION
   Defines an abstract interface for a continuous single variable, single
   value function.


COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 11.17.1997 : Created file
*****************************************************************************/

class MATHCLASS mathFunction2d
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   mathFunction2d();

   //------------------------------------------------------------------------
   // Destructor
   virtual ~mathFunction2d();

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   // Evaluatest the function at x.  If an error occurs during the evaluation,
   // a mathXEvalError exception will be thrown.
   virtual Float64 Evaluate(Float64 x) const = 0;

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

   // Prevent accidental copying and assignment
   mathFunction2d(const mathFunction2d&);
   mathFunction2d& operator=(const mathFunction2d&);

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_MATH_FUNCTION2D_H_
