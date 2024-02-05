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
#include "InplaceEditTaskImpl.h"
#include <DManip/DisplayView.h>
#include <DManip/DisplayObject.h>
#include <DManip/DisplayMgr.h>

#define IDC_EDIT 100

using namespace WBFL::DManip;

InplaceEditTask::InplaceEditTask(CDisplayView* pView,std::shared_ptr<iInplaceEditable> pEditable)
{
   m_pView = pView;
   m_pView->SetCapture();
   m_pEditable = pEditable;
}

void InplaceEditTask::Start()
{
   Do();
}

void InplaceEditTask::OnLButtonUp(UINT nFlags,const CPoint& point)
{
   // Do nothing
}

void InplaceEditTask::OnRButtonUp(UINT nFlags,const CPoint& point)
{
   // Do nothing
}

void InplaceEditTask::OnMouseMove(UINT nFlags, const CPoint& point)
{
   // Do nothing
}

void InplaceEditTask::OnMouseWheel(UINT nFlags, short zDelta, const CPoint& point)
{
   // Do nothing
}

void InplaceEditTask::OnLButtonDown(UINT nFlags, const CPoint& point)
{
   LButtonDown();
   CompleteTask(); // Task only ends if in Done state
}

void InplaceEditTask::OnRButtonDown(UINT nFlags, const CPoint& point)
{
   // Do nothing
}

void InplaceEditTask::OnLButtonDblClk(UINT nFlags,const CPoint& point)
{
   // Do nothing
}

void InplaceEditTask::OnRButtonDblClk(UINT nFlags,const CPoint& point)
{
   // Do nothing
}

void InplaceEditTask::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
   KeyPress(nChar,nRepCnt,nFlags);
   CompleteTask(); // Task only ends if in Done state
}

void InplaceEditTask::OnContextMenu(CWnd* pWnd,const CPoint& point)
{
   // Do nothing
}

DROPEFFECT InplaceEditTask::OnDragEnter(COleDataObject* pDataObject,DWORD dwKeyState,CPoint point)
{
   return DROPEFFECT_NONE;
}

void InplaceEditTask::OnDragLeave()
{
}

DROPEFFECT InplaceEditTask::OnDragOver(COleDataObject* pDataObject,DWORD dwKeyState,CPoint point)
{
   return DROPEFFECT_NONE;
}

DROPEFFECT InplaceEditTask::OnDragScroll(DWORD dwKeyState,CPoint point)
{
   return DROPEFFECT_NONE;
}

BOOL InplaceEditTask::OnDrop(COleDataObject* pDataObject,DROPEFFECT dropEffect,CPoint point)
{
   return FALSE;
}

DROPEFFECT InplaceEditTask::OnDropEx(COleDataObject* pDataObject,DROPEFFECT dropEffect,DROPEFFECT dropList,CPoint point)
{
   return DROPEFFECT_NONE;
}

void InplaceEditTask::FSMError(LPCTSTR t,LPCTSTR s)
{
   ASSERT(FALSE);
}

void InplaceEditTask::InitTask()
{
   m_pEditable->CreateEditControl();
}

BOOL InplaceEditTask::ValidateData()
{
   return m_pEditable->ValidateData();
}

void InplaceEditTask::NotifyEditable()
{
   m_pEditable->OnDataChanged();
}

void InplaceEditTask::CompleteTask()
{
   if ( CompareStates(InplaceEditFSM::Cancelled) || CompareStates(InplaceEditFSM::Done) )
   {
      ReleaseCapture();

      m_pEditable->DestroyEditControl();

      CDManipClientDC dc(m_pView);

      auto disp_obj = std::dynamic_pointer_cast<iDisplayObject>(m_pEditable);
      auto box = disp_obj->GetLogicalBoundingBox();
      m_pView->InvalidateRect(&box);

      if ( CompareStates(InplaceEditFSM::Done) )
         m_pEditable->OnDataChanged();

      m_pEditable->EndInplaceEdit();
   }
}