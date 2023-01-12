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
#include <RCSection\MomentCapacitySolution.h>
#include <GeomModel/GeomOp2d.h>

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
            const WBFL::Geometry::Plane3d& incrementalStrainPlane,
            const WBFL::Geometry::Point2d& pntC,
            const WBFL::Geometry::Point2d& cgC,
            Float64 C,
            const WBFL::Geometry::Point2d& pntT,
            const WBFL::Geometry::Point2d& cgT,
            Float64 T,
            Float64 k,
            std::unique_ptr<GeneralSectionSolution>&& solution 
         );

         Float64 GetFz() const;
         Float64 GetMx() const;
         Float64 GetMy() const;
         const WBFL::Geometry::Plane3d& GetIncrementalStrainPlane() const;
         const WBFL::Geometry::Line2d& GetNeutralAxis() const;
         Float64 GetNeutralAxisDirection() const;
         Float64 GetDepthToNeutralAxis() const;
         Float64 GetCompressionResultant() const;
         Float64 GetTensionResultant() const;
         const WBFL::Geometry::Point2d& GetCompressionResultantLocation() const;
         const WBFL::Geometry::Point2d& GetTensionResultantLocation() const;
         const WBFL::Geometry::Point2d& GetExtremeCompressionPoint() const;
         const WBFL::Geometry::Point2d& GetExtremeTensionPoint() const;
         Float64 GetDepthToCompressionResultant() const;
         Float64 GetDepthToTensionResultant() const;
         Float64 GetMomentArm() const;
         Float64 GetCurvature() const;
         const std::unique_ptr<GeneralSectionSolution>& GetGeneralSectionSolution() const;

      private:
         Float64 m_Fz{0.0};
         Float64 m_Mx{ 0.0 };
         Float64 m_My{ 0.0 };
         Float64 m_C{ 0.0 };
         Float64 m_T{ 0.0 };
         Float64 m_Curvature{ 0.0 };
         WBFL::Geometry::Plane3d m_IncrementalStrainPlane;
         WBFL::Geometry::Point2d m_cgC;
         WBFL::Geometry::Point2d m_cgT;
         WBFL::Geometry::Point2d m_ExtremeCompressionPoint;
         WBFL::Geometry::Point2d m_ExtremeTensionPoint;
         std::unique_ptr<GeneralSectionSolution> m_GeneralSolution;
      };


      void MomentCapacitySolutionImpl::InitSolution(
         Float64 fz,
         Float64 mx,
         Float64 my,
         const WBFL::Geometry::Plane3d& incrementalStrainPlane,
         const WBFL::Geometry::Point2d& pntC,
         const WBFL::Geometry::Point2d& cgC,
         Float64 C,
         const WBFL::Geometry::Point2d& pntT,
         const WBFL::Geometry::Point2d& cgT,
         Float64 T,
         Float64 k,
         std::unique_ptr<GeneralSectionSolution>&& solution
      )
      {
         m_Fz = fz;
         m_Mx = mx;
         m_My = my;
         m_IncrementalStrainPlane = incrementalStrainPlane;
         m_ExtremeCompressionPoint = pntC;
         m_cgC = cgC;
         m_C = C;
         m_ExtremeTensionPoint = pntT;
         m_cgT = cgT;
         m_T = T;
         m_Curvature = k;
         m_GeneralSolution = std::move(solution);
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

      const WBFL::Geometry::Plane3d& MomentCapacitySolutionImpl::GetIncrementalStrainPlane() const
      {
         return m_IncrementalStrainPlane;
      }

      const WBFL::Geometry::Line2d& MomentCapacitySolutionImpl::GetNeutralAxis() const
      {
         return m_GeneralSolution->GetNeutralAxis();
      }

      Float64 MomentCapacitySolutionImpl::GetNeutralAxisDirection() const
      {
         return m_GeneralSolution->GetNeutralAxisDirection();
      }

      Float64 MomentCapacitySolutionImpl::GetDepthToNeutralAxis() const
      {
         // Compute depth to neutral axis, c
         const auto& na = m_GeneralSolution->GetNeutralAxis();
         auto point_on_na = WBFL::Geometry::GeometricOperations::PointOnLineNearest(na, m_ExtremeCompressionPoint);
         auto c = point_on_na.Distance(m_ExtremeCompressionPoint);

         return c;
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

      const WBFL::Geometry::Point2d& MomentCapacitySolutionImpl::GetExtremeCompressionPoint() const
      {
         return m_ExtremeCompressionPoint;
      }

      const WBFL::Geometry::Point2d& MomentCapacitySolutionImpl::GetExtremeTensionPoint() const
      {
         return m_ExtremeTensionPoint;
      }

      Float64 MomentCapacitySolutionImpl::GetDepthToCompressionResultant() const
      {
         const auto& na = m_GeneralSolution->GetNeutralAxis();
         Float64 d1 = WBFL::Geometry::GeometricOperations::ShortestOffsetToPoint(na, m_ExtremeCompressionPoint);
         Float64 d2 = WBFL::Geometry::GeometricOperations::ShortestOffsetToPoint(na, m_cgC);
         return fabs(d1) - fabs(d2);
      }

      Float64 MomentCapacitySolutionImpl::GetDepthToTensionResultant() const
      {
         const auto& na = m_GeneralSolution->GetNeutralAxis();
         Float64 d1 = WBFL::Geometry::GeometricOperations::ShortestOffsetToPoint(na, m_ExtremeCompressionPoint);
         Float64 d2 = WBFL::Geometry::GeometricOperations::ShortestOffsetToPoint(na, m_cgT);
         return fabs(d1) + fabs(d2);
      }

      Float64 MomentCapacitySolutionImpl::GetMomentArm() const
      {
         return m_cgC.Distance(m_cgT);
      }

      Float64 MomentCapacitySolutionImpl::GetCurvature() const
      {
         return m_Curvature;
      }

      const std::unique_ptr<GeneralSectionSolution>& MomentCapacitySolutionImpl::GetGeneralSectionSolution() const
      {
         return m_GeneralSolution;
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
   const WBFL::Geometry::Plane3d& incrementalStrainPlane,
   const WBFL::Geometry::Point2d& pntC,
   const WBFL::Geometry::Point2d& cgC,
   Float64 C,
   const WBFL::Geometry::Point2d& pntT,
   const WBFL::Geometry::Point2d& cgT,
   Float64 T,
   Float64 k,
   std::unique_ptr<GeneralSectionSolution>&& solution
)
{
   m_pImpl->InitSolution(fz, mx, my, incrementalStrainPlane, pntC, cgC, C, pntT, cgT, T, k, std::move(solution));
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

const WBFL::Geometry::Plane3d& MomentCapacitySolution::GetIncrementalStrainPlane() const
{
   return m_pImpl->GetIncrementalStrainPlane();
}

const WBFL::Geometry::Line2d& MomentCapacitySolution::GetNeutralAxis() const
{
   return m_pImpl->GetNeutralAxis();
}

Float64 MomentCapacitySolution::GetNeutralAxisDirection() const
{
   return m_pImpl->GetNeutralAxisDirection();
}

Float64 MomentCapacitySolution::GetDepthToNeutralAxis() const
{
   return m_pImpl->GetDepthToNeutralAxis();
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

const WBFL::Geometry::Point2d& MomentCapacitySolution::GetExtremeCompressionPoint() const
{
   return m_pImpl->GetExtremeCompressionPoint();
}

const WBFL::Geometry::Point2d& MomentCapacitySolution::GetExtremeTensionPoint() const
{
   return m_pImpl->GetExtremeTensionPoint();
}

Float64 MomentCapacitySolution::GetDepthToCompressionResultant() const
{
   return m_pImpl->GetDepthToCompressionResultant();
}

Float64 MomentCapacitySolution::GetDepthToTensionResultant() const
{
   return m_pImpl->GetDepthToTensionResultant();
}

Float64 MomentCapacitySolution::GetMomentArm() const
{
   return m_pImpl->GetMomentArm();
}

Float64 MomentCapacitySolution::GetCurvature() const
{
   return m_pImpl->GetCurvature();
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
