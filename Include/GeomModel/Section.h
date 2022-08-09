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

#ifndef INCLUDED_GEOMMODEL_SECTION_H_
#define INCLUDED_GEOMMODEL_SECTION_H_
#pragma once

#include <GeomModel/GeomModelExp.h>
#include <GeomModel/SectionComponent.h>
#include <GeomModel/Primitives.h>
#include <GeomModel/Line2d.h>
#include <GeomModel/Shape.h>

namespace WBFL
{
   namespace Geometry
   {
      class ElasticProperties;
      class MassProperties;


      /// A section is a collection of components that make up a structural member. 
      /// Each component consists of a shape and its associated material
      /// properties.  A component can be designated as structural or
      /// non-structural.  Non-structural components do not contribute to the
      /// elastic or transformed properties of a section,  they do however
      /// contribute to the mass properties.
      class GEOMMODELCLASS Section
      {
      public:
         /// Defines the region of a rectangle that a shape should be clipped against.
         enum class ClipRegion{ In, Out };

         Section() = default;
         Section(const Section& other) = default;

         virtual ~Section() = default;

         Section& operator=(const Section& other) = default;

         virtual std::unique_ptr<Section> CreateClone() const;

         void Offset(Float64 dx, Float64 dy);
         void Offset(const Size2d& delta);
         void Move(Shape::LocatorPoint point, const Point2d& to);
         void Move(const Point2d& from, const Point2d& to);
         void Rotate(Float64 cx, Float64 cy, Float64 angle);
         void Rotate(const Point2d& center, Float64 angle);
         void SetHookPoint(std::shared_ptr<Point2d>& hookPnt);
         void SetHookPoint(const Point2d& hookPnt);
         std::shared_ptr<Point2d>& GetHookPoint();
         const std::shared_ptr<Point2d>& GetHookPoint() const;
         Point2d GetLocatorPoint(Shape::LocatorPoint lp) const;
         void SetLocatorPoint(Shape::LocatorPoint lp, Point2d& position);

         //------------------------------------------------------------------------
         // AddComponent
         // Adds a component to the section.  A component consists of a shape (a clone 
         // of rShape) and the material properties modE and density.  This method 
         // creates a clone of rShape.  If bRegisterListeners is true,  listeners 
         // registered with rShape are registered with the clone as well. If a 
         // shape is modified,  section listeners will be notified through the 
         // gmSectionListener interface.  A lookup key is returned.  This key is 
         // used to access the clone of the shape or its associated material 
         // properties.
         void AddComponent(const Shape& shape, Float64 fgModE, Float64 fgDensity, Float64 bgModE, Float64 bgDensity, SectionComponent::ComponentType componentType);
         void AddComponent(std::unique_ptr<Shape>&& shape, Float64 fgModE, Float64 fgDensity, Float64 bgModE, Float64 bgDensity, SectionComponent::ComponentType componentType);

         const SectionComponent& GetComponent(IndexType idx) const;
         SectionComponent& GetComponent(IndexType idx);

         //------------------------------------------------------------------------
         // RemoveComponent
         // Removes a component (shape and material) from the section and frees 
         // the memory allocated by the call to CreateClone() in AddComponent().
         // If the component could not be found,  this method does nothing (the 
         // debugging version issues a WARNing).  Returns true if the component 
         // was successfully removed,  otherwise false.
         void RemoveComponent(IndexType idx);

         //------------------------------------------------------------------------
         // Removes all of the components from this section.
         void Clear();

         //------------------------------------------------------------------------
         // GetElasticProperties
         // Assigns the elastic properties of the section to the gmElasticProperties 
         // object pointed to by pProperties.
         ElasticProperties GetElasticProperties() const;

         //------------------------------------------------------------------------
         // GetMassProperties
         // Assigns the mass properties of the section to the gmMassProperties 
         // object pointed to by pProperties.
         MassProperties GetMassProperties() const;

         //------------------------------------------------------------------------
         // GetBoundingBox
         // Returns the smallest rectangle that bounds the entire section.  If 
         // bExcludeNonstructualComponents is true,  the bounding box is the 
         // smallest rectangle that bounds all of the structural components.
         Rect2d GetBoundingBox(bool bExcludeNonstructuralComponents=true) const;

         //------------------------------------------------------------------------
         // CreateClippedSection
         // Clips this section against line.  Clips away the portion of the shape 
         // on the side of the line defined by side.  This is a factory method.  
         // You are responsible for freeing the memory allocated by this method. 
         // If shape s lies entire on the clipping side of the line 0 is returned.
         // Any listeners to the original section are not transferred to this new 
         // section.
         std::unique_ptr<Section> CreateClippedSection(const Line2d& line,Line2d::Side side) const;

         //------------------------------------------------------------------------
         // CreateClippedSection
         // Clips this section against rectangle r.  Clips in or out of the 
         // rectangle as specified by region.  This is a factory method.  You 
         // are responsible for freeing memory allocated by this method.  This method
         // returns 0 if, the shape lies entirely within the clipping rectangle and 
         // region is set to clip out, or the shape and the rectangle do not 
         // intersection and region is to clip in. Any listeners to the original 
         // section are not transferred to this new section.
         std::unique_ptr<Section> CreateClippedSection(const Rect2d& r,Section::ClipRegion region) const;

      #if defined _DEBUG
         virtual bool AssertValid() const;
         virtual void Dump(WBFL::Debug::LogContext& os) const;
      #endif // _DEBUG

      #if defined _UNITTEST
         static bool TestMe(WBFL::Debug::Log& rlog);
      #endif // _UNITTEST

      private:
         std::vector<SectionComponent> m_Components;
         std::shared_ptr<Point2d> m_DummyHookPoint{ nullptr };
         void Copy(const Section& other);
      };

   }; // Geometry
}; // WBFL


#endif // INCLUDED_GEOMMODEL_SECTION_H_
