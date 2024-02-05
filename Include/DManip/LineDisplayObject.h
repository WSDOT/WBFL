///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
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

#pragma once

#include <DManip/DManipExp.h>
#include <DManip/DisplayObjectDefaultImpl.h>

namespace WBFL
{
   namespace DManip
   {
      class iDrawLineStrategy;

      /// @brief Interface defining a line display object
      class DMANIPCLASS iLineDisplayObject : public DisplayObjectDefaultImpl
      {
      public:
         using DisplayObjectDefaultImpl::DisplayObjectDefaultImpl;

         /// @brief The strategy object used to draw the line
         virtual void SetDrawLineStrategy(std::shared_ptr<iDrawLineStrategy> pStrategy) = 0;
         virtual std::shared_ptr<iDrawLineStrategy> GetDrawLineStrategy() = 0;

         /// @brief Returns the end points of the line in logical space
         virtual std::pair<CPoint,CPoint> GetLogicalEndPoints() const = 0;

         /// @brief Returns the end points of the line in model space
         virtual std::pair<WBFL::Geometry::Point2d, WBFL::Geometry::Point2d> GetEndPoints() const = 0;
      };
   };
};
