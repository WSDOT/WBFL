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
#include <GeomModel/NUDeckedIBeam.h>
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

NUDeckedIBeam::NUDeckedIBeam() :
   FlangedBeam()
{
}

NUDeckedIBeam::NUDeckedIBeam(Float64 w1, Float64 w2, Float64 w3, Float64 w4, Float64 h, Float64 d1, Float64 d2, Float64 d3, Float64 d4, Float64 d5, Float64 d6, Float64 t, Float64 r1, Float64 r2, Float64 c1, std::shared_ptr<Point2d>& hookPnt) :
   FlangedBeam(hookPnt), m_W1(w1),m_W2(w2), m_W3(w3), m_W4(w4), m_H(h), m_D1(d1), m_D2(d2), m_D3(d3), m_D4(d4), m_D5(d5), m_D6(d6), m_T(t), m_R1(r1), m_R2(r2), m_C1(c1)
{
}

NUDeckedIBeam::~NUDeckedIBeam()
{
}

void NUDeckedIBeam::SetW1(Float64 w1)
{
   m_W1 = w1;
   SetDirtyFlag();
}

Float64 NUDeckedIBeam::GetW1() const
{
   return m_W1;
}

void NUDeckedIBeam::SetW2(Float64 w2)
{
   m_W2 = w2;
   SetDirtyFlag();
}

Float64 NUDeckedIBeam::GetW2() const
{
   return m_W2;
}

void NUDeckedIBeam::SetW3(Float64 w3)
{
   m_W3 = w3;
   SetDirtyFlag();
}

Float64 NUDeckedIBeam::GetW3() const
{
   return m_W3;
}

void NUDeckedIBeam::SetW4(Float64 w4)
{
   m_W4 = w4;
   SetDirtyFlag();
}

Float64 NUDeckedIBeam::GetW4() const
{
   return m_W4;
}

void NUDeckedIBeam::SetH(Float64 h)
{
   m_H = h;
   SetDirtyFlag();
}

Float64 NUDeckedIBeam::GetH() const
{
   return m_H;
}

void NUDeckedIBeam::SetD1(Float64 d1)
{
   m_D1 = d1;
   SetDirtyFlag();
}

Float64 NUDeckedIBeam::GetD1() const
{
   return m_D1;
}

void NUDeckedIBeam::SetD2(Float64 d2)
{
   m_D2 = d2;
   SetDirtyFlag();
}

Float64 NUDeckedIBeam::GetD2() const
{
   return m_D2;
}

void NUDeckedIBeam::SetD3(Float64 d3)
{
   m_D3 = d3;
   SetDirtyFlag();
}

Float64 NUDeckedIBeam::GetD3() const
{
   return m_D3;
}

void NUDeckedIBeam::SetD4(Float64 d4)
{
   m_D4 = d4;
   SetDirtyFlag();
}

Float64 NUDeckedIBeam::GetD4() const
{
   return m_D4;
}

void NUDeckedIBeam::SetD5(Float64 d5)
{
   m_D5 = d5;
   SetDirtyFlag();
}

Float64 NUDeckedIBeam::GetD5() const
{
   return m_D5;
}

void NUDeckedIBeam::SetD6(Float64 d6)
{
   m_D6 = d6;
   SetDirtyFlag();
}

Float64 NUDeckedIBeam::GetD6() const
{
   return m_D6;
}

void NUDeckedIBeam::SetT(Float64 t)
{
   m_T = t;
   SetDirtyFlag();
}

Float64 NUDeckedIBeam::GetT() const
{
   return m_T;
}

void NUDeckedIBeam::SetR1(Float64 r1)
{
   m_R1 = r1;
   SetDirtyFlag();
}

Float64 NUDeckedIBeam::GetR1() const
{
   return m_R1;
}

void NUDeckedIBeam::SetR2(Float64 r2)
{
   m_R2 = r2;
   SetDirtyFlag();
}

Float64 NUDeckedIBeam::GetR2() const
{
   return m_R2;
}

void NUDeckedIBeam::SetC1(Float64 c1)
{
   m_C1 = c1;
   SetDirtyFlag();
}

Float64 NUDeckedIBeam::GetC1() const
{
   return m_C1;
}

void NUDeckedIBeam::GetTopFlangePoints(Point2d* pntLeftTop, Point2d* pntLeftBottom, Point2d* pntTopCL, Point2d* pntTopCentral, Point2d* pntRightTop, Point2d* pntRightBottom) const
{
   auto& polygon = GetPolygon();
   *pntLeftBottom = polygon->GetPoint(m_LeftBottomIdx);
   *pntLeftTop = polygon->GetPoint(m_LeftTopIdx);
   *pntRightTop = polygon->GetPoint(m_RightTopIdx);
   *pntRightBottom = polygon->GetPoint(m_RightBottomIdx);

   *pntTopCentral = (*pntLeftTop + *pntRightTop) / 2;
   *pntTopCL = *pntTopCentral;
}

void NUDeckedIBeam::GetBottomFlangePoints(Point2d* pntLeftTop, Point2d* pntLeftBottom, Point2d* pntRightTop, Point2d* pntRightBottom) const
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

void NUDeckedIBeam::GetTopFlangeThickness(Float64* pHl, Float64* pHc, Float64* pHr) const
{
   *pHl = m_D1;
   *pHc = m_D1;
   *pHr = m_D1;
}

Float64 NUDeckedIBeam::GetHeight() const
{
   return GetH();
}

IndexType NUDeckedIBeam::GetTopFlangeCount() const
{
   return 1;
}

Float64 NUDeckedIBeam::GetTopFlangeLocation(IndexType flangeIdx) const
{
   if (0 < flangeIdx) THROW_GEOMETRY(_T("NUDeckedIBeam::GetTopFlangeLocation - invalid index"));
   return 0.0;
}

Float64 NUDeckedIBeam::GetTopFlangeWidth(IndexType flangeIdx) const
{
   if (0 < flangeIdx) THROW_GEOMETRY(_T("NUDeckedIBeam::GetTopFlangeWidth - invalid index"));
   return GetTopWidth();
}

IndexType NUDeckedIBeam::GetBottomFlangeCount() const
{
   return 1;
}

Float64 NUDeckedIBeam::GetBottomFlangeLocation(IndexType flangeIdx) const
{
   if (0 < flangeIdx) THROW_GEOMETRY(_T("NUDeckedIBeam::GetBottomFlangeLocation - invalid index"));
   return 0.0;
}

Float64 NUDeckedIBeam::GetBottomFlangeWidth(IndexType flangeIdx) const
{
   if (0 < flangeIdx) THROW_GEOMETRY(_T("NUDeckedIBeam::GetBottomFlangeWidth - invalid index"));
   return GetBottomWidth();
}

Float64 NUDeckedIBeam::GetTopWidth() const
{
   return  m_W1 + 2 * (m_W2 + m_W3);
}

Float64 NUDeckedIBeam::GetBottomWidth() const
{
   return m_W4;
}

Float64 NUDeckedIBeam::GetAvgWebWidth() const
{
   return GetMinWebWidth();
}

Float64 NUDeckedIBeam::GetShearWidth() const
{
   return GetAvgWebWidth();
}

Float64 NUDeckedIBeam::GetMinWebWidth() const
{
   return m_T;
}

Float64 NUDeckedIBeam::GetMinBottomFlangeThickness() const
{
   return m_D6;
}

Float64 NUDeckedIBeam::GetMinTopFlangeThickness() const
{
   return m_D1;
}

MatingSurfaceIndexType NUDeckedIBeam::GetMatingSurfaceCount() const
{
   return 1;
}

Float64 NUDeckedIBeam::GetMatingSurfaceWidth(MatingSurfaceIndexType idx) const
{
   if (0 < idx) THROW_GEOMETRY(_T("NUDeckedIBeam::GetMatingSurfaceWidth - index out of range"));
   return GetTopWidth();
}

Float64 NUDeckedIBeam::GetMatingSurfaceLocation(MatingSurfaceIndexType idx) const
{
   if (0 < idx) THROW_GEOMETRY(_T("NUDeckedIBeam::GetMatingSurfaceLocation - index out of range"));
   return 0;
}

IndexType NUDeckedIBeam::GetWebCount() const
{
   return 1;
}

Plane3d NUDeckedIBeam::GetWebPlane(WebIndexType webIdx) const
{
   if (0 < webIdx) THROW_GEOMETRY(_T("NUDeckedIBeam::GetWebPlane - index out of range"));
   return Plane3d(0, 0, -1, 0); // vertical plane
}

void NUDeckedIBeam::DoOffset(const Size2d& delta)
{
   GetHookPoint()->Offset(delta);
   SetDirtyFlag();
}

void NUDeckedIBeam::DoRotate(const Point2d& center, Float64 angle)
{
   m_Rotation += angle;
   GetHookPoint()->Rotate(center, angle);
   SetDirtyFlag();
}

std::unique_ptr<Shape> NUDeckedIBeam::CreateClone() const
{
   return std::make_unique<NUDeckedIBeam>(*this);
}

#if defined _DEBUG
bool NUDeckedIBeam::AssertValid() const
{
   return __super::AssertValid();
}

void NUDeckedIBeam::Dump(WBFL::Debug::LogContext& os) const
{
   os << _T("*** Dump for NUDeckedIBeam ***")<< WBFL::Debug::endl;
   __super::Dump( os );
}
#endif // _DEBUG

void NUDeckedIBeam::OnUpdatePolygon(std::unique_ptr<Polygon>& polygon) const
{
   // Generate points along the left-hand side of the shape... 
   // then we will copy and mirror them about the Y axis
   std::vector<Point2d> vPoints;

   const long nSpaces = 20; // number of spaces used to approximate the curved fillets
   Float64 cx, cy;           // center of arc
   Float64 delta;            // sweep angle of arc
   Float64 startAngle;       // start angle for generating points along arc

   // Start at the bottom center of the shape and work clockwise up to the top center
   vPoints.emplace_back(0, 0);

   if  ( IsZero(m_C1) )
   {
      vPoints.emplace_back(-m_W4/2,0.0);
   }
   else
   {
      vPoints.emplace_back(-m_W4/2+m_C1,0.0);
      vPoints.emplace_back(-m_W4/2,m_C1);
   }

   // top of bottom flange
   vPoints.emplace_back( -m_W4 / 2, m_D6);

   // compute angle of bottom flange (measured from vertical)
   delta = atan2( (m_W4-m_T)/2, m_D5-m_D6 );

   // generate bottom left flange-web fillet
   cx = -m_T/2 - m_R2;
   cy = m_D5 + m_R2*tan(delta/2);
   startAngle = TWO_PI - delta;

   GenerateFillet(vPoints,cx,cy,m_R2,startAngle, delta,nSpaces);

   // compute angle of top flange (measured from vertical)
   delta = atan2( m_W1/2 + m_W2 + m_W4, m_D4-m_D1 );

   // generate top left flange-web fillet
   cx = -m_T/2 - m_R1;
   cy = m_H - m_D3 - m_R1*tan(delta/2);
   startAngle = 0.0;

   GenerateFillet(vPoints,cx,cy,m_R1,startAngle, delta,nSpaces);

   // bottom of top flange
   vPoints.emplace_back( -m_W1 / 2, m_H - m_D4);
   vPoints.emplace_back( -m_W1 / 2 - m_W2, m_H - m_D1);
   vPoints.emplace_back(-m_W1/2 - m_W2 - m_W3,m_H);

   vPoints.emplace_back(0, m_H); // top center

   // get indicies of key top flange points
   IndexType nPoints = vPoints.size();
   m_LeftBottomIdx = nPoints - 3;
   m_LeftTopIdx = nPoints - 2;
   m_RightBottomIdx = nPoints;
   m_RightTopIdx = nPoints + 1;

   // add left hand points into the collection
   polygon->AddPoints(vPoints);

   polygon->SetSymmetry(Polygon::Symmetry::Y);

   if (!IsZero(m_Rotation))
      polygon->Rotate(Point2d(0, 0), m_Rotation);

   polygon->Move(Point2d(0, 0), *GetHookPoint());
}

#if defined _UNITTEST
#include <GeomModel/UnitTest.h>
bool NUDeckedIBeam::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("NUDeckedIBeam");

   NUDeckedIBeam beam;

   // Use some real dimensions
   beam.SetW1(26);
   beam.SetW2(49);
   beam.SetW3(1);
   beam.SetW4(38);
   beam.SetD1(2);
   beam.SetD2(6);
   beam.SetD3(9);
   beam.SetD4(3);
   beam.SetD5(13);
   beam.SetD6(5);
   beam.SetH(108);
   beam.SetT(4);
   beam.SetR1(10);
   beam.SetR2(22.5);
   beam.SetC1(1.0);

   //
   // Bounding Box
   //
   Rect2d box = beam.GetBoundingBox();
   TRY_TESTME(IsEqual(box.Left(), -63.0));
   TRY_TESTME(IsEqual(box.Right(), 63.0));
   TRY_TESTME(IsEqual(box.Top(), 108.0));
   TRY_TESTME(IsEqual(box.Bottom(), 0.00));

   //
   // ShapeProperties
   //
   ShapeProperties props = beam.GetProperties();
   TRY_TESTME(IsEqual(props.GetArea(), 1286.6976042586434));
   TRY_TESTME(IsEqual(props.GetIxx(), 2471035.0754711358));
   TRY_TESTME(IsEqual(props.GetIyy(), 419404.68570325995));
   TRY_TESTME(IsEqual(props.GetIxy(), 0.0, 0.0005));
   TRY_TESTME(IsEqual(props.GetCentroid().X(), 0.0));
   TRY_TESTME(IsEqual(props.GetCentroid().Y(), 59.057149336875156));
   TRY_TESTME(props.GetCoordinateSystem() == ShapeProperties::CoordSystemType::Centroidal);

   TRY_TESTME(IsEqual(props.GetXleft(), 63.0));
   TRY_TESTME(IsEqual(props.GetXright(), 63.0));
   TRY_TESTME(IsEqual(props.GetYtop(), 108.0 - props.GetCentroid().Y()));
   TRY_TESTME(IsEqual(props.GetYbottom(), props.GetCentroid().Y()));

   //
   // Perimeter
   //
   TRY_TESTME(IsEqual(beam.GetPerimeter(), 502.08150632310787));

   //
   // FurthestDistance
   //

   // Shape on right
   Point2d p1(0, 20);
   Point2d p2(100, 20);
   Line2d line(p1, p2);
   TRY_TESTME(IsEqual(beam.GetFurthestDistance(line, Line2d::Side::Right), 20.0));

   // shape on left
   p1.Move(0, -20);
   p2.Move(100, -20);
   line.ThroughPoints(p1, p2);
   TRY_TESTME(IsEqual(beam.GetFurthestDistance(line, Line2d::Side::Right), -20.0));

   // 
   // PolyPoints
   //
   auto points = beam.GetPolyPoints();
   TRY_TESTME(points.size() == 99);

   int i = 0;
   TRY_TESTME(points[i++] == Point2d(  0.000000, 0.000000));
   TRY_TESTME(points[i++] == Point2d(-18.000000, 0.000000));
   TRY_TESTME(points[i++] == Point2d(-19.000000, 1.000000));
   TRY_TESTME(points[i++] == Point2d(-19.000000, 5.000000));
   TRY_TESTME(points[i++] == Point2d(-14.919567, 6.920204));
   TRY_TESTME(points[i++] == Point2d(-13.784272, 7.494207));
   TRY_TESTME(points[i++] == Point2d(-12.683233, 8.131457));
   TRY_TESTME(points[i++] == Point2d(-11.619970, 8.829917));
   TRY_TESTME(points[i++] == Point2d(-10.597881, 9.587353));
   TRY_TESTME(points[i++] == Point2d(-9.620235, 10.401345));
   TRY_TESTME(points[i++] == Point2d(-8.690156, 11.269289));
   TRY_TESTME(points[i++] == Point2d(-7.810618, 12.188412));
   TRY_TESTME(points[i++] == Point2d(-6.984432, 13.155775));
   TRY_TESTME(points[i++] == Point2d(-6.214240, 14.168286));
   TRY_TESTME(points[i++] == Point2d(-5.502503, 15.222708));
   TRY_TESTME(points[i++] == Point2d(-4.851498, 16.315670));
   TRY_TESTME(points[i++] == Point2d(-4.263305, 17.443679));
   TRY_TESTME(points[i++] == Point2d(-3.739804, 18.603127));
   TRY_TESTME(points[i++] == Point2d(-3.282669, 19.790310));
   TRY_TESTME(points[i++] == Point2d(-2.893361, 21.001431));
   TRY_TESTME(points[i++] == Point2d(-2.573126, 22.232619));
   TRY_TESTME(points[i++] == Point2d(-2.322985, 23.479937));
   TRY_TESTME(points[i++] == Point2d(-2.143741, 24.739400));
   TRY_TESTME(points[i++] == Point2d(-2.035964, 26.006980));
   TRY_TESTME(points[i++] == Point2d(-2.000000, 27.278625));
   TRY_TESTME(points[i++] == Point2d(-2.000000, 89.099500));
   TRY_TESTME(points[i++] == Point2d(-2.030436, 89.879106));
   TRY_TESTME(points[i++] == Point2d(-2.121557, 90.653967));
   TRY_TESTME(points[i++] == Point2d(-2.272810, 91.419366));
   TRY_TESTME(points[i++] == Point2d(-2.483274, 92.170643));
   TRY_TESTME(points[i++] == Point2d(-2.751667, 92.903226));
   TRY_TESTME(points[i++] == Point2d(-3.076356, 93.612655));
   TRY_TESTME(points[i++] == Point2d(-3.455364, 94.294612));
   TRY_TESTME(points[i++] == Point2d(-3.886384, 94.944946));
   TRY_TESTME(points[i++] == Point2d(-4.366793, 95.559698));
   TRY_TESTME(points[i++] == Point2d(-4.893667, 96.135125));
   TRY_TESTME(points[i++] == Point2d(-5.463797, 96.667726));
   TRY_TESTME(points[i++] == Point2d(-6.073714, 97.154259));
   TRY_TESTME(points[i++] == Point2d(-6.719705, 97.591761));
   TRY_TESTME(points[i++] == Point2d(-7.397838, 97.977569));
   TRY_TESTME(points[i++] == Point2d(-8.103985, 98.309335));
   TRY_TESTME(points[i++] == Point2d(-8.833848, 98.585041));
   TRY_TESTME(points[i++] == Point2d(-9.582983, 98.803006));
   TRY_TESTME(points[i++] == Point2d(-10.346831, 98.961905));
   TRY_TESTME(points[i++] == Point2d(-11.120742, 99.060770));
   TRY_TESTME(points[i++] == Point2d(-11.900005, 99.099000));
   TRY_TESTME(points[i++] == Point2d(-13.000000, 105.000000));
   TRY_TESTME(points[i++] == Point2d(-62.000000, 106.000000));
   TRY_TESTME(points[i++] == Point2d(-63.000000, 108.000000));
   TRY_TESTME(points[i++] == Point2d(0.000000, 108.000000));
   TRY_TESTME(points[i++] == Point2d(63.000000, 108.000000));
   TRY_TESTME(points[i++] == Point2d(62.000000, 106.000000));
   TRY_TESTME(points[i++] == Point2d(13.000000, 105.000000));
   TRY_TESTME(points[i++] == Point2d(11.900005, 99.099000));
   TRY_TESTME(points[i++] == Point2d(11.120742, 99.060770));
   TRY_TESTME(points[i++] == Point2d(10.346831, 98.961905));
   TRY_TESTME(points[i++] == Point2d(9.582983, 98.803006));
   TRY_TESTME(points[i++] == Point2d(8.833848, 98.585041));
   TRY_TESTME(points[i++] == Point2d(8.103985, 98.309335));
   TRY_TESTME(points[i++] == Point2d(7.397838, 97.977569));
   TRY_TESTME(points[i++] == Point2d(6.719705, 97.591761));
   TRY_TESTME(points[i++] == Point2d(6.073714, 97.154259));
   TRY_TESTME(points[i++] == Point2d(5.463797, 96.667726));
   TRY_TESTME(points[i++] == Point2d(4.893667, 96.135125));
   TRY_TESTME(points[i++] == Point2d(4.366793, 95.559698));
   TRY_TESTME(points[i++] == Point2d(3.886384, 94.944946));
   TRY_TESTME(points[i++] == Point2d(3.455364, 94.294612));
   TRY_TESTME(points[i++] == Point2d(3.076356, 93.612655));
   TRY_TESTME(points[i++] == Point2d(2.751667, 92.903226));
   TRY_TESTME(points[i++] == Point2d(2.483274, 92.170643));
   TRY_TESTME(points[i++] == Point2d(2.272810, 91.419366));
   TRY_TESTME(points[i++] == Point2d(2.121557, 90.653967));
   TRY_TESTME(points[i++] == Point2d(2.030436, 89.879106));
   TRY_TESTME(points[i++] == Point2d(2.000000, 89.099500));
   TRY_TESTME(points[i++] == Point2d(2.000000, 27.278625));
   TRY_TESTME(points[i++] == Point2d(2.035964, 26.006980));
   TRY_TESTME(points[i++] == Point2d(2.143741, 24.739400));
   TRY_TESTME(points[i++] == Point2d(2.322985, 23.479937));
   TRY_TESTME(points[i++] == Point2d(2.573126, 22.232619));
   TRY_TESTME(points[i++] == Point2d(2.893361, 21.001431));
   TRY_TESTME(points[i++] == Point2d(3.282669, 19.790310));
   TRY_TESTME(points[i++] == Point2d(3.739804, 18.603127));
   TRY_TESTME(points[i++] == Point2d(4.263305, 17.443679));
   TRY_TESTME(points[i++] == Point2d(4.851498, 16.315670));
   TRY_TESTME(points[i++] == Point2d(5.502503, 15.222708));
   TRY_TESTME(points[i++] == Point2d(6.214240, 14.168286));
   TRY_TESTME(points[i++] == Point2d(6.984432, 13.155775));
   TRY_TESTME(points[i++] == Point2d(7.810618, 12.188412));
   TRY_TESTME(points[i++] == Point2d(8.690156, 11.269289));
   TRY_TESTME(points[i++] == Point2d(9.620235, 10.401345));
   TRY_TESTME(points[i++] == Point2d(10.597881, 9.587353));
   TRY_TESTME(points[i++] == Point2d(11.619970, 8.829917));
   TRY_TESTME(points[i++] == Point2d(12.683233, 8.131457));
   TRY_TESTME(points[i++] == Point2d(13.784272, 7.494207));
   TRY_TESTME(points[i++] == Point2d(14.919567, 6.920204));
   TRY_TESTME(points[i++] == Point2d(19.000000, 5.000000));
   TRY_TESTME(points[i++] == Point2d(19.000000, 1.000000));
   TRY_TESTME(points[i++] == Point2d(18.000000, 0.000000));
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

   // Test properties
   TRY_TESTME(IsEqual(beam.GetHeight(), 108.));
   TRY_TESTME(IsEqual(beam.GetTopFlangeWidth(0), 126.));
   TRY_TESTME(IsEqual(beam.GetBottomFlangeWidth(0), 38.0));
   TRY_TESTME(IsEqual(beam.GetAvgWebWidth(), 4.));

   // Test hook point behavior
   TRY_TESTME(UnitTest::TestHookPoint(beam) == true);

   TESTME_EPILOG("NUDeckedIBeam");
}

#endif // _UNITTEST



