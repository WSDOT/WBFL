///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
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

#include <GeomModel/GeomModelExp.h>
#include <GeomModel/Primitives.h>
#include <GeomModel/Line2d.h>

namespace WBFL
{
   namespace Geometry
   {
      class Shape;

      /// A SectionComponent groups together the shape, material 
      /// properties, and structural properties of a component in a Section.
      class GEOMMODELCLASS SectionComponent
      {
      public:
         enum class ComponentType 
         { 
            Structural, ///< Designations a component as structural. Structural components contribute to the elastic and mass properties of the Section
            Nonstructural ///< Designations a component as nonstructural. Nonstructural components contribute to mass, but not structural, properties of the Section
         };

         SectionComponent() = delete;

         SectionComponent(std::shared_ptr<Shape> shape, Float64 fgModE, Float64 fgDensity, Float64 bgModE, Float64 bgDensity, ComponentType componentType);

         SectionComponent(const SectionComponent& rOther) = default;
         SectionComponent& operator=(const SectionComponent& rOther) = default;

         ~SectionComponent() = default;

         /// @brief Sets the component shape.
         /// @param shape 
         void SetShape(std::shared_ptr<Shape> shape);

         /// @brief Returns the component shape.
         const Shape& GetShape() const;

         /// @brief Returns the component shape.
         Shape& GetShape();

         /// Sets the modulus of elasticity of the material.
         void SetForegroundModE(Float64 modE);

         /// Returns the modulus of elasticity of the material.
         Float64 GetForegroundModE() const;

         /// Sets the density of the material. Returns the old density.
         void SetForegroundDensity(Float64 density);

         /// Returns the density of the material.
         Float64 GetForegroundDensity() const;

         /// Sets the modulus of elasticity of the material.
         void SetBackgroundModE(Float64 modE);

         /// Returns the modulus of elasticity of the material.
         Float64 GetBackgroundModE() const;

         /// Sets the density of the material. Returns the old density.
         void SetBackgroundDensity(Float64 density);

         /// Returns the density of the material.
         Float64 GetBackgroundDensity() const;

         /// @brief Sets the component type as structural or nonstructural.
         /// @param componentType 
         void SetComponentType(ComponentType componentType);

         /// @brief Returns the component type
         ComponentType GetComponentType() const;

      private:
         std::shared_ptr<Shape> m_Shape;
         Float64    m_fgModE{ 1.0 };
         Float64    m_fgDensity{ 0.0 };
         Float64    m_bgModE{ 0.0 };
         Float64    m_bgDensity{ 0.0 };
         ComponentType m_ComponentType{ ComponentType::Structural };
      };
   }; // Geometry
}; // WBFL
