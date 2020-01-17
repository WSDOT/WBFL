///////////////////////////////////////////////////////////////////////
// Roark - Simple span beam forumla, patterned after Roark's formulas
//         for Stress and Strain
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

#include <Roark\RoarkLib.h>
#include <Roark\BeamWithUnequalOverhangsUniformLoad.h>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   rkBeamWithUnequalOverhangsUniformLoad
   Based on PCI Design Manual, Design Aid 11.1.7
****************************************************************************/

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
rkBeamWithUnequalOverhangsUniformLoad::rkBeamWithUnequalOverhangsUniformLoad(Float64 length,Float64 a,Float64 b, Float64 w,
                                                                            Float64 e,Float64 i):
rkRoarkBeam(length,e,i),
m_EI(e*i),
m_L(length),
m_LeftOverhang(a),
m_RightOverhang(b),
m_W(w)
{
   PRECONDITION(m_EI>0.0);
   PRECONDITION(m_L>0.0);
   PRECONDITION(m_LeftOverhang>=0.0);
   PRECONDITION(m_RightOverhang>=0.0);
   PRECONDITION(m_LeftOverhang + m_RightOverhang < m_L);
}

rkBeamWithUnequalOverhangsUniformLoad::rkBeamWithUnequalOverhangsUniformLoad(const rkBeamWithUnequalOverhangsUniformLoad& rOther) :
rkRoarkBeam(rOther)
{
   MakeCopy(rOther);
}

rkBeamWithUnequalOverhangsUniformLoad::~rkBeamWithUnequalOverhangsUniformLoad()
{
}

rkRoarkBeam* rkBeamWithUnequalOverhangsUniformLoad::CreateClone() const
{
   return new rkBeamWithUnequalOverhangsUniformLoad(*this);
}

//======================== OPERATORS  =======================================
rkBeamWithUnequalOverhangsUniformLoad& rkBeamWithUnequalOverhangsUniformLoad::operator= (const rkBeamWithUnequalOverhangsUniformLoad& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================
Float64 rkBeamWithUnequalOverhangsUniformLoad::GetLeftOverhang() const
{
   return m_LeftOverhang;
}

Float64 rkBeamWithUnequalOverhangsUniformLoad::GetRightOverhang() const
{
   return m_RightOverhang;
}

Float64 rkBeamWithUnequalOverhangsUniformLoad::GetW() const
{
   return m_W;
}

void rkBeamWithUnequalOverhangsUniformLoad::GetReactions(Float64 *pRa,Float64* pRb) const
{
   Float64 c = m_LeftOverhang;
   Float64 e = m_RightOverhang;
   Float64 d = m_L - c - e;
   Float64 W = m_W * m_L;

   (*pRa) = -W*(c+d-e)/(2*d);
   (*pRb) = -W*(d+e-c)/(2*d);
}

void rkBeamWithUnequalOverhangsUniformLoad::GetMoments(Float64* pMa,Float64* pMb) const
{
   Float64 c = m_LeftOverhang;
   Float64 e = m_RightOverhang;
   Float64 d = m_L - c - e;
   Float64 W = m_W * m_L;

   (*pMa) = W*c*c/(2*m_L);
   (*pMb) = W*e*e/(2*m_L);
}

void rkBeamWithUnequalOverhangsUniformLoad::GetRotations(Float64* pra,Float64* prb) const
{
   *pra=  ComputeRotation(m_LeftOverhang);
   *prb = ComputeRotation(m_L-m_RightOverhang);
}

void rkBeamWithUnequalOverhangsUniformLoad::GetDeflections(Float64* pYa,Float64* pYb) const
{
   *pYa = 0;
   *pYb = 0;
}

sysSectionValue rkBeamWithUnequalOverhangsUniformLoad::ComputeShear(Float64 x) const
{

   PRECONDITION(x>=0.0 && x<=m_L);
   Float64 c = m_LeftOverhang;
   Float64 e = m_RightOverhang;
   Float64 d = m_L - c - e;
   Float64 W = m_W*m_L;

   Float64 Rl, Rr;
   GetReactions(&Rl,&Rr);

   sysSectionValue v;
   if ( x < c )
   {
      x = c - x; // measure X positive left of the left support
      v = W*(c-x)/m_L;
   }
   else if ( x == c )  // left support
   {
      v.Left()  = W*c/m_L;
      v.Right() = Rl + W*c/m_L;
   }
   else if (c < x && x < c+d) // between supports
   {
      x = x - c; // measure X positive from left support
      v = Rl + W*(c+x)/m_L;
   }
   else if ( x == c+d )  // right support
   {
      v.Left() = Rl + W*(c+d)/m_L;
      v.Right() = -W*e/m_L;
   }
   else // right cantilever
   {
      x = x - c; // measure X positive from left support
      v = -W*(d+e-x)/m_L;
   }
   return v;
}

sysSectionValue rkBeamWithUnequalOverhangsUniformLoad::ComputeMoment(Float64 x) const
{
   PRECONDITION(x>=0.0 && x<=m_L);
   Float64 c = m_LeftOverhang;
   Float64 e = m_RightOverhang;
   Float64 d = m_L - c - e;
   Float64 W = m_W*m_L;

   Float64 Rl, Rr;
   GetReactions(&Rl,&Rr);

   Float64 m;
   if ( x < c )
   {
      x = c - x; // measure X positive left of the left support
      m = W*(c-x)*(c-x)/(2*m_L);
   }
   else if (c <= x && x <= c+d) // between supports
   {
      x = x - c; // measure X positive from left support
      m = W*(c+x)*(c+x)/(2*m_L) + Rl*x;
   }
   else // right cantilever
   {
      x = x - c; // measure X positive from left support
      m = W*(e+d-x)*(e+d-x)/(2*m_L);
   }

   return m;
}

Float64 rkBeamWithUnequalOverhangsUniformLoad::ComputeRotation(Float64 x) const
{
#pragma Reminder("IMPLEMENT - Not computing rotations")
   return 0;
}

Float64 rkBeamWithUnequalOverhangsUniformLoad::ComputeDeflection(Float64 x) const
{
   PRECONDITION(x>=0.0 && x<=m_L);
   Float64 c = m_LeftOverhang;
   Float64 e = m_RightOverhang;
   Float64 d = m_L - c - e;
   Float64 W = m_W*m_L;

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

   return y_ei / (24.0*m_L*m_EI);
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void rkBeamWithUnequalOverhangsUniformLoad::MakeCopy(const rkBeamWithUnequalOverhangsUniformLoad& rOther)
{
   m_EI            = rOther.m_EI;
   m_L             = rOther.m_L;
   m_LeftOverhang  = rOther.m_LeftOverhang;
   m_RightOverhang = rOther.m_RightOverhang;
   m_W             = rOther.m_W;
}

void rkBeamWithUnequalOverhangsUniformLoad::MakeAssignment(const rkBeamWithUnequalOverhangsUniformLoad& rOther)
{
   MakeCopy( rOther );
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

//======================== DEBUG      =======================================
#if defined _DEBUG
bool rkBeamWithUnequalOverhangsUniformLoad::AssertValid() const
{
   return true;
}

void rkBeamWithUnequalOverhangsUniformLoad::Dump(dbgDumpContext& os) const
{
   os << "Dump for rkBeamWithUnequalOverhangsUniformLoad" << endl;
}
#endif // _DEBUG

#if defined _UNITTEST


bool rkBeamWithUnequalOverhangsUniformLoad::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("rkBeamWithUnequalOverhangsUniformLoad");

   // answers calculated by MathCad sheet
   Float64 L = 100;
   Float64 a = 15;
   Float64 c = 15;
   rkBeamWithUnequalOverhangsUniformLoad beam1(L,a,c,5,2,.5);
   Float64 t = 0;
   TRY_TESTME(0==beam1.ComputeMoment(t).Right());
   TRY_TESTME(0==beam1.ComputeShear(t).Right());
   TRY_TESTME(IsEqual(744921.875, beam1.ComputeDeflection(t)))
//   TRY_TESTME(IsEqual(-49062.5, beam1.ComputeRotation(t)))
   t = a/3;
   TRY_TESTME(62.5==beam1.ComputeMoment(t).Right());
   TRY_TESTME(25==beam1.ComputeShear(t).Right());
   TRY_TESTME(IsEqual(500000., beam1.ComputeDeflection(t)))
//   TRY_TESTME(IsEqual(-49062.5, beam1.ComputeRotation(t)))
   t = a;
   TRY_TESTME(562.5==beam1.ComputeMoment(t).Right());
   TRY_TESTME(  75==beam1.ComputeShear(t).Left());
   TRY_TESTME(-175==beam1.ComputeShear(t).Right());
   TRY_TESTME(IsEqual(0., beam1.ComputeDeflection(t)))
//   TRY_TESTME(IsEqual(-51770.833333, beam1.ComputeRotation(t)))
   t = 30;
   TRY_TESTME(-1500.==beam1.ComputeMoment(t).Right());
   TRY_TESTME(-100==beam1.ComputeShear(t).Right());
   TRY_TESTME(IsEqual(751953.125, beam1.ComputeDeflection(t)))
//   TRY_TESTME(IsEqual(-43333.333333, beam1.ComputeRotation(t)))
   t = L/2;
   TRY_TESTME(-2500.==beam1.ComputeMoment(t).Right());
   TRY_TESTME(0==beam1.ComputeShear(t).Right());
   TRY_TESTME(IsEqual(1.21862e6, beam1.ComputeDeflection(t), 0.1e6 ))
//   TRY_TESTME(IsEqual(0., beam1.ComputeRotation(t)))
   t = L - a;
   TRY_TESTME(562.5==beam1.ComputeMoment(t).Right());
   TRY_TESTME(175==beam1.ComputeShear(t).Left());
   TRY_TESTME(-75==beam1.ComputeShear(t).Right());
   TRY_TESTME(IsEqual(0., beam1.ComputeDeflection(t)))
//   TRY_TESTME(IsEqual(51770.833333, beam1.ComputeRotation(t)))
   t = L - c/3;
   TRY_TESTME(62.5==beam1.ComputeMoment(t).Right());
   TRY_TESTME(-25.==beam1.ComputeShear(t).Right());
   TRY_TESTME(IsEqual(500000., beam1.ComputeDeflection(t)))
//   TRY_TESTME(IsEqual(49062.5, beam1.ComputeRotation(t)))
   t = L;
   TRY_TESTME(0==beam1.ComputeMoment(t).Right());
   TRY_TESTME(0==beam1.ComputeShear(t).Right());
   TRY_TESTME(IsEqual(744921.875, beam1.ComputeDeflection(t)))
//   TRY_TESTME(IsEqual(-49062.5, beam1.ComputeRotation(t)))

   TESTME_EPILOG("BeamWithEqualOverhangsUniformLoad");
}
#endif // _UNITTEST
