// FEA2DView.h : interface of the CFEA2DView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FEA2DVIEW_H__BCB8A0F1_E659_11D4_8B81_006097C68A9C__INCLUDED_)
#define AFX_FEA2DVIEW_H__BCB8A0F1_E659_11D4_8B81_006097C68A9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFEA2DView : public CDisplayView
{
protected: // create from serialization only
	CFEA2DView();
	DECLARE_DYNCREATE(CFEA2DView)

// Attributes
public:
	CFEA2DDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFEA2DView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFEA2DView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

   virtual DROPEFFECT CanDrop(COleDataObject* pDataObject,DWORD dwKeyState,IPoint2d* point);
   virtual void OnDropped(COleDataObject* pDataObject,DROPEFFECT dropEffect,IPoint2d* point);
//
//   virtual void OnChanged(IDisplayMgr* pDM,IDisplayList* pDL,IDisplayObject* pDO);
//   virtual void OnMoved(IDisplayMgr* pDM,IDisplayList* pDL,IDisplayObject* pDO,ISize2d* offset);

protected:
   bool m_bHideJoints;
   bool m_bHideMembers;
   bool m_bHideLoads;

   void BuildJointDisplayObjects();
   void BuildMemberDisplayObjects();
   void BuildLoadDisplayObjects();

// Generated message map functions
protected:
	//{{AFX_MSG(CFEA2DView)
	afx_msg void OnViewScaleToFit();
	afx_msg void OnViewCenterOnPoint();
	afx_msg void OnViewZoom();
	afx_msg void OnViewSetScale();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLoadsCreateLoading();
	afx_msg void OnLoadsAddPointLoad();
	afx_msg void OnViewJoints();
	afx_msg void OnUpdateViewJoints(CCmdUI* pCmdUI);
	afx_msg void OnViewMembers();
	afx_msg void OnUpdateViewMembers(CCmdUI* pCmdUI);
	afx_msg void OnViewLoads();
	afx_msg void OnUpdateViewLoads(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in FEA2DView.cpp
inline CFEA2DDoc* CFEA2DView::GetDocument()
   { return (CFEA2DDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FEA2DVIEW_H__BCB8A0F1_E659_11D4_8B81_006097C68A9C__INCLUDED_)
