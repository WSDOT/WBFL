///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2025  Washington State Department of Transportation
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
#include <EAF\EAFGraphView.h>
#include <EAF\EAFGraphChildFrame.h>
#include <EAF\EAFDocTemplate.h>
#include <EAF\EAFMainFrame.h>
#include <EAF\EAFUtilities.h>
#include <EAF\EAFDocument.h>
#include <EAF\EAFStatusCenter.h>

#include "AgentTools.h"

#include <Graphing/GraphManager.h>
#include <IGraphManager.h>

#include <MfcTools\Text.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEAFGraphView


IMPLEMENT_DYNCREATE(CEAFGraphView, CEAFView)

CEAFGraphView::CEAFGraphView() :
m_bIsPrinting(false),
m_bUpdateError(false)
{
}

CEAFGraphView::~CEAFGraphView()
{
}

BEGIN_MESSAGE_MAP(CEAFGraphView, CEAFView)
	//{{AFX_MSG_MAP(CEAFGraphView)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT, OnUpdateFilePrint)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_DIRECT, OnUpdateFilePrint)
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
   ON_WM_LBUTTONDBLCLK()
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEAFGraphView drawing

void CEAFGraphView::OnDraw(CDC* pDC)
{
   // deal with printing and reentrant behavior
   if (m_bIsPrinting)
      return;

   if (pDC->IsPrinting())
      m_bIsPrinting = true;

   if (m_bUpdateError)
   {
      CString msg;
      AfxFormatString1(msg, IDS_E_UPDATE, m_ErrorMsg.c_str());

      CFont font;
      CFont* pOldFont = nullptr;
      if (font.CreatePointFont(100, _T("Arial"), pDC))
         pOldFont = pDC->SelectObject(&font);

      MultiLineTextOut(pDC, 0, 0, msg);

      if (pOldFont)
         pDC->SelectObject(pOldFont);
   }
   else
   {
      CEAFGraphChildFrame* pParent = (CEAFGraphChildFrame*)GetParent();
      std::unique_ptr<WBFL::Graphing::GraphBuilder>& pGraphBuilder(pParent->GetGraphBuilder());
      pGraphBuilder->DrawGraph(this, pDC);
   }

   if ( m_bIsPrinting )
   {
      m_bIsPrinting = false;
      Invalidate();
   }
}

/////////////////////////////////////////////////////////////////////////////
// CEAFGraphView diagnostics

#ifdef _DEBUG
void CEAFGraphView::AssertValid() const
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
	CEAFView::AssertValid();
}

void CEAFGraphView::Dump(CDumpContext& dc) const
{
	CEAFView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEAFGraphView message handlers
void CEAFGraphView::OnUpdateFilePrint(CCmdUI* pCmdUI) 
{
   std::unique_ptr<WBFL::Graphing::GraphBuilder>& pBuilder(GetGraphBuilder());
   BOOL bCanPrint = FALSE;
   if ( pBuilder )
   {
      bCanPrint = pBuilder->CanPrint();
   }

   pCmdUI->Enable( bCanPrint );
}

void CEAFGraphView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
   CEAFDocument* pDoc = (CEAFDocument*)GetDocument();
   CEAFStatusCenter& statusCenter = pDoc->GetStatusCenter();

   if (statusCenter.GetSeverity() == eafTypes::statusError)
   {
      m_bUpdateError = true;
      m_ErrorMsg = _T("Errors exist that prevent analysis. Review the errors posted in the status center for more information");

      Invalidate();
      UpdateWindow();

      return;
   }

   m_bUpdateError = false;

   CEAFView::OnUpdate( pSender, lHint, pHint ); // base class

   std::unique_ptr<WBFL::Graphing::GraphBuilder>& pBuilder(GetGraphBuilder());
   pBuilder->OnUpdate(pSender,lHint,pHint);
}

CRect CEAFGraphView::GetDrawingRect()
{
   if ( m_bIsPrinting )
   {
      return m_PrintRect;
   }
   else
   {
      CRect rect;
      GetClientRect(&rect);
      return rect;
   }
}

CEAFGraphChildFrame* CEAFGraphView::GetFrame()
{
   CWnd* pParent = GetParent();
   ATLASSERT(pParent->IsKindOf(RUNTIME_CLASS(CEAFGraphChildFrame)));
   CEAFGraphChildFrame* pFrame = (CEAFGraphChildFrame*)pParent;
   return pFrame;
}

std::unique_ptr<WBFL::Graphing::GraphBuilder>& CEAFGraphView::GetGraphBuilder()
{
   CEAFGraphChildFrame* pFrame = GetFrame();
   return pFrame->GetGraphBuilder();
}

void CEAFGraphView::OnInitialUpdate() 
{
   CEAFDocument* pDoc = (CEAFDocument*)GetDocument();
   CEAFStatusCenter& statusCenter = pDoc->GetStatusCenter();

   if (statusCenter.GetSeverity() == eafTypes::statusError)
   {
      m_bUpdateError = true;
      m_ErrorMsg = _T("Errors exist that prevent analysis. Review the errors posted in the status center for more information");

      Invalidate();
      UpdateWindow();

      return;
   }

   try
   {
      CDocTemplate* pDocTemplate = pDoc->GetDocTemplate();
      ASSERT( pDocTemplate->IsKindOf(RUNTIME_CLASS(CEAFDocTemplate)) );

      CEAFDocTemplate* pTemplate = (CEAFDocTemplate*)pDocTemplate;
      CEAFGraphViewCreationData* pCreateData = (CEAFGraphViewCreationData*)pTemplate->GetViewCreationData();
      ASSERT(pCreateData != nullptr);

      CEAFGraphChildFrame* pParent = (CEAFGraphChildFrame*)GetParent();

      pParent->m_pGraphMgr  = pCreateData->m_pGraphMgr;
      pParent->m_pIGraphMgr = pCreateData->m_pIGraphMgr;
      ATLASSERT(pCreateData->m_pGraphMgr != nullptr || pCreateData->m_pIGraphMgr != nullptr); // one of these should not be nullptr

      if ( !pParent->CreateGraph(pCreateData->m_GraphIndex) )
      {
         ATLASSERT(false); // should have never gotten here
         // can't initialize graph list... that's is probably
         // because there aren't any graphs... cancel
         // the creation of this view

         // The view creation must fail and this is intentional
         // Turn off the error message so the user doesn't see it
         CEAFMainFrame* pFrame = EAFGetMainFrame();
         pFrame->DisableFailCreateMessage();
         pFrame->CreateCanceled();

         return;
      }

      CEAFView::OnInitialUpdate();
   }
   catch(...)
   {
      // The view creation must fail and this is intentional
      // Turn off the error message so the user doesn't see it
      CEAFMainFrame* pFrame = EAFGetMainFrame();
      pFrame->DisableFailCreateMessage();
      pFrame->CreateCanceled();

      throw; // keep the exception moving
   }
}

BOOL CEAFGraphView::OnPreparePrinting(CPrintInfo* pInfo) 
{
   m_PrintRect = pInfo->m_rectDraw;

   if (DoPreparePrinting(pInfo))
	   return CEAFView::OnPreparePrinting(pInfo);
   else
      return FALSE;
}

void CEAFGraphView::UpdateViewTitle()
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());

   CEAFGraphChildFrame* pParent = (CEAFGraphChildFrame*)GetParent();
   std::unique_ptr<WBFL::Graphing::GraphBuilder>& pGraphBuilder(pParent->GetGraphBuilder());
   if ( pGraphBuilder )
   {
      CString strTitle;
      strTitle.Format(_T("Graph View - %s"),pGraphBuilder->GetName().c_str());
      SetWindowText(strTitle);
   }
   else
   {
      SetWindowText(_T("Graph View"));
   }

   CFrameWnd* pFrame = GetParentFrame();
   pFrame->OnUpdateFrameTitle(TRUE);

   CDocument* pDoc = GetDocument();
   pDoc->UpdateFrameCounts();
}

void CEAFGraphView::OnLButtonDblClk(UINT nFlags,CPoint point)
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());

   // Have the graphbuilder handle this
   CEAFGraphChildFrame* pParent = (CEAFGraphChildFrame*)GetParent();
   std::unique_ptr<WBFL::Graphing::GraphBuilder>& pGraphBuilder(pParent->GetGraphBuilder());
   bool bHandled(false);
   if (pGraphBuilder)
   {
      bHandled = pGraphBuilder->HandleDoubleClick(nFlags,point);
   }

   if (!bHandled)
   {
      CEAFView::OnLButtonDblClk(nFlags,point);
   }
}
