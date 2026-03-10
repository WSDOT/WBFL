// FEA2DView.cpp : implementation of the CFEA2DView class
//

#include "stdafx.h"
#include "FEA2D.h"

#include "FEA2DDoc.h"
#include "FEA2DView.h"
#include "MainFrm.h"

#include "JointEvents.h"
#include "JointDrawStrategy.h"

#include "PointLoadEventsImpl.h"
#include "PointLoadDrawStrategy.h"

#include "DisplayObjectFactory.h"

#include "MemberDropSite.h"

#include "CreateLoadingDlg.h"
#include "AddPointLoadDlg.h"

#include "ListID.h"

#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFEA2DView

IMPLEMENT_DYNCREATE(CFEA2DView, CDisplayView)

BEGIN_MESSAGE_MAP(CFEA2DView, CDisplayView)
	//{{AFX_MSG_MAP(CFEA2DView)
	ON_COMMAND(ID_VIEW_SCALETOFIT, OnViewScaleToFit)
	ON_COMMAND(ID_VIEW_CENTERONPOINT, OnViewCenterOnPoint)
	ON_COMMAND(ID_VIEW_ZOOM, OnViewZoom)
	ON_COMMAND(ID_VIEW_SETSCALE, OnViewSetScale)
	ON_WM_MOUSEMOVE()
   ON_WM_SIZE()
	ON_COMMAND(ID_LOADS_CREATELOADING, OnLoadsCreateLoading)
	ON_COMMAND(ID_LOADS_ADDPOINTLOAD, OnLoadsAddPointLoad)
	ON_COMMAND(ID_VIEW_JOINTS, OnViewJoints)
	ON_UPDATE_COMMAND_UI(ID_VIEW_JOINTS, OnUpdateViewJoints)
	ON_COMMAND(ID_VIEW_MEMBERS, OnViewMembers)
	ON_UPDATE_COMMAND_UI(ID_VIEW_MEMBERS, OnUpdateViewMembers)
	ON_COMMAND(ID_VIEW_LOADS, OnViewLoads)
	ON_UPDATE_COMMAND_UI(ID_VIEW_LOADS, OnUpdateViewLoads)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CDisplayView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CDisplayView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CDisplayView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFEA2DView construction/destruction

CFEA2DView::CFEA2DView()
{
	// TODO: add construction code here
   AfxEnableControlContainer();

   m_bHideJoints  = FALSE;
   m_bHideMembers = FALSE;
   m_bHideLoads   = FALSE;
}

CFEA2DView::~CFEA2DView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CFEA2DView drawing

void CFEA2DView::OnDraw(CDC* pDC)
{
	CFEA2DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here

   CDisplayView::OnDraw(pDC);
}

void CFEA2DView::OnInitialUpdate()
{
	CDisplayView::OnInitialUpdate();
   EnableToolTips();

   // set a temporary dc so we can do mapping
   CDManipClientDC dc(this);

   CFEA2DDoc* pDoc = GetDocument();
   CComPtr<IFem2dModel> model = pDoc->m_Model;

   auto dispMgr = GetDisplayMgr();

   // Setup the display object factory
   dispMgr->AddDisplayObjectFactory(std::make_shared<CDisplayObjectFactory>(pDoc));

   // Create display lists
   auto dlList = DisplayList::Create();
   dlList->SetID(DIMLINE_LIST);
   dispMgr->AddDisplayList(dlList);

   auto loadList = DisplayList::Create();
   loadList->SetID(LOAD_LIST);
   dispMgr->AddDisplayList(loadList);

   auto jntList = DisplayList::Create();
   jntList->SetID(JNT_LIST);
   dispMgr->AddDisplayList(jntList);

   auto mbrList = DisplayList::Create();
   mbrList->SetID(MBR_LIST);
   dispMgr->AddDisplayList(mbrList);

   BuildJointDisplayObjects();
   BuildMemberDisplayObjects();
   BuildLoadDisplayObjects();

   SetMappingMode(MapMode::Isotropic);

   ScaleToFit();

   USES_CONVERSION;
   CComBSTR name;
   model->get_Name(&name);
   SetWindowText(OLE2T(name));
}

void CFEA2DView::BuildJointDisplayObjects()
{
   CFEA2DDoc* pDoc = GetDocument();
   CComPtr<IFem2dModel> model = pDoc->m_Model;

   auto dispMgr = GetDisplayMgr();
   auto pDL = dispMgr->FindDisplayList(JNT_LIST);
   pDL->Clear();

   auto factory = dispMgr->GetDisplayObjectFactory(0);

   CComPtr<IFem2dJointCollection> joints;
   model->get_Joints(&joints);

   IndexType nJnts;
   joints->get_Count(&nJnts);

   for ( IndexType jnt = 0; jnt < nJnts; jnt++ )
   {
      CComPtr<IFem2dJoint> joint;
      joints->get_Item(jnt,&joint);

      Float64 x,y;
      joint->get_X(&x);
      joint->get_Y(&y);

      WBFL::Geometry::Point2d point(x, y);

      auto dispObj = factory->Create(CJointEvents::ms_Format,NULL);
      auto ptDispObj = std::dynamic_pointer_cast<iPointDisplayObject>(dispObj);
      auto ds = ptDispObj->GetDrawingStrategy();
      auto strategy = std::dynamic_pointer_cast<iJointDrawStrategy>(ds);

      strategy->SetJoint(joint);

      ptDispObj->SetPosition(point,FALSE,FALSE);

      JointIDType ID;
      joint->get_ID(&ID);
      ptDispObj->SetID(ID);

      joint->get_X(&x);
      joint->get_Y(&y);

      CString strToolTipText;
      strToolTipText.Format(_T("Joint %d (%f,%f)"),ID,x,y);
      ptDispObj->SetToolTipText(strToolTipText);

      pDL->AddDisplayObject(ptDispObj);
   }
}

void CFEA2DView::BuildMemberDisplayObjects()
{
   CFEA2DDoc* pDoc = GetDocument();
   CComPtr<IFem2dModel> model = pDoc->m_Model;
   
   auto dispMgr = GetDisplayMgr();

   auto pDL = dispMgr->FindDisplayList(MBR_LIST);
   pDL->Clear();

   // Connect display objects representing joints with
   // line display objects
   CComPtr<IFem2dMemberCollection> members;
   model->get_Members(&members);

   CComPtr<IFem2dJointCollection> joints;
   model->get_Joints(&joints);

   IndexType nMembers;
   members->get_Count(&nMembers);
   for ( IndexType mbr = 0; mbr < nMembers; mbr++ )
   {
      CComPtr<IFem2dMember> pMbr;
      members->get_Item(mbr,&pMbr);

      JointIDType startJntID, endJntID;
      pMbr->get_StartJoint(&startJntID);
      pMbr->get_EndJoint(&endJntID);

      CComPtr<IFem2dJoint> pStartJnt, pEndJnt;
      joints->Find(startJntID,&pStartJnt);
      joints->Find(endJntID,  &pEndJnt);

      auto mbrRep = LineDisplayObject::Create();

      MemberIDType mbrID;
      pMbr->get_ID(&mbrID);
      mbrRep->SetID(mbrID);

      auto drawStrategy = SimpleDrawLineStrategy::Create();
      mbrRep->SetDrawLineStrategy(drawStrategy);

      VARIANT_BOOL bIsReleased;
      pMbr->IsReleased(metStart,mbrReleaseMz,&bIsReleased);
      if ( bIsReleased == VARIANT_TRUE )
         drawStrategy->SetBeginType(PointType::Circle);

      pMbr->IsReleased(metEnd,mbrReleaseMz,&bIsReleased);
      if ( bIsReleased == VARIANT_TRUE )
         drawStrategy->SetEndType(PointType::Circle);
      
      auto connector = std::dynamic_pointer_cast<iConnector>(mbrRep);

      auto startPlug = connector->GetStartPlug();
      auto endPlug = connector->GetEndPlug();

      auto pStartJntRep = dispMgr->FindDisplayObject(startJntID,JNT_LIST,AccessType::ByID);
      auto pEndJntRep   = dispMgr->FindDisplayObject(endJntID,  JNT_LIST,AccessType::ByID);

      auto startConnectable = std::dynamic_pointer_cast<iConnectable>(pStartJntRep);
      std::shared_ptr<iSocket> socket;
      WBFL::Geometry::Point2d point;

      Float64 x,y;
      pStartJnt->get_X(&x);
      pStartJnt->get_Y(&y);

      point.Move(x,y);
      socket = startConnectable->AddSocket(0,point);
      
      DWORD dwCookie = socket->Connect(startPlug);

      auto endConnectable = std::dynamic_pointer_cast<iConnectable>(pEndJntRep);

      pEndJnt->get_X(&x);
      pEndJnt->get_Y(&y);

      point.Move(x,y);
      socket = endConnectable->AddSocket(0,point);
      dwCookie = socket->Connect(endPlug);

      CString strToolTip;
      pMbr->get_ID(&mbrID);
      strToolTip.Format(_T("Member %d"),mbrID);
      mbrRep->SetToolTipText(strToolTip);

      auto pDropSite = std::make_shared<CMemberDropSite>(pDoc);
      mbrRep->RegisterDropSite(pDropSite);
      mbrRep->RegisterEventSink(pDropSite);

      pDL->AddDisplayObject(mbrRep);
   }
}

void CFEA2DView::BuildLoadDisplayObjects()
{
   // Initialize loading colors
   COLORREF colors[] = { RGB(0,0,255),
                         RGB(0,255,0),
                         RGB(255,127,127),
                         RGB(0,255,255),
                         RGB(255,0,255) };
   IndexType colorCount = sizeof(colors)/sizeof(COLORREF);

   CFEA2DDoc* pDoc = GetDocument();
   CComPtr<IFem2dModel> model = pDoc->m_Model;

   auto dispMgr = GetDisplayMgr();

   auto pDL = dispMgr->FindDisplayList(LOAD_LIST);
   pDL->Clear();

   auto factory = dispMgr->GetDisplayObjectFactory(0);

   CComPtr<IFem2dMemberCollection> members;
   model->get_Members(&members);

   CComPtr<IFem2dJointCollection> joints;
   model->get_Joints(&joints);

   CComPtr<IFem2dLoadingCollection> loadings;
   model->get_Loadings(&loadings);
   IndexType cLoadings;
   loadings->get_Count(&cLoadings);
   for ( IndexType i = 0; i < cLoadings; i++ )
   {
      // Determine the color
      IndexType clrIdx = i;
      while ( colorCount <= clrIdx )
      {
         clrIdx -= colorCount;
      }
      COLORREF color = colors[clrIdx];

      CComPtr<IFem2dLoading> loading;
      loadings->get_Item(i,&loading);

      CComPtr<IFem2dPointLoadCollection> ptLoads;
      loading->get_PointLoads(&ptLoads);

      IndexType cPtLoads;
      ptLoads->get_Count(&cPtLoads);

      for ( IndexType j = 0; j < cPtLoads; j++ )
      {
         CComPtr<IFem2dPointLoad> ptLoad;
         ptLoads->get_Item(j,&ptLoad);

         MemberIDType mbrID;
         ptLoad->get_MemberID(&mbrID);

         CComPtr<IFem2dMember> mbr;
         members->Find(mbrID,&mbr);

         JointIDType startJntID, endJntID;
         mbr->get_StartJoint(&startJntID);
         mbr->get_EndJoint(&endJntID);

         CComPtr<IFem2dJoint> startJoint,endJoint;
         joints->Find(startJntID,&startJoint);
         joints->Find(endJntID,&endJoint);

         Float64 startX, startY;
         startJoint->get_X(&startX);
         startJoint->get_Y(&startY);

         WBFL::Geometry::Point2d startPoint(startX, startY);

         Float64 endX, endY;
         endJoint->get_X(&endX);
         endJoint->get_Y(&endY);

         WBFL::Geometry::Point2d endPoint(endX, endY);

         double angle = atan2(endY - startY, endX - startX);

         double mbrLength;
         mbr->get_Length(&mbrLength);

         double location;
         ptLoad->get_Location(&location);
         if ( location < 0 ) // fractional load
            location = -1*location*mbrLength;

         WBFL::Geometry::Point2d point(startX + location*cos(angle), startY + location*sin(angle));

         auto dispObj = factory->Create(CPointLoadEventsImpl::ms_Format,NULL);
         auto ptDispObj = std::dynamic_pointer_cast<iPointDisplayObject>(dispObj);
         
         auto ds = ptDispObj->GetDrawingStrategy();
         auto strategy = std::dynamic_pointer_cast<iPointLoadDrawStrategy>(ds);
         strategy->SetLoad(ptLoad);
         strategy->SetColor(color);

         auto sink = dispObj->GetEventSink();
         auto events = std::dynamic_pointer_cast<iPointLoadEvents>(sink);
         events->InitFromLoad(ptLoad);

         LoadIDType loadID;
         ptLoad->get_ID(&loadID);

         LoadCaseIDType loadcaseID;
         loading->get_ID(&loadcaseID);

         ptDispObj->SetPosition(point,FALSE,FALSE);
         ptDispObj->SetID(loadID);

         CString strToolTipText;
         strToolTipText.Format(_T("Loading %d Load %d"),loadcaseID,loadID);
         ptDispObj->SetToolTipText(strToolTipText);

         pDL->AddDisplayObject(ptDispObj);
      }
   }
}

/////////////////////////////////////////////////////////////////////////////
// CFEA2DView printing

void CFEA2DView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{

	CDisplayView::OnPrepareDC(pDC, pInfo);
}


/////////////////////////////////////////////////////////////////////////////
// CFEA2DView diagnostics

#ifdef _DEBUG
void CFEA2DView::AssertValid() const
{
	CDisplayView::AssertValid();
}

void CFEA2DView::Dump(CDumpContext& dc) const
{
	CDisplayView::Dump(dc);
}

CFEA2DDoc* CFEA2DView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFEA2DDoc)));
	return (CFEA2DDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFEA2DView message handlers
DROPEFFECT CFEA2DView::CanDrop(COleDataObject* pDataObject,DWORD dwKeyState,const WBFL::Geometry::Point2d& point)
{
   // This override has to determine if the thing being dragged over it can
   // be dropped. In order to do that, it must unpackage the OleDataObject.
   //
   // The stuff in the data object is just from the display object. The display
   // objects need to be updated so that the client can attach an object to it
   // that knows how to package up domain specific information. At the same
   // time, this view needs to be able to get some domain specific hint 
   // as to the type of data that is going to be dropped.

   if ( pDataObject->IsDataAvailable(CJointEvents::ms_Format) )
      return DROPEFFECT_MOVE;

   return DROPEFFECT_NONE;
}

void CFEA2DView::OnDropped(COleDataObject* pDataObject,DROPEFFECT dropEffect, const WBFL::Geometry::Point2d& point)
{
   AfxMessageBox(_T("OnDropped"));
}
//
//void CFEA2DView::OnChanged(IDisplayMgr* pDM,IDisplayList* pDL,IDisplayObject* pDO)
//{
//   if (pDO->GetID() == 500 )
//   {
//      // Get the two end plugs and their coordinates
//      IConnector* pConnector = dynamic_cast<IConnector*>(pDO);
//      ASSERT(pConnector);
//      IPlug* pStartPlug = pConnector->GetStartPlug();
//      IPlug* pEndPlug = pConnector->GetEndPlug();
//
//      ISocket* pStartSocket = pStartPlug->GetSocket();
//      ISocket* pEndSocket = pEndPlug->GetSocket();
//
//      WBFLGeometry::IPoint2dPtr pStart = pStartSocket->GetPosition();
//      WBFLGeometry::IPoint2dPtr pEnd = pEndSocket->GetPosition();
//
//      // Determine the slope of the line
//      double angle = atan2(pEnd->Y - pStart->Y,pEnd->X - pStart->X);
//
//      // Get the text block from the dimension line and get the new distance
//      IDimensionLine* pDim = dynamic_cast<IDimensionLine*>(pDO);
//      ITextBlock* pText = pDim->GetTextBlock();
//      CString strText = pText->GetText();
//      double dist = atof(strText);
//
//      // Compute the new coordinates of the end point
//      pEnd->X = pStart->X + dist*cos(angle);
//      pEnd->Y = pStart->Y + dist*sin(angle);
//
//      // Move the end point
//      IConnectable* pConnectable = pEndSocket->GetConnectable();
//      IPointDisplayObject* pPoint = dynamic_cast<IPointDisplayObject*>(pConnectable);
//      ASSERT(pPoint);
//      pPoint->SetPosition(pEnd,TRUE,FALSE);
//   }
//}
//
//void CFEA2DView::OnMoved(IDisplayMgr* pDM,IDisplayList* pDL,IDisplayObject* pDO,ISize2d* offset)
//{
////   if ( pDO->GetID() == 200 )
////   {
////      IPointDisplayObject* pPoint = dynamic_cast<IPointDisplayObject*>(pDO);
////      ASSERT(pPoint != 0);
////      pPoint->Move(offset,TRUE,FALSE);
////   }
//
//   if ( pDO->GetID() >= 0 )
//   {
//      // Only display objects that represent joints are assigned positive id's
//      // so a joint was moved.
//   	CFEA2DDoc* pDoc = GetDocument();
//      WBFLFem2d::IFem2dModelPtr model = pDoc->m_Model;
//
//      WBFLFem2d::IFem2dJointCollectionPtr joints = model->Joints;
//      WBFLFem2d::IFem2dJointPtr joint = joints->Find[pDO->GetID()];
//
//      double x,y;
//      x = joint->X;
//      y = joint->Y;
//
//      joint->X = x + offset->dx;
//      joint->Y = x + offset->dy;
//
//      IPointDisplayObject* pPoint = dynamic_cast<IPointDisplayObject*>(pDO);
//      ASSERT(pPoint);
//      pPoint->Move(offset,TRUE,FALSE);
//
//      pDoc->SetModifiedFlag(TRUE);
//   }
//}


void CFEA2DView::OnViewScaleToFit() 
{
   ScaleToFit();	
   Invalidate();
}

void CFEA2DView::OnViewCenterOnPoint() 
{
   ActivateCenterOnPointTask();
}

void CFEA2DView::OnViewZoom() 
{
   ActivateZoomTask();
}

void CFEA2DView::OnViewSetScale() 
{
   AfxMessageBox(_T("Setting scale to 2"));
   auto dispMgr = GetDisplayMgr();
   Zoom(2);
   Invalidate();
}

void CFEA2DView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
   CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();

   pMainFrm->UpdateDevicePoint(point.x,point.y);

   CDManipClientDC dc(this);

   CPoint logPoint(point);
   dc.DPtoLP(&logPoint);

   pMainFrm->UpdateLogicalPoint(logPoint.x,logPoint.y);

   double wx,wy;

   auto pDM = GetDisplayMgr();

   auto pMap = pDM->GetCoordinateMap();

   pMap->LPtoWP(logPoint.x,logPoint.y,&wx,&wy);

   pMainFrm->UpdateWorldPoint(wx,wy);
	
	CDisplayView::OnMouseMove(nFlags, point);
}

void CFEA2DView::OnLoadsCreateLoading() 
{
   CFEA2DDoc* pDoc = GetDocument();
   CComPtr<IFem2dModel> model = pDoc->m_Model;
   CComPtr<IFem2dLoadingCollection> loadings;
   model->get_Loadings(&loadings);

   CCreateLoadingDlg dlg;
   IndexType count;
   loadings->get_Count(&count);
   dlg.m_ID = count;

   if ( dlg.DoModal() == IDOK )
   {
      LoadCaseIDType id = dlg.m_ID;

      try
      {
         // An error will occur if the loading already exists
         CComPtr<IFem2dLoading> loading;
         loadings->Create(id,&loading);
      }
      catch (...)
      {
         AfxMessageBox(_T("Error creating loading"));
      }
   }
}

void CFEA2DView::OnLoadsAddPointLoad() 
{
   CFEA2DDoc* pDoc = GetDocument();
   CComPtr<IFem2dModel> model = pDoc->m_Model;

   CComPtr<IFem2dLoadingCollection> loadings;
   model->get_Loadings(&loadings);

   CAddPointLoadDlg dlg(model);

   if ( dlg.DoModal() == IDOK )
   {
      CComPtr<IFem2dLoading> loading;
      loadings->get_Item(dlg.m_LoadingID,&loading);

      CComPtr<IFem2dPointLoadCollection> pointLoads;
      loading->get_PointLoads(&pointLoads);

      try
      {
         IndexType count;
         pointLoads->get_Count(&count);
         CComPtr<IFem2dPointLoad> ptLoad;
         pointLoads->Create(count,dlg.m_MbrID,dlg.m_Location,dlg.m_Fx,dlg.m_Fy,dlg.m_Mz,lotGlobal,&ptLoad);
      }
      catch(...)
      {
         AfxMessageBox(_T("Failed to create load"));
      }
   }
}

void CFEA2DView::OnViewJoints() 
{
   CDManipClientDC dc(this);

   m_bHideJoints = !m_bHideJoints;

   auto pDM = GetDisplayMgr();

   auto pDL = pDM->FindDisplayList(JNT_LIST);
   pDL->HideDisplayObjects(m_bHideJoints);
}

void CFEA2DView::OnUpdateViewJoints(CCmdUI* pCmdUI) 
{
   pCmdUI->SetCheck(!m_bHideJoints);
}

void CFEA2DView::OnViewLoads() 
{
   CDManipClientDC dc(this);

   m_bHideLoads = !m_bHideLoads;

   auto pDM = GetDisplayMgr();

   auto pDL = pDM->FindDisplayList(LOAD_LIST);
   pDL->HideDisplayObjects(m_bHideLoads);
}

void CFEA2DView::OnUpdateViewLoads(CCmdUI* pCmdUI) 
{
   pCmdUI->SetCheck(!m_bHideLoads);
}

void CFEA2DView::OnViewMembers() 
{
   CDManipClientDC dc(this);

   m_bHideMembers = !m_bHideMembers;

   auto pDM = GetDisplayMgr();

   auto pDL = pDM->FindDisplayList(MBR_LIST);
   pDL->HideDisplayObjects(m_bHideMembers);
}

void CFEA2DView::OnUpdateViewMembers(CCmdUI* pCmdUI) 
{
   pCmdUI->SetCheck(!m_bHideMembers);
}

void CFEA2DView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
   // Model changed, re-build everything
   if ( lHint == 1 )
   {
      auto pDM = GetDisplayMgr();

      pDM->ClearDisplayObjects();
      BuildJointDisplayObjects();
      BuildMemberDisplayObjects();
      BuildLoadDisplayObjects();

      Invalidate();
      UpdateWindow();
   }

   // Loads changed, rebuild loads
   if ( lHint == 2 )
   {
      BuildLoadDisplayObjects();
      Invalidate();
      UpdateWindow();
   }
}

BOOL CFEA2DView::OnPreparePrinting(CPrintInfo* pInfo) 
{
	if (DoPreparePrinting(pInfo))
   {
   	return CDisplayView::OnPreparePrinting(pInfo);
   }
   else
      return FALSE;
}

void CFEA2DView::OnSize(UINT nType, int cx, int cy)
{
   OnViewScaleToFit();
}