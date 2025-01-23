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
      for (const auto& [back,ahead] : vEquations)
      {
         alignment->AddStationEquation(back,ahead);
      }
   }

   // Go through all the profile-alignment associations to see if any profiles
   // are associated with the alignment that is being created. If so,
   // create the profile and add it to the alignment
   for (const auto& [profileID,association_alignmentID] : m_ProfileAlignmentAssociations)
   {
      if (association_alignmentID == alignmentID)
      {
         auto profile = CreateProfile(profileID, alignment);
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

bool Model::SetAlignmentReferenceStation(IDType alignmentID, const Station& station)
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
      auto [iter,bSuccess] = m_StationEquations.emplace(alignmentID, std::vector<StationEquationDefinition>());
      if (bSuccess == false) THROW_COGO(WBFL_COGO_E_INVALIDARG);

      found = iter;
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
   auto [nSegments,alignmentPointIdx,profilePointIdx] = GetSurface(surfaceID); // throws on bad ID

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
      auto [iter,bSuccess] = m_SurfaceTemplates.emplace(surfaceID, vSurfaceTemplates);
      return bSuccess;
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

   auto& [ID, surface_templates] = *found;

   if (surface_templates.size() <= templateIdx) return false;

   const auto& surface_template = surface_templates[templateIdx];
   auto& this_surface_template = surface_templates.back();
   this_surface_template = surface_template;
   this_surface_template.first = station; // the assignment on the line above changes the station - put it back to the correct value
   return true;
}

bool Model::MoveSurfaceTemplate(IDType surfaceID, IndexType templateIdx, const Station& station)
{
   auto found = m_SurfaceTemplates.find(surfaceID);
   if (found == m_SurfaceTemplates.end()) return false;

   auto& [ID, surface_templates] = *found;
   if (surface_templates.size() <= templateIdx) return false;

   surface_templates[templateIdx].first = station;
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

   auto& [ID, surface_templates] = *found;
   if(surface_templates.size() <= templateIdx)
      THROW_COGO(WBFL_COGO_E_INVALIDARG);

   return surface_templates[templateIdx].first;
}

const Model::SurfaceTemplateDefinition& Model::GetSurfaceTemplate(IDType surfaceID, IndexType templateIdx) const
{
   auto found = m_SurfaceTemplates.find(surfaceID);
   if (found == m_SurfaceTemplates.end())
      THROW_COGO(WBFL_COGO_E_INVALIDARG);

   auto& [ID, surface_templates] = *found;
   if (surface_templates.size() <= templateIdx)
      THROW_COGO(WBFL_COGO_E_INVALIDARG);

   return surface_templates[templateIdx];
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

   auto& [ID, surface_templates] = *found;
   if (surface_templates.size() <= templateIdx)
      THROW_COGO(WBFL_COGO_E_INVALIDARG);

   auto [nSegments, alignmentPointIdx, profilePointIdx] = GetSurface(surfaceID); // throws on bad ID
   if (nSegments <= segmentIdx)
      THROW_COGO(WBFL_COGO_E_INVALIDARG);

   surface_templates[templateIdx].second[segmentIdx] = surfaceTemplateSegment;
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
      auto [iter,bSuccess] = m_Superelevations.emplace(surfaceID, vSuperelevations);
      if (!bSuccess) return false;

      found = iter;
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

   const auto& [id, definitions] = *found;
   return definitions;
}

bool Model::ClearSuperelevations(IDType surfaceID)
{
   auto found = m_Superelevations.find(surfaceID);
   if (found == m_Superelevations.end())
   {
      return false;
   }

   auto& [id, definitions] = *found;
   definitions.clear();
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
      auto [iter,bSuccess] = m_Widenings.emplace(surfaceID, vWidenings);
      if (!bSuccess) return false;
      found = iter;
   }

   auto& [id, widenings] = *found;
   widenings.emplace_back(definition);

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
      auto [newFrom, newTo] = COGO::LocateParallelLineByPoints(from, to, offset);
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
      auto [newPoint, distFromStart, bOnProjection] = curve->ProjectPoint(point);
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
      auto [newPoint, distFromStart, bOnProjection] = curve->ProjectPoint(point);
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
      auto [newPoint, distFromStart, bOnProjection] = curve->ProjectPoint(point);
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
      auto [newPoint, distFromStart, bOnProjection] = path->ProjectPoint(point);
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
      auto [newPoint, station, bOnProjection] = alignment->ProjectPoint(point);
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
      auto [t1, t2] = COGO::CrossingTangents(center1, radius1, center2, radius2, sign);
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
      auto [t1, t2] = COGO::ExternalTangents(center1, radius1, center2, radius2, sign);

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
      auto& [id,point](*iter);
      bSucceeded &= StorePoint(id,point);
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
      const auto& [element_type, element_id](*iter);
      switch (element_type)
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
   for (const auto& [surfaceID,association_profileID] : m_SurfaceProfileAssociations)
   {
      if (association_profileID == profileID)
      {
         auto surface = CreateSurface(surfaceID,profile);
      }
   }

   return profile;
}

const ProfilePoint& Model::GetStartProfilePoint(const std::pair<ProfileElementType, IDType>& elementData) const
{
   const auto& [type, id](elementData);
   const ProfilePoint* point = nullptr;
   switch (type)
   {
   case ProfileElementType::Point:
      point = &GetProfilePoint(id);
      break;

   case ProfileElementType::Segment:
      point = &GetProfilePoint(GetProfileSegment(id).startID);
      break;

   case ProfileElementType::VerticalCurve:
      point = &GetProfilePoint(GetVerticalCurve(id).pbgID);
   
   default:
      CHECK(false); // is there a new type?
   }
   return *point;
}

WBFL::Geometry::Point2d Model::GetStartPathPoint(const std::pair<PathElementType, IDType>& elementData) const
{
   const auto& [type, id](elementData);
   WBFL::Geometry::Point2d point;
   switch (type)
   {
   case PathElementType::Point:
      point = GetPoint(id);
      break;

   case PathElementType::Segment:
      point = GetPoint(GetPathSegment(id).startID);
      break;

   case PathElementType::CompoundCurve:
      point = CreateCompoundCurve(id)->GetTS();
      break;

   case PathElementType::CircularCurve:
      point = CreateCircularCurve(id)->GetPC();
      break;

   case PathElementType::TransitionCurve:
      point = GetPoint(GetTransitionCurve(id).startID);
      break;

   case PathElementType::CubicSpline:
      point = GetPoint(GetCubicSpline(id).front());
      break;

   case PathElementType::Path:
      point = GetStartPathPoint(GetPath(id).front());

   default:
      CHECK(false); // is there a new type?
   }

   return point;
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

   auto [nSegments, alignmentPointIdx, profilePointIdx] = surface_definition;
   surface->SetSurfaceTemplateSegmentCount(nSegments);
   surface->SetAlignmentPoint(alignmentPointIdx);
   surface->SetProfileGradePoint(profilePointIdx);

   // create the surface templates and update the surface template segments
   auto found = m_SurfaceTemplates.find(surfaceID);
   if (found != m_SurfaceTemplates.end())
   {
      const auto& surface_template_definitions = found->second;
      for (const auto& [station,surface_template_definition] : surface_template_definitions)
      {
         auto surface_template = surface->CreateSurfaceTemplate(station);
         IndexType segmentIdx = 0;
         for (const auto& [width,slope,slopeType] : surface_template_definition)
         {
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
      const auto& [type, element_id](*iter);
      switch (type)
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
