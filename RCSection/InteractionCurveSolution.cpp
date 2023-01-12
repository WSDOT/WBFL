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
#include <RCSection\InteractionCurveSolution.h>

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
      class InteractionCurveSolutionImpl
      {
      public:
         InteractionCurveSolutionImpl() = default;
         InteractionCurveSolutionImpl(const InteractionCurveSolutionImpl& other) = default;
         ~InteractionCurveSolutionImpl() = default;

         InteractionCurveSolutionImpl& operator=(const InteractionCurveSolutionImpl& other) = default;

         void AddSolutionPoint(std::unique_ptr<MomentCapacitySolution>&& capacity);
         Float64 GetNeutralAxisDirection(IndexType index) const;
         Float64 GetFz(IndexType index) const;
         const std::unique_ptr<MomentCapacitySolution>& GetSolutionPoint(IndexType index) const;
         IndexType GetSolutionPointCount() const;
         void SortByFz();
         void SortByNeutralAxisDirection();

      private:
         std::vector<std::unique_ptr<MomentCapacitySolution>> m_vCapacity;
      };

      void InteractionCurveSolutionImpl::AddSolutionPoint(std::unique_ptr<MomentCapacitySolution>&& capacity)
      {
         m_vCapacity.emplace_back(std::move(capacity));
      }

      Float64 InteractionCurveSolutionImpl::GetFz(IndexType index) const
      {
         PRECONDITION(index < m_vCapacity.size());
         return m_vCapacity[index]->GetFz();
      }

      Float64 InteractionCurveSolutionImpl::GetNeutralAxisDirection(IndexType index) const
      {
         PRECONDITION(index < m_vCapacity.size());
         return m_vCapacity[index]->GetNeutralAxisDirection();
      }

      const std::unique_ptr<MomentCapacitySolution>& InteractionCurveSolutionImpl::GetSolutionPoint(IndexType index) const
      {
         PRECONDITION(index < m_vCapacity.size());
         return m_vCapacity[index];
      }

      IndexType InteractionCurveSolutionImpl::GetSolutionPointCount() const
      {
         return m_vCapacity.size();
      }

      void InteractionCurveSolutionImpl::SortByFz()
      {
         std::sort(m_vCapacity.begin(), m_vCapacity.end(), [](const auto& a, const auto& b) {return a->GetFz() < b->GetFz(); });
      }

      void InteractionCurveSolutionImpl::SortByNeutralAxisDirection()
      {
         std::sort(m_vCapacity.begin(), m_vCapacity.end(), [](const auto& a, const auto& b) {return a->GetNeutralAxisDirection() < b->GetNeutralAxisDirection(); });
      }
   };
};

////////////////////////////////////////////////
InteractionCurveSolution::InteractionCurveSolution()
{
   m_pImpl = std::make_unique<InteractionCurveSolutionImpl>();
}

InteractionCurveSolution::~InteractionCurveSolution() = default;

void InteractionCurveSolution::AddSolutionPoint(std::unique_ptr<MomentCapacitySolution>&& capacity)
{
   m_pImpl->AddSolutionPoint(std::move(capacity));
}

Float64 InteractionCurveSolution::GetFz(IndexType index) const
{
   return m_pImpl->GetFz(index);
}

Float64 InteractionCurveSolution::GetNeutralAxisDirection(IndexType index) const
{
   return m_pImpl->GetNeutralAxisDirection(index);
}

const std::unique_ptr<MomentCapacitySolution>& InteractionCurveSolution::GetSolutionPoint(IndexType index) const
{
   return m_pImpl->GetSolutionPoint(index);
}

IndexType InteractionCurveSolution::GetSolutionPointCount() const
{
   return m_pImpl->GetSolutionPointCount();
}

void InteractionCurveSolution::SortByFz()
{
   m_pImpl->SortByFz();
}

void InteractionCurveSolution::SortByNeutralAxisDirection()
{
   m_pImpl->SortByNeutralAxisDirection();
}


#if defined _UNITTEST
bool InteractionCurveSolution::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("InteractionCurveSolution");

   //TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for InteractionCurveSolution");
   // not much to test here

   TESTME_EPILOG("InteractionCurveSolution");
}
#endif // _UNITTEST
