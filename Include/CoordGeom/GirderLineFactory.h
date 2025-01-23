///////////////////////////////////////////////////////////////////////
// CoordGeom - Coordinate Geometry Library
// Copyright © 1999-2025  Washington State Department of Transportation
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
#include <CoordGeom/GirderLine.h>

namespace WBFL
{
   namespace COGO
   {
      class BridgeFramingGeometry;

      /// @brief Abstract base class for girder line factories. A girder line factory creates girder lines
      /// for a BridgeFramingGeometry model. GirderLineFactory objects do not store girder lines in the bridge framing model.
      /// Add GirderLineFactory objects to the BridgeFramingGeometry, then the BridgeFramingGeometry object will call
      /// the factory Create method when girder lines are needed. It is the responsibility of the BridgeFramingGeometry object
      /// to store the girder lines.
      class COORDGEOMCLASS GirderLineFactory
      {
      public:
         virtual ~GirderLineFactory() = default;

         /// @brief Creates girder lines. This method is typically called by a BridgeFramingGeometry object when creation of girder lines
         /// is needed. Implementations of this method do not store girder lines in the bridge framing model.
         /// @param bridge The bridge geometry object that is creating the girder lines
         /// @return The girder lines
         virtual std::vector<std::shared_ptr<GirderLine>> Create(std::shared_ptr<const BridgeFramingGeometry> bridge) const = 0;
      };
   };
};
