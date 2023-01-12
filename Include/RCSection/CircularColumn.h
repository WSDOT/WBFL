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
#include <RCSection/ConstantStressBlockFactor.h>
#include <vector>

namespace WBFL
{
   namespace RCSection
   {
      /// A circular reinforced concrete column. The reinforcing is assumed to be closely spaced and uniformly distributed around the cross section.
      /// \image html CircularColumn/CircularColumn.jpg
      class RCSCLASS CircularColumn
      {
      public:
         CircularColumn() = default;
         CircularColumn(Float64 diameter, Float64 cover, Float64 As, Float64 fc, Float64 fy, Float64 Es);
         CircularColumn(const CircularColumn&) = default;
         ~CircularColumn() = default;

         CircularColumn& operator=(const CircularColumn&) = default;

         /// Diameter of the column
         void SetDiameter(Float64 diameter);
         Float64 GetDiameter() const;

         /// Cover from the exterior face of the column to the center of the reinforcement
         void SetCover(Float64 cover);
         Float64 GetCover() const;

         /// Total area of reinforcement
         void SetAs(Float64 as);
         Float64 GetAs() const;

         /// Concrete compressive strength
         void SetFc(Float64 fc);
         Float64 GetFc() const;

         /// Yield strength of reinforcement
         void SetFy(Float64 fy);
         Float64 GetFy() const;

         /// Modulus of elasticity of reinforcement
         void SetEs(Float64 Es);
         Float64 GetEs() const;

         /// Stress block factor
         void SetStressBlockFactor(const std::shared_ptr<const StressBlockFactor>& stressBlockFactor);
         const std::shared_ptr<const StressBlockFactor>& GetStressBlockFactor() const;

         /// Computes an axial force - moment interaction curve
         /// \param nSteps number of axial load steps for the analysis
         /// \return the interaction curve. The first element of the pair is Moment, the second element is Axial force
         std::vector<std::pair<Float64, Float64>> ComputeInteraction(IndexType nSteps) const;

         /// Computes an axial force - moment interaction curve and applies the LRFD Resistance Factor
         ///
         /// The resistance factor is computed as \f$ 0.75 \le \phi = 0.75 + \frac{0.15(\epsilon_t - \epsilon_{cl})}{(\epsilon_{tl} - \epsilon_{cl})} \le 0.90 \f$
         /// \param[in] nSteps number of axial load steps for the analysis
         /// \param[in] ecl Strain limit for compression controlled sections
         /// \param[in] etl Strain limit for tension controlled sections
         /// \param[out] unfactored  the unfactored interaction curve points. The first element of the pair is Moment, the second element is Axial force
         /// \param[out] factored  the factored interaction curve points. The first element of the pair is Moment, the second element is Axial force
         void ComputeInteraction(IndexType nSteps, Float64 ecl, Float64 etl, std::vector<std::pair<Float64, Float64>>& unfactored, std::vector<std::pair<Float64, Float64>>& factored) const;

      private:
         // class members initialized with default values in Kip-Inch units
         Float64 m_Diameter{ 72.0 };
         Float64 m_As{10.0};
         Float64 m_Cover{2.0};
         Float64 m_Fc{4.0};
         Float64 m_Fy{60.0};
         Float64 m_Es{29000};
         std::shared_ptr<const StressBlockFactor> m_StressBlockFactor{ std::make_shared<ConstantStressBlockFactor>() };

#if defined _UNITTEST
      public:
         static bool TestMe(WBFL::Debug::Log& rlog);
#endif // _UNITTEST
      };
   };
};
