///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2016  Washington State Department of Transportation
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


COLORREF CStatusItemListCtrl::OnGetCellBkColor(int nRow,int nColumn)
{
   if ( 0 < nColumn )
   {
      return ::GetSysColor(COLOR_WINDOW);
   }

   DWORD_PTR dw = GetItemData(nRow);
   eafTypes::StatusSeverityType severity = (eafTypes::StatusSeverityType)HIWORD(dw); 

   COLORREF color;
   switch(severity)
   {
   case eafTypes::statusOK:
      color = RGB(0,255,0);
      break;
   case eafTypes::statusWarning:
      color = RGB(255,255,0);
      break;
   case eafTypes::statusError:
      color = RGB(255,0,0);
      break;
   default:
      ATLASSERT(false); // should never get here
   }

   return color;
}

class SortObject
{
public:
   static bool m_bSortAscending;
   static int CALLBACK SortFunc(LPARAM lParam1,LPARAM lParam2,LPARAM lParamSort);
};

bool SortObject::m_bSortAscending = false; // want to start with errors at the top

int CALLBACK SortObject::SortFunc(LPARAM lParam1,LPARAM lParam2,LPARAM lParamSort)
{
   eafTypes::StatusSeverityType severity1 = (eafTypes::StatusSeverityType)HIWORD(lParam1);
   eafTypes::StatusSeverityType severity2 = (eafTypes::StatusSeverityType)HIWORD(lParam2);
   int result =  severity1 < severity2;
   if ( !SortObject::m_bSortAscending )
   {
      result = !result;
   }

   return result;
}

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

   m_bSortAscending = SortObject::m_bSortAscending;
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

   DDX_Control(pDX,IDC_STATUSLIST,m_ctrlList);
}


BEGIN_MESSAGE_MAP(CStatusCenterDlg, CDialog)
	//{{AFX_MSG_MAP(CStatusCenterDlg)
	ON_BN_CLICKED(IDCLOSE, OnClose)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
   ON_NOTIFY(NM_DBLCLK,IDC_STATUSLIST,OnDoubleClick)
   ON_NOTIFY(HDN_ITEMCLICK,0,OnHeaderClicked)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStatusCenterDlg message handlers

BOOL CStatusCenterDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
   m_ctrlList.SetExtendedStyle ( LVS_EX_FULLROWSELECT );

   CRect r;
   m_ctrlList.GetClientRect(&r);

   int k = 8;
   m_ctrlList.InsertColumn(0,_T("Level"),LVCFMT_LEFT,r.Width()/k);
   m_ctrlList.InsertColumn(1,_T("Description"),LVCFMT_LEFT,r.Width() - r.Width()/k);
	
   m_ctrlList.SetSortColumn(0,m_bSortAscending);

   return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CStatusCenterDlg::OnStatusItemAdded(CEAFStatusItem* pNewItem)
{
   eafTypes::StatusSeverityType severity = m_StatusCenter.GetSeverity(pNewItem->GetCallbackID());

   CString strSeverityType[] = { _T("Info"), _T("Warn"), _T("Error") };
   CString strSeverity;
   strSeverity.Format(_T("%s"),strSeverityType[severity]);
   int idx = m_ctrlList.InsertItem((int)pNewItem->GetID(),strSeverity);
   VERIFY( m_ctrlList.SetItemText(idx,1,pNewItem->GetDescription()) );
   VERIFY( m_ctrlList.SetItemData(idx,MAKELONG(pNewItem->GetID(),severity)) );

   Sort();
}

void CStatusCenterDlg::OnStatusItemRemoved(StatusItemIDType id)
{
   LVFINDINFO info;
   info.flags = LVFI_PARAM;
   info.lParam = MAKELONG(id,eafTypes::statusOK);

   if ( GetSafeHwnd() == NULL )
      return;

   int idx = m_ctrlList.FindItem(&info);
   if ( idx == -1 )
   {
      info.lParam = MAKELONG(id,eafTypes::statusWarning);
      idx = m_ctrlList.FindItem(&info);
   }

   if ( idx == -1 )
   {
      info.lParam = MAKELONG(id,eafTypes::statusError);
      idx = m_ctrlList.FindItem(&info);
   }

   if ( idx != -1 )
   {
      m_ctrlList.DeleteItem(idx);
   }

   Sort();
}

void CStatusCenterDlg::OnHeaderClicked(NMHDR* pNMHDR, LRESULT* pResult)
{
   NMLISTVIEW* pLV = (NMLISTVIEW*)pNMHDR;

   if (pLV->iItem == 0 )
   {
      Sort();
   }

   *pResult = 0;
}

void CStatusCenterDlg::Sort(bool bReverse)
{
   if ( bReverse )
   {
      SortObject::m_bSortAscending = !m_bSortAscending;
   }
   else
   {
      SortObject::m_bSortAscending = m_bSortAscending;
   }

   m_ctrlList.SortItems(SortObject::SortFunc,0);


   // remove old header image
   HDITEM old_item;
   old_item.mask  = HDI_FORMAT;
   m_ctrlList.GetHeaderCtrl().GetItem(0,&old_item);
   old_item.fmt &= ~(HDF_SORTDOWN | HDF_SORTUP);
   m_ctrlList.GetHeaderCtrl().SetItem(0,&old_item);

   // add header image
   HDITEM new_item;
   new_item.mask  = HDI_FORMAT;
   m_ctrlList.GetHeaderCtrl().GetItem(0,&new_item);
   new_item.fmt  |= (SortObject::m_bSortAscending ? HDF_SORTUP : HDF_SORTDOWN); 
   m_ctrlList.GetHeaderCtrl().SetItem(0,&new_item);

   m_bSortAscending = SortObject::m_bSortAscending;
}

void CStatusCenterDlg::OnDoubleClick(NMHDR* pNotifyStruct,LRESULT* pResult)
{
   NMITEMACTIVATE* pNotify = (NMITEMACTIVATE*)(pNotifyStruct);
   int idx = pNotify->iItem;

   if ( 0 <= idx )
   {
      DWORD_PTR dw = m_ctrlList.GetItemData(idx);
      StatusItemIDType id = LOWORD(dw); 
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
   CWnd* pLabel = GetDlgItem(IDC_LABEL);

   if ( pBtn == NULL )
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
   m_ctrlList.GetClientRect(&rList);
   int w = rc.Width() - 2*border;
   int h = rc.Height() - 3*border - rBtn.Height();
   m_ctrlList.SetWindowPos(NULL,0,0,w,h,SWP_NOMOVE | SWP_NOZORDER);
}
