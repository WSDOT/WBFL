///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2022  Washington State Department of Transportation
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

// EAFGraphChildFrame.h : header file
//

#include <EAF\EAFExp.h>
#include <EAF\EAFOutputChildFrame.h>
#include <Graphing/GraphManager.h>
#include <Graphing/GraphBuilder.h>
#include <IGraphManager.h>

#include <EAF\EAFViewControllerFactory.h>

#include <map>

class CEAFGraphView;

/////////////////////////////////////////////////////////////////////////////
// CEAFGraphChildFrame
class EAFCLASS CEAFGraphChildFrame : public CEAFOutputChildFrame, public CEAFViewControllerFactory
{
protected:
	CEAFGraphChildFrame();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CEAFGraphChildFrame)

// Attributes
public:

// Operations
public:
   virtual void RecalcLayout(BOOL bNotify = TRUE);

   bool CreateGraph(IndexType graphIdx);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEAFGraphChildFrame)
	//}}AFX_VIRTUAL


// Implementation
public:
   CEAFGraphView* GetGraphView();
   std::unique_ptr<WBFL::Graphing::GraphBuilder>& GetGraphBuilder();

protected:
	virtual ~CEAFGraphChildFrame();

// CEAFViewControllerFactory
protected:
   virtual void CreateViewController(IEAFViewController** ppController) override;

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

   // Generated message map functions
protected:
	//{{AFX_MSG(CEAFGraphChildFrame)
   afx_msg LRESULT OnCommandHelp(WPARAM, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
 

   // pointer to the graph manager
   // one of these is nullptr, the other is not
   WBFL::Graphing::GraphManager* m_pGraphMgr;  // for use with regular MFC Doc/View
   IGraphManager* m_pIGraphMgr; // for use with Agent/Broker

   std::unique_ptr<WBFL::Graphing::GraphBuilder> m_pMyGraphBuilder;

protected:
   // New version of MFC's CWnd::RepositionBars... deals with module state issues
	void MyRepositionBars(UINT nIDFirst, UINT nIDLast, UINT nIDLeftOver,
		UINT nFlag = reposDefault, LPRECT lpRectParam = nullptr,
		LPCRECT lpRectClient = nullptr, BOOL bStretch = TRUE);

   // returns a graph builder from the graph manager (not the close stored in m_pMyGraphBuilders)
   // This graph builder does not have access to the actual graph control window.
   std::unique_ptr<WBFL::Graphing::GraphBuilder>& GetGraphBuilder(IndexType index);

   friend CEAFGraphView; 
};
