///////////////////////////////////////////////////////////////////////
// CoordGeom - Coordinate Geometry Library
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

#include <CoordGeom/CoordGeomExp.h>
#include <CoordGeom/PathElement.h>

#include <GeomModel/Primitives.h>

namespace WBFL
{
   namespace COGO
   {
      /// @brief An object that represents a geometric path in plan view. 
      /// A path consists of PathElement objects, which are typically Segment, TransitionCurve, CircularCurve, CompoundCurve, and CubicSpline objects.
      /// PathElement objects are positioned end to end in the order they are defined. Straight lines are used to connect the PathElement objects together. 
      /// The tangents at the beginning and end of the path are projected as straight lines.
      /// If a Path does not contain any PathElement objects, it is assumed that the path begins at N 0.00, E 0.00, and is a straight line bearing N 90 E.
      class COORDGEOMCLASS Path : public PathElement, public std::enable_shared_from_this<Path>
      {
      private:
         Path() = default;
         Path(const Path&);
         Path& operator=(Path other) = delete;

      public:
         static std::shared_ptr<Path> Create();
         static std::shared_ptr<Path> Create(const Path& path);
         static std::shared_ptr<Path> Create(const std::vector<std::shared_ptr<PathElement>>& vElements);

         ~Path() = default;

         /// @brief Adds a PathElement to the path
         /// @param pathElement 
         void AddPathElement(std::shared_ptr<PathElement> pathElement);

         /// @brief Inserts a PathElement at the specified index
         /// @param idx 
         /// @param pathElement 
         void InsertPathElement(IndexType idx, std::shared_ptr<PathElement> pathElement);

         /// @brief Returns the number of path elements
         /// @return 
         IndexType GetPathElementCount() const;

         /// @brief Returns the PathElement at the specified index
         /// @param idx 
         /// @return 
         std::shared_ptr<const PathElement> GetPathElement(IndexType idx) const;
         std::shared_ptr<PathElement> GetPathElement(IndexType idx);

         /// @brief Returns the path elements
         /// @return 
         std::vector<std::shared_ptr<PathElement>>& GetPathElements();

         /// @brief Returns the path elements
         /// @return 
         const std::vector<std::shared_ptr<PathElement>>& GetPathElements() const;

         /// @brief Removes all path elements
         void Clear();

         /// @brief Computes the distance from the start of the path and offset from the path for a given point
         /// @image html Images/Offset.jpg
         /// @param point The point whose offset is to be computed
         /// @return A pair of the form (DistFromStart,Offset). DistFromStart is the distance from the start of the path where a normal line passing through point intersects the path. Offset is the offset from the path to the point.
         std::pair<Float64,Float64> DistanceAndOffset(const WBFL::Geometry::Point2d& point) const;

         /// @brief Divides the path into nParts equal length parts
         /// @param nParts Number of equal length parts
         /// @return Points along the path at the division points
         std::vector<WBFL::Geometry::Point2d> Divide(IndexType nParts) const;

         /// @brief Divides the path, between start and end, into nParts equal length parts
         /// @param start Location from the start of the path where the division begins
         /// @param end Location from the start of the path where the division ends. If < 0, ends at the end of the path
         /// @param nParts Number of equal length parts
         /// @return Points along the path at the division points
         std::vector<WBFL::Geometry::Point2d> Divide(Float64 start,Float64 end,IndexType nParts) const;

         /// @brief Intersects a Line2d object with the path, projecting the start and end tangents if specified, returning the intersection point nearest a specified point.
         /// @param line The line to intersect with the path.
         /// @param nearest A point used for comparison with multiple intersection points. The resulting point is the one nearest this point.
         /// @param bProjectBack If true, the back tangent line at the start of the path is considered to be part of the path
         /// @param bProjectAhead If true, the ahead tangent line at the end of the path is considered to be part of the path
         /// @return Pair of the format (Success,Point). Success is true if an intersection point is found, otherwise false and Point is undetermined. Point is the intersection point closest to nearest.
         std::pair<bool, WBFL::Geometry::Point2d> Intersect(const WBFL::Geometry::Line2d& line, const WBFL::Geometry::Point2d& nearest, bool bProjectBack,bool bProjectAhead) const;

         //
         // PathElement methods
         //
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

      private:
         std::vector<std::shared_ptr<PathElement>> m_Elements; // These are the input elements, there could be gaps between elements

         friend PathElement;
         void OnPathChanged();

         struct Element
         {
            Element(Float64 s, Float64 e, std::shared_ptr<PathElement> pe) : start(s), end(e), element(pe) {}
            Float64 start{ 0.0 };
            Float64 end{ 0.0 };
            std::shared_ptr<PathElement> element;
         };
         using Element = Element;
         mutable std::vector<Element> m_ConnectedPathElements; // not the same as m_Elements. This is a fully connected path of elements
         mutable Float64 m_PathLength{ 0.0 };

         // Returns a vector of Element objects that captures the start and end location
         // along the path of a path element as well as the path element itself.
         // Don't access m_ConnectedPathElements directly. Use GetConnectedPathElements because it
         // initializes m_ConnectedPathElements on demand.
         const std::vector<Element>& GetConnectedPathElements() const;

         // Finds a PathElement object that contains the specified distance from start of the path.
         // Also determines the distance to the beginning of that Path element
         std::pair<std::shared_ptr<const PathElement>, Float64> FindElement(Float64 distFromStart) const;
      };
   };
};
