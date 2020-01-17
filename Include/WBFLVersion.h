///////////////////////////////////////////////////////////////////////
// Washington Bridge Foundation Libraries - The foundation of
// high quality structural engineering applications
//
// Copyright © 1999-2020  Washington State Department of Transportation
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

#pragma once

#include <sdkddkver.h>

#ifndef _WBFL_VERSION
#define _WBFL_VERSION 445 // version 4.4.5
#endif 


// The following macros define the minimum required platform.  The minimum required platform
// is the earliest version of Windows, Internet Explorer etc. that has the necessary features to run 
// your application.  The macros work by enabling all features available on platform versions up to and 
// including the version specified.

// Modify the following defines if you have to target a platform prior to the ones specified below.
// Refer to MSDN for the latest info on corresponding values for different platforms.

#if defined _WIN64

// 64 bit Windows... target Windows Vista
#ifndef WINVER
#define WINVER 0x0600 // minimum system requirements Windows Vista
#endif

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600 // minimum system requirements Windows Vista
#endif

#ifndef _WIN32_WINDOWS
#define _WIN32_WINDOWS 0x0600  // minimum system requirements Windows Vista
#endif

#else

// 32 bit Windows... target Windows XP
#ifndef WINVER
#define WINVER _WIN32_WINNT_WINXP // minimum system requirements Windows XP
#endif

#ifndef _WIN32_WINNT
#define _WIN32_WINNT _WIN32_WINNT_WINXP // minimum system requirements Windows XP
#endif

#ifndef _WIN32_WINDOWS
#define _WIN32_WINDOWS _WIN32_WINNT_WINXP  // minimum system requirements Windows XP
#endif

#endif


#ifndef _WIN32_IE
#define _WIN32_IE _WIN32_IE_IE55  // min version of IE is 5.5      // Change this to the appropriate value to target other versions of IE.
#endif
