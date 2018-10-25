///////////////////////////////////////////////////////////////////////
// RCCapacity Test - Test driver for RCCapacity library
// Copyright © 1999-2016  Washington State Department of Transportation
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

// RCBeamTest.cpp: implementation of the CRCBeamTest class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RCBeamTest.h"
#include "GeneralTests.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRCBeamTest::CRCBeamTest()
{

}

CRCBeamTest::~CRCBeamTest()
{

}

void CRCBeamTest::Test()
{
   CComPtr<IRCBeam> beam;
   TRY_TEST(beam.CoCreateInstance(CLSID_RCBeam),S_OK);

   Float64 val;
   TRY_TEST(beam->put_Aps(-10),E_INVALIDARG);
   TRY_TEST(beam->put_Aps(10), S_OK);
   TRY_TEST(beam->get_Aps(NULL), E_POINTER);
   TRY_TEST(beam->get_Aps(&val), S_OK);
   TRY_TEST( IsEqual(val,10.0), true );

   TRY_TEST(beam->put_As(-10),E_INVALIDARG);
   TRY_TEST(beam->put_As(10), S_OK);
   TRY_TEST(beam->get_As(NULL), E_POINTER);
   TRY_TEST(beam->get_As(&val), S_OK);
   TRY_TEST( IsEqual(val,10.0), true );

   TRY_TEST(beam->put_b(-10),E_INVALIDARG);
   TRY_TEST(beam->put_b(10), S_OK);
   TRY_TEST(beam->get_b(NULL), E_POINTER);
   TRY_TEST(beam->get_b(&val), S_OK);
   TRY_TEST( IsEqual(val,10.0), true );

   TRY_TEST(beam->put_bw(-10),E_INVALIDARG);
   TRY_TEST(beam->put_bw(10), S_OK);
   TRY_TEST(beam->get_bw(NULL), E_POINTER);
   TRY_TEST(beam->get_bw(&val), S_OK);
   TRY_TEST( IsEqual(val,10.0), true );

   TRY_TEST(beam->put_dps(-10),E_INVALIDARG);
   TRY_TEST(beam->put_dps(10), S_OK);
   TRY_TEST(beam->get_dps(NULL), E_POINTER);
   TRY_TEST(beam->get_dps(&val), S_OK);
   TRY_TEST( IsEqual(val,10.0), true );

   TRY_TEST(beam->put_ds(-10),E_INVALIDARG);
   TRY_TEST(beam->put_ds(10), S_OK);
   TRY_TEST(beam->get_ds(NULL), E_POINTER);
   TRY_TEST(beam->get_ds(&val), S_OK);
   TRY_TEST( IsEqual(val,10.0), true );

   TRY_TEST(beam->put_Eps(-10),E_INVALIDARG);
   TRY_TEST(beam->put_Eps(0),E_INVALIDARG);
   TRY_TEST(beam->put_Eps(10), S_OK);
   TRY_TEST(beam->get_Eps(NULL), E_POINTER);
   TRY_TEST(beam->get_Eps(&val), S_OK);
   TRY_TEST( IsEqual(val,10.0), true );

   TRY_TEST(beam->put_Es(-10),E_INVALIDARG);
   TRY_TEST(beam->put_Es(0),E_INVALIDARG);
   TRY_TEST(beam->put_Es(10), S_OK);
   TRY_TEST(beam->get_Es(NULL), E_POINTER);
   TRY_TEST(beam->get_Es(&val), S_OK);
   TRY_TEST( IsEqual(val,10.0), true );

   TRY_TEST(beam->put_FcBeam(-10),E_INVALIDARG);
   TRY_TEST(beam->put_FcBeam(0),E_INVALIDARG);
   TRY_TEST(beam->put_FcBeam(10), S_OK);
   TRY_TEST(beam->get_FcBeam(NULL), E_POINTER);
   TRY_TEST(beam->get_FcBeam(&val), S_OK);
   TRY_TEST( IsEqual(val,10.0), true );

   TRY_TEST(beam->put_FcSlab(-10),E_INVALIDARG);
   TRY_TEST(beam->put_FcSlab(0),E_INVALIDARG);
   TRY_TEST(beam->put_FcSlab(10), S_OK);
   TRY_TEST(beam->get_FcSlab(NULL), E_POINTER);
   TRY_TEST(beam->get_FcSlab(&val), S_OK);
   TRY_TEST( IsEqual(val,10.0), true );

   TRY_TEST(beam->put_fpe(-10),E_INVALIDARG);
   TRY_TEST(beam->put_fpe(10), S_OK);
   TRY_TEST(beam->get_fpe(NULL), E_POINTER);
   TRY_TEST(beam->get_fpe(&val), S_OK);
   TRY_TEST( IsEqual(val,10.0), true );

   TRY_TEST(beam->put_fpu(-10),E_INVALIDARG);
   TRY_TEST(beam->put_fpu(10), S_OK);
   TRY_TEST(beam->get_fpu(NULL), E_POINTER);
   TRY_TEST(beam->get_fpu(&val), S_OK);
   TRY_TEST( IsEqual(val,10.0), true );

   TRY_TEST(beam->put_fpy(-10),E_INVALIDARG);
   TRY_TEST(beam->put_fpy(10), S_OK);
   TRY_TEST(beam->get_fpy(NULL), E_POINTER);
   TRY_TEST(beam->get_fpy(&val), S_OK);
   TRY_TEST( IsEqual(val,10.0), true );

   TRY_TEST(beam->put_fy(-10),E_INVALIDARG);
   TRY_TEST(beam->put_fy(10), S_OK);
   TRY_TEST(beam->get_fy(NULL), E_POINTER);
   TRY_TEST(beam->get_fy(&val), S_OK);
   TRY_TEST( IsEqual(val,10.0), true );

   TRY_TEST(beam->put_h(-10),E_INVALIDARG);
   TRY_TEST(beam->put_h(10), S_OK);
   TRY_TEST(beam->get_h(NULL), E_POINTER);
   TRY_TEST(beam->get_h(&val), S_OK);
   TRY_TEST( IsEqual(val,10.0), true );

   TRY_TEST(beam->put_hf(-10),E_INVALIDARG);
   TRY_TEST(beam->put_hf(10), S_OK);
   TRY_TEST(beam->get_hf(NULL), E_POINTER);
   TRY_TEST(beam->get_hf(&val), S_OK);
   TRY_TEST( IsEqual(val,10.0), true );

   TestISupportUnitServer(beam);

   CComQIPtr<ISupportErrorInfo> eInfo(beam);
   TRY_TEST( eInfo != NULL, true);
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo(IID_IRCBeam),             S_OK);
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo(IID_IStructuredStorage2), S_OK);
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo(IID_ISupportErrorInfo),   S_FALSE);
}