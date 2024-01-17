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
#include <CoordGeom/PierLine.h>
#include <CoordGeom/BridgeFramingGeometry.h>
#include <CoordGeom/Alignment.h>
#include <CoordGeom/COGO.h>

using namespace WBFL::COGO;

PierLine::PierLine(std::weak_ptr<const BridgeFramingGeometry> bridge, IDType pierID,  IDType alignmentID, const Station& station, const std::_tstring& strOrientation, Float64 length, Float64 offset,const ConnectionGeometry& back,const ConnectionGeometry& ahead) :
   m_pBridge(bridge), m_ID(pierID), m_AlignmentID(alignmentID), m_Station(station), m_strOrientation(strOrientation), m_Length(length), m_Offset(offset)
{
   m_ConnectionGeometry[+PierFaceType::Back] = back;
   m_ConnectionGeometry[+PierFaceType::Ahead] = ahead;
   UpdateGeometry();
}

std::shared_ptr<PierLine> PierLine::Create(const PierLine& other)
{
   return std::shared_ptr<PierLine>(new PierLine(other));
}

std::shared_ptr<PierLine> PierLine::Create(std::weak_ptr<const BridgeFramingGeometry> bridge, IDType pierID, IDType alignmentID, const Station& station, const std::_tstring& strOrientation, Float64 length, Float64 offset, const ConnectionGeometry& back, const ConnectionGeometry& ahead)
{
   std::shared_ptr<PierLine> pier_line(new PierLine(bridge, pierID, alignmentID, station, strOrientation, length, offset, back, ahead));
   return pier_line;
}

IDType PierLine::GetID() const
{
   return m_ID;
}

IndexType PierLine::GetIndex() const
{
   return m_Index;
} 

IDType PierLine::GetAlignmentID() const
{
   return m_AlignmentID;
}

const WBFL::COGO::Station& PierLine::GetStation() const
{
   return m_Station;
}

const WBFL::COGO::Direction& PierLine::GetDirection() const
{
   return m_Direction;
}

const WBFL::COGO::Direction& PierLine::GetNormal() const
{
   return m_Normal;
}

const WBFL::COGO::Angle& PierLine::GetSkewAngle() const
{
   return m_SkewAngle;
}

void PierLine::SetConnectionGeometry(PierFaceType pierFace, const ConnectionGeometry& connectionGeometry)
{
   m_ConnectionGeometry[+pierFace] = connectionGeometry;
}

const ConnectionGeometry& PierLine::GetConnectionGeometry(PierFaceType pierFace) const
{
   return m_ConnectionGeometry[+pierFace];
}

const WBFL::Geometry::Point2d& PierLine::GetAlignmentPoint() const
{
   return m_pntAlignment;
}

const WBFL::Geometry::Point2d& PierLine::GetBridgeLinePoint() const
{
   return m_pntBridgeLine;
}

const WBFL::Geometry::Point2d& PierLine::GetLeftPoint() const
{
   return m_pntLeft;
}

const WBFL::Geometry::Point2d& PierLine::GetRightPoint() const
{
   return m_pntRight;
}

const WBFL::Geometry::Line2d& PierLine::GetCenterLine() const
{
   return m_Centerline;
}

Float64 PierLine::GetBearingOffset(PierFaceType pierFace, const Direction& direction) const
{
   // computes the bearing offset, measured from the cl pier, along a line defined by direction,
   // on the face of the pier specified
   Float64 brgOffset = m_ConnectionGeometry[+pierFace].BearingOffset;
   if (m_ConnectionGeometry[+pierFace].BearingOffsetMeasurementType == MeasurementType::NormalToItem)
   {
      // bearing offset is measured normal to pier... adjust it so it is measured along "direction"
      auto angle = m_Normal.AngleBetween(direction);
      brgOffset /= cos(angle);
}
   else
   {
      // bearing offset is measured along item. no adjustment is necessary
   }

   return brgOffset; 
}

std::shared_ptr<const BridgeFramingGeometry> PierLine::GetBridge() const
{
   return m_pBridge.lock();
}

void PierLine::UpdateGeometry()
{
   auto bridge = GetBridge();

   // don't use bridge->GetBridgeAlignment() here. we need the alignment the pier is keyed to, which might be different than the bridge alignment
   auto alignment = bridge->GetAlignment(m_AlignmentID);

   // The point on alignment where the pier is located
   m_pntAlignment = alignment->LocatePoint(m_Station, OffsetType::Normal, 0.0, 0.0);

   // Get the direction of the pier
   m_Direction = alignment->GetDirection(m_Station, m_strOrientation);

   // Get the alignment normal
   auto alignment_normal = alignment->GetNormal(m_Station);
   alignment_normal.Increment(M_PI); // we want normal to the left so increment by 180 deg

   // Skew angle is the difference between the pier direction and the normal
   m_SkewAngle = m_Direction.AngleBetween(alignment_normal);

   // if the skew angle is more than PI/2, it is a right skew. Right skews are negative
   if (PI_OVER_2 < m_SkewAngle.GetValue())
   {
      m_SkewAngle.SetValue(m_SkewAngle.GetValue() - TWO_PI);
   }

   // Pier centerline
   m_Centerline.SetExplicit(m_pntAlignment, WBFL::Geometry::Vector2d(1.0, m_Direction));

   // pier line - bridge line intersection point
   auto bridge_line = bridge->GetBridgeLine();

   bool bIntersect;
   std::tie(bIntersect,m_pntBridgeLine) = bridge_line->Intersect(m_Centerline, m_pntAlignment,true,true);
   CHECK(bIntersect == true);

   // locate left and right points
   m_pntLeft = COGO::LocateByDistanceAndDirection(m_pntAlignment, -m_Offset, m_Direction, 0.0);
   m_pntRight = COGO::LocateByDistanceAndDirection(m_pntLeft, -m_Length, m_Direction, 0.0);

   // create normal to the pier
   m_Normal = m_Direction.IncrementBy(-PI_OVER_2);
}
