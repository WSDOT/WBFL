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
#include <GeomModel/NUBeam.h>
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

NUBeam::NUBeam() : FlangedBeam()
{
}

NUBeam::NUBeam(Float64 w1, Float64 w2, 
                   Float64 d1, Float64 d2, Float64 d3, Float64 d4, Float64 d5,
                   Float64 t, 
                   Float64 r1, Float64 r2, Float64 r3, Float64 r4,Float64 c1,Float64 endBlockWidth,
    std::shared_ptr<Point2d>& hookPnt) : FlangedBeam(hookPnt)

{
   m_W1 = w1;
   m_W2 = w2;
   m_D1 = d1;
   m_D2 = d2;
   m_D3 = d3;
   m_D4 = d4;
   m_D5 = d5;
   m_T  = t;
   m_R1 = r1;
   m_R2 = r2;
   m_R3 = r3;
   m_R4 = r4;
   m_C1 = c1;
   m_EndBlockWidth = endBlockWidth;
}

NUBeam::~NUBeam()
{
}

void NUBeam::SetW1(Float64 w1)
{
   PRECONDITION(w1>=0);
   m_W1 = w1;
   SetDirtyFlag();
}

Float64 NUBeam::GetW1() const
{
   return m_W1;
}

void NUBeam::SetW2(Float64 w2)
{
   PRECONDITION(w2>=0);
   m_W2 = w2;
   SetDirtyFlag();
}

Float64 NUBeam::GetW2() const
{
   return m_W2;
}

void NUBeam::SetD1(Float64 d1)
{
   PRECONDITION(d1>=0);
   m_D1 = d1;
   SetDirtyFlag();
}

Float64 NUBeam::GetD1() const
{
   return m_D1;
}

void NUBeam::SetD2(Float64 d2)
{
   PRECONDITION(d2>=0);
   m_D2 = d2;
   SetDirtyFlag();
}

Float64 NUBeam::GetD2() const
{
   return m_D2;
}

void NUBeam::SetD3(Float64 d3)
{
   PRECONDITION(d3>=0);
   m_D3 = d3;
   SetDirtyFlag();
}

Float64 NUBeam::GetD3() const
{
   return m_D3;
}

void NUBeam::SetD4(Float64 d4)
{
   PRECONDITION(d4>=0);
   m_D4 = d4;
   SetDirtyFlag();
}

Float64 NUBeam::GetD4() const
{
   return m_D4;
}

void NUBeam::SetD5(Float64 d5)
{
   PRECONDITION(d5>=0);
   m_D5 = d5;
   SetDirtyFlag();
}

Float64 NUBeam::GetD5() const
{
   return m_D5;
}

void NUBeam::SetT(Float64 t)
{
   PRECONDITION(t>=0);
   m_T = t;
   SetDirtyFlag();
}

Float64 NUBeam::GetT() const
{
   return m_T;
}

void NUBeam::SetR1(Float64 r1)
{
   PRECONDITION(r1>=0);
   m_R1 = r1;
   SetDirtyFlag();
}

Float64 NUBeam::GetR1() const
{
   return m_R1;
}

void NUBeam::SetR2(Float64 r2)
{
   PRECONDITION(r2>=0);
   m_R2 = r2;
   SetDirtyFlag();
}

Float64 NUBeam::GetR2() const
{
   return m_R2;
}

void NUBeam::SetR3(Float64 r3)
{
   PRECONDITION(r3>=0);
   m_R3 = r3;
   SetDirtyFlag();
}

Float64 NUBeam::GetR3() const
{
   return m_R3;
}

void NUBeam::SetR4(Float64 r4)
{
   PRECONDITION(r4>=0);
   m_R4 = r4;
   SetDirtyFlag();
}

Float64 NUBeam::GetR4() const
{
   return m_R4;
}

void NUBeam::SetC1(Float64 c1)
{
   PRECONDITION(0 <= c1);
   m_C1 = c1;
   SetDirtyFlag();
}

Float64 NUBeam::GetC1() const
{
   return m_C1;
}

void NUBeam::SetEndBlockWidth(Float64 endBlockWidth)
{
   PRECONDITION(0 <= endBlockWidth);
   m_EndBlockWidth = endBlockWidth;
   SetDirtyFlag();
}

Float64 NUBeam::GetEndBlockWidth() const
{
   return m_EndBlockWidth;
}

Float64 NUBeam::GetHeight() const
{
   return m_D1 + m_D2 + m_D3 + m_D4 + m_D5;
}

void NUBeam::DoOffset(const Size2d& delta)
{
   GetHookPoint()->Offset(delta);
   SetDirtyFlag();
}

void NUBeam::DoRotate(const Point2d& center, Float64 angle)
{
   m_Rotation += angle;
   GetHookPoint()->Rotate(center, angle);
   SetDirtyFlag();
}

IndexType NUBeam::GetTopFlangeCount() const
{
   return 1;
}

Float64 NUBeam::GetTopFlangeLocation(IndexType flangeIdx) const
{
   if (0 < flangeIdx) throw std::invalid_argument("NUBeam::GetTopFlangeLocation - invalid flange index");
   return 0.0;
}

Float64 NUBeam::GetTopFlangeWidth(IndexType flangeIdx) const
{
   if (0 < flangeIdx) throw std::invalid_argument("NUBeam::GetTopFlangeWidth - invalid flange index");
   return m_W1;
}

IndexType NUBeam::GetBottomFlangeCount() const
{
   return 1;
}

Float64 NUBeam::GetBottomFlangeLocation(IndexType flangeIdx) const
{
   if (0 < flangeIdx) throw std::invalid_argument("NUBeam::GetBottomFlangeLocation - invalid flange index");
   return 0.0;
}

Float64 NUBeam::GetBottomFlangeWidth(IndexType flangeIdx) const
{
   if (0 < flangeIdx) throw std::invalid_argument("NUBeam::GetBottomFlangeWidth - invalid flange index");
   return GetBottomWidth();
}

Float64 NUBeam::GetTopWidth() const
{
   return m_W1;
}

Float64 NUBeam::GetBottomWidth() const
{
   return m_W2;
}

MatingSurfaceIndexType NUBeam::GetMatingSurfaceCount() const
{
   return 1;
}

Float64 NUBeam::GetMatingSurfaceWidth(MatingSurfaceIndexType webIdx) const
{
   if (0 < webIdx) throw std::invalid_argument("NUBeam::GetMatingSurfaceWidth - index out of range");
   return GetTopWidth();
}

Float64 NUBeam::GetMatingSurfaceLocation(MatingSurfaceIndexType webIdx) const
{
   if (0 < webIdx) throw std::invalid_argument("NUBeam::GetMatingSurfaceLocation - index out of range");
   return 0;
}

IndexType NUBeam::GetWebCount() const
{
   return 1;
}

Plane3d NUBeam::GetWebPlane(WebIndexType webIdx) const
{
   if (0 < webIdx) throw std::invalid_argument("NUBeam::GetWebPlane - index out of range");
   return Plane3d(0, 0, -1, 0); // vertical plane
}

Float64 NUBeam::GetShearWidth() const
{
   return GetMinWebWidth();
}

Float64 NUBeam::GetAvgWebWidth() const
{
   Float64 avg_web_width;
   // if m_EndBlock is zero, it isn't used
   // if m_EndBlock != m_T then we are in an end block region
   // m_EndBlock should = m_T if we are not in an end block region
   if (!IsZero(m_EndBlockWidth) && !IsEqual(m_EndBlockWidth, m_T))
   {
      avg_web_width = m_EndBlockWidth;
   }
   else
   {
      avg_web_width = m_T;
   }

   return avg_web_width;
}

Float64 NUBeam::GetMinWebWidth() const
{
   return m_T;
}

Float64 NUBeam::GetMinBottomFlangeThickness() const
{
   return m_D5;
}

Float64 NUBeam::GetMinTopFlangeThickness() const
{
   return m_D1;
}

std::unique_ptr<Shape> NUBeam::CreateClone() const
{
   return std::make_unique<NUBeam>(*this);
}

#if defined _DEBUG
bool NUBeam::AssertValid() const
{
//   if ( m_W1<0 || m_W2<0 || m_W3<0 || m_W4<0 || m_D1<0 )return false;
//   if ( m_D2<0 || m_D3<0 || m_D4<0 || m_D5<0 || m_D6<0 )return false;
//   if ( m_D7<0 || m_T1<0 || m_T2<0) return false;

   return ShapeImpl::AssertValid();
}

void NUBeam::Dump(dbgDumpContext& os) const
{
   os << _T("*** Dump for NUBeam ***") <<endl;
//   gmShapeImp::Dump( os );
//   os << "  Hook Point      = ("<<GetHookPoint()->X()<<", "<<GetHookPoint()->Y()<<")"<<endl;
//   os << "  Rotation        =  "<<m_Rotation<<endl;
//   os << "  D1              =  "<<m_D1 <<endl;
//   os << "  D2              =  "<<m_D2 <<endl;
//   os << "  D3              =  "<<m_D3 <<endl;
//   os << "  D4              =  "<<m_D4 <<endl;
//   os << "  D5              =  "<<m_D5 <<endl;
//   os << "  D6              =  "<<m_D6 <<endl;
//   os << "  D7              =  "<<m_D7 <<endl;
//   os << "  W1              =  "<<m_W1 <<endl;
//   os << "  W2              =  "<<m_W2 <<endl;
//   os << "  W3              =  "<<m_W3 <<endl;
//   os << "  W4              =  "<<m_W4 <<endl;
//   os << "  T1              =  "<<m_T1 <<endl;
//   os << "  T2              =  "<<m_T2 <<endl;
//   os << "Polygon rep of beam" << endl;
//   m_PolyImp.Dump( os );
}
#endif // _DEBUG

void NUBeam::OnUpdatePolygon(std::unique_ptr<Polygon>& polygon) const
{
   std::vector<Point2d> vPoints;
   const long nSpaces = 20; // number of spaces used to approximate the curved fillets
   Float64 cx, cy;           // center of arc
   Float64 delta;            // sweep angle of arc
   Float64 startAngle;       // start angle for generating points along arc

   // Start at the bottom center of the shape and work clockwise to the top center
   vPoints.emplace_back(0, 0); // bottom center
   if (IsZero(m_C1))
   {
      vPoints.emplace_back(-m_W2 / 2, 0.0);
   }
   else
   {
      vPoints.emplace_back( -m_W2 / 2 + m_C1, 0.0);
      vPoints.emplace_back( -m_W2 / 2, m_C1);
   }

   // compute angle of bottom flange (measured from vertical)
   delta = atan2((m_W2 - m_T) / 2, m_D4);

   // generate lower left fillet
   cx = -m_W2 / 2 + m_R4;
   cy = m_D5 - m_R4 * tan(delta / 2);
   startAngle = M_PI;
   GenerateFillet(vPoints, cx, cy, m_R4, startAngle, -delta, nSpaces);

   // generate bottom left flange-web fillet
   if (::IsLE(m_R2 * (1 - cos(delta)), (m_EndBlockWidth - m_T) / 2))
   {
      // the end block is wider that the fillet... no fillet
      Float64 x1 = (m_W2 - m_T) / 2;
      Float64 x2 = (m_EndBlockWidth - m_T) / 2;
      Float64 d = x2 * m_D4 / x1;
      cx = -m_EndBlockWidth / 2;
      cy = m_D5 + m_D4 - d;
      GenerateFillet(vPoints, cx, cy, 0.0, startAngle, 0.0, nSpaces);
   }
   else
   {
      cx = -m_T / 2 - m_R2;
      cy = m_D5 + m_D4 + m_R2 * tan(delta / 2);
      startAngle = TWO_PI - delta;

      Float64 deltaFillet = delta;
      if (m_T < m_EndBlockWidth)
      {
         Float64 x = (m_EndBlockWidth - m_T) / 2;
         Float64 theta = acos((m_R2 - x) / m_R2);
         deltaFillet = delta - theta;
      }

      GenerateFillet(vPoints, cx, cy, m_R2, startAngle, deltaFillet, nSpaces);
   }

   // compute angle of top flange (measured from vertical)
   delta = atan2((m_W1 - m_T) / 2, m_D2);

   // generate top left flange-web fillet
   if (::IsLE(m_R1 * (1 - cos(delta)), (m_EndBlockWidth - m_T) / 2))
   {
      // the end block is wider that the fillet... no fillet
      Float64 x1 = (m_W1 - m_T) / 2;
      Float64 x2 = (m_EndBlockWidth - m_T) / 2;
      Float64 d = x2 * m_D2 / x1;
      cx = -m_EndBlockWidth / 2;
      cy = m_D5 + m_D4 + m_D3 + d;
      GenerateFillet(vPoints, cx, cy, 0.0, startAngle, 0.0, nSpaces);
   }
   else
   {
      cx = -m_T / 2 - m_R1;
      cy = m_D5 + m_D4 + m_D3 - m_R1 * tan(delta / 2);
      startAngle = 0.0;

      Float64 deltaFillet = delta;
      if (m_T < m_EndBlockWidth)
      {
         Float64 x = (m_EndBlockWidth - m_T) / 2;
         Float64 theta = acos((m_R1 - x) / m_R1);
         startAngle = theta;
         deltaFillet = delta - theta;
      }

      GenerateFillet(vPoints, cx, cy, m_R1, startAngle, deltaFillet, nSpaces);
   }

   // generate top flange left fillet
   cx = -m_W1 / 2 + m_R3;
   cy = m_D5 + m_D4 + m_D3 + m_D2 + m_R3 * tan(delta / 2);
   startAngle = M_PI + delta;
   GenerateFillet(vPoints, cx, cy, m_R3, startAngle, -delta, nSpaces);

   // extreme points on top flange
   vPoints.emplace_back( -m_W1 / 2, m_D5 + m_D4 + m_D3 + m_D2 + m_D1);

   vPoints.emplace_back(0, m_D5 + m_D4 + m_D3 + m_D2 + m_D1); // top center

   // put the points into the polygon - these are the left half points only
   polygon->SetPoints(vPoints);

   polygon->SetSymmetry(Polygon::Symmetry::Y);

   if (!IsZero(m_Rotation))
      polygon->Rotate(Point2d(0,0), m_Rotation);

   polygon->Move(Point2d(0, 0), *GetHookPoint());
}

#if defined _UNITTEST
#include <GeomModel/UnitTest.h>
bool NUBeam::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("NUBeam");

   // let's try a NU4200
   Float64 t  = 150;
   Float64 w1 = 1225;
   Float64 w2 = 975;
   Float64 d1 = 65;
   Float64 d2 = 45;
   Float64 d3 = 2015;
   Float64 d4 = 140;
   Float64 d5 = 135;
   Float64 r1 = 200;
   Float64 r2 = 200;
   Float64 r3 = 50;
   Float64 r4 = 50;
   Float64 c1 = 0;
   Float64 endBlockWidth = 0;

   NUBeam nu4200(w1,w2,d1,d2,d3,d4,d5,t,r1,r2,r3,r4,c1,endBlockWidth,std::make_shared<Point2d>());
   ShapeProperties aprops = nu4200.GetProperties();
   TRY_TESTME (nu4200.GetBoundingBox() == Rect2d(-612.5,0,612.5,2400.)) ;
   TRY_TESTME ( IsEqual(aprops.GetArea(), 643591.88418736, 1.)) ;
   TRY_TESTME ( IsEqual(aprops.GetIxx(),  514253978920.25, 1.)) ;
   TRY_TESTME ( IsEqual(aprops.GetIxy(),  0.     , 1.)) ;
   TRY_TESTME ( IsEqual(aprops.GetCentroid().X(),  0.     ,.1)) ;
   TRY_TESTME ( IsEqual(aprops.GetCentroid().Y(), 1093.1459162077   ,.1)) ;
   TRY_TESTME ( IsEqual(nu4200.GetHeight(), 2400.)) ;
   TRY_TESTME ( IsEqual(nu4200.GetTopFlangeWidth(0), 1225.)) ;
   TRY_TESTME ( IsEqual(nu4200.GetBottomFlangeWidth(0), 975.)) ;
   TRY_TESTME ( IsEqual(nu4200.GetT(),  150.)) ;
   TRY_TESTME ( IsEqual(nu4200.GetW1(), 1225.)) ;
   TRY_TESTME ( IsEqual(nu4200.GetW2(), 975.)) ;
   TRY_TESTME ( IsEqual(nu4200.GetD1(), 65.)) ;
   TRY_TESTME ( IsEqual(nu4200.GetD2(), 45.)) ;
   TRY_TESTME ( IsEqual(nu4200.GetD3(), 2015.)) ;
   TRY_TESTME ( IsEqual(nu4200.GetD4(), 140.)) ;
   TRY_TESTME ( IsEqual(nu4200.GetD5(), 135.)) ;
   TRY_TESTME ( IsEqual(nu4200.GetR1(), 200.)) ;
   TRY_TESTME ( IsEqual(nu4200.GetR2(), 200.)) ;
   TRY_TESTME ( IsEqual(nu4200.GetR3(), 50.)) ;
   TRY_TESTME ( IsEqual(nu4200.GetR4(), 50.)) ;

#ifdef _DEBUG
   nu4200.Dump(rlog.GetDumpCtx());
#endif 

   NUBeam beam;

   // Use some real dimensions (NU2400 - 150mm web)
   beam.SetW1(1225);
   beam.SetW2(975);
   beam.SetD1(65);
   beam.SetD2(45);
   beam.SetD3(2015);
   beam.SetD4(140);
   beam.SetD5(135);
   beam.SetT(150);
   beam.SetR1(200);
   beam.SetR2(200);
   beam.SetR3(50);
   beam.SetR4(50);

   //
   // Bounding Box
   //
   Rect2d box = beam.GetBoundingBox();
   TRY_TESTME(IsEqual(box.Left(), -612.5));
   TRY_TESTME(IsEqual(box.Right(), 612.5));
   TRY_TESTME(IsEqual(box.Top(), 2400.));
   TRY_TESTME(IsEqual(box.Bottom(), 0.00));

   //
   // ShapeProperties
   //
   ShapeProperties props = beam.GetProperties();
   TRY_TESTME(IsEqual(props.GetArea(), 643591.88418736495));
   TRY_TESTME(IsEqual(props.GetIxx(), 514253978920.25220));
   TRY_TESTME(IsEqual(props.GetIyy(), 25969895815.002991));
   TRY_TESTME(IsEqual(props.GetIxy(), 0.0));
   TRY_TESTME(IsEqual(props.GetCentroid().X(), 0.0));
   TRY_TESTME(IsEqual(props.GetCentroid().Y(), 1093.1459162077181));
   TRY_TESTME(props.GetCoordinateSystem() == ShapeProperties::CoordSystemType::Centroidal);

   TRY_TESTME(IsEqual(props.GetXleft(), 612.5));
   TRY_TESTME(IsEqual(props.GetXright(), 612.5));
   TRY_TESTME(IsEqual(props.GetYtop(), 2400.0 - props.GetCentroid().Y()));
   TRY_TESTME(IsEqual(props.GetYbottom(), props.GetCentroid().Y()));

   //
   // Perimeter
   //
   TRY_TESTME(IsEqual(beam.GetPerimeter(), 8308.7371100128730));

   //
   // FurthestDistance
   //

   Point2d p1(0, 20);
   Point2d p2(100, 20);
   Line2d line(p1, p2);

   // Shape on right
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

   TRY_TESTME(points.size() == 174);
   int i = 0;
   TRY_TESTME(points[i++] == Point2d(0.000000, 0.000000));
   TRY_TESTME(points[i++] == Point2d(-487.500000, 0.000000));
   TRY_TESTME(points[i++] == Point2d(-487.500000, 99.168460));
   TRY_TESTME(points[i++] == Point2d(-487.403372, 102.275460));
   TRY_TESTME(points[i++] == Point2d(-487.113862, 105.370451));
   TRY_TESTME(points[i++] == Point2d(-486.632589, 108.441471));
   TRY_TESTME(points[i++] == Point2d(-485.961412, 111.476649));
   TRY_TESTME(points[i++] == Point2d(-485.102927, 114.464255));
   TRY_TESTME(points[i++] == Point2d(-484.060451, 117.392741));
   TRY_TESTME(points[i++] == Point2d(-482.838014, 120.250787));
   TRY_TESTME(points[i++] == Point2d(-481.440339, 123.027349));
   TRY_TESTME(points[i++] == Point2d(-479.872831, 125.711693));
   TRY_TESTME(points[i++] == Point2d(-478.141547, 128.293444));
   TRY_TESTME(points[i++] == Point2d(-476.253178, 130.762624));
   TRY_TESTME(points[i++] == Point2d(-474.215024, 133.109689));
   TRY_TESTME(points[i++] == Point2d(-472.034962, 135.325567));
   TRY_TESTME(points[i++] == Point2d(-469.721419, 137.401694));
   TRY_TESTME(points[i++] == Point2d(-467.283336, 139.330045));
   TRY_TESTME(points[i++] == Point2d(-464.730137, 141.103167));
   TRY_TESTME(points[i++] == Point2d(-462.071691, 142.714206));
   TRY_TESTME(points[i++] == Point2d(-459.318272, 144.156936));
   TRY_TESTME(points[i++] == Point2d(-456.480523, 145.425781));
   TRY_TESTME(points[i++] == Point2d(-453.569412, 146.515836));
   TRY_TESTME(points[i++] == Point2d(-210.722351, 228.936657));
   TRY_TESTME(points[i++] == Point2d(-199.077907, 233.296876));
   TRY_TESTME(points[i++] == Point2d(-187.726912, 238.372254));
   TRY_TESTME(points[i++] == Point2d(-176.713237, 244.143175));
   TRY_TESTME(points[i++] == Point2d(-166.079451, 250.587333));
   TRY_TESTME(points[i++] == Point2d(-155.866656, 257.679820));
   TRY_TESTME(points[i++] == Point2d(-146.114325, 265.393224));
   TRY_TESTME(points[i++] == Point2d(-136.860151, 273.697732));
   TRY_TESTME(points[i++] == Point2d(-128.139904, 282.561244));
   TRY_TESTME(points[i++] == Point2d(-119.987288, 291.949504));
   TRY_TESTME(points[i++] == Point2d(-112.433814, 301.826224));
   TRY_TESTME(points[i++] == Point2d(-105.508676, 312.153229));
   TRY_TESTME(points[i++] == Point2d(-99.238642, 322.890605));
   TRY_TESTME(points[i++] == Point2d(-93.647946, 333.996850));
   TRY_TESTME(points[i++] == Point2d(-88.758196, 345.429038));
   TRY_TESTME(points[i++] == Point2d(-84.588292, 357.142981));
   TRY_TESTME(points[i++] == Point2d(-81.154351, 369.093404));
   TRY_TESTME(points[i++] == Point2d(-78.469645, 381.234117));
   TRY_TESTME(points[i++] == Point2d(-76.544552, 393.518196));
   TRY_TESTME(points[i++] == Point2d(-75.386511, 405.898160));
   TRY_TESTME(points[i++] == Point2d(-75.000000, 418.326160));
   TRY_TESTME(points[i++] == Point2d(-75.000000, 2106.044491));
   TRY_TESTME(points[i++] == Point2d(-75.552738, 2120.903489));
   TRY_TESTME(points[i++] == Point2d(-77.207898, 2135.680355));
   TRY_TESTME(points[i++] == Point2d(-79.956331, 2150.293413));
   TRY_TESTME(points[i++] == Point2d(-83.782845, 2164.661891));
   TRY_TESTME(points[i++] == Point2d(-88.666289, 2178.706367));
   TRY_TESTME(points[i++] == Point2d(-94.579672, 2192.349213));
   TRY_TESTME(points[i++] == Point2d(-101.490306, 2205.515020));
   TRY_TESTME(points[i++] == Point2d(-109.359996, 2218.131015));
   TRY_TESTME(points[i++] == Point2d(-118.145241, 2230.127465));
   TRY_TESTME(points[i++] == Point2d(-127.797483, 2241.438061));
   TRY_TESTME(points[i++] == Point2d(-138.263369, 2252.000284));
   TRY_TESTME(points[i++] == Point2d(-149.485051, 2261.755754));
   TRY_TESTME(points[i++] == Point2d(-161.400503, 2270.650548));
   TRY_TESTME(points[i++] == Point2d(-173.943862, 2278.635501));
   TRY_TESTME(points[i++] == Point2d(-187.045798, 2285.666478));
   TRY_TESTME(points[i++] == Point2d(-200.633890, 2291.704615));
   TRY_TESTME(points[i++] == Point2d(-214.633032, 2296.716537));
   TRY_TESTME(points[i++] == Point2d(-228.965846, 2300.674541));
   TRY_TESTME(points[i++] == Point2d(-243.553108, 2303.556751));
   TRY_TESTME(points[i++] == Point2d(-258.314189, 2305.347234));
   TRY_TESTME(points[i++] == Point2d(-566.671453, 2331.163191));
   TRY_TESTME(points[i++] == Point2d(-570.361723, 2331.610812));
   TRY_TESTME(points[i++] == Point2d(-574.008539, 2332.331365));
   TRY_TESTME(points[i++] == Point2d(-577.591742, 2333.320866));
   TRY_TESTME(points[i++] == Point2d(-581.091527, 2334.573846));
   TRY_TESTME(points[i++] == Point2d(-584.488551, 2336.083381));
   TRY_TESTME(points[i++] == Point2d(-587.764034, 2337.841125));
   TRY_TESTME(points[i++] == Point2d(-590.899874, 2339.837363));
   TRY_TESTME(points[i++] == Point2d(-593.878737, 2342.061061));
   TRY_TESTME(points[i++] == Point2d(-596.684158, 2344.499929));
   TRY_TESTME(points[i++] == Point2d(-599.300629, 2347.140485));
   TRY_TESTME(points[i++] == Point2d(-601.713690, 2349.968134));
   TRY_TESTME(points[i++] == Point2d(-603.910001, 2352.967246));
   TRY_TESTME(points[i++] == Point2d(-605.877423, 2356.121245));
   TRY_TESTME(points[i++] == Point2d(-607.605082, 2359.412697));
   TRY_TESTME(points[i++] == Point2d(-609.083428, 2362.823408));
   TRY_TESTME(points[i++] == Point2d(-610.304289, 2366.334527));
   TRY_TESTME(points[i++] == Point2d(-611.260917, 2369.926647));
   TRY_TESTME(points[i++] == Point2d(-611.948025, 2373.579911));
   TRY_TESTME(points[i++] == Point2d(-612.361815, 2377.274128));
   TRY_TESTME(points[i++] == Point2d(-612.500000, 2380.988877));
   TRY_TESTME(points[i++] == Point2d(-612.500000, 2400.000000));
   TRY_TESTME(points[i++] == Point2d(0.000000, 2400.000000));
   TRY_TESTME(points[i++] == Point2d(612.500000, 2400.000000));
   TRY_TESTME(points[i++] == Point2d(612.500000, 2380.988877));
   TRY_TESTME(points[i++] == Point2d(612.361815, 2377.274128));
   TRY_TESTME(points[i++] == Point2d(611.948025, 2373.579911));
   TRY_TESTME(points[i++] == Point2d(611.260917, 2369.926647));
   TRY_TESTME(points[i++] == Point2d(610.304289, 2366.334527));
   TRY_TESTME(points[i++] == Point2d(609.083428, 2362.823408));
   TRY_TESTME(points[i++] == Point2d(607.605082, 2359.412697));
   TRY_TESTME(points[i++] == Point2d(605.877423, 2356.121245));
   TRY_TESTME(points[i++] == Point2d(603.910001, 2352.967246));
   TRY_TESTME(points[i++] == Point2d(601.713690, 2349.968134));
   TRY_TESTME(points[i++] == Point2d(599.300629, 2347.140485));
   TRY_TESTME(points[i++] == Point2d(596.684158, 2344.499929));
   TRY_TESTME(points[i++] == Point2d(593.878737, 2342.061061));
   TRY_TESTME(points[i++] == Point2d(590.899874, 2339.837363));
   TRY_TESTME(points[i++] == Point2d(587.764034, 2337.841125));
   TRY_TESTME(points[i++] == Point2d(584.488551, 2336.083381));
   TRY_TESTME(points[i++] == Point2d(581.091527, 2334.573846));
   TRY_TESTME(points[i++] == Point2d(577.591742, 2333.320866));
   TRY_TESTME(points[i++] == Point2d(574.008539, 2332.331365));
   TRY_TESTME(points[i++] == Point2d(570.361723, 2331.610812));
   TRY_TESTME(points[i++] == Point2d(566.671453, 2331.163191));
   TRY_TESTME(points[i++] == Point2d(258.314189, 2305.347234));
   TRY_TESTME(points[i++] == Point2d(243.553108, 2303.556751));
   TRY_TESTME(points[i++] == Point2d(228.965846, 2300.674541));
   TRY_TESTME(points[i++] == Point2d(214.633032, 2296.716537));
   TRY_TESTME(points[i++] == Point2d(200.633890, 2291.704615));
   TRY_TESTME(points[i++] == Point2d(187.045798, 2285.666478));
   TRY_TESTME(points[i++] == Point2d(173.943862, 2278.635501));
   TRY_TESTME(points[i++] == Point2d(161.400503, 2270.650548));
   TRY_TESTME(points[i++] == Point2d(149.485051, 2261.755754));
   TRY_TESTME(points[i++] == Point2d(138.263369, 2252.000284));
   TRY_TESTME(points[i++] == Point2d(127.797483, 2241.438061));
   TRY_TESTME(points[i++] == Point2d(118.145241, 2230.127465));
   TRY_TESTME(points[i++] == Point2d(109.359996, 2218.131015));
   TRY_TESTME(points[i++] == Point2d(101.490306, 2205.515020));
   TRY_TESTME(points[i++] == Point2d(94.579672, 2192.349213));
   TRY_TESTME(points[i++] == Point2d(88.666289, 2178.706367));
   TRY_TESTME(points[i++] == Point2d(83.782845, 2164.661891));
   TRY_TESTME(points[i++] == Point2d(79.956331, 2150.293413));
   TRY_TESTME(points[i++] == Point2d(77.207898, 2135.680355));
   TRY_TESTME(points[i++] == Point2d(75.552738, 2120.903489));
   TRY_TESTME(points[i++] == Point2d(75.000000, 2106.044491));
   TRY_TESTME(points[i++] == Point2d(75.000000, 418.326160));
   TRY_TESTME(points[i++] == Point2d(75.386511, 405.898160));
   TRY_TESTME(points[i++] == Point2d(76.544552, 393.518196));
   TRY_TESTME(points[i++] == Point2d(78.469645, 381.234117));
   TRY_TESTME(points[i++] == Point2d(81.154351, 369.093404));
   TRY_TESTME(points[i++] == Point2d(84.588292, 357.142981));
   TRY_TESTME(points[i++] == Point2d(88.758196, 345.429038));
   TRY_TESTME(points[i++] == Point2d(93.647946, 333.996850));
   TRY_TESTME(points[i++] == Point2d(99.238642, 322.890605));
   TRY_TESTME(points[i++] == Point2d(105.508676, 312.153229));
   TRY_TESTME(points[i++] == Point2d(112.433814, 301.826224));
   TRY_TESTME(points[i++] == Point2d(119.987288, 291.949504));
   TRY_TESTME(points[i++] == Point2d(128.139904, 282.561244));
   TRY_TESTME(points[i++] == Point2d(136.860151, 273.697732));
   TRY_TESTME(points[i++] == Point2d(146.114325, 265.393224));
   TRY_TESTME(points[i++] == Point2d(155.866656, 257.679820));
   TRY_TESTME(points[i++] == Point2d(166.079451, 250.587333));
   TRY_TESTME(points[i++] == Point2d(176.713237, 244.143175));
   TRY_TESTME(points[i++] == Point2d(187.726912, 238.372254));
   TRY_TESTME(points[i++] == Point2d(199.077907, 233.296876));
   TRY_TESTME(points[i++] == Point2d(210.722351, 228.936657));
   TRY_TESTME(points[i++] == Point2d(453.569412, 146.515836));
   TRY_TESTME(points[i++] == Point2d(456.480523, 145.425781));
   TRY_TESTME(points[i++] == Point2d(459.318272, 144.156936));
   TRY_TESTME(points[i++] == Point2d(462.071691, 142.714206));
   TRY_TESTME(points[i++] == Point2d(464.730137, 141.103167));
   TRY_TESTME(points[i++] == Point2d(467.283336, 139.330045));
   TRY_TESTME(points[i++] == Point2d(469.721419, 137.401694));
   TRY_TESTME(points[i++] == Point2d(472.034962, 135.325567));
   TRY_TESTME(points[i++] == Point2d(474.215024, 133.109689));
   TRY_TESTME(points[i++] == Point2d(476.253178, 130.762624));
   TRY_TESTME(points[i++] == Point2d(478.141547, 128.293444));
   TRY_TESTME(points[i++] == Point2d(479.872831, 125.711693));
   TRY_TESTME(points[i++] == Point2d(481.440339, 123.027349));
   TRY_TESTME(points[i++] == Point2d(482.838014, 120.250787));
   TRY_TESTME(points[i++] == Point2d(484.060451, 117.392741));
   TRY_TESTME(points[i++] == Point2d(485.102927, 114.464255));
   TRY_TESTME(points[i++] == Point2d(485.961412, 111.476649));
   TRY_TESTME(points[i++] == Point2d(486.632589, 108.441471));
   TRY_TESTME(points[i++] == Point2d(487.113862, 105.370451));
   TRY_TESTME(points[i++] == Point2d(487.403372, 102.275460));
   TRY_TESTME(points[i++] == Point2d(487.500000, 99.168460));
   TRY_TESTME(points[i++] == Point2d(487.500000, 0.000000));
   TRY_TESTME(i == points.size());


   //
   // PointInShape
   //
   Point2d pnt(0, 0.5);
   TRY_TESTME(beam.PointInShape(pnt) == true);

   pnt.Move(500, 500);
   TRY_TESTME(beam.PointInShape(pnt) == false);

   pnt.Move(0, 0); // Point on perimeter
   TRY_TESTME(beam.PointInShape(pnt) == false);

   //
   // ClipWithLine
   //

   // setup clipping line
   p1.Move(-5000, 1500);
   p2.Move(5000, 1500);
   Line2d clipLine(p1, p2);

   auto clip = beam.CreateClippedShape(clipLine, Line2d::Side::Left);
   TRY_TESTME(clip != nullptr);

   points = clip->GetPolyPoints();
   TRY_TESTME(points.size() == 90);
   i = 0;
   TRY_TESTME(points[i++] == Point2d(0.000000, 0.000000));
   TRY_TESTME(points[i++] == Point2d(-487.500000, 0.000000));
   TRY_TESTME(points[i++] == Point2d(-487.500000, 99.168460));
   TRY_TESTME(points[i++] == Point2d(-487.403372, 102.275460));
   TRY_TESTME(points[i++] == Point2d(-487.113862, 105.370451));
   TRY_TESTME(points[i++] == Point2d(-486.632589, 108.441471));
   TRY_TESTME(points[i++] == Point2d(-485.961412, 111.476649));
   TRY_TESTME(points[i++] == Point2d(-485.102927, 114.464255));
   TRY_TESTME(points[i++] == Point2d(-484.060451, 117.392741));
   TRY_TESTME(points[i++] == Point2d(-482.838014, 120.250787));
   TRY_TESTME(points[i++] == Point2d(-481.440339, 123.027349));
   TRY_TESTME(points[i++] == Point2d(-479.872831, 125.711693));
   TRY_TESTME(points[i++] == Point2d(-478.141547, 128.293444));
   TRY_TESTME(points[i++] == Point2d(-476.253178, 130.762624));
   TRY_TESTME(points[i++] == Point2d(-474.215024, 133.109689));
   TRY_TESTME(points[i++] == Point2d(-472.034962, 135.325567));
   TRY_TESTME(points[i++] == Point2d(-469.721419, 137.401694));
   TRY_TESTME(points[i++] == Point2d(-467.283336, 139.330045));
   TRY_TESTME(points[i++] == Point2d(-464.730137, 141.103167));
   TRY_TESTME(points[i++] == Point2d(-462.071691, 142.714206));
   TRY_TESTME(points[i++] == Point2d(-459.318272, 144.156936));
   TRY_TESTME(points[i++] == Point2d(-456.480523, 145.425781));
   TRY_TESTME(points[i++] == Point2d(-453.569412, 146.515836));
   TRY_TESTME(points[i++] == Point2d(-210.722351, 228.936657));
   TRY_TESTME(points[i++] == Point2d(-199.077907, 233.296876));
   TRY_TESTME(points[i++] == Point2d(-187.726912, 238.372254));
   TRY_TESTME(points[i++] == Point2d(-176.713237, 244.143175));
   TRY_TESTME(points[i++] == Point2d(-166.079451, 250.587333));
   TRY_TESTME(points[i++] == Point2d(-155.866656, 257.679820));
   TRY_TESTME(points[i++] == Point2d(-146.114325, 265.393224));
   TRY_TESTME(points[i++] == Point2d(-136.860151, 273.697732));
   TRY_TESTME(points[i++] == Point2d(-128.139904, 282.561244));
   TRY_TESTME(points[i++] == Point2d(-119.987288, 291.949504));
   TRY_TESTME(points[i++] == Point2d(-112.433814, 301.826224));
   TRY_TESTME(points[i++] == Point2d(-105.508676, 312.153229));
   TRY_TESTME(points[i++] == Point2d(-99.238642, 322.890605));
   TRY_TESTME(points[i++] == Point2d(-93.647946, 333.996850));
   TRY_TESTME(points[i++] == Point2d(-88.758196, 345.429038));
   TRY_TESTME(points[i++] == Point2d(-84.588292, 357.142981));
   TRY_TESTME(points[i++] == Point2d(-81.154351, 369.093404));
   TRY_TESTME(points[i++] == Point2d(-78.469645, 381.234117));
   TRY_TESTME(points[i++] == Point2d(-76.544552, 393.518196));
   TRY_TESTME(points[i++] == Point2d(-75.386511, 405.898160));
   TRY_TESTME(points[i++] == Point2d(-75.000000, 418.326160));
   TRY_TESTME(points[i++] == Point2d(-75.000000, 1500.000000));
   TRY_TESTME(points[i++] == Point2d(75.000000, 1500.000000));
   TRY_TESTME(points[i++] == Point2d(75.000000, 418.326160));
   TRY_TESTME(points[i++] == Point2d(75.386511, 405.898160));
   TRY_TESTME(points[i++] == Point2d(76.544552, 393.518196));
   TRY_TESTME(points[i++] == Point2d(78.469645, 381.234117));
   TRY_TESTME(points[i++] == Point2d(81.154351, 369.093404));
   TRY_TESTME(points[i++] == Point2d(84.588292, 357.142981));
   TRY_TESTME(points[i++] == Point2d(88.758196, 345.429038));
   TRY_TESTME(points[i++] == Point2d(93.647946, 333.996850));
   TRY_TESTME(points[i++] == Point2d(99.238642, 322.890605));
   TRY_TESTME(points[i++] == Point2d(105.508676, 312.153229));
   TRY_TESTME(points[i++] == Point2d(112.433814, 301.826224));
   TRY_TESTME(points[i++] == Point2d(119.987288, 291.949504));
   TRY_TESTME(points[i++] == Point2d(128.139904, 282.561244));
   TRY_TESTME(points[i++] == Point2d(136.860151, 273.697732));
   TRY_TESTME(points[i++] == Point2d(146.114325, 265.393224));
   TRY_TESTME(points[i++] == Point2d(155.866656, 257.679820));
   TRY_TESTME(points[i++] == Point2d(166.079451, 250.587333));
   TRY_TESTME(points[i++] == Point2d(176.713237, 244.143175));
   TRY_TESTME(points[i++] == Point2d(187.726912, 238.372254));
   TRY_TESTME(points[i++] == Point2d(199.077907, 233.296876));
   TRY_TESTME(points[i++] == Point2d(210.722351, 228.936657));
   TRY_TESTME(points[i++] == Point2d(453.569412, 146.515836));
   TRY_TESTME(points[i++] == Point2d(456.480523, 145.425781));
   TRY_TESTME(points[i++] == Point2d(459.318272, 144.156936));
   TRY_TESTME(points[i++] == Point2d(462.071691, 142.714206));
   TRY_TESTME(points[i++] == Point2d(464.730137, 141.103167));
   TRY_TESTME(points[i++] == Point2d(467.283336, 139.330045));
   TRY_TESTME(points[i++] == Point2d(469.721419, 137.401694));
   TRY_TESTME(points[i++] == Point2d(472.034962, 135.325567));
   TRY_TESTME(points[i++] == Point2d(474.215024, 133.109689));
   TRY_TESTME(points[i++] == Point2d(476.253178, 130.762624));
   TRY_TESTME(points[i++] == Point2d(478.141547, 128.293444));
   TRY_TESTME(points[i++] == Point2d(479.872831, 125.711693));
   TRY_TESTME(points[i++] == Point2d(481.440339, 123.027349));
   TRY_TESTME(points[i++] == Point2d(482.838014, 120.250787));
   TRY_TESTME(points[i++] == Point2d(484.060451, 117.392741));
   TRY_TESTME(points[i++] == Point2d(485.102927, 114.464255));
   TRY_TESTME(points[i++] == Point2d(485.961412, 111.476649));
   TRY_TESTME(points[i++] == Point2d(486.632589, 108.441471));
   TRY_TESTME(points[i++] == Point2d(487.113862, 105.370451));
   TRY_TESTME(points[i++] == Point2d(487.403372, 102.275460));
   TRY_TESTME(points[i++] == Point2d(487.500000, 99.168460));
   TRY_TESTME(points[i++] == Point2d(487.500000, 0.000000));
   TRY_TESTME(points[i++] == Point2d(0.000000, 0.000000));
   TRY_TESTME(i == points.size());

   // clip in other direction
   p1.Move(5000, 1500);
   p2.Move(-5000, 1500);
   clipLine.ThroughPoints(p1, p2);

   clip = beam.CreateClippedShape(clipLine, Line2d::Side::Left);
   TRY_TESTME(clip != nullptr);

   points = clip->GetPolyPoints();
   TRY_TESTME(points.size() == 89);
   i = 0;
   TRY_TESTME(points[i++] == Point2d(-75.000000, 1500.000000));
   TRY_TESTME(points[i++] == Point2d(-75.000000, 2106.044491));
   TRY_TESTME(points[i++] == Point2d(-75.552738, 2120.903489));
   TRY_TESTME(points[i++] == Point2d(-77.207898, 2135.680355));
   TRY_TESTME(points[i++] == Point2d(-79.956331, 2150.293413));
   TRY_TESTME(points[i++] == Point2d(-83.782845, 2164.661891));
   TRY_TESTME(points[i++] == Point2d(-88.666289, 2178.706367));
   TRY_TESTME(points[i++] == Point2d(-94.579672, 2192.349213));
   TRY_TESTME(points[i++] == Point2d(-101.490306, 2205.515020));
   TRY_TESTME(points[i++] == Point2d(-109.359996, 2218.131015));
   TRY_TESTME(points[i++] == Point2d(-118.145241, 2230.127465));
   TRY_TESTME(points[i++] == Point2d(-127.797483, 2241.438061));
   TRY_TESTME(points[i++] == Point2d(-138.263369, 2252.000284));
   TRY_TESTME(points[i++] == Point2d(-149.485051, 2261.755754));
   TRY_TESTME(points[i++] == Point2d(-161.400503, 2270.650548));
   TRY_TESTME(points[i++] == Point2d(-173.943862, 2278.635501));
   TRY_TESTME(points[i++] == Point2d(-187.045798, 2285.666478));
   TRY_TESTME(points[i++] == Point2d(-200.633890, 2291.704615));
   TRY_TESTME(points[i++] == Point2d(-214.633032, 2296.716537));
   TRY_TESTME(points[i++] == Point2d(-228.965846, 2300.674541));
   TRY_TESTME(points[i++] == Point2d(-243.553108, 2303.556751));
   TRY_TESTME(points[i++] == Point2d(-258.314189, 2305.347234));
   TRY_TESTME(points[i++] == Point2d(-566.671453, 2331.163191));
   TRY_TESTME(points[i++] == Point2d(-570.361723, 2331.610812));
   TRY_TESTME(points[i++] == Point2d(-574.008539, 2332.331365));
   TRY_TESTME(points[i++] == Point2d(-577.591742, 2333.320866));
   TRY_TESTME(points[i++] == Point2d(-581.091527, 2334.573846));
   TRY_TESTME(points[i++] == Point2d(-584.488551, 2336.083381));
   TRY_TESTME(points[i++] == Point2d(-587.764034, 2337.841125));
   TRY_TESTME(points[i++] == Point2d(-590.899874, 2339.837363));
   TRY_TESTME(points[i++] == Point2d(-593.878737, 2342.061061));
   TRY_TESTME(points[i++] == Point2d(-596.684158, 2344.499929));
   TRY_TESTME(points[i++] == Point2d(-599.300629, 2347.140485));
   TRY_TESTME(points[i++] == Point2d(-601.713690, 2349.968134));
   TRY_TESTME(points[i++] == Point2d(-603.910001, 2352.967246));
   TRY_TESTME(points[i++] == Point2d(-605.877423, 2356.121245));
   TRY_TESTME(points[i++] == Point2d(-607.605082, 2359.412697));
   TRY_TESTME(points[i++] == Point2d(-609.083428, 2362.823408));
   TRY_TESTME(points[i++] == Point2d(-610.304289, 2366.334527));
   TRY_TESTME(points[i++] == Point2d(-611.260917, 2369.926647));
   TRY_TESTME(points[i++] == Point2d(-611.948025, 2373.579911));
   TRY_TESTME(points[i++] == Point2d(-612.361815, 2377.274128));
   TRY_TESTME(points[i++] == Point2d(-612.500000, 2380.988877));
   TRY_TESTME(points[i++] == Point2d(-612.500000, 2400.000000));
   TRY_TESTME(points[i++] == Point2d(0.000000, 2400.000000));
   TRY_TESTME(points[i++] == Point2d(612.500000, 2400.000000));
   TRY_TESTME(points[i++] == Point2d(612.500000, 2380.988877));
   TRY_TESTME(points[i++] == Point2d(612.361815, 2377.274128));
   TRY_TESTME(points[i++] == Point2d(611.948025, 2373.579911));
   TRY_TESTME(points[i++] == Point2d(611.260917, 2369.926647));
   TRY_TESTME(points[i++] == Point2d(610.304289, 2366.334527));
   TRY_TESTME(points[i++] == Point2d(609.083428, 2362.823408));
   TRY_TESTME(points[i++] == Point2d(607.605082, 2359.412697));
   TRY_TESTME(points[i++] == Point2d(605.877423, 2356.121245));
   TRY_TESTME(points[i++] == Point2d(603.910001, 2352.967246));
   TRY_TESTME(points[i++] == Point2d(601.713690, 2349.968134));
   TRY_TESTME(points[i++] == Point2d(599.300629, 2347.140485));
   TRY_TESTME(points[i++] == Point2d(596.684158, 2344.499929));
   TRY_TESTME(points[i++] == Point2d(593.878737, 2342.061061));
   TRY_TESTME(points[i++] == Point2d(590.899874, 2339.837363));
   TRY_TESTME(points[i++] == Point2d(587.764034, 2337.841125));
   TRY_TESTME(points[i++] == Point2d(584.488551, 2336.083381));
   TRY_TESTME(points[i++] == Point2d(581.091527, 2334.573846));
   TRY_TESTME(points[i++] == Point2d(577.591742, 2333.320866));
   TRY_TESTME(points[i++] == Point2d(574.008539, 2332.331365));
   TRY_TESTME(points[i++] == Point2d(570.361723, 2331.610812));
   TRY_TESTME(points[i++] == Point2d(566.671453, 2331.163191));
   TRY_TESTME(points[i++] == Point2d(258.314189, 2305.347234));
   TRY_TESTME(points[i++] == Point2d(243.553108, 2303.556751));
   TRY_TESTME(points[i++] == Point2d(228.965846, 2300.674541));
   TRY_TESTME(points[i++] == Point2d(214.633032, 2296.716537));
   TRY_TESTME(points[i++] == Point2d(200.633890, 2291.704615));
   TRY_TESTME(points[i++] == Point2d(187.045798, 2285.666478));
   TRY_TESTME(points[i++] == Point2d(173.943862, 2278.635501));
   TRY_TESTME(points[i++] == Point2d(161.400503, 2270.650548));
   TRY_TESTME(points[i++] == Point2d(149.485051, 2261.755754));
   TRY_TESTME(points[i++] == Point2d(138.263369, 2252.000284));
   TRY_TESTME(points[i++] == Point2d(127.797483, 2241.438061));
   TRY_TESTME(points[i++] == Point2d(118.145241, 2230.127465));
   TRY_TESTME(points[i++] == Point2d(109.359996, 2218.131015));
   TRY_TESTME(points[i++] == Point2d(101.490306, 2205.515020));
   TRY_TESTME(points[i++] == Point2d(94.579672, 2192.349213));
   TRY_TESTME(points[i++] == Point2d(88.666289, 2178.706367));
   TRY_TESTME(points[i++] == Point2d(83.782845, 2164.661891));
   TRY_TESTME(points[i++] == Point2d(79.956331, 2150.293413));
   TRY_TESTME(points[i++] == Point2d(77.207898, 2135.680355));
   TRY_TESTME(points[i++] == Point2d(75.552738, 2120.903489));
   TRY_TESTME(points[i++] == Point2d(75.000000, 2106.044491));
   TRY_TESTME(points[i++] == Point2d(75.000000, 1500.000000));
   TRY_TESTME(i == points.size());

   //
   // ClipIn
   //
   Rect2d clipRect(-5000, 1500, 5000, 10000);

   clip = beam.CreateClippedShape(clipRect, Shape::ClipRegion::In);
   TRY_TESTME(clip != nullptr);

   points = clip->GetPolyPoints();
   TRY_TESTME(points.size() == 89);
   i = 0;
   TRY_TESTME(points[i++] == Point2d(-75.000000, 1500.000000));
   TRY_TESTME(points[i++] == Point2d(-75.000000, 2106.044491));
   TRY_TESTME(points[i++] == Point2d(-75.552738, 2120.903489));
   TRY_TESTME(points[i++] == Point2d(-77.207898, 2135.680355));
   TRY_TESTME(points[i++] == Point2d(-79.956331, 2150.293413));
   TRY_TESTME(points[i++] == Point2d(-83.782845, 2164.661891));
   TRY_TESTME(points[i++] == Point2d(-88.666289, 2178.706367));
   TRY_TESTME(points[i++] == Point2d(-94.579672, 2192.349213));
   TRY_TESTME(points[i++] == Point2d(-101.490306, 2205.515020));
   TRY_TESTME(points[i++] == Point2d(-109.359996, 2218.131015));
   TRY_TESTME(points[i++] == Point2d(-118.145241, 2230.127465));
   TRY_TESTME(points[i++] == Point2d(-127.797483, 2241.438061));
   TRY_TESTME(points[i++] == Point2d(-138.263369, 2252.000284));
   TRY_TESTME(points[i++] == Point2d(-149.485051, 2261.755754));
   TRY_TESTME(points[i++] == Point2d(-161.400503, 2270.650548));
   TRY_TESTME(points[i++] == Point2d(-173.943862, 2278.635501));
   TRY_TESTME(points[i++] == Point2d(-187.045798, 2285.666478));
   TRY_TESTME(points[i++] == Point2d(-200.633890, 2291.704615));
   TRY_TESTME(points[i++] == Point2d(-214.633032, 2296.716537));
   TRY_TESTME(points[i++] == Point2d(-228.965846, 2300.674541));
   TRY_TESTME(points[i++] == Point2d(-243.553108, 2303.556751));
   TRY_TESTME(points[i++] == Point2d(-258.314189, 2305.347234));
   TRY_TESTME(points[i++] == Point2d(-566.671453, 2331.163191));
   TRY_TESTME(points[i++] == Point2d(-570.361723, 2331.610812));
   TRY_TESTME(points[i++] == Point2d(-574.008539, 2332.331365));
   TRY_TESTME(points[i++] == Point2d(-577.591742, 2333.320866));
   TRY_TESTME(points[i++] == Point2d(-581.091527, 2334.573846));
   TRY_TESTME(points[i++] == Point2d(-584.488551, 2336.083381));
   TRY_TESTME(points[i++] == Point2d(-587.764034, 2337.841125));
   TRY_TESTME(points[i++] == Point2d(-590.899874, 2339.837363));
   TRY_TESTME(points[i++] == Point2d(-593.878737, 2342.061061));
   TRY_TESTME(points[i++] == Point2d(-596.684158, 2344.499929));
   TRY_TESTME(points[i++] == Point2d(-599.300629, 2347.140485));
   TRY_TESTME(points[i++] == Point2d(-601.713690, 2349.968134));
   TRY_TESTME(points[i++] == Point2d(-603.910001, 2352.967246));
   TRY_TESTME(points[i++] == Point2d(-605.877423, 2356.121245));
   TRY_TESTME(points[i++] == Point2d(-607.605082, 2359.412697));
   TRY_TESTME(points[i++] == Point2d(-609.083428, 2362.823408));
   TRY_TESTME(points[i++] == Point2d(-610.304289, 2366.334527));
   TRY_TESTME(points[i++] == Point2d(-611.260917, 2369.926647));
   TRY_TESTME(points[i++] == Point2d(-611.948025, 2373.579911));
   TRY_TESTME(points[i++] == Point2d(-612.361815, 2377.274128));
   TRY_TESTME(points[i++] == Point2d(-612.500000, 2380.988877));
   TRY_TESTME(points[i++] == Point2d(-612.500000, 2400.000000));
   TRY_TESTME(points[i++] == Point2d(0.000000, 2400.000000));
   TRY_TESTME(points[i++] == Point2d(612.500000, 2400.000000));
   TRY_TESTME(points[i++] == Point2d(612.500000, 2380.988877));
   TRY_TESTME(points[i++] == Point2d(612.361815, 2377.274128));
   TRY_TESTME(points[i++] == Point2d(611.948025, 2373.579911));
   TRY_TESTME(points[i++] == Point2d(611.260917, 2369.926647));
   TRY_TESTME(points[i++] == Point2d(610.304289, 2366.334527));
   TRY_TESTME(points[i++] == Point2d(609.083428, 2362.823408));
   TRY_TESTME(points[i++] == Point2d(607.605082, 2359.412697));
   TRY_TESTME(points[i++] == Point2d(605.877423, 2356.121245));
   TRY_TESTME(points[i++] == Point2d(603.910001, 2352.967246));
   TRY_TESTME(points[i++] == Point2d(601.713690, 2349.968134));
   TRY_TESTME(points[i++] == Point2d(599.300629, 2347.140485));
   TRY_TESTME(points[i++] == Point2d(596.684158, 2344.499929));
   TRY_TESTME(points[i++] == Point2d(593.878737, 2342.061061));
   TRY_TESTME(points[i++] == Point2d(590.899874, 2339.837363));
   TRY_TESTME(points[i++] == Point2d(587.764034, 2337.841125));
   TRY_TESTME(points[i++] == Point2d(584.488551, 2336.083381));
   TRY_TESTME(points[i++] == Point2d(581.091527, 2334.573846));
   TRY_TESTME(points[i++] == Point2d(577.591742, 2333.320866));
   TRY_TESTME(points[i++] == Point2d(574.008539, 2332.331365));
   TRY_TESTME(points[i++] == Point2d(570.361723, 2331.610812));
   TRY_TESTME(points[i++] == Point2d(566.671453, 2331.163191));
   TRY_TESTME(points[i++] == Point2d(258.314189, 2305.347234));
   TRY_TESTME(points[i++] == Point2d(243.553108, 2303.556751));
   TRY_TESTME(points[i++] == Point2d(228.965846, 2300.674541));
   TRY_TESTME(points[i++] == Point2d(214.633032, 2296.716537));
   TRY_TESTME(points[i++] == Point2d(200.633890, 2291.704615));
   TRY_TESTME(points[i++] == Point2d(187.045798, 2285.666478));
   TRY_TESTME(points[i++] == Point2d(173.943862, 2278.635501));
   TRY_TESTME(points[i++] == Point2d(161.400503, 2270.650548));
   TRY_TESTME(points[i++] == Point2d(149.485051, 2261.755754));
   TRY_TESTME(points[i++] == Point2d(138.263369, 2252.000284));
   TRY_TESTME(points[i++] == Point2d(127.797483, 2241.438061));
   TRY_TESTME(points[i++] == Point2d(118.145241, 2230.127465));
   TRY_TESTME(points[i++] == Point2d(109.359996, 2218.131015));
   TRY_TESTME(points[i++] == Point2d(101.490306, 2205.515020));
   TRY_TESTME(points[i++] == Point2d(94.579672, 2192.349213));
   TRY_TESTME(points[i++] == Point2d(88.666289, 2178.706367));
   TRY_TESTME(points[i++] == Point2d(83.782845, 2164.661891));
   TRY_TESTME(points[i++] == Point2d(79.956331, 2150.293413));
   TRY_TESTME(points[i++] == Point2d(77.207898, 2135.680355));
   TRY_TESTME(points[i++] == Point2d(75.552738, 2120.903489));
   TRY_TESTME(points[i++] == Point2d(75.000000, 2106.044491));
   TRY_TESTME(points[i++] == Point2d(75.000000, 1500.000000));
   TRY_TESTME(i == points.size());


   //
   // MoveEx (tests Offset as well)
   //
   Point2d from(0, 0);
   Point2d to(100, 100);

   beam.Move(from, to);
   points = beam.GetPolyPoints();
   TRY_TESTME(points.size() == 175);
   i = 0;
   TRY_TESTME(points[i++] == Point2d(100.000000, 100.000000));
   TRY_TESTME(points[i++] == Point2d(-387.500000, 100.000000));
   TRY_TESTME(points[i++] == Point2d(-387.500000, 199.168460));
   TRY_TESTME(points[i++] == Point2d(-387.403372, 202.275460));
   TRY_TESTME(points[i++] == Point2d(-387.113862, 205.370451));
   TRY_TESTME(points[i++] == Point2d(-386.632589, 208.441471));
   TRY_TESTME(points[i++] == Point2d(-385.961412, 211.476649));
   TRY_TESTME(points[i++] == Point2d(-385.102927, 214.464255));
   TRY_TESTME(points[i++] == Point2d(-384.060451, 217.392741));
   TRY_TESTME(points[i++] == Point2d(-382.838014, 220.250787));
   TRY_TESTME(points[i++] == Point2d(-381.440339, 223.027349));
   TRY_TESTME(points[i++] == Point2d(-379.872831, 225.711693));
   TRY_TESTME(points[i++] == Point2d(-378.141547, 228.293444));
   TRY_TESTME(points[i++] == Point2d(-376.253178, 230.762624));
   TRY_TESTME(points[i++] == Point2d(-374.215024, 233.109689));
   TRY_TESTME(points[i++] == Point2d(-372.034962, 235.325567));
   TRY_TESTME(points[i++] == Point2d(-369.721419, 237.401694));
   TRY_TESTME(points[i++] == Point2d(-367.283336, 239.330045));
   TRY_TESTME(points[i++] == Point2d(-364.730137, 241.103167));
   TRY_TESTME(points[i++] == Point2d(-362.071691, 242.714206));
   TRY_TESTME(points[i++] == Point2d(-359.318272, 244.156936));
   TRY_TESTME(points[i++] == Point2d(-356.480523, 245.425781));
   TRY_TESTME(points[i++] == Point2d(-353.569412, 246.515836));
   TRY_TESTME(points[i++] == Point2d(-110.722351, 328.936657));
   TRY_TESTME(points[i++] == Point2d(-99.077907, 333.296876));
   TRY_TESTME(points[i++] == Point2d(-87.726912, 338.372254));
   TRY_TESTME(points[i++] == Point2d(-76.713237, 344.143175));
   TRY_TESTME(points[i++] == Point2d(-66.079451, 350.587333));
   TRY_TESTME(points[i++] == Point2d(-55.866656, 357.679820));
   TRY_TESTME(points[i++] == Point2d(-46.114325, 365.393224));
   TRY_TESTME(points[i++] == Point2d(-36.860151, 373.697732));
   TRY_TESTME(points[i++] == Point2d(-28.139904, 382.561244));
   TRY_TESTME(points[i++] == Point2d(-19.987288, 391.949504));
   TRY_TESTME(points[i++] == Point2d(-12.433814, 401.826224));
   TRY_TESTME(points[i++] == Point2d(-5.508676, 412.153229));
   TRY_TESTME(points[i++] == Point2d(0.761358, 422.890605));
   TRY_TESTME(points[i++] == Point2d(6.352054, 433.996850));
   TRY_TESTME(points[i++] == Point2d(11.241804, 445.429038));
   TRY_TESTME(points[i++] == Point2d(15.411708, 457.142981));
   TRY_TESTME(points[i++] == Point2d(18.845649, 469.093404));
   TRY_TESTME(points[i++] == Point2d(21.530355, 481.234117));
   TRY_TESTME(points[i++] == Point2d(23.455448, 493.518196));
   TRY_TESTME(points[i++] == Point2d(24.613489, 505.898160));
   TRY_TESTME(points[i++] == Point2d(25.000000, 518.326160));
   TRY_TESTME(points[i++] == Point2d(25.000000, 2206.044491));
   TRY_TESTME(points[i++] == Point2d(24.447262, 2220.903489));
   TRY_TESTME(points[i++] == Point2d(22.792102, 2235.680355));
   TRY_TESTME(points[i++] == Point2d(20.043669, 2250.293413));
   TRY_TESTME(points[i++] == Point2d(16.217155, 2264.661891));
   TRY_TESTME(points[i++] == Point2d(11.333711, 2278.706367));
   TRY_TESTME(points[i++] == Point2d(5.420328, 2292.349213));
   TRY_TESTME(points[i++] == Point2d(-1.490306, 2305.515020));
   TRY_TESTME(points[i++] == Point2d(-9.359996, 2318.131015));
   TRY_TESTME(points[i++] == Point2d(-18.145241, 2330.127465));
   TRY_TESTME(points[i++] == Point2d(-27.797483, 2341.438061));
   TRY_TESTME(points[i++] == Point2d(-38.263369, 2352.000284));
   TRY_TESTME(points[i++] == Point2d(-49.485051, 2361.755754));
   TRY_TESTME(points[i++] == Point2d(-61.400503, 2370.650548));
   TRY_TESTME(points[i++] == Point2d(-73.943862, 2378.635501));
   TRY_TESTME(points[i++] == Point2d(-87.045798, 2385.666478));
   TRY_TESTME(points[i++] == Point2d(-100.633890, 2391.704615));
   TRY_TESTME(points[i++] == Point2d(-114.633032, 2396.716537));
   TRY_TESTME(points[i++] == Point2d(-128.965846, 2400.674541));
   TRY_TESTME(points[i++] == Point2d(-143.553108, 2403.556751));
   TRY_TESTME(points[i++] == Point2d(-158.314189, 2405.347234));
   TRY_TESTME(points[i++] == Point2d(-466.671453, 2431.163191));
   TRY_TESTME(points[i++] == Point2d(-470.361723, 2431.610812));
   TRY_TESTME(points[i++] == Point2d(-474.008539, 2432.331365));
   TRY_TESTME(points[i++] == Point2d(-477.591742, 2433.320866));
   TRY_TESTME(points[i++] == Point2d(-481.091527, 2434.573846));
   TRY_TESTME(points[i++] == Point2d(-484.488551, 2436.083381));
   TRY_TESTME(points[i++] == Point2d(-487.764034, 2437.841125));
   TRY_TESTME(points[i++] == Point2d(-490.899874, 2439.837363));
   TRY_TESTME(points[i++] == Point2d(-493.878737, 2442.061061));
   TRY_TESTME(points[i++] == Point2d(-496.684158, 2444.499929));
   TRY_TESTME(points[i++] == Point2d(-499.300629, 2447.140485));
   TRY_TESTME(points[i++] == Point2d(-501.713690, 2449.968134));
   TRY_TESTME(points[i++] == Point2d(-503.910001, 2452.967246));
   TRY_TESTME(points[i++] == Point2d(-505.877423, 2456.121245));
   TRY_TESTME(points[i++] == Point2d(-507.605082, 2459.412697));
   TRY_TESTME(points[i++] == Point2d(-509.083428, 2462.823408));
   TRY_TESTME(points[i++] == Point2d(-510.304289, 2466.334527));
   TRY_TESTME(points[i++] == Point2d(-511.260917, 2469.926647));
   TRY_TESTME(points[i++] == Point2d(-511.948025, 2473.579911));
   TRY_TESTME(points[i++] == Point2d(-512.361815, 2477.274128));
   TRY_TESTME(points[i++] == Point2d(-512.500000, 2480.988877));
   TRY_TESTME(points[i++] == Point2d(-512.500000, 2500.000000));
   TRY_TESTME(points[i++] == Point2d(100.000000, 2500.000000));
   TRY_TESTME(points[i++] == Point2d(712.500000, 2500.000000));
   TRY_TESTME(points[i++] == Point2d(712.500000, 2480.988877));
   TRY_TESTME(points[i++] == Point2d(712.361815, 2477.274128));
   TRY_TESTME(points[i++] == Point2d(711.948025, 2473.579911));
   TRY_TESTME(points[i++] == Point2d(711.260917, 2469.926647));
   TRY_TESTME(points[i++] == Point2d(710.304289, 2466.334527));
   TRY_TESTME(points[i++] == Point2d(709.083428, 2462.823408));
   TRY_TESTME(points[i++] == Point2d(707.605082, 2459.412697));
   TRY_TESTME(points[i++] == Point2d(705.877423, 2456.121245));
   TRY_TESTME(points[i++] == Point2d(703.910001, 2452.967246));
   TRY_TESTME(points[i++] == Point2d(701.713690, 2449.968134));
   TRY_TESTME(points[i++] == Point2d(699.300629, 2447.140485));
   TRY_TESTME(points[i++] == Point2d(696.684158, 2444.499929));
   TRY_TESTME(points[i++] == Point2d(693.878737, 2442.061061));
   TRY_TESTME(points[i++] == Point2d(690.899874, 2439.837363));
   TRY_TESTME(points[i++] == Point2d(687.764034, 2437.841125));
   TRY_TESTME(points[i++] == Point2d(684.488551, 2436.083381));
   TRY_TESTME(points[i++] == Point2d(681.091527, 2434.573846));
   TRY_TESTME(points[i++] == Point2d(677.591742, 2433.320866));
   TRY_TESTME(points[i++] == Point2d(674.008539, 2432.331365));
   TRY_TESTME(points[i++] == Point2d(670.361723, 2431.610812));
   TRY_TESTME(points[i++] == Point2d(666.671453, 2431.163191));
   TRY_TESTME(points[i++] == Point2d(358.314189, 2405.347234));
   TRY_TESTME(points[i++] == Point2d(343.553108, 2403.556751));
   TRY_TESTME(points[i++] == Point2d(328.965846, 2400.674541));
   TRY_TESTME(points[i++] == Point2d(314.633032, 2396.716537));
   TRY_TESTME(points[i++] == Point2d(300.633890, 2391.704615));
   TRY_TESTME(points[i++] == Point2d(287.045798, 2385.666478));
   TRY_TESTME(points[i++] == Point2d(273.943862, 2378.635501));
   TRY_TESTME(points[i++] == Point2d(261.400503, 2370.650548));
   TRY_TESTME(points[i++] == Point2d(249.485051, 2361.755754));
   TRY_TESTME(points[i++] == Point2d(238.263369, 2352.000284));
   TRY_TESTME(points[i++] == Point2d(227.797483, 2341.438061));
   TRY_TESTME(points[i++] == Point2d(218.145241, 2330.127465));
   TRY_TESTME(points[i++] == Point2d(209.359996, 2318.131015));
   TRY_TESTME(points[i++] == Point2d(201.490306, 2305.515020));
   TRY_TESTME(points[i++] == Point2d(194.579672, 2292.349213));
   TRY_TESTME(points[i++] == Point2d(188.666289, 2278.706367));
   TRY_TESTME(points[i++] == Point2d(183.782845, 2264.661891));
   TRY_TESTME(points[i++] == Point2d(179.956331, 2250.293413));
   TRY_TESTME(points[i++] == Point2d(177.207898, 2235.680355));
   TRY_TESTME(points[i++] == Point2d(175.552738, 2220.903489));
   TRY_TESTME(points[i++] == Point2d(175.000000, 2206.044491));
   TRY_TESTME(points[i++] == Point2d(175.000000, 518.326160));
   TRY_TESTME(points[i++] == Point2d(175.386511, 505.898160));
   TRY_TESTME(points[i++] == Point2d(176.544552, 493.518196));
   TRY_TESTME(points[i++] == Point2d(178.469645, 481.234117));
   TRY_TESTME(points[i++] == Point2d(181.154351, 469.093404));
   TRY_TESTME(points[i++] == Point2d(184.588292, 457.142981));
   TRY_TESTME(points[i++] == Point2d(188.758196, 445.429038));
   TRY_TESTME(points[i++] == Point2d(193.647946, 433.996850));
   TRY_TESTME(points[i++] == Point2d(199.238642, 422.890605));
   TRY_TESTME(points[i++] == Point2d(205.508676, 412.153229));
   TRY_TESTME(points[i++] == Point2d(212.433814, 401.826224));
   TRY_TESTME(points[i++] == Point2d(219.987288, 391.949504));
   TRY_TESTME(points[i++] == Point2d(228.139904, 382.561244));
   TRY_TESTME(points[i++] == Point2d(236.860151, 373.697732));
   TRY_TESTME(points[i++] == Point2d(246.114325, 365.393224));
   TRY_TESTME(points[i++] == Point2d(255.866656, 357.679820));
   TRY_TESTME(points[i++] == Point2d(266.079451, 350.587333));
   TRY_TESTME(points[i++] == Point2d(276.713237, 344.143175));
   TRY_TESTME(points[i++] == Point2d(287.726912, 338.372254));
   TRY_TESTME(points[i++] == Point2d(299.077907, 333.296876));
   TRY_TESTME(points[i++] == Point2d(310.722351, 328.936657));
   TRY_TESTME(points[i++] == Point2d(553.569412, 246.515836));
   TRY_TESTME(points[i++] == Point2d(556.480523, 245.425781));
   TRY_TESTME(points[i++] == Point2d(559.318272, 244.156936));
   TRY_TESTME(points[i++] == Point2d(562.071691, 242.714206));
   TRY_TESTME(points[i++] == Point2d(564.730137, 241.103167));
   TRY_TESTME(points[i++] == Point2d(567.283336, 239.330045));
   TRY_TESTME(points[i++] == Point2d(569.721419, 237.401694));
   TRY_TESTME(points[i++] == Point2d(572.034962, 235.325567));
   TRY_TESTME(points[i++] == Point2d(574.215024, 233.109689));
   TRY_TESTME(points[i++] == Point2d(576.253178, 230.762624));
   TRY_TESTME(points[i++] == Point2d(578.141547, 228.293444));
   TRY_TESTME(points[i++] == Point2d(579.872831, 225.711693));
   TRY_TESTME(points[i++] == Point2d(581.440339, 223.027349));
   TRY_TESTME(points[i++] == Point2d(582.838014, 220.250787));
   TRY_TESTME(points[i++] == Point2d(584.060451, 217.392741));
   TRY_TESTME(points[i++] == Point2d(585.102927, 214.464255));
   TRY_TESTME(points[i++] == Point2d(585.961412, 211.476649));
   TRY_TESTME(points[i++] == Point2d(586.632589, 208.441471));
   TRY_TESTME(points[i++] == Point2d(587.113862, 205.370451));
   TRY_TESTME(points[i++] == Point2d(587.403372, 202.275460));
   TRY_TESTME(points[i++] == Point2d(587.500000, 199.168460));
   TRY_TESTME(points[i++] == Point2d(587.500000, 100.000000));
   TRY_TESTME(points[i++] == Point2d(100.000000, 100.000000));
   TRY_TESTME(i == points.size());

   //
   // OffsetEx
   //
   Size2d size(-100, -100);
   beam.Offset(size);
   points = beam.GetPolyPoints();
   TRY_TESTME(points.size() == 174);
   i = 0;
   TRY_TESTME(points[i++] == Point2d(0.000000, 0.000000));
   TRY_TESTME(points[i++] == Point2d(-487.500000, 0.000000));
   TRY_TESTME(points[i++] == Point2d(-487.500000, 99.168460));
   TRY_TESTME(points[i++] == Point2d(-487.403372, 102.275460));
   TRY_TESTME(points[i++] == Point2d(-487.113862, 105.370451));
   TRY_TESTME(points[i++] == Point2d(-486.632589, 108.441471));
   TRY_TESTME(points[i++] == Point2d(-485.961412, 111.476649));
   TRY_TESTME(points[i++] == Point2d(-485.102927, 114.464255));
   TRY_TESTME(points[i++] == Point2d(-484.060451, 117.392741));
   TRY_TESTME(points[i++] == Point2d(-482.838014, 120.250787));
   TRY_TESTME(points[i++] == Point2d(-481.440339, 123.027349));
   TRY_TESTME(points[i++] == Point2d(-479.872831, 125.711693));
   TRY_TESTME(points[i++] == Point2d(-478.141547, 128.293444));
   TRY_TESTME(points[i++] == Point2d(-476.253178, 130.762624));
   TRY_TESTME(points[i++] == Point2d(-474.215024, 133.109689));
   TRY_TESTME(points[i++] == Point2d(-472.034962, 135.325567));
   TRY_TESTME(points[i++] == Point2d(-469.721419, 137.401694));
   TRY_TESTME(points[i++] == Point2d(-467.283336, 139.330045));
   TRY_TESTME(points[i++] == Point2d(-464.730137, 141.103167));
   TRY_TESTME(points[i++] == Point2d(-462.071691, 142.714206));
   TRY_TESTME(points[i++] == Point2d(-459.318272, 144.156936));
   TRY_TESTME(points[i++] == Point2d(-456.480523, 145.425781));
   TRY_TESTME(points[i++] == Point2d(-453.569412, 146.515836));
   TRY_TESTME(points[i++] == Point2d(-210.722351, 228.936657));
   TRY_TESTME(points[i++] == Point2d(-199.077907, 233.296876));
   TRY_TESTME(points[i++] == Point2d(-187.726912, 238.372254));
   TRY_TESTME(points[i++] == Point2d(-176.713237, 244.143175));
   TRY_TESTME(points[i++] == Point2d(-166.079451, 250.587333));
   TRY_TESTME(points[i++] == Point2d(-155.866656, 257.679820));
   TRY_TESTME(points[i++] == Point2d(-146.114325, 265.393224));
   TRY_TESTME(points[i++] == Point2d(-136.860151, 273.697732));
   TRY_TESTME(points[i++] == Point2d(-128.139904, 282.561244));
   TRY_TESTME(points[i++] == Point2d(-119.987288, 291.949504));
   TRY_TESTME(points[i++] == Point2d(-112.433814, 301.826224));
   TRY_TESTME(points[i++] == Point2d(-105.508676, 312.153229));
   TRY_TESTME(points[i++] == Point2d(-99.238642, 322.890605));
   TRY_TESTME(points[i++] == Point2d(-93.647946, 333.996850));
   TRY_TESTME(points[i++] == Point2d(-88.758196, 345.429038));
   TRY_TESTME(points[i++] == Point2d(-84.588292, 357.142981));
   TRY_TESTME(points[i++] == Point2d(-81.154351, 369.093404));
   TRY_TESTME(points[i++] == Point2d(-78.469645, 381.234117));
   TRY_TESTME(points[i++] == Point2d(-76.544552, 393.518196));
   TRY_TESTME(points[i++] == Point2d(-75.386511, 405.898160));
   TRY_TESTME(points[i++] == Point2d(-75.000000, 418.326160));
   TRY_TESTME(points[i++] == Point2d(-75.000000, 2106.044491));
   TRY_TESTME(points[i++] == Point2d(-75.552738, 2120.903489));
   TRY_TESTME(points[i++] == Point2d(-77.207898, 2135.680355));
   TRY_TESTME(points[i++] == Point2d(-79.956331, 2150.293413));
   TRY_TESTME(points[i++] == Point2d(-83.782845, 2164.661891));
   TRY_TESTME(points[i++] == Point2d(-88.666289, 2178.706367));
   TRY_TESTME(points[i++] == Point2d(-94.579672, 2192.349213));
   TRY_TESTME(points[i++] == Point2d(-101.490306, 2205.515020));
   TRY_TESTME(points[i++] == Point2d(-109.359996, 2218.131015));
   TRY_TESTME(points[i++] == Point2d(-118.145241, 2230.127465));
   TRY_TESTME(points[i++] == Point2d(-127.797483, 2241.438061));
   TRY_TESTME(points[i++] == Point2d(-138.263369, 2252.000284));
   TRY_TESTME(points[i++] == Point2d(-149.485051, 2261.755754));
   TRY_TESTME(points[i++] == Point2d(-161.400503, 2270.650548));
   TRY_TESTME(points[i++] == Point2d(-173.943862, 2278.635501));
   TRY_TESTME(points[i++] == Point2d(-187.045798, 2285.666478));
   TRY_TESTME(points[i++] == Point2d(-200.633890, 2291.704615));
   TRY_TESTME(points[i++] == Point2d(-214.633032, 2296.716537));
   TRY_TESTME(points[i++] == Point2d(-228.965846, 2300.674541));
   TRY_TESTME(points[i++] == Point2d(-243.553108, 2303.556751));
   TRY_TESTME(points[i++] == Point2d(-258.314189, 2305.347234));
   TRY_TESTME(points[i++] == Point2d(-566.671453, 2331.163191));
   TRY_TESTME(points[i++] == Point2d(-570.361723, 2331.610812));
   TRY_TESTME(points[i++] == Point2d(-574.008539, 2332.331365));
   TRY_TESTME(points[i++] == Point2d(-577.591742, 2333.320866));
   TRY_TESTME(points[i++] == Point2d(-581.091527, 2334.573846));
   TRY_TESTME(points[i++] == Point2d(-584.488551, 2336.083381));
   TRY_TESTME(points[i++] == Point2d(-587.764034, 2337.841125));
   TRY_TESTME(points[i++] == Point2d(-590.899874, 2339.837363));
   TRY_TESTME(points[i++] == Point2d(-593.878737, 2342.061061));
   TRY_TESTME(points[i++] == Point2d(-596.684158, 2344.499929));
   TRY_TESTME(points[i++] == Point2d(-599.300629, 2347.140485));
   TRY_TESTME(points[i++] == Point2d(-601.713690, 2349.968134));
   TRY_TESTME(points[i++] == Point2d(-603.910001, 2352.967246));
   TRY_TESTME(points[i++] == Point2d(-605.877423, 2356.121245));
   TRY_TESTME(points[i++] == Point2d(-607.605082, 2359.412697));
   TRY_TESTME(points[i++] == Point2d(-609.083428, 2362.823408));
   TRY_TESTME(points[i++] == Point2d(-610.304289, 2366.334527));
   TRY_TESTME(points[i++] == Point2d(-611.260917, 2369.926647));
   TRY_TESTME(points[i++] == Point2d(-611.948025, 2373.579911));
   TRY_TESTME(points[i++] == Point2d(-612.361815, 2377.274128));
   TRY_TESTME(points[i++] == Point2d(-612.500000, 2380.988877));
   TRY_TESTME(points[i++] == Point2d(-612.500000, 2400.000000));
   TRY_TESTME(points[i++] == Point2d(0.000000, 2400.000000));
   TRY_TESTME(points[i++] == Point2d(612.500000, 2400.000000));
   TRY_TESTME(points[i++] == Point2d(612.500000, 2380.988877));
   TRY_TESTME(points[i++] == Point2d(612.361815, 2377.274128));
   TRY_TESTME(points[i++] == Point2d(611.948025, 2373.579911));
   TRY_TESTME(points[i++] == Point2d(611.260917, 2369.926647));
   TRY_TESTME(points[i++] == Point2d(610.304289, 2366.334527));
   TRY_TESTME(points[i++] == Point2d(609.083428, 2362.823408));
   TRY_TESTME(points[i++] == Point2d(607.605082, 2359.412697));
   TRY_TESTME(points[i++] == Point2d(605.877423, 2356.121245));
   TRY_TESTME(points[i++] == Point2d(603.910001, 2352.967246));
   TRY_TESTME(points[i++] == Point2d(601.713690, 2349.968134));
   TRY_TESTME(points[i++] == Point2d(599.300629, 2347.140485));
   TRY_TESTME(points[i++] == Point2d(596.684158, 2344.499929));
   TRY_TESTME(points[i++] == Point2d(593.878737, 2342.061061));
   TRY_TESTME(points[i++] == Point2d(590.899874, 2339.837363));
   TRY_TESTME(points[i++] == Point2d(587.764034, 2337.841125));
   TRY_TESTME(points[i++] == Point2d(584.488551, 2336.083381));
   TRY_TESTME(points[i++] == Point2d(581.091527, 2334.573846));
   TRY_TESTME(points[i++] == Point2d(577.591742, 2333.320866));
   TRY_TESTME(points[i++] == Point2d(574.008539, 2332.331365));
   TRY_TESTME(points[i++] == Point2d(570.361723, 2331.610812));
   TRY_TESTME(points[i++] == Point2d(566.671453, 2331.163191));
   TRY_TESTME(points[i++] == Point2d(258.314189, 2305.347234));
   TRY_TESTME(points[i++] == Point2d(243.553108, 2303.556751));
   TRY_TESTME(points[i++] == Point2d(228.965846, 2300.674541));
   TRY_TESTME(points[i++] == Point2d(214.633032, 2296.716537));
   TRY_TESTME(points[i++] == Point2d(200.633890, 2291.704615));
   TRY_TESTME(points[i++] == Point2d(187.045798, 2285.666478));
   TRY_TESTME(points[i++] == Point2d(173.943862, 2278.635501));
   TRY_TESTME(points[i++] == Point2d(161.400503, 2270.650548));
   TRY_TESTME(points[i++] == Point2d(149.485051, 2261.755754));
   TRY_TESTME(points[i++] == Point2d(138.263369, 2252.000284));
   TRY_TESTME(points[i++] == Point2d(127.797483, 2241.438061));
   TRY_TESTME(points[i++] == Point2d(118.145241, 2230.127465));
   TRY_TESTME(points[i++] == Point2d(109.359996, 2218.131015));
   TRY_TESTME(points[i++] == Point2d(101.490306, 2205.515020));
   TRY_TESTME(points[i++] == Point2d(94.579672, 2192.349213));
   TRY_TESTME(points[i++] == Point2d(88.666289, 2178.706367));
   TRY_TESTME(points[i++] == Point2d(83.782845, 2164.661891));
   TRY_TESTME(points[i++] == Point2d(79.956331, 2150.293413));
   TRY_TESTME(points[i++] == Point2d(77.207898, 2135.680355));
   TRY_TESTME(points[i++] == Point2d(75.552738, 2120.903489));
   TRY_TESTME(points[i++] == Point2d(75.000000, 2106.044491));
   TRY_TESTME(points[i++] == Point2d(75.000000, 418.326160));
   TRY_TESTME(points[i++] == Point2d(75.386511, 405.898160));
   TRY_TESTME(points[i++] == Point2d(76.544552, 393.518196));
   TRY_TESTME(points[i++] == Point2d(78.469645, 381.234117));
   TRY_TESTME(points[i++] == Point2d(81.154351, 369.093404));
   TRY_TESTME(points[i++] == Point2d(84.588292, 357.142981));
   TRY_TESTME(points[i++] == Point2d(88.758196, 345.429038));
   TRY_TESTME(points[i++] == Point2d(93.647946, 333.996850));
   TRY_TESTME(points[i++] == Point2d(99.238642, 322.890605));
   TRY_TESTME(points[i++] == Point2d(105.508676, 312.153229));
   TRY_TESTME(points[i++] == Point2d(112.433814, 301.826224));
   TRY_TESTME(points[i++] == Point2d(119.987288, 291.949504));
   TRY_TESTME(points[i++] == Point2d(128.139904, 282.561244));
   TRY_TESTME(points[i++] == Point2d(136.860151, 273.697732));
   TRY_TESTME(points[i++] == Point2d(146.114325, 265.393224));
   TRY_TESTME(points[i++] == Point2d(155.866656, 257.679820));
   TRY_TESTME(points[i++] == Point2d(166.079451, 250.587333));
   TRY_TESTME(points[i++] == Point2d(176.713237, 244.143175));
   TRY_TESTME(points[i++] == Point2d(187.726912, 238.372254));
   TRY_TESTME(points[i++] == Point2d(199.077907, 233.296876));
   TRY_TESTME(points[i++] == Point2d(210.722351, 228.936657));
   TRY_TESTME(points[i++] == Point2d(453.569412, 146.515836));
   TRY_TESTME(points[i++] == Point2d(456.480523, 145.425781));
   TRY_TESTME(points[i++] == Point2d(459.318272, 144.156936));
   TRY_TESTME(points[i++] == Point2d(462.071691, 142.714206));
   TRY_TESTME(points[i++] == Point2d(464.730137, 141.103167));
   TRY_TESTME(points[i++] == Point2d(467.283336, 139.330045));
   TRY_TESTME(points[i++] == Point2d(469.721419, 137.401694));
   TRY_TESTME(points[i++] == Point2d(472.034962, 135.325567));
   TRY_TESTME(points[i++] == Point2d(474.215024, 133.109689));
   TRY_TESTME(points[i++] == Point2d(476.253178, 130.762624));
   TRY_TESTME(points[i++] == Point2d(478.141547, 128.293444));
   TRY_TESTME(points[i++] == Point2d(479.872831, 125.711693));
   TRY_TESTME(points[i++] == Point2d(481.440339, 123.027349));
   TRY_TESTME(points[i++] == Point2d(482.838014, 120.250787));
   TRY_TESTME(points[i++] == Point2d(484.060451, 117.392741));
   TRY_TESTME(points[i++] == Point2d(485.102927, 114.464255));
   TRY_TESTME(points[i++] == Point2d(485.961412, 111.476649));
   TRY_TESTME(points[i++] == Point2d(486.632589, 108.441471));
   TRY_TESTME(points[i++] == Point2d(487.113862, 105.370451));
   TRY_TESTME(points[i++] == Point2d(487.403372, 102.275460));
   TRY_TESTME(points[i++] == Point2d(487.500000, 99.168460));
   TRY_TESTME(points[i++] == Point2d(487.500000, 0.000000));
   TRY_TESTME(i == points.size());

   //
   // LocatorPoint property
   //
   auto hookPnt = beam.GetHookPoint();

   // BottomLeft
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::BottomLeft, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::BottomLeft);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(712.5, 100.0));

   // BottomCenter
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::BottomCenter, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::BottomCenter);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(100.0, 100.0));

   // BottomRight
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::BottomRight, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::BottomRight);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(-512.5, 100.0));

   // CenterLeft
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::CenterLeft, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::CenterLeft);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(712.5, -1100.0));

   // CenterCenter
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::CenterCenter, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::CenterCenter);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(100.0, -1100.0));

   // CenterRight
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::CenterRight, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::CenterRight);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(-512.5, -1100.0));

   // TopLeft
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::TopLeft, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::TopLeft);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(712.5, -2300.0));

   // TopCenter
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::TopCenter, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::TopCenter);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(100.0, -2300.0));

   // TopRight
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::TopRight, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::TopRight);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(-512.5, -2300.0));

   // HookPoint
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::HookPoint, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::HookPoint);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(100.0, 100.0));

   //
   // RotateEx (Provides coverage of Rotate)
   //
   hookPnt->Move(0, 0);
   Point2d c(0, 0);

   beam.Rotate(c, M_PI);

   points = beam.GetPolyPoints();
   TRY_TESTME(points.size() == 174);
   i = 0;
   TRY_TESTME(points[i++] == Point2d(0.000000, 0.000000));
   TRY_TESTME(points[i++] == Point2d(487.500000, -0.000000));
   TRY_TESTME(points[i++] == Point2d(487.500000, -99.168460));
   TRY_TESTME(points[i++] == Point2d(487.403372, -102.275460));
   TRY_TESTME(points[i++] == Point2d(487.113862, -105.370451));
   TRY_TESTME(points[i++] == Point2d(486.632589, -108.441471));
   TRY_TESTME(points[i++] == Point2d(485.961412, -111.476649));
   TRY_TESTME(points[i++] == Point2d(485.102927, -114.464255));
   TRY_TESTME(points[i++] == Point2d(484.060451, -117.392741));
   TRY_TESTME(points[i++] == Point2d(482.838014, -120.250787));
   TRY_TESTME(points[i++] == Point2d(481.440339, -123.027349));
   TRY_TESTME(points[i++] == Point2d(479.872831, -125.711693));
   TRY_TESTME(points[i++] == Point2d(478.141547, -128.293444));
   TRY_TESTME(points[i++] == Point2d(476.253178, -130.762624));
   TRY_TESTME(points[i++] == Point2d(474.215024, -133.109689));
   TRY_TESTME(points[i++] == Point2d(472.034962, -135.325567));
   TRY_TESTME(points[i++] == Point2d(469.721419, -137.401694));
   TRY_TESTME(points[i++] == Point2d(467.283336, -139.330045));
   TRY_TESTME(points[i++] == Point2d(464.730137, -141.103167));
   TRY_TESTME(points[i++] == Point2d(462.071691, -142.714206));
   TRY_TESTME(points[i++] == Point2d(459.318272, -144.156936));
   TRY_TESTME(points[i++] == Point2d(456.480523, -145.425781));
   TRY_TESTME(points[i++] == Point2d(453.569412, -146.515836));
   TRY_TESTME(points[i++] == Point2d(210.722351, -228.936657));
   TRY_TESTME(points[i++] == Point2d(199.077907, -233.296876));
   TRY_TESTME(points[i++] == Point2d(187.726912, -238.372254));
   TRY_TESTME(points[i++] == Point2d(176.713237, -244.143175));
   TRY_TESTME(points[i++] == Point2d(166.079451, -250.587333));
   TRY_TESTME(points[i++] == Point2d(155.866656, -257.679820));
   TRY_TESTME(points[i++] == Point2d(146.114325, -265.393224));
   TRY_TESTME(points[i++] == Point2d(136.860151, -273.697732));
   TRY_TESTME(points[i++] == Point2d(128.139904, -282.561244));
   TRY_TESTME(points[i++] == Point2d(119.987288, -291.949504));
   TRY_TESTME(points[i++] == Point2d(112.433814, -301.826224));
   TRY_TESTME(points[i++] == Point2d(105.508676, -312.153229));
   TRY_TESTME(points[i++] == Point2d(99.238642, -322.890605));
   TRY_TESTME(points[i++] == Point2d(93.647946, -333.996850));
   TRY_TESTME(points[i++] == Point2d(88.758196, -345.429038));
   TRY_TESTME(points[i++] == Point2d(84.588292, -357.142981));
   TRY_TESTME(points[i++] == Point2d(81.154351, -369.093404));
   TRY_TESTME(points[i++] == Point2d(78.469645, -381.234117));
   TRY_TESTME(points[i++] == Point2d(76.544552, -393.518196));
   TRY_TESTME(points[i++] == Point2d(75.386511, -405.898160));
   TRY_TESTME(points[i++] == Point2d(75.000000, -418.326160));
   TRY_TESTME(points[i++] == Point2d(75.000000, -2106.044491));
   TRY_TESTME(points[i++] == Point2d(75.552738, -2120.903489));
   TRY_TESTME(points[i++] == Point2d(77.207898, -2135.680355));
   TRY_TESTME(points[i++] == Point2d(79.956331, -2150.293413));
   TRY_TESTME(points[i++] == Point2d(83.782845, -2164.661891));
   TRY_TESTME(points[i++] == Point2d(88.666289, -2178.706367));
   TRY_TESTME(points[i++] == Point2d(94.579672, -2192.349213));
   TRY_TESTME(points[i++] == Point2d(101.490306, -2205.515020));
   TRY_TESTME(points[i++] == Point2d(109.359996, -2218.131015));
   TRY_TESTME(points[i++] == Point2d(118.145241, -2230.127465));
   TRY_TESTME(points[i++] == Point2d(127.797483, -2241.438061));
   TRY_TESTME(points[i++] == Point2d(138.263369, -2252.000284));
   TRY_TESTME(points[i++] == Point2d(149.485051, -2261.755754));
   TRY_TESTME(points[i++] == Point2d(161.400503, -2270.650548));
   TRY_TESTME(points[i++] == Point2d(173.943862, -2278.635501));
   TRY_TESTME(points[i++] == Point2d(187.045798, -2285.666478));
   TRY_TESTME(points[i++] == Point2d(200.633890, -2291.704615));
   TRY_TESTME(points[i++] == Point2d(214.633032, -2296.716537));
   TRY_TESTME(points[i++] == Point2d(228.965846, -2300.674541));
   TRY_TESTME(points[i++] == Point2d(243.553108, -2303.556751));
   TRY_TESTME(points[i++] == Point2d(258.314189, -2305.347234));
   TRY_TESTME(points[i++] == Point2d(566.671453, -2331.163191));
   TRY_TESTME(points[i++] == Point2d(570.361723, -2331.610812));
   TRY_TESTME(points[i++] == Point2d(574.008539, -2332.331365));
   TRY_TESTME(points[i++] == Point2d(577.591742, -2333.320866));
   TRY_TESTME(points[i++] == Point2d(581.091527, -2334.573846));
   TRY_TESTME(points[i++] == Point2d(584.488551, -2336.083381));
   TRY_TESTME(points[i++] == Point2d(587.764034, -2337.841125));
   TRY_TESTME(points[i++] == Point2d(590.899874, -2339.837363));
   TRY_TESTME(points[i++] == Point2d(593.878737, -2342.061061));
   TRY_TESTME(points[i++] == Point2d(596.684158, -2344.499929));
   TRY_TESTME(points[i++] == Point2d(599.300629, -2347.140485));
   TRY_TESTME(points[i++] == Point2d(601.713690, -2349.968134));
   TRY_TESTME(points[i++] == Point2d(603.910001, -2352.967246));
   TRY_TESTME(points[i++] == Point2d(605.877423, -2356.121245));
   TRY_TESTME(points[i++] == Point2d(607.605082, -2359.412697));
   TRY_TESTME(points[i++] == Point2d(609.083428, -2362.823408));
   TRY_TESTME(points[i++] == Point2d(610.304289, -2366.334527));
   TRY_TESTME(points[i++] == Point2d(611.260917, -2369.926647));
   TRY_TESTME(points[i++] == Point2d(611.948025, -2373.579911));
   TRY_TESTME(points[i++] == Point2d(612.361815, -2377.274128));
   TRY_TESTME(points[i++] == Point2d(612.500000, -2380.988877));
   TRY_TESTME(points[i++] == Point2d(612.500000, -2400.000000));
   TRY_TESTME(points[i++] == Point2d(-0.000000, -2400.000000));
   TRY_TESTME(points[i++] == Point2d(-612.500000, -2400.000000));
   TRY_TESTME(points[i++] == Point2d(-612.500000, -2380.988877));
   TRY_TESTME(points[i++] == Point2d(-612.361815, -2377.274128));
   TRY_TESTME(points[i++] == Point2d(-611.948025, -2373.579911));
   TRY_TESTME(points[i++] == Point2d(-611.260917, -2369.926647));
   TRY_TESTME(points[i++] == Point2d(-610.304289, -2366.334527));
   TRY_TESTME(points[i++] == Point2d(-609.083428, -2362.823408));
   TRY_TESTME(points[i++] == Point2d(-607.605082, -2359.412697));
   TRY_TESTME(points[i++] == Point2d(-605.877423, -2356.121245));
   TRY_TESTME(points[i++] == Point2d(-603.910001, -2352.967246));
   TRY_TESTME(points[i++] == Point2d(-601.713690, -2349.968134));
   TRY_TESTME(points[i++] == Point2d(-599.300629, -2347.140485));
   TRY_TESTME(points[i++] == Point2d(-596.684158, -2344.499929));
   TRY_TESTME(points[i++] == Point2d(-593.878737, -2342.061061));
   TRY_TESTME(points[i++] == Point2d(-590.899874, -2339.837363));
   TRY_TESTME(points[i++] == Point2d(-587.764034, -2337.841125));
   TRY_TESTME(points[i++] == Point2d(-584.488551, -2336.083381));
   TRY_TESTME(points[i++] == Point2d(-581.091527, -2334.573846));
   TRY_TESTME(points[i++] == Point2d(-577.591742, -2333.320866));
   TRY_TESTME(points[i++] == Point2d(-574.008539, -2332.331365));
   TRY_TESTME(points[i++] == Point2d(-570.361723, -2331.610812));
   TRY_TESTME(points[i++] == Point2d(-566.671453, -2331.163191));
   TRY_TESTME(points[i++] == Point2d(-258.314189, -2305.347234));
   TRY_TESTME(points[i++] == Point2d(-243.553108, -2303.556751));
   TRY_TESTME(points[i++] == Point2d(-228.965846, -2300.674541));
   TRY_TESTME(points[i++] == Point2d(-214.633032, -2296.716537));
   TRY_TESTME(points[i++] == Point2d(-200.633890, -2291.704615));
   TRY_TESTME(points[i++] == Point2d(-187.045798, -2285.666478));
   TRY_TESTME(points[i++] == Point2d(-173.943862, -2278.635501));
   TRY_TESTME(points[i++] == Point2d(-161.400503, -2270.650548));
   TRY_TESTME(points[i++] == Point2d(-149.485051, -2261.755754));
   TRY_TESTME(points[i++] == Point2d(-138.263369, -2252.000284));
   TRY_TESTME(points[i++] == Point2d(-127.797483, -2241.438061));
   TRY_TESTME(points[i++] == Point2d(-118.145241, -2230.127465));
   TRY_TESTME(points[i++] == Point2d(-109.359996, -2218.131015));
   TRY_TESTME(points[i++] == Point2d(-101.490306, -2205.515020));
   TRY_TESTME(points[i++] == Point2d(-94.579672, -2192.349213));
   TRY_TESTME(points[i++] == Point2d(-88.666289, -2178.706367));
   TRY_TESTME(points[i++] == Point2d(-83.782845, -2164.661891));
   TRY_TESTME(points[i++] == Point2d(-79.956331, -2150.293413));
   TRY_TESTME(points[i++] == Point2d(-77.207898, -2135.680355));
   TRY_TESTME(points[i++] == Point2d(-75.552738, -2120.903489));
   TRY_TESTME(points[i++] == Point2d(-75.000000, -2106.044491));
   TRY_TESTME(points[i++] == Point2d(-75.000000, -418.326160));
   TRY_TESTME(points[i++] == Point2d(-75.386511, -405.898160));
   TRY_TESTME(points[i++] == Point2d(-76.544552, -393.518196));
   TRY_TESTME(points[i++] == Point2d(-78.469645, -381.234117));
   TRY_TESTME(points[i++] == Point2d(-81.154351, -369.093404));
   TRY_TESTME(points[i++] == Point2d(-84.588292, -357.142981));
   TRY_TESTME(points[i++] == Point2d(-88.758196, -345.429038));
   TRY_TESTME(points[i++] == Point2d(-93.647946, -333.996850));
   TRY_TESTME(points[i++] == Point2d(-99.238642, -322.890605));
   TRY_TESTME(points[i++] == Point2d(-105.508676, -312.153229));
   TRY_TESTME(points[i++] == Point2d(-112.433814, -301.826224));
   TRY_TESTME(points[i++] == Point2d(-119.987288, -291.949504));
   TRY_TESTME(points[i++] == Point2d(-128.139904, -282.561244));
   TRY_TESTME(points[i++] == Point2d(-136.860151, -273.697732));
   TRY_TESTME(points[i++] == Point2d(-146.114325, -265.393224));
   TRY_TESTME(points[i++] == Point2d(-155.866656, -257.679820));
   TRY_TESTME(points[i++] == Point2d(-166.079451, -250.587333));
   TRY_TESTME(points[i++] == Point2d(-176.713237, -244.143175));
   TRY_TESTME(points[i++] == Point2d(-187.726912, -238.372254));
   TRY_TESTME(points[i++] == Point2d(-199.077907, -233.296876));
   TRY_TESTME(points[i++] == Point2d(-210.722351, -228.936657));
   TRY_TESTME(points[i++] == Point2d(-453.569412, -146.515836));
   TRY_TESTME(points[i++] == Point2d(-456.480523, -145.425781));
   TRY_TESTME(points[i++] == Point2d(-459.318272, -144.156936));
   TRY_TESTME(points[i++] == Point2d(-462.071691, -142.714206));
   TRY_TESTME(points[i++] == Point2d(-464.730137, -141.103167));
   TRY_TESTME(points[i++] == Point2d(-467.283336, -139.330045));
   TRY_TESTME(points[i++] == Point2d(-469.721419, -137.401694));
   TRY_TESTME(points[i++] == Point2d(-472.034962, -135.325567));
   TRY_TESTME(points[i++] == Point2d(-474.215024, -133.109689));
   TRY_TESTME(points[i++] == Point2d(-476.253178, -130.762624));
   TRY_TESTME(points[i++] == Point2d(-478.141547, -128.293444));
   TRY_TESTME(points[i++] == Point2d(-479.872831, -125.711693));
   TRY_TESTME(points[i++] == Point2d(-481.440339, -123.027349));
   TRY_TESTME(points[i++] == Point2d(-482.838014, -120.250787));
   TRY_TESTME(points[i++] == Point2d(-484.060451, -117.392741));
   TRY_TESTME(points[i++] == Point2d(-485.102927, -114.464255));
   TRY_TESTME(points[i++] == Point2d(-485.961412, -111.476649));
   TRY_TESTME(points[i++] == Point2d(-486.632589, -108.441471));
   TRY_TESTME(points[i++] == Point2d(-487.113862, -105.370451));
   TRY_TESTME(points[i++] == Point2d(-487.403372, -102.275460));
   TRY_TESTME(points[i++] == Point2d(-487.500000, -99.168460));
   TRY_TESTME(points[i++] == Point2d(-487.500000, 0.000000));
   TRY_TESTME(i == points.size());

   // Test hook point behavior
   TRY_TESTME(UnitTest::TestHookPoint(beam) == true);

   TESTME_EPILOG("NUBeam");
}

#endif // _UNITTEST


