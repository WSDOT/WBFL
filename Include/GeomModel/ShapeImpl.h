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
#include <GeomModel/Shape.h>
#include <GeomModel/Primitives.h>

namespace WBFL
{
   namespace Geometry
   {
      class CompositeShape;
      class Properties;

      /// A partial implementation of the Shape class, including support for a hook point.
      class GEOMMODELCLASS ShapeImpl : public Shape
      {
      public:
         ShapeImpl();
         ShapeImpl(std::shared_ptr<Point2d>& hookPnt);
         ShapeImpl(const Point2d& hookPnt);
         ShapeImpl(const ShapeImpl&);

         virtual ~ShapeImpl();

         ShapeImpl& operator=(const ShapeImpl&);

         virtual void SetHookPoint(std::shared_ptr<Point2d> hookPnt) override;
         virtual void SetHookPoint(const Point2d& hookPnt) override;
         virtual std::shared_ptr<Point2d> GetHookPoint() override;
         virtual std::shared_ptr<const Point2d> GetHookPoint() const override;

         virtual void Offset(const Size2d& delta) override;
         virtual void Offset(Float64 dx, Float64 dy) override;
         virtual void Move(LocatorPoint lp, const Point2d& to) override;
         virtual void Move(const Point2d& from, const Point2d& to) override;
         virtual void Rotate(const Point2d& center, Float64 angle) override;
         virtual void Rotate(Float64 cx, Float64 cy, Float64 angle) override;
         virtual std::unique_ptr<Shape> CreateReflectedShape(const Line2d& line) const override;
         virtual Point2d GetLocatorPoint(LocatorPoint lp) const override;
         virtual void SetLocatorPoint(LocatorPoint lp, const Point2d& position) override;

      protected:
         virtual void DoOffset(const Size2d& delta) = 0;
         virtual void DoRotate(const Point2d& center, Float64 angle) = 0;

         // returns true if the hook point has changed since it was set
         bool IsHookPointChanged() const;

         // called by derived classes when shapes have been made consistent with the
         // current location of the hook point
         void ShapeCurrentWithHookPoint() const; 

      private:
         std::shared_ptr<Point2d> m_pHookPoint{ std::make_shared<Point2d>() };
         mutable Point2d m_CachedHookPoint;
         void Copy(const ShapeImpl& other);
      };
   }; // Geometry
}; // WBFL
