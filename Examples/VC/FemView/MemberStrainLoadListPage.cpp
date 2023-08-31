// MemberStrainListPage.cpp : implementation file
//

#include "stdafx.h"
#include "FEA2D.h"
#include "MemberStrainLoadListPage.h"
#include "ModelPropertiesDlg.h"


// CMemberStrainLoadListPage dialog

IMPLEMENT_DYNAMIC(CMemberStrainLoadListPage, CPropertyPage)

CMemberStrainLoadListPage::CMemberStrainLoadListPage()
	: CPropertyPage(CMemberStrainLoadListPage::IDD)
{

}

CMemberStrainLoadListPage::~CMemberStrainLoadListPage()
{
}

void CMemberStrainLoadListPage::DoDataExchange(CDataExchange* pDX)
{
   CPropertyPage::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_LIST, m_ctrlList);
}


BEGIN_MESSAGE_MAP(CMemberStrainLoadListPage, CPropertyPage)
END_MESSAGE_MAP()


// CMemberStrainLoadListPage message handlers

BOOL CMemberStrainLoadListPage::OnInitDialog()
{
   CPropertyPage::OnInitDialog();


   m_ctrlList.InsertColumn(0,_T("ID"));
   m_ctrlList.InsertColumn(1,_T("Member"));
   m_ctrlList.InsertColumn(2,_T("Loading"));
   m_ctrlList.InsertColumn(3,_T("Start"));
   m_ctrlList.InsertColumn(4,_T("End"));
   m_ctrlList.InsertColumn(5,_T("e*10^6"));
   m_ctrlList.InsertColumn(6,_T("r*10^6"));

   CModelPropertiesDlg* pParent = (CModelPropertiesDlg*)GetParent();
   CComPtr<IFem2dLoadingCollection> loadings;
   pParent->m_pFem2d->get_Loadings(&loadings);

   int listIdx = 0;
   IndexType nLoadings;
   loadings->get_Count(&nLoadings);
   for ( IndexType idx = 0; idx < nLoadings; idx++ )
   {
      CComPtr<IFem2dLoading> loading;
      loadings->get_Item(idx,&loading);

      CComPtr<IFem2dMemberStrainCollection> loads;
      loading->get_MemberStrains(&loads);
      IndexType nLoads;
      loads->get_Count(&nLoads);
      for ( IndexType ldIdx = 0; ldIdx < nLoads; ldIdx++ )
      {
         CComPtr<IFem2dMemberStrain> load;
         loads->get_Item(ldIdx,&load);

         IDType ID;
         load->get_ID(&ID);

         MemberIDType mbrID;
         load->get_MemberID(&mbrID);

         LoadCaseIDType loadID;
         load->get_Loading(&loadID);

         Float64 Start,End;
         load->get_StartLocation(&Start);
         load->get_EndLocation(&End);

         Float64 axial,curvature;
         load->get_AxialStrain(&axial);
         load->get_CurvatureStrain(&curvature);

         m_ctrlList.InsertItem(listIdx,_T("Load"));

         CString str;
         str.Format(_T("%d"),ID);
         m_ctrlList.SetItemText(listIdx,0,str);

         str.Format(_T("%d"),mbrID);
         m_ctrlList.SetItemText(listIdx,1,str);

         str.Format(_T("%d"),loadID);
         m_ctrlList.SetItemText(listIdx,2,str);

         str.Format(_T("%f"),Start);
         m_ctrlList.SetItemText(listIdx,3,str);

         str.Format(_T("%f"),End);
         m_ctrlList.SetItemText(listIdx,4,str);

         str.Format(_T("%f"),1e6*axial);
         m_ctrlList.SetItemText(listIdx,5,str);

         str.Format(_T("%f"),1e6*curvature);
         m_ctrlList.SetItemText(listIdx,6,str);

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

   return TRUE;  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}
