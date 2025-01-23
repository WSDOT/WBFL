///////////////////////////////////////////////////////////////////////
// CoordGeom - Coordinate Geometry Library
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

#include <CoordGeom/CoordGeomLib.h>
#include <CoordGeom/ProfileSegment.h>
#include <CoordGeom/Profile.h>
#include <CoordGeom/Alignment.h>

using namespace WBFL::COGO;

std::shared_ptr<ProfileSegment> ProfileSegment::Create()
{
   return std::shared_ptr<ProfileSegment>(new ProfileSegment());
}

std::shared_ptr<ProfileSegment> ProfileSegment::Create(const ProfilePoint& p1, const ProfilePoint& p2)
{
   auto segment = Create();
   segment->Move(p1, p2);
   return segment;
}

void ProfileSegment::SetStartPoint(const ProfilePoint& start)
{
   m_Start = start;
   OnProfileElementChanged();
}

void ProfileSegment::SetEndPoint(const ProfilePoint& end)
{
   m_End = end;
   OnProfileElementChanged();
}

std::pair<ProfilePoint, ProfilePoint> ProfileSegment::GetLocation() const
{
   return std::make_pair(m_Start, m_End);
}

void ProfileSegment::Move(const ProfilePoint& p1, const ProfilePoint& p2)
{
   m_Start = p1;
   m_End = p2;
   OnProfileElementChanged();
}

//
// ProfileElement methods
//

std::shared_ptr<ProfileElement> ProfileSegment::Clone() const
{
   return std::shared_ptr<ProfileElement>(new ProfileSegment(*this));
}

const ProfilePoint& ProfileSegment::GetStartPoint() const
{
   return m_Start;
}

const ProfilePoint& ProfileSegment::GetEndPoint() const
{
   return m_End;
}

Float64 ProfileSegment::GetLength() const
{
   return GetProfile()->GetAlignment()->DistanceBetweenStations(m_Start.GetStation(), m_End.GetStation());
}

std::pair<Float64, Float64> ProfileSegment::ComputeGradeAndElevation(const Station& station) const
{
   auto s1 = GetProfile()->GetAlignment()->ConvertToNormalizedStation(m_Start.GetStation()).GetValue();
   auto s2 = GetProfile()->GetAlignment()->ConvertToNormalizedStation(m_End.GetStation()).GetValue();
   auto dx = s2 - s1;
   auto dy = m_End.GetElevation() - m_Start.GetElevation();
   auto grade = IsZero(dx) ? Float64_Max : dy / dx;
   
   auto s = GetProfile()->GetAlignment()->ConvertToNormalizedStation(station).GetValue();
   auto d = s - s1;
   auto elevation = m_Start.GetElevation() + d * (grade);

   return std::make_pair(grade, elevation);
}
