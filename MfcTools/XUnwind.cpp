///////////////////////////////////////////////////////////////////////
// MfcTools - Extension library for MFC
// Copyright © 1999-2025  Washington State Department of Transportation
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

#include "StdAfx.h"

/****************************************************************************
CLASS
   CXUnwind
****************************************************************************/

#include <MfcTools\XUnwind.h>


IMPLEMENT_DYNAMIC(CXUnwind,CException)

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
CXUnwind::CXUnwind(LPCTSTR msg,Int32 reason,LPCTSTR file, Int16 line) :
CException(TRUE),
m_Message(msg),
m_Reason(reason),
m_File(file),
m_Line(line)
{
}

CXUnwind::~CXUnwind()
{
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

Int32 CXUnwind::GetReason() const
{
   return m_Reason;
}

void CXUnwind::GetErrorMessage(std::_tstring* pMsg) const
{
   *pMsg = m_Message;
}

BOOL CXUnwind::GetErrorMessage( LPTSTR lpszError, INT nChar, UINT nMaxError, PUINT pnHelpContext)
{
   IndexType max = min(nMaxError, m_Message.size());
   _tcsncpy_s(lpszError,nChar,m_Message.c_str(),max);
   return TRUE;
}

std::_tstring CXUnwind::GetFile() const
{
   return m_File;
}

Int16 CXUnwind::GetLine() const
{
   return m_Line;
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

//======================== DEBUG      =======================================
