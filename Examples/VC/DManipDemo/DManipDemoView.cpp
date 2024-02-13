
// DManipDemoView.cpp : implementation of the CDManipDemoView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "DManipDemo.h"
#endif

#include "DManipDemoDoc.h"
#include "DManipDemoView.h"

#include <GeomModel/GeomModel.h>

#include <Colors.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDManipDemoView

IMPLEMENT_DYNCREATE(CDManipDemoView, CDisplayView)

BEGIN_MESSAGE_MAP(CDManipDemoView, CDisplayView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CDisplayView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CDisplayView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CDisplayView::OnFilePrintPreview)
	ON_WM_SIZE()
	ON_COMMAND(ID_ZOOM_IN, &CDManipDemoView::OnZoomIn)
	ON_COMMAND(ID_ZOOM_OUT, &CDManipDemoView::OnZoomOut)
	ON_COMMAND(ID_ZOOM_RECT, &CDManipDemoView::OnZoomRect)
	ON_COMMAND(ID_CENTER_ON_POINT, &CDManipDemoView::OnCenterOnPoint)
END_MESSAGE_MAP()

// CDManipDemoView construction/destruction

CDManipDemoView::CDManipDemoView() noexcept
{
	// TODO: add construction code here

}

CDManipDemoView::~CDManipDemoView()
{
}

BOOL CDManipDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CDisplayView::PreCreateWindow(cs);
}

// CDManipDemoView drawing

void CDManipDemoView::OnDraw(CDC* pDC)
{
	CDManipClientDC dc(this);
	CDisplayView::OnDraw(pDC);

	CDManipDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CDManipDemoView printing

BOOL CDManipDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDManipDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDManipDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CDManipDemoView diagnostics

#ifdef _DEBUG
void CDManipDemoView::AssertValid() const
{
	CDisplayView::AssertValid();
}

void CDManipDemoView::Dump(CDumpContext& dc) const
{
	CDisplayView::Dump(dc);
}

CDManipDemoDoc* CDManipDemoView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDManipDemoDoc)));
	return (CDManipDemoDoc*)m_pDocument;
}
#endif //_DEBUG


// CDManipDemoView message handlers


void CDManipDemoView::OnInitialUpdate()
{
	SetMappingMode(WBFL::DManip::MapMode::Isotropic);


	// TODO: Add your specialized code here and/or call the base class
	m_pDispMgr->CreateDisplayList(100);


	CDisplayView::OnInitialUpdate();

	ScaleToFit();
}


void CDManipDemoView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	CDManipClientDC dc(this);

	// TODO: Add your specialized code here and/or call the base class
	auto display_list = m_pDispMgr->FindDisplayList(100);

	std::shared_ptr<WBFL::Geometry::Rectangle> rect = std::make_shared<WBFL::Geometry::Rectangle>(WBFL::Geometry::Point2d(0, 0), 50, 100);

	auto disp_obj = WBFL::DManip::PointDisplayObject::Create();
	auto draw_strategy = WBFL::DManip::ShapeDrawStrategy::Create(rect);
	auto gravity_well = WBFL::DManip::ShapeGravityWellStrategy::Create(rect);
	disp_obj->SetDrawingStrategy(draw_strategy);
	disp_obj->SetGravityWellStrategy(gravity_well);

	draw_strategy->SetSolidFillColor(RED);
	draw_strategy->Fill(true);

	draw_strategy->SetSolidLineColor(BLACK);
	draw_strategy->SetSolidLineStyle(WBFL::DManip::LineStyleType::Dash);
	draw_strategy->SetSolidLineWidth(5);

	display_list->AddDisplayObject(disp_obj);
}


void CDManipDemoView::OnSize(UINT nType, int cx, int cy)
{
	CDisplayView::OnSize(nType, cx, cy);
}


void CDManipDemoView::OnZoomIn()
{
	// TODO: Add your command handler code here
	Zoom(1.1);
}


void CDManipDemoView::OnZoomOut()
{
	// TODO: Add your command handler code here
	Zoom(0.9);
}


void CDManipDemoView::OnZoomRect()
{
	// TODO: Add your command handler code here
	ActivateZoomTask();
}


void CDManipDemoView::OnCenterOnPoint()
{
	// TODO: Add your command handler code here
	ActivateCenterOnPointTask();
}
