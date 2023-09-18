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

#include <Stability/StabilityLib.h>
#include <Stability/HaulingCheckArtifact.h>

using namespace WBFL::Stability;

HaulingCheckArtifact::HaulingCheckArtifact()
{
}

HaulingCheckArtifact::HaulingCheckArtifact(const HaulingResults& results, const HaulingCriteria& criteria)
{
   Init(results, criteria);
}

void HaulingCheckArtifact::Init(const HaulingResults& results, const HaulingCriteria& criteria)
{
   m_Results = results;
   m_Criteria = criteria;
}

const HaulingResults& HaulingCheckArtifact::GetHaulingResults() const
{
   return m_Results;
}

const HaulingCriteria& HaulingCheckArtifact::GetCriteria() const
{
   return m_Criteria;
}

ControllingTensionCase HaulingCheckArtifact::GetControllingTensionCase(HaulingSlope slope, const HaulingSectionResult& sectionResult) const
{
   ControllingTensionCase controlling_case;

   Float64 Fallow;
   Float64 CD = Float64_Max;
   for (int i = 0; i < 3; i++)
   {
      ImpactDirection impact = (ImpactDirection)i;
#if defined REBAR_FOR_DIRECT_TENSION
      Float64 fAllow = GetAllowableTension(slope, sectionResult, impact);
#endif
      for (int w = 0; w < 2; w++)
      {
         WindDirection wind = (WindDirection)w;

#if !defined REBAR_FOR_DIRECT_TENSION
         Float64 fAllow = GetAllowableTension(slope, sectionResult, impact, wind);
#endif

         auto [cd, corner] = WBFL::Math::CDRatio::MinCDRatio(WBFL::Math::CDRatio::Sense::Positive,
            fAllow, sectionResult.f[+slope][+impact][+wind][+Corner::TopLeft],
            fAllow, sectionResult.f[+slope][+impact][+wind][+Corner::TopRight],
            fAllow, sectionResult.f[+slope][+impact][+wind][+Corner::BottomLeft],
            fAllow, sectionResult.f[+slope][+impact][+wind][+Corner::BottomRight]);

         if ((i == 0 && w == 0) || // this is the first time so this cd wins
            (CD < 0 && 0 <= cd) || // there is a sign change and the current cd is a positive value
            (0 <= cd && (0 <= CD ? cd < CD : fabs(CD) < fabs(cd)))
            )
         {
            CD = cd;
            controlling_case.impact = impact;
            controlling_case.wind = wind;
            controlling_case.corner = (Corner)corner;
            Fallow = fAllow;
         }
      }
   }

   controlling_case.stress_limit = Fallow;
   controlling_case.bPassed = (::IsLE(sectionResult.f[+slope][+(controlling_case.impact)][+(controlling_case.wind)][+(controlling_case.corner)], controlling_case.stress_limit));
   controlling_case.CD = CD;
   return controlling_case;
}

ControllingGlobalCompressionCase HaulingCheckArtifact::GetControllingGlobalCompressionCase(HaulingSlope slope, const HaulingSectionResult& sectionResult) const
{
   ControllingGlobalCompressionCase controlling_case;
   Float64 fAllow = m_Criteria.AllowableCompression_GlobalStress;
   Float64 CD = Float64_Max;
   for (int i = 0; i < 3; i++)
   {
      ImpactDirection impact = (ImpactDirection)i;

      auto [cd, corner] = WBFL::Math::CDRatio::MinCDRatio(WBFL::Math::CDRatio::Sense::Negative,
         fAllow, sectionResult.fDirect[+slope][+impact][+Corner::TopLeft],
         fAllow, sectionResult.fDirect[+slope][+impact][+Corner::TopRight],
         fAllow, sectionResult.fDirect[+slope][+impact][+Corner::BottomLeft],
         fAllow, sectionResult.fDirect[+slope][+impact][+Corner::BottomRight]);

      if ((i == 0) || // this is the first time so this cd wins
         (CD < 0 && 0 <= cd) || // there is a sign change and the current cd is a positive value
         (0 <= cd && 0 <= CD ? cd < CD : fabs(CD) < fabs(cd))
         )
      {
         CD = cd;
         controlling_case.impact = impact;
         controlling_case.corner = (Corner)corner;
      }
   }

   controlling_case.stress_limit = fAllow;
   controlling_case.bPassed = (::IsLT(controlling_case.stress_limit, sectionResult.fDirect[+slope][+(controlling_case.impact)][+(controlling_case.corner)]));
   controlling_case.CD = CD;
   return controlling_case;
}

ControllingPeakCompressionCase HaulingCheckArtifact::GetControllingPeakCompressionCase(HaulingSlope slope, const HaulingSectionResult& sectionResult) const
{
   ControllingPeakCompressionCase controlling_case;
   Float64 fAllow = m_Criteria.AllowableCompression_PeakStress;
   Float64 CD = Float64_Max;
   for (int i = 0; i < 3; i++)
   {
      ImpactDirection impact = (ImpactDirection)i;
      for (int w = 0; w < 2; w++)
      {
         WindDirection wind = (WindDirection)w;
         auto [cd,corner] = WBFL::Math::CDRatio::MinCDRatio(WBFL::Math::CDRatio::Sense::Negative,
            fAllow, sectionResult.f[+slope][+impact][+wind][+Corner::TopLeft],
            fAllow, sectionResult.f[+slope][+impact][+wind][+Corner::TopRight],
            fAllow, sectionResult.f[+slope][+impact][+wind][+Corner::BottomLeft],
            fAllow, sectionResult.f[+slope][+impact][+wind][+Corner::BottomRight]);

         if ((i == 0 && w == 0) || // this is the first time so this cd wins
            (CD < 0 && 0 <= cd) || // there is a sign change and the current cd is a positive value
            (0 <= cd && 0 <= CD ? cd < CD : fabs(CD) < fabs(cd))
            )
         {
            CD = cd;
            controlling_case.impact = impact;
            controlling_case.wind = wind;
            controlling_case.corner = (Corner)corner;
         }
      }
   }

   controlling_case.stress_limit = fAllow;
   controlling_case.bPassed = (::IsLT(controlling_case.stress_limit, sectionResult.f[+slope][+(controlling_case.impact)][+(controlling_case.wind)][+(controlling_case.corner)]));
   controlling_case.CD = CD;
   return controlling_case;
}

bool HaulingCheckArtifact::Passed(bool bIgnoreConfigurationLimits) const
{
   bool bPassed = (Passed(HaulingSlope::CrownSlope) && Passed(HaulingSlope::Superelevation) ? true : false);
   bPassed = bPassed && PassedDirectStressCheck(HaulingSlope::CrownSlope) && PassedDirectStressCheck(HaulingSlope::Superelevation);
   if (!bIgnoreConfigurationLimits)
   {
      bPassed = bPassed && PassedClearSpan() && PassedLeadingOverhang() && PassedMaxWeight();
   }
   return bPassed;
}

bool HaulingCheckArtifact::Passed(HaulingSlope slope) const
{
   for (int i = 0; i < 3; i++)
   {
      ImpactDirection impact = (ImpactDirection)i;
      for (int w = 0; w < 2; w++)
      {
         WindDirection wind = (WindDirection)w;
         if (!m_Results.bRotationalStability[+slope][+impact][+wind] || !m_Results.bRolloverStability[+slope][+impact][+wind])
         {
            return false;
         }
      }
   }
   return (PassedCrackingCheck(slope) && PassedFailureCheck(slope) && PassedRolloverCheck(slope) && PassedStressCheck(slope));
}

bool HaulingCheckArtifact::PassedCrackingCheck(HaulingSlope slope) const
{
   return m_Criteria.MinFScr < m_Results.MinFScr[+slope];
}

bool HaulingCheckArtifact::PassedFailureCheck(HaulingSlope slope) const
{
   return m_Criteria.MinFSf < m_Results.MinFsFailure[+slope];
}

bool HaulingCheckArtifact::PassedRolloverCheck(HaulingSlope slope) const
{
   return m_Criteria.MinFSf < m_Results.MinFsRollover[+slope];
}

bool HaulingCheckArtifact::PassedStressCheck(HaulingSlope slope) const
{
   return PassedCompressionCheck(slope) && PassedTensionCheck(slope);
}

bool HaulingCheckArtifact::PassedDirectStressCheck(HaulingSlope slope) const
{
   return PassedDirectCompressionCheck(slope) && PassedDirectTensionCheck(slope);
}

bool HaulingCheckArtifact::PassedDirectCompressionCheck(HaulingSlope slope) const
{
   return (::IsLE(m_Criteria.AllowableCompression_GlobalStress, m_Results.MinDirectStress[+slope]) ? true : false);
}

bool HaulingCheckArtifact::PassedDirectTensionCheck(HaulingSlope slope) const
{
   // since the allowable tension can change based on the amount of reinforcement
   // in the tension region, we have to check every point for every condition
   // against its associated allowable
   for (const auto& sectionResult : m_Results.vSectionResults)
   {
      for (IndexType i = 0; i < 3; i++)
      {
         ImpactDirection impact = (ImpactDirection)i;
         for (IndexType c = 0; c < 4; c++)
         {
            Corner corner = (Corner)c;
            Float64 f = sectionResult.fDirect[+slope][+impact][+corner];

#if defined REBAR_FOR_DIRECT_TENSION
            Float64 fAllow = GetAllowableTension(slope, sectionResult, impact);
            if (::IsLE(fAllow, f))
            {
               return false;
            }
#else
            for (IndexType w = 0; w < 2; w++)
            {
               WindDirection wind = (WindDirection)w;
               Float64 fAllow = GetAllowableTension(slope, sectionResult, impact, wind);
               if (::IsLE(fAllow, f))
               {
                  return false;
               }
            }
#endif
         }
      }
   }

   return true;
}

bool HaulingCheckArtifact::PassedCompressionCheck(HaulingSlope slope) const
{
   return (::IsLE(m_Criteria.AllowableCompression_PeakStress, m_Results.MinStress[+slope]) ? true : false);
}

bool HaulingCheckArtifact::PassedTensionCheck(HaulingSlope slope) const
{
   // since the allowable tension can change based on the amount of reinforcement
   // in the tension region, we have to check every point for every condition
   // against its associated allowable
   for (const auto& sectionResult : m_Results.vSectionResults)
   {
      for (IndexType i = 0; i < 3; i++)
      {
         ImpactDirection impact = (ImpactDirection)i;
         for (IndexType c = 0; c < 4; c++)
         {
            Corner corner = (Corner)c;
#if defined REBAR_FOR_DIRECT_TENSION
            Float64 fAllow = GetAllowableTension(slope, sectionResult, impact);
#endif // REBAR_FOR_DIRECT_TENSION
            for (IndexType w = 0; w < 2; w++)
            {
               WindDirection wind = (WindDirection)w;
               Float64 f = sectionResult.f[+slope][+impact][+wind][+corner];
               if (::IsLE(fAllow, f))
               {
                  return false;
               }
            }

         }
      }
   }

   return true;
}

#if defined REBAR_FOR_DIRECT_TENSION
Float64 HaulingCheckArtifact::GetAllowableTension(HaulingSlope slope, const HaulingSectionResult& sectionResult, ImpactDirection impact) const
{
   return m_Criteria.TensionStressLimit->GetTensionLimit(slope, sectionResult, impact);
}
#else
Float64 HaulingCheckArtifact::GetAllowableTension(HaulingSlope slope, const HaulingSectionResult& sectionResult, ImpactDirection impact, WindDirection wind) const
{
   return m_Criteria.TensionStressLimit->GetTensionLimit(slope, sectionResult, impact, wind);
}
#endif

bool HaulingCheckArtifact::PassedClearSpan() const
{
   return ::IsLE(m_Results.Ls, m_Criteria.MaxClearSpan);
}

bool HaulingCheckArtifact::PassedLeadingOverhang() const
{
   return ::IsLE(m_Results.Lr, m_Criteria.MaxLeadingOverhang);
}

bool HaulingCheckArtifact::PassedMaxWeight() const
{
   return ::IsLE(m_Results.Wg, m_Criteria.MaxGirderWeight);
}

Float64 HaulingCheckArtifact::RequiredFcCompression(HaulingSlope slope) const
{
   Float64 minDirectStress = m_Results.MinDirectStress[+slope];
   Float64 global_coeff = m_Criteria.CompressionCoefficient_GlobalStress;
   Float64 fcReqd_Global = -minDirectStress / global_coeff;

   Float64 minStress = m_Results.MinStress[+slope];
   Float64 peak_coeff = m_Criteria.CompressionCoefficient_PeakStress;
   Float64 fcReqd_Peak = -minStress / peak_coeff;
   return Max(fcReqd_Global, fcReqd_Peak);
}

Float64 HaulingCheckArtifact::RequiredFcTension(HaulingSlope slope) const
{
   return m_Criteria.TensionStressLimit->GetRequiredFcTension(slope,this);
}

Float64 HaulingCheckArtifact::RequiredFcTensionWithoutRebar(HaulingSlope slope) const
{
    return m_Criteria.TensionStressLimit->GetRequiredFcTensionWithoutRebar(slope, this);
}

Float64 HaulingCheckArtifact::RequiredFcTensionWithRebar(HaulingSlope slope) const
{
    return m_Criteria.TensionStressLimit->GetRequiredFcTensionWithRebar(slope, this);
}
