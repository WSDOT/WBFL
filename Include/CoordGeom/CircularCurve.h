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
#include <CoordGeom/CoordGeomTypes.h>
#include <CoordGeom/Direction.h>

#include <GeomModel/Primitives.h>
#include <GeomModel/Line2d.h>

namespace WBFL
{
   namespace COGO
   {
      /// @brief A circular curve defined by a point on the back tangent, the intersection point of the back and forward tangents, 
      /// a point on the forward tangent, and the radius. Input values are denoted in red in the figure below. 
      /// @image html Images/CircularCurve.png
      class COORDGEOMCLASS CircularCurve : public PathElement
      {
      private:
         CircularCurve();
         CircularCurve(const WBFL::Geometry::Point2d& pbt, const WBFL::Geometry::Point2d& pi, const WBFL::Geometry::Point2d& pft, Float64 radius);
         CircularCurve(const CircularCurve&) = default;
         CircularCurve& operator=(const CircularCurve&) = delete;

      public:
         static std::shared_ptr<CircularCurve> Create();
         static std::shared_ptr<CircularCurve> Create(const WBFL::Geometry::Point2d& pbt, const WBFL::Geometry::Point2d& pi, const WBFL::Geometry::Point2d& pft, Float64 radius);
         static std::shared_ptr<CircularCurve> Create(const CircularCurve& curve);

         ~CircularCurve() = default;

         /// @brief Sets the point on the back tangent
         /// @param pbt A point on the back tangent of the curve
         void SetPBT(const WBFL::Geometry::Point2d& pbt);

         /// @brief Gets the point on the back tangent used to defined the curve
         /// @return The point on the back tangent
         const WBFL::Geometry::Point2d& GetPBT() const;

         /// @brief Set the tangent intersection point
         /// @param pi The point where the back and forward tangents intersect
         void SetPI(const WBFL::Geometry::Point2d& pi);

         /// @brief Gets the point where the back and forward tangents intersect
         /// @return The tangent intersection point
         const WBFL::Geometry::Point2d& GetPI() const;

         /// @brief Set the point on the forward tangent
         /// @param pft A point on the forward tangent of the curve
         void SetPFT(const WBFL::Geometry::Point2d& pft);

         /// @brief Gets the point on the forward tangent used to define the curve
         /// @return The point on the forward tangent
         const WBFL::Geometry::Point2d& GetPFT() const;

         /// @brief Sets the curve radius
         /// @param radius 
         void SetRadius(Float64 radius);

         /// @brief Gets the curve radius
         /// @return 
         Float64 GetRadius() const;

         /// @brief Gets the point of tangency at the start of the curve
         /// @return Point of curvature
         WBFL::Geometry::Point2d GetPC() const;

         /// @brief Gets the point of tangency at the end of the curve
         /// @return Point of tangency
         WBFL::Geometry::Point2d GetPT() const;

         /// @brief Gets the direction of the tangent line at the end of the curve
         /// @return Forward tangent
         Direction GetForwardTangentBearing() const;

         /// @brief Gets the direction of the tangent line at the start of the curve
         /// @return Back tangent
         Direction GetBackTangentBearing() const;

         /// @brief Gets the angle subtended by the circular arc
         /// @return 
         Angle GetAngle() const;

         /// @brief Returns the length of the circular curve tangent
         /// @image html Images/CircularCurve.png
         /// @return 
         Float64 GetTangent() const;

         /// @brief Returns the chord length of the circular curve
         /// @image html Images/CircularCurve.png
         /// @return 
         Float64 GetChord() const;

         /// @brief Returns the length of the circular curve mid-ordinate
         /// @image html Images/CircularCurve.png
         /// @return 
         Float64 GetMidOrdinate() const;

         /// @brief Returns the length of the circular curve external
         /// @image html Images/CircularCurve.png
         /// @return 
         Float64 GetExternal() const;

         /// @brief Returns the center point of the curve. The center point of the curve is taken to be the intersection of lines perpendicular to the back and forward tangents at PC and PT.
         WBFL::Geometry::Point2d GetCenter() const;

         /// @brief Returns the direction if the curve. The direction is as viewed looking ahead on station.
         CurveDirection GetCurveDirection() const;

         /// @brief Returns the degree of curvature of the circular curve.
         ///
         /// The degree of curvature can be computed by either the arc or chord method.
         ///
         /// Arc Method: \f[ dc = \frac{\Delta}{R} \f]
         /// Chord Method: \f[ dc = 2\sin^{-1}\frac{\Delta}{2R} \f]
         /// @param delta angle subtended by the curve
         /// @param type degree of curvature type
         /// @return 
         Angle GetDegreeOfCurvature(const Angle& delta, DegreeCurvature type) const;

         /// @brief Locates a point on the curve at a specified distance from PC.
         /// If the specified distance is less than zero or if it is greater than the curve length, the point will be located on the back or forward tangent, respectively.
         WBFL::Geometry::Point2d PointOnCurve(Float64 distFromStart) const;

         /// @brief Divides the curve into nParts equal length segments
         /// @param nParts Number of parts into which the curve is divided
         /// @return Vector of points at the ends of each equal length segment
         std::vector<WBFL::Geometry::Point2d> Divide(IndexType nParts) const;

         //
         // Path Element
         //

         virtual std::shared_ptr<PathElement> Clone() const override;
         virtual const WBFL::Geometry::Point2d& GetStartPoint() const override;
         virtual const WBFL::Geometry::Point2d& GetEndPoint() const override;
         virtual void Move(Float64 distance, const Direction& direction) override;
         virtual void Offset(Float64 dx, Float64 dy) override;
         virtual Float64 GetLength() const override;
         virtual std::vector<WBFL::Geometry::Point2d> GetKeyPoints() const override;
         virtual WBFL::Geometry::Point2d LocatePoint(Float64 distFromStart, OffsetType offsetType, Float64 offset, const Direction& direction) const override;
         virtual Direction GetBearing(Float64 distFromStart) const override;
         virtual std::tuple<WBFL::Geometry::Point2d,Float64,bool> ProjectPoint(const WBFL::Geometry::Point2d& point) const override;
         virtual std::vector<WBFL::Geometry::Point2d> Intersect(const WBFL::Geometry::Line2d& line, bool bProjectBack, bool bProjectAhead) const override;
         virtual std::vector<std::shared_ptr<PathElement>> CreateOffsetPath(Float64 offset) const override;
         virtual std::vector<std::shared_ptr<PathElement>> CreateSubpath(Float64 start, Float64 end) const override;

#if defined _UNITTEST
         /// A self-test function - returns true if passed.
         static bool TestMe(WBFL::Debug::Log& rlog);
#endif // _UNITTEST


      private:
         WBFL::Geometry::Point2d m_PBT, m_PI, m_PFT;
         Float64 m_Radius;

         mutable WBFL::Geometry::Point2d m_PC, m_PT;

         int ProjectionRegion(const WBFL::Geometry::Point2d& point) const;
         WBFL::Geometry::Line2d GetBackTangentLine() const;
         WBFL::Geometry::Line2d GetForwardTangentLine() const;
      };
   };
};
