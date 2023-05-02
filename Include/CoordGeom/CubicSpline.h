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
#include <CoordGeom/PathElement.h>

#include <GeomModel/Primitives.h>
#include <GeomModel/Line2d.h>
#include <GeomModel/CoordinateXform2d.h>

#include <Math/Math.h>

namespace WBFL
{
   namespace COGO
   {
      /// @brief A cubic spline consists of at least two end points and the tangent directions at the end points. Additional points between the end points can be included. 
      /// A clamped cubic spline is modeled with a series of piecewise cubic segments.
      class COORDGEOMCLASS CubicSpline : public PathElement
      {
      private:
         class SplineSegment; // forward declaration of a private nested class
         CubicSpline() = default;
         CubicSpline(const CubicSpline&) = default;
         CubicSpline& operator=(const CubicSpline&) = delete;

      public:
         static std::shared_ptr<CubicSpline> Create();
         static std::shared_ptr<CubicSpline> Create(const CubicSpline& curve);

         ~CubicSpline() = default;

         /// @brief Adds multiple points to the end of the spline
         /// @param vPoints A collection of points
         void AddPoints(const std::vector<WBFL::Geometry::Point2d>& vPoints);

         /// @brief Adds a point to the end of the spline
         /// @param x 
         /// @param y 
         void AddPoint(Float64 x, Float64 y);
         
         /// /// @brief Adds a point to the end of the spline
         /// @param p 
         void AddPoint(const WBFL::Geometry::Point2d& p);

         /// @brief Returns the number of points
         /// @return 
         IndexType GetPointCount() const;

         /// @brief Returns a point at the specified index
         /// @param idx 
         /// @return 
         const WBFL::Geometry::Point2d& GetPoint(IndexType idx) const;

         /// @brief Returns a collection of points defining the spline
         /// @return 
         const std::vector<WBFL::Geometry::Point2d>& GetPoints() const;

         /// @brief Removes all spline points
         void Clear();

         /// @brief Sets the direction of a line tangent to the spline at the start point
         /// @param direction 
         void SetStartDirection(const Direction& direction);

         /// @brief Returns the direction of a line tangent to the spline at the start point
         /// @return 
         const Direction& GetStartDirection() const;

         /// @brief Sets the direction of a line tangent to the spline at the end point
         /// @param direction 
         void SetEndDirection(const Direction& direction);

         /// @brief Returns the direction of a line tangent to the spline at the end point
         /// @return 
         const Direction& GetEndDirection() const;

         /// @brief Computes the bearing of a line tangent to the spline at a specified point.
         /// @param idx 
         /// @return 
         Direction GetBearingAtPoint(IndexType idx) const;

         /// @brief Computes the bearing of a line normal to the spline at a specified point.
         /// @param idx 
         /// @return 
         Direction GetNormalAtPoint(IndexType idx) const;

         /// @brief Determines the coordinate of a point on the spline at a specified distance from the start point.
         /// @param distFromStart 
         /// @return 
         WBFL::Geometry::Point2d PointOnCurve(Float64 distFromStart) const;

         /// @brief Computes the distance along the spline from the start point to a specified point
         /// @param idx 
         /// @return 
         Float64 DistanceFromStartAtPoint(IndexType idx) const;

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
         virtual std::tuple<WBFL::Geometry::Point2d, Float64, bool> ProjectPoint(const WBFL::Geometry::Point2d& point) const override;
         virtual std::vector<WBFL::Geometry::Point2d> Intersect(const WBFL::Geometry::Line2d& line, bool bProjectBack, bool bProjectAhead) const override;
         virtual std::vector<std::shared_ptr<PathElement>> CreateOffsetPath(Float64 offset) const override;
         virtual std::vector<std::shared_ptr<PathElement>> CreateSubpath(Float64 start, Float64 end) const override;

#if defined _UNITTEST
         /// A self-test function - returns true if passed.
         static bool TestMe(WBFL::Debug::Log& rlog);
#endif // _UNITTEST


      private:
         // These are the basic spline input parameters
         std::vector<WBFL::Geometry::Point2d> m_vPoints;
         Direction m_StartDirection;
         Direction m_EndDirection;
         
         // These are internal members that keep track of the state of spline data
         mutable bool m_bUpdateSpline{ true };
         mutable Angle m_RotationAngle;  // rotation angle between the global coordinate system and the spline coordinate system
         mutable WBFL::Geometry::CoordinateXform2d m_CoordXform; // tool used for coordinate transformation
         mutable std::vector<SplineSegment> m_SplineSegments; // individual spline elements
         
         void CreateSplineSegments() const; // builds the m_SplineSegments vector
         void UpdateSpline() const; // computes the spline coefficients (A,B,C,D) for the SplineSegment objects in m_SplineSegments

         Float64 Slope(Float64 distFromStart, bool bProjectBack, bool bProjectAhead) const; // computes the tangent slope
         std::pair<SplineSegment*,Float64> FindSplineSegment(Float64 distFromStart) const;

         void CheckValid() const; // checks to make sure a spline is valid before any spline function

#if defined _DEBUG
         void ValidateSpline() const;
#endif

         class SplineSegment
         {
         public:
            SplineSegment();
            SplineSegment(const WBFL::Geometry::Point2d& pntA, const WBFL::Geometry::Point2d& pntB);
            void Init(Float64 A, Float64 B, Float64 C, Float64 D);
            Float64 Length() const;
            Float64 Length(Float64 dx) const;
            Float64 Evaluate(Float64 x) const;
            Float64 Slope(Float64 x) const;
            std::pair<Float64,Float64> GetPoint(Float64 distance) const;
            Float64 Bearing(Float64 distance) const;
            Float64 Normal(Float64 distance) const;
            std::vector<WBFL::Geometry::Point2d> Intersect(const WBFL::Geometry::Line2d& line) const;

            WBFL::Geometry::Point2d pntA; // point at start of segment
            WBFL::Geometry::Point2d pntB; // point at end of segment

         private:
            // f(x)  =  A + Bx +  Cx^2 +  Dx^3
            // f'(x) =      B  + 2Cx   + 3Dx^2
            Float64 A{0.0}, B{ 0.0 }, C{ 0.0 }, D{ 0.0 };

            mutable bool m_bComputeLength{ true };
            mutable Float64 m_Length{ 0.0 };
         };


         class SplineSegmentLengthFunction : public WBFL::Math::Function
         {
         public:
            SplineSegmentLengthFunction(const SplineSegment& splineSegment);
            Float64 Evaluate(Float64 x) const;
            virtual std::unique_ptr<WBFL::Math::Function> Clone() const override;

         private:
            const SplineSegment& m_SplineSegment;
         };

         class SplineSegmentPointFunction : public WBFL::Math::Function
         {
         public:
            SplineSegmentPointFunction(Float64 distance, Float64 x0, const SplineSegment& splineSegment);
            Float64 Evaluate(Float64 x) const;
            virtual std::unique_ptr<WBFL::Math::Function> Clone() const override;

         private:
            Float64 m_Distance; // distance along segment where solution is sought
            Float64 m_X0; // x0
            const SplineSegment& m_SplineSegment;
         };


         class SplineSegmentProjectPointFunction : public WBFL::Math::Function
         {
         public:
            SplineSegmentProjectPointFunction(const SplineSegment& splineSegment, const WBFL::Geometry::Point2d& tp);
            Float64 Evaluate(Float64 x) const;
            virtual std::unique_ptr<WBFL::Math::Function> Clone() const override;

         private:
            const SplineSegment& m_SplineSegment;
            const WBFL::Geometry::Point2d& m_TargetPoint;
         };
      };
   };
};
