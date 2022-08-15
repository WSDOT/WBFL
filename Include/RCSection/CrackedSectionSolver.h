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
#include <RCSection/CrackedSectionSlice.h>
#include <RCSection/GeneralSection.h>
#include <RCSection/CrackedSectionSolution.h>
#include <GeomModel/Line2d.h>
#include <GeomModel/Primitives.h>

namespace WBFL
{
   namespace RCSection
   {
      class CrackedSectionSolverImpl;

      /// Performs a biaxial fiber based Cracked section analysis on a GeneralSection model for a given direction of the neutral axis line
      class RCSCLASS CrackedSectionSolver
      {
      public:
         CrackedSectionSolver();
         CrackedSectionSolver(const CrackedSectionSolver& other) = delete;
         ~CrackedSectionSolver();
         
         CrackedSectionSolver& operator=(const CrackedSectionSolver& other) = delete;

         /// Set the GeneralSection to be analyzed
         void SetSection(const std::shared_ptr<const IGeneralSection>& section);
         const std::shared_ptr<const IGeneralSection>& GetSection() const;

         /// The number of slices to subdivide the section into for analysis
         void SetSlices(IndexType nSlices);
         IndexType GetSlices() const;

         /// A factor that varies the height of the slices.
         ///
         /// The height of the slice furthest from the compression face is this factor times the height of the first slice.If the slice growth factor is 2, the last slice will be twice as tall as the first slice.
         ///
         ///  Slice heights reduce when the factor is less than 1 and grow if greater than 1. All slices are the same height wht the factor is 1.
         void SetSliceGrowthFactor(Float64 sliceGrowthFactor);
         Float64 GetSliceGrowthFactor() const;

         /// Convergance tolerance for centroid
         void SetTolerance(Float64 tolerance);
         Float64 GetTolerance() const;

         /// Maximum number of iterations before solution fails
         void SetMaxIterations(IndexType maxIter);
         IndexType GetMaxIterations() const;

         /// Performs the cracked section analysis
         ///
         /// \param naAngle ///< Orientation of the neutral axis (radians), measured counter-clockwise from the X-axis
         std::unique_ptr<CrackedSectionSolution> Solve(Float64 naAngle) const;

      private:
         std::unique_ptr<CrackedSectionSolverImpl> m_pImpl;

#if defined _UNITTEST
      public:
         static bool TestMe(WBFL::Debug::Log& rlog);
      private:
         static bool TestRectangularBeam(WBFL::Debug::Log& rlog);
         static bool TestTeeBeam1(WBFL::Debug::Log& rlog);
         static bool TestTeeBeam2(WBFL::Debug::Log& rlog);
         static bool TestTeeBeam3(WBFL::Debug::Log& rlog);
#endif // _UNITTEST
      };
   };
};