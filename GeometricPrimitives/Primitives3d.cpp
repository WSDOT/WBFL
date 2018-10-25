///////////////////////////////////////////////////////////////////////
// Geometry - Modeling of geometric primitives
// Copyright (C) 1999  Washington State Department of Transportation
//                     Bridge and Structures Office
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

#include <GeometricPrimitives\GeometryLib.h>

#include <GeometricPrimitives\Primitives3d.h>
#include <System\Exception.h>
#include <MathEx.h>
#include <math.h>
#include <iostream>
#include <xutility>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   gpSize3d
****************************************************************************/

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
gpSize3d::gpSize3d()
{
   m_Dx = 0;
   m_Dy = 0;
   m_Dz = 0;
}

gpSize3d::gpSize3d(const gpSize3d& rOther)
{
   MakeCopy(rOther);
}

gpSize3d::gpSize3d(Float64 dx, Float64 dy,Float64 dz)
{
   m_Dx = dx;
   m_Dy = dy;
   m_Dz = dz;
}

gpSize3d::gpSize3d(const gpPoint3d& point)
{
   m_Dx = point.X();
   m_Dy = point.Y();
   m_Dz = point.Z();
}

gpSize3d::~gpSize3d()
{
}

//======================== OPERATORS  =======================================
gpSize3d& gpSize3d::operator= (const gpSize3d& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}
   
gpSize3d gpSize3d::operator + (const gpSize3d& size) const
{
   return gpSize3d( m_Dx + size.Dx(), m_Dy + size.Dy(), m_Dz + size.Dz() );
}

gpSize3d gpSize3d::operator - (const gpSize3d& size) const
{
   return gpSize3d( m_Dx - size.Dx(), m_Dy - size.Dy(), m_Dz - size.Dz() );
}

gpSize3d gpSize3d::operator*(Float64 c) const
{
   return gpSize3d( m_Dx*c, m_Dy*c, m_Dz*c );
}

gpSize3d gpSize3d::operator/(Float64 c) const
{
   return gpSize3d( m_Dx/c, m_Dy/c, m_Dz/c );
}

gpSize3d gpSize3d::operator- () const
{
   return gpSize3d(-m_Dx,-m_Dy,-m_Dz);
}

bool gpSize3d::operator==(const gpSize3d& rOther) const
{
   return IsEqual( m_Dx, rOther.Dx() ) && IsEqual(m_Dy, rOther.Dy() ) && IsEqual(m_Dz,rOther.Dz());
}

bool gpSize3d::operator!=(const gpSize3d& rOther) const
{
   return !(*this == rOther);
}

gpSize3d& gpSize3d::operator+= (const gpSize3d& rOther)
{
   m_Dx += rOther.Dx();
   m_Dy += rOther.Dy();
   m_Dz += rOther.Dz();
   return *this;
}

gpSize3d& gpSize3d::operator-= (const gpSize3d& rOther)
{
   m_Dx -= rOther.Dx();
   m_Dy -= rOther.Dy();
   m_Dz -= rOther.Dz();
   return *this;
}

gpSize3d& gpSize3d::operator/= (Float64 c)
{
   m_Dx /= c;
   m_Dy /= c;
   m_Dz /= c;
   return *this;
}

gpSize3d& gpSize3d::operator*= (Float64 c)
{
   m_Dx *= c;
   m_Dy *= c;
   m_Dz *= c;
   return *this;
}

//======================== OPERATIONS =======================================
Float64 gpSize3d::Magnitude() const
{
   return sqrt( m_Dx*m_Dx + m_Dy*m_Dy + m_Dz*m_Dz );
}

//======================== ACCESS     =======================================
Float64 gpSize3d::Dx() const
{
   return m_Dx;
}

Float64& gpSize3d::Dx()
{
   return m_Dx;
}

Float64 gpSize3d::Dy() const
{
   return m_Dy;
}

Float64& gpSize3d::Dy()
{
   return m_Dy;
}

Float64 gpSize3d::Dz() const
{
   return m_Dz;
}

Float64& gpSize3d::Dz()
{
   return m_Dz;
}

//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG

void gpSize3d::Dump(dbgDumpContext& os) const
{
   os << "Dump for gpSize3d" << endl;
   os << "  (m_Dx, m_Dy, m_Dz) = (" << m_Dx << ", " << m_Dy << ", " << m_Dz << ")" << endl;
}

#endif // _DEBUG

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void gpSize3d::MakeCopy(const gpSize3d& rOther)
{
   m_Dx = rOther.m_Dx;
   m_Dy = rOther.m_Dy;
   m_Dz = rOther.m_Dz;
}

void gpSize3d::MakeAssignment(const gpSize3d& rOther)
{
   MakeCopy( rOther );
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================
std::ostream& operator<<(std::ostream& os,gpSize3d& size)
{
   os << "(" << size.Dx() << " x " << size.Dy() << " x " << size.Dz() << ")";
   return os;
}


/****************************************************************************
CLASS
   gpPoint3d
****************************************************************************/

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
gpPoint3d::gpPoint3d()
{
   m_X = 0;
   m_Y = 0;
   m_Z = 0;
}

gpPoint3d::gpPoint3d(Float64 x,Float64 y,Float64 z)
{
   m_X = x;
   m_Y = y;
   m_Z = z;
}

gpPoint3d::gpPoint3d(const gpPoint3d& rOther)
{
   MakeCopy(rOther);
}

gpPoint3d::~gpPoint3d()
{
}

//======================== OPERATORS  =======================================
gpPoint3d& gpPoint3d::operator= (const gpPoint3d& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

gpPoint3d gpPoint3d::operator+ (const gpSize3d& size) const
{
   return gpPoint3d(m_X+size.Dx(), m_Y+size.Dy(), m_Z + size.Dz());
}

gpPoint3d gpPoint3d::operator- (const gpSize3d& size) const
{
   return gpPoint3d(m_X-size.Dx(), m_Y-size.Dy(), m_Z - size.Dz());
}

gpSize3d gpPoint3d::operator- (const gpPoint3d& p) const
{
   return gpSize3d(m_X-p.X(), m_Y-p.Y(), m_Z-p.Z());
}

gpPoint3d gpPoint3d::operator- () const
{
   return gpPoint3d(-m_X,-m_Y,-m_Z);
}

gpPoint3d& gpPoint3d::operator+= (const gpSize3d& size)
{
   return Offset( size );
}

gpPoint3d& gpPoint3d::operator-= (const gpSize3d& size)
{
   return Offset( -size );
}

//======================== OPERATIONS =======================================

Float64 gpPoint3d::Magnitude() const
{
   return sqrt( m_X*m_X + m_Y*m_Y + m_Z*m_Z);
}

void gpPoint3d::Move(Float64 x,Float64 y,Float64 z)
{
   m_X = x;
   m_Y = y;
   m_Z = z;
}

void gpPoint3d::Move(const gpPoint3d& newPosition)
{
   m_X = newPosition.X();
   m_Y = newPosition.Y(); 
   m_Z = newPosition.Z(); 
}

Float64 gpPoint3d::Distance(const gpPoint3d& p) const
{
   gpSize3d size = (p - *this);
   return size.Magnitude();
}

gpPoint3d& gpPoint3d::Offset(Float64 dx,Float64 dy,Float64 dz)
{
   m_X += dx;
   m_Y += dy;
   m_Z += dz;
   return *this;
}

gpPoint3d& gpPoint3d::Offset(const gpSize3d& size)
{
   m_X += size.Dx();
   m_Y += size.Dy();
   m_Z += size.Dz();
   return *this;
}

gpPoint3d gpPoint3d::OffsetBy(Float64 dx,Float64 dy,Float64 dz) const
{
   return gpPoint3d( m_X+dx, m_Y+dy, m_Z+dz );
}

gpPoint3d gpPoint3d::OffsetBy(const gpSize3d& size) const
{
   return gpPoint3d( m_X+size.Dx(), m_Y+size.Dy(), m_Z+size.Dz() );
}

//======================== ACCESS     =======================================
Float64 gpPoint3d::X() const
{
   return m_X;
}

Float64& gpPoint3d::X()
{
   return m_X;
}

Float64 gpPoint3d::Y() const
{
   return m_Y;
}

Float64& gpPoint3d::Y()
{
   return m_Y;
}

Float64 gpPoint3d::Z() const
{
   return m_Z;
}

Float64& gpPoint3d::Z()
{
   return m_Z;
}

//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG

void gpPoint3d::Dump(dbgDumpContext& os) const
{
   os << "Dump for gpPointd" << endl;
   os << "  (m_X, m_Y, m_Z) = ("<< m_X<<", "<< m_Y<<", "<< m_Z<<")"<<endl;
}

#endif // _DEBUG


////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void gpPoint3d::MakeCopy(const gpPoint3d& rOther)
{
   m_X = rOther.m_X;
   m_Y = rOther.m_Y;
   m_Z = rOther.m_Z;
}

void gpPoint3d::MakeAssignment(const gpPoint3d& rOther)
{
   MakeCopy( rOther );
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

bool operator==(const gpPoint3d& lhs, const gpPoint3d& rhs)
{
   return IsEqual( lhs.X(), rhs.X(),1.0e-6 ) && IsEqual( lhs.Y(), rhs.Y(),1.0e-6 ) && IsEqual( lhs.Z(), rhs.Z(),1.0e-6 );
}

bool operator!=(const gpPoint3d& lhs, const gpPoint3d& rhs)
{
   return !( lhs == rhs );
}

std::ostream& operator<<(std::ostream& os,const gpPoint3d& p)
{
   os << "(" << p.X() << "," << p.Y() << "," << p.Z() << ")";
   return os;
}


