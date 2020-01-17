///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2020  Washington State Department of Transportation
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

// ForeignDragDropTaskImpl.cpp: implementation of the CForeignDragDropTaskImpl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <WBFLDManip.h>
#include <DManip\DManip.h>
#include "ForeignDragDropTaskImpl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CForeignDragDropTaskImpl::CForeignDragDropTaskImpl()
{
   m_PointCache.CoCreateInstance(CLSID_Point2d);
}

CForeignDragDropTaskImpl::~CForeignDragDropTaskImpl()
{
}

void CForeignDragDropTaskImpl::Init(iDisplayMgr* pDM,const CPoint& startPoint)
{
   m_pDispMgr = pDM;

   m_pDispMgr->GetCoordinateMap(&m_pMap);

   m_DragStart = startPoint;
   m_LastPoint = m_DragStart;
   m_DragPoint = m_DragStart;

   m_pDataObject = 0;
   m_dwKeyState  = 0;
   m_dropEffect  = 0;
   m_dropList    = 0;
}

STDMETHODIMP_(void) CForeignDragDropTaskImpl::Start()
{
   Do();
}

STDMETHODIMP_(void) CForeignDragDropTaskImpl::OnLButtonUp(UINT nFlags,const CPoint& point)
{
}

STDMETHODIMP_(void) CForeignDragDropTaskImpl::OnRButtonUp(UINT nFlags,const CPoint& point)
{
   // Do nothing
}

STDMETHODIMP_(void) CForeignDragDropTaskImpl::OnMouseMove(UINT nFlags, const CPoint& point)
{
   // Do nothing
}

STDMETHODIMP_(void) CForeignDragDropTaskImpl::OnMouseWheel(UINT nFlags, short zDelta, const CPoint& point)
{
   // Do nothing
}

STDMETHODIMP_(void) CForeignDragDropTaskImpl::OnLButtonDown(UINT nFlags, const CPoint& point)
{
   // Do nothing
}

STDMETHODIMP_(void) CForeignDragDropTaskImpl::OnRButtonDown(UINT nFlags, const CPoint& point)
{
   // Do nothing
}

STDMETHODIMP_(void) CForeignDragDropTaskImpl::OnLButtonDblClk(UINT nFlags,const CPoint& point)
{
   // Do nothing
}

STDMETHODIMP_(void) CForeignDragDropTaskImpl::OnRButtonDblClk(UINT nFlags,const CPoint& point)
{
   // Do nothing
}

STDMETHODIMP_(void) CForeignDragDropTaskImpl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
}

STDMETHODIMP_(void) CForeignDragDropTaskImpl::OnContextMenu(CWnd* pWnd,const CPoint& point)
{
   // Do nothing
}

STDMETHODIMP_(DROPEFFECT) CForeignDragDropTaskImpl::OnDragEnter(COleDataObject* pDataObject,DWORD dwKeyState,CPoint point)
{
   m_pDataObject = pDataObject;
   m_dwKeyState = dwKeyState;

   m_LastPoint = m_DragPoint;
   m_DragPoint = point;

   return DragEnter(pDataObject,dwKeyState,point);
}

STDMETHODIMP_(void) CForeignDragDropTaskImpl::OnDragLeave()
{
   DragLeave();
   
   m_pDispMgr->SetTask(nullptr);
}

STDMETHODIMP_(DROPEFFECT) CForeignDragDropTaskImpl::OnDragOver(COleDataObject* pDataObject,DWORD dwKeyState,CPoint point)
{
   m_pDataObject = pDataObject;
   m_dwKeyState = dwKeyState;

   CPoint oldDragPoint(m_DragPoint);

   m_DragPoint = point;

   DROPEFFECT de = DragOver(pDataObject,dwKeyState,point);

   m_LastPoint = oldDragPoint;
   return de;
}

STDMETHODIMP_(DROPEFFECT) CForeignDragDropTaskImpl::OnDragScroll(DWORD dwKeyState,CPoint point)
{
   m_dwKeyState = dwKeyState;

   m_LastPoint = m_DragPoint;
   m_DragPoint = point;
   return DragScroll(dwKeyState,point);
}

STDMETHODIMP_(BOOL) CForeignDragDropTaskImpl::OnDrop(COleDataObject* pDataObject,DROPEFFECT dropEffect,CPoint point)
{
   m_pDataObject = pDataObject;
   m_dropEffect = dropEffect;

   m_LastPoint = m_DragPoint;
   m_DragPoint = point;
   
   BOOL bRetVal = Drop(pDataObject,dropEffect,point);

   if ( CompareStates(CForeignDragDropFSM::Done) )
      m_pDispMgr->SetTask(nullptr);

   return bRetVal;
}

STDMETHODIMP_(DROPEFFECT) CForeignDragDropTaskImpl::OnDropEx(COleDataObject* pDataObject,DROPEFFECT dropEffect,DROPEFFECT dropList,CPoint point)
{
   m_pDataObject = pDataObject;
   m_dropEffect  = dropEffect;
   m_dropList    = dropList;

   m_LastPoint = m_DragPoint;
   m_DragPoint = point;

   BOOL bRetVal = DropEx(pDataObject,dropEffect,dropList,point);

   if ( CompareStates(CForeignDragDropFSM::Done) )
      m_pDispMgr->SetTask(nullptr);

   return bRetVal;
}

STDMETHODIMP_(void) CForeignDragDropTaskImpl::FSMError(LPCTSTR t,LPCTSTR s)
{
   ASSERT(FALSE);
}

STDMETHODIMP_(void) CForeignDragDropTaskImpl::InitTask()
{
}

STDMETHODIMP_(void) CForeignDragDropTaskImpl::CreateDragObjects()
{
   m_pDispMgr->CreateDragObjects(m_pDataObject);
   m_pDispMgr->DrawDragObjects(m_DragStart,m_LastPoint);
}

STDMETHODIMP_(void) CForeignDragDropTaskImpl::DestroyDragObjects()
{
   m_pDispMgr->DrawDragObjects(m_DragStart,m_DragPoint);
   m_pDispMgr->DestroyDragObjects();

   m_pDispMgr->HighliteDropSite(FALSE);
   m_pDispMgr->UnregisterDropSite();
}

STDMETHODIMP_(DROPEFFECT) CForeignDragDropTaskImpl::DetermineDropEffect()
{
   DROPEFFECT de = DROPEFFECT_NONE;

   // If the cursor is currently over a display object, 
   // determine if it is a drop object.
   DisplayObjectContainer dispObjs;
   m_pDispMgr->FindDisplayObjects(m_DragPoint,&dispObjs);
   bool found = false;
   if ( 0 < dispObjs.size() )
   {
      Float64 wx, wy;
      m_pMap->LPtoWP(m_DragPoint.x, m_DragPoint.y, &wx, &wy);
      m_pMap->WPtoMP(wx, wy, &wx, &wy);
      m_PointCache->put_X(wx);
      m_PointCache->put_Y(wy);

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
               CComPtr<iDropSite> currentDropSite;
               m_pDispMgr->GetDropSite(&currentDropSite);
               if ( currentDropSite && !pDropSite.IsEqualObject(currentDropSite) )
               {
                  // if there is a current drop site, draw it in its normal stage
                  m_pDispMgr->HighliteDropSite(FALSE);
               }

               // Set the new drop site
               m_pDispMgr->RegisterDropSite(pDropSite);

               // draw in highlited stage
               m_pDispMgr->HighliteDropSite(TRUE);

               found = true;
               break; // we found a drop site... get the heck outta here
            }
         }
      }
   }

   if (!found)
   {
      // Cursor is not over a display object - relegate to view
      m_pDispMgr->HighliteDropSite(FALSE);
      m_pDispMgr->UnregisterDropSite();

      // Ask the View if we can drop the payload on the canvas
      Float64 wx, wy;
      m_pMap->LPtoWP(m_DragPoint.x, m_DragPoint.y, &wx, &wy);
      m_pMap->WPtoMP(wx, wy, &wx, &wy);
      m_PointCache->put_X(wx);
      m_PointCache->put_Y(wy);

      CDisplayView* pView = m_pDispMgr->GetView();
      de = pView->CanDrop(m_pDataObject,m_dwKeyState,m_PointCache);
   }

   return de;
}

STDMETHODIMP_(void) CForeignDragDropTaskImpl::TrackDragObjects()
{
   m_pDispMgr->DrawDragObjects(m_DragStart,m_LastPoint);
   m_pDispMgr->DrawDragObjects(m_DragStart,m_DragPoint);
}

STDMETHODIMP_(void) CForeignDragDropTaskImpl::NotifyDropTarget()
{
   // If the payload landed on a drop site, notify it,
   // otherwise, notify the canvas
   Float64 wx, wy;
   m_pMap->LPtoWP(m_DragPoint.x, m_DragPoint.y, &wx, &wy);
   m_pMap->WPtoMP(wx, wy, &wx, &wy);
   m_PointCache->put_X(wx);
   m_PointCache->put_Y(wy);

   CComPtr<iDropSite> pDropSite;
   m_pDispMgr->GetDropSite(&pDropSite);
   if ( pDropSite )
   {
      pDropSite->OnDropped(m_pDataObject,m_dropEffect,m_PointCache);
   }
   else
   {
      CDisplayView* pView = m_pDispMgr->GetView();
      pView->OnDropped(m_pDataObject,m_dropEffect,m_PointCache);
   }
}
