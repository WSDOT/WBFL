// FileNewDlgView.cpp : implementation of the CFileNewDlgView class
//

#include "stdafx.h"
#include "FileNewDlg.h"

#include "FileNewDlgDoc.h"
#include "FileNewDlgView.h"
#include <mfcTools\DocTemplateFinder.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileNewDlgView

IMPLEMENT_DYNCREATE(CFileNewDlgView, CView)

BEGIN_MESSAGE_MAP(CFileNewDlgView, CView)
	//{{AFX_MSG_MAP(CFileNewDlgView)
	ON_COMMAND(IDM_FILE_NEW_TEST, OnFileNewTest)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileNewDlgView construction/destruction

CFileNewDlgView::CFileNewDlgView()
{
	// TODO: add construction code here

}

CFileNewDlgView::~CFileNewDlgView()
{
}

BOOL CFileNewDlgView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CFileNewDlgView drawing

void CFileNewDlgView::OnDraw(CDC* pDC)
{
	CFileNewDlgDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CFileNewDlgView printing

BOOL CFileNewDlgView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CFileNewDlgView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CFileNewDlgView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CFileNewDlgView diagnostics

#ifdef _DEBUG
void CFileNewDlgView::AssertValid() const
{
	CView::AssertValid();
}

void CFileNewDlgView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFileNewDlgDoc* CFileNewDlgView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFileNewDlgDoc)));
	return (CFileNewDlgDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFileNewDlgView message handlers

void CFileNewDlgView::OnFileNewTest() 
{
   std::vector<std::string> dirvec;
   dirvec.push_back("\\wbfl\\mfcTools\\UnitTests\\FileNewDlg");
   dirvec.push_back("\\wbfl\\mfcTools\\UnitTests\\FileNewDlg\\Level2");
   mfcDocTemplateFinder fndlg(dirvec,"dot");

   CWinApp* papp = AfxGetApp();
   HICON hentry = papp->LoadIcon(IDI_TICON);
   ASSERT(hentry);
   fndlg.SetIcon(hentry);

   CString msg;
   std::string fn;
   mfcDocTemplateFinder::GetTemplateFileResult res = fndlg.GetTemplateFile(fn);
   if (res==mfcDocTemplateFinder::ValidFileSelected)
      msg = CString("Valid File was: ")+CString(fn.c_str());
   else if (res==mfcDocTemplateFinder::CancelledSelection)
      msg ="File Operation Cancelled";
   else if (res==mfcDocTemplateFinder::DefaultFileSelected)
      msg ="Default File Selected";
   else if (res==mfcDocTemplateFinder::SelectedFileThatDoesntExist)
      msg ="Selected File That Doesnt Exist";
   else
      ASSERT(0);

   AfxMessageBox(msg);
}
