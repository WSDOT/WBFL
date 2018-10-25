///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2010  Washington State Department of Transportation
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

CManagePluginsDlg::CManagePluginsDlg(const CATID& catid,CWnd* pParent /*=NULL*/)
	: CDialog(CManagePluginsDlg::IDD, pParent),
   m_strSection("Plugins")
{
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

   m_PluginList.SetCheckStyle( BS_AUTOCHECKBOX );

   InitList();

   return TRUE;  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CManagePluginsDlg::InitList()
{
   USES_CONVERSION;

   CWaitCursor cursor;

   CComPtr<ICatRegister> pICatReg;
   HRESULT hr = pICatReg.CoCreateInstance(CLSID_StdComponentCategoriesMgr);
   if ( FAILED(hr) )
   {
      AfxMessageBox("Failed to create the component category manager");
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
   CEAFApp* pApp = (CEAFApp*)AfxGetApp();
   while ( SUCCEEDED(pIEnumCLSID->Next(nPlugins,clsid,&nFetched)) && 0 < nFetched)
   {
      for ( ULONG i = 0; i < nFetched; i++ )
      {
         LPOLESTR pszUserType;
         OleRegGetUserType(clsid[i],USERCLASSTYPE_SHORT,&pszUserType);
         int idx = m_PluginList.AddString(OLE2A(pszUserType));

         LPOLESTR pszCLSID;
         ::StringFromCLSID(clsid[i],&pszCLSID);
         
         CString strState = pApp->GetProfileString(m_strSection,OLE2A(pszCLSID),_T("Enabled"));
         m_CLSIDs.push_back(CString(pszCLSID));

         ::CoTaskMemFree((void*)pszCLSID);

         if ( strState.CompareNoCase("Enabled") == 0 )
            m_PluginList.SetCheck(idx,TRUE);
         else
            m_PluginList.SetCheck(idx,FALSE);
      }
   }

   return TRUE;
}

void CManagePluginsDlg::OnOK()
{
   CEAFApp* pApp = (CEAFApp*)AfxGetApp();

   int nItems = m_PluginList.GetCount();
   for (int idx = 0; idx < nItems; idx++ )
   {
      CString strCLSID = m_CLSIDs[idx];
      BOOL bEnabled = m_PluginList.GetCheck(idx);

      pApp->WriteProfileString(m_strSection,strCLSID,(bEnabled ? _T("Enabled") : _T("Disabled")));
   }
   CDialog::OnOK();
}
