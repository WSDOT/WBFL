// PointLoadListPage.cpp : implementation file
//

#include "stdafx.h"
#include "FEA2D.h"
#include "PointLoadListPage.h"
#include "ModelPropertiesDlg.h"


// CPointLoadListPage dialog

IMPLEMENT_DYNAMIC(CPointLoadListPage, CPropertyPage)

CPointLoadListPage::CPointLoadListPage()
	: CPropertyPage(CPointLoadListPage::IDD)
{

}

CPointLoadListPage::~CPointLoadListPage()
{
}

void CPointLoadListPage::DoDataExchange(CDataExchange* pDX)
{
   CPropertyPage::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_LIST, m_ctrlList);
}


BEGIN_MESSAGE_MAP(CPointLoadListPage, CPropertyPage)
END_MESSAGE_MAP()


// CPointLoadListPage message handlers

BOOL CPointLoadListPage::OnInitDialog()
{
   CPropertyPage::OnInitDialog();

   m_ctrlList.InsertColumn(0,_T("ID"));
   m_ctrlList.InsertColumn(1,_T("Member"));
   m_ctrlList.InsertColumn(2,_T("Location"));
   m_ctrlList.InsertColumn(3,_T("Orientation"));
   m_ctrlList.InsertColumn(4,_T("Loading"));
   m_ctrlList.InsertColumn(5,_T("Fx"));
   m_ctrlList.InsertColumn(6,_T("Fy"));
   m_ctrlList.InsertColumn(7,_T("Mz"));

   CModelPropertiesDlg* pParent = (CModelPropertiesDlg*)GetParent();

   CString strOrientation[] = {_T("Global"),_T("Member"),_T("GlobalProjected")};

   int listIdx = 0;

   IndexType nLoadings = pParent->m_pFem2d->GetLoadingCount();
   for ( IndexType idx = 0; idx < nLoadings; idx++ )
   {
      WBFL::FEA2D::Loading* loading = pParent->m_pFem2d->FindLoadingByIndex(idx);

      IndexType nLoads = loading->GetPointLoadCount();
      for ( IndexType ldIdx = 0; ldIdx < nLoads; ldIdx++ )
      {
         WBFL::FEA2D::PointLoad* load = loading->FindPointLoadByIndex(ldIdx);

         IDType ID = load->GetID();

         MemberIDType mbrID = load->GetMemberID();

         Float64 location = load->GetLocation();

         WBFL::FEA2D::LoadOrientation orientation = load->GetOrientation();

         LoadCaseIDType loadID = load->GetLoadingID();

         Float64 fx,fy,mz;
         load->GetForce(&fx,&fy,&mz);

         m_ctrlList.InsertItem(listIdx,_T("Load"));

         CString str;
         str.Format(_T("%d"),ID);
         m_ctrlList.SetItemText(listIdx,0,str);

         str.Format(_T("%d"),mbrID);
         m_ctrlList.SetItemText(listIdx,1,str);

         str.Format(_T("%f"),location);
         m_ctrlList.SetItemText(listIdx,2,str);

         str.Format(_T("%s"),strOrientation[static_cast<int>(orientation)]);
         m_ctrlList.SetItemText(listIdx,3,str);

         str.Format(_T("%d"),loadID);
         m_ctrlList.SetItemText(listIdx,4,str);

         str.Format(_T("%f"),fx);
         m_ctrlList.SetItemText(listIdx,5,str);

         str.Format(_T("%f"),fy);
         m_ctrlList.SetItemText(listIdx,6,str);

         str.Format(_T("%f"),mz);
         m_ctrlList.SetItemText(listIdx,7,str);

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

   return TRUE;  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}
