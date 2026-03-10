///////////////////////////////////////////////////////////////////////
// RCCapacity Test - Test driver for RCCapacity library
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

// UHPConcreteTest.cpp: implementation of the CUHPConcreteTest class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UHPConcreteTest.h"
#include "GeneralTests.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUHPConcreteTest::CUHPConcreteTest()
{

}

CUHPConcreteTest::~CUHPConcreteTest()
{

}

void CUHPConcreteTest::Test()
{
   CComPtr<IUHPConcrete> concrete;
   TRY_TEST(concrete.CoCreateInstance(CLSID_UHPConcrete),S_OK);

   concrete->put_ftcr(8273708.7518); // 1.2 KSI
   concrete->put_ftloc(8273708.7518); // 1.2 KSI
   concrete->put_etloc(0.0045);
   concrete->put_gamma(0.85);

   Float64 val;
   TRY_TEST( concrete->put_fc(0), E_INVALIDARG);
   TRY_TEST( concrete->put_fc(-10), E_INVALIDARG);
   TRY_TEST( concrete->put_fc(151684660.45), S_OK);   // 22 KSI
   TRY_TEST( concrete->get_fc(nullptr), E_POINTER );

   TRY_TEST(concrete->get_fc(&val), S_OK);
   TRY_TEST( IsEqual(val, 151684660.45), true);

   TestISupportUnitServer(concrete);

   CComQIPtr<IStressStrain> ss(concrete);
   TRY_TEST( ss != nullptr, true );

   // compute stress for tension strains

   // elastic region
   TRY_TEST( ss->ComputeStress(0.00005,nullptr), E_POINTER);
   TRY_TEST( ss->ComputeStress(0.00005,&val), S_OK );
   TRY_TEST( IsEqual(val, 2390168.2910847836), true );

   // plastic region
   TRY_TEST(ss->ComputeStress(0.0010, &val), S_OK);
   TRY_TEST(IsEqual(val, 0.85*8273708.7518), true); // gamma*ft,cr

   // after crack localization
   TRY_TEST(ss->ComputeStress(0.0050, &val), S_OK);
   TRY_TEST(IsEqual(val, 0.0), true);

   // compute stress for compression strain

   // elastic region
   TRY_TEST( ss->ComputeStress(-0.001,&val), S_OK );
   TRY_TEST( IsEqual(val, -47803365.821695670), true );

   // plastic region
   TRY_TEST(ss->ComputeStress(-0.003, &val), S_OK);
   TRY_TEST(IsEqual(val, -0.85*151684660.45), true); // stress plateau at alpha*f'c

   // after crushing
   TRY_TEST(ss->ComputeStress(-0.004, &val), S_FALSE); // -0.0035 is crushing
   TRY_TEST(IsEqual(val, -0.85 * 151684660.45), true);

   CComQIPtr<ISupportErrorInfo> eInfo(ss);
   TRY_TEST( eInfo != nullptr, true);
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo(IID_IUHPConcrete), S_OK);
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo(IID_IStressStrain),       S_OK);
   TRY_TEST(eInfo->InterfaceSupportsErrorInfo(IID_ISupportUnitServer), S_OK);
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo(IID_ISupportErrorInfo),   S_FALSE);
}
