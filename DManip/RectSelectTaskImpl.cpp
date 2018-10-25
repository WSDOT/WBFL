///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2014  Washington State Department of Transportation
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

// RectSelectTaskImpl.cpp: implementation of the CRectSelectTaskImpl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <WBFLDManip.h>
#include <DManip\DManip.h>
#include "RectSelectTaskImpl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRectSelectTaskImpl::CRectSelectTaskImpl()
{
}

CRectSelectTaskImpl::~CRectSelectTaskImpl()
{
}

void CRectSelectTaskImpl::Init(iDisplayMgr* pDM,const CPoint& startPoint)
{
   m_pDispMgr = pDM;
   CDisplayView* pView = m_pDispMgr->GetView();

   pView->SetCapture();

   m_FirstPoint = m_SecondPoint = m_TempPoint = startPoint;
}

STDMETHODIMP_(void) CRectSelectTaskImpl::Start()
{
   Do();
}

STDMETHODIMP_(void) CRectSelectTaskImpl::OnLButtonUp(UINT nFlags,const CPoint& point)
{
   m_TempPoint = point;
   MouseUp();
   m_pDispMgr->SetTask(NULL);
}

STDMETHODIMP_(void) CRectSelectTaskImpl::OnRButtonUp(UINT nFlags,const CPoint& point)
{
   // Do nothing
}

STDMETHODIMP_(void) CRectSelectTaskImpl::OnMouseMove(UINT nFlags, const CPoint& point)
{
   m_TempPoint = point;
   MouseMove();
}

STDMETHODIMP_(void) CRectSelectTaskImpl::OnMouseWheel(UINT nFlags, short zDelta, const CPoint& point)
{
   // Do nothing
}

STDMETHODIMP_(void) CRectSelectTaskImpl::OnLButtonDown(UINT nFlags, const CPoint& point)
{
   m_TempPoint = point;
   MouseDown();
}

STDMETHODIMP_(void) CRectSelectTaskImpl::OnRButtonDown(UINT nFlags, const CPoint& point)
{
   // Do nothing
}

STDMETHODIMP_(void) CRectSelectTaskImpl::OnLButtonDblClk(UINT nFlags,const CPoint& point)
{
   // Do nothing
}

STDMETHODIMP_(void) CRectSelectTaskImpl::OnRButtonDblClk(UINT nFlags,const CPoint& point)
{
   // Do nothing
}

STDMETHODIMP_(void) CRectSelectTaskImpl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
   KeyPress(nChar,nRepCnt,nFlags);

   if ( CompareStates(CRectSelectFSM::Done) )
      m_pDispMgr->SetTask(NULL);
}

STDMETHODIMP_(void) CRectSelectTaskImpl::OnContextMenu(CWnd* pWnd,const CPoint& point)
{
   // Do nothing
}

STDMETHODIMP_(DROPEFFECT) CRectSelectTaskImpl::OnDragEnter(COleDataObject* pDataObject,DWORD dwKeyState,CPoint point)
{
   return DROPEFFECT_NONE;
}

STDMETHODIMP_(void) CRectSelectTaskImpl::OnDragLeave()
{
}

STDMETHODIMP_(DROPEFFECT) CRectSelectTaskImpl::OnDragOver(COleDataObject* pDataObject,DWORD dwKeyState,CPoint point)
{
   return DROPEFFECT_NONE;
}

STDMETHODIMP_(DROPEFFECT) CRectSelectTaskImpl::OnDragScroll(DWORD dwKeyState,CPoint point)
{
   return DROPEFFECT_NONE;
}

STDMETHODIMP_(BOOL) CRectSelectTaskImpl::OnDrop(COleDataObject* pDataObject,DROPEFFECT dropEffect,CPoint point)
{
   return FALSE;
}

STDMETHODIMP_(DROPEFFECT) CRectSelectTaskImpl::OnDropEx(COleDataObject* pDataObject,DROPEFFECT dropEffect,DROPEFFECT dropList,CPoint point)
{
   return DROPEFFECT_NONE;
}

STDMETHODIMP_(void) CRectSelectTaskImpl::SelectObjects()
{
   // TODO
   ClearRect();
   ReleaseCapture();

   // Select objects in the rect
   CRect rect(m_FirstPoint,m_SecondPoint);
   rect.NormalizeRect();
   m_pDispMgr->SelectObjects(rect);
}

STDMETHODIMP_(void) CRectSelectTaskImpl::ClearRect()
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

STDMETHODIMP_(void) CRectSelectTaskImpl::TrackRect()
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

STDMETHODIMP_(void) CRectSelectTaskImpl::FSMError(LPCTSTR t,LPCTSTR s)
{
   ASSERT(FALSE);
}

STDMETHODIMP_(void) CRectSelectTaskImpl::Cancel()
{
   ClearRect();
}

STDMETHODIMP_(void) CRectSelectTaskImpl::InitTask()
{
}
