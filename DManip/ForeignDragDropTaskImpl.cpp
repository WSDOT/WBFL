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
#include "ForeignDragDropTaskImpl.h"
#include <DManip/DisplayObject.h>
#include <DManip/DropSite.h>
#include <DManip/DisplayView.h>

using namespace WBFL::DManip;

ForeignDragDropTask::ForeignDragDropTask()
{
}

ForeignDragDropTask::ForeignDragDropTask(std::shared_ptr<iDisplayMgr> pDM,const CPoint& startPoint)
{
   m_pDispMgr = pDM;

   m_pMap = m_pDispMgr->GetCoordinateMap();

   m_DragStart = startPoint;
   m_LastPoint = m_DragStart;
   m_DragPoint = m_DragStart;

   m_pDataObject = nullptr;
   m_dwKeyState  = 0;
   m_dropEffect  = 0;
   m_dropList    = 0;
}

ForeignDragDropTask::~ForeignDragDropTask()
{
}

void ForeignDragDropTask::Start()
{
   Do();
}

void ForeignDragDropTask::OnLButtonUp(UINT nFlags,const CPoint& point)
{
}

void ForeignDragDropTask::OnRButtonUp(UINT nFlags,const CPoint& point)
{
   // Do nothing
}

void ForeignDragDropTask::OnMouseMove(UINT nFlags, const CPoint& point)
{
   // Do nothing
}

void ForeignDragDropTask::OnMouseWheel(UINT nFlags, short zDelta, const CPoint& point)
{
   // Do nothing
}

void ForeignDragDropTask::OnLButtonDown(UINT nFlags, const CPoint& point)
{
   // Do nothing
}

void ForeignDragDropTask::OnRButtonDown(UINT nFlags, const CPoint& point)
{
   // Do nothing
}

void ForeignDragDropTask::OnLButtonDblClk(UINT nFlags,const CPoint& point)
{
   // Do nothing
}

void ForeignDragDropTask::OnRButtonDblClk(UINT nFlags,const CPoint& point)
{
   // Do nothing
}

void ForeignDragDropTask::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
}

void ForeignDragDropTask::OnContextMenu(CWnd* pWnd,const CPoint& point)
{
   // Do nothing
}

DROPEFFECT ForeignDragDropTask::OnDragEnter(COleDataObject* pDataObject,DWORD dwKeyState,CPoint point)
{
   m_pDataObject = pDataObject;
   m_dwKeyState = dwKeyState;

   m_LastPoint = m_DragPoint;
   m_DragPoint = point;

   return DragEnter(pDataObject,dwKeyState,point);
}

void ForeignDragDropTask::OnDragLeave()
{
   DragLeave();
   
   m_pDispMgr->SetTask(nullptr);
}

DROPEFFECT ForeignDragDropTask::OnDragOver(COleDataObject* pDataObject,DWORD dwKeyState,CPoint point)
{
   m_pDataObject = pDataObject;
   m_dwKeyState = dwKeyState;

   CPoint oldDragPoint(m_DragPoint);

   m_DragPoint = point;

   DROPEFFECT de = DragOver(pDataObject,dwKeyState,point);

   m_LastPoint = oldDragPoint;
   return de;
}

DROPEFFECT ForeignDragDropTask::OnDragScroll(DWORD dwKeyState,CPoint point)
{
   m_dwKeyState = dwKeyState;

   m_LastPoint = m_DragPoint;
   m_DragPoint = point;
   return DragScroll(dwKeyState,point);
}

BOOL ForeignDragDropTask::OnDrop(COleDataObject* pDataObject,DROPEFFECT dropEffect,CPoint point)
{
   m_pDataObject = pDataObject;
   m_dropEffect = dropEffect;

   m_LastPoint = m_DragPoint;
   m_DragPoint = point;
   
   BOOL bRetVal = Drop(pDataObject,dropEffect,point);

   if ( CompareStates(ForeignDragDropFSM::Done) )
      m_pDispMgr->SetTask(nullptr);

   return bRetVal;
}

DROPEFFECT ForeignDragDropTask::OnDropEx(COleDataObject* pDataObject,DROPEFFECT dropEffect,DROPEFFECT dropList,CPoint point)
{
   m_pDataObject = pDataObject;
   m_dropEffect  = dropEffect;
   m_dropList    = dropList;

   m_LastPoint = m_DragPoint;
   m_DragPoint = point;

   BOOL bRetVal = DropEx(pDataObject,dropEffect,dropList,point);

   if ( CompareStates(ForeignDragDropFSM::Done) )
      m_pDispMgr->SetTask(nullptr);

   return bRetVal;
}

void ForeignDragDropTask::FSMError(LPCTSTR t,LPCTSTR s)
{
   ASSERT(FALSE);
}

void ForeignDragDropTask::InitTask()
{
}

void ForeignDragDropTask::CreateDragObjects()
{
   m_pDispMgr->CreateDragObjects(m_pDataObject);
   m_pDispMgr->DrawDragObjects(m_DragStart,m_LastPoint);
}

void ForeignDragDropTask::DestroyDragObjects()
{
   m_pDispMgr->DrawDragObjects(m_DragStart,m_DragPoint);
   m_pDispMgr->DestroyDragObjects();

   m_pDispMgr->HighlightDropSite(FALSE);
   m_pDispMgr->UnregisterDropSite();
}

DROPEFFECT ForeignDragDropTask::DetermineDropEffect()
{
   DROPEFFECT de = DROPEFFECT_NONE;

   // If the cursor is currently over a display object, 
   // determine if it is a drop object.
   auto dispObjs = m_pDispMgr->FindDisplayObjects(m_DragPoint);
   bool found = false;
   if ( 0 < dispObjs.size() )
   {
      Float64 wx, wy;
      m_pMap->LPtoWP(m_DragPoint.x, m_DragPoint.y, &wx, &wy);
      m_pMap->WPtoMP(wx, wy, &wx, &wy);
      m_PointCache.Move(wx, wy);

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
               if (current_drop_site && drop_site.get() != current_drop_site.get() )
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
   }

   if (!found)
   {
      // Cursor is not over a display object - relegate to view
      m_pDispMgr->HighlightDropSite(FALSE);
      m_pDispMgr->UnregisterDropSite();

      // Ask the View if we can drop the payload on the canvas
      Float64 wx, wy;
      m_pMap->LPtoWP(m_DragPoint.x, m_DragPoint.y, &wx, &wy);
      m_pMap->WPtoMP(wx, wy, &wx, &wy);
      m_PointCache.Move(wx, wy);

      CDisplayView* pView = m_pDispMgr->GetView();
      de = pView->CanDrop(m_pDataObject,m_dwKeyState,m_PointCache);
   }

   return de;
}

void ForeignDragDropTask::TrackDragObjects()
{
   m_pDispMgr->DrawDragObjects(m_DragStart,m_LastPoint);
   m_pDispMgr->DrawDragObjects(m_DragStart,m_DragPoint);
}

void ForeignDragDropTask::NotifyDropTarget()
{
   // If the payload landed on a drop site, notify it,
   // otherwise, notify the canvas
   Float64 wx, wy;
   m_pMap->LPtoWP(m_DragPoint.x, m_DragPoint.y, &wx, &wy);
   m_pMap->WPtoMP(wx, wy, &wx, &wy);
   m_PointCache.Move(wx, wy);

   auto drop_site = m_pDispMgr->GetDropSite();
   if ( drop_site )
   {
      drop_site->OnDropped(m_pDataObject,m_dropEffect,m_PointCache);
   }
   else
   {
      CDisplayView* pView = m_pDispMgr->GetView();
      pView->OnDropped(m_pDataObject,m_dropEffect,m_PointCache);
   }
}
