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

namespace WBFL
{
   namespace DManip
   {
      class iLineDisplayObject;
      class iCoordinateMap;

      /// @brief Interface implemented by line drawing strategy objects. 
      /// By implementing a line drawing strategy, line display objects can easily be drawn in different ways.
      class DMANIPCLASS iDrawLineStrategy
      {
      public:
         /// @brief Called by the framework when a line display object needs to be drawn
         virtual void Draw(std::shared_ptr<const iLineDisplayObject> pDO,CDC* pDC) const = 0;

         /// @brief Called by the framework when a line is being dragged and it needs to be drawn
         virtual void DrawDragImage(std::shared_ptr<const iLineDisplayObject> pDO,CDC* pDC, std::shared_ptr<const iCoordinateMap> map, const POINT& dragStart, const POINT& dragPoint) const = 0;

         /// @brief Called by the framework whenever an appropriate object is dragged over this display object. 
         /// The line display object needs to be drawn highlighted to indicate to the user that it is a valid point to drop.
         virtual void DrawHighlight(std::shared_ptr<const iLineDisplayObject> pDO,CDC* pDC,bool bHighlight) const = 0;

         /// @brief Returns the size of the display object in world coordinates
         virtual WBFL::Geometry::Rect2d GetBoundingBox(std::shared_ptr<const iLineDisplayObject> pDO) const = 0;
      };
   };
};
