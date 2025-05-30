///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
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

#include <System\SysLib.h>
#include <System\UnitTestLog.h>
#include <iostream>

using namespace WBFL::Debug;

UnitTestLog::UnitTestLog():
m_NumErrors(0)
{
}

UnitTestLog::UnitTestLog(LogContext& context):
m_pContext( &context ),
m_NumErrors(0)
{
}

UnitTestLog::~UnitTestLog()
{
}

UnitTestLog& UnitTestLog::operator<<(const std::_tstring& s)
{
   *m_pContext << s;
   return *this;
}

UnitTestLog& UnitTestLog::operator<<(LPCTSTR s)
{
   *m_pContext << s;
   return *this;
}

UnitTestLog& UnitTestLog::operator<<(TCHAR c)
{
   *m_pContext << c;
   return *this;
}

UnitTestLog& UnitTestLog::operator<<(bool n)
{
   *m_pContext << n;
   return *this;
}

UnitTestLog& UnitTestLog::operator<<(Int16 n)
{
   *m_pContext << n;
   return *this;
}

UnitTestLog& UnitTestLog::operator<<(Uint16 n)
{
   *m_pContext << n;
   return *this;
}

UnitTestLog& UnitTestLog::operator<<(Int32 n)
{
   *m_pContext << n;
   return *this;
}

UnitTestLog& UnitTestLog::operator<<(Uint32 n)
{
   *m_pContext << n;
   return *this;
}

UnitTestLog& UnitTestLog::operator<<(Int64 n)
{
   *m_pContext << n;
   return *this;
}

UnitTestLog& UnitTestLog::operator<<(Uint64 n)
{
   *m_pContext << n;
   return *this;
}

UnitTestLog& UnitTestLog::operator<<(Float32 n)    
{
   *m_pContext << n;
   return *this;
}

UnitTestLog& UnitTestLog::operator<<(Float64 n)
{
   *m_pContext << n;
   return *this;
}

UnitTestLog& UnitTestLog::operator<<(Float80 n)
{
   *m_pContext << n;
   return *this;
}

UnitTestLog& UnitTestLog::operator<<(void * n)
{
   *m_pContext << n;
   return *this;
}

UnitTestLog& UnitTestLog::operator<<(UnitTestLog& (*pf)(UnitTestLog&))
{
   (*pf)(*this);
   return *this;
}

void UnitTestLog::LogTestResult(const std::_tstring& msg,  TestResult type)
{
   if (type == UnitTestLog::TestResult::Failed)
   {
      m_NumErrors++; // can set a break here when test fails
   }

   m_ErrorLog.emplace_back(type,msg);
}

size_t UnitTestLog::GetNumEntries() const
{
   return m_ErrorLog.size();
}

size_t UnitTestLog::GetNumErrors() const
{
   return m_NumErrors;
}

size_t UnitTestLog::GetTestCount(TestResult type) const
{
   size_t cTests = std::count_if(m_ErrorLog.begin(), m_ErrorLog.end(), [&](const auto& error) {return (error.first == type); });
   return cTests;
}

void UnitTestLog::DumpFilteredLog(TestResult type) const
{
   std::for_each(m_ErrorLog.begin(), m_ErrorLog.end(),[&](const auto& error) {if (error.first == type) *m_pContext << error.second << endl; });
}

void UnitTestLog::DumpEntireLog() const
{
   std::for_each(m_ErrorLog.begin(), m_ErrorLog.end(), [&](const auto& error) {*m_pContext << error.second << endl; });
}

void UnitTestLog::SetLogContext(LogContext& context)
{ 
   m_pContext = &context;
}

LogContext& UnitTestLog::GetLogContext()
{ 
   return *m_pContext;
}

namespace WBFL
{
   namespace Debug
   {
      UnitTestLog& endl(UnitTestLog& rl)
      {
         rl << _T("\n");
         return rl;
      }
   }
}
