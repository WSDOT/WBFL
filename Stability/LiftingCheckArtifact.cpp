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
#include <Stability\LiftingCheckArtifact.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

stbLiftingCheckArtifact::stbLiftingCheckArtifact()
{
}

stbLiftingCheckArtifact::stbLiftingCheckArtifact(const stbLiftingResults& results,const stbCriteria& criteria)
{
   Init(results,criteria);
}

void stbLiftingCheckArtifact::Init(const stbLiftingResults& results,const stbCriteria& criteria)
{
   m_Results = results;
   m_Criteria = criteria;
}

const stbLiftingResults& stbLiftingCheckArtifact::GetLiftingResults() const
{
   return m_Results;
}

const stbCriteria& stbLiftingCheckArtifact::GetCriteria() const
{
   return m_Criteria;
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

bool stbLiftingCheckArtifact::PassedStressCheck() const
{
   return PassedCompressionCheck() && PassedTensionCheck();
}

bool stbLiftingCheckArtifact::PassedCompressionCheck() const
{
   return (::IsLE(m_Criteria.AllowableCompression,m_Results.MinStress) ? true : false);
}

bool stbLiftingCheckArtifact::PassedTensionCheck() const
{
   return (::IsLE(m_Results.MaxStress,m_Criteria.AllowableTension) ? true : false);
}

Float64 stbLiftingCheckArtifact::GetAllowableTension(const stbLiftingSectionResult& sectionResult,int face) const
{
   if ( sectionResult.bSectionHasRebar[face] )
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
   Float64 minStress = m_Results.MinStress;
   Float64 coeff = m_Criteria.CompressionCoefficient;
   Float64 fcReqd = -minStress/coeff;
   return fcReqd;
}

Float64 stbLiftingCheckArtifact::RequiredFcTension() const
{
   Float64 maxStress = m_Results.MaxStress;
   Float64 coeff = m_Criteria.TensionCoefficient;
#pragma Reminder("WORKING HERE - need to have or compute lambda")
   Float64 lambda = 1.0;

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
#pragma Reminder("WORKING HERE - need to have or compute lambda")
   Float64 lambda = 1.0;

   Float64 fcReqd = 0;
   if ( 0 < maxStress )
   {
      fcReqd = pow(maxStress/(coeff*lambda),2);
   }
   return fcReqd;
}
