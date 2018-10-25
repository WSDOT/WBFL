// WatermarkView.cpp : implementation of the CWatermarkView class
//

#include "stdafx.h"
#include "Watermark.h"

#include "WatermarkDoc.h"
#include "WatermarkView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWatermarkView

IMPLEMENT_DYNCREATE(CWatermarkView, CView)

BEGIN_MESSAGE_MAP(CWatermarkView, CView)
	//{{AFX_MSG_MAP(CWatermarkView)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWatermarkView construction/destruction

CWatermarkView::CWatermarkView()
{
	// TODO: add construction code here

}

CWatermarkView::~CWatermarkView()
{
}

BOOL CWatermarkView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CWatermarkView drawing

void CWatermarkView::OnDraw(CDC* pDC)
{
	CWatermarkDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CWatermarkView printing

BOOL CWatermarkView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CWatermarkView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CWatermarkView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CWatermarkView diagnostics

#ifdef _DEBUG
void CWatermarkView::AssertValid() const
{
	CView::AssertValid();
}

void CWatermarkView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWatermarkDoc* CWatermarkView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWatermarkDoc)));
	return (CWatermarkDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWatermarkView message handlers
