///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
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

#include <DManip/DManipExp.h>
#include <DManip/DisplayObjectDefaultImpl.h>

namespace WBFL
{
   namespace DManip
   {
      class iDrawPointStrategy;

      /// @brief Interface defining a display object located by a single point
      /// Point display objects can represent a single point, or they can locate more
      /// complex objects like shapes. The drawing strategy defines the visual
      /// representation of the point.
      class DMANIPCLASS iPointDisplayObject : public DisplayObjectDefaultImpl
      {
      public:
         using DisplayObjectDefaultImpl::DisplayObjectDefaultImpl;

         /// @brief Position of the display object in model space
         /// @param pos 
         /// @param bRedraw 
         /// @param bFireEvent 
         virtual void SetPosition(const WBFL::Geometry::Point2d& pos,bool bRedraw, bool bFireEvent) = 0;
         virtual const WBFL::Geometry::Point2d& GetPosition() const = 0;

         /// @brief Position in logical space
         /// @return 
         virtual CPoint GetLogicalPosition() const = 0;

         /// @brief Offsets the display object
         /// @param offset 
         /// @param bRedraw 
         /// @param bFireEvent 
         virtual void Offset(const WBFL::Geometry::Size2d& offset, bool bRedraw, bool bFireEvent) = 0;

         /// @brief Sets tne drawing strategy
         /// @param pStrategy 
         virtual void SetDrawingStrategy(std::shared_ptr<iDrawPointStrategy> pStrategy) = 0;
         virtual std::shared_ptr<iDrawPointStrategy> GetDrawingStrategy() = 0;

         /// @brief If enabled, the visual representation is automatically updated when the display object changes
         /// @param bEnable 
         virtual void EnableAutoUpdate(bool bEnable) = 0;
         virtual bool IsAutoUpdateEnabled() const = 0;
      };
   };
};
