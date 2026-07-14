///////////////////////////////////////////////////////////////////////
// WBFL - Washington Bridge Foundation Libraries
// Copyright � 1999-2026  Washington State Department of Transportation
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

// Shared "minimum required platform" header. Include this FIRST, before any header that pulls in
// <windows.h> (directly, or via ATL/MFC), so the Windows SDK doesn't emit "_WIN32_WINNT not defined.
// Defaulting to _WIN32_WINNT_MAXVER" and silently pick a default on its own.
//
// _WIN32_WINNT_MAXVER always tracks the newest version the installed Windows SDK knows about. It has
// been 0x0A00 (Windows 10) for the entire Windows 10/11 SDK era - Windows 11 API differences are gated
// by NTDDI_VERSION sub-values, not _WIN32_WINNT - so this is not expected to drift across machines with
// any currently-supported SDK. If a future SDK does raise it, every WBFL project picks up the new value
// together the next time it's rebuilt, since they all funnel through this one header.

#pragma once

#include <WinSDKVer.h>
// Guarded: some headers (COM #import-generated wrappers, MIDL-generated RPC headers) pull in
// <windows.h> before this file gets included, which silently defaults _WIN32_WINNT on its own.
// An unconditional #define here would then warn C4005 on redefinition even though the value agrees.
#ifndef _WIN32_WINNT
#define _WIN32_WINNT _WIN32_WINNT_MAXVER
#endif
#include <SDKDDKVer.h>
