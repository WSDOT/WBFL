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

#include "LegendDisplayObject.h"


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
   m_Factory = WBFL::DManip::DisplayObjectFactory::Create();
}


CDisplayObjectFactory::~CDisplayObjectFactory()
{
}

/////////////////////////////////////////////////////////////////////////////
// CDisplayObjectFactory message handlers
std::shared_ptr<WBFL::DManip::iDisplayObject> CDisplayObjectFactory::Create(CLIPFORMAT cfFormat, COleDataObject* pDataObject) const
{
   if (cfFormat == CLegendDisplayObject::ms_cfFormat)
   {
      auto legRep = CLegendDisplayObject::Create();

      if (pDataObject)
      {
         // Initialize from data object
         auto source = WBFL::DManip::DragDataSource::Create();
         source->SetDataObject(pDataObject);

         // rebuild the display object from the data source
         legRep->OnDrop(source);
      }

      return std::dynamic_pointer_cast<WBFL::DManip::iDisplayObject>(legRep);
   }
   else if ( cfFormat == CSupportEvents::ms_Format )
   {
      auto SupportRep = WBFL::DManip::PointDisplayObject::Create();

      auto pDrawStrategy = std::make_shared<CSupportDrawStrategyImpl>(m_pDoc);
      SupportRep->SetDrawingStrategy(pDrawStrategy);

      auto pEvents = std::make_shared<CSupportEvents>(m_pDoc);
      SupportRep->RegisterEventSink(pEvents);
      SupportRep->SetDragData(pEvents);

      if ( pDataObject )
      {
         // Initialize from data object
         auto source = WBFL::DManip::DragDataSource::Create();
         source->SetDataObject(pDataObject);

         // rebuild the display object from the data source
         SupportRep->OnDrop(source);
      }

      return SupportRep;
   }
   else if ( cfFormat == CTemporarySupportEvents::ms_Format )
   {
      auto TemporarySupportRep = WBFL::DManip::PointDisplayObject::Create();

      auto pDrawStrategy = std::make_shared<CTemporarySupportDrawStrategyImpl>(m_pDoc);
      TemporarySupportRep->SetDrawingStrategy(pDrawStrategy);

      auto pEvents = std::make_shared<CTemporarySupportEvents>(m_pDoc);
      TemporarySupportRep->RegisterEventSink(pEvents);
      TemporarySupportRep->SetDragData(pEvents);

      if ( pDataObject )
      {
         // Initialize from data object
         auto source = WBFL::DManip::DragDataSource::Create();
         source->SetDataObject(pDataObject);

         // rebuild the display object from the data source
         TemporarySupportRep->OnDrop(source);
      }

      return TemporarySupportRep;
   }
   else if ( cfFormat == CLBAMTruckDisplayImpl::ms_Format )
   {
      auto TruckRep = WBFL::DManip::PointDisplayObject::Create();

      auto pDisplayImpl = std::make_shared<CLBAMTruckDisplayImpl>();
      TruckRep->SetDrawingStrategy(pDisplayImpl);
      TruckRep->RegisterEventSink(pDisplayImpl);
      TruckRep->SetDragData(pDisplayImpl);

      if ( pDataObject )
      {
         // Initialize from data object
         auto source = WBFL::DManip::DragDataSource::Create();
         source->SetDataObject(pDataObject);

         // rebuild the display object from the data source
         TruckRep->OnDrop(source);
      }

      return TruckRep;
   }
   else
   {
      return m_Factory->Create(cfFormat,pDataObject);
   }
}
