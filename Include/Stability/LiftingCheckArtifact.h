///////////////////////////////////////////////////////////////////////
// Stability
// Copyright © 1999-2021  Washington State Department of Transportation
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
#include <Stability\LiftingResults.h>
#include <Stability\LiftingCriteria.h>

namespace WBFL
{
   namespace Stability
   {

      /// Results of a lifting check analysis
      class STABILITYCLASS LiftingCheckArtifact
      {
      public:
         /// Constructions a default artifact. 
         /// Init must be called to initialize the artifact with analysis results.
         LiftingCheckArtifact();

         /// Constructs a check artifact, initializing it with analysis results and check criteria.
         /// There is no need to call Init if this constructor is used.
         LiftingCheckArtifact(
            const LiftingResults& results, ///< Lifting analysis results
            const LiftingCriteria& criteria ///< Lifting check criteria
         );

         /// Initializes this object
         void Init(
            const LiftingResults& results, ///< Lifting analysis results
            const LiftingCriteria& criteria ///< Lifting check criteria
         );

         /// Returns the results of a lifting analysis
         const LiftingResults& GetLiftingResults() const;

         /// Returns the lifting check criteria
         const LiftingCriteria& GetCriteria() const;

         /// Analyzes the section results and retrieves the controlling tension stress case
         /// \param[in] sectionResult Analysis results to be evalauted
         /// \param[out] pImpact Impact direction associated with the controlling case
         /// \param[out] pWind Wind direction associated with the controlling case
         /// \param[out] pCorner Corner associated with the controlling case
         /// \param[out] pfAllow Tension stress limit associated with the controlling case
         /// \param[out] pbPassed Indicates if the controlling case passes the specification check
         /// \param[out] pCD Capacity-Demand ratio for the controlling case
         void GetControllingTensionCase(const LiftingSectionResult& sectionResult, ImpactDirection* pImpact, WindDirection* pWind, Corner* pCorner, Float64* pfAllow, bool* pbPassed, Float64* pCD) const;

         /// Analyzes the section results and retrieves the controlling global compression case.
         /// \param[in] sectionResult Analysis results to be evalauted
         /// \param[out] pImpact Impact direction associated with the controlling case
         /// \param[out] pCorner Corner associated with the controlling case
         /// \param[out] pfAllow Tension stress limit associated with the controlling case
         /// \param[out] pbPassed Indicates if the controlling case passes the specification check
         /// \param[out] pCD Capacity-Demand ratio for the controlling case
         void GetControllingGlobalCompressionCase(const LiftingSectionResult& sectionResult, ImpactDirection* pImpact, Corner* pCorner, Float64* pfAllow, bool* pbPassed, Float64* pCD) const;

         /// Analyzes the section results and retrieves the controlling peak compression case.
         /// \param[in] sectionResult Analysis results to be evalauted
         /// \param[out] pImpact Impact direction associated with the controlling case
         /// \param[out] pWind Wind direction associated with the controlling case
         /// \param[out] pCorner Corner associated with the controlling case
         /// \param[out] pfAllow Tension stress limit associated with the controlling case
         /// \param[out] pbPassed Indicates if the controlling case passes the specification check
         /// \param[out] pCD Capacity-Demand ratio for the controlling case
         void GetControllingPeakCompressionCase(const LiftingSectionResult& sectionResult, ImpactDirection* pImpact, WindDirection* pWind, Corner* pCorner, Float64* pfAllow, bool* pbPassed, Float64* pCD) const;

         /// Returns true if the lifting check was successful
         bool Passed() const;

         /// Returns true if the cracking check passed
         bool PassedCrackingCheck() const;

         /// Returns true if the failure check passed
         bool PassedFailureCheck() const;

         /// Returns true if the stress check without lateral load and tilt effects passed
         bool PassedDirectStressCheck() const;

         /// Returns true if the compression stress check without lateral load and tilt effects passed
         bool PassedDirectCompressionCheck() const;

         /// Returns true if the tension stress check without lateral load and tilt effects passed
         bool PassedDirectTensionCheck() const;

         /// Returns true if the stress check with lateral load and tilt effects passed
         bool PassedStressCheck() const;

         /// Returns true if the compression stress check with lateral load and tilt effects passed
         bool PassedCompressionCheck() const;

         /// Returns true if the tension stress check with lateral load and tilt effects passed
         bool PassedTensionCheck() const;

#if defined REBAR_FOR_DIRECT_TENSION
         /// Returns the tension stress limit
         /// \param[in] sectionResult Analysis results to be evalauted
         /// \param[in] impact Impact direction
         Float64 GetAllowableTension(const LiftingSectionResult& sectionResult, ImpactDirection impact) const;
#else
         /// Returns the tension stress limit
         /// \param[in] sectionResult Analysis results to be evalauted
         /// \param[in] impact Impact direction
         /// \param[in] wind Wind direction
         Float64 GetAllowableTension(const LiftingSectionResult& sectionResult, ImpactDirection impact, WindDirection wind) const;
#endif

         /// Returns the concrete strength required to satisfy the compression stress limit
         Float64 RequiredFcCompression() const;

         /// Returns the concrete strenght required to satisfy the tension stress limit for sections without sufficient auxilary reinforcement
         Float64 RequiredFcTension() const;

         /// Returns the concrete strenght required to satisfy the tension stress limit for sections with sufficient auxilary reinforcement
         Float64 RequiredFcTensionWithRebar() const;

      private:
         LiftingResults m_Results;
         LiftingCriteria m_Criteria;
      };
   }
}