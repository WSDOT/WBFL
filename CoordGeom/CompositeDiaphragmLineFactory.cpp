///////////////////////////////////////////////////////////////////////
// CoordGeom - Coordinate Geometry Library
// Copyright � 1999-2025  Washington State Department of Transportation
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
#include <CoordGeom/CompositeDiaphragmLineFactory.h>

using namespace WBFL::COGO;

void CompositeDiaphragmLineFactory::AddFactory(std::shared_ptr<DiaphragmLineFactory> factory)
{
   m_Factories.emplace_back(factory);
}

std::vector<std::shared_ptr<DiaphragmLine>> CompositeDiaphragmLineFactory::Create(std::shared_ptr<const BridgeFramingGeometry> bridge) const
{
   std::vector<std::shared_ptr<DiaphragmLine>> diaphragm_lines;
   for (auto& factory : m_Factories)
   {
      auto dl = factory->Create(bridge);
      diaphragm_lines.insert(diaphragm_lines.end(), dl.begin(), dl.end());
   }
   return diaphragm_lines;
}
