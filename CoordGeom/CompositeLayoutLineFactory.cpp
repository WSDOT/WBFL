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
#include <CoordGeom/CompositeLayoutLineFactory.h>

using namespace WBFL::COGO;

void CompositeLayoutLineFactory::AddFactory(std::shared_ptr<LayoutLineFactory> factory)
{
   m_Factories.emplace_back(factory);
}

std::vector<std::pair<IDType, std::shared_ptr<Path>>> CompositeLayoutLineFactory::Create(std::shared_ptr<const BridgeFramingGeometry> bridge) const
{
   std::vector<std::pair<IDType, std::shared_ptr<Path>>> layout_lines;
   for (auto& factory : m_Factories)
   {
      auto ll = factory->Create(bridge);
      layout_lines.insert(layout_lines.end(), ll.begin(), ll.end());
   }
   return layout_lines;
}

#if defined _UNITTEST
bool CompositeLayoutLineFactory::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("CompositeLayoutLineFactory");

   TESTME_EPILOG("CompositeLayoutLineFactory");
}
#endif // _UNITTEST


