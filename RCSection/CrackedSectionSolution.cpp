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

#include <RCSection/RCSectionLib.h>
#include <RCSection/CrackedSectionSolution.h>
#include <GeomModel/Section.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace WBFL::RCSection;

namespace WBFL
{
   namespace RCSection
   {
      class CrackedSectionSolutionImpl
      {
      public:
         CrackedSectionSolutionImpl() = default;
         CrackedSectionSolutionImpl(const CrackedSectionSolutionImpl& other) = default;
         ~CrackedSectionSolutionImpl() = default;

         CrackedSectionSolutionImpl& operator=(const CrackedSectionSolutionImpl& other) = default;

         void InitSolution(
            const WBFL::Geometry::Point2d& cg,
            std::vector<std::unique_ptr<CrackedSectionSlice>>&& vSlices
         );

         const WBFL::Geometry::Point2d& GetCentroid() const;
         IndexType GetSliceCount() const;
         const std::unique_ptr<CrackedSectionSlice>& GetSlice(IndexType sliceIdx) const;
         WBFL::Geometry::ElasticProperties GetElasticProperties() const;

      private:
         WBFL::Geometry::Point2d m_CG;
         std::vector<std::unique_ptr<CrackedSectionSlice>> m_vSlices;
      };


      void CrackedSectionSolutionImpl::InitSolution(
         const WBFL::Geometry::Point2d& cg,
         std::vector<std::unique_ptr<CrackedSectionSlice>>&& vSlices
      )
      {
         m_CG = cg;
         m_vSlices = std::move(vSlices);
      }

      const WBFL::Geometry::Point2d& CrackedSectionSolutionImpl::GetCentroid() const
      {
         return m_CG;
      }

      IndexType CrackedSectionSolutionImpl::GetSliceCount() const
      {
         return m_vSlices.size();
      }

      const std::unique_ptr<CrackedSectionSlice>& CrackedSectionSolutionImpl::GetSlice(IndexType sliceIdx) const
      {
         PRECONDITION(sliceIdx < m_vSlices.size());
         return m_vSlices[sliceIdx];
      }

      WBFL::Geometry::ElasticProperties CrackedSectionSolutionImpl::GetElasticProperties() const
      {
         WBFL::Geometry::Section section;

         // add each slice into a composite section object
         for(const auto& slice : m_vSlices)
         {
            Float64 Efg = slice->GetForegroundE();
            Float64 Ebg = slice->GetBackgroundE();

            const auto& shape = slice->GetShape();
            
            if (!IsZero(Efg))
            {
#pragma Reminder("WORKING HERE - Modernization - section.AddComponent creates a clone because section tries to own the shapes - reimplement section using shared_ptrs")
               // only add slices that aren't cracked
               section.AddComponent(*shape, Efg, 0.0, 0.0, 0.0, WBFL::Geometry::SectionComponent::ComponentType::Structural);

               if (!IsZero(Ebg))
               {
                  // add the void
                  section.AddComponent(*shape, 0.0, Ebg, 0.0, 0.0, WBFL::Geometry::SectionComponent::ComponentType::Nonstructural);
               }
            }
         }

         // get the elastic properties
         return section.GetElasticProperties();
      }
   };
};

////////////////////////////////////////////////
CrackedSectionSolution::CrackedSectionSolution()
{
   m_pImpl = std::make_unique<CrackedSectionSolutionImpl>();
}

CrackedSectionSolution::CrackedSectionSolution(
   const WBFL::Geometry::Point2d& cg, ///< Centroid of the cracked section
   std::vector<std::unique_ptr<CrackedSectionSlice>>&& vSlices ///< Array of fibers ("slices") resulting from the discritization of the cross section.
)
{
   m_pImpl = std::make_unique<CrackedSectionSolutionImpl>();
   InitSolution(cg, std::move(vSlices));
}

CrackedSectionSolution::~CrackedSectionSolution() = default;

void CrackedSectionSolution::InitSolution(
   const WBFL::Geometry::Point2d& cg,
   std::vector<std::unique_ptr<CrackedSectionSlice>>&& vSlices
)
{
   m_pImpl->InitSolution(cg, std::move(vSlices));
}

const WBFL::Geometry::Point2d& CrackedSectionSolution::GetCentroid() const
{
   return m_pImpl->GetCentroid();
}

IndexType CrackedSectionSolution::GetSliceCount() const
{
   return m_pImpl->GetSliceCount();
}

const std::unique_ptr<CrackedSectionSlice>& CrackedSectionSolution::GetSlice(IndexType sliceIdx) const
{
   return m_pImpl->GetSlice(sliceIdx);
}

WBFL::Geometry::ElasticProperties CrackedSectionSolution::GetElasticProperties() const
{
   return m_pImpl->GetElasticProperties();
}

#if defined _UNITTEST
bool CrackedSectionSolution::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("CrackedSectionSolution");

   //TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for CrackedSectionSolution");
   // not much to test here

   TESTME_EPILOG("CrackedSectionSolution");
}
#endif // _UNITTEST
