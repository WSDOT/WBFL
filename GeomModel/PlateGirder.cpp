///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
// Copyright © 1999-2022  Washington State Department of Transportation
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
#include <GeomModel/PlateGirder.h>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace WBFL::Geometry;

PlateGirder::PlateGirder() :ShapeOnPolygonImpl()
{
}

PlateGirder::PlateGirder(std::shared_ptr<Point2d>& hookPnt, Float64 tfw, Float64 tft, Float64 bfw, Float64 bft, Float64 hWeb, Float64 wWeb, Float64 rotAngle) :
   ShapeOnPolygonImpl(hookPnt), m_tfWidth(tfw), m_tfThickness(tft), m_bfWidth(bfw), m_bfThickness(bft), m_webHeight(hWeb), m_webWidth(wWeb), m_Rotation(rotAngle)
{
}

PlateGirder::PlateGirder(const Point2d& hookPnt, Float64 tfw, Float64 tft, Float64 bfw, Float64 bft, Float64 hWeb, Float64 wWeb, Float64 rotAngle) :
   ShapeOnPolygonImpl(hookPnt), m_tfWidth(tfw), m_tfThickness(tft), m_bfWidth(bfw), m_bfThickness(bft), m_webHeight(hWeb), m_webWidth(wWeb), m_Rotation(rotAngle)
{
}

PlateGirder::~PlateGirder()
{
}

void PlateGirder::SetTopFlangeWidth(Float64 wtf)
{
   m_tfWidth = wtf;
   SetDirtyFlag();
}

Float64 PlateGirder::GetTopFlangeWidth() const
{
   return m_tfWidth;
}

void PlateGirder::SetTopFlangeThickness(Float64 ttf)
{
   m_tfThickness = ttf;
   SetDirtyFlag();
}

Float64 PlateGirder::GetTopFlangeThickness() const
{
   return m_tfThickness;
}

void PlateGirder::SetBottomFlangeWidth(Float64 wbf)
{
   m_bfWidth = wbf;
   SetDirtyFlag();
}

Float64 PlateGirder::GetBottomFlangeWidth() const
{
   return m_bfWidth;
}

void PlateGirder::SetBottomFlangeThickness(Float64 tbf)
{
   m_bfThickness = tbf;
   SetDirtyFlag();
}

Float64 PlateGirder::GetBottomFlangeThickness() const
{
   return m_bfThickness;
}

void PlateGirder::SetWebHeight(Float64 tWeb)
{
   m_webHeight = tWeb;
   SetDirtyFlag();
}

Float64 PlateGirder::GetWebHeight() const
{
   return m_webHeight;
}

void PlateGirder::SetWebWidth(Float64 wWeb)
{
   m_webWidth = wWeb;
   SetDirtyFlag();
}

Float64 PlateGirder::GetWebWidth() const
{
   return m_webWidth;
}

Float64 PlateGirder::GetHeight() const
{
   return m_bfThickness + m_webHeight + m_tfThickness;
}

Float64 PlateGirder::GetQTopFlange() const
{
   Float64 Aflange = m_tfWidth * m_tfThickness;
   Float64 cgFlange = m_bfThickness + m_webHeight + m_tfThickness / 2;

   Float64 Ybot = GetProperties().GetYbottom();

   Float64 Q = Aflange * (cgFlange - Ybot);

   return Q;
}

Float64 PlateGirder::GetQBottomFlange() const
{
   Float64 Aflange = m_bfWidth * m_bfThickness;
   Float64 cgFlange = m_bfThickness / 2;


   Float64 Ybot = GetProperties().GetYbottom();

   Float64 Q = Aflange * (Ybot - cgFlange);

   return Q;
}

////////////////////////////////////////////////
void PlateGirder::DoOffset(const Size2d& delta)
{
   GetHookPoint()->Offset(delta);
   SetDirtyFlag();
}

void PlateGirder::DoRotate(const Point2d& center, Float64 angle)
{
   m_Rotation += angle;
   GetHookPoint()->Rotate(center, angle);
   SetDirtyFlag();
}

std::unique_ptr<Shape> PlateGirder::CreateClone() const
{
   return std::make_unique<PlateGirder>(*this);
}

#if defined _DEBUG
bool PlateGirder::AssertValid() const
{
   return __super::AssertValid();
}

void PlateGirder::Dump(dbgDumpContext& os) const
{
   os << _T("*** Dump for PlateGirder ***")<<endl;
   __super::Dump(os);
}
#endif // _DEBUG

void PlateGirder::OnUpdatePolygon(std::unique_ptr<Polygon>& polygon) const
{
   // start at bottom center and go around counter-clockwise
   // there are 13 points total. point 1 is bottom left, point 6 is the
   // top left corner.
   Float64 p1_x = -m_bfWidth / 2;
   Float64 p1_y = 0.;
   Float64 p2_x = -m_bfWidth / 2;
   Float64 p2_y = m_bfThickness;
   Float64 p3_x = -m_webWidth / 2;
   Float64 p3_y = m_bfThickness;
   Float64 p4_x = -m_webWidth / 2;
   Float64 p4_y = m_bfThickness + m_webHeight;
   Float64 p5_x = -m_tfWidth / 2;
   Float64 p5_y = m_bfThickness + m_webHeight;
   Float64 p6_x = -m_tfWidth / 2;
   Float64 p6_y = m_bfThickness + m_webHeight + m_tfThickness;

   polygon->AddPoint(p1_x, p1_y); // 1
   polygon->AddPoint(p2_x, p2_y);
   polygon->AddPoint(p3_x, p3_y);
   polygon->AddPoint(p4_x, p4_y);
   polygon->AddPoint(p5_x, p5_y);
   polygon->AddPoint(p6_x, p6_y);  // 6
   polygon->AddPoint(-p6_x, p6_y);
   polygon->AddPoint(-p5_x, p5_y);
   polygon->AddPoint(-p4_x, p4_y);
   polygon->AddPoint(-p3_x, p3_y);
   polygon->AddPoint(-p2_x, p2_y);
   polygon->AddPoint(-p1_x, p1_y); // 13 = 1

   // rotate if needed
   if (m_Rotation != 0.)
      polygon->Rotate(*GetHookPoint(), m_Rotation);

   polygon->Move(Point2d(0, 0), *GetHookPoint());
}

#if defined _UNITTEST
#include <GeomModel/UnitTest.h>
bool PlateGirder::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("PlateGirder");

//   Triangle rt(Point2d(1,2),4,2,1);
//   TRY_TESTME( IsEqual(2., rt.GetWidth())) ;
//   TRY_TESTME( IsEqual(4., rt.GetHeight())) ;
//   TRY_TESTME( IsEqual(1., rt.GetOffset())) ;
//   TRY_TESTME( Point2d(1,2) == rt.GetHookPoint()); 
//   ShapeProperties aprops = rt.GetProperties();
//   TRY_TESTME ( IsEqual(aprops.GetArea(), 4.)) ;
//   TRY_TESTME ( IsEqual(aprops.GetIxx(),   3.55, .1)) ;
//   TRY_TESTME ( IsEqual(aprops.GetIyy(),   0.67, .1)) ;
//   TRY_TESTME ( IsEqual(aprops.GetIxy(),   0.00, .001)) ;
//   TRY_TESTME (rt.GetBoundingBox() == Rect2d(1,2,3,6)) ;
//
//   rt.SetHookPoint(Point2d(0,0));
//   TRY_TESTME (rt.GetBoundingBox() == Rect2d(0,0,2,4)) ;
//   rt.Move(Shape::LocatorPoint::CenterCenter, Point2d(0,0));
//   TRY_TESTME (rt.GetBoundingBox() == Rect2d(-1,-2,1,2)) ;
//
//   Float64 ang = atan(.25);
//   Float64 cosa = cos(ang);
//   rt.SetHookPoint(Point2d(0,0));
//   rt.Rotate(Point2d(0,0),ang);
//   TRY_TESTME (rt.GetBoundingBox() == Rect2d(0,0,2*cosa,4/cosa)) ;
//   rt.SetRotationAngle(0);
//   TRY_TESTME (rt.GetBoundingBox() == Rect2d(0,0,2,4)) ;
//
//#if defined _DEBUG
//   rt.Dump(rlog.GetDumpCtx());
//#endif

   // Test hook point behavior
   //TRY_TESTME(UnitTest::TestHookPoint(beam) == true);


   TESTME_EPILOG("PlateGirder");
}
#endif // _UNITTEST



