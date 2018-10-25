///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2011  Washington State Department of Transportation
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

// ZoomRectTaskImpl.cpp: implementation of the CZoomRectTaskImpl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <WBFLDManip.h>
#include <DManip\DManip.h>
#include "ZoomRectTaskImpl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CZoomRectTaskImpl::CZoomRectTaskImpl()
{
   m_pTrackPen = NULL;
   m_Cursor = NULL;
}

CZoomRectTaskImpl::~CZoomRectTaskImpl()
{
   delete m_pTrackPen;
}

void CZoomRectTaskImpl::Init(CDisplayView* pView,HCURSOR hCursor,COLORREF color)
{
   m_pView = pView;
   m_Cursor = hCursor;
   m_pTrackPen = new CPen(PS_SOLID,1,color);
}

STDMETHODIMP_(void) CZoomRectTaskImpl::Start()
{
   AFX_MANAGE_STATE(AfxGetStaticModuleState());

   m_pView->SetCapture();
   if ( m_Cursor == NULL )
      m_Cursor = AfxGetApp()->LoadCursor(IDC_MAGNIFY);

   m_OldCursor = ::SetCursor(m_Cursor);

   Do();
}

STDMETHODIMP_(void) CZoomRectTaskImpl::OnLButtonUp(UINT nFlags,const CPoint& point)
{
   m_TempPoint = point;

   MouseUp();

   CComPtr<iDisplayMgr> pDispMgr;
   m_pView->GetDisplayMgr(&pDispMgr);
   pDispMgr->SetTask(NULL);
}

STDMETHODIMP_(void) CZoomRectTaskImpl::OnRButtonUp(UINT nFlags,const CPoint& point)
{
   // Do nothing
}

STDMETHODIMP_(void) CZoomRectTaskImpl::OnMouseMove(UINT nFlags, const CPoint& point)
{
   m_TempPoint = point;

   MouseMove();
}

STDMETHODIMP_(void) CZoomRectTaskImpl::OnMouseWheel(UINT nFlags, short zDelta, const CPoint& point)
{
   // Do nothing
}

STDMETHODIMP_(void) CZoomRectTaskImpl::OnLButtonDown(UINT nFlags, const CPoint& point)
{
   m_TempPoint = point;

   MouseDown();
}

STDMETHODIMP_(void) CZoomRectTaskImpl::OnRButtonDown(UINT nFlags, const CPoint& point)
{
   // Do nothing
}

STDMETHODIMP_(void) CZoomRectTaskImpl::OnLButtonDblClk(UINT nFlags,const CPoint& point)
{
   // Do nothing
}

STDMETHODIMP_(void) CZoomRectTaskImpl::OnRButtonDblClk(UINT nFlags,const CPoint& point)
{
   // Do nothing
}

STDMETHODIMP_(void) CZoomRectTaskImpl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
   if ( nChar == VK_ESCAPE )
   {
      EscKey();
      CComPtr<iDisplayMgr> pDispMgr;
      m_pView->GetDisplayMgr(&pDispMgr);
      pDispMgr->SetTask(NULL);
   }
}

STDMETHODIMP_(void) CZoomRectTaskImpl::OnContextMenu(CWnd* pWnd,const CPoint& point)
{
   // Do nothing
}

STDMETHODIMP_(DROPEFFECT) CZoomRectTaskImpl::OnDragEnter(COleDataObject* pDataObject,DWORD dwKeyState,CPoint point)
{
   // Do nothing
   return DROPEFFECT_NONE;
}

STDMETHODIMP_(void) CZoomRectTaskImpl::OnDragLeave()
{
   // Do nothing
}

STDMETHODIMP_(DROPEFFECT) CZoomRectTaskImpl::OnDragOver(COleDataObject* pDataObject,DWORD dwKeyState,CPoint point)
{
   // Do nothing
   return DROPEFFECT_NONE;
}

STDMETHODIMP_(DROPEFFECT) CZoomRectTaskImpl::OnDragScroll(DWORD dwKeyState,CPoint point)
{
   // Do nothing
   return DROPEFFECT_NONE;
}

STDMETHODIMP_(BOOL) CZoomRectTaskImpl::OnDrop(COleDataObject* pDataObject,DROPEFFECT dropEffect,CPoint point)
{
   // Do nothing
   return FALSE;
}

STDMETHODIMP_(DROPEFFECT) CZoomRectTaskImpl::OnDropEx(COleDataObject* pDataObject,DROPEFFECT dropEffect,DROPEFFECT dropList,CPoint point)
{
   // Do nothing
   return DROPEFFECT_NONE;
}

STDMETHODIMP_(void) CZoomRectTaskImpl::ZoomRect()
{
   // TODO
   ClearRect();
   ReleaseCapture();
   SetCursor(m_OldCursor);

   m_pView->Zoom(CRect(m_FirstPoint,m_SecondPoint));
}

STDMETHODIMP_(void) CZoomRectTaskImpl::RecordFirstPoint()
{
   m_FirstPoint = m_SecondPoint = m_TempPoint;
}

STDMETHODIMP_(void) CZoomRectTaskImpl::ClearRect()
{
   if ( m_pView->GetCapture() == m_pView )
   {
      DrawRect(m_FirstPoint,m_SecondPoint);
   }
}

STDMETHODIMP_(void) CZoomRectTaskImpl::TrackRect()
{
   if ( m_pView->GetCapture() == m_pView )
   {
      DrawRect(m_FirstPoint,m_SecondPoint);
      DrawRect(m_FirstPoint,m_TempPoint);
      m_SecondPoint = m_TempPoint;
   }
}

STDMETHODIMP_(void) CZoomRectTaskImpl::FSMError(LPCTSTR t,LPCTSTR s)
{
   ASSERT(FALSE);
}

STDMETHODIMP_(void) CZoomRectTaskImpl::InitTask()
{
}

STDMETHODIMP_(void) CZoomRectTaskImpl::Cancel()
{
   ClearRect();
   ReleaseCapture();
   SetCursor(m_OldCursor);
}


void CZoomRectTaskImpl::DrawRect(CPoint& from,CPoint& to)
{
   CDManipClientDC dc(m_pView);

   // setup dc
   int rop = dc.SetROP2(R2_XORPEN);
   CPen* oldPen = dc.SelectObject(m_pTrackPen);
   CGdiObject* oldBrush = dc.SelectStockObject(NULL_BRUSH);

   CRect rect(from,to);
   rect.NormalizeRect();
   dc.Rectangle(rect);

   // Clean up
   dc.SetROP2(rop);
   dc.SelectObject(oldPen);
   dc.SelectObject(oldBrush);
}
