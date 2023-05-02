///////////////////////////////////////////////////////////////////////
// CoordGeom - Coordinate Geometry Library
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

#include <CoordGeom/CoordGeomExp.h>
#include <CoordGeom/CoordGeomTypes.h>
#include <CoordGeom/Direction.h>

#include <GeomModel/Primitives.h>
#include <GeomModel/Line2d.h>

#include <memory>

namespace WBFL
{
   namespace COGO
   {
      class Path;

      /// @brief Abstract base class for path elements
      class COORDGEOMCLASS PathElement
      {
      private:
         void SetPath(std::weak_ptr<Path> path) { m_Path = path; }
         friend Path;

      protected:
         PathElement() = default;
         PathElement(const PathElement&);
         virtual ~PathElement() = default;

      public:
         PathElement& operator=(const PathElement&) = delete;

         std::shared_ptr<const Path> GetPath() const;
         std::shared_ptr<Path> GetPath();

         /// @brief Creates a copy of this path element
         /// @return 
         virtual std::shared_ptr<PathElement> Clone() const = 0;

         /// @brief Returns the start point of the element
         /// @return 
         virtual const WBFL::Geometry::Point2d& GetStartPoint() const = 0;

         /// @brief Returns the end point of the element
         /// @return 
         virtual const WBFL::Geometry::Point2d& GetEndPoint() const = 0;

         /// @brief Returns a point along the curve
         /// @param distFromStart 
         /// @return 
         virtual WBFL::Geometry::Point2d PointOnCurve(Float64 distFromStart) const = 0;

         /// @brief Moves the path element
         /// @param distance Distance to move
         /// @param direction Direction to move
         virtual void Move(Float64 distance, const Direction& direction) = 0;

         /// @brief Offsets the curve from its present location
         /// @param dx Distance to offset the curve in the X (East-West) direction.
         /// @param dy Distance to offset the curve in the Y (North-South) direction.
         virtual void Offset(Float64 dx, Float64 dy) = 0;

         /// @brief Offsets the curve from its present location
         /// @param size The offset amount as a size object
         virtual void Offset(const WBFL::Geometry::Size2d& size) {Offset(size.Dx(), size.Dy());}

         /// @brief Returns the length of the path element
         /// @return 
         virtual Float64 GetLength() const = 0;

         /// @brief Returns a vector of the key points defining the path element
         /// @return 
         virtual std::vector<WBFL::Geometry::Point2d> GetKeyPoints() const = 0;

         /// @brief Creates a point on the path element at the specified location
         /// @param distFromStart Distance from the start of the path element from with the point is to be located
         /// @param offsetType Specifies how offset is measured
         /// @param offset Offset from the path element to the point
         /// @param direction Direction from the path element at which to locate the point
         /// @return The point
         virtual WBFL::Geometry::Point2d LocatePoint(Float64 distFromStart, OffsetType offsetType, Float64 offset, const Direction& direction) const = 0;

         /// @brief Computes the bearing of the path element at a specified location
         /// @image html Images/Bearing.jpg
         /// @param distFromStart Distance from the start of the path element
         /// @return 
         virtual Direction GetBearing(Float64 distFromStart) const = 0;

         /// @brief Computes the normal to the path element at the specified location
         /// @image html Images/Normal.jpg
         /// @param distFromStart Distance from the start of the path element
         /// @return 
         virtual Direction GetNormal(Float64 distFromStart) const { auto bearing = GetBearing(distFromStart); bearing.Increment(3 * PI_OVER_2); return bearing; }

         /// @brief Project a point onto the path element
         /// @param point The point to project onto the path element
         /// @return Returns the tuple<NewPoint,DistFromStart,OnProjection> where NewPoint is the point on the path element, 
         /// DistFromStart is the distance from the start of the path element to the projected point, and OnProjection is a boolean
         /// with value of true indicating the point is on a projection of the path element
         virtual std::tuple<WBFL::Geometry::Point2d, Float64, bool> ProjectPoint(const WBFL::Geometry::Point2d& point) const = 0;

         /// @brief Intersects a line with the path element
         /// @param line Line to intersect with the path element
         /// @param bProjectBack If true, the back tangent line at the start of the path element is considered to be part of the element
         /// @param bProjectAhead If true, the ahead tangent line at the end of the path element is considered to be part of the element
         /// @return 
         virtual std::vector<WBFL::Geometry::Point2d> Intersect(const WBFL::Geometry::Line2d& line, bool bProjectBack, bool bProjectAhead) const = 0;

         /// @brief Creates a new path that is offset from this path element. Some PathElement types require
         /// multiple PathElement objects to represent the offset element.
         /// @param offset The offset distance, measure normal to the path element
         /// @return Collection of path elements
         virtual std::vector<std::shared_ptr<PathElement>> CreateOffsetPath(Float64 offset) const = 0;

         /// @brief Creates a new path that is a subset of this path element. Some PathElement types require
         /// multiple PathElement objects to represent the sub-path
         /// @param start Distance from the start of the element to the start of the sub-path element
         /// @param end Distance from the start of the element to the end of the sub-path element
         /// @return 
         virtual std::vector<std::shared_ptr<PathElement>> CreateSubpath(Float64 start, Float64 end) const = 0;

#if defined _UNITTEST
         /// A self-test function - returns true if passed.
         //static bool TestMe(WBFL::Debug::Log& rlog);
#endif // _UNITTEST
      protected:

         /// @brief Adjust the offset so that it is measured along the specified direction. Subclasses can use this when implementing LocatePoint
         /// @param distFromStart Distance from the start of the path element
         /// @param offsetType Indicates how the offset is measured
         /// @param offset The offset
         /// @param dir Direction the offset is measure for OffsetType::AlongDirection
         /// @return The offset measured along the direction
         Float64 AdjustOffset(Float64 distFromStart,OffsetType offsetType,Float64 offset,const Direction& dir) const
         {
            if (offsetType == OffsetType::Normal && !IsZero(offset))
            {
               // adjust offset so that it is measured along direction
               auto normal = GetNormal(distFromStart);
               auto angle = dir.AngleBetween(normal);
               offset *= cos(angle);
            }
            return offset;
         }

         /// @brief Subclasses should call this method whenever their data changes in such a way
         /// to modify the layout of the profile.
         void OnPathElementChanged();

      private:
         std::weak_ptr<Path> m_Path;
      };
   };
};
