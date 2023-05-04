///////////////////////////////////////////////////////////////////////
// Roark - Simple span beam formula, patterned after Roark's formulas
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
#include <Roark/PPPartialUniformLoad.h>

using namespace WBFL::Beams;

PPPartialUniformLoad::PPPartialUniformLoad(Float64 La,Float64 Lb,Float64 w,Float64 l,Float64 ei) :
RoarkBeam(l,ei)
{
   a = La;
   b = Lb;
   c = b - a;
   d = l - 0.5*a - 0.5*b;

   W = w*c;
}

std::shared_ptr<RoarkBeam> PPPartialUniformLoad::CreateClone() const
{
   return std::make_shared<PPPartialUniformLoad>( a, b, GetW(), GetL(), GetEI() );
}

void PPPartialUniformLoad::SetLa(Float64 la)
{
   a = la;
   c = b - a;
}

Float64 PPPartialUniformLoad::GetLa() const
{
   return a;
}

void PPPartialUniformLoad::SetLb(Float64 lb)
{
   b = lb;
   c = b - a;
}

Float64 PPPartialUniformLoad::GetLb() const
{
   return b;
}

void PPPartialUniformLoad::SetW(Float64 w)
{
   W = w * c;
}

Float64 PPPartialUniformLoad::GetW() const
{
   return W/c;
}

std::pair<Float64, Float64> PPPartialUniformLoad::GetReactions() const
{
   Float64 L = GetL();
   Float64 Ra = -W*d/L;
   Float64 Rb = -W*(a + 0.5*c)/L;
   return std::make_pair(Ra, Rb);
}

std::pair<Float64, Float64> PPPartialUniformLoad::GetMoments() const
{
   return std::make_pair(0.0, 0.0);
}

std::pair<Float64, Float64> PPPartialUniformLoad::GetRotations() const
{
   Float64 L = GetL();
   return std::make_pair(ComputeRotation(0),ComputeRotation(L));
}

std::pair<Float64, Float64> PPPartialUniformLoad::GetDeflections() const
{
   Float64 L = GetL();
   return std::make_pair(ComputeDeflection(0), ComputeDeflection(L));
}

WBFL::System::SectionValue PPPartialUniformLoad::ComputeShear(Float64 x) const
{
   Float64 V;
   
   if ( IsZero(W) )
      return 0;

   Float64 L = GetL();

   Float64 Ra, Rb;
   std::tie(Ra,Rb) = GetReactions();

   if (x < a)
      V = Ra;
   else if (x < b)
      V = Ra + W*(x - a)/c;
   else
      V = Ra + W;

   return WBFL::System::SectionValue( IsZero(x) ? 0.0 : V, IsEqual(x,L) ? 0.0 : V);
}

WBFL::System::SectionValue PPPartialUniformLoad::ComputeMoment(Float64 x) const
{
   Float64 M;


   if ( IsZero(W) )
      return 0;

   Float64 Ra, Rb;
   std::tie(Ra,Rb) = GetReactions();

   if (x < a)
      M = Ra*x;
   else if (x < b)
      M = Ra*x + W*(x-a)*(x-a)/(2*c);
   else
      M = Ra*x + W*(x - 0.5*a - 0.5*b);

   return M;
}

Float64 PPPartialUniformLoad::ComputeRotation(Float64 x) const
{
   Float64 r;

   if ( IsZero(W) )
      return 0;

   Float64 L, EI;
   std::tie(L,EI) = GetProperties();

   Float64 Ra, Rb;
   std::tie(Ra,Rb) = GetReactions();

   Float64 K1, K2, K3, K6;

   K6 = W*b*b*b/12 + W*pow((b-a),3)/24 - W*b*(b-a)*(b-a)/6 - W*a*b*b/4;
   K3 = -K6/L - Ra*L*L/6 - W*L*(L/3 - a/2 - b/2)/2;
   K2 = K3 - W/6*(b-a)*(b-a) - W*a*b/2;
   K1 = K2;

   if (x < a)
   {
      r = Ra*x*x/2 + K1;
   }
   else if (x < b)
   {
      r = Ra*x*x/2 + W*pow((x-a),3)/(6*c) + K2;
   }
   else
   {
      r = Ra*x*x/2 + W*(x*x/2 - a*x/2 - b*x/2) + K3;
   }

   r /= EI;

   return r;
}

Float64 PPPartialUniformLoad::ComputeDeflection(Float64 x) const
{
   Float64 y;

   if ( IsZero(W) )
      return 0;

   Float64 L, EI;
   std::tie(L,EI) = GetProperties();

   Float64 Ra, Rb;
   std::tie(Ra,Rb) = GetReactions();

   Float64 K1, K2, K3, K6;

   K6 = W*b*b*b/12 + W*pow((b-a),3)/24 - W*b*(b-a)*(b-a)/6 - W*a*b*b/4;
   K3 = -K6/L - Ra*L*L/6 - W*L*(L/3 - a/2 - b/2)/2;
   K2 = K3 - W/6*(b-a)*(b-a) - W*a*b/2;
   K1 = K2;

   if ( x < a )
   {
      y = Ra*x*x*x/6 + K1*x;
   }
   else if ( x < b )
   {
      y = Ra*x*x*x/6 + W*pow((x-a),4)/(24*c) + K2*x;
   }
   else
   {
      y = Ra*x*x*x/6 + W*(x*x*x/6 - a*x*x/4 - b*x*x/4) + K3*x + K6;
   }

   y /= EI;

   return y;
}

#if defined _DEBUG
bool PPPartialUniformLoad::AssertValid() const
{
   Float64 L = GetL();

   if ( a < 0 || L < a )
      return false;

   if ( b < 0 || L < b )
      return false;

   if ( b < a )
      return false;

   return __super::AssertValid();
}

void PPPartialUniformLoad::Dump(WBFL::Debug::LogContext& os) const
{
   os << "Dump for PPPartUniformLoad" << WBFL::Debug::endl;
   os << " a = " << a << WBFL::Debug::endl;
   os << " b = " << b << WBFL::Debug::endl;
   os << " c = " << c << WBFL::Debug::endl;
   os << " d = " << d << WBFL::Debug::endl;
   os << " W = " << W << WBFL::Debug::endl;
   __super::Dump( os );
}
#endif // _DEBUG

#if defined _UNITTEST
#include "Private.h"

// When a symmetrically loaded beam is used, the results must be symmetrical
bool Test_Symmetry(WBFL::Debug::Log& rlog,Float64 fra)
{
   TESTME_PROLOGUE("PPPartialUniformLoad - Test_Symmetry");

   Float64 L = 10;
   Float64 La = fra*L;
   Float64 Lb = (1.0 - fra)*L;
   Float64 EI = 1;
   Float64 w = -10;
   Uint16 nPoints = 10;
   Uint16 i;

   PPPartialUniformLoad beam(La,Lb,w,L,EI);
   for ( i = 0; i < nPoints/2; i++ )
   {
      WBFL::System::SectionValue lShear, rShear;
      WBFL::System::SectionValue lMoment, rMoment;

      Float64 xl = i * L / nPoints;
      Float64 xr = L - i * L / nPoints;

      lShear = beam.ComputeShear( xl );
      rShear = beam.ComputeShear( xr );
      TRY_TESTME( IsEqual( lShear.Left(),  -rShear.Right() ) );
      TRY_TESTME( IsEqual( lShear.Right(), -rShear.Left()  ) );

      lMoment = beam.ComputeMoment( xl );
      rMoment = beam.ComputeMoment( xr );
      TRY_TESTME( IsEqual( lMoment.Left(),  rMoment.Right() ) );
      TRY_TESTME( IsEqual( lMoment.Right(), rMoment.Left()  ) );

      TRY_TESTME( IsEqual( beam.ComputeRotation(xl),  -beam.ComputeRotation(xr)   ) );
      TRY_TESTME( IsEqual( beam.ComputeDeflection(xl), beam.ComputeDeflection(xr) ) );
   }

   TESTME_EPILOG("PPPartialUniformLoad - Test_Symmetry");
}

bool PPPartialUniformLoad::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("PPPartialUniformLoad");
   Float64 La = 0;
   Float64 Lb = 10;
   Float64 w = -1;
   Float64 l = 10;
   Float64 ei = 1;

   PPPartialUniformLoad beam(La,Lb,w,l,ei);
   Float64 Ra, Rb;
   std::tie(Ra,Rb) = beam.GetReactions();
   TRY_TESTME( IsEqual(Ra,5.0) );
   TRY_TESTME( IsEqual(Rb ,5.0) );

   WBFL::System::SectionValue Mcl = beam.ComputeMoment(5);
   TRY_TESTME( IsEqual(Mcl.Left(),12.5) && IsEqual(Mcl.Right(),12.5) );

   WBFL::System::SectionValue Vcl = beam.ComputeShear(5);
   TRY_TESTME( IsEqual(Vcl.Left(),0.0) && IsEqual(Vcl.Right(),0.0) );

   WBFL::System::SectionValue V25 = beam.ComputeShear( 0.25*l );
   TRY_TESTME( IsEqual(V25.Left(),V25.Right()) && IsEqual(V25.Left(),2.5) );

   WBFL::System::SectionValue V75 = beam.ComputeShear( 0.75*l );
   TRY_TESTME( IsEqual(V75.Left(),V75.Right()) && IsEqual(V75.Left(),-2.5) );

   // Check deflections
   TRY_TESTME( IsZero(beam.ComputeDeflection(0)) );
   TRY_TESTME( IsZero(beam.ComputeDeflection(l)) );

   Float64 D50 = beam.ComputeDeflection(5);
   Float64 delta =  (5*w*l*l*l*l)/(384*ei);
   TRY_TESTME( IsEqual(D50,delta) );

   // Test signs of rotations
   TRY_TESTME( beam.ComputeRotation(0) < 0 );
   TRY_TESTME( beam.ComputeRotation(l) > 0 );

   TRY_TESTME( Test_Symmetry(rlog,0.00) );
   TRY_TESTME( Test_Symmetry(rlog,0.25) );
   TRY_TESTME( Test_Symmetry(rlog,0.50) );

   TRY_TESTME( Test_Numerical(rlog, beam ) );
   TRY_TESTME( Test_Numerical(rlog, PPPartialUniformLoad(2,5,-10,10,1) ) );
   TRY_TESTME( Test_Numerical(rlog, PPPartialUniformLoad(4,9,-10,10,1) ) );
   TRY_TESTME( Test_Numerical(rlog, PPPartialUniformLoad(9,10,-10,10,1) ) );


   TESTME_EPILOG("PPPartialUniformLoad");
}
#endif // _UNITTEST
