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
#include <Stability\LiftingCheckArtifact.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

stbLiftingCheckArtifact::stbLiftingCheckArtifact()
{
}

stbLiftingCheckArtifact::stbLiftingCheckArtifact(const stbLiftingResults& results,const stbLiftingCriteria& criteria)
{
   Init(results,criteria);
}

void stbLiftingCheckArtifact::Init(const stbLiftingResults& results,const stbLiftingCriteria& criteria)
{
   m_Results = results;
   m_Criteria = criteria;
}

const stbLiftingResults& stbLiftingCheckArtifact::GetLiftingResults() const
{
   return m_Results;
}

const stbLiftingCriteria& stbLiftingCheckArtifact::GetCriteria() const
{
   return m_Criteria;
}

void stbLiftingCheckArtifact::GetControllingTensionCase(const stbLiftingSectionResult& sectionResult,stbTypes::ImpactDirection* pImpact,stbTypes::WindDirection* pWind,stbTypes::Corner* pCorner,Float64* pfAllow,bool* pbPassed,Float64* pCD) const
{
   Float64 Fallow;
   Float64 CD = Float64_Max;
   for ( int i = 0; i < 3; i++ )
   {
      stbTypes::ImpactDirection impact = (stbTypes::ImpactDirection)i;
#if defined REBAR_FOR_DIRECT_TENSION
      Float64 fAllow = GetAllowableTension(sectionResult, impact);
#endif
      for ( int w = 0; w < 2; w++ )
      {
         stbTypes::WindDirection wind = (stbTypes::WindDirection)w;
#if !defined REBAR_FOR_DIRECT_TENSION
         Float64 fAllow = GetAllowableTension(sectionResult,impact,wind);
#endif

         Float64 cd;
         stbTypes::Corner corner;
         corner = (stbTypes::Corner)mathCDRatio::MinCDRatio(mathCDRatio::cdPositive,
            fAllow, sectionResult.f[impact][wind][stbTypes::TopLeft],
            fAllow, sectionResult.f[impact][wind][stbTypes::TopRight],
            fAllow, sectionResult.f[impact][wind][stbTypes::BottomLeft],
            fAllow, sectionResult.f[impact][wind][stbTypes::BottomRight], &cd);

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

void stbLiftingCheckArtifact::GetControllingGlobalCompressionCase(const stbLiftingSectionResult& sectionResult, stbTypes::ImpactDirection* pImpact, stbTypes::Corner* pCorner, Float64* pfAllow, bool* pbPassed, Float64* pCD) const
{
   Float64 fAllow = m_Criteria.AllowableCompression_GlobalStress;
   Float64 CD = Float64_Max;
   for (int i = 0; i < 3; i++)
   {
      stbTypes::ImpactDirection impact = (stbTypes::ImpactDirection)i;
      Float64 cd;
      stbTypes::Corner corner;
      corner = (stbTypes::Corner)mathCDRatio::MinCDRatio(mathCDRatio::cdNegative,
         fAllow, sectionResult.fDirect[impact][stbTypes::TopLeft],
         fAllow, sectionResult.fDirect[impact][stbTypes::TopRight],
         fAllow, sectionResult.fDirect[impact][stbTypes::BottomLeft],
         fAllow, sectionResult.fDirect[impact][stbTypes::BottomRight], &cd);

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

void stbLiftingCheckArtifact::GetControllingPeakCompressionCase(const stbLiftingSectionResult& sectionResult,stbTypes::ImpactDirection* pImpact,stbTypes::WindDirection* pWind,stbTypes::Corner* pCorner,Float64* pfAllow,bool* pbPassed,Float64* pCD) const
{
   Float64 fAllow = m_Criteria.AllowableCompression_PeakStress;
   Float64 CD = Float64_Max;
   for ( int i = 0; i < 3; i++ )
   {
      stbTypes::ImpactDirection impact = (stbTypes::ImpactDirection)i;
      for ( int w = 0; w < 2; w++ )
      {
         stbTypes::WindDirection wind = (stbTypes::WindDirection)w;
         Float64 cd;
         stbTypes::Corner corner;
         corner = (stbTypes::Corner)mathCDRatio::MinCDRatio(mathCDRatio::cdNegative,
            fAllow, sectionResult.f[impact][wind][stbTypes::TopLeft],
            fAllow, sectionResult.f[impact][wind][stbTypes::TopRight],
            fAllow, sectionResult.f[impact][wind][stbTypes::BottomLeft],
            fAllow, sectionResult.f[impact][wind][stbTypes::BottomRight], &cd);

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

bool stbLiftingCheckArtifact::Passed() const
{
   for (int i = 0; i < 3; i++)
   {
      stbTypes::ImpactDirection impact = (stbTypes::ImpactDirection)i;
      for (int w = 0; w < 2; w++)
      {
         stbTypes::WindDirection wind = (stbTypes::WindDirection)w;
         if (!m_Results.bIsStable[impact][wind])
         {
            return false;
         }
      }
   }


   return (PassedCrackingCheck() && PassedFailureCheck() && PassedStressCheck() && PassedDirectStressCheck());
}

bool stbLiftingCheckArtifact::PassedCrackingCheck() const
{
   return m_Criteria.MinFScr < m_Results.FScrMin;
}

bool stbLiftingCheckArtifact::PassedFailureCheck() const
{
   return m_Criteria.MinFSf < m_Results.MinAdjFsFailure;
}

bool stbLiftingCheckArtifact::PassedDirectStressCheck() const
{
   return PassedDirectCompressionCheck() && PassedDirectTensionCheck();
}

bool stbLiftingCheckArtifact::PassedDirectCompressionCheck() const
{
   return (::IsLE(m_Criteria.AllowableCompression_GlobalStress,m_Results.MinDirectStress) ? true : false);
}

bool stbLiftingCheckArtifact::PassedDirectTensionCheck() const
{
   // since the allowable tension can change based on the amount of reinforcement
   // in the tension region, we have to check every point for every condition
   // against its associted allowable
   for (const auto& sectionResult : m_Results.vSectionResults)
   {
      for (IndexType i = 0; i < 3; i++)
      {
         stbTypes::ImpactDirection impact = (stbTypes::ImpactDirection)i;
         for (IndexType c = 0; c < 4; c++)
         {
            stbTypes::Corner corner = (stbTypes::Corner)c;
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
               stbTypes::WindDirection wind = (stbTypes::WindDirection)w;
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

bool stbLiftingCheckArtifact::PassedStressCheck() const
{
   return PassedCompressionCheck() && PassedTensionCheck();
}

bool stbLiftingCheckArtifact::PassedCompressionCheck() const
{
   return (::IsLE(m_Criteria.AllowableCompression_PeakStress,m_Results.MinStress) ? true : false);
}

bool stbLiftingCheckArtifact::PassedTensionCheck() const
{
   // since the allowable tension can change based on the amount of reinforcement
   // in the tension region, we have to check every point for every condition
   // against its associted allowable
   for (const auto& sectionResult : m_Results.vSectionResults)
   {
      for (IndexType i = 0; i < 3; i++)
      {
         stbTypes::ImpactDirection impact = (stbTypes::ImpactDirection)i;
         for (IndexType c = 0; c < 4; c++)
         {
            stbTypes::Corner corner = (stbTypes::Corner)c;
#if defined REBAR_FOR_DIRECT_TENSION
            Float64 fAllow = GetAllowableTension(sectionResult, impact);
#endif // REBAR_FOR_DIRECT_TENSION
            for (IndexType w = 0; w < 2; w++)
            {
               stbTypes::WindDirection wind = (stbTypes::WindDirection)w;
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
Float64 stbLiftingCheckArtifact::GetAllowableTension(const stbLiftingSectionResult& sectionResult, stbTypes::ImpactDirection impact) const
{
   if (sectionResult.altTensionRequirements[impact].bIsAdequateRebar && 0 <= sectionResult.altTensionRequirements[impact].AsRequired)
   {
      return m_Criteria.AllowableTensionWithRebar;
   }
   else
   {
      return m_Criteria.AllowableTension;
   }
}
#else
Float64 stbLiftingCheckArtifact::GetAllowableTension(const stbLiftingSectionResult& sectionResult, stbTypes::ImpactDirection impact, stbTypes::WindDirection wind) const
{
   if (sectionResult.altTensionRequirements[impact][wind].bIsAdequateRebar && 0 <= sectionResult.altTensionRequirements[impact][wind].AsRequired)
   {
      return m_Criteria.AllowableTensionWithRebar;
   }
   else
   {
      return m_Criteria.AllowableTension;
   }
}
#endif

Float64 stbLiftingCheckArtifact::RequiredFcCompression() const
{
   Float64 minDirectStress = m_Results.MinDirectStress;
   Float64 global_coeff = m_Criteria.CompressionCoefficient_GlobalStress;
   Float64 fcReqd_Global = -minDirectStress / global_coeff;

   Float64 minStress = m_Results.MinStress;
   Float64 peak_coeff = m_Criteria.CompressionCoefficient_PeakStress;
   Float64 fcReqd_Peak = -minStress/peak_coeff;
   return Max(fcReqd_Global, fcReqd_Peak);
}

Float64 stbLiftingCheckArtifact::RequiredFcTension() const
{
   Float64 maxStress = m_Results.MaxStress;
   Float64 coeff = m_Criteria.TensionCoefficient;
   Float64 lambda = m_Criteria.Lambda;

   Float64 fcReqd = 0;
   if ( 0 < maxStress )
   {
      fcReqd = pow(maxStress/(coeff*lambda),2);
   }

   if ( m_Criteria.bMaxTension && m_Criteria.MaxTension < maxStress )
   {
      fcReqd = -99999; // doesn't matter what f'c is, tension will never be satisfied
   }

   return fcReqd;
}

Float64 stbLiftingCheckArtifact::RequiredFcTensionWithRebar() const
{
   Float64 maxStress = m_Results.MaxStress;
   Float64 coeff = m_Criteria.TensionCoefficientWithRebar;
   Float64 lambda = m_Criteria.Lambda;

   Float64 fcReqd = 0;
   if ( 0 < maxStress )
   {
      fcReqd = pow(maxStress/(coeff*lambda),2);
   }
   return fcReqd;
}
