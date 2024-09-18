///////////////////////////////////////////////////////////////////////
// MfcTools - Extension library for MFC
// Copyright © 1999-2024  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the Alternate Route Library Open Source License as published by 
// the Washington State Department of Transportation, Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but is distributed 
// AS IS, WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See the Alternate Route Library Open Source 
// License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License 
// along with this program; if not, write to the Washington State Department of 
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <MfcTools\RebarMaterialComboBox.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void DDX_RebarMaterial(CDataExchange* pDX,UINT nIDC,WBFL::Materials::Rebar::Type& type,WBFL::Materials::Rebar::Grade& grade)
{
   HWND hWndCtrl = pDX->PrepareCtrl(nIDC);

   CRebarMaterialComboBox* pCB = (CRebarMaterialComboBox*)pDX->m_pDlgWnd->GetDlgItem(nIDC);
   if ( pDX->m_bSaveAndValidate )
   {
      pCB->GetMaterial(&type,&grade);
   }
   else
   {
      pCB->SetMaterial(type,grade);
   }
}


/////////////////////////////////////////////////////////////////////////////
// CRebarMaterialComboBox

CRebarMaterialComboBox::CRebarMaterialComboBox()
{
}

CRebarMaterialComboBox::~CRebarMaterialComboBox()
{
}

IMPLEMENT_DYNAMIC(CRebarMaterialComboBox, CComboBox)

BEGIN_MESSAGE_MAP(CRebarMaterialComboBox, CComboBox)
    //{{AFX_MSG_MAP(CRebarMaterialComboBox)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CRebarMaterialComboBox::Initialize(bool bFilterBySpec)
{
   ResetContent();

   AddString( WBFL::LRFD::RebarPool::GetMaterialName(WBFL::Materials::Rebar::Type::A615,  WBFL::Materials::Rebar::Grade::Grade40).c_str()  );
   AddString( WBFL::LRFD::RebarPool::GetMaterialName(WBFL::Materials::Rebar::Type::A615,  WBFL::Materials::Rebar::Grade::Grade60).c_str()  );

   if (bFilterBySpec && WBFL::LRFD::BDSManager::Edition::ThirdEditionWith2005Interims <= WBFL::LRFD::BDSManager::GetEdition())
   {
      AddString(WBFL::LRFD::RebarPool::GetMaterialName(WBFL::Materials::Rebar::Type::A615, WBFL::Materials::Rebar::Grade::Grade75).c_str());
      AddString(WBFL::LRFD::RebarPool::GetMaterialName(WBFL::Materials::Rebar::Type::A615, WBFL::Materials::Rebar::Grade::Grade80).c_str());
   }

   AddString( WBFL::LRFD::RebarPool::GetMaterialName(WBFL::Materials::Rebar::Type::A706,  WBFL::Materials::Rebar::Grade::Grade60).c_str()  );
   
   if (bFilterBySpec && WBFL::LRFD::BDSManager::Edition::ThirdEditionWith2005Interims <= WBFL::LRFD::BDSManager::GetEdition())
   {
      AddString(WBFL::LRFD::RebarPool::GetMaterialName(WBFL::Materials::Rebar::Type::A706, WBFL::Materials::Rebar::Grade::Grade80).c_str());
   }

   if ( bFilterBySpec && WBFL::LRFD::BDSManager::Edition::SixthEditionWith2013Interims <= WBFL::LRFD::BDSManager::GetEdition() )
   {
      AddString(WBFL::LRFD::RebarPool::GetMaterialName(WBFL::Materials::Rebar::Type::A1035, WBFL::Materials::Rebar::Grade::Grade100).c_str() );
   }
}

void CRebarMaterialComboBox::GetMaterial(WBFL::Materials::Rebar::Type* pType,WBFL::Materials::Rebar::Grade* pGrade)
{
   int curSel = GetCurSel();
      switch(curSel)
      {
      case 0:  *pType = WBFL::Materials::Rebar::Type::A615;  *pGrade = WBFL::Materials::Rebar::Grade::Grade40;  break;
      case 1:  *pType = WBFL::Materials::Rebar::Type::A615;  *pGrade = WBFL::Materials::Rebar::Grade::Grade60;  break;
      case 2:  *pType = WBFL::Materials::Rebar::Type::A615;  *pGrade = WBFL::Materials::Rebar::Grade::Grade75;  break;
      case 3:  *pType = WBFL::Materials::Rebar::Type::A615;  *pGrade = WBFL::Materials::Rebar::Grade::Grade80;  break;
      case 4:  *pType = WBFL::Materials::Rebar::Type::A706;  *pGrade = WBFL::Materials::Rebar::Grade::Grade60;  break;
      case 5:  *pType = WBFL::Materials::Rebar::Type::A706;  *pGrade = WBFL::Materials::Rebar::Grade::Grade80;  break;
      case 6:  *pType = WBFL::Materials::Rebar::Type::A1035; *pGrade = WBFL::Materials::Rebar::Grade::Grade100; break;
      default:
         ATLASSERT(false); // should never get here
      }
}

void CRebarMaterialComboBox::SetMaterial(WBFL::Materials::Rebar::Type type,WBFL::Materials::Rebar::Grade grade)
{
   int curSel = CB_ERR;
   if ( type == WBFL::Materials::Rebar::Type::A615 )
   {
      if ( grade == WBFL::Materials::Rebar::Grade::Grade40 )
         curSel = 0;
      else if ( grade == WBFL::Materials::Rebar::Grade::Grade60 )
         curSel = 1;
      else if ( grade == WBFL::Materials::Rebar::Grade::Grade75 )
         curSel = 2;
      else if ( grade == WBFL::Materials::Rebar::Grade::Grade80 )
         curSel = 3;
#if defined _DEBUG
      else
         ATLASSERT(false); // should never get here
#endif
   }
   else if ( type == WBFL::Materials::Rebar::Type::A706 )
   {
      if ( grade == WBFL::Materials::Rebar::Grade::Grade60 )
         curSel = 4;
      else if ( grade == WBFL::Materials::Rebar::Grade::Grade80 )
         curSel = 5;
#if defined _DEBUG
      else
         ATLASSERT(false); // should never get here
#endif
   }
   else if ( type == WBFL::Materials::Rebar::Type::A1035 )
   {
      if ( grade == WBFL::Materials::Rebar::Grade::Grade100 )
         curSel = 6;
#if defined _DEBUG
      else
         ATLASSERT(false); // should never get here
#endif
   }
   else
   {
      ATLASSERT(false); // should never get here
      curSel = CB_ERR;
   }

   SetCurSel(curSel);
}



/////////////////////////////////////////////////////////////////////////////
// CRebarMaterialComboBox message handlers
void CRebarMaterialComboBox::PreSubclassWindow()
{
   CComboBox::PreSubclassWindow();
   ATLASSERT( !(GetStyle() & CBS_SORT) ); // make sure sort style is turned off
   Initialize();
}
