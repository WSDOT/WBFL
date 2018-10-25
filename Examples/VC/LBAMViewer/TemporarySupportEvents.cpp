// TemporarySupportEvents.cpp : implementation file
//

#include "stdafx.h"
#include "LBAMViewer.h"
#include "LBAMViewerDoc.h"
#include "TemporarySupportEvents.h"
#include "TemporarySupportEditDlg.h"
#include "mfcdual.h"
#include "ListID.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTemporarySupportEvents
UINT CTemporarySupportEvents::ms_Format = ::RegisterClipboardFormat(_T("TemporarySupports"));

CTemporarySupportEvents::CTemporarySupportEvents(CLBAMViewerDoc* pDoc)
{
   m_pDoc = pDoc;
}

CTemporarySupportEvents::~CTemporarySupportEvents()
{
}

BEGIN_INTERFACE_MAP(CTemporarySupportEvents,CCmdTarget)
   INTERFACE_PART(CTemporarySupportEvents,IID_iDisplayObjectEvents,DisplayObjectEvents)
   INTERFACE_PART(CTemporarySupportEvents,IID_iDragData,DragData)
END_INTERFACE_MAP()

DELEGATE_CUSTOM_INTERFACE(CTemporarySupportEvents,DisplayObjectEvents);
DELEGATE_CUSTOM_INTERFACE(CTemporarySupportEvents,DragData);

STDMETHODIMP_(void) CTemporarySupportEvents::XDisplayObjectEvents::OnChanged(iDisplayObject* pDO)
{
}

STDMETHODIMP_(void) CTemporarySupportEvents::XDisplayObjectEvents::OnDragMoved(iDisplayObject* pDO,ISize2d* offset)
{
   METHOD_PROLOGUE(CTemporarySupportEvents,DisplayObjectEvents);

   // Move the support and the display object
   IDType id = pDO->GetID();
/*
   WBFLFem2d::IModelPtr model = pThis->m_pDoc->m_Model;
   WBFLFem2d::ITemporarySupportPtr jnt = model->TemporarySupports->Find(id);
   ASSERT(jnt != NULL);
   ASSERT(id == jnt->ID);

   double x,y;
   x = jnt->X;
   y = jnt->Y;
   x += offset->dx;
   y += offset->dy;
   jnt->X = x;
   jnt->Y = y;
*/
   CComQIPtr<iPointDisplayObject,&IID_iPointDisplayObject> jntRep(pDO);
   ASSERT(jntRep != NULL);
   jntRep->Offset(offset,TRUE,FALSE);
}

STDMETHODIMP_(void) CTemporarySupportEvents::XDisplayObjectEvents::OnMoved(iDisplayObject* pDO)
{
   // TemporarySupport got dropped in a different view... Need to delete the support and
   // all members that attach to it.
   ASSERT(FALSE);
}

STDMETHODIMP_(void) CTemporarySupportEvents::XDisplayObjectEvents::OnCopied(iDisplayObject* pDO)
{
   // This support got drag/drop copied to a different view... No big deal
}

STDMETHODIMP_(bool) CTemporarySupportEvents::XDisplayObjectEvents::OnLButtonDblClk(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
   METHOD_PROLOGUE(CTemporarySupportEvents,DisplayObjectEvents);

   // TemporarySupport got double clicked on... Display its editing dialog
   IDType id = pDO->GetID();
   pThis->EditTemporarySupport(id);

   return true;
}

STDMETHODIMP_(bool) CTemporarySupportEvents::XDisplayObjectEvents::OnLButtonDown(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
   // Select the display object and start a drag and drop task

   CComPtr<iDisplayList> list;
   pDO->GetDisplayList(&list);

   CComPtr<iDisplayMgr> dispMgr;
   list->GetDisplayMgr(&dispMgr);

   // If control key is pressed, don't clear current selection
   // (i.e. we want multi-select)
   BOOL bMultiSelect = nFlags & MK_CONTROL ? TRUE : FALSE;
   
   if ( bMultiSelect )
   {
      // clear all selected objects that aren't part of the support list
      dispMgr->ClearSelectedObjectsByList(SUPPORT_LIST,atByIndex,FALSE);
   }

   dispMgr->SelectObject(pDO,!bMultiSelect);

   // d&d task
   CComPtr<iTaskFactory> factory;
   dispMgr->GetTaskFactory(&factory);
   CComPtr<iTask> task;
   factory->CreateLocalDragDropTask(dispMgr,point,&task);
   dispMgr->SetTask(task);

   return true;
}


STDMETHODIMP_(bool) CTemporarySupportEvents::XDisplayObjectEvents::OnRButtonDblClk(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
   METHOD_PROLOGUE(CTemporarySupportEvents,DisplayObjectEvents);
   return false;
}

STDMETHODIMP_(bool) CTemporarySupportEvents::XDisplayObjectEvents::OnRButtonDown(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
   METHOD_PROLOGUE(CTemporarySupportEvents,DisplayObjectEvents);
   return false;
}

STDMETHODIMP_(bool) CTemporarySupportEvents::XDisplayObjectEvents::OnRButtonUp(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
   METHOD_PROLOGUE(CTemporarySupportEvents,DisplayObjectEvents);
   return false;
}

STDMETHODIMP_(bool) CTemporarySupportEvents::XDisplayObjectEvents::OnLButtonUp(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
   METHOD_PROLOGUE(CTemporarySupportEvents,DisplayObjectEvents);
   return false;
}


STDMETHODIMP_(bool) CTemporarySupportEvents::XDisplayObjectEvents::OnMouseMove(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
   METHOD_PROLOGUE(CTemporarySupportEvents,DisplayObjectEvents);
   return false;
}

STDMETHODIMP_(bool) CTemporarySupportEvents::XDisplayObjectEvents::OnMouseWheel(iDisplayObject* pDO,UINT nFlags,short zDelta,CPoint point)
{
   METHOD_PROLOGUE(CTemporarySupportEvents,DisplayObjectEvents);
   return false;
}


STDMETHODIMP_(bool) CTemporarySupportEvents::XDisplayObjectEvents::OnKeyDown(iDisplayObject* pDO,UINT nChar, UINT nRepCnt, UINT nFlags)
{
   METHOD_PROLOGUE(CTemporarySupportEvents,DisplayObjectEvents);
   IDType id = pDO->GetID();

   switch(nChar)
   {
   case VK_RETURN:
      pThis->EditTemporarySupport(id);
      break;

   case VK_DELETE:
      pThis->DeleteTemporarySupport(id);
      break;
   }

   return true;
}

STDMETHODIMP_(bool) CTemporarySupportEvents::XDisplayObjectEvents::OnContextMenu(iDisplayObject* pDO,CWnd* pWnd,CPoint point)
{
   METHOD_PROLOGUE(CTemporarySupportEvents,DisplayObjectEvents);
   return false;
}

STDMETHODIMP_(void) CTemporarySupportEvents::XDisplayObjectEvents::OnSelect(iDisplayObject* pDO)
{
}

STDMETHODIMP_(void) CTemporarySupportEvents::XDisplayObjectEvents::OnUnselect(iDisplayObject* pDO)
{
}

STDMETHODIMP_(UINT) CTemporarySupportEvents::XDragData::Format()
{
   return ms_Format;
}

STDMETHODIMP_(BOOL) CTemporarySupportEvents::XDragData::PrepareForDrag(iDisplayObject* pDO,iDragDataSink* pSink)
{
   pSink->CreateFormat(ms_Format);

   IDType id = pDO->GetID();
   pSink->Write(ms_Format,&id,sizeof(id));
   return TRUE;
}

STDMETHODIMP_(void) CTemporarySupportEvents::XDragData::OnDrop(iDisplayObject* pDO,iDragDataSource* pSource)
{
   IDType id;
   pSource->PrepareFormat(ms_Format);
   pSource->Read(ms_Format,&id,sizeof(id));
   pDO->SetID(id);
}



void CTemporarySupportEvents::EditTemporarySupport(IDType jntID)
{
/*
   WBFLFem2d::IModelPtr model = m_pDoc->m_Model;
   WBFLFem2d::ITemporarySupportPtr jnt = model->TemporarySupports->Find(jntID);
   ASSERT(jnt != NULL);
   ASSERT(jntID == jnt->ID);
*/
   CTemporarySupportEditDlg dlg;
/*
   dlg.m_bTemporarySupportFx = jnt->IsDofReleased(WBFLFem2d::jrtFx) == VARIANT_TRUE ? FALSE : TRUE;
   dlg.m_bTemporarySupportFy = jnt->IsDofReleased(WBFLFem2d::jrtFy) == VARIANT_TRUE ? FALSE : TRUE;
   dlg.m_bTemporarySupportMz = jnt->IsDofReleased(WBFLFem2d::jrtMz) == VARIANT_TRUE ? FALSE : TRUE;
   dlg.m_X = jnt->X;
   dlg.m_Y = jnt->Y;
   dlg.m_JntID = jnt->ID;
*/
   if ( dlg.DoModal() )
   {
/*
      jnt->X = dlg.m_X;
      jnt->Y = dlg.m_Y;

      if ( dlg.m_bTemporarySupportFx || dlg.m_bTemporarySupportFy || dlg.m_bTemporarySupportMz )
      {
         jnt->TemporarySupport();
         if ( !dlg.m_bTemporarySupportFx )
            jnt->ReleaseDof(WBFLFem2d::jrtFx);

         if ( !dlg.m_bTemporarySupportFy )
            jnt->ReleaseDof(WBFLFem2d::jrtFy);

         if ( !dlg.m_bTemporarySupportMz )
            jnt->ReleaseDof(WBFLFem2d::jrtMz);

     }
*/   
   }
}

void CTemporarySupportEvents::DeleteTemporarySupport(IDType jntID)
{
/*
   WBFLFem2d::IModelPtr model = m_pDoc->m_Model;
   WBFLFem2d::ITemporarySupportCollectionPtr supports = model->TemporarySupports;
   WBFLFem2d::ITemporarySupportPtr support = supports->Find(jntID);
   if ( support->Members->Count == 0 )
   {
      supports->Remove(jntID,WBFLFem2d::atID);
   }
   else
   {
*/
      AfxMessageBox(_T("The support can't be deleted because it has members connected to it"));
  
}
