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

#include <GeomModel\GeomModelLib.h>
#include <GeomModel\Properties.h>

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
   gmProperties
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
gmProperties::gmProperties():
m_Area(0),
m_Centroid(0,0),
m_Ixx(0),
m_Iyy(0),
m_Ixy(0),
m_Perimeter(0),
m_CurrIxx(0),
m_CurrIyy(0),
m_CurrIxy(0),
m_CoordType(Centroidal),
m_Origin(0,0),
m_Orientation(0)
{
}

gmProperties::gmProperties(Float64 area,
                           const gpPoint2d& centroid,
                           Float64 ixx, Float64 iyy, Float64 ixy,
                           Float64 yTop, Float64 yBottom,
                           Float64 xLeft, Float64 xRight,
                           Float64 perimeter):
m_Area(area),
m_Centroid(centroid),
m_Ixx(ixx),
m_Iyy(iyy),
m_Ixy(ixy),
m_Box(xLeft, yBottom, xRight, yTop),
m_Perimeter(perimeter),
m_CoordType(Centroidal),
m_Origin(centroid),
m_Orientation(0)
{
   UpdateOrientation();
}



gmProperties::gmProperties(const gmProperties& rOther)
{
   MakeCopy(rOther);
}

gmProperties::~gmProperties()
{
}

//======================== OPERATORS  =======================================
gmProperties& gmProperties::operator= (const gmProperties& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

gmProperties gmProperties::operator+ (const gmProperties& rhs) const
{
   gmProperties tmp(*this);
   return tmp+=rhs;
}


gmProperties& gmProperties::operator+= (const gmProperties& rhs)
{
   Float64 ixx=0, iyy=0, ixy = 0; // about global axes
   Float64 mxx=0, myy = 0;        // first moments

   mxx = m_Area * m_Centroid.Y() + rhs.m_Area * rhs.m_Centroid.Y();
   myy = m_Area * m_Centroid.X() + rhs.m_Area * rhs.m_Centroid.X();

   // Get centriodal I for each shape and transform it to the global axes
   ixx = (     m_Ixx +     m_Area *     m_Centroid.Y()*    m_Centroid.Y() + 
           rhs.m_Ixx + rhs.m_Area * rhs.m_Centroid.Y()*rhs.m_Centroid.Y());

   iyy = (     m_Iyy +     m_Area *     m_Centroid.X()*    m_Centroid.X() + 
           rhs.m_Iyy + rhs.m_Area * rhs.m_Centroid.X()*rhs.m_Centroid.X());

   ixy = (     m_Ixy +     m_Area *     m_Centroid.X()*    m_Centroid.Y() + 
           rhs.m_Ixy + rhs.m_Area * rhs.m_Centroid.X()*rhs.m_Centroid.Y());

   m_Area += rhs.m_Area;

   // find union of two bounds in global space - will move into centroid space
   // after centroid of composite is determined
   gpRect2d rr = rhs.m_Box.Normalized();
   gpRect2d mm = m_Box.Normalized();
   rr.Offset(rhs.m_Centroid.X(), rhs.m_Centroid.Y());
   mm.Offset(    m_Centroid.X(),     m_Centroid.Y());
   rr.Union(mm);

   m_Centroid.Y() = mxx / m_Area;
   m_Centroid.X() = myy / m_Area;

   m_Ixx = ixx - m_Area * m_Centroid.Y() * m_Centroid.Y();
   m_Iyy = iyy - m_Area * m_Centroid.X() * m_Centroid.X();
   m_Ixy = ixy - m_Area * m_Centroid.X() * m_Centroid.Y();

   // move bounding box from global to centoidal coord's
   m_Box = rr.OffsetBy(-(m_Centroid.X()),-(m_Centroid.Y()));

   // Perimeter
#pragma Reminder("Perimeter - This doesn't make sense")
   m_Perimeter += rhs.m_Perimeter;
 
   UpdateOrientation();
   return *this;
}




//======================== OPERATIONS =======================================

Float64 gmProperties::SetArea(Float64 area)
{
   Float64 tmp = m_Area;
   m_Area = area;
   return tmp;
}

gpPoint2d gmProperties::SetCentroid(gpPoint2d cent)
{
   gpPoint2d tmp = m_Centroid;
   m_Centroid = cent;
   UpdateOrientation();
   return tmp;
}

Float64 gmProperties::SetIxx(Float64 ixx)
{
   Float64 tmp = m_Ixx;
   m_Ixx = ixx;
   UpdateOrientation();
   return tmp;
}

Float64 gmProperties::SetIyy(Float64 iyy)
{
   Float64 tmp = m_Iyy;
   m_Iyy = iyy;
   UpdateOrientation();
   return tmp;
}

Float64 gmProperties::SetIxy(Float64 ixy)
{
   Float64 tmp = m_Ixy;
   m_Ixy = ixy;
   UpdateOrientation();
   return tmp;
}

Float64 gmProperties::SetYtop(Float64 ytop)
{
   Float64 tmp = m_Box.Top();
   m_Box.Top() = ytop;
   return tmp;
}

Float64 gmProperties::SetYbottom(Float64 ybot)
{
   Float64 tmp = m_Box.Bottom();
   m_Box.Bottom() = ybot;
   return tmp;
}

Float64 gmProperties::SetXleft(Float64 xleft)
{
   Float64 tmp = m_Box.Left();
   m_Box.Left() = xleft;
   return tmp;
}

Float64 gmProperties::SetXright(Float64 xright)
{
   Float64 tmp = m_Box.Right();
   m_Box.Right() = xright;
   return tmp;
}

Float64 gmProperties::SetPerimeter(Float64 p)
{
   Float64 tmp = m_Perimeter;
   m_Perimeter = p;
   return tmp;
}

Float64 gmProperties::Area() const
{
   return m_Area;
}


gpPoint2d gmProperties::Centroid() const
{
   return m_CurrCentroid;
}

Float64 gmProperties::Ixx() const
{
   return m_CurrIxx;
}

Float64 gmProperties::Iyy() const
{
   return m_CurrIyy;
}

Float64 gmProperties::Ixy() const
{
   return m_CurrIxy;
}

Float64 gmProperties::Ytop() const
{
   return m_Box.Top();
}

Float64 gmProperties::Ybottom() const
{
   return m_Box.Bottom();
}

Float64 gmProperties::Xleft() const
{
   return m_Box.Left();
}

Float64 gmProperties::Xright() const
{
   return m_Box.Right();
}

Float64 gmProperties::Perimeter() const
{
   return m_Perimeter;
}

Float64 gmProperties::I11() const
{
   etMohrCircle ms(m_CurrIxx, m_CurrIyy, m_CurrIxy);
   Float64 ixx, iyy, ixy, angle;
   angle = ms.GetPrincDirection(false);
   ms.ComputeState(&ixx,&iyy,&ixy,angle,false);
   return ixx;
}

Float64 gmProperties::I22() const
{
   etMohrCircle ms(m_CurrIxx, m_CurrIyy, m_CurrIxy);
   Float64 ixx, iyy, ixy, angle;
   angle = ms.GetPrincDirection(false);
   ms.ComputeState(&ixx,&iyy,&ixy,angle,false);
   return iyy;
}

Float64 gmProperties::PrincipalDirection() const
{
   etMohrCircle ms(m_CurrIxx, m_CurrIyy, m_CurrIxy);
   return ms.GetPrincDirection();
}

Float64 gmProperties::I12Max() const
{
   etMohrCircle ms(m_CurrIxx, m_CurrIyy, m_CurrIxy);
   return ms.GetTmax();
}

Float64 gmProperties::I12Min() const
{
   etMohrCircle ms(m_CurrIxx, m_CurrIyy, m_CurrIxy);
   return -ms.GetTmax();
}

void gmProperties::SetCoordinateSystem(gmProperties::CoordSystemType sys)
{
   switch(sys)
   {
      case Centroidal:
      {
         m_CoordType = sys;
         m_Origin = m_Centroid;
         m_Orientation = 0;
         UpdateOrientation();
         break;
      }
      case Global:
      {
         m_CoordType = sys;
         m_Origin = gpPoint2d(0,0);
         m_Orientation = 0;
         UpdateOrientation();
         break;
      }
      case Principal:
      {
         // first have to get principal orientation angle
         SetCoordinateSystem(Centroidal);
         m_Orientation = PrincipalDirection();
         m_CoordType = sys;
         UpdateOrientation();
         break;
      }
      case UserDefined:
      {
         m_CoordType = sys;
         break;
      }
      default:
         CHECKX(0,_T("Bad coordinate type"));
   }
}

gmProperties::CoordSystemType gmProperties::GetCoordinateSystem() const
{
   return m_CoordType;
}

void gmProperties::SetOrigin(const gpPoint2d& origin)
{
      m_CoordType = UserDefined;
      m_Origin = origin;
      UpdateOrientation();
}

gpPoint2d gmProperties::GetOrigin() const
{
   return m_Origin;
}

void gmProperties::SetOrientation(Float64 angle)
{
      m_CoordType = UserDefined;
      m_Orientation = angle;
      UpdateOrientation();
}

Float64 gmProperties::GetOrientation() const
{
   return m_Orientation;
}




//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool gmProperties::AssertValid() const
{
   return true;
}

void gmProperties::Dump(dbgDumpContext& os) const
{
   os << _T("Dump for gmProperties") << endl;
   os << _T("   m_Area         = ")<< m_Area <<endl;
   os << _T("   m_Centroid     = (")<< m_Centroid.X()<<_T(", ")<<m_Centroid.Y()<<_T(")")<<endl;
   os << _T("   m_Ixx          = ")<< m_Ixx <<endl;         
   os << _T("   m_Iyy          = ")<< m_Iyy <<endl;          
   os << _T("   m_Ixy          = ")<< m_Ixy <<endl;         
   os << _T("   m_Box.Top      = ")<< m_Box.Top() <<endl;        
   os << _T("   m_Box.Bottom   = ")<< m_Box.Bottom() <<endl;     
   os << _T("   m_Box.Left     = ")<< m_Box.Left() <<endl;       
   os << _T("   m_Box.Right    = ")<< m_Box.Right() <<endl;      
   os << _T("   m_CoordType    = ")<< (int)m_CoordType <<endl;   
   os << _T("   m_Origin       = (")<<m_Origin.X()<<_T(", ")<<m_Origin.Y()<<_T(")") <<endl;
   os << _T("   m_Orientation  = ")<< m_Orientation <<endl;
   os << _T("   m_CurrCentroid = (")<< m_CurrCentroid.X()<<_T(", ")<<m_CurrCentroid.Y()<<_T(")")<<endl;
   os << _T("   m_CurrIxx      = ")<< m_CurrIxx <<endl;
   os << _T("   m_CurrIyy      = ")<< m_CurrIyy <<endl;
   os << _T("   m_CurrIxy      = ")<< m_CurrIxy <<endl;
}

#endif // _DEBUG


////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void gmProperties::MakeCopy(const gmProperties& rOther)
{
   m_Area         = rOther.m_Area;
   m_Centroid     = rOther.m_Centroid;
   m_Ixx          = rOther.m_Ixx;
   m_Iyy          = rOther.m_Iyy;
   m_Ixy          = rOther.m_Ixy;
   m_Box          = rOther.m_Box;
   m_Perimeter    = rOther.m_Perimeter;

   m_CoordType    = rOther.m_CoordType;
   m_Origin       = rOther.m_Origin;
   m_Orientation  = rOther.m_Orientation;

   m_CurrCentroid = rOther.m_CurrCentroid;
   m_CurrIxx      = rOther.m_CurrIxx;
   m_CurrIyy      = rOther.m_CurrIyy;
   m_CurrIxy      = rOther.m_CurrIxy;
}

void gmProperties::MakeAssignment(const gmProperties& rOther)
{
   MakeCopy( rOther );
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================


void gmProperties::UpdateOrientation()
{
   switch (m_CoordType)
   {
   case (Centroidal):
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
         etMohrCircle ms(m_Ixx, m_Iyy, m_Ixy);
         ms.ComputeState(&ixx, &iyy, &ixy, m_Orientation);

         // next need to transform into origin coord's
         gpPoint2d delta( m_Centroid.X() - m_Origin.X(), m_Centroid.Y() - m_Origin.Y());
         delta.Rotate(gpPoint2d(0,0), -m_Orientation);

         Float64 dx = delta.X();
         Float64 dy = delta.Y();

         // use principal axis theorem to put properties into new system
         m_CurrCentroid = delta;
         m_CurrIxx      = ixx + m_Area * dy * dy;
         m_CurrIyy      = iyy + m_Area * dx * dx;
         m_CurrIxy      = ixy + m_Area * dx * dy;
         break;
      }
   }
}
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

bool GEOMMODELFUNC operator==(const gmProperties& lhs, const gmProperties& rhs)
{
   return IsEqual(lhs.Area(), rhs.Area())         &&
          lhs.Centroid()  == rhs.Centroid()       &&
          IsEqual(lhs.Ixx(),       rhs.Ixx())     &&
          IsEqual(lhs.Iyy(),       rhs.Iyy())     &&
          IsEqual(lhs.Ixy(),       rhs.Ixy())     &&
          IsEqual(lhs.Xleft(),     rhs.Xleft())   &&
          IsEqual(lhs.Xright(),    rhs.Xright())  &&
          IsEqual(lhs.Ytop(),      rhs.Ytop())    &&
          IsEqual(lhs.Ybottom(),   rhs.Ybottom()) &&
          IsEqual(lhs.Perimeter(), rhs.Perimeter());
}

bool GEOMMODELFUNC operator!=(const gmProperties& lhs, const gmProperties& rhs)
{
   return !(lhs==rhs);
}


#if defined _UNITTEST
#include <Units\SysUnits.h>

bool Test_AddOperator1(dbgLog& rlog)
{
   // Test the addition of properties when both properties objects are in
   // centroidal coordinates
   TESTME_PROLOGUE( "gmProperties - Test_AddOperator1" );

   gmProperties shape1(10,gpPoint2d(10,10),10,10,10,10,-10,-10,10,0);
   gmProperties shape2(20,gpPoint2d(20,20),20,20,20,20,-20,-20,20,0);

   gmProperties shape3 = shape1 + shape2;

   TRY_TESTME( IsEqual(shape3.Area(), 30.) );
   TRY_TESTME( IsEqual(shape3.Ixx(), 696.6666666666) );
   TRY_TESTME( IsEqual(shape3.Iyy(), 696.6666666666) );
   TRY_TESTME( IsEqual(shape3.Ixy(), 696.6666666666) );
   TRY_TESTME( gpPoint2d(16.666666666666,16.6666666666666) == shape3.Centroid() );
   TRY_TESTME( IsEqual(shape3.Xleft(), -16.666666666666666) );
   TRY_TESTME( IsEqual(shape3.Xright(), 23.333333333333333) );
   TRY_TESTME( IsEqual(shape3.Ybottom(), -16.666666666666666) );
   TRY_TESTME( IsEqual(shape3.Ytop(), 23.333333333333333) );

   TESTME_EPILOG( "gmProperties - Test_AddOperator1" );
}

bool Test_AddOperator2(dbgLog& rlog)
{
   // Test the addition of properties when one property object is in centroidal
   // coordinates and one is in global coordaintes
   TESTME_PROLOGUE( "gmProperties - Test_AddOperator2" );

   gmProperties shape1(10,gpPoint2d(10,10),10,10,10,10,-10,-10,10,0);
   gmProperties shape2(20,gpPoint2d(20,20),20,20,20,20,-20,-20,20,0);
   shape2.SetCoordinateSystem( gmProperties::Global );

   TRY_TESTME( IsEqual(shape2.Area(), 20.) );
   TRY_TESTME( IsEqual(shape2.Ixx(), 8020. ) );
   TRY_TESTME( IsEqual(shape2.Iyy(), 8020. ) );
   TRY_TESTME( IsEqual(shape2.Ixy(), 8020. ) );
   TRY_TESTME( gpPoint2d(20,20) == shape2.Centroid() );
   TRY_TESTME( IsEqual( shape2.Xleft(),   -20. ) );
   TRY_TESTME( IsEqual( shape2.Xright(),   20. ) );
   TRY_TESTME( IsEqual( shape2.Ybottom(), -20. ) );
   TRY_TESTME( IsEqual( shape2.Ytop(),     20. ) );

   gmProperties shape3 = shape1 + shape2;

   TRY_TESTME( IsEqual(shape3.Area(), 30.) );
   TRY_TESTME( IsEqual(shape3.Ixx(), 696.6666666666) );
   TRY_TESTME( IsEqual(shape3.Iyy(), 696.6666666666) );
   TRY_TESTME( IsEqual(shape3.Ixy(), 696.6666666666) );
   TRY_TESTME( gpPoint2d(16.666666666666,16.6666666666666) == shape3.Centroid() );
   TRY_TESTME( IsEqual(shape3.Xleft(), -16.666666666666666) );
   TRY_TESTME( IsEqual(shape3.Xright(), 23.333333333333333) );
   TRY_TESTME( IsEqual(shape3.Ybottom(), -16.666666666666666) );
   TRY_TESTME( IsEqual(shape3.Ytop(), 23.333333333333333) );

   TESTME_EPILOG( "gmProperties - Test_AddOperator2" );
}

bool Test_Assignment1(dbgLog& rlog)
{
   TESTME_PROLOGUE( "gmProperties - Test_Assignment1" );

   // Test the mutators and accessor when property object is in centrodial units
   // This is just a raw test to make sure we get back what we put in.
   // This test makes no assumptions about the correctness of the section properties!!!
   gmProperties shape;

   shape.SetArea(10);
   TRY_TESTME( IsEqual( shape.Area(), 10. ) );

   shape.SetCentroid( gpPoint2d(10,10) );
   TRY_TESTME( gpPoint2d(10,10) == shape.Centroid() );

   shape.SetIxx( 10 );
   TRY_TESTME( IsEqual( shape.Ixx(), 10. ) );

   shape.SetIyy( 10 );
   TRY_TESTME( IsEqual( shape.Iyy(), 10. ) );

   shape.SetIxy( 10 );
   TRY_TESTME( IsEqual( shape.Ixy(), 10. ) );

   shape.SetOrigin( gpPoint2d(10,10) );
   TRY_TESTME( gpPoint2d(10,10) == shape.GetOrigin() );

   shape.SetOrientation( 0.5 );
   TRY_TESTME( IsEqual( shape.GetOrientation(), 0.5 ) );

   shape.SetXleft(10);
   TRY_TESTME( IsEqual( shape.Xleft(), 10. ) );

   shape.SetXright(10);
   TRY_TESTME( IsEqual( shape.Xright(), 10. ) );

   shape.SetYtop(10);
   TRY_TESTME( IsEqual( shape.Ytop(), 10. ) );
   
   shape.SetYbottom(10);
   TRY_TESTME( IsEqual( shape.Ybottom(), 10. ) );
   
   TESTME_EPILOG( "gmProperties - Test_Assignment1" );
}

bool Test_Assignment2(dbgLog& rlog)
{
   TESTME_PROLOGUE( "gmProperties - Test_Assignment2" );

   // Test the mutators and accessor when property object is in centrodial units
   // This test verifies section properties remain correct.
   gmProperties shape(10,gpPoint2d(10,10),10,10,10,10,-10,-10,10,0);

   shape.SetCentroid( gpPoint2d(20,20) );
   TRY_TESTME( gpPoint2d(20,20) == shape.Centroid() );
   TRY_TESTME( IsEqual( shape.Area(), 10. ) );
   TRY_TESTME( IsEqual( shape.Ixx(), 10. ) );
   TRY_TESTME( IsEqual( shape.Iyy(), 10. ) );
   TRY_TESTME( IsEqual( shape.Ixy(), 10. ) );

   shape.SetIxx( 20 );
   TRY_TESTME( gpPoint2d(20,20) == shape.Centroid() );
   TRY_TESTME( IsEqual( shape.Area(), 10. ) );
   TRY_TESTME( IsEqual( shape.Ixx(), 20. ) );
   TRY_TESTME( IsEqual( shape.Iyy(), 10. ) );
   TRY_TESTME( IsEqual( shape.Ixy(), 10. ) );

   shape.SetIyy( 20 );
   TRY_TESTME( gpPoint2d(20,20) == shape.Centroid() );
   TRY_TESTME( IsEqual( shape.Area(), 10. ) );
   TRY_TESTME( IsEqual( shape.Ixx(), 20. ) );
   TRY_TESTME( IsEqual( shape.Iyy(), 20. ) );
   TRY_TESTME( IsEqual( shape.Ixy(), 10. ) );

   shape.SetIxy( 20 );
   TRY_TESTME( gpPoint2d(20,20) == shape.Centroid() );
   TRY_TESTME( IsEqual( shape.Area(), 10. ) );
   TRY_TESTME( IsEqual( shape.Ixx(), 20. ) );
   TRY_TESTME( IsEqual( shape.Iyy(), 20. ) );
   TRY_TESTME( IsEqual( shape.Ixy(), 20. ) );
   
   TESTME_EPILOG( "gmProperties - Test_Assignment2" );
}

bool gmProperties::TestMe(dbgLog& rlog)
{
      TESTME_PROLOGUE("gmProperties");
// try a point area
      gmProperties gpa(4., gpPoint2d(0,0), 0., 0., 0, 0,  0,  0, 0, 0);
      TRY_TESTME(gpa.GetCoordinateSystem() == gmProperties::Centroidal) ;
      TRY_TESTME(gpPoint2d(0,0) == gpa.Centroid()) ;
      TRY_TESTME( IsZero(4-gpa.Area())) ;
      TRY_TESTME( IsZero(gpa.I11())) ;
      TRY_TESTME( IsZero(gpa.I22())) ;
      TRY_TESTME( IsZero(gpa.Ixy())) ;
      TRY_TESTME( IsZero(gpa.I12Max())) ;
      TRY_TESTME( IsZero(gpa.I12Min())) ;
      TRY_TESTME( IsZero(gpa.Ytop())) ;
      TRY_TESTME( IsZero(gpa.Ybottom())) ;
      TRY_TESTME( IsZero(gpa.Xright())) ;
      TRY_TESTME( IsZero(gpa.Xleft())) ;

      // move origin
      gpPoint2d orn(4,-2);
      gpa.SetOrigin(orn);
      TRY_TESTME( gpa.GetCoordinateSystem() == gmProperties::UserDefined) ;
      TRY_TESTME( gpPoint2d(-4,2) == gpa.Centroid()) ;
      TRY_TESTME( IsZero(4-gpa.Area())) ;
      TRY_TESTME( IsZero( 63.43 - ::ConvertFromSysUnits( gpa.PrincipalDirection(), unitMeasure::Degree ),.1)) ;
      TRY_TESTME( IsZero(16-gpa.Ixx())) ;
      TRY_TESTME( IsZero(64-gpa.Iyy())) ;
      TRY_TESTME( IsZero(32+gpa.Ixy())) ;
      TRY_TESTME( IsZero(80-gpa.I11())) ;
      TRY_TESTME( IsZero(gpa.I22())) ;
      TRY_TESTME( IsZero(40-gpa.I12Max())) ;
      TRY_TESTME( IsZero(40+gpa.I12Min())) ;
      TRY_TESTME( IsZero(gpa.Ytop())) ;
      TRY_TESTME( IsZero(gpa.Ybottom())) ;
      TRY_TESTME( IsZero(gpa.Xright())) ;
      TRY_TESTME( IsZero(gpa.Xleft())) ;

      // rotate 90 deg
      gpa.SetOrientation(M_PI/2);
      TRY_TESTME( gpa.GetCoordinateSystem() == gmProperties::UserDefined) ;
      TRY_TESTME( gpPoint2d(2,4) == gpa.Centroid()) ;
      TRY_TESTME( IsZero(4-gpa.Area())) ;
      TRY_TESTME( IsZero(64-gpa.Ixx())) ;
      TRY_TESTME( IsZero(16-gpa.Iyy())) ;
      TRY_TESTME( IsZero(32-gpa.Ixy())) ;
      TRY_TESTME( IsZero(80.-gpa.I11())) ;
      TRY_TESTME( IsZero(gpa.I22())) ;
      TRY_TESTME( IsZero(40-gpa.I12Max())) ;
      TRY_TESTME( IsZero(40+gpa.I12Min())) ;

   // try a 2x4 rectangle
      gmProperties gs2x4(8., gpPoint2d(0,0), 128./12., 32./12., 0, 2, -2, -1, 1, 0);
      TRY_TESTME( IsZero(8-gs2x4.Area())) ;
      TRY_TESTME( IsZero(128./12.-gs2x4.I11())) ;
      TRY_TESTME( IsZero(32./12-gs2x4.I22())) ;
      TRY_TESTME( IsZero(gs2x4.Ixy())) ;
      TRY_TESTME( IsZero(4-gs2x4.I12Max())) ;
      TRY_TESTME( IsZero(4+gs2x4.I12Min())) ;
      TRY_TESTME( IsZero(2-gs2x4.Ytop())) ;
      TRY_TESTME( IsZero(2+gs2x4.Ybottom())) ;
      TRY_TESTME( IsZero(1-gs2x4.Xright())) ;
      TRY_TESTME( IsZero(1+gs2x4.Xleft())) ;

      // move origin to user-defined location
      gs2x4.SetOrigin(orn); 
      TRY_TESTME( IsZero(8-gs2x4.Area())) ;
      TRY_TESTME( IsZero((128./12.+32)-gs2x4.Ixx())) ;
      TRY_TESTME( IsZero((32./12+128)-gs2x4.Iyy())) ;
      TRY_TESTME( IsZero(64+gs2x4.Ixy())) ;
      TRY_TESTME( IsZero(62.25 - ::ConvertFromSysUnits( gs2x4.PrincipalDirection(), unitMeasure::Degree ),.01)) ;
      TRY_TESTME( IsZero(77.67-gs2x4.I12Max(),.01)) ;
      TRY_TESTME( IsZero(2-gs2x4.Ytop())) ;
      TRY_TESTME( IsZero(2+gs2x4.Ybottom())) ;
      TRY_TESTME( IsZero(1-gs2x4.Xright())) ;
      TRY_TESTME( IsZero(1+gs2x4.Xleft())) ;

   // move origin back to centroid
      gs2x4.SetCoordinateSystem(gmProperties::Centroidal);
      TRY_TESTME( gs2x4.GetCoordinateSystem() == gmProperties::Centroidal) ;
      TRY_TESTME( gpPoint2d(0,0) == gs2x4.GetOrigin() );
      TRY_TESTME( IsZero(8-gs2x4.Area())) ;
      TRY_TESTME( IsZero(128./12.-gs2x4.I11())) ;
      TRY_TESTME( IsZero(32./12-gs2x4.I22())) ;
      TRY_TESTME( IsZero(gs2x4.Ixy())) ;
      TRY_TESTME( IsZero(4-gs2x4.I12Max())) ;
      TRY_TESTME( IsZero(4+gs2x4.I12Min())) ;
      TRY_TESTME( IsZero(2-gs2x4.Ytop())) ;
      TRY_TESTME( IsZero(2+gs2x4.Ybottom())) ;
      TRY_TESTME( IsZero(1-gs2x4.Xright())) ;
      TRY_TESTME( IsZero(1+gs2x4.Xleft())) ;

   // try rotation to principal
      gmProperties gsr(4., gpPoint2d(0,0), 16., 64., -32, 2, -2, -1, 1, 0);
      gsr.SetCoordinateSystem(gmProperties::Principal);
      TRY_TESTME( gsr.GetCoordinateSystem() == gmProperties::Principal) ;
      TRY_TESTME( IsZero(4-gsr.Area())) ;
      TRY_TESTME( IsZero(80.-gsr.I11())) ;
      TRY_TESTME( IsZero(gsr.I22())) ;
      TRY_TESTME( IsZero(gsr.Ixy())) ;
      TRY_TESTME( IsZero(40-gsr.I12Max())) ;
      TRY_TESTME( IsZero(40+gsr.I12Min())) ;

   // try addition and subraction
      gmProperties gps1( 4., gpPoint2d( 4, 2), 0, 0, 0, 0, 0, 0, 0, 0);
      gmProperties gps2( 4., gpPoint2d(-4,-2), 0, 0, 0, 0, 0, 0, 0, 0);
      gmProperties gps4(-4., gpPoint2d(-4,-2), 0, 0, 0, 0, 0, 0, 0, 0);
      gmProperties gps3 = gps1 + gps2;
      TRY_TESTME( IsZero(8-gps3.Area())) ;
      TRY_TESTME( IsZero(160.-gps3.I11())) ;
      TRY_TESTME( IsZero(gps3.I22())) ;
      TRY_TESTME( IsZero(32-gps3.Ixx())) ;
      TRY_TESTME( IsZero(128-gps3.Iyy())) ;
      TRY_TESTME( IsZero(64-gps3.Ixy())) ;

      gps3 = gps3 + gps4;
      gps3.SetXleft(0);
      gps3.SetXright(0);
      gps3.SetYtop(0);
      gps3.SetYbottom(0);
      TRY_TESTME (gps3 == gps1) ;

   // take a dump
#if defined _DEBUG
      gsr.Dump(rlog.GetDumpCtx());
#endif

      TRY_TESTME( Test_AddOperator1(rlog) );
      TRY_TESTME( Test_AddOperator2(rlog) );
      TRY_TESTME( Test_Assignment1(rlog) );
      TRY_TESTME( Test_Assignment2(rlog) );

      TESTME_EPILOG("gmProperties");
}

#endif // _UNITTEST


