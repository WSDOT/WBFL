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
#include <GeomModel/DeckedSlabBeam.h>
#include <GeomModel/Polygon.h>
#include <MathEx.h>

using namespace WBFL::Geometry;

DeckedSlabBeam::DeckedSlabBeam() :
   ShapeOnCompositeImpl()
{
}

DeckedSlabBeam::DeckedSlabBeam(Float64 a, Float64 b, Float64 c, Float64 w, Float64 tt, Float64 tb, Float64 f, IndexType nVoids, bool bLeftBlockout, bool bRightBlockout, std::shared_ptr<Point2d>& hookPnt) :
ShapeOnCompositeImpl(hookPnt),m_A(a),m_B(b),m_C(c),m_W(w), m_Tt(tt), m_Tb(tb), m_F(f), m_nVoids(nVoids), m_bLeftBlockout(bLeftBlockout),m_bRightBlockout(bRightBlockout)
{
}

DeckedSlabBeam::DeckedSlabBeam(Float64 a, Float64 b, Float64 c, Float64 w, Float64 tt, Float64 tb, Float64 f, IndexType nVoids, bool bLeftBlockout, bool bRightBlockout, const Point2d& hookPnt) :
ShapeOnCompositeImpl(hookPnt),m_A(a), m_B(b), m_C(c), m_W(w), m_Tt(tt), m_Tb(tb), m_F(f), m_nVoids(nVoids), m_bLeftBlockout(bLeftBlockout), m_bRightBlockout(bRightBlockout)
{
}

DeckedSlabBeam::~DeckedSlabBeam()
{
}

void DeckedSlabBeam::SetA(Float64 a) { if (a < 0) THROW_GEOMETRY(WBFL_GEOMETRY_E_DIMENSION);  m_A = a; SetDirtyFlag(); }
Float64 DeckedSlabBeam::GetA() const { return m_A; }

void DeckedSlabBeam::SetB(Float64 b) { if (b < 0) THROW_GEOMETRY(WBFL_GEOMETRY_E_DIMENSION);  m_B = b; SetDirtyFlag(); }
Float64 DeckedSlabBeam::GetB() const { return m_B; }

void DeckedSlabBeam::SetC(Float64 c) { if (c < 0) THROW_GEOMETRY(WBFL_GEOMETRY_E_DIMENSION);  m_C = c; SetDirtyFlag(); }
Float64 DeckedSlabBeam::GetC() const { return m_C; }

void DeckedSlabBeam::SetW(Float64 w) { if (w < 0) THROW_GEOMETRY(WBFL_GEOMETRY_E_DIMENSION);  m_W = w; SetDirtyFlag(); }
Float64 DeckedSlabBeam::GetW() const { return m_W; }

void DeckedSlabBeam::SetTt(Float64 tt) { if (tt < 0) THROW_GEOMETRY(WBFL_GEOMETRY_E_DIMENSION);  m_Tt = tt; SetDirtyFlag(); }
Float64 DeckedSlabBeam::GetTt() const { return m_Tt; }

void DeckedSlabBeam::SetTb(Float64 tb) { if (tb < 0) THROW_GEOMETRY(WBFL_GEOMETRY_E_DIMENSION);  m_Tb = tb; SetDirtyFlag(); }
Float64 DeckedSlabBeam::GetTb() const { return m_Tb; }

void DeckedSlabBeam::SetF(Float64 f) { if (f < 0) THROW_GEOMETRY(WBFL_GEOMETRY_E_DIMENSION); m_F = f;  SetDirtyFlag(); }
Float64 DeckedSlabBeam::GetF() const { return m_F; }

void DeckedSlabBeam::SetVoidCount(IndexType nVoids)
{
   if (1 < nVoids) THROW_GEOMETRY(WBFL_GEOMETRY_E_DIMENSION);

   m_nVoids = nVoids;
   SetDirtyFlag();
}

IndexType DeckedSlabBeam::GetVoidCount() const { return m_nVoids; }

void DeckedSlabBeam::SetLeftBlockout(bool bBlockout) { m_bLeftBlockout = bBlockout;  SetDirtyFlag(); }
bool DeckedSlabBeam::GetLeftBlockout() const { return m_bLeftBlockout; }

void DeckedSlabBeam::SetRightBlockout(bool bBlockout) { m_bRightBlockout = bBlockout;  SetDirtyFlag(); }
bool DeckedSlabBeam::GetRightBlockout() const { return m_bRightBlockout; }

Float64 DeckedSlabBeam::GetHeight() const
{
   return m_Tt + m_C;
}

void DeckedSlabBeam::Offset(const Size2d& delta)
{
   GetHookPoint()->Offset(delta);
   SetDirtyFlag();
}

void DeckedSlabBeam::Rotate(const Point2d& center, Float64 angle)
{
   m_Rotation += angle;
   GetHookPoint()->Rotate(center, angle);
   SetDirtyFlag();
}

std::unique_ptr<Shape> DeckedSlabBeam::CreateClone() const
{
   return std::make_unique<DeckedSlabBeam>(*this);
}

std::shared_ptr<Shape> DeckedSlabBeam::GetSlabShape() const
{
   return GetComposite()->GetShape(0);
}

std::shared_ptr<Shape> DeckedSlabBeam::GetVoidShape(IndexType voidIdx) const
{
   if (m_nVoids <= voidIdx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);

   return GetComposite()->GetShape(voidIdx + 1);
}

void DeckedSlabBeam::OnUpdateComposite(std::unique_ptr<CompositeShape>& composite) const
{
   // Create the outer shape
   std::unique_ptr<Polygon> slab = std::make_unique<Polygon>();
   Float64 Wb = m_A - 2 * m_B;

   slab->AddPoint(0, 0);
   slab->AddPoint(Wb / 2, 0.0);  // bottom right corner
   slab->AddPoint(Wb / 2, m_C);
   slab->AddPoint(m_A / 2, m_C);

   if (m_bRightBlockout)
   {
      slab->AddPoint(m_A / 2 - m_F, m_C + m_Tt);
   }
   else
   {
      slab->AddPoint(m_A / 2, m_C + m_Tt);
   }

   if (m_bRightBlockout == m_bLeftBlockout)
   {
      // the shape is symmetric about the X = 0 axis
      slab->AddPoint(0, m_C + m_Tt);
      slab->SetSymmetry(Polygon::Symmetry::Y, 0.0);
   }
   else
   {
      // the shape is not symmetric

      // top left corner
      if (m_bLeftBlockout)
      {
         slab->AddPoint(-(m_A / 2 - m_F), m_C + m_Tt);
      }
      else
      {
         slab->AddPoint(-m_A / 2, m_C + m_Tt);
      }

      slab->AddPoint(-m_A / 2, m_C);
      slab->AddPoint(-Wb / 2, m_C);
      slab->AddPoint(-Wb / 2, 0.0);
   }

   composite->AddShape(std::move(slab));

   // put an exterior void in the center of the beam
   if (0 < m_nVoids)
   {
      std::unique_ptr<Polygon> void_shape = std::make_unique<Polygon>();
      Float64 Wv2 = (Wb - 2 * m_W) / 2.0; // half width of void
      void_shape->AddPoint(0, m_Tb);
      void_shape->AddPoint(Wv2, m_Tb);
      void_shape->AddPoint(Wv2, m_C);
      void_shape->AddPoint(0, m_C);
      void_shape->SetSymmetry(Polygon::Symmetry::Y); // the void is always symmetric about the X=0 axis
      composite->AddShape(std::move(void_shape),CompositeShape::ShapeType::Void);
   }

   if (!IsZero(m_Rotation))
      composite->Rotate(Point2d(0, 0), m_Rotation);

   composite->Move(Point2d(0, 0), *GetHookPoint());
}
