///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
// Copyright © 1999-2010  Washington State Department of Transportation
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

#define BUILD_CHECKS

#if !defined __WATCH
#define __WATCH
#endif

#include <System\SysLib.h>

#include <System\Checks.h>
#include <System\XProgrammingError.h>
#include <strstream>

/*#if !defined _DEBUG
#include <stdexcept>
#endif
  */ 
DIAG_DEFINE_GROUP(Def,1,0);

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

bool dbgDiagBase::bWarnPopup = true;

void dbgDiagBase::Watch( const char *group, const char *msg,
                         const char *fname, Uint32 line )
{
   dbgDiagBase::Message( "Watch", group, msg, fname, line, false );
}

void dbgDiagBase::Warn( const char *group, const char *msg,
                        const char *fname, Uint32 line )
{
   dbgDiagBase::Message( "Warn", group, msg, fname, line, bWarnPopup );
}

void dbgDiagBase::Message( const char *type,
                           const char *group, const char *msg,
                           const char *fname, Uint32 line, bool bPopup)
{
    std::ostringstream out;
    out << type << ' ' << fname << ' ' << line
        << ": [" << group << "] " << msg
        << std::endl;
    std::string message = out.str();
    Output( message.c_str() );

   if ( bPopup )
      ::MessageBox(0, message.c_str(), "Warning", MB_OK | MB_ICONWARNING );
}

void dbgDiagBase::Output( const char *msg )
{
    ::OutputDebugString(msg);
}

void dbgDiagBase::EnableWarnPopup(bool bEnable)
{
   bWarnPopup = bEnable;
}

bool dbgDiagBase::IsWarnPopupEnabled()
{
   return bWarnPopup;
}

void dbgMessage::Precondition(const char* s,const char* file, Int32 line)
{
#if defined _DEBUG
    if ( _CrtDbgReport(_CRT_ASSERT,file,line,NULL,"[Precondition] %s\n",s) == 1 )
       _CrtDbgBreak();
#else
    throw sysXProgrammingError(sysXProgrammingError::InvalidValue,file,line);
#endif
}

void dbgMessage::Check(const char* s,const char* file, Int32 line)
{
#if defined _DEBUG
    if ( _CrtDbgReport(_CRT_ASSERT,file,line,NULL,"[Check] %s\n",s) == 1 )
       _CrtDbgBreak();
#else
    throw sysXProgrammingError(sysXProgrammingError::CodeFault,file,line);
#endif
}

void dbgMessage::AssertValidFailed(const char* s,const char* file, Int32 line)
{
#if defined _DEBUG
    if ( _CrtDbgReport(_CRT_ASSERT,file,line,NULL,"[Assert Valid Failed] %s\n",s) == 1 )
       _CrtDbgBreak();
#else
    throw sysXProgrammingError(sysXProgrammingError::AssertValidFailed,file,line);
#endif
}
