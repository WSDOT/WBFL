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
      class GeneralSectionSolverImpl
      {
      public:
         GeneralSectionSolverImpl() = default;
         GeneralSectionSolverImpl(const GeneralSectionSolverImpl& other) = default;
         ~GeneralSectionSolverImpl() = default;

         GeneralSectionSolverImpl& operator=(const GeneralSectionSolverImpl& other) = default;

         void SetSection(const std::shared_ptr<const IGeneralSection>& section);
         const std::shared_ptr<const IGeneralSection>& GetSection() const;

         void SetSlices(IndexType nSlices);
         IndexType GetSlices() const;

         void SetSliceGrowthFactor(Float64 sliceGrowthFactor);
         Float64 GetSliceGrowthFactor() const;

         std::unique_ptr<GeneralSectionSolution> Solve(const WBFL::Geometry::Plane3d& incrementalStrainPlane) const;

      private:
         std::shared_ptr<const IGeneralSection> m_Section;
         IndexType m_nSlices{ 100 };
         Float64 m_SliceGrowthFactor{ 1.0 }; // all slices are equal height

         mutable bool m_bDecomposed{ false };

         mutable WBFL::Geometry::Line2d m_NeutralAxis;
         mutable WBFL::Geometry::Line2d m_TestLine;
         mutable WBFL::Geometry::Rect2d m_ClippingRect;

         // Basic information about the slice shape before processing
         struct SHAPEINFO
         {
            IndexType ShapeIdx; // index of the shape in the general section model
            std::shared_ptr<const WBFL::Geometry::Shape> Shape; // shape of the slice
            std::shared_ptr<const WBFL::Materials::StressStrainModel> FgMaterial;
            std::shared_ptr<const WBFL::Materials::StressStrainModel> BgMaterial;
            std::shared_ptr<const WBFL::Geometry::Plane3d> InitialStrain;
            Float64 Le; // elongation length (typically 1 unit, but can be different for unbonded reinforcement elements)
            SHAPEINFO(IndexType shapeIdx,
               const std::shared_ptr<const WBFL::Geometry::Shape>& shape,
               const std::shared_ptr<const WBFL::Materials::StressStrainModel>& fg,
               const std::shared_ptr<const WBFL::Materials::StressStrainModel>& bg,
               const std::shared_ptr<const WBFL::Geometry::Plane3d>& initialStrain,
               Float64 Le) : ShapeIdx(shapeIdx), Shape(shape), FgMaterial(fg), BgMaterial(bg), InitialStrain(initialStrain), Le(Le)
            {}
         };
         
         // Slice properties
         struct SLICEINFO
         {
            IndexType ShapeIdx; // index of the general section shape from which this slice is taken
            Float64 Area; // slice area
            Float64 Top; // top of slice elevation (may be off the section)
            Float64 Bottom; // bottom of slice elevation (may be off the section)
            WBFL::Geometry::Point2d pntCG;
            Float64 ei; // initial strain at the centroid of this slice
            Float64 Le; // elongation length (typically 1 unit, but can be different for unbonded reinforcement elements)
            std::shared_ptr<const WBFL::Materials::StressStrainModel> FgMaterial;
            std::shared_ptr<const WBFL::Materials::StressStrainModel> BgMaterial;
            std::shared_ptr<const WBFL::Geometry::Shape> SliceShape;

            SLICEINFO() = default;
            SLICEINFO(const SLICEINFO& other) = default;
            SLICEINFO& operator=(const SLICEINFO& other) = default;
         };

         mutable std::vector<SLICEINFO> m_Slices;


         void DecomposeSection(const WBFL::Geometry::Plane3d& strainPlane) const;
         bool IsNeutralAxisParallel(const WBFL::Geometry::Plane3d& strainPlane) const;
         void UpdateNeutralAxis(const WBFL::Geometry::Plane3d& strainPlane, WBFL::Geometry::Line2d& line) const;

         void AnalyzeSlice(const SLICEINFO& slice, const WBFL::Geometry::Plane3d& incrementalStrainPlane, Float64& P, Float64& Mx, Float64& My, Float64& fg_stress, Float64& bg_stress, Float64& stress, Float64& incrementalStrain, Float64& totalStrain, bool& bExceededStrainLimits) const;
         bool SliceShape(const SHAPEINFO& shapeInfo, Float64 angle, Float64 sliceTop, Float64 sliceBottom, SLICEINFO& sliceInfo) const;
         Float64 GetNeutralAxisAngle() const;
      };
   };
};