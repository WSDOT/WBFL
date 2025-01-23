///////////////////////////////////////////////////////////////////////
// COGOTest - Test Driver for Coordinate Geometry Library
// Copyright © 1999-2025  Washington State Department of Transportation
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

// TestAlignment.cpp: implementation of the CTestAlignment class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestAlignment.h"
#include "TestAlignment1.h"
#include "TestAlignment2.h"
#include "TestAlignment3.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestAlignment::CTestAlignment()
{

}

void CTestAlignment::Test()
{
   CComPtr<IAlignment> alignment;
   TRY_TEST(alignment.CoCreateInstance(CLSID_Alignment),S_OK);

   //
   // Test Add
   //

   // Create an Alignment segment
   CComPtr<IPathSegment> segment;
   TRY_TEST(segment.CoCreateInstance(CLSID_PathSegment),S_OK);

   CComPtr<IPoint2d> p1;
   p1.CoCreateInstance(CLSID_Point2d);
   p1->Move(10, 20);

   CComPtr<IPoint2d> p2;
   p2.CoCreateInstance(CLSID_Point2d);
   p2->Move(10, 50);

   segment->ThroughPoints(p1, p2);

   // add it to the Alignment
   TRY_TEST(alignment->AddPathElement(nullptr),E_INVALIDARG);
   CComQIPtr<IPathElement> element(segment);
   TRY_TEST(alignment->AddPathElement(element),S_OK);

   // create a horz curve
   CComPtr<ICompoundCurve> hc;
   hc.CoCreateInstance(CLSID_CompoundCurve);
   p1.Release();
   hc->get_PBT(&p1);
   p1->Move(100,100);

   // add it to the Alignment
   element.Release();
   hc->QueryInterface(&element);
   TRY_TEST(alignment->AddPathElement(element), S_OK);

   //
   // Test Count
   //
   IndexType count;
   TRY_TEST(alignment->get_Count(nullptr),E_POINTER);
   TRY_TEST(alignment->get_Count(&count),S_OK);
   TRY_TEST(count,2);

   //
   // Test Item
   //

   // make sure items are sorted properly
   element.Release();
   TRY_TEST(alignment->get_Item(-1,&element),E_INVALIDARG);
   TRY_TEST(alignment->get_Item(100,&element),E_INVALIDARG);
   TRY_TEST(alignment->get_Item(0,nullptr),E_POINTER);
   TRY_TEST(alignment->get_Item(0,&element),S_OK);

   ////
   //// Test Insert and InsertEx
   ////
   //TRY_TEST(alignment->Insert(1,nullptr),E_INVALIDARG);
   //TRY_TEST(alignment->Insert(-1,element),E_INVALIDARG);
   //TRY_TEST(alignment->Insert(100,element),E_INVALIDARG);
   //TRY_TEST(alignment->Insert(1,element),S_OK);

   //TRY_TEST(alignment->InsertEx(1,nullptr),E_INVALIDARG);
   ////TRY_TEST(alignment->InsertEx(1,alignment),COGO_E_PATHELEMENTTYPE); // alignment/path are now valid path elements
   //TRY_TEST(alignment->InsertEx(-1,point),E_INVALIDARG);
   //TRY_TEST(alignment->InsertEx(100,point),E_INVALIDARG);
   //TRY_TEST(alignment->InsertEx(1,point),S_OK);

   ////
   //// Test Remove
   ////
   //point.Release();
   //hc->get_PBT(&point);
   //TRY_TEST(alignment->Remove(CComVariant()),E_INVALIDARG);
   //TRY_TEST(alignment->Remove(CComVariant(alignment)),E_INVALIDARG);
   //TRY_TEST(alignment->Remove(CComVariant(-1)),E_INVALIDARG);
   //TRY_TEST(alignment->Remove(CComVariant(100)),E_INVALIDARG);
   //TRY_TEST(alignment->Remove(CComVariant(point)),S_OK);
   //TRY_TEST(alignment->Remove(CComVariant(hc)),S_OK); // Remove the vert curve
   //TRY_TEST(alignment->Remove(CComVariant(1)),S_OK);  // Remove the element at index 1

   //alignment->get_Count(&count);
   //TRY_TEST(count,2);

   ////
   //// Test Profile
   ////
   //CComPtr<IProfile> profile;
   //TRY_TEST(alignment->get_Profile(nullptr),E_POINTER);
   //TRY_TEST(alignment->get_Profile(&profile),S_OK);

   ////
   //// Test Station Equations
   ////
   //CComPtr<IStationEquationCollection> equations;
   //TRY_TEST(alignment->get_StationEquations(nullptr),E_POINTER);
   //TRY_TEST(alignment->get_StationEquations(&equations),S_OK);

   ////
   //// Test Clear
   ////
   //TRY_TEST(alignment->Clear(),S_OK);
   //alignment->get_Count(&count);
   //TRY_TEST(count,0);

   ////
   //// RefStation
   //CComPtr<IStation> station;
   //Float64 stationVal;
   //TRY_TEST(alignment->get_RefStation(nullptr),E_POINTER);
   //TRY_TEST(alignment->get_RefStation(&station),S_OK);
   //station->get_Value(&stationVal);
   //TRY_TEST(IsEqual(stationVal,0.0),true);
   //TRY_TEST(alignment->put_RefStation(CComVariant(100.0)),S_OK);
   //station.Release();
   //TRY_TEST(alignment->get_RefStation(&station),S_OK);
   //station->get_Value(&stationVal);
   //TRY_TEST(IsEqual(stationVal,100.0),true);
   //TRY_TEST(alignment->put_RefStation(CComVariant("12+3499.56")),E_INVALIDARG);
   //TRY_TEST(alignment->put_RefStation(CComVariant("12+34.56")),S_OK);
   //station.Release();
   //TRY_TEST(alignment->get_RefStation(&station),S_OK);
   //station->get_Value(&stationVal);
   //TRY_TEST(IsEqual(stationVal,1234.56),true);

   ////
   //// GetDirection
   //alignment->put_RefStation(CComVariant(0.0));
   //point.Release();
   //point.CoCreateInstance(CLSID_Point2d);
   //point->Move(0, 0);
   //TRY_TEST(alignment->AddEx(point), S_OK);
   //point.Release();
   //point.CoCreateInstance(CLSID_Point2d);
   //point->Move(100, 100);
   //TRY_TEST(alignment->AddEx(point), S_OK);

   //CComPtr<IDirection> direction;
   //alignment->GetDirection(CComVariant(0.0), CComBSTR("N"), &direction);
   //Float64 value;
   //direction->get_Value(&value);
   //TRY_TEST(IsEqual(value, 3 * M_PI / 4), true);

   //direction.Release();
   //alignment->GetDirection(CComVariant(0.0), CComBSTR("Normal"), &direction);
   //direction->get_Value(&value);
   //TRY_TEST(IsEqual(value, 3 * M_PI / 4), true);

   //direction.Release();
   //alignment->GetDirection(CComVariant(50.0), CComBSTR("15 0 0 L"), &direction);
   //direction->get_Value(&value);
   //TRY_TEST(IsEqual(value, 3 * M_PI / 4 + ToRadians(15)), true);

   //direction.Release();
   //alignment->GetDirection(CComVariant(50.0), CComBSTR("15 0 0 R"), &direction);
   //direction->get_Value(&value);
   //TRY_TEST(IsEqual(value, 3 * M_PI / 4 - ToRadians(15)), true);

   //direction.Release();
   //alignment->GetDirection(CComVariant(100.0), CComBSTR("N 45 W"), &direction);
   //direction->get_Value(&value);
   //TRY_TEST(IsEqual(value, 3 * M_PI / 4), true);

   //direction.Release();
   //alignment->GetDirection(CComVariant(100.0), CComBSTR("S 45 W"), &direction);
   //direction->get_Value(&value);
   //TRY_TEST(IsEqual(value, 5 * M_PI / 4), true);

   //direction.Release();
   //alignment->GetDirection(CComVariant(100.0), CComBSTR("N 45 E"), &direction);
   //direction->get_Value(&value);
   //TRY_TEST(IsEqual(value, M_PI / 4), true);

   //direction.Release();
   //alignment->GetDirection(CComVariant(100.0), CComBSTR("S 45 E"), &direction);
   //direction->get_Value(&value);
   //TRY_TEST(IsEqual(value, 3 * M_PI / 4), true);


   ////
   //// _EnumAlignmentElements
   //alignment->Clear();
   //alignment->AddEx(point);
   //alignment->AddEx(hc);
   //CComPtr<IEnumPathElements> pEnum;
   //TRY_TEST(alignment->get__EnumAlignmentElements(nullptr),E_POINTER);
   //TRY_TEST(alignment->get__EnumAlignmentElements(&pEnum),S_OK);

   //// Test ISupportErrorInfo
   //CComQIPtr<ISupportErrorInfo> eInfo(alignment);
   //TRY_TEST( eInfo != nullptr, true );
   //TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IAlignment ), S_OK );
   //TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

   //// Test IObjectSafety
   //TRY_TEST( TestIObjectSafety(CLSID_Alignment,IID_IAlignment,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);


   /// Additional Tests
   CTestAlignment1::Test();
   CTestAlignment2::Test();
   CTestAlignment3::Test();
}
