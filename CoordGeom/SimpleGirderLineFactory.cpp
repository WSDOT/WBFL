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
#include <CoordGeom/SimpleGirderLineFactory.h>

using namespace WBFL::COGO;

void SimpleGirderLineFactory::SetGirderLineID(IDType id)
{
   m_GirderLineID = id;
}

IDType SimpleGirderLineFactory::GetGirderLineID() const
{
   return m_GirderLineID;
}

void SimpleGirderLineFactory::SetGirderLineIDIncrement(IDType idIncrement)
{
   m_GirderLineIDIncrement = idIncrement;
}

IDType SimpleGirderLineFactory::GetGirderLineIDIncrement() const
{
   return m_GirderLineIDIncrement;
}

void SimpleGirderLineFactory::SetLayoutLineID(SideType side,IDType id)
{
   m_LayoutLineID[+side] = id;
}

IDType SimpleGirderLineFactory::GetLayoutLineID(SideType side) const
{
   return m_LayoutLineID[+side];
}

void SimpleGirderLineFactory::SetLayoutLineIDIncrement(IDType idIncrement)
{
   m_LayoutLineIDIncrement = idIncrement;
}

IDType SimpleGirderLineFactory::GetLayoutLineIDIncrement() const
{
   return m_LayoutLineIDIncrement;
}

void SimpleGirderLineFactory::SetGirderLineType(GirderLineType type)
{
   m_GirderLineType = type;
}

GirderLineType SimpleGirderLineFactory::GetGirderLineType() const
{
   return m_GirderLineType;
}

void SimpleGirderLineFactory::SetPierID(EndType endType, IDType id)
{
   m_PierID[+endType] = id;
}

IDType SimpleGirderLineFactory::GetPierID(EndType endType) const
{
   return m_PierID[+endType];
}

void SimpleGirderLineFactory::SetPierIDIncrement(IDType idIncrement)
{
   m_PierIDIncrement = idIncrement;
}

IDType SimpleGirderLineFactory::GetPierIDIncrement() const
{
   return m_PierIDIncrement;
}

void SimpleGirderLineFactory::IsContinuous(bool bIsContinuous)
{
   m_bIsContinuous = bIsContinuous;
}

bool SimpleGirderLineFactory::IsContinuous() const
{
   return m_bIsContinuous;
}

void SimpleGirderLineFactory::SetMeasurementType(EndType endType, MeasurementType measurementType)
{
   m_MeasurementType[+endType] = measurementType;
}

MeasurementType SimpleGirderLineFactory::GetMeasurementType(EndType endType) const
{
   return m_MeasurementType[+endType];
}

void SimpleGirderLineFactory::SetMeasurementLocation(EndType endType, MeasurementLocation measurementLocation)
{
   m_MeasurementLocation[+endType] = measurementLocation;
}

MeasurementLocation SimpleGirderLineFactory::GetMeasurementLocation(EndType endType) const
{
   return m_MeasurementLocation[+endType];
}

std::vector<std::shared_ptr<GirderLine>> SimpleGirderLineFactory::Create(std::shared_ptr<const BridgeFramingGeometry> bridge) const
{
   std::vector<std::shared_ptr<GirderLine>> girder_lines;

   if (m_bIsContinuous)
   {
      IDType girderLineID = m_GirderLineID;
      IDType layoutLineID = m_LayoutLineID[+SideType::Left];
      for (; layoutLineID <= m_LayoutLineID[+SideType::Right]; girderLineID += m_GirderLineIDIncrement, layoutLineID += m_LayoutLineIDIncrement)
      {
         auto girder_line = GirderLine::Create(bridge, girderLineID, layoutLineID, m_GirderLineType,
            m_PierID[+EndType::Start], m_MeasurementType[+EndType::Start], m_MeasurementLocation[+EndType::Start],
            m_PierID[+EndType::End], m_MeasurementType[+EndType::End], m_MeasurementLocation[+EndType::End]
         );
         girder_lines.emplace_back(girder_line);
      }
   }
   else
   {
      // simple span layout
      IDType girderLineID = m_GirderLineID;
      for (PierIDType pierID = m_PierID[+EndType::Start]; pierID < m_PierID[+EndType::End]; pierID += m_PierIDIncrement)
      {
         IDType layoutLineID = m_LayoutLineID[+SideType::Left];
         for (; layoutLineID <= m_LayoutLineID[+SideType::Right]; girderLineID += m_GirderLineIDIncrement, layoutLineID += m_LayoutLineIDIncrement)
         {
            auto girder_line = GirderLine::Create(bridge, girderLineID, layoutLineID, m_GirderLineType,
               pierID, m_MeasurementType[+EndType::Start], m_MeasurementLocation[+EndType::Start],
               pierID + m_PierIDIncrement, m_MeasurementType[+EndType::End], m_MeasurementLocation[+EndType::End]
            );
            girder_lines.emplace_back(girder_line);
         }
      }
   }

   return girder_lines;
}
