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

#include <Stability\StabilityLib.h>
#include <Stability\HaulingTensionStressLimit.h>
#include <Stability\HaulingCheckArtifact.h>
#include <UnitMgt\UnitMgt.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace WBFL::Stability;

CCHaulingTensionStressLimit::CCHaulingTensionStressLimit()
{
   Lambda = 0.0;

   for (int s = 0; s < 2; s++)
   {
      HaulingSlope slope = (HaulingSlope)s;
      TensionCoefficient[slope] = 0;
      bMaxTension[slope] = false;
      MaxTension[slope] = 0;
      TensionCoefficientWithRebar[slope] = 0;
      AllowableTension[slope] = 0;
      AllowableTensionWithRebar[slope] = 0;
   }
}

#if defined REBAR_FOR_DIRECT_TENSION
Float64 CCHaulingTensionStressLimit::GetTensionLimit(HaulingSlope slope, const HaulingSectionResult& sectionResult, ImpactDirection impact) const
{
   if (sectionResult.altTensionRequirements[slope][impact].bIsAdequateRebar && 0 <= sectionResult.altTensionRequirements[slope][impact].AsRequired)
   {
      return AllowableTensionWithRebar[slope];
   }
   else
   {
      return AllowableTension[slope];
   }
}
#else
Float64 CCHaulingTensionStressLimit::GetTensionLimit(HaulingSlope slope, const HaulingSectionResult& sectionResult, ImpactDirection impact, WindDirection wind) const
{
   if (sectionResult.altTensionRequirements[slope][impact][wind].bIsAdequateRebar && 0 <= sectionResult.altTensionRequirements[slope][impact][wind].AsRequired)
   {
      return AllowableTensionWithRebar[slope];
   }
   else
   {
      return AllowableTension[slope];
   }
}
#endif

Float64 CCHaulingTensionStressLimit::GetRequiredFcTension(HaulingSlope slope, const HaulingCheckArtifact* pArtifact) const
{
   return Min(GetRequiredFcTensionWithoutRebar(slope,pArtifact), GetRequiredFcTensionWithRebar(slope,pArtifact));
}

void CCHaulingTensionStressLimit::ReportTensionLimit(HaulingSlope slope, rptParagraph* pPara, const unitmgtIndirectMeasure* pDisplayUnits) const
{
   INIT_UV_PROTOTYPE(rptSqrtPressureValue, tension_coeff, pDisplayUnits->SqrtPressure, false);
   INIT_UV_PROTOTYPE(rptStressUnitValue, stress, pDisplayUnits->Stress, true);

   bool bLambda = (lrfdVersionMgr::SeventhEditionWith2016Interims <= lrfdVersionMgr::GetVersion() ? true : false);

   *pPara << _T("Tension stress limit = ") << tension_coeff.SetValue(TensionCoefficient[slope]);
   if (bLambda)
   {
      *pPara << symbol(lambda);
   }
   *pPara << symbol(ROOT) << RPT_FC;
   if (bMaxTension[slope])
   {
      *pPara << _T(" but not more than ") << stress.SetValue(MaxTension[slope]);
   }
   *pPara << _T(" = ") << stress.SetValue(AllowableTension[slope]) << rptNewLine;

   if (bWithRebarLimit[slope])
   {
      *pPara << _T("Tension stress limit = ") << tension_coeff.SetValue(TensionCoefficientWithRebar[slope]);
      if (bLambda)
      {
         *pPara << symbol(lambda);
      }
      *pPara << symbol(ROOT) << RPT_FC;
      *pPara << _T(" if bonded reinforcement sufficient to resist the tensile force in the concrete is provided = ") << stress.SetValue(AllowableTensionWithRebar[slope]) << rptNewLine;
   }
   else
   {
      *pPara << _T("Tensile stress limit with bonded reinforcement sufficient to resist tension force in concrete was not evaluated because reinforcement is not modeled.") << rptNewLine;
   }
}

void CCHaulingTensionStressLimit::ReportRequiredConcreteStrength(HaulingSlope slope,const HaulingCheckArtifact* pArtifact, rptParagraph* pPara, const unitmgtIndirectMeasure* pDisplayUnits) const
{
   INIT_UV_PROTOTYPE(rptStressUnitValue, stress, pDisplayUnits->Stress, true);

   Float64 fcReqd = GetRequiredFcTensionWithoutRebar(slope,pArtifact);
   *pPara << RPT_FC << _T(" required for tensile stress = ");
   if (fcReqd < 0)
   {
      ATLASSERT(fcReqd == -99999);
      *pPara << _T("Regardless of the concrete strength, the stress requirements will not be satisfied.") << rptNewLine;
   }
   else
   {
      *pPara << stress.SetValue(fcReqd) << rptNewLine;
   }

   if (bWithRebarLimit[slope])
   {
      fcReqd = GetRequiredFcTensionWithRebar(slope, pArtifact);
      *pPara << RPT_FC << _T(" required for tensile stress with bonded reinforcement sufficient to resist the tensile force in the concrete = ");
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

Float64 CCHaulingTensionStressLimit::GetRequiredFcTensionWithoutRebar(HaulingSlope slope, const HaulingCheckArtifact* pArtifact) const
{
   Float64 maxStress = pArtifact->GetHaulingResults().MaxStress[slope];
   Float64 fcReqd = 0;
   if (0 < maxStress)
   {
      fcReqd = pow(maxStress / (Lambda * TensionCoefficient[slope]), 2);
   }

   if (bMaxTension[slope] && MaxTension[slope] < maxStress)
   {
      fcReqd = -99999; // doesn't matter what f'c is, tension will never be satisfied
   }

   return fcReqd;
}

Float64 CCHaulingTensionStressLimit::GetRequiredFcTensionWithRebar(HaulingSlope slope, const HaulingCheckArtifact* pArtifact) const
{
   Float64 maxStress = pArtifact->GetHaulingResults().MaxStress[slope];
   Float64 fcReqd = 0;
   if (0 < maxStress)
   {
      fcReqd = pow(maxStress / (Lambda * TensionCoefficientWithRebar[slope]), 2);
   }

   return fcReqd;
}


UHPCHaulingTensionStressLimit::UHPCHaulingTensionStressLimit()
{
   AllowableTension[CrownSlope] = 0;
   AllowableTension[Superelevation] = 0;
}

#if defined REBAR_FOR_DIRECT_TENSION
Float64 UHPCHaulingTensionStressLimit::GetTensionLimit(HaulingSlope slope, const HaulingSectionResult& sectionResult, ImpactDirection impact) const
{
   return AllowableTension[slope];
}
#else
Float64 UHPCHaulingTensionStressLimit::GetTensionLimit(HaulingSlope slope, const HaulingSectionResult& sectionResult, ImpactDirection impact, WindDirection wind) const
{
   return AllowableTension[slope];
}
#endif


void UHPCHaulingTensionStressLimit::ReportTensionLimit(HaulingSlope slope, rptParagraph* pPara, const unitmgtIndirectMeasure* pDisplayUnits) const
{
   INIT_UV_PROTOTYPE(rptStressUnitValue, stress, pDisplayUnits->Stress, true);
   *pPara << _T("Tension stress limit = (2/3)") << RPT_STRESS(_T("fc")) << _T(" = ") << stress.SetValue(AllowableTension[slope]) << rptNewLine;
}

void UHPCHaulingTensionStressLimit::ReportRequiredConcreteStrength(HaulingSlope slope, const HaulingCheckArtifact* pArtifact, rptParagraph* pPara, const unitmgtIndirectMeasure* pDisplayUnits) const
{
   // Do nothing - tension stress limit is not a function of concrete strength
}
