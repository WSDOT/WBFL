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

// TestDirection.cpp
//
// Ported from F:\ARP\WBFL\COGO\CogoTest\TestDirection.cpp (legacy WBFLTest.h
// harness) to MSVC CppUnitTestFramework, talking to WBFLCogo.dll purely
// through its public COM interfaces (see CogoTestUtil.h).
#include "pch.h"

namespace CogoUnitTests
{

TEST_CLASS(TestDirection)
{
public:
   TEST_METHOD(BasicOperations)
   {
      CComPtr<IDirection> dir;
      ASSERT_EQ(dir.CoCreateInstance(CLSID_Direction),S_OK);

      Float64 val;
      NSDirectionType nsDir;
      long deg, min;
      Float64 sec;
      EWDirectionType ewDir;

      // Test initial value
      ASSERT_EQ(dir->get_Value(nullptr),E_POINTER);
      ASSERT_EQ(dir->get_Value(&val),S_OK);
      ASSERT_EQ(IsZero(val),true);

      // Set/Get value (value should be normalized)
      ASSERT_EQ(dir->put_Value(3.23),S_OK);
      ASSERT_EQ(dir->get_Value(&val),S_OK);
      ASSERT_EQ(IsEqual(3.23,val),true);

      ASSERT_EQ(dir->put_Value(-3.23),S_OK);
      ASSERT_EQ(dir->get_Value(&val),S_OK);
      ASSERT_EQ(IsEqual(TWO_PI - 3.23,val),true);

      // N 45 15 22.5 E =  44.74375deg = 0.780925757rad
      // N 45 15 22.5 W = 135.25625deg = 2.360666897rad
      // S 45 15 22.5 W = 224.74375deg = 3.922518411rad
      // S 45 15 22.5 E = 315.25625deg = 5.502259551rad

      // North/South and East/West Direction
      ASSERT_EQ(dir->get_NSDirection(nullptr),E_POINTER);   
      ASSERT_EQ(dir->get_EWDirection(nullptr),E_POINTER);   
      ASSERT_EQ(dir->put_NSDirection((NSDirectionType)4), E_INVALIDARG);
      ASSERT_EQ(dir->put_EWDirection((EWDirectionType)4), E_INVALIDARG);

      dir->put_Value(0.780925757);
      ASSERT_EQ(dir->get_NSDirection(&nsDir),S_OK);   
      ASSERT_EQ(nsDir,nsNorth);
      ASSERT_EQ(dir->get_EWDirection(&ewDir),S_OK);   
      ASSERT_EQ(ewDir,ewEast);

      dir->put_Value(2.360666897);
      ASSERT_EQ(dir->get_NSDirection(&nsDir),S_OK);   
      ASSERT_EQ(nsDir,nsNorth);
      ASSERT_EQ(dir->get_EWDirection(&ewDir),S_OK);   
      ASSERT_EQ(ewDir,ewWest);

      dir->put_Value(3.922548411);
      ASSERT_EQ(dir->get_NSDirection(&nsDir),S_OK);   
      ASSERT_EQ(nsDir,nsSouth);
      ASSERT_EQ(dir->get_EWDirection(&ewDir),S_OK);   
      ASSERT_EQ(ewDir,ewWest);

      dir->put_Value(5.502259551);
      ASSERT_EQ(dir->get_NSDirection(&nsDir),S_OK);   
      ASSERT_EQ(nsDir,nsSouth);
      ASSERT_EQ(dir->get_EWDirection(&ewDir),S_OK);   
      ASSERT_EQ(ewDir,ewEast);

      // Swap around the N/S, E/W and check the resulting value
      dir->put_Value(0.780925757); // N 45 15 22.5 E
      ASSERT_EQ(dir->put_NSDirection(nsSouth),S_OK);
      dir->get_Value(&val);
      ASSERT_EQ(IsEqual(val,5.502259551),true); // S 45 15 22.5 E

      ASSERT_EQ(dir->put_EWDirection(ewWest),S_OK);
      dir->get_Value(&val);
      ASSERT_EQ(IsEqual(val,3.922518411),true); // S 45 15 22.5 W

      ASSERT_EQ(dir->put_NSDirection(nsNorth),S_OK);
      dir->get_Value(&val);
      ASSERT_EQ(IsEqual(val,2.360666897),true); // N 45 15 22.5 W

      ASSERT_EQ(dir->put_EWDirection(ewEast),S_OK);
      dir->get_Value(&val);
      ASSERT_EQ(IsEqual(val,0.780925757),true); // N 45 15 22.5 E

      // Get Degree/Min/Sec
      ASSERT_EQ(dir->get_Degree(nullptr),E_POINTER);
      ASSERT_EQ(dir->get_Minute(nullptr),E_POINTER);
      ASSERT_EQ(dir->get_Second(nullptr),E_POINTER);

      dir->put_Value(0.780925757); // N 45 15 22.5 E
      ASSERT_EQ(dir->get_Degree(&deg),S_OK);
      ASSERT_EQ(dir->get_Minute(&min),S_OK);
      ASSERT_EQ(dir->get_Second(&sec),S_OK);
      ASSERT_EQ(deg,45);
      ASSERT_EQ(min,15);
      ASSERT_EQ(IsEqual(sec,22.5,0.1),true);

      dir->put_Value(2.360666897); // N 45 15 22.5 W
      ASSERT_EQ(dir->get_Degree(&deg),S_OK);
      ASSERT_EQ(dir->get_Minute(&min),S_OK);
      ASSERT_EQ(dir->get_Second(&sec),S_OK);
      ASSERT_EQ(deg,45);
      ASSERT_EQ(min,15);
      ASSERT_EQ(IsEqual(sec,22.5,0.1),true);

      dir->put_Value(3.922518411); // S 45 15 22.5 W
      ASSERT_EQ(dir->get_Degree(&deg),S_OK);
      ASSERT_EQ(dir->get_Minute(&min),S_OK);
      ASSERT_EQ(dir->get_Second(&sec),S_OK);
      ASSERT_EQ(deg,45);
      ASSERT_EQ(min,15);
      ASSERT_EQ(IsEqual(sec,22.5,0.1),true);

      dir->put_Value(5.502259551); // S 45 15 22.5 E
      ASSERT_EQ(dir->get_Degree(&deg),S_OK);
      ASSERT_EQ(dir->get_Minute(&min),S_OK);
      ASSERT_EQ(dir->get_Second(&sec),S_OK);
      ASSERT_EQ(deg,45);
      ASSERT_EQ(min,15);
      ASSERT_EQ(IsEqual(sec,22.5,0.1),true);

      // Put Deg,Min,Sec
      ASSERT_EQ(dir->put_Degree(100), E_INVALIDARG);
      ASSERT_EQ(dir->put_Degree(-1), E_INVALIDARG);
      ASSERT_EQ(dir->put_Degree(90), E_INVALIDARG); // Puts total angle > 90
      dir->put_Minute(0);
      dir->put_Second(0);
      ASSERT_EQ(dir->put_Degree(90),S_OK);
      ASSERT_EQ(dir->put_Degree( 0),S_OK);
      ASSERT_EQ(dir->put_Degree(60),S_OK);
      ASSERT_EQ(dir->get_Degree(&deg),S_OK);
      ASSERT_EQ(deg,60);

      ASSERT_EQ(dir->put_Minute(100), E_INVALIDARG);
      ASSERT_EQ(dir->put_Minute(-1), E_INVALIDARG);
      ASSERT_EQ(dir->put_Minute(60), E_INVALIDARG);
      ASSERT_EQ(dir->put_Minute( 0),S_OK);
      ASSERT_EQ(dir->put_Minute(30),S_OK);
      ASSERT_EQ(dir->get_Minute(&min),S_OK);
      ASSERT_EQ(min,30);

      ASSERT_EQ(dir->put_Second(100.), E_INVALIDARG);
      ASSERT_EQ(dir->put_Second(-1.), E_INVALIDARG);
      ASSERT_EQ(dir->put_Second(60.), E_INVALIDARG);
      ASSERT_EQ(dir->put_Second( 0.),S_OK);
      ASSERT_EQ(dir->put_Second(30.),S_OK);
      ASSERT_EQ(dir->get_Second(&sec),S_OK);
      ASSERT_EQ(IsEqual(sec,30.),true);

      // Test Increment
      ASSERT_EQ(dir->IncrementBy(CComVariant(dir)),E_INVALIDARG);

      dir->put_Value(M_PI/4.); // N 45 E
      ASSERT_EQ(dir->IncrementBy(CComVariant(M_PI/4.)),S_OK);
      dir->get_Value(&val);
      ASSERT_EQ(IsEqual(val,PI_OVER_2),true);

      // Make sure angle is properly normalized
      dir->put_Value(3*PI_OVER_2); // S 0 E
      ASSERT_EQ(dir->IncrementBy(CComVariant(M_PI)),S_OK);
      dir->get_Value(&val);
      ASSERT_EQ(IsEqual(val,PI_OVER_2),true);

      dir->put_Value(3*PI_OVER_2); // S 0 E
      ASSERT_EQ(dir->IncrementBy(CComVariant(-M_PI)),S_OK);
      dir->get_Value(&val);
      ASSERT_EQ(IsEqual(val,PI_OVER_2),true);

      dir->put_Value(3*PI_OVER_2); // S 0 E
      ASSERT_EQ(dir->IncrementBy(CComVariant((float)M_PI)),S_OK);
      dir->get_Value(&val);
      ASSERT_EQ(IsEqual(val,PI_OVER_2),true);

      dir->put_Value(1.0);
      ASSERT_EQ(dir->IncrementBy(CComVariant((short)1)),S_OK);
      dir->get_Value(&val);
      ASSERT_EQ(IsEqual(val,2.0),true);

      dir->put_Value(1.0);
      ASSERT_EQ(dir->IncrementBy(CComVariant((long)1)),S_OK);
      dir->get_Value(&val);
      ASSERT_EQ(IsEqual(val,2.0),true);

      dir->put_Value(1.0);
      ASSERT_EQ(dir->IncrementBy(CComVariant(CComBSTR("1"))),S_OK); // this is 1^ 00' 00"
      dir->get_Value(&val);
      ASSERT_EQ(IsEqual(val,1.0 + M_PI/180.0),true);

      CComPtr<IAngle> angle;
      angle.CoCreateInstance(CLSID_Angle);
      angle->put_Value(M_PI/4.);
      dir->put_Value(M_PI/4.); // N 45 E
      ASSERT_EQ(dir->IncrementBy(CComVariant(angle)),S_OK);
      dir->get_Value(&val);
      ASSERT_EQ(IsEqual(val,PI_OVER_2),true);

      CComPtr<IDirection> incDir;
      dir->put_Value(1.0);
      ASSERT_EQ(dir->Increment(CComVariant(dir),&incDir),E_INVALIDARG);
      ASSERT_EQ(dir->Increment(CComVariant(1.0),nullptr),E_POINTER);
      ASSERT_EQ(dir->Increment(CComVariant(1.0),&incDir),S_OK);
      dir->get_Value(&val);
      ASSERT_EQ(IsEqual(val,1.0),true);
      incDir->get_Value(&val);
      ASSERT_EQ(IsEqual(val,2.0),true);

      // Test FromString
      ASSERT_EQ(dir->FromString(nullptr),                       E_INVALIDARG);
      ASSERT_EQ(dir->FromString(CComBSTR()),                    E_INVALIDARG);
      ASSERT_EQ(dir->FromString(CComBSTR("")),                  E_INVALIDARG);
      ASSERT_EQ(dir->FromString(CComBSTR("         ")),         E_INVALIDARG);
      ASSERT_EQ(dir->FromString(CComBSTR("ABC123")),            E_INVALIDARG);
      ASSERT_EQ(dir->FromString(CComBSTR("N")),                 E_INVALIDARG);
      ASSERT_EQ(dir->FromString(CComBSTR("N S")),               E_INVALIDARG);
      ASSERT_EQ(dir->FromString(CComBSTR("N 100 45 12.3 E")),   E_INVALIDARG);
      ASSERT_EQ(dir->FromString(CComBSTR("N 45 90 22.5 E")),    E_INVALIDARG);
      ASSERT_EQ(dir->FromString(CComBSTR("N 45 15 90.5 E")),    E_INVALIDARG);
      ASSERT_EQ(dir->FromString(CComBSTR("0.76")),              E_INVALIDARG);
      ASSERT_EQ(dir->FromString(CComBSTR("E 45 15 22.5 W")),    E_INVALIDARG);
      ASSERT_EQ(dir->FromString(CComBSTR("N 45 15 22.5 N")),    E_INVALIDARG);
      ASSERT_EQ(dir->FromString(CComBSTR("NS 45 15 22.5 E")),   E_INVALIDARG);
      ASSERT_EQ(dir->FromString(CComBSTR("N 45 15 22.5 EW")),   E_INVALIDARG);
      ASSERT_EQ(dir->FromString(CComBSTR("N 0A 15 22.5 E")),    E_INVALIDARG);
      ASSERT_EQ(dir->FromString(CComBSTR("N A0 15 22.5 E")),    E_INVALIDARG);
      ASSERT_EQ(dir->FromString(CComBSTR("N 45 0A 22.5 E")),    E_INVALIDARG);
      ASSERT_EQ(dir->FromString(CComBSTR("N 45 A0 22.5 E")),    E_INVALIDARG);
      ASSERT_EQ(dir->FromString(CComBSTR("N 45 15 A0.0 E")),    E_INVALIDARG);
      ASSERT_EQ(dir->FromString(CComBSTR("N    45 15 22.5 E")), E_INVALIDARG);
      ASSERT_EQ(dir->FromString(CComBSTR("N 45    15 22.5 E")), E_INVALIDARG);
      ASSERT_EQ(dir->FromString(CComBSTR("N 45 15    22.5 E")), E_INVALIDARG);
      ASSERT_EQ(dir->FromString(CComBSTR("N 45 15 22.5    E")), E_INVALIDARG);

      ASSERT_EQ(dir->FromString(CComBSTR("        N 45 15 22.5 E")),S_OK);
      ASSERT_EQ(dir->FromString(CComBSTR("N 45 15 22.5 E"        )),S_OK);
      ASSERT_EQ(dir->FromString(CComBSTR("   N 45 15 22.5 E"     )),S_OK);
      ASSERT_EQ(dir->FromString(CComBSTR("N 45 15 22.5 E")),S_OK);
      dir->get_NSDirection(&nsDir);
      dir->get_Degree(&deg);
      dir->get_Minute(&min);
      dir->get_Second(&sec);
      dir->get_EWDirection(&ewDir);
      ASSERT_EQ(nsDir,nsNorth);
      ASSERT_EQ(deg,45);
      ASSERT_EQ(min,15);
      ASSERT_EQ(IsEqual(sec,22.5,0.1),true);
      ASSERT_EQ(ewDir,ewEast);

      ASSERT_EQ(dir->FromString(CComBSTR("N 00 15 22.5 E")),S_OK);
      dir->get_NSDirection(&nsDir);
      dir->get_Degree(&deg);
      dir->get_Minute(&min);
      dir->get_Second(&sec);
      dir->get_EWDirection(&ewDir);
      ASSERT_EQ(nsDir,nsNorth);
      ASSERT_EQ(deg,0);
      ASSERT_EQ(min,15);
      ASSERT_EQ(IsEqual(sec,22.5,0.1),true);
      ASSERT_EQ(ewDir,ewEast);

      ASSERT_EQ(dir->FromString(CComBSTR("N 45 00 22.5 E")),S_OK);
      dir->get_NSDirection(&nsDir);
      dir->get_Degree(&deg);
      dir->get_Minute(&min);
      dir->get_Second(&sec);
      dir->get_EWDirection(&ewDir);
      ASSERT_EQ(nsDir,nsNorth);
      ASSERT_EQ(deg,45);
      ASSERT_EQ(min,0);
      ASSERT_EQ(IsEqual(sec,22.5,0.1),true);
      ASSERT_EQ(ewDir,ewEast);

      ASSERT_EQ(dir->FromString(CComBSTR("N 45 15 0.00 E")),S_OK);
      dir->get_NSDirection(&nsDir);
      dir->get_Degree(&deg);
      dir->get_Minute(&min);
      dir->get_Second(&sec);
      dir->get_EWDirection(&ewDir);
      ASSERT_EQ(nsDir,nsNorth);
      ASSERT_EQ(deg,45);
      ASSERT_EQ(min,15);
      ASSERT_EQ(IsEqual(sec,0.00),true);
      ASSERT_EQ(ewDir,ewEast);

      ASSERT_EQ(dir->FromString(CComBSTR("N 45 E")),S_OK);
      dir->get_NSDirection(&nsDir);
      dir->get_Degree(&deg);
      dir->get_Minute(&min);
      dir->get_Second(&sec);
      dir->get_EWDirection(&ewDir);
      ASSERT_EQ(nsDir,nsNorth);
      ASSERT_EQ(deg,45);
      ASSERT_EQ(min,0);
      ASSERT_EQ(IsEqual(sec,0.00),true);
      ASSERT_EQ(ewDir,ewEast);

      ASSERT_EQ(dir->FromString(CComBSTR("N 0 E")),S_OK);
      dir->get_NSDirection(&nsDir);
      dir->get_Degree(&deg);
      dir->get_Minute(&min);
      dir->get_Second(&sec);
      dir->get_EWDirection(&ewDir);
      ASSERT_EQ(nsDir,nsNorth);
      ASSERT_EQ(deg,0);
      ASSERT_EQ(min,0);
      ASSERT_EQ(IsEqual(sec,0.00),true);
      ASSERT_EQ(ewDir,ewEast);

      ASSERT_EQ(dir->FromString(CComBSTR("N 0 W")),S_OK);
      dir->get_NSDirection(&nsDir);
      dir->get_Degree(&deg);
      dir->get_Minute(&min);
      dir->get_Second(&sec);
      dir->get_EWDirection(&ewDir);
      ASSERT_EQ(nsDir,nsNorth);
      ASSERT_EQ(deg,0);
      ASSERT_EQ(min,0);
      ASSERT_EQ(IsEqual(sec,0.00),true);
      ASSERT_EQ(ewDir,ewEast); // east is favored when ambiguous

      ASSERT_EQ(dir->FromString(CComBSTR("S 0 E")),S_OK);
      dir->get_NSDirection(&nsDir);
      dir->get_Degree(&deg);
      dir->get_Minute(&min);
      dir->get_Second(&sec);
      dir->get_EWDirection(&ewDir);
      ASSERT_EQ(nsDir,nsSouth);
      ASSERT_EQ(deg,0);
      ASSERT_EQ(min,0);
      ASSERT_EQ(IsEqual(sec,0.00),true);
      ASSERT_EQ(ewDir,ewEast);

      ASSERT_EQ(dir->FromString(CComBSTR("S 0 W")),S_OK);
      dir->get_NSDirection(&nsDir);
      dir->get_Degree(&deg);
      dir->get_Minute(&min);
      dir->get_Second(&sec);
      dir->get_EWDirection(&ewDir);
      ASSERT_EQ(nsDir,nsSouth);
      ASSERT_EQ(deg,0);
      ASSERT_EQ(min,0);
      ASSERT_EQ(IsEqual(sec,0.00),true);
      ASSERT_EQ(ewDir,ewEast); // east is favored when ambiguous

      ASSERT_EQ(dir->FromString(CComBSTR("N 34 54 W")),S_OK);
      dir->get_NSDirection(&nsDir);
      dir->get_Degree(&deg);
      dir->get_Minute(&min);
      dir->get_Second(&sec);
      dir->get_EWDirection(&ewDir);
      ASSERT_EQ(nsDir,nsNorth);
      ASSERT_EQ(deg,34);
      ASSERT_EQ(min,54);
      ASSERT_EQ(IsEqual(sec,0.00),true);
      ASSERT_EQ(ewDir,ewWest); // east is favored when ambiguous

      // Test FromDMS
      ASSERT_EQ(dir->FromDMS((NSDirectionType)4,45,15,22.5,ewEast),  E_INVALIDARG);
      ASSERT_EQ(dir->FromDMS(nsNorth,100,15,22.5,ewEast),            E_INVALIDARG);
      ASSERT_EQ(dir->FromDMS(nsNorth,-10,15,22.5,ewEast),            E_INVALIDARG);
      ASSERT_EQ(dir->FromDMS(nsNorth,45,90,22.5,ewEast),             E_INVALIDARG);
      ASSERT_EQ(dir->FromDMS(nsNorth,45,-1,22.5,ewEast),             E_INVALIDARG);
      ASSERT_EQ(dir->FromDMS(nsNorth,45,15,122.5,ewEast),            E_INVALIDARG);
      ASSERT_EQ(dir->FromDMS(nsNorth,45,15,-22.5,ewEast),            E_INVALIDARG);
      ASSERT_EQ(dir->FromDMS(nsNorth,45,15,22.5,(EWDirectionType)4), E_INVALIDARG);

      ASSERT_EQ(dir->FromDMS(nsNorth,45,15,22.5,ewEast),S_OK);
      dir->get_NSDirection(&nsDir);
      dir->get_Degree(&deg);
      dir->get_Minute(&min);
      dir->get_Second(&sec);
      dir->get_EWDirection(&ewDir);
      ASSERT_EQ(nsDir,nsNorth);
      ASSERT_EQ(deg,45);
      ASSERT_EQ(min,15);
      ASSERT_EQ(IsEqual(sec,22.5,0.1),true);
      ASSERT_EQ(ewDir,ewEast);

      // Test FromAzimuth
      ASSERT_EQ(dir->FromAzimuthEx(370,15,22.5),  E_INVALIDARG);
      ASSERT_EQ(dir->FromAzimuthEx(360,15,22.5),  E_INVALIDARG);
      ASSERT_EQ(dir->FromAzimuthEx(-360,15,22.5), E_INVALIDARG);
      ASSERT_EQ(dir->FromAzimuthEx(-370,15,22.5), E_INVALIDARG);
      ASSERT_EQ(dir->FromAzimuthEx(45,60,22.5),   E_INVALIDARG);
      ASSERT_EQ(dir->FromAzimuthEx(45,90,22.5),   E_INVALIDARG);
      ASSERT_EQ(dir->FromAzimuthEx(45,-15,22.5),  E_INVALIDARG);
      ASSERT_EQ(dir->FromAzimuthEx(45,15,60.0),   E_INVALIDARG);
      ASSERT_EQ(dir->FromAzimuthEx(45,15,90.5),   E_INVALIDARG);
      ASSERT_EQ(dir->FromAzimuthEx(45,15,-22.5),  E_INVALIDARG);

      ASSERT_EQ(dir->FromAzimuthEx(45,15,22.5),S_OK);
      dir->get_NSDirection(&nsDir);
      dir->get_Degree(&deg);
      dir->get_Minute(&min);
      dir->get_Second(&sec);
      dir->get_EWDirection(&ewDir);
      ASSERT_EQ(nsDir,nsNorth);
      ASSERT_EQ(deg,45);
      ASSERT_EQ(min,15);
      ASSERT_EQ(IsEqual(sec,22.5,0.1),true);
      ASSERT_EQ(ewDir,ewEast);

      ASSERT_EQ(dir->FromAzimuthEx(-45,15,22.5),S_OK);
      dir->get_NSDirection(&nsDir);
      dir->get_Degree(&deg);
      dir->get_Minute(&min);
      dir->get_Second(&sec);
      dir->get_EWDirection(&ewDir);
      ASSERT_EQ(nsDir,nsNorth);
      ASSERT_EQ(deg,45);
      ASSERT_EQ(min,15);
      ASSERT_EQ(IsEqual(sec,22.5,0.1),true);
      ASSERT_EQ(ewDir,ewWest);

      // Test AngleBetween
      CComPtr<IDirection> dir1;
      CComPtr<IDirection> dir2;
      dir1.CoCreateInstance(CLSID_Direction);
      dir2.CoCreateInstance(CLSID_Direction);

      dir1->FromDMS(nsNorth,45,0,0,ewEast);
      dir2->FromDMS(nsNorth,45,0,0,ewWest);

      angle.Release();
      // angle = dir1 - dir2;
      ASSERT_EQ( dir1->AngleBetween(dir2,nullptr), E_POINTER );
      ASSERT_EQ( dir1->AngleBetween(nullptr,&angle), E_INVALIDARG );
      ASSERT_EQ( dir1->AngleBetween(dir2,&angle), S_OK );
      angle->get_Value(&val);
      ASSERT_EQ(IsEqual(val,PI_OVER_2),S_OK);

      // angle = dir2 - dir1;
      angle.Release();
      ASSERT_EQ( dir2->AngleBetween(dir1,&angle), S_OK );
      angle->get_Value(&val);
      ASSERT_EQ(IsEqual(val,3*PI_OVER_2),S_OK);

      // angle = dir1 - dir1;
      angle.Release();
      ASSERT_EQ( dir1->AngleBetween(dir1,&angle), S_OK );
      angle->get_Value(&val);
      ASSERT_EQ(IsEqual(val,0.0),true);

      // Test ISupportErrorInfo
      CComQIPtr<ISupportErrorInfo> eInfo(dir);
      ASSERT_EQ( eInfo != 0, true );

      // Interfaces that should be supported
      ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_IDirection ), S_OK );

      // Interface that is not supported
      ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

      // Test IObjectSafety
      ASSERT_EQ( TestIObjectSafety(CLSID_Direction,IID_IDirection,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
   }
};
} // namespace CogoUnitTests