///////////////////////////////////////////////////////////////////////
// COGOTest - Test Driver for Coordinate Geometry Library
// Copyright © 1999-2023  Washington State Department of Transportation
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
void TestGrade(IProfile* profile,Float64 results[],long minStation=440,long maxStation=1560,long inc=160);
void TestCrownSlopes(IProfile* profile,IDType surfaceID,IndexType ridgePointIdx,Float64 results[][2],long minStation=440,long maxStation=1560,long inc=160);
void TestElevation(IProfile* profile,IDType surfaceID,Float64 offset,Float64 results[],long minStation=440,long maxStation=1560,long inc=160);

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
   Test12();
}

void CTestProfile::Test1()
{
   CComPtr<IAlignment> alignment;
   alignment.CoCreateInstance(CLSID_Alignment);

   CComPtr<IProfile> profile;
   TRY_TEST(profile.CoCreateInstance(CLSID_Profile),S_OK);

   alignment->AddProfile(0, profile);

   //
   // Test Add
   //

   CComPtr<IProfilePoint> start;
   start.CoCreateInstance(CLSID_ProfilePoint);
   start->put_Station(CComVariant(100.0));
   start->put_Elevation(50.0);

   CComPtr<IProfilePoint> end;
   end.CoCreateInstance(CLSID_ProfilePoint);
   end->put_Station(CComVariant(50.0));
   end->put_Elevation(10.0);

   CComPtr<IProfileSegment> segment;
   segment.CoCreateInstance(CLSID_ProfileSegment);
   segment->Move(start, end);
   CComQIPtr<IProfileElement> element(segment);

   // add it to the profile
   TRY_TEST(profile->AddProfileElement(nullptr),E_INVALIDARG);
   TRY_TEST(profile->AddProfileElement(element), S_OK);

   // create a vertical curve
   CComPtr<IVerticalCurve> vc;
   vc.CoCreateInstance(CLSID_VerticalCurve);
   CComPtr<IProfilePoint> point;
   point.Release();
   vc->get_PBG(&point);
   point->put_Station(CComVariant(200));
   point->put_Elevation(250);
   vc->put_PBG(point);

   point.Release();
   vc->get_PVI(&point);
   point->put_Station(CComVariant(300));
   point->put_Elevation(250);
   vc->put_PVI(point);

   point.Release();
   vc->get_PFG(&point);
   point->put_Station(CComVariant(400));
   point->put_Elevation(150);
   vc->put_PFG(point);

   vc->put_L1(100);
   vc->put_L2(100);

   // add it to the profile
   element.Release();
   vc.QueryInterface(&element);
   TRY_TEST(profile->AddProfileElement(element), S_OK);

   //
   // Test Count
   //
   IndexType count;
   TRY_TEST(profile->get_ProfileElementCount(nullptr),E_POINTER);
   TRY_TEST(profile->get_ProfileElementCount(&count),S_OK);
   TRY_TEST(count,2);

   //
   // Test Item
   //

   // make sure items are sorted properly
   element.Release();
   TRY_TEST(profile->get_Item(-1,&element),E_INVALIDARG);
   TRY_TEST(profile->get_Item(100,&element),E_INVALIDARG);
   TRY_TEST(profile->get_Item(0,nullptr),E_POINTER);
   TRY_TEST(profile->get_Item(0,&element),S_OK);

   point.Release();
   element->GetStartPoint(&point);
   CComPtr<IStation> station;
   Float64 sta, elev;
   point->get_Station(&station);
   station->get_Value(&sta);
   point->get_Elevation(&elev);
   TRY_TEST(IsEqual(sta,100.0),true);
   TRY_TEST(IsEqual(elev,50.0),true);

   point.Release();
   station.Release();
   element->GetEndPoint(&point);
   point->get_Station(&station);
   station->get_Value(&sta);
   point->get_Elevation(&elev);
   TRY_TEST(IsEqual(sta, 50.0), true);
   TRY_TEST(IsEqual(elev, 10.0), true);

   element.Release();
   TRY_TEST(profile->get_Item(1,&element),S_OK);

   point.Release();
   station.Release();
   element->GetStartPoint(&point);
   point->get_Station(&station);
   station->get_Value(&sta);
   point->get_Elevation(&elev);
   TRY_TEST(IsEqual(sta,200.0),true);
   TRY_TEST(IsEqual(elev,250.0),true);

   ////
   //// Test Remove
   ////
   //point.Release();
   //vc->get_BVC(&point);
   //TRY_TEST(profile->Remove(CComVariant()),E_INVALIDARG);
   //TRY_TEST(profile->Remove(CComVariant(profile)),E_INVALIDARG);
   //TRY_TEST(profile->Remove(CComVariant(-1)),E_INVALIDARG);
   //TRY_TEST(profile->Remove(CComVariant(100)),E_INVALIDARG);
   //TRY_TEST(profile->Remove(CComVariant(point)),E_INVALIDARG);
   //TRY_TEST(profile->Remove(CComVariant(vc)),S_OK); // Remove the vert curve
   //TRY_TEST(profile->Remove(CComVariant(1)),S_OK);  // Remove the element at index 1

   //profile->get_Count(&count);
   //TRY_TEST(count,1);

   //
   // Test Clear
   //
   profile->ClearProfileElements();
   profile->get_ProfileElementCount(&count);
   TRY_TEST(count,0);
   
   ////
   //// Test _Enum
   ////
   //profile->Clear();
   //profile->Add(element);
   //profile->Add(element);
   //CComPtr<IEnumProfileElements> pEnum;
   //TRY_TEST(profile->get__EnumProfileElements(nullptr), E_POINTER );
   //TRY_TEST(profile->get__EnumProfileElements(&pEnum), S_OK );

   //ULONG fetched;
   //CComPtr<IProfileElement> pe;
   //TRY_TEST(pEnum->Next(1,&pe,&fetched ),S_OK);
   //TRY_TEST(pe.IsEqualObject(element),true);

   //pe.Release();
   //TRY_TEST(pEnum->Next(1,&pe,&fetched ),S_OK);
   //TRY_TEST(pe.IsEqualObject(element),true);

   //point.Release();
   //vc.Release();
   //vc.CoCreateInstance(CLSID_VerticalCurve);

   // Test ISupportErrorInfo
   CComQIPtr<ISupportErrorInfo> eInfo(profile);
   TRY_TEST( eInfo != nullptr, true );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IProfile ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

   // Test IObjectSafety
   TRY_TEST( TestIObjectSafety(CLSID_Profile,IID_IProfile,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
}

void CTestProfile::Test2()
{
   CComPtr<IAlignment> alignment;
   alignment.CoCreateInstance(CLSID_Alignment);

   CComPtr<IProfile> profile;
   TRY_TEST(profile.CoCreateInstance(CLSID_Profile), S_OK);

   alignment->AddProfile(0, profile);


   //
   // Test Elevation and Grade
   //
   //
   // Profile Point: Station 6+00 Elev 80.0
   // Vert Curve: BVC  7+00 Elev  85.0
   //             PVI 10+00 Elev 100.0
   //             EVC 13+00 Elev  91.0
   // Profile Point: Station 14+00 Elev 88.0
   CComPtr<IProfilePoint> start;
   start.CoCreateInstance(CLSID_ProfilePoint);
   start->Move(CComVariant(600),80);

   CComPtr<IProfilePoint> pbg;
   pbg.CoCreateInstance(CLSID_ProfilePoint);
   pbg->Move(CComVariant(700), 85.0);

   CComPtr<IProfilePoint> pvi;
   pvi.CoCreateInstance(CLSID_ProfilePoint);
   pvi->Move(CComVariant(1000), 100);

   CComPtr<IProfilePoint> pfg;
   pfg.CoCreateInstance(CLSID_ProfilePoint);
   pfg->Move(CComVariant(1300), 91);

   CComPtr<IProfilePoint> end;
   end.CoCreateInstance(CLSID_ProfilePoint);
   end->Move(CComVariant(1400), 88);

   CComPtr<IProfileSegment> start_segment;
   start_segment.CoCreateInstance(CLSID_ProfileSegment);
   start_segment->Move(start, pbg);
   CComQIPtr<IProfileElement> element(start_segment);
   profile->AddProfileElement(element);

   CComPtr<IVerticalCurve> vc;
   vc.CoCreateInstance(CLSID_VerticalCurve);
   vc->Init(pbg, pvi, pfg, 300, 300);
   element.Release();
   vc.QueryInterface(&element);
   profile->AddProfileElement(element);

   CComPtr<IProfileSegment> end_segment;
   end_segment.CoCreateInstance(CLSID_ProfileSegment);
   end_segment->Move(pfg,end);
   element.Release();
   end_segment.QueryInterface(&element);
   profile->AddProfileElement(element);

   // create roadway surface model
   IDType surfaceID = 0;
   CComPtr<ISurface> surface;
   surface.CoCreateInstance(CLSID_Surface);
   profile->AddSurface(surfaceID, surface); // this may need to go after the surface is built with by-value semantics

   surface->put_SurfaceTemplateSegmentCount(4);
   surface->put_AlignmentPoint(3);
   surface->put_ProfileGradePoint(3);

   CComPtr<ISurfaceTemplate> template430;
   surface->CreateSurfaceTemplate(CComVariant(430), &template430);
   template430->UpdateSegmentParameters(0, 20.0, 0.02,tsHorizontal);
   template430->UpdateSegmentParameters(1,  5.0, 0.02,tsHorizontal);
   template430->UpdateSegmentParameters(2,  5.0,-0.02,tsHorizontal);
   template430->UpdateSegmentParameters(3, 20.0,-0.02,tsHorizontal);

   CComPtr<ISurfaceTemplate> template700;
   surface->CreateSurfaceTemplate(CComVariant(700), &template700);
   template700->UpdateSegmentParameters(0, 20.0, 0.02,tsHorizontal);
   template700->UpdateSegmentParameters(1,  5.0, 0.02,tsHorizontal);
   template700->UpdateSegmentParameters(2,  5.0,-0.02,tsHorizontal);
   template700->UpdateSegmentParameters(3, 20.0,-0.02,tsHorizontal);

   CComPtr<ISurfaceTemplate> template1000;
   surface->CreateSurfaceTemplate(CComVariant(1000), &template1000);
   template1000->UpdateSegmentParameters(0, 20.0,-0.06,tsHorizontal);
   template1000->UpdateSegmentParameters(1,  5.0,-0.06,tsHorizontal);
   template1000->UpdateSegmentParameters(2,  5.0,-0.06,tsHorizontal);
   template1000->UpdateSegmentParameters(3, 20.0,-0.06,tsHorizontal);

   CComPtr<ISurfaceTemplate> template1300;
   surface->CreateSurfaceTemplate(CComVariant(1300), &template1300);
   template1300->UpdateSegmentParameters(0, 20.0, 0.04,tsHorizontal);
   template1300->UpdateSegmentParameters(1,  5.0, 0.04,tsHorizontal);
   template1300->UpdateSegmentParameters(2,  5.0,-0.08,tsHorizontal);
   template1300->UpdateSegmentParameters(3, 20.0,-0.08,tsHorizontal);

   CComPtr<ISurfaceTemplate> template1600;
   surface->CreateSurfaceTemplate(CComVariant(1600), &template1600);
   template1600->UpdateSegmentParameters(0, 20.0, 0.04, tsHorizontal);
   template1600->UpdateSegmentParameters(1, 5.0, 0.04, tsHorizontal);
   template1600->UpdateSegmentParameters(2, 5.0, -0.08, tsHorizontal);
   template1600->UpdateSegmentParameters(3, 20.0,-0.08,tsHorizontal);

   Float64 Grades[] = { 5.0000, 5.0000, 4.2000, 2.0667, -0.0667, -2.2000, -3.0000, -3.0000 };
   TestGrade(profile,Grades);

   Float64 CrownSlopes1[][2] = { {  0.0200, -0.0200}, {  0.0200, -0.0200}, {  0.0040, -0.0280}, { -0.0387, -0.0493}, { -0.0333,-0.0653}, { 0.0200, -0.0760}, { 0.0400, -0.0800}, { 0.0400, -0.0800} };
   TestCrownSlopes(profile,surfaceID,2,CrownSlopes1);

   Float64 ElevA[] = { 71.900, 79.900, 87.860, 93.407, 95.033, 92.740, 88.000, 83.200 };
   Float64 ElevB[] = { 72.100, 80.100, 87.900, 93.020, 94.700, 92.940, 88.400, 83.600 };
   Float64 ElevC[] = { 72.040, 80.040, 87.816, 92.872, 94.504, 92.712, 88.160, 83.360 };
   Float64 ElevD[] = { 72.000, 80.000, 87.760, 92.773, 94.373, 92.560, 88.000, 83.200 };
   Float64 ElevE[] = { 71.900, 79.900, 87.620, 92.527, 94.047, 92.180, 87.600, 82.800 };
   Float64 ElevOL[]= { 71.600, 79.600, 87.800, 93.987, 95.533, 92.440, 87.400, 82.600 };
   Float64 ElevOR[]= { 71.600, 79.600, 87.200, 91.787, 93.067, 91.040, 86.400, 81.600 };
   TestElevation(profile, surfaceID,-15,ElevA);
   TestElevation(profile, surfaceID, -5,ElevB);
   TestElevation(profile, surfaceID, -2,ElevC);
   TestElevation(profile, surfaceID,  0,ElevD);
   TestElevation(profile, surfaceID,  5,ElevE);
   TestElevation(profile, surfaceID,-35,ElevOL); // off of surface at left edge
   TestElevation(profile, surfaceID,-50,ElevOL); // off of surface at left edge
   TestElevation(profile, surfaceID, 30,ElevOR); // off of surface at right edge
   TestElevation(profile, surfaceID, 50,ElevOR); // off of surface at right edge

   // shift the crown point offset to +5
   surface->put_AlignmentPoint(1);
   surface->put_ProfileGradePoint(1);

   Float64 ElevF[] = { 71.900, 79.900, 87.740, 92.967, 94.540, 92.460, 87.800, 83.000 };
   Float64 ElevG[] = { 72.000, 80.000, 87.760, 92.773, 94.373, 92.560, 88.000, 83.200 };
   Float64 ElevH[] = { 72.040, 80.040, 87.768, 92.696, 94.307, 92.600, 88.080, 83.280 };
   Float64 ElevI[] = { 72.100, 80.100, 87.780, 92.580, 94.207, 92.660, 88.200, 83.400 };
   Float64 ElevJ[] = { 71.900, 79.900, 87.500, 92.087, 93.553, 91.900, 87.400, 82.600 };
   TestElevation(profile, surfaceID, -5,ElevF);
   TestElevation(profile, surfaceID,  0,ElevG);
   TestElevation(profile, surfaceID,  2,ElevH);
   TestElevation(profile, surfaceID,  5,ElevI);
   TestElevation(profile, surfaceID, 15,ElevJ);

   // shift the crown point offset back to -5 and reverse all of the crown slopes
   surface->put_AlignmentPoint(3);
   surface->put_ProfileGradePoint(3);

   IndexType nTemplates;
   surface->GetSurfaceTemplateCount(&nTemplates);
   for(IndexType idx = 0; idx < nTemplates; idx++)
   {
      CComPtr<ISurfaceTemplate> surface_template;
      surface->GetSurfaceTemplate(idx, &surface_template);
      IndexType nSegments;
      surface_template->get_Count(&nSegments);
      for ( IndexType idx = 0; idx < nSegments; idx++ )
      {
         Float64 width, slope;
         TemplateSlopeType slopeType;
         surface_template->GetSegmentParameters(idx, &width, &slope, &slopeType);

         slope *= -1;
         surface_template->UpdateSegmentParameters(idx, width, slope, slopeType);
      }
   }

   Float64 CrownSlopes2[][2] = { { -0.0200,  0.0200}, { -0.0200,  0.0200}, { -0.0040,  0.0280}, { 0.0387,  0.0493}, { 0.0333, 0.0653}, { -0.0200,  0.0760}, { -0.0400,  0.0800}, { -0.0400,  0.0800} };
   TestCrownSlopes(profile,surfaceID,2,CrownSlopes2);

   Float64 ElevK[] = { 72.100, 80.100, 87.660, 92.140, 93.713, 92.380, 88.000, 83.200 };
   Float64 ElevL[] = { 71.900, 79.900, 87.620, 92.527, 94.047, 92.180, 87.600, 82.800 };
   Float64 ElevM[] = { 71.960, 79.960, 87.704, 92.675, 94.243, 92.408, 87.840, 83.040 };
   Float64 ElevN[] = { 72.000, 80.000, 87.760, 92.773, 94.373, 92.560, 88.000, 83.200 };
   Float64 ElevO[] = { 72.100, 80.100, 87.900, 93.020, 94.700, 92.940, 88.400, 83.600 };
   TestElevation(profile, surfaceID,-15,ElevK);
   TestElevation(profile, surfaceID, -5,ElevL);
   TestElevation(profile, surfaceID, -2,ElevM);
   TestElevation(profile, surfaceID,  0,ElevN);
   TestElevation(profile, surfaceID,  5,ElevO);

   // shift the crown point offset to +5, keep the slopes the same
   surface->put_AlignmentPoint(1);
   surface->put_ProfileGradePoint(1);

   Float64 ElevP[] = { 72.100, 80.100, 87.780, 92.580, 94.207, 92.660, 88.200, 83.400 };
   Float64 ElevQ[] = { 72.000, 80.000, 87.760, 92.773, 94.373, 92.560, 88.000, 83.200 };
   Float64 ElevR[] = { 71.960, 79.960, 87.752, 92.851, 94.440, 92.520, 87.920, 83.120 };
   Float64 ElevS[] = { 71.900, 79.900, 87.740, 92.967, 94.540, 92.460, 87.800, 83.000 };
   Float64 ElevT[] = { 72.100, 80.100, 88.020, 93.460, 95.193, 93.220, 88.600, 83.800 };
   TestElevation(profile, surfaceID, -5,ElevP);
   TestElevation(profile, surfaceID,  0,ElevQ);
   TestElevation(profile, surfaceID,  2,ElevR);
   TestElevation(profile, surfaceID,  5,ElevS);
   TestElevation(profile, surfaceID, 15,ElevT);
}

void CTestProfile::Test3()
{
   CComPtr<IAlignment> alignment;
   alignment.CoCreateInstance(CLSID_Alignment);

   CComPtr<IProfile> profile;
   TRY_TEST(profile.CoCreateInstance(CLSID_Profile), S_OK);

   alignment->AddProfile(0, profile);


   //
   // Test Elevation and Grade
   //
   //
   // Vert Curve: BVC  7+00 Elev  85.0
   //             PVI 10+00 Elev 100.0
   //             EVC 13+00 Elev  91.0
   //
   // Profile Point: Station 14+00 Elev 88.0

   CComPtr<IProfilePoint> pbg;
   pbg.CoCreateInstance(CLSID_ProfilePoint);
   pbg->Move(CComVariant(700), 85.0);

   CComPtr<IProfilePoint> pvi;
   pvi.CoCreateInstance(CLSID_ProfilePoint);
   pvi->Move(CComVariant(1000), 100);

   CComPtr<IProfilePoint> pfg;
   pfg.CoCreateInstance(CLSID_ProfilePoint);
   pfg->Move(CComVariant(1300), 91);

   CComPtr<IProfilePoint> end;
   end.CoCreateInstance(CLSID_ProfilePoint);
   end->Move(CComVariant(1400), 88);

   CComPtr<IVerticalCurve> vc;
   vc.CoCreateInstance(CLSID_VerticalCurve);
   vc->Init(pbg, pvi, pfg, 300, 300);
   CComQIPtr<IProfileElement> element(vc);
   profile->AddProfileElement(element);

   CComPtr<IProfileSegment> end_segment;
   end_segment.CoCreateInstance(CLSID_ProfileSegment);
   end_segment->Move(pfg, end);
   element.Release();
   end_segment.QueryInterface(&element);
   profile->AddProfileElement(element);

   // create roadway surface model
   IDType surfaceID = 0;
   CComPtr<ISurface> surface;
   surface.CoCreateInstance(CLSID_Surface);
   profile->AddSurface(surfaceID, surface); // this may need to go after the surface is built with by-value semantics

   surface->put_SurfaceTemplateSegmentCount(4);
   surface->put_AlignmentPoint(3);
   surface->put_ProfileGradePoint(3);

   CComPtr<ISurfaceTemplate> template430;
   surface->CreateSurfaceTemplate(CComVariant(430), &template430);
   template430->UpdateSegmentParameters(0, 20.0, 0.02, tsHorizontal);
   template430->UpdateSegmentParameters(1, 5.0, 0.02, tsHorizontal);
   template430->UpdateSegmentParameters(2, 5.0, -0.02, tsHorizontal);
   template430->UpdateSegmentParameters(3, 20.0, -0.02, tsHorizontal);

   CComPtr<ISurfaceTemplate> template700;
   surface->CreateSurfaceTemplate(CComVariant(700), &template700);
   template700->UpdateSegmentParameters(0, 20.0, 0.02, tsHorizontal);
   template700->UpdateSegmentParameters(1, 5.0, 0.02, tsHorizontal);
   template700->UpdateSegmentParameters(2, 5.0, -0.02, tsHorizontal);
   template700->UpdateSegmentParameters(3, 20.0, -0.02, tsHorizontal);

   CComPtr<ISurfaceTemplate> template1000;
   surface->CreateSurfaceTemplate(CComVariant(1000), &template1000);
   template1000->UpdateSegmentParameters(0, 20.0, -0.06, tsHorizontal);
   template1000->UpdateSegmentParameters(1, 5.0, -0.06, tsHorizontal);
   template1000->UpdateSegmentParameters(2, 5.0, -0.06, tsHorizontal);
   template1000->UpdateSegmentParameters(3, 20.0, -0.06, tsHorizontal);

   CComPtr<ISurfaceTemplate> template1300;
   surface->CreateSurfaceTemplate(CComVariant(1300), &template1300);
   template1300->UpdateSegmentParameters(0, 20.0, 0.04, tsHorizontal);
   template1300->UpdateSegmentParameters(1, 5.0, 0.04, tsHorizontal);
   template1300->UpdateSegmentParameters(2, 5.0, -0.08, tsHorizontal);
   template1300->UpdateSegmentParameters(3, 20.0, -0.08, tsHorizontal);

   CComPtr<ISurfaceTemplate> template1600;
   surface->CreateSurfaceTemplate(CComVariant(1600), &template1600);
   template1600->UpdateSegmentParameters(0, 20.0, 0.04, tsHorizontal);
   template1600->UpdateSegmentParameters(1, 5.0, 0.04, tsHorizontal);
   template1600->UpdateSegmentParameters(2, 5.0, -0.08, tsHorizontal);
   template1600->UpdateSegmentParameters(3, 20.0, -0.08, tsHorizontal);

   Float64 Grades[] = { 5.0000, 5.0000, 4.2000, 2.0667, -0.0667, -2.2000, -3.0000, -3.0000 };
   TestGrade(profile,Grades);

   Float64 CrownSlopes1[][2] = { {  0.0200, -0.0200}, {  0.0200, -0.0200}, {  0.0040, -0.0280}, { -0.0387, -0.0493}, { -0.0333,-0.0653}, { 0.0200, -0.0760}, { 0.0400, -0.0800}, { 0.0400, -0.0800} };
   TestCrownSlopes(profile,surfaceID,2,CrownSlopes1);

   Float64 ElevA[] = { 71.900, 79.900, 87.860, 93.407, 95.033, 92.740, 88.000, 83.200 };
   Float64 ElevB[] = { 72.100, 80.100, 87.900, 93.020, 94.700, 92.940, 88.400, 83.600 };
   Float64 ElevC[] = { 72.040, 80.040, 87.816, 92.872, 94.504, 92.712, 88.160, 83.360 };
   Float64 ElevD[] = { 72.000, 80.000, 87.760, 92.773, 94.373, 92.560, 88.000, 83.200 };
   Float64 ElevE[] = { 71.900, 79.900, 87.620, 92.527, 94.047, 92.180, 87.600, 82.800 };
   TestElevation(profile, surfaceID,-15,ElevA);
   TestElevation(profile, surfaceID, -5,ElevB);
   TestElevation(profile, surfaceID, -2,ElevC);
   TestElevation(profile, surfaceID,  0,ElevD);
   TestElevation(profile, surfaceID,  5,ElevE);

   // shift the crown point offset to +5
   surface->put_AlignmentPoint(1);
   surface->put_ProfileGradePoint(1);

   Float64 ElevF[] = { 71.900, 79.900, 87.740, 92.967, 94.540, 92.460, 87.800, 83.000 };
   Float64 ElevG[] = { 72.000, 80.000, 87.760, 92.773, 94.373, 92.560, 88.000, 83.200 };
   Float64 ElevH[] = { 72.040, 80.040, 87.768, 92.696, 94.307, 92.600, 88.080, 83.280 };
   Float64 ElevI[] = { 72.100, 80.100, 87.780, 92.580, 94.207, 92.660, 88.200, 83.400 };
   Float64 ElevJ[] = { 71.900, 79.900, 87.500, 92.087, 93.553, 91.900, 87.400, 82.600 };
   TestElevation(profile, surfaceID, -5,ElevF);
   TestElevation(profile, surfaceID,  0,ElevG);
   TestElevation(profile, surfaceID,  2,ElevH);
   TestElevation(profile, surfaceID,  5,ElevI);
   TestElevation(profile, surfaceID, 15,ElevJ);

   // shift the crown point offset back to -5 and reverse all of the crown slopes
   surface->put_AlignmentPoint(3);
   surface->put_ProfileGradePoint(3);

   IndexType nTemplates;
   surface->GetSurfaceTemplateCount(&nTemplates);
   for (IndexType idx = 0; idx < nTemplates; idx++)
   {
      CComPtr<ISurfaceTemplate> surface_template;
      surface->GetSurfaceTemplate(idx, &surface_template);
      IndexType nSegments;
      surface_template->get_Count(&nSegments);
      for (IndexType idx = 0; idx < nSegments; idx++)
      {
         Float64 width, slope;
         TemplateSlopeType slopeType;
         surface_template->GetSegmentParameters(idx, &width, &slope, &slopeType);

         slope *= -1;
         surface_template->UpdateSegmentParameters(idx, width, slope, slopeType);
      }
   }

   Float64 CrownSlopes2[][2] = { { -0.0200,  0.0200}, { -0.0200,  0.0200}, { -0.0040,  0.0280}, { 0.0387,  0.0493}, { 0.0333, 0.0653}, {-0.0200,  0.0760}, {-0.0400,  0.0800}, {-0.0400,  0.0800} };
   TestCrownSlopes(profile,surfaceID,2,CrownSlopes2);

   Float64 ElevK[] = { 72.100, 80.100, 87.660, 92.140, 93.713, 92.380, 88.000, 83.200 };
   Float64 ElevL[] = { 71.900, 79.900, 87.620, 92.527, 94.047, 92.180, 87.600, 82.800 };
   Float64 ElevM[] = { 71.960, 79.960, 87.704, 92.675, 94.243, 92.408, 87.840, 83.040 };
   Float64 ElevN[] = { 72.000, 80.000, 87.760, 92.773, 94.373, 92.560, 88.000, 83.200 };
   Float64 ElevO[] = { 72.100, 80.100, 87.900, 93.020, 94.700, 92.940, 88.400, 83.600 };
   TestElevation(profile, surfaceID,-15,ElevK);
   TestElevation(profile, surfaceID, -5,ElevL);
   TestElevation(profile, surfaceID, -2,ElevM);
   TestElevation(profile, surfaceID,  0,ElevN);
   TestElevation(profile, surfaceID,  5,ElevO);

   // shift the crown point offset to +5, keep the slopes the same
   surface->put_AlignmentPoint(1);
   surface->put_ProfileGradePoint(1);
   
   Float64 ElevP[] = { 72.100, 80.100, 87.780, 92.580, 94.207, 92.660, 88.200, 83.400 };
   Float64 ElevQ[] = { 72.000, 80.000, 87.760, 92.773, 94.373, 92.560, 88.000, 83.200 };
   Float64 ElevR[] = { 71.960, 79.960, 87.752, 92.851, 94.440, 92.520, 87.920, 83.120 };
   Float64 ElevS[] = { 71.900, 79.900, 87.740, 92.967, 94.540, 92.460, 87.800, 83.000 };
   Float64 ElevT[] = { 72.100, 80.100, 88.020, 93.460, 95.193, 93.220, 88.600, 83.800 };
   TestElevation(profile, surfaceID, -5,ElevP);
   TestElevation(profile, surfaceID,  0,ElevQ);
   TestElevation(profile, surfaceID,  2,ElevR);
   TestElevation(profile, surfaceID,  5,ElevS);
   TestElevation(profile, surfaceID, 15,ElevT);
}

void CTestProfile::Test4()
{
   CComPtr<IAlignment> alignment;
   alignment.CoCreateInstance(CLSID_Alignment);

   CComPtr<IProfile> profile;
   TRY_TEST(profile.CoCreateInstance(CLSID_Profile), S_OK);

   alignment->AddProfile(0, profile);


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

   CComPtr<IProfilePoint> pbg1;
   pbg1.CoCreateInstance(CLSID_ProfilePoint);
   pbg1->Move(CComVariant(700), 85.0);

   CComPtr<IProfilePoint> pvi1;
   pvi1.CoCreateInstance(CLSID_ProfilePoint);
   pvi1->Move(CComVariant(1000), 100);

   CComPtr<IProfilePoint> pfg1;
   pfg1.CoCreateInstance(CLSID_ProfilePoint);
   pfg1->Move(CComVariant(1300), 91);

   CComPtr<IProfilePoint> pbg2;
   pbg2.CoCreateInstance(CLSID_ProfilePoint);
   pbg2->Move(CComVariant(1390), 85.0);

   CComPtr<IProfilePoint> pvi2;
   pvi2.CoCreateInstance(CLSID_ProfilePoint);
   pvi2->Move(CComVariant(1450), 100);

   CComPtr<IProfilePoint> pfg2;
   pfg2.CoCreateInstance(CLSID_ProfilePoint);
   pfg2->Move(CComVariant(1490), 91);

   CComPtr<IVerticalCurve> vc1;
   vc1.CoCreateInstance(CLSID_VerticalCurve);
   vc1->Init(pbg1, pvi1, pfg1, 300, 300);
   CComQIPtr<IProfileElement> element(vc1);
   profile->AddProfileElement(element);

   CComPtr<IVerticalCurve> vc2;
   vc2.CoCreateInstance(CLSID_VerticalCurve);
   vc2->Init(pbg2, pvi2, pfg2, 60, 40);
   element.Release();
   vc2.QueryInterface(&element);
   profile->AddProfileElement(element);

   // create roadway surface model
   IDType surfaceID = 0;
   CComPtr<ISurface> surface;
   surface.CoCreateInstance(CLSID_Surface);
   profile->AddSurface(surfaceID, surface); // this may need to go after the surface is built with by-value semantics

   surface->put_SurfaceTemplateSegmentCount(4);
   surface->put_AlignmentPoint(3);
   surface->put_ProfileGradePoint(3);

   CComPtr<ISurfaceTemplate> template430;
   surface->CreateSurfaceTemplate(CComVariant(430), &template430);
   template430->UpdateSegmentParameters(0, 20.0, 0.02, tsHorizontal);
   template430->UpdateSegmentParameters(1, 5.0, 0.02, tsHorizontal);
   template430->UpdateSegmentParameters(2, 5.0, -0.02, tsHorizontal);
   template430->UpdateSegmentParameters(3, 20.0, -0.02, tsHorizontal);

   CComPtr<ISurfaceTemplate> template700;
   surface->CreateSurfaceTemplate(CComVariant(700), &template700);
   template700->UpdateSegmentParameters(0, 20.0, 0.02, tsHorizontal);
   template700->UpdateSegmentParameters(1, 5.0, 0.02, tsHorizontal);
   template700->UpdateSegmentParameters(2, 5.0, -0.02, tsHorizontal);
   template700->UpdateSegmentParameters(3, 20.0, -0.02, tsHorizontal);

   CComPtr<ISurfaceTemplate> template1000;
   surface->CreateSurfaceTemplate(CComVariant(1000), &template1000);
   template1000->UpdateSegmentParameters(0, 20.0, -0.06, tsHorizontal);
   template1000->UpdateSegmentParameters(1, 5.0, -0.06, tsHorizontal);
   template1000->UpdateSegmentParameters(2, 5.0, -0.06, tsHorizontal);
   template1000->UpdateSegmentParameters(3, 20.0, -0.06, tsHorizontal);

   CComPtr<ISurfaceTemplate> template1300;
   surface->CreateSurfaceTemplate(CComVariant(1300), &template1300);
   template1300->UpdateSegmentParameters(0, 20.0, 0.04, tsHorizontal);
   template1300->UpdateSegmentParameters(1, 5.0, 0.04, tsHorizontal);
   template1300->UpdateSegmentParameters(2, 5.0, -0.08, tsHorizontal);
   template1300->UpdateSegmentParameters(3, 20.0, -0.08, tsHorizontal);

   CComPtr<ISurfaceTemplate> template1600;
   surface->CreateSurfaceTemplate(CComVariant(1600), &template1600);
   template1600->UpdateSegmentParameters(0, 20.0, 0.04, tsHorizontal);
   template1600->UpdateSegmentParameters(1, 5.0, 0.04, tsHorizontal);
   template1600->UpdateSegmentParameters(2, 5.0, -0.08, tsHorizontal);
   template1600->UpdateSegmentParameters(3, 20.0, -0.08, tsHorizontal);

   Float64 Grades[] = { 5.0000, 5.0000, 4.2000, 2.0667, -0.0667, -2.2000, 21.8333, -22.5000 };
   TestGrade(profile,Grades);

   Float64 CrownSlopes1[][2] = { { 0.0200, -0.0200}, { 0.0200, -0.0200}, { 0.0040, -0.0280}, { -0.0387, -0.0493}, { -0.0333,-0.0653}, { 0.0200, -0.0760}, { 0.0400, -0.0800}, { 0.0400, -0.0800} };
   TestCrownSlopes(profile,surfaceID,2,CrownSlopes1);

   Float64 ElevA[] = { 71.900, 79.900, 87.860, 93.407, 95.033, 92.740, 87.3417, 75.250 };
   Float64 ElevB[] = { 72.100, 80.100, 87.900, 93.020, 94.700, 92.940, 87.7417, 75.650 };
   Float64 ElevC[] = { 72.040, 80.040, 87.816, 92.872, 94.504, 92.712, 87.5017, 75.410 };
   Float64 ElevD[] = { 72.000, 80.000, 87.760, 92.773, 94.373, 92.560, 87.3417, 75.250 };
   Float64 ElevE[] = { 71.900, 79.900, 87.620, 92.527, 94.047, 92.180, 86.9417, 74.850 };
   TestElevation(profile, surfaceID,-15,ElevA);
   TestElevation(profile, surfaceID, -5,ElevB);
   TestElevation(profile, surfaceID, -2,ElevC);
   TestElevation(profile, surfaceID,  0,ElevD);
   TestElevation(profile, surfaceID,  5,ElevE);

   // shift the crown point offset to +5
   surface->put_AlignmentPoint(1);
   surface->put_ProfileGradePoint(1);

   Float64 ElevF[] = { 71.900, 79.900, 87.740, 92.967, 94.540, 92.460, 87.1417, 75.050 };
   Float64 ElevG[] = { 72.000, 80.000, 87.760, 92.773, 94.373, 92.560, 87.3417, 75.250 };
   Float64 ElevH[] = { 72.040, 80.040, 87.768, 92.696, 94.307, 92.600, 87.4217, 75.330 };
   Float64 ElevI[] = { 72.100, 80.100, 87.780, 92.580, 94.207, 92.660, 87.5417, 75.450 };
   Float64 ElevJ[] = { 71.900, 79.900, 87.500, 92.087, 93.553, 91.900, 86.7417, 74.650 };
   TestElevation(profile, surfaceID, -5,ElevF);
   TestElevation(profile, surfaceID,  0,ElevG);
   TestElevation(profile, surfaceID,  2,ElevH);
   TestElevation(profile, surfaceID,  5,ElevI);
   TestElevation(profile, surfaceID, 15,ElevJ);

   // shift the crown point offset back to -5 and reverse all of the crown slopes
   surface->put_AlignmentPoint(3);
   surface->put_ProfileGradePoint(3);

   IndexType nTemplates;
   surface->GetSurfaceTemplateCount(&nTemplates);
   for (IndexType idx = 0; idx < nTemplates; idx++)
   {
      CComPtr<ISurfaceTemplate> surface_template;
      surface->GetSurfaceTemplate(idx, &surface_template);
      IndexType nSegments;
      surface_template->get_Count(&nSegments);
      for (IndexType idx = 0; idx < nSegments; idx++)
      {
         Float64 width, slope;
         TemplateSlopeType slopeType;
         surface_template->GetSegmentParameters(idx, &width, &slope, &slopeType);

         slope *= -1;
         surface_template->UpdateSegmentParameters(idx, width, slope, slopeType);
      }
   }

   Float64 CrownSlopes2[][2] = { { -0.0200,  0.0200}, { -0.0200,  0.0200}, { -0.0040,  0.0280}, { 0.0387,  0.0493}, { 0.0333, 0.0653}, { -0.0200,  0.0760}, { -0.0400,  0.0800}, { -0.0400,  0.0800} };
   TestCrownSlopes(profile,surfaceID,2,CrownSlopes2);

   Float64 ElevK[] = { 72.100, 80.100, 87.660, 92.140, 93.713, 92.380, 87.3417, 75.250 };
   Float64 ElevL[] = { 71.900, 79.900, 87.620, 92.527, 94.047, 92.180, 86.9417, 74.850 };
   Float64 ElevM[] = { 71.960, 79.960, 87.704, 92.675, 94.243, 92.408, 87.1817, 75.090 };
   Float64 ElevN[] = { 72.000, 80.000, 87.760, 92.773, 94.373, 92.560, 87.3417, 75.250 };
   Float64 ElevO[] = { 72.100, 80.100, 87.900, 93.020, 94.700, 92.940, 87.7417, 75.650 };
   TestElevation(profile, surfaceID,-15,ElevK);
   TestElevation(profile, surfaceID, -5,ElevL);
   TestElevation(profile, surfaceID, -2,ElevM);
   TestElevation(profile, surfaceID,  0,ElevN);
   TestElevation(profile, surfaceID,  5,ElevO);

   // shift the crown point offset to +5, keep the slopes the same
   surface->put_AlignmentPoint(1);
   surface->put_ProfileGradePoint(1);
   
   Float64 ElevP[] = { 72.100, 80.100, 87.780, 92.580, 94.207, 92.660, 87.5417, 75.450 };
   Float64 ElevQ[] = { 72.000, 80.000, 87.760, 92.773, 94.373, 92.560, 87.3417, 75.250 };
   Float64 ElevR[] = { 71.960, 79.960, 87.752, 92.851, 94.440, 92.520, 87.2617, 75.170 };
   Float64 ElevS[] = { 71.900, 79.900, 87.740, 92.967, 94.540, 92.460, 87.1417, 75.050 };
   Float64 ElevT[] = { 72.100, 80.100, 88.020, 93.460, 95.193, 93.220, 87.9417, 75.850 };
   TestElevation(profile, surfaceID, -5,ElevP);
   TestElevation(profile, surfaceID,  0,ElevQ);
   TestElevation(profile, surfaceID,  2,ElevR);
   TestElevation(profile, surfaceID,  5,ElevS);
   TestElevation(profile, surfaceID, 15,ElevT);
}

void CTestProfile::Test5()
{
   CComPtr<IAlignment> alignment;
   alignment.CoCreateInstance(CLSID_Alignment);

   CComPtr<IProfile> profile;
   TRY_TEST(profile.CoCreateInstance(CLSID_Profile), S_OK);

   alignment->AddProfile(0, profile);


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
   CComPtr<IProfilePoint> start;
   start.CoCreateInstance(CLSID_ProfilePoint);
   start->Move(CComVariant(610), 80.5);

   CComPtr<IProfilePoint> p1;
   p1.CoCreateInstance(CLSID_ProfilePoint);
   p1->Move(CComVariant(650), 82.5);

   CComPtr<IProfilePoint> pbg;
   pbg.CoCreateInstance(CLSID_ProfilePoint);
   pbg->Move(CComVariant(700), 85.0);

   CComPtr<IProfilePoint> pvi;
   pvi.CoCreateInstance(CLSID_ProfilePoint);
   pvi->Move(CComVariant(1000), 100);

   CComPtr<IProfilePoint> pfg;
   pfg.CoCreateInstance(CLSID_ProfilePoint);
   pfg->Move(CComVariant(1300), 91);

   CComPtr<IProfilePoint> end;
   end.CoCreateInstance(CLSID_ProfilePoint);
   end->Move(CComVariant(1400), 88);

   CComPtr<IProfileSegment> start_segment1;
   start_segment1.CoCreateInstance(CLSID_ProfileSegment);
   start_segment1->Move(start, p1);
   CComQIPtr<IProfileElement> element(start_segment1);
   profile->AddProfileElement(element);

   CComPtr<IProfileSegment> start_segment2;
   start_segment2.CoCreateInstance(CLSID_ProfileSegment);
   start_segment2->Move(p1, pbg);
   element.Release();
   start_segment2.QueryInterface(&element);
   profile->AddProfileElement(element);

   CComPtr<IVerticalCurve> vc;
   vc.CoCreateInstance(CLSID_VerticalCurve);
   vc->Init(pbg, pvi, pfg, 300, 300);
   element.Release();
   vc.QueryInterface(&element);
   profile->AddProfileElement(element);

   CComPtr<IProfileSegment> end_segment;
   end_segment.CoCreateInstance(CLSID_ProfileSegment);
   end_segment->Move(pfg, end);
   element.Release();
   end_segment.QueryInterface(&element);
   profile->AddProfileElement(element);

   // create roadway surface model
   IDType surfaceID = 0;
   CComPtr<ISurface> surface;
   surface.CoCreateInstance(CLSID_Surface);
   profile->AddSurface(surfaceID, surface); // this may need to go after the surface is built with by-value semantics

   surface->put_SurfaceTemplateSegmentCount(4);
   surface->put_AlignmentPoint(3);
   surface->put_ProfileGradePoint(3);

   CComPtr<ISurfaceTemplate> template430;
   surface->CreateSurfaceTemplate(CComVariant(430), &template430);
   template430->UpdateSegmentParameters(0, 20.0, 0.02, tsHorizontal);
   template430->UpdateSegmentParameters(1, 5.0, 0.02, tsHorizontal);
   template430->UpdateSegmentParameters(2, 5.0, -0.02, tsHorizontal);
   template430->UpdateSegmentParameters(3, 20.0, -0.02, tsHorizontal);

   CComPtr<ISurfaceTemplate> template700;
   surface->CreateSurfaceTemplate(CComVariant(700), &template700);
   template700->UpdateSegmentParameters(0, 20.0, 0.02, tsHorizontal);
   template700->UpdateSegmentParameters(1, 5.0, 0.02, tsHorizontal);
   template700->UpdateSegmentParameters(2, 5.0, -0.02, tsHorizontal);
   template700->UpdateSegmentParameters(3, 20.0, -0.02, tsHorizontal);

   CComPtr<ISurfaceTemplate> template1000;
   surface->CreateSurfaceTemplate(CComVariant(1000), &template1000);
   template1000->UpdateSegmentParameters(0, 20.0, -0.06, tsHorizontal);
   template1000->UpdateSegmentParameters(1, 5.0, -0.06, tsHorizontal);
   template1000->UpdateSegmentParameters(2, 5.0, -0.06, tsHorizontal);
   template1000->UpdateSegmentParameters(3, 20.0, -0.06, tsHorizontal);

   CComPtr<ISurfaceTemplate> template1300;
   surface->CreateSurfaceTemplate(CComVariant(1300), &template1300);
   template1300->UpdateSegmentParameters(0, 20.0, 0.04, tsHorizontal);
   template1300->UpdateSegmentParameters(1, 5.0, 0.04, tsHorizontal);
   template1300->UpdateSegmentParameters(2, 5.0, -0.08, tsHorizontal);
   template1300->UpdateSegmentParameters(3, 20.0, -0.08, tsHorizontal);

   CComPtr<ISurfaceTemplate> template1600;
   surface->CreateSurfaceTemplate(CComVariant(1600), &template1600);
   template1600->UpdateSegmentParameters(0, 20.0, 0.04, tsHorizontal);
   template1600->UpdateSegmentParameters(1, 5.0, 0.04, tsHorizontal);
   template1600->UpdateSegmentParameters(2, 5.0, -0.08, tsHorizontal);
   template1600->UpdateSegmentParameters(3, 20.0, -0.08, tsHorizontal);

   Float64 Grades[] = { 5.0000, 5.0000, 4.2000, 2.0667, -0.0667, -2.2000, -3.0000, -3.0000 };
   TestGrade(profile,Grades);

   Float64 CrownSlopes1[][2] = { {  0.0200, -0.0200}, {  0.0200, -0.0200}, {  0.0040, -0.0280}, { -0.0387, -0.0493}, { -0.0333,-0.0653}, { 0.0200, -0.0760}, { 0.0400, -0.0800}, { 0.0400, -0.0800} };
   TestCrownSlopes(profile,surfaceID,2,CrownSlopes1);

   Float64 ElevA[] = { 71.900, 79.900, 87.860, 93.407, 95.033, 92.740, 88.000, 83.200 };
   Float64 ElevB[] = { 72.100, 80.100, 87.900, 93.020, 94.700, 92.940, 88.400, 83.600 };
   Float64 ElevC[] = { 72.040, 80.040, 87.816, 92.872, 94.504, 92.712, 88.160, 83.360 };
   Float64 ElevD[] = { 72.000, 80.000, 87.760, 92.773, 94.373, 92.560, 88.000, 83.200 };
   Float64 ElevE[] = { 71.900, 79.900, 87.620, 92.527, 94.047, 92.180, 87.600, 82.800 };
   TestElevation(profile, surfaceID,-15,ElevA);
   TestElevation(profile, surfaceID, -5,ElevB);
   TestElevation(profile, surfaceID, -2,ElevC);
   TestElevation(profile, surfaceID,  0,ElevD);
   TestElevation(profile, surfaceID,  5,ElevE);

   // shift the crown point offset to +5
   surface->put_AlignmentPoint(1);
   surface->put_ProfileGradePoint(1);

   Float64 ElevF[] = { 71.900, 79.900, 87.740, 92.967, 94.540, 92.460, 87.800, 83.000 };
   Float64 ElevG[] = { 72.000, 80.000, 87.760, 92.773, 94.373, 92.560, 88.000, 83.200 };
   Float64 ElevH[] = { 72.040, 80.040, 87.768, 92.696, 94.307, 92.600, 88.080, 83.280 };
   Float64 ElevI[] = { 72.100, 80.100, 87.780, 92.580, 94.207, 92.660, 88.200, 83.400 };
   Float64 ElevJ[] = { 71.900, 79.900, 87.500, 92.087, 93.553, 91.900, 87.400, 82.600 };
   TestElevation(profile, surfaceID, -5,ElevF);
   TestElevation(profile, surfaceID,  0,ElevG);
   TestElevation(profile, surfaceID,  2,ElevH);
   TestElevation(profile, surfaceID,  5,ElevI);
   TestElevation(profile, surfaceID, 15,ElevJ);

   // shift the crown point offset back to -5 and reverse all of the crown slopes
   surface->put_AlignmentPoint(3);
   surface->put_ProfileGradePoint(3);

   IndexType nTemplates;
   surface->GetSurfaceTemplateCount(&nTemplates);
   for (IndexType idx = 0; idx < nTemplates; idx++)
   {
      CComPtr<ISurfaceTemplate> surface_template;
      surface->GetSurfaceTemplate(idx, &surface_template);
      IndexType nSegments;
      surface_template->get_Count(&nSegments);
      for (IndexType idx = 0; idx < nSegments; idx++)
      {
         Float64 width, slope;
         TemplateSlopeType slopeType;
         surface_template->GetSegmentParameters(idx, &width, &slope, &slopeType);

         slope *= -1;
         surface_template->UpdateSegmentParameters(idx, width, slope, slopeType);
      }
   }

   Float64 CrownSlopes2[][2] = { { -0.0200,  0.0200}, { -0.0200,  0.0200}, { -0.0040,  0.0280}, { 0.0387,  0.0493}, { 0.0333, 0.0653}, { -0.0200,  0.0760}, { -0.0400,  0.0800}, { -0.0400,  0.0800} };
   TestCrownSlopes(profile,surfaceID,2,CrownSlopes2);

   Float64 ElevK[] = { 72.100, 80.100, 87.660, 92.140, 93.713, 92.380, 88.000, 83.200 };
   Float64 ElevL[] = { 71.900, 79.900, 87.620, 92.527, 94.047, 92.180, 87.600, 82.800 };
   Float64 ElevM[] = { 71.960, 79.960, 87.704, 92.675, 94.243, 92.408, 87.840, 83.040 };
   Float64 ElevN[] = { 72.000, 80.000, 87.760, 92.773, 94.373, 92.560, 88.000, 83.200 };
   Float64 ElevO[] = { 72.100, 80.100, 87.900, 93.020, 94.700, 92.940, 88.400, 83.600 };
   TestElevation(profile, surfaceID,-15,ElevK);
   TestElevation(profile, surfaceID, -5,ElevL);
   TestElevation(profile, surfaceID, -2,ElevM);
   TestElevation(profile, surfaceID,  0,ElevN);
   TestElevation(profile, surfaceID,  5,ElevO);

   // shift the crown point offset to +5, keep the slopes the same
   surface->put_AlignmentPoint(1);
   surface->put_ProfileGradePoint(1);
   
   Float64 ElevP[] = { 72.100, 80.100, 87.780, 92.580, 94.207, 92.660, 88.200, 83.400 };
   Float64 ElevQ[] = { 72.000, 80.000, 87.760, 92.773, 94.373, 92.560, 88.000, 83.200 };
   Float64 ElevR[] = { 71.960, 79.960, 87.752, 92.851, 94.440, 92.520, 87.920, 83.120 };
   Float64 ElevS[] = { 71.900, 79.900, 87.740, 92.967, 94.540, 92.460, 87.800, 83.000 };
   Float64 ElevT[] = { 72.100, 80.100, 88.020, 93.460, 95.193, 93.220, 88.600, 83.800 };
   TestElevation(profile, surfaceID, -5,ElevP);
   TestElevation(profile, surfaceID,  0,ElevQ);
   TestElevation(profile, surfaceID,  2,ElevR);
   TestElevation(profile, surfaceID,  5,ElevS);
   TestElevation(profile, surfaceID, 15,ElevT);
}

void CTestProfile::Test6()
{
   CComPtr<IAlignment> alignment;
   alignment.CoCreateInstance(CLSID_Alignment);

   CComPtr<IProfile> profile;
   TRY_TEST(profile.CoCreateInstance(CLSID_Profile), S_OK);

   alignment->AddProfile(0, profile);


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
   CComPtr<IProfilePoint> start;
   start.CoCreateInstance(CLSID_ProfilePoint);
   start->Move(CComVariant(610), 80.5);

   CComPtr<IProfilePoint> p1;
   p1.CoCreateInstance(CLSID_ProfilePoint);
   p1->Move(CComVariant(650), 82.5);

   CComPtr<IProfilePoint> pbg;
   pbg.CoCreateInstance(CLSID_ProfilePoint);
   pbg->Move(CComVariant(700), 85.0);

   CComPtr<IProfilePoint> pvi;
   pvi.CoCreateInstance(CLSID_ProfilePoint);
   pvi->Move(CComVariant(1000), 100);

   CComPtr<IProfilePoint> pfg;
   pfg.CoCreateInstance(CLSID_ProfilePoint);
   pfg->Move(CComVariant(1300), 91);

   CComPtr<IProfilePoint> p2;
   p2.CoCreateInstance(CLSID_ProfilePoint);
   p2->Move(CComVariant(1400), 88.0);

   CComPtr<IProfilePoint> end;
   end.CoCreateInstance(CLSID_ProfilePoint);
   end->Move(CComVariant(1450), 86.5);

   CComPtr<IProfileSegment> start_segment1;
   start_segment1.CoCreateInstance(CLSID_ProfileSegment);
   start_segment1->Move(start, p1);
   CComQIPtr<IProfileElement> element(start_segment1);
   profile->AddProfileElement(element);

   CComPtr<IProfileSegment> start_segment2;
   start_segment2.CoCreateInstance(CLSID_ProfileSegment);
   start_segment2->Move(p1, pbg);
   element.Release();
   start_segment2.QueryInterface(&element);
   profile->AddProfileElement(element);

   CComPtr<IVerticalCurve> vc;
   vc.CoCreateInstance(CLSID_VerticalCurve);
   vc->Init(pbg, pvi, pfg, 300, 300);
   element.Release();
   vc.QueryInterface(&element);
   profile->AddProfileElement(element);

   CComPtr<IProfileSegment> segment2;
   segment2.CoCreateInstance(CLSID_ProfileSegment);
   segment2->Move(pfg, p2);
   element.Release();
   segment2.QueryInterface(&element);
   profile->AddProfileElement(element);

   CComPtr<IProfileSegment> end_segment;
   end_segment.CoCreateInstance(CLSID_ProfileSegment);
   end_segment->Move(p2, end);
   element.Release();
   end_segment.QueryInterface(&element);
   profile->AddProfileElement(element);

   // create roadway surface model
   IDType surfaceID = 0;
   CComPtr<ISurface> surface;
   surface.CoCreateInstance(CLSID_Surface);
   profile->AddSurface(surfaceID, surface); // this may need to go after the surface is built with by-value semantics

   surface->put_SurfaceTemplateSegmentCount(4);
   surface->put_AlignmentPoint(3);
   surface->put_ProfileGradePoint(3);

   CComPtr<ISurfaceTemplate> template430;
   surface->CreateSurfaceTemplate(CComVariant(430), &template430);
   template430->UpdateSegmentParameters(0, 20.0, 0.02, tsHorizontal);
   template430->UpdateSegmentParameters(1, 5.0, 0.02, tsHorizontal);
   template430->UpdateSegmentParameters(2, 5.0, -0.02, tsHorizontal);
   template430->UpdateSegmentParameters(3, 20.0, -0.02, tsHorizontal);

   CComPtr<ISurfaceTemplate> template700;
   surface->CreateSurfaceTemplate(CComVariant(700), &template700);
   template700->UpdateSegmentParameters(0, 20.0, 0.02, tsHorizontal);
   template700->UpdateSegmentParameters(1, 5.0, 0.02, tsHorizontal);
   template700->UpdateSegmentParameters(2, 5.0, -0.02, tsHorizontal);
   template700->UpdateSegmentParameters(3, 20.0, -0.02, tsHorizontal);

   CComPtr<ISurfaceTemplate> template1000;
   surface->CreateSurfaceTemplate(CComVariant(1000), &template1000);
   template1000->UpdateSegmentParameters(0, 20.0, -0.06, tsHorizontal);
   template1000->UpdateSegmentParameters(1, 5.0, -0.06, tsHorizontal);
   template1000->UpdateSegmentParameters(2, 5.0, -0.06, tsHorizontal);
   template1000->UpdateSegmentParameters(3, 20.0, -0.06, tsHorizontal);

   CComPtr<ISurfaceTemplate> template1300;
   surface->CreateSurfaceTemplate(CComVariant(1300), &template1300);
   template1300->UpdateSegmentParameters(0, 20.0, 0.04, tsHorizontal);
   template1300->UpdateSegmentParameters(1, 5.0, 0.04, tsHorizontal);
   template1300->UpdateSegmentParameters(2, 5.0, -0.08, tsHorizontal);
   template1300->UpdateSegmentParameters(3, 20.0, -0.08, tsHorizontal);

   CComPtr<ISurfaceTemplate> template1600;
   surface->CreateSurfaceTemplate(CComVariant(1600), &template1600);
   template1600->UpdateSegmentParameters(0, 20.0, 0.04, tsHorizontal);
   template1600->UpdateSegmentParameters(1, 5.0, 0.04, tsHorizontal);
   template1600->UpdateSegmentParameters(2, 5.0, -0.08, tsHorizontal);
   template1600->UpdateSegmentParameters(3, 20.0, -0.08, tsHorizontal);

   Float64 Grades[] = { 5.0000, 5.0000, 4.2000, 2.0667, -0.0667, -2.2000, -3.0000, -3.0000 };
   TestGrade(profile,Grades);

   Float64 CrownSlopes1[][2] = { { 0.0200, -0.0200}, { 0.0200, -0.0200}, { 0.0040, -0.0280}, { -0.0387, -0.0493}, { -0.0333,-0.0653}, { 0.0200, -0.0760}, { 0.0400, -0.0800}, { 0.0400, -0.0800} };
   TestCrownSlopes(profile,surfaceID,2,CrownSlopes1);

   Float64 ElevA[] = { 71.900, 79.900, 87.860, 93.407, 95.033, 92.740, 88.000, 83.200 };
   Float64 ElevB[] = { 72.100, 80.100, 87.900, 93.020, 94.700, 92.940, 88.400, 83.600 };
   Float64 ElevC[] = { 72.040, 80.040, 87.816, 92.872, 94.504, 92.712, 88.160, 83.360 };
   Float64 ElevD[] = { 72.000, 80.000, 87.760, 92.773, 94.373, 92.560, 88.000, 83.200 };
   Float64 ElevE[] = { 71.900, 79.900, 87.620, 92.527, 94.047, 92.180, 87.600, 82.800 };
   TestElevation(profile, surfaceID,-15,ElevA);
   TestElevation(profile, surfaceID, -5,ElevB);
   TestElevation(profile, surfaceID, -2,ElevC);
   TestElevation(profile, surfaceID,  0,ElevD);
   TestElevation(profile, surfaceID,  5,ElevE);

   // shift the crown point offset to +5
   surface->put_AlignmentPoint(1);
   surface->put_ProfileGradePoint(1);

   Float64 ElevF[] = { 71.900, 79.900, 87.740, 92.967, 94.540, 92.460, 87.800, 83.000 };
   Float64 ElevG[] = { 72.000, 80.000, 87.760, 92.773, 94.373, 92.560, 88.000, 83.200 };
   Float64 ElevH[] = { 72.040, 80.040, 87.768, 92.696, 94.307, 92.600, 88.080, 83.280 };
   Float64 ElevI[] = { 72.100, 80.100, 87.780, 92.580, 94.207, 92.660, 88.200, 83.400 };
   Float64 ElevJ[] = { 71.900, 79.900, 87.500, 92.087, 93.553, 91.900, 87.400, 82.600 };
   TestElevation(profile, surfaceID, -5,ElevF);
   TestElevation(profile, surfaceID,  0,ElevG);
   TestElevation(profile, surfaceID,  2,ElevH);
   TestElevation(profile, surfaceID,  5,ElevI);
   TestElevation(profile, surfaceID, 15,ElevJ);

   // shift the crown point offset back to -5 and reverse all of the crown slopes
   surface->put_AlignmentPoint(3);
   surface->put_ProfileGradePoint(3);

   IndexType nTemplates;
   surface->GetSurfaceTemplateCount(&nTemplates);
   for (IndexType idx = 0; idx < nTemplates; idx++)
   {
      CComPtr<ISurfaceTemplate> surface_template;
      surface->GetSurfaceTemplate(idx, &surface_template);
      IndexType nSegments;
      surface_template->get_Count(&nSegments);
      for (IndexType idx = 0; idx < nSegments; idx++)
      {
         Float64 width, slope;
         TemplateSlopeType slopeType;
         surface_template->GetSegmentParameters(idx, &width, &slope, &slopeType);

         slope *= -1;
         surface_template->UpdateSegmentParameters(idx, width, slope, slopeType);
      }
   }

   Float64 CrownSlopes2[][2] = { { -0.0200,  0.0200}, { -0.0200,  0.0200}, { -0.0040,  0.0280}, { 0.0387,  0.0493}, { 0.0333, 0.0653}, { -0.0200,  0.0760}, { -0.0400,  0.0800}, { -0.0400,  0.0800} };
   TestCrownSlopes(profile,surfaceID,2,CrownSlopes2);

   Float64 ElevK[] = { 72.100, 80.100, 87.660, 92.140, 93.713, 92.380, 88.000, 83.200 };
   Float64 ElevL[] = { 71.900, 79.900, 87.620, 92.527, 94.047, 92.180, 87.600, 82.800 };
   Float64 ElevM[] = { 71.960, 79.960, 87.704, 92.675, 94.243, 92.408, 87.840, 83.040 };
   Float64 ElevN[] = { 72.000, 80.000, 87.760, 92.773, 94.373, 92.560, 88.000, 83.200 };
   Float64 ElevO[] = { 72.100, 80.100, 87.900, 93.020, 94.700, 92.940, 88.400, 83.600 };
   TestElevation(profile, surfaceID,-15,ElevK);
   TestElevation(profile, surfaceID, -5,ElevL);
   TestElevation(profile, surfaceID, -2,ElevM);
   TestElevation(profile, surfaceID,  0,ElevN);
   TestElevation(profile, surfaceID,  5,ElevO);

   // shift the crown point offset to +5, keep the slopes the same
   surface->put_AlignmentPoint(1);
   surface->put_ProfileGradePoint(1);
   
   Float64 ElevP[] = { 72.100, 80.100, 87.780, 92.580, 94.207, 92.660, 88.200, 83.400 };
   Float64 ElevQ[] = { 72.000, 80.000, 87.760, 92.773, 94.373, 92.560, 88.000, 83.200 };
   Float64 ElevR[] = { 71.960, 79.960, 87.752, 92.851, 94.440, 92.520, 87.920, 83.120 };
   Float64 ElevS[] = { 71.900, 79.900, 87.740, 92.967, 94.540, 92.460, 87.800, 83.000 };
   Float64 ElevT[] = { 72.100, 80.100, 88.020, 93.460, 95.193, 93.220, 88.600, 83.800 };
   TestElevation(profile, surfaceID, -5,ElevP);
   TestElevation(profile, surfaceID,  0,ElevQ);
   TestElevation(profile, surfaceID,  2,ElevR);
   TestElevation(profile, surfaceID,  5,ElevS);
   TestElevation(profile, surfaceID, 15,ElevT);
}

void CTestProfile::Test7()
{
   // Test a profile with no elements
   CComPtr<IAlignment> alignment;
   alignment.CoCreateInstance(CLSID_Alignment);

   CComPtr<IProfile> profile;
   TRY_TEST(profile.CoCreateInstance(CLSID_Profile), S_OK);

   alignment->AddProfile(0, profile);


   IDType surfaceID = 0;

   Float64 val;
   profile->Elevation(surfaceID,CComVariant(100.00),0.0,&val);
   TRY_TEST(IsZero(val),true);

   profile->Grade(CComVariant(100.00), &val);
   TRY_TEST(IsZero(val),true);

   profile->CrossSlope(surfaceID,CComVariant(100.00) ,-10.0,&val);
   TRY_TEST(IsZero(val),true);

   profile->CrossSlope(surfaceID,CComVariant(100.00), 10.0,&val);
   TRY_TEST(IsZero(val),true);

   // add a surface and re-test the slopes
   // create roadway surface model
   CComPtr<ISurface> surface;
   surface.CoCreateInstance(CLSID_Surface);
   profile->AddSurface(surfaceID, surface);


   surface->put_SurfaceTemplateSegmentCount(2);
   surface->put_AlignmentPoint(1);
   surface->put_ProfileGradePoint(1);

   CComPtr<ISurfaceTemplate> template0;
   surface->CreateSurfaceTemplate(CComVariant(0), &template0);
   template0->UpdateSegmentParameters(0, 20.0, 0.02, tsHorizontal);
   template0->UpdateSegmentParameters(1, 20.0, -0.02, tsHorizontal);

   CComPtr<ISurfaceTemplate> template50;
   surface->CreateSurfaceTemplate(CComVariant(50), &template50);
   template50->UpdateSegmentParameters(0, 20.0, 0.02, tsHorizontal);
   template50->UpdateSegmentParameters(1, 20.0, -0.02, tsHorizontal);

   CComPtr<ISurfaceTemplate> template100;
   surface->CreateSurfaceTemplate(CComVariant(100), &template100);
   template100->UpdateSegmentParameters(0, 20.0, 0.04, tsHorizontal);
   template100->UpdateSegmentParameters(1, 20.0, -0.04, tsHorizontal);

   CComPtr<ISurfaceTemplate> template200;
   surface->CreateSurfaceTemplate(CComVariant(200), &template200);
   template200->UpdateSegmentParameters(0, 20.0, 0.04, tsHorizontal);
   template200->UpdateSegmentParameters(1, 20.0, -0.04, tsHorizontal);

   profile->CrossSlope(surfaceID, CComVariant(0.00), -10.0, &val);
   TRY_TEST(IsEqual(val, 0.02), true);

   profile->CrossSlope(surfaceID, CComVariant(0.00), 10.0, &val);
   TRY_TEST(IsEqual(val, -0.02), true);

   profile->CrossSlope(surfaceID, CComVariant(50.00), -10.0, &val);
   TRY_TEST(IsEqual(val, 0.02), true);

   profile->CrossSlope(surfaceID, CComVariant(50.00), 10.0, &val);
   TRY_TEST(IsEqual(val, -0.02), true);

   profile->CrossSlope(surfaceID, CComVariant(75.00), -10.0, &val);
   TRY_TEST(IsEqual(val, 0.03), true);

   profile->CrossSlope(surfaceID, CComVariant(75.00), 10.0, &val);
   TRY_TEST(IsEqual(val, -0.03), true);

   profile->CrossSlope(surfaceID, CComVariant(100.00), -10.0, &val);
   TRY_TEST(IsEqual(val, 0.04), true);

   profile->CrossSlope(surfaceID, CComVariant(100.00), 10.0, &val);
   TRY_TEST(IsEqual(val, -0.04), true);

   profile->CrossSlope(surfaceID, CComVariant(150.00), -10.0, &val);
   TRY_TEST(IsEqual(val, 0.04), true);

   profile->CrossSlope(surfaceID, CComVariant(150.00), 10.0, &val);
   TRY_TEST(IsEqual(val, -0.04), true);
}

void CTestProfile::Test8()
{
   // Test a profile with one point element
   //
   // One point profiles are not allowed in the C++ version
   // This test is originally from the COM version
   // Use a flat profile segment to simulate what the old COM version did
   CComPtr<IAlignment> alignment;
   alignment.CoCreateInstance(CLSID_Alignment);

   CComPtr<IProfile> profile;
   TRY_TEST(profile.CoCreateInstance(CLSID_Profile), S_OK);

   alignment->AddProfile(0, profile);

   CComPtr<IProfilePoint> start;
   start.CoCreateInstance(CLSID_ProfilePoint);
   start->put_Station(CComVariant(100.0));
   start->put_Elevation(100.0);

   CComPtr<IProfilePoint> end;
   end.CoCreateInstance(CLSID_ProfilePoint);
   end->put_Station(CComVariant(200.0));
   end->put_Elevation(100.0);

   CComPtr<IProfileSegment> segment;
   segment.CoCreateInstance(CLSID_ProfileSegment);
   segment->Move(start, end);

   CComQIPtr<IProfileElement> element(segment);
   TRY_TEST(profile->AddProfileElement(element), S_OK);

   Float64 val;
   profile->Elevation(INVALID_ID, CComVariant(100.00), 0.0, &val);
   TRY_TEST(IsEqual(val, 100.0), true);

   profile->Grade(CComVariant(100.00), &val);
   TRY_TEST(IsZero(val), true);

   profile->CrossSlope(INVALID_ID, CComVariant(100.00), -10.0, &val);
   TRY_TEST(IsZero(val), true);

   profile->CrossSlope(INVALID_ID, CComVariant(100.00), 10.0, &val);
   TRY_TEST(IsZero(val), true);

   // add a surface and re-test the slopes
   // create roadway surface model
   IDType surfaceID = 0;

   CComPtr<ISurface> surface;
   surface.CoCreateInstance(CLSID_Surface);
   profile->AddSurface(surfaceID, surface);

   surface->put_SurfaceTemplateSegmentCount(2);
   surface->put_AlignmentPoint(1);
   surface->put_ProfileGradePoint(1);

   CComPtr<ISurfaceTemplate> template0;
   surface->CreateSurfaceTemplate(CComVariant(0), &template0);
   template0->UpdateSegmentParameters(0, 20.0, 0.02, tsHorizontal);
   template0->UpdateSegmentParameters(1, 20.0, -0.02, tsHorizontal);

   CComPtr<ISurfaceTemplate> template50;
   surface->CreateSurfaceTemplate(CComVariant(50), &template50);
   template50->UpdateSegmentParameters(0, 20.0, 0.02, tsHorizontal);
   template50->UpdateSegmentParameters(1, 20.0, -0.02, tsHorizontal);

   CComPtr<ISurfaceTemplate> template100;
   surface->CreateSurfaceTemplate(CComVariant(100), &template100);
   template100->UpdateSegmentParameters(0, 20.0, 0.04, tsHorizontal);
   template100->UpdateSegmentParameters(1, 20.0, -0.04, tsHorizontal);

   CComPtr<ISurfaceTemplate> template200;
   surface->CreateSurfaceTemplate(CComVariant(200), &template200);
   template200->UpdateSegmentParameters(0, 20.0, 0.04, tsHorizontal);
   template200->UpdateSegmentParameters(1, 20.0, -0.04, tsHorizontal);

   profile->CrossSlope(surfaceID, CComVariant(0.00), -10.0, &val);
   TRY_TEST(IsEqual(val, 0.02), true);

   profile->CrossSlope(surfaceID, CComVariant(0.00), 10.0, &val);
   TRY_TEST(IsEqual(val, -0.02), true);

   profile->CrossSlope(surfaceID, CComVariant(50.00), -10.0, &val);
   TRY_TEST(IsEqual(val, 0.02), true);

   profile->CrossSlope(surfaceID, CComVariant(50.00), 10.0, &val);
   TRY_TEST(IsEqual(val, -0.02), true);

   profile->CrossSlope(surfaceID, CComVariant(75.00), -10.0, &val);
   TRY_TEST(IsEqual(val, 0.03), true);

   profile->CrossSlope(surfaceID, CComVariant(75.00), 10.0, &val);
   TRY_TEST(IsEqual(val, -0.03), true);

   profile->CrossSlope(surfaceID, CComVariant(100.00), -10.0, &val);
   TRY_TEST(IsEqual(val, 0.04), true);

   profile->CrossSlope(surfaceID, CComVariant(100.00), 10.0, &val);
   TRY_TEST(IsEqual(val, -0.04), true);

   profile->CrossSlope(surfaceID, CComVariant(150.00), -10.0, &val);
   TRY_TEST(IsEqual(val, 0.04), true);

   profile->CrossSlope(surfaceID, CComVariant(150.00), 10.0, &val);
   TRY_TEST(IsEqual(val, -0.04), true);
}

void CTestProfile::Test9()
{
   // Test a profile with one vertical curve element
   CComPtr<IAlignment> alignment;
   alignment.CoCreateInstance(CLSID_Alignment);

   CComPtr<IProfile> profile;
   TRY_TEST(profile.CoCreateInstance(CLSID_Profile), S_OK);

   alignment->AddProfile(0, profile);


   CComPtr<IProfilePoint> pbg;
   pbg.CoCreateInstance(CLSID_ProfilePoint);
   pbg->Move(CComVariant(4850), 436.34);

   CComPtr<IProfilePoint> pvi;
   pvi.CoCreateInstance(CLSID_ProfilePoint);
   pvi->Move(CComVariant(5250), 432.34);

   CComPtr<IProfilePoint> pfg;
   pfg.CoCreateInstance(CLSID_ProfilePoint);
   pfg->Move(CComVariant(5650), 441.14);

   CComPtr<IVerticalCurve> vc;
   vc.CoCreateInstance(CLSID_VerticalCurve);
   vc->Init(pbg, pvi, pfg, 400, 400);
   CComQIPtr<IProfileElement> element(vc);
   profile->AddProfileElement(element);

   Float64 elev;
   profile->Elevation(INVALID_ID, CComVariant(4700), 0.00, &elev);   TRY_TEST(IsEqual(elev, 437.84), true);
   profile->Elevation(INVALID_ID, CComVariant(4850), 0.00, &elev);   TRY_TEST(IsEqual(elev, 436.34), true);
   profile->Elevation(INVALID_ID, CComVariant(4900), 0.00, &elev);   TRY_TEST(IsEqual(elev, 435.89), true);
   profile->Elevation(INVALID_ID, CComVariant(5000), 0.00, &elev);   TRY_TEST(IsEqual(elev, 435.29), true);
   profile->Elevation(INVALID_ID, CComVariant(5100), 0.00, &elev);   TRY_TEST(IsEqual(elev, 435.09), true);
   profile->Elevation(INVALID_ID, CComVariant(5200), 0.00, &elev);   TRY_TEST(IsEqual(elev, 435.29), true);
   profile->Elevation(INVALID_ID, CComVariant(5300), 0.00, &elev);   TRY_TEST(IsEqual(elev, 435.89), true);
   profile->Elevation(INVALID_ID, CComVariant(5400), 0.00, &elev);   TRY_TEST(IsEqual(elev, 436.89), true);
   profile->Elevation(INVALID_ID, CComVariant(5500), 0.00, &elev);   TRY_TEST(IsEqual(elev, 438.29), true);
   profile->Elevation(INVALID_ID, CComVariant(5600), 0.00, &elev);   TRY_TEST(IsEqual(elev, 440.09), true);
   profile->Elevation(INVALID_ID, CComVariant(5650), 0.00, &elev);   TRY_TEST(IsEqual(elev, 441.14), true);
   profile->Elevation(INVALID_ID, CComVariant(6000), 0.00,&elev);   TRY_TEST(IsEqual(elev,448.84),true);
}

void CTestProfile::Test10()
{
   // Test a profile with one vertical curve element
   CComPtr<IAlignment> alignment;
   alignment.CoCreateInstance(CLSID_Alignment);

   CComPtr<IProfile> profile;
   TRY_TEST(profile.CoCreateInstance(CLSID_Profile), S_OK);

   alignment->AddProfile(0, profile);


   CComPtr<IProfilePoint> pbg;
   pbg.CoCreateInstance(CLSID_ProfilePoint);
   pbg->Move(CComVariant(100), 100);

   CComPtr<IProfilePoint> pvi;
   pvi.CoCreateInstance(CLSID_ProfilePoint);
   pvi->Move(CComVariant(200), 90);

   CComPtr<IProfilePoint> pfg;
   pfg.CoCreateInstance(CLSID_ProfilePoint);
   pfg->Move(CComVariant(300), 100);

   CComPtr<IVerticalCurve> vc;
   vc.CoCreateInstance(CLSID_VerticalCurve);
   vc->Init(pbg, pvi, pfg, 50, 50);
   CComQIPtr<IProfileElement> element(vc);
   profile->AddProfileElement(element);

   // create roadway surface model
   CComPtr<ISurface> surface;
   surface.CoCreateInstance(CLSID_Surface);

   surface->put_AlignmentPoint(1);
   surface->put_ProfileGradePoint(1);
   IDType surfaceID = 0;

   profile->AddSurface(surfaceID, surface);

   surface->put_SurfaceTemplateSegmentCount(2);
   surface->put_AlignmentPoint(1);
   surface->put_ProfileGradePoint(1);

   CComPtr<ISurfaceTemplate> template50;
   surface->CreateSurfaceTemplate(CComVariant(50), &template50);
   template50->UpdateSegmentParameters(0, 20.0, 0.02, tsHorizontal);
   template50->UpdateSegmentParameters(1, 20.0, -0.04, tsHorizontal);

   CComPtr<ISurfaceTemplate> template100;
   surface->CreateSurfaceTemplate(CComVariant(100), &template100);
   template100->UpdateSegmentParameters(0, 20.0, 0.02, tsHorizontal);
   template100->UpdateSegmentParameters(1, 20.0, -0.04, tsHorizontal);

   Float64 elev;
   profile->Elevation(surfaceID, CComVariant(100), 0.00, &elev);   TRY_TEST(IsEqual(elev, 100.00), true);
   profile->Elevation(surfaceID, CComVariant(100), 5.00, &elev);   TRY_TEST(IsEqual(elev, 99.80), true);
   profile->Elevation(surfaceID, CComVariant(100), -5.00,&elev);   TRY_TEST(IsEqual(elev, 99.90),true);
}

void CTestProfile::Test11()
{
   // Test a profile with 3 vertical curve elements
   // Adding this test because I found an error that was
   // not detected by the previous test cases.
   // The elevation at the BVC not computed correctly by the Profile object
   // however, it is computed correctly by the VertCurve object
   // RAB: 11/14/2001
   CComPtr<IAlignment> alignment;
   alignment.CoCreateInstance(CLSID_Alignment);

   CComPtr<IProfile> profile;
   TRY_TEST(profile.CoCreateInstance(CLSID_Profile), S_OK);

   alignment->AddProfile(0, profile);


   // Start point
   CComPtr<IProfilePoint> start;
   start.CoCreateInstance(CLSID_ProfilePoint);
   start->Move(CComVariant(100), 50);

   CComPtr<IProfilePoint> pvi1;
   pvi1.CoCreateInstance(CLSID_ProfilePoint);
   pvi1->Move(CComVariant(300), 80);

   CComPtr<IProfilePoint> pvi2;
   pvi2.CoCreateInstance(CLSID_ProfilePoint);
   pvi2->Move(CComVariant(500), 50);

   CComPtr<IProfilePoint> pvi3;
   pvi3.CoCreateInstance(CLSID_ProfilePoint);
   pvi3->Move(CComVariant(700), 80);

   // Finish point
   CComPtr<IProfilePoint> finish;
   finish.CoCreateInstance(CLSID_ProfilePoint);
   finish->Move(CComVariant(900),50);

   // Vert Curve #1
   CComPtr<IVerticalCurve> vc1;
   vc1.CoCreateInstance(CLSID_VerticalCurve);
   vc1->Init(start, pvi1, pvi2, 50, 50);

   // Vert Curve #2
   CComPtr<IVerticalCurve> vc2;
   vc2.CoCreateInstance(CLSID_VerticalCurve);
   vc2->Init(pvi1, pvi2, pvi3, 50, 50);

   // Vert Curve #3
   CComPtr<IVerticalCurve> vc3;
   vc3.CoCreateInstance(CLSID_VerticalCurve);
   vc3->Init(pvi2, pvi3, finish, 50, 50);

   CComQIPtr<IProfileElement> element1(vc1), element2(vc2), element3(vc3);
   profile->AddProfileElement(element1);
   profile->AddProfileElement(element2);
   profile->AddProfileElement(element3);

   Float64 elev;
   profile->Elevation(INVALID_ID, CComVariant(250), 0.00, &elev);   TRY_TEST(IsEqual(elev, 72.5), true);
   profile->Elevation(INVALID_ID, CComVariant(450), 0.00, &elev);   TRY_TEST(IsEqual(elev, 57.5), true);
   profile->Elevation(INVALID_ID, CComVariant(650), 0.00,&elev);   TRY_TEST(IsEqual(elev,72.5),true);
}

void CTestProfile::Test12()
{
   CComPtr<IAlignment> alignment;
   alignment.CoCreateInstance(CLSID_Alignment);
   Float64 refStation = 2336.53;
   alignment->put_RefStation(CComVariant(refStation));

   CComPtr<IPoint2d> pbt;
   pbt.CoCreateInstance(CLSID_Point2d);
   pbt->Move(2451859.110, 1005078.896);

   CComPtr<IDirection> bkTangent;
   bkTangent.CoCreateInstance(CLSID_Direction);
   bkTangent->FromString(CComBSTR("N 02 06 34 E"));

   CComPtr<ICogoEngine> engine;
   engine.CoCreateInstance(CLSID_CogoEngine);

   CComQIPtr<ILocate2> locate(engine);
   CComPtr<IPoint2d> pi;
   locate->ByDistDir(pbt, (2587.80 - refStation), CComVariant(bkTangent), 0.0, &pi);

   CComPtr<IDirection> fwdTangent;
   fwdTangent.CoCreateInstance(CLSID_Direction);
   fwdTangent->FromString(CComBSTR("N 02 06 34 E"));
   fwdTangent->IncrementBy(CComVariant("10 01 30 R"));

   CComPtr<IPoint2d> pft;
   locate->ByDistDir(pbt, 5000.0, CComVariant(fwdTangent), 0.0, &pft);

   CComPtr<ICircularCurve> curve;
   curve.CoCreateInstance(CLSID_CircularCurve);
   curve->put_PBT(pbt);
   curve->put_PI(pi);
   curve->put_PFT(pft);
   curve->put_Radius(2864.79);

   CComPtr<IPoint2d> pc;
   curve->get_PC(&pc);

   CComPtr<IPathSegment> segment;
   segment.CoCreateInstance(CLSID_PathSegment);
   segment->ThroughPoints(pbt, pc);

   CComQIPtr<IPathElement> element(segment);
   alignment->AddPathElement(element);
   element.Release();
   curve.QueryInterface(&element);
   alignment->AddPathElement(element);

   CComPtr<IProfile> profile;
   TRY_TEST(profile.CoCreateInstance(CLSID_Profile), S_OK);

   alignment->AddProfile(0, profile);


   // Start point
   CComPtr<IProfilePoint> bvc1;
   bvc1.CoCreateInstance(CLSID_ProfilePoint);
   bvc1->Move(CComVariant(2000.61), 289.97);

   CComPtr<IProfilePoint> evc1;
   evc1.CoCreateInstance(CLSID_ProfilePoint);
   evc1->Move(CComVariant(2255.97), 293.16);

   CComPtr<IVerticalCurve> vc1;
   vc1.CoCreateInstance(CLSID_VerticalCurve);
   vc1->Init2(bvc1, evc1, 1.97585 / 100, 0.5187 / 100);

   CComPtr<IProfilePoint> bvc2;
   bvc2.CoCreateInstance(CLSID_ProfilePoint);
   bvc2->Move(CComVariant(2749.94), 295.72);

   CComPtr<IProfilePoint> pvi2;
   pvi2.CoCreateInstance(CLSID_ProfilePoint);
   pvi2->Move(CComVariant(2997.77), 297.01);

   CComPtr<IProfilePoint> evc2;
   evc2.CoCreateInstance(CLSID_ProfilePoint);
   evc2->Move(CComVariant(3245.63), 295.74);

   CComPtr<IVerticalCurve> vc2;
   vc2.CoCreateInstance(CLSID_VerticalCurve);
   vc2->Init(bvc2, pvi2, evc2, 495.73 / 2, 495.73 / 2);

   CComQIPtr<IProfileElement> pelement(vc1);
   profile->AddProfileElement(pelement);
   pelement.Release();
   vc2.QueryInterface(&pelement);
   profile->AddProfileElement(pelement);

   CComPtr<ISurface> surface;
   surface.CoCreateInstance(CLSID_Surface);
   surface->put_SurfaceTemplateSegmentCount(2);
   surface->put_AlignmentPoint(2);
   surface->put_ProfileGradePoint(1);
   profile->AddSurface(0, surface);

   CComPtr<ISurfaceTemplate> surface_template;
   surface->CreateSurfaceTemplate(CComVariant(refStation), &surface_template);
   surface_template->UpdateSegmentParameters(0, 36, -0.02, tsHorizontal);
   surface_template->UpdateSegmentParameters(1, 16, -0.02, tsHorizontal);

   CComPtr<ISuperelevation> superelevation;
   superelevation.CoCreateInstance(CLSID_Superelevation);
   superelevation->Init(CComVariant(2198), CComVariant(2300), CComVariant(2770), CComVariant(2872), -0.04, 1, stLinear, 0, 0, stLinear, 0, 0);

   surface->AddSuperelevation(superelevation);

   std::vector<std::tuple<Float64, Float64, Float64, Float64>> vResults1{
      {2000.61000, 290.69000, 289.97000, 289.65000},
      {2025.51040, 291.16440, 290.44440, 290.12440},
      {2050.41080, 291.60360, 290.88360, 290.56360},
      {2075.31120, 292.00762, 291.28762, 290.96762},
      {2100.21160, 292.37644, 291.65644, 291.33644},
      {2125.11200, 292.71007, 291.99007, 291.67007},
      {2150.01240, 293.00836, 292.28836, 291.96836},
      {2174.91280, 293.27110, 292.55110, 292.23110},
      {2199.81320, 293.51106, 292.77826, 292.45257},
      {2224.71360, 293.87842, 292.96985, 292.56604},
      {2249.61400, 294.21021, 293.12587, 292.64395},
      {2274.51440, 294.51621, 293.25611, 292.69606},
      {2299.41480, 294.82102, 293.38515, 292.74699},
      {2324.31520, 294.95420, 293.51420, 292.87420},
      {2349.21560, 295.08325, 293.64325, 293.00325},
      {2374.11600, 295.21229, 293.77229, 293.13229},
      {2399.01640, 295.34134, 293.90134, 293.26134},
      {2423.91680, 295.47038, 294.03038, 293.39038},
      {2448.81720, 295.59943, 294.15943, 293.51943},
      {2473.71760, 295.72848, 294.28848, 293.64848},
      {2498.61800, 295.85752, 294.41752, 293.77752},
      {2523.51840, 295.98657, 294.54657, 293.90657},
      {2548.41880, 296.11562, 294.67562, 294.03562},
      {2573.31920, 296.24466, 294.80466, 294.16466},
      {2598.21960, 296.37371, 294.93371, 294.29371},
      {2623.12000, 296.50275, 295.06275, 294.42275},
      {2648.02040, 296.63180, 295.19180, 294.55180},
      {2672.92080, 296.76085, 295.32085, 294.68085},
      {2697.82120, 296.88989, 295.44989, 294.80989},
      {2722.72160, 297.01894, 295.57894, 294.93894},
      {2747.62200, 297.14799, 295.70799, 295.06799},
      {2772.52240, 297.25441, 295.83222, 295.20013},
      {2797.42280, 297.19006, 295.94363, 295.38967},
      {2822.32320, 297.11279, 296.04213, 295.56628},
      {2847.22360, 297.02260, 296.12771, 295.72998},
      {2872.12400, 296.92037, 296.20037, 295.88037},
      {2897.02440, 296.98011, 296.26011, 295.94011},
      {2921.92480, 297.02693, 296.30693, 295.98693},
      {2946.82520, 297.06084, 296.34084, 296.02084},
      {2971.72560, 297.08182, 296.36182, 296.04182},
      {2996.62600, 297.08989, 296.36989, 296.04989},
      {3021.52640, 297.08503, 296.36503, 296.04503},
      {3046.42680, 297.06726, 296.34726, 296.02726},
      {3071.32720, 297.03657, 296.31657, 295.99657},
      {3096.22760, 296.99296, 296.27296, 295.95296},
      {3121.12800, 296.93643, 296.21643, 295.89643},
      {3146.02840, 296.86698, 296.14698, 295.82698},
      {3170.92880, 296.78462, 296.06462, 295.74462},
      {3195.82920, 296.68933, 295.96933, 295.64933},
      {3220.72960, 296.58112, 295.86112, 295.54112}
   };

   for (int i = 0; i < 50; i++)
   {
      Float64 station(2000.61 + i * (3245.63 - 2000.61) / 50);
      Float64 elevL, elevP, elevR;
      profile->Elevation(0, CComVariant(station), -52, &elevL); // 52 ft left of alignment
      profile->Elevation(0, CComVariant(station), -16, &elevP); // 16 ft left of alignment
      profile->Elevation(0, CComVariant(station), 0, &elevR); // on the alignment

      TRY_TEST(IsEqual(station, std::get<0>(vResults1[i])),true);
      TRY_TEST(IsEqual(std::get<1>(vResults1[i]), elevL),true);
      TRY_TEST(IsEqual(std::get<2>(vResults1[i]), elevP),true);
      TRY_TEST(IsEqual(std::get<3>(vResults1[i]), elevR),true);
   }

   superelevation->put_PivotPoint(0); // pivot about left curb line
   std::vector<std::tuple<Float64, Float64, Float64, Float64>> vResults2{
      {2000.61000, 290.69000, 289.97000, 289.65000},
      {2025.51040, 291.16440, 290.44440, 290.12440},
      {2050.41080, 291.60360, 290.88360, 290.56360},
      {2075.31120, 292.00762, 291.28762, 290.96762},
      {2100.21160, 292.37644, 291.65644, 291.33644},
      {2125.11200, 292.71007, 291.99007, 291.67007},
      {2150.01240, 293.00836, 292.28836, 291.96836},
      {2174.91280, 293.27110, 292.55110, 292.23110},
      {2199.81320, 293.49826, 292.76546, 292.43977},
      {2224.71360, 293.68985, 292.78128, 292.37748},
      {2249.61400, 293.84587, 292.76154, 292.27961},
      {2274.51440, 293.97611, 292.71600, 292.15596},
      {2299.41480, 294.10515, 292.66928, 292.03112},
      {2324.31520, 294.23420, 292.79420, 292.15420},
      {2349.21560, 294.36325, 292.92325, 292.28325},
      {2374.11600, 294.49229, 293.05229, 292.41229},
      {2399.01640, 294.62134, 293.18134, 292.54134},
      {2423.91680, 294.75038, 293.31038, 292.67038},
      {2448.81720, 294.87943, 293.43943, 292.79943},
      {2473.71760, 295.00848, 293.56848, 292.92848},
      {2498.61800, 295.13752, 293.69752, 293.05752},
      {2523.51840, 295.26657, 293.82657, 293.18657},
      {2548.41880, 295.39562, 293.95562, 293.31562},
      {2573.31920, 295.52466, 294.08466, 293.44466},
      {2598.21960, 295.65371, 294.21371, 293.57371},
      {2623.12000, 295.78275, 294.34275, 293.70275},
      {2648.02040, 295.91180, 294.47180, 293.83180},
      {2672.92080, 296.04085, 294.60085, 293.96085},
      {2697.82120, 296.16989, 294.72989, 294.08989},
      {2722.72160, 296.29894, 294.85894, 294.21894},
      {2747.62200, 296.42799, 294.98799, 294.34799},
      {2772.52240, 296.55222, 295.13002, 294.49793},
      {2797.42280, 296.66363, 295.41721, 294.86324},
      {2822.32320, 296.76213, 295.69147, 295.21562},
      {2847.22360, 296.84771, 295.95282, 295.55509},
      {2872.12400, 296.92037, 296.20037, 295.88037},
      {2897.02440, 296.98011, 296.26011, 295.94011},
      {2921.92480, 297.02693, 296.30693, 295.98693},
      {2946.82520, 297.06084, 296.34084, 296.02084},
      {2971.72560, 297.08182, 296.36182, 296.04182},
      {2996.62600, 297.08989, 296.36989, 296.04989},
      {3021.52640, 297.08503, 296.36503, 296.04503},
      {3046.42680, 297.06726, 296.34726, 296.02726},
      {3071.32720, 297.03657, 296.31657, 295.99657},
      {3096.22760, 296.99296, 296.27296, 295.95296},
      {3121.12800, 296.93643, 296.21643, 295.89643},
      {3146.02840, 296.86698, 296.14698, 295.82698},
      {3170.92880, 296.78462, 296.06462, 295.74462},
      {3195.82920, 296.68933, 295.96933, 295.64933},
      {3220.72960, 296.58112, 295.86112, 295.54112}
   };

   for (int i = 0; i < 50; i++)
   {
      Float64 station(2000.61 + i * (3245.63 - 2000.61) / 50);
      Float64 elevL, elevP, elevR;
      profile->Elevation(0, CComVariant(station), -52, &elevL); // 52 ft left of alignment
      profile->Elevation(0, CComVariant(station), -16, &elevP); // 16 ft left of alignment
      profile->Elevation(0, CComVariant(station), 0, &elevR); // on the alignment

      TRY_TEST(IsEqual(station, std::get<0>(vResults2[i])), true);
      TRY_TEST(IsEqual(std::get<1>(vResults2[i]), elevL), true);
      TRY_TEST(IsEqual(std::get<2>(vResults2[i]), elevP), true);
      TRY_TEST(IsEqual(std::get<3>(vResults2[i]), elevR), true);
   }


   superelevation->put_PivotPoint(2); // pivot about right curb line
   std::vector<std::tuple<Float64, Float64, Float64, Float64>> vResults3{
      {2000.61000, 290.69000, 289.97000, 289.65000},
      {2025.51040, 291.16440, 290.44440, 290.12440},
      {2050.41080, 291.60360, 290.88360, 290.56360},
      {2075.31120, 292.00762, 291.28762, 290.96762},
      {2100.21160, 292.37644, 291.65644, 291.33644},
      {2125.11200, 292.71007, 291.99007, 291.67007},
      {2150.01240, 293.00836, 292.28836, 291.96836},
      {2174.91280, 293.27110, 292.55110, 292.23110},
      {2199.81320, 293.51675, 292.78395, 292.45826},
      {2224.71360, 293.96222, 293.05366, 292.64985},
      {2249.61400, 294.37213, 293.28780, 292.80587},
      {2274.51440, 294.75625, 293.49615, 292.93611},
      {2299.41480, 295.13919, 293.70332, 293.06515},
      {2324.31520, 295.27420, 293.83420, 293.19420},
      {2349.21560, 295.40325, 293.96325, 293.32325},
      {2374.11600, 295.53229, 294.09229, 293.45229},
      {2399.01640, 295.66134, 294.22134, 293.58134},
      {2423.91680, 295.79038, 294.35038, 293.71038},
      {2448.81720, 295.91943, 294.47943, 293.83943},
      {2473.71760, 296.04848, 294.60848, 293.96848},
      {2498.61800, 296.17752, 294.73752, 294.09752},
      {2523.51840, 296.30657, 294.86657, 294.22657},
      {2548.41880, 296.43562, 294.99562, 294.35562},
      {2573.31920, 296.56466, 295.12466, 294.48466},
      {2598.21960, 296.69371, 295.25371, 294.61371},
      {2623.12000, 296.82275, 295.38275, 294.74275},
      {2648.02040, 296.95180, 295.51180, 294.87180},
      {2672.92080, 297.08085, 295.64085, 295.00085},
      {2697.82120, 297.20989, 295.76989, 295.12989},
      {2722.72160, 297.33894, 295.89894, 295.25894},
      {2747.62200, 297.46799, 296.02799, 295.38799},
      {2772.52240, 297.56650, 296.14430, 295.51222},
      {2797.42280, 297.42403, 296.17760, 295.62363},
      {2822.32320, 297.26864, 296.19798, 295.72213},
      {2847.22360, 297.10033, 296.20544, 295.80771},
      {2872.12400, 296.92037, 296.20037, 295.88037},
      {2897.02440, 296.98011, 296.26011, 295.94011},
      {2921.92480, 297.02693, 296.30693, 295.98693},
      {2946.82520, 297.06084, 296.34084, 296.02084},
      {2971.72560, 297.08182, 296.36182, 296.04182},
      {2996.62600, 297.08989, 296.36989, 296.04989},
      {3021.52640, 297.08503, 296.36503, 296.04503},
      {3046.42680, 297.06726, 296.34726, 296.02726},
      {3071.32720, 297.03657, 296.31657, 295.99657},
      {3096.22760, 296.99296, 296.27296, 295.95296},
      {3121.12800, 296.93643, 296.21643, 295.89643},
      {3146.02840, 296.86698, 296.14698, 295.82698},
      {3170.92880, 296.78462, 296.06462, 295.74462},
      {3195.82920, 296.68933, 295.96933, 295.64933},
      {3220.72960, 296.58112, 295.86112, 295.54112}
   };

   for (int i = 0; i < 50; i++)
   {
      Float64 station(2000.61 + i * (3245.63 - 2000.61) / 50);
      Float64 elevL, elevP, elevR;
      profile->Elevation(0, CComVariant(station), -52, &elevL); // 52 ft left of alignment
      profile->Elevation(0, CComVariant(station), -16, &elevP); // 16 ft left of alignment
      profile->Elevation(0, CComVariant(station), 0, &elevR); // on the alignment

      TRY_TEST(IsEqual(station, std::get<0>(vResults3[i])), true);
      TRY_TEST(IsEqual(std::get<1>(vResults3[i]), elevL), true);
      TRY_TEST(IsEqual(std::get<2>(vResults3[i]), elevP), true);
      TRY_TEST(IsEqual(std::get<3>(vResults3[i]), elevR), true);
   }
}

void TestElevation(IProfile* profile, IDType surfaceID,Float64 offset,Float64 results[],long minStation,long maxStation,long inc)
{
   CComPtr<IAlignment> alignment;
   profile->get_Alignment(&alignment);

   long j = 0;
   for ( long i = minStation; i <= maxStation; i += inc, j++)
   {
      Float64 elev;
      Float64 station = (Float64)i;
      CComPtr<IStation> objStation;
      alignment->ConvertFromNormalizedStation(station, &objStation);
      profile->Elevation(surfaceID,CComVariant(objStation),offset,&elev);
      TRY_TEST( IsEqual(elev, results[j],0.001), true );
   }
}

void TestGrade(IProfile* profile,Float64 results[],long minStation,long maxStation,long inc)
{
   CComPtr<IAlignment> alignment;
   profile->get_Alignment(&alignment);

   long j = 0;
   for ( long i = minStation; i <= maxStation; i += inc, j++)
   {
      CComPtr<IStation> objStation;
      Float64 grade;
      Float64 station = (Float64)i;
      alignment->ConvertFromNormalizedStation(station, &objStation);
      profile->Grade(CComVariant(objStation),&grade);
      TRY_TEST( IsEqual(grade*100, results[j],0.001), true );
   }
}

void TestCrownSlopes(IProfile* profile,IDType surfaceID,IndexType ridgePointIdx,Float64 results[][2],long minStation,long maxStation,long inc)
{
   CComPtr<IAlignment> alignment;
   profile->get_Alignment(&alignment);

   IndexType leftSegmentIdx = ridgePointIdx-1;
   IndexType rightSegmentIdx = ridgePointIdx;

   long j = 0;
   for ( long i = minStation; i <= maxStation; i += inc, j++)
   {
      Float64 left, right;
      Float64 station = (Float64)i;
      CComPtr<IStation> objStation;
      alignment->ConvertFromNormalizedStation(station, &objStation);

      CComPtr<ISurfaceTemplate> surface_template;
      profile->CreateSurfaceTemplateSectionCut(surfaceID, CComVariant(objStation), true, &surface_template);
      surface_template->GetSegmentSlope(leftSegmentIdx, &left);
      surface_template->GetSegmentSlope(rightSegmentIdx,&right);

      TRY_TEST( IsEqual(left,  results[j][0], 0.001), true );
      TRY_TEST( IsEqual(right, results[j][1], 0.001), true );
   }
}