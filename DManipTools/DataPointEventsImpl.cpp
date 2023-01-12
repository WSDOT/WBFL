///////////////////////////////////////////////////////////////////////
// DManipTools - Direct Manipulation Tools
// Copyright © 1999-2023  Washington State Department of Transportation
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

// DataPointEventsImpl.cpp : implementation file
//

#include "stdafx.h"
#include "DataPointEventsImpl.h"
#include "mfcdual.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

UINT CDataPointEventsImpl::ms_Format = ::RegisterClipboardFormat(_T("DataPointData"));

/////////////////////////////////////////////////////////////////////////////
// CDataPointEventsImpl
CDataPointEventsImpl::CDataPointEventsImpl()
{
}

CDataPointEventsImpl::~CDataPointEventsImpl()
{
}

BEGIN_INTERFACE_MAP(CDataPointEventsImpl,CCmdTarget)
   INTERFACE_PART(CDataPointEventsImpl,IID_iDataPointEvents,Events)
   INTERFACE_PART(CDataPointEventsImpl,IID_iDisplayObjectEvents,DisplayObjectEvents)
//   INTERFACE_PART(CDataPointEventsImpl,IID_iDragData,DragData)
END_INTERFACE_MAP()

DELEGATE_CUSTOM_INTERFACE(CDataPointEventsImpl,Events);
DELEGATE_CUSTOM_INTERFACE(CDataPointEventsImpl,DisplayObjectEvents);
//DELEGATE_CUSTOM_INTERFACE(CDataPointEventsImpl,DragData);

STDMETHODIMP_(void) CDataPointEventsImpl::XDisplayObjectEvents::OnChanged(iDisplayObject* pDO)
{
}

STDMETHODIMP_(void) CDataPointEventsImpl::XDisplayObjectEvents::OnDragMoved(iDisplayObject* pDO,ISize2d* offset)
{
   ASSERT(FALSE); // Points must be dropped on a member. This event should never occur
}

STDMETHODIMP_(void) CDataPointEventsImpl::XDisplayObjectEvents::OnMoved(iDisplayObject* pDO)
{
   METHOD_PROLOGUE(CDataPointEventsImpl,DisplayObjectEvents);

}

STDMETHODIMP_(void) CDataPointEventsImpl::XDisplayObjectEvents::OnCopied(iDisplayObject* pDO)
{
   // No big deal...
}

STDMETHODIMP_(bool) CDataPointEventsImpl::XDisplayObjectEvents::OnLButtonDblClk(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
   METHOD_PROLOGUE(CDataPointEventsImpl,DisplayObjectEvents);
   return false;
}

STDMETHODIMP_(bool) CDataPointEventsImpl::XDisplayObjectEvents::OnLButtonDown(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
   CComPtr<iDisplayList> list;
   pDO->GetDisplayList(&list);

   CComPtr<iDisplayMgr> dispMgr;
   list->GetDisplayMgr(&dispMgr);

   // If control key is pressed, don't clear current selection
   // (i.e. we want multi-select)
   BOOL bMultiSelect = nFlags & MK_CONTROL ? TRUE : FALSE;
   
   if ( bMultiSelect )
   {
      // clear all selected objects that aren't part of the load list
//      dispMgr->ClearSelectedObjectsByList(LOAD_LIST,atByID,FALSE);
   }

   dispMgr->SelectObject(pDO,!bMultiSelect);
/*
   // d&d task
   CComPtr<iTaskFactory> factory;
   dispMgr->GetTaskFactory(&factory);
   CComPtr<iTask> task;
   factory->CreateLocalDragDropTask(dispMgr,point,&task);
   dispMgr->SetTask(task);
*/
   return true;
}

STDMETHODIMP_(bool) CDataPointEventsImpl::XDisplayObjectEvents::OnRButtonDblClk(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
   METHOD_PROLOGUE(CDataPointEventsImpl,DisplayObjectEvents);
   return false;
}

STDMETHODIMP_(bool) CDataPointEventsImpl::XDisplayObjectEvents::OnRButtonUp(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
   METHOD_PROLOGUE(CDataPointEventsImpl,DisplayObjectEvents);
   return false;
}

STDMETHODIMP_(bool) CDataPointEventsImpl::XDisplayObjectEvents::OnLButtonUp(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
   METHOD_PROLOGUE(CDataPointEventsImpl,DisplayObjectEvents);
   return false;
}

STDMETHODIMP_(bool) CDataPointEventsImpl::XDisplayObjectEvents::OnRButtonDown(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
   METHOD_PROLOGUE(CDataPointEventsImpl,DisplayObjectEvents);
   return false;
}

STDMETHODIMP_(bool) CDataPointEventsImpl::XDisplayObjectEvents::OnMouseMove(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
   METHOD_PROLOGUE(CDataPointEventsImpl,DisplayObjectEvents);
   return false;
}

STDMETHODIMP_(bool) CDataPointEventsImpl::XDisplayObjectEvents::OnMouseWheel(iDisplayObject* pDO,UINT nFlags,short zDelta,CPoint point)
{
   METHOD_PROLOGUE(CDataPointEventsImpl,DisplayObjectEvents);
   return false;
}

STDMETHODIMP_(bool) CDataPointEventsImpl::XDisplayObjectEvents::OnKeyDown(iDisplayObject* pDO,UINT nChar, UINT nRepCnt, UINT nFlags)
{
   METHOD_PROLOGUE(CDataPointEventsImpl,DisplayObjectEvents);
   switch(nChar)
   {
   case VK_RETURN:
//         pThis->EditLoad(pThis->m_Loading,pThis->m_ID);
         break;

   case VK_DELETE:
//         pThis->DeleteLoad(pThis->m_Loading,pThis->m_ID);
         break;
   }
   return false;
}

STDMETHODIMP_(bool) CDataPointEventsImpl::XDisplayObjectEvents::OnContextMenu(iDisplayObject* pDO,CWnd* pWnd,CPoint point)
{
   METHOD_PROLOGUE(CDataPointEventsImpl,DisplayObjectEvents);
   return false;
}

STDMETHODIMP_(void) CDataPointEventsImpl::XDisplayObjectEvents::OnSelect(iDisplayObject* pDO)
{
}

STDMETHODIMP_(void) CDataPointEventsImpl::XDisplayObjectEvents::OnUnselect(iDisplayObject* pDO)
{
}
/*
STDMETHODIMP_(UINT) CDataPointEventsImpl::XDragData::Format()
{
   return ms_Format;
}

STDMETHODIMP_(BOOL) CDataPointEventsImpl::XDragData::PrepareForDrag(iDisplayObject* pDO,iDragDataSink* pSink)
{
   METHOD_PROLOGUE(CDataPointEventsImpl,DragData);

   // Create a place to store the drag data for this object
   pSink->CreateFormat(ms_Format);


   return TRUE;
}

STDMETHODIMP_(void) CDataPointEventsImpl::XDragData::OnDrop(iDisplayObject* pDO,iDragDataSource* pSource)
{
   METHOD_PROLOGUE(CDataPointEventsImpl,DragData);

   // Tell the source we are about to read from our format
   pSource->PrepareFormat(ms_Format);


}
*/