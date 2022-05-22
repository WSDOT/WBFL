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
#include <GeomModel/Primitives3d.h>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace WBFL::Geometry;

Size3d::Size3d()
{
}

Size3d::Size3d(Float64 dx, Float64 dy,Float64 dz)
{
   SetDimensions(dx, dy, dz);
}

Size3d::Size3d(const Point3d& point)
{
   SetDimensions(point);
}

Size3d::~Size3d()
{
}

Size3d Size3d::operator+(const Size3d& size) const
{
   return Size3d( m_Dx + size.Dx(), m_Dy + size.Dy(), m_Dz + size.Dz() );
}

Size3d Size3d::operator-(const Size3d& size) const
{
   return Size3d( m_Dx - size.Dx(), m_Dy - size.Dy(), m_Dz - size.Dz() );
}

Size3d Size3d::operator*(Float64 c) const
{
   return Size3d( m_Dx*c, m_Dy*c, m_Dz*c );
}

Size3d Size3d::operator/(Float64 c) const
{
   return Size3d( m_Dx/c, m_Dy/c, m_Dz/c );
}

Size3d Size3d::operator-() const
{
   return Size3d(-m_Dx,-m_Dy,-m_Dz);
}

bool Size3d::operator==(const Size3d& rOther) const
{
   return IsEqual( m_Dx, rOther.Dx() ) && IsEqual(m_Dy, rOther.Dy() ) && IsEqual(m_Dz,rOther.Dz());
}

bool Size3d::operator!=(const Size3d& rOther) const
{
   return !(*this == rOther);
}

Size3d& Size3d::operator+= (const Size3d& rOther)
{
   m_Dx += rOther.Dx();
   m_Dy += rOther.Dy();
   m_Dz += rOther.Dz();
   return *this;
}

Size3d& Size3d::operator-= (const Size3d& rOther)
{
   m_Dx -= rOther.Dx();
   m_Dy -= rOther.Dy();
   m_Dz -= rOther.Dz();
   return *this;
}

Size3d& Size3d::operator/= (Float64 c)
{
   m_Dx /= c;
   m_Dy /= c;
   m_Dz /= c;
   return *this;
}

Size3d& Size3d::operator*= (Float64 c)
{
   m_Dx *= c;
   m_Dy *= c;
   m_Dz *= c;
   return *this;
}

Float64 Size3d::Magnitude() const
{
   return sqrt( m_Dx*m_Dx + m_Dy*m_Dy + m_Dz*m_Dz );
}

Float64 Size3d::Dx() const
{
   return m_Dx;
}

Float64& Size3d::Dx()
{
   return m_Dx;
}

Float64 Size3d::Dy() const
{
   return m_Dy;
}

Float64& Size3d::Dy()
{
   return m_Dy;
}

Float64 Size3d::Dz() const
{
   return m_Dz;
}

Float64& Size3d::Dz()
{
   return m_Dz;
}

void Size3d::SetDimensions(Float64 dx, Float64 dy, Float64 dz)
{
   m_Dx = dx;
   m_Dy = dy;
   m_Dz = dz;
}

void Size3d::SetDimensions(const Point3d& point)
{
   SetDimensions(point.X(), point.Y(), point.Z());
}

void Size3d::GetDimensions(Float64* dx, Float64* dy, Float64* dz) const
{
   *dx = m_Dx;
   *dy = m_Dy;
   *dz = m_Dz;
}

#if defined _DEBUG
void Size3d::Dump(WBFL::Debug::LogContext& os) const
{
   os << "Dump for Size3d" << WBFL::Debug::endl;
   os << "  (m_Dx, m_Dy, m_Dz) = (" << m_Dx << ", " << m_Dy << ", " << m_Dz << ")" << WBFL::Debug::endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool Size3d::TestMe(WBFL::Debug::Log& rlog)
{
   return true;
}
#endif // _UNITTEST

std::ostream& operator<<(std::ostream& os,Size3d& size)
{
   os << "(" << size.Dx() << " x " << size.Dy() << " x " << size.Dz() << ")";
   return os;
}






Point3d::Point3d()
{
}

Point3d::Point3d(Float64 x,Float64 y,Float64 z)
{
   Move(x, y, z);
}

Point3d::~Point3d()
{
}

bool Point3d::operator==(const Point3d& other) const
{
   return IsEqual(m_X, other.X()) && IsEqual(m_Y, other.Y()) && IsEqual(m_Z, other.Z());
}

bool Point3d::operator!=(const Point3d& other) const
{
   return !(*this == other);
}

Point3d Point3d::operator+ (const Size3d& size) const
{
   return Point3d(m_X+size.Dx(), m_Y+size.Dy(), m_Z + size.Dz());
}

Point3d Point3d::operator- (const Size3d& size) const
{
   return Point3d(m_X-size.Dx(), m_Y-size.Dy(), m_Z - size.Dz());
}

Size3d Point3d::operator- (const Point3d& p) const
{
   return Size3d(m_X-p.X(), m_Y-p.Y(), m_Z-p.Z());
}

Point3d Point3d::operator- () const
{
   return Point3d(-m_X,-m_Y,-m_Z);
}

Point3d& Point3d::operator+= (const Size3d& size)
{
   return Offset( size );
}

Point3d& Point3d::operator-= (const Size3d& size)
{
   return Offset( -size );
}

Float64 Point3d::Magnitude() const
{
   return sqrt( m_X*m_X + m_Y*m_Y + m_Z*m_Z);
}

void Point3d::Move(Float64 x,Float64 y,Float64 z)
{
   m_X = x;
   m_Y = y;
   m_Z = z;
}

void Point3d::Move(const Point3d& newPosition)
{
   m_X = newPosition.X();
   m_Y = newPosition.Y(); 
   m_Z = newPosition.Z(); 
}

Float64 Point3d::Distance(Float64 x, Float64 y, Float64 z) const
{
   return Distance(Point3d(x, y, z));
}

Float64 Point3d::Distance(const Point3d& p) const
{
   Size3d size = (p - *this);
   return size.Magnitude();
}

Point3d& Point3d::Offset(Float64 dx,Float64 dy,Float64 dz)
{
   m_X += dx;
   m_Y += dy;
   m_Z += dz;
   return *this;
}

Point3d& Point3d::Offset(const Size3d& size)
{
   m_X += size.Dx();
   m_Y += size.Dy();
   m_Z += size.Dz();
   return *this;
}

Point3d Point3d::OffsetBy(Float64 dx,Float64 dy,Float64 dz) const
{
   return Point3d( m_X+dx, m_Y+dy, m_Z+dz );
}

Point3d Point3d::OffsetBy(const Size3d& size) const
{
   return Point3d( m_X+size.Dx(), m_Y+size.Dy(), m_Z+size.Dz() );
}

Float64 Point3d::X() const
{
   return m_X;
}

Float64& Point3d::X()
{
   return m_X;
}

Float64 Point3d::Y() const
{
   return m_Y;
}

Float64& Point3d::Y()
{
   return m_Y;
}

Float64 Point3d::Z() const
{
   return m_Z;
}

Float64& Point3d::Z()
{
   return m_Z;
}

void Point3d::GetLocation(Float64* pX, Float64* pY, Float64* pZ) const
{
   *pX = m_X;
   *pY = m_Y;
   *pZ = m_Z;
}

#if defined _DEBUG
void Point3d::Dump(WBFL::Debug::LogContext& os) const
{
   os << "Dump for Point3d" << WBFL::Debug::endl;
   os << "  (m_X, m_Y, m_Z) = ("<< m_X<<", "<< m_Y<<", "<< m_Z<<")"<< WBFL::Debug::endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool Point3d::TestMe(WBFL::Debug::Log& rlog)
{
   return true;
}
#endif // _UNITTEST

std::ostream& operator<<(std::ostream& os,const Point3d& p)
{
   os << "(" << p.X() << "," << p.Y() << "," << p.Z() << ")";
   return os;
}
