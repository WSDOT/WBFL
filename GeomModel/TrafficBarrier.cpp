///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
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

#include <GeomModel/GeomModelLib.h>
#include <GeomModel/TrafficBarrier.h>
#include <GeomModel/ShapeProperties.h>
#include <GeomModel/Polygon.h>
#include <MathEx.h>
#include <memory>

using namespace WBFL::Geometry;

TrafficBarrier::TrafficBarrier() :
ShapeOnPolygonImpl()
{
}

TrafficBarrier::TrafficBarrier(Float64 x1,Float64 x2,Float64 x3,Float64 x4,Float64 x5,
                                   Float64 y1,Float64 y2,Float64 y3,
                                   Float64 tSlab,
                                   Orientation orient,
   std::shared_ptr<Point2d>& hookPoint) :
ShapeOnPolygonImpl(hookPoint),
m_X1(x1),
m_X2(x2),
m_X3(x3),
m_X4(x4),
m_X5(x5),
m_Y1(y1),
m_Y2(y2),
m_Y3(y3),
m_tSlab(tSlab),
m_Orientation(orient)
{
}

TrafficBarrier::~TrafficBarrier()
{
}

void TrafficBarrier::SetX1(Float64 x1)
{
   m_X1 = x1;
   SetDirtyFlag();
}

Float64 TrafficBarrier::GetX1() const
{
   return m_X1;
}

void TrafficBarrier::SetX2(Float64 x2)
{
   m_X2 = x2;
   SetDirtyFlag();
}

Float64 TrafficBarrier::GetX2() const
{
   return m_X2;
}

void TrafficBarrier::SetX3(Float64 x3)
{
   m_X3 = x3;
   SetDirtyFlag();
}

Float64 TrafficBarrier::GetX3() const
{
   return m_X3;
}

void TrafficBarrier::SetX4(Float64 x4)
{
   m_X4 = x4;
   SetDirtyFlag();
}

Float64 TrafficBarrier::GetX4() const
{
   return m_X4;
}

void TrafficBarrier::SetX5(Float64 x5)
{
   m_X5 = x5;
   SetDirtyFlag();
}

Float64 TrafficBarrier::GetX5() const
{
   return m_X5;
}

void TrafficBarrier::SetY1(Float64 y1)
{
   m_Y1 = y1;
   SetDirtyFlag();
}

Float64 TrafficBarrier::GetY1() const
{
   return m_Y1;
}

void TrafficBarrier::SetY2(Float64 y2)
{
   m_Y2 = y2;
   SetDirtyFlag();
}

Float64 TrafficBarrier::GetY2() const
{
   return m_Y2;
}

void TrafficBarrier::SetY3(Float64 y3)
{
   m_Y3 = y3;
}

Float64 TrafficBarrier::GetY3() const
{
   return m_Y3;
}

void TrafficBarrier::SetSlabDepth(Float64 tSlab)
{
   m_tSlab = tSlab;
   SetDirtyFlag();
}

Float64 TrafficBarrier::GetSlabDepth() const
{
   return m_tSlab;
}

void TrafficBarrier::SetOrientation(TrafficBarrier::Orientation orient)
{
   m_Orientation = orient;
   SetDirtyFlag();
}

TrafficBarrier::Orientation TrafficBarrier::GetOrientation() const
{
   return m_Orientation;
}

void TrafficBarrier::DoOffset(const Size2d& delta)
{
   GetHookPoint()->Offset(delta);
   SetDirtyFlag();
}

void TrafficBarrier::DoRotate(const Point2d& center, Float64 angle)
{
   m_Rotation += angle;
   GetHookPoint()->Rotate(center, angle);
   SetDirtyFlag();
}

ShapeProperties TrafficBarrier::GetProperties() const
{
   return GetPolygon()->GetProperties();
}

Rect2d TrafficBarrier::GetBoundingBox() const
{
   return GetPolygon()->GetBoundingBox();
}

std::unique_ptr<Shape> TrafficBarrier::CreateClone() const
{
   return std::make_unique<TrafficBarrier>(*this);
}

std::unique_ptr<Shape> TrafficBarrier::CreateClippedShape(const Line2d& line,Line2d::Side side) const
{
   return GetPolygon()->CreateClippedShape(line, side);
}

std::unique_ptr<Shape> TrafficBarrier::CreateClippedShape(const Rect2d& r, Shape::ClipRegion region) const
{
   return GetPolygon()->CreateClippedShape(r, region);
}

Float64 TrafficBarrier::GetFurthestDistance(const Line2d& line,Line2d::Side side) const
{
   return GetPolygon()->GetFurthestDistance(line, side);
}

void TrafficBarrier::OnUpdatePolygon(std::unique_ptr<Polygon>& polygon) const
{
   Float64 sign = (m_Orientation == Orientation::Left ? 1 : -1);

   // Hook Point (make it 0,0 for ease of construction)
   Point2d p0(0,0);

   // Work clockwise around the left oriented shape.
   Point2d p1( sign*(p0.X() + m_X2), p0.Y() );
   Point2d p2( sign*(p0.X() + m_X2), p0.Y() + m_Y1 );
   Point2d p3( sign*(p0.X() + m_X2 - m_X5), p0.Y() + m_Y1 + m_Y2 );
   Point2d p4( sign*(p0.X() + m_X2 - m_X5 - m_X4), p0.Y() + m_Y3 );
   Point2d p5( sign*(p0.X() + m_X2 - m_X5 - m_X4 - m_X3), p0.Y() + m_Y3 );
   Point2d p6( sign*(p0.X() - m_X1), p0.Y() - m_tSlab );
   Point2d p7( p0.X() , p0.Y() - m_tSlab );
   
   polygon->AddPoint(p0);
   polygon->AddPoint(p1);
   polygon->AddPoint(p2);
   polygon->AddPoint(p3);
   polygon->AddPoint(p4);
   polygon->AddPoint(p5);
   polygon->AddPoint(p6);
   polygon->AddPoint(p7);

   if (!IsZero(m_Rotation))
      polygon->Rotate(*GetHookPoint(), m_Rotation);

   polygon->Move(Point2d(0, 0), *GetHookPoint());
}

#if defined _DEBUG
bool TrafficBarrier::AssertValid() const
{
   return ShapeImpl::AssertValid();
}

void TrafficBarrier::Dump(WBFL::Debug::LogContext& os) const
{
   ShapeImpl::Dump( os );
}
#endif // _DEBUG

#if defined _UNITTEST
#include <GeomModel/UnitTest.h>
bool TrafficBarrier::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("TrafficBarrier");

   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for TrafficBarrier");

   // Test hook point behavior
   //TRY_TESTME(UnitTest::TestHookPoint(anglep) == true);

   TESTME_EPILOG("TrafficBarrier");
}
#endif // _UNITTEST
