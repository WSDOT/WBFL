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
#include <GeomModel/ShapeImpl.h>
#include <GeomModel/Polygon.h>

namespace WBFL
{
   namespace Geometry
   {
      /// Partial implementation of the Shape class for shapes that generally have closed form solutions, but still need to create
      /// and alternative polygon representation. A shape may need an alternative polygon representation for PolyPoints and Clipping
      class GEOMMODELCLASS ShapeOnAlternativePolygonImpl : public ShapeImpl
      {
      public:
         ShapeOnAlternativePolygonImpl();
         ShapeOnAlternativePolygonImpl(std::shared_ptr<Point2d>& hookPnt);
         ShapeOnAlternativePolygonImpl(const Point2d& hookPnt);
         ShapeOnAlternativePolygonImpl(const ShapeOnAlternativePolygonImpl&);

         virtual ~ShapeOnAlternativePolygonImpl();

         ShapeOnAlternativePolygonImpl& operator=(const ShapeOnAlternativePolygonImpl&);

         virtual std::vector<Point2d> GetPolyPoints() const override;

         virtual void SetHookPoint(std::shared_ptr<Point2d> hookPnt) override;
         virtual void SetHookPoint(const Point2d& hookPnt) override;

         virtual void Offset(const Size2d& delta) override;
         virtual void Rotate(const Point2d& center, Float64 angle) override;
         virtual void Reflect(const Line2d& line) override;

      protected:
         virtual void OnUpdatePolygon(std::unique_ptr<Polygon>& polygon) const = 0;

         /// Retrieves the polygon representation. DO NOT CALL THIS FROM OnUpdatePolygon.
         std::unique_ptr<Polygon>& GetPolygon() const;
         void SetDirtyFlag(bool bFlag = true);
         bool IsDirty() const;

      private:
         void Copy(const ShapeOnAlternativePolygonImpl& other);
         void UpdatePolygon() const;
         mutable bool m_bIsDirty{ true };
         mutable std::unique_ptr<Polygon> m_Polygon;
      };
   }; // Geometry
}; // WBFL
