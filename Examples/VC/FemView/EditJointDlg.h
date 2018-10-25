#if !defined(AFX_EDITJOINTDLG_H__1F8A97D0_F789_11D4_8B9B_006097C68A9C__INCLUDED_)
#define AFX_EDITJOINTDLG_H__1F8A97D0_F789_11D4_8B9B_006097C68A9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditJointDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEditJointDlg dialog

class CEditJointDlg : public CDialog
{
// Construction
public:
	CEditJointDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEditJointDlg)
	enum { IDD = IDD_EDITJOINT };
	BOOL	m_bSupportMz;
	BOOL	m_bSupportFx;
	BOOL	m_bSupportFy;
	double	m_X;
	double	m_Y;
	long	m_JntID;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditJointDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEditJointDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITJOINTDLG_H__1F8A97D0_F789_11D4_8B9B_006097C68A9C__INCLUDED_)
