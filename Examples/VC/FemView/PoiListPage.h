#pragma once
#include "afxcmn.h"


// CPoiListPage dialog

class CPoiListPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CPoiListPage)

public:
	CPoiListPage();
	virtual ~CPoiListPage();

// Dialog Data
	enum { IDD = IDD_POI_LIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
   CListCtrl m_ctrlList;
   virtual BOOL OnInitDialog();
};
