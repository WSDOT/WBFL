// ArpNoticeDoc.cpp : implementation of the CArpNoticeDoc class
//

#include "stdafx.h"
#include "ArpNotice.h"

#include "ArpNoticeDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CArpNoticeDoc

IMPLEMENT_DYNCREATE(CArpNoticeDoc, CDocument)

BEGIN_MESSAGE_MAP(CArpNoticeDoc, CDocument)
	//{{AFX_MSG_MAP(CArpNoticeDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CArpNoticeDoc construction/destruction

CArpNoticeDoc::CArpNoticeDoc()
{
	// TODO: add one-time construction code here

}

CArpNoticeDoc::~CArpNoticeDoc()
{
}

BOOL CArpNoticeDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CArpNoticeDoc serialization

void CArpNoticeDoc::Serialize(CArchive& ar)
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
// CArpNoticeDoc diagnostics

#ifdef _DEBUG
void CArpNoticeDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CArpNoticeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CArpNoticeDoc commands
