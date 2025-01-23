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
#include <GeomModel/ShapeOnPolygonImpl.h>

namespace WBFL
{
   namespace Geometry
   {
      class Polygon;

      /// Object representing the shape of a traffic barrier
      ///
      /// \image html TrafficBarrier/TrafficBarrier.jpg   	
      class GEOMMODELCLASS TrafficBarrier : public ShapeOnPolygonImpl
      {
      public:
         enum class Orientation { Left, Right };

         TrafficBarrier();

         TrafficBarrier(Float64 x1,Float64 x2,Float64 x3,Float64 x4,Float64 x5,
                        Float64 y1,Float64 y2,Float64 y3,
                        Float64 tSlab,
                        Orientation orient,
            std::shared_ptr<Point2d>& hookPoint);

         TrafficBarrier(const TrafficBarrier& other) = default;
         TrafficBarrier& operator=(const TrafficBarrier& other) = default;

         virtual ~TrafficBarrier();

         void SetX1(Float64 x1);
         Float64 GetX1() const;

         void SetX2(Float64 x2);
         Float64 GetX2() const;

         void SetX3(Float64 x3);
         Float64 GetX3() const;

         void SetX4(Float64 x4);
         Float64 GetX4() const;

         void SetX5(Float64 x5);
         Float64 GetX5() const;

         void SetY1(Float64 y1);
         Float64 GetY1() const;

         void SetY2(Float64 y2);
         Float64 GetY2() const;

         void SetY3(Float64 y3);
         Float64 GetY3() const;

         void SetSlabDepth(Float64 tSlab);
         Float64 GetSlabDepth() const;

         void SetOrientation(Orientation orient);
         Orientation GetOrientation() const;

         /// Translates a shape by a delta amount.
         virtual void DoOffset(const Size2d& delta) override;

         /// Rotates a shape.  The rotation is centered about point center.  The 
         /// rotation angle is measured in radians counter clockwise.
         virtual void DoRotate(const Point2d& center, Float64 angle) override;

         ShapeProperties GetProperties() const;

         Rect2d GetBoundingBox() const;

         std::unique_ptr<Shape> CreateClone() const;

         std::unique_ptr<Shape> CreateClippedShape(const Line2d& line, Line2d::Side side) const;

         std::unique_ptr<Shape> CreateClippedShape(const Rect2d& r, Shape::ClipRegion region) const;

         Float64 GetFurthestDistance(const Line2d& line, Line2d::Side side) const;

      protected:
         virtual void OnUpdatePolygon(std::unique_ptr<Polygon>& polygon) const override;

      private:
         Float64 m_Rotation{ 0.0 };
         Float64 m_X1{ 0.0 };
         Float64 m_X2{ 0.0 };
         Float64 m_X3{ 0.0 };
         Float64 m_X4{ 0.0 };
         Float64 m_X5{ 0.0 };
         Float64 m_Y1{ 0.0 };
         Float64 m_Y2{ 0.0 };
         Float64 m_Y3{ 0.0 };
         Float64 m_tSlab{ 0.0 };
         Orientation m_Orientation{ Orientation::Left };
      };
   }; // Geometry
}; // WBFL
