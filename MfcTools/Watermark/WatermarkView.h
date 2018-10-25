// WatermarkView.h : interface of the CWatermarkView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WATERMARKVIEW_H__FD924340_315B_11D2_8EB6_006097DF3C68__INCLUDED_)
#define AFX_WATERMARKVIEW_H__FD924340_315B_11D2_8EB6_006097DF3C68__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CWatermarkView : public CView
{
protected: // create from serialization only
	CWatermarkView();
	DECLARE_DYNCREATE(CWatermarkView)

// Attributes
public:
	CWatermarkDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWatermarkView)
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
	virtual ~CWatermarkView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CWatermarkView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in WatermarkView.cpp
inline CWatermarkDoc* CWatermarkView::GetDocument()
   { return (CWatermarkDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WATERMARKVIEW_H__FD924340_315B_11D2_8EB6_006097DF3C68__INCLUDED_)
