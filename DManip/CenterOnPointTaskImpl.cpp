///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2018  Washington State Department of Transportation
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

// CenterOnPointTaskImpl.cpp: implementation of the CCenterOnPointTaskImpl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <WBFLDManip.h>
#include <DManip\DManip.h>
#include "CenterOnPointTaskImpl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCenterOnPointTaskImpl::CCenterOnPointTaskImpl()
{
}

CCenterOnPointTaskImpl::~CCenterOnPointTaskImpl()
{
}

void CCenterOnPointTaskImpl::Init(CDisplayView* pView)
{
   m_pView = pView;
}

STDMETHODIMP_(void) CCenterOnPointTaskImpl::Start()
{
   AFX_MANAGE_STATE(AfxGetStaticModuleState());

   m_pView->SetCapture();
   HCURSOR hCursor = AfxGetApp()->LoadCursor(IDC_TARGET);
   ASSERT(hCursor != nullptr);
   m_OldCursor = ::SetCursor(hCursor);
   Do();
}

STDMETHODIMP_(void) CCenterOnPointTaskImpl::OnLButtonUp(UINT nFlags,const CPoint& point)
{
}

STDMETHODIMP_(void) CCenterOnPointTaskImpl::OnRButtonUp(UINT nFlags,const CPoint& point)
{
   // Do nothing
}

STDMETHODIMP_(void) CCenterOnPointTaskImpl::OnMouseMove(UINT nFlags, const CPoint& point)
{
   // Do nothing
}

STDMETHODIMP_(void) CCenterOnPointTaskImpl::OnMouseWheel(UINT nFlags, short zDelta, const CPoint& point)
{
   // Do nothing
}

STDMETHODIMP_(void) CCenterOnPointTaskImpl::OnLButtonDown(UINT nFlags, const CPoint& point)
{
   m_Point = point;

   MouseDown();

   CComPtr<iDisplayMgr> pDispMgr;
   m_pView->GetDisplayMgr(&pDispMgr);

   pDispMgr->SetTask(nullptr);
}

STDMETHODIMP_(void) CCenterOnPointTaskImpl::OnRButtonDown(UINT nFlags, const CPoint& point)
{
   // Do nothing
}

STDMETHODIMP_(void) CCenterOnPointTaskImpl::OnRButtonDblClk(UINT nFlags,const CPoint& point)
{
   // Do nothing
}

STDMETHODIMP_(void) CCenterOnPointTaskImpl::OnLButtonDblClk(UINT nFlags,const CPoint& point)
{
   // Do nothing
}

STDMETHODIMP_(void) CCenterOnPointTaskImpl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
   if ( nChar == VK_ESCAPE )
   {
      EscKey();
      CComPtr<iDisplayMgr> pDispMgr;
      m_pView->GetDisplayMgr(&pDispMgr);

      pDispMgr->SetTask(nullptr);
   }
}

STDMETHODIMP_(void) CCenterOnPointTaskImpl::OnContextMenu(CWnd* pWnd,const CPoint& point)
{
   // Do nothing
}

STDMETHODIMP_(DROPEFFECT) CCenterOnPointTaskImpl::OnDragEnter(COleDataObject* pDataObject,DWORD dwKeyState,CPoint point)
{
   // Do nothing
   return DROPEFFECT_NONE;
}

STDMETHODIMP_(void) CCenterOnPointTaskImpl::OnDragLeave()
{
   // Do nothing
}

STDMETHODIMP_(DROPEFFECT) CCenterOnPointTaskImpl::OnDragOver(COleDataObject* pDataObject,DWORD dwKeyState,CPoint point)
{
   // Do nothing
   return DROPEFFECT_NONE;
}

STDMETHODIMP_(DROPEFFECT) CCenterOnPointTaskImpl::OnDragScroll(DWORD dwKeyState,CPoint point)
{
   // Do nothing
   return DROPEFFECT_NONE;
}

STDMETHODIMP_(BOOL) CCenterOnPointTaskImpl::OnDrop(COleDataObject* pDataObject,DROPEFFECT dropEffect,CPoint point)
{
   // Do nothing
   return FALSE;
}

STDMETHODIMP_(DROPEFFECT) CCenterOnPointTaskImpl::OnDropEx(COleDataObject* pDataObject,DROPEFFECT dropEffect,DROPEFFECT dropList,CPoint point)
{
   // Do nothing
   return DROPEFFECT_NONE;
}

STDMETHODIMP_(void) CCenterOnPointTaskImpl::CenterOnPoint()
{
   ReleaseCapture();
   SetCursor(m_OldCursor);

   // Ask the view to select objects in the rect
   m_pView->CenterOnPoint(m_Point);
}

STDMETHODIMP_(void) CCenterOnPointTaskImpl::FSMError(LPCTSTR t,LPCTSTR s)
{
   ASSERT(FALSE);
}

STDMETHODIMP_(void) CCenterOnPointTaskImpl::InitTask()
{
}

STDMETHODIMP_(void) CCenterOnPointTaskImpl::Cancel()
{
   ReleaseCapture();
   SetCursor(m_OldCursor);
}