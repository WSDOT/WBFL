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

#include <GeomModel/Primitives.h>
#include <MathEx.h>
#include <math.h>
#include <iostream>
#include <xutility>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace WBFL::Geometry;

///////////////////////////////////////////////////////////////
/// Size2d
///////////////////////////////////////////////////////////////
Size2d::Size2d()
{
}

Size2d::Size2d(Float64 dx, Float64 dy)
{
   SetDimensions(dx, dy);
}

Size2d::Size2d(const Point2d& point)
{
   SetDimensions(point);
}

Size2d::~Size2d()
{
}

Size2d Size2d::operator+(const Size2d& size) const
{
   return Size2d( m_Dx + size.Dx(), m_Dy + size.Dy() );
}

Size2d Size2d::operator-(const Size2d& size) const
{
   return Size2d( m_Dx - size.Dx(), m_Dy - size.Dy() );
}

Size2d Size2d::operator*(Float64 c) const
{
   return Size2d( m_Dx*c, m_Dy*c );
}

Size2d Size2d::operator/(Float64 c) const
{
   return Size2d( m_Dx/c, m_Dy/c );
}

Size2d Size2d::operator- () const
{
   return Size2d(-m_Dx,-m_Dy);
}

bool Size2d::operator==(const Size2d& rOther) const
{
   return IsEqual( m_Dx, rOther.Dx() ) && IsEqual(m_Dy, rOther.Dy() );
}

bool Size2d::operator!=(const Size2d& rOther) const
{
   return !(*this == rOther);
}

Size2d& Size2d::operator+= (const Size2d& rOther)
{
   m_Dx += rOther.Dx();
   m_Dy += rOther.Dy();
   return *this;
}

Size2d& Size2d::operator-= (const Size2d& rOther)
{
   m_Dx -= rOther.Dx();
   m_Dy -= rOther.Dy();
   return *this;
}

Size2d& Size2d::operator/= (Float64 c)
{
   m_Dx /= c;
   m_Dy /= c;
   return *this;
}

Size2d& Size2d::operator*= (Float64 c)
{
   m_Dx *= c;
   m_Dy *= c;
   return *this;
}

Float64 Size2d::Magnitude() const
{
   Float64 mag;
   const Float64 limit = sqrt(Float64_Max);
   if (limit < m_Dx || limit < m_Dy )
      mag = Float64_Max;
   else
      mag = sqrt( m_Dx*m_Dx + m_Dy*m_Dy );

   return mag;
}

Float64 Size2d::Dx() const
{
   return m_Dx;
}

Float64& Size2d::Dx()
{
   return m_Dx;
}

Float64 Size2d::Dy() const
{
   return m_Dy;
}

Float64& Size2d::Dy()
{
   return m_Dy;
}

void Size2d::SetDimensions(Float64 dx, Float64 dy)
{
   m_Dx = dx;
   m_Dy = dy;
}

void Size2d::SetDimensions(const Point2d& point)
{
   SetDimensions(point.X(), point.Y());
}

void Size2d::GetDimensions(Float64* dx, Float64* dy) const
{
   *dx = m_Dx;
   *dy = m_Dy;
}

#if defined _DEBUG
void Size2d::Dump(WBFL::Debug::LogContext& os) const
{
   os <<_T( "Dump for Size2d") << WBFL::Debug::endl;
   os << _T("  (m_Dx, m_Dy) = (")<< m_Dx<<_T(", ")<< m_Dy<<_T(")")<< WBFL::Debug::endl;
}
#endif // _DEBUG


///////////////////////////////////////////////////////////////
/// Point2d
///////////////////////////////////////////////////////////////

/// Rotates pnt about pntCenter by the angular distance angle
Point2d RotatePoint(const Point2d& pntCenter, Float64 angle, const Point2d& pnt)
{
   Point2d newPnt;

   newPnt.X() = (pnt.X() - pntCenter.X()) * cos(angle) - (pnt.Y() - pntCenter.Y()) * sin(angle) + pntCenter.X();
   newPnt.Y() = (pnt.Y() - pntCenter.Y()) * cos(angle) + (pnt.X() - pntCenter.X()) * sin(angle) + pntCenter.Y();

   return newPnt;
}

Point2d::Point2d()
{
}

Point2d::Point2d(Float64 x,Float64 y)
{
   Move(x, y);
}

Point2d::~Point2d()
{
}

Point2d Point2d::operator+ (const Size2d& size) const
{
   return Point2d(m_X+size.Dx(), m_Y+size.Dy());
}

Point2d Point2d::operator- (const Size2d& size) const
{
   return Point2d(m_X-size.Dx(), m_Y-size.Dy());
}

Size2d Point2d::operator- (const Point2d& p) const
{
   return Size2d(m_X-p.X(), m_Y-p.Y());
}

Point2d Point2d::operator- () const
{
   return Point2d(-m_X,-m_Y);
}

Point2d& Point2d::operator+= (const Size2d& size)
{
   return Offset( size );
}

Point2d& Point2d::operator-= (const Size2d& size)
{
   return Offset( -size );
}

Float64 Point2d::Magnitude() const
{
   return sqrt( m_X*m_X + m_Y*m_Y );
}

void Point2d::Scale(Float64 c)
{
   m_X *= c;
   m_Y *= c;
}

void Point2d::Move(Float64 x,Float64 y)
{
   m_X = x;
   m_Y = y;
}

void Point2d::Move(const Point2d& newPosition)
{
   m_X = newPosition.X();
   m_Y = newPosition.Y(); 
}

Float64 Point2d::Distance(Float64 x, Float64 y) const
{
   return Distance(Point2d(x, y));
}

Float64 Point2d::Distance(const Point2d& p) const
{
   Size2d size = (p - *this);
   return size.Magnitude();
}

Point2d& Point2d::Offset(Float64 dx,Float64 dy)
{
   m_X += dx;
   m_Y += dy;
   return *this;
}

Point2d& Point2d::Offset(const Size2d& size)
{
   m_X += size.Dx();
   m_Y += size.Dy();
   return *this;
}

Point2d Point2d::OffsetBy(Float64 dx,Float64 dy) const
{
   return Point2d( m_X+dx, m_Y+dy );
}

Point2d Point2d::OffsetBy(const Size2d& size) const
{
   return Point2d( m_X+size.Dx(), m_Y+size.Dy() );
}

Point2d& Point2d::Rotate(Float64 x, Float64 y, Float64 angle)
{
   return Rotate(Point2d(x, y), angle);
}

Point2d& Point2d::Rotate(const Point2d& centerPoint, Float64 angle)
{
  *this = RotatePoint(centerPoint, angle, *this);
  return *this;
} 

Point2d Point2d::RotateBy(Float64 x, Float64 y, Float64 angle) const
{
   return RotateBy(Point2d(x, y), angle);
}

Point2d Point2d::RotateBy(const Point2d& centerPoint, Float64 angle) const
{
   return RotatePoint(centerPoint, angle, *this);
}

Float64 Point2d::X() const
{
   return m_X;
}

Float64& Point2d::X()
{
   return m_X;
}

Float64 Point2d::Y() const
{
   return m_Y;
}

Float64& Point2d::Y()
{
   return m_Y;
}

void Point2d::GetLocation(Float64* x, Float64* y) const
{
   *x = m_X;
   *y = m_Y;
}

#if defined _DEBUG
void Point2d::Dump(WBFL::Debug::LogContext& os) const
{
   os << _T("Dump for Point2d") << WBFL::Debug::endl;
   os << _T("  (m_X, m_Y) = (")<< m_X<<_T(", ")<< m_Y<<_T(")")<< WBFL::Debug::endl;
}
#endif // _DEBUG

bool Point2d::operator==(const Point2d& other) const
{
   return IsEqual( m_X, other.X()) && IsEqual( m_Y, other.Y());
}

bool Point2d::operator!=(const Point2d& other ) const
{
   return !( *this == other);
}

///////////////////////////////////////////////////////////////
/// Rect2d
///////////////////////////////////////////////////////////////

Rect2d::Rect2d(void) :
   m_Left(0.0),
   m_Right(0.0),
   m_Top(0.0),
   m_Bottom(0.0)
{
}

Rect2d::Rect2d(Float64 left,  Float64 bottom, Float64 right, Float64 top) :
m_Left(left),
m_Bottom(bottom),
m_Right(right),
m_Top(top)
{
}

Rect2d::Rect2d(const Point2d& bottomLeft,const Point2d& topRight) :
m_Left(bottomLeft.X()),
m_Bottom(bottomLeft.Y()),
m_Right(topRight.X()),
m_Top(topRight.Y())
{
}

Rect2d::Rect2d(const Point2d& bottomLeft,const Size2d& size) :
m_Left( bottomLeft.X() ),
m_Bottom( bottomLeft.Y() ),
m_Right( bottomLeft.X() + size.Dx() ),
m_Top( bottomLeft.Y() + size.Dy() )
{
}

Float64 Rect2d::Area() const
{
   return Height() * Width();
}

void Rect2d::Set(Float64 left,Float64 bottom,Float64 right,Float64 top)
{
   m_Left   = left;
   m_Bottom = bottom;
   m_Right  = right;
   m_Top    = top;
}

void Rect2d::Set(const Point2d& bottomLeft, const Point2d& topRight)
{
   m_Left   = bottomLeft.X();
   m_Bottom = bottomLeft.Y();
   m_Right  = topRight.X();
   m_Top    = topRight.Y();
}

void Rect2d::SetEmpty()
{
   SetNull();
}

void Rect2d::SetNull()
{
   m_Left   = 0;
   m_Bottom = 0;
   m_Right  = 0;
   m_Top    = 0;
}

void Rect2d::SetWH(Float64 left,Float64 bottom,Float64 width,Float64 height)
{
   m_Left   = left;
   m_Bottom = bottom;
   m_Right  = m_Left + width;
   m_Top    = bottom + height;
}

void Rect2d::SetWH(const Point2d& bottomLeft,const Size2d& size)
{
   SetWH( bottomLeft.X(), bottomLeft.Y(), size.Dx(), size.Dy() );
}

Point2d Rect2d::TopLeft() const
{
   return Point2d(m_Left,m_Top);
}

Point2d Rect2d::TopRight() const
{
   return Point2d(m_Right,m_Top);
}

Point2d Rect2d::BottomLeft() const
{
   return Point2d(m_Left,m_Bottom);
}

Point2d Rect2d::BottomRight() const
{
   return Point2d(m_Right,m_Bottom);
}

Point2d Rect2d::Center() const
{
   return Point2d(m_Left + Width()/2, m_Bottom + Height()/2);
}

Point2d Rect2d::TopCenter() const
{
   return Point2d( m_Left + Width()/2, m_Top );
}

Point2d Rect2d::BottomCenter() const
{
   return Point2d( m_Left + Width()/2, m_Bottom );
}

Point2d Rect2d::LeftCenter() const
{
   return Point2d( m_Left, m_Bottom + Height()/2 );
}

Point2d Rect2d::RightCenter() const
{
   return Point2d( m_Right, m_Bottom + Height()/2 );
}

Size2d Rect2d::Size() const
{
   return Size2d(m_Right - m_Left,m_Top - m_Bottom);
}

Float64 Rect2d::Height() const
{
   return m_Top - m_Bottom;
}

Float64 Rect2d::Width() const
{
   return m_Right - m_Left;
}

Rect2d& Rect2d::Inflate(Float64 dx,Float64 dy)
{
   m_Left   -= dx;
   m_Right  += dx;
   m_Top    += dy;
   m_Bottom -= dy;
   return *this;
}

Rect2d& Rect2d::Inflate(const Size2d& size)
{
   m_Left   -= size.Dx();
   m_Right  += size.Dx();
   m_Top    += size.Dy();
   m_Bottom -= size.Dy();
   return *this;
}

Rect2d Rect2d::InflateBy(Float64 dx,Float64 dy) const
{
   Rect2d rect( *this );
   rect.Left()   -= dx;
   rect.Right()  += dx;
   rect.Top()    += dy;
   rect.Bottom() -= dy;
   return rect;
}

Rect2d Rect2d::InflateBy(const Size2d& size) const
{
   Rect2d rect( *this );
   rect.Left()   -= size.Dx();
   rect.Right()  += size.Dx();
   rect.Top()    += size.Dy();
   rect.Bottom() -= size.Dy();
   return rect;
}

Rect2d& Rect2d::MoveTo(Float64 bottom,Float64 left)
{
   m_Right = left + Width();
   m_Top = bottom + Height();
   m_Bottom = bottom;
   m_Left = left;
   return *this;
}

Rect2d Rect2d::MovedTo(Float64 bottom,Float64 left) const
{
   return Rect2d(left,bottom,left+Width(),bottom+Height());
}

Rect2d& Rect2d::Normalize()
{
   if ( m_Right < m_Left )
   {
      std::swap(m_Left, m_Right);
   }

   if ( m_Top < m_Bottom )
   {
      std::swap(m_Top, m_Bottom);
   }

   return *this;
}

Rect2d Rect2d::Normalized() const
{
   return Rect2d( Point2d( Min(m_Left,m_Right), Min(m_Top,m_Bottom) ),
                    Point2d( Max(m_Left,m_Right), Max(m_Top,m_Bottom) ) );
}

Rect2d& Rect2d::Offset(Float64 dx,Float64 dy)
{
   m_Left   += dx;
   m_Right  += dx;
   m_Top    += dy;
   m_Bottom += dy;

   return *this;
}

Rect2d& Rect2d::Offset(const Size2d& delta)
{
   return Offset(delta.Dx(),delta.Dy());
}

Rect2d Rect2d::OffsetBy(Float64 dx,Float64 dy) const
{
   return Rect2d( m_Left+dx, m_Bottom+dy, m_Right+dx, m_Top+dy);
}

Rect2d Rect2d::OffsetBy(const Size2d& delta) const
{
   return OffsetBy(delta.Dx(), delta.Dy());
}

Rect2d& Rect2d::Union(const Rect2d& rOther)
{
   if (!IsNormalized()) THROW_GEOMETRY(_T("Rect2d::Union - the target rectangle must be normalized"));
   
   if(!rOther.IsNormalized()) THROW_GEOMETRY(_T("Rect2d::Union - the source rectangle must be normalized"));

   m_Left   = Min(rOther.m_Left,   m_Left);
   m_Bottom = Min(rOther.m_Bottom, m_Bottom);
   m_Right  = Max(rOther.m_Right,  m_Right);
   m_Top    = Max(rOther.m_Top,    m_Top);
   return *this;
}

Rect2d Rect2d::UnionBy(const Rect2d& rOther) const
{
   if (!IsNormalized()) THROW_GEOMETRY(_T("Rect2d::Union - the target rectangle must be normalized"));

   if (!rOther.IsNormalized()) THROW_GEOMETRY(_T("Rect2d::Union - the source rectangle must be normalized"));

   return Rect2d( Min(rOther.m_Left,   m_Left),
                    Min(rOther.m_Bottom, m_Bottom),
                    Max(rOther.m_Right,  m_Right),
                    Max(rOther.m_Top,    m_Top) );
}

Rect2d& Rect2d::Intersection(const Rect2d& rOther)
{
   if (!IsNormalized()) THROW_GEOMETRY(_T("Rect2d::Intersection - the target rectangle must be normalized"));

   if (!rOther.IsNormalized()) THROW_GEOMETRY(_T("Rect2d::Intersection - the source rectangle must be normalized"));

   if (Touches(rOther))
   {
      m_Left   = Max(rOther.m_Left,   m_Left);
      m_Bottom = Max(rOther.m_Bottom, m_Bottom);
      m_Right  = Min(rOther.m_Right,  m_Right);
      m_Top    = Min(rOther.m_Top,    m_Top);
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

Rect2d Rect2d::IntersectionBy(const Rect2d& rOther) const
{
   if (!IsNormalized()) THROW_GEOMETRY(_T("Rect2d::Intersection - the target rectangle must be normalized"));

   if (!rOther.IsNormalized()) THROW_GEOMETRY(_T("Rect2d::Intersection - the source rectangle must be normalized"));

   if (Touches(rOther))
   {
      return Rect2d(Max(rOther.m_Left,   m_Left),
                      Max(rOther.m_Bottom, m_Bottom),
                      Min(rOther.m_Right,  m_Right),
                      Min(rOther.m_Top,    m_Top));
   }

   return Rect2d(0,0,0,0);
}

Rect2d& Rect2d::BoundPoint(Float64 x, Float64 y)
{
   if (!IsNormalized()) THROW_GEOMETRY(_T("Rect2d::BoundPoint - rectangle must be normalized"));

   m_Left = Min(x, m_Left);
   m_Bottom = Min(y, m_Bottom);
   m_Right = Max(x, m_Right);
   m_Top = Max(y, m_Top);

   return *this;
}

Rect2d& Rect2d::BoundPoint(const Point2d& point)
{
   return BoundPoint(point.X(), point.Y());
}

Rect2d Rect2d::BoundPointBy(Float64 x,Float64 y) const
{
   if (!IsNormalized()) THROW_GEOMETRY(_T("Rect2d::BoundPointBy - rectangle must be normalized"));

   Rect2d rect(*this);
   rect.BoundPoint(x,y);
   return rect;
}

Rect2d Rect2d::BoundPointBy(const Point2d& point) const
{
   return BoundPointBy(point.X(), point.Y());
}


Float64 Rect2d::Left() const
{
   return m_Left;
}

Float64& Rect2d::Left()
{
   return m_Left;
}

Float64 Rect2d::Right() const
{
   return m_Right;
}

Float64& Rect2d::Right()
{
   return m_Right;
}

Float64 Rect2d::Top() const
{
   return m_Top;
}

Float64& Rect2d::Top()
{
   return m_Top;
}

Float64 Rect2d::Bottom() const
{
   return m_Bottom;
}

Float64& Rect2d::Bottom()
{
   return m_Bottom;
}

bool Rect2d::operator==(const Rect2d& other) const
{
   return(IsEqual( m_Right, other.Right()) && 
          IsEqual( m_Left,  other.Left())  &&
          IsEqual( m_Top,   other.Top())   &&
          IsEqual( m_Bottom,other.Bottom()));
}

bool Rect2d::operator!=(const Rect2d& other) const
{
   return !( *this == other );
}

bool Rect2d::IsNormalized() const
{
   return ( IsGE(m_Left,m_Right) && IsGE(m_Bottom, m_Top) );
}

bool Rect2d::IsNull() const
{
   return (IsZero( m_Left ) && IsZero( m_Right ) && IsZero( m_Top ) && IsZero( m_Bottom )) || IsZero(Area());
}

bool Rect2d::Contains(const Point2d& point) const
{
   return ( (::IsLE(m_Left,point.X()) && ::IsLT(point.X(),m_Right)) &&
            (::IsLE(m_Bottom,point.Y()) && ::IsLT(point.Y(),m_Top)) );
}

bool Rect2d::Contains(const Rect2d& other) const
{
   return ( (::IsLE(m_Left,other.Left()) && ::IsLE(other.Right(),m_Right)) &&
            (::IsLE(m_Bottom,other.Bottom()) && ::IsLE(other.Top(),m_Top)) );
}

bool Rect2d::Touches(const Rect2d& other) const
{
   return ( (::IsLT(m_Left,other.Right()) && ::IsLT(other.Left(),m_Right)) &&
            (::IsLT(m_Bottom,other.Top()) && ::IsLT(other.Bottom(),m_Top)) );
}

Rect2d::RelPosition Rect2d::GetPosition(const Rect2d& other) const
{
   if ( Contains(other) )
   {
      return Rect2d::RelPosition::Contains;
   }
   else if ( Touches(other) )
   {
      return Rect2d::RelPosition::Touches;
   }
   else
   {
      return Rect2d::RelPosition::Outside;
   }
}

#if defined _DEBUG
void Rect2d::Dump(WBFL::Debug::LogContext& os) const
{
   os << _T("Dump for Rect2d") << WBFL::Debug::endl;
   os << _T("  (Bottom,Left,Right,Top) = (")<< m_Bottom<<_T(", ")<< m_Left
      <<_T(", ")<< m_Right<<_T(", ")<< m_Top<<_T(")")<< WBFL::Debug::endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool Size2d::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("Size2d");

   const Size2d s0_0(0,0), s1_1(1,1), s0_1(0,1), s1_4(1,4), s0_3(0,3),
                   sn3_0(-3,0), s3_0(3,0);
   Size2d st1, st2;
   Point2d pt1;

   // add, subtract, ==
   TRY_TESTME (st1 == s0_0);
   st1 = s1_1 + s1_4;
   st2 = st1;
   TRY_TESTME (st1 == Size2d(2,5));
   st1-=s1_1;
   TRY_TESTME (st1 == s1_4);
   st1 = st2 - s1_4;
   TRY_TESTME (st1 == s1_1);
   st1+=sn3_0;
   TRY_TESTME (st1 == Size2d(-2,1));
   st1 = -s1_1 + s1_1;
   TRY_TESTME (st1 == s0_0);

   // magnitude
   st1 = Size2d(4,4);
   TRY_TESTME (st1.Magnitude() == sqrt(32.));
   TRY_TESTME (s0_3.Magnitude() == 3);

#if defined _DEBUG
   s1_4.Dump(rlog.GetLogContext());
#endif

   TESTME_EPILOG("Size2d");
}

bool Point2d::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("Point2d");

   const Point2d p0_0(0,0), p1_1(1,1), p0_1(0,1), p1_4(1,4), p0_3(0,3),
                   pn3_0(-3,0), p3_0(3,0);
   Point2d pt1, pt2;
   Size2d st;

   // add, subtract, ==
   TRY_TESTME (pt1 == p0_0);
   pt1 = p1_1 + p1_4;
   pt2 = pt1;
   TRY_TESTME (pt1 == Point2d(2,5));
   pt1-=p1_1;
   TRY_TESTME (pt1 == p1_4);
   pt1 = p0_0;
   pt1+=pn3_0;
   TRY_TESTME (pt1 == pn3_0);

   TRY_TESTME( (Point2d(10,10) - Point2d(5,5)) == Size2d(5,5) );

   // distance, magnitude
   pt1 = Point2d(4,4);
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
   pt1.Offset(Size2d(0,3));
   TRY_TESTME (pt1 == p0_3);
   pt1 = p1_1.OffsetBy(0,3);
   TRY_TESTME (pt1 == p1_4);
   pt1 = pt1.OffsetBy(Size2d(-1,-4));
   TRY_TESTME (pt1 == p0_0);
   pt1 = p0_0.RotateBy(p0_0, 1);
   TRY_TESTME (pt1 == p0_0);
   pt1 = p1_1.RotateBy(p0_0, atan(1.));
   TRY_TESTME (pt1 == Point2d(0,sqrt(2.)));
   pt1 = pn3_0;
   pt1.Rotate(p3_0, -2*atan(1.));
   TRY_TESTME (pt1 == Point2d(3,6));
   
#if defined _DEBUG
   p1_4.Dump(rlog.GetLogContext());
#endif

   TESTME_EPILOG("Point2d");
}

bool Rect2d::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("Rect2d");

   const Point2d pn2_n4(-2,-4), p4_n1(4,-1), p1_2(1,2), pn4_n2(-4,-2);
   const Rect2d r1(pn4_n2, p1_2), r1u(p1_2,pn4_n2);
   const Rect2d r2(-2,-4,4,-1);

   Point2d pt1, pt2;
   Rect2d rt1, rt2;

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
   TRY_TESTME (pt1 == Point2d(1,-2.5));
   pt1 = r2.LeftCenter();
   TRY_TESTME (pt1 == Point2d(-2,-2.5));
   pt1 = r2.BottomCenter();
   TRY_TESTME (pt1 == Point2d(1,-4));
   pt1 = r2.RightCenter();
   TRY_TESTME (pt1 == Point2d(4,-2.5));
   pt1 = r2.TopCenter();
   TRY_TESTME (pt1 == Point2d(1,-1));

   // set, move
   rt1 = r2.MovedTo(-2,-4);
   TRY_TESTME ( rt1 != r2 );
   rt1.SetWH(pn4_n2, Size2d(5,4));
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
   TRY_TESTME (r2.Contains(Point2d(1,-2)));
   TRY_TESTME (!r2.Contains(Point2d(5,-2)));

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
   Rect2d br = r2.BoundPointBy(Point2d(0,-2));
   TRY_TESTME (br==r2);
   br = r2.BoundPointBy(Point2d(10,10));//  -2,-4,4,-1);
   TRY_TESTME (br==Rect2d(-2,-4,10,10));
   br = br.BoundPointBy(Point2d(-10,-10));
   TRY_TESTME (br==Rect2d(-10,-10,10,10));

   // test derived properties
   Float64 left, right, top, bottom;
   left = 10;
   top = 10;
   right = 20;
   bottom = 5;
   Rect2d r(left,bottom,right,top);
   TRY_TESTME(IsEqual(r.Width(), right - left));
   TRY_TESTME(IsEqual(r.Height(), top - bottom));
   TRY_TESTME(IsEqual(r.Area(), (right - left) * (top - bottom)));

   // Points
   // make this an easy rectangle
   r.Set(-10, -10, 10, 10);
   TRY_TESTME(r.TopLeft() == Point2d(-10, 10));
   TRY_TESTME(r.TopCenter() == Point2d(0, 10));
   TRY_TESTME(r.TopRight() == Point2d(10, 10));
   TRY_TESTME(r.LeftCenter() == Point2d(-10, 0));
   TRY_TESTME(r.Center() == Point2d(0, 0));
   TRY_TESTME(r.RightCenter() == Point2d(10, 0));
   TRY_TESTME(r.BottomLeft() == Point2d(-10, -10));
   TRY_TESTME(r.BottomCenter() == Point2d(0, -10));
   TRY_TESTME(r.BottomRight() == Point2d(10, -10));

   // Contains
   r.Set(0, 0, 10, 10);
   TRY_TESTME(r.Contains(Point2d(5, 5)) == true);
   TRY_TESTME(r.Contains(Point2d(50, 50)) == false);
   // Test a point a the middle of each side and at each corner
   // (points on bottom and left sides are contained)
   TRY_TESTME(r.Contains(Point2d(0, 0)) == true);
   TRY_TESTME(r.Contains(Point2d(5, 0)) == true);
   TRY_TESTME(r.Contains(Point2d(10, 0)) == false);
   TRY_TESTME(r.Contains(Point2d(10, 5)) == false);
   TRY_TESTME(r.Contains(Point2d(10,10)) == false);
   TRY_TESTME(r.Contains(Point2d(5, 10)) == false);
   TRY_TESTME(r.Contains(Point2d(0, 10)) == false);
   TRY_TESTME(r.Contains(Point2d(0, 5)) == true);

   // Contains Rect and Touches
   r.Set(0, 0, 10, 10);
   Rect2d r_(20, 0, 30, 10);
   TRY_TESTME(r.Contains(r_) == false);
   TRY_TESTME(r.Touches(r_) == false);

   // make both rects the same
   r_ = r;
   TRY_TESTME(r.Contains(r_) == true);
   TRY_TESTME(r.Touches(r_) == true);

   r_.Set(2., 2., 8., 8.);
   TRY_TESTME(r.Contains(r_) == true);
   TRY_TESTME(r.Touches(r_) == true);

   // covers top left corner
   r_.Set(-2, 2, 8, 12);
   TRY_TESTME(r.Contains(r_) == false);
   TRY_TESTME(r.Touches(r_) == true);

   // covers bottom left corner
   r_.Set(2, -2, 12, 8);
   TRY_TESTME(r.Contains(r_) == false);
   TRY_TESTME(r.Touches(r_) == true);

   // Normize & IsNormalized
   r.Set(100, 0, 0, 100);
   TRY_TESTME(r.IsNormalized() == false);
   r.Normalize();
   TRY_TESTME(r.IsNormalized() == true);
   TRY_TESTME(IsEqual(r.Left(), 0.0));
   TRY_TESTME(IsEqual(r.Right(), 100.0));
   TRY_TESTME(IsEqual(r.Bottom(), 0.0));
   TRY_TESTME(IsEqual(r.Top(), 100.0));

   r.Set(0, 100, 100, 0);
   TRY_TESTME(r.IsNormalized() == false);
   r.Normalize();
   TRY_TESTME(r.IsNormalized() == true);
   TRY_TESTME(IsEqual(r.Left(), 0.0));
   TRY_TESTME(IsEqual(r.Right(), 100.0));
   TRY_TESTME(IsEqual(r.Bottom(), 0.0));
   TRY_TESTME(IsEqual(r.Top(), 100.0));

   r.Set(0, 100, 100, 0);
   TRY_TESTME(r.IsNormalized() == false);
   r.Normalize();
   TRY_TESTME(r.IsNormalized() == true);
   TRY_TESTME(IsEqual(r.Left(), 0.0));
   TRY_TESTME(IsEqual(r.Right(), 100.0));
   TRY_TESTME(IsEqual(r.Bottom(), 0.0));
   TRY_TESTME(IsEqual(r.Top(), 100.0));

   // Null/Empty
   r.Set(0, 0, 100, 100);
   TRY_TESTME(r.IsNull() == false);
   r.SetNull();
   TRY_TESTME(r.IsNull() == true);
   TRY_TESTME(IsEqual(r.Left(), 0.0));
   TRY_TESTME(IsEqual(r.Right(), 0.0));
   TRY_TESTME(IsEqual(r.Bottom(), 0.0));
   TRY_TESTME(IsEqual(r.Top(), 0.0));

   //
   // Test the Union method
   //
   r.Set(0, 0, 10, 10);

   // Rect2 is to the left
   r_.Set(20, 0, 30, 10);
   r.Union(r_);
   TRY_TESTME(IsEqual(r.Left(), 0.00));
   TRY_TESTME(IsEqual(r.Right(), 30.00));
   TRY_TESTME(IsEqual(r.Top(), 10.00));
   TRY_TESTME(IsEqual(r.Bottom(), 0.00));

   // reset Rect
   r.Set(0, 0, 10, 10);

   //Rect2 is to the right
   r_.Set(-30, 0, -20, 10);

   r.Union(r_);
   TRY_TESTME(IsEqual(r.Left(), -30.00));
   TRY_TESTME(IsEqual(r.Right(), 10.00));
   TRY_TESTME(IsEqual(r.Top(), 10.00));
   TRY_TESTME(IsEqual(r.Bottom(), 0.00));

   // reset Rect
   r.Set(0, 0, 10, 10);

   //Rect2 is above
   r_.Set(0, 20, 10, 30);

   r.Union(r_);
   TRY_TESTME(IsEqual(r.Left(), 0.00));
   TRY_TESTME(IsEqual(r.Right(), 10.00));
   TRY_TESTME(IsEqual(r.Top(), 30.00));
   TRY_TESTME(IsEqual(r.Bottom(), 0.00));

   // reset Rect
   r.Set(0, 0, 10, 10);

   //Rect2 is below
   r_.Set(0, -30, 10, -20);

   r.Union(r_);
   TRY_TESTME(IsEqual(r.Left(), 0.00));
   TRY_TESTME(IsEqual(r.Right(), 10.00));
   TRY_TESTME(IsEqual(r.Top(), 10.00));
   TRY_TESTME(IsEqual(r.Bottom(), -30.00));

   // pRect is not normalized
   r.Set(10, 0, 0, 10);

   r_.Set(10, 10, 20, 20);

   try
   {
      r.Union(r_);
      TRY_TESTME(false); // exception should throw and skip this line
   }
   catch (...)
   {
      TRY_TESTME(true);
      //TRY_TEST(pRect->Union(pRect2), GEOMETRY_E_NOTNORMALIZED);
   }

   // pRect2 is not normalized
   r.Set(0, 0, 10, 10);
   r_.Set(20, 10, 10, 20);
   try
   {
      r.Union(r_);
      TRY_TESTME(false); // exception should throw and skip this line
   }
   catch (...)
   {
      TRY_TESTME(true);
      //TRY_TEST(pRect->Union(pRect2), GEOMETRY_E_NOTNORMALIZED);
   }

   //
   // Test the UnionBy method
   //
   Rect2d r_union;

   r.Set(0, 0, 10, 10);

   // Rect2 is to the left
   r_.Set(20, 0, 30, 10);

   r_union = r.UnionBy(r_);
   TRY_TESTME(IsEqual(r_union.Left(), 0.00));
   TRY_TESTME(IsEqual(r_union.Right(), 30.00));
   TRY_TESTME(IsEqual(r_union.Top(), 10.00));
   TRY_TESTME(IsEqual(r_union.Bottom(), 0.00));

   //Rect2 is to the right
   r_.Set(-30, 0, -20, 10);

   r_union = r.UnionBy(r_);
   TRY_TESTME(IsEqual(r_union.Left(), -30.00));
   TRY_TESTME(IsEqual(r_union.Right(), 10.00));
   TRY_TESTME(IsEqual(r_union.Top(), 10.00));
   TRY_TESTME(IsEqual(r_union.Bottom(), 0.00));

   //Rect2 is above
   r_.Set(0, 20, 10, 30);

   r_union = r.UnionBy(r_);
   TRY_TESTME(IsEqual(r_union.Left(), 0.00));
   TRY_TESTME(IsEqual(r_union.Right(), 10.00));
   TRY_TESTME(IsEqual(r_union.Top(), 30.00));
   TRY_TESTME(IsEqual(r_union.Bottom(), 0.00));

   //Rect2 is below
   r_.Set(0, -30, 10, -20);

   r_union = r.UnionBy(r_);
   TRY_TESTME(IsEqual(r_union.Left(), 0.00));
   TRY_TESTME(IsEqual(r_union.Right(), 10.00));
   TRY_TESTME(IsEqual(r_union.Top(), 10.00));
   TRY_TESTME(IsEqual(r_union.Bottom(), -30.00));

   // pRect is not normalized
   r.Set(10, 0, 0, 10);
   r_.Set(10, 10, 20, 20);

   try
   {
      r_union = r.UnionBy(r_);
      TRY_TESTME(false);
   }
   catch (...)
   {
      TRY_TESTME(true);
   }

   // pRect2 is not normalized
   r.Set(0, 0, 10, 10);
   r_.Set(20, 10, 10, 20);

   try
   {
      r_union = r.UnionBy(r_);
      TRY_TESTME(false);
   }
   catch (...)
   {
      TRY_TESTME(true);
   }

   //
   // Test BoundPoint and BoundPointEx
   //
   r.Set(0, 0, 10, 10);
   Point2d p(20, 20);

   r.BoundPoint(p);
   r.BoundPoint(-10, -10);

   TRY_TESTME(IsEqual(r.Left(), -10.00));
   TRY_TESTME(IsEqual(r.Right(), 20.00));
   TRY_TESTME(IsEqual(r.Top(), 20.00));
   TRY_TESTME(IsEqual(r.Bottom(), -10.00));

   // pRect is not normalized
   r.Set(10, 0, 0, 10);
   try
   {
      r.BoundPoint(-10, -10);
      TRY_TESTME(false);
   }
   catch (...)
   {
      TRY_TESTME(true);
   }

   // make sure pRect didn't change
   TRY_TESTME(IsEqual(r.Left(), 10.00));
   TRY_TESTME(IsEqual(r.Right(), 0.00));
   TRY_TESTME(IsEqual(r.Top(), 10.00));
   TRY_TESTME(IsEqual(r.Bottom(), 0.00));

   //
   // Test Inflate and InflateEx
   //
   r.Set(0, 0, 10, 10);

   Size2d inflate(10, 10);

   r.Inflate(inflate);
   TRY_TESTME(IsEqual(r.Left(), -10.00));
   TRY_TESTME(IsEqual(r.Right(), 20.00));
   TRY_TESTME(IsEqual(r.Top(), 20.00));
   TRY_TESTME(IsEqual(r.Bottom(), -10.00));

   r.Inflate(-10, -10);
   TRY_TESTME(IsEqual(r.Left(), 0.00));
   TRY_TESTME(IsEqual(r.Right(), 10.00));
   TRY_TESTME(IsEqual(r.Top(), 10.00));
   TRY_TESTME(IsEqual(r.Bottom(), 0.00));

   //
   // Test Size method
   //
   r.Set(0, 0, 10, 10);

   Size2d size = r.Size();
   TRY_TESTME(IsEqual(size.Dx(), 10.0));
   TRY_TESTME(IsEqual(size.Dy(), 10.0));

   r.Set(10, 10, 0, 0);
   size = r.Size();
   TRY_TESTME(IsEqual(size.Dx(), -10.0));
   TRY_TESTME(IsEqual(size.Dy(), -10.0));

   //
   // Test Offset and OffsetEx
   //
   r.Set(0, 0, 10, 10);

   Size2d offset(10, 10);
   r.Offset(offset);
   TRY_TESTME(IsEqual(r.Left(), 10.00));
   TRY_TESTME(IsEqual(r.Right(), 20.00));
   TRY_TESTME(IsEqual(r.Top(), 20.00));
   TRY_TESTME(IsEqual(r.Bottom(), 10.00));
   
   r.Offset(20, 20);
   TRY_TESTME(IsEqual(r.Left(), 30.00));
   TRY_TESTME(IsEqual(r.Right(), 40.00));
   TRY_TESTME(IsEqual(r.Top(), 40.00));
   TRY_TESTME(IsEqual(r.Bottom(), 30.00));

   //
   // Test Intersect
   //
   r.Set(0, 0, 10, 10);
   r_.Set(25, 5, 35, 15);

   Rect2d intersect = r.IntersectionBy(r_);
   TRY_TESTME(IsEqual(intersect.Left(), 0.00));
   TRY_TESTME(IsEqual(intersect.Right(), 0.00));
   TRY_TESTME(IsEqual(intersect.Top(), 0.00));
   TRY_TESTME(IsEqual(intersect.Bottom(), 0.00));

   // Basic intersection
   r_.Set(5, 5, 15, 15);
   intersect = r.IntersectionBy(r_);
   TRY_TESTME(IsEqual(intersect.Left(), 5.00));
   TRY_TESTME(IsEqual(intersect.Right(), 10.00));
   TRY_TESTME(IsEqual(intersect.Top(), 10.00));
   TRY_TESTME(IsEqual(intersect.Bottom(), 5.00));

   // pRect is not normalized
   r.Set(10, 0, 0, 10);
   r_.Set(5, 5, 15, 15);
   try
   {
      r_union = r.Intersection(r_);
      TRY_TESTME(false);
   }
   catch (...)
   {
      TRY_TESTME(true);
   }

   // pRect2 is not normalized
   r.Set(0, 0, 10, 10);
   r_.Set(15, 5, 5, 15);
   try
   {
      r_union = r.Intersection(r_);
      TRY_TESTME(false);
   }
   catch (...)
   {
      TRY_TESTME(true);
   }

#if defined _DEBUG
   r1.Dump(rlog.GetLogContext());
#endif

   TESTME_EPILOG("Rect2d");
}
#endif // _UNITTEST

