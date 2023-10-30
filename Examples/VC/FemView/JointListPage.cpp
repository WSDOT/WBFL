// JointListPage.cpp : implementation file
//

#include "stdafx.h"
#include "FEA2D.h"
#include "JointListPage.h"
#include "ModelPropertiesDlg.h"


// CJointListPage dialog

IMPLEMENT_DYNAMIC(CJointListPage, CPropertyPage)

CJointListPage::CJointListPage()
	: CPropertyPage(CJointListPage::IDD)
{

}

CJointListPage::~CJointListPage()
{
}

void CJointListPage::DoDataExchange(CDataExchange* pDX)
{
   CPropertyPage::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_LIST, m_ctrlList);
}


BEGIN_MESSAGE_MAP(CJointListPage, CPropertyPage)
END_MESSAGE_MAP()


// CJointListPage message handlers

BOOL CJointListPage::OnInitDialog()
{
   CPropertyPage::OnInitDialog();

   // Prepare the column headers
   m_ctrlList.InsertColumn(0,_T("Joint"));
   m_ctrlList.InsertColumn(1,_T("X"));
   m_ctrlList.InsertColumn(2,_T("Y"));
   m_ctrlList.InsertColumn(3,_T("SX"));
   m_ctrlList.InsertColumn(4,_T("SY"));
   m_ctrlList.InsertColumn(5,_T("SZ"));

   CModelPropertiesDlg* pParent = (CModelPropertiesDlg*)GetParent();

   CComPtr<IFem2dJointCollection> joints;
   pParent->m_pFem2d->get_Joints(&joints);

   IndexType nJoints;
   joints->get_Count(&nJoints);
   for ( IndexType jntIdx = 0; jntIdx < nJoints; jntIdx++ )
   {
      CComPtr<IFem2dJoint> joint;
      joints->get_Item(jntIdx,&joint);

      JointIDType ID;
      joint->get_ID(&ID);

      Float64 x,y;
      joint->get_X(&x);
      joint->get_Y(&y);

      VARIANT_BOOL bSupportedFx, bSupportedFy, bSupportedMz;
      joint->IsDofSupported(jrtFx,&bSupportedFx);
      joint->IsDofSupported(jrtFy,&bSupportedFy);
      joint->IsDofSupported(jrtMz,&bSupportedMz);

      m_ctrlList.InsertItem((int)jntIdx,_T("Joint"));
      CString str;
      str.Format(_T("%d"),ID);
      m_ctrlList.SetItemText((int)jntIdx,0,str);
      str.Format(_T("%f"),x);
      m_ctrlList.SetItemText((int)jntIdx,1,str);
      str.Format(_T("%f"),y);
      m_ctrlList.SetItemText((int)jntIdx,2,str);

      str.Format(_T("%s"),bSupportedFx == VARIANT_TRUE ? _T("x") : _T(""));
      m_ctrlList.SetItemText((int)jntIdx,3,str);

      str.Format(_T("%s"),bSupportedFy == VARIANT_TRUE ? _T("x") : _T(""));
      m_ctrlList.SetItemText((int)jntIdx,4,str);

      str.Format(_T("%s"),bSupportedMz == VARIANT_TRUE ? _T("x") : _T(""));
      m_ctrlList.SetItemText((int)jntIdx,5,str);
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
