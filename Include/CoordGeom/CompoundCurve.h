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
#include <CoordGeom/CoordGeomTypes.h>
#include <CoordGeom/Direction.h>
#include <CoordGeom/PathElement.h>

#include <GeomModel/Primitives.h>
#include <GeomModel/Line2d.h>

#include <Math\Math.h>

namespace WBFL
{
   namespace COGO
   {
      class CubicSpline; // forward declaration

      /// @brief A compound curve is defined by a point on the back tangent, the intersection point of the back and forward tangents, 
      /// a point on the forward tangent, and the radius. Entry and/or exit clothoid spirals can be added to the curve by 
      /// defining their length. Input values are denoted in red in the figure below. 
      /// @image html Images/CompoundCurve.jpg
      class COORDGEOMCLASS CompoundCurve : public PathElement
      {
      private:
         CompoundCurve();
         CompoundCurve(const WBFL::Geometry::Point2d& pbt, const WBFL::Geometry::Point2d& pi, const WBFL::Geometry::Point2d& pft, Float64 radius, Float64 lsEntry = 0.0, TransitionCurveType lsEntryType = TransitionCurveType::Clothoid, Float64 lsExit = 0.0, TransitionCurveType lsExitType = TransitionCurveType::Clothoid);
         CompoundCurve(const CompoundCurve&) = default;
         CompoundCurve& operator=(const CompoundCurve&) = delete;

      public:
         enum class SpiralLocation
         {
            Entry, ///< Entry spiral at start of curve
            Exit  ///< Exit spiral at end of curve
         };

         static std::shared_ptr<CompoundCurve> Create();
         static std::shared_ptr<CompoundCurve> Create(const WBFL::Geometry::Point2d& pbt, const WBFL::Geometry::Point2d& pi, const WBFL::Geometry::Point2d& pft, Float64 radius,Float64 lsEntry=0.0,TransitionCurveType lsEntryType = TransitionCurveType::Clothoid,Float64 lsExit=0.0,TransitionCurveType lsExitType = TransitionCurveType::Clothoid);
         static std::shared_ptr<CompoundCurve> Create(const CompoundCurve& curve);

         ~CompoundCurve() = default;

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

         /// @brief Sets the spiral transition curve type
         /// @param location The spiral location
         /// @param type The transition curve type
         void SetSpiralType(SpiralLocation location, TransitionCurveType type);

         /// @brief Returns the spiral transition curve type
         /// @param location The spiral location
         /// @return 
         TransitionCurveType GetSpiralType(SpiralLocation location) const;

         /// @brief Sets the length of transition spiral
         /// @param location The spiral location
         /// @param Ls spiral length
         void SetSpiralLength(SpiralLocation location, Float64 Ls);

         /// @brief Gets the length of transition spiral
         /// @param location The spiral location
         /// @return The spiral length
         Float64 GetSpiralLength(SpiralLocation location) const;

         /// @brief Returns the direction if the curve. The direction is as viewed looking ahead on station.
         /// @return 
         CurveDirection GetCurveDirection() const;

         /// @brief Returns the angle subtended by the spiral curve
         /// @param location The spiral location
         /// @return 
         Angle GetSpiralAngle(SpiralLocation location) const;

         /// @brief Returns the angle subtended by the circular curve
         /// @return 
         Angle GetCircularCurveAngle() const;

         /// @brief Returns the total angle subtended by the compound curve
         /// @return 
         Angle GetCurveAngle() const;

         /// @brief Returns the distance along the tangent from TS (or ST) to a perpendicular offset to the end of the spiral.
         /// @image html Images/Spiral.png
         /// @param location The spiral location
         /// @return 
         Float64 GetX(SpiralLocation location) const;

         /// @brief Returns the offset from the tangent to the spiral at its maximum degree of curvature measured along a perpendicular from the tangent to SC (or CS).
         /// @image html Images/Spiral.png
         /// @param location The spiral location
         /// @return 
         Float64 GetY(SpiralLocation location) const;

         /// @brief Returns the offset distance that the entire circular curve is radially set in from the tangents to allow for spiral connections.
         /// @image html Images/Spiral.png
         /// @param location THe spiral location
         /// @return 
         Float64 GetQ(SpiralLocation location) const;

         /// @brief Returns the distance T
         /// @image html Images/Spiral.png
         /// @param location 
         /// @return 
         Float64 GetT(SpiralLocation location) const;

         /// @brief Returns the direction of the forward tangent
         /// @return 
         Direction GetForwardTangentBearing() const;

         /// @brief Returns the direction of the back tangent
         /// @return 
         Direction GetBackTangentBearing() const;

         /// @brief Returns the length of the forward tangent
         /// @return 
         Float64 GetForwardTangentLength() const;

         /// @brief Returns the length of the back tangent
         /// @return 
         Float64 GetBackTangentLength() const;

         /// @brief Returns the direction of the forward tangent to the circular curve
         /// @return 
         Direction GetCurveForwardTangentBearing() const;

         /// @brief Returns the direction of the back tangent to the circular curve
         /// @return 
         Direction GetCurveBackTangentBearing() const;

         /// @brief Returns the center point of the compound curve
         /// @return 
         WBFL::Geometry::Point2d GetCCC() const;

         /// @brief Returns the intersection point of the circular curve tangents
         /// @return 
         WBFL::Geometry::Point2d GetPCI() const;

         /// @brief Returns the intersection point of the spiral tangents
         /// @param location The spiral location
         /// @return 
         WBFL::Geometry::Point2d GetSPI(SpiralLocation location) const;

         /// @brief Returns the center point of the circular curve
         /// @return 
         WBFL::Geometry::Point2d GetCC() const;

         /// @brief Returns the spiral to circular curve point
         /// @return 
         WBFL::Geometry::Point2d GetSC() const;

         /// @brief Returns the circular curve to spiral point
         /// @return 
         WBFL::Geometry::Point2d GetCS() const;

         /// @brief Returns the tangent to spiral point
         /// @return 
         WBFL::Geometry::Point2d GetTS() const;

         /// @brief Returns the spiral to tangent point
         /// @return 
         WBFL::Geometry::Point2d GetST() const;

         /// @brief Returns the chord length of the circular curve
         /// @image html Images/CircularCurve.jpg
         /// @return 
         Float64 GetChord() const;

         /// @brief Returns the length of the circular curve tangent
         /// @image html Images/CircularCurve.jpg
         /// @return 
         Float64 GetTangent() const;

         /// @brief Returns the length of the circular curve mid-ordinate
         /// @image html Images/CircularCurve.jpg
         /// @return 
         Float64 GetMidOrdinate() const;

         /// @brief Returns the length of the circular curve external
         /// @image html Images/CircularCurve.jpg
         /// @return 
         Float64 GetExternal() const;

         /// @brief Returns the deviation angle of the spiral
         /// @image html Images/Spiral.png
         /// @param location The spiral location
         /// @return 
         Angle GetDE(SpiralLocation location) const;

         /// @brief  Returns the difference between DE and DF
         /// @image html Images/Spiral.png
         /// @param location The spiral location
         /// @return 
         Angle GetDH(SpiralLocation location) const;

         /// @brief Returns the deflection angle of the spiral
         /// @image html Images/Spiral.png
         /// @param location The spiral location
         /// @return 
         Angle GetDF(SpiralLocation location) const;

         /// @brief Returns the short tangent of the spiral
         /// @image html Images/Spiral.png
         /// @param location The spiral location
         /// @return 
         Float64 GetShortTangent(SpiralLocation location) const;

         /// @brief Returns the long tangent of the spiral
         /// @image html Images/Spiral.png
         /// @param location The spiral location
         /// @return 
         Float64 GetLongTangent(SpiralLocation location) const;

         /// @brief Returns the chord length of the spiral
         /// @param location The spiral location
         /// @return 
         Float64 GetSpiralChord(SpiralLocation location) const;

         /// @brief Returns the total length of the curve
         /// @return 
         Float64 GetTotalLength() const;

         /// @brief Returns the length of the circular curve
         /// @return 
         Float64 GetCurveLength() const;

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

         /// @brief Locates a point on the curve at a specified distance from TS. If the specified distance is less than zero or if it is greater than the curve length, the point will be located on the back or forward tangent, respectively.
         /// @param distFromStart Distance from the start of the curve
         /// @return 
         WBFL::Geometry::Point2d PointOnCurve(Float64 distFromStart) const;

         /// @brief Divides the curve into nParts equal length segments
         /// @param nParts Number of parts into which the curve is divided
         /// @return Vector of points at the ends of each equal length segment
         std::vector<WBFL::Geometry::Point2d> Divide(IndexType nParts) const;

         //
         // PathElement methods
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
         WBFL::Geometry::Point2d m_PBT, m_PI, m_PFT;
         Float64 m_Radius;
         Float64 m_LsEntry, m_LsExit;
         TransitionCurveType m_LsEntryType, m_LsExitType;

         mutable WBFL::Geometry::Point2d m_TS, m_ST;

         Float64 SpiralX(Float64 ls, Float64 angle) const;
         Float64 SpiralY(Float64 ls, Float64 angle) const;
         WBFL::Geometry::Point2d PointOnEntrySpiral(Float64 x, Float64 y) const;
         WBFL::Geometry::Point2d PointOnExitSpiral(Float64 x, Float64 y) const;
         WBFL::Geometry::Point2d PointOnEntrySpiral(Float64 distFromTS) const;
         WBFL::Geometry::Point2d PointOnExitSpiral(Float64 distFromST) const;
         std::pair<Float64, WBFL::Geometry::Point2d> ProjectPointOnEntrySpiral(const WBFL::Geometry::Point2d& point) const;
         std::pair<Float64, WBFL::Geometry::Point2d> ProjectPointOnExitSpiral(const WBFL::Geometry::Point2d& point) const;

         int ProjectionRegion(const WBFL::Geometry::Point2d& point) const;
         WBFL::Geometry::Line2d GetBackTangentLine() const;
         WBFL::Geometry::Line2d GetForwardTangentLine() const;

         std::shared_ptr<CubicSpline> CreateSubpathSpline(Float64 start, Float64 end, IndexType nPoints) const;

#if defined _DEBUG
         bool IsPointOnCurve(const WBFL::Geometry::Point2d& point) const;
         bool IsPointOnLine(const WBFL::Geometry::Line2d& line, const WBFL::Geometry::Point2d& point) const;
         bool TestIntersection(const WBFL::Geometry::Line2d& line, const WBFL::Geometry::Point2d& point) const;
#endif

         class CEntrySpiralFunction : public WBFL::Math::Function
         {
         public:
            CEntrySpiralFunction(const CompoundCurve* hc, const WBFL::Geometry::Point2d& tp) :
               m_pCurve(hc), m_TargetPoint(tp)
            {
            }

            Float64 Evaluate(Float64 x) const
            {
               auto pnt = m_pCurve->PointOnEntrySpiral(x);
               auto normal = m_pCurve->GetNormal(x);

               WBFL::Geometry::Vector2d v(1.0, normal);
               WBFL::Geometry::Line2d l(pnt, v);

               auto offset = l.DistanceToPoint(m_TargetPoint);
               return offset;
            }

            virtual std::unique_ptr<WBFL::Math::Function> Clone() const override
            {
               return std::make_unique<CEntrySpiralFunction>(m_pCurve, m_TargetPoint);
            }

         private:
            const CompoundCurve* m_pCurve;
            WBFL::Geometry::Point2d  m_TargetPoint;
         };


         class CExitSpiralFunction : public WBFL::Math::Function
         {
         public:
            CExitSpiralFunction(const CompoundCurve* hc, const WBFL::Geometry::Point2d& tp) :
               m_pCurve(hc), m_TargetPoint(tp)
            {
            }

            Float64 Evaluate(Float64 x) const
            {
               auto pnt = m_pCurve->PointOnExitSpiral(x);

               Float64 Lt = m_pCurve->GetTotalLength();
               auto normal = m_pCurve->GetNormal(Lt - x);

               WBFL::Geometry::Vector2d v(1.0, normal);
               WBFL::Geometry::Line2d l(pnt, v);

               auto offset = l.DistanceToPoint(m_TargetPoint);
               return offset;
            }

            virtual std::unique_ptr<WBFL::Math::Function> Clone() const override
            {
               return std::make_unique<CExitSpiralFunction>(m_pCurve, m_TargetPoint);
            }

         private:
            const CompoundCurve* m_pCurve;
            WBFL::Geometry::Point2d  m_TargetPoint;
         };

         class CLineIntersectFunction : public WBFL::Math::Function
         {
         public:
            CLineIntersectFunction(const CompoundCurve* hc, const WBFL::Geometry::Line2d& line) :
               m_pCurve(hc), m_Line(line)
            {
            }

            Float64 Evaluate(Float64 distFromStartOfCurve) const
            {
               // output is distance between line and the point located at
               // distFromStartOfCurve

               auto point_on_curve = m_pCurve->PointOnCurve(distFromStartOfCurve);

               Float64 offset = -1*m_Line.DistanceToPoint(point_on_curve);
               return offset;
            }

            virtual std::unique_ptr< WBFL::Math::Function> Clone() const override
            {
               return std::make_unique<CLineIntersectFunction>(m_pCurve, m_Line);
            }

         private:
            const CompoundCurve* m_pCurve;
            WBFL::Geometry::Line2d m_Line;
         };

         class CParallelLineFunction : public WBFL::Math::Function
         {
         public:
            CParallelLineFunction(const CompoundCurve* hc, const WBFL::Geometry::Line2d& line) :
               m_pCurve(hc), m_Line(line)
            {
               WBFL::Geometry::Point2d p;
               std::tie(p,m_Nline) = m_Line.GetExplicit();
            }

            Float64 Evaluate(Float64 distFromStartOfCurve) const
            {
               // trying to find location on curve where line and angle are parallel
               auto normal = m_pCurve->GetNormal(distFromStartOfCurve);

               WBFL::Geometry::Vector2d n(1.0, normal);

               auto dot = m_Nline.Dot(n);

               return dot;
            }

            virtual std::unique_ptr<WBFL::Math::Function> Clone() const override
            {
               return std::make_unique<CParallelLineFunction>(m_pCurve, m_Line);
            }

         private:
            const CompoundCurve* m_pCurve;
            WBFL::Geometry::Line2d m_Line;
            WBFL::Geometry::Vector2d m_Nline;
         };
      };
   };
};
