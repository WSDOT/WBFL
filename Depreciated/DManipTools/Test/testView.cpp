// testView.cpp : implementation of the CTestView class
// 

#include "stdafx.h"
#include "test.h"

#include "testDoc.h"
#include "testView.h"
#include "DisplayObjectFactory.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestView

IMPLEMENT_DYNCREATE(CTestView, CDisplayView)

BEGIN_MESSAGE_MAP(CTestView, CDisplayView)
	//{{AFX_MSG_MAP(CTestView)
	ON_COMMAND(IDM_UPDATE, OnMenuUpdate)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CDisplayView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CDisplayView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CDisplayView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestView construction/destruction

CTestView::CTestView():
m_NumUpdates(0),
m_ColorIter(RGB(255,0,0), RGB(0,0,255), 10)
{
   AfxEnableControlContainer();
	// TODO: add construction code here

}

CTestView::~CTestView()
{
}

BOOL CTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CDisplayView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTestView drawing

void CTestView::OnDraw(CDC* pDC)
{
	CTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

   CDisplayView::OnDraw(pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CTestView printing

BOOL CTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	if (DoPreparePrinting(pInfo))
   {
   	return CDisplayView::OnPreparePrinting(pInfo);
   }
   else
      return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// CTestView diagnostics

#ifdef _DEBUG
void CTestView::AssertValid() const
{
	CDisplayView::AssertValid();
}

void CTestView::Dump(CDumpContext& dc) const
{
	CDisplayView::Dump(dc);
}

CTestDoc* CTestView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestDoc))); 
	return (CTestDoc*)m_pDocument;
}
#endif //_DEBUG
 
/////////////////////////////////////////////////////////////////////////////
// CTestView message handlers

void CTestView::OnInitialUpdate() 
{
   HRESULT hr;

   m_First = true;

   CDisplayView::OnInitialUpdate();
   EnableToolTips();

   CTestDoc* pDoc = GetDocument();
   CComPtr<iDisplayMgr> dispMgr;
   GetDisplayMgr(&dispMgr);

   // Setup the display object factories
   // local
   CDisplayObjectFactory* factory = new CDisplayObjectFactory(pDoc);
   iDisplayObjectFactory* pfac = (iDisplayObjectFactory*)factory->GetInterface(&IID_iDisplayObjectFactory);
   dispMgr->AddDisplayObjectFactory(pfac);
   pfac->Release();

   // in dmaniptools
   CComPtr<iDisplayObjectFactory> pfac2;
   hr = pfac2.CoCreateInstance(CLSID_DManipToolsDisplayObjectFactory);
   ATLASSERT(SUCCEEDED(hr));
   dispMgr->AddDisplayObjectFactory(pfac2);

   // Create display lists
   CComPtr<iDisplayList> dlList;
   hr = ::CoCreateInstance(CLSID_DisplayList,NULL,CLSCTX_ALL,IID_iDisplayList,(void**)&dlList);
   dlList->SetID(1);
   dispMgr->AddDisplayList(dlList);

   // set up temporary dc for mapping
   CDManipClientDC dc2(this);

   // graph
   hr = m_Graph.CoCreateInstance(CLSID_GraphXyDisplayObject);
   ATLASSERT(SUCCEEDED(hr));

   // add graph to display list
   CComPtr<iDisplayObject> gdo;
   hr = m_Graph->QueryInterface(IID_iDisplayObject, (void**)&gdo);
   ATLASSERT(SUCCEEDED(hr));
   dlList->AddDisplayObject(gdo);

   // legend
   hr = m_Legend.CoCreateInstance(CLSID_LegendDisplayObject);
   ATLASSERT(SUCCEEDED(hr));

   m_Legend->put_Title(CComBSTR("Legend Title"));
   m_Legend->put_DoDrawBorder(TRUE);
   m_Legend->put_IsDraggable(TRUE);

   // place legend in a convenient place (dependent on graph bounds set below)
   CComPtr<IPoint2d> pos;
   pos.CoCreateInstance(CLSID_Point2d);
   pos->put_X(6);
   pos->put_Y(-0.25);
   m_Legend->put_Position(pos,FALSE,FALSE);

   // add legend to display list
   CComPtr<iDisplayObject> ldo;
   hr = m_Legend->QueryInterface(IID_iDisplayObject, (void**)&ldo);
   ATLASSERT(SUCCEEDED(hr));
   dlList->AddDisplayObject(ldo);

}

void CTestView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
   if (m_First)
   {
      m_First = false;
      return;
   }

   HRESULT hr;
   m_NumUpdates++;

   CComPtr<iDisplayMgr> dispMgr;
   GetDisplayMgr(&dispMgr);

   // set up dc
   CDManipClientDC dc2(this);

   // clear out graph data and display objects
// m_Graph->ClearData();

   // set up bounds for graph
   CComPtr<IRect2d> graph_bounds;
   m_Graph->get_GraphBounds(&graph_bounds);

   graph_bounds->put_Left(0);
   graph_bounds->put_Right(10.0);
   graph_bounds->put_Top(1);
   graph_bounds->put_Bottom(-1);
  
   // create dataset and add it to the graph
   CComPtr<iGraphXyDataProvider> data;
   hr = data.CoCreateInstance(CLSID_GraphXyDataProvider);
   ATLASSERT(SUCCEEDED(hr));

   // set up colors and symbols
   COLORREF color = m_ColorIter.Item(m_NumUpdates-1);

   CComPtr<iDataPointFactory> factory;
   data->get_DataPointFactory(&factory);
   CComQIPtr<iSymbolLegendEntry> legend_entry(factory);

   // add entry to legend
   CString str;
   str.Format("Entry %d", m_NumUpdates);
   legend_entry->put_Name(CComBSTR(str));
   legend_entry->put_Color(color);
   legend_entry->put_SymbolCharacterCode(128+m_NumUpdates);
   legend_entry->put_SymbolSize(120);
   legend_entry->put_SymbolFontFace("Wingdings\0");
   legend_entry->put_DoDrawLine(TRUE);
   
   CComQIPtr<iLegendEntry> entry(legend_entry);
   m_Legend->AddEntry(entry);
   m_Legend->put_NumRows(1+ m_NumUpdates/4);

   // create data
   CComPtr<iDataSet2d> dataset;
   data->get_DataSet(&dataset);

   double loc = 0.0;
   double scale_fac = (11-m_NumUpdates)/10.0;
   while(loc<10.0)
   {
      // set left value
      CComPtr<IPoint2d> pnt;
      hr = pnt.CoCreateInstance(CLSID_Point2d);
      ATLASSERT(SUCCEEDED(hr)); 

      pnt->put_X(loc);
      pnt->put_Y(sin(loc)*scale_fac);

      dataset->Add(pnt);

      loc += 0.5;
   };

   m_Graph->AddData(data);
   m_Graph->put_DoDisplayGrid(VARIANT_TRUE);
   m_Graph->Commit();


   ScaleToFit();
}

void CTestView::OnMenuUpdate() 
{
   CTestDoc* pDoc = GetDocument();
   pDoc->UpdateAllViews(NULL);
}


void CTestView::PostNcDestroy() 
{
	m_Graph.Release();
	
	CDisplayView::PostNcDestroy();
}

DROPEFFECT CTestView::CanDrop(COleDataObject* pDataObject,DWORD dwKeyState,IPoint2d* point)
{
   // This override has to determine if the thing being dragged over it can
   // be dropped. In order to do that, it must unpackage the OleDataObject.
   //
   // The stuff in the data object is just from the display object. The display
   // objects need to be updated so that the client can attach an object to it
   // that knows how to package up domain specific information. At the same
   // time, this view needs to be able to get some domain specific hint 
   // as to the type of data that is going to be dropped.

   CComQIPtr<iDraggable> drag(m_Legend);
   UINT format = drag->Format();
   if ( pDataObject->IsDataAvailable(format) )
      return DROPEFFECT_MOVE;

   return DROPEFFECT_NONE;
}

void CTestView::OnDropped(COleDataObject* pDataObject,DROPEFFECT dropEffect,IPoint2d* point)
{
   AfxMessageBox("OnDropped");
}

void CTestView::OnSize(UINT nType, int cx, int cy) 
{
	CDisplayView::OnSize(nType, cx, cy);

   if (!m_First)
   	this->ScaleToFit();
}
