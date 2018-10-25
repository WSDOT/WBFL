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

#pragma once

#include "afxwin.h"
#include "resource.h"

#include <EAF\EAFPluginState.h>
#include <vector>

// CManagePluginsDlg dialog

class CManagePluginsDlg : public CDialog
{
	DECLARE_DYNAMIC(CManagePluginsDlg)

public:
	CManagePluginsDlg(LPCTSTR lpszTitle,const CATID& catid,CWnd* pParent = NULL);   // standard constructor
	virtual ~CManagePluginsDlg();

// Dialog Data
	enum { IDD = IDD_MANAGE_PLUGINS };

   std::vector<CEAFPluginState> m_PluginStates;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

   CString m_Title;

   CCheckListBox m_PluginList;
   CString m_strSection;
   CATID m_CATID;
   BOOL InitList();

	DECLARE_MESSAGE_MAP()
public:
   virtual BOOL OnInitDialog();
   virtual void OnOK();
protected:
   virtual void OnCancel();
};
