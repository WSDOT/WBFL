// JointListPage.cpp : implementation file
//

#include "stdafx.h"
#include "FEA2D.h"
#include "PoiListPage.h"
#include "ModelPropertiesDlg.h"


// CPoiListPage dialog

IMPLEMENT_DYNAMIC(CPoiListPage, CPropertyPage)

CPoiListPage::CPoiListPage()
	: CPropertyPage(CPoiListPage::IDD)
{

}

CPoiListPage::~CPoiListPage()
{
}

void CPoiListPage::DoDataExchange(CDataExchange* pDX)
{
   CPropertyPage::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_LIST, m_ctrlList);
}


BEGIN_MESSAGE_MAP(CPoiListPage, CPropertyPage)
END_MESSAGE_MAP()


// CPoiListPage message handlers

BOOL CPoiListPage::OnInitDialog()
{
   CPropertyPage::OnInitDialog();

   // Prepare the column headers
   m_ctrlList.InsertColumn(0,_T("POI"));
   m_ctrlList.InsertColumn(1,_T("Mbr"));
   m_ctrlList.InsertColumn(2,_T("Location"));

   CModelPropertiesDlg* pParent = (CModelPropertiesDlg*)GetParent();

   CComPtr<IFem2dPOICollection> POIs;
   pParent->m_pFem2d->get_POIs(&POIs);

   IndexType nPoi;
   POIs->get_Count(&nPoi);
   for ( IndexType poiIdx = 0; poiIdx < nPoi; poiIdx++ )
   {
      CComPtr<IFem2dPOI> poi;
      POIs->get_Item(poiIdx,&poi);

      PoiIDType ID;
      poi->get_ID(&ID);

      MemberIDType mbrID;
      poi->get_MemberID(&mbrID);

      Float64 location;
      poi->get_Location(&location);

      m_ctrlList.InsertItem((int)poiIdx,_T("POI"));
      CString str;
      str.Format(_T("%d"),ID);
      m_ctrlList.SetItemText((int)poiIdx,0,str);
      str.Format(_T("%d"),mbrID);
      m_ctrlList.SetItemText((int)poiIdx,1,str);
      str.Format(_T("%f"),location);
      m_ctrlList.SetItemText((int)poiIdx,2,str);
   }


   m_ctrlList.SetColumnWidth(0,LVSCW_AUTOSIZE);
   m_ctrlList.SetColumnWidth(1,LVSCW_AUTOSIZE);
   m_ctrlList.SetColumnWidth(2,LVSCW_AUTOSIZE);

   return TRUE;  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}
