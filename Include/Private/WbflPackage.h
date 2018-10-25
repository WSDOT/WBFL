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

#ifndef INCLUDED_PRIVATE_WBFLPACKAGE_H_
#define INCLUDED_PRIVATE_WBFLPACKAGE_H_

#pragma once

// Standard Include file for all of WBFL Packages.
// This file must be either directly or indirectly included into to
// every WBFL file.  The best way to do it is to include it as the
// first line of every source file, or put it in a header file that
// is included as the first line in every source file for a package.
//
// WARNING: Do not change this file unless it is absolutely necessary.
//          Any changes to this file will cause a system wide recompile.

#include <WBFLAll.h>
#include <WBFLVersion.h>

#define VC_EXTRALEAN

#ifndef STRICT
#define STRICT
#endif

#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxpriv.h>        // Private MFC extensions


#include <WBFLDebug.h>
#include <WBFLTest.h>

#include <System\AutoLib.h>
#include <System\Log.h>
#include <tchar.h>

#endif // INCLUDED_PRIVATE_WBFLPACKAGE_H_
