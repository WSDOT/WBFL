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

// TestAlignment.cpp
//
// Ported from F:\ARP\WBFL\COGO\CogoTest\TestAlignment.cpp (legacy WBFLTest.h
// harness) to MSVC CppUnitTestFramework, talking to WBFLCogo.dll purely
// through its public COM interfaces (see CogoTestUtil.h). The legacy Test()
// dispatched to CTestAlignment1/2/3::Test() at the end; those are now
// independent TEST_CLASSes (TestAlignment1/2/3) run directly by MSTest, so
// that dispatch tail is dropped here rather than ported.
#include "pch.h"

namespace CogoUnitTests
{

TEST_CLASS(TestAlignment)
{
public:
   TEST_METHOD(AddCountItem)
   {
         CComPtr<IAlignment> alignment;
         ASSERT_EQ(alignment.CoCreateInstance(CLSID_Alignment),S_OK);

         //
         // Test Add
         //

         // Create an Alignment segment
         CComPtr<IPathSegment> segment;
         ASSERT_EQ(segment.CoCreateInstance(CLSID_PathSegment),S_OK);

         CComPtr<IPoint2d> p1;
         p1.CoCreateInstance(CLSID_Point2d);
         p1->Move(10, 20);

         CComPtr<IPoint2d> p2;
         p2.CoCreateInstance(CLSID_Point2d);
         p2->Move(10, 50);

         segment->ThroughPoints(p1, p2);

         // add it to the Alignment
         ASSERT_EQ(alignment->AddPathElement(nullptr),E_INVALIDARG);
         CComQIPtr<IPathElement> element(segment);
         ASSERT_EQ(alignment->AddPathElement(element),S_OK);

         // create a horz curve
         CComPtr<ICompoundCurve> hc;
         hc.CoCreateInstance(CLSID_CompoundCurve);
         p1.Release();
         hc->get_PBT(&p1);
         p1->Move(100,100);

         // add it to the Alignment
         element.Release();
         hc->QueryInterface(&element);
         ASSERT_EQ(alignment->AddPathElement(element), S_OK);

         //
         // Test Count
         //
         IndexType count;
         ASSERT_EQ(alignment->get_Count(nullptr),E_POINTER);
         ASSERT_EQ(alignment->get_Count(&count),S_OK);
         ASSERT_EQ(count,2);

         //
         // Test Item
         //

         // make sure items are sorted properly
         element.Release();
         ASSERT_EQ(alignment->get_Item(-1,&element),E_INVALIDARG);
         ASSERT_EQ(alignment->get_Item(100,&element),E_INVALIDARG);
         ASSERT_EQ(alignment->get_Item(0,nullptr),E_POINTER);
         ASSERT_EQ(alignment->get_Item(0,&element),S_OK);

         ////
         //// Test Insert and InsertEx
         ////
         //ASSERT_EQ(alignment->Insert(1,nullptr),E_INVALIDARG);
         //ASSERT_EQ(alignment->Insert(-1,element),E_INVALIDARG);
         //ASSERT_EQ(alignment->Insert(100,element),E_INVALIDARG);
         //ASSERT_EQ(alignment->Insert(1,element),S_OK);

         //ASSERT_EQ(alignment->InsertEx(1,nullptr),E_INVALIDARG);
         ////ASSERT_EQ(alignment->InsertEx(1,alignment),COGO_E_PATHELEMENTTYPE); // alignment/path are now valid path elements
         //ASSERT_EQ(alignment->InsertEx(-1,point),E_INVALIDARG);
         //ASSERT_EQ(alignment->InsertEx(100,point),E_INVALIDARG);
         //ASSERT_EQ(alignment->InsertEx(1,point),S_OK);

         ////
         //// Test Remove
         ////
         //point.Release();
         //hc->get_PBT(&point);
         //ASSERT_EQ(alignment->Remove(CComVariant()),E_INVALIDARG);
         //ASSERT_EQ(alignment->Remove(CComVariant(alignment)),E_INVALIDARG);
         //ASSERT_EQ(alignment->Remove(CComVariant(-1)),E_INVALIDARG);
         //ASSERT_EQ(alignment->Remove(CComVariant(100)),E_INVALIDARG);
         //ASSERT_EQ(alignment->Remove(CComVariant(point)),S_OK);
         //ASSERT_EQ(alignment->Remove(CComVariant(hc)),S_OK); // Remove the vert curve
         //ASSERT_EQ(alignment->Remove(CComVariant(1)),S_OK);  // Remove the element at index 1

         //alignment->get_Count(&count);
         //ASSERT_EQ(count,2);

         ////
         //// Test Profile
         ////
         //CComPtr<IProfile> profile;
         //ASSERT_EQ(alignment->get_Profile(nullptr),E_POINTER);
         //ASSERT_EQ(alignment->get_Profile(&profile),S_OK);

         ////
         //// Test Station Equations
         ////
         //CComPtr<IStationEquationCollection> equations;
         //ASSERT_EQ(alignment->get_StationEquations(nullptr),E_POINTER);
         //ASSERT_EQ(alignment->get_StationEquations(&equations),S_OK);

         ////
         //// Test Clear
         ////
         //ASSERT_EQ(alignment->Clear(),S_OK);
         //alignment->get_Count(&count);
         //ASSERT_EQ(count,0);

         ////
         //// RefStation
         //CComPtr<IStation> station;
         //Float64 stationVal;
         //ASSERT_EQ(alignment->get_RefStation(nullptr),E_POINTER);
         //ASSERT_EQ(alignment->get_RefStation(&station),S_OK);
         //station->get_Value(&stationVal);
         //ASSERT_EQ(IsEqual(stationVal,0.0),true);
         //ASSERT_EQ(alignment->put_RefStation(CComVariant(100.0)),S_OK);
         //station.Release();
         //ASSERT_EQ(alignment->get_RefStation(&station),S_OK);
         //station->get_Value(&stationVal);
         //ASSERT_EQ(IsEqual(stationVal,100.0),true);
         //ASSERT_EQ(alignment->put_RefStation(CComVariant("12+3499.56")),E_INVALIDARG);
         //ASSERT_EQ(alignment->put_RefStation(CComVariant("12+34.56")),S_OK);
         //station.Release();
         //ASSERT_EQ(alignment->get_RefStation(&station),S_OK);
         //station->get_Value(&stationVal);
         //ASSERT_EQ(IsEqual(stationVal,1234.56),true);

         ////
         //// GetDirection
         //alignment->put_RefStation(CComVariant(0.0));
         //point.Release();
         //point.CoCreateInstance(CLSID_Point2d);
         //point->Move(0, 0);
         //ASSERT_EQ(alignment->AddEx(point), S_OK);
         //point.Release();
         //point.CoCreateInstance(CLSID_Point2d);
         //point->Move(100, 100);
         //ASSERT_EQ(alignment->AddEx(point), S_OK);

         //CComPtr<IDirection> direction;
         //alignment->GetDirection(CComVariant(0.0), CComBSTR("N"), &direction);
         //Float64 value;
         //direction->get_Value(&value);
         //ASSERT_EQ(IsEqual(value, 3 * M_PI / 4), true);

         //direction.Release();
         //alignment->GetDirection(CComVariant(0.0), CComBSTR("Normal"), &direction);
         //direction->get_Value(&value);
         //ASSERT_EQ(IsEqual(value, 3 * M_PI / 4), true);

         //direction.Release();
         //alignment->GetDirection(CComVariant(50.0), CComBSTR("15 0 0 L"), &direction);
         //direction->get_Value(&value);
         //ASSERT_EQ(IsEqual(value, 3 * M_PI / 4 + ToRadians(15)), true);

         //direction.Release();
         //alignment->GetDirection(CComVariant(50.0), CComBSTR("15 0 0 R"), &direction);
         //direction->get_Value(&value);
         //ASSERT_EQ(IsEqual(value, 3 * M_PI / 4 - ToRadians(15)), true);

         //direction.Release();
         //alignment->GetDirection(CComVariant(100.0), CComBSTR("N 45 W"), &direction);
         //direction->get_Value(&value);
         //ASSERT_EQ(IsEqual(value, 3 * M_PI / 4), true);

         //direction.Release();
         //alignment->GetDirection(CComVariant(100.0), CComBSTR("S 45 W"), &direction);
         //direction->get_Value(&value);
         //ASSERT_EQ(IsEqual(value, 5 * M_PI / 4), true);

         //direction.Release();
         //alignment->GetDirection(CComVariant(100.0), CComBSTR("N 45 E"), &direction);
         //direction->get_Value(&value);
         //ASSERT_EQ(IsEqual(value, M_PI / 4), true);

         //direction.Release();
         //alignment->GetDirection(CComVariant(100.0), CComBSTR("S 45 E"), &direction);
         //direction->get_Value(&value);
         //ASSERT_EQ(IsEqual(value, 3 * M_PI / 4), true);


         ////
         //// _EnumAlignmentElements
         //alignment->Clear();
         //alignment->AddEx(point);
         //alignment->AddEx(hc);
         //CComPtr<IEnumPathElements> pEnum;
         //ASSERT_EQ(alignment->get__EnumAlignmentElements(nullptr),E_POINTER);
         //ASSERT_EQ(alignment->get__EnumAlignmentElements(&pEnum),S_OK);

         //// Test ISupportErrorInfo
         //CComQIPtr<ISupportErrorInfo> eInfo(alignment);
         //ASSERT_EQ( eInfo != nullptr, true );
         //ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_IAlignment ), S_OK );
         //ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

         //// Test IObjectSafety
         //ASSERT_EQ( TestIObjectSafety(CLSID_Alignment,IID_IAlignment,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
   }
};
} // namespace CogoUnitTests