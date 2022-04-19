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
#include <GeomModel/CoordinateXform2d.h>
#include <GeomModel/GeomOp2d.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace WBFL::Geometry;

CoordinateXform2d::CoordinateXform2d()
{
}

CoordinateXform2d::CoordinateXform2d(const Point2d& origin, Float64 angle) :
   m_Origin(origin)
{
   SetRotationAngle(angle);
}

CoordinateXform2d::~CoordinateXform2d()
{
}

void CoordinateXform2d::SetRotationAngle(Float64 angle)
{
   m_Angle = angle;
   m_CosAngle = cos(m_Angle);
   m_SinAngle = sin(m_Angle);
}

Float64 CoordinateXform2d::GetRotationAngle() const
{
   return m_Angle;
}

void CoordinateXform2d::SetNewOrigin(const Point2d& origin)
{
   m_Origin = origin;
}

Point2d& CoordinateXform2d::GetNewOrigin()
{
   return m_Origin;
}

const Point2d& CoordinateXform2d::GetNewOrigin() const
{
   return m_Origin;
}

Point2d& CoordinateXform2d::Xform(Point2d& point, Type type) const
{
   if (type == Type::OldToNew)
      OldToNew(point);
   else
      NewToOld(point);

   return point;
}

Point2d CoordinateXform2d::XformBy(const Point2d& point, Type type) const
{
   Point2d p = point;
   if (type == Type::OldToNew)
      OldToNew(p);
   else
      NewToOld(p);

   return p;
}

void CoordinateXform2d::OldToNew(Point2d& point) const
{
   point = GeometricOperations::GlobalToLocal(m_Origin, m_Angle, point);
}

void CoordinateXform2d::NewToOld(Point2d& point) const
{
   point = GeometricOperations::LocalToGlobal(m_Origin, m_Angle, point);
}

#if defined _DEBUG
bool CoordinateXform2d::AssertValid() const
{
   return true;
}

void CoordinateXform2d::Dump(dbgDumpContext& os) const
{
   os << "Dump for CoordinateXform2d" << endl;
}
#endif // _DEBUG

#if defined _UNITTEST
#include <MathEx.h>
bool CoordinateXform2d::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("CoordinateXform2d");

   const Float64 tolerance = 1.0e-04;

   CoordinateXform2d xform;

   Point2d origin(7, -4);
   xform.SetNewOrigin(origin);

   xform.SetRotationAngle(27*M_PI / 180);

   Point2d p1(-9, 7);
   Point2d p2 = xform.XformBy(p1, Type::OldToNew);
   TRY_TESTME(IsEqual(p1.X(), -9.0, tolerance)); // should not change original point
   TRY_TESTME(IsEqual(p1.Y(),  7.0, tolerance));
   TRY_TESTME(IsEqual(p2.X(), -9.2622, tolerance));
   TRY_TESTME(IsEqual(p2.Y(), 17.0649, tolerance));

   Point2d p3 = xform.Xform(p1, Type::OldToNew);
   TRY_TESTME(IsEqual(p1.X(), -9.2622, tolerance)); // changes original point
   TRY_TESTME(IsEqual(p1.Y(), 17.0649, tolerance));
   TRY_TESTME(IsEqual(p3.X(), -9.2622, tolerance));
   TRY_TESTME(IsEqual(p3.Y(), 17.0649, tolerance));

   Point2d p1_ = xform.XformBy(p1, Type::NewToOld);
   TRY_TESTME(IsEqual(p1.X(), -9.2622, tolerance));
   TRY_TESTME(IsEqual(p1.Y(), 17.0649, tolerance));
   TRY_TESTME(IsEqual(p1_.X(), -9.0, tolerance));
   TRY_TESTME(IsEqual(p1_.Y(), 7.0, tolerance));

   Point2d p2_ = xform.Xform(p1, Type::NewToOld);
   TRY_TESTME(IsEqual(p1.X(), -9.0, tolerance));
   TRY_TESTME(IsEqual(p1.Y(), 7.0, tolerance));
   TRY_TESTME(IsEqual(p2_.X(), -9.0, tolerance));
   TRY_TESTME(IsEqual(p2_.Y(), 7.0, tolerance));

   TESTME_EPILOG("CoordinateXform2d");
}
#endif // _UNITTEST


