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
#include <System\DebugWindowLogContext.h>

using namespace WBFL::Debug;

#define BUFSIZE 256

DebugWindowLogContext::DebugWindowLogContext()
{
}

DebugWindowLogContext::~DebugWindowLogContext()
{
}

LogContext& DebugWindowLogContext::operator<<(const std::_tstring& s)
{
   OutputDebugString( s.c_str() );
   return *this;
}

LogContext& DebugWindowLogContext::operator<<(LPCTSTR s)
{
   OutputDebugString( s );
   return *this;
}

LogContext& DebugWindowLogContext::operator<<(TCHAR ch)
{
   TCHAR buffer[BUFSIZE];
   buffer[0] = '\0';
   _stprintf_s( buffer, TEXT("%c"), ch );
   OutputDebugString( buffer );
   return *this;
}

LogContext& DebugWindowLogContext::operator<<(DWORD n)
{
   TCHAR buffer[BUFSIZE];
   buffer[0] = '\0';
   _stprintf_s( buffer, TEXT("%d"), n );
   OutputDebugString( buffer );
   return *this;
}

LogContext& DebugWindowLogContext::operator<<(bool n)
{
   OutputDebugString( n ? TEXT("True") : TEXT("False") );
   return *this;
}

LogContext& DebugWindowLogContext::operator<<(Int16 n)
{
   TCHAR buffer[BUFSIZE];
   _stprintf_s( buffer, BUFSIZE, TEXT("%d"), n );
   OutputDebugString( buffer );
   return *this;
}

LogContext& DebugWindowLogContext::operator<<(Uint16 n)
{
   TCHAR buffer[BUFSIZE];
   _stprintf_s( buffer, BUFSIZE, TEXT("%u"), n );
   OutputDebugString( buffer );
   return *this;
}

LogContext& DebugWindowLogContext::operator<<(Int32 n)
{
   TCHAR buffer[BUFSIZE];
   _stprintf_s( buffer, BUFSIZE, TEXT("%I32d"), n );
   OutputDebugString( buffer );
   return *this;
}

LogContext& DebugWindowLogContext::operator<<(Uint32 n)
{
   TCHAR buffer[BUFSIZE];
   _stprintf_s( buffer, BUFSIZE, TEXT("%I32u"), n );
   OutputDebugString( buffer );
   return *this;
}

LogContext& DebugWindowLogContext::operator<<(Int64 n)
{
   TCHAR buffer[BUFSIZE];
   _stprintf_s( buffer, BUFSIZE, TEXT("%I64d"), n );
   OutputDebugString( buffer );
   return *this;
}

LogContext& DebugWindowLogContext::operator<<(Uint64 n)
{
   TCHAR buffer[BUFSIZE];
   _stprintf_s( buffer, BUFSIZE, TEXT("%I64u"), n );
   OutputDebugString( buffer );
   return *this;
}

LogContext& DebugWindowLogContext::operator<<(Float32 n)    
{
   TCHAR buffer[BUFSIZE];
   _stprintf_s( buffer, BUFSIZE, TEXT("%f"), n );
   OutputDebugString( buffer );
   return *this;
}

LogContext& DebugWindowLogContext::operator<<(Float64 n)
{
   TCHAR buffer[BUFSIZE];
   _stprintf_s( buffer, BUFSIZE, TEXT("%f"), n );
   OutputDebugString( buffer );
   return *this;
}

LogContext& DebugWindowLogContext::operator<<(Float80 n)
{
   TCHAR buffer[BUFSIZE];
   _stprintf_s( buffer, BUFSIZE, TEXT("%lf"), n );
   OutputDebugString( buffer );
   return *this;
}

LogContext& DebugWindowLogContext::operator<<(void * n)
{
   TCHAR buffer[BUFSIZE];
   _stprintf_s( buffer, BUFSIZE, TEXT("%p"), n );
   OutputDebugString( buffer );
   return *this;
}

LogContext& DebugWindowLogContext::operator<<(const WBFL::System::SectionValue& n)
{
   TCHAR buffer[BUFSIZE];
   _stprintf_s( buffer, BUFSIZE, TEXT("%s"), n.AsString().c_str() );
   OutputDebugString( buffer );
   return *this;
}

LogContext& DebugWindowLogContext::EndLine()
{
   TCHAR buffer[BUFSIZE];
   _stprintf_s( buffer, BUFSIZE, TEXT("%s"), TEXT("\n") );
   OutputDebugString( buffer );
   return *this;
}
