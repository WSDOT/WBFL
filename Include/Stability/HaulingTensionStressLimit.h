///////////////////////////////////////////////////////////////////////
// Stability
// Copyright © 1999-2022  Washington State Department of Transportation
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

#include <Stability\StabilityExp.h>
#include <Stability\HaulingResults.h>

class rptParagraph;
interface IEAFDisplayUnits;

namespace WBFL
{
   namespace Stability
   {
      class HaulingCheckArtifact;

      /// Abstract interface defining a tension stress limit model
      class STABILITYCLASS IHaulingTensionStressLimit
      {
      public:
#if defined REBAR_FOR_DIRECT_TENSION
         /// Returns the tension stress limit
         virtual Float64 GetTensionLimit(HaulingSlope slope, const HaulingSectionResult& sectionResult, ImpactDirection impact) const = 0;
#else
         /// Returns the tension stress limit
         virtual Float64 GetTensionLimit(HaulingSlope slope, const HaulingSectionResult& sectionResult, ImpactDirection impact, WindDirection wind) const = 0;
#endif
         virtual Float64 GetRequiredFcTension(HaulingSlope slope, const HaulingCheckArtifact* pArtifact) const = 0;
         virtual Float64 GetRequiredFcTensionWithoutRebar(HaulingSlope slope, const HaulingCheckArtifact* pArtifact) const = 0;
         virtual Float64 GetRequiredFcTensionWithRebar(HaulingSlope slope, const HaulingCheckArtifact* pArtifact) const = 0;

         /// Reports the tension stress limit
         virtual void ReportTensionLimit(HaulingSlope slope, rptParagraph* pPara, const unitmgtIndirectMeasure* pDisplayUnits) const = 0;

         /// Reports the required concrete strength to satisfy the tension stress limit
         virtual void ReportRequiredConcreteStrength(HaulingSlope slope, const HaulingCheckArtifact* pArtifact, rptParagraph* pPara, const unitmgtIndirectMeasure* pDisplayUnits) const = 0;
      };

      /// Conventional concrete tension stress limit
      class STABILITYCLASS CCHaulingTensionStressLimit : public IHaulingTensionStressLimit
      {
      public:
         CCHaulingTensionStressLimit();

#if defined REBAR_FOR_DIRECT_TENSION
         virtual Float64 GetTensionLimit(HaulingSlope slope, const HaulingSectionResult& sectionResult, ImpactDirection impact) const override;
#else
         virtual Float64 GetTensionLimit(HaulingSlope slope, const HaulingSectionResult& sectionResult, ImpactDirection impact, WindDirection wind) const override;
#endif
         virtual Float64 GetRequiredFcTension(HaulingSlope slope, const HaulingCheckArtifact* pArtifact) const override;
         virtual Float64 GetRequiredFcTensionWithoutRebar(HaulingSlope slope, const HaulingCheckArtifact* pArtifact) const override;
         virtual Float64 GetRequiredFcTensionWithRebar(HaulingSlope slope, const HaulingCheckArtifact* pArtifact) const override;
         virtual void ReportTensionLimit(HaulingSlope slope, rptParagraph* pPara, const unitmgtIndirectMeasure* pDisplayUnits) const override;
         virtual void ReportRequiredConcreteStrength(HaulingSlope slope, const HaulingCheckArtifact* pArtifact, rptParagraph* pPara, const unitmgtIndirectMeasure* pDisplayUnits) const override;

         Float64 Lambda; ///< concrete density modification factor (see LRFD 5.4.2.8)

          // array index is HaulingSlope
         std::array<Float64, 2> TensionCoefficient; ///< Coefficient for tension stress without rebar (x*lambda*sqrt(f'c))
         std::array<bool, 2> bMaxTension; ///< If true, there is an upper limit on the tension stress limit
         std::array<Float64, 2> MaxTension; ///< Upper limit on the tension stress limit
         std::array<Float64, 2> AllowableTension; ///< Tension stress limit

         std::array<bool, 2> bWithRebarLimit; ///< If true, the tension limit with rebar is applicable
         std::array<Float64, 2> TensionCoefficientWithRebar;  ///< Coefficient for tension stress with rebar (x*lambda*sqrt(f'c))
         std::array<Float64, 2> AllowableTensionWithRebar; ///< Tension stress limit when there is adequate reinforcement
      };


      /// UHPC concrete tension stress limit
      class STABILITYCLASS UHPCHaulingTensionStressLimit : public IHaulingTensionStressLimit
      {
      public:
         UHPCHaulingTensionStressLimit();

#if defined REBAR_FOR_DIRECT_TENSION
         virtual Float64 GetTensionLimit(HaulingSlope slope, const HaulingSectionResult& sectionResult, ImpactDirection impact) const override;
#else
         virtual Float64 GetTensionLimit(HaulingSlope slope, const HaulingSectionResult& sectionResult, ImpactDirection impact, WindDirection wind) const override;
#endif
         virtual Float64 GetRequiredFcTension(HaulingSlope slope, const HaulingCheckArtifact* pArtifact) const override { return 0; }
         virtual Float64 GetRequiredFcTensionWithoutRebar(HaulingSlope slope, const HaulingCheckArtifact* pArtifact) const override { return GetRequiredFcTension(slope, pArtifact); }
         virtual Float64 GetRequiredFcTensionWithRebar(HaulingSlope slope, const HaulingCheckArtifact* pArtifact) const override { return GetRequiredFcTension(slope, pArtifact); }
         virtual void ReportTensionLimit(HaulingSlope slope, rptParagraph* pPara, const unitmgtIndirectMeasure* pDisplayUnits) const override;
         virtual void ReportRequiredConcreteStrength(HaulingSlope slope, const HaulingCheckArtifact* pArtifact, rptParagraph* pPara, const unitmgtIndirectMeasure* pDisplayUnits) const override;

         std::array<Float64, 2> AllowableTension; ///< Tension stress limit
      };
   }
}