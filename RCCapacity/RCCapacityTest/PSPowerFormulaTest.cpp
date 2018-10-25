///////////////////////////////////////////////////////////////////////
// RCCapacity Test - Test driver for RCCapacity library
// Copyright © 1999-2010  Washington State Department of Transportation
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

// PSPowerFormulaTest.cpp: implementation of the CPSPowerFormulaTest class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PSPowerFormulaTest.h"
#include "GeneralTests.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPSPowerFormulaTest::CPSPowerFormulaTest()
{

}

CPSPowerFormulaTest::~CPSPowerFormulaTest()
{

}

void CPSPowerFormulaTest::Test()
{
   CComPtr<IStressStrain> ps;
   TRY_TEST(ps.CoCreateInstance(CLSID_PSPowerFormula),S_OK);

   TestISupportUnitServer(ps);

   CComQIPtr<IStressStrain> ss(ps);
   TRY_TEST( ss != NULL, true );

   Float64 val;
   TRY_TEST( ss->ComputeStress(0.00764,NULL), E_POINTER);
   TRY_TEST( ss->ComputeStress(0.00764,&val), S_OK );
   TRY_TEST( IsEqual(val,1446556950.5987,0.0001), true );
   TRY_TEST( ss->ComputeStress(-0.00764,&val), S_OK );
   TRY_TEST( IsEqual(val,-1446556950.5987,0.0001), true );
   TRY_TEST( ss->ComputeStress(0.1,&val), S_OK );
   TRY_TEST( IsEqual(val,1861584469.1559,0.0001), true );
   TRY_TEST( ss->ComputeStress(-0.1,&val), S_OK );
   TRY_TEST( IsEqual(val,-1861584469.1559,0.0001), true );

   CComQIPtr<ISupportErrorInfo> eInfo(ss);
   TRY_TEST( eInfo != NULL, true);
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo(IID_IStressStrain),       S_OK);
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo(IID_IStructuredStorage2), S_OK);
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo(IID_ISupportErrorInfo),   S_FALSE);
}
