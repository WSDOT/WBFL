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


// StatusCenterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "StatusCenterDlg.h"
#include <EAF\EAFStatusItem.h>
#include <EAF\EAFUtilities.h>
#include <EAF\EAFStatusBar.h> // for colors
#include <EAF\EAFApp.h>

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
   case eafTypes::statusInformation:
      color = STATUS_INFORMATION_COLOR;
      break;
   case eafTypes::statusWarning:
      color = STATUS_WARNING_COLOR;
      break;
   case eafTypes::statusError:
      color = STATUS_ERROR_COLOR;
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

   m_nInfo = 0;
   m_nWarn = 0;
   m_nError = 0;

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
	ON_BN_CLICKED(IDCLOSE, OnClosePressed)
	//}}AFX_MSG_MAP
   ON_NOTIFY(NM_DBLCLK,IDC_STATUSLIST,OnDoubleClick)
   ON_NOTIFY(HDN_ITEMCLICK,0,OnHeaderClicked)
   ON_WM_CTLCOLOR()
   ON_WM_SHOWWINDOW()
   ON_WM_CLOSE()
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

   UpdateStatusItemCounts();

   // minimum size of the window
   CRect rect;
   GetWindowRect(&rect);
   m_cxMin = rect.Width();
   m_cyMin = rect.Height();


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

   if ( severity == eafTypes::statusInformation )
   {
      m_nInfo++;
   }
   else if ( severity == eafTypes::statusWarning )
   {
      m_nWarn++;
   }
   else
   {
      m_nError++;
   }
   UpdateStatusItemCounts();

   Sort();
}

void CStatusCenterDlg::OnStatusItemRemoved(StatusItemIDType id)
{
   if ( GetSafeHwnd() == nullptr )
      return;

   eafTypes::StatusSeverityType severity;

   LVFINDINFO info;
   severity = eafTypes::statusInformation;
   info.flags = LVFI_PARAM;
   info.lParam = MAKELONG(id,severity);

   int idx = m_ctrlList.FindItem(&info);
   if ( idx == -1 )
   {
      severity = eafTypes::statusWarning;
      info.lParam = MAKELONG(id,severity);
      idx = m_ctrlList.FindItem(&info);
   }

   if ( idx == -1 )
   {
      severity = eafTypes::statusError;
      info.lParam = MAKELONG(id,severity);
      idx = m_ctrlList.FindItem(&info);
   }

   if ( idx != -1 )
   {
      m_ctrlList.DeleteItem(idx);

      if ( severity == eafTypes::statusInformation )
      {
         m_nInfo--;
      }
      else if ( severity == eafTypes::statusWarning )
      {
         m_nWarn--;
      }
      else
      {
         m_nError--;
      }

      UpdateStatusItemCounts();
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

void CStatusCenterDlg::OnClosePressed() 
{
   ShowWindow(SW_HIDE);	
}

void CStatusCenterDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
   CDialog::OnShowWindow(bShow, nStatus);

   if (bShow)
   {
      RestoreWindowPosition();
   }
   else
   {
      SaveWindowPosition();
   }
}

void CStatusCenterDlg::OnClose()
{
   SaveWindowPosition();
   CDialog::OnClose();
}

void CStatusCenterDlg::UpdateStatusItemCounts()
{
   CString str;
   str.Format(_T("Information (%d)"),m_nInfo);
   GetDlgItem(IDC_INFORMATION)->SetWindowText(str);

   str.Format(_T("Warning (%d)"),m_nWarn);
   GetDlgItem(IDC_WARNING)->SetWindowText(str);

   str.Format(_T("Error (%d)"),m_nError);
   GetDlgItem(IDC_ERROR)->SetWindowText(str);
}

HBRUSH CStatusCenterDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
   HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
   int ID = pWnd->GetDlgCtrlID();
   switch( ID )
   {
   case IDC_INFORMATION:
      pDC->SetBkColor(STATUS_INFORMATION_COLOR);
      break;

   case IDC_WARNING:
      pDC->SetBkColor(STATUS_WARNING_COLOR);
      break;

   case IDC_ERROR:
      pDC->SetBkColor(STATUS_ERROR_COLOR);
      break;
   }

   return hbr;
}

void CStatusCenterDlg::SaveWindowPosition()
{
   WINDOWPLACEMENT wp;
   if (GetWindowPlacement(&wp))
   {
      EAFGetApp()->WriteWindowPlacement(CString((LPCTSTR)IDS_WINDOW_POSITIONS), _T("StatusCenter"), &wp);
   }
}

void CStatusCenterDlg::RestoreWindowPosition()
{
   WINDOWPLACEMENT wp;
   if (EAFGetApp()->ReadWindowPlacement(CString((LPCTSTR)IDS_WINDOW_POSITIONS), _T("StatusCenter"), &wp))
   {
      HMONITOR hMonitor = MonitorFromRect(&wp.rcNormalPosition, MONITOR_DEFAULTTONULL); // get the monitor that has maximum overlap with the dialog rectangle (returns null if none)
      if (hMonitor != NULL)
      {
         // if dialog is within a monitor, set its position... otherwise the default position will be sued
         SetWindowPos(NULL, wp.rcNormalPosition.left, wp.rcNormalPosition.top, wp.rcNormalPosition.right - wp.rcNormalPosition.left, wp.rcNormalPosition.bottom - wp.rcNormalPosition.top, 0);
      }
   }
}

LRESULT CStatusCenterDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
   // prevent the dialog from getting smaller than the original size
   if (message == WM_SIZING)
   {
      LPRECT rect = (LPRECT)lParam;
      int cx = rect->right - rect->left;
      int cy = rect->bottom - rect->top;

      if (cx < m_cxMin || cy < m_cyMin)
      {
         // prevent the dialog from moving right or down
         if (wParam == WMSZ_BOTTOMLEFT ||
            wParam == WMSZ_LEFT ||
            wParam == WMSZ_TOP ||
            wParam == WMSZ_TOPLEFT ||
            wParam == WMSZ_TOPRIGHT)
         {
            CRect r;
            GetWindowRect(&r);
            rect->left = r.left;
            rect->top = r.top;
         }

         if (cx < m_cxMin)
         {
            rect->right = rect->left + m_cxMin;
         }

         if (cy < m_cyMin)
         {
            rect->bottom = rect->top + m_cyMin;
         }

         return TRUE;
      }
   }

   return CDialog::WindowProc(message, wParam, lParam);
}
