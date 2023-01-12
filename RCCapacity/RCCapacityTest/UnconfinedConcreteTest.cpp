///////////////////////////////////////////////////////////////////////
// RCCapacity Test - Test driver for RCCapacity library
// Copyright © 1999-2023  Washington State Department of Transportation
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

// UnconfinedConcreteTest.cpp: implementation of the CUnconfinedConcreteTest class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UnconfinedConcreteTest.h"
#include "GeneralTests.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUnconfinedConcreteTest::CUnconfinedConcreteTest()
{

}

CUnconfinedConcreteTest::~CUnconfinedConcreteTest()
{

}

void CUnconfinedConcreteTest::Test()
{
   CComPtr<IUnconfinedConcrete> concrete;
   TRY_TEST(concrete.CoCreateInstance(CLSID_UnconfinedConcrete),S_OK);

   Float64 val;
   TRY_TEST( concrete->put_fc(0), E_INVALIDARG);
   TRY_TEST( concrete->put_fc(-10), E_INVALIDARG);
   TRY_TEST( concrete->put_fc(13789514.59), S_OK); // 2 KSI
   TRY_TEST( concrete->put_fc(20684271.88), S_OK);         // 3 KSI
   TRY_TEST( concrete->put_fc(89631844.81), S_OK);         // 13 KSI
   TRY_TEST( concrete->put_fc(117210874), S_OK);   // 17 KSI
   TRY_TEST( concrete->get_fc(nullptr), E_POINTER );

   TRY_TEST(concrete->put_fc(89631844.81), S_OK);
   TRY_TEST(concrete->get_fc(&val), S_OK);
   TRY_TEST( IsEqual(val,89631844.810000), true);

   TestISupportUnitServer(concrete);

   CComQIPtr<IStressStrain> ss(concrete);
   TRY_TEST( ss != nullptr, true );

   TRY_TEST( ss->ComputeStress(0.00764,nullptr), E_POINTER);
   TRY_TEST( ss->ComputeStress(0.00764,&val), S_OK );
   TRY_TEST( IsEqual(val,0.00), true );
   TRY_TEST( ss->ComputeStress(-0.00764,&val), S_FALSE ); // exceeds concrete crushing strai -0.003
   TRY_TEST( IsEqual(val, -78333650.161053866), true );
   TRY_TEST( ss->ComputeStress(-0.00245,&val), S_OK );
   TRY_TEST( IsEqual(val,-86277115.080388337), true );

   CComQIPtr<ISupportErrorInfo> eInfo(ss);
   TRY_TEST( eInfo != nullptr, true);
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo(IID_IUnconfinedConcrete), S_OK);
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo(IID_IStressStrain),       S_OK);
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo(IID_IStructuredStorage2), S_OK);
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo(IID_ISupportErrorInfo),   S_FALSE);
}
