// DimensionView.h : interface of the CDimensionView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIMENSIONVIEW_H__2FC36C6E_6F5A_11D2_9D88_00609710E6CE__INCLUDED_)
#define AFX_DIMENSIONVIEW_H__2FC36C6E_6F5A_11D2_9D88_00609710E6CE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CDimensionView : public CView
{
protected: // create from serialization only
	CDimensionView();
	DECLARE_DYNCREATE(CDimensionView)

// Attributes
public:
	CDimensionDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDimensionView)
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
	virtual ~CDimensionView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDimensionView)
	afx_msg void OnSchematic();
	afx_msg void OnUpdateSchematic(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	bool m_Schematic;
};

#ifndef _DEBUG  // debug version in DimensionView.cpp
inline CDimensionDoc* CDimensionView::GetDocument()
   { return (CDimensionDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIMENSIONVIEW_H__2FC36C6E_6F5A_11D2_9D88_00609710E6CE__INCLUDED_)
