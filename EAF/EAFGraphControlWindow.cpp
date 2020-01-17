///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2020  Washington State Department of Transportation
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
#include <EAF\EAFGraphControlWindow.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CEAFGraphControlWindow

IMPLEMENT_DYNCREATE(CEAFGraphControlWindow,CDialogBar)

CEAFGraphControlWindow::CEAFGraphControlWindow()
{
   m_pCmdTarget = nullptr;
   m_pGraphBuilder = nullptr;
}

void CEAFGraphControlWindow::SetCommandTarget(CCmdTarget* pCmdTarget)
{
   m_pCmdTarget = pCmdTarget;
}

void CEAFGraphControlWindow::SetGraphBuilder(CEAFGraphBuilderBase* pBuilder)
{
   m_pGraphBuilder = pBuilder;
}

CEAFGraphBuilderBase* CEAFGraphControlWindow::GetGraphBuilder()
{
   return  m_pGraphBuilder;
}

void CEAFGraphControlWindow::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
   // do nothing by default
}

BEGIN_MESSAGE_MAP(CEAFGraphControlWindow, CDialogBar)
	//{{AFX_MSG_MAP(CTestDialogBar)
	//}}AFX_MSG_MAP
   ON_WM_CREATE()
   ON_MESSAGE(WM_INITDIALOG,OnInitDialog)
END_MESSAGE_MAP()

int CEAFGraphControlWindow::OnCreate(LPCREATESTRUCT lpcs)
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
   return CDialogBar::OnCreate(lpcs);
}

BOOL CEAFGraphControlWindow::OnCmdMsg(UINT nID,int nCode,void* pExtra,AFX_CMDHANDLERINFO* pHandlerInfo)
{
   // if there is a secondary command target, route commands to it first
   if ( m_pCmdTarget && m_pCmdTarget->OnCmdMsg(nID,nCode,pExtra,pHandlerInfo) )
      return TRUE; // command was handled

   // set the command on its way
   return CDialogBar::OnCmdMsg(nID,nCode,pExtra,pHandlerInfo);
}

LRESULT CEAFGraphControlWindow::OnInitDialog(WPARAM wParam,LPARAM lParam)
{
   LRESULT lResult = HandleInitDialog(wParam,lParam);

   // mimic CDialog behavior
   OnInitDialog();

   return lResult;
}

BOOL CEAFGraphControlWindow::OnInitDialog()
{
   // mimic CDialog::OnInitiDialog
   if ( !UpdateData(FALSE) )
   {
      TRACE0("Warning: UpdateData failed during dialog init.\n");
   }

   return TRUE;
}

#ifdef _DEBUG
void CEAFGraphControlWindow::AssertValid() const
{
   // the module state stuff gets really ugly here... there doesn't
   // seem to be a consistent way to set it for all times when this
   // method gets called... just skip the validation for this object.
	//CDialogBar::AssertValid();
}

void CEAFGraphControlWindow::Dump(CDumpContext& dc) const
{
	CDialogBar::Dump(dc);
}
#endif //_DEBUG
