
// DManipDemoView.h : interface of the CDManipDemoView class
//

#pragma once


class CDManipDemoView : public CDisplayView
{
protected: // create from serialization only
	CDManipDemoView() noexcept;
	DECLARE_DYNCREATE(CDManipDemoView)

// Attributes
public:
	CDManipDemoDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CDManipDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnZoomIn();
	afx_msg void OnZoomOut();
	afx_msg void OnZoomRect();
	afx_msg void OnCenterOnPoint();
};

#ifndef _DEBUG  // debug version in DManipDemoView.cpp
inline CDManipDemoDoc* CDManipDemoView::GetDocument() const
   { return reinterpret_cast<CDManipDemoDoc*>(m_pDocument); }
#endif

