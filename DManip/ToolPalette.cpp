///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
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

// ToolPalette.cpp : implementation file
//

#include "stdafx.h"
#include <WBFLDManip.h>
#include <DManip\DManip.h>
#include "DragDataImpl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CToolPalette dialog


CToolPalette::CToolPalette()
	: CDialogBar()
{
	//{{AFX_DATA_INIT(CToolPalette)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CToolPalette::DoDataExchange(CDataExchange* pDX)
{
	CDialogBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CToolPalette)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CToolPalette, CDialogBar)
	//{{AFX_MSG_MAP(CToolPalette)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolPalette message handlers
void CToolPalette::AddTool(iTool* tool)
{
   ASSERT( tool != nullptr );
   if ( tool == nullptr )
      return;

   m_Tools.emplace_back(tool);

   CWnd* pWnd = GetDlgItem(tool->GetID());
   ASSERT(pWnd); // if this fires, the dialog does not have an item
                 // with the resource id specified by the tool

   CRect rTool;
   pWnd->GetClientRect(&rTool);
   m_ctrlToolTip.AddTool(pWnd,tool->GetToolTipText(),rTool,tool->GetID());
}

void CToolPalette::GetTool(CollectionIndexType idx,iTool** tool)
{
   *tool = 0;

   if ( idx < 0 || m_Tools.size() <= idx )
      return; // Index is out of range

   CComPtr<iTool> t = m_Tools[idx];
   (*tool) = t;
   (*tool)->AddRef();
}

void CToolPalette::FindTool(IDType id,iTool** tool)
{
   (*tool) = 0;
   ToolContainer::iterator iter;
   for ( iter = m_Tools.begin(); iter != m_Tools.end(); iter++ )
   {
      CComPtr<iTool> pTool = *iter;
      if ( pTool->GetID() == id )
      {
         *tool = pTool;
         (*tool)->AddRef();
         return;
      }
   }

}

void CToolPalette::RemoveTool(CollectionIndexType idx)
{
   if ( idx < 0 || m_Tools.size() <= idx )
      return; // Index is out of range

   CComPtr<iTool> tool = m_Tools[idx];
   m_Tools.erase(m_Tools.begin() + idx);

   CWnd* pWnd = GetDlgItem(tool->GetID());
   ASSERT(pWnd);

   m_ctrlToolTip.DelTool(pWnd,tool->GetID());
   pWnd->DestroyWindow();
}

void CToolPalette::AddTooltip(CWnd* pWnd)
{
   CString strTip;
   pWnd->GetWindowText(strTip);
   CRect rWnd;
   pWnd->GetClientRect(&rWnd);
   m_ctrlToolTip.AddTool(pWnd, strTip, rWnd, pWnd->GetDlgCtrlID());
}

void CToolPalette::RemoveTool(IDType id)
{
   ToolContainer::iterator iter;
   for ( iter = m_Tools.begin(); iter != m_Tools.end(); iter++ )
   {
      CComPtr<iTool> tool = *iter;
      if ( tool->GetID() == id )
      {
         m_Tools.erase(iter);

         CWnd* pWnd = GetDlgItem(tool->GetID());
         ASSERT(pWnd);

         m_ctrlToolTip.DelTool(pWnd,tool->GetID());
         pWnd->DestroyWindow();

         return;
      }
   }
}

int CToolPalette::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialogBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
   if ( !m_ctrlToolTip.Create(this) )
      return -1;

   EnableToolTips(TRUE);
   m_ctrlToolTip.Activate(TRUE);
	
	return 0;
}

BOOL CToolPalette::PreTranslateMessage(MSG* pMsg) 
{
   m_ctrlToolTip.Activate(TRUE);
   m_ctrlToolTip.RelayEvent(pMsg);
	
	return CDialogBar::PreTranslateMessage(pMsg);
}

BOOL CToolPalette::OnCommand(WPARAM wParam, LPARAM lParam) 
{
   if ( HIWORD(wParam) == BN_CLICKED )
   {
      // Something was clicked... Check to see if it was one of the tools
      WORD wID = LOWORD(wParam); // get the control id

      CComPtr<iTool> tool;
      FindTool(wID,&tool);
      if ( tool )
      {
         CComQIPtr<iDraggable,&IID_iDraggable> draggable(tool);
         if ( draggable )
         {
            CComObject<CDragDataSinkImpl>* pSink;
            CComObject<CDragDataSinkImpl>::CreateInstance(&pSink);
            CComPtr<iDragDataSink> sink(pSink);
            draggable->PrepareDrag(sink);

            COleDataSource ods;
            pSink->CacheGlobalData(&ods);

            DROPEFFECT de = ods.DoDragDrop(DROPEFFECT_COPY | DROPEFFECT_MOVE);
         }
      }
   }

	return CDialogBar::OnCommand(wParam, lParam);
}

void CToolPalette::PreSubclassWindow() 
{
   if ( m_ctrlToolTip.GetSafeHwnd() == 0 )
   {
//      m_ctrlToolTip.Create(this);
//      m_ctrlToolTip.Activate(TRUE);
   }
	
	CDialogBar::PreSubclassWindow();
}
