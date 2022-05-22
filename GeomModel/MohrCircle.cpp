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
#include "MohrCircle.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

MohrCircle::MohrCircle() :
   m_Sii(0.0),
   m_Sjj(0.0),
   m_Sij(0.0)
{
   Init();
}

MohrCircle::MohrCircle(Float64 sii, Float64 sjj, Float64 sij) :
   m_Sii(sii),
   m_Sjj(sjj),
   m_Sij(sij)
{
   Init();
}

MohrCircle::~MohrCircle()
{
}

void MohrCircle::ComputeState(Float64 angle,Float64& sii, Float64& sjj, Float64& sij) const
{
   sii = (m_Sii + m_Sjj) / 2.0 + (m_Sii - m_Sjj) * cos(2 * angle) / 2.0 + m_Sij * sin(2 * angle);
   sij = -(m_Sii - m_Sjj) * sin(2 * angle) / 2.0 + m_Sij * cos(2 * angle);
   sjj = m_Sii + m_Sjj - sii;
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

Float64 MohrCircle::GetPrincipalDirection() const
{
   if (IsZero(GetRadius()))
      return 0; // special case

   return m_Angle / 2;
}

Float64 MohrCircle::GetCenter() const
{
   return m_Center;
}

Float64 MohrCircle::GetRadius() const
{
   return m_Radius;
}

#if defined _DEBUG
bool MohrCircle::AssertValid() const
{
   if (m_Radius < 0)
      return false;

   //if (!InRange(0., m_Angle, TWO_PI))
   //   return false;

   if (0 < m_Radius)
   {
      if (!IsEqual((m_Smax - m_Smin) / (2 * m_Radius), 1.0))
         return false;
   }

   if (m_Smax < m_Smin)
      return false;

   return true;
}

void MohrCircle::Dump(WBFL::Debug::LogContext& os) const
{
   os << "Dump for MohrCircle" << WBFL::Debug::endl;
}
#endif // _DEBUG

void MohrCircle::Init()
{
   // Compute principal values
   m_Radius = pow((m_Sii - m_Sjj), 2.) / 4. + pow(m_Sij, 2.);
   m_Radius = sqrt(m_Radius);

   m_Smin = (m_Sii + m_Sjj) / 2. + m_Radius;
   m_Smax = (m_Sii + m_Sjj) / 2. - m_Radius;

   if (m_Smax < m_Smin)
   {
      Float64 temp = m_Smin;
      m_Smin = m_Smax;
      m_Smax = temp;
   }

   // Center of circle
   m_Center = (m_Smin + m_Smax) / 2.;

   // Angle to principal plane
   if (m_Radius == 0.0)
   {
      m_Angle = 0.0;
   }
   else
   {
      // stored angle is in mohr's system (twice external angle and measured clockwise)
      m_Angle = atan2(2 * m_Sij, (m_Sii - m_Sjj));
   }

   ASSERTVALID;
}

//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

#if defined _UNITTEST
bool MohrCircle::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("MohrCircle");

   Float64 sii, sjj, sij;
   Float64 temp;

   MohrCircle ct(64, 16, -32);

   temp = ct.GetPrincipalDirection();
   if (!IsEqual(ct.GetSmax(), 80., 0.01) ||
      !IsEqual(ct.GetSmin(), 0., 0.01) ||
      !IsEqual(ct.GetTmax(), 40., 0.01) ||
      !IsEqual(temp, ToRadians(-26.57), 0.01))
   {
      TRY_TESTME(false);
   }

   // should be able to get principals from princ angle
   ct.ComputeState(temp, sii, sjj, sij);
   if (!IsEqual(sii, 80.) ||
      !IsEqual(sjj, 0.) ||
      !IsEqual(sij, 0.))
   {
      TRY_TESTME(false);
   }


   // Test 1
   // Example 1.1 pg 13 from Ugural and Fenster
   MohrCircle c1(80, 40, 30);

   if (!IsEqual(c1.GetSmax(), 96.05, 0.01) ||
      !IsEqual(c1.GetSmin(), 23.95, 0.01) ||
      !IsEqual(c1.GetTmax(), 36.05, 0.01) ||
      !IsEqual(c1.GetPrincipalDirection(), ToRadians(28.15), 0.01))
   {
      TRY_TESTME(false);
   }

   // Test 2
   // Example 1.2 pg 15 from Ugural and Fenster
   MohrCircle c2(-14, 28, 0);

   c2.ComputeState(ToRadians(30.0), sii, sjj, sij);
   if (!IsEqual(sii, -3.5, 0.1) ||
      !IsEqual(sjj, 17.5, 0.1) ||
      !IsEqual(sij, 18.186, 0.001))
   {
      TRY_TESTME(false);
   }

   // Test 2
   // Problem 1.3 pg 27 from Ugural and Fenster
   MohrCircle c3(100, -50, -60);

   if (!IsEqual(c3.GetSmax(), 121.0, 0.1) ||
      !IsEqual(c3.GetSmin(), -71.0, 0.1) ||
      !IsEqual(c3.GetTmax(), 96.0, 0.1) ||
      !IsEqual(c3.GetPrincipalDirection(), ToRadians(-19.33), 0.1))
   {
      TRY_TESTME(false);
   }

   MohrCircle c4(150, 0, 100);

   if (!IsEqual(c4.GetSmax(), 200.0, 0.1) ||
      !IsEqual(c4.GetSmin(), -50.0, 0.1) ||
      !IsEqual(c4.GetTmax(), 125.0, 0.1) ||
      !IsEqual(c4.GetPrincipalDirection(), ToRadians(26.57), 0.1))
   {
      TRY_TESTME(false);
   }

   // From "Statics", Merriam, Pge 373
   MohrCircle c5(18.167, 10.167, -7.5);
   if (!IsEqual(c5.GetSmax(), 22.67, 0.1) ||
      !IsEqual(c5.GetSmin(), 5.67, 0.1) ||
      !IsEqual(c5.GetPrincipalDirection(), ToRadians(-30.96), 0.01))
   {
      TRY_TESTME(false);
   }

   // From Beer & Johnston, Mechanics of Materials, page 306
   MohrCircle c6(100, 60, 48);
   if (!IsEqual(c6.GetSmax(), 132., 0.1) ||
      !IsEqual(c6.GetSmin(), 28., 0.1) ||
      !IsEqual(c6.GetPrincipalDirection(), ToRadians(33.7), 0.1))
   {
      TRY_TESTME(false);
   }

   c6.ComputeState(ToRadians(30.0), sii, sjj, sij);
   if (!IsEqual(sii, 131.57, 0.1) ||
      !IsEqual(sjj, 28.43, 0.1) ||
      !IsEqual(sij, 6.68, 0.1))
   {
      TRY_TESTME(false);
   }

   MohrCircle c7(50, -10, 40);
   if (!IsEqual(c7.GetSmax(), 70., 0.1) ||
      !IsEqual(c7.GetSmin(), -30., 0.1) ||
      !IsEqual(c7.GetPrincipalDirection(), ToRadians(26.56), 0.1))
   {
      TRY_TESTME(false);
   }

   MohrCircle c8(4.18, 3.25, 2.87);
   if (!IsEqual(c8.GetSmax(), 6.63, 0.1) ||
      !IsEqual(c8.GetSmin(), 0.81, 0.1) ||
      !IsEqual(c8.GetPrincipalDirection(), ToRadians(40.4), 0.1))
   {
      TRY_TESTME(false);
   }

   MohrCircle c9(10.38, 6.97, -6.56);
   if (!IsEqual(c9.GetSmax(), 15.45, 0.1) ||
      !IsEqual(c9.GetSmin(), 1.897, 0.1) ||
      !IsEqual(c9.GetPrincipalDirection(), ToRadians(-37.7), 0.1))
   {
      TRY_TESTME(false);
   }

   TESTME_EPILOG("MohrCircle");
}
#endif // _UNITTEST
