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

#include <RCSection\RCSectionLib.h>
#include <RCSection\GeneralSectionSolution.h>

using namespace WBFL::RCSection;

namespace WBFL
{
   namespace RCSection
   {
      class GeneralSectionSolutionImpl
      {
      public:
         GeneralSectionSolutionImpl() = default;
         GeneralSectionSolutionImpl(const GeneralSectionSolutionImpl& other) = default;
         ~GeneralSectionSolutionImpl() = default;

         GeneralSectionSolutionImpl& operator=(const GeneralSectionSolutionImpl& other) = default;

         void InitSolution(
            Float64 fz,
            Float64 mx,
            Float64 my,
            const WBFL::Geometry::Line2d& neutralAxis,
            const WBFL::Geometry::Point2d& cgC,
            Float64 C,
            const WBFL::Geometry::Point2d& cgT,
            Float64 T,
            std::vector<std::unique_ptr<GeneralSectionSlice>>&& vSlices,
            bool bExceededStrainLimits
         );

         Float64 GetFz() const;
         Float64 GetMx() const;
         Float64 GetMy() const;
         Float64 GetM() const;
         const WBFL::Geometry::Line2d& GetNeutralAxis() const;
         Float64 GetNeutralAxisDirection() const;
         Float64 GetCompressionResultant() const;
         Float64 GetTensionResultant() const;
         const WBFL::Geometry::Point2d& GetCompressionResultantLocation() const;
         const WBFL::Geometry::Point2d& GetTensionResultantLocation() const;
         Float64 GetMomentArm() const;
         IndexType GetSliceCount() const;
         const GeneralSectionSlice& GetSlice(IndexType sliceIdx) const;
         std::vector<const GeneralSectionSlice*> FindSlices(IndexType shapeIdx) const;
         bool ExceededStrainLimits() const;

      private:
         Float64 m_Fz{0.0};
         Float64 m_Mx{ 0.0 };
         Float64 m_My{ 0.0 };
         Float64 m_C{ 0.0 };
         Float64 m_T{ 0.0 };
         WBFL::Geometry::Line2d m_NeutralAxis;
         WBFL::Geometry::Point2d m_cgC;
         WBFL::Geometry::Point2d m_cgT;
         std::vector<std::unique_ptr<GeneralSectionSlice>> m_vSlices;
         bool m_bExceededStrainLimits{ false };
      };


      void GeneralSectionSolutionImpl::InitSolution(
         Float64 fz,
         Float64 mx,
         Float64 my,
         const WBFL::Geometry::Line2d& neutralAxis,
         const WBFL::Geometry::Point2d& cgC,
         Float64 C,
         const WBFL::Geometry::Point2d& cgT,
         Float64 T,
         std::vector<std::unique_ptr<GeneralSectionSlice>>&& vSlices,
         bool bExceededStrainLimits
      )
      {
         m_Fz = fz;
         m_Mx = mx;
         m_My = my;
         m_NeutralAxis = neutralAxis;
         m_cgC = cgC;
         m_C = C;
         m_cgT = cgT;
         m_T = T;
         m_vSlices = std::move(vSlices);
         m_bExceededStrainLimits = bExceededStrainLimits;
      }

      Float64 GeneralSectionSolutionImpl::GetFz() const
      {
         return m_Fz;
      }

      Float64 GeneralSectionSolutionImpl::GetMx() const
      {
         return m_Mx;
      }

      Float64 GeneralSectionSolutionImpl::GetMy() const
      {
         return m_My;
      }

      Float64 GeneralSectionSolutionImpl::GetM() const
      {
         return sqrt(m_Mx * m_Mx + m_My * m_My);
      }

      const WBFL::Geometry::Line2d& GeneralSectionSolutionImpl::GetNeutralAxis() const
      {
         return m_NeutralAxis;
      }

      Float64 GeneralSectionSolutionImpl::GetNeutralAxisDirection() const
      {
         auto [p,d] = m_NeutralAxis.GetExplicit();
         return d.GetDirection();
      }

      Float64 GeneralSectionSolutionImpl::GetCompressionResultant() const
      {
         return m_C;
      }

      Float64 GeneralSectionSolutionImpl::GetTensionResultant() const
      {
         return m_T;
      }

      const WBFL::Geometry::Point2d& GeneralSectionSolutionImpl::GetCompressionResultantLocation() const
      {
         return m_cgC;
      }

      const WBFL::Geometry::Point2d& GeneralSectionSolutionImpl::GetTensionResultantLocation() const
      {
         return m_cgT;
      }

      Float64 GeneralSectionSolutionImpl::GetMomentArm() const
      {
         return m_cgC.Distance(m_cgT);
      }

      IndexType GeneralSectionSolutionImpl::GetSliceCount() const
      {
         return m_vSlices.size();
      }

      const GeneralSectionSlice& GeneralSectionSolutionImpl::GetSlice(IndexType sliceIdx) const
      {
         PRECONDITION(sliceIdx < m_vSlices.size());
         return *m_vSlices[sliceIdx];
      }

      std::vector<const GeneralSectionSlice*> GeneralSectionSolutionImpl::FindSlices(IndexType shapeIdx) const
      {
         std::vector<const GeneralSectionSlice*> vSlices;
         for (const auto& slice : m_vSlices)
         {
            IndexType thisShapeIdx = slice->GetShapeIndex();
            if (thisShapeIdx == shapeIdx)
            {
               vSlices.emplace_back(slice.get());
            }
         }
         return vSlices;
      }

      bool GeneralSectionSolutionImpl::ExceededStrainLimits() const
      {
         return m_bExceededStrainLimits;
      }
   };
};

////////////////////////////////////////////////
GeneralSectionSolution::GeneralSectionSolution()
{
   m_pImpl = std::make_unique<GeneralSectionSolutionImpl>();
}

GeneralSectionSolution::GeneralSectionSolution(const GeneralSectionSolution& other)
{
   m_pImpl = std::make_unique<GeneralSectionSolutionImpl>();
   *this = other;
}

GeneralSectionSolution& GeneralSectionSolution::operator=(const GeneralSectionSolution& other)
{
   std::vector<std::unique_ptr<GeneralSectionSlice>> vSlices;
   auto nSlices = other.GetSliceCount();
   for (auto idx = 0; idx < nSlices; idx++)
   {
      const auto& other_slice = other.GetSlice(idx);
      auto slice(std::make_unique<GeneralSectionSlice>(other_slice));
      vSlices.emplace_back(std::move(slice));
   }

   m_pImpl->InitSolution(other.GetFz(), other.GetMx(), other.GetMy(), other.GetNeutralAxis(), 
      other.GetCompressionResultantLocation(), other.GetCompressionResultant(), 
      other.GetTensionResultantLocation(), other.GetTensionResultant(),
      std::move(vSlices), 
      other.ExceededStrainLimits());

   return *this;
}

GeneralSectionSolution::~GeneralSectionSolution() = default;

void GeneralSectionSolution::InitSolution(
   Float64 fz,
   Float64 mx,
   Float64 my,
   const WBFL::Geometry::Line2d& neutralAxis,
   const WBFL::Geometry::Point2d& cgC,
   Float64 C,
   const WBFL::Geometry::Point2d& cgT,
   Float64 T,
   std::vector<std::unique_ptr<GeneralSectionSlice>>&& vSlices,
   bool bExceededStrainLimits
)
{
   m_pImpl->InitSolution(fz, mx, my, neutralAxis, cgC, C, cgT, T, std::move(vSlices), bExceededStrainLimits);
}

Float64 GeneralSectionSolution::GetFz() const
{
   return m_pImpl->GetFz();
}

Float64 GeneralSectionSolution::GetMx() const
{
   return m_pImpl->GetMx();
}

Float64 GeneralSectionSolution::GetMy() const
{
   return m_pImpl->GetMy();
}

Float64 GeneralSectionSolution::GetM() const
{
   return m_pImpl->GetM();
}

const WBFL::Geometry::Line2d& GeneralSectionSolution::GetNeutralAxis() const
{
   return m_pImpl->GetNeutralAxis();
}

Float64 GeneralSectionSolution::GetNeutralAxisDirection() const
{
   return m_pImpl->GetNeutralAxisDirection();
}

Float64 GeneralSectionSolution::GetCompressionResultant() const
{
   return m_pImpl->GetCompressionResultant();
}

Float64 GeneralSectionSolution::GetTensionResultant() const
{
   return m_pImpl->GetTensionResultant();
}

const WBFL::Geometry::Point2d& GeneralSectionSolution::GetCompressionResultantLocation() const
{
   return m_pImpl->GetCompressionResultantLocation();
}

const WBFL::Geometry::Point2d& GeneralSectionSolution::GetTensionResultantLocation() const
{
   return m_pImpl->GetTensionResultantLocation();
}

Float64 GeneralSectionSolution::GetMomentArm() const
{
   return m_pImpl->GetMomentArm();
}

IndexType GeneralSectionSolution::GetSliceCount() const
{
   return m_pImpl->GetSliceCount();
}

const GeneralSectionSlice& GeneralSectionSolution::GetSlice(IndexType sliceIdx) const
{
   return m_pImpl->GetSlice(sliceIdx);
}

std::vector<const GeneralSectionSlice*> GeneralSectionSolution::FindSlices(IndexType shapeIdx) const
{
   return m_pImpl->FindSlices(shapeIdx);
}

bool GeneralSectionSolution::ExceededStrainLimits() const
{
   return m_pImpl->ExceededStrainLimits();
}
