// JointEvents.cpp : implementation file
//

#include "stdafx.h"
#include "FEA2D.h"
#include "FEA2DDoc.h"
#include "JointEvents.h"
#include "EditJointDlg.h"
#include "mfcdual.h"
#include "ListID.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CJointEvents
UINT CJointEvents::ms_Format = ::RegisterClipboardFormat("Joints");

CJointEvents::CJointEvents(CFEA2DDoc* pDoc)
{
   m_pDoc = pDoc;
}

CJointEvents::~CJointEvents()
{
}

BEGIN_INTERFACE_MAP(CJointEvents,CCmdTarget)
   INTERFACE_PART(CJointEvents,IID_iDisplayObjectEvents,DisplayObjectEvents)
   INTERFACE_PART(CJointEvents,IID_iDragData,DragData)
END_INTERFACE_MAP()

DELEGATE_CUSTOM_INTERFACE(CJointEvents,DisplayObjectEvents);
DELEGATE_CUSTOM_INTERFACE(CJointEvents,DragData);

STDMETHODIMP_(void) CJointEvents::XDisplayObjectEvents::OnChanged(iDisplayObject* pDO)
{
}

STDMETHODIMP_(void) CJointEvents::XDisplayObjectEvents::OnDragMoved(iDisplayObject* pDO,ISize2d* offset)
{
   METHOD_PROLOGUE(CJointEvents,DisplayObjectEvents);

   // Move the joint and the display object
   JointIDType id = pDO->GetID();

   CComPtr<IFem2dModel> model = pThis->m_pDoc->m_Model;
   CComPtr<IFem2dJointCollection> joints;
   model->get_Joints(&joints);

   CComPtr<IFem2dJoint> jnt;
   joints->Find(id,&jnt);

   JointIDType jntID;
   jnt->get_ID(&jntID);

   ASSERT(jnt != NULL);
   ASSERT(id == jntID);

   Float64 x,y;
   jnt->get_X(&x);
   jnt->get_Y(&y);

   Float64 dx,dy;
   offset->get_Dx(&dx);
   offset->get_Dy(&dy);

   x += dx;
   y += dy;

   jnt->put_X(x);
   jnt->put_Y(y);

   CComQIPtr<iPointDisplayObject,&IID_iPointDisplayObject> jntRep(pDO);
   ASSERT(jntRep != NULL);
   jntRep->Offset(offset,TRUE,FALSE);
}

STDMETHODIMP_(void) CJointEvents::XDisplayObjectEvents::OnMoved(iDisplayObject* pDO)
{
   // Joint got dropped in a different view... Need to delete the joint and
   // all members that attach to it.
   ASSERT(FALSE);
}

STDMETHODIMP_(void) CJointEvents::XDisplayObjectEvents::OnCopied(iDisplayObject* pDO)
{
   // This joint got drag/drop copied to a different view... No big deal
}

STDMETHODIMP_(bool) CJointEvents::XDisplayObjectEvents::OnLButtonDblClk(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
   METHOD_PROLOGUE(CJointEvents,DisplayObjectEvents);

   // Joint got double clicked on... Display its editing dialog
   long id = pDO->GetID();
   pThis->EditJoint(id);

   return true;
}

STDMETHODIMP_(bool) CJointEvents::XDisplayObjectEvents::OnLButtonDown(iDisplayObject* pDO,UINT nFlags,CPoint point)
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
      // clear all selected objects that aren't part of the joint list
      dispMgr->ClearSelectedObjectsByList(JNT_LIST,atByID,FALSE);
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

STDMETHODIMP_(bool) CJointEvents::XDisplayObjectEvents::OnRButtonDblClk(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
   METHOD_PROLOGUE(CJointEvents,DisplayObjectEvents);
   return false;
}

STDMETHODIMP_(bool) CJointEvents::XDisplayObjectEvents::OnRButtonDown(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
   METHOD_PROLOGUE(CJointEvents,DisplayObjectEvents);
   return false;
}

STDMETHODIMP_(bool) CJointEvents::XDisplayObjectEvents::OnRButtonUp(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
   METHOD_PROLOGUE(CJointEvents,DisplayObjectEvents);
   return false;
}

STDMETHODIMP_(bool) CJointEvents::XDisplayObjectEvents::OnLButtonUp(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
   METHOD_PROLOGUE(CJointEvents,DisplayObjectEvents);
   return false;
}

STDMETHODIMP_(bool) CJointEvents::XDisplayObjectEvents::OnMouseMove(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
   METHOD_PROLOGUE(CJointEvents,DisplayObjectEvents);
   return false;
}

STDMETHODIMP_(bool) CJointEvents::XDisplayObjectEvents::OnMouseWheel(iDisplayObject* pDO,UINT nFlags,short zDelta,CPoint point)
{
   METHOD_PROLOGUE(CJointEvents,DisplayObjectEvents);
   return false;
}

STDMETHODIMP_(bool) CJointEvents::XDisplayObjectEvents::OnKeyDown(iDisplayObject* pDO,UINT nChar, UINT nRepCnt, UINT nFlags)
{
   METHOD_PROLOGUE(CJointEvents,DisplayObjectEvents);
   long id = pDO->GetID();

   switch(nChar)
   {
   case VK_RETURN:
      pThis->EditJoint(id);
      break;

   case VK_DELETE:
      pThis->DeleteJoint(id);
      break;
   }

   return true;
}

STDMETHODIMP_(bool) CJointEvents::XDisplayObjectEvents::OnContextMenu(iDisplayObject* pDO,CWnd* pWnd,CPoint point)
{
   METHOD_PROLOGUE(CJointEvents,DisplayObjectEvents);
   return false;
}

STDMETHODIMP_(void) CJointEvents::XDisplayObjectEvents::OnSelect(iDisplayObject* pDO)
{
}

STDMETHODIMP_(void) CJointEvents::XDisplayObjectEvents::OnUnselect(iDisplayObject* pDO)
{
}

STDMETHODIMP_(UINT) CJointEvents::XDragData::Format()
{
   return ms_Format;
}

STDMETHODIMP_(BOOL) CJointEvents::XDragData::PrepareForDrag(iDisplayObject* pDO,iDragDataSink* pSink)
{
   pSink->CreateFormat(ms_Format);

   long id = pDO->GetID();
   pSink->Write(ms_Format,&id,sizeof(id));
   return TRUE;
}

STDMETHODIMP_(void) CJointEvents::XDragData::OnDrop(iDisplayObject* pDO,iDragDataSource* pSource)
{
   long id;
   pSource->PrepareFormat(ms_Format);
   pSource->Read(ms_Format,&id,sizeof(id));
   pDO->SetID(id);
}



void CJointEvents::EditJoint(long jntID)
{
   CComPtr<IFem2dModel> model = m_pDoc->m_Model;
   CComPtr<IFem2dJointCollection> joints;
   model->get_Joints(&joints);

   CComPtr<IFem2dJoint> jnt;
   joints->Find(jntID,&jnt);

   ASSERT(jnt != NULL);
//   ASSERT(jntID == jnt->ID);

   CEditJointDlg dlg;
   VARIANT_BOOL bIsReleased;
   jnt->IsDofReleased(jrtFx,&bIsReleased);
   dlg.m_bSupportFx = bIsReleased == VARIANT_TRUE ? FALSE : TRUE;

   jnt->IsDofReleased(jrtFy,&bIsReleased);
   dlg.m_bSupportFy = bIsReleased == VARIANT_TRUE ? FALSE : TRUE;

   jnt->IsDofReleased(jrtMz,&bIsReleased);
   dlg.m_bSupportMz = bIsReleased == VARIANT_TRUE ? FALSE : TRUE;

   jnt->get_X(&dlg.m_X);
   jnt->get_Y(&dlg.m_Y);
   jnt->get_ID(&dlg.m_JntID);

   if ( dlg.DoModal() )
   {
      jnt->put_X(dlg.m_X);
      jnt->put_Y(dlg.m_Y);

      if ( dlg.m_bSupportFx || dlg.m_bSupportFy || dlg.m_bSupportMz )
      {
         jnt->Support();
         if ( !dlg.m_bSupportFx )
            jnt->ReleaseDof(jrtFx);

         if ( !dlg.m_bSupportFy )
            jnt->ReleaseDof(jrtFy);

         if ( !dlg.m_bSupportMz )
            jnt->ReleaseDof(jrtMz);
      }
   }
}

void CJointEvents::DeleteJoint(long jntID)
{
   CComPtr<IFem2dModel> model = m_pDoc->m_Model;
   CComPtr<IFem2dJointCollection> joints;
   model->get_Joints(&joints);

   CComPtr<IFem2dJoint> joint;
   joints->Find(jntID,&joint);

   CComPtr<ILongArray> mbrIDs;
   joint->get_Members(&mbrIDs);

   CollectionIndexType count;
   mbrIDs->get_Count(&count);
   if ( count == 0 )
   {
      JointIDType removedID;
      joints->Remove(jntID,atID,&removedID);
   }
   else
   {
      AfxMessageBox("The joint can't be deleted because it has members connected to it");
   }
}
