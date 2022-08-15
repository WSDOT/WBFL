///////////////////////////////////////////////////////////////////////
// RCSection - Reinforced concrete section analysis modeling
// Copyright © 1999-2022  Washington State Department of Transportation
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
#include <RCSection/MomentCapacitySolver.h>
#include <RCSection/InteractionCurveSolution.h>

namespace WBFL
{
   namespace RCSection
   {
      class RCSCLASS AxialInteractionCurveSolverImpl
      {
      public:
         AxialInteractionCurveSolverImpl() = default;
         AxialInteractionCurveSolverImpl(const AxialInteractionCurveSolverImpl& other) = default;
         ~AxialInteractionCurveSolverImpl() = default;
         
         AxialInteractionCurveSolverImpl& operator=(const AxialInteractionCurveSolverImpl& other) = default;

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

         void GetCompressionLimit(Float64* Fz, Float64* Mx, Float64* My, Float64* eo) const;

         void GetTensionLimit(Float64* Fz, Float64* Mx, Float64* My, Float64* eo) const;

         std::unique_ptr<InteractionCurveSolution> Solve(Float64 na, IndexType nFzSteps) const;

      private:
         MomentCapacitySolver m_Solver;
      };
   };
};