///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
// Copyright © 1999-2016  Washington State Department of Transportation
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

#if defined VBA_BUILD
#if defined _WIN64

#if defined _DEBUG
#include <x64\VBA_Debug\_WBFLTypes.h>
#else // _DEBUG
#include <x64\VBA_Release\_WBFLTypes.h>
#endif // _DEBUG

#else // _WIN64

#if defined _DEBUG
#include <Win32\VBA_Debug\_WBFLTypes.h>
#else // _DEBUG
#include <Win32\VBA_Release\_WBFLTypes.h>
#endif // _DEBUG

#endif // _WIN64

#else // VBA_BUILD

#if defined _WIN64

#if defined _DEBUG
#include <x64\Debug\_WBFLTypes.h>
#else
#include <x64\Release\_WBFLTypes.h>
#endif

#else

#if defined _DEBUG
#include <Win32\Debug\_WBFLTypes.h>
#else
#include <Win32\Release\_WBFLTypes.h>
#endif

#endif // _WIN64

#endif // VBA_BUILD