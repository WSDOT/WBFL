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

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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
      THROW_GEOMETRY(_T("Vector3d::AngleBetween - cannot compute angle between with a zero magnitude vector"));

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
      THROW_GEOMETRY(_T("Vector3d::Projection - cannot project onto a zero magnitude vector"));

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
      THROW_GEOMETRY(_T("Vector3d::Normalize - cannot normalize a zero length vector"));

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
      THROW_GEOMETRY(_T("Vector3d::SetMagnitude - invalid magnitude"));

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

void Vector3d::GetDimensions(Float64* x, Float64* y, Float64* z) const
{
   *x = m_X;
   *y = m_Y;
   *z = m_Z;
}

#if defined _DEBUG
bool Vector3d::AssertValid() const
{
   return true;
}

void Vector3d::Dump(WBFL::Debug::LogContext& os) const
{
   os << "Dump for Vector3d" << WBFL::Debug::endl;
   os << "  m_X = "<<m_X<<", m_Y = "<<m_Y << ", m_Z = " << m_Z << WBFL::Debug::endl;
}
#endif // _DEBUG

Vector3d WBFL::Geometry::operator+(const Vector3d& lhs, const Vector3d& rhs)
{
   return Vector3d(Size3d(lhs.X()+rhs.X(), lhs.Y()+rhs.Y(), lhs.Z()+rhs.Z()));
}

Vector3d WBFL::Geometry::operator-(const Vector3d& lhs, const Vector3d& rhs)
{
   return Vector3d(Size3d(lhs.X()-rhs.X(), lhs.Y()-rhs.Y(), lhs.Z()-rhs.Z()));
}

#if defined _UNITTEST
bool Vector3d::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("Vector3d");

   //
   // Test Properties
   //
   Float64 x, y, z;
   x = -10.0;
   y = -20.0;
   z = -30.0;

   Vector3d vec(x, y, z);
   TRY_TESTME(IsEqual(x, vec.X()));
   TRY_TESTME(IsEqual(y, vec.Y()));
   TRY_TESTME(IsEqual(z, vec.Z()));

   //
   // Test Size Property
   //
   Size3d size = vec.GetSize();
   TRY_TESTME(IsEqual(x, size.Dx()));
   TRY_TESTME(IsEqual(y, size.Dy()));
   TRY_TESTME(IsEqual(z, size.Dz()));

   //
   // Test Magnitude Property
   //
   vec.SetSize(Size3d(3, 4, 5));
   TRY_TESTME(IsEqual(vec.GetMagnitude(), 7.07106781187));

   vec.SetMagnitude(70.7106781187);
   TRY_TESTME(IsEqual(vec.GetMagnitude(), 70.7106781187));
   TRY_TESTME(IsEqual(vec.X(), 30.0));
   TRY_TESTME(IsEqual(vec.Y(), 40.0));
   TRY_TESTME(IsEqual(vec.Z(), 50.0));

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
   // Test Normalize
   //
   vec.SetSize(Size3d(10, 20, 30));
   vec.Normalize();
   TRY_TESTME(IsEqual(vec.GetMagnitude(), 1.0));
   TRY_TESTME(IsEqual(vec.X(), 0.267261));
   TRY_TESTME(IsEqual(vec.Y(), 0.534522));
   TRY_TESTME(IsEqual(vec.Z(), 0.801784));

   // normalize a zero length vector
   vec.SetSize(Size3d(0, 0, 0));
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
   TRY_TESTME(vec.IsZero() == true);
   vec.SetSize(Size3d(10, 0, 0));
   TRY_TESTME(vec.IsZero() == false);

   vec.SetSize(Size3d(0, 10, 0));
   TRY_TESTME(vec.IsZero() == false);

   vec.SetSize(Size3d(0, 0, 10));
   TRY_TESTME(vec.IsZero() == false);

   //
   // Test Offset and OffsetEx
   //
   vec.SetSize(Size3d(10, 10, 10));
   vec.Offset(Size3d(5, 5, 5));
   TRY_TESTME(IsEqual(vec.X(), 15.0));
   TRY_TESTME(IsEqual(vec.Y(), 15.0));
   TRY_TESTME(IsEqual(vec.Z(), 15.0));

   vec.SetSize(Size3d(10, 10, 10));
   vec.Offset(Size3d(-20,-20,-20));
   TRY_TESTME(IsEqual(vec.X(), -10.0));
   TRY_TESTME(IsEqual(vec.Y(), -10.0));
   TRY_TESTME(IsEqual(vec.Z(), -10.0));

   //
   // Test Projection (Projection of Vec2 onto Vec1)
   //

   // Vector is zero length
   Vector3d vec2(0, 0, 0);
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
   vec.SetSize(Size3d(0, 0, 0));
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
   vec.SetSize(Size3d(10, 10, 0));
   vec2.SetSize(Size3d(-10, 10, 0));
   TRY_TESTME(::IsZero(vec.Projection(vec2)));

   // One vector in the X direction, and one at 3,4,5. Projection will
   // be 3
   vec.SetSize(Size3d(3, 4, 5));
   vec2.SetSize(Size3d(10, 0, 0));
   TRY_TESTME(IsEqual(vec.Projection(vec2),3.0));

   // One vector in the Y direction, and one at 3,4,5. Projection will
   // be 4
   vec.SetSize(Size3d(3, 4, 5));
   vec2.SetSize(Size3d(0, 10, 0));
   TRY_TESTME(IsEqual(vec.Projection(vec2), 4.0));

   // Negative projections (vectors in opposite directions)
   vec.SetSize(Size3d(-3, 4, 5));
   vec2.SetSize(Size3d(10, 0, 0));
   TRY_TESTME(IsEqual(vec.Projection(vec2), -3.0));

   vec.SetSize(Size3d(10, 10, 10));
   vec2.SetSize(Size3d(10, 0, 10));
   TRY_TESTME(IsEqual(vec.Projection(vec2), 14.1421356));

   //
   // Test Reflect
   //
   vec.SetSize(Size3d(10, 10, 10));
   vec.Reflect();
   TRY_TESTME(IsEqual(vec.X(), -10.0));
   TRY_TESTME(IsEqual(vec.Y(), -10.0));
   TRY_TESTME(IsEqual(vec.Z(), -10.0));

   //
   // Test Scale
   //
   vec.SetSize(Size3d(10, 10, 10)); // establish direction
   vec.SetMagnitude(10); // fix magnitude
   vec.Scale(2);
   TRY_TESTME(IsEqual(vec.GetMagnitude(), 20.0));

   //
   // Test Dot
   //
   vec.SetSize(Size3d(10, 20, 30));
   vec2.SetSize(Size3d(40, 50, 60));
   TRY_TESTME(IsEqual(vec.Dot(vec2), 3200.0));

   //
   // Test AngleBetween
   //
   vec.SetSize(Size3d(10, 0, 0));
   vec2.SetSize(Size3d(10, 10, 0));
   TRY_TESTME(IsEqual(vec.AngleBetween(vec2), M_PI / 4));

   vec.SetSize(Size3d(10, 10, 10));
   vec2.SetSize(Size3d(-10, -10, -10));
   TRY_TESTME(IsEqual(vec.AngleBetween(vec2), M_PI));

   // pVec is zero
   vec.SetSize(Size3d(0, 0, 0));
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
   vec.SetSize(Size3d(10, 0, 0));
   vec2.SetSize(Size3d(0, 0, 0));
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
   // Test Cross 
   //
   vec.SetSize(Size3d(10, 20, 30));
   vec2.SetSize(Size3d(-32, -25, 4));
   auto cross = vec.Cross(vec2);
   TRY_TESTME(IsEqual(cross.X(),   830.));
   TRY_TESTME(IsEqual(cross.Y(), -1000.));
   TRY_TESTME(IsEqual(cross.Z(),   390.));

   cross = vec2.Cross(vec);
   TRY_TESTME(IsEqual(cross.X(), -830.));
   TRY_TESTME(IsEqual(cross.Y(), 1000.));
   TRY_TESTME(IsEqual(cross.Z(), -390.));

   //
   // Test Increment and Decrement
   //
   vec.SetSize(Size3d(10, 20, 30));
   vec2.SetSize(Size3d(50, 60, 70));
   vec.Increment(vec2);
   TRY_TESTME(IsEqual(vec.X(), 60.));
   TRY_TESTME(IsEqual(vec.Y(), 80.));
   TRY_TESTME(IsEqual(vec.Z(), 100.));

   auto vec3 = vec.IncrementBy(vec2);
    // vector 1 unchanged
   TRY_TESTME(IsEqual(vec.X(), 60.));
   TRY_TESTME(IsEqual(vec.Y(), 80.));
   TRY_TESTME(IsEqual(vec.Z(), 100.));
   TRY_TESTME(IsEqual(vec3.X(), 110.));
   TRY_TESTME(IsEqual(vec3.Y(), 140.));
   TRY_TESTME(IsEqual(vec3.Z(), 170.));

   vec.SetSize(Size3d(10, 20, 30));
   vec2.SetSize(Size3d(50, 60, 70));
   vec.Decrement(vec2);
   TRY_TESTME(IsEqual(vec.X(), -40.));
   TRY_TESTME(IsEqual(vec.Y(), -40.));
   TRY_TESTME(IsEqual(vec.Z(), -40.));

   vec3 = vec.DecrementBy(vec2);
   // vector 1, unchanged
   TRY_TESTME(IsEqual(vec.X(), -40.));
   TRY_TESTME(IsEqual(vec.Y(), -40.));
   TRY_TESTME(IsEqual(vec.Z(), -40.));
   TRY_TESTME(IsEqual(vec3.X(), -90.));
   TRY_TESTME(IsEqual(vec3.Y(), -100.));
   TRY_TESTME(IsEqual(vec3.Z(), -110.));


   TESTME_EPILOG("Vector3d");
}
#endif // _UNITTEST


