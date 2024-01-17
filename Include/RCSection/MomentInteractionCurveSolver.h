///////////////////////////////////////////////////////////////////////
// RCSection - Reinforced concrete section analysis modeling
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

#include <RCSection/RCSectionExp.h>
#include <RCSection/GeneralSection.h>
#include <RCSection/InteractionCurveSolution.h>
#include <RCSection/CapacityLimit.h>

namespace WBFL
{
   namespace RCSection
   {
      class MomentInteractionCurveSolverImpl;

      /// Computes a moment interaction diagram for a GeneralSection object.
      /// This solver computes Mx-My values for a given axial force Fz
      class RCSCLASS MomentInteractionCurveSolver
      {
      public:
         MomentInteractionCurveSolver();
         MomentInteractionCurveSolver(const MomentInteractionCurveSolver& other) = delete; // can't copy because of unique_ptr - also don't need copy semantics
         ~MomentInteractionCurveSolver();
         
         MomentInteractionCurveSolver& operator=(const MomentInteractionCurveSolver& other) = delete; // can't assign

         /// GeneralSection object to be analyzed
         void SetSection(const std::shared_ptr<const IGeneralSection>& section);
         const std::shared_ptr<const IGeneralSection>& GetSection() const;
         
         /// Number of slices to subdivide the section into for analysis
         void SetSlices(IndexType nSlices);
         IndexType GetSlices() const;

         /// A factor that varies the height of the slices.
         ///
         /// The height of the slice furthest from the compression face is this factor times the height of the first slice.If the slice growth factor is 2, the last slice will be twice as tall as the first slice.
         ///
         ///  Slice heights reduce when the factor is less than 1 and grow if greater than 1. All slices are the same height wht the factor is 1.
         void SetSliceGrowthFactor(Float64 sliceGrowthFactor);
         Float64 GetSliceGrowthFactor() const;

         /// Convergence tolerance for Moment force equilibrium
         void SetTolerance(Float64 tolerance);
         Float64 GetTolerance() const;

         /// Maximum number of iterations before solution fails
         void SetMaxIterations(IndexType maxIter);
         IndexType GetMaxIterations() const;

         /// Compression limit
         ///
         /// The compression limit is the force state for the maximum compression force that can be applied to the section
         const CapacityLimit& GetCompressionLimit() const;

         /// Tension limit
         ///
         /// The tension limit is the force state for the maximum tensile force that can be applied to the section
         const CapacityLimit& GetTensionLimit() const;

         /// Performs the moment interaction analysis.
         ///
         /// Note that the solution does not contain a MomentCurvatureSolution for TWO_PI. This is the same solution for an angle of 0.
         std::unique_ptr<InteractionCurveSolution> Solve(
            Float64 Fz, ///< Axial force
            Float64 startNA, ///< Starting direction of the neutral axis, measures counter-clockwise from the X axis (radius)
            Float64 endNA, ///< Ending direction of the neutral axis, measures counter-clockwise from the X axis (radius)
            IndexType nSteps ///< Number of neutral axis increments
            ) const;

      private:
         std::unique_ptr<MomentInteractionCurveSolverImpl> m_pImpl;
      };
   };
};