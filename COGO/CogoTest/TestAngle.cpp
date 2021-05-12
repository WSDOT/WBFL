///////////////////////////////////////////////////////////////////////
// COGOTest - Test Driver for Coordinate Geometry Library
// Copyright © 1999-2021  Washington State Department of Transportation
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

// TestAngle.cpp: implementation of the CTestAngle class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestAngle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestAngle::CTestAngle()
{

}

CTestAngle::~CTestAngle()
{

}

void CTestAngle::Test()
{
   CComPtr<IAngle> angle;
   TRY_TEST( angle.CoCreateInstance(CLSID_Angle), S_OK );

   // Test default value
   Float64 val;
   TRY_TEST( angle->get_Value(nullptr), E_POINTER );
   TRY_TEST( angle->get_Value(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   // Test setting value
   TRY_TEST( angle->put_Value(10.0), S_OK );
   TRY_TEST( angle->get_Value(&val), S_OK );
   TRY_TEST( IsEqual(val,10.0), true);

   // Test FromDMS and Degree, Minute, Second properties
   TRY_TEST( angle->FromDMS(-14,60,13.5),  COGO_E_BADANGLE ); // Invalid minute
   TRY_TEST( angle->FromDMS(-14,65,13.5),  COGO_E_BADANGLE ); // Invalid minute
   TRY_TEST( angle->FromDMS(-14,-10,13.5), COGO_E_BADANGLE ); // Invalid minute
   TRY_TEST( angle->FromDMS(-14,25,60.0),  COGO_E_BADANGLE ); // Invalid second
   TRY_TEST( angle->FromDMS(-14,25,65.0),  COGO_E_BADANGLE ); // Invalid second
   TRY_TEST( angle->FromDMS(-14,25,-10.0), COGO_E_BADANGLE ); // Invalid second
   TRY_TEST( angle->FromDMS(-14,25,13.5), S_OK);
   long deg,min;
   Float64 sec;
   TRY_TEST( angle->get_Degree(nullptr), E_POINTER );
   TRY_TEST( angle->get_Degree(&deg), S_OK);
   TRY_TEST( deg, -14);

   TRY_TEST( angle->get_Minute(nullptr), E_POINTER );
   TRY_TEST( angle->get_Minute(&min), S_OK);
   TRY_TEST( min, 25);

   TRY_TEST( angle->get_Second(nullptr), E_POINTER );
   TRY_TEST( angle->get_Second(&sec), S_OK);
   TRY_TEST( IsEqual(sec,13.5), true);

   // Test Normalize
   angle->put_Value(-2*TWO_PI);
   angle->Normalize();
   angle->get_Value(&val);
   TRY_TEST( IsZero(val), true );

   angle->put_Value(2*TWO_PI);
   angle->Normalize();
   angle->get_Value(&val);
   TRY_TEST( IsZero(val), true );

   angle->put_Value(TWO_PI);
   angle->Normalize();
   angle->get_Value(&val);
   TRY_TEST( IsZero(val), true );

   angle->put_Value(TWO_PI);
   angle->Normalize();
   angle->get_Value(&val);
   TRY_TEST( IsZero(val), true );

   angle->put_Value(1.25*TWO_PI);
   angle->Normalize();
   angle->get_Value(&val);
   TRY_TEST( IsEqual(val,PI_OVER_2), true );

   angle->put_Value(-1.25*TWO_PI);
   angle->Normalize();
   angle->get_Value(&val);
   TRY_TEST( IsEqual(val,3*PI_OVER_2), true );

   // Test FromString
   TRY_TEST( angle->FromString(nullptr),                       E_INVALIDARG );
   TRY_TEST( angle->FromString(CComBSTR("")),               COGO_E_BADANGLESTRING );
   TRY_TEST( angle->FromString(CComBSTR("        ")),       COGO_E_BADANGLESTRING );
   TRY_TEST( angle->FromString(CComBSTR("A")),              COGO_E_BADANGLESTRING );
   TRY_TEST( angle->FromString(CComBSTR("+12.5 L")),        COGO_E_BADANGLESTRING );
   TRY_TEST( angle->FromString(CComBSTR("-12.5 L")),        COGO_E_BADANGLESTRING );
   TRY_TEST( angle->FromString(CComBSTR("+12.5 R")),        COGO_E_BADANGLESTRING );
   TRY_TEST( angle->FromString(CComBSTR("-12.5 R")),        COGO_E_BADANGLESTRING );
   TRY_TEST( angle->FromString(CComBSTR("x12.5 L")),        COGO_E_BADANGLESTRING );
   TRY_TEST( angle->FromString(CComBSTR("12.5 LR")),        COGO_E_BADANGLESTRING );
   TRY_TEST( angle->FromString(CComBSTR("12.5 x")),         COGO_E_BADANGLESTRING );
   TRY_TEST( angle->FromString(CComBSTR("DD 13 14.15")),    COGO_E_BADANGLESTRING );
   TRY_TEST( angle->FromString(CComBSTR("12 MM 14.15")),    COGO_E_BADANGLESTRING );
   TRY_TEST( angle->FromString(CComBSTR("12 13 SS.ss")),    COGO_E_BADANGLESTRING );
   TRY_TEST( angle->FromString(CComBSTR("12 -10 14.15")),   COGO_E_BADANGLESTRING );
   TRY_TEST( angle->FromString(CComBSTR("12 60 14.15")),    COGO_E_BADANGLESTRING );
   TRY_TEST( angle->FromString(CComBSTR("12 65 14.15")),    COGO_E_BADANGLESTRING );
   TRY_TEST( angle->FromString(CComBSTR("12 13 -14.15")),   COGO_E_BADANGLESTRING );
   TRY_TEST( angle->FromString(CComBSTR("12 13 60.00")),    COGO_E_BADANGLESTRING );
   TRY_TEST( angle->FromString(CComBSTR("12 13 65.00")),    COGO_E_BADANGLESTRING );
   TRY_TEST( angle->FromString(CComBSTR("12 13 14.15 LR")), COGO_E_BADANGLESTRING );
   TRY_TEST( angle->FromString(CComBSTR("12 13 14.15 x")),  COGO_E_BADANGLESTRING );
   TRY_TEST( angle->FromString(CComBSTR("-12 13 14.15 L")), COGO_E_BADANGLESTRING );
   TRY_TEST( angle->FromString(CComBSTR("+12 13 14.15 L")), COGO_E_BADANGLESTRING );
   TRY_TEST( angle->FromString(CComBSTR("-12 13 14.15 R")), COGO_E_BADANGLESTRING );
   TRY_TEST( angle->FromString(CComBSTR("+12 13 14.15 R")), COGO_E_BADANGLESTRING );

   // This should work!!!
   TRY_TEST( angle->FromString(CComBSTR("12 13 R")), S_OK);
   angle->get_Degree(&deg);
   angle->get_Minute(&min);
   angle->get_Second(&sec);
   TRY_TEST( deg, -12 );
   TRY_TEST( min, 13 );
   TRY_TEST( IsZero(sec), true );

   TRY_TEST( angle->FromString(CComBSTR("12 13 L")), S_OK);
   angle->get_Degree(&deg);
   angle->get_Minute(&min);
   angle->get_Second(&sec);
   TRY_TEST( deg, 12 );
   TRY_TEST( min, 13 );
   TRY_TEST( IsZero(sec), true );

   TRY_TEST( angle->FromString(CComBSTR("12.5")), S_OK );
   angle->get_Degree(&deg);
   angle->get_Minute(&min);
   angle->get_Second(&sec);
   TRY_TEST( deg, 12 );
   TRY_TEST( min, 30 );
   TRY_TEST( IsZero(sec), true );

   TRY_TEST( angle->FromString(CComBSTR("-12.5")), S_OK );
   angle->get_Degree(&deg);
   angle->get_Minute(&min);
   angle->get_Second(&sec);
   TRY_TEST( deg, -12 );
   TRY_TEST( min, 30 );
   TRY_TEST( IsZero(sec), true );

   TRY_TEST( angle->FromString(CComBSTR("12.5 L")), S_OK );
   angle->get_Degree(&deg);
   angle->get_Minute(&min);
   angle->get_Second(&sec);
   TRY_TEST( deg, 12 );
   TRY_TEST( min, 30 );
   TRY_TEST( IsZero(sec), true );

   TRY_TEST( angle->FromString(CComBSTR("12.5 R")), S_OK );
   angle->get_Degree(&deg);
   angle->get_Minute(&min);
   angle->get_Second(&sec);
   TRY_TEST( deg, -12 );
   TRY_TEST( min, 30 );
   TRY_TEST( IsZero(sec), true );

   TRY_TEST( angle->FromString(CComBSTR("12.5 l")), S_OK );
   angle->get_Degree(&deg);
   angle->get_Minute(&min);
   angle->get_Second(&sec);
   TRY_TEST( deg, 12 );
   TRY_TEST( min, 30 );
   TRY_TEST( IsZero(sec), true );

   TRY_TEST( angle->FromString(CComBSTR("12.5 r")), S_OK );
   angle->get_Degree(&deg);
   angle->get_Minute(&min);
   angle->get_Second(&sec);
   TRY_TEST( deg, -12 );
   TRY_TEST( min, 30 );
   TRY_TEST( IsZero(sec), true );

   TRY_TEST( angle->FromString(CComBSTR("          12.5 L")), S_OK );
   angle->get_Degree(&deg);
   angle->get_Minute(&min);
   angle->get_Second(&sec);
   TRY_TEST( deg, 12 );
   TRY_TEST( min, 30 );
   TRY_TEST( IsZero(sec), true );

   TRY_TEST( angle->FromString(CComBSTR("12.5 L           ")), S_OK );
   angle->get_Degree(&deg);
   angle->get_Minute(&min);
   angle->get_Second(&sec);
   TRY_TEST( deg, 12 );
   TRY_TEST( min, 30 );
   TRY_TEST( IsZero(sec), true );

   TRY_TEST( angle->FromString(CComBSTR("        12.5 L      ")), S_OK );
   angle->get_Degree(&deg);
   angle->get_Minute(&min);
   angle->get_Second(&sec);
   TRY_TEST( deg, 12 );
   TRY_TEST( min, 30 );
   TRY_TEST( IsZero(sec), true );

   TRY_TEST( angle->FromString(CComBSTR("12 13 14.15 L")), S_OK );
   angle->get_Degree(&deg);
   angle->get_Minute(&min);
   angle->get_Second(&sec);
   TRY_TEST( deg, 12 );
   TRY_TEST( min, 13 );
   TRY_TEST( IsEqual(sec,14.15), true );

   TRY_TEST( angle->FromString(CComBSTR("12 13 14.15 R")), S_OK );
   angle->get_Degree(&deg);
   angle->get_Minute(&min);
   angle->get_Second(&sec);
   TRY_TEST( deg, -12 );
   TRY_TEST( min, 13 );
   TRY_TEST( IsEqual(sec,14.15), true );

   TRY_TEST( angle->FromString(CComBSTR("12 13 14.15")), S_OK );
   angle->get_Degree(&deg);
   angle->get_Minute(&min);
   angle->get_Second(&sec);
   TRY_TEST( deg, 12 );
   TRY_TEST( min, 13 );
   TRY_TEST( IsEqual(sec,14.15), true );

   TRY_TEST( angle->FromString(CComBSTR("+12 13 14.15")), S_OK );
   angle->get_Degree(&deg);
   angle->get_Minute(&min);
   angle->get_Second(&sec);
   TRY_TEST( deg, 12 );
   TRY_TEST( min, 13 );
   TRY_TEST( IsEqual(sec,14.15), true );

   TRY_TEST( angle->FromString(CComBSTR("-12 13 14.15")), S_OK );
   angle->get_Degree(&deg);
   angle->get_Minute(&min);
   angle->get_Second(&sec);
   TRY_TEST( deg, -12 );
   TRY_TEST( min, 13 );
   TRY_TEST( IsEqual(sec,14.15), true );

   TRY_TEST( angle->FromString(CComBSTR("00 00 14.15")), S_OK );
   angle->get_Degree(&deg);
   angle->get_Minute(&min);
   angle->get_Second(&sec);
   TRY_TEST( deg, 0 );
   TRY_TEST( min, 0 );
   TRY_TEST( IsEqual(sec,14.15), true );

   // Test Increment and IncrementBy
   angle->put_Value(0);
   TRY_TEST(angle->IncrementBy(CComVariant(CComBSTR("Invalid"))),E_INVALIDARG);
   TRY_TEST(angle->IncrementBy(CComVariant(M_PI)),S_OK);
   angle->get_Value(&val);
   TRY_TEST(IsEqual(val,M_PI),true);
   CComPtr<IAngle> incAngle;
   TRY_TEST(angle->Increment(CComVariant(TWO_PI),nullptr),E_POINTER);
   TRY_TEST(angle->Increment(CComVariant(TWO_PI),&incAngle),S_OK);
   angle->get_Value(&val);
   TRY_TEST(IsEqual(val,M_PI),true);
   incAngle->get_Value(&val);
   TRY_TEST(IsEqual(val,3*M_PI),true);

   CComQIPtr<ISupportErrorInfo> eInfo(angle);
   TRY_TEST( eInfo != 0, true );

   // Interfaces that should be supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IAngle ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );

   // Interface that is not supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

   // Test IObjectSafety
   TRY_TEST( TestIObjectSafety(CLSID_Angle,IID_IAngle,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
   TRY_TEST( TestIObjectSafety(CLSID_Angle,IID_IStructuredStorage2,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
}
