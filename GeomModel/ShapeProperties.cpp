///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
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
#include <GeomModel/ShapeProperties.h>

#include "MohrCircle.h"
#include <MathEx.h>
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace WBFL::Geometry;

ShapeProperties::ShapeProperties()
{
   SetProperties(0, Point2d(0,0), 0, 0, 0, 0, 0, 0, 0);
}

ShapeProperties::ShapeProperties(Float64 area,
   const Point2d& centroid,
   Float64 ixx, Float64 iyy, Float64 ixy,
   Float64 xLeft, Float64 yBottom,
   Float64 xRight, Float64 yTop)
{
   SetProperties(area, centroid, ixx, iyy, ixy, xLeft, yBottom,xRight,yTop);
}

ShapeProperties::~ShapeProperties()
{
}

bool ShapeProperties::operator==(const ShapeProperties& rhs) const
{
   return IsEqual(m_Area, rhs.m_Area) &&
      m_Centroid == rhs.m_Centroid &&
      IsEqual(m_Ixx, rhs.m_Ixx) &&
      IsEqual(m_Iyy, rhs.m_Iyy) &&
      IsEqual(m_Ixy, rhs.m_Ixy) &&
      IsEqual(m_Xleft,rhs.m_Xleft) &&
      IsEqual(m_Xright,rhs.m_Xright) &&
      IsEqual(m_Ytop,rhs.m_Ytop) &&
      IsEqual(m_Ybottom,rhs.m_Ybottom);
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
   PRECONDITION(0 <= xLeft && 0 <= yBottom && 0 <= xRight && 0 <= yTop);
   m_Area = area;
   m_Centroid = centroid;
   m_Ixx = ixx;
   m_Iyy = iyy;
   m_Ixy = ixy;

   m_Ytop = yTop;
   m_Ybottom = yBottom;
   m_Xleft = xLeft;
   m_Xright = xRight;

   m_CoordType = CoordSystemType::Centroidal;
   m_Orientation = 0;

   UpdateOrientation();
}

void ShapeProperties::GetProperties(Float64* area, Point2d* centroid, Float64* ixx, Float64* iyy, Float64* ixy, Float64* xLeft, Float64* yBottom, Float64* xRight, Float64* yTop) const
{
   *area = m_Area;
   *centroid = m_Centroid;
   *ixx = m_Ixx;
   *iyy = m_Iyy;
   *ixy = m_Ixy;
   *yTop = m_Ytop;
   *yBottom = m_Ybottom;
   *xLeft = m_Xleft;
   *xRight = m_Xright;
}

void ShapeProperties::Clear()
{
   SetProperties(0, Point2d(0,0), 0, 0, 0, 0, 0, 0, 0);
}

void ShapeProperties::SetArea(Float64 area)
{
   m_Area = area;
}

Float64 ShapeProperties::GetArea() const
{
   return m_Area;
}

void ShapeProperties::SetCentroid(const Point2d& cent)
{
   m_Centroid = cent;
   UpdateOrientation();
}

const Point2d& ShapeProperties::GetCentroid() const
{
   return m_CurrCentroid;
}

void ShapeProperties::SetIxx(Float64 ixx)
{
   m_Ixx = ixx;
   UpdateOrientation();
}

Float64 ShapeProperties::GetIxx() const
{
   return m_CurrIxx;
}

void ShapeProperties::SetIyy(Float64 iyy)
{
   m_Iyy = iyy;
   UpdateOrientation();
}

Float64 ShapeProperties::GetIyy() const
{
   return m_CurrIyy;
}

void ShapeProperties::SetIxy(Float64 ixy)
{
   m_Ixy = ixy;
   UpdateOrientation();
}

Float64 ShapeProperties::GetIxy() const
{
   return m_CurrIxy;
}

void ShapeProperties::SetYtop(Float64 yTop)
{
   PRECONDITION(0 <= yTop);
   m_Ytop = yTop;
}

Float64 ShapeProperties::GetYtop() const
{
   return m_Ytop;
}

void ShapeProperties::SetYbottom(Float64 yBottom)
{
   PRECONDITION(0 <= yBottom);
   m_Ybottom = yBottom;
}

Float64 ShapeProperties::GetYbottom() const
{
   return m_Ybottom;
}

void ShapeProperties::SetXleft(Float64 xLeft)
{
   PRECONDITION(0 <= xLeft);
   m_Xleft = xLeft;
}

Float64 ShapeProperties::GetXleft() const
{
   return m_Xleft;
}

void ShapeProperties::SetXright(Float64 xRight)
{
   PRECONDITION(0 <= xRight);
   m_Xright = xRight;
}

Float64 ShapeProperties::GetXright() const
{
   return m_Xright;
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

void ShapeProperties::SetCoordinateSystem(ShapeProperties::CoordSystemType sys)
{
   switch(sys)
   {
   case CoordSystemType::Centroidal:
      {
         m_CoordType = sys;
         m_Origin = m_Centroid;
         m_Orientation = 0;
         UpdateOrientation();
         break;
      }
      case CoordSystemType::Global:
      {
         m_CoordType = sys;
         m_Origin = Point2d(0,0);
         m_Orientation = 0;
         UpdateOrientation();
         break;
      }
      case CoordSystemType::Principal:
      {
         // first have to get principal orientation angle
         SetCoordinateSystem(CoordSystemType::Centroidal);
         m_Orientation = GetPrincipalDirection();
         m_CoordType = sys;
         UpdateOrientation();
         break;
      }
      case CoordSystemType::UserDefined:
      {
         m_CoordType = sys;
         break;
      }
      default:
         CHECKX(0,_T("Bad coordinate type"));
   }
}

ShapeProperties::CoordSystemType ShapeProperties::GetCoordinateSystem() const
{
   return m_CoordType;
}

void ShapeProperties::SetOrigin(const Point2d& origin)
{
      m_CoordType = CoordSystemType::UserDefined;
      m_Origin = origin;
      UpdateOrientation();
}

const Point2d& ShapeProperties::GetOrigin() const
{
   return m_Origin;
}

void ShapeProperties::SetOrientation(Float64 angle)
{
      m_CoordType = CoordSystemType::UserDefined;
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

void ShapeProperties::Dump(dbgDumpContext& os) const
{
   os << _T("Dump for ShapeProperties") << endl;
   os << _T("   m_Area         = ")<< m_Area <<endl;
   os << _T("   m_Centroid     = (")<< m_Centroid.X()<<_T(", ")<<m_Centroid.Y()<<_T(")")<<endl;
   os << _T("   m_Ixx          = ")<< m_Ixx <<endl;         
   os << _T("   m_Iyy          = ")<< m_Iyy <<endl;          
   os << _T("   m_Ixy          = ")<< m_Ixy <<endl;         
   os << _T("   m_CoordType    = ")<< (int)m_CoordType <<endl;   
   os << _T("   m_Origin       = (")<<m_Origin.X()<<_T(", ")<<m_Origin.Y()<<_T(")") <<endl;
   os << _T("   m_Orientation  = ")<< m_Orientation <<endl;
   os << _T("   m_CurrCentroid = (")<< m_CurrCentroid.X()<<_T(", ")<<m_CurrCentroid.Y()<<_T(")")<<endl;
   os << _T("   m_CurrIxx      = ")<< m_CurrIxx <<endl;
   os << _T("   m_CurrIyy      = ")<< m_CurrIyy <<endl;
   os << _T("   m_CurrIxy      = ")<< m_CurrIxy <<endl;
}

#endif // _DEBUG

void ShapeProperties::UpdateOrientation()
{
   switch (m_CoordType)
   {
   case (CoordSystemType::Centroidal):
      {
         // in centroidal system = just copy values
         m_CurrCentroid = m_Centroid;
         m_CurrIxx      = m_Ixx;
         m_CurrIyy      = m_Iyy;
         m_CurrIxy      = m_Ixy;
         break;
      }
   default:
      {
         // not centroidal - need to rotate into orientation
         // first rotate about centroid
         Float64 ixx, iyy, ixy;
         MohrCircle ms(m_Ixx, m_Iyy, m_Ixy);
         ms.ComputeState(m_Orientation,ixx, iyy, ixy);

         // next need to transform into origin coord's
         Point2d delta( m_Centroid.X() - m_Origin.X(), m_Centroid.Y() - m_Origin.Y());
         delta.Rotate(Point2d(0,0), -m_Orientation);

         Float64 dx = delta.X();
         Float64 dy = delta.Y();

         // use parallel axis theorem to put properties into new system
         m_CurrCentroid = delta;
         m_CurrIxx      = ixx + m_Area * dy * dy;
         m_CurrIyy      = iyy + m_Area * dx * dx;
         m_CurrIxy      = ixy + m_Area * dx * dy;
         break;
      }
   }
}

ShapeProperties& ShapeProperties::Join(const ShapeProperties& rOther, Float64 scale)
{
   auto currCoordinateSystemType = m_CoordType; // reserve the current coordinate system type

   // convert to global coordinates
   SetCoordinateSystem(CoordSystemType::Global);
   ShapeProperties other(rOther);
   other.SetCoordinateSystem(CoordSystemType::Global);

   Float64 ixx = 0, iyy = 0, ixy = 0; // about global axes
   Float64 mxx = 0, myy = 0;        // first moments

   Float64 cx1, cy1;
   m_Centroid.GetLocation(&cx1, &cy1);

   Float64 cx2, cy2;
   other.GetCentroid().GetLocation(&cx2, &cy2);

   mxx = m_Area * m_Centroid.Y() + scale* other.m_Area * other.m_Centroid.Y();
   myy = m_Area * m_Centroid.X() + scale * other.m_Area * other.m_Centroid.X();

   // Get centriodal I for each shape and transform it to the global axes
   ixx = (m_Ixx + m_Area * m_Centroid.Y() * m_Centroid.Y() +
      scale * other.m_Ixx + scale * other.m_Area * other.m_Centroid.Y() * other.m_Centroid.Y());

   iyy = (m_Iyy + m_Area * m_Centroid.X() * m_Centroid.X() +
      scale * other.m_Iyy + scale * other.m_Area * other.m_Centroid.X() * other.m_Centroid.X());

   ixy = (m_Ixy + m_Area * m_Centroid.X() * m_Centroid.Y() +
      scale * other.m_Ixy + scale * other.m_Area * other.m_Centroid.X() * other.m_Centroid.Y());

   m_Area += scale * other.m_Area;

   m_Centroid.Y() = mxx / m_Area;
   m_Centroid.X() = myy / m_Area;

   Float64 cgx, cgy;
   m_Centroid.GetLocation(&cgx, &cgy);

   m_Ixx = ixx - m_Area * m_Centroid.Y() * m_Centroid.Y();
   m_Iyy = iyy - m_Area * m_Centroid.X() * m_Centroid.X();
   m_Ixy = ixy - m_Area * m_Centroid.X() * m_Centroid.Y();

   // Update the distance from the edges to the centroid
   Float64 l2 = other.GetXleft();
   Float64 r2 = other.GetXright();
   Float64 t2 = other.GetYtop();
   Float64 b2 = other.GetYbottom();

   Float64 l, r, t, b; // distance from the global axes to the extreme edges
   l = Min(cx1 - m_Xleft, cx2 - l2);
   r = Max(cx1 + m_Xright, cx2 + r2);
   t = Max(cy1 + m_Ytop, cy2 + t2);
   b = Min(cy1 - m_Ybottom, cy2 - b2);

   m_Xleft = cgx - l;
   m_Xright = r - cgx;
   m_Ytop = t - cgy;
   m_Ybottom = cgy - b;

   UpdateOrientation();

   // restore the original coordinate system
   SetCoordinateSystem(currCoordinateSystemType);

   return *this;
}

#if defined _UNITTEST
bool Test_AddOperator1(dbgLog& rlog)
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

bool Test_AddOperator2(dbgLog& rlog)
{
   // Test the addition of properties when one property object is in centroidal
   // coordinates and one is in global coordaintes
   TESTME_PROLOGUE( "ShapeProperties - Test_AddOperator2" );

   ShapeProperties shape1(10,Point2d(10,10),10,10,10,10,10,10,10);
   ShapeProperties shape2(20,Point2d(20,20),20,20,20,20,20,20,20);
   shape2.SetCoordinateSystem( ShapeProperties::CoordSystemType::Global );

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

bool Test_Assignment1(dbgLog& rlog)
{
   TESTME_PROLOGUE( "ShapeProperties - Test_Assignment1" );

   // Test the mutators and accessor when property object is in centrodial units
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

bool Test_Assignment2(dbgLog& rlog)
{
   TESTME_PROLOGUE( "ShapeProperties - Test_Assignment2" );

   // Test the mutators and accessor when property object is in centrodial units
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

bool ShapeProperties::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("ShapeProperties");
   // try a point area
   ShapeProperties a(4., Point2d(0,0), 0., 0., 0, 0,  0,  0, 0);
   TRY_TESTME(a.GetCoordinateSystem() == ShapeProperties::CoordSystemType::Centroidal) ;
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
   TRY_TESTME( a.GetCoordinateSystem() == ShapeProperties::CoordSystemType::UserDefined) ;
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
   TRY_TESTME( a.GetCoordinateSystem() == ShapeProperties::CoordSystemType::UserDefined) ;
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
   gs2x4.SetCoordinateSystem(ShapeProperties::CoordSystemType::Centroidal);
   TRY_TESTME( gs2x4.GetCoordinateSystem() == ShapeProperties::CoordSystemType::Centroidal) ;
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
   gsr.SetCoordinateSystem(ShapeProperties::CoordSystemType::Principal);
   TRY_TESTME(gsr.GetCoordinateSystem() == ShapeProperties::CoordSystemType::Principal);
   TRY_TESTME(IsZero(4 - gsr.GetArea()));
   TRY_TESTME(IsZero(80. - gsr.GetI11()));
   TRY_TESTME(IsZero(gsr.GetI22()));
   TRY_TESTME(IsZero(gsr.GetIxy()));
   TRY_TESTME(IsZero(40 - gsr.GetI12Max()));
   TRY_TESTME(IsZero(40 + gsr.GetI12Min()));

   // try addition and subraction
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
   gsr.Dump(rlog.GetDumpCtx());
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

   TRY_TESTME(props.GetCoordinateSystem() == ShapeProperties::CoordSystemType::Centroidal);

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
   TRY_TESTME(props.GetCoordinateSystem() == ShapeProperties::CoordSystemType::UserDefined);
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
   TRY_TESTME(props.GetCoordinateSystem() == ShapeProperties::CoordSystemType::UserDefined);

   TRY_TESTME(IsEqual(props.GetArea(), area));
   TRY_TESTME(IsEqual(props.GetIxx(), ixx + area * cgy * cgy));
   TRY_TESTME(IsEqual(props.GetIyy(), iyy + area * cgx * cgx));
   TRY_TESTME(IsEqual(props.GetIxy(), ixy + area * cgx * cgy));
   TRY_TESTME(props.GetCentroid() == Point2d(-cgx, -cgy));

   //
   // Test CoordinateSystem property
   //

   // global
   props.SetCoordinateSystem(ShapeProperties::CoordSystemType::Global);
   TRY_TESTME(props.GetCoordinateSystem() == ShapeProperties::CoordSystemType::Global);

   TRY_TESTME(IsEqual(props.GetIxx(), ixx + area * cgy * cgy));
   TRY_TESTME(IsEqual(props.GetIyy(), iyy + area * cgx * cgx));
   TRY_TESTME(IsEqual(props.GetIxy(), ixy + area * cgx * cgy));
   TRY_TESTME(IsEqual(props.GetArea(), area));
   TRY_TESTME(IsEqual(props.GetOrientation(), 0.0));
   TRY_TESTME(props.GetCentroid() == Point2d(cgx, cgy));
   TRY_TESTME(props.GetOrigin() == Point2d(0, 0));

   // centroidal
   props.SetCoordinateSystem(ShapeProperties::CoordSystemType::Centroidal);
   TRY_TESTME(props.GetCoordinateSystem() == ShapeProperties::CoordSystemType::Centroidal);

   TRY_TESTME(IsEqual(props.GetIxx(), ixx));
   TRY_TESTME(IsEqual(props.GetIyy(), iyy));
   TRY_TESTME(IsEqual(props.GetIxy(), ixy));
   TRY_TESTME(IsEqual(props.GetArea(), area));
   TRY_TESTME(IsEqual(props.GetOrientation(), 0.0));

   TRY_TESTME(props.GetCentroid() == Point2d(cgx, cgy));
   TRY_TESTME(props.GetOrigin() == Point2d(cgx, cgy));

   // principle
   props.SetCoordinateSystem(ShapeProperties::CoordSystemType::Principal);
   TRY_TESTME(props.GetCoordinateSystem() == ShapeProperties::CoordSystemType::Principal);

   TRY_TESTME(IsEqual(props.GetIxx(), 30.20176));
   TRY_TESTME(IsEqual(props.GetIyy(), 7.248239));
   TRY_TESTME(IsEqual(props.GetIxy(), 0.0));
   TRY_TESTME(IsEqual(props.GetArea(), area));
   TRY_TESTME(IsEqual(props.GetOrientation(), 0.33645));

   TRY_TESTME(props.GetCentroid() == Point2d(0, 0));
   TRY_TESTME(props.GetOrigin() == Point2d(cgx, cgy));

   // user
   props.SetCoordinateSystem(ShapeProperties::CoordSystemType::UserDefined);
   TRY_TESTME(props.GetCoordinateSystem() == ShapeProperties::CoordSystemType::UserDefined);

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
   prop1.SetCoordinateSystem(ShapeProperties::CoordSystemType::Global);

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
   prop1.SetCoordinateSystem(ShapeProperties::CoordSystemType::Global);

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


