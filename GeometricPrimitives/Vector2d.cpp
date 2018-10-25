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
#include <GeometricPrimitives\Vector2d.h>
#include <GeometricPrimitives\GeomOp2d.h>
#include <GeometricPrimitives\Primitives.h>
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
   gpVector2d
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
gpVector2d::gpVector2d()
{
   m_X = 0;
   m_Y = 0;
}

gpVector2d::gpVector2d(Float64 magnitude, Float64 direction)
{
   m_X = magnitude * cos(direction);
   m_Y = magnitude * sin(direction);
}

gpVector2d::gpVector2d(const gpPoint2d& a, const gpPoint2d& b)
{
   m_X = b.X() - a.X();
   m_Y = b.Y() - a.Y();
}


gpVector2d::gpVector2d(const gpSize2d& size)
{
   m_X = size.Dx();
   m_Y = size.Dy();
}


gpVector2d::gpVector2d(const gpVector2d& rOther)
{
   MakeCopy(rOther);
}

gpVector2d::~gpVector2d()
{
}

//======================== OPERATORS  =======================================
gpVector2d& gpVector2d::operator= (const gpVector2d& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

gpVector2d gpVector2d::operator - () const
{
   return gpVector2d(gpSize2d(-m_X, -m_Y));
}

gpVector2d& gpVector2d::operator += (const gpVector2d& rOther)
{
   m_X += rOther.m_X;
   m_Y += rOther.m_Y;
   return *this;
}

gpVector2d& gpVector2d::operator -= (const gpVector2d& rOther)
{
   m_X -= rOther.m_X;
   m_Y -= rOther.m_Y;
   return *this;
}

//======================== OPERATIONS =======================================

Float64 gpVector2d::AngleBetween(const gpVector2d& rOther) const
{
   Float64 mag1 = GetMagnitude();
   Float64 mag2 = rOther.GetMagnitude();

   PRECONDITION( !::IsZero(mag1) && !::IsZero(mag2) );

   Float64 x = Dot(rOther)/(mag1*mag2);
   if ( ::IsZero(x-1.0) )
      x = 1.0;

   Float64 angle = acos(x);
   angle = gpGeomOp2d::NormalizeAngle(angle);
   return angle;
}

Float64 gpVector2d::Projection(const gpVector2d& rOther) const
{
   return this->Dot(rOther) / rOther.GetMagnitude();
}

Float64 gpVector2d::Dot(const gpVector2d& rOther) const
{
   return (m_X*rOther.m_X) + (m_Y*rOther.m_Y);
}

Float64 gpVector2d::GetDirection() const
{
   return gpGeomOp2d::NormalizeAngle( atan2(m_Y, m_X) );
}


gpSize2d gpVector2d::GetSize()const
{
   return gpSize2d(m_X, m_Y);
}

bool gpVector2d::IsZero() const
{
   return ( ::IsZero(m_X) && ::IsZero(m_Y) );
}


Float64 gpVector2d::GetMagnitude() const
{
   return sqrt(GetRelMagnitude());
}

Float64 gpVector2d::GetRelMagnitude() const
{
   return m_X*m_X + m_Y*m_Y;
}


gpVector2d& gpVector2d::Reflect()
{
   m_X = -m_X;
   m_Y = -m_Y;
   return *this;
}

gpVector2d& gpVector2d::Normalize()
{
   Float64 len = this->GetMagnitude();
   if (len != 0)
   {
      m_X /= len;
      m_Y /= len;
   }
   return *this;
}

gpVector2d gpVector2d::NormalizeBy() const
{
   Float64 len = this->GetMagnitude();
   if ( !::IsZero(len) )
      return gpVector2d(gpSize2d(m_X/len, m_Y/len));
   else
      return gpVector2d();
}

gpVector2d gpVector2d::Normal(Side side) const
{
   if (side==Left)
      return gpVector2d(gpSize2d(-m_Y, m_X));
   else
      return gpVector2d(gpSize2d(m_Y, -m_X));
}

gpVector2d& gpVector2d::Scale(Float64 factor)
{
   m_X *= factor;
   m_Y *= factor; 
   return *this;
}

gpVector2d gpVector2d::ScaleBy(Float64 factor) const
{
   gpVector2d temp(*this);
   return temp.Scale(factor);
}

gpVector2d& gpVector2d::SetDirection(Float64 direction)
{
   Float64 mag = this->GetMagnitude();
   *this = gpVector2d(mag, direction);
   return *this;
}

gpVector2d& gpVector2d::SetSize(const gpSize2d& size)
{
   m_X = size.Dx();
   m_Y = size.Dy();
   return *this;
}


gpVector2d& gpVector2d::SetMagnitude(Float64 magnitude)
{
   this->Normalize();
   m_X *= magnitude;
   m_Y *= magnitude;
   return *this;
}

gpVector2d gpVector2d::SetMagnitudeBy(Float64 magnitude) const
{
   gpVector2d t(*this);
   return t.SetMagnitude(magnitude);
}


gpVector2d& gpVector2d::Offset(Float64 dx,Float64 dy)
{
   m_X += dx;
   m_Y += dy;
   return *this;
}

gpVector2d& gpVector2d::Offset(const gpSize2d& size)
{
   return Offset(size.Dx(), size.Dy());
}

gpVector2d gpVector2d::OffsetBy(Float64 dx, Float64 dy) const
{
   return gpVector2d(gpSize2d(m_X+dx, m_Y+dy));
}

gpVector2d gpVector2d::OffsetBy(const gpSize2d& size) const
{
   return OffsetBy(size.Dx(), size.Dy());
}

gpVector2d& gpVector2d::Rotate(Float64 angle)
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

gpVector2d gpVector2d::RotateBy(Float64 angle) const
{
   gpVector2d temp(*this);
   return temp.Rotate(angle);
}


Float64 gpVector2d::X() const
{
   return m_X;
}

Float64& gpVector2d::X()
{
   return m_X;
}

Float64 gpVector2d::Y() const
{
   return m_Y;
}

Float64& gpVector2d::Y()
{
   return m_Y;
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool gpVector2d::AssertValid() const
{
   return true;
}

void gpVector2d::Dump(dbgDumpContext& os) const
{
   os << "Dump for gpVector2d" << endl;
   os << "  m_X = "<<m_X<<", m_Y = "<<m_Y<<endl;
}
#endif // _DEBUG

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void gpVector2d::MakeCopy(const gpVector2d& rOther)
{
   m_X = rOther.m_X;
   m_Y = rOther.m_Y;
}

void gpVector2d::MakeAssignment(const gpVector2d& rOther)
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


bool operator==(const gpVector2d& lhs, const gpVector2d& rhs)
{
   return (IsEqual(lhs.X(),rhs.X(),1.0e-10) && IsEqual(lhs.Y(),rhs.Y(),1.0e-10));
}

bool operator!=(const gpVector2d& lhs, const gpVector2d& rhs)
{
   return !(lhs==rhs);
}

gpVector2d operator+(const gpVector2d& lhs, const gpVector2d& rhs)
{
   return gpVector2d(gpSize2d(lhs.X()+rhs.X(), lhs.Y()+rhs.Y()));
}

gpVector2d operator-(const gpVector2d& lhs, const gpVector2d& rhs)
{
   return gpVector2d(gpSize2d(lhs.X()-rhs.X(), lhs.Y()-rhs.Y()));
}

#if defined _UNITTEST
bool gpVector2d::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("gpVector2d");

   // test all of the features of a vector

   Float64 pi = 4.*atan(1.);

   const gpVector2d up(1,pi/2), left(1,pi), down(1,3*pi/2), right(1,0);
   const gpVector2d at45(gpSize2d(1,1)), at135(gpSize2d(-1,1)), 
                    at315(gpSize2d(1,-1)), at225(gpSize2d(-1,-1));

   gpVector2d testvec1, testvec2;

   // size
   gpSize2d ts(2,3);
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
   testvec1 = at315.Normal(Left);
   TRY_TESTME (testvec1 == at45);

   testvec1 = at315.Normal(Right);
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

#if defined _DEBUG
   testvec1.Dump(rlog.GetDumpCtx());
#endif
   TESTME_EPILOG("gpVector2d");
}
#endif // _UNITTEST


