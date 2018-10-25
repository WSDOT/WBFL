///////////////////////////////////////////////////////////////////////
// LBAM Analysis Test - Test driver for LBAM analysis library
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
#include <WBFLTools_i.c>

#include "TestInfluenceLine.h"
#include "TestTwoSpan.h"
#include "TestOverhang.h"
#include "TestFourStage.h"
#include "TestSpliced.h"
#include "TestStressPoints.h"

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

      HRESULT hr;

      CTestTwoSpan t2sp;
      hr = t2sp.Test();

      CTestOverhang toh;
      hr = toh.Test();

      CTestInfluenceLine til;
      hr = til.Test();

      CTestFourStage t4st;
      hr = t4st.Test();

      CTestSpliced tspl;
      hr = tspl.Test();

      TestStressPoints tsps;
      hr = tsps.Test();

   }

   ::CoUninitialize();

	return 0; 
}
