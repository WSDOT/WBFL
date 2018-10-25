// PointLoadEvents.cpp : implementation file
//

#include "stdafx.h"
#include "FEA2D.h"
#include "FEA2DDoc.h"
#include "PointLoadEvents.h"
#include "AddPointLoadDlg.h"
#include "mfcdual.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

UINT CPointLoadEvents::ms_Format = ::RegisterClipboardFormat("PointLoadData");

/////////////////////////////////////////////////////////////////////////////
// CPointLoadEvents
CPointLoadEvents::CPointLoadEvents(CFEA2DDoc* pDoc,WBFLFem2d::IPointLoadPtr load)
{
   m_pDoc = pDoc;

   if ( load )
   {
      m_ID = load->ID;
      m_MemberID = load->MemberID;
      m_Location = load->Location;
      m_Orientation = load->Orientation;
      m_Loading = load->Loading;
      m_Fx = load->Fx;
      m_Fy = load->Fy;
      m_Mz = load->Mz;
   }
}

CPointLoadEvents::~CPointLoadEvents()
{
}

BEGIN_INTERFACE_MAP(CPointLoadEvents,CCmdTarget)
   INTERFACE_PART(CPointLoadEvents,IID_iDisplayObjectEvents,DisplayObjectEvents)
   INTERFACE_PART(CPointLoadEvents,IID_iDragData,DragData)
END_INTERFACE_MAP()

DELEGATE_CUSTOM_INTERFACE(CPointLoadEvents,DisplayObjectEvents);
DELEGATE_CUSTOM_INTERFACE(CPointLoadEvents,DragData);


STDMETHODIMP_(void) CPointLoadEvents::XDisplayObjectEvents::OnChanged(iDisplayObject* pDO)
{
}

STDMETHODIMP_(void) CPointLoadEvents::XDisplayObjectEvents::OnDragMoved(iDisplayObject* pDO,WBFLGeometry::ISize2dPtr offset)
{
   ASSERT(FALSE); // Points must be dropped on a member. This event should never occur
}

STDMETHODIMP_(void) CPointLoadEvents::XDisplayObjectEvents::OnMoved(iDisplayObject* pDO)
{
   METHOD_PROLOGUE(CPointLoadEvents,DisplayObjectEvents);

   // Remove the load from the model...
   // The display object representation of the model will automatically
   // rebuild when the model is changes so we don't need to worry about
   // deleting the display object that represents the load that was moved.
   ASSERT( pThis->m_ID == pDO->GetID() );

   WBFLFem2d::IModelPtr model = pThis->m_pDoc->m_Model;
   WBFLFem2d::ILoadingCollectionPtr loadings = model->Loadings;
   WBFLFem2d::ILoadingPtr loading = loadings->Find(pThis->m_Loading);
   WBFLFem2d::IPointLoadCollectionPtr ptLoads = loading->PointLoads;
   ptLoads->Remove(pThis->m_ID,WBFLFem2d::atID);
}

STDMETHODIMP_(void) CPointLoadEvents::XDisplayObjectEvents::OnCopied(iDisplayObject* pDO)
{
   // No big deal...
}

STDMETHODIMP_(void) CPointLoadEvents::XDisplayObjectEvents::OnLButtonDblClk(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
   METHOD_PROLOGUE(CPointLoadEvents,DisplayObjectEvents);

   WBFLFem2d::IModelPtr model = pThis->m_pDoc->m_Model;
   CAddPointLoadDlg dlg(model,TRUE);

   WBFLFem2d::ILoadingCollectionPtr loadings = model->Loadings;
   WBFLFem2d::ILoadingPtr loading = loadings->Find(pThis->m_Loading);
   WBFLFem2d::IPointLoadCollectionPtr ptLoads = loading->PointLoads;
   WBFLFem2d::IPointLoadPtr ptLoad = ptLoads->Find(pThis->m_ID);

   dlg.m_MbrID = ptLoad->MemberID;
   dlg.m_LoadingID = ptLoad->Loading;
   dlg.m_Fx = ptLoad->Fx;
   dlg.m_Fy = ptLoad->Fy;
   dlg.m_Mz = ptLoad->Mz;
   dlg.m_Location = ptLoad->Location;

   if ( dlg.DoModal() == IDOK )
   {
      ptLoad->SetForce(dlg.m_Fx,dlg.m_Fy,dlg.m_Mz);
   }
}


STDMETHODIMP_(UINT) CPointLoadEvents::XDragData::Format()
{
   return ms_Format;
}

STDMETHODIMP_(BOOL) CPointLoadEvents::XDragData::PrepareForDrag(iDisplayObject* pDO,iDragDataSink* pSink)
{
   METHOD_PROLOGUE(CPointLoadEvents,DragData);

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
   WBFLFem2d::f2dLoadOrientation orient = pThis->m_Orientation;
   pSink->Write(ms_Format,&orient,sizeof(WBFLFem2d::f2dLoadOrientation));

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

STDMETHODIMP_(void) CPointLoadEvents::XDragData::OnDrop(iDisplayObject* pDO,iDragDataSource* pSource)
{
   METHOD_PROLOGUE(CPointLoadEvents,DragData);

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
   WBFLFem2d::f2dLoadOrientation orient;
   pSource->Read(ms_Format,&orient,sizeof(WBFLFem2d::f2dLoadOrientation));
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
