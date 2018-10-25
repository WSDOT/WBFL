// ArpNoticeView.cpp : implementation of the CArpNoticeView class
//

#include "stdafx.h"
#include "ArpNotice.h"

#include "ArpNoticeDoc.h"
#include "ArpNoticeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CArpNoticeView

IMPLEMENT_DYNCREATE(CArpNoticeView, CView)

BEGIN_MESSAGE_MAP(CArpNoticeView, CView)
	//{{AFX_MSG_MAP(CArpNoticeView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CArpNoticeView construction/destruction

CArpNoticeView::CArpNoticeView()
{
	// TODO: add construction code here

}

CArpNoticeView::~CArpNoticeView()
{
}

BOOL CArpNoticeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CArpNoticeView drawing

void CArpNoticeView::OnDraw(CDC* pDC)
{
	CArpNoticeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CArpNoticeView printing

BOOL CArpNoticeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CArpNoticeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CArpNoticeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CArpNoticeView diagnostics

#ifdef _DEBUG
void CArpNoticeView::AssertValid() const
{
	CView::AssertValid();
}

void CArpNoticeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CArpNoticeDoc* CArpNoticeView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CArpNoticeDoc)));
	return (CArpNoticeDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CArpNoticeView message handlers
