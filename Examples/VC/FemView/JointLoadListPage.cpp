// JointLoadListPage.cpp : implementation file
//

#include "stdafx.h"
#include "FEA2D.h"
#include "JointLoadListPage.h"
#include "ModelPropertiesDlg.h"


// CJointLoadListPage dialog

IMPLEMENT_DYNAMIC(CJointLoadListPage, CPropertyPage)

CJointLoadListPage::CJointLoadListPage()
	: CPropertyPage(CJointLoadListPage::IDD)
{

}

CJointLoadListPage::~CJointLoadListPage()
{
}

void CJointLoadListPage::DoDataExchange(CDataExchange* pDX)
{
   CPropertyPage::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_LIST, m_ctrlList);
}


BEGIN_MESSAGE_MAP(CJointLoadListPage, CPropertyPage)
END_MESSAGE_MAP()


// CJointLoadListPage message handlers

BOOL CJointLoadListPage::OnInitDialog()
{
   CPropertyPage::OnInitDialog();

   m_ctrlList.InsertColumn(0,_T("ID"));
   m_ctrlList.InsertColumn(1,_T("Joint"));
   m_ctrlList.InsertColumn(2,_T("Loading"));
   m_ctrlList.InsertColumn(3,_T("Fx"));
   m_ctrlList.InsertColumn(4,_T("Fy"));
   m_ctrlList.InsertColumn(5,_T("Mz"));

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

      CComPtr<IFem2dJointLoadCollection> loads;
      loading->get_JointLoads(&loads);
      IndexType nLoads;
      loads->get_Count(&nLoads);
      for ( IndexType ldIdx = 0; ldIdx < nLoads; ldIdx++ )
      {
         CComPtr<IFem2dJointLoad> load;
         loads->get_Item(ldIdx,&load);

         IDType ID;
         load->get_ID(&ID);

         JointIDType jntID;
         load->get_JointID(&jntID);

         LoadCaseIDType loadID;
         load->get_Loading(&loadID);

         Float64 fx,fy,mz;
         load->GetForce(&fx,&fy,&mz);

         m_ctrlList.InsertItem(listIdx,_T("Load"));

         CString str;
         str.Format(_T("%d"),ID);
         m_ctrlList.SetItemText(listIdx,0,str);

         str.Format(_T("%d"),jntID);
         m_ctrlList.SetItemText(listIdx,1,str);

         str.Format(_T("%d"),loadID);
         m_ctrlList.SetItemText(listIdx,2,str);

         str.Format(_T("%f"),fx);
         m_ctrlList.SetItemText(listIdx,3,str);

         str.Format(_T("%f"),fy);
         m_ctrlList.SetItemText(listIdx,4,str);

         str.Format(_T("%f"),mz);
         m_ctrlList.SetItemText(listIdx,5,str);

         listIdx++;
      }
   }

   m_ctrlList.SetColumnWidth(0,LVSCW_AUTOSIZE);
   m_ctrlList.SetColumnWidth(1,LVSCW_AUTOSIZE);
   m_ctrlList.SetColumnWidth(2,LVSCW_AUTOSIZE);
   m_ctrlList.SetColumnWidth(3,LVSCW_AUTOSIZE);
   m_ctrlList.SetColumnWidth(4,LVSCW_AUTOSIZE);
   m_ctrlList.SetColumnWidth(5,LVSCW_AUTOSIZE);

   return TRUE;  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}
