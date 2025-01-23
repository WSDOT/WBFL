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





void BearingCalculator::SetMethodA(BearingCalculator::AnalysisMethodA method_a)
{
	m_method_a = method_a;
}
void BearingCalculator::SetMaximumAllowableStress(Float64 sigma_max)
{
	m_maximum_allowable_stress = sigma_max;
}
void BearingCalculator::SetAbsoluteMinimumShimThickness(Float64 tmin)
{
	m_absolute_minimum_shim_thickness = tmin;
}
void BearingCalculator::SetElastomerBulkModulus(Float64 k)
{
	m_elastomer_bulk_modulus = k;
}


BearingCalculator::AnalysisMethodA BearingCalculator::GetAnalysisMethodA() const
{
	return m_method_a;
}


Float64 BearingCalculator::GetMaximumAllowableStress() const
{
	return m_maximum_allowable_stress;
}

Float64 BearingCalculator::GetAbsoluteMinimumShimThickness() const
{
	return m_absolute_minimum_shim_thickness;
}

Float64 BearingCalculator::GetElastomerBulkModulus() const
{
	return m_elastomer_bulk_modulus;
}

Float64 BearingCalculator::GetElastomerElasticModulusMethodA(const Bearing& brg) const
{
	Float64 Gmin = brg.GetShearModulusMinimum();
	Float64 Gmax = brg.GetShearModulusMaximum();
	Float64 S = brg.GetShapeFactor();
	Float64 EcMethodA = 3 * (Gmin + Gmax) * pow(S, 2);
    return EcMethodA;
}

Float64 BearingCalculator::GetInitialDeadLoadDeflectionMethodA(const Bearing& brg, const BearingLoads& brg_loads) const
{
	Float64 DL = brg_loads.GetDeadLoad();
	Float64 ttotal = brg.GetTotalElastomerThickness();
	Float64 A = brg.GetArea();
	Float64 EcMethodA = GetElastomerElasticModulusMethodA(brg);
	Float64 deltaDLi = DL * ttotal / A / EcMethodA;
    return  deltaDLi;
}

Float64 BearingCalculator::GetInitialDeadLoadDeflectionMethodB(const Bearing& brg, const BearingLoads& brg_loads) const
{
	Float64 DL = brg_loads.GetDeadLoad();
	Float64 ttotal = brg.GetTotalElastomerThickness();
	Float64 A = brg.GetArea();
	Float64 EcMethodB = GetElastomerElasticModulusMethodB(brg);
	Float64 deltaDLi = DL * ttotal / A / EcMethodB;
	return  deltaDLi;
}

Float64 BearingCalculator::GetInstantaneousLiveLoadDeflectionMethodA(const Bearing& brg, const BearingLoads& brg_loads) const
{
	Float64 LL = brg_loads.GetLiveLoad();
	Float64 ttotal = brg.GetTotalElastomerThickness();
	Float64 A = brg.GetArea();
	Float64 EcMethodA = GetElastomerElasticModulusMethodA(brg);
	Float64 deltaLL = LL * ttotal / A / EcMethodA;
    return deltaLL;
}

Float64 BearingCalculator::GetInstantaneousLiveLoadDeflectionMethodB(const Bearing& brg, const BearingLoads& brg_loads) const
{
	Float64 LL = brg_loads.GetLiveLoad();
	Float64 ttotal = brg.GetTotalElastomerThickness();
	Float64 A = brg.GetArea();
	Float64 EcMethodB = GetElastomerElasticModulusMethodB(brg);
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

Float64 BearingCalculator::GetSigmaMultiplier(const BearingLoads& brg_loads) const
{
	Float64 shear_delta = brg_loads.GetShearDeformation();
	if (shear_delta == 0)
	{
		Float64 sigmaX = 1.1;
		return sigmaX;
	}
	else
	{
		Float64 sigmaX = 1.0;
		return sigmaX;
	}
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

Float64 BearingCalculator::GetMinimumAllowableArea(const Bearing& brg, const BearingLoads& brg_loads) const
{
	Float64 TL = brg_loads.GetTotalLoad();
	Float64 sigma_max = GetMaximumAllowableStress();
	Float64 shear_delta = brg_loads.GetShearDeformation();
	Float64 Amin = TL / (sigma_max * GetSigmaMultiplier(brg_loads));
	return Amin;
}

Float64 BearingCalculator::GetMinimumAllowableLength(const Bearing& brg, const BearingLoads& brg_loads) const
{
	Float64 Amin = GetMinimumAllowableArea(brg, brg_loads);
	Float64 w = brg.GetWidth();
	Float64 Lmin = Amin / w;
    return Lmin;
}

Float64 BearingCalculator::GetMinimumAllowableWidth(const Bearing& brg, const BearingLoads& brg_loads) const
{
	Float64 Amin = GetMinimumAllowableArea(brg, brg_loads);
	Float64 l = brg.GetLength();
	Float64 Wmin = Amin / l;
	return Wmin;
}

Float64 BearingCalculator::GetMinimumAllowableShapeFactor(const Bearing& brg, const BearingLoads& brg_loads) const
{
	Float64 sigmaTL = GetTotalLoadStress(brg, brg_loads);
	Float64 Gmin = brg.GetShearModulusMinimum();
	Float64 shear_delta = brg_loads.GetShearDeformation();
	Float64 Smin = sigmaTL / (1.25 * Gmin * (shear_delta == 0 ? 1.1 : 1));
	return Smin;
}

Float64 BearingCalculator::GetMaximumAllowableIntermediateLayerThickness(const Bearing& brg, const BearingLoads& brg_loads) const
{
	Float64 l = brg.GetLength();
	Float64 w = brg.GetWidth();
	Float64 Smin = GetMinimumAllowableShapeFactor(brg, brg_loads);
	Float64 tlayer_max = l * w / (2 * Smin * (l + w));
	return tlayer_max;
}

Float64 BearingCalculator::GetMaximumAllowableShapeFactor(const Bearing& brg, const BearingLoads& brg_loads) const
{
	IndexType Nlay = brg.GetNumIntLayers();
	Float64 tcover = brg.GetCoverThickness();
	Float64 tlay = brg.GetIntermediateLayerThickness();
	Float64 Smax = sqrt(22 * (Nlay + (tcover >= 0.5 * tlay ? 1 : 0)));
    return Smax;
}

Float64 BearingCalculator::GetMinimumAllowableNumLayersShearDeformation(const Bearing& brg, const BearingLoads& brg_loads) const
{
	Float64 shear_delta = brg_loads.GetShearDeformation();
	Float64 tcover = brg.GetCoverThickness();
	Float64 tlay = brg.GetIntermediateLayerThickness();
	Float64 Nlay_delta_shear = 2 * (shear_delta - tcover) / tlay;
	return Nlay_delta_shear;
}

Float64 BearingCalculator::GetNumLayersRotationXCalc(const Bearing& brg, const BearingLoads& brg_loads) const
{
	Float64 Gmax = brg.GetShearModulusMaximum();
	Float64 S = brg.GetShapeFactor();
	Float64 rx = brg_loads.GetRotationX();
	Float64 sigma_TL = GetTotalLoadStress(brg, brg_loads);
	Float64 l = brg.GetLength();
	Float64 tlay = brg.GetIntermediateLayerThickness();
	Float64 tcover = brg.GetCoverThickness();
	Float64 n_lay_r_x = 0.5 * Gmax * S * rx / sigma_TL * pow(l / tlay, 2) - (tcover >= 0.5 * tlay ? 1 : 0);
	return n_lay_r_x;
}

Float64 BearingCalculator::GetMinimumAllowableNumLayersRotationX(const Bearing& brg, const BearingLoads& brg_loads) const
{
	Float64 Nlay_rx = max(0, GetNumLayersRotationXCalc(brg,brg_loads));
	return Nlay_rx;
}

Float64 BearingCalculator::GetNumLayersRotationYCalc(const Bearing& brg, const BearingLoads& brg_loads) const
{
	Float64 Gmax = brg.GetShearModulusMaximum();
	Float64 S = brg.GetShapeFactor();
	Float64 ry = brg_loads.GetRotationY();
	Float64 sigma_TL = GetTotalLoadStress(brg, brg_loads);
	Float64 w = brg.GetWidth();
	Float64 tlay = brg.GetIntermediateLayerThickness();
	Float64 tcover = brg.GetCoverThickness();
	Float64 n_lay_r_y = 0.5 * Gmax * S * ry / sigma_TL * pow(w / tlay, 2) - (tcover >= 0.5 * tlay ? 1 : 0);
	return n_lay_r_y;
}

Float64 BearingCalculator::GetMinimumAllowableNumLayersRotationY(const Bearing& brg, const BearingLoads& brg_loads) const
{
	Float64 Nlay_ry = max(0, GetNumLayersRotationYCalc(brg, brg_loads));
	return Nlay_ry;
}

Float64 BearingCalculator::GetMaximumAllowableNumLayersStabilityX(const Bearing& brg, const BearingLoads& brg_loads) const
{
	Float64 l = brg.GetLength();
	Float64 tcover = brg.GetCoverThickness();
	Float64 tshim = brg.GetSteelShimThickness();
	Float64 tlayer = brg.GetIntermediateLayerThickness();
	Float64 Nlay_stabX = (l / 3 - 2 * tcover - tshim) / (tlayer + tshim);
    return Nlay_stabX;
}

Float64 BearingCalculator::GetMaximumAllowableNumLayersStabilityY(const Bearing& brg, const BearingLoads& brg_loads) const
{
	Float64 w = brg.GetWidth();
	Float64 tcover = brg.GetCoverThickness();
	Float64 tshim = brg.GetSteelShimThickness();
	Float64 tlayer = brg.GetIntermediateLayerThickness();
	Float64 Nlay_stabY = (w / 3 - 2 * tcover - tshim) / (tlayer + tshim);
    return Nlay_stabY;
}

Float64 BearingCalculator::GetMinimumAllowableSteelShimThicknessService(const Bearing& brg, const BearingLoads& brg_loads) const
{
	Float64 tlayer = brg.GetIntermediateLayerThickness();
	Float64 sigma_TL = GetTotalLoadStress(brg, brg_loads);
	Float64 fy = brg.GetYieldStrength();
	Float64 tshim_service = 3 * tlayer * sigma_TL / fy;
	return tshim_service;
}

Float64 BearingCalculator::GetMinimumAllowableSteelShimThicknessFatigue(const Bearing& brg, const BearingLoads& brg_loads) const
{
	Float64 tlayer = brg.GetIntermediateLayerThickness();
	Float64 sigma_LL = GetLiveLoadStress(brg, brg_loads);
	Float64 fth = brg.GetFatigueThreshold();
	Float64 tshim_fatigue = 2 * tlayer * sigma_LL / fth;
	return tshim_fatigue;
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

Float64 BearingCalculator::GetCompressibilityIndex(const Bearing& brg) const
{
	Float64 K = GetElastomerBulkModulus();
	Float64 S = brg.GetShapeFactor();
	Float64 Gmin = brg.GetShearModulusMinimum();
	Float64 lambda = S*sqrt(3*Gmin/K);
	return lambda;
}

Float64 BearingCalculator::Getda1(const Bearing& brg) const ///da1
{
	Float64 i = GetCompressibilityIndex(brg);
	Float64 da1 = 1.06 + 0.210 * i + 0.413 * pow(i, 2);
	return da1;
}

Float64 BearingCalculator::Getda2(const Bearing& brg) const ///da2
{
	Float64 i = GetCompressibilityIndex(brg);
	Float64 da2 = 1.506 - 0.071 * i + 0.406 * pow(i, 2);
	return da2;
}

Float64 BearingCalculator::Getda3(const Bearing& brg) const ///da3
{
	Float64 i = GetCompressibilityIndex(brg);
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
	Float64 lambda = GetCompressibilityIndex(brg);
	Float64 l = brg.GetLength();
	Float64 w = brg.GetWidth();
	Float64 Dr = min((1.552 - 0.627 * lambda) / (2.233 + 0.156 * lambda + l / w), 0.5);
	return Dr;
}

Float64 BearingCalculator::GetSecondaryShearStrainRotationCoefficient(const Bearing& brg) const ///Dr
{
	Float64 lambda = GetCompressibilityIndex(brg);
	Float64 w = brg.GetWidth();
	Float64 l = brg.GetLength();
	Float64 Dr = min((1.552 - 0.627 * lambda) / (2.233 + 0.156 * lambda + w / l), 0.5);
	return Dr;
}

Float64 BearingCalculator::GetPeakHydrostaticStressCoefficient(const Bearing& brg) const //Ba
{
	Float64 lambda = GetCompressibilityIndex(brg);
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

Float64 BearingCalculator::GetPrimaryIntermediateCalculationA(const Bearing& brg) const
{
	Float64 ttotal = brg.GetTotalElastomerThickness();
	Float64 l = brg.GetLength();
	Float64 w = brg.GetWidth();
	Float64 Ax = 1.92 * ttotal / l / sqrt(1 + 2 * l / w);
	return Ax;
}

Float64 BearingCalculator::GetSecondaryIntermediateCalculationA(const Bearing& brg) const
{
	Float64 tlayer = brg.GetTotalElastomerThickness();
	Float64 w = brg.GetWidth();
	Float64 l = brg.GetLength();
	Float64 Ay = 1.92 * tlayer / w / sqrt(1 + 2 * w / l);
	return Ay;
}

Float64 BearingCalculator::GetPrimaryIntermediateCalculationB(const Bearing& brg) const
{
	Float64 S = brg.GetShapeFactor();
	Float64 l = brg.GetLength();
	Float64 w = brg.GetWidth();
	Float64 Bx = 2.67 / (S + 2) / (1 + l / 4 / w);
	return Bx;
}

Float64 BearingCalculator::GetSecondaryIntermediateCalculationB(const Bearing& brg) const
{
	Float64 S = brg.GetShapeFactor();
	Float64 w = brg.GetWidth();
	Float64 l = brg.GetLength();
	Float64 By = 2.67 / (S + 2) / (1 + w / 4 / l);
	return By;
}

Float64 BearingCalculator::GetElastomerElasticModulusMethodB(const Bearing& brg) const
{
	Float64 Gmin = brg.GetShearModulusMinimum();
	Float64 S = brg.GetShapeFactor();
	Float64 EcMethodB = 6 * Gmin * pow(S, 2);
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

Float64 BearingCalculator::GetMaximumStress(const Bearing& brg) const
{
	Float64 Gmin = brg.GetShearModulusMinimum();
	Float64 sigma_max = 2.25 * Gmin;
	return sigma_max;
}

bool BearingCalculator::CheckApplicabilityTotalStressStabilityX(const Bearing& brg, const BearingLoads& brg_loads) const
{
	Float64 Gmin = brg.GetShearModulusMinimum();
	Float64 S = brg.GetShapeFactor();
	Float64 KeffX = brg_loads.GetEffectiveKFactorX();
	Float64 Ax = GetPrimaryIntermediateCalculationA(brg);
	Float64 Bx = GetPrimaryIntermediateCalculationB(brg);
	if (Gmin* S /(KeffX * Ax - Bx) > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool BearingCalculator::CheckApplicabilityTotalStressStabilityY(const Bearing& brg, const BearingLoads& brg_loads) const
{
	Float64 Gmin = brg.GetShearModulusMinimum();
	Float64 S = brg.GetShapeFactor();
	Float64 KeffY = brg_loads.GetEffectiveKFactorY();
	Float64 Ay = GetSecondaryIntermediateCalculationA(brg);
	Float64 By = GetSecondaryIntermediateCalculationB(brg);
	if (Gmin * S /(KeffY * Ay - By) > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

Float64 BearingCalculator::GetAllowableTotalLoadStressStabilityX(const Bearing& brg, const BearingLoads& brg_loads) const
{
	Float64 Gmin = brg.GetShearModulusMinimum();
	Float64 S = brg.GetShapeFactor();
	Float64 KeffX = brg_loads.GetEffectiveKFactorX();
	Float64 Ax = GetPrimaryIntermediateCalculationA(brg);
	Float64 Bx = GetPrimaryIntermediateCalculationB(brg);
	Float64 sigmaTLstabX = Gmin * S / (KeffX * Ax - Bx);
	return sigmaTLstabX;
}

Float64 BearingCalculator::GetAllowableTotalLoadStressStabilityY(const Bearing& brg, const BearingLoads& brg_loads) const
{
	Float64 Gmin = brg.GetShearModulusMinimum();
	Float64 S = brg.GetShapeFactor();
	Float64 KeffY = brg_loads.GetEffectiveKFactorY();
	Float64 Ay = GetSecondaryIntermediateCalculationA(brg);
	Float64 By = GetSecondaryIntermediateCalculationB(brg);
	Float64 sigmaTLstabY = Gmin * S / (KeffY * Ay - By);
	return sigmaTLstabY;
}

Float64 BearingCalculator::RestraintSystemCalc(const Bearing& brg, const BearingLoads& brg_loads) const
{
	Float64 rot_static = brg_loads.GetStaticRotation();
	Float64 rot_cyclic = brg_loads.GetCyclicRotation();
	Float64 s = brg.GetShapeFactor();
	Float64 Ec = GetElastomerElasticModulusMethodB(brg);
	IndexType n = brg.GetNumIntLayers();
	Float64 m = GetNlayMultiplier(brg);
	Float64 Sstatic = GetStaticStress(brg, brg_loads);
	Float64 Scyclic = GetCyclicStress(brg, brg_loads);
	Float64 restraint_system_calc = (rot_static + 1.75 * rot_cyclic) * s * Ec / 3.0 / (n + m)/(Sstatic + 1.75*Scyclic);
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

bool BearingCalculator::MinimumAreaCheck(const Bearing& brg, const BearingLoads& brg_loads) const
{
	if (brg.GetArea() >= GetMinimumAllowableArea(brg, brg_loads))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool BearingCalculator::MinimumLengthCheck(const Bearing& brg, const BearingLoads& brg_loads) const
{
	if (brg.GetLength() >= GetMinimumAllowableLength(brg, brg_loads))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool BearingCalculator::MinimumWidthCheck(const Bearing& brg, const BearingLoads& brg_loads) const
{
	if (brg.GetWidth() >= GetMinimumAllowableWidth(brg, brg_loads))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool BearingCalculator::MaximumStressCheck(const Bearing& brg, const BearingLoads& brg_loads) const
{
	if (GetTotalLoadStress(brg, brg_loads) <= GetMaximumAllowableStress())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool BearingCalculator::MaximumIntermediateLayerThicknessCheck(const Bearing& brg, const BearingLoads& brg_loads) const
{
	if (brg.GetIntermediateLayerThickness() <= GetMaximumAllowableIntermediateLayerThickness(brg, brg_loads))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool BearingCalculator::MinimumShapeFactorCheck(const Bearing& brg, const BearingLoads& brg_loads) const
{
	if (brg.GetShapeFactor() >= GetMinimumAllowableShapeFactor(brg, brg_loads))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool BearingCalculator::MaximumShapeFactorCheck(const Bearing& brg, const BearingLoads& brg_loads) const
{
	if (brg.GetShapeFactor() <= GetMaximumAllowableShapeFactor(brg, brg_loads))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool BearingCalculator::MinimumNumLayersShearDeformationCheck(const Bearing& brg, const BearingLoads& brg_loads) const
{
	if (brg.GetNumIntLayers() >= GetMinimumAllowableNumLayersShearDeformation(brg, brg_loads))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool BearingCalculator::MinimumNumLayersRotationXCheck(const Bearing& brg, const BearingLoads& brg_loads) const
{
	if (brg.GetNumIntLayers() >= GetMinimumAllowableNumLayersRotationX(brg, brg_loads))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool BearingCalculator::MinimumNumLayersRotationYCheck(const Bearing& brg, const BearingLoads& brg_loads) const
{
	if (brg.GetNumIntLayers() >= GetMinimumAllowableNumLayersRotationY(brg, brg_loads))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool BearingCalculator::MaximumNumLayersStabilityXCheck(const Bearing& brg, const BearingLoads& brg_loads) const
{
	if (brg.GetNumIntLayers() <= GetMaximumAllowableNumLayersStabilityX(brg, brg_loads))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool BearingCalculator::MaximumNumLayersStabilityYCheck(const Bearing& brg, const BearingLoads& brg_loads) const
{
	if (brg.GetNumIntLayers() <= GetMaximumAllowableNumLayersStabilityY(brg, brg_loads))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool BearingCalculator::MinimumSteelShimThicknessAbsoluteCheck(const Bearing& brg, const BearingLoads& brg_loads) const
{
	if (brg.GetSteelShimThickness() >= GetAbsoluteMinimumShimThickness())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool BearingCalculator::MinimumSteelShimThicknessServiceCheck(const Bearing& brg, const BearingLoads& brg_loads) const
{
	if (brg.GetSteelShimThickness() >= GetMinimumAllowableSteelShimThicknessService(brg, brg_loads))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool BearingCalculator::MinimumSteelShimThicknessFatigueCheck(const Bearing& brg, const BearingLoads& brg_loads) const
{
	if (brg.GetSteelShimThickness() >= GetMinimumAllowableSteelShimThicknessFatigue(brg, brg_loads))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool BearingCalculator::MaximumCompressiveStrainCheck(const Bearing& brg, const BearingLoads& brg_loads) const
{
	if (GetTotalLoadStress(brg, brg_loads) / GetElastomerElasticModulusMethodA(brg) <= 0.07)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool BearingCalculator::StaticRotationalPrimaryShearStrainCheck(const Bearing& brg, const BearingLoads& brg_load) const
{

	if (1.552-0.627*GetCompressibilityIndex(brg)/(2.233 + 0.156 * GetCompressibilityIndex(brg)*brg.GetLength()) >= 0.5)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool BearingCalculator::ShearDeformationCheck(const Bearing& brg, const BearingLoads& brg_loads) const
{
	if (brg.GetTotalElastomerThickness() >= 2 * brg_loads.GetShearDeformation())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool BearingCalculator::StaticAxialPrimaryShearStrainCheck(const Bearing& brg, const BearingLoads& brg_loads) const
{
	if (GetStaticAxialPrimaryShearStrain(brg, brg_loads) <= 3.0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool BearingCalculator::StaticAxialSecondaryShearStrainCheck(const Bearing& brg, const BearingLoads& brg_loads) const
{
	if (GetStaticAxialSecondaryShearStrain(brg, brg_loads) <= 3.0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool BearingCalculator::PrimaryShearStrainComboSumCheck(const Bearing& brg, const BearingLoads& brg_loads) const
{
	if (abs(GetPrimaryShearStrainComboSum(brg, brg_loads)) <= 5.0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool BearingCalculator::SecondaryShearStrainComboSumCheck(const Bearing& brg, const BearingLoads& brg_loads) const
{
	if (abs(GetSecondaryShearStrainComboSum(brg, brg_loads)) <= 5.0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool BearingCalculator::StabilityXDirectionCheck(const Bearing& brg, const BearingLoads& brg_loads) const
{
	if (GetTotalStress(brg, brg_loads) <= GetAllowableTotalLoadStressStabilityX(brg, brg_loads))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool BearingCalculator::StabilityYDirectionCheck(const Bearing& brg, const BearingLoads& brg_loads) const
{
	if (GetTotalStress(brg, brg_loads) <= GetAllowableTotalLoadStressStabilityY(brg, brg_loads))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool BearingCalculator::RestraintSystemRequirementCheck(const Bearing& brg, const BearingLoads& brg_loads) const
{
	if ( RestraintSystemCalc(brg,brg_loads) <= 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool BearingCalculator::HydrostaticStressCheck(const Bearing& brg, const BearingLoads& brg_loads) const
{
	if (GetMaximumStress(brg) >= GetHydrostaticStress(brg, brg_loads))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool BearingCalculator::HorizontalForceCheck(const Bearing& brg, const BearingLoads& brg_loads) const
{
	if (GetHorizontalForce(brg,brg_loads) <= brg_loads.GetDeadLoad()/5.0)

	{
		return true;
	}
	else
	{
		return false;
	}
}