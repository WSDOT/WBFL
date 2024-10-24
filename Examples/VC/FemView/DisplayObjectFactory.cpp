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
   m_Factory = DisplayObjectFactory::Create();
}

CDisplayObjectFactory::~CDisplayObjectFactory()
{
}

std::shared_ptr<WBFL::DManip::iDisplayObject> CDisplayObjectFactory::Create(CLIPFORMAT cfFormat, COleDataObject* pDataObject) const
{
   if ( cfFormat == CJointEvents::ms_Format )
   {
      auto jointRep = WBFL::DManip::PointDisplayObject::Create();
      auto draw_strategy = std::make_shared<CJointDrawStrategyImpl>(m_pDoc);
      jointRep->SetDrawingStrategy(draw_strategy);

      auto events = std::make_shared<CJointEvents>(m_pDoc);
      jointRep->RegisterEventSink(events);
      jointRep->SetDragData(events);

      if (pDataObject)
      {
         // Initialize from data object
         auto source = WBFL::DManip::DragDataSource::Create();
         source->SetDataObject(pDataObject);

         // rebuild the display object from the data source
         jointRep->OnDrop(source);
      }

      return jointRep;
   }
   else if ( cfFormat == CPointLoadEventsImpl::ms_Format )
   {
      auto loadRep = WBFL::DManip::PointDisplayObject::Create();
      auto draw_strategy = std::make_shared<CPointLoadDrawStrategyImpl>();
      loadRep->SetDrawingStrategy(draw_strategy);

      auto events = std::make_shared<CPointLoadEventsImpl>(m_pDoc);
      loadRep->RegisterEventSink(events);
      loadRep->SetDragData(events);

      if ( pDataObject )
      {
         // Initialize from data object
         auto source = WBFL::DManip::DragDataSource::Create();
         source->SetDataObject(pDataObject);

         // rebuild the display object from the data source
         loadRep->OnDrop(source);

         CComPtr<IFem2dModel> model = m_pDoc->m_Model;
         CComPtr<IFem2dLoadingCollection> loadings;
         model->get_Loadings(&loadings);

         CComPtr<IFem2dLoading> loading;
         loadings->Find(events->m_Loading,&loading);

         CComPtr<IFem2dPointLoadCollection> ptLoads;
         loading->get_PointLoads(&ptLoads);

         CComPtr<IFem2dPointLoad> ptLoad;
         ptLoads->Find(events->m_ID,&ptLoad);

         draw_strategy->SetLoad(ptLoad);
      }

      return loadRep;
   }
   else
   {
      return m_Factory->Create(cfFormat,pDataObject);
   }
}
