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
#include <GeomModel/FIBeam.h>
#include <GeomModel/ShapeProperties.h>
#include <GeomModel/Polygon.h>
#include <GeomModel/Primitives3d.h>
#include <MathEx.h>
#include "Helpers.h"

using namespace WBFL::Geometry;


void GenerateFillet(std::vector<Point2d>& vPoints, Float64 cx, Float64 cy, Float64 r, Float64 startAngle, Float64 delta, long nSpaces)
{
   if (!IsZero(r))
   {
      Float64 dAngle = delta / nSpaces;
      for (long i = 0; i <= nSpaces; i++)
      {
         Float64 x = cx + r * cos(startAngle + i * dAngle);
         Float64 y = cy + r * sin(startAngle + i * dAngle);

         vPoints.emplace_back(x, y);
      }
   }
   else
   {
      // No radius 
      Float64 x = cx;
      Float64 y = cy;
      vPoints.emplace_back(x, y);
   }
}


FIBeam::FIBeam() : FlangedBeam()
{
}

FIBeam::FIBeam(Float64 w1, Float64 w2, Float64 w3,
                   Float64 d1, Float64 d2, Float64 d3, Float64 d4, Float64 d5,
                   Float64 h,
                   Float64 t, 
                   Float64 r,Float64 c1,
    std::shared_ptr<Point2d>& hookPnt) : FlangedBeam(hookPnt)

{
   m_W1 = w1;
   m_W2 = w2;
   m_W3 = w3;
   m_D1 = d1;
   m_D2 = d2;
   m_D3 = d3;
   m_D4 = d4;
   m_D5 = d5;
   m_H = h;
   m_T  = t;
   m_R = r;
   m_C1 = c1;
}

FIBeam::~FIBeam()
{
}

void FIBeam::SetW1(Float64 w1)
{
   PRECONDITION(w1>=0);
   m_W1 = w1;
   SetDirtyFlag();
}

Float64 FIBeam::GetW1() const
{
   return m_W1;
}

void FIBeam::SetW2(Float64 w2)
{
   PRECONDITION(w2>=0);
   m_W2 = w2;
   SetDirtyFlag();
}

Float64 FIBeam::GetW2() const
{
   return m_W2;
}

void FIBeam::SetW3(Float64 w3)
{
   PRECONDITION(w3 >= 0);
   m_W3 = w3;
   SetDirtyFlag();
}

Float64 FIBeam::GetW3() const
{
   return m_W3;
}

void FIBeam::SetD1(Float64 d1)
{
   PRECONDITION(d1>=0);
   m_D1 = d1;
   SetDirtyFlag();
}

Float64 FIBeam::GetD1() const
{
   return m_D1;
}

void FIBeam::SetD2(Float64 d2)
{
   PRECONDITION(d2>=0);
   m_D2 = d2;
   SetDirtyFlag();
}

Float64 FIBeam::GetD2() const
{
   return m_D2;
}

void FIBeam::SetD3(Float64 d3)
{
   PRECONDITION(d3>=0);
   m_D3 = d3;
   SetDirtyFlag();
}

Float64 FIBeam::GetD3() const
{
   return m_D3;
}

void FIBeam::SetD4(Float64 d4)
{
   PRECONDITION(d4>=0);
   m_D4 = d4;
   SetDirtyFlag();
}

Float64 FIBeam::GetD4() const
{
   return m_D4;
}

void FIBeam::SetD5(Float64 d5)
{
   PRECONDITION(d5>=0);
   m_D5 = d5;
   SetDirtyFlag();
}

Float64 FIBeam::GetD5() const
{
   return m_D5;
}

void FIBeam::SetT(Float64 t)
{
   PRECONDITION(t>=0);
   m_T = t;
   SetDirtyFlag();
}

Float64 FIBeam::GetT() const
{
   return m_T;
}

void FIBeam::SetH(Float64 h)
{
   PRECONDITION(h>=0);
   m_H = h;
   SetDirtyFlag();
}

Float64 FIBeam::GetH() const
{
   return m_H;
}

void FIBeam::SetR(Float64 r)
{
   PRECONDITION(r>=0);
   m_R = r;
   SetDirtyFlag();
}

Float64 FIBeam::GetR() const
{
   return m_R;
}

void FIBeam::SetC1(Float64 c1)
{
   PRECONDITION(0 <= c1);
   m_C1 = c1;
   SetDirtyFlag();
}

Float64 FIBeam::GetC1() const
{
   return m_C1;
}

Float64 FIBeam::GetHeight() const
{
   return m_H;
}

void FIBeam::DoOffset(const Size2d& delta)
{
   GetHookPoint()->Offset(delta);
   SetDirtyFlag();
}

void FIBeam::DoRotate(const Point2d& center, Float64 angle)
{
   m_Rotation += angle;
   GetHookPoint()->Rotate(center, angle);
   SetDirtyFlag();
}

IndexType FIBeam::GetTopFlangeCount() const
{
   return 1;
}

Float64 FIBeam::GetTopFlangeLocation(IndexType flangeIdx) const
{
   if (0 < flangeIdx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);
   return 0.0;
}

Float64 FIBeam::GetTopFlangeWidth(IndexType flangeIdx) const
{
   if (0 < flangeIdx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);
   return GetTopWidth();
}

IndexType FIBeam::GetBottomFlangeCount() const
{
   return 1;
}

Float64 FIBeam::GetBottomFlangeLocation(IndexType flangeIdx) const
{
   if (0 < flangeIdx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);
   return 0.0;
}

Float64 FIBeam::GetBottomFlangeWidth(IndexType flangeIdx) const
{
   if (0 < flangeIdx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);
   return GetBottomWidth();
}

Float64 FIBeam::GetTopWidth() const
{
   return 2*(m_W1 + m_W2) + m_T;
}

Float64 FIBeam::GetBottomWidth() const
{
   return m_W3;
}

MatingSurfaceIndexType FIBeam::GetMatingSurfaceCount() const
{
   return 1;
}

Float64 FIBeam::GetMatingSurfaceWidth(MatingSurfaceIndexType webIdx) const
{
   if (0 < webIdx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);
   return GetTopWidth();
}

Float64 FIBeam::GetMatingSurfaceLocation(MatingSurfaceIndexType webIdx) const
{
   if (0 < webIdx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);
   return 0;
}

IndexType FIBeam::GetWebCount() const
{
   return 1;
}

Plane3d FIBeam::GetWebPlane(WebIndexType webIdx) const
{
   if (0 < webIdx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);
   return Plane3d(0, 0, -1, 0); // vertical plane
}

Float64 FIBeam::GetShearWidth() const
{
   return GetMinWebWidth();
}

Float64 FIBeam::GetAvgWebWidth() const
{
   return m_T;
}

Float64 FIBeam::GetMinWebWidth() const
{
   return m_T;
}

Float64 FIBeam::GetMinBottomFlangeThickness() const
{
   return m_D5;
}

Float64 FIBeam::GetMinTopFlangeThickness() const
{
   return m_D1;
}

std::unique_ptr<Shape> FIBeam::CreateClone() const
{
   return std::make_unique<FIBeam>(*this);
}

void FIBeam::OnUpdatePolygon(std::unique_ptr<Polygon>& polygon) const
{
   std::vector<Point2d> vPoints;
   const long nSpaces = 100; // number of spaces used to approximate the curved fillets
   Float64 cx, cy;           // center of arc
   Float64 delta;            // sweep angle of arc
   Float64 startAngle;       // start angle for generating points along arc

   // Start at the bottom center of the shape and work clockwise to the top center
   vPoints.emplace_back(0, 0); // bottom center
   if (IsZero(m_C1))
   {
      vPoints.emplace_back(-m_W3 / 2, 0.0);
   }
   else
   {
      vPoints.emplace_back( -m_W3 / 2 + m_C1, 0.0);
      vPoints.emplace_back( -m_W3 / 2, m_C1);
   }

   vPoints.emplace_back(-m_W3 / 2, m_D4);

   // compute angle of bottom flange (measured from vertical)
   delta = atan2((m_W3 - m_T) / 2, m_D5);

   // generate lower left fillet
   cx = -m_T / 2 - m_R;
   cy = m_D5 + m_D4 + m_R * tan(delta / 2);
   startAngle = TWO_PI - delta;
   GenerateFillet(vPoints, cx, cy, m_R, startAngle, delta, nSpaces);

   // going around the top flange
   vPoints.emplace_back(-m_T / 2, m_H - m_D1 - m_D2 - m_D3);
   vPoints.emplace_back(-m_T / 2 - m_W2, m_H - m_D1 - m_D2);
   vPoints.emplace_back(-m_T / 2 - m_W2 - m_W1, m_H - m_D1);
   vPoints.emplace_back(-m_T / 2 - m_W2 - m_W1, m_H);
   vPoints.emplace_back(0, m_H);

   // put the points into the polygon - these are the left half points only
   polygon->SetPoints(vPoints);

   polygon->SetSymmetry(Polygon::Symmetry::Y);

   if (!IsZero(m_Rotation))
      polygon->Rotate(Point2d(0,0), m_Rotation);

   polygon->Move(Point2d(0, 0), *GetHookPoint());
}
