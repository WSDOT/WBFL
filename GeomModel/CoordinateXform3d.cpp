///////////////////////////////////////////////////////////////////////
// Geometry - Modeling of geometric primitives
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
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#include <GeomModel/GeomModelLib.h>
#include <GeomModel/CoordinateXform3d.h>
#include <GeomModel/GeomOp2d.h>
#include <stdexcept>

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
   if (vector.IsZero()) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDARG);

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
