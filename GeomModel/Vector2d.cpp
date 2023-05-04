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
   if (::IsZero(mag))
      THROW_GEOMETRY(WBFL_GEOMETRY_E_ZEROMAGNITUDE);

   m_X /= mag;
   m_Y /= mag;
   return *this;
}

Vector2d Vector2d::NormalizeBy() const
{
   Float64 len = this->GetMagnitude();
   if ( !::IsZero(len) )
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

#if defined _DEBUG
bool Vector2d::AssertValid() const
{
   return true;
}

void Vector2d::Dump(WBFL::Debug::LogContext& os) const
{
   os << _T("Dump for Vector2d") << WBFL::Debug::endl;
   os << _T("  m_X = ")<<m_X<<_T(", m_Y = ")<<m_Y<< WBFL::Debug::endl;
}
#endif // _DEBUG

Vector2d WBFL::Geometry::operator+(const Vector2d& lhs, const Vector2d& rhs)
{
   return Vector2d(Size2d(lhs.X()+rhs.X(), lhs.Y()+rhs.Y()));
}

Vector2d WBFL::Geometry::operator-(const Vector2d& lhs, const Vector2d& rhs)
{
   return Vector2d(Size2d(lhs.X()-rhs.X(), lhs.Y()-rhs.Y()));
}

#if defined _UNITTEST
bool Vector2d::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("Vector2d");

   // test all of the features of a vector

   Float64 pi = 4.*atan(1.);

   const Vector2d up(1,pi/2), left(1,pi), down(1,3*pi/2), right(1,0);
   const Vector2d at45(Size2d(1,1)), at135(Size2d(-1,1)), 
                    at315(Size2d(1,-1)), at225(Size2d(-1,-1));

   Vector2d testvec1, testvec2;

   // size
   Size2d ts(2,3);
   testvec1.SetSize(ts);
   TRY_TESTME ( ts == testvec1.GetSize());   

   // dot product
   Float64 val = right.Dot(up);
   TRY_TESTME ( IsEqual(val,0.) );

   // add, subtract, reflection
   testvec1 = right + up;
   testvec2 = -left - down;
   TRY_TESTME (testvec1 == at45);
   TRY_TESTME (testvec1 == testvec2);

   // setmagnitude, length
   testvec1.SetMagnitude(4);
   val = testvec1.GetMagnitude();
   TRY_TESTME(IsEqual(val,4.0));

   // assignment, reflection, ==
   testvec1 = at45;
   testvec1.Reflect();
   TRY_TESTME (testvec1 == at225);

   // Normal
   testvec1 = at315.Normal(Side::Left);
   TRY_TESTME (testvec1 == at45);

   testvec1 = at315.Normal(Side::Right);
   TRY_TESTME (testvec1 == at225);

   // Normalize
   testvec1 = at45.NormalizeBy();
   val = testvec1.GetMagnitude();
   TRY_TESTME ( IsEqual(val, 1.,1.0e-6));

   // Offset, OffsetBy
   testvec1 = at45.OffsetBy(21,21);
   testvec2 = testvec1.Normal();
   val = at45.Dot(testvec2);
   TRY_TESTME (val == 0);

   // Rotate, RotateBy
   testvec1 = right;
   testvec2 = testvec1.RotateBy(atan(1.));

   // scale, scaleby
   val = at45.GetMagnitude();
   testvec1 = at45.ScaleBy(4);
   TRY_TESTME (IsEqual(4*val, testvec1.GetMagnitude()));

   // projection.
   val = right.Projection(at315);
   TRY_TESTME(IsEqual(val, sqrt(2.)/2));

   //
   // Test Properties
   //
   Float64 x, y;
   x = -10.0;
   y = -20.0;
   Vector2d vec;
   vec.SetSize(x, y);
   TRY_TESTME(IsEqual(x, vec.X()));
   TRY_TESTME(IsEqual(y, vec.Y()));

   //
   // Test Size Property
   //
   auto size = vec.GetSize();
   TRY_TESTME(IsEqual(x, size.Dx()));
   TRY_TESTME(IsEqual(y, size.Dy()));

   //
   // Test Magnitude Property
   //

   // use a 3,4,5 triangle
   vec.SetSize(3, 4);
   TRY_TESTME(IsEqual(vec.GetMagnitude(), 5.0));
   // Set magnitude to 15 (9,12,15 triangle, 
   // this is a 3,4,5 triangle scaled by a factor of 3)
   vec.SetMagnitude(15.0);
   TRY_TESTME(IsEqual(vec.GetMagnitude(), 15.0));
   TRY_TESTME(IsEqual(vec.X(), 9.0));
   TRY_TESTME(IsEqual(vec.Y(), 12.0));

   // Magnitude must be a positive number
   try
   {
      vec.SetMagnitude(-10);
      TRY_TESTME(false);
   }
   catch (...)
   {
      TRY_TESTME(true);
   }

   //
   // Test Direction property
   //

   // (45 deg line, direction = M_PI/4)
   vec.SetSize(1, 1);
   TRY_TESTME(IsEqual(vec.GetDirection(), M_PI / 4));

   // Set direction to 90 deg
   vec.SetDirection(PI_OVER_2);
   TRY_TESTME(IsEqual(vec.GetDirection(), PI_OVER_2));
   TRY_TESTME(IsEqual(vec.X(), 0.0));
   TRY_TESTME(IsEqual(vec.Y(), 1.4142135)); // Magnitude stays the same so magnitude is Sqrt(2) = 1.414

   //
   // Test Normalize
   //
   vec.SetSize(10, 10);
   vec.Normalize();
   TRY_TESTME(IsEqual(vec.GetMagnitude(), 1.0));
   TRY_TESTME(IsEqual(vec.X(), 0.70710678));
   TRY_TESTME(IsEqual(vec.Y(), 0.70710678));

   // normalize a zero length vector
   vec.SetSize(0, 0);
   try
   {
      vec.Normalize();
      TRY_TESTME(false);
   }
   catch (...)
   {
      TRY_TESTME(true);
   }

   //
   // Test IsZero
   //
   vec.SetSize(10, 0);
   TRY_TESTME(vec.IsZero() == false);

   vec.SetSize(0, 10);
   TRY_TESTME(vec.IsZero() == false);

   vec.SetSize(0, 0);
   TRY_TESTME(vec.IsZero() == true);

   //
   // Test Normal
   //

   // Make source vector point to the right. Normal will be up
   vec.SetSize(10, 0);
   auto normal = vec.Normal();
   TRY_TESTME(IsEqual(normal.X(), 0.0));
   TRY_TESTME(IsEqual(normal.Y(), 10.0));

   // Make source vector point to the left. Normal will be down
   vec.SetSize(-10, 0);
   normal = vec.Normal();
   TRY_TESTME(IsEqual(normal.X(), 0.0));
   TRY_TESTME(IsEqual(normal.Y(), -10.0));

   // Make source vector point up.
   vec.SetSize(0, 10);
   normal = vec.Normal();
   TRY_TESTME(IsEqual(normal.X(), -10.0));
   TRY_TESTME(IsEqual(normal.Y(), 0.0));

   // Make source vector point down.
   vec.SetSize(0, -10);
   normal = vec.Normal();
   TRY_TESTME(IsEqual(normal.X(), 10.0));
   TRY_TESTME(IsEqual(normal.Y(), 0.0));

   // Make source vector point up and to the right (45 deg)
   vec.SetSize(10, 10);
   normal = vec.Normal();
   TRY_TESTME(IsEqual(normal.X(), -10.0));
   TRY_TESTME(IsEqual(normal.Y(), 10.0));

   // Make source vector point up and to the left (45 deg)
   vec.SetSize(-10, 10);
   normal = vec.Normal();
   TRY_TESTME(IsEqual(normal.X(), -10.0));
   TRY_TESTME(IsEqual(normal.Y(), -10.0));

   // Make source vector point down and to the right (45 deg)
   vec.SetSize(10, -10);
   normal = vec.Normal();
   TRY_TESTME(IsEqual(normal.X(), 10.0));
   TRY_TESTME(IsEqual(normal.Y(), 10.0));

   // Make source vector point down and to the left (45 deg)
   vec.SetSize(-10, -10);
   normal = vec.Normal();
   TRY_TESTME(IsEqual(normal.X(), 10.0));
   TRY_TESTME(IsEqual(normal.Y(), -10.0));

   //
   // Test Offset and OffsetEx
   //
   vec.SetSize(10, 10);
   vec.Offset(5, 5);
   TRY_TESTME(IsEqual(vec.X(), 15.0));
   TRY_TESTME(IsEqual(vec.Y(), 15.0));

   vec.SetSize(10, 10);
   vec.Offset(Size2d(-20, -20));
   TRY_TESTME(IsEqual(vec.X(), -10.0));
   TRY_TESTME(IsEqual(vec.Y(), -10.0));

   //
   // Test Projection (Projection of Vec1 onto Vec2)
   //

   // Vector is zero length
   Vector2d vec2(0, 0);
   try
   {
      vec.Projection(vec2);
      TRY_TESTME(false);
   }
   catch (...)
   {
      TRY_TESTME(true);
   }

   // Vector is zero length
   vec.SetSize(0, 0);
   vec2.SetSize(10, 10);
   try
   {
      vec.Projection(vec2);
      TRY_TESTME(false);
   }
   catch (...)
   {
      TRY_TESTME(true);
   }

   // Vectors are right angles (projection = 0)
   vec.SetSize(10, 0);
   vec2.SetSize(0, 10);
   TRY_TESTME(::IsZero(vec.Projection(vec2)) == true);

   // One vector in the X direction, and one at 3,4,5. Projection will
   // be 3
   vec.SetSize(3,4);
   vec2.SetSize(10, 0);
   TRY_TESTME(IsEqual(vec.Projection(vec2), 3.0));

   // One vector in the Y direction, and one at 3,4,5. Projection will
   // be 4
   vec.SetSize(3, 4);
   vec2.SetSize(0, 10);
   TRY_TESTME(IsEqual(vec.Projection(vec2), 4.0));

   // Negative projections (vectors in opposite directions)
   vec.SetSize(-3, 4);
   vec2.SetSize(10, 0);
   TRY_TESTME(IsEqual(vec.Projection(vec2), -3.0));

   //
   // Test Reflect
   //
   vec.SetSize(10, 10);
   vec.Reflect();
   TRY_TESTME(IsEqual(vec.X(), -10.0));
   TRY_TESTME(IsEqual(vec.Y(), -10.0));

   //
   // Test Rotate
   //
   vec.SetSize(10, 0);
   vec.Rotate(M_PI / 4);
   TRY_TESTME(IsEqual(vec.X(), 7.0710678));
   TRY_TESTME(IsEqual(vec.Y(), 7.0710678));

   vec.SetSize(10, 10);
   vec.Rotate(M_PI / 4);
   TRY_TESTME(IsEqual(vec.X(), 0.0));
   TRY_TESTME(IsEqual(vec.Y(), 14.142135));

   vec.SetSize(10, 10);
   vec.Rotate(-M_PI / 4);
   TRY_TESTME(IsEqual(vec.X(), 14.142135));
   TRY_TESTME(IsEqual(vec.Y(), 0.0));

   //
   // Test Scale
   //
   vec.SetSize(10, 10);
   vec.SetMagnitude(10.0);
   vec.Scale(2.0);
   TRY_TESTME(IsEqual(vec.GetMagnitude(), 20.0));

   //
   // Test Dot
   //
   vec.SetSize(10, 20);
   vec2.SetSize(30, 40);
   TRY_TESTME(IsEqual(vec.Dot(vec2), 1100.0));

   //
   // Test AngleBetween
   //
   vec.SetSize(10, 0);
   vec2.SetSize(10, 10);
   TRY_TESTME(IsEqual(vec.AngleBetween(vec2), M_PI / 4.0));

   // pVec is zero
   vec.SetSize(0, 0);
   try
   {
      vec.AngleBetween(vec2);
      TRY_TESTME(false);
   }
   catch (...)
   {
      TRY_TESTME(true);
   }

   // pVec2 is zero
   vec.SetSize(10, 0);
   vec2.SetSize(0, 0);
   try
   {
      vec.AngleBetween(vec2);
      TRY_TESTME(false);
   }
   catch (...)
   {
      TRY_TESTME(true);
   }

   //
   // Test Increment and Decrement
   //
   vec.SetSize(10, 20);
   vec2.SetSize(50, 60);
   vec.Increment(vec2);
   TRY_TESTME(IsEqual(vec.X(), 60.));
   TRY_TESTME(IsEqual(vec.Y(), 80.));

   auto vec3 = vec.IncrementBy(vec2);
   // vector 1, unchanged
   TRY_TESTME(IsEqual(vec.X(), 60.));
   TRY_TESTME(IsEqual(vec.Y(), 80.));
   TRY_TESTME(IsEqual(vec3.X(), 110.));
   TRY_TESTME(IsEqual(vec3.Y(), 140.));

   vec.SetSize(10, 20);
   vec2.SetSize(50, 60);
   vec.Decrement(vec2);
   TRY_TESTME(IsEqual(vec.X(), -40.));
   TRY_TESTME(IsEqual(vec.Y(), -40.));

   vec3 = vec.DecrementBy(vec2);
   // vector 1, unchanged
   TRY_TESTME(IsEqual(vec.X(), -40.));
   TRY_TESTME(IsEqual(vec.Y(), -40.));
   TRY_TESTME(IsEqual(vec3.X(), -90.));
   TRY_TESTME(IsEqual(vec3.Y(), -100.));


#if defined _DEBUG
   testvec1.Dump(rlog.GetLogContext());
#endif
   TESTME_EPILOG("Vector2d");
}
#endif // _UNITTEST


