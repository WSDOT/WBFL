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
   CComPtr<IFem2dLoadingCollection> loadings;
   pParent->m_pFem2d->get_Loadings(&loadings);

   CString strOrientation[] = {_T("Global"),_T("Member"),_T("GlobalProjected")};
   CString strDirection[] = {_T("X"),_T("Y")};

   int listIdx = 0;
   CollectionIndexType nLoadings;
   loadings->get_Count(&nLoadings);
   for ( CollectionIndexType idx = 0; idx < nLoadings; idx++ )
   {
      CComPtr<IFem2dLoading> loading;
      loadings->get_Item(idx,&loading);

      CComPtr<IFem2dDistributedLoadCollection> loads;
      loading->get_DistributedLoads(&loads);
      CollectionIndexType nLoads;
      loads->get_Count(&nLoads);
      for ( CollectionIndexType ldIdx = 0; ldIdx < nLoads; ldIdx++ )
      {
         CComPtr<IFem2dDistributedLoad> load;
         loads->get_Item(ldIdx,&load);

         IDType ID;
         load->get_ID(&ID);

         MemberIDType mbrID;
         load->get_MemberID(&mbrID);

         Fem2dLoadDirection direction;
         load->get_Direction(&direction);

         Fem2dLoadOrientation orientation;
         load->get_Orientation(&orientation);

         LoadCaseIDType loadID;
         load->get_Loading(&loadID);

         Float64 Start,End;
         load->get_StartLocation(&Start);
         load->get_EndLocation(&End);

         Float64 Ws, We;
         load->get_WStart(&Ws);
         load->get_WEnd(&We);

         m_ctrlList.InsertItem(listIdx,_T("Load"));

         CString str;
         str.Format(_T("%d"),ID);
         m_ctrlList.SetItemText(listIdx,0,str);

         str.Format(_T("%d"),mbrID);
         m_ctrlList.SetItemText(listIdx,1,str);

         str.Format(_T("%s"),strDirection[direction]);
         m_ctrlList.SetItemText(listIdx,2,str);

         str.Format(_T("%s"),strOrientation[orientation]);
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
