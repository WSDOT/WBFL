///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright � 1999-2025  Washington State Department of Transportation
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

// StatusCenterDlg.h : header file
//
#include "Resource.h"
#include <EAF\StatusCenter.h>

class CStatusItemListCtrl : public CMFCListCtrl
{
public:
   virtual COLORREF OnGetCellBkColor(int nRow,int nColumn);
};

/////////////////////////////////////////////////////////////////////////////
// CStatusCenterDlg dialog

class CStatusCenterDlg : public CDialog, public IEAFStatusCenterEventSink
{
// Construction
public:
	CStatusCenterDlg(CEAFStatusCenter& statusCenter);
	~CStatusCenterDlg();

// Dialog Data
	//{{AFX_DATA(CStatusCenterDlg)
	enum { IDD = IDD_STATUSCENTER };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

   void OnStatusItemAdded(CEAFStatusItem* pNewItem);
   void OnStatusItemRemoved(StatusItemIDType id);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStatusCenterDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
   afx_msg void OnDoubleClick(NMHDR* pNotifyStruct,LRESULT* pResult);
   afx_msg void OnHeaderClicked(NMHDR* pNMHDR, LRESULT* pResult);

// Implementation
protected:
   CEAFStatusCenter& m_StatusCenter;

   CStatusItemListCtrl m_ctrlList;

   int m_cxMin;
   int m_cyMin;

   IndexType m_nInfo;
   IndexType m_nWarn;
   IndexType m_nError;
   void UpdateStatusItemCounts();

   bool m_bSortAscending;
   void Sort(bool bReverse=true);

	// Generated message map functions
	//{{AFX_MSG(CStatusCenterDlg)
	virtual BOOL OnInitDialog() override;
   virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam) override;
   afx_msg void OnClosePressed();
   afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
   afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
   afx_msg void OnClose();
   //}}AFX_MSG

   void SaveWindowPosition();
   void RestoreWindowPosition();

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
