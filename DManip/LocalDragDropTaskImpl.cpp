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

#include "pch.h"
#include "LocalDragDropTaskImpl.h"
#include <DManip/DragDataImpl.h>
#include <DManip/CoordinateMap.h>
#include <DManip/DisplayView.h>
#include <DManip/DisplayObject.h>
#include <DManip/DropSite.h>
#include <DManip/Draggable.h>

using namespace WBFL::DManip;

LocalDragDropTask::LocalDragDropTask()
{
}

LocalDragDropTask::LocalDragDropTask(std::shared_ptr<iDisplayMgr> pDM, const CPoint& startPoint)
{
   m_pDispMgr = pDM;

   m_pMap = m_pDispMgr->GetCoordinateMap();

   m_StartPoint = startPoint;

   m_DragStart = startPoint;
   m_LastPoint = m_DragStart;
   m_DragPoint = m_DragStart;

   m_pDataObject = nullptr;
   m_dwKeyState = 0;
   m_dropEffect = 0;
   m_dropList = 0;
}

LocalDragDropTask::~LocalDragDropTask()
{
}

void LocalDragDropTask::Start()
{
   Do();

   auto sink = std::make_shared<DragDataSink>();
   m_pDispMgr->PrepareDragData(sink);

   COleDataSource ods;
   sink->CacheGlobalData(&ods);

   CRect startRect;
   startRect.SetRect(m_StartPoint,m_StartPoint);
   startRect.InflateRect(5,5,5,5);

   CDisplayView* pView = m_pDispMgr->GetView();
   pView->ClientToScreen(&startRect);

   DROPEFFECT de = ods.DoDragDrop(DROPEFFECT_COPY | DROPEFFECT_MOVE, &startRect);

   // If we are in the WaitingForDragEnter state when DoDragDrop completes, this
   // means the drop occurred in a foreign window. A simple intra-view drag did
   // not occur. If there is a meaningful drop effect the current drag objects
   // need to be notified about it.
   if ( de != DROPEFFECT_NONE && CompareStates(WaitingForDragEnter) )
      m_pDispMgr->OnDragFinished(de);

   m_pDispMgr->SetTask(nullptr);
}

void LocalDragDropTask::OnLButtonUp(UINT nFlags,const CPoint& point)
{
}

void LocalDragDropTask::OnRButtonUp(UINT nFlags,const CPoint& point)
{
   // Do nothing
}

void LocalDragDropTask::OnMouseMove(UINT nFlags, const CPoint& point)
{
   // Do nothing
}

void LocalDragDropTask::OnMouseWheel(UINT nFlags, short zDelta, const CPoint& point)
{
   // Do nothing
}

void LocalDragDropTask::OnLButtonDown(UINT nFlags, const CPoint& point)
{
   // Do nothing
}

void LocalDragDropTask::OnRButtonDown(UINT nFlags, const CPoint& point)
{
   // Do nothing
}

void LocalDragDropTask::OnLButtonDblClk(UINT nFlags,const CPoint& point)
{
   // Do nothing
}

void LocalDragDropTask::OnRButtonDblClk(UINT nFlags,const CPoint& point)
{
   // Do nothing
}

void LocalDragDropTask::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
}

void LocalDragDropTask::OnContextMenu(CWnd* pWnd,const CPoint& point)
{
   // Do nothing
}

DROPEFFECT LocalDragDropTask::OnDragEnter(COleDataObject* pDataObject,DWORD dwKeyState,CPoint point)
{
   m_pDataObject = pDataObject;
   m_dwKeyState = dwKeyState;

   m_LastPoint = m_DragPoint;
   m_DragPoint = point;
   return DragEnter(pDataObject,dwKeyState,point);
}

void LocalDragDropTask::OnDragLeave()
{
   DragLeave();
}

DROPEFFECT LocalDragDropTask::OnDragOver(COleDataObject* pDataObject,DWORD dwKeyState,CPoint point)
{
   m_pDataObject = pDataObject;
   m_dwKeyState = dwKeyState;

   CPoint oldDragPoint(m_DragPoint);

   m_DragPoint = point;

   DROPEFFECT de = DragOver(pDataObject,dwKeyState,point);

   m_LastPoint = oldDragPoint;
   return de;
}

DROPEFFECT LocalDragDropTask::OnDragScroll(DWORD dwKeyState,CPoint point)
{
   m_dwKeyState = dwKeyState;

   m_LastPoint = m_DragPoint;
   m_DragPoint = point;
   return DragScroll(dwKeyState,point);
}

BOOL LocalDragDropTask::OnDrop(COleDataObject* pDataObject,DROPEFFECT dropEffect,CPoint point)
{
   m_pDataObject = pDataObject;
   m_dropEffect = dropEffect;

   m_LastPoint = m_DragPoint;
   m_DragPoint = point;
   return Drop(pDataObject,dropEffect,point);
}

DROPEFFECT LocalDragDropTask::OnDropEx(COleDataObject* pDataObject,DROPEFFECT dropEffect,DROPEFFECT dropList,CPoint point)
{
   m_pDataObject = pDataObject;
   m_dropEffect  = dropEffect;
   m_dropList    = dropList;

   m_LastPoint = m_DragPoint;
   m_DragPoint = point;
   return DropEx(pDataObject,dropEffect,dropList,point);
}

void LocalDragDropTask::FSMError(LPCTSTR t,LPCTSTR s)
{
   ASSERT(FALSE);
}

void LocalDragDropTask::InitTask()
{
}

void LocalDragDropTask::CreateDragObjects()
{
   m_pDispMgr->CreateDragObjects(m_pDataObject);
   m_pDispMgr->DrawDragObjects(m_DragStart,m_LastPoint);
}

void LocalDragDropTask::DestroyDragObjects()
{
   m_pDispMgr->DrawDragObjects(m_DragStart,m_DragPoint);
   m_pDispMgr->DestroyDragObjects();

   m_pDispMgr->HighlightDropSite(FALSE);
   m_pDispMgr->UnregisterDropSite();
}

DROPEFFECT LocalDragDropTask::DetermineDropEffect()
{
   DROPEFFECT de = DROPEFFECT_NONE;

   // If the cursor is currently over a display object, 
   // determine if it is a drop object.
   Float64 wx, wy;
   m_pMap->LPtoWP(m_DragPoint.x, m_DragPoint.y, &wx, &wy);
   m_pMap->WPtoMP(wx, wy, &wx, &wy);
   m_PointCache.Move(wx, wy);

   auto dispObjs = m_pDispMgr->FindDisplayObjects(m_DragPoint);
   bool found = false;

   CDisplayView* pView = m_pDispMgr->GetView();
   CDManipClientDC dc(pView);

   for(auto& dispObj : dispObjs)
   {
      // Is it a drop object? Can we drop the payload on it?
      auto drop_site = dispObj->GetDropSite();
      if ( drop_site )
      {
         de = drop_site->CanDrop(m_pDataObject,m_dwKeyState,m_PointCache);
         if ( 0 < de )
         {
            // Payload can be dropped!
            auto current_drop_site = m_pDispMgr->GetDropSite();
            if (current_drop_site && drop_site != current_drop_site)
            {
               // if there is a current drop site, draw it in its normal stage
               m_pDispMgr->HighlightDropSite(FALSE);
            }

            // Set the new drop site
            m_pDispMgr->RegisterDropSite(drop_site);

            // draw in Highlighted stage
            m_pDispMgr->HighlightDropSite(TRUE);

            found = true;
            break; // we found a drop site... get the heck outta here
         }
      }
   }

   if (!found)
   {
      // Cursor is not over a display object - relegate to the view
      m_pDispMgr->HighlightDropSite(FALSE);
      m_pDispMgr->UnregisterDropSite();

      // Ask the View if we can drop the payload on the canvas
      CDisplayView* pView = m_pDispMgr->GetView();
      de = pView->CanDrop(m_pDataObject,m_dwKeyState,m_PointCache);
   }

   return de;
}

void LocalDragDropTask::TrackDragObjects()
{
   m_pDispMgr->DrawDragObjects(m_DragStart,m_LastPoint);
   m_pDispMgr->DrawDragObjects(m_DragStart,m_DragPoint);
}

void LocalDragDropTask::NotifyDropTarget()
{
   // If the payload landed on a drop site, notify it and tell
   // the display object what just happened,
   // otherwise, this is a simple intra-view move operation
   auto drop_site = m_pDispMgr->GetDropSite();
   if ( drop_site )
   {
      Float64 wx, wy;
      m_pMap->LPtoWP(m_DragPoint.x, m_DragPoint.y, &wx, &wy);
      m_pMap->WPtoMP(wx,wy,&wx,&wy);
      m_PointCache.Move(wx, wy);

      drop_site->OnDropped(m_pDataObject,m_dropEffect,m_PointCache);
      m_pDispMgr->OnDragFinished(m_dropEffect);
   }
   else
   {
      // convert offset distances to model space coords
      Float64 dox, doy, dex, dey;
      m_pMap->LPtoWP(m_DragStart.x, m_DragStart.y, &dox, &doy);
      m_pMap->LPtoWP(m_DragPoint.x, m_DragPoint.y, &dex, &dey);
      m_pMap->WPtoMP(dox, doy, &dox, &doy);
      m_pMap->WPtoMP(dex, dey, &dex, &dey);

      Float64 ddx = dex-dox;
      Float64 ddy = dey-doy;

      WBFL::Geometry::Size2d offset(ddx, ddy);

      auto dragObjects = m_pDispMgr->GetSelectedObjects();
      for(auto& dispObj : dragObjects)
      {
         auto draggable = std::dynamic_pointer_cast<iDraggable>(dispObj);
         CHECK(draggable);
         draggable->OnDragMoved(offset);
      }
   }
}
