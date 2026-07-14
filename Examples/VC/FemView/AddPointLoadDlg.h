
#pragma once
// AddPointLoadDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAddPointLoadDlg dialog

class CAddPointLoadDlg : public CDialog
{
// Construction
public:
   CAddPointLoadDlg(IFem2dModel* model,BOOL bMbrIDReadOnly = FALSE,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAddPointLoadDlg)
	enum { IDD = IDD_ADDPOINTLOAD };
	double	m_Fx;
	double	m_Fy;
	IDType		m_LoadingID;
	double	m_Location;
	MemberIDType	m_MbrID;
	double	m_Mz;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddPointLoadDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
   CComPtr<IFem2dModel> m_Model;
   BOOL m_bMbrIDReadOnly;

	// Generated message map functions
	//{{AFX_MSG(CAddPointLoadDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

