#ifndef INCLUDED_WBFLDEBUG_H_
#define INCLUDED_WBFLDEBUG_H_
///////////////////////////////////////////////////////////////////////
// WBFL - Washington Bridge Foundation Libraries
// Copyright © 1999-2022  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Library Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// 4500 3rd Ave SE, P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////


#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#if defined _DEBUG

// Enable full global checking if WBFL_DEBUG is defined
// otherise, define each one of these symbols individual to
// enable a certain part of the checking subsystem
#if defined WBFL_DEBUG
#undef __ASSERTVALID
#undef __CHECK
#undef __WATCH
#undef __WARN
#undef __PRECONDITION
#undef __CONFIRM
#undef SIMERR

#define __ASSERTVALID
#define __CHECK
#define __WATCH
#define __WARN
#define __PRECONDITION
#define __CONFIRM
#define SIMERR
#endif // WBFL_DEBUG

// unit testing is always enabled in debug builds
#undef _UNITTEST
#define _UNITTEST

// STL iterator checking and debugging must be enabled
#if defined _HAS_ITERATOR_DEBUGGING
#if _HAS_ITERATOR_DEBUGGING == 0
#error STL iterator debugging must be enabled, set _HAS_ITERATOR_DEBUGGING = 1
#endif 
#endif

#if defined _SECURE_SCL
#if _SECURE_SCL == 0
#error STL iterator debugging must be enabled, set _SECURE_SCL = 1
#endif 
#endif

#else  // _DEBUG

// Release Builds
#undef _UNITTEST
#undef __PRECONDITION

#define _UNITTEST
#define __PRECONDITION

#endif // _DEBUG

#include <System\Debug.h>

// Compile time reminder message
// See Windows Developer's Journal, September 1997, pg 45
// Usage
// #pragma Reminder( "This is a reminder" )
//
// Don't use Warning or Error in your reminder message. This will
// cause the IDE to count them as real messages and could stop the
// build process.
#define Stringize(L) #L
#define MakeString(M,L) M(L)
#define $LINE MakeString( Stringize, __LINE__ )
#define ReminderMsg __FILE__ "(" $LINE ") : Reminder: "
#define Reminder(msg) message( ReminderMsg msg )

#endif // INCLUDED_WBFLDEBUG_H_