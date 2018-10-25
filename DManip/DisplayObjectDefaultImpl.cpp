///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2016  Washington State Department of Transportation
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

// DisplayObjectDefaultImpl.cpp: implementation of the CDisplayObjectDefaultImpl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <DManip\DManip.h>
#include <DManip\DisplayObjectDefaultImpl.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif 

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDisplayObjectDefaultImpl::CDisplayObjectDefaultImpl()
{
   m_pParent = 0;
   m_strToolTipText = "";
   m_MaxToolTipWidth = -1; // use default width
   m_ToolTipDisplayTime = -1; // use default duration
   m_bSelected = FALSE;
   m_pDispList = 0;

   m_ID = -1;
   m_bIsVisible = TRUE;

   m_pDropSite = 0;

   m_SelectionType = stNone;

   // we will be using this a lot so allocate once, use many
   m_ReusableRect.CoCreateInstance(CLSID_Rect2d);

   m_pItemData = NULL;
}

CDisplayObjectDefaultImpl::~CDisplayObjectDefaultImpl()
{
   if ( m_pItemData && m_bDeleteItemData )
   {
      delete m_pItemData;
      m_pItemData = NULL;
   }
}

void CDisplayObjectDefaultImpl::SetDisplayObject(iDisplayObject* pParent)
{
   m_pParent = pParent;
}

void CDisplayObjectDefaultImpl::Fire_OnChanged()
{
   if ( m_EventSink )
      m_EventSink->OnChanged(m_pParent);
}

void CDisplayObjectDefaultImpl::Fire_OnDragMoved(ISize2d* offset)
{
   if ( m_EventSink )
      m_EventSink->OnDragMoved(m_pParent,offset);
}

void CDisplayObjectDefaultImpl::Fire_OnMoved()
{
   if ( m_EventSink )
      m_EventSink->OnMoved(m_pParent);
}

void CDisplayObjectDefaultImpl::Fire_OnCopied()
{
   if ( m_EventSink )
      m_EventSink->OnCopied(m_pParent);
}

bool CDisplayObjectDefaultImpl::Fire_OnLButtonDblClk(UINT nFlags,CPoint point)
{
   if ( m_EventSink )
   {
      return m_EventSink->OnLButtonDblClk(m_pParent,nFlags,point);
   }
   else
   {
      return false;
   }
}

bool CDisplayObjectDefaultImpl::Fire_OnLButtonDown(UINT nFlags,CPoint point)
{
   if ( m_EventSink )
   {
      return m_EventSink->OnLButtonDown(m_pParent,nFlags,point);
   }
   else
   {
      return false;
   }
}

bool CDisplayObjectDefaultImpl::Fire_OnLButtonUp(UINT nFlags,CPoint point)
{
   if ( m_EventSink )
   {
      return m_EventSink->OnLButtonUp(m_pParent,nFlags,point);
   }
   else
   {
      return false;
   }
}

bool CDisplayObjectDefaultImpl::Fire_OnRButtonDown(UINT nFlags,CPoint point)
{
   if ( m_EventSink )
   {
      return m_EventSink->OnRButtonDown(m_pParent,nFlags,point);
   }
   else
   {
      return false;
   }
}

bool CDisplayObjectDefaultImpl::Fire_OnRButtonUp(UINT nFlags,CPoint point)
{
   if ( m_EventSink )
   {
      return m_EventSink->OnRButtonUp(m_pParent,nFlags,point);
   }
   else
   {
      return false;
   }
}

bool CDisplayObjectDefaultImpl::Fire_OnRButtonDblClk(UINT nFlags,CPoint point)
{
   if ( m_EventSink )
   {
      return m_EventSink->OnRButtonDblClk(m_pParent,nFlags,point);
   }
   else
   {
      return false;
   }
}

bool CDisplayObjectDefaultImpl::Fire_OnMouseMove(UINT nFlags,CPoint point)
{
   if ( m_EventSink )
   {
      return m_EventSink->OnMouseMove(m_pParent,nFlags,point);
   }
   else
   {
      return false;
   }
}

bool CDisplayObjectDefaultImpl::Fire_OnMouseWheel(UINT nFlags,short zDelta, CPoint point)
{
   if ( m_EventSink )
   {
      return m_EventSink->OnMouseWheel(m_pParent,nFlags,zDelta,point);
   }
   else
   {
      return false;
   }
}

bool CDisplayObjectDefaultImpl::Fire_OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
   if ( m_EventSink )
   {
      return m_EventSink->OnKeyDown(m_pParent,nChar,nRepCnt,nFlags);
   }
   else
   {
      return false;
   }
}

bool CDisplayObjectDefaultImpl::Fire_OnContextMenu(CWnd* pWnd,CPoint point)
{
   if ( m_EventSink )
   {
      return m_EventSink->OnContextMenu(m_pParent,pWnd,point);
   }
   else
   {
      return false;
   }
}

void CDisplayObjectDefaultImpl::Fire_OnSelect()
{
   if ( m_EventSink )
      m_EventSink->OnSelect(m_pParent);
}

void CDisplayObjectDefaultImpl::Fire_OnUnselect()
{
   if ( m_EventSink )
      m_EventSink->OnUnselect(m_pParent);
}

void CDisplayObjectDefaultImpl::Do_SetID(IDType id)
{
   m_ID = id;
}

IDType CDisplayObjectDefaultImpl::Do_GetID()
{
   return m_ID;
}

void CDisplayObjectDefaultImpl::Do_SetItemData(void* pVoid,bool bDelete)
{
   if ( m_pItemData && m_bDeleteItemData )
   {
      delete m_pItemData;
      m_pItemData = NULL;
   }

   m_pItemData = pVoid;
   m_bDeleteItemData = bDelete;
}

void CDisplayObjectDefaultImpl::Do_GetItemData(void** ppVoid)
{
   (*ppVoid) = m_pItemData;
}

void CDisplayObjectDefaultImpl::Do_Visible(BOOL bVisible)
{
   BOOL bRedraw = (m_bIsVisible != bVisible);
   m_bIsVisible = bVisible;

   if ( bRedraw && m_pDispList != NULL )
   {
      CComPtr<iDisplayMgr> pDispMgr;
      m_pDispList->GetDisplayMgr(&pDispMgr);
      CRect box = m_pParent->GetBoundingBox();
      box.InflateRect(1,1);
      pDispMgr->InvalidateRect(box);
   }
}

BOOL CDisplayObjectDefaultImpl::Do_IsVisible()
{
   return m_bIsVisible;
}

#if defined(_DEBUG)
void CDisplayObjectDefaultImpl::Do_DrawGravityWell(CDC* pDC)
{
   // Draw gravity well for selected objects only
//   if ( !m_pParent->IsSelected() )
//      return;

   CComPtr<iGravityWellStrategy> strategy;
   m_pParent->GetGravityWellStrategy(&strategy);

   COLORREF color = RGB(255,200,200);

   CBrush fillBrush;
   fillBrush.CreateHatchBrush(HS_DIAGCROSS,color);

   CBrush frameBrush;
   frameBrush.CreateSolidBrush(color);
   if ( strategy )
   {
      CRgn rgn;
      strategy->GetGravityWell(m_pParent,&rgn);
      pDC->FrameRgn(&rgn,&frameBrush,2,2);
      pDC->FillRgn(&rgn,&fillBrush);
   }
   else
   {
      CRect box = m_pParent->GetBoundingBox();
      pDC->FrameRect(&box,&frameBrush);
      pDC->FillRect(&box,&fillBrush);
   }
}
#endif

void CDisplayObjectDefaultImpl::Do_SetDisplayList(iDisplayList * pDL)
{
   // weak reference
   m_pDispList = pDL;
}

void CDisplayObjectDefaultImpl::Do_GetDisplayList(iDisplayList** list)
{
   (*list) = m_pDispList;
   if ( *list )
      (*list)->AddRef();
}

void CDisplayObjectDefaultImpl::Do_SetGravityWellStrategy(iGravityWellStrategy* pStrategy)
{
   m_pGravityWellStrategy = pStrategy;
}

void CDisplayObjectDefaultImpl::Do_GetGravityWellStrategy(iGravityWellStrategy** pStrategy)
{
   (*pStrategy) = m_pGravityWellStrategy;
   if ( *pStrategy )
      (*pStrategy)->AddRef();
}

BOOL CDisplayObjectDefaultImpl::Do_HitTest(CPoint point)
{
   if ( m_pGravityWellStrategy )
   {
      CRgn rgn;
      m_pGravityWellStrategy->GetGravityWell(m_pParent,&rgn);
      if ( rgn.m_hObject != NULL )
         return rgn.PtInRegion(point);
      else
         return FALSE;
   }
   else
   {
      CRect box = m_pParent->GetBoundingBox();
      return box.PtInRect(point);
   }

   return FALSE;
}

BOOL CDisplayObjectDefaultImpl::Do_TouchesRect(CRect r)
{
   CRect box = m_pParent->GetBoundingBox();
   return ( (box.left < r.right && r.left < box.right) &&
      (box.bottom > r.top && r.bottom > box.top) ) ? TRUE : FALSE;
}

CRect CDisplayObjectDefaultImpl::Do_GetBoundingBox()
{
   // In leiu of an implementation supplied by the parent object,
   // get the bounding box in world coordinates and map to
   // logical coordinates.

   CComPtr<IRect2d> box;
   m_pParent->GetBoundingBox(&box);
   Float64 wl, wr, wt, wb;
   box->get_Left(&wl);
   box->get_Right(&wr);
   box->get_Top(&wt);
   box->get_Bottom(&wb);

   CComPtr<iDisplayMgr> pDispMgr;
   m_pDispList->GetDisplayMgr(&pDispMgr);

   CComPtr<iCoordinateMap> map;
   pDispMgr->GetCoordinateMap(&map);

   LONG l,r,t,b;
   map->WPtoLP(wl, wt, &l, &t);
   map->WPtoLP(wr, wb, &r, &b);

   CRect rect(l,t,r,b);
   rect.NormalizeRect();
   return rect;
}

void CDisplayObjectDefaultImpl::Do_Select(BOOL bSelect)
{
   // If the display object cannot be selected, just get the heck outta here
   if ( m_SelectionType == stNone )
      return;

   if ( m_bSelected == bSelect )
      return;

   m_bSelected = bSelect;
   
   if ( m_bSelected )
      Fire_OnSelect();
   else
      Fire_OnUnselect();

   CComPtr<iDisplayMgr> pDispMgr;
   m_pDispList->GetDisplayMgr(&pDispMgr);

// selecting the gravity well region tends to leave stray marks when an object is
// unselected. For this reason, I've changed this to use only the bounding box
// RAB 2/1/08
//
//   CComPtr<iGravityWellStrategy> gravityWellStrategy;
//   m_pParent->GetGravityWellStrategy(&gravityWellStrategy);
//   if ( gravityWellStrategy )
//   {
//      CRgn rgnGravityWell;
//      gravityWellStrategy->GetGravityWell(m_pParent,&rgnGravityWell);
//      pDispMgr->InvalidateRgn(&rgnGravityWell);
//   }
//   else
//   {
      CRect box = m_pParent->GetBoundingBox();
      box.InflateRect(1,1); // inflate a bit for tolerancing
      pDispMgr->InvalidateRect(box);
//   }
}

BOOL CDisplayObjectDefaultImpl::Do_IsSelected()
{
   return m_bSelected;
}

void CDisplayObjectDefaultImpl::Do_SetSelectionType(SelectionType st)
{
   m_SelectionType = st;
}

SelectionType CDisplayObjectDefaultImpl::Do_GetSelectionType()
{
   return m_SelectionType;
}

bool CDisplayObjectDefaultImpl::Do_OnLButtonDblClk(UINT nFlags,CPoint point)
{
   return Fire_OnLButtonDblClk(nFlags,point);
}

bool CDisplayObjectDefaultImpl::Do_OnLButtonDown(UINT nFlags,CPoint point)
{
   return Fire_OnLButtonDown(nFlags,point);
}

bool CDisplayObjectDefaultImpl::Do_OnLButtonUp(UINT nFlags,CPoint point)
{
   return Fire_OnLButtonUp(nFlags,point);
}

bool CDisplayObjectDefaultImpl::Do_OnRButtonDown(UINT nFlags,CPoint point)
{
   return Fire_OnRButtonDown(nFlags,point);
}

bool CDisplayObjectDefaultImpl::Do_OnRButtonUp(UINT nFlags,CPoint point)
{
   return Fire_OnRButtonUp(nFlags,point);
}

bool CDisplayObjectDefaultImpl::Do_OnRButtonDblClk(UINT nFlags,CPoint point)
{
   return Fire_OnRButtonDblClk(nFlags,point);
}

bool CDisplayObjectDefaultImpl::Do_OnMouseMove(UINT nFlags,CPoint point)
{
   return Fire_OnMouseMove(nFlags,point);
}

bool CDisplayObjectDefaultImpl::Do_OnMouseWheel(UINT nFlags,short zDelta,CPoint point)
{
   return Fire_OnMouseWheel(nFlags,zDelta,point);
}

bool CDisplayObjectDefaultImpl::Do_OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
   return Fire_OnKeyDown(nChar,nRepCnt,nFlags);
}

bool CDisplayObjectDefaultImpl::Do_OnContextMenu(CWnd* pWnd,CPoint point)
{
   return Fire_OnContextMenu(pWnd,point);
}

void CDisplayObjectDefaultImpl::Do_SetToolTipText(LPCTSTR lpszToolTipText)
{
   m_strToolTipText = lpszToolTipText;
}

CString CDisplayObjectDefaultImpl::Do_GetToolTipText()
{
   return m_strToolTipText;
}

void CDisplayObjectDefaultImpl::Do_SetMaxTipWidth(INT maxWidth)
{
   m_MaxToolTipWidth = maxWidth;
}

INT CDisplayObjectDefaultImpl::Do_GetMaxTipWidth()
{
   return m_MaxToolTipWidth;
}

void CDisplayObjectDefaultImpl::Do_SetTipDisplayTime(INT iTime)
{
   m_ToolTipDisplayTime = iTime;
}

INT CDisplayObjectDefaultImpl::Do_GetTipDisplayTime()
{
   return m_ToolTipDisplayTime;
}

void CDisplayObjectDefaultImpl::Do_RegisterEventSink(iDisplayObjectEvents* pEventSink)
{
   m_EventSink = pEventSink;
}

void CDisplayObjectDefaultImpl::Do_UnregisterEventSink()
{
   m_EventSink = 0;
}

void CDisplayObjectDefaultImpl::Do_GetEventSink(iDisplayObjectEvents** pEventSink)
{
   if ( pEventSink == NULL )
      return;

   (*pEventSink) = m_EventSink;
   (*pEventSink)->AddRef();
}

void CDisplayObjectDefaultImpl::Do_SetDropSite(iDropSite* pDropSite)
{
   m_pDropSite = pDropSite;
   m_pDropSite->SetDisplayObject(m_pParent);
}

void CDisplayObjectDefaultImpl::Do_GetDropSite(iDropSite** dropSite)
{
   (*dropSite) = m_pDropSite;

   if ( *dropSite )
      (*dropSite)->AddRef();
}
