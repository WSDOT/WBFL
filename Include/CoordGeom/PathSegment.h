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
#include <CoordGeom/PathElement.h>

#include <GeomModel/LineSegment2d.h>

namespace WBFL
{
   namespace COGO
   {
      /// @brief A linear segment PathElement
      class COORDGEOMCLASS PathSegment : public PathElement
      {
      private:
         PathSegment() = default;
         PathSegment(const WBFL::Geometry::Point2d& start, const WBFL::Geometry::Point2d& end);
         PathSegment(Float64 x1, Float64 y1, Float64 x2, Float64 y2);
         PathSegment(const WBFL::Geometry::Point2d& start, const WBFL::Geometry::Size2d& relEnd);
         PathSegment(const PathSegment&) = default;
         PathSegment& operator=(const PathSegment&) = delete;

      public:
         /// @brief Creates a PathSegment
         /// @return 
         static std::shared_ptr<PathSegment> Create();

         /// @brief Creates a PathSegment
         /// @param segment The segment to be copied. The Path object association is not copied.
         /// @return 
         static std::shared_ptr<PathSegment> Create(const PathSegment& segment);

         /// @brief Creates a PathSement
         /// @param start Starting point of the segment
         /// @param end Ending point of the segment
         /// @return 
         static std::shared_ptr<PathSegment> Create(const WBFL::Geometry::Point2d& start, const WBFL::Geometry::Point2d& end);

         /// @brief Creates a PathSegment between points (x1,y1) and (x2,y2)
         /// @param x1 X-ordinate of first point
         /// @param y1 Y-ordinate of first point
         /// @param x2 X-ordinate of second point
         /// @param y2 Y-ordinate of second point
         /// @return 
         static std::shared_ptr<PathSegment> Create(Float64 x1, Float64 y1, Float64 x2, Float64 y2);

         /// @brief Creates a PathSegment starting at start with the end defined as a relative distance from the start
         /// @param start The start point
         /// @param relEnd The relative distance to the end point
         /// @return 
         static std::shared_ptr<PathSegment> Create(const WBFL::Geometry::Point2d& start, const WBFL::Geometry::Size2d& relEnd);

         ~PathSegment() = default;

         /// @brief Repositions the PathSegment with new terminus points
         /// @param start The new start point
         /// @param end The new end point
         void ThroughPoints(const WBFL::Geometry::Point2d& start, const WBFL::Geometry::Point2d& end);

         /// @brief Offsets the line segment
         /// @param offset Perpendicular offset distance
         void Offset(Float64 offset);

         // PathElement methods
         virtual std::shared_ptr<PathElement> Clone() const override;
         virtual const WBFL::Geometry::Point2d& GetStartPoint() const override;
         virtual const WBFL::Geometry::Point2d& GetEndPoint() const override;
         virtual WBFL::Geometry::Point2d PointOnCurve(Float64 distFromStart) const override;
         virtual void Move(Float64 distance, const Direction& direction) override;
         virtual void Offset(Float64 dx, Float64 dy) override;
         virtual Float64 GetLength() const override;
         virtual std::vector<WBFL::Geometry::Point2d> GetKeyPoints() const override;
         virtual WBFL::Geometry::Point2d LocatePoint(Float64 distFromStart, OffsetType offsetType, Float64 offset, const Direction& direction) const override;
         virtual Direction GetBearing(Float64 distFromStart) const override;
         virtual std::tuple<WBFL::Geometry::Point2d, Float64, bool> ProjectPoint(const WBFL::Geometry::Point2d& point) const override;
         virtual std::vector<WBFL::Geometry::Point2d> Intersect(const WBFL::Geometry::Line2d& line, bool bProjectBack, bool bProjectAhead) const override;
         virtual std::vector<std::shared_ptr<PathElement>> CreateOffsetPath(Float64 offset) const override;
         virtual std::vector<std::shared_ptr<PathElement>> CreateSubpath(Float64 start, Float64 end) const override;

         /// @brief Type conversion operator allowing a PathSegment to be converted to a LineSegment2d
         operator WBFL::Geometry::LineSegment2d const() { return m_Segment; }

      private:
         WBFL::Geometry::LineSegment2d m_Segment;
      };
   };
};
