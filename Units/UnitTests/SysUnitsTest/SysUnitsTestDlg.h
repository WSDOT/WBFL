// SysUnitsTestDlg.h : header file
//

#if !defined(AFX_SYSUNITSTESTDLG_H__7FA7E94C_578A_11D1_8AC0_0000F8776D5D__INCLUDED_)
#define AFX_SYSUNITSTESTDLG_H__7FA7E94C_578A_11D1_8AC0_0000F8776D5D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CSysUnitsTestDlg dialog

class CSysUnitsTestDlg : public CDialog
{
// Construction
public:
	CSysUnitsTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSysUnitsTestDlg)
	enum { IDD = IDD_SYSUNITSTEST_DIALOG };
	int		m_BaseLength;
	CString	m_UnitTagForCurrentBase;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSysUnitsTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSysUnitsTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBaseLengthChanged();
	afx_msg void OnRefresh();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYSUNITSTESTDLG_H__7FA7E94C_578A_11D1_8AC0_0000F8776D5D__INCLUDED_)
