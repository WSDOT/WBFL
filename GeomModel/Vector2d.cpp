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
#include <GeomModel/Vector2d.h>
#include <GeomModel/GeomOp2d.h>
#include <GeomModel/Primitives.h>
#include <math.h>
#include <MathEx.h>
#include <iostream>

using namespace WBFL::Geometry;

Vector2d::Vector2d() : m_X(1.0), m_Y(0.0)
{
}

Vector2d::Vector2d(Float64 magnitude, Float64 direction)
{
   m_X = magnitude * cos(direction);
   m_Y = magnitude * sin(direction);
}

Vector2d::Vector2d(const Point2d& a, const Point2d& b)
{
   m_X = b.X() - a.X();
   m_Y = b.Y() - a.Y();
}

Vector2d::Vector2d(const Size2d& size)
{
   m_X = size.Dx();
   m_Y = size.Dy();
}

Vector2d::~Vector2d()
{
}

bool Vector2d::operator==(const Vector2d& other) const
{
   return (IsEqual(m_X, other.X(), 1.0e-10) && IsEqual(m_Y, other.Y(), 1.0e-10));
}

bool Vector2d::operator!=(const Vector2d& other) const
{
   return !(*this == other);
}

Vector2d Vector2d::operator-() const
{
   return Vector2d(Size2d(-m_X, -m_Y));
}

Vector2d& Vector2d::operator+=(const Vector2d& other)
{
   m_X += other.m_X;
   m_Y += other.m_Y;
   return *this;
}

Vector2d& Vector2d::operator-=(const Vector2d& other)
{
   m_X -= other.m_X;
   m_Y -= other.m_Y;
   return *this;
}

Float64 Vector2d::AngleBetween(const Vector2d& other) const
{
   Float64 mag1 = GetMagnitude();
   Float64 mag2 = other.GetMagnitude();

   if (::IsZero(mag1) || ::IsZero(mag2)) 
      THROW_GEOMETRY(WBFL_GEOMETRY_E_ZEROMAGNITUDE);

   Float64 x = Dot(other)/(mag1*mag2);
   if ( ::IsZero(x-1.0) )
      x = 1.0;

   Float64 angle = acos(x);
   angle = GeometricOperations::NormalizeAngle(angle);
   return angle;
}

Float64 Vector2d::Projection(const Vector2d& other) const
{
   if (::IsZero(GetMagnitude()) || ::IsZero(other.GetMagnitude()))
      THROW_GEOMETRY(WBFL_GEOMETRY_E_ZEROMAGNITUDE);

   return Dot(other) / other.GetMagnitude();
}

Float64 Vector2d::Dot(const Vector2d& other) const
{
   return (m_X*other.m_X) + (m_Y*other.m_Y);
}

Float64 Vector2d::GetDirection() const
{
   return GeometricOperations::NormalizeAngle( atan2(m_Y, m_X) );
}

Size2d Vector2d::GetSize()const
{
   return Size2d(m_X, m_Y);
}

bool Vector2d::IsZero() const
{
   return ( ::IsZero(m_X) && ::IsZero(m_Y) );
}


Float64 Vector2d::GetMagnitude() const
{
   return sqrt(GetRelMagnitude());
}

Float64 Vector2d::GetRelMagnitude() const
{
   return m_X*m_X + m_Y*m_Y;
}

Vector2d& Vector2d::Reflect()
{
   m_X = -m_X;
   m_Y = -m_Y;
   return *this;
}

Vector2d& Vector2d::Normalize()
{
   Float64 mag = GetMagnitude();
   if (mag == 0.0)
      THROW_GEOMETRY(WBFL_GEOMETRY_E_ZEROMAGNITUDE);

   m_X /= mag;
   m_Y /= mag;
   return *this;
}

Vector2d Vector2d::NormalizeBy() const
{
   Float64 len = this->GetMagnitude();
   if ( len != 0.0 )
      return Vector2d(Size2d(m_X/len, m_Y/len));
   else
      return Vector2d();
}

Vector2d Vector2d::Normal(Side side) const
{
   if (side==Side::Left)
      return Vector2d(Size2d(-m_Y, m_X));
   else
      return Vector2d(Size2d(m_Y, -m_X));
}

Vector2d& Vector2d::Scale(Float64 factor)
{
   m_X *= factor;
   m_Y *= factor; 
   return *this;
}

Vector2d Vector2d::ScaleBy(Float64 factor) const
{
   Vector2d temp(*this);
   return temp.Scale(factor);
}

Vector2d& Vector2d::Increment(const Vector2d& other)
{
   return Offset(other.GetSize());
}

Vector2d Vector2d::IncrementBy(const Vector2d& other) const
{
   return OffsetBy(other.GetSize());
}

Vector2d& Vector2d::Decrement(const Vector2d& other)
{
   return Offset(-other.GetSize());
}

Vector2d Vector2d::DecrementBy(const Vector2d& other) const
{
   return OffsetBy(-other.GetSize());
}

Vector2d& Vector2d::SetDirection(Float64 direction)
{
   Float64 magnitude = GetMagnitude();
   m_X = magnitude * cos(direction);
   m_Y = magnitude * sin(direction);
   return *this;
}

Vector2d Vector2d::SetDirectionBy(Float64 direction) const
{
   Float64 magnitude = GetMagnitude();
   return Vector2d(magnitude,direction);
}

Vector2d& Vector2d::SetSize(const Size2d& size)
{
   m_X = size.Dx();
   m_Y = size.Dy();
   return *this;
}

Vector2d& Vector2d::SetSize(Float64 x,Float64 y)
{
   m_X = x;
   m_Y = y;
   return *this;
}

Vector2d& Vector2d::SetMagnitude(Float64 magnitude)
{
   if (magnitude < 0)
      THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDARG);

   Normalize();
   m_X *= magnitude;
   m_Y *= magnitude;
   return *this;
}

Vector2d Vector2d::SetMagnitudeBy(Float64 magnitude) const
{
   Vector2d t(*this);
   return t.SetMagnitude(magnitude);
}


Vector2d& Vector2d::Offset(Float64 dx,Float64 dy)
{
   m_X += dx;
   m_Y += dy;
   return *this;
}

Vector2d& Vector2d::Offset(const Size2d& size)
{
   return Offset(size.Dx(), size.Dy());
}

Vector2d Vector2d::OffsetBy(Float64 dx, Float64 dy) const
{
   return Vector2d(Size2d(m_X+dx, m_Y+dy));
}

Vector2d Vector2d::OffsetBy(const Size2d& size) const
{
   return OffsetBy(size.Dx(), size.Dy());
}

Vector2d& Vector2d::Rotate(Float64 angle)
{
   Float64 x, y;
   Float64 cosa = cos(angle);
   Float64 sina = sin(angle);
   
   x = m_X*cosa - m_Y*sina;
   y = m_X*sina + m_Y*cosa;

   m_X = x;
   m_Y = y;
   return *this;
}

Vector2d Vector2d::RotateBy(Float64 angle) const
{
   Vector2d temp(*this);
   return temp.Rotate(angle);
}


Float64 Vector2d::X() const
{
   return m_X;
}

Float64& Vector2d::X()
{
   return m_X;
}

Float64 Vector2d::Y() const
{
   return m_Y;
}

Float64& Vector2d::Y()
{
   return m_Y;
}         

std::pair<Float64,Float64> Vector2d::GetDimensions() const
{
   return std::make_pair(m_X, m_Y);
}

Vector2d WBFL::Geometry::operator+(const Vector2d& lhs, const Vector2d& rhs)
{
   return Vector2d(Size2d(lhs.X()+rhs.X(), lhs.Y()+rhs.Y()));
}

Vector2d WBFL::Geometry::operator-(const Vector2d& lhs, const Vector2d& rhs)
{
   return Vector2d(Size2d(lhs.X()-rhs.X(), lhs.Y()-rhs.Y()));
}
