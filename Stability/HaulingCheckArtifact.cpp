///////////////////////////////////////////////////////////////////////
// Stability
// Copyright © 1999-2016  Washington State Department of Transportation
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
#include <Stability\HaulingCheckArtifact.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

stbHaulingCheckArtifact::stbHaulingCheckArtifact()
{
}

stbHaulingCheckArtifact::stbHaulingCheckArtifact(const stbHaulingResults& results,const stbHaulingCriteria& criteria)
{
   Init(results,criteria);
}

void stbHaulingCheckArtifact::Init(const stbHaulingResults& results,const stbHaulingCriteria& criteria)
{
   m_Results = results;
   m_Criteria = criteria;
}

const stbHaulingResults& stbHaulingCheckArtifact::GetHaulingResults() const
{
   return m_Results;
}

const stbHaulingCriteria& stbHaulingCheckArtifact::GetCriteria() const
{
   return m_Criteria;
}

void stbHaulingCheckArtifact::GetControllingTensionCase(stbTypes::HaulingSlope slope,const stbHaulingSectionResult& sectionResult,stbTypes::ImpactDirection* pImpact,stbTypes::WindDirection* pWind,stbTypes::Corner* pCorner,Float64* pfAllow,bool* pbPassed,Float64* pCD) const
{
   Float64 Fallow;
   Float64 CD = DBL_MAX;
   for ( int i = 0; i < 3; i++ )
   {
      stbTypes::ImpactDirection impact = (stbTypes::ImpactDirection)i;
      for ( int w = 0; w < 2; w++ )
      {
         stbTypes::WindDirection wind = (stbTypes::WindDirection)w;

         Float64 fAllow = GetAllowableTension(slope,sectionResult,impact,wind);

         Float64 cd;
         stbTypes::Corner corner;
#if defined MATCH_OLD_ANALYSIS
         if ( slope == stbTypes::CrownSlope )
         {
            corner = (stbTypes::Corner)mathCDRatio::MinCDRatio(mathCDRatio::cdPositive,
               fAllow, sectionResult.fDirect[slope][impact][wind][stbTypes::TopLeft], 
               fAllow, sectionResult.fDirect[slope][impact][wind][stbTypes::TopRight],
               fAllow, sectionResult.fDirect[slope][impact][wind][stbTypes::BottomLeft],
               fAllow, sectionResult.fDirect[slope][impact][wind][stbTypes::BottomRight],&cd);
         }
         else
         {
            corner = (stbTypes::Corner)mathCDRatio::MinCDRatio(mathCDRatio::cdPositive,
               fAllow, sectionResult.f[slope][impact][wind][stbTypes::TopLeft], 
               fAllow, sectionResult.f[slope][impact][wind][stbTypes::TopRight],
               fAllow, sectionResult.f[slope][impact][wind][stbTypes::BottomLeft],
               fAllow, sectionResult.f[slope][impact][wind][stbTypes::BottomRight],&cd);
         }
#else
         corner = (stbTypes::Corner)mathCDRatio::MinCDRatio(mathCDRatio::cdPositive,
            fAllow, sectionResult.f[slope][impact][wind][stbTypes::TopLeft], 
            fAllow, sectionResult.f[slope][impact][wind][stbTypes::TopRight],
            fAllow, sectionResult.f[slope][impact][wind][stbTypes::BottomLeft],
            fAllow, sectionResult.f[slope][impact][wind][stbTypes::BottomRight],&cd);
#endif

         if ( (i == 0 && w == 0) || // this is the first time so this cd wins
              (CD < 0 && 0 <= cd) || // there is a sign change and the current cd is a positive value
              (0 <= cd && (0 <= CD ? cd < CD : fabs(CD) < fabs(cd)) )
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
   *pbPassed = (::IsLE(sectionResult.f[slope][*pImpact][*pWind][*pCorner],*pfAllow));
   *pCD = CD;
}

void stbHaulingCheckArtifact::GetControllingCompressionCase(stbTypes::HaulingSlope slope,const stbHaulingSectionResult& sectionResult,stbTypes::ImpactDirection* pImpact,stbTypes::WindDirection* pWind,stbTypes::Corner* pCorner,Float64* pfAllow,bool* pbPassed,Float64* pCD) const
{
   Float64 fAllow = m_Criteria.AllowableCompression;
   Float64 CD = DBL_MAX;
   for ( int i = 0; i < 3; i++ )
   {
      stbTypes::ImpactDirection impact = (stbTypes::ImpactDirection)i;
      for ( int w = 0; w < 2; w++ )
      {
         stbTypes::WindDirection wind = (stbTypes::WindDirection)w;
         Float64 cd;
         stbTypes::Corner corner;
#if defined MATCH_OLD_ANALYSIS
         if ( slope == stbTypes::CrownSlope )
         {
            corner = (stbTypes::Corner)mathCDRatio::MinCDRatio(mathCDRatio::cdNegative,
               fAllow, sectionResult.fDirect[slope][impact][wind][stbTypes::TopLeft], 
               fAllow, sectionResult.fDirect[slope][impact][wind][stbTypes::TopRight],
               fAllow, sectionResult.fDirect[slope][impact][wind][stbTypes::BottomLeft],
               fAllow, sectionResult.fDirect[slope][impact][wind][stbTypes::BottomRight],&cd);
         }
         else
         {
            corner = (stbTypes::Corner)mathCDRatio::MinCDRatio(mathCDRatio::cdNegative,
               fAllow, sectionResult.f[slope][impact][wind][stbTypes::TopLeft], 
               fAllow, sectionResult.f[slope][impact][wind][stbTypes::TopRight],
               fAllow, sectionResult.f[slope][impact][wind][stbTypes::BottomLeft],
               fAllow, sectionResult.f[slope][impact][wind][stbTypes::BottomRight],&cd);
         }
#else
         corner = (stbTypes::Corner)mathCDRatio::MinCDRatio(mathCDRatio::cdNegative,
            fAllow, sectionResult.f[slope][impact][wind][stbTypes::TopLeft], 
            fAllow, sectionResult.f[slope][impact][wind][stbTypes::TopRight],
            fAllow, sectionResult.f[slope][impact][wind][stbTypes::BottomLeft],
            fAllow, sectionResult.f[slope][impact][wind][stbTypes::BottomRight],&cd);
#endif

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
   *pbPassed = (::IsLT(*pfAllow,sectionResult.f[slope][*pImpact][*pWind][*pCorner]));
   *pCD = CD;
}

bool stbHaulingCheckArtifact::Passed() const
{
   return ( Passed(stbTypes::CrownSlope) && Passed(stbTypes::Superelevation) && PassedClearSpan() && PassedLeadingOverhang() && PassedMaxWeight() ? true : false);
}

bool stbHaulingCheckArtifact::Passed(stbTypes::HaulingSlope slope) const
{
   return (PassedCrackingCheck(slope) && PassedFailureCheck(slope) && PassedRolloverCheck(slope) && PassedStressCheck(slope));
}

bool stbHaulingCheckArtifact::PassedCrackingCheck(stbTypes::HaulingSlope slope) const
{
   return m_Criteria.MinFScr < m_Results.MinFScr[slope];
}

bool stbHaulingCheckArtifact::PassedFailureCheck(stbTypes::HaulingSlope slope) const
{
   return m_Criteria.MinFSf < m_Results.MinFsFailure[slope];
}

bool stbHaulingCheckArtifact::PassedRolloverCheck(stbTypes::HaulingSlope slope) const
{
   return m_Criteria.MinFSf < m_Results.MinFsRollover[slope];
}

bool stbHaulingCheckArtifact::PassedStressCheck(stbTypes::HaulingSlope slope) const
{
   return PassedCompressionCheck(slope) && PassedTensionCheck(slope);
}

bool stbHaulingCheckArtifact::PassedCompressionCheck(stbTypes::HaulingSlope slope) const
{
#if defined MATCH_OLD_ANALYSIS
   if ( slope == stbTypes::CrownSlope )
   {
      return (::IsLE(m_Criteria.AllowableCompression,m_Results.MinDirectStress[slope]) ? true : false);
   }
   else
   {
      return (::IsLE(m_Criteria.AllowableCompression,m_Results.MinStress[slope]) ? true : false);
   }
#else
   return (::IsLE(m_Criteria.AllowableCompression,m_Results.MinStress[slope]) ? true : false);
#endif
}

bool stbHaulingCheckArtifact::PassedTensionCheck(stbTypes::HaulingSlope slope) const
{
#if defined MATCH_OLD_ANALYSIS
   if ( slope == stbTypes::CrownSlope )
   {
      Float64 fAllow = GetAllowableTension(slope,m_Results.vSectionResults[m_Results.MaxDirectStressAnalysisPointIndex[slope]],m_Results.MaxDirectStressImpactDirection[slope],m_Results.MaxDirectStressWindDirection[slope]);
      return (::IsLE(m_Results.MaxDirectStress[slope],fAllow) ? true : false);
   }
   else
   {
      Float64 fAllow = GetAllowableTension(slope,m_Results.vSectionResults[m_Results.MaxStressAnalysisPointIndex[slope]],m_Results.MaxStressImpactDirection[slope],m_Results.MaxStressWindDirection[slope]);
      return (::IsLE(m_Results.MaxStress[slope],fAllow) ? true : false);
   }
#else
   Float64 fAllow = GetAllowableTension(slope,m_Results.vSectionResults[m_Results.MaxStressAnalysisPointIndex[slope]],m_Results.MaxStressImpactDirection[slope],m_Results.MaxStressWindDirection[slope]);
   return (::IsLE(m_Results.MaxStress[slope],fAllow) ? true : false);
#endif
}

Float64 stbHaulingCheckArtifact::GetAllowableTension(stbTypes::HaulingSlope slope,const stbHaulingSectionResult& sectionResult,stbTypes::ImpactDirection impact,stbTypes::WindDirection wind) const
{
   if ( sectionResult.bSectionHasRebar[slope][impact][wind] )
   {
      return m_Criteria.AllowableTensionWithRebar[slope];
   }
   else
   {
      return m_Criteria.AllowableTension[slope];
   }
}

bool stbHaulingCheckArtifact::PassedClearSpan() const
{
   return ::IsLE(m_Results.Ls,m_Criteria.MaxClearSpan);
}

bool stbHaulingCheckArtifact::PassedLeadingOverhang() const
{
   return ::IsLE(m_Results.Lr,m_Criteria.MaxLeadingOverhang);
}

bool stbHaulingCheckArtifact::PassedMaxWeight() const
{
   return ::IsLE(m_Results.Wg,m_Criteria.MaxGirderWeight);
}

Float64 stbHaulingCheckArtifact::RequiredFcCompression(stbTypes::HaulingSlope slope) const
{
#if defined MATCH_OLD_ANALYSIS
   Float64 minStress;
   if ( slope == stbTypes::CrownSlope )
   {
      minStress = m_Results.MinDirectStress[slope];
   }
   else
   {
      minStress = m_Results.MinStress[slope];
   }
#else
   Float64 minStress = m_Results.MinStress[slope];
#endif
   Float64 coeff = m_Criteria.CompressionCoefficient;
   Float64 fcReqd = -minStress/coeff;
   return fcReqd;
}

Float64 stbHaulingCheckArtifact::RequiredFcTension(stbTypes::HaulingSlope slope) const
{
#if defined MATCH_OLD_ANALYSIS
   Float64 maxStress;
   if ( slope == stbTypes::CrownSlope )
   {
      maxStress = m_Results.MaxDirectStress[slope];
   }
   else
   {
      maxStress = m_Results.MaxStress[slope];
   }
#else
   Float64 maxStress = m_Results.MaxStress[slope];
#endif
   Float64 coeff = m_Criteria.TensionCoefficient[slope];
   Float64 lambda = m_Criteria.Lambda;

   Float64 fcReqd = 0;
   if ( 0 < maxStress )
   {
      fcReqd = pow(maxStress/(coeff*lambda),2);
   }

   if ( m_Criteria.bMaxTension[slope] && m_Criteria.MaxTension[slope] < maxStress )
   {
      fcReqd = -99999; // doesn't matter what f'c is, tension will never be satisfied
   }

   return fcReqd;
}

Float64 stbHaulingCheckArtifact::RequiredFcTensionWithRebar(stbTypes::HaulingSlope slope) const
{
#if defined MATCH_OLD_ANALYSIS
   Float64 maxStress;
   if ( slope == stbTypes::CrownSlope )
   {
      maxStress = m_Results.MaxDirectStress[slope];
   }
   else
   {
      maxStress = m_Results.MaxStress[slope];
   }
#else
   Float64 maxStress = m_Results.MaxStress[slope];
#endif
   Float64 coeff = m_Criteria.TensionCoefficientWithRebar[slope];
   Float64 lambda = m_Criteria.Lambda;

   Float64 fcReqd = 0;
   if ( 0 < maxStress )
   {
      fcReqd = pow(maxStress/(coeff*lambda),2);
   }
   return fcReqd;
}
