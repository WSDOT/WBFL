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

#include <GeomModel/ShapeOnPolygonImpl.h>
#include <GeomModel/Plane3d.h>

namespace WBFL
{
   namespace Geometry
   {

/// Abstract base class for flanged beams shapes and use an underlying polygon for their implementation
class GEOMMODELCLASS FlangedBeam : public ShapeOnPolygonImpl
{
public:
   FlangedBeam() : ShapeOnPolygonImpl() {}
   FlangedBeam(std::shared_ptr<Point2d>& hookPnt) : ShapeOnPolygonImpl(hookPnt) {}
   FlangedBeam(const Point2d& hookPnt) : ShapeOnPolygonImpl(hookPnt) {}
   FlangedBeam(const FlangedBeam& other) : ShapeOnPolygonImpl(other) {}
   virtual ~FlangedBeam() {}
   FlangedBeam& operator=(const FlangedBeam& other) { __super::operator=(other); return *this; }

   /// Returns the number of top flanges
   virtual IndexType GetTopFlangeCount() const = 0;
   
   /// Returns the location of the center of the top flange relative to the centerline of the beam.
   /// Negative values indicate the center of the top flange is to the left of the centerline of the beam
   virtual Float64 GetTopFlangeLocation(IndexType flangeIdx) const = 0;

   /// Returns the top flange width of the girder
   virtual Float64 GetTopFlangeWidth(IndexType flangeIdx) const = 0;

   /// Returns the number of bottom flanges
   virtual IndexType GetBottomFlangeCount() const = 0;

   /// Returns the location of the center of the bottom flange relative to the centerline of the beam.
   /// Negative values indicate the center of the bottom flange is to the left of the centerline of the beam
   virtual Float64 GetBottomFlangeLocation(IndexType flangeIdx) const = 0;

   /// Returns the bottom flange width of the girder
   virtual Float64 GetBottomFlangeWidth(IndexType flangeIdx) const = 0;

   /// Returns the overall top width of the girder
   virtual Float64 GetTopWidth() const = 0;

   /// Returns the overall bottom width of the girder
   virtual Float64 GetBottomWidth() const = 0;

   /// Returns the number of webs
   virtual IndexType GetWebCount() const = 0;

   /// Returns a plane object that represents the mid-plane member of a web
   virtual Plane3d GetWebPlane(WebIndexType webIdx) const = 0;

   /// Returns the web width for shear
   virtual Float64 GetShearWidth() const = 0;

   /// Returns the average web width
   virtual Float64 GetAvgWebWidth() const = 0;

   /// Returns the minimum web width
   virtual Float64 GetMinWebWidth() const = 0;

   /// Returns the the overall girder height
   virtual Float64 GetHeight() const = 0;

   /// Returns the minimum bottom flange thickness
   virtual Float64 GetMinBottomFlangeThickness() const = 0;

   /// Returns the minimum top flange thickness
   virtual Float64 GetMinTopFlangeThickness() const = 0;

   /// Returns the number of mating surfaces
   virtual MatingSurfaceIndexType GetMatingSurfaceCount() const = 0;

   /// Returns the width of the mating surface between the girder and a
   /// composite slab. This may or may not be equal to the top flange width
   virtual Float64 GetMatingSurfaceWidth(MatingSurfaceIndexType idx) const = 0;

   /// Returns the location of the center of the mating surface, relative
   /// to the centerline of the beam. The mating surface is left of the centerline if
   /// the location is less than zero.
   virtual Float64 GetMatingSurfaceLocation(MatingSurfaceIndexType idx) const = 0;
};

   }; // Geometry
}; // WBFL
