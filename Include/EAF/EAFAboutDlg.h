#pragma once
#include <EAF\EAFExp.h>


// CEAFAboutDlg dialog

class EAFCLASS CEAFAboutDlg : public CDialog
{
	DECLARE_DYNAMIC(CEAFAboutDlg)

public:
   CEAFAboutDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEAFAboutDlg();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

   virtual HICON GetIconHandle() = 0;

   afx_msg void OnSomething(NMHDR* pNotifyStruct,LRESULT* pResult);


   CListCtrl m_PluginList;
   CImageList m_ImageList;

	DECLARE_MESSAGE_MAP()
public:
   virtual BOOL OnInitDialog();
};
