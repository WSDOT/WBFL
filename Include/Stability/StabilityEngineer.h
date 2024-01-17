///////////////////////////////////////////////////////////////////////
// Stability
// Copyright © 1999-2024  Washington State Department of Transportation
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

#include <Stability/StabilityExp.h>
#include <Stability/StabilityProblem.h>
#include <Stability/LiftingCriteria.h>
#include <Stability/LiftingResults.h>
#include <Stability/HaulingCriteria.h>
#include <Stability/HaulingResults.h>
#include <Stability/OneEndSeatedResults.h>
#include <Stability/OneEndSeatedCriteria.h>
#include <Stability/LiftingCheckArtifact.h>
#include <Stability/HaulingCheckArtifact.h>
#include <Stability/OneEndSeatedCheckArtifact.h>

#include <WBFLFem2d.h>

#include <WBFLGenericBridge.h>

namespace WBFL
{
   namespace Stability
   {

      /// Performs stability analysis for precast-prestressed concrete bridge girders
      class STABILITYCLASS StabilityEngineer
      {
      public:
         StabilityEngineer();

         /// Performs a lifting stress and stability analysis
         ///
         /// \return returns the analysis results
         LiftingResults AnalyzeLifting(
            const IGirder* pGirder, ///< the girder to be analyzed
            const ILiftingStabilityProblem* pStabilityProblem ///< the stability problem parameters
         ) const;

         /// Performs a hauling stress and stability analysis
         HaulingResults AnalyzeHauling(const IGirder* pGirder, const IHaulingStabilityProblem* pStabilityProblem) const;

         /// Performs a stress and stability analysis for a girder seated at one end
         OneEndSeatedResults AnalyzeOneEndSeated(const IGirder * pGirder, const IOneEndSeatedStabilityProblem * pStabilityProblem) const;

         /// Performs a stress and stability analysis and compares the results to a set of criteria for the lifting condition
         LiftingCheckArtifact CheckLifting(const IGirder* pGirder, const ILiftingStabilityProblem* pStabilityProblem, const LiftingCriteria& criteria) const;

         /// Performs a stress and stability analysis and compares the results to a set of criteria for the hauling condition
         HaulingCheckArtifact CheckHauling(const IGirder* pGirder, const IHaulingStabilityProblem* pStabilityProblem, const HaulingCriteria& criteria) const;

         /// Performs a stress and stability analysis and compares the results to a set of criteria for the seated at one end condition
         OneEndSeatedCheckArtifact CheckOneEndSeated(const IGirder* pGirder, const IOneEndSeatedStabilityProblem* pStabilityProblem, const OneEndSeatedCriteria& criteria) const;

      private:
         CComPtr<IRebarFactory> m_RebarFactory;

         mutable PoiIDType m_StartPoi, m_MidSpanPoi; // poi at start of girder and mid-span. used for computing deflection relative to the ends of a girder

         mutable PoiIDType m_FirstPoi, m_LastPoi; // first and last poiIDs used for computing Zo
         mutable std::vector<Float64> m_vPoi; // location of POIs used for computing Zo

         // General initialization of the results object
         void PrepareResults(const IGirder* pGirder, const IStabilityProblem* pStabilityProblem, Results& results) const;

         // builds the FEM model
         void BuildModel(const IGirder* pGirder, const IStabilityProblem* pStabilityProblem, Results& results, IFem2dModel** ppModel) const;

         // Common analysis code
         void Analyze(const IGirder* pGirder, const IStabilityProblem* pStabilityProblem, Results& results, IFem2dModel** ppModel) const;

         void AnalyzeOneEndSeated(const IGirder * pGirder, const IOneEndSeatedStabilityProblem * pStabilityProblem, OneEndSeatedResults & results) const;

         // analyze for lifting
         void AnalyzeLifting(const IGirder* pGirder, const ILiftingStabilityProblem* pStabilityProblem, LiftingResults& results) const;

         // analyze for hauling
         void AnalyzeHauling(const IGirder* pGirder, const IHaulingStabilityProblem* pStabilityProblem, HaulingResults& results) const;

         // Determines Xleft, relative to the roll axis
         Float64 ComputeXcg(const IGirder* pGirder, const IStabilityProblem* pStabilityProblem, Results& results) const;

         // Determines how to compute Zo
         void GetZoComputationMethod(const IGirder* pGirder, const IStabilityProblem* pStabilityProblem, IFem2dModel* pModel, Results& results) const;

         // Computes Zo by either a closed form exact solution or by numerical integration
         Float64 ComputeZo(const IGirder* pGirder, const IStabilityProblem* pStabilityProblem, IFem2dModel* pModel, Results& results) const;

         // Get a rebar layout model
         void GetRebarLayout(const IGirder* pGirder, IRebarLayout** ppRebarLayout) const;

         Float64 ComputePz(Float64 velocity, Float64 Cd) const;

         void FindMember(IFem2dModel* pModel, Float64 distFromStartOfModel, MemberIDType* pMbrID, Float64* pDistFromStartOfMbr) const;
      };
   }
}