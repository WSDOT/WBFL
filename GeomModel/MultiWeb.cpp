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
#include <GeomModel/MultiWeb.h>
#include <GeomModel/ShapeProperties.h>
#include <GeomModel/Polygon.h>
#include <MathEx.h>

using namespace WBFL::Geometry;

MultiWeb::MultiWeb() :
   ShapeOnPolygonImpl()
{
}

MultiWeb::MultiWeb(Float64 w1, Float64 w2, Float64 d1, Float64 d2, Float64 t1, Float64 t2, IndexType nWebs, std::shared_ptr<Point2d>& hookPnt) :
   ShapeOnPolygonImpl(hookPnt), m_W1(w1),m_W2(w2),m_D1(d1), m_D2(d2), m_T1(t1), m_T2(t2), m_WebCount(nWebs)
{
}

MultiWeb::~MultiWeb()
{
}

void MultiWeb::SetW1(Float64 w1)
{
   m_W1 = w1;
   SetDirtyFlag();
}

Float64 MultiWeb::GetW1() const
{
   return m_W1;
}

void MultiWeb::SetW2(Float64 w2)
{
   m_W2 = w2;
   SetDirtyFlag();
}

Float64 MultiWeb::GetW2() const
{
   return m_W2;
}

void MultiWeb::SetD1(Float64 d1)
{
   m_D1 = d1;
   SetDirtyFlag();
}

Float64 MultiWeb::GetD1() const
{
   return m_D1;
}

void MultiWeb::SetD2(Float64 d2)
{
   m_D2 = d2;
   SetDirtyFlag();
}

Float64 MultiWeb::GetD2() const
{
   return m_D2;
}

void MultiWeb::SetT1(Float64 t1)
{
   m_T1 = t1;
   SetDirtyFlag();
}

Float64 MultiWeb::GetT1() const
{
   return m_T1;
}

void MultiWeb::SetT2(Float64 t2)
{
   m_T2 = t2;
   SetDirtyFlag();
}

Float64 MultiWeb::GetT2() const
{
   return m_T2;
}

void MultiWeb::SetWebCount(WebIndexType nWebs)
{
   m_WebCount = nWebs;
   SetDirtyFlag();
}

WebIndexType MultiWeb::GetWebCount() const
{
   return m_WebCount;
}

Float64 MultiWeb::GetWebLocation(WebIndexType webIdx)
{
   if (m_WebCount <= webIdx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);

   Float64 W = GetTopFlangeWidth();

   return (m_W1 + webIdx * (m_W2 + m_T1) + m_T1 / 2) - W / 2;
}

Float64 MultiWeb::GetTopFlangeWidth() const
{
   return 2 * m_W1 + m_WebCount * m_T1 + (m_WebCount - 1) * m_W2;
}

Float64 MultiWeb::GetAvgWebWidth() const
{
   return m_WebCount * (m_T1 + m_T2) / 2.;
}

Float64 MultiWeb::GetHeight() const
{
   return m_D1 + m_D2;
}

void MultiWeb::DoOffset(const Size2d& delta)
{
   GetHookPoint()->Offset(delta);
   SetDirtyFlag();
}

void MultiWeb::DoRotate(const Point2d& center, Float64 angle)
{
   m_Rotation += angle;

   // our shape uses symmetry - once the shape is rotated, symmetry with the Y axis is broken
   // rotating the polygon causes the full set of points to be modeled and the symmetry 
   // property set to None
   GetPolygon()->Rotate(center, angle);
   SetDirtyFlag();
}

std::unique_ptr<Shape> MultiWeb::CreateClone() const
{
   return std::make_unique<MultiWeb>(*this);
}

void MultiWeb::OnUpdatePolygon(std::unique_ptr<Polygon>& polygon) const
{
   Float64 width = 2 * m_W1 + m_WebCount * m_T1 + (m_WebCount - 1) * m_W2;

   polygon->AddPoint(0, 0); // top center
   polygon->AddPoint(-width / 2, 0); // top left
   polygon->AddPoint(-width / 2, -m_D1);

   WebIndexType nFullWebs = (m_WebCount < 2 ? 0 : m_WebCount / 2);
   WebIndexType nHalfWebs = (nFullWebs == 0 ? 0 : m_WebCount / 2 - nFullWebs + IsOdd(m_WebCount) ? 1 : 0);
   for (WebIndexType i = 0; i < nFullWebs; i++)
   {
      Float64 web_x1 = -width/2 + m_W1 + i * (m_W2 + m_T1);
      Float64 web_y1 = -m_D1;

      Float64 web_x2 = web_x1 + m_T1 / 2 - m_T2 / 2;
      Float64 web_y2 = -m_D1 - m_D2;

      Float64 web_x3 = web_x2 + m_T2;
      Float64 web_y3 = -m_D1 - m_D2;

      Float64 web_x4 = web_x1 + m_T1;
      Float64 web_y4 = -m_D1;

      polygon->AddPoint(web_x1, web_y1);
      polygon->AddPoint(web_x2, web_y2);
      polygon->AddPoint(web_x3, web_y3);
      polygon->AddPoint(web_x4, web_y4);

      if (nHalfWebs == 0)
         polygon->AddPoint(web_x4 + m_W2 / 2, web_y4); // point half-way to the next web
   }

   if (nHalfWebs != 0)
   {
      Float64 web_x1 = -width / 2 + m_W1 + nFullWebs * (m_T1 + m_W2);
      Float64 web_y1 = -m_D1;

      Float64 web_x2 = web_x1 + m_T1 / 2 - m_T2 / 2;
      Float64 web_y2 = -m_D1 - m_D2;
      polygon->AddPoint(web_x1, web_y1);
      polygon->AddPoint(web_x2, web_y2);
      polygon->AddPoint(web_x2 + m_T2 / 2, web_y2); // point at bottom-CL of web
   }

   polygon->SetSymmetry(Polygon::Symmetry::Y);

   if (!IsZero(m_Rotation))
      polygon->Rotate(Point2d(0, 0), m_Rotation);

   polygon->Move(Point2d(0, 0), *GetHookPoint());
}
