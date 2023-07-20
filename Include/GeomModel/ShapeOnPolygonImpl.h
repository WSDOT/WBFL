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
#include <GeomModel/ShapeOnAlternativePolygonImpl.h>
#include <GeomModel/Polygon.h>

namespace WBFL
{
   namespace Geometry
   {
      /// A partial implementation of the Shape class for shapes that use a polygon representation for all properties
      class GEOMMODELCLASS ShapeOnPolygonImpl : public ShapeOnAlternativePolygonImpl
      {
      public:
         ShapeOnPolygonImpl();
         ShapeOnPolygonImpl(std::shared_ptr<Point2d>& hookPnt);
         ShapeOnPolygonImpl(const Point2d& hookPnt);
         ShapeOnPolygonImpl(const ShapeOnPolygonImpl&);

         virtual ~ShapeOnPolygonImpl();

         ShapeOnPolygonImpl& operator=(const ShapeOnPolygonImpl&);

         virtual ShapeProperties GetProperties() const override;
         virtual Rect2d GetBoundingBox() const override;
         virtual std::vector<Point2d> GetPolyPoints() const override;
         virtual std::unique_ptr<Shape> CreateClippedShape(const Line2d& line, Line2d::Side side) const override;
         virtual std::unique_ptr<Shape> CreateClippedShape(const Rect2d& r, Shape::ClipRegion region) const override;
         virtual Float64 GetFurthestDistance(const Line2d& line, Line2d::Side side) const override;
         virtual void GetFurthestPoint(const Line2d& line, Line2d::Side side, Point2d& furthestPoint, Float64& furthestDistance) const override;
         virtual bool PointInShape(const Point2d& p) const override;
         virtual Float64 GetPerimeter() const override;
         virtual void Reflect(const Line2d& line) override;

      private:
         void Copy(const ShapeOnPolygonImpl& other);
      };
   }; // Geometry
}; // WBFL
