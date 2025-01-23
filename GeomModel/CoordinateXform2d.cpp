///////////////////////////////////////////////////////////////////////
// Geometry - Modeling of geometric primitives
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
#include <GeomModel/CoordinateXform2d.h>
#include <GeomModel/GeomOp2d.h>

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
