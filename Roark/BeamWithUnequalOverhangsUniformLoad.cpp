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
#include <Roark/BeamWithUnequalOverhangsUniformLoad.h>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace WBFL::Beams;

/****************************************************************************
CLASS
   rkBeamWithUnequalOverhangsUniformLoad
   Based on PCI Design Manual, Design Aid 11.1.7
****************************************************************************/

BeamWithUnequalOverhangsUniformLoad::BeamWithUnequalOverhangsUniformLoad(Float64 length,Float64 a,Float64 b, Float64 w,Float64 ei):
RoarkBeam(length,ei),
m_LeftOverhang(a),
m_RightOverhang(b),
m_W(w)
{
   PRECONDITION(m_LeftOverhang>=0.0);
   PRECONDITION(m_RightOverhang>=0.0);
   PRECONDITION(m_LeftOverhang + m_RightOverhang < length);
}

BeamWithUnequalOverhangsUniformLoad::~BeamWithUnequalOverhangsUniformLoad()
{
}

std::unique_ptr<RoarkBeam> BeamWithUnequalOverhangsUniformLoad::CreateClone() const
{
   return std::make_unique<BeamWithUnequalOverhangsUniformLoad>(GetL(), m_LeftOverhang, m_RightOverhang, m_W, GetEI());
}

Float64 BeamWithUnequalOverhangsUniformLoad::GetLeftOverhang() const
{
   return m_LeftOverhang;
}

Float64 BeamWithUnequalOverhangsUniformLoad::GetRightOverhang() const
{
   return m_RightOverhang;
}

Float64 BeamWithUnequalOverhangsUniformLoad::GetW() const
{
   return m_W;
}

void BeamWithUnequalOverhangsUniformLoad::GetReactions(Float64 *pRa,Float64* pRb) const
{
   Float64 L = GetL();
   Float64 c = m_LeftOverhang;
   Float64 e = m_RightOverhang;
   Float64 d = L - c - e;
   Float64 W = m_W * L;

   (*pRa) = -W*(c+d-e)/(2*d);
   (*pRb) = -W*(d+e-c)/(2*d);
}

void BeamWithUnequalOverhangsUniformLoad::GetMoments(Float64* pMa,Float64* pMb) const
{
   Float64 L = GetL();
   Float64 c = m_LeftOverhang;
   Float64 e = m_RightOverhang;
   Float64 d = L - c - e;
   Float64 W = m_W * L;

   (*pMa) = W*c*c/(2*L);
   (*pMb) = W*e*e/(2*L);
}

void BeamWithUnequalOverhangsUniformLoad::GetRotations(Float64* pra,Float64* prb) const
{
   Float64 L = GetL();
   *pra=  ComputeRotation(m_LeftOverhang);
   *prb = ComputeRotation(L-m_RightOverhang);
}

void BeamWithUnequalOverhangsUniformLoad::GetDeflections(Float64* pYa,Float64* pYb) const
{
   *pYa = 0;
   *pYb = 0;
}

WBFL::System::SectionValue BeamWithUnequalOverhangsUniformLoad::ComputeShear(Float64 x) const
{
   Float64 L = GetL();
   PRECONDITION(0.0 <= x && x <= L);
   Float64 c = m_LeftOverhang;
   Float64 e = m_RightOverhang;
   Float64 d = L - c - e;
   Float64 W = m_W*L;

   Float64 Rl, Rr;
   GetReactions(&Rl,&Rr);

   WBFL::System::SectionValue v;
   if ( x < c )
   {
      x = c - x; // measure X positive left of the left support
      v = W*(c-x)/L;
   }
   else if ( x == c )  // left support
   {
      v.Left()  = W*c/L;
      v.Right() = Rl + W*c/L;
   }
   else if (c < x && x < c+d) // between supports
   {
      x = x - c; // measure X positive from left support
      v = Rl + W*(c+x)/L;
   }
   else if ( x == c+d )  // right support
   {
      v.Left() = Rl + W*(c+d)/L;
      v.Right() = -W*e/L;
   }
   else // right cantilever
   {
      x = x - c; // measure X positive from left support
      v = -W*(d+e-x)/L;
   }
   return v;
}

WBFL::System::SectionValue BeamWithUnequalOverhangsUniformLoad::ComputeMoment(Float64 x) const
{
   Float64 L = GetL();
   PRECONDITION(0.0 <= x && x <= L);
   Float64 c = m_LeftOverhang;
   Float64 e = m_RightOverhang;
   Float64 d = L - c - e;
   Float64 W = m_W*L;

   Float64 Rl, Rr;
   GetReactions(&Rl,&Rr);

   Float64 m;
   if ( x < c )
   {
      x = c - x; // measure X positive left of the left support
      m = W*(c-x)*(c-x)/(2*L);
   }
   else if (c <= x && x <= c+d) // between supports
   {
      x = x - c; // measure X positive from left support
      m = W*(c+x)*(c+x)/(2*L) + Rl*x;
   }
   else // right cantilever
   {
      x = x - c; // measure X positive from left support
      m = W*(e+d-x)*(e+d-x)/(2*L);
   }

   return m;
}

Float64 BeamWithUnequalOverhangsUniformLoad::ComputeRotation(Float64 x) const
{
   Float64 L, EI;
   GetProperties(&L, &EI);

   PRECONDITION(0.0 <= x && x <= L);
   Float64 c = m_LeftOverhang;
   Float64 e = m_RightOverhang;
   Float64 d = L - c - e;

   Float64 r_ei;
   if (x < c)
   {
      // left cantilever
      r_ei = (m_W / 24.0) * (4 * c * c * d + 2 * e * e * d - d * d * d + 4 * c * c * c - 4 * x * x * x);
   }
   else if (c <= x && x <= c + d) // between supports
   {
      x = x - c;
      r_ei = (m_W * x/ (2 * d)) * ((d * d + c * c - e * e) * x / 2 - d * (c * c + x * x / 3)) + ((m_W * d) / 24) * (4 * c * c + 2 * e * e - d * d);
   }
   else
   {
      // right cantilever
      x = x - c - d;
      r_ei = -(m_W / 24.0) * (12 * e * e * x + 4 * x * x * x - 12 * e * x * x - d * d * d + 2 * c * c * d + 4 * e * e * d);
   }

   return -r_ei / EI;
}

Float64 BeamWithUnequalOverhangsUniformLoad::ComputeDeflection(Float64 x) const
{
   Float64 L, EI;
   GetProperties(&L, &EI);

   PRECONDITION(0.0 <= x && x <= L);
   Float64 c = m_LeftOverhang;
   Float64 e = m_RightOverhang;
   Float64 d = L - c - e;
   Float64 W = m_W*L;

   Float64 Rl, Rr;
   GetReactions(&Rl,&Rr);

   Float64 y_ei;
   if ( x < c )
   {
      x = c - x; // measure X positive left of the left support
      y_ei = -W*x*(2*d*(e*e + 2*c*c) + 6*c*c*x - x*x*(4*c - x) - d*d*d);
   }
   else if (c <= x && x <= c+d) // between supports
   {
      x = x - c; // measure X positive from left support
      y_ei = W*x*(d-x)*(x*(d-x) + d*d - 2*(c*c + e*e) - 2*(e*e*x + c*c*(d-x))/d);
   }
   else // right cantilever
   {
      x = x - c; // measure X positive from left support
      y_ei = -W*(x-d)*(2*d*(c*c+2*e*e) + 6*e*e*(x-d) - (x-d)*(x-d)*(4*e + d - x) - d*d*d);
   }

   return y_ei / (24.0*L*EI);
}

#if defined _DEBUG
bool BeamWithUnequalOverhangsUniformLoad::AssertValid() const
{
   return true;
}

void BeamWithUnequalOverhangsUniformLoad::Dump(WBFL::Debug::LogContext& os) const
{
   os << "Dump for BeamWithUnequalOverhangsUniformLoad" << WBFL::Debug::endl;
}
#endif // _DEBUG

#if defined _UNITTEST


bool BeamWithUnequalOverhangsUniformLoad::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("BeamWithUnequalOverhangsUniformLoad");

   // answers calculated by MathCad sheet
   Float64 L = 100;
   Float64 a = 15;
   Float64 c = 15;
   BeamWithUnequalOverhangsUniformLoad beam1(L,a,c,5,1);

   Float64 t = 0;
   TRY_TESTME(0==beam1.ComputeMoment(t).Right());
   TRY_TESTME(0==beam1.ComputeShear(t).Right());
   TRY_TESTME(IsEqual(744921.875, beam1.ComputeDeflection(t)));

   t = a/3;
   TRY_TESTME(62.5==beam1.ComputeMoment(t).Right());
   TRY_TESTME(25==beam1.ComputeShear(t).Right());
   TRY_TESTME(IsEqual(500000., beam1.ComputeDeflection(t)));
   
   t = a;
   TRY_TESTME(562.5==beam1.ComputeMoment(t).Right());
   TRY_TESTME(  75==beam1.ComputeShear(t).Left());
   TRY_TESTME(-175==beam1.ComputeShear(t).Right());
   TRY_TESTME(IsEqual(0., beam1.ComputeDeflection(t)));

   t = 30;
   TRY_TESTME(-1500.==beam1.ComputeMoment(t).Right());
   TRY_TESTME(-100==beam1.ComputeShear(t).Right());
   TRY_TESTME(IsEqual(751953.125, beam1.ComputeDeflection(t)));

   t = L/2;
   TRY_TESTME(-2500.==beam1.ComputeMoment(t).Right());
   TRY_TESTME(0==beam1.ComputeShear(t).Right());
   TRY_TESTME(IsEqual(1.21862e6, beam1.ComputeDeflection(t), 0.1e6));

   t = L - a;
   TRY_TESTME(562.5==beam1.ComputeMoment(t).Right());
   TRY_TESTME(175==beam1.ComputeShear(t).Left());
   TRY_TESTME(-75==beam1.ComputeShear(t).Right());
   TRY_TESTME(IsEqual(0., beam1.ComputeDeflection(t)));

   t = L - c/3;
   TRY_TESTME(62.5==beam1.ComputeMoment(t).Right());
   TRY_TESTME(-25.==beam1.ComputeShear(t).Right());
   TRY_TESTME(IsEqual(500000., beam1.ComputeDeflection(t)));

   t = L;
   TRY_TESTME(0==beam1.ComputeMoment(t).Right());
   TRY_TESTME(0==beam1.ComputeShear(t).Right());
   TRY_TESTME(IsEqual(744921.875, beam1.ComputeDeflection(t)));

   // beam based on "Deflection of Beams with Unqeual Overhangs" in Supporting Documents
   BeamWithUnequalOverhangsUniformLoad beam2(223*12, 26*12, 26*12, -0.0865, 4009.*1524912.);

   TRY_TESTME(IsEqual(beam2.ComputeRotation(0), -0.00431576));
   TRY_TESTME(IsEqual(beam2.ComputeRotation(223*12), 0.00431576));

   // Left support, 26ft = 312in
   TRY_TESTME(beam2.ComputeMoment(312) == WBFL::System::SectionValue(-4210.1280));
   TRY_TESTME(beam2.ComputeShear(312) == WBFL::System::SectionValue(-26.98799,88.74899));
   TRY_TESTME(IsEqual(beam2.ComputeRotation(312), -0.004387));
   TRY_TESTME(IsEqual(beam2.ComputeDeflection(312), 0.00));

   // Mid-span, 115.5ft = 1338in
   TRY_TESTME(beam2.ComputeMoment(1338) == WBFL::System::SectionValue(41318.109));
   TRY_TESTME(beam2.ComputeShear(1338) == WBFL::System::SectionValue(0.0, 0.0));
   TRY_TESTME(IsEqual(beam2.ComputeRotation(1338), 0.0));
   TRY_TESTME(IsEqual(beam2.ComputeDeflection(1338), -2.90403));

   // Right support, 197ft = 2364in
   TRY_TESTME(beam2.ComputeMoment(2364) == WBFL::System::SectionValue(-4210.1280));
   TRY_TESTME(beam2.ComputeShear(2364) == WBFL::System::SectionValue(-88.74899, 26.98799));
   TRY_TESTME(IsEqual(beam2.ComputeRotation(2364), 0.004387));
   TRY_TESTME(IsEqual(beam2.ComputeDeflection(2364), 0.00));

   TESTME_EPILOG("BeamWithUnequalOverhangsUniformLoad");
}
#endif // _UNITTEST
