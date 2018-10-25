// SupportEvents.cpp : implementation file
//

#include "stdafx.h"
#include "LBAMViewer.h"
#include "LBAMViewerDoc.h"
#include "SupportEvents.h"
#include "SupportEditDlg.h"
#include "mfcdual.h"
#include "ListID.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSupportEvents
UINT CSupportEvents::ms_Format = ::RegisterClipboardFormat(_T("Supports"));

CSupportEvents::CSupportEvents(CLBAMViewerDoc* pDoc)
{
   m_pDoc = pDoc;
}

CSupportEvents::~CSupportEvents()
{
}

BEGIN_INTERFACE_MAP(CSupportEvents,CCmdTarget)
   INTERFACE_PART(CSupportEvents,IID_iDisplayObjectEvents,DisplayObjectEvents)
   INTERFACE_PART(CSupportEvents,IID_iDragData,DragData)
END_INTERFACE_MAP()

DELEGATE_CUSTOM_INTERFACE(CSupportEvents,DisplayObjectEvents);
DELEGATE_CUSTOM_INTERFACE(CSupportEvents,DragData);

STDMETHODIMP_(void) CSupportEvents::XDisplayObjectEvents::OnChanged(iDisplayObject* pDO)
{
}

STDMETHODIMP_(void) CSupportEvents::XDisplayObjectEvents::OnDragMoved(iDisplayObject* pDO, ISize2d* offset)
{
   METHOD_PROLOGUE(CSupportEvents,DisplayObjectEvents);

   // Move the support and the display object
   IDType id = pDO->GetID();
/*
   WBFLFem2d::IModelPtr model = pThis->m_pDoc->m_Model;
   WBFLFem2d::ISupportPtr jnt = model->Supports->Find(id);
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

STDMETHODIMP_(void) CSupportEvents::XDisplayObjectEvents::OnMoved(iDisplayObject* pDO)
{
   // Support got dropped in a different view... Need to delete the support and
   // all members that attach to it.
   ASSERT(FALSE);
}

STDMETHODIMP_(void) CSupportEvents::XDisplayObjectEvents::OnCopied(iDisplayObject* pDO)
{
   // This support got drag/drop copied to a different view... No big deal
}

STDMETHODIMP_(bool) CSupportEvents::XDisplayObjectEvents::OnLButtonDblClk(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
   METHOD_PROLOGUE(CSupportEvents,DisplayObjectEvents);

   // Support got double clicked on... Display its editing dialog
   IDType id = pDO->GetID();
   pThis->EditSupport(id);

   return true;
}

STDMETHODIMP_(bool) CSupportEvents::XDisplayObjectEvents::OnLButtonDown(iDisplayObject* pDO,UINT nFlags,CPoint point)
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

STDMETHODIMP_(bool) CSupportEvents::XDisplayObjectEvents::OnRButtonDblClk(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
   METHOD_PROLOGUE(CSupportEvents,DisplayObjectEvents);
   return false;
}

STDMETHODIMP_(bool) CSupportEvents::XDisplayObjectEvents::OnRButtonDown(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
   METHOD_PROLOGUE(CSupportEvents,DisplayObjectEvents);
   return false;
}

STDMETHODIMP_(bool) CSupportEvents::XDisplayObjectEvents::OnRButtonUp(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
   METHOD_PROLOGUE(CSupportEvents,DisplayObjectEvents);
   return false;
}

STDMETHODIMP_(bool) CSupportEvents::XDisplayObjectEvents::OnLButtonUp(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
   METHOD_PROLOGUE(CSupportEvents,DisplayObjectEvents);
   return false;
}


STDMETHODIMP_(bool) CSupportEvents::XDisplayObjectEvents::OnMouseMove(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
   METHOD_PROLOGUE(CSupportEvents,DisplayObjectEvents);
   return false;
}

STDMETHODIMP_(bool) CSupportEvents::XDisplayObjectEvents::OnMouseWheel(iDisplayObject* pDO,UINT nFlags,short zDelta,CPoint point)
{
   METHOD_PROLOGUE(CSupportEvents,DisplayObjectEvents);
   return false;
}


STDMETHODIMP_(bool) CSupportEvents::XDisplayObjectEvents::OnKeyDown(iDisplayObject* pDO,UINT nChar, UINT nRepCnt, UINT nFlags)
{
   METHOD_PROLOGUE(CSupportEvents,DisplayObjectEvents);
   IDType id = pDO->GetID();

   switch(nChar)
   {
   case VK_RETURN:
      pThis->EditSupport(id);
      break;

   case VK_DELETE:
      pThis->DeleteSupport(id);
      break;
   }

   return true;
}

STDMETHODIMP_(bool) CSupportEvents::XDisplayObjectEvents::OnContextMenu(iDisplayObject* pDO,CWnd* pWnd,CPoint point)
{
   METHOD_PROLOGUE(CSupportEvents,DisplayObjectEvents);
   return false;
}

STDMETHODIMP_(void) CSupportEvents::XDisplayObjectEvents::OnSelect(iDisplayObject* pDO)
{
}

STDMETHODIMP_(void) CSupportEvents::XDisplayObjectEvents::OnUnselect(iDisplayObject* pDO)
{
}

STDMETHODIMP_(UINT) CSupportEvents::XDragData::Format()
{
   return ms_Format;
}

STDMETHODIMP_(BOOL) CSupportEvents::XDragData::PrepareForDrag(iDisplayObject* pDO,iDragDataSink* pSink)
{
   pSink->CreateFormat(ms_Format);

   IDType id = pDO->GetID();
   pSink->Write(ms_Format,&id,sizeof(id));
   return TRUE;
}

STDMETHODIMP_(void) CSupportEvents::XDragData::OnDrop(iDisplayObject* pDO,iDragDataSource* pSource)
{
   IDType id;
   pSource->PrepareFormat(ms_Format);
   pSource->Read(ms_Format,&id,sizeof(id));
   pDO->SetID(id);
}



void CSupportEvents::EditSupport(IDType jntID)
{
/*
   WBFLFem2d::IModelPtr model = m_pDoc->m_Model;
   WBFLFem2d::ISupportPtr jnt = model->Supports->Find(jntID);
   ASSERT(jnt != NULL);
   ASSERT(jntID == jnt->ID);
*/
   CSupportEditDlg dlg;
/*
   dlg.m_bSupportFx = jnt->IsDofReleased(WBFLFem2d::jrtFx) == VARIANT_TRUE ? FALSE : TRUE;
   dlg.m_bSupportFy = jnt->IsDofReleased(WBFLFem2d::jrtFy) == VARIANT_TRUE ? FALSE : TRUE;
   dlg.m_bSupportMz = jnt->IsDofReleased(WBFLFem2d::jrtMz) == VARIANT_TRUE ? FALSE : TRUE;
   dlg.m_X = jnt->X;
   dlg.m_Y = jnt->Y;
   dlg.m_JntID = jnt->ID;
*/
   if ( dlg.DoModal() )
   {
/*
      jnt->X = dlg.m_X;
      jnt->Y = dlg.m_Y;

      if ( dlg.m_bSupportFx || dlg.m_bSupportFy || dlg.m_bSupportMz )
      {
         jnt->Support();
         if ( !dlg.m_bSupportFx )
            jnt->ReleaseDof(WBFLFem2d::jrtFx);

         if ( !dlg.m_bSupportFy )
            jnt->ReleaseDof(WBFLFem2d::jrtFy);

         if ( !dlg.m_bSupportMz )
            jnt->ReleaseDof(WBFLFem2d::jrtMz);

     }
*/   
   }
}

void CSupportEvents::DeleteSupport(IDType jntID)
{
/*
   WBFLFem2d::IModelPtr model = m_pDoc->m_Model;
   WBFLFem2d::ISupportCollectionPtr supports = model->Supports;
   WBFLFem2d::ISupportPtr support = supports->Find(jntID);
   if ( support->Members->Count == 0 )
   {
      supports->Remove(jntID,WBFLFem2d::atID);
   }
   else
   {
*/
      AfxMessageBox(_T("The support can't be deleted because it has members connected to it"));
  
}
