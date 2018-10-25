// ResultsListPage.cpp : implementation file
//

#include "stdafx.h"
#include "FEA2D.h"
#include "ResultsListPage.h"
#include "ModelPropertiesDlg.h"


// ResultsListPage dialog

IMPLEMENT_DYNAMIC(CResultsListPage, CPropertyPage)

CResultsListPage::CResultsListPage()
	: CPropertyPage(CResultsListPage::IDD)
{

}

CResultsListPage::~CResultsListPage()
{
}

void CResultsListPage::DoDataExchange(CDataExchange* pDX)
{
   CPropertyPage::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_LIST, m_ctrlList);
}


BEGIN_MESSAGE_MAP(CResultsListPage, CPropertyPage)
   ON_CBN_SELCHANGE(IDC_LOADING,OnLoadingChanged)
END_MESSAGE_MAP()


// CPoiListPage message handlers

BOOL CResultsListPage::OnInitDialog()
{
   CPropertyPage::OnInitDialog();

   // Prepare the column headers
   int col = 0;
   m_ctrlList.InsertColumn(col++,_T("Mbr"));
   m_ctrlList.InsertColumn(col++,_T("Fx"));
   m_ctrlList.InsertColumn(col++,_T("Fy"));
   m_ctrlList.InsertColumn(col++,_T("Mz"));
   m_ctrlList.InsertColumn(col++,_T("Fx"));
   m_ctrlList.InsertColumn(col++,_T("Fy"));
   m_ctrlList.InsertColumn(col++,_T("Mz"));
   m_ctrlList.InsertColumn(col++,_T("DyS"));
   m_ctrlList.InsertColumn(col++,_T("DyE"));

   CModelPropertiesDlg* pParent = (CModelPropertiesDlg*)GetParent();

   CComboBox* pcbLoadings = (CComboBox*)GetDlgItem(IDC_LOADING);
   CComPtr<IFem2dLoadingCollection> loadings;
   pParent->m_pFem2d->get_Loadings(&loadings);
   IndexType nLoadings;
   loadings->get_Count(&nLoadings);
   for ( IndexType loadingIdx = 0; loadingIdx < nLoadings; loadingIdx++ )
   {
      CComPtr<IFem2dLoading> loading;
      loadings->get_Item(loadingIdx,&loading);
      LoadCaseIDType id;
      loading->get_ID(&id);
      CString strID;
      strID.Format(_T("%d"),id);
      int idx = pcbLoadings->AddString(strID);
      pcbLoadings->SetItemData(idx,id);
   }

   return TRUE;  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}

void CResultsListPage::OnLoadingChanged()
{
   m_ctrlList.DeleteAllItems();

   CComboBox* pcbLoading = (CComboBox*)GetDlgItem(IDC_LOADING);
   int curSel = pcbLoading->GetCurSel();
   LoadCaseIDType lcid = (LoadCaseIDType)(pcbLoading->GetItemData(curSel));

   CModelPropertiesDlg* pParent = (CModelPropertiesDlg*)GetParent();
   CComQIPtr<IFem2dModelResults> results(pParent->m_pFem2d);

   CComPtr<IFem2dMemberCollection> members;
   pParent->m_pFem2d->get_Members(&members);

   IndexType nMembers;
   members->get_Count(&nMembers);
   for ( IndexType mbrIdx = 0; mbrIdx < nMembers; mbrIdx++ )
   {
      CComPtr<IFem2dMember> member;
      members->get_Item(mbrIdx,&member);
      MemberIDType mbrID;
      member->get_ID(&mbrID);

      Float64 FxStart,FyStart,MzStart;
      Float64 FxEnd,  FyEnd,  MzEnd;
      results->ComputeMemberForces(lcid,mbrID,&FxStart,&FyStart,&MzStart,&FxEnd,&FyEnd,&MzEnd);

      int col = 0;

      m_ctrlList.InsertItem((int)mbrIdx,_T("Member"));
      CString str;
      str.Format(_T("%d"),mbrID);
      m_ctrlList.SetItemText((int)mbrIdx,col++,str);
      
      str.Format(_T("%f"),FxStart);
      m_ctrlList.SetItemText((int)mbrIdx,col++,str);
      
      str.Format(_T("%f"),FyStart);
      m_ctrlList.SetItemText((int)mbrIdx,col++,str);
      
      str.Format(_T("%f"),MzStart);
      m_ctrlList.SetItemText((int)mbrIdx,col++,str);
      
      str.Format(_T("%f"),FxEnd);
      m_ctrlList.SetItemText((int)mbrIdx,col++,str);
      
      str.Format(_T("%f"),FyEnd);
      m_ctrlList.SetItemText((int)mbrIdx,col++,str);
      
      str.Format(_T("%f"),MzEnd);
      m_ctrlList.SetItemText((int)mbrIdx,col++,str);

      results->ComputeMemberDeflections(lcid,mbrID,&FxStart,&FyStart,&MzStart,&FxEnd,&FyEnd,&MzEnd);
      str.Format(_T("%f"),FyStart);
      m_ctrlList.SetItemText((int)mbrIdx,col++,str);
      str.Format(_T("%f"),FyEnd);
      m_ctrlList.SetItemText((int)mbrIdx,col++,str);

   }

   int nColumns = m_ctrlList.GetHeaderCtrl()->GetItemCount();
   for ( int col = 0; col < nColumns; col++ )
   {
      m_ctrlList.SetColumnWidth(col,LVSCW_AUTOSIZE);
   }
}
