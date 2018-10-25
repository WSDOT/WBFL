#if !defined(AFX_SUPPORTEDITDLG_H__082AFE4F_2AC3_4D9A_A80C_39E642199441__INCLUDED_)
#define AFX_SUPPORTEDITDLG_H__082AFE4F_2AC3_4D9A_A80C_39E642199441__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SupportEditDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSupportEditDlg dialog

class CSupportEditDlg : public CDialog
{
// Construction
public:
	CSupportEditDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSupportEditDlg)
	enum { IDD = IDD_SUPPORT_EDIT_DLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSupportEditDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSupportEditDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUPPORTEDITDLG_H__082AFE4F_2AC3_4D9A_A80C_39E642199441__INCLUDED_)
