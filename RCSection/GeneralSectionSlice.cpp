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

#include <RCSection\RCSectionLib.h>
#include <RCSection\GeneralSectionSlice.h>

using namespace WBFL::RCSection;

namespace WBFL
{
   namespace RCSection
   {
      class GeneralSectionSliceImpl
      {
      public:
         GeneralSectionSliceImpl() = default;
         GeneralSectionSliceImpl(
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
         GeneralSectionSliceImpl(const GeneralSectionSliceImpl& other) = default;
         ~GeneralSectionSliceImpl() = default;

         GeneralSectionSliceImpl& operator=(const GeneralSectionSliceImpl& other) = default;

         void InitSlice(
            IndexType shapeIdx,
            const std::shared_ptr<const WBFL::Geometry::Shape>& shape,
            Float64 A,
            const WBFL::Geometry::Point2d& cg,
            Float64 initial_strain,
            Float64 delta_strain,
            Float64 total_strain,
            Float64 fgStress,
            Float64 bgStress,
            const std::shared_ptr<const WBFL::Materials::StressStrainModel>& fgMaterial,
            const std::shared_ptr<const WBFL::Materials::StressStrainModel>& bgMaterial,
            bool bExceededStrainLimit
         );
         IndexType GetShapeIndex() const;
         const std::shared_ptr<const WBFL::Geometry::Shape>& GetShape() const;
         Float64 GetArea() const;
         const WBFL::Geometry::Point2d& GetCentroid() const;
         Float64 GetInitialStrain() const;
         Float64 GetIncrementalStrain() const;
         Float64 GetTotalStrain() const;
         Float64 GetForegroundStress() const;
         Float64 GetBackgroundStress() const;
         const std::shared_ptr<const WBFL::Materials::StressStrainModel>& GetForegroundMaterial() const;
         const std::shared_ptr<const WBFL::Materials::StressStrainModel>& GetBackgroundMaterial() const;
         bool ExceededStrainLimit() const;

      private:
         IndexType m_ShapeIdx{INVALID_INDEX};
         std::shared_ptr<const WBFL::Geometry::Shape> m_Shape;
         std::shared_ptr<const WBFL::Materials::StressStrainModel> m_fgMaterial;
         std::shared_ptr<const WBFL::Materials::StressStrainModel> m_bgMaterial;
         WBFL::Geometry::Point2d m_CG;
         Float64 m_Area{ 0.0 };
         Float64 m_InitialStrain{ 0.0 };
         Float64 m_IncrementalStrain{ 0.0 };
         Float64 m_TotalStrain{ 0.0 };
         Float64 m_fgStress{ 0.0 };
         Float64 m_bgStress{ 0.0 };
         bool m_bExceededStrainLimit{false};
      };


      void GeneralSectionSliceImpl::InitSlice(
         IndexType shapeIdx,
         const std::shared_ptr<const WBFL::Geometry::Shape>& shape,
         Float64 A,
         const WBFL::Geometry::Point2d& cg,
         Float64 initial_strain,
         Float64 delta_strain,
         Float64 total_strain,
         Float64 fgStress,
         Float64 bgStress,
         const std::shared_ptr<const WBFL::Materials::StressStrainModel>& fgMaterial,
         const std::shared_ptr<const WBFL::Materials::StressStrainModel>& bgMaterial,
         bool bExceededStrainLimit
      )
      {
         m_ShapeIdx = shapeIdx;
         m_Shape = shape;
         m_Area = A;
         m_CG = cg;
         m_InitialStrain = initial_strain;
         m_IncrementalStrain = delta_strain;
         m_TotalStrain = total_strain;
         m_fgStress = fgStress;
         m_bgStress = bgStress;
         m_fgMaterial = fgMaterial;
         m_bgMaterial = bgMaterial;
      }

      IndexType GeneralSectionSliceImpl::GetShapeIndex() const
      {
         return m_ShapeIdx;
      }

      const std::shared_ptr<const WBFL::Geometry::Shape>& GeneralSectionSliceImpl::GetShape() const
      {
         return m_Shape;
      }

      Float64 GeneralSectionSliceImpl::GetArea() const
      {
         return m_Area;
      }

      const WBFL::Geometry::Point2d& GeneralSectionSliceImpl::GetCentroid() const
      {
         return m_CG;
      }

      Float64 GeneralSectionSliceImpl::GetInitialStrain() const
      {
         return m_InitialStrain;
      }

      Float64 GeneralSectionSliceImpl::GetIncrementalStrain() const
      {
         return m_IncrementalStrain;
      }

      Float64 GeneralSectionSliceImpl::GetTotalStrain() const
      {
         return m_TotalStrain;
      }

      Float64 GeneralSectionSliceImpl::GetForegroundStress() const
      {
         return m_fgStress;
      }

      Float64 GeneralSectionSliceImpl::GetBackgroundStress() const
      {
         return m_bgStress;
      }

      const std::shared_ptr<const WBFL::Materials::StressStrainModel>& GeneralSectionSliceImpl::GetForegroundMaterial() const
      {
         return m_fgMaterial;
      }

      const std::shared_ptr<const WBFL::Materials::StressStrainModel>& GeneralSectionSliceImpl::GetBackgroundMaterial() const
      {
         return m_bgMaterial;
      }

      bool GeneralSectionSliceImpl::ExceededStrainLimit() const
      {
         return m_bExceededStrainLimit;
      }
   };
};

////////////////////////////////////////////////
GeneralSectionSlice::GeneralSectionSlice()
{
   m_pImpl = std::make_unique<GeneralSectionSliceImpl>();
}

GeneralSectionSlice::GeneralSectionSlice(
   IndexType shapeIdx,
   const std::shared_ptr<const WBFL::Geometry::Shape>& shape,
   Float64 A,
   const WBFL::Geometry::Point2d& cg,
   Float64 initial_strain,
   Float64 delta_strain,
   Float64 total_strain,
   Float64 fgStress,
   Float64 bgStress,
   const std::shared_ptr<const WBFL::Materials::StressStrainModel>& fgMaterial,
   const std::shared_ptr<const WBFL::Materials::StressStrainModel>& bgMaterial,
   bool bExceededStrainLimit
)
{
   m_pImpl = std::make_unique<GeneralSectionSliceImpl>();
   InitSlice(shapeIdx, shape, A, cg, initial_strain, delta_strain, total_strain, fgStress, bgStress, fgMaterial, bgMaterial, bExceededStrainLimit);
}

GeneralSectionSlice::GeneralSectionSlice(const GeneralSectionSlice& other)
{
   m_pImpl = std::make_unique<GeneralSectionSliceImpl>();
   *this = other;
}

GeneralSectionSlice& GeneralSectionSlice::operator=(const GeneralSectionSlice& other)
{
   InitSlice(other.GetShapeIndex(), other.GetShape(), other.GetArea(), other.GetCentroid(), other.GetInitialStrain(), other.GetIncrementalStrain(), other.GetTotalStrain(),
      other.GetForegroundStress(), other.GetBackgroundStress(), other.GetForegroundMaterial(), other.GetBackgroundMaterial(), other.ExceededStrainLimit());

   return *this;
}

GeneralSectionSlice::~GeneralSectionSlice() = default;

void GeneralSectionSlice::InitSlice(
   IndexType shapeIdx, 
   const std::shared_ptr<const WBFL::Geometry::Shape>& shape,
   Float64 A,
   const WBFL::Geometry::Point2d& cg, 
   Float64 initial_strain, 
   Float64 delta_strain, 
   Float64 total_strain, 
   Float64 fgStress,
   Float64 bgStress,
   const std::shared_ptr<const WBFL::Materials::StressStrainModel>& fgMaterial,
   const std::shared_ptr<const WBFL::Materials::StressStrainModel>& bgMaterial,
   bool bExceededStrainLimit
)
{
   m_pImpl->InitSlice(shapeIdx, shape, A, cg, initial_strain, delta_strain, total_strain, fgStress, bgStress, fgMaterial, bgMaterial, bExceededStrainLimit);
}

IndexType GeneralSectionSlice::GetShapeIndex() const
{
   return m_pImpl->GetShapeIndex();
}

const std::shared_ptr<const WBFL::Geometry::Shape>& GeneralSectionSlice::GetShape() const
{
   return m_pImpl->GetShape();
}

Float64 GeneralSectionSlice::GetArea() const
{
   return m_pImpl->GetArea();
}

const WBFL::Geometry::Point2d& GeneralSectionSlice::GetCentroid() const
{
   return m_pImpl->GetCentroid();
}

Float64 GeneralSectionSlice::GetInitialStrain() const
{
   return m_pImpl->GetInitialStrain();
}

Float64 GeneralSectionSlice::GetIncrementalStrain() const
{
   return m_pImpl->GetIncrementalStrain();
}

Float64 GeneralSectionSlice::GetTotalStrain() const
{
   return m_pImpl->GetTotalStrain();
}

Float64 GeneralSectionSlice::GetForegroundStress() const
{
   return m_pImpl->GetForegroundStress();
}

Float64 GeneralSectionSlice::GetBackgroundStress() const
{
   return m_pImpl->GetBackgroundStress();
}

const std::shared_ptr<const WBFL::Materials::StressStrainModel>& GeneralSectionSlice::GetForegroundMaterial() const
{
   return m_pImpl->GetForegroundMaterial();
}

const std::shared_ptr<const WBFL::Materials::StressStrainModel>& GeneralSectionSlice::GetBackgroundMaterial() const
{
   return m_pImpl->GetBackgroundMaterial();
}

bool GeneralSectionSlice::ExceededStrainLimit() const
{
   return m_pImpl->ExceededStrainLimit();
}

#if defined _UNITTEST
bool GeneralSectionSlice::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("GeneralSectionSlice");

   // there really isn't much to test here
   //TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for GeneralSectionSlice");

   TESTME_EPILOG("GeneralSectionSlice");
}
#endif // _UNITTEST
