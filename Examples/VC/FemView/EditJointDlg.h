
#pragma once
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
	JointIDType	m_JntID;
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

