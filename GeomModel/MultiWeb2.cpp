///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
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

#include <GeomModel/GeomModelLib.h>
#include <GeomModel/MultiWeb2.h>
#include <GeomModel/ShapeProperties.h>
#include <GeomModel/Polygon.h>
#include <GeomModel/GeomOp2d.h>
#include <MathEx.h>

using namespace WBFL::Geometry;

MultiWeb2::MultiWeb2() :
   ShapeOnPolygonImpl()
{
}

MultiWeb2::MultiWeb2(Float64 h1, Float64 h2, Float64 h3, Float64 w1, Float64 w2, Float64 t1, Float64 t2, Float64 t3, Float64 t4, Float64 t5, Float64 f1, Float64 f2, Float64 c1, Float64 c2, IndexType nWebs, bool bLeftBlockOut, bool bRightBlockOut, std::shared_ptr<Point2d>& hookPnt) :
ShapeOnPolygonImpl(hookPnt), m_H1(h1), m_H2(h2), m_H3(h3), m_W1(w1),m_W2(w2),m_T1(t1), m_T2(t2), m_T3(t3), m_T4(t4), m_T5(t5),m_F1(f1),m_F2(f2),m_C1(c1),m_C2(c2),m_WebCount(nWebs),m_bLeftBlockout(bLeftBlockOut),m_bRightBlockout(bRightBlockOut)
{
}

MultiWeb2::~MultiWeb2()
{
}

void MultiWeb2::SetH1(Float64 h1)
{
   m_H1 = h1;
   SetDirtyFlag();
}

Float64 MultiWeb2::GetH1() const
{
   return m_H1;
}

void MultiWeb2::SetH2(Float64 h2)
{
   m_H2 = h2;
   SetDirtyFlag();
}

Float64 MultiWeb2::GetH2() const
{
   return m_H2;
}

void MultiWeb2::SetH3(Float64 h3)
{
   m_H3 = h3;
   SetDirtyFlag();
}

Float64 MultiWeb2::GetH3() const
{
   return m_H3;
}

void MultiWeb2::SetW1(Float64 w1)
{
   m_W1 = w1;
   SetDirtyFlag();
}

Float64 MultiWeb2::GetW1() const
{
   return m_W1;
}

void MultiWeb2::SetW2(Float64 w2)
{
   m_W2 = w2;
   SetDirtyFlag();
}

Float64 MultiWeb2::GetW2() const
{
   return m_W2;
}

void MultiWeb2::SetT1(Float64 t1)
{
   m_T1 = t1;
   SetDirtyFlag();
}

Float64 MultiWeb2::GetT1() const
{
   return m_T1;
}

void MultiWeb2::SetT2(Float64 t2)
{
   m_T2 = t2;
   SetDirtyFlag();
}

Float64 MultiWeb2::GetT2() const
{
   return m_T2;
}

void MultiWeb2::SetT3(Float64 t3)
{
   m_T3 = t3;
   SetDirtyFlag();
}

Float64 MultiWeb2::GetT3() const
{
   return m_T3;
}

void MultiWeb2::SetT4(Float64 t4)
{
   m_T4 = t4;
   SetDirtyFlag();
}

Float64 MultiWeb2::GetT4() const
{
   return m_T4;
}

void MultiWeb2::SetT5(Float64 t5)
{
   m_T5 = t5;
   SetDirtyFlag();
}

Float64 MultiWeb2::GetT5() const
{
   return m_T5;
}

void MultiWeb2::SetF1(Float64 f1)
{
   m_F1 = f1;
   SetDirtyFlag();
}

Float64 MultiWeb2::GetF1() const
{
   return m_F1;
}

void MultiWeb2::SetF2(Float64 f2)
{
   m_F2 = f2;
   SetDirtyFlag();
}

Float64 MultiWeb2::GetF2() const
{
   return m_F2;
}

void MultiWeb2::SetC1(Float64 c1)
{
   m_C1 = c1;
   SetDirtyFlag();
}

Float64 MultiWeb2::GetC1() const
{
   return m_C1;
}

void MultiWeb2::SetC2(Float64 c2)
{
   m_C2 = c2;
   SetDirtyFlag();
}

Float64 MultiWeb2::GetC2() const
{
   return m_C2;
}

void MultiWeb2::SetWebCount(WebIndexType nWebs)
{
   // minimum of 2 webs required
   if (nWebs < 2) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDARG);

   m_WebCount = nWebs;
   SetDirtyFlag();
}

WebIndexType MultiWeb2::GetWebCount() const
{
   return m_WebCount;
}

void MultiWeb2::SetLeftBlockout(bool bBlockout)
{
   m_bLeftBlockout = bBlockout;
   SetDirtyFlag();
}

bool MultiWeb2::GetLeftBlockout() const
{
   return m_bLeftBlockout;
}

void MultiWeb2::SetRightBlockout(bool bBlockout)
{
   m_bRightBlockout = bBlockout;
   SetDirtyFlag();
}

bool MultiWeb2::GetRightBlockout() const
{
   return m_bRightBlockout;
}

Float64 MultiWeb2::GetWebLocation(WebIndexType webIdx)
{
   if (m_WebCount <= webIdx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);

   Float64 W = GetTopFlangeWidth();

   WebIndexType nInteriorWebs;
   if (m_WebCount < 3)
   {
      nInteriorWebs = 0;
   }
   else
   {
      nInteriorWebs = m_WebCount - 2;
   }

   WebIndexType nExteriorWebs = m_WebCount - nInteriorWebs;

   Float64 location;
   if (webIdx == 0)
   {
      // first web
      location = m_W1 + m_T1 + m_T2 / 2 - W / 2;
   }
   else if (webIdx == m_WebCount - 1)
   {
      // last web
      location = W / 2 - (m_W1 + m_T1 + m_T2 / 2);
   }
   else
   {
      // interior web
      location = m_W1 + m_T1 + m_T2 + m_T3 + (webIdx - 1) * (m_W2 + m_T4 + m_T5 + m_T4) + m_W2 + m_T4 + m_T5 / 2 - W / 2;
   }

   return location;
}

Float64 MultiWeb2::GetTopFlangeWidth() const
{
   // WebIndexType is unsigned so we can't just do m_WebCount - 2 and check for less than zero because
   // the integer will rollover
   WebIndexType nInteriorWebs = (1 < m_WebCount) ? m_WebCount - 2 : 0;
   WebIndexType nExteriorWebs = m_WebCount - nInteriorWebs;

   return 2 * m_W1 + nExteriorWebs * (m_T1 + m_T2 + m_T3) + nInteriorWebs * (m_T4 + m_T5 + m_T4) + m_W2 * (nInteriorWebs + 1);
}

Float64 MultiWeb2::GetAvgWebWidth(WebIndexType webIdx) const
{
   if (m_WebCount <= webIdx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);

   if (webIdx == 0 || webIdx == m_WebCount - 1)
   {
      return (m_T1 + m_T2 + m_T3 + m_T2) / 2;
   }
   else
   {
      return (2 * m_T4 + m_T5 + m_T5) / 2;
   }
}

Float64 MultiWeb2::GetHeight() const
{
   return m_H1 + m_H2 + m_H3;
}

void MultiWeb2::DoOffset(const Size2d& delta)
{
   GetHookPoint()->Offset(delta);
   SetDirtyFlag();
}

void MultiWeb2::DoRotate(const Point2d& center, Float64 angle)
{
   m_Rotation += angle;
   GetHookPoint()->Rotate(center, angle);
   SetDirtyFlag();
}

std::unique_ptr<Shape> MultiWeb2::CreateClone() const
{
   return std::make_unique<MultiWeb2>(*this);
}

void MultiWeb2::OnUpdatePolygon(std::unique_ptr<Polygon>& polygon) const
{
   Float64 W = GetTopFlangeWidth();

   Float64 H = m_H1 + m_H2 + m_H3;

   // start at top left and go around clockwise

   // top left
   Float64 p1_x = m_bLeftBlockout ? m_C2 : 0.0;
   Float64 p1_y = 0.;
   polygon->AddPoint(p1_x, p1_y);

   // top right
   Float64 p2_x = m_bRightBlockout ? W - m_C2 : W;
   Float64 p2_y = 0;
   polygon->AddPoint(p2_x, p2_y);

   // top right, bottom of top flange
   Float64 p3_x = W;
   Float64 p3_y = -m_H3;
   polygon->AddPoint(p3_x, p3_y);

   // corner at outside of right outside web, top of fillet
   Float64 p4_x = W - m_W1 + m_F1;
   Float64 p4_y = -(m_H2 + m_H3);
   polygon->AddPoint(p4_x, p4_y);

   // corner at outside of right outside web, bottom of fillet
   Float64 p5_x = W - m_W1;
   Float64 p5_y = -(m_H2 + m_H3 + m_F1);
   polygon->AddPoint(p5_x, p5_y);

   // bottom right corner of right web
   // if no chamfer, computation is simple
   Float64 p6_x = W - m_W1 - m_T1;
   Float64 p6_y = -H;

   if (m_C1 <= 0.0)
   {
      polygon->AddPoint(p6_x, p6_y);
   }
   else
   {
      // must compute chamfer locations along outside of right outside web
      // a is first location b is second
      Point2d p6a = GeometricOperations::PointOnLine(Point2d(p6_x, p6_y), Point2d(p5_x, p5_y), m_C1);
      polygon->AddPoint(p6a);

      Point2d p6b(p6_x-m_C1,p6_y);
      polygon->AddPoint(p6b);
   }

   // bottom left corner of right web - again, chamfer is an issue
   Float64 p7_x = W - m_W1 - m_T1 - m_T2;
   Float64 p7_y = -H;

   // corner at inside of right web, bottom of fillet
   Float64 p8_x = p7_x - m_T3;
   Float64 p8_y = -H + m_H1 - m_F1;

   if (m_C1 <= 0.0)
   {
      polygon->AddPoint(p7_x, p7_y);
   }
   else
   {
      // must compute chamfer locations along inside of right outside web
      // a is first location b is second
      Float64 p7a_x = p7_x + m_C1;
      Float64 p7a_y = p7_y;
      polygon->AddPoint(p7a_x, p7a_y);

      Point2d p7b = GeometricOperations::PointOnLine(Point2d(p7_x, p7_y), Point2d(p8_x, p8_y), m_C1);
      polygon->AddPoint(p7b);
   }

   polygon->AddPoint(p8_x, p8_y);

   // corner at inside of right web, top of fillet
   Float64 p9_x = p8_x - m_F1;
   Float64 p9_y = p8_y + m_F1;
   polygon->AddPoint(p9_x, p9_y);

   // loop over all the interior webs
   Float64 x1 = W - (m_W1 + m_T1 + m_T2 + m_T3 + m_W2 - m_F2);
   Float64 y1 = -H + m_H1;

   for (WebIndexType webIdx = 1; webIdx < m_WebCount - 1; webIdx++)
   {
      polygon->AddPoint(x1, y1);

      // top right corner of web, above fillet
      // work clockwise around the web
      Float64 x2 = x1 - m_F2;
      Float64 y2 = y1 - m_F2;
      polygon->AddPoint(x2, y2);

      // add chamfer at right side of web if needed
      Float64 x3 = x2 - m_T4;
      Float64 y3 = -H;

      if (m_C1 <= 0.0)
      {
         polygon->AddPoint(x3, y3);
      }
      else
      {
         // must compute chamfer locations along right side of inside web
         // a is first location b is second
         Point2d p3a = GeometricOperations::PointOnLine(Point2d(x3, y3), Point2d(x2, y2), m_C1);
         polygon->AddPoint(p3a);

         Float64 x3_b = x3 - m_C1;
         Float64 y3_b = y3;
         polygon->AddPoint(x3_b, y3_b);
      }

      Float64 x4 = x3 - m_T5;
      Float64 y4 = y3;

      Float64 x5 = x4 - m_T4;
      Float64 y5 = y4 + m_H1 - m_F2;

      if (m_C1 <= 0.0)
      {
         polygon->AddPoint(x4, y4);
      }
      else
      {
         // must compute chamfer locations along left side of inside web
         Float64 x4_a = x4 + m_C1;
         Float64 y4_a = y4;
         polygon->AddPoint(x4_a, y4_a);

         Point2d p4b = GeometricOperations::PointOnLine(Point2d(x4, y4), Point2d(x5, y5), m_C1);
         polygon->AddPoint(p4b);
      }

      Float64 x6 = x5 - m_F2;
      Float64 y6 = y5 + m_F2;

      polygon->AddPoint(x5, y5);
      polygon->AddPoint(x6, y6);

      x1 = x6 - (m_W2 - 2 * m_F2);
   }

   // left exterior web

   // inside right corner of left web... top of fillet
   Float64 p10_x = m_W1 + m_T1 + m_T2 + m_T3 + m_F1;
   Float64 p10_y = p9_y;
   polygon->AddPoint(p10_x, p10_y);

   Float64 p11_x = p10_x - m_F1;
   Float64 p11_y = p9_y - m_F1;
   polygon->AddPoint(p11_x, p11_y);

   // right side bottom
   Float64 p12_x = p11_x - m_T3;
   Float64 p12_y = -H;

   if (m_C1 <= 0.0)
   {
      polygon->AddPoint(p12_x, p12_y);
   }
   else
   {
      // must compute chamfer locations along right side of left outside web
      Point2d p12a = GeometricOperations::PointOnLine(Point2d(p12_x, p12_y), Point2d(p11_x, p11_y), m_C1);
      polygon->AddPoint(p12a);

      Float64 p12b_x = p12_x - m_C1;
      Float64 p12b_y = p12_y;
      polygon->AddPoint(p12b_x, p12b_y);
   }

   Float64 p13_x = p12_x - m_T2;
   Float64 p13_y = p12_y;

   Float64 p14_x = p13_x - m_T1;
   Float64 p14_y = p5_y;


   if (m_C1 <= 0.0)
   {
      polygon->AddPoint(p13_x, p13_y);
   }
   else
   {
      // must compute chamfer locations along left side of left outside web
      // a is first location b is second
      Float64 p13a_x = p13_x + m_C1;
      Float64 p13a_y = p13_y;
      polygon->AddPoint(p13a_x, p13a_y);

      Point2d p13b = GeometricOperations::PointOnLine(Point2d(p13_x, p13_y), Point2d(p14_x, p14_y), m_C1);
      polygon->AddPoint(p13b);
   }

   polygon->AddPoint(p14_x, p14_y);

   Float64 p15_x = p14_x - m_F1;
   Float64 p15_y = p14_y + m_F1;

   Float64 p16_x = 0;
   Float64 p16_y = -m_H3;

   polygon->AddPoint(p15_x, p15_y);
   polygon->AddPoint(p16_x, p16_y);

   // close the shape
   polygon->AddPoint(p1_x, p1_y);


   // move the shape so that the bottom center is at (0,0)
   polygon->Offset(Size2d(-W / 2, H));

   if (!IsZero(m_Rotation))
      polygon->Rotate(Point2d(0, 0), m_Rotation);

   polygon->Move(Point2d(0,0),*GetHookPoint());
}
