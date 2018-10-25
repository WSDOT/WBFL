#pragma once
#include "afxcmn.h"


// CJointLoadListPage dialog

class CJointLoadListPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CJointLoadListPage)

public:
	CJointLoadListPage();
	virtual ~CJointLoadListPage();

// Dialog Data
	enum { IDD = IDD_JOINT_LOAD_LIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
   CListCtrl m_ctrlList;
   virtual BOOL OnInitDialog();
};
