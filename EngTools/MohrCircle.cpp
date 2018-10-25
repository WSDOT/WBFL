///////////////////////////////////////////////////////////////////////
// EngTools - Library of miscellaneous engineering tools
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

#include <EngTools\EngToolsLib.h>
#include <EngTools\MohrCircle.h>
#include <Units\SysUnits.h>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   etMohrCircle
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
etMohrCircle::etMohrCircle() :
m_Sii(0.0),
m_Sjj(0.0),
m_Sij(0.0)
{
   Init();
}

etMohrCircle::etMohrCircle(Float64 sii,Float64 sjj,Float64 sij) :
m_Sii(sii),
m_Sjj(sjj),
m_Sij(sij)
{
   Init();
}

etMohrCircle::etMohrCircle(const etMohrCircle& rOther)
{
   MakeCopy(rOther);
}

etMohrCircle::~etMohrCircle()
{
}

//======================== OPERATORS  =======================================
etMohrCircle& etMohrCircle::operator= (const etMohrCircle& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================
void etMohrCircle::ComputeState(Float64* pSii,Float64* pSjj, Float64* pSij,Float64 angle,bool bSysUnits)
{
   PRECONDITION( pSii != 0 && pSjj != 0 && pSij != 0 );

   Float64 angle2;
   if ( bSysUnits )
      angle2 = ::ConvertFromSysUnits( angle, unitMeasure::Radian );
   else
      angle2 = angle;

   // convert to circle system
   angle2 = 2*angle2 + m_Angle;

   // deal with wild-ass angles
   angle2 = fmod(angle2, 2*M_PI);

   Float64 c2 = cos( angle2 );
   Float64 s2 = sin( angle2 );

   *pSii = m_Center + m_Radius*c2;
   *pSjj = m_Center - m_Radius*c2;
   *pSij = m_Radius*s2;
}

//======================== ACCESS     =======================================
void etMohrCircle::SetSii(Float64 sii)
{
   m_Sii = sii;
   Init();
}

void etMohrCircle::SetSjj(Float64 sjj)
{
   m_Sjj = sjj;
   Init();
}

void etMohrCircle::SetSij(Float64 sij)
{
   m_Sij = sij;
   Init();
}

Float64 etMohrCircle::GetSmax() const
{
   return m_Smax;
}

Float64 etMohrCircle::GetSmin() const
{
   return m_Smin;
}

Float64 etMohrCircle::GetTmax() const
{
   return m_Radius;
}

Float64 etMohrCircle::GetPrincDirection(bool bSysUnits) const
{
   // internal principle angle is stored in clockwise direction and is
   // twice external angle - need to convert to counter-clockwise external.
   Float64 angle;
   angle = (2.*M_PI-m_Angle)/2.;

   // only return (-pi/2 <= angle <= pi/2)
   if (angle>M_PI/2.)
      angle -= M_PI;

   if ( bSysUnits )
   {
      // Convert from radians to system units
      angle = ::ConvertToSysUnits( angle, unitMeasure::Radian );
   }

    return angle;
}

Float64 etMohrCircle::GetCenter() const
{
	return m_Center;
}

Float64 etMohrCircle::GetRadius() const
{
	return m_Radius;
}

//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool etMohrCircle::AssertValid() const
{
   if ( m_Radius < 0 )
      return false;

   if ( !InRange( 0., m_Angle, 2*M_PI ) )
      return false;

   if ( !IsEqual( m_Smax - m_Smin, 2*m_Radius ) )
      return false;

   if ( m_Smax < m_Smin )
      return false;

   return true;
}

void etMohrCircle::Dump(dbgDumpContext& os) const
{
   os << "Dump for etMohrCircle" << endl;
}
#endif // _DEBUG

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void etMohrCircle::MakeCopy(const etMohrCircle& rOther)
{
   m_Smin   = rOther.m_Smin;
   m_Smax   = rOther.m_Smax;
   m_Angle  = rOther.m_Angle;
   m_Radius = rOther.m_Radius;
   m_Center = rOther.m_Center;
}

void etMohrCircle::MakeAssignment(const etMohrCircle& rOther)
{
   MakeCopy( rOther );
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void etMohrCircle::Init()
{
   // Compute principle values
   m_Radius = pow( (m_Sii - m_Sjj),2.)/4. + pow(m_Sij,2.);
   m_Radius = sqrt( m_Radius );

   m_Smin = (m_Sii + m_Sjj)/2. + m_Radius;
   m_Smax = (m_Sii + m_Sjj)/2. - m_Radius;

   if ( m_Smax < m_Smin )
   {
      Float64 temp = m_Smin;
      m_Smin = m_Smax;
      m_Smax = temp;
   }

   // Center of circle
   m_Center = (m_Smin + m_Smax)/2.;

   // Angle to principle plane
   if ( m_Radius == 0.0 )
   {
      m_Angle = 0.0;
   }
   else
   {
      // stored angle is in mohr's system (twice external angle and measured clockwise)
      m_Angle = atan2( 2*m_Sij, (m_Sii-m_Sjj) );
      if (m_Angle<0)
         m_Angle += 2*M_PI;
   }

   ASSERTVALID;
}

//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

#if defined _UNITTEST
#include <Units\AutoSysUnits.h>
bool etMohrCircle::TestMe()
{
   unitAutoSysUnits au;
   Float64 sii,sjj,sij;
   Float64 temp;

   etMohrCircle ct(64,16,-32);

   temp = ct.GetPrincDirection();
   if ( !IsEqual(ct.GetSmax(),80.,0.01) ||
        !IsEqual(ct.GetSmin(),0.,0.01) ||
        !IsEqual(ct.GetTmax(),40.,0.01) ||
        !IsEqual(temp,26.57,0.01) )
   {
      return false;
   }

   // should be able to get principals from princ angle
   ct.ComputeState(&sii,&sjj,&sij,temp,true);
   if ( !IsEqual( sii, 80.) ||
        !IsEqual( sjj, 0. ) ||
        !IsEqual( sij, 0. ) )
   {
      return false;
   }


   // Test 1
   // Example 1.1 pg 13 from Ugural and Fenster
   etMohrCircle c1(80,40,30);

   if ( !IsEqual(c1.GetSmax(),96.05,0.01) ||
        !IsEqual(c1.GetSmin(),23.95,0.01) ||
        !IsEqual(c1.GetTmax(),36.05,0.01) ||
        !IsEqual(c1.GetPrincDirection(),-28.15,0.01) )
   {
      return false;
   }

   // Test 2
   // Example 1.2 pg 15 from Ugural and Fenster
   etMohrCircle c2(-14,28,0);

   c2.ComputeState(&sii,&sjj,&sij,30.,true);
   if ( !IsEqual( sii, -3.5, 0.1 ) ||
        !IsEqual( sjj, 17.5, 0.1 ) ||
        !IsEqual( sij, -18.186, 0.001) )
   {
      return false;
   }

   // Test 2
   // Problem 1.3 pg 27 from Ugural and Fenster
   etMohrCircle c3(100,-50,-60);

   if ( !IsEqual(c3.GetSmax(),121.0,0.1) ||
        !IsEqual(c3.GetSmin(),-71.0,0.1) ||
        !IsEqual(c3.GetTmax(), 96.0,0.1) ||
        !IsEqual(c3.GetPrincDirection(),19.33,0.1) )
   {
      return false;
   }

   etMohrCircle c4(150,0,100);

   if ( !IsEqual(c4.GetSmax(),200.0,0.1) ||
        !IsEqual(c4.GetSmin(),-50.0,0.1) ||
        !IsEqual(c4.GetTmax(),125.0,0.1) ||
        !IsEqual(c4.GetPrincDirection(),-26.57,0.1) )
   {
      return false;
   }

   // From "Statics", Merriam, Pge 373
   etMohrCircle c5(18.167,10.167,-7.5);
   if ( !IsEqual(c5.GetSmax(),22.67,0.1) ||
        !IsEqual(c5.GetSmin(), 5.67,0.1) ||
        !IsEqual(c5.GetPrincDirection(),30.96,0.01) )
   {
      return false;
   }

   // From Beer & Johnston, Mechanics of Materials, page 306
   etMohrCircle c6(100,60,48);
   if ( !IsEqual(c6.GetSmax(),132.,0.1) ||
        !IsEqual(c6.GetSmin(), 28.,0.1) ||
        !IsEqual(c6.GetPrincDirection(),-33.7,0.1) )
   {
      return false;
   }

   c6.ComputeState(&sii,&sjj,&sij,30.,true);
   if ( !IsEqual( sii, 48.4, 0.1 ) ||
        !IsEqual( sjj, 111.6, 0.1 ) ||
        !IsEqual( sij, 41.3, 0.01) )
   {
      return false;
   }

   etMohrCircle c7(50,-10,40);
   if ( !IsEqual(c7.GetSmax(),70.,0.1) ||
        !IsEqual(c7.GetSmin(), -30.,0.1) ||
        !IsEqual(c7.GetPrincDirection(),-26.56,0.1) )
   {
      return false;
   }

   etMohrCircle c8(4.18, 3.25, 2.87);
   if ( !IsEqual(c8.GetSmax(),6.63,0.1) ||
        !IsEqual(c8.GetSmin(),0.81,0.1) ||
        !IsEqual(c8.GetPrincDirection(),-40.4,0.1) )
   {
      return false;
   }

   return true;
}
#endif // _UNITTEST


