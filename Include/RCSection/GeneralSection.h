///////////////////////////////////////////////////////////////////////
// RCSection - Reinforced concrete section analysis modeling
// Copyright © 1999-2025  Washington State Department of Transportation
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
#include <GeomModel/Shape.h>
#include <GeomModel/Plane3d.h>
#include <Materials/StressStrainModel.h>

namespace WBFL
{
   namespace RCSection
   {
      class GeneralSectionImpl;

      /// Abstract definition of a general cross section that can be analyzed by various "solver" classes
      class RCSCLASS IGeneralSection
      {
      public:
         IGeneralSection() = default;
         IGeneralSection(const IGeneralSection& other) = delete; // can't copy because of unique_ptr - also don't need copy semantics
         virtual ~IGeneralSection() = default;

         IGeneralSection& operator=(const IGeneralSection& other) = delete; // can't assign

         /// Number of shapes in the cross section
         virtual IndexType GetShapeCount() const = 0;

         /// Index of the primary shape. 
         /// The incremental strain plane from moment capacity analysis is added to the inital strain plane of the primary shape to get the final strain plane stored in the MomentCapacitySolution
         virtual IndexType GetPrimaryShapeIndex() const = 0;

         /// The shape of an element of the cross section
         virtual const WBFL::Geometry::Shape& GetShape(IndexType shapeIdx) const = 0;

         /// The foreground material.
         ///
         /// This material provides the stress-strain model for solid elements of the cross section such as concrete or steel.
         virtual const std::shared_ptr<const WBFL::Materials::StressStrainModel>& GetForegroundMaterial(IndexType shapeIdx) const = 0;

         /// The background material.
         ///
         /// This material provides the stress-strain model for voids in elements of the cross section such as holes or "negative" areas in a solid area representing holes where reinforcement is located.
         virtual const std::shared_ptr<const WBFL::Materials::StressStrainModel>& GetBackgroundMaterial(IndexType shapeIdx) const = 0;

         /// Initial state of strain of a shape
         virtual const std::shared_ptr<const WBFL::Geometry::Plane3d>& GetInitialStrain(IndexType shapeIdx) const = 0;

         /// Strain elongation length (typically 0.0 for strain compatibility with other materials in the section, but a finite length for unbonded elements such as post-tensioning tendons)
         virtual Float64 GetElongationLength(IndexType shapeIdx) const = 0;
      };

      /// An implementation of the IGeneralSection interface
      class RCSCLASS GeneralSection : public IGeneralSection
      {
      public:
         GeneralSection();
         GeneralSection(const GeneralSection& other) = delete; // can't copy because of unique_ptr - also don't need copy semantics
         ~GeneralSection();
         
         GeneralSection& operator=(const GeneralSection& other) = delete; // can't assign

         /// Adds a shape, it's constitutive models, and initial strain state to the section model
         ///
         /// A linear variation of the initial strain is assumed over the depth of the shape.
         /// Incremental strains due to imposed section curvature are divided by Le to get the net strain.
         void AddShape(
            LPCTSTR name, ///< Name that identifies the shape (eg Deck, Girder, Rebar, etc)
            std::unique_ptr<WBFL::Geometry::Shape>&& shape, ///< The shape of a component of the cross section
            const std::shared_ptr<const WBFL::Materials::StressStrainModel>& fgMaterial,   ///< The foreground material constitutive model
            const std::shared_ptr<const WBFL::Materials::StressStrainModel>& bgMaterial, ///< The background material constitutive model
            const std::shared_ptr<const WBFL::Geometry::Plane3d>& initialStrain, ///< Initial strain. This parameter can be set to Nothing (nullptr) if there is not initial strains
            Float64 Le,///< Strain elongation length (typically 1.0 for strain compatibility with other materials in the section, but a finite length for unbonded elements such as post-tensioning tendons)
            bool bIsPrimaryShape = false  ///< Indicates if this is the primary shape of the section. Initial strains of the primary shape are combined with the incremental solution strains to form the solution strain plane. The last shape to be designated as the primary shape will be considered the one and only primary shape
         );

         /// Adds a shape, it's constitutive models, and initial strain state to the section model
         ///
         /// A linear variation of the initial strain is assumed over the depth of the shape.
         /// Incremental strains due to imposed section curvature are divided by Le to get the net strain.
         void AddShape(
            LPCTSTR name, ///< Name that identifies the shape (eg Deck, Girder, Rebar, etc)
            const WBFL::Geometry::Shape& shape, ///< The shape of a component of the cross section. This shape is cloned
            const std::shared_ptr<const WBFL::Materials::StressStrainModel>& fgMaterial,   ///< The foreground material constitutive model
            const std::shared_ptr<const WBFL::Materials::StressStrainModel>& bgMaterial, ///< The background material constitutive model
            const std::shared_ptr<const WBFL::Geometry::Plane3d>& initialStrain, ///< Initial strain. This parameter can be set to Nothing (nullptr) if there is not initial strains
            Float64 Le,///< Strain elongation length (typically 1.0 for strain compatibility with other materials in the section, but a finite length for unbonded elements such as post-tensioning tendons)
            bool bIsPrimaryShape = false  ///< Indicates if this is the primary shape of the section. Initial strains of the primary shape are combined with the incremental solution strains to form the solution strain plane. The last shape to be designated as the primary shape will be considered the one and only primary shape
         );

         /// Number of shapes in the cross section
         virtual IndexType GetShapeCount() const override;

         /// Index of the primary shape
         void SetPrimaryShapeIndex(IndexType idx);
         virtual IndexType GetPrimaryShapeIndex() const override;

         /// Name of the shape
         void SetName(IndexType shapeIdx, LPCTSTR name);
         void SetName(IndexType shapeIdx, const std::_tstring& name);
         const std::_tstring& GetName(IndexType shapeIdx) const;

         /// The shape of an element of the cross section
         void SetShape(IndexType shapeIdx, std::unique_ptr<WBFL::Geometry::Shape>&& shape);
         virtual const WBFL::Geometry::Shape& GetShape(IndexType shapeIdx) const override;

         /// The foreground material.
         ///
         /// This material provides the stress-strain model for solid elements of the cross section such as concrete or steel.
         void SetForegroundMaterial(IndexType shapeIdx,const std::shared_ptr<const WBFL::Materials::StressStrainModel>& fgMaterial);
         virtual const std::shared_ptr<const WBFL::Materials::StressStrainModel>& GetForegroundMaterial(IndexType shapeIdx) const override;

         /// The background material.
         ///
         /// This material provides the stress-strain model for voids in elements of the cross section such as holes or "negative" areas in a solid area representing holes where reinforcement is located.
         void SetBackgroundMaterial(IndexType shapeIdx,const std::shared_ptr<const WBFL::Materials::StressStrainModel>& bgMaterial);
         virtual const std::shared_ptr<const WBFL::Materials::StressStrainModel>& GetBackgroundMaterial(IndexType shapeIdx) const override;

         /// Initial state of strain of a shape
         void SetInitialStrain(IndexType shapeIdx, const std::shared_ptr<const WBFL::Geometry::Plane3d>& initialStrain);
         virtual const std::shared_ptr<const WBFL::Geometry::Plane3d>& GetInitialStrain(IndexType shapeIdx) const override;

         /// Strain elongation length (typically 0.0 for strain compatibility with other materials in the section, but a finite length for unbonded elements such as post-tensioning tendons)
         void SetElongationLength(IndexType shapeIdx, Float64 Le);
         virtual Float64 GetElongationLength(IndexType shapeIdx) const override;

      private:
         std::unique_ptr<GeneralSectionImpl> m_pImpl;
      };
   };
};