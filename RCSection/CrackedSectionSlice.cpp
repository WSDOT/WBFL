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
#include <RCSection\CrackedSectionSlice.h>

using namespace WBFL::RCSection;

namespace WBFL
{
   namespace RCSection
   {
      class CrackedSectionSliceImpl
      {
      public:
         CrackedSectionSliceImpl() = default;
         CrackedSectionSliceImpl(
            IndexType shapeIdx,
            const std::shared_ptr<const WBFL::Geometry::Shape>& shape,
            Float64 A,
            const WBFL::Geometry::Point2d& cg,
            Float64 Efg,
            Float64 Ebg
         );
         CrackedSectionSliceImpl(const CrackedSectionSliceImpl& other) = default;
         ~CrackedSectionSliceImpl() = default;

         CrackedSectionSliceImpl& operator=(const CrackedSectionSliceImpl& other) = default;

         void InitSlice(
            IndexType shapeIdx,
            const std::shared_ptr<const WBFL::Geometry::Shape>& shape,
            Float64 A,
            const WBFL::Geometry::Point2d& cg,
            Float64 Efg,
            Float64 Ebg
         );
         IndexType GetShapeIndex() const;
         const std::shared_ptr<const WBFL::Geometry::Shape>& GetShape() const;
         const WBFL::Geometry::Point2d& GetCentroid() const;
         Float64 GetForegroundE() const;
         Float64 GetBackgroundE() const;

      private:
         IndexType m_ShapeIdx{ INVALID_INDEX };
         std::shared_ptr<const WBFL::Geometry::Shape> m_Shape;
         WBFL::Geometry::Point2d m_CG;
         Float64 m_Efg{ 0.0 };
         Float64 m_Ebg{ 0.0 };
         Float64 m_Area{ 0.0 };
      };

      CrackedSectionSliceImpl::CrackedSectionSliceImpl(
         IndexType shapeIdx,
         const std::shared_ptr<const WBFL::Geometry::Shape>& shape,
         Float64 A,
         const WBFL::Geometry::Point2d& cg,
         Float64 Efg,
         Float64 Ebg
      )
      {
         InitSlice(shapeIdx, shape, A, cg, Efg, Ebg);
      }


      void CrackedSectionSliceImpl::InitSlice(
         IndexType shapeIdx,
         const std::shared_ptr<const WBFL::Geometry::Shape>& shape,
         Float64 A,
         const WBFL::Geometry::Point2d& cg,
         Float64 Efg,
         Float64 Ebg
      )
      {
         m_ShapeIdx = shapeIdx;
         m_Shape = shape;
         m_Area = A;
         m_CG = cg;
         m_Efg = Efg;
         m_Ebg = Ebg;
      }

      IndexType CrackedSectionSliceImpl::GetShapeIndex() const
      {
         return m_ShapeIdx;
      }

      const std::shared_ptr<const WBFL::Geometry::Shape>& CrackedSectionSliceImpl::GetShape() const
      {
         return m_Shape;
      }

      const WBFL::Geometry::Point2d& CrackedSectionSliceImpl::GetCentroid() const
      {
         return m_CG;
      }

      Float64 CrackedSectionSliceImpl::GetForegroundE() const
      {
         return m_Efg;
      }

      Float64 CrackedSectionSliceImpl::GetBackgroundE() const
      {
         return m_Ebg;
      }
   };
};

////////////////////////////////////////////////
CrackedSectionSlice::CrackedSectionSlice()
{
   m_pImpl = std::make_unique<CrackedSectionSliceImpl>();
}

CrackedSectionSlice::CrackedSectionSlice(IndexType shapeIdx,const std::shared_ptr<const WBFL::Geometry::Shape>& shape, Float64 A, const WBFL::Geometry::Point2d& cg, Float64 Efg, Float64 Ebg)
{
   m_pImpl = std::make_unique<CrackedSectionSliceImpl>();
   InitSlice(shapeIdx, shape, A, cg, Efg, Ebg);
}

CrackedSectionSlice::~CrackedSectionSlice() = default;

void CrackedSectionSlice::InitSlice(
   IndexType shapeIdx,
   const std::shared_ptr<const WBFL::Geometry::Shape>& shape,
   Float64 A,
   const WBFL::Geometry::Point2d& cg, 
   Float64 Efg,
   Float64 Ebg
)
{
   m_pImpl->InitSlice(shapeIdx, shape, A, cg, Efg, Ebg);
}

IndexType CrackedSectionSlice::GetShapeIndex() const
{
   return m_pImpl->GetShapeIndex();
}

const std::shared_ptr<const WBFL::Geometry::Shape>& CrackedSectionSlice::GetShape() const
{
   return m_pImpl->GetShape();
}

const WBFL::Geometry::Point2d& CrackedSectionSlice::GetCentroid() const
{
   return m_pImpl->GetCentroid();
}

Float64 CrackedSectionSlice::GetForegroundE() const
{
   return m_pImpl->GetForegroundE();
}

Float64 CrackedSectionSlice::GetBackgroundE() const
{
   return m_pImpl->GetBackgroundE();
}

#if defined _UNITTEST
bool CrackedSectionSlice::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("CrackedSectionSlice");

   // there really isn't much to test here
   //TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for CrackedSectionSlice");

   TESTME_EPILOG("CrackedSectionSlice");
}
#endif // _UNITTEST
