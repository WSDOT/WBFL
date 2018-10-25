///////////////////////////////////////////////////////////////////////
// RCCapacity Test - Test driver for RCCapacity library
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

// RCSolutionTest.cpp: implementation of the CRCSolutionTest class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RCSolutionTest.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRCSolutionTest::CRCSolutionTest()
{

}

CRCSolutionTest::~CRCSolutionTest()
{

}

void CRCSolutionTest::Test()
{
   CComPtr<IRCSolution> soln;
   TRY_TEST(soln.CoCreateInstance(CLSID_RCSolution),S_OK);

   TRY_TEST(soln->InitSolution(1,2,3,4,5,6,7,8,VARIANT_FALSE),S_OK);

   Float64 val;
   TRY_TEST( soln->get_Mn(nullptr),E_POINTER);
   TRY_TEST( soln->get_Mn(&val), S_OK);
   TRY_TEST( IsEqual(val,1.0), true);

   TRY_TEST( soln->get_NeutralAxisDepth(nullptr),E_POINTER);
   TRY_TEST( soln->get_NeutralAxisDepth(&val), S_OK);
   TRY_TEST( IsEqual(val,2.0), true);

   TRY_TEST( soln->get_fps(nullptr),E_POINTER);
   TRY_TEST( soln->get_fps(&val), S_OK);
   TRY_TEST( IsEqual(val,3.0), true);

   TRY_TEST( soln->get_Cflange(nullptr),E_POINTER);
   TRY_TEST( soln->get_Cflange(&val), S_OK);
   TRY_TEST( IsEqual(val,4.0), true);

   TRY_TEST( soln->get_Cweb(nullptr),E_POINTER);
   TRY_TEST( soln->get_Cweb(&val), S_OK);
   TRY_TEST( IsEqual(val,5.0), true);

   TRY_TEST( soln->get_T(nullptr),E_POINTER);
   TRY_TEST( soln->get_T(&val), S_OK);
   TRY_TEST( IsEqual(val,6.0), true);

   TRY_TEST( soln->get_Yflange(nullptr),E_POINTER);
   TRY_TEST( soln->get_Yflange(&val), S_OK);
   TRY_TEST( IsEqual(val,7.0), true);

   TRY_TEST( soln->get_Yweb(nullptr),E_POINTER);
   TRY_TEST( soln->get_Yweb(&val), S_OK);
   TRY_TEST( IsEqual(val,8.0), true);

   VARIANT_BOOL bVal;
   TRY_TEST( soln->get_IsOverReinforced(nullptr),E_POINTER);
   TRY_TEST( soln->get_IsOverReinforced(&bVal), S_OK);
   TRY_TEST( bVal,VARIANT_FALSE);

   CComQIPtr<ISupportErrorInfo> eInfo(soln);
   TRY_TEST( eInfo != nullptr, true);
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo(IID_IRCSolution),         S_OK);
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo(IID_ISupportErrorInfo),   S_FALSE);
}
