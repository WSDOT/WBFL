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
#include <MfcTools\XShutDown.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CXShutDown,CException)
/****************************************************************************
CLASS
   CXShutDown
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
CXShutDown::CXShutDown(LPCTSTR msg,Int32 reason,bool bAttemptSave,LPCTSTR file, Int16 line) :
CException(TRUE),
m_Message(msg),
m_Reason(reason),
m_bAttemptSave( bAttemptSave ),
m_File(file),
m_Line(line)
{
}

CXShutDown::~CXShutDown()
{
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

Int32 CXShutDown::GetReason() const
{
   return m_Reason;
}

void CXShutDown::GetErrorMessage(std::_tstring* pMsg) const
{
   *pMsg = m_Message;
}

BOOL CXShutDown::GetErrorMessage( LPTSTR lpszError,INT nChar, UINT nMaxError, PUINT pnHelpContext)
{
   IndexType max = min(nMaxError, m_Message.size());
   _tcsncpy_s(lpszError,nChar,m_Message.c_str(),max);
   return TRUE;
}

bool CXShutDown::AttemptSave() const
{
   return m_bAttemptSave;
}

std::_tstring CXShutDown::GetFile() const
{
   return m_File;
}

Int16 CXShutDown::GetLine() const
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
