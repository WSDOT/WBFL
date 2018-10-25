///////////////////////////////////////////////////////////////////////
// COGOTest - Test Driver for Coordinate Geometry Library
// Copyright © 1999-2016  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// TestStation.cpp: implementation of the CTestStation class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestStation.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestStation::CTestStation()
{

}

void CTestStation::Test()
{
   CComPtr<IStation> station;
   TRY_TEST(station.CoCreateInstance(CLSID_Station),S_OK);

   Float64 value;
   TRY_TEST(station->get_Value(NULL),E_POINTER);
   TRY_TEST(station->get_Value(&value),S_OK);
   TRY_TEST(IsZero(value),true);

   TRY_TEST(station->put_Value(100),S_OK);

   // Valid US station
   CComBSTR usStation("3+34.54");
   TRY_TEST(station->FromString(usStation,umUS),S_OK);
   TRY_TEST(station->get_Value(&value),S_OK);
   TRY_TEST(IsEqual(value,334.54),true);

   CComBSTR usStation2("-3+34.54");
   TRY_TEST(station->FromString(usStation2,umUS),S_OK);
   TRY_TEST(station->get_Value(&value),S_OK);
   TRY_TEST(IsEqual(value,-334.54),true);

   // Valid SI station
   CComBSTR siStation("3+034.54");
   TRY_TEST(station->FromString(siStation,umSI),S_OK);
   TRY_TEST(station->get_Value(&value),S_OK);
   TRY_TEST(IsEqual(value,3034.54),true);

   CComBSTR siStation2("-3+034.54");
   TRY_TEST(station->FromString(siStation2,umSI),S_OK);
   TRY_TEST(station->get_Value(&value),S_OK);
   TRY_TEST(IsEqual(value,-3034.54),true);

   // Bad US Station (use the SI station)
   TRY_TEST(station->FromString(siStation,umUS),COGO_E_BADSTATIONSTRING);

   // Bad SI Station (use the US station)
   TRY_TEST(station->FromString(usStation,umSI),COGO_E_BADSTATIONSTRING);

   station->put_Value(3434.34);
   CComBSTR bstrStation;
   TRY_TEST(station->AsString(umUS,&bstrStation),S_OK);
   TRY_TEST(bstrStation == CComBSTR("34+34.34"),true);

   station->put_Value(9999.99);
   bstrStation.Empty();
   TRY_TEST(station->AsString(umUS,&bstrStation),S_OK);
   TRY_TEST(bstrStation == CComBSTR("99+99.99"),true);

   station->put_Value(9999.99);
   bstrStation.Empty();
   TRY_TEST(station->AsString(umSI,&bstrStation),S_OK);
   TRY_TEST(bstrStation == CComBSTR("9+999.990"),true);

   station->put_Value(-9999.99);
   bstrStation.Empty();
   TRY_TEST(station->AsString(umUS,&bstrStation),S_OK);
   TRY_TEST(bstrStation == CComBSTR("-99+99.99"),true);

   station->put_Value(0.45);
   bstrStation.Empty();
   TRY_TEST(station->AsString(umUS,&bstrStation),S_OK);
   TRY_TEST(bstrStation == CComBSTR("0+00.45"),true);

   station->put_Value(0.45);
   bstrStation.Empty();
   TRY_TEST(station->AsString(umSI,&bstrStation),S_OK);
   TRY_TEST(bstrStation == CComBSTR("0+000.450"),true);

   TRY_TEST( TestIObjectSafety(CLSID_Station,IID_IStation,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
   TRY_TEST( TestIObjectSafety(CLSID_Station,IID_IStructuredStorage2,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
}