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

namespace WBFL
{
   namespace Geometry
   {
      class Size2d;
   };

   namespace DManip
   {
      class iDragDataSource;
      class iDragDataSink;
      class iDragData;
      class iCoordinateMap;

      /// @brief Implemented by display objects that can participate in a drag/drop operation.
      class DMANIPCLASS iDraggable
      {
      public:
         /// @brief Sets the drag data object
         /// @param dd 
         virtual void SetDragData(std::shared_ptr<iDragData> dd) = 0;
         virtual std::shared_ptr<iDragData> GetDragData() = 0;

         /// @brief Returns the clipboard format
         /// @return 
         virtual UINT Format() = 0;

         /// @brief Called by the framework to prepare a draggable object for drag drop operation.
         /// After saving display object specific data, calls PrepareDrag on the associated DragData object.
         /// @param pSink 
         virtual void PrepareDrag(std::shared_ptr<iDragDataSink> pSink) = 0;

         /// @brief Called by the framework when the draggable object has been dropped. 
         /// The draggable object reads the data is stored in PrepareDrag and then calls OnDrop on the associated DragData object.
         /// @param pSource 
         virtual void OnDrop(std::shared_ptr<iDragDataSource> pSource) = 0;
         
         /// @brief Called by the framework when a draggable display object is moved within a DisplayView
         /// @param offset 
         virtual void OnDragMoved(const WBFL::Geometry::Size2d& offset) = 0;

         /// @brief Called by the framework when a draggable display object is moved from one DisplayView to another.
         virtual void OnMoved() = 0;

         /// @brief Called by the framework when a draggable display object is copied from one DisplayView to another, or copied within a DisplayView
         virtual void OnCopied() = 0;

         /// @brief Called by the framework whenever the display object needs to be drawn during a drag/drop operation.
         /// @param pDC The device context for drawing
         /// @param map The coordinate mapping. Draggable objects are created on demand and do not necessarily belong to a display list and therefore don't have access to the display manager's coordinate map. For this reason, the coordinate map is provided directly in this function.
         /// @param dragStart The starting point of the drag/drop operation in world space
         /// @param dragPoint The current location of the cursor in world space
         virtual void DrawDragImage(CDC* pDC,
                                    std::shared_ptr<const iCoordinateMap> map,
                                    const POINT& dragStart,
                                    const POINT& dragPoint) = 0;
      };
   };
};
