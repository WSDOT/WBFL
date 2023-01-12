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
#include <Stability/OneEndSeatedCheckArtifact.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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

void OneEndSeatedCheckArtifact::GetControllingTensionCase(const OneEndSeatedSectionResult& sectionResult,ImpactDirection* pImpact,WindDirection* pWind,Corner* pCorner,Float64* pfAllow,bool* pbPassed,Float64* pCD) const
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
         corner = (Corner)mathCDRatio::MinCDRatio(mathCDRatio::cdPositive,
            fAllow, sectionResult.f[impact][wind][TopLeft],
            fAllow, sectionResult.f[impact][wind][TopRight],
            fAllow, sectionResult.f[impact][wind][BottomLeft],
            fAllow, sectionResult.f[impact][wind][BottomRight], &cd);

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
   *pbPassed = (::IsLE(sectionResult.f[*pImpact][*pWind][*pCorner], *pfAllow));

   *pCD = CD;
}

void OneEndSeatedCheckArtifact::GetControllingGlobalCompressionCase(const OneEndSeatedSectionResult& sectionResult, ImpactDirection* pImpact, Corner* pCorner, Float64* pfAllow, bool* pbPassed, Float64* pCD) const
{
   Float64 fAllow = m_Criteria.AllowableCompression_GlobalStress;
   Float64 CD = Float64_Max;
   for (int i = 0; i < 3; i++)
   {
      ImpactDirection impact = (ImpactDirection)i;
      Float64 cd;
      Corner corner;
      corner = (Corner)mathCDRatio::MinCDRatio(mathCDRatio::cdNegative,
         fAllow, sectionResult.fDirect[impact][TopLeft],
         fAllow, sectionResult.fDirect[impact][TopRight],
         fAllow, sectionResult.fDirect[impact][BottomLeft],
         fAllow, sectionResult.fDirect[impact][BottomRight], &cd);

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
   *pbPassed = (::IsLT(*pfAllow, sectionResult.fDirect[*pImpact][*pCorner]));

   *pCD = CD;
}

void OneEndSeatedCheckArtifact::GetControllingPeakCompressionCase(const OneEndSeatedSectionResult& sectionResult,ImpactDirection* pImpact,WindDirection* pWind,Corner* pCorner,Float64* pfAllow,bool* pbPassed,Float64* pCD) const
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
         corner = (Corner)mathCDRatio::MinCDRatio(mathCDRatio::cdNegative,
            fAllow, sectionResult.f[impact][wind][TopLeft],
            fAllow, sectionResult.f[impact][wind][TopRight],
            fAllow, sectionResult.f[impact][wind][BottomLeft],
            fAllow, sectionResult.f[impact][wind][BottomRight], &cd);

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
   *pbPassed = (::IsLT(*pfAllow, sectionResult.f[*pImpact][*pWind][*pCorner]));

   *pCD = CD;
}

bool OneEndSeatedCheckArtifact::Passed() const
{
   for (int i = 0; i < 3; i++)
   {
      ImpactDirection impact = (ImpactDirection)i;
      for (int w = 0; w < 2; w++)
      {
         WindDirection wind = (WindDirection)w;
         if (!m_Results.bRotationalStability[impact][wind] || !m_Results.bRolloverStability[impact][wind])
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
   // against its associted allowable
   for (const auto& sectionResult : m_Results.vSectionResults)
   {
      for (IndexType i = 0; i < 3; i++)
      {
         ImpactDirection impact = (ImpactDirection)i;
         for (IndexType c = 0; c < 4; c++)
         {
            Corner corner = (Corner)c;
            Float64 f = sectionResult.fDirect[impact][corner];
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
   // against its associted allowable
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
               Float64 f = sectionResult.f[impact][wind][corner];
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
