// TestProgressDlg.h : header file
//

#if !defined(AFX_TESTPROGRESSDLG_H__3557B780_9AED_40B9_A90C_4DF5B7DE04EF__INCLUDED_)
#define AFX_TESTPROGRESSDLG_H__3557B780_9AED_40B9_A90C_4DF5B7DE04EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestProgressDlg dialog

class CTestProgressDlg : public CDialog
{
// Construction
public:
	CTestProgressDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestProgressDlg)
	enum { IDD = IDD_TESTPROGRESS_DIALOG };
	CEdit	m_FileNameEdit;
	CButton	m_CheckFileNameCtrl;
	CButton	m_EnableGaugeCtrl;
	CButton	m_EnableCancelCtrl;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestProgressDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	HICON m_hIcon;
   bool  m_IsLogFileOpen;

   CComPtr<IProgressMonitorWindow> m_ProgressMon;

	// Generated message map functions
	//{{AFX_MSG(CTestProgressDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTest1();
	afx_msg void OnCheckFilename();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

   void UpdateLogFile();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTPROGRESSDLG_H__3557B780_9AED_40B9_A90C_4DF5B7DE04EF__INCLUDED_)
