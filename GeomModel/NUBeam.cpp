///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
// Copyright © 1999-2025  Washington State Department of Transportation
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
   if (0 < flangeIdx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);
   return 0.0;
}

Float64 NUBeam::GetTopFlangeWidth(IndexType flangeIdx) const
{
   if (0 < flangeIdx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);
   return m_W1;
}

IndexType NUBeam::GetBottomFlangeCount() const
{
   return 1;
}

Float64 NUBeam::GetBottomFlangeLocation(IndexType flangeIdx) const
{
   if (0 < flangeIdx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);
   return 0.0;
}

Float64 NUBeam::GetBottomFlangeWidth(IndexType flangeIdx) const
{
   if (0 < flangeIdx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);
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
   if (0 < webIdx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);
   return GetTopWidth();
}

Float64 NUBeam::GetMatingSurfaceLocation(MatingSurfaceIndexType webIdx) const
{
   if (0 < webIdx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);
   return 0;
}

IndexType NUBeam::GetWebCount() const
{
   return 1;
}

Plane3d NUBeam::GetWebPlane(WebIndexType webIdx) const
{
   if (0 < webIdx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);
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
