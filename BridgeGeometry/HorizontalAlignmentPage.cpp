// HorizontalAlignmentPage.cpp : implementation file
//

#include "stdafx.h"
#include "BridgeGeometry.h"
#include "HorizontalAlignmentPage.h"

#include <MfcTools\CogoDDX.h>

// CHorizontalAlignmentPage dialog

IMPLEMENT_DYNAMIC(CHorizontalAlignmentPage, CPropertyPage)

CHorizontalAlignmentPage::CHorizontalAlignmentPage()
	: CPropertyPage(CHorizontalAlignmentPage::IDD)
{
   m_DirFormatter.CoCreateInstance(CLSID_DirectionDisplayUnitFormatter);
   m_DirFormatter->put_CondensedFormat(VARIANT_TRUE);
   m_DirFormatter->put_BearingFormat(VARIANT_TRUE);
}

CHorizontalAlignmentPage::~CHorizontalAlignmentPage()
{
}

void CHorizontalAlignmentPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);

   CComPtr<IDirection> direction;
   direction.CoCreateInstance(CLSID_Direction);


   if ( pDX->m_bSaveAndValidate )
   {
      DDX_Direction(pDX,IDC_INITIAL_DIRECTION,direction,m_DirFormatter);
      direction->get_Value(&m_Direction);
   }
   else
   {
      direction->put_Value(m_Direction);
      DDX_Direction(pDX,IDC_INITIAL_DIRECTION,direction,m_DirFormatter);
   }
}


BEGIN_MESSAGE_MAP(CHorizontalAlignmentPage, CPropertyPage)
END_MESSAGE_MAP()


// CHorizontalAlignmentPage message handlers

BOOL CHorizontalAlignmentPage::OnInitDialog()
{
   CPropertyPage::OnInitDialog();

   // TODO:  Add extra initialization here

   return TRUE;  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}
