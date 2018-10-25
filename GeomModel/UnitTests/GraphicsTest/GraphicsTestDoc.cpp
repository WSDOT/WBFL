// GraphicsTestDoc.cpp : implementation of the CGraphicsTestDoc class
//

#include "stdafx.h"
#include "GraphicsTest.h"

#include "GraphicsTestDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraphicsTestDoc

IMPLEMENT_DYNCREATE(CGraphicsTestDoc, CDocument)

BEGIN_MESSAGE_MAP(CGraphicsTestDoc, CDocument)
	//{{AFX_MSG_MAP(CGraphicsTestDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphicsTestDoc construction/destruction

CGraphicsTestDoc::CGraphicsTestDoc()
{
	// TODO: add one-time construction code here

}

CGraphicsTestDoc::~CGraphicsTestDoc()
{
}

BOOL CGraphicsTestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CGraphicsTestDoc serialization

void CGraphicsTestDoc::Serialize(CArchive& ar)
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
// CGraphicsTestDoc diagnostics

#ifdef _DEBUG
void CGraphicsTestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGraphicsTestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGraphicsTestDoc commands
