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
#include <CoordGeom/Model.h>
#include <CoordGeom/COGO.h>
#include <CoordGeom/XCoordGeom.h>

using namespace WBFL::COGO;

bool Model::StorePoint(IDType id, const WBFL::Geometry::Point2d& point)
{
   auto result = m_Points.emplace(id, point);
   return result.second;
}

bool Model::StorePoint(IDType id, Float64 x, Float64 y)
{
   return StorePoint(id, WBFL::Geometry::Point2d(x, y));
}

bool Model::StorePoints(IDType firstID, IDType idInc, const std::vector<WBFL::Geometry::Point2d>& vPoints)
{
   return StorePoints(firstID, idInc, vPoints.begin(), vPoints.end());
}

bool Model::StorePoints(IDType firstID, IDType idInc, std::vector<WBFL::Geometry::Point2d>::const_iterator i1, std::vector<WBFL::Geometry::Point2d>::const_iterator i2)
{
   bool bSucceeded = false;
   IDType id = firstID;
   auto begin = i1;
   for (; i1 != i2; i1++)
   {
      bSucceeded = StorePoint(id, *i1);
      if (!bSucceeded) break;

      id += idInc;
   }
   
   // if all points were not successfully stored, remove any point that was stored
   if(!bSucceeded)
   {
      id = firstID;
      for (; begin != i1; begin++)
      {
         RemovePoint(id);
         id += idInc;
      }
   }
   return bSucceeded;
}

bool Model::ReplacePoint(IDType id, const WBFL::Geometry::Point2d& point)
{
   auto found = m_Points.find(id);
   if (found == m_Points.end())
   {
      return false;
   }

   found->second = point;
   return true;
}

bool Model::ReplacePoint(IDType id, Float64 x, Float64 y)
{
   return ReplacePoint(id, WBFL::Geometry::Point2d(x, y));
}

bool Model::RemovePoint(IDType id)
{
   return RemoveItem(m_Points, id);
}

WBFL::Geometry::Point2d Model::GetPoint(IDType id)
{
   auto found = m_Points.find(id);
   if (found == m_Points.end())
      THROW_COGO(WBFL_COGO_E_INVALIDARG);

   return found->second;
}

const WBFL::Geometry::Point2d& Model::GetPoint(IDType id) const
{
   auto found = m_Points.find(id);
   if (found == m_Points.end())
      THROW_COGO(WBFL_COGO_E_INVALIDARG);

   return found->second;
}

const std::map<IDType, WBFL::Geometry::Point2d>& Model::GetPoints() const
{
   return m_Points;
}

void Model::ClearPoints()
{
   m_Points.clear();
}

bool Model::StorePathSegment(IDType id, IDType startID, IDType endID)
{
   PathSegmentDefinition definition{ startID, endID };
   return StorePathSegment(id, definition);
}

bool Model::StorePathSegment(IDType id, const PathSegmentDefinition& definition)
{
   auto result = m_Segments.emplace(id, definition);
   return result.second;
}

bool Model::RemovePathSegment(IDType id)
{
   return RemoveItem(m_Segments, id);
}

const Model::PathSegmentDefinition& Model::GetPathSegment(IDType id) const
{
   auto found = m_Segments.find(id);
   if (found == m_Segments.end())
   {
      THROW_COGO(WBFL_COGO_E_INVALIDARG);
   }

   return found->second;
}

std::shared_ptr<PathSegment> Model::CreatePathSegment(IDType id) const
{
   auto found = m_Segments.find(id);
   if (found == m_Segments.end())
   {
      THROW_COGO(WBFL_COGO_E_INVALIDARG);
   }
    
   const auto& p1 = GetPoint(found->second.startID);
   const auto& p2 = GetPoint(found->second.endID);
   return PathSegment::Create(p1, p2);
}

const std::map<IDType, Model::PathSegmentDefinition>& Model::GetPathSegments() const
{
   return m_Segments;
}

void Model::ClearPathSegments()
{
   m_Segments.clear();
}

bool Model::StoreCompoundCurve(IDType id, IDType pbtID, IDType piID, IDType pftID, Float64 radius, Float64 lsEntry, TransitionCurveType lsEntryType, Float64 lsExit, TransitionCurveType lsExitType)
{
   CompoundCurveDefinition definition{ pbtID,piID,pftID,radius,lsEntry,lsEntryType,lsExit,lsExitType };
   return StoreCompoundCurve(id, definition);
}

bool Model::StoreCompoundCurve(IDType id, CompoundCurveDefinition& definition)
{
   auto result = m_CompoundCurves.emplace(id, definition);
   return result.second;
}

bool Model::RemoveCompoundCurve(IDType id)
{
   return RemoveItem(m_CompoundCurves, id);
}

const Model::CompoundCurveDefinition& Model::GetCompoundCurve(IDType id) const
{
   auto found = m_CompoundCurves.find(id);
   if (found == m_CompoundCurves.end())
      THROW_COGO(WBFL_COGO_E_INVALIDARG);

   return found->second;
}

std::shared_ptr<CompoundCurve> Model::CreateCompoundCurve(IDType id) const
{
   auto found = m_CompoundCurves.find(id);
   if (found == m_CompoundCurves.end())
      THROW_COGO(WBFL_COGO_E_INVALIDARG);

   CompoundCurveDefinition definition = found->second;
   const auto& pbt = GetPoint(definition.pbtID);
   const auto& pi = GetPoint(definition.piID);
   const auto& pft = GetPoint(definition.pftID);
   return CompoundCurve::Create(pbt, pi, pft, definition.radius, definition.entry_spiral_length, definition.entry_spiral_type, definition.exit_spiral_length, definition.exit_spiral_type);
}

const std::map<IDType, Model::CompoundCurveDefinition>& Model::GetCompoundCurves() const
{
   return m_CompoundCurves;
}

void Model::ClearCompoundCurves()
{
   m_CompoundCurves.clear();
}

bool Model::StoreCircularCurve(IDType id, IDType pbtID, IDType piID, IDType pftID, Float64 radius)
{
   CircularCurveDefinition definition{ pbtID,piID,pftID,radius };
   return StoreCircularCurve(id, definition);
}

bool Model::StoreCircularCurve(IDType id, const CircularCurveDefinition& definition)
{
   auto result = m_CircularCurves.emplace(id, definition);
   return result.second;
}

bool Model::RemoveCircularCurve(IDType id)
{
   return RemoveItem(m_CircularCurves, id);
}

const Model::CircularCurveDefinition& Model::GetCircularCurve(IDType id) const
{
   auto found = m_CircularCurves.find(id);
   if (found == m_CircularCurves.end())
      THROW_COGO(WBFL_COGO_E_INVALIDARG);

   return found->second;
}

std::shared_ptr<CircularCurve> Model::CreateCircularCurve(IDType id) const
{
   auto found = m_CircularCurves.find(id);
   if (found == m_CircularCurves.end())
      THROW_COGO(WBFL_COGO_E_INVALIDARG);

   CircularCurveDefinition definition = found->second;
   const auto& pbt = GetPoint(definition.pbtID);
   const auto& pi = GetPoint(definition.piID);
   const auto& pft = GetPoint(definition.pftID);
   return CircularCurve::Create(pbt, pi, pft, definition.radius);
}

const std::map<IDType, Model::CircularCurveDefinition>& Model::GetCircularCurves() const
{
   return m_CircularCurves;
}

void Model::ClearCircularCurves()
{
   m_CircularCurves.clear();
}

bool Model::StoreTransitionCurve(IDType id, IDType startID, const Direction& direction, Float64 r1, Float64 r2, Float64 L, TransitionCurveType transitionType)
{
   TransitionCurveDefinition definition{ startID,direction,r1,r2,L,transitionType };
   return StoreTransitionCurve(id, definition);
}

bool Model::StoreTransitionCurve(IDType id, const TransitionCurveDefinition& definition)
{
   auto result = m_TransitionCurves.emplace(id, definition);
   return result.second;
}

bool Model::RemoveTransitionCurve(IDType id)
{
   return RemoveItem(m_TransitionCurves, id);
}

const Model::TransitionCurveDefinition& Model::GetTransitionCurve(IDType id) const
{
   auto found = m_TransitionCurves.find(id);
   if (found == m_TransitionCurves.end())
      THROW_COGO(WBFL_COGO_E_INVALIDARG);

   return found->second;
}

std::shared_ptr<TransitionCurve> Model::CreateTransitionCurve(IDType id) const
{
   auto found = m_TransitionCurves.find(id);
   if (found == m_TransitionCurves.end())
      THROW_COGO(WBFL_COGO_E_INVALIDARG);

   TransitionCurveDefinition definition = found->second;
   const auto& pntStart = GetPoint(definition.startID);
   return TransitionCurve::Create(pntStart, definition.start_direction, definition.start_radius, definition.end_radius, definition.length, definition.transition_type);
}

const std::map<IDType, Model::TransitionCurveDefinition>& Model::GetTransitionCurves() const
{
   return m_TransitionCurves;
}

void Model::ClearTransitionCurves()
{
   m_TransitionCurves.clear();
}

bool Model::StoreCubicSpline(IDType id, const std::vector<IDType>& vPointIDs)
{
   auto result = m_CubicSplines.emplace(id, vPointIDs);
   return result.second;
}

bool Model::RemoveCubicSpline(IDType id)
{
   return RemoveItem(m_CubicSplines,id);
}

const std::vector<IDType>& Model::GetCubicSpline(IDType id) const
{
   auto found = m_CubicSplines.find(id);
   if (found == m_CubicSplines.end())
      THROW_COGO(WBFL_COGO_E_INVALIDARG);

   return found->second;
}

std::shared_ptr<CubicSpline> Model::CreateCubicSpline(IDType id) const
{
   auto found = m_CubicSplines.find(id);
   if (found == m_CubicSplines.end())
      THROW_COGO(WBFL_COGO_E_INVALIDARG);

   auto spline = CubicSpline::Create();
   for (const auto& pntID : found->second)
   {
      const auto& pnt = GetPoint(pntID);
      spline->AddPoint(pnt);
   }

   return spline;
}

const std::map<IDType, std::vector<IDType>>& Model::GetCubicSplines()
{
   return m_CubicSplines;
}

void Model::ClearCubicSplines()
{
   m_CubicSplines.clear();
}

bool Model::StoreAlignment(IDType alignmentID)
{
   return StoreAlignment(alignmentID, std::vector<PathElementDefinition>());
}

bool Model::StoreAlignment(IDType alignmentID, const std::vector<PathElementDefinition>& vElements)
{
   auto result = m_Alignments.emplace(alignmentID, vElements);
   return result.second;
}

bool Model::AppendElementToAlignment(IDType alignmentID, PathElementType elementType, IDType elementID)
{
   PathElementDefinition item{ elementType,elementID };
   return AppendElementToAlignment(alignmentID, item);
}

bool Model::AppendElementToAlignment(IDType alignmentID, const PathElementDefinition& item)
{
   auto found = m_Alignments.find(alignmentID);
   if (found == m_Alignments.end()) return false;

   found->second.emplace_back(item);
   return true;
}

bool Model::RemoveAlignment(IDType alignmentID)
{
   return RemoveItem(m_Alignments, alignmentID);
}

const std::vector<Model::PathElementDefinition>& Model::GetAlignment(IDType alignmentID) const
{
   auto found = m_Alignments.find(alignmentID);
   if (found == m_Alignments.end())
      THROW_COGO(WBFL_COGO_E_INVALIDARG);

   return found->second;
}

std::shared_ptr<Alignment> Model::CreateAlignment(IDType alignmentID) const
{
   auto alignment = Alignment::Create();
   CreatePath(alignmentID, m_Alignments, alignment); // create the alignment (same procedure as creating a path)

   // If there is a reference station, set it
   auto found_refstation = m_AlignmentReferenceStations.find(alignmentID);
   if (found_refstation != m_AlignmentReferenceStations.end())
      alignment->SetReferenceStation(found_refstation->second);

   // Apply station equations, if defined
   auto found_stationequations = m_StationEquations.find(alignmentID);
   if (found_stationequations != m_StationEquations.end())
   {
      const auto& vEquations = found_stationequations->second;
      for (const auto& equation : vEquations)
      {
         alignment->AddStationEquation(equation.first, equation.second);
      }
   }

   // Go through all the profile-alignment associations to see if any profiles
   // are associated with the alignment that is being created. If so,
   // create the profile and add it to the alignment
   for (const auto& association : m_ProfileAlignmentAssociations)
   {
      if (association.second == alignmentID)
      {
         auto profile = CreateProfile(association.first, alignment);
      }
   }

   return alignment;
}

const std::map<IDType, std::vector<Model::PathElementDefinition>>& Model::GetAlignments() const
{
   return m_Alignments;
}

void Model::ClearAlignments(bool bClearRefStations)
{
   m_Alignments.clear();
   if (bClearRefStations) m_AlignmentReferenceStations.clear();
}

bool Model::SetAlignmentReferneceStation(IDType alignmentID, const Station& station)
{
   auto result = m_AlignmentReferenceStations.emplace(alignmentID, station);
   return result.second;
}

bool Model::RemoveAlignmentReferenceStation(IDType alignmentID)
{
   return RemoveItem(m_AlignmentReferenceStations, alignmentID);
}

const Station& Model::GetAlignmentReferenceStation(IDType alignmentID) const
{
   auto found = m_AlignmentReferenceStations.find(alignmentID);
   if (found == m_AlignmentReferenceStations.end())
      THROW_COGO(WBFL_COGO_E_INVALIDARG);

   return found->second;
}

bool Model::AddStationEquation(IDType alignmentID, Float64 back, Float64 ahead)
{
   return AddStationEquation(alignmentID, StationEquationDefinition(back, ahead));
}

bool Model::AddStationEquation(IDType alignmentID, const StationEquationDefinition& definition)
{
   auto found = m_StationEquations.find(alignmentID);
   if (found == m_StationEquations.end())
   {
      auto result = m_StationEquations.emplace(alignmentID, std::vector<StationEquationDefinition>());
      if (result.second == false) THROW_COGO(WBFL_COGO_E_INVALIDARG);

      found = result.first;
   }

   found->second.emplace_back(definition);
   return true;
}

const std::vector<Model::StationEquationDefinition>& Model::GetStationEquations(IDType alignmentID) const
{
   auto found = m_StationEquations.find(alignmentID);
   if (found == m_StationEquations.end())
   {
      THROW_COGO(WBFL_COGO_E_INVALIDARG);
   }

   return found->second;
}

void Model::ClearStationEquations(IDType alignmentID)
{
   if (alignmentID == INVALID_ID)
   {
      // clear all
      m_StationEquations.clear();
   }
   else
   {
      auto found = m_StationEquations.find(alignmentID);
      if (found == m_StationEquations.end())
      {
         THROW_COGO(WBFL_COGO_E_INVALIDARG);
      }

      found->second.clear();
   }
}

bool Model::StorePath(IDType id)
{
   return StorePath(id, std::vector<std::pair<PathElementType, IDType>>());
}

bool Model::StorePath(IDType id, const std::vector<std::pair<PathElementType, IDType>>& vElements)
{
   auto result = m_Paths.emplace(id, vElements);
   return result.second;
}

bool Model::AppendElementToPath(IDType pathID, PathElementType elementType, IDType elementID)
{
   PathElementDefinition item{ elementType,elementID };
   return AppendElementToPath(pathID, item);
}

bool Model::AppendElementToPath(IDType pathID, const PathElementDefinition& item)
{
   auto found = m_Paths.find(pathID);
   if (found == m_Paths.end()) return false;

   found->second.emplace_back(item);
   return true;
}

bool Model::RemovePath(IDType id)
{
   return RemoveItem(m_Paths, id);
}

const std::vector<Model::PathElementDefinition>& Model::GetPath(IDType id) const
{
   auto found = m_Paths.find(id);
   if (found == m_Paths.end())
      THROW_COGO(WBFL_COGO_E_INVALIDARG);

   return found->second;
}

std::shared_ptr<Path> Model::CreatePath(IDType id) const
{
   auto path = Path::Create();
   CreatePath(id, m_Paths, path);
   return path;
}

const std::map<IDType, std::vector<Model::PathElementDefinition>>& Model::GetPaths() const
{
   return m_Paths;
}

void Model::ClearPaths()
{
   m_Paths.clear();
}

bool Model::StoreProfilePoint(IDType id, const ProfilePoint& profilePoint)
{
   auto result = m_ProfilePoints.emplace(id, profilePoint);
   return result.second;
}

bool Model::StoreProfilePoint(IDType id, const Station& station, Float64 elevation)
{
   return StoreProfilePoint(id,ProfilePoint(station, elevation));
}

bool Model::ReplaceProfilePoint(IDType id, const ProfilePoint& profilePoint)
{
   auto found = m_ProfilePoints.find(id);
   if (found == m_ProfilePoints.end())
   {
      return false;
   }

   found->second = profilePoint;
   return true;
}

bool Model::ReplaceProfilePoint(IDType id, const Station& station, Float64 elevation)
{
   return ReplaceProfilePoint(id, ProfilePoint(station, elevation));
}

bool Model::RemoveProfilePoint(IDType id)
{
   return m_ProfilePoints.erase(id) == 1 ? true : false;
}

ProfilePoint Model::GetProfilePoint(IDType id)
{
   auto found = m_ProfilePoints.find(id);
   if (found == m_ProfilePoints.end())
      THROW_COGO(WBFL_COGO_E_INVALIDARG);

   return found->second;
}

const ProfilePoint& Model::GetProfilePoint(IDType id) const
{
   auto found = m_ProfilePoints.find(id);
   if (found == m_ProfilePoints.end())
      THROW_COGO(WBFL_COGO_E_INVALIDARG);

   return found->second;
}

const std::map<IDType, ProfilePoint>& Model::GetProfilePoints() const
{
   return m_ProfilePoints;
}

void Model::ClearProfilePoints()
{
   m_ProfilePoints.clear();
}

bool Model::StoreProfileSegment(IDType id, IDType startID, IDType endID)
{
   ProfileSegmentDefinition definition{ startID,endID };
   return StoreProfileSegment(id, definition);
}

bool Model::StoreProfileSegment(IDType id, const ProfileSegmentDefinition& definition)
{
   auto result = m_ProfileSegments.emplace(id, definition);
   return result.second;
}

bool Model::RemoveProfileSegment(IDType id)
{
   auto found = m_ProfileSegments.find(id);
   if (found == m_ProfileSegments.end())
      return false;

   m_ProfileSegments.erase(found);
   return true;
}

const Model::ProfileSegmentDefinition& Model::GetProfileSegment(IDType id) const
{
   auto found = m_ProfileSegments.find(id);
   if (found == m_ProfileSegments.end())
   {
      THROW_COGO(WBFL_COGO_E_INVALIDARG);
   }

   return found->second;
}

std::shared_ptr<ProfileSegment> Model::CreateProfileSegment(IDType id) const
{
   const auto definition = GetProfileSegment(id);
   const auto& p1 = GetProfilePoint(definition.startID);
   const auto& p2 = GetProfilePoint(definition.endID);
   return ProfileSegment::Create(p1, p2);
}

const std::map<IDType, Model::ProfileSegmentDefinition>& Model::GetProfileSegments() const
{
   return m_ProfileSegments;
}

void Model::ClearProfileSegments()
{
   m_ProfileSegments.clear();
}

bool Model::StoreVerticalCurve(IDType id, IDType pbgID, IDType pviID, IDType pftID, Float64 l1_or_g1, Float64 l2_or_g2)
{
   VerticalCurveDefinition definition{ pbgID,pviID,pftID,l1_or_g1,l2_or_g2 };
   return StoreVerticalCurve(id, definition);
}

bool Model::StoreVerticalCurve(IDType id, const VerticalCurveDefinition& definition)
{
   auto result = m_VerticalCurves.emplace(id, definition);
   return result.second;
}

bool Model::RemoveVerticalCurve(IDType id)
{
   auto found = m_VerticalCurves.find(id);
   if (found == m_VerticalCurves.end())
      return false;

   m_VerticalCurves.erase(found);
   return true;
}

const Model::VerticalCurveDefinition& Model::GetVerticalCurve(IDType id) const
{
   auto found = m_VerticalCurves.find(id);
   if (found == m_VerticalCurves.end())
   {
      THROW_COGO(WBFL_COGO_E_INVALIDARG);
   }

   return found->second;
}

std::shared_ptr<VerticalCurve> Model::CreateVerticalCurve(IDType id) const
{
   const auto& definition = GetVerticalCurve(id);
   const auto& pbg = GetProfilePoint(definition.pbgID);
   const auto& pfg = GetProfilePoint(definition.pfgID);
   if (definition.pviID == INVALID_ID)
   {
      Float64 g1 = definition.l1_or_g1;
      Float64 g2 = definition.l2_or_g2;
      return VerticalCurve::Create(pbg, pfg, g1, g2);
   }
   else
   {
      auto pvi = GetProfilePoint(definition.pviID);
      Float64 l1 = definition.l1_or_g1;
      Float64 l2 = definition.l2_or_g2;
      return VerticalCurve::Create(pbg, pvi, pfg, l1, l2);
   }
}

const std::map<IDType, Model::VerticalCurveDefinition>& Model::GetVerticalCurves() const
{
   return m_VerticalCurves;
}

void Model::ClearVerticalCurves()
{
   m_VerticalCurves.clear();
}

bool Model::StoreProfile(IDType id)
{
   return StoreProfile(id, std::vector<std::pair<ProfileElementType, IDType>>());
}

bool Model::StoreProfile(IDType id, const std::vector<std::pair<ProfileElementType, IDType>>& vElements)
{
   auto result = m_Profiles.emplace(id, vElements);
   return result.second;
}

bool Model::AppendElementToProfile(IDType profileID, ProfileElementType type, IDType elementID)
{
   auto found = m_Profiles.find(profileID);
   if (found == m_Profiles.end()) return false;

   found->second.emplace_back(type, elementID);
   return true;
}

bool Model::RemoveProfile(IDType id)
{
   auto found = m_Profiles.find(id);
   if (found == m_Profiles.end())
      return false;

   m_Profiles.erase(found);

   auto found2 = m_ProfileAlignmentAssociations.find(id);
   if (found2 != m_ProfileAlignmentAssociations.end())
      m_ProfileAlignmentAssociations.erase(found2);

   return true;
}

const std::vector<std::pair<Model::ProfileElementType, IDType>>& Model::GetProfile(IDType id) const
{
   auto found = m_Profiles.find(id);
   if (found == m_Profiles.end())
   {
      THROW_COGO(WBFL_COGO_E_INVALIDARG);
   }

   return found->second;
}

std::shared_ptr<Profile> Model::CreateProfile(IDType id) const
{
   return CreateProfile(id, nullptr);
}

const std::map<IDType, std::vector<std::pair<Model::ProfileElementType, IDType>>>& Model::GetProfiles() const
{
   return m_Profiles;
}

void Model::ClearProfiles()
{
   m_Profiles.clear();
   m_ProfileAlignmentAssociations.clear();
}

bool Model::StoreSurface(IDType surfaceID, IndexType nSegments, IndexType alignmentPointIdx, IndexType profilePointIdx)
{
   return StoreSurface(surfaceID,std::make_tuple(nSegments, alignmentPointIdx, profilePointIdx));
}

bool Model::StoreSurface(IDType surfaceID, const SurfaceDefinition& surfaceDef)
{
   auto result = m_Surfaces.emplace(surfaceID, surfaceDef);
   return result.second;
}

const std::map<IDType, Model::SurfaceDefinition>& Model::GetSurfaces() const
{
   return m_Surfaces;
}

const Model::SurfaceDefinition& Model::GetSurface(IDType surfaceID) const
{
   auto found = m_Surfaces.find(surfaceID);
   if (found == m_Surfaces.end())
      THROW_COGO(WBFL_COGO_E_INVALIDARG);

   return found->second;
}

bool Model::AddSurfaceTemplate(IDType surfaceID, const Station& station)
{
   IndexType nSegments, alignmentPointIdx, profilePointIdx;
   std::tie(nSegments,alignmentPointIdx,profilePointIdx) = GetSurface(surfaceID); // throws on bad ID

   // default surface template segment (width = 1, slope = 0, horizontal slope)
   auto default_segment = std::make_tuple(1.0, 0.0, SurfaceTemplateSegment::SlopeType::Horizontal);

   // fill a vector with nSegment number of segments
   std::vector<std::tuple<Float64, Float64, SurfaceTemplateSegment::SlopeType>> vSurfaceTemplateSegments(nSegments, default_segment);

   // search for the surface templates for surfaceID
   auto found = m_SurfaceTemplates.find(surfaceID);
   if (found == m_SurfaceTemplates.end())
   {
      // not found, this is the first template, create a new record

      // vector of surface template segments defined, on for each station where surface templates are defined
      std::vector<std::pair<Station, std::vector<std::tuple<Float64, Float64, SurfaceTemplateSegment::SlopeType>>>> vSurfaceTemplates;

      // store the station and surface template segments for the first surface template
      vSurfaceTemplates.emplace_back(std::make_pair(station, vSurfaceTemplateSegments));

      // put the collection of surface templates for this surface into the surface templates storage
      auto result = m_SurfaceTemplates.emplace(surfaceID, vSurfaceTemplates);
      if (result.second == false)
         return false;
      else
         found = result.first;
   }
   else
   {
      // a surface template has already been defined. append the new surface template to the existing collection
      found->second.emplace_back(std::make_pair(station, vSurfaceTemplateSegments));
   }
   return true;
}

bool Model::CopySurfaceTemplate(IDType surfaceID, IndexType templateIdx, const Station& station)
{
   if (!AddSurfaceTemplate(surfaceID, station)) return false;

   auto found = m_SurfaceTemplates.find(surfaceID);
   if (found == m_SurfaceTemplates.end()) return false;
   if (found->second.size() <= templateIdx) return false;

   const auto& surface_template = found->second[templateIdx];
   auto& this_surface_template = found->second.back();
   this_surface_template = surface_template;
   this_surface_template.first = station; // the assignment on the line above changes the station - put it back to the correct value
   return true;
}

bool Model::MoveSurfaceTemplate(IDType surfaceID, IndexType templateIdx, const Station& station)
{
   auto found = m_SurfaceTemplates.find(surfaceID);
   if (found == m_SurfaceTemplates.end()) return false;
   if (found->second.size() <= templateIdx) return false;
   found->second[templateIdx].first = station;
   return true;
}

IndexType Model::GetSurfaceTemplateCount(IDType surfaceID) const
{
   auto found = m_SurfaceTemplates.find(surfaceID);
   if (found == m_SurfaceTemplates.end())
      return 0;
   else
      return found->second.size();
}

const Station& Model::GetSurfaceTemplateLocation(IDType surfaceID, IndexType templateIdx)
{
   auto found = m_SurfaceTemplates.find(surfaceID);
   if (found == m_SurfaceTemplates.end())
      THROW_COGO(WBFL_COGO_E_INVALIDARG);

   if(found->second.size() <= templateIdx)
      THROW_COGO(WBFL_COGO_E_INVALIDARG);

   return found->second[templateIdx].first;
}

const Model::SurfaceTemplateDefinition& Model::GetSurfaceTemplate(IDType surfaceID, IndexType templateIdx) const
{
   auto found = m_SurfaceTemplates.find(surfaceID);
   if (found == m_SurfaceTemplates.end())
      THROW_COGO(WBFL_COGO_E_INVALIDARG);

   if (found->second.size() <= templateIdx)
      THROW_COGO(WBFL_COGO_E_INVALIDARG);

   return found->second[templateIdx];
}

bool Model::UpdateSurfaceTemplateSegment(IDType surfaceID, IndexType templateIdx, IndexType segmentIdx, Float64 width, Float64 slope, SurfaceTemplateSegment::SlopeType slopeType)
{
   return UpdateSurfaceTemplateSegment(surfaceID, templateIdx, segmentIdx, std::make_tuple(width, slope, slopeType));
}

bool Model::UpdateSurfaceTemplateSegment(IDType surfaceID, IndexType templateIdx, IndexType segmentIdx, const SurfaceTemplateSegmentDefinition& surfaceTemplateSegment)
{
   auto found = m_SurfaceTemplates.find(surfaceID);
   if (found == m_SurfaceTemplates.end())
      THROW_COGO(WBFL_COGO_E_INVALIDARG);

   if (found->second.size() <= templateIdx)
      THROW_COGO(WBFL_COGO_E_INVALIDARG);

   IndexType nSegments, alignmentPointIdx, profilePointIdx;
   std::tie(nSegments, alignmentPointIdx, profilePointIdx) = GetSurface(surfaceID); // throws on bad ID
   if (nSegments <= segmentIdx)
      THROW_COGO(WBFL_COGO_E_INVALIDARG);

   found->second[templateIdx].second[segmentIdx] = surfaceTemplateSegment;
   return true;
}

bool Model::StoreSuperelevation(IDType surfaceID, const Station& beginTrasitionStation, const Station& beginFullSuperStation, const Station& endFullSuperStation, const Station& endTrasitionStation, Float64 rate, IndexType pivotPointIdx,
   Superelevation::TransitionType beginTransitionType, Float64 beginL1, Float64 beginL2, Superelevation::TransitionType endTransitionType, Float64 endL1, Float64 endL2)
{
   SuperelevationDefinition definition{ beginTrasitionStation,beginFullSuperStation,endFullSuperStation,endTrasitionStation,rate,pivotPointIdx,beginTransitionType,beginL1,beginL2,endTransitionType,endL1,endL2 };
   return StoreSuperelevation(surfaceID, definition);
}

bool Model::StoreSuperelevation(IDType surfaceID, const SuperelevationDefinition& definition)
{
   auto found = m_Superelevations.find(surfaceID);
   if (found == m_Superelevations.end())
   {
      // this is a new superelevation. create the superelevation record
      std::vector<SuperelevationDefinition> vSuperelevations;
      auto result = m_Superelevations.emplace(surfaceID, vSuperelevations);
      found = result.first;
   }

   found->second.emplace_back(definition);

   return true;
}

const std::map<IDType, std::vector<Model::SuperelevationDefinition>>& Model::GetSuperelevations() const
{
   return m_Superelevations;
}

const std::vector<Model::SuperelevationDefinition>& Model::GetSuperelevations(IDType surfaceID) const
{
   auto found = m_Superelevations.find(surfaceID);
   if (found == m_Superelevations.end())
      THROW_COGO(WBFL_COGO_E_INVALIDARG);

   return found->second;
}

bool Model::ClearSuperelevations(IDType surfaceID)
{
   auto found = m_Superelevations.find(surfaceID);
   if (found == m_Superelevations.end())
   {
      return false;
   }

   found->second.clear();
   return true;
}

void Model::ClearSuperelevations()
{
   m_Superelevations.clear();
}

bool Model::StoreWidening(IDType surfaceID, const Station& beginTrasitionStation, const Station& beginFullWidening, const Station& endFullWidening, const Station& endTrasitionStation, Float64 widening, IndexType segment1, IndexType segment2)
{
   WideningDefinition definition{ beginTrasitionStation, beginFullWidening, endFullWidening, endTrasitionStation, widening, segment1, segment2 };
   return StoreWidening(surfaceID, definition);
}

bool Model::StoreWidening(IDType surfaceID, const WideningDefinition& definition)
{
   auto found = m_Widenings.find(surfaceID);
   if (found == m_Widenings.end())
   {
      // this is a new widening. create the widening record
      std::vector<WideningDefinition> vWidenings;
      auto result = m_Widenings.emplace(surfaceID, vWidenings);
      found = result.first;
   }

   found->second.emplace_back(definition);
   return true;
}

const std::map<IDType, std::vector<Model::WideningDefinition>>& Model::GetWidenings() const
{
   return m_Widenings;
}

const std::vector<Model::WideningDefinition>& Model::GetWidenings(IDType surfaceID) const
{
   auto found = m_Widenings.find(surfaceID);
   if (found == m_Widenings.end())
      THROW_COGO(WBFL_COGO_E_INVALIDARG);

   return found->second;
}

bool Model::ClearWidenings(IDType surfaceID)
{
   auto found = m_Widenings.find(surfaceID);
   if (found == m_Widenings.end())
   {
      return false;
   }

   found->second.clear();
   return true;
}

void Model::ClearWidenings()
{
   m_Widenings.clear();
}

std::shared_ptr<Surface> Model::CreateSurface(IDType surfaceID) const
{
   return CreateSurface(surfaceID, nullptr);
}

bool Model::RemoveSurface(IDType surfaceID, bool bClearModifiers)
{
   auto found_surface = m_Surfaces.find(surfaceID);
   if (found_surface == m_Surfaces.end())
      return false; // the surface doesn't exist

   m_Surfaces.erase(found_surface);

   // the following attributes of a surface are optional and may not be defined

   auto found_template = m_SurfaceTemplates.find(surfaceID);
   if(found_template != m_SurfaceTemplates.end())
      m_SurfaceTemplates.erase(found_template);

   auto found_association = m_SurfaceProfileAssociations.find(surfaceID);
   if(found_association != m_SurfaceProfileAssociations.end())
      m_SurfaceProfileAssociations.erase(found_association);

   if (bClearModifiers)
   {
      auto found_superelevations = m_Superelevations.find(surfaceID);
      if (found_superelevations != m_Superelevations.end())
      {
         m_Superelevations.erase(found_superelevations);
      }

      auto found_widenings = m_Widenings.find(surfaceID);
      if (found_widenings != m_Widenings.end())
      {
         m_Widenings.erase(found_widenings);
      }
   }

   return true;
}

void Model::ClearSurfaces(bool bClearModifiers)
{
   m_Surfaces.clear();
   m_SurfaceTemplates.clear();
   m_SurfaceProfileAssociations.clear();

   if (bClearModifiers)
   {
      m_Superelevations.clear();
      m_Widenings.clear();
   }
}

void Model::AttachProfileToAlignment(IDType profileID, IDType alignmentID)
{
   m_ProfileAlignmentAssociations.emplace(profileID, alignmentID);
}

void Model::AttachSurfaceToProfile(IDType surfaceID, IDType profileID)
{
   m_SurfaceProfileAssociations.emplace(surfaceID, profileID);
}

void Model::Clear()
{
   ClearPoints();
   ClearPathSegments();
   ClearCompoundCurves();
   ClearCircularCurves();
   ClearTransitionCurves();
   ClearCubicSplines();
   ClearAlignments();
   ClearPaths();
   ClearProfilePoints();
   ClearProfileSegments();
   ClearProfiles();
   ClearStationEquations();
   ClearSurfaces(); // clears surface profile associations and surface modifiers
}

Angle Model::MeasureAngle(IDType fromID, IDType vertexID, IDType toID) const
{
   const auto& from = GetPoint(fromID);
   const auto& vertex = GetPoint(vertexID);
   const auto& to = GetPoint(toID);

   return COGO::MeasureAngle(from, vertex, to);
}


Float64 Model::MeasureArea(const std::vector<IDType>& vIDs) const
{
   std::vector<WBFL::Geometry::Point2d> points;
   for (const auto& id : vIDs)
   {
      points.emplace_back(GetPoint(id));
   }

   return COGO::MeasureArea(points);
}

Float64 Model::MeasureDistance(IDType fromID, IDType toID) const
{
   const auto& from = GetPoint(fromID);
   const auto& to = GetPoint(toID);
   return COGO::MeasureDistance(from, to);
}

Direction Model::MeasureDirection(IDType fromID, IDType toID) const
{
   const auto& from = GetPoint(fromID);
   const auto& to = GetPoint(toID);
   return COGO::MeasureDirection(from, to);
}

std::pair<Float64, Direction> Model::ComputeInverse(IDType fromID, IDType toID) const
{
   const auto& from = GetPoint(fromID);
   const auto& to = GetPoint(toID);
   return COGO::ComputeInverse(from, to);
}

bool Model::LocateByDistanceAndAngle(IDType newPointID, IDType fromID, IDType toID, Float64 distance, const Angle& angle, Float64 offset)
{
   const auto& from = GetPoint(fromID);
   const auto& to = GetPoint(toID);
   try
   {
      auto point = COGO::LocateByDistanceAndAngle(from, to, distance, angle, offset);
      return StorePoint(newPointID, point);
   }
   catch (...)
   {
   }
   return false;
}

bool Model::LocateByDistanceAndDeflectionAngle(IDType newPointID, IDType fromID, IDType toID, Float64 distance, const Angle& defAngle, Float64 offset)
{
   const auto& from = GetPoint(fromID);
   const auto& to = GetPoint(toID);
   try
   {
      auto point = COGO::LocateByDistanceAndDeflectionAngle(from, to, distance, defAngle, offset);
      return StorePoint(newPointID, point);
   }
   catch (...)
   {
   }
   return false;
}

bool Model::LocateByDistanceAndDirection(IDType newPointID, IDType fromID, Float64 distance, const Direction& direction, Float64 offset)
{
   const auto& from = GetPoint(fromID);
   try
   {
      auto point = COGO::LocateByDistanceAndDirection(from, distance, direction, offset);
      return StorePoint(newPointID, point);
   }
   catch (...)
   {
   }
   return false;
}

bool Model::LocatePointOnLine(IDType newPointID, IDType fromID, IDType toID, Float64 distance, Float64 offset)
{
   const auto& from = GetPoint(fromID);
   const auto& to = GetPoint(toID);
   try
   {
      auto point = COGO::LocatePointOnLine(from, to, distance, offset);
      return StorePoint(newPointID, point);
   }
   catch (...)
   {
   }
   return false;
}

bool Model::LocateParallelLineByPoints(IDType newFromID, IDType newToID, IDType fromID, IDType toID, Float64 offset)
{
   const auto& from = GetPoint(fromID);
   const auto& to = GetPoint(toID);
   try
   {
      WBFL::Geometry::Point2d newFrom, newTo;
      std::tie(newFrom, newTo) = COGO::LocateParallelLineByPoints(from, to, offset);
      std::vector<std::pair<IDType, WBFL::Geometry::Point2d>> points;
      points.emplace_back(newFromID, newFrom);
      points.emplace_back(newToID, newTo);
      return AtomicStorePoints(points);
   }
   catch (...)
   {
   }
   return false;
}

bool Model::LocateParallelLineSegment(IDType newSegmentID, IDType newFromID, IDType newToID, IDType segmentID, Float64 offset)
{
   auto segment = CreatePathSegment(segmentID);
   auto newSegment = COGO::LocateParallelLineSegment(*segment, offset);

   bool bFrom = StorePoint(newFromID, newSegment.GetStartPoint());
   bool bTo = StorePoint(newToID, newSegment.GetEndPoint());
   bool bSegment = StorePathSegment(newSegmentID, newFromID, newToID);
   if (!(bFrom && bTo && bSegment))
   {
      // something didn't get stored, so remove any that did
      if (bFrom) RemovePoint(newFromID);
      if (bTo) RemovePoint(newToID);
      if (bSegment) RemovePathSegment(newSegmentID);
   }

   return bFrom &&  bTo && bSegment;
}

bool Model::IntersectBearings(IDType newID, IDType id1, const Direction& dir1, Float64 offset1, IDType id2, const Direction& dir2, Float64 offset2)
{
   const auto& p1 = GetPoint(id1);
   const auto& p2 = GetPoint(id2);
   try
   {
      auto point = COGO::IntersectBearings(p1, dir1, offset1, p2, dir2, offset2);
      return StorePoint(newID, point);
   }
   catch(...)
   {
   }
   return false;
}

bool Model::IntersectBearingAndCircle(IDType newID, IDType startID, const Direction& dir, Float64 offset, IDType centerID, Float64 radius, IDType nearestID)
{
   const auto& start = GetPoint(startID);
   const auto& center = GetPoint(centerID);
   const auto& nearest = GetPoint(nearestID);
   try
   {
      auto point = COGO::IntersectBearingAndCircle(start, dir, offset, center, radius, nearest);
      return StorePoint(newID, point);
   }
   catch (...)
   {
   }
   return false;
}

bool Model::IntersectCircles(IDType newID, IDType centerID1, Float64 radius1, IDType centerID2, Float64 radius2, IDType nearestID)
{
   const auto& center1 = GetPoint(centerID1);
   const auto& center2 = GetPoint(centerID2);
   const auto& nearest = GetPoint(nearestID);
   try
   {
      auto point = COGO::IntersectCircles(center1, radius1, center2, radius2, nearest);
      return StorePoint(newID, point);
   }
   catch (...)
   {
   }
   return false;
}

bool Model::IntersectLineByPointsAndCircle(IDType newID, IDType startID, IDType endID, Float64 offset, IDType centerID, Float64 radius, IDType nearestID)
{
   const auto& start = GetPoint(startID);
   const auto& end = GetPoint(endID);
   const auto& center = GetPoint(centerID);
   const auto& nearest = GetPoint(nearestID);
   try
   {
      auto point = COGO::IntersectLineByPointsAndCircle(start, end, offset, center, radius, nearest);
      return StorePoint(newID, point);
   }
   catch (...)
   {
   }
   return false;
}

bool Model::IntersectLinesByPoints(IDType newID, IDType startID1, IDType endID1, Float64 offset1, IDType startID2, IDType endID2, Float64 offset2)
{
   const auto& start1 = GetPoint(startID1);
   const auto& end1 = GetPoint(endID1);
   const auto& start2 = GetPoint(startID2);
   const auto& end2 = GetPoint(endID2);
   try
   {
      auto point = COGO::IntersectLinesByPoints(start1, end1, offset1, start2, end2, offset2);
      return StorePoint(newID, point);
   }
   catch (...)
   {
   }
   return false;
}

bool Model::IntersectPathSegments(IDType newID, IDType lsID1, Float64 offset1, IDType lsID2, Float64 offset2)
{
   auto ls1 = CreatePathSegment(lsID1);
   auto ls2 = CreatePathSegment(lsID2);
   try
   {
      auto point = COGO::IntersectLineSegments(*ls1, offset1, *ls2, offset2);
      return StorePoint(newID, point);
   }
   catch (...)
   {
   }
   return false;
}

bool Model::IntersectPathSegmentAndCircle(IDType newID, IDType lsID, Float64 offset, IDType centerID, Float64 radius, IDType nearestID)
{
   auto ls = CreatePathSegment(lsID);
   const auto& center = GetPoint(centerID);
   const auto& nearest = GetPoint(nearestID);
   try
   {
      auto point = COGO::IntersectLineSegmentAndCircle(*ls, offset, center, radius, nearest);
      return StorePoint(newID, point);
   }
   catch (...)
   {
   }
   return false;
}

bool Model::ProjectPointOnCompoundCurve(IDType newID, IDType fromID, IDType curveID)
{
   auto curve = CreateCompoundCurve(curveID);
   const auto& point = GetPoint(fromID);
   try
   {
      WBFL::Geometry::Point2d newPoint;
      Float64 distFromStart;
      bool bOnProjection;
      std::tie(newPoint, distFromStart, bOnProjection) = curve->ProjectPoint(point);
      return StorePoint(newID, newPoint);
   }
   catch (...)
   {
   }
   return false;
}

bool Model::ProjectPointOnTransitionCurve(IDType newID, IDType fromID, IDType curveID)
{
   auto curve = CreateTransitionCurve(curveID);
   const auto& point = GetPoint(fromID);
   try
   {
      WBFL::Geometry::Point2d newPoint;
      Float64 distFromStart;
      bool bOnProjection;
      std::tie(newPoint, distFromStart, bOnProjection) = curve->ProjectPoint(point);
      return StorePoint(newID, newPoint);
   }
   catch (...)
   {
   }
   return false;
}

bool Model::ProjectPointOnCircularCurve(IDType newID, IDType fromID, IDType curveID)
{
   auto curve = CreateCircularCurve(curveID);
   const auto& point = GetPoint(fromID);
   try
   {
      WBFL::Geometry::Point2d newPoint;
      Float64 distFromStart;
      bool bOnProjection;
      std::tie(newPoint, distFromStart, bOnProjection) = curve->ProjectPoint(point);
      return StorePoint(newID, newPoint);
   }
   catch (...)
   {
   }
   return false;
}

bool Model::ProjectPointOnPath(IDType newID, IDType fromID, IDType pathID)
{
   auto path = CreatePath(pathID);
   const auto& point = GetPoint(fromID);
   try
   {
      WBFL::Geometry::Point2d newPoint;
      Float64 distFromStart;
      bool bOnProjection;
      std::tie(newPoint, distFromStart, bOnProjection) = path->ProjectPoint(point);
      return StorePoint(newID, newPoint);
   }
   catch (...)
   {
   }
   return false;
}

bool Model::ProjectPointOnAlignment(IDType newID, IDType fromID, IDType alignmentID)
{
   auto alignment = CreateAlignment(alignmentID);
   const auto& point = GetPoint(fromID);
   try
   {
      WBFL::Geometry::Point2d newPoint;
      Station station;
      bool bOnProjection;
      std::tie(newPoint, station, bOnProjection) = alignment->ProjectPoint(point);
      return StorePoint(newID, newPoint);
   }
   catch (...)
   {
   }
   return false;
}

bool Model::ProjectPointOnLineByPoints(IDType newID, IDType fromID, IDType startID, IDType endID, Float64 offset)
{
   const auto& from = GetPoint(fromID);
   const auto& start = GetPoint(startID);
   const auto& end = GetPoint(endID);
   try
   {
      auto point = COGO::ProjectPointOnLineByPoints(from, start, end, offset);
      return StorePoint(newID, point);
   }
   catch (...)
   {
   }
   return false;
}

bool Model::ProjectPointOnPathSegment(IDType newID, IDType fromID, IDType lsID, Float64 offset)
{
   const auto& from = GetPoint(fromID);
   auto ls = CreatePathSegment(lsID);
   try
   {
      auto point = COGO::ProjectPointOnLineSegment(from, *ls, offset);
      return StorePoint(newID, point);
   }
   catch (...)
   {
   }
   return false;
}

bool Model::DivideArc(IDType firstID, IDType idInc, IDType fromID, IDType vertexID, IDType toID, IndexType nParts)
{
   if (nParts == INVALID_INDEX) return false;

   const auto& from = GetPoint(fromID);
   const auto& vertex = GetPoint(vertexID);
   const auto& to = GetPoint(toID);

   try
   {
      auto points = COGO::DivideArc(from, vertex, to, nParts);
      return StorePoints(firstID, idInc, std::next(std::begin(points)), std::prev(std::end(points)));
   }
   catch (...)
   {
   }
   return false;
}

bool Model::DivideBetweenPoints(IDType firstID, IDType idInc, IDType fromID, IDType toID, IndexType nParts)
{
   if (nParts == INVALID_INDEX) return false;

   const auto& from = GetPoint(fromID);
   const auto& to = GetPoint(toID);

   try
   {
      auto points = COGO::DivideBetweenPoints(from, to, nParts);
      return StorePoints(firstID, idInc, std::next(std::begin(points)), std::prev(std::end(points)));
   }
   catch (...)
   {
   }
   return false;
}

bool Model::DivideLineSegment(IDType firstID, IDType idInc, IDType lsID, IndexType nParts)
{
   if (nParts == INVALID_INDEX) return false;

   auto ls = CreatePathSegment(lsID);
   try
   {
      auto points = COGO::DivideBetweenPoints(ls->GetStartPoint(), ls->GetEndPoint(), nParts);
      return StorePoints(firstID, idInc, std::next(std::begin(points)), std::prev(std::end(points)));
   }
   catch (...)
   {
   }
   return false;
}

bool Model::DivideCompoundCurve(IDType firstID, IDType idInc, IDType curveID, IndexType nParts)
{
   if (nParts == INVALID_INDEX) return false;

   auto curve = CreateCompoundCurve(curveID);

   try
   {
      auto points = curve->Divide(nParts);
      return StorePoints(firstID, idInc, std::next(std::begin(points)), std::prev(std::end(points)));
   }
   catch (...)
   {
   }
   return false;
}

bool Model::DivideTransitionCurve(IDType firstID, IDType idInc, IDType curveID, IndexType nParts)
{
   if (nParts == INVALID_INDEX) return false;

   auto curve = CreateTransitionCurve(curveID);
   
   try
   {
      auto points = curve->Divide(nParts);
      return StorePoints(firstID, idInc, std::next(std::begin(points)), std::prev(std::end(points)));
   }
   catch (...)
   {
   }
   return false;
}

bool Model::DivideCircularCurve(IDType firstID, IDType idInc, IDType curveID, IndexType nParts)
{
   if (nParts == INVALID_INDEX) return false;

   auto curve = CreateCircularCurve(curveID);
   try
   {
      auto points = curve->Divide(nParts);
      return StorePoints(firstID, idInc, std::next(std::begin(points)), std::prev(std::end(points)));
   }
   catch (...)
   {
   }
   return false;
}

bool Model::DividePath(IDType firstID, IDType idInc, IDType pathID, IndexType nParts, Float64 start, Float64 end)
{
   if (nParts == INVALID_INDEX) return false;

   auto path = CreatePath(pathID);
   
   try
   {
      auto points = path->Divide(start, end, nParts);
      return StorePoints(firstID, idInc, std::next(std::begin(points)), std::prev(std::end(points)));
   }
   catch (...)
   {
   }
   return false;
}

bool Model::DivideAlignment(IDType firstID, IDType idInc, IDType alignmentID, IndexType nParts, const Station& start, const Station& end)
{
   if (nParts == INVALID_INDEX) return false;

   auto alignment = CreateAlignment(alignmentID);
   
   try
   {
      auto points = alignment->Divide(start, end, nParts);
      return StorePoints(firstID, idInc, std::next(std::begin(points)), std::prev(std::end(points)));
   }
   catch (...)
   {
   }
   return false;
}

bool Model::CrossingTangents(IDType newID1, IDType centerID1, Float64 radius1, IDType newID2, IDType centerID2, Float64 radius2, TangentSign sign)
{
   if (radius1 < 0 || radius2 < 0)
      return false;

   const auto& center1 = GetPoint(centerID1);
   const auto& center2 = GetPoint(centerID2);

   try
   {
      WBFL::Geometry::Point2d t1, t2;
      std::tie(t1, t2) = COGO::CrossingTangents(center1, radius1, center2, radius2, sign);
      std::vector<std::pair<IDType, WBFL::Geometry::Point2d>> points;
      points.emplace_back(newID1, t1);
      points.emplace_back(newID2, t2);
      return AtomicStorePoints(points);
   }
   catch (...)
   {
   }
   return false;
}

bool Model::ExternalTangents(IDType newID1, IDType centerID1, Float64 radius1, IDType newID2, IDType centerID2, Float64 radius2, TangentSign sign)
{
   if (radius1 < 0 || radius2 < 0)
      return false;

   const auto& center1 = GetPoint(centerID1);
   const auto& center2 = GetPoint(centerID2);

   try
   {
      WBFL::Geometry::Point2d t1, t2;
      std::tie(t1, t2) = COGO::ExternalTangents(center1, radius1, center2, radius2, sign);

      std::vector<std::pair<IDType, WBFL::Geometry::Point2d>> points;
      points.emplace_back(newID1, t1);
      points.emplace_back(newID2, t2);
      return AtomicStorePoints(points);
   }
   catch (...)
   {
   }
   return false;
}

bool Model::TangentPoint(IDType newID, IDType centerID, Float64 radius, IDType pointID, TangentSign sign)
{
   if (radius < 0) return false;
   const auto& center = GetPoint(centerID);
   const auto& point = GetPoint(pointID);
   try
   {
      auto newPoint = COGO::TangentPoint(center, radius, point, sign);
      return StorePoint(newID, newPoint);
   }
   catch (...)
   {
   }
   return false;
}

bool Model::AtomicStorePoints(std::vector<std::pair<IDType, WBFL::Geometry::Point2d>>& points)
{
   bool bSucceeded = true;
   auto begin = points.begin();
   auto iter = begin;
   auto end = points.end();
   for (; iter != end; iter++)
   {
      auto& pair(*iter);
      bSucceeded &= StorePoint(pair.first, pair.second);
      if (!bSucceeded) break; // point storage failed... break out so we don't store any more points
   }

   if (!bSucceeded)
   {
      // point storage failed... remove any points that were previously stored
      for (; begin != iter; begin++)
      {
         RemovePoint(begin->first);
      }
   }

   return bSucceeded;
}

std::shared_ptr<Profile> Model::CreateProfile(IDType profileID, std::shared_ptr<Alignment> alignment) const
{
   auto profile = Profile::Create();
   if (alignment)
   {
      alignment->AddProfile(profileID, profile);
   }

   const auto& profile_data = GetProfile(profileID);

   auto begin = profile_data.begin();
   auto iter = begin;
   auto end = profile_data.end();
   for (; iter != end; iter++)
   {
      const auto& profile_element_data(*iter);
      auto element_id = profile_element_data.second;
      switch (profile_element_data.first)
      {
      case ProfileElementType::Point:
      {
         const auto& point = GetProfilePoint(element_id);
         if (profile_data.size() == 1)
         {
            // there is only one element in the profile and it's a profile point
            // create a profile segment
            auto p2 = point;
            if (alignment == nullptr)
            {
               if(p2.GetStation().GetStationZoneIndex() != INVALID_INDEX)
               {
                  THROW_COGO(WBFL_COGO_E_STATION); // if no alignment, station must be normalized
               }
               else
               {
                  p2.SetStation(p2.GetStation().GetValue() + 100);
               }
            }
            else
            {
               auto station = alignment->IncrementStationBy(p2.GetStation(), 100);
               p2.SetStation(station);
            }

            auto segment = ProfileSegment::Create();
            segment->SetStartPoint(point);
            segment->SetEndPoint(p2);
            profile->AddProfileElement(segment);
         }
         else
         {
            // there are multiple elements in the profile - connect this point to the end of the previous element
            // unless this is the first element, then it needs to be connected to the start of the next element
            if (iter == begin)
            {
               // this is the first element
               const auto& next_profile_element_data(*std::next(iter));
               auto p2 = GetStartProfilePoint(next_profile_element_data);

               auto segment = ProfileSegment::Create();
               segment->SetStartPoint(point);
               segment->SetEndPoint(p2);
               profile->AddProfileElement(segment);
            }
            else
            {
               // this profile point is not the first element so connect the end of the previous
               // profile element to this point
               auto nElements = profile->GetProfileElementCount();
               auto last_element = profile->GetProfileElement(nElements - 1);
               const auto& p1 = last_element->GetEndPoint();
               auto segment = ProfileSegment::Create();
               segment->SetStartPoint(p1);
               segment->SetEndPoint(point);
               profile->AddProfileElement(segment);
            }
         }
         break;
      }

      case ProfileElementType::Segment:
      {
         auto segment = CreateProfileSegment(element_id);
         profile->AddProfileElement(segment);
         break;
      }

      case ProfileElementType::VerticalCurve:
      {
         auto vc = CreateVerticalCurve(element_id);
         profile->AddProfileElement(vc);
         break;
      }

      default:
         CHECK(false); // is there a new type?
      }
   }

   // Go through all the surface-profile associations to see if any surfaces
   // are associated with the profile that is being created. If so,
   // create the surface and add it to the profile
   for (const auto& association : m_SurfaceProfileAssociations)
   {
      if (association.second == profileID)
      {
         auto surface = CreateSurface(association.first,profile);
      }
   }

   return profile;
}

const ProfilePoint& Model::GetStartProfilePoint(const std::pair<ProfileElementType, IDType>& elementData) const
{
   const ProfilePoint* point;
   switch (elementData.first)
   {
   case ProfileElementType::Point:
      point = &GetProfilePoint(elementData.second);
      break;

   case ProfileElementType::Segment:
      point = &GetProfilePoint(GetProfileSegment(elementData.second).startID);
      break;

   case ProfileElementType::VerticalCurve:
      point = &GetProfilePoint(GetVerticalCurve(elementData.second).pbgID);
   
   default:
      CHECK(false); // is there a new type?
   }
   return *point;
}

const WBFL::Geometry::Point2d& Model::GetStartPathPoint(const std::pair<PathElementType, IDType>& elementData) const
{
   const WBFL::Geometry::Point2d* point;
   switch (elementData.first)
   {
   case PathElementType::Point:
      point = &GetPoint(elementData.second);
      break;

   case PathElementType::Segment:
      point = &GetPoint(GetPathSegment(elementData.second).startID);
      break;

   case PathElementType::CompoundCurve:
      point = &(CreateCompoundCurve(elementData.second)->GetTS());
      break;

   case PathElementType::CircularCurve:
      point = &(CreateCircularCurve(elementData.second)->GetPC());
      break;

   case PathElementType::TransitionCurve:
      point = &GetPoint(GetTransitionCurve(elementData.second).startID);
      break;

   case PathElementType::CubicSpline:
      point = &GetPoint(GetCubicSpline(elementData.second).front());
      break;

   case PathElementType::Path:
      point = &GetStartPathPoint(GetPath(elementData.second).front());

   default:
      CHECK(false); // is there a new type?
   }

   return *point;
}

std::shared_ptr<Surface> Model::CreateSurface(IDType surfaceID,std::shared_ptr<Profile> profile) const
{
   // create an initialize the basic surface
   const auto& surface_definition = GetSurface(surfaceID);
   auto surface = Surface::Create();
   if (profile)
   {
      profile->AddSurface(surfaceID, surface);
   }

   IndexType nSegments, alignmentPointIdx, profilePointIdx;
   std::tie(nSegments, alignmentPointIdx, profilePointIdx) = surface_definition;
   surface->SetSurfaceTemplateSegmentCount(nSegments);
   surface->SetAlignmentPoint(alignmentPointIdx);
   surface->SetProfileGradePoint(profilePointIdx);

   // create the surface templates and update the surface template segments
   auto found = m_SurfaceTemplates.find(surfaceID);
   if (found != m_SurfaceTemplates.end())
   {
      const auto& surface_template_definitions = found->second;
      for (const auto& surface_template_definition : surface_template_definitions)
      {
         auto surface_template = surface->CreateSurfaceTemplate(surface_template_definition.first);
         IndexType segmentIdx = 0;
         for (const auto& surface_template_segment_definition : surface_template_definition.second)
         {
            Float64 width, slope;
            SurfaceTemplateSegment::SlopeType slopeType;
            std::tie(width, slope, slopeType) = surface_template_segment_definition;
            surface_template->UpdateSegmentParameters(segmentIdx, width, slope, slopeType);
            segmentIdx++;
         }
      }
   }

   auto found_super = m_Superelevations.find(surfaceID);
   if (found_super != m_Superelevations.end())
   {
      // there are some superelevations for this surface
      const auto& superelevation_definitions = found_super->second;
      for (const auto& superelevation_definition : superelevation_definitions)
      {
         auto superelevation = Superelevation::Create(
            superelevation_definition.begin_transition_station, 
            superelevation_definition.begin_full_super_station, 
            superelevation_definition.end_full_super_station, 
            superelevation_definition.end_transition_station, 
            superelevation_definition.rate, 
            superelevation_definition.pivot_point_index, 
            superelevation_definition.begin_transition_type, superelevation_definition.begin_l1, superelevation_definition.begin_l2, 
            superelevation_definition.end_transition_type, superelevation_definition.end_l1, superelevation_definition.end_l2);
         surface->AddSuperelevation(superelevation);
      }
   }

   auto found_widening = m_Widenings.find(surfaceID);
   if (found_widening != m_Widenings.end())
   {
      // there are some widenings for this surface
      const auto& widening_definitions = found_widening->second;
      for (const auto& widening_definition : widening_definitions)
      {
         auto widening = Widening::Create(
            widening_definition.begin_transition_station,
            widening_definition.begin_full_widening_station,
            widening_definition.end_full_widening_station,
            widening_definition.end_transition_station,
            widening_definition.widening, 
            widening_definition.segment1, 
            widening_definition.segment2);
         surface->AddWidening(widening);
      }
   }

   return surface;
}

template <class C> 
bool Model::RemoveItem(C& container,IDType id)
{
   return container.erase(id) == 1 ? true : false;
}

template <class C, class P> 
void Model::CreatePath(IDType id,const C& container, std::shared_ptr<P> path) const
{
   auto found = container.find(id);
   if (found == container.end()) THROW_COGO(WBFL_COGO_E_INVALIDARG);
   const auto& elements = found->second;
   auto begin = elements.begin();
   auto iter = begin;
   auto end = elements.end();

   for (; iter != end; iter++)
   {
      const auto& path_element_data(*iter);
      auto element_id = path_element_data.second;
      switch (path_element_data.first)
      {
      case PathElementType::Point:
      {
         auto point = GetPoint(element_id);
         if (elements.size() == 1)
         {
            // there is only one element in the path and it's a point
            // create a straight line path segment that is due east
            auto p2 = point;
            p2.Offset(100, 0);
            auto segment = PathSegment::Create(point, p2);
            path->AddPathElement(segment);
         }
         else
         {
            // there are multiple path elements - connect this point to the end of the previous element
            // unless this is the first element, then it needs to be connected to the start of the next element
            if (iter == begin)
            {
               // this is the first element
               const auto& next_path_element_data(*std::next(iter));
               auto p2 = GetStartPathPoint(next_path_element_data);

               auto segment = PathSegment::Create(point, p2);
               path->AddPathElement(segment);
            }
            else
            {
               // this point is not the first element so connect it to the end of the previous element
               auto nElements = path->GetPathElementCount();
               auto last_element = path->GetPathElement(nElements - 1);
               const auto& p1 = last_element->GetEndPoint();
               auto segment = PathSegment::Create(p1, point);
               path->AddPathElement(segment);
            }
         }
         break;
      }

      case PathElementType::Segment:
         path->AddPathElement(CreatePathSegment(element_id));
         break;

      case PathElementType::CompoundCurve:
         path->AddPathElement(CreateCompoundCurve(element_id));
         break;

      case PathElementType::CircularCurve:
         path->AddPathElement(CreateCircularCurve(element_id));
         break;

      case PathElementType::TransitionCurve:
         path->AddPathElement(CreateTransitionCurve(element_id));
         break;

      case PathElementType::CubicSpline:
         path->AddPathElement(CreateCubicSpline(element_id));
         break;

      case PathElementType::Path:
         path->AddPathElement(CreatePath(element_id));
         break;

      default:
         CHECK(false); // is there a new path element type?
      }
   }
}

#if defined _UNITTEST
bool Model::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("Model");
   TRY_TESTME(Measure(rlog));
   TRY_TESTME(Locate(rlog));
   TRY_TESTME(Intersect(rlog));
   TRY_TESTME(Project(rlog));
   TRY_TESTME(Divide(rlog));
   TRY_TESTME(Tangent(rlog));
   TESTME_EPILOG("Model");
}

bool Model::Measure(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("Measure");

   // Distance
   Model model;
   model.StorePoint(1, 10.0, 10.0);
   model.StorePoint(2, 40.0, 20.0);
   model.StorePoint(3, 40.0,  0.0);

   try { model.MeasureDistance(1, 20); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_INVALIDARG); }

   try { model.MeasureDistance(10, 2); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_INVALIDARG); }

   TRY_TESTME(IsEqual(model.MeasureDistance(1, 2), 31.62277660));
   TRY_TESTME(IsEqual(model.MeasureDistance(1, 1), 0.0));

   // Angle
   model.ClearPoints();
   model.StorePoint(1, 10, 0);
   model.StorePoint(2, 0, 0);
   model.StorePoint(3, 0, 10);

   TRY_TESTME(model.MeasureAngle(1, 2, 3) == Angle(PI_OVER_2));
   TRY_TESTME(model.MeasureAngle(3, 2, 1) == Angle(3 * PI_OVER_2));

   // Direction
   model.ClearPoints();
   model.StorePoint(1, 10, 10);
   model.StorePoint(2, 20, 20);
   TRY_TESTME(model.MeasureDirection(1, 2) == Direction(Direction::NSDirection::North, 45, 0, 0, Direction::EWDirection::East));
   TRY_TESTME(model.MeasureDirection(1, 1) == Direction(Direction::NSDirection::North, 90, 0, 0, Direction::EWDirection::East));

   // Area
   model.ClearPoints();
   model.StorePoint(1, 0, 0);
   model.StorePoint(2, 10, 0);
   model.StorePoint(3, 10, 10);
   model.StorePoint(4, 0, 10);
   std::vector<IDType> vID{ 1,2,3,4 };
   TRY_TESTME(IsEqual(model.MeasureArea(vID), 100.0));
   vID.pop_back(); // remove two points so there isn't enough to compute an area
   vID.pop_back();
   TRY_TESTME(IsEqual(model.MeasureArea(vID), 0.0));

   TESTME_EPILOG("Measure");
}

bool Model::Locate(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("Locate");

   // Distance and Direction
   Model model;
   model.StorePoint(1, 0, 0);
   model.StorePoint(2, 10, 0);

   TRY_TESTME(model.LocateByDistanceAndDirection(3, 2, 10.0, PI_OVER_2, 0.0));
   TRY_TESTME(model.GetPoint(3) == WBFL::Geometry::Point2d(10, 10));

   TRY_TESTME(model.LocateByDistanceAndDirection(3, 2, 10.0, PI_OVER_2, 5.0) == false);
   TRY_TESTME(model.LocateByDistanceAndDirection(4, 2, 10.0, PI_OVER_2, 5.0));
   TRY_TESTME(model.GetPoint(4) == WBFL::Geometry::Point2d(15, 10));

   TRY_TESTME(model.LocateByDistanceAndDirection(5, 2, 10.0, PI_OVER_2, -5.0));
   TRY_TESTME(model.GetPoint(5) == WBFL::Geometry::Point2d( 5, 10));

   Direction direction(Direction::NSDirection::North, 45, 0, 0, Direction::EWDirection::West);
   TRY_TESTME(model.LocateByDistanceAndDirection(6, 2, 10, direction, 0.0));
   TRY_TESTME(model.GetPoint(6) == WBFL::Geometry::Point2d(2.92893218813, 7.07106781187));

   TRY_TESTME(model.LocateByDistanceAndDirection(7, 2, 10, direction, 5.0));
   TRY_TESTME(model.GetPoint(7) == WBFL::Geometry::Point2d(6.46446609407, 10.6066017178));

   TRY_TESTME(model.LocateByDistanceAndDirection(8, 2, 10, direction, -5.0));
   TRY_TESTME(model.GetPoint(8) == WBFL::Geometry::Point2d(-0.60660171781, 3.53553390593));

   TRY_TESTME(model.LocateByDistanceAndDirection(9, 2, -10, direction, 0.0));
   TRY_TESTME(model.GetPoint(9) == WBFL::Geometry::Point2d(17.07106781187, -7.07106781187));

   // Distance and Angle
   model.ClearPoints();
   model.StorePoint(1, 10, 10);
   model.StorePoint(2, 0, 0);

   TRY_TESTME(model.LocateByDistanceAndAngle(3, 1, 2, 10.0, M_PI, 0.0));
   TRY_TESTME(model.GetPoint(3) == WBFL::Geometry::Point2d(-7.07106781187, -7.07106781187));

   TRY_TESTME(model.LocateByDistanceAndAngle(4, 1, 2, 10.0, M_PI/4, 0.0));
   TRY_TESTME(model.GetPoint(4) == WBFL::Geometry::Point2d(0,10));

   Angle angle(225, 0, 0);
   TRY_TESTME(model.LocateByDistanceAndAngle(5, 1, 2, 10.0, angle, -5.0));
   TRY_TESTME(model.GetPoint(5) == WBFL::Geometry::Point2d(3.53553390594, -13.53553390594));

   TRY_TESTME(model.LocateByDistanceAndAngle(6, 1, 2, -10.0, angle, -5.0));
   TRY_TESTME(model.GetPoint(6) == WBFL::Geometry::Point2d(3.53553390594, 6.46446609406));

   // Distance and Deflection Angle
   model.ClearPoints();
   model.StorePoint(1, 10, 10);
   model.StorePoint(2, 0, 0);

   TRY_TESTME(model.LocateByDistanceAndDeflectionAngle(3, 1, 2, 10, M_PI, 0.0));
   TRY_TESTME(model.GetPoint(3) == WBFL::Geometry::Point2d(7.07106781187, 7.07106781187));

   TRY_TESTME(model.LocateByDistanceAndDeflectionAngle(4, 1, 2, 10, M_PI / 4, 0.0));
   TRY_TESTME(model.GetPoint(4) == WBFL::Geometry::Point2d(0, -10));

   Angle defAngle(45, 0, 0);
   TRY_TESTME(model.LocateByDistanceAndDeflectionAngle(5, 1, 2, 10, defAngle, -5.0));
   TRY_TESTME(model.GetPoint(5) == WBFL::Geometry::Point2d(3.53553390594,-13.53553390594));

   TRY_TESTME(model.LocateByDistanceAndDeflectionAngle(6, 1, 2, -10, defAngle, -5.0));
   TRY_TESTME(model.GetPoint(6) == WBFL::Geometry::Point2d(3.53553390594, 6.46446609406));

   // Point On Line
   model.ClearPoints();
   model.StorePoint(1, 10, 10);
   model.StorePoint(2, 20, 20);

   TRY_TESTME(model.LocatePointOnLine(3, 1, 2, 20, 0));
   TRY_TESTME(model.GetPoint(3) == WBFL::Geometry::Point2d(24.1421356237, 24.1421356237));

   TRY_TESTME(model.LocatePointOnLine(4, 1, 2, -20, 0));
   TRY_TESTME(model.GetPoint(4) == WBFL::Geometry::Point2d(-4.1421356237, -4.1421356237));

   TRY_TESTME(model.LocatePointOnLine(5, 1, 2, 10, 5));
   TRY_TESTME(model.GetPoint(5) == WBFL::Geometry::Point2d(20.6066017178, 13.5355339059));

   TRY_TESTME(model.LocatePointOnLine(6, 1, 2, 10, -5));
   TRY_TESTME(model.GetPoint(6) == WBFL::Geometry::Point2d(13.5355339059, 20.6066017178));

   // ParallelLineSegment and ParallelLineByPoints
   model.Clear();
   model.StorePoint(1, 0, 0);
   model.StorePoint(2, 20, 20);
   model.StorePathSegment(1, 1, 2);

   TRY_TESTME(model.LocateParallelLineSegment(2, 3, 4, 1, 5.0));
   TRY_TESTME(model.GetPoint(3) == WBFL::Geometry::Point2d(3.53553390594, -3.53553390594));
   TRY_TESTME(model.GetPoint(4) == WBFL::Geometry::Point2d(23.5355339059, 16.4644660941));
   TRY_TESTME(model.CreatePathSegment(2)->GetStartPoint() == WBFL::Geometry::Point2d(3.53553390594, -3.53553390594));
   TRY_TESTME(model.CreatePathSegment(2)->GetEndPoint() == WBFL::Geometry::Point2d(23.5355339059, 16.4644660941));

   TRY_TESTME(model.LocateParallelLineSegment(3, 5, 6, 1, -5.0));
   TRY_TESTME(model.GetPoint(5) == WBFL::Geometry::Point2d(-3.53553390594, 3.53553390594));
   TRY_TESTME(model.GetPoint(6) == WBFL::Geometry::Point2d(16.4644660941, 23.5355339059));
   TRY_TESTME(model.CreatePathSegment(3)->GetStartPoint() == WBFL::Geometry::Point2d(-3.53553390594, 3.53553390594));
   TRY_TESTME(model.CreatePathSegment(3)->GetEndPoint() == WBFL::Geometry::Point2d(16.4644660941, 23.5355339059));


   TRY_TESTME(model.LocateParallelLineByPoints(13, 14, 1, 2, 5.0));
   TRY_TESTME(model.GetPoint(13) == WBFL::Geometry::Point2d(3.53553390594,-3.53553390594));
   TRY_TESTME(model.GetPoint(14) == WBFL::Geometry::Point2d(23.5355339059, 16.4644660940));

   TESTME_EPILOG("Locate");
}

bool Model::Intersect(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("Intersect");

   Model model;

   // IntersectBearings
   model.StorePoint(1, 0, 0);
   model.StorePoint(2, 10, 0);
   TRY_TESTME(model.IntersectBearings(3, 1, M_PI / 4, 0.0, 2, 3 * M_PI / 4, 0));
   TRY_TESTME(model.GetPoint(3) == WBFL::Geometry::Point2d(5,5));

   TRY_TESTME(model.IntersectBearings(4, 1, M_PI / 4, 5.0, 2, 3 * M_PI / 4, 5));
   TRY_TESTME(model.GetPoint(4) == WBFL::Geometry::Point2d(12.0710678119, 5));

   TRY_TESTME(model.IntersectBearings(5, 1, M_PI / 4, 0.0, 2, M_PI / 4, 0) == false);

   // IntersectBearingAndCircle
   model.Clear();
   model.StorePoint(1, 0, 0);
   model.StorePoint(2, 10, 10);
   model.StorePoint(3, 15, 15);

   TRY_TESTME(model.IntersectBearingAndCircle(4, 1, M_PI/4, 0.0, 2, 5.0, 3));
   TRY_TESTME(model.GetPoint(4) == WBFL::Geometry::Point2d(13.5355339059, 13.5355339059));

   TRY_TESTME(model.IntersectBearingAndCircle(5, 1, M_PI / 4, 0.0, 2, 5.0, 1));
   TRY_TESTME(model.GetPoint(5) == WBFL::Geometry::Point2d(6.46446609406, 6.46446609406));

   TRY_TESTME(model.IntersectBearingAndCircle(6, 1, PI_OVER_2, 5.0, 2, 5.0, 1));
   TRY_TESTME(model.GetPoint(6) == WBFL::Geometry::Point2d(5, 10));

   TRY_TESTME(model.IntersectBearingAndCircle(7, 1, PI_OVER_2, 0.0, 2, 5.0, 1) == false);

   // IntersectCircles
   model.Clear();
   model.StorePoint(1, 0, 0);
   model.StorePoint(2, 10, 10);
   model.StorePoint(3, 20, 20);
   model.StorePoint(4, 20, 0);
   model.StorePoint(5, 0, 20);

   TRY_TESTME(model.IntersectCircles(6, 2, 10.0, 3, 10.0, 4));
   TRY_TESTME(model.GetPoint(6) == WBFL::Geometry::Point2d(20, 10));

   TRY_TESTME(model.IntersectCircles(7, 2, 20.0, 6, 10.0, 4));
   TRY_TESTME(model.GetPoint(7) == WBFL::Geometry::Point2d(30, 10));

   TRY_TESTME(model.IntersectCircles(8, 2, 20.0, 6, 20.0, 5));
   TRY_TESTME(model.GetPoint(8) == WBFL::Geometry::Point2d(15, 29.3649167));

   TRY_TESTME(model.IntersectCircles(9, 2, 2.0, 3, 2.0, 4) == false);

   // IntersectLineByPointsAndCircle
   model.Clear();
   model.StorePoint(1, 0, 0);
   model.StorePoint(2, 10, 10);
   model.StorePoint(3, 15, 15);
   model.StorePoint(10, 0, 20);

   TRY_TESTME(model.IntersectLineByPointsAndCircle(4, 1, 3, 0.0, 2, 5.0, 3));
   TRY_TESTME(model.GetPoint(4) == WBFL::Geometry::Point2d(13.5355339059, 13.5355339059));

   TRY_TESTME(model.IntersectLineByPointsAndCircle(5, 1, 3, 0.0, 2, 5.0, 1));
   TRY_TESTME(model.GetPoint(5) == WBFL::Geometry::Point2d(6.46446609406, 6.46446609406));

   TRY_TESTME(model.IntersectLineByPointsAndCircle(6, 1, 10, 5.0, 2, 5.0, 1));
   TRY_TESTME(model.GetPoint(6) == WBFL::Geometry::Point2d(5,10));

   TRY_TESTME(model.IntersectLineByPointsAndCircle(7, 1, 10, 0.0, 2, 5.0, 1) == false);

   // IntersectLinesByPoints
   model.Clear();
   model.StorePoint(1, 0, 0);
   model.StorePoint(2, 10, 0);
   model.StorePoint(30, 10, 10);
   model.StorePoint(40, 0, 10);

   TRY_TESTME(model.IntersectLinesByPoints(3, 1, 30, 0.0, 2, 40, 0.0));
   TRY_TESTME(model.GetPoint(3) == WBFL::Geometry::Point2d(5, 5));

   TRY_TESTME(model.IntersectLinesByPoints(4, 1, 30, 5.0, 2, 40, 5.0));
   TRY_TESTME(model.GetPoint(4) == WBFL::Geometry::Point2d(12.0710678119, 5));

   TRY_TESTME(model.IntersectLinesByPoints(5, 1, 2, 0.0, 30, 40, 0.0) == false);

   // IntersectPathSegments
   model.Clear();
   model.StorePoint(1, 0, 0);
   model.StorePoint(2, 10, 0);
   model.StorePoint(30, 10, 10);
   model.StorePoint(40, 0, 10);
   model.StorePathSegment(1, 1, 30);
   model.StorePathSegment(2, 2, 40);

   TRY_TESTME(model.IntersectPathSegments(3, 1, 0.0, 2, 0.0));
   TRY_TESTME(model.GetPoint(3) == WBFL::Geometry::Point2d(5,5));

   TRY_TESTME(model.IntersectPathSegments(4, 1, 5.0, 2, 5.0));
   TRY_TESTME(model.GetPoint(4) == WBFL::Geometry::Point2d(12.0710678119, 5));

   // make lines parallel
   auto p30 = model.GetPoint(30);// ->Move(0, 10);
   auto p40 = model.GetPoint(40);// ->Move(10, 10);
   p30.Move(0, 10);
   p40.Move(10, 10);
   model.ReplacePoint(30, p30);
   model.ReplacePoint(40, p40);
   TRY_TESTME(model.IntersectPathSegments(5, 1, 0.0, 2, 0.0) == false);

   // IntersectLineSegmentAndCircle
   model.Clear();
   model.StorePoint(1, 0, 0);
   model.StorePoint(2, 10, 10);
   model.StorePoint(3, 15, 15);
   model.StorePoint(10, 0, 20);
   model.StorePathSegment(1, 1, 3);
   model.StorePathSegment(2, 1, 10);

   TRY_TESTME(model.IntersectPathSegmentAndCircle(4, 1, 0.0, 2, 5.0, 3));
   TRY_TESTME(model.GetPoint(4) == WBFL::Geometry::Point2d(13.5355339059, 13.5355339059));

   TRY_TESTME(model.IntersectPathSegmentAndCircle(5, 1, 0.0, 2, 5.0, 1));
   TRY_TESTME(model.GetPoint(5) == WBFL::Geometry::Point2d(6.46446609406, 6.46446609406));

   TRY_TESTME(model.IntersectPathSegmentAndCircle(6, 2, 5.0, 2, 5.0, 1));
   TRY_TESTME(model.GetPoint(6) == WBFL::Geometry::Point2d(5, 10));

   TRY_TESTME(model.IntersectPathSegmentAndCircle(7, 2, 0.0, 2, 5.0, 1) == false);

   TESTME_EPILOG("Intersect");
}

bool Model::Project(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("Project");

   Model model;

   model.StorePoint(1, 0, 1000);
   model.StorePoint(2, 700, 1000);
   model.StorePoint(3, 1000, 700);

   // ProjectPointOnCompoundCurve
   model.StoreCompoundCurve(1, 1,2,3,500,100,TransitionCurveType::Clothoid,200,TransitionCurveType::Clothoid);
   TRY_TESTME(model.ProjectPointOnCompoundCurve(5, 2, 1));
   TRY_TESTME(model.GetPoint(5) == WBFL::Geometry::Point2d(683.12870529355951, 959.95042556846295));

   // ProjectPointOnLineByPoints
   model.Clear();
   model.StorePoint(1, 0, 0);
   model.StorePoint(2, 5, 5);
   model.StorePoint(3, 6, 12);
   model.StorePoint(4, 12, 6);

   TRY_TESTME(model.ProjectPointOnLineByPoints(5, 3, 1, 2, 0.0));
   TRY_TESTME(model.GetPoint(5) == WBFL::Geometry::Point2d(9, 9));

   TRY_TESTME(model.ProjectPointOnLineByPoints(6, 4, 1, 2, 0.0));
   TRY_TESTME(model.GetPoint(6) == WBFL::Geometry::Point2d(9, 9));

   TRY_TESTME(model.ProjectPointOnLineByPoints(7, 3, 1, 2, 4.24264068712));
   TRY_TESTME(model.GetPoint(7) == WBFL::Geometry::Point2d(12, 6));

   TRY_TESTME(model.ProjectPointOnLineByPoints(8, 4, 1, 2, -4.24264068712));
   TRY_TESTME(model.GetPoint(8) == WBFL::Geometry::Point2d(6, 12));

   // ProjectPointOnPathSegment
   model.StorePathSegment(1, 1, 2);
   TRY_TESTME(model.ProjectPointOnPathSegment(9, 3, 1, 0.0));
   TRY_TESTME(model.GetPoint(9) == WBFL::Geometry::Point2d(9,9));

   TESTME_EPILOG("Project");
}

#include <CoordGeom/PathSegment.h>
bool Model::Divide(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("Divide");

   Model model;

   // Test DivideArc
   model.StorePoint(1, 0, 0);
   model.StorePoint(2, 10, 0);
   model.StorePoint(3, -10, 0);
   TRY_TESTME(model.DivideArc(4, 1, 2, 1, 3, -1) == false);
   TRY_TESTME(model.DivideArc(4, 1, 2, 1, 3, 0) == false);
   TRY_TESTME(model.DivideArc(4, 1, 2, 1, 3, 1) == false);
   TRY_TESTME_CATCH(model.DivideArc(4, 1, -2, 1, 3, 4));
   TRY_TESTME_CATCH(model.DivideArc(4, 1, 2, -1, 3, 4));
   TRY_TESTME_CATCH(model.DivideArc(4, 1, 2, 1, -3, 4));
   TRY_TESTME(model.DivideArc(1, 1, 2, 1, 3, 4) == false);
   TRY_TESTME(model.DivideArc(4, 0, 2, 1, 3, 4) == false);
   TRY_TESTME(model.DivideArc(4, 1, 1, 1, 3, 4) == false);
   TRY_TESTME(model.DivideArc(4, 1, 2, 1, 1, 4) == false);
   TRY_TESTME(model.DivideArc(4, 1, 2, 1, 3, 4) == true);
   TRY_TESTME(model.GetPoint(4) == WBFL::Geometry::Point2d(7.07106781187, 7.07106781187));
   TRY_TESTME(model.GetPoint(5) == WBFL::Geometry::Point2d(0,10));
   TRY_TESTME(model.GetPoint(6) == WBFL::Geometry::Point2d(-7.07106781187, 7.07106781187));

   // Test DivideBetweenPoints
   model.Clear();
   model.StorePoint(1, 10, 10);
   model.StorePoint(2, 110, 110);
   TRY_TESTME(model.DivideBetweenPoints(3, 1, 1, 2, 10));
   for (IDType i = 3; i <= 11; i++)
   {
      TRY_TESTME(model.GetPoint(i) == WBFL::Geometry::Point2d((Float64)(i-1)*10, (Float64)(i-1)*10));
      i++;
   }

   // Test DivideLineSegment
   model.Clear();
   model.StorePoint(1, 10, 10);
   model.StorePoint(2, 110, 110);
   model.StorePathSegment(1, 1, 2);

   TRY_TESTME(model.DivideLineSegment(3, 1, 1, -1) == false);
   TRY_TESTME(model.DivideLineSegment(3, 1, 1, 0) == false);
   TRY_TESTME(model.DivideLineSegment(3, 1, 1, 1) == false);
   TRY_TESTME(model.DivideLineSegment(3, 0, 1, 10) == false);
   TRY_TESTME_CATCH(model.DivideLineSegment(3, 1, -1, 10));
   TRY_TESTME(model.DivideLineSegment(1, 1, 1, 10) == false);

   TRY_TESTME(model.DivideLineSegment(3, 1, 1, 10) == true);
   for (IDType i = 3; i <= 11; i++)
   {
      TRY_TESTME(model.GetPoint(i) == WBFL::Geometry::Point2d((Float64)(i - 1) * 10, (Float64)(i - 1) * 10));
      i++;
   }

   // Test CompoundCurve
   model.StorePoint(101, 0, 1000);
   model.StorePoint(102, 700, 1000);
   model.StorePoint(103, 1000, 700);

   model.StoreCompoundCurve(1, 101, 102, 103, 500, 100, TransitionCurveType::Clothoid, 200, TransitionCurveType::Clothoid);

   TRY_TESTME(model.DivideCompoundCurve(150, 1, 1, -1) == false);
   TRY_TESTME(model.DivideCompoundCurve(150, 0, 1, 5) == false);
   TRY_TESTME_CATCH(model.DivideCompoundCurve(150, 1, -1, 5));
   TRY_TESTME(model.DivideCompoundCurve(99, 1, 1, 5) == false);
   TRY_TESTME(model.DivideCompoundCurve(150, 1, 1, 10) == true);

   TRY_TESTME(model.GetPoint(150) == WBFL::Geometry::Point2d(493.30080, 999.46724));
   TRY_TESTME(model.GetPoint(151) == WBFL::Geometry::Point2d(547.42511, 995.74397));
   TRY_TESTME(model.GetPoint(152) == WBFL::Geometry::Point2d(600.87402, 986.49482));
   TRY_TESTME(model.GetPoint(153) == WBFL::Geometry::Point2d(653.00647, 971.51016));
   TRY_TESTME(model.GetPoint(154) == WBFL::Geometry::Point2d(703.20889, 950.96633));
   TRY_TESTME(model.GetPoint(155) == WBFL::Geometry::Point2d(750.89045, 925.10512));
   TRY_TESTME(model.GetPoint(156) == WBFL::Geometry::Point2d(795.54108, 894.29971));
   TRY_TESTME(model.GetPoint(157) == WBFL::Geometry::Point2d(837.31329, 859.67354));
   TRY_TESTME(model.GetPoint(158) == WBFL::Geometry::Point2d(876.98033, 822.64293));

   // Divide Path
   auto curve = model.CreateCompoundCurve(1);
   model.StorePoint(200, curve->GetTS());
   model.StorePoint(201, curve->GetST());

   std::vector<std::pair<PathElementType, IDType>> vPathElements;
   vPathElements.emplace_back(PathElementType::Point, 101);
   vPathElements.emplace_back(PathElementType::Point, 200);
   vPathElements.emplace_back(PathElementType::CompoundCurve, 1);
   vPathElements.emplace_back(PathElementType::Point, 201);
   vPathElements.emplace_back(PathElementType::Point, 103);
   model.StorePath(1, vPathElements);
   model.DividePath(350, 1, 1, 10,0.0,-1.0);
   TRY_TESTME(model.GetPoint(350) == WBFL::Geometry::Point2d(110.11756, 1000.00000));
   TRY_TESTME(model.GetPoint(351) == WBFL::Geometry::Point2d(220.23513, 1000.00000));
   TRY_TESTME(model.GetPoint(352) == WBFL::Geometry::Point2d(330.35269, 1000.00000));
   TRY_TESTME(model.GetPoint(353) == WBFL::Geometry::Point2d(440.47026, 999.99999));
   TRY_TESTME(model.GetPoint(354) == WBFL::Geometry::Point2d(550.41581, 995.38307));
   TRY_TESTME(model.GetPoint(355) == WBFL::Geometry::Point2d(657.33575, 969.98482));
   TRY_TESTME(model.GetPoint(356) == WBFL::Geometry::Point2d(756.12468, 921.84240));
   TRY_TESTME(model.GetPoint(357) == WBFL::Geometry::Point2d(843.08205, 854.50477));
   TRY_TESTME(model.GetPoint(358) == WBFL::Geometry::Point2d(922.13512, 777.86488));

   TESTME_EPILOG("Divide");
}

bool Model::Tangent(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("Tangent");

   Model model;

   // Test ExternalTangent
   model.StorePoint(1, 10, 10);
   model.StorePoint(2, 40, 10);

   // Test some error cases
   TRY_TESTME(model.ExternalTangents(3, 1, -20.0, 4, 2, 5.0, TangentSign::CW) == false); // COGO_E_RADIUS
   TRY_TESTME(model.ExternalTangents(3, 1, 20.0, 4, 2, -5.0, TangentSign::CW) == false); // COGO_E_RADIUS
   TRY_TESTME_CATCH(model.ExternalTangents(3, 10, 20.0, 4, 2, 5.0, TangentSign::CW)); // COGO_E_POINTNOTFOUND
   TRY_TESTME_CATCH(model.ExternalTangents(3, 1, 20.0, 4, 20, 5.0, TangentSign::CW)); // COGO_E_POINTNOTFOUND
   TRY_TESTME(model.ExternalTangents(1, 1, 20.0, 4, 2, 5.0, TangentSign::CW) == false); // COGO_E_POINTALREADYDEFINED
   TRY_TESTME(model.ExternalTangents(3, 1, 20.0, 2, 2, 5.0, TangentSign::CW) == false); // COGO_E_POINTALREADYDEFINED
   TRY_TESTME(model.ExternalTangents(3, 1, 20.0, 4, 1, 5.0, TangentSign::CW) == false); // COGO_E_COINCIDENTPOINTS

   // define the big circle first
   TRY_TESTME(model.ExternalTangents(3, 1, 20.0, 4, 2, 5.0, TangentSign::CW));
   TRY_TESTME(model.GetPoint(3) == WBFL::Geometry::Point2d(20, 27.3205));
   TRY_TESTME(model.GetPoint(4) == WBFL::Geometry::Point2d(42.5, 14.33013));

   TRY_TESTME(model.ExternalTangents(5, 1, 20.0, 6, 2, 5.0, TangentSign::CCW));
   TRY_TESTME(model.GetPoint(5) == WBFL::Geometry::Point2d(20, 27.3205));
   TRY_TESTME(model.GetPoint(6) == WBFL::Geometry::Point2d(42.5, 14.33013));

   // define the small circle first
   TRY_TESTME(model.ExternalTangents(7, 2, 5.0, 8, 1, 20.0, TangentSign::CW));
   TRY_TESTME(model.GetPoint(7) == WBFL::Geometry::Point2d(42.5, 14.33013));
   TRY_TESTME(model.GetPoint(8) == WBFL::Geometry::Point2d(20, 27.3205));

   TRY_TESTME(model.ExternalTangents(9, 2, 5.0, 10, 1, 20.0, TangentSign::CCW));
   TRY_TESTME(model.GetPoint(9) == WBFL::Geometry::Point2d(42.5, 14.33013));
   TRY_TESTME(model.GetPoint(10) == WBFL::Geometry::Point2d(20, 27.3205));

   // rotate both circles 180deg around (0,0)
   // (make x = -x)
   auto p1 = model.GetPoint(1);
   auto p2 = model.GetPoint(2);
   p1.Move(-10, 10);
   p2.Move(-40, 10);
   model.ReplacePoint(1, p1);
   model.ReplacePoint(2, p2);


   // big circle first
   TRY_TESTME(model.ExternalTangents(11, 1, 20.0, 12, 2, 5.0, TangentSign::CW));
   TRY_TESTME(model.GetPoint(11) == WBFL::Geometry::Point2d(-20.0, -7.3205));
   TRY_TESTME(model.GetPoint(12) == WBFL::Geometry::Point2d(-42.5, 5.66987));

   TRY_TESTME(model.ExternalTangents(13, 1, 20.0, 14, 2, 5.0, TangentSign::CCW));
   TRY_TESTME(model.GetPoint(13) == WBFL::Geometry::Point2d(-20.0, -7.3205));
   TRY_TESTME(model.GetPoint(14) == WBFL::Geometry::Point2d(-42.5, 5.66987));

   // small circle first
   TRY_TESTME(model.ExternalTangents(15, 2, 5.0, 16, 1, 20.0, TangentSign::CW));
   TRY_TESTME(model.GetPoint(15) == WBFL::Geometry::Point2d(-42.5, 5.66987));
   TRY_TESTME(model.GetPoint(16) == WBFL::Geometry::Point2d(-20.0, -7.3205));

   TRY_TESTME(model.ExternalTangents(17, 2, 5.0, 18, 1, 20.0, TangentSign::CCW));
   TRY_TESTME(model.GetPoint(17) == WBFL::Geometry::Point2d(-42.5, 5.66987));
   TRY_TESTME(model.GetPoint(18) == WBFL::Geometry::Point2d(-20.0, -7.3205));

   // rotate both (original) circles 90deg around (0,0)
   // (make Y = x, X = -Y)
   p1 = model.GetPoint(1);
   p2 = model.GetPoint(2);
   p1.Move(-10, 10);
   p2.Move(-10, 40);
   model.ReplacePoint(1, p1);
   model.ReplacePoint(2, p2);

   // big circle first
   TRY_TESTME(model.ExternalTangents(19, 1, 20.0, 20, 2, 5.0, TangentSign::CW));
   TRY_TESTME(model.GetPoint(19) == WBFL::Geometry::Point2d(-27.3205, 20.0));
   TRY_TESTME(model.GetPoint(20) == WBFL::Geometry::Point2d(-14.33013, 42.5));

   TRY_TESTME(model.ExternalTangents(21, 1, 20.0, 22, 2, 5.0, TangentSign::CCW));
   TRY_TESTME(model.GetPoint(21) == WBFL::Geometry::Point2d(-27.3205, 20.0));
   TRY_TESTME(model.GetPoint(22) == WBFL::Geometry::Point2d(-14.33013, 42.5));

   // small circle first
   TRY_TESTME(model.ExternalTangents(23, 2, 5.0, 24, 1, 20.0, TangentSign::CW));
   TRY_TESTME(model.GetPoint(23) == WBFL::Geometry::Point2d(-14.33013, 42.5));
   TRY_TESTME(model.GetPoint(24) == WBFL::Geometry::Point2d(-27.3205, 20.0));

   TRY_TESTME(model.ExternalTangents(25, 2, 5.0, 26, 1, 20.0, TangentSign::CCW));
   TRY_TESTME(model.GetPoint(25) == WBFL::Geometry::Point2d(-14.33013, 42.5));
   TRY_TESTME(model.GetPoint(26) == WBFL::Geometry::Point2d(-27.3205, 20.0));

   /////////////////////////////////////////////////////////////////////////////////////////

   // Quadrants   ^
   //             |
   //       2     |     1
   //             |
   //   ----------+----------->
   //             |
   //       3     |     4
   //             |

   // 2 Equal radius circles, one centered at the origin, one at 45deg in quadrant 1
   p1 = model.GetPoint(1);
   p2 = model.GetPoint(2);
   p1.Move(0, 0);
   p2.Move(10, 10);
   model.ReplacePoint(1, p1);
   model.ReplacePoint(2, p2);
   TRY_TESTME(model.ExternalTangents(27, 1, 5.0, 28, 2, 5.0, TangentSign::CW));
   TRY_TESTME(model.GetPoint(27) == WBFL::Geometry::Point2d(-3.53553, 3.53553));
   TRY_TESTME(model.GetPoint(28) == WBFL::Geometry::Point2d(6.46447, 13.53553));

   TRY_TESTME(model.ExternalTangents(29, 1, 5.0, 30, 2, 5.0, TangentSign::CCW));
   TRY_TESTME(model.GetPoint(29) == WBFL::Geometry::Point2d(-3.53553, 3.53553));
   TRY_TESTME(model.GetPoint(30) == WBFL::Geometry::Point2d(6.46447, 13.53553));

   // 2 Equal radius circles, one centered at the origin, one at 45deg in quadrant 2
   p1 = model.GetPoint(1);
   p2 = model.GetPoint(2);
   p1.Move(0, 0);
   p2.Move(-10, 10);
   model.ReplacePoint(1, p1);
   model.ReplacePoint(2, p2);
   
   TRY_TESTME(model.ExternalTangents(31, 1, 5.0, 32, 2, 5.0, TangentSign::CW));
   TRY_TESTME(model.GetPoint(31) == WBFL::Geometry::Point2d(-3.53553, -3.53553));
   TRY_TESTME(model.GetPoint(32) == WBFL::Geometry::Point2d(-13.53553, 6.46447));

   TRY_TESTME(model.ExternalTangents(33, 1, 5.0, 34, 2, 5.0, TangentSign::CCW));
   TRY_TESTME(model.GetPoint(33) == WBFL::Geometry::Point2d(-3.53553, -3.53553));
   TRY_TESTME(model.GetPoint(34) == WBFL::Geometry::Point2d(-13.53553, 6.46447));

   // 2 Equal radius circles, one centered at the origin, one at 45deg in quadrant 3
   p1 = model.GetPoint(1);
   p2 = model.GetPoint(2);
   p1.Move(0, 0);
   p2.Move(-10, -10);
   model.ReplacePoint(1, p1);
   model.ReplacePoint(2, p2);

   TRY_TESTME(model.ExternalTangents(35, 1, 5.0, 36, 2, 5.0, TangentSign::CW));
   TRY_TESTME(model.GetPoint(35) == WBFL::Geometry::Point2d( 3.53553, -3.53553));
   TRY_TESTME(model.GetPoint(36) == WBFL::Geometry::Point2d(-6.46447, -13.53553));

   TRY_TESTME(model.ExternalTangents(37, 1, 5.0, 38, 2, 5.0, TangentSign::CCW));
   TRY_TESTME(model.GetPoint(37) == WBFL::Geometry::Point2d(3.53553, -3.53553));
   TRY_TESTME(model.GetPoint(38) == WBFL::Geometry::Point2d(-6.46447, -13.53553));

   // 2 Equal radius circles, one centered at the origin, one at 45deg in quadrant 4
   p1 = model.GetPoint(1);
   p2 = model.GetPoint(2);
   p1.Move(0, 0);
   p2.Move(10, -10);
   model.ReplacePoint(1, p1);
   model.ReplacePoint(2, p2);

   TRY_TESTME(model.ExternalTangents(39, 1, 5.0, 40, 2, 5.0, TangentSign::CW));
   TRY_TESTME(model.GetPoint(39) == WBFL::Geometry::Point2d(3.53553, 3.53553));
   TRY_TESTME(model.GetPoint(40) == WBFL::Geometry::Point2d(13.53553 ,-6.46447));

   TRY_TESTME(model.ExternalTangents(41, 1, 5.0, 42, 2, 5.0, TangentSign::CCW));
   TRY_TESTME(model.GetPoint(41) == WBFL::Geometry::Point2d(3.53553, 3.53553));
   TRY_TESTME(model.GetPoint(42) == WBFL::Geometry::Point2d(13.53553, -6.46447));

   // Test CrossingTangent
   model.Clear();

   model.StorePoint(1, 10, 10);
   model.StorePoint(2, 40, 10);

   TRY_TESTME(model.CrossingTangents(3, 1, -20.0, 4, 2, 5.0, TangentSign::CW) == false);
   TRY_TESTME(model.CrossingTangents(3, 1, 20.0, 4, 2, -5.0, TangentSign::CW) == false);
   TRY_TESTME_CATCH(model.CrossingTangents(3, 10, 20.0, 4, 2, 5.0, TangentSign::CW));
   TRY_TESTME_CATCH(model.CrossingTangents(3, 1, 20.0, 4, 20, 5.0, TangentSign::CW));
   TRY_TESTME(model.CrossingTangents(1, 1, 20.0, 4, 2, 5.0, TangentSign::CW) == false);
   TRY_TESTME(model.CrossingTangents(3, 1, 20.0, 2, 2, 5.0, TangentSign::CW) == false);
   TRY_TESTME(model.CrossingTangents(3, 1, 20.0, 4, 1, 5.0, TangentSign::CW) == false);

   // define the big circle first
   TRY_TESTME(model.CrossingTangents(3, 1, 20.0, 4, 2, 5.0, TangentSign::CW));
   TRY_TESTME(model.GetPoint(3) == WBFL::Geometry::Point2d(26.66666, -1.05541));
   TRY_TESTME(model.GetPoint(4) == WBFL::Geometry::Point2d(44.16667, 12.76385));

   TRY_TESTME(model.CrossingTangents(5, 1, 20.0, 6, 2, 5.0, TangentSign::CCW));
   TRY_TESTME(model.GetPoint(5) == WBFL::Geometry::Point2d(26.66666, 21.055415));
   TRY_TESTME(model.GetPoint(6) == WBFL::Geometry::Point2d(44.16667, 7.23615));

   // Test Point
   Float64 radius = 20;

   model.Clear();
   model.StorePoint(1, 10, 10);
   model.StorePoint(2, 10 + radius * sqrt(2.), 10);
   model.StorePoint(3, 10 + radius, 10 + radius);
   model.StorePoint(999, 5, 5);

   TRY_TESTME(model.TangentPoint(4, 1, -20.0, 2, TangentSign::CW) == false);
   TRY_TESTME_CATCH(model.TangentPoint(4, 10, 20.0, 2, TangentSign::CW));
   TRY_TESTME_CATCH(model.TangentPoint(4, 1, 20.0, 4, TangentSign::CW));
   TRY_TESTME(model.TangentPoint(1, 1, 20.0, 2, TangentSign::CW) == false);
   TRY_TESTME(model.TangentPoint(4, 1, 20.0, 1, TangentSign::CW) == false);
   TRY_TESTME(model.TangentPoint(4, 1, 20.0, 999, TangentSign::CW) == false);

   TRY_TESTME(model.TangentPoint(4, 1, radius, 2, TangentSign::CW));
   TRY_TESTME(model.GetPoint(4) == WBFL::Geometry::Point2d(24.14214, -4.14214));

   TRY_TESTME(model.TangentPoint(5, 1, radius, 2, TangentSign::CCW));
   TRY_TESTME(model.GetPoint(5) == WBFL::Geometry::Point2d(24.14214, 24.14214));

   TRY_TESTME(model.TangentPoint(6, 1, radius, 3, TangentSign::CW));
   TRY_TESTME(model.GetPoint(6) == WBFL::Geometry::Point2d(30, 10));

   TRY_TESTME(model.TangentPoint(7, 1, radius, 3, TangentSign::CCW));
   TRY_TESTME(model.GetPoint(7) == WBFL::Geometry::Point2d(10, 30));

   TESTME_EPILOG("Tangent");
}

#endif // _UNITTEST