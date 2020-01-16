///////////////////////////////////////////////////////////////////////
// Tools Test - Test driver for WBFLTools library
// Copyright © 1999-2020  Washington State Department of Transportation
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

// TestMohrCircle.cpp: implementation of the CTestMohrCircle class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestMohrCircle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestMohrCircle::CTestMohrCircle()
{

}

CTestMohrCircle::~CTestMohrCircle()
{

}

void CTestMohrCircle::Test()
{
   CComPtr<IMohrCircle> mc;
   TRY_TEST( mc.CoCreateInstance( CLSID_MohrCircle ), S_OK );

   TRY_TEST(mc->put_Sii(12), S_OK);
   TRY_TEST(mc->put_Sjj(4),  S_OK);
   TRY_TEST(mc->put_Sij(3),  S_OK);

   Float64 val;
   TRY_TEST( mc->get_Sii(nullptr), E_POINTER );
   TRY_TEST( mc->get_Sjj(nullptr), E_POINTER );
   TRY_TEST( mc->get_Sij(nullptr), E_POINTER );

   TRY_TEST( mc->get_Sii(&val), S_OK );
   TRY_TEST( IsEqual(val,12.0), true );

   TRY_TEST( mc->get_Sjj(&val), S_OK );
   TRY_TEST( IsEqual(val,4.0), true );

   TRY_TEST( mc->get_Sij(&val), S_OK );
   TRY_TEST( IsEqual(val,3.0), true );

   TRY_TEST( mc->get_Center(nullptr), E_POINTER );
   TRY_TEST( mc->get_Center(&val), S_OK );
   TRY_TEST( IsEqual(val,8.0), true );

   TRY_TEST( mc->get_Radius(nullptr), E_POINTER );
   TRY_TEST( mc->get_Radius(&val), S_OK );
   TRY_TEST( IsEqual(val,5.0), true );

   TRY_TEST( mc->get_Smax(nullptr), E_POINTER );
   TRY_TEST( mc->get_Smax(&val), S_OK );
   TRY_TEST( IsEqual(val,13.0), true );

   TRY_TEST( mc->get_Smin(nullptr), E_POINTER );
   TRY_TEST( mc->get_Smin(&val), S_OK );
   TRY_TEST( IsEqual(val,3.0), true );

   TRY_TEST( mc->get_Tmax(nullptr), E_POINTER );
   TRY_TEST( mc->get_Tmax(&val), S_OK );
   TRY_TEST( IsEqual(val,5.0), true );

   TRY_TEST( mc->get_PrincipleDirection(nullptr), E_POINTER );
   TRY_TEST( mc->get_PrincipleDirection(&val), S_OK );
   TRY_TEST( IsEqual(val,M_PI*18.43/180.,0.02), true );

   Float64 s1,s2,s12;
   TRY_TEST( mc->ComputeState(M_PI*15.0/180.0,nullptr,&s2,&s12), E_POINTER );
   TRY_TEST( mc->ComputeState(M_PI*15.0/180.0,&s1,nullptr,&s12), E_POINTER );
   TRY_TEST( mc->ComputeState(M_PI*15.0/180.0,&s1,&s2,nullptr),  E_POINTER );
   TRY_TEST( mc->ComputeState(M_PI*15.0/180.0,&s1,&s2,&s12),  S_OK );
   TRY_TEST( IsEqual(s1,12.964,0.002), true );
   TRY_TEST( IsEqual(s2, 3.036,0.002), true );
   TRY_TEST( IsEqual(s12,0.598,0.002), true );

   // Test special case of radius = 0
   mc->put_Sii(10);
   mc->put_Sjj(10);
   mc->put_Sij(0);

   mc->get_Radius(&val);
   TRY_TEST( IsZero(val), true );
   mc->get_PrincipleDirection(&val);
   TRY_TEST( IsZero(val), true );
}
