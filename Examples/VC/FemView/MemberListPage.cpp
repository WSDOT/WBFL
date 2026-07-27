// MemberListPage.cpp : implementation file
//

#include "stdafx.h"
#include "FEA2D.h"
#include "MemberListPage.h"
#include "ModelPropertiesDlg.h"

// MemberListPage dialog

IMPLEMENT_DYNAMIC(CMemberListPage, CPropertyPage)

CMemberListPage::CMemberListPage()
	: CPropertyPage(CMemberListPage::IDD)
{

}

CMemberListPage::~CMemberListPage()
{
}

void CMemberListPage::DoDataExchange(CDataExchange* pDX)
{
   CPropertyPage::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_LIST, m_ctrlList);
}


BEGIN_MESSAGE_MAP(CMemberListPage, CPropertyPage)
END_MESSAGE_MAP()


// MemberListPage message handlers

BOOL CMemberListPage::OnInitDialog()
{
   CPropertyPage::OnInitDialog();

   m_ctrlList.InsertColumn(0,_T("Member"));
   m_ctrlList.InsertColumn(1,_T("Start"));
   m_ctrlList.InsertColumn(2,_T("End"));
   m_ctrlList.InsertColumn(3,_T("Length"));
   m_ctrlList.InsertColumn(4,_T("RS"));
   m_ctrlList.InsertColumn(5,_T("RE"));
   m_ctrlList.InsertColumn(6,_T("EA"));
   m_ctrlList.InsertColumn(7,_T("EI"));

   CModelPropertiesDlg* pParent = (CModelPropertiesDlg*)GetParent();
   IndexType nMembers = pParent->m_pFem2d->GetMemberCount();
   for ( IndexType mbrIdx = 0; mbrIdx < nMembers; mbrIdx++ )
   {
      WBFL::FEA2D::Member* mbr = pParent->m_pFem2d->FindMemberByIndex(mbrIdx);

      MemberIDType ID = mbr->GetID();

      JointIDType startID = mbr->GetStartJoint();
      JointIDType endID = mbr->GetEndJoint();

      Float64 length = mbr->GetLength();

      bool bStartReleaseFx = mbr->IsReleased(WBFL::FEA2D::MemberEndType::Start,WBFL::FEA2D::MemberReleaseType::Fx);
      bool bEndReleaseFx   = mbr->IsReleased(WBFL::FEA2D::MemberEndType::End,  WBFL::FEA2D::MemberReleaseType::Fx);

      bool bStartReleaseMz = mbr->IsReleased(WBFL::FEA2D::MemberEndType::Start,WBFL::FEA2D::MemberReleaseType::Mz);
      bool bEndReleaseMz   = mbr->IsReleased(WBFL::FEA2D::MemberEndType::End,  WBFL::FEA2D::MemberReleaseType::Mz);

      Float64 EA = mbr->GetEA();
      Float64 EI = mbr->GetEI();

      m_ctrlList.InsertItem((int)mbrIdx,_T("Member"));
      CString str;
      str.Format(_T("%d"),ID);
      m_ctrlList.SetItemText((int)mbrIdx,0,str);

      str.Format(_T("%d"),startID);
      m_ctrlList.SetItemText((int)mbrIdx,1,str);

      str.Format(_T("%d"),endID);
      m_ctrlList.SetItemText((int)mbrIdx,2,str);

      str.Format(_T("%f"),length);
      m_ctrlList.SetItemText((int)mbrIdx,3,str);

      str.Format(_T("%s%s"),bStartReleaseFx ? _T("Fx") : _T(""),bStartReleaseMz ? _T("Mz") : _T(""));
      m_ctrlList.SetItemText((int)mbrIdx,4,str);

      str.Format(_T("%s%s"),bEndReleaseFx ? _T("Fx") : _T(""),bEndReleaseMz ? _T("Mz") : _T(""));
      m_ctrlList.SetItemText((int)mbrIdx,5,str);

      str.Format(_T("%f"),EA);
      m_ctrlList.SetItemText((int)mbrIdx,6,str);

      str.Format(_T("%f"),EI);
      m_ctrlList.SetItemText((int)mbrIdx,7,str);
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
