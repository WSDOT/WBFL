///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2015  Washington State Department of Transportation
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
#include <EAF\EAFGraphBuilderBase.h>
#include <EAF\EAFGraphControlWindow.h>
#include <EAF\EAFGraphView.h>
#include <EAF\EAFHints.h>

#include <MFCTools\Text.h> // for MultiLineTextOut

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CEAFGraphBuilderBase

CEAFGraphBuilderBase::CEAFGraphBuilderBase()
{
   m_bValidGraph = false;
   m_bUpdateError = false;
   m_pFrame = NULL;
}

CEAFGraphBuilderBase::CEAFGraphBuilderBase(const CEAFGraphBuilderBase& other) :
CGraphBuilder(other), CCmdTarget()
{
   m_bValidGraph = false;
   m_bUpdateError = false;
   m_pFrame = NULL;
}

CEAFGraphBuilderBase::~CEAFGraphBuilderBase()
{
}

BEGIN_MESSAGE_MAP(CEAFGraphBuilderBase, CCmdTarget)
	//{{AFX_MSG_MAP(CEAFGraphBuilderBase)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

int CEAFGraphBuilderBase::InitializeGraphController(CWnd* pParent,UINT nID)
{
   ASSERT(pParent->IsKindOf(RUNTIME_CLASS(CEAFGraphChildFrame)));
   m_pFrame = (CEAFGraphChildFrame*)pParent;

   // Setup command routing
   CEAFGraphControlWindow* pWnd = GetGraphControlWindow();
   if ( pWnd )
   {
      pWnd->SetCommandTarget(this);
      pWnd->SetGraphBuilder(this);
   }

   if ( !CreateGraphController(pParent,nID) )
   {
      return -1;
   }

   return 0;
}

CEAFGraphChildFrame* CEAFGraphBuilderBase::GetFrame()
{
   return m_pFrame;
}

CEAFGraphView* CEAFGraphBuilderBase::GetView()
{
   if ( m_pFrame )
   {
      return m_pFrame->GetGraphView();
   }
   else
   {
      return NULL;
   }
}

void CEAFGraphBuilderBase::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
   // some kind of error occured when updating results somewhere in the system.
   if ( lHint == EAF_HINT_UPDATEERROR )
   {
      CString* pmsg = (CString*)pHint;
      m_ErrorMsg = *pmsg;
      m_bUpdateError = true;
      m_bValidGraph = false;
      GetView()->Invalidate();
      return; // don't go any further, when the view re-draws it will write the error message
   }

   // there was an update request, but not because of an error
   m_bUpdateError = false;

   CEAFGraphControlWindow* pGraphControlWnd = GetGraphControlWindow();
   if ( pGraphControlWnd )
   {
      pGraphControlWnd->OnUpdate(pSender,lHint,pHint);
   }

   // Update the graph
   Update();
}

void CEAFGraphBuilderBase::DrawGraph(CWnd* pGraphWnd,CDC* pDC)
{
   if ( m_bValidGraph && !m_bUpdateError )
   {
      DrawGraphNow(pGraphWnd,pDC);
   }
   else
   {
      // There was an error and data isn't available or data isn't
      // available because autocalc is turned off and the results
      // haven't been updated yet.... either way, there is nothing to draw.

      // Display a message to indicate to the user the state of the results

      AFX_MANAGE_STATE(AfxGetAppModuleState());

      CString msg;
      if ( m_bUpdateError )
      {
         AfxFormatString1(msg,IDS_E_UPDATE,m_ErrorMsg.c_str());
      }
      else
      {
         msg.LoadString(IDS_RESULTS_NOT_AVAILABLE);
      }

      CFont font;
      CFont* pOldFont = NULL;
      if ( font.CreatePointFont(100,_T("Arial"),pDC) )
      {
         pOldFont = pDC->SelectObject(&font);
      }

      MultiLineTextOut(pDC,0,0,msg);

      if ( pOldFont )
      {
         pDC->SelectObject(pOldFont);
      }
   }
}

void CEAFGraphBuilderBase::Update()
{
   CEAFGraphView* pView = GetView();

   // catch any exceptions coming out of the graph update and
   // set us to a safe mode
   try
   {
      m_bValidGraph = UpdateNow();
      m_bUpdateError = !m_bValidGraph;

      pView->Invalidate();
      pView->UpdateWindow();
   }
   catch(...)
   {
      m_bUpdateError = true; // there was an update error
      m_bValidGraph = false; // the graph data is invalid

      // force the view to redraw
      pView->Invalidate();
      pView->UpdateWindow();

      // keep the exception moving
      throw;
   }
}

BOOL CEAFGraphBuilderBase::CanPrint()
{
   return (m_bValidGraph && !m_bUpdateError) ? TRUE : FALSE;
}
