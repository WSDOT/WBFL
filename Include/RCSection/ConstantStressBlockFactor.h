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
      /// A constant value stress block factor. The default value is 0.85
      class RCSCLASS ConstantStressBlockFactor : public StressBlockFactor
      {
      public:
         ConstantStressBlockFactor(Float64 alpha1 = 0.85,Float64 beta1=0.85) : StressBlockFactor(), m_Alpha1(alpha1), m_Beta1(beta1) {}
         ConstantStressBlockFactor(const ConstantStressBlockFactor& other) = default;
         virtual ~ConstantStressBlockFactor() = default;
         
         ConstantStressBlockFactor& operator=(const ConstantStressBlockFactor& other) = default;

         void SetIntensityFactor(Float64 alpha1) { m_Alpha1 = alpha1; }
         void SetDepthFactor(Float64 beta1) { m_Beta1 = beta1; }

         virtual Float64 GetIntensityFactor() const override
         {
            return m_Alpha1;
         }

         virtual Float64 GetDepthFactor() const override
         {
            return m_Beta1;
         }

      private:
         Float64 m_Alpha1{ 0.85 };
         Float64 m_Beta1{ 0.85 };
      };
   };
};