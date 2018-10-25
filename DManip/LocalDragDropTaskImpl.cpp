///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2015  Washington State Department of Transportation
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

// LocalDragDropTaskImpl.cpp: implementation of the CLocalDragDropTaskImpl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <WBFLDManip.h>
#include <DManip\DManip.h>
#include "LocalDragDropTaskImpl.h"

#include "DragDataImpl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLocalDragDropTaskImpl::CLocalDragDropTaskImpl()
{
   m_PointCache.CoCreateInstance(CLSID_Point2d);
}

CLocalDragDropTaskImpl::~CLocalDragDropTaskImpl()
{
}

void CLocalDragDropTaskImpl::Init(iDisplayMgr* pDM,const CPoint& startPoint)
{
   m_pDispMgr = pDM;

   m_pDispMgr->GetCoordinateMap(&m_pMap);

   m_StartPoint = startPoint;

   m_DragStart = startPoint;
   m_LastPoint = m_DragStart;
   m_DragPoint = m_DragStart;

   m_pDataObject = 0;
   m_dwKeyState  = 0;
   m_dropEffect  = 0;
   m_dropList    = 0;
}

STDMETHODIMP_(void) CLocalDragDropTaskImpl::Start()
{
   Do();

   CComObject<CDragDataSinkImpl>* pSink;
   CComObject<CDragDataSinkImpl>::CreateInstance(&pSink);
   
   m_pDispMgr->PrepareDragData(pSink);

   COleDataSource ods;
   pSink->CacheGlobalData(&ods);

   CRect startRect;
   startRect.SetRect(m_StartPoint,m_StartPoint);
   startRect.InflateRect(5,5,5,5);

   CDisplayView* pView = m_pDispMgr->GetView();
   pView->ClientToScreen(&startRect);

   DROPEFFECT de = ods.DoDragDrop(DROPEFFECT_COPY | DROPEFFECT_MOVE,
                                  &startRect);

   // If we are in the WaitingForDragEnter state when DoDragDrop completes, this
   // means the drop occured in a foreign window. A simple intra-view drag did
   // not occur. If there is a meaningful drop effect the current drag objects
   // need to be notified about it.
   if ( de != DROPEFFECT_NONE && CompareStates(WaitingForDragEnter) )
      m_pDispMgr->OnDragFinished(de);

   m_pDispMgr->SetTask(NULL);
}

STDMETHODIMP_(void) CLocalDragDropTaskImpl::OnLButtonUp(UINT nFlags,const CPoint& point)
{
}

STDMETHODIMP_(void) CLocalDragDropTaskImpl::OnRButtonUp(UINT nFlags,const CPoint& point)
{
   // Do nothing
}

STDMETHODIMP_(void) CLocalDragDropTaskImpl::OnMouseMove(UINT nFlags, const CPoint& point)
{
   // Do nothing
}

STDMETHODIMP_(void) CLocalDragDropTaskImpl::OnMouseWheel(UINT nFlags, short zDelta, const CPoint& point)
{
   // Do nothing
}

STDMETHODIMP_(void) CLocalDragDropTaskImpl::OnLButtonDown(UINT nFlags, const CPoint& point)
{
   // Do nothing
}

STDMETHODIMP_(void) CLocalDragDropTaskImpl::OnRButtonDown(UINT nFlags, const CPoint& point)
{
   // Do nothing
}

STDMETHODIMP_(void) CLocalDragDropTaskImpl::OnLButtonDblClk(UINT nFlags,const CPoint& point)
{
   // Do nothing
}

STDMETHODIMP_(void) CLocalDragDropTaskImpl::OnRButtonDblClk(UINT nFlags,const CPoint& point)
{
   // Do nothing
}

STDMETHODIMP_(void) CLocalDragDropTaskImpl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
}

STDMETHODIMP_(void) CLocalDragDropTaskImpl::OnContextMenu(CWnd* pWnd,const CPoint& point)
{
   // Do nothing
}

STDMETHODIMP_(DROPEFFECT) CLocalDragDropTaskImpl::OnDragEnter(COleDataObject* pDataObject,DWORD dwKeyState,CPoint point)
{
   m_pDataObject = pDataObject;
   m_dwKeyState = dwKeyState;

   m_LastPoint = m_DragPoint;
   m_DragPoint = point;
   return DragEnter(pDataObject,dwKeyState,point);
}

STDMETHODIMP_(void) CLocalDragDropTaskImpl::OnDragLeave()
{
   DragLeave();
}

STDMETHODIMP_(DROPEFFECT) CLocalDragDropTaskImpl::OnDragOver(COleDataObject* pDataObject,DWORD dwKeyState,CPoint point)
{
   m_pDataObject = pDataObject;
   m_dwKeyState = dwKeyState;

   CPoint oldDragPoint(m_DragPoint);

   m_DragPoint = point;

   DROPEFFECT de = DragOver(pDataObject,dwKeyState,point);

   m_LastPoint = oldDragPoint;
   return de;
}

STDMETHODIMP_(DROPEFFECT) CLocalDragDropTaskImpl::OnDragScroll(DWORD dwKeyState,CPoint point)
{
   m_dwKeyState = dwKeyState;

   m_LastPoint = m_DragPoint;
   m_DragPoint = point;
   return DragScroll(dwKeyState,point);
}

STDMETHODIMP_(BOOL) CLocalDragDropTaskImpl::OnDrop(COleDataObject* pDataObject,DROPEFFECT dropEffect,CPoint point)
{
   m_pDataObject = pDataObject;
   m_dropEffect = dropEffect;

   m_LastPoint = m_DragPoint;
   m_DragPoint = point;
   return Drop(pDataObject,dropEffect,point);
}

STDMETHODIMP_(DROPEFFECT) CLocalDragDropTaskImpl::OnDropEx(COleDataObject* pDataObject,DROPEFFECT dropEffect,DROPEFFECT dropList,CPoint point)
{
   m_pDataObject = pDataObject;
   m_dropEffect  = dropEffect;
   m_dropList    = dropList;

   m_LastPoint = m_DragPoint;
   m_DragPoint = point;
   return DropEx(pDataObject,dropEffect,dropList,point);
}

STDMETHODIMP_(void) CLocalDragDropTaskImpl::FSMError(LPCTSTR t,LPCTSTR s)
{
   ASSERT(FALSE);
}

STDMETHODIMP_(void) CLocalDragDropTaskImpl::InitTask()
{
}

STDMETHODIMP_(void) CLocalDragDropTaskImpl::CreateDragObjects()
{
   m_pDispMgr->CreateDragObjects(m_pDataObject);
   m_pDispMgr->DrawDragObjects(m_DragStart,m_LastPoint);
}

STDMETHODIMP_(void) CLocalDragDropTaskImpl::DestroyDragObjects()
{
   m_pDispMgr->DrawDragObjects(m_DragStart,m_DragPoint);
   m_pDispMgr->DestroyDragObjects();

   m_pDispMgr->HighliteDropSite(FALSE);
   m_pDispMgr->SetDropSite(NULL);
}

STDMETHODIMP_(DROPEFFECT) CLocalDragDropTaskImpl::DetermineDropEffect()
{
#pragma Reminder("CLocalDragDropTaskImpl - move this to a common base class for all D&D tasks")
// This code, and probably a lot more, is duplicated in ForeignDragDropTaskImpl. Move it to a
// common base class

   DROPEFFECT de = DROPEFFECT_NONE;

   // If the cursor is currently over a display object, 
   // determine if it is a drop object.
   Float64 wx, wy;
   m_pMap->LPtoWP(m_DragPoint.x, m_DragPoint.y, &wx, &wy);
   m_pMap->WPtoMP(wx, wy, &wx, &wy);
   m_PointCache->put_X(wx);
   m_PointCache->put_Y(wy);

   DisplayObjectContainer dispObjs;
   m_pDispMgr->FindDisplayObjects(m_DragPoint,&dispObjs);
   bool found = false;

   CDisplayView* pView = m_pDispMgr->GetView();
   CDManipClientDC dc(pView);

   DisplayObjectContainer::iterator iter;
   for ( iter = dispObjs.begin(); iter != dispObjs.end(); iter++ )
   {
      CComPtr<iDisplayObject> pDO = *iter;

      // Is it a drop object? Can we drop the payload on it?
      CComPtr<iDropSite> pDropSite;
      pDO->GetDropSite(&pDropSite);
      if ( pDropSite )
      {
         de = pDropSite->CanDrop(m_pDataObject,m_dwKeyState,m_PointCache);
         if ( de > 0 )
         {
            // Payload can be dropped!
            pDropSite->Highlite(&dc,TRUE);
#pragma Reminder("The drop site needs to be unhighlighed when the mouse moves off of it")

            found = true;
            break; // we found a drop site... get the heck outta here
         }
      }
   }

   if (!found)
   {
      // Cursor is not over a display object - relegate to the view
      m_pDispMgr->HighliteDropSite(FALSE);

      // Ask the View if we can drop the payload on the canvas
      CDisplayView* pView = m_pDispMgr->GetView();
      de = pView->CanDrop(m_pDataObject,m_dwKeyState,m_PointCache);
   }

   return de;
}

STDMETHODIMP_(void) CLocalDragDropTaskImpl::TrackDragObjects()
{
   m_pDispMgr->DrawDragObjects(m_DragStart,m_LastPoint);
   m_pDispMgr->DrawDragObjects(m_DragStart,m_DragPoint);
}

STDMETHODIMP_(void) CLocalDragDropTaskImpl::NotifyDropTarget()
{
   // If the payload landed on a drop site, notify it and tell
   // the display object what just happened,
   // otherwise, this is a simple intra-view move operation
   CComPtr<iDropSite> pDropSite;
   m_pDispMgr->GetDropSite(&pDropSite);
   if ( pDropSite )
   {
      Float64 wx, wy;
      m_pMap->LPtoWP(m_DragPoint.x, m_DragPoint.y, &wx, &wy);
      m_pMap->WPtoMP(wx,wy,&wx,&wy);
      m_PointCache->put_X(wx);
      m_PointCache->put_Y(wy);

      pDropSite->OnDropped(m_pDataObject,m_dropEffect,m_PointCache);
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

      CComPtr<ISize2d> offset;
      offset.CoCreateInstance(CLSID_Size2d);
      offset->put_Dx(ddx);
      offset->put_Dy(ddy);

      DisplayObjectContainer dragObjects;
      m_pDispMgr->GetSelectedObjects(&dragObjects);
      DisplayObjectContainer::iterator iter;
      for ( iter = dragObjects.begin(); iter != dragObjects.end(); iter++ )
      {
         CComPtr<iDisplayObject> pDisplayObject = *iter;
         CComQIPtr<iDraggable,&IID_iDraggable> pDraggable(pDisplayObject);
         ATLASSERT(pDraggable != 0);
         pDraggable->OnDragMoved(offset);
      }
   }
}
