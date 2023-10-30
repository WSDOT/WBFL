///////////////////////////////////////////////////////////////////////
// Geometry - Modeling of geometric primitives
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
#include <GeomModel/Vector3d.h>
#include <GeomModel/Primitives3d.h>
#include <GeomModel/GeomOp2d.h>
#include <MathEx.h>

using namespace WBFL::Geometry;

Vector3d::Vector3d() :
   m_X(0.0),m_Y(0.0),m_Z(0.0)
{
}

Vector3d::Vector3d(const Point3d& a, const Point3d& b)
{
   m_X = b.X() - a.X();
   m_Y = b.Y() - a.Y();
   m_Z = b.Z() - a.Z();
}

Vector3d::Vector3d(Float64 x,Float64 y,Float64 z)
{
   m_X = x;
   m_Y = y;
   m_Z = z;
}

Vector3d::Vector3d(const Size3d& size)
{
   m_X = size.Dx();
   m_Y = size.Dy();
   m_Z = size.Dz();
}

Vector3d::~Vector3d()
{
}

bool Vector3d::operator==(const Vector3d& other) const
{
   return (IsEqual(m_X, other.X(), 1.0e-10) &&
           IsEqual(m_Y, other.Y(), 1.0e-10) &&
           IsEqual(m_Z, other.Z(), 1.0e-10));
}

bool Vector3d::operator!=(const Vector3d& other) const
{
   return !(*this == other);
}

Vector3d Vector3d::operator - () const
{
   return Vector3d(Size3d(-m_X, -m_Y, -m_Z));
}

Vector3d& Vector3d::operator += (const Vector3d& other)
{
   return Increment(other);
}

Vector3d& Vector3d::operator -= (const Vector3d& other)
{
   return Decrement(other);
}

Float64 Vector3d::AngleBetween(const Vector3d& other) const
{
   Float64 mag1 = GetMagnitude();
   Float64 mag2 = other.GetMagnitude();

   if (::IsZero(mag1) || ::IsZero(mag2))
      THROW_GEOMETRY(WBFL_GEOMETRY_E_ZEROMAGNITUDE);

   Float64 x = Dot(other) / (mag1 * mag2);

   // if z is just barely greater than 1, make it equal to one
   if ( ::IsZero(x-1.0) && 1.0 < x)
      x = 1.0;

   Float64 angle = acos(x);
   angle = GeometricOperations::NormalizeAngle(angle);
   return angle;
}

Float64 Vector3d::Projection(const Vector3d& other) const
{
   if (::IsZero(GetMagnitude()) || ::IsZero(other.GetMagnitude()))
      THROW_GEOMETRY(WBFL_GEOMETRY_E_ZEROMAGNITUDE);

   return Dot(other) / other.GetMagnitude();
}

Float64 Vector3d::Dot(const Vector3d& other) const
{
   return (m_X*other.m_X) + (m_Y*other.m_Y) + (m_Z*other.m_Z);
}

Vector3d Vector3d::Cross(const Vector3d& other) const
{
   Vector3d cross;
   cross.m_X = m_Y*other.m_Z - m_Z*other.m_Y;
   cross.m_Y = m_Z*other.m_X - m_X*other.m_Z;
   cross.m_Z = m_X*other.m_Y - m_Y*other.m_X;

   return cross;
}

Size3d Vector3d::GetSize()const
{
   return Size3d(m_X, m_Y,m_Z);
}

bool Vector3d::IsZero() const
{
   return ( ::IsZero(m_X) && ::IsZero(m_Y) && ::IsZero(m_Z));
}

Float64 Vector3d::GetMagnitude() const
{
   return sqrt(GetRelMagnitude());
}

Float64 Vector3d::GetRelMagnitude() const
{
   return m_X*m_X + m_Y*m_Y + m_Z*m_Z;
}

Vector3d& Vector3d::Reflect()
{
   m_X = -m_X;
   m_Y = -m_Y;
   m_Z = -m_Z;
   return *this;
}

Vector3d& Vector3d::Normalize()
{
   Float64 mag = GetMagnitude();
   if (::IsZero(mag))
      THROW_GEOMETRY(WBFL_GEOMETRY_E_ZEROMAGNITUDE);

   m_X /= mag;
   m_Y /= mag;
   m_Z /= mag;
   return *this;
}

Vector3d Vector3d::NormalizeBy() const
{
   Float64 len = this->GetMagnitude();
   if ( !::IsZero(len) )
      return Vector3d(Size3d(m_X/len, m_Y/len, m_Z/len));
   else
      return Vector3d();
}

Vector3d& Vector3d::Scale(Float64 factor)
{
   m_X *= factor;
   m_Y *= factor; 
   m_Z *= factor; 
   return *this;
}

Vector3d Vector3d::ScaleBy(Float64 factor) const
{
   Vector3d temp(*this);
   return temp.Scale(factor);
}

Vector3d& Vector3d::SetSize(Float64 dx, Float64 dy, Float64 dz)
{
   m_X = dx;
   m_Y = dy;
   m_Z = dz;
   return *this;
}

Vector3d& Vector3d::SetSize(const Size3d& size)
{
   return SetSize(size.Dx(),size.Dy(),size.Dz());
}

Vector3d& Vector3d::SetMagnitude(Float64 magnitude)
{
   if (magnitude < 0)
      THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDARG);

   Normalize();
   m_X *= magnitude;
   m_Y *= magnitude;
   m_Z *= magnitude;
   return *this;
}

Vector3d Vector3d::SetMagnitudeBy(Float64 magnitude) const
{
   Vector3d v(*this);
   v.SetMagnitude(magnitude);
   return v;
}

Vector3d& Vector3d::Increment(const Vector3d& other)
{
   return Offset(other.X(), other.Y(), other.Z());
}

Vector3d Vector3d::IncrementBy(const Vector3d& other) const
{
   return OffsetBy(other.X(), other.Y(), other.Z());
}

Vector3d& Vector3d::Decrement(const Vector3d& other)
{
   return Offset(-other.X(), -other.Y(), -other.Z());
}

Vector3d Vector3d::DecrementBy(const Vector3d& other) const
{
   return OffsetBy(-other.X(), -other.Y(), -other.Z());
}

Vector3d& Vector3d::Offset(Float64 dx,Float64 dy,Float64 dz)
{
   m_X += dx;
   m_Y += dy;
   m_Z += dz;
   return *this;
}

Vector3d& Vector3d::Offset(const Size3d& size)
{
   return Offset(size.Dx(), size.Dy(), size.Dz());
}

Vector3d Vector3d::OffsetBy(Float64 dx, Float64 dy,Float64 dz) const
{
   return Vector3d(Size3d(m_X+dx, m_Y+dy, m_Z+dz));
}

Vector3d Vector3d::OffsetBy(const Size3d& size) const
{
   return OffsetBy(size.Dx(), size.Dy(), size.Dz());
}

Float64 Vector3d::X() const
{
   return m_X;
}

Float64& Vector3d::X()
{
   return m_X;
}

Float64 Vector3d::Y() const
{
   return m_Y;
}

Float64& Vector3d::Y()
{
   return m_Y;
}

Float64 Vector3d::Z() const
{
   return m_Z;
}

Float64& Vector3d::Z()
{
   return m_Z;
}

std::tuple<Float64,Float64,Float64> Vector3d::GetDimensions() const
{
   return std::make_tuple(m_X, m_Y, m_Z);
}

Vector3d WBFL::Geometry::operator+(const Vector3d& lhs, const Vector3d& rhs)
{
   return Vector3d(Size3d(lhs.X()+rhs.X(), lhs.Y()+rhs.Y(), lhs.Z()+rhs.Z()));
}

Vector3d WBFL::Geometry::operator-(const Vector3d& lhs, const Vector3d& rhs)
{
   return Vector3d(Size3d(lhs.X()-rhs.X(), lhs.Y()-rhs.Y(), lhs.Z()-rhs.Z()));
}
