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
#include <CoordGeom/DiaphragmLine.h>

namespace WBFL
{
   namespace COGO
   {
      class BridgeFramingGeometry;

      /// @brief Abstract base class for diaphragm line factories. A diaphragm line factory creates diaphragm lines
      /// for a BridgeFramingGeometry model.
      class COORDGEOMCLASS DiaphragmLineFactory
      {
      public:
         virtual ~DiaphragmLineFactory() = default;

         /// @brief Creates diaphragm lines. This method is called by a BridgeFramingGeometry object when creation of diaphragm lines
         /// are needed. The owning BridgeFramingGeometry object stores the diaphragm lines created
         /// @param bridge The bridge geometry object that is creating the diaphragm lines
         /// @return The diaphragm lines
         virtual std::vector<std::shared_ptr<DiaphragmLine>> Create(std::shared_ptr<const BridgeFramingGeometry> bridge) const = 0;
      };
   };
};
