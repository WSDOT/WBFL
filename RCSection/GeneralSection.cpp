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
#include <RCSection\GeneralSection.h>

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
      class GeneralSectionImpl
      {
      public:
         GeneralSectionImpl() = default;
         GeneralSectionImpl(const GeneralSectionImpl&) = default;
         ~GeneralSectionImpl() = default;

         GeneralSectionImpl& operator=(const GeneralSectionImpl&) = default;

         void AddShape(
            LPCTSTR name,
            std::unique_ptr<WBFL::Geometry::Shape>&& shape,
            const std::shared_ptr<const WBFL::Materials::StressStrainModel>& fgMaterial,
            const std::shared_ptr<const WBFL::Materials::StressStrainModel>& bgMaterial,
            const std::shared_ptr<const WBFL::Geometry::Plane3d>& initialStrain,
            Float64 Le,
            bool bIsPrimaryShape = false
         );

         void AddShape(
            LPCTSTR name,
            const WBFL::Geometry::Shape& shape,
            const std::shared_ptr<const WBFL::Materials::StressStrainModel>& fgMaterial,
            const std::shared_ptr<const WBFL::Materials::StressStrainModel>& bgMaterial,
            const std::shared_ptr<const WBFL::Geometry::Plane3d>& initialStrain,
            Float64 Le,
            bool bIsPrimaryShape = false
         );

         IndexType GetShapeCount() const;

         void SetPrimaryShapeIndex(IndexType idx);
         IndexType GetPrimaryShapeIndex() const;

         void SetName(IndexType shapeIdx, LPCTSTR name);
         void SetName(IndexType shapeIdx, const std::_tstring& name);
         const std::_tstring& GetName(IndexType shapeIdx) const;

         void SetShape(IndexType shapeIdx, std::unique_ptr < WBFL::Geometry::Shape>&& shape);
         const std::unique_ptr<WBFL::Geometry::Shape>& GetShape(IndexType shapeIdx) const;

         void SetForegroundMaterial(IndexType shapeIdx, const std::shared_ptr<const WBFL::Materials::StressStrainModel>& fgMaterial);
         const std::shared_ptr<const WBFL::Materials::StressStrainModel>& GetForegroundMaterial(IndexType shapeIdx) const;

         void SetBackgroundMaterial(IndexType shapeIdx, const std::shared_ptr<const WBFL::Materials::StressStrainModel>& bgMaterial);
         const std::shared_ptr<const WBFL::Materials::StressStrainModel>& GetBackgroundMaterial(IndexType shapeIdx) const;

         void SetInitialStrain(IndexType shapeIdx, const std::shared_ptr<const WBFL::Geometry::Plane3d>& initialStrain);
         const std::shared_ptr<const WBFL::Geometry::Plane3d>& GetInitialStrain(IndexType shapeIdx) const;

         void SetElongationLength(IndexType shapeIdx, Float64 Le);
         Float64 GetElongationLength(IndexType shapeIdx) const;

      private:
         struct SectionItem
         {
            std::_tstring m_Name;
            std::unique_ptr<WBFL::Geometry::Shape> m_Shape;
            std::shared_ptr<const WBFL::Materials::StressStrainModel> m_FgMaterial;
            std::shared_ptr<const WBFL::Materials::StressStrainModel> m_BgMaterial;
            std::shared_ptr<const WBFL::Geometry::Plane3d> m_InitialStrain;
            Float64 m_Le{ 1.0 };

            SectionItem(
               LPCTSTR name, 
               std::unique_ptr<WBFL::Geometry::Shape>&& shape, 
               const std::shared_ptr<const WBFL::Materials::StressStrainModel>& fg,
               const std::shared_ptr<const WBFL::Materials::StressStrainModel>& bg, 
               const std::shared_ptr<const WBFL::Geometry::Plane3d>& initialStrain, Float64 le) : 
               m_Name(name), m_Shape(std::move(shape)), m_FgMaterial(fg), m_BgMaterial(bg), m_InitialStrain(initialStrain),m_Le(le)
            {}
         };

         std::vector<SectionItem> m_vItems;
         IndexType m_PrimaryShapeIdx{ INVALID_INDEX };
      };

      void GeneralSectionImpl::AddShape(
         LPCTSTR name,
         std::unique_ptr<WBFL::Geometry::Shape>&& shape,
         const std::shared_ptr<const WBFL::Materials::StressStrainModel>& fgMaterial,
         const std::shared_ptr<const WBFL::Materials::StressStrainModel>& bgMaterial,
         const std::shared_ptr<const WBFL::Geometry::Plane3d>& initialStrain,
         Float64 Le,
         bool bIsPrimaryShape
      )
      {
         m_vItems.emplace_back(name, std::move(shape), fgMaterial, bgMaterial, initialStrain, Le);
         if (bIsPrimaryShape)
         {
            m_PrimaryShapeIdx = m_vItems.size() - 1;
         }
      }


      void GeneralSectionImpl::AddShape(
         LPCTSTR name,
         const WBFL::Geometry::Shape& shape,
         const std::shared_ptr<const WBFL::Materials::StressStrainModel>& fgMaterial,
         const std::shared_ptr<const WBFL::Materials::StressStrainModel>& bgMaterial,
         const std::shared_ptr<const WBFL::Geometry::Plane3d>& initialStrain,
         Float64 Le,
         bool bIsPrimaryShape
      )
      {
         AddShape(name, shape.CreateClone(), fgMaterial, bgMaterial, initialStrain, Le, bIsPrimaryShape);
      }

      IndexType GeneralSectionImpl::GetShapeCount() const
      {
         return m_vItems.size();
      }

      void GeneralSectionImpl::SetPrimaryShapeIndex(IndexType idx)
      {
         PRECONDITION(idx < m_vItems.size());
         m_PrimaryShapeIdx = idx;
      }

      IndexType GeneralSectionImpl::GetPrimaryShapeIndex() const
      {
         return m_PrimaryShapeIdx;
      }

      void GeneralSectionImpl::SetName(IndexType shapeIdx, LPCTSTR name)
      {
         PRECONDITION(shapeIdx < m_vItems.size());
         m_vItems[shapeIdx].m_Name = name;
      }

      void GeneralSectionImpl::SetName(IndexType shapeIdx, const std::_tstring& name)
      {
         PRECONDITION(shapeIdx < m_vItems.size());
         m_vItems[shapeIdx].m_Name = name;
      }

      const std::_tstring& GeneralSectionImpl::GetName(IndexType shapeIdx) const
      {
         PRECONDITION(shapeIdx < m_vItems.size());
         return m_vItems[shapeIdx].m_Name;
      }

      void GeneralSectionImpl::SetShape(IndexType shapeIdx, std::unique_ptr<WBFL::Geometry::Shape>&& shape)
      {
         PRECONDITION(shapeIdx < m_vItems.size());
         m_vItems[shapeIdx].m_Shape = std::move(shape);
      }

      const std::unique_ptr<WBFL::Geometry::Shape>& GeneralSectionImpl::GetShape(IndexType shapeIdx) const
      {
         PRECONDITION(shapeIdx < m_vItems.size());
         return m_vItems[shapeIdx].m_Shape;
      }

      void GeneralSectionImpl::SetForegroundMaterial(IndexType shapeIdx, const std::shared_ptr<const WBFL::Materials::StressStrainModel>& fgMaterial)
      {
         PRECONDITION(shapeIdx < m_vItems.size());
         m_vItems[shapeIdx].m_FgMaterial = fgMaterial;
      }

      const std::shared_ptr<const WBFL::Materials::StressStrainModel>& GeneralSectionImpl::GetForegroundMaterial(IndexType shapeIdx) const
      {
         PRECONDITION(shapeIdx < m_vItems.size());
         return m_vItems[shapeIdx].m_FgMaterial;
      }

      void GeneralSectionImpl::SetBackgroundMaterial(IndexType shapeIdx, const std::shared_ptr<const WBFL::Materials::StressStrainModel>& bgMaterial)
      {
         PRECONDITION(shapeIdx < m_vItems.size());
         m_vItems[shapeIdx].m_BgMaterial = bgMaterial;
      }

      const std::shared_ptr<const WBFL::Materials::StressStrainModel>& GeneralSectionImpl::GetBackgroundMaterial(IndexType shapeIdx) const
      {
         PRECONDITION(shapeIdx < m_vItems.size());
         return m_vItems[shapeIdx].m_BgMaterial;
      }

      void GeneralSectionImpl::SetInitialStrain(IndexType shapeIdx, const std::shared_ptr<const WBFL::Geometry::Plane3d>& initialStrain)
      {
         PRECONDITION(shapeIdx < m_vItems.size());
         m_vItems[shapeIdx].m_InitialStrain = initialStrain;
      }

      const std::shared_ptr<const WBFL::Geometry::Plane3d>& GeneralSectionImpl::GetInitialStrain(IndexType shapeIdx) const
      {
         PRECONDITION(shapeIdx < m_vItems.size());
         return m_vItems[shapeIdx].m_InitialStrain;
      }

      void GeneralSectionImpl::SetElongationLength(IndexType shapeIdx, Float64 Le)
      {
         PRECONDITION(shapeIdx < m_vItems.size());
         m_vItems[shapeIdx].m_Le = Le;
      }

      Float64 GeneralSectionImpl::GetElongationLength(IndexType shapeIdx) const
      {
         PRECONDITION(shapeIdx < m_vItems.size());
         return m_vItems[shapeIdx].m_Le;
      }
   };
};

////////////////////////////////////////////////
GeneralSection::GeneralSection()
{
   m_pImpl = std::make_unique<GeneralSectionImpl>();
}

GeneralSection::~GeneralSection() = default;

void GeneralSection::AddShape(
   LPCTSTR name,
   std::unique_ptr<WBFL::Geometry::Shape>&& shape,
   const std::shared_ptr<const WBFL::Materials::StressStrainModel>& fgMaterial,
   const std::shared_ptr<const WBFL::Materials::StressStrainModel>& bgMaterial,
   const std::shared_ptr<const WBFL::Geometry::Plane3d>& initialStrain,
   Float64 Le,
   bool bIsPrimaryShape
)
{
   m_pImpl->AddShape(name, std::move(shape), fgMaterial, bgMaterial, initialStrain, Le, bIsPrimaryShape);
}

void GeneralSection::AddShape(
   LPCTSTR name,
   const WBFL::Geometry::Shape& shape,
   const std::shared_ptr<const WBFL::Materials::StressStrainModel>& fgMaterial,
   const std::shared_ptr<const WBFL::Materials::StressStrainModel>& bgMaterial,
   const std::shared_ptr<const WBFL::Geometry::Plane3d>& initialStrain,
   Float64 Le,
   bool bIsPrimaryShape
)
{
   m_pImpl->AddShape(name, std::move(shape), fgMaterial, bgMaterial, initialStrain, Le, bIsPrimaryShape);
}

IndexType GeneralSection::GetShapeCount() const
{
   return m_pImpl->GetShapeCount();
}

void GeneralSection::SetPrimaryShapeIndex(IndexType idx)
{
   m_pImpl->SetPrimaryShapeIndex(idx);
}

IndexType GeneralSection::GetPrimaryShapeIndex() const
{
   return m_pImpl->GetPrimaryShapeIndex();
}

void GeneralSection::SetName(IndexType shapeIdx, LPCTSTR name)
{
   m_pImpl->SetName(shapeIdx, name);
}

void GeneralSection::SetName(IndexType shapeIdx, const std::_tstring& name)
{
   m_pImpl->SetName(shapeIdx, name);
}

const std::_tstring& GeneralSection::GetName(IndexType shapeIdx) const
{
   return m_pImpl->GetName(shapeIdx);
}

void GeneralSection::SetShape(IndexType shapeIdx, std::unique_ptr<WBFL::Geometry::Shape>&& shape)
{
   m_pImpl->SetShape(shapeIdx, std::move(shape));
}

const std::unique_ptr<WBFL::Geometry::Shape>& GeneralSection::GetShape(IndexType shapeIdx) const
{
   return m_pImpl->GetShape(shapeIdx);
}

void GeneralSection::SetForegroundMaterial(IndexType shapeIdx, const std::shared_ptr<const WBFL::Materials::StressStrainModel>& fgMaterial)
{
   m_pImpl->SetForegroundMaterial(shapeIdx, fgMaterial);
}

const std::shared_ptr<const WBFL::Materials::StressStrainModel>& GeneralSection::GetForegroundMaterial(IndexType shapeIdx) const
{
   return m_pImpl->GetForegroundMaterial(shapeIdx);
}

void GeneralSection::SetBackgroundMaterial(IndexType shapeIdx, const std::shared_ptr<const WBFL::Materials::StressStrainModel>& bgMaterial)
{
   m_pImpl->SetBackgroundMaterial(shapeIdx, bgMaterial);
}

const std::shared_ptr<const WBFL::Materials::StressStrainModel>& GeneralSection::GetBackgroundMaterial(IndexType shapeIdx) const
{
   return m_pImpl->GetBackgroundMaterial(shapeIdx);
}

void GeneralSection::SetInitialStrain(IndexType shapeIdx, const std::shared_ptr<const WBFL::Geometry::Plane3d>& initialStrain)
{
   m_pImpl->SetInitialStrain(shapeIdx, initialStrain);
}

const std::shared_ptr<const WBFL::Geometry::Plane3d>& GeneralSection::GetInitialStrain(IndexType shapeIdx) const
{
   return m_pImpl->GetInitialStrain(shapeIdx);
}

void GeneralSection::SetElongationLength(IndexType shapeIdx, Float64 Le)
{
   m_pImpl->SetElongationLength(shapeIdx, Le);
}

Float64 GeneralSection::GetElongationLength(IndexType shapeIdx) const
{
   return m_pImpl->GetElongationLength(shapeIdx);
}

#if defined _UNITTEST
#include <Units/Units.h>
#include <Materials/Materials.h>
#include <GeomModel/GeomModel.h>
bool GeneralSection::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("GeneralSection");

   // work in KSI units
   WBFL::Units::AutoSystem as;
   WBFL::Units::System::SetSystemUnits(WBFL::Units::Measure::_12KSlug, WBFL::Units::Measure::Inch, WBFL::Units::Measure::Second, WBFL::Units::Measure::Fahrenheit, WBFL::Units::Measure::Degree);

   std::shared_ptr<GeneralSection> section(std::make_shared<GeneralSection>());

   // Materials

   // concrete
   std::shared_ptr<WBFL::Materials::UnconfinedConcreteModel> concrete(std::make_shared<WBFL::Materials::UnconfinedConcreteModel>(_T("Concrete"), 4.0));

   // rebar
   std::shared_ptr<WBFL::Materials::RebarModel> rebar(std::make_shared<WBFL::Materials::RebarModel>(_T("Rebar"), 60.0, 29000.0, 0.11));

   // Shapes

   // main beam
   WBFL::Geometry::Rectangle beam;
   beam.SetHeight(8 * 12);
   beam.SetWidth(4 * 12);

   // #6 rebar
   WBFL::Geometry::Circle bar1(WBFL::Geometry::Point2d(22, 46), 0.37424);
   WBFL::Geometry::Circle bar2(WBFL::Geometry::Point2d(-22, 46), 0.37424);
   WBFL::Geometry::Circle bar3(WBFL::Geometry::Point2d(-22, -46), 0.37424);
   WBFL::Geometry::Circle bar4(WBFL::Geometry::Point2d(22, -46), 0.37424);

   section->AddShape(_T("Beam"), beam, concrete, nullptr, nullptr, 1.0, true);
   section->AddShape(_T("Bar 1"), bar1, rebar, concrete, nullptr, 1.0);
   section->AddShape(_T("Bar 2"), bar2, rebar, concrete, nullptr, 1.0);
   section->AddShape(_T("Bar 3"), bar3, rebar, concrete, nullptr, 1.0);
   section->AddShape(_T("Bar 4"), bar4, rebar, concrete, nullptr, 1.0);

   TRY_TESTME(section->GetShapeCount() == 5);
   TRY_TESTME(section->GetName(3) == std::_tstring(_T("Bar 3")));

   TESTME_EPILOG("GeneralSection");
}
#endif // _UNITTEST
