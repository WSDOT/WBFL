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
#include <Roark\Roark.h>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

rkPPIntermediateCouple::rkPPIntermediateCouple(Float64 Mo,Float64 La,Float64 l,Float64 e,Float64 i) :
rkRoarkBeam(l,e,i)
{
   M = Mo;
   a = La;
}

rkPPIntermediateCouple::rkPPIntermediateCouple(const rkPPIntermediateCouple& rOther) :
rkRoarkBeam( rOther )
{
   M = rOther.M;
   a = rOther.a;
}

rkRoarkBeam* rkPPIntermediateCouple::CreateClone() const
{
   return new rkPPIntermediateCouple( *this );
}

Float64 rkPPIntermediateCouple::GetLa() const
{
   return a;
}

Float64 rkPPIntermediateCouple::GetMo() const
{
   return M;
}

void rkPPIntermediateCouple::GetReactions(Float64 *pRa,Float64* pRb) const
{
   *pRa = M/L;
   *pRb = -M/L;
}

void rkPPIntermediateCouple::GetMoments(Float64* pMa,Float64* pMb) const
{
   *pMa = 0.0;
   *pMb = 0.0;
}

void rkPPIntermediateCouple::GetRotations(Float64* pra,Float64* prb) const
{
   *pra = ComputeRotation(0.0);
   *prb = ComputeRotation(L);
}

void rkPPIntermediateCouple::GetDeflections(Float64* pYa,Float64* pYb) const
{
   *pYa = ComputeDeflection(0.0);
   *pYb = ComputeDeflection(L);
}

sysSectionValue rkPPIntermediateCouple::ComputeShear(Float64 /*x*/) const
{
   return M/L;
}

sysSectionValue rkPPIntermediateCouple::ComputeMoment(Float64 x) const
{
   sysSectionValue m;

   // Compute moments left and right of a
   Float64 left  = M*x/L;
   Float64 right = M*x/L - M;

   if (x < a)
   {
      m = left;
   }
   else if ( IsEqual(x,a) )
   {
      m.Left()  = left;
      m.Right() = right;
   }
   else
   {
      m = right;
   }

   if ( IsZero(x) )
      m.Left() = 0.0;

   if ( IsEqual(x,L) )
      m.Right() = 0.0;

   return m;
}

Float64 rkPPIntermediateCouple::ComputeRotation(Float64 x) const
{
   Float64 r;

   if ( x < a )
   {
      r = M*x*x/(2*L) + M*L/3 + M*a*a/(2*L) - M*a;
   }
   else
   {
      r = M*x*x/(2*L) - M*x + M*L/3 + M*a*a/(2*L);
   }

   r /= EI;

   return r;
}

Float64 rkPPIntermediateCouple::ComputeDeflection(Float64 x) const
{
   Float64 y;

   if ( x < a )
   {
      y = M*x*x*x/(6*L) +(M*L/3 + M*a*a/(2*L) - M*a)*x;
   }
   else
   {
      y = M*x*x*x/(6*L) - M*x*x/2 + (M*L/3 + M*a*a/(2*L))*x - M*a*a/2;
   }

   y /= EI;

   return y;
}

//======================== DEBUG      =======================================
#if defined _DEBUG
bool rkPPIntermediateCouple::AssertValid() const
{
   if ( a < 0 || L < a )  // a must be on the beam
      return false;

   return rkRoarkBeam::AssertValid();
}

void rkPPIntermediateCouple::Dump(dbgDumpContext& os) const
{
   os << "Dump for rkPPIntermediateCouple" << endl;
   os << " a = " << a << endl;
   os << " M = " << M << endl;
   rkRoarkBeam::Dump( os );
}
#endif // _DEBUG

#if defined _UNITTEST
#include "Private.h"
bool rkPPIntermediateCouple::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("rkPPIntermediateCouple");

// Don't run this test with the concentrated moment anywhere but the ends of the girder.
// The numerical integration routine can't handle the discontinuity in the moment diagram
// caused by the concentrated load.
//   TRY_TESTME( Test_Numerical(rlog,rkPPIntermediateCouple(10,5,10,1,1)) );
   TRY_TESTME( Test_Numerical(rlog,rkPPIntermediateCouple(10,0,10,1,1)) );
   TRY_TESTME( Test_Numerical(rlog,rkPPIntermediateCouple(10,10,10,1,1)) );

   TESTME_EPILOG("PPIntermediateCouple");
}
#endif // _UNITTEST
