///////////////////////////////////////////////////////////////////////////////
// generic support draw routines to share between Supports and TemporarySupports

#include "stdafx.h"
#include "DataPointEventsImpl.h"

UINT CDataPointEventsImpl::ms_Format = ::RegisterClipboardFormat(_T("DataPointData"));

void CDataPointEventsImpl::OnChanged(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO)
{
}

void CDataPointEventsImpl::OnDragMoved(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO, const WBFL::Geometry::Size2d& offset)
{
   CHECK(FALSE); // Points must be dropped on a member. This event should never occur
}

void CDataPointEventsImpl::OnMoved(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO)
{
}

void CDataPointEventsImpl::OnCopied(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO)
{
   // No big deal...
}

bool CDataPointEventsImpl::OnLButtonDblClk(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO, UINT nFlags, const POINT& point)
{
   return false;
}

bool CDataPointEventsImpl::OnLButtonDown(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO, UINT nFlags, const POINT& point)
{
   auto list = pDO->GetDisplayList();
   auto dispMgr = list->GetDisplayMgr();

   // If control key is pressed, don't clear current selection
   // (i.e. we want multi-select)
   BOOL bMultiSelect = nFlags & MK_CONTROL ? TRUE : FALSE;

   if (bMultiSelect)
   {
      // clear all selected objects that aren't part of the load list
//      dispMgr->ClearSelectedObjectsByList(LOAD_LIST,atByID,FALSE);
   }

   dispMgr->SelectObject(pDO, !bMultiSelect);
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

bool CDataPointEventsImpl::OnRButtonDblClk(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO, UINT nFlags, const POINT& point)
{
   return false;
}

bool CDataPointEventsImpl::OnRButtonUp(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO, UINT nFlags, const POINT& point)
{
   return false;
}

bool CDataPointEventsImpl::OnLButtonUp(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO, UINT nFlags, const POINT& point)
{
   return false;
}

bool CDataPointEventsImpl::OnRButtonDown(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO, UINT nFlags, const POINT& point)
{
   return false;
}

bool CDataPointEventsImpl::OnMouseMove(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO, UINT nFlags, const POINT& point)
{
   return false;
}

bool CDataPointEventsImpl::OnMouseWheel(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO, UINT nFlags, short zDelta, const POINT& point)
{
   return false;
}

bool CDataPointEventsImpl::OnKeyDown(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO, UINT nChar, UINT nRepCnt, UINT nFlags)
{
   switch (nChar)
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

bool CDataPointEventsImpl::OnContextMenu(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO, CWnd* pWnd, const POINT& point)
{
   return false;
}

void CDataPointEventsImpl::OnSelect(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO)
{
}

void CDataPointEventsImpl::OnUnselect(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO)
{
}
