///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2021  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the Alternate Route Library Open Source License as published by 
// the Washington State Department of Transportation, Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but is distributed 
// AS IS, WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See the Alternate Route Library Open Source 
// License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License 
// along with this program; if not, write to the Washington State Department of 
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////


#pragma once

// EAFGraphView.h : header file
//

#include <EAF\EAFExp.h>
#include <IGraphManager.h>
#include <EAF\EAFView.h>

class CEAFGraphChildFrame;

// Creation data that is needed by the graph view
struct EAFCLASS CEAFGraphViewCreationData
{
   // The graph manager
   CGraphManager* m_pGraphMgr;  // Use this when for regular Doc/View
   IGraphManager* m_pIGraphMgr; // Use this when for the Agent/Broker architecture

   IndexType m_GraphIndex; // Index of the graph to initialize the view with

   CEAFGraphViewCreationData()
   {
      m_GraphIndex = 0;
      m_pGraphMgr  = nullptr;
      m_pIGraphMgr = nullptr;
   }
};

/////////////////////////////////////////////////////////////////////////////
// CEAFGraphView view
class EAFCLASS CEAFGraphView : public CEAFView
{
public:
protected:
	CEAFGraphView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CEAFGraphView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEAFGraphView)
	public:
	virtual void OnInitialUpdate();
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);

   virtual CRect GetDrawingRect();

   CEAFGraphChildFrame* GetFrame();
   std::shared_ptr<CGraphBuilder> GetGraphBuilder();

	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);

protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
public:
   void UpdateViewTitle();

protected:
	virtual ~CEAFGraphView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

   // Generated message map functions
protected:
	//{{AFX_MSG(CEAFGraphView)
	afx_msg void OnUpdateFilePrint(CCmdUI* pCmdUI);
	afx_msg void OnLButtonDblClk(UINT nFlags,CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

   CRect m_PrintRect;
   bool m_bIsPrinting;
	BOOL m_bUpdateError;   // true if an error occured while updating the report contents
	std::_tstring m_ErrorMsg;

};
