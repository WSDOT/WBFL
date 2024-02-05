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

#include "pch.h"
#include <DManip/DisplayMgrImpl.h>
#include <DManip/DisplayView.h>
#include <DManip/DisplayObject.h>
#include <DManip/DisplayList.h>
#include <DManip/DropSite.h>
#include <DManip/CompositeDisplayObject.h>
#include <DManip/DisplayListImpl.h>
#include <DManip/DisplayObjectFactoryImpl.h>
#include <DManip/DragDataImpl.h>
#include <DManip/ToolImpl.h>

#include <DManip/Task.h>
#include <DManip/TaskFactory.h>

#include "Helpers.h"

using namespace WBFL::DManip;

DisplayMgr::~DisplayMgr()
{
   m_SelectedObjects.clear(); // don't call ClearSelectedObjects here - it depends on DisplayMgr, which is being destroyed
   ClearDisplayLists();
   m_DropTarget.Revoke();
}

void DisplayMgr::PrepareDragData(std::shared_ptr<iDragDataSink> pSink)
{
   std::for_each(m_SelectedObjects.begin(), m_SelectedObjects.end(), [pSink](auto& display_object)
      {
         auto draggable = std::dynamic_pointer_cast<iDraggable>(display_object);
         CHECK(draggable);
         draggable->PrepareDrag(pSink);
      });
}

void DisplayMgr::SetView(CDisplayView* pView)
{
   // because of the implementation of Revoke and Register, we need to work
   // in the app module state

   AFX_MANAGE_STATE(AfxGetAppModuleState());
   if ( m_pView )
   {
      m_DropTarget.Revoke();
   }

   m_pView = pView;

   // If this VERIFY fails, you most likely initialized COM with
   // CoInitialize instead of OleInitialize. You must use
   // OleInitialize for drag and drop to work
   VERIFY( m_DropTarget.Register(m_pView) );
}

CDisplayView* DisplayMgr::GetView()
{
   return m_pView;
}

const CDisplayView* DisplayMgr::GetView() const
{
   return m_pView;
}

std::shared_ptr<const iCoordinateMap> DisplayMgr::GetCoordinateMap() const
{
   return m_pView->GetCoordinateMap();
}

std::shared_ptr<iDisplayList> DisplayMgr::CreateDisplayList(IDType id)
{
   auto dl = DisplayList::Create(id);
   if (AddDisplayList(dl))
      return dl;
   else
      return std::shared_ptr<iDisplayList>();
}

bool DisplayMgr::AddDisplayList(std::shared_ptr<iDisplayList> pDL)
{
   IDType id = pDL->GetID();
   auto pDLExists = FindDisplayList(id);
   if (pDLExists)
   {
      CHECK(false);
      return false; // A display list with this id already exists
   }

   m_DisplayLists.emplace_back(pDL);
   pDL->SetDisplayMgr(weak_from_this());

   auto event_sink = std::dynamic_pointer_cast<iDisplayListEvents>(shared_from_this());
   pDL->RegisterEventSink(event_sink);
   return true;
}

std::shared_ptr<iDisplayList> DisplayMgr::GetDisplayList(IndexType idx)
{
   PRECONDITION(0 <= idx and idx < m_DisplayLists.size());
   return m_DisplayLists[idx];
}

std::shared_ptr<const iDisplayList> DisplayMgr::GetDisplayList(IndexType idx) const
{
   PRECONDITION(0 <= idx and idx < m_DisplayLists.size());
   return m_DisplayLists[idx];
}

std::shared_ptr<iDisplayList> DisplayMgr::FindDisplayList(IDType id)
{
   auto iter = std::find_if(m_DisplayLists.begin(), m_DisplayLists.end(), [id](auto& list) {return list->GetID() == id; });

   std::shared_ptr<iDisplayList> list;
   if (iter != m_DisplayLists.end())
   {
      list = *iter;
   }
   return list;
}

std::shared_ptr<const iDisplayList> DisplayMgr::FindDisplayList(IDType id) const
{
   auto iter = std::find_if(m_DisplayLists.begin(), m_DisplayLists.end(), [id](auto& list) {return list->GetID() == id; });

   std::shared_ptr<iDisplayList> list;
   if (iter != m_DisplayLists.end())
   {
      list = *iter;
   }
   return list;
}

IndexType DisplayMgr::GetDisplayListCount() const
{
   return m_DisplayLists.size();
}

void DisplayMgr::RemoveDisplayList(IDType key,AccessType access)
{
   std::shared_ptr<iDisplayList> pDL;
   decltype(m_DisplayLists.begin()) iter;
   if ( access == AccessType::ByIndex )
   {
      // Remove by index
      IndexType index = (IndexType)key;
      PRECONDITION(0 <= index && index < m_DisplayLists.size());

      iter = m_DisplayLists.begin() + index;
   }
   else
   {
      // Remove by id
      iter = std::find_if(m_DisplayLists.begin(), m_DisplayLists.end(), [key](auto& list) {return list->GetID() == key; });
   }

   if (iter != m_DisplayLists.end())
   {
      pDL = *iter;
      pDL->UnregisterEventSink();
      m_DisplayLists.erase(iter);
   }
}

void DisplayMgr::ClearDisplayLists()
{
   std::for_each(m_DisplayLists.begin(), m_DisplayLists.end(), [](auto& list) {list->Clear(); list->UnregisterEventSink(); });
   m_DisplayLists.clear();
}

void DisplayMgr::AddDisplayObject(std::shared_ptr<iDisplayObject> pDO, IDType key, AccessType access)
{
   std::shared_ptr<iDisplayList> pDL;
   if ( access == AccessType::ByIndex )
      pDL = GetDisplayList(key);
   else
      pDL = FindDisplayList(key);

   if ( pDL )
      pDL->AddDisplayObject(pDO);
}

void DisplayMgr::SelectObject(std::shared_ptr<iDisplayObject> pDO, bool bClearSelection)
{
   if ( bClearSelection )
      ClearSelectedObjects();

   // Only call Select if the display object is not currently selected
   // otherwise there will be recursion until the stack pops.
   if ( !pDO->IsSelected() && pDO->GetSelectionType() != SelectionType::None )
   {
      pDO->Select(TRUE);
      m_SelectedObjects.emplace_back(pDO);

      CRect bbox = pDO->GetLogicalBoundingBox();
      m_pView->InvalidateRect(bbox);
   }
}

void DisplayMgr::SelectObjects(const RECT& rect)
{
   auto dispObjs = FindDisplayObjects(rect);

   // If Multi-select isn't enabled and if more than one object was
   // found, don't do the selection.
   if ( !m_bLBtnMultiSelectEnabled && 1 < dispObjs.size() )
      return;

   std::for_each(dispObjs.begin(), dispObjs.end(), [this](auto& dispObj) {this->SelectObject(dispObj, FALSE); }); // Don't clear current selection
}

void DisplayMgr::RemoveDisplayObject(IDType doKey,AccessType doAccess,IDType dlKey,AccessType dlAccess)
{
   std::shared_ptr<iDisplayList> pDL;

   if ( dlAccess == AccessType::ByIndex )
      pDL = GetDisplayList(dlKey);
   else
      pDL = FindDisplayList(dlKey);

   if ( pDL )
      pDL->RemoveDisplayObject(doKey,doAccess);
}

void DisplayMgr::ClearDisplayObjects()
{
   m_SelectedObjects.clear();

   // Clears all display objects from all display list
   std::for_each(m_DisplayLists.begin(), m_DisplayLists.end(), [](auto& list) {list->Clear(); });
}

void DisplayMgr::ClearDisplayObjects(IDType key,AccessType access)
{
   // Clear the display objects from the specified display list;
   std::shared_ptr<iDisplayList> pDL;
   if ( access == AccessType::ByIndex )
      pDL = GetDisplayList(key);
   else
      pDL = FindDisplayList(key);

   if ( pDL )
      pDL->Clear();
}

std::vector<std::shared_ptr<iDisplayObject>> DisplayMgr::GetSelectedObjects()
{
   return m_SelectedObjects;
}

std::vector<std::shared_ptr<const iDisplayObject>> DisplayMgr::GetSelectedObjects() const
{
   std::vector<std::shared_ptr<const iDisplayObject>> so;
   so.insert(so.end(), m_SelectedObjects.begin(), m_SelectedObjects.end());
   return so;
}

void DisplayMgr::SelectAll(bool bSelect)
{
   // Unselect all by clearing whatever is selected
   if ( !bSelect )
   {
      ClearSelectedObjects();
      return;
   }

   // Select all
   for (auto& dl : m_DisplayLists)
   {
      dl->SelectAll();
   }
}

void DisplayMgr::ClearSelectedObjects()
{
   std::for_each(m_SelectedObjects.begin(), m_SelectedObjects.end(), [](auto& disp_obj) {disp_obj->Select(false); });
   m_SelectedObjects.clear();
}

void DisplayMgr::ClearSelectedObjectsByList(IDType key,AccessType access,bool bInclusive)
{
   // Clears all selection objects that belong to the specified display list
   IDType listID;

   if ( access == AccessType::ByIndex )
   {
      auto list = GetDisplayList(key);
      listID = list->GetID();
   }
   else
   {
      listID = key;
   }

   std::erase_if(m_SelectedObjects, [listID, bInclusive](auto& disp_obj)
      {
         auto display_list = disp_obj->GetDisplayList();
         bool bRemove = bInclusive ? (display_list->GetID() == listID) : (display_list->GetID() != listID);
         if (bRemove)
            disp_obj->Select(false);

         return bRemove;
      });
}

void DisplayMgr::EnableLBtnMultiSelect(bool bEnable,DWORD dwKey)
{
   m_bLBtnMultiSelectEnabled = bEnable;

   if ( bEnable )
      EnableLBtnSelect(bEnable); // If multi select is enabled, then single select has to be enabled too

   ASSERT( dwKey & MK_CONTROL || dwKey & MK_SHIFT || dwKey & MK_ALT );
   m_dwLBtnMultiSelectKey = dwKey;
}

bool DisplayMgr::IsLBtnMultiSelectEnabled() const
{
   return m_bLBtnMultiSelectEnabled;
}

DWORD DisplayMgr::GetLBtnMultiSelectKey() const
{
   return m_dwLBtnMultiSelectKey;
}

void DisplayMgr::EnableLBtnSelectRect(bool bEnable)
{
   m_bLBtnRectSelectEnabled = bEnable;
}

bool DisplayMgr::IsLBtnSelectRectEnabled() const
{
   return m_bLBtnRectSelectEnabled;
}

void DisplayMgr::EnableLBtnSelect(bool bEnable)
{
   m_bLBtnSelectEnabled = bEnable;
}

bool DisplayMgr::IsLBtnSelectEnabled() const
{
   return m_bLBtnSelectEnabled;
}

void DisplayMgr::EnableRBtnSelect(bool bEnable)
{
   m_bRBtnSelectEnabled = bEnable;
}

bool DisplayMgr::IsRBtnSelectEnabled() const
{
   return m_bRBtnSelectEnabled;
}


void DisplayMgr::DrawDisplayObjects(CDC* pDC) const
{
   // draw in reverse order so the deepest display objects are drawn first
   // (Z-order is based on display list order. The top of the Z-order are the display lists
   // at the lowest indicies)
   std::for_each(m_DisplayLists.rbegin(), m_DisplayLists.rend(), [pDC](auto& dl) {dl->DrawDisplayObjects(pDC, TRUE); });// Skip selected display objects (they are drawn below)

   // Draw the selected display objects last so that they are always on top
   // Draw in reverse order to preserve relative Z-order of selected objects
   std::for_each(m_SelectedObjects.rbegin(), m_SelectedObjects.rend(), [pDC](auto& dl) {dl->Draw(pDC); });
}

void DisplayMgr::SetSelectionFillColor(COLORREF color)
{
   m_crSelectionFill;
}

void DisplayMgr::SetSelectionLineColor(COLORREF color)
{
   m_crSelectionLine;
}

COLORREF DisplayMgr::GetSelectionFillColor() const
{
   return m_crSelectionFill;
}

COLORREF DisplayMgr::GetSelectionLineColor() const
{
   return m_crSelectionLine;
}

#if defined(_DEBUG)
void DisplayMgr::DrawGravityWells(CDC* pDC) const
{
   // draw in reverse order so the deepest display objects are drawn first
   // (Z-order is based on display list order. The top of the Z-order are the display lists
   // at the lowest indicies)
   std::for_each(m_DisplayLists.rbegin(), m_DisplayLists.rend(), [pDC](auto& dl) {dl->DrawGravityWells(pDC); });

   // Draw the selected display objects last so that they are always on top
   // Draw in reverse order to preserve relative Z-order of selected objects
   std::for_each(m_SelectedObjects.rbegin(), m_SelectedObjects.rend(), [pDC](auto& dl) {dl->DrawGravityWell(pDC); });
}
#endif

bool DisplayMgr::OnLButtonDown(UINT nFlags,const POINT& point)
{
   bool handled = false;

   if ( m_pCurrTask )
   {
      m_pCurrTask->OnLButtonDown(nFlags,point);
      handled = true;
   }
   else
   {
      std::vector<std::shared_ptr<iDisplayObject>> dispObjs;

      BOOL bSelectionEnabled = FALSE;
      if ( m_bLBtnSelectEnabled )
      {
         // find the display objects at this click point
         auto doS = FindDisplayObjects(point);
         std::copy_if(doS.begin(), doS.end(), std::back_inserter(dispObjs), [](auto& dispObj) {return dispObj->IsSelected() and dispObj->RetainSelection(); });

         if (dispObjs.size() == 0)
         {
            auto disp_obj = FindNextSelectableDisplayObject(point);
            if (disp_obj)
            {
               dispObjs.push_back(disp_obj);
               bSelectionEnabled = TRUE;
            }
            else
            {
               dispObjs = FindDisplayObjects(point);
               bSelectionEnabled = FALSE;
            }
         }
      }

      BOOL bClearSelection = ( !m_bLBtnMultiSelectEnabled || (nFlags & m_dwLBtnMultiSelectKey) != m_dwLBtnMultiSelectKey );
      // Some display objects were found
      for(auto& disp_obj : dispObjs)
      {
         // Let the display object know it was clicked on
         handled = disp_obj->OnLButtonDown(nFlags,point);

         if ( bSelectionEnabled )
         {
            // Left mouse button selection is enabled... Select the object

            // If multi select is not enabled or if the the multiselect key isn't pressed, clear the current selection
            SelectObject(disp_obj,bClearSelection);

            if (disp_obj->IsSelected() )
            {
               handled = true; // event was handled with a selection

               if ( !m_bLBtnMultiSelectEnabled )
                  break; // multi-select is not enabled so we are done selecting
            }
         }

         // if click was not handled and not multi-select - then deselect current
         if (!handled && bClearSelection )
         {
            ClearSelectedObjects();
         }
      }

      if ( !handled )
      {
         // A display object wasn't found... (Click was in the whitespace or on a non-selectable display object)
         if ( bClearSelection )
            ClearSelectedObjects();

         // If selection by drawing a rectangle with the left mouse button is enabled
         // begin the task
         if ( m_bLBtnRectSelectEnabled )
         {
            auto task = m_pTaskFactory->CreateRectSelectTask(shared_from_this(), point);
            SetTask(task);
            handled = true;
         }
      }
   } // end else... no current task

   // use our event strategy if not handled
   if (!handled && m_EventSink)
   {
      handled = m_EventSink->OnLButtonDown(shared_from_this(), nFlags, point);
   }

   return handled;
}

bool DisplayMgr::OnLButtonUp(UINT nFlags,const POINT& point)
{
   bool handled = false;

   if ( m_pCurrTask )
   {
      m_pCurrTask->OnLButtonUp(nFlags,point);
      handled = true;
   }
   else
   {
      auto dispObjs = FindDisplayObjects(point);
      for(auto& dispObj : dispObjs)
      {
         if (dispObj->OnLButtonUp(nFlags,point))
         {
            handled = true;
            break;
         }
      }
   }

   // use our event strategy if not handled
   if (!handled && m_EventSink)
   {
      handled = m_EventSink->OnLButtonUp(shared_from_this(), nFlags, point);
   }

   return handled;
}

bool DisplayMgr::OnLButtonDblClk(UINT nFlags,const POINT& point)
{
   bool handled = false;

   if ( m_pCurrTask )
   {
      m_pCurrTask->OnLButtonDblClk(nFlags,point);
      handled = true;
   }
   else
   {
      auto dispObjs = FindDisplayObjects(point);
      for(auto& dispObj : dispObjs)
      {
         if (dispObj->OnLButtonDblClk(nFlags,point))
         {
            handled = true;
            break;  // break on first successful response
         }
      }

      // use our event strategy if not handled
      if (!handled && m_EventSink)
      {
         handled = m_EventSink->OnLButtonDblClk(shared_from_this(), nFlags, point);
      }
   }

   return handled;
}

bool DisplayMgr::OnRButtonDown(UINT nFlags,const POINT& point)
{
   bool handled = false;

   if ( m_pCurrTask )
   {
      // if there is a current task object, send this event along
      m_pCurrTask->OnRButtonDown(nFlags,point);
      handled = true;
   }
   else
   {
      // check if right-click occurred over a currently selected display object
      auto dispObjs = GetSelectedObjects();
      for(auto& dispObj : dispObjs)
      {
         if ( dispObj->HitTest(point) )
         {
            if ( dispObj->OnRButtonDown(nFlags,point) )
               handled = true;
         }
      }

      if ( !handled )
      {
         std::vector<std::shared_ptr<iDisplayObject>> dispObjs;

         BOOL bSelectionEnabled = FALSE;

         // find all the display objects at the click location
         if ( m_bRBtnSelectEnabled )
         {
            // r-button selection is enabled so we only want the selectable display objects
            // find the display objects at this point... if one of them is already selected,
            // then retain the selection
            auto doS = FindDisplayObjects(point);
            std::copy_if(doS.begin(), doS.end(), std::back_inserter(dispObjs), [](auto& dispObj) {return dispObj->IsSelected(); });

            if (dispObjs.size() == 0)
            {
               auto disp_obj = FindNextSelectableDisplayObject(point);
               if (disp_obj)
               {
                  dispObjs.push_back(disp_obj);
                  bSelectionEnabled = TRUE;
               }
               else
               {
                  // a selectable display object wasn't found... go to the full list of display objects
                  dispObjs = FindDisplayObjects(point);
                  bSelectionEnabled = FALSE;
               }
            }
         }
         else
         {
            // r-button selection is NOT enabled... get all the display objects
            dispObjs = FindDisplayObjects(point);
            bSelectionEnabled = FALSE;
         }

         if ( 0 < dispObjs.size() )
         {
            // Some display objects were found
            BOOL bClearSelection = !m_bRBtnSelectEnabled;
            for(auto& dispObj : dispObjs)
            {
               // Let the display object know it was clicked on
               if (dispObj->OnRButtonDown(nFlags,point))
               {

                  if ( bSelectionEnabled )
                  {
                     // Left mouse button selection is enabled... Select the object

                     // If multi select is not enabled or if the the multiselect key isn't pressed, clear the current selection
                     SelectObject(dispObj,bClearSelection);
                  }

                  handled = true;
                  break;
               }
            }

            // if click was not handled and not multi-select - then deselect current
            if (!handled && bClearSelection )
            {
               ClearSelectedObjects();
            }
         }
      }

   } // end else... no current task

   // use our event strategy if not handled
   if (!handled && m_EventSink)
   {
      handled = m_EventSink->OnRButtonDown(shared_from_this(), nFlags, point);
   }

   return handled;
}

bool DisplayMgr::OnRButtonUp(UINT nFlags,const POINT& point)
{
   bool handled = false;

   if ( m_pCurrTask )
   {
      m_pCurrTask->OnRButtonUp(nFlags,point);
      handled = true;
   }
   else
   {
      auto dispObjs = FindDisplayObjects(point);
      for(auto& dispObj : dispObjs)
      {
         if (dispObj->OnRButtonUp(nFlags,point))
         {
            handled = true;
            break;
         }
      }

      // use our event strategy if not handled
      if (!handled && m_EventSink)
      {
         handled = m_EventSink->OnRButtonUp(shared_from_this(), nFlags, point);
      }
   }

   return handled;
}

bool DisplayMgr::OnRButtonDblClk(UINT nFlags,const POINT& point)
{
   bool handled = false;

   if ( m_pCurrTask )
   {
      m_pCurrTask->OnRButtonDblClk(nFlags,point);
      handled = true;
   }
   else
   {
      auto dispObjs = FindDisplayObjects(point);
      for(auto& dispObj : dispObjs)
      {
         if(dispObj->OnRButtonDblClk(nFlags,point))
         {
            handled = true;
            break;
         }
      }

      // use our event strategy if not handled
      if (!handled && m_EventSink)
      {
         handled = m_EventSink->OnRButtonDblClk(shared_from_this(), nFlags, point);
      }
   }

   return handled;
}

bool DisplayMgr::OnMouseMove(UINT nFlags, const POINT& point)
{
   bool handled = false;

   if ( m_pCurrTask )
   {
      m_pCurrTask->OnMouseMove(nFlags,point);
      handled = true;
   }
   else
   {
      auto dispObjs = FindDisplayObjects(point);
      for(auto& dispObj : dispObjs)
      {
         if(dispObj->OnMouseMove(nFlags,point))
         {
            handled = true;
            break;
         }
      }

      // use our event strategy if not handled
      if (!handled && m_EventSink)
      {
         handled = m_EventSink->OnMouseMove(shared_from_this(), nFlags, point);
      }
   }

   return handled;
}

bool DisplayMgr::OnMouseWheel(UINT nFlags, short zDelta, const POINT& point)
{
   bool handled = false;

   if ( m_pCurrTask )
   {
      m_pCurrTask->OnMouseWheel(nFlags,zDelta,point);
      handled = true;
   }
   else
   {
      auto dispObjs = FindDisplayObjects(point);

      for(auto& dispObj : dispObjs)
      {
         if(dispObj->OnMouseWheel(nFlags,zDelta,point))
         {
            handled = true;
            break;
         }
      }

      // use our event strategy if not handled
      if (!handled && m_EventSink)
      {
         handled = m_EventSink->OnMouseWheel(shared_from_this(), nFlags, zDelta, point);
      }
   }

   return handled;
}

bool DisplayMgr::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
   bool handled = false;

   if (m_pCurrTask )
   {
      m_pCurrTask->OnKeyDown(nChar,nRepCnt,nFlags);
      handled = true;
   }
   else
   {
      for(auto& dispObj : m_SelectedObjects)
      {
         if (dispObj->OnKeyDown(nChar,nRepCnt,nFlags))
         {
            handled = true;
            break;
         }
      }

      // use our event strategy if not handled
      if (!handled && m_EventSink)
      {
         handled = m_EventSink->OnKeyDown(shared_from_this(), nChar, nRepCnt, nFlags);
      }
   }

   return handled;
}

bool DisplayMgr::OnContextMenu(CWnd* pWnd,const POINT& sp)
{
   POINT screenPoint = sp; // make a copy because we are going to change it
   bool handled = false;

   if (m_pCurrTask )
   {
      m_pCurrTask->OnContextMenu(pWnd,screenPoint);
      handled = true;
   }
   else
   {
      for(auto& dispObj : m_SelectedObjects)
      {
         CPoint pntClient = screenPoint;
         if ( screenPoint.x < 0 || screenPoint.y < 0 )
         {
            // the context menu key was pressed, get a point somewhere near the display object
            pntClient = CRect(dispObj->GetLogicalBoundingBox()).TopLeft();
            pntClient += CSize(1,1);

            if ( !dispObj->HitTest(pntClient) )
               pntClient = CRect(dispObj->GetLogicalBoundingBox()).CenterPoint();

            screenPoint = pntClient;
            pWnd->ClientToScreen(&screenPoint);
         }
         else
         {
            pWnd->ScreenToClient(&pntClient);
         }

         if (dispObj->HitTest(pntClient) && dispObj->OnContextMenu(pWnd,screenPoint))
         {
            handled = true;
            break;
         }
      }

      // use our event strategy if not handled
      if (!handled && m_EventSink)
      {
         handled = m_EventSink->OnContextMenu(shared_from_this(), pWnd, screenPoint);
      }
   }

   return handled;
}

BOOL DisplayMgr::OnNeedToolTipText(UINT id,NMHDR* pNMHDR,LRESULT* pResult)
{
   BOOL bRetVal = FALSE;
   if ( m_ToolTipObject /*&& id == 9999*/ )
   {
      INT maxTipWidth = m_ToolTipObject->GetMaxTipWidth();
      SendMessage(pNMHDR->hwndFrom,TTM_SETMAXTIPWIDTH,0,maxTipWidth);

      INT iDuration = m_ToolTipObject->GetTipDisplayTime();
      SendMessage(pNMHDR->hwndFrom,TTM_SETDELAYTIME,TTDT_AUTOPOP,iDuration);

      TOOLTIPTEXT* pTTT = (TOOLTIPTEXT*)pNMHDR;
      m_strToolTipText = m_ToolTipObject->GetToolTipText();
      if (!m_strToolTipText.empty())
      {
         pTTT->lpszText = (LPTSTR)m_strToolTipText.c_str();
         pTTT->hinst = nullptr;
         bRetVal = TRUE;

//#if defined _DEBUG
//         int id = m_ToolTipObject->GetID();
//         CComPtr<iDisplayList> disp_list;
//         m_ToolTipObject->GetDisplayList(&disp_list);
//         int list_id = disp_list->GetID();
//         WATCH(_T("Tool Tip from DO ") << id << _T("in DL ") << list_id << _T(" ") << m_strToolTipText);
//#endif // _DEBUG
      }
   }

   *pResult = 0;
   return bRetVal;
}

std::shared_ptr<iDisplayObject> FindToolTipDisplayObject(CPoint point,std::shared_ptr<iDisplayObject> pDO)
{
   if (pDO->GetToolTipText().empty() || pDO->GetToolTipText().length() == 0)
   {
      // if pDO doesn't have tooltip text, drill down to see if a sub display object
      // has it. The first display object to have tool tip text is the one
      auto compDO = std::dynamic_pointer_cast<CompositeDisplayObject>(pDO);
      if (compDO)
      {
         IndexType nDO = compDO->GetDisplayObjectCount();
         for (IndexType doIdx = 0; doIdx < nDO; doIdx++)
         {
            auto pSubDO = compDO->GetDisplayObject(doIdx, AccessType::ByIndex);

            if (pSubDO->HitTest(point))
            {
               auto ttDO = FindToolTipDisplayObject(point, pSubDO);
               if (ttDO)
               {
                  return ttDO;
               }
            }
         }
      }
   }
   return pDO;
}

INT_PTR DisplayMgr::OnToolHitTest(const POINT& point,TOOLINFO* pTI)
{
   auto dispObjs = FindDisplayObjects(point);
   for(auto& dispObj : dispObjs)
   {
      m_ToolTipObject = FindToolTipDisplayObject(point, dispObj);
      if (m_ToolTipObject)
      {
         CHECK(m_ToolTipObject->HitTest(point));

         pTI->cbSize = sizeof(TOOLINFO);
         pTI->hwnd = m_pView->GetSafeHwnd();
         pTI->uId = MAKELONG(point.x, point.y);
         pTI->lpszText = LPSTR_TEXTCALLBACK;
         pTI->rect = m_ToolTipObject->GetLogicalBoundingBox();
         pTI->uFlags |= TTF_NOTBUTTON | TTF_ALWAYSTIP;

         //#if defined _DEBUG
         //      int id = m_ToolTipObject->GetID();
         //      CComPtr<iDisplayList> disp_list;
         //      m_ToolTipObject->GetDisplayList(&disp_list);
         //      int list_id = disp_list->GetID();
         //      WATCH(_T("New Tool Tip Object: DO ") << id << _T(" in DL ") << list_id);
         //#endif // _DEBUG

         return pTI->uId;
      }
   }

   m_ToolTipObject = nullptr;
   return -1;
}

DROPEFFECT DisplayMgr::OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, const POINT& point)
{
   DROPEFFECT de = DROPEFFECT_NONE;

   if ( m_pCurrTask )
   {
      // Forward the event to the current task
      de = m_pCurrTask->OnDragEnter(pDataObject,dwKeyState,point);
   }
   else
   {
      // If there is a OnDragEnter event and there is not a current task
      // then something foreign just got dragged over the canvas. Start
      // a foreign drag drop task
      auto task = m_pTaskFactory->CreateForeignDragDropTask(shared_from_this(), point);
      SetTask(task);

      de = m_pCurrTask->OnDragEnter(pDataObject,dwKeyState,point);

   }

   return de;
}

void DisplayMgr::OnDragLeave()
{
   if ( m_pCurrTask )
      m_pCurrTask->OnDragLeave();
}

DROPEFFECT DisplayMgr::OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, const POINT& point)
{
   DROPEFFECT de = DROPEFFECT_NONE;
   if ( m_pCurrTask )
      de = m_pCurrTask->OnDragOver(pDataObject,dwKeyState,point);

   return de;
}

BOOL DisplayMgr::OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, const POINT& point)
{
   BOOL bDropped = FALSE;
   if ( m_pCurrTask )
      bDropped = m_pCurrTask->OnDrop(pDataObject,dropEffect,point);

   return bDropped;
}

DROPEFFECT DisplayMgr::OnDragScroll( DWORD dwKeyState, const POINT& point )
{
   DROPEFFECT de = DROPEFFECT_NONE;
   if ( m_pCurrTask )
      de = m_pCurrTask->OnDragScroll(dwKeyState,point);

   return de;
}

void DisplayMgr::CreateDragObjects(COleDataObject* pDataObject)
{
   PRECONDITION( m_DragList.size() == 0 );

   // first check to see if this from our tool box
   if (pDataObject->IsDataAvailable(Tool::ms_cfFormat) != FALSE)
   {
      // a tool was dragged over us
      auto tool = Tool::Create();
      auto draggable = std::dynamic_pointer_cast<iDraggable>(tool);

      auto source = DragDataSource::Create();
      source->SetDataObject(pDataObject);
      draggable->OnDrop(source); // Rebuild the tool object from the data object

      m_DragList.emplace_back(draggable);
   }
   else
   {
      // now see if it's a local display object
      for(auto& dispObj : m_SelectedObjects)
      {
         auto pDraggable = std::dynamic_pointer_cast<iDraggable>(dispObj);

         if ( pDraggable )
         {
            bool bCreated = false;
            // cycle through factories until we create something successfully
            for (const auto& factory : m_DisplayObjectFactories)
            {
               if (pDataObject->IsDataAvailable(pDraggable->Format()))
               {
                  auto pDragObject = factory->Create(pDraggable->Format(), pDataObject);
                  bCreated = true;
                  break;
               }
            }

            if (bCreated)
            {
               m_DragList.emplace_back(pDraggable);
            }
         }
      }
   }
}

void DisplayMgr::DrawDragObjects(const POINT& dragStart, const POINT& dragPoint)
{
   CDManipClientDC dc(m_pView);
   int rop2 = dc.SetROP2(R2_NOTXORPEN);

   auto map = GetCoordinateMap();

   for (auto& draggable : m_DragList)
   {
      draggable->DrawDragImage(&dc, map, dragStart, dragPoint);
   }

   dc.SetROP2(rop2);
}

void DisplayMgr::DestroyDragObjects()
{
   m_DragList.clear();
}

void DisplayMgr::RegisterDropSite(std::shared_ptr<iDropSite> pDropSite)
{
   m_pDropSite = pDropSite;
}

void DisplayMgr::UnregisterDropSite()
{
   m_pDropSite.reset();
}

std::shared_ptr<iDropSite> DisplayMgr::GetDropSite()
{
   return m_pDropSite;
}

void DisplayMgr::HighlightDropSite(BOOL bHighlight)
{
   if ( auto drop_site = m_pDropSite)
   {
      CDManipClientDC dc(m_pView);
      drop_site->Highlight(&dc,bHighlight);
   }
}

void DisplayMgr::OnDragFinished(DROPEFFECT de)
{
   for(auto& dispObj : m_SelectedObjects)
   {
      auto draggable = std::dynamic_pointer_cast<iDraggable>(dispObj);
      CHECK(draggable);
      
      if ( de & DROPEFFECT_MOVE )
         draggable->OnMoved();
      else if ( de & DROPEFFECT_COPY )
         draggable->OnCopied();
   }
}

std::shared_ptr<iDisplayObject> DisplayMgr::FindDisplayObject(IDType id,IDType listKey,AccessType access)
{
   std::shared_ptr<iDisplayList> pDL;
   if ( access == AccessType::ByIndex )
      pDL = GetDisplayList(listKey);
   else
      pDL = FindDisplayList(listKey);

   return pDL ? pDL->FindDisplayObject(id) : nullptr;
}

std::shared_ptr<const iDisplayObject> DisplayMgr::FindDisplayObject(IDType id, IDType listKey, AccessType access) const
{
   std::shared_ptr<const iDisplayList> pDL;
   if (access == AccessType::ByIndex)
      pDL = GetDisplayList(listKey);
   else
      pDL = FindDisplayList(listKey);

   return pDL ? pDL->FindDisplayObject(id) : nullptr;
}

std::vector<std::shared_ptr<iDisplayObject>> DisplayMgr::FindDisplayObjects(const POINT& point)
{
   std::vector<std::shared_ptr<iDisplayObject>> display_objects;
   for (auto& dl : m_DisplayLists)
   {
      auto dos = dl->FindDisplayObjects(point);
      display_objects.insert(display_objects.end(), dos.begin(), dos.end());
   }

   // remove duplicates
   std::sort(display_objects.begin(), display_objects.end());
   display_objects.erase(std::unique(display_objects.begin(), display_objects.end()), display_objects.end());
   return display_objects;
}

std::vector<std::shared_ptr<const iDisplayObject>> DisplayMgr::FindDisplayObjects(const POINT& point) const
{
   std::vector<std::shared_ptr<const iDisplayObject>> display_objects;
   for (auto& dl : m_DisplayLists)
   {
      auto dos = dl->FindDisplayObjects(point);
      display_objects.insert(display_objects.end(), dos.begin(), dos.end());
   }

   // remove duplicates
   std::sort(display_objects.begin(), display_objects.end());
   display_objects.erase(std::unique(display_objects.begin(), display_objects.end()), display_objects.end());
   return display_objects;
}

std::vector<std::shared_ptr<iDisplayObject>> DisplayMgr::FindDisplayObjects(const WBFL::Geometry::Point2d& point)
{
   std::vector<std::shared_ptr<iDisplayObject>> display_objects;
   for (auto& dl : m_DisplayLists)
   {
      auto dos = dl->FindDisplayObjects(point);
      display_objects.insert(display_objects.end(), dos.begin(), dos.end());
   }

   // remove duplicates
   std::sort(display_objects.begin(), display_objects.end());
   display_objects.erase(std::unique(display_objects.begin(), display_objects.end()), display_objects.end());
   return display_objects;
}

std::vector<std::shared_ptr<const iDisplayObject>> DisplayMgr::FindDisplayObjects(const WBFL::Geometry::Point2d& point) const
{
   std::vector<std::shared_ptr<const iDisplayObject>> display_objects;
   for (auto& dl : m_DisplayLists)
   {
      auto dos = dl->FindDisplayObjects(point);
      display_objects.insert(display_objects.end(), dos.begin(), dos.end());
   }

   // remove duplicates
   std::sort(display_objects.begin(), display_objects.end());
   display_objects.erase(std::unique(display_objects.begin(), display_objects.end()), display_objects.end());
   return display_objects;
}

std::vector<std::shared_ptr<iDisplayObject>> DisplayMgr::FindDisplayObjects(const RECT& rect)
{
   std::vector<std::shared_ptr<iDisplayObject>> display_objects;
   for(auto& dl : m_DisplayLists)
   {
      auto dos = dl->FindDisplayObjects(rect);
      display_objects.insert(display_objects.end(), dos.begin(), dos.end());
   }

   // remove duplicates
   std::sort(display_objects.begin(), display_objects.end());
   display_objects.erase(std::unique(display_objects.begin(), display_objects.end()), display_objects.end());
   return display_objects;
}

std::vector<std::shared_ptr<const iDisplayObject>> DisplayMgr::FindDisplayObjects(const RECT& rect) const
{
   std::vector<std::shared_ptr<const iDisplayObject>> display_objects;
   for (auto& dl : m_DisplayLists)
   {
      auto dos = dl->FindDisplayObjects(rect);
      display_objects.insert(display_objects.end(), dos.begin(), dos.end());
   }

   // remove duplicates
   std::sort(display_objects.begin(), display_objects.end());
   display_objects.erase(std::unique(display_objects.begin(), display_objects.end()), display_objects.end());
   return display_objects;
}

std::vector<std::shared_ptr<iDisplayObject>> DisplayMgr::FindDisplayObjects(const WBFL::Geometry::Rect2d& rect)
{
   std::vector<std::shared_ptr<iDisplayObject>> display_objects;
   for (auto& dl : m_DisplayLists)
   {
      auto dos = dl->FindDisplayObjects(rect);
      display_objects.insert(display_objects.end(), dos.begin(), dos.end());
   }

   // remove duplicates
   std::sort(display_objects.begin(), display_objects.end());
   display_objects.erase(std::unique(display_objects.begin(), display_objects.end()), display_objects.end());
   return display_objects;
}

std::vector<std::shared_ptr<const iDisplayObject>> DisplayMgr::FindDisplayObjects(const WBFL::Geometry::Rect2d& rect) const
{
   std::vector<std::shared_ptr<const iDisplayObject>> display_objects;
   for (auto& dl : m_DisplayLists)
   {
      auto dos = dl->FindDisplayObjects(rect);
      display_objects.insert(display_objects.end(), dos.begin(), dos.end());
   }

   // remove duplicates
   std::sort(display_objects.begin(), display_objects.end());
   display_objects.erase(std::unique(display_objects.begin(), display_objects.end()), display_objects.end());
   return display_objects;
}

IndexType DisplayMgr::GetDisplayObjectCount() const
{
   IndexType count = 0;
   std::for_each(m_DisplayLists.begin(), m_DisplayLists.end(), [&count](auto& dl) {count += dl->GetDisplayObjectCount(); });
   return count;
}

IndexType DisplayMgr::GetDisplayObjectFactoryCount() const
{
   return m_DisplayObjectFactories.size();
}

void DisplayMgr::AddDisplayObjectFactory(std::shared_ptr<iDisplayObjectFactory> factory)
{
   m_DisplayObjectFactories.emplace_back(factory);
}

std::shared_ptr<iDisplayObjectFactory> DisplayMgr::GetDisplayObjectFactory(IndexType idx)
{
   PRECONDITION(0 <= idx && idx < m_DisplayObjectFactories.size());
   return m_DisplayObjectFactories[idx];
}

std::shared_ptr<const iDisplayObjectFactory> DisplayMgr::GetDisplayObjectFactory(IndexType idx) const
{
   PRECONDITION(0 <= idx && idx < m_DisplayObjectFactories.size());
   return m_DisplayObjectFactories[idx];
}

void DisplayMgr::SetTaskFactory(std::shared_ptr<TaskFactory> pFactory)
{
   m_pTaskFactory = pFactory;
}

std::shared_ptr<TaskFactory> DisplayMgr::GetTaskFactory()
{
   return m_pTaskFactory;
}

void DisplayMgr::SetTask(std::shared_ptr<iTask> pTask)
{
   m_pCurrTask = pTask;

   if ( m_pCurrTask )
   {
      m_pCurrTask->Start();
   }
}

WBFL::Geometry::Rect2d DisplayMgr::GetBoundingBox(bool boundOrigin) const
{
   WBFL::Geometry::Rect2d rect;

   // Begin with an inverted world
   Float64 rl =  DBL_MAX;
   Float64 rr = -DBL_MAX;
   Float64 rt = -DBL_MAX;
   Float64 rb =  DBL_MAX;

   // Iterate through all of the display objects to determine the physical extents
   bool bHasDO = false;
   for ( auto& pDL : m_DisplayLists )
   {
      IndexType nDisplayObjects = pDL->GetDisplayObjectCount();
      for ( IndexType i = 0; i < nDisplayObjects; i++ )
      {
         bHasDO = true;
         auto pDO = pDL->GetDisplayObject(i);

         if ( pDO->IsVisible() )
         {
            auto box = pDO->GetBoundingBox();

            auto lBox = box.Left();
            auto rBox = box.Right();
            auto tBox = box.Top();
            auto bBox = box.Bottom();

            rl = Min(rl,lBox);
            rr = Max(rr,rBox);
            rt = Max(rt,tBox);
            rb = Min(rb,bBox);
         }
      }
   }

   if (bHasDO)
   {
      rect.Left() = rl;
      rect.Right() = rr;
      rect.Top() = rt;
      rect.Bottom() = rb;
   }

   if ( boundOrigin )
   {
      // If BoundZero is enabled, force the bottom left corner of the
      // world rect to (0,0) if it does not already contain it.
      rect.BoundPoint(0,0);
   }

   return rect;
}

std::vector<std::shared_ptr<iDisplayObject> > DisplayMgr::FindAllDisplayObjects(const POINT& point)
{
   std::vector<std::shared_ptr<iDisplayObject> > dispObjects;
   for(auto& dl : m_DisplayLists)
   {
      IndexType doCount = dl->GetDisplayObjectCount();
      for ( IndexType i = 0; i < doCount; i++ )
      {
         auto dispObj = dl->GetDisplayObject(i);
         if ( dispObj->HitTest(point) )
            dispObjects.push_back(dispObj);
      }
   }

   return dispObjects;
}

std::vector<std::shared_ptr<iDisplayObject>> DisplayMgr::FindAllSelectableDisplayObjects(const POINT& point)
{
   std::vector<std::shared_ptr<iDisplayObject>> dispObjects;

   for(auto& dl : m_DisplayLists)
   {
      IndexType doCount = dl->GetDisplayObjectCount();
      for ( IndexType i = 0; i < doCount; i++ )
      {
         auto dispObj = dl->GetDisplayObject(i);
         if ( dispObj->GetSelectionType() == SelectionType::All && dispObj->HitTest(point) )
            dispObjects.push_back(dispObj);
      }
   }

   return dispObjects;
}

std::shared_ptr<iDisplayObject> DisplayMgr::FindNextSelectableDisplayObject(const POINT& point)
{
   auto dispObjects = FindAllSelectableDisplayObjects(point);

   if ( dispObjects.size() == 0 )
   {
      // No display objects were found
      return nullptr;
   }

   // Traverse the vector in reverse order, looking for the first display object that
   // is selected. Once found, back up one position (move forward in the display list).
   // This is the next display object to be selected. If none are selected, select the first one
   auto iter = dispObjects.rbegin();
   auto end = dispObjects.rend();
   for ( ; iter != end; iter++ )
   {
      auto dispObj(*iter);
      if ( iter == dispObjects.rbegin() && dispObj->IsSelected() )
      {
         // If the first display object is selected (which would be the last display object
         // in the list), the don't iterate any further because the display object we want to
         // return is the first one. (The same as if none are selected, see below)
         break;
      }
      else if ( dispObj->IsSelected() )
      {
         iter--; // Back up one
         return *iter;
      }
   }

   // If we got this far, nothing is selected, or the last display object in the list is selected
   // In either event, we want the first display object
   return *(dispObjects.begin());
}

void DisplayMgr::RegisterEventSink(std::shared_ptr<iDisplayMgrEvents> pEventSink)
{
   UnregisterEventSink();
   m_EventSink = pEventSink;
}

void DisplayMgr::UnregisterEventSink()
{
   m_EventSink.reset();
}

std::shared_ptr<iDisplayMgrEvents> DisplayMgr::GetEventSink()
{
   return m_EventSink;
}

// iDisplayListEvents
void DisplayMgr::OnDisplayObjectAdded(IDType listID, std::shared_ptr<iDisplayObject> pDO)
{
   CRect box = pDO->GetLogicalBoundingBox();
   if (m_pView->GetSafeHwnd()) m_pView->InvalidateRect(box);

#if defined _DEBUG
   auto& record = CircularRefDebugger::GetRecord((void*)(pDO.get()));
   record.view_address = (Uint64)m_pView;
#endif
}

void DisplayMgr::OnDisplayObjectRemoved(IDType listID, IDType doID)
{
   if(m_pView->GetSafeHwnd()) m_pView->Invalidate();
}

void DisplayMgr::OnDisplayObjectsCleared(IDType listID)
{
   if (m_pView->GetSafeHwnd()) m_pView->Invalidate();
}
