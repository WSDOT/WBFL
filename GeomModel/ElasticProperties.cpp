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
#include <GeomModel/ElasticProperties.h>

#include <MathEx.h>
#include <iostream>

using namespace WBFL::Geometry;

ElasticProperties::ElasticProperties()
{
}

ElasticProperties::ElasticProperties(Float64 eA,
                           const Point2d& centroid,
                           Float64 eIxx, Float64 eIyy, Float64 eIxy,
                           Float64 xLeft, Float64 yBottom,
                           Float64 xRight, Float64 yTop):
m_Properties(eA, centroid, eIxx, eIyy, eIxy, xLeft, yBottom, xRight,yTop)
{
}

ElasticProperties::~ElasticProperties()
{
}

bool ElasticProperties::operator==(const ElasticProperties& rhs) const
{
   return m_Properties == rhs.m_Properties;
}

bool ElasticProperties::operator!=(const ElasticProperties& rhs) const
{
   return !(*this == rhs);
}

ElasticProperties ElasticProperties::operator+ (const ElasticProperties& rhs) const
{
   ElasticProperties tmp(*this);
   return tmp+=rhs;
}


ElasticProperties& ElasticProperties::operator+= (const ElasticProperties& rhs)
{
   m_Properties+=rhs.m_Properties;
   return *this;
}

ElasticProperties ElasticProperties::operator- (const ElasticProperties& rhs) const
{
   ElasticProperties tmp(*this);
   return tmp -= rhs;
}

ElasticProperties& ElasticProperties::operator-= (const ElasticProperties& rhs)
{
   m_Properties -= rhs.m_Properties;
   return *this;
}

void ElasticProperties::SetEA(Float64 eA)
{
   m_Properties.SetArea(eA);
}

Float64 ElasticProperties::GetEA() const
{
   return m_Properties.GetArea();
}

void ElasticProperties::SetCentroid(const Point2d& cent)
{
   m_Properties.SetCentroid(cent);
}

const Point2d& ElasticProperties::GetCentroid() const
{
   return m_Properties.GetCentroid();
}

void ElasticProperties::SetEIxx(Float64 eIxx)
{
   m_Properties.SetIxx(eIxx);
}

Float64 ElasticProperties::GetEIxx() const
{
   return m_Properties.GetIxx();
}

void ElasticProperties::SetEIyy(Float64 eIyy)
{
   m_Properties.SetIyy(eIyy);
}

Float64 ElasticProperties::GetEIyy() const
{
   return m_Properties.GetIyy();
}

void ElasticProperties::SetEIxy(Float64 eIxy)
{
   m_Properties.SetIxy(eIxy);
}

Float64 ElasticProperties::GetEIxy() const
{
   return m_Properties.GetIxy();
}

void ElasticProperties::SetYtop(Float64 ytop)
{
   m_Properties.SetYtop(ytop);
}

Float64 ElasticProperties::GetYtop() const
{
   return m_Properties.GetYtop();
}

void ElasticProperties::SetYbottom(Float64 ybot)
{
   m_Properties.SetYbottom(ybot);
}

Float64 ElasticProperties::GetYbottom() const
{
   return m_Properties.GetYbottom();
}

void ElasticProperties::SetXleft(Float64 xleft)
{
   m_Properties.SetXleft(xleft);
}

Float64 ElasticProperties::GetXleft() const
{
   return m_Properties.GetXleft();
}

void ElasticProperties::SetXright(Float64 xright)
{
   m_Properties.SetXright(xright);
}

Float64 ElasticProperties::GetXright() const
{
   return m_Properties.GetXright();
}

Float64 ElasticProperties::GetEI11() const
{
   return m_Properties.GetI11();
}

Float64 ElasticProperties::GetEI22() const
{
   return m_Properties.GetI22();
}

Float64 ElasticProperties::GetPrincipalDirection() const
{
   return m_Properties.GetPrincipalDirection();
}

Float64 ElasticProperties::GetEI12Max() const
{
   return m_Properties.GetI12Max();
}

Float64 ElasticProperties::GetEI12Min() const
{
   return m_Properties.GetI12Min();
}

void ElasticProperties::SetCoordinateSystem(ElasticProperties::CoordSystemType sys)
{
   ShapeProperties::CoordinateSystemType pct;
   switch(sys)
   {
   case CoordSystemType::Centroidal:
      {
         pct= ShapeProperties::CoordinateSystemType::Centroidal;
         break;
      }
      case CoordSystemType::Global:
      {
         pct= ShapeProperties::CoordinateSystemType::Global;
         break;
      }
      case CoordSystemType::Principal:
      {
         pct= ShapeProperties::CoordinateSystemType::Principal;
         break;
      }
      case CoordSystemType::UserDefined:
      {
         pct= ShapeProperties::CoordinateSystemType::UserDefined;
         break;
      }
      default:
         CHECKX(0, _T("Bad coordinate type"));
   }

   m_Properties.SetCoordinateSystem(pct);
}

ElasticProperties::CoordSystemType ElasticProperties::GetCoordinateSystem() const
{
   ElasticProperties::CoordSystemType epct= CoordSystemType::UserDefined;

   ShapeProperties::CoordinateSystemType pct = m_Properties.GetCoordinateSystem();
   switch(pct)
   {
      case ShapeProperties::CoordinateSystemType::Centroidal:
      {
         epct= CoordSystemType::Centroidal;
         break;
      }
      case ShapeProperties::CoordinateSystemType::Global:
      {
         epct= CoordSystemType::Global;
         break;
      }
      case ShapeProperties::CoordinateSystemType::Principal:
      {
         epct= CoordSystemType::Principal;
         break;
      }
      case ShapeProperties::CoordinateSystemType::UserDefined:
      {
         epct= CoordSystemType::UserDefined;
         break;
      }
      default:
         CHECKX(0,_T("Bad coordinate type"));
   }

   return epct;
}

void ElasticProperties::SetOrigin(const Point2d& origin)
{
   m_Properties.SetOrigin(origin);
}

const Point2d& ElasticProperties::GetOrigin() const
{
   return m_Properties.GetOrigin();
}

void ElasticProperties::SetOrientation(Float64 angle)
{
   m_Properties.SetOrientation(angle);
}

Float64 ElasticProperties::GetOrientation() const
{
   return m_Properties.GetOrientation();
}

ShapeProperties ElasticProperties::TransformProperties(Float64 E) const
{
   ShapeProperties props = m_Properties;
   props.SetArea( props.GetArea()/E );
   props.SetIxx( props.GetIxx()/E );
   props.SetIxy( props.GetIxy()/E );
   props.SetIyy( props.GetIyy()/E );

   return props;
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool ElasticProperties::AssertValid() const
{
   return true;
}

void ElasticProperties::Dump(WBFL::Debug::LogContext& os) const
{
   os << _T("Dump for ElasticProperties") << WBFL::Debug::endl;
   os << _T("Start Dump of implementation m_Properties:")<< WBFL::Debug::endl;
   m_Properties.Dump(os);
   os << _T("End Dump of implementation m_Properties:")<< WBFL::Debug::endl;
}

#endif // _DEBUG

#if defined _UNITTEST
bool ElasticProperties::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("ElasticProperties"); 

   // try a point area
      ElasticProperties gpa(4., Point2d(0,0), 0., 0., 0, 0,  0,  0, 0);
      TRY_TESTME( gpa.GetCoordinateSystem() == ElasticProperties::CoordSystemType::Centroidal ) ;
      TRY_TESTME( Point2d(0,0) == gpa.GetCentroid() ) ;
      TRY_TESTME( IsZero(4-gpa.GetEA()) ) ;
      TRY_TESTME( IsZero(gpa.GetEI11()) ) ;
      TRY_TESTME( IsZero(gpa.GetEI22()) ) ;
      TRY_TESTME( IsZero(gpa.GetEIxy()) ) ;
      TRY_TESTME( IsZero(gpa.GetEI12Max()) ) ;
      TRY_TESTME( IsZero(gpa.GetEI12Min()) ) ;
      TRY_TESTME( IsZero(gpa.GetYtop()) ) ;
      TRY_TESTME( IsZero(gpa.GetYbottom()) ) ;
      TRY_TESTME( IsZero(gpa.GetXright()) ) ;
      TRY_TESTME( IsZero(gpa.GetXleft()) ) ;

      // move origin
      Point2d orn(4,-2);
      gpa.SetOrigin(orn);
      TRY_TESTME( gpa.GetCoordinateSystem() == ElasticProperties::CoordSystemType::UserDefined ) ;
      TRY_TESTME( Point2d(-4,2) == gpa.GetCentroid() ) ;
      TRY_TESTME( IsZero(4-gpa.GetEA())) ;
      TRY_TESTME( IsZero( -63.43 - ToDegrees(gpa.GetPrincipalDirection()),.1)) ;
      TRY_TESTME( IsZero(16-gpa.GetEIxx())) ;
      TRY_TESTME( IsZero(64-gpa.GetEIyy())) ;
      TRY_TESTME( IsZero(32+gpa.GetEIxy())) ;
      TRY_TESTME( IsZero(80-gpa.GetEI11())) ;
      TRY_TESTME( IsZero(gpa.GetEI22())) ;
      TRY_TESTME( IsZero(40-gpa.GetEI12Max())) ;
      TRY_TESTME( IsZero(40+gpa.GetEI12Min())) ;
      TRY_TESTME( IsZero(gpa.GetYtop())) ;
      TRY_TESTME( IsZero(gpa.GetYbottom())) ;
      TRY_TESTME( IsZero(gpa.GetXright())) ;
      TRY_TESTME( IsZero(gpa.GetXleft())) ;

      // rotate 90 deg
      gpa.SetOrientation(M_PI/2);
      TRY_TESTME( gpa.GetCoordinateSystem() == ElasticProperties::CoordSystemType::UserDefined) ;
      TRY_TESTME( Point2d(2,4) == gpa.GetCentroid()) ;
      TRY_TESTME( IsZero(4-gpa.GetEA())) ;
      TRY_TESTME( IsZero(64-gpa.GetEIxx())) ;
      TRY_TESTME( IsZero(16-gpa.GetEIyy())) ;
      TRY_TESTME( IsZero(32-gpa.GetEIxy())) ;
      TRY_TESTME( IsZero(80.-gpa.GetEI11())) ;
      TRY_TESTME( IsZero(gpa.GetEI22())) ;
      TRY_TESTME( IsZero(40-gpa.GetEI12Max())) ;
      TRY_TESTME( IsZero(40+gpa.GetEI12Min())) ;

   // try a 2x4 rectangle
      ElasticProperties gs2x4(8., Point2d(0,0), 128./12., 32./12., 0, 1,2,1,2);
      TRY_TESTME( IsZero(8-gs2x4.GetEA())) ;
      TRY_TESTME( IsZero(128./12.-gs2x4.GetEI11())) ;
      TRY_TESTME( IsZero(32./12-gs2x4.GetEI22())) ;
      TRY_TESTME( IsZero(gs2x4.GetEIxy())) ;
      TRY_TESTME( IsZero(4-gs2x4.GetEI12Max())) ;
      TRY_TESTME( IsZero(4+gs2x4.GetEI12Min())) ;
      TRY_TESTME( IsZero(2-gs2x4.GetYtop())) ;
      TRY_TESTME( IsZero(2-gs2x4.GetYbottom())) ;
      TRY_TESTME( IsZero(1-gs2x4.GetXright())) ;
      TRY_TESTME( IsZero(1-gs2x4.GetXleft())) ;

      // move origin to user-defined location
      gs2x4.SetOrigin(orn); 
      TRY_TESTME( IsZero(8-gs2x4.GetEA())) ;
      TRY_TESTME( IsZero((128./12.+32)-gs2x4.GetEIxx())) ;
      TRY_TESTME( IsZero((32./12+128)-gs2x4.GetEIyy())) ;
      TRY_TESTME( IsZero(64+gs2x4.GetEIxy())) ;
      TRY_TESTME( IsZero( -62.25 - ToDegrees(gs2x4.GetPrincipalDirection()),.01)) ;
      TRY_TESTME( IsZero(77.67-gs2x4.GetEI12Max(),.01)) ;
      TRY_TESTME( IsZero(2-gs2x4.GetYtop())) ;
      TRY_TESTME( IsZero(2-gs2x4.GetYbottom())) ;
      TRY_TESTME( IsZero(1-gs2x4.GetXright())) ;
      TRY_TESTME( IsZero(1-gs2x4.GetXleft())) ;

   // move origin back to centroid
      gs2x4.SetCoordinateSystem(ElasticProperties::CoordSystemType::Centroidal);
      TRY_TESTME( gs2x4.GetCoordinateSystem() == ElasticProperties::CoordSystemType::Centroidal) ;
      TRY_TESTME( IsZero(8-gs2x4.GetEA())) ;
      TRY_TESTME( IsZero(128./12.-gs2x4.GetEI11())) ;
      TRY_TESTME( IsZero(32./12-gs2x4.GetEI22())) ;
      TRY_TESTME( IsZero(gs2x4.GetEIxy())) ;
      TRY_TESTME( IsZero(4-gs2x4.GetEI12Max())) ;
      TRY_TESTME( IsZero(4+gs2x4.GetEI12Min())) ;
      TRY_TESTME( IsZero(2-gs2x4.GetYtop())) ;
      TRY_TESTME( IsZero(2-gs2x4.GetYbottom())) ;
      TRY_TESTME( IsZero(1-gs2x4.GetXright())) ;
      TRY_TESTME( IsZero(1-gs2x4.GetXleft())) ;

   // try rotation to principal
      ElasticProperties gsr(4., Point2d(0,0), 16., 64., -32, 1,2,1,2);
      gsr.SetCoordinateSystem(ElasticProperties::CoordSystemType::Principal);
      TRY_TESTME( gsr.GetCoordinateSystem() == ElasticProperties::CoordSystemType::Principal) ;
      TRY_TESTME( IsZero(4-gsr.GetEA())) ;
      TRY_TESTME( IsZero(80.-gsr.GetEI11())) ;
      TRY_TESTME( IsZero(gsr.GetEI22())) ;
      TRY_TESTME( IsZero(gsr.GetEIxy())) ;
      TRY_TESTME( IsZero(40-gsr.GetEI12Max())) ;
      TRY_TESTME( IsZero(40+gsr.GetEI12Min())) ;

   // try addition and subraction
      ElasticProperties gps1( 4., Point2d( 4, 2), 0, 0, 0, 0, 0, 0, 0);
      ElasticProperties gps2( 4., Point2d(-4,-2), 0, 0, 0, 0, 0, 0, 0);
      ElasticProperties gps4(-4., Point2d(-4,-2), 0, 0, 0, 0, 0, 0, 0);
      ElasticProperties gps3 = gps1 + gps2;
      TRY_TESTME( IsZero(8-gps3.GetEA())) ;
      TRY_TESTME( IsZero(160.-gps3.GetEI11())) ;
      TRY_TESTME( IsZero(gps3.GetEI22())) ;
      TRY_TESTME( IsZero(32-gps3.GetEIxx())) ;
      TRY_TESTME( IsZero(128-gps3.GetEIyy())) ;
      TRY_TESTME( IsZero(64-gps3.GetEIxy())) ;

      gps3 = gps3 + gps4;
      gps3.SetXleft(0);
      gps3.SetXright(0);
      gps3.SetYtop(0);
      gps3.SetYbottom(0);
      TRY_TESTME ( gps3 == gps1 ) ;

   // take a dump
#if defined _DEBUG
      gsr.Dump(rlog.GetLogContext());
#endif

   TESTME_EPILOG("ElasticProperties");
}

#endif // _UNITTEST



