#pragma once
#include "afxcmn.h"


// CJointListPage dialog

class CJointListPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CJointListPage)

public:
	CJointListPage();
	virtual ~CJointListPage();

// Dialog Data
	enum { IDD = IDD_JOINT_LIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
   CListCtrl m_ctrlList;
   virtual BOOL OnInitDialog();
};
