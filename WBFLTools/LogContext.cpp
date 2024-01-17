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

#include "StdAfx.h"

/****************************************************************************
CLASS
   LogContext
****************************************************************************/

#include <WBFLTools\LogContext.h>
#include <System\SectionValue.h>
#include <TCHAR.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define BUFSIZE 256

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
LogContext::LogContext(ILogFile* pLog,DWORD dwCookie):
WBFL::Debug::LogContext(),
m_LogFile(pLog),
m_dwCookie(dwCookie)
{
   if (m_LogFile)
   {
      m_LogFile->put_EndLines( FALSE );
   }
}

LogContext::~LogContext()
{
}

//======================== OPERATORS  =======================================
WBFL::Debug::LogContext& LogContext::operator<<(const std::_tstring& s)
{
   if (m_LogFile)
      m_LogFile->LogMessage(m_dwCookie,s.c_str());

   return *this;
}

WBFL::Debug::LogContext& LogContext::operator<<(LPCTSTR s)
{
   if (m_LogFile)
      m_LogFile->LogMessage(m_dwCookie,s);

   return *this;
}

WBFL::Debug::LogContext& LogContext::operator<<(TCHAR c)
{
   if (m_LogFile)
   {
      TCHAR buffer[BUFSIZE];
      _stprintf_s( buffer, TEXT("%c"), c );
      m_LogFile->LogMessage(m_dwCookie,buffer);
   }

   return *this;
}

WBFL::Debug::LogContext& LogContext::operator<<(DWORD n)
{
   if (m_LogFile)
   {
      TCHAR buffer[BUFSIZE];
      _stprintf_s(buffer, TEXT("%d"), n);
      m_LogFile->LogMessage(m_dwCookie, buffer);
   }

   return *this;
}

WBFL::Debug::LogContext& LogContext::operator<<(bool n)
{
   if (m_LogFile)
      m_LogFile->LogMessage(m_dwCookie,(n ? TEXT("True") : TEXT("False") ));

   return *this;
}

WBFL::Debug::LogContext& LogContext::operator<<(Int16 n)
{
   if (m_LogFile)
   {
      TCHAR buffer[BUFSIZE];
      _stprintf_s( buffer, TEXT("%d"), n );
      m_LogFile->LogMessage(m_dwCookie,buffer);
   }

   return *this;
}

WBFL::Debug::LogContext& LogContext::operator<<(Uint16 n)
{
   if (m_LogFile)
   {
      TCHAR buffer[BUFSIZE];
      _stprintf_s( buffer, TEXT("%u"), n );
      m_LogFile->LogMessage(m_dwCookie,buffer);
   }

   return *this;
}

WBFL::Debug::LogContext& LogContext::operator<<(Int32 n)
{
   if (m_LogFile)
   {
      TCHAR buffer[BUFSIZE];
      _stprintf_s( buffer, TEXT("%I32d"), n );
      m_LogFile->LogMessage(m_dwCookie,buffer);
   }

   return *this;
}

WBFL::Debug::LogContext& LogContext::operator<<(Uint32 n)
{
   if (m_LogFile)
   {
      TCHAR buffer[BUFSIZE];
      _stprintf_s( buffer, TEXT("%I32u"), n );
      m_LogFile->LogMessage(m_dwCookie,buffer);
   }

   return *this;
}

WBFL::Debug::LogContext& LogContext::operator<<(Int64 n)
{
   if (m_LogFile)
   {
      TCHAR buffer[BUFSIZE];
      _stprintf_s( buffer, TEXT("%I64d"), n );
      m_LogFile->LogMessage(m_dwCookie,buffer);
   }

   return *this;
}

WBFL::Debug::LogContext& LogContext::operator<<(Uint64 n)
{
   if (m_LogFile)
   {
      TCHAR buffer[BUFSIZE];
      _stprintf_s( buffer, TEXT("%I64u"), n );
      m_LogFile->LogMessage(m_dwCookie,buffer);
   }

   return *this;
}

WBFL::Debug::LogContext& LogContext::operator<<(Float32 n)    
{
   if (m_LogFile)
   {
      std::_tostringstream os;
      os << n;
      m_LogFile->LogMessage(m_dwCookie,os.str().c_str());
   }

   return *this;
}

WBFL::Debug::LogContext& LogContext::operator<<(Float64 n)
{
   if (m_LogFile)
   {
      std::_tostringstream os;
      os << n;
      m_LogFile->LogMessage(m_dwCookie,os.str().c_str());
   }

   return *this;
}

WBFL::Debug::LogContext& LogContext::operator<<(Float80 n)
{
   if (m_LogFile)
   {
      std::_tostringstream os;
      os << n;
      m_LogFile->LogMessage(m_dwCookie,os.str().c_str());
   }

   return *this;
}

WBFL::Debug::LogContext& LogContext::operator<<(void * n)
{
   if (m_LogFile)
   {
      TCHAR buffer[BUFSIZE];
      _stprintf_s( buffer, TEXT("%p"), n );
      m_LogFile->LogMessage(m_dwCookie,buffer);
   }

   return *this;
}

WBFL::Debug::LogContext& LogContext::operator<<(const WBFL::System::SectionValue& n)
{
   if (m_LogFile)
   {
      TCHAR buffer[BUFSIZE];
      _stprintf_s( buffer, TEXT("%s"), n.AsString().c_str() );
      m_LogFile->LogMessage(m_dwCookie,buffer);
   }

   return *this;
}

//======================== OPERATIONS =======================================
void LogContext::SetLog(ILogFile* pLog,DWORD dwCookie)
{
   m_LogFile = pLog;

   if (m_LogFile)
   {
      m_LogFile->put_EndLines( FALSE );
   }

   m_dwCookie = dwCookie;
}

void LogContext::GetLog(ILogFile** ppLog,DWORD* pdwCookie)
{
   m_LogFile.CopyTo(ppLog);
   *pdwCookie = m_dwCookie;
}

WBFL::Debug::LogContext& LogContext::EndLine()
{
   if (m_LogFile)
      m_LogFile->LogMessage(m_dwCookie,_T("\n"));

   return *this;
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
