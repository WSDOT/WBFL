///////////////////////////////////////////////////////////////////////
// LBAM Test - Test driver for LBAM analysis library
// Copyright © 1999-2025  Washington State Department of Transportation
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
#include "TestStressPoint.h"
#include "TestCrossSection.h"
#include "TestSuperstructureMember.h"
#include "TestSupport.h"
#include "TestTemporarySupport.h"
#include "TestSpan.h"
#include "TestDistributionFactor.h"
#include "TestPOI.h"
#include "TestStage.h"
#include "TestLoadGroup.h"
#include "TestPointLoad.h" 
#include "TestStrainLoad.h" 
#include "TestSettlementLoad.h" 
#include "TestDistributedLoad.h"
#include "TestTemperatureLoad.h"
#include "TestModel.h"
#include "TestAxle.h"
#include "TestVehicularLoad.h"
#include "TestLiveLoadModel.h"
#include "TestLoadCase.h"
#include "TestLoadCombination.h"

#include <initguid.h>
#include <WBFLTools_i.c>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CComModule _Module;

int main(int argc, char* argv[])
{
   ::CoInitialize(nullptr);
   {

      CTestStressPoint::Test();

      CTestCrossSection::Test();
      CTestSuperstructureMember::Test();
      CTestSupport::Test();
      CTestTemporarySupport::Test(); 
      CTestSpan::Test();

      CTestDistributionFactor::Test();

      CTestPOI::Test();

      CTestStage::Test();
      CTestLoadGroup::Test();

      CTestLoadCase::Test();
      CTestLoadCombination::Test();

      CTestPointLoad::Test();
      CTestSettlementLoad::Test();
      CTestDistributedLoad::Test();
      CTestTemperatureLoad::Test();
      CTestStrainLoad::Test();

      CTestAxle::Test();

      CTestVehicularLoad::Test();
      CTestLiveLoadModel::Test();

      CTestModel::Test();
   }

   ::CoUninitialize();

	return 0;
}
