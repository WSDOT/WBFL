// ArpNoticeView.h : interface of the CArpNoticeView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARPNOTICEVIEW_H__790C0064_8D43_11D3_89DC_006097C68A9C__INCLUDED_)
#define AFX_ARPNOTICEVIEW_H__790C0064_8D43_11D3_89DC_006097C68A9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CArpNoticeView : public CView
{
protected: // create from serialization only
	CArpNoticeView();
	DECLARE_DYNCREATE(CArpNoticeView)

// Attributes
public:
	CArpNoticeDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CArpNoticeView)
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
	virtual ~CArpNoticeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CArpNoticeView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ArpNoticeView.cpp
inline CArpNoticeDoc* CArpNoticeView::GetDocument()
   { return (CArpNoticeDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ARPNOTICEVIEW_H__790C0064_8D43_11D3_89DC_006097C68A9C__INCLUDED_)
