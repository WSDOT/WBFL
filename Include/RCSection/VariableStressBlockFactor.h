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
#pragma once

#include <RCSection/RCSectionExp.h>
#include <RCSection/StressBlockFactor.h>

namespace WBFL
{
   namespace RCSection
   {
      /// A stress block factor that linearly varies between two values
      class RCSCLASS VariableStressBlockFactor : public StressBlockFactor
      {
      public:
         VariableStressBlockFactor(Float64 alpha1 = 0.85, Float64 fc1 = 10, Float64 alpha2 = 0.75, Float64 fc2 = 15,Float64 beta1=0.85);
         VariableStressBlockFactor(const VariableStressBlockFactor& other) = default;
         virtual ~VariableStressBlockFactor() = default;
         
         VariableStressBlockFactor& operator=(const VariableStressBlockFactor& other) = default;

         void SetStressBlockParameters(Float64 alpha1, Float64 fc1, Float64 alpha2, Float64 fc2,Float64 beta1);
         void GetStressBlockParameters(Float64& alpha1, Float64& fc1, Float64& alpha2, Float64& fc2,Float64& beta1) const;

         void SetFc(Float64 fc);
         Float64 GetFc() const;
         
         virtual Float64 GetIntensityFactor() const override;
         virtual Float64 GetDepthFactor() const override;

      private:
         Float64 m_Alpha1{ 0.85 };
         Float64 m_Alpha2{ 0.75 };
         Float64 m_Fc1{ 10 };
         Float64 m_Fc2{ 15 };
         Float64 m_Fc{ 0 };
         Float64 m_Beta1{ 0.85 };
      };
   };
};