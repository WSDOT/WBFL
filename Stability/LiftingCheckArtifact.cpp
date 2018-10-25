///////////////////////////////////////////////////////////////////////
// Stability
// Copyright © 1999-2017  Washington State Department of Transportation
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

stbLiftingCheckArtifact::stbLiftingCheckArtifact(const stbLiftingResults& results,const stbLiftingCriteria& criteria,bool bPlumbGirderStresses)
{
   Init(results,criteria,bPlumbGirderStresses);
}

void stbLiftingCheckArtifact::Init(const stbLiftingResults& results,const stbLiftingCriteria& criteria,bool bPlumbGirderStresses)
{
   m_Results = results;
   m_Criteria = criteria;
   m_bPlumbGirderStresses = bPlumbGirderStresses;
}

const stbLiftingResults& stbLiftingCheckArtifact::GetLiftingResults() const
{
   return m_Results;
}

const stbLiftingCriteria& stbLiftingCheckArtifact::GetCriteria() const
{
   return m_Criteria;
}

bool stbLiftingCheckArtifact::PlumbGirderStressesEvaluated() const
{
   return m_bPlumbGirderStresses;
}

void stbLiftingCheckArtifact::GetControllingTensionCase(const stbLiftingSectionResult& sectionResult,stbTypes::ImpactDirection* pImpact,stbTypes::WindDirection* pWind,stbTypes::Corner* pCorner,Float64* pfAllow,bool* pbPassed,Float64* pCD) const
{
   Float64 Fallow;
   Float64 CD = DBL_MAX;
   for ( int i = 0; i < 3; i++ )
   {
      stbTypes::ImpactDirection impact = (stbTypes::ImpactDirection)i;
      for ( int w = 0; w < 2; w++ )
      {
         stbTypes::WindDirection wind = (stbTypes::WindDirection)w;
         Float64 fAllow = GetAllowableTension(sectionResult,impact,wind);

         Float64 cd;
         stbTypes::Corner corner;
         if ( m_bPlumbGirderStresses )
         {
            corner = (stbTypes::Corner)mathCDRatio::MinCDRatio(mathCDRatio::cdPositive,
               fAllow, sectionResult.fDirect[impact][wind][stbTypes::TopLeft], 
               fAllow, sectionResult.fDirect[impact][wind][stbTypes::TopRight],
               fAllow, sectionResult.fDirect[impact][wind][stbTypes::BottomLeft],
               fAllow, sectionResult.fDirect[impact][wind][stbTypes::BottomRight],&cd);
         }
         else
         {
            corner = (stbTypes::Corner)mathCDRatio::MinCDRatio(mathCDRatio::cdPositive,
               fAllow, sectionResult.f[impact][wind][stbTypes::TopLeft], 
               fAllow, sectionResult.f[impact][wind][stbTypes::TopRight],
               fAllow, sectionResult.f[impact][wind][stbTypes::BottomLeft],
               fAllow, sectionResult.f[impact][wind][stbTypes::BottomRight],&cd);
         }

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
   if ( m_bPlumbGirderStresses )
   {
      *pbPassed = (::IsLE(sectionResult.fDirect[*pImpact][*pWind][*pCorner],*pfAllow));
   }
   else
   {
      *pbPassed = (::IsLE(sectionResult.f[*pImpact][*pWind][*pCorner],*pfAllow));
   }

   *pCD = CD;
}

void stbLiftingCheckArtifact::GetControllingCompressionCase(const stbLiftingSectionResult& sectionResult,stbTypes::ImpactDirection* pImpact,stbTypes::WindDirection* pWind,stbTypes::Corner* pCorner,Float64* pfAllow,bool* pbPassed,Float64* pCD) const
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
         if ( m_bPlumbGirderStresses )
         {
            corner = (stbTypes::Corner)mathCDRatio::MinCDRatio(mathCDRatio::cdNegative,
               fAllow, sectionResult.fDirect[impact][wind][stbTypes::TopLeft], 
               fAllow, sectionResult.fDirect[impact][wind][stbTypes::TopRight],
               fAllow, sectionResult.fDirect[impact][wind][stbTypes::BottomLeft],
               fAllow, sectionResult.fDirect[impact][wind][stbTypes::BottomRight],&cd);
         }
         else
         {
            corner = (stbTypes::Corner)mathCDRatio::MinCDRatio(mathCDRatio::cdNegative,
               fAllow, sectionResult.f[impact][wind][stbTypes::TopLeft], 
               fAllow, sectionResult.f[impact][wind][stbTypes::TopRight],
               fAllow, sectionResult.f[impact][wind][stbTypes::BottomLeft],
               fAllow, sectionResult.f[impact][wind][stbTypes::BottomRight],&cd);
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
   if ( m_bPlumbGirderStresses )
   {
      *pbPassed = (::IsLT(*pfAllow,sectionResult.fDirect[*pImpact][*pWind][*pCorner]));
   }
   else
   {
      *pbPassed = (::IsLT(*pfAllow,sectionResult.f[*pImpact][*pWind][*pCorner]));
   }

   *pCD = CD;
}

bool stbLiftingCheckArtifact::Passed() const
{
   return (PassedCrackingCheck() && PassedFailureCheck() && PassedStressCheck());
}

bool stbLiftingCheckArtifact::PassedCrackingCheck() const
{
   return m_Criteria.MinFScr < m_Results.MinFScr;
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
   return (::IsLE(m_Criteria.AllowableCompression,m_Results.MinDirectStress) ? true : false);
}

bool stbLiftingCheckArtifact::PassedDirectTensionCheck() const
{
   Float64 fAllow = GetAllowableTension(m_Results.vSectionResults[m_Results.MaxDirectStressAnalysisPointIndex],m_Results.MaxDirectStressImpactDirection,m_Results.MaxDirectStressWindDirection);
   return (::IsLE(m_Results.MaxDirectStress,fAllow) ? true : false);
}

bool stbLiftingCheckArtifact::PassedStressCheck() const
{
   if ( m_bPlumbGirderStresses )
   {
      return PassedDirectCompressionCheck() && PassedDirectTensionCheck();
   }
   else
   {
      return PassedCompressionCheck() && PassedTensionCheck();
   }
}

bool stbLiftingCheckArtifact::PassedCompressionCheck() const
{
   return (::IsLE(m_Criteria.AllowableCompression,m_Results.MinStress) ? true : false);
}

bool stbLiftingCheckArtifact::PassedTensionCheck() const
{
   Float64 fAllow = GetAllowableTension(m_Results.vSectionResults[m_Results.MaxStressAnalysisPointIndex],m_Results.MaxStressImpactDirection,m_Results.MaxStressWindDirection);
   return (::IsLE(m_Results.MaxStress,fAllow) ? true : false);
}

Float64 stbLiftingCheckArtifact::GetAllowableTension(const stbLiftingSectionResult& sectionResult,stbTypes::ImpactDirection impact,stbTypes::WindDirection wind) const
{
   if ( sectionResult.bSectionHasRebar[impact][wind] )
   {
      return m_Criteria.AllowableTensionWithRebar;
   }
   else
   {
      return m_Criteria.AllowableTension;
   }
}

Float64 stbLiftingCheckArtifact::RequiredFcCompression() const
{
   Float64 minStress = (m_bPlumbGirderStresses ? m_Results.MinDirectStress : m_Results.MinStress);
   Float64 coeff = m_Criteria.CompressionCoefficient;
   Float64 fcReqd = -minStress/coeff;
   return fcReqd;
}

Float64 stbLiftingCheckArtifact::RequiredFcTension() const
{
   Float64 maxStress = (m_bPlumbGirderStresses ? m_Results.MaxDirectStress : m_Results.MaxStress);
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
   Float64 maxStress = (m_bPlumbGirderStresses ? m_Results.MaxDirectStress : m_Results.MaxStress);
   Float64 coeff = m_Criteria.TensionCoefficientWithRebar;
   Float64 lambda = m_Criteria.Lambda;

   Float64 fcReqd = 0;
   if ( 0 < maxStress )
   {
      fcReqd = pow(maxStress/(coeff*lambda),2);
   }
   return fcReqd;
}
