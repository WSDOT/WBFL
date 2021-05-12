///////////////////////////////////////////////////////////////////////
// Geometry - Modeling of geometric primitives
// Copyright © 1999-2021  Washington State Department of Transportation
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

#include <GeometricPrimitives\GeometryLib.h>
#include <GeometricPrimitives\Polygon2d.h>
#include <GeometricPrimitives\LineSegment2d.h>
#include <vector>
#include <MathEx.h>
#include <iostream>
#include <memory>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////// PUBLIC     ///////////////////////////////////////

/****************************************************************************
CLASS
   gpPolygon2d
****************************************************************************/


//======================== LIFECYCLE  =======================================
gpPolygon2d::gpPolygon2d()
{
   Init();
   m_PointContainer.reserve(4); // make a guess at size
}

gpPolygon2d::gpPolygon2d(const gpPolygon2d& rOther)
{
   Clear();
   MakeCopy(rOther);
}

gpPolygon2d::~gpPolygon2d()
{
}

//======================== OPERATORS  =======================================
gpPolygon2d& gpPolygon2d::operator= (const gpPolygon2d& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================
Uint32 gpPolygon2d::AddPoint(const gpPoint2d& p)
{
   m_PointContainer.emplace_back(m_LastKey, p);
   return m_LastKey++;
}

bool gpPolygon2d::RemovePoint(Uint32 key)
{
   PointIterator iter;
   GetPointIter(key, iter);

   if ( iter != m_PointContainer.end() )
   {
      m_PointContainer.erase(iter);
      return true;
   }
   else
   {
      return false;
   }
}

const gpPoint2d* gpPolygon2d::GetPoint(Uint32 key) const
{
   PointIterator iter;
   GetPointIter(key, iter);

   if ( iter != m_PointContainer.end() )
   {
      return &(*iter).second;
   }
   else
   {
      return nullptr;
   }
}

bool gpPolygon2d::ReplacePoint(Uint32 key,const gpPoint2d& p)
{
   PointIterator iter;
   GetPointIter(key, iter);
   if ( iter != m_PointContainer.end() )
   {
      (*iter).second = p;
      return true;
   }
   else
   {
      return false;
   }
}

CollectionIndexType gpPolygon2d::GetNumPoints() const
{
   return m_PointContainer.size();
}

void gpPolygon2d::Clear()
{
   m_PointContainer.clear();
   Init();
}

gpPolygon2d& gpPolygon2d::Offset(Float64 x, Float64 y)
{
   return Offset(gpSize2d(x,y));
}

gpPolygon2d& gpPolygon2d::Offset(const gpSize2d& delta)
{
   for (PointIterator iter=m_PointContainer.begin(); iter!=m_PointContainer.end(); iter++)
   {
      gpPoint2d& point = (*iter).second;
      point += delta;
   }
   return *this;
}

gpPolygon2d& gpPolygon2d::Rotate(const gpPoint2d& center, Float64 angle)
{
   for (PointIterator iter=m_PointContainer.begin(); iter!=m_PointContainer.end(); iter++)
   {
      gpPoint2d& point = (*iter).second;
      point.Rotate( center, angle );
   }
   return *this;
}

Float64 gpPolygon2d::Perimeter() const
{
   if ( GetNumPoints() < 2) return 0.;

   Float64 len = 0;
   Float64 x0,y0;
   Float64 x1,y1;
   Float64 dy, dx;
   ConstPointIterator ip0 = m_PointContainer.begin();
   ConstPointIterator ip1 = ip0;
   ip1++;

   // looping is ugly here because we have to close polygon if user did not close
   // if for use.
   bool loop=true, last_round=false;
   while (loop)
   {
      x0 = (*ip0).second.X();
      y0 = (*ip0).second.Y();
      x1 = (*ip1).second.X();
      y1 = (*ip1).second.Y();

      dx = x1 - x0;
      dy = y1 - y0;

      len += sqrt(dx*dx + dy*dy);

      if (last_round)
      {
         // just finished closure loop. time to quit
         loop = false;
      }
      else
      {
         // increment for next go-around
         ip0=ip1;
         ip1++;

         if ( ip1==m_PointContainer.end() )
         {
         // check if extra loop is required for closure
            ip1 = m_PointContainer.begin();
            const gpPoint2d& lastp  = (*ip0).second;   // convert to points here to avoid ugliness
            const gpPoint2d& beginp = (*ip1).second;
            if ( lastp != beginp )
            {
               // one more loop to close poly
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

   return len;
}

void gpPolygon2d::GetProperties(Float64* area,Float64* ixx,Float64* iyy,
               Float64* ixy, gpPoint2d* centroid) const
{
   // Intialize and check for null polygon.
   *area = *ixx = *iyy = *ixy = 0.;
   centroid->Move(0,0);

   if ( GetNumPoints() < 3) return;

   Float64 x0,y0;
   Float64 x1,y1;
   Float64 dy, dx;
   Float64 ar, at;
   Float64 g_ixx=0, g_iyy=0, g_ixy = 0; // moments of inertia about the global axes
   Float64 c_ixx=0, c_iyy=0, c_ixy = 0; // moments of inertia about the centroid
   Float64 area_local  = 0;
   gpPoint2d cg;

   // loop over all points - make sure of closure

   ConstPointIterator ip0 = m_PointContainer.begin();
   ConstPointIterator ip1 = ip0;
   ip1++;

   bool loop=true, last_round=false;
   while (loop)
   {
      x0 = (*ip0).second.X();
      y0 = (*ip0).second.Y();
      x1 = (*ip1).second.X();
      y1 = (*ip1).second.Y();

      dx = x1 - x0;
      dy = y1 - y0;

      ar = dx * y0;
      at = 0.5*dy*dx;

      area_local += (ar + at);

      // Centroid
      cg.X() += ar*(x1 + x0)/2 + at*(2*dx/3 + x0);
      cg.Y() += ar*(y0/2) + at*(dy/3 + y0);

      // Inertia about global axes
      g_ixx += (y0)*(y0)*(y0)*dx/12 + ar*(y0/2)*(y0/2) +
               dy*dy*dy*dx/36       + at*(dy/3 + y0)*(dy/3 + y0);

      g_iyy += (y0)*dx*dx*dx/12 + ar*(x0 + dx/2)*(x0 + dx/2) +
               dy*dx*dx*dx/36 + at*(2*dx/3 + x0)*(2*dx/3 + x0);

      g_ixy += ar*(y0/2)*(x0 + dx/2) +
               at*(dy/3 + y0)*(2*dx/3 + x0) +
               dy*dy*dx*dx/72;

      // loop termination test - need to go one more iteration if loop is not closed
      if (last_round)
      {
         // just finished closure loop. time to quit
         loop = false;
      }
      else
      {
         // increment for next go-around
         ip0=ip1;
         ip1++;

         if ( ip1==m_PointContainer.end() )
         {
         // check if extra loop is required for closure
            ip1 = m_PointContainer.begin();
            gpPoint2d lastp  = (*ip0).second;   // convert to points here to avoid ugliness
            gpPoint2d beginp = (*ip1).second;
            if ( lastp != beginp )
            {
               // one more loop to close poly
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
   if ( !IsZero( area_local ) )
   {

      // Finish centriod
      cg.X() /= area_local;
      cg.Y() /= area_local;

      // Inertia about local axes
      c_ixx = g_ixx - area_local * cg.Y() * cg.Y();
      c_iyy = g_iyy - area_local * cg.X() * cg.X();
      c_ixy = g_ixy - area_local * cg.X() * cg.Y();

      // return properties
      *area    = area_local;
      *centroid= cg;
      *ixx     = c_ixx;
      *iyy     = c_iyy;
      *ixy     = c_ixy;
   }
}

void gpPolygon2d::GetArea(Float64* area, gpPoint2d* centroid) const
{
   // Intialize and check for null polygon.
   *area = 0.;
   centroid->Move(0,0);

   if ( GetNumPoints() < 3) return;

   Float64 x0,y0;
   Float64 x1,y1;
   Float64 dy, dx;
   Float64 ar, at;
   Float64 area_local  = 0;
   gpPoint2d cg;

   // loop over all points - make sure of closure

   ConstPointIterator ip0 = m_PointContainer.begin();
   ConstPointIterator ip1 = ip0;
   ip1++;

   bool loop=true, last_round=false;
   while (loop)
   {
      x0 = (*ip0).second.X();
      y0 = (*ip0).second.Y();
      x1 = (*ip1).second.X();
      y1 = (*ip1).second.Y();

      dx = x1 - x0;
      dy = y1 - y0;

      ar = dx * y0;
      at = 0.5*dy*dx;

      area_local += (ar + at);

      // Centroid
      cg.X() += ar*(x1 + x0)/2 + at*(2*dx/3 + x0);
      cg.Y() += ar*(y0/2) + at*(dy/3 + y0);

      // loop termination test - need to go one more iteration if loop is not closed
      if (last_round)
      {
         // just finished closure loop. time to quit
         loop = false;
      }
      else
      {
         // increment for next go-around
         ip0=ip1;
         ip1++;

         if ( ip1==m_PointContainer.end() )
         {
         // check if extra loop is required for closure
            ip1 = m_PointContainer.begin();
            gpPoint2d lastp  = (*ip0).second;   // convert to points here to avoid ugliness
            gpPoint2d beginp = (*ip1).second;
            if ( lastp != beginp )
            {
               // one more loop to close poly
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
   if ( !IsZero( area_local ) )
   {
      // Finish centriod
      cg.X() /= area_local;
      cg.Y() /= area_local;

      // return properties
      *area    = area_local;
      *centroid= cg;
   }
}

gpRect2d gpPolygon2d::GetBoundingBox() const
{
   Float64 left=0, right=0, top=0, bottom = 0;
   bool first = true;
   for (ConstPointIterator iter=m_PointContainer.begin(); iter!=m_PointContainer.end();iter++)
   {
      const gpPoint2d& point = (*iter).second;
      if (first)
      {
         left   = point.X();
         right  = point.X();
         bottom = point.Y();
         top    = point.Y();
         first  = false;
      }
      else
      {
         left   = Min( point.X(), left);
         right  = Max( point.X(), right);
         bottom = Min( point.Y(), bottom);
         top    = Max( point.Y(), top);
      }
    }

    return gpRect2d(left, bottom, right, top);
}



gpPolygon2d* gpPolygon2d::CreateClippedPolygon(const gpLine2d& line, gpLine2d::Side side) const
{
   //
   // could optimize this routine to work with gpLine2d and gpLineSegment2d, but 
   // would not likely gain much.
   gpVector2d dir;
   gpPoint2d  pnt_a;
   gpPoint2d  pnt_b;

   line.GetExplicit(&pnt_a, &dir);  // point on the line and direction vector
   if ( side == gpLine2d::Right )
   {
      pnt_b = pnt_a.OffsetBy(-dir.X(), -dir.Y());
   }
   else
   {
      pnt_b = pnt_a.OffsetBy(dir.X(), dir.Y());
   }

   Float64 dx, dy; // components of the direction vector of the clipping line
   Float64 nx, ny; // components of a vector normal to the clipping line
   Float64 s;      // dot product of the normal vector and the position vector
                  // of this Polygon

   // If the polyPolygon isn't at least a triangle, just get the heck outta here.
   CollectionIndexType num_points = this->GetNumPoints();
   if ( num_points  < 3 )
      return nullptr;

   // create an empty clipped Polygon - return empty if need be
   std::unique_ptr<gpPolygon2d> clipped_Polygon(std::make_unique<gpPolygon2d>());
   clipped_Polygon->Reserve(num_points+1); // assume clip might add a point

   dx = pnt_b.X() - pnt_a.X();
   dy = pnt_b.Y() - pnt_a.Y();

   nx = -dy;
   ny =  dx;

   // get the vector of points from the Polygon and make sure that it's closed
   std::vector<gpPoint2d> my_points;
   my_points.reserve(num_points+1);
   for (ConstPointIterator it=m_PointContainer.begin();it!=m_PointContainer.end(); it++)
      my_points.push_back( (*it).second );

   gpPoint2d current;
   gpPoint2d last;
   gpPoint2d last_added;
   bool      was_last_added=false;
   std::vector<gpPoint2d>::const_iterator begin = my_points.begin();
   gpPoint2d& back  = my_points.back();
   if ( *begin != back)
      my_points.push_back( *begin ); // close polygon if not already

   begin = my_points.begin();
   std::vector<gpPoint2d>::const_iterator end   = my_points.end();
   bool current_out;
   bool last_out;

   last = *begin++;

   s = nx * (last.X() - pnt_a.X()) + ny * (last.Y() - pnt_a.Y());

   last_out = ( s < 0 ) ? true : false;

   if ( !last_out )
   {
      last_added.Move(last.X(), last.Y());
      was_last_added = true;
      clipped_Polygon->AddPoint( last_added );
   }

   do
   {
      current = *begin++;
      s = nx * (current.X() - pnt_a.X()) + ny * (current.Y() - pnt_a.Y());
      current_out = ( s < 0 ) ? true : false;

      Float64 A1, A2;
      Float64 B1, B2;
      Float64 C1, C2;
      gpPoint2d intersect;
      if ( last_out && !current_out ||
          !last_out &&  current_out )
      {
         // Find intersection

         // A1*x + B1*y + C1 = 0
         // A2*x + B2*y + C2 = 0
         // Two equations, two unknowns

         // Equation of clipping line
         A1 = dy;
         B1 = -dx;
         C1 = dx * pnt_a.Y() - dy * pnt_a.X();

         // Equation of line to be clipped
         A2 = current.Y() - last.Y();
         B2 = last.X() - current.X();
         C2 = (current.X() - last.X()) * last.Y() - (current.Y() - last.Y()) * last.X();

         intersect.Y() = ( A2*C1 - A1*C2 ) / ( A1*B2 - A2*B1 );

         if ( IsZero( A1 ) ) // Clipping line is horizontal
            intersect.X() = last.X() + ( -B2/A2 ) * ( intersect.Y() - last.Y() );
         else
            intersect.X() = -( (B1*intersect.Y() + C1) / A1 );

         // don't add duplicate points
         if (!(was_last_added && intersect==last_added))
         {
            last_added =  intersect;
            was_last_added = true;
            clipped_Polygon->AddPoint( last_added );
         }
      }

      if ( !current_out && !(was_last_added && current==last_added))
      {
         last_added =  current;
         was_last_added = true;
         clipped_Polygon->AddPoint( current );
      }

      last = current;
      last_out = current_out;

   } while ( begin != end );

   // make sure clipped Polygon has enough points to be interesting
   if ( clipped_Polygon->GetNumPoints() < 3 )
      return nullptr;
   else
      return clipped_Polygon.release();
}

gpPolygon2d* gpPolygon2d::CreateClippedPolygon(const gpRect2d& r, gpPolygon2d::ClipRegion region) const
{
   gpLine2d::Side side;
   if (region==gpPolygon2d::In)
     side = gpLine2d::Right;
   else
     side = gpLine2d::Left;

   typedef std::unique_ptr<gpPolygon2d> Aps;

   // Clip by consecutively clipping against each edge of the rectangle
   Aps clip_top   (       this->CreateClippedPolygon(gpLine2d(r.TopLeft(), r.TopRight()), side ));
   Aps clip_right (   clip_top->CreateClippedPolygon(gpLine2d(r.TopRight(),    r.BottomRight()), side ));
   Aps clip_bottom( clip_right->CreateClippedPolygon(gpLine2d(r.BottomRight(), r.BottomLeft()), side ));
   Aps clip_left  (clip_bottom->CreateClippedPolygon(gpLine2d(r.BottomLeft(),  r.TopLeft()), side ));

   return clip_left.release();
}

bool gpPolygon2d::Contains(const gpPoint2d& pnt) const
{
   // Reference:
   // "Use of the residue theorem in locating points within an
   // arbitrary multiply-connected region"
   // G. Steven Gipson
   // Adv. Eng. Software, 1986, Vol. 8, No. 2

   CollectionIndexType num_points = GetNumPoints();
   if (num_points<3)
      return false;   // points and lines can't contain anything.

   const Float64 angular_tolerance = 6.2831853e-02; // 2*pi*10^-2
   // this is probably the correct way to do it, but we'll approximate for now
   // boundary_tolerance = GetMinEdgeLength() / ( 2 * m_ShapeExtents.TopLeft().Distance( m_ShapeExtents.BottomRight() ) );
   gpRect2d rect = GetBoundingBox();
   Float64 edgelen = min(rect.Width(),rect.Height());
   Float64 dist =  2 * rect.TopLeft().Distance( rect.BottomRight() );
   if (IsZero(dist))
      return false;
   Float64 boundary_tolerance = edgelen / dist;
   boundary_tolerance = min( 1e-06, boundary_tolerance );

   Float64 sum = 0;

   ConstPointIterator ip0 = m_PointContainer.begin();
   ConstPointIterator ip1 = ip0;
   ip1++;
   bool loop=true, last_round=false;
   while (loop)
   {
      Float64 x0 = (*ip0).second.X();
      Float64 y0 = (*ip0).second.Y();
      Float64 x1 = (*ip1).second.X();
      Float64 y1 = (*ip1).second.Y();

      // no calculation if points are coincident
      if (x0!=x1 || y0!=y1)
      {

         // Compute components of two vectors formed by
         // joining point in question with endpoints of 
         // boundary segment
         Float64 ax = x0 - pnt.X();
         Float64 ay = y0 - pnt.Y();
         Float64 bx = x1 - pnt.X();
         Float64 by = y1 - pnt.Y();

         // Form cross product of the vectors to determine
         // the sign of the angular segment
         Float64 cp = ax*by - ay*bx;
         Float64 sign = cp < 0 ? -1 : 1;

         // Test for vanishing cross product in case the test point
         // is on the boundary.
         //
         // The line segment is used to make sure the point is actually 
         // contained in the line segment, and not a projection of the line segment
         if ( IsZero( fabs( cp ), boundary_tolerance ) && 
              gpLineSegment2d(gpPoint2d(x0,y0),gpPoint2d(x1,y1)).Contains(pnt))
            return false;

         // Compute dot product of two vectors for purpose of obtaining
         // the actual angle subtended by the boundary increment.
         Float64  dot = ax*bx + ay*by;
         Float64  A2 = ax*ax + ay*ay;
         Float64  B2 = bx*bx + by*by;
         Float64  prod = A2 * B2;

         // Compute angle
         Float64  angle = 0;
         if ( !IsZero( prod ), 1.0e-16 )
         {
            Float64 x = dot/sqrt(prod);
            if ( IsZero(x-1.0) )
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
         ip0=ip1;
         ip1++;
         if ( ip1==m_PointContainer.end() )
         {
         // check if extra loop is required for closure
            ip1 = m_PointContainer.begin();
            gpPoint2d lastp  = (*ip0).second;   // convert to points here to avoid ugliness
            gpPoint2d beginp = (*ip1).second;
            if ( lastp != beginp )
            {
               // one more loop to close poly
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
   sum *= 0.159154943; // ( 1/2*PI )

   bool contained;

   if ( IsEqual( sum, -1., angular_tolerance) || IsEqual( sum, 1., angular_tolerance ) )
      contained = true;
   else if ( IsZero( sum, angular_tolerance ) )
      contained = false;
   else
   {
      CHECKX( false, _T("This should never happen") );
   }

   return contained;

}

Float64 gpPolygon2d::GetFurthestDistance(const gpLine2d& line, gpLine2d::Side side) const
{
   // need to determine which side of line each point is on. Implicit rep of line has normal
   // vector which always points left.
   Float64    c;
   gpVector2d n;
   line.GetImplicit(&c, &n);

   // change n to point toward desired side of line
   if (gpLine2d::Right == side)
      n = -n;

   // loop over all points to determine farthest point.
   Float64 max_dist;
   bool first = true;
   for (ConstPointIterator it=m_PointContainer.begin();it!=m_PointContainer.end(); it++)
   {
      const gpPoint2d& p = (*it).second;
      // get point on line closest to point.
      gpPoint2d norm=line.PointOnLineNearest(p);

      Float64 dist = p.Distance(norm);  // always positive

      // Now must determine if point is on desired side or other side
      // create a vector from point on line to point.
      gpVector2d vec(p-norm);
      // if dot product with n is positive, point is on left
      Float64 dot = n.Dot(vec);
      if (dot<0)
         dist = -dist; // point on other side of line (negative direction)


      if (first)
      {
         max_dist = dist;
         first = false;
      }
      else
         max_dist = Max(dist,max_dist);
   }

   return max_dist;
   
}

void gpPolygon2d::Reserve(CollectionIndexType size)
{
   m_PointContainer.reserve(size);
}



//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool gpPolygon2d::AssertValid() const
{
   return true;
}

void gpPolygon2d::Dump(dbgDumpContext& os) const
{
   os << _T("Dump for gpPolygon2d") << endl;
   os << _T("   m_LastKey   = ")<<m_LastKey<<endl;
   os << _T("   # of Points = ")<< (Uint32)m_PointContainer.size()<<endl;
   for (ConstPointIterator iter = m_PointContainer.begin(); iter != m_PointContainer.end(); iter++)
   {
      const gpPoint2d& p = (*iter).second;
      Uint32     key = (*iter).first;
      os << _T("     (Key,X,Y)   = (") << key << _T(", ") << p.X() << _T(", ") << p.Y() << _T(")") << endl;
   }
}
#endif // _DEBUG

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void gpPolygon2d::MakeCopy(const gpPolygon2d& rOther)
{
   m_LastKey = rOther.m_LastKey;
   m_PointContainer = rOther.m_PointContainer;
}

void gpPolygon2d::MakeAssignment(const gpPolygon2d& rOther)
{
   Clear();
   MakeCopy( rOther );
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void gpPolygon2d::Init()
{
   m_LastKey = 0;
}

//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

//======================== LIFECYCLE  =======================================

/****************************************************************************
CLASS
   gpPolyPointIter2d
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////
gpPolyPointIter2d::gpPolyPointIter2d()
{
   Init();
}

gpPolyPointIter2d::gpPolyPointIter2d(const gpPolygon2d* const pPolygon)
{
   SetPolygon(pPolygon);
}


gpPolyPointIter2d::gpPolyPointIter2d(const gpPolyPointIter2d& rOther)
{
   Init();
   MakeCopy(rOther);
}

gpPolyPointIter2d::~gpPolyPointIter2d()
{
   Init();
}

//======================== OPERATORS  =======================================
gpPolyPointIter2d& gpPolyPointIter2d::operator= (const gpPolyPointIter2d& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================

void gpPolyPointIter2d::SetPolygon(const gpPolygon2d* const pPolygon)
{
   PRECONDITION(pPolygon != nullptr);
   m_pPolygon = pPolygon;
   m_Iterator = pPolygon->m_PointContainer.begin();
}

void gpPolyPointIter2d::Begin()
{
   PRECONDITION(m_pPolygon != nullptr);
   m_Iterator = m_pPolygon->m_PointContainer.begin();
}

void gpPolyPointIter2d::End()
{
   PRECONDITION(m_pPolygon != nullptr);
   m_Iterator = m_pPolygon->m_PointContainer.end();
}

void gpPolyPointIter2d::Next()
{
   PRECONDITION(m_pPolygon != nullptr);
   CHECK(m_Iterator!=m_pPolygon->m_PointContainer.end());
   m_Iterator++;
}

void gpPolyPointIter2d::Prev()
{
   PRECONDITION(m_pPolygon != nullptr);
   CHECK(m_Iterator!=m_pPolygon->m_PointContainer.begin());
   m_Iterator--;
}

gpPolyPointIter2d::operator void *() 
{
   if (m_pPolygon == nullptr)
      return nullptr;
   else if (m_Iterator==m_pPolygon->m_PointContainer.end())
      return nullptr;
   else
      return (void*)&(*m_Iterator).second;
}

// code duplication of above -- watch out!!
gpPolyPointIter2d::operator void *() const
{
   if (m_pPolygon == nullptr)
      return nullptr;
   else if (m_Iterator==m_pPolygon->m_PointContainer.end())
      return nullptr;
   else
      return (void*)&(*m_Iterator).second;
}

const gpPoint2d* gpPolyPointIter2d::CurrentPoint() const
{
   PRECONDITION(*this);
   return &(*m_Iterator).second;
}

const Uint32* gpPolyPointIter2d::CurrentKey() const
{
   PRECONDITION(*this);
   return &((*m_Iterator).first);
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool gpPolyPointIter2d::AssertValid() const
{
   return true;
}

void gpPolyPointIter2d::Dump(dbgDumpContext& os) const
{
   os<< _T("Dump for gpPolyPointIter2d") <<endl;
}

#endif // _DEBUG

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void gpPolyPointIter2d::MakeCopy(const gpPolyPointIter2d& rOther)
{
   m_pPolygon = rOther.m_pPolygon;
   m_Iterator = rOther.m_Iterator;
}

void gpPolyPointIter2d::MakeAssignment(const gpPolyPointIter2d& rOther)
{
   Init();

   MakeCopy( rOther );
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void gpPolyPointIter2d::Init()
{
   m_pPolygon = nullptr;
}

void gpPolyPointIter2d::Clean()
{
   // nothing to clean up.
}

#if defined _UNITTEST
bool gpPolygon2d::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("gpPolygon2d");

   // create an angle shape. Taken from "Statics" 1st Ed. by J.L. Merriam, page 373
   Float64   area, ixx, iyy, ixy;
   gpPoint2d cg;
   Float64   a_area;
   gpPoint2d a_cg;

   gpPolygon2d anglep;
   Uint32 p1 = anglep.AddPoint(gpPoint2d(0 , 0));
   Uint32 p2 = anglep.AddPoint(gpPoint2d(0 ,50));
   Uint32 p3 = anglep.AddPoint(gpPoint2d(10,50));
   Uint32 p4 = anglep.AddPoint(gpPoint2d(10,10));
   Uint32 p5 = anglep.AddPoint(gpPoint2d(40,10));
   Uint32 p6 = anglep.AddPoint(gpPoint2d(40, 0));  // don't close polygon

   anglep.GetProperties( &area, &ixx, &iyy, &ixy, &cg);
   TRY_TESTME (IsEqual(area, 800.));
   TRY_TESTME (IsEqual(ixx,  181670., 10.));
   TRY_TESTME (IsEqual(iyy,  101670., 10.));
   TRY_TESTME (IsEqual(ixy, -75000., 10.));
   TRY_TESTME (anglep.GetBoundingBox() == gpRect2d(0,0,40,50));

   anglep.GetArea( &a_area, &a_cg);
   TRY_TESTME (a_area==area);
   TRY_TESTME (a_cg==cg);

   // test assignment
   gpPolygon2d anglec = anglep;
   anglec.GetProperties( &area, &ixx, &iyy, &ixy, &cg);
   TRY_TESTME (IsEqual(area, 800.));
   TRY_TESTME (IsEqual(ixx,  181670., 10.));
   TRY_TESTME (IsEqual(iyy,  101670., 10.));
   TRY_TESTME (IsEqual(ixy, -75000., 10.));
   TRY_TESTME (anglep.GetBoundingBox() == gpRect2d(0,0,40,50));

   anglec.GetArea( &a_area, &a_cg);
   TRY_TESTME (a_area==area);
   TRY_TESTME (a_cg==cg);

   // point containment
   gpPoint2d in1(5,20), in2(35,1), in3(1,1);
   gpPoint2d out1(5,60), out2(0,12), out3(-1,1), out4(0,0), out5(10,0), out6(-1,-1);
   TRY_TESTME (anglep.Contains(in1));
   TRY_TESTME (anglep.Contains(in2));
   TRY_TESTME (!anglep.Contains(out1));
   TRY_TESTME (!anglep.Contains(out2));
   TRY_TESTME (!anglep.Contains(out3));
   TRY_TESTME (!anglep.Contains(out4));
   TRY_TESTME (!anglep.Contains(out5));
   TRY_TESTME (!anglep.Contains(out6));

   // try translation
   gpPoint2d center(20,25);
   gpPoint2d top_right(40,50);

   anglec.Offset(top_right-center);
   anglec.GetProperties( &area, &ixx, &iyy, &ixy, &cg);
   TRY_TESTME (IsEqual(area, 800.));
   TRY_TESTME (IsEqual(ixx,  181670., 10.));
   TRY_TESTME (IsEqual(iyy,  101670., 10.));
   TRY_TESTME (IsEqual(ixy, -75000., 10.));
   TRY_TESTME (anglec.GetBoundingBox() == gpRect2d(20,25,60,75));

   anglec.GetArea( &a_area, &a_cg);
   TRY_TESTME (a_area==area);
   TRY_TESTME (a_cg==cg);

   // rotate to principal axes
   anglep.Rotate(center, -0.54105);
   anglep.GetProperties( &area, &ixx, &iyy, &ixy, &cg);
   TRY_TESTME (IsEqual(area, 800.));
   TRY_TESTME (IsEqual(ixx,  226666., 10.));
   TRY_TESTME (IsEqual(iyy,   56666., 10.));
   TRY_TESTME (IsEqual(ixy,     107., 10.));

   anglep.GetArea( &a_area, &a_cg);
   TRY_TESTME (a_area==area);
   TRY_TESTME (a_cg==cg);

   // turn our angle into a rectangle
   TRY_TESTME ((anglec.RemovePoint(p4)));
   TRY_TESTME ((anglec.RemovePoint(p5)));
   TRY_TESTME ((anglec.ReplacePoint(p3,gpPoint2d(60,75))));
   anglec.GetProperties( &area, &ixx, &iyy, &ixy, &cg);
   TRY_TESTME (IsEqual(area, 2000.));
   TRY_TESTME (IsEqual(ixx,  416666., 10.));
   TRY_TESTME (IsEqual(iyy,  266666., 10.));
   TRY_TESTME (IsEqual(ixy,  0., 1.));
   TRY_TESTME (anglec.GetBoundingBox() == gpRect2d(20,25,60,75));

   anglec.GetArea( &a_area, &a_cg);
   TRY_TESTME (a_area==area);
   TRY_TESTME (a_cg==cg);

   // create a line and find farthest point
   gpLine2d down_left(gpPoint2d(25,25), gpVector2d(gpSize2d(1,-1)));
   Float64 dist = anglec.GetFurthestDistance(down_left, gpLine2d::Left);
   TRY_TESTME (IsEqual(60.1,dist,.1));
   dist = anglec.GetFurthestDistance(down_left, gpLine2d::Right);
   TRY_TESTME (IsEqual(3.53, dist, .01));

   // create a rectangle and clip it into a triangle
   gpPolygon2d rect;
   p1 = rect.AddPoint(gpPoint2d(0 , 0));
   p2 = rect.AddPoint(gpPoint2d(0 ,50));
   p3 = rect.AddPoint(gpPoint2d(40,50));
   p4 = rect.AddPoint(gpPoint2d(40,0));
   gpLine2d up_left(gpPoint2d(0,0), gpVector2d(gpSize2d(1,1)));
   gpLine2d up_rgt(gpPoint2d(40,0), gpVector2d(gpSize2d(-3,5)));
   std::unique_ptr<gpPolygon2d> pfirst(rect.CreateClippedPolygon(up_left, gpLine2d::Right));
   pfirst->GetProperties( &area, &ixx, &iyy, &ixy, &cg);
   TRY_TESTME(IsEqual(area,800.));
   TRY_TESTME(IsEqual(cg.X(),26.666666667));
   TRY_TESTME(IsEqual(cg.Y(),13.333333333));

   std::unique_ptr<gpPolygon2d> ptriang(pfirst->CreateClippedPolygon(up_rgt, gpLine2d::Left));
   ptriang->GetProperties( &area, &ixx, &iyy, &ixy, &cg);
   TRY_TESTME (IsEqual(area, 500.));
   TRY_TESTME (ptriang->GetBoundingBox() == gpRect2d(0,0,40,25));

   ptriang->GetArea( &a_area, &a_cg);
   TRY_TESTME (a_area==area);
   TRY_TESTME (a_cg==cg);

   // clip triangle into a right triangle
   gpRect2d clip_box(0,5,20,25);
   std::unique_ptr<gpPolygon2d> prtri(ptriang->CreateClippedPolygon(clip_box, gpPolygon2d::In));
   prtri->GetProperties( &area, &ixx, &iyy, &ixy, &cg);
   TRY_TESTME (IsEqual(area, 112.5));
   TRY_TESTME (prtri->GetBoundingBox() == gpRect2d(5,5,20,20));

   // Try a simple square
   gpPolygon2d square;
   square.AddPoint(gpPoint2d(0,0));
   square.AddPoint(gpPoint2d(10,0));
   square.AddPoint(gpPoint2d(10,10));
   square.AddPoint(gpPoint2d(0,10));
   TRY_TESTME( IsEqual(square.Perimeter(),40.0) );

#if defined _DEBUG
   prtri->Dump(rlog.GetDumpCtx());
#endif

   TESTME_EPILOG("gpPolygon2d");
}

bool gpPolyPointIter2d::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("gpPolyPointIter2d");

   // create a polygon and iterate through its points
   gpPolygon2d anglep;
   Uint32 p1 = anglep.AddPoint(gpPoint2d(0 , 0));
   Uint32 p2 = anglep.AddPoint(gpPoint2d(0 ,50));
   Uint32 p3 = anglep.AddPoint(gpPoint2d(10,50));
   Uint32 p4 = anglep.AddPoint(gpPoint2d(10,10));
   Uint32 p5 = anglep.AddPoint(gpPoint2d(40,10));
   Uint32 p6 = anglep.AddPoint(gpPoint2d(40, 0));

   gpPolyPointIter2d my_it(&anglep);
   Uint32 i = 0;
   for(my_it.Begin(); my_it; my_it.Next())
   {
      i++;
      if (i==3)
         TRY_TESTME (p3 == *my_it.CurrentKey());
      if (i==4)
         TRY_TESTME (gpPoint2d(10,10) == *my_it.CurrentPoint());
      if (i==5)
         TRY_TESTME (p5 == *my_it.CurrentKey());
   }

   my_it.Prev();
   TRY_TESTME (p6 == *my_it.CurrentKey());

   TRY_TESTME ( anglep.RemovePoint(p4) );
   TRY_TESTME ( anglep.RemovePoint(p5) );
   TRY_TESTME ( anglep.ReplacePoint( p3,gpPoint2d(60,75) ) );

   my_it.End();
   gpPolyPointIter2d new_it = my_it;
   new_it.Prev();
   new_it.Prev();
   TRY_TESTME (gpPoint2d(60,75) == *new_it.CurrentPoint());

#if defined _DEBUG
   my_it.Dump(rlog.GetDumpCtx());
#endif

   TESTME_EPILOG("gpPolyPointIter2d");
}
#endif // _UNITTEST


