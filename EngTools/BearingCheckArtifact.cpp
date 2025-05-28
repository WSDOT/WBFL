///////////////////////////////////////////////////////////////////////
// EngTools - Library of miscellaneous engineering tools
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

#include <EngTools\EngToolsLib.h>
#include <EngTools\BearingCheckArtifact.h>
#include <Units\Convert.h>
#include <MathEx.h>



using namespace WBFL::EngTools;



BearingCheckArtifact::BearingCheckArtifact(const Bearing& bearing, const BearingLoads& loads, const BearingResults& results, const BearingDesignCriteria& criteria)
	:m_bearing(bearing),
	m_loads(loads),
	m_results(results),
	m_criteria(criteria)
{
}

BearingCheckArtifact::~BearingCheckArtifact()
{
}

const Bearing& BearingCheckArtifact::GetBearing() const
{
	return m_bearing;
}

const BearingLoads& BearingCheckArtifact::GetBearingLoads() const
{
	return m_loads;
}

const BearingResults& BearingCheckArtifact::GetBearingResults() const
{
	return m_results;
}

const BearingDesignCriteria& BearingCheckArtifact::GetBearingDesignCriteria() const
{
	return m_criteria;
}

bool BearingCheckArtifact::MinimumAreaCheck() const
{
	bool check = m_bearing.GetArea() >= m_criteria.GetMinimumAllowableArea();
	return check;
}

bool BearingCheckArtifact::MinimumLengthCheck() const
{
	bool check = m_bearing.GetLength() >= m_criteria.GetMinimumAllowableLength();
	return check;
}

bool BearingCheckArtifact::MinimumWidthCheck() const
{
	bool check = m_bearing.GetWidth() >= m_criteria.GetMinimumAllowableWidth();
	return check;
}

bool BearingCheckArtifact::MaximumStressCheck() const
{
	bool check = m_results.TotalLoadStress <= m_criteria.MaximumAllowableStressMethodA;
	return check;
}

bool BearingCheckArtifact::MaximumIntermediateLayerThicknessCheck() const
{
	bool check = m_bearing.GetIntermediateLayerThickness() <= m_criteria.GetMaximumAllowableIntermediateLayerThickness();
	return check;
}

bool BearingCheckArtifact::MinimumShapeFactorCheck() const
{
	bool check = m_bearing.GetShapeFactor() >= m_criteria.GetMinimumAllowableShapeFactor();
	return check;
}

bool BearingCheckArtifact::MaximumShapeFactorCheck() const
{
	bool check = m_bearing.GetShapeFactor() <= m_criteria.GetMaximumAllowableShapeFactor();
	return check;
}

bool BearingCheckArtifact::MinimumNumLayersShearDeformationCheck() const
{
	bool check = m_bearing.GetNumIntLayers() >= m_criteria.GetMinimumAllowableNumLayersShearDeformation();
	return check;
}

bool BearingCheckArtifact::MinimumNumLayersRotationXCheck() const
{
	bool check = m_bearing.GetNumIntLayers() >= m_criteria.GetMinimumAllowableNumLayersRotationX();
	return check;
}

bool BearingCheckArtifact::MinimumNumLayersRotationYCheck() const
{
	bool check = m_bearing.GetNumIntLayers() >= m_criteria.GetMinimumAllowableNumLayersRotationY();
	return check;
}

bool BearingCheckArtifact::MaximumNumLayersStabilityXCheck() const
{
	bool check = m_bearing.GetNumIntLayers() <= m_criteria.GetMaximumAllowableNumLayersStabilityX();
	return check;
}

bool BearingCheckArtifact::MaximumNumLayersStabilityYCheck() const
{
	bool check = m_bearing.GetNumIntLayers() <= m_criteria.GetMaximumAllowableNumLayersStabilityY();
	return check;
}

bool BearingCheckArtifact::MinimumSteelShimThicknessAbsoluteCheck() const
{
	bool check = m_bearing.GetSteelShimThickness() >= m_criteria.GetAbsoluteMinimumShimThickness();
	return check;
}

bool BearingCheckArtifact::MinimumElastomerCoverThicknessCheck() const
{
	bool check = m_bearing.GetCoverThickness() >= m_criteria.GetMinimumElastomerCoverThickness();
	return check;
}

bool BearingCheckArtifact::MaximumElastomerCoverThicknessCheck() const
{
	bool check = m_bearing.GetCoverThickness() <= m_criteria.GetMaximumElastomerCoverThickness();
	return check;
}

bool BearingCheckArtifact::MinimumSteelShimThicknessServiceCheck() const
{
	bool check = m_bearing.GetSteelShimThickness() >= m_criteria.GetMinimumAllowableSteelShimThicknessService();
	return check;
}

bool BearingCheckArtifact::MinimumSteelShimThicknessFatigueCheck() const
{
	bool check = m_bearing.GetSteelShimThickness() >= m_criteria.GetMinimumAllowableSteelShimThicknessFatigue();
	return check;
}

bool BearingCheckArtifact::MaximumCompressiveStrainCheck() const
{
	bool check = m_results.TotalLoadStress / m_results.ElastomerElasticModulusMethodA <= 0.07;
	return check;
}

bool BearingCheckArtifact::StaticRotationalPrimaryShearStrainCheck() const
{
	bool check = 1.552 - 0.627 * m_bearing.GetCompressibilityIndex() / (2.233 + 0.156 * m_bearing.GetCompressibilityIndex() * m_bearing.GetLength()) >= 0.5;
	return check;
}

bool BearingCheckArtifact::ShearDeformationCheck() const
{
	bool check = m_bearing.GetTotalElastomerThickness() >= 2 * m_loads.GetShearDeformation();
	return check;
}

bool BearingCheckArtifact::StaticAxialPrimaryShearStrainCheck() const
{
	bool check = m_results.StaticAxialPrimaryShearStrain <= m_criteria.MaximumStaticAxialShearStrain;
	return check;
}

bool BearingCheckArtifact::StaticAxialSecondaryShearStrainCheck() const
{
	bool check = m_results.StaticAxialSecondaryShearStrain <= m_criteria.MaximumStaticAxialShearStrain;
	return check;
}

bool BearingCheckArtifact::PrimaryShearStrainComboSumCheck() const
{
	bool check = abs(m_results.PrimaryShearStrainComboSum) <= m_criteria.MaximumCombinedShearStrain;
	return check;
}

bool BearingCheckArtifact::SecondaryShearStrainComboSumCheck() const
{
	bool check = abs(m_results.SecondaryShearStrainComboSum) <= m_criteria.MaximumCombinedShearStrain;
	return check;
}

bool BearingCheckArtifact::StabilityXDirectionCheck() const
{
	bool check = m_results.TotalStress <= m_criteria.GetAllowableTotalLoadStressStabilityX();
	return check;
}

bool BearingCheckArtifact::StabilityYDirectionCheck() const
{
	bool check = m_results.TotalStress <= m_criteria.GetAllowableTotalLoadStressStabilityY();
	return check;
}

bool BearingCheckArtifact::RestraintSystemRequirementCheck() const
{
	bool check = m_results.RestraintSystemDCRatio <= 1.0;
	return check;
}

bool BearingCheckArtifact::HydrostaticStressCheck() const
{
	bool check = m_criteria.GetMaximumAllowableHydrostaticStress() >= m_results.HydrostaticStress;
	return check;
}

bool BearingCheckArtifact::HorizontalForceCheck() const
{
	bool check = m_results.HorizontalForce <= m_loads.GetDeadLoad() / 5.0;
	return check;
}

bool BearingCheckArtifact::MinimumAllowableShearModulusCheck() const
{
	bool check = m_bearing.GetShearModulusMinimum() >= m_criteria.MinimumElastomerShearModulus;
	return check;
}

bool BearingCheckArtifact::MaximumAllowableShearModulusCheck() const
{
	bool check = m_bearing.GetShearModulusMaximum() <= m_criteria.MaximumElastomerShearModulus;
	return check;
}

bool BearingCheckArtifact::RequiredIntermediateElastomerThicknessCheck() const
{
	bool check = m_bearing.GetIntermediateLayerThickness() == m_criteria.RequiredIntermediateElastomerThickness;
	return check;
}

bool BearingCheckArtifact::MinimumTotalBearingHeightCheck() const
{
	bool check = m_results.TotalBearingHeight >= m_criteria.MinimumTotalBearingHeight;
	return check;
}

bool BearingCheckArtifact::MinimumBearingEdgeToBottomFlangeEdgeDistCheck() const
{
	bool check = m_bearing.GetBearingToGirderFlangeDistance() >= m_criteria.MinimumBearingEdgeToGirderEdgeDistance;
	return check;
}

bool BearingCheckArtifact::MaximumBearingEdgeToBottomFlangeEdgeDistCheck() const
{
	bool check = m_bearing.GetBearingToGirderFlangeDistance() <= m_criteria.MaximumBearingEdgeToGirderEdgeDistance;
	return check;
}

bool BearingCheckArtifact::RequiredBearingEdgeToBottomFlangeEdgeDistCheck() const
{
	bool check = m_bearing.GetBearingToGirderFlangeDistance() == m_criteria.RequiredBearingEdgeToGirderEdgeDistance;
	return check;
}

bool BearingCheckArtifact::MaximumLiveLoadDeflectionMethodACheck() const
{
	bool check = m_results.InstantaneousLiveLoadDeflectionMethodA <= m_criteria.maxLLdef;
	return check;
}

bool BearingCheckArtifact::MaximumLiveLoadDeflectionMethodBCheck() const
{
	bool check = m_results.InstantaneousLiveLoadDeflectionMethodB <= m_criteria.maxLLdef;
	return check;
}

bool BearingCheckArtifact::MaximumTotalLoadCheck() const
{
	bool check = m_loads.GetTotalLoad() <= m_criteria.MaximumTotalLoad;
	return check;
}


