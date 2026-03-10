// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <initguid.h>
#include "WBFLLoading_i.c"
#include "WBFLTools_i.c"

#include "TestPointLoad.h" 
#include "TestDistributedLoad.h"
#include "TestTemperatureLoad.h"
#include "TestStrainLoad.h" 
#include "TestSettlementLoad.h" 
#include "TestAxle.h"
#include "TestVehicularLoad.h"
#include "TestLoadGroup.h"
#include "TestLoadCase.h"
#include "TestLoadCombination.h"



CComModule _Module;

int main(int argc, char* argv[])
{
   ::CoInitialize(nullptr);
   {
      CTestPointLoad::Test();
      CTestDistributedLoad::Test();
      CTestSettlementLoad::Test();
      CTestTemperatureLoad::Test();
      CTestStrainLoad::Test();

      CTestAxle::Test();
      CTestVehicularLoad::Test();

      CTestLoadGroup::Test();
      CTestLoadCase::Test();
      CTestLoadCombination::Test();
   }

   ::CoUninitialize();

	return 0;
}
