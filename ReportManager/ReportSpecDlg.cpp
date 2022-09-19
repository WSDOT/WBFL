///////////////////////////////////////////////////////////////////////
// ReportManager - Manages report definitions
// Copyright © 1999-2022  Washington State Department of Transportation
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

// ReportSpecDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ReportManager.h"
#include "ReportSpecDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReportSpecDlg dialog


CReportSpecDlg::CReportSpecDlg(const ReportDescription& rptDesc, std::shared_ptr<ReportSpecification>& pRptSpec,CWnd* pParent /*=nullptr*/)
	: CDialog(CReportSpecDlg::IDD, pParent), m_RptDesc(rptDesc), m_pInitRptSpec(pRptSpec)
{
	//{{AFX_DATA_INIT(CReportSpecDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
   m_ReportName = rptDesc.GetReportName().c_str();
}


void CReportSpecDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReportSpecDlg)
	DDX_Text(pDX, IDC_NAME, m_ReportName);
	DDX_Control(pDX, IDC_CHAPTER_LIST, m_clbChapterList);
	//}}AFX_DATA_MAP

   if ( pDX->m_bSaveAndValidate )
   {
      m_ChapterInfo.clear();
      m_ChapterList.clear();

      int cChapters = m_clbChapterList.GetCount();
      for ( int ch = 0; ch < cChapters; ch++ )
      {
         if ( m_clbChapterList.GetCheck( ch ) == 1 )
         {
            ChapterInfo chInfo;
            CString strBuffer;
            m_clbChapterList.GetText( ch, strBuffer);
            chInfo.Key = strBuffer;
            chInfo.Name = strBuffer;
            chInfo.MaxLevel = (Uint16)m_clbChapterList.GetItemData(ch);

            m_ChapterInfo.push_back(chInfo);
            m_ChapterList.push_back(chInfo.Name);
         }
      }

      if ( m_ChapterInfo.size() == 0 )
      {
         pDX->PrepareCtrl(IDC_CHAPTER_LIST);
         AfxMessageBox(IDS_E_NOCHAPTERS);
         pDX->Fail();
      }
   }

}


BEGIN_MESSAGE_MAP(CReportSpecDlg, CDialog)
	//{{AFX_MSG_MAP(CReportSpecDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReportSpecDlg message handlers

BOOL CReportSpecDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
   UpdateChapterList();
	
   if ( m_pInitRptSpec )
      InitChapterListFromSpec();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CReportSpecDlg::UpdateChapterList()
{
   // Clear out the list box
   m_clbChapterList.ResetContent();

   std::vector<ChapterInfo> vchInfo = m_RptDesc.GetChapterInfo();
   std::vector<ChapterInfo>::iterator iter;
   for ( iter = vchInfo.begin(); iter != vchInfo.end(); iter++ )
   {
      ChapterInfo chInfo = *iter;
      int idx = m_clbChapterList.AddString( chInfo.Name.c_str() );
      if ( idx != LB_ERR )
      {
         m_clbChapterList.SetCheck(idx,chInfo.Select ? 1 : 0); // turn check on
         m_clbChapterList.SetItemData(idx,chInfo.MaxLevel);
      }
   }
   m_clbChapterList.SetCurSel(-1);
}

void CReportSpecDlg::ClearChapterCheckMarks()
{
   int cChapters = m_clbChapterList.GetCount();
   for ( int ch = 0; ch < cChapters; ch++ )
   {
      m_clbChapterList.SetCheck(ch,0);
   }
}

void CReportSpecDlg::InitChapterListFromSpec()
{
   ClearChapterCheckMarks();
   std::vector<ChapterInfo> chInfo = m_pInitRptSpec->GetChapterInfo();
   std::vector<ChapterInfo>::iterator iter;
   for ( iter = chInfo.begin(); iter != chInfo.end(); iter++ )
   {
      ChapterInfo& ch = *iter;
      int cChapters = m_clbChapterList.GetCount();
      for ( int idx = 0; idx < cChapters; idx++ )
      {
         CString strChapter;
         m_clbChapterList.GetText(idx,strChapter);
         if ( strChapter == ch.Name.c_str() )
         {
            m_clbChapterList.SetCheck(idx,1);
            break;
         }
      }
   }
}
