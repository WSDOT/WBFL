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
#include <afxole.h> // For drag and drop
#include <vector>
#include <DManip/DisplayMgr.h>
#include <DManip/DisplayListEvents.h>
#include <DManip/DisplayMgrEvents.h>
#include <DManip/TaskFactory.h>
#include <Colors.h>

namespace WBFL
{
   namespace DManip
   {
      /// @brief A display manager implementing the iDisplayMgr interface
      class DMANIPCLASS DisplayMgr :
         public iDisplayMgr,
         public iDisplayListEvents,
         public std::enable_shared_from_this<DisplayMgr>
      {
      protected:
         DisplayMgr() = default;

      public:
         static std::shared_ptr<DisplayMgr> Create() { return std::shared_ptr<DisplayMgr>(new DisplayMgr()); }
	      virtual ~DisplayMgr();

         // iDisplayMgr Implementation
      public:
         virtual void SetView(CDisplayView* pView) override;

         // Be very careful using the View!!!
         // Do not use the view unless you are ABSOLUTELY SURE that the method you are 
         // calling it from has nothing to do with printing or print preview. If all you 
         // need is scaling, use GetCoordinateMap from below. 
         // If all you want is to call InvalidateRect, or InvalidateRgn, call the methods below
         virtual CDisplayView* GetView() override;
         virtual const CDisplayView* GetView() const override;

         virtual std::shared_ptr<const iCoordinateMap> GetCoordinateMap() const override;

         // Display List Management
         virtual std::shared_ptr<iDisplayList> CreateDisplayList(IDType id) override;
         virtual bool AddDisplayList(std::shared_ptr<iDisplayList> pDL) override;
         virtual std::shared_ptr<iDisplayList> GetDisplayList(IndexType idx) override;
         virtual std::shared_ptr<const iDisplayList> GetDisplayList(IndexType idx) const override;
         virtual std::shared_ptr<iDisplayList> FindDisplayList(IDType id) override;
         virtual std::shared_ptr<const iDisplayList> FindDisplayList(IDType id) const override;
         virtual IndexType GetDisplayListCount() const override;
         virtual void RemoveDisplayList(IDType key, AccessType access) override;
         virtual void ClearDisplayLists() override;

         // Display Object Management
         virtual void AddDisplayObject(std::shared_ptr<iDisplayObject> pDO, IDType key, AccessType access) override;
         virtual std::shared_ptr<iDisplayObject> FindDisplayObject(IDType id, IDType listKey, AccessType access) override;
         virtual std::shared_ptr<const iDisplayObject> FindDisplayObject(IDType id, IDType listKey, AccessType access) const override;
         virtual std::vector<std::shared_ptr<iDisplayObject>> FindDisplayObjects(const POINT& point) override;
         virtual std::vector<std::shared_ptr<const iDisplayObject>> FindDisplayObjects(const POINT& point) const override;
         virtual std::vector<std::shared_ptr<iDisplayObject>> FindDisplayObjects(const WBFL::Geometry::Point2d& point) override;
         virtual std::vector<std::shared_ptr<const iDisplayObject>> FindDisplayObjects(const WBFL::Geometry::Point2d& point) const override;
         virtual std::vector<std::shared_ptr<iDisplayObject>> FindDisplayObjects(const RECT& rect) override;
         virtual std::vector<std::shared_ptr<const iDisplayObject>> FindDisplayObjects(const RECT& rect) const override;
         virtual std::vector<std::shared_ptr<iDisplayObject>> FindDisplayObjects(const WBFL::Geometry::Rect2d& rect) override;
         virtual std::vector<std::shared_ptr<const iDisplayObject>> FindDisplayObjects(const WBFL::Geometry::Rect2d& rect) const override;
         virtual void RemoveDisplayObject(IDType doKey, AccessType doAccess, IDType dlKey, AccessType dlAccess) override;
         virtual void ClearDisplayObjects() override;
         virtual void ClearDisplayObjects(IDType key, AccessType access) override;
         virtual IndexType GetDisplayObjectCount() const override;
         virtual IndexType GetDisplayObjectFactoryCount() const override;
         virtual void AddDisplayObjectFactory(std::shared_ptr<iDisplayObjectFactory> factory) override;
         virtual std::shared_ptr<iDisplayObjectFactory> GetDisplayObjectFactory(IndexType idx) override;
         virtual std::shared_ptr<const iDisplayObjectFactory> GetDisplayObjectFactory(IndexType idx) const override;

         // Selecting and Selections
         virtual void SelectObject(std::shared_ptr<iDisplayObject> pDO, bool bClearSelection) override;
         virtual void SelectObjects(const RECT& r) override;
         virtual void ClearSelectedObjects() override;
         virtual void ClearSelectedObjectsByList(IDType key, AccessType access, bool bInclusive) override;
         virtual std::vector<std::shared_ptr<iDisplayObject>> GetSelectedObjects() override;
         virtual std::vector<std::shared_ptr<const iDisplayObject>> GetSelectedObjects() const override;
         virtual void SelectAll(bool bSelect = true) override;

         // Selection Methods
         virtual void EnableLBtnMultiSelect(bool bEnable, DWORD dwKey) override;
         virtual bool IsLBtnMultiSelectEnabled() const override;
         virtual DWORD GetLBtnMultiSelectKey() const override;
         virtual void EnableLBtnSelectRect(bool bEnable) override;
         virtual bool IsLBtnSelectRectEnabled() const override;
         virtual void EnableLBtnSelect(bool bEnable) override;
         virtual bool IsLBtnSelectEnabled() const override;
         virtual void EnableRBtnSelect(bool bEnable) override;
         virtual bool IsRBtnSelectEnabled() const override;

         // Drawing
         virtual void DrawDisplayObjects(CDC* pDC) const override;
         virtual void SetSelectionFillColor(COLORREF color) override;
         virtual void SetSelectionLineColor(COLORREF color) override;
         virtual COLORREF GetSelectionFillColor() const override;
         virtual COLORREF GetSelectionLineColor() const override;
         virtual WBFL::Geometry::Rect2d GetBoundingBox(bool boundOrigin) const override;

#if defined(_DEBUG)
         virtual void DrawGravityWells(CDC* pDC) const override;
#endif

         // Input Events
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

         // Tool Tips
         virtual BOOL OnNeedToolTipText(UINT id, NMHDR* pNMHDR, LRESULT* pResult) override;
         virtual INT_PTR OnToolHitTest(const POINT& point, TOOLINFO* pTI) override;

         // OLE Drag/Drop Events
         virtual DROPEFFECT OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, const POINT& point) override;
         virtual void OnDragLeave() override;
         virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, const POINT& point) override;
         virtual BOOL OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, const POINT& point) override;
         virtual DROPEFFECT OnDragScroll(DWORD dwKeyState, const POINT& point) override;

         // Drag and Drop
         virtual void PrepareDragData(std::shared_ptr<iDragDataSink> pSink) override;
         virtual void CreateDragObjects(COleDataObject* pDataObject) override;
         virtual void DrawDragObjects(const POINT& dragStart, const POINT& dragPoint) override;
         virtual void DestroyDragObjects() override;
         virtual void RegisterDropSite(std::shared_ptr<iDropSite> pDropSite) override;
         virtual void UnregisterDropSite() override;
         virtual std::shared_ptr<iDropSite> GetDropSite() override;
         virtual void HighlightDropSite(BOOL bHighlight) override;
         virtual void OnDragFinished(DROPEFFECT de) override;

         // Tasks
         virtual void SetTaskFactory(std::shared_ptr<TaskFactory> pFactory) override;
         virtual std::shared_ptr<TaskFactory> GetTaskFactory() override;
         virtual void SetTask(std::shared_ptr<iTask> pTask) override;

         // Event Sink - This gives the canvas a pluggable event handling strategy for events 
         //              that are not handled by display objects
         virtual void RegisterEventSink(std::shared_ptr<iDisplayMgrEvents> pEventSink) override;
         virtual void UnregisterEventSink() override;
         virtual std::shared_ptr<iDisplayMgrEvents> GetEventSink() override;

         // iDisplayListEvents
         virtual void OnDisplayObjectAdded(IDType listID, std::shared_ptr<iDisplayObject> pDO) override;
         virtual void OnDisplayObjectRemoved(IDType listID, IDType doID) override;
         virtual void OnDisplayObjectsCleared(IDType listID) override;

      private:
         CDisplayView* m_pView = nullptr;

         std::vector<std::shared_ptr<iDisplayObjectFactory>> m_DisplayObjectFactories;

         std::shared_ptr<TaskFactory> m_pTaskFactory;
         std::shared_ptr<iTask> m_pCurrTask;

         std::vector<std::shared_ptr<iDraggable>> m_DragList;

         COleDropTarget m_DropTarget; // This view is an OLE drop target

         std::shared_ptr<iDisplayObject> m_ToolTipObject; // Current object for which tool tip text will be requested
         std::_tstring m_strToolTipText;

         std::shared_ptr<iDropSite> m_pDropSite; // Object that a drag/drop payload is about to be dropped on

         std::vector<std::shared_ptr<iDisplayList>> m_DisplayLists;

         DWORD m_dwLBtnMultiSelectKey = MK_CONTROL;
         bool m_bLBtnMultiSelectEnabled = false;
         bool m_bLBtnRectSelectEnabled = false;
         bool m_bLBtnSelectEnabled = false;
         bool m_bRBtnSelectEnabled = false;

         COLORREF m_crSelectionFill = RED;
         COLORREF m_crSelectionLine = RED4;

         std::vector<std::shared_ptr<iDisplayObject>> m_SelectedObjects;  // The display objects that are currently selected

         std::vector<std::shared_ptr<iDisplayObject>> FindAllDisplayObjects(const POINT& point);
         std::vector<std::shared_ptr<iDisplayObject>> FindAllSelectableDisplayObjects(const POINT& point);
         std::shared_ptr<iDisplayObject> FindNextSelectableDisplayObject(const POINT& point);

         std::shared_ptr<iDisplayMgrEvents> m_EventSink;
      };
   };
};
