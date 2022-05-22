///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
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

#ifndef INCLUDED_GEOMMODEL_SECTIONCOMPONENT_H_
#define INCLUDED_GEOMMODEL_SECTIONCOMPONENT_H_
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
   enum class ShapeType { 
      Solid, ///< The shape represents a solid element of the cross section
      Void ///< The shape represents a void element of the crosss section. Void shapes must be contained entirely within solid shapes.
   };

   enum class ComponentType 
   { 
      Structural, ///< Designations a component as structural. Structural components contribute to the elastic and mass properties of the Section
      Nonstructural ///< Designations a component as notstructural. Nonstructural componenets contribute to mass, but not structural, properties of the Section
   };

   SectionComponent() = delete;

   SectionComponent(const Shape& shape,Float64 fgModE, Float64 fgDensity, Float64 bgModE, Float64 bgDensity,ComponentType componentType);
   SectionComponent(std::unique_ptr<Shape>&& shape, Float64 fgModE, Float64 fgDensity, Float64 bgModE, Float64 bgDensity, ComponentType componentType);

   SectionComponent(const SectionComponent& rOther);
   SectionComponent& operator=(const SectionComponent& rOther);

   ~SectionComponent();

   std::unique_ptr<SectionComponent> CreateClone() const;

   void SetShape(const Shape& shape);
   void SetShape(std::unique_ptr<Shape>&& shape);
   const Shape& GetShape() const;
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

   void SetComponentType(ComponentType componentType);
   ComponentType GetComponentType() const;


#if defined _DEBUG
   virtual bool AssertValid() const;
   virtual void Dump(WBFL::Debug::LogContext& os) const;
#endif // _DEBUG

#if defined _UNITTEST
   static bool TestMe(WBFL::Debug::Log& rlog);
#endif // _UNITTEST

private:
   std::unique_ptr<Shape> m_Shape;
   Float64    m_fgModE{ 1.0 };
   Float64    m_fgDensity{ 0.0 };
   Float64    m_bgModE{ 0.0 };
   Float64    m_bgDensity{ 0.0 };
   ComponentType m_ComponentType{ ComponentType::Structural };

   void Copy(const SectionComponent& other);
};

   }; // Geometry
}; // WBFL


#endif // INCLUDED_GEOMMODEL_SECTIONCOMPONENT_H_
