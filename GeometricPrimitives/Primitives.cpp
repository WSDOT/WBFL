///////////////////////////////////////////////////////////////////////
// Geometry - Modeling of geometric primitives
// Copyright © 1999-2014, Washington State Department of Transportation, All Rights Reserved
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

#include <GeometricPrimitives\Primitives.h>
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
   gpSize2d
****************************************************************************/

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
gpSize2d::gpSize2d()
{
   m_Dx = 0;
   m_Dy = 0;
}

gpSize2d::gpSize2d(const gpSize2d& rOther)
{
   MakeCopy(rOther);
}

gpSize2d::gpSize2d(Float64 dx, Float64 dy)
{
   m_Dx = dx;
   m_Dy = dy;
}

gpSize2d::gpSize2d(const gpPoint2d& point)
{
   m_Dx = point.X();
   m_Dy = point.Y();
}

gpSize2d::~gpSize2d()
{
}

//======================== OPERATORS  =======================================
gpSize2d& gpSize2d::operator= (const gpSize2d& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}
   
gpSize2d gpSize2d::operator + (const gpSize2d& size) const
{
   return gpSize2d( m_Dx + size.Dx(), m_Dy + size.Dy() );
}

gpSize2d gpSize2d::operator - (const gpSize2d& size) const
{
   return gpSize2d( m_Dx - size.Dx(), m_Dy - size.Dy() );
}

gpSize2d gpSize2d::operator*(Float64 c) const
{
   return gpSize2d( m_Dx*c, m_Dy*c );
}

gpSize2d gpSize2d::operator/(Float64 c) const
{
   return gpSize2d( m_Dx/c, m_Dy/c );
}

gpSize2d gpSize2d::operator- () const
{
   return gpSize2d(-m_Dx,-m_Dy);
}

bool gpSize2d::operator==(const gpSize2d& rOther) const
{
   return IsEqual( m_Dx, rOther.Dx() ) && IsEqual(m_Dy, rOther.Dy() );
}

bool gpSize2d::operator!=(const gpSize2d& rOther) const
{
   return !(*this == rOther);
}

gpSize2d& gpSize2d::operator+= (const gpSize2d& rOther)
{
   m_Dx += rOther.Dx();
   m_Dy += rOther.Dy();
   return *this;
}

gpSize2d& gpSize2d::operator-= (const gpSize2d& rOther)
{
   m_Dx -= rOther.Dx();
   m_Dy -= rOther.Dy();
   return *this;
}

gpSize2d& gpSize2d::operator/= (Float64 c)
{
   m_Dx /= c;
   m_Dy /= c;
   return *this;
}

gpSize2d& gpSize2d::operator*= (Float64 c)
{
   m_Dx *= c;
   m_Dy *= c;
   return *this;
}

//======================== OPERATIONS =======================================
Float64 gpSize2d::Magnitude() const
{
   Float64 mag;
   const Float64 limit = sqrt(Float64_Max);
   if (limit < m_Dx || limit < m_Dy )
      mag = Float64_Max;
   else
      mag = sqrt( m_Dx*m_Dx + m_Dy*m_Dy );

   return mag;
}

//======================== ACCESS     =======================================
Float64 gpSize2d::Dx() const
{
   return m_Dx;
}

Float64& gpSize2d::Dx()
{
   return m_Dx;
}

Float64 gpSize2d::Dy() const
{
   return m_Dy;
}

Float64& gpSize2d::Dy()
{
   return m_Dy;
}

//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG

void gpSize2d::Dump(dbgDumpContext& os) const
{
   os <<_T( "Dump for gpSize2d") << endl;
   os << _T("  (m_Dx, m_Dy) = (")<< m_Dx<<_T(", ")<< m_Dy<<_T(")")<<endl;
}

#endif // _DEBUG

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void gpSize2d::MakeCopy(const gpSize2d& rOther)
{
   m_Dx = rOther.m_Dx;
   m_Dy = rOther.m_Dy;
}

void gpSize2d::MakeAssignment(const gpSize2d& rOther)
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
std::_tostream& operator<<(std::_tostream& os,gpSize2d& size)
{
   os << _T("(") << size.Dx() << _T(" x ") << size.Dy() << _T(")");
   return os;
}


/****************************************************************************
CLASS
   gpPoint2d
****************************************************************************/
gpPoint2d RotatePoint(const gpPoint2d& fixed,Float64 angle, const gpPoint2d& pnt);

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
gpPoint2d::gpPoint2d()
{
   m_X = 0;
   m_Y = 0;
}

gpPoint2d::gpPoint2d(Float64 x,Float64 y)
{
   m_X = x;
   m_Y = y;
}

gpPoint2d::gpPoint2d(const gpPoint2d& rOther)
{
   MakeCopy(rOther);
}

gpPoint2d::~gpPoint2d()
{
}

//======================== OPERATORS  =======================================
gpPoint2d& gpPoint2d::operator= (const gpPoint2d& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

gpPoint2d gpPoint2d::operator+ (const gpSize2d& size) const
{
   return gpPoint2d(m_X+size.Dx(), m_Y+size.Dy());
}

gpPoint2d gpPoint2d::operator- (const gpSize2d& size) const
{
   return gpPoint2d(m_X-size.Dx(), m_Y-size.Dy());
}

gpSize2d gpPoint2d::operator- (const gpPoint2d& p) const
{
   return gpSize2d(m_X-p.X(), m_Y-p.Y());
}

gpPoint2d gpPoint2d::operator- () const
{
   return gpPoint2d(-m_X,-m_Y);
}

gpPoint2d& gpPoint2d::operator+= (const gpSize2d& size)
{
   return Offset( size );
}

gpPoint2d& gpPoint2d::operator-= (const gpSize2d& size)
{
   return Offset( -size );
}

//======================== OPERATIONS =======================================

Float64 gpPoint2d::Magnitude() const
{
   return sqrt( m_X*m_X + m_Y*m_Y );
}

void gpPoint2d::Move(Float64 x,Float64 y)
{
   m_X = x;
   m_Y = y;
}

void gpPoint2d::Move(const gpPoint2d& newPosition)
{
   m_X = newPosition.X();
   m_Y = newPosition.Y(); 
}

Float64 gpPoint2d::Distance(const gpPoint2d& p) const
{
   gpSize2d size = (p - *this);
   return size.Magnitude();
}

gpPoint2d& gpPoint2d::Offset(Float64 dx,Float64 dy)
{
   m_X += dx;
   m_Y += dy;
   return *this;
}

gpPoint2d& gpPoint2d::Offset(const gpSize2d& size)
{
   m_X += size.Dx();
   m_Y += size.Dy();
   return *this;
}

gpPoint2d gpPoint2d::OffsetBy(Float64 dx,Float64 dy) const
{
   return gpPoint2d( m_X+dx, m_Y+dy );
}

gpPoint2d gpPoint2d::OffsetBy(const gpSize2d& size) const
{
   return gpPoint2d( m_X+size.Dx(), m_Y+size.Dy() );
}

gpPoint2d& gpPoint2d::Rotate(const gpPoint2d& centerPoint, Float64 angle)
{
  *this = RotatePoint(centerPoint, angle, *this);
  return *this;
} 



gpPoint2d gpPoint2d::RotateBy(const gpPoint2d& centerPoint, Float64 angle) const
{
   return RotatePoint(centerPoint, angle, *this);
}



//======================== ACCESS     =======================================
Float64 gpPoint2d::X() const
{
   return m_X;
}

Float64& gpPoint2d::X()
{
   return m_X;
}

Float64 gpPoint2d::Y() const
{
   return m_Y;
}

Float64& gpPoint2d::Y()
{
   return m_Y;
}

//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG

void gpPoint2d::Dump(dbgDumpContext& os) const
{
   os << _T("Dump for gpPointd") << endl;
   os << _T("  (m_X, m_Y) = (")<< m_X<<_T(", ")<< m_Y<<_T(")")<<endl;
}

#endif // _DEBUG


////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void gpPoint2d::MakeCopy(const gpPoint2d& rOther)
{
   m_X = rOther.m_X;
   m_Y = rOther.m_Y;
}

void gpPoint2d::MakeAssignment(const gpPoint2d& rOther)
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

bool operator==(const gpPoint2d& lhs, const gpPoint2d& rhs)
{
   return IsEqual( lhs.X(), rhs.X(),1.0e-6 ) && IsEqual( lhs.Y(), rhs.Y(),1.0e-6 );
}

bool operator!=(const gpPoint2d& lhs, const gpPoint2d& rhs)
{
   return !( lhs == rhs );
}

std::_tostream& operator<<(std::_tostream& os,const gpPoint2d& p)
{
   os << _T("(") << p.X() << _T(",") << p.Y() << _T(")");
   return os;
}

gpPoint2d RotatePoint(const gpPoint2d& fixed,Float64 angle,const gpPoint2d& pnt)
{
   gpPoint2d newPnt;

   newPnt.X() = (pnt.X() - fixed.X()) * cos(angle) - (pnt.Y() - fixed.Y()) * sin(angle) + fixed.X();
   newPnt.Y() = (pnt.Y() - fixed.Y()) * cos(angle) + (pnt.X() - fixed.X()) * sin(angle) + fixed.Y();

   return newPnt;
} // RotatePoint



/****************************************************************************
CLASS
   gpRect2d
****************************************************************************/

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
gpRect2d::gpRect2d(void)
{
   m_Left = m_Right = m_Top = m_Bottom = 0;
}

gpRect2d::gpRect2d(Float64 left,  Float64 bottom,
                   Float64 right, Float64 top) :
m_Left(left),
m_Bottom(bottom),
m_Right(right),
m_Top(top)
{
}

gpRect2d::gpRect2d(const gpPoint2d& bottomLeft,const gpPoint2d& topRight) :
m_Left(bottomLeft.X()),
m_Bottom(bottomLeft.Y()),
m_Right(topRight.X()),
m_Top(topRight.Y())
{
}

gpRect2d::gpRect2d(const gpPoint2d& bottomLeft,const gpSize2d& size) :
m_Left( bottomLeft.X() ),
m_Bottom( bottomLeft.Y() ),
m_Right( bottomLeft.X() + size.Dx() ),
m_Top( bottomLeft.Y() + size.Dy() )
{
}

gpRect2d::gpRect2d(const gpRect2d& rOther)
{
   MakeCopy( rOther );
}

//======================== OPERATORS  =======================================

gpRect2d& gpRect2d::operator= (const gpRect2d& rOther)
{
   if ( this != &rOther )
      MakeAssignment( rOther );

   return *this;
}

//======================== OPERATIONS =======================================
Float64 gpRect2d::Area() const
{
   return Height() * Width();
}

void gpRect2d::Set(Float64 left,Float64 bottom,Float64 right,Float64 top)
{
   m_Left   = left;
   m_Bottom = bottom;
   m_Right  = right;
   m_Top    = top;
}

void gpRect2d::Set(const gpPoint2d& bottomLeft, const gpPoint2d& topRight)
{
   m_Left   = bottomLeft.X();
   m_Bottom = bottomLeft.Y();
   m_Right  = topRight.X();
   m_Top    = topRight.Y();
}

void gpRect2d::SetEmpty()
{
   SetNull();
}

void gpRect2d::SetNull()
{
   m_Left   = 0;
   m_Bottom = 0;
   m_Right  = 0;
   m_Top    = 0;
}

void gpRect2d::SetWH(Float64 left,Float64 bottom,Float64 width,Float64 height)
{
   m_Left   = left;
   m_Bottom = bottom;
   m_Right  = m_Left + width;
   m_Top    = bottom + height;
}

void gpRect2d::SetWH(const gpPoint2d& bottomLeft,const gpSize2d& size)
{
   SetWH( bottomLeft.X(), bottomLeft.Y(), size.Dx(), size.Dy() );
}

gpPoint2d gpRect2d::TopLeft() const
{
   return gpPoint2d(m_Left,m_Top);
}

gpPoint2d gpRect2d::TopRight() const
{
   return gpPoint2d(m_Right,m_Top);
}

gpPoint2d gpRect2d::BottomLeft() const
{
   return gpPoint2d(m_Left,m_Bottom);
}

gpPoint2d gpRect2d::BottomRight() const
{
   return gpPoint2d(m_Right,m_Bottom);
}

gpPoint2d gpRect2d::Center() const
{
   return gpPoint2d(m_Left + Width()/2, m_Bottom + Height()/2);
}

gpPoint2d gpRect2d::TopCenter() const
{
   return gpPoint2d( m_Left + Width()/2, m_Top );
}

gpPoint2d gpRect2d::BottomCenter() const
{
   return gpPoint2d( m_Left + Width()/2, m_Bottom );
}

gpPoint2d gpRect2d::LeftCenter() const
{
   return gpPoint2d( m_Left, m_Bottom + Height()/2 );
}

gpPoint2d gpRect2d::RightCenter() const
{
   return gpPoint2d( m_Right, m_Bottom + Height()/2 );
}

gpSize2d gpRect2d::Size() const
{
   return gpSize2d(m_Right - m_Left,m_Top - m_Bottom);
}

Float64 gpRect2d::Height() const
{
   return m_Top - m_Bottom;
}

Float64 gpRect2d::Width() const
{
   return m_Right - m_Left;
}

gpRect2d& gpRect2d::Inflate(Float64 dx,Float64 dy)
{
   m_Left   -= dx;
   m_Right  += dx;
   m_Top    += dy;
   m_Bottom -= dy;
   return *this;
}

gpRect2d& gpRect2d::Inflate(const gpSize2d& size)
{
   m_Left   -= size.Dx();
   m_Right  += size.Dx();
   m_Top    += size.Dy();
   m_Bottom -= size.Dy();
   return *this;
}

gpRect2d gpRect2d::InflateBy(Float64 dx,Float64 dy) const
{
   gpRect2d rect( *this );
   rect.Left()   -= dx;
   rect.Right()  += dx;
   rect.Top()    += dy;
   rect.Bottom() -= dy;
   return rect;
}

gpRect2d gpRect2d::InflateBy(const gpSize2d& size) const
{
   gpRect2d rect( *this );
   rect.Left()   -= size.Dx();
   rect.Right()  += size.Dx();
   rect.Top()    += size.Dy();
   rect.Bottom() -= size.Dy();
   return rect;
}

gpRect2d& gpRect2d::MoveTo(Float64 bottom,Float64 left)
{
   m_Right = left + Width();
   m_Top = bottom + Height();
   m_Bottom = bottom;
   m_Left = left;
   return *this;
}

gpRect2d gpRect2d::MovedTo(Float64 bottom,Float64 left) const
{
   return gpRect2d(left,bottom,left+Width(),bottom+Height());
}

gpRect2d& gpRect2d::Normalize()
{
   Float64 temp;
   if ( m_Left > m_Right )
   {
      temp = m_Right;
      m_Right = m_Left;
      m_Left = temp;
   }

   if ( m_Top < m_Bottom )
   {
      temp = m_Bottom;
      m_Bottom = m_Top;
      m_Top = temp;
   }

   return *this;
}

gpRect2d gpRect2d::Normalized() const
{
   return gpRect2d( gpPoint2d( _cpp_min(m_Left,m_Right), _cpp_min(m_Top,m_Bottom) ),
                    gpPoint2d( _cpp_max(m_Left,m_Right), _cpp_max(m_Top,m_Bottom) ) );
}

gpRect2d& gpRect2d::Offset(Float64 dx,Float64 dy)
{
   m_Left   += dx;
   m_Right  += dx;
   m_Top    += dy;
   m_Bottom += dy;

   return *this;
}

gpRect2d gpRect2d::OffsetBy(Float64 dx,Float64 dy) const
{
   return gpRect2d( m_Left+dx, m_Bottom+dy, m_Right+dx, m_Top+dy);
}

gpRect2d& gpRect2d::Union(const gpRect2d& rOther)
{
   PRECONDITION( IsNormalized() && rOther.IsNormalized() );

   m_Left   = _cpp_min(rOther.m_Left,   m_Left);
   m_Bottom = _cpp_min(rOther.m_Bottom, m_Bottom);
   m_Right  = _cpp_max(rOther.m_Right,  m_Right);
   m_Top    = _cpp_max(rOther.m_Top,    m_Top);
   return *this;
}

gpRect2d gpRect2d::UnionBy(const gpRect2d& rOther) const
{
   PRECONDITION( IsNormalized() && rOther.IsNormalized() );

   return gpRect2d( _cpp_min(rOther.m_Left,   m_Left),
                    _cpp_min(rOther.m_Bottom, m_Bottom),
                    _cpp_max(rOther.m_Right,  m_Right),
                    _cpp_max(rOther.m_Top,    m_Top) );
}

gpRect2d& gpRect2d::Intersection(const gpRect2d& rOther)
{
   PRECONDITION( IsNormalized() && rOther.IsNormalized() );

   if (Touches(rOther))
   {
      m_Left   = _cpp_max(rOther.m_Left,   m_Left);
      m_Bottom = _cpp_max(rOther.m_Bottom, m_Bottom);
      m_Right  = _cpp_min(rOther.m_Right,  m_Right);
      m_Top    = _cpp_min(rOther.m_Top,    m_Top);
   }
   else
   {
      m_Left   = 0;
      m_Top    = 0;
      m_Right  = 0;
      m_Bottom = 0;
   }

   return *this;
}

gpRect2d gpRect2d::IntersectionBy(const gpRect2d& rOther) const
{
   PRECONDITION( IsNormalized() && rOther.IsNormalized() );

   if (Touches(rOther))
   {
      return gpRect2d(_cpp_max(rOther.m_Left,   m_Left),
                      _cpp_max(rOther.m_Bottom, m_Bottom),
                      _cpp_min(rOther.m_Right,  m_Right),
                      _cpp_min(rOther.m_Top,    m_Top));
   }

   return gpRect2d(0,0,0,0);
}

gpRect2d& gpRect2d::BoundPoint(const gpPoint2d& rPoint)
{
   PRECONDITION( IsNormalized() );

   m_Left   = _cpp_min(rPoint.X(),  m_Left);
   m_Bottom = _cpp_min(rPoint.Y(),  m_Bottom);
   m_Right  = _cpp_max(rPoint.X(),  m_Right);
   m_Top    = _cpp_max(rPoint.Y(),  m_Top);

   return *this;
}

gpRect2d  gpRect2d::BoundPointBy(const gpPoint2d& rPoint) const
{
   gpRect2d rect(*this);
   rect.BoundPoint(rPoint);
   return rect;
}

//======================== ACCESS     =======================================

Float64 gpRect2d::Left() const
{
   return m_Left;
}

Float64& gpRect2d::Left()
{
   return m_Left;
}

Float64 gpRect2d::Right() const
{
   return m_Right;
}

Float64& gpRect2d::Right()
{
   return m_Right;
}

Float64 gpRect2d::Top() const
{
   return m_Top;
}

Float64& gpRect2d::Top()
{
   return m_Top;
}

Float64 gpRect2d::Bottom() const
{
   return m_Bottom;
}

Float64& gpRect2d::Bottom()
{
   return m_Bottom;
}

//======================== INQUERY    =======================================

bool operator==(const gpRect2d& lhs, const gpRect2d& rhs)
{
   return(IsEqual( lhs.Right(), rhs.Right(), 1.0e-8 ) && 
          IsEqual( lhs.Left(),  rhs.Left(),  1.0e-8 )   &&
          IsEqual( lhs.Top(),   rhs.Top(),   1.0e-8 )   &&
          IsEqual( lhs.Bottom(),rhs.Bottom(),1.0e-8 ));
}

bool operator!=(const gpRect2d& lhs, const gpRect2d& rhs)
{
   return !( lhs == rhs );
}

std::_tostream& operator<<(std::_tostream& os,const gpRect2d& rect)
{
   os << rect.TopLeft() << _T(" ") << rect.BottomRight();
   return os;
}


bool gpRect2d::IsNormalized() const
{
   return ( IsGE(m_Left,m_Right) || IsGE(m_Bottom, m_Top) );
}

bool gpRect2d::IsNull() const
{
   return IsZero( m_Left ) && IsZero( m_Right ) && IsZero( m_Top ) && IsZero( m_Bottom );
}

bool gpRect2d::Contains(const gpPoint2d& point) const
{
   return ( (m_Left   <= point.X() && point.X() < m_Right) &&
            (m_Bottom <= point.Y() && point.Y() < m_Top) );
}

bool gpRect2d::Contains(const gpRect2d& other) const
{
   return ( (m_Left   <= other.Left()   && other.Right() <= m_Right) &&
            (m_Bottom <= other.Bottom() && other.Top()   <= m_Top) );
}

bool gpRect2d::Touches(const gpRect2d& other) const
{
   return ( (m_Left   < other.Right() && other.Left()   < m_Right) &&
            (m_Bottom < other.Top()   && other.Bottom() < m_Top) );
}

gpRect2d::rctPosition gpRect2d::GetPosition(const gpRect2d& other) const
{
   Float64 oLeft   = other.m_Left;
   Float64 oRight  = other.m_Right;
   Float64 oBottom = other.m_Bottom;
   Float64 oTop    = other.m_Top;

   // Use contains and touches algorithms above
   if ( (m_Left  <=oLeft    && oRight<=m_Right) &&
        (m_Bottom<= oBottom && oTop  <= m_Top) )
   {
      return gpRect2d::rpContains;
   }
   else if ( (m_Left   < oRight && oLeft   < m_Right) &&
             (m_Bottom < oTop   && oBottom < m_Top) )
   {
      return gpRect2d::rpTouches;
   }
   else
   {
      return gpRect2d::rpOutside;
   }
}

//======================== DEBUG      =======================================
#if defined _DEBUG

void gpRect2d::Dump(dbgDumpContext& os) const
{
   os << _T("Dump for gpRect2d") << endl;
   os << _T("  (Bottom,Left,Right,Top) = (")<< m_Bottom<<_T(", ")<< m_Left
      <<_T(", ")<< m_Right<<_T(", ")<< m_Top<<_T(")")<<endl;
}
#endif // _DEBUG

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void gpRect2d::MakeCopy(const gpRect2d& rOther)
{
   m_Left   = rOther.m_Left;
   m_Right  = rOther.m_Right;
   m_Bottom = rOther.m_Bottom;
   m_Top    = rOther.m_Top;
}

void gpRect2d::MakeAssignment(const gpRect2d& rOther)
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

#if defined _UNITTEST
bool gpSize2d::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("gpSize2d");

   const gpSize2d s0_0(0,0), s1_1(1,1), s0_1(0,1), s1_4(1,4), s0_3(0,3),
                   sn3_0(-3,0), s3_0(3,0);
   gpSize2d st1, st2;
   gpPoint2d pt1;

   // add, subtract, ==
   TRY_TESTME (st1 == s0_0);
   st1 = s1_1 + s1_4;
   st2 = st1;
   TRY_TESTME (st1 == gpSize2d(2,5));
   st1-=s1_1;
   TRY_TESTME (st1 == s1_4);
   st1 = st2 - s1_4;
   TRY_TESTME (st1 == s1_1);
   st1+=sn3_0;
   TRY_TESTME (st1 == gpSize2d(-2,1));
   st1 = -s1_1 + s1_1;
   TRY_TESTME (st1 == s0_0);

   // magnitude
   st1 = gpSize2d(4,4);
   TRY_TESTME (st1.Magnitude() == sqrt(32.));
   TRY_TESTME (s0_3.Magnitude() == 3);

#if defined _DEBUG
   s1_4.Dump(rlog.GetDumpCtx());
#endif

   TESTME_EPILOG("gpSize2d");
}

bool gpPoint2d::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("gpPoint2d");

   const gpPoint2d p0_0(0,0), p1_1(1,1), p0_1(0,1), p1_4(1,4), p0_3(0,3),
                   pn3_0(-3,0), p3_0(3,0);
   gpPoint2d pt1, pt2;
   gpSize2d st;

   // add, subtract, ==
   TRY_TESTME (pt1 == p0_0);
   pt1 = p1_1 + p1_4;
   pt2 = pt1;
   TRY_TESTME (pt1 == gpPoint2d(2,5));
   pt1-=p1_1;
   TRY_TESTME (pt1 == p1_4);
   pt1 = p0_0;
   pt1+=pn3_0;
   TRY_TESTME (pt1 == pn3_0);

   TRY_TESTME( (gpPoint2d(10,10) - gpPoint2d(5,5)) == gpSize2d(5,5) );

   // distance, magnitude
   pt1 = gpPoint2d(4,4);
   TRY_TESTME (pt1.Magnitude() == sqrt(32.));
   TRY_TESTME (pt1.Distance(p0_0) == sqrt(32.));
   TRY_TESTME (p1_4.Distance(pn3_0) == sqrt(32.));

   // move, offset, rotate
   pt1.Move(-3,0);
   TRY_TESTME (pt1 == pn3_0);
   pt1.Move(p1_4);
   TRY_TESTME (pt1 == p1_4);
   pt1.Offset(-1,-4);
   TRY_TESTME (pt1 == p0_0);
   pt1.Offset(gpSize2d(0,3));
   TRY_TESTME (pt1 == p0_3);
   pt1 = p1_1.OffsetBy(0,3);
   TRY_TESTME (pt1 == p1_4);
   pt1 = pt1.OffsetBy(gpSize2d(-1,-4));
   TRY_TESTME (pt1 == p0_0);
   pt1 = p0_0.RotateBy(p0_0, 1);
   TRY_TESTME (pt1 == p0_0);
   pt1 = p1_1.RotateBy(p0_0, atan(1.));
   TRY_TESTME (pt1 == gpPoint2d(0,sqrt(2.)));
   pt1 = pn3_0;
   pt1.Rotate(p3_0, -2*atan(1.));
   TRY_TESTME (pt1 == gpPoint2d(3,6));
   
#if defined _DEBUG
   p1_4.Dump(rlog.GetDumpCtx());
#endif

   TESTME_EPILOG("gpPoint2d");
}

bool gpRect2d::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("gpRect2d");

   const gpPoint2d pn2_n4(-2,-4), p4_n1(4,-1), p1_2(1,2), pn4_n2(-4,-2);
   const gpRect2d r1(pn4_n2, p1_2), r1u(p1_2,pn4_n2);
   const gpRect2d r2(-2,-4,4,-1);

   gpPoint2d pt1, pt2;
   gpRect2d rt1, rt2;

   // Area & Inquiry
   TRY_TESTME (rt1.IsNull());
   TRY_TESTME (!r1.IsNull());
   TRY_TESTME (r1.Bottom() == -2);
   TRY_TESTME (r1.Right()  == 1);
   TRY_TESTME (r1.Top()    == 2);
   TRY_TESTME (r1.Left()   == -4);
   TRY_TESTME (r1.Width()  == 5);
   TRY_TESTME (r1.Height() == 4);
   TRY_TESTME (rt1.Area()  == 0);
   TRY_TESTME (r1.Area()   == 20);
   TRY_TESTME (!r1u.IsNormalized());
   TRY_TESTME (r1.IsNormalized());
   rt1 = r1u.Normalized();
   TRY_TESTME (r1 == rt1);

   // location points
   pt1 = r2.Center();
   TRY_TESTME (pt1 == gpPoint2d(1,-2.5));
   pt1 = r2.LeftCenter();
   TRY_TESTME (pt1 == gpPoint2d(-2,-2.5));
   pt1 = r2.BottomCenter();
   TRY_TESTME (pt1 == gpPoint2d(1,-4));
   pt1 = r2.RightCenter();
   TRY_TESTME (pt1 == gpPoint2d(4,-2.5));
   pt1 = r2.TopCenter();
   TRY_TESTME (pt1 == gpPoint2d(1,-1));

   // set, move
   rt1 = r2.MovedTo(-2,-4);
   TRY_TESTME ( rt1 != r2 );
   rt1.SetWH(pn4_n2, gpSize2d(5,4));
   TRY_TESTME ( rt1 == r1 );
   rt1.SetWH(-2,-4,6,3);
   TRY_TESTME ( rt1 == r2 );
   rt1 = r2;
   rt1.MoveTo(12,12);
   rt2 = r2.MovedTo(12,12);
   TRY_TESTME ( rt1 == rt2 );
   rt1 = r2.OffsetBy(14,16);
   TRY_TESTME ( rt1 == rt2 );
   rt2 = r2;
   rt2.Offset(14,16);
   TRY_TESTME ( rt1 == rt2 );
   rt1.SetEmpty();
   rt2.SetNull();
   TRY_TESTME ( rt1 == rt2 );
   TRY_TESTME ( rt1.IsNull() );

   // contains, intersect, union
   TRY_TESTME (r2.Touches(r1));
   TRY_TESTME (!r2.Contains(r1));
   TRY_TESTME (r2.Contains(pn2_n4));
   TRY_TESTME (r2.Contains(gpPoint2d(1,-2)));
   TRY_TESTME (!r2.Contains(gpPoint2d(5,-2)));

   rt1 = r1.IntersectionBy(r2);
   rt2 = r2;
   rt2.Intersection(r1);
   TRY_TESTME (rt1 == rt2);
   TRY_TESTME (rt1.Area() == 3);
   rt1 = r1.UnionBy(r2);
   rt2 = r2;
   rt2.Union(r1);
   TRY_TESTME (rt1 == rt2);
   TRY_TESTME (rt1.Area() == 48);

   // bound points
   gpRect2d br = r2.BoundPointBy(gpPoint2d(0,-2));
   TRY_TESTME (br==r2);
   br = r2.BoundPointBy(gpPoint2d(10,10));//  -2,-4,4,-1);
   TRY_TESTME (br==gpRect2d(-2,-4,10,10));
   br = br.BoundPointBy(gpPoint2d(-10,-10));
   TRY_TESTME (br==gpRect2d(-10,-10,10,10));

   
#if defined _DEBUG
   r1.Dump(rlog.GetDumpCtx());
#endif

   TESTME_EPILOG("gpRect2d");
}

#endif // _UNITTEST


