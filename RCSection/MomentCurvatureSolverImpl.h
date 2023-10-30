///////////////////////////////////////////////////////////////////////
// RCSection - Reinforced concrete section analysis modeling
// Copyright © 1999-2023  Washington State Department of Transportation
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

#include <RCSection/RCSectionExp.h>
#include <RCSection/GeneralSectionSolver.h>
#include <RCSection/GeneralSectionSolution.h>
#include <RCSection/MomentCapacitySolver.h>
#include <RCSection/MomentCurvatureSolution.h>

namespace WBFL
{
   namespace RCSection
   {
      class RCSCLASS MomentCurvatureSolverImpl
      {
      public:
         MomentCurvatureSolverImpl() = default;
         MomentCurvatureSolverImpl(const MomentCurvatureSolverImpl& other) = default;
         ~MomentCurvatureSolverImpl() = default;
         
         MomentCurvatureSolverImpl& operator=(const MomentCurvatureSolverImpl& other) = default;

         void SetSection(const std::shared_ptr<const IGeneralSection>& section);
         const std::shared_ptr<const IGeneralSection>& GetSection() const;
         
         void SetSlices(IndexType nSlices);
         IndexType GetSlices() const;

         void SetSliceGrowthFactor(Float64 sliceGrowthFactor);
         Float64 GetSliceGrowthFactor() const;

         void SetTolerance(Float64 tolerance);
         Float64 GetTolerance() const;

         void SetMaxIterations(IndexType maxIter);
         IndexType GetMaxIterations() const;

         void SetInitialCurvatureStep(Float64 k);
         Float64 GetInitialCurvatureStep() const;

         std::unique_ptr<MomentCurvatureSolution> Solve(Float64 Fz, Float64 angle) const;

      private:
         Float64 m_kInitialStep{ 1e-5 };
         MomentCapacitySolver m_CapacitySolver;

         Float64 GetCurvatureIncrement(Uint32 nFail) const;
         bool AnalyzeSection(Float64 Fz, Float64 angle, Float64 k, std::unique_ptr<MomentCurvatureSolution>& solution) const;
      };
   };
};