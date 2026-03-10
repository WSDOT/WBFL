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
#include "resource.h"
#include "ZoomRectTaskImpl.h"

using namespace WBFL::DManip;

ZoomRectTask::ZoomRectTask()
{
   m_pTrackPen = nullptr;
   m_Cursor = nullptr;
}

ZoomRectTask::ZoomRectTask(CDisplayView* pView, HCURSOR hCursor, COLORREF color)
{
   m_pView = pView;
   m_Cursor = hCursor;
   m_pTrackPen = new CPen(PS_SOLID, 1, color);
}

ZoomRectTask::~ZoomRectTask()
{
   delete m_pTrackPen;
}

void ZoomRectTask::Start()
{
   AFX_MANAGE_STATE(AfxGetStaticModuleState());

   m_pView->SetCapture();
   if ( m_Cursor == nullptr )
      m_Cursor = AfxGetApp()->LoadCursor(IDC_MAGNIFY);

   m_OldCursor = ::SetCursor(m_Cursor);

   Do();
}

void ZoomRectTask::OnLButtonUp(UINT nFlags,const CPoint& point)
{
   m_TempPoint = point;

   MouseUp();

   m_pView->GetDisplayMgr()->SetTask(nullptr);
}

void ZoomRectTask::OnRButtonUp(UINT nFlags,const CPoint& point)
{
   // Do nothing
}

void ZoomRectTask::OnMouseMove(UINT nFlags, const CPoint& point)
{
   m_TempPoint = point;

   MouseMove();
}

void ZoomRectTask::OnMouseWheel(UINT nFlags, short zDelta, const CPoint& point)
{
   // Do nothing
}

void ZoomRectTask::OnLButtonDown(UINT nFlags, const CPoint& point)
{
   m_TempPoint = point;

   MouseDown();
}

void ZoomRectTask::OnRButtonDown(UINT nFlags, const CPoint& point)
{
   // Do nothing
}

void ZoomRectTask::OnLButtonDblClk(UINT nFlags,const CPoint& point)
{
   // Do nothing
}

void ZoomRectTask::OnRButtonDblClk(UINT nFlags,const CPoint& point)
{
   // Do nothing
}

void ZoomRectTask::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
   if ( nChar == VK_ESCAPE )
   {
      EscKey();
      m_pView->GetDisplayMgr()->SetTask(nullptr);
   }
}

void ZoomRectTask::OnContextMenu(CWnd* pWnd,const CPoint& point)
{
   // Do nothing
}

DROPEFFECT ZoomRectTask::OnDragEnter(COleDataObject* pDataObject,DWORD dwKeyState,CPoint point)
{
   // Do nothing
   return DROPEFFECT_NONE;
}

void ZoomRectTask::OnDragLeave()
{
   // Do nothing
}

DROPEFFECT ZoomRectTask::OnDragOver(COleDataObject* pDataObject,DWORD dwKeyState,CPoint point)
{
   // Do nothing
   return DROPEFFECT_NONE;
}

DROPEFFECT ZoomRectTask::OnDragScroll(DWORD dwKeyState,CPoint point)
{
   // Do nothing
   return DROPEFFECT_NONE;
}

BOOL ZoomRectTask::OnDrop(COleDataObject* pDataObject,DROPEFFECT dropEffect,CPoint point)
{
   // Do nothing
   return FALSE;
}

DROPEFFECT ZoomRectTask::OnDropEx(COleDataObject* pDataObject,DROPEFFECT dropEffect,DROPEFFECT dropList,CPoint point)
{
   // Do nothing
   return DROPEFFECT_NONE;
}

void ZoomRectTask::ZoomRect()
{
   // TODO
   ClearRect();
   ReleaseCapture();
   SetCursor(m_OldCursor);

   m_pView->Zoom(CRect(m_FirstPoint,m_SecondPoint));
}

void ZoomRectTask::RecordFirstPoint()
{
   m_FirstPoint = m_SecondPoint = m_TempPoint;
}

void ZoomRectTask::ClearRect()
{
   if ( m_pView->GetCapture() == m_pView )
   {
      DrawRect(m_FirstPoint,m_SecondPoint);
   }
}

void ZoomRectTask::TrackRect()
{
   if ( m_pView->GetCapture() == m_pView )
   {
      DrawRect(m_FirstPoint,m_SecondPoint);
      DrawRect(m_FirstPoint,m_TempPoint);
      m_SecondPoint = m_TempPoint;
   }
}

void ZoomRectTask::FSMError(LPCTSTR t,LPCTSTR s)
{
   ASSERT(FALSE);
}

void ZoomRectTask::InitTask()
{
}

void ZoomRectTask::Cancel()
{
   ClearRect();
   ReleaseCapture();
   SetCursor(m_OldCursor);
}


void ZoomRectTask::DrawRect(CPoint& from,CPoint& to)
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
