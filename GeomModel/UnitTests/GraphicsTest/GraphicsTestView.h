// GraphicsTestView.h : interface of the CGraphicsTestView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAPHICSTESTVIEW_H__09BC96CE_8907_11D1_9C68_00609710E6CE__INCLUDED_)
#define AFX_GRAPHICSTESTVIEW_H__09BC96CE_8907_11D1_9C68_00609710E6CE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CGraphicsTestView : public CView
{
protected: // create from serialization only
	CGraphicsTestView();
	DECLARE_DYNCREATE(CGraphicsTestView)

// Attributes
public:
	CGraphicsTestDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphicsTestView)
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
	virtual ~CGraphicsTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGraphicsTestView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in GraphicsTestView.cpp
inline CGraphicsTestDoc* CGraphicsTestView::GetDocument()
   { return (CGraphicsTestDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHICSTESTVIEW_H__09BC96CE_8907_11D1_9C68_00609710E6CE__INCLUDED_)
