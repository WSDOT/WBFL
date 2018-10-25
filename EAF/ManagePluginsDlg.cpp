///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2012  Washington State Department of Transportation
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

// ManageDocPlugins.cpp : implementation file
//

#include "stdafx.h"
#include "ManagePluginsDlg.h"

#include <EAF\EAFApp.h>


// CManagePluginsDlg dialog

IMPLEMENT_DYNAMIC(CManagePluginsDlg, CDialog)

CManagePluginsDlg::CManagePluginsDlg(LPCTSTR lpszTitle,const CATID& catid,CWnd* pParent /*=NULL*/)
	: CDialog(CManagePluginsDlg::IDD, pParent),
   m_strSection("Plugins")
{
   m_Title = lpszTitle;
   m_CATID = catid;
}

CManagePluginsDlg::~CManagePluginsDlg()
{
}

void CManagePluginsDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_PLUGIN_LIST, m_PluginList);
}


BEGIN_MESSAGE_MAP(CManagePluginsDlg, CDialog)
END_MESSAGE_MAP()


// CManagePluginsDlg message handlers

BOOL CManagePluginsDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   if ( !m_Title.IsEmpty() )
      SetWindowText(m_Title);

   m_PluginList.SetCheckStyle( BS_AUTOCHECKBOX );

   InitList();

   return TRUE;  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CManagePluginsDlg::InitList()
{
   USES_CONVERSION;

   CWaitCursor cursor;

   m_PluginStates.clear();

   CComPtr<ICatRegister> pICatReg;
   HRESULT hr = pICatReg.CoCreateInstance(CLSID_StdComponentCategoriesMgr);
   if ( FAILED(hr) )
   {
      AfxMessageBox(_T("Failed to create the component category manager"));
      return FALSE;
   }

   CComQIPtr<ICatInformation> pICatInfo(pICatReg);
   CComPtr<IEnumCLSID> pIEnumCLSID;

   const int nID = 1;
   CATID ID[nID];

   ID[0] = m_CATID;
   pICatInfo->EnumClassesOfCategories(nID,ID,0,NULL,&pIEnumCLSID);

   const int nPlugins = 5;
   CLSID clsid[nPlugins]; 
   ULONG nFetched = 0;

   // Load Importers
   CEAFApp* pApp = EAFGetApp();
   while ( SUCCEEDED(pIEnumCLSID->Next(nPlugins,clsid,&nFetched)) && 0 < nFetched)
   {
      for ( ULONG i = 0; i < nFetched; i++ )
      {
         LPOLESTR pszUserType;
         OleRegGetUserType(clsid[i],USERCLASSTYPE_SHORT,&pszUserType);
         int idx = m_PluginList.AddString(OLE2T(pszUserType));

         LPOLESTR pszCLSID;
         ::StringFromCLSID(clsid[i],&pszCLSID);
         
         CString strCLSID(pszCLSID);

         CString strState = pApp->GetProfileString(m_strSection,strCLSID,_T("Enabled"));
         
         bool bInitiallyEnabled = (strState.CompareNoCase(_T("Enabled")) == 0 ? true : false);
         m_PluginList.SetCheck(idx,bInitiallyEnabled);

         CEAFPluginState state(clsid[i],strCLSID,bInitiallyEnabled);
         m_PluginStates.push_back(state);

         ::CoTaskMemFree((void*)pszCLSID);
      }
   }

   return TRUE;
}

void CManagePluginsDlg::OnOK()
{
   int nItems = m_PluginList.GetCount();
   for (int idx = 0; idx < nItems; idx++ )
   {
      BOOL bEnabled = m_PluginList.GetCheck(idx);

      m_PluginStates[idx].SetState(bEnabled ? true : false);
   }
   CDialog::OnOK();
}

void CManagePluginsDlg::OnCancel()
{
   m_PluginStates.clear();

   CDialog::OnCancel();
}
