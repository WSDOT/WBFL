// DisplayObjectFactoryEvents.cpp : implementation file
//

#include "stdafx.h"
#include "FEA2D.h"
#include "FEA2DDoc.h"
#include "DisplayObjectFactory.h"

// Header files for classes that implement iDragData
#include "JointEvents.h"
#include "PointLoadEventsImpl.h"

// Stuff used by display objects
#include "JointDrawStrategyImpl.h"
#include "PointLoadDrawStrategyImpl.h"

#include "mfcdual.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDisplayObjectFactory

CDisplayObjectFactory::CDisplayObjectFactory(CFEA2DDoc* pDoc)
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

STDMETHODIMP_(void) CDisplayObjectFactory::XFactory::Create(CLIPFORMAT cfFormat,COleDataObject* pDataObject,iDisplayObject** dispObj)
{
   METHOD_PROLOGUE(CDisplayObjectFactory,Factory);

   if ( cfFormat == CJointEvents::ms_Format )
   {
      CComPtr<iPointDisplayObject> jointRep;
      ::CoCreateInstance(CLSID_PointDisplayObject,NULL,CLSCTX_ALL,IID_iPointDisplayObject,(void**)&jointRep);

      CJointDrawStrategyImpl* pDrawStrategy = new CJointDrawStrategyImpl(pThis->m_pDoc);
      iDrawPointStrategy* cpstrategy = (iDrawPointStrategy*)pDrawStrategy->GetInterface(&IID_iDrawPointStrategy);
      jointRep->SetDrawingStrategy(cpstrategy);
      cpstrategy->Release();

      CJointEvents* pEvents = new CJointEvents(pThis->m_pDoc);
      iDisplayObjectEvents* pDOE =(iDisplayObjectEvents*)pEvents->GetInterface(&IID_iDisplayObjectEvents);
      jointRep->RegisterEventSink(pDOE);
      pDOE->Release();

      CComQIPtr<iDragData,&IID_iDragData> dd(pEvents->GetInterface(&IID_IUnknown));
      CComQIPtr<iDraggable,&IID_iDraggable> draggable(jointRep);
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

      (*dispObj) = jointRep;
      (*dispObj)->AddRef();
   }
   else if ( cfFormat == CPointLoadEventsImpl::ms_Format )
   {
      CComPtr<iPointDisplayObject> loadRep;
      ::CoCreateInstance(CLSID_PointDisplayObject,NULL,CLSCTX_ALL,IID_iPointDisplayObject,(void**)&loadRep);

      CPointLoadDrawStrategyImpl* pDrawStrategy = new CPointLoadDrawStrategyImpl;
      CComQIPtr<iDrawPointStrategy,&IID_iDrawPointStrategy> drawStrategy(pDrawStrategy->GetInterface(&IID_IUnknown));
      loadRep->SetDrawingStrategy(drawStrategy);

      CPointLoadEventsImpl* pEvents = new CPointLoadEventsImpl(pThis->m_pDoc);
      CComQIPtr<iDisplayObjectEvents,&IID_iDisplayObjectEvents> events(pEvents->GetInterface(&IID_IUnknown));
      loadRep->RegisterEventSink(events);

      CComQIPtr<iDragData,&IID_iDragData> dd(pEvents->GetInterface(&IID_IUnknown));
      CComQIPtr<iDraggable,&IID_iDraggable> draggable(loadRep);
      draggable->SetDragData(dd);

      if ( pDataObject )
      {
         // Initialize from data object
         CComPtr<iDragDataSource> source;
         ::CoCreateInstance(CLSID_DragDataSource,NULL,CLSCTX_ALL,IID_iDragDataSource,(void**)&source);
         source->SetDataObject(pDataObject);

         // rebuild the display object from the data source
         draggable->OnDrop(source);

         CComPtr<IFem2dModel> model = pThis->m_pDoc->m_Model;
         CComPtr<IFem2dLoadingCollection> loadings;
         model->get_Loadings(&loadings);

         CComPtr<IFem2dLoading> loading;
         loadings->Find(pEvents->m_Loading,&loading);

         CComPtr<IFem2dPointLoadCollection> ptLoads;
         loading->get_PointLoads(&ptLoads);

         CComPtr<IFem2dPointLoad> ptLoad;
         ptLoads->Find(pEvents->m_ID,&ptLoad);

         CComPtr<iPointLoadDrawStrategy> strategy((iPointLoadDrawStrategy*)pDrawStrategy->GetInterface(&IID_iPointLoadDrawStrategy));
         strategy->SetLoad(ptLoad);
      }

      (*dispObj) = loadRep;
      (*dispObj)->AddRef();
   }
   else
   {
      pThis->m_Factory->Create(cfFormat,pDataObject,dispObj);
   }
}
