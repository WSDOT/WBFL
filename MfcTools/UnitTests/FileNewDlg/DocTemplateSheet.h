#if !defined(AFX_DocTemplateSHEET_H__BD01DE8B_5A3D_11D2_9D69_00609710E6CE__INCLUDED_)
#define AFX_DocTemplateSHEET_H__BD01DE8B_5A3D_11D2_9D69_00609710E6CE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DocTemplateSheet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDocTemplateSheet

class CDocTemplateSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CDocTemplateSheet)

// Construction
public:
	CDocTemplateSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CDocTemplateSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDocTemplateSheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDocTemplateSheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDocTemplateSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DocTemplateSHEET_H__BD01DE8B_5A3D_11D2_9D69_00609710E6CE__INCLUDED_)
