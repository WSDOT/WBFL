// DimensionDoc.cpp : implementation of the CDimensionDoc class
//

#include "stdafx.h"
#include "Dimension.h"

#include "DimensionDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDimensionDoc

IMPLEMENT_DYNCREATE(CDimensionDoc, CDocument)

BEGIN_MESSAGE_MAP(CDimensionDoc, CDocument)
	//{{AFX_MSG_MAP(CDimensionDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDimensionDoc construction/destruction

CDimensionDoc::CDimensionDoc()
{
	// TODO: add one-time construction code here

}

CDimensionDoc::~CDimensionDoc()
{
}

BOOL CDimensionDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDimensionDoc serialization

void CDimensionDoc::Serialize(CArchive& ar)
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
// CDimensionDoc diagnostics

#ifdef _DEBUG
void CDimensionDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDimensionDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDimensionDoc commands
