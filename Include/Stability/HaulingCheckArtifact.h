///////////////////////////////////////////////////////////////////////
// Stability
// Copyright © 1999-2020  Washington State Department of Transportation
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
#include <Stability\HaulingCriteria.h>


/// Results of a hauling check analysis
class STABILITYCLASS stbHaulingCheckArtifact
{
public:
   /// Constructions a default artifact. 
   /// Init must be called to initialize the artifact with analysis results.
   stbHaulingCheckArtifact();

   /// Constructs a check artifact, initializing it with analysis results and check criteria.
   /// There is no need to call Init if this constructor is used.
   stbHaulingCheckArtifact(
      const stbHaulingResults& results, ///< Hauling analysis results
      const stbHaulingCriteria& criteria ///< Hauling check criteria
   );

   /// Initializes this object
   /// \param results Hauling analysis results
   /// \param criteria Hauling check criteria
   void Init(const stbHaulingResults& results, const stbHaulingCriteria& criteria);

   /// Returns the results of a hauling analysis
   const stbHaulingResults& GetHaulingResults() const;

   /// Returns the hauling check criteria
   const stbHaulingCriteria& GetCriteria() const;

   /// Analyzes the section results and retrieves the controlling tension stress case
   /// \param[in] slope Specifies the roadway slope type
   /// \param[in] sectionResult Analysis results to be evalauted
   /// \param[out] pImpact Impact direction associated with the controlling case
   /// \param[out] pWind Wind direction associated with the controlling case
   /// \param[out] pCorner Corner associated with the controlling case
   /// \param[out] pfAllow Tension stress limit associated with the controlling case
   /// \param[out] pbPassed Indicates if the controlling case passes the specification check
   /// \param[out] pCD Capacity-Demand ratio for the controlling case
   void GetControllingTensionCase(stbTypes::HaulingSlope slope, const stbHaulingSectionResult& sectionResult, stbTypes::ImpactDirection* pImpact, stbTypes::WindDirection* pWind, stbTypes::Corner* pCorner, Float64* pfAllow, bool* pbPassed, Float64* pCD) const;

   /// Analyzes the section results and retrieves the controlling global compression case.
   /// \param[in] slope Specifies the roadway slope type
   /// \param[in] sectionResult Analysis results to be evalauted
   /// \param[out] pImpact Impact direction associated with the controlling case
   /// \param[out] pCorner Corner associated with the controlling case
   /// \param[out] pfAllow Tension stress limit associated with the controlling case
   /// \param[out] pbPassed Indicates if the controlling case passes the specification check
   /// \param[out] pCD Capacity-Demand ratio for the controlling case
   void GetControllingGlobalCompressionCase(stbTypes::HaulingSlope slope, const stbHaulingSectionResult& sectionResult, stbTypes::ImpactDirection* pImpact, stbTypes::Corner* pCorner, Float64* pfAllow, bool* pbPassed, Float64* pCD) const;

   /// Analyzes the section results and retrieves the controlling peak compression case.
   /// \param[in] slope Specifies the roadway slope type
   /// \param[in] sectionResult Analysis results to be evalauted
   /// \param[out] pImpact Impact direction associated with the controlling case
   /// \param[out] pWind Wind direction associated with the controlling case
   /// \param[out] pCorner Corner associated with the controlling case
   /// \param[out] pfAllow Tension stress limit associated with the controlling case
   /// \param[out] pbPassed Indicates if the controlling case passes the specification check
   /// \param[out] pCD Capacity-Demand ratio for the controlling case
   void GetControllingPeakCompressionCase(stbTypes::HaulingSlope slope, const stbHaulingSectionResult& sectionResult, stbTypes::ImpactDirection* pImpact, stbTypes::WindDirection* pWind, stbTypes::Corner* pCorner, Float64* pfAllow, bool* pbPassed, Float64* pCD) const;

   /// Returns true if the hauling check was successful
   /// \param[in] bIgnoreConfigurationLimits If true the clear span, leading overhang, and max weight limits are ignored
   bool Passed(bool bIgnoreConfigurationLimits) const;

   /// Returns true if the hauling check passed for the specified roadway slope type
   bool Passed(stbTypes::HaulingSlope slope) const;

   /// Returns true if the cracking check passed for the specified roadway slope type
   bool PassedCrackingCheck(stbTypes::HaulingSlope slope) const;

   /// Returns true if the failure check passed for the specified roadway slope type
   bool PassedFailureCheck(stbTypes::HaulingSlope slope) const;

   /// Returns true if the rollover check passed for the specified roadway slope type
   bool PassedRolloverCheck(stbTypes::HaulingSlope slope) const;

   /// Returns true if the stress check without lateral load and tilt effects passed for the specified roadway slope type
   bool PassedDirectStressCheck(stbTypes::HaulingSlope slope) const;

   /// Returns true if the compression stress check without lateral load and tilt effects passed for the specified roadway slope type
   bool PassedDirectCompressionCheck(stbTypes::HaulingSlope slope) const;

   /// Returns true if the tension stress check without lateral load and tilt effects passed for the specified roadway slope type
   bool PassedDirectTensionCheck(stbTypes::HaulingSlope slope) const;

   /// Returns true if the stress check with lateral load and tilt effects passed for the specified roadway slope type
   bool PassedStressCheck(stbTypes::HaulingSlope slope) const;

   /// Returns true if the compression stress check with lateral load and tilt effects passed for the specified roadway slope type
   bool PassedCompressionCheck(stbTypes::HaulingSlope slope) const;

   /// Returns true if the tension stress check with lateral load and tilt effects passed for the specified roadway slope type
   bool PassedTensionCheck(stbTypes::HaulingSlope slope) const;

   /// Returns true of the clear span check passed
   bool PassedClearSpan() const;

   /// Returns true of the leading overhang check passed
   bool PassedLeadingOverhang() const;

   /// Returns true of the maximum girder weight check passed
   bool PassedMaxWeight() const;

#if defined REBAR_FOR_DIRECT_TENSION
   /// Returns the tension stress limit
   /// \param[in] slope Specifies the roadway slope type
   /// \param[in] sectionResult Analysis results to be evalauted
   /// \param[in] impact Impact direction
   Float64 GetAllowableTension(stbTypes::HaulingSlope slope, const stbHaulingSectionResult& sectionResult, stbTypes::ImpactDirection impact) const;
#else
   /// Returns the tension stress limit
   /// \param[in] slope Specifies the roadway slope type
   /// \param[in] sectionResult Analysis results to be evalauted
   /// \param[in] impact Impact direction
   /// \param[in] wind Wind direction
   Float64 GetAllowableTension(stbTypes::HaulingSlope slope,const stbHaulingSectionResult& sectionResult,stbTypes::ImpactDirection impact,stbTypes::WindDirection wind) const;
#endif

   /// Returns the concrete strength required to satisfy the compression stress limit
   Float64 RequiredFcCompression(stbTypes::HaulingSlope slope /*! Roadway slope type*/) const;

   /// Returns the concrete strenght required to satisfy the tension stress limit for sections without sufficient auxilary reinforcement
   Float64 RequiredFcTension(stbTypes::HaulingSlope slope /*! Roadway slope type*/) const;

   /// Returns the concrete strenght required to satisfy the tension stress limit for sections with sufficient auxilary reinforcement
   Float64 RequiredFcTensionWithRebar(stbTypes::HaulingSlope slope /*! Roadway slope type*/) const;

private:
   stbHaulingResults m_Results;
   stbHaulingCriteria m_Criteria;
};
