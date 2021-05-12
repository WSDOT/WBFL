///////////////////////////////////////////////////////////////////////
// LBAM Live Load Test - Test driver for LBAM analysis library
// Copyright © 1999-2021  Washington State Department of Transportation
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

// LiveLoadTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TestVehicularLoadContext.h"
#include "TestBasicVehicularResponse.h"
#include "TestLiveLoadConfiguration.h"
#include "TestLiveLoadModelResponse.h"
#include "Solleks.h"
#include "TestSimpleTwoSpan.h"
#include "TestDistributionFactorStrategy.h"
#include "TestResults.h"

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

      TestResults::Test();

      TestDistributionFactorStrategy::Test();

      TestLiveLoadConfiguration::Test();

      TestVehicularLoadContext::Test();
      TestBasicVehicularResponse::Test();

      TestLiveLoadModelResponse::Test();

      Solleks::Test();
      TestSimpleTwoSpan::Test();

   }

   ::CoUninitialize();

   return 0;
}
