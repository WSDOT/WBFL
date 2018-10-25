///////////////////////////////////////////////////////////////////////
// COGOTest - Test Driver for Coordinate Geometry Library
// Copyright © 1999-2014  Washington State Department of Transportation
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

   // Create a Alignment point
   CComPtr<IPoint2d> point;
   point.CoCreateInstance(CLSID_Point2d);
   point->Move(10,20);

   // Create a path element and assign the Alignment point to it
   CComPtr<IPathElement> element;
   element.CoCreateInstance(CLSID_PathElement);
   element->putref_Value(point);

   // add it to the Alignment
   TRY_TEST(alignment->Add(NULL),E_INVALIDARG);
   TRY_TEST(alignment->Add(element),S_OK);

   //
   // Test AddEx
   //

   // create a new point
   point.Release();
   point.CoCreateInstance(CLSID_Point2d);
   point->Move(20,30);

   // add it to the Alignment
   TRY_TEST(alignment->AddEx(NULL),E_INVALIDARG);
   //TRY_TEST(alignment->AddEx(alignment),COGO_E_PATHELEMENTTYPE); // alignment/paths are now valid path element types
   TRY_TEST(alignment->AddEx(point), S_OK);

   // create a horz curve
   CComPtr<IHorzCurve> hc;
   hc.CoCreateInstance(CLSID_HorzCurve);
   point.Release();
   hc->get_PBT(&point);
   point->Move(100,100);

   // add it to the Alignment
   TRY_TEST(alignment->AddEx(hc), S_OK);

   //
   // Test Count
   //
   CollectionIndexType count;
   TRY_TEST(alignment->get_Count(NULL),E_POINTER);
   TRY_TEST(alignment->get_Count(&count),S_OK);
   TRY_TEST(count,3);

   //
   // Test Item
   //

   // make sure items are sorted properly
   element.Release();
   TRY_TEST(alignment->get_Item(-1,&element),E_INVALIDARG);
   TRY_TEST(alignment->get_Item(100,&element),E_INVALIDARG);
   TRY_TEST(alignment->get_Item(0,NULL),E_POINTER);
   TRY_TEST(alignment->get_Item(0,&element),S_OK);
   PathElementType type;
   element->get_Type(&type);
   TRY_TEST(type,petPoint);
   CComPtr<IUnknown> dispVal;
   element->get_Value(&dispVal);
   point.Release();
   dispVal->QueryInterface(&point);
   Float64 x,y;
   point->get_X(&x);
   point->get_Y(&y);
   TRY_TEST(IsEqual(x,10.0),true);
   TRY_TEST(IsEqual(y,20.0),true);

   element.Release();
   TRY_TEST(alignment->get_Item(1,&element),S_OK);
   element->get_Type(&type);
   TRY_TEST(type,petPoint);
   dispVal.Release();
   element->get_Value(&dispVal);
   point.Release();
   dispVal->QueryInterface(&point);
   point->get_X(&x);
   point->get_Y(&y);
   TRY_TEST(IsEqual(x,20.0),true);
   TRY_TEST(IsEqual(y,30.0),true);

   element.Release();
   TRY_TEST(alignment->get_Item(2,&element),S_OK);
   element->get_Type(&type);
   TRY_TEST(type,petHorzCurve);
   dispVal.Release();
   element->get_Value(&dispVal);
   hc.Release();
   dispVal->QueryInterface(&hc);
   point.Release();
   hc->get_PBT(&point);
   point->get_X(&x);
   point->get_Y(&y);
   TRY_TEST(IsEqual(x,100.0),true);
   TRY_TEST(IsEqual(y,100.0),true);

   TRY_TEST(alignment->putref_Item(1,NULL),E_INVALIDARG);
   TRY_TEST(alignment->putref_Item(-1,element),E_INVALIDARG);
   TRY_TEST(alignment->putref_Item(100,element),E_INVALIDARG);
   TRY_TEST(alignment->putref_Item(1,element),S_OK);
   element.Release();
   TRY_TEST(alignment->get_Item(1,&element),S_OK);
   element->get_Type(&type);
   TRY_TEST(type,petHorzCurve);

   //
   // Test Insert and InsertEx
   //
   TRY_TEST(alignment->Insert(1,NULL),E_INVALIDARG);
   TRY_TEST(alignment->Insert(-1,element),E_INVALIDARG);
   TRY_TEST(alignment->Insert(100,element),E_INVALIDARG);
   TRY_TEST(alignment->Insert(1,element),S_OK);

   TRY_TEST(alignment->InsertEx(1,NULL),E_INVALIDARG);
   //TRY_TEST(alignment->InsertEx(1,alignment),COGO_E_PATHELEMENTTYPE); // alignment/path are now valid path elements
   TRY_TEST(alignment->InsertEx(-1,point),E_INVALIDARG);
   TRY_TEST(alignment->InsertEx(100,point),E_INVALIDARG);
   TRY_TEST(alignment->InsertEx(1,point),S_OK);

   //
   // Test Remove
   //
   point.Release();
   hc->get_PBT(&point);
   TRY_TEST(alignment->Remove(CComVariant()),E_INVALIDARG);
   TRY_TEST(alignment->Remove(CComVariant(alignment)),E_INVALIDARG);
   TRY_TEST(alignment->Remove(CComVariant(-1)),E_INVALIDARG);
   TRY_TEST(alignment->Remove(CComVariant(100)),E_INVALIDARG);
   TRY_TEST(alignment->Remove(CComVariant(point)),S_OK);
   TRY_TEST(alignment->Remove(CComVariant(hc)),S_OK); // Remove the vert curve
   TRY_TEST(alignment->Remove(CComVariant(1)),S_OK);  // Remove the element at index 1

   alignment->get_Count(&count);
   TRY_TEST(count,2);

   //
   // Test Profile
   //
   CComPtr<IProfile> profile;
   TRY_TEST(alignment->get_Profile(NULL),E_POINTER);
   TRY_TEST(alignment->get_Profile(&profile),S_OK);
   TRY_TEST(alignment->putref_Profile(NULL),E_INVALIDARG);
   TRY_TEST(alignment->putref_Profile(profile),S_OK);

   //
   // Test Clear
   //
   TRY_TEST(alignment->Clear(),S_OK);
   alignment->get_Count(&count);
   TRY_TEST(count,0);

   //
   // RefStation
   CComPtr<IStation> station;
   Float64 stationVal;
   TRY_TEST(alignment->get_RefStation(NULL),E_POINTER);
   TRY_TEST(alignment->get_RefStation(&station),S_OK);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,0.0),true);
   TRY_TEST(alignment->put_RefStation(CComVariant(100.0)),S_OK);
   station.Release();
   TRY_TEST(alignment->get_RefStation(&station),S_OK);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,100.0),true);
   TRY_TEST(alignment->put_RefStation(CComVariant("12+34.56")),E_INVALIDARG);

   //
   // _EnumAlignmentElements
   alignment->Clear();
   alignment->AddEx(point);
   alignment->AddEx(hc);
   CComPtr<IEnumPathElements> pEnum;
   TRY_TEST(alignment->get__EnumPathElements(NULL),E_POINTER);
   TRY_TEST(alignment->get__EnumPathElements(&pEnum),S_OK);

   // Test PointFactory
   CComPtr<IPoint2dFactory> factory;
   TRY_TEST(alignment->get_PointFactory(NULL),E_POINTER);
   TRY_TEST(alignment->get_PointFactory(&factory),S_OK);
   TRY_TEST(alignment->putref_PointFactory(NULL),E_INVALIDARG);
   TRY_TEST(alignment->putref_PointFactory(factory),S_OK);

   // Test Events
   CComObject<CTestAlignment>* pTestAlignment;
   CComObject<CTestAlignment>::CreateInstance(&pTestAlignment);
   pTestAlignment->AddRef();

   DWORD dwCookie;
   CComPtr<IUnknown> punk(pTestAlignment);
   TRY_TEST(AtlAdvise(alignment,punk,IID_IPathEvents,&dwCookie),S_OK);

   // Create a new "clean" horizontal curve
   hc.Release();
   hc.CoCreateInstance(CLSID_HorzCurve);

   pTestAlignment->InitEventTest();
   alignment->Clear();
   TRY_TEST(pTestAlignment->PassedEventTest(), true );

   pTestAlignment->InitEventTest();
   alignment->AddEx(hc);
   TRY_TEST(pTestAlignment->PassedEventTest(), true );

   pTestAlignment->InitEventTest();
   hc->putref_PBT(point);
   TRY_TEST(pTestAlignment->PassedEventTest(), true );

   pTestAlignment->InitEventTest();
   alignment->AddEx(point);
   TRY_TEST(pTestAlignment->PassedEventTest(), true );

   pTestAlignment->InitEventTest();
   point->put_X(50);
   TRY_TEST(pTestAlignment->PassedEventTest(), true );

   profile.Release();
   alignment->get_Profile(&profile);
   pTestAlignment->InitEventTest();
   profile->Clear();
   TRY_TEST(pTestAlignment->PassedEventTest(), true);

   pTestAlignment->InitEventTest();
   alignment->putref_Profile(profile);
   TRY_TEST(pTestAlignment->PassedEventTest(), true);

   pTestAlignment->InitEventTest();
   profile->Clear(); // make sure events are still being sinked properly
   TRY_TEST(pTestAlignment->PassedEventTest(), true);

   TRY_TEST(AtlUnadvise(alignment,IID_IPathEvents,dwCookie),S_OK);
   pTestAlignment->Release();

   // Test ISupportErrorInfo
   CComQIPtr<ISupportErrorInfo> eInfo(alignment);
   TRY_TEST( eInfo != NULL, true );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IAlignment ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

   // Test IObjectSafety
   TRY_TEST( TestIObjectSafety(CLSID_Alignment,IID_IAlignment,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
   TRY_TEST( TestIObjectSafety(CLSID_Alignment,IID_IStructuredStorage2,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);


   /// Additional Tests
   CTestAlignment1::Test();
   CTestAlignment2::Test();
   CTestAlignment3::Test();
}

STDMETHODIMP CTestAlignment::OnPathChanged(IPath* pp)
{
   CComQIPtr<IAlignment> alignment(pp);
   if ( alignment != NULL )
      Pass();

   return S_OK;
}

STDMETHODIMP CTestAlignment::OnProfileChanged(IProfile* profile)
{
   Pass();
   return S_OK;
}
