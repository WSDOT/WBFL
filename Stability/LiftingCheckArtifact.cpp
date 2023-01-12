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

#include <Stability/StabilityLib.h>
#include <Stability/LiftingCheckArtifact.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace WBFL::Stability;

LiftingCheckArtifact::LiftingCheckArtifact()
{
}

LiftingCheckArtifact::LiftingCheckArtifact(const LiftingResults& results,const LiftingCriteria& criteria)
{
   Init(results,criteria);
}

void LiftingCheckArtifact::Init(const LiftingResults& results,const LiftingCriteria& criteria)
{
   m_Results = results;
   m_Criteria = criteria;
}

const LiftingResults& LiftingCheckArtifact::GetLiftingResults() const
{
   return m_Results;
}

const LiftingCriteria& LiftingCheckArtifact::GetCriteria() const
{
   return m_Criteria;
}

void LiftingCheckArtifact::GetControllingTensionCase(const LiftingSectionResult& sectionResult,ImpactDirection* pImpact,WindDirection* pWind,Corner* pCorner,Float64* pfAllow,bool* pbPassed,Float64* pCD) const
{
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

         Float64 cd;
         Corner corner;
         corner = (Corner)WBFL::Math::CDRatio::MinCDRatio(WBFL::Math::CDRatio::Sense::Positive,
            fAllow, sectionResult.f[+impact][+wind][+Corner::TopLeft],
            fAllow, sectionResult.f[+impact][+wind][+Corner::TopRight],
            fAllow, sectionResult.f[+impact][+wind][+Corner::BottomLeft],
            fAllow, sectionResult.f[+impact][+wind][+Corner::BottomRight], &cd);

         if ( (i == 0 && w == 0) || // this is the first time so this cd wins
              (CD < 0 && 0 <= cd) || // there is a sign change and the current cd is a positive value
              (0 <= cd && (0 <= CD ? cd < CD : fabs(CD) < fabs(cd)))
            )
         {
            CD = cd;
            *pImpact = impact;
            *pWind   = wind;
            *pCorner = corner;
            Fallow = fAllow;
         }
      }
   }

   *pfAllow = Fallow;
   *pbPassed = (::IsLE(sectionResult.f[+(*pImpact)][+(*pWind)][+(*pCorner)], *pfAllow));

   *pCD = CD;
}

void LiftingCheckArtifact::GetControllingGlobalCompressionCase(const LiftingSectionResult& sectionResult, ImpactDirection* pImpact, Corner* pCorner, Float64* pfAllow, bool* pbPassed, Float64* pCD) const
{
   Float64 fAllow = m_Criteria.AllowableCompression_GlobalStress;
   Float64 CD = Float64_Max;
   for (int i = 0; i < 3; i++)
   {
      ImpactDirection impact = (ImpactDirection)i;
      Float64 cd;
      Corner corner;
      corner = (Corner)WBFL::Math::CDRatio::MinCDRatio(WBFL::Math::CDRatio::Sense::Negative,
         fAllow, sectionResult.fDirect[+impact][+Corner::TopLeft],
         fAllow, sectionResult.fDirect[+impact][+Corner::TopRight],
         fAllow, sectionResult.fDirect[+impact][+Corner::BottomLeft],
         fAllow, sectionResult.fDirect[+impact][+Corner::BottomRight], &cd);

      if ((i == 0) || // this is the first time so this cd wins
         (CD < 0 && 0 <= cd) || // there is a sign change and the current cd is a positive value
         (0 <= cd && 0 <= CD ? cd < CD : fabs(CD) < fabs(cd))
         )
      {
         CD = cd;
         *pImpact = impact;
         *pCorner = corner;
      }
   }

   *pfAllow = fAllow;
   *pbPassed = (::IsLT(*pfAllow, sectionResult.fDirect[+(*pImpact)][+(*pCorner)]));

   *pCD = CD;
}

void LiftingCheckArtifact::GetControllingPeakCompressionCase(const LiftingSectionResult& sectionResult,ImpactDirection* pImpact,WindDirection* pWind,Corner* pCorner,Float64* pfAllow,bool* pbPassed,Float64* pCD) const
{
   Float64 fAllow = m_Criteria.AllowableCompression_PeakStress;
   Float64 CD = Float64_Max;
   for ( int i = 0; i < 3; i++ )
   {
      ImpactDirection impact = (ImpactDirection)i;
      for ( int w = 0; w < 2; w++ )
      {
         WindDirection wind = (WindDirection)w;
         Float64 cd;
         Corner corner;
         corner = (Corner)WBFL::Math::CDRatio::MinCDRatio(WBFL::Math::CDRatio::Sense::Negative,
            fAllow, sectionResult.f[+impact][+wind][+Corner::TopLeft],
            fAllow, sectionResult.f[+impact][+wind][+Corner::TopRight],
            fAllow, sectionResult.f[+impact][+wind][+Corner::BottomLeft],
            fAllow, sectionResult.f[+impact][+wind][+Corner::BottomRight], &cd);

         if ( (i == 0 && w == 0) || // this is the first time so this cd wins
              (CD < 0 && 0 <= cd) || // there is a sign change and the current cd is a positive value
              (0 <= cd && 0 <= CD ? cd < CD : fabs(CD) < fabs(cd))
            )
         {
            CD = cd;
            *pImpact = impact;
            *pWind   = wind;
            *pCorner = corner;
         }
      }
   }

   *pfAllow = fAllow;
   *pbPassed = (::IsLT(*pfAllow, sectionResult.f[+(*pImpact)][+(*pWind)][+(*pCorner)]));

   *pCD = CD;
}

bool LiftingCheckArtifact::Passed() const
{
   for (int i = 0; i < 3; i++)
   {
      ImpactDirection impact = (ImpactDirection)i;
      for (int w = 0; w < 2; w++)
      {
         WindDirection wind = (WindDirection)w;
         if (!m_Results.bIsStable[+impact][+wind])
         {
            return false;
         }
      }
   }


   return (PassedCrackingCheck() && PassedFailureCheck() && PassedStressCheck() && PassedDirectStressCheck());
}

bool LiftingCheckArtifact::PassedCrackingCheck() const
{
   return m_Criteria.MinFScr < m_Results.FScrMin;
}

bool LiftingCheckArtifact::PassedFailureCheck() const
{
   return m_Criteria.MinFSf < m_Results.MinAdjFsFailure;
}

bool LiftingCheckArtifact::PassedDirectStressCheck() const
{
   return PassedDirectCompressionCheck() && PassedDirectTensionCheck();
}

bool LiftingCheckArtifact::PassedDirectCompressionCheck() const
{
   return (::IsLE(m_Criteria.AllowableCompression_GlobalStress,m_Results.MinDirectStress) ? true : false);
}

bool LiftingCheckArtifact::PassedDirectTensionCheck() const
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

bool LiftingCheckArtifact::PassedStressCheck() const
{
   return PassedCompressionCheck() && PassedTensionCheck();
}

bool LiftingCheckArtifact::PassedCompressionCheck() const
{
   return (::IsLE(m_Criteria.AllowableCompression_PeakStress,m_Results.MinStress) ? true : false);
}

bool LiftingCheckArtifact::PassedTensionCheck() const
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
Float64 LiftingCheckArtifact::GetAllowableTension(const LiftingSectionResult& sectionResult, ImpactDirection impact) const
{
   return m_Criteria.TensionStressLimit->GetTensionLimit(sectionResult,impact);
}
#else
Float64 LiftingCheckArtifact::GetAllowableTension(const LiftingSectionResult& sectionResult, ImpactDirection impact, WindDirection wind) const
{
   return m_Criteria.TensionStressLimit->GetTensionLimit(sectionResult, impact, wind);
}
#endif

Float64 LiftingCheckArtifact::RequiredFcCompression() const
{
   Float64 minDirectStress = m_Results.MinDirectStress;
   Float64 global_coeff = m_Criteria.CompressionCoefficient_GlobalStress;
   Float64 fcReqd_Global = -minDirectStress / global_coeff;

   Float64 minStress = m_Results.MinStress;
   Float64 peak_coeff = m_Criteria.CompressionCoefficient_PeakStress;
   Float64 fcReqd_Peak = -minStress/peak_coeff;
   return Max(fcReqd_Global, fcReqd_Peak);
}

Float64 LiftingCheckArtifact::RequiredFcTension() const
{
   return m_Criteria.TensionStressLimit->GetRequiredFcTension(this);
}

Float64 LiftingCheckArtifact::RequiredFcTensionWithoutRebar() const
{
    return m_Criteria.TensionStressLimit->GetRequiredFcTensionWithoutRebar(this);
}

Float64 LiftingCheckArtifact::RequiredFcTensionWithRebar() const
{
    return m_Criteria.TensionStressLimit->GetRequiredFcTensionWithRebar(this);
}
