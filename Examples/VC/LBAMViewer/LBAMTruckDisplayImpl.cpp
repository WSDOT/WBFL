#include "stdafx.h"
#include "LBAMTruckDisplayImpl.h"
#include "mfcdual.h"
#include <MathEx.h>
#include "ListID.h"
#include "LBAMViewerGuid.c"
#include "EditTruckPosition.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

UINT CLBAMTruckDisplayImpl::ms_Format = ::RegisterClipboardFormat(_T("LBAMTruckData"));

CLBAMTruckDisplayImpl::CLBAMTruckDisplayImpl():
m_RoadwayElevation(0.0),
m_Color(RGB(0,0,220)),
m_Dirty(true),
m_PlacementCookie(0)
{
   EnableAutomation ();
 
   HRESULT hr = m_Placement.CoCreateInstance( CLSID_LiveLoadConfiguration);
   ATLASSERT(SUCCEEDED(hr));
}

CLBAMTruckDisplayImpl::~CLBAMTruckDisplayImpl()
{
   IDispatch* pid = this->GetIDispatch(FALSE);
   AfxConnectionUnadvise (m_Placement, IID_ILiveLoadConfigurationEvents,
                          pid, FALSE, 
                          m_PlacementCookie);

}

BEGIN_MESSAGE_MAP(CLBAMTruckDisplayImpl, CCmdTarget)
	//{{AFX_MSG_MAP(CLBAMTruckDisplayImpl)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_INTERFACE_MAP(CLBAMTruckDisplayImpl,CCmdTarget)
   INTERFACE_PART(CLBAMTruckDisplayImpl,IID_iDrawPointStrategy,DrawPointStrategy)
   INTERFACE_PART(CLBAMTruckDisplayImpl,IID_iLBAMTruckDrawStrategy,Strategy)
   INTERFACE_PART(CLBAMTruckDisplayImpl,IID_iLBAMTruckEvents,Events)
   INTERFACE_PART(CLBAMTruckDisplayImpl,IID_iDisplayObjectEvents,DisplayObjectEvents)
   INTERFACE_PART(CLBAMTruckDisplayImpl,IID_iDragData,DragData)
   INTERFACE_PART(CLBAMTruckDisplayImpl,IID_ILiveLoadConfigurationEvents,LiveLoadEvents)
END_INTERFACE_MAP()

DELEGATE_CUSTOM_INTERFACE(CLBAMTruckDisplayImpl,DrawPointStrategy);
DELEGATE_CUSTOM_INTERFACE(CLBAMTruckDisplayImpl,Strategy);
DELEGATE_CUSTOM_INTERFACE(CLBAMTruckDisplayImpl,Events);
DELEGATE_CUSTOM_INTERFACE(CLBAMTruckDisplayImpl,DisplayObjectEvents);
DELEGATE_CUSTOM_INTERFACE(CLBAMTruckDisplayImpl,DragData);
DELEGATE_CUSTOM_INTERFACE(CLBAMTruckDisplayImpl,LiveLoadEvents);

// This goes in the source code file
 // Note: ClassWizard looks for these comments:
 BEGIN_DISPATCH_MAP(CLBAMTruckDisplayImpl, CCmdTarget)
     //{{AFX_DISPATCH_MAP(AClassWithAutomation)
        // NOTE - the ClassWizard will add and remove mapping macros here.
     //}}AFX_DISPATCH_MAP
 END_DISPATCH_MAP()
 

STDMETHODIMP_(void) CLBAMTruckDisplayImpl::XEvents::Init(iPointDisplayObject* pDO, ILBAMModel* model, LiveLoadModelType llType, VehicleIndexType vehicleIndex, ILiveLoadConfiguration* placement)
{
   METHOD_PROLOGUE(CLBAMTruckDisplayImpl,Events);

   HRESULT hr;
   // get our vehicular load
   CComPtr<ILiveLoad> liveload;
   hr = model->get_LiveLoad(&liveload);
   ATLASSERT(SUCCEEDED(hr));

   CComPtr<ILiveLoadModel> llm;
   switch (llType)
   {
   case lltDeflection:
      hr = liveload->get_Deflection(&llm);
      break;
   case lltDesign:
      hr = liveload->get_Design(&llm);
      break;
   case lltPedestrian:
      hr = liveload->get_Pedestrian(&llm);
      break;
   case lltFatigue:
      hr = liveload->get_Fatigue(&llm);
      break;
   case lltPermit:
      hr = liveload->get_Permit(&llm);
      break;
   case lltSpecial:
      hr = liveload->get_Special(&llm);
      break;

   case lltLegalRoutineRating:
      hr = liveload->get_LegalRoutineRating(&llm);
      break;

   case lltLegalSpecialRating:
      hr = liveload->get_LegalSpecialRating(&llm);
      break;

   case lltPermitRoutineRating:
      hr = liveload->get_PermitRoutineRating(&llm);
      break;

   case lltPermitSpecialRating:
      hr = liveload->get_PermitSpecialRating(&llm);
      break;

   default:
      ATLASSERT(0);
   };


   ATLASSERT(SUCCEEDED(hr));

   CComPtr<IVehicularLoads> vls;
   hr = llm->get_VehicularLoads(&vls);
   ATLASSERT(SUCCEEDED(hr));

   hr = vls->get_Item(vehicleIndex, &(pThis->m_VehicularLoad));
   ATLASSERT(SUCCEEDED(hr));
#pragma Reminder("This class needs to listen to the model for vehicle changes in order to be robust")

   // use placement to listen for events
   pThis->m_Placement = placement;

   IDispatch* pid = pThis->GetIDispatch(FALSE);
   if (!AfxConnectionAdvise (placement,
        IID_ILiveLoadConfigurationEvents, pid, FALSE,
        &pThis->m_PlacementCookie))
   {
      ATLASSERT(0);
   }

   pThis->m_Dirty = true;
}

void CLBAMTruckDisplayImpl::Compute(iPointDisplayObject* pDO)
{
   // compute local parameters if things get stale
   if (m_Dirty)
   {

      // save off truck axle spacing and bounding box;
      CacheTruckParameters();

      double position;
      m_Placement->get_TruckPosition(&position);
      UpdateTruckPosition(pDO, position);

      m_Dirty = false;
   }
}

void CLBAMTruckDisplayImpl::UpdateTruckPosition(iPointDisplayObject* pDO, double location)
{
   // position is middle of truck
   double length =0.0;
   if (m_AxleLocations.size()>0)
   {
      length = m_AxleLocations.back();
   }

   double xloc = location+length/2.0;
   CComPtr<IPoint2d> pnt;
   pnt.CoCreateInstance(CLSID_Point2d);
   pnt->put_X(xloc);
   pnt->put_Y( m_RoadwayElevation + (m_WheelDiameter + m_TrailerHeight)/2. );
   pDO->SetPosition(pnt, FALSE, FALSE);
}


STDMETHODIMP_(void) CLBAMTruckDisplayImpl::XEvents::GetLiveLoadConfiguration(ILiveLoadConfiguration** placement)
{
   METHOD_PROLOGUE(CLBAMTruckDisplayImpl,Events);

   HRESULT hr = pThis->m_Placement.CopyTo(placement);
}


STDMETHODIMP_(void) CLBAMTruckDisplayImpl::XEvents::GetRoadwayElevation(double *pVal)
{
   METHOD_PROLOGUE(CLBAMTruckDisplayImpl,Events);

   *pVal = pThis->m_RoadwayElevation;
}

STDMETHODIMP_(void) CLBAMTruckDisplayImpl::XEvents::SetRoadwayElevation(iPointDisplayObject* pDO, double newVal)
{
   METHOD_PROLOGUE(CLBAMTruckDisplayImpl,Events);

   pThis->m_RoadwayElevation = newVal;

   pThis->m_Dirty = true;
}


STDMETHODIMP_(void) CLBAMTruckDisplayImpl::XStrategy::SetColor(COLORREF color)
{
   METHOD_PROLOGUE(CLBAMTruckDisplayImpl,Strategy);
   pThis->m_Color = color;
}


STDMETHODIMP_(void) CLBAMTruckDisplayImpl::XDrawPointStrategy::Draw(iPointDisplayObject* pDO,CDC* pDC)
{
   METHOD_PROLOGUE(CLBAMTruckDisplayImpl,DrawPointStrategy);

   CComPtr<iDisplayList> pDL;
   pDO->GetDisplayList(&pDL);

   CComPtr<iDisplayMgr> pDispMgr;
   pDL->GetDisplayMgr(&pDispMgr);

   COLORREF color;

   if ( pDO->IsSelected() )
      color = pDispMgr->GetSelectionLineColor();
   else
      color = pThis->m_Color;

   CComPtr<IPoint2d> pos;
   pDO->GetPosition(&pos);

   pThis->Draw(pDO,pDC,color,pos);
}

STDMETHODIMP_(void) CLBAMTruckDisplayImpl::XDrawPointStrategy::DrawHighlite(iPointDisplayObject* pDO,CDC* pDC,BOOL bHighlite)
{
   METHOD_PROLOGUE(CLBAMTruckDisplayImpl,DrawPointStrategy);
   Draw(pDO,pDC);
}

STDMETHODIMP_(void) CLBAMTruckDisplayImpl::XDrawPointStrategy::DrawDragImage(iPointDisplayObject* pDO,CDC* pDC, iCoordinateMap* map, const CPoint& dragStart, const CPoint& cpdragPoint)
{
   METHOD_PROLOGUE(CLBAMTruckDisplayImpl,DrawPointStrategy);

   CComPtr<IPoint2d> dragPoint;
   map->LPtoWP(cpdragPoint.x, cpdragPoint.y, &dragPoint);

   pThis->Draw(pDO,pDC,RGB(150,150,150),dragPoint);
}

STDMETHODIMP_(void) CLBAMTruckDisplayImpl::XDrawPointStrategy::GetBoundingBox(iPointDisplayObject* pDO,IRect2d** pBox)
{
   METHOD_PROLOGUE(CLBAMTruckDisplayImpl,DrawPointStrategy);

   pThis->Compute(pDO);

   CComPtr<iDisplayList> pDL;
   pDO->GetDisplayList(&pDL);
   CComPtr<iDisplayMgr> pDispMgr;
   pDL->GetDisplayMgr(&pDispMgr);
   CComPtr<iCoordinateMap> pMap;
   pDispMgr->GetCoordinateMap(&pMap);

   double dx=0, dy=0;

   if ( pThis->m_AxleLocations.size() > 1)
   {
      dx = (fabs(pThis->m_AxleLocations.back()) + 2*pThis->m_WheelDiameter) / 2.0;
      dy = (pThis->m_TrailerHeight + pThis->m_WheelDiameter) / 2.0;
   }

   CComPtr<IPoint2d> point;
   pDO->GetPosition(&point);
   double xp, yp;
   point->get_X(&xp);
   point->get_Y(&yp);

   CComPtr<IRect2d> box;
   box.CoCreateInstance(CLSID_Rect2d);

   box->put_Right(xp + dx);
   box->put_Left(xp - dx);
   box->put_Top(yp + dy);
   box->put_Bottom(yp - dy);

   (*pBox) = box;
   (*pBox)->AddRef();
}

void CLBAMTruckDisplayImpl::Draw(iPointDisplayObject* pDO,CDC* pDC,COLORREF color,IPoint2d* userLoc)
{
   Compute(pDO);

   CComPtr<iDisplayList> pDL;
   pDO->GetDisplayList(&pDL);

   CComPtr<iDisplayMgr> pDispMgr;
   pDL->GetDisplayMgr(&pDispMgr);

   CComPtr<iCoordinateMap> pMap;
   pDispMgr->GetCoordinateMap(&pMap);

   // set up some constants
   AxleIndexType num_wheels = m_AxleLocations.size();
   if (1 < num_wheels)
   {
      AxleIndexType pivotAxleIndex;
      m_Placement->get_PivotAxleIndex(&pivotAxleIndex);

      double pivot_axle_offset = m_AxleLocations[pivotAxleIndex];

      // get location of first wheel on roadway
      double fwx, fwy;
      userLoc->get_X(&fwx);
      fwx -= m_AxleLocations.back()/2.; // point location is at center of truck
      fwy = m_RoadwayElevation;

      CPen   black_pen(PS_SOLID,1,RGB(0,0,0));
      CBrush black_brush(RGB(0,0,0));
      CBrush truck_brush(color);
      CPen* old_pen = pDC->SelectObject(&black_pen);
      CBrush* old_brush = pDC->SelectObject(&truck_brush);

      TruckDirectionType direction;
      HRESULT hr = m_Placement->get_TruckDirection(&direction);
      ATLASSERT(SUCCEEDED(hr));

      long tdf = direction==ltdForward ? -1 : 1;

      // draw cab
      double offset;
      double cab_hgt;
      if (num_wheels>2)
      {
         cab_hgt = m_CabHeight;
         offset = m_WheelDiameter;
      }
      else
      {
         cab_hgt = m_TrailerHeight; // make two-wheeled trucks higher
         offset = 0.0;
      }

      double first_spc = fabs( m_AxleLocations[1] - m_AxleLocations[0] );
      RECT rect;
      double l,r,t,b;
      b = fwy + m_WheelDiameter/2.;
      t = b + m_CabHeight;
      if ( direction == ltdForward )
      {
         l = fwx + m_AxleLocations[1] + offset - pivot_axle_offset;
         r = l + first_spc; 
      }
      else
      {
         r = fwx + m_AxleLocations[1] - offset - pivot_axle_offset;
         l = r - first_spc; 
      }

      pMap->WPtoLP(l,t,&(rect.left),&(rect.top));
      pMap->WPtoLP(r,b,&(rect.right),&(rect.bottom));
      
      pDC->Rectangle(&rect);

      // draw trailer
      if (2 < num_wheels)
      {
         double trailer_length = fabs(m_AxleLocations[num_wheels-1] - m_AxleLocations[1]);
         b = fwy + m_WheelDiameter/2.;
         t = m_TrailerHeight + b;
         if (direction==ltdForward)
         {
            r = l;
            l = r - trailer_length - 2*m_WheelDiameter;
         }
         else
         {
            l = r;
            r = l + trailer_length + 2*m_WheelDiameter;
         }

         pMap->WPtoLP(l,t,&(rect.left),&(rect.top));
         pMap->WPtoLP(r,b,&(rect.right),&(rect.bottom));
      
         pDC->Rectangle(&rect);
      }

      // draw wheels
      pDC->SelectObject(&black_brush);
      b = fwy;
      t = b + m_WheelDiameter;


      for(AxleIndexType iw = 0; iw < num_wheels; iw++)
      {
         double xloc = fwx + m_AxleLocations[iw] - pivot_axle_offset;
         l = xloc - m_WheelDiameter/2;
         r = xloc + m_WheelDiameter/2;

         pMap->WPtoLP(l,t,&(rect.left),&(rect.top));
         pMap->WPtoLP(r,b,&(rect.right),&(rect.bottom));
      
         pDC->Ellipse(&rect);
      }

      pDC->SelectObject(old_pen);
      pDC->SelectObject(old_brush);
   }
}

STDMETHODIMP_(void) CLBAMTruckDisplayImpl::XDisplayObjectEvents::OnChanged(iDisplayObject* pDO)
{
   METHOD_PROLOGUE(CLBAMTruckDisplayImpl,DisplayObjectEvents);

   // not sure how this would ever get called
   pThis->m_Dirty = true;
}

STDMETHODIMP_(void) CLBAMTruckDisplayImpl::XDisplayObjectEvents::OnDragMoved(iDisplayObject* pDO,ISize2d* offset)
{
   METHOD_PROLOGUE(CLBAMTruckDisplayImpl,DisplayObjectEvents);

   double pos;
   pThis->m_Placement->get_TruckPosition(&pos);

   double xoff;
   offset->get_Dx(&xoff);

   pos += xoff;

   CComQIPtr<iPointDisplayObject,&IID_iPointDisplayObject> ppdo(pDO);
   ATLASSERT(ppdo!=NULL);

   pThis->m_Placement->put_TruckPosition(pos);

   pThis->m_Dirty = true;
}

STDMETHODIMP_(void) CLBAMTruckDisplayImpl::XDisplayObjectEvents::OnMoved(iDisplayObject* pDO)
{
   METHOD_PROLOGUE(CLBAMTruckDisplayImpl,DisplayObjectEvents);

   ASSERT(FALSE); // Points must be dropped on a member. This event should never occur
}

STDMETHODIMP_(void) CLBAMTruckDisplayImpl::XDisplayObjectEvents::OnCopied(iDisplayObject* pDO)
{
   ASSERT(FALSE); // Points must be dropped on a member. This event should never occur
}

STDMETHODIMP_(bool) CLBAMTruckDisplayImpl::XDisplayObjectEvents::OnLButtonDblClk(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
   METHOD_PROLOGUE(CLBAMTruckDisplayImpl,DisplayObjectEvents);
   pThis->EditTruckPosition();

   return true;
}

STDMETHODIMP_(bool) CLBAMTruckDisplayImpl::XDisplayObjectEvents::OnLButtonDown(iDisplayObject* pDO,UINT nFlags,CPoint point)
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

STDMETHODIMP_(bool) CLBAMTruckDisplayImpl::XDisplayObjectEvents::OnRButtonUp(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
   METHOD_PROLOGUE(CLBAMTruckDisplayImpl,DisplayObjectEvents);
   return false;
}

STDMETHODIMP_(bool) CLBAMTruckDisplayImpl::XDisplayObjectEvents::OnLButtonUp(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
   METHOD_PROLOGUE(CLBAMTruckDisplayImpl,DisplayObjectEvents);
   return false;
}


STDMETHODIMP_(bool) CLBAMTruckDisplayImpl::XDisplayObjectEvents::OnRButtonDblClk(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
   METHOD_PROLOGUE(CLBAMTruckDisplayImpl,DisplayObjectEvents);
   return false;
}

STDMETHODIMP_(bool) CLBAMTruckDisplayImpl::XDisplayObjectEvents::OnRButtonDown(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
   METHOD_PROLOGUE(CLBAMTruckDisplayImpl,DisplayObjectEvents);
   return false;
}

STDMETHODIMP_(bool) CLBAMTruckDisplayImpl::XDisplayObjectEvents::OnMouseMove(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
   METHOD_PROLOGUE(CLBAMTruckDisplayImpl,DisplayObjectEvents);
   return false;
}

STDMETHODIMP_(bool) CLBAMTruckDisplayImpl::XDisplayObjectEvents::OnMouseWheel(iDisplayObject* pDO,UINT nFlags,short zDelta,CPoint point)
{
   METHOD_PROLOGUE(CLBAMTruckDisplayImpl,DisplayObjectEvents);
   return false;
}

STDMETHODIMP_(bool) CLBAMTruckDisplayImpl::XDisplayObjectEvents::OnKeyDown(iDisplayObject* pDO,UINT nChar, UINT nRepCnt, UINT nFlags)
{
   METHOD_PROLOGUE(CLBAMTruckDisplayImpl,DisplayObjectEvents);

   switch(nChar)
   {
   case VK_RIGHT:
   case VK_LEFT:
      {
         double pos;
         pThis->m_Placement->get_TruckPosition(&pos);

         double xoff = nChar==VK_RIGHT ? 1.0 : -1.0;
         pos += xoff;

         pThis->m_Placement->put_TruckPosition(pos);
         pThis->m_Dirty = true;
      }
      break;
      break;
   case VK_RETURN:
   case VK_DELETE:
      ATLASSERT(0);
   }

   return true;
}

STDMETHODIMP_(bool) CLBAMTruckDisplayImpl::XDisplayObjectEvents::OnContextMenu(iDisplayObject* pDO,CWnd* pWnd,CPoint point)
{
   METHOD_PROLOGUE(CLBAMTruckDisplayImpl,DisplayObjectEvents);
   return false;
}

STDMETHODIMP_(void) CLBAMTruckDisplayImpl::XDisplayObjectEvents::OnSelect(iDisplayObject* pDO)
{
}

STDMETHODIMP_(void) CLBAMTruckDisplayImpl::XDisplayObjectEvents::OnUnselect(iDisplayObject* pDO)
{
}

STDMETHODIMP_(UINT) CLBAMTruckDisplayImpl::XDragData::Format()
{
   return ms_Format;
}

STDMETHODIMP_(BOOL) CLBAMTruckDisplayImpl::XDragData::PrepareForDrag(iDisplayObject* pDO,iDragDataSink* pSink)
{
   METHOD_PROLOGUE(CLBAMTruckDisplayImpl,DragData);

   // Create a place to store the drag data for this object
   pSink->CreateFormat(ms_Format);

   // write pointers
   pSink->Write(ms_Format,&pThis->m_Placement.p,sizeof(ILiveLoadConfiguration*));
   pSink->Write(ms_Format,&pThis->m_VehicularLoad.p,sizeof(IVehicularLoad*));

   // road elevation
   pSink->Write(ms_Format,&pThis->m_RoadwayElevation,sizeof(double));

   // write cached truck drawing information
   AxleIndexType size = pThis->m_AxleLocations.size();
   pSink->Write(ms_Format,&size,sizeof(AxleIndexType));
   for ( AxleIndexType i=0; i<size; i++)
   {
      pSink->Write(ms_Format,&pThis->m_AxleLocations[i],sizeof(double));
   }

   for ( AxleIndexType i=0; i<size; i++)
   {
      pSink->Write(ms_Format,&pThis->m_ActiveAxles[i],sizeof(bool));
   }

   pSink->Write(ms_Format,&pThis->m_WheelDiameter,sizeof(double));
   pSink->Write(ms_Format,&pThis->m_CabHeight,sizeof(double));
   pSink->Write(ms_Format,&pThis->m_TrailerHeight,sizeof(double));

   return TRUE;
}

STDMETHODIMP_(void) CLBAMTruckDisplayImpl::XDragData::OnDrop(iDisplayObject* pDO,iDragDataSource* pSource)
{
   METHOD_PROLOGUE(CLBAMTruckDisplayImpl,DragData);

   // Tell the source we are about to read from our format
   pSource->PrepareFormat(ms_Format);

   // read pointers
   ILiveLoadConfiguration* pvp;
   pSource->Read(ms_Format,&pvp,sizeof(ILiveLoadConfiguration*));
   pThis->m_Placement = pvp;

   IVehicularLoad* pvl;
   pSource->Read(ms_Format, &pvl, sizeof(IVehicularLoad*));
   pThis->m_VehicularLoad = pvl;

   // road elevation
   pSource->Read(ms_Format,&pThis->m_RoadwayElevation,sizeof(double));

   // write cached truck drawing information
   long size;
   pSource->Read(ms_Format,&size,sizeof(long));
   pThis->m_AxleLocations.reserve(size);

   for ( long i=0; i<size; i++)
   {
      double d;
      pSource->Read(ms_Format,&d,sizeof(double));
      pThis->m_AxleLocations.push_back(d);
   }

   for ( long i=0; i<size; i++)
   {
      bool b;
      pSource->Read(ms_Format,&b,sizeof(bool));
      pThis->m_ActiveAxles.push_back(b);
   }

   pSource->Read(ms_Format,&pThis->m_WheelDiameter,sizeof(double));
   pSource->Read(ms_Format,&pThis->m_CabHeight,sizeof(double));
   pSource->Read(ms_Format,&pThis->m_TrailerHeight,sizeof(double));

}

void CLBAMTruckDisplayImpl::EditTruck()
{
}

void CLBAMTruckDisplayImpl::CacheTruckParameters()
{
   m_AxleLocations.clear();

   HRESULT hr;
   CComPtr<IAxles> axles;
   hr = m_VehicularLoad->get_Axles(&axles);
   ATLASSERT(SUCCEEDED(hr));

   AxleIndexType axle_cnt;
   hr = axles->get_Count(&axle_cnt);
   ATLASSERT(SUCCEEDED(hr));

   // nothing to do if there are no axles
   if (axle_cnt>0)
   {
      m_AxleLocations.reserve(axle_cnt);
      m_ActiveAxles.assign(axle_cnt,false);

      AxleIndexType var_axle_idx;
      hr = m_VehicularLoad->get_VariableAxle(&var_axle_idx);
      ATLASSERT(SUCCEEDED(hr));

      double max_var_axle_spacing;
      hr = m_VehicularLoad->get_VariableMaxSpacing(&max_var_axle_spacing);
      ATLASSERT(SUCCEEDED(hr));

      double var_axle_spacing;
      hr = m_Placement->get_VariableSpacing(&var_axle_spacing);
      ATLASSERT(SUCCEEDED(hr));

      // Some error checking
      if (var_axle_idx>=0)
      {
         if (var_axle_idx>axle_cnt-2)
         {
            ATLASSERT(0);
         }
      }

      // See if we are picking up any axles
      bool is_axle_config;
      CComPtr<IIndexArray> axle_config;
      hr = m_Placement->get_AxleConfig(&axle_config);
      ATLASSERT(SUCCEEDED(hr));

      CollectionIndexType axle_config_size = 0;
      axle_config->get_Count(&axle_config_size);

      if (axle_config_size>0)
      {
         is_axle_config = true;
      }
      else
      {
          is_axle_config = false;
      }

      // Locate unfactored axles as if truck is moving backward
      double loc = 0;
      double spacing=0.0;
      for (AxleIndexType i=0; i<axle_cnt; i++)
      {
         CComPtr<IAxle> axle;
         hr = axles->get_Item(i, &axle);
         ATLASSERT(SUCCEEDED(hr));

         // Add our axle
         m_AxleLocations.push_back( loc );

         // Only apply axle if it's in current configuration
         m_ActiveAxles[i] = true;
         if ( is_axle_config )
         {
            CollectionIndexType fidx;
            HRESULT hresult = axle_config->Find(i,&fidx);
            if (FAILED(hresult))
            {
               m_ActiveAxles[i] = false;
            }
         }

         hr = axle->get_Spacing(&spacing);
         ATLASSERT(SUCCEEDED(hr));

         if (i==var_axle_idx)
         {
            // we are at variable axle
            double min_var_axle_spacing = spacing;
            spacing = var_axle_spacing;

            // error check
            if (var_axle_spacing<min_var_axle_spacing || var_axle_spacing>max_var_axle_spacing)
            {
               ATLASSERT(0); 
            }
         }

         loc += spacing;
      }

      // deal with truck direction
      TruckDirectionType direction;
      hr = m_Placement->get_TruckDirection(&direction);
      ATLASSERT(SUCCEEDED(hr));

      long tdf = direction==ltdForward ? -1 : 1;

      for (AxleIndexType i=0; i<axle_cnt; i++)
      {
         m_AxleLocations[i] *= tdf;
      }
   }

   // cache off some constants
   // truck geometry is based on spacing between first two wheels
   double first_spc = fabs( m_AxleLocations[1] - m_AxleLocations[0] );
   if (first_spc==0)
   {
      first_spc = fabs( m_AxleLocations[axle_cnt-1] );
      if (first_spc==0)
      {
         ATLASSERT(0); // zero-length truck?
         return;
      }
   }

   m_WheelDiameter   = first_spc/4;
   m_CabHeight       = first_spc/2;
   m_TrailerHeight   = first_spc*0.75;
}


HRESULT CLBAMTruckDisplayImpl::XLiveLoadEvents::OnLiveLoadConfigurationChanged(ILiveLoadConfiguration* placement)
{
   METHOD_PROLOGUE(CLBAMTruckDisplayImpl,LiveLoadEvents);

   pThis->m_Dirty = true;

   return S_OK;
}


void CLBAMTruckDisplayImpl::EditTruckPosition()
{
   double position;
   m_Placement->get_TruckPosition(&position);
   TruckDirectionType direction;
   m_Placement->get_TruckDirection(&direction);

   double varspcg;
   m_Placement->get_VariableSpacing(&varspcg);
   AxleIndexType var_axle;
   m_VehicularLoad->get_VariableAxle(&var_axle);
   bool is_var = var_axle>=0 ? true : false;

   double min_varspcg=0, max_varspcg=0;

   CComPtr<IAxles> axles;
   m_VehicularLoad->get_Axles(&axles);
   AxleIndexType nAxles;
   axles->get_Count(&nAxles);

   if (is_var)
   {
      CComPtr<IAxle> axle;
      axles->get_Item(var_axle, &axle);
      axle->get_Spacing(&min_varspcg);
      m_VehicularLoad->get_VariableMaxSpacing(&max_varspcg);
   }

   AxleIndexType pivotAxleIndex;
   m_Placement->get_PivotAxleIndex(&pivotAxleIndex);

   VARIANT_BOOL apply_impact;
   m_Placement->get_DoApplyImpact(&apply_impact);

   CEditTruckPosition dlg;
   dlg.Init( position, direction, is_var, varspcg, min_varspcg, max_varspcg, apply_impact, nAxles, pivotAxleIndex);
   INT_PTR st = dlg.DoModal();
   if (st==IDOK)
   {
      if (dlg.m_TruckPosition != position)
         m_Placement->put_TruckPosition(dlg.m_TruckPosition);

      if (dlg.m_PivotAxleIndex != pivotAxleIndex )
         m_Placement->put_PivotAxleIndex(dlg.m_PivotAxleIndex);

      if (dlg.m_Direction != direction)
         m_Placement->put_TruckDirection(dlg.m_Direction);

      if (is_var && dlg.m_VariableAxleSpacing!=varspcg)
         m_Placement->put_VariableSpacing(dlg.m_VariableAxleSpacing);

      if (apply_impact!=dlg.m_ApplyImpact)
      {
         apply_impact = dlg.m_ApplyImpact==TRUE? VARIANT_TRUE : VARIANT_FALSE;
         m_Placement->put_DoApplyImpact(apply_impact);
      }
   }
}