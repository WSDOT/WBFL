#pragma once
#include "afxcmn.h"


// CPointLoadListPage dialog

class CPointLoadListPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CPointLoadListPage)

public:
	CPointLoadListPage();
	virtual ~CPointLoadListPage();

// Dialog Data
	enum { IDD = IDD_POINT_LOAD_LIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
   CListCtrl m_ctrlList;
   virtual BOOL OnInitDialog();
};
