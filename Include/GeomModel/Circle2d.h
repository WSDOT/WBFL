///////////////////////////////////////////////////////////////////////
// Geometry - Modeling of geometric primitives
// Copyright © 1999-2024  Washington State Department of Transportation
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

namespace WBFL
{
   namespace Geometry
   {
      class Arc;

      /// A class to represent a circle in the X-Y Plane
      /// Using the name Circle2d so Circle can be used for the Shape object
      class GEOMMODELCLASS Circle2d
      {
      public:
         /// Default constructor. Circle centered at (0,0) with radius of zero
         Circle2d() = default;

         Circle2d(const Circle2d&) = default;
         Circle2d& operator=(const Circle2d&) = default;

         /// Create a circle from a centerpoint and radius
         Circle2d(const Point2d& center, Float64 radius);

         /// Defines a circle with two points on its diameter
         Circle2d(const Point2d& p1,const Point2d& p2);

         /// Defines a circle using three non-colinear points.  If the points
         /// are colinear a circle with center at p2 with a radius of zero is created.
         Circle2d(const Point2d& p1,const Point2d& p2, const Point2d& p3);

         /// Create a circle by completing an arch
         Circle2d(const Arc& arc);

         virtual ~Circle2d();

         bool operator==(const Circle2d& other) const;
         bool operator!=(const Circle2d& other) const;

         void SetRadius(Float64 r);
         Float64 GetRadius() const;

         void SetCenter(const Point2d& center);
         Point2d& GetCenter();
         const Point2d& GetCenter() const;

         Float64 GetPerimeter() const;

         bool IsPointOnPerimeter(const Point2d& p) const;

      private:
         Point2d m_Center;
         Float64 m_Radius{ 0.0 };
      };
   }; // Geometry
}; // WBFL
