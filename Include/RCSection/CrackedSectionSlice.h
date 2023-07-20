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
#include <GeomModel/Shape.h>
#include <GeomModel/Plane3d.h>
#include <Materials/StressStrainModel.h>

namespace WBFL
{
   namespace RCSection
   {
      class CrackedSectionSliceImpl;

      /// A "slice" in a fiber based discretization of a GeneralSection cross section object. 
      /// CrackedSectionSlice objects are created by the CrackedSectionSolver, as part of a section analysis and 
      /// are obtained through the solution object CrackedSectionSolution. These objects have fiber level state of stress information 
      /// for the related section analysis solution.
      class RCSCLASS CrackedSectionSlice
      {
      public:
         CrackedSectionSlice();
         CrackedSectionSlice(
            IndexType shapeIdx, ///< Index of the general section shape from which this slice is cut
            const std::shared_ptr<const WBFL::Geometry::Shape>& shape, ///< Shape of the slice
            Float64 A, ///< Slice area
            const WBFL::Geometry::Point2d& cg, ///< Location of the slice centroid
            Float64 Efg, ///< Modulus of elasticity of the foreground material
            Float64 Ebg ///< Modulus of elasticity of the background material
         );
         CrackedSectionSlice(const CrackedSectionSlice& other) = delete; // can't copy because of unique_ptr - also don't need copy semantics
         ~CrackedSectionSlice();
         
         CrackedSectionSlice& operator=(const CrackedSectionSlice& other) = delete; // can't assign

         /// Initializes the slice with its properties
         void InitSlice(
            IndexType shapeIdx, ///< Index of the general section shape from which this slice is cut
            const std::shared_ptr<const WBFL::Geometry::Shape>& shape, ///< Shape of the slice
            Float64 A, ///< Slice area
            const WBFL::Geometry::Point2d& cg, ///< Location of the slice centroid
            Float64 Efg, ///< Modulus of elasticity of the foreground material
            Float64 Ebg ///< Modulus of elasticity of the background material
         );

         /// Index of the general section shape from which this slice is taken
         IndexType GetShapeIndex() const;

         /// Shape of the slice
         const WBFL::Geometry::Shape& GetShape() const;

         /// Centroid of the slice
         const WBFL::Geometry::Point2d& GetCentroid() const;

         /// Modulus of elasticity of the foreground material
         Float64 GetForegroundE() const;

         /// Modulus of elasticity of the background material
         Float64 GetBackgroundE() const;

      private:
         std::unique_ptr<CrackedSectionSliceImpl> m_pImpl;
      };
   };
};