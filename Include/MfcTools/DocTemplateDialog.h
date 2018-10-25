///////////////////////////////////////////////////////////////////////
// MfcTools - Extension library for MFC
// Copyright © 1999-2017  Washington State Department of Transportation
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

#if !defined(AFX_DOCTEMPLATEDIALOG_H__E428EFC3_5E1F_11D2_9D6E_00609710E6CE__INCLUDED_)
#define AFX_DOCTEMPLATEDIALOG_H__E428EFC3_5E1F_11D2_9D6E_00609710E6CE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DocTemplateDialog.h : header file
//

#include "resource.h"
#include <MfcTools\TemplateTabHelper.h>
#include <MfcTools\DocTemplateFinder.h>

/////////////////////////////////////////////////////////////////////////////
// CDocTemplateDialog dialog

class CDocTemplateDialog : public CDialog
{
// Construction
public:
	CDocTemplateDialog(CWnd* pParent = nullptr);   // standard constructor
	~CDocTemplateDialog();

// Dialog Data
	//{{AFX_DATA(CDocTemplateDialog)
	enum { IDD = IDD_DOC_TEMPLATE_DIALOG };
	CButton	m_OkButton;
	CStatic	   m_FileSelected;
	CListCtrl	m_FileListCtrl;
	CTabCtrl	   m_TabCtrl;
	int		m_RadioButton;
	//}}AFX_DATA

   bool m_bOmitDefaultFile;


   void SetListMode(mfcDocTemplateFinder::ListMode mode);
   mfcDocTemplateFinder::ListMode GetListMode() const;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDocTemplateDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
   // set our list of tabs and files
   void SetTabList(TabList* ptab_list);
   void SetIcon(HICON hicon);
   std::_tstring GetSelectedFile() const;
   void SetDefaultFile(const std::_tstring& filename);
protected:

	// Generated message map functions
	//{{AFX_MSG(CDocTemplateDialog)
	virtual BOOL OnInitDialog() override;
	afx_msg void OnSelchangeFileViewTab(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRadioClicked(UINT i);
	afx_msg void OnClickFileListctrl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkFileListctrl(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
   TabList*      m_pTabList;
	CImageList    m_FileImages32; // list box images for files
	CImageList    m_FileImages16; // list box images for files

   std::_tstring   m_CurrentlySelectedFile;
   std::_tstring   m_DefaultFile;
   mfcTemplateTabHelper* m_pSelectedTabHelper;

   mfcDocTemplateFinder::ListMode m_ListMode;

   void SelectTab(const std::_tstring& key);
   void ClearSelectedFile();
   void SetSelectedFile(const std::_tstring& filename);

   void UpdateListViewMode();

private:
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOCTEMPLATEDIALOG_H__E428EFC3_5E1F_11D2_9D6E_00609710E6CE__INCLUDED_)
