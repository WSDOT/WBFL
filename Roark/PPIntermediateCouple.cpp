///////////////////////////////////////////////////////////////////////
// Roark - Simple span beam formula, patterned after Roark's formulas
//         for Stress and Strain
// Copyright © 1999-2024  Washington State Department of Transportation
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


using namespace WBFL::Beams;

PPIntermediateCouple::PPIntermediateCouple(Float64 Mo,Float64 La,Float64 l,Float64 ei) :
RoarkBeam(l,ei)
{
   M = Mo;
   a = La;
}

std::shared_ptr<RoarkBeam> PPIntermediateCouple::CreateClone() const
{
   return std::make_shared<PPIntermediateCouple>(M,a,GetL(),GetEI());
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

std::pair<Float64, Float64> PPIntermediateCouple::GetReactions() const
{
   Float64 L = GetL();
   Float64 Ra = M/L;
   Float64 Rb = -M/L;
   return std::make_pair(Ra, Rb);
}

std::pair<Float64, Float64>PPIntermediateCouple::GetMoments() const
{
   return std::make_pair(0.0, 0.0);
}

std::pair<Float64, Float64>PPIntermediateCouple::GetRotations() const
{
   Float64 L = GetL();
   return std::make_pair(ComputeRotation(0.0), ComputeRotation(L));
}

std::pair<Float64, Float64> PPIntermediateCouple::GetDeflections() const
{
   Float64 L = GetL();
   return std::make_pair(ComputeDeflection(0.0), ComputeDeflection(L));
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

   auto [L,EI] = GetProperties();

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

   auto [L,EI] = GetProperties();

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
