///////////////////////////////////////////////////////////////////////
// Stability
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

#include <Stability/StabilityExp.h>
#include <Stability/HaulingResults.h>
#include <Stability/HaulingCriteria.h>
#include <Stability/ControllingCases.h>

namespace WBFL
{
   namespace Stability
   {

      /// Results of a hauling check analysis
      class STABILITYCLASS HaulingCheckArtifact
      {
      public:
         /// Constructions a default artifact. 
         /// Init must be called to initialize the artifact with analysis results.
         HaulingCheckArtifact();

         /// Constructs a check artifact, initializing it with analysis results and check criteria.
         /// There is no need to call Init if this constructor is used.
         HaulingCheckArtifact(
            const HaulingResults& results, ///< Hauling analysis results
            const HaulingCriteria& criteria ///< Hauling check criteria
         );

         /// Initializes this object
         /// \param results Hauling analysis results
         /// \param criteria Hauling check criteria
         void Init(const HaulingResults& results, const HaulingCriteria& criteria);

         /// Returns the results of a hauling analysis
         const HaulingResults& GetHaulingResults() const;

         /// Returns the hauling check criteria
         const HaulingCriteria& GetCriteria() const;

         /// Analyzes the section results and retrieves the valuated
         ControllingTensionCase GetControllingTensionCase(HaulingSlope slope, const HaulingSectionResult& sectionResult) const;

         /// Analyzes the section results and retrieves the controlling global compression case.
         /// \param slope Specifies the roadway slope type
         /// \param sectionResult Analysis results to be evaluated
         ControllingGlobalCompressionCase GetControllingGlobalCompressionCase(HaulingSlope slope, const HaulingSectionResult& sectionResult) const;

         /// Analyzes the section results and retrieves the controlling peak compression case.
         /// \param slope Specifies the roadway slope type
         /// \param sectionResult Analysis results to be evaluated
         ControllingPeakCompressionCase GetControllingPeakCompressionCase(HaulingSlope slope, const HaulingSectionResult& sectionResult) const;

         /// Returns true if the hauling check was successful
         /// \param[in] bIgnoreConfigurationLimits If true the clear span, leading overhang, and max weight limits are ignored
         bool Passed(bool bIgnoreConfigurationLimits) const;

         /// Returns true if the hauling check passed for the specified roadway slope type
         bool Passed(HaulingSlope slope) const;

         /// Returns true if the cracking check passed for the specified roadway slope type
         bool PassedCrackingCheck(HaulingSlope slope) const;

         /// Returns true if the failure check passed for the specified roadway slope type
         bool PassedFailureCheck(HaulingSlope slope) const;

         /// Returns true if the rollover check passed for the specified roadway slope type
         bool PassedRolloverCheck(HaulingSlope slope) const;

         /// Returns true if the stress check without lateral load and tilt effects passed for the specified roadway slope type
         bool PassedDirectStressCheck(HaulingSlope slope) const;

         /// Returns true if the compression stress check without lateral load and tilt effects passed for the specified roadway slope type
         bool PassedDirectCompressionCheck(HaulingSlope slope) const;

         /// Returns true if the tension stress check without lateral load and tilt effects passed for the specified roadway slope type
         bool PassedDirectTensionCheck(HaulingSlope slope) const;

         /// Returns true if the stress check with lateral load and tilt effects passed for the specified roadway slope type
         bool PassedStressCheck(HaulingSlope slope) const;

         /// Returns true if the compression stress check with lateral load and tilt effects passed for the specified roadway slope type
         bool PassedCompressionCheck(HaulingSlope slope) const;

         /// Returns true if the tension stress check with lateral load and tilt effects passed for the specified roadway slope type
         bool PassedTensionCheck(HaulingSlope slope) const;

         /// Returns true of the clear span check passed
         bool PassedClearSpan() const;

         /// Returns true of the leading overhang check passed
         bool PassedLeadingOverhang() const;

         /// Returns true of the maximum girder weight check passed
         bool PassedMaxWeight() const;

#if defined REBAR_FOR_DIRECT_TENSION
         /// Returns the tension stress limit
         /// \param[in] slope Specifies the roadway slope type
         /// \param[in] sectionResult Analysis results to be evaluated
         /// \param[in] impact Impact direction
         Float64 GetAllowableTension(HaulingSlope slope, const HaulingSectionResult& sectionResult, ImpactDirection impact) const;
#else
         /// Returns the tension stress limit
         /// \param[in] slope Specifies the roadway slope type
         /// \param[in] sectionResult Analysis results to be evaluated
         /// \param[in] impact Impact direction
         /// \param[in] wind Wind direction
         Float64 GetAllowableTension(HaulingSlope slope, const HaulingSectionResult& sectionResult, ImpactDirection impact, WindDirection wind) const;
#endif

         /// Returns the concrete strength required to satisfy the compression stress limit
         Float64 RequiredFcCompression(HaulingSlope slope /*! Roadway slope type*/) const;

         /// Returns the concrete strength required to satisfy the tension stress limit
         Float64 RequiredFcTension(HaulingSlope slope /*! Roadway slope type*/) const;
         Float64 RequiredFcTensionWithoutRebar(HaulingSlope slope /*! Roadway slope type*/) const;
         Float64 RequiredFcTensionWithRebar(HaulingSlope slope /*! Roadway slope type*/) const;

      private:
         HaulingResults m_Results;
         HaulingCriteria m_Criteria;
      };
   }
}