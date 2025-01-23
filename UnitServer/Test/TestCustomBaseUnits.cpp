///////////////////////////////////////////////////////////////////////
// Unit Test - Test driver for WBFLUnits library
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

// TestCustomBaseUnits.cpp: implementation of the CTestCustomBaseUnits class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestCustomBaseUnits.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestCustomBaseUnits::CTestCustomBaseUnits()
{

}

CTestCustomBaseUnits::~CTestCustomBaseUnits()
{

}

void CTestCustomBaseUnits::Test()
{
   CComPtr<IUnitServer> unitServer;
   unitServer.CoCreateInstance( CLSID_UnitServer );

   // Use base units of kip,ft,s,F,deg
   TRY_TEST(unitServer->SetSystemUnits(CComBSTR("kslug"),CComBSTR("ft"),CComBSTR("sec"),CComBSTR("F"),CComBSTR("deg")),S_OK);

   CComPtr<IUnitConvert> convert;
   unitServer->get_UnitConvert(&convert);

   Float64 val;

   // Test basic mechanism..
   TRY_TEST(convert->ConvertToBaseUnits(1.0,CComBSTR("kip"),&val),S_OK);
   TRY_TEST(IsEqual(val,1.0),true);

   TRY_TEST(convert->ConvertToBaseUnits(1000.0,CComBSTR("lbf"),&val),S_OK);
   TRY_TEST(IsEqual(val,1.0),true);

   TRY_TEST(convert->ConvertToBaseUnits(1.0,CComBSTR("kip-ft"),&val),S_OK);
   TRY_TEST(IsEqual(val,1.0),true);

   TRY_TEST(convert->ConvertToBaseUnits(1000.0,CComBSTR("lbf-ft"),&val),S_OK);
   TRY_TEST(IsEqual(val,1.0),true);

   TRY_TEST(convert->ConvertToBaseUnits(12.0,CComBSTR("kip-in"),&val),S_OK);
   TRY_TEST(IsEqual(val,1.0),true);

   TRY_TEST(convert->ConvertToBaseUnits(144.0,CComBSTR("in^2"),&val),S_OK);
   TRY_TEST(IsEqual(val,1.0),true);

   TRY_TEST(convert->ConvertToBaseUnits(1728.0,CComBSTR("in^3"),&val),S_OK);
   TRY_TEST(IsEqual(val,1.0),true);

   TRY_TEST(convert->ConvertToBaseUnits(32.0,CComBSTR("F"),&val),S_OK);
   TRY_TEST(IsEqual(val,32.0),true);

   TRY_TEST(convert->ConvertToBaseUnits(0.0,CComBSTR("C"),&val),S_OK);
   TRY_TEST(IsEqual(val,32.0),true);

   TRY_TEST(convert->ConvertToBaseUnits(45.0,CComBSTR("deg"),&val),S_OK);
   TRY_TEST(IsEqual(val,45.0),true);

   TRY_TEST(convert->ConvertToBaseUnits(M_PI/4,CComBSTR("rad"),&val),S_OK);
   TRY_TEST(IsEqual(val,45.0),true);

   TRY_TEST(convert->ConvertToBaseUnits(1.0,CComBSTR("kip/in"),&val),S_OK);
   TRY_TEST(IsEqual(val,12.0),true);


   
   TRY_TEST(convert->ConvertFromBaseUnits(1.0,CComBSTR("kip"),&val),S_OK);
   TRY_TEST(IsEqual(val,1.0),true);
   
   TRY_TEST(convert->ConvertFromBaseUnits(1.0,CComBSTR("lbf"),&val),S_OK);
   TRY_TEST(IsEqual(val,1000.0),true);
   
   TRY_TEST(convert->ConvertFromBaseUnits(1.0,CComBSTR("kip-ft"),&val),S_OK);
   TRY_TEST(IsEqual(val,1.0),true);
   
   TRY_TEST(convert->ConvertFromBaseUnits(1.0,CComBSTR("lbf-ft"),&val),S_OK);
   TRY_TEST(IsEqual(val,1000.0),true);
   
   TRY_TEST(convert->ConvertFromBaseUnits(1.0,CComBSTR("kip-in"),&val),S_OK);
   TRY_TEST(IsEqual(val,12.0),true);
   
   TRY_TEST(convert->ConvertFromBaseUnits(1.0,CComBSTR("in^2"),&val),S_OK);
   TRY_TEST(IsEqual(val,144.0),true);
   
   TRY_TEST(convert->ConvertFromBaseUnits(1.0,CComBSTR("in^3"),&val),S_OK);
   TRY_TEST(IsEqual(val,1728.0),true);

   TRY_TEST(convert->ConvertFromBaseUnits(32.0,CComBSTR("F"),&val),S_OK);
   TRY_TEST(IsEqual(val,32.0),true);

   TRY_TEST(convert->ConvertFromBaseUnits(32.0,CComBSTR("C"),&val),S_OK);
   TRY_TEST(IsEqual(val,0.0),true);

   TRY_TEST(convert->ConvertFromBaseUnits(45.0,CComBSTR("deg"),&val),S_OK);
   TRY_TEST(IsEqual(val,45.0),true);

   TRY_TEST(convert->ConvertFromBaseUnits(45,CComBSTR("rad"),&val),S_OK);
   TRY_TEST(IsEqual(val,M_PI/4),true);

   TRY_TEST(convert->ConvertFromBaseUnits(1.0,CComBSTR("kip/in"),&val),S_OK);
   TRY_TEST(IsEqual(val,0.083333333333333333),true);

   // Test with Mg for base units of kN, m, s
   convert.Release();
   unitServer.Release();

   unitServer.CoCreateInstance( CLSID_UnitServer );

   // Use base units of kip,ft,s,F,deg
   TRY_TEST(unitServer->SetSystemUnits(CComBSTR("Mg"),CComBSTR("m"),CComBSTR("sec"),CComBSTR("C"),CComBSTR("rad")),S_OK);

   unitServer->get_UnitConvert(&convert);

   TRY_TEST(convert->ConvertToBaseUnits(1.0,CComBSTR("kN"),&val),S_OK);
   TRY_TEST(IsEqual(val,1.0),true);

   TRY_TEST(convert->ConvertToBaseUnits(1000.0,CComBSTR("N"),&val),S_OK);
   TRY_TEST(IsEqual(val,1.0),true);

   TRY_TEST(convert->ConvertToBaseUnits(1.0,CComBSTR("kip"),&val),S_OK);
   TRY_TEST(IsEqual(val,4.44822161526),true);

   TRY_TEST(convert->ConvertToBaseUnits(1.0,CComBSTR("kN-m"),&val),S_OK);
   TRY_TEST(IsEqual(val,1.0),true);

   TRY_TEST(convert->ConvertToBaseUnits(1.0,CComBSTR("N-mm"),&val),S_OK);
   TRY_TEST(IsEqual(val,1.0),true);



   TRY_TEST(convert->ConvertFromBaseUnits(1.0,CComBSTR("kN"),&val),S_OK);
   TRY_TEST(IsEqual(val,1.0),true);

   TRY_TEST(convert->ConvertFromBaseUnits(1.0,CComBSTR("N"),&val),S_OK);
   TRY_TEST(IsEqual(val,1000.0),true);

   TRY_TEST(convert->ConvertFromBaseUnits(4.44822161526,CComBSTR("kip"),&val),S_OK);
   TRY_TEST(IsEqual(val,1.0),true);

   TRY_TEST(convert->ConvertFromBaseUnits(1.0,CComBSTR("kN-m"),&val),S_OK);
   TRY_TEST(IsEqual(val,1.0),true);

   TRY_TEST(convert->ConvertFromBaseUnits(1.0,CComBSTR("N-mm"),&val),S_OK);
   TRY_TEST(IsEqual(val,1.0),true);
}
