///////////////////////////////////////////////////////////////////////
// EngTools - Library of miscellaneous engineering tools
// Copyright © 1999-2025  Washington State Department of Transportation
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
#include <Units\Convert.h>

using namespace WBFL::EngTools;

MohrCircle::MohrCircle() :
m_Sii(0.0),
m_Sjj(0.0),
m_Sij(0.0)
{
   Init();
}

MohrCircle::MohrCircle(Float64 sii,Float64 sjj,Float64 sij) :
m_Sii(sii),
m_Sjj(sjj),
m_Sij(sij)
{
   Init();
}

void MohrCircle::SetStresses(Float64 sii, Float64 sjj, Float64 sij)
{
   m_Sii = sii;
   m_Sjj = sjj;
   m_Sij = sij;
   Init();
}

void MohrCircle::ComputeState(Float64* pSii,Float64* pSjj, Float64* pSij,Float64 angle,bool bSysUnits)
{
   PRECONDITION( pSii != nullptr && pSjj != nullptr && pSij != nullptr );

   Float64 angle2;
   if ( bSysUnits )
      angle2 = WBFL::Units::ConvertFromSysUnits( angle, WBFL::Units::Measure::Radian );
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

void MohrCircle::SetSii(Float64 sii)
{
   m_Sii = sii;
   Init();
}

void MohrCircle::SetSjj(Float64 sjj)
{
   m_Sjj = sjj;
   Init();
}

void MohrCircle::SetSij(Float64 sij)
{
   m_Sij = sij;
   Init();
}

Float64 MohrCircle::GetSmax() const
{
   return m_Smax;
}

Float64 MohrCircle::GetSmin() const
{
   return m_Smin;
}

Float64 MohrCircle::GetTmax() const
{
   return m_Radius;
}

Float64 MohrCircle::GetPrincipalDirection(bool bSysUnits) const
{
   // internal principle angle is stored in clockwise direction and is
   // twice external angle - need to convert to counter-clockwise external.
   Float64 angle;
   angle = (2.*M_PI-m_Angle)/2.;

   // only return (-pi/2 <= angle <= pi/2)
   if (PI_OVER_2 < angle)
      angle -= M_PI;

   if ( bSysUnits )
   {
      // Convert from radians to system units
      angle = WBFL::Units::ConvertToSysUnits( angle, WBFL::Units::Measure::Radian );
   }

    return angle;
}

Float64 MohrCircle::GetCenter() const
{
	return m_Center;
}

Float64 MohrCircle::GetRadius() const
{
	return m_Radius;
}

void MohrCircle::Init()
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
      // stored angle is in Mohr's system (twice external angle and measured clockwise)
      m_Angle = atan2( 2*m_Sij, (m_Sii-m_Sjj) );
      if (m_Angle<0)
         m_Angle += 2*M_PI;
   }

   ASSERTVALID;
}

#if defined _DEBUG
bool MohrCircle::AssertValid() const
{
   if (m_Radius < 0)
      return false;

   if (!InRange(0., m_Angle, 2 * M_PI))
      return false;

   if (!IsEqual(m_Smax - m_Smin, 2 * m_Radius))
      return false;

   if (m_Smax < m_Smin)
      return false;

   return true;
}
#endif // _DEBUG
