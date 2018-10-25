///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2014  Washington State Department of Transportation
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

// DisplayMgrImpl.cpp: implementation of the CDisplayMgrImpl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <WBFLDManip.h>
#include <DManip\DManip.h>
#include "DisplayMgrImpl.h"

#include "DisplayListImpl.h"
#include "DisplayObjectFactoryImpl.h"
#include "DragDataImpl.h"
#include <MathEx.h>
#include <algorithm>
#include <float.h>
#include "ToolImpl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif 

// Predicate object for removing displays from the selection list
// if they belog to a certain list
class RemoveByListID
{
public:
   RemoveByListID(IDType listID,BOOL bInclusive) : m_ListID(listID),m_bInclusive(bInclusive) {}
   bool operator()(DisplayObjectItem dispObj)
   {
      CComPtr<iDisplayList> list;
      dispObj.m_T->GetDisplayList(&list);
      BOOL bRemove = m_bInclusive ? ( list->GetID() == m_ListID ) : ( list->GetID() != m_ListID );
      if ( bRemove )
      {
         dispObj.m_T->Select(FALSE);
         return true;
      }

      return false;
   }

private:
   IDType m_ListID;
   BOOL m_bInclusive;
};

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDisplayMgrImpl::CDisplayMgrImpl()
{
   m_crSelectionLine = RGB(255,0,0);
   m_crSelectionFill = RGB(255,50,50);
}

CDisplayMgrImpl::~CDisplayMgrImpl()
{
}

HRESULT CDisplayMgrImpl::FinalConstruct()
{
   m_pView = 0;

   m_bLBtnSelectEnabled = FALSE;
   m_bRBtnSelectEnabled = FALSE;
   m_bLBtnMultiSelectEnabled = FALSE;
   m_dwLBtnMultiSelectKey = MK_CONTROL;
   m_bLBtnRectSelectEnabled = FALSE;

   m_pDropSite = 0;

   // NOTE: Initialization of mapping and scrolling is handled
   //       in SetView.
   return S_OK;
}

void CDisplayMgrImpl::FinalRelease()
{
   ClearDisplayLists();
   m_DropTarget.Revoke();
}

STDMETHODIMP_(void) CDisplayMgrImpl::PrepareDragData(iDragDataSink* pSink)
{
   DisplayObjectContainer::iterator iter;
   for ( iter = m_SelectedObjects.begin(); iter != m_SelectedObjects.end(); iter++ )
   {
      CComPtr<iDisplayObject> pDO = *iter;

      CComQIPtr<iDraggable,&IID_iDraggable> pDraggable(pDO);
      ASSERT(pDraggable != 0);
      pDraggable->PrepareDrag(pSink);
   }
}

STDMETHODIMP_(void) CDisplayMgrImpl::SetView(CDisplayView* pView)
{
   if ( m_pView )
      m_DropTarget.Revoke();

   m_pView = pView;

   // If this VERIFY fails, you most likely initilized COM with
   // CoInitialize instead of OleInitialize. You must use
   // OleInitialize for drag and drop to work
   VERIFY( m_DropTarget.Register(m_pView) );
}

STDMETHODIMP_(CDisplayView*) CDisplayMgrImpl::GetView()
{
   return m_pView;
}

STDMETHODIMP_(void) CDisplayMgrImpl::GetCoordinateMap(iCoordinateMap** map)
{
   m_pView->GetCoordinateMap(map);
}

STDMETHODIMP_(void) CDisplayMgrImpl::AddDisplayList(iDisplayList* pDL)
{
   IDType id = pDL->GetID();
   CComPtr<iDisplayList> pDLExists;
   FindDisplayList(id,&pDLExists);
   if ( pDLExists )
      return; // A display list with this id already exists

   m_DisplayLists.push_back(DisplayListItem(pDL));
   pDL->SetDisplayMgr(this);

   pDL->RegisterEventSink(this);
   InternalRelease();
}

STDMETHODIMP_(void) CDisplayMgrImpl::GetDisplayList(CollectionIndexType idx,iDisplayList** list)
{
   if ( idx < 0 || m_DisplayLists.size() <= idx )
      return; // Index is out of range

   CComPtr<iDisplayList> pDL = m_DisplayLists[idx];
   (*list) = pDL;
   (*list)->AddRef();
}

STDMETHODIMP_(void) CDisplayMgrImpl::FindDisplayList(IDType id,iDisplayList** list)
{
   (*list) = 0;
   DisplayListContainer::iterator iter;
   for ( iter = m_DisplayLists.begin(); iter != m_DisplayLists.end(); iter++ )
   {
      CComPtr<iDisplayList> pDL = *iter;
      if ( pDL->GetID() == id )
      {
         (*list) = pDL;
         (*list)->AddRef();
         return;
      }
   }

   return;
}

STDMETHODIMP_(CollectionIndexType) CDisplayMgrImpl::GetDisplayListCount()
{
   return m_DisplayLists.size();
}

STDMETHODIMP_(void) CDisplayMgrImpl::RemoveDisplayList(IDType key,AccessType access)
{
   CComPtr<iDisplayList> pDL;

   if ( access == atByIndex )
   {
      // Remove by index
      IndexType index = (IndexType)key;
      if ( index < 0 || m_DisplayLists.size() <= index )
         return; // index out of bounds

      DisplayListContainer::iterator iter = m_DisplayLists.begin() + index;

      pDL = *iter;

      m_DisplayLists.erase(iter);
   }
   else
   {
      // Remove by id
      DisplayListContainer::iterator iter;
      for ( iter = m_DisplayLists.begin(); iter != m_DisplayLists.end(); iter++ )
      {
         CComPtr<iDisplayList> pDL = *iter;
         if ( pDL->GetID() == key )
         {
            m_DisplayLists.erase(iter);
            break;;
         }
      }
   }

   InternalAddRef();
   pDL->UnregisterEventSink();
}

STDMETHODIMP_(void) CDisplayMgrImpl::ClearDisplayLists()
{
   DisplayListContainer::iterator iter;
   for ( iter = m_DisplayLists.begin(); iter != m_DisplayLists.end(); iter++ )
   {
      CComPtr<iDisplayList> pDL = *iter;
      pDL->Clear();
      InternalAddRef();
      pDL->UnregisterEventSink();
   }

   m_DisplayLists.clear();
}

STDMETHODIMP_(void) CDisplayMgrImpl::AddDisplayObject(iDisplayObject* pDO,IDType key,AccessType access)
{
   CComPtr<iDisplayList> pDL;
   if ( access == atByIndex )
      GetDisplayList(key,&pDL);
   else
      FindDisplayList(key,&pDL);

   if ( pDL == 0 )
      return; // No display list

   pDL->AddDisplayObject(pDO);
}

STDMETHODIMP_(void) CDisplayMgrImpl::SelectObject(iDisplayObject* pDO,BOOL bClearSelection)
{
   ASSERT(pDO);

   if ( bClearSelection )
      ClearSelectedObjects();

   // Only call Select if the display object is not currently selected
   // otherwise there will be recursion until the stack pops.
   if ( !pDO->IsSelected() && pDO->GetSelectionType() != stNone )
   {
      pDO->Select(TRUE);
      m_SelectedObjects.push_back(DisplayObjectItem(pDO));

      CRect bbox = pDO->GetBoundingBox();
      InvalidateRect(bbox);
   }
}

STDMETHODIMP_(void) CDisplayMgrImpl::SelectObjects(CRect rect)
{
   DisplayObjectContainer dispObjs;
   FindDisplayObjects(rect,&dispObjs);

   // If Multi-select isn't enabled and if more than one object was
   // found, don't do the selection.
   if ( !m_bLBtnMultiSelectEnabled && dispObjs.size() > 1 )
      return;

   //ClearSelectedObjects();
   DisplayObjectContainer::iterator iter;
   for ( iter = dispObjs.begin(); iter != dispObjs.end(); iter++ )
   {
      CComPtr<iDisplayObject> pDO = *iter;
      SelectObject(pDO,FALSE);  // Don't clear current selection
   }
}

STDMETHODIMP_(void) CDisplayMgrImpl::RemoveDisplayObject(IDType doKey,AccessType doAccess,IDType dlKey,AccessType dlAccess)
{
   CComPtr<iDisplayList> pDL;

   if ( dlAccess == atByIndex )
      GetDisplayList(dlKey,&pDL);
   else
      FindDisplayList(dlKey,&pDL);

   if ( pDL == 0 )
      return; // display list not found

   pDL->RemoveDisplayObject(doKey,doAccess);
}

STDMETHODIMP_(void) CDisplayMgrImpl::ClearDisplayObjects()
{
   m_SelectedObjects.clear();

   // Clears all display objects from all display list
   DisplayListContainer::iterator iter;
   for ( iter = m_DisplayLists.begin(); iter != m_DisplayLists.end(); iter++ )
   {
      CComPtr<iDisplayList> pDL = *iter;
      pDL->Clear();
   }
}

STDMETHODIMP_(void) CDisplayMgrImpl::ClearDisplayObjects(IDType key,AccessType access)
{
   // Clear the display objects from the specified display list;
   CComPtr<iDisplayList> pDL;
   if ( access == atByIndex )
      GetDisplayList(key,&pDL);
   else
      FindDisplayList(key,&pDL);

   if ( pDL == 0 )
      return; // Display list not found

   pDL->Clear();
}

STDMETHODIMP_(void) CDisplayMgrImpl::GetSelectedObjects(DisplayObjectContainer* selObjs)
{
   *selObjs = m_SelectedObjects;
}

STDMETHODIMP_(void) CDisplayMgrImpl::SelectAll(BOOL bSelect)
{
   // Unselect all by clearing whatever is selected
   if ( !bSelect )
   {
      ClearSelectedObjects();
      return;
   }

   // Select all
   DisplayListContainer::iterator iter;
   for ( iter = m_DisplayLists.begin(); iter != m_DisplayLists.end(); iter++ )
   {
      CComPtr<iDisplayList> pDL = *iter;
      CollectionIndexType nDO = pDL->GetDisplayObjectCount();
      for ( CollectionIndexType i = 0; i < nDO; i++ )
      {
         CComPtr<iDisplayObject> pDO;
         pDL->GetDisplayObject(i,&pDO);
         this->SelectObject(pDO,FALSE);
      }
   }
}

STDMETHODIMP_(void) CDisplayMgrImpl::ClearSelectedObjects()
{
   DisplayObjectContainer::iterator iter;
   for ( iter = m_SelectedObjects.begin(); iter != m_SelectedObjects.end(); iter++ )
   {
      CComPtr<iDisplayObject> pDO = *iter;
      pDO->Select(FALSE);
   }

   m_SelectedObjects.clear();
}

STDMETHODIMP_(void) CDisplayMgrImpl::ClearSelectedObjectsByList(IDType key,AccessType access,BOOL bInclusive)
{
   // Clears all selection objects that belong to the specified display list
   IDType listID;

   if ( access == atByIndex )
   {
      CComPtr<iDisplayList> list;
      GetDisplayList(key,&list);
      listID = list->GetID();
   }
   else
   {
      listID = key;
   }

   std::remove_if(m_SelectedObjects.begin(),m_SelectedObjects.end(),RemoveByListID(listID,bInclusive));
}

STDMETHODIMP_(void) CDisplayMgrImpl::EnableLBtnMultiSelect(BOOL bEnable,DWORD dwKey)
{
   m_bLBtnMultiSelectEnabled = bEnable;

   if ( bEnable )
      EnableLBtnSelect(bEnable); // If multi select is enabled, then single select has to be enabled too

   ASSERT( dwKey & MK_CONTROL || dwKey & MK_SHIFT || dwKey & MK_ALT );
   m_dwLBtnMultiSelectKey = dwKey;
}

STDMETHODIMP_(BOOL) CDisplayMgrImpl::IsLBtnMultiSelectEnabled()
{
   return m_bLBtnMultiSelectEnabled;
}

STDMETHODIMP_(DWORD) CDisplayMgrImpl::GetLBtnMultiSelectKey()
{
   return m_dwLBtnMultiSelectKey;
}

STDMETHODIMP_(void) CDisplayMgrImpl::EnableLBtnSelectRect(BOOL bEnable)
{
   m_bLBtnRectSelectEnabled = bEnable;
}

STDMETHODIMP_(BOOL) CDisplayMgrImpl::IsLBtnSelectRectEnabled()
{
   return m_bLBtnRectSelectEnabled;
}

STDMETHODIMP_(void) CDisplayMgrImpl::EnableLBtnSelect(BOOL bEnable)
{
   m_bLBtnSelectEnabled = bEnable;
}

STDMETHODIMP_(BOOL) CDisplayMgrImpl::IsLBtnSelectEnabled()
{
   return m_bLBtnSelectEnabled;
}

STDMETHODIMP_(void) CDisplayMgrImpl::EnableRBtnSelect(BOOL bEnable)
{
   m_bRBtnSelectEnabled = bEnable;
}

STDMETHODIMP_(BOOL) CDisplayMgrImpl::IsRBtnSelectEnabled()
{
   return m_bRBtnSelectEnabled;
}


STDMETHODIMP_(void) CDisplayMgrImpl::DrawDisplayObjects(CDC* pDC)
{
   // draw in reverse order so the deepest display objects are drawn first
   // (Z-order is based on display list order. The top of the Z-order are the display lists
   // at the lowest indicies)
   DisplayListContainer::reverse_iterator iter;
   for ( iter = m_DisplayLists.rbegin(); iter != m_DisplayLists.rend(); iter++ )
   {
      CComPtr<iDisplayList> pDL = *iter;
      pDL->DrawDisplayObjects(pDC,TRUE); // Skip selected display objects (they are drawn below)
   }

   // Draw the selected display objects last so that they are always on top
   // Draw in reverse order to perserve relative Z-order of selected objects
   DisplayObjectContainer::reverse_iterator selIter;
   for ( selIter = m_SelectedObjects.rbegin(); selIter != m_SelectedObjects.rend(); selIter++ )
   {
      CComPtr<iDisplayObject> pDO = *selIter;
      pDO->Draw(pDC);
   }
}

STDMETHODIMP_(void) CDisplayMgrImpl::InvalidateRect(LPCRECT lpRect)
{
   m_pView->InvalidateRect(lpRect);
}

STDMETHODIMP_(void) CDisplayMgrImpl::InvalidateRgn(CRgn* pRgn)
{
   m_pView->InvalidateRgn(pRgn);
}

STDMETHODIMP_(void) CDisplayMgrImpl::SetSelectionFillColor(COLORREF color)
{
   m_crSelectionFill;
}

STDMETHODIMP_(void) CDisplayMgrImpl::SetSelectionLineColor(COLORREF color)
{
   m_crSelectionLine;
}

STDMETHODIMP_(COLORREF) CDisplayMgrImpl::GetSelectionFillColor()
{
   return m_crSelectionFill;
}

STDMETHODIMP_(COLORREF) CDisplayMgrImpl::GetSelectionLineColor()
{
   return m_crSelectionLine;
}

#if defined(_DEBUG)
STDMETHODIMP_(void) CDisplayMgrImpl::DrawGravityWells(CDC* pDC)
{
   // draw in reverse order so the deepest display objects are drawn first
   // (Z-order is based on display list order. The top of the Z-order are the display lists
   // at the lowest indicies)
   DisplayListContainer::reverse_iterator iter;
   for ( iter = m_DisplayLists.rbegin(); iter != m_DisplayLists.rend(); iter++ )
   {
      CComPtr<iDisplayList> pDL = *iter;
      pDL->DrawGravityWells(pDC);
   }

   // Draw the selected display objects last so that they are always on top
   // Draw in reverse order to perserve relative Z-order of selected objects
   DisplayObjectContainer::reverse_iterator selIter;
   for ( selIter = m_SelectedObjects.rbegin(); selIter != m_SelectedObjects.rend(); selIter++ )
   {
      CComPtr<iDisplayObject> pDO = *selIter;
      pDO->DrawGravityWell(pDC);
   }
}
#endif

STDMETHODIMP_(bool) CDisplayMgrImpl::OnLButtonDown(UINT nFlags,CPoint point)
{
   bool handled = false;

   if ( m_pCurrTask )
   {
      m_pCurrTask->OnLButtonDown(nFlags,point);
      handled = true;
   }
   else
   {
      CComPtr<iDisplayObject> pDO;
      DisplayObjectContainer dispObjs;

      BOOL bSelectionEnabled = FALSE;
      if ( m_bLBtnSelectEnabled )
      {
         FindNextSelectableDisplayObject(point,&pDO);
         if ( pDO )
         {
            dispObjs.push_back(pDO);
            bSelectionEnabled = TRUE;
         }
      }
      else
      {
         FindDisplayObjects(point,&dispObjs);
         bSelectionEnabled = FALSE;
      }

      if ( m_bLBtnSelectEnabled && pDO == NULL )
      {
         FindDisplayObjects(point,&dispObjs);
         bSelectionEnabled = FALSE;
      }

      BOOL bClearSelection = ( !m_bLBtnMultiSelectEnabled || (nFlags & m_dwLBtnMultiSelectKey) != m_dwLBtnMultiSelectKey );
      if ( 0 < dispObjs.size() )
      {
         // Some display objects were found
         DisplayObjectContainer::iterator iter;
         for ( iter = dispObjs.begin(); iter != dispObjs.end(); iter++ )
         {
            pDO.Release();
            pDO = *iter;
            
            // Let the display object know it was clicked on
            handled = pDO->OnLButtonDown(nFlags,point);

            if ( bSelectionEnabled )
            {
               // Left mouse button selection is enabled... Select the object

               // If multi select is not enabled or if the the multiselect key isn't pressed, clear the current selection
               SelectObject(pDO,bClearSelection);

               if ( pDO->IsSelected() )
               {
                  handled = true; // event was handled with a selection

                  if ( !m_bLBtnMultiSelectEnabled )
                     break; // multi-select is not enabled so we are done selecting
               }
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
            CComPtr<iTask> task;
            m_pTaskFactory->CreateRectSelectTask(this,point,&task);
            SetTask(task);
            handled = true;
         }
      }
   } // end else... no current task

   // use our event strategy if not handled
   if (!handled && m_EventSink)
   {
      handled = m_EventSink->OnLButtonDown(this, nFlags, point);
   }

   return handled;
}

STDMETHODIMP_(bool) CDisplayMgrImpl::OnLButtonUp(UINT nFlags,CPoint point)
{
   bool handled = false;

   if ( m_pCurrTask )
   {
      m_pCurrTask->OnLButtonUp(nFlags,point);
      handled = true;
   }
   else
   {
      DisplayObjectContainer dispObjs;
      FindDisplayObjects(point,&dispObjs);

      DisplayObjectContainer::iterator iter;
      for ( iter = dispObjs.begin(); iter != dispObjs.end(); iter++ )
      {
         CComPtr<iDisplayObject> pDO = *iter;
         if (pDO->OnLButtonUp(nFlags,point))
         {
            handled = true;
            break;
         }
      }
   }

   // use our event strategy if not handled
   if (!handled && m_EventSink)
   {
      handled = m_EventSink->OnLButtonUp(this, nFlags, point);
   }

   return handled;
}

STDMETHODIMP_(bool) CDisplayMgrImpl::OnLButtonDblClk(UINT nFlags,CPoint point)
{
   bool handled = false;

   if ( m_pCurrTask )
   {
      m_pCurrTask->OnLButtonDblClk(nFlags,point);
      handled = true;
   }
   else
   {
      DisplayObjectContainer dispObjs;
      FindDisplayObjects(point,&dispObjs);

      DisplayObjectContainer::iterator iter;
      for ( iter = dispObjs.begin(); iter != dispObjs.end(); iter++ )
      {
         CComPtr<iDisplayObject> pDO = *iter;
         if (pDO->OnLButtonDblClk(nFlags,point))
         {
            handled = true;
            break;  // break on first successful response
         }
      }

      // use our event strategy if not handled
      if (!handled && m_EventSink)
      {
         handled = m_EventSink->OnLButtonDblClk(this, nFlags, point);
      }
   }

   return handled;
}

STDMETHODIMP_(bool) CDisplayMgrImpl::OnRButtonDown(UINT nFlags,CPoint point)
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
      // check if right-click occured over a currently selected display object
      DisplayObjectContainer curSel;
      GetSelectedObjects(&curSel);
      DisplayObjectContainer::iterator iter;
      for ( iter = curSel.begin(); iter != curSel.end(); iter++ )
      {
         CComPtr<iDisplayObject> pSelDO;
         pSelDO = *iter;

         if ( pSelDO->HitTest(point) )
         {
            if ( pSelDO->OnRButtonDown(nFlags,point) )
               handled = true;
         }
      }

      if ( !handled )
      {
         CComPtr<iDisplayObject> pDO;
         DisplayObjectContainer dispObjs;

         BOOL bSelectionEnabled = FALSE;

         // find all the display objects at the click location
         if ( m_bRBtnSelectEnabled )
         {
            // r-button selection is enabled so we only want the selectable display objects
            FindNextSelectableDisplayObject(point,&pDO);
            if ( pDO )
            {
               dispObjs.push_back(pDO);
               bSelectionEnabled = TRUE;
            }
            else
            {
               // a selectable display object wasn't found... go to the full list of display objects
               FindDisplayObjects(point,&dispObjs);
               bSelectionEnabled = FALSE;
            }
         }
         else
         {
            // r-button selection is NOT enabled... get all the display objects
            FindDisplayObjects(point,&dispObjs);
            bSelectionEnabled = FALSE;
         }

         if ( 0 < dispObjs.size() )
         {
            // Some display objects were found
            BOOL bClearSelection = !m_bRBtnSelectEnabled;
            DisplayObjectContainer::iterator iter;
            for ( iter = dispObjs.begin(); iter != dispObjs.end(); iter++ )
            {
               pDO.Release();
               pDO = *iter;
            
               // Let the display object know it was clicked on
               if (pDO->OnRButtonDown(nFlags,point))
               {

                  if ( bSelectionEnabled )
                  {
                     // Left mouse button selection is enabled... Select the object

                     // If multi select is not enabled or if the the multiselect key isn't pressed, clear the current selection
                     SelectObject(pDO,bClearSelection);
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
      handled = m_EventSink->OnRButtonDown(this, nFlags, point);
   }

   return handled;
}

STDMETHODIMP_(bool) CDisplayMgrImpl::OnRButtonUp(UINT nFlags,CPoint point)
{
   bool handled = false;

   if ( m_pCurrTask )
   {
      m_pCurrTask->OnRButtonUp(nFlags,point);
      handled = true;
   }
   else
   {
      DisplayObjectContainer dispObjs;
      FindDisplayObjects(point,&dispObjs);

      DisplayObjectContainer::iterator iter;
      for ( iter = dispObjs.begin(); iter != dispObjs.end(); iter++ )
      {
         CComPtr<iDisplayObject> pDO = *iter;
         if (pDO->OnRButtonUp(nFlags,point))
         {
            handled = true;
            break;
         }
      }

      // use our event strategy if not handled
      if (!handled && m_EventSink)
      {
         handled = m_EventSink->OnRButtonUp(this, nFlags, point);
      }
   }

   return handled;
}

STDMETHODIMP_(bool) CDisplayMgrImpl::OnRButtonDblClk(UINT nFlags,CPoint point)
{
   bool handled = false;

   if ( m_pCurrTask )
   {
      m_pCurrTask->OnRButtonDblClk(nFlags,point);
      handled = true;
   }
   else
   {
      DisplayObjectContainer dispObjs;
      FindDisplayObjects(point,&dispObjs);

      DisplayObjectContainer::iterator iter;
      for ( iter = dispObjs.begin(); iter != dispObjs.end(); iter++ )
      {
         CComPtr<iDisplayObject> pDO = *iter;
         if(pDO->OnRButtonDblClk(nFlags,point))
         {
            handled = true;
            break;
         }
      }

      // use our event strategy if not handled
      if (!handled && m_EventSink)
      {
         handled = m_EventSink->OnRButtonDblClk(this, nFlags, point);
      }
   }

   return handled;
}

STDMETHODIMP_(bool) CDisplayMgrImpl::OnMouseMove(UINT nFlags, CPoint point)
{
   bool handled = false;

   if ( m_pCurrTask )
   {
      m_pCurrTask->OnMouseMove(nFlags,point);
      handled = true;
   }
   else
   {
      DisplayObjectContainer dispObjs;
      FindDisplayObjects(point,&dispObjs);

      DisplayObjectContainer::iterator iter;
      for ( iter = dispObjs.begin(); iter != dispObjs.end(); iter++ )
      {
         CComPtr<iDisplayObject> pDO = *iter;
         if(pDO->OnMouseMove(nFlags,point))
         {
            handled = true;
            break;
         }
      }

      // use our event strategy if not handled
      if (!handled && m_EventSink)
      {
         handled = m_EventSink->OnMouseMove(this, nFlags, point);
      }
   }

   return handled;
}

STDMETHODIMP_(bool) CDisplayMgrImpl::OnMouseWheel(UINT nFlags, short zDelta, CPoint point)
{
   bool handled = false;

   if ( m_pCurrTask )
   {
      m_pCurrTask->OnMouseWheel(nFlags,zDelta,point);
      handled = true;
   }
   else
   {
      DisplayObjectContainer dispObjs;
      FindDisplayObjects(point,&dispObjs);

      DisplayObjectContainer::iterator iter;
      for ( iter = dispObjs.begin(); iter != dispObjs.end(); iter++ )
      {
         CComPtr<iDisplayObject> pDO = *iter;
         if(pDO->OnMouseWheel(nFlags,zDelta,point))
         {
            handled = true;
            break;
         }
      }

      // use our event strategy if not handled
      if (!handled && m_EventSink)
      {
         handled = m_EventSink->OnMouseWheel(this, nFlags, zDelta, point);
      }
   }

   return handled;
}

STDMETHODIMP_(bool) CDisplayMgrImpl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
   bool handled = false;

   if (m_pCurrTask )
   {
      m_pCurrTask->OnKeyDown(nChar,nRepCnt,nFlags);
      handled = true;
   }
   else
   {
      for ( DisplayObjectContainer::iterator iter = m_SelectedObjects.begin(); iter != m_SelectedObjects.end(); iter++ )
      {
         CComPtr<iDisplayObject> dispObj = *iter;
         if (dispObj->OnKeyDown(nChar,nRepCnt,nFlags))
         {
            handled = true;
            break;
         }
      }

      // use our event strategy if not handled
      if (!handled && m_EventSink)
      {
         handled = m_EventSink->OnKeyDown(this, nChar,nRepCnt,nFlags);
      }
   }

   return handled;
}

STDMETHODIMP_(bool) CDisplayMgrImpl::OnContextMenu(CWnd* pWnd,CPoint screenPoint)
{
   bool handled = false;

   if (m_pCurrTask )
   {
      m_pCurrTask->OnContextMenu(pWnd,screenPoint);
      handled = true;
   }
   else
   {
      DisplayObjectContainer::iterator iter;
      for ( iter = m_SelectedObjects.begin(); iter != m_SelectedObjects.end(); iter++ )
      {
         CComPtr<iDisplayObject> dispObj = *iter;

         CPoint pntClient = screenPoint;
         if ( screenPoint.x < 0 || screenPoint.y < 0 )
         {
            // the context menu key was pressed, get a point somewhere near the display object
            pntClient = dispObj->GetBoundingBox().TopLeft();
            pntClient += CSize(1,1);

            if ( !dispObj->HitTest(pntClient) )
               pntClient = dispObj->GetBoundingBox().CenterPoint();

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
         handled = m_EventSink->OnContextMenu(this, pWnd, screenPoint);
      }
   }

   return handled;
}

STDMETHODIMP_(BOOL) CDisplayMgrImpl::OnNeedToolTipText(UINT id,NMHDR* pNMHDR,LRESULT* pResult)
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
      if (!m_strToolTipText.IsEmpty())
      {
         pTTT->lpszText = m_strToolTipText.GetBuffer(m_strToolTipText.GetLength()+1);
         pTTT->hinst = NULL;
         bRetVal = TRUE;

//#if defined _DEBUG
//         int id = m_ToolTipObject->GetID();
//         CComPtr<iDisplayList> disp_list;
//         m_ToolTipObject->GetDisplayList(&disp_list);
//         int list_id = disp_list->GetID();
//         WATCH("Tool Tip from DO " << id << "in DL " << list_id << " " << m_strToolTipText);
//#endif // _DEBUG
      }
   }

   *pResult = 0;
   return bRetVal;
}

STDMETHODIMP_(INT_PTR) CDisplayMgrImpl::OnToolHitTest(CPoint point,TOOLINFO* pTI)
{
   m_ToolTipObject.Release();

   DisplayObjectContainer dispObjs;
   FindDisplayObjects(point,&dispObjs);

   if ( 0 < dispObjs.size() )
   {
      CComPtr<iDisplayObject> pDO = *(dispObjs.begin());  // use the first display object found

      if ( pDO->GetToolTipText().IsEmpty() || pDO->GetToolTipText().GetLength() == 0 )
         return -1;

      m_ToolTipObject = pDO;

      ATLASSERT( m_ToolTipObject->HitTest(point) );

      pTI->cbSize = sizeof(TOOLINFO);
      pTI->hwnd = m_pView->GetSafeHwnd();
      pTI->uId =  MAKELONG(point.x,point.y);
      pTI->lpszText = LPSTR_TEXTCALLBACK;
      pTI->rect = m_ToolTipObject->GetBoundingBox();
      pTI->uFlags |= TTF_NOTBUTTON | TTF_ALWAYSTIP;

//#if defined _DEBUG
//      int id = m_ToolTipObject->GetID();
//      CComPtr<iDisplayList> disp_list;
//      m_ToolTipObject->GetDisplayList(&disp_list);
//      int list_id = disp_list->GetID();
//      WATCH("New Tool Tip Object: DO " << id << " in DL " << list_id);
//#endif // _DEBUG

      return pTI->uId;
   }

   return -1;
}

STDMETHODIMP_(DROPEFFECT) CDisplayMgrImpl::OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point)
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
      CComPtr<iTask> task;
      m_pTaskFactory->CreateForeignDragDropTask(this,point,&task);
      SetTask(task);

      de = m_pCurrTask->OnDragEnter(pDataObject,dwKeyState,point);

   }

   return de;
}

STDMETHODIMP_(void) CDisplayMgrImpl::OnDragLeave()
{
   if ( m_pCurrTask )
      m_pCurrTask->OnDragLeave();
}

STDMETHODIMP_(DROPEFFECT) CDisplayMgrImpl::OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point)
{
   DROPEFFECT de = DROPEFFECT_NONE;
   if ( m_pCurrTask )
      de = m_pCurrTask->OnDragOver(pDataObject,dwKeyState,point);

   return de;
}

STDMETHODIMP_(BOOL) CDisplayMgrImpl::OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point)
{
   BOOL bDropped = FALSE;
   if ( m_pCurrTask )
      bDropped = m_pCurrTask->OnDrop(pDataObject,dropEffect,point);

   return bDropped;
}

STDMETHODIMP_(DROPEFFECT) CDisplayMgrImpl::OnDragScroll( DWORD dwKeyState, CPoint point )
{
   DROPEFFECT de = DROPEFFECT_NONE;
   if ( m_pCurrTask )
      de = m_pCurrTask->OnDragScroll(dwKeyState,point);

   return de;
}

STDMETHODIMP_(void) CDisplayMgrImpl::CreateDragObjects(COleDataObject* pDataObject)
{
   ASSERT( m_DragList.size() == 0 );

   // first check to see if this from our tool box
   if (pDataObject->IsDataAvailable(CToolImpl::ms_cfFormat) != FALSE)
   {
      // a tool was dragged over us
      CComPtr<iTool> tool;
      ::CoCreateInstance(CLSID_Tool,NULL,CLSCTX_ALL,IID_iTool,(void**)&tool);
      CComQIPtr<iDraggable,&IID_iDraggable> draggable(tool);

      CComPtr<iDragDataSource> source;
      ::CoCreateInstance(CLSID_DragDataSource,NULL,CLSCTX_ALL,IID_iDragDataSource,(void**)&source);
      source->SetDataObject(pDataObject);
      draggable->OnDrop(source); // Rebuild the tool object from the data object

      m_DragList.push_back( DragMember(draggable.p) );
   }
   else
   {
      // now see if it's a local display object
      DisplayObjectContainer::iterator iter;
      for ( iter = m_SelectedObjects.begin(); iter != m_SelectedObjects.end(); iter++ )
      {
         CComPtr<iDisplayObject> pDO = *iter;
         CComQIPtr<iDraggable,&IID_iDraggable> pDraggable(pDO);

         if ( pDraggable )
         {
            bool bCreated = false;
            CComPtr<iDisplayObject> pDragObject;
            // cycle through factories until we create something successfully
            for (DisplayObjectFactoriesIterator it=m_pDisplayObjectFactories.begin(); it!=m_pDisplayObjectFactories.end(); it++)
            {
               if ( pDataObject->IsDataAvailable(pDraggable->Format()) )
               {
                  it->m_T->Create(pDraggable->Format(),pDataObject,&pDragObject);

                  if (pDragObject)
                  {
                     bCreated = true;
                     break;
                  }
               }
            }

            if ( bCreated )
               m_DragList.push_back( DragMember(pDraggable.p) );
         }
      }
   }
}

STDMETHODIMP_(void) CDisplayMgrImpl::DrawDragObjects(const CPoint& dragStart, const CPoint& dragPoint)
{
   CDManipClientDC dc(m_pView);
   int rop2 = dc.SetROP2(R2_NOTXORPEN);

   CComPtr<iCoordinateMap> pMap;
   m_pView->GetCoordinateMap(&pMap);

   CollectionIndexType count = m_DragList.size();
   for ( CollectionIndexType i = 0; i < count; i++ )
   {
      CComPtr<iDisplayObject> pDO;
      m_DragList[i].m_T->DrawDragImage(&dc, pMap, dragStart, dragPoint);
   }

   dc.SetROP2(rop2);
}

STDMETHODIMP_(void) CDisplayMgrImpl::DestroyDragObjects()
{
   m_DragList.clear();
}

STDMETHODIMP_(void) CDisplayMgrImpl::SetDropSite(iDropSite* pDropSite)
{
   m_pDropSite = pDropSite;
}

STDMETHODIMP_(void) CDisplayMgrImpl::GetDropSite(iDropSite** dropSite)
{
   (*dropSite) = m_pDropSite;
   if ( *dropSite )
      (*dropSite)->AddRef();
}

STDMETHODIMP_(void) CDisplayMgrImpl::HighliteDropSite(BOOL bHighlite)
{
   if ( m_pDropSite )
   {
      CDManipClientDC dc(m_pView);
      m_pDropSite->Highlite(&dc,bHighlite);
   }
}

STDMETHODIMP_(void) CDisplayMgrImpl::OnDragFinished(DROPEFFECT de)
{
   DisplayObjectContainer::iterator iter;
   for ( iter = m_SelectedObjects.begin(); iter != m_SelectedObjects.end(); iter++ )
   {
      CComPtr<iDisplayObject> pDO = *iter;

      CComQIPtr<iDraggable,&IID_iDraggable> pDraggable(pDO);
      ASSERT(pDraggable != 0);
      
      if ( de & DROPEFFECT_MOVE )
         pDraggable->OnMoved();
      else if ( de & DROPEFFECT_COPY )
         pDraggable->OnCopied();
   }
}

STDMETHODIMP_(void) CDisplayMgrImpl::FindDisplayObject(IDType id,IDType listKey,AccessType access,iDisplayObject** dispObj)
{
   CComPtr<iDisplayList> pDL;
   if ( access == atByIndex )
      GetDisplayList(listKey,&pDL);
   else
      FindDisplayList(listKey,&pDL);

   if ( pDL == 0 )
      return;

   pDL->FindDisplayObject(id,dispObj);
}

STDMETHODIMP_(void) CDisplayMgrImpl::FindDisplayObjects(CPoint point,DisplayObjectContainer* dispObjs)
{
   DisplayListContainer::iterator iter;
   for ( iter = m_DisplayLists.begin(); iter != m_DisplayLists.end(); iter++ )
   {
      CComPtr<iDisplayList> pDL = *iter;
      pDL->FindDisplayObjects(point,dispObjs);
   }
}

STDMETHODIMP_(void) CDisplayMgrImpl::FindDisplayObjects(IPoint2d* point,DisplayObjectContainer* dispObjs)
{
   DisplayListContainer::iterator iter;
   for ( iter = m_DisplayLists.begin(); iter != m_DisplayLists.end(); iter++ )
   {
      CComPtr<iDisplayList> pDL = *iter;
      pDL->FindDisplayObjects(point,dispObjs);
   }
}

STDMETHODIMP_(void) CDisplayMgrImpl::FindDisplayObjects(CRect rect,DisplayObjectContainer* dispObjs)
{
   DisplayListContainer::iterator iter;
   for ( iter = m_DisplayLists.begin(); iter != m_DisplayLists.end(); iter++ )
   {
      CComPtr<iDisplayList> pDL = *iter;
      pDL->FindDisplayObjects(rect,dispObjs);
   }
}

STDMETHODIMP_(CollectionIndexType) CDisplayMgrImpl::GetDisplayObjectCount()
{
   SIZE_T count = 0;
   DisplayListContainer::iterator iter;
   for ( iter = m_DisplayLists.begin(); iter != m_DisplayLists.end(); iter++ )
   {
      CComPtr<iDisplayList> pDL = *iter;
      count += pDL->GetDisplayObjectCount();
   }
   return count;
}

STDMETHODIMP_(CollectionIndexType) CDisplayMgrImpl::GetDisplayObjectFactoryCount()
{
   return m_pDisplayObjectFactories.size();
}

STDMETHODIMP_(void) CDisplayMgrImpl::AddDisplayObjectFactory(iDisplayObjectFactory* factory)
{
   m_pDisplayObjectFactories.push_back( DisplayObjectFactoriesItem(factory) );
}

STDMETHODIMP_(void) CDisplayMgrImpl::GetDisplayObjectFactory(CollectionIndexType idx, iDisplayObjectFactory** factory)
{
   if (idx>=0 && idx<GetDisplayObjectFactoryCount())
   {
      m_pDisplayObjectFactories[idx].m_T.CopyTo(factory);
   }
   else
   {
      ATLASSERT(0);
      *factory = 0;
   }
}

STDMETHODIMP_(void) CDisplayMgrImpl::SetTaskFactory(iTaskFactory* pFactory)
{
   m_pTaskFactory = pFactory;
}

STDMETHODIMP_(void) CDisplayMgrImpl::GetTaskFactory(iTaskFactory** factory)
{
   (*factory) = m_pTaskFactory;
   (*factory)->AddRef();
}

STDMETHODIMP_(void) CDisplayMgrImpl::SetTask(iTask* pTask)
{
   if ( m_pCurrTask )
   {
      m_pCurrTask.Release();
   }

   m_pCurrTask = pTask;

   if ( m_pCurrTask )
      m_pCurrTask->Start();
}

void CDisplayMgrImpl::GetBoundingBox(iCoordinateMap* pMap, bool boundOrigin, IRect2d** pRect)
{
   CComPtr<IRect2d> rect;
   rect.CoCreateInstance(CLSID_Rect2d);

   if ( GetDisplayObjectCount() > 0 )
   {
      // Begin with an inverted world
      Float64 rl =  DBL_MAX;
      Float64 rr = -DBL_MAX;
      Float64 rt = -DBL_MAX;
      Float64 rb =  DBL_MAX;

      // Iterate through all of the display objects to determine the physical extents
      DisplayListContainer::iterator iter;
      for ( iter = m_DisplayLists.begin(); iter != m_DisplayLists.end(); iter++ )
      {
         CComPtr<iDisplayList> pDL = *iter;

         CollectionIndexType nDisplayObjects = pDL->GetDisplayObjectCount();
         for ( CollectionIndexType i = 0; i < nDisplayObjects; i++ )
         {
            CComPtr<iDisplayObject> pDO;
            pDL->GetDisplayObject(i,&pDO);

            if ( pDO->IsVisible() )
            {
               CComPtr<IRect2d> box;
               pDO->GetBoundingBox(&box);

               Float64 lBox,rBox,tBox,bBox;
               box->get_Left(&lBox);
               box->get_Right(&rBox);
               box->get_Top(&tBox);
               box->get_Bottom(&bBox);

               rl = _cpp_min(rl,lBox);
               rr = _cpp_max(rr,rBox);
               rt = _cpp_max(rt,tBox);
               rb = _cpp_min(rb,bBox);
            }
         }
      }

      rect->put_Left(  rl );
      rect->put_Right( rr );
      rect->put_Top(   rt );
      rect->put_Bottom(rb  );

      if ( boundOrigin )
      {
         // If BoundZero is enabled, force the bottom left corner of the
         // world rect to (0,0) if it does not already contain it.
         rect->BoundPoint(0,0);
      }
   }

   rect.CopyTo(pRect);
}

std::vector<CComPtr<iDisplayObject> > CDisplayMgrImpl::FindAllDisplayObjects(CPoint point)
{
   std::vector<CComPtr<iDisplayObject> > dispObjects;

   DisplayListContainer::iterator iter;
   for ( iter = m_DisplayLists.begin(); iter != m_DisplayLists.end(); iter++ )
   {
      CComPtr<iDisplayList> pDL = *iter;

      CComPtr<iDisplayObject> dispObj;
      CollectionIndexType doCount = pDL->GetDisplayObjectCount();
      for ( CollectionIndexType i = 0; i < doCount; i++ )
      {
         dispObj.Release();
         pDL->GetDisplayObject(i,&dispObj);
         if ( dispObj->HitTest(point) )
            dispObjects.push_back(dispObj);
      }
   }

   return dispObjects;
}

std::vector<CComPtr<iDisplayObject> > CDisplayMgrImpl::FindAllSelectableDisplayObjects(CPoint point)
{
   std::vector<CComPtr<iDisplayObject> > dispObjects;

   DisplayListContainer::iterator iter;
   for ( iter = m_DisplayLists.begin(); iter != m_DisplayLists.end(); iter++ )
   {
      CComPtr<iDisplayList> pDL = *iter;

      CComPtr<iDisplayObject> dispObj;
      CollectionIndexType doCount = pDL->GetDisplayObjectCount();
      for ( CollectionIndexType i = 0; i < doCount; i++ )
      {
         dispObj.Release();
         pDL->GetDisplayObject(i,&dispObj);
         if ( dispObj->GetSelectionType() == stAll && dispObj->HitTest(point) )
            dispObjects.push_back(dispObj);
      }
   }

   return dispObjects;
}

void CDisplayMgrImpl::FindNextSelectableDisplayObject(CPoint point,iDisplayObject* *pDispObj)
{
   std::vector<CComPtr<iDisplayObject> > dispObjects = FindAllSelectableDisplayObjects(point);
   std::vector<CComPtr<iDisplayObject> >::reverse_iterator iter;

   if ( dispObjects.size() == 0 )
   {
      // No display objects were found
      (*pDispObj) = 0;
      return;
   }

   // Traverse the vector in reverse order, looking for the first display object that
   // is selected. Once found, back up one position (move forward in the display list).
   // This is the next display object to be selected. If none are selected, select the first one
   for ( iter = dispObjects.rbegin(); iter != dispObjects.rend(); iter++ )
   {
      CComPtr<iDisplayObject> dispObj = *iter;
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
         (*pDispObj) = (*iter);
         (*pDispObj)->AddRef();
         return;
      }
   }

   // If we got this far, nothing is selected, or the last display object in the list is selected
   // In either event, we want the first display object
   (*pDispObj) = *(dispObjects.begin());
   (*pDispObj)->AddRef();
   return;
}

// iDisplayListEvents
STDMETHODIMP_(void) CDisplayMgrImpl::OnDisplayObjectAdded(IDType listID,iDisplayObject* pDO)
{
   CRect box = pDO->GetBoundingBox();
   m_pView->InvalidateRect(box);
}

STDMETHODIMP_(void) CDisplayMgrImpl::OnDisplayObjectRemoved(IDType listID,SIZE_T doID)
{
   m_pView->Invalidate();
}

STDMETHODIMP_(void) CDisplayMgrImpl::OnDisplayObjectsCleared(IDType listID)
{
   m_pView->Invalidate();
}

void CDisplayMgrImpl::RegisterEventSink(iDisplayMgrEvents* pEventSink)
{
   m_EventSink = pEventSink;
}

void CDisplayMgrImpl::UnregisterEventSink()
{
   m_EventSink = 0;
}

void CDisplayMgrImpl::GetEventSink(iDisplayMgrEvents** pEventSink)
{
   if ( pEventSink == NULL )
      return;

   (*pEventSink) = m_EventSink;
   (*pEventSink)->AddRef();
}
