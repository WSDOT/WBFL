///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
// Copyright (C) 1999  Washington State Department of Transportation
//                     Bridge and Structures Office
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

/****************************************************************************
CLASS
   dbgDumpContext
****************************************************************************/

#include <System\DumpContext.h>
#include <System\SectionValue.h>
#include <TCHAR.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define BUFSIZE 256

dbgDumpContext& operator<<(dbgDumpContext& dc,dbgDumpContext& (*pf)(dbgDumpContext&))
{
   return (*pf)(dc);
}

dbgDumpContext& endl(dbgDumpContext& dmpCtx)
{
   return dmpCtx.EndLine();
}

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
dbgDumpContext::dbgDumpContext()
{
}

dbgDumpContext::~dbgDumpContext()
{
}

//======================== OPERATORS  =======================================
dbgDumpContext& dbgDumpContext::operator<<(const std::string& s)
{
   OutputDebugString( s.c_str() );
   return *this;
}

dbgDumpContext& dbgDumpContext::operator<<(const char* s)
{
   OutputDebugString( s );
   return *this;
}

dbgDumpContext& dbgDumpContext::operator<<(char ch)
{
   TCHAR buffer[BUFSIZE];
   sprintf_s( buffer, TEXT("%c"), ch );
   OutputDebugString( buffer );
   return *this;
}

dbgDumpContext& dbgDumpContext::operator<<(bool n)
{
   OutputDebugString( n ? TEXT("True") : TEXT("False") );
   return *this;
}

dbgDumpContext& dbgDumpContext::operator<<(int n)
{
   TCHAR buffer[BUFSIZE];
   sprintf_s( buffer, TEXT("%d"), n );
   OutputDebugString( buffer );
   return *this;
}

dbgDumpContext& dbgDumpContext::operator<<(unsigned int n)
{
   TCHAR buffer[BUFSIZE];
   sprintf_s( buffer, BUFSIZE, TEXT("%u"), n );
   OutputDebugString( buffer );
   return *this;
}

dbgDumpContext& dbgDumpContext::operator<<(Int16 n)
{
   TCHAR buffer[BUFSIZE];
   sprintf_s( buffer, BUFSIZE, TEXT("%d"), n );
   OutputDebugString( buffer );
   return *this;
}

dbgDumpContext& dbgDumpContext::operator<<(Uint16 n)
{
   TCHAR buffer[BUFSIZE];
   sprintf_s( buffer, BUFSIZE, TEXT("%u"), n );
   OutputDebugString( buffer );
   return *this;
}

dbgDumpContext& dbgDumpContext::operator<<(Int32 n)
{
   TCHAR buffer[BUFSIZE];
   sprintf_s( buffer, BUFSIZE, TEXT("%ld"), n );
   OutputDebugString( buffer );
   return *this;
}

dbgDumpContext& dbgDumpContext::operator<<(Uint32 n)
{
   TCHAR buffer[BUFSIZE];
   sprintf_s( buffer, BUFSIZE, TEXT("%lu"), n );
   OutputDebugString( buffer );
   return *this;
}

dbgDumpContext& dbgDumpContext::operator<<(Float32 n)    
{
   TCHAR buffer[BUFSIZE];
   sprintf_s( buffer, BUFSIZE, TEXT("%f"), n );
   OutputDebugString( buffer );
   return *this;
}

dbgDumpContext& dbgDumpContext::operator<<(Float64 n)
{
   TCHAR buffer[BUFSIZE];
   sprintf_s( buffer, BUFSIZE, TEXT("%f"), n );
   OutputDebugString( buffer );
   return *this;
}

dbgDumpContext& dbgDumpContext::operator<<(Float80 n)
{
   TCHAR buffer[BUFSIZE];
   sprintf_s( buffer, BUFSIZE, TEXT("%lf"), n );
   OutputDebugString( buffer );
   return *this;
}

dbgDumpContext& dbgDumpContext::operator<<(void * n)
{
   TCHAR buffer[BUFSIZE];
   sprintf_s( buffer, BUFSIZE, TEXT("%p"), n );
   OutputDebugString( buffer );
   return *this;
}

dbgDumpContext& dbgDumpContext::operator<<(const sysSectionValue& n)
{
   TCHAR buffer[BUFSIZE];
   sprintf_s( buffer, BUFSIZE, TEXT("%s"), n.AsString() );
   OutputDebugString( buffer );
   return *this;
}

//======================== OPERATIONS =======================================
dbgDumpContext& dbgDumpContext::EndLine()
{
   TCHAR buffer[BUFSIZE];
   sprintf_s( buffer, BUFSIZE, TEXT("%s"), TEXT("\n") );
   OutputDebugString( buffer );
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
