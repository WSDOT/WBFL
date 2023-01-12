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
#include <RCSection\MomentCurvatureSolution.h>

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
      class MomentCurvatureSolutionImpl
      {
      public:
         MomentCurvatureSolutionImpl() = default;
         MomentCurvatureSolutionImpl(const MomentCurvatureSolutionImpl& other) = default;
         ~MomentCurvatureSolutionImpl() = default;

         MomentCurvatureSolutionImpl& operator=(const MomentCurvatureSolutionImpl& other) = default;

         void AddPoint(Float64 M, Float64 k, std::unique_ptr<MomentCapacitySolution>&& capacitySolution);
            
         Float64 GetMaxMoment() const;

         Float64 GetMaxMomentCurvature() const;

         void GetPeakCapacity(Float64& Mmax, Float64& k);

         Float64 GetMoment(IndexType idx) const;

         Float64 GetCurvature(IndexType idx) const;

         const WBFL::Geometry::Plane3d& GetIncrementalStrainPlane(IndexType idx) const;

         const std::unique_ptr<MomentCapacitySolution>& GetCapacitySolution(IndexType idx) const;

         IndexType GetPointCount() const;

      private:
         struct CurvaturePoint
         {
            CurvaturePoint() = default;
            CurvaturePoint(Float64 M, Float64 k, std::unique_ptr<MomentCapacitySolution>&& Solution) :
               M(M), k(k), Solution(std::move(Solution))
            {
            }

            Float64 M;
            Float64 k;
            std::unique_ptr<MomentCapacitySolution> Solution;

            bool operator<(const CurvaturePoint& other) const { return k < other.k; }
         };
         std::vector<CurvaturePoint> m_CurvaturePoints;
      };

      void MomentCurvatureSolutionImpl::AddPoint(Float64 M, Float64 k, std::unique_ptr<MomentCapacitySolution>&& capacitySolution)
      {
         m_CurvaturePoints.emplace_back(M, k, std::move(capacitySolution));
         std::sort(m_CurvaturePoints.begin(), m_CurvaturePoints.end());
      }

      Float64 MomentCurvatureSolutionImpl::GetMaxMoment() const
      {
         auto iter = std::max_element(m_CurvaturePoints.cbegin(), m_CurvaturePoints.cend());
         return (*iter).M;
      }

      Float64 MomentCurvatureSolutionImpl::GetMaxMomentCurvature() const
      {
         auto iter = std::max_element(m_CurvaturePoints.cbegin(), m_CurvaturePoints.cend());
         return (*iter).k;
      }

      void MomentCurvatureSolutionImpl::GetPeakCapacity(Float64& Mmax, Float64& k)
      {
         auto iter = std::max_element(m_CurvaturePoints.cbegin(), m_CurvaturePoints.cend());
         Mmax = (*iter).M;
         k = (*iter).k;
      }

      Float64 MomentCurvatureSolutionImpl::GetMoment(IndexType idx) const
      {
         PRECONDITION(idx < m_CurvaturePoints.size());
         return m_CurvaturePoints[idx].M;
      }

      Float64 MomentCurvatureSolutionImpl::GetCurvature(IndexType idx) const
      {
         PRECONDITION(idx < m_CurvaturePoints.size());
         return m_CurvaturePoints[idx].k;
      }

      const WBFL::Geometry::Plane3d& MomentCurvatureSolutionImpl::GetIncrementalStrainPlane(IndexType idx) const
      {
         PRECONDITION(idx < m_CurvaturePoints.size());
         return m_CurvaturePoints[idx].Solution->GetIncrementalStrainPlane();
      }

      const std::unique_ptr<MomentCapacitySolution>& MomentCurvatureSolutionImpl::GetCapacitySolution(IndexType idx) const
      {
         PRECONDITION(idx < m_CurvaturePoints.size());
         return m_CurvaturePoints[idx].Solution;
      }

      IndexType MomentCurvatureSolutionImpl::GetPointCount() const
      {
         return m_CurvaturePoints.size();
      }
   };
};

////////////////////////////////////////////////
MomentCurvatureSolution::MomentCurvatureSolution()
{
   m_pImpl = std::make_unique<MomentCurvatureSolutionImpl>();
}

MomentCurvatureSolution::~MomentCurvatureSolution() = default;

void MomentCurvatureSolution::AddPoint(Float64 M, Float64 k, std::unique_ptr<MomentCapacitySolution>&& capacitySolution)
{
   m_pImpl->AddPoint(M, k, std::move(capacitySolution));
}

Float64 MomentCurvatureSolution::GetMaxMoment() const
{
   return m_pImpl->GetMaxMoment();
}

Float64 MomentCurvatureSolution::GetMaxMomentCurvature() const
{
   return m_pImpl->GetMaxMomentCurvature();
}

void MomentCurvatureSolution::GetPeakCapacity(Float64& Mmax, Float64& k)
{
   m_pImpl->GetPeakCapacity(Mmax, k);
}

Float64 MomentCurvatureSolution::GetMoment(IndexType idx) const
{
   return m_pImpl->GetMoment(idx);
}

Float64 MomentCurvatureSolution::GetCurvature(IndexType idx) const
{
   return m_pImpl->GetCurvature(idx);
}

const WBFL::Geometry::Plane3d& MomentCurvatureSolution::GetIncrementalStrainPlane(IndexType idx) const
{
   return m_pImpl->GetIncrementalStrainPlane(idx);
}

const std::unique_ptr<MomentCapacitySolution>& MomentCurvatureSolution::GetCapacitySolution(IndexType idx) const
{
   return m_pImpl->GetCapacitySolution(idx);
}

IndexType MomentCurvatureSolution::GetPointCount() const
{
   return m_pImpl->GetPointCount();
}


#if defined _UNITTEST
bool MomentCurvatureSolution::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("MomentCurvatureSolution");

   //TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for MomentCurvatureSolution");
   // not much to test here

   TESTME_EPILOG("MomentCurvatureSolution");
}
#endif // _UNITTEST
