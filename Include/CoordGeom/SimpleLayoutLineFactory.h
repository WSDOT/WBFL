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
#include <CoordGeom/LayoutLineFactory.h>

namespace WBFL
{
   namespace COGO
   {
      /// @brief A simple layout line factory that simply returns a collection of layout line path objects from the Create method
      class COORDGEOMCLASS SimpleLayoutLineFactory : public LayoutLineFactory
      {
      public:
         SimpleLayoutLineFactory() = default;
         SimpleLayoutLineFactory(const SimpleLayoutLineFactory&) = default;
         ~SimpleLayoutLineFactory() = default;
         SimpleLayoutLineFactory& operator=(const SimpleLayoutLineFactory&) = default;

         /// @brief Adds a path to be used as a layout line
         /// @param id 
         /// @param path 
         void AddPath(IDType id, std::shared_ptr<Path> path);

         virtual std::vector<std::pair<IDType, std::shared_ptr<Path>>> Create(std::shared_ptr<const BridgeFramingGeometry> bridge) const override;

#if defined _UNITTEST
         /// A self-test function - returns true if passed.
         static bool TestMe(WBFL::Debug::Log& rlog);
#endif // _UNITTEST


      private:
         std::vector<std::pair<IDType, std::shared_ptr<Path>>> m_Paths;
      };
   };
};
