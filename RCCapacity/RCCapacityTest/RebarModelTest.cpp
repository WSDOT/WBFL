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

// RebarModelTest.cpp: implementation of the CRebarModelTest class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RebarModelTest.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRebarModelTest::CRebarModelTest()
{

}

CRebarModelTest::~CRebarModelTest()
{

}

void CRebarModelTest::Test()
{
   CComPtr<IRebarModel> rebar;
   TRY_TEST(rebar.CoCreateInstance(CLSID_RebarModel),S_OK);

   Float64 val;
   TRY_TEST( rebar->get_fy(nullptr), E_POINTER );
   TRY_TEST( rebar->get_fy(&val), S_OK );
   TRY_TEST( IsEqual(val,60.0), true );
   TRY_TEST( rebar->put_fy(-10), E_INVALIDARG );
   TRY_TEST( rebar->put_fy(  0), E_INVALIDARG );
   TRY_TEST( rebar->put_fy(val), S_OK );

   TRY_TEST( rebar->get_Es(nullptr), E_POINTER );
   TRY_TEST( rebar->get_Es(&val), S_OK );
   TRY_TEST( IsEqual(val,29000.0), true );
   TRY_TEST( rebar->put_Es(-10), E_INVALIDARG );
   TRY_TEST( rebar->put_Es(  0), E_INVALIDARG );
   TRY_TEST( rebar->put_Es(val), S_OK );

   CComQIPtr<IStressStrain> ss(rebar);
   TRY_TEST( ss != nullptr, true );

   TRY_TEST( ss->ComputeStress(0.001,nullptr), E_POINTER);
   TRY_TEST( ss->ComputeStress(0.001,&val), S_OK );
   TRY_TEST( IsEqual(val,29.0), true );
   TRY_TEST( ss->ComputeStress(-0.001,&val), S_OK );
   TRY_TEST( IsEqual(val,-29.0), true );
   TRY_TEST( ss->ComputeStress(0.1,&val), S_FALSE ); // strain exceeds tensile fracture strain
   TRY_TEST( IsEqual(val,60.0), true );
   TRY_TEST( ss->ComputeStress(-0.1,&val), S_OK );
   TRY_TEST( IsEqual(val,-60.0), true );

   CComQIPtr<ISupportErrorInfo> eInfo(rebar);
   TRY_TEST( eInfo != nullptr, true);
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo(IID_IRebarModel),         S_OK);
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo(IID_IStressStrain),       S_OK);
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo(IID_IStructuredStorage2), S_OK);
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo(IID_ISupportErrorInfo),   S_FALSE);
}
