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

#include <Math\Math.h>

namespace WBFL
{
   namespace COGO
   {
      class CubicSpline; // forward declaration

      /// @brief A spiral transition curve
      /// The curve radii must have the same sign (reverse curves are not supported). Positive values indicate curves to the left.
      /// Use a radius of 0.0 to indicate infinite radius (such as tangency to a straight line)
      class COORDGEOMCLASS TransitionCurve : public PathElement
      {
      private:
         TransitionCurve() = default;
         TransitionCurve(const WBFL::Geometry::Point2d& start, const Direction& startDirection, Float64 R1, Float64 R2, Float64 L, TransitionCurveType type);
         TransitionCurve(const TransitionCurve&) = default;
         TransitionCurve& operator=(const TransitionCurve&) = delete;

      public:
         ~TransitionCurve() = default;

         static std::shared_ptr<TransitionCurve> Create();
         static std::shared_ptr<TransitionCurve> Create(const WBFL::Geometry::Point2d& start, const Direction& startDirection, Float64 R1, Float64 R2, Float64 L, TransitionCurveType type);
         static std::shared_ptr<TransitionCurve> Create(const TransitionCurve& curve);

         void Init(const WBFL::Geometry::Point2d& start, const Direction& startDirection, Float64 R1, Float64 R2, Float64 L, TransitionCurveType type);

         /// @brief Returns the start point
         /// @return 
         const WBFL::Geometry::Point2d& GetStart() const;

         /// @brief Returns the tangent direction at the start of the curve
         /// @return 
         const Direction& GetStartDirection() const;

         /// @brief Returns the radius at the start of the curve (R1)
         /// @return 
         Float64 GetStartRadius() const;

         /// @brief Returns the radius at the end of the curve (R2)
         /// @return 
         Float64 GetEndRadius() const;

         /// @brief Returns the type of transition curve
         /// @return 
         TransitionCurveType GetTransitionType() const;

         /// @brief Returns the radius at the specified distance from the start of the transition curve
         /// Radius of zero indicates infinite radius
         /// @param distFromStart Location where the radius is calculated
         /// @return 
         Float64 GetRadius(Float64 distFromStart) const;

         /// @brief Returns the distance along the tangent from the start of the curve to a perpendicular offset to the end of the spiral.
         /// @image html Images/Spiral.png
         /// @return 
         Float64 GetX() const;

         /// @brief Returns the offset from the tangent to the spiral at its maximum degree of curvature measured along a perpendicular from the tangent to the end of the transition curve.
         /// @image html Images/Spiral.png
         /// @return 
         Float64 GetY() const;

         /// @brief Returns the long tangent of the spiral
         /// @image html Images/Spiral.png
         /// @return 
         Float64 GetLongTangent() const;

         /// @brief Returns the short tangent of the spiral
         /// @image html Images/Spiral.png
         /// @return 
         Float64 GetShortTangent() const;

         /// @brief Returns the intersection point of the curve tangents
         /// @return
         WBFL::Geometry::Point2d GetPI() const;

         /// @brief Returns the subtended angle of the curve
         /// @return 
         Angle GetAngle() const;

         /// @brief Returns the direction if the curve. The direction is as viewed looking ahead on station.
         /// @return 
         CurveDirection GetCurveDirection() const;

         /// @brief Returns the end point
         /// @return 
         WBFL::Geometry::Point2d GetEnd() const;

         /// @brief Returns the tangent direction at the end of the curve
         /// @return 
         Direction GetEndDirection() const;

         /// @brief Locates a point on the curve at a specified distance from Start. 
         /// If the specified distance is less than zero or if it is greater than the curve length, the point will be located on the back or forward tangent, respectively.
         /// @param distFromStart Distance from the start of the curve to the point
         /// @return 
         WBFL::Geometry::Point2d PointOnCurve(Float64 distFromStart) const;

         /// @brief Divides the curve into nParts equal length segments
         /// @param nParts Number of parts into which the curve is divided
         /// @return Vector of points at the ends of each equal length segment
         std::vector<WBFL::Geometry::Point2d> Divide(IndexType nParts) const;

         /// @brief Computes the distance along the curve from the start point to a specified point
         /// @param point 
         /// @return 
         Float64 DistanceFromStart(const WBFL::Geometry::Point2d& point) const;

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

      private:
         TransitionCurveType m_Type;
         WBFL::Geometry::Point2d m_StartPoint; // point where transition curve beings
         Direction m_StartDirection;
         Float64 m_r1; // radius at start of transition curve (use 0.0 for infinite radius) - this is the input value
         Float64 m_r2; // radius at end of transition curve (use 0.0 for infinite radius) - this is the input value
         Float64 m_L; // length of transition curve

         Float64 m_R1; // radius at start - this is the value where 0.0 is converted to Float64_Max for easier computations
         Float64 m_R2; // radius at end - this is the value where 0.0 is converted to Float64_Max for easier computations
         Float64 m_StartDirectionValue; // this is the value in the m_StartDirection object

         WBFL::Geometry::Point2d m_EndPoint;
         Direction m_EndDirection;
         WBFL::Geometry::Point2d m_PI;

         Float64 m_U; // long tangent
         Float64 m_V; // short tangent

         Float64 m_Rs; // radius at start of transition curve nearest (or at) the point of infinite radius (greatest absolute value of R1 and R2)
         Float64 m_Re; // radius at end of transition curve opposite the point of infinite radius (least absolute value of R1 and R2)
         Float64 m_A; // scale factor
         Float64 m_Ls; // length of curve from the point of infinite radius to the end of the transition curve segment
         Float64 m_SpiralAngle; // Total angle of the full spiral (from point of infinite radius to terminus of curve)
         Float64 m_StartDist; // distance from start of full spiral at point of infinite radius to start of actual curve

         Float64 m_Sign; // 1 for CCW, -1 for CW curves
         Float64 m_SignY; // Sign to correct Y values based on direction of local coordinate system

         WBFL::Geometry::Point2d m_SpiralOrigin;
         Float64 m_SpiralRotation;

         Float64 SpiralX(Float64 ls, Float64 angle) const;
         Float64 SpiralY(Float64 ls, Float64 angle) const;

         Float64 DistanceFromStartOfSpiral(Float64 distance) const;

         std::pair<Float64,WBFL::Geometry::Point2d> DoProjectPoint(const WBFL::Geometry::Point2d& point) const;

         // creates line objects for the curve tangents
         WBFL::Geometry::Line2d GetBackTangentLine() const;
         WBFL::Geometry::Line2d GetForwardTangentLine() const;

         int ProjectionRegion(const WBFL::Geometry::Point2d& point) const;

         std::shared_ptr<CubicSpline> CreateSubpathSpline(Float64 start, Float64 end, IndexType nPoints) const;

#if defined _DEBUG
         bool IsPointOnCurve(const WBFL::Geometry::Point2d& point) const;
         bool IsPointOnLine(const WBFL::Geometry::Line2d& line,const WBFL::Geometry::Point2d& point) const;
         bool TestIntersection(const WBFL::Geometry::Line2d& line,const WBFL::Geometry::Point2d& point) const;
#endif

         class CLineIntersectFunction : public WBFL::Math::Function
         {
         public:
            CLineIntersectFunction(const TransitionCurve* tc, const WBFL::Geometry::Line2d& line) :
               m_pCurve(tc), m_Line(line)
            {
            }

            Float64 Evaluate(Float64 distFromStartOfCurve) const
            {
               // output is distance between line and the point located at
               // distFromStartOfCurve

               auto point_on_curve = m_pCurve->PointOnCurve(distFromStartOfCurve);
               return m_Line.DistanceToPoint(point_on_curve);
            }

            virtual std::unique_ptr<WBFL::Math::Function> Clone() const override
            {
               return std::make_unique<CLineIntersectFunction>(m_pCurve, m_Line);
            }

         private:
            const TransitionCurve* m_pCurve;
            WBFL::Geometry::Line2d m_Line;
         };

         class CParallelLineFunction : public WBFL::Math::Function
         {
         public:
            CParallelLineFunction(const TransitionCurve* tc, const WBFL::Geometry::Line2d& line) :
               m_pCurve(tc), m_Line(line)
            {
               auto [p,v] = m_Line.GetExplicit();
               m_Angle = v.GetDirection();
            }

            Float64 Evaluate(Float64 distFromStartOfCurve) const
            {
               // trying to find location on curve where line and angle are parallel
               auto dir = m_pCurve->GetBearing(distFromStartOfCurve);

               Float64 angle = dir.GetValue();

               if (IsZero(angle) && 3 * PI_OVER_2 < m_Angle)
               {
                  angle = 2 * M_PI;
               }

               return m_Angle - angle;
            }

            virtual std::unique_ptr<WBFL::Math::Function> Clone() const override
            {
               return std::make_unique<CParallelLineFunction>(m_pCurve, m_Line);
            }

         private:
            const TransitionCurve* m_pCurve;
            Float64 m_Angle;
            WBFL::Geometry::Line2d m_Line;
         };

         class CSpiralFunction : public WBFL::Math::Function
         {
         public:
            CSpiralFunction(const TransitionCurve* tc, const WBFL::Geometry::Point2d& tp) :
               m_pCurve(tc), m_TargetPoint(tp)
            {
            }

            Float64 Evaluate(Float64 x) const
            {
               auto pnt = m_pCurve->PointOnCurve(x);

               auto dir = m_pCurve->GetNormal(x);
               
               Float64 angle = dir.GetValue();

               WBFL::Geometry::Vector2d v;
               v.SetDirection(angle);

               WBFL::Geometry::Line2d line(pnt, v);


               Float64 dist = line.DistanceToPoint(m_TargetPoint);
               return dist;
            }

            virtual std::unique_ptr<WBFL::Math::Function> Clone() const override
            {
               return std::make_unique<CSpiralFunction>(m_pCurve, m_TargetPoint);
            }

         private:
            const TransitionCurve* m_pCurve;
            WBFL::Geometry::Point2d m_TargetPoint;
         };
      };
   };
};
