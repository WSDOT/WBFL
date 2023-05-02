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

#define BUILD_CHECKS

#if !defined __WATCH
#define __WATCH
#endif

#include <System\SysLib.h>
#include <System\Checks.h>
#include <System\XProgrammingError.h>
#include <strstream>

using namespace WBFL::Debug;

DIAG_DEFINE_GROUP(Def,1,0);

bool Diagnostics::bWarnPopup = true;

void Diagnostics::Watch(const std::_tstring& group, const std::_tstring& msg,
                         const std::_tstring& fname, Uint32 line )
{
   Diagnostics::Message( _T("Watch"), group, msg, fname, line, false );
}

void Diagnostics::Warn( const std::_tstring& group, const std::_tstring& msg,
                        const std::_tstring& fname, Uint32 line )
{
   Diagnostics::Message( _T("Warn"), group, msg, fname, line, bWarnPopup );
}

void Diagnostics::Message( const std::_tstring& type,
                           const std::_tstring& group, const std::_tstring& msg,
                           const std::_tstring& fname, Uint32 line, bool bPopup)
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

void Diagnostics::Output( const std::_tstring& msg )
{
    ::OutputDebugString(msg.c_str());
}

void Diagnostics::EnableWarnPopup(bool bEnable)
{
   bWarnPopup = bEnable;
}

bool Diagnostics::IsWarnPopupEnabled()
{
   return bWarnPopup;
}

void Message::Precondition(const std::_tstring& s,const std::_tstring& file, Uint32 line)
{
#if defined _DEBUG
#if defined _UNICODE
    if ( _CrtDbgReportW(_CRT_ASSERT,file.c_str(), line, nullptr, _T("[Precondition] %s\n"), s.c_str()) == 1)
#else
    if ( _CrtDbgReport(_CRT_ASSERT,file.c_str(),line,nullptr,_T("[Precondition] %s\n"),s.c_str()) == 1 )
#endif
       _CrtDbgBreak();
#else
    throw WBFL::System::XProgrammingError(WBFL::System::XProgrammingError::InvalidValue,file,line);
#endif
}

void Message::Check(const std::_tstring& s,const std::_tstring& file, Uint32 line)
{
#if defined _DEBUG
#if defined _UNICODE
    if ( _CrtDbgReportW(_CRT_ASSERT,file.c_str(),line,nullptr,_T("[Check] %s\n"),s.c_str()) == 1 )
#else
    if ( _CrtDbgReport(_CRT_ASSERT,file.c_str(),line,nullptr,_T("[Check] %s\n"),s.c_str()) == 1 )
#endif
       _CrtDbgBreak();
#else
    throw WBFL::System::XProgrammingError(WBFL::System::XProgrammingError::CodeFault,file,line);
#endif
}

void Message::AssertValidFailed(const std::_tstring& s,const std::_tstring& file, Uint32 line)
{
#if defined _DEBUG
    if ( _CrtDbgReportW(_CRT_ASSERT,file.c_str(),line,nullptr,_T("[Assert Valid Failed] %s\n"),s.c_str()) == 1 )
#if defined _UNICODE
#else
    if ( _CrtDbgReport(_CRT_ASSERT,file.c_str(),line,nullptr,_T("[Assert Valid Failed] %s\n"),s.c_str()) == 1 )
#endif
       _CrtDbgBreak();
#else
    throw WBFL::System::XProgrammingError(WBFL::System::XProgrammingError::AssertValidFailed,file,line);
#endif
}
