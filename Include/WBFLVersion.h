///////////////////////////////////////////////////////////////////////
// Washington Bridge Foundation Libraries - The foundation of
// high quality structural engineering applications
//
// Copyright © 1999-2026  Washington State Department of Transportation
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

#include <targetver.h>

// The BridgeLink version number, major.minor.hotfix.build (BridgeLink\devdocs\Version Numbers.md).
// This is the one place it is set. Everything else gets it from here:
//    the C++ code (_WBFL_VERSION),
//    BridgeLink\GetVersion.bat (BuildRelease.bat, PublishDocumentation.bat, Tag.bat,
//       PGSuper\Configurations\PublishConfigurations.bat),
//    the BridgeLink installer (BridgeLinkInstaller.wixproj and Installer\Scripts\Build*Fragments.js), which read
//       WBFL_VERSION_STRING,
//    the version resources: each project's VS_VERSION_INFO is in its res\<name>.rc2 file (which the resource
//       editor doesn't change) and uses these macros.
// BridgeLink\CheckVersions.ps1 checks that the binaries in the release file tree and in the installer have this version.
// Beta or official release is set by _BETA_VERSION in BridgeLink\Include\BridgeLinkVersion.h.
//
// Change the numbers and the string together: the resource compiler can't build a string from the numbers,
// so the string is written out, and the check below stops the compile when the two don't match.
#define WBFL_VERSION_MAJOR   10
#define WBFL_VERSION_MINOR   0
#define WBFL_VERSION_HOTFIX  0
#define WBFL_VERSION_BUILD   1
#define WBFL_VERSION_STRING  "10.0.0.1"

// major.minor.hotfix as one number (e.g. 1000 for 10.0.0, 710 for 7.1.0), for #if tests
#ifndef _WBFL_VERSION
#define _WBFL_VERSION (WBFL_VERSION_MAJOR*100 + WBFL_VERSION_MINOR*10 + WBFL_VERSION_HOTFIX)
#endif

#if defined(__cplusplus) && !defined(RC_INVOKED)
#define WBFL_VERSION_STRINGIZE_(x) #x
#define WBFL_VERSION_STRINGIZE(x) WBFL_VERSION_STRINGIZE_(x)
namespace WBFL_VersionCheck
{
   constexpr bool IsSameString(const char* a, const char* b) { return *a == *b && (*a == '\0' || IsSameString(a + 1, b + 1)); }
}
static_assert(WBFL_VersionCheck::IsSameString(WBFL_VERSION_STRING,
   WBFL_VERSION_STRINGIZE(WBFL_VERSION_MAJOR) "." WBFL_VERSION_STRINGIZE(WBFL_VERSION_MINOR) "."
   WBFL_VERSION_STRINGIZE(WBFL_VERSION_HOTFIX) "." WBFL_VERSION_STRINGIZE(WBFL_VERSION_BUILD)),
   "WBFLVersion.h: WBFL_VERSION_STRING doesn't match WBFL_VERSION_MAJOR.MINOR.HOTFIX.BUILD");
#endif
