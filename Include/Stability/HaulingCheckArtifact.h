///////////////////////////////////////////////////////////////////////
// Stability
// Copyright © 1999-2018  Washington State Department of Transportation
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


/*****************************************************************************
CLASS 
   stbHaulingCheckArtifact

DESCRIPTION
   Encapsulates the spec check of a hauling analysis
*****************************************************************************/

class STABILITYCLASS stbHaulingCheckArtifact
{
public:
   stbHaulingCheckArtifact();
   stbHaulingCheckArtifact(const stbHaulingResults& results,const stbHaulingCriteria& criteria,bool bComputeCrownSlopeStressesAtEquilibriumAngle, bool bComputeSuperelevationStressesAtEquilibriumAngle);
   void Init(const stbHaulingResults& results,const stbHaulingCriteria& criteria, bool bComputeCrownSlopeStressesAtEquilibriumAngle, bool bComputeSuperelevationStressesAtEquilibriumAngle);

   const stbHaulingResults& GetHaulingResults() const;
   const stbHaulingCriteria& GetCriteria() const;

   bool EvaluateStressesAtEquilibriumAngle(stbTypes::HaulingSlope slope) const;

   void GetControllingTensionCase(stbTypes::HaulingSlope slope,const stbHaulingSectionResult& sectionResult,stbTypes::ImpactDirection* pImpact,stbTypes::WindDirection* pWind,stbTypes::Corner* pCorner,Float64* pfAllow,bool* pbPassed,Float64* pCD) const;
   void GetControllingCompressionCase(stbTypes::HaulingSlope slope,const stbHaulingSectionResult& sectionResult,stbTypes::ImpactDirection* pImpact,stbTypes::WindDirection* pWind,stbTypes::Corner* pCorner,Float64* pfAllow,bool* pbPassed,Float64* pCD) const;

   bool Passed(bool bIgnoreConfigurationLimits) const;
   bool Passed(stbTypes::HaulingSlope slope) const;
   bool PassedCrackingCheck(stbTypes::HaulingSlope slope) const;
   bool PassedFailureCheck(stbTypes::HaulingSlope slope) const;
   bool PassedRolloverCheck(stbTypes::HaulingSlope slope) const;
   bool PassedDirectStressCheck(stbTypes::HaulingSlope slope) const;
   bool PassedDirectCompressionCheck(stbTypes::HaulingSlope slope) const;
   bool PassedDirectTensionCheck(stbTypes::HaulingSlope slope) const;
   bool PassedStressCheck(stbTypes::HaulingSlope slope) const;
   bool PassedCompressionCheck(stbTypes::HaulingSlope slope) const;
   bool PassedTensionCheck(stbTypes::HaulingSlope slope) const;

   bool PassedClearSpan() const;
   bool PassedLeadingOverhang() const;
   bool PassedMaxWeight() const;

   Float64 GetAllowableTension(stbTypes::HaulingSlope slope,const stbHaulingSectionResult& sectionResult,stbTypes::ImpactDirection impact,stbTypes::WindDirection wind) const;

   Float64 RequiredFcCompression(stbTypes::HaulingSlope slope) const;
   Float64 RequiredFcTension(stbTypes::HaulingSlope slope) const;
   Float64 RequiredFcTensionWithRebar(stbTypes::HaulingSlope slope) const;

protected:
   stbHaulingResults m_Results;
   stbHaulingCriteria m_Criteria;
   bool m_bComputeStressesAtEquilibriumAngle[2]; // HaulingSlope is the array index
};
