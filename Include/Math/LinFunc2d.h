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

#ifndef INCLUDED_MATH_LINFUNC2D_H_
#define INCLUDED_MATH_LINFUNC2D_H_
#pragma once

// SYSTEM INCLUDES
//
#include <Math\MathExp.h>
#include <Math\Function2d.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   mathLinFunc2d

   Derived from mathFunction2d,  this class represents a linear function of
   the form f(x) = mx + b.


DESCRIPTION
   Derived from mathFunction2d,  this class represents a linear function of
   the form f(x) = mx + b.

LOG
   rab : 11.17.1997 : Created file
*****************************************************************************/

class MATHCLASS mathLinFunc2d : public mathFunction2d
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor.  Creates a function whose slope and y-intercept
   // are zero.
   mathLinFunc2d();

   //------------------------------------------------------------------------
   // Creates a linear function using slope and yIntercept.
   mathLinFunc2d(Float64 slope,Float64 yIntercept);

   //------------------------------------------------------------------------
   // Copy constructor
   mathLinFunc2d(const mathLinFunc2d& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~mathLinFunc2d();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   mathLinFunc2d& operator = (const mathLinFunc2d& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   Float64 Evaluate(Float64 x) const;

   virtual mathFunction2d* Clone() const override;

   Float64 GetSlope() const;
   void SetSlope(Float64 slope);

   Float64 GetYIntercept() const;
   void SetYIntercept(Float64 yIntercept);

   // GROUP: ACCESS
   // GROUP: INQUIRY
   // GROUP: DEBUG
#if defined _DEBUG
   //------------------------------------------------------------------------
   // Returns <b>true</b> if the class is in a valid state, otherwise returns
   // <b>false</b>.
   virtual bool AssertValid() const override;

   //------------------------------------------------------------------------
   // Dumps the contents of the class to the given stream.
   virtual void Dump(dbgDumpContext& os) const override;
#endif // _DEBUG

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const mathLinFunc2d& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const mathLinFunc2d& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   Float64 m_Slope;
   Float64 m_Yintercept;

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

#endif // INCLUDED_MATH_LINFUNC2D_H_
