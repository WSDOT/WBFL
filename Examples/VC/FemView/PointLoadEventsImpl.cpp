// PointLoadEventsImpl.cpp : implementation file
//

#include "stdafx.h"
#include "FEA2D.h"
#include "FEA2DDoc.h"
#include "PointLoadEventsImpl.h"
#include "AddPointLoadDlg.h"
#include "mfcdual.h"
#include "ListID.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

UINT CPointLoadEventsImpl::ms_Format = ::RegisterClipboardFormat(_T("PointLoadData"));

/////////////////////////////////////////////////////////////////////////////
// CPointLoadEventsImpl
CPointLoadEventsImpl::CPointLoadEventsImpl(CFEA2DDoc* pDoc)
{
   m_pDoc = pDoc;
}

CPointLoadEventsImpl::~CPointLoadEventsImpl()
{
}

BEGIN_INTERFACE_MAP(CPointLoadEventsImpl,CCmdTarget)
   INTERFACE_PART(CPointLoadEventsImpl,IID_iPointLoadEvents,Events)
   INTERFACE_PART(CPointLoadEventsImpl,IID_iDisplayObjectEvents,DisplayObjectEvents)
   INTERFACE_PART(CPointLoadEventsImpl,IID_iDragData,DragData)
END_INTERFACE_MAP()

DELEGATE_CUSTOM_INTERFACE(CPointLoadEventsImpl,Events);
DELEGATE_CUSTOM_INTERFACE(CPointLoadEventsImpl,DisplayObjectEvents);
DELEGATE_CUSTOM_INTERFACE(CPointLoadEventsImpl,DragData);

STDMETHODIMP_(void) CPointLoadEventsImpl::XEvents::InitFromLoad(IFem2dPointLoad* load)
{
   METHOD_PROLOGUE(CPointLoadEventsImpl,Events);
   if ( load )
   {
      load->get_ID(&pThis->m_ID);
      load->get_MemberID(&pThis->m_MemberID);
      load->get_Location(&pThis->m_Location);
      load->get_Orientation(&pThis->m_Orientation);
      load->get_Loading(&pThis->m_Loading);
      load->get_Fx(&pThis->m_Fx);
      load->get_Fy(&pThis->m_Fy);
      load->get_Mz(&pThis->m_Mz);
   }
}

STDMETHODIMP_(void) CPointLoadEventsImpl::XDisplayObjectEvents::OnChanged(iDisplayObject* pDO)
{
}

STDMETHODIMP_(void) CPointLoadEventsImpl::XDisplayObjectEvents::OnDragMoved(iDisplayObject* pDO,ISize2d* offset)
{
   ASSERT(FALSE); // Points must be dropped on a member. This event should never occur
}

STDMETHODIMP_(void) CPointLoadEventsImpl::XDisplayObjectEvents::OnMoved(iDisplayObject* pDO)
{
   METHOD_PROLOGUE(CPointLoadEventsImpl,DisplayObjectEvents);

   // Remove the load from the model...
   // The display object representation of the model will automatically
   // rebuild when the model is changes so we don't need to worry about
   // deleting the display object that represents the load that was moved.
   ASSERT( pThis->m_ID == pDO->GetID() );

   CComPtr<IFem2dModel> model = pThis->m_pDoc->m_Model;
   CComPtr<IFem2dLoadingCollection> loadings;
   model->get_Loadings(&loadings);

   CComPtr<IFem2dLoading> loading;
   loadings->Find(pThis->m_Loading,&loading);

   CComPtr<IFem2dPointLoadCollection> ptLoads;
   loading->get_PointLoads(&ptLoads);
   
   LoadIDType removedID;
   ptLoads->Remove(pThis->m_ID,atID,&removedID);
}

STDMETHODIMP_(void) CPointLoadEventsImpl::XDisplayObjectEvents::OnCopied(iDisplayObject* pDO)
{
   // No big deal...
}

STDMETHODIMP_(bool) CPointLoadEventsImpl::XDisplayObjectEvents::OnLButtonDblClk(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
   METHOD_PROLOGUE(CPointLoadEventsImpl,DisplayObjectEvents);
   pThis->EditLoad(pThis->m_Loading,pThis->m_ID);

   return true;
}

STDMETHODIMP_(bool) CPointLoadEventsImpl::XDisplayObjectEvents::OnLButtonDown(iDisplayObject* pDO,UINT nFlags,CPoint point)
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
      dispMgr->ClearSelectedObjectsByList(LOAD_LIST,atByID,FALSE);
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

STDMETHODIMP_(bool) CPointLoadEventsImpl::XDisplayObjectEvents::OnRButtonDblClk(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
   METHOD_PROLOGUE(CPointLoadEventsImpl,DisplayObjectEvents);
   return false;
}

STDMETHODIMP_(bool) CPointLoadEventsImpl::XDisplayObjectEvents::OnRButtonDown(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
   METHOD_PROLOGUE(CPointLoadEventsImpl,DisplayObjectEvents);
   return false;
}

STDMETHODIMP_(bool) CPointLoadEventsImpl::XDisplayObjectEvents::OnRButtonUp(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
   METHOD_PROLOGUE(CPointLoadEventsImpl,DisplayObjectEvents);
   return false;
}

STDMETHODIMP_(bool) CPointLoadEventsImpl::XDisplayObjectEvents::OnLButtonUp(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
   METHOD_PROLOGUE(CPointLoadEventsImpl,DisplayObjectEvents);
   return false;
}

STDMETHODIMP_(bool) CPointLoadEventsImpl::XDisplayObjectEvents::OnMouseMove(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
   METHOD_PROLOGUE(CPointLoadEventsImpl,DisplayObjectEvents);
   return false;
}

STDMETHODIMP_(bool) CPointLoadEventsImpl::XDisplayObjectEvents::OnMouseWheel(iDisplayObject* pDO,UINT nFlags,short zDelta,CPoint point)
{
   METHOD_PROLOGUE(CPointLoadEventsImpl,DisplayObjectEvents);
   return false;
}

STDMETHODIMP_(bool) CPointLoadEventsImpl::XDisplayObjectEvents::OnKeyDown(iDisplayObject* pDO,UINT nChar, UINT nRepCnt, UINT nFlags)
{
   METHOD_PROLOGUE(CPointLoadEventsImpl,DisplayObjectEvents);
   switch(nChar)
   {
   case VK_RETURN:
         pThis->EditLoad(pThis->m_Loading,pThis->m_ID);
         break;

   case VK_DELETE:
         pThis->DeleteLoad(pThis->m_Loading,pThis->m_ID);
         break;
   }
   return false;
}

STDMETHODIMP_(bool) CPointLoadEventsImpl::XDisplayObjectEvents::OnContextMenu(iDisplayObject* pDO,CWnd* pWnd,CPoint point)
{
   METHOD_PROLOGUE(CPointLoadEventsImpl,DisplayObjectEvents);
   return false;
}

STDMETHODIMP_(void) CPointLoadEventsImpl::XDisplayObjectEvents::OnSelect(iDisplayObject* pDO)
{
}

STDMETHODIMP_(void) CPointLoadEventsImpl::XDisplayObjectEvents::OnUnselect(iDisplayObject* pDO)
{
}

STDMETHODIMP_(UINT) CPointLoadEventsImpl::XDragData::Format()
{
   return ms_Format;
}

STDMETHODIMP_(BOOL) CPointLoadEventsImpl::XDragData::PrepareForDrag(iDisplayObject* pDO,iDragDataSink* pSink)
{
   METHOD_PROLOGUE(CPointLoadEventsImpl,DragData);

   // Create a place to store the drag data for this object
   pSink->CreateFormat(ms_Format);

   // Load ID
   long id = pThis->m_ID;
   pSink->Write(ms_Format,&id,sizeof(id));

   // loading
   id = pThis->m_Loading;
   pSink->Write(ms_Format,&id,sizeof(id));

   // member id
   id = pThis->m_MemberID;
   pSink->Write(ms_Format,&id,sizeof(id));

   // location
   double location = pThis->m_Location;
   pSink->Write(ms_Format,&location,sizeof(location));

   // orientation
   Fem2dLoadOrientation orient = pThis->m_Orientation;
   pSink->Write(ms_Format,&orient,sizeof(Fem2dLoadOrientation));

   // fx, fy, mz;
   double val;
   val = pThis->m_Fx;
   pSink->Write(ms_Format,&val,sizeof(val));

   val = pThis->m_Fy;
   pSink->Write(ms_Format,&val,sizeof(val));
   
   val = pThis->m_Mz;
   pSink->Write(ms_Format,&val,sizeof(val));

   return TRUE;
}

STDMETHODIMP_(void) CPointLoadEventsImpl::XDragData::OnDrop(iDisplayObject* pDO,iDragDataSource* pSource)
{
   METHOD_PROLOGUE(CPointLoadEventsImpl,DragData);

   // Tell the source we are about to read from our format
   pSource->PrepareFormat(ms_Format);

   // Load ID
   long id;
   pSource->Read(ms_Format,&id,sizeof(id));
   pThis->m_ID = id;

   // loading
   pSource->Read(ms_Format,&id,sizeof(id));
   pThis->m_Loading = id;

   // member id
   pSource->Read(ms_Format,&id,sizeof(id));
   pThis->m_MemberID = id;

   // location
   double location;
   pSource->Read(ms_Format,&location,sizeof(location));
   pThis->m_Location = location;

   // orientation
   Fem2dLoadOrientation orient;
   pSource->Read(ms_Format,&orient,sizeof(Fem2dLoadOrientation));
   pThis->m_Orientation = orient;

   // fx, fy, mz;
   double val;
   pSource->Read(ms_Format,&val,sizeof(val));
   pThis->m_Fx = val;

   pSource->Read(ms_Format,&val,sizeof(val));
   pThis->m_Fy = val;

   pSource->Read(ms_Format,&val,sizeof(val));
   pThis->m_Mz = val;
}

void CPointLoadEventsImpl::EditLoad(long loadingID,long loadID)
{
   CComPtr<IFem2dModel> model = m_pDoc->m_Model;
   CAddPointLoadDlg dlg(model,TRUE);

   CComPtr<IFem2dLoadingCollection> loadings;
   model->get_Loadings(&loadings);

   CComPtr<IFem2dLoading> loading;
   loadings->Find(loadingID,&loading);

   CComPtr<IFem2dPointLoadCollection> ptLoads;
   loading->get_PointLoads(&ptLoads);

   CComPtr<IFem2dPointLoad> ptLoad;
   ptLoads->Find(loadID,&ptLoad);

   ptLoad->get_MemberID(&dlg.m_MbrID);
   LoadCaseIDType lcID;
   ptLoad->get_Loading(&lcID);
   dlg.m_LoadingID = lcID;

   ptLoad->get_Fx(&dlg.m_Fx);
   ptLoad->get_Fy(&dlg.m_Fy);
   ptLoad->get_Mz(&dlg.m_Mz);
   ptLoad->get_Location(&dlg.m_Location);

   if ( dlg.DoModal() == IDOK )
   {
      ptLoad->SetForce(dlg.m_Fx,dlg.m_Fy,dlg.m_Mz);
   }
}

void CPointLoadEventsImpl::DeleteLoad(long loadingID,long loadID)
{
   CComPtr<IFem2dModel>model = m_pDoc->m_Model;

   CComPtr<IFem2dLoadingCollection> loadings;
   model->get_Loadings(&loadings);

   CComPtr<IFem2dLoading> loading;
   loadings->Find(loadingID,&loading);

   CComPtr<IFem2dPointLoadCollection> ptLoads;
   loading->get_PointLoads(&ptLoads);

   LoadIDType removedID;
   ptLoads->Remove(loadID,atID,&removedID);
}
