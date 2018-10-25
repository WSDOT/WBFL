#if !defined(AFX_EDITMEMBERDLG_H__1F8A97D1_F789_11D4_8B9B_006097C68A9C__INCLUDED_)
#define AFX_EDITMEMBERDLG_H__1F8A97D1_F789_11D4_8B9B_006097C68A9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditMemberDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEditMemberDlg dialog

class CEditMemberDlg : public CDialog
{
// Construction
public:
	CEditMemberDlg(IFem2dModel* pModel,BOOL bMbrIDReadOnly = FALSE,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEditMemberDlg)
	enum { IDD = IDD_EDITMEMBER };
	Float64	m_EA;
	Float64	m_EI;
	JointIDType m_EndJoint;
	MemberIDType	m_MbrID;
	BOOL	m_bReleaseMzAtEnd;
	BOOL	m_bReleaseMzAtStart;
	JointIDType		m_StartJoint;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditMemberDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
   CComPtr<IFem2dModel> m_Model;
   BOOL m_bMbrIDReadOnly;

	// Generated message map functions
	//{{AFX_MSG(CEditMemberDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITMEMBERDLG_H__1F8A97D1_F789_11D4_8B9B_006097C68A9C__INCLUDED_)
