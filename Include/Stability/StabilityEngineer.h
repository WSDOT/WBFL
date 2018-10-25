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

#pragma once

#include <Stability\StabilityExp.h>
#include <Stability\StabilityProblem.h>
#include <Stability\LiftingCriteria.h>
#include <Stability\LiftingResults.h>
#include <Stability\HaulingCriteria.h>
#include <Stability\HaulingResults.h>
#include <Stability\LiftingCheckArtifact.h>
#include <Stability\HaulingCheckArtifact.h>

#include <WBFLFem2d.h>

#include <WBFLGenericBridge.h>

/*****************************************************************************
CLASS 
   stbStabilityEngineer

DESCRIPTION
   Performes the stability analysis
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
   stbLiftingCheckArtifact CheckLifting(const stbIGirder* pGirder,const stbILiftingStabilityProblem* pStabilityProblem,const stbLiftingCriteria& criteria) const;

   // Performs a hauling stress and stability analysis and compares the results to a set of criteria
   stbHaulingCheckArtifact CheckHauling(const stbIGirder* pGirder,const stbIHaulingStabilityProblem* pStabilityProblem,const stbHaulingCriteria& criteria) const;

private:
   CComPtr<IRebarFactory> m_RebarFactory;

   mutable PoiIDType m_StartPoi, m_MidSpanPoi; // poi at start of girder and mid-span. used for computing deflection relative to the ends of a girder

   mutable PoiIDType m_FirstPoi, m_LastPoi; // first and last poiIDs used for computing Zo
   mutable std::vector<Float64> m_vPoi; // location of POIs used for computing Zo

   // General initialization of the results object
   void PrepareResults(const stbIGirder* pGirder,const stbIStabilityProblem* pStabilityProblem,stbResults& results) const;

   // builds the FEM model
   void BuildModel(const stbIGirder* pGirder,const stbIStabilityProblem* pStabilityProblem,stbResults& results,IFem2dModel** ppModel) const;

   // Common analysis code
   void Analyze(const stbIGirder* pGirder,const stbIStabilityProblem* pStabilityProblem,stbResults& results,IFem2dModel** ppModel) const;

   // analyze for lifting
   void AnalyzeLifting(const stbIGirder* pGirder,const stbILiftingStabilityProblem* pStabilityProblem,stbLiftingResults& results) const;

   // analyze for hauling
   void AnalyzeHauling(const stbIGirder* pGirder,const stbIHaulingStabilityProblem* pStabilityProblem,stbHaulingResults& results) const;

   // Determines Xleft, relative to the roll axis
   Float64 ComputeXcg(const stbIGirder* pGirder, stbResults& results) const;

   // Deterimes how to compute Zo
   void GetZoComputationMethod(const stbIGirder* pGirder,const stbIStabilityProblem* pStabilityProblem,IFem2dModel* pModel,stbResults& results) const;

   // Computes Zo by either a closed form exact solution or by numerical integration
   Float64 ComputeZo(const stbIGirder* pGirder,const stbIStabilityProblem* pStabilityProblem,IFem2dModel* pModel,stbResults& results) const;

   // Get a rebar layout model
   void GetRebarLayout(const stbIGirder* pGirder,IRebarLayout** ppRebarLayout) const;

   Float64 ComputePz(Float64 velocity,Float64 Cd) const;
};
