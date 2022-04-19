///////////////////////////////////////////////////////////////////////
// Geometry - Modeling of geometric primitives
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
#include <GeomModel/CoordinateXform3d.h>
#include <GeomModel/GeomOp2d.h>
#include <stdexcept>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace WBFL::Geometry;

CoordinateXform3d::CoordinateXform3d()
{
}

CoordinateXform3d::CoordinateXform3d(const Point3d& origin, const Vector3d& rv, Float64 angle) :
   m_Origin(origin),
   m_RotationVector(rv),
   m_Angle(angle)
{
}

CoordinateXform3d::~CoordinateXform3d()
{
}

void CoordinateXform3d::SetRotationVector(const Vector3d& vector)
{
   if (vector.IsZero())
      throw std::invalid_argument("CoordinateXfor3d::SetRotationVector - invalid vector");

   m_RotationVector = vector;
}

Vector3d& CoordinateXform3d::GetRotationVector()
{
   return m_RotationVector;
}

const Vector3d& CoordinateXform3d::GetRotationVector() const
{
   return m_RotationVector;
}

void CoordinateXform3d::SetRotationAngle(Float64 angle)
{
   m_Angle = angle;
}

Float64 CoordinateXform3d::GetRotationAngle() const
{
   return m_Angle;
}

void CoordinateXform3d::SetNewOrigin(const Point3d& origin)
{
   m_Origin = origin;
}

Point3d& CoordinateXform3d::GetNewOrigin()
{
   return m_Origin;
}

const Point3d& CoordinateXform3d::GetNewOrigin() const
{
   return m_Origin;
}

Point3d& CoordinateXform3d::Xform(Point3d& point, Type type) const
{
   if (type == Type::OldToNew)
      OldToNew(point);
   else
      NewToOld(point);

   return point;
}

Point3d CoordinateXform3d::XformBy(const Point3d& point, Type type) const
{
   Point3d p = point;
   if (type == Type::OldToNew)
      OldToNew(p);
   else
      NewToOld(p);

   return p;
}

void CoordinateXform3d::OldToNew(Point3d& point) const
{
   point = GeometricOperations::GlobalToLocal(m_Origin, m_RotationVector.NormalizeBy(), m_Angle, point);
}

void CoordinateXform3d::NewToOld(Point3d& point) const
{
   point = GeometricOperations::LocalToGlobal(m_Origin, m_RotationVector.NormalizeBy(), m_Angle, point);
}

#if defined _DEBUG
bool CoordinateXform3d::AssertValid() const
{
   return true;
}

void CoordinateXform3d::Dump(dbgDumpContext& os) const
{
   os << "Dump for CoordinateXform3d" << endl;
}
#endif // _DEBUG

#if defined _UNITTEST
#include <MathEx.h>
bool CoordinateXform3d::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("CoordinateXform3d");

   const Float64 tolerance = 1e-04;

   CoordinateXform3d xform;

   // Setup for some real transformations (XY Plane)
   Point3d origin(7, -4, 0);
   Vector3d rv(0, 0, 0); // this is an invalid rotation vector.... will be tested below
   xform.SetNewOrigin(origin);
   try
   {
      xform.SetRotationVector(rv);
      TRY_TESTME(false);
   }
   catch (...)
   {
      TRY_TESTME(true);
   }

   xform.SetRotationAngle(ToRadians(27));

   // use a valid rotation vector
   rv.SetSize(Size3d(0, 0, 1));
   xform.SetRotationVector(rv);

   Point3d pnt(-9, 7, 0);
   Point3d p1;

   p1 = xform.XformBy(pnt, Type::OldToNew);
   // original point should not change
   TRY_TESTME(IsEqual(pnt.X(), -9., tolerance)); 
   TRY_TESTME(IsEqual(pnt.Y(), 7., tolerance));
   TRY_TESTME(IsEqual(pnt.Z(), 0., tolerance));
   // point in new coordinate system
   TRY_TESTME(IsEqual(p1.X(), -9.2622, tolerance));
   TRY_TESTME(IsEqual(p1.Y(), 17.0649, tolerance));
   TRY_TESTME(IsEqual(p1.Z(), 0., tolerance));

   // convert back to original system
   auto p2 = xform.XformBy(p1, Type::NewToOld);
   TRY_TESTME(IsEqual(pnt.X(), p2.X(), tolerance));
   TRY_TESTME(IsEqual(pnt.Y(), p2.Y(), tolerance));
   TRY_TESTME(IsEqual(pnt.Z(), p2.Z(), tolerance));

   // same as the first transformation, except that pnt is changed
   xform.Xform(pnt, Type::OldToNew);
   TRY_TESTME(IsEqual(pnt.X(), p1.X(), tolerance));
   TRY_TESTME(IsEqual(pnt.Y(), p1.Y(), tolerance));
   TRY_TESTME(IsEqual(pnt.Z(), p1.Z(), tolerance));

   // transform back to the origina coodinates
   xform.Xform(pnt, Type::NewToOld);
   TRY_TESTME(IsEqual(pnt.X(), -9., tolerance));
   TRY_TESTME(IsEqual(pnt.Y(), 7., tolerance));
   TRY_TESTME(IsEqual(pnt.Z(), 0., tolerance));

   // Test XZ Plane
   origin.Move(7, 0, -4);
   rv.SetSize(Size3d(0, -1, 0));
   xform.SetNewOrigin(origin);
   xform.SetRotationVector(rv);
   pnt.Move(-9, 0, 7);
   xform.Xform(pnt, Type::OldToNew);
   TRY_TESTME(IsEqual(pnt.X(), -9.2622, tolerance));
   TRY_TESTME(IsEqual(pnt.Y(), 0.0000, tolerance));
   TRY_TESTME(IsEqual(pnt.Z(), 17.0649, tolerance));

   pnt.Move(-9.2622, 0.0000, 17.0649);
   xform.Xform(pnt,Type::NewToOld);
   TRY_TESTME(IsEqual(pnt.X(), -9., tolerance));
   TRY_TESTME(IsEqual(pnt.Y(), 0., tolerance));
   TRY_TESTME(IsEqual(pnt.Z(), 7., tolerance));

   // Test YZ Plane
   origin.Move(0, 7, -4);
   rv.SetSize(Size3d(1, 0, 0));
   xform.SetNewOrigin(origin);
   xform.SetRotationVector(rv);
   pnt.Move(0, -9, 7);
   xform.Xform(pnt, Type::OldToNew);
   TRY_TESTME(IsEqual(pnt.X(), 0.0000, tolerance));
   TRY_TESTME(IsEqual(pnt.Y(), -9.2622, tolerance));
   TRY_TESTME(IsEqual(pnt.Z(), 17.0649, tolerance));

   pnt.Move(0.0000, -9.2622, 17.0649);
   xform.Xform(pnt, Type::NewToOld);
   TRY_TESTME(IsEqual(pnt.X(), 0., tolerance));
   TRY_TESTME(IsEqual(pnt.Y(), -9., tolerance));
   TRY_TESTME(IsEqual(pnt.Z(), 7., tolerance));

   // 3D Transformation
   origin.Move(2.45, 4, 4.25);
   rv.SetSize(Size3d(0, -1, -1));
   xform.SetNewOrigin(origin);
   xform.SetRotationVector(rv);
   xform.SetRotationAngle(ToRadians(62.5));
   pnt.Move(3.9, 2.1, 7.0);
   xform.Xform(pnt, Type::OldToNew);
   TRY_TESTME(IsEqual(pnt.X(), 3.5861, tolerance));
   TRY_TESTME(IsEqual(pnt.Y(), 0.2609, tolerance));
   TRY_TESTME(IsEqual(pnt.Z(), 0.5891, tolerance));

   pnt.Move(3.5861, 0.2609, 0.5891);
   xform.Xform(pnt,Type::NewToOld);
   TRY_TESTME(IsEqual(pnt.X(), 3.9, 0.1));
   TRY_TESTME(IsEqual(pnt.Y(), 2.1, 0.1));
   TRY_TESTME(IsEqual(pnt.Z(), 7.0, 0.1));

   pnt.Move(1, 1, 1);
   xform.Xform(pnt,Type::NewToOld);
   TRY_TESTME(IsEqual(pnt.X(), 2.9117, tolerance));
   TRY_TESTME(IsEqual(pnt.Y(), 4.3728, tolerance));
   TRY_TESTME(IsEqual(pnt.Z(), 5.8772, tolerance));

   pnt.Move(2.9117, 4.3728, 5.8772);
   xform.Xform(pnt,Type::OldToNew);
   TRY_TESTME(IsEqual(pnt.X(), 1.0, 0.1));
   TRY_TESTME(IsEqual(pnt.Y(), 1.0, 0.1));
   TRY_TESTME(IsEqual(pnt.Z(), 1.0, 0.1));

   TESTME_EPILOG("CoordinateXform3d");
}
#endif // _UNITTEST


