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
#include <CoordGeom/UniformSpacingLayoutLineFactory.h>
#include <CoordGeom/BridgeFramingGeometry.h>
#include <CoordGeom/Alignment.h>
#include <CoordGeom/COGO.h>
#include <CoordGeom/PathSegment.h>

using namespace WBFL::COGO;

void UniformSpacingLayoutLineFactory::SetAlignmentID(IDType alignmentID)
{
   m_AlignmentID = alignmentID;
}

IDType UniformSpacingLayoutLineFactory::GetAlignmentID() const
{
   return m_AlignmentID;
}

void UniformSpacingLayoutLineFactory::SetStartPierLineID(IDType pierID)
{
   m_StartPierLineID = pierID;
}

IDType UniformSpacingLayoutLineFactory::GetStartPierLineID() const
{
   return m_StartPierLineID;
}

void UniformSpacingLayoutLineFactory::SetEndPierLineID(IDType pierID)
{
   m_EndPierLineID = pierID;
}

IDType UniformSpacingLayoutLineFactory::GetEndPierLineID() const
{
   return m_EndPierLineID;
}

void UniformSpacingLayoutLineFactory::SetPierLineIDIncrement(IDType idIncrement)
{
   m_PierLineIDInc = idIncrement;
}

IDType UniformSpacingLayoutLineFactory::GetPierLineIDIncrement() const
{
   return m_PierLineIDInc;
}

void UniformSpacingLayoutLineFactory::SetLayoutLineID(IDType id)
{
   m_LayoutLineID = id;
}

IDType UniformSpacingLayoutLineFactory::GetLayoutLineID() const
{
   return m_LayoutLineID;
}

void UniformSpacingLayoutLineFactory::SetLayoutLineIDIncrement(IDType idIncrement)
{
   m_LayoutLineIDInc = idIncrement;
}

IDType UniformSpacingLayoutLineFactory::GetLayoutLineIDIncrement() const
{
   return m_LayoutLineIDInc;
}

void UniformSpacingLayoutLineFactory::SetStartSpacingOffset(Float64 offset)
{
   m_StartOffset = offset;
}

Float64 UniformSpacingLayoutLineFactory::GetStartSpacingOffset() const
{
   return m_StartOffset;
}

void UniformSpacingLayoutLineFactory::SetEndSpacingOffset(Float64 offset)
{
   m_EndOffset = offset;
}

Float64 UniformSpacingLayoutLineFactory::GetEndSpacingOffset() const
{
   return m_EndOffset;
}

void UniformSpacingLayoutLineFactory::SetStartSpacing(const std::vector<Float64>& spacing)
{
   m_StartSpacing = spacing;
}

const std::vector<Float64>& UniformSpacingLayoutLineFactory::GetStartSpacing() const
{
   return m_StartSpacing;
}

void UniformSpacingLayoutLineFactory::SetEndSpacing(const std::vector<Float64>& spacing)
{
   m_EndSpacing = spacing;
}

const std::vector<Float64>& UniformSpacingLayoutLineFactory::GetEndSpacing() const
{
   return m_EndSpacing;
}

std::vector<std::pair<IDType,std::shared_ptr<Path>>> UniformSpacingLayoutLineFactory::Create(std::shared_ptr<const BridgeFramingGeometry> bridge) const
{
   PRECONDITION(m_AlignmentID != INVALID_ID);
   PRECONDITION(m_LayoutLineID != INVALID_ID);
   PRECONDITION(m_StartPierLineID != INVALID_ID);
   PRECONDITION(m_EndPierLineID != INVALID_ID);
   PRECONDITION(m_StartSpacing.size() == m_EndSpacing.size());

   std::vector<std::pair<IDType, std::shared_ptr<Path>>> vPaths;

   auto alignment = bridge->GetAlignment(m_AlignmentID);

   IDType layout_line_id = m_LayoutLineID;

   for (IDType pierID = m_StartPierLineID; pierID < m_EndPierLineID; pierID += m_PierLineIDInc)
   {
      IDType nextPierID = pierID + m_PierLineIDInc;
      auto prev_pier_line = bridge->FindPierLine(pierID);
      auto next_pier_line = bridge->FindPierLine(nextPierID);

      const auto& prev_pier_direction = prev_pier_line->GetDirection();
      const auto& next_pier_direction = next_pier_line->GetDirection();

      // Intersect alignment with pier lines
      bool bSuccess;
      WBFL::Geometry::Point2d alignment_start_point;
      std::tie(bSuccess, alignment_start_point) = alignment->Intersect(prev_pier_line->GetCenterLine(), prev_pier_line->GetAlignmentPoint(), true, true);
      CHECK(bSuccess);

      WBFL::Geometry::Point2d alignment_end_point;
      std::tie(bSuccess, alignment_end_point) = alignment->Intersect(next_pier_line->GetCenterLine(), next_pier_line->GetAlignmentPoint(), true, true);
      CHECK(bSuccess);

      // Locate start and end point of layout lines
      auto start_point = COGO::LocateByDistanceAndDirection(alignment_start_point, -m_StartOffset, prev_pier_direction, 0.0);
      auto end_point = COGO::LocateByDistanceAndDirection(alignment_end_point, -m_EndOffset, next_pier_direction, 0.0);

      // Create first layout line
      auto layout_line = PathSegment::Create(start_point, end_point);
      auto path = Path::Create();
      path->AddPathElement(layout_line);
      vPaths.emplace_back(layout_line_id, path);

      layout_line_id += m_LayoutLineIDInc;

      // Loop over spaces and create the other layout lines
      Float64 start_offset = -m_StartOffset;
      Float64 end_offset = -m_EndOffset;
      auto start_spacing_iter = m_StartSpacing.begin();
      auto start_spacing_end = m_StartSpacing.end();
      auto end_spacing_iter = m_EndSpacing.begin();
      for (; start_spacing_iter != start_spacing_end; start_spacing_iter++, end_spacing_iter++)
      {
         auto start_spacing = *start_spacing_iter;
         auto end_spacing = *end_spacing_iter;

         start_offset -= start_spacing;
         end_offset -= end_spacing;

         start_point = COGO::LocateByDistanceAndDirection(alignment_start_point, start_offset, prev_pier_direction, 0.0);
         end_point = COGO::LocateByDistanceAndDirection(alignment_end_point, end_offset, next_pier_direction, 0.0);

         layout_line = PathSegment::Create(start_point, end_point);
         path = Path::Create();
         path->AddPathElement(layout_line);
         vPaths.emplace_back(layout_line_id, path);
         layout_line_id += m_LayoutLineIDInc;
      }
   }

   return vPaths;
}
