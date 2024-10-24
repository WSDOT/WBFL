// LBAMViewerView.cpp : implementation of the CLBAMViewerView class
//

#include "stdafx.h"
#include "math.h"
#include <MathEx.h>

#include "LBAMViewer.h"

#include "LBAMViewerDoc.h"
#include "LBAMViewerView.h"

#include "DisplayObjectFactory.h"
#include "ListID.h"

#include "SupportEvents.h"
#include "SupportDrawStrategy.h"
#include "TemporarySupportEvents.h"
#include "TemporarySupportDrawStrategy.h"

#include "LBAMTruckDisplayImpl.h"
#include "LBAMViewerGuid.c"

#include "DataSetBuilder.h"

#include <ProgressMonitorUtils.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define DRW_OFFSET 100

// useful local functions
void BuildSegmentDisplayObjects(CString& Stage, double xStart, double yStart, double xEnd, double yEnd, std::shared_ptr<iDisplayList> pDL, ISuperstructureMember* ssm, long* pCurrID);


bool GetPointAlongLineSegment(double xStart, double yStart, double xEnd, double yEnd, double dist, double* xLoc, double* yLoc)
{
   // returns true if location is within segment. not necessarily an error - but worth checking for some applications
   bool is_within = true;

   double dx = xEnd-xStart;
   double dy = yEnd-yStart;
   double len = sqrt(dx*dx + dy*dy);

   ASSERT(len!=0.0);

   // dist is distance from start point along line
   // check if location is within line bounds
   if (dist<0.0 || dist>len)
      is_within = false;

   // check out extreme cases
   if (dx==0.0)
   {
      // vertical line
      *xLoc = xStart;
      *yLoc = yStart+dist;
   }
   else if (dy==0.0)
   {
      // horizontal line
      *xLoc = xStart+dist;
      *yLoc = yStart;
   }
   else
   {
      // sloped line
      double rat = dist/len;
      *xLoc = xStart + rat*dx;
      *yLoc = yStart + rat*dy;
   }

   return is_within;
}


/////////////////////////////////////////////////////////////////////////////
// CLBAMViewerView

IMPLEMENT_DYNCREATE(CLBAMViewerView, CDisplayView)

BEGIN_MESSAGE_MAP(CLBAMViewerView, CDisplayView)
	//{{AFX_MSG_MAP(CLBAMViewerView)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CDisplayView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CDisplayView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CDisplayView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLBAMViewerView construction/destruction

CLBAMViewerView::CLBAMViewerView():
m_CurrentStageIndex(-1),
m_RoadwayElevation(0),
m_First(true),
m_FirstSize(true),
m_DoUpdate(true)
{

}

CLBAMViewerView::~CLBAMViewerView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CLBAMViewerView drawing

void CLBAMViewerView::OnDraw(CDC* pDC)
{
	CLBAMViewerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

   CDisplayView::OnDraw(pDC);

}

/////////////////////////////////////////////////////////////////////////////
// CLBAMViewerView printing

BOOL CLBAMViewerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLBAMViewerView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
   CDisplayView::OnBeginPrinting(pDC, pInfo);
}

void CLBAMViewerView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
   CDisplayView::OnEndPrinting(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CLBAMViewerView diagnostics

#ifdef _DEBUG
void CLBAMViewerView::AssertValid() const
{
	CDisplayView::AssertValid();
}

void CLBAMViewerView::Dump(CDumpContext& dc) const
{
	CDisplayView::Dump(dc);
}

CLBAMViewerDoc* CLBAMViewerView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLBAMViewerDoc)));
	return (CLBAMViewerDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLBAMViewerView message handlers
DROPEFFECT CLBAMViewerView::CanDrop(COleDataObject* pDataObject,DWORD dwKeyState,IPoint2d* point)
{
   // This override has to determine if the thing being dragged over it can
   // be dropped. In order to do that, it must unpackage the OleDataObject.
   //
   // The stuff in the data object is just from the display object. The display
   // objects need to be updated so that the client can attach an object to it
   // that knows how to package up domain specific information. At the same
   // time, this view needs to be able to get some domain specific hint 
   // as to the type of data that is going to be dropped.

   if ( pDataObject->IsDataAvailable(CLBAMTruckDisplayImpl::ms_Format) )
   {
      return DROPEFFECT_MOVE;
   }
   else
   {
      auto drag = std::dynamic_pointer_cast<iDraggable>(m_Legend);
      UINT format = drag->Format();
      if ( pDataObject->IsDataAvailable(format) )
         return DROPEFFECT_MOVE;
   }

   return DROPEFFECT_NONE;
}

void CLBAMViewerView::OnDropped(COleDataObject* pDataObject,DROPEFFECT dropEffect,IPoint2d* point)
{
   AfxMessageBox(_T("OnDropped"));
}


void CLBAMViewerView::OnInitialUpdate() 
{
   try
   {
      CDisplayView::OnInitialUpdate();

      // Setup the local display object factory
      CLBAMViewerDoc* pDoc = GetDocument();
      auto dispMgr = GetDisplayMgr();
      auto factory = std::make_shared<CDisplayObjectFactory>(pDoc);
      dispMgr->AddDisplayObjectFactory(factory);

      // factory from dmaniptools
      //CComPtr<iDisplayObjectFactory> pfac2;
      //hr = pfac2.CoCreateInstance(CLSID_DManipToolsDisplayObjectFactory);
      //ATLASSERT(SUCCEEDED(hr));
      //dispMgr->AddDisplayObjectFactory(pfac2);

      // Create display lists
      // dimension lines
      auto dlList = WBFL::DManip::DisplayList::Create(DIMLINE_LIST);
      dispMgr->AddDisplayList(dlList);

      // supports
      auto sup_list = WBFL::DManip::DisplayList::Create(SUPPORT_LIST);
      dispMgr->AddDisplayList(sup_list);

      // temporary supports
      auto ts_list = WBFL::DManip::DisplayList::Create(TEMPSUPPORT_LIST);
      dispMgr->AddDisplayList(ts_list);

      // spans
      auto span_list = WBFL::DManip::DisplayList::Create(SPAN_LIST);
      dispMgr->AddDisplayList(span_list);

      // superstructuremembers
      auto ssm_list = WBFL::DManip::DisplayList::Create(SSM_LIST);
      dispMgr->AddDisplayList(ssm_list);

      // graph
      auto graph_list = WBFL::DManip::DisplayList::Create(GRAPH_LIST);

      // legend
      auto legend_list = WBFL::DManip::DisplayList::Create(LEGEND_LIST);
      dispMgr->AddDisplayList(legend_list);

      // truck
      auto truck_list = WBFL::DManip::DisplayList::Create(TRUCK_LIST);
      dispMgr->AddDisplayList(truck_list);

      // Make sure mapping has a DC
      CDManipClientDC dc(this);

      // create our one and only graph display object
      m_Graph = CGraphXyDisplayObject::Create();
      graph_list->AddDisplayObject(m_Graph);

      // create our one and only legend display object
      m_Legend = CLegendDisplayObject::Create();
      m_Legend->SetTitle(_T("Legend"));
      legend_list->AddDisplayObject(m_Legend);


      EnableToolTips();

      this->OnUpdate(this, 0, NULL);
   }
   catch(...)
   {
      DealWithExceptions();
   }
}

void CLBAMViewerView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
   HRESULT hr;

   // don't draw anything when called by on initial update

   if (m_First)
   {
      m_First = false;
      return;
   }

   // use a mutex to block update from being reentrant
   if (!m_DoUpdate) 
      return;

   SimpleMutex mutex(m_DoUpdate); // exception safe

   try
   {
      CFrameWnd* frame = GetParentFrame( );

      CLBAMViewerDoc* pDoc = GetDocument();
      CComPtr<ILBAMModel> model = pDoc->m_pModel;
      if (model==NULL)
      {
         return;
      }
      else
      {
         CLBAMViewerDoc* pDoc = GetDocument();
         auto dispMgr = GetDisplayMgr();

         if (lHint == GRAPH_SETTING_HINT)
         {
            // only grid setting changed
            BOOL show_grid = pDoc->GetShowGrid();
            m_Graph->DoDisplayGrid(show_grid==FALSE ? VARIANT_FALSE:VARIANT_TRUE );
            m_Graph->Commit();
         }
         else 
         {
            // this will be a bit more time consuming - put up progress monitor window
            pDoc->m_pProgressMonitorWindow->Show(CComBSTR("Processing..."),this->GetSafeHwnd());
            CProgressAutoHide autohide(pDoc->m_pProgressMonitorWindow); // make sure Hide() gets called even if exception gets thrown

            CWaitCursor cursor; // The rest can talk a while... Show the wait cursor

            // Make sure mapping has a DC
            CDManipClientDC dc(this);

            if (lHint == TRUCK_POSITION_CHANGED_HINT)
            {
               // if truck position changed, this means that we only need to update the graph
               BuildGraphDisplayObjects(pDoc, dispMgr);

               RECT rect;
               this->GetClientRect(&rect);
               this->RedrawWindow(&rect);
            }
            else
            {
               // need to make sure truck data is cleared out if a previous view showed truck response
               ClearTruckData(dispMgr);

               // set index of current stage - if there is one
               CString curr_stg = pDoc->GetStage();
               if (curr_stg.IsEmpty())
                  return;

               CComPtr<IStages> stages;
               hr = model->get_Stages(&stages);
               CComBSTR bstg(curr_stg);
               hr = stages->FindIndex(bstg, &m_CurrentStageIndex);
               ATLASSERT(SUCCEEDED(hr));
               //if (m_CurrentStageIndex==-1)
               //   ATLASSERT(0);

               // build display lists for model
               if ( BuildSupportDisplayObjects(pDoc, dispMgr) )
               {
                  BuildTempSupportDisplayObjects(pDoc, dispMgr);
                  BuildSpanDisplayObjects(pDoc, dispMgr);
                  BuildSSMDisplayObjects(pDoc, dispMgr);
                  BuildGraphDisplayObjects(pDoc, dispMgr);

                  ScaleToFit();
               }
            }
         }
      }
   }
   catch (HRESULT hr)
   {
      if (hr==S_FALSE)
      {
         // analysis was cancelled
         ::AfxMessageBox(_T("Analysis Cancelled - Select another load to restart"));
      }
      else
      {
         DealWithExceptions();
      }
   }
   catch(...)
   {
      DealWithExceptions();
   }

	Invalidate(TRUE);
}

bool CLBAMViewerView::BuildSupportDisplayObjects(CLBAMViewerDoc* pDoc, std::shared_ptr<WBFL::DManip::iDisplayMgr> dispMgr)
{
   HRESULT hr;
   CComPtr<ILBAMModel> model = pDoc->m_pModel;

   auto pDL = dispMgr->FindDisplayList(SUPPORT_LIST);
   pDL->Clear();

   auto factory = dispMgr->GetDisplayObjectFactory(0);

   CComPtr<ISupports> supports;
   hr = model->get_Supports(&supports);
   SupportIndexType nsuprts;
   hr = supports->get_Count(&nsuprts);

   CComPtr<ISpans> spans;
   hr = model->get_Spans(&spans);
   SpanIndexType nspans;
   hr = spans->get_Count(&nspans);
   if (nsuprts==0 && nspans==0)
   {
      return false;
   }
   else if (nsuprts != nspans+1)
   {
      CString msg;
      throw msg.LoadString(IDS_INVALID_N_SPANS);
   }
   else
   {
      double loc = 0.0;
      for ( SupportIndexType nsprt = 0; nsprt < nsuprts; nsprt++ )
      {
         CComPtr<ISupport> support;
         hr = supports->get_Item(nsprt,&support);

         WBFL::Geometry::Point2d point(loc, 0.0);

         auto dispObj = factory->Create(CSupportEvents::ms_Format,NULL);

         auto ptDispObj = std::dynamic_pointer_cast<iPointDisplayObject>(dispObj);
      
         auto ds = ptDispObj->GetDrawingStrategy();

         auto strategy = std::dynamic_pointer_cast<iSupportDrawStrategy>(ds);
         strategy->SetSupport(support, nsprt);

         ptDispObj->SetPosition(point,FALSE,FALSE);
         ptDispObj->SetID(nsprt);

         CString strToolTipText;
         auto [x, y] = point.GetLocation();
         strToolTipText.Format(_T("Support %d (%f,%f)"),nsprt, x, y);
         ptDispObj->SetToolTipText(strToolTipText);

         auto connectable = std::dynamic_pointer_cast<iConnectable>(ptDispObj);
         auto socket = connectable->AddSocket(0,point);

         pDL->AddDisplayObject(dispObj);

         if (nsprt <nspans)
         {
            CComPtr<ISpan> span;
            hr = spans->get_Item(nsprt,&span);
            double length;
            hr = span->get_Length(&length);
            loc += length;
         }
      }
   }
   return true;
}

bool CLBAMViewerView::BuildTempSupportDisplayObjects(CLBAMViewerDoc* pDoc, std::shared_ptr<WBFL::DManip::iDisplayMgr> dispMgr)
{
   auto pDL = dispMgr->FindDisplayList(TEMPSUPPORT_LIST);
   pDL->Clear();

   auto factory = dispMgr->GetDisplayObjectFactory(0);

   HRESULT hr;
   CComPtr<ILBAMModel> model = pDoc->m_pModel;
   CComPtr<IStages> stages;
   hr = model->get_Stages(&stages);
   CComPtr<ISpans> spans;
   hr = model->get_Spans(&spans);
   SpanIndexType nspans;
   hr = spans->get_Count(&nspans);
   double loc=0.0;
   for ( SpanIndexType nspan = 0; nspan < nspans; nspan++ )
   {
      CComPtr<ISpan> span;
      hr = spans->get_Item(nspan,&span);

      CComPtr<ITemporarySupports> tss;
      hr = span->get_TemporarySupports(&tss);
      SupportIndexType ntss;
      hr = tss->get_Count(&ntss);
      for (SupportIndexType nts=0; nts<ntss; nts++)
      {
         CComPtr<ITemporarySupport> ts;
         hr = tss->get_Item(nts,&ts);

         // check if temporary support is in current stage
         CComBSTR ts_stage;
         hr = ts->get_StageRemoved(&ts_stage);
         StageIndexType stage_index;
         hr = stages->FindIndex(ts_stage, &stage_index);
         if (m_CurrentStageIndex<stage_index)
         {
            // compute location of top of support
            SupportIDType id;
            hr = ts->get_ID(&id);
            double xloc, yloc;
            double lloc;
            hr = ts->get_Location(&lloc);
            model->ComputeLocation(id, mtTemporarySupport, -1.0, &xloc, &yloc);

            WBFL::Geometry::Point2d point(xloc, yloc);

            // use of support's events class might cause problems when editing is enabled
            auto dispObj = factory->Create(CTemporarySupportEvents::ms_Format,NULL);

            auto ptDispObj = std::dynamic_pointer_cast<iPointDisplayObject>(dispObj);
   
            auto ds = ptDispObj->GetDrawingStrategy();

            auto strategy = std::dynamic_pointer_cast<iTemporarySupportDrawStrategy>(ds);
            strategy->SetTemporarySupport(ts, id);

            ptDispObj->SetPosition(point,FALSE,FALSE);
            ptDispObj->SetID(id);

            CString strToolTipText;
            auto [x, y] = point.GetLocation();
            strToolTipText.Format(_T("TemporarySupport %d (%f,%f)"),id, x, y);
            ptDispObj->SetToolTipText(strToolTipText);

            auto connectable = std::dynamic_pointer_cast<iConnectable>(ptDispObj);
            auto socket = connectable->AddSocket(0,point);

            pDL->AddDisplayObject(ptDispObj);

            double length;
            hr = span->get_Length(&length);
            loc += length;
         }
      }
   }

   return true;
}


void CLBAMViewerView::BuildSpanDisplayObjects(CLBAMViewerDoc* pDoc, std::shared_ptr<WBFL::DManip::iDisplayMgr> dispMgr)
{
   HRESULT hr;
   CComPtr<ILBAMModel> model = pDoc->m_pModel;
   
   auto pDL = dispMgr->FindDisplayList(SPAN_LIST);
   pDL->Clear();

   // Connect display objects representing supports with
   // line display objects
   CComPtr<ISpans> spans;
   hr = model->get_Spans(&spans);
   SpanIndexType nspans;
   hr = spans->get_Count(&nspans);
   for ( SpanIndexType nspan = 0; nspan < nspans; nspan++ )
   {
      auto span_rep = WBFL::DManip::LineDisplayObject::Create();
      span_rep->SetID(nspan);

      auto ds = span_rep->GetDrawLineStrategy();
      auto sds = std::dynamic_pointer_cast<WBFL::DManip::SimpleDrawLineStrategy>(ds);

      sds->SetColor( RGB(0,0,0));
      sds->SetWidth(2);

      auto connector = std::dynamic_pointer_cast<iConnector>(span_rep);

      auto startPlug = connector->GetStartPlug();
      auto endPlug   = connector->GetEndPlug();

      auto pstart_support_rep = dispMgr->FindDisplayObject(nspan,SUPPORT_LIST,AccessType::ByID);

      auto pend_support_rep = dispMgr->FindDisplayObject(nspan+1,SUPPORT_LIST,AccessType::ByID);

      auto startConnectable = std::dynamic_pointer_cast<iConnectable>(pstart_support_rep);
      auto socket = startConnectable->GetSocket(0,AccessType::ByIndex);
      DWORD dwCookie;
      dwCookie = socket->Connect(startPlug);

      auto endConnectable = std::dynamic_pointer_cast<iConnectable>(pend_support_rep);
      socket = endConnectable->GetSocket(0,AccessType::ByIndex);
      dwCookie = socket->Connect(endPlug);

      CString strToolTip;
      strToolTip.Format(_T("Span %d"), nspan);
      span_rep->SetToolTipText(strToolTip);
/*
      CMemberDropSite* pDropSite = new CMemberDropSite(pDoc);
      CComQIPtr<iDropSite,&IID_iDropSite> dropSite(pDropSite->GetInterface(&IID_iDropSite));
      mbrRep->SetDropSite(dropSite);

      CComPtr<iDisplayObjectEvents> pDOE = (iDisplayObjectEvents*)pDropSite->GetInterface(&IID_iDisplayObjectEvents);
      mbrRep->RegisterEventSink(pDOE);
*/
      pDL->AddDisplayObject(span_rep);
   }
}

void CLBAMViewerView::BuildSSMDisplayObjects(CLBAMViewerDoc* pDoc, std::shared_ptr<WBFL::DManip::iDisplayMgr> dispMgr)
{
   HRESULT hr;
   CComPtr<ILBAMModel> model = pDoc->m_pModel;
   CComPtr<IStages> stages;
   hr = model->get_Stages(&stages);

   auto pDL = dispMgr->FindDisplayList(SSM_LIST);
   pDL->Clear();

   auto factory = dispMgr->GetDisplayObjectFactory(0);

   CComPtr<ISuperstructureMembers> ssms;
   hr = model->get_SuperstructureMembers(&ssms);
   IndexType nssms;
   hr = ssms->get_Count(&nssms);
   double offset;
   hr = ssms->get_Offset(&offset);
   double total_length;
   hr = ssms->get_Length(&total_length);

   // deal with colors
   CColorIterator colors( RGB(255, 255, 20), RGB( 255, 75, 20), (int)nssms);

   // make starting point
   double loc = -offset;

   WBFL::Geometry::Point2d point(loc, total_length / DRW_OFFSET);

   long curr_id=0;
   auto startpt_rep = WBFL::DManip::PointDisplayObject::Create();
   startpt_rep->SetPosition(point,FALSE,FALSE);
   startpt_rep->SetID(curr_id++);
   auto start_connectable = std::dynamic_pointer_cast<iConnectable>(startpt_rep);
   auto start_socket = start_connectable->AddSocket(0,point);
   pDL->AddDisplayObject(startpt_rep);
   startpt_rep->Visible(FALSE);

   for ( IndexType nssm = 0; nssm < nssms; nssm++ )
   {
      CComPtr<ISuperstructureMember> ssm;
      hr = ssms->get_Item(nssm,&ssm);

      double length;
      hr = ssm->get_Length(&length);
      loc += length;
      point.X() = loc;

      // end point display object
      auto endpt_rep = WBFL::DManip::PointDisplayObject::Create();
      endpt_rep->SetPosition(point,FALSE,FALSE);
      endpt_rep->SetID(curr_id++);
      auto end_connectable = std::dynamic_pointer_cast<iConnectable>(endpt_rep);
      auto end_socket = end_connectable->AddSocket(0,point);

      pDL->AddDisplayObject(endpt_rep);
      endpt_rep->Visible(FALSE);

      // line to represent ssm
      auto ssm_rep = WBFL::DManip::LineDisplayObject::Create();
      ssm_rep->SetID(10000+curr_id++);


      m_RoadwayElevation = 3; // same as rectangle width

      //CComPtr<iRectangleDrawLineStrategy> draw_ssm;
      //::CoCreateInstance(CLSID_RectangleDrawLineStrategy,NULL,CLSCTX_ALL,IID_iRectangleDrawLineStrategy,(void**)&draw_ssm);
      //draw_ssm->SetLineWidth(3);
      //draw_ssm->SetWidth(5);
      //draw_ssm->SetColor( colors.Item((int)nssm) );
      //ssm_rep->SetDrawLineStrategy(draw_ssm);

      auto draw_ssm = WBFL::DManip::SimpleDrawLineStrategy::Create();
      draw_ssm->SetWidth(3);
      draw_ssm->SetColor(colors.Item((int)nssm));
      ssm_rep->SetDrawLineStrategy(draw_ssm);

      // see if ends are released
      BSTR start_rel_stage=NULL;
      ssm->GetEndReleaseRemovalStage(ssLeft,&start_rel_stage);
      VARIANT_BOOL bIsReleased;
      ssm->IsEndReleased(ssLeft, mrtMz, &bIsReleased);
      if (bIsReleased == VARIANT_TRUE)
      {
         StageIndexType rel_index;
         stages->FindIndex(start_rel_stage,&rel_index);
         if ( rel_index == INVALID_INDEX || rel_index>m_CurrentStageIndex )
         {
            draw_ssm->SetBeginType(WBFL::DManip::PointType::Circle);
            draw_ssm->SetBeginSize(10);
         }
      }
      ::SysFreeString(start_rel_stage);

      BSTR end_rel_stage=NULL;
      ssm->GetEndReleaseRemovalStage(ssRight,&end_rel_stage);
      ssm->IsEndReleased(ssRight, mrtMz, &bIsReleased);
      if (bIsReleased == VARIANT_TRUE)
      {
         StageIndexType rel_index;
         stages->FindIndex(end_rel_stage,&rel_index);
         if ( rel_index == INVALID_INDEX || rel_index>m_CurrentStageIndex )
         {
            draw_ssm->SetEndType(WBFL::DManip::PointType::Circle);
            draw_ssm->SetEndSize(10);
         }
      }
      ::SysFreeString(end_rel_stage);

      // plug in
      auto connector = std::dynamic_pointer_cast<iConnector>(ssm_rep);

      auto startPlug = connector->GetStartPlug();
      auto endPlug = connector->GetEndPlug();

      auto startConnectable = std::dynamic_pointer_cast<iConnectable>(startpt_rep);
      auto socket = startConnectable->GetSocket(0,AccessType::ByIndex);
      DWORD dwCookie = socket->Connect(startPlug);

      auto endConnectable = std::dynamic_pointer_cast<iConnectable>(endpt_rep);
      socket = endConnectable->GetSocket(0,AccessType::ByIndex);
      dwCookie = socket->Connect(endPlug);

      CString strToolTip;
      strToolTip.Format(_T("SuperstructureMember %d"), nssm);
      ssm_rep->SetToolTipText(strToolTip);

      pDL->AddDisplayObject(ssm_rep);

      // draw segments
      CString curr_stg = pDoc->GetStage();
      double offset = total_length/(DRW_OFFSET);
      BuildSegmentDisplayObjects(curr_stg,loc-length, offset, loc, offset, pDL, ssm, &curr_id);

      // loop
      startpt_rep = endpt_rep;
   }
}

void BuildSegmentDisplayObjects(CString& Stage, double xStart, double yStart, double xEnd, double yEnd, std::shared_ptr<iDisplayList> pDL, ISuperstructureMember* ssm, long* pCurrID)
{
   HRESULT hr;
   CComPtr<IFilteredSegmentCollection> segs;
   hr = ssm->GetMemberSegments(_bstr_t(Stage), &segs);
   SegmentIndexType nsegs;
   hr = segs->get_Count(&nsegs);

   CColorIterator colors( RGB(255, 20, 20), RGB( 20,  20, 255), (int)nsegs);

   // make starting point
   WBFL::Geometry::Point2d point(xStart, yStart);

   auto startpt_rep = WBFL::DManip::PointDisplayObject::Create();
   startpt_rep->SetPosition(point,FALSE,FALSE);
   startpt_rep->SetID(30000+(*pCurrID)++);
   auto start_connectable = std::dynamic_pointer_cast<iConnectable>(startpt_rep);
   auto start_socket = start_connectable->AddSocket(0,point);
   pDL->AddDisplayObject(startpt_rep);
   startpt_rep->Visible(FALSE);

   double loc=0.0;
   for (SegmentIndexType iseg=0; iseg<nsegs; iseg++)
   {
      CComPtr<ISegment> seg;
      hr = segs->get_Item(iseg,&seg);
      double len;
      hr = seg->get_Length(&len);
      loc += len;

      double xloc, yloc;
      GetPointAlongLineSegment(xStart, yStart, xEnd, yEnd, loc, &xloc, &yloc);

      point.Move(xloc, yloc);

      // end point display object
      auto endpt_rep = WBFL::DManip::PointDisplayObject::Create();
      endpt_rep->SetPosition(point,FALSE,FALSE);
      endpt_rep->SetID(30000+(*pCurrID)++);
      auto end_connectable = std::dynamic_pointer_cast<iConnectable>(endpt_rep);
      auto end_socket = end_connectable->AddSocket(0,point);
      pDL->AddDisplayObject(endpt_rep);
      endpt_rep->Visible(FALSE);

      // line to represent seg
      auto seg_rep = WBFL::DManip::LineDisplayObject::Create();
      seg_rep->SetID(30000+(*pCurrID)++);

      auto ds = seg_rep->GetDrawLineStrategy();
      auto sds = std::dynamic_pointer_cast<WBFL::DManip::SimpleDrawLineStrategy>(ds);

      sds->SetColor( colors.Item((int)iseg) );
      sds->SetWidth(5);

      // plug in
      auto connector = std::dynamic_pointer_cast<iConnector>(seg_rep);

      auto startPlug = connector->GetStartPlug();
      auto endPlug = connector->GetEndPlug();

      auto startConnectable = std::dynamic_pointer_cast<iConnectable>(startpt_rep);
      auto socket = startConnectable->GetSocket(0,AccessType::ByIndex);
      DWORD dwCookie = socket->Connect(startPlug);

      auto endConnectable = std::dynamic_pointer_cast<iConnectable>(endpt_rep);
      endConnectable->GetSocket(0,AccessType::ByIndex);
      dwCookie = socket->Connect(endPlug);

      CString strToolTip;
      strToolTip.Format(_T("Segment %d"), iseg);
      seg_rep->SetToolTipText(strToolTip);

      pDL->AddDisplayObject(seg_rep);

      // loop
      startpt_rep = endpt_rep;

   }
}

void CLBAMViewerView::BuildGraphDisplayObjects(CLBAMViewerDoc* pDoc, std::shared_ptr<WBFL::DManip::iDisplayMgr> dispMgr)
{
   HRESULT hr;

   bool has_truck_data = false;

   try
   {
      // clear out graph and add new data
      m_Graph->ClearData();
      m_Legend->ClearEntries();

      BOOL show_grid = pDoc->GetShowGrid();
      m_Graph->DoDisplayGrid(show_grid==FALSE ? VARIANT_FALSE:VARIANT_TRUE );

      if (m_FirstSize)
      {
         m_FirstSize=false;

         // set up bounds for graph
         CComPtr<ISuperstructureMembers> ssms;
         hr = pDoc->m_pModel->get_SuperstructureMembers(&ssms);
         PROCESS_HR(hr);

         double lbam_length;
         hr = ssms->get_Length(&lbam_length);
         PROCESS_HR(hr);

         double overhang;
         hr = ssms->get_Offset(&overhang);
         PROCESS_HR(hr);

      #pragma Reminder("Hack - placing graph in view")
         // assume that column lengths are less than 10% of lbam length
         auto graph_bounds = m_Graph->GetGraphBounds();

         double graph_top = -lbam_length/10.0;
         double graph_bottom = graph_top - lbam_length/2; // 2:1 aspect

         graph_bounds.Left() = -overhang;
         graph_bounds.Right() = lbam_length-overhang;
         graph_bounds.Top() = graph_top;
         graph_bounds.Bottom() = graph_bottom;

         WBFL::Geometry::Point2d leg_pos(lbam_length/2.0, graph_top);

         m_Legend->SetPosition(leg_pos,FALSE,FALSE);
      }
      // get analysis information
      CString curr_stg = pDoc->GetStage();
      if (curr_stg.GetLength()==0)
         return;

      BOOL is_cumm = pDoc->GetAccumulateResults();
      ResultsSummationType summ_type = is_cumm ? rsCumulative : rsIncremental;

      CLBAMViewerDoc::ResponseType curr_rt = pDoc->GetResponseType();

      // get superstructure pois
      CComPtr<IAnalysisPOIs> poi_utility;
      pDoc->m_pLBAMAnalysisEngine->get_AnalysisPOIs(&poi_utility);

      CComPtr<IIDArray> poilist;
      CComPtr<IDblArray> loclist;
      hr = poi_utility->GetSuperstructurePois(CComBSTR(curr_stg), &poilist, &loclist);
      PROCESS_HR(hr);

      IndexType poi_cnt;
      poilist->get_Count(&poi_cnt);

      // remove internally generated pois if asked
      if (pDoc->GetShowInternalPOIs()==FALSE)
      {
         CComPtr<IIDArray> new_poilist;
         hr = new_poilist.CoCreateInstance(CLSID_IDArray);
         CComPtr<IDblArray> new_loclist;
         hr = new_loclist.CoCreateInstance(CLSID_DblArray);

         for (IndexType i=0; i<poi_cnt; i++)
         {
            PoiIDType poi_id;
            hr = poilist->get_Item(i,&poi_id);

            if (poi_id>=0)
            {
               double poi_loc;
               hr = loclist->get_Item(i, &poi_loc);

               new_poilist->Add(poi_id);
               new_loclist->Add(poi_loc);
            }
         }

         poilist = new_poilist;
         loclist = new_loclist;

         poilist->get_Count(&poi_cnt);
      }

      if (poi_cnt==0)
      {
         ::AfxMessageBox(_T("No POIs in LBAM model. Results cannot be displayed"));
         return;
      }

      // selection data is in our frame
      CChildFrame* pframe = (CChildFrame*)GetParentFrame( );

      // get color demand
      IndexType num_dsb = pframe->GetNumDataSetBuilders();
      IndexType num_colors=0;
      for (IndexType i=0; i<num_dsb; i++)
      {
         iDataSetBuilder* pbld = pframe->GetDataSetBuilder(i);
         num_colors += pbld->ColorDemand(curr_stg, curr_rt);
      }

      // our range of color
      CColorIterator graph_colors(RGB(220,110,0), RGB(0,0,220), (int)num_colors);

      // percent increments for progress monitor
      CComQIPtr<IProgressMonitor> prog_mon(pDoc->m_pProgressMonitorWindow);
      IndexType inc = 100 / (num_dsb!=0? num_dsb:1);
      IndexType curr_inc = 0;
      for (IndexType i=0; i<num_dsb; i++)
      {
         COLORREF color = graph_colors.Item((int)i);

         iDataSetBuilder* pbld = pframe->GetDataSetBuilder(i);
         std::vector<std::shared_ptr<iGraphXyDataProvider>> data_sets;

         CString cmsg(pbld->GetDescription());
         cmsg = CString(_T("Computing ")) + cmsg;
         CComBSTR bmsg((const TCHAR*)cmsg);
         prog_mon->put_Message(pDoc->m_LoadCombinationCookie, bmsg); // cookie is arbitrary

         if (i!=0)
         {
            curr_inc += inc;
            prog_mon->put_GaugeValue(pDoc->m_LoadCombinationCookie,(long)curr_inc);
         }

         pbld->BuildDataSets(poilist, loclist, curr_stg, curr_rt, summ_type, color, &data_sets);

         IndexType num_ds = data_sets.size();
         for (IndexType ids=0; ids<num_ds; ids++)
         {
            auto pds = data_sets[ids];
            m_Graph->AddData(pds);

            auto fac = pds->GetDataPointFactory();
            auto entry = std::dynamic_pointer_cast<iLegendEntry>(fac);
            m_Legend->AddEntry(entry);
         }

         // create and set up truck display object if needed for this vehicle
         if (pbld->HasTruckPlacement())
         {
            has_truck_data = true;

            auto pDL = dispMgr->FindDisplayList(TRUCK_LIST);

            auto factory = dispMgr->GetDisplayObjectFactory(0);

            auto disp_obj = factory->Create(CLBAMTruckDisplayImpl::ms_Format,NULL);

            auto sink = disp_obj->GetEventSink();

            auto point_disp = std::dynamic_pointer_cast<iPointDisplayObject>(disp_obj);
            auto truck_events = std::dynamic_pointer_cast<iLBAMTruckEvents>(sink);

            LiveLoadModelType model_type;
            VehicleIndexType vehicle_index;
            CComPtr<ILiveLoadConfiguration> placement;
            pbld->GetTruckInfo(&model_type, &vehicle_index, &placement);

            truck_events->Init(point_disp, pDoc->m_pModel, model_type, vehicle_index, placement );
            truck_events->SetRoadwayElevation(point_disp, m_RoadwayElevation);

            auto truck_strat = std::dynamic_pointer_cast<iLBAMTruckDrawStrategy>(truck_events);
            truck_strat->SetColor(color);

            pDL->AddDisplayObject(disp_obj);
         }
      }

      prog_mon->put_GaugeValue(pDoc->m_LoadCombinationCookie,100);

      // size legend to fit entry texts
      auto size = m_Legend->GetMinCellSize();
      size.cy += 60; // expand a bit (twips) to give border buffer
      m_Legend->SetCellSize(size);

      m_Graph->Commit();
   }
   catch(HRESULT hr)
   {
      if (hr==S_FALSE)
      {
         // analysis was cancelled - clear graph objects
         m_Graph->ClearData();
         m_Graph->Commit();

         m_Legend->ClearEntries();

         if (has_truck_data)
         {
            auto pDL = dispMgr->FindDisplayList(TRUCK_LIST);
            pDL->Clear();
         }
      }

      throw;
   }
   catch(...)
   {
      throw;
   }
}

void CLBAMViewerView::DealWithExceptions()
{
   try
   {
      // throw only to be caught below
      throw;
   }
   catch (CString& rstring)
   {
      // clear out display lists and display a message
      auto dispMgr = GetDisplayMgr();
      IndexType cnt = dispMgr->GetDisplayListCount();
      for (IndexType i=0; i<cnt; i++)
      {
         auto pDL = dispMgr->GetDisplayList(i);
         pDL->Clear();
      }

      MessageBox(rstring, _T("Error"), MB_OK | MB_ICONERROR);

   }
   catch (HRESULT /*hr*/)
   {
      // see if we can get errorinfo
      CComPtr<IErrorInfo> errinf;
      HRESULT hr2 = ::GetErrorInfo(0, &errinf);
      if (SUCCEEDED(hr2))
      {
         BSTR msg;
         errinf->GetDescription(&msg);
         _bstr_t bmsg(msg);
         AfxMessageBox((const TCHAR*)bmsg, MB_OK | MB_ICONERROR);
      }
      else
      {
         ATLASSERT(0);
         AfxMessageBox(_T("An unknown error occurred"), MB_OK | MB_ICONERROR);
      }
   }
   catch(...)
   {
      ATLASSERT(0);
      AfxMessageBox(_T("An unknown error occurred"), MB_OK | MB_ICONERROR);
   }
}

void CLBAMViewerView::ClearTruckData(std::shared_ptr<WBFL::DManip::iDisplayMgr> dispMgr)
{
   // clean out truck placement data

   if (dispMgr!=NULL)
   {
      // clear truck display list
      auto pDL = dispMgr->FindDisplayList(TRUCK_LIST);
      pDL->Clear();
   }
}


void CLBAMViewerView::OnSize(UINT nType, int cx, int cy) 
{
	CDisplayView::OnSize(nType, cx, cy);

   if (!m_First)
   {
      CRect rect;
      this->GetClientRect(&rect);

      auto dispMgr = GetDisplayMgr();

      SetLogicalViewRect(MM_TEXT,rect);

      CSize size = rect.Size();
      SetScrollSizes(MM_TEXT,size,CScrollView::sizeDefault,CScrollView::sizeDefault);

      ScaleToFit();

   }
}

