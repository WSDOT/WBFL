///////////////////////////////////////////////////////////////////////
// MfcTools - Extension library for MFC
// Copyright © 1999-2023  Washington State Department of Transportation
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
#include "resource.h"
#include <MfcTools\ModifyButton.h>
#include <MfcTools\ddxfolder.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


BEGIN_MESSAGE_MAP(CModifyButton, CButton)
  //{{AFX_MSG_MAP(CModifyButton)
  ON_CONTROL_REFLECT_EX(BN_CLICKED, OnClicked)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()
        
CModifyButton::CModifyButton()
{
  m_pBuddy = nullptr;
  m_bFirstCall = TRUE;
}

void CModifyButton::SetBuddy(IGetEdit* pBuddy)
{
  m_pBuddy = pBuddy;
}

BOOL CModifyButton::PreTranslateMessage(MSG* pMsg) 
{                     
  //create the tooltip
  if (m_bFirstCall)
  {
    m_ToolTip.Create(this);
    m_ToolTip.Activate(TRUE);
    m_ToolTip.AddTool(this, IDS_DDXFOLDER_TT_MODIFY);
    m_bFirstCall = FALSE;
  }
  
  //give the tooltip a chance to handle the message
  m_ToolTip.RelayEvent(pMsg);

  return CButton::PreTranslateMessage(pMsg);
}

BOOL CModifyButton::OnClicked() 
{
  if (m_pBuddy)
    m_pBuddy->Edit();
  else
    TRACE(_T("CModifyButton: No auto buddy defined\n"));

  return FALSE;
}                        

