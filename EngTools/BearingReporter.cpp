///////////////////////////////////////////////////////////////////////
// Stability
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

#include <EngTools/EngToolsLib.h>
#include <Reporter\Reporter.h>
#include <EngTools\BearingReporter.h>

using namespace WBFL::EngTools;

BearingReporter::BearingReporter()
{
}


void BearingReporter::ReportIntroduction(rptParagraph* pPara, const BearingCheckArtifact& artifact)
{

	const auto& criteria = artifact.GetBearingDesignCriteria();
	const auto& spec = criteria.GetSpecification();

	*pPara << color(Blue);
	*pPara << Bold(_T("-Calculations are based on ")) << WBFL::LRFD::BDSManager::GetEditionAsString(spec) << rptNewLine;
	*pPara << Bold(_T("-This Program is for rectangular-shaped bearings only")) << rptNewLine;
	*pPara << Bold(_T("-Shear strain due to rotation in secondary direction is based upon 0.010 radian out - of - plumb tolerance")) << rptNewLine;
	*pPara << Bold(_T("-Peak hydrostatic stress must be checked for bearings with externally bonded steel plates")) << rptNewLine;
	*pPara << Bold(_T("Bearing Orientation:")) << rptNewLine;
	*pPara << rptRcImage(std::_tstring(rptStyleManager::GetImagePath()) + _T("BearingOrientation.png")) << rptNewLine;
	*pPara << Bold(_T("-The primary rotation axis is about the axis parallel to the tranverse axis of the bridge")) << rptNewLine;
	*pPara << Bold(_T("-x, L are perpendicular; y,W are parallel, to the primary rotation axis. Usually W>L")) << rptNewLine << rptNewLine << rptNewLine;
}

void BearingReporter::ReportBearingProperties(const WBFL::Units::IndirectMeasure* pDispUnits,
	rptChapter* pChapter, rptParagraph* pPara, const BearingCheckArtifact& artifact)
{


	const BearingCalculator calc;
	const auto& brg = artifact.GetBearing();
	const auto& loads = artifact.GetBearingLoads();
	const auto& criteria = artifact.GetBearingDesignCriteria();
	const auto& spec = criteria.GetSpecification();


	Float64 l = brg.GetLength();
	Float64 w = brg.GetWidth();
	Float64 a = brg.GetArea();
	Float64 Gmin = brg.GetShearModulusMinimum();
	Float64 Gmax = brg.GetShearModulusMaximum();
	Float64 K = brg.GetElastomerBulkModulus();
	Float64 dl = loads.GetDeadLoad();
	Float64 ll = loads.GetLiveLoad();
	Float64 tl = loads.GetTotalLoad();
	Float64 ll_stress = calc.GetLiveLoadStress(brg, loads);
	Float64 tl_stress = calc.GetTotalLoadStress(brg, loads);
	Float64 fy = brg.GetYieldStrength();
	Float64 fth = brg.GetFatigueThreshold();
	Float64 Sstatic = calc.GetStaticStress(brg, loads);
	Float64 Scyclic = calc.GetCyclicStress(brg, loads);
	Float64 n_multiplier = calc.GetNlayMultiplier(brg);
	Float64 s = brg.GetShapeFactor();
	IndexType n = brg.GetNumIntLayers();
	Float64 tcover = brg.GetCoverThickness();
	Float64 sdef = loads.GetShearDeformation();
	Float64 static_rotation = loads.GetStaticRotation();
	Float64 cyclic_rotation = loads.GetCyclicRotation();
	Float64 x_rotation = loads.GetRotationX();
	Float64 y_rotation = loads.GetRotationY();
	Float64 total_elastomer_thickness = brg.GetTotalElastomerThickness();
	Float64 total_bearing_height = calc.ComputeBearingHeight(brg);
	Float64 tlayer = brg.GetIntermediateLayerThickness();
	Float64 tshim = brg.GetSteelShimThickness();
	Float64 weight = brg.GetBearingWeight();

	rptHeading* pHeading = rptStyleManager::CreateHeading(1);

	(*pChapter) << pHeading;
	pHeading->SetName(_T("Initial Parameters"));
	*pHeading << _T("Bearing Design Parameters");
	pPara = new rptParagraph;
	(*pChapter) << pPara;

	
	INIT_UV_PROTOTYPE(rptLengthUnitValue, length, pDispUnits->ComponentDim, true);
	INIT_UV_PROTOTYPE(rptAngleUnitValue, angle, pDispUnits->RadAngle, true);
	INIT_UV_PROTOTYPE(rptAreaUnitValue, area, pDispUnits->Area, true);
	INIT_UV_PROTOTYPE(rptForceUnitValue, force, pDispUnits->GeneralForce, true);
	INIT_UV_PROTOTYPE(rptStressUnitValue, stress, pDispUnits->Stress, true);
	INIT_UV_PROTOTYPE(rptStressUnitValue, E, pDispUnits->ModE, true);

	*pPara << _T("Area, A = ") << length.SetValue(l) << _T(" ") << symbol(TIMES) << length.SetValue(w) << _T(" = ") << area.SetValue(a) << rptNewLine;
	*pPara << _T("Total Elastomer Thickness, ") << Sub2(_T("h"), _T("rt")) << _T(" = 2 ") << symbol(TIMES) << _T(" ") << Sub2(_T("h"), _T("c")) << _T(" + n ");
	*pPara << symbol(TIMES) << Sub2(_T(" h"), _T("ri")) << _T(" = 2 ") << symbol(TIMES) << length.SetValue(tcover) << _T(" + ");
	*pPara << n << _T(" ") << symbol(TIMES) << length.SetValue(tlayer) << _T(" = ") << length.SetValue(total_elastomer_thickness) << rptNewLine;
	*pPara << _T("Shape Factor, S = A / (2 ") << symbol(TIMES) << _T(" ") << Sub2(_T("h"), _T("ri")) << _T(" ") << symbol(TIMES) << _T(" (L + W)) = ");
	*pPara << area.SetValue(a) << _T(" / (2 ") << symbol(TIMES) << _T(" ") << length.SetValue(tlayer) << _T(" ") << symbol(TIMES) << _T(" (");
	*pPara << length.SetValue(l) << _T(" + ") << length.SetValue(w) << _T(")) = ") << s << rptNewLine;
	*pPara << color(Blue);
	*pPara << _T("Summary:") << rptNewLine;
	*pPara << _T("Dimensions: ") << length.SetValue(w) << _T(" ") << symbol(TIMES) << length.SetValue(l);
	*pPara << _T(" ") << symbol(TIMES) << length.SetValue(total_bearing_height);
	*pPara << color(Blue) << rptNewLine;
	*pPara << _T("Approx. Weight = ");
	if (pDispUnits->Name == _T("English"))
	{
		*pPara << weight * 0.225 << _T(" lbs");
	}
	else
	{
		*pPara << weight << _T(" N");
	}
	*pPara << color(Blue) << rptNewLine << rptNewLine;

	length.ShowUnitTag(false);
	angle.ShowUnitTag(false);
	area.ShowUnitTag(false);
	force.ShowUnitTag(false);
	stress.ShowUnitTag(false);
	E.ShowUnitTag(false);

	rptRcTable* pTable = rptStyleManager::CreateDefaultTable(8, _T("Geometric Properties"));
	*pPara << pTable << rptNewLine;
	(*pTable)(0, 0) << COLHDR(_T("L"), rptLengthUnitTag, pDispUnits->ComponentDim);
	(*pTable)(1, 0) << length.SetValue(l);
	(*pTable)(0, 1) << COLHDR(_T("W"), rptLengthUnitTag, pDispUnits->ComponentDim);
	(*pTable)(1, 1) << length.SetValue(w);
	(*pTable)(0, 2) << COLHDR(_T("A"), rptAreaUnitTag, pDispUnits->Area);
	(*pTable)(1, 2) << area.SetValue(a);
	(*pTable)(0, 3) << Sub2(_T("N"), _T("lay"));
	(*pTable)(1, 3) << n;
	(*pTable)(0, 4) << COLHDR(Sub2(_T("h"), _T("ri")), rptLengthUnitTag, pDispUnits->ComponentDim);
	(*pTable)(1, 4) << length.SetValue(tlayer);
	(*pTable)(0, 5) << COLHDR(Sub2(_T("h"), _T("c")), rptLengthUnitTag, pDispUnits->ComponentDim);
	(*pTable)(1, 5) << length.SetValue(tcover);
	(*pTable)(0, 6) << COLHDR(Sub2(_T("h"), _T("rt")), rptLengthUnitTag, pDispUnits->ComponentDim);
	(*pTable)(1, 6) << length.SetValue(total_elastomer_thickness);
	(*pTable)(0, 7) << _T("S");
	(*pTable)(1, 7) << s;

	IndexType i = 4;
	if (criteria.AnalysisMethod == WBFL::EngTools::BearingAnalysisMethod::MethodA)
	{
		i = 5;
	}
	rptRcTable* pTable2 = rptStyleManager::CreateDefaultTable(i, _T("Design Properties"));

	*pPara << pTable2 << rptNewLine;
	(*pTable2)(0, 0) << COLHDR(_T("K"), rptStressUnitTag, pDispUnits->ModE);
	(*pTable2)(1, 0) << E.SetValue(K);
	(*pTable2)(0, 1) << COLHDR(Sub2(_T("F"), _T("y")), rptStressUnitTag, pDispUnits->ModE);
	(*pTable2)(1, 1) << E.SetValue(fy);
	(*pTable2)(0, 2) << COLHDR(Sub2(_T("F"), _T("th")), rptStressUnitTag, pDispUnits->ModE);
	(*pTable2)(1, 2) << E.SetValue(fth);
	(*pTable2)(0, 3) << COLHDR(Sub2(_T("G"), _T("min")), rptStressUnitTag, pDispUnits->ModE);
	(*pTable2)(1, 3) << E.SetValue(Gmin);

	if (criteria.AnalysisMethod == WBFL::EngTools::BearingAnalysisMethod::MethodA)
	{
		(*pTable2)(0, 4) << COLHDR(Sub2(_T("G"), _T("max")), rptStressUnitTag, pDispUnits->ModE);
		(*pTable2)(1, 4) << E.SetValue(Gmax);
	}


	rptRcTable* pTable3 = rptStyleManager::CreateDefaultTable(4, _T("Loads"));
	*pPara << pTable3 << rptNewLine;
	(*pTable3)(0, 0) << COLHDR(Sub2(_T("P"), _T("D")), rptForceUnitTag, pDispUnits->GeneralForce);
	(*pTable3)(1, 0) << force.SetValue(dl);
	(*pTable3)(0, 1) << COLHDR(Sub2(_T("P"), _T("L")), rptForceUnitTag, pDispUnits->GeneralForce);
	(*pTable3)(1, 1) << force.SetValue(ll);
	(*pTable3)(0, 2) << COLHDR(Sub2(_T("P"), _T("s")), rptForceUnitTag, pDispUnits->GeneralForce);
	(*pTable3)(1, 2) << force.SetValue(tl);
	(*pTable3)(0, 3) << COLHDR(Sub2(symbol(sigma), _T("s")), rptStressUnitTag, pDispUnits->Stress);
	(*pTable3)(1, 3) << stress.SetValue(tl_stress);

	rptRcTable* pTable4 = rptStyleManager::CreateDefaultTable(3, _T("Movements"));
	*pPara << pTable4 << rptNewLine;
	(*pTable4)(0, 0) << COLHDR(Sub2(symbol(DELTA), _T("s")), rptLengthUnitTag, pDispUnits->ComponentDim);
	(*pTable4)(1, 0) << length.SetValue(sdef);

	if (criteria.AnalysisMethod == WBFL::EngTools::BearingAnalysisMethod::MethodA)
	{
		(*pTable4)(0, 1) << COLHDR(Sub2(symbol(theta), _T("x")), rptAngleUnitTag, pDispUnits->RadAngle);
		(*pTable4)(1, 1) << angle.SetValue(x_rotation);
		(*pTable4)(0, 2) << COLHDR(Sub2(symbol(theta), _T("y")), rptAngleUnitTag, pDispUnits->RadAngle);
		(*pTable4)(1, 2) << angle.SetValue(y_rotation);
	}
	else
	{
		(*pTable4)(0, 1) << COLHDR(Sub2(symbol(theta), _T("st")), rptAngleUnitTag, pDispUnits->RadAngle);
		(*pTable4)(1, 1) << angle.SetValue(static_rotation);
		(*pTable4)(0, 2) << COLHDR(Sub2(symbol(theta), _T("cy")), rptAngleUnitTag, pDispUnits->RadAngle);
		(*pTable4)(1, 2) << angle.SetValue(cyclic_rotation);
	}

}


void CommonReportBearingSpecificationCheck(const WBFL::Units::IndirectMeasure* pDispUnits,
	rptChapter* pChapter, rptParagraph* pPara,
	const WBFL::EngTools::BearingCheckArtifact& artifact)
{

	const BearingCalculator brg_calc;
	const auto& brg = artifact.GetBearing();
	const auto& brg_loads = artifact.GetBearingLoads();
	const auto& criteria = artifact.GetBearingDesignCriteria();
	const auto& spec = criteria.GetSpecification();

	INIT_UV_PROTOTYPE(rptLengthUnitValue, length, pDispUnits->ComponentDim, true);
	INIT_UV_PROTOTYPE(rptStressUnitValue, stress, pDispUnits->Stress, true);
	INIT_UV_PROTOTYPE(rptForceUnitValue, force, pDispUnits->GeneralForce, true);

	Float64 n_multiplier = brg_calc.GetNlayMultiplier(brg);
	Float64 t_min_shim_absolute = criteria.GetAbsoluteMinimumShimThickness();
	Float64 tcover = brg.GetCoverThickness();
	bool t_min_shim_absolute_check = artifact.MinimumSteelShimThicknessAbsoluteCheck();
	Float64 tlayer = brg.GetIntermediateLayerThickness();
	Float64 tshim = brg.GetSteelShimThickness();
	Float64 fy = brg.GetYieldStrength();
	Float64 fth = brg.GetFatigueThreshold();
	Float64 t_min_shim_service = criteria.GetMinimumAllowableSteelShimThicknessService();
	Float64 tl_stress = brg_calc.GetTotalLoadStress(brg, brg_loads);
	Float64 ll_stress = brg_calc.GetLiveLoadStress(brg, brg_loads);
	bool t_min_shim_service_check = artifact.MinimumSteelShimThicknessServiceCheck();
	Float64 t_min_shim_fatigue = criteria.GetMinimumAllowableSteelShimThicknessFatigue();
	bool t_min_shim_fatigue_check = artifact.MinimumSteelShimThicknessFatigueCheck();
	Float64 t_min_cover = criteria.GetMinimumElastomerCoverThickness();
	Float64 t_max_cover = criteria.GetMaximumElastomerCoverThickness();
	bool t_min_cover_check = artifact.MinimumElastomerCoverThicknessCheck();
	bool t_max_cover_check = artifact.MaximumElastomerCoverThicknessCheck();
	bool gMin_check = artifact.MinimumAllowableShearModulusCheck();
	bool gMax_check = artifact.MaximumAllowableShearModulusCheck();
	Float64 total_bearing_height = brg_calc.ComputeBearingHeight(brg);
	bool hri_check = artifact.RequiredIntermediateElastomerThicknessCheck();
	bool height_check = artifact.MinimumTotalBearingHeightCheck();
	bool minDistBrg2gBfCheck = artifact.MinimumBearingEdgeToBottomFlangeEdgeDistCheck();
	bool maxDistBrg2gBfCheck = artifact.MaximumBearingEdgeToBottomFlangeEdgeDistCheck();
	bool distBrg2gBfCheck = artifact.RequiredBearingEdgeToBottomFlangeEdgeDistCheck();

	Float64 distBrg2gBf = brg.GetBearingToGirderFlangeDistance();

	Float64 tl = brg_loads.GetTotalLoad();
	bool maxTLcheck = artifact.MaximumTotalLoadCheck();

	rptHeading* pHeading = rptStyleManager::CreateHeading(1);
	(*pChapter) << pHeading;
	pHeading->SetName(_T("Details"));
	*pHeading << _T("Details");

	pPara = new rptParagraph;
	(*pChapter) << pPara;

	if (n_multiplier == 1)
	{
		*pPara << symbol(RIGHT_SINGLE_ARROW) << _T("0.5 ") << symbol(TIMES) << Sub2(_T(" h"), _T("ri"));
		*pPara << _T(" = 0.5 ") << symbol(TIMES) << _T(" ") << length.SetValue(tlayer) << _T(" = ") << length.SetValue(0.5 * tlayer) << rptNewLine;
		*pPara << symbol(RIGHT_SINGLE_ARROW) << Sub2(_T("h"), _T("c")) << _T(" = ") << length.SetValue(tcover) << (tcover == 0.5 * tlayer ? _T(" = ") : _T(" > ")) << length.SetValue(0.5 * tlayer);
		*pPara << symbol(RIGHT_SINGLE_ARROW) << symbol(eta) << _T(" = 1") << rptNewLine;
	}
	else
	{
		*pPara << symbol(RIGHT_SINGLE_ARROW) << _T("0.5 ") << symbol(TIMES) << Sub2(_T("h"), _T("ri"));
		*pPara << _T(" = 0.5 ") << symbol(TIMES) << length.SetValue(tlayer) << _T(" = ") << length.SetValue(0.5 * tlayer) << rptNewLine;
		*pPara << symbol(RIGHT_SINGLE_ARROW) << Sub2(_T("h"), _T("c")) << _T(" = ") << length.SetValue(tcover) << _T(" < ") << length.SetValue(0.5 * tlayer);
		*pPara << symbol(RIGHT_SINGLE_ARROW) << symbol(eta) << _T(" = 0") << rptNewLine;
	}

	rptHeading* pSubHeading = rptStyleManager::CreateSubHeading();
	(*pChapter) << pSubHeading;
	*pSubHeading << _T("Minimum Allowable Steel Shim Thickness Check:");

	pPara = new rptParagraph;
	(*pChapter) << pPara;

	*pPara << Sub2(_T("h"), _T("s,fab")) << _T(" = ") << length.SetValue(t_min_shim_absolute) << _T(" (Article 4.5, AASHTO M 251)") << rptNewLine;
	if (t_min_shim_absolute_check)
	{
		*pPara << symbol(RIGHT_SINGLE_ARROW) << length.SetValue(tshim) << (IsEqual(tshim, t_min_shim_absolute) ? _T(" = ") : _T(" > ")) << length.SetValue(t_min_shim_absolute);
		*pPara << _T(" ") << RPT_PASS;
	}
	else
	{
		*pPara << symbol(RIGHT_SINGLE_ARROW) << length.SetValue(tshim) << _T(" < ") << length.SetValue(t_min_shim_absolute);
		*pPara << _T(" ") << RPT_FAIL;
	}

	*pPara << rptNewLine << rptNewLine;


	*pPara << Sub2(_T("h"), _T("s,service")) << _T(" = ");

	*pPara << _T("3 ") << symbol(TIMES) << Sub2(_T(" h"), _T("ri ")) << symbol(TIMES) << _T(" ") << Sub2(symbol(sigma), _T("s")) << _T(" / ") << Sub2(_T("f"), _T("y"));
	*pPara << _T(" = 3 ") << symbol(TIMES) << _T(" ") << length.SetValue(tlayer) << _T(" ") << symbol(TIMES) << _T(" ") << stress.SetValue(tl_stress);
	*pPara << _T(" / ") << stress.SetValue(fy) << _T(" = ") << length.SetValue(t_min_shim_service) << rptNewLine;
	if (t_min_shim_service_check)
	{
		*pPara << symbol(RIGHT_SINGLE_ARROW) << length.SetValue(tshim) << _T(" > ") << length.SetValue(t_min_shim_service);
		*pPara << _T(" ") << RPT_PASS;
	}
	else
	{
		*pPara << symbol(RIGHT_SINGLE_ARROW) << length.SetValue(tshim) << _T(" < ") << length.SetValue(t_min_shim_service);
		*pPara << _T(" ") << RPT_FAIL;
	}
	*pPara << _T(" (14.7.5.3.5-1)");

	*pPara << rptNewLine << rptNewLine;

	*pPara << Sub2(_T("h"), _T("s,fatigue")) << _T(" = 2 ") << symbol(TIMES) << _T(" ") << Sub2(_T(" h"), _T("ri"));
	*pPara << symbol(TIMES) << _T(" ") << Sub2(symbol(sigma), _T("L")) << _T(" / ") << Sub2(_T("f"), _T("th"));
	*pPara << _T(" = 2 ") << symbol(TIMES) << _T(" ") << length.SetValue(tlayer) << symbol(TIMES) << stress.SetValue(ll_stress);
	*pPara << _T(" / ") << stress.SetValue(fth) << _T(" = ") << length.SetValue(t_min_shim_fatigue) << rptNewLine;
	if (t_min_shim_fatigue_check)
	{
		*pPara << symbol(RIGHT_SINGLE_ARROW) << length.SetValue(tshim) << _T(" > ") << length.SetValue(t_min_shim_fatigue);
		*pPara << _T(" ") << RPT_PASS;
	}
	else
	{
		*pPara << symbol(RIGHT_SINGLE_ARROW) << length.SetValue(tshim) << _T(" < ") << length.SetValue(t_min_shim_fatigue);
		*pPara << _T(" ") << RPT_FAIL;
	}
	*pPara << _T(" (14.7.5.3.5-2)") << rptNewLine;


	*pPara << rptNewLine;

	if (spec >= WBFL::LRFD::BDSManager::Edition::TenthEdition2024)
	{
		pSubHeading = rptStyleManager::CreateSubHeading();
		(*pChapter) << pSubHeading;
		*pSubHeading << _T("Minimum Allowable Elastomer Cover Thickness Check:");

		pPara = new rptParagraph;
		(*pChapter) << pPara;

		if (t_min_cover_check)
		{
			*pPara << symbol(RIGHT_SINGLE_ARROW) << length.SetValue(tcover) << (tcover == t_min_cover ? _T(" = ") : _T(" > ")) << length.SetValue(t_min_cover);
			*pPara << _T(" ") << RPT_PASS;
		}
		else
		{
			*pPara << symbol(RIGHT_SINGLE_ARROW) << length.SetValue(tcover) << _T(" < ") << length.SetValue(t_min_cover);
			*pPara << _T(" ") << RPT_FAIL;
		}

		*pPara << _T(" (14.7.5.1)") << rptNewLine << rptNewLine;
	}

	pSubHeading = rptStyleManager::CreateSubHeading();
	(*pChapter) << pSubHeading;
	*pSubHeading << _T("Maximum Allowable Elastomer Cover Thickness Check:");

	pPara = new rptParagraph;
	(*pChapter) << pPara;

	if (spec >= WBFL::LRFD::BDSManager::Edition::TenthEdition2024)
	{
		*pPara << Sub2(_T("h"), _T("c,max")) << _T(" = greater of 0.7") << symbol(TIMES) << Sub2(_T("h"), _T("c")) << _T(" and ");
		*pPara << length.SetValue(WBFL::Units::ConvertToSysUnits(0.3125, WBFL::Units::Measure::Inch)) << _T(" = ");
		*pPara << length.SetValue(t_max_cover) << rptNewLine;
	}
	else
	{
		*pPara << Sub2(_T("h"), _T("c,max")) << _T(" = 0.7") << symbol(TIMES) << Sub2(_T("h"), _T("c")) << _T(" = ");
		*pPara << length.SetValue(t_max_cover) << rptNewLine;
	}

	if (t_max_cover_check)
	{
		*pPara << symbol(RIGHT_SINGLE_ARROW) << length.SetValue(tcover) << (tcover == t_max_cover ? _T(" = ") : _T(" < ")) << length.SetValue(t_max_cover);
		*pPara << _T(" ") << RPT_PASS;
	}
	else
	{
		*pPara << symbol(RIGHT_SINGLE_ARROW) << length.SetValue(tcover) << _T(" > ") << length.SetValue(t_max_cover);
		*pPara << _T(" ") << RPT_FAIL;
	}

	*pPara << _T(" (14.7.5.1)") << rptNewLine << rptNewLine;

	if (criteria.bRequiredIntermediateElastomerThickness)
	{
		pSubHeading = rptStyleManager::CreateSubHeading();
		(*pChapter) << pSubHeading;
		*pSubHeading << _T("Required Intermediate Elastomer Layer Thickness Check:");

		pPara = new rptParagraph;
		(*pChapter) << pPara;


		*pPara << Sub2(_T("h"), _T("ri,rqd")) << _T(" = ") << length.SetValue(criteria.RequiredIntermediateElastomerThickness);
		if (hri_check)
		{
			*pPara << symbol(RIGHT_SINGLE_ARROW) << length.SetValue(tlayer) << _T(" = ") << length.SetValue(criteria.RequiredIntermediateElastomerThickness);
			*pPara << _T(" ") << RPT_PASS;
		}
		else
		{
			*pPara << symbol(RIGHT_SINGLE_ARROW) << length.SetValue(tlayer) << _T(" ") << symbol(NE) << length.SetValue(criteria.RequiredIntermediateElastomerThickness);
			*pPara << _T(" ") << RPT_FAIL;
		}

		*pPara << rptNewLine << rptNewLine;
	}

	if (criteria.bMinimumTotalBearingHeight)
	{
		pSubHeading = rptStyleManager::CreateSubHeading();
		(*pChapter) << pSubHeading;
		*pSubHeading << _T("Minimum Bearing Height Check:");

		pPara = new rptParagraph;
		(*pChapter) << pPara;


		*pPara << Sub2(_T("H"), _T("min")) << _T(" = ") << length.SetValue(criteria.MinimumTotalBearingHeight);
		if (height_check)
		{
			*pPara << symbol(RIGHT_SINGLE_ARROW) << length.SetValue(total_bearing_height) << _T(" ") << symbol(GTE) << length.SetValue(criteria.MinimumTotalBearingHeight);
			*pPara << _T(" ") << RPT_PASS;
		}
		else
		{
			*pPara << symbol(RIGHT_SINGLE_ARROW) << length.SetValue(total_bearing_height) << _T(" ") << length.SetValue(criteria.MinimumTotalBearingHeight);
			*pPara << _T(" ") << RPT_FAIL;
		}

		*pPara << rptNewLine << rptNewLine;

	}



	if (criteria.bRequiredBearingEdgeToGirderEdgeDistance || 
		criteria.bMinimumBearingEdgeToGirderEdgeDistance || 
		criteria.bMaximumBearingEdgeToGirderEdgeDistance)
	{
		pSubHeading = rptStyleManager::CreateSubHeading();
		(*pChapter) << pSubHeading;
		*pSubHeading << _T("Girder Edge to Bearing Edge Distance Check:");

		pPara = new rptParagraph;
		(*pChapter) << pPara;

		if (criteria.bRequiredBearingEdgeToGirderEdgeDistance)
		{

			*pPara << _T("Required Distance from Edge of Bearing to Edge of Girder Bottome Flange = ") << length.SetValue(distBrg2gBf);
			if (distBrg2gBfCheck)
			{
				*pPara << symbol(RIGHT_SINGLE_ARROW) << length.SetValue(distBrg2gBf) << _T(" = ") << length.SetValue(distBrg2gBf);
				*pPara << _T(" ") << RPT_PASS;
			}
			else
			{
				*pPara << symbol(RIGHT_SINGLE_ARROW) << length.SetValue(distBrg2gBf) << _T(" ") << symbol(NE) << length.SetValue(distBrg2gBf);
				*pPara << _T(" ") << RPT_FAIL;
			}

			*pPara << rptNewLine;

		}

		if (criteria.bMinimumBearingEdgeToGirderEdgeDistance)
		{

			*pPara << _T("Minimum Required Distance from Edge of Bearing to Edge of Girder Bottome Flange = ") << length.SetValue(criteria.MinimumBearingEdgeToGirderEdgeDistance);
			if (minDistBrg2gBfCheck)
			{
				*pPara << symbol(RIGHT_SINGLE_ARROW) << length.SetValue(distBrg2gBf) << _T(" ") << symbol(GTE) << length.SetValue(criteria.MinimumBearingEdgeToGirderEdgeDistance);
				*pPara << _T(" ") << RPT_PASS;
			}
			else
			{
				*pPara << symbol(RIGHT_SINGLE_ARROW) << length.SetValue(distBrg2gBf) << _T(" < ") << length.SetValue(criteria.MinimumBearingEdgeToGirderEdgeDistance);
				*pPara << _T(" ") << RPT_FAIL;
			}

			*pPara << rptNewLine;

		}

		if (criteria.bMaximumBearingEdgeToGirderEdgeDistance)
		{

			*pPara << _T("Maximum Distance from Edge of Bearing to Edge of Girder Bottome Flange = ") << length.SetValue(criteria.MaximumBearingEdgeToGirderEdgeDistance);
			if (maxDistBrg2gBfCheck)
			{
				*pPara << symbol(RIGHT_SINGLE_ARROW) << length.SetValue(distBrg2gBf) << _T(" ") << symbol(LTE) << _T(" ") << length.SetValue(criteria.MaximumBearingEdgeToGirderEdgeDistance);
				*pPara << _T(" ") << RPT_PASS;
			}
			else
			{
				*pPara << symbol(RIGHT_SINGLE_ARROW) << length.SetValue(distBrg2gBf) << _T(" > ") << length.SetValue(criteria.MaximumBearingEdgeToGirderEdgeDistance);
				*pPara << _T(" ") << RPT_FAIL;
			}

			*pPara << rptNewLine;

		}

		*pPara  << rptNewLine;

	}


	if (criteria.bMaximumTotalLoad)
	{
		pSubHeading = rptStyleManager::CreateSubHeading();
		(*pChapter) << pSubHeading;
		*pSubHeading << _T("Maximum Total Vertical Load Check:");

		pPara = new rptParagraph;
		(*pChapter) << pPara;


		*pPara << _T("Total Load Limit = ") << force.SetValue(criteria.MaximumTotalLoad);
		if (maxTLcheck)
		{
			*pPara << symbol(RIGHT_SINGLE_ARROW) << force.SetValue(tl) << _T(" ") << symbol(LTE) << force.SetValue(criteria.MaximumTotalLoad);
			*pPara << _T(" ") << RPT_PASS;						   
		}														   
		else													   
		{														   
			*pPara << symbol(RIGHT_SINGLE_ARROW) << force.SetValue(tl) << _T(" > ") << force.SetValue(criteria.MaximumTotalLoad);
			*pPara << _T(" ") << RPT_FAIL;
		}

		*pPara << rptNewLine << rptNewLine;

	}
	

}

void BearingReporter::ReportBearingSpecCheckSummaryA(rptChapter* pChapter, rptParagraph* pPara,
	const WBFL::EngTools::BearingCheckArtifact& artifact)
{

	const auto& criteria = artifact.GetBearingDesignCriteria();
	const auto& spec = criteria.GetSpecification();

	bool w_min_check = artifact.MinimumWidthCheck();
	bool l_min_check = artifact.MinimumLengthCheck();
	bool a_min_check = artifact.MinimumAreaCheck();
	bool tlayer_max_check = artifact.MaximumIntermediateLayerThicknessCheck();
	bool t_min_shim_absolute_check = artifact.MinimumSteelShimThicknessAbsoluteCheck();
	bool t_min_cover_check = artifact.MinimumElastomerCoverThicknessCheck();
	bool t_max_cover_check = artifact.MaximumElastomerCoverThicknessCheck();
	bool s_min_check = artifact.MinimumShapeFactorCheck();
	bool s_max_check = artifact.MaximumShapeFactorCheck();
	bool n_min_shear_def_check = artifact.MinimumNumLayersShearDeformationCheck();
	bool n_min_rot_x_check = artifact.MinimumNumLayersRotationXCheck();
	bool n_min_rot_y_check = artifact.MinimumNumLayersRotationYCheck();
	bool n_max_stab_x_check = artifact.MaximumNumLayersStabilityXCheck();
	bool n_max_stab_y_check = artifact.MaximumNumLayersStabilityYCheck();
	bool t_min_shim_service_check = artifact.MinimumSteelShimThicknessServiceCheck();
	bool t_min_shim_fatigue_check = artifact.MinimumSteelShimThicknessFatigueCheck();
	bool max_comp_strain_check = artifact.MaximumCompressiveStrainCheck();
	bool max_stress_check = artifact.MaximumStressCheck();
	auto deltaLLiACheck = artifact.MaximumLiveLoadDeflectionMethodACheck();
	bool gMin_check = artifact.MinimumAllowableShearModulusCheck();
	bool gMax_check = artifact.MaximumAllowableShearModulusCheck();
	bool hri_check = artifact.RequiredIntermediateElastomerThicknessCheck();
	bool height_check = artifact.MinimumTotalBearingHeightCheck();
	bool minDistBrg2gBfCheck = artifact.MinimumBearingEdgeToBottomFlangeEdgeDistCheck();
	bool maxDistBrg2gBfCheck = artifact.MaximumBearingEdgeToBottomFlangeEdgeDistCheck();
	bool distBrg2gBfCheck = artifact.RequiredBearingEdgeToBottomFlangeEdgeDistCheck();
	bool maxTLCheck = artifact.MaximumTotalLoadCheck();

	pPara = new rptParagraph;
	(*pChapter) << pPara;

	if (!t_min_shim_absolute_check || !t_max_cover_check || !t_min_shim_service_check
		|| !t_min_shim_fatigue_check || !w_min_check || !l_min_check
		|| !a_min_check || !tlayer_max_check || !s_min_check || !s_max_check || !n_min_shear_def_check
		|| (spec >= WBFL::LRFD::BDSManager::Edition::TenthEdition2024 ? !t_min_cover_check : false)
		|| (spec < WBFL::LRFD::BDSManager::Edition::SixthEdition2012 ? !n_min_rot_x_check : false)
		|| (spec < WBFL::LRFD::BDSManager::Edition::SixthEdition2012 ? !n_min_rot_y_check : false)
		|| !n_max_stab_x_check || !n_max_stab_y_check || !max_comp_strain_check || !max_stress_check
		|| !deltaLLiACheck || !gMin_check || !gMax_check || (criteria.bRequiredIntermediateElastomerThickness ? !hri_check : false)
		|| (criteria.bMinimumTotalBearingHeight ? !height_check : false)
		|| (criteria.bMinimumBearingEdgeToGirderEdgeDistance ? !minDistBrg2gBfCheck : false)
		|| (criteria.bMaximumBearingEdgeToGirderEdgeDistance ? !maxDistBrg2gBfCheck : false)
		|| (criteria.bRequiredBearingEdgeToGirderEdgeDistance ? !distBrg2gBfCheck : false)
		|| (criteria.bMaximumTotalLoad ? !maxTLCheck : false))

	{
		*pPara << color(Red);
		if (!t_min_shim_absolute_check)
		{
			*pPara << _T("Steel shim thickness is less than required for fabrication.") << rptNewLine;
		}
		if (!t_min_cover_check && spec >= WBFL::LRFD::BDSManager::Edition::TenthEdition2024)
		{
			*pPara << _T("Elastomer cover thickness is below the minimum thickness limit.") << rptNewLine;
		}
		if (!t_max_cover_check)
		{
			*pPara << _T("Elastomer cover thickness exceeds the maximum thickness limit.") << rptNewLine;
		}
		if (!t_min_shim_service_check)
		{
			*pPara << _T("Steel shim thickness is not sufficient to resist service loads.") << rptNewLine;
		}
		if (!t_min_shim_fatigue_check)
		{
			*pPara << _T("Steel shim thickness is not sufficient to resist fatigue loads.") << rptNewLine;
		}
		if (!w_min_check)
		{
			*pPara << _T("Bearing width is not sufficient for design.") << rptNewLine;
		}
		if (!l_min_check)
		{
			*pPara << _T("Bearing length is not sufficient for design.") << rptNewLine;
		}
		if (!a_min_check)
		{
			*pPara << _T("Bearing area is not sufficient for design.") << rptNewLine;
		}
		if (!tlayer_max_check)
		{
			*pPara << _T("Elastomer exceeds the maximum thickness limit.") << rptNewLine;
		}
		if (!s_min_check)
		{
			*pPara << _T("Bearing shape factor is not sufficient for design.") << rptNewLine;
		}
		if (!s_max_check)
		{
			*pPara << _T("Bearing exceeds the maximum shape factor.") << rptNewLine;
		}
		if (!n_min_shear_def_check)
		{
			*pPara << _T("Number of elastomer layers is not sufficient to accommodate shear deformation.") << rptNewLine;
		}
		if (!n_min_rot_x_check && spec < WBFL::LRFD::BDSManager::Edition::SixthEdition2012)
		{
			*pPara << _T("Number of elastomer layers is not sufficient to accommodate flexural rotation.") << rptNewLine;
		}
		if (!n_min_rot_y_check && spec < WBFL::LRFD::BDSManager::Edition::SixthEdition2012)
		{
			*pPara << _T("Number of elastomer layers is not sufficient to accommodate torsional rotation.") << rptNewLine;
		}
		if (!n_max_stab_x_check)
		{
			*pPara << _T("Number of elastomer layers exceeds the maximum number of layers for stability in the primary direction (longitudinal to the bridge).") << rptNewLine;
		}
		if (!n_max_stab_y_check)
		{
			*pPara << _T("Number of elastomer layers exceeds the maximum number of layers for stability in the secondary direction (transverse to the bridge).") << rptNewLine;
		}
		if (!max_comp_strain_check)
		{
			*pPara << _T("Elastomer exceeds maximum the compressive strain limit.") << rptNewLine;
		}
		if (!max_stress_check)
		{
			*pPara << _T("The maximum stress limit is exceeded.") << rptNewLine;
		}
		if (!deltaLLiACheck)
		{
			*pPara << _T("Instantaneous live load deflection exceeds the recommended limit.") << rptNewLine;
		}
		if (!gMin_check)
		{
			*pPara << _T("Specifed elastomer shear modulus range is below the minimum limit.") << rptNewLine;
		}
		if (!gMax_check)
		{
			*pPara << _T("Specifed elastomer shear modulus range exceeds the maximum limit.") << rptNewLine;
		}
		if (criteria.bRequiredIntermediateElastomerThickness && !hri_check)
		{
			*pPara << _T("Input for intermediate elastomer thickness does not equal the required thickness.") << rptNewLine;
		}
		if (criteria.bMinimumTotalBearingHeight && !height_check)
		{
			*pPara << _T("Total bearing height is below the minimum limit.") << rptNewLine;
		}
		if (criteria.bMinimumBearingEdgeToGirderEdgeDistance && !minDistBrg2gBfCheck)
		{
			*pPara << _T("Distance from edge of bearing to edge of girder bottom flange is less than the minimum limit.") << rptNewLine;
		}
		if (criteria.bMaximumBearingEdgeToGirderEdgeDistance && !maxDistBrg2gBfCheck)
		{
			*pPara << _T("Distance from edge of bearing to edge of girder bottom flange exceeds the maximum limit.") << rptNewLine;
		}
		if (criteria.bRequiredBearingEdgeToGirderEdgeDistance && !distBrg2gBfCheck)
		{
			*pPara << _T("Distance from edge of bearing to edge of girder bottom flange does not equal the required distance.") << rptNewLine;
		}
		if (criteria.bMaximumTotalLoad && !maxTLCheck)
		{
			*pPara << _T("The total vertical load exceeds the maximum limit.") << rptNewLine;
		}

		*pPara << color(Red) << rptNewLine << rptNewLine;

	}
	else
	{
		*pPara << color(Green) << _T("Bearing design per Method A was successful.") << color(Green) << rptNewLine << rptNewLine;
	}
}

void BearingReporter::ReportBearingSpecificationCheckA(const WBFL::Units::IndirectMeasure* pDispUnits,
	rptChapter* pChapter, rptParagraph* pPara,
	const WBFL::EngTools::BearingCheckArtifact& artifact)
{
	INIT_UV_PROTOTYPE(rptLengthUnitValue, length, pDispUnits->ComponentDim, true);
	INIT_UV_PROTOTYPE(rptAreaUnitValue, area, pDispUnits->Area, true);
	INIT_UV_PROTOTYPE(rptForceUnitValue, force, pDispUnits->GeneralForce, true);
	INIT_UV_PROTOTYPE(rptStressUnitValue, stress, pDispUnits->Stress, true);
	INIT_UV_PROTOTYPE(rptStressUnitValue, E, pDispUnits->ModE, true);

	const BearingCalculator brg_calc;
	const auto& brg = artifact.GetBearing();
	const auto& brg_loads = artifact.GetBearingLoads();
	const auto& criteria = artifact.GetBearingDesignCriteria();
	const auto& spec = criteria.GetSpecification();

	Float64 l = brg.GetLength();
	Float64 w = brg.GetWidth();
	Float64 a = brg.GetArea();
	Float64 Gmin = brg.GetShearModulusMinimum();
	Float64 Gmax = brg.GetShearModulusMaximum();
	Float64 K = brg.GetElastomerBulkModulus();
	Float64 dl = brg_loads.GetDeadLoad();
	Float64 ll = brg_loads.GetLiveLoad();
	Float64 tl = brg_loads.GetTotalLoad();
	Float64 ll_stress = brg_calc.GetLiveLoadStress(brg, brg_loads);
	Float64 tl_stress = brg_calc.GetTotalLoadStress(brg, brg_loads);

	Float64 n_multiplier = brg_calc.GetNlayMultiplier(brg);
	Float64 s = brg.GetShapeFactor();
	IndexType n = brg.GetNumIntLayers();
	Float64 tcover = brg.GetCoverThickness();
	Float64 sdef = brg_loads.GetShearDeformation();

	Float64 x_rotation = brg_loads.GetRotationX();
	Float64 y_rotation = brg_loads.GetRotationY();
	Float64 total_elastomer_thickness = brg.GetTotalElastomerThickness();
	Float64 tlayer = brg.GetIntermediateLayerThickness();
	Float64 tshim = brg.GetSteelShimThickness();

	Float64 w_min = criteria.GetMinimumAllowableWidth();
	bool w_min_check = artifact.MinimumWidthCheck();
	Float64 l_min = criteria.GetMinimumAllowableLength();
	bool l_min_check = artifact.MinimumLengthCheck();

	Float64 EcA = brg_calc.GetElastomerElasticModulusMethodA(brg, spec);
	Float64 Ecoeff = brg_calc.GetElasticModulusCoefficient(spec);

	Float64 smax = criteria.MaximumAllowableStressMethodA;
	Float64 smax_multiplier = criteria.GetSigmaMultiplier();

	Float64 a_min = criteria.GetMinimumAllowableArea();
	bool a_min_check = artifact.MinimumAreaCheck();

	Float64 tlayer_max = criteria.GetMaximumAllowableIntermediateLayerThickness();
	bool tlayer_max_check = artifact.MaximumIntermediateLayerThicknessCheck();

	bool t_min_shim_absolute_check = artifact.MinimumSteelShimThicknessAbsoluteCheck();
	bool t_min_cover_check = artifact.MinimumElastomerCoverThicknessCheck();
	bool t_max_cover_check = artifact.MaximumElastomerCoverThicknessCheck();

	Float64 s_min = criteria.GetMinimumAllowableShapeFactor();
	bool s_min_check = artifact.MinimumShapeFactorCheck();
	Float64 s_max = criteria.GetMaximumAllowableShapeFactor();
	bool s_max_check = artifact.MaximumShapeFactorCheck();

	Float64 n_min_shear_def    = criteria.GetMinimumAllowableNumLayersShearDeformation();
	bool n_min_shear_def_check = artifact.MinimumNumLayersShearDeformationCheck();
	Float64 n_lay_r_x_calc     = criteria.GetNumLayersRotationXCalc();
	Float64 n_min_rot_x        = criteria.GetMinimumAllowableNumLayersRotationX();
	bool n_min_rot_x_check     = artifact.MinimumNumLayersRotationXCheck();
	Float64 n_lay_r_y_calc     = criteria.GetNumLayersRotationYCalc();
	Float64 n_min_rot_y        = criteria.GetMinimumAllowableNumLayersRotationY();
	bool n_min_rot_y_check     = artifact.MinimumNumLayersRotationYCheck();
	Float64 n_max_stab_x       = criteria.GetMaximumAllowableNumLayersStabilityX();
	bool n_max_stab_x_check    = artifact.MaximumNumLayersStabilityXCheck();
	Float64 n_max_stab_y       = criteria.GetMaximumAllowableNumLayersStabilityY();
	bool n_max_stab_y_check    = artifact.MaximumNumLayersStabilityYCheck();
	bool t_min_shim_service_check = artifact.MinimumSteelShimThicknessServiceCheck();
	bool t_min_shim_fatigue_check = artifact.MinimumSteelShimThicknessFatigueCheck();
	bool max_comp_strain_check = artifact.MaximumCompressiveStrainCheck();
	Float64 total_stress = brg_calc.GetTotalStress(brg, brg_loads);
	bool max_stress_check = artifact.MaximumStressCheck();
	auto deltaDLiA = brg_calc.GetInitialDeadLoadDeflectionMethodA(brg, brg_loads, spec);
	auto deltaLLiA = brg_calc.GetInstantaneousLiveLoadDeflectionMethodA(brg, brg_loads, spec);
	auto deltaLLiACheck = artifact.MaximumLiveLoadDeflectionMethodACheck();
	bool gMin_check = artifact.MinimumAllowableShearModulusCheck();
	bool gMax_check = artifact.MaximumAllowableShearModulusCheck();
	bool hri_check = artifact.RequiredIntermediateElastomerThicknessCheck();
	bool height_check = artifact.MinimumTotalBearingHeightCheck();
	bool minDistBrg2gBfCheck = artifact.MinimumBearingEdgeToBottomFlangeEdgeDistCheck();
	bool maxDistBrg2gBfCheck = artifact.MaximumBearingEdgeToBottomFlangeEdgeDistCheck();
	bool distBrg2gBfCheck = artifact.RequiredBearingEdgeToBottomFlangeEdgeDistCheck();
	bool maxTLCheck = artifact.MaximumTotalLoadCheck();	

	CommonReportBearingSpecificationCheck(pDispUnits, pChapter, pPara, artifact);

	rptHeading* pHeading = rptStyleManager::CreateHeading();
	(*pChapter) << pHeading;
	pHeading->SetName(_T("Method A Analysis:"));
	*pHeading << _T("Method A Analysis:");
	pPara = new rptParagraph;
	(*pChapter) << pPara;

	rptHeading* pSubHeading = rptStyleManager::CreateSubHeading();
	(*pChapter) << pSubHeading;
	*pSubHeading << _T("Maximum Allowable Shape Factor, for applicability of Method A:");
	pPara = new rptParagraph;
	(*pChapter) << pPara;

	*pPara << Sub2(_T("S"), _T("max")) << _T(" = ") << symbol(ROOT) << _T(" 22 ") << symbol(TIMES) << _T(" (n + ");
	*pPara << symbol(eta) << _T(")) = ") << symbol(ROOT) << _T("22 ") << symbol(TIMES) << _T(" (") << n << _T(" + ") << n_multiplier << _T(")) = ") << s_max << rptNewLine;

	if (s_max_check)
	{
		*pPara << symbol(RIGHT_SINGLE_ARROW) << s << (s == s_max ? _T(" = ") : _T(" < ")) << s_max << _T(" ") << RPT_PASS << _T(" (Method A can be used per SECTION 14.7.6.1) ") << rptNewLine;
	}
	else
	{
		*pPara << color(Red) << symbol(RIGHT_SINGLE_ARROW) << s << _T(" > ") << s_max << _T(" ") << RPT_FAIL << color(Red) << _T(" (METHOD A cannot be used per SECTION 14.7.6.1) ") << color(Red) << rptNewLine;
	}
	*pPara << rptNewLine;

	pSubHeading = pSubHeading = rptStyleManager::CreateSubHeading();
	(*pChapter) << pSubHeading;
	*pSubHeading << _T("Shear Modulus Range Checks:");
	pPara = new rptParagraph;
	(*pChapter) << pPara;

	*pPara << _T("Minimum limit for G = ") << E.SetValue(criteria.MinimumElastomerShearModulus) << _T(" (14.7.6.2)") << rptNewLine;
	if (gMin_check)
	{
		*pPara << symbol(RIGHT_SINGLE_ARROW) << E.SetValue(Gmin) << _T(" ") << symbol(GTE) << _T(" ") << E.SetValue(criteria.MinimumElastomerShearModulus);
		*pPara << _T(" ") << RPT_PASS << rptNewLine;
	}
	else
	{
		*pPara << symbol(RIGHT_SINGLE_ARROW) << E.SetValue(Gmin) << _T(" < ") << E.SetValue(criteria.MinimumElastomerShearModulus);
		*pPara << _T(" ") << RPT_FAIL << rptNewLine;
	}

	*pPara << _T("Maximum limit for G = ") << E.SetValue(criteria.MaximumElastomerShearModulus) << _T(" (14.7.6.2)") << rptNewLine;
	if (gMax_check)
	{
		*pPara << symbol(RIGHT_SINGLE_ARROW) << E.SetValue(Gmax) << _T(" ") << symbol(LTE) << _T(" ") << E.SetValue(criteria.MaximumElastomerShearModulus);
		*pPara << _T(" ") << RPT_PASS << rptNewLine;
	}
	else
	{
		*pPara << symbol(RIGHT_SINGLE_ARROW) << E.SetValue(Gmax) << _T(" > ") << E.SetValue(criteria.MaximumElastomerShearModulus);
		*pPara << _T(" ") << RPT_FAIL << rptNewLine;
	}

	*pPara << rptNewLine;

	pSubHeading = pSubHeading = rptStyleManager::CreateSubHeading();
	(*pChapter) << pSubHeading;
	*pSubHeading << _T("Minimum Allowable Shape Factor Checks:");
	pPara = new rptParagraph;
	(*pChapter) << pPara;

	if (smax_multiplier == 0)
	{
		*pPara << Sub2(symbol(DELTA), _T("s")) << _T(" = 0 ") << symbol(RIGHT_SINGLE_ARROW) << _T(" ") << Sub2(symbol(mu), _T("sd allow")) << _T(" = 1.1 (10 % allowed increase in ") << Sub2(symbol(sigma), _T("max")) << _T(" since shear deformation is prevented)");
	}
	else
	{
		*pPara << Sub2(symbol(DELTA), _T("s")) << _T(" > 0 ") << symbol(RIGHT_SINGLE_ARROW) << _T(" ") << Sub2(symbol(mu), _T("sd allow")) << _T(" = 1.0 (shear deformation is not prevented)");
	}
	*pPara << _T(" (SECTION 14.7.6.3.2-7)") << rptNewLine;
	*pPara << Sub2(_T("S"), _T("min")) << _T(" = ") << Sub2(symbol(sigma), _T("s")) << _T(" / (1.25 ") << symbol(TIMES);
	*pPara << Sub2(_T(" G"), _T("min")) << _T(" ") << symbol(TIMES) << _T(" ") << Sub2(symbol(mu), _T("sd allow")) << _T(") = ");
	*pPara << stress.SetValue(tl_stress) << _T(" / (1.25 ") << symbol(TIMES) << _T(" ") << E.SetValue(Gmin) << _T(" ");
	*pPara << symbol(TIMES) << _T(" ") << smax_multiplier << _T(") = ") << s_min << rptNewLine;
	if (s_min_check)
	{
		*pPara << symbol(RIGHT_SINGLE_ARROW) << s << (s == s_min ? _T(" = ") : _T(" > ")) << s_min << _T(" ") << RPT_PASS;
	}
	else
	{
		*pPara << symbol(RIGHT_SINGLE_ARROW) << s << _T(" < ") << s_min << _T(" ") << RPT_FAIL;
	}
	*pPara << _T(" (SECTION 14.7.6.3.2-7)") << rptNewLine;
	*pPara << _T("Minimum Area, ") << Sub2(_T("A"), _T("min")) << _T(" = ") << Sub2(_T("P"), _T("s"));
	*pPara << _T(" / (") << Sub2(symbol(sigma), _T("max ")) << symbol(TIMES);
	*pPara << _T(" ") << Sub2(symbol(mu), _T("sd allow")) << _T(") = ") << force.SetValue(tl);
	*pPara << _T(" / (") << stress.SetValue(smax) << _T(" ") << symbol(TIMES) << _T(" ");
	*pPara << smax_multiplier << _T(") = ") << area.SetValue(a_min) << rptNewLine;
	if (a_min_check)
	{
		*pPara << symbol(RIGHT_SINGLE_ARROW) << area.SetValue(a) << _T(" ") << (a == a_min ? _T(" = ") : _T(" > "));
		*pPara << _T(" ") << area.SetValue(a_min) << _T(" ");
		*pPara << RPT_PASS << rptNewLine;
	}
	else
	{
		*pPara << symbol(RIGHT_SINGLE_ARROW) << area.SetValue(a) << _T(" ") << _T(" < ");
		*pPara << _T(" ") << area.SetValue(a_min) << _T(" ");
		*pPara << RPT_FAIL << rptNewLine;
	}
	*pPara << _T("Minimum Length, ") << Sub2(_T("L"), _T("min")) << _T(" = ") << Sub2(_T("A"), _T("min")) << _T(" / W = ") << area.SetValue(a_min);
	*pPara << _T(" / ") << length.SetValue(w) << _T(" = ") << length.SetValue(l_min) << rptNewLine;
	if (l_min_check)
	{
		*pPara << symbol(RIGHT_SINGLE_ARROW) << length.SetValue(l) << (l == l_min ? _T(" = ") : _T(" > ")) << _T(" ") << length.SetValue(l_min) << _T(" ");
		*pPara << RPT_PASS << rptNewLine;
	}
	else
	{
		*pPara << symbol(RIGHT_SINGLE_ARROW) << length.SetValue(l) << _T(" < ") << _T(" ") << length.SetValue(l_min) << _T(" ");
		*pPara << RPT_FAIL << rptNewLine;
	}
	*pPara << _T("Minimum Width, ") << Sub2(_T("W"), _T("min")) << _T(" = ") << Sub2(_T("A"), _T("min")) << _T(" / L = ");
	*pPara << area.SetValue(a_min) << _T(" / ") << length.SetValue(l) << _T(" = ") << length.SetValue(w_min) << rptNewLine;
	if (w_min_check)
	{
		*pPara << symbol(RIGHT_SINGLE_ARROW) << length.SetValue(w) << (w == w_min ? _T(" = ") : _T(" > ")) << length.SetValue(w_min) << _T(" ");
		*pPara << RPT_PASS << rptNewLine;
	}
	else
	{
		*pPara << symbol(RIGHT_SINGLE_ARROW) << length.SetValue(w) << _T(" < ") << length.SetValue(w_min) << _T(" ");
		*pPara << RPT_FAIL << rptNewLine;
	}
	*pPara << _T("Maximum Intermediate Elastomer Layer Thickness, ") << Sub2(_T("h"), _T("ri max")) << _T(" = L ") << symbol(TIMES) << _T(" W / (2") Sub2(_T("S"), _T("min ")) << symbol(TIMES);
	*pPara << _T(" (L + W)) = ") << length.SetValue(l) << _T(" ") << symbol(TIMES) << _T(" ") << length.SetValue(w) << _T(" / (2 ") << symbol(TIMES) << _T(" ") << s_min << _T(" ");
	*pPara << symbol(TIMES) << _T(" (");
	*pPara << length.SetValue(l) << _T(" + ") << length.SetValue(w) << _T(")) = ") << length.SetValue(tlayer_max) << rptNewLine;
	if (tlayer_max_check)
	{
		*pPara << symbol(RIGHT_SINGLE_ARROW) << length.SetValue(tlayer) << (tlayer == tlayer_max ? _T(" = ") : _T(" < ")) << length.SetValue(tlayer_max) << _T(" ");
		*pPara << RPT_PASS << rptNewLine << rptNewLine;
	}
	else
	{
		*pPara << symbol(RIGHT_SINGLE_ARROW) << length.SetValue(tlayer) << _T(" > ") << length.SetValue(tlayer_max) << _T(" ");
		*pPara << RPT_FAIL << rptNewLine << rptNewLine;
	}



	pSubHeading = pSubHeading = rptStyleManager::CreateSubHeading();
	(*pChapter) << pSubHeading;
	*pSubHeading << _T("Maximum Allowable Stress Check:");
	pPara = new rptParagraph;
	(*pChapter) << pPara;

	*pPara << Sub2(symbol(sigma), _T("max")) << _T(" = ") << stress.SetValue(smax) << rptNewLine;
	if (max_stress_check)
	{
		*pPara << symbol(RIGHT_SINGLE_ARROW) << stress.SetValue(total_stress) << (s == smax ? _T(" = ") : _T(" < ")) << stress.SetValue(smax);
		*pPara << _T(" ") << RPT_PASS;
	}
	else
	{
		*pPara << symbol(RIGHT_SINGLE_ARROW) << stress.SetValue(total_stress) << _T(" > ") << stress.SetValue(smax);
		*pPara << _T(" ") << RPT_FAIL;
	}
	*pPara << _T(" (14.7.6.3.2-8)");

	*pPara << rptNewLine << rptNewLine;

	pSubHeading = rptStyleManager::CreateSubHeading();
	(*pChapter) << pSubHeading;
	*pSubHeading << _T("Minimum Allowable Layers Checks:");
	pPara = new rptParagraph;
	(*pChapter) << pPara;

	rptHeading* pLevel3Heading = rptStyleManager::CreateHeading(3);
	(*pChapter) << pLevel3Heading;
	*pLevel3Heading << _T("Shear Deformation:");
	pPara = new rptParagraph;
	(*pChapter) << pPara;


	*pPara << Sub2(_T("n"), _T("min")) << _T("(") << Sub2(symbol(DELTA), _T("s")) << _T(") = 2 ") << symbol(TIMES);
	*pPara << _T(" (") << Sub2(symbol(DELTA), _T("s")) << _T(" - ") << Sub2(_T("h"), _T("c")) << _T(") / ") Sub2(_T("h"), _T("ri")) << _T(" = 2 ") << symbol(TIMES) << _T(" (");
	*pPara << length.SetValue(sdef) << _T(" - ") << length.SetValue(tcover) << _T(") / ") << length.SetValue(tlayer) << _T(" = ") << n_min_shear_def << rptNewLine;
	*pPara << symbol(RIGHT_SINGLE_ARROW);
	if (n_min_shear_def_check)
	{
		*pPara << _T(" ") << n << (n == n_min_shear_def ? _T(" = ") : _T(" > ")) << n_min_shear_def << _T(" ");
		*pPara << RPT_PASS;
	}
	else
	{
		*pPara << _T(" ") << n << _T(" < ") << n_min_shear_def << _T(" ");
		*pPara << RPT_FAIL;
	}
	*pPara << _T(" (14.7.6.3.4-1)") << rptNewLine;

	*pPara << rptNewLine;

	pLevel3Heading = rptStyleManager::CreateHeading(3);
	(*pChapter) << pLevel3Heading;
	*pLevel3Heading << _T("Primary Direction:");

	rptHeading* pLevel4Heading = rptStyleManager::CreateHeading(4);

	if (spec < WBFL::LRFD::BDSManager::Edition::SixthEdition2012)
	{
		(*pChapter) << pLevel4Heading;
		*pLevel4Heading << _T("Rotation:");
		pPara = new rptParagraph;
		(*pChapter) << pPara;

		if (n_min_rot_x <= 0)
		{
			*pPara << Sub2(_T("0.5G"), _T("max ")) << symbol(TIMES) << _T(" S ") << symbol(TIMES) << _T(" ");
			*pPara << Sub2(symbol(theta), _T("x")) << _T(" / ") << Sub2(symbol(sigma), _T("s"));
			*pPara << symbol(TIMES) << _T("(") << Sub2(_T("h"), _T("ri")) << _T(" / L)") << Super(_T("2")) << _T(" - ");
			*pPara << symbol(eta) << _T(" = ");
			*pPara << _T("0.5(") << E.SetValue(Gmax) << _T(") ") << symbol(TIMES) << _T(" (") << s << _T(") ") << symbol(TIMES) << _T(" (") << x_rotation << _T(" / ");
			*pPara << stress.SetValue(tl_stress) << _T(") ") << symbol(TIMES) << _T(" (") << length.SetValue(l) << _T("/") << length.SetValue(tlayer) << _T(")") << Super(_T("2"));
			*pPara << _T(" - ") << n_multiplier << _T(" = ") << n_lay_r_x_calc << rptNewLine;
			*pPara << symbol(RIGHT_SINGLE_ARROW) << n_lay_r_x_calc << _T(" < ") << _T(" 0 ") << symbol(RIGHT_SINGLE_ARROW);
			*pPara << Sub2(_T("n"), _T("min")) << _T("(") << Sub2(symbol(theta), _T("x")) << _T(") = 0") << rptNewLine;
		}
		else
		{
			*pPara << Sub2(_T("0.5G"), _T("max ")) << symbol(TIMES) << _T(" S ") << symbol(TIMES) << _T(" ");
			*pPara << Sub2(symbol(theta), _T("x")) << _T(" / ") << Sub2(symbol(sigma), _T("s"));
			*pPara << symbol(TIMES) << _T("(") << Sub2(_T("h"), _T("ri")) << _T(" / L)") << Super(_T("2")) << _T(" - ");
			*pPara << symbol(eta) << _T(" = ");
			*pPara << _T("0.5(") << E.SetValue(Gmax) << _T(") ") << symbol(TIMES) << _T(" (") << s << _T(") ") << symbol(TIMES) << _T(" (") << x_rotation << _T(" / ");
			*pPara << stress.SetValue(tl_stress) << _T(") ") << symbol(TIMES) << _T(" (") << length.SetValue(l) << _T(" / ") << length.SetValue(tlayer) << _T(")") << Super(_T("2"));
			*pPara << _T(" - ") << n_multiplier << _T(" = ") << n_lay_r_x_calc << rptNewLine;
			*pPara << symbol(RIGHT_SINGLE_ARROW) << n_lay_r_x_calc << _T(" > 0 ") << symbol(RIGHT_SINGLE_ARROW);
			*pPara << Sub2(_T("n"), _T("min")) << _T("(") << Sub2(symbol(theta), _T("x")) << _T(") = ") << n_min_rot_x << rptNewLine;
		}
		if (n_min_rot_x_check)
		{
			*pPara << symbol(RIGHT_SINGLE_ARROW) << n << (n == n_min_rot_x ? _T(" = ") : _T(" > ")) << n_min_rot_x << _T(" ") << RPT_PASS;
		}
		else
		{
			*pPara << symbol(RIGHT_SINGLE_ARROW) << n << _T(" < ") << n_min_rot_x << _T(" ") << RPT_FAIL;
		}
		*pPara << _T(" (SECTION 14.7.6.3.5)") << rptNewLine;
		*pPara << rptNewLine;
	}

	pLevel4Heading = rptStyleManager::CreateHeading(4);
	(*pChapter) << pLevel4Heading;
	*pLevel4Heading << _T("Stability:");
	pPara = new rptParagraph;
	(*pChapter) << pPara;

	*pPara << Sub2(_T("n"), _T("max Stab X")) << _T(" = (L / 3 - 2 ");
	*pPara << symbol(TIMES) << Sub2(_T(" h"), _T("c")) << _T(" - ") << Sub2(_T("h"), _T("s")) << _T(") / (") << Sub2(_T("h"), _T("ri")) << _T(" + ") << Sub2(_T("h"), _T("s")) << _T(") = ");
	*pPara << _T("(") << length.SetValue(l) << _T(" / 3 - 2 ") << symbol(TIMES) << _T(" ") << length.SetValue(tcover) << _T(" - ");
	*pPara << length.SetValue(tshim) << _T(") / (") << length.SetValue(tlayer) << _T(" + ");
	*pPara << length.SetValue(tshim) << _T(") = ") << n_max_stab_x << rptNewLine;
	if (n_max_stab_x_check)
	{
		*pPara << symbol(RIGHT_SINGLE_ARROW) << n << (n == n_max_stab_x ? _T(" = ") : _T(" < ")) << n_max_stab_x << _T(" ") << RPT_PASS;
	}
	else
	{
		*pPara << symbol(RIGHT_SINGLE_ARROW) << n << _T(" > ") << n_max_stab_x << _T(" ") << RPT_FAIL;
	}
	*pPara << _T(" (SECTION 14.7.6.3.6)") << rptNewLine;




	*pPara << rptNewLine;

	pLevel3Heading = rptStyleManager::CreateHeading(3);
	(*pChapter) << pLevel3Heading;
	*pLevel3Heading << _T("Secondary Direction:");

	if (spec < WBFL::LRFD::BDSManager::Edition::SixthEdition2012)
	{

		pLevel4Heading = rptStyleManager::CreateHeading(4);
		(*pChapter) << pLevel4Heading;
		*pLevel4Heading << _T("Rotation:");
		pPara = new rptParagraph;
		(*pChapter) << pPara;


		if (n_min_rot_y <= 0)
		{
			*pPara << Sub2(_T("0.5G"), _T("max ")) << symbol(TIMES) << _T(" S ") << symbol(TIMES) << _T(" ");
			*pPara << Sub2(symbol(theta), _T("y")) << _T(" / ") << Sub2(symbol(sigma), _T("s"));
			*pPara << _T("(") << Sub2(_T("h"), _T("ri")) << _T(" / W)") << Super(_T("2")) << _T(" - ");
			*pPara << symbol(eta) << _T(" = ");
			*pPara << _T("0.5(") << E.SetValue(Gmax) << _T(") ") << symbol(TIMES) << _T(" (") << s << _T(") ") << symbol(TIMES) << _T(" (") << y_rotation << _T(") / (");
			*pPara << stress.SetValue(tl_stress) << _T(") ") << symbol(TIMES) << _T(" (") << length.SetValue(w) << _T(" / ");
			*pPara << length.SetValue(tlayer) << _T(")") << Super(_T("2"));
			*pPara << _T(" - ") << n_multiplier << _T(" = ") << n_lay_r_y_calc << rptNewLine;
			*pPara << symbol(RIGHT_SINGLE_ARROW) << n_lay_r_y_calc << _T(" < 0 ") << symbol(RIGHT_SINGLE_ARROW);
			*pPara << Sub2(_T("n"), _T("min")) << _T("(") << Sub2(symbol(theta), _T("y")) << _T(") = 0") << rptNewLine;
		}
		else
		{
			*pPara << Sub2(_T("0.5G"), _T("max ")) << symbol(TIMES) << _T(" S ") << symbol(TIMES);
			*pPara << _T(" ") << Sub2(symbol(theta), _T("y")) << _T(" / ") << Sub2(symbol(sigma), _T("s"));
			*pPara << _T("(") << Sub2(_T("h"), _T("ri")) << _T(" / W)") << Super(_T("2")) << _T(" - ");
			*pPara << symbol(eta) << _T(" = ");
			*pPara << _T("0.5(") << E.SetValue(Gmax) << _T(") ") << symbol(TIMES) << _T(" (") << s << _T(")") << symbol(TIMES) << _T(" (") << y_rotation << _T(") / (");
			*pPara << stress.SetValue(tl_stress) << _T(") ") << symbol(TIMES) << _T(" (") << length.SetValue(w) << _T("/");
			*pPara << length.SetValue(tlayer) << _T(")") << Super(_T("2"));
			*pPara << _T(" - ") << n_multiplier << _T(" = ") << n_lay_r_y_calc << rptNewLine;
			*pPara << symbol(RIGHT_SINGLE_ARROW) << n_lay_r_y_calc << _T(" > 0 ") << symbol(RIGHT_SINGLE_ARROW);
			*pPara << Sub2(_T("n"), _T("min")) << _T("(") << Sub2(symbol(theta), _T("y")) << _T(") = ") << n_min_rot_y << rptNewLine;
		}
		if (n_min_rot_y_check)
		{
			*pPara << symbol(RIGHT_SINGLE_ARROW) << n << (n == n_min_rot_y ? _T(" = ") : _T(" > ")) << n_min_rot_y << _T(" ") << RPT_PASS;
		}
		else
		{
			*pPara << symbol(RIGHT_SINGLE_ARROW) << n << _T(" < ") << n_min_rot_y << _T(" ") << RPT_FAIL;
		}
		*pPara << _T(" (SECTION 14.7.6.3.5)") << rptNewLine;

		*pPara << rptNewLine;
	}

	pLevel4Heading = rptStyleManager::CreateHeading(4);
	(*pChapter) << pLevel4Heading;
	*pLevel4Heading << _T("Stability:");
	pPara = new rptParagraph;
	(*pChapter) << pPara;

	*pPara << Sub2(_T("n"), _T("max Stab Y")) << _T(" = (W / 3 - 2");
	*pPara << symbol(TIMES) << Sub2(_T(" h"), _T("c")) << _T(" - ") << Sub2(_T("h"), _T("s")) << _T(") / (") << Sub2(_T("h"), _T("ri")) << _T(" + ") << Sub2(_T("h"), _T("s")) << _T(") = ");
	*pPara << _T("(") << length.SetValue(w) << _T(" / 3 - 2 ") << symbol(TIMES) << _T(" ") << length.SetValue(tcover) << _T(" - ");
	*pPara << length.SetValue(tshim) << _T(") / (") << length.SetValue(tlayer) << _T(" + ");
	*pPara << length.SetValue(tshim) << _T(") = ") << n_max_stab_y << rptNewLine;
	if (n_max_stab_y_check)
	{
		*pPara << symbol(RIGHT_SINGLE_ARROW) << n << (n == n_max_stab_y ? _T(" = ") : _T(" < ")) << n_max_stab_y << _T(" ") << RPT_PASS;
	}
	else
	{
		*pPara << symbol(RIGHT_SINGLE_ARROW) << n << _T(" > ") << n_max_stab_y << _T(" ") << RPT_FAIL;
	}
	*pPara << _T(" (SECTION 14.7.6.3.6)");

	*pPara << rptNewLine << rptNewLine;

	pSubHeading = pSubHeading = rptStyleManager::CreateSubHeading();
	(*pChapter) << pSubHeading;
	*pSubHeading << _T("Maximum Compressive Strain:");
	pPara = new rptParagraph;
	(*pChapter) << pPara;
	*pPara << _T("Elastomer Elastic Modulus, ") << Sub2(_T("E"), _T("A")) << _T(" = ") << Ecoeff;
	*pPara << _T(" ") << symbol(TIMES) << Sub2(_T(" (G"), _T("min")) << _T(" + ") << Sub2(_T("G"), _T("max")) << _T(")/2 ");
	*pPara << symbol(TIMES) << _T(" S") << Super(_T("2")) << _T(" = ") << Ecoeff << _T(" ") << symbol(TIMES) << _T(" (");
	*pPara << E.SetValue(Gmin) << _T(" + ") << E.SetValue(Gmax) << _T(")/2 ") << symbol(TIMES) << _T(" ");
	*pPara << s << Super(_T("2")) << _T(" = ") << E.SetValue(EcA) << rptNewLine;
	if (max_comp_strain_check)
	{
		*pPara << symbol(RIGHT_SINGLE_ARROW) << stress.SetValue(tl_stress) << _T(" / ");
		*pPara << E.SetValue(EcA) << _T(" = ") << tl_stress / EcA << (tl_stress / EcA == 0.7 ? _T(" = 0.07 ") : _T(" < 0.07 ")) << RPT_PASS;
	}
	else
	{
		*pPara << symbol(RIGHT_SINGLE_ARROW) << stress.SetValue(tl_stress) << _T(" / ");
		*pPara << E.SetValue(EcA) << _T(" = ") << tl_stress / EcA << _T(" > 0.07 ") << RPT_FAIL;
	}
	*pPara << _T(" (14.7.6.3.3-1)");

	*pPara << rptNewLine << rptNewLine;

	pSubHeading = pSubHeading = rptStyleManager::CreateSubHeading();
	(*pChapter) << pSubHeading;
	*pSubHeading << _T("Initial Dead Load Deflection:");
	pPara = new rptParagraph;
	(*pChapter) << pPara;

	*pPara << Sub2(symbol(delta), _T("D-initial")) << _T(" = ") << Sub2(_T("P"), _T("D ")) << symbol(TIMES) << Sub2(_T(" h"), _T("rt"));
	*pPara << _T(" / A / ") << Sub2(_T("E"), _T("A")) << _T(" = ");
	*pPara << force.SetValue(dl) << _T(" ") << symbol(TIMES) << _T(" ") << length.SetValue(total_elastomer_thickness);
	*pPara << _T(" / ") << area.SetValue(a) << _T(" / ") << E.SetValue(EcA) << _T(" = ");
	*pPara << length.SetValue(deltaDLiA) << _T(" (Comm. C14.7.5.3.6-1)");

	*pPara << rptNewLine << rptNewLine;

	pSubHeading = pSubHeading = rptStyleManager::CreateSubHeading();
	(*pChapter) << pSubHeading;
	*pSubHeading << _T("Instantaneous Live Load Deflection:");
	pPara = new rptParagraph;
	(*pChapter) << pPara;

	*pPara << Sub2(symbol(delta), _T("L")) << _T(" = ") << Sub2(_T("P"), _T("L ")) << symbol(TIMES) << Sub2(_T(" h"), _T("rt"));
	*pPara << _T(" / A / ") << Sub2(_T("E"), _T("A")) << _T(" = ");
	*pPara << force.SetValue(ll) << _T(" ") << symbol(TIMES) << _T(" ") << length.SetValue(total_elastomer_thickness);
	*pPara << _T(" / ") << area.SetValue(a) << _T(" / ") << E.SetValue(EcA) << _T(" = ");
	*pPara << length.SetValue(deltaLLiA) << _T(" (Comm. C14.7.5.3.6-1)") << rptNewLine;

	if (deltaLLiACheck)
	{
		*pPara << symbol(RIGHT_SINGLE_ARROW) << length.SetValue(deltaLLiA) << _T(" ") << symbol(LTE) << _T(" ") << length.SetValue(criteria.maxLLdef) << _T(" ") << RPT_PASS;
	}
	else
	{
		*pPara << symbol(RIGHT_SINGLE_ARROW) << length.SetValue(deltaLLiA) << _T(" > ") << length.SetValue(criteria.maxLLdef) << _T(" ") << RPT_FAIL;
	}

}

void BearingReporter::ReportBearingSpecCheckSummaryB(rptChapter* pChapter, rptParagraph* pPara,
	const WBFL::EngTools::BearingCheckArtifact& artifact)
{
	const BearingCalculator brg_calc;
	const auto& brg = artifact.GetBearing();
	const auto& criteria = artifact.GetBearingDesignCriteria();
	const auto& spec = criteria.GetSpecification();


	bool t_min_shim_absolute_check = artifact.MinimumSteelShimThicknessAbsoluteCheck();
	bool t_min_cover_check = artifact.MinimumElastomerCoverThicknessCheck();
	bool t_max_cover_check = artifact.MaximumElastomerCoverThicknessCheck();
	bool s_max_check = artifact.MaximumShapeFactorCheck();
	bool n_min_shear_def_check = artifact.MinimumNumLayersShearDeformationCheck();
	bool t_min_shim_service_check = artifact.MinimumSteelShimThicknessServiceCheck();
	bool t_min_shim_fatigue_check = artifact.MinimumSteelShimThicknessFatigueCheck();
	bool shear_def_check = artifact.ShearDeformationCheck();
	bool static_axial_X_ss_check = artifact.StaticAxialPrimaryShearStrainCheck();
	bool static_axial_Y_ss_check = artifact.StaticAxialSecondaryShearStrainCheck();
	bool ss_X_combo_sum_check = artifact.PrimaryShearStrainComboSumCheck();
	bool ss_Y_combo_sum_check = artifact.SecondaryShearStrainComboSumCheck();
	bool check_app_TL_stab_X = criteria.CheckApplicabilityTotalStressStabilityX();
	bool check_app_TL_stab_Y = criteria.CheckApplicabilityTotalStressStabilityY();
	bool stab_X_dir_check = artifact.StabilityXDirectionCheck();
	bool stab_Y_dir_check = artifact.StabilityYDirectionCheck();
	bool use_ext_plates = brg.UseExternalPlates();
	bool rest_system_req_check = artifact.RestraintSystemRequirementCheck();
	bool hydrostatic_check = artifact.HydrostaticStressCheck();
	auto horiz_force_check = artifact.HorizontalForceCheck();
	auto deltaLLiBCheck = artifact.MaximumLiveLoadDeflectionMethodBCheck();
	bool gMin_check = artifact.MinimumAllowableShearModulusCheck();
	bool gMax_check = artifact.MaximumAllowableShearModulusCheck();
	bool hri_check = artifact.RequiredIntermediateElastomerThicknessCheck();
	bool height_check = artifact.MinimumTotalBearingHeightCheck();
	bool minDistBrg2gBfCheck = artifact.MinimumBearingEdgeToBottomFlangeEdgeDistCheck();
	bool maxDistBrg2gBfCheck = artifact.MaximumBearingEdgeToBottomFlangeEdgeDistCheck();
	bool distBrg2gBfCheck = artifact.RequiredBearingEdgeToBottomFlangeEdgeDistCheck();
	bool maxTLCheck = artifact.MaximumTotalLoadCheck();

	//pPara = new rptParagraph;
	//(*pChapter) << pPara;

	//*pPara << rptNewPage;

	rptHeading* pHeading = rptStyleManager::CreateHeading();
	(*pChapter) << pHeading;
	pHeading->SetName(_T("Specification Check Summary"));
	*pHeading << _T("Specification Check Summary");

	pPara = new rptParagraph;
	(*pChapter) << pPara;

	if (!t_min_shim_absolute_check || !t_min_shim_service_check || !t_min_shim_fatigue_check || !n_min_shear_def_check || !t_max_cover_check
		|| (spec >= WBFL::LRFD::BDSManager::Edition::TenthEdition2024 ? !t_min_cover_check : false)
		|| !shear_def_check || !static_axial_X_ss_check || !static_axial_Y_ss_check || !ss_X_combo_sum_check || (check_app_TL_stab_X && !stab_X_dir_check)
		|| (check_app_TL_stab_Y && !stab_Y_dir_check) || !use_ext_plates && !rest_system_req_check || (use_ext_plates && !hydrostatic_check)
		|| (!use_ext_plates && !horiz_force_check) || !deltaLLiBCheck || !gMin_check || !gMax_check || (criteria.bRequiredIntermediateElastomerThickness ? !hri_check : false)
		|| (criteria.bMinimumTotalBearingHeight ? !height_check : false)
		|| (criteria.bMaximumBearingEdgeToGirderEdgeDistance ? !minDistBrg2gBfCheck : false)
		|| (criteria.bMaximumBearingEdgeToGirderEdgeDistance ? !maxDistBrg2gBfCheck : false)
		|| (criteria.bRequiredBearingEdgeToGirderEdgeDistance ? !distBrg2gBfCheck : false)
		|| (criteria.bMaximumTotalLoad ? !maxTLCheck : false))
	{
		*pPara << color(Red);
		if (!t_min_shim_absolute_check)
		{
			*pPara << _T("Steel shim thickness is less than required for fabrication.") << rptNewLine;
		}
		if (!t_min_cover_check && spec >= WBFL::LRFD::BDSManager::Edition::TenthEdition2024)
		{
			*pPara << _T("Elastomer cover thickness is below the minimum thickness limit.") << rptNewLine;
		}
		if (!t_max_cover_check)
		{
			*pPara << _T("Elastomer cover thickness exceeds the maximum thickness limit.") << rptNewLine;
		}
		if (!t_min_shim_service_check)
		{
			*pPara << _T("Steel shim thickness is not sufficient to resist service loads.") << rptNewLine;
		}
		if (!t_min_shim_fatigue_check)
		{
			*pPara << _T("Steel shim thickness is not sufficient to resist fatigue loads.") << rptNewLine;
		}
		if (!n_min_shear_def_check)
		{
			*pPara << _T("Number of elastomer layers is not sufficient to accommodate shear deformation.") << rptNewLine;
		}
		if (!shear_def_check)
		{
			*pPara << _T("Total elastomer thickness is not sufficient to accommodate shear deformation.") << rptNewLine;
		}
		if (!static_axial_X_ss_check)
		{
			*pPara << _T("Elastomer is not sufficient to accommodate shear strain in the primary direction (longitudinal to the bridge) due to static axial load.") << rptNewLine;
		}
		if (!static_axial_X_ss_check)
		{
			*pPara << _T("Elastomer is not sufficient to accommodate shear strain in the secondary direction (transverse to the bridge) due to static axial load.") << rptNewLine;
		}
		if (!ss_X_combo_sum_check)
		{
			*pPara << _T("Elastomer is not sufficient to accommodate shear strain in the primary direction (longitudinal to the bridge) due to axial service loads.") << rptNewLine;
		}
		if (!ss_Y_combo_sum_check)
		{
			*pPara << _T("Elastomer is not sufficient to accommodate shear strain in the secondary direction (transverse to the bridge) due to axial service loads.") << rptNewLine;
		}
		if (check_app_TL_stab_X && !stab_X_dir_check)
		{
			*pPara << _T("Bearing is unstable in the primary direction (longitudinal to the bridge) due to axial load.") << rptNewLine;
		}
		if (check_app_TL_stab_Y && !stab_Y_dir_check)
		{
			*pPara << _T("Bearing is unstable in the secondary direction (transverse to the bridge) due to axial load.") << rptNewLine;
		}
		if (!use_ext_plates && !rest_system_req_check)
		{
			*pPara << _T("Bearing restraint system is required.") << rptNewLine;
		}
		if (use_ext_plates && !hydrostatic_check)
		{
			*pPara << _T("Elastomer is not sufficient to resist tension due to hydrostatic stress (Applicable if externally bonded plates are used).") << rptNewLine;
		}
		if (!use_ext_plates && !horiz_force_check)
		{
			*pPara << _T("Elastomer is not sufficient to resist horizontal force effects due to shear deformation.") << rptNewLine;
		}
		if (!deltaLLiBCheck)
		{
			*pPara << _T("Instantaneous live load deflection exceeds the recommended limit.") << rptNewLine;
		}
		if (!gMin_check)
		{
			*pPara << _T("Specifed elastomer shear modulus is below the minimum limit.") << rptNewLine;
		}
		if (!gMax_check)
		{
			*pPara << _T("Specifed elastomer shear modulus exceeds the maximum limit.") << rptNewLine;
		}
		if (criteria.bRequiredIntermediateElastomerThickness && !hri_check)
		{
			*pPara << _T("Input for intermediate elastomer thickness does not equal the required thickness.") << rptNewLine;
		}
		if (criteria.bMinimumTotalBearingHeight && !height_check)
		{
			*pPara << _T("Total bearing height is below the minimum limit.") << rptNewLine;
		}
		if (criteria.bMinimumBearingEdgeToGirderEdgeDistance && !minDistBrg2gBfCheck)
		{
			*pPara << _T("Distance from edge of bearing to edge of girder bottom flange is less than the minimum limit.") << rptNewLine;
		}
		if (criteria.bMaximumBearingEdgeToGirderEdgeDistance && !maxDistBrg2gBfCheck)
		{
			*pPara << _T("Distance from edge of bearing to edge of girder bottom flange exceeds the maximum limit.") << rptNewLine;
		}
		if (criteria.bRequiredBearingEdgeToGirderEdgeDistance && !distBrg2gBfCheck)
		{
			*pPara << _T("Distance from edge of bearing to edge of girder bottom flange does not equal the required distance.") << rptNewLine;
		}
		if (criteria.bMaximumTotalLoad && !maxTLCheck)
		{
			*pPara << _T("The total vertical load exceeds the maximum limit.") << rptNewLine;
		}

		*pPara << color(Red) << rptNewLine << rptNewLine;
	}
	else
	{
		*pPara << color(Green) << _T("Bearing design per Method B was successful.") << color(Green) << rptNewLine << rptNewLine;
	}
}

void BearingReporter::ReportBearingSpecificationCheckB(const WBFL::Units::IndirectMeasure* pDispUnits,
	rptChapter* pChapter, rptParagraph* pPara,
	const WBFL::EngTools::BearingCheckArtifact& artifact)
{

	INIT_UV_PROTOTYPE(rptLengthUnitValue, length, pDispUnits->ComponentDim, true);
	INIT_UV_PROTOTYPE(rptAreaUnitValue, area, pDispUnits->Area, true);
	INIT_UV_PROTOTYPE(rptForceUnitValue, force, pDispUnits->GeneralForce, true);
	INIT_UV_PROTOTYPE(rptStressUnitValue, stress, pDispUnits->Stress, true);
	INIT_UV_PROTOTYPE(rptStressUnitValue, E, pDispUnits->ModE, true);

	const BearingCalculator brg_calc;
	const auto& brg = artifact.GetBearing();
	const auto& brg_loads = artifact.GetBearingLoads();
	const auto& criteria = artifact.GetBearingDesignCriteria();
	const auto& spec = criteria.GetSpecification();

	Float64 l = brg.GetLength();
	Float64 w = brg.GetWidth();
	Float64 a = brg.GetArea();
	Float64 Gmin = brg.GetShearModulusMinimum();

	Float64 K = brg.GetElastomerBulkModulus();
	Float64 dl = brg_loads.GetDeadLoad();
	Float64 ll = brg_loads.GetLiveLoad();
	Float64 tl = brg_loads.GetTotalLoad();
	Float64 tl_stress = brg_calc.GetTotalLoadStress(brg, brg_loads);

	Float64 Sstatic = brg_calc.GetStaticStress(brg, brg_loads);
	Float64 Scyclic = brg_calc.GetCyclicStress(brg, brg_loads);
	Float64 n_multiplier = brg_calc.GetNlayMultiplier(brg);
	Float64 s = brg.GetShapeFactor();
	IndexType n = brg.GetNumIntLayers();
	Float64 sdef = brg_loads.GetShearDeformation();
	Float64 static_rotation = brg_loads.GetStaticRotation();
	Float64 cyclic_rotation = brg_loads.GetCyclicRotation();
	Float64 total_elastomer_thickness = brg.GetTotalElastomerThickness();
	Float64 tlayer = brg.GetIntermediateLayerThickness();


	Float64 da1 = brg_calc.Getda1(brg);
	Float64 da2 = brg_calc.Getda2(brg);
	Float64 da3 = brg_calc.Getda3(brg);
	Float64 Dax = brg_calc.GetPrimaryShearStrainAxialCoefficient(brg);
	Float64 Day = brg_calc.GetSecondaryShearStrainAxialCoefficient(brg);
	Float64 Drx = brg_calc.GetPrimaryShearStrainRotationCoefficient(brg);
	Float64 Dry = brg_calc.GetSecondaryShearStrainRotationCoefficient(brg);
	Float64 es_rotx = brg_calc.GetStaticRotationalPrimaryShearStrain(brg, brg_loads);
	Float64 es_roty = brg_calc.GetStaticRotationalSecondaryShearStrain(brg, brg_loads);
	Float64 Dsx = brg_calc.GetStaticDisplacementPrimaryShearStrain(brg, brg_loads);
	Float64 Dsy = brg_calc.GetStaticDisplacementSecondaryShearStrain();
	Float64 es_cyclic_dispx = brg_calc.GetCyclicDisplacementPrimaryShearStrain(brg, brg_loads);
	Float64 es_cyclic_dispy = brg_calc.GetCyclicDisplacementSecondaryShearStrain();
	Float64 es_cyclic_axialx = brg_calc.GetCyclicAxialPrimaryShearStrain(brg, brg_loads);
	Float64 es_cyclic_axialy = brg_calc.GetCyclicAxialSecondaryShearStrain(brg, brg_loads);
	Float64 es_cyclic_rotx = brg_calc.GetCyclicRotationalPrimaryShearStrain(brg, brg_loads);
	Float64 es_cyclic_roty = brg_calc.GetCyclicRotationalSecondaryShearStrain(brg, brg_loads);

	Float64 EcB = brg_calc.GetElastomerElasticModulusMethodB(brg, spec);
	Float64 Ecoeff = brg_calc.GetElasticModulusCoefficient(spec);

	Float64 sigmaTLstabX = criteria.GetAllowableTotalLoadStressStabilityX();
	Float64 sigmaTLstabY = criteria.GetAllowableTotalLoadStressStabilityY();
	Float64 smax_multiplier = criteria.GetSigmaMultiplier();

	bool t_min_shim_absolute_check = artifact.MinimumSteelShimThicknessAbsoluteCheck();
	bool t_min_cover_check = artifact.MinimumElastomerCoverThicknessCheck();
	bool t_max_cover_check = artifact.MaximumElastomerCoverThicknessCheck();


	Float64 s_max = criteria.GetMaximumAllowableShapeFactor();
	bool s_max_check = artifact.MaximumShapeFactorCheck();

	bool n_min_shear_def_check = artifact.MinimumNumLayersShearDeformationCheck();

	bool t_min_shim_service_check = artifact.MinimumSteelShimThicknessServiceCheck();

	bool t_min_shim_fatigue_check = artifact.MinimumSteelShimThicknessFatigueCheck();

	bool shear_def_check = artifact.ShearDeformationCheck();
	Float64 static_axial_X_ss = brg_calc.GetStaticAxialPrimaryShearStrain(brg, brg_loads);
	bool static_axial_X_ss_check = artifact.StaticAxialPrimaryShearStrainCheck();
	Float64 static_axial_Y_ss = brg_calc.GetStaticAxialSecondaryShearStrain(brg, brg_loads);
	bool static_axial_Y_ss_check = artifact.StaticAxialSecondaryShearStrainCheck();
	Float64 ss_X_combo_sum = brg_calc.GetPrimaryShearStrainComboSum(brg, brg_loads);
	bool ss_X_combo_sum_check = artifact.PrimaryShearStrainComboSumCheck();
	Float64 ss_Y_combo_sum = brg_calc.GetSecondaryShearStrainComboSum(brg, brg_loads);
	bool ss_Y_combo_sum_check = artifact.SecondaryShearStrainComboSumCheck();
	bool check_app_TL_stab_X = criteria.CheckApplicabilityTotalStressStabilityX();
	bool check_app_TL_stab_Y = criteria.CheckApplicabilityTotalStressStabilityY();
	Float64 total_stress = brg_calc.GetTotalStress(brg, brg_loads);
	Float64 allow_stab_X_dir = criteria.GetAllowableTotalLoadStressStabilityX();
	bool stab_X_dir_check = artifact.StabilityXDirectionCheck();
	Float64 allow_stab_Y_dir = criteria.GetAllowableTotalLoadStressStabilityY();
	bool stab_Y_dir_check = artifact.StabilityYDirectionCheck();
	bool use_ext_plates = brg.UseExternalPlates();

	Float64 static_stress = brg_calc.GetStaticStress(brg, brg_loads);
	Float64 cyclic_stress = brg_calc.GetCyclicStress(brg, brg_loads);
	Float64 lambda = brg.GetCompressibilityIndex();
	Float64 restraint_system_calc = brg_calc.GetRestraintSystemCDRatio(brg, brg_loads, spec);
	bool rest_system_req_check = artifact.RestraintSystemRequirementCheck();
	Float64 max_stress = criteria.GetMaximumAllowableHydrostaticStress();
	Float64 hydrostatic_stress = brg_calc.GetHydrostaticStress(brg, brg_loads);
	bool hydrostatic_check = artifact.HydrostaticStressCheck();
	Float64 KeffX = brg_loads.GetEffectiveKFactorX();
	Float64 KeffY = brg_loads.GetEffectiveKFactorY();
	auto fixed_x = brg_loads.GetFixedTranslationX();
	auto fixed_y = brg_loads.GetFixedTranslationY();
	Float64 Ax = criteria.GetPrimaryIntermediateCalculationA();
	Float64 Ay = criteria.GetSecondaryIntermediateCalculationA();
	Float64 Bx = criteria.GetPrimaryIntermediateCalculationB();
	Float64 By = criteria.GetSecondaryIntermediateCalculationB();
	Float64 peak_hyd = brg_calc.GetPeakHydrostaticStressCoefficient(brg);
	Float64 total_axial_strain = brg_calc.GetTotalAxialStrain(brg, brg_loads);
	Float64 alpha = brg_calc.GetAlphaCoefficient(brg, brg_loads);
	Float64 Ca = brg_calc.GetCaCoefficient(brg, brg_loads);
	auto horiz_force = brg_calc.GetHorizontalForce(brg, brg_loads);
	auto horiz_force_check = artifact.HorizontalForceCheck();
	auto deltaDLiB = brg_calc.GetInitialDeadLoadDeflectionMethodB(brg, brg_loads, spec);
	auto deltaLLiB = brg_calc.GetInstantaneousLiveLoadDeflectionMethodB(brg, brg_loads, spec);
	auto deltaLLiBCheck = artifact.MaximumLiveLoadDeflectionMethodBCheck();
	bool gMin_check = artifact.MinimumAllowableShearModulusCheck();
	bool gMax_check = artifact.MaximumAllowableShearModulusCheck();
	bool hri_check = artifact.RequiredIntermediateElastomerThicknessCheck();
	bool height_check = artifact.MinimumTotalBearingHeightCheck();
	bool minDistBrg2gBfCheck = artifact.MinimumBearingEdgeToBottomFlangeEdgeDistCheck();
	bool maxDistBrg2gBfCheck = artifact.MaximumBearingEdgeToBottomFlangeEdgeDistCheck();
	bool distBrg2gBfCheck = artifact.RequiredBearingEdgeToBottomFlangeEdgeDistCheck();
	bool maxTLCheck = artifact.MaximumTotalLoadCheck();

	CommonReportBearingSpecificationCheck(pDispUnits, pChapter, pPara, artifact);

	rptHeading* pHeading = rptStyleManager::CreateHeading();
	(*pChapter) << pHeading;
	pHeading->SetName(_T("Method B Analysis:"));
	*pHeading << _T("Method B Analysis:");
	pPara = new rptParagraph;
	(*pChapter) << pPara;

	rptHeading*  pSubHeading = pSubHeading = rptStyleManager::CreateSubHeading();
	(*pChapter) << pSubHeading;
	*pSubHeading << _T("Shear Modulus Range Checks:");
	pPara = new rptParagraph;
	(*pChapter) << pPara;

	*pPara << _T("Minimum limit for G = ") << E.SetValue(criteria.MinimumElastomerShearModulus) << _T(" (14.7.5.2)") << rptNewLine;
	if (gMin_check)
	{
		*pPara << symbol(RIGHT_SINGLE_ARROW) << E.SetValue(Gmin) << _T(" ") << symbol(GTE) << _T(" ") << E.SetValue(criteria.MinimumElastomerShearModulus);
		*pPara << _T(" ") << RPT_PASS << rptNewLine;
	}
	else
	{
		*pPara << symbol(RIGHT_SINGLE_ARROW) << E.SetValue(Gmin) << _T(" < ") << E.SetValue(criteria.MinimumElastomerShearModulus);
		*pPara << _T(" ") << RPT_FAIL << rptNewLine;
	}

	*pPara << _T("Maximum limit for G = ") << E.SetValue(criteria.MaximumElastomerShearModulus) << _T(" (14.7.5.2)") << rptNewLine;
	if (gMax_check)
	{
		*pPara << symbol(RIGHT_SINGLE_ARROW) << E.SetValue(Gmin) << _T(" ") << symbol(LTE) << _T(" ") << E.SetValue(criteria.MaximumElastomerShearModulus);
		*pPara << _T(" ") << RPT_PASS << rptNewLine;
	}
	else
	{
		*pPara << symbol(RIGHT_SINGLE_ARROW) << E.SetValue(Gmin) << _T(" > ") << E.SetValue(criteria.MaximumElastomerShearModulus);
		*pPara << _T(" ") << RPT_FAIL << rptNewLine;
	}

	*pPara << rptNewLine;

	pSubHeading = rptStyleManager::CreateSubHeading();
	(*pChapter) << pSubHeading;
	*pSubHeading << _T("Minimum Allowable Total Elastomer Thickness Check:");
	pPara = new rptParagraph;
	(*pChapter) << pPara;

	*pPara << _T("2 ") << symbol(TIMES) << _T(" ") << Sub2(symbol(DELTA), _T("s-st")) << _T(" = 2 (") << length.SetValue(sdef);
	*pPara << _T(") = ") << length.SetValue(2 * sdef) << rptNewLine;

	if (shear_def_check)
	{
		*pPara << symbol(RIGHT_SINGLE_ARROW) << length.SetValue(total_elastomer_thickness) << (total_elastomer_thickness == sdef ? _T(" = ") : _T(" > ")) << length.SetValue(2 * sdef) << _T(" ");
		*pPara << RPT_PASS;
	}
	else
	{
		*pPara << symbol(RIGHT_SINGLE_ARROW) << length.SetValue(total_elastomer_thickness) << _T(" < ") << length.SetValue(2 * sdef) << _T(" ");
		*pPara << RPT_FAIL;
	}
	*pPara << _T(" (14.7.5.3.2-1)");

	*pPara << rptNewLine << rptNewLine;

	pSubHeading = rptStyleManager::CreateSubHeading();
	(*pChapter) << pSubHeading;
	*pSubHeading << _T("Shear Strain Combination Check:");
	pPara = new rptParagraph;
	(*pChapter) << pPara;


	*pPara << _T("Compressibility Index, ");
	*pPara << symbol(lambda) << _T(" = S ") << symbol(TIMES) << _T(" ") << symbol(ROOT) << _T("(3 ") << symbol(TIMES);
	*pPara << Sub2(_T(" G"), _T("min")) << _T(" / K) = ");
	*pPara << s << symbol(ROOT) << _T("(3 ") << symbol(TIMES) << _T(" ") << stress.SetValue(Gmin) << _T(" / ");
	*pPara << stress.SetValue(K) << _T(") = ") << lambda;
	*pPara << _T(" (14.7.5.3.3-6)") << rptNewLine;
	*pPara << Sub2(_T("d"), _T("a1")) << _T(" = 1.06 + 0.210") << symbol(lambda) << _T(" + 0.413") << symbol(lambda) << Super(_T("2")) << _T(" = 1.06 + 0.210(");
	*pPara << lambda << _T(") + 0.413(") << lambda << _T(")") << Super(_T("2")) << _T(" = ") << da1 << _T(" (Comm. C14.7.5.3.3-3)") << rptNewLine;
	*pPara << Sub2(_T("d"), _T("a2")) << _T(" = 1.506 - 0.071") << symbol(lambda);
	*pPara << _T(" + 0.406") << symbol(lambda) << Super(_T("2")) << _T(" = 1.506 - 0.071(") << lambda << _T(") + 0.406(") << lambda;
	*pPara << _T(")") << Super(_T("2")) << _T(" = ") << da2 << _T(" (Comm. C14.7.5.3.3-4)") << rptNewLine;
	*pPara << Sub2(_T("d"), _T("a3")) << _T(" = -0.315 + 0.195") << symbol(lambda);
	*pPara << _T(" - 0.047") << symbol(lambda) << Super(_T("2")) << _T(" = -0.315 + 0.195(");
	*pPara << lambda << _T(") - 0.047(") << lambda << _T(")") << Super(_T("2")) << _T(" = ") << da3 << _T(" (Comm. C14.7.5.3.3-5)") << rptNewLine;

	*pPara << rptNewLine;

	rptHeading* pLevel3Heading = rptStyleManager::CreateHeading(3);
	(*pChapter) << pLevel3Heading;
	*pLevel3Heading << _T("Primary Direction : ");
	pPara = new rptParagraph;
	(*pChapter) << pPara;

	*pPara << symbol(RIGHT_SINGLE_ARROW) << Sub2(_T("d"), _T("a2")) << _T(" + ");
	*pPara << Sub2(_T("d"), _T("a3 ")) << symbol(TIMES) << _T(" L / W = ");
	*pPara << da2 << _T(" + ") << da3 << _T(" ") << symbol(TIMES) << _T(" ") << length.SetValue(l);
	*pPara << _T(" / ") << length.SetValue(w) << _T(" = ") << da2 + da3 * l / w << rptNewLine;

	if (da1 > da2 + da3 * l / w)
	{
		*pPara << symbol(RIGHT_SINGLE_ARROW) << _T(" ") << Sub2(_T("d"), _T("a1")) << _T(" = ") << da1;
		*pPara << _T(" > ") << da2 + da3 * l / w << rptNewLine;
	}
	else
	{
		*pPara << symbol(RIGHT_SINGLE_ARROW) << _T(" ") << Sub2(_T("d"), _T("a1")) << _T(" = ") << da1;
		*pPara << _T(" < ") << da2 + da3 * l / w << rptNewLine;
	}
	*pPara << symbol(RIGHT_SINGLE_ARROW) << _T("Axial Shear Strain Coefficient, ") << Sub2(_T("D"), _T("a")) << _T(" = ") << Dax << _T(" (Comm. C14.7.5.3.3-1)") << rptNewLine;
	*pPara << Sub2(_T("D"), _T("r")) << _T(" = (1.552 - 0.627") << symbol(lambda) << _T(") / (2.233 + 0.156") << symbol(lambda) << _T(" + L / W) = ");
	*pPara << _T("(1.552 - 0.627 ") << symbol(TIMES) << _T(" ") << lambda << _T(") / (2.233 + 0.156 ") << symbol(TIMES) << _T(" ") << lambda << _T(" + ");
	*pPara << length.SetValue(l) << _T(" / ") << length.SetValue(w) << _T(") = ");
	*pPara << (1.552 - 0.627 * lambda) / (2.223 + 0.156 * lambda + l / w) << rptNewLine;
	if ((1.552 - 0.627 * lambda) / (2.223 + 0.156 * lambda + l / w) < 0.5)
	{
		*pPara << symbol(RIGHT_SINGLE_ARROW) << (1.552 - 0.627 * lambda) / (2.223 + 0.156 * lambda + l / w) << _T(" < 0.5") << rptNewLine;
	}
	else
	{
		*pPara << symbol(RIGHT_SINGLE_ARROW) << (1.552 - 0.627 * lambda) / (2.223 + 0.156 * lambda + l / w) << _T(" > 0.5") << rptNewLine;
	}
	*pPara << symbol(RIGHT_SINGLE_ARROW) << _T("Rotational Shear Strain Coefficient, ") << Sub2(_T("D"), _T("r")) << _T(" = ") << Drx << _T(" (Comm. C14.7.5.3.3-2)") << rptNewLine;


	*pPara << _T("Static Stress, ") << Sub2(symbol(sigma), _T("st")) << _T(" = ") << Sub2(_T("P"), _T("D")) << _T(" / A = ") << force.SetValue(dl) << _T(" / ");
	*pPara << area.SetValue(a) << _T(" = ") << stress.SetValue(Sstatic) << rptNewLine;
	*pPara << _T("Static Axial Shear Strain, ") << Sub2(symbol(gamma), _T("a,st")) << _T(" = ") << Sub2(_T("D"), _T("a")) << _T(" ");
	*pPara << symbol(TIMES) << _T(" ") << Sub2(symbol(sigma), _T("st")) << _T("/") << Sub2(_T("G"), _T("min")) << _T(" / S = ") << Dax << _T(" ");
	*pPara << symbol(TIMES) << _T(" ") << stress.SetValue(Sstatic) << _T(" / ");
	*pPara << stress.SetValue(Gmin) << _T(" / ") << s << _T(" = ") << static_axial_X_ss << rptNewLine;
	if (static_axial_X_ss_check)
	{
		*pPara << symbol(RIGHT_SINGLE_ARROW) << static_axial_X_ss << (static_axial_X_ss == 3.0 ? _T(" = 3.0 ") : _T(" < 3.0 ")) << RPT_PASS;
	}
	else
	{
		*pPara << symbol(RIGHT_SINGLE_ARROW) << static_axial_X_ss << _T(" > 3.0 ") << RPT_FAIL;
	}
	*pPara << _T(" (14.7.5.3.3-2)") << rptNewLine;
	*pPara << _T("Static Rotational Shear Strain, ") << Sub2(symbol(gamma), _T("r,st")) << _T(" = ") << Sub2(_T("D"), _T("r "));
	*pPara << symbol(TIMES) << _T(" (L / ") << Sub2(_T("h"), _T("ri")) << _T(")") << Super(_T("2 ")) << symbol(TIMES) << _T(" ") << Sub2(symbol(theta), _T("st"));
	*pPara << _T(" / (n + ") << symbol(eta) << _T(") = ");
	*pPara << Drx << _T(" ") << symbol(TIMES) << _T(" (") << length.SetValue(l) << _T(" / ") << length.SetValue(tlayer) << _T(")") << Super(_T("2"));
	*pPara << symbol(TIMES) << _T(" ") << static_rotation << _T(" / (") << n << _T(" + ") << n_multiplier << _T(") = ") << es_rotx << rptNewLine;
	*pPara << _T("Static Displacement Shear Strain, ") << Sub2(symbol(gamma), _T("s,st")) << _T(" = ") << Sub2(symbol(DELTA), _T("s")) << _T(" / ") << Sub2(_T("h"), _T("rt")) << _T(" = ");
	*pPara << length.SetValue(sdef) << _T(" / ") << length.SetValue(total_elastomer_thickness) << _T(" = ") << Dsx << rptNewLine;
	*pPara << _T("Cyclic Stress, ") << Sub2(symbol(sigma), _T("cy")) << _T(" = ") << Sub2(_T("P"), _T("L")) << _T(" / A = ") << force.SetValue(ll) << _T(" / ");
	*pPara << area.SetValue(a) << _T(" = ") << stress.SetValue(Scyclic) << rptNewLine;
	*pPara << _T("Cyclic Axial Shear Strain, ") << Sub2(symbol(gamma), _T("a,cy")) << _T(" = ") << Sub2(_T("D"), _T("a")) << _T(" ");
	*pPara << symbol(TIMES) << _T(" ") << Sub2(symbol(sigma), _T("cy")) << _T(" / ") << Sub2(_T("G"), _T("min")) << _T(" / S = ") << Dax << _T(" ");
	*pPara << symbol(TIMES) << _T(" ") << stress.SetValue(Scyclic) << _T(" / ");
	*pPara << stress.SetValue(Gmin) << _T(" / ") << s << _T(" = ") << es_cyclic_axialx << rptNewLine;
	*pPara << _T("Cyclic Rotational Shear Strain, ") << Sub2(symbol(gamma), _T("r,cy")) << _T(" = ") << Sub2(_T("D"), _T("r "));
	*pPara << symbol(TIMES) << _T(" (L / ") << Sub2(_T("h"), _T("ri")) << _T(")") << Super(_T("2 ")) << symbol(TIMES) << _T(" ") << Sub2(symbol(theta), _T("cy"));
	*pPara << _T(" / (n + ") << symbol(eta) << _T(") = ");
	*pPara << Drx << _T(" ") << symbol(TIMES) << _T(" (") << length.SetValue(l) << _T(" / ") << length.SetValue(tlayer) << _T(")") << Super(_T("2"));
	*pPara << symbol(TIMES) << _T(" ") << cyclic_rotation << _T(" / (") << n << _T(" + ") << n_multiplier << _T(") = ") << es_cyclic_rotx << rptNewLine;
	*pPara << _T("Cyclic Displacement Shear Strain, ") << Sub2(symbol(gamma), _T("s,cy")) << _T(" = ") << es_cyclic_dispx << rptNewLine;

	*pPara << Sub2(symbol(gamma), _T("combo")) << _T(" = (");
	*pPara << Sub2(symbol(gamma), _T("a,st")) << _T(" + ") << Sub2(symbol(gamma), _T("r,st")) << _T(" + ") << Sub2(symbol(gamma), _T("s,st"));
	*pPara << _T(") + 1.75 ") << symbol(TIMES) << _T(" (") << Sub2(symbol(gamma), _T("a,cy")) << _T(" + ");
	*pPara << Sub2(symbol(gamma), _T("r,cy")) << _T(" + ") << Sub2(symbol(gamma), _T("s,cy")) << _T(") = (");
	*pPara << static_axial_X_ss << _T(" + ") << es_rotx << _T(" + ") << Dsx << _T(") + 1.75 (");
	*pPara << es_cyclic_axialx << _T(" + ") << es_cyclic_rotx << _T(" + ") << es_cyclic_dispx << _T(") = " << ss_X_combo_sum) << rptNewLine;
	*pPara << symbol(RIGHT_SINGLE_ARROW) << _T("|") << ss_X_combo_sum;
	if (ss_X_combo_sum_check)
	{
		*pPara << (ss_X_combo_sum == 5.0 ? _T("| = 5.0") : _T("| < 5.0 "));
		*pPara << RPT_PASS;
	}
	else
	{
		*pPara << _T("| > 5.0 ");
		*pPara << RPT_FAIL;
	}
	*pPara << _T(" (14.7.5.3.3-1)") << rptNewLine;

	*pPara << rptNewLine;

	pLevel3Heading = rptStyleManager::CreateHeading(3);
	(*pChapter) << pLevel3Heading;
	*pLevel3Heading << _T("Secondary Direction:");
	pPara = new rptParagraph;
	(*pChapter) << pPara;


	*pPara << symbol(RIGHT_SINGLE_ARROW) << Sub2(_T("d"), _T("a2")) << _T(" + ");
	*pPara << Sub2(_T("d"), _T("a3 ")) << symbol(TIMES) << _T(" W / L = ");
	*pPara << da2 << _T(" + ") << da3 << symbol(TIMES) << length.SetValue(w);
	*pPara << _T(" / ") << length.SetValue(l) << _T(" = ") << da2 + da3 * w / l << rptNewLine;

	if (da1 > da2 + da3 * w / l)
	{
		*pPara << symbol(RIGHT_SINGLE_ARROW) << _T(" ") << Sub2(_T("d"), _T("a1")) << _T(" = ") << da1;
		*pPara << _T(" > ") << da2 + da3 * w / l << rptNewLine;
	}
	else
	{
		*pPara << symbol(RIGHT_SINGLE_ARROW) << _T(" ") << Sub2(_T("d"), _T("a1")) << _T(" = ") << da1;
		*pPara << _T(" < ") << da2 + da3 * w / l << rptNewLine;
	}
	*pPara << symbol(RIGHT_SINGLE_ARROW) << _T("Axial Shear Strain Coefficient, ") << Sub2(_T("D"), _T("a")) << _T(" = ") << Day << _T(" (Comm. C14.7.5.3.3-1)") << rptNewLine;
	*pPara << Sub2(_T("D"), _T("r")) << _T(" = (1.552 - 0.627") << symbol(lambda) << _T(") / (2.233 + 0.156") << symbol(lambda) << _T(" + W / L) = ");
	*pPara << _T("(1.552 - 0.627") << symbol(TIMES) << lambda << _T(") / (2.233 + 0.156") << symbol(TIMES) << lambda << _T(" + ");
	*pPara << length.SetValue(w) << _T(" / ") << length.SetValue(l) << _T(") = ");
	*pPara << (1.552 - 0.627 * lambda) / (2.223 + 0.156 * lambda + w / l) << rptNewLine;
	if ((1.552 - 0.627 * lambda) / (2.223 + 0.156 * lambda + w / l) < 0.5)
	{
		*pPara << symbol(RIGHT_SINGLE_ARROW) << (1.552 - 0.627 * lambda) / (2.223 + 0.156 * lambda + w / l) << _T(" < 0.5") << rptNewLine;
	}
	else
	{
		*pPara << symbol(RIGHT_SINGLE_ARROW) << (1.552 - 0.627 * lambda) / (2.223 + 0.156 * lambda + w / l) << _T(" > 0.5") << rptNewLine;
	}
	*pPara << symbol(RIGHT_SINGLE_ARROW) << _T("Rotational Shear Strain Coefficient, ") << Sub2(_T("D"), _T("r")) << _T(" = ") << Dry;
	*pPara << _T(" (Comm. C14.7.5.3.3-2)") << rptNewLine;


	*pPara << _T("Static Stress, ") << Sub2(symbol(sigma), _T("st")) << _T(" = ") << Sub2(_T("P"), _T("D")) << _T(" / A = ") << force.SetValue(dl) << _T(" / ");
	*pPara << area.SetValue(a) << _T(" = ") << stress.SetValue(Sstatic) << rptNewLine;
	*pPara << _T("Static Axial Shear Strain, ") << Sub2(symbol(gamma), _T("a,st")) << _T(" = ") << Sub2(_T("D"), _T("a")) << _T(" ");
	*pPara << symbol(TIMES) << _T(" ") << Sub2(symbol(sigma), _T("st")) << _T(" / ") << Sub2(_T("G"), _T("min")) << _T(" / S = ") << Day << _T(" ");
	*pPara << symbol(TIMES) << _T(" ") << stress.SetValue(Sstatic) << _T(" / ");
	*pPara << stress.SetValue(Gmin) << _T(" / ") << s << _T(" = ") << static_axial_Y_ss << rptNewLine;
	if (static_axial_Y_ss_check)
	{
		*pPara << symbol(RIGHT_SINGLE_ARROW) << static_axial_Y_ss << (static_axial_Y_ss == 3.0 ? _T(" = 3.0 ") : _T(" < 3.0 ")) << RPT_PASS;
	}
	else
	{
		*pPara << symbol(RIGHT_SINGLE_ARROW) << static_axial_Y_ss << _T(" > ") << _T(" 3.0 ") << RPT_FAIL;
	}
	*pPara << _T(" (14.7.5.3.3-2)") << rptNewLine;
	*pPara << _T("Static Rotational Shear Strain, ") << Sub2(symbol(gamma), _T("r,st")) << _T(" = ") << Sub2(_T("D"), _T("r "));
	*pPara << symbol(TIMES) << _T(" (W / ") << Sub2(_T("h"), _T("ri")) << _T(")") << Super(_T("2 ")) << symbol(TIMES) << _T(" ") << _T("0.01");
	*pPara << _T(" / (n + ") << symbol(eta) << _T(") = ");
	*pPara << Dry << _T(" ") << symbol(TIMES) << _T(" (") << length.SetValue(w) << _T(" / ") << length.SetValue(tlayer) << _T(")") << Super(_T("2 "));
	*pPara << symbol(TIMES) << _T(" 0.01") << _T(" / (") << n << _T(" + ") << n_multiplier << _T(") = ") << es_roty << rptNewLine;
	*pPara << _T("Static Displacement Shear Strain, ") << Sub2(symbol(gamma), _T("s,st")) << _T(" = ") << Dsy << rptNewLine;
	*pPara << _T("Cyclic Axial Shear Strain, ") << Sub2(symbol(gamma), _T("a,cy")) << _T(" = ") << Sub2(_T("D"), _T("a")) << _T(" ");
	*pPara << symbol(TIMES) << _T(" ") << Sub2(symbol(sigma), _T("cy")) << _T(" / ") << Sub2(_T("G"), _T("min")) << _T(" / S = ") << Dax << _T(" ");
	*pPara << symbol(TIMES) << _T(" ") << stress.SetValue(Scyclic) << _T(" / ");
	*pPara << stress.SetValue(Gmin) << _T(" / ") << s << _T(" = ") << es_cyclic_axialy << rptNewLine;
	*pPara << _T("Cyclic Rotational Shear Strain, ") << Sub2(symbol(gamma), _T("r,cy")) << _T(" = ") << es_cyclic_roty << rptNewLine;
	*pPara << _T("Cyclic Displacement Shear Strain, ") << Sub2(symbol(gamma), _T("s,cy")) << _T(" = ") << es_cyclic_dispy << rptNewLine;


	*pPara << Sub2(symbol(gamma), _T("combo")) << _T(" = (");
	*pPara << Sub2(symbol(gamma), _T("a,st")) << _T(" + ") << Sub2(symbol(gamma), _T("r,st")) << _T(" + ") << Sub2(symbol(gamma), _T("s,st"));
	*pPara << _T(") + 1.75 ") << symbol(TIMES) << _T(" (") << Sub2(symbol(gamma), _T("a,cy")) << _T(" + ");
	*pPara << Sub2(symbol(gamma), _T("r,cy")) << _T(" + ") << Sub2(symbol(gamma), _T("s,cy")) << _T(") = (");
	*pPara << static_axial_Y_ss << _T(" + ") << es_roty << _T(" + ") << Dsy << _T(") + 1.75 (");
	*pPara << es_cyclic_axialy << _T(" + ") << es_cyclic_roty << _T(" + ") << es_cyclic_dispy << _T(") = " << ss_Y_combo_sum) << rptNewLine;
	*pPara << symbol(RIGHT_SINGLE_ARROW) << _T("|") << ss_Y_combo_sum;
	if (ss_Y_combo_sum_check)
	{
		*pPara << (ss_Y_combo_sum == 5.0 ? _T("| = 5.0 ") : _T("| < 5.0 "));
		*pPara << RPT_PASS;
	}
	else
	{
		*pPara << _T("| > 5.0 ");
		*pPara << RPT_FAIL;
	}
	*pPara << _T(" (14.7.5.3.3-1)") << rptNewLine;



	*pPara << rptNewLine;



	pSubHeading = pSubHeading = rptStyleManager::CreateSubHeading();
	(*pChapter) << pSubHeading;
	*pSubHeading << _T("Stability:");

	pLevel3Heading = rptStyleManager::CreateHeading(3);
	(*pChapter) << pLevel3Heading;
	*pLevel3Heading << _T("Primary Direction:");
	pPara = new rptParagraph;
	(*pChapter) << pPara;


	std::_tstring is_x_fixed;
	if (fixed_x)
	{
		is_x_fixed = _T("fixed");
	}
	else
	{
		is_x_fixed = _T("not fixed");
	}
	*pPara << _T("Translation is ") << is_x_fixed << symbol(RIGHT_SINGLE_ARROW) << Sub2(_T("K"), _T("eff")) << _T(" = ") << KeffX << rptNewLine;
	*pPara << _T(" A = 1.92 ") << symbol(TIMES) << Sub2(_T(" h"), _T("rt"));
	*pPara << _T(" / L /") << symbol(ROOT) << _T("1 + 2 ") << symbol(TIMES) << _T(" L / W) = 1.92 ") << symbol(TIMES) << _T(" ");
	*pPara << length.SetValue(total_elastomer_thickness) << _T(" / ") << length.SetValue(l);
	*pPara << _T("/") << symbol(ROOT) << _T("1 + 2") << symbol(TIMES) << length.SetValue(l) << _T("/");
	*pPara << length.SetValue(w) << _T(") = ") << Ax << rptNewLine;
	*pPara << _T("B = 2.67 / (S + 2) / (1 + L / 4 / W) = 2.67 / (");
	*pPara << s << _T("+ 2) / (1 + ") << length.SetValue(l) << _T("/4/") << length.SetValue(w);
	*pPara << _T(") = ") << Bx << rptNewLine;
	if (check_app_TL_stab_X)
	{
		*pPara << Sub2(symbol(sigma), _T("s,stab,max")) << _T(" = ");
		*pPara << Sub2(_T("G"), _T("min ")) << symbol(TIMES) << _T(" S / (") << Sub2(_T("K"), _T("eff ")) << symbol(TIMES);
		*pPara << _T(" A - B) = ") << stress.SetValue(Gmin) << _T(" ") << symbol(TIMES) << _T(" ") << s;
		*pPara << _T(" / (") << KeffX << _T(" ") << symbol(TIMES) << _T(" ") << Ax << _T(" - ") << Bx << _T(") = ");
		*pPara << stress.SetValue(sigmaTLstabX) << _T(" > 0") << symbol(RIGHT_SINGLE_ARROW) << _T(" Applies") << rptNewLine;

		if (stab_X_dir_check)
		{
			*pPara << symbol(RIGHT_SINGLE_ARROW) << stress.SetValue(tl_stress) << (tl_stress == sigmaTLstabX ? _T(" = ") : _T(" < "));
			*pPara << stress.SetValue(sigmaTLstabX) << _T(" ") << RPT_PASS;
		}
		else
		{
			*pPara << symbol(RIGHT_SINGLE_ARROW) << stress.SetValue(tl_stress) << _T(" > ");
			*pPara << stress.SetValue(sigmaTLstabX) << _T(" ") << RPT_FAIL;
		}
		*pPara << _T(" (14.7.5.3.4)") << rptNewLine;
	}
	else
	{
		*pPara << Sub2(_T("G"), _T("min ")) << symbol(TIMES) << _T(" S / (") << Sub2(_T("K"), _T("effX ")) << symbol(TIMES) << Sub2(_T(" A"), _T("x"));
		*pPara << _T(" - ") << Sub2(_T("B"), _T("x")) << _T(") = ") << stress.SetValue(Gmin) << symbol(TIMES) << s;
		*pPara << _T(" / (") << KeffX << symbol(TIMES) << _T(" ") << Ax << _T(" - ") << Bx << _T(") = ") << stress.SetValue(sigmaTLstabX);
		*pPara << _T(" < 0") << symbol(RIGHT_SINGLE_ARROW);
		*pPara << _T(" Does not apply") << rptNewLine;
	}

	*pPara << rptNewLine;



	pLevel3Heading = rptStyleManager::CreateHeading(3);
	(*pChapter) << pLevel3Heading;
	*pLevel3Heading << _T("Secondary Direction:");
	pPara = new rptParagraph;
	(*pChapter) << pPara;


	std::_tstring is_y_fixed;
	if (fixed_y)
	{
		is_y_fixed = _T("fixed");
	}
	else
	{
		is_y_fixed = _T("not fixed");
	}
	*pPara << _T("Translation is ") << is_y_fixed << symbol(RIGHT_SINGLE_ARROW) << Sub2(_T("K"), _T("eff")) << _T(" = ") << KeffY << rptNewLine;
	*pPara << _T("A = 1.92 ") << symbol(TIMES) << Sub2(_T(" h"), _T("rt"));
	*pPara << _T(" / W /") << symbol(ROOT) << _T("1 + 2 ") << symbol(TIMES) << _T(" W / L) = 1.92 ") << symbol(TIMES);
	*pPara << _T(" ") << length.SetValue(total_elastomer_thickness) << _T(" / ") << length.SetValue(w);
	*pPara << _T(" / ") << symbol(ROOT) << _T("1 + 2 ") << symbol(TIMES) << _T(" ") << length.SetValue(w) << _T(" / ");
	*pPara << length.SetValue(l) << _T(") = ") << Ay << rptNewLine;
	*pPara << _T("B = 2.67 / (S + 2) / (1 + W / 4 / L) = 2.67 / (");
	*pPara << s << _T("+ 2) / (1 + ") << length.SetValue(w) << _T("/4/") << length.SetValue(l);
	*pPara << _T(") = ") << By << rptNewLine;
	if (check_app_TL_stab_Y)
	{
		*pPara << Sub2(symbol(sigma), _T("s,stab,max")) << _T(" = ");
		*pPara << Sub2(_T(" G"), _T("min ")) << symbol(TIMES) << _T(" S / (") << Sub2(_T("K"), _T("eff ")) << symbol(TIMES);
		*pPara << _T(" A - B) = ") << stress.SetValue(Gmin) << _T(" ") << symbol(TIMES) << _T(" ") << s;
		*pPara << _T(" / (") << KeffY << _T(" ") << symbol(TIMES) << _T(" ") << Ay << _T(" - ") << By << _T(") = ");
		*pPara << stress.SetValue(sigmaTLstabY) << _T(" > 0") << symbol(RIGHT_SINGLE_ARROW) << _T(" Applies") << rptNewLine;

		if (stab_Y_dir_check)
		{
			*pPara << symbol(RIGHT_SINGLE_ARROW) << stress.SetValue(tl_stress) << (tl_stress == sigmaTLstabY ? _T(" = ") : _T(" < "));
			*pPara << stress.SetValue(sigmaTLstabY) << _T(" ") << RPT_PASS;
		}
		else
		{
			*pPara << symbol(RIGHT_SINGLE_ARROW) << stress.SetValue(tl_stress) << _T(" > ");
			*pPara << stress.SetValue(sigmaTLstabY) << _T(" ") << RPT_FAIL;
		}
		*pPara << _T(" (14.7.5.3.4)") << rptNewLine;
	}
	else
	{
		*pPara << Sub2(_T("G"), _T("min ")) << symbol(TIMES) << _T(" S / (") << Sub2(_T("K"), _T("effY ")) << symbol(TIMES) << Sub2(_T(" A"), _T("y"));
		*pPara << _T(" - ") << Sub2(_T("B"), _T("y")) << _T(") = ") << stress.SetValue(Gmin) << _T(" ") << symbol(TIMES) << _T(" ") << s;
		*pPara << _T(" / (") << KeffY << _T(" ") << symbol(TIMES) << _T(" ") << Ay << _T(" - ") << By << _T(") = ") << stress.SetValue(sigmaTLstabY);
		*pPara << _T(" < 0") << symbol(RIGHT_SINGLE_ARROW);
		*pPara << _T(" Does not apply") << rptNewLine;
	}

	*pPara << rptNewLine;

	if (!use_ext_plates)
	{
		pSubHeading = pSubHeading = rptStyleManager::CreateSubHeading();
		(*pChapter) << pSubHeading;
		*pSubHeading << _T("Restraint System Requirement:");
		pPara = new rptParagraph;
		(*pChapter) << pPara;

		*pPara << _T("Elastomer Elastic Modulus Method B, ") << Sub2(_T("E"), _T("B"));
		*pPara << _T(" = ") << Ecoeff << _T(" ") << symbol(TIMES) << Sub2(_T(" G"), _T("min ")) << symbol(TIMES) << _T(" ") << Super2(_T("S"), _T("2"));
		*pPara << _T(" = ") << Ecoeff << _T(" ") << symbol(TIMES) << _T(" ");
		*pPara << stress.SetValue(Gmin) << _T(" ") << symbol(TIMES) << _T(" ") << s << Super(_T("2")) << _T(" = ") << stress.SetValue(EcB) << rptNewLine;

		if (rest_system_req_check)
		{
			*pPara << symbol(RIGHT_SINGLE_ARROW) << _T("(") << Sub2(symbol(theta), _T("s,st")) << _T(" + 1.75") << Sub2(symbol(theta), _T("s,cy"));
			*pPara << _T(") ") << symbol(TIMES) << _T(" S / 3 / (n + ") << symbol(eta) << _T(") / (") << Sub2(symbol(sigma), _T("st"));
			*pPara << _T(" + 1.75") << Sub2(symbol(sigma), _T("cy")) << _T(") ") << symbol(TIMES) << Sub2(_T(" E"), _T("B")) << _T(" = (");
			*pPara << static_rotation << _T(" + 1.75 ") << symbol(TIMES) << _T(" ") << cyclic_rotation << _T(") ") << symbol(TIMES) << _T(" ") << s << _T(" / 3 / (");
			*pPara << n << _T(" + ") << n_multiplier << _T(") / (") << stress.SetValue(static_stress) << _T(" + 1.75 ") << symbol(TIMES) << stress.SetValue(cyclic_stress);
			*pPara << _T(") ") << symbol(TIMES) << _T(" ") << E.SetValue(EcB) << _T(" = ") << restraint_system_calc;
			*pPara << (restraint_system_calc == 1.0 ? _T(" = 1") : _T(" < 1 ")) << rptNewLine;
			*pPara << symbol(RIGHT_SINGLE_ARROW) << color(Green) << _T("NO RESTRAINT SYSTEM REQUIRED") << color(Green);
		}
		else
		{
			*pPara << symbol(RIGHT_SINGLE_ARROW) << _T("(") << Sub2(symbol(theta), _T("s,st")) << _T(" + 1.75") << Sub2(symbol(theta), _T("s,cy"));
			*pPara << _T(") ") << symbol(TIMES) << _T(" S / 3 / (n + ") << symbol(eta) << _T(") / (") << Sub2(symbol(sigma), _T("st"));
			*pPara << _T(" + 1.75") << Sub2(symbol(sigma), _T("cy")) << _T(") ") << symbol(TIMES) << Sub2(_T(" E"), _T("B")) << _T(" = (");
			*pPara << static_rotation << _T(" + 1.75 ") << symbol(TIMES) << _T(" ") << cyclic_rotation << _T(") ") << symbol(TIMES) << _T(" ") << s << _T(" / 3 / (");
			*pPara << n << _T(" + ") << n_multiplier << _T(") / (") << stress.SetValue(static_stress) << _T(" + 1.75 ") << stress.SetValue(cyclic_stress);
			*pPara << _T(") ") << symbol(TIMES) << _T(" ") << E.SetValue(EcB) << _T(" = ") << restraint_system_calc;
			*pPara << _T(" > 1 ") << rptNewLine;
			*pPara << symbol(RIGHT_SINGLE_ARROW) << color(Red) << _T("RESTRAINT SYSTEM REQUIRED") << color(Red);
		}
		*pPara << _T(" (SECTION 14.7.5.4)");

		*pPara << rptNewLine << rptNewLine;
	}

	if (use_ext_plates)
	{

		pSubHeading = pSubHeading = rptStyleManager::CreateSubHeading();
		(*pChapter) << pSubHeading;
		*pSubHeading << _T("Hydrostatic Stress:");
		pPara = new rptParagraph;
		(*pChapter) << pPara;

		*pPara << _T("Total axial strain, ") << Sub2(symbol(epsilon), _T("a"));
		*pPara << _T(" = (") << Sub2(symbol(sigma), _T("st")) << _T(" + 1.75 ");
		*pPara << symbol(TIMES) << _T(" ") << Sub2(symbol(sigma), _T("cy")) << _T(") / 3 / ");
		*pPara << Sub2(_T("B"), _T("a")) << _T(" / ") << Sub2(_T("G"), _T("min")) << _T(" / ") << Super2(_T("S"), _T("2")) << _T(" = (");
		*pPara << stress.SetValue(static_stress) << _T(" + 1.75 ") << symbol(TIMES) << _T(" ") << stress.SetValue(cyclic_stress) << _T(") / 3 / ");
		*pPara << peak_hyd << _T(" / ") << stress.SetValue(Gmin) << _T(" / ") << Super2(s, _T("2")) << _T(" = ");
		*pPara << total_axial_strain << rptNewLine;

		*pPara << symbol(alpha) << _T(" = ") << Sub2(symbol(epsilon), _T("a ")) << symbol(TIMES) << _T(" (n + ");
		*pPara << symbol(eta) << _T(") / S / (") << Sub2(symbol(theta), _T("st")) << _T(" + 1.75 ");
		*pPara << symbol(TIMES) << _T(" ") << Sub2(symbol(theta), _T("cy")) << _T(") = ") << total_axial_strain << _T(" ") << symbol(TIMES);
		*pPara << _T(" (") << n << _T(" + ") << n_multiplier << _T(") / ") << s << _T(" / (") << static_rotation << _T(" + 1.75 ");
		*pPara << symbol(TIMES) << _T(" ") << cyclic_rotation << _T(") = ") << alpha << rptNewLine;

		*pPara << _T("Ca = 4 / 3 ") << symbol(TIMES) << _T(" ((") << alpha << Super(_T("2")) << _T(" + 1 / 3 )") << Super(_T("1.5")) << _T(" - ") << alpha;
		*pPara << _T(" ") << symbol(TIMES) << _T(" (1 - ") << Super2(alpha, _T("2")) << _T(")) = ") << Ca << rptNewLine;

		*pPara << Sub2(symbol(sigma), _T("hyd")) << _T(" = 3 ") << symbol(TIMES) << Sub2(_T(" G"), _T("min "));
		*pPara << symbol(TIMES) << _T(" S") << Super(_T("3")) << _T(" (") << Sub2(symbol(theta), _T("st")) << _T(" + 1.75 ") << symbol(TIMES);
		*pPara << _T(" ") << Sub2(symbol(theta), _T("cy")) << _T(") / (n + ") << symbol(eta) << _T(") ") << symbol(TIMES);
		*pPara << _T(" Ca = 3 ") << symbol(TIMES) << _T(" ") << stress.SetValue(Gmin) << _T(" ") << symbol(TIMES) << _T(" ") << Super2(s, _T("3"));
		*pPara << _T(" ") << symbol(TIMES) << _T(" (") << static_rotation;
		*pPara << _T(" + 1.75 ") << symbol(TIMES) << _T(" ") << cyclic_rotation << _T(") / (") << n << _T(" + ") << n_multiplier << _T(")");
		*pPara << _T(" ") << symbol(TIMES) << _T(" ") << Ca << _T(" = ") << stress.SetValue(hydrostatic_stress) << rptNewLine;

		if (hydrostatic_check)
		{
			*pPara << symbol(RIGHT_SINGLE_ARROW) << stress.SetValue(max_stress) << (max_stress == hydrostatic_stress ? _T(" = ") : _T(" > ")) << stress.SetValue(hydrostatic_stress) << _T(" ");
			*pPara << RPT_PASS;
		}
		else
		{
			*pPara << symbol(RIGHT_SINGLE_ARROW) << stress.SetValue(max_stress) << _T(" < ") << stress.SetValue(hydrostatic_stress) << _T(" ");
			*pPara << RPT_FAIL;
		}
		*pPara << _T(" (14.7.5.3.3-11)");

		*pPara << rptNewLine << rptNewLine;
	}

	if (!use_ext_plates)
	{
		pSubHeading = pSubHeading = rptStyleManager::CreateSubHeading();
		(*pChapter) << pSubHeading;
		*pSubHeading << _T("Bearing Slip Check:");
		pPara = new rptParagraph;
		(*pChapter) << pPara;

		*pPara << _T("Horizontal Force, ") << Sub2(_T("F"), _T("horiz")) << _T(" = ") << Sub2(_T("G"), _T("min ")) << symbol(TIMES);
		*pPara << _T(" A ") << symbol(TIMES) << _T(" ") << Sub2(symbol(DELTA), _T("s")) << _T(" / ") << Sub2(_T("h"), _T("rt")) << _T(" = ");
		*pPara << E.SetValue(Gmin) << _T(" ") << symbol(TIMES) << _T(" ") << area.SetValue(a) << _T(" ") << symbol(TIMES) << _T(" ") << length.SetValue(sdef);
		*pPara << _T(" / ") << length.SetValue(total_elastomer_thickness) << _T(" = ");
		*pPara << force.SetValue(horiz_force) << rptNewLine;
		*pPara << symbol(RIGHT_SINGLE_ARROW) << symbol(mu) << Sub2(_T("P"), _T("D")) << _T(" = 0.20") << force.SetValue(dl);
		*pPara << force.SetValue(dl / 5) << rptNewLine;
		*pPara << symbol(RIGHT_SINGLE_ARROW);
		if (horiz_force_check)
		{
			*pPara << force.SetValue(horiz_force) << (horiz_force == dl / 5.0 ? _T(" = ") : _T(" < ")) << force.SetValue(dl / 5.0);
			*pPara << _T(" ") << RPT_PASS;
		}
		else
		{
			*pPara << force.SetValue(horiz_force) << _T(" > ") << force.SetValue(dl / 5.0);
			*pPara << _T(" ") << color(Red) << _T("RESTRAINT SYSTEM REQUIRED") << color(Red);
		}

		*pPara << rptNewLine << rptNewLine;
	}

	pSubHeading = rptStyleManager::CreateSubHeading();
	(*pChapter) << pSubHeading;
	*pSubHeading << _T("Initial Dead Load Deflection:");
	pPara = new rptParagraph;
	(*pChapter) << pPara;

	*pPara << Sub2(symbol(delta), _T("D-initial")) << Sub2(_T(" = P"), _T("D")) << symbol(TIMES) << Sub2(_T(" h"), _T("rt"));
	*pPara << _T(" / A / ") << Sub2(_T("E"), _T("B")) << _T(" = ");
	*pPara << force.SetValue(dl) << _T(" ") << symbol(TIMES) << _T(" ") << length.SetValue(total_elastomer_thickness);
	*pPara << _T(" / ") << area.SetValue(a) << _T(" / ") << E.SetValue(EcB) << _T(" = ");
	*pPara << length.SetValue(deltaDLiB) << _T(" (Comm. C14.7.5.3.6-1)");

	*pPara << rptNewLine << rptNewLine;

	pSubHeading = rptStyleManager::CreateSubHeading();
	(*pChapter) << pSubHeading;
	*pSubHeading << _T("Instantaneous Live Load Deflection:");
	pPara = new rptParagraph;
	(*pChapter) << pPara;

	*pPara << Sub2(symbol(delta), _T("L ")) << _T(" = LL ") << symbol(TIMES) << Sub2(_T(" h"), _T("rt"));
	*pPara << _T(" / A / ") << Sub2(_T("E"), _T("B")) << _T(" = ");
	*pPara << force.SetValue(ll) << _T(" ") << symbol(TIMES) << _T(" ") << length.SetValue(total_elastomer_thickness);
	*pPara << _T(" / ") << area.SetValue(a) << _T(" / ") << E.SetValue(EcB) << _T(" = ");
	*pPara << length.SetValue(deltaLLiB) << _T(" (Comm. C14.7.5.3.6-1)") << rptNewLine;

	if (deltaLLiBCheck)
	{
		*pPara << symbol(RIGHT_SINGLE_ARROW) << length.SetValue(deltaLLiB) << _T(" ") << symbol(LTE) << _T(" ") << length.SetValue(criteria.maxLLdef) << _T(" ") << RPT_PASS;
	}
	else
	{
		*pPara << symbol(RIGHT_SINGLE_ARROW) << length.SetValue(deltaLLiB) << _T(" > ") << length.SetValue(criteria.maxLLdef) << _T(" ") << RPT_FAIL;
	}

	*pPara << rptNewLine << rptNewLine;

	pSubHeading = pSubHeading = rptStyleManager::CreateSubHeading();
	(*pChapter) << pSubHeading;
	*pSubHeading << _T("Maximum Allowable Shape Factor, for applicability of Method A:");
	pPara = new rptParagraph;
	(*pChapter) << pPara;

	*pPara << Sub2(_T("S"), _T("max")) << _T(" = ") << symbol(ROOT) << _T("22 ") << symbol(TIMES) << _T(" (n + ");
	*pPara << symbol(eta) << _T(")) = ") << symbol(ROOT) << _T(" 22 ") << symbol(TIMES) << _T(" (") << n << _T(" + ") << n_multiplier << _T(")) = ") << s_max << rptNewLine;

	if (s_max_check)
	{
		*pPara << symbol(RIGHT_SINGLE_ARROW) << s << (s == s_max ? _T(" = ") : _T(" < ")) << s_max << _T(" ") << RPT_PASS << _T(" (Method A can be used per SECTION 14.7.6.1) ") << rptNewLine;
	}
	else
	{
		*pPara << color(Red) << symbol(RIGHT_SINGLE_ARROW) << s << _T(" > ") << s_max << _T(" ") << RPT_FAIL << color(Red) << _T(" (METHOD A CANNOT BE USED per SECTION 14.7.6.1) ") << color(Red) << rptNewLine;
	}

}



void BearingReporter::BuildSpecCheckChapter(const WBFL::Units::IndirectMeasure* pDispUnits, 
	rptChapter* pChapter, rptParagraph* pPara, const WBFL::EngTools::BearingCheckArtifact& artifact)
{

	ReportIntroduction(pPara, artifact);
	ReportBearingProperties(pDispUnits, pChapter, pPara, artifact);

	const auto& criteria = artifact.GetBearingDesignCriteria();

	if (criteria.AnalysisMethod == WBFL::EngTools::BearingAnalysisMethod::MethodA)
	{
		ReportBearingSpecCheckSummaryA(pChapter, pPara, artifact);

		ReportBearingSpecificationCheckA(pDispUnits, pChapter, pPara, artifact);
	}
	else
	{
		ReportBearingSpecCheckSummaryB(pChapter, pPara, artifact);

		ReportBearingSpecificationCheckB(pDispUnits, pChapter, pPara, artifact);
	}
}


