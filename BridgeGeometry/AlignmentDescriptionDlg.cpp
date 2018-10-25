// AlignmentDescriptionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BridgeGeometry.h"
#include "AlignmentDescriptionDlg.h"


// CAlignmentDescriptionDlg

IMPLEMENT_DYNAMIC(CAlignmentDescriptionDlg, CPropertySheet)

CAlignmentDescriptionDlg::CAlignmentDescriptionDlg(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
   Init();
}

CAlignmentDescriptionDlg::CAlignmentDescriptionDlg(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
   Init();
}

CAlignmentDescriptionDlg::~CAlignmentDescriptionDlg()
{
}


BEGIN_MESSAGE_MAP(CAlignmentDescriptionDlg, CPropertySheet)
END_MESSAGE_MAP()


// CAlignmentDescriptionDlg message handlers

void CAlignmentDescriptionDlg::Init(void)
{
   AddPage(&m_AlignmentPage);
}
