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

void CPointLoadEventsImpl::InitFromLoad(IFem2dPointLoad* load)
{
   if ( load )
   {
      load->get_ID(&m_ID);
      load->get_MemberID(&m_MemberID);
      load->get_Location(&m_Location);
      load->get_Orientation(&m_Orientation);
      load->get_Loading(&m_Loading);
      load->get_Fx(&m_Fx);
      load->get_Fy(&m_Fy);
      load->get_Mz(&m_Mz);
   }
}

void CPointLoadEventsImpl::OnChanged(std::shared_ptr<iDisplayObject> pDO)
{
}

void CPointLoadEventsImpl::OnDragMoved(std::shared_ptr<iDisplayObject> pDO,const WBFL::Geometry::Size2d& offset)
{
   ASSERT(FALSE); // Points must be dropped on a member. This event should never occur
}

void CPointLoadEventsImpl::OnMoved(std::shared_ptr<iDisplayObject> pDO)
{
   // Remove the load from the model...
   // The display object representation of the model will automatically
   // rebuild when the model is changes so we don't need to worry about
   // deleting the display object that represents the load that was moved.
   ASSERT( m_ID == pDO->GetID() );

   CComPtr<IFem2dModel> model = m_pDoc->m_Model;
   CComPtr<IFem2dLoadingCollection> loadings;
   model->get_Loadings(&loadings);

   CComPtr<IFem2dLoading> loading;
   loadings->Find(m_Loading,&loading);

   CComPtr<IFem2dPointLoadCollection> ptLoads;
   loading->get_PointLoads(&ptLoads);
   
   LoadIDType removedID;
   ptLoads->Remove(m_ID,atID,&removedID);
}

void CPointLoadEventsImpl::OnCopied(std::shared_ptr<iDisplayObject> pDO)
{
   // No big deal...
}

bool CPointLoadEventsImpl::OnLButtonDblClk(std::shared_ptr<iDisplayObject> pDO,UINT nFlags,const POINT& point)
{
   EditLoad(m_Loading,m_ID);

   return true;
}

bool CPointLoadEventsImpl::OnLButtonDown(std::shared_ptr<iDisplayObject> pDO,UINT nFlags,const POINT& point)
{
   auto list = pDO->GetDisplayList();

   auto dispMgr = list->GetDisplayMgr();

   // If control key is pressed, don't clear current selection
   // (i.e. we want multi-select)
   BOOL bMultiSelect = nFlags & MK_CONTROL ? TRUE : FALSE;
   
   if ( bMultiSelect )
   {
      // clear all selected objects that aren't part of the load list
      dispMgr->ClearSelectedObjectsByList(LOAD_LIST,AccessType::ByID,FALSE);
   }

   dispMgr->SelectObject(pDO,!bMultiSelect);

   // d&d task
   auto factory = dispMgr->GetTaskFactory();
   auto task = factory->CreateLocalDragDropTask(dispMgr,point);
   dispMgr->SetTask(task);

   return true;
}

bool CPointLoadEventsImpl::OnRButtonDblClk(std::shared_ptr<iDisplayObject> pDO,UINT nFlags,const POINT& point)
{
   return false;
}

bool CPointLoadEventsImpl::OnRButtonDown(std::shared_ptr<iDisplayObject> pDO,UINT nFlags,const POINT& point)
{
   return false;
}

bool CPointLoadEventsImpl::OnRButtonUp(std::shared_ptr<iDisplayObject> pDO,UINT nFlags,const POINT& point)
{
   return false;
}

bool CPointLoadEventsImpl::OnLButtonUp(std::shared_ptr<iDisplayObject> pDO,UINT nFlags,const POINT& point)
{
   return false;
}

bool CPointLoadEventsImpl::OnMouseMove(std::shared_ptr<iDisplayObject> pDO,UINT nFlags,const POINT& point)
{
   return false;
}

bool CPointLoadEventsImpl::OnMouseWheel(std::shared_ptr<iDisplayObject> pDO,UINT nFlags,short zDelta,const POINT& point)
{
   return false;
}

bool CPointLoadEventsImpl::OnKeyDown(std::shared_ptr<iDisplayObject> pDO,UINT nChar, UINT nRepCnt, UINT nFlags)
{
   switch(nChar)
   {
   case VK_RETURN:
         EditLoad(m_Loading,m_ID);
         break;

   case VK_DELETE:
         DeleteLoad(m_Loading,m_ID);
         break;
   }
   return false;
}

bool CPointLoadEventsImpl::OnContextMenu(std::shared_ptr<iDisplayObject> pDO,CWnd* pWnd,const POINT& point)
{
   return false;
}

void CPointLoadEventsImpl::OnSelect(std::shared_ptr<iDisplayObject> pDO)
{
}

void CPointLoadEventsImpl::OnUnselect(std::shared_ptr<iDisplayObject> pDO)
{
}

UINT CPointLoadEventsImpl::Format()
{
   return ms_Format;
}

bool CPointLoadEventsImpl::PrepareForDrag(std::shared_ptr<iDisplayObject> pDO,std::shared_ptr<iDragDataSink> pSink)
{
   // Create a place to store the drag data for this object
   pSink->CreateFormat(ms_Format);

   // Load ID
   IDType id = m_ID;
   pSink->Write(ms_Format,&id,sizeof(id));

   // loading
   id = m_Loading;
   pSink->Write(ms_Format,&id,sizeof(id));

   // member id
   id = m_MemberID;
   pSink->Write(ms_Format,&id,sizeof(id));

   // location
   double location = m_Location;
   pSink->Write(ms_Format,&location,sizeof(location));

   // orientation
   Fem2dLoadOrientation orient = m_Orientation;
   pSink->Write(ms_Format,&orient,sizeof(Fem2dLoadOrientation));

   // fx, fy, mz;
   double val;
   val = m_Fx;
   pSink->Write(ms_Format,&val,sizeof(val));

   val = m_Fy;
   pSink->Write(ms_Format,&val,sizeof(val));
   
   val = m_Mz;
   pSink->Write(ms_Format,&val,sizeof(val));

   return TRUE;
}

void CPointLoadEventsImpl::OnDrop(std::shared_ptr<iDisplayObject> pDO,std::shared_ptr<iDragDataSource> pSource)
{
   // Tell the source we are about to read from our format
   pSource->PrepareFormat(ms_Format);

   // Load ID
   long id;
   pSource->Read(ms_Format,&id,sizeof(id));
   m_ID = id;

   // loading
   pSource->Read(ms_Format,&id,sizeof(id));
   m_Loading = id;

   // member id
   pSource->Read(ms_Format,&id,sizeof(id));
   m_MemberID = id;

   // location
   double location;
   pSource->Read(ms_Format,&location,sizeof(location));
   m_Location = location;

   // orientation
   Fem2dLoadOrientation orient;
   pSource->Read(ms_Format,&orient,sizeof(Fem2dLoadOrientation));
   m_Orientation = orient;

   // fx, fy, mz;
   double val;
   pSource->Read(ms_Format,&val,sizeof(val));
   m_Fx = val;

   pSource->Read(ms_Format,&val,sizeof(val));
   m_Fy = val;

   pSource->Read(ms_Format,&val,sizeof(val));
   m_Mz = val;
}

void CPointLoadEventsImpl::EditLoad(IDType loadingID,IDType loadID)
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

void CPointLoadEventsImpl::DeleteLoad(IDType loadingID,IDType loadID)
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
