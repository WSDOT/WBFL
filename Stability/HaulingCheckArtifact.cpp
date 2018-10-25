///////////////////////////////////////////////////////////////////////
// Stability
// Copyright © 1999-2018  Washington State Department of Transportation
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

stbHaulingCheckArtifact::stbHaulingCheckArtifact(const stbHaulingResults& results,const stbHaulingCriteria& criteria, bool bComputeCrownSlopeStressesAtEquilibriumAngle, bool bComputeSuperelevationStressesAtEquilibriumAngle)
{
   Init(results,criteria, bComputeCrownSlopeStressesAtEquilibriumAngle, bComputeSuperelevationStressesAtEquilibriumAngle);
}

void stbHaulingCheckArtifact::Init(const stbHaulingResults& results,const stbHaulingCriteria& criteria, bool bComputeCrownSlopeStressesAtEquilibriumAngle, bool bComputeSuperelevationStressesAtEquilibriumAngle)
{
   m_Results = results;
   m_Criteria = criteria;
   m_bComputeStressesAtEquilibriumAngle[stbTypes::CrownSlope] = bComputeCrownSlopeStressesAtEquilibriumAngle;
   m_bComputeStressesAtEquilibriumAngle[stbTypes::Superelevation] = bComputeSuperelevationStressesAtEquilibriumAngle;
}

bool stbHaulingCheckArtifact::EvaluateStressesAtEquilibriumAngle(stbTypes::HaulingSlope slope) const
{
   return m_bComputeStressesAtEquilibriumAngle[slope];
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
         if (m_bComputeStressesAtEquilibriumAngle[slope])
         {
            corner = (stbTypes::Corner)mathCDRatio::MinCDRatio(mathCDRatio::cdPositive,
               fAllow, sectionResult.f[slope][impact][wind][stbTypes::TopLeft],
               fAllow, sectionResult.f[slope][impact][wind][stbTypes::TopRight],
               fAllow, sectionResult.f[slope][impact][wind][stbTypes::BottomLeft],
               fAllow, sectionResult.f[slope][impact][wind][stbTypes::BottomRight], &cd);
         }
         else
         {
            corner = (stbTypes::Corner)mathCDRatio::MinCDRatio(mathCDRatio::cdPositive,
               fAllow, sectionResult.fDirect[slope][impact][wind][stbTypes::TopLeft],
               fAllow, sectionResult.fDirect[slope][impact][wind][stbTypes::TopRight],
               fAllow, sectionResult.fDirect[slope][impact][wind][stbTypes::BottomLeft],
               fAllow, sectionResult.fDirect[slope][impact][wind][stbTypes::BottomRight], &cd);
         }

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
   if (m_bComputeStressesAtEquilibriumAngle[slope])
   {
      *pbPassed = (::IsLE(sectionResult.f[slope][*pImpact][*pWind][*pCorner], *pfAllow));
   }
   else
   {
      *pbPassed = (::IsLE(sectionResult.fDirect[slope][*pImpact][*pWind][*pCorner], *pfAllow));
   }

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
         if (m_bComputeStressesAtEquilibriumAngle[slope])
         {
            corner = (stbTypes::Corner)mathCDRatio::MinCDRatio(mathCDRatio::cdNegative,
               fAllow, sectionResult.f[slope][impact][wind][stbTypes::TopLeft],
               fAllow, sectionResult.f[slope][impact][wind][stbTypes::TopRight],
               fAllow, sectionResult.f[slope][impact][wind][stbTypes::BottomLeft],
               fAllow, sectionResult.f[slope][impact][wind][stbTypes::BottomRight], &cd);
         }
         else
         {
            corner = (stbTypes::Corner)mathCDRatio::MinCDRatio(mathCDRatio::cdNegative,
               fAllow, sectionResult.fDirect[slope][impact][wind][stbTypes::TopLeft],
               fAllow, sectionResult.fDirect[slope][impact][wind][stbTypes::TopRight],
               fAllow, sectionResult.fDirect[slope][impact][wind][stbTypes::BottomLeft],
               fAllow, sectionResult.fDirect[slope][impact][wind][stbTypes::BottomRight], &cd);
         }

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
   if (m_bComputeStressesAtEquilibriumAngle[slope])
   {
      *pbPassed = (::IsLT(*pfAllow, sectionResult.f[slope][*pImpact][*pWind][*pCorner]));
   }
   else
   {
      *pbPassed = (::IsLT(*pfAllow, sectionResult.fDirect[slope][*pImpact][*pWind][*pCorner]));
   }

   *pCD = CD;
}

bool stbHaulingCheckArtifact::Passed(bool bIgnoreConfigurationLimits) const
{
   bool bPassed = ( Passed(stbTypes::CrownSlope) && Passed(stbTypes::Superelevation) ? true : false);
   if (!bIgnoreConfigurationLimits)
   {
      bPassed = bPassed && PassedClearSpan() && PassedLeadingOverhang() && PassedMaxWeight();
   }
   return bPassed;
}

bool stbHaulingCheckArtifact::Passed(stbTypes::HaulingSlope slope) const
{
   for (int i = 0; i < 3; i++)
   {
      stbTypes::ImpactDirection impact = (stbTypes::ImpactDirection)i;
      for (int w = 0; w < 2; w++)
      {
         stbTypes::WindDirection wind = (stbTypes::WindDirection)w;
         if (!m_Results.bRotationalStability[slope][impact][wind] || !m_Results.bRolloverStability[slope][impact][wind])
         {
            return false;
         }
      }
   }
   return (PassedCrackingCheck(slope) && PassedRolloverCheck(slope) && PassedStressCheck(slope));
}

bool stbHaulingCheckArtifact::PassedCrackingCheck(stbTypes::HaulingSlope slope) const
{
   return m_Criteria.MinFScr < m_Results.MinFScr[slope];
}

bool stbHaulingCheckArtifact::PassedRolloverCheck(stbTypes::HaulingSlope slope) const
{
   return m_Criteria.MinFSf < m_Results.MinFsRollover[slope];
}

bool stbHaulingCheckArtifact::PassedStressCheck(stbTypes::HaulingSlope slope) const
{
   if (m_bComputeStressesAtEquilibriumAngle[slope])
   {
      return PassedCompressionCheck(slope) && PassedTensionCheck(slope);
   }
   else
   {
      return PassedDirectCompressionCheck(slope) && PassedDirectTensionCheck(slope);
   }
}

bool stbHaulingCheckArtifact::PassedDirectStressCheck(stbTypes::HaulingSlope slope) const
{
   return PassedDirectCompressionCheck(slope) && PassedDirectTensionCheck(slope);
}

bool stbHaulingCheckArtifact::PassedDirectCompressionCheck(stbTypes::HaulingSlope slope) const
{
   return (::IsLE(m_Criteria.AllowableCompression, m_Results.MinDirectStress[slope]) ? true : false);
}

bool stbHaulingCheckArtifact::PassedDirectTensionCheck(stbTypes::HaulingSlope slope) const
{
   // since the allowable tension can change based on the amount of reinforcement
   // in the tension region, we have to check every point for every condition
   // against its associted allowable
   for (const auto& sectionResult : m_Results.vSectionResults)
   {
      for (IndexType i = 0; i < 3; i++)
      {
         stbTypes::ImpactDirection impact = (stbTypes::ImpactDirection)i;
         for (IndexType w = 0; w < 2; w++)
         {
            stbTypes::WindDirection wind = (stbTypes::WindDirection)w;
            for (IndexType c = 0; c < 4; c++)
            {
               stbTypes::Corner corner = (stbTypes::Corner)c;
               Float64 fAllow = GetAllowableTension(slope, sectionResult, impact, wind);
               Float64 f = sectionResult.fDirect[slope][impact][wind][corner];
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

bool stbHaulingCheckArtifact::PassedCompressionCheck(stbTypes::HaulingSlope slope) const
{
   return (::IsLE(m_Criteria.AllowableCompression,m_Results.MinStress[slope]) ? true : false);
}

bool stbHaulingCheckArtifact::PassedTensionCheck(stbTypes::HaulingSlope slope) const
{
   // since the allowable tension can change based on the amount of reinforcement
   // in the tension region, we have to check every point for every condition
   // against its associted allowable
   for (const auto& sectionResult : m_Results.vSectionResults)
   {
      for (IndexType i = 0; i < 3; i++)
      {
         stbTypes::ImpactDirection impact = (stbTypes::ImpactDirection)i;
         for (IndexType w = 0; w < 2; w++)
         {
            stbTypes::WindDirection wind = (stbTypes::WindDirection)w;
            for (IndexType c = 0; c < 4; c++)
            {
               stbTypes::Corner corner = (stbTypes::Corner)c;
               Float64 fAllow = GetAllowableTension(slope, sectionResult, impact, wind);
               Float64 f = sectionResult.f[slope][impact][wind][corner];
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

Float64 stbHaulingCheckArtifact::GetAllowableTension(stbTypes::HaulingSlope slope,const stbHaulingSectionResult& sectionResult,stbTypes::ImpactDirection impact,stbTypes::WindDirection wind) const
{
   if ( sectionResult.altTensionRequirements[slope][impact][wind].bIsAdequateRebar && 0 <= sectionResult.altTensionRequirements[slope][impact][wind].AsRequired )
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
   Float64 minStress = (m_bComputeStressesAtEquilibriumAngle[slope] ? m_Results.MinStress[slope] : m_Results.MinDirectStress[slope]);
   Float64 coeff = m_Criteria.CompressionCoefficient;
   Float64 fcReqd = -minStress/coeff;
   return fcReqd;
}

Float64 stbHaulingCheckArtifact::RequiredFcTension(stbTypes::HaulingSlope slope) const
{
   Float64 maxStress = (m_bComputeStressesAtEquilibriumAngle[slope] ? m_Results.MaxStress[slope] : m_Results.MaxDirectStress[slope]);
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
   Float64 maxStress = (m_bComputeStressesAtEquilibriumAngle[slope] ? m_Results.MaxStress[slope] : m_Results.MaxDirectStress[slope]);
   Float64 coeff = m_Criteria.TensionCoefficientWithRebar[slope];
   Float64 lambda = m_Criteria.Lambda;

   Float64 fcReqd = 0;
   if ( 0 < maxStress )
   {
      fcReqd = pow(maxStress/(coeff*lambda),2);
   }
   return fcReqd;
}
