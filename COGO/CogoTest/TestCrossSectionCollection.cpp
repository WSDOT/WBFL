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

// TestCrossSectionCollection.cpp: implementation of the CTestCrossSectionCollection class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestCrossSectionCollection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestCrossSectionCollection::CTestCrossSectionCollection()
{

}

void CTestCrossSectionCollection::Test()
{
   CComPtr<ICrossSectionCollection> pColl;
   TRY_TEST(pColl.CoCreateInstance( CLSID_CrossSectionCollection ), S_OK);

   CollectionIndexType count;
   TRY_TEST(pColl->get_Count(NULL),E_POINTER);
   TRY_TEST(pColl->get_Count(&count),S_OK);
   TRY_TEST(count,0);

   CComPtr<ICrossSection> cs1;
   cs1.CoCreateInstance(CLSID_CrossSection);
   cs1->put_Station(CComVariant(100));
   cs1->put_LeftCrownSlope(-0.02);
   cs1->put_RightCrownSlope(-0.02);

   CComPtr<ICrossSection> cs2;
   cs2.CoCreateInstance(CLSID_CrossSection);
   cs2->put_Station(CComVariant(200));
   cs2->put_CrownPointOffset(5);
   cs2->put_LeftCrownSlope(-0.04);
   cs2->put_RightCrownSlope(0.04);

   CComPtr<ICrossSectionFactory> factory;
   TRY_TEST(pColl->get_Factory(NULL),E_POINTER);
   TRY_TEST(pColl->get_Factory(&factory),S_OK);
   TRY_TEST( factory != NULL, true );
   TRY_TEST(pColl->putref_Factory(NULL),E_INVALIDARG);
   TRY_TEST(pColl->putref_Factory(factory),S_OK);

   //
   // Test AddEx method
   //
   TRY_TEST(pColl->AddEx(NULL),E_INVALIDARG);
   TRY_TEST(pColl->AddEx(cs2),S_OK); // add in reverse order... Check sorting
   TRY_TEST(pColl->AddEx(cs1),S_OK);
   
   CComPtr<ICrossSection> cs;
   TRY_TEST(pColl->get_Item(1,&cs),S_OK);
   TRY_TEST(pColl->get_Count(&count),S_OK);
   TRY_TEST(count,2);

   CComPtr<IStation> objStation;
   Float64 sta, cpo, left, right;
   cs->get_Station(&objStation);
   objStation->get_Value(&sta);
   TRY_TEST(IsEqual(sta,200.0),true);

   //
   // Test Add method
   //
   TRY_TEST(pColl->Add(CComVariant(150),10,-0.04,0.04,NULL),S_OK);


   // Test Item property
   cs.Release();
   TRY_TEST(pColl->get_Item(-1,&cs),E_INVALIDARG);
   TRY_TEST(pColl->get_Item(1,NULL),E_POINTER);
   TRY_TEST(pColl->get_Item(1,&cs),S_OK);
   TRY_TEST(pColl->putref_Item(-1,cs),E_INVALIDARG);
   TRY_TEST(pColl->putref_Item(100,cs),E_INVALIDARG);
   TRY_TEST(pColl->putref_Item(2,NULL),E_INVALIDARG);
   TRY_TEST(pColl->putref_Item(2,cs),S_OK);

   //
   // Test Remove
   //
   TRY_TEST(pColl->Remove(-1),E_INVALIDARG);
   TRY_TEST(pColl->Remove(1),S_OK);

   //
   // Test Clear
   //
   pColl->get_Count(&count);
   TRY_TEST(count,2);
   TRY_TEST( pColl->Clear(), S_OK );
   pColl->get_Count(&count);
   TRY_TEST(count,0);
   
   //
   // Test _Enum
   //
   pColl->Clear();
   pColl->AddEx(cs1);
   pColl->AddEx(cs2);
   CComPtr<IEnumCrossSections> pEnum;
   TRY_TEST(pColl->get__EnumCrossSections(NULL), E_POINTER );
   TRY_TEST( pColl->get__EnumCrossSections(&pEnum), S_OK );

   ULONG fetched;
   CComPtr<ICrossSection> section;
   TRY_TEST(pEnum->Next(1,&section,&fetched ),S_OK);
   objStation.Release();
   section->get_Station(&objStation);
   objStation->get_Value(&sta);
   TRY_TEST(IsEqual(sta,100.),true);

   section.Release();
   TRY_TEST(pEnum->Next(1,&section,&fetched ),S_OK);
   objStation.Release();
   section->get_Station(&objStation);
   objStation->get_Value(&sta);
   TRY_TEST(IsEqual(sta,200.),true);

   section.Release();
   TRY_TEST(pEnum->Next(1,&section,&fetched ),S_FALSE);

   //
   // Test CreateCrossSection
   //
   pColl->Clear();
   pColl->AddEx(cs1);
   pColl->AddEx(cs2);
   cs.Release();
   TRY_TEST(pColl->CreateCrossSection(CComVariant(50),NULL),E_POINTER);

   // a station before the first cross section
   TRY_TEST(pColl->CreateCrossSection(CComVariant(50),&cs),S_OK);
   objStation.Release();
   cs->get_Station(&objStation);
   objStation->get_Value(&sta);
   cs->get_CrownPointOffset(&cpo);
   cs->get_LeftCrownSlope(&left);
   cs->get_RightCrownSlope(&right);
   TRY_TEST(IsEqual(sta,50.0),true);
   TRY_TEST(IsEqual(cpo,0.0),true);
   TRY_TEST(IsEqual(left,-0.02),true);
   TRY_TEST(IsEqual(right,-0.02),true);

   // a station after the last cross section
   cs.Release();
   TRY_TEST(pColl->CreateCrossSection(CComVariant(250),&cs),S_OK);
   objStation.Release();
   cs->get_Station(&objStation);
   objStation->get_Value(&sta);
   cs->get_CrownPointOffset(&cpo);
   cs->get_LeftCrownSlope(&left);
   cs->get_RightCrownSlope(&right);
   TRY_TEST(IsEqual(sta,250.0),true);
   TRY_TEST(IsEqual(cpo,5.0),true);
   TRY_TEST(IsEqual(left,-0.04),true);
   TRY_TEST(IsEqual(right, 0.04),true);

   // a station between the first and last cross sections
   cs.Release();
   TRY_TEST(pColl->CreateCrossSection(CComVariant(150),&cs),S_OK);
   objStation.Release();
   cs->get_Station(&objStation);
   objStation->get_Value(&sta);
   cs->get_CrownPointOffset(&cpo);
   cs->get_LeftCrownSlope(&left);
   cs->get_RightCrownSlope(&right);
   TRY_TEST(IsEqual(sta,150.0),true);
   TRY_TEST(IsEqual(cpo,2.5),true);
   TRY_TEST(IsEqual(left,-0.03),true);
   TRY_TEST(IsEqual(right,0.01),true);

   //
   // Test CrownSlope
   //
   pColl->Clear();
   Float64 slope;
   TRY_TEST(pColl->CrownSlope(CComVariant(150),10.0,NULL),E_POINTER);
   TRY_TEST(pColl->CrownSlope(CComVariant(150),10,&slope),S_OK); // empty container
   TRY_TEST(IsZero(slope),true);

   pColl->AddEx(cs1);
   pColl->AddEx(cs2);

   TRY_TEST(pColl->CrownSlope(CComVariant(150),5.0,&slope),S_OK);
   TRY_TEST(IsEqual(slope,0.01),true);

   TRY_TEST(pColl->CrownSlope(CComVariant(150),-5.0,&slope),S_OK);
   TRY_TEST(IsEqual(slope,-0.03),true);

   //
   // Test Events
   //
   pColl->Clear(); // start with an empty container

   CComObject<CTestCrossSectionCollection>* pTestEvents;
   CComObject<CTestCrossSectionCollection>::CreateInstance(&pTestEvents);
   pTestEvents->AddRef();

   DWORD dwCookie;
   CComPtr<IUnknown> punk(pTestEvents);
   TRY_TEST(AtlAdvise(pColl,punk,IID_ICrossSectionCollectionEvents,&dwCookie),S_OK);

   // Add a CrossSection to the collection
   pTestEvents->InitEventTest();
   pColl->AddEx(cs1);
   TRY_TEST(pTestEvents->PassedEventTest(),true);

   pColl->AddEx(cs2);

   // Move a CrossSection... Event should fire... container should re-sort
   pTestEvents->InitEventTest();
   cs1->put_Station(CComVariant(300));
   TRY_TEST(pTestEvents->PassedEventTest(),true);
   cs.Release();
   pColl->get_Item(0,&cs);
   objStation.Release();
   cs->get_Station(&objStation);
   objStation->get_Value(&sta);
   TRY_TEST(IsEqual(sta,200.),true);

   pTestEvents->InitEventTest();
   cs1->put_CrownPointOffset(5);
   TRY_TEST(pTestEvents->PassedEventTest(),true);

   pTestEvents->InitEventTest();
   cs1->put_LeftCrownSlope(-0.03);
   TRY_TEST(pTestEvents->PassedEventTest(),true);

   pTestEvents->InitEventTest();
   cs1->put_RightCrownSlope(-0.03);
   TRY_TEST(pTestEvents->PassedEventTest(),true);

   // Remove a CrossSection
   pTestEvents->InitEventTest();
   pColl->Remove(1);
   TRY_TEST(pTestEvents->PassedEventTest(),true);

   // Clear
   pTestEvents->InitEventTest();
   pColl->Clear();
   TRY_TEST(pTestEvents->PassedEventTest(),true);

   TRY_TEST(AtlUnadvise(pColl,IID_ICrossSectionCollectionEvents,dwCookie),S_OK);
   pTestEvents->Release();

   //
   // Test ISupportErrorInfo
   //
   CComQIPtr<ISupportErrorInfo> eInfo(pColl);
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ICrossSectionCollection ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

   // Test IObjectSafety
   TRY_TEST( TestIObjectSafety(CLSID_CrossSectionCollection,IID_ICrossSectionCollection,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
   TRY_TEST( TestIObjectSafety(CLSID_CrossSectionCollection,IID_IStructuredStorage2,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
}

STDMETHODIMP CTestCrossSectionCollection::OnCrossSectionChanged(ICrossSection* cs)
{
//   MessageBox(NULL,"CrossSectionChanged","Event",MB_OK);
   Pass();

   return S_OK;
}

STDMETHODIMP CTestCrossSectionCollection::OnCrossSectionAdded(ICrossSection* cs)
{
//   MessageBox(NULL,"CrossSectionAdded","Event",MB_OK);
   Pass();

   return S_OK;
}

STDMETHODIMP CTestCrossSectionCollection::OnCrossSectionRemoved()
{
//   MessageBox(NULL,"CrossSectionRemoved","Event",MB_OK);
   Pass();

   return S_OK;
}

STDMETHODIMP CTestCrossSectionCollection::OnCrossSectionsCleared()
{
//   MessageBox(NULL,"CrossSectionCleared","Event",MB_OK);
   Pass();
   return S_OK;
}
