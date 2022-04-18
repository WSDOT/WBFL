///////////////////////////////////////////////////////////////////////
// Tools Test - Test driver for WBFLTools library
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
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "TestMohrCircle.h"
#include "TestStructuredStorage2.h"

#include <initguid.h>
#include <WBFLTools_i.c>

#if defined _DEBUG
#if defined VBA_BUILD
#if defined _WIN64
#include "StorageTest\x64\VBA_Debug\StorageTest_i.c"
#else
#include "StorageTest\Win32\VBA_Debug\StorageTest_i.c"
#endif
#else
#if defined _WIN64
#include "StorageTest\x64\Debug\StorageTest_i.c"
#else
#include "StorageTest\Win32\Debug\StorageTest_i.c"
#endif
#endif
#else
#if defined VBA_BUILD
#if defined _WIN64
#include "StorageTest\x64\VBA_Release\StorageTest_i.c"
#else
#include "StorageTest\Win32\VBA_Release\StorageTest_i.c"
#endif
#else
#if defined _WIN64
#include "StorageTest\x64\Release\StorageTest_i.c"
#else
#include "StorageTest\Win32\Release\StorageTest_i.c"
#endif
#endif
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int main(int argc, LPTSTR  argv[])
{
   ::CoInitialize(nullptr);

   CTestMohrCircle::Test();
   CTestStructuredStorage2::Test();
   
   ::CoUninitialize();

	return 0;
}
