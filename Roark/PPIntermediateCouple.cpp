///////////////////////////////////////////////////////////////////////
// Roark - Simple span beam forumla, patterned after Roark's formulas
//         for Stress and Strain
// Copyright © 1999-2023  Washington State Department of Transportation
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

#include <Roark/RoarkLib.h>
#include <Roark/PPIntermediateCouple.h>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace WBFL::Beams;

PPIntermediateCouple::PPIntermediateCouple(Float64 Mo,Float64 La,Float64 l,Float64 ei) :
RoarkBeam(l,ei)
{
   M = Mo;
   a = La;
}

std::unique_ptr<RoarkBeam> PPIntermediateCouple::CreateClone() const
{
   return std::make_unique<PPIntermediateCouple>(M,a,GetL(),GetEI());
}

void PPIntermediateCouple::SetLa(Float64 la)
{
   a = la;
}

Float64 PPIntermediateCouple::GetLa() const
{
   return a;
}

void PPIntermediateCouple::SetMo(Float64 mo)
{
   M = mo;
}

Float64 PPIntermediateCouple::GetMo() const
{
   return M;
}

void PPIntermediateCouple::GetReactions(Float64 *pRa,Float64* pRb) const
{
   Float64 L = GetL();
   *pRa = M/L;
   *pRb = -M/L;
}

void PPIntermediateCouple::GetMoments(Float64* pMa,Float64* pMb) const
{
   *pMa = 0.0;
   *pMb = 0.0;
}

void PPIntermediateCouple::GetRotations(Float64* pra,Float64* prb) const
{
   Float64 L = GetL();
   *pra = ComputeRotation(0.0);
   *prb = ComputeRotation(L);
}

void PPIntermediateCouple::GetDeflections(Float64* pYa,Float64* pYb) const
{
   Float64 L = GetL();
   *pYa = ComputeDeflection(0.0);
   *pYb = ComputeDeflection(L);
}

WBFL::System::SectionValue PPIntermediateCouple::ComputeShear(Float64 /*x*/) const
{
   Float64 L = GetL();
   return M/L;
}

WBFL::System::SectionValue PPIntermediateCouple::ComputeMoment(Float64 x) const
{
   WBFL::System::SectionValue m;

   Float64 L = GetL();

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

Float64 PPIntermediateCouple::ComputeRotation(Float64 x) const
{
   Float64 r = 0;

   Float64 L, EI;
   GetProperties(&L, &EI);

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

Float64 PPIntermediateCouple::ComputeDeflection(Float64 x) const
{
   Float64 y = 0;

   Float64 L, EI;
   GetProperties(&L, &EI);

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
bool PPIntermediateCouple::AssertValid() const
{
   Float64 L = GetL();
   if ( a < 0 || L < a )  // a must be on the beam
      return false;

   return __super::AssertValid();
}

void PPIntermediateCouple::Dump(WBFL::Debug::LogContext& os) const
{
   os << "Dump for PPIntermediateCouple" << WBFL::Debug::endl;
   os << " a = " << a << WBFL::Debug::endl;
   os << " M = " << M << WBFL::Debug::endl;
   __super::Dump( os );
}
#endif // _DEBUG

#if defined _UNITTEST
#include "Private.h"
bool PPIntermediateCouple::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("PPIntermediateCouple");

// Don't run this test with the concentrated moment anywhere but the ends of the girder.
// The numerical integration routine can't handle the discontinuity in the moment diagram
// caused by the concentrated load.
//   TRY_TESTME( Test_Numerical(rlog,PPIntermediateCouple(10,5,10,1)) );
   TRY_TESTME( Test_Numerical(rlog,PPIntermediateCouple(10,0,10,1)) );
   TRY_TESTME( Test_Numerical(rlog,PPIntermediateCouple(10,10,10,1)) );

   TESTME_EPILOG("PPIntermediateCouple");
}
#endif // _UNITTEST
