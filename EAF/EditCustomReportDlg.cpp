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
// EditCustomReportDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EditCustomReportDlg.h"

#include "ConfigureReportsDlg.h"
#include <AgentTools.h>
#include <IReportManager.h>

// CEditCustomReportDlg dialog

IMPLEMENT_DYNAMIC(CEditCustomReportDlg, CDialog)

CEditCustomReportDlg::CEditCustomReportDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEditCustomReportDlg::IDD, pParent)
   , m_bIsFavorite(FALSE)
{
   m_FromInit = false;
}

CEditCustomReportDlg::~CEditCustomReportDlg()
{
}

void CEditCustomReportDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);

   DDX_Control(pDX, IDC_PARENT_COMBO, m_ParentReportCombo);

   // only fill parent combo once.
   if (m_FromInit)
   {
      std::set<std::_tstring>::const_iterator it = m_pConfigureReportsDlg->m_BuiltInReports.begin();
      while (it != m_pConfigureReportsDlg->m_BuiltInReports.end())
      {
         m_ParentReportCombo.AddString( it->c_str() );
         it++;
      }
   }

   DDX_Control(pDX, IDC_REPORT_NAME, m_ReportName);

   CString strParentReport = m_CustomReport.m_ParentReportName.c_str();
   DDX_CBString(pDX, IDC_PARENT_COMBO, strParentReport);

   if (pDX->m_bSaveAndValidate)
   {
      CString strName;
      m_ReportName.GetWindowTextW(strName);
      strName.Trim();

      if (strName.IsEmpty())
      {
         AfxMessageBox(_T("Report Name cannot be blank"), MB_ICONEXCLAMATION);
         pDX->Fail();
      }

      if (-1 != strName.FindOneOf(_T("\t")))
      {
         // UI should make this impossible, but...
         AfxMessageBox(_T("Report Name cannot contain Tabs"), MB_ICONEXCLAMATION);
         pDX->Fail();
      }

      if (strParentReport.IsEmpty())
      {
         AfxMessageBox(_T("You must select a Parent Report"), MB_ICONEXCLAMATION);
         pDX->Fail();
      }

      // Must have a unique report name
      if (strName != m_CustomReport.m_ReportName.c_str())
      {
         std::set<std::_tstring> rnames = m_pConfigureReportsDlg->GetReservedReportNames();
         std::set<std::_tstring>::iterator itf = rnames.find(std::_tstring(strName));
         if (itf != rnames.end())
         {
            AfxMessageBox(_T("The input report name already exists. You must enter a unique name. Please enter a new one."), MB_ICONEXCLAMATION);
            pDX->Fail();
         }
      }

      int cnt = m_SelectedChaptersList.GetCount();
      if (cnt==0)
      {
         AfxMessageBox(_T("Reports must have at least one chapter. Please select a chapter"), MB_ICONEXCLAMATION);
         pDX->Fail();
      }

      m_CustomReport.m_ReportName = strName;
      m_CustomReport.m_ParentReportName = strParentReport;

      m_CustomReport.m_Chapters.clear();
      for (int i=0; i<cnt; i++)
      {
         TCHAR strChapter[128];
         m_SelectedChaptersList.GetText(i, strChapter);
         m_CustomReport.m_Chapters.push_back(strChapter);
      }
   }
   else
   {
      m_ReportName.SetWindowText(m_CustomReport.m_ReportName.c_str());
   }

   DDX_Control(pDX, IDC_AVAILABLE_LIST, m_AvailableChaptersList);
   DDX_Control(pDX, IDC_SELECTED_LIST, m_SelectedChaptersList);
   DDX_Control(pDX, IDC_ADD_BUTTON, m_AddButton);
   DDX_Control(pDX, IDC_REMOVE_BUTTON, m_RemoveButton);
   DDX_Control(pDX, IDC_MOVE_UP_BUTTON, m_MoveUpButton);
   DDX_Control(pDX, IDC_MOVE_DOWN_BUTTON, m_MoveDownButton);
   DDX_Check(pDX, IDC_CHECK1, m_bIsFavorite);
}

BEGIN_MESSAGE_MAP(CEditCustomReportDlg, CDialog)
   ON_CBN_SELCHANGE(IDC_PARENT_COMBO, &CEditCustomReportDlg::OnCbnSelchangeParentCombo)
   ON_BN_CLICKED(IDC_ADD_BUTTON, &CEditCustomReportDlg::OnBnClickedAddButton)
   ON_BN_CLICKED(IDC_REMOVE_BUTTON, &CEditCustomReportDlg::OnBnClickedRemoveButton)
   ON_BN_CLICKED(IDC_MOVE_UP_BUTTON, &CEditCustomReportDlg::OnBnClickedMoveUpButton)
   ON_BN_CLICKED(IDC_MOVE_DOWN_BUTTON, &CEditCustomReportDlg::OnBnClickedMoveDownButton)
   ON_LBN_SELCHANGE(IDC_AVAILABLE_LIST, &CEditCustomReportDlg::OnLbnSelchangeAvailableList)
   ON_LBN_SELCHANGE(IDC_SELECTED_LIST, &CEditCustomReportDlg::OnLbnSelchangeSelectedList)
   ON_BN_CLICKED(IDC_ADD_ALL_BUTTON, &CEditCustomReportDlg::OnBnClickedAddAllButton)
   ON_BN_CLICKED(IDC_REMOVE_ALL_BUTTON, &CEditCustomReportDlg::OnBnClickedRemoveAllButton)
   ON_LBN_DBLCLK(IDC_AVAILABLE_LIST, &CEditCustomReportDlg::OnLbnDblclkAvailableList)
   ON_LBN_DBLCLK(IDC_SELECTED_LIST, &CEditCustomReportDlg::OnLbnDblclkSelectedList)
END_MESSAGE_MAP()

// CEditCustomReportDlg message handlers

BOOL CEditCustomReportDlg::OnInitDialog()
{
   m_FromInit = true;
   CDialog::OnInitDialog();
   m_FromInit = false;

   FillChapterData(true);
   OnSelectAvailable( FALSE );
   OnSelectSelected( FALSE );

   return TRUE;  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}

void CEditCustomReportDlg::FillChapterData(bool initial)
{
   m_AvailableChaptersList.ResetContent();
   m_SelectedChaptersList.ResetContent();

   // Fill chapter list boxes
   int sel = m_ParentReportCombo.GetCurSel();
   if ( sel != CB_ERR )
   {
      CString rptname;
      m_ParentReportCombo.GetLBText(sel, rptname);

      GET_IFACE2(m_pConfigureReportsDlg->m_pBroker,IReportManager,pReportMgr);
      boost::shared_ptr<CReportBuilder> pBuilder = pReportMgr->GetReportBuilder(rptname);
      CollectionIndexType nc = pBuilder->GetChapterBuilderCount();
      for (CollectionIndexType ic=0; ic<nc; ic++)
      {
         boost::shared_ptr<CChapterBuilder> pCb = pBuilder->GetChapterBuilder(ic);
         std::_tstring cbname = pCb->GetName();

         // At initial time we are loading data as in report. if not initial, we have no chapters selected
         if (initial)
         {
            std::vector<std::_tstring>::const_iterator itc = std::find(m_CustomReport.m_Chapters.begin(), m_CustomReport.m_Chapters.end(), cbname);
            if (itc == m_CustomReport.m_Chapters.end())
            {
               m_AvailableChaptersList.AddString(cbname.c_str());
            }
         }
         else
         {
            m_AvailableChaptersList.AddString(cbname.c_str());
         }
      }

      // Selected chapters
      if (initial)
      {
         std::vector<std::_tstring>::const_iterator itch = m_CustomReport.m_Chapters.begin();
         while(itch != m_CustomReport.m_Chapters.end())
         {
            m_SelectedChaptersList.AddString(itch->c_str());
            itch++;
         }
      }
   }
}

void CEditCustomReportDlg::OnCbnSelchangeParentCombo()
{
   FillChapterData(false);
}

void CEditCustomReportDlg::OnBnClickedAddButton()
{
   int sel = m_AvailableChaptersList.GetCurSel();
   if (sel!=LB_ERR)
   {
      CString strSel;
      m_AvailableChaptersList.GetText(sel, strSel);
      m_AvailableChaptersList.DeleteString(sel);
      m_AvailableChaptersList.SetCurSel(-1);

      m_SelectedChaptersList.AddString(strSel);
      m_SelectedChaptersList.SetCurSel(-1);

      OnSelectAvailable( FALSE );
   }
   else
      ATLASSERT(0);
}

void CEditCustomReportDlg::OnBnClickedRemoveButton()
{
   int sel = m_SelectedChaptersList.GetCurSel();
   if (sel!=LB_ERR)
   {
      CString strSel;
      m_SelectedChaptersList.GetText(sel, strSel);
      m_SelectedChaptersList.DeleteString(sel);
      m_SelectedChaptersList.SetCurSel(-1);

      m_AvailableChaptersList.AddString(strSel);
      m_AvailableChaptersList.SetCurSel(-1);

      OnSelectSelected( FALSE );
   }
   else
      ATLASSERT(0);
}

void CEditCustomReportDlg::OnBnClickedAddAllButton()
{
   int cnt = m_AvailableChaptersList.GetCount();
   // Move strings,
   for (int il=0; il<cnt; il++)
   {
      CString strSel;
      m_AvailableChaptersList.GetText(il, strSel);
      m_SelectedChaptersList.AddString(strSel);
   }

   // then delete them
   for (int il=0; il<cnt; il++)
   {
      m_AvailableChaptersList.DeleteString(0);
   }

   m_SelectedChaptersList.SetCurSel(-1);
   m_AvailableChaptersList.SetCurSel(-1);
   OnSelectSelected( FALSE );
}

void CEditCustomReportDlg::OnBnClickedRemoveAllButton()
{
   int cnt = m_SelectedChaptersList.GetCount();
   // Move strings,
   for (int il=0; il<cnt; il++)
   {
      CString strSel;
      m_SelectedChaptersList.GetText(il, strSel);
      m_AvailableChaptersList.AddString(strSel);
   }

   // then delete them
   for (int il=0; il<cnt; il++)
   {
      m_SelectedChaptersList.DeleteString(0);
   }

   m_SelectedChaptersList.SetCurSel(-1);
   m_AvailableChaptersList.SetCurSel(-1);
   OnSelectSelected( FALSE );
}

void CEditCustomReportDlg::OnBnClickedMoveUpButton()
{
   int sel = m_SelectedChaptersList.GetCurSel();
   if (sel!=LB_ERR && sel!=0)
   {
      CString strSel;
      m_SelectedChaptersList.GetText(sel, strSel);
      m_SelectedChaptersList.DeleteString(sel);
      sel = m_SelectedChaptersList.InsertString(sel-1, strSel);
      m_SelectedChaptersList.SetCurSel(sel);
   }
   else
      ::MessageBeep(MB_ICONASTERISK);
}

void CEditCustomReportDlg::OnBnClickedMoveDownButton()
{
   int cnt = m_SelectedChaptersList.GetCount();
   int sel = m_SelectedChaptersList.GetCurSel();
   if (sel!=LB_ERR && sel<cnt-1)
   {
      CString strSel;
      m_SelectedChaptersList.GetText(sel, strSel);
      m_SelectedChaptersList.DeleteString(sel);
      sel = m_SelectedChaptersList.InsertString(sel+1, strSel);
      m_SelectedChaptersList.SetCurSel(sel);
   }
   else
      ::MessageBeep(MB_ICONASTERISK);
}

void CEditCustomReportDlg::OnLbnSelchangeAvailableList()
{
   int pos = m_AvailableChaptersList.GetCurSel( );
   BOOL sel = (pos!=LB_ERR) ? TRUE:FALSE;

   OnSelectAvailable( sel );

   OnSelectSelected(FALSE);
}

void CEditCustomReportDlg::OnLbnSelchangeSelectedList()
{
   int pos = m_SelectedChaptersList.GetCurSel( );
   BOOL sel = (pos!=LB_ERR) ? TRUE:FALSE;
   OnSelectSelected( sel );

   OnSelectAvailable(FALSE);
}

void CEditCustomReportDlg::OnSelectAvailable(BOOL sel)
{
   m_AddButton.EnableWindow(sel);
   if (sel==FALSE)
   {
      m_AvailableChaptersList.SetCurSel(-1);
   }
}

void CEditCustomReportDlg::OnSelectSelected(BOOL sel)
{
   m_RemoveButton.EnableWindow(sel);
   m_MoveUpButton.EnableWindow(sel);
   m_MoveDownButton.EnableWindow(sel);

   if (sel==FALSE)
   {
      m_SelectedChaptersList.SetCurSel(-1);
   }
}


void CEditCustomReportDlg::OnLbnDblclkAvailableList()
{
   OnBnClickedAddButton();
}

void CEditCustomReportDlg::OnLbnDblclkSelectedList()
{
   OnBnClickedRemoveButton();
}
