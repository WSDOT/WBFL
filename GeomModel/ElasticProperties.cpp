///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
// Copyright © 1999-2010  Washington State Department of Transportation
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

#include <GeomModel\GeomModelLib.h>
#include <GeomModel\ElasticProperties.h>

#include <EngTools\MohrCircle.h>
#include <MathEx.h>
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   gmElasticProperties
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
gmElasticProperties::gmElasticProperties():
m_Properties()
{
}

gmElasticProperties::gmElasticProperties(Float64 eA,
                           const gpPoint2d& centroid,
                           Float64 eIxx, Float64 eIyy, Float64 eIxy,
                           Float64 yTop, Float64 yBottom,
                           Float64 xLeft, Float64 xRight,
                           Float64 perimeter):
m_Properties(eA, centroid, eIxx, eIyy, eIxy, yTop, yBottom, xLeft, xRight,perimeter)
{
}



gmElasticProperties::gmElasticProperties(const gmElasticProperties& rOther)
{
   MakeCopy(rOther);
}

gmElasticProperties::~gmElasticProperties()
{
}

//======================== OPERATORS  =======================================
gmElasticProperties& gmElasticProperties::operator= (const gmElasticProperties& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

gmElasticProperties gmElasticProperties::operator+ (const gmElasticProperties& rhs) const
{
   gmElasticProperties tmp(*this);
   return tmp+=rhs;
}


gmElasticProperties& gmElasticProperties::operator+= (const gmElasticProperties& rhs)
{
   m_Properties+=rhs.m_Properties;
   return *this;
}




//======================== OPERATIONS =======================================

Float64 gmElasticProperties::SetEA(Float64 eA)
{
   return m_Properties.SetArea(eA);
}

gpPoint2d gmElasticProperties::SetCentroid(gpPoint2d cent)
{
   return m_Properties.SetCentroid(cent);
}

Float64 gmElasticProperties::SetEIxx(Float64 eIxx)
{
   return m_Properties.SetIxx(eIxx);
}

Float64 gmElasticProperties::SetEIyy(Float64 eIyy)
{
   return m_Properties.SetIyy(eIyy);
}

Float64 gmElasticProperties::SetEIxy(Float64 eIxy)
{
   return m_Properties.SetIxy(eIxy);
}

Float64 gmElasticProperties::SetYtop(Float64 ytop)
{
   return m_Properties.SetYtop(ytop);
}

Float64 gmElasticProperties::SetYbottom(Float64 ybot)
{
   return m_Properties.SetYbottom(ybot);
}

Float64 gmElasticProperties::SetXleft(Float64 xleft)
{
   return m_Properties.SetXleft(xleft);
}

Float64 gmElasticProperties::SetXright(Float64 xright)
{
   return m_Properties.SetXright(xright);
}

Float64 gmElasticProperties::SetPerimeter(Float64 p)
{
   return m_Properties.SetPerimeter(p);
}

Float64 gmElasticProperties::EA() const
{
   return m_Properties.Area();
}

gpPoint2d gmElasticProperties::Centroid() const
{
   return m_Properties.Centroid();
}

Float64 gmElasticProperties::EIxx() const
{
   return m_Properties.Ixx();
}

Float64 gmElasticProperties::EIyy() const
{
   return m_Properties.Iyy();
}

Float64 gmElasticProperties::EIxy() const
{
   return m_Properties.Ixy();
}

Float64 gmElasticProperties::Ytop() const
{
   return m_Properties.Ytop();
}

Float64 gmElasticProperties::Ybottom() const
{
   return m_Properties.Ybottom();
}

Float64 gmElasticProperties::Xleft() const
{
   return m_Properties.Xleft();
}

Float64 gmElasticProperties::Xright() const
{
   return m_Properties.Xright();
}

Float64 gmElasticProperties::Perimeter() const
{
   return m_Properties.Perimeter();
}

Float64 gmElasticProperties::EI11() const
{
   return m_Properties.I11();
}

Float64 gmElasticProperties::EI22() const
{
   return m_Properties.I22();
}

Float64 gmElasticProperties::PrincipalDirection() const
{
   return m_Properties.PrincipalDirection();
}

Float64 gmElasticProperties::EI12Max() const
{
   return m_Properties.I12Max();
}

Float64 gmElasticProperties::EI12Min() const
{
   return m_Properties.I12Min();
}

void gmElasticProperties::SetCoordinateSystem(gmElasticProperties::CoordSystemType sys)
{
   gmProperties::CoordSystemType pct;
   switch(sys)
   {
      case Centroidal:
      {
         pct=gmProperties::Centroidal;
         break;
      }
      case Global:
      {
         pct=gmProperties::Global;
         break;
      }
      case Principal:
      {
         pct=gmProperties::Principal;
         break;
      }
      case UserDefined:
      {
         pct=gmProperties::UserDefined;
         break;
      }
      default:
         CHECKX(0,"Bad coordinate type");
   }

   m_Properties.SetCoordinateSystem(pct);
}

gmElasticProperties::CoordSystemType gmElasticProperties::GetCoordinateSystem() const
{
   gmElasticProperties::CoordSystemType epct=UserDefined;

   gmProperties::CoordSystemType pct = m_Properties.GetCoordinateSystem();
   switch(pct)
   {
      case gmProperties::Centroidal:
      {
         epct= Centroidal;
         break;
      }
      case gmProperties::Global:
      {
         epct= Global;
         break;
      }
      case gmProperties::Principal:
      {
         epct= Principal;
         break;
      }
      case gmProperties::UserDefined:
      {
         epct= UserDefined;
         break;
      }
      default:
         CHECKX(0,"Bad coordinate type");
   }

   return epct;
}

void gmElasticProperties::SetOrigin(const gpPoint2d& origin)
{
   m_Properties.SetOrigin(origin);
}

gpPoint2d gmElasticProperties::GetOrigin() const
{
   return m_Properties.GetOrigin();
}

void gmElasticProperties::SetOrientation(Float64 angle)
{
   m_Properties.SetOrientation(angle);
}

Float64 gmElasticProperties::GetOrientation() const
{
   return m_Properties.GetOrientation();
}

gmProperties gmElasticProperties::TransformProperties(Float64 E) const
{
   gmProperties props = m_Properties;
   props.SetArea( props.Area()/E );
   props.SetIxx( props.Ixx()/E );
   props.SetIxy( props.Ixy()/E );
   props.SetIyy( props.Iyy()/E );

   return props;
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool gmElasticProperties::AssertValid() const
{
   return true;
}

void gmElasticProperties::Dump(dbgDumpContext& os) const
{
   os << "Dump for gmElasticProperties" << endl;
   os << "Start Dump of implementation m_Properties:"<<endl;
   m_Properties.Dump(os);
   os << "End Dump of implementation m_Properties:"<<endl;
}

#endif // _DEBUG


////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void gmElasticProperties::MakeCopy(const gmElasticProperties& rOther)
{
   m_Properties   = rOther.m_Properties;
}

void gmElasticProperties::MakeAssignment(const gmElasticProperties& rOther)
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

bool GEOMMODELFUNC operator==(const gmElasticProperties& lhs, const gmElasticProperties& rhs)
{
   return lhs.m_Properties==rhs.m_Properties;
}

bool GEOMMODELFUNC operator!=(const gmElasticProperties& lhs, const gmElasticProperties& rhs)
{
   return !(lhs==rhs);
}

#if defined _UNITTEST
#include <Units\SysUnits.h>
bool gmElasticProperties::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("gmElasticProperties"); 

   // try a point area
      gmElasticProperties gpa(4., gpPoint2d(0,0), 0., 0., 0, 0,  0,  0, 0, 0);
      TRY_TESTME( gpa.GetCoordinateSystem() == gmElasticProperties::Centroidal ) ;
      TRY_TESTME( gpPoint2d(0,0) == gpa.Centroid() ) ;
      TRY_TESTME( IsZero(4-gpa.EA()) ) ;
      TRY_TESTME( IsZero(gpa.EI11()) ) ;
      TRY_TESTME( IsZero(gpa.EI22()) ) ;
      TRY_TESTME( IsZero(gpa.EIxy()) ) ;
      TRY_TESTME( IsZero(gpa.EI12Max()) ) ;
      TRY_TESTME( IsZero(gpa.EI12Min()) ) ;
      TRY_TESTME( IsZero(gpa.Ytop()) ) ;
      TRY_TESTME( IsZero(gpa.Ybottom()) ) ;
      TRY_TESTME( IsZero(gpa.Xright()) ) ;
      TRY_TESTME( IsZero(gpa.Xleft()) ) ;

      // move origin
      gpPoint2d orn(4,-2);
      gpa.SetOrigin(orn);
      TRY_TESTME( gpa.GetCoordinateSystem() == gmElasticProperties::UserDefined ) ;
      TRY_TESTME( gpPoint2d(-4,2) == gpa.Centroid() ) ;
      TRY_TESTME( IsZero(4-gpa.EA())) ;
      TRY_TESTME( IsZero( 63.43 - ::ConvertFromSysUnits(gpa.PrincipalDirection(), unitMeasure::Degree),.1)) ;
      TRY_TESTME( IsZero(16-gpa.EIxx())) ;
      TRY_TESTME( IsZero(64-gpa.EIyy())) ;
      TRY_TESTME( IsZero(32+gpa.EIxy())) ;
      TRY_TESTME( IsZero(80-gpa.EI11())) ;
      TRY_TESTME( IsZero(gpa.EI22())) ;
      TRY_TESTME( IsZero(40-gpa.EI12Max())) ;
      TRY_TESTME( IsZero(40+gpa.EI12Min())) ;
      TRY_TESTME( IsZero(gpa.Ytop())) ;
      TRY_TESTME( IsZero(gpa.Ybottom())) ;
      TRY_TESTME( IsZero(gpa.Xright())) ;
      TRY_TESTME( IsZero(gpa.Xleft())) ;

      // rotate 90 deg
      gpa.SetOrientation(M_PI/2);
      TRY_TESTME( gpa.GetCoordinateSystem() == gmElasticProperties::UserDefined) ;
      TRY_TESTME( gpPoint2d(2,4) == gpa.Centroid()) ;
      TRY_TESTME( IsZero(4-gpa.EA())) ;
      TRY_TESTME( IsZero(64-gpa.EIxx())) ;
      TRY_TESTME( IsZero(16-gpa.EIyy())) ;
      TRY_TESTME( IsZero(32-gpa.EIxy())) ;
      TRY_TESTME( IsZero(80.-gpa.EI11())) ;
      TRY_TESTME( IsZero(gpa.EI22())) ;
      TRY_TESTME( IsZero(40-gpa.EI12Max())) ;
      TRY_TESTME( IsZero(40+gpa.EI12Min())) ;

   // try a 2x4 rectangle
      gmElasticProperties gs2x4(8., gpPoint2d(0,0), 128./12., 32./12., 0, 2, -2, -1, 1, 0);
      TRY_TESTME( IsZero(8-gs2x4.EA())) ;
      TRY_TESTME( IsZero(128./12.-gs2x4.EI11())) ;
      TRY_TESTME( IsZero(32./12-gs2x4.EI22())) ;
      TRY_TESTME( IsZero(gs2x4.EIxy())) ;
      TRY_TESTME( IsZero(4-gs2x4.EI12Max())) ;
      TRY_TESTME( IsZero(4+gs2x4.EI12Min())) ;
      TRY_TESTME( IsZero(2-gs2x4.Ytop())) ;
      TRY_TESTME( IsZero(2+gs2x4.Ybottom())) ;
      TRY_TESTME( IsZero(1-gs2x4.Xright())) ;
      TRY_TESTME( IsZero(1+gs2x4.Xleft())) ;

      // move origin to user-defined location
      gs2x4.SetOrigin(orn); 
      TRY_TESTME( IsZero(8-gs2x4.EA())) ;
      TRY_TESTME( IsZero((128./12.+32)-gs2x4.EIxx())) ;
      TRY_TESTME( IsZero((32./12+128)-gs2x4.EIyy())) ;
      TRY_TESTME( IsZero(64+gs2x4.EIxy())) ;
      TRY_TESTME( IsZero( 62.25 - ::ConvertFromSysUnits(gs2x4.PrincipalDirection(),unitMeasure::Degree),.01)) ;
      TRY_TESTME( IsZero(77.67-gs2x4.EI12Max(),.01)) ;
      TRY_TESTME( IsZero(2-gs2x4.Ytop())) ;
      TRY_TESTME( IsZero(2+gs2x4.Ybottom())) ;
      TRY_TESTME( IsZero(1-gs2x4.Xright())) ;
      TRY_TESTME( IsZero(1+gs2x4.Xleft())) ;

   // move origin back to centroid
      gs2x4.SetCoordinateSystem(gmElasticProperties::Centroidal);
      TRY_TESTME( gs2x4.GetCoordinateSystem() == gmElasticProperties::Centroidal) ;
      TRY_TESTME( IsZero(8-gs2x4.EA())) ;
      TRY_TESTME( IsZero(128./12.-gs2x4.EI11())) ;
      TRY_TESTME( IsZero(32./12-gs2x4.EI22())) ;
      TRY_TESTME( IsZero(gs2x4.EIxy())) ;
      TRY_TESTME( IsZero(4-gs2x4.EI12Max())) ;
      TRY_TESTME( IsZero(4+gs2x4.EI12Min())) ;
      TRY_TESTME( IsZero(2-gs2x4.Ytop())) ;
      TRY_TESTME( IsZero(2+gs2x4.Ybottom())) ;
      TRY_TESTME( IsZero(1-gs2x4.Xright())) ;
      TRY_TESTME( IsZero(1+gs2x4.Xleft())) ;

   // try rotation to principal
      gmElasticProperties gsr(4., gpPoint2d(0,0), 16., 64., -32, 2, -2, -1, 1, 0);
      gsr.SetCoordinateSystem(gmElasticProperties::Principal);
      TRY_TESTME( gsr.GetCoordinateSystem() == gmElasticProperties::Principal) ;
      TRY_TESTME( IsZero(4-gsr.EA())) ;
      TRY_TESTME( IsZero(80.-gsr.EI11())) ;
      TRY_TESTME( IsZero(gsr.EI22())) ;
      TRY_TESTME( IsZero(gsr.EIxy())) ;
      TRY_TESTME( IsZero(40-gsr.EI12Max())) ;
      TRY_TESTME( IsZero(40+gsr.EI12Min())) ;

   // try addition and subraction
      gmElasticProperties gps1( 4., gpPoint2d( 4, 2), 0, 0, 0, 0, 0, 0, 0, 0);
      gmElasticProperties gps2( 4., gpPoint2d(-4,-2), 0, 0, 0, 0, 0, 0, 0, 0);
      gmElasticProperties gps4(-4., gpPoint2d(-4,-2), 0, 0, 0, 0, 0, 0, 0, 0);
      gmElasticProperties gps3 = gps1 + gps2;
      TRY_TESTME( IsZero(8-gps3.EA())) ;
      TRY_TESTME( IsZero(160.-gps3.EI11())) ;
      TRY_TESTME( IsZero(gps3.EI22())) ;
      TRY_TESTME( IsZero(32-gps3.EIxx())) ;
      TRY_TESTME( IsZero(128-gps3.EIyy())) ;
      TRY_TESTME( IsZero(64-gps3.EIxy())) ;

      gps3 = gps3 + gps4;
      gps3.SetXleft(0);
      gps3.SetXright(0);
      gps3.SetYtop(0);
      gps3.SetYbottom(0);
      TRY_TESTME ( gps3 == gps1 ) ;

   // take a dump
#if defined _DEBUG
      gsr.Dump(rlog.GetDumpCtx());
#endif

   TESTME_EPILOG("gmElasticProperties");
}

#endif // _UNITTEST



