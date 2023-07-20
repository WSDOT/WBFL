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
#include <Roark/PPIntermediateLoad.h>

using namespace WBFL::Beams;

PPIntermediateLoad::PPIntermediateLoad(Float64 w,Float64 La,Float64 l,Float64 ei) :
RoarkBeam(l,ei)
{
   a = La;
   b = l - a;
   W = w;
}

std::shared_ptr<RoarkBeam> PPIntermediateLoad::CreateClone() const
{
   return std::make_shared<PPIntermediateLoad>(W,a,GetL(),GetEI());
}

void PPIntermediateLoad::SetLa(Float64 la)
{
   a = la;
}

Float64 PPIntermediateLoad::GetLa() const
{
   return a;
}

Float64 PPIntermediateLoad::GetLb() const
{
   return b;
}

void PPIntermediateLoad::SetW(Float64 w)
{
   W = w;
}

Float64 PPIntermediateLoad::GetW() const
{
   return W;
}

std::pair<Float64, Float64> PPIntermediateLoad::GetReactions() const
{
   Float64 L = GetL();
   Float64 Ra = -W*b/L;
   Float64 Rb = -W*a/L;
   return std::make_pair(Ra, Rb);
}

std::pair<Float64, Float64> PPIntermediateLoad::GetMoments() const
{
   return std::make_pair(0.0, 0.0);
}

std::pair<Float64, Float64> PPIntermediateLoad::GetRotations() const
{
   Float64 L = GetL();
   return std::make_pair(ComputeRotation(0),ComputeRotation(L));
}

std::pair<Float64, Float64> PPIntermediateLoad::GetDeflections() const
{
   Float64 L = GetL();
   return std::make_pair(ComputeDeflection(0),ComputeDeflection(L));
}

WBFL::System::SectionValue PPIntermediateLoad::ComputeShear(Float64 x) const
{
   WBFL::System::SectionValue V;
   Float64 L = GetL();

   // Compute shear left and right of W
   Float64 Ra, Rb;
   std::tie(Ra,Rb) = GetReactions();
   Float64 left  =  Ra;
   Float64 right = -Rb;

   if ( IsZero(a) && IsZero(x) )
   {
      // Special case when load is directly over left support
      // and we want the shear at the left support
      V.Left()  = left;
      V.Right() = 0.0;
   }
   else if ( IsZero(a-L) && IsZero(x-L) )
   {
      // Special case when load is directly over right support
      // and we want the shear at the left support
      V.Left()  = 0.0;
      V.Right() = right;
   }
   else
   {
      if ( IsZero(x-a) )
      {
         V.Left()  = left;
         V.Right() = right;
      }
      else if (x < a)
      {
         V = left;
      }
      else
      {
         V = right;
      } 

      // If we want the shear at one end of the beam of the other.
      // We need to zero out the exterior face shear so we get the correct
      // stepping in the shear diagram.
      if ( IsZero(x) )
         V.Left() = 0.0;

      if ( IsZero(x-L) )
         V.Right() = 0.0;
   }

   return V;
}

WBFL::System::SectionValue PPIntermediateLoad::ComputeMoment(Float64 x) const
{
   Float64 L = GetL();

   Float64 M = 0;

   if (x < a)
      M = -W*b*x/L;
   else
      M = -W*b*x/L + W*(x-a);

   return M;
}

Float64 PPIntermediateLoad::ComputeRotation(Float64 x) const
{
   Float64 r = 0;

   Float64 L, EI;
   std::tie(L,EI) = GetProperties();

   if ( x < a )
   {
      r = W*b*(L*L - b*b - x*x)/(6*EI*L) - W*b*x*x/(3*EI*L);
   }
   else
   {
      r = W*a*(L-x)*(2*L - 2*x)/(6*EI*L) - W*a*(L*L - a*a - (L-x)*(L-x))/(6*EI*L);
   }

   return r;
}

Float64 PPIntermediateLoad::ComputeDeflection(Float64 x) const
{
   Float64 y = 0;

   Float64 L, EI;
   std::tie(L,EI) = GetProperties();

   if (x < a)
   {
      y = W*b*x*(L*L - b*b - x*x)/(6*EI*L);
   }
   else
   {
      y = W*a*(L-x)*(L*L - a*a - (L-x)*(L-x))/(6*EI*L);
   }

   return y;
}
