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
#include <MfcTools\CacheEdit.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCacheEdit

CCacheEdit::CCacheEdit() :
m_strDefault(_T("")),
m_strCache(_T("")),
m_DefaultValue(0.0),
m_bShowDefault(FALSE)
{
}

CCacheEdit::~CCacheEdit()
{
}

IMPLEMENT_DYNAMIC(CCacheEdit, CEdit)

BEGIN_MESSAGE_MAP(CCacheEdit, CEdit)
    //{{AFX_MSG_MAP(CCacheEdit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCacheEdit message handlers
void CCacheEdit::ShowDefaultWhenDisabled(BOOL bShowDefault)
{
   m_bShowDefault = bShowDefault;
}

BOOL CCacheEdit::ShowDefaultWhenDisabled() const
{
   return m_bShowDefault;
}

void CCacheEdit::EnableWindow(BOOL bEnable)
{
   if ( bEnable )
   {
      if ( !IsWindowEnabled() )
      {
         SetWindowText(m_strCache);
         CEdit::EnableWindow(TRUE);
      }
   }
   else
   {
      if ( IsWindowEnabled() )
      {
         if ( m_bShowDefault )
         {
            SetWindowText(m_strDefault);
         }
         else
         {
            GetWindowText(m_strCache);
            SetWindowText( _T("") );
         }
         CEdit::EnableWindow(FALSE);
      }
      else
      {
         if ( !m_bShowDefault )
         {
            SetWindowText( _T("") );
         }
      }
   }
}

CString CCacheEdit::GetCache() const
{
   return m_strCache;
}

void CCacheEdit::SetDefaultValue(Float64 value,LPCTSTR strDefault)
{
   m_DefaultValue = value;
   m_strDefault = strDefault;
   m_strCache = strDefault;
}

Float64 CCacheEdit::GetDefaultValue() const
{
   return m_DefaultValue;
}

