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

#include <RCSection\RCSectionLib.h>
#include <RCSection\MomentCapacitySolution.h>

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
      class MomentCapacitySolutionImpl
      {
      public:
         MomentCapacitySolutionImpl() = default;
         MomentCapacitySolutionImpl(const MomentCapacitySolutionImpl& other) = default;
         ~MomentCapacitySolutionImpl() = default;

         MomentCapacitySolutionImpl& operator=(const MomentCapacitySolutionImpl& other) = default;

         void InitSolution(
            Float64 fz,
            Float64 mx,
            Float64 my,
            const WBFL::Geometry::Plane3d& strainPlane,
            const WBFL::Geometry::Line2d& neutralAxis,
            const WBFL::Geometry::Point2d& cgC,
            Float64 C,
            const WBFL::Geometry::Point2d& cgT,
            Float64 T,
            std::unique_ptr<GeneralSectionSolution>&& solution 
         );

         Float64 GetFz() const;
         Float64 GetMx() const;
         Float64 GetMy() const;
         const WBFL::Geometry::Plane3d& GetStrainPlane() const;
         const WBFL::Geometry::Line2d& GetNeutralAxis() const;
         Float64 GetNeutralAxisDirection() const;
         Float64 GetCompressionResultant() const;
         Float64 GetTensionResultant() const;
         const WBFL::Geometry::Point2d& GetCompressionResultantLocation() const;
         const WBFL::Geometry::Point2d& GetTensionResultantLocation() const;
         const std::unique_ptr<GeneralSectionSolution>& GetGeneralSectionSolution() const;

      private:
         Float64 m_Fz{0.0};
         Float64 m_Mx{ 0.0 };
         Float64 m_My{ 0.0 };
         Float64 m_C{ 0.0 };
         Float64 m_T{ 0.0 };
         WBFL::Geometry::Plane3d m_StrainPlane;
         WBFL::Geometry::Line2d m_NeutralAxis;
         WBFL::Geometry::Point2d m_cgC;
         WBFL::Geometry::Point2d m_cgT;
         std::unique_ptr<GeneralSectionSolution> m_Solution;
      };


      void MomentCapacitySolutionImpl::InitSolution(
         Float64 fz,
         Float64 mx,
         Float64 my,
         const WBFL::Geometry::Plane3d& strainPlane,
         const WBFL::Geometry::Line2d& neutralAxis,
         const WBFL::Geometry::Point2d& cgC,
         Float64 C,
         const WBFL::Geometry::Point2d& cgT,
         Float64 T,
         std::unique_ptr<GeneralSectionSolution>&& solution
      )
      {
         m_Fz = fz;
         m_Mx = mx;
         m_My = my;
         m_StrainPlane = strainPlane;
         m_NeutralAxis = neutralAxis;
         m_cgC = cgC;
         m_C = C;
         m_cgT = cgT;
         m_T = T;
         m_Solution = std::move(solution);
      }

      Float64 MomentCapacitySolutionImpl::GetFz() const
      {
         return m_Fz;
      }

      Float64 MomentCapacitySolutionImpl::GetMx() const
      {
         return m_Mx;
      }

      Float64 MomentCapacitySolutionImpl::GetMy() const
      {
         return m_My;
      }

      const WBFL::Geometry::Plane3d& MomentCapacitySolutionImpl::GetStrainPlane() const
      {
         return m_StrainPlane;
      }

      const WBFL::Geometry::Line2d& MomentCapacitySolutionImpl::GetNeutralAxis() const
      {
         return m_NeutralAxis;
      }

      Float64 MomentCapacitySolutionImpl::GetNeutralAxisDirection() const
      {
         WBFL::Geometry::Point2d p;
         WBFL::Geometry::Vector2d d;
         m_NeutralAxis.GetExplicit(&p, &d);
         return d.GetDirection();
      }

      Float64 MomentCapacitySolutionImpl::GetCompressionResultant() const
      {
         return m_C;
      }

      Float64 MomentCapacitySolutionImpl::GetTensionResultant() const
      {
         return m_T;
      }

      const WBFL::Geometry::Point2d& MomentCapacitySolutionImpl::GetCompressionResultantLocation() const
      {
         return m_cgC;
      }

      const WBFL::Geometry::Point2d& MomentCapacitySolutionImpl::GetTensionResultantLocation() const
      {
         return m_cgT;
      }

      const std::unique_ptr<GeneralSectionSolution>& MomentCapacitySolutionImpl::GetGeneralSectionSolution() const
      {
         return m_Solution;
      }
   };
};

////////////////////////////////////////////////
MomentCapacitySolution::MomentCapacitySolution()
{
   m_pImpl = std::make_unique<MomentCapacitySolutionImpl>();
}

MomentCapacitySolution::~MomentCapacitySolution() = default;

void MomentCapacitySolution::InitSolution(
   Float64 fz,
   Float64 mx,
   Float64 my,
   const WBFL::Geometry::Plane3d& strainPlane,
   const WBFL::Geometry::Line2d& neutralAxis,
   const WBFL::Geometry::Point2d& cgC,
   Float64 C,
   const WBFL::Geometry::Point2d& cgT,
   Float64 T,
   std::unique_ptr<GeneralSectionSolution>&& solution
)
{
   m_pImpl->InitSolution(fz, mx, my, strainPlane, neutralAxis, cgC, C, cgT, T, std::move(solution));
}

Float64 MomentCapacitySolution::GetFz() const
{
   return m_pImpl->GetFz();
}

Float64 MomentCapacitySolution::GetMx() const
{
   return m_pImpl->GetMx();
}

Float64 MomentCapacitySolution::GetMy() const
{
   return m_pImpl->GetMy();
}

const WBFL::Geometry::Plane3d& MomentCapacitySolution::GetStrainPlane() const
{
   return m_pImpl->GetStrainPlane();
}

const WBFL::Geometry::Line2d& MomentCapacitySolution::GetNeutralAxis() const
{
   return m_pImpl->GetNeutralAxis();
}

Float64 MomentCapacitySolution::GetNeutralAxisDirection() const
{
   return m_pImpl->GetNeutralAxisDirection();
}

Float64 MomentCapacitySolution::GetCompressionResultant() const
{
   return m_pImpl->GetCompressionResultant();
}

Float64 MomentCapacitySolution::GetTensionResultant() const
{
   return m_pImpl->GetTensionResultant();
}

const WBFL::Geometry::Point2d& MomentCapacitySolution::GetCompressionResultantLocation() const
{
   return m_pImpl->GetCompressionResultantLocation();
}

const WBFL::Geometry::Point2d& MomentCapacitySolution::GetTensionResultantLocation() const
{
   return m_pImpl->GetTensionResultantLocation();
}

const std::unique_ptr<GeneralSectionSolution>& MomentCapacitySolution::GetGeneralSectionSolution() const
{
   return m_pImpl->GetGeneralSectionSolution();
}

#if defined _UNITTEST
bool MomentCapacitySolution::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("MomentCapacitySolution");

   //TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for MomentCapacitySolution");
   // not much to test here

   TESTME_EPILOG("MomentCapacitySolution");
}
#endif // _UNITTEST
