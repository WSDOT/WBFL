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

stbHaulingCheckArtifact::stbHaulingCheckArtifact(const stbHaulingResults& results,const stbCriteria& criteria)
{
   Init(results,criteria);
}

void stbHaulingCheckArtifact::Init(const stbHaulingResults& results,const stbCriteria& criteria)
{
   m_Results = results;
   m_Criteria = criteria;
}

const stbHaulingResults& stbHaulingCheckArtifact::GetHaulingResults() const
{
   return m_Results;
}

const stbCriteria& stbHaulingCheckArtifact::GetCriteria() const
{
   return m_Criteria;
}

bool stbHaulingCheckArtifact::Passed() const
{
   return (PassedCrackingCheck() && PassedFailureCheck() && PassedStressCheck());
}

bool stbHaulingCheckArtifact::PassedCrackingCheck() const
{
   return m_Criteria.MinFScr < m_Results.MinFScr;
}

bool stbHaulingCheckArtifact::PassedFailureCheck() const
{
   return m_Criteria.MinFSf < m_Results.MinFsFailure;
}

bool stbHaulingCheckArtifact::PassedDirectStressCheck() const
{
   return PassedDirectCompressionCheck() && PassedDirectTensionCheck();
}

bool stbHaulingCheckArtifact::PassedDirectCompressionCheck() const
{
   return (::IsLE(m_Criteria.AllowableCompression,m_Results.MinDirectStress) ? true : false);
}

bool stbHaulingCheckArtifact::PassedDirectTensionCheck() const
{
   return (::IsLE(m_Results.MaxDirectStress,m_Criteria.AllowableTension) ? true : false);
}

bool stbHaulingCheckArtifact::PassedStressCheck() const
{
   return PassedCompressionCheck() && PassedTensionCheck();
}

bool stbHaulingCheckArtifact::PassedCompressionCheck() const
{
   return (::IsLE(m_Criteria.AllowableCompression,m_Results.MinStress) ? true : false);
}

bool stbHaulingCheckArtifact::PassedTensionCheck() const
{
   return (::IsLE(m_Results.MaxStress,m_Criteria.AllowableTensionTiltedGirder) ? true : false);
}
