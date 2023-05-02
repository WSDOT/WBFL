///////////////////////////////////////////////////////////////////////
// CoordGeom - Coordinate Geometry Library
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

#include <CoordGeom/CoordGeomLib.h>
#include <CoordGeom/ProfilePoint.h>

using namespace WBFL::COGO;

ProfilePoint::ProfilePoint(const Station& station, Float64 elevation) :
   m_Station(station), m_Elevation(elevation)
{
}

bool ProfilePoint::operator==(const ProfilePoint& other) const
{
   return m_Station == other.m_Station && IsEqual(m_Elevation, other.m_Elevation);
}

bool ProfilePoint::operator!=(const ProfilePoint& other) const
{
   return !operator==(other);
}

void ProfilePoint::SetStation(const Station& station)
{
   m_Station = station;
}

const Station& ProfilePoint::GetStation() const
{
   return m_Station;
}

void ProfilePoint::SetElevation(Float64 elevation)
{
   m_Elevation = elevation;
}

Float64 ProfilePoint::GetElevation() const
{
   return m_Elevation;
}

void ProfilePoint::Move(const Station& station, Float64 elevation)
{
   m_Station = station;
   m_Elevation = elevation;
}

std::pair<Station,Float64> ProfilePoint::GetLocation() const
{
   return std::make_pair(m_Station, m_Elevation);
}


#if defined _UNITTEST
bool ProfilePoint::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("ProfilePoint");

   Station s(100.0);
   ProfilePoint p(s, 200);
   Station x;
   Float64 y;
   std::tie(x,y) = p.GetLocation();
   TRY_TESTME(s == x);
   TRY_TESTME(IsEqual(y, 200.));

   ProfilePoint z;
   TRY_TESTME(z.GetStation() == 0.0);
   TRY_TESTME(IsZero(z.GetElevation()));

   ProfilePoint zz(z);
   TRY_TESTME(zz == z);

   TRY_TESTME(p != z);

   TESTME_EPILOG("ProfilePoint");
}
#endif // _UNITTEST


