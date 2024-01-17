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
// Olympia, WA 98703, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#include <GeomModel/GeomModelLib.h>
#include <GeomModel/PCIDeckedIBeam.h>
#include <GeomModel/ShapeProperties.h>
#include <GeomModel/Polygon.h>
#include <GeomModel/Primitives3d.h>
#include <MathEx.h>
#include "Helpers.h"

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
   if (0 < flangeIdx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);
   return 0.0;
}

Float64 PCIDeckedIBeam::GetTopFlangeWidth(IndexType flangeIdx) const
{
   if (0 < flangeIdx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);
   return GetTopWidth();
}

IndexType PCIDeckedIBeam::GetBottomFlangeCount() const
{
   return 1;
}

Float64 PCIDeckedIBeam::GetBottomFlangeLocation(IndexType flangeIdx) const
{
   if (0 < flangeIdx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);
   return 0.0;
}

Float64 PCIDeckedIBeam::GetBottomFlangeWidth(IndexType flangeIdx) const
{
   if (0 < flangeIdx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);
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
   if (0 < idx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);
   return GetTopWidth();
}

Float64 PCIDeckedIBeam::GetMatingSurfaceLocation(MatingSurfaceIndexType idx) const
{
   if (0 < idx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);
   return 0;
}

IndexType PCIDeckedIBeam::GetWebCount() const
{
   return 1;
}

Plane3d PCIDeckedIBeam::GetWebPlane(WebIndexType webIdx) const
{
   if (0 < webIdx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);
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
