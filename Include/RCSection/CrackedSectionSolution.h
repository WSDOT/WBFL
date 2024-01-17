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
#include <RCSection/CrackedSectionSlice.h>
#include <GeomModel/Primitives.h>
#include <GeomModel/ElasticProperties.h>

namespace WBFL
{
   namespace RCSection
   {
      class CrackedSectionSolutionImpl;

      /// Solution to a biaxial fiber based Cracked section analysis.
      /// CrackedSectionSolution objects are created by CrackedSectionSolver objects.
      class RCSCLASS CrackedSectionSolution
      {
      public:
         CrackedSectionSolution();
         CrackedSectionSolution(
            const WBFL::Geometry::Point2d& cg, ///< Centroid of the cracked section
            std::vector<std::unique_ptr<CrackedSectionSlice>>&& vSlices ///< Array of fibers ("slices") resulting from the discretization of the cross section.
         );
         CrackedSectionSolution(const CrackedSectionSolution& other) = delete; // can't copy because of unique_ptr - also don't need copy semantics
         ~CrackedSectionSolution();
         
         CrackedSectionSolution& operator=(const CrackedSectionSolution& other) = delete; // can't assign

         /// Initialize with the solution results
         void InitSolution(
            const WBFL::Geometry::Point2d& cg, ///< Centroid of the cracked section
            std::vector<std::unique_ptr<CrackedSectionSlice>>&& vSlices ///< Array of fibers ("slices") resulting from the discretization of the cross section.
         );

         /// Centroid of the cracked section
         const WBFL::Geometry::Point2d& GetCentroid() const;

         /// Number of slices
         IndexType GetSliceCount() const;

         /// Returns a slice
         const CrackedSectionSlice& GetSlice(IndexType sliceIdx) const;

         /// Returns the elastic properties of the cracked section
         WBFL::Geometry::ElasticProperties GetElasticProperties() const;

      private:
         std::unique_ptr<CrackedSectionSolutionImpl> m_pImpl;
      };
   };
};