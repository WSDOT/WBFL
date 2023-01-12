///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
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

#include <System\SysLib.h>
#include <System\XStructuredLoad.h>

#ifdef _DEBUG
#if defined(_AFX_NO_DEBUG_CRT)
#pramga message("WARNING - Memory debugging disabled")
#endif
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace WBFL::System;

XStructuredLoad::XStructuredLoad(XStructuredLoad::Reason reason, const std::_tstring& file, Uint32 line) :
XBase(file,line),
m_Reason(reason)
{
}

void XStructuredLoad::Throw() const
{
   throw *this; //*static_cast<const sysXStructuredLoad*>(this);
}

Int32 XStructuredLoad::GetReason() const noexcept
{
   return m_Reason;
}

XStructuredLoad::Reason XStructuredLoad::GetReasonCode() const noexcept
{
   return m_Reason;
}

void XStructuredLoad::SetExtendedMessage(LPCTSTR msg)
{
   m_ExtendedMessage = std::_tstring(msg);
}

void XStructuredLoad::GetErrorMessage(std::_tstring* pMsg) const
{
   __super::GetErrorMessage(pMsg);
   switch (m_Reason)
   {
   case InvalidFileFormat:
      *pMsg += _T("File format was invalid\n\n");
      break;
   case EndOfFile:
      *pMsg += _T("Unexpected end of file\n\n");
      break;
   case BadRead:
      *pMsg += _T("Unexpected error trying to read file\n\n");
      break;
   case BadVersion:
      *pMsg += _T("Unexpected version number reading structured data\n\n");
      break;
   case MemoryError:
      *pMsg += _T("Memory allocation error during structured read\n\n");
      break;
   case CantInitializeTheParser:
      *pMsg += _T("Could not initialize the parser. Perhaps the parser component is not installed\n\n");
      break;
   case UserDefined:
      *pMsg += _T("User Defined error reading structured data\n\n");
      break;
   case Unspecified:
      *pMsg += _T("Unspecified error reading structured data\n\n");
      break;
   default:
      *pMsg += _T("Unknown error reading structured data\n\n");
      break;
   }
   *pMsg += m_ExtendedMessage;
}
