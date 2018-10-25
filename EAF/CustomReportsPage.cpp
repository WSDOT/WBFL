///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2014  Washington State Department of Transportation
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
// CustomReportsPage.cpp : implementation file
//

#include "stdafx.h"
#include "CustomReportsPage.h"

#include <EAF\EAFUtilities.h>
#include <EAF\EAFDocument.h>

#include "EditCustomReportDlg.h"
#include "ConfigureReportsDlg.h"
#include "EAFExportCustomReports.h"
#include "EAFCustomReportConflictDlg.h"

static bool DoesFileExist(const CString& filename)
{
   if (filename.IsEmpty())
   {
      return false;
   }
   else
   {
      CFileFind finder;
      BOOL is_file;
      is_file = finder.FindFile(filename);
      return (is_file!=0);
   }
}

// CCustomReportsPage dialog

IMPLEMENT_DYNAMIC(CCustomReportsPage, CPropertyPage)

CCustomReportsPage::CCustomReportsPage()
	: CPropertyPage(CCustomReportsPage::IDD)
{
}

CCustomReportsPage::~CCustomReportsPage()
{
}

void CCustomReportsPage::DoDataExchange(CDataExchange* pDX)
{
   CPropertyPage::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_CUSTOM_REPORT_LIST, m_CustomReportsList);
   DDX_Control(pDX, IDC_EDIT, m_EditButton);
   DDX_Control(pDX, IDC_DELETE, m_DeleteButton);

   if (pDX->m_bSaveAndValidate)
   {
   }
   else if(!m_bInInit)
   {
      InsertData();
   }
}

BOOL CCustomReportsPage::OnInitDialog()
{
   m_bInInit = true;
   CPropertyPage::OnInitDialog();

   // Make it so entire row is selected in list control
   m_CustomReportsList.SetExtendedStyle ( LVS_EX_FULLROWSELECT );

   RECT rect;
   m_CustomReportsList.GetClientRect(&rect);
   int wid = rect.right;

   int st;
   st = m_CustomReportsList.InsertColumn(0,_T("Report Name"),LVCFMT_LEFT, (int)(.4*wid) );
   ATLASSERT(st!=-1);
   st = m_CustomReportsList.InsertColumn(1,_T("Based On"),LVCFMT_LEFT,  (int)(.4*wid) );
   ATLASSERT(st!=-1);
   st = m_CustomReportsList.InsertColumn(2,_T("Favorite?"),LVCFMT_LEFT, (int)(.2*wid) );
   ATLASSERT(st!=-1);

   InsertData();

   m_bInInit = false;

   return TRUE;  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_MESSAGE_MAP(CCustomReportsPage, CPropertyPage)
   ON_BN_CLICKED(IDC_ADDNEW, &CCustomReportsPage::OnBnClickedAddnew)
   ON_BN_CLICKED(IDC_EDIT, &CCustomReportsPage::OnBnClickedEdit)
   ON_BN_CLICKED(IDC_DELETE, &CCustomReportsPage::OnBnClickedDelete)
   ON_NOTIFY(LVN_ITEMCHANGED, IDC_CUSTOM_REPORT_LIST, &CCustomReportsPage::OnLvnItemchangedCustomReportList)
   ON_NOTIFY(NM_DBLCLK, IDC_CUSTOM_REPORT_LIST, &CCustomReportsPage::OnNMDblclkCustomReportList)
   ON_BN_CLICKED(IDC_EXPORT, &CCustomReportsPage::OnBnClickedExport)
   ON_BN_CLICKED(IDC_IMPORT, &CCustomReportsPage::OnBnClickedImport)
END_MESSAGE_MAP()


// CCustomReportsPage message handlers

void CCustomReportsPage::OnBnClickedAddnew()
{
   CEditCustomReportDlg dlg;
   dlg.m_CustomReport = CEAFCustomReport();
   dlg.m_pConfigureReportsDlg = m_pParentDlg;
   dlg.m_bIsFavorite = FALSE;
   if (dlg.DoModal() == IDOK)
   {
      std::pair<CEAFCustomReports::ReportIterator, bool> itb = m_pParentDlg->m_CustomReports.m_Reports.insert(dlg.m_CustomReport);
      if (itb.second==false)
      {
         ATLASSERT(0);
         AfxMessageBox(_T("An unknown error occurred creating custom report"), MB_ICONEXCLAMATION);
      }

      // deal with favoritism
      std::_tstring name = itb.first->m_ReportName;
      m_pParentDlg->DealWithFavorite(name, dlg.m_bIsFavorite==TRUE);

      UpdateData(FALSE);
   }
}

void CCustomReportsPage::OnBnClickedEdit()
{
   EditSelectedReport();
}

void CCustomReportsPage::OnBnClickedDelete()
{
   POSITION pos = m_CustomReportsList.GetFirstSelectedItemPosition( );
   if (pos!=NULL)
   {
      int nItem = m_CustomReportsList.GetNextSelectedItem(pos);

      CString reportname = m_CustomReportsList.GetItemText(nItem, 0);
      CEAFCustomReport stub;
      stub.m_ReportName = reportname;
      CEAFCustomReports::ReportIterator it = m_pParentDlg->m_CustomReports.m_Reports.find(stub);
      if (it != m_pParentDlg->m_CustomReports.m_Reports.end())
      {
         m_pParentDlg->m_CustomReports.m_Reports.erase(it);

         m_CustomReportsList.DeleteItem(nItem);
      }
      else
      {
         ATLASSERT(0);
      }
   }
   else
   {
      ATLASSERT(0);
   }
}

void CCustomReportsPage::InsertData()
{
   m_CustomReportsList.DeleteAllItems();

   int irow=0;

   // Add reports
   CEAFCustomReports::ReportConstIterator it = m_pParentDlg->m_CustomReports.m_Reports.begin();
   while (it != m_pParentDlg->m_CustomReports.m_Reports.end())
   {
      int iloc = m_CustomReportsList.InsertItem(irow, it->m_ReportName.c_str() );
      m_CustomReportsList.SetItemText(iloc, 1, it->m_ParentReportName.c_str() );

      bool isFav = m_pParentDlg->IsFavorite(it->m_ReportName);
      CString yn = isFav ? _T("Yes") : _T("No");
      m_CustomReportsList.SetItemText(irow, 2, yn );

      irow++;
      it++;
   }

   // nothing is selected by default, so we can't edit or delete
   m_EditButton.EnableWindow(FALSE);
   m_DeleteButton.EnableWindow(FALSE);
}

void CCustomReportsPage::OnLvnItemchangedCustomReportList(NMHDR *pNMHDR, LRESULT *pResult)
{
   POSITION pos = m_CustomReportsList.GetFirstSelectedItemPosition( );

   BOOL sel = (pos!=NULL) ? TRUE:FALSE;
   m_EditButton.EnableWindow(sel);
   m_DeleteButton.EnableWindow(sel);
	
   *pResult = 0;
}

void CCustomReportsPage::OnNMDblclkCustomReportList(NMHDR *pNMHDR, LRESULT *pResult)
{
   EditSelectedReport();

   *pResult = 0;
}

void CCustomReportsPage::EditSelectedReport()
{
   POSITION pos = m_CustomReportsList.GetFirstSelectedItemPosition( );
   if (pos!=NULL)
   {
      int nItem = m_CustomReportsList.GetNextSelectedItem(pos);

      CString reportname = m_CustomReportsList.GetItemText(nItem, 0);
      CEAFCustomReport stub;
      stub.m_ReportName = reportname;
      CEAFCustomReports::ReportIterator it = m_pParentDlg->m_CustomReports.m_Reports.find(stub);
      if (it != m_pParentDlg->m_CustomReports.m_Reports.end())
      {
         CEditCustomReportDlg dlg;
         dlg.m_CustomReport = *it;
         dlg.m_bIsFavorite = m_pParentDlg->IsFavorite(it->m_ReportName) ? TRUE : FALSE;
         dlg.m_pConfigureReportsDlg = m_pParentDlg;
         if (dlg.DoModal() == IDOK)
         {
            // Delete from collection and reinsert. This will keep collection properly ordered
            m_pParentDlg->m_CustomReports.m_Reports.erase(it);
            m_pParentDlg->m_CustomReports.m_Reports.insert(dlg.m_CustomReport);

            m_pParentDlg->DealWithFavorite(dlg.m_CustomReport.m_ReportName, dlg.m_bIsFavorite==TRUE);
         }
      }
      else
      {
         ATLASSERT(0);
      }
    
   }

   UpdateData(FALSE);
}

void CCustomReportsPage::OnBnClickedExport()
{
   CEAFExportCustomReports dlg;
   dlg.m_pCustomReports = &(m_pParentDlg->m_CustomReports);
   if (dlg.DoModal()==IDOK)
   {
      CEAFDocument* pDoc = EAFGetDocument();
      CEAFDocTemplate* pTemplate = (CEAFDocTemplate*)pDoc->GetDocTemplate();

      CString strExtensions;
      pTemplate->GetDocString(strExtensions,CDocTemplate::filterExt);
      int pos = 0;
      CString strExtension = strExtensions.Tokenize(_T(";"),pos);
      strExtension = strExtension.Mid(1);
      strExtension += _T("rpt");

      CString strAppName;
      pTemplate->GetDocString(strAppName,CDocTemplate::docName);

	   CString strDefaultName;
      strDefaultName.Format(_T("CustomReports.%s"),strExtension);

      CString strFilter;
      strFilter.Format(_T("%s Custom Report Files (*.%s)|*.%s||"),strAppName,strExtension,strExtension);

	   // Open the SAVEAS dialog box 
	   CFileDialog  fildlg(FALSE,strExtension,strDefaultName,OFN_HIDEREADONLY, strFilter);
	   if (fildlg.DoModal() == IDOK)
	   {
		   CString file_path = fildlg.GetPathName();

		   /* See if the file currently exists */
		   if (DoesFileExist(file_path))
		   {
			   /* See if the user wants to overwrite file */
			   CString msg(_T(" The file: "));
			   msg += file_path + _T(" exists. Overwrite it?");
			   int stm = AfxMessageBox(msg,MB_YESNOCANCEL|MB_ICONQUESTION);
			   if (stm != IDYES) 
            {
               return;
            }
		   }

         // Use structured save to save file
         CHRException hr;
         try
         {
            HRESULT hr2;
            CComPtr<IStructuredSave2> save;
            hr2 = save.CoCreateInstance(CLSID_StructuredSave2);
            if ( FAILED(hr2) )
            {
               ::AfxMessageBox(_T("An error occurred creating CLSID_StructuredSave2"));
               return;
            }

            CComBSTR bpath(file_path);
            hr2 = save->Open(bpath);
            if ( FAILED(hr2) )
            {
               CString err(_T("An error occurred opening the file "));
               err += file_path;
               ::AfxMessageBox(err);
               return;
            }

            CString strUnit;
            strUnit.Format(_T("%sCustomReports"),strAppName);
            hr = save->BeginUnit(CComBSTR(strUnit),1.0);

            // loop over reports and save
            hr = save->put_Property(CComBSTR("NumReports"), CComVariant(dlg.m_SelectedReports.size()));

            std::vector<std::_tstring>::const_iterator itr = dlg.m_SelectedReports.begin();
            while(itr != dlg.m_SelectedReports.end())
            {
               CEAFCustomReport stub;
               stub.m_ReportName = *itr;
               CEAFCustomReports::ReportConstIterator it = m_pParentDlg->m_CustomReports.m_Reports.find(stub);
               if (it != m_pParentDlg->m_CustomReports.m_Reports.end())
               {
                  const CEAFCustomReport& rReport = *it;

                  hr = save->BeginUnit(CComBSTR("CustomReport"),1.0);
                  hr = save->put_Property(CComBSTR("ReportName"), CComVariant(it->m_ReportName.c_str()));
                  hr = save->put_Property(CComBSTR("ParentReportName"), CComVariant(it->m_ParentReportName.c_str()));

                  hr = save->put_Property(CComBSTR("NumChapters"), CComVariant(it->m_Chapters.size()));

                  std::vector<std::_tstring>::const_iterator itchap = it->m_Chapters.begin();
                  while(itchap != it->m_Chapters.end())
                  {
                     hr = save->put_Property(CComBSTR("ChapterName"), CComVariant(itchap->c_str()));
                     itchap++;
                  }

                  hr = save->EndUnit();
               }
               else
               {
                  ATLASSERT(0);
               }

               itr++;
            }

            save->EndUnit();
            save->Close();
         }
         catch(...)
         {
            ATLASSERT(0);
         }

         CString msg;
         msg.Format(_T("%d reports were exported successfully."), dlg.m_SelectedReports.size());
         ::AfxMessageBox(msg, MB_OK);
      }
   }
}

void CCustomReportsPage::OnBnClickedImport()
{
   // Get list of already taken report names
   std::set<std::_tstring> reservedNames = m_pParentDlg->GetReservedReportNames();

   CEAFDocument* pDoc = EAFGetDocument();
   CEAFDocTemplate* pTemplate = (CEAFDocTemplate*)pDoc->GetDocTemplate();

   CString strExtensions;
   pTemplate->GetDocString(strExtensions,CDocTemplate::filterExt);
   int pos = 0;
   CString strExtension = strExtensions.Tokenize(_T(";"),pos);
   strExtension = strExtension.Mid(1);
   strExtension += _T("rpt");

   CString strAppName;
   pTemplate->GetDocString(strAppName,CDocTemplate::docName);

   // start UI dance
   bool doCancel(false);

   CString strFilter;
   strFilter.Format(_T("%s Custom Report Files (*.%s)|*.%s||"),strAppName,strExtension,strExtension);

   CFileDialog  fildlg(TRUE,strExtension,NULL,OFN_FILEMUSTEXIST|OFN_HIDEREADONLY,strFilter);
   INT_PTR stf = fildlg.DoModal();
   if (stf==IDOK)
   {
      CString file_path = fildlg.GetPathName();

      // Use structured Load to Load file
      HRESULT hr;
      CComPtr<IStructuredLoad2> Load;
      hr = Load.CoCreateInstance(CLSID_StructuredLoad2);
      if ( FAILED(hr) )
      {
         ::AfxMessageBox(_T("An error occurred creating CLSID_StructuredLoad2"));
         return;
      }

      CComBSTR bpath(file_path);
      hr = Load->Open(bpath);
      if ( FAILED(hr) )
      {
         CString err(_T("An error occurred opening the file "));
         err += file_path;
         ::AfxMessageBox(err);
         return;
      }

      CString strUnit;
      strUnit.Format(_T("%sCustomReports"),strAppName);
      hr = Load->BeginUnit(CComBSTR(strUnit));
      if ( FAILED(hr) )
      {
         CString err(_T("Error reading custom report file. - Bad Format"));
         ::AfxMessageBox(err);
         return;
      }
      else
      {
         Float64 vers;
         Load->get_Version(&vers);
         if (vers != 1.0)
         {
            CString err(_T("Error reading custom report file. - File version is newer. Software is out of date."));
            ::AfxMessageBox(err);
            return;
         }

         CEAFCustomReports Reports;

         CComVariant varNumReports;
         varNumReports.vt = VT_I4;
         hr = Load->get_Property(CComBSTR("NumReports"), &varNumReports);

         for(long ir=0; ir<varNumReports.lVal; ir++)
         {
            CEAFCustomReport Report;

            hr = Load->BeginUnit(_T("CustomReport")); 
            if ( FAILED(hr) )
            {
               ::AfxMessageBox(_T("Error reading custom report file. - Format"));
               return;
            }

            CComVariant varName, varParent;
            varName.vt = VT_BSTR;
            varParent.vt = VT_BSTR;
            HRESULT hr = Load->get_Property(_T("ReportName"), &varName);
            if ( FAILED(hr) )
            {
               ::AfxMessageBox(_T("Error reading custom report file. - Format"));
               return;
            }

            Report.m_ReportName = varName.bstrVal;

            hr = Load->get_Property(_T("ParentReportName"), &varParent);
            if ( FAILED(hr) )
            {
               ::AfxMessageBox(_T("Error reading custom report file. - Format"));
               return;
            }

            Report.m_ParentReportName = varParent.bstrVal;

            CComVariant varNumChapters;
            varNumChapters.vt = VT_I4;
            hr = Load->get_Property(CComBSTR("NumChapters"), &varNumChapters);

            for(long ic=0; ic<varNumChapters.lVal; ic++)
            {
               CComVariant varChapter;
               varChapter.vt = VT_BSTR;
               hr = Load->get_Property(_T("ChapterName"),&varChapter);
               Report.m_Chapters.push_back(varChapter.bstrVal);
            }

            // check that report is unique
            bool doInsert(true);
            std::set<std::_tstring>::const_iterator itf = reservedNames.find(Report.m_ReportName);
            if (itf != reservedNames.end())
            {
               CEAFCustomReportConflictDlg dlgc;
               dlgc.m_pReservedNames = &reservedNames;
               dlgc.m_pReport = &Report;
               INT_PTR st = dlgc.DoModal();
               if (st == ID_SKIP )
               {
                  doInsert = false;
               }
               else if (st == IDCANCEL )
               {
                  doCancel = true;
                  break; 
               }
               else if (st == ID_RENAME )
               {
                  // report was renamed - nothing to do here
               }
            }


            if (doInsert)
            {
               Reports.m_Reports.insert(Report);
            }

            VARIANT_BOOL bEnd;
            Load->EndUnit(&bEnd);
         }

         VARIANT_BOOL bEnd;
         Load->EndUnit(&bEnd);
         Load->Close();

         // Reports are loaded from file. Now a bit more error checking
         int numreports = 0;
         if (!doCancel)
         {
            CEAFCustomReports::ReportConstIterator itrpt = Reports.m_Reports.begin();
            while(itrpt != Reports.m_Reports.end())
            {
               const CEAFCustomReport& rReport = *itrpt;

               // Make sure parent report exists
               std::set<std::_tstring>::const_iterator itchap =m_pParentDlg->m_BuiltInReports.find( rReport.m_ParentReportName );
               if (itchap == m_pParentDlg->m_BuiltInReports.end())
               {
                  CString msg;
                  msg.Format(_T("Error - Importing the custom report %s. The parent report named %s does not exist on this system. Import of this report was skipped."), rReport.m_ReportName.c_str(), rReport.m_ParentReportName.c_str());
                  ::AfxMessageBox(msg);
               }
               else
               {
                  m_pParentDlg->m_CustomReports.m_Reports.insert(rReport);
                  numreports++;
               }

               itrpt++;
            }

            CString msg;
            msg.Format(_T("%d reports were imported."), numreports);
            ::AfxMessageBox(msg);

            InsertData();
         }
         else
         {
            ::AfxMessageBox(_T("Report Import was Cancelled"));
         }
      }
   }
}
