// FileNewDlgView.h : interface of the CFileNewDlgView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILENEWDLGVIEW_H__BD01DE81_5A3D_11D2_9D69_00609710E6CE__INCLUDED_)
#define AFX_FILENEWDLGVIEW_H__BD01DE81_5A3D_11D2_9D69_00609710E6CE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//#pragma warning ( disable : 4231 4251 4786 )
#pragma warning( disable : 4251 )

class CFileNewDlgView : public CView
{
protected: // create from serialization only
	CFileNewDlgView();
	DECLARE_DYNCREATE(CFileNewDlgView)

// Attributes
public:
	CFileNewDlgDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileNewDlgView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFileNewDlgView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFileNewDlgView)
	afx_msg void OnFileNewTest();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in FileNewDlgView.cpp
inline CFileNewDlgDoc* CFileNewDlgView::GetDocument()
   { return (CFileNewDlgDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILENEWDLGVIEW_H__BD01DE81_5A3D_11D2_9D69_00609710E6CE__INCLUDED_)
