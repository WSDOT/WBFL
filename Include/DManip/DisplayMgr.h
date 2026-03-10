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
#include <DManip/DManipTypes.h>
#include <DManip/CoordinateMap.h>

class CDisplayView;

namespace WBFL
{
   namespace DManip
   {
      class iCoordinateMap;
      class iDisplayObject;
      class iDisplayObjectFactory;
      class iDisplayList;
      class iDropSite;
      class iDraggable;
      class iDragDataSink;
      class iTask;
      class iDisplayMgrEvents;
      class TaskFactory;

      /// @brief Interface defining a Display Manager 
      /// The display manager is responsible for managing the display lists, display objects, selections, 
      /// drawing, scaling, drag and drop, events, and tasks. 
      /// The display manager coordinates all of the interactions of the direct manipulation framework.
      class DMANIPCLASS iDisplayMgr
      {
      public:
#if defined _DEBUG
         iDisplayMgr();
         virtual ~iDisplayMgr();
#endif

         /// @brief Sets the associated view class
         /// @param pView 
         virtual void SetView(CDisplayView* pView) = 0;
         virtual CDisplayView* GetView() = 0;
         virtual const CDisplayView* GetView() const = 0;

         /// @brief Returns the coordinate mapping object
         /// @return 
         virtual std::shared_ptr<const iCoordinateMap> GetCoordinateMap() const = 0;

         /// @brief Creates a new display list.
         /// @param id Must be a unique ID.
         /// @return The new display list, or nullptr if failed to create
         virtual std::shared_ptr<iDisplayList> CreateDisplayList(IDType id) = 0;

         /// @brief Adds a previously created display list. The display list ID must be unique
         /// @param pDL 
         /// @return true if successful
         virtual bool AddDisplayList(std::shared_ptr<iDisplayList> pDL) = 0;

         /// @brief Returns a display list
         /// @param idx 
         /// @return 
         virtual std::shared_ptr<iDisplayList> GetDisplayList(IndexType idx) = 0;
         virtual std::shared_ptr<const iDisplayList> GetDisplayList(IndexType idx) const = 0;

         /// @brief Find a display list based on its ID
         /// @param id 
         /// @return 
         virtual std::shared_ptr<iDisplayList> FindDisplayList(IDType id) = 0;
         virtual std::shared_ptr<const iDisplayList> FindDisplayList(IDType id) const = 0;

         /// @brief Returns the number of display lists
         /// @return 
         virtual IndexType GetDisplayListCount() const = 0;

         /// @brief Removes a display list
         /// @param key 
         /// @param access 
         virtual void RemoveDisplayList(IDType key,AccessType access) = 0;

         /// @brief Clears all display lists
         virtual void ClearDisplayLists() = 0;

         /// @brief Adds a display object to a display list
         /// @param pDO 
         /// @param key key that identifies the display list
         /// @param access Identifies the type of key
         virtual void AddDisplayObject(std::shared_ptr<iDisplayObject> pDO,IDType key,AccessType access) = 0;

         /// @brief Find a display object
         /// @param id ID of the display object to find
         /// @param listKey 
         /// @param access 
         /// @return 
         virtual std::shared_ptr<iDisplayObject> FindDisplayObject(IDType id, IDType listKey, AccessType access) = 0;
         virtual std::shared_ptr<const iDisplayObject> FindDisplayObject(IDType id, IDType listKey, AccessType access) const = 0;

         /// @brief Searches all display lists to find display objects containing a logical point
         /// @param point 
         /// @return 
         virtual std::vector<std::shared_ptr<iDisplayObject>> FindDisplayObjects(const POINT& point) = 0;
         virtual std::vector<std::shared_ptr<const iDisplayObject>> FindDisplayObjects(const POINT& point) const = 0;

         /// @brief Searches all display lists to find display objects containing a model space point
         /// @param point 
         /// @return 
         virtual std::vector<std::shared_ptr<iDisplayObject>> FindDisplayObjects(const WBFL::Geometry::Point2d& point) = 0;
         virtual std::vector<std::shared_ptr<const iDisplayObject>> FindDisplayObjects(const WBFL::Geometry::Point2d& point) const = 0;

         /// @brief Searches all display lists to find display objects contained within a logical rectangle
         /// @param rect 
         /// @return 
         virtual std::vector<std::shared_ptr<iDisplayObject>> FindDisplayObjects(const RECT& rect) = 0;
         virtual std::vector<std::shared_ptr<const iDisplayObject>> FindDisplayObjects(const RECT& rect) const = 0;

         /// @brief Searches all display lists to find display objects contained within a model space rectangle
         /// @param rect 
         /// @return 
         virtual std::vector<std::shared_ptr<iDisplayObject>> FindDisplayObjects(const WBFL::Geometry::Rect2d& rect) = 0;
         virtual std::vector<std::shared_ptr<const iDisplayObject>> FindDisplayObjects(const WBFL::Geometry::Rect2d& rect) const = 0;

         /// @brief Removes a display object from a display list
         /// @param doKey 
         /// @param doAccess 
         /// @param dlKey 
         /// @param dlAccess 
         virtual void RemoveDisplayObject(IDType doKey,AccessType doAccess,IDType dlKey,AccessType dlAccess) = 0;

         /// @brief Clears all display objects from all display lists
         virtual void ClearDisplayObjects() = 0;

         /// @brief Clears all display objects from the specified display list
         /// @param key 
         /// @param access 
         virtual void ClearDisplayObjects(IDType key,AccessType access) = 0;

         /// @brief Returns the number of display objects in all display lists
         /// @return 
         virtual IndexType GetDisplayObjectCount() const = 0;

         /// @brief Adds a display object factory
         /// @param factory 
         virtual void AddDisplayObjectFactory(std::shared_ptr<iDisplayObjectFactory> factory) = 0;
         virtual std::shared_ptr<iDisplayObjectFactory> GetDisplayObjectFactory(IndexType idx) = 0;
         virtual std::shared_ptr<const iDisplayObjectFactory> GetDisplayObjectFactory(IndexType idx) const = 0;
         /// @brief Returns the number of display object factories
         /// @return 
         virtual IndexType GetDisplayObjectFactoryCount() const = 0;

         // Selecting and Selections
         
         /// @brief Selects a display object
         /// @param pDO The display object to select
         /// @param bClearSelection If true, clears any previous selection
         virtual void SelectObject(std::shared_ptr<iDisplayObject> pDO,bool bClearSelection) = 0;

         /// @brief Selects all selectable display objects within a logical rectangle
         /// @param r 
         virtual void SelectObjects(const RECT& r) = 0;

         /// @brief Clears all selected display objects
         virtual void ClearSelectedObjects() = 0;

         /// @brief Clears all selected display objects associated with a display list
         /// @param key 
         /// @param access 
         /// @param bInclusive If true, the selected display objects belonging to the specified display list are unselected, otherwise all but the selected display objects belonging to the specified display list are unselected
         virtual void ClearSelectedObjectsByList(IDType key,AccessType access,bool bInclusive) = 0;

         /// @brief Returns the selected display objects
         /// @return 
         virtual std::vector<std::shared_ptr<iDisplayObject>> GetSelectedObjects() = 0;
         virtual std::vector<std::shared_ptr<const iDisplayObject>> GetSelectedObjects() const = 0;

         /// @brief Selects, or unselects all selectable display objects
         /// @param bSelect 
         virtual void SelectAll(bool bSelect = true) = 0;

         // Selection Methods

         /// @brief Enables left button multi-select
         /// @param bEnable 
         /// @param dwKey Key to press along with left button for multi-select to occur
         virtual void EnableLBtnMultiSelect(bool bEnable,DWORD dwKey) = 0;
         virtual bool IsLBtnMultiSelectEnabled() const = 0;
         virtual DWORD GetLBtnMultiSelectKey() const = 0;

         /// @brief Enables selection by drawing a rectangle with the left mouse button clicked
         /// @param bEnable 
         virtual void EnableLBtnSelectRect(bool bEnable) = 0;
         virtual bool IsLBtnSelectRectEnabled() const = 0;

         /// @brief Enables object selection with the left mouse button
         /// @param bEnable 
         virtual void EnableLBtnSelect(bool bEnable) = 0;
         virtual bool IsLBtnSelectEnabled() const = 0;

         /// @brief Enables object selection with the right mouse button
         /// @param bEnable 
         virtual void EnableRBtnSelect(bool bEnable) = 0;
         virtual bool IsRBtnSelectEnabled() const = 0;

         // Drawing

         /// @brief Draws all of the visible display objects
         /// @param pDC 
         virtual void DrawDisplayObjects(CDC* pDC) const = 0;

         /// @brief Sets the fill color for selected objects
         /// @param color 
         virtual void SetSelectionFillColor(COLORREF color) = 0;
         virtual COLORREF GetSelectionFillColor() const = 0;

         /// @brief Sets the line color for selected display objects
         /// @param color 
         virtual void SetSelectionLineColor(COLORREF color) = 0;
         virtual COLORREF GetSelectionLineColor() const = 0;

         /// @brief Returns the model space bounding box.
         /// @param boundOrigin If true, the bounding box will include (0,0)
         /// @return 
         virtual WBFL::Geometry::Rect2d GetBoundingBox(bool boundOrigin) const = 0;

      #if defined(_DEBUG)
         virtual void DrawGravityWells(CDC* pDC) const = 0;
      #endif

         /// @{
         /// Input Events
         virtual bool OnLButtonDown(UINT nFlags,const POINT& point) = 0;
         virtual bool OnLButtonUp(UINT nFlags, const POINT& point) = 0;
         virtual bool OnLButtonDblClk(UINT nFlags, const POINT& point) = 0;
         virtual bool OnRButtonDown(UINT nFlags, const POINT& point) = 0;
         virtual bool OnRButtonUp(UINT nFlags, const POINT& point) = 0;
         virtual bool OnRButtonDblClk(UINT nFlags, const POINT& point) = 0;
         virtual bool OnMouseMove(UINT nFlags, const POINT& point) = 0;
         virtual bool OnMouseWheel(UINT nFlags, short zDelta, const POINT& point) = 0;
         virtual bool OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) = 0;
         virtual bool OnContextMenu(CWnd* pWnd, const POINT& point) = 0;
         /// @}

         /// @{
         /// Tool Tips
         virtual BOOL OnNeedToolTipText(UINT id,NMHDR* pNMHDR,LRESULT* pResult) = 0;
         virtual INT_PTR OnToolHitTest(const POINT& point,TOOLINFO* pTI) = 0;
         /// @}

         /// @{
         // OLE Drag/Drop Events
 	      virtual DROPEFFECT OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, const POINT& point) = 0;
	      virtual void OnDragLeave() = 0;
	      virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, const POINT& point) = 0;
	      virtual BOOL OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, const POINT& point) = 0;
         virtual DROPEFFECT OnDragScroll( DWORD dwKeyState, const POINT& point ) = 0;
         /// @}

         /// @{
         // Drag and Drop
         virtual void PrepareDragData(std::shared_ptr<iDragDataSink> pSink) = 0;
         virtual void CreateDragObjects(COleDataObject* pDataObject) = 0;
         virtual void DrawDragObjects(const POINT& dragStart, const POINT& dragPoint) = 0;
         virtual void DestroyDragObjects() = 0;
         virtual void RegisterDropSite(std::shared_ptr<iDropSite> pDropSite) = 0;
         virtual void UnregisterDropSite() = 0;
         virtual std::shared_ptr<iDropSite> GetDropSite() = 0;
         virtual void HighlightDropSite(BOOL bHighlight) = 0;
         virtual void OnDragFinished(DROPEFFECT de) = 0;
         /// @}

         /// @{
         // Tasks
         virtual void SetTaskFactory(std::shared_ptr<TaskFactory> pFactory) = 0;
         virtual std::shared_ptr<TaskFactory> GetTaskFactory() = 0;
         virtual void SetTask(std::shared_ptr<iTask> pTask) = 0;
         /// @}

         /// @{
         /// Event Sink - This gives the canvas a pluggable event handling strategy for events that are not handled by display objects
         virtual void RegisterEventSink(std::shared_ptr<iDisplayMgrEvents> pEventSink) = 0;
         virtual void UnregisterEventSink() = 0;
         virtual std::shared_ptr<iDisplayMgrEvents> GetEventSink() = 0;
         /// @}
      };
   };
};
