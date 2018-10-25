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


// StatusCenterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "StatusCenterDlg.h"
#include <EAF\EAFStatusItem.h>
#include <EAF\EAFUtilities.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStatusCenterDlg dialog


CStatusCenterDlg::CStatusCenterDlg(CEAFStatusCenter& statusCenter)
	: CDialog(_T("")),
   m_StatusCenter(statusCenter)
{
	//{{AFX_DATA_INIT(CStatusCenterDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
   Create(CStatusCenterDlg::IDD,EAFGetMainFrame());

   m_StatusCenter.SinkEvents(this);
}

CStatusCenterDlg::~CStatusCenterDlg()
{
   m_StatusCenter.UnSinkEvents(this);
}

void CStatusCenterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStatusCenterDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStatusCenterDlg, CDialog)
	//{{AFX_MSG_MAP(CStatusCenterDlg)
	ON_BN_CLICKED(IDCLOSE, OnClose)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
   ON_NOTIFY(NM_DBLCLK,IDC_STATUSLIST,OnDoubleClick)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStatusCenterDlg message handlers

BOOL CStatusCenterDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
   CListCtrl* pListCtrl = (CListCtrl*)GetDlgItem(IDC_STATUSLIST);
   pListCtrl->SetExtendedStyle ( LVS_EX_FULLROWSELECT );

   CRect r;
   pListCtrl->GetClientRect(&r);

   int k = 8;
   pListCtrl->InsertColumn(0,_T("Level"),LVCFMT_LEFT,r.Width()/k);
   pListCtrl->InsertColumn(1,_T("Description"),LVCFMT_LEFT,r.Width() - r.Width()/k);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CStatusCenterDlg::OnStatusItemAdded(CEAFStatusItem* pNewItem)
{
   CListCtrl* pListCtrl = (CListCtrl*)GetDlgItem(IDC_STATUSLIST);

   eafTypes::StatusSeverityType severity = m_StatusCenter.GetSeverity(pNewItem->GetCallbackID());

   CString strSeverityType[] = { _T("Info"), _T("Warn"), _T("Error") };
   CString strSeverity;
   strSeverity.Format(_T("%s"),strSeverityType[severity]);
   int idx = pListCtrl->InsertItem((int)pNewItem->GetID(),strSeverity);
   VERIFY( pListCtrl->SetItemText(idx,1,pNewItem->GetDescription()) );
   VERIFY( pListCtrl->SetItemData(idx,pNewItem->GetID()) );
}

void CStatusCenterDlg::OnStatusItemRemoved(StatusItemIDType id)
{
   LVFINDINFO info;
   info.flags = LVFI_PARAM;
   info.lParam = id;

   if ( GetSafeHwnd() == NULL )
      return;

   CListCtrl* pListCtrl = (CListCtrl*)GetDlgItem(IDC_STATUSLIST);
   int idx = pListCtrl->FindItem(&info);
   if ( idx != -1 )
   {
      pListCtrl->DeleteItem(idx);
   }
}

void CStatusCenterDlg::OnDoubleClick(NMHDR* pNotifyStruct,LRESULT* pResult)
{
   NMITEMACTIVATE* pNotify = (NMITEMACTIVATE*)(pNotifyStruct);
   int idx = pNotify->iItem;

   if ( 0 <= idx )
   {
      CListCtrl* pListCtrl = (CListCtrl*)GetDlgItem(IDC_STATUSLIST);
      DWORD_PTR id = pListCtrl->GetItemData(idx);
      m_StatusCenter.EditItem((StatusItemIDType)id);
   }
}

void CStatusCenterDlg::OnClose() 
{
   ShowWindow(SW_HIDE);	
}

void CStatusCenterDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	const int border = 10;

   CRect rc;
   GetClientRect(&rc);

   CWnd* pBtn  = GetDlgItem(IDCLOSE);
   CWnd* pList = GetDlgItem(IDC_STATUSLIST);
   CWnd* pLabel = GetDlgItem(IDC_LABEL);

   if ( pBtn == NULL || pList == NULL )
      return;

   CRect rBtn;
   pBtn->GetClientRect(&rBtn);
   int x = rc.right - rBtn.Width() - border;
   int y = rc.bottom - rBtn.Height() - border;
   pBtn->SetWindowPos(NULL,x,y,0,0,SWP_NOSIZE | SWP_NOZORDER);

   CRect rLabel;
   pLabel->GetClientRect(&rLabel);
   x = rc.left + border;
   pLabel->SetWindowPos(NULL,x,y,0,0,SWP_NOSIZE | SWP_NOZORDER);

   CRect rList;
   pList->GetClientRect(&rList);
   int w = rc.Width() - 2*border;
   int h = rc.Height() - 3*border - rBtn.Height();
   pList->SetWindowPos(NULL,0,0,w,h,SWP_NOMOVE | SWP_NOZORDER);
}
