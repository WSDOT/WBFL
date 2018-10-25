#if !defined(AFX_REACTIONREPORTDLG_H__BA01C81A_FAE0_4D92_8047_434FA1A07F23__INCLUDED_)
#define AFX_REACTIONREPORTDLG_H__BA01C81A_FAE0_4D92_8047_434FA1A07F23__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReactionReportDlg.h : header file
//
#include <sstream>

/////////////////////////////////////////////////////////////////////////////
// CReactionReportDlg dialog

class CReactionReportDlg : public CDialog
{
// Construction
public:
	CReactionReportDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CReactionReportDlg)
	enum { IDD = IDD_REACTION_REPORT_DLG };
	//}}AFX_DATA


   std::_tostringstream m_Stream;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReactionReportDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CReactionReportDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REACTIONREPORTDLG_H__BA01C81A_FAE0_4D92_8047_434FA1A07F23__INCLUDED_)
