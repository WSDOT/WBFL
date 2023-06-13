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
#include <CoordGeom/GirderLine.h>
#include <CoordGeom/BridgeFramingGeometry.h>
#include <CoordGeom/Alignment.h>
#include <CoordGeom/PathSegment.h>
#include <CoordGeom/COGO.h>
#include <CoordGeom/XCoordGeom.h>

using namespace WBFL::COGO;

GirderLine::GirderLine(std::weak_ptr<const BridgeFramingGeometry> bridge,
   IDType girderLineID,
   IDType layoutLineID,
   GirderLineType type,
   IDType startPierID,
   MeasurementType startPierMeasurementType,
   MeasurementLocation startPierMeasurementLocation,
   IDType endPierID,
   MeasurementType endPierMeasurementType,
   MeasurementLocation endPierMeasurementLocation
) : 
   m_pBridge(bridge),
   m_ID(girderLineID),
   m_LayoutLineID(layoutLineID),
   m_Type(type)
{
   m_PierID[+EndType::Start] = startPierID;
   m_MeasurementType[+EndType::Start] = startPierMeasurementType;
   m_MeasurementLocation[+EndType::Start] = startPierMeasurementLocation;

   m_PierID[+EndType::End] = endPierID;
   m_MeasurementType[+EndType::End] = endPierMeasurementType;
   m_MeasurementLocation[+EndType::End] = endPierMeasurementLocation;

   UpdateGeometry();
}

std::shared_ptr<GirderLine> GirderLine::Create(const GirderLine& girderLine)
{
   return std::shared_ptr<GirderLine>(new GirderLine(girderLine));
}

std::shared_ptr<GirderLine> GirderLine::Create(std::weak_ptr<const BridgeFramingGeometry> bridge,
   IDType girderLineID,
   IDType layoutLineID,
   GirderLineType type,
   IDType startPierID,
   MeasurementType startPierMeasurementType,
   MeasurementLocation startPierMeasurementLocation,
   IDType endPierID,
   MeasurementType endPierMeasurementType,
   MeasurementLocation endPierMeasurementLocation
)
{
   std::shared_ptr<GirderLine> girder_line(new GirderLine(bridge, girderLineID, layoutLineID, type, startPierID, startPierMeasurementType, startPierMeasurementLocation, endPierID, endPierMeasurementType, endPierMeasurementLocation));
   return girder_line;
}

IDType GirderLine::GetID() const
{
   return m_ID;
}

std::shared_ptr<const PierLine> GirderLine::GetPierLine(EndType endType) const
{
   return m_PierLine[+endType];
}

Float64 GirderLine::GetGirderLength() const
{
   return m_GirderLength;
}

Float64 GirderLine::GetSpanLength() const
{
   return m_SpanLength;
}

Float64 GirderLine::GetLayoutLength() const
{
   return m_LayoutLength;
}

const WBFL::Geometry::Point2d& GirderLine::GetPierPoint(EndType endType) const
{
   return m_PierPoint[+endType];
}

const WBFL::Geometry::Point2d& GirderLine::GetBearingPoint(EndType endType) const
{
   return m_BearingPoint[+endType];
}

const WBFL::Geometry::Point2d& GirderLine::GetEndPoint(EndType endType) const
{
   return m_EndPoint[+endType];
}

std::tuple<WBFL::Geometry::Point2d, WBFL::Geometry::Point2d, WBFL::Geometry::Point2d, WBFL::Geometry::Point2d, WBFL::Geometry::Point2d, WBFL::Geometry::Point2d> GirderLine::GetEndPoints() const
{
   return std::make_tuple(GetPierPoint(EndType::Start), GetEndPoint(EndType::Start), GetBearingPoint(EndType::Start),
      GetBearingPoint(EndType::End), GetEndPoint(EndType::End), GetPierPoint(EndType::End));
}

std::shared_ptr<const Path> GirderLine::GetPath() const
{
   return m_Path;
}

const Direction& GirderLine::GetDirection() const
{
   return m_Direction;
}

Float64 GirderLine::GetBearingOffset(EndType endType) const
{
   return m_BearingOffset[+endType];
}

Float64 GirderLine::GetEndDistance(EndType endType) const
{
   return m_EndDistance[+endType];
}

std::shared_ptr<const BridgeFramingGeometry> GirderLine::GetBridge()
{
   return m_pBridge.lock();
}

void GirderLine::UpdateGeometry()
{
   CreatePath();
   LocatePoints();
}

void GirderLine::CreatePath()
{
   // The girder line path goes from CL Pier to CL Pier
   auto bridge = GetBridge();

   auto layout_path = bridge->FindLayoutLine(m_LayoutLineID);

   // Get the pier lines that this girder line intersects with
   m_PierLine[+EndType::Start] = bridge->FindPierLine(m_PierID[+EndType::Start]);
   m_PierLine[+EndType::End] = bridge->FindPierLine(m_PierID[+EndType::End]);

   // Get CL Pier - Alignment intersection points
   m_PierPoint[+EndType::Start] = m_PierLine[+EndType::Start]->GetAlignmentPoint();
   m_PierPoint[+EndType::End] = m_PierLine[+EndType::End]->GetAlignmentPoint();

   // Get centerlines of the piers
   std::array<WBFL::Geometry::Line2d, 2> cl_pier;
   cl_pier[+EndType::Start] = m_PierLine[+EndType::Start]->GetCenterLine();
   cl_pier[+EndType::End] = m_PierLine[+EndType::End]->GetCenterLine();

   if (m_Type == GirderLineType::Chord)
   {
      // girder line is a straight line cord between the intersection of the CL-piers
      auto start_line = GetGirderSpacingLine(EndType::Start);
      auto end_line = GetGirderSpacingLine(EndType::End);

      // intersect the spacing layout lines with the girder path
      auto result = layout_path->Intersect(start_line, m_PierPoint[+EndType::Start], true, true);
      CHECK(result.first == true);
      auto pnt1 = result.second;

      result = layout_path->Intersect(end_line, m_PierPoint[+EndType::End], true, true);
      CHECK(result.first == true);
      auto pnt2 = result.second;

      // create a work line through the points on the girder spacing measurement line
      WBFL::Geometry::Line2d line(pnt1, pnt2);

      // intersect the CL Piers with the girder work line
      m_PierPoint[+EndType::Start] = COGO::IntersectLines(m_PierLine[+EndType::Start]->GetCenterLine(), line);
      m_PierPoint[+EndType::End] = COGO::IntersectLines(m_PierLine[+EndType::End]->GetCenterLine(), line);

      // girder line is a straight line cord between the intersection of the CL-piers
      auto line_segment = PathSegment::Create(m_PierPoint[+EndType::Start], m_PierPoint[+EndType::End]);
      m_Path = Path::Create();
      m_Path->AddPathElement(line_segment);
   }
   else
   {
      // girder line is a sub-path of the layout path

      // determine where the girder path starts and end
      Float64 start_distance, end_distance, offset;
      std::tie(start_distance, offset) = layout_path->DistanceAndOffset(m_PierPoint[+EndType::Start]);
      CHECK(IsZero(offset));
      std::tie(end_distance, offset) = layout_path->DistanceAndOffset(m_PierPoint[+EndType::End]);
      CHECK(IsZero(offset));

      auto subpath_elements = layout_path->CreateSubpath(start_distance, end_distance);
      m_Path = Path::Create();
      for (auto& subpath_element : subpath_elements)
      {
         m_Path->AddPathElement(subpath_element);
      }
   }

   m_LayoutLength = m_Path->GetLength();
   m_Direction = COGO::MeasureDirection(m_PierPoint[+EndType::Start], m_PierPoint[+EndType::End]);
}

void GirderLine::LocatePoints()
{
   //
   // Locate intersection of girder line and centerline bearing
   //
   const auto& ahead_connection_geometry = m_PierLine[+EndType::Start]->GetConnectionGeometry(PierFaceType::Ahead);
   const auto& back_connection_geometry = m_PierLine[+EndType::End]->GetConnectionGeometry(PierFaceType::Back);
   std::array<Float64, 2> brgOffset;
   brgOffset[+EndType::Start] = ahead_connection_geometry.BearingOffset;
   brgOffset[+EndType::End] = back_connection_geometry.BearingOffset;

   std::array<MeasurementType, 2> brgMeasureType;
   brgMeasureType[+EndType::Start] = ahead_connection_geometry.BearingOffsetMeasurementType;
   brgMeasureType[+EndType::End] = back_connection_geometry.BearingOffsetMeasurementType;

   for (int i = 0; i < 2; i++)
   {
      EndType endType = (EndType)i;
      if (brgMeasureType[+endType] == MeasurementType::NormalToItem)
      {
         // convert to distance along girder centerline
         const auto& pier_direction = m_PierLine[+endType]->GetDirection();
         auto pier_normal = pier_direction.IncrementBy(-PI_OVER_2);
         auto skew_angle = pier_normal.AngleBetween(m_Direction);
         brgOffset[+endType] /= cos(skew_angle);
      }
   }

   m_BearingPoint[+EndType::Start] = COGO::LocatePointOnLine(m_PierPoint[+EndType::Start], m_PierPoint[+EndType::End], brgOffset[+EndType::Start], 0.0);
   m_BearingPoint[+EndType::End] = COGO::LocatePointOnLine(m_PierPoint[+EndType::End], m_PierPoint[+EndType::Start], brgOffset[+EndType::End], 0.0);

   //
   // Locate ends of girder
   //

   std::array<Float64, 2> endDistance;
   endDistance[+EndType::Start] = ahead_connection_geometry.EndDistance;
   endDistance[+EndType::End] = back_connection_geometry.EndDistance;

   std::array<MeasurementType, 2> measureType;
   measureType[+EndType::Start] = ahead_connection_geometry.EndDistanceMeasurementType;
   measureType[+EndType::End] = back_connection_geometry.EndDistanceMeasurementType;

   std::array<MeasurementLocation, 2> measureLocation;
   measureLocation[+EndType::Start] = ahead_connection_geometry.EndDistanceMeasurementLocationType;
   measureLocation[+EndType::End] = back_connection_geometry.EndDistanceMeasurementLocationType;

   for (int i = 0; i < 2; i++)
   {
      EndType endType = EndType(i);
      if (measureType[+endType] == MeasurementType::NormalToItem)
      {
         // convert to distance along girder centerline
         const auto& pier_direction = m_PierLine[+endType]->GetDirection();
         auto pier_normal = pier_direction.IncrementBy(-PI_OVER_2);
         auto skew_angle = pier_normal.AngleBetween(m_Direction);
         endDistance[+endType] /= cos(skew_angle);
      }
   }

   if (measureLocation[+EndType::Start] == MeasurementLocation::PierLine)
   {
      m_EndPoint[+EndType::Start] = COGO::LocatePointOnLine(m_PierPoint[+EndType::Start], m_PierPoint[+EndType::End], endDistance[+EndType::Start], 0.0);
   }
   else
   {
      CHECK(measureLocation[+EndType::Start] == MeasurementLocation::CenterlineBearing);
      m_EndPoint[+EndType::Start] = COGO::LocatePointOnLine(m_BearingPoint[+EndType::Start], m_BearingPoint[+EndType::End], -endDistance[+EndType::Start], 0.0);
   }

   if (measureLocation[+EndType::End] == MeasurementLocation::PierLine)
   {
      m_EndPoint[+EndType::End] = COGO::LocatePointOnLine(m_PierPoint[+EndType::End], m_PierPoint[+EndType::Start], endDistance[+EndType::End], 0.0);
   }
   else
   {
      CHECK(measureLocation[+EndType::End] == MeasurementLocation::CenterlineBearing);
      m_EndPoint[+EndType::End] = COGO::LocatePointOnLine(m_BearingPoint[+EndType::End], m_BearingPoint[+EndType::Start], -endDistance[+EndType::End], 0.0);
   }

   Float64 dist1, dist2, offset;
   std::tie(dist1, offset) = m_Path->DistanceAndOffset(m_BearingPoint[+EndType::Start]);
   CHECK(IsZero(offset));
   std::tie(dist2, offset) = m_Path->DistanceAndOffset(m_BearingPoint[+EndType::End]);
   CHECK(IsZero(offset));
   m_SpanLength = dist2 - dist1;
   
   std::tie(dist1, offset) = m_Path->DistanceAndOffset(m_EndPoint[+EndType::Start]);
   CHECK(IsZero(offset));
   std::tie(dist2, offset) = m_Path->DistanceAndOffset(m_EndPoint[+EndType::End]);
   CHECK(IsZero(offset));
   m_GirderLength = dist2 - dist1;

   std::tie(dist1, offset) = m_Path->DistanceAndOffset(m_EndPoint[+EndType::Start]);
   CHECK(IsZero(offset));
   std::tie(dist2, offset) = m_Path->DistanceAndOffset(m_BearingPoint[+EndType::Start]);
   CHECK(IsZero(offset));
   m_EndDistance[+EndType::Start] = fabs(dist2 - dist1); // using fabs because distance are always positive values

   std::tie(dist1, offset) = m_Path->DistanceAndOffset(m_BearingPoint[+EndType::End]);
   CHECK(IsZero(offset));
   std::tie(dist2, offset) = m_Path->DistanceAndOffset(m_EndPoint[+EndType::End]);
   CHECK(IsZero(offset));
   m_EndDistance[+EndType::End] = fabs(dist2 - dist1);

   std::tie(dist1, offset) = m_Path->DistanceAndOffset(m_PierPoint[+EndType::Start]);
   CHECK(IsZero(offset));
   std::tie(dist2, offset) = m_Path->DistanceAndOffset(m_BearingPoint[+EndType::Start]);
   CHECK(IsZero(offset));
   m_BearingOffset[+EndType::Start] = fabs(dist2 - dist1);

   std::tie(dist1, offset) = m_Path->DistanceAndOffset(m_BearingPoint[+EndType::End]);
   CHECK(IsZero(offset));
   std::tie(dist2, offset) = m_Path->DistanceAndOffset(m_PierPoint[+EndType::End]);
   CHECK(IsZero(offset));
   m_BearingOffset[+EndType::End] = fabs(dist2 - dist1);

   // The end distance is longer than the girder... something is messed up with the bridge geometry
   CHECK(m_EndDistance[+EndType::Start] + m_EndDistance[+EndType::End] < m_GirderLength);

#if defined _DEBUG
   const auto& elements = m_Path->GetPathElements();
   if (elements.size() == 1 && std::dynamic_pointer_cast<PathSegment>(elements.front()) != nullptr)
   {
      // The path consists of only one element and it is a straight segment... validate
      // the above calculations using simple point-distance calculations
      std::array<Float64, 2> endDistance, bearingOffset;
      Float64 spanLength = m_BearingPoint[+EndType::End].Distance(m_BearingPoint[+EndType::Start]);
      Float64 girderLength = m_EndPoint[+EndType::End].Distance(m_EndPoint[+EndType::Start]);
      endDistance[+EndType::Start] = m_BearingPoint[+EndType::Start].Distance(m_EndPoint[+EndType::Start]);
      endDistance[+EndType::End] = m_BearingPoint[+EndType::End].Distance(m_EndPoint[+EndType::End]);
      bearingOffset[+EndType::Start] = m_PierPoint[+EndType::Start].Distance(m_BearingPoint[+EndType::Start]);
      bearingOffset[+EndType::End] = m_PierPoint[+EndType::End].Distance(m_BearingPoint[+EndType::End]);
      CHECK(IsEqual(m_SpanLength, spanLength));
      CHECK(IsEqual(m_GirderLength, girderLength));
      CHECK(IsEqual(endDistance[+EndType::Start], m_EndDistance[+EndType::Start]));
      CHECK(IsEqual(endDistance[+EndType::End], m_EndDistance[+EndType::End]));
      CHECK(IsEqual(bearingOffset[+EndType::Start], m_BearingOffset[+EndType::Start]));
      CHECK(IsEqual(bearingOffset[+EndType::End], m_BearingOffset[+EndType::End]));
   }
#endif


   Direction direction; // direction from end to pier point
   std::tie(offset, direction) = COGO::ComputeInverse(m_PierPoint[+EndType::Start], m_BearingPoint[+EndType::Start]);
   if (!IsZero(offset) && m_Direction != direction)
   {
      m_BearingOffset[+EndType::Start] *= -1;
   }

   std::tie(offset, direction) = COGO::ComputeInverse(m_BearingPoint[+EndType::End], m_PierPoint[+EndType::End]);
   if (!IsZero(offset) && m_Direction != direction)
   {
      m_BearingOffset[+EndType::End] *= -1;
   }

   CHECK(::BinarySign(m_BearingOffset[+EndType::Start]) == ::BinarySign(brgOffset[+EndType::Start]));
   CHECK(::BinarySign(m_BearingOffset[+EndType::End]) == ::BinarySign(brgOffset[+EndType::End]));
}

WBFL::Geometry::Line2d GirderLine::GetGirderSpacingLine(EndType endType)
{
   PierFaceType pierFace = (endType == EndType::Start ? PierFaceType::Ahead : PierFaceType::Back);
   const auto& connection_geometry = m_PierLine[+endType]->GetConnectionGeometry(pierFace);

   WBFL::Geometry::Line2d girder_spacing_line;

   if (m_MeasurementType[+endType] == MeasurementType::AlongItem)
   {
      // Girder spacing is measured along the CL Pier or CL Bearing
      if (m_MeasurementLocation[+endType] == MeasurementLocation::PierLine)
      {
         // Girder spacing was measured along the CL Pier so layout lines
         // were defined based on this.
         // Intersect the centerline of the pier with the layout line
         girder_spacing_line = m_PierLine[+endType]->GetCenterLine();
      }
      else
      {
         // girder spacing is measured along CL Bearing
         // locate the CL Bearing line
         CHECK(m_MeasurementLocation[+endType] == MeasurementLocation::CenterlineBearing);

         MeasurementType brgOffsetMeasurement = connection_geometry.BearingOffsetMeasurementType;

         Float64 brgOffset = connection_geometry.BearingOffset;

         if (brgOffsetMeasurement == MeasurementType::NormalToItem)
         {
            // CL Bearing is located "brgOffset" from the CL Pier, measured normal to the pier
            // The CL Bearing line is parallel to the CL Pier line
            girder_spacing_line = m_PierLine[+endType]->GetCenterLine();

            // offset to make it the CL Bearing line
            girder_spacing_line.Offset(pierFace == PierFaceType::Ahead ? -brgOffset : brgOffset);
         }
         else
         {
            // CL Bearing line is located "brgOffset" along the centerline of this girder, measured
            // from the point where the centerline of this girder intersects with the CL pier
            // The CL Bearing line is parallel to the CL Pier line.

            // This input combination is not supported
            CHECK(false);
            THROW_COGO(WBFL_COGO_E_INVALIDARG);
         }
      }
   }
   else
   {
      // Girder spacing is measured normal to the alignment at the CL Pier or CL Bearing
      CHECK(m_MeasurementType[+endType] == MeasurementType::NormalToItem);

      if (m_MeasurementLocation[+endType] == MeasurementLocation::PierLine)
      {
         // Girder spacing was measured along the normal to the alignment where
         // the CL Pier intersects the alignment

         // get the alignment
         auto alignment = GetBridge()->GetBridgeAlignment();

         // get the station at the pier
         const auto& pier_station = m_PierLine[+endType]->GetStation();

         // get the normal to the alignment at this station
         auto alignment_normal = alignment->GetNormal(pier_station);

         // get the intersection of the pier and the alignment
         const auto& alignment_point = m_PierLine[+endType]->GetAlignmentPoint();

         // create line objects to represent the normal
         girder_spacing_line.SetExplicit(alignment_point, WBFL::Geometry::Vector2d(1.0, alignment_normal));
      }
      else
      {
         // Girder spacing was measured along the normal to the alignment where
         // the CL Bearing intersects the alignment

         CHECK(m_MeasurementLocation[+endType] == MeasurementLocation::CenterlineBearing);

         MeasurementType brgOffsetMeasurement = connection_geometry.BearingOffsetMeasurementType;

         Float64 brgOffset = connection_geometry.BearingOffset;

         if (brgOffsetMeasurement == MeasurementType::NormalToItem)
         {
            // CL Bearing is located "brgOffset" from the CL Pier, measured normal to the pier
            // The CL Bearing line is parallel to the CL Pier line
            const auto& centerline = m_PierLine[+endType]->GetCenterLine();

            // offset to make it the CL Bearing line
            auto cl_bearing = centerline.OffsetBy(pierFace == PierFaceType::Ahead ? -brgOffset : brgOffset);
            //hr = centerline->Offset(pierFace == pfAhead ? -brgOffset : brgOffset);
            //if (FAILED(hr))
            //   return hr;

            // get alignment
            auto alignment = GetBridge()->GetBridgeAlignment();

            // intersect CL bearing with alignment
            const auto& pier_point = m_PierLine[+endType]->GetAlignmentPoint();
            bool bSuccess;
            WBFL::Geometry::Point2d brg_point;
            std::tie(bSuccess, brg_point) = alignment->Intersect(cl_bearing, pier_point, true, true);
            CHECK(bSuccess);
            //CComPtr<IPoint2d> pntPier, pntBrg;
            //pPierLine->get_AlignmentPoint(&pntPier);
            //alignment->Intersect(centerline, pntPier, &pntBrg);

            // get station and offset of CL Bearing/Alignment intersection point
            Station cl_bearing_station;
            Float64 offset;
            std::tie(cl_bearing_station,offset) = alignment->StationAndOffset(brg_point);
            CHECK(IsZero(offset));

            // get the normal at this station
            auto normal = alignment->GetNormal(cl_bearing_station);

            // create the work line
            girder_spacing_line.SetExplicit(brg_point, WBFL::Geometry::Vector2d(1.0, normal));
         }
         else
         {
            // CL Bearing line is located "brgOffset" along the centerline of this girder, measured
            // from the point where the centerline of this girder intersects with the CL pier
            // The CL Bearing line is parallel to the CL Pier line

            // This input combination is not supported
            CHECK(false);
            THROW_COGO(WBFL_COGO_E_INVALIDARG);
         }
      }
   }

   return girder_spacing_line;
}

#if defined _UNITTEST
bool GirderLine::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("GirderLine");

   TESTME_EPILOG("GirderLine");
}
#endif // _UNITTEST


