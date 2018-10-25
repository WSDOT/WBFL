// FileNewDlgDoc.cpp : implementation of the CFileNewDlgDoc class
//

#include "stdafx.h"
#include "FileNewDlg.h"

#include "FileNewDlgDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileNewDlgDoc

IMPLEMENT_DYNCREATE(CFileNewDlgDoc, CDocument)

BEGIN_MESSAGE_MAP(CFileNewDlgDoc, CDocument)
	//{{AFX_MSG_MAP(CFileNewDlgDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileNewDlgDoc construction/destruction

CFileNewDlgDoc::CFileNewDlgDoc()
{
	// TODO: add one-time construction code here

}

CFileNewDlgDoc::~CFileNewDlgDoc()
{
}

BOOL CFileNewDlgDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CFileNewDlgDoc serialization

void CFileNewDlgDoc::Serialize(CArchive& ar)
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
// CFileNewDlgDoc diagnostics

#ifdef _DEBUG
void CFileNewDlgDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFileNewDlgDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFileNewDlgDoc commands
