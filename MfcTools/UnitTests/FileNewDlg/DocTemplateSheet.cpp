// DocTemplateSheet.cpp : implementation file
//

#include "stdafx.h"
#include "filenewdlg.h"
#include "DocTemplateSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDocTemplateSheet

IMPLEMENT_DYNAMIC(CDocTemplateSheet, CPropertySheet)

CDocTemplateSheet::CDocTemplateSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CDocTemplateSheet::CDocTemplateSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

CDocTemplateSheet::~CDocTemplateSheet()
{
}


BEGIN_MESSAGE_MAP(CDocTemplateSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CDocTemplateSheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDocTemplateSheet message handlers
