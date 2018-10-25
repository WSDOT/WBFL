// DisplayObjectFactory.cpp : implementation file
//

#include "stdafx.h"
#include "LBAMViewer.h"
#include "DisplayObjectFactory.h"

#include "LBAMViewerDoc.h"

#include "mfcdual.h"

#include "SupportEvents.h"
#include "SupportDrawStrategyImpl.h"
#include "TemporarySupportEvents.h"
#include "TemporarySupportDrawStrategyImpl.h"
#include "LBAMTruckDisplayImpl.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDisplayObjectFactory

CDisplayObjectFactory::CDisplayObjectFactory(CLBAMViewerDoc* pDoc)
{
   m_pDoc = pDoc;
   ::CoCreateInstance(CLSID_DisplayObjectFactory,NULL,CLSCTX_ALL,IID_iDisplayObjectFactory,(void**)&m_Factory);
}


CDisplayObjectFactory::~CDisplayObjectFactory()
{
}




BEGIN_INTERFACE_MAP(CDisplayObjectFactory,CCmdTarget)
   INTERFACE_PART(CDisplayObjectFactory,IID_iDisplayObjectFactory,Factory)
END_INTERFACE_MAP()

DELEGATE_CUSTOM_INTERFACE(CDisplayObjectFactory,Factory);


/////////////////////////////////////////////////////////////////////////////
// CDisplayObjectFactory message handlers
STDMETHODIMP_(void) CDisplayObjectFactory::XFactory::Create(CLIPFORMAT cfFormat,COleDataObject* pDataObject,iDisplayObject** dispObj)
{
   METHOD_PROLOGUE(CDisplayObjectFactory,Factory);

   if ( cfFormat == CSupportEvents::ms_Format )
   {
      CComPtr<iPointDisplayObject> SupportRep;
      ::CoCreateInstance(CLSID_PointDisplayObject,NULL,CLSCTX_ALL,IID_iPointDisplayObject,(void**)&SupportRep);

      CSupportDrawStrategyImpl* pDrawStrategy = new CSupportDrawStrategyImpl(pThis->m_pDoc);
      SupportRep->SetDrawingStrategy((iDrawPointStrategy*)pDrawStrategy->GetInterface(&IID_iDrawPointStrategy));

      CSupportEvents* pEvents = new CSupportEvents(pThis->m_pDoc);
      CComPtr<iDisplayObjectEvents> pDOE = (iDisplayObjectEvents*)pEvents->GetInterface(&IID_iDisplayObjectEvents);
      SupportRep->RegisterEventSink(pDOE);

      CComQIPtr<iDragData,&IID_iDragData> dd(pEvents->GetInterface(&IID_IUnknown));
      CComQIPtr<iDraggable,&IID_iDraggable> draggable(SupportRep);
      draggable->SetDragData(dd);

      if ( pDataObject )
      {
         // Initialize from data object
         CComPtr<iDragDataSource> source;
         ::CoCreateInstance(CLSID_DragDataSource,NULL,CLSCTX_ALL,IID_iDragDataSource,(void**)&source);
         source->SetDataObject(pDataObject);

         // rebuild the display object from the data source
         draggable->OnDrop(source);
      }

      (*dispObj) = SupportRep;
      (*dispObj)->AddRef();
   }
   else if ( cfFormat == CTemporarySupportEvents::ms_Format )
   {
      CComPtr<iPointDisplayObject> TemporarySupportRep;
      ::CoCreateInstance(CLSID_PointDisplayObject,NULL,CLSCTX_ALL,IID_iPointDisplayObject,(void**)&TemporarySupportRep);

      CTemporarySupportDrawStrategyImpl* pDrawStrategy = new CTemporarySupportDrawStrategyImpl(pThis->m_pDoc);
      TemporarySupportRep->SetDrawingStrategy((iDrawPointStrategy*)pDrawStrategy->GetInterface(&IID_iDrawPointStrategy));

      CTemporarySupportEvents* pEvents = new CTemporarySupportEvents(pThis->m_pDoc);
      CComPtr<iDisplayObjectEvents> pDOE = (iDisplayObjectEvents*)pEvents->GetInterface(&IID_iDisplayObjectEvents);
      TemporarySupportRep->RegisterEventSink(pDOE);

      CComQIPtr<iDragData,&IID_iDragData> dd(pEvents->GetInterface(&IID_IUnknown));
      CComQIPtr<iDraggable,&IID_iDraggable> draggable(TemporarySupportRep);
      draggable->SetDragData(dd);

      if ( pDataObject )
      {
         // Initialize from data object
         CComPtr<iDragDataSource> source;
         ::CoCreateInstance(CLSID_DragDataSource,NULL,CLSCTX_ALL,IID_iDragDataSource,(void**)&source);
         source->SetDataObject(pDataObject);

         // rebuild the display object from the data source
         draggable->OnDrop(source);
      }

      (*dispObj) = TemporarySupportRep;
      (*dispObj)->AddRef();
   }
   else if ( cfFormat == CLBAMTruckDisplayImpl::ms_Format )
   {
      CComPtr<iPointDisplayObject> TruckRep;
      ::CoCreateInstance(CLSID_PointDisplayObject,NULL,CLSCTX_ALL,IID_iPointDisplayObject,(void**)&TruckRep);

      CLBAMTruckDisplayImpl* pDisplayImpl = new CLBAMTruckDisplayImpl();
      TruckRep->SetDrawingStrategy((iDrawPointStrategy*)pDisplayImpl->GetInterface(&IID_iDrawPointStrategy));

      CComPtr<iDisplayObjectEvents> pDOE = (iDisplayObjectEvents*)pDisplayImpl->GetInterface(&IID_iDisplayObjectEvents);
      TruckRep->RegisterEventSink(pDOE);

      CComQIPtr<iDragData,&IID_iDragData> dd(pDisplayImpl->GetInterface(&IID_IUnknown));
      CComQIPtr<iDraggable,&IID_iDraggable> draggable(TruckRep);
      draggable->SetDragData(dd);

      if ( pDataObject )
      {
         // Initialize from data object
         CComPtr<iDragDataSource> source;
         ::CoCreateInstance(CLSID_DragDataSource,NULL,CLSCTX_ALL,IID_iDragDataSource,(void**)&source);
         source->SetDataObject(pDataObject);

         // rebuild the display object from the data source
         draggable->OnDrop(source);
      }

      (*dispObj) = TruckRep;
      (*dispObj)->AddRef();
   }

   else
   {
      pThis->m_Factory->Create(cfFormat,pDataObject,dispObj);
   }

}
