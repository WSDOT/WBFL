#pragma once
#include "afxcmn.h"


// CDistributedLoadListPage dialog

class CDistributedLoadListPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CDistributedLoadListPage)

public:
	CDistributedLoadListPage();
	virtual ~CDistributedLoadListPage();

// Dialog Data
	enum { IDD = IDD_DISTRIBUTED_LOAD_LIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
   CListCtrl m_ctrlList;
   virtual BOOL OnInitDialog();
};
