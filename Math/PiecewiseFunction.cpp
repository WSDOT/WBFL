///////////////////////////////////////////////////////////////////////
// Math - Utility library of mathematical services
// Copyright © 1999-2025  Washington State Department of Transportation
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

#include <Math\MathLib.h>
#include <Math\PiecewiseFunction.h>
#include <Math\XFunction.h>
#include <GeomModel\LineSegment2d.h>
#include <GeomModel\GeomOp2d.h>
#include <algorithm>

using namespace WBFL::Math;

static const Float64 FLT_TOLER=1.0e-06; // close enough

// free functions
void seek_right(const std::vector<WBFL::Geometry::Point2d>& points, Float64 x, IndexType* segment)
{
   PRECONDITION(segment!=nullptr);
   std::vector<WBFL::Geometry::Point2d>::size_type siz = points.size();
   CHECK(*segment<siz);
   CHECK(points[*segment-1].X() <= x);

   // assume that x is right of the left end of this segment.
   std::vector<WBFL::Geometry::Point2d>::size_type start = *segment;
   for (std::vector<WBFL::Geometry::Point2d>::size_type i=start; i<siz; i++)
   {
      if (::IsLE(x,points[i].X()) )
      {
         *segment=i;
         return;
      }
   }

   // x not in function range - throw
   THROW_FUNCTION(XFunction::Reason::Undefined);
}

void seek_left(const std::vector<WBFL::Geometry::Point2d>& points, Float64 x, IndexType* segment)
{
   // assume that x is left of the right end of this segment.
   PRECONDITION(segment != nullptr);
   std::vector<WBFL::Geometry::Point2d>::size_type siz = points.size();
   CHECK(*segment<siz);
   CHECK(x<=points[*segment].X());

   std::vector<WBFL::Geometry::Point2d>::size_type start = *segment;
   std::vector<WBFL::Geometry::Point2d>::size_type i = start-1;
   bool loop=true;
   do
   {
      if ( ::IsLE(points[i].X(),x) )
      {
         *segment=i+1;
         return;
      }
      if (i==0)
      {
         loop=false;
      }

      i--;
   } while (loop);

   // x not in function range - throw
   THROW_FUNCTION(XFunction::Reason::Undefined);
}

Float64 interpolate(const WBFL::Geometry::Point2d& p1, const WBFL::Geometry::Point2d& p2, Float64 x)
{
   // vertical segments not allowed
   CHECK( !IsEqual(p1.X(),p2.X()) );
   
   Float64 a     = x - p1.X();
   Float64 l     = p1.Y();
   Float64 h     = p2.Y();
   Float64 delta = p2.X()-p1.X();
   return LinInterp( a, l, h, delta);
}

PiecewiseFunction::PiecewiseFunction()
{
   ASSERTVALID;
}

PiecewiseFunction::PiecewiseFunction(const std::vector<WBFL::Geometry::Point2d>& points) :
m_Points(points)
{
   ASSERTVALID;
}

Float64 PiecewiseFunction::Evaluate(Float64 x) const
{
   ASSERTVALID;
   // first find which segment x lies in
   bool found=false;

   if (m_Points.empty())
   {
      // x not in function range - throw
      THROW_FUNCTION(XFunction::Reason::Undefined);
   }

   auto range = GetRange();

   // Deal with out of range x's
   if ( x < range.GetLeftBoundLocation() )
   {
      if (m_OutOfRangeBehavior == OutOfRangeBehavior::ExtendOuterValue)
      {
         return m_Points.front().Y();
      }
      else if (m_OutOfRangeBehavior == OutOfRangeBehavior::Extrapolate)
      {
         // interpolate outside of our bounds
         Float64 yval = interpolate(m_Points[0],m_Points[1],x);
         return yval;
      }
      else // m_OutOfRangeBehavior == orbThrowException
      {
         THROW_FUNCTION(XFunction::Reason::Undefined);
      }
   }
   else if ( range.GetRightBoundLocation() < x )
   {
      if (m_OutOfRangeBehavior == OutOfRangeBehavior::ExtendOuterValue)
      {
         return m_Points.back().Y();
      }
      else if (m_OutOfRangeBehavior == OutOfRangeBehavior::Extrapolate)
      {
         // interpolate outside of our bounds
         std::size_t lastval = m_Points.size() - 1;
         Float64 yval = interpolate(m_Points[lastval-1], m_Points[lastval], x);
         return yval;
      }
      else // (m_OutOfRangeBehavior == OutOfRangeBehavior::ThrowException)
      {
         THROW_FUNCTION(XFunction::Reason::Undefined);
      }
   }

   // We are in range. Go to work
   if (IsEqual(x,m_Points.front().X()))
   {
      // Edge case - no need for interpolation
      return m_Points.front().Y();
   }
   else if (IsEqual(x,m_Points.back().X()))
   {
      // Edge case - no need for interpolation
      return m_Points.back().Y();
   }
   else if (m_LastSegment==0)
   {
      // no last seek. just start at the left end and work right
      if (m_Points[0].X() < x)
      {
         m_LastSegment=1;
         seek_right(m_Points, x, &m_LastSegment);
      }
   }
   else
   {
      Float64 segrgt = m_Points[m_LastSegment].X();
      if (x<=segrgt)
      {
         seek_left(m_Points, x, &m_LastSegment);
      }
      else
      {
         seek_right(m_Points, x, &m_LastSegment);
      }
   }

   // linear interpolate across segment to find Y
   // make sure x is between p1 and p2
   CHECK(InRange(m_Points[m_LastSegment - 1].X(), x, m_Points[m_LastSegment].X()));

   Float64 yval = interpolate(m_Points[m_LastSegment-1],m_Points[m_LastSegment],x);

   return yval;
}

std::unique_ptr<Function> PiecewiseFunction::Clone() const
{
   std::unique_ptr<PiecewiseFunction> pfunc = std::make_unique<PiecewiseFunction>(m_Points);
   pfunc->m_OutOfRangeBehavior = m_OutOfRangeBehavior;

   return pfunc;
}

Range PiecewiseFunction::GetRange() const
{
   ASSERTVALID;
   if (0 < m_Points.size())
   {
      return Range(m_Points.front().X(),Range::BoundType::Bound,
                   m_Points.back().X() ,Range::BoundType::Bound);
   }
   else
   {
      return Range();
   }
}

void WBFL::Math::PiecewiseFunction::SetOutOfRangeBehavior(OutOfRangeBehavior behavior)
{
   m_OutOfRangeBehavior = behavior;
}

WBFL::Math::PiecewiseFunction::OutOfRangeBehavior WBFL::Math::PiecewiseFunction::GetOutOfRangeBehavior() const
{
   return m_OutOfRangeBehavior;
}

IndexType PiecewiseFunction::GetPointCount() const
{
   return m_Points.size();
}

const WBFL::Geometry::Point2d& PiecewiseFunction::GetPoint(IndexType idx) const
{
   ASSERTVALID;
   PRECONDITION(idx < m_Points.size());
   return m_Points[idx];
}

const std::vector<WBFL::Geometry::Point2d>& PiecewiseFunction::GetPoints() const
{
   ASSERTVALID;
   return m_Points;
}

void PiecewiseFunction::SetPoints(const std::vector<WBFL::Geometry::Point2d>& points)
{
   ASSERTVALID;
   m_Points = points;
   std::sort(m_Points.begin(), m_Points.end(), [](const auto& p1, const auto& p2) {return p1.X() < p2.X(); });

   auto size = m_Points.size();
   if (size < m_LastSegment)
   {
      m_LastSegment = size;
   }
   ASSERTVALID;
}

IndexType PiecewiseFunction::AddPoint(const WBFL::Geometry::Point2d& point)
{
   ASSERTVALID;
   m_Points.push_back(point);
   std::sort(m_Points.begin(),m_Points.end(), [](const auto& p1, const auto& p2) {return p1.X() < p2.X(); });
   ASSERTVALID;
   return m_Points.size();
}

IndexType PiecewiseFunction::AddPoint(Float64 X,Float64 Y)
{
   return AddPoint(WBFL::Geometry::Point2d(X,Y));
}

IndexType PiecewiseFunction::AddPoints(std::vector<WBFL::Geometry::Point2d>& points)
{
   ASSERTVALID;
   m_Points.insert(m_Points.end(),points.begin(), points.end());
   std::sort(m_Points.begin(), m_Points.end(), [](const auto& p1, const auto& p2) {return p1.X() < p2.X(); });
   ASSERTVALID;
   return m_Points.size();
}

void PiecewiseFunction::Clear()
{
   ASSERTVALID;
   m_Points.clear();
   m_LastSegment = 0;
}

Int16 PiecewiseFunction::Intersect(const PiecewiseFunction& rOther,const Range& range, WBFL::Geometry::Point2d* p) const
{
   // first determine if we have a range in common
   Range r = range.Intersection(GetRange());
   r = r.Intersection(rOther.GetRange());
   if (r.IsNull())
   {
      return 0;
   }

   // next determine the ranges of segments that we may have an intersection on
   IndexType this_first=1,  this_last;
   IndexType other_first=1, other_last;
   try
   {
      seek_right(m_Points, r.GetLeftBoundLocation(), &this_first);
      this_last=this_first; // optimization
      seek_right(m_Points, r.GetRightBoundLocation(), &this_last);

      seek_right(rOther.m_Points, r.GetLeftBoundLocation(), &other_first);
      other_last=other_first; // optimization
      seek_right(rOther.m_Points, r.GetRightBoundLocation(), &other_last);
   }
   catch(...)
   {
      CHECK(0); // should not get here
      return 0;
   }

   // walk over ranges and try to find intersection point
   IndexType this_curr =this_first;
   IndexType other_curr=other_first;
   bool loop=true;
   WBFL::Geometry::Point2d intersection_point;
   while(loop)
   {
      // neither of these cases should ever happen, but...
      if (this_last < this_curr)
      {
         CHECK(0);
         return 0;
      }
      else if (other_last < other_curr)
      {
         CHECK(0);
         return 0;
      }

      WBFL::Geometry::LineSegment2d this_seg(m_Points[this_curr-1],m_Points[this_curr]);
      WBFL::Geometry::LineSegment2d other_seg(rOther.m_Points[other_curr-1],rOther.m_Points[other_curr]);
      Int16 st = WBFL::Geometry::GeometricOperations::Intersect(this_seg, other_seg, &intersection_point);
      if (st != 0)
      {
         // it's possible that intersection could lie outside of intended range
         if (range.IsInRange(intersection_point.X()))
         {
            *p = intersection_point;
            return st;
         }
      }

      // no intersection yet - increment next segment
      if (this_curr==this_last && other_curr==other_last)
      {
         loop=false; // no intersection found
      }
      else
      {
         if (m_Points[this_curr].X()>rOther.m_Points[other_curr].X())
         {
            other_curr++;
         }
         else
         {
            this_curr++;
         }
      }
   }

   return 0;
}

void PiecewiseFunction::GetMaximumsInRange(const Range& range, Float64* pMin, Float64* pMax) const
{
   Float64 left_bnd = range.GetLeftBoundLocation();
   Float64 right_bnd = range.GetRightBoundLocation();

   // Call Evaluate function to get left end of range.
   // This will also set m_LastSegment to the point location just right of the left range bound
   Float64 left_y = Evaluate( left_bnd );

   Float64 min_y(left_y);
   Float64 max_y(left_y);

   // Loop over remaining values to find max's
   Float64 last_x(left_bnd);
   Float64 last_y(left_y);
   IndexType idx(m_LastSegment); // m_LastSegment set by Evaluate
   IndexType size(m_Points.size());

   while(true)
   {
      if (size <= idx)
      {
         // We have hit end of bounds without finding a value. Throw
         THROW_FUNCTION(XFunction::Reason::Undefined);
      }

      Float64 x = m_Points[idx].X();
      Float64 y = m_Points[idx].Y();
      if (x <= right_bnd)
      {
         // point is within right bound, just take max's
         min_y = min(min_y, y);
         max_y = max(max_y, y);

         if (right_bnd-x < FLT_TOLER)
         {
            break; // x is at end of range, we are done
         }
      }
      else
      {
         // Point is beyond end of range and last point is before. Interpolate
         Float64 a     = right_bnd - last_x;
         Float64 l     = last_y;
         Float64 h     = y;
         Float64 delta = x - last_x;
         Float64 int_y =  LinInterp( a, l, h, delta);

         min_y = min(min_y, int_y);
         max_y = max(max_y, int_y);
         break; // done
      }

      last_x = x;
      last_y = y;
      idx++;
   }

   *pMin = min_y;
   *pMax = max_y;
}

void PiecewiseFunction::MirrorAboutY(Float64 xLocation)
{
   // Mirror all points around xLocation. This is done with two operations:
   // 1) reverse order of points
   // 2) New x values = 2*xLocation - x
   std::reverse(m_Points.begin(), m_Points.end());

   for(auto& point : m_Points)
   {
      Float64 x = point.X();
      point.X() = 2*xLocation - x;
   }
}

void PiecewiseFunction::GetYValues(std::vector<Float64>& Yvec) const
{
   for (const auto& point : m_Points)
   {
      Yvec.push_back(point.Y());
   }
}

void PiecewiseFunction::ResetOuterRange(const Range& range)
{
   Float64 xleft = range.GetLeftBoundLocation();
   Float64 xright = range.GetRightBoundLocation();

   auto size = m_Points.size();

   // New range must fit at outer edges of function
   if (size < 2 || m_Points[1].X()<=xleft || xright<=m_Points[size-2].X())
   {
      THROW_FUNCTION(XFunction::Reason::Undefined);
   }
   else
   { 
      // Set the new range
      m_Points[0].X() = xleft;
      m_Points.back().X() = xright;
   }
}


#if defined _DEBUG
bool PiecewiseFunction::AssertValid() const
{
   // values of x must increase
   IndexType size = m_Points.size();
   if (0 < size)
   {
      Float64 cval = m_Points[0].X();
      for(IndexType i=1; i < size; i++)
      {
         if (m_Points[i].X() < cval)
         {
            return false;
         }

         cval = m_Points[i].X();
      }
      // last-used segment must lie within range
      if (size <= m_LastSegment)
      {
         return false;
      }
   }
   else
   {
      if (m_LastSegment != 0)
      {
         return false;
      }
   }


   return true;
}
#endif // _DEBUG
