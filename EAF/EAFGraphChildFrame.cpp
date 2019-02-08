///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2019  Washington State Department of Transportation
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


#include "stdafx.h"
#include "resource.h"
#include <EAF\EAFGraphChildFrame.h>
#include <EAF\EAFGraphView.h>
#include <EAF\EAFHelp.h>
#include <EAF\EAFGraphBuilderBase.h>

// include files needed to get the RecalcLayout override working
#include <oleimpl2.h>
#include <afximpl.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CEAFGraphChildFrame


IMPLEMENT_DYNCREATE(CEAFGraphChildFrame, CEAFOutputChildFrame)

CEAFGraphChildFrame::CEAFGraphChildFrame()
{
   m_pGraphMgr = nullptr;
   m_pIGraphMgr = nullptr;
}

CEAFGraphChildFrame::~CEAFGraphChildFrame()
{
}

BEGIN_MESSAGE_MAP(CEAFGraphChildFrame, CEAFOutputChildFrame)
	//{{AFX_MSG_MAP(CEAFGraphChildFrame)
	ON_MESSAGE(WM_HELP, OnCommandHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CEAFGraphChildFrame::CreateViewController(IEAFViewController** ppController)
{
   if (ppController )
   {
      *ppController = nullptr;
      CEAFGraphBuilderBase* pBuilder = dynamic_cast<CEAFGraphBuilderBase*>(m_pMyGraphBuilder.get());
      if (pBuilder)
      {
         pBuilder->CreateViewController(ppController);
      }
   }
}

LRESULT CEAFGraphChildFrame::OnCommandHelp(WPARAM, LPARAM lParam)
{
   UINT nHID = m_pMyGraphBuilder->GetHelpID();
   if ( 0 < nHID )
   {
      EAFHelp( m_pMyGraphBuilder->GetDocumentationSetName(), nHID );
      return TRUE;
   }
   return FALSE;
}

CEAFGraphView* CEAFGraphChildFrame::GetGraphView()
{
   CWnd* pWnd = GetActiveView();
   CEAFGraphView* pGraphView = (CEAFGraphView*)pWnd;
   return pGraphView;
}

std::shared_ptr<CGraphBuilder> CEAFGraphChildFrame::GetGraphBuilder()
{
   return m_pMyGraphBuilder;
}

bool CEAFGraphChildFrame::CreateGraph(IndexType graphIdx)
{
   std::shared_ptr<CGraphBuilder> pGraphBuilder = GetGraphBuilder(graphIdx);
   if ( pGraphBuilder == nullptr )
      return false;

   // Because multiple graph views can be created, we have to create a clone
   // of the graph builder. Each view needs its own unique graph builder.
   m_pMyGraphBuilder = std::shared_ptr<CGraphBuilder>(pGraphBuilder->Clone());

   if ( m_pMyGraphBuilder->InitializeGraphController(this,AFX_IDW_CONTROLBAR_LAST) < 0 )
      return false;

   RecalcLayout();

   CEAFGraphView* pGraphView = GetGraphView();
   pGraphView->UpdateViewTitle();
   pGraphView->Invalidate();
   pGraphView->UpdateWindow();

   return true;
}

std::shared_ptr<CGraphBuilder> CEAFGraphChildFrame::GetGraphBuilder(IndexType index)
{
   if ( m_pGraphMgr )
   {
      return m_pGraphMgr->GetGraphBuilder(index);
   }
   else
   {
      return m_pIGraphMgr->GetGraphBuilder(index);
   }
}


#ifdef _DEBUG
void CEAFGraphChildFrame::AssertValid() const
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
	CEAFOutputChildFrame::AssertValid();
}

void CEAFGraphChildFrame::Dump(CDumpContext& dc) const
{
	CEAFOutputChildFrame::Dump(dc);
}
#endif //_DEBUG


void CEAFGraphChildFrame::RecalcLayout(BOOL bNotify)
{
   // DO NOT CALL THE BASE CLASS VERSION
   //CEAFOutputChildFrame::RecalcLayout(bNotify);

   // The base class version doesn't work for us... More specifically, CWnd::RepositionBars doesn't
   // work for us because the module state is incorrect when getting a CWnd pointer from the window 
   // handle map. Since CWnd::RepositionBars is not virtual, we have re-implement RecalcLayout
   // so that it calls our special version of RepositionBars (see below)

	if (m_bInRecalcLayout)
		return;

	m_bInRecalcLayout = TRUE;
	// clear idle flags for recalc layout if called elsewhere
	if (m_nIdleFlags & idleNotify)
		bNotify = TRUE;
	m_nIdleFlags &= ~(idleLayout|idleNotify);

#ifndef _AFX_NO_OLE_SUPPORT
	// call the layout hook -- OLE support uses this hook
	if (bNotify && m_pNotifyHook != nullptr)
		m_pNotifyHook->OnRecalcLayout();
#endif

   // RAB: FWS_SNAPTOBARS is only used with mini-frame windows and we
   // don't have any so just call the default RepositionBars

	// reposition all the child windows (regardless of ID)
	if (GetStyle() & FWS_SNAPTOBARS)
	{
		CRect rect(0, 0, 32767, 32767);
		RepositionBars(0, 0xffff, AFX_IDW_PANE_FIRST, reposQuery,
			&rect, &rect, FALSE);
		RepositionBars(0, 0xffff, AFX_IDW_PANE_FIRST, reposExtra,
			&m_rectBorder, &rect, TRUE);
		CalcWindowRect(&rect);
		SetWindowPos(nullptr, 0, 0, rect.Width(), rect.Height(),
			SWP_NOACTIVATE|SWP_NOMOVE|SWP_NOZORDER);
	}
	else
   {
      // RAB: this method is the culprit. It can't handle that the graph builder provided
      // control bar comes from a different DLL.... call our special version of RepositionBars
      // (if RepositionBars was virtual, we could have just re-defined it)
      // This is the only change from the base class version of this method

		//RepositionBars(0, 0xffff, AFX_IDW_PANE_FIRST, reposExtra, &m_rectBorder);
		MyRepositionBars(0, 0xffff, AFX_IDW_PANE_FIRST, reposExtra, &m_rectBorder);
   }

	m_bInRecalcLayout = FALSE;


   // RAB: Because the base class version is not being called, we are missing out
   // on the functionality provided by the license plate frame... repeat the
   // functionality here
   UpdateLPFrame();
}

void CEAFGraphChildFrame::MyRepositionBars(UINT nIDFirst, UINT nIDLast, UINT nIDLeftOver,
	UINT nFlags, LPRECT lpRectParam, LPCRECT lpRectClient, BOOL bStretch)
{
   // CWnd::RepositionBars is not a virtual method so we have to have a total replacement for it
   // just so we can override one line.... See RAB comment below

	ASSERT(nFlags == 0 || (nFlags & ~reposNoPosLeftOver) == reposQuery || 
			(nFlags & ~reposNoPosLeftOver) == reposExtra);

	// walk kids in order, control bars get the resize notification
	//   which allow them to shrink the client area
	// remaining size goes to the 'nIDLeftOver' pane
	// NOTE: nIDFirst->nIDLast are usually 0->0xffff

	AFX_SIZEPARENTPARAMS layout;
	HWND hWndLeftOver = nullptr;

	layout.bStretch = bStretch;
	layout.sizeTotal.cx = layout.sizeTotal.cy = 0;
	if (lpRectClient != nullptr)
		layout.rect = *lpRectClient;    // starting rect comes from parameter
	else
		GetClientRect(&layout.rect);    // starting rect comes from client rect

	if ((nFlags & ~reposNoPosLeftOver) != reposQuery)
		layout.hDWP = ::BeginDeferWindowPos(8); // reasonable guess
	else
		layout.hDWP = nullptr; // not actually doing layout

	for (HWND hWndChild = ::GetTopWindow(m_hWnd); hWndChild != nullptr;
		hWndChild = ::GetNextWindow(hWndChild, GW_HWNDNEXT))
	{
		UINT_PTR nIDC = _AfxGetDlgCtrlID(hWndChild);

      /////////////////////////////////////////////////////
      // RAB: Problem happens here!!!
      /////////////////////////////////////////////////////
      // CWnd::FromHandlePerment can't find the window created by the graph builder
      // however CWnd::FromHandle gets the job done. This is the only
      // change from the implementation in CWnd::FromHandlePermanent

		//CWnd* pWnd = CWnd::FromHandlePermanent(hWndChild);
		CWnd* pWnd = CWnd::FromHandle(hWndChild);

		if (nIDC == nIDLeftOver)
			hWndLeftOver = hWndChild;
      else if (nIDC >= nIDFirst && nIDC <= nIDLast && pWnd != nullptr )
			::SendMessage(hWndChild, WM_SIZEPARENT, 0, (LPARAM)&layout);
	}

	// if just getting the available rectangle, return it now...
	if ((nFlags & ~reposNoPosLeftOver) == reposQuery)
	{
		ASSERT(lpRectParam != nullptr);
		if (bStretch)
			::CopyRect(lpRectParam, &layout.rect);
		else
		{
			lpRectParam->left = lpRectParam->top = 0;
			lpRectParam->right = layout.sizeTotal.cx;
			lpRectParam->bottom = layout.sizeTotal.cy;
		}
		return;
	}

	// the rest is the client size of the left-over pane
	if (nIDLeftOver != 0 && hWndLeftOver != nullptr)
	{
		CWnd* pLeftOver = CWnd::FromHandle(hWndLeftOver);
		// allow extra space as specified by lpRectBorder
		if ((nFlags & ~reposNoPosLeftOver) == reposExtra)
		{
			ASSERT(lpRectParam != nullptr);
			layout.rect.left += lpRectParam->left;
			layout.rect.top += lpRectParam->top;
			layout.rect.right -= lpRectParam->right;
			layout.rect.bottom -= lpRectParam->bottom;
		}
		// reposition the window
		if ((nFlags & reposNoPosLeftOver) != reposNoPosLeftOver)
		{
			pLeftOver->CalcWindowRect(&layout.rect);
			AfxRepositionWindow(&layout, hWndLeftOver, &layout.rect);
		}
	}

	// move and resize all the windows at once!
	if (layout.hDWP == nullptr || !::EndDeferWindowPos(layout.hDWP))
		TRACE(traceAppMsg, 0, "Warning: DeferWindowPos failed - low system resources.\n");
}
