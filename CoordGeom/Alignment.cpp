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
#include <CoordGeom/Alignment.h>
#include <CoordGeom/XCoordGeom.h>
#include <CoordGeom/Profile.h>
#include <CoordGeom/PathSegment.h>
#include <CoordGeom/Utilities.h>

using namespace WBFL::COGO;

std::shared_ptr<Alignment> Alignment::Create()
{
   //return std::make_shared<Alignment>(); This doesn't work because make_shared needs a public constructor for alignment
   return std::shared_ptr<Alignment>(new Alignment());
}

std::shared_ptr<Alignment> Alignment::Create(const Alignment& alignment)
{
   return std::shared_ptr<Alignment>(new Alignment(alignment));
}

Alignment::Alignment()
{
   m_Path = Path::Create();
}

Alignment::Alignment(const Alignment& alignment)
{
   m_ReferenceStation = alignment.m_ReferenceStation;
   m_Path = Path::Create(*alignment.m_Path);
   m_StationEquations = alignment.m_StationEquations;

   for (const auto& pair : alignment.m_Profiles)
   {
      auto id = pair.first;
      const auto& profile(pair.second);
      AddProfile(id, Profile::Create(*profile));
   }
}

void Alignment::SetReferenceStation(const Station& station)
{
   PRECONDITION(station.GetStationZoneIndex() == INVALID_INDEX);
   m_ReferenceStation = station.GetValue();
}

Station Alignment::GetReferenceStation() const
{
   return Station(m_ReferenceStation);
}

const StationEquation& Alignment::AddStationEquation(Float64 back, Float64 ahead)
{
   if (!m_StationEquations.empty())
   {
      auto prev_ahead_station = m_StationEquations.back().GetAhead();
      if (back <= prev_ahead_station)
      {
         BackStationError();
      }
   }

   Float64 normalized_station = ComputeNormalizedStation(back);
   m_StationEquations.emplace_back(back, ahead, normalized_station);
   return m_StationEquations.back();
}

const std::vector<StationEquation>& Alignment::GetStationEquations() const
{
   return m_StationEquations;
}

void Alignment::ClearStationEquations()
{
   m_StationEquations.clear();
}

Float64 Alignment::DistanceBetweenStations(const Station& s1, const Station& s2) const
{
   auto sta1 = ConvertToNormalizedStation(s1);
   auto sta2 = ConvertToNormalizedStation(s2);

   return sta2.GetValue() - sta1.GetValue();
}

Station& Alignment::IncrementStation(Station& station, Float64 distance) const
{
   auto ns = ConvertToNormalizedStation(station);
   CHECK(ns.IsNormalized());
   station = ConvertFromNormalizedStation(ns.GetValue() + distance);
   return station;
}

Station Alignment::IncrementStationBy(const Station& station, Float64 distance) const
{
   auto ns = ConvertToNormalizedStation(station);
   CHECK(ns.IsNormalized());
   return ConvertFromNormalizedStation(ns.GetValue() + distance);
}

Station Alignment::ConvertToNormalizedStation(const Station& station) const
{
   ZoneIndexType zoneIdx;
   Float64 value;
   std::tie(value,zoneIdx) = station.GetStation();
   if (zoneIdx == INVALID_INDEX)
   {
      return value;
   }

   IndexType nEquations = m_StationEquations.size();
   if (nEquations < zoneIdx)
   {
      THROW_COGO(WBFL_COGO_E_INVALIDINDEX); // the zone index is invalid (must be between 0 and nEquations+1
   }

   if (zoneIdx == 0)
   {
      // before the first equation
      if (0 < m_StationEquations.size())
      {
         // make sure the station is before the back station of the next equation
         Float64 nextBack = m_StationEquations.front().GetBack();
         if (nextBack < value)
         {
            StationEquationError();
         }
      }
      return value;
   }

   if (zoneIdx == nEquations)
   {
      // after the last equation
      // make sure the station is after the last ahead station
      Float64 nextAhead = m_StationEquations.back().GetAhead();
      if (value < nextAhead)
      {
         StationEquationError();
      }

      Float64 normalizedStation = m_StationEquations.back().GetNormalizedStation();
      return normalizedStation + (value - nextAhead);
   }

   // zone is somewhere between two equations

   IndexType eqIdx = zoneIdx - 1;
   auto prevAhead = m_StationEquations[eqIdx].GetAhead();
   auto nextBack = m_StationEquations[eqIdx + 1].GetBack();
   if (!InRange(prevAhead, value, nextBack))
   {
      StationEquationError();
   }

   Float64 normalizedStation = m_StationEquations[eqIdx].GetNormalizedStation();

   return normalizedStation + (value - prevAhead);

}

Station Alignment::ConvertFromNormalizedStation(Float64 normalizedStation) const
{
   if (m_StationEquations.empty())
   {
      // no station equations
      return Station(normalizedStation);
   }

   Float64 ns = m_StationEquations.front().GetNormalizedStation();
   if (normalizedStation <= ns)
   {
      // before the start of the station equations
      return Station(0, normalizedStation);
   }

   ns = m_StationEquations.back().GetNormalizedStation();
   if (ns <= normalizedStation)
   {
      // after the end of the station equations
      Float64 ahead = m_StationEquations.back().GetAhead();
      return Station(m_StationEquations.size(), normalizedStation - ns + ahead);
   }

   // somewhere in the middle... find it
   auto prev_iter(m_StationEquations.begin());
   auto iter = std::next(prev_iter);
   auto end(m_StationEquations.end());
   for (; iter != end; iter++, prev_iter++)
   {
      auto ns1 = prev_iter->GetNormalizedStation();
      auto ns2 = iter->GetNormalizedStation();

      if (InRange(ns1, normalizedStation, ns2))
      {
         Float64 ahead = prev_iter->GetAhead();
         ZoneIndexType zoneIdx = std::distance(m_StationEquations.begin(), iter);
         return Station(zoneIdx,normalizedStation - ns1 + ahead);
      }
   }

   CHECK(false); // should not get here
   return Station(INVALID_INDEX - 1, -9999999.999); // obviously bad station
}

Station Alignment::ConvertFromNormalizedStation(const Station& station) const
{
   if (station.GetStationZoneIndex() != INVALID_INDEX)
   {
      StationEquationError();
   }
   return ConvertFromNormalizedStation(station.GetValue());
}

Int8 Alignment::CompareStations(const Station& s1, const Station& s2) const
{
   auto ns1 = ConvertToNormalizedStation(s1);
   auto ns2 = ConvertToNormalizedStation(s2);
   return Utilities::CompareNormalizedStations(ns1, ns2);
}

void Alignment::AddProfile(IDType id,std::shared_ptr<Profile> profile)
{
   PRECONDITION(profile->GetAlignment() == nullptr); // profile can't be associated with multiple alignments
   auto result = m_Profiles.emplace(id, profile);
   result.first->second->SetAlignment(weak_from_this());
}

std::shared_ptr<Profile> Alignment::GetProfile(IDType id)
{
   auto found = m_Profiles.find(id);
   return (found == m_Profiles.end()) ? nullptr : found->second;
}

std::shared_ptr<const Profile> Alignment::GetProfile(IDType id) const
{
   auto found = m_Profiles.find(id);
   return (found == m_Profiles.end()) ? nullptr : found->second;
}

const std::map<IDType, std::shared_ptr<Profile>>& Alignment::GetProfiles() const
{
   return m_Profiles;
}

IDType Alignment::GetProfileID(IndexType idx) const
{
   auto iter = m_Profiles.begin();
   std::advance(iter, idx);
   return iter->first;
}

IndexType Alignment::GetProfileCount() const
{
   return m_Profiles.size();
}

void Alignment::ClearProfiles()
{
   m_Profiles.clear();
}

void Alignment::AddPathElement(std::shared_ptr<PathElement> pathElement)
{
   PRECONDITION(pathElement != nullptr); // can't be nullptr
   m_Path->AddPathElement(pathElement);
}

void Alignment::InsertPathElement(IndexType idx, std::shared_ptr<PathElement> pathElement)
{
   PRECONDITION(pathElement != nullptr); // can't be nullptr
   m_Path->InsertPathElement(idx, pathElement);
}

IndexType Alignment::GetPathElementCount() const
{
   return m_Path->GetPathElementCount();
}

std::shared_ptr<PathElement> Alignment::GetPathElement(IndexType idx)
{
   return m_Path->GetPathElement(idx);
}

std::shared_ptr<const PathElement> Alignment::GetPathElement(IndexType idx) const
{
   return m_Path->GetPathElement(idx);
}

std::vector<std::shared_ptr<PathElement>>& Alignment::GetPathElements()
{
   return m_Path->GetPathElements();
}

const std::vector<std::shared_ptr<PathElement>>& Alignment::GetPathElements() const
{
   return m_Path->GetPathElements();
}

void Alignment::ClearPathElements()
{
   m_Path->Clear();
}

void Alignment::Move(Float64 distance, const Direction& direction)
{
   m_Path->Move(distance, direction);
}

std::pair<Station, Float64> Alignment::StationAndOffset(const WBFL::Geometry::Point2d& point) const
{
   Float64 distFromStart;
   Float64 offset;
   std::tie(distFromStart, offset) = m_Path->DistanceAndOffset(point);
   Station station = ConvertFromNormalizedStation(m_ReferenceStation + distFromStart);
   return std::make_pair(station, offset);
}

std::vector<WBFL::Geometry::Point2d> Alignment::Divide(IndexType nParts) const
{
   Float64 L = GetLength();
   auto start = GetReferenceStation();
   auto end = IncrementStationBy(start, L);
   return Divide(start, end, nParts);
}

std::vector<WBFL::Geometry::Point2d> Alignment::Divide(const Station& start, const Station& end, IndexType nParts) const
{
   auto start_distance = StationToPathDistance(start);
   auto end_distance = StationToPathDistance(end);
   return m_Path->Divide(start_distance, end_distance, nParts);
}


std::tuple<WBFL::Geometry::Point2d, Station, bool> Alignment::ProjectPoint(const WBFL::Geometry::Point2d& point) const
{
   WBFL::Geometry::Point2d prjPoint;
   Float64 distFromStart;
   bool bOnProjection;
   std::tie(prjPoint,distFromStart,bOnProjection) = m_Path->ProjectPoint(point);
   Station station = ConvertFromNormalizedStation(m_ReferenceStation + distFromStart);
   return std::make_tuple(prjPoint, station, bOnProjection);
}

WBFL::Geometry::Point2d Alignment::LocatePoint(const Station& station, OffsetType offsetType, Float64 offset, const Direction& dir) const
{
   Float64 distFromStart = StationToPathDistance(station);
   return m_Path->LocatePoint(distFromStart, offsetType, offset, dir);
}

std::pair<bool, WBFL::Geometry::Point2d> Alignment::Intersect(const WBFL::Geometry::Line2d& line, const WBFL::Geometry::Point2d& nearest, bool bProjectBack, bool bProjectAhead) const
{
   return m_Path->Intersect(line, nearest, bProjectBack, bProjectAhead);
}

Direction Alignment::GetBearing(const Station& station) const
{
   Float64 distFromStart = StationToPathDistance(station);
   return m_Path->GetBearing(distFromStart);
}

Direction Alignment::GetNormal(const Station& station) const
{
   Float64 distFromStart = StationToPathDistance(station);
   return m_Path->GetNormal(distFromStart);
}

Direction Alignment::GetDirection(const Station& station, const std::_tstring& strOrient) const
{
   Direction direction;

   // Make the orientation string all upper case for easy comparison
   std::_tstring strOrientation(strOrient);
   std::transform(strOrientation.begin(), strOrientation.end(), strOrientation.begin(), (int(*)(int))std::toupper);


   // Get the alignment normal
   auto normal = GetNormal(station); // This is the normal to the right

   // We want the normal to the left... Increment by 180 degrees
   normal.Increment(M_PI);

   // process the orientation string
   if (strOrientation.compare(_T("N")) == 0 || strOrientation.compare(_T("NORMAL")) == 0)
   {
      // Normal to the alignment
      direction = normal;
   }
   else if (strOrientation[0] == _T('N') || strOrientation[0] == _T('S'))
   {
      // Defined by an explicit bearing
      Direction brg(strOrientation);

      // if the bearing is to the right of the alignment, reverse it
      auto alignment_direction = GetBearing(station);

      auto angle = brg.AngleBetween(alignment_direction);

      // if the angle between is between 0 and 180, bearing is to the left
      if (M_PI < angle)
      {
         // bearing is to the right of the alignment.... increment by 180 degrees
         brg.Increment(M_PI);
      }

      direction = brg;
   }
   else
   {
      Angle angle(strOrientation);
      direction = normal.IncrementBy(angle);
   }
   return direction;
}

Float64 Alignment::GetLength() const
{
   return m_Path->GetLength();
}

std::shared_ptr<Alignment> Alignment::CreateOffsetAlignment(Float64 offset) const
{
   auto offset_alignment = Alignment::Create();
   offset_alignment->SetReferenceStation(GetReferenceStation());

   auto offset_path_elements = m_Path->CreateOffsetPath(offset);
   offset_alignment->m_Path->Clear();
   for (auto& offset_path_element : offset_path_elements)
   {
      offset_alignment->m_Path->AddPathElement(offset_path_element);
   }

   // copy station equations
   for (const auto& equation : m_StationEquations)
   {
      offset_alignment->AddStationEquation(equation.GetBack(),equation.GetAhead());
   }

   return offset_alignment;
}

std::shared_ptr<Alignment> Alignment::CreateSubAlignment(const Station& start, const Station& end) const
{
   auto start_distance = StationToPathDistance(start);
   auto end_distance = StationToPathDistance(end);

   auto subpath_elements = m_Path->CreateSubpath(start_distance, end_distance);

   auto subalignment = Alignment::Create();
   subalignment->SetReferenceStation(start);
   if (!subpath_elements.empty())
   {
      subalignment->m_Path->Clear();
      for (auto& subpath_element : subpath_elements)
      {
         subalignment->m_Path->AddPathElement(subpath_element);
      }
   }

   // clone profile here if needed
   for (const auto& profile_record : m_Profiles)
   {
      auto ID = profile_record.first;
      const auto& profile = profile_record.second;

      // copy the profiles and all of it's surfaces and modifiers (superelevation and widenings)
      // and add to offset_alignment
      auto offset_alignment_profile = Profile::Create();

      // copy the profile elements
      auto nElements = profile->GetProfileElementCount();
      for (auto idx = 0; idx < nElements; idx++)
      {
         auto profile_element = profile->GetProfileElement(idx);

         // COPY SURFACES HERE ???

         offset_alignment_profile->AddProfileElement(profile_element->Clone());
      }

      subalignment->AddProfile(ID, offset_alignment_profile);
   }

   // Copy station equations that are within the station range
   for (const auto& equation : m_StationEquations)
   {
      if (InRange(ConvertToNormalizedStation(start).GetValue(), equation.GetNormalizedStation(), ConvertToNormalizedStation(end).GetValue()))
      {
         subalignment->AddStationEquation(equation.GetBack(), equation.GetAhead());
      }
   }

   auto pntStart = LocatePoint(start, OffsetType::AlongDirection, 0.0, 0.0);
   if (subalignment->GetPathElementCount() == 0)
   {
      auto pntEnd = LocatePoint(end, OffsetType::AlongDirection, 0.0, 0.0);
      auto segment = PathSegment::Create(pntStart, pntEnd);
      subalignment->AddPathElement(segment);
   }
   else
   {
      auto element = subalignment->GetPathElement(0);
      auto pntEnd = element->GetStartPoint();
      auto segment = PathSegment::Create(pntStart, pntEnd);
      subalignment->InsertPathElement(0, segment);
   }

   return subalignment;
}

std::shared_ptr<Path> Alignment::CreateOffsetPath(Float64 offset) const
{
   auto path_elements = m_Path->CreateOffsetPath(offset);
   auto path = Path::Create();
   for (auto& path_element : path_elements)
   {
      path->AddPathElement(path_element);
   }

   return path;
}

std::shared_ptr<Path> Alignment::CreateSubpath(const Station& start, const Station& end) const
{
   auto start_distance = StationToPathDistance(start);
   auto end_distance = StationToPathDistance(end);

   auto subpath_elements = m_Path->CreateSubpath(start_distance, end_distance);
   auto subpath = Path::Create();
   for (auto& subpath_element : subpath_elements)
   {
      subpath->AddPathElement(subpath_element);
   }
   return  subpath;
}

//
// Private methods
//
Float64 Alignment::ComputeNormalizedStation(Float64 back)
{
   if (m_StationEquations.empty())
      return back;

   Float64 prevNormalizedStation = m_StationEquations.back().GetNormalizedStation();
   Float64 prevAhead = m_StationEquations.back().GetAhead();
   Float64 dist = back - prevAhead;

   return prevNormalizedStation + dist;
}

void Alignment::BackStationError() const
{
   THROW_COGO(WBFL_COGO_E_STATIONEQUATIONBACK);
}

void Alignment::AheadStationError() const
{
   THROW_COGO(WBFL_COGO_E_STATIONEQUATIONAHEAD);
}

void Alignment::StationEquationError() const
{
   THROW_COGO(WBFL_COGO_E_STATIONRANGEERROR);
}

Float64 Alignment::StationToPathDistance(const Station& station) const
{
   auto normalized_station = ConvertToNormalizedStation(station);
   return normalized_station.GetValue() - m_ReferenceStation;
}

Station Alignment::CreateStation(Float64 normalizedStation) const
{
   return ConvertFromNormalizedStation(normalizedStation);
}

#if defined _UNITTEST
#include <CoordGeom/PathSegment.h>
#include <CoordGeom/CompoundCurve.h>
#include "Testing\TestAlignment1.h"
#include "Testing\TestAlignment2.h"
#include "Testing\TestAlignment3.h"
bool Alignment::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("Alignment");

   TRY_TESTME(TestStationEquations(rlog));
   TRY_TESTME(TestAlignment(rlog));
   TRY_TESTME(CTestAlignment1::Test(rlog));
   TRY_TESTME(CTestAlignment2::Test(rlog));
   TRY_TESTME(CTestAlignment3::Test(rlog));

   TESTME_EPILOG("Alignment");
}

bool Alignment::TestStationEquations(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("Alignment::TestStationEquations");

   auto alignment = Alignment::Create();
   TRY_TESTME(alignment->GetStationEquations().empty()); // should start off empty

   auto equation = alignment->AddStationEquation(3400, 3200);
   TRY_TESTME(alignment->GetStationEquations().size() == 1);
   TRY_TESTME(IsEqual(equation.GetBack(), 3400.0));
   TRY_TESTME(IsEqual(equation.GetAhead(), 3200.0));

   try { alignment->AddStationEquation(200.00, 50.0); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_STATIONEQUATIONBACK); }

   equation = alignment->AddStationEquation(4200, 500.0);
   TRY_TESTME(alignment->GetStationEquations().size() == 2);
   TRY_TESTME(IsEqual(equation.GetBack(), 4200.0));
   TRY_TESTME(IsEqual(equation.GetAhead(), 500.0));

   equation = alignment->AddStationEquation(600, 1500.0);
   TRY_TESTME(alignment->GetStationEquations().size() == 3);
   TRY_TESTME(IsEqual(equation.GetBack(), 600.0));
   TRY_TESTME(IsEqual(equation.GetAhead(), 1500.0));

   alignment->ClearStationEquations();
   TRY_TESTME(alignment->GetStationEquations().empty());

   // test with some real values
   alignment->AddStationEquation(1500, 1350);
   alignment->AddStationEquation(2000, 2150);
   alignment->AddStationEquation(3200, 4000);
   alignment->AddStationEquation(4800, 0);

   Station station;

   // before first equation
   station.SetStation(0, 11700);
   try { alignment->ConvertToNormalizedStation(station); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_STATIONRANGEERROR); }

   station.SetStation(0, 1200);
   TRY_TESTME(IsEqual(alignment->ConvertToNormalizedStation(station).GetValue(), 1200.0));

   // after last equation
   station.SetStation(25, 11700); // bad zone index
   try { alignment->ConvertToNormalizedStation(station); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_INVALIDINDEX); }

   station.SetStation(4, -600);
   try { alignment->ConvertToNormalizedStation(station); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_STATIONRANGEERROR); }

   station.SetStation(4, 1200);
   TRY_TESTME(IsEqual(alignment->ConvertToNormalizedStation(station).GetValue(), 5200.0));

   station.SetStation(1, 11700);
   try { alignment->ConvertToNormalizedStation(station); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_STATIONRANGEERROR); }

   station.SetStation(1, 1250);
   try { alignment->ConvertToNormalizedStation(station); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_STATIONRANGEERROR); }

   station.SetStation(1, 1700);
   TRY_TESTME(IsEqual(alignment->ConvertToNormalizedStation(station).GetValue(), 1850.0));

   // station is already normalized
   station.SetStation(INVALID_INDEX,1700);
   TRY_TESTME(IsEqual(alignment->ConvertToNormalizedStation(station).GetValue(), 1700.0));

   station = alignment->ConvertFromNormalizedStation(1200);
   TRY_TESTME(station.GetStationZoneIndex() == 0);
   TRY_TESTME(IsEqual(station.GetValue(), 1200.0));

   station = alignment->ConvertFromNormalizedStation(1800);
   TRY_TESTME(station.GetStationZoneIndex() == 1);
   TRY_TESTME(IsEqual(station.GetValue(), 1650.0));

   station = alignment->ConvertFromNormalizedStation(2300);
   TRY_TESTME(station.GetStationZoneIndex() == 2);
   TRY_TESTME(IsEqual(station.GetValue(), 2300.0));

   station = alignment->ConvertFromNormalizedStation(3300);
   TRY_TESTME(station.GetStationZoneIndex() == 3);
   TRY_TESTME(IsEqual(station.GetValue(), 4100.0));

   station = alignment->ConvertFromNormalizedStation(4500);
   TRY_TESTME(station.GetStationZoneIndex() == 4);
   TRY_TESTME(IsEqual(station.GetValue(), 500.));

   station = alignment->ConvertFromNormalizedStation(2150);
   TRY_TESTME(station.GetStationZoneIndex() == 1);
   TRY_TESTME(IsEqual(station.GetValue(), 2000.0));

   station = alignment->ConvertFromNormalizedStation(3200);
   TRY_TESTME(station.GetStationZoneIndex() == 2);
   TRY_TESTME(IsEqual(station.GetValue(), 3200.0));

   station.SetStation(1, 1360);
   try { alignment->ConvertFromNormalizedStation(station); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_STATIONRANGEERROR); }

   station.SetStation(INVALID_INDEX, 1360);
   station = alignment->ConvertFromNormalizedStation(station);
   TRY_TESTME(station.GetStationZoneIndex() == 0);
   TRY_TESTME(IsEqual(station.GetValue(), 1360.0));

   // Test Distance
   auto dist = alignment->DistanceBetweenStations(2000.0, 3000.0);
   TRY_TESTME(IsEqual(dist, 1000.0));

   dist = alignment->DistanceBetweenStations(3000.0, 2000.0);
   TRY_TESTME(IsEqual(dist, -1000.0));

   dist = alignment->DistanceBetweenStations(Station(1, 1400.0), Station(2, 3000.0));
   TRY_TESTME(IsEqual(dist, 1450.0));

   // Test Increment
   station.SetStation(3, 4100);
   alignment->IncrementStation(station, -500);
   TRY_TESTME(station.GetStationZoneIndex() == 2);
   TRY_TESTME(IsEqual(station.GetValue(), 2800.0));


   TESTME_EPILOG("Alignment::TestStationEquations");
}

bool Alignment::TestAlignment(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("Alignment::TestAlignment");

   auto alignment = Alignment::Create();

   auto segment = PathSegment::Create(10, 20, 20, 30);
   alignment->AddPathElement(segment);

   auto hc = CompoundCurve::Create();
   hc->SetPBT(WBFL::Geometry::Point2d(100, 100));
   alignment->AddPathElement(hc);

   TRY_TESTME(alignment->GetPathElementCount() == 2);

   auto pe = alignment->GetPathElement(0);
   TRY_TESTME(std::dynamic_pointer_cast<const PathSegment>(pe));
   TRY_TESTME(segment == pe);
   TRY_TESTME(std::dynamic_pointer_cast<const PathSegment>(pe)->GetStartPoint() == WBFL::Geometry::Point2d(10, 20));
   TRY_TESTME(std::dynamic_pointer_cast<const PathSegment>(pe)->GetEndPoint() == WBFL::Geometry::Point2d(20, 30));

   pe = alignment->GetPathElement(1);
   TRY_TESTME(std::dynamic_pointer_cast<const CompoundCurve>(pe));
   TRY_TESTME(hc == pe);
   TRY_TESTME(std::dynamic_pointer_cast<const CompoundCurve>(pe)->GetPBT() == WBFL::Geometry::Point2d(100, 100));

   TRY_TESTME(alignment->GetReferenceStation() == Station(0.0));
   alignment->SetReferenceStation(50.0);
   TRY_TESTME(alignment->GetReferenceStation() == Station(50.0));

   alignment->ClearPathElements();
   TRY_TESTME(alignment->GetPathElementCount() == 0);

   // Test GetDirection
   segment->ThroughPoints(WBFL::Geometry::Point2d(0, 0), WBFL::Geometry::Point2d(100, 100));
   alignment->AddPathElement(segment);
   TRY_TESTME(alignment->GetDirection(0.0, _T("N")) == Direction(3 * M_PI / 4));
   TRY_TESTME(alignment->GetDirection(0.0, _T("Normal")) == Direction(3 * M_PI / 4));
   TRY_TESTME(alignment->GetDirection(50.0, _T("15 0 0 L")) == Direction(3*M_PI / 4 + ToRadians(15)));
   TRY_TESTME(alignment->GetDirection(50.0, _T("15 0 0 R")) == Direction(3*M_PI / 4 - ToRadians(15)));
   TRY_TESTME(alignment->GetDirection(100.0, _T("N 45 W")) == Direction(3 * M_PI / 4));
   TRY_TESTME(alignment->GetDirection(100.0, _T("S 45 W")) == Direction(5 * M_PI / 4));
   TRY_TESTME(alignment->GetDirection(100.0, _T("N 45 E")) == Direction(M_PI / 4));
   TRY_TESTME(alignment->GetDirection(100.0, _T("S 45 E")) == Direction(3 * M_PI / 4));

   TESTME_EPILOG("Alignment::TestAlignment");
}

#endif // _UNITTEST


