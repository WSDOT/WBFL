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
#include <Roark\BeamWithEqualOverhangsUniformLoad.h>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   rkBeamWithEqualOverhangsUniformLoad
****************************************************************************/

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
rkBeamWithEqualOverhangsUniformLoad::  rkBeamWithEqualOverhangsUniformLoad(Float64 length,Float64 overhang, Float64 w,
                                                                            Float64 e,Float64 i):
m_EI(e*i),
m_L(length),
m_Overhang(overhang),
m_W(w)
{
   PRECONDITION(m_EI>0.0);
   PRECONDITION(m_L>0.0);
   PRECONDITION(m_Overhang>=0.0);
   PRECONDITION(m_W>0.0);
   PRECONDITION(m_L>2*m_Overhang);
}

rkBeamWithEqualOverhangsUniformLoad::rkBeamWithEqualOverhangsUniformLoad(const rkBeamWithEqualOverhangsUniformLoad& rOther)
{
   MakeCopy(rOther);
}

rkBeamWithEqualOverhangsUniformLoad::~rkBeamWithEqualOverhangsUniformLoad()
{
}

//======================== OPERATORS  =======================================
rkBeamWithEqualOverhangsUniformLoad& rkBeamWithEqualOverhangsUniformLoad::operator= (const rkBeamWithEqualOverhangsUniformLoad& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================
Float64 rkBeamWithEqualOverhangsUniformLoad::GetL() const
{
   return m_L;
}

Float64 rkBeamWithEqualOverhangsUniformLoad::GetEI() const
{
   return m_EI;
}

Float64 rkBeamWithEqualOverhangsUniformLoad::GetOverhang() const
{
   return m_Overhang;
}

Float64 rkBeamWithEqualOverhangsUniformLoad::GetW() const
{
   return m_W;
}

void rkBeamWithEqualOverhangsUniformLoad::GetReactions(Float64 *pRa,Float64* pRb) const
{
   *pRa = -m_W*m_L/2;
   *pRb = *pRa;
}

void rkBeamWithEqualOverhangsUniformLoad::GetMoments(Float64* pMa,Float64* pMb) const
{
   *pMa = 0;
   *pMb = 0;
}

void rkBeamWithEqualOverhangsUniformLoad::GetRotations(Float64* pra,Float64* prb) const
{
   *pra=  ComputeRotation(m_Overhang);
   *prb = ComputeRotation(m_L-m_Overhang);
}

void rkBeamWithEqualOverhangsUniformLoad::GetDeflections(Float64* pYa,Float64* pYb) const
{
   *pYa = 0;
   *pYb = 0;
}

sysSectionValue rkBeamWithEqualOverhangsUniformLoad::ComputeShear(Float64 x) const
{
   PRECONDITION(x>=0.0 && x<=m_L);
   Float64 a = m_Overhang;
   Float64 L = m_L;
   Float64 w = m_W;

   sysSectionValue v;
   if (x<m_Overhang)
   {
      v =  w*x;
   }
   else if (x==m_Overhang)  // right support
   {
      v.Left() =  w*x;
      Float64 xn = x-a;
      v.Right() =  -w*(L-2*a)/2 + w*xn;
   }
   else if (x>L-a)
   {
      Float64 xn = x - L + a;
      v = -w*a + w*xn;
   }
   else if (x==L-a)  // left support
   {
      Float64 xn = x-a;
      v.Left() =  -w*(L-2*a)/2 + w*xn;
      xn = x - L + a;
      v.Right() = -w*a + w*xn;
   }
   else
   {
      Float64 xn = x-a;
      v =  -w*(L-2*a)/2 + w*xn;
   }
   return v;
}

sysSectionValue rkBeamWithEqualOverhangsUniformLoad::ComputeMoment(Float64 x) const
{
   PRECONDITION(x>=0.0 && x<=m_L);
   Float64 a = m_Overhang;
   Float64 L = m_L;
   Float64 w = m_W;

   Float64 m;
   if (x<m_Overhang)
   {
      m =  -w*x*x/2;
   }
   else if (x>L-a)
   {
      m = -w*(L-x)*(L-x)/2.;
   }
   else
   {
      m =  w*(-x*x + x*L - L*a)/2;
   }

   return m;
}

Float64 rkBeamWithEqualOverhangsUniformLoad::ComputeRotation(Float64 x) const
{
   PRECONDITION(x>=0.0 && x<=m_L);
   Float64 a = m_Overhang;
   Float64 L = m_L-2*a;
   Float64 w = m_W;

   Float64 theta_ei;
   if (x<m_Overhang)
   {
      theta_ei = -w*x*x*x/6.
                + w*a*a*a/6.
                + w*a*a*L/4.
                - w*L*L*L/24.;
   }
   else if (x>L+a)
   {
      Float64 xn = x - L - a;
      theta_ei =  -w*xn*xn*xn/6.
                 + w*a*xn*xn/2.
                 - w*a*a*xn/2.
                 + w*L*L*L/24.
                 - w*a*a*L/4.;
   }
   else
   {
      Float64 xn = x-a;
      theta_ei =  -w*xn*xn*xn/6.
                 + w*L*xn*xn/4.
                 - w*a*a*xn/2.
                 + w*a*a*L/4.
                 - w*L*L*L/24;
   }

   return theta_ei / m_EI;
}

Float64 rkBeamWithEqualOverhangsUniformLoad::ComputeDeflection(Float64 x) const
{
   PRECONDITION(x>=0.0 && x<=m_L);
   Float64 a = m_Overhang;
   Float64 L = m_L-2*a;
   Float64 w = m_W;

   Float64 y_ei;
   if (x<m_Overhang)
   {
      y_ei = -w*x*x*x*x/24.
            +(w*a*a*L/4. - w*L*L*L/24.+ w*a*a*a/6. ) * x
            - w*a*a*a*a/8.
            - w*a*a*a*L/4
            + w*a*L*L*L/24;
   }
   else if (x>L+a)
   {
      Float64 xn = x - L - a;
      y_ei = -w*xn*xn*xn*xn/24.
            + w*a*xn*xn*xn/6.
            - w*a*a*xn*xn/4.
            +(w*L*L*L/24 - w*a*a*L/4)*xn;
   }
   else
   {
      Float64 xn = x-a;
      y_ei = -w*xn*xn*xn*xn/24.
            + w*L*xn*xn*xn/12
            - w*a*a*xn*xn/4
            +(w*a*a*L/4 - w*L*L*L/24)*xn;
   }

   return y_ei / m_EI;}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void rkBeamWithEqualOverhangsUniformLoad::MakeCopy(const rkBeamWithEqualOverhangsUniformLoad& rOther)
{
   m_EI       = rOther.m_EI;
   m_L        = rOther.m_L;
   m_Overhang = rOther.m_Overhang;
   m_W        = rOther.m_W;
}

void rkBeamWithEqualOverhangsUniformLoad::MakeAssignment(const rkBeamWithEqualOverhangsUniformLoad& rOther)
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
bool rkBeamWithEqualOverhangsUniformLoad::AssertValid() const
{
   return true;
}

void rkBeamWithEqualOverhangsUniformLoad::Dump(dbgDumpContext& os) const
{
   os << "Dump for rkBeamWithEqualOverhangsUniformLoad" << endl;
}
#endif // _DEBUG

#if defined _UNITTEST


bool rkBeamWithEqualOverhangsUniformLoad::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("rkBeamWithEqualOverhangsUniformLoad");

   // answers calculated by MathCad sheet
   rkBeamWithEqualOverhangsUniformLoad beam1(100,15,5,2,.5);
   Float64 t = 5;
   TRY_TESTME(-62.5==beam1.ComputeMoment(t).Right());
   TRY_TESTME(25==beam1.ComputeShear(t).Right());
   TRY_TESTME(IsEqual(500000., beam1.ComputeDeflection(t)))
   TRY_TESTME(IsEqual(-49062.5, beam1.ComputeRotation(t)))
   t = 15;
   TRY_TESTME(-562.5==beam1.ComputeMoment(t).Right());
   TRY_TESTME(-175==beam1.ComputeShear(t).Right());
   TRY_TESTME(IsEqual(0., beam1.ComputeDeflection(t)))
   TRY_TESTME(IsEqual(-51770.833333, beam1.ComputeRotation(t)))
   t = 30;
   TRY_TESTME(1500.==beam1.ComputeMoment(t).Right());
   TRY_TESTME(-100==beam1.ComputeShear(t).Right());
   TRY_TESTME(IsEqual(-751953.125, beam1.ComputeDeflection(t)))
   TRY_TESTME(IsEqual(-43333.333333, beam1.ComputeRotation(t)))
   t = 50;
   TRY_TESTME(2500.==beam1.ComputeMoment(t).Right());
   TRY_TESTME(0==beam1.ComputeShear(t).Right());
   TRY_TESTME(IsEqual(-1.21862e6, beam1.ComputeDeflection(t), 0.1e6 ))
   TRY_TESTME(IsEqual(0., beam1.ComputeRotation(t)))
   t = 85;
   TRY_TESTME(-562.5==beam1.ComputeMoment(t).Right());
   TRY_TESTME(175==beam1.ComputeShear(t).Left());
   TRY_TESTME(-75==beam1.ComputeShear(t).Right());
   TRY_TESTME(IsEqual(0., beam1.ComputeDeflection(t)))
   TRY_TESTME(IsEqual(51770.833333, beam1.ComputeRotation(t)))
   t = 99;
   TRY_TESTME(-2.5==beam1.ComputeMoment(t).Right());
   TRY_TESTME(-5.==beam1.ComputeShear(t).Right());
   TRY_TESTME(IsEqual(695963.333333, beam1.ComputeDeflection(t)))
   TRY_TESTME(IsEqual(48959.166667, beam1.ComputeRotation(t)))

   TESTME_EPILOG("BeamWithEqualOverhangsUniformLoad");
}
#endif // _UNITTEST
