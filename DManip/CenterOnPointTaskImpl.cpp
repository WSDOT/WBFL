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
#include "CenterOnPointTaskImpl.h"
#include <DManip/DisplayView.h>

using namespace WBFL::DManip;

CenterOnPointTask::CenterOnPointTask()
{
}

CenterOnPointTask::CenterOnPointTask(CDisplayView* pView)
{
   m_pView = pView;
}

CenterOnPointTask::~CenterOnPointTask()
{
}

void CenterOnPointTask::Start()
{
   AFX_MANAGE_STATE(AfxGetStaticModuleState());

   m_pView->SetCapture();
   HCURSOR hCursor = AfxGetApp()->LoadCursor(IDC_TARGET);
   ASSERT(hCursor != nullptr);
   m_OldCursor = ::SetCursor(hCursor);
   Do();
}

void CenterOnPointTask::OnLButtonUp(UINT nFlags,const CPoint& point)
{
}

void CenterOnPointTask::OnRButtonUp(UINT nFlags,const CPoint& point)
{
   // Do nothing
}

void CenterOnPointTask::OnMouseMove(UINT nFlags, const CPoint& point)
{
   // Do nothing
}

void CenterOnPointTask::OnMouseWheel(UINT nFlags, short zDelta, const CPoint& point)
{
   // Do nothing
}

void CenterOnPointTask::OnLButtonDown(UINT nFlags, const CPoint& point)
{
   m_Point = point;

   MouseDown();

   m_pView->GetDisplayMgr()->SetTask(nullptr);
}

void CenterOnPointTask::OnRButtonDown(UINT nFlags, const CPoint& point)
{
   // Do nothing
}

void CenterOnPointTask::OnRButtonDblClk(UINT nFlags,const CPoint& point)
{
   // Do nothing
}

void CenterOnPointTask::OnLButtonDblClk(UINT nFlags,const CPoint& point)
{
   // Do nothing
}

void CenterOnPointTask::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
   if ( nChar == VK_ESCAPE )
   {
      EscKey();
      m_pView->GetDisplayMgr()->SetTask(nullptr);
   }
}

void CenterOnPointTask::OnContextMenu(CWnd* pWnd,const CPoint& point)
{
   // Do nothing
}

DROPEFFECT CenterOnPointTask::OnDragEnter(COleDataObject* pDataObject,DWORD dwKeyState,CPoint point)
{
   // Do nothing
   return DROPEFFECT_NONE;
}

void CenterOnPointTask::OnDragLeave()
{
   // Do nothing
}

DROPEFFECT CenterOnPointTask::OnDragOver(COleDataObject* pDataObject,DWORD dwKeyState,CPoint point)
{
   // Do nothing
   return DROPEFFECT_NONE;
}

DROPEFFECT CenterOnPointTask::OnDragScroll(DWORD dwKeyState,CPoint point)
{
   // Do nothing
   return DROPEFFECT_NONE;
}

BOOL CenterOnPointTask::OnDrop(COleDataObject* pDataObject,DROPEFFECT dropEffect,CPoint point)
{
   // Do nothing
   return FALSE;
}

DROPEFFECT CenterOnPointTask::OnDropEx(COleDataObject* pDataObject,DROPEFFECT dropEffect,DROPEFFECT dropList,CPoint point)
{
   // Do nothing
   return DROPEFFECT_NONE;
}

void CenterOnPointTask::CenterOnPoint()
{
   ReleaseCapture();
   SetCursor(m_OldCursor);

   // Ask the view to select objects in the rect
   m_pView->CenterOnPoint(m_Point);
}

void CenterOnPointTask::FSMError(LPCTSTR t,LPCTSTR s)
{
   ASSERT(FALSE);
}

void CenterOnPointTask::InitTask()
{
}

void CenterOnPointTask::Cancel()
{
   ReleaseCapture();
   SetCursor(m_OldCursor);
}