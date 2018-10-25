///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
// Copyright © 1999-2017  Washington State Department of Transportation
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
#include <GeomModel\TrafficBarrier.h>
#include <GeomModel\Properties.h>
#include <GeomModel\ShapeUtils.h>
#include <GeomModel\Polygon.h>
#include <MathEx.h>
#include <memory>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   gmTrafficBarrier
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
gmTrafficBarrier::gmTrafficBarrier() :
gmShapeImp()
{
   Init();
}

gmTrafficBarrier::gmTrafficBarrier(Float64 x1,Float64 x2,Float64 x3,Float64 x4,Float64 x5,
                                   Float64 y1,Float64 y2,Float64 y3,
                                   Float64 tSlab,
                                   Orientation orient,
                                   const gpPoint2d& hookPoint) :
gmShapeImp()
{
   Init();

   m_X1 = x1;
   m_X2 = x2;
   m_X3 = x3;
   m_X4 = x4;
   m_X5 = x5;
   m_Y1 = y1;
   m_Y2 = y2;
   m_Y3 = y3;
   m_tSlab = tSlab;
   m_Orientation = orient;
   m_HookPoint = hookPoint;

   UpdatePolygon();
}

gmTrafficBarrier::gmTrafficBarrier(const gmTrafficBarrier& rOther) :
gmShapeImp(rOther)
{
   MakeCopy(rOther);
}

gmTrafficBarrier::~gmTrafficBarrier()
{
}

//======================== OPERATORS  =======================================
gmTrafficBarrier& gmTrafficBarrier::operator= (const gmTrafficBarrier& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================
void gmTrafficBarrier::GetProperties(gmProperties* pProperties) const
{
   ASSERTVALID;

   Float64 area, ixx, iyy, ixy, perimeter;
   gpPoint2d  cg;
   m_PolyImp.GetProperties(&area, &ixx, &iyy, &ixy, &cg);
   perimeter = m_PolyImp.Perimeter();

   // deal with signs and hollowness
   if( (area>0 && !IsSolid() || (area<0 && IsSolid())))
   {
      area *= -1;
      ixx  *= -1;
      iyy  *= -1;
      ixy  *= -1;
   }

   // bounding box in centroidal coords
   gpRect2d bb = m_PolyImp.GetBoundingBox();
   bb.Offset(-cg.X(), -cg.Y());

   *pProperties =  gmProperties(area , cg, ixx, iyy, ixy, 
                                bb.Top(),bb.Bottom(),bb.Left(),bb.Right(),
                                perimeter);
}

gpRect2d gmTrafficBarrier::GetBoundingBox() const
{
   return m_PolyImp.GetBoundingBox();
}

gmIShape* gmTrafficBarrier::CreateClone(bool bRegisterListeners) const
{
   std::unique_ptr<gmTrafficBarrier> ph(new gmTrafficBarrier( *this ));// no memory leaks if DoRegister() throws

   // copy listeners if requested.
   if (bRegisterListeners)
      ph->DoRegisterListeners(*this);

   return ph.release();
}

gmIShape* gmTrafficBarrier::CreateClippedShape(const gpLine2d& line,
                                               gpLine2d::Side side) const
{
   // make shape into a gmpolygon and use its clip
   std::unique_ptr<gmPolygon> poly(CreatePolygon());
   return poly->CreateClippedShape(line,side);
}

gmIShape* gmTrafficBarrier::CreateClippedShape(const gpRect2d& r,
                                               gmShapeImp::ClipRegion region ) const
{
   // make shape into a gmpolygon and use its clip
   std::unique_ptr<gmPolygon> poly(CreatePolygon());
   return poly->CreateClippedShape(r, region);
}

Float64 gmTrafficBarrier::GetFurthestDistance(const gpLine2d& line,
                                              gpLine2d::Side side) const
{
   // make shape into a gmpolygon and use its clip
   std::unique_ptr<gmPolygon> poly(CreatePolygon());
   return poly->GetFurthestDistance(line,side);
}

void gmTrafficBarrier::Draw(HDC hDC,const grlibPointMapper& mapper) const
{
   std::unique_ptr<gmPolygon> poly(CreatePolygon());
   poly->Draw(hDC,mapper);
}

//======================== ACCESS     =======================================
Float64 gmTrafficBarrier::SetX1(Float64 x1)
{
   Float64 tmp = m_X1;
   m_X1 = x1;
   UpdatePolygon();
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   return tmp;
}

Float64 gmTrafficBarrier::GetX1() const
{
   return m_X1;
}

Float64 gmTrafficBarrier::SetX2(Float64 x2)
{
   Float64 tmp = m_X2;
   m_X2 = x2;
   UpdatePolygon();
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   return tmp;
}

Float64 gmTrafficBarrier::GetX2() const
{
   return m_X2;
}

Float64 gmTrafficBarrier::SetX3(Float64 x3)
{
   Float64 tmp = m_X3;
   m_X3 = x3;
   UpdatePolygon();
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   return tmp;
}

Float64 gmTrafficBarrier::GetX3() const
{
   return m_X3;
}

Float64 gmTrafficBarrier::SetX4(Float64 x4)
{
   Float64 tmp = m_X4;
   m_X4 = x4;
   UpdatePolygon();
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   return tmp;
}

Float64 gmTrafficBarrier::GetX4() const
{
   return m_X4;
}

Float64 gmTrafficBarrier::SetX5(Float64 x5)
{
   Float64 tmp = m_X5;
   m_X5 = x5;
   UpdatePolygon();
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   return tmp;
}

Float64 gmTrafficBarrier::GetX5() const
{
   return m_X5;
}

Float64 gmTrafficBarrier::SetY1(Float64 y1)
{
   Float64 tmp = m_Y1;
   m_Y1 = y1;
   UpdatePolygon();
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   return tmp;
}

Float64 gmTrafficBarrier::GetY1() const
{
   return m_Y1;
}

Float64 gmTrafficBarrier::SetY2(Float64 y2)
{
   Float64 tmp = m_Y2;
   m_Y2 = y2;
   UpdatePolygon();
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   return tmp;
}

Float64 gmTrafficBarrier::GetY2() const
{
   return m_Y2;
}

Float64 gmTrafficBarrier::SetY3(Float64 y3)
{
   Float64 tmp = m_Y3;
   m_Y2 = y3;
   UpdatePolygon();
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   return tmp;
}

Float64 gmTrafficBarrier::GetY3() const
{
   return m_Y3;
}

Float64 gmTrafficBarrier::SetSlabDepth(Float64 tSlab)
{
   Float64 tmp = m_tSlab;
   m_tSlab = tSlab;
   UpdatePolygon();
   NotifyAllListeners(gmShapeListener::PROPERTIES);
   return tmp;
}

Float64 gmTrafficBarrier::GetSlabDepth() const
{
   return m_tSlab;
}

gmTrafficBarrier::Orientation gmTrafficBarrier::SetOrientation(gmTrafficBarrier::Orientation orient)
{
   Orientation tmp = m_Orientation;
   if ( m_Orientation != orient )
   {
      m_Orientation = orient;
      UpdatePolygon();
      NotifyAllListeners(gmShapeListener::PROPERTIES);
   }
   return tmp;
}

gmTrafficBarrier::Orientation gmTrafficBarrier::GetOrientation() const
{
   return m_Orientation;
}

gpPoint2d gmTrafficBarrier::SetHookPoint(const gpPoint2d& hookPnt)
{
   gpPoint2d tmp = m_HookPoint;
   if ( m_HookPoint != hookPnt )
   {
      tmp = hookPnt;
      UpdatePolygon();
      NotifyAllListeners(gmShapeListener::PROPERTIES);
   }
   return tmp;
}

gpPoint2d gmTrafficBarrier::GetHookPoint() const
{
   return m_HookPoint;
}

//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void gmTrafficBarrier::DoTranslate(const gpSize2d& delta)
{
   m_HookPoint.Offset(delta);
   UpdatePolygon();
}

void gmTrafficBarrier::DoRotate(const gpPoint2d& center,Float64 angle)
{
   m_Rotation += angle;
   m_HookPoint.Rotate(center, angle);
   UpdatePolygon();
}

void gmTrafficBarrier::MakeCopy(const gmTrafficBarrier& rOther)
{
   // Add copy code here...
   m_X1 = rOther.m_X1;
   m_X2 = rOther.m_X2;
   m_X3 = rOther.m_X3;
   m_X4 = rOther.m_X4;
   m_X5 = rOther.m_X5;
   m_Y1 = rOther.m_Y1;
   m_Y2 = rOther.m_Y2;
   m_Y3 = rOther.m_Y3;
   m_tSlab = rOther.m_tSlab;
   m_Orientation = rOther.m_Orientation;
   m_Rotation = rOther.m_Rotation;
   m_HookPoint = rOther.m_HookPoint;
   m_PolyImp   = rOther.m_PolyImp;
}

void gmTrafficBarrier::MakeAssignment(const gmTrafficBarrier& rOther)
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
void gmTrafficBarrier::Init()
{
   m_HookPoint = gpPoint2d(0,0);
   m_Rotation = 0;
   m_X1 = 0;
   m_X2 = 0;
   m_X3 = 0;
   m_X4 = 0;
   m_X5 = 0;
   m_Y1 = 0;
   m_Y2 = 0;
   m_Y3 = 0;
   m_tSlab = 0;
   m_PolyImp.Clear();
}

gmPolygon* gmTrafficBarrier::CreatePolygon() const
{
   // Make a polygon with same traits as this.
   std::unique_ptr<gmPolygon> ph(new gmPolygon(m_PolyImp));
   gmShapeUtils::CopyTraits(*this, ph.get());
   return ph.release();
}

void gmTrafficBarrier::UpdatePolygon()
{
   // clear the polygon implemenation and recalculate all of the points
   m_PolyImp.Clear();

   Float64 sign = (m_Orientation == Left ? 1 : -1);

   // Hook Point (make it 0,0 for ease of construction)
   gpPoint2d p0(0,0);

   // Work clockwise around the left oriented shape.
   gpPoint2d p1( sign*(p0.X() + m_X2), p0.Y() );
   gpPoint2d p2( sign*(p0.X() + m_X2), p0.Y() + m_Y1 );
   gpPoint2d p3( sign*(p0.X() + m_X2 - m_X5), p0.Y() + m_Y1 + m_Y2 );
   gpPoint2d p4( sign*(p0.X() + m_X2 - m_X5 - m_X4), p0.Y() + m_Y3 );
   gpPoint2d p5( sign*(p0.X() + m_X2 - m_X5 - m_X4 - m_X3), p0.Y() + m_Y3 );
   gpPoint2d p6( sign*(p0.X() - m_X1), p0.Y() - m_tSlab );
   gpPoint2d p7( p0.X() , p0.Y() - m_tSlab );
   
   m_PolyImp.AddPoint(p0);
   m_PolyImp.AddPoint(p1);
   m_PolyImp.AddPoint(p2);
   m_PolyImp.AddPoint(p3);
   m_PolyImp.AddPoint(p4);
   m_PolyImp.AddPoint(p5);
   m_PolyImp.AddPoint(p6);
   m_PolyImp.AddPoint(p7);

   if (!IsZero(m_Rotation))
      m_PolyImp.Rotate(gpPoint2d(0,0), m_Rotation);

   if ( m_HookPoint != gpPoint2d(0,0) )
      m_PolyImp.Offset(m_HookPoint);
}

//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

//======================== DEBUG      =======================================
#if defined _DEBUG
bool gmTrafficBarrier::AssertValid() const
{
   return gmShapeImp::AssertValid();
}

void gmTrafficBarrier::Dump(dbgDumpContext& os) const
{
   gmShapeImp::Dump( os );
}
#endif // _DEBUG

#if defined _UNITTEST
bool gmTrafficBarrier::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("gmTrafficBarrier");

   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for gmTrafficBarrier");

   TESTME_EPILOG("TrafficBarrier");
}
#endif // _UNITTEST
