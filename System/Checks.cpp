///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
// Copyright © 1999-2014, Washington State Department of Transportation, All Rights Reserved
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

void dbgDiagBase::Watch( LPCTSTR group, LPCTSTR msg,
                         LPCTSTR fname, Uint32 line )
{
   dbgDiagBase::Message( _T("Watch"), group, msg, fname, line, false );
}

void dbgDiagBase::Warn( LPCTSTR group, LPCTSTR msg,
                        LPCTSTR fname, Uint32 line )
{
   dbgDiagBase::Message( _T("Warn"), group, msg, fname, line, bWarnPopup );
}

void dbgDiagBase::Message( LPCTSTR type,
                           LPCTSTR group, LPCTSTR msg,
                           LPCTSTR fname, Uint32 line, bool bPopup)
{
    std::_tostringstream out;
    out << type << _T(' ') << fname << _T(' ') << line
        << _T(": [") << group << _T("] ") << msg
        << std::endl;
    std::_tstring message = out.str();
    Output( message.c_str() );

   if ( bPopup )
      ::MessageBox(0, message.c_str(), _T("Warning"), MB_OK | MB_ICONWARNING );
}

void dbgDiagBase::Output( LPCTSTR msg )
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

void dbgMessage::Precondition(LPCTSTR s,LPCTSTR file, Int32 line)
{
#if defined _DEBUG
#if defined _UNICODE
    if ( _CrtDbgReportW(_CRT_ASSERT,file,line,NULL,_T("[Precondition] %s\n"),s) == 1 )
#else
    if ( _CrtDbgReport(_CRT_ASSERT,file,line,NULL,_T("[Precondition] %s\n"),s) == 1 )
#endif
       _CrtDbgBreak();
#else
    throw sysXProgrammingError(sysXProgrammingError::InvalidValue,file,line);
#endif
}

void dbgMessage::Check(LPCTSTR s,LPCTSTR file, Int32 line)
{
#if defined _DEBUG
#if defined _UNICODE
    if ( _CrtDbgReportW(_CRT_ASSERT,file,line,NULL,_T("[Check] %s\n"),s) == 1 )
#else
    if ( _CrtDbgReport(_CRT_ASSERT,file,line,NULL,_T("[Check] %s\n"),s) == 1 )
#endif
       _CrtDbgBreak();
#else
    throw sysXProgrammingError(sysXProgrammingError::CodeFault,file,line);
#endif
}

void dbgMessage::AssertValidFailed(LPCTSTR s,LPCTSTR file, Int32 line)
{
#if defined _DEBUG
    if ( _CrtDbgReportW(_CRT_ASSERT,file,line,NULL,_T("[Assert Valid Failed] %s\n"),s) == 1 )
#if defined _UNICODE
#else
    if ( _CrtDbgReport(_CRT_ASSERT,file,line,NULL,_T("[Assert Valid Failed] %s\n"),s) == 1 )
#endif
       _CrtDbgBreak();
#else
    throw sysXProgrammingError(sysXProgrammingError::AssertValidFailed,file,line);
#endif
}
