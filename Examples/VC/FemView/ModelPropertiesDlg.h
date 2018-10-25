#pragma once

#include "JointListPage.h"
#include "MemberListPage.h"
#include "JointLoadListPage.h"
#include "PointLoadListPage.h"
#include "DistributedLoadListPage.h"
#include "MemberStrainLoadListPage.h"
#include "PoiListPage.h"
#include "ResultsListPage.h"

// CModelPropertiesDlg

class CModelPropertiesDlg : public CPropertySheet
{
	DECLARE_DYNAMIC(CModelPropertiesDlg)

public:
	CModelPropertiesDlg(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CModelPropertiesDlg();

   CComPtr<IFem2dModel> m_pFem2d;

protected:
	DECLARE_MESSAGE_MAP()

   void Init();

   CJointListPage m_JointPage;
   CMemberListPage m_MemberPage;
   CJointLoadListPage m_JointLoadPage;
   CPointLoadListPage m_PointLoadPage;
   CDistributedLoadListPage m_DistributedLoadPage;
   CMemberStrainLoadListPage m_StrainLoadPage;
   CPoiListPage m_PoiPage;
   CResultsListPage m_ResultsPage;
};


