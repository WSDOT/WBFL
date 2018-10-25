#pragma once

#include "HorizontalAlignmentPage.h"

// CAlignmentDescriptionDlg

class CAlignmentDescriptionDlg : public CPropertySheet
{
	DECLARE_DYNAMIC(CAlignmentDescriptionDlg)

public:
	CAlignmentDescriptionDlg(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CAlignmentDescriptionDlg(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CAlignmentDescriptionDlg();

   CHorizontalAlignmentPage m_AlignmentPage;

protected:
	DECLARE_MESSAGE_MAP()
   void Init(void);
};


