///////////////////////////////////////////////////////////////////////
// Roark - Simple span beam forumla, patterned after Roark's formulas
//         for Stress and Strain
// Copyright © 1999-2013  Washington State Department of Transportation
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

#include <Roark\RoarkLib.h>
#include <Roark\UnitTest.h>
#include <Roark\Roark.h>
#include <Roark\BeamWithEqualOverhangsUniformLoad.h>
#include <Roark\BeamWithUnequalOverhangsUniformLoad.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   bmfUnitTest
****************************************************************************/

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
bool rkUnitTest::TestMe(dbgLog& rlog)
{
   bool bPassed = true;

#if defined _UNITTEST
   bPassed &= rkPPIntermediateLoad::TestMe(rlog);
   bPassed &= rkPPPartUniformLoad::TestMe(rlog);
   bPassed &= rkPPIntermediateCouple::TestMe(rlog);
   bPassed &= rkBeamWithEqualOverhangsUniformLoad::TestMe(rlog);
   bPassed &= rkBeamWithUnequalOverhangsUniformLoad::TestMe(rlog);
#endif

   return bPassed;
}

#if defined _UNITTEST
#include "Private.h"
#include <MathEx.h>

// Use numerical integration to test the beam equations
bool Test_Numerical(dbgLog& rlog,const rkRoarkBeam& beam)
{
   TESTME_PROLOGUE( "Test_Numerical" );

   Uint16 nIntSteps = 100;
   Uint16 nCheckPnts = 10;
   Float64 sumShear = 0;  // cummulated area under the shear diagram
   Float64 sumMoment = 0; // cummulated area under the moment diagram
   Float64 sumRotation = 0; // cummulated area under the rotation diagram
   Float64 EI = beam.GetEI();
   Float64 Ma, Mb;
   Float64 ra, rb;
   Float64 ya, yb;

   Ma = beam.ComputeMoment(0).Right();
   Mb = beam.ComputeMoment(beam.GetL()).Left();
   ra = beam.ComputeRotation(0);
   rb = beam.ComputeRotation(beam.GetL());
   ya = beam.ComputeDeflection(0);
   yb = beam.ComputeDeflection(beam.GetL());

   Float64 dx = beam.GetL() / nIntSteps;
   Float64 sumx = 0;

   for ( Uint16 i = 0; i < nIntSteps; i++ )
   {
      Float64 x = i * dx;
      Float64 x_dx = x + dx;

      sysSectionValue V    = beam.ComputeShear( x );
      sysSectionValue V_dV = beam.ComputeShear( x_dx );
      sumShear += (V.Right() + V_dV.Left()) * dx / 2;

      sysSectionValue M    = beam.ComputeMoment( x );
      sysSectionValue M_dM = beam.ComputeMoment( x_dx );
      sumMoment += (M.Right() + M_dM.Left()) * dx / 2;

      Float64 r    = beam.ComputeRotation( x );
      Float64 r_dr = beam.ComputeRotation( x_dx );
      sumRotation += (r + r_dr) * dx / 2;

      if ( i % nCheckPnts == 0 )
      {
         sysSectionValue tstM = beam.ComputeMoment( x_dx );
         TRY_TESTME( IsEqual( tstM.Left(), sumShear + Ma, 0.1) );

         Float64 tstR = beam.ComputeRotation( x_dx );
         TRY_TESTME( IsEqual( tstR, sumMoment/EI + ra, 0.1) );

         Float64 tstDelta = beam.ComputeDeflection( x_dx );
         TRY_TESTME( IsEqual( tstDelta, sumRotation + ya, 0.1) );
      }
   }

   Float64 yl, yr;
   beam.GetDeflections( &yl, &yr );
   TRY_TESTME( IsZero(yl) );
   TRY_TESTME( IsZero(yr) );

   TESTME_EPILOG( "Test_Numerical" );
}
#endif // _UNITTEST