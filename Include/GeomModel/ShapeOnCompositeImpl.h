///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
// Copyright � 1999-2025  Washington State Department of Transportation
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
#include <GeomModel/ShapeImpl.h>
#include <GeomModel/CompositeShape.h>

namespace WBFL
{
   namespace Geometry
   {
      /// Partial implementation of the Shape class for complex shapes that utilize a CompositeShape for the implementation.
      class GEOMMODELCLASS ShapeOnCompositeImpl : public ShapeImpl
      {
      public:
         ShapeOnCompositeImpl();
         ShapeOnCompositeImpl(std::shared_ptr<Point2d>& hookPnt);
         ShapeOnCompositeImpl(const Point2d& hookPnt);
         ShapeOnCompositeImpl(const ShapeOnCompositeImpl& rOther);
         virtual ~ShapeOnCompositeImpl();

         ShapeOnCompositeImpl& operator= (const ShapeOnCompositeImpl& rOther);

         virtual ShapeProperties GetProperties() const override;
         virtual Rect2d GetBoundingBox() const override;
         virtual std::vector<Point2d> GetPolyPoints() const override;
         virtual bool PointInShape(const Point2d& p) const override;
         virtual std::unique_ptr<Shape> CreateClippedShape(const Line2d& line, Line2d::Side side) const override;
         virtual std::unique_ptr<Shape> CreateClippedShape(const Rect2d& r, Shape::ClipRegion region) const override;
         virtual Float64 GetFurthestDistance(const Line2d& line, Line2d::Side side) const override;
         virtual std::pair<Point2d,Float64> GetFurthestPoint(const Line2d& line, Line2d::Side side) const override;
         virtual Float64 GetPerimeter() const override;
         virtual void Reflect(const Line2d& line) override;

      protected:
         virtual void OnUpdateComposite(std::unique_ptr<CompositeShape>& composite) const = 0;

         /// Retrieves the composite shape representation. DO NOT CALL THIS FROM OnUpdateComposite.
         std::unique_ptr<CompositeShape>& GetComposite() const;
         void SetDirtyFlag(bool bFlag = true);
         bool IsDirty() const;

      protected:
         virtual void DoOffset(const Size2d& delta) override;
         virtual void DoRotate(const Point2d& center, Float64 angle) override;

      private:
         void Copy(const ShapeOnCompositeImpl& other);
         void UpdateComposite() const;
         mutable bool m_bIsDirty{ true };
         mutable std::unique_ptr<CompositeShape> m_Composite;
      };

   }; // Geometry
}; // WBFL
