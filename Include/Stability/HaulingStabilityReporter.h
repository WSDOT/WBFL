///////////////////////////////////////////////////////////////////////
// Stability
// Copyright © 1999-2019  Washington State Department of Transportation
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

#pragma once

#include <Stability\StabilityExp.h>
#include <Stability\StabilityProblem.h>
#include <Stability\HaulingResults.h>
#include <Stability\HaulingCheckArtifact.h>

/*****************************************************************************
CLASS 
   stbHaulingStabilityReporter

DESCRIPTION
   Generates reports for Hauling stability analysis
*****************************************************************************/

class STABILITYCLASS stbHaulingStabilityReporter
{
public:
   stbHaulingStabilityReporter();

   void BuildSpecCheckChapter(const stbIGirder* pGirder,const stbIHaulingStabilityProblem* pStabilityProblem,const stbHaulingCheckArtifact* pArtifact,rptChapter* pChapter,LPCTSTR lpszLocColumnLabel = nullptr,Float64 offset = 0);
   void BuildDetailsChapter(const stbIGirder* pGirder,const stbIHaulingStabilityProblem* pStabilityProblem,const stbHaulingResults* pResults,rptChapter* pChapter,LPCTSTR lpszLocColumnLabel = nullptr,Float64 offset = 0);
};
