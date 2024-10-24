// LBAMViewerView.h : interface of the CLBAMViewerView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LBAMVIEWERVIEW_H__9C9264B2_61E9_477D_A752_9D835E871087__INCLUDED_)
#define AFX_LBAMVIEWERVIEW_H__9C9264B2_61E9_477D_A752_9D835E871087__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "LBAMViewerDoc.h"
#include "GraphXyDisplayObjectImpl.h"
#include "LegendDisplayObject.h"
#include "ColorMapper.h"
#include "ChildFrm.h"

class CLBAMViewerView : public CDisplayView
{
   friend CChildFrame;

protected: // create from serialization only
	CLBAMViewerView();
	DECLARE_DYNCREATE(CLBAMViewerView)

// Attributes
public:
	CLBAMViewerDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLBAMViewerView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual void OnInitialUpdate();
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLBAMViewerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

   virtual DROPEFFECT CanDrop(COleDataObject* pDataObject,DWORD dwKeyState,IPoint2d* point);
   virtual void OnDropped(COleDataObject* pDataObject,DROPEFFECT dropEffect,IPoint2d* point);


private:
   StageIndexType m_CurrentStageIndex; // temporary used in building display lists
   std::shared_ptr<CGraphXyDisplayObject> m_Graph;
   std::shared_ptr<CLegendDisplayObject>  m_Legend;

   double m_RoadwayElevation; // top of our 'deck'

   void ClearTruckData(std::shared_ptr<WBFL::DManip::iDisplayMgr> dispMgr);

   bool BuildSupportDisplayObjects(CLBAMViewerDoc* pDoc, std::shared_ptr<WBFL::DManip::iDisplayMgr> dispMgr);
   bool BuildTempSupportDisplayObjects(CLBAMViewerDoc* pDoc, std::shared_ptr<WBFL::DManip::iDisplayMgr> dispMgr);
   void BuildSpanDisplayObjects(CLBAMViewerDoc* pDoc, std::shared_ptr<WBFL::DManip::iDisplayMgr> dispMgr);
   void BuildSSMDisplayObjects(CLBAMViewerDoc* pDoc, std::shared_ptr<WBFL::DManip::iDisplayMgr> dispMgr);
   void BuildGraphDisplayObjects(CLBAMViewerDoc* pDoc, std::shared_ptr<WBFL::DManip::iDisplayMgr> dispMgr);
   void GetVehicularLoad(ILBAMModel* model, LiveLoadModelType modelType, long vehicleIndex, IVehicularLoad** vehicularLoad);


   void DealWithExceptions();

// Generated message map functions
protected:
	//{{AFX_MSG(CLBAMViewerView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// flag to prevent drawing first time through
   bool m_First;
   bool m_FirstSize;
   bool m_DoUpdate; // block update from being reentrant
};

#ifndef _DEBUG  // debug version in LBAMViewerView.cpp
inline CLBAMViewerDoc* CLBAMViewerView::GetDocument()
   { return (CLBAMViewerDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LBAMVIEWERVIEW_H__9C9264B2_61E9_477D_A752_9D835E871087__INCLUDED_)
