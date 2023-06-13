///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
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
#include <GeomModel/ShapeProperties.h>

#include "MohrCircle.h"
#include <MathEx.h>
#include <iostream>

using namespace WBFL::Geometry;

ShapeProperties::ShapeProperties(Float64 area,
   const Point2d& centroid,
   Float64 ixx, Float64 iyy, Float64 ixy,
   Float64 xLeft, Float64 yBottom,
   Float64 xRight, Float64 yTop)
{
   m_Properties.area = area;
   m_Properties.centroid = centroid;
   m_Properties.ixx = ixx;
   m_Properties.iyy = iyy;
   m_Properties.ixy = ixy;
   m_Properties.xLeft = xLeft;
   m_Properties.xRight = xRight;
   m_Properties.yTop = yTop;
   m_Properties.yBottom = yBottom;
   SetProperties(m_Properties); // causes the coordinate system and orientation to be set
}

ShapeProperties::ShapeProperties(const ShapePropertyParameters& properties)
{
   SetProperties(m_Properties); // causes the coordinate system and orientation to be set
}

ShapeProperties::~ShapeProperties()
{
}

bool ShapeProperties::operator==(const ShapeProperties& rhs) const
{
   return IsEqual(m_Properties.area, rhs.m_Properties.area) &&
      m_Properties.centroid == rhs.m_Properties.centroid &&
      IsEqual(m_Properties.ixx, rhs.m_Properties.ixx) &&
      IsEqual(m_Properties.iyy, rhs.m_Properties.iyy) &&
      IsEqual(m_Properties.ixy, rhs.m_Properties.ixy) &&
      IsEqual(m_Properties.xLeft,rhs.m_Properties.xLeft) &&
      IsEqual(m_Properties.xRight,rhs.m_Properties.xRight) &&
      IsEqual(m_Properties.yTop,rhs.m_Properties.yTop) &&
      IsEqual(m_Properties.yBottom,rhs.m_Properties.yBottom);
}

bool ShapeProperties::operator!=(const ShapeProperties& rhs) const
{
   return !(*this == rhs);
}

ShapeProperties ShapeProperties::operator+ (const ShapeProperties& rhs) const
{
   ShapeProperties tmp(*this);
   return tmp += rhs;
}

ShapeProperties ShapeProperties::operator- (const ShapeProperties& rhs) const
{
   ShapeProperties tmp(*this);
   return tmp -= rhs;
}

ShapeProperties& ShapeProperties::operator+= (const ShapeProperties& rhs)
{
   return Join(rhs, 1.0);
}

ShapeProperties& ShapeProperties::operator-= (const ShapeProperties& rhs)
{
   return Join(rhs, -1.0);
}

void ShapeProperties::SetProperties(Float64 area, const Point2d& centroid, Float64 ixx, Float64 iyy, Float64 ixy, Float64 xLeft, Float64 yBottom, Float64 xRight, Float64 yTop)
{
   m_Properties.area = area;
   m_Properties.centroid = centroid;
   m_Properties.ixx = ixx;
   m_Properties.iyy = iyy;
   m_Properties.ixy = ixy;
   m_Properties.xLeft = xLeft;
   m_Properties.xRight = xRight;
   m_Properties.yTop = yTop;
   m_Properties.yBottom = yBottom;
   SetProperties(m_Properties);
}

void ShapeProperties::SetProperties(const ShapePropertyParameters& properties)
{
   PRECONDITION(0 <= properties.xLeft && 0 <= properties.yBottom && 0 <= properties.xRight && 0 <= properties.yTop);
   m_Properties = properties;

   m_CoordType = CoordinateSystemType::Centroidal;
   m_Orientation = 0;

   UpdateOrientation();
}

const ShapePropertyParameters& ShapeProperties::GetProperties() const
{
   return m_Properties;
}

void ShapeProperties::Clear()
{
   m_Properties = ShapePropertyParameters();
}

void ShapeProperties::SetArea(Float64 area)
{
   m_Properties.area = area;
}

Float64 ShapeProperties::GetArea() const
{
   return m_Properties.area;
}

void ShapeProperties::SetCentroid(const Point2d& centroid)
{
   m_Properties.centroid = centroid;
   UpdateOrientation();
}

const Point2d& ShapeProperties::GetCentroid() const
{
   return m_CurrCentroid;
}

void ShapeProperties::SetIxx(Float64 ixx)
{
   m_Properties.ixx = ixx;
   UpdateOrientation();
}

Float64 ShapeProperties::GetIxx() const
{
   return m_CurrIxx;
}

void ShapeProperties::SetIyy(Float64 iyy)
{
   m_Properties.iyy = iyy;
   UpdateOrientation();
}

Float64 ShapeProperties::GetIyy() const
{
   return m_CurrIyy;
}

void ShapeProperties::SetIxy(Float64 ixy)
{
   m_Properties.ixy = ixy;
   UpdateOrientation();
}

Float64 ShapeProperties::GetIxy() const
{
   return m_CurrIxy;
}

void ShapeProperties::SetYtop(Float64 yTop)
{
   PRECONDITION(0 <= yTop);
   m_Properties.yTop = yTop;
}

Float64 ShapeProperties::GetYtop() const
{
   return m_Properties.yTop;
}

void ShapeProperties::SetYbottom(Float64 yBottom)
{
   PRECONDITION(0 <= yBottom);
   m_Properties.yBottom = yBottom;
}

Float64 ShapeProperties::GetYbottom() const
{
   return m_Properties.yBottom;
}

void ShapeProperties::SetXleft(Float64 xLeft)
{
   PRECONDITION(0 <= xLeft);
   m_Properties.xLeft = xLeft;
}

Float64 ShapeProperties::GetXleft() const
{
   return m_Properties.xLeft;
}

void ShapeProperties::SetXright(Float64 xRight)
{
   PRECONDITION(0 <= xRight);
   m_Properties.xRight = xRight;
}

Float64 ShapeProperties::GetXright() const
{
   return m_Properties.xRight;
}

Float64 ShapeProperties::GetI11() const
{
   MohrCircle ms(m_CurrIxx, m_CurrIyy, m_CurrIxy);
   Float64 ixx, iyy, ixy, angle;
   angle = ms.GetPrincipalDirection();
   ms.ComputeState(angle,ixx,iyy,ixy);
   return ixx;
}

Float64 ShapeProperties::GetI22() const
{
   MohrCircle ms(m_CurrIxx, m_CurrIyy, m_CurrIxy);
   Float64 ixx, iyy, ixy, angle;
   angle = ms.GetPrincipalDirection();
   ms.ComputeState(angle,ixx,iyy,ixy);
   return iyy;
}

Float64 ShapeProperties::GetPrincipalDirection() const
{
   MohrCircle ms(m_CurrIxx, m_CurrIyy, m_CurrIxy);
   return ms.GetPrincipalDirection();
}

Float64 ShapeProperties::GetI12Max() const
{
   MohrCircle ms(m_CurrIxx, m_CurrIyy, m_CurrIxy);
   return ms.GetTmax();
}

Float64 ShapeProperties::GetI12Min() const
{
   MohrCircle ms(m_CurrIxx, m_CurrIyy, m_CurrIxy);
   return -ms.GetTmax();
}

void ShapeProperties::SetCoordinateSystem(ShapeProperties::CoordinateSystemType sys)
{
   switch(sys)
   {
   case CoordinateSystemType::Centroidal:
      {
         m_CoordType = sys;
         m_Origin = m_Properties.centroid;
         m_Orientation = 0;
         UpdateOrientation();
         break;
      }
      case CoordinateSystemType::Global:
      {
         m_CoordType = sys;
         m_Origin = Point2d(0,0);
         m_Orientation = 0;
         UpdateOrientation();
         break;
      }
      case CoordinateSystemType::Principal:
      {
         // first have to get principal orientation angle
         SetCoordinateSystem(CoordinateSystemType::Centroidal);
         m_Orientation = GetPrincipalDirection();
         m_CoordType = sys;
         UpdateOrientation();
         break;
      }
      case CoordinateSystemType::UserDefined:
      {
         m_CoordType = sys;
         break;
      }
      default:
         CHECKX(0,_T("Bad coordinate type"));
   }
}

ShapeProperties::CoordinateSystemType ShapeProperties::GetCoordinateSystem() const
{
   return m_CoordType;
}

void ShapeProperties::SetOrigin(const Point2d& origin)
{
      m_CoordType = CoordinateSystemType::UserDefined;
      m_Origin = origin;
      UpdateOrientation();
}

const Point2d& ShapeProperties::GetOrigin() const
{
   return m_Origin;
}

void ShapeProperties::SetOrientation(Float64 angle)
{
      m_CoordType = CoordinateSystemType::UserDefined;
      m_Orientation = angle;
      UpdateOrientation();
}

Float64 ShapeProperties::GetOrientation() const
{
   return m_Orientation;
}

#if defined _DEBUG
bool ShapeProperties::AssertValid() const
{
   return true;
}

void ShapeProperties::Dump(WBFL::Debug::LogContext& os) const
{
   os << _T("Dump for ShapeProperties") << WBFL::Debug::endl;
   os << _T("   m_Area         = ")<< m_Properties.area << WBFL::Debug::endl;
   os << _T("   m_Centroid     = (")<< m_Properties.centroid.X()<<_T(", ")<<m_Properties.centroid.Y()<<_T(")")<< WBFL::Debug::endl;
   os << _T("   m_Ixx          = ")<< m_Properties.ixx << WBFL::Debug::endl;         
   os << _T("   m_Iyy          = ")<< m_Properties.iyy << WBFL::Debug::endl;          
   os << _T("   m_Ixy          = ")<< m_Properties.ixy << WBFL::Debug::endl;         
   os << _T("   m_CoordType    = ")<< (int)m_CoordType << WBFL::Debug::endl;   
   os << _T("   m_Origin       = (")<<m_Origin.X()<<_T(", ")<<m_Origin.Y()<<_T(")") << WBFL::Debug::endl;
   os << _T("   m_Orientation  = ")<< m_Orientation << WBFL::Debug::endl;
   os << _T("   m_CurrCentroid = (")<< m_CurrCentroid.X()<<_T(", ")<<m_CurrCentroid.Y()<<_T(")")<< WBFL::Debug::endl;
   os << _T("   m_CurrIxx      = ")<< m_CurrIxx << WBFL::Debug::endl;
   os << _T("   m_CurrIyy      = ")<< m_CurrIyy << WBFL::Debug::endl;
   os << _T("   m_CurrIxy      = ")<< m_CurrIxy << WBFL::Debug::endl;
}

#endif // _DEBUG

void ShapeProperties::UpdateOrientation()
{
   switch (m_CoordType)
   {
   case (CoordinateSystemType::Centroidal):
      {
         // in centroidal system = just copy values
         m_CurrCentroid = m_Properties.centroid;
         m_CurrIxx      = m_Properties.ixx;
         m_CurrIyy      = m_Properties.iyy;
         m_CurrIxy      = m_Properties.ixy;
         break;
      }
   default:
      {
         // not centroidal - need to rotate into orientation
         // first rotate about centroid
         Float64 ixx, iyy, ixy;
         MohrCircle ms(m_Properties.ixx, m_Properties.iyy, m_Properties.ixy);
         ms.ComputeState(m_Orientation,ixx, iyy, ixy);

         // next need to transform into origin coordinates
         Point2d delta( m_Properties.centroid.X() - m_Origin.X(), m_Properties.centroid.Y() - m_Origin.Y());
         delta.Rotate(Point2d(0,0), -m_Orientation);

         Float64 dx = delta.X();
         Float64 dy = delta.Y();

         // use parallel axis theorem to put properties into new system
         m_CurrCentroid = delta;
         m_CurrIxx      = ixx + m_Properties.area * dy * dy;
         m_CurrIyy      = iyy + m_Properties.area * dx * dx;
         m_CurrIxy      = ixy + m_Properties.area * dx * dy;
         break;
      }
   }
}

ShapeProperties& ShapeProperties::Join(const ShapeProperties& rOther, Float64 scale)
{
   auto currCoordinateSystemType = m_CoordType; // reserve the current coordinate system type

   // convert to global coordinates
   SetCoordinateSystem(CoordinateSystemType::Global);
   ShapeProperties other(rOther);
   other.SetCoordinateSystem(CoordinateSystemType::Global);

   Float64 ixx = 0, iyy = 0, ixy = 0; // about global axes
   Float64 mxx = 0, myy = 0;        // first moments

   Float64 cx1, cy1;
   std::tie(cx1,cy1) = m_Properties.centroid.GetLocation();

   Float64 cx2, cy2;
   std::tie(cx2,cy2) = other.GetCentroid().GetLocation();

   mxx = m_Properties.area * m_Properties.centroid.Y() + scale* other.m_Properties.area * other.m_Properties.centroid.Y();
   myy = m_Properties.area * m_Properties.centroid.X() + scale * other.m_Properties.area * other.m_Properties.centroid.X();

   // Get centroidal I for each shape and transform it to the global axes
   ixx = (m_Properties.ixx + m_Properties.area * m_Properties.centroid.Y() * m_Properties.centroid.Y() +
      scale * other.m_Properties.ixx + scale * other.m_Properties.area * other.m_Properties.centroid.Y() * other.m_Properties.centroid.Y());

   iyy = (m_Properties.iyy + m_Properties.area * m_Properties.centroid.X() * m_Properties.centroid.X() +
      scale * other.m_Properties.iyy + scale * other.m_Properties.area * other.m_Properties.centroid.X() * other.m_Properties.centroid.X());

   ixy = (m_Properties.ixy + m_Properties.area * m_Properties.centroid.X() * m_Properties.centroid.Y() +
      scale * other.m_Properties.ixy + scale * other.m_Properties.area * other.m_Properties.centroid.X() * other.m_Properties.centroid.Y());

   m_Properties.area += scale * other.m_Properties.area;

   m_Properties.centroid.Y() = mxx / m_Properties.area;
   m_Properties.centroid.X() = myy / m_Properties.area;

   Float64 cgx, cgy;
   std::tie(cgx,cgy) = m_Properties.centroid.GetLocation();

   m_Properties.ixx = ixx - m_Properties.area * m_Properties.centroid.Y() * m_Properties.centroid.Y();
   m_Properties.iyy = iyy - m_Properties.area * m_Properties.centroid.X() * m_Properties.centroid.X();
   m_Properties.ixy = ixy - m_Properties.area * m_Properties.centroid.X() * m_Properties.centroid.Y();

   // Update the distance from the edges to the centroid
   Float64 l2 = other.GetXleft();
   Float64 r2 = other.GetXright();
   Float64 t2 = other.GetYtop();
   Float64 b2 = other.GetYbottom();

   Float64 l, r, t, b; // distance from the global axes to the extreme edges
   l = Min(cx1 - m_Properties.xLeft, cx2 - l2);
   r = Max(cx1 + m_Properties.xRight, cx2 + r2);
   t = Max(cy1 + m_Properties.yTop, cy2 + t2);
   b = Min(cy1 - m_Properties.yBottom, cy2 - b2);

   m_Properties.xLeft = cgx - l;
   m_Properties.xRight = r - cgx;
   m_Properties.yTop = t - cgy;
   m_Properties.yBottom = cgy - b;

   UpdateOrientation();

   // restore the original coordinate system
   SetCoordinateSystem(currCoordinateSystemType);

   return *this;
}

#if defined _UNITTEST
bool Test_AddOperator1(WBFL::Debug::Log& rlog)
{
   // Test the addition of properties when both properties objects are in
   // centroidal coordinates
   TESTME_PROLOGUE( "ShapeProperties - Test_AddOperator1" );

   ShapeProperties shape1(10,Point2d(10,10),10,10,10,10,10,10,10);
   ShapeProperties shape2(20,Point2d(20,20),20,20,20,20,20,20,20);

   ShapeProperties shape3 = shape1 + shape2;

   TRY_TESTME( IsEqual(shape3.GetArea(), 30.) );
   TRY_TESTME( IsEqual(shape3.GetIxx(), 696.6666666666) );
   TRY_TESTME( IsEqual(shape3.GetIyy(), 696.6666666666) );
   TRY_TESTME( IsEqual(shape3.GetIxy(), 696.6666666666) );
   TRY_TESTME( Point2d(16.666666666666,16.6666666666666) == shape3.GetCentroid() );
   TRY_TESTME( IsEqual(shape3.GetXleft(), 16.666666666666666) );
   TRY_TESTME( IsEqual(shape3.GetXright(), 23.333333333333333) );
   TRY_TESTME( IsEqual(shape3.GetYbottom(), 16.666666666666666) );
   TRY_TESTME( IsEqual(shape3.GetYtop(), 23.333333333333333) );

   TESTME_EPILOG( "ShapeProperties - Test_AddOperator1" );
}

bool Test_AddOperator2(WBFL::Debug::Log& rlog)
{
   // Test the addition of properties when one property object is in centroidal
   // coordinates and one is in global coordinates
   TESTME_PROLOGUE( "ShapeProperties - Test_AddOperator2" );

   ShapeProperties shape1(10,Point2d(10,10),10,10,10,10,10,10,10);
   ShapeProperties shape2(20,Point2d(20,20),20,20,20,20,20,20,20);
   shape2.SetCoordinateSystem( ShapeProperties::CoordinateSystemType::Global );

   TRY_TESTME( IsEqual(shape2.GetArea(), 20.) );
   TRY_TESTME( IsEqual(shape2.GetIxx(), 8020. ) );
   TRY_TESTME( IsEqual(shape2.GetIyy(), 8020. ) );
   TRY_TESTME( IsEqual(shape2.GetIxy(), 8020. ) );
   TRY_TESTME( Point2d(20,20) == shape2.GetCentroid() );
   TRY_TESTME( IsEqual( shape2.GetXleft(),    20. ) );
   TRY_TESTME( IsEqual( shape2.GetXright(),   20. ) );
   TRY_TESTME( IsEqual( shape2.GetYbottom(),  20. ) );
   TRY_TESTME( IsEqual( shape2.GetYtop(),     20. ) );

   ShapeProperties shape3 = shape1 + shape2;

   TRY_TESTME( IsEqual(shape3.GetArea(), 30.) );
   TRY_TESTME( IsEqual(shape3.GetIxx(), 696.6666666666) );
   TRY_TESTME( IsEqual(shape3.GetIyy(), 696.6666666666) );
   TRY_TESTME( IsEqual(shape3.GetIxy(), 696.6666666666) );
   TRY_TESTME( Point2d(16.666666666666,16.6666666666666) == shape3.GetCentroid() );
   TRY_TESTME( IsEqual(shape3.GetXleft(),  16.666666666666666) );
   TRY_TESTME( IsEqual(shape3.GetXright(), 23.333333333333333) );
   TRY_TESTME( IsEqual(shape3.GetYbottom(),  16.666666666666666) );
   TRY_TESTME( IsEqual(shape3.GetYtop(), 23.333333333333333) );

   TESTME_EPILOG( "ShapeProperties - Test_AddOperator2" );
}

bool Test_Assignment1(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE( "ShapeProperties - Test_Assignment1" );

   // Test the mutators and accessors when property object is in centroidal units
   // This is just a raw test to make sure we get back what we put in.
   // This test makes no assumptions about the correctness of the section properties!!!
   ShapeProperties shape;

   shape.SetArea(10);
   TRY_TESTME( IsEqual( shape.GetArea(), 10. ) );

   shape.SetCentroid( Point2d(10,10) );
   TRY_TESTME( Point2d(10,10) == shape.GetCentroid() );

   shape.SetIxx( 10 );
   TRY_TESTME( IsEqual( shape.GetIxx(), 10. ) );

   shape.SetIyy( 10 );
   TRY_TESTME( IsEqual( shape.GetIyy(), 10. ) );

   shape.SetIxy( 10 );
   TRY_TESTME( IsEqual( shape.GetIxy(), 10. ) );

   shape.SetOrigin( Point2d(10,10) );
   TRY_TESTME( Point2d(10,10) == shape.GetOrigin() );

   shape.SetOrientation( 0.5 );
   TRY_TESTME( IsEqual( shape.GetOrientation(), 0.5 ) );

   shape.SetXleft(10);
   TRY_TESTME( IsEqual( shape.GetXleft(), 10. ) );

   shape.SetXright(10);
   TRY_TESTME( IsEqual( shape.GetXright(), 10. ) );

   shape.SetYtop(10);
   TRY_TESTME( IsEqual( shape.GetYtop(), 10. ) );
   
   shape.SetYbottom(10);
   TRY_TESTME( IsEqual( shape.GetYbottom(), 10. ) );
   
   TESTME_EPILOG( "ShapeProperties - Test_Assignment1" );
}

bool Test_Assignment2(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE( "ShapeProperties - Test_Assignment2" );

   // Test the mutators and accessors when property object is in centroidal units
   // This test verifies section properties remain correct.
   ShapeProperties shape(10,Point2d(10,10),10,10,10,10,10,10,10);

   shape.SetCentroid( Point2d(20,20) );
   TRY_TESTME( Point2d(20,20) == shape.GetCentroid() );
   TRY_TESTME( IsEqual( shape.GetArea(), 10. ) );
   TRY_TESTME( IsEqual( shape.GetIxx(), 10. ) );
   TRY_TESTME( IsEqual( shape.GetIyy(), 10. ) );
   TRY_TESTME( IsEqual( shape.GetIxy(), 10. ) );

   shape.SetIxx( 20 );
   TRY_TESTME( Point2d(20,20) == shape.GetCentroid() );
   TRY_TESTME( IsEqual( shape.GetArea(), 10. ) );
   TRY_TESTME( IsEqual( shape.GetIxx(), 20. ) );
   TRY_TESTME( IsEqual( shape.GetIyy(), 10. ) );
   TRY_TESTME( IsEqual( shape.GetIxy(), 10. ) );

   shape.SetIyy( 20 );
   TRY_TESTME( Point2d(20,20) == shape.GetCentroid() );
   TRY_TESTME( IsEqual( shape.GetArea(), 10. ) );
   TRY_TESTME( IsEqual( shape.GetIxx(), 20. ) );
   TRY_TESTME( IsEqual( shape.GetIyy(), 20. ) );
   TRY_TESTME( IsEqual( shape.GetIxy(), 10. ) );

   shape.SetIxy( 20 );
   TRY_TESTME( Point2d(20,20) == shape.GetCentroid() );
   TRY_TESTME( IsEqual( shape.GetArea(), 10. ) );
   TRY_TESTME( IsEqual( shape.GetIxx(), 20. ) );
   TRY_TESTME( IsEqual( shape.GetIyy(), 20. ) );
   TRY_TESTME( IsEqual( shape.GetIxy(), 20. ) );
   
   TESTME_EPILOG( "ShapeProperties - Test_Assignment2" );
}

bool ShapeProperties::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("ShapeProperties");
   // try a point area
   ShapeProperties a(4., Point2d(0,0), 0., 0., 0, 0,  0,  0, 0);
   TRY_TESTME(a.GetCoordinateSystem() == ShapeProperties::CoordinateSystemType::Centroidal) ;
   TRY_TESTME(Point2d(0,0) == a.GetCentroid()) ;
   TRY_TESTME( IsZero(4-a.GetArea())) ;
   TRY_TESTME( IsZero(a.GetI11())) ;
   TRY_TESTME( IsZero(a.GetI22())) ;
   TRY_TESTME( IsZero(a.GetIxy())) ;
   TRY_TESTME( IsZero(a.GetI12Max())) ;
   TRY_TESTME( IsZero(a.GetI12Min())) ;
   TRY_TESTME( IsZero(a.GetYtop())) ;
   TRY_TESTME( IsZero(a.GetYbottom())) ;
   TRY_TESTME( IsZero(a.GetXright())) ;
   TRY_TESTME( IsZero(a.GetXleft())) ;

   // move origin
   Point2d orn(4,-2);
   a.SetOrigin(orn);
   TRY_TESTME( a.GetCoordinateSystem() == ShapeProperties::CoordinateSystemType::UserDefined) ;
   TRY_TESTME( Point2d(-4,2) == a.GetCentroid()) ;
   TRY_TESTME( IsZero(4-a.GetArea())) ;
   TRY_TESTME( IsZero( -63.43 - ToDegrees(a.GetPrincipalDirection()),.1)) ;
   TRY_TESTME( IsZero(16-a.GetIxx())) ;
   TRY_TESTME( IsZero(64-a.GetIyy())) ;
   TRY_TESTME( IsZero(32+a.GetIxy())) ;
   TRY_TESTME( IsZero(80-a.GetI11())) ;
   TRY_TESTME( IsZero(a.GetI22())) ;
   TRY_TESTME( IsZero(40-a.GetI12Max())) ;
   TRY_TESTME( IsZero(40+a.GetI12Min())) ;
   TRY_TESTME( IsZero(a.GetYtop())) ;
   TRY_TESTME( IsZero(a.GetYbottom())) ;
   TRY_TESTME( IsZero(a.GetXright())) ;
   TRY_TESTME( IsZero(a.GetXleft())) ;

   // rotate 90 deg
   a.SetOrientation(M_PI/2);
   TRY_TESTME( a.GetCoordinateSystem() == ShapeProperties::CoordinateSystemType::UserDefined) ;
   TRY_TESTME( Point2d(2,4) == a.GetCentroid()) ;
   TRY_TESTME( IsZero(4-a.GetArea())) ;
   TRY_TESTME( IsZero(64-a.GetIxx())) ;
   TRY_TESTME( IsZero(16-a.GetIyy())) ;
   TRY_TESTME( IsZero(32-a.GetIxy())) ;
   TRY_TESTME( IsZero(80.-a.GetI11())) ;
   TRY_TESTME( IsZero(a.GetI22())) ;
   TRY_TESTME( IsZero(40-a.GetI12Max())) ;
   TRY_TESTME( IsZero(40+a.GetI12Min())) ;

   // try a 2x4 rectangle
   ShapeProperties gs2x4(8., Point2d(0,0), 128./12., 32./12., 0.0, 1,2,1,2);
   TRY_TESTME( IsZero(8-gs2x4.GetArea())) ;
   TRY_TESTME( IsZero(128./12.-gs2x4.GetI11())) ;
   TRY_TESTME( IsZero(32./12-gs2x4.GetI22())) ;
   TRY_TESTME( IsZero(gs2x4.GetIxy())) ;
   TRY_TESTME( IsZero(4-gs2x4.GetI12Max())) ;
   TRY_TESTME( IsZero(4+gs2x4.GetI12Min())) ;
   TRY_TESTME( IsZero(2-gs2x4.GetYtop())) ;
   TRY_TESTME( IsZero(2-gs2x4.GetYbottom())) ;
   TRY_TESTME( IsZero(1-gs2x4.GetXright())) ;
   TRY_TESTME( IsZero(1-gs2x4.GetXleft())) ;

   // move origin to user-defined location
   gs2x4.SetOrigin(orn); 
   TRY_TESTME( IsZero(8-gs2x4.GetArea())) ;
   TRY_TESTME( IsZero((128./12.+32)-gs2x4.GetIxx())) ;
   TRY_TESTME( IsZero((32./12+128)-gs2x4.GetIyy())) ;
   TRY_TESTME( IsZero(64+gs2x4.GetIxy())) ;
   TRY_TESTME( IsZero(-62.25 - ToDegrees(gs2x4.GetPrincipalDirection()),.01)) ;
   TRY_TESTME( IsZero(77.67-gs2x4.GetI12Max(),.01)) ;
   TRY_TESTME( IsZero(2-gs2x4.GetYtop())) ;
   TRY_TESTME( IsZero(2-gs2x4.GetYbottom())) ;
   TRY_TESTME( IsZero(1-gs2x4.GetXright())) ;
   TRY_TESTME( IsZero(1-gs2x4.GetXleft())) ;

   // move origin back to centroid
   gs2x4.SetCoordinateSystem(ShapeProperties::CoordinateSystemType::Centroidal);
   TRY_TESTME( gs2x4.GetCoordinateSystem() == ShapeProperties::CoordinateSystemType::Centroidal) ;
   TRY_TESTME( Point2d(0,0) == gs2x4.GetOrigin() );
   TRY_TESTME( IsZero(8-gs2x4.GetArea())) ;
   TRY_TESTME( IsZero(128./12.-gs2x4.GetI11())) ;
   TRY_TESTME( IsZero(32./12-gs2x4.GetI22())) ;
   TRY_TESTME( IsZero(gs2x4.GetIxy())) ;
   TRY_TESTME( IsZero(4-gs2x4.GetI12Max())) ;
   TRY_TESTME( IsZero(4+gs2x4.GetI12Min())) ;
   TRY_TESTME( IsZero(2-gs2x4.GetYtop())) ;
   TRY_TESTME( IsZero(2-gs2x4.GetYbottom())) ;
   TRY_TESTME( IsZero(1-gs2x4.GetXright())) ;
   TRY_TESTME( IsZero(1-gs2x4.GetXleft())) ;

   // try rotation to principal
   ShapeProperties gsr(4., Point2d(0,0), 16., 64., -32, 1, 2, 1, 2);
   gsr.SetCoordinateSystem(ShapeProperties::CoordinateSystemType::Principal);
   TRY_TESTME(gsr.GetCoordinateSystem() == ShapeProperties::CoordinateSystemType::Principal);
   TRY_TESTME(IsZero(4 - gsr.GetArea()));
   TRY_TESTME(IsZero(80. - gsr.GetI11()));
   TRY_TESTME(IsZero(gsr.GetI22()));
   TRY_TESTME(IsZero(gsr.GetIxy()));
   TRY_TESTME(IsZero(40 - gsr.GetI12Max()));
   TRY_TESTME(IsZero(40 + gsr.GetI12Min()));

   // try addition and subtraction
   ShapeProperties s1(4., Point2d(4, 2), 0, 0, 0, 0, 0, 0, 0);
   ShapeProperties s2(4., Point2d(-4, -2), 0, 0, 0, 0, 0, 0, 0);
   ShapeProperties s4(-4., Point2d(-4, -2), 0, 0, 0, 0, 0, 0, 0);
   ShapeProperties s3 = s1 + s2;
   TRY_TESTME(IsZero(8 - s3.GetArea()));
   TRY_TESTME(IsZero(160. - s3.GetI11()));
   TRY_TESTME(IsZero(s3.GetI22()));
   TRY_TESTME(IsZero(32 - s3.GetIxx()));
   TRY_TESTME(IsZero(128 - s3.GetIyy()));
   TRY_TESTME(IsZero(64 - s3.GetIxy()));

   s3 = s3 + s4;
   s3.SetXleft(0);
   s3.SetXright(0);
   s3.SetYtop(0);
   s3.SetYbottom(0);
   TRY_TESTME(s3 == s1);

   // take a dump
#if defined _DEBUG
   gsr.Dump(rlog.GetLogContext());
#endif

   TRY_TESTME( Test_AddOperator1(rlog) );
   TRY_TESTME( Test_AddOperator2(rlog) );
   TRY_TESTME( Test_Assignment1(rlog) );
   TRY_TESTME( Test_Assignment2(rlog) );

   // Properties of a L6x4x7/8
   Float64 area = 7.98;
   Float64 ixx = 27.7;
   Float64 iyy = 9.75;
   Float64 ixy = 7.153;
   Float64 cgx = 1.12;
   Float64 cgy = 2.12;
   Float64 xLeft = 0;
   Float64 yBottom = 0;
   Float64 xRight = 4.0;
   Float64 yTop = 6.0;

   ShapeProperties props(area,Point2d(cgx,cgy),ixx, iyy, ixy,xLeft, yBottom,xRight, yTop);

   //
   // Test properties
   //
   TRY_TESTME(IsEqual(props.GetArea(), area));
   TRY_TESTME(IsEqual(props.GetIxx(), ixx));
   TRY_TESTME(IsEqual(props.GetIyy(), iyy));
   TRY_TESTME(IsEqual(props.GetIxy(), ixy));
   TRY_TESTME(IsEqual(props.GetCentroid().X(), cgx));
   TRY_TESTME(IsEqual(props.GetCentroid().Y(), cgy));

   TRY_TESTME(IsEqual(props.GetXleft(), xLeft));
   TRY_TESTME(IsEqual(props.GetXright(), xRight));
   TRY_TESTME(IsEqual(props.GetYtop(), yTop));
   TRY_TESTME(IsEqual(props.GetYbottom(), yBottom));

   TRY_TESTME(props.GetCoordinateSystem() == ShapeProperties::CoordinateSystemType::Centroidal);

   // Default orientation is 0.0
   TRY_TESTME(IsZero(props.GetOrientation()));

   // Default origin is (0.0,0.0)
   TRY_TESTME(props.GetOrigin() == Point2d(0, 0));

   //
   // Principle Direction
   //
   TRY_TESTME(IsEqual(props.GetPrincipalDirection(), 0.33645));

   //
   // Principle Values
   //
   TRY_TESTME(IsEqual(props.GetI11(), 30.20176));
   TRY_TESTME(IsEqual(props.GetI22(), 7.248239));
   TRY_TESTME(IsEqual(props.GetI12Min(), -11.47676));
   TRY_TESTME(IsEqual(props.GetI12Max(), 11.47676));

   //
   // Move the origin
   //
   Point2d pnt(10, 20);
   props.SetOrigin(pnt);
   TRY_TESTME(props.GetCoordinateSystem() == ShapeProperties::CoordinateSystemType::UserDefined);
   TRY_TESTME(props.GetOrigin() == pnt);
   TRY_TESTME(props.GetCentroid() == Point2d(cgx - 10, cgy - 20));
   TRY_TESTME(IsEqual(props.GetIxx(), ixx + area * (cgy - 20) * (cgy - 20)));
   TRY_TESTME(IsEqual(props.GetIyy(), iyy + area * (cgx - 10) * (cgx - 10)));
   TRY_TESTME(IsEqual(props.GetIxy(), ixy + area * (cgx - 10) * (cgy - 20)));

   // Put the origin back at (0,0)
   pnt.Move(0, 0);
   props.SetOrigin(pnt);

   TRY_TESTME(IsEqual(props.GetArea(), area));
   TRY_TESTME(IsEqual(props.GetIxx(), ixx + area * cgy * cgy));
   TRY_TESTME(IsEqual(props.GetIyy(), iyy + area * cgx * cgx));
   TRY_TESTME(IsEqual(props.GetIxy(), ixy + area * cgx * cgy));

   //
   // Test Orientation
   //
   props.SetOrientation(M_PI);
   TRY_TESTME(IsEqual(props.GetOrientation(), M_PI));
   TRY_TESTME(props.GetCoordinateSystem() == ShapeProperties::CoordinateSystemType::UserDefined);

   TRY_TESTME(IsEqual(props.GetArea(), area));
   TRY_TESTME(IsEqual(props.GetIxx(), ixx + area * cgy * cgy));
   TRY_TESTME(IsEqual(props.GetIyy(), iyy + area * cgx * cgx));
   TRY_TESTME(IsEqual(props.GetIxy(), ixy + area * cgx * cgy));
   TRY_TESTME(props.GetCentroid() == Point2d(-cgx, -cgy));

   //
   // Test CoordinateSystem property
   //

   // global
   props.SetCoordinateSystem(ShapeProperties::CoordinateSystemType::Global);
   TRY_TESTME(props.GetCoordinateSystem() == ShapeProperties::CoordinateSystemType::Global);

   TRY_TESTME(IsEqual(props.GetIxx(), ixx + area * cgy * cgy));
   TRY_TESTME(IsEqual(props.GetIyy(), iyy + area * cgx * cgx));
   TRY_TESTME(IsEqual(props.GetIxy(), ixy + area * cgx * cgy));
   TRY_TESTME(IsEqual(props.GetArea(), area));
   TRY_TESTME(IsEqual(props.GetOrientation(), 0.0));
   TRY_TESTME(props.GetCentroid() == Point2d(cgx, cgy));
   TRY_TESTME(props.GetOrigin() == Point2d(0, 0));

   // centroidal
   props.SetCoordinateSystem(ShapeProperties::CoordinateSystemType::Centroidal);
   TRY_TESTME(props.GetCoordinateSystem() == ShapeProperties::CoordinateSystemType::Centroidal);

   TRY_TESTME(IsEqual(props.GetIxx(), ixx));
   TRY_TESTME(IsEqual(props.GetIyy(), iyy));
   TRY_TESTME(IsEqual(props.GetIxy(), ixy));
   TRY_TESTME(IsEqual(props.GetArea(), area));
   TRY_TESTME(IsEqual(props.GetOrientation(), 0.0));

   TRY_TESTME(props.GetCentroid() == Point2d(cgx, cgy));
   TRY_TESTME(props.GetOrigin() == Point2d(cgx, cgy));

   // principle
   props.SetCoordinateSystem(ShapeProperties::CoordinateSystemType::Principal);
   TRY_TESTME(props.GetCoordinateSystem() == ShapeProperties::CoordinateSystemType::Principal);

   TRY_TESTME(IsEqual(props.GetIxx(), 30.20176));
   TRY_TESTME(IsEqual(props.GetIyy(), 7.248239));
   TRY_TESTME(IsEqual(props.GetIxy(), 0.0));
   TRY_TESTME(IsEqual(props.GetArea(), area));
   TRY_TESTME(IsEqual(props.GetOrientation(), 0.33645));

   TRY_TESTME(props.GetCentroid() == Point2d(0, 0));
   TRY_TESTME(props.GetOrigin() == Point2d(cgx, cgy));

   // user
   props.SetCoordinateSystem(ShapeProperties::CoordinateSystemType::UserDefined);
   TRY_TESTME(props.GetCoordinateSystem() == ShapeProperties::CoordinateSystemType::UserDefined);

   TRY_TESTME(IsEqual(props.GetIxx(), 30.20176));
   TRY_TESTME(IsEqual(props.GetIyy(), 7.248239));
   TRY_TESTME(IsEqual(props.GetIxy(), 0.0));
   TRY_TESTME(IsEqual(props.GetArea(), area));
   TRY_TESTME(IsEqual(props.GetOrientation(), 0.33645));

   TRY_TESTME(props.GetCentroid() == Point2d(0, 0));
   TRY_TESTME(props.GetOrigin() == Point2d(cgx, cgy));

   //////////////////////////////////////

   ShapeProperties prop1, prop2;

   // Initialize shape 1
   // Rectangle 5 wide x 10 high
   // Bottom Left at 5,15
   prop1.SetArea(50);
   prop1.SetIxx(416.66667);
   prop1.SetIyy(104.16667);
   prop1.SetIxy(0);
   prop1.SetCentroid(Point2d(7.5, 20));
   prop1.SetXleft(2.5);
   prop1.SetXright(2.5);
   prop1.SetYtop(5.0);
   prop1.SetYbottom(5.0);

   // Initialize shape 2
   // Rectangle 2 wide x 5 high
   // Bottom left at 20,5
   prop2.SetArea(10);
   prop2.SetIxx(20.833333);
   prop2.SetIyy(3.33333);
   prop2.SetIxy(0);
   prop2.SetCentroid(Point2d(21, 7.5));
   prop2.SetXleft(1.0);
   prop2.SetXright(1.0);
   prop2.SetYtop(2.5);
   prop2.SetYbottom(2.5);

   // Add the properties together
   prop1 += prop2;

   // Transform to global coordinates for easier validation
   prop1.SetCoordinateSystem(ShapeProperties::CoordinateSystemType::Global);

   TRY_TESTME(IsEqual(prop1.GetArea(), 60.));
   TRY_TESTME(IsEqual(prop1.GetIxx(), 21000.));
   TRY_TESTME(IsEqual(prop1.GetIyy(), 7330.));
   TRY_TESTME(IsEqual(prop1.GetIxy(), 9075.));
   TRY_TESTME(prop1.GetCentroid() == Point2d(9.75, 17.91666666666667));

   TRY_TESTME(IsEqual(prop1.GetXleft(), 4.75));
   TRY_TESTME(IsEqual(prop1.GetXright(), 12.25));
   TRY_TESTME(IsEqual(prop1.GetYtop(), 7.083333333));
   TRY_TESTME(IsEqual(prop1.GetYbottom(), 12.91666667));

   // Add a shape with no area and make sure results stay the same
   // The xleft, xright, ytop, and ybottom values will be effected.
   ShapeProperties prop3;
   prop1 += prop3;

   // Confirm nothing changed

   // Transform to global coordinates for easier validation
   prop1.SetCoordinateSystem(ShapeProperties::CoordinateSystemType::Global);

   TRY_TESTME(IsEqual(prop1.GetArea(), 60.));
   TRY_TESTME(IsEqual(prop1.GetIxx(), 21000.));
   TRY_TESTME(IsEqual(prop1.GetIyy(), 7330.));
   TRY_TESTME(IsEqual(prop1.GetIxy(), 9075.));
   TRY_TESTME(prop1.GetCentroid() == Point2d(9.75, 17.91666666666667));

   TRY_TESTME(IsEqual(prop1.GetXleft(), 9.75));
   TRY_TESTME(IsEqual(prop1.GetXright(), 12.25));
   TRY_TESTME(IsEqual(prop1.GetYtop(), 7.083333333));
   TRY_TESTME(IsEqual(prop1.GetYbottom(), 17.91666667));


   TESTME_EPILOG("ShapeProperties");
}

#endif // _UNITTEST


