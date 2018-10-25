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

#pragma once

#include <Stability\StabilityExp.h>
#include <Stability\StabilityProblem.h>
#include <Stability\Criteria.h>
#include <Stability\LiftingResults.h>
#include <Stability\HaulingResults.h>
#include <Stability\LiftingCheckArtifact.h>
#include <Stability\HaulingCheckArtifact.h>

#include <WBFLFem2d.h>

/*****************************************************************************
CLASS 
   stbStabilityEngineer

DESCRIPTION
   Performes the stability analysis


COPYRIGHT
   Copyright © 1997-2016
   Washington State Department Of Transportation
   All Rights Reserved
*****************************************************************************/

class STABILITYCLASS stbStabilityEngineer
{
public:
   stbStabilityEngineer();

   // Performs a lifting stress and stability analysis
   stbLiftingResults AnalyzeLifting(const stbIGirder* pGirder,const stbILiftingStabilityProblem* pStabilityProblem) const;

   // Performs a hauling stress and stability analysis
   stbHaulingResults AnalyzeHauling(const stbIGirder* pGirder,const stbIHaulingStabilityProblem* pStabilityProblem) const;

   // Performs a lifting stress and stability analysis and compares the results to a set of criteria
   stbLiftingCheckArtifact CheckLifting(const stbIGirder* pGirder,const stbILiftingStabilityProblem* pStabilityProblem,const stbCriteria& criteria) const;

   // Performs a hauling stress and stability analysis and compares the results to a set of criteria
   stbHaulingCheckArtifact CheckHauling(const stbIGirder* pGirder,const stbIHaulingStabilityProblem* pStabilityProblem,const stbCriteria& criteria) const;

private:
   mutable PoiIDType m_FirstPoi, m_LastPoi; // first and last poiIDs used for computing Zo
   mutable std::vector<Float64> m_vPoi; // location of POIs used for computing Zo

   // General initialization of the results object
   void PrepareResults(const stbIGirder* pGirder,const stbIStabilityProblem* pStabilityProblem,stbResults& results) const;

   // builds the FEM model
   void BuildModel(const stbIGirder* pGirder,const stbIStabilityProblem* pStabilityProblem,stbResults& results,IFem2dModel** ppModel,PoiIDType* pMidSpanPoiID) const;

   // Common analysis code
   void Analyze(const stbIGirder* pGirder,const stbIStabilityProblem* pStabilityProblem,stbResults& results,IFem2dModel** ppModel,PoiIDType* pMidSpanPoiID) const;

   // analyze for lifting
   void AnalyzeLifting(const stbIGirder* pGirder,const stbILiftingStabilityProblem* pStabilityProblem,stbLiftingResults& results) const;

   // analyze for hauling
   void AnalyzeHauling(const stbIGirder* pGirder,const stbIHaulingStabilityProblem* pStabilityProblem,stbHaulingResults& results) const;

   // performs a numerical integration to compute Zo
   Float64 ComputeZo(const stbIGirder* pGirder,IFem2dModel* pModel) const;
};
