///////////////////////////////////////////////////////////////////////
// RCSection - Reinforced concrete section analysis modeling
// Copyright © 1999-2025  Washington State Department of Transportation
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
#pragma once

#include <RCSection/RCSectionExp.h>

namespace WBFL
{
   namespace RCSection
   {
      /// Abstract class representing a stress block factor.
      ///
      /// Stress block factor is the ratio of equivalent rectangular concrete compressive stress block intensity to the compressive strength of concrete used in design
      class RCSCLASS StressBlockFactor
      {
      public:
         StressBlockFactor() = default;
         StressBlockFactor(const StressBlockFactor& other) = default;
         virtual ~StressBlockFactor() = default;
         
         StressBlockFactor& operator=(const StressBlockFactor& other) = default;

         /// Returns the stress block intensity factor (alpha1)
         virtual Float64 GetIntensityFactor() const = 0;

         /// Returns the stress block depth factor (beta1)
         virtual Float64 GetDepthFactor() const = 0;
      };
   };
};