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
#include <Roark/BeamWithEqualOverhangsUniformLoad.h>

using namespace WBFL::Beams;

BeamWithEqualOverhangsUniformLoad::BeamWithEqualOverhangsUniformLoad(Float64 length,Float64 overhang, Float64 w,Float64 ei):
RoarkBeam(length,ei),
m_Overhang(overhang),
m_W(w)
{
   PRECONDITION(0.0 <= m_Overhang);
   PRECONDITION(0.0 <= m_W);
   PRECONDITION(2*m_Overhang < length);
}

BeamWithEqualOverhangsUniformLoad::~BeamWithEqualOverhangsUniformLoad()
{
}

std::shared_ptr<RoarkBeam> BeamWithEqualOverhangsUniformLoad::CreateClone() const
{
   return std::make_shared<BeamWithEqualOverhangsUniformLoad>(GetL(), m_Overhang, m_W, GetEI());
}

Float64 BeamWithEqualOverhangsUniformLoad::GetOverhang() const
{
   return m_Overhang;
}

Float64 BeamWithEqualOverhangsUniformLoad::GetW() const
{
   return m_W;
}

std::pair<Float64,Float64> BeamWithEqualOverhangsUniformLoad::GetReactions() const
{
   Float64 L = GetL();
   Float64 R = -m_W * L / 2;
   return std::make_pair(R, R);
}

std::pair<Float64, Float64> BeamWithEqualOverhangsUniformLoad::GetMoments() const
{
   return std::make_pair(0.0, 0.0);
}

std::pair<Float64, Float64> BeamWithEqualOverhangsUniformLoad::GetRotations() const
{
   Float64 L = GetL();
   return std::make_pair(ComputeRotation(m_Overhang), ComputeRotation(L-m_Overhang));
}

std::pair<Float64, Float64> BeamWithEqualOverhangsUniformLoad::GetDeflections() const
{
   return std::make_pair(0.0, 0.0);
}

WBFL::System::SectionValue BeamWithEqualOverhangsUniformLoad::ComputeShear(Float64 x) const
{
   Float64 L = GetL();
   PRECONDITION(0.0 <= x && x <= L);
   Float64 a = m_Overhang;
   Float64 w = m_W;

   WBFL::System::SectionValue v;
   if (x < m_Overhang)
   {
      v =  w*x;
   }
   else if (x == m_Overhang)  // right support
   {
      v.Left() =  w*x;
      Float64 xn = x-a;
      v.Right() =  -w*(L-2*a)/2 + w*xn;
   }
   else if ((L-a) < x)
   {
      Float64 xn = x - L + a;
      v = -w*a + w*xn;
   }
   else if (x == (L-a))  // left support
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

WBFL::System::SectionValue BeamWithEqualOverhangsUniformLoad::ComputeMoment(Float64 x) const
{
   Float64 L = GetL();

   PRECONDITION(0.0 <= x && x <= L);

   Float64 a = m_Overhang;
   Float64 w = m_W;

   Float64 m;
   if (x < m_Overhang)
   {
      m =  -w*x*x/2;
   }
   else if ((L-a) < x)
   {
      m = -w*(L-x)*(L-x)/2.;
   }
   else
   {
      m =  w*(-x*x + x*L - L*a)/2;
   }

   return m;
}

Float64 BeamWithEqualOverhangsUniformLoad::ComputeRotation(Float64 x) const
{
   Float64 L, EI;
   std::tie(L,EI) = GetProperties();

   PRECONDITION(0.0 <= x && x <= L);

   Float64 a = m_Overhang;
   Float64 l = L - 2 * a;
   Float64 w = m_W;

   Float64 theta_ei;
   if (x<m_Overhang)
   {
      theta_ei = -w*x*x*x/6.
                + w*a*a*a/6.
                + w*a*a*l/4.
                - w*l*l*l/24.;
   }
   else if ((l+a) < x)
   {
      Float64 xn = x - l - a;
      theta_ei =  -w*xn*xn*xn/6.
                 + w*a*xn*xn/2.
                 - w*a*a*xn/2.
                 + w*l*l*l/24.
                 - w*a*a*l/4.;
   }
   else
   {
      Float64 xn = x-a;
      theta_ei =  -w*xn*xn*xn/6.
                 + w*l*xn*xn/4.
                 - w*a*a*xn/2.
                 + w*a*a*l/4.
                 - w*l*l*l/24;
   }

   return theta_ei / EI;
}

Float64 BeamWithEqualOverhangsUniformLoad::ComputeDeflection(Float64 x) const
{
   Float64 L, EI;
   std::tie(L,EI) = GetProperties();

   PRECONDITION(0.0 <= x && x <= L);

   Float64 a = m_Overhang;
   Float64 l = L-2*a;
   Float64 w = m_W;

   Float64 y_ei;
   if (x < m_Overhang)
   {
      y_ei = -w*x*x*x*x/24.
            +(w*a*a*l/4. - w*l*l*l/24.+ w*a*a*a/6. ) * x
            - w*a*a*a*a/8.
            - w*a*a*a*l/4
            + w*a*l*l*l/24;
   }
   else if ((l+a) < x)
   {
      Float64 xn = x - l - a;
      y_ei = -w*xn*xn*xn*xn/24.
            + w*a*xn*xn*xn/6.
            - w*a*a*xn*xn/4.
            +(w*l*l*l/24 - w*a*a*l/4)*xn;
   }
   else
   {
      Float64 xn = x-a;
      y_ei = -w*xn*xn*xn*xn/24.
            + w*l*xn*xn*xn/12
            - w*a*a*xn*xn/4
            +(w*a*a*l/4 - w*l*l*l/24)*xn;
   }

   return y_ei / EI;
}

#if defined _DEBUG
bool BeamWithEqualOverhangsUniformLoad::AssertValid() const
{
   return true;
}

void BeamWithEqualOverhangsUniformLoad::Dump(WBFL::Debug::LogContext& os) const
{
   os << "Dump for BeamWithEqualOverhangsUniformLoad" << WBFL::Debug::endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool BeamWithEqualOverhangsUniformLoad::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("BeamWithEqualOverhangsUniformLoad");

   // answers calculated by MathCad sheet
   BeamWithEqualOverhangsUniformLoad beam1(100,15,5,1);
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
