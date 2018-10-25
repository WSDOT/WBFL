#if !defined(AFX_TEMPORARYSUPPORTEDITDLG_H__52D37275_5BA0_410C_9AAC_737B4C6868D5__INCLUDED_)
#define AFX_TEMPORARYSUPPORTEDITDLG_H__52D37275_5BA0_410C_9AAC_737B4C6868D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TemporarySupportEditDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTemporarySupportEditDlg dialog

class CTemporarySupportEditDlg : public CDialog
{
// Construction
public:
	CTemporarySupportEditDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTemporarySupportEditDlg)
	enum { IDD = IDD_TEMPORARY_SUPPORT_DLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTemporarySupportEditDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTemporarySupportEditDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEMPORARYSUPPORTEDITDLG_H__52D37275_5BA0_410C_9AAC_737B4C6868D5__INCLUDED_)
