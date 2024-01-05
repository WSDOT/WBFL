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

namespace WBFL
{
   namespace RCSection
   {
      /// Moment capacity solution for an RCBeam
      class RCSCLASS RCSolution
      {
      public:
         RCSolution() = default;
         RCSolution(Float64 Mn,Float64 c,Float64 alpha1,Float64 beta1,Float64 fps,Float64 et)
         {
            m_Mn = Mn;
            m_c = c;
            m_Alpha1 = alpha1;
            m_Beta1 = beta1;
            m_fps = fps;
            m_et = et;
         }

         RCSolution(const RCSolution& other) = default;
         ~RCSolution() = default;
         
         RCSolution& operator=(const RCSolution& other) = default;

         void SetMn(Float64 Mn) { m_Mn = Mn; }
         Float64 GetMn() const { return m_Mn; }

         void SetC(Float64 c) { m_c = c; }
         Float64 GetC() const { return m_c;  }

         void SetAlpha1(Float64 alpha1) { m_Alpha1 = alpha1; }
         Float64 GetAlpha1() const { return m_Alpha1; }

         void SetBeta1(Float64 beta1) { m_Beta1 = beta1; }
         Float64 GetBeta1() const { return m_Beta1; }

         void SetFps(Float64 fps) { m_fps = fps; }
         Float64 GetFps() const { return m_fps; }

         void Set_et(Float64 et) { m_et = et; }
         Float64 Get_et() const { return m_et; }

      private:
         Float64 m_Mn = 0.0;
         Float64 m_c = 0.0;
         Float64 m_Alpha1 = 0.0;
         Float64 m_Beta1 = 0.0;
         Float64 m_fps = 0.0;
         Float64 m_et = 0.0;
      };
   };
};