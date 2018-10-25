// ModelPropertiesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FEA2D.h"
#include "ModelPropertiesDlg.h"


// CModelPropertiesDlg

IMPLEMENT_DYNAMIC(CModelPropertiesDlg, CPropertySheet)

CModelPropertiesDlg::CModelPropertiesDlg(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
   Init();
}

CModelPropertiesDlg::~CModelPropertiesDlg()
{
}


BEGIN_MESSAGE_MAP(CModelPropertiesDlg, CPropertySheet)
END_MESSAGE_MAP()


// CModelPropertiesDlg message handlers
void CModelPropertiesDlg::Init()
{
   AddPage(&m_JointPage);
   AddPage(&m_MemberPage);
   AddPage(&m_JointLoadPage);
   AddPage(&m_PointLoadPage);
   AddPage(&m_DistributedLoadPage);
   AddPage(&m_StrainLoadPage);
   AddPage(&m_PoiPage);
}
