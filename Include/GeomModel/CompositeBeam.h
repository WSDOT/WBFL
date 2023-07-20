///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
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

#pragma once

#include <GeomModel/GeomModelExp.h>
#include <GeomModel/ElasticProperties.h>
#include <GeomModel/MassProperties.h>
#include <GeomModel/Section.h>
#include <GeomModel/Shape.h>
#include <GeomModel/Primitives.h>

namespace WBFL
{
   namespace Geometry
   {
      /// A slab-on-girder composite beam
      /// \image html CompositeBeam/CompositeBeam.gif
      class GEOMMODELCLASS CompositeBeam
      {
      public:
         CompositeBeam();
         CompositeBeam(const CompositeBeam& other);
         virtual ~CompositeBeam();

         CompositeBeam& operator=(const CompositeBeam& other);

         void SetBeam(const Shape& beam);
         void SetBeam(std::unique_ptr<Shape>&& beam);
         Shape& GetBeam();
         const Shape& GetBeam() const;

         /// @brief Sets the effective slab width used when computing section properties
         /// @param wEff 
         void SetEffectiveSlabWidth(Float64 wEff);
         Float64 GetEffectiveSlabWidth() const;

         /// @brief Sets the tributary slab width used when computing mass properties
         /// @param wTrib 
         void SetTributarySlabWidth(Float64 wTrib);
         Float64 GetTributarySlabWidth() const;

         /// @brief Sets the total cast depth of the slab, used when computing mass properties
         /// @param tSlab 
         void SetGrossSlabDepth(Float64 tSlab);
         Float64 GetGrossSlabDepth() const;

         /// @brief Sets the sacrificial depth that is deducted from the gross depth to yield the structural depth. THe structural depth is used when computing section properties.
         /// @param tSac 
         void SetSacrificialDepth(Float64 tSac);
         Float64 GetSacrificialDepth() const;

         void SetHaunchDepth(Float64 tHaunch);
         Float64 GetHaunchDepth() const;

         void SetHaunchWidth(Float64 wHaunch);
         Float64 GetHaunchWidth() const;

         void SetSlabE(Float64 modE);
         Float64 GetSlabE() const;

         void SetSlabDensity(Float64 d);
         Float64 GetSlabDensity() const;

         void SetBeamE(Float64 modE);
         Float64 GetBeamE() const;

         void SetBeamDensity(Float64 d);
         Float64 GetBeamDensity() const;

         void SetHookPoint(std::shared_ptr<Point2d>& hookPnt);
         void SetHookPoint(const Point2d& hookPnt);
         std::shared_ptr<Point2d>& GetHookPoint();
         const std::shared_ptr<Point2d>& GetHookPoint() const;

         Rect2d GetBoundingBox(bool bExcludeNonstructuralComponents) const;
         std::unique_ptr<Section> CreateClippedSection(const Line2d& line, Line2d::Side side) const;
         std::unique_ptr<Section> CreateClippedSection(const Rect2d& r, Section::ClipRegion region) const;

         /// Returns the first moment of area of the deck slab
         Float64 GetQslab() const;

         /// Returns the first moment of area at the specified elevation
         /// \param y distance from bottom of section
         Float64 GetQ(Float64 y) const;
   
         /// @brief Returns the elastic properties of the beam
         /// @return 
         ElasticProperties GetElasticProperties() const;

         /// @brief Returns the mass properties of the beam
         /// @return 
         MassProperties GetMassProperties() const;

      private:
         Section m_Section;

         void Init();
         void Copy(const CompositeBeam& other);
         void UpdateShapeLocations();
      };
   }; // Geometry
}; // WBFL
