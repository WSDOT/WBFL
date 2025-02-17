///////////////////////////////////////////////////////////////////////
// Roark - Simple span beam formula, patterned after Roark's formulas
//         for Stress and Strain
// Copyright � 1999-2025  Washington State Department of Transportation
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

std::shared_ptr<RoarkBeam> BeamWithUnequalOverhangsUniformLoad::CreateClone() const
{
   return std::make_shared<BeamWithUnequalOverhangsUniformLoad>(GetL(), m_LeftOverhang, m_RightOverhang, m_W, GetEI());
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

std::pair<Float64, Float64> BeamWithUnequalOverhangsUniformLoad::GetReactions() const
{
   Float64 L = GetL();
   Float64 c = m_LeftOverhang;
   Float64 e = m_RightOverhang;
   Float64 d = L - c - e;
   Float64 W = m_W * L;

   Float64 Ra = -W*(c+d-e)/(2*d);
   Float64 Rb = -W*(d+e-c)/(2*d);
   return std::make_pair(Ra, Rb);
}

std::pair<Float64, Float64> BeamWithUnequalOverhangsUniformLoad::GetMoments() const
{
   Float64 L = GetL();
   Float64 c = m_LeftOverhang;
   Float64 e = m_RightOverhang;
   Float64 d = L - c - e;
   Float64 W = m_W * L;

   Float64 Ma = W*c*c/(2*L);
   Float64 Mb = W*e*e/(2*L);
   return std::make_pair(Ma, Mb);
}

std::pair<Float64, Float64> BeamWithUnequalOverhangsUniformLoad::GetRotations() const
{
   Float64 L = GetL();
   return std::make_pair(ComputeRotation(m_LeftOverhang), ComputeRotation(L-m_RightOverhang));
}

std::pair<Float64, Float64> BeamWithUnequalOverhangsUniformLoad::GetDeflections() const
{
   return std::make_pair(0.0, 0.0);
}

WBFL::System::SectionValue BeamWithUnequalOverhangsUniformLoad::ComputeShear(Float64 x) const
{
   Float64 L = GetL();
   PRECONDITION(0.0 <= x && x <= L);
   Float64 c = m_LeftOverhang;
   Float64 e = m_RightOverhang;
   Float64 d = L - c - e;
   Float64 W = m_W*L;

   auto [Rl,Rr] = GetReactions();

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

   auto [Rl,Rr] = GetReactions();

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
   auto [L,EI] = GetProperties();

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
   auto [L,EI] = GetProperties();

   PRECONDITION(0.0 <= x && x <= L);
   Float64 c = m_LeftOverhang;
   Float64 e = m_RightOverhang;
   Float64 d = L - c - e;
   Float64 W = m_W*L;

   auto [Rl,Rr] = GetReactions();

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
