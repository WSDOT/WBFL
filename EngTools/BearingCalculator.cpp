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
#include <EngTools\BearingCalculator.h>
#include <Units\Convert.h>
#include <MathEx.h>

using namespace WBFL::EngTools;






Float64 BearingCalculator::ComputeBearingHeight(const Bearing& brg) const
{
	int n = brg.GetNumIntLayers();
	Float64 hrt = brg.GetTotalElastomerThickness();
	Float64 hst = brg.GetSteelShimThickness();
	Float64 totalHeight = hrt + (n + 1) * hst;
	return totalHeight;
}






Float64 BearingCalculator::GetElastomerElasticModulusMethodA(const Bearing& brg, const WBFL::LRFD::BDSManager::Edition& spec) const
{
	Float64 Gmin = brg.GetShearModulusMinimum();
	Float64 Gmax = brg.GetShearModulusMaximum();
	Float64 S = brg.GetShapeFactor();
	Float64 Ecoeff = GetElasticModulusCoefficient(spec);
	Float64 EcMethodA = Ecoeff * (Gmin + Gmax)/2 * pow(S, 2);
    return EcMethodA;
}

Float64 BearingCalculator::GetInitialDeadLoadDeflectionMethodA(const Bearing& brg, const BearingLoads& brg_loads, const WBFL::LRFD::BDSManager::Edition& spec) const
{
	Float64 DL = brg_loads.GetDeadLoad();
	Float64 ttotal = brg.GetTotalElastomerThickness();
	Float64 A = brg.GetArea();
	Float64 EcMethodA = GetElastomerElasticModulusMethodA(brg, spec);
	Float64 deltaDLi = DL * ttotal / A / EcMethodA;
    return  deltaDLi;
}

Float64 BearingCalculator::GetInitialDeadLoadDeflectionMethodB(const Bearing& brg, const BearingLoads& brg_loads, const WBFL::LRFD::BDSManager::Edition& spec) const
{
	Float64 DL = brg_loads.GetDeadLoad();
	Float64 ttotal = brg.GetTotalElastomerThickness();
	Float64 A = brg.GetArea();
	Float64 EcMethodB = GetElastomerElasticModulusMethodB(brg, spec);
	Float64 deltaDLi = DL * ttotal / A / EcMethodB;
	return  deltaDLi;
}

Float64 BearingCalculator::GetInstantaneousLiveLoadDeflectionMethodA(const Bearing& brg, const BearingLoads& brg_loads, const WBFL::LRFD::BDSManager::Edition& spec) const
{
	Float64 LL = brg_loads.GetLiveLoad();
	Float64 ttotal = brg.GetTotalElastomerThickness();
	Float64 A = brg.GetArea();
	Float64 EcMethodA = GetElastomerElasticModulusMethodA(brg, spec);
	Float64 deltaLL = LL * ttotal / A / EcMethodA;
    return deltaLL;
}

Float64 BearingCalculator::GetInstantaneousLiveLoadDeflectionMethodB(const Bearing& brg, const BearingLoads& brg_loads, const WBFL::LRFD::BDSManager::Edition& spec) const
{
	Float64 LL = brg_loads.GetLiveLoad();
	Float64 ttotal = brg.GetTotalElastomerThickness();
	Float64 A = brg.GetArea();
	Float64 EcMethodB = GetElastomerElasticModulusMethodB(brg, spec);
	Float64 deltaLL = LL * ttotal / A / EcMethodB;
	return deltaLL;
}

Float64 BearingCalculator::GetTotalLoadStress(const Bearing& brg, const BearingLoads& brg_loads) const
{
	Float64 TL = brg_loads.GetTotalLoad();
	Float64 A = brg.GetArea();
	Float64 Sigma_TL = TL / A;
    return Sigma_TL;
}

Float64 BearingCalculator::GetLiveLoadStress(const Bearing& brg, const BearingLoads& brg_loads) const
{
	Float64 LL = brg_loads.GetLiveLoad();
	Float64 A = brg.GetArea();
	Float64 Sigma_LL = LL / A;
    return Sigma_LL;
}

Float64 BearingCalculator::GetNlayMultiplier(const Bearing& brg) const
{
	Float64 tcover = brg.GetCoverThickness();
	Float64 tlay = brg.GetIntermediateLayerThickness();
	if (tcover >= 0.5*tlay)
	{
		Float64 NlayX = 1;
		return NlayX;
	}
	else
	{
		Float64 NlayX = 0;
		return NlayX;
	}
}

Float64 BearingCalculator::GetStaticDisplacementPrimaryShearStrain(const Bearing& brg, const BearingLoads& brg_loads) const
{
	Float64 shear_delta = brg_loads.GetShearDeformation();
	Float64 ttotal = brg.GetTotalElastomerThickness();
	Float64 es_Xdisp = shear_delta/ttotal;
	return  es_Xdisp;
}

Float64 BearingCalculator::GetCyclicDisplacementPrimaryShearStrain(const Bearing& brg, const BearingLoads& brg_loads) const
{
	return 0.0;
}

Float64 BearingCalculator::GetStaticAxialPrimaryShearStrain(const Bearing& brg, const BearingLoads& brg_loads) const
{
	Float64 Da = GetPrimaryShearStrainAxialCoefficient(brg);
	Float64 Sstatic = GetStaticStress(brg, brg_loads);
	Float64 Gmin = brg.GetShearModulusMinimum();
	Float64 S = brg.GetShapeFactor();
	Float64 es = Da*Sstatic/Gmin/S;
	return  es;
}

Float64 BearingCalculator::GetCyclicAxialPrimaryShearStrain(const Bearing& brg, const BearingLoads& brg_loads) const
{
	Float64 Da = GetPrimaryShearStrainAxialCoefficient(brg);
	Float64 sigma_cyclic = GetCyclicStress(brg, brg_loads);
	Float64 Gmin = brg.GetShearModulusMinimum();
	Float64 S = brg.GetShapeFactor();
	Float64 es = Da * sigma_cyclic / Gmin / S;
	return es;
}

Float64 BearingCalculator::GetStaticRotationalPrimaryShearStrain(const Bearing& brg, const BearingLoads& brg_loads) const
{
	Float64 Dr = GetPrimaryShearStrainRotationCoefficient(brg);
	Float64 l = brg.GetLength();
	Float64 tlayer = brg.GetIntermediateLayerThickness();
	Float64 rot_static = brg_loads.GetStaticRotation();
	IndexType Nlay = brg.GetNumIntLayers();
	Float64 tcover = brg.GetCoverThickness();
	Float64 es = Dr * pow(l / tlayer, 2) * rot_static / (Nlay + (tcover >= 0.5 * tlayer ? 1 : 0));
	return es;
}

Float64 BearingCalculator::GetCyclicRotationalPrimaryShearStrain(const Bearing& brg, const BearingLoads& brg_loads) const
{
	Float64 Dr = GetPrimaryShearStrainRotationCoefficient(brg);
	Float64 l = brg.GetLength();
	Float64 tlayer = brg.GetIntermediateLayerThickness();
	Float64 rot_cyclic = brg_loads.GetCyclicRotation();
	IndexType Nlay = brg.GetNumIntLayers();
	Float64 tcover = brg.GetCoverThickness();
	Float64 es = Dr * pow(l / tlayer, 2) * rot_cyclic / (Nlay + (tcover >= 0.5 * tlayer ? 1 : 0));
	return es;
}

Float64 BearingCalculator::GetPrimaryShearStrainComboSum(const Bearing& brg, const BearingLoads& brg_loads) const
{
	Float64 D = GetStaticDisplacementPrimaryShearStrain(brg, brg_loads);
	Float64 es_axial = GetStaticAxialPrimaryShearStrain(brg, brg_loads);
	Float64 es_rot = GetStaticRotationalPrimaryShearStrain(brg, brg_loads);
	Float64 es_cyclic_disp = GetCyclicDisplacementPrimaryShearStrain(brg, brg_loads);
	Float64 es_cyclic_axial = GetCyclicAxialPrimaryShearStrain(brg, brg_loads);
	Float64 es_cyclic_rot = GetCyclicRotationalPrimaryShearStrain(brg, brg_loads);
	Float64 esXcombo_sum = D + es_axial + es_rot + 1.75 * (es_cyclic_disp + es_cyclic_axial + es_cyclic_rot);
	return  esXcombo_sum;
}

Float64 BearingCalculator::GetStaticDisplacementSecondaryShearStrain() const
{
	return 0;
}

Float64 BearingCalculator::GetCyclicDisplacementSecondaryShearStrain() const
{
	return 0;
}

Float64 BearingCalculator::GetStaticAxialSecondaryShearStrain(const Bearing& brg, const BearingLoads& brg_loads) const
{
	Float64 Da = GetSecondaryShearStrainAxialCoefficient(brg);
	Float64 sigma_static = GetStaticStress(brg, brg_loads);
	Float64 Gmin = brg.GetShearModulusMinimum();
	Float64 S = brg.GetShapeFactor();
	Float64 es = Da * sigma_static / Gmin / S;
	return es;
}

Float64 BearingCalculator::GetCyclicAxialSecondaryShearStrain(const Bearing& brg, const BearingLoads& brg_loads) const
{
	Float64 Da = GetSecondaryShearStrainAxialCoefficient(brg);
	Float64 sigma_cyclic = GetCyclicStress(brg, brg_loads);
	Float64 Gmin = brg.GetShearModulusMinimum();
	Float64 S = brg.GetShapeFactor();
	Float64 es = Da * sigma_cyclic / Gmin / S;
	return es;
}

Float64 BearingCalculator::GetStaticRotationalSecondaryShearStrain(const Bearing& brg, const BearingLoads& brg_loads) const
{
	Float64 Dr = GetSecondaryShearStrainRotationCoefficient(brg);
	Float64 w = brg.GetWidth();
	Float64 tlayer = brg.GetIntermediateLayerThickness();
	IndexType Nlay = brg.GetNumIntLayers();
	Float64 tcover = brg.GetCoverThickness();

	Float64 es = Dr * pow(w / tlayer, 2) * 0.01 / (Nlay + (tcover >= 0.5 * tlayer ? 1 : 0));
	return es;
}

Float64 BearingCalculator::GetCyclicRotationalSecondaryShearStrain(const Bearing& brg, const BearingLoads& brg_loads) const
{
	return 0;
}

Float64 BearingCalculator::GetSecondaryShearStrainComboSum(const Bearing& brg, const BearingLoads& brg_loads) const
{
	Float64 es_disp_static = GetStaticDisplacementSecondaryShearStrain();
	Float64 es_axial_static = GetStaticAxialSecondaryShearStrain(brg, brg_loads);
	Float64 es_rot_static = GetStaticRotationalSecondaryShearStrain(brg, brg_loads);
	Float64 es_disp_cyclic = GetCyclicDisplacementSecondaryShearStrain();
	Float64 es_axial_cyclic = GetCyclicAxialSecondaryShearStrain(brg, brg_loads);
	Float64 es_rot_cyclic = GetCyclicRotationalSecondaryShearStrain(brg, brg_loads);
	Float64 es = es_disp_static + es_axial_static + es_rot_static + 1.75 * (es_disp_cyclic + es_axial_cyclic + es_rot_cyclic);
	return es;
}



Float64 BearingCalculator::Getda1(const Bearing& brg) const ///da1
{
	Float64 i = brg.GetCompressibilityIndex();
	Float64 da1 = 1.06 + 0.210 * i + 0.413 * pow(i, 2);
	return da1;
}

Float64 BearingCalculator::Getda2(const Bearing& brg) const ///da2
{
	Float64 i = brg.GetCompressibilityIndex();
	Float64 da2 = 1.506 - 0.071 * i + 0.406 * pow(i, 2);
	return da2;
}

Float64 BearingCalculator::Getda3(const Bearing& brg) const ///da3
{
	Float64 i = brg.GetCompressibilityIndex();
	Float64 da3 = -0.315 + 0.195 * i - 0.047 * pow(i, 2);
	return da3;
}

Float64 BearingCalculator::GetPrimaryShearStrainAxialCoefficient(const Bearing& brg) const ///Dax
{
	Float64 da1 = Getda1(brg);
	Float64 da2 = Getda2(brg);
	Float64 da3 = Getda3(brg);
	Float64 l = brg.GetLength();
	Float64 w = brg.GetWidth();
	Float64 Da = max(da1, (da2 + da3 * l / w));
	return Da;
}

Float64 BearingCalculator::GetSecondaryShearStrainAxialCoefficient(const Bearing& brg) const ///Day
{
	Float64 da1 = Getda1(brg);
	Float64 da2 = Getda2(brg);
	Float64 da3 = Getda3(brg);
	Float64 l = brg.GetLength();
	Float64 w = brg.GetWidth();
	Float64 Da = max(da1, (da2 + da3 * w / l));
	return Da;
}

Float64 BearingCalculator::GetPrimaryShearStrainRotationCoefficient(const Bearing& brg) const ///Dr
{
	Float64 lambda = brg.GetCompressibilityIndex();
	Float64 l = brg.GetLength();
	Float64 w = brg.GetWidth();
	Float64 Dr = min((1.552 - 0.627 * lambda) / (2.233 + 0.156 * lambda + l / w), 0.5);
	return Dr;
}

Float64 BearingCalculator::GetSecondaryShearStrainRotationCoefficient(const Bearing& brg) const ///Dr
{
	Float64 lambda = brg.GetCompressibilityIndex();
	Float64 w = brg.GetWidth();
	Float64 l = brg.GetLength();
	Float64 Dr = min((1.552 - 0.627 * lambda) / (2.233 + 0.156 * lambda + w / l), 0.5);
	return Dr;
}

Float64 BearingCalculator::GetPeakHydrostaticStressCoefficient(const Bearing& brg) const //Ba
{
	Float64 lambda = brg.GetCompressibilityIndex();
	Float64 l = brg.GetLength();
	Float64 w = brg.GetWidth();
	Float64 Ba = (2.31 - 1.86 * lambda) + (-0.90 + 0.96 * lambda) * pow(1 - min(l / w, w / l), 2);
	return Ba;
}

Float64 BearingCalculator::GetStaticStress(const Bearing& brg, const BearingLoads& brg_loads) const
{
	Float64 DL = brg_loads.GetDeadLoad();
	Float64 A = brg.GetArea();
	Float64 sigma_static = DL/A;
	return sigma_static;
}

Float64 BearingCalculator::GetCyclicStress(const Bearing& brg, const BearingLoads& brg_loads) const
{
	Float64 LL = brg_loads.GetLiveLoad();
	Float64 A = brg.GetArea();
	Float64 sigma_cyclic = LL / A;
	return sigma_cyclic;
}

Float64 BearingCalculator::GetTotalStress(const Bearing& brg, const BearingLoads& brg_loads) const
{
	Float64 sigma_static = GetStaticStress(brg, brg_loads);
	Float64 sigma_cyclic = GetCyclicStress(brg, brg_loads);
	Float64 sigma_total = sigma_static + sigma_cyclic;
	return sigma_total;
}



Float64 BearingCalculator::GetElasticModulusCoefficient(const WBFL::LRFD::BDSManager::Edition& spec) const
{
	Float64 C = 6;
	if (spec >= SpecType::SixthEdition2012)
	{
		C = 4.8;
	}
	return C;
}


Float64 BearingCalculator::GetElastomerElasticModulusMethodB(const Bearing& brg, const WBFL::LRFD::BDSManager::Edition& spec) const
{
	Float64 Gmin = brg.GetShearModulusMinimum();
	Float64 S = brg.GetShapeFactor();
	Float64 Ecoeff = GetElasticModulusCoefficient(spec);
	Float64 EcMethodB = Ecoeff * Gmin * pow(S, 2);
	return EcMethodB;
}

Float64 BearingCalculator::GetTotalAxialStrain(const Bearing& brg, const BearingLoads& brg_loads) const //epsilon_a
{
	Float64 sigma_stress = GetStaticStress(brg, brg_loads);
	Float64 sigma_cyclic = GetCyclicStress(brg, brg_loads);
	Float64 sigma_hydrostatic = GetPeakHydrostaticStressCoefficient(brg);
	Float64 Gmin = brg.GetShearModulusMinimum();
	Float64 S = brg.GetShapeFactor();
	Float64 es_total = (sigma_stress + 1.75 * sigma_cyclic) / 3 / sigma_hydrostatic / Gmin / pow(S, 2);
	return es_total;
}

Float64 BearingCalculator::GetAlphaCoefficient(const Bearing& brg, const BearingLoads& brg_loads) const
{
	Float64 es_total = GetTotalAxialStrain(brg, brg_loads);
	IndexType Nlay = brg.GetNumIntLayers();
	Float64 tcover = brg.GetCoverThickness();
	Float64 tlayer = brg.GetIntermediateLayerThickness();
	Float64 alpha = es_total * (Nlay + (tcover >= 0.5 * tlayer ? 1 : 0)) / brg.GetShapeFactor() / (brg_loads.GetStaticRotation() + 1.75 * brg_loads.GetCyclicRotation());
	return alpha;
}

Float64 BearingCalculator::GetCaCoefficient(const Bearing& brg, const BearingLoads& brg_loads) const
{
	Float64 alpha = GetAlphaCoefficient(brg, brg_loads);
	Float64 Ca = 4.0 / 3 * (pow(pow(alpha, 2) + (1 / 3.0), 1.5) - alpha * (1 - pow(alpha, 2)));
	return Ca;
}

Float64 BearingCalculator::GetHydrostaticStress(const Bearing& brg, const BearingLoads& brg_loads) const
{
	Float64 Gmin = brg.GetShearModulusMinimum();
	Float64 S = brg.GetShapeFactor();
	Float64 r_static = brg_loads.GetStaticRotation();
	Float64 r_cyclic = brg_loads.GetCyclicRotation();
	IndexType Nlay = brg.GetNumIntLayers();
	Float64 tcover = brg.GetCoverThickness();
	Float64 tlayer = brg.GetIntermediateLayerThickness();
	Float64 Ca = GetCaCoefficient(brg, brg_loads);
	Float64 sigma_hydrostatic = 3 * Gmin * pow(S, 3) * (r_static + 1.75 * r_cyclic) / (Nlay + (tcover >= 0.5 * tlayer ? 1:0))*Ca;
	return sigma_hydrostatic;
}

Float64 BearingCalculator::GetRestraintSystemCDRatio(const Bearing& brg, const BearingLoads& brg_loads, const WBFL::LRFD::BDSManager::Edition& spec) const
{
	Float64 rot_static = brg_loads.GetStaticRotation();
	Float64 rot_cyclic = brg_loads.GetCyclicRotation();
	Float64 s = brg.GetShapeFactor();
	Float64 Ec = GetElastomerElasticModulusMethodB(brg, spec);
	IndexType n = brg.GetNumIntLayers();
	Float64 m = GetNlayMultiplier(brg);
	Float64 Sstatic = GetStaticStress(brg, brg_loads);
	Float64 Scyclic = GetCyclicStress(brg, brg_loads);
	Float64 restraint_system_calc = (rot_static + 1.75 * rot_cyclic) * s * Ec / 3.0 / (n + m)/(Sstatic + 1.75 * Scyclic);
	return restraint_system_calc;
}

Float64 BearingCalculator::GetHorizontalForce(const Bearing& brg, const BearingLoads& brg_loads) const
{
	Float64 Gmin = brg.GetShearModulusMinimum();
	Float64 A = brg.GetArea();
	Float64 shear_def = brg_loads.GetShearDeformation();
	Float64 hrt = brg.GetTotalElastomerThickness();
	Float64 horizontal_force = Gmin*A*shear_def/hrt;
	return horizontal_force;
}

BearingResults BearingCalculator::AnalyzeBearing(const Bearing& bearing, const BearingLoads& loads, 
	const BearingDesignCriteria& criteria) const
{
	const auto& spec = criteria.GetSpecification();

	BearingResults results;

	results.TotalLoadStress = GetTotalLoadStress(bearing, loads);
	results.ElastomerElasticModulusMethodA = GetElastomerElasticModulusMethodA(bearing, spec);
	results.StaticAxialPrimaryShearStrain = GetStaticAxialPrimaryShearStrain(bearing, loads);
	results.StaticAxialSecondaryShearStrain = GetStaticAxialSecondaryShearStrain(bearing, loads);
	results.PrimaryShearStrainComboSum = GetPrimaryShearStrainComboSum(bearing, loads);
	results.SecondaryShearStrainComboSum = GetSecondaryShearStrainComboSum(bearing, loads);
	results.TotalStress = GetTotalStress(bearing, loads);
	results.RestraintSystemDCRatio = GetRestraintSystemCDRatio(bearing, loads, spec);
	results.HydrostaticStress = GetHydrostaticStress(bearing, loads);
	results.HorizontalForce = GetHorizontalForce(bearing, loads);
	results.TotalBearingHeight = ComputeBearingHeight(bearing);
	results.InstantaneousLiveLoadDeflectionMethodA = GetInstantaneousLiveLoadDeflectionMethodA(bearing, loads, spec);
	results.InstantaneousLiveLoadDeflectionMethodB = GetInstantaneousLiveLoadDeflectionMethodB(bearing, loads, spec);

	return results;
};



BearingCheckArtifact BearingCalculator::CheckBearing(const Bearing& bearing, const BearingLoads& loads, 
	const BearingDesignCriteria& criteria) const
{
	BearingResults results = AnalyzeBearing(bearing, loads, criteria);

	BearingCheckArtifact artifact(bearing, loads, results, criteria);

	return artifact;
};


