// DimensionView.cpp : implementation of the CDimensionView class
//

#include "stdafx.h"
#include "Dimension.h"

#include "DimensionDoc.h"
#include "DimensionView.h"

#include <graphicslib\pointmapper.h>
#include <graphicslib\dimension.h>
#include <geommodel\geommodel.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDimensionView

IMPLEMENT_DYNCREATE(CDimensionView, CView)

BEGIN_MESSAGE_MAP(CDimensionView, CView)
	//{{AFX_MSG_MAP(CDimensionView)
	ON_COMMAND(IDM_SCHEMATIC, OnSchematic)
	ON_UPDATE_COMMAND_UI(IDM_SCHEMATIC, OnUpdateSchematic)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDimensionView construction/destruction

CDimensionView::CDimensionView():
m_Schematic(false)
{
	// TODO: add construction code here

}

CDimensionView::~CDimensionView()
{
}

BOOL CDimensionView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDimensionView drawing

void CDimensionView::OnDraw(CDC* pDC)
{
	CDimensionDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

   CRect rect;
   GetClientRect(rect);

   bool bIsotropic = !m_Schematic;
   bool bScale = false;
   grlibPointMapper mapper;
   Int32 center_x,center_y;

   grlibPointMapper::MapMode mapmode;
   mapmode = ( bIsotropic ? grlibPointMapper::Isotropic : grlibPointMapper::Anisotropic );
   grlibPointMapper::MapModeModifier modifier;
   modifier = (bScale ? grlibPointMapper::BestFitXY : grlibPointMapper::NoFit);
   mapper.SetMappingMode(mapmode);
   mapper.SetMappingModeModifier(modifier);
   mapper.SetDeviceExt(rect.right - rect.left, rect.bottom - rect.top);
   center_x = (rect.left + rect.right)/2;
   center_y = (rect.top + rect.bottom)/2;
   mapper.SetDeviceOrg(center_x,center_y);

   gpRect2d box(0,0,1000., 1000.);
   mapper.SetWorldExt( box.Size() );
   mapper.SetWorldOrg( box.Center() );

   HDC hDC = pDC->GetSafeHdc();
   
   {
      // horizontal dimensions
      gpPoint2d  left(0,300);
      gpPoint2d  right(400,700);
      grDimension my_dim(left, right, "Above");
      my_dim.Draw(hDC, mapper);
      my_dim.SetSpaceFactor(1);
      my_dim.SetLabel("Above Factor 1");
      my_dim.Draw(hDC, mapper);
      my_dim.SetSpaceFactor(2);
      my_dim.SetHorizontalDimensionPos(grDimension::Right);
      my_dim.SetLabel("Right Factor 2 \n Two Lines");
      my_dim.Draw(hDC, mapper);

      grDimension myb_dim(right, left, "Below");
      myb_dim.SetVerticalDimensionPos(grDimension::Below);
      myb_dim.Draw(hDC, mapper);
      myb_dim.SetStyle(grDimension::Horizontal);
      myb_dim.SetSpaceFactor(2);
      myb_dim.SetLabel("Space Factor 2\nTwo Lines");
      myb_dim.Draw(hDC, mapper);

      // draw bounding box
      gpRect2d drect = myb_dim.GetBoundingBox(hDC, mapper);
      gpPoint2d pnt = drect.Center();
      gmRectangle gmr(pnt, drect.Width(), drect.Height());
      gmr.EnableFillMode(false);
      gmr.SetBorderColor(RGB(0,0,255));
      gmr.Draw(hDC, mapper);

      myb_dim.SetHorizontalDimensionPos(grDimension::Left);
      myb_dim.SetSpaceFactor(2);
      myb_dim.SetLabel("Left Factor 2");
      myb_dim.Draw(hDC, mapper);


      // draw object being dimensioned
      HPEN hRedPen = (HPEN)::CreatePen(PS_SOLID, 1, RGB( 255,   0,   0) );
      HPEN hOldPen = (HPEN)::SelectObject(hDC,hRedPen);
      POINT p;
      long dvx, dvy;
      mapper.WPtoDP(left.X(), left.Y(), &dvx, &dvy);
      ::MoveToEx(hDC, dvx, dvy, &p);
      mapper.WPtoDP(right.X(), right.Y(), &dvx, &dvy);
      ::LineTo(hDC, dvx, dvy);

      ::SelectObject(hDC,hOldPen);
      ::DeleteObject(hRedPen);

   }

   {
      // vertical dimensions
      gpPoint2d  left(600,300);
      gpPoint2d  right(900,700);
      grDimension my_dim(left, right, "Above");
      my_dim.SetStyle(grDimension::Vertical);
      my_dim.SetLabel("Vertical Above");
      my_dim.Draw(hDC, mapper);
      my_dim.SetSpaceFactor(1);
      my_dim.SetLabel("Above Factor 1");
      my_dim.Draw(hDC, mapper);
      my_dim.SetSpaceFactor(2);
      my_dim.SetHorizontalDimensionPos(grDimension::Right);
      my_dim.SetAdditionalOffset(100.);
      my_dim.SetLabel("Right Factor 2");
      my_dim.Draw(hDC, mapper);

      grDimension myb_dim(right, left, "Below");
      myb_dim.SetVerticalDimensionPos(grDimension::Below);
      myb_dim.SetStyle(grDimension::Vertical);
      myb_dim.SetLabel("Vertical Below");
      myb_dim.Draw(hDC, mapper);
      myb_dim.SetSpaceFactor(1);
      myb_dim.SetLabel("Space Factor 1");
      myb_dim.Draw(hDC, mapper);
      myb_dim.SetHorizontalDimensionPos(grDimension::Left);
      myb_dim.SetSpaceFactor(2);
      myb_dim.SetLabel("Left Factor 2");
      myb_dim.Draw(hDC, mapper);

      // draw bounding box
      gpRect2d drect = myb_dim.GetBoundingBox(hDC, mapper);
      gpPoint2d pnt = drect.Center();
      gmRectangle gmr(pnt, drect.Width(), drect.Height());
      gmr.EnableFillMode(false);
      gmr.SetBorderColor(RGB(0,0,255));
      gmr.Draw(hDC, mapper);

#if defined _DEBUG
   dbgDumpContext dc;
   myb_dim.Dump(dc);
#endif
      // draw object being dimensioned
      HPEN hRedPen = (HPEN)::CreatePen(PS_SOLID, 1, RGB( 255,   0,   0) );
      HPEN hOldPen = (HPEN)::SelectObject(hDC,hRedPen);
      POINT p;
      long dvx, dvy;
      mapper.WPtoDP(left.X(), left.Y(), &dvx, &dvy);
      ::MoveToEx(hDC, dvx, dvy, &p);
      mapper.WPtoDP(right.X(), right.Y(), &dvx, &dvy);
      ::LineTo(hDC, dvx, dvy);

      ::SelectObject(hDC,hOldPen);
      ::DeleteObject(hRedPen);

   }

}

/////////////////////////////////////////////////////////////////////////////
// CDimensionView printing

BOOL CDimensionView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDimensionView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDimensionView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDimensionView diagnostics

#ifdef _DEBUG
void CDimensionView::AssertValid() const
{
	CView::AssertValid();
}

void CDimensionView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDimensionDoc* CDimensionView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDimensionDoc)));
	return (CDimensionDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDimensionView message handlers

void CDimensionView::OnSchematic() 
{
   m_Schematic=!m_Schematic;
   Invalidate(TRUE);
}

void CDimensionView::OnUpdateSchematic(CCmdUI* pCmdUI) 
{
   pCmdUI->SetCheck(m_Schematic);
   pCmdUI->Enable(TRUE);
}
