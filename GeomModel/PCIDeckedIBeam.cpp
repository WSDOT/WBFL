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
// Olympia, WA 98703, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#include <GeomModel/GeomModelLib.h>
#include <GeomModel/PCIDeckedIBeam.h>
#include <GeomModel/ShapeProperties.h>
#include <GeomModel/Polygon.h>
#include <GeomModel/Primitives3d.h>
#include <MathEx.h>
#include "Helpers.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace WBFL::Geometry;

PCIDeckedIBeam::PCIDeckedIBeam() :
   FlangedBeam()
{
}

PCIDeckedIBeam::PCIDeckedIBeam(Float64 w1, Float64 w2, Float64 w3, Float64 w4, Float64 w5, Float64 w6, Float64 h, Float64 d1, Float64 d2, Float64 d3, Float64 d4, Float64 d5, Float64 d6, Float64 d7, Float64 d8, Float64 d9, Float64 t, Float64 r1, Float64 r2, Float64 r3, Float64 c1, std::shared_ptr<Point2d>& hookPnt) :
   FlangedBeam(hookPnt), m_W1(w1),m_W2(w2), m_W3(w3), m_W4(w4),m_W5(w5),m_W6(w6), m_H(h), m_D1(d1), m_D2(d2), m_D3(d3), m_D4(d4), m_D5(d5), m_D6(d6),m_D7(d7),m_D8(d8),m_D9(d9), m_T(t), m_R1(r1), m_R2(r2), m_R3(r3), m_C1(c1)
{
}

PCIDeckedIBeam::~PCIDeckedIBeam()
{
}

void PCIDeckedIBeam::SetW1(Float64 w1)
{
   m_W1 = w1;
   SetDirtyFlag();
}

Float64 PCIDeckedIBeam::GetW1() const
{
   return m_W1;
}

void PCIDeckedIBeam::SetW2(Float64 w2)
{
   m_W2 = w2;
   SetDirtyFlag();
}

Float64 PCIDeckedIBeam::GetW2() const
{
   return m_W2;
}

void PCIDeckedIBeam::SetW3(Float64 w3)
{
   m_W3 = w3;
   SetDirtyFlag();
}

Float64 PCIDeckedIBeam::GetW3() const
{
   return m_W3;
}

void PCIDeckedIBeam::SetW4(Float64 w4)
{
   m_W4 = w4;
   SetDirtyFlag();
}

Float64 PCIDeckedIBeam::GetW4() const
{
   return m_W4;
}

void PCIDeckedIBeam::SetW5(Float64 w5)
{
   m_W5 = w5;
   SetDirtyFlag();
}

Float64 PCIDeckedIBeam::GetW5() const
{
   return m_W5;
}

void PCIDeckedIBeam::SetW6(Float64 w6)
{
   m_W6 = w6;
   SetDirtyFlag();
}

Float64 PCIDeckedIBeam::GetW6() const
{
   return m_W6;
}

void PCIDeckedIBeam::SetH(Float64 h)
{
   m_H = h;
   SetDirtyFlag();
}

Float64 PCIDeckedIBeam::GetH() const
{
   return m_H;
}

void PCIDeckedIBeam::SetD1(Float64 d1)
{
   m_D1 = d1;
   SetDirtyFlag();
}

Float64 PCIDeckedIBeam::GetD1() const
{
   return m_D1;
}

void PCIDeckedIBeam::SetD2(Float64 d2)
{
   m_D2 = d2;
   SetDirtyFlag();
}

Float64 PCIDeckedIBeam::GetD2() const
{
   return m_D2;
}

void PCIDeckedIBeam::SetD3(Float64 d3)
{
   m_D3 = d3;
   SetDirtyFlag();
}

Float64 PCIDeckedIBeam::GetD3() const
{
   return m_D3;
}

void PCIDeckedIBeam::SetD4(Float64 d4)
{
   m_D4 = d4;
   SetDirtyFlag();
}

Float64 PCIDeckedIBeam::GetD4() const
{
   return m_D4;
}

void PCIDeckedIBeam::SetD5(Float64 d5)
{
   m_D5 = d5;
   SetDirtyFlag();
}

Float64 PCIDeckedIBeam::GetD5() const
{
   return m_D5;
}

void PCIDeckedIBeam::SetD6(Float64 d6)
{
   m_D6 = d6;
   SetDirtyFlag();
}

Float64 PCIDeckedIBeam::GetD6() const
{
   return m_D6;
}

void PCIDeckedIBeam::SetD7(Float64 d7)
{
   m_D7 = d7;
   SetDirtyFlag();
}

Float64 PCIDeckedIBeam::GetD7() const
{
   return m_D7;
}

void PCIDeckedIBeam::SetD8(Float64 d8)
{
   m_D8 = d8;
   SetDirtyFlag();
}

Float64 PCIDeckedIBeam::GetD8() const
{
   return m_D8;
}

void PCIDeckedIBeam::SetD9(Float64 d9)
{
   m_D9 = d9;
   SetDirtyFlag();
}

Float64 PCIDeckedIBeam::GetD9() const
{
   return m_D9;
}

void PCIDeckedIBeam::SetT(Float64 t)
{
   m_T = t;
   SetDirtyFlag();
}

Float64 PCIDeckedIBeam::GetT() const
{
   return m_T;
}

void PCIDeckedIBeam::SetR1(Float64 r1)
{
   m_R1 = r1;
   SetDirtyFlag();
}

Float64 PCIDeckedIBeam::GetR1() const
{
   return m_R1;
}

void PCIDeckedIBeam::SetR2(Float64 r2)
{
   m_R2 = r2;
   SetDirtyFlag();
}

Float64 PCIDeckedIBeam::GetR2() const
{
   return m_R2;
}

void PCIDeckedIBeam::SetR3(Float64 r3)
{
   m_R3 = r3;
   SetDirtyFlag();
}

Float64 PCIDeckedIBeam::GetR3() const
{
   return m_R3;
}

void PCIDeckedIBeam::SetC1(Float64 c1)
{
   m_C1 = c1;
   SetDirtyFlag();
}

Float64 PCIDeckedIBeam::GetC1() const
{
   return m_C1;
}

void PCIDeckedIBeam::GetTopFlangePoints(Point2d* pntLeftTop, Point2d* pntLeftBottom, Point2d* pntTopCL, Point2d* pntTopCentral, Point2d* pntRightTop, Point2d* pntRightBottom) const
{
   auto& polygon = GetPolygon();
   *pntLeftBottom = polygon->GetPoint(m_LeftBottomIdx);
   *pntLeftTop = polygon->GetPoint(m_LeftTopIdx);
   *pntRightTop = polygon->GetPoint(m_RightTopIdx);
   *pntRightBottom = polygon->GetPoint(m_RightBottomIdx);

   *pntTopCentral = (*pntLeftTop + *pntRightTop) / 2;
   *pntTopCL = *pntTopCentral;
}

void PCIDeckedIBeam::GetBottomFlangePoints(Point2d* pntLeftTop, Point2d* pntLeftBottom, Point2d* pntRightTop, Point2d* pntRightBottom) const
{
   auto& polygon = GetPolygon();
   IndexType nPoints = polygon->GetCount();
   if (IsZero(m_C1))
   {
      // no chamfer
      *pntRightBottom = polygon->GetPoint(0);
      *pntRightTop = polygon->GetPoint(0);;

      *pntLeftTop = polygon->GetPoint(nPoints-1);
      *pntLeftBottom = polygon->GetPoint(nPoints-1);
   }
   else
   {
      *pntRightBottom = polygon->GetPoint(0);
      *pntRightTop = polygon->GetPoint(1);

      *pntLeftTop = polygon->GetPoint(nPoints-2);
      *pntLeftBottom = polygon->GetPoint(nPoints-1);
   }
}

void PCIDeckedIBeam::GetTopFlangeThickness(Float64* pHl, Float64* pHc, Float64* pHr) const
{
   *pHl = m_D7;
   *pHc = *pHl;
   *pHr = *pHl;
}

Float64 PCIDeckedIBeam::GetHeight() const
{
   return GetH();
}

IndexType PCIDeckedIBeam::GetTopFlangeCount() const
{
   return 1;
}

Float64 PCIDeckedIBeam::GetTopFlangeLocation(IndexType flangeIdx) const
{
   if (0 < flangeIdx) THROW_GEOMETRY(_T("PCIDeckedIBeam::GetTopFlangeLocation - invalid flange index"));
   return 0.0;
}

Float64 PCIDeckedIBeam::GetTopFlangeWidth(IndexType flangeIdx) const
{
   if (0 < flangeIdx) THROW_GEOMETRY(_T("PCIDeckedIBeam::GetTopFlangeWidth - invalid flange index"));
   return GetTopWidth();
}

IndexType PCIDeckedIBeam::GetBottomFlangeCount() const
{
   return 1;
}

Float64 PCIDeckedIBeam::GetBottomFlangeLocation(IndexType flangeIdx) const
{
   if (0 < flangeIdx) THROW_GEOMETRY(_T("PCIDeckedIBeam::GetBottomFlangeLocation - invalid flange index"));
   return 0.0;
}

Float64 PCIDeckedIBeam::GetBottomFlangeWidth(IndexType flangeIdx) const
{
   if (0 < flangeIdx) THROW_GEOMETRY(_T("PCIDeckedIBeam::GetBottomFlangeWidth - invalid flange index"));
   return GetBottomWidth();
}

Float64 PCIDeckedIBeam::GetTopWidth() const
{
   return m_W1 + 2 * (m_W2 - m_W5);
}

Float64 PCIDeckedIBeam::GetBottomWidth() const
{
   return m_W6;
}

Float64 PCIDeckedIBeam::GetAvgWebWidth() const
{
   return GetMinWebWidth();
}

Float64 PCIDeckedIBeam::GetShearWidth() const
{
   return GetAvgWebWidth();
}

Float64 PCIDeckedIBeam::GetMinWebWidth() const
{
   return m_T;
}

Float64 PCIDeckedIBeam::GetMinBottomFlangeThickness() const
{
   return m_D9;
}

Float64 PCIDeckedIBeam::GetMinTopFlangeThickness() const
{
   return m_D7;
}

MatingSurfaceIndexType PCIDeckedIBeam::GetMatingSurfaceCount() const
{
   return 1;
}

Float64 PCIDeckedIBeam::GetMatingSurfaceWidth(MatingSurfaceIndexType idx) const
{
   if (0 < idx) THROW_GEOMETRY(_T("PCIDeckedIBeam::GetMatingSurfaceWidth - index out of range"));
   return GetTopWidth();
}

Float64 PCIDeckedIBeam::GetMatingSurfaceLocation(MatingSurfaceIndexType idx) const
{
   if (0 < idx) THROW_GEOMETRY(_T("PCIDeckedIBeam::GetMatingSurfaceLocation - index out of range"));
   return 0;
}

IndexType PCIDeckedIBeam::GetWebCount() const
{
   return 1;
}

Plane3d PCIDeckedIBeam::GetWebPlane(WebIndexType webIdx) const
{
   if (0 < webIdx) THROW_GEOMETRY(_T("PCIDeckedIBeam::GetWebPlane - index out of range"));
   return Plane3d(0, 0, -1, 0); // vertical plane
}

void PCIDeckedIBeam::DoOffset(const Size2d& delta)
{
   GetHookPoint()->Offset(delta);
   SetDirtyFlag();
}

void PCIDeckedIBeam::DoRotate(const Point2d& center, Float64 angle)
{
   m_Rotation += angle;
   GetHookPoint()->Rotate(center, angle);
   SetDirtyFlag();
}

std::unique_ptr<Shape> PCIDeckedIBeam::CreateClone() const
{
   return std::make_unique<PCIDeckedIBeam>(*this);
}

#if defined _DEBUG
bool PCIDeckedIBeam::AssertValid() const
{
   return __super::AssertValid();
}

void PCIDeckedIBeam::Dump(WBFL::Debug::LogContext& os) const
{
   os << _T("*** Dump for PCIDeckedIBeam ***")<< WBFL::Debug::endl;
   __super::Dump( os );
}
#endif // _DEBUG

void PCIDeckedIBeam::OnUpdatePolygon(std::unique_ptr<Polygon>& polygon) const
{
   // Generate points along the left-hand side of the shape... 
   // then we will copy and mirror them about the Y axis
   std::vector<Point2d> vPoints;


   const long nSpaces = 20; // number of spaces used to approximate the curved fillets
   Float64 cx, cy;           // center of arc
   Float64 delta;            // sweep angle of arc
   Float64 startAngle;       // start angle for generating points along arc

   // Start at the bottom center of the shape
   vPoints.emplace_back(0, 0);

   if (IsZero(m_C1))
   {
      vPoints.emplace_back(-m_W6 / 2, 0.0);
   }
   else
   {
      vPoints.emplace_back(-m_W6 / 2 + m_C1, 0.0);
      vPoints.emplace_back(-m_W6 / 2, m_C1);
   }

   // compute angle of bottom flange (measured from vertical)
   delta = atan2((m_W6 - m_T) / 2, m_D8 - m_D9);

   // top of bottom flange
   cx = -m_W6 / 2 + m_R3;
   cy = m_D9 - m_R3 * tan(delta / 2);
   startAngle = M_PI;
   GenerateFillet(vPoints, cx, cy, m_R3, startAngle, -delta, nSpaces);

   // generate bottom left flange-web fillet
   cx = -m_T / 2 - m_R2;
   cy = m_D8 + m_R2 * tan(delta / 2);
   startAngle = TWO_PI - delta;

   GenerateFillet(vPoints, cx, cy, m_R2, startAngle, delta, nSpaces);

   // compute angle of top flange (measured from vertical)
   delta = atan2(m_W1 / 2 + m_W2, m_D6 - m_D1);

   // generate top left flange-web fillet
   cx = -m_T / 2 - m_R1;
   cy = m_H - m_D6 - m_R1 * tan(delta / 2);
   startAngle = 0.0;

   GenerateFillet(vPoints, cx, cy, m_R1, startAngle, delta, nSpaces);

   // bottom of top flange
   vPoints.emplace_back(-m_W1 / 2, m_H - m_D7);

   vPoints.emplace_back(-m_W1 / 2 - m_W2 + m_W3 + (m_W1 / 2 - (m_R1 + m_T / 2)), m_H - m_D1 + (m_D6 - m_D7));

   vPoints.emplace_back(-m_W1 / 2 - m_W2 + m_W3, m_H - m_D1);
   vPoints.emplace_back(-m_W1 / 2 - m_W2, m_H - m_D1);
   vPoints.emplace_back(-m_W1 / 2 - m_W2, m_H - m_D1 + m_D5);
   vPoints.emplace_back(-m_W1 / 2 - m_W2 + m_W5, m_H - m_D1 + m_D4 + m_D5);
   vPoints.emplace_back(-m_W1 / 2 - m_W2 + m_W5, m_H - m_D2 - m_D3);
   vPoints.emplace_back(-m_W1 / 2 - m_W2 + m_W5 - m_W4, m_H - m_D2);
   vPoints.emplace_back(-m_W1 / 2 - m_W2 + m_W5 - m_W4, m_H);

   vPoints.emplace_back(0, m_H);


   // get indicies of key top flange points
   IndexType nPoints = vPoints.size();
   m_LeftBottomIdx = nPoints - 4;
   m_LeftTopIdx = nPoints - 2;
   m_RightTopIdx = nPoints;
   m_RightBottomIdx = nPoints + 2;

   // add left hand points into the collection
   polygon->AddPoints(vPoints);

   polygon->SetSymmetry(Polygon::Symmetry::Y);

   if (!IsZero(m_Rotation))
      polygon->Rotate(Point2d(0, 0), m_Rotation);

   polygon->Move(Point2d(0, 0), *GetHookPoint());
}

#if defined _UNITTEST
#include <GeomModel/UnitTest.h>
bool PCIDeckedIBeam::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("PCIDeckedIBeam");

   PCIDeckedIBeam beam;

   // Use some real dimensions
   beam.SetW1(26);
   beam.SetW2(45.5);
   beam.SetW3(7.5);
   beam.SetW4(1);
   beam.SetW5(5.5);
   beam.SetW6(38.375);
   beam.SetD1(8);
   beam.SetD2(1);
   beam.SetD3(0.5);
   beam.SetD4(0.5);
   beam.SetD5(1);
   beam.SetD6(9);
   beam.SetD7(3);
   beam.SetD8(10);
   beam.SetD9(3.75);
   beam.SetH(54);
   beam.SetT(4);
   beam.SetR1(9);
   beam.SetR2(12);
   beam.SetR3(2);
   beam.SetC1(1.0);

   //
   // Bounding Box
   //
   Rect2d box = beam.GetBoundingBox();
   TRY_TESTME(IsEqual(box.Left(), -58.5));
   TRY_TESTME(IsEqual(box.Right(), 58.5));
   TRY_TESTME(IsEqual(box.Top(), 54.0));
   TRY_TESTME(IsEqual(box.Bottom(), 0.00));


   //
   // ShapeProperties
   //
   ShapeProperties props = beam.GetProperties();
   TRY_TESTME(IsEqual(props.GetArea(), 941.66528114402706));
   TRY_TESTME(IsEqual(props.GetIxx(), 420903.30302683858));
   TRY_TESTME(IsEqual(props.GetIyy(), 403184.22410364990));
   TRY_TESTME(IsEqual(props.GetIxy(), 0.0, 0.0005));
   TRY_TESTME(IsEqual(props.GetCentroid().X(), 0.0));
   TRY_TESTME(IsEqual(props.GetCentroid().Y(), 32.324778419863591));
   TRY_TESTME(props.GetCoordinateSystem() == ShapeProperties::CoordSystemType::Centroidal);

   TRY_TESTME(IsEqual(props.GetXleft(), 58.5));
   TRY_TESTME(IsEqual(props.GetXright(), 58.5));
   TRY_TESTME(IsEqual(props.GetYtop(), 54.0 - props.GetCentroid().Y()));
   TRY_TESTME(IsEqual(props.GetYbottom(), props.GetCentroid().Y()));

   //
   // Perimeter
   //
   TRY_TESTME(IsEqual(beam.GetPerimeter(), 403.95659655723534));

   //
   // FurthestDistance
   //

   // Shape on right
   Point2d p1(0, 20);
   Point2d p2(100, 20);
   Line2d line(p1, p2);
   TRY_TESTME(IsEqual(beam.GetFurthestDistance(line, Line2d::Side::Right), 20.000));

   // shape on left
   p1.Move(0, -20);
   p2.Move(100, -20);
   line.ThroughPoints(p1, p2);
   TRY_TESTME(IsEqual(beam.GetFurthestDistance(line, Line2d::Side::Right), -20.000));

   // 
   // PolyPoints
   //
   auto points = beam.GetPolyPoints();
   TRY_TESTME(points.size() == 151);

   int i = 0;
   TRY_TESTME(points[i++] == Point2d(  0.000000, 0.000000));
   TRY_TESTME(points[i++] == Point2d(-18.187500, 0.000000));
   TRY_TESTME(points[i++] == Point2d(-19.187500, 1.000000));
   TRY_TESTME(points[i++] == Point2d(-19.187500, 2.349145));
   TRY_TESTME(points[i++] == Point2d(-19.183768, 2.471272));
   TRY_TESTME(points[i++] == Point2d(-19.172585, 2.592943));
   TRY_TESTME(points[i++] == Point2d(-19.153994, 2.713703));
   TRY_TESTME(points[i++] == Point2d(-19.128063, 2.833104));
   TRY_TESTME(points[i++] == Point2d(-19.094890, 2.950698));
   TRY_TESTME(points[i++] == Point2d(-19.054597, 3.066047));
   TRY_TESTME(points[i++] == Point2d(-19.007337, 3.178720));
   TRY_TESTME(points[i++] == Point2d(-18.953284, 3.288297));
   TRY_TESTME(points[i++] == Point2d(-18.892642, 3.394369));
   TRY_TESTME(points[i++] == Point2d(-18.825635, 3.496540));
   TRY_TESTME(points[i++] == Point2d(-18.752514, 3.594429));
   TRY_TESTME(points[i++] == Point2d(-18.673553, 3.687670));
   TRY_TESTME(points[i++] == Point2d(-18.589045, 3.775915));
   TRY_TESTME(points[i++] == Point2d(-18.499306, 3.858835));
   TRY_TESTME(points[i++] == Point2d(-18.404672, 3.936121));
   TRY_TESTME(points[i++] == Point2d(-18.305495, 4.007484));
   TRY_TESTME(points[i++] == Point2d(-18.202145, 4.072658));
   TRY_TESTME(points[i++] == Point2d(-18.095008, 4.131399));
   TRY_TESTME(points[i++] == Point2d(-17.984484, 4.183489));
   TRY_TESTME(points[i++] == Point2d(-17.870986, 4.228732));
   TRY_TESTME(points[i++] == Point2d(-9.899083, 7.127606));
   TRY_TESTME(points[i++] == Point2d(-9.218094, 7.399066));
   TRY_TESTME(points[i++] == Point2d(-8.554951, 7.711604));
   TRY_TESTME(points[i++] == Point2d(-7.912131, 8.064051));
   TRY_TESTME(points[i++] == Point2d(-7.292032, 8.455094));
   TRY_TESTME(points[i++] == Point2d(-6.696968, 8.883272));
   TRY_TESTME(points[i++] == Point2d(-6.129161, 9.346988));
   TRY_TESTME(points[i++] == Point2d(-5.590729, 9.844510));
   TRY_TESTME(points[i++] == Point2d(-5.083683, 10.373982));
   TRY_TESTME(points[i++] == Point2d(-4.609914, 10.933429));
   TRY_TESTME(points[i++] == Point2d(-4.171190, 11.520761));
   TRY_TESTME(points[i++] == Point2d(-3.769150, 12.133787));
   TRY_TESTME(points[i++] == Point2d(-3.405293, 12.770219));
   TRY_TESTME(points[i++] == Point2d(-3.080978, 13.427681));
   TRY_TESTME(points[i++] == Point2d(-2.797415, 14.103721));
   TRY_TESTME(points[i++] == Point2d(-2.555663, 14.795814));
   TRY_TESTME(points[i++] == Point2d(-2.356622, 15.501378));
   TRY_TESTME(points[i++] == Point2d(-2.201038, 16.217779));
   TRY_TESTME(points[i++] == Point2d(-2.089489, 16.942344));
   TRY_TESTME(points[i++] == Point2d(-2.022393, 17.672368));
   TRY_TESTME(points[i++] == Point2d(-2.000000, 18.405127));
   TRY_TESTME(points[i++] == Point2d(-2.000000, 36.152531));
   TRY_TESTME(points[i++] == Point2d(-2.027144, 36.850995));
   TRY_TESTME(points[i++] == Point2d(-2.108411, 37.545246));
   TRY_TESTME(points[i++] == Point2d(-2.243313, 38.231096));
   TRY_TESTME(points[i++] == Point2d(-2.431034, 38.904408));
   TRY_TESTME(points[i++] == Point2d(-2.670443, 39.561121));
   TRY_TESTME(points[i++] == Point2d(-2.960095, 40.197273));
   TRY_TESTME(points[i++] == Point2d(-3.298244, 40.809028));
   TRY_TESTME(points[i++] == Point2d(-3.682850, 41.392695));
   TRY_TESTME(points[i++] == Point2d(-4.111592, 41.944753));
   TRY_TESTME(points[i++] == Point2d(-4.581885, 42.461873));
   TRY_TESTME(points[i++] == Point2d(-5.090891, 42.940935));
   TRY_TESTME(points[i++] == Point2d(-5.635541, 43.379051));
   TRY_TESTME(points[i++] == Point2d(-6.212549, 43.773576));
   TRY_TESTME(points[i++] == Point2d(-6.818435, 44.122131));
   TRY_TESTME(points[i++] == Point2d(-7.449544, 44.422614));
   TRY_TESTME(points[i++] == Point2d(-8.102069, 44.673212));
   TRY_TESTME(points[i++] == Point2d(-8.772074, 44.872414));
   TRY_TESTME(points[i++] == Point2d(-9.455518, 45.019017));
   TRY_TESTME(points[i++] == Point2d(-10.148279, 45.112139));
   TRY_TESTME(points[i++] == Point2d(-10.846176, 45.151217));
   TRY_TESTME(points[i++] == Point2d(-13.000000, 51.000000));
   TRY_TESTME(points[i++] == Point2d(-49.000000, 52.000000));
   TRY_TESTME(points[i++] == Point2d(-51.000000, 46.000000));
   TRY_TESTME(points[i++] == Point2d(-58.500000, 46.000000));
   TRY_TESTME(points[i++] == Point2d(-58.500000, 47.000000));
   TRY_TESTME(points[i++] == Point2d(-53.000000, 47.500000));
   TRY_TESTME(points[i++] == Point2d(-53.000000, 52.500000));
   TRY_TESTME(points[i++] == Point2d(-54.000000, 53.000000));
   TRY_TESTME(points[i++] == Point2d(-54.000000, 54.000000));
   TRY_TESTME(points[i++] == Point2d(  0.000000, 54.000000));
   TRY_TESTME(points[i++] == Point2d(54.000000, 54.000000));
   TRY_TESTME(points[i++] == Point2d(54.000000, 53.000000));
   TRY_TESTME(points[i++] == Point2d(53.000000, 52.500000));
   TRY_TESTME(points[i++] == Point2d(53.000000, 47.500000));
   TRY_TESTME(points[i++] == Point2d(58.500000, 47.000000));
   TRY_TESTME(points[i++] == Point2d(58.500000, 46.000000));
   TRY_TESTME(points[i++] == Point2d(51.000000, 46.000000));
   TRY_TESTME(points[i++] == Point2d(49.000000, 52.000000));
   TRY_TESTME(points[i++] == Point2d(13.000000, 51.000000));
   TRY_TESTME(points[i++] == Point2d(10.846176, 45.151217));
   TRY_TESTME(points[i++] == Point2d(10.148279, 45.112139));
   TRY_TESTME(points[i++] == Point2d(9.455518, 45.019017));
   TRY_TESTME(points[i++] == Point2d(8.772074, 44.872414));
   TRY_TESTME(points[i++] == Point2d(8.102069, 44.673212));
   TRY_TESTME(points[i++] == Point2d(7.449544, 44.422614));
   TRY_TESTME(points[i++] == Point2d(6.818435, 44.122131));
   TRY_TESTME(points[i++] == Point2d(6.212549, 43.773576));
   TRY_TESTME(points[i++] == Point2d(5.635541, 43.379051));
   TRY_TESTME(points[i++] == Point2d(5.090891, 42.940935));
   TRY_TESTME(points[i++] == Point2d(4.581885, 42.461873));
   TRY_TESTME(points[i++] == Point2d(4.111592, 41.944753));
   TRY_TESTME(points[i++] == Point2d(3.682850, 41.392695));
   TRY_TESTME(points[i++] == Point2d(3.298244, 40.809028));
   TRY_TESTME(points[i++] == Point2d(2.960095, 40.197273));
   TRY_TESTME(points[i++] == Point2d(2.670443, 39.561121));
   TRY_TESTME(points[i++] == Point2d(2.431034, 38.904408));
   TRY_TESTME(points[i++] == Point2d(2.243313, 38.231096));
   TRY_TESTME(points[i++] == Point2d(2.108411, 37.545246));
   TRY_TESTME(points[i++] == Point2d(2.027144, 36.850995));
   TRY_TESTME(points[i++] == Point2d(2.000000, 36.152531));
   TRY_TESTME(points[i++] == Point2d(2.000000, 18.405127));
   TRY_TESTME(points[i++] == Point2d(2.022393, 17.672368));
   TRY_TESTME(points[i++] == Point2d(2.089489, 16.942344));
   TRY_TESTME(points[i++] == Point2d(2.201038, 16.217779));
   TRY_TESTME(points[i++] == Point2d(2.356622, 15.501378));
   TRY_TESTME(points[i++] == Point2d(2.555663, 14.795814));
   TRY_TESTME(points[i++] == Point2d(2.797415, 14.103721));
   TRY_TESTME(points[i++] == Point2d(3.080978, 13.427681));
   TRY_TESTME(points[i++] == Point2d(3.405293, 12.770219));
   TRY_TESTME(points[i++] == Point2d(3.769150, 12.133787));
   TRY_TESTME(points[i++] == Point2d(4.171190, 11.520761));
   TRY_TESTME(points[i++] == Point2d(4.609914, 10.933429));
   TRY_TESTME(points[i++] == Point2d(5.083683, 10.373982));
   TRY_TESTME(points[i++] == Point2d(5.590729, 9.844510));
   TRY_TESTME(points[i++] == Point2d(6.129161, 9.346988));
   TRY_TESTME(points[i++] == Point2d(6.696968, 8.883272));
   TRY_TESTME(points[i++] == Point2d(7.292032, 8.455094));
   TRY_TESTME(points[i++] == Point2d(7.912131, 8.064051));
   TRY_TESTME(points[i++] == Point2d(8.554951, 7.711604));
   TRY_TESTME(points[i++] == Point2d(9.218094, 7.399066));
   TRY_TESTME(points[i++] == Point2d(9.899083, 7.127606));
   TRY_TESTME(points[i++] == Point2d(17.870986, 4.228732));
   TRY_TESTME(points[i++] == Point2d(17.984484, 4.183489));
   TRY_TESTME(points[i++] == Point2d(18.095008, 4.131399));
   TRY_TESTME(points[i++] == Point2d(18.202145, 4.072658));
   TRY_TESTME(points[i++] == Point2d(18.305495, 4.007484));
   TRY_TESTME(points[i++] == Point2d(18.404672, 3.936121));
   TRY_TESTME(points[i++] == Point2d(18.499306, 3.858835));
   TRY_TESTME(points[i++] == Point2d(18.589045, 3.775915));
   TRY_TESTME(points[i++] == Point2d(18.673553, 3.687670));
   TRY_TESTME(points[i++] == Point2d(18.752514, 3.594429));
   TRY_TESTME(points[i++] == Point2d(18.825635, 3.496540));
   TRY_TESTME(points[i++] == Point2d(18.892642, 3.394369));
   TRY_TESTME(points[i++] == Point2d(18.953284, 3.288297));
   TRY_TESTME(points[i++] == Point2d(19.007337, 3.178720));
   TRY_TESTME(points[i++] == Point2d(19.054597, 3.066047));
   TRY_TESTME(points[i++] == Point2d(19.094890, 2.950698));
   TRY_TESTME(points[i++] == Point2d(19.128063, 2.833104));
   TRY_TESTME(points[i++] == Point2d(19.153994, 2.713703));
   TRY_TESTME(points[i++] == Point2d(19.172585, 2.592943));
   TRY_TESTME(points[i++] == Point2d(19.183768, 2.471272));
   TRY_TESTME(points[i++] == Point2d(19.187500, 2.349145));
   TRY_TESTME(points[i++] == Point2d(19.187500, 1.000000));
   TRY_TESTME(points[i++] == Point2d(18.187500, 0.000000));
   TRY_TESTME(points[i++] == Point2d(0.000000, 0.000000));
   TRY_TESTME(i == points.size());

   //
   // PointInShape
   //
   Point2d pnt(0.0, 0.5);
   TRY_TESTME(beam.PointInShape(pnt) == true);

   pnt.Move(500, 500);
   TRY_TESTME(beam.PointInShape(pnt) == false);

   pnt.Move(0, 0); // Point on perimeter
   TRY_TESTME(beam.PointInShape(pnt) == false);

   // Test hook point behavior
   TRY_TESTME(UnitTest::TestHookPoint(beam) == true);


   // Test properties
   TRY_TESTME(IsEqual(beam.GetHeight(), 54.));
   TRY_TESTME(IsEqual(beam.GetTopFlangeWidth(0), 106.));
   TRY_TESTME(IsEqual(beam.GetBottomFlangeWidth(0), 38.375));
   TRY_TESTME(IsEqual(beam.GetAvgWebWidth(), 4.));


   //
   // MoveEx (tests Offset as well)
   //
   Point2d from(0, 0);
   Point2d to(100, 100);
   beam.Move(from, to);
   points = beam.GetPolyPoints();

   points = beam.GetPolyPoints();
   TRY_TESTME(points.size() == 151);

   i = 0;
   TRY_TESTME(points[i++] == Point2d(100.000000, 100.000000));
   TRY_TESTME(points[i++] == Point2d(81.812500, 100.000000));
   TRY_TESTME(points[i++] == Point2d(80.812500, 101.000000));
   TRY_TESTME(points[i++] == Point2d(80.812500, 102.349145));
   TRY_TESTME(points[i++] == Point2d(80.816232, 102.471272));
   TRY_TESTME(points[i++] == Point2d(80.827415, 102.592943));
   TRY_TESTME(points[i++] == Point2d(80.846006, 102.713703));
   TRY_TESTME(points[i++] == Point2d(80.871937, 102.833104));
   TRY_TESTME(points[i++] == Point2d(80.905110, 102.950698));
   TRY_TESTME(points[i++] == Point2d(80.945403, 103.066047));
   TRY_TESTME(points[i++] == Point2d(80.992663, 103.178720));
   TRY_TESTME(points[i++] == Point2d(81.046716, 103.288297));
   TRY_TESTME(points[i++] == Point2d(81.107358, 103.394369));
   TRY_TESTME(points[i++] == Point2d(81.174365, 103.496540));
   TRY_TESTME(points[i++] == Point2d(81.247486, 103.594429));
   TRY_TESTME(points[i++] == Point2d(81.326447, 103.687670));
   TRY_TESTME(points[i++] == Point2d(81.410955, 103.775915));
   TRY_TESTME(points[i++] == Point2d(81.500694, 103.858835));
   TRY_TESTME(points[i++] == Point2d(81.595328, 103.936121));
   TRY_TESTME(points[i++] == Point2d(81.694505, 104.007484));
   TRY_TESTME(points[i++] == Point2d(81.797855, 104.072658));
   TRY_TESTME(points[i++] == Point2d(81.904992, 104.131399));
   TRY_TESTME(points[i++] == Point2d(82.015516, 104.183489));
   TRY_TESTME(points[i++] == Point2d(82.129014, 104.228732));
   TRY_TESTME(points[i++] == Point2d(90.100917, 107.127606));
   TRY_TESTME(points[i++] == Point2d(90.781906, 107.399066));
   TRY_TESTME(points[i++] == Point2d(91.445049, 107.711604));
   TRY_TESTME(points[i++] == Point2d(92.087869, 108.064051));
   TRY_TESTME(points[i++] == Point2d(92.707968, 108.455094));
   TRY_TESTME(points[i++] == Point2d(93.303032, 108.883272));
   TRY_TESTME(points[i++] == Point2d(93.870839, 109.346988));
   TRY_TESTME(points[i++] == Point2d(94.409271, 109.844510));
   TRY_TESTME(points[i++] == Point2d(94.916317, 110.373982));
   TRY_TESTME(points[i++] == Point2d(95.390086, 110.933429));
   TRY_TESTME(points[i++] == Point2d(95.828810, 111.520761));
   TRY_TESTME(points[i++] == Point2d(96.230850, 112.133787));
   TRY_TESTME(points[i++] == Point2d(96.594707, 112.770219));
   TRY_TESTME(points[i++] == Point2d(96.919022, 113.427681));
   TRY_TESTME(points[i++] == Point2d(97.202585, 114.103721));
   TRY_TESTME(points[i++] == Point2d(97.444337, 114.795814));
   TRY_TESTME(points[i++] == Point2d(97.643378, 115.501378));
   TRY_TESTME(points[i++] == Point2d(97.798962, 116.217779));
   TRY_TESTME(points[i++] == Point2d(97.910511, 116.942344));
   TRY_TESTME(points[i++] == Point2d(97.977607, 117.672368));
   TRY_TESTME(points[i++] == Point2d(98.000000, 118.405127));
   TRY_TESTME(points[i++] == Point2d(98.000000, 136.152531));
   TRY_TESTME(points[i++] == Point2d(97.972856, 136.850995));
   TRY_TESTME(points[i++] == Point2d(97.891589, 137.545246));
   TRY_TESTME(points[i++] == Point2d(97.756687, 138.231096));
   TRY_TESTME(points[i++] == Point2d(97.568966, 138.904408));
   TRY_TESTME(points[i++] == Point2d(97.329557, 139.561121));
   TRY_TESTME(points[i++] == Point2d(97.039905, 140.197273));
   TRY_TESTME(points[i++] == Point2d(96.701756, 140.809028));
   TRY_TESTME(points[i++] == Point2d(96.317150, 141.392695));
   TRY_TESTME(points[i++] == Point2d(95.888408, 141.944753));
   TRY_TESTME(points[i++] == Point2d(95.418115, 142.461873));
   TRY_TESTME(points[i++] == Point2d(94.909109, 142.940935));
   TRY_TESTME(points[i++] == Point2d(94.364459, 143.379051));
   TRY_TESTME(points[i++] == Point2d(93.787451, 143.773576));
   TRY_TESTME(points[i++] == Point2d(93.181565, 144.122131));
   TRY_TESTME(points[i++] == Point2d(92.550456, 144.422614));
   TRY_TESTME(points[i++] == Point2d(91.897931, 144.673212));
   TRY_TESTME(points[i++] == Point2d(91.227926, 144.872414));
   TRY_TESTME(points[i++] == Point2d(90.544482, 145.019017));
   TRY_TESTME(points[i++] == Point2d(89.851721, 145.112139));
   TRY_TESTME(points[i++] == Point2d(89.153824, 145.151217));
   TRY_TESTME(points[i++] == Point2d(87.000000, 151.000000));
   TRY_TESTME(points[i++] == Point2d(51.000000, 152.000000));
   TRY_TESTME(points[i++] == Point2d(49.000000, 146.000000));
   TRY_TESTME(points[i++] == Point2d(41.500000, 146.000000));
   TRY_TESTME(points[i++] == Point2d(41.500000, 147.000000));
   TRY_TESTME(points[i++] == Point2d(47.000000, 147.500000));
   TRY_TESTME(points[i++] == Point2d(47.000000, 152.500000));
   TRY_TESTME(points[i++] == Point2d(46.000000, 153.000000));
   TRY_TESTME(points[i++] == Point2d(46.000000, 154.000000));
   TRY_TESTME(points[i++] == Point2d(100.000000, 154.000000));
   TRY_TESTME(points[i++] == Point2d(154.000000, 154.000000));
   TRY_TESTME(points[i++] == Point2d(154.000000, 153.000000));
   TRY_TESTME(points[i++] == Point2d(153.000000, 152.500000));
   TRY_TESTME(points[i++] == Point2d(153.000000, 147.500000));
   TRY_TESTME(points[i++] == Point2d(158.500000, 147.000000));
   TRY_TESTME(points[i++] == Point2d(158.500000, 146.000000));
   TRY_TESTME(points[i++] == Point2d(151.000000, 146.000000));
   TRY_TESTME(points[i++] == Point2d(149.000000, 152.000000));
   TRY_TESTME(points[i++] == Point2d(113.000000, 151.000000));
   TRY_TESTME(points[i++] == Point2d(110.846176, 145.151217));
   TRY_TESTME(points[i++] == Point2d(110.148279, 145.112139));
   TRY_TESTME(points[i++] == Point2d(109.455518, 145.019017));
   TRY_TESTME(points[i++] == Point2d(108.772074, 144.872414));
   TRY_TESTME(points[i++] == Point2d(108.102069, 144.673212));
   TRY_TESTME(points[i++] == Point2d(107.449544, 144.422614));
   TRY_TESTME(points[i++] == Point2d(106.818435, 144.122131));
   TRY_TESTME(points[i++] == Point2d(106.212549, 143.773576));
   TRY_TESTME(points[i++] == Point2d(105.635541, 143.379051));
   TRY_TESTME(points[i++] == Point2d(105.090891, 142.940935));
   TRY_TESTME(points[i++] == Point2d(104.581885, 142.461873));
   TRY_TESTME(points[i++] == Point2d(104.111592, 141.944753));
   TRY_TESTME(points[i++] == Point2d(103.682850, 141.392695));
   TRY_TESTME(points[i++] == Point2d(103.298244, 140.809028));
   TRY_TESTME(points[i++] == Point2d(102.960095, 140.197273));
   TRY_TESTME(points[i++] == Point2d(102.670443, 139.561121));
   TRY_TESTME(points[i++] == Point2d(102.431034, 138.904408));
   TRY_TESTME(points[i++] == Point2d(102.243313, 138.231096));
   TRY_TESTME(points[i++] == Point2d(102.108411, 137.545246));
   TRY_TESTME(points[i++] == Point2d(102.027144, 136.850995));
   TRY_TESTME(points[i++] == Point2d(102.000000, 136.152531));
   TRY_TESTME(points[i++] == Point2d(102.000000, 118.405127));
   TRY_TESTME(points[i++] == Point2d(102.022393, 117.672368));
   TRY_TESTME(points[i++] == Point2d(102.089489, 116.942344));
   TRY_TESTME(points[i++] == Point2d(102.201038, 116.217779));
   TRY_TESTME(points[i++] == Point2d(102.356622, 115.501378));
   TRY_TESTME(points[i++] == Point2d(102.555663, 114.795814));
   TRY_TESTME(points[i++] == Point2d(102.797415, 114.103721));
   TRY_TESTME(points[i++] == Point2d(103.080978, 113.427681));
   TRY_TESTME(points[i++] == Point2d(103.405293, 112.770219));
   TRY_TESTME(points[i++] == Point2d(103.769150, 112.133787));
   TRY_TESTME(points[i++] == Point2d(104.171190, 111.520761));
   TRY_TESTME(points[i++] == Point2d(104.609914, 110.933429));
   TRY_TESTME(points[i++] == Point2d(105.083683, 110.373982));
   TRY_TESTME(points[i++] == Point2d(105.590729, 109.844510));
   TRY_TESTME(points[i++] == Point2d(106.129161, 109.346988));
   TRY_TESTME(points[i++] == Point2d(106.696968, 108.883272));
   TRY_TESTME(points[i++] == Point2d(107.292032, 108.455094));
   TRY_TESTME(points[i++] == Point2d(107.912131, 108.064051));
   TRY_TESTME(points[i++] == Point2d(108.554951, 107.711604));
   TRY_TESTME(points[i++] == Point2d(109.218094, 107.399066));
   TRY_TESTME(points[i++] == Point2d(109.899083, 107.127606));
   TRY_TESTME(points[i++] == Point2d(117.870986, 104.228732));
   TRY_TESTME(points[i++] == Point2d(117.984484, 104.183489));
   TRY_TESTME(points[i++] == Point2d(118.095008, 104.131399));
   TRY_TESTME(points[i++] == Point2d(118.202145, 104.072658));
   TRY_TESTME(points[i++] == Point2d(118.305495, 104.007484));
   TRY_TESTME(points[i++] == Point2d(118.404672, 103.936121));
   TRY_TESTME(points[i++] == Point2d(118.499306, 103.858835));
   TRY_TESTME(points[i++] == Point2d(118.589045, 103.775915));
   TRY_TESTME(points[i++] == Point2d(118.673553, 103.687670));
   TRY_TESTME(points[i++] == Point2d(118.752514, 103.594429));
   TRY_TESTME(points[i++] == Point2d(118.825635, 103.496540));
   TRY_TESTME(points[i++] == Point2d(118.892642, 103.394369));
   TRY_TESTME(points[i++] == Point2d(118.953284, 103.288297));
   TRY_TESTME(points[i++] == Point2d(119.007337, 103.178720));
   TRY_TESTME(points[i++] == Point2d(119.054597, 103.066047));
   TRY_TESTME(points[i++] == Point2d(119.094890, 102.950698));
   TRY_TESTME(points[i++] == Point2d(119.128063, 102.833104));
   TRY_TESTME(points[i++] == Point2d(119.153994, 102.713703));
   TRY_TESTME(points[i++] == Point2d(119.172585, 102.592943));
   TRY_TESTME(points[i++] == Point2d(119.183768, 102.471272));
   TRY_TESTME(points[i++] == Point2d(119.187500, 102.349145));
   TRY_TESTME(points[i++] == Point2d(119.187500, 101.000000));
   TRY_TESTME(points[i++] == Point2d(118.187500, 100.000000));
   TRY_TESTME(points[i++] == Point2d(100.000000, 100.000000));
   TRY_TESTME(i == points.size());

   //
   // OffsetEx
   //

   Size2d size(-100, -100);
   beam.Offset(size);

   points = beam.GetPolyPoints();
   TRY_TESTME(points.size() == 151);

   i = 0;
   TRY_TESTME(points[i++] == Point2d(0.000000, 0.000000));
   TRY_TESTME(points[i++] == Point2d(-18.187500, 0.000000));
   TRY_TESTME(points[i++] == Point2d(-19.187500, 1.000000));
   TRY_TESTME(points[i++] == Point2d(-19.187500, 2.349145));
   TRY_TESTME(points[i++] == Point2d(-19.183768, 2.471272));
   TRY_TESTME(points[i++] == Point2d(-19.172585, 2.592943));
   TRY_TESTME(points[i++] == Point2d(-19.153994, 2.713703));
   TRY_TESTME(points[i++] == Point2d(-19.128063, 2.833104));
   TRY_TESTME(points[i++] == Point2d(-19.094890, 2.950698));
   TRY_TESTME(points[i++] == Point2d(-19.054597, 3.066047));
   TRY_TESTME(points[i++] == Point2d(-19.007337, 3.178720));
   TRY_TESTME(points[i++] == Point2d(-18.953284, 3.288297));
   TRY_TESTME(points[i++] == Point2d(-18.892642, 3.394369));
   TRY_TESTME(points[i++] == Point2d(-18.825635, 3.496540));
   TRY_TESTME(points[i++] == Point2d(-18.752514, 3.594429));
   TRY_TESTME(points[i++] == Point2d(-18.673553, 3.687670));
   TRY_TESTME(points[i++] == Point2d(-18.589045, 3.775915));
   TRY_TESTME(points[i++] == Point2d(-18.499306, 3.858835));
   TRY_TESTME(points[i++] == Point2d(-18.404672, 3.936121));
   TRY_TESTME(points[i++] == Point2d(-18.305495, 4.007484));
   TRY_TESTME(points[i++] == Point2d(-18.202145, 4.072658));
   TRY_TESTME(points[i++] == Point2d(-18.095008, 4.131399));
   TRY_TESTME(points[i++] == Point2d(-17.984484, 4.183489));
   TRY_TESTME(points[i++] == Point2d(-17.870986, 4.228732));
   TRY_TESTME(points[i++] == Point2d(-9.899083, 7.127606));
   TRY_TESTME(points[i++] == Point2d(-9.218094, 7.399066));
   TRY_TESTME(points[i++] == Point2d(-8.554951, 7.711604));
   TRY_TESTME(points[i++] == Point2d(-7.912131, 8.064051));
   TRY_TESTME(points[i++] == Point2d(-7.292032, 8.455094));
   TRY_TESTME(points[i++] == Point2d(-6.696968, 8.883272));
   TRY_TESTME(points[i++] == Point2d(-6.129161, 9.346988));
   TRY_TESTME(points[i++] == Point2d(-5.590729, 9.844510));
   TRY_TESTME(points[i++] == Point2d(-5.083683, 10.373982));
   TRY_TESTME(points[i++] == Point2d(-4.609914, 10.933429));
   TRY_TESTME(points[i++] == Point2d(-4.171190, 11.520761));
   TRY_TESTME(points[i++] == Point2d(-3.769150, 12.133787));
   TRY_TESTME(points[i++] == Point2d(-3.405293, 12.770219));
   TRY_TESTME(points[i++] == Point2d(-3.080978, 13.427681));
   TRY_TESTME(points[i++] == Point2d(-2.797415, 14.103721));
   TRY_TESTME(points[i++] == Point2d(-2.555663, 14.795814));
   TRY_TESTME(points[i++] == Point2d(-2.356622, 15.501378));
   TRY_TESTME(points[i++] == Point2d(-2.201038, 16.217779));
   TRY_TESTME(points[i++] == Point2d(-2.089489, 16.942344));
   TRY_TESTME(points[i++] == Point2d(-2.022393, 17.672368));
   TRY_TESTME(points[i++] == Point2d(-2.000000, 18.405127));
   TRY_TESTME(points[i++] == Point2d(-2.000000, 36.152531));
   TRY_TESTME(points[i++] == Point2d(-2.027144, 36.850995));
   TRY_TESTME(points[i++] == Point2d(-2.108411, 37.545246));
   TRY_TESTME(points[i++] == Point2d(-2.243313, 38.231096));
   TRY_TESTME(points[i++] == Point2d(-2.431034, 38.904408));
   TRY_TESTME(points[i++] == Point2d(-2.670443, 39.561121));
   TRY_TESTME(points[i++] == Point2d(-2.960095, 40.197273));
   TRY_TESTME(points[i++] == Point2d(-3.298244, 40.809028));
   TRY_TESTME(points[i++] == Point2d(-3.682850, 41.392695));
   TRY_TESTME(points[i++] == Point2d(-4.111592, 41.944753));
   TRY_TESTME(points[i++] == Point2d(-4.581885, 42.461873));
   TRY_TESTME(points[i++] == Point2d(-5.090891, 42.940935));
   TRY_TESTME(points[i++] == Point2d(-5.635541, 43.379051));
   TRY_TESTME(points[i++] == Point2d(-6.212549, 43.773576));
   TRY_TESTME(points[i++] == Point2d(-6.818435, 44.122131));
   TRY_TESTME(points[i++] == Point2d(-7.449544, 44.422614));
   TRY_TESTME(points[i++] == Point2d(-8.102069, 44.673212));
   TRY_TESTME(points[i++] == Point2d(-8.772074, 44.872414));
   TRY_TESTME(points[i++] == Point2d(-9.455518, 45.019017));
   TRY_TESTME(points[i++] == Point2d(-10.148279, 45.112139));
   TRY_TESTME(points[i++] == Point2d(-10.846176, 45.151217));
   TRY_TESTME(points[i++] == Point2d(-13.000000, 51.000000));
   TRY_TESTME(points[i++] == Point2d(-49.000000, 52.000000));
   TRY_TESTME(points[i++] == Point2d(-51.000000, 46.000000));
   TRY_TESTME(points[i++] == Point2d(-58.500000, 46.000000));
   TRY_TESTME(points[i++] == Point2d(-58.500000, 47.000000));
   TRY_TESTME(points[i++] == Point2d(-53.000000, 47.500000));
   TRY_TESTME(points[i++] == Point2d(-53.000000, 52.500000));
   TRY_TESTME(points[i++] == Point2d(-54.000000, 53.000000));
   TRY_TESTME(points[i++] == Point2d(-54.000000, 54.000000));
   TRY_TESTME(points[i++] == Point2d(0.000000, 54.000000));
   TRY_TESTME(points[i++] == Point2d(54.000000, 54.000000));
   TRY_TESTME(points[i++] == Point2d(54.000000, 53.000000));
   TRY_TESTME(points[i++] == Point2d(53.000000, 52.500000));
   TRY_TESTME(points[i++] == Point2d(53.000000, 47.500000));
   TRY_TESTME(points[i++] == Point2d(58.500000, 47.000000));
   TRY_TESTME(points[i++] == Point2d(58.500000, 46.000000));
   TRY_TESTME(points[i++] == Point2d(51.000000, 46.000000));
   TRY_TESTME(points[i++] == Point2d(49.000000, 52.000000));
   TRY_TESTME(points[i++] == Point2d(13.000000, 51.000000));
   TRY_TESTME(points[i++] == Point2d(10.846176, 45.151217));
   TRY_TESTME(points[i++] == Point2d(10.148279, 45.112139));
   TRY_TESTME(points[i++] == Point2d(9.455518, 45.019017));
   TRY_TESTME(points[i++] == Point2d(8.772074, 44.872414));
   TRY_TESTME(points[i++] == Point2d(8.102069, 44.673212));
   TRY_TESTME(points[i++] == Point2d(7.449544, 44.422614));
   TRY_TESTME(points[i++] == Point2d(6.818435, 44.122131));
   TRY_TESTME(points[i++] == Point2d(6.212549, 43.773576));
   TRY_TESTME(points[i++] == Point2d(5.635541, 43.379051));
   TRY_TESTME(points[i++] == Point2d(5.090891, 42.940935));
   TRY_TESTME(points[i++] == Point2d(4.581885, 42.461873));
   TRY_TESTME(points[i++] == Point2d(4.111592, 41.944753));
   TRY_TESTME(points[i++] == Point2d(3.682850, 41.392695));
   TRY_TESTME(points[i++] == Point2d(3.298244, 40.809028));
   TRY_TESTME(points[i++] == Point2d(2.960095, 40.197273));
   TRY_TESTME(points[i++] == Point2d(2.670443, 39.561121));
   TRY_TESTME(points[i++] == Point2d(2.431034, 38.904408));
   TRY_TESTME(points[i++] == Point2d(2.243313, 38.231096));
   TRY_TESTME(points[i++] == Point2d(2.108411, 37.545246));
   TRY_TESTME(points[i++] == Point2d(2.027144, 36.850995));
   TRY_TESTME(points[i++] == Point2d(2.000000, 36.152531));
   TRY_TESTME(points[i++] == Point2d(2.000000, 18.405127));
   TRY_TESTME(points[i++] == Point2d(2.022393, 17.672368));
   TRY_TESTME(points[i++] == Point2d(2.089489, 16.942344));
   TRY_TESTME(points[i++] == Point2d(2.201038, 16.217779));
   TRY_TESTME(points[i++] == Point2d(2.356622, 15.501378));
   TRY_TESTME(points[i++] == Point2d(2.555663, 14.795814));
   TRY_TESTME(points[i++] == Point2d(2.797415, 14.103721));
   TRY_TESTME(points[i++] == Point2d(3.080978, 13.427681));
   TRY_TESTME(points[i++] == Point2d(3.405293, 12.770219));
   TRY_TESTME(points[i++] == Point2d(3.769150, 12.133787));
   TRY_TESTME(points[i++] == Point2d(4.171190, 11.520761));
   TRY_TESTME(points[i++] == Point2d(4.609914, 10.933429));
   TRY_TESTME(points[i++] == Point2d(5.083683, 10.373982));
   TRY_TESTME(points[i++] == Point2d(5.590729, 9.844510));
   TRY_TESTME(points[i++] == Point2d(6.129161, 9.346988));
   TRY_TESTME(points[i++] == Point2d(6.696968, 8.883272));
   TRY_TESTME(points[i++] == Point2d(7.292032, 8.455094));
   TRY_TESTME(points[i++] == Point2d(7.912131, 8.064051));
   TRY_TESTME(points[i++] == Point2d(8.554951, 7.711604));
   TRY_TESTME(points[i++] == Point2d(9.218094, 7.399066));
   TRY_TESTME(points[i++] == Point2d(9.899083, 7.127606));
   TRY_TESTME(points[i++] == Point2d(17.870986, 4.228732));
   TRY_TESTME(points[i++] == Point2d(17.984484, 4.183489));
   TRY_TESTME(points[i++] == Point2d(18.095008, 4.131399));
   TRY_TESTME(points[i++] == Point2d(18.202145, 4.072658));
   TRY_TESTME(points[i++] == Point2d(18.305495, 4.007484));
   TRY_TESTME(points[i++] == Point2d(18.404672, 3.936121));
   TRY_TESTME(points[i++] == Point2d(18.499306, 3.858835));
   TRY_TESTME(points[i++] == Point2d(18.589045, 3.775915));
   TRY_TESTME(points[i++] == Point2d(18.673553, 3.687670));
   TRY_TESTME(points[i++] == Point2d(18.752514, 3.594429));
   TRY_TESTME(points[i++] == Point2d(18.825635, 3.496540));
   TRY_TESTME(points[i++] == Point2d(18.892642, 3.394369));
   TRY_TESTME(points[i++] == Point2d(18.953284, 3.288297));
   TRY_TESTME(points[i++] == Point2d(19.007337, 3.178720));
   TRY_TESTME(points[i++] == Point2d(19.054597, 3.066047));
   TRY_TESTME(points[i++] == Point2d(19.094890, 2.950698));
   TRY_TESTME(points[i++] == Point2d(19.128063, 2.833104));
   TRY_TESTME(points[i++] == Point2d(19.153994, 2.713703));
   TRY_TESTME(points[i++] == Point2d(19.172585, 2.592943));
   TRY_TESTME(points[i++] == Point2d(19.183768, 2.471272));
   TRY_TESTME(points[i++] == Point2d(19.187500, 2.349145));
   TRY_TESTME(points[i++] == Point2d(19.187500, 1.000000));
   TRY_TESTME(points[i++] == Point2d(18.187500, 0.000000));
   TRY_TESTME(points[i++] == Point2d(0.000000, 0.000000));
   TRY_TESTME(i == points.size());

   //
   // RotateEx (Provides coverage of Rotate)
   //
   auto hookPnt = beam.GetHookPoint();
   hookPnt->Move(0, 0);
   Point2d c(0, 0);
   beam.Rotate(c, M_PI/6);
   points = beam.GetPolyPoints();
   TRY_TESTME(points.size() == 151);

   i = 0;
   TRY_TESTME(points[i++] == Point2d(0.000000, 0.000000));
   TRY_TESTME(points[i++] == Point2d(-15.750837, -9.093750));
   TRY_TESTME(points[i++] == Point2d(-17.116862, -8.727725));
   TRY_TESTME(points[i++] == Point2d(-17.791435, -7.559330));
   TRY_TESTME(points[i++] == Point2d(-17.849266, -7.451700));
   TRY_TESTME(points[i++] == Point2d(-17.900417, -7.340738));
   TRY_TESTME(points[i++] == Point2d(-17.944697, -7.226861));
   TRY_TESTME(points[i++] == Point2d(-17.981940, -7.110492));
   TRY_TESTME(points[i++] == Point2d(-18.012008, -6.992066));
   TRY_TESTME(points[i++] == Point2d(-18.034789, -6.872025));
   TRY_TESTME(points[i++] == Point2d(-18.050197, -6.750816));
   TRY_TESTME(points[i++] == Point2d(-18.058174, -6.628894));
   TRY_TESTME(points[i++] == Point2d(-18.058692, -6.506711));
   TRY_TESTME(points[i++] == Point2d(-18.051748, -6.384725));
   TRY_TESTME(points[i++] == Point2d(-18.037368, -6.263391));
   TRY_TESTME(points[i++] == Point2d(-18.015606, -6.143161));
   TRY_TESTME(points[i++] == Point2d(-17.986543, -6.024484));
   TRY_TESTME(points[i++] == Point2d(-17.950287, -5.907804));
   TRY_TESTME(points[i++] == Point2d(-17.906974, -5.793555));
   TRY_TESTME(points[i++] == Point2d(-17.856766, -5.682164));
   TRY_TESTME(points[i++] == Point2d(-17.799849, -5.574047));
   TRY_TESTME(points[i++] == Point2d(-17.736436, -5.469607));
   TRY_TESTME(points[i++] == Point2d(-17.666765, -5.369234));
   TRY_TESTME(points[i++] == Point2d(-17.591094, -5.273303));
   TRY_TESTME(points[i++] == Point2d(-12.136661, 1.223146));
   TRY_TESTME(points[i++] == Point2d(-11.682637, 1.798733));
   TRY_TESTME(points[i++] == Point2d(-11.264607, 2.400969));
   TRY_TESTME(points[i++] == Point2d(-10.884132, 3.027608));
   TRY_TESTME(points[i++] == Point2d(-10.542632, 3.676310));
   TRY_TESTME(points[i++] == Point2d(-10.241381, 4.344655));
   TRY_TESTME(points[i++] == Point2d(-9.981503, 5.030148));
   TRY_TESTME(points[i++] == Point2d(-9.763969, 5.730231));
   TRY_TESTME(points[i++] == Point2d(-9.589590, 6.442291));
   TRY_TESTME(points[i++] == Point2d(-9.459017, 7.163670));
   TRY_TESTME(points[i++] == Point2d(-9.372737, 7.891676));
   TRY_TESTME(points[i++] == Point2d(-9.331073, 8.623593));
   TRY_TESTME(points[i++] == Point2d(-9.334180, 9.356687));
   TRY_TESTME(points[i++] == Point2d(-9.382046, 10.088224));
   TRY_TESTME(points[i++] == Point2d(-9.474493, 10.815473));
   TRY_TESTME(points[i++] == Point2d(-9.611176, 11.535719));
   TRY_TESTME(points[i++] == Point2d(-9.791584, 12.246276));
   TRY_TESTME(points[i++] == Point2d(-10.015044, 12.944490));
   TRY_TESTME(points[i++] == Point2d(-10.280723, 13.627756));
   TRY_TESTME(points[i++] == Point2d(-10.587628, 14.293523));
   TRY_TESTME(points[i++] == Point2d(-10.934614, 14.939308));
   TRY_TESTME(points[i++] == Point2d(-19.808316, 30.309011));
   TRY_TESTME(points[i++] == Point2d(-20.181056, 30.900326));
   TRY_TESTME(points[i++] == Point2d(-20.598561, 31.460931));
   TRY_TESTME(points[i++] == Point2d(-21.058314, 31.987444));
   TRY_TESTME(points[i++] == Point2d(-21.557541, 32.476688));
   TRY_TESTME(points[i++] == Point2d(-22.093232, 32.925714));
   TRY_TESTME(points[i++] == Point2d(-22.662154, 33.331812));
   TRY_TESTME(points[i++] == Point2d(-23.260877, 33.692533));
   TRY_TESTME(points[i++] == Point2d(-23.885789, 34.005700));
   TRY_TESTME(points[i++] == Point2d(-24.533119, 34.269426));
   TRY_TESTME(points[i++] == Point2d(-25.198965, 34.482119));
   TRY_TESTME(points[i++] == Point2d(-25.879309, 34.642495));
   TRY_TESTME(points[i++] == Point2d(-26.570047, 34.749589));
   TRY_TESTME(points[i++] == Point2d(-27.267013, 34.802754));
   TRY_TESTME(points[i++] == Point2d(-27.966003, 34.801669));
   TRY_TESTME(points[i++] == Point2d(-28.662801, 34.746340));
   TRY_TESTME(points[i++] == Point2d(-29.353203, 34.637102));
   TRY_TESTME(points[i++] == Point2d(-30.033046, 34.474613));
   TRY_TESTME(points[i++] == Point2d(-30.698228, 34.259854));
   TRY_TESTME(points[i++] == Point2d(-31.344737, 33.994119));
   TRY_TESTME(points[i++] == Point2d(-31.968673, 33.679013));
   TRY_TESTME(points[i++] == Point2d(-36.758330, 37.667296));
   TRY_TESTME(points[i++] == Point2d(-68.435245, 20.533321));
   TRY_TESTME(points[i++] == Point2d(-67.167296, 14.337169));
   TRY_TESTME(points[i++] == Point2d(-73.662486, 10.587169));
   TRY_TESTME(points[i++] == Point2d(-74.162486, 11.453194));
   TRY_TESTME(points[i++] == Point2d(-69.649346, 14.636207));
   TRY_TESTME(points[i++] == Point2d(-72.149346, 18.966334));
   TRY_TESTME(points[i++] == Point2d(-73.265372, 18.899346));
   TRY_TESTME(points[i++] == Point2d(-73.765372, 19.765372));
   TRY_TESTME(points[i++] == Point2d(-27.000000, 46.765372));
   TRY_TESTME(points[i++] == Point2d(19.765372, 73.765372));
   TRY_TESTME(points[i++] == Point2d(20.265372, 72.899346));
   TRY_TESTME(points[i++] == Point2d(19.649346, 71.966334));
   TRY_TESTME(points[i++] == Point2d(22.149346, 67.636207));
   TRY_TESTME(points[i++] == Point2d(27.162486, 69.953194));
   TRY_TESTME(points[i++] == Point2d(27.662486, 69.087169));
   TRY_TESTME(points[i++] == Point2d(21.167296, 65.337169));
   TRY_TESTME(points[i++] == Point2d(16.435245, 69.533321));
   TRY_TESTME(points[i++] == Point2d(-14.241670, 50.667296));
   TRY_TESTME(points[i++] == Point2d(-13.182544, 44.525189));
   TRY_TESTME(points[i++] == Point2d(-13.767403, 44.142398));
   TRY_TESTME(points[i++] == Point2d(-14.320790, 43.715372));
   TRY_TESTME(points[i++] == Point2d(-14.839368, 43.246687));
   TRY_TESTME(points[i++] == Point2d(-15.320008, 42.739171));
   TRY_TESTME(points[i++] == Point2d(-15.759813, 42.195884));
   TRY_TESTME(points[i++] == Point2d(-16.156127, 41.620104));
   TRY_TESTME(points[i++] == Point2d(-16.506562, 41.015303));
   TRY_TESTME(points[i++] == Point2d(-16.809004, 40.385130));
   TRY_TESTME(points[i++] == Point2d(-17.061627, 39.733386));
   TRY_TESTME(points[i++] == Point2d(-17.262908, 39.064003));
   TRY_TESTME(points[i++] == Point2d(-17.411634, 38.381018));
   TRY_TESTME(points[i++] == Point2d(-17.506906, 37.688550));
   TRY_TESTME(points[i++] == Point2d(-17.548151, 36.990777));
   TRY_TESTME(points[i++] == Point2d(-17.535119, 36.291907));
   TRY_TESTME(points[i++] == Point2d(-17.467889, 35.596157));
   TRY_TESTME(points[i++] == Point2d(-17.346867, 34.907722));
   TRY_TESTME(points[i++] == Point2d(-17.172782, 34.230756));
   TRY_TESTME(points[i++] == Point2d(-16.946685, 33.569342));
   TRY_TESTME(points[i++] == Point2d(-16.669940, 32.927470));
   TRY_TESTME(points[i++] == Point2d(-16.344215, 32.309011));
   TRY_TESTME(points[i++] == Point2d(-7.470513, 16.939308));
   TRY_TESTME(points[i++] == Point2d(-7.084740, 16.315916));
   TRY_TESTME(points[i++] == Point2d(-6.661621, 15.717245));
   TRY_TESTME(points[i++] == Point2d(-6.202735, 15.145528));
   TRY_TESTME(points[i++] == Point2d(-5.709794, 14.602898));
   TRY_TESTME(points[i++] == Point2d(-5.184638, 14.091382));
   TRY_TESTME(points[i++] == Point2d(-4.629228, 13.612888));
   TRY_TESTME(points[i++] == Point2d(-4.045635, 13.169202));
   TRY_TESTME(points[i++] == Point2d(-3.436039, 12.761981));
   TRY_TESTME(points[i++] == Point2d(-2.802714, 12.392743));
   TRY_TESTME(points[i++] == Point2d(-2.148024, 12.062867));
   TRY_TESTME(points[i++] == Point2d(-1.474412, 11.773584));
   TRY_TESTME(points[i++] == Point2d(-0.784393, 11.525974));
   TRY_TESTME(points[i++] == Point2d(-0.080541, 11.320960));
   TRY_TESTME(points[i++] == Point2d(0.634515, 11.159309));
   TRY_TESTME(points[i++] == Point2d(1.358109, 11.041623));
   TRY_TESTME(points[i++] == Point2d(2.087538, 10.968342));
   TRY_TESTME(points[i++] == Point2d(2.820081, 10.939739));
   TRY_TESTME(points[i++] == Point2d(3.553003, 10.955920));
   TRY_TESTME(points[i++] == Point2d(4.283570, 11.016826));
   TRY_TESTME(points[i++] == Point2d(5.009055, 11.122230));
   TRY_TESTME(points[i++] == Point2d(13.362362, 12.597683));
   TRY_TESTME(points[i++] == Point2d(13.483276, 12.615250));
   TRY_TESTME(points[i++] == Point2d(13.605037, 12.625401));
   TRY_TESTME(points[i++] == Point2d(13.727191, 12.628098));
   TRY_TESTME(points[i++] == Point2d(13.849281, 12.623331));
   TRY_TESTME(points[i++] == Point2d(13.970853, 12.611117));
   TRY_TESTME(points[i++] == Point2d(14.091452, 12.591503));
   TRY_TESTME(points[i++] == Point2d(14.210628, 12.564561));
   TRY_TESTME(points[i++] == Point2d(14.327936, 12.530392));
   TRY_TESTME(points[i++] == Point2d(14.442940, 12.489124));
   TRY_TESTME(points[i++] == Point2d(14.555208, 12.440910));
   TRY_TESTME(points[i++] == Point2d(14.664323, 12.385930));
   TRY_TESTME(points[i++] == Point2d(14.769877, 12.324391));
   TRY_TESTME(points[i++] == Point2d(14.871477, 12.256521));
   TRY_TESTME(points[i++] == Point2d(14.968742, 12.182573));
   TRY_TESTME(points[i++] == Point2d(15.061311, 12.102824));
   TRY_TESTME(points[i++] == Point2d(15.148837, 12.017571));
   TRY_TESTME(points[i++] == Point2d(15.230993, 11.927133));
   TRY_TESTME(points[i++] == Point2d(15.307474, 11.831847));
   TRY_TESTME(points[i++] == Point2d(15.377994, 11.732068));
   TRY_TESTME(points[i++] == Point2d(15.442290, 11.628170));
   TRY_TESTME(points[i++] == Point2d(16.116862, 10.459775));
   TRY_TESTME(points[i++] == Point2d(15.750837, 9.093750));
   TRY_TESTME(points[i++] == Point2d(0.000000, 0.000000));
   TRY_TESTME(i == points.size());

   //std::cout.setf(std::ios::fixed);
   //for (auto& point : points)
   //{
   //   std::cout << "TRY_TESTME(points[i++] == Point2d(" << std::setprecision(6) << point.X() << ", " << std::setprecision(6) << point.Y() << "));" << std::endl;
   //}

   TESTME_EPILOG("PCIDeckedIBeam");
}

#endif // _UNITTEST



