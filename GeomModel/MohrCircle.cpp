///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
// Copyright © 1999-2024  Washington State Department of Transportation
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

std::tuple<Float64,Float64,Float64> MohrCircle::ComputeState(Float64 angle) const
{
   auto sii = (m_Sii + m_Sjj) / 2.0 + (m_Sii - m_Sjj) * cos(2 * angle) / 2.0 + m_Sij * sin(2 * angle);
   auto sij = -(m_Sii - m_Sjj) * sin(2 * angle) / 2.0 + m_Sij * cos(2 * angle);
   auto sjj = m_Sii + m_Sjj - sii;

   return std::make_tuple(sii, sjj, sij);
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

#if defined _DEBUG
bool MohrCircle::AssertValid() const
{
   if (m_Radius < 0)
      return false;

   //if (!InRange(0., m_Angle, TWO_PI))
   //   return false;

   if (::IsGT(0.0, m_Radius))
   {
      if (!IsEqual((m_Smax - m_Smin) / (2 * m_Radius), 1.0))
         return false;
   }

   if (::IsGT(m_Smax, m_Smin))
      return false;

   return true;
}
#endif // _DEBUG
