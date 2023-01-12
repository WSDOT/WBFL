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
#include <GeomModel/Primitives.h>

namespace WBFL
{
   namespace RCSection
   {
      class CrackedSectionSolverImpl
      {
      public:
         CrackedSectionSolverImpl() = default;
         CrackedSectionSolverImpl(const CrackedSectionSolverImpl& other) = default;
         ~CrackedSectionSolverImpl() = default;

         CrackedSectionSolverImpl& operator=(const CrackedSectionSolverImpl& other) = default;

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

         std::unique_ptr<CrackedSectionSolution> Solve(Float64 naAngle) const;

      private:
         std::shared_ptr<const IGeneralSection> m_Section;
         IndexType m_nSlices{ 100 };
         Float64 m_SliceGrowthFactor{ 1.0 }; // all slices are equal height
         IndexType m_MaxIter{ 50 };
         Float64 m_Tolerance{ 0.001 };

         mutable WBFL::Geometry::Rect2d m_ClippingRect;
         mutable bool m_bDecomposed{false};

         // Basic information about the slice shape before processing
         typedef struct SHAPEINFO
         {
            IndexType ShapeIdx; // index of the shape in the general section model
            std::shared_ptr<const WBFL::Geometry::Shape> Shape; // shape of the slice
            std::shared_ptr<const WBFL::Materials::StressStrainModel> FgMaterial;
            std::shared_ptr<const WBFL::Materials::StressStrainModel> BgMaterial;
            SHAPEINFO() = default;
            SHAPEINFO(
               IndexType shapeIdx,
               const std::shared_ptr<const WBFL::Geometry::Shape>& shape, 
               const std::shared_ptr<const WBFL::Materials::StressStrainModel>& fg, 
               const std::shared_ptr<const WBFL::Materials::StressStrainModel>& bg 
               ) : ShapeIdx(shapeIdx), Shape(shape), FgMaterial(fg), BgMaterial(bg)
            {}
         } SHAPEINFO;

         // Slice properties
         typedef struct SLICEINFO
         {
            IndexType ShapeIdx; // index of the general section shape from which this slice is taken
            Float64 Area; // slice area
            Float64 Top; // top of slice elevation (may be off the section)
            Float64 Bottom; // bottom of slice elevation (may be off the section)
            WBFL::Geometry::Point2d pntCG;
            std::shared_ptr<const WBFL::Materials::StressStrainModel> FgMaterial;
            std::shared_ptr<const WBFL::Materials::StressStrainModel> BgMaterial;
            std::shared_ptr<const WBFL::Geometry::Shape> SliceShape;

            SLICEINFO() = default;
            SLICEINFO(SLICEINFO& other) = default;
            SLICEINFO& operator=(SLICEINFO& other) = default;

            bool operator<(const SLICEINFO& other) { return other.pntCG.Y() < pntCG.Y(); }
         } SLICEINFO;

         mutable std::vector<SLICEINFO> m_Slices;
         mutable Float64 m_Angle;
         mutable Float64 m_Ybottom, m_Ytop; // top and bottom of section


         void DecomposeSection() const;
         void AnalyzeSection(Float64 Yguess, std::vector<std::unique_ptr<CrackedSectionSlice>>& slices, WBFL::Geometry::Point2d& cg) const;

         void AnalyzeSlice(Float64 Yguess, SLICEINFO& slice, Float64& EA, Float64& EAx, Float64& EAy, Float64& Efg, Float64& Ebg) const;
         bool SliceShape(const SHAPEINFO& shapeInfo, Float64 sliceTop, Float64 sliceBottom, SLICEINFO& sliceInfo) const;
      };
   };
};