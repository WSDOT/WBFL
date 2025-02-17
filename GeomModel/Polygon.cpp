///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
// Copyright � 1999-2025  Washington State Department of Transportation
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

#include <GeomModel/GeomModelLib.h>
#include <GeomModel/Polygon.h>
#include <GeomModel/LineSegment2d.h>
#include <GeomModel/GeomOp2d.h>
#include <MathEx.h>
#include <stdexcept>
#include <algorithm>

using namespace WBFL::Geometry;

inline IndexType GetIndex(IndexType idx, const std::vector<Point2d>& container, Polygon::Symmetry symmetry)
{
   return symmetry == Polygon::Symmetry::None || idx < container.size() ? idx : 2*(container.size() - 1) - idx;
}

inline bool IsValidIndex(IndexType idx, const std::vector<Point2d>& container, Polygon::Symmetry symmetry)
{
   return GetIndex(idx, container, symmetry) < container.size();
}

inline void _RemoveDuplicatePoints(std::vector<Point2d>& vPoints)
{
   vPoints.erase(std::unique(vPoints.begin(), vPoints.end()), vPoints.end()); // remove adjacent duplications
}

Polygon::Polygon(std::shared_ptr<Point2d>& hookPnt) :
   ShapeImpl(hookPnt)
{
}

void Polygon::SetSymmetry(Polygon::Symmetry sym,Float64 axis)
{
   m_Symmetry = sym;
   m_SymmetryAxis = axis;
}

Polygon::Symmetry Polygon::GetSymmetry() const
{
   return m_Symmetry;
}

Float64 Polygon::GetSymmetryAxis() const
{
   return m_SymmetryAxis;
}

void Polygon::AddPoint(Float64 x, Float64 y)
{
   CHECK(isfinite(x)); CHECK(isfinite(y));
   if (m_Points.empty())
      GetHookPoint()->Move(x, y);

   m_Points.emplace_back(x, y);
   m_bIsDirty = true;
}

void Polygon::AddPoint(const Point2d& p)
{
   AddPoint(p.X(), p.Y());
}

void Polygon::AddPoints(const std::vector<Point2d>& points)
{
   if (m_Points.empty() && !points.empty())
      GetHookPoint()->Move(points.front());

   m_Points.insert(m_Points.begin(), points.cbegin(), points.cend());
   m_bIsDirty = true;
}

void Polygon::SetPoints(const std::vector<Point2d>& points)
{
   if (m_Points.empty() && !points.empty())
      GetHookPoint()->Move(points.front());

   m_Points = points;
   m_bIsDirty = true;
}

void Polygon::Clear()
{
   m_Points.clear();
   m_Properties.Clear();
   m_BoundingBox.SetNull();
   m_Perimeter = 0.0;
   GetHookPoint()->Move(0,0);
   m_bIsDirty = true;
}

void Polygon::RemovePoint(IndexType idx)
{
   if (IsValidIndex(idx,m_Points,m_Symmetry))
   {
      m_Points.erase(m_Points.begin() + GetIndex(idx,m_Points,m_Symmetry));
      if (idx == 0)
      {
         if (m_Points.empty())
            GetHookPoint()->Move(0,0);
         else
            GetHookPoint()->Move(m_Points.front());
      }

      m_bIsDirty = true;
   }
   else
   {
      THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);
   }
}

Point2d Polygon::GetPoint(IndexType idx) const
{
   UpdatePoints();
   if (IsValidIndex(idx, m_Points, m_Symmetry))
   {
      Point2d p = m_Points[GetIndex(idx, m_Points, m_Symmetry)];
      if (m_Symmetry != Symmetry::None && m_Points.size() <= idx)
      {
         p = GetMirroredPoint(p);
      }
      return p;
   }
   else
   {
      THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);
   }
}

IndexType Polygon::GetCount() const
{
   return (m_Symmetry == Symmetry::None ? m_Points.size() : 2*m_Points.size());
}

void Polygon::ReplacePoint(IndexType idx, Float64 x, Float64 y)
{
   if (idx < m_Points.size())
   {
      m_Points[idx].Move(x,y);
      if (idx == 0)
         GetHookPoint()->Move(x, y);

      m_bIsDirty = true;
   }
   else
   {
      THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);
   }
}

void Polygon::ReplacePoint(IndexType idx,const Point2d& p)
{
   ReplacePoint(idx, p.X(), p.Y());
}

void Polygon::RemoveDuplicatePoints()
{
   _RemoveDuplicatePoints(m_Points);
}

std::vector<Point2d> Polygon::GetPolyPoints() const
{
   UpdatePoints();
   if (m_Symmetry == Symmetry::None)
   {
      return m_Points;
   }
   else
   {
      std::vector<Point2d> points;
      GetAllPoints(&points);
      return points;
   }
}

ShapeProperties Polygon::GetProperties() const
{
   UpdateProperties();
   return m_Properties;
}

Rect2d Polygon::GetBoundingBox() const
{
   UpdateProperties();
   return m_BoundingBox;
}

bool Polygon::PointInShape(const Point2d& point) const
{
   if (m_Symmetry == Symmetry::X)
   {
      return PointInShape_Private(point) || PointInShape_Private(Point2d(point.X(), -point.Y()));
   }
   else if (m_Symmetry == Symmetry::Y)
   {
      return PointInShape_Private(point) || PointInShape_Private(Point2d(-point.X(), point.Y()));
   }
   else
   {
      return PointInShape_Private(point);
   }
}

Float64 Polygon::GetPerimeter() const
{
   UpdateProperties();
   return m_Perimeter;
}

void Polygon::DoOffset(const Size2d& delta)
{
   std::for_each(m_Points.begin(), m_Points.end(), [&](auto& point) {point.Offset(delta); });
   if(!m_Points.empty()) GetHookPoint()->Offset(delta);
   
   if (m_Symmetry == Symmetry::X)
      m_SymmetryAxis += delta.Dy();
   else if (m_Symmetry == Symmetry::Y)
      m_SymmetryAxis += delta.Dx();

   m_bIsDirty = true;

#if defined _DEBUG
   if (!m_Points.empty())
   {
      CHECK(*GetHookPoint() == m_Points.front());
   }
#endif
}

void Polygon::DoRotate(const Point2d& center, Float64 angle)
{
   if (m_Symmetry != Symmetry::None)
   {
      // rotation kills symmetry
      // convert this to a full polygon (no symmetry)
      std::vector<Point2d> points;
      GetAllPoints(&points);
      m_Points = points;
      m_Symmetry = Symmetry::None;
      m_SymmetryAxis = 0.0;
   }

   std::for_each(m_Points.begin(), m_Points.end(), [&](auto& point) {point.Rotate(center, angle); });
   if (!m_Points.empty()) GetHookPoint()->Rotate(center, angle);
   m_bIsDirty = true;

#if defined _DEBUG
   if (!m_Points.empty())
   {
      CHECK(*GetHookPoint() == m_Points.front());
   }
#endif
}

std::unique_ptr<Shape> Polygon::CreateClone() const
{
   return std::make_unique<Polygon>(*this);
}

std::unique_ptr<Shape> Polygon::CreateClippedShape(const Line2d& line, Line2d::Side side) const
{
   if (m_Symmetry == Symmetry::None)
   {
      return CreateClippedShape_Private(line, side, m_Points);
   }
   else
   {
      // Clipping symmetric shapes is complicated and often results in unsymmetrical shapes.
      // To make life easy, create the fully populated vector of points and operate as if the
      // shape is not symmetric
      std::vector<Point2d> points;
      GetAllPoints(&points);
      return CreateClippedShape_Private(line, side, points);
   }
}

std::unique_ptr<Shape> Polygon::CreateClippedShape(const Rect2d& r, Shape::ClipRegion region) const
{
   // Before we do anything, make sure there is a chance for this shape to be clipped
   // Check if this shape is inside, outside, or intersects with the clipping rectangle
   Rect2d bounding_box = GetBoundingBox();
   if (bounding_box.IsNull())
      return nullptr;

   Rect2d::RelPosition pos = r.GetPosition(bounding_box);
   if (pos == Rect2d::RelPosition::Outside)
   {
      // the entire shape is outside of the clipping rectangle so nothing will remain after clipping
      return std::unique_ptr<Shape>();
   }
   else if (pos == Rect2d::RelPosition::Contains)
   {
      // the entire shape is inside the clipping rectangle so the entire shape will remain after clipping
      return CreateClone();
   }

   // this shape will be clipped

   Line2d::Side side(region == Shape::ClipRegion::In ? Line2d::Side::Left : Line2d::Side::Right);

   using ClippedShape = std::unique_ptr<Shape>;

   // Clip by consecutively clipping against each edge of the rectangle

   // clip with top edge of clipping rectangle
   ClippedShape clip_top;
   if (r.Top() < bounding_box.Top())
      clip_top = CreateClippedShape(Line2d(r.TopLeft(), r.TopRight()), side);
   else
      clip_top = CreateClone();

   CHECK(clip_top != nullptr);

   // clip with right edge of clipping rectangle
   ClippedShape clip_right;
   if (r.Right() < bounding_box.Right())
      clip_right = clip_top->CreateClippedShape(Line2d(r.TopRight(), r.BottomRight()), side);
   else
      clip_right.swap(clip_top);

   CHECK(clip_right != nullptr);

   // clip with bottom edge of clipping rectangle
   ClippedShape clip_bottom;
   if (bounding_box.Bottom() < r.Bottom())
      clip_bottom = clip_right->CreateClippedShape(Line2d(r.BottomRight(), r.BottomLeft()), side);
   else
      clip_bottom.swap(clip_right);

   CHECK(clip_bottom != nullptr);

   // clip with left edge of clipping rectangle
   ClippedShape clip_left;
   if (bounding_box.Left() < r.Left())
      clip_left = clip_bottom->CreateClippedShape(Line2d(r.BottomLeft(), r.TopLeft()), side);
   else
      clip_left.swap(clip_bottom);

   return clip_left;
}

Float64 Polygon::GetFurthestDistance(const Line2d& line, Line2d::Side side) const
{
   auto [furthestPoint, furthestDistance] = GetFurthestPoint(line, side);
   return furthestDistance;
}

std::pair<Point2d,Float64> Polygon::GetFurthestPoint(const Line2d& line, Line2d::Side side) const
{
   // need to determine which side of line each point is on. Implicit rep of line has normal
   // vector which always points left.
   auto [c,n] = line.GetImplicit();

   // change n to point toward desired side of line
   if (Line2d::Side::Right == side)
      n = -n;

   // loop over all points to determine farthest point.
   Float64 max_dist = -Float64_Max;
   IndexType idx = INVALID_INDEX; // index of the point furthest from the line
   bool bIsSymPoint = false; // if true, the furthest point isn't m_Point[idx] .... it is the symmetrical version of that point
   for (const auto& point : m_Points)
   {
      // get point on line closest to point.
      bool bSymPoint = false;
      Point2d nearest = line.PointOnLineNearest(point);
      Float64 dist = point.Distance(nearest);  // always positive
      Vector2d vec(point - nearest);

      // Determine if point is on desired side or other side.
      // Create a vector from point on line to point.
      // if dot product with n is positive, point is on left
      Float64 dot = n.Dot(vec);
      if (dot < 0)  dist = -dist; // point on other side of line (negative direction)
      
      if (m_Symmetry == Symmetry::X || m_Symmetry == Symmetry::Y)
      {
         Float64 xSign = m_Symmetry == Symmetry::X ? 1 : -1;
         Float64 ySign = m_Symmetry == Symmetry::Y ? 1 : -1;
         Point2d point2(xSign * point.X(), ySign * point.Y());
         Point2d nearest2 = line.PointOnLineNearest(point2);
         Float64 dist2 = point2.Distance(nearest2);
         Vector2d vec2(point2 - nearest2);
         Float64 dot2 = n.Dot(vec2);
         if (dot2 < 0) dist2 = -dist2; // point on other side of line (negative direction)

         if (dist <= dist2)
         {
            // the symmetrical point is furthest
            bSymPoint = true;
            dist = dist2;
         }
      }

      if (max_dist < dist)
      {
         bIsSymPoint = bSymPoint;
         idx = &point - &m_Points[0]; // a little pointer arithmetic to get the index
         max_dist = dist;
      }
   }

   CHECK(idx != INVALID_INDEX && idx < m_Points.size());
   auto furthestPoint = m_Points[idx];
   if (bIsSymPoint)
   {
      Float64 xSign = m_Symmetry == Symmetry::X ? 1 : -1;
      Float64 ySign = m_Symmetry == Symmetry::Y ? 1 : -1;
      furthestPoint.X() *= xSign;
      furthestPoint.Y() *= ySign;
   }
   auto furthestDistance = max_dist;
   return std::make_pair(furthestPoint, furthestDistance);
}

void Polygon::Reflect(const Line2d& line)
{
   // this is probably not the best implementation because it destroys symmetry, but it is easiest
   auto points = GetPolyPoints();
   m_Points.clear();
   for (auto& point : points)
   {
      m_Points.emplace_back(GeometricOperations::ReflectPointAcrossLine(point, line));
   }
   m_Symmetry = Symmetry::None;
}

void Polygon::UpdateProperties() const
{
   if (!m_bIsDirty) return;

   ASSERTVALID;

   // Initialize and check for null polygon.
   Float64 area = 0.0;
   Float64 ixx = 0.0;
   Float64 iyy = 0.0;
   Float64 ixy = 0.0;
   Point2d centroid(0,0);
   m_Perimeter = 0;

   m_Properties.SetProperties(area, centroid, ixx, iyy, ixy, 0,0,0,0);

   UpdatePoints();

   if (m_Points.size() < 3)
   {
      if (m_Points.empty())
      {
         m_BoundingBox.SetNull();
      }
      else
      {
         Float64 left = Float64_Max;
         Float64 right = -Float64_Max;
         Float64 top = -Float64_Max;
         Float64 bottom = Float64_Max;

         for (const auto& point : m_Points)
         {
            Float64 x = point.X();
            Float64 y = point.Y();

            left = Min(x, left);
            right = Max(x, right);
            bottom = Min(y, bottom);
            top = Max(y, top);
         }

         m_BoundingBox.Set(left, bottom, right, top);
      }

      return;
   }

   Float64 x0, y0;
   Float64 x1, y1;
   Float64 dy, dx;
   Float64 ar, at;
   Float64 g_ixx = 0, g_iyy = 0, g_ixy = 0; // moments of inertia about the global axes
   Float64 c_ixx = 0, c_iyy = 0, c_ixy = 0; // moments of inertia about the centroid
   Float64 area_local = 0;
   Point2d cg;
   
   // loop over all points - make sure of closure

   auto ip0 = m_Points.begin();
   auto ip1 = ip0;
   ip1++;

   Float64 left = (*ip0).X();
   Float64 right = (*ip0).X();
   Float64 top = (*ip0).Y();
   Float64 bottom = (*ip0).Y();

   bool loop = true, last_round = false;
   while (loop)
   {
      x0 = (*ip0).X();
      y0 = (*ip0).Y();
      x1 = (*ip1).X();
      y1 = (*ip1).Y();

      // record extreme points for bounding box
      left = Min(x1, left);
      right = Max(x1, right);
      top = Max(y1, top);
      bottom = Min(y1, bottom);

      dx = x1 - x0;
      dy = y1 - y0;

      if (!last_round || (last_round && m_Symmetry == Symmetry::None))
      {
         m_Perimeter += sqrt(dx * dx + dy * dy);
      }

      ar = dx * y0;
      at = 0.5 * dy * dx;

      area_local += (ar + at);

      // Centroid
      cg.X() += ar * (x1 + x0) / 2 + at * (2 * dx / 3 + x0);
      cg.Y() += ar * (y0 / 2) + at * (dy / 3 + y0);

      // Inertia about global axes
      g_ixx += (y0) * (y0) * (y0)*dx / 12 + ar * (y0 / 2) * (y0 / 2) +
         dy * dy * dy * dx / 36 + at * (dy / 3 + y0) * (dy / 3 + y0);

      g_iyy += (y0)*dx * dx * dx / 12 + ar * (x0 + dx / 2) * (x0 + dx / 2) +
         dy * dx * dx * dx / 36 + at * (2 * dx / 3 + x0) * (2 * dx / 3 + x0);

      g_ixy += ar * (y0 / 2) * (x0 + dx / 2) +
         at * (dy / 3 + y0) * (2 * dx / 3 + x0) +
         dy * dy * dx * dx / 72;

      // loop termination test - need to go one more iteration if loop is not closed
      if (last_round)
      {
         // just finished closure loop. time to quit
         loop = false;
      }
      else
      {
         // increment for next go-around
         ip0 = ip1;
         ip1++;

         if (ip1 == m_Points.end())
         {
            // check if extra loop is required for closure
            ip1 = m_Points.begin();
            const Point2d& lastp = (*ip0);   // convert to points here to avoid ugliness
            const Point2d& beginp = (*ip1);
            if (lastp != beginp)
            {
               // one more loop to close polygon
               last_round = true;
            }
            else
            {
               // loop is closed - just quit
               loop = false;
            }
         }
      }
   }     // while

   // If the Polygon has no area_local, then there is nothing left to compute.
   if (IsZero(area_local))
   {
      cg.X() = (left + right) / 2.0;
      cg.Y() = (top + bottom) / 2.0;

      m_Properties.SetProperties(0, cg, 0, 0, 0, cg.X() - left, cg.Y() - bottom, right - cg.X(), top - cg.Y());
      m_BoundingBox.Set(left, bottom, right, top);
   }
   else
   {
      // Finish centroid
      cg.X() /= area_local;
      cg.Y() /= area_local;

      // Inertia about local axes
      c_ixx = g_ixx - area_local * cg.Y() * cg.Y();
      c_iyy = g_iyy - area_local * cg.X() * cg.X();
      c_ixy = g_ixy - area_local * cg.X() * cg.Y();

      // If the points are defined counter-clockwise, everything comes out -1 of what it should be
      if (area_local < 0)
      {
         area_local *= -1;
         c_ixx *= -1;
         c_iyy *= -1;
         c_ixy *= -1;

         g_ixx *= -1;
         g_iyy *= -1;
         g_ixy *= -1;
      }

      if (m_Symmetry == Symmetry::X)
      {
         // the X-axis is an axis of symmetry, so far the properties are for half the shape
         Float64 A = 2 * area_local;
         Float64 cgx = cg.X();
         Float64 cgy = cg.Y();

         Float64 CGx = cgx;
         Float64 CGy = m_SymmetryAxis;

         c_ixx = 2 * (c_ixx + area_local * (CGy - cgy) * (CGy - cgy));
         c_iyy = 2 * (c_iyy + area_local * (CGx - cgx) * (CGx - cgx));
         c_ixy = 0; // Ixy is 0 for symmetric sections

         area_local = A;
         cg.Move(CGx, CGy);

         if (IsLT(m_SymmetryAxis,top))
            bottom = top - 2*(top - m_SymmetryAxis);
         else
            top = bottom + 2*(m_SymmetryAxis - bottom);

         m_Perimeter *= 2;
      }
      else if (m_Symmetry == Symmetry::Y)
      {
         // the Y-axis is an axis of symmetry, so far the properties are for half the shape
         Float64 A = 2 * area_local;
         Float64 cgx = cg.X();
         Float64 cgy = cg.Y();

         Float64 CGx = m_SymmetryAxis;
         Float64 CGy = cgy;

         c_ixx = 2 * (c_ixx + area_local * (CGy-cgy) * (CGy - cgy));
         c_iyy = 2 * (c_iyy + area_local * (CGx-cgx) * (CGx - cgx));
         c_ixy = 0; // Ixy is 0 for symmetric sections

         area_local = A;
         cg.Move(CGx, CGy);

         if (IsLT(m_SymmetryAxis,right))
            left = right - 2 * (right - m_SymmetryAxis);
         else
            right = left + 2 * (m_SymmetryAxis - left);

         m_Perimeter *= 2;
      }

      m_Properties.SetProperties(area_local, cg, c_ixx, c_iyy, c_ixy, cg.X() - left,cg.Y() - bottom,right -cg.X(), top - cg.Y());
      m_BoundingBox.Set(left, bottom, right, top);
   }

   m_bIsDirty = false;
}

void Polygon::UpdatePoints() const
{
   if (m_Points.empty() || !IsHookPointChanged() ) return;

   // hook point is not in the same location as the first point. that means the hook point has been moved
   // update the point collection
   Size2d size = *GetHookPoint() - m_Points.front();
   std::for_each(m_Points.begin(),m_Points.end(), [&](auto& p) { return p.Offset(size); });
   ShapeCurrentWithHookPoint();
}

bool Polygon::PointInShape_Private(const Point2d& point) const
{
   // Reference:
   // "Use of the residue theorem in locating points within an
   // arbitrary multiply-connected region"
   // G. Steven Gipson
   // Adv. Eng. Software, 1986, Vol. 8, No. 2

   IndexType num_points = m_Points.size();
   if (num_points < 3)
      return false;   // points and lines can't contain anything.

   const Float64 angular_tolerance = TWO_PI * 1.0e-02; // 2*pi*10^-2
   // this is probably the correct way to do it, but we'll approximate for now
   Rect2d rect = GetBoundingBox();
   Float64 edgelen = min(rect.Width(), rect.Height());
   Float64 dist = 2 * rect.TopLeft().Distance(rect.BottomRight());
   if (IsZero(dist))
      return false;

   Float64 boundary_tolerance = edgelen / dist;
   boundary_tolerance = min(1e-06, boundary_tolerance);

   Float64 sum = 0;

   auto ip0 = m_Points.begin();
   auto ip1 = ip0;
   ip1++;
   bool loop = true, last_round = false;
   while (loop)
   {
      Float64 x0 = (*ip0).X();
      Float64 y0 = (*ip0).Y();
      Float64 x1 = (*ip1).X();
      Float64 y1 = (*ip1).Y();

      // no calculation if points are coincident
      if (x0 != x1 || y0 != y1)
      {

         // Compute components of two vectors formed by
         // joining point in question with endpoints of 
         // boundary segment
         Float64 ax = x0 - point.X();
         Float64 ay = y0 - point.Y();
         Float64 bx = x1 - point.X();
         Float64 by = y1 - point.Y();

         // Form cross product of the vectors to determine
         // the sign of the angular segment
         Float64 cp = ax * by - ay * bx;
         Float64 sign = cp < 0 ? -1 : 1;

         // Test for vanishing cross product in case the test point is on the boundary.
         //
         // The line segment is used to make sure the point is actually 
         // contained in the line segment, and not a projection of the line segment
         if (IsZero(fabs(cp), boundary_tolerance) && LineSegment2d(Point2d(x0, y0), Point2d(x1, y1)).ContainsPoint(point))
         {
            // if the point is on the symmetry boundary, it may be inside the shape
            if (
               (m_Symmetry == Symmetry::X && IsEqual(y0, m_SymmetryAxis) && IsEqual(y1, m_SymmetryAxis)) ||
               (m_Symmetry == Symmetry::Y && IsEqual(x0, m_SymmetryAxis) && IsEqual(x1, m_SymmetryAxis))
               )
            {
               return true; // point is on a symmetry boundary edge so by definition, it is in the shape
            }
            else
            {
               return false; // not on the symmetry boundary so it must be on the edge so the point is not in the shape
            }
         }

         // Compute dot product of two vectors for purpose of obtaining
         // the actual angle subtended by the boundary increment.
         Float64  dot = ax * bx + ay * by;
         Float64  A2 = ax * ax + ay * ay;
         Float64  B2 = bx * bx + by * by;
         Float64  prod = A2 * B2;

         // Compute angle
         Float64  angle = 0;
         if (!IsZero(prod), 1.0e-16)
         {
            Float64 x = dot / sqrt(prod);
            if (IsZero(x - 1.0))
               x = 1.0;

            angle = acos(x);
         }

         // Add angle to running sum
         sum += sign * angle;
      }

      // loop termination test - need to go one more iteration if loop is not closed
      if (last_round)
      {
         // just finished closure loop. time to quit
         loop = false;
      }
      else
      {
         // increment for next go-around
         ip0 = ip1;
         ip1++;
         if (ip1 == m_Points.end())
         {
            // check if extra loop is required for closure
            ip1 = m_Points.begin();
            Point2d lastp = (*ip0);   // convert to points here to avoid ugliness
            Point2d beginp = (*ip1);
            if (lastp != beginp)
            {
               // one more loop to close polygon
               last_round = true;
            }
            else
            {
               // loop is closed - just quit
               loop = false;
            }
         }
      }
   }

   // Clean up round off errors in sum and determine if the point
   // is in or out.
   sum /= TWO_PI; // ( 1/2*PI )

   bool contained{false};

   if (IsEqual(sum, -1., angular_tolerance) || IsEqual(sum, 1., angular_tolerance))
      contained = true;
   else if (IsZero(sum, angular_tolerance))
      contained = false;
   else
   {
      CHECKX(false, _T("This should never happen"));
   }

   return contained;
}

Point2d Polygon::GetMirroredPoint(const Point2d& point) const
{
   Float64 xSign = m_Symmetry == Symmetry::X ? 1 : -1;
   Float64 ySign = m_Symmetry == Symmetry::Y ? 1 : -1;
   Float64 xOffset = m_Symmetry == Symmetry::X ? 0 : m_SymmetryAxis;
   Float64 yOffset = m_Symmetry == Symmetry::Y ? 0 : m_SymmetryAxis;
   return Point2d(xSign * (point.X() - xOffset) + xOffset, ySign * (point.Y() - yOffset) + yOffset);
}

void Polygon::GetAllPoints(std::vector<Point2d>* points) const
{
   CHECK(m_Symmetry != Symmetry::None);

   *points = m_Points;
   Float64 xOffset = m_Symmetry == Symmetry::X ? 0 : m_SymmetryAxis;
   Float64 yOffset = m_Symmetry == Symmetry::Y ? 0 : m_SymmetryAxis;

   auto iter = m_Points.rbegin();
   auto end = m_Points.rend();
   for (; iter != end; iter++)
   {
      // working in reverse order, add the mirrored points to the vector of points
      // don't mirror points that are on the axis of symmetry
      const auto& point(*iter);
      if( (m_Symmetry == Symmetry::X && !IsEqual(point.Y(),m_SymmetryAxis))
          or
          (m_Symmetry == Symmetry::Y && !IsEqual(point.X(), m_SymmetryAxis))
         )
      {
         points->emplace_back(GetMirroredPoint(point));
      }
   }

   // close the polygon if first and last point are different
   if (points->front() != points->back())
   {
      points->emplace_back(points->front());
   }
}

std::unique_ptr<Shape> Polygon::CreateClippedShape_Private(const Line2d& line, Line2d::Side side, const std::vector<Point2d>& points) const
{
   // could optimize this routine to work with Line2d and LineSegment2d, but 
   // would not likely gain much.
   Point2d  pnt_b;

   auto [pnt_a,dir] = line.GetExplicit();  // point on the line and direction vector
   if (side == Line2d::Side::Right)
   {
      pnt_b = pnt_a.OffsetBy(dir.X(), dir.Y());
   }
   else
   {
      pnt_b = pnt_a.OffsetBy(-dir.X(), -dir.Y());
   }

   Float64 dx, dy; // components of the direction vector of the clipping line
   Float64 nx, ny; // components of a vector normal to the clipping line
   Float64 s;      // dot product of the normal vector and the position vector
                  // of this Polygon

   // If the polyPolygon isn't at least a triangle, just get the heck out of here.
   IndexType nPoints = points.size();
   if (nPoints < 3)
      return nullptr;

   // create an empty clipped Polygon - return empty if need be
   std::unique_ptr<Polygon> clipped_Polygon(std::make_unique<Polygon>());
   clipped_Polygon->m_Points.reserve(nPoints + 1);

   dx = pnt_b.X() - pnt_a.X();
   dy = pnt_b.Y() - pnt_a.Y();

   nx = -dy;
   ny = dx;

   // get the vector of points from the Polygon and make sure that it's closed
   std::vector<Point2d> my_points(points);
   if (my_points.front() != my_points.back()) my_points.emplace_back(my_points.front());

   Point2d last_added;
   bool    was_last_added = false;

   auto begin = my_points.begin();
   auto end = my_points.end();
   bool current_out;

   Point2d last = *begin++;
   s = nx * (last.X() - pnt_a.X()) + ny * (last.Y() - pnt_a.Y());

   bool last_out = (s < 0) ? true : false;

   if (!last_out)
   {
      last_added.Move(last.X(), last.Y());
      was_last_added = true;
      clipped_Polygon->AddPoint(last_added);
   }

   do
   {
      const Point2d& current = *begin++;
      s = nx * (current.X() - pnt_a.X()) + ny * (current.Y() - pnt_a.Y());
      current_out = (s < 0.0) ? true : false;

      if (last_out && !current_out ||
         !last_out && current_out)
      {
         // Find intersection

         // A1*x + B1*y + C1 = 0
         // A2*x + B2*y + C2 = 0
         // Two equations, two unknowns

         // Equation of clipping line
         Float64 A1 = dy;
         Float64 B1 = -dx;
         Float64 C1 = dx * pnt_a.Y() - dy * pnt_a.X();

         // Equation of line to be clipped
         Float64 A2 = current.Y() - last.Y();
         Float64 B2 = last.X() - current.X();
         Float64 C2 = (current.X() - last.X()) * last.Y() - (current.Y() - last.Y()) * last.X();

         Point2d intersect;
         intersect.Y() = (A2 * C1 - A1 * C2) / (A1 * B2 - A2 * B1);

         if (IsZero(A1) && IsZero(A2)) // lines are coincident
            intersect.X() = current.X();
         else if (IsZero(A1)) // Clipping line is horizontal
            intersect.X() = last.X() + (-B2 / A2) * (intersect.Y() - last.Y());
         else
            intersect.X() = -((B1 * intersect.Y() + C1) / A1);

         // don't add duplicate points
         if (!(was_last_added && intersect == last_added))
         {
            last_added = intersect;
            was_last_added = true;
            clipped_Polygon->AddPoint(last_added);
         }
      }

      if (!current_out && !(was_last_added && current == last_added))
      {
         last_added = current;
         was_last_added = true;
         clipped_Polygon->AddPoint(current);
      }

      last = current;
      last_out = current_out;

   } while (begin != end);

   // make sure clipped Polygon has enough points to be interesting
   // If there are less than 3 points, it isn't a shape.
   // If there are exactly 3 points, and the first and last points are the same
   // it isn't a shape either (area is zero)
   if (clipped_Polygon->m_Points.size() < 3 || (clipped_Polygon->m_Points.size() == 3 && clipped_Polygon->m_Points.front() == clipped_Polygon->m_Points.back()))
      return nullptr;
   else
      return clipped_Polygon;
}

#if defined _DEBUG
bool Polygon::AssertValid() const
{
   if (m_Points.empty()) return true;

   // could add test for bow ties here if a suitable algorithm can be found
   auto iter = m_Points.begin();
   auto end = m_Points.end();
   Point2d p0(*iter); // previous point
   iter++;
   for (; iter != end; iter++)
   {
      Point2d p1(*iter); // current point

      if (m_Symmetry == Symmetry::X)
      {
         // when symmetry is about the Y=0 axis, the current point cannot be on the opposite side of the symmetry axis that the previous point
         Float64 d0 = p0.Y() - m_SymmetryAxis;
         Float64 d1 = p1.Y() - m_SymmetryAxis;
         if (!IsZero(d0) && !IsZero(d1) && ::BinarySign(d0) != ::BinarySign(d1))
            return false;
      }
      else if (m_Symmetry == Symmetry::Y)
      {
         // when symmetry is about the X=0 axis, the current point cannot be on the opposite side of the symmetry axis that the previous point
         Float64 d0 = p0.X() - m_SymmetryAxis;
         Float64 d1 = p1.X() - m_SymmetryAxis;
         if (!IsZero(d0) && !IsZero(d1) && ::BinarySign(d0) != ::BinarySign(d1))
            return false;
      }

      p0 = p1; // update previous point
   }

   return true;
}
#endif // _DEBUG
