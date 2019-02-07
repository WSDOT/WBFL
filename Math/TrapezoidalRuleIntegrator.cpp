///////////////////////////////////////////////////////////////////////
// Math - Utility library of mathematical services
// Copyright © 1999-2019  Washington State Department of Transportation
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

#include <Math\MathLib.h>

/****************************************************************************
CLASS
   mathTrapezoidalRuleIntegrator
****************************************************************************/

#include <Math\TrapezoidalRuleIntegrator.h>
#include <Math\Function2d.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////// PUBLIC     ///////////////////////////////////////

Float64 mathTrapezoidalRuleIntegrator::Evaluate(const mathFunction2d& f,Float64 xMin,Float64 xMax,Uint16 nIntervals)
{
   Float64 stepSize = (xMax - xMin)/nIntervals;

   Float64 A = 0;
   for ( Uint16 i = 0; i < nIntervals; i++ )
   {
      Float64 xa = xMin + stepSize*i;
      Float64 xb = xMin + stepSize*(i+1);

      Float64 ya = f.Evaluate(xa);
      Float64 yb = f.Evaluate(xb);

      A += 0.5*(yb+ya)*(xb-xa);
   }

   return A;
}
