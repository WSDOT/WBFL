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
#pragma once

#include <CoordGeom/CoordGeomExp.h>
#include <CoordGeom/Path.h>

namespace WBFL
{
   namespace COGO
   {
      class BridgeFramingGeometry;

      /// @brief Abstract base class for layout line factories. A layout line factory creates geometric layout lines that
      /// can be used to establish the geometry of bridge framing elements
      class COORDGEOMCLASS LayoutLineFactory
      {
      public:
         virtual ~LayoutLineFactory() = default;

         /// @brief Creates layout lines. This method is called by a BridgeFramingGeometry object when creation of layout lines are
         /// needed. The owning BridgeFramingGeometry object stores the layout lines created.
         /// @param bridge The bridge geometry object that is creating the layout lines
         /// @return The layout lines
         virtual std::vector<std::pair<IDType, std::shared_ptr<Path>>> Create(std::shared_ptr<const BridgeFramingGeometry> bridge) const = 0;

#if defined _UNITTEST
         //static bool TestMe(WBFL::Debug::Log& rlog);
#endif // _UNITTEST

      private:
      };
   };
};
