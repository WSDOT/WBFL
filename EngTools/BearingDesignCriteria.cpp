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
#include <EngTools\BearingDesignCriteria.h>
#include <Units\Convert.h>
#include <MathEx.h>


using namespace WBFL::EngTools;



BearingDesignCriteria::BearingDesignCriteria()
{
}

WBFL::EngTools::BearingDesignCriteria::BearingDesignCriteria(
	const Bearing& bearing, const BearingLoads& loads, const WBFL::LRFD::BDSManager::Edition& spec)
	:m_bearing(bearing),
	m_loads(loads),
	m_spec(spec)
{
}

WBFL::EngTools::BearingDesignCriteria::BearingDesignCriteria(const Bearing& bearing, const BearingLoads& loads, 
	const WBFL::LRFD::BDSManager::Edition& spec, const BearingProjectCriteria& base)
	:m_bearing(bearing),
	m_loads(loads),
	m_spec(spec),
	BearingProjectCriteria(base)
{
}


BearingDesignCriteria::~BearingDesignCriteria()
{
}

const WBFL::LRFD::BDSManager::Edition& BearingDesignCriteria::GetSpecification() const
{
	return m_spec;
}

void BearingDesignCriteria::SetSpecification(const WBFL::LRFD::BDSManager::Edition& spec)
{
	m_spec = spec;
}


Float64 BearingDesignCriteria::GetSigmaMultiplier() const
{
	Float64 shear_def = m_loads.GetShearDeformation();
	return (shear_def == 0? 1.1:1.0);
}

Float64 BearingDesignCriteria::GetMinimumAllowableArea() const
{
	Float64 TL = m_loads.GetTotalLoad();
	Float64 sigma_max = MaximumAllowableStressMethodA;
	Float64 shear_delta = m_loads.GetShearDeformation();
	Float64 Amin = TL / (sigma_max * GetSigmaMultiplier());
	return Amin;
}

Float64 BearingDesignCriteria::GetMinimumAllowableLength() const
{
	Float64 Amin = GetMinimumAllowableArea();
	Float64 w = m_bearing.GetWidth();
	Float64 Lmin = Amin / w;
	return Lmin;
}

Float64 BearingDesignCriteria::GetMinimumAllowableWidth() const
{
	Float64 Amin = GetMinimumAllowableArea();
	Float64 l = m_bearing.GetLength();
	Float64 Wmin = Amin / l;
	return Wmin;
}

Float64 BearingDesignCriteria::GetMinimumAllowableShapeFactor() const
{
	Float64 TL = m_loads.GetTotalLoad();
	Float64 A = m_bearing.GetArea();
	Float64 sigma_TL = TL / A;
	Float64 Gmin = m_bearing.GetShearModulusMinimum();
	Float64 shear_delta = m_loads.GetShearDeformation();
	Float64 Smin = sigma_TL / (1.25 * Gmin * (shear_delta == 0 ? 1.1 : 1));
	return Smin;
}

Float64 BearingDesignCriteria::GetMaximumAllowableIntermediateLayerThickness() const
{
	Float64 l = m_bearing.GetLength();
	Float64 w = m_bearing.GetWidth();
	Float64 Smin = GetMinimumAllowableShapeFactor();
	Float64 tlayer_max = l * w / (2 * Smin * (l + w));
	return tlayer_max;
}

Float64 BearingDesignCriteria::GetMaximumAllowableShapeFactor() const
{
	IndexType Nlay = m_bearing.GetNumIntLayers();
	Float64 tcover = m_bearing.GetCoverThickness();
	Float64 tlay = m_bearing.GetIntermediateLayerThickness();
	Float64 Smax = sqrt(22 * (Nlay + (tcover >= 0.5 * tlay ? 1 : 0)));
	return Smax;
}

Float64 BearingDesignCriteria::GetMinimumAllowableNumLayersShearDeformation() const
{
	Float64 shear_delta = m_loads.GetShearDeformation();
	Float64 tcover = m_bearing.GetCoverThickness();
	Float64 tlay = m_bearing.GetIntermediateLayerThickness();
	Float64 Nlay_delta_shear = 2 * (shear_delta - tcover) / tlay;
	return Nlay_delta_shear;
}

Float64 BearingDesignCriteria::GetNumLayersRotationXCalc() const
{
	Float64 Gmax = m_bearing.GetShearModulusMaximum();
	Float64 S = m_bearing.GetShapeFactor();
	Float64 rx = m_loads.GetRotationX();
	Float64 TL = m_loads.GetTotalLoad();
	Float64 A = m_bearing.GetArea();
	Float64 sigma_TL = TL / A;
	Float64 l = m_bearing.GetLength();
	Float64 tlay = m_bearing.GetIntermediateLayerThickness();
	Float64 tcover = m_bearing.GetCoverThickness();
	Float64 n_lay_r_x = 0.5 * Gmax * S * rx / sigma_TL * pow(l / tlay, 2) - (tcover >= 0.5 * tlay ? 1 : 0);
	return n_lay_r_x;
}

Float64 BearingDesignCriteria::GetMinimumAllowableNumLayersRotationX() const
{
	Float64 Nlay_rx = max(0, GetNumLayersRotationXCalc());
	return Nlay_rx;
}

Float64 BearingDesignCriteria::GetNumLayersRotationYCalc() const
{
	Float64 Gmax = m_bearing.GetShearModulusMaximum();
	Float64 S = m_bearing.GetShapeFactor();
	Float64 ry = m_loads.GetRotationY();
	Float64 TL = m_loads.GetTotalLoad();
	Float64 A = m_bearing.GetArea();
	Float64 sigma_TL = TL / A;
	Float64 w = m_bearing.GetWidth();
	Float64 tlay = m_bearing.GetIntermediateLayerThickness();
	Float64 tcover = m_bearing.GetCoverThickness();
	Float64 n_lay_r_y = 0.5 * Gmax * S * ry / sigma_TL * pow(w / tlay, 2) - (tcover >= 0.5 * tlay ? 1 : 0);
	return n_lay_r_y;
}

Float64 BearingDesignCriteria::GetMinimumAllowableNumLayersRotationY() const
{
	Float64 Nlay_ry = max(0, GetNumLayersRotationYCalc());
	return Nlay_ry;
}

Float64 BearingDesignCriteria::GetMaximumAllowableNumLayersStabilityX() const
{
	Float64 l = m_bearing.GetLength();
	Float64 tcover = m_bearing.GetCoverThickness();
	Float64 tshim = m_bearing.GetSteelShimThickness();
	Float64 tlayer = m_bearing.GetIntermediateLayerThickness();
	Float64 Nlay_stabX = (l / 3 - 2 * tcover - tshim) / (tlayer + tshim);
	return Nlay_stabX;
}

Float64 BearingDesignCriteria::GetMaximumAllowableNumLayersStabilityY() const
{
	Float64 w = m_bearing.GetWidth();
	Float64 tcover = m_bearing.GetCoverThickness();
	Float64 tshim = m_bearing.GetSteelShimThickness();
	Float64 tlayer = m_bearing.GetIntermediateLayerThickness();
	Float64 Nlay_stabY = (w / 3 - 2 * tcover - tshim) / (tlayer + tshim);
	return Nlay_stabY;
}






Float64 BearingDesignCriteria::GetAbsoluteMinimumShimThickness() const
{
	if (m_spec >= Spec::TenthEdition2024)
	{
		return WBFL::Units::ConvertToSysUnits(0.0747, WBFL::Units::Measure::Inch);
	}
	else
	{
		return WBFL::Units::ConvertToSysUnits(0.0625, WBFL::Units::Measure::Inch);
	}
};

Float64 BearingDesignCriteria::GetMinimumElastomerCoverThickness() const
{
	if (m_spec >= Spec::TenthEdition2024)
	{
		return WBFL::Units::ConvertToSysUnits(0.25, WBFL::Units::Measure::Inch);
	}
	else
	{
		return WBFL::Units::ConvertToSysUnits(0.0, WBFL::Units::Measure::Inch);
	}
};

Float64 BearingDesignCriteria::GetMinimumAllowableSteelShimThicknessService() const
{
	Float64 tlayer = m_bearing.GetIntermediateLayerThickness();
	Float64 TL = m_loads.GetTotalLoad();
	Float64 A = m_bearing.GetArea();
	Float64 sigma_TL = TL / A;
	Float64 fy = m_bearing.GetYieldStrength();
	Float64 tshim_service = 3 * tlayer * sigma_TL / fy;
	return tshim_service;
};

Float64 BearingDesignCriteria::GetMinimumAllowableSteelShimThicknessFatigue() const
{
	Float64 tlayer = m_bearing.GetIntermediateLayerThickness();
	Float64 LL = m_loads.GetLiveLoad();
	Float64 A = m_bearing.GetArea();
	Float64 sigma_LL = LL / A;
	Float64 fth = m_bearing.GetFatigueThreshold();
	Float64 tshim_fatigue = 2 * tlayer * sigma_LL / fth;
	return tshim_fatigue;
};

Float64 BearingDesignCriteria::GetMaximumElastomerCoverThickness() const
{
	Float64 max_cover = 0.7 * m_bearing.GetIntermediateLayerThickness();

	if (m_spec >= Spec::TenthEdition2024)
	{
		max_cover = max(max_cover, WBFL::Units::ConvertToSysUnits(0.3125, WBFL::Units::Measure::Inch));
	}

	return max_cover;
};

Float64 BearingDesignCriteria::GetMaximumAllowableHydrostaticStress() const
{
	Float64 Gmin = m_bearing.GetShearModulusMinimum();
	Float64 sigma_max = 2.25 * Gmin;
	return sigma_max;
}

Float64 BearingDesignCriteria::GetPrimaryIntermediateCalculationA() const
{
	Float64 ttotal = m_bearing.GetTotalElastomerThickness();
	Float64 l = m_bearing.GetLength();
	Float64 w = m_bearing.GetWidth();
	Float64 Ax = 1.92 * ttotal / l / sqrt(1 + 2 * l / w);
	return Ax;
};

Float64 BearingDesignCriteria::GetSecondaryIntermediateCalculationA() const
{
	Float64 tlayer = m_bearing.GetTotalElastomerThickness();
	Float64 w = m_bearing.GetWidth();
	Float64 l = m_bearing.GetLength();
	Float64 Ay = 1.92 * tlayer / w / sqrt(1 + 2 * w / l);
	return Ay;
};

Float64 BearingDesignCriteria::GetPrimaryIntermediateCalculationB() const
{
	Float64 S = m_bearing.GetShapeFactor();
	Float64 l = m_bearing.GetLength();
	Float64 w = m_bearing.GetWidth();
	Float64 Bx = 2.67 / (S + 2) / (1 + l / 4 / w);
	return Bx;
};

Float64 BearingDesignCriteria::GetSecondaryIntermediateCalculationB() const
{
	Float64 S = m_bearing.GetShapeFactor();
	Float64 w = m_bearing.GetWidth();
	Float64 l = m_bearing.GetLength();
	Float64 By = 2.67 / (S + 2) / (1 + w / 4 / l);
	return By;
};

bool BearingDesignCriteria::CheckApplicabilityTotalStressStabilityX() const
{
	Float64 Gmin = m_bearing.GetShearModulusMinimum();
	Float64 S = m_bearing.GetShapeFactor();
	Float64 KeffX = m_loads.GetEffectiveKFactorX();
	Float64 Ax = GetPrimaryIntermediateCalculationA();
	Float64 Bx = GetPrimaryIntermediateCalculationB();
	if (Gmin * S / (KeffX * Ax - Bx) > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
};

bool BearingDesignCriteria::CheckApplicabilityTotalStressStabilityY() const
{
	Float64 Gmin = m_bearing.GetShearModulusMinimum();
	Float64 S = m_bearing.GetShapeFactor();
	Float64 KeffY = m_loads.GetEffectiveKFactorY();
	Float64 Ay = GetSecondaryIntermediateCalculationA();
	Float64 By = GetSecondaryIntermediateCalculationB();
	if (Gmin * S / (KeffY * Ay - By) > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
};

Float64 BearingDesignCriteria::GetAllowableTotalLoadStressStabilityX() const
{
	Float64 Gmin = m_bearing.GetShearModulusMinimum();
	Float64 S = m_bearing.GetShapeFactor();
	Float64 KeffX = m_loads.GetEffectiveKFactorX();
	Float64 Ax = GetPrimaryIntermediateCalculationA();
	Float64 Bx = GetPrimaryIntermediateCalculationB();
	Float64 sigmaTLstabX = Gmin * S / (KeffX * Ax - Bx);
	return sigmaTLstabX;
};

Float64 BearingDesignCriteria::GetAllowableTotalLoadStressStabilityY() const
{
	Float64 Gmin = m_bearing.GetShearModulusMinimum();
	Float64 S = m_bearing.GetShapeFactor();
	Float64 KeffY = m_loads.GetEffectiveKFactorY();
	Float64 Ay = GetSecondaryIntermediateCalculationA();
	Float64 By = GetSecondaryIntermediateCalculationB();
	Float64 sigmaTLstabY = Gmin * S / (KeffY * Ay - By);
	return sigmaTLstabY;
};
