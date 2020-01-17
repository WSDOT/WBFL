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

// EAFAboutDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include <EAF\EAFAboutDlg.h>
#include <EAF\EAFApp.h>
#include <MFCTools\VersionInfo.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CEAFAboutDlg dialog

IMPLEMENT_DYNAMIC(CEAFAboutDlg, CDialog)

CEAFAboutDlg::CEAFAboutDlg(HICON hIcon,UINT nIDTemplate,CWnd* pParent /*=nullptr*/)
: CDialog(nIDTemplate == 0 ? IDD_ABOUTBOX : nIDTemplate, pParent)
{
   m_hIcon = hIcon;
}

CEAFAboutDlg::~CEAFAboutDlg()
{
}

void CEAFAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
   DDX_Control(pDX,IDC_APPLIST,m_AppList);
   DDX_Control(pDX,IDC_DESCRIPTION,m_Description);
}


BEGIN_MESSAGE_MAP(CEAFAboutDlg, CDialog)
   ON_LBN_SELCHANGE(IDC_APPLIST,&CEAFAboutDlg::OnAppListSelChanged)
	ON_BN_CLICKED(IDC_MOREINFO,OnMoreInfo)
   ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CEAFAboutDlg message handlers

BOOL CEAFAboutDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   // put the icon in the dialog
   CStatic* pIcon = (CStatic*)GetDlgItem(IDC_APPICON);
   if ( m_hIcon == nullptr )
   {
      CWnd* pWnd = EAFGetMainFrame();
      m_hIcon = pWnd->GetIcon(TRUE);
   }

   if ( m_hIcon )
   {
      pIcon->SetIcon( m_hIcon );
   }
   else
   {
      pIcon->ShowWindow(SW_HIDE);
   }

   // Get the version information and update the version # and copyright
   CString strTitle;
   strTitle.Format(_T("About %s"),AfxGetAppName());
   SetWindowText( strTitle );

   CString strExe = EAFGetApp()->m_pszAppName;
   strExe += _T(".exe");

   CVersionInfo verInfo;
   verInfo.Load(strExe);
   CString strVersion = verInfo.GetFileVersionAsString();
   CString strCopyright = verInfo.GetLegalCopyright();

#if defined _WIN64
   CString strPlatform(_T("x64"));
#else
   CString strPlatform(_T("x86"));
#endif
   CString str;
   str.Format(_T("Version %s (%s)"),strVersion,strPlatform);
   GetDlgItem(IDC_VERSION)->SetWindowText(str);
   GetDlgItem(IDC_COPYRIGHT)->SetWindowText(strCopyright);

   // Fill the list control with plugin names
   CEAFApp* pApp = EAFGetApp();
   CEAFComponentInfoManager* pComponentInfoMgr = pApp->GetComponentInfoManager();
   CollectionIndexType nPlugins = pComponentInfoMgr->GetPluginCount();
   
   // for each plugin
   for ( CollectionIndexType pluginIdx = 0; pluginIdx < nPlugins; pluginIdx++ )
   {
      CComPtr<IEAFComponentInfo> plugin;
      pComponentInfoMgr->GetPlugin(pluginIdx,&plugin);
      UINT idx = m_AppList.AddString(plugin->GetName());
      m_AppList.SetItemData(idx,pluginIdx);
   }

   m_AppList.SetCurSel(0);
   OnAppListSelChanged();

   return TRUE;  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}

void CEAFAboutDlg::OnAppListSelChanged()
{
   int idx = m_AppList.GetCurSel();
   if ( idx != LB_ERR )
   {
      CEAFApp* pApp = EAFGetApp();
      CEAFComponentInfoManager* pComponentInfoMgr = pApp->GetComponentInfoManager();
      CComPtr<IEAFComponentInfo> component;
      DWORD_PTR pluginIdx = m_AppList.GetItemData(idx);
      pComponentInfoMgr->GetPlugin(pluginIdx,&component);
      m_Description.SetWindowText(component->GetDescription());
      if ( component->HasMoreInfo() )
         GetDlgItem(IDC_MOREINFO)->EnableWindow(TRUE);
      else
         GetDlgItem(IDC_MOREINFO)->EnableWindow(FALSE);
   }
   else
   {
      GetDlgItem(IDC_MOREINFO)->EnableWindow(FALSE);
      m_Description.SetWindowText(_T(""));
   }
}

void CEAFAboutDlg::OnMoreInfo()
{
   int idx = m_AppList.GetCurSel();
   if ( idx != LB_ERR )
   {
      CEAFApp* pApp = EAFGetApp();
      CEAFComponentInfoManager* pComponentInfoMgr = pApp->GetComponentInfoManager();

      DWORD_PTR pluginIdx = m_AppList.GetItemData(idx);
      CComPtr<IEAFComponentInfo> component;
      pComponentInfoMgr->GetPlugin(pluginIdx,&component);

      component->OnMoreInfo();
      OnAppListSelChanged();
   }
}

HBRUSH CEAFAboutDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	if (pWnd->GetDlgCtrlID() == IDC_DESCRIPTION)
		return GetSysColorBrush(COLOR_WINDOW);

	return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
}
