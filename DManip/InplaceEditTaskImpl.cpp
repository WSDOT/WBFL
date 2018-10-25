///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2017  Washington State Department of Transportation
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

// InplaceEditTaskImpl.cpp: implementation of the CInplaceEditTaskImpl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <WBFLDManip.h>
#include <DManip\DManip.h>
#include "InplaceEditTaskImpl.h"

#include <DManip\DisplayView.h>
#include <DManip\InplaceEdit.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define IDC_EDIT 100

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CInplaceEditTaskImpl::CInplaceEditTaskImpl()
{
}

CInplaceEditTaskImpl::~CInplaceEditTaskImpl()
{
}

void CInplaceEditTaskImpl::Init(CDisplayView* pView,iInplaceEditable* pEditable)
{
   m_pView = pView;
   m_pView->SetCapture();
   m_pEditable = pEditable;
}

STDMETHODIMP_(void) CInplaceEditTaskImpl::Start()
{
   Do();
}

STDMETHODIMP_(void) CInplaceEditTaskImpl::OnLButtonUp(UINT nFlags,const CPoint& point)
{
   // Do nothing
}

STDMETHODIMP_(void) CInplaceEditTaskImpl::OnRButtonUp(UINT nFlags,const CPoint& point)
{
   // Do nothing
}

STDMETHODIMP_(void) CInplaceEditTaskImpl::OnMouseMove(UINT nFlags, const CPoint& point)
{
   // Do nothing
}

STDMETHODIMP_(void) CInplaceEditTaskImpl::OnMouseWheel(UINT nFlags, short zDelta, const CPoint& point)
{
   // Do nothing
}

STDMETHODIMP_(void) CInplaceEditTaskImpl::OnLButtonDown(UINT nFlags, const CPoint& point)
{
   LButtonDown();
   CompleteTask(); // Task only ends if in Done state
}

STDMETHODIMP_(void) CInplaceEditTaskImpl::OnRButtonDown(UINT nFlags, const CPoint& point)
{
   // Do nothing
}

STDMETHODIMP_(void) CInplaceEditTaskImpl::OnLButtonDblClk(UINT nFlags,const CPoint& point)
{
   // Do nothing
}

STDMETHODIMP_(void) CInplaceEditTaskImpl::OnRButtonDblClk(UINT nFlags,const CPoint& point)
{
   // Do nothing
}

STDMETHODIMP_(void) CInplaceEditTaskImpl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
   KeyPress(nChar,nRepCnt,nFlags);
   CompleteTask(); // Task only ends if in Done state
}

STDMETHODIMP_(void) CInplaceEditTaskImpl::OnContextMenu(CWnd* pWnd,const CPoint& point)
{
   // Do nothing
}

STDMETHODIMP_(DROPEFFECT) CInplaceEditTaskImpl::OnDragEnter(COleDataObject* pDataObject,DWORD dwKeyState,CPoint point)
{
   return DROPEFFECT_NONE;
}

STDMETHODIMP_(void) CInplaceEditTaskImpl::OnDragLeave()
{
}

STDMETHODIMP_(DROPEFFECT) CInplaceEditTaskImpl::OnDragOver(COleDataObject* pDataObject,DWORD dwKeyState,CPoint point)
{
   return DROPEFFECT_NONE;
}

STDMETHODIMP_(DROPEFFECT) CInplaceEditTaskImpl::OnDragScroll(DWORD dwKeyState,CPoint point)
{
   return DROPEFFECT_NONE;
}

STDMETHODIMP_(BOOL) CInplaceEditTaskImpl::OnDrop(COleDataObject* pDataObject,DROPEFFECT dropEffect,CPoint point)
{
   return FALSE;
}

STDMETHODIMP_(DROPEFFECT) CInplaceEditTaskImpl::OnDropEx(COleDataObject* pDataObject,DROPEFFECT dropEffect,DROPEFFECT dropList,CPoint point)
{
   return DROPEFFECT_NONE;
}

STDMETHODIMP_(void) CInplaceEditTaskImpl::FSMError(LPCTSTR t,LPCTSTR s)
{
   ASSERT(FALSE);
}

STDMETHODIMP_(void) CInplaceEditTaskImpl::InitTask()
{
   m_pEditable->CreateEditControl();
}

STDMETHODIMP_(BOOL) CInplaceEditTaskImpl::ValidateData()
{
   return m_pEditable->ValidateData();
}

STDMETHODIMP_(void) CInplaceEditTaskImpl::NotifyEditable()
{
   m_pEditable->OnDataChanged();
}

void CInplaceEditTaskImpl::CompleteTask()
{
   if ( CompareStates(CInplaceEditFSM::Cancelled) || CompareStates(CInplaceEditFSM::Done) )
   {
      ReleaseCapture();

      m_pEditable->DestroyEditControl();

      CDManipClientDC dc(m_pView);

      CComQIPtr<iDisplayObject,&IID_iDisplayObject> dispObj(m_pEditable);
      CRect box = dispObj->GetBoundingBox();
      m_pView->InvalidateRect(box);

      if ( CompareStates(CInplaceEditFSM::Done) )
         m_pEditable->OnDataChanged();

      CComPtr<iDisplayMgr> pDispMgr;
      m_pView->GetDisplayMgr(&pDispMgr);
      pDispMgr->SetTask(nullptr);
   }
}