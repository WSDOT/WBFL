///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
// Copyright © 1999-2013  Washington State Department of Transportation
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

//----------------------------------------------------------------------------
//   Diagnostic macros for checking:
//
//     PRECONDITION[X]  Used to check values you don't have direct control over
//     CHECK[X]         Used to check values you do have direct control over
//     ASSERTVALID[X]   Calls you class's AssertValid() method
//     WATCH[X]         Output a tracing text stream
//     WARN[X]          Output a warning text stream
//
//   Based on the following switches:
//     __PRECONDITION  When defined enables PRECONDITION
//     __CHECK         When defined enables CHECK
//     __ASSERTVALID   When defined enables ASSERTVALID
//     __WATCH         When defined enables WATCH
//     __WARN          When defined enables WARN
//
//   ASSERTVALID, WATCH, and WARN are always compiled out of release builds.
//----------------------------------------------------------------------------
#ifndef INCLUDED_SYSTEM_CHECKS_H_
#define INCLUDED_SYSTEM_CHECKS_H_
#pragma once

#ifndef __cplusplus
#error Must use C++ for CHECKS.H
#endif

#include <WBFLTypes.h>
#include <System\DbgBuild.h>
#include <sstream>

#if !defined _DEBUG
#undef __WATCH
#undef __WARN
#undef __ASSERTVALID
#endif

#define DIAG_GROUP_DISABLE 0
#define DIAG_GROUP_ENABLE  1
#define MAX_DIAG_GROUP_LEVEL 127

//
// dbgDiagBase - this class forms the base for dbgDiagGroup classes and
// handles basic message output.
//

class SYSCLASS dbgDiagBase
{
public:
   static void EnableWarnPopup(bool bEnable);
   static bool IsWarnPopupEnabled();

protected:
   static void Watch( LPCTSTR group, LPCTSTR msg,
                      LPCTSTR fname, Uint32 line );
   static void Warn( LPCTSTR group, LPCTSTR msg,
                     LPCTSTR fname, Uint32 line );

public:
    struct Flags
    {
        Uint8 Enabled : 1;
        Uint8 Level   : 7;
    };

private:
    static bool bWarnPopup;

    static void Message( LPCTSTR type,
                         LPCTSTR group, LPCTSTR msg,
                         LPCTSTR fname, Uint32 line, bool bPopup );
    static void Output( LPCTSTR msg );
};


class SYSCLASS dbgMessage
{
public:
   static void Precondition(LPCTSTR s,LPCTSTR file, Int32 line);
   static void Check(LPCTSTR s,LPCTSTR file, Int32 line);
   static void AssertValidFailed(LPCTSTR s,LPCTSTR file, Int32 line);
};


#undef PRECONDITION
#undef PRECONDITIONX
#define PRECONDITION(p) PRECONDITIONX(p,_T(#p))

#if defined __PRECONDITION

#define PRECONDITIONX(p,s)   \
   if(!(p)) { dbgMessage::Precondition(s,_T(__FILE__),__LINE__);}

#else

#define PRECONDITIONX(p,s) __noop

#endif //__PRECONDITION

#undef CHECK
#undef CHECKX
#define CHECK(p) CHECKX(p,_T(#p))

#if defined __CHECK

#define CHECKX(p,s)   \
   if(!(p)) { dbgMessage::Check(s,_T(__FILE__),__LINE__);}

#else

#define CHECKX(p,s)    __noop

#endif // __CHECK


#undef ASSERTVALID
#undef ASSERTVALIDX
#define ASSERTVALID ASSERTVALIDX( _T("") )

#if defined __ASSERTVALID

#define ASSERTVALIDX(s) \
   if (!AssertValid()) { dbgMessage::AssertValidFailed(s,_T(__FILE__),__LINE__);}

#else

#define ASSERTVALIDX(S) __noop

#endif // __ASSERTVALID

#if defined(__WATCH) || defined(__WARN)

#if defined (BUILDSYSLIB) && !defined(SYSLIB)
#define DIAG_IMPORT __declspec(dllimport)
#define DIAG_EXPORT __declspec(dllexport)
#elif defined(DBGLIB)
#define DIAG_IMPORT
#define DIAG_EXPORT
#else
#define DIAG_IMPORT
#define DIAG_EXPORT
#endif

#define DECLARE_DIAG_GROUP(g,qual)                                         \
class qual dbgDiagGroup##g : private dbgDiagBase                           \
{                                                                          \
public:                                                                    \
    static void Watch( Uint8 level, LPCTSTR msg,                       \
                       LPCTSTR fname, Uint32 line );                   \
                                                                           \
    static void Warn( Uint8 level, LPCTSTR msg,                        \
                      LPCTSTR fname, Uint32 line );                    \
                                                                           \
    static void Enable(Uint8 enabled)                                      \
                    { Flags.Enabled = Uint8(enabled ? 1 : 0); }            \
    static int  IsEnabled() { return Flags.Enabled; }                      \
                                                                           \
    static void SetLevel( Uint8 level ) { Flags.Level = level; }           \
    static Uint8 GetLevel() { return Flags.Level; }                        \
                                                                           \
private:                                                                   \
     static Flags Flags;                                                   \
     static LPTSTR Name;                                                    \
}

#define DIAG_DECLARE_GROUP(g)                                              \
DECLARE_DIAG_GROUP(g,DIAG_IMPORT);

#define DIAG_DEFINE_GROUP(g,e,l)                                           \
DECLARE_DIAG_GROUP(g,DIAG_EXPORT);                                         \
void dbgDiagGroup##g::Watch( Uint8 level, LPCTSTR msg,                 \
                             LPCTSTR fname, Uint32 line )              \
{                                                                          \
     if( IsEnabled() && level <= GetLevel() )                              \
          dbgDiagBase::Watch( Name, msg, fname, line );                    \
}                                                                          \
                                                                           \
void dbgDiagGroup##g::Warn( Uint8 level, LPCTSTR msg,                  \
                            LPCTSTR fname, Uint32 line )               \
{                                                                          \
     if( IsEnabled() && level <= GetLevel() )                              \
          dbgDiagBase::Warn( Name, msg, fname, line );                     \
}                                                                          \
                                                                           \
LPTSTR dbgDiagGroup##g::Name = _T(#g);                                          \
dbgDiagBase::Flags dbgDiagGroup##g::Flags = { (e), (l) }

#define DIAG_ENABLE(g,s)            dbgDiagGroup##g::Enable(s)
#define DIAG_ISENABLED(g)           dbgDiagGroup##g::IsEnabled()
#define DIAG_SETLEVEL(g,l)          dbgDiagGroup##g::SetLevel(l)
#define DIAG_GETLEVEL(g)            dbgDiagGroup##g::GetLevel()

#define DIAG_WARNPOPUP(b)           dbgDiagBase::EnableWarnPopup(b)
#define DIAG_ISENABLED_WARNPOPUP    dbgDiagBase::IsWarnPopupEnabled()

#if !defined( BUILD_CHECKS ) && !defined( _DEF_DECLARED )
#define _DEF_DECLARED
DECLARE_DIAG_GROUP(Def, SYSCLASS);
#endif

#else   // !defined(__WATCH) && !defined(__WARN)

#define DIAG_DECLARE_GROUP(g)
#define DIAG_DEFINE_GROUP(g,e,l)

#define DIAG_ENABLE(g,s)            __noop
#define DIAG_ISENABLED(g)           __noop
#define DIAG_SETLEVEL(g,l)          __noop
#define DIAG_GETLEVEL(g)            __noop

#define DIAG_WARNPOPUP(b)           __noop
#define DIAG_ISENABLED_WARNPOPUP    __noop

#endif

#if defined(__WATCH)
    #define WATCH(m)                    WATCHX(Def,0,m)
    #define WATCHX(g,l,m)\
            {\
                std::_tostringstream Out; \
                Out << m << std::ends;\
                dbgDiagGroup##g::Watch(l,Out.str().c_str(),_T(__FILE__),__LINE__);\
            }
#else
    #define WATCH(m)                    __noop
    #define WATCHX(g,l,m)               __noop
#endif

#if defined(__WARN)
    #define WARN(c,m)                   WARNX(Def,c,0,m)
    #define WARNX(g,c,l,m)\
            if(c)\
            {\
                std::_tostringstream Out; \
                Out << m << std::ends;\
                dbgDiagGroup##g::Warn(l,Out.str().c_str(),_T(__FILE__),__LINE__);\
            }
#else
    #define WARN(c,m)                   __noop
    #define WARNX(g,c,l,m)              __noop
#endif

#endif  // INCLUDED_DEBUGTOOLS_CHECKS_H_
