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
#include <CoordGeom/SingleGirderLineFactory.h>

using namespace WBFL::COGO;

void SingleGirderLineFactory::SetGirderLineID(IDType id)
{
   m_GirderLineID = id;
}

IDType SingleGirderLineFactory::GetGirderLineID() const
{
   return m_GirderLineID;
}

void SingleGirderLineFactory::SetLayoutLineID(IDType id)
{
   m_LayoutLineID = id;
}

IDType SingleGirderLineFactory::GetLayoutLineID() const
{
   return m_LayoutLineID;
}

void SingleGirderLineFactory::SetGirderLineType(GirderLineType type)
{
   m_GirderLineType = type;
}

GirderLineType SingleGirderLineFactory::GetGirderLineType() const
{
   return m_GirderLineType;
}

void SingleGirderLineFactory::SetPierID(EndType endType, IDType id)
{
   m_PierID[+endType] = id;
}

IDType SingleGirderLineFactory::GetPierID(EndType endType) const
{
   return m_PierID[+endType];
}

void SingleGirderLineFactory::SetMeasurementType(EndType endType, MeasurementType measurementType)
{
   m_MeasurementType[+endType] = measurementType;
}

MeasurementType SingleGirderLineFactory::GetMeasurementType(EndType endType) const
{
   return m_MeasurementType[+endType];
}

void SingleGirderLineFactory::SetMeasurementLocation(EndType endType, MeasurementLocation measurementLocation)
{
   m_MeasurementLocation[+endType] = measurementLocation;
}

MeasurementLocation SingleGirderLineFactory::GetMeasurementLocation(EndType endType) const
{
   return m_MeasurementLocation[+endType];
}

std::vector<std::shared_ptr<GirderLine>> SingleGirderLineFactory::Create(std::shared_ptr<const BridgeFramingGeometry> bridge) const
{
   auto girder_line = GirderLine::Create(bridge,m_GirderLineID,m_LayoutLineID,m_GirderLineType,
      m_PierID[+EndType::Start],m_MeasurementType[+EndType::Start],m_MeasurementLocation[+EndType::End],
      m_PierID[+EndType::End], m_MeasurementType[+EndType::End], m_MeasurementLocation[+EndType::End]
      );

   std::vector<std::shared_ptr<GirderLine>> girder_lines;
   girder_lines.emplace_back(girder_line);
   return girder_lines;
}

#if defined _UNITTEST
bool SingleGirderLineFactory::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("SingleGirderLineFactory");

   TESTME_EPILOG("SingleGirderLineFactory");
}
#endif // _UNITTEST


