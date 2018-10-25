///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2017  Washington State Department of Transportation
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
#include <WBFLFem2d_i.c>

#include "TestJoint.h"
#include "TestMember.h"
#include "TestJointLoad.h"
#include "TestJointDisplacement.h"
#include "TestPointLoad.h"
#include "TestDistributedLoad.h"
#include "TestPOI.h"
#include "TestSimpleBeamWithJointLoad.h"
#include "TestSimpleBeamWithPointLoad.h"
#include "TestSimpleBeamWithPointLoad2.h"
#include "TestSimpleBeamWithDistributedLoad.h"
#include "TestBarWithDistributedLoad.h"
#include "TestFrameWithDistributedLoad.h"
#include "TestFrameWithReleases.h"
#include "TestTrussSennett2-11.h"
#include "TestFrameSennett3-17.h"
#include "TestSupportMovement.h"
#include "TestMemberStrains.h"
#include "TestMemberStrains2.h"
#include "TestAxialLoads.h"
#include "TestInstability.h"
#include "TestPersistence.h"
#include "TestPointerFail.h"
#include "TestISupportErrorInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CComModule _Module;

#define TEST_ME(_class) \
   CComObject<_class>* p##_class; \
   CComObject<_class>::CreateInstance(&p##_class); \
   p##_class->AddRef(); \
   p##_class->Test(); \
   p##_class->Release()

int main(int argc, TCHAR* argv[])
{
  ::CoInitialize(NULL);
   {

      TEST_ME(CTestJoint);

      TEST_ME(CTestMember);
      TEST_ME(CTestJointLoad);
      TEST_ME(CTestJointDeflection);
      TEST_ME(CTestPointLoad);
      TEST_ME(CTestPOI);
      TEST_ME(CTestDistributedLoad);

      // Calculation verifications
      TEST_ME(CTestSimpleBeamWithJointLoad);
      TEST_ME(CTestSimpleBeamWithPointLoad);
      TEST_ME(CTestSimpleBeamWithPointLoad2);
      TEST_ME(CTestFrameWithDistributedLoad);
      TEST_ME(CTestTrussSennett2_11);
      TEST_ME(CTestFrameSennett3_17);

      TEST_ME(CTestSupportMovement);
      TEST_ME(CTestMemberStrains);
      TEST_ME(CTestMemberStrains2);
      TEST_ME(CTestSimpleBeamWithDistributedLoad);
      TEST_ME(CTestBarWithDistributedLoad);
      TEST_ME(CTestAxialLoads);
      TEST_ME(CTestFrameWithReleases);

      // Error handling
      TEST_ME(CTestInstability);
      TEST_ME(CTestPointerFail);

      // persistence
      TEST_ME(CTestPersistence);
      TEST_ME(CTestISupportErrorInfo);

   }

   ::CoUninitialize();
	return 0;
}

