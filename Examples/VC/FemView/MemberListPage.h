#pragma once
#include "afxcmn.h"


// MemberListPage dialog

class CMemberListPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CMemberListPage)

public:
	CMemberListPage();
	virtual ~CMemberListPage();

// Dialog Data
	enum { IDD = IDD_MEMBER_LIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
   CListCtrl m_ctrlList;
   virtual BOOL OnInitDialog();
};
