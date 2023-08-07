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

   auto [Ra,Rb] = GetReactions();

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

   auto [Ra,Rb] = GetReactions();

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

   auto [L, EI] = GetProperties();
   auto [Ra,Rb] = GetReactions();

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

   auto [L,EI] = GetProperties();
   auto [Ra,Rb] = GetReactions();

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
