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
#include <System\FileLogContext.h>
#include <System\SectionValue.h>
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace WBFL::Debug;

FileLogContext::FileLogContext(const std::_tstring& fname):
LogContext(),
m_os(fname.c_str())
{
}

FileLogContext::~FileLogContext()
{
}

LogContext& FileLogContext::operator<<(const std::_tstring& s)
{
   m_os << s;
   return *this;
}

LogContext& FileLogContext::operator<<(LPCTSTR s)
{
   m_os << s;
   return *this;
}

LogContext& FileLogContext::operator<<(TCHAR c)
{
   m_os << c;
   return *this;
}

LogContext& FileLogContext::operator<<(DWORD n)
{
   m_os << n;
   return *this;
}

LogContext& FileLogContext::operator<<(bool n)
{
   m_os << (n ? _T("True") : _T("False"));
   return *this;
}

LogContext& FileLogContext::operator<<(Int16 n)
{
   m_os << n;
   return *this;
}

LogContext& FileLogContext::operator<<(Uint16 n)
{
   m_os << n;
   return *this;
}

LogContext& FileLogContext::operator<<(Int32 n)
{
   m_os << n;
   return *this;
}

LogContext& FileLogContext::operator<<(Uint32 n)
{
   m_os << n;
   return *this;
}

LogContext& FileLogContext::operator<<(Int64 n)
{
   m_os << n;
   return *this;
}

LogContext& FileLogContext::operator<<(Uint64 n)
{
   m_os << n;
   return *this;
}

LogContext& FileLogContext::operator<<(Float32 n)    
{
   m_os << n;
   return *this;
}

LogContext& FileLogContext::operator<<(Float64 n)
{
   m_os << n;
   return *this;
}

LogContext& FileLogContext::operator<<(Float80 n)
{
   m_os << n;
   return *this;
}

LogContext& FileLogContext::operator<<(void * n)
{
   m_os << n;
   return *this;
}

LogContext& FileLogContext::operator<<(const WBFL::System::SectionValue& n)
{
   m_os << n.AsString();
   return *this;
}

std::_tostream& FileLogContext::GetStream()
{
   return m_os;
}

FileLogContext::operator std::_tostream&()
{
   return GetStream();
}

LogContext& FileLogContext::EndLine()
{
   m_os << std::endl; 
   return *this;
}
