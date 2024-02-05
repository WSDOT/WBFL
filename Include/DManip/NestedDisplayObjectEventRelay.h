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
#include <DManip/DisplayObjectDefaultImpl.h>


namespace WBFL
{
   namespace DManip
   {
      /// @brief Relays events from iDisplayObjectEvents to a parent display object.
      /// This object should be used in the implementation of display objects that delegate
      /// some or all of their implementation to a nested display object. An example is
      /// DimensionLine that delegates the text block part of the implementation to an iTextBlock
      /// display object. The parent object (DimensionLine) listens for event on the delegate (text block)
      /// and then calls it's own event notification functions. A circular reference between the parent object
      /// and the delegate occurs when the parent listens for events directly. This results in memory leaks.
      /// This object breaks the circular dependency.
      class NestedDisplayObjectEventRelay : public iDisplayObjectEvents
      {
      private:
         NestedDisplayObjectEventRelay(DisplayObjectDefaultImpl* parent);

      public:
         static std::shared_ptr<NestedDisplayObjectEventRelay> Create(DisplayObjectDefaultImpl* parent);
         virtual ~NestedDisplayObjectEventRelay() = default;

         virtual void OnChanged(std::shared_ptr<iDisplayObject> pDO) override;
         virtual void OnDragMoved(std::shared_ptr<iDisplayObject> pDO, const WBFL::Geometry::Size2d& offset) override;
         virtual bool OnKeyDown(std::shared_ptr<iDisplayObject> pDO, UINT nChar, UINT nRepCnt, UINT nFlags) override;
         virtual bool OnContextMenu(std::shared_ptr<iDisplayObject> pDO, CWnd* pWnd, const POINT& point) override;
         virtual bool OnLButtonDblClk(std::shared_ptr<iDisplayObject> pDO, UINT nFlags, const POINT& point) override;
         virtual bool OnLButtonDown(std::shared_ptr<iDisplayObject> pDO, UINT nFlags, const POINT& point) override;
         virtual bool OnLButtonUp(std::shared_ptr<iDisplayObject> pDO, UINT nFlags, const POINT& point) override;
         virtual bool OnRButtonDblClk(std::shared_ptr<iDisplayObject> pDO, UINT nFlags, const POINT& point) override;
         virtual bool OnRButtonDown(std::shared_ptr<iDisplayObject> pDO, UINT nFlags, const POINT& point) override;
         virtual bool OnRButtonUp(std::shared_ptr<iDisplayObject> pDO, UINT nFlags, const POINT& point) override;
         virtual bool OnMouseMove(std::shared_ptr<iDisplayObject> pDO, UINT nFlags, const POINT& point) override;
         virtual bool OnMouseWheel(std::shared_ptr<iDisplayObject> pDO, UINT nFlags, short zDelta, const POINT& point) override;
         virtual void OnMoved(std::shared_ptr<iDisplayObject> pDO) override;
         virtual void OnCopied(std::shared_ptr<iDisplayObject> pDO) override;
         virtual void OnSelect(std::shared_ptr<iDisplayObject> pDO) override;
         virtual void OnUnselect(std::shared_ptr<iDisplayObject> pDO) override;

      private:
         DisplayObjectDefaultImpl* m_pParent = nullptr;
      };
   };
};
