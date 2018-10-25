///////////////////////////////////////////////////////////////////////
// Math - Utility library of mathematical services
// Copyright © 1999-2016  Washington State Department of Transportation
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

#ifndef INCLUDED_MATH_TRAPEZOIDALRULEINTEGRATOR_H_
#define INCLUDED_MATH_TRAPEZOIDALRULEINTEGRATOR_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <Math\MathExp.h>
#include <Math\NumericIntegrator2d.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   mathTrapezoidalRuleIntegrator

   Utility class to integrate functions using the trapezoidal rule


DESCRIPTION
   Utility class to integrate functions using the trapezoidal rule


COPYRIGHT
   Copyright © 1997-2008
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 06.24.2008 : Created file
*****************************************************************************/

class MATHCLASS mathTrapezoidalRuleIntegrator : public mathNumericIntegrator2d
{
public:
   // GROUP: LIFECYCLE
   virtual Float64 Evaluate(const mathFunction2d& f,Float64 xMin,Float64 xMax,Uint16 nIntervals);

};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_MATH_TRAPEZOIDALRULEINTEGRATOR_H_
