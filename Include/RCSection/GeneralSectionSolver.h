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
#include <RCSection/GeneralSectionSlice.h>
#include <RCSection/GeneralSection.h>
#include <RCSection/GeneralSectionSolution.h>
#include <GeomModel/Line2d.h>
#include <GeomModel/Primitives.h>

namespace WBFL
{
   namespace RCSection
   {
      class GeneralSectionSolverImpl;

      /// Performs a biaxial fiber based general section analysis on a GeneralSection model given a state of strains represented by a Plane3d object.
      class RCSCLASS GeneralSectionSolver
      {
      public:
         GeneralSectionSolver();
         GeneralSectionSolver(const GeneralSectionSolver& other) = delete;
         ~GeneralSectionSolver();
         
         GeneralSectionSolver& operator=(const GeneralSectionSolver& other) = delete;

         /// Set the GeneralSection to be analyzed
         void SetSection(const std::shared_ptr<const IGeneralSection>& section);
         const std::shared_ptr<const IGeneralSection>& GetSection() const;

         /// The number of slices to subdivide the section into for analysis
         void SetSlices(IndexType nSlices);
         IndexType GetSlices() const;

         /// A factor that varies the height of the slices. 
         ///
         /// The height of the slice furthest from the compression face is this factor times the height of the first slice. If the slice growth factor is 2, the last slice
         /// will be twice as tall as the first slice.
         ///
         /// Slice heights reduce when the factor is less than 1 and grow if greater than 1. All slices are the same height wht the factor is 1.
         void SetSliceGrowthFactor(Float64 sliceGrowthFactor);
         Float64 GetSliceGrowthFactor() const;

         /// Analyses the section for a given state of strain
         ///
         /// \param incrementalStrainPlane Plane object representing the state of incremental strain. The incremental strain is added to the initial strain defined in the general section model resulting in the total strain. The total strain is input to the StressStrainModel objects to compute stress.
         std::unique_ptr<GeneralSectionSolution> Solve(const WBFL::Geometry::Plane3d& incrementalStrainPlane) const;

      private:
         std::unique_ptr<GeneralSectionSolverImpl> m_pImpl;
      };
   };
};