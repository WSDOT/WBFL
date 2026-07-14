
#pragma once
// CreateLoadingDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCreateLoadingDlg dialog

class CCreateLoadingDlg : public CDialog
{
// Construction
public:
	CCreateLoadingDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCreateLoadingDlg)
	enum { IDD = IDD_CREATELOADING };
	LoadCaseIDType	m_ID;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCreateLoadingDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCreateLoadingDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

