///////////////////////////////////////////////////////////////////////
// Stability
// Copyright © 1999-2024  Washington State Department of Transportation
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
#include <Stability/OneEndSeatedCheckArtifact.h>

using namespace WBFL::Stability;

OneEndSeatedCheckArtifact::OneEndSeatedCheckArtifact()
{
}

OneEndSeatedCheckArtifact::OneEndSeatedCheckArtifact(const OneEndSeatedResults& results,const OneEndSeatedCriteria& criteria)
{
   Init(results,criteria);
}

void OneEndSeatedCheckArtifact::Init(const OneEndSeatedResults& results,const OneEndSeatedCriteria& criteria)
{
   m_Results = results;
   m_Criteria = criteria;
}

const OneEndSeatedResults& OneEndSeatedCheckArtifact::GetOneEndSeatedResults() const
{
   return m_Results;
}

const OneEndSeatedCriteria& OneEndSeatedCheckArtifact::GetCriteria() const
{
   return m_Criteria;
}

OneEndSeatedCheckArtifact::ControllingTensionCase OneEndSeatedCheckArtifact::GetControllingTensionCase(const OneEndSeatedSectionResult& sectionResult) const
{
   ControllingTensionCase controlling_case;
   Float64 Fallow;
   Float64 CD = Float64_Max;
   for ( int i = 0; i < 3; i++ )
   {
      ImpactDirection impact = (ImpactDirection)i;
#if defined REBAR_FOR_DIRECT_TENSION
      Float64 fAllow = GetAllowableTension(sectionResult, impact);
#endif
      for ( int w = 0; w < 2; w++ )
      {
         WindDirection wind = (WindDirection)w;
#if !defined REBAR_FOR_DIRECT_TENSION
         Float64 fAllow = GetAllowableTension(sectionResult,impact,wind);
#endif

         auto [cd, corner] = WBFL::Math::CDRatio::MinCDRatio(WBFL::Math::CDRatio::Sense::Positive,
            fAllow, sectionResult.f[+impact][+wind][+Corner::TopLeft],
            fAllow, sectionResult.f[+impact][+wind][+Corner::TopRight],
            fAllow, sectionResult.f[+impact][+wind][+Corner::BottomLeft],
            fAllow, sectionResult.f[+impact][+wind][+Corner::BottomRight]);

         if ( (i == 0 && w == 0) || // this is the first time so this cd wins
              (CD < 0 && 0 <= cd) || // there is a sign change and the current cd is a positive value
              (0 <= cd && (0 <= CD ? cd < CD : fabs(CD) < fabs(cd)))
            )
         {
            CD = cd;
            controlling_case.impact = impact;
            controlling_case.wind   = wind;
            controlling_case.corner = (Corner)corner;
            Fallow = fAllow;
         }
      }
   }

   controlling_case.stress_limit = Fallow;
   controlling_case.bPassed = (::IsLE(sectionResult.f[+(controlling_case.impact)][+(controlling_case.wind)][+(controlling_case.corner)], controlling_case.stress_limit));
   controlling_case.CD = CD;
   return controlling_case;
}

OneEndSeatedCheckArtifact::ControllingGlobalCompressionCase OneEndSeatedCheckArtifact::GetControllingGlobalCompressionCase(const OneEndSeatedSectionResult& sectionResult) const
{
   ControllingGlobalCompressionCase controlling_case;
   Float64 fAllow = m_Criteria.AllowableCompression_GlobalStress;
   Float64 CD = Float64_Max;
   for (int i = 0; i < 3; i++)
   {
      ImpactDirection impact = (ImpactDirection)i;
      auto [cd,corner] = WBFL::Math::CDRatio::MinCDRatio(WBFL::Math::CDRatio::Sense::Negative,
         fAllow, sectionResult.fDirect[+impact][+Corner::TopLeft],
         fAllow, sectionResult.fDirect[+impact][+Corner::TopRight],
         fAllow, sectionResult.fDirect[+impact][+Corner::BottomLeft],
         fAllow, sectionResult.fDirect[+impact][+Corner::BottomRight]);

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
   controlling_case.bPassed = (::IsLT(controlling_case.stress_limit, sectionResult.fDirect[+(controlling_case.impact)][+(controlling_case.corner)]));
   controlling_case.CD = CD;
   return controlling_case;
}

OneEndSeatedCheckArtifact::ControllingPeakCompressionCase OneEndSeatedCheckArtifact::GetControllingPeakCompressionCase(const OneEndSeatedSectionResult& sectionResult) const
{
   ControllingPeakCompressionCase controlling_case;
   Float64 fAllow = m_Criteria.AllowableCompression_PeakStress;
   Float64 CD = Float64_Max;
   for ( int i = 0; i < 3; i++ )
   {
      ImpactDirection impact = (ImpactDirection)i;
      for ( int w = 0; w < 2; w++ )
      {
         WindDirection wind = (WindDirection)w;
         auto [cd, corner] = WBFL::Math::CDRatio::MinCDRatio(WBFL::Math::CDRatio::Sense::Negative,
            fAllow, sectionResult.f[+impact][+wind][+Corner::TopLeft],
            fAllow, sectionResult.f[+impact][+wind][+Corner::TopRight],
            fAllow, sectionResult.f[+impact][+wind][+Corner::BottomLeft],
            fAllow, sectionResult.f[+impact][+wind][+Corner::BottomRight]);

         if ( (i == 0 && w == 0) || // this is the first time so this cd wins
              (CD < 0 && 0 <= cd) || // there is a sign change and the current cd is a positive value
              (0 <= cd && 0 <= CD ? cd < CD : fabs(CD) < fabs(cd))
            )
         {
            CD = cd;
            controlling_case.impact = impact;
            controlling_case.wind   = wind;
            controlling_case.corner = (Corner)corner;
         }
      }
   }

   controlling_case.stress_limit = fAllow;
   controlling_case.bPassed = (::IsLT(controlling_case.stress_limit, sectionResult.f[+(controlling_case.impact)][+(controlling_case.wind)][+(controlling_case.corner)]));
   controlling_case.CD = CD;

   return controlling_case;
}

bool OneEndSeatedCheckArtifact::Passed() const
{
   for (int i = 0; i < 3; i++)
   {
      ImpactDirection impact = (ImpactDirection)i;
      for (int w = 0; w < 2; w++)
      {
         WindDirection wind = (WindDirection)w;
         if (!m_Results.bRotationalStability[+impact][+wind] || !m_Results.bRolloverStability[+impact][+wind])
         {
            return false;
         }
      }
   }


   return (PassedCrackingCheck() && PassedFailureCheck() && PassedStressCheck() && PassedDirectStressCheck());
}

bool OneEndSeatedCheckArtifact::PassedCrackingCheck() const
{
   return m_Criteria.MinFScr < m_Results.MinFScr;
}

bool OneEndSeatedCheckArtifact::PassedFailureCheck() const
{
   return m_Criteria.MinFSf < m_Results.MinAdjFsFailure;
}

bool OneEndSeatedCheckArtifact::PassedRolloverCheck() const
{
   return m_Criteria.MinFSf < m_Results.MinFsRollover;
}

bool OneEndSeatedCheckArtifact::PassedDirectStressCheck() const
{
   return PassedDirectCompressionCheck() && PassedDirectTensionCheck();
}

bool OneEndSeatedCheckArtifact::PassedDirectCompressionCheck() const
{
   return (::IsLE(m_Criteria.AllowableCompression_GlobalStress,m_Results.MinDirectStress) ? true : false);
}

bool OneEndSeatedCheckArtifact::PassedDirectTensionCheck() const
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
            Float64 f = sectionResult.fDirect[+impact][+corner];
#if defined REBAR_FOR_DIRECT_TENSION
            Float64 fAllow = GetAllowableTension(sectionResult, impact);
            if (::IsLE(fAllow, f))
            {
               return false;
            }
#else
            for (IndexType w = 0; w < 2; w++)
            {
               WindDirection wind = (WindDirection)w;
               Float64 fAllow = GetAllowableTension(sectionResult, impact, wind);
               if (::IsLE(fAllow, f))
               {
                  return false;
               }
            }
#endif // REBAR_FOR_DIRECT_TENSION
         }
      }
   }

   return true;
}

bool OneEndSeatedCheckArtifact::PassedStressCheck() const
{
   return PassedCompressionCheck() && PassedTensionCheck();
}

bool OneEndSeatedCheckArtifact::PassedCompressionCheck() const
{
   return (::IsLE(m_Criteria.AllowableCompression_PeakStress,m_Results.MinStress) ? true : false);
}

bool OneEndSeatedCheckArtifact::PassedTensionCheck() const
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
            Float64 fAllow = GetAllowableTension(sectionResult, impact);
#endif // REBAR_FOR_DIRECT_TENSION
            for (IndexType w = 0; w < 2; w++)
            {
               WindDirection wind = (WindDirection)w;
               Float64 f = sectionResult.f[+impact][+wind][+corner];
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
Float64 OneEndSeatedCheckArtifact::GetAllowableTension(const OneEndSeatedSectionResult& sectionResult, ImpactDirection impact) const
{
   return m_Criteria.TensionStressLimit->GetTensionLimit(sectionResult,impact);
}
#else
Float64 OneEndSeatedCheckArtifact::GetAllowableTension(const OneEndSeatedSectionResult& sectionResult, ImpactDirection impact, WindDirection wind) const
{
   return m_Criteria.TensionStressLimit->GetTensionLimit(sectionResult, impact, wind);
}
#endif

Float64 OneEndSeatedCheckArtifact::RequiredFcCompression() const
{
   Float64 minDirectStress = m_Results.MinDirectStress;
   Float64 global_coeff = m_Criteria.CompressionCoefficient_GlobalStress;
   Float64 fcReqd_Global = -minDirectStress / global_coeff;

   Float64 minStress = m_Results.MinStress;
   Float64 peak_coeff = m_Criteria.CompressionCoefficient_PeakStress;
   Float64 fcReqd_Peak = -minStress/peak_coeff;
   return Max(fcReqd_Global, fcReqd_Peak);
}

Float64 OneEndSeatedCheckArtifact::RequiredFcTension() const
{
   return m_Criteria.TensionStressLimit->GetRequiredFcTension(this);
}

Float64 OneEndSeatedCheckArtifact::RequiredFcTensionWithoutRebar() const
{
    return m_Criteria.TensionStressLimit->GetRequiredFcTensionWithoutRebar(this);
}

Float64 OneEndSeatedCheckArtifact::RequiredFcTensionWithRebar() const
{
    return m_Criteria.TensionStressLimit->GetRequiredFcTensionWithRebar(this);
}
