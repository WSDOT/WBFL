///////////////////////////////////////////////////////////////////////
// RCSection - Reinforced concrete section analysis modeling
// Copyright © 1999-2025  Washington State Department of Transportation
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
#include <RCSection/MomentCurvatureSolution.h>

namespace WBFL
{
   namespace RCSection
   {
      class MomentCurvatureSolverImpl;

      /// Performs a moment curvature analysis for a GeneralSection objects.
      /// This solver increases curvature from zero until the maximum strain limit of a material is reached.
      class RCSCLASS MomentCurvatureSolver
      {
      public:
         MomentCurvatureSolver();
         MomentCurvatureSolver(const MomentCurvatureSolver& other) = delete; // can't copy because of unique_ptr - also don't need copy semantics
         ~MomentCurvatureSolver();
         
         MomentCurvatureSolver& operator=(const MomentCurvatureSolver& other) = delete; // can't assign

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

         /// Convergance tolerance for axial force equilibrium
         void SetTolerance(Float64 tolerance);
         Float64 GetTolerance() const;

         /// Maximum number of iterations before solution fails
         void SetMaxIterations(IndexType maxIter);
         IndexType GetMaxIterations() const;

         /// The initial step size used for curvature increments. The step size is automatically reduced as the analysis nears the failure point.
         void SetInitialCurvatureStep(Float64 k);
         Float64 GetInitialCurvatureStep() const;

         std::unique_ptr<MomentCurvatureSolution> Solve(
            Float64 Fz, ///< Externally applied axial force.
            Float64 angle ///< Direction of the neutral axis (radians), measured counter-clockwise from the X axis
         ) const;

      private:
         std::unique_ptr<MomentCurvatureSolverImpl> m_pImpl;
      };
   };
};