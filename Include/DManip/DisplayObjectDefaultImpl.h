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
#include <DManip/DisplayObject.h>
#include <DManip/DisplayObjectEvents.h>
#include <DManip/DisplayList.h>
#include <DManip/GravityWellStrategy.h>
#include <set>

namespace WBFL
{
   namespace DManip
   {
      class iDropSite;
      class NestedDisplayObjectEventRelay;

      /// @brief This class implements the majority of the iDisplayObject interface
      /// Many derived display object interfaces inherit from this class to provide a near
      /// complete implementation.
      class DMANIPCLASS DisplayObjectDefaultImpl : public iDisplayObject, public std::enable_shared_from_this<DisplayObjectDefaultImpl>
      {
      public:
	      DisplayObjectDefaultImpl(IDType id = INVALID_ID);
	      virtual ~DisplayObjectDefaultImpl();

         virtual void SetID(IDType id) override;
         virtual IDType GetID() const override;

         virtual void SetItemData(void* pVoid, bool bDelete) override;
         virtual void GetItemData(void** ppVoid) override;

         virtual void SetDisplayList(std::weak_ptr<iDisplayList> pDL) override;
         virtual std::shared_ptr<iDisplayList> GetDisplayList() override;
         virtual std::shared_ptr<const iDisplayList> GetDisplayList() const override;

         virtual void Visible(bool bVisible) override;
         virtual bool IsVisible() const override;

         // Drawing
         //virtual void Draw(CDC* pDC) override;
         //virtual void Highlight(CDC* pDC, bool bHighlight) override;
#if defined(_DEBUG)
         virtual void DrawGravityWell(CDC* pDC) override;
#endif

         // Size and Hit Testing
         virtual void SetGravityWellStrategy(std::shared_ptr<iGravityWellStrategy> pStrategy) override;
         virtual std::shared_ptr<iGravityWellStrategy> GetGravityWellStrategy() override;
         virtual bool HitTest(const POINT& point) const override;
         virtual RECT GetLogicalBoundingBox() const override;
         //virtual WBFL::Geometry::Rect2d GetBoundingBox() const override; // subclasses need to implement
         virtual bool TouchesRect(const RECT& r) const override;

         // Selection
         virtual void Select(bool bSelect) override;
         virtual bool IsSelected() const override;
         virtual void SetSelectionType(SelectionType st) override;
         virtual SelectionType GetSelectionType() const override;
         virtual void  RetainSelection(bool bRetain) override;
         virtual bool  RetainSelection() const override;

         // Tool Tips
         virtual void SetToolTipText(LPCTSTR lpszToolTipText) override;
         virtual std::_tstring GetToolTipText() const override;
         virtual void SetMaxTipWidth(INT maxWidth) override;
         virtual INT GetMaxTipWidth() const override;
         virtual void SetTipDisplayTime(INT iTime) override;
         virtual INT GetTipDisplayTime() const override;

         // Interface Events
         // Called by the framework when UI events occur that are directed
         // towards this display object.
         virtual bool OnLButtonDown(UINT nFlags, const POINT& point) override;
         virtual bool OnLButtonUp(UINT nFlags, const POINT& point) override;
         virtual bool OnLButtonDblClk(UINT nFlags, const POINT& point) override;
         virtual bool OnRButtonDown(UINT nFlags, const POINT& point) override;
         virtual bool OnRButtonUp(UINT nFlags, const POINT& point) override;
         virtual bool OnRButtonDblClk(UINT nFlags, const POINT& point) override;
         virtual bool OnMouseMove(UINT nFlags, const POINT& point) override;
         virtual bool OnMouseWheel(UINT nFlags, short zDelta, const POINT& point) override;
         virtual bool OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) override;
         virtual bool OnContextMenu(CWnd* pWnd, const POINT& point) override;

         // Event Sink
         virtual void RegisterEventSink(std::shared_ptr<iDisplayObjectEvents> pEventSink) override;
         virtual void UnregisterEventSink() override;
         virtual std::shared_ptr<iDisplayObjectEvents> GetEventSink() override;

         // Drag Drop
         virtual void RegisterDropSite(std::shared_ptr<iDropSite> pDropSite) override;
         virtual void UnregisterDropSite() override;
         virtual std::shared_ptr<iDropSite> GetDropSite() override;

         // Composite linkage
         virtual void SetParent(std::weak_ptr<iDisplayObject> pParent) override;
         virtual std::shared_ptr<iDisplayObject> GetParent() override;

      protected:
         IDType m_ID = INVALID_ID;
         bool m_bIsVisible = true;
         std::weak_ptr<iDisplayList> m_pDispList;

         std::shared_ptr<iGravityWellStrategy> m_pGravityWellStrategy;
         std::shared_ptr<iDropSite> m_pDropSite;
         bool m_bSelected = false;
         bool m_bRetainSelection = true;
         std::_tstring m_strToolTipText = _T("");
         INT m_MaxToolTipWidth = -1;
         INT m_ToolTipDisplayTime = -1;
         SelectionType m_SelectionType = SelectionType::None;
         WBFL::Geometry::Rect2d m_ReusableRect;

         void* m_pItemData = nullptr;
         bool m_bDeleteItemData = false;

         std::shared_ptr<iDisplayObjectEvents> m_EventSink;

         std::weak_ptr<iDisplayObject> m_pCompositeParent;


         // Notifies all sinks of display object events
         friend NestedDisplayObjectEventRelay;
         virtual void Fire_OnChanged();
         virtual void Fire_OnDragMoved(const WBFL::Geometry::Size2d& offset);
         virtual void Fire_OnMoved();
         virtual void Fire_OnCopied();
         virtual bool Fire_OnLButtonDown(UINT nFlags, const POINT& point);
         virtual bool Fire_OnLButtonUp(UINT nFlags, const POINT& point);
         virtual bool Fire_OnLButtonDblClk(UINT nFlags, const POINT& point);
         virtual bool Fire_OnRButtonDown(UINT nFlags, const POINT& point);
         virtual bool Fire_OnRButtonUp(UINT nFlags, const POINT& point);
         virtual bool Fire_OnRButtonDblClk(UINT nFlags, const POINT& point);
         virtual bool Fire_OnMouseMove(UINT nFlags, const POINT& point);
         virtual bool Fire_OnMouseWheel(UINT nFlags, short zDelta, const POINT& point);
         virtual bool Fire_OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
         virtual bool Fire_OnContextMenu(CWnd* pWnd, const POINT& point);
         virtual void Fire_OnSelect();
         virtual void Fire_OnUnselect();
      };
   };
};
