///////////////////////////////////////////////////////////////////////
// RCSection - Reinforced concrete section analysis modeling
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

#include <RCSection\RCSectionLib.h>
#include <RCSection\RCSolver.h>

#include <LRFD/ConcreteUtil.h>
#include <algorithm>

using namespace WBFL::RCSection;

RCSolution RCSolver::Solve(const RCBeam& beam)
{
   auto fpy = beam.GetFpy();
   auto fpu = beam.GetFpu();
   auto fs = beam.GetFy();

   auto k = 2.0 * (1.04 - fpy / fpu);

   auto As = beam.GetAs();
   auto Aps = beam.GetAps();

   auto ds = beam.GetDs();
   auto dps = beam.GetDps();

   auto fc = Min(beam.GetFcSlab(), beam.GetFcBeam());

   auto b = beam.GetB();
   auto bw = beam.GetBw();
   auto hf = beam.GetHf();

   if (IsZero(As) && IsZero(Aps))
   {
      // if there is no reinforcement, then there is no capacity
      return RCSolution();
   }

   // dps is likely to be 0.0 if Aps is 0.0
   // to prevent divide by zero, set dps to 1.0
   if (IsZero(Aps)) dps = 1.0;

   auto alpha1 = WBFL::LRFD::ConcreteUtil::Alpha1(fc);
   auto beta1 = WBFL::LRFD::ConcreteUtil::Beta1(fc);

   // assume t-section behavior, compute c
   auto c = (Aps * fpu + As * fs - alpha1 * fc * (b - bw) * hf)/(alpha1*fc*beta1*bw + k*Aps*fpu/dps);

   auto fps = 0.0;
   auto Mn = 0.0;
   if (c < hf)
   {
      // rectangular section behavior
      c = (Aps * fpu + As * fs) / (alpha1 * fc * beta1 * b + k * Aps * fpu / dps);
      auto a = beta1 * c;
      fps = IsZero(Aps) ? 0.0 : fpu * (1 - k * c / dps);

      Mn = Aps * fps * (dps - a / 2) + As * fs * (ds - a / 2);
   }
   else
   {
      // t-section behavior
      auto a = beta1 * c;
      fps = IsZero(Aps) ? 0.0 : fpu * (1 - k * c / dps);

      Mn = Aps * fps * (dps - a / 2) + As * fs * (ds - a / 2) + alpha1 * fc * (b - bw) * hf * (a / 2 - hf / 2);
   }

   auto d = Max(beam.GetDpsMax(), beam.GetDsMax());
   auto et = 0.003 * (d - c) / c;

   RCSolution solution(Mn, c, alpha1, beta1, fps, et);
   return solution;
}