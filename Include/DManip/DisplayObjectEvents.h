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
      class iDisplayObject;

      /// @brief Interface implemented by objects wanting to receive display object events. Objects implementing this interface
      /// provide application specific event processing for individual display objects. The first parameter in all of the methods
      /// on this interface is the display object to which the event belongs. This allows a single display objects event object to
      /// be registered with multiple display objects
      class DMANIPCLASS iDisplayObjectEvents
      {
      public:
         // UI Events that are directed towards the display object
         virtual bool OnLButtonDblClk(std::shared_ptr<iDisplayObject> pDO,UINT nFlags, const POINT& point) = 0;
         virtual bool OnLButtonDown(std::shared_ptr<iDisplayObject> pDO,UINT nFlags, const POINT& point) = 0;
         virtual bool OnLButtonUp(std::shared_ptr<iDisplayObject> pDO,UINT nFlags, const POINT& point) = 0;
         virtual bool OnRButtonDblClk(std::shared_ptr<iDisplayObject> pDO,UINT nFlags, const POINT& point) = 0;
         virtual bool OnRButtonDown(std::shared_ptr<iDisplayObject> pDO,UINT nFlags, const POINT& point) = 0;
         virtual bool OnRButtonUp(std::shared_ptr<iDisplayObject> pDO,UINT nFlags, const POINT& point) = 0;
         virtual bool OnMouseMove(std::shared_ptr<iDisplayObject> pDO,UINT nFlags, const POINT& point) = 0;
         virtual bool OnMouseWheel(std::shared_ptr<iDisplayObject> pDO,UINT nFlags,short zDelta, const POINT& point) = 0;
         virtual bool OnKeyDown(std::shared_ptr<iDisplayObject> pDO,UINT nChar, UINT nRepCnt, UINT nFlags) = 0;
         virtual bool OnContextMenu(std::shared_ptr<iDisplayObject> pDO,CWnd* pWnd, const POINT& point) = 0;

         /// @brief The display object contains some internal data that was changed
         virtual void OnChanged(std::shared_ptr<iDisplayObject> pDO) = 0;

         /// @brief The display object was moved to a different location on the canvas via dragging
         virtual void OnDragMoved(std::shared_ptr<iDisplayObject> pDO, const WBFL::Geometry::Size2d& offset) = 0;

         /// @brief The display object was drag and dropped
         virtual void OnMoved(std::shared_ptr<iDisplayObject> pDO) = 0;

         /// @brief The display object was drag/dropped copied
         virtual void OnCopied(std::shared_ptr<iDisplayObject> pDO) = 0;

          /// @brief The display object was selected
          virtual void OnSelect(std::shared_ptr<iDisplayObject> pDO) = 0;

          /// @brief The display object was unselected
          virtual void OnUnselect(std::shared_ptr<iDisplayObject> pDO) = 0;
      };
   };
};
