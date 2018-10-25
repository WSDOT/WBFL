///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2013  Washington State Department of Transportation
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
#include "afxcmn.h"

#include "resource.h"
#include <EAF\EAFDocTemplate.h>
#include <EAF\EAFTemplateGroup.h>

// CNewProjectDlg dialog

class CNewProjectDlg : public CDialog
{
	DECLARE_DYNAMIC(CNewProjectDlg)
protected:
   CEAFTemplateGroup* m_pRootTemplateGroup; // root template group

public:
	CEAFDocTemplate*  m_pSelectedTemplate;
   const CEAFTemplateItem* m_pTemplateItem;

   int m_ViewMode;

public:
   CNewProjectDlg(CEAFTemplateGroup* pRootTemplateGroup,CWnd* pParent = NULL);
	virtual ~CNewProjectDlg();

// Dialog Data
	enum { IDD = IDD_NEWPROJECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

   void SetOKButtonState();

   CString m_strToolTipText;
   int m_cxMin;
   int m_cyMin;

   HICON m_hDefaultIcon;
   HICON m_hDefaultSelectedIcon;
   int m_DefaultIconIdx;
   int m_DefaultSelectedIconIdx;

   void AddProjectGroup(HTREEITEM hParent,HTREEITEM hAfter,const CEAFTemplateGroup* pGroup);
   
   void ExpandProjectTypes();

	DECLARE_MESSAGE_MAP()
public:
   virtual BOOL OnInitDialog();
   CTreeCtrl m_ctrlProjectTypes;
   CListCtrl m_ctrlTemplates;
   CImageList m_TemplateLargeImageList;
   CImageList m_TemplateSmallImageList;
   CImageList m_ProjectTypeImageList;

   afx_msg void OnProjectTypeSelectionChanged(NMHDR *pNMHDR, LRESULT *pResult);
   afx_msg void OnTemplatesItemChanged(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnViewModeClicked(UINT i);
   afx_msg BOOL OnToolTipNotify(UINT id,NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnSize(UINT nType, int cx, int cy);
   virtual LRESULT WindowProc(UINT message,WPARAM wParam,LPARAM lParam);
   afx_msg void OnDestroy();
   afx_msg void OnTemplatesDblClick(NMHDR *pNMHDR, LRESULT *pResult);
};
