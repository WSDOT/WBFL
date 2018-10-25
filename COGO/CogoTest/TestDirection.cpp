///////////////////////////////////////////////////////////////////////
// COGOTest - Test Driver for Coordinate Geometry Library
// Copyright © 1999-2015  Washington State Department of Transportation
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

// TestDirection.cpp: implementation of the TestDirection class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestDirection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestDirection::CTestDirection()
{

}

CTestDirection::~CTestDirection()
{

}

void CTestDirection::Test()
{
   CComPtr<IDirection> dir;
   TRY_TEST(dir.CoCreateInstance(CLSID_Direction),S_OK);

   Float64 val;
   NSDirectionType nsDir;
   long deg, min;
   Float64 sec;
   EWDirectionType ewDir;

   // Test initial value
   TRY_TEST(dir->get_Value(NULL),E_POINTER);
   TRY_TEST(dir->get_Value(&val),S_OK);
   TRY_TEST(IsZero(val),true);

   // Set/Get value (value should be normalized)
   TRY_TEST(dir->put_Value(3.23),S_OK);
   TRY_TEST(dir->get_Value(&val),S_OK);
   TRY_TEST(IsEqual(3.23,val),true);

   TRY_TEST(dir->put_Value(-3.23),S_OK);
   TRY_TEST(dir->get_Value(&val),S_OK);
   TRY_TEST(IsEqual(TWO_PI - 3.23,val),true);

   // N 45 15 22.5 E =  44.74375deg = 0.780925757rad
   // N 45 15 22.5 W = 135.25625deg = 2.360666897rad
   // S 45 15 22.5 W = 224.74375deg = 3.922518411rad
   // S 45 15 22.5 E = 315.25625deg = 5.502259551rad

   // North/South and East/West Direction
   TRY_TEST(dir->get_NSDirection(NULL),E_POINTER);   
   TRY_TEST(dir->get_EWDirection(NULL),E_POINTER);   
   TRY_TEST(dir->put_NSDirection((NSDirectionType)4),COGO_E_BADDIRECTION);
   TRY_TEST(dir->put_EWDirection((EWDirectionType)4),COGO_E_BADDIRECTION);

   dir->put_Value(0.780925757);
   TRY_TEST(dir->get_NSDirection(&nsDir),S_OK);   
   TRY_TEST(nsDir,nsNorth);
   TRY_TEST(dir->get_EWDirection(&ewDir),S_OK);   
   TRY_TEST(ewDir,ewEast);

   dir->put_Value(2.360666897);
   TRY_TEST(dir->get_NSDirection(&nsDir),S_OK);   
   TRY_TEST(nsDir,nsNorth);
   TRY_TEST(dir->get_EWDirection(&ewDir),S_OK);   
   TRY_TEST(ewDir,ewWest);

   dir->put_Value(3.922548411);
   TRY_TEST(dir->get_NSDirection(&nsDir),S_OK);   
   TRY_TEST(nsDir,nsSouth);
   TRY_TEST(dir->get_EWDirection(&ewDir),S_OK);   
   TRY_TEST(ewDir,ewWest);

   dir->put_Value(5.502259551);
   TRY_TEST(dir->get_NSDirection(&nsDir),S_OK);   
   TRY_TEST(nsDir,nsSouth);
   TRY_TEST(dir->get_EWDirection(&ewDir),S_OK);   
   TRY_TEST(ewDir,ewEast);

   // Swap around the N/S, E/W and check the resulting value
   dir->put_Value(0.780925757); // N 45 15 22.5 E
   TRY_TEST(dir->put_NSDirection(nsSouth),S_OK);
   dir->get_Value(&val);
   TRY_TEST(IsEqual(val,5.502259551),true); // S 45 15 22.5 E

   TRY_TEST(dir->put_EWDirection(ewWest),S_OK);
   dir->get_Value(&val);
   TRY_TEST(IsEqual(val,3.922518411),true); // S 45 15 22.5 W

   TRY_TEST(dir->put_NSDirection(nsNorth),S_OK);
   dir->get_Value(&val);
   TRY_TEST(IsEqual(val,2.360666897),true); // N 45 15 22.5 W

   TRY_TEST(dir->put_EWDirection(ewEast),S_OK);
   dir->get_Value(&val);
   TRY_TEST(IsEqual(val,0.780925757),true); // N 45 15 22.5 E

   // Get Degree/Min/Sec
   TRY_TEST(dir->get_Degree(NULL),E_POINTER);
   TRY_TEST(dir->get_Minute(NULL),E_POINTER);
   TRY_TEST(dir->get_Second(NULL),E_POINTER);

   dir->put_Value(0.780925757); // N 45 15 22.5 E
   TRY_TEST(dir->get_Degree(&deg),S_OK);
   TRY_TEST(dir->get_Minute(&min),S_OK);
   TRY_TEST(dir->get_Second(&sec),S_OK);
   TRY_TEST(deg,45);
   TRY_TEST(min,15);
   TRY_TEST(IsEqual(sec,22.5,0.1),true);

   dir->put_Value(2.360666897); // N 45 15 22.5 W
   TRY_TEST(dir->get_Degree(&deg),S_OK);
   TRY_TEST(dir->get_Minute(&min),S_OK);
   TRY_TEST(dir->get_Second(&sec),S_OK);
   TRY_TEST(deg,45);
   TRY_TEST(min,15);
   TRY_TEST(IsEqual(sec,22.5,0.1),true);

   dir->put_Value(3.922518411); // S 45 15 22.5 W
   TRY_TEST(dir->get_Degree(&deg),S_OK);
   TRY_TEST(dir->get_Minute(&min),S_OK);
   TRY_TEST(dir->get_Second(&sec),S_OK);
   TRY_TEST(deg,45);
   TRY_TEST(min,15);
   TRY_TEST(IsEqual(sec,22.5,0.1),true);

   dir->put_Value(5.502259551); // S 45 15 22.5 E
   TRY_TEST(dir->get_Degree(&deg),S_OK);
   TRY_TEST(dir->get_Minute(&min),S_OK);
   TRY_TEST(dir->get_Second(&sec),S_OK);
   TRY_TEST(deg,45);
   TRY_TEST(min,15);
   TRY_TEST(IsEqual(sec,22.5,0.1),true);

   // Put Deg,Min,Sec
   TRY_TEST(dir->put_Degree(100),COGO_E_BADDIRECTION);
   TRY_TEST(dir->put_Degree(-1),COGO_E_BADDIRECTION);
   TRY_TEST(dir->put_Degree(90),COGO_E_BADDIRECTION); // Puts total angle > 90
   dir->put_Minute(0);
   dir->put_Second(0);
   TRY_TEST(dir->put_Degree(90),S_OK);
   TRY_TEST(dir->put_Degree( 0),S_OK);
   TRY_TEST(dir->put_Degree(60),S_OK);
   TRY_TEST(dir->get_Degree(&deg),S_OK);
   TRY_TEST(deg,60);

   TRY_TEST(dir->put_Minute(100),COGO_E_BADDIRECTION);
   TRY_TEST(dir->put_Minute(-1),COGO_E_BADDIRECTION);
   TRY_TEST(dir->put_Minute(60),COGO_E_BADDIRECTION);
   TRY_TEST(dir->put_Minute( 0),S_OK);
   TRY_TEST(dir->put_Minute(30),S_OK);
   TRY_TEST(dir->get_Minute(&min),S_OK);
   TRY_TEST(min,30);

   TRY_TEST(dir->put_Second(100.),COGO_E_BADDIRECTION);
   TRY_TEST(dir->put_Second(-1.),COGO_E_BADDIRECTION);
   TRY_TEST(dir->put_Second(60.),COGO_E_BADDIRECTION);
   TRY_TEST(dir->put_Second( 0.),S_OK);
   TRY_TEST(dir->put_Second(30.),S_OK);
   TRY_TEST(dir->get_Second(&sec),S_OK);
   TRY_TEST(IsEqual(sec,30.),true);

   // Test Increment
   TRY_TEST(dir->IncrementBy(CComVariant(dir)),E_INVALIDARG);

   dir->put_Value(M_PI/4.); // N 45 E
   TRY_TEST(dir->IncrementBy(CComVariant(M_PI/4.)),S_OK);
   dir->get_Value(&val);
   TRY_TEST(IsEqual(val,PI_OVER_2),true);

   // Make sure angle is properly normalized
   dir->put_Value(3*PI_OVER_2); // S 0 E
   TRY_TEST(dir->IncrementBy(CComVariant(M_PI)),S_OK);
   dir->get_Value(&val);
   TRY_TEST(IsEqual(val,PI_OVER_2),true);

   dir->put_Value(3*PI_OVER_2); // S 0 E
   TRY_TEST(dir->IncrementBy(CComVariant(-M_PI)),S_OK);
   dir->get_Value(&val);
   TRY_TEST(IsEqual(val,PI_OVER_2),true);

   dir->put_Value(3*PI_OVER_2); // S 0 E
   TRY_TEST(dir->IncrementBy(CComVariant((float)M_PI)),S_OK);
   dir->get_Value(&val);
   TRY_TEST(IsEqual(val,PI_OVER_2),true);

   dir->put_Value(1.0);
   TRY_TEST(dir->IncrementBy(CComVariant((short)1)),S_OK);
   dir->get_Value(&val);
   TRY_TEST(IsEqual(val,2.0),true);

   dir->put_Value(1.0);
   TRY_TEST(dir->IncrementBy(CComVariant((long)1)),S_OK);
   dir->get_Value(&val);
   TRY_TEST(IsEqual(val,2.0),true);

   dir->put_Value(1.0);
   TRY_TEST(dir->IncrementBy(CComVariant(CComBSTR("1"))),S_OK); // this is 1^ 00' 00"
   dir->get_Value(&val);
   TRY_TEST(IsEqual(val,1.0 + M_PI/180.0),true);

   CComPtr<IAngle> angle;
   angle.CoCreateInstance(CLSID_Angle);
   angle->put_Value(M_PI/4.);
   dir->put_Value(M_PI/4.); // N 45 E
   TRY_TEST(dir->IncrementBy(CComVariant(angle)),S_OK);
   dir->get_Value(&val);
   TRY_TEST(IsEqual(val,PI_OVER_2),true);

   CComPtr<IDirection> incDir;
   dir->put_Value(1.0);
   TRY_TEST(dir->Increment(CComVariant(dir),&incDir),E_INVALIDARG);
   TRY_TEST(dir->Increment(CComVariant(1.0),NULL),E_POINTER);
   TRY_TEST(dir->Increment(CComVariant(1.0),&incDir),S_OK);
   dir->get_Value(&val);
   TRY_TEST(IsEqual(val,1.0),true);
   incDir->get_Value(&val);
   TRY_TEST(IsEqual(val,2.0),true);

   // Test FromString
   TRY_TEST(dir->FromString(NULL),                          E_INVALIDARG);
   TRY_TEST(dir->FromString(CComBSTR()),                    E_INVALIDARG);
   TRY_TEST(dir->FromString(CComBSTR("")),                  COGO_E_BADDIRECTIONSTRING);
   TRY_TEST(dir->FromString(CComBSTR("         ")),         COGO_E_BADDIRECTIONSTRING);
   TRY_TEST(dir->FromString(CComBSTR("ABC123")),            COGO_E_BADDIRECTIONSTRING);
   TRY_TEST(dir->FromString(CComBSTR("N")),                 COGO_E_BADDIRECTIONSTRING);
   TRY_TEST(dir->FromString(CComBSTR("N S")),               COGO_E_BADDIRECTIONSTRING);
   TRY_TEST(dir->FromString(CComBSTR("N 100 45 12.3 E")),   COGO_E_BADDIRECTIONSTRING);
   TRY_TEST(dir->FromString(CComBSTR("N 45 90 22.5 E")),    COGO_E_BADDIRECTIONSTRING);
   TRY_TEST(dir->FromString(CComBSTR("N 45 15 90.5 E")),    COGO_E_BADDIRECTIONSTRING);
   TRY_TEST(dir->FromString(CComBSTR("0.76")),              COGO_E_BADDIRECTIONSTRING);
   TRY_TEST(dir->FromString(CComBSTR("E 45 15 22.5 W")),    COGO_E_BADDIRECTIONSTRING);
   TRY_TEST(dir->FromString(CComBSTR("N 45 15 22.5 N")),    COGO_E_BADDIRECTIONSTRING);
   TRY_TEST(dir->FromString(CComBSTR("NS 45 15 22.5 E")),   COGO_E_BADDIRECTIONSTRING);
   TRY_TEST(dir->FromString(CComBSTR("N 45 15 22.5 EW")),   COGO_E_BADDIRECTIONSTRING);
   TRY_TEST(dir->FromString(CComBSTR("N 0A 15 22.5 E")),    COGO_E_BADDIRECTIONSTRING);
   TRY_TEST(dir->FromString(CComBSTR("N A0 15 22.5 E")),    COGO_E_BADDIRECTIONSTRING);
   TRY_TEST(dir->FromString(CComBSTR("N 45 0A 22.5 E")),    COGO_E_BADDIRECTIONSTRING);
   TRY_TEST(dir->FromString(CComBSTR("N 45 A0 22.5 E")),    COGO_E_BADDIRECTIONSTRING);
   TRY_TEST(dir->FromString(CComBSTR("N 45 15 A0.0 E")),    COGO_E_BADDIRECTIONSTRING);
   TRY_TEST(dir->FromString(CComBSTR("N    45 15 22.5 E")), COGO_E_BADDIRECTIONSTRING);
   TRY_TEST(dir->FromString(CComBSTR("N 45    15 22.5 E")), COGO_E_BADDIRECTIONSTRING);
   TRY_TEST(dir->FromString(CComBSTR("N 45 15    22.5 E")), COGO_E_BADDIRECTIONSTRING);
   TRY_TEST(dir->FromString(CComBSTR("N 45 15 22.5    E")), COGO_E_BADDIRECTIONSTRING);

   TRY_TEST(dir->FromString(CComBSTR("        N 45 15 22.5 E")),S_OK);
   TRY_TEST(dir->FromString(CComBSTR("N 45 15 22.5 E"        )),S_OK);
   TRY_TEST(dir->FromString(CComBSTR("   N 45 15 22.5 E"     )),S_OK);
   TRY_TEST(dir->FromString(CComBSTR("N 45 15 22.5 E")),S_OK);
   dir->get_NSDirection(&nsDir);
   dir->get_Degree(&deg);
   dir->get_Minute(&min);
   dir->get_Second(&sec);
   dir->get_EWDirection(&ewDir);
   TRY_TEST(nsDir,nsNorth);
   TRY_TEST(deg,45);
   TRY_TEST(min,15);
   TRY_TEST(IsEqual(sec,22.5,0.1),true);
   TRY_TEST(ewDir,ewEast);

   TRY_TEST(dir->FromString(CComBSTR("N 00 15 22.5 E")),S_OK);
   dir->get_NSDirection(&nsDir);
   dir->get_Degree(&deg);
   dir->get_Minute(&min);
   dir->get_Second(&sec);
   dir->get_EWDirection(&ewDir);
   TRY_TEST(nsDir,nsNorth);
   TRY_TEST(deg,0);
   TRY_TEST(min,15);
   TRY_TEST(IsEqual(sec,22.5,0.1),true);
   TRY_TEST(ewDir,ewEast);

   TRY_TEST(dir->FromString(CComBSTR("N 45 00 22.5 E")),S_OK);
   dir->get_NSDirection(&nsDir);
   dir->get_Degree(&deg);
   dir->get_Minute(&min);
   dir->get_Second(&sec);
   dir->get_EWDirection(&ewDir);
   TRY_TEST(nsDir,nsNorth);
   TRY_TEST(deg,45);
   TRY_TEST(min,0);
   TRY_TEST(IsEqual(sec,22.5,0.1),true);
   TRY_TEST(ewDir,ewEast);

   TRY_TEST(dir->FromString(CComBSTR("N 45 15 0.00 E")),S_OK);
   dir->get_NSDirection(&nsDir);
   dir->get_Degree(&deg);
   dir->get_Minute(&min);
   dir->get_Second(&sec);
   dir->get_EWDirection(&ewDir);
   TRY_TEST(nsDir,nsNorth);
   TRY_TEST(deg,45);
   TRY_TEST(min,15);
   TRY_TEST(IsEqual(sec,0.00),true);
   TRY_TEST(ewDir,ewEast);

   TRY_TEST(dir->FromString(CComBSTR("N 45 E")),S_OK);
   dir->get_NSDirection(&nsDir);
   dir->get_Degree(&deg);
   dir->get_Minute(&min);
   dir->get_Second(&sec);
   dir->get_EWDirection(&ewDir);
   TRY_TEST(nsDir,nsNorth);
   TRY_TEST(deg,45);
   TRY_TEST(min,0);
   TRY_TEST(IsEqual(sec,0.00),true);
   TRY_TEST(ewDir,ewEast);

   TRY_TEST(dir->FromString(CComBSTR("N 0 E")),S_OK);
   dir->get_NSDirection(&nsDir);
   dir->get_Degree(&deg);
   dir->get_Minute(&min);
   dir->get_Second(&sec);
   dir->get_EWDirection(&ewDir);
   TRY_TEST(nsDir,nsNorth);
   TRY_TEST(deg,0);
   TRY_TEST(min,0);
   TRY_TEST(IsEqual(sec,0.00),true);
   TRY_TEST(ewDir,ewEast);

   TRY_TEST(dir->FromString(CComBSTR("N 0 W")),S_OK);
   dir->get_NSDirection(&nsDir);
   dir->get_Degree(&deg);
   dir->get_Minute(&min);
   dir->get_Second(&sec);
   dir->get_EWDirection(&ewDir);
   TRY_TEST(nsDir,nsNorth);
   TRY_TEST(deg,0);
   TRY_TEST(min,0);
   TRY_TEST(IsEqual(sec,0.00),true);
   TRY_TEST(ewDir,ewEast); // east is favored when ambiguous

   TRY_TEST(dir->FromString(CComBSTR("S 0 E")),S_OK);
   dir->get_NSDirection(&nsDir);
   dir->get_Degree(&deg);
   dir->get_Minute(&min);
   dir->get_Second(&sec);
   dir->get_EWDirection(&ewDir);
   TRY_TEST(nsDir,nsSouth);
   TRY_TEST(deg,0);
   TRY_TEST(min,0);
   TRY_TEST(IsEqual(sec,0.00),true);
   TRY_TEST(ewDir,ewEast);

   TRY_TEST(dir->FromString(CComBSTR("S 0 W")),S_OK);
   dir->get_NSDirection(&nsDir);
   dir->get_Degree(&deg);
   dir->get_Minute(&min);
   dir->get_Second(&sec);
   dir->get_EWDirection(&ewDir);
   TRY_TEST(nsDir,nsSouth);
   TRY_TEST(deg,0);
   TRY_TEST(min,0);
   TRY_TEST(IsEqual(sec,0.00),true);
   TRY_TEST(ewDir,ewEast); // east is favored when ambiguous

   TRY_TEST(dir->FromString(CComBSTR("N 34 54 W")),S_OK);
   dir->get_NSDirection(&nsDir);
   dir->get_Degree(&deg);
   dir->get_Minute(&min);
   dir->get_Second(&sec);
   dir->get_EWDirection(&ewDir);
   TRY_TEST(nsDir,nsNorth);
   TRY_TEST(deg,34);
   TRY_TEST(min,54);
   TRY_TEST(IsEqual(sec,0.00),true);
   TRY_TEST(ewDir,ewWest); // east is favored when ambiguous

   // Test FromDMS
   TRY_TEST(dir->FromDMS((NSDirectionType)4,45,15,22.5,ewEast),  COGO_E_BADDIRECTION);
   TRY_TEST(dir->FromDMS(nsNorth,100,15,22.5,ewEast),            COGO_E_BADDIRECTION);
   TRY_TEST(dir->FromDMS(nsNorth,-10,15,22.5,ewEast),            COGO_E_BADDIRECTION);
   TRY_TEST(dir->FromDMS(nsNorth,45,90,22.5,ewEast),             COGO_E_BADDIRECTION);
   TRY_TEST(dir->FromDMS(nsNorth,45,-1,22.5,ewEast),             COGO_E_BADDIRECTION);
   TRY_TEST(dir->FromDMS(nsNorth,45,15,122.5,ewEast),            COGO_E_BADDIRECTION);
   TRY_TEST(dir->FromDMS(nsNorth,45,15,-22.5,ewEast),            COGO_E_BADDIRECTION);
   TRY_TEST(dir->FromDMS(nsNorth,45,15,22.5,(EWDirectionType)4), COGO_E_BADDIRECTION);

   TRY_TEST(dir->FromDMS(nsNorth,45,15,22.5,ewEast),S_OK);
   dir->get_NSDirection(&nsDir);
   dir->get_Degree(&deg);
   dir->get_Minute(&min);
   dir->get_Second(&sec);
   dir->get_EWDirection(&ewDir);
   TRY_TEST(nsDir,nsNorth);
   TRY_TEST(deg,45);
   TRY_TEST(min,15);
   TRY_TEST(IsEqual(sec,22.5,0.1),true);
   TRY_TEST(ewDir,ewEast);

   // Test FromAzimuth
   TRY_TEST(dir->FromAzimuthEx(370,15,22.5),  COGO_E_BADAZIMUTH);
   TRY_TEST(dir->FromAzimuthEx(360,15,22.5),  COGO_E_BADAZIMUTH);
   TRY_TEST(dir->FromAzimuthEx(-360,15,22.5), COGO_E_BADAZIMUTH);
   TRY_TEST(dir->FromAzimuthEx(-370,15,22.5), COGO_E_BADAZIMUTH);
   TRY_TEST(dir->FromAzimuthEx(45,60,22.5),   COGO_E_BADAZIMUTH);
   TRY_TEST(dir->FromAzimuthEx(45,90,22.5),   COGO_E_BADAZIMUTH);
   TRY_TEST(dir->FromAzimuthEx(45,-15,22.5),  COGO_E_BADAZIMUTH);
   TRY_TEST(dir->FromAzimuthEx(45,15,60.0),   COGO_E_BADAZIMUTH);
   TRY_TEST(dir->FromAzimuthEx(45,15,90.5),   COGO_E_BADAZIMUTH);
   TRY_TEST(dir->FromAzimuthEx(45,15,-22.5),  COGO_E_BADAZIMUTH);

   TRY_TEST(dir->FromAzimuthEx(45,15,22.5),S_OK);
   dir->get_NSDirection(&nsDir);
   dir->get_Degree(&deg);
   dir->get_Minute(&min);
   dir->get_Second(&sec);
   dir->get_EWDirection(&ewDir);
   TRY_TEST(nsDir,nsNorth);
   TRY_TEST(deg,45);
   TRY_TEST(min,15);
   TRY_TEST(IsEqual(sec,22.5,0.1),true);
   TRY_TEST(ewDir,ewEast);

   TRY_TEST(dir->FromAzimuthEx(-45,15,22.5),S_OK);
   dir->get_NSDirection(&nsDir);
   dir->get_Degree(&deg);
   dir->get_Minute(&min);
   dir->get_Second(&sec);
   dir->get_EWDirection(&ewDir);
   TRY_TEST(nsDir,nsNorth);
   TRY_TEST(deg,45);
   TRY_TEST(min,15);
   TRY_TEST(IsEqual(sec,22.5,0.1),true);
   TRY_TEST(ewDir,ewWest);

   // Test AngleBetween
   CComPtr<IDirection> dir1;
   CComPtr<IDirection> dir2;
   dir1.CoCreateInstance(CLSID_Direction);
   dir2.CoCreateInstance(CLSID_Direction);

   dir1->FromDMS(nsNorth,45,0,0,ewEast);
   dir2->FromDMS(nsNorth,45,0,0,ewWest);

   angle.Release();
   // angle = dir1 - dir2;
   TRY_TEST( dir1->AngleBetween(dir2,NULL), E_POINTER );
   TRY_TEST( dir1->AngleBetween(NULL,&angle), E_INVALIDARG );
   TRY_TEST( dir1->AngleBetween(dir2,&angle), S_OK );
   angle->get_Value(&val);
   TRY_TEST(IsEqual(val,PI_OVER_2),S_OK);

   // angle = dir2 - dir1;
   angle.Release();
   TRY_TEST( dir2->AngleBetween(dir1,&angle), S_OK );
   angle->get_Value(&val);
   TRY_TEST(IsEqual(val,3*PI_OVER_2),S_OK);

   // angle = dir1 - dir1;
   angle.Release();
   TRY_TEST( dir1->AngleBetween(dir1,&angle), S_OK );
   angle->get_Value(&val);
   TRY_TEST(IsEqual(val,0.0),true);

   // Test ISupportErrorInfo
   CComQIPtr<ISupportErrorInfo> eInfo(dir);
   TRY_TEST( eInfo != 0, true );

   // Interfaces that should be supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IDirection ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );

   // Interface that is not supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

   // Test IObjectSafety
   TRY_TEST( TestIObjectSafety(CLSID_Direction,IID_IDirection,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
   TRY_TEST( TestIObjectSafety(CLSID_Direction,IID_IStructuredStorage2,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
}
