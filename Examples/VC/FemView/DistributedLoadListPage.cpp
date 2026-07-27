// DistributedLoadListPage.cpp : implementation file
//

#include "stdafx.h"
#include "FEA2D.h"
#include "DistributedLoadListPage.h"
#include "ModelPropertiesDlg.h"


// CDistributedLoadListPage dialog

IMPLEMENT_DYNAMIC(CDistributedLoadListPage, CPropertyPage)

CDistributedLoadListPage::CDistributedLoadListPage()
	: CPropertyPage(CDistributedLoadListPage::IDD)
{

}

CDistributedLoadListPage::~CDistributedLoadListPage()
{
}

void CDistributedLoadListPage::DoDataExchange(CDataExchange* pDX)
{
   CPropertyPage::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_LIST, m_ctrlList);
}


BEGIN_MESSAGE_MAP(CDistributedLoadListPage, CPropertyPage)
END_MESSAGE_MAP()


// CDistributedLoadListPage message handlers

BOOL CDistributedLoadListPage::OnInitDialog()
{
   CPropertyPage::OnInitDialog();


   m_ctrlList.InsertColumn(0,_T("ID"));
   m_ctrlList.InsertColumn(1,_T("Member"));
   m_ctrlList.InsertColumn(2,_T("Direction"));
   m_ctrlList.InsertColumn(3,_T("Orientation"));
   m_ctrlList.InsertColumn(4,_T("Loading"));
   m_ctrlList.InsertColumn(5,_T("Start"));
   m_ctrlList.InsertColumn(6,_T("End"));
   m_ctrlList.InsertColumn(7,_T("Ws"));
   m_ctrlList.InsertColumn(8,_T("We"));

   CModelPropertiesDlg* pParent = (CModelPropertiesDlg*)GetParent();

   CString strOrientation[] = {_T("Global"),_T("Member"),_T("GlobalProjected")};
   CString strDirection[] = {_T("X"),_T("Y")};

   int listIdx = 0;
   IndexType nLoadings = pParent->m_pFem2d->GetLoadingCount();
   for ( IndexType idx = 0; idx < nLoadings; idx++ )
   {
      WBFL::FEA2D::Loading* loading = pParent->m_pFem2d->FindLoadingByIndex(idx);

      IndexType nLoads = loading->GetDistributedLoadCount();
      for ( IndexType ldIdx = 0; ldIdx < nLoads; ldIdx++ )
      {
         WBFL::FEA2D::DistributedLoad* load = loading->FindDistributedLoadByIndex(ldIdx);

         IDType ID = load->GetID();

         MemberIDType mbrID = load->GetMemberID();

         WBFL::FEA2D::LoadDirection direction = load->GetDirection();

         WBFL::FEA2D::LoadOrientation orientation = load->GetOrientation();

         LoadCaseIDType loadID = load->GetLoadingID();

         Float64 Start = load->GetStartLocation();
         Float64 End = load->GetEndLocation();

         Float64 Ws = load->GetWStart();
         Float64 We = load->GetWEnd();

         m_ctrlList.InsertItem(listIdx,_T("Load"));

         CString str;
         str.Format(_T("%d"),ID);
         m_ctrlList.SetItemText(listIdx,0,str);

         str.Format(_T("%d"),mbrID);
         m_ctrlList.SetItemText(listIdx,1,str);

         str.Format(_T("%s"),strDirection[static_cast<int>(direction)]);
         m_ctrlList.SetItemText(listIdx,2,str);

         str.Format(_T("%s"),strOrientation[static_cast<int>(orientation)]);
         m_ctrlList.SetItemText(listIdx,3,str);

         str.Format(_T("%d"),loadID);
         m_ctrlList.SetItemText(listIdx,4,str);

         str.Format(_T("%f"),Start);
         m_ctrlList.SetItemText(listIdx,5,str);

         str.Format(_T("%f"),End);
         m_ctrlList.SetItemText(listIdx,6,str);

         str.Format(_T("%f"),Ws);
         m_ctrlList.SetItemText(listIdx,7,str);

         str.Format(_T("%f"),We);
         m_ctrlList.SetItemText(listIdx,8,str);

         listIdx++;
      }
   }

   m_ctrlList.SetColumnWidth(0,LVSCW_AUTOSIZE);
   m_ctrlList.SetColumnWidth(1,LVSCW_AUTOSIZE);
   m_ctrlList.SetColumnWidth(2,LVSCW_AUTOSIZE);
   m_ctrlList.SetColumnWidth(3,LVSCW_AUTOSIZE);
   m_ctrlList.SetColumnWidth(4,LVSCW_AUTOSIZE);
   m_ctrlList.SetColumnWidth(5,LVSCW_AUTOSIZE);
   m_ctrlList.SetColumnWidth(6,LVSCW_AUTOSIZE);
   m_ctrlList.SetColumnWidth(7,LVSCW_AUTOSIZE);
   m_ctrlList.SetColumnWidth(8,LVSCW_AUTOSIZE);

   return TRUE;  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}
