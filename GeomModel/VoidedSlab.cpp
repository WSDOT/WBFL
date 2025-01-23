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
#include <GeomModel/VoidedSlab.h>
#include <GeomModel/ShapeProperties.h>
#include <GeomModel/Rectangle.h>
#include <GeomModel/Circle.h>
#include <MathEx.h>

using namespace WBFL::Geometry;

VoidedSlab::VoidedSlab() :
   ShapeOnCompositeImpl()
{
}

VoidedSlab::VoidedSlab(Float64 h, Float64 w, Float64 d, Float64 s, IndexType nVoids, std::shared_ptr<Point2d>& hookPnt) :
   ShapeOnCompositeImpl(hookPnt), m_H(h),m_W(w),m_D(d), m_S(s), m_nVoids(nVoids)
{
}

VoidedSlab::~VoidedSlab()
{
}

void VoidedSlab::SetHeight(Float64 h)
{
   m_H = h;
   SetDirtyFlag();
}

Float64 VoidedSlab::GetHeight() const
{
   return m_H;
}

void VoidedSlab::SetWidth(Float64 width)
{
   m_W = width;
   SetDirtyFlag();
}

Float64 VoidedSlab::GetWidth() const
{
   return m_W;
}

void VoidedSlab::SetVoidDiameter(Float64 d)
{
   m_D = d;
   SetDirtyFlag();
}

Float64 VoidedSlab::GetVoidDiameter() const
{
   return m_D;
}

void VoidedSlab::SetVoidSpacing(Float64 s)
{
   m_S = s;
   SetDirtyFlag();
}

Float64 VoidedSlab::GetVoidSpacing() const
{
   return m_S;
}

void VoidedSlab::SetVoidCount(IndexType nVoids)
{
   m_nVoids = nVoids;
   SetDirtyFlag();
}

IndexType VoidedSlab::GetVoidCount() const
{
   return m_nVoids;
}

void VoidedSlab::Offset(const Size2d& delta)
{
   GetHookPoint()->Offset(delta);
   SetDirtyFlag();
}

void VoidedSlab::Rotate(const Point2d& center, Float64 angle)
{
   m_Rotation += angle;
   GetHookPoint()->Rotate(center, angle);
   SetDirtyFlag();
}

std::unique_ptr<Shape> VoidedSlab::CreateClone() const
{
   return std::make_unique<VoidedSlab>(*this);
}

std::shared_ptr<Shape> VoidedSlab::GetSlabShape() const
{
   return GetComposite()->GetShape(0);
}

std::shared_ptr<Shape> VoidedSlab::GetVoidShape(IndexType voidIdx) const
{
   if (m_nVoids <= voidIdx)
      THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);

   return GetComposite()->GetShape(voidIdx + 1);
}

void VoidedSlab::OnUpdateComposite(std::unique_ptr<CompositeShape>& composite) const
{
   Rectangle slab(Point2d(0,0), m_W, m_H);
   composite->AddShape(slab);

   if (0 < m_nVoids)
   {
      Float64 x = -m_S * (m_nVoids - 1) / 2;
      Float64 y = 0;
      Float64 r = m_D / 2;
      for (IndexType i = 0; i < m_nVoids; i++)
      {
         Circle hole(Point2d(x, y), r);
         composite->AddShape(hole, CompositeShape::ShapeType::Void);

         x += m_S;
      }
   }

   // move the shape so that the bottom center is at (0,0)
   // this is the hook point
   composite->Offset(Size2d(0.0, m_H / 2));

   if (!IsZero(m_Rotation))
      composite->Rotate(Point2d(0, 0), m_Rotation);

   composite->Move(Point2d(0, 0), *GetHookPoint());
}
