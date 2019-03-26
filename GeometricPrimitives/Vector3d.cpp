///////////////////////////////////////////////////////////////////////
// Geometry - Modeling of geometric primitives
// Copyright © 1999-2019  Washington State Department of Transportation
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

#include <GeometricPrimitives\GeometryLib.h>
#include <GeometricPrimitives\Vector3d.h>
#include <GeometricPrimitives\Primitives3d.h>
#include <math.h>
#include <MathEx.h>
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   gpVector3d
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
gpVector3d::gpVector3d()
{
   m_X = 0;
   m_Y = 0;
   m_Z = 0;
}

gpVector3d::gpVector3d(const gpPoint3d& a, const gpPoint3d& b)
{
   m_X = b.X() - a.X();
   m_Y = b.Y() - a.Y();
   m_Z = b.Z() - a.Z();
}

gpVector3d::gpVector3d(Float64 x,Float64 y,Float64 z)
{
   m_X = x;
   m_Y = y;
   m_Z = z;
}

gpVector3d::gpVector3d(const gpSize3d& size)
{
   m_X = size.Dx();
   m_Y = size.Dy();
   m_Z = size.Dz();
}


gpVector3d::gpVector3d(const gpVector3d& rOther)
{
   MakeCopy(rOther);
}

gpVector3d::~gpVector3d()
{
}

//======================== OPERATORS  =======================================
gpVector3d& gpVector3d::operator= (const gpVector3d& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

gpVector3d gpVector3d::operator - () const
{
   return gpVector3d(gpSize3d(-m_X, -m_Y, -m_Z));
}

gpVector3d& gpVector3d::operator += (const gpVector3d& rOther)
{
   m_X += rOther.m_X;
   m_Y += rOther.m_Y;
   m_Z += rOther.m_Z;
   return *this;
}

gpVector3d& gpVector3d::operator -= (const gpVector3d& rOther)
{
   m_X -= rOther.m_X;
   m_Y -= rOther.m_Y;
   m_Z -= rOther.m_Z;
   return *this;
}

//======================== OPERATIONS =======================================

Float64 gpVector3d::AngleBetween(const gpVector3d& rOther) const
{
   Float64 x = Dot(rOther) / (GetMagnitude() * rOther.GetMagnitude());
   if ( ::IsZero(x-1.0) )
      x = 1.0;

   return acos(x);
}

Float64 gpVector3d::Projection(const gpVector3d& rOther) const
{
   return this->Dot(rOther) / rOther.GetMagnitude();
}

Float64 gpVector3d::Dot(const gpVector3d& rOther) const
{
   return (m_X*rOther.m_X) + (m_Y*rOther.m_Y) + (m_Z*rOther.m_Z);
}

gpVector3d gpVector3d::Cross(const gpVector3d& rOther) const
{
   gpVector3d cross;
   cross.m_X = m_Y*rOther.m_Z - m_Z*rOther.m_Y;
   cross.m_Y = m_Z*rOther.m_X - m_X*rOther.m_Z;
   cross.m_Z = m_X*rOther.m_Y - m_Y*rOther.m_Z;

   return cross;
}

gpSize3d gpVector3d::GetSize()const
{
   return gpSize3d(m_X, m_Y,m_Z);
}

bool gpVector3d::IsZero() const
{
   return ( ::IsZero(m_X) && ::IsZero(m_Y) && ::IsZero(m_Z));
}


Float64 gpVector3d::GetMagnitude() const
{
   return sqrt(GetRelMagnitude());
}

Float64 gpVector3d::GetRelMagnitude() const
{
   return m_X*m_X + m_Y*m_Y + m_Z*m_Z;
}

gpVector3d& gpVector3d::Reflect()
{
   m_X = -m_X;
   m_Y = -m_Y;
   m_Z = -m_Z;
   return *this;
}

gpVector3d& gpVector3d::Normalize()
{
   Float64 len = this->GetMagnitude();
   if (len != 0)
   {
      m_X /= len;
      m_Y /= len;
      m_Z /= len;
   }
   return *this;
}

gpVector3d gpVector3d::NormalizeBy() const
{
   Float64 len = this->GetMagnitude();
   if ( !::IsZero(len) )
      return gpVector3d(gpSize3d(m_X/len, m_Y/len, m_Z/len));
   else
      return gpVector3d();
}

gpVector3d& gpVector3d::Scale(Float64 factor)
{
   m_X *= factor;
   m_Y *= factor; 
   m_Z *= factor; 
   return *this;
}

gpVector3d gpVector3d::ScaleBy(Float64 factor) const
{
   gpVector3d temp(*this);
   return temp.Scale(factor);
}

gpVector3d& gpVector3d::SetSize(const gpSize3d& size)
{
   m_X = size.Dx();
   m_Y = size.Dy();
   m_Z = size.Dz();
   return *this;
}


gpVector3d& gpVector3d::SetMagnitude(Float64 magnitude)
{
   this->Normalize();
   m_X *= magnitude;
   m_Y *= magnitude;
   m_Z *= magnitude;
   return *this;
}

gpVector3d& gpVector3d::Offset(Float64 dx,Float64 dy,Float64 dz)
{
   m_X += dx;
   m_Y += dy;
   m_Z += dz;
   return *this;
}

gpVector3d& gpVector3d::Offset(const gpSize3d& size)
{
   return Offset(size.Dx(), size.Dy(), size.Dz());
}

gpVector3d gpVector3d::OffsetBy(Float64 dx, Float64 dy,Float64 dz) const
{
   return gpVector3d(gpSize3d(m_X+dx, m_Y+dy, m_Z+dz));
}

gpVector3d gpVector3d::OffsetBy(const gpSize3d& size) const
{
   return OffsetBy(size.Dx(), size.Dy(), size.Dz());
}


Float64 gpVector3d::X() const
{
   return m_X;
}

Float64& gpVector3d::X()
{
   return m_X;
}

Float64 gpVector3d::Y() const
{
   return m_Y;
}

Float64& gpVector3d::Y()
{
   return m_Y;
}

Float64 gpVector3d::Z() const
{
   return m_Z;
}

Float64& gpVector3d::Z()
{
   return m_Z;
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool gpVector3d::AssertValid() const
{
   return true;
}

void gpVector3d::Dump(dbgDumpContext& os) const
{
   os << "Dump for gpVector3d" << endl;
   os << "  m_X = "<<m_X<<", m_Y = "<<m_Y << ", m_Z = " << m_Z <<endl;
}
#endif // _DEBUG

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void gpVector3d::MakeCopy(const gpVector3d& rOther)
{
   m_X = rOther.m_X;
   m_Y = rOther.m_Y;
   m_Z = rOther.m_Z;
}

void gpVector3d::MakeAssignment(const gpVector3d& rOther)
{
   MakeCopy( rOther );
}

//======================== TESTING =======================================
//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================


bool operator==(const gpVector3d& lhs, const gpVector3d& rhs)
{
   return (IsEqual(lhs.X(),rhs.X(),1.0e-10) && 
           IsEqual(lhs.Y(),rhs.Y(),1.0e-10) &&
           IsEqual(lhs.Z(),rhs.Z(),1.0e-10));
}

bool operator!=(const gpVector3d& lhs, const gpVector3d& rhs)
{
   return !(lhs==rhs);
}

gpVector3d operator+(const gpVector3d& lhs, const gpVector3d& rhs)
{
   return gpVector3d(gpSize3d(lhs.X()+rhs.X(), lhs.Y()+rhs.Y(), lhs.Z()+rhs.Z()));
}

gpVector3d operator-(const gpVector3d& lhs, const gpVector3d& rhs)
{
   return gpVector3d(gpSize3d(lhs.X()-rhs.X(), lhs.Y()-rhs.Y(), lhs.Z()-rhs.Z()));
}

#if defined _UNITTEST
bool gpVector3d::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("gpVector3d");

//   // test all of the features of a vector
//
//   Float64 pi = 4.*atan(1.);
//
//   const gpVector3d up(1,pi/2), left(1,pi), down(1,3*pi/2), right(1,0);
//   const gpVector3d at45(gpSize2d(1,1)), at135(gpSize2d(-1,1)), 
//                    at315(gpSize2d(1,-1)), at225(gpSize2d(-1,-1));
//
//   gpVector3d testvec1, testvec2;
//
//   // size
//   gpSize2d ts(2,3);
//   testvec1.SetSize(ts);
//   TRY_TEST ( ts == testvec1.GetSize());   
//
//   // dot product
//   Float64 val = right.Dot(up);
//   TRY_TEST ( IsEqual(val,0.) );
//
//   // add, subtract, reflection
//   testvec1 = right + up;
//   testvec2 = -left - down;
//   TRY_TEST (testvec1 == at45);
//   TRY_TEST (testvec1 == testvec2);
//
//   // setmagnitude, length
//   testvec1.SetMagnitude(4);
//   val = testvec1.GetMagnitude();
//   TRY_TEST(IsEqual(val,4.0));
//
//   // colinearity
//   TRY_TEST (testvec1.IsCollinear(testvec2));
//
//   // assignment, reflection, ==
//   testvec1 = at45;
//   testvec1.Reflect();
//   TRY_TEST (testvec1 == at225);
//
//   // Normal
//   testvec1 = at315.Normal(Left);
//   TRY_TEST (testvec1 == at45);
//
//   testvec1 = at315.Normal(Right);
//   TRY_TEST (testvec1 == at225);
//
//   // Normalize
//   testvec1 = at45.NormalizeBy();
//   val = testvec1.GetMagnitude();
//   TRY_TEST ( IsEqual(val, 1.,1.0e-6));
//   TRY_TEST ( testvec1.IsCollinear(at45));
//
//   // Offset, OffsetBy
//   testvec1 = at45.OffsetBy(21,21);
//   testvec2 = testvec1.Normal();
//   val = at45.Dot(testvec2);
//   TRY_TEST (val == 0);
//
//   // Rotate, RotateBy
//   testvec1 = right;
//   testvec2 = testvec1.RotateBy(atan(1.));
//   TRY_TEST (testvec2.IsCollinear(at45));
//
//   // scale, scaleby
//   val = at45.GetMagnitude();
//   testvec1 = at45.ScaleBy(4);
//   TRY_TEST (IsEqual(4*val, testvec1.GetMagnitude()));
//
//   // projection.
//   val = right.Projection(at315);
//   TRY_TEST(IsEqual(val, sqrt(2.)/2));
//
//#if defined _DEBUG
//   testvec1.Dump(rlog.GetDumpCtx());
//#endif

   TESTME_EPILOG("gpVector3d");
}
#endif // _UNITTEST


