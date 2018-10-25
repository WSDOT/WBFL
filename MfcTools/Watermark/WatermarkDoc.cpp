// WatermarkDoc.cpp : implementation of the CWatermarkDoc class
//

#include "stdafx.h"
#include "Watermark.h"

#include "WatermarkDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWatermarkDoc

IMPLEMENT_DYNCREATE(CWatermarkDoc, CDocument)

BEGIN_MESSAGE_MAP(CWatermarkDoc, CDocument)
	//{{AFX_MSG_MAP(CWatermarkDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWatermarkDoc construction/destruction

CWatermarkDoc::CWatermarkDoc()
{
	// TODO: add one-time construction code here

}

CWatermarkDoc::~CWatermarkDoc()
{
}

BOOL CWatermarkDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CWatermarkDoc serialization

void CWatermarkDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CWatermarkDoc diagnostics

#ifdef _DEBUG
void CWatermarkDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CWatermarkDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWatermarkDoc commands
