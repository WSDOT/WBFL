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

#include <GeomModel/Primitives.h>
#include <MathEx.h>
#include <math.h>
#include <iostream>
#include <xutility>

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

std::pair<Float64,Float64> Size2d::GetDimensions() const
{
   return std::make_pair(m_Dx, m_Dy);
}


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

std::pair<Float64,Float64> Point2d::GetLocation() const
{
   return std::make_pair(m_X, m_Y);
}

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
   if (!IsNormalized()) THROW_GEOMETRY(WBFL_GEOMETRY_E_NOTNORMALIZED);
   
   if(!rOther.IsNormalized()) THROW_GEOMETRY(WBFL_GEOMETRY_E_NOTNORMALIZED);

   m_Left   = Min(rOther.m_Left,   m_Left);
   m_Bottom = Min(rOther.m_Bottom, m_Bottom);
   m_Right  = Max(rOther.m_Right,  m_Right);
   m_Top    = Max(rOther.m_Top,    m_Top);
   return *this;
}

Rect2d Rect2d::UnionBy(const Rect2d& rOther) const
{
   if (!IsNormalized()) THROW_GEOMETRY(WBFL_GEOMETRY_E_NOTNORMALIZED);

   if (!rOther.IsNormalized()) THROW_GEOMETRY(WBFL_GEOMETRY_E_NOTNORMALIZED);

   return Rect2d( Min(rOther.m_Left,   m_Left),
                    Min(rOther.m_Bottom, m_Bottom),
                    Max(rOther.m_Right,  m_Right),
                    Max(rOther.m_Top,    m_Top) );
}

Rect2d& Rect2d::Intersection(const Rect2d& rOther)
{
   if (!IsNormalized()) THROW_GEOMETRY(WBFL_GEOMETRY_E_NOTNORMALIZED);

   if (!rOther.IsNormalized()) THROW_GEOMETRY(WBFL_GEOMETRY_E_NOTNORMALIZED);

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
   if (!IsNormalized()) THROW_GEOMETRY(WBFL_GEOMETRY_E_NOTNORMALIZED);

   if (!rOther.IsNormalized()) THROW_GEOMETRY(WBFL_GEOMETRY_E_NOTNORMALIZED);

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
   if (!IsNormalized()) THROW_GEOMETRY(WBFL_GEOMETRY_E_NOTNORMALIZED);

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
   if (!IsNormalized()) THROW_GEOMETRY(WBFL_GEOMETRY_E_NOTNORMALIZED);

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
