// GraphicsTestView.cpp : implementation of the CGraphicsTestView class
//

#include "stdafx.h"
#include "GraphicsTest.h"

#include "GraphicsTestDoc.h"
#include "GraphicsTestView.h"

#include <GeomModel\WsdotPrecastBeams.h>
#include <GeomModel\Circle.h>
#include <GeomModel\Rectangle.h>
#include <GeomModel\Triangle.h>
#include <GeomModel\Section.h>
#include <GeomModel\CompositeShape.h>
#include <GraphicsLib\PointMapper.h>
#include <Geometry\Geometry.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


void SetMapper(grlibPointMapper* pmap, const RECT& srect, const gpRect2d& wrect);
/////////////////////////////////////////////////////////////////////////////
// CGraphicsTestView

IMPLEMENT_DYNCREATE(CGraphicsTestView, CView)

BEGIN_MESSAGE_MAP(CGraphicsTestView, CView)
	//{{AFX_MSG_MAP(CGraphicsTestView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphicsTestView construction/destruction

CGraphicsTestView::CGraphicsTestView()
{
	// TODO: add construction code here

}

CGraphicsTestView::~CGraphicsTestView()
{
}

BOOL CGraphicsTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CGraphicsTestView drawing

void CGraphicsTestView::OnDraw(CDC* pDC)
{
	CGraphicsTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

   RECT rect;
   GetClientRect(&rect);
   CRect left_rect (rect.left, rect.top, (rect.left+rect.right)/2, rect.bottom);
   CRect right_rect((rect.left+rect.right)/2, rect.top, rect.right, rect.bottom);

   // draw a composite shape in right window
   gmCompositeShape scomp;
   gmCircle scirc(gpPoint2d(0,30), 10);
   scirc.SetFillColor(RGB(255,0,0));
   gmRectangle srect(gpPoint2d(0,0), 10, 10);
   srect.SetFillColor(RGB(0,255,0));
   gmTriangle  stri(gpPoint2d(-5,5),15,10,5);
   stri.SetFillColor(RGB(0,0,255));
   scomp.AddShape(srect);
   scomp.AddShape(scirc);
   scomp.AddShape(stri);

   std::auto_ptr<gmIShape> pclon;
   pclon = std::auto_ptr<gmIShape>(scomp.CreateClone());
   pclon->Translate(gpSize2d(15,15));
   scomp.AddShape(*pclon);

   gpRect2d brect = scomp.GetBoundingBox();

   grlibPointMapper my_mapper;
   SetMapper(&my_mapper, right_rect, brect);
   scomp.Draw(pDC->GetSafeHdc(), my_mapper);

   // draw a slab on girder section in left window
   gmWsdotPrecastBeams& wpb = gmWsdotPrecastBeams::GetInstance();
   const gmPrecastBeam& w74g = wpb.W74G();
   std::auto_ptr<gmIShape> pw74g (w74g.CreateClone());
   pw74g->SetFillColor(RGB(100,100,100)); 
   gmRectangle slab(gpPoint2d(0,.2),2,.4);
   slab.SetFillColor(RGB(200,200,200));
   gmSection slab_girder;
   slab_girder.AddComponent(*pw74g,10, 10);
   slab_girder.AddComponent(slab, 10, 10);

   brect = slab_girder.GetBoundingBox(false);
   SetMapper(&my_mapper, left_rect, brect);
   slab_girder.Draw(pDC->GetSafeHdc(), my_mapper);
}

/////////////////////////////////////////////////////////////////////////////
// CGraphicsTestView printing

BOOL CGraphicsTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGraphicsTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGraphicsTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CGraphicsTestView diagnostics

#ifdef _DEBUG
void CGraphicsTestView::AssertValid() const
{
	CView::AssertValid();
}

void CGraphicsTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGraphicsTestDoc* CGraphicsTestView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGraphicsTestDoc)));
	return (CGraphicsTestDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGraphicsTestView message handlers
void SetMapper(grlibPointMapper* pmap, const RECT& rect, const gpRect2d& wrect)
{
   pmap->SetMappingMode(grlibPointMapper::Isotropic);
   pmap->SetWorldExt(wrect.Width(), wrect.Height());
   pmap->SetDeviceExt(rect.right - rect.left, rect.bottom - rect.top);
   // Map world origin to device origin
   long dx,dy;    // center of device space
   dx = (rect.left + rect.right)/2;
   dy = (rect.top + rect.bottom)/2;
   double x_center = (wrect.Left()+wrect.Right()) / 2;
   double y_center = (wrect.Top()+wrect.Bottom()) / 2;
   pmap->SetDeviceOrg( dx, dy );
   pmap->SetWorldOrg( x_center, y_center );
}
