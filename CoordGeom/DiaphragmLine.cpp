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
#include <CoordGeom/DiaphragmLine.h>
#include <CoordGeom/BridgeFramingGeometry.h>
#include <CoordGeom/XCoordGeom.h>
#include <numeric>

using namespace WBFL::COGO;

std::shared_ptr<DiaphragmLine> DiaphragmLine::Create(const DiaphragmLine& diaphragmLine)
{
   return std::shared_ptr<DiaphragmLine>(new DiaphragmLine(diaphragmLine));
}

std::shared_ptr<DiaphragmLine> DiaphragmLine::Create(std::weak_ptr<const BridgeFramingGeometry> bridge, IDType id, IDType leftGirderLineID, IDType rightGirderLineID, bool bIsStaggered, const WBFL::Geometry::Line2d& line)
{
   std::shared_ptr<DiaphragmLine> diaphragm_line(new DiaphragmLine(bridge, id, leftGirderLineID, rightGirderLineID, bIsStaggered, line));
   return diaphragm_line;
}

DiaphragmLine::DiaphragmLine(std::weak_ptr<const BridgeFramingGeometry> bridge, IDType id, IDType leftGirderLineID, IDType rightGirderLineID, bool bIsStaggered, const WBFL::Geometry::Line2d& line) :
   m_pBridge(bridge), m_ID(id), m_bIsStaggered(bIsStaggered), m_Line(line)
{
   m_GirderLineID[+SideType::Left] = leftGirderLineID;
   m_GirderLineID[+SideType::Right] = rightGirderLineID;
   UpdateGeometry();
}

IDType DiaphragmLine::GetID() const
{
   return m_ID;
}

Float64 DiaphragmLine::Length(IDType girderLineID) const
{
   auto found = m_EndPoints.find(girderLineID);
   if (found == m_EndPoints.end())
      THROW_COGO(WBFL_COGO_E_INVALIDARG);

   const auto& p1 = found->second[+SideType::Left];
   const auto& p2 = found->second[+SideType::Right];
   return p1.Distance(p2);
}

const WBFL::Geometry::Point2d& DiaphragmLine::GetPoint(IDType girderLineID, EndType endType) const
{
   // gdrLineID identifies the girder bay where the diaphragm is located.
   // gdrLineID identifies the girder line on the left hand side of the bay.
   auto found = m_EndPoints.find(girderLineID);
   if (found == m_EndPoints.end())
      THROW_COGO(WBFL_COGO_E_INVALIDARG);

   return found->second[+endType];
}

std::shared_ptr<const BridgeFramingGeometry> DiaphragmLine::GetBridge() const
{
   return m_pBridge.lock();
}

void DiaphragmLine::UpdateGeometry()
{
   m_EndPoints.clear();
   LocatePoints();
}

void DiaphragmLine::LocatePoints()
{
   auto bridge = GetBridge();

   //
   // Locate intersection of diaphragm reference line and the left and right girder lines
   //
   const auto& left_girder_line = bridge->FindGirderLine(m_GirderLineID[+SideType::Left]);
   const auto& right_girder_line = bridge->FindGirderLine(m_GirderLineID[+SideType::Right]);

   auto left_path = left_girder_line->GetPath();
   auto right_path = right_girder_line->GetPath();

   auto[p,v] = m_Line.GetExplicit();

   bool bSuccess;
   std::tie(bSuccess, m_Point[+EndType::Start]) = left_path->Intersect(m_Line, p, true, true);
   CHECK(bSuccess);
   std::tie(bSuccess, m_Point[+EndType::End]) = right_path->Intersect(m_Line, p, true, true);
   CHECK(bSuccess);

   //
   // Find the start and end points of the diaphragm in the girder bays
   //
   auto left_point = m_Point[+EndType::Start];

   for (GirderIDType gdrID = m_GirderLineID[+EndType::Start]; gdrID < m_GirderLineID[+EndType::End]; gdrID++)
   {
      const auto& next_girder_line = bridge->FindGirderLine(gdrID+1);
      auto next_path = next_girder_line->GetPath();

      WBFL::Geometry::Point2d next_point;
      std::tie(bSuccess, next_point) = next_path->Intersect(m_Line, p, true, true);
      CHECK(bSuccess);

      if (m_bIsStaggered)
      {
         // find mid-point between pntLeft and pntRight. This is the point the staggered diaphragm
         // passes through in the center of the girder bay
         auto [xl, yl] = left_point.GetLocation();
         auto [xr, yr] = next_point.GetLocation();
         Float64 cx = std::midpoint(xl, xr);
         Float64 cy = std::midpoint(yl, yr);
         WBFL::Geometry::Point2d center_point(cx, cy);

         // Find the point on the left girder line where the normal passes through (cx,cy)
         Float64 distFromStart;
         bool bOnProjection;
         std::tie(left_point, distFromStart, bOnProjection) = left_path->ProjectPoint(center_point);

         // Create a line from this point through point (cx,cy)
         WBFL::Geometry::Line2d staggered_line(left_point, center_point);

         // Intersect staggered line with the right girder line
         std::tie(bSuccess, next_point) = next_path->Intersect(staggered_line, center_point, true, true);
      }

      std::array<WBFL::Geometry::Point2d, 2> points{ left_point,next_point };
      m_EndPoints.insert(std::make_pair(gdrID, points));

      left_point = next_point;
      left_path = next_path;
   }
}
