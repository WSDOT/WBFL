///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2024  Washington State Department of Transportation
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

// StatusMessageDialog.cpp : implementation file
//

#include "stdafx.h"
#include "StatusMessageDialog.h"
#include <EAF\EAFStatusItem.h>
#include <EAF\EAFHelp.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStatusMessageDialog dialog
CStatusMessageDialog::CStatusMessageDialog(CEAFStatusItem* pStatusItem, eafTypes::StatusSeverityType severity, BOOL bRemoveableOnError, BOOL bEnableEdit, LPCTSTR lpszDocSetName, UINT helpID, CWnd* pParent /*=nullptr*/)
   : CDialog(CStatusMessageDialog::IDD, pParent),
   m_Message(pStatusItem->GetDescription()), m_strDocSetName(lpszDocSetName), m_HelpID(helpID), m_Severity(severity), m_bRemoveableOnError(bRemoveableOnError),
   m_bEnableEdit(bEnableEdit)
{
	//{{AFX_DATA_INIT(CStatusMessageDialog)
	//}}AFX_DATA_INIT
}


void CStatusMessageDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStatusMessageDialog)
	DDX_Text(pDX, IDC_MESSAGE, m_Message);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStatusMessageDialog, CDialog)
	//{{AFX_MSG_MAP(CStatusMessageDialog)
	ON_BN_CLICKED(IDHELP, OnHelp)
	//}}AFX_MSG_MAP
   ON_BN_CLICKED(IDEDIT, &CStatusMessageDialog::OnBnClickedEdit)
   ON_BN_CLICKED(IDREMOVE, &CStatusMessageDialog::OnBnClickedRemove)
   ON_BN_CLICKED(IDCLOSE, &CStatusMessageDialog::OnBnClickedClose)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStatusMessageDialog message handlers
void CStatusMessageDialog::OnHelp() 
{
   EAFHelp(m_strDocSetName,m_HelpID);
}

BOOL CStatusMessageDialog::OnInitDialog() 
{

   if (m_HelpID != 0)
   {
      m_Message += CString(_T("\r\n\r\nPress Help for more details."));
   }

   // can we remove the status item?
   bool bHideRemove = m_bRemoveableOnError ? false : (m_Severity == eafTypes::statusError ? true : false);

   if (!bHideRemove)
   {
      m_Message += CString(_T("\r\n\r\nPress Remove to remove this status message."));
   }

   if (m_bEnableEdit)
   {
      m_Message += CString(_T("\r\n\r\nPress Edit to edit and try to resolve the issue."));
   }

	CDialog::OnInitDialog();
	
   if ( m_HelpID == 0 )
   {
      // If there isn't a help ID, hide the Help button and
      // shift other buttons to the right
      CWnd* pwndHelp = GetDlgItem(IDHELP);
      CRect rHelp;
      pwndHelp->GetWindowRect(&rHelp);
      ScreenToClient(rHelp);

      CWnd* pwndClose = GetDlgItem(IDCLOSE);
      CRect rClose;
      pwndClose->GetWindowRect(&rClose);
      ScreenToClient(rClose);

      CWnd* pwndRemove = GetDlgItem(IDREMOVE);
      CRect rRemove;
      pwndRemove->GetWindowRect(&rRemove);
      ScreenToClient(rRemove);

      pwndHelp->ShowWindow(SW_HIDE);
      pwndClose->MoveWindow(rHelp);
      GetDlgItem(IDREMOVE)->MoveWindow(rClose);
      GetDlgItem(IDEDIT)->MoveWindow(rRemove);
   }

   if ( bHideRemove )
   {
      CWnd* pwndRemove = GetDlgItem(IDREMOVE);
      CRect rRemove;
      pwndRemove->GetWindowRect(&rRemove);
      ScreenToClient(rRemove);
      
      pwndRemove->ShowWindow(SW_HIDE);
      GetDlgItem(IDEDIT)->MoveWindow(rRemove);
   }

   if (!m_bEnableEdit)
   {
      GetDlgItem(IDEDIT)->ShowWindow(SW_HIDE);
   }

   // string for group box
   CString strGroupLabel;
   HICON hIcon;
   switch(m_Severity)
   {
   case eafTypes::statusInformation:
      strGroupLabel = _T("Information");
      hIcon = ::LoadIcon(nullptr,IDI_INFORMATION);
      break;
   
   case eafTypes::statusWarning:
      strGroupLabel = _T("Warning");
      hIcon = ::LoadIcon(nullptr,IDI_WARNING);
      break;

   case eafTypes::statusError:
      strGroupLabel = _T("Error");
      hIcon = ::LoadIcon(nullptr,IDI_ERROR);
      break;

   default:
      ATLASSERT(false); // should never get here
   }
	GetDlgItem(IDC_GROUP)->SetWindowText(strGroupLabel);

   CStatic* pIcon = (CStatic*)GetDlgItem(IDC_MY_ICON);
   pIcon->SetIcon(hIcon);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CStatusMessageDialog::OnBnClickedEdit()
{
   m_StatusItemDisplayReturn = eafTypes::eafsiEdit;
   OnOK();
}


void CStatusMessageDialog::OnBnClickedRemove()
{
   m_StatusItemDisplayReturn = eafTypes::eafsiRemove;
   OnOK();
}


void CStatusMessageDialog::OnBnClickedClose()
{
   m_StatusItemDisplayReturn = eafTypes::eafsiClose;
   OnOK();
}

eafTypes::StatusItemDisplayReturn CStatusMessageDialog::GetReturnValue() const
{
   return m_StatusItemDisplayReturn;
}
