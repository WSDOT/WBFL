///////////////////////////////////////////////////////////////////////
// COGOTest - Test Driver for Coordinate Geometry Library
// Copyright � 1999-2026  Washington State Department of Transportation
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

// TestAngle.cpp
//
// Ported from F:\ARP\WBFL\COGO\CogoTest\TestAngle.cpp (legacy WBFLTest.h
// harness) to MSVC CppUnitTestFramework, talking to WBFLCogo.dll purely
// through its public COM interfaces (see CogoTestUtil.h).
#include "pch.h"

namespace CogoUnitTests
{

TEST_CLASS(TestAngle)
{
public:
   TEST_METHOD(BasicOperations)
   {
      CComPtr<IAngle> angle;
      ASSERT_EQ( angle.CoCreateInstance(CLSID_Angle), S_OK );

      // Test default value
      Float64 val;
      ASSERT_EQ( angle->get_Value(nullptr), E_POINTER );
      ASSERT_EQ( angle->get_Value(&val), S_OK );
      ASSERT_EQ( IsZero(val), true );

      // Test setting value
      ASSERT_EQ( angle->put_Value(10.0), S_OK );
      ASSERT_EQ( angle->get_Value(&val), S_OK );
      ASSERT_EQ( IsEqual(val,10.0), true);

      // Test FromDMS and Degree, Minute, Second properties
      ASSERT_EQ( angle->FromDMS(-14,60,13.5), E_INVALIDARG); // Invalid minute
      ASSERT_EQ( angle->FromDMS(-14,65,13.5), E_INVALIDARG); // Invalid minute
      ASSERT_EQ( angle->FromDMS(-14,-10,13.5), E_INVALIDARG); // Invalid minute
      ASSERT_EQ( angle->FromDMS(-14,25,60.0), E_INVALIDARG); // Invalid second
      ASSERT_EQ( angle->FromDMS(-14,25,65.0), E_INVALIDARG); // Invalid second
      ASSERT_EQ( angle->FromDMS(-14,25,-10.0), E_INVALIDARG); // Invalid second
      ASSERT_EQ( angle->FromDMS(-14,25,13.5), S_OK);
      long deg,min;
      Float64 sec;
      ASSERT_EQ( angle->get_Degree(nullptr), E_POINTER );
      ASSERT_EQ( angle->get_Degree(&deg), S_OK);
      ASSERT_EQ( deg, -14);

      ASSERT_EQ( angle->get_Minute(nullptr), E_POINTER );
      ASSERT_EQ( angle->get_Minute(&min), S_OK);
      ASSERT_EQ( min, 25);

      ASSERT_EQ( angle->get_Second(nullptr), E_POINTER );
      ASSERT_EQ( angle->get_Second(&sec), S_OK);
      ASSERT_EQ( IsEqual(sec,13.5), true);

      // Test Normalize
      angle->put_Value(-2*TWO_PI);
      angle->Normalize();
      angle->get_Value(&val);
      ASSERT_EQ( IsZero(val), true );

      angle->put_Value(2*TWO_PI);
      angle->Normalize();
      angle->get_Value(&val);
      ASSERT_EQ( IsZero(val), true );

      angle->put_Value(TWO_PI);
      angle->Normalize();
      angle->get_Value(&val);
      ASSERT_EQ( IsZero(val), true );

      angle->put_Value(TWO_PI);
      angle->Normalize();
      angle->get_Value(&val);
      ASSERT_EQ( IsZero(val), true );

      angle->put_Value(1.25*TWO_PI);
      angle->Normalize();
      angle->get_Value(&val);
      ASSERT_EQ( IsEqual(val,PI_OVER_2), true );

      angle->put_Value(-1.25*TWO_PI);
      angle->Normalize();
      angle->get_Value(&val);
      ASSERT_EQ( IsEqual(val,3*PI_OVER_2), true );

      // Test FromString
      ASSERT_EQ( angle->FromString(nullptr),                    E_INVALIDARG );
      ASSERT_EQ( angle->FromString(CComBSTR("")),               E_INVALIDARG );
      ASSERT_EQ( angle->FromString(CComBSTR("        ")),       E_INVALIDARG );
      ASSERT_EQ( angle->FromString(CComBSTR("A")),              E_INVALIDARG );
      ASSERT_EQ( angle->FromString(CComBSTR("+12.5 L")),        E_INVALIDARG );
      ASSERT_EQ( angle->FromString(CComBSTR("-12.5 L")),        E_INVALIDARG );
      ASSERT_EQ( angle->FromString(CComBSTR("+12.5 R")),        E_INVALIDARG );
      ASSERT_EQ( angle->FromString(CComBSTR("-12.5 R")),        E_INVALIDARG );
      ASSERT_EQ( angle->FromString(CComBSTR("x12.5 L")),        E_INVALIDARG );
      ASSERT_EQ( angle->FromString(CComBSTR("12.5 LR")),        E_INVALIDARG );
      ASSERT_EQ( angle->FromString(CComBSTR("12.5 x")),         E_INVALIDARG );
      ASSERT_EQ( angle->FromString(CComBSTR("DD 13 14.15")),    E_INVALIDARG );
      ASSERT_EQ( angle->FromString(CComBSTR("12 MM 14.15")),    E_INVALIDARG );
      ASSERT_EQ( angle->FromString(CComBSTR("12 13 SS.ss")),    E_INVALIDARG );
      ASSERT_EQ( angle->FromString(CComBSTR("12 -10 14.15")),   E_INVALIDARG );
      ASSERT_EQ( angle->FromString(CComBSTR("12 60 14.15")),    E_INVALIDARG );
      ASSERT_EQ( angle->FromString(CComBSTR("12 65 14.15")),    E_INVALIDARG );
      ASSERT_EQ( angle->FromString(CComBSTR("12 13 -14.15")),   E_INVALIDARG );
      ASSERT_EQ( angle->FromString(CComBSTR("12 13 60.00")),    E_INVALIDARG );
      ASSERT_EQ( angle->FromString(CComBSTR("12 13 65.00")),    E_INVALIDARG );
      ASSERT_EQ( angle->FromString(CComBSTR("12 13 14.15 LR")), E_INVALIDARG );
      ASSERT_EQ( angle->FromString(CComBSTR("12 13 14.15 x")),  E_INVALIDARG );
      ASSERT_EQ( angle->FromString(CComBSTR("-12 13 14.15 L")), E_INVALIDARG );
      ASSERT_EQ( angle->FromString(CComBSTR("+12 13 14.15 L")), E_INVALIDARG );
      ASSERT_EQ( angle->FromString(CComBSTR("-12 13 14.15 R")), E_INVALIDARG );
      ASSERT_EQ( angle->FromString(CComBSTR("+12 13 14.15 R")), E_INVALIDARG );

      // This should work!!!
      ASSERT_EQ( angle->FromString(CComBSTR("12 13 R")), S_OK);
      angle->get_Degree(&deg);
      angle->get_Minute(&min);
      angle->get_Second(&sec);
      ASSERT_EQ( deg, -12 );
      ASSERT_EQ( min, 13 );
      ASSERT_EQ( IsZero(sec), true );

      ASSERT_EQ( angle->FromString(CComBSTR("12 13 L")), S_OK);
      angle->get_Degree(&deg);
      angle->get_Minute(&min);
      angle->get_Second(&sec);
      ASSERT_EQ( deg, 12 );
      ASSERT_EQ( min, 13 );
      ASSERT_EQ( IsZero(sec), true );

      ASSERT_EQ( angle->FromString(CComBSTR("12.5")), S_OK );
      angle->get_Degree(&deg);
      angle->get_Minute(&min);
      angle->get_Second(&sec);
      ASSERT_EQ( deg, 12 );
      ASSERT_EQ( min, 30 );
      ASSERT_EQ( IsZero(sec), true );

      ASSERT_EQ( angle->FromString(CComBSTR("-12.5")), S_OK );
      angle->get_Degree(&deg);
      angle->get_Minute(&min);
      angle->get_Second(&sec);
      ASSERT_EQ( deg, -12 );
      ASSERT_EQ( min, 30 );
      ASSERT_EQ( IsZero(sec), true );

      ASSERT_EQ( angle->FromString(CComBSTR("12.5 L")), S_OK );
      angle->get_Degree(&deg);
      angle->get_Minute(&min);
      angle->get_Second(&sec);
      ASSERT_EQ( deg, 12 );
      ASSERT_EQ( min, 30 );
      ASSERT_EQ( IsZero(sec), true );

      ASSERT_EQ( angle->FromString(CComBSTR("12.5 R")), S_OK );
      angle->get_Degree(&deg);
      angle->get_Minute(&min);
      angle->get_Second(&sec);
      ASSERT_EQ( deg, -12 );
      ASSERT_EQ( min, 30 );
      ASSERT_EQ( IsZero(sec), true );

      ASSERT_EQ( angle->FromString(CComBSTR("12.5 l")), S_OK );
      angle->get_Degree(&deg);
      angle->get_Minute(&min);
      angle->get_Second(&sec);
      ASSERT_EQ( deg, 12 );
      ASSERT_EQ( min, 30 );
      ASSERT_EQ( IsZero(sec), true );

      ASSERT_EQ( angle->FromString(CComBSTR("12.5 r")), S_OK );
      angle->get_Degree(&deg);
      angle->get_Minute(&min);
      angle->get_Second(&sec);
      ASSERT_EQ( deg, -12 );
      ASSERT_EQ( min, 30 );
      ASSERT_EQ( IsZero(sec), true );

      ASSERT_EQ( angle->FromString(CComBSTR("          12.5 L")), S_OK );
      angle->get_Degree(&deg);
      angle->get_Minute(&min);
      angle->get_Second(&sec);
      ASSERT_EQ( deg, 12 );
      ASSERT_EQ( min, 30 );
      ASSERT_EQ( IsZero(sec), true );

      ASSERT_EQ( angle->FromString(CComBSTR("12.5 L           ")), S_OK );
      angle->get_Degree(&deg);
      angle->get_Minute(&min);
      angle->get_Second(&sec);
      ASSERT_EQ( deg, 12 );
      ASSERT_EQ( min, 30 );
      ASSERT_EQ( IsZero(sec), true );

      ASSERT_EQ( angle->FromString(CComBSTR("        12.5 L      ")), S_OK );
      angle->get_Degree(&deg);
      angle->get_Minute(&min);
      angle->get_Second(&sec);
      ASSERT_EQ( deg, 12 );
      ASSERT_EQ( min, 30 );
      ASSERT_EQ( IsZero(sec), true );

      ASSERT_EQ( angle->FromString(CComBSTR("12 13 14.15 L")), S_OK );
      angle->get_Degree(&deg);
      angle->get_Minute(&min);
      angle->get_Second(&sec);
      ASSERT_EQ( deg, 12 );
      ASSERT_EQ( min, 13 );
      ASSERT_EQ( IsEqual(sec,14.15), true );

      ASSERT_EQ( angle->FromString(CComBSTR("12 13 14.15 R")), S_OK );
      angle->get_Degree(&deg);
      angle->get_Minute(&min);
      angle->get_Second(&sec);
      ASSERT_EQ( deg, -12 );
      ASSERT_EQ( min, 13 );
      ASSERT_EQ( IsEqual(sec,14.15), true );

      ASSERT_EQ( angle->FromString(CComBSTR("12 13 14.15")), S_OK );
      angle->get_Degree(&deg);
      angle->get_Minute(&min);
      angle->get_Second(&sec);
      ASSERT_EQ( deg, 12 );
      ASSERT_EQ( min, 13 );
      ASSERT_EQ( IsEqual(sec,14.15), true );

      ASSERT_EQ( angle->FromString(CComBSTR("+12 13 14.15")), S_OK );
      angle->get_Degree(&deg);
      angle->get_Minute(&min);
      angle->get_Second(&sec);
      ASSERT_EQ( deg, 12 );
      ASSERT_EQ( min, 13 );
      ASSERT_EQ( IsEqual(sec,14.15), true );

      ASSERT_EQ( angle->FromString(CComBSTR("-12 13 14.15")), S_OK );
      angle->get_Degree(&deg);
      angle->get_Minute(&min);
      angle->get_Second(&sec);
      ASSERT_EQ( deg, -12 );
      ASSERT_EQ( min, 13 );
      ASSERT_EQ( IsEqual(sec,14.15), true );

      ASSERT_EQ( angle->FromString(CComBSTR("00 00 14.15")), S_OK );
      angle->get_Degree(&deg);
      angle->get_Minute(&min);
      angle->get_Second(&sec);
      ASSERT_EQ( deg, 0 );
      ASSERT_EQ( min, 0 );
      ASSERT_EQ( IsEqual(sec,14.15), true );

      // Test Increment and IncrementBy
      angle->put_Value(0);
      ASSERT_EQ(angle->IncrementBy(CComVariant(CComBSTR("Invalid"))),E_INVALIDARG);
      ASSERT_EQ(angle->IncrementBy(CComVariant(M_PI)),S_OK);
      angle->get_Value(&val);
      ASSERT_EQ(IsEqual(val,M_PI),true);
      CComPtr<IAngle> incAngle;
      ASSERT_EQ(angle->Increment(CComVariant(TWO_PI),nullptr),E_POINTER);
      ASSERT_EQ(angle->Increment(CComVariant(TWO_PI),&incAngle),S_OK);
      angle->get_Value(&val);
      ASSERT_EQ(IsEqual(val,M_PI),true);
      incAngle->get_Value(&val);
      ASSERT_EQ(IsEqual(val,3*M_PI),true);

      CComQIPtr<ISupportErrorInfo> eInfo(angle);
      ASSERT_EQ( eInfo != 0, true );

      // Interfaces that should be supported
      ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_IAngle ), S_OK );

      // Interface that is not supported
      ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

      // Test IObjectSafety
      ASSERT_EQ( TestIObjectSafety(CLSID_Angle,IID_IAngle,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
   }
};
} // namespace CogoUnitTests