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

#include <Stability\StabilityLib.h>
#include <Stability\LiftingTensionStressLimit.h>
#include <Stability\LiftingCheckArtifact.h>
#include <UnitMgt\UnitMgt.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace WBFL::Stability;

CCLiftingTensionStressLimit::CCLiftingTensionStressLimit()
{
   Lambda = 0.0;

   TensionCoefficient = 0;
   bMaxTension = false;
   MaxTension = 0;

   AllowableTension = 0;
   AllowableTensionWithRebar = 0;
}

#if defined REBAR_FOR_DIRECT_TENSION
Float64 CCLiftingTensionStressLimit::GetTensionLimit(const LiftingSectionResult& sectionResult, ImpactDirection impact) const
{
   if (sectionResult.altTensionRequirements[impact].bIsAdequateRebar && 0 <= sectionResult.altTensionRequirements[impact].AsRequired)
   {
      return AllowableTensionWithRebar;
   }
   else
   {
      return AllowableTension;
   }
}
#else
Float64 CCLiftingTensionStressLimit::GetTensionLimit(const LiftingSectionResult& sectionResult, ImpactDirection impact, WindDirection wind) const
{
   if (sectionResult.altTensionRequirements[impact][wind].bIsAdequateRebar && 0 <= sectionResult.altTensionRequirements[impact][wind].AsRequired)
   {
      return AllowableTensionWithRebar;
   }
   else
   {
      return AllowableTension;
   }
}
#endif

Float64 CCLiftingTensionStressLimit::GetRequiredFcTension(const LiftingCheckArtifact* pArtifact) const
{
   return Min(GetRequiredFcTensionWithoutRebar(pArtifact), GetRequiredFcTensionWithRebar(pArtifact));
}

Float64 CCLiftingTensionStressLimit::GetRequiredFcTensionWithoutRebar(const LiftingCheckArtifact* pArtifact) const
{
   Float64 maxStress = pArtifact->GetLiftingResults().MaxStress;

   Float64 fcReqd = 0;
   if (0 < maxStress)
   {
      fcReqd = pow(maxStress / (Lambda * TensionCoefficient), 2);
   }

   if (bMaxTension && MaxTension < maxStress)
   {
      fcReqd = -99999; // doesn't matter what f'c is, tension will never be satisfied
   }

   return fcReqd;
}

Float64 CCLiftingTensionStressLimit::GetRequiredFcTensionWithRebar(const LiftingCheckArtifact* pArtifact) const
{
   Float64 maxStress = pArtifact->GetLiftingResults().MaxStress;

   Float64 fcReqd = 0;
   if (0 < maxStress)
   {
      fcReqd = pow(maxStress / (Lambda * TensionCoefficientWithRebar), 2);
   }
   return fcReqd;
}

void CCLiftingTensionStressLimit::ReportTensionLimit(rptParagraph* pPara, const unitmgtIndirectMeasure* pDisplayUnits) const
{
   INIT_UV_PROTOTYPE(rptSqrtPressureValue, tension_coeff, pDisplayUnits->SqrtPressure, false);
   INIT_UV_PROTOTYPE(rptStressUnitValue, stress, pDisplayUnits->Stress, true);

   bool bLambda = (lrfdVersionMgr::SeventhEditionWith2016Interims <= lrfdVersionMgr::GetVersion() ? true : false);

   *pPara << _T("Tension stress limit = ") << tension_coeff.SetValue(TensionCoefficient);
   if (bLambda)
   {
      *pPara << symbol(lambda);
   }
   *pPara << symbol(ROOT) << RPT_FCI;
   if (bMaxTension)
   {
      *pPara << _T(" but not more than ") << stress.SetValue(MaxTension);
   }
   *pPara << _T(" = ") << stress.SetValue(AllowableTension) << rptNewLine;

   if (bWithRebarLimit)
   {
      *pPara << _T("Tension stress limit = ") << tension_coeff.SetValue(TensionCoefficientWithRebar);
      if (bLambda)
      {
         *pPara << symbol(lambda);
      }
      *pPara << symbol(ROOT) << RPT_FCI;
      *pPara << _T(" if bonded reinforcement sufficient to resist the tensile force in the concrete is provided = ") << stress.SetValue(AllowableTensionWithRebar) << rptNewLine;
   }
   else
   {
      *pPara << _T("Tensile stress limit with bonded reinforcement sufficient to resist tension force in concrete was not evaluated because reinforcement is not modeled.") << rptNewLine;
   }
}

void CCLiftingTensionStressLimit::ReportRequiredConcreteStrength(const LiftingCheckArtifact* pArtifact, rptParagraph* pPara, const unitmgtIndirectMeasure* pDisplayUnits) const
{
   INIT_UV_PROTOTYPE(rptStressUnitValue, stress, pDisplayUnits->Stress, true);

   Float64 fcReqd = GetRequiredFcTensionWithoutRebar(pArtifact);;
   *pPara << RPT_FCI << _T(" required for tensile stress = ");
   if (fcReqd < 0)
   {
      ATLASSERT(fcReqd == -99999);
      *pPara << _T("Regardless of the concrete strength, the stress requirements will not be satisfied.") << rptNewLine;
   }
   else
   {
      *pPara << stress.SetValue(fcReqd) << rptNewLine;
   }

   if (bWithRebarLimit)
   {
      fcReqd = GetRequiredFcTensionWithRebar(pArtifact);
      *pPara << RPT_FCI << _T(" required for tensile stress with bonded reinforcement sufficient to resist the tensile force in the concrete = ");
      if (fcReqd < 0)
      {
         ATLASSERT(fcReqd == -99999);
         *pPara << _T("Regardless of the concrete strength, the stress requirements will not be satisfied.") << rptNewLine;
      }
      else
      {
         *pPara << stress.SetValue(fcReqd) << rptNewLine;
      }
   }
}



UHPCLiftingTensionStressLimit::UHPCLiftingTensionStressLimit()
{
   ffc = 0;
   fc28 = 0;
   AllowableTension = 0;
}

#if defined REBAR_FOR_DIRECT_TENSION
Float64 UHPCLiftingTensionStressLimit::GetTensionLimit(const LiftingSectionResult& sectionResult, ImpactDirection impact) const
{
   return AllowableTension;
}
#else
Float64 UHPCLiftingTensionStressLimit::GetTensionLimit(const LiftingSectionResult& sectionResult, ImpactDirection impact, WindDirection wind) const
{
   return AllowableTension;
}
#endif

Float64 UHPCLiftingTensionStressLimit::GetRequiredFcTension(const LiftingCheckArtifact* pArtifact) const
{
   Float64 maxStress = pArtifact->GetLiftingResults().MaxStress;
   Float64 fcReqd = pow(1.5 * maxStress / ffc, 2) * fc28;
   return fcReqd;
}

Float64 UHPCLiftingTensionStressLimit::GetRequiredFcTensionWithoutRebar(const LiftingCheckArtifact* pArtifact) const
{
    return GetRequiredFcTension(pArtifact);
}

Float64 UHPCLiftingTensionStressLimit::GetRequiredFcTensionWithRebar(const LiftingCheckArtifact* pArtifact) const
{
    return GetRequiredFcTension(pArtifact);
}

void UHPCLiftingTensionStressLimit::ReportTensionLimit(rptParagraph* pPara, const unitmgtIndirectMeasure* pDisplayUnits) const
{
   INIT_UV_PROTOTYPE(rptStressUnitValue, stress, pDisplayUnits->Stress, true);
   *pPara << _T("Tension stress limit = (2/3)(") << RPT_STRESS(_T("fc")) << _T(")") << symbol(ROOT) << _T("(") << RPT_FCI << _T("/") << RPT_FC << _T(")") << _T(" = ") << stress.SetValue(AllowableTension) << rptNewLine;
}

void UHPCLiftingTensionStressLimit::ReportRequiredConcreteStrength(const LiftingCheckArtifact* pArtifact, rptParagraph* pPara, const unitmgtIndirectMeasure* pDisplayUnits) const
{
   INIT_UV_PROTOTYPE(rptStressUnitValue, stress, pDisplayUnits->Stress, true);

   Float64 fcReqd = GetRequiredFcTension(pArtifact);
   *pPara << RPT_FCI << _T(" required for tensile stress = ");
   if (fcReqd < 0)
   {
      ATLASSERT(fcReqd == -99999);
      *pPara << _T("Regardless of the concrete strength, the stress requirements will not be satisfied.") << rptNewLine;
   }
   else
   {
      *pPara << stress.SetValue(fcReqd) << rptNewLine;
   }
}
