///////////////////////////////////////////////////////////////////////
// Math - Utility library of mathematical services
// Copyright © 1999-2018  Washington State Department of Transportation
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
#include <Math\PwLinearFunction2dUsingPoints.h>
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static const Float64 FLT_TOLER=1.0e-06; // close enough

/****************************************************************************
CLASS
   mathPwLinearFunction2dUsingPoints
****************************************************************************/

////////////////////////// PUBLIC     ///////////////////////////////////////
// free functions
void seek_right (const std::vector<gpPoint2d>& points, Float64 x, CollectionIndexType* segment)
{
   PRECONDITION(segment!=0);
   std::vector<gpPoint2d>::size_type siz = points.size();
   CHECK(*segment<siz);
   CHECK(points[*segment-1].X() <= x);

   // assume that x is right of the left end of this segment.
   std::vector<gpPoint2d>::size_type start = *segment;
   for (std::vector<gpPoint2d>::size_type i=start; i<siz; i++)
   {
      if (::IsLE(x,points[i].X()) )
      {
         *segment=i;
         return;
      }
   }

   // x not in function range - throw
   THROW(mathXEvalError, Undefined);
}
void seek_left(const std::vector<gpPoint2d>& points, Float64 x, CollectionIndexType* segment)
{
   // assume that x is left of the right end of this segment.
   PRECONDITION(segment!=0);
   std::vector<gpPoint2d>::size_type siz = points.size();
   CHECK(*segment<siz);
   CHECK(x<=points[*segment].X());

   std::vector<gpPoint2d>::size_type start = *segment;
   std::vector<gpPoint2d>::size_type i = start-1;
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
   THROW(mathXEvalError, Undefined);
}

Float64 interpolate(const gpPoint2d& p1, const gpPoint2d& p2, Float64 x)
{
   // vertical segments not allowed
   ATLASSERT( !IsEqual(p1.X(),p2.X()) );
   
   // make sure x is between p1 and p2
   ATLASSERT(InRange(p1.X(),x,p2.X()));

   Float64 a     = x - p1.X();
   Float64 l     = p1.Y();
   Float64 h     = p2.Y();
   Float64 delta = p2.X()-p1.X();
   return LinInterp( a, l, h, delta);
}

bool point_sort(const gpPoint2d& p1,const gpPoint2d& p2)
{
   return p1.X() < p2.X();
}

//======================== LIFECYCLE  =======================================
mathPwLinearFunction2dUsingPoints::mathPwLinearFunction2dUsingPoints() :
mathPwLinearFunction2d(),
m_LastSegment(0)
{
}

mathPwLinearFunction2dUsingPoints::mathPwLinearFunction2dUsingPoints(const std::vector<gpPoint2d>& points):
mathPwLinearFunction2d(),
m_Points(points),
m_LastSegment(0)
{
   ASSERTVALID;
}

mathPwLinearFunction2dUsingPoints::~mathPwLinearFunction2dUsingPoints()
{
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

Float64 mathPwLinearFunction2dUsingPoints::Evaluate(Float64 x) const
{
   ASSERTVALID;
   // first find which segment x lies in
   bool found=false;

   if (GetNumPoints()==0)
   {
      // x not in function range - throw
      THROW(mathXEvalError, Undefined);
   }

   math1dRange range = GetRange();
   if ( x < range.GetLeftBoundLocation() )
   {
      return m_Points.front().Y();
   }
   else if ( range.GetRightBoundLocation() < x )
   {
      return m_Points.back().Y();
   }

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
   Float64 yval = interpolate(m_Points[m_LastSegment-1],m_Points[m_LastSegment],x);

   return yval;
}

mathFunction2d* mathPwLinearFunction2dUsingPoints::Clone() const
{
   return new mathPwLinearFunction2dUsingPoints(m_Points);
}

math1dRange mathPwLinearFunction2dUsingPoints::GetRange() const
{
   ASSERTVALID;
   if (0 < m_Points.size())
   {
      return math1dRange(m_Points.begin()->X(),math1dRange::Bound,
                         m_Points.back().X() ,math1dRange::Bound);
   }
   else
   {
      return math1dRange();
   }
}

CollectionIndexType mathPwLinearFunction2dUsingPoints::GetNumPoints() const
{
   return m_Points.size();
}

gpPoint2d mathPwLinearFunction2dUsingPoints::GetPoint(CollectionIndexType pnum) const
{
   ASSERTVALID;
   PRECONDITION(pnum<GetNumPoints());
   return m_Points[pnum];
}

std::vector<gpPoint2d> mathPwLinearFunction2dUsingPoints::GetPoints() const
{
   ASSERTVALID;
   return m_Points;
}

void mathPwLinearFunction2dUsingPoints::SetPoints(const std::vector<gpPoint2d>& points)
{
   ASSERTVALID;
   m_Points = points;
   std::sort(m_Points.begin(),m_Points.end(),point_sort);

   CollectionIndexType size = GetNumPoints();
   if (size < m_LastSegment)
   {
      m_LastSegment = size;
   }
   ASSERTVALID;
}

CollectionIndexType mathPwLinearFunction2dUsingPoints::AddPoint(const gpPoint2d& point)
{
   ASSERTVALID;
   m_Points.push_back(point);
   std::sort(m_Points.begin(),m_Points.end(),point_sort);
   ASSERTVALID;
   return GetNumPoints();
}

CollectionIndexType mathPwLinearFunction2dUsingPoints::AddPoint(Float64 X,Float64 Y)
{
   return AddPoint(gpPoint2d(X,Y));
}

void mathPwLinearFunction2dUsingPoints::Clear()
{
   ASSERTVALID;
   m_Points.clear();
   m_LastSegment = 0;
}

Int16 mathPwLinearFunction2dUsingPoints::Intersect(const mathPwLinearFunction2dUsingPoints& rOther, 
                                                   const math1dRange& range, gpPoint2d* p)
{
   // first determine if we have a range in common
   math1dRange r = range.Intersection(GetRange());
   r = r.Intersection(rOther.GetRange());
   if (r.IsNull())
   {
      return 0;
   }

   // next determine the ranges of segments that we may have an intersection on
   CollectionIndexType this_first=1,  this_last;
   CollectionIndexType other_first=1, other_last;
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
   CollectionIndexType this_curr =this_first;
   CollectionIndexType other_curr=other_first;
   bool loop=true;
   gpPoint2d intersection_point;
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

      gpLineSegment2d this_seg(m_Points[this_curr-1],m_Points[this_curr]);
      gpLineSegment2d other_seg(rOther.m_Points[other_curr-1],rOther.m_Points[other_curr]);
      Int16 st = gpGeomOp2d::Intersect(&intersection_point,this_seg, other_seg);
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

void mathPwLinearFunction2dUsingPoints::GetMaximumsInRange(const math1dRange& range, Float64* pMin, Float64* pMax)
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
   CollectionIndexType idx(m_LastSegment); // m_LastSegment set by Evaluate
   CollectionIndexType size(m_Points.size());

   while(true)
   {
      if (size <= idx)
      {
         // We have hit end of bounds without finding a value. Throw
         THROW(mathXEvalError, Undefined);
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

void mathPwLinearFunction2dUsingPoints::MirrorAboutY(Float64 xLocation)
{
   // Mirror all points around xLocation. This is done with two operations:
   // 1) reverse order of points
   // 2) New x values = 2*xLocation - x
   std::reverse(m_Points.begin(), m_Points.end());

   for( std::vector<gpPoint2d>::iterator it=m_Points.begin(); it!=m_Points.end(); it++)
   {
      gpPoint2d& rpoint = *it;
      Float64 x = rpoint.X();
      rpoint.X() = 2*xLocation - x;
   }
}

void mathPwLinearFunction2dUsingPoints::GetYValues(std::vector<Float64>& Yvec)
{
   for( std::vector<gpPoint2d>::const_iterator it=m_Points.begin(); it!=m_Points.end(); it++)
   {
      const gpPoint2d& rpoint = *it;
      Float64 y = rpoint.Y();
      Yvec.push_back(y);
   }
}

void mathPwLinearFunction2dUsingPoints::ResetOuterRange( const math1dRange& range)
{
   Float64 xleft = range.GetLeftBoundLocation();
   Float64 xright = range.GetRightBoundLocation();

   std::vector<gpPoint2d>::size_type siz = m_Points.size();

   // New range must fit at outer edges of function
   if (siz < 2 || m_Points[1].X()<=xleft || xright<=m_Points[siz-2].X())
   {
      ATLASSERT(false);
      THROW(mathXEvalError, Undefined);
   }
   else
   { 
      // Set the new range
      m_Points[0].X() = xleft;
      m_Points.back().X() = xright;
   }
}


//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

//======================== DEBUG      =======================================
#if defined _DEBUG
bool mathPwLinearFunction2dUsingPoints::AssertValid() const
{
   if (!mathPwLinearFunction2d::AssertValid())
      return false;

   // values of x must increase
   CollectionIndexType size = GetNumPoints();
   if (0 < size)
   {
      Float64 cval = m_Points[0].X();
      for(CollectionIndexType i=1; i < size; i++)
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

void mathPwLinearFunction2dUsingPoints::Dump(dbgDumpContext& os) const
{
   os << _T("Start Dump for mathPwLinearFunction2dUsingPoints") <<endl;
   mathPwLinearFunction2d::Dump( os );
   CollectionIndexType siz = GetNumPoints();
   os << _T("Number of Points = ") <<siz<<endl;
   for (CollectionIndexType i = 0; i<siz; i++)
   {
      os <<i<<_T("  (")<< m_Points[i].X()<<_T(", ")<<m_Points[i].Y()<<_T(")")<<endl;
   }
   os << _T("m_LastSegment = ")<< m_LastSegment <<endl;
   os << _T("End Dump for mathPwLinearFunction2dUsingPoints")<<endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool mathPwLinearFunction2dUsingPoints::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("mathPwLinearFunction2dUsingPoints");

   // create a function
   mathPwLinearFunction2dUsingPoints fun1;
   TRY_TESTME(fun1.AddPoint(gpPoint2d(-4,-2))==1);
   TRY_TESTME(fun1.AddPoint(gpPoint2d(-3,-1))==2);
   TRY_TESTME(fun1.AddPoint(gpPoint2d( 1, 2))==3);
   TRY_TESTME(fun1.AddPoint(gpPoint2d( 3,-1))==4);
   TRY_TESTME(fun1.GetRange()==math1dRange(-4,math1dRange::Bound,3,math1dRange::Bound));
   TRY_TESTME(fun1.GetNumPoints()==4);
   TRY_TESTME(fun1.Evaluate(-4)==-2);
   TRY_TESTME(fun1.Evaluate(-3)==-1);
   TRY_TESTME(fun1.Evaluate( 1)==2);
   TRY_TESTME(fun1.Evaluate( 3)==-1);
   TRY_TESTME(fun1.Evaluate(-5./3.)==0.0);
   TRY_TESTME(fun1.Evaluate( 7./3.)==0.0);
   TRY_TESTME(fun1.Evaluate(0.0)==1.25);
   TRY_TESTME(fun1.GetPoint(1)==gpPoint2d(-3,-1));

   // create another function
   std::vector<gpPoint2d> pvec;
   pvec.push_back(gpPoint2d(-5,1));
   pvec.push_back(gpPoint2d(-4.1,1));
   pvec.push_back(gpPoint2d(-3.4,1));
   pvec.push_back(gpPoint2d( 0.0,1));
   pvec.push_back(gpPoint2d( 2.2,1));
   pvec.push_back(gpPoint2d( 5,1));
   mathPwLinearFunction2dUsingPoints fun2(pvec);
   TRY_TESTME(fun2.GetPoints()==pvec);
   TRY_TESTME(fun2.Evaluate(0.0)==1);
   TRY_TESTME(fun2.Evaluate(3.0)==1);
   try
   {
      fun2.Evaluate(-7); // out of bounds
   }
   catch (mathXEvalError& e)
   {
      TRY_TESTME(e.GetReasonCode()==mathXEvalError::Undefined);
   }
   // intersection
   gpPoint2d ip1,ip2;
   math1dRange r(-3.5,math1dRange::Bound,.9,math1dRange::Bound);
   TRY_TESTME(fun1.Intersect(fun2,r,&ip1)==1);
   TRY_TESTME(ip1==gpPoint2d(-1./3.,1));
   TRY_TESTME(fun2.Intersect(fun1,r,&ip2)==1);
   TRY_TESTME(ip1==ip2);

   r.SetLeftBoundLocation(1);
   r.SetRightBoundLocation(250);
   TRY_TESTME(fun1.Intersect(fun2,r,&ip1)==1);
   TRY_TESTME(fun2.Intersect(fun1,r,&ip2)==1);
   TRY_TESTME(ip1==gpPoint2d(5./3.,1));
   TRY_TESTME(ip1==ip2);

   // set where an intersection does not occur
   r.SetLeftBoundLocation(0.9);
   r.SetRightBoundLocation(1.1);
   TRY_TESTME(fun1.Intersect(fun2,r,&ip1)==0);
   TRY_TESTME(fun2.Intersect(fun1,r,&ip2)==0);

   r.SetLeftBoundLocation(-100);
   r.SetRightBoundLocation(-50);
   TRY_TESTME(fun1.Intersect(fun2,r,&ip1)==0);
   TRY_TESTME(fun2.Intersect(fun1,r,&ip1)==0);

   r.SetLeftBoundLocation(100);
   r.SetRightBoundLocation(250);
   TRY_TESTME(fun1.Intersect(fun2,r,&ip1)==0);
   TRY_TESTME(fun2.Intersect(fun1,r,&ip1)==0);

   // GetMaximumsInRange
   Float64 fmin, fmax;
   r.SetLeftBoundLocation(-3.5);
   r.SetRightBoundLocation(1.0);
   fun1.GetMaximumsInRange(r, &fmin, &fmax);
   TRY_TESTME(fmin==-1.5);
   TRY_TESTME(fmax==2.0);

   r.SetLeftBoundLocation(-4.0);
   r.SetRightBoundLocation(3.0);
   fun1.GetMaximumsInRange(r, &fmin, &fmax);
   TRY_TESTME(fmin==-2.0);
   TRY_TESTME(fmax==2.0);

   r.SetLeftBoundLocation(2.0);
   r.SetRightBoundLocation(2.5);
   fun1.GetMaximumsInRange(r, &fmin, &fmax);
   TRY_TESTME(fmin==-0.25);
   TRY_TESTME(fmax==0.5);

   try
   {
      r.SetLeftBoundLocation(2.0);
      r.SetRightBoundLocation(5.0);
      fun1.GetMaximumsInRange(r, &fmin, &fmax);
   }
   catch (mathXEvalError& e)
   {
      TRY_TESTME(e.GetReasonCode()==mathXEvalError::Undefined);
   }
 

#ifdef _DEBUG
   fun2.Dump(rlog.GetDumpCtx());
#endif


   TESTME_EPILOG("PwLinearFunction2dUsingPoints");
}
#endif // _UNITTEST
