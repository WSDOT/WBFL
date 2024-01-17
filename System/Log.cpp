///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
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

#include <System\SysLib.h>
#include <System\Log.h>
#include <iostream>

using namespace WBFL::Debug;

Log::Log(): 
m_NumErrors(0)
{
}

Log::Log(LogContext& context): 
m_pContext( &context ),
m_NumErrors(0)
{
}

Log::~Log()
{
}

Log& Log::operator<<(const std::_tstring& s)
{
   *m_pContext << s;
   return *this;
}

Log& Log::operator<<(LPCTSTR s)
{
   *m_pContext << s;
   return *this;
}

Log& Log::operator<<(TCHAR c)
{
   *m_pContext << c;
   return *this;
}

Log& Log::operator<<(bool n)
{
   *m_pContext << n;
   return *this;
}

Log& Log::operator<<(Int16 n)
{
   *m_pContext << n;
   return *this;
}

Log& Log::operator<<(Uint16 n)
{
   *m_pContext << n;
   return *this;
}

Log& Log::operator<<(Int32 n)
{
   *m_pContext << n;
   return *this;
}

Log& Log::operator<<(Uint32 n)
{
   *m_pContext << n;
   return *this;
}

Log& Log::operator<<(Int64 n)
{
   *m_pContext << n;
   return *this;
}

Log& Log::operator<<(Uint64 n)
{
   *m_pContext << n;
   return *this;
}

Log& Log::operator<<(Float32 n)    
{
   *m_pContext << n;
   return *this;
}

Log& Log::operator<<(Float64 n)
{
   *m_pContext << n;
   return *this;
}

Log& Log::operator<<(Float80 n)
{
   *m_pContext << n;
   return *this;
}

Log& Log::operator<<(void * n)
{
   *m_pContext << n;
   return *this;
}

Log& Log::operator<<(Log& (*pf)(Log&))
{
   (*pf)(*this);
   return *this;
}

void Log::LogTestResult(const std::_tstring& msg,  TestResult type)
{
   if (type == Log::TestResult::Failed)
   {
      m_NumErrors++; // can set a break here when test fails
   }

   m_ErrorLog.emplace_back(type,msg);
}

size_t Log::GetNumEntries() const
{
   return m_ErrorLog.size();
}

size_t Log::GetNumErrors() const
{
   return m_NumErrors;
}

size_t Log::GetTestCount(TestResult type) const
{
   size_t cTests = std::count_if(m_ErrorLog.begin(), m_ErrorLog.end(), [&](const auto& error) {return (error.first == type); });
   return cTests;
}

void Log::DumpFilteredLog(TestResult type) const
{
   std::for_each(m_ErrorLog.begin(), m_ErrorLog.end(),[&](const auto& error) {if (error.first == type) *m_pContext << error.second << endl; });
}

void Log::DumpEntireLog() const
{
   std::for_each(m_ErrorLog.begin(), m_ErrorLog.end(), [&](const auto& error) {*m_pContext << error.second << endl; });
}

void Log::SetLogContext(LogContext& context) 
{ 
   m_pContext = &context;
}

LogContext& Log::GetLogContext() 
{ 
   return *m_pContext;
}

namespace WBFL
{
   namespace Debug
   {
      Log& endl(Log& rl)
      {
         rl << _T("\n");
         return rl;
      }
   }
}
