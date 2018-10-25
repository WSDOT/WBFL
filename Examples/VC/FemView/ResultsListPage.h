#pragma once
#include "afxcmn.h"


// CResultsListPage dialog

class CResultsListPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CResultsListPage)

public:
	CResultsListPage();
	virtual ~CResultsListPage();

// Dialog Data
	enum { IDD = IDD_RESULTS_LIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

   afx_msg void OnLoadingChanged();

	DECLARE_MESSAGE_MAP()
public:
   CListCtrl m_ctrlList;
   virtual BOOL OnInitDialog();
};
