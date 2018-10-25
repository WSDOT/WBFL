#pragma once
#include "afxcmn.h"


// CMemberStrainLoadListPage dialog

class CMemberStrainLoadListPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CMemberStrainLoadListPage)

public:
	CMemberStrainLoadListPage();
	virtual ~CMemberStrainLoadListPage();

// Dialog Data
	enum { IDD = IDD_STRAIN_LOAD_LIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
   CListCtrl m_ctrlList;
   virtual BOOL OnInitDialog();
};
