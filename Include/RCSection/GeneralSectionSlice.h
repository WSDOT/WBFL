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
#include <GeomModel/Shape.h>
#include <GeomModel/Plane3d.h>
#include <Materials/StressStrainModel.h>

namespace WBFL
{
   namespace RCSection
   {
      class GeneralSectionSliceImpl;

      /// A "slice" in a fiber based discretization of a GeneralSection cross section object. 
      /// GeneralSectionSlice objects are created the GeneralSectionSolver, as part of a section analysis and 
      /// are obtained through the solution object GeneralSectionSolution. These objects have fiber level state of stress information 
      /// for the related section analysis solution.
      class RCSCLASS GeneralSectionSlice
      {
      public:
         GeneralSectionSlice();
         GeneralSectionSlice(
            IndexType shapeIdx, ///< Index of the general section shape from which this slice is cut
            const std::shared_ptr<const WBFL::Geometry::Shape>& shape, ///< Shape of the slice
            Float64 A, ///< Slice area
            const WBFL::Geometry::Point2d& cg, ///< Location of the slice centroid
            Float64 initial_strain, ///< Initial strain at CG of slice
            Float64 delta_strain, ///< Strain increment
            Float64 total_strain, ///< Total strain at CG of slice
            Float64 fgStress, ///< Foreground stress at the slice centroid
            Float64 bgStress, ///< Background stress at the slice centroid
            const std::shared_ptr<const WBFL::Materials::StressStrainModel>& fgMaterial, ///< Foreground material stress-strain model
            const std::shared_ptr<const WBFL::Materials::StressStrainModel>& bgMaterial, ///< Background material stress-strain model
            bool bExceededStrainLimit ///< Indicates if total_strain exceeds the strain limits of this slice
         );
         GeneralSectionSlice(const GeneralSectionSlice& other);
         ~GeneralSectionSlice();
         
         GeneralSectionSlice& operator=(const GeneralSectionSlice& other);

         /// Initializes the slice with its properties
         void InitSlice(
            IndexType shapeIdx, ///< Index of the general section shape from which this slice is cut
            const std::shared_ptr<const WBFL::Geometry::Shape>& shape, ///< Shape of the slice
            Float64 A, ///< Slice area
            const WBFL::Geometry::Point2d& cg, ///< Location of the slice centroid
            Float64 initial_strain, ///< Initial strain at CG of slice
            Float64 delta_strain, ///< Strain increment
            Float64 total_strain, ///< Total strain at CG of slice
            Float64 fgStress, ///< Foreground stress at the slice centroid
            Float64 bgStress, ///< Background stress at the slice centroid
            const std::shared_ptr<const WBFL::Materials::StressStrainModel>& fgMaterial, ///< Foreground material stress-strain model
            const std::shared_ptr<const WBFL::Materials::StressStrainModel>& bgMaterial, ///< Background material stress-strain model
            bool bExceededStrainLimit ///< Indicates if total_strain exceeds the strain limits of this slice
         );

         /// Index of the general section shape from which this slice is taken
         IndexType GetShapeIndex() const;

         /// Shape of the slice
         const WBFL::Geometry::Shape& GetShape() const;

         /// Area of slice
         Float64 GetArea() const;

         /// Centroid of the slice
         const WBFL::Geometry::Point2d& GetCentroid() const;

         /// Initial strain at CG of slice
         Float64 GetInitialStrain() const;

         /// Strain increment at CG of slice
         Float64 GetIncrementalStrain() const;

         /// Total strain at CG of slice
         Float64 GetTotalStrain() const;

         /// Foreground material stress at the slice centroid
         Float64 GetForegroundStress() const;

         /// Background material stress at the slice centroid
         Float64 GetBackgroundStress() const;

         /// Foreground material stress-strain model
         const std::shared_ptr<const WBFL::Materials::StressStrainModel>& GetForegroundMaterial() const;

         /// Background material stress-strain model
         const std::shared_ptr<const WBFL::Materials::StressStrainModel>& GetBackgroundMaterial() const;

         /// Indicates if the strain limit of the foreground material at this slice were exceeded
         bool ExceededStrainLimit() const;

      private:
         std::unique_ptr<GeneralSectionSliceImpl> m_pImpl;
      };
   };
};