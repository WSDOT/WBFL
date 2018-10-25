///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
// Copyright © 1999-2011  Washington State Department of Transportation
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

#include <GeomModel\GeomModelLib.h>
#include <GeomModel\CircularSegment.h>
#include <GeomModel\Polygon.h>
#include <GeomModel\Properties.h>
#include <GeomModel\ShapeUtils.h>
#include <EngTools\MohrCircle.h>
#include <GeometricPrimitives\Circle.h>
#include <GeometricPrimitives\GeomOp2d.h>
#include <MathEx.h>
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   gmCircularSegment
****************************************************************************/


// number of vertex points used to describe a polyline version of a circle
const int NUM_POINTS=32;
////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
gmCircularSegment::gmCircularSegment()
{
   Init();
}

gmCircularSegment::gmCircularSegment(const gpPoint2d& center,Float64 radius,Float64 midOrdinate,Float64 rotation)
{
   PRECONDITION(radius>=0);
   Init();
   m_Center      = center;
   m_Radius      = radius;
   m_MidOrdinate = midOrdinate;
   m_Rotation    = rotation;

   UpdateHookPoint();
}


gmCircularSegment::~gmCircularSegment()
{
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

gpPoint2d gmCircularSegment::SetHookPoint(const gpPoint2d& hookPnt)
{
   gpSize2d delta = hookPnt - m_HookPoint;
   
   gpPoint2d tmp = m_HookPoint;
   m_HookPoint = hookPnt;

   m_Center += delta;

   NotifyAllListeners(gmShapeListener::PROPERTIES);
   return tmp;
}

gpPoint2d gmCircularSegment::GetHookPoint() const
{
   return m_HookPoint;
}

gpPoint2d gmCircularSegment::SetCenter(const gpPoint2d& center)
{
   gpPoint2d tmp = m_Center;
   m_Center = center;
   UpdateHookPoint();
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   return tmp;
}

gpPoint2d gmCircularSegment::GetCenter() const
{
   return m_Center;
}

Float64 gmCircularSegment::SetRadius(Float64 r)
{
   PRECONDITION(r>=0);
   Float64 tmp = m_Radius;
   m_Radius = r;
   UpdateHookPoint();
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   return tmp;
}

Float64 gmCircularSegment::GetRadius() const
{
   return m_Radius;
}

Float64 gmCircularSegment::SetMidOrdinate(Float64 mo)
{
   PRECONDITION(mo >= 0);
   Float64 tmp = m_MidOrdinate;
   m_MidOrdinate = mo;
   UpdateHookPoint();
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   return tmp;
}

Float64 gmCircularSegment::GetMidOrdinate() const
{
   return m_MidOrdinate;
}

Float64 gmCircularSegment::SetRotation(Float64 rotation)
{
   Float64 tmp = m_Rotation;
   m_Rotation = rotation;
   UpdateHookPoint();
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   return tmp;
}

Float64 gmCircularSegment::GetRotation() const
{
   return m_Rotation;
}

Float64 gmCircularSegment::SetInteriorAngle(Float64 ia)
{
   PRECONDITION( 0 <= ia && ia <= TWO_PI );

   Float64 ia_old = GetInteriorAngle();

   m_MidOrdinate = m_Radius*(1.0 - cos(ia/2));
   UpdateHookPoint();
   NotifyAllListeners(gmShapeListener::PROPERTIES);

	return ia_old;
}

Float64 gmCircularSegment::GetInteriorAngle() const
{
   Float64 x = (m_Radius - m_MidOrdinate)/m_Radius;
   if ( IsZero(x-1.0) )
      x = 1.0;

   Float64 angle = acos(x);
	return 2.0*angle;
}

void gmCircularSegment::GetProperties(gmProperties* pProperties) const
{
   ASSERTVALID;

   // Compute properties for non-rotated shape, about global axes (0,0)
   Float64 angle = GetInteriorAngle()/2.0;
   Float64 area, ixx, iyy, ixy, cgx, cgy;

   if ( IsZero(angle) )
   {
      area = 0;
      ixx = 0;
      iyy = 0;
      ixy = 0;
      cgx = m_Radius;
      cgy = 0;
   }
   else
   {
      area = m_Radius*m_Radius*(angle - sin(2*angle)/2);
      ixx = (area*m_Radius*m_Radius/4)*(1 - (4*pow(sin(angle),3)*cos(angle))/(3*(2*angle - sin(2*angle))));
      iyy = (area*m_Radius*m_Radius/4)*(1 + (4*pow(sin(angle),3)*cos(angle))/(2*angle - sin(2*angle)));
      ixy = 0.00;

      cgx = (4*m_Radius/3) * pow(sin(angle),3)/(2*angle-sin(2*angle));
      cgy = 0.00;
   }

   gpPoint2d cg(cgx,cgy);

   // Transform properties to centroidal coordinates
   iyy = iyy - area*cgx*cgx;

   // Transform properties into rotated coordinate system
   etMohrCircle mohrCircle(ixx,iyy,ixy);
   mohrCircle.ComputeState(&ixx,&iyy,&ixy,m_Rotation);

   // deal with signs and hollowness
   if( (area > 0 && !IsSolid()))
   {
      area *= -1;
      ixx  *= -1;
      iyy  *= -1;
      ixy  *= -1;
   }

   // next need to translate and rotate CG to proper position
   cg.Offset(m_Center.X(),m_Center.Y());
   cg.Rotate(m_Center,m_Rotation);

   // Get bounded box in centroidal coordinates
   gpRect2d bb = GetBoundingBox();
   bb.Offset(-m_HookPoint.X(), -m_HookPoint.Y());
   
   // Perimeter
   Float64 arc_length;
   arc_length = 2.0*angle*m_Radius;

   Float64 chord_length;
   chord_length = 2*m_Radius*sin(angle);

   Float64 p = arc_length + chord_length;

   *pProperties =  gmProperties(area , cg, ixx, iyy, ixy, 
                                bb.Top(),bb.Bottom(),bb.Left(),bb.Right(),p);
}

gpRect2d gmCircularSegment::GetBoundingBox() const
{
   gpPoint2d p1,p2;
   EdgePoints(&p1,&p2);
   Float64 p1x = p1.X();
   Float64 p1y = p1.Y();
   Float64 p2x = p2.X();
   Float64 p2y = p2.Y();

   // Get boundary line
   gpLine2d line = BoundaryLine();

   Float64 c;
   gpVector2d n;
   line.GetImplicit(&c,&n); // normal to line
   Float64 nx,ny;
   nx = n.X();
   ny = n.Y();
   // drown out any noice in the vector
   nx = IsZero(nx) ? 0.00 : nx;
   ny = IsZero(ny) ? 0.00 : ny;

   // Center of circle
   Float64 cx, cy;
   cx = m_Center.X();
   cy = m_Center.Y();

   // Find sides
   Float64 left, right, top, bottom;

   // left
   if ( (IsZero(nx) && m_Radius < m_MidOrdinate) || 0.0 < nx )
      left = cx - m_Radius;
   else
      left = _cpp_min(p1x,p2x);

   // right
   if ( (IsZero(nx) && m_Radius < m_MidOrdinate) || nx < 0.0 )
      right = cx + m_Radius;
   else
      right = _cpp_max(p1x,p2x);

   // top
   if ( (IsZero(ny) && m_MidOrdinate < m_Radius) || 0.0 < ny )
      top = _cpp_max(p1y,p2y);
   else
      top = cy + m_Radius;

   // bottom
   if ( (IsZero(ny) && m_MidOrdinate < m_Radius) || ny < 0.0 )
      bottom = _cpp_min(p1y,p2y);
   else
      bottom = cy - m_Radius;

   return gpRect2d(left,bottom,right,top);
}

gmIShape* gmCircularSegment::CreateClone(bool bRegisterListeners) const
{
   std::auto_ptr<gmCircularSegment> ph(new gmCircularSegment( *this ));// no memory leaks if DoRegister() throws

   // copy listeners if requested.
   if (bRegisterListeners)
      ph->DoRegisterListeners(*this);

   return ph.release();
}

gmIShape* gmCircularSegment::CreateClippedShape(const gpLine2d& line, 
                                    gpLine2d::Side side) const
{
   // boundary case: if radius is zero - return zero
   if (m_Radius<=0)
      return 0;

   // This routine always clips away the left side of the line, leaving
   // the portion of the shape on the right side.
   // If the right side clipping is requested, reverse the direction of
   // the clipping line
   gpLine2d clipLine = line;
   if ( side == gpLine2d::Right )
      clipLine.Reverse();

   // since clipping a circular segment is very expensive
   // first determine if shape really needs to be clipped.
   gpGeomOp2d geomUtil;

      // Determine if the shape is on the left or right of the line.
   // Create a line through the center of the circle and parallel to the clipping line
   gpLine2d centerLine = clipLine.Parallel(m_Center);

   // Get implicit version of the two lines. since they are parallel, their vectors should
   // be equal.
   // The distance between the two lines will be the offset (c) value.
   // The left-most line will always have the largest c value.
   Float64 clip_c, ctr_c;
   gpVector2d clip_v, ctr_v;
   clipLine.GetImplicit(&clip_c,&clip_v);
   centerLine.GetImplicit(&ctr_c,&ctr_v);

   CHECK(clip_v==ctr_v); // lines must be parallel

   // distance between lines. if positive, clipping line is to left of centerline
   Float64 dist = clip_c - ctr_c;

   if (fabs(dist)<= m_Radius)
   {
      // Clipping line intersects the shape
      // If the clipping line is in the same direction as the edge line,
      // the resulting shape is a circular segment, unless the clipping line and
      // edge line intersect on the shape boundary

      gpLine2d edge = BoundaryLine();
      Float64 c;
      gpVector2d n1; // normal to edge
      gpVector2d n2; // normal to clipping line;
      edge.GetImplicit(&c,&n1);
      clipLine.GetImplicit(&c,&n2);

      Float64 dot;
      dot = n1.Dot(n2);

      if ( dot < 0 )
      {
         // Lines are in opposite direct

         // Make shape into a Polygon and use its clip
         std::auto_ptr<gmPolygon> polygon( CreatePolygon() );
         return polygon->CreateClippedShape(line,side);
      }
      else
      {
         // Lines are same direction
         // Check the interesction point
         gpPoint2d s;
         gpPoint2d e;
         EdgePoints(&s,&e);
         gpLineSegment2d ls(s,e);

         gpPoint2d is; // intersection point
         Int16 nIntersect = geomUtil.Intersect(&is,ls,line);

         if ( nIntersect != 0 )
         {
            // Clipping line intersects straight edge of shape
            // Make shape into a Polygon and use its clip
            std::auto_ptr<gmPolygon> polygon( CreatePolygon() );
            return polygon->CreateClippedShape(line,side);
         }
         else
         {
            // resulting shape is a circular segment
            gmIShape* clone = CreateClone();
            gmCircularSegment* cloneShape = dynamic_cast<gmCircularSegment*>(clone);

            Float64 nx,ny;
            nx = n2.X();
            ny = n2.Y();
            Float64 rotation = atan2(-ny,-nx);
            cloneShape->SetRotation(rotation);

            Float64 dist;
            dist = clipLine.DistanceToPoint(m_Center);
            cloneShape->SetMidOrdinate(m_Radius - dist);
            return clone;
         }
         CHECK(false); // should never get here
      }
   }
   else if (dist>0)
   {
      // clip line is to left of shape
      // circle is entirely within clipping region
      return CreateClone();
   }
   else
   {
      // circle is entirely outside of clipping region
      return 0;
   }

   CHECK(false); // should never get here
   return 0;
}

gmIShape* gmCircularSegment::CreateClippedShape(const gpRect2d& r,
                                     gmShapeImp::ClipRegion region
                                     ) const
{
   // make shape into a gmpolygon and use its clip
   std::auto_ptr<gmPolygon> poly(CreatePolygon());
   return poly->CreateClippedShape(r, region);
}

Float64 gmCircularSegment::GetFurthestDistance(const gpLine2d& line, gpLine2d::Side side) const
{
   Float64 dist;
   gpLine2d bndLine = BoundaryLine();

   Float64 temp;
   gpVector2d n1; // normal of boundary line
   gpVector2d n2; // normal of input line

   bndLine.GetImplicit(&temp,&n1);
   line.GetImplicit(&temp,&n2);

   Float64 dot;
   dot = n1.Dot(n2);

   // if dot < 0, the line in question and the straight edge of the shape
   // are in opposite directions

   if ( dot < 0 )
   {
      // Lines are in opposite direction.
      // The furthest distance is the greater of the shorter distance from the line
      // to the edge points of the shape.
      Float64 d1, d2;
      gpPoint2d p1, p2;
      EdgePoints(&p1,&p2);
      d1 = line.DistanceToPoint(p1);
      d2 = line.DistanceToPoint(p2);
      dist = _cpp_max(d1,d2);
   }
   else
   {
      // Lines are in the same direction. The furthest distance is the
      // shortest distance from the line to the center of the circle plus
      // the radius
      Float64 distToCenter; // Shortest distance from line to center of circle
                           // if < 0, circle is to the left of the line
      distToCenter = line.DistanceToPoint(m_Center);
 
      dist = m_Radius + distToCenter;
  }

   return dist;
}

void gmCircularSegment::Draw(HDC hDC, const grlibPointMapper& mapper) const
{
   std::auto_ptr<gmPolygon> poly(CreatePolygon());
   poly->Draw(hDC,mapper);
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool gmCircularSegment::AssertValid() const
{
   if ( m_Radius < 0 )
      return false;

   if ( m_MidOrdinate < 0 || (2*m_Radius) < m_MidOrdinate )
      return false;

   return gmShapeImp::AssertValid();
}

void gmCircularSegment::Dump(dbgDumpContext& os) const
{
   os << _T("*** Dump for gmCircularSegment ***")<<endl;
   gmShapeImp::Dump( os );
   os << _T("  Hook Point      = (") <<m_HookPoint.X()<<_T(", ")<<m_HookPoint.Y()<<_T(")")<<endl;
   os << _T("  Center Point    = (") << m_Center.X() << _T(", ") << m_Center.Y() <<_T(")") << endl;
   os << _T("  Radius          = ") << m_Radius      << endl;
   os << _T("  Mid-ordinate    = ") << m_MidOrdinate << endl;
}
#endif // _DEBUG

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
gmCircularSegment::gmCircularSegment(const gmCircularSegment& rOther) :
gmShapeImp(rOther)
{
   MakeCopy(rOther);
}

gmCircularSegment& gmCircularSegment::operator= (const gmCircularSegment& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void gmCircularSegment::DoTranslate(const gpSize2d& delta)
{
   m_Center.Offset(delta);
   UpdateHookPoint();
}

void gmCircularSegment::DoRotate(const gpPoint2d& center, Float64 angle)
{
   gpGeomOp2d geomUtil;

   m_Center.Rotate(center,angle);
   m_Rotation += angle;
   m_Rotation = geomUtil.NormalizeAngle(m_Rotation);
   UpdateHookPoint();
}

void gmCircularSegment::MakeCopy(const gmCircularSegment& rOther)
{
   m_Radius      = rOther.m_Radius;
   m_HookPoint   = rOther.m_HookPoint;
   m_Center      = rOther.m_Center;
   m_MidOrdinate = rOther.m_MidOrdinate;
   m_Rotation    = rOther.m_Rotation;
}

void gmCircularSegment::MakeAssignment(const gmCircularSegment& rOther)
{
   gmShapeImp::MakeAssignment( rOther );
   MakeCopy( rOther );
}


//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

gmPolygon* gmCircularSegment::CreatePolygon() const
{
   ASSERTVALID;

   // make an empty polygon with same traits as this.
   std::auto_ptr<gmPolygon> ph(new gmPolygon());
   gmShapeUtils::CopyTraits(*this, ph.get());

   // number of vertex points used to describe a polyline version of a circle
   const short NUM_POINTS = 36; // 36 segments.

   Float64 angle = GetInteriorAngle()/2.0;
   Float64 angle_inc = 2*angle / (NUM_POINTS-1);

   // determine radius of circle to make an "Area Perfect" polygon.
   Float64 cfArea = m_Radius*m_Radius*(angle - sin(2*angle)/2); // closed form area

   Float64 rad = sqrt( cfArea/(((NUM_POINTS-1)*sin(angle_inc/2)*cos(angle_inc/2) - sin(angle)*cos(angle))) );

#if defined _DEBUG
   Float64 polyArea = (NUM_POINTS-1)*(rad*rad*sin(angle_inc/2)*cos(angle_inc/2))-rad*rad*sin(angle)*cos(angle);
   CHECK( IsEqual(cfArea,polyArea) );
#endif // _DEBUG

   Float64 cx,cy;
   cx = m_Center.X();
   cy = m_Center.Y();

   Float64 startAngle = m_Rotation - angle;

   for (short i = 0; i < NUM_POINTS; i++)
   {
      Float64 a = startAngle + i * angle_inc;

      Float64 x = cx + rad * cos(a);
      Float64 y = cy + rad * sin(a);

      gpPoint2d p(x,y);

      ph->AddPoint(p);
   }

   return ph.release();
}

void gmCircularSegment::Init()
{
   m_Radius      = 0.0;
   m_MidOrdinate = 0.0;
   m_Rotation    = 0.0;
   m_Center      = gpPoint2d(0,0);
   m_HookPoint   = gpPoint2d(0,0);
}

void gmCircularSegment::UpdateHookPoint()
{
   Float64 x,y;
   x = m_Center.X() + (m_Radius-m_MidOrdinate)*cos(m_Rotation);
   y = m_Center.Y() + (m_Radius-m_MidOrdinate)*sin(m_Rotation);

   m_HookPoint.Move(x,y);
}

void gmCircularSegment::EdgePoints(gpPoint2d* p1,gpPoint2d* p2) const
{
   Float64 cx,cy;
   cx = m_Center.X();
   cy = m_Center.Y();

   Float64 angle = GetInteriorAngle();

   if (IsEqual(angle,TWO_PI))
      angle -= 0.01; // Prevent the closed circle case

   Float64 x1,y1;
   Float64 x2,y2;

   x1 = cx + m_Radius * cos(m_Rotation - angle/2);
   y1 = cy + m_Radius * sin(m_Rotation - angle/2);

   x2 = cx + m_Radius * cos(m_Rotation + angle/2);
   y2 = cy + m_Radius * sin(m_Rotation + angle/2);

   p1->Move(x1,y1);
   p2->Move(x2,y2);

   // Both points can't be the same.
   CHECK( !(IsEqual(x1,x2) && IsEqual(y1,y2)) );
}

gpLine2d gmCircularSegment::BoundaryLine() const
{
   // Create the boundary line that forms the straight edge of the shape
   gpPoint2d p1,p2;
   EdgePoints(&p1,&p2);

   gpLine2d line;
   line.SetPoints(p1,p2);
   return line;
}

//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

#if defined _UNITTEST
#include <GeomModel\Polygon.h>
bool gmCircularSegment::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("gmCircularSegment");

   Float64 radius = 50;
   Float64 mo = radius;
   gmCircularSegment circseg(gpPoint2d(0,0),radius,mo,0);
   gmProperties props;

   circseg.GetProperties(&props);

   TRY_TESTME( IsEqual(props.Area(),M_PI*radius*radius/2) );
   TRY_TESTME( IsEqual(props.Ixx(),M_PI*radius*radius*radius*radius/8) );
   TRY_TESTME( IsEqual(props.Iyy(),pow(radius,4)*(9*M_PI*M_PI-64)/(72*M_PI)) );
   TRY_TESTME( IsEqual(props.Ixy(),0.0) );
   TRY_TESTME( IsEqual(props.Centroid().X(),4*radius/(3*M_PI)) );
   TRY_TESTME( IsEqual(props.Centroid().Y(),0.0) );
   TRY_TESTME( props.GetCoordinateSystem() == gmProperties::Centroidal );

   // rotate 90 deg and check results
   circseg.SetRotation(PI_OVER_2);
   circseg.GetProperties(&props);
   TRY_TESTME( IsEqual(props.Area(),M_PI*radius*radius/2) );
   TRY_TESTME( IsEqual(props.Ixx(),pow(radius,4)*(9*M_PI*M_PI-64)/(72*M_PI)) );
   TRY_TESTME( IsEqual(props.Iyy(),M_PI*radius*radius*radius*radius/8) );
   TRY_TESTME( IsEqual(props.Ixy(),0.0) );
   TRY_TESTME( IsEqual(props.Centroid().X(),0.0) );
   TRY_TESTME( IsEqual(props.Centroid().Y(),4*radius/(3*M_PI)) );
   TRY_TESTME( props.GetCoordinateSystem() == gmProperties::Centroidal );

   ////////////////////////////
   // Test Polygon
   Float64 px[] = {
      51.73693885,
      53.76574463,
      55.52668195,
      57.00897296,
      58.20354531,
      59.10308761,
      59.7020942,
      59.99689886,
      59.98569724,
      59.66855789,
      59.04742187,
      58.12609085,
      56.91020383,
      55.40720267,
      53.62628648,
      51.57835537,
      49.27594372,
      46.73314345,
      43.96551778,
      40.99000598,
      37.82481969,
      34.48933144,
      31.0039561,
      27.39002595,
      23.66966004,
      19.86562891,
      16.00121515,
      12.10007092,
      8.186073192,
      4.283177614,
      0.415271877,
      -3.393970481,
      -7.121234972,
      -10.74370885,
      -14.23922076,
      -17.58637638
   };

   Float64 py[] = {
      -17.58637638,
      -14.23922076,
      -10.74370885,
      -7.121234972,
      -3.393970481,
      0.415271877,
      4.283177614,
      8.186073192,
      12.10007092,
      16.00121515,
      19.86562891,
      23.66966004,
      27.39002595,
      31.0039561,
      34.48933144,
      37.82481969,
      40.99000598,
      43.96551778,
      46.73314345,
      49.27594372,
      51.57835537,
      53.62628648,
      55.40720267,
      56.91020383,
      58.12609085,
      59.04742187,
      59.66855789,
      59.98569724,
      59.99689886,
      59.7020942,
      59.10308761,
      58.20354531,
      57.00897296,
      55.52668195,
      53.76574463,
      51.73693885
   };

   circseg.SetRotation(M_PI/4);
   circseg.SetRadius(50);
   circseg.SetMidOrdinate(40);
   circseg.SetCenter(gpPoint2d(10,10));

   std::auto_ptr<gmPolygon> polygon( circseg.CreatePolygon() );

   long nPoints = sizeof(px)/sizeof(Float64);
   long cPoints = polygon->GetNumPoints();
   TRY_TESTME(cPoints == nPoints); // nPoints polypoints
   gmPolyPointIter iter(polygon.get());
   long i = 0;
   for ( iter.Begin(); iter; iter.Next() )
   {
      const gpPoint2d* p = iter.CurrentPoint();

      TRY_TESTME(IsEqual(p->X(),px[i]));
      TRY_TESTME(IsEqual(p->Y(),py[i]));
      i++;
   }

   ////////////////////////////
   // Test ClipWithLine
   circseg.SetRotation(0.0);
   radius = 50;
   mo = radius;
   circseg.SetRadius(radius);
   circseg.SetMidOrdinate(mo);
   circseg.SetCenter(gpPoint2d(10,10));

   // clipping line well below shape (shape on right of line)
   gpLine2d line(gpPoint2d(100,-70),gpPoint2d(-100,-70));
   std::auto_ptr<gmIShape> clipShape(circseg.CreateClippedShape(line,gpLine2d::Left));
   clipShape->GetProperties(&props);
   TRY_TESTME(IsEqual(props.Area(),M_PI*radius*radius/2));

   // reverse clipping line (shape on left of line)
   // entire shape clipped away
   clipShape = std::auto_ptr<gmIShape>(circseg.CreateClippedShape(line,gpLine2d::Right));
   TRY_TESTME(clipShape.get() == NULL);

   // clip shape in such a way that we are left with a quarter circle
   circseg.SetCenter(gpPoint2d(100,100));
   circseg.SetRotation(PI_OVER_2);
   radius = 50;
   mo = radius;
   circseg.SetRadius(radius);
   circseg.SetMidOrdinate(mo);

   line.SetPoints(gpPoint2d(100,-500),gpPoint2d(100,500));

   clipShape = std::auto_ptr<gmIShape>(circseg.CreateClippedShape(line,gpLine2d::Left));
   clipShape->GetProperties(&props);
   Float64 val1 = props.Area();
   Float64 val2 = M_PI*radius*radius/4;
   TRY_TESTME(IsEqual(val1,val2,0.01));

   // Test relative correctness of centroid.
   // Should be left and above center of circle
   // and x and y should be equal.
   TRY_TESTME(props.Centroid().X() > 100);
   TRY_TESTME(props.Centroid().Y() > 100);
   TRY_TESTME(IsEqual(props.Centroid().X(),props.Centroid().Y(),0.0001));

   // clip in such a way the the result is still a circular segment
   circseg.SetCenter(gpPoint2d(0,0));
   radius = 50;
   mo = 60;
   circseg.SetRadius(radius);
   circseg.SetMidOrdinate(mo);
   circseg.SetRotation(0);
   line.SetPoints(gpPoint2d(40,-100),gpPoint2d(40,100));
   clipShape = std::auto_ptr<gmIShape>(circseg.CreateClippedShape(line,gpLine2d::Left));
   gmCircularSegment* clip = dynamic_cast<gmCircularSegment*>(clipShape.get());
   TRY_TESTME(clip != 0);
   // center and radius should be the same
   TRY_TESTME(IsEqual(circseg.GetRadius(),clip->GetRadius()));
   TRY_TESTME(IsEqual(circseg.GetCenter().X(),clip->GetCenter().X()));
   TRY_TESTME(IsEqual(circseg.GetCenter().Y(),clip->GetCenter().Y()));
   // mid-ordinate should be the radius less the original mid-ordinate
   TRY_TESTME(IsEqual(clip->GetMidOrdinate(),mo-radius));

   // reverse the direction of the clipping line
   // result should be a polygon.
   // area clip = area shape - area clip from above
   //
   // get area of source shape and the clip shape from above
   Float64 area1, area2, area3;
   circseg.GetProperties(&props);
   area1 = props.Area();

   clip->GetProperties(&props);
   area2 = props.Area();

   clipShape = std::auto_ptr<gmIShape>(circseg.CreateClippedShape(line,gpLine2d::Right));

   clipShape->GetProperties(&props);
   area3 = props.Area();
   val1 = area1 - area2;
   TRY_TESTME( IsEqual(area3,val1,0.35) );

   // run a clipping line through the straight edge of the shape
   // Clip with line going both direction. Sum of clipped shape areas
   // must be equal to the area of the original shape
   circseg.SetCenter(gpPoint2d(0,0));
   circseg.SetRadius(100);
   circseg.SetMidOrdinate(70);
   circseg.SetRotation(0);
   circseg.GetProperties(&props);
   area1 = props.Area();

   line.SetPoints(gpPoint2d(90,90),gpPoint2d(20,-60));
   clipShape = std::auto_ptr<gmIShape>(circseg.CreateClippedShape(line,gpLine2d::Left));
   clipShape->GetProperties(&props);
   area2 = props.Area();

   clipShape = std::auto_ptr<gmIShape>(circseg.CreateClippedShape(line,gpLine2d::Right));
   clipShape->GetProperties(&props);
   area3 = props.Area();

   val1 = area2 + area3;
   TRY_TESTME(IsEqual(area1,val1));

   // same as above, but this time shape is a full circle (interior angle = 360)
   circseg.SetCenter(gpPoint2d(0,0));
   circseg.SetRadius(50);
   circseg.SetMidOrdinate(100);
   circseg.SetRotation(0);
   circseg.GetProperties(&props);
   area1 = props.Area();

   line.SetPoints(gpPoint2d(-50,-50),gpPoint2d(50,50));

   clipShape = std::auto_ptr<gmIShape>(circseg.CreateClippedShape(line,gpLine2d::Left));
   clipShape->GetProperties(&props);
   area2 = props.Area();
   TRY_TESTME(IsEqual(area2*2,area1,0.001)); // clip shape half circle

   Float64 cgx1,cgy1;
   cgx1 = props.Centroid().X();
   cgy1 = props.Centroid().Y();

   clipShape = std::auto_ptr<gmIShape>(circseg.CreateClippedShape(line,gpLine2d::Right));
   clipShape->GetProperties(&props);
   area3 = props.Area();
   TRY_TESTME(IsEqual(area3*2,area1,0.5)); // clip shape half circle

   Float64 cgx2,cgy2;
   cgx2 = props.Centroid().X();
   cgy2 = props.Centroid().Y();

   val1 = area2 + area3;
   TRY_TESTME(IsEqual(area1,val1,0.2));

   TRY_TESTME(IsEqual(cgx1,-cgx2,0.001));
   TRY_TESTME(IsEqual(cgy1,-cgy2,0.001));

///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////

//   gmCircularSegment rt(gpPoint2d(2,2),2);
//   TRY_TESTME( IsEqual(2., rt.GetRadius())) 
//   TRY_TESTME(gpPoint2d(2,2) == rt.GetHookPoint()) 
//   gmProperties aprops;
//   rt.GetProperties(&aprops);
//   TRY_TESTME (IsEqual(aprops.Area(), 12.566, .01)) 
//   TRY_TESTME (IsEqual(aprops.Ixx(),  12.56, .1)) 
//   TRY_TESTME (IsEqual(aprops.Iyy(),  12.56, .1)) 
//   TRY_TESTME (IsEqual(aprops.Ixy(),   0.00, .001)) 
//   TRY_TESTME (rt.GetBoundingBox() == gpRect2d(0,0,4,4)) 
//
//   rt.SetHookPoint(gpPoint2d(0,0));
//   TRY_TESTME (rt.GetBoundingBox() == gpRect2d(-2,-2,2,2)) 
//   rt.Move(gmIShape::CenterCenter, gpPoint2d(2,2));
//   TRY_TESTME (rt.GetBoundingBox() == gpRect2d(0,0,4,4)) 
//
//   Float64 ang = atan(1.);
//   Float64 dis = 2/cos(ang);
//   rt.Rotate(gpPoint2d(0,0),ang);
//   TRY_TESTME (rt.GetBoundingBox() == gpRect2d(-2,dis-2,2,dis+2)) 
//
//   // Resize circle and clip it into a hemi
//   rt.SetRadius(40);
//   rt.SetHookPoint(gpPoint2d(0,40));
//   gpLine2d at45(gpPoint2d(0,40), gpVector2d(gpSize2d(1,1)));
//   std::auto_ptr<gmIShape> phemi(rt.CreateClippedShape(at45, gpLine2d::Right));
//   phemi->GetProperties(&aprops);
//   TRY_TESTME (IsEqual(aprops.Area(), 2513.2,.1)) 
//
//   // clip should return entire circle
//   rt.SetHookPoint(gpPoint2d(60,0));
//   std::auto_ptr<gmIShape> prt(rt.CreateClippedShape(at45, gpLine2d::Right));
//   prt->GetProperties(&aprops);
//   TRY_TESTME (IsEqual(aprops.Area(), 5026.55,.1)) 
//
//#if defined _DEBUG
//   rt.Dump(rlog.GetDumpCtx());
//#endif

   TESTME_EPILOG("gmCircularSegment");
}

#endif // _UNITTEST



