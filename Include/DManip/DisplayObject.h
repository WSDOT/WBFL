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
#include <DManip/DManipTypes.h>
#include <GeomModel/Primitives.h>
#include <memory>
#include <string>

namespace WBFL
{
   namespace DManip
   {
      class iCoordinateMap;
      class iDisplayList;
      class iDisplayObjectEvents;
      class iDropSite;
      class iGravityWellStrategy;

      /// @brief Interface defining a display object
      /// @param pDL 
      class DMANIPCLASS iDisplayObject
      {
      public:
#if defined _DEBUG
         iDisplayObject();
         virtual ~iDisplayObject();
#endif
         /// @brief The display object identifier.
         virtual void SetID(IDType id) = 0;
         virtual IDType GetID() const = 0;

         /// @brief Sets data on the object.
         /// @param pVoid A void pointer to the item data
         /// @param bDelete if true, the display object will delete the data
         virtual void SetItemData(void* pVoid,bool bDelete) = 0;
         virtual void GetItemData(void** ppVoid) = 0;

         /// @brief Associates the display list in which the display object is contained
         virtual void SetDisplayList(std::weak_ptr<iDisplayList> pDL) = 0;
         virtual std::shared_ptr<iDisplayList> GetDisplayList() = 0;
         virtual std::shared_ptr<const iDisplayList> GetDisplayList() const = 0;

         /// @brief Indicates if a display object is visible. Only visible display objects drawn.
         virtual void Visible(bool bVisible) = 0;
         virtual bool IsVisible() const = 0;

         // Drawing
         /// @brief Called by the framework when a display objects needs to draw itself
         virtual void Draw(CDC* pDC) = 0;
         /// @brief Called by the framework when a display objects needs to draw itself in a highlighted state
         virtual void Highlight(CDC* pDC, bool bHighlight) = 0;
      #if defined(_DEBUG)
         virtual void DrawGravityWell(CDC* pDC) = 0;
      #endif

         // Size and Hit Testing
         /// @brief Associates a gravity well with the display object for customized hit testing
         virtual void SetGravityWellStrategy(std::shared_ptr<iGravityWellStrategy> pStrategy) = 0;
         virtual std::shared_ptr<iGravityWellStrategy> GetGravityWellStrategy() = 0;

         /// @brief Returns true if a logical point is within the display object
         virtual bool HitTest(const POINT& point) const = 0;

         /// @brief Returns true if the display object touches a logical space rectangle
         virtual bool TouchesRect(const RECT& r) const = 0;

         /// @brief Returns the bounding box in logical coordinates
         /// @return 
         virtual RECT GetLogicalBoundingBox() const = 0;

         /// @brief Returns the bounding box in model space coordinates
         virtual WBFL::Geometry::Rect2d GetBoundingBox() const = 0;

         // Selection
         /// @brief Selects or unselects the display object
         virtual void Select(bool bSelect) = 0;
         virtual bool IsSelected() const = 0;

         /// @brief Sets the selection type
         virtual void SetSelectionType(SelectionType st) = 0;
         virtual SelectionType GetSelectionType() const = 0;

         /// @brief Indicates if a display object should retain its selection state if it is clicked on
         virtual void RetainSelection(bool bRetain) = 0;
         virtual bool RetainSelection() const = 0;

         // Tool Tips
         virtual void SetToolTipText(LPCTSTR lpszToolTipText) = 0;
         virtual std::_tstring GetToolTipText() const = 0;
         virtual void SetMaxTipWidth(INT maxWidth) = 0;
         virtual INT GetMaxTipWidth() const = 0;
         virtual void SetTipDisplayTime(INT iTime) = 0;
         virtual INT GetTipDisplayTime() const = 0;

         // Interface Events
         // Called by the framework when UI events occur that are directed
         // towards this display object.
         virtual bool OnLButtonDown(UINT nFlags,const POINT& point) = 0;
         virtual bool OnLButtonUp(UINT nFlags, const POINT& point) = 0;
         virtual bool OnLButtonDblClk(UINT nFlags, const POINT& point) = 0;
         virtual bool OnRButtonDown(UINT nFlags, const POINT& point) = 0;
         virtual bool OnRButtonUp(UINT nFlags, const POINT& point) = 0;
         virtual bool OnRButtonDblClk(UINT nFlags, const POINT& point) = 0;
         virtual bool OnMouseMove(UINT nFlags, const POINT& point) = 0;
         virtual bool OnMouseWheel(UINT nFlags,short zDelta, const POINT& point) = 0;
         virtual bool OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) = 0;
         virtual bool OnContextMenu(CWnd* pWnd, const POINT& point) = 0;

         // Event Sink
         virtual void RegisterEventSink(std::shared_ptr<iDisplayObjectEvents> pEventSink) = 0;
         virtual void UnregisterEventSink() = 0;
         virtual std::shared_ptr<iDisplayObjectEvents> GetEventSink() = 0;

         // Drag Drop
         virtual void RegisterDropSite(std::shared_ptr<iDropSite> pDropSite) = 0;
         virtual void UnregisterDropSite() = 0;
         virtual std::shared_ptr<iDropSite> GetDropSite() = 0;

         /// @brief Associates a parent display object, if this display object is in a parent-child composition
         virtual void SetParent(std::weak_ptr<iDisplayObject> pParent) = 0;
         virtual std::shared_ptr<iDisplayObject> GetParent() = 0;
      };
   };
};
