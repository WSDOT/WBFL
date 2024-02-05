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
#include "RectSelectTaskImpl.h"
#include <DManip/DisplayView.h>

using namespace WBFL::DManip;

RectSelectTask::RectSelectTask()
{
}

RectSelectTask::RectSelectTask(std::shared_ptr<iDisplayMgr> pDM, const CPoint& startPoint)
{
   m_pDispMgr = pDM;
   CDisplayView* pView = m_pDispMgr->GetView();

   pView->SetCapture();

   m_FirstPoint = m_SecondPoint = m_TempPoint = startPoint;
}

RectSelectTask::~RectSelectTask()
{
}

void RectSelectTask::Start()
{
   Do();
}

void RectSelectTask::OnLButtonUp(UINT nFlags,const CPoint& point)
{
   m_TempPoint = point;
   MouseUp();
   m_pDispMgr->SetTask(nullptr);
}

void RectSelectTask::OnRButtonUp(UINT nFlags,const CPoint& point)
{
   // Do nothing
}

void RectSelectTask::OnMouseMove(UINT nFlags, const CPoint& point)
{
   m_TempPoint = point;
   MouseMove();
}

void RectSelectTask::OnMouseWheel(UINT nFlags, short zDelta, const CPoint& point)
{
   // Do nothing
}

void RectSelectTask::OnLButtonDown(UINT nFlags, const CPoint& point)
{
   m_TempPoint = point;
   MouseDown();
}

void RectSelectTask::OnRButtonDown(UINT nFlags, const CPoint& point)
{
   // Do nothing
}

void RectSelectTask::OnLButtonDblClk(UINT nFlags,const CPoint& point)
{
   // Do nothing
}

void RectSelectTask::OnRButtonDblClk(UINT nFlags,const CPoint& point)
{
   // Do nothing
}

void RectSelectTask::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
   KeyPress(nChar,nRepCnt,nFlags);

   if ( CompareStates(RectSelectFSM::Done) )
      m_pDispMgr->SetTask(nullptr);
}

void RectSelectTask::OnContextMenu(CWnd* pWnd,const CPoint& point)
{
   // Do nothing
}

DROPEFFECT RectSelectTask::OnDragEnter(COleDataObject* pDataObject,DWORD dwKeyState,CPoint point)
{
   return DROPEFFECT_NONE;
}

void RectSelectTask::OnDragLeave()
{
}

DROPEFFECT RectSelectTask::OnDragOver(COleDataObject* pDataObject,DWORD dwKeyState,CPoint point)
{
   return DROPEFFECT_NONE;
}

DROPEFFECT RectSelectTask::OnDragScroll(DWORD dwKeyState,CPoint point)
{
   return DROPEFFECT_NONE;
}

BOOL RectSelectTask::OnDrop(COleDataObject* pDataObject,DROPEFFECT dropEffect,CPoint point)
{
   return FALSE;
}

DROPEFFECT RectSelectTask::OnDropEx(COleDataObject* pDataObject,DROPEFFECT dropEffect,DROPEFFECT dropList,CPoint point)
{
   return DROPEFFECT_NONE;
}

void RectSelectTask::SelectObjects()
{
   // TODO
   ClearRect();
   ReleaseCapture();

   // Select objects in the rect
   CRect rect(m_FirstPoint,m_SecondPoint);
   rect.NormalizeRect();
   m_pDispMgr->SelectObjects(rect);
}

void RectSelectTask::ClearRect()
{
   CDisplayView* pView = m_pDispMgr->GetView();

   if ( pView->GetCapture() == pView )
   {
      CDManipClientDC dc(pView);

      CRect rect(m_FirstPoint,m_SecondPoint);
      rect.NormalizeRect();
      dc.DrawFocusRect(rect);
   }
}

void RectSelectTask::TrackRect()
{
   CDisplayView* pView = m_pDispMgr->GetView();

   if ( pView->GetCapture() == pView )
   {
      CDManipClientDC dc(pView);

      // draw the previous rect
      CRect rect1(m_FirstPoint,m_SecondPoint);
      rect1.NormalizeRect();
      dc.DrawFocusRect(rect1);

      // draw the current rect
      CRect rect2(m_FirstPoint,m_TempPoint);
      rect2.NormalizeRect();
      dc.DrawFocusRect(rect2);
      m_SecondPoint = m_TempPoint;
   }
}

void RectSelectTask::FSMError(LPCTSTR t,LPCTSTR s)
{
   ASSERT(FALSE);
}

void RectSelectTask::Cancel()
{
   ClearRect();
}

void RectSelectTask::InitTask()
{
}
