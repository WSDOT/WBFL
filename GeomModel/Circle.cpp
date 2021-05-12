///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
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

#include <GeomModel\GeomModelLib.h>
#include <GeomModel\Circle.h>
#include <GeomModel\CircularSegment.h>
#include <GeomModel\Polygon.h>
#include <GeomModel\Properties.h>
#include <GeomModel\ShapeUtils.h>
#include <mathEx.h>
#include <iostream>
#include <memory>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   gmCircle
****************************************************************************/


// number of vertex points used to describe a polyline version of a circle
const int NUM_POINTS=32;
////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
gmCircle::gmCircle()
{
   Init();
}

gmCircle::gmCircle(const gpPoint2d& hookPnt,Float64 radius)
{
   PRECONDITION(radius>=0);
   Init();
   m_HookPoint = hookPnt;
   m_Radius    = radius;
}


gmCircle::~gmCircle()
{
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

gpPoint2d gmCircle::SetHookPoint(const gpPoint2d& hookPnt)
{
   gpPoint2d tmp = m_HookPoint;
   m_HookPoint = hookPnt;
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   return tmp;
}

gpPoint2d gmCircle::GetHookPoint() const
{
   return m_HookPoint;
}

Float64 gmCircle::SetRadius(Float64 r)
{
   PRECONDITION(r>=0);
   Float64 tmp = m_Radius;
   m_Radius = r;
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   return tmp;
}

Float64 gmCircle::GetRadius() const
{
   return m_Radius;
}

void gmCircle::GetProperties(gmProperties* pProperties) const
{
   ASSERTVALID;
   // get non-rotated properties
   Float64 area = M_PI * m_Radius * m_Radius;
   Float64 ixx  = M_PI * pow(m_Radius,4.)/4.;
   Float64 iyy  = ixx;
   Float64 ixy  = 0;

   // deal with signs and hollowness
   if( (area>0 && !IsSolid()))
   {
      area *= -1;
      ixx  *= -1;
      iyy  *= -1;
      ixy  *= -1;
   }
   // bounding box in centroidal coords
   gpRect2d bb = GetBoundingBox();
   bb.Offset(-m_HookPoint.X(), -m_HookPoint.Y());

   // Perimeter
   Float64 p = 2.0*M_PI*m_Radius;

   *pProperties =  gmProperties(area , m_HookPoint, ixx, iyy, ixy, 
                                bb.Top(),bb.Bottom(),bb.Left(),bb.Right(),p);
}

void gmCircle::GetArea(Float64* pArea, gpPoint2d* pCG) const
{
   *pArea = M_PI * m_Radius * m_Radius;

   // deal with signs and hollowness
   if( (*pArea>0 && !IsSolid()))
   {
      *pArea *= -1;
   }

   *pCG = m_HookPoint;
}

gpRect2d gmCircle::GetBoundingBox() const
{
   // use a point to determine box height and width
   Float64 top   = m_HookPoint.Y() + m_Radius;
   Float64 right = m_HookPoint.X() + m_Radius;
   Float64 bottom= m_HookPoint.Y() - m_Radius;
   Float64 left  = m_HookPoint.X() - m_Radius;

   return gpRect2d(left,bottom,right,top);
}


gmIShape* gmCircle::CreateClone(bool bRegisterListeners) const
{
   std::unique_ptr<gmCircle> ph(new gmCircle( *this ));// no memory leaks if DoRegister() throws

   // copy listeners if requested.
   if (bRegisterListeners)
      ph->DoRegisterListeners(*this);

   return ph.release();
}

gmIShape* gmCircle::CreateClippedShape(const gpLine2d& line, 
                                    gpLine2d::Side side) const
{
   // since clipping a circle is very expensive
   // first determine if circle really needs to be clipped.
   Float64 distance = line.DistanceToPoint(m_HookPoint);

   if (fabs(distance) <=m_Radius)
   {
      // circle touces line, must clip
      // Resulting shape is a circular segment
      std::unique_ptr<gmCircularSegment> clip(std::make_unique<gmCircularSegment>());
      clip->SetCenter(m_HookPoint);
      clip->SetRadius(m_Radius);

      Float64 c;
      gpVector2d n;
      line.GetImplicit(&c,&n);

      Float64 nx,ny;
      nx = n.X();
      ny = n.Y();
      Float64 rotation = atan2(-ny,-nx);
      if ( side == gpLine2d::Right )
         rotation += M_PI;
      clip->SetRotation(rotation);

      clip->SetMidOrdinate(m_Radius + distance);

      return clip.release();

// OLD IMPLEMENTATION
//      // make shape into a gmpolygon and use its clip
//      std::auto_ptr<gmPolygon> poly(CreatePolygon());
//      return poly->CreateClippedShape(line,side);
   }
   else
   {
      // now need to find out which side of line circle is on.
      if (side==gpLine2d::Left) distance = -distance;

      if (distance>0)
      {
         // circle is entirely within clipping region
         return new gmCircle(*this);
      }
      else
      {
         // circle is entirely outside of clipping region
         return nullptr;
      }
   }
}

gmIShape* gmCircle::CreateClippedShape(const gpRect2d& r,
                                     gmShapeImp::ClipRegion region
                                     ) const
{
   // make shape into a gmpolygon and use its clip
   std::unique_ptr<gmPolygon> poly(CreatePolygon());
   return poly->CreateClippedShape(r, region);
}

void gmCircle::ComputeClippedArea(const gpLine2d& line, gpLine2d::Side side,
                                   Float64* pArea, gpPoint2d* pCG) const
{
   // since clipping a circle is very expensive
   // first determine if circle really needs to be clipped.
   Float64 distance = line.DistanceToPoint(m_HookPoint);

   if (fabs(distance) <=m_Radius)
   {
      // circle touces line, must clip
      // Resulting shape is a circular segment
      gmCircularSegment clip;
      clip.SetCenter(m_HookPoint);
      clip.SetRadius(m_Radius);

      Float64 c;
      gpVector2d n;
      line.GetImplicit(&c,&n);

      Float64 nx,ny;
      nx = n.X();
      ny = n.Y();
      Float64 rotation = atan2(-ny,-nx);
      if ( side == gpLine2d::Right )
         rotation += M_PI;
      clip.SetRotation(rotation);

      clip.SetMidOrdinate(m_Radius + distance);

      gmProperties props;
      clip.GetProperties(&props);

      *pArea = props.Area();
      *pCG   = props.Centroid();
   }
   else
   {
      // now need to find out which side of line circle is on.
      if (side==gpLine2d::Left) distance = -distance;

      if (distance>0)
      {
         // circle is entirely within clipping region
         *pArea = M_PI*m_Radius*m_Radius;
         if (!IsSolid())
            *pArea*=-1.;

         *pCG   = m_HookPoint;
      }
      else
         // circle is entirely outside of clipping region
         *pArea = 0;
         *pCG   = m_HookPoint;
   }
}


Float64 gmCircle::GetFurthestDistance(const gpLine2d& line, gpLine2d::Side side) const
{
   // get distance from left side of line to center
   Float64 dist = line.DistanceToPoint(m_HookPoint);
   if (side==gpLine2d::Right)
      dist = -dist;

   dist += m_Radius;

   return dist;
}

void gmCircle::Draw(HDC hDC, const grlibPointMapper& mapper) const
{
   std::unique_ptr<gmPolygon> poly(CreatePolygon());
   poly->Draw(hDC,mapper);
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool gmCircle::AssertValid() const
{
   if (m_Radius<0) return false;
   return gmShapeImp::AssertValid();
}

void gmCircle::Dump(dbgDumpContext& os) const
{
   os << _T("*** Dump for gmCircle ***")<<endl;
   gmShapeImp::Dump( os );
   os << _T("  Hook Point      = (")<<m_HookPoint.X()<<_T(", ")<<m_HookPoint.Y()<<_T(")")<<endl;
   os << _T("  Radius          =  ")<<m_Radius  <<endl;
}
#endif // _DEBUG

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
gmCircle::gmCircle(const gmCircle& rOther) :
gmShapeImp(rOther)
{
   MakeCopy(rOther);
}

gmCircle& gmCircle::operator= (const gmCircle& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

void gmCircle::DoTranslate(const gpSize2d& delta)
{
   m_HookPoint.Offset(delta);
}

void gmCircle::DoRotate(const gpPoint2d& center, Float64 angle)
{
   m_HookPoint.Rotate(center, angle);
}


void gmCircle::MakeCopy(const gmCircle& rOther)
{
   m_Radius    = rOther.m_Radius;
   m_HookPoint = rOther.m_HookPoint;
}

void gmCircle::MakeAssignment(const gmCircle& rOther)
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
gmPolygon* gmCircle::CreatePolygon() const
{
   if (m_Radius <= 0) 
      return nullptr;

   // make an empty polygon with same traits as this.
   std::unique_ptr<gmPolygon> ph(std::make_unique<gmPolygon>());
   gmShapeUtils::CopyTraits(*this, ph.get());

   Float64 angle_inc = 2*M_PI/NUM_POINTS;

   // determine radius of circle to make an "Area Perfect" polycircle.
   Float64 rad = sqrt(M_PI * m_Radius * m_Radius / 
                      (NUM_POINTS * sin(M_PI/NUM_POINTS) * cos(M_PI/NUM_POINTS)));

   for (Int32 i = 0; i<=NUM_POINTS; i++)
   {
      Float64 a = i * angle_inc;
      Float64 x = m_HookPoint.X() + rad * cos(a);
      Float64 y = m_HookPoint.Y() + rad * sin(a);
      ph->AddPoint(gpPoint2d(x,y));
   }

   return ph.release();
}

void gmCircle::Init()
{
   m_Radius    = 0.;
   m_HookPoint = gpPoint2d(0,0);
}

//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

#if defined _UNITTEST

bool gmCircle::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("gmCircle");

   gmCircle rt(gpPoint2d(2,2),2);
   TRY_TESTME( IsEqual(2., rt.GetRadius())) 
   TRY_TESTME(gpPoint2d(2,2) == rt.GetHookPoint()) 
   gmProperties aprops;
   rt.GetProperties(&aprops);
   TRY_TESTME (IsEqual(aprops.Area(), 12.566, .01)) 
   TRY_TESTME (IsEqual(aprops.Ixx(),  12.56, .1)) 
   TRY_TESTME (IsEqual(aprops.Iyy(),  12.56, .1)) 
   TRY_TESTME (IsEqual(aprops.Ixy(),   0.00, .001)) 
   TRY_TESTME (rt.GetBoundingBox() == gpRect2d(0,0,4,4)) 

   rt.SetHookPoint(gpPoint2d(0,0));
   TRY_TESTME (rt.GetBoundingBox() == gpRect2d(-2,-2,2,2)) 
   rt.Move(gmIShape::CenterCenter, gpPoint2d(2,2));
   TRY_TESTME (rt.GetBoundingBox() == gpRect2d(0,0,4,4)) 

   Float64 ang = atan(1.);
   Float64 dis = 2/cos(ang);
   rt.Rotate(gpPoint2d(0,0),ang);
   TRY_TESTME (rt.GetBoundingBox() == gpRect2d(-2,dis-2,2,dis+2)) 

   // Resize circle and clip it into a hemi
   rt.SetRadius(40);
   rt.SetHookPoint(gpPoint2d(0,40));
   gpLine2d at45(gpPoint2d(0,40), gpVector2d(gpSize2d(1,1)));
   std::unique_ptr<gmIShape> phemi(rt.CreateClippedShape(at45, gpLine2d::Right));
   phemi->GetProperties(&aprops);
   TRY_TESTME (IsEqual(aprops.Area(), 2513.2,.1)) 

   // clip should return entire circle
   rt.SetHookPoint(gpPoint2d(60,0));
   std::unique_ptr<gmIShape> prt(rt.CreateClippedShape(at45, gpLine2d::Left));
   prt->GetProperties(&aprops);
   TRY_TESTME (IsEqual(aprops.Area(), 5026.55,.1)) 

#if defined _DEBUG
   rt.Dump(rlog.GetDumpCtx());
#endif

   TESTME_EPILOG("gmCircle");
}

#endif // _UNITTEST



