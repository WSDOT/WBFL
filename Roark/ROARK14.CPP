///////////////////////////////////////////////////////////////////////
// Roark - Simple span beam forumla, patterned after Roark's formulas
//         for Stress and Strain
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

#include <Roark\RoarkLib.h>
#include <Roark\Roark.h>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

rkPPPartUniformLoad::rkPPPartUniformLoad(Float64 La,Float64 Lb,Float64 w,Float64 l,Float64 e,Float64 i) :
rkRoarkBeam(l,e,i)
{
   a = La;
   b = Lb;
   c = b - a;
   d = l - 0.5*a - 0.5*b;

   W = w*c;
}

rkPPPartUniformLoad::rkPPPartUniformLoad(const rkPPPartUniformLoad& rOther) :
rkRoarkBeam(rOther)
{
   a = rOther.a;
   b = rOther.b;
   c = rOther.c;
   d = rOther.d;
   W = rOther.W;
}

rkRoarkBeam* rkPPPartUniformLoad::CreateClone() const
{
   return new rkPPPartUniformLoad( *this );
}

Float64 rkPPPartUniformLoad::GetLa() const
{
   return a;
}

Float64 rkPPPartUniformLoad::GetLb() const
{
   return b;
}

Float64 rkPPPartUniformLoad::GetW() const
{
   return W/c;
}

void rkPPPartUniformLoad::GetReactions(Float64* pRa,Float64* pRb) const
{
   *pRa = -W*d/L;
   *pRb = -W*(a + 0.5*c)/L;
}

void rkPPPartUniformLoad::GetMoments(Float64* pMa,Float64* pMb) const
{
   *pMa = 0.;
   *pMb = 0.;
}

void rkPPPartUniformLoad::GetRotations(Float64* pra,Float64* prb) const
{
   *pra = ComputeRotation(0);
   *prb = ComputeRotation(L);
}

void rkPPPartUniformLoad::GetDeflections(Float64* pYa,Float64* pYb) const
{
   *pYa = ComputeDeflection(0);
   *pYb = ComputeDeflection(L);
}

sysSectionValue rkPPPartUniformLoad::ComputeShear(Float64 x) const
{
   Float64 V;
   Float64 Ra,Rb;

   if ( IsZero(W) )
      return 0;

   GetReactions(&Ra,&Rb);

   if (x < a)
      V = Ra;
   else if (x < b)
      V = Ra + W*(x - a)/c;
   else
      V = Ra + W;

   return sysSectionValue( IsZero(x) ? 0.0 : V, IsEqual(x,L) ? 0.0 : V);
}

sysSectionValue rkPPPartUniformLoad::ComputeMoment(Float64 x) const
{
   Float64 M;
   Float64 Ra, Rb;

   if ( IsZero(W) )
      return 0;

   GetReactions(&Ra,&Rb);

   if (x < a)
      M = Ra*x;
   else if (x < b)
      M = Ra*x + W*(x-a)*(x-a)/(2*c);
   else
      M = Ra*x + W*(x - 0.5*a - 0.5*b);

   return M;
}

Float64 rkPPPartUniformLoad::ComputeRotation(Float64 x) const
{
   Float64 r;

   Float64 Ra, Rb;

   if ( IsZero(W) )
      return 0;

   GetReactions(&Ra,&Rb);

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

Float64 rkPPPartUniformLoad::ComputeDeflection(Float64 x) const
{
   Float64 y;

   Float64 Ra, Rb;

   if ( IsZero(W) )
      return 0;

   GetReactions(&Ra,&Rb);

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

//======================== DEBUG      =======================================
#if defined _DEBUG
bool rkPPPartUniformLoad::AssertValid() const
{
   if ( a < 0 || L < a )
      return false;

   if ( b < 0 || L < b )
      return false;

   if ( b < a )
      return false;

   return rkRoarkBeam::AssertValid();
}

void rkPPPartUniformLoad::Dump(dbgDumpContext& os) const
{
   os << "Dump for rkPPPartUniformLoad" << endl;
   os << " a = " << a << endl;
   os << " b = " << b << endl;
   os << " c = " << c << endl;
   os << " d = " << d << endl;
   os << " W = " << W << endl;
   rkRoarkBeam::Dump( os );
}
#endif // _DEBUG

#if defined _UNITTEST
#include "Private.h"

// When a symmetrically loaded beam is used, the results must be symmetrical
bool Test_Symmetry(dbgLog& rlog,Float64 fra)
{
   TESTME_PROLOGUE("rkPPPartUniformLoad - Test_Symmetry");

   Float64 L = 10;
   Float64 La = fra*L;
   Float64 Lb = (1.0 - fra)*L;
   Float64 E = 1;
   Float64 I = 1;
   Float64 w = -10;
   Uint16 nPoints = 10;
   Uint16 i;

   rkPPPartUniformLoad beam(La,Lb,w,L,E,I);
   for ( i = 0; i < nPoints/2; i++ )
   {
      sysSectionValue lShear, rShear;
      sysSectionValue lMoment, rMoment;

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

   TESTME_EPILOG("rkPPPartUniformLoad - Test_Symmetry");
}

bool rkPPPartUniformLoad::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("rkPPPartUniformLoad");
   Float64 La = 0;
   Float64 Lb = 10;
   Float64 w = -1;
   Float64 l = 10;
   Float64 e = 1;
   Float64 i = 1;

   rkPPPartUniformLoad beam(La,Lb,w,l,e,i);
   Float64 Ra, Rb;
   beam.GetReactions(&Ra,&Rb);
   TRY_TESTME( IsEqual(Ra,5.0) );
   TRY_TESTME( IsEqual(Rb ,5.0) );

   sysSectionValue Mcl = beam.ComputeMoment(5);
   TRY_TESTME( IsEqual(Mcl.Left(),12.5) && IsEqual(Mcl.Right(),12.5) );

   sysSectionValue Vcl = beam.ComputeShear(5);
   TRY_TESTME( IsEqual(Vcl.Left(),0.0) && IsEqual(Vcl.Right(),0.0) );

   sysSectionValue V25 = beam.ComputeShear( 0.25*l );
   TRY_TESTME( IsEqual(V25.Left(),V25.Right()) && IsEqual(V25.Left(),2.5) );

   sysSectionValue V75 = beam.ComputeShear( 0.75*l );
   TRY_TESTME( IsEqual(V75.Left(),V75.Right()) && IsEqual(V75.Left(),-2.5) );

   // Check deflections
   TRY_TESTME( IsZero(beam.ComputeDeflection(0)) );
   TRY_TESTME( IsZero(beam.ComputeDeflection(l)) );

   Float64 D50 = beam.ComputeDeflection(5);
   Float64 delta =  (5*w*l*l*l*l)/(384*e*i);
   TRY_TESTME( IsEqual(D50,delta) );

   // Test signs of rotations
   TRY_TESTME( beam.ComputeRotation(0) < 0 );
   TRY_TESTME( beam.ComputeRotation(l) > 0 );

   TRY_TESTME( Test_Symmetry(rlog,0.00) );
   TRY_TESTME( Test_Symmetry(rlog,0.25) );
   TRY_TESTME( Test_Symmetry(rlog,0.50) );

   TRY_TESTME( Test_Numerical(rlog, beam ) );
   TRY_TESTME( Test_Numerical(rlog, rkPPPartUniformLoad(2,5,-10,10,1,1) ) );
   TRY_TESTME( Test_Numerical(rlog, rkPPPartUniformLoad(4,9,-10,10,1,1) ) );
   TRY_TESTME( Test_Numerical(rlog, rkPPPartUniformLoad(9,10,-10,10,1,1) ) );


   TESTME_EPILOG("rkPPPartUniformLoad");
}
#endif // _UNITTEST
