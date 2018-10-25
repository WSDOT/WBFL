///////////////////////////////////////////////////////////////////////
// Unit Test - Test driver for WBFLUnits library
// Copyright © 1999-2018  Washington State Department of Transportation
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

#include <initguid.h>
#include <WBFLUnitServer_i.c>

#include "TestUnitServer.h"
#include "TestUnitModeController.h"
#include "TestDisplayUnitMgr.h"
#include "TestDisplayUnitMgr2.h"
#include "TestDisplayUnitGroup.h"
#include "TestDisplayUnit2.h"
#include "TestDisplayUnitFormatter.h"
#include "TestAnnotatedDisplayUnitFormatter.h"
#include "TestUnitTypes.h"
#include "TestUnitType.h"
#include "TestUnits.h"
#include "TestUnit.h"
#include "TestUnitSystem.h"
#include "TestAppUnitSystem.h"
#include "TestDocUnitSystem.h"
#include "TestCustomBaseUnits.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CComModule _Module;

int main(int argc, TCHAR* argv[])
{
   ::CoInitialize(nullptr);

   {
      CTestUnitServer::Test();
      CTestUnitModeController::Test();
      CTestUnit::Test();
      CTestUnits::Test();
      CTestUnitType::Test();
      CTestUnitTypes::Test();
      CTestUnitSystem::Test();

      CTestDisplayUnitFormatter::Test();
      CTestAnnotatedDisplayUnitFormatter::Test();
      CTestDisplayUnit::Test();
      CTestDisplayUnitGroup::Test();
      CTestDisplayUnitMgr::Test();

      CTestDisplayUnitMgr2::Test();
      CTestAppUnitSystem::Test();
      CTestDocUnitSystem::Test();

      CTestCustomBaseUnits::Test();
   }

   ::CoUninitialize();
	return 0;
}
