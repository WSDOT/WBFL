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
   m_ctrlList.InsertColumn(0,_T("POI"));
   m_ctrlList.InsertColumn(1,_T("Fx"));
   m_ctrlList.InsertColumn(2,_T("Fy"));
   m_ctrlList.InsertColumn(3,_T("Mz"));
   m_ctrlList.InsertColumn(4,_T("Dx"));
   m_ctrlList.InsertColumn(5,_T("Dy"));
   m_ctrlList.InsertColumn(6,_T("Rz"));

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

   CComPtr<IFem2dPOICollection> POIs;
   pParent->m_pFem2d->get_POIs(&POIs);

   CollectionIndexType nPoi;
   POIs->get_Count(&nPoi);
   for ( CollectionIndexType poiIdx = 0; poiIdx < nPoi; poiIdx++ )
   {
      CComPtr<IFem2dPOI> poi;
      POIs->get_Item(poiIdx,&poi);

      PoiIDType poiID;
      poi->get_ID(&poiID);

      Float64 Fx,Fy,Mz;
      results->ComputePOIForces(lcid,poiID, mftRight,lotMember,&Fx,&Fy,&Mz);

      Float64 Dx,Dy,Rz;
      results->ComputePOIDeflections(lcid,poiID,lotMember,&Dx,&Dy,&Rz);

      m_ctrlList.InsertItem((int)poiIdx,_T("POI"));
      CString str;
      str.Format(_T("%d"),poiID);
      m_ctrlList.SetItemText((int)poiIdx,0,str);
      
      str.Format(_T("%f"),Fx);
      m_ctrlList.SetItemText((int)poiIdx,1,str);
      
      str.Format(_T("%f"),Fy);
      m_ctrlList.SetItemText((int)poiIdx,2,str);
      
      str.Format(_T("%f"),Mz);
      m_ctrlList.SetItemText((int)poiIdx,3,str);
      
      str.Format(_T("%f"),Dx);
      m_ctrlList.SetItemText((int)poiIdx,4,str);
      
      str.Format(_T("%f"),Dy);
      m_ctrlList.SetItemText((int)poiIdx,5,str);
      
      str.Format(_T("%f"),Rz);
      m_ctrlList.SetItemText((int)poiIdx,6,str);
   }


   m_ctrlList.SetColumnWidth(0,LVSCW_AUTOSIZE);
   m_ctrlList.SetColumnWidth(1,LVSCW_AUTOSIZE);
   m_ctrlList.SetColumnWidth(2,LVSCW_AUTOSIZE);
   m_ctrlList.SetColumnWidth(3,LVSCW_AUTOSIZE);
   m_ctrlList.SetColumnWidth(4,LVSCW_AUTOSIZE);
   m_ctrlList.SetColumnWidth(5,LVSCW_AUTOSIZE);
   m_ctrlList.SetColumnWidth(6,LVSCW_AUTOSIZE);
}
