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
#pragma once

#include <CoordGeom/CoordGeomExp.h>
#include <CoordGeom/LayoutLineFactory.h>

namespace WBFL
{
   namespace COGO
   {
      /// @brief A LayoutLineFactory that is composed of other LayoutLineFactory objects.
      class COORDGEOMCLASS CompositeLayoutLineFactory : public LayoutLineFactory
      {
      public:
         CompositeLayoutLineFactory() = default;
         CompositeLayoutLineFactory(const CompositeLayoutLineFactory&) = delete;
         ~CompositeLayoutLineFactory() = default;
         CompositeLayoutLineFactory& operator=(const CompositeLayoutLineFactory&) = delete;

         /// @brief Adds a factory to the composition
         /// @param factory 
         void AddFactory(std::shared_ptr<LayoutLineFactory> factory);

         virtual std::vector<std::pair<IDType, std::shared_ptr<Path>>> Create(std::shared_ptr<const BridgeFramingGeometry> bridge) const override;

      private:
         std::vector<std::shared_ptr<LayoutLineFactory>> m_Factories;
      };
   };
};
