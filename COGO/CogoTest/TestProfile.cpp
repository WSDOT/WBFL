///////////////////////////////////////////////////////////////////////
// COGOTest - Test Driver for Coordinate Geometry Library
// Copyright © 1999-2012  Washington State Department of Transportation
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

// TestProfile.cpp: implementation of the CTestProfile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestProfile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
void TestGrade(IProfile* profile,Float64 results[]);
void TestCrownSlopes(IProfile* profile,Float64 results[][2]);
void TestElevation(IProfile* profile,Float64 offset,Float64 results[]);

CTestProfile::CTestProfile()
{

}

void CTestProfile::Test()
{
   Test1();
   Test2();
   Test3();
   Test4();
   Test5();
   Test6();
   Test7();
   Test8();
   Test9();
   Test10();
   Test11();

   // Test IObjectSafety
   TRY_TEST( TestIObjectSafety(CLSID_Profile,IID_IProfile,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
   TRY_TEST( TestIObjectSafety(CLSID_Profile,IID_IStructuredStorage2,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
}

void CTestProfile::Test1()
{
   CComPtr<IProfile> profile;
   TRY_TEST(profile.CoCreateInstance(CLSID_Profile),S_OK);

   //
   // Test Add
   //

   // Create a profile point
   CComPtr<IProfilePoint> point;
   point.CoCreateInstance(CLSID_ProfilePoint);
   point->put_Station(CComVariant(100.0));
   point->put_Elevation(50.0);

   // Create a profile element and assign the profile point to it
   CComPtr<IProfileElement> element;
   element.CoCreateInstance(CLSID_ProfileElement);
   element->putref_Value(point);

   // add it to the profile
   TRY_TEST(profile->Add(NULL),E_INVALIDARG);
   TRY_TEST(profile->Add(element),S_OK);

   //
   // Test AddEx
   //

   // create a new point
   point.Release();
   point.CoCreateInstance(CLSID_ProfilePoint);
   point->put_Station(CComVariant(50));
   point->put_Elevation(10);

   // add it to the profile
   TRY_TEST(profile->AddEx(NULL),E_INVALIDARG);
   TRY_TEST(profile->AddEx(profile),COGO_E_PROFILEELEMENTTYPE);
   TRY_TEST(profile->AddEx(point), S_OK);

   // create a vertical curve
   CComPtr<IVertCurve> vc;
   vc.CoCreateInstance(CLSID_VertCurve);
   point.Release();
   vc->get_PBG(&point);
   point->put_Station(CComVariant(200));
   point->put_Elevation(250);

   point.Release();
   vc->get_PVI(&point);
   point->put_Station(CComVariant(300));
   point->put_Elevation(250);

   point.Release();
   vc->get_PFG(&point);
   point->put_Station(CComVariant(400));
   point->put_Elevation(150);

   vc->put_L1(100);
   vc->put_L2(100);

   // add it to the profile
   TRY_TEST(profile->AddEx(vc), S_OK);

   //
   // Test Count
   //
   CollectionIndexType count;
   TRY_TEST(profile->get_Count(NULL),E_POINTER);
   TRY_TEST(profile->get_Count(&count),S_OK);
   TRY_TEST(count,3);

   //
   // Test Item
   //

   // make sure items are sorted properly
   element.Release();
   TRY_TEST(profile->get_Item(-1,&element),E_INVALIDARG);
   TRY_TEST(profile->get_Item(100,&element),E_INVALIDARG);
   TRY_TEST(profile->get_Item(0,NULL),E_POINTER);
   TRY_TEST(profile->get_Item(0,&element),S_OK);
   ProfileElementType type;
   element->get_Type(&type);
   TRY_TEST(type,pePoint);
   CComPtr<IUnknown> dispVal;
   element->get_Value(&dispVal);
   point.Release();
   dispVal->QueryInterface(&point);
   CComPtr<IStation> station;
   Float64 sta, elev;
   point->get_Station(&station);
   station->get_Value(&sta);
   point->get_Elevation(&elev);
   TRY_TEST(IsEqual(sta,50.0),true);
   TRY_TEST(IsEqual(elev,10.0),true);

   element.Release();
   TRY_TEST(profile->get_Item(1,&element),S_OK);
   element->get_Type(&type);
   TRY_TEST(type,pePoint);
   dispVal.Release();
   element->get_Value(&dispVal);
   point.Release();
   dispVal->QueryInterface(&point);
   station.Release();
   point->get_Station(&station);
   station->get_Value(&sta);
   point->get_Elevation(&elev);
   TRY_TEST(IsEqual(sta,100.0),true);
   TRY_TEST(IsEqual(elev,50.0),true);

   element.Release();
   TRY_TEST(profile->get_Item(2,&element),S_OK);
   element->get_Type(&type);
   TRY_TEST(type,peVertCurve);
   dispVal.Release();
   element->get_Value(&dispVal);
   vc.Release();
   dispVal->QueryInterface(&vc);
   point.Release();
   vc->get_BVC(&point);
   station.Release();
   point->get_Station(&station);
   station->get_Value(&sta);
   point->get_Elevation(&elev);
   TRY_TEST(IsEqual(sta,200.0),true);
   TRY_TEST(IsEqual(elev,250.0),true);

   TRY_TEST(profile->putref_Item(1,NULL),E_INVALIDARG);
   TRY_TEST(profile->putref_Item(-1,element),E_INVALIDARG);
   TRY_TEST(profile->putref_Item(100,element),E_INVALIDARG);
   TRY_TEST(profile->putref_Item(1,element),S_OK);
   element.Release();
   TRY_TEST(profile->get_Item(1,&element),S_OK);
   element->get_Type(&type);
   TRY_TEST(type,peVertCurve);

   //
   // Test Remove
   //
   point.Release();
   vc->get_BVC(&point);
   TRY_TEST(profile->Remove(CComVariant()),E_INVALIDARG);
   TRY_TEST(profile->Remove(CComVariant(profile)),E_INVALIDARG);
   TRY_TEST(profile->Remove(CComVariant(-1)),E_INVALIDARG);
   TRY_TEST(profile->Remove(CComVariant(100)),E_INVALIDARG);
   TRY_TEST(profile->Remove(CComVariant(point)),E_INVALIDARG);
   TRY_TEST(profile->Remove(CComVariant(vc)),S_OK); // Remove the vert curve
   TRY_TEST(profile->Remove(CComVariant(1)),S_OK);  // Remove the element at index 1

   profile->get_Count(&count);
   TRY_TEST(count,1);

   //
   // Test CrossSections
   //
   CComPtr<ICrossSectionCollection> sections;
   TRY_TEST(profile->get_CrossSections(NULL),E_POINTER);
   TRY_TEST(profile->get_CrossSections(&sections),S_OK);
   TRY_TEST(profile->putref_CrossSections(NULL),E_INVALIDARG);
   TRY_TEST(profile->putref_CrossSections(sections),S_OK);

   //
   // Test Clear
   //
   TRY_TEST(profile->Clear(),S_OK);
   profile->get_Count(&count);
   TRY_TEST(count,0);
   
   //
   // Test _Enum
   //
   profile->Clear();
   profile->Add(element);
   profile->Add(element);
   CComPtr<IEnumProfileElements> pEnum;
   TRY_TEST(profile->get__EnumProfileElements(NULL), E_POINTER );
   TRY_TEST(profile->get__EnumProfileElements(&pEnum), S_OK );

   ULONG fetched;
   CComPtr<IProfileElement> pe;
   TRY_TEST(pEnum->Next(1,&pe,&fetched ),S_OK);
   TRY_TEST(pe.IsEqualObject(element),true);

   pe.Release();
   TRY_TEST(pEnum->Next(1,&pe,&fetched ),S_OK);
   TRY_TEST(pe.IsEqualObject(element),true);

   point.Release();
   vc.Release();
   vc.CoCreateInstance(CLSID_VertCurve);

   // Test Events
   CComObject<CTestProfile>* pTestProfile;
   CComObject<CTestProfile>::CreateInstance(&pTestProfile);
   pTestProfile->AddRef();

   DWORD dwCookie;
   CComPtr<IUnknown> punk(pTestProfile);
   TRY_TEST(AtlAdvise(profile,punk,IID_IProfileEvents,&dwCookie),S_OK);

   pTestProfile->InitEventTest();
   profile->Clear();
   TRY_TEST(pTestProfile->PassedEventTest(), true );

   pTestProfile->InitEventTest();
   profile->AddEx(vc);
   TRY_TEST(pTestProfile->PassedEventTest(), true );

   pTestProfile->InitEventTest();
   point.CoCreateInstance(CLSID_ProfilePoint);
   vc->putref_PBG(point);
   TRY_TEST(pTestProfile->PassedEventTest(), true );

   pTestProfile->InitEventTest();
   profile->AddEx(point);
   TRY_TEST(pTestProfile->PassedEventTest(), true );

   pTestProfile->InitEventTest();
   point->put_Elevation(50);
   TRY_TEST(pTestProfile->PassedEventTest(), true );


   TRY_TEST(AtlUnadvise(profile,IID_IProfileEvents,dwCookie),S_OK);
   pTestProfile->Release();

   // Test ISupportErrorInfo
   CComQIPtr<ISupportErrorInfo> eInfo(profile);
   TRY_TEST( eInfo != NULL, true );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IProfile ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

   // Test IObjectSafety
   TRY_TEST( TestIObjectSafety(CLSID_Profile,IID_IProfile,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
   TRY_TEST( TestIObjectSafety(CLSID_Profile,IID_IStructuredStorage2,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
}

void CTestProfile::Test2()
{
   CComPtr<IProfile> profile;
   TRY_TEST(profile.CoCreateInstance(CLSID_Profile),S_OK);

   //
   // Test Elevation and Grade
   //
   //
   // Profile Point: Station 6+00 Elev 80.0
   // Vert Curve: BVC  7+00 Elev  85.0
   //             PVI 10+00 Elev 100.0
   //             EVC 13+00 Elev  91.0
   // Profile Point: Station 14+00 Elev 88.0
   CComPtr<IProfilePoint> point;
   point.CoCreateInstance(CLSID_ProfilePoint);
   point->put_Station(CComVariant(600));
   point->put_Elevation(80);
   profile->AddEx(point);

   CComPtr<IVertCurve> vc;
   vc.CoCreateInstance(CLSID_VertCurve);
   point.Release();
   vc->get_PBG(&point);
   point->put_Station(CComVariant(700));
   point->put_Elevation(85);
   point.Release();
   vc->get_PVI(&point);
   point->put_Station(CComVariant(1000));
   point->put_Elevation(100);
   point.Release();
   vc->get_PFG(&point);
   point->put_Station(CComVariant(1300));
   point->put_Elevation(91);
   vc->put_L1(300);
   vc->put_L2(300);
   profile->AddEx(vc);
   
   point.Release();
   point.CoCreateInstance(CLSID_ProfilePoint);
   point->put_Station(CComVariant(1400));
   point->put_Elevation(88);
   profile->AddEx(point);

   CComPtr<ICrossSectionCollection> sections;
   profile->get_CrossSections(&sections);
   sections->Add(CComVariant(700), -5,-0.02,-0.02,NULL);
   sections->Add(CComVariant(1000),-5, 0.06,-0.06,NULL);
   sections->Add(CComVariant(1300),-5,-0.04,-0.08,NULL);

   Float64 Grades[] = { 5.0000, 5.0000, 4.2000, 2.0667, -0.0667, -2.2000, -3.0000, -3.0000 };
   TestGrade(profile,Grades);

   Float64 CrownSlopes1[][2] = { { -0.0200, -0.0200}, { -0.0200, -0.0200}, { -0.0040, -0.0280}, { 0.0387, -0.0493}, { 0.0333,-0.0653}, {-0.0200, -0.0760}, {-0.0400, -0.0800}, {-0.0400, -0.0800} };
   TestCrownSlopes(profile,CrownSlopes1);

   Float64 ElevA[] = { 71.900, 79.900, 87.860, 93.407, 95.033, 92.740, 88.000, 83.200 };
   Float64 ElevB[] = { 72.100, 80.100, 87.900, 93.020, 94.700, 92.940, 88.400, 83.600 };
   Float64 ElevC[] = { 72.040, 80.040, 87.816, 92.872, 94.504, 92.712, 88.160, 83.360 };
   Float64 ElevD[] = { 72.000, 80.000, 87.760, 92.773, 94.373, 92.560, 88.000, 83.200 };
   Float64 ElevE[] = { 71.900, 79.900, 87.620, 92.527, 94.047, 92.180, 87.600, 82.800 };
   TestElevation(profile,-15,ElevA);
   TestElevation(profile, -5,ElevB);
   TestElevation(profile, -2,ElevC);
   TestElevation(profile,  0,ElevD);
   TestElevation(profile,  5,ElevE);

   // shift the crown point offset to +5
   CComPtr<ICrossSection> cs;
   CollectionIndexType count;
   sections->get_Count(&count);
   for ( CollectionIndexType i = 0; i < count; i++ )
   {
      cs.Release();
      sections->get_Item(i,&cs);
      cs->put_CrownPointOffset(5);
   }

   Float64 ElevF[] = { 71.900, 79.900, 87.740, 92.967, 94.540, 92.460, 87.800, 83.000 };
   Float64 ElevG[] = { 72.000, 80.000, 87.760, 92.773, 94.373, 92.560, 88.000, 83.200 };
   Float64 ElevH[] = { 72.040, 80.040, 87.768, 92.696, 94.307, 92.600, 88.080, 83.280 };
   Float64 ElevI[] = { 72.100, 80.100, 87.780, 92.580, 94.207, 92.660, 88.200, 83.400 };
   Float64 ElevJ[] = { 71.900, 79.900, 87.500, 92.087, 93.553, 91.900, 87.400, 82.600 };
   TestElevation(profile, -5,ElevF);
   TestElevation(profile,  0,ElevG);
   TestElevation(profile,  2,ElevH);
   TestElevation(profile,  5,ElevI);
   TestElevation(profile, 15,ElevJ);

   // shift the crown point offset back to -5 and reverse all of the crown slopes
   for ( CollectionIndexType i = 0; i < count; i++ )
   {
      cs.Release();
      sections->get_Item(i,&cs);
      cs->put_CrownPointOffset(-5);

      Float64 val;
      cs->get_LeftCrownSlope(&val);
      val *= -1;
      cs->put_LeftCrownSlope(val);
   
      cs->get_RightCrownSlope(&val);
      val *= -1;
      cs->put_RightCrownSlope(val);
   }

   Float64 CrownSlopes2[][2] = { {  0.0200,  0.0200}, {  0.0200,  0.0200}, {  0.0040,  0.0280}, {-0.0387,  0.0493}, {-0.0333, 0.0653}, { 0.0200,  0.0760}, { 0.0400,  0.0800}, { 0.0400,  0.0800} };
   TestCrownSlopes(profile,CrownSlopes2);

   Float64 ElevK[] = { 72.100, 80.100, 87.660, 92.140, 93.713, 92.380, 88.000, 83.200 };
   Float64 ElevL[] = { 71.900, 79.900, 87.620, 92.527, 94.047, 92.180, 87.600, 82.800 };
   Float64 ElevM[] = { 71.960, 79.960, 87.704, 92.675, 94.243, 92.408, 87.840, 83.040 };
   Float64 ElevN[] = { 72.000, 80.000, 87.760, 92.773, 94.373, 92.560, 88.000, 83.200 };
   Float64 ElevO[] = { 72.100, 80.100, 87.900, 93.020, 94.700, 92.940, 88.400, 83.600 };
   TestElevation(profile,-15,ElevK);
   TestElevation(profile, -5,ElevL);
   TestElevation(profile, -2,ElevM);
   TestElevation(profile,  0,ElevN);
   TestElevation(profile,  5,ElevO);

   // shift the crown point offset to +5, keep the slopes the same
   sections->get_Count(&count);
   for ( CollectionIndexType i = 0; i < count; i++ )
   {
      cs.Release();
      sections->get_Item(i,&cs);
      cs->put_CrownPointOffset(5);
   }
   
   Float64 ElevP[] = { 72.100, 80.100, 87.780, 92.580, 94.207, 92.660, 88.200, 83.400 };
   Float64 ElevQ[] = { 72.000, 80.000, 87.760, 92.773, 94.373, 92.560, 88.000, 83.200 };
   Float64 ElevR[] = { 71.960, 79.960, 87.752, 92.851, 94.440, 92.520, 87.920, 83.120 };
   Float64 ElevS[] = { 71.900, 79.900, 87.740, 92.967, 94.540, 92.460, 87.800, 83.000 };
   Float64 ElevT[] = { 72.100, 80.100, 88.020, 93.460, 95.193, 93.220, 88.600, 83.800 };
   TestElevation(profile, -5,ElevP);
   TestElevation(profile,  0,ElevQ);
   TestElevation(profile,  2,ElevR);
   TestElevation(profile,  5,ElevS);
   TestElevation(profile, 15,ElevT);
}

void CTestProfile::Test3()
{
   CComPtr<IProfile> profile;
   TRY_TEST(profile.CoCreateInstance(CLSID_Profile),S_OK);

   //
   // Test Elevation and Grade
   //
   //
   // Vert Curve: BVC  7+00 Elev  85.0
   //             PVI 10+00 Elev 100.0
   //             EVC 13+00 Elev  91.0
   //
   // Profile Point: Station 14+00 Elev 88.0

   CComPtr<IProfilePoint> point;
   CComPtr<IVertCurve> vc;
   vc.CoCreateInstance(CLSID_VertCurve);
   vc->get_PBG(&point);
   point->put_Station(CComVariant(700));
   point->put_Elevation(85);
   point.Release();
   vc->get_PVI(&point);
   point->put_Station(CComVariant(1000));
   point->put_Elevation(100);
   point.Release();
   vc->get_PFG(&point);
   point->put_Station(CComVariant(1300));
   point->put_Elevation(91);
   vc->put_L1(300);
   vc->put_L2(300);
   profile->AddEx(vc);

   point.Release();
   point.CoCreateInstance(CLSID_ProfilePoint);
   point->put_Station(CComVariant(1400));
   point->put_Elevation(88);
   profile->AddEx(point);

   CComPtr<ICrossSectionCollection> sections;
   profile->get_CrossSections(&sections);
   sections->Add(CComVariant(700), -5,-0.02,-0.02,NULL);
   sections->Add(CComVariant(1000),-5, 0.06,-0.06,NULL);
   sections->Add(CComVariant(1300),-5,-0.04,-0.08,NULL);

   Float64 Grades[] = { 5.0000, 5.0000, 4.2000, 2.0667, -0.0667, -2.2000, -3.0000, -3.0000 };
   TestGrade(profile,Grades);

   Float64 CrownSlopes1[][2] = { { -0.0200, -0.0200}, { -0.0200, -0.0200}, { -0.0040, -0.0280}, { 0.0387, -0.0493}, { 0.0333,-0.0653}, {-0.0200, -0.0760}, {-0.0400, -0.0800}, {-0.0400, -0.0800} };
   TestCrownSlopes(profile,CrownSlopes1);

   Float64 ElevA[] = { 71.900, 79.900, 87.860, 93.407, 95.033, 92.740, 88.000, 83.200 };
   Float64 ElevB[] = { 72.100, 80.100, 87.900, 93.020, 94.700, 92.940, 88.400, 83.600 };
   Float64 ElevC[] = { 72.040, 80.040, 87.816, 92.872, 94.504, 92.712, 88.160, 83.360 };
   Float64 ElevD[] = { 72.000, 80.000, 87.760, 92.773, 94.373, 92.560, 88.000, 83.200 };
   Float64 ElevE[] = { 71.900, 79.900, 87.620, 92.527, 94.047, 92.180, 87.600, 82.800 };
   TestElevation(profile,-15,ElevA);
   TestElevation(profile, -5,ElevB);
   TestElevation(profile, -2,ElevC);
   TestElevation(profile,  0,ElevD);
   TestElevation(profile,  5,ElevE);

   // shift the crown point offset to +5
   CComPtr<ICrossSection> cs;
   CollectionIndexType count;
   sections->get_Count(&count);
   for ( CollectionIndexType i = 0; i < count; i++ )
   {
      cs.Release();
      sections->get_Item(i,&cs);
      cs->put_CrownPointOffset(5);
   }

   Float64 ElevF[] = { 71.900, 79.900, 87.740, 92.967, 94.540, 92.460, 87.800, 83.000 };
   Float64 ElevG[] = { 72.000, 80.000, 87.760, 92.773, 94.373, 92.560, 88.000, 83.200 };
   Float64 ElevH[] = { 72.040, 80.040, 87.768, 92.696, 94.307, 92.600, 88.080, 83.280 };
   Float64 ElevI[] = { 72.100, 80.100, 87.780, 92.580, 94.207, 92.660, 88.200, 83.400 };
   Float64 ElevJ[] = { 71.900, 79.900, 87.500, 92.087, 93.553, 91.900, 87.400, 82.600 };
   TestElevation(profile, -5,ElevF);
   TestElevation(profile,  0,ElevG);
   TestElevation(profile,  2,ElevH);
   TestElevation(profile,  5,ElevI);
   TestElevation(profile, 15,ElevJ);

   // shift the crown point offset back to -5 and reverse all of the crown slopes
   for ( CollectionIndexType i = 0; i < count; i++ )
   {
      cs.Release();
      sections->get_Item(i,&cs);
      cs->put_CrownPointOffset(-5);

      Float64 val;
      cs->get_LeftCrownSlope(&val);
      val *= -1;
      cs->put_LeftCrownSlope(val);
   
      cs->get_RightCrownSlope(&val);
      val *= -1;
      cs->put_RightCrownSlope(val);
   }

   Float64 CrownSlopes2[][2] = { {  0.0200,  0.0200}, {  0.0200,  0.0200}, {  0.0040,  0.0280}, {-0.0387,  0.0493}, {-0.0333, 0.0653}, { 0.0200,  0.0760}, { 0.0400,  0.0800}, { 0.0400,  0.0800} };
   TestCrownSlopes(profile,CrownSlopes2);

   Float64 ElevK[] = { 72.100, 80.100, 87.660, 92.140, 93.713, 92.380, 88.000, 83.200 };
   Float64 ElevL[] = { 71.900, 79.900, 87.620, 92.527, 94.047, 92.180, 87.600, 82.800 };
   Float64 ElevM[] = { 71.960, 79.960, 87.704, 92.675, 94.243, 92.408, 87.840, 83.040 };
   Float64 ElevN[] = { 72.000, 80.000, 87.760, 92.773, 94.373, 92.560, 88.000, 83.200 };
   Float64 ElevO[] = { 72.100, 80.100, 87.900, 93.020, 94.700, 92.940, 88.400, 83.600 };
   TestElevation(profile,-15,ElevK);
   TestElevation(profile, -5,ElevL);
   TestElevation(profile, -2,ElevM);
   TestElevation(profile,  0,ElevN);
   TestElevation(profile,  5,ElevO);

   // shift the crown point offset to +5, keep the slopes the same
   sections->get_Count(&count);
   for ( CollectionIndexType i = 0; i < count; i++ )
   {
      cs.Release();
      sections->get_Item(i,&cs);
      cs->put_CrownPointOffset(5);
   }
   
   Float64 ElevP[] = { 72.100, 80.100, 87.780, 92.580, 94.207, 92.660, 88.200, 83.400 };
   Float64 ElevQ[] = { 72.000, 80.000, 87.760, 92.773, 94.373, 92.560, 88.000, 83.200 };
   Float64 ElevR[] = { 71.960, 79.960, 87.752, 92.851, 94.440, 92.520, 87.920, 83.120 };
   Float64 ElevS[] = { 71.900, 79.900, 87.740, 92.967, 94.540, 92.460, 87.800, 83.000 };
   Float64 ElevT[] = { 72.100, 80.100, 88.020, 93.460, 95.193, 93.220, 88.600, 83.800 };
   TestElevation(profile, -5,ElevP);
   TestElevation(profile,  0,ElevQ);
   TestElevation(profile,  2,ElevR);
   TestElevation(profile,  5,ElevS);
   TestElevation(profile, 15,ElevT);
}

void CTestProfile::Test4()
{
   CComPtr<IProfile> profile;
   TRY_TEST(profile.CoCreateInstance(CLSID_Profile),S_OK);

   //
   // Test Elevation and Grade
   //
   //
   // Vert Curve: BVC  7+00 Elev  85.0
   //             PVI 10+00 Elev 100.0
   //             EVC 13+00 Elev  91.0
   //
   // Vert Curve: BVC 13+90 Elev  85.0
   //             PVI 14+50 Elev 100.0
   //             EVC 14+90 Elev  91.0

   CComPtr<IProfilePoint> point;
   CComPtr<IVertCurve> vc;
   vc.CoCreateInstance(CLSID_VertCurve);
   vc->get_PBG(&point);
   point->put_Station(CComVariant(700));
   point->put_Elevation(85);
   point.Release();
   vc->get_PVI(&point);
   point->put_Station(CComVariant(1000));
   point->put_Elevation(100);
   point.Release();
   vc->get_PFG(&point);
   point->put_Station(CComVariant(1300));
   point->put_Elevation(91);
   vc->put_L1(300);
   vc->put_L2(300);
   profile->AddEx(vc);

   vc.Release();
   vc.CoCreateInstance(CLSID_VertCurve);
   point.Release();
   vc->get_PBG(&point);
   point->put_Station(CComVariant(1390));
   point->put_Elevation(85);
   point.Release();
   vc->get_PVI(&point);
   point->put_Station(CComVariant(1450));
   point->put_Elevation(100);
   point.Release();
   vc->get_PFG(&point);
   point->put_Station(CComVariant(1490));
   point->put_Elevation(91);
   vc->put_L1(60);
   vc->put_L2(40);
   profile->AddEx(vc);

   CComPtr<ICrossSectionCollection> sections;
   profile->get_CrossSections(&sections);
   sections->Add(CComVariant(700), -5,-0.02,-0.02,NULL);
   sections->Add(CComVariant(1000),-5, 0.06,-0.06,NULL);
   sections->Add(CComVariant(1300),-5,-0.04,-0.08,NULL);

   Float64 Grades[] = { 5.0000, 5.0000, 4.2000, 2.0667, -0.0667, -2.2000, 21.8333, -22.5000 };
   TestGrade(profile,Grades);

   Float64 CrownSlopes1[][2] = { { -0.0200, -0.0200}, { -0.0200, -0.0200}, { -0.0040, -0.0280}, { 0.0387, -0.0493}, { 0.0333,-0.0653}, {-0.0200, -0.0760}, {-0.0400, -0.0800}, {-0.0400, -0.0800} };
   TestCrownSlopes(profile,CrownSlopes1);

   Float64 ElevA[] = { 71.900, 79.900, 87.860, 93.407, 95.033, 92.740, 87.3417, 75.250 };
   Float64 ElevB[] = { 72.100, 80.100, 87.900, 93.020, 94.700, 92.940, 87.7417, 75.650 };
   Float64 ElevC[] = { 72.040, 80.040, 87.816, 92.872, 94.504, 92.712, 87.5017, 75.410 };
   Float64 ElevD[] = { 72.000, 80.000, 87.760, 92.773, 94.373, 92.560, 87.3417, 75.250 };
   Float64 ElevE[] = { 71.900, 79.900, 87.620, 92.527, 94.047, 92.180, 86.9417, 74.850 };
   TestElevation(profile,-15,ElevA);
   TestElevation(profile, -5,ElevB);
   TestElevation(profile, -2,ElevC);
   TestElevation(profile,  0,ElevD);
   TestElevation(profile,  5,ElevE);

   // shift the crown point offset to +5
   CComPtr<ICrossSection> cs;
   CollectionIndexType count;
   sections->get_Count(&count);
   for ( CollectionIndexType i = 0; i < count; i++ )
   {
      cs.Release();
      sections->get_Item(i,&cs);
      cs->put_CrownPointOffset(5);
   }

   Float64 ElevF[] = { 71.900, 79.900, 87.740, 92.967, 94.540, 92.460, 87.1417, 75.050 };
   Float64 ElevG[] = { 72.000, 80.000, 87.760, 92.773, 94.373, 92.560, 87.3417, 75.250 };
   Float64 ElevH[] = { 72.040, 80.040, 87.768, 92.696, 94.307, 92.600, 87.4217, 75.330 };
   Float64 ElevI[] = { 72.100, 80.100, 87.780, 92.580, 94.207, 92.660, 87.5417, 75.450 };
   Float64 ElevJ[] = { 71.900, 79.900, 87.500, 92.087, 93.553, 91.900, 86.7417, 74.650 };
   TestElevation(profile, -5,ElevF);
   TestElevation(profile,  0,ElevG);
   TestElevation(profile,  2,ElevH);
   TestElevation(profile,  5,ElevI);
   TestElevation(profile, 15,ElevJ);

   // shift the crown point offset back to -5 and reverse all of the crown slopes
   for ( CollectionIndexType i = 0; i < count; i++ )
   {
      cs.Release();
      sections->get_Item(i,&cs);
      cs->put_CrownPointOffset(-5);

      Float64 val;
      cs->get_LeftCrownSlope(&val);
      val *= -1;
      cs->put_LeftCrownSlope(val);
   
      cs->get_RightCrownSlope(&val);
      val *= -1;
      cs->put_RightCrownSlope(val);
   }

   Float64 CrownSlopes2[][2] = { {  0.0200,  0.0200}, {  0.0200,  0.0200}, {  0.0040,  0.0280}, {-0.0387,  0.0493}, {-0.0333, 0.0653}, { 0.0200,  0.0760}, { 0.0400,  0.0800}, { 0.0400,  0.0800} };
   TestCrownSlopes(profile,CrownSlopes2);

   Float64 ElevK[] = { 72.100, 80.100, 87.660, 92.140, 93.713, 92.380, 87.3417, 75.250 };
   Float64 ElevL[] = { 71.900, 79.900, 87.620, 92.527, 94.047, 92.180, 86.9417, 74.850 };
   Float64 ElevM[] = { 71.960, 79.960, 87.704, 92.675, 94.243, 92.408, 87.1817, 75.090 };
   Float64 ElevN[] = { 72.000, 80.000, 87.760, 92.773, 94.373, 92.560, 87.3417, 75.250 };
   Float64 ElevO[] = { 72.100, 80.100, 87.900, 93.020, 94.700, 92.940, 87.7417, 75.650 };
   TestElevation(profile,-15,ElevK);
   TestElevation(profile, -5,ElevL);
   TestElevation(profile, -2,ElevM);
   TestElevation(profile,  0,ElevN);
   TestElevation(profile,  5,ElevO);

   // shift the crown point offset to +5, keep the slopes the same
   sections->get_Count(&count);
   for ( CollectionIndexType i = 0; i < count; i++ )
   {
      cs.Release();
      sections->get_Item(i,&cs);
      cs->put_CrownPointOffset(5);
   }
   
   Float64 ElevP[] = { 72.100, 80.100, 87.780, 92.580, 94.207, 92.660, 87.5417, 75.450 };
   Float64 ElevQ[] = { 72.000, 80.000, 87.760, 92.773, 94.373, 92.560, 87.3417, 75.250 };
   Float64 ElevR[] = { 71.960, 79.960, 87.752, 92.851, 94.440, 92.520, 87.2617, 75.170 };
   Float64 ElevS[] = { 71.900, 79.900, 87.740, 92.967, 94.540, 92.460, 87.1417, 75.050 };
   Float64 ElevT[] = { 72.100, 80.100, 88.020, 93.460, 95.193, 93.220, 87.9417, 75.850 };
   TestElevation(profile, -5,ElevP);
   TestElevation(profile,  0,ElevQ);
   TestElevation(profile,  2,ElevR);
   TestElevation(profile,  5,ElevS);
   TestElevation(profile, 15,ElevT);
}

void CTestProfile::Test5()
{
   CComPtr<IProfile> profile;
   TRY_TEST(profile.CoCreateInstance(CLSID_Profile),S_OK);

   //
   // Test Elevation and Grade
   //
   //
   // Profile Point: Station 6+10 Elev 80.5
   // Profile Point: Station 6+50 Elev 82.5
   // Vert Curve: BVC  7+00 Elev  85.0
   //             PVI 10+00 Elev 100.0
   //             EVC 13+00 Elev  91.0
   // Profile Point: Station 14+00 Elev 88.0
   CComPtr<IProfilePoint> point;
   point.CoCreateInstance(CLSID_ProfilePoint);
   point->put_Station(CComVariant(610));
   point->put_Elevation(80.5);
   profile->AddEx(point);

   point.Release();
   point.CoCreateInstance(CLSID_ProfilePoint);
   point->put_Station(CComVariant(650));
   point->put_Elevation(82.5);
   profile->AddEx(point);

   CComPtr<IVertCurve> vc;
   vc.CoCreateInstance(CLSID_VertCurve);
   point.Release();
   vc->get_PBG(&point);
   point->put_Station(CComVariant(700));
   point->put_Elevation(85);
   point.Release();
   vc->get_PVI(&point);
   point->put_Station(CComVariant(1000));
   point->put_Elevation(100);
   point.Release();
   vc->get_PFG(&point);
   point->put_Station(CComVariant(1300));
   point->put_Elevation(91);
   vc->put_L1(300);
   vc->put_L2(300);
   profile->AddEx(vc);
   
   point.Release();
   point.CoCreateInstance(CLSID_ProfilePoint);
   point->put_Station(CComVariant(1400));
   point->put_Elevation(88);
   profile->AddEx(point);

   CComPtr<ICrossSectionCollection> sections;
   profile->get_CrossSections(&sections);
   sections->Add(CComVariant(700), -5,-0.02,-0.02,NULL);
   sections->Add(CComVariant(1000),-5, 0.06,-0.06,NULL);
   sections->Add(CComVariant(1300),-5,-0.04,-0.08,NULL);

   Float64 Grades[] = { 5.0000, 5.0000, 4.2000, 2.0667, -0.0667, -2.2000, -3.0000, -3.0000 };
   TestGrade(profile,Grades);

   Float64 CrownSlopes1[][2] = { { -0.0200, -0.0200}, { -0.0200, -0.0200}, { -0.0040, -0.0280}, { 0.0387, -0.0493}, { 0.0333,-0.0653}, {-0.0200, -0.0760}, {-0.0400, -0.0800}, {-0.0400, -0.0800} };
   TestCrownSlopes(profile,CrownSlopes1);

   Float64 ElevA[] = { 71.900, 79.900, 87.860, 93.407, 95.033, 92.740, 88.000, 83.200 };
   Float64 ElevB[] = { 72.100, 80.100, 87.900, 93.020, 94.700, 92.940, 88.400, 83.600 };
   Float64 ElevC[] = { 72.040, 80.040, 87.816, 92.872, 94.504, 92.712, 88.160, 83.360 };
   Float64 ElevD[] = { 72.000, 80.000, 87.760, 92.773, 94.373, 92.560, 88.000, 83.200 };
   Float64 ElevE[] = { 71.900, 79.900, 87.620, 92.527, 94.047, 92.180, 87.600, 82.800 };
   TestElevation(profile,-15,ElevA);
   TestElevation(profile, -5,ElevB);
   TestElevation(profile, -2,ElevC);
   TestElevation(profile,  0,ElevD);
   TestElevation(profile,  5,ElevE);

   // shift the crown point offset to +5
   CComPtr<ICrossSection> cs;
   CollectionIndexType count;
   sections->get_Count(&count);
   for ( CollectionIndexType i = 0; i < count; i++ )
   {
      cs.Release();
      sections->get_Item(i,&cs);
      cs->put_CrownPointOffset(5);
   }

   Float64 ElevF[] = { 71.900, 79.900, 87.740, 92.967, 94.540, 92.460, 87.800, 83.000 };
   Float64 ElevG[] = { 72.000, 80.000, 87.760, 92.773, 94.373, 92.560, 88.000, 83.200 };
   Float64 ElevH[] = { 72.040, 80.040, 87.768, 92.696, 94.307, 92.600, 88.080, 83.280 };
   Float64 ElevI[] = { 72.100, 80.100, 87.780, 92.580, 94.207, 92.660, 88.200, 83.400 };
   Float64 ElevJ[] = { 71.900, 79.900, 87.500, 92.087, 93.553, 91.900, 87.400, 82.600 };
   TestElevation(profile, -5,ElevF);
   TestElevation(profile,  0,ElevG);
   TestElevation(profile,  2,ElevH);
   TestElevation(profile,  5,ElevI);
   TestElevation(profile, 15,ElevJ);

   // shift the crown point offset back to -5 and reverse all of the crown slopes
   for ( CollectionIndexType i = 0; i < count; i++ )
   {
      cs.Release();
      sections->get_Item(i,&cs);
      cs->put_CrownPointOffset(-5);

      Float64 val;
      cs->get_LeftCrownSlope(&val);
      val *= -1;
      cs->put_LeftCrownSlope(val);
   
      cs->get_RightCrownSlope(&val);
      val *= -1;
      cs->put_RightCrownSlope(val);
   }

   Float64 CrownSlopes2[][2] = { {  0.0200,  0.0200}, {  0.0200,  0.0200}, {  0.0040,  0.0280}, {-0.0387,  0.0493}, {-0.0333, 0.0653}, { 0.0200,  0.0760}, { 0.0400,  0.0800}, { 0.0400,  0.0800} };
   TestCrownSlopes(profile,CrownSlopes2);

   Float64 ElevK[] = { 72.100, 80.100, 87.660, 92.140, 93.713, 92.380, 88.000, 83.200 };
   Float64 ElevL[] = { 71.900, 79.900, 87.620, 92.527, 94.047, 92.180, 87.600, 82.800 };
   Float64 ElevM[] = { 71.960, 79.960, 87.704, 92.675, 94.243, 92.408, 87.840, 83.040 };
   Float64 ElevN[] = { 72.000, 80.000, 87.760, 92.773, 94.373, 92.560, 88.000, 83.200 };
   Float64 ElevO[] = { 72.100, 80.100, 87.900, 93.020, 94.700, 92.940, 88.400, 83.600 };
   TestElevation(profile,-15,ElevK);
   TestElevation(profile, -5,ElevL);
   TestElevation(profile, -2,ElevM);
   TestElevation(profile,  0,ElevN);
   TestElevation(profile,  5,ElevO);

   // shift the crown point offset to +5, keep the slopes the same
   sections->get_Count(&count);
   for ( CollectionIndexType i = 0; i < count; i++ )
   {
      cs.Release();
      sections->get_Item(i,&cs);
      cs->put_CrownPointOffset(5);
   }
   
   Float64 ElevP[] = { 72.100, 80.100, 87.780, 92.580, 94.207, 92.660, 88.200, 83.400 };
   Float64 ElevQ[] = { 72.000, 80.000, 87.760, 92.773, 94.373, 92.560, 88.000, 83.200 };
   Float64 ElevR[] = { 71.960, 79.960, 87.752, 92.851, 94.440, 92.520, 87.920, 83.120 };
   Float64 ElevS[] = { 71.900, 79.900, 87.740, 92.967, 94.540, 92.460, 87.800, 83.000 };
   Float64 ElevT[] = { 72.100, 80.100, 88.020, 93.460, 95.193, 93.220, 88.600, 83.800 };
   TestElevation(profile, -5,ElevP);
   TestElevation(profile,  0,ElevQ);
   TestElevation(profile,  2,ElevR);
   TestElevation(profile,  5,ElevS);
   TestElevation(profile, 15,ElevT);
}

void CTestProfile::Test6()
{
   CComPtr<IProfile> profile;
   TRY_TEST(profile.CoCreateInstance(CLSID_Profile),S_OK);

   //
   // Test Elevation and Grade
   //
   //
   // Profile Point: Station 6+10 Elev 80.5
   // Profile Point: Station 6+50 Elev 82.5
   // Vert Curve: BVC  7+00 Elev  85.0
   //             PVI 10+00 Elev 100.0
   //             EVC 13+00 Elev  91.0
   // Profile Point: Station 14+00 Elev 88.0
   // Profile Point: Station 14+50 Elev 86.5
   CComPtr<IProfilePoint> point;
   point.CoCreateInstance(CLSID_ProfilePoint);
   point->put_Station(CComVariant(610));
   point->put_Elevation(80.5);
   profile->AddEx(point);

   point.Release();
   point.CoCreateInstance(CLSID_ProfilePoint);
   point->put_Station(CComVariant(650));
   point->put_Elevation(82.5);
   profile->AddEx(point);

   CComPtr<IVertCurve> vc;
   vc.CoCreateInstance(CLSID_VertCurve);
   point.Release();
   vc->get_PBG(&point);
   point->put_Station(CComVariant(700));
   point->put_Elevation(85);
   point.Release();
   vc->get_PVI(&point);
   point->put_Station(CComVariant(1000));
   point->put_Elevation(100);
   point.Release();
   vc->get_PFG(&point);
   point->put_Station(CComVariant(1300));
   point->put_Elevation(91);
   vc->put_L1(300);
   vc->put_L2(300);
   profile->AddEx(vc);
   
   point.Release();
   point.CoCreateInstance(CLSID_ProfilePoint);
   point->put_Station(CComVariant(1400));
   point->put_Elevation(88);
   profile->AddEx(point);
   
   point.Release();
   point.CoCreateInstance(CLSID_ProfilePoint);
   point->put_Station(CComVariant(1450));
   point->put_Elevation(86.5);
   profile->AddEx(point);

   CComPtr<ICrossSectionCollection> sections;
   profile->get_CrossSections(&sections);
   sections->Add(CComVariant(700), -5,-0.02,-0.02,NULL);
   sections->Add(CComVariant(1000),-5, 0.06,-0.06,NULL);
   sections->Add(CComVariant(1300),-5,-0.04,-0.08,NULL);

   Float64 Grades[] = { 5.0000, 5.0000, 4.2000, 2.0667, -0.0667, -2.2000, -3.0000, -3.0000 };
   TestGrade(profile,Grades);

   Float64 CrownSlopes1[][2] = { { -0.0200, -0.0200}, { -0.0200, -0.0200}, { -0.0040, -0.0280}, { 0.0387, -0.0493}, { 0.0333,-0.0653}, {-0.0200, -0.0760}, {-0.0400, -0.0800}, {-0.0400, -0.0800} };
   TestCrownSlopes(profile,CrownSlopes1);

   Float64 ElevA[] = { 71.900, 79.900, 87.860, 93.407, 95.033, 92.740, 88.000, 83.200 };
   Float64 ElevB[] = { 72.100, 80.100, 87.900, 93.020, 94.700, 92.940, 88.400, 83.600 };
   Float64 ElevC[] = { 72.040, 80.040, 87.816, 92.872, 94.504, 92.712, 88.160, 83.360 };
   Float64 ElevD[] = { 72.000, 80.000, 87.760, 92.773, 94.373, 92.560, 88.000, 83.200 };
   Float64 ElevE[] = { 71.900, 79.900, 87.620, 92.527, 94.047, 92.180, 87.600, 82.800 };
   TestElevation(profile,-15,ElevA);
   TestElevation(profile, -5,ElevB);
   TestElevation(profile, -2,ElevC);
   TestElevation(profile,  0,ElevD);
   TestElevation(profile,  5,ElevE);

   // shift the crown point offset to +5
   CComPtr<ICrossSection> cs;
   CollectionIndexType count;
   sections->get_Count(&count);
   for ( CollectionIndexType i = 0; i < count; i++ )
   {
      cs.Release();
      sections->get_Item(i,&cs);
      cs->put_CrownPointOffset(5);
   }

   Float64 ElevF[] = { 71.900, 79.900, 87.740, 92.967, 94.540, 92.460, 87.800, 83.000 };
   Float64 ElevG[] = { 72.000, 80.000, 87.760, 92.773, 94.373, 92.560, 88.000, 83.200 };
   Float64 ElevH[] = { 72.040, 80.040, 87.768, 92.696, 94.307, 92.600, 88.080, 83.280 };
   Float64 ElevI[] = { 72.100, 80.100, 87.780, 92.580, 94.207, 92.660, 88.200, 83.400 };
   Float64 ElevJ[] = { 71.900, 79.900, 87.500, 92.087, 93.553, 91.900, 87.400, 82.600 };
   TestElevation(profile, -5,ElevF);
   TestElevation(profile,  0,ElevG);
   TestElevation(profile,  2,ElevH);
   TestElevation(profile,  5,ElevI);
   TestElevation(profile, 15,ElevJ);

   // shift the crown point offset back to -5 and reverse all of the crown slopes
   for ( CollectionIndexType i = 0; i < count; i++ )
   {
      cs.Release();
      sections->get_Item(i,&cs);
      cs->put_CrownPointOffset(-5);

      Float64 val;
      cs->get_LeftCrownSlope(&val);
      val *= -1;
      cs->put_LeftCrownSlope(val);
   
      cs->get_RightCrownSlope(&val);
      val *= -1;
      cs->put_RightCrownSlope(val);
   }

   Float64 CrownSlopes2[][2] = { {  0.0200,  0.0200}, {  0.0200,  0.0200}, {  0.0040,  0.0280}, {-0.0387,  0.0493}, {-0.0333, 0.0653}, { 0.0200,  0.0760}, { 0.0400,  0.0800}, { 0.0400,  0.0800} };
   TestCrownSlopes(profile,CrownSlopes2);

   Float64 ElevK[] = { 72.100, 80.100, 87.660, 92.140, 93.713, 92.380, 88.000, 83.200 };
   Float64 ElevL[] = { 71.900, 79.900, 87.620, 92.527, 94.047, 92.180, 87.600, 82.800 };
   Float64 ElevM[] = { 71.960, 79.960, 87.704, 92.675, 94.243, 92.408, 87.840, 83.040 };
   Float64 ElevN[] = { 72.000, 80.000, 87.760, 92.773, 94.373, 92.560, 88.000, 83.200 };
   Float64 ElevO[] = { 72.100, 80.100, 87.900, 93.020, 94.700, 92.940, 88.400, 83.600 };
   TestElevation(profile,-15,ElevK);
   TestElevation(profile, -5,ElevL);
   TestElevation(profile, -2,ElevM);
   TestElevation(profile,  0,ElevN);
   TestElevation(profile,  5,ElevO);

   // shift the crown point offset to +5, keep the slopes the same
   sections->get_Count(&count);
   for ( CollectionIndexType i = 0; i < count; i++ )
   {
      cs.Release();
      sections->get_Item(i,&cs);
      cs->put_CrownPointOffset(5);
   }
   
   Float64 ElevP[] = { 72.100, 80.100, 87.780, 92.580, 94.207, 92.660, 88.200, 83.400 };
   Float64 ElevQ[] = { 72.000, 80.000, 87.760, 92.773, 94.373, 92.560, 88.000, 83.200 };
   Float64 ElevR[] = { 71.960, 79.960, 87.752, 92.851, 94.440, 92.520, 87.920, 83.120 };
   Float64 ElevS[] = { 71.900, 79.900, 87.740, 92.967, 94.540, 92.460, 87.800, 83.000 };
   Float64 ElevT[] = { 72.100, 80.100, 88.020, 93.460, 95.193, 93.220, 88.600, 83.800 };
   TestElevation(profile, -5,ElevP);
   TestElevation(profile,  0,ElevQ);
   TestElevation(profile,  2,ElevR);
   TestElevation(profile,  5,ElevS);
   TestElevation(profile, 15,ElevT);
}

void CTestProfile::Test7()
{
   // Test a profile with no elements
   CComPtr<IProfile> profile;
   profile.CoCreateInstance(CLSID_Profile);

   Float64 val;
   profile->Elevation(CComVariant(100.00),0.0,&val);
   TRY_TEST(IsZero(val),true);

   profile->Grade(CComVariant(100.00),&val);
   TRY_TEST(IsZero(val),true);

   profile->LeftCrownSlope(CComVariant(100.00),&val);
   TRY_TEST(IsZero(val),true);

   profile->RightCrownSlope(CComVariant(100.00),&val);
   TRY_TEST(IsZero(val),true);

   // add some cross sections and re-test the crown slopes
   CComPtr<ICrossSectionCollection> sections;
   profile->get_CrossSections(&sections);

   sections->Add(CComVariant(50.00), 0.00,-0.02,-0.02,NULL);
   sections->Add(CComVariant(100.00),0.00,-0.04,-0.04,NULL);

   profile->LeftCrownSlope(CComVariant(0.00),&val);
   TRY_TEST(IsEqual(val,-0.02),true);

   profile->RightCrownSlope(CComVariant(0.00),&val);
   TRY_TEST(IsEqual(val,-0.02),true);

   profile->LeftCrownSlope(CComVariant(50.00),&val);
   TRY_TEST(IsEqual(val,-0.02),true);

   profile->RightCrownSlope(CComVariant(50.00),&val);
   TRY_TEST(IsEqual(val,-0.02),true);

   profile->LeftCrownSlope(CComVariant(75.00),&val);
   TRY_TEST(IsEqual(val,-0.03),true);

   profile->RightCrownSlope(CComVariant(75.00),&val);
   TRY_TEST(IsEqual(val,-0.03),true);

   profile->LeftCrownSlope(CComVariant(100.00),&val);
   TRY_TEST(IsEqual(val,-0.04),true);

   profile->RightCrownSlope(CComVariant(100.00),&val);
   TRY_TEST(IsEqual(val,-0.04),true);

   profile->LeftCrownSlope(CComVariant(150.00),&val);
   TRY_TEST(IsEqual(val,-0.04),true);

   profile->RightCrownSlope(CComVariant(150.00),&val);
   TRY_TEST(IsEqual(val,-0.04),true);
}

void CTestProfile::Test8()
{
   // Test a profile with one point element
   CComPtr<IProfile> profile;
   profile.CoCreateInstance(CLSID_Profile);

   CComPtr<IProfilePoint> point;
   point.CoCreateInstance(CLSID_ProfilePoint);
   point->put_Station(CComVariant(100));
   point->put_Elevation(100);

   profile->AddEx(point);

   Float64 val;
   profile->Elevation(CComVariant(100.00),0.0,&val);
   TRY_TEST(IsEqual(val,100.0),true);

   profile->Grade(CComVariant(100.00),&val);
   TRY_TEST(IsZero(val),true);

   profile->LeftCrownSlope(CComVariant(100.00),&val);
   TRY_TEST(IsZero(val),true);

   profile->RightCrownSlope(CComVariant(100.00),&val);
   TRY_TEST(IsZero(val),true);

   // add some cross sections and re-test the crown slopes
   CComPtr<ICrossSectionCollection> sections;
   profile->get_CrossSections(&sections);

   sections->Add(CComVariant(50.00), 0.00,-0.02,-0.02,NULL);
   sections->Add(CComVariant(100.00),0.00,-0.04,-0.04,NULL);

   profile->LeftCrownSlope(CComVariant(0.00),&val);
   TRY_TEST(IsEqual(val,-0.02),true);

   profile->RightCrownSlope(CComVariant(0.00),&val);
   TRY_TEST(IsEqual(val,-0.02),true);

   profile->LeftCrownSlope(CComVariant(50.00),&val);
   TRY_TEST(IsEqual(val,-0.02),true);

   profile->RightCrownSlope(CComVariant(50.00),&val);
   TRY_TEST(IsEqual(val,-0.02),true);

   profile->LeftCrownSlope(CComVariant(75.00),&val);
   TRY_TEST(IsEqual(val,-0.03),true);

   profile->RightCrownSlope(CComVariant(75.00),&val);
   TRY_TEST(IsEqual(val,-0.03),true);

   profile->LeftCrownSlope(CComVariant(100.00),&val);
   TRY_TEST(IsEqual(val,-0.04),true);

   profile->RightCrownSlope(CComVariant(100.00),&val);
   TRY_TEST(IsEqual(val,-0.04),true);

   profile->LeftCrownSlope(CComVariant(150.00),&val);
   TRY_TEST(IsEqual(val,-0.04),true);

   profile->RightCrownSlope(CComVariant(150.00),&val);
   TRY_TEST(IsEqual(val,-0.04),true);
}

void CTestProfile::Test9()
{
   // Test a profile with one vertical curve element
   CComPtr<IProfile> profile;
   profile.CoCreateInstance(CLSID_Profile);

   CComPtr<IVertCurve> vc;
   vc.CoCreateInstance(CLSID_VertCurve);
   CComPtr<IProfilePoint> point;
   vc->get_PBG(&point);
   point->put_Station(CComVariant(4850));
   point->put_Elevation(436.34);

   point.Release();
   vc->get_PVI(&point);
   point->put_Station(CComVariant(5250));
   point->put_Elevation(432.34);

   point.Release();
   vc->get_PFG(&point);
   point->put_Station(CComVariant(5650));
   point->put_Elevation(441.14);

   vc->put_L1(400);
   vc->put_L2(400);

   profile->AddEx(vc);

   Float64 elev;
   profile->Elevation(CComVariant(4700),0.00,&elev);   TRY_TEST(IsEqual(elev,437.84),true);
   profile->Elevation(CComVariant(4850),0.00,&elev);   TRY_TEST(IsEqual(elev,436.34),true);
   profile->Elevation(CComVariant(4900),0.00,&elev);   TRY_TEST(IsEqual(elev,435.89),true);
   profile->Elevation(CComVariant(5000),0.00,&elev);   TRY_TEST(IsEqual(elev,435.29),true);
   profile->Elevation(CComVariant(5100),0.00,&elev);   TRY_TEST(IsEqual(elev,435.09),true);
   profile->Elevation(CComVariant(5200),0.00,&elev);   TRY_TEST(IsEqual(elev,435.29),true);
   profile->Elevation(CComVariant(5300),0.00,&elev);   TRY_TEST(IsEqual(elev,435.89),true);
   profile->Elevation(CComVariant(5400),0.00,&elev);   TRY_TEST(IsEqual(elev,436.89),true);
   profile->Elevation(CComVariant(5500),0.00,&elev);   TRY_TEST(IsEqual(elev,438.29),true);
   profile->Elevation(CComVariant(5600),0.00,&elev);   TRY_TEST(IsEqual(elev,440.09),true);
   profile->Elevation(CComVariant(5650),0.00,&elev);   TRY_TEST(IsEqual(elev,441.14),true);
   profile->Elevation(CComVariant(6000),0.00,&elev);   TRY_TEST(IsEqual(elev,448.84),true);
}

void CTestProfile::Test10()
{
   // Test a profile with one vertical curve element
   CComPtr<IProfile> profile;
   profile.CoCreateInstance(CLSID_Profile);

   CComPtr<IVertCurve> vc;
   vc.CoCreateInstance(CLSID_VertCurve);
   CComPtr<IProfilePoint> point;
   vc->get_PBG(&point);
   point->put_Station(CComVariant(100));
   point->put_Elevation(100);

   point.Release();
   vc->get_PVI(&point);
   point->put_Station(CComVariant(200));
   point->put_Elevation(90);

   point.Release();
   vc->get_PFG(&point);
   point->put_Station(CComVariant(300));
   point->put_Elevation(100);

   vc->put_L1(50);
   vc->put_L2(50);

   profile->AddEx(vc);

   CComPtr<ICrossSectionCollection> cs;
   profile->get_CrossSections(&cs);
   cs->Add(CComVariant(100.0),0.0,-0.02,-0.04,NULL);

   Float64 elev;
   profile->Elevation(CComVariant(100), 0.00,&elev);   TRY_TEST(IsEqual(elev,100.00),true);
   profile->Elevation(CComVariant(100), 5.00,&elev);   TRY_TEST(IsEqual(elev, 99.80),true);
   profile->Elevation(CComVariant(100),-5.00,&elev);   TRY_TEST(IsEqual(elev, 99.90),true);
}

void CTestProfile::Test11()
{
   // Test a profile with 3 vertical curve elements
   // Adding this test because I found an error that was
   // not detected by the previous test cases.
   // The elevation at the BVC not computed correctly by the Profile object
   // however, it is computed correctly by the VertCurve object
   // RAB: 11/14/2001
   CComPtr<IProfile> profile;
   profile.CoCreateInstance(CLSID_Profile);

   // Start point
   CComPtr<IProfilePoint> start;
   start.CoCreateInstance(CLSID_ProfilePoint);
   start->put_Station(CComVariant(100));
   start->put_Elevation(50);

   CComPtr<IProfilePoint> pvi;

   // Vert Curve #1
   CComPtr<IVertCurve> vc1;
   vc1.CoCreateInstance(CLSID_VertCurve);
   vc1->put_L1(50);
   vc1->put_L2(50);
   pvi.Release();
   vc1->get_PVI(&pvi);
   pvi->put_Station(CComVariant(300));
   pvi->put_Elevation(80);

   // Vert Curve #2
   CComPtr<IVertCurve> vc2;
   vc2.CoCreateInstance(CLSID_VertCurve);
   vc2->put_L1(50);
   vc2->put_L2(50);
   pvi.Release();
   vc2->get_PVI(&pvi);
   pvi->put_Station(CComVariant(500));
   pvi->put_Elevation(50);

   // Vert Curve #3
   CComPtr<IVertCurve> vc3;
   vc3.CoCreateInstance(CLSID_VertCurve);
   vc3->put_L1(50);
   vc3->put_L2(50);
   pvi.Release();
   vc3->get_PVI(&pvi);
   pvi->put_Station(CComVariant(700));
   pvi->put_Elevation(80);

   // Finish point
   CComPtr<IProfilePoint> finish;
   finish.CoCreateInstance(CLSID_ProfilePoint);
   finish->put_Station(CComVariant(900));
   finish->put_Elevation(50);


   // Set the PBG and PFG for each Vert Curve
   // Use the Start, Finish, and PVI points.
   vc1->putref_PBG(start);
   pvi.Release();
   vc2->get_PVI(&pvi);
   vc1->putref_PFG(pvi);

   pvi.Release();
   vc1->get_PVI(&pvi);
   vc2->putref_PBG(pvi);
   pvi.Release();
   vc3->get_PVI(&pvi);
   vc2->putref_PFG(pvi);

   pvi.Release();
   vc2->get_PVI(&pvi);
   vc3->putref_PBG(pvi);
   vc3->putref_PFG(finish);

   profile->AddEx(start);
   profile->AddEx(vc1);
   profile->AddEx(vc2);
   profile->AddEx(vc3);
   profile->AddEx(finish);

   Float64 elev;
   profile->Elevation(CComVariant(250), 0.00,&elev);   TRY_TEST(IsEqual(elev,72.5),true);
   profile->Elevation(CComVariant(450), 0.00,&elev);   TRY_TEST(IsEqual(elev,57.5),true);
   profile->Elevation(CComVariant(650), 0.00,&elev);   TRY_TEST(IsEqual(elev,72.5),true);
}

STDMETHODIMP CTestProfile::OnProfileChanged(IProfile* pp)
{
//   ::MessageBox(NULL,"OnProfileChanged","Event",MB_OK);
   Pass();
   return S_OK;
}

void TestElevation(IProfile* profile,Float64 offset,Float64 results[])
{
   long j = 0;
   for ( long i = 440; i <= 1560; i += 160, j++)
   {
      Float64 elev;
      Float64 station = (Float64)i;
      profile->Elevation(CComVariant(station),offset,&elev);
      TRY_TEST( IsEqual(elev, results[j],0.001), true );
   }
}

void TestGrade(IProfile* profile,Float64 results[])
{
   long j = 0;
   for ( long i = 440; i <= 1560; i += 160, j++)
   {
      Float64 grade;
      Float64 station = (Float64)i;
      profile->Grade(CComVariant(station),&grade);
      TRY_TEST( IsEqual(grade*100, results[j],0.001), true );
   }
}

void TestCrownSlopes(IProfile* profile,Float64 results[][2])
{
   long j = 0;
   for ( long i = 440; i <= 1560; i += 160, j++)
   {
      Float64 left, right;
      Float64 station = (Float64)i;
      profile->LeftCrownSlope(CComVariant(station),&left);
      profile->RightCrownSlope(CComVariant(station),&right);
      TRY_TEST( IsEqual(left,  results[j][0], 0.001), true );
      TRY_TEST( IsEqual(right, results[j][1], 0.001), true );
   }
}