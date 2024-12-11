///////////////////////////////////////////////////////////////////////
// CoordGeom - Coordinate Geometry Library
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

#include <CoordGeom/CoordGeomLib.h>
#include <CoordGeom/DeckBoundary.h>
#include <CoordGeom/BridgeFramingGeometry.h>
#include <CoordGeom/Alignment.h>

using namespace WBFL::COGO;

DeckBoundary::DeckBoundary(std::weak_ptr<const BridgeFramingGeometry> bridge,
   const std::array<IDType, 2>& transverseEdgeIDs,
   const std::array<TransverseEdgeType, 2>& transverseEdgeTypes,
   const std::array<IDType, 2>& edgeIDs,
   const std::array<IDType, 2>& edgeBreakIDs,
   const std::array<std::array<bool, 2>, 2>& bBreakEdge) :
   m_pBridge(bridge), 
   m_TransverseEdgeID(transverseEdgeIDs),
   m_TransverseEdgeType(transverseEdgeTypes),
   m_EdgeID(edgeIDs),
   m_EdgeBreakID(edgeBreakIDs),
   m_bBreakEdge(bBreakEdge)
{
   UpdateGeometry();
}

std::shared_ptr<DeckBoundary> DeckBoundary::Create(const DeckBoundary& deckBoundary)
{
   return std::shared_ptr<DeckBoundary>(new DeckBoundary(deckBoundary));
}

std::shared_ptr<DeckBoundary> DeckBoundary::Create(std::weak_ptr<const BridgeFramingGeometry> bridge,
   const std::array<IDType, 2>& transverseEdgeIDs,
   const std::array<TransverseEdgeType, 2>& transverseEdgeTypes,
   const std::array<IDType, 2>& edgeIDs,
   const std::array<IDType, 2>& edgeBreakIDs,
   const std::array<std::array<bool, 2>, 2>& bBreakEdge)
{
   return std::shared_ptr<DeckBoundary>(new DeckBoundary(bridge, transverseEdgeIDs, transverseEdgeTypes, edgeIDs, edgeBreakIDs, bBreakEdge));
}

std::vector<WBFL::Geometry::Point2d> DeckBoundary::GetPerimeter(IndexType nMinPointsPerSide) const
{
   auto bridge = GetBridge();
   auto firstPierID = bridge->GetPierLine(0)->GetID();
   auto lastPierID = bridge->GetPierLine(bridge->GetPierLineCount() - 1)->GetID();

   return GetPerimeter(nMinPointsPerSide, firstPierID, 0.0, lastPierID, 0.0, true);
}

std::vector<WBFL::Geometry::Point2d> DeckBoundary::GetPerimeter(IndexType nMinPointsPerSide, IDType startPierID, Float64 Xstart, IDType endPierID, Float64 Xend, bool bParallelToPiers) const
{
   std::vector<WBFL::Geometry::Point2d> boundary_points;
   auto bridge = GetBridge();
   auto first_pier_line = bridge->GetPierLine(0); // first pier line in the bridge
   auto last_pier_line = bridge->GetPierLine(bridge->GetPierLineCount() - 1); // last pier line in the bridge

   auto first_pier_id = first_pier_line->GetID();
   auto last_pier_id = last_pier_line->GetID();

   auto start_pier_line = bridge->FindPierLine(startPierID); // starting pier line where the perimeter is requested
   auto end_pier_line = bridge->FindPierLine(endPierID); // ending pier line where the perimeter is requested

   Float64 left_edge_start, right_edge_start; // distance along the edge path to the start of this DeckBoundary segment

   // build starting edge of DeckBoundary
   if (first_pier_id == startPierID && IsZero(Xstart))
   {
      // starting with first pier
      // use the DeckBoundary transverse end points at the start
      boundary_points.emplace_back(m_EdgePoint[+EndType::Start][+SideType::Left]);

      if (m_bBreakEdge[+EndType::Start][+SideType::Left])
      {
         boundary_points.emplace_back(m_EdgeBreakPoint[+EndType::Start][+SideType::Left]);
      }

      if (m_bBreakEdge[+EndType::Start][+SideType::Right])
      {
         boundary_points.emplace_back(m_EdgeBreakPoint[+EndType::Start][+SideType::Right]);
      }

      boundary_points.emplace_back(m_EdgePoint[+EndType::Start][+SideType::Right]);

      left_edge_start = 0;
      right_edge_start = 0;
   }
   else
   {
      auto start_pier_station = start_pier_line->GetStation();

      WBFL::Geometry::Point2d alignment_point;

      if (IsZero(Xstart))
      {
         alignment_point = start_pier_line->GetAlignmentPoint();
      }
      else
      {
         // Xstart is the distance, in stations along the alignment, to where we want to
         // start getting the perimeter relative to the centerline. get x,y of that point on the alignment and then
         // move centerline so it passes through that point. Make sure Xstart isn't before the start of the bridge

         // move the "centerline" so that it passes through the point defined by Xstart
         start_pier_station.Offset(Xstart);

         auto alignment = bridge->GetBridgeAlignment();
         alignment_point = alignment->LocatePoint(start_pier_station, OffsetType::Normal, 0.0, 0.0);
      }

      auto centerline = start_pier_line->GetCenterLine();
      if (!bParallelToPiers)
      {
         auto alignment = bridge->GetBridgeAlignment();
         auto normal = alignment->GetNormal(start_pier_station);
         centerline.SetExplicit(alignment_point, WBFL::Geometry::Vector2d(1.0, normal));
      }

      // intersect centerline of pier with left and right DeckBoundary edges
      // these two points define the start edge of the DeckBoundary
      bool bSuccess;
      WBFL::Geometry::Point2d left_point;
      std::tie(bSuccess, left_point) = m_EdgePath[+SideType::Left]->Intersect(centerline, alignment_point, true, true);
      CHECK(bSuccess);

      WBFL::Geometry::Point2d right_point;
      std::tie(bSuccess, right_point) = m_EdgePath[+SideType::Right]->Intersect(centerline, alignment_point, true, true);
      CHECK(bSuccess);

      boundary_points.emplace_back(left_point);
      boundary_points.emplace_back(right_point);

      Float64 offset;
      std::tie(left_edge_start,offset) = m_EdgePath[+SideType::Left]->DistanceAndOffset(left_point);
      std::tie(right_edge_start,offset) = m_EdgePath[+SideType::Right]->DistanceAndOffset(right_point);
   }

   // determine where to stop dividing the DeckBoundary edge paths
   WBFL::Geometry::Point2d left_end_point, right_end_point;
   if (last_pier_id == endPierID && IsZero(Xend))
   {
      left_end_point = m_EdgePoint[+EndType::End][+SideType::Left];
      right_end_point = m_EdgePoint[+EndType::End][+SideType::Right];
   }
   else
   {
      auto end_pier_station = end_pier_line->GetStation();

      WBFL::Geometry::Point2d alignment_point;
      if (IsZero(Xend))
      {
         alignment_point = end_pier_line->GetAlignmentPoint();
      }
      else
      {
         // Xend is the distance, in stations along the alignment, to where we want to
         // stop getting the perimeter, relative to the center. get x,y of that point on the alignment and then
         // move centerline so it passes through that point. Make sure Xend doesn't go too far off the bridge

         // move the "centerline" so that it passes through the point defined by Xend
         end_pier_station.Offset(Xend);

         auto alignment = bridge->GetBridgeAlignment();
         alignment_point = alignment->LocatePoint(end_pier_station, OffsetType::Normal, 0.0, 0.0);
      }

      auto centerline = end_pier_line->GetCenterLine();
      if (!bParallelToPiers)
      {
         auto alignment = bridge->GetBridgeAlignment();
         auto normal = alignment->GetNormal(end_pier_station);
         centerline.SetExplicit(alignment_point, WBFL::Geometry::Vector2d(1.0, normal));
      }

      // intersect centerline of pier with left and right DeckBoundary edges
      // these two points define the start edge of the DeckBoundary
      bool bSuccess;
      std::tie(bSuccess,left_end_point) = m_EdgePath[+SideType::Left]->Intersect(centerline, alignment_point, true, true);
      CHECK(bSuccess);

      std::tie(bSuccess,right_end_point) = m_EdgePath[+SideType::Right]->Intersect(centerline, alignment_point, true, true);
      CHECK(bSuccess);
   }

   // determine where to stop dividing the edge paths
   auto [left_edge_end,left_edge_offset] = m_EdgePath[+SideType::Left]->DistanceAndOffset(left_end_point);
   auto [right_edge_end,right_edge_offset] = m_EdgePath[+SideType::Right]->DistanceAndOffset(right_end_point);

   std::map<Float64,WBFL::Geometry::Point2d> right_path_points;
   IndexType nPathElements = m_EdgePath[+SideType::Right]->GetPathElementCount();
   for (IndexType i = 0; i < nPathElements; i++)
   {
      auto path_element = m_EdgePath[+SideType::Right]->GetPathElement(i);

      auto key_points = path_element->GetKeyPoints();

      for(const auto& key_point : key_points)
      {
         auto [distance,offset] = m_EdgePath[+SideType::Right]->DistanceAndOffset(key_point);
         if (::InRange(right_edge_start, distance, right_edge_end))
         {
            right_path_points.insert(std::make_pair(distance, key_point));
         }
      }
   }

   Float64 path_length = right_edge_end - right_edge_start;
   for (IndexType idx = 0; idx < nMinPointsPerSide; idx++)
   {
      Float64 distance_along_path = right_edge_start + path_length * idx / (nMinPointsPerSide - 1);
      auto point = m_EdgePath[+SideType::Right]->LocatePoint(distance_along_path, OffsetType::Normal, 0.0, 0.0);
      right_path_points.insert(std::make_pair(distance_along_path, point));
   }

   for (const auto& right_path_point : right_path_points)
   {
      boundary_points.emplace_back(right_path_point.second);
   }

   // define the transverse line at the end of the DeckBoundary
   if (last_pier_id == endPierID && IsZero(Xend))
   {
      boundary_points.emplace_back(m_EdgePoint[+EndType::End][+SideType::Right]);

      if (m_bBreakEdge[+EndType::End][+SideType::Right])
      {
         boundary_points.emplace_back(m_EdgeBreakPoint[+EndType::End][+SideType::Right]);
      }

      if (m_bBreakEdge[+EndType::End][+SideType::Left])
      {
         boundary_points.emplace_back(m_EdgeBreakPoint[+EndType::End][+SideType::Left]);
      }

      boundary_points.emplace_back(m_EdgePoint[+EndType::End][+SideType::Left]);
   }
   else
   {
      boundary_points.emplace_back(right_end_point);
      boundary_points.emplace_back(left_end_point);
   }

   std::map<Float64, WBFL::Geometry::Point2d, std::greater<Float64>> left_path_points; // sort from greatest to least (opposite order from the ridge edge)

   nPathElements = m_EdgePath[+SideType::Left]->GetPathElementCount();
   for (IndexType i = 0; i < nPathElements; i++)
   {
      auto path_element = m_EdgePath[+SideType::Left]->GetPathElement(i);

      auto key_points = path_element->GetKeyPoints();

      for (const auto& key_point : key_points)
      {
         auto [distance, offset] = m_EdgePath[+SideType::Left]->DistanceAndOffset(key_point);
         if (::InRange(right_edge_start, distance, right_edge_end))
         {
            left_path_points.insert(std::make_pair(distance, key_point));
         }
      }
   }

   path_length = left_edge_end - left_edge_start;
   for (IndexType idx = 0; idx < nMinPointsPerSide; idx++)
   {
      Float64 distance_along_path = left_edge_start + path_length * idx / (nMinPointsPerSide - 1);
      auto point = m_EdgePath[+SideType::Left]->LocatePoint(distance_along_path, OffsetType::Normal, 0.0, 0.0);
      left_path_points.insert(std::make_pair(distance_along_path, point));
   }

   for (const auto& left_path_point : left_path_points)
   {
      boundary_points.emplace_back(left_path_point.second);
   }

   // remove adjacent duplicates
   boundary_points.erase(std::unique(boundary_points.begin(), boundary_points.end()), boundary_points.end());

   // close the perimeter shape
   if(boundary_points.front() != boundary_points.back()) boundary_points.emplace_back(boundary_points.front());

   return boundary_points;
}

std::array<WBFL::Geometry::Point2d, 4> DeckBoundary::GetTransverseEdgePoints(EndType endType) const
{
   std::array<WBFL::Geometry::Point2d, 4> points;
   auto sideType1 = (endType == EndType::Start ? SideType::Left : SideType::Right);
   auto sideType2 = (endType == EndType::Start ? SideType::Right : SideType::Left);
   points[0] = m_EdgePoint[+endType][+sideType1];
   points[1] = m_EdgeBreakPoint[+endType][+sideType1];
   points[2] = m_EdgeBreakPoint[+endType][+sideType2];
   points[3] = m_EdgePoint[+endType][+sideType2];

   return points;
}

std::shared_ptr<const Path> DeckBoundary::GetEdgePath(SideType side, bool bReturnLayoutPath) const
{
   if (bReturnLayoutPath)
   {
      auto bridge = GetBridge();
      return bridge->FindLayoutLine(m_EdgeID[+side]);
   }
   else
   {
      return m_EdgePath[+side];
   }
}

std::shared_ptr<const BridgeFramingGeometry> DeckBoundary::GetBridge() const
{
   return m_pBridge.lock();
}

void DeckBoundary::UpdateGeometry()
{
   PRECONDITION(m_TransverseEdgeID[+EndType::Start] != m_TransverseEdgeID[+EndType::End]);
   PRECONDITION(m_EdgeID[+SideType::Left] != m_EdgeID[+SideType::Right]);

   CreateDeckBoundaryEndPoints(EndType::Start);
   CreateDeckBoundaryEndPoints(EndType::End);

   CreateEdgePath(SideType::Left);
   CreateEdgePath(SideType::Right);
}

void DeckBoundary::CreateDeckBoundaryEndPoints(EndType endType)
{
   WBFL::Geometry::Line2d end_line;
   WBFL::Geometry::Point2d alignment_point;

   WBFL::Geometry::Point2d end_point_1; // intersection of end line and left edge
   WBFL::Geometry::Point2d end_point_2; // intersection of end line and left edge break
   WBFL::Geometry::Point2d end_point_3; // intersection of end line and right edge break
   WBFL::Geometry::Point2d end_point_4; // intersection of end line and right edge

   auto bridge = GetBridge();
   auto alignment = bridge->GetBridgeAlignment();

   // Get path that represents the end of the DeckBoundary
   if (m_TransverseEdgeType[+endType] == TransverseEdgeType::Pier)
   {
      // edge of deck is the pier line
      auto pier_line = bridge->FindPierLine(m_TransverseEdgeID[+endType]);
      end_line = pier_line->GetCenterLine();
      alignment_point = pier_line->GetAlignmentPoint();
   }
   else
   {
      // edge of deck is a layout line
      auto end_path = bridge->FindLayoutLine(m_TransverseEdgeID[+endType]);
      auto nPathElements = end_path->GetPathElementCount();
      CHECK(nPathElements == 1);
      auto path_element = end_path->GetPathElement(0);
      const auto& start_point = path_element->GetStartPoint();
      const auto& end_point = path_element->GetEndPoint();
      end_line.ThroughPoints(start_point, end_point);
      bool bSuccess;
      std::tie(bSuccess,alignment_point) = alignment->Intersect(end_line, start_point, true, true);
      CHECK(bSuccess);
   }

   if (m_bBreakEdge[+endType][+SideType::Left])
   {
      // intersect edge path with left break line
      auto left_edge_break_path = bridge->FindLayoutLine(m_EdgeBreakID[+SideType::Left]);
      bool bSuccess;
      std::tie(bSuccess,end_point_2) = left_edge_break_path->Intersect(end_line, alignment_point, true, true);
      CHECK(bSuccess);

      // create a line that is normal to the alignment passing through this intersection point
      auto [point_on_alignment, station, bOnProjection] = alignment->ProjectPoint(end_point_2);

      WBFL::Geometry::Line2d break_line(point_on_alignment, end_point_2);

      // intersect break line with left edge path
      auto left_edge_path = bridge->FindLayoutLine(m_EdgeID[+SideType::Left]);
      std::tie(bSuccess,end_point_1) = left_edge_path->Intersect(break_line, end_point_2,true,true);
      CHECK(bSuccess);
   }
   else
   {
      // intersect edge path with left edge path
      auto left_edge_path = bridge->FindLayoutLine(m_EdgeID[+SideType::Left]);
      bool bSuccess;
      std::tie(bSuccess,end_point_1) = left_edge_path->Intersect(end_line, alignment_point,true,true);
      CHECK(bSuccess);
      end_point_2 = end_point_1;
   }

   if (m_bBreakEdge[+endType][+SideType::Right])
   {
      // intersect edge path with right break line
      auto right_edge_break_path = bridge->FindLayoutLine(m_EdgeBreakID[+SideType::Right]);
      bool bSuccess;
      std::tie(bSuccess,end_point_3) = right_edge_break_path->Intersect(end_line, alignment_point,true,true);
      CHECK(bSuccess);

      // create a line that is normal to the alignment passing through this intersection point
      auto [point_on_alignment, station, bOnProjection] = alignment->ProjectPoint(end_point_3);

      WBFL::Geometry::Line2d break_line(point_on_alignment, end_point_3);

      // intersect break line with left edge path
      auto right_edge_path = bridge->FindLayoutLine(m_EdgeID[+SideType::Right]);
      std::tie(bSuccess,end_point_4) = right_edge_path->Intersect(break_line, end_point_3,true,true);
      CHECK(bSuccess);
   }
   else
   {
      // intersect edge path with right edge path
      auto right_edge_path = bridge->FindLayoutLine(m_EdgeID[+SideType::Right]);
      bool bSuccess;
      std::tie(bSuccess,end_point_4) = right_edge_path->Intersect(end_line, alignment_point,true,true);
      CHECK(bSuccess);
      end_point_3 = end_point_4;
   }

   m_EdgePoint[+endType][+SideType::Left]       = end_point_1;
   m_EdgeBreakPoint[+endType][+SideType::Left]  = end_point_2;
   m_EdgeBreakPoint[+endType][+SideType::Right] = end_point_3;
   m_EdgePoint[+endType][+SideType::Right]      = end_point_4;
}

void DeckBoundary::CreateEdgePath(SideType sideType)
{
   auto bridge = GetBridge();
   auto edge_path = bridge->FindLayoutLine(m_EdgeID[+sideType]);

   const auto& start_point = m_EdgePoint[+EndType::Start][+sideType];
   const auto& end_point = m_EdgePoint[+EndType::End][+sideType];

   // get distance along path to start_point and end_point, then create a sub-path between these two locations
   Float64 offset;
   Float64 distance_to_start_point, distance_to_end_point;
   std::tie(distance_to_start_point, offset) = edge_path->DistanceAndOffset(start_point);
   CHECK(IsZero(offset));

   std::tie(distance_to_end_point, offset) = edge_path->DistanceAndOffset(end_point);
   CHECK(IsZero(offset));

    auto path_elements = edge_path->CreateSubpath(distance_to_start_point, distance_to_end_point);
    auto sub_path = Path::Create();
    for (const auto& path_element : path_elements)
    {
       sub_path->AddPathElement(path_element);
    }
    m_EdgePath[+sideType] = sub_path;
}
