///////////////////////////////////////////////////////////////////////
// COGOTest - Test Driver for Coordinate Geometry Library
// Copyright © 1999-2016  Washington State Department of Transportation
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

// TestHorzCurveCollection.cpp: implementation of the CTestHorzCurveCollection class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestHorzCurveCollection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestHorzCurveCollection::CTestHorzCurveCollection()
{

}

void CTestHorzCurveCollection::Test()
{
   CComPtr<IHorzCurveCollection> pColl;
   TRY_TEST(pColl.CoCreateInstance( CLSID_HorzCurveCollection ), S_OK);

   CollectionIndexType count;
   TRY_TEST(pColl->get_Count(NULL),E_POINTER);
   TRY_TEST(pColl->get_Count(&count),S_OK);
   TRY_TEST(count,0);

   CComPtr<IPoint2d> pbt, pi, pft;
   pbt.CoCreateInstance(CLSID_Point2d);
   pi.CoCreateInstance(CLSID_Point2d);
   pft.CoCreateInstance(CLSID_Point2d);

   pbt->Move(0,1000);
   pi->Move(700,1000);
   pft->Move(1000,700);

   CComPtr<IHorzCurveFactory> factory;
   TRY_TEST(pColl->get_Factory(NULL),E_POINTER);
   TRY_TEST(pColl->get_Factory(&factory),S_OK);
   TRY_TEST( factory != NULL, true );
   TRY_TEST(pColl->putref_Factory(NULL),E_INVALIDARG);
   TRY_TEST(pColl->putref_Factory(factory),S_OK);

   //
   // Test Add method
   //
   TRY_TEST(pColl->Add(1,NULL,pi,pft,500,100,200,NULL),  E_INVALIDARG);
   TRY_TEST(pColl->Add(1,pbt,NULL,pft,500,100,200,NULL), E_INVALIDARG);
   TRY_TEST(pColl->Add(1,pbt,pi,NULL,500,100,200,NULL),  E_INVALIDARG);
   TRY_TEST(pColl->Add(1,pbt,pi,pft,-500,100,200,NULL),  E_INVALIDARG);
   TRY_TEST(pColl->Add(1,pbt,pi,pft,0,100,200,NULL),     E_INVALIDARG);
   TRY_TEST(pColl->Add(1,pbt,pi,pft,500,-100,200,NULL),  E_INVALIDARG);
   TRY_TEST(pColl->Add(1,pbt,pi,pft,500,100,-200,NULL),  E_INVALIDARG);

   TRY_TEST(pColl->Add(1,pbt,pi,pft,500,100,200,NULL),S_OK);
   TRY_TEST(pColl->Add(1,pbt,pi,pft,500,100,200,NULL),COGO_E_HORZCURVEALREADYDEFINED);
   CComPtr<IHorzCurve> hc;
   TRY_TEST(pColl->get_Item(1,&hc),S_OK);
   TRY_TEST(pColl->get_Count(&count),S_OK);
   TRY_TEST(count,1);

   //
   // Test AddEx method
   //
   TRY_TEST(pColl->AddEx(0,NULL),E_INVALIDARG);


   // Test Item property
   hc.Release();
   TRY_TEST(pColl->get_Item(-1,&hc),COGO_E_HORZCURVENOTFOUND);
   TRY_TEST(pColl->get_Item(1,NULL),E_POINTER);
   TRY_TEST(pColl->get_Item(1,&hc),S_OK);

   //
   // Test Remove
   //
   TRY_TEST(pColl->Remove(-1),COGO_E_HORZCURVENOTFOUND);
   TRY_TEST(pColl->Remove(1),S_OK);

   //
   // Test Clear
   //
   pColl->Add(1,pbt,pi,pft,500,100,200,NULL);
   pColl->get_Count(&count);
   TRY_TEST(count,1);
   TRY_TEST( pColl->Clear(), S_OK );
   pColl->get_Count(&count);
   TRY_TEST(count,0);

   //
   // Test putref_Item
   //
   TRY_TEST(pColl->AddEx(1,hc),S_OK);

   TRY_TEST(pColl->putref_Item(1,NULL),E_INVALIDARG);
   TRY_TEST(pColl->putref_Item(-1,hc),COGO_E_HORZCURVENOTFOUND);
   TRY_TEST(pColl->putref_Item(1,hc),S_OK);

   //
   // Test FindKey
   //
   CogoElementKey key;
   TRY_TEST(pColl->FindKey(NULL,&key),E_INVALIDARG);
   TRY_TEST(pColl->FindKey(hc,NULL),E_POINTER);
   TRY_TEST(pColl->FindKey(hc,&key),S_OK);
   TRY_TEST(key,1);

   //
   // Test Key
   //
   pColl->Clear();
   pColl->Add(1,pbt,pi,pft,500,100,200,NULL);
   pColl->Add(2,pbt,pi,pft,500,100,200,NULL);
   pColl->Add(3,pbt,pi,pft,500,100,200,NULL);
   pColl->Add(4,pbt,pi,pft,500,100,200,NULL);

   TRY_TEST(pColl->Key(-1,&key),E_INVALIDARG);
   TRY_TEST(pColl->Key(500,&key),E_INVALIDARG);
   TRY_TEST(pColl->Key(3,NULL),E_POINTER);
   TRY_TEST(pColl->Key(3,&key),S_OK);
   TRY_TEST(key,4);
   

   //
   // Test _Enum
   //
   CComPtr<IHorzCurve> hcurve[4];
   pColl->Clear();
   pColl->Add(1,pbt,pi,pft,500,100,200,NULL);
   pColl->Add(2,pbt,pi,pft,500,100,200,NULL);
   pColl->Add(3,pbt,pi,pft,500,100,200,NULL);
   pColl->Add(4,pbt,pi,pft,500,100,200,NULL);
   pColl->get_Item(1,&hcurve[0]);
   pColl->get_Item(2,&hcurve[1]);
   pColl->get_Item(3,&hcurve[2]);
   pColl->get_Item(4,&hcurve[3]);
   CComPtr<IEnumKeys> pEnum;
   TRY_TEST(pColl->get__EnumKeys(NULL), E_POINTER );
   TRY_TEST( pColl->get__EnumKeys(&pEnum), S_OK );

   ULONG fetched;
   CogoElementKey target_key = 1;
   while( pEnum->Next(1,&key,&fetched ) == S_OK )
   {
      TRY_TEST(key,target_key++);
   }
   
   //
   // Test _EnumHorzCurves
   //
   hcurve[0].Release();
   hcurve[1].Release();
   hcurve[2].Release();
   hcurve[3].Release();
   pColl->Clear();
   pColl->Add(1,pbt,pi,pft,500,100,200,NULL);
   pColl->Add(2,pbt,pi,pft,500,100,200,NULL);
   pColl->Add(3,pbt,pi,pft,500,100,200,NULL);
   pColl->Add(4,pbt,pi,pft,500,100,200,NULL);
   pColl->get_Item(1,&hcurve[0]);
   pColl->get_Item(2,&hcurve[1]);
   pColl->get_Item(3,&hcurve[2]);
   pColl->get_Item(4,&hcurve[3]);
   CComPtr<IEnumHorzCurves> pEnumHorzCurves;
   TRY_TEST(pColl->get__EnumHorzCurves(NULL), E_POINTER );
   TRY_TEST( pColl->get__EnumHorzCurves(&pEnumHorzCurves), S_OK );

   for ( long i = 0; i < 4; i++ )
   {
      CComPtr<IHorzCurve> horzCurve;
      pEnumHorzCurves->Next(1,&horzCurve,&fetched);
      TRY_TEST(horzCurve.IsEqualObject(hcurve[i]),true);
   }

   //
   // Test Events
   //
   pColl->Clear(); // start with an empty container

   CComObject<CTestHorzCurveCollection>* pTestEvents;
   CComObject<CTestHorzCurveCollection>::CreateInstance(&pTestEvents);
   pTestEvents->AddRef();

   DWORD dwCookie;
   CComPtr<IUnknown> punk(pTestEvents);
   TRY_TEST(AtlAdvise(pColl,punk,IID_IHorzCurveCollectionEvents,&dwCookie),S_OK);

   // Add a HorzCurve to the collection
   pTestEvents->InitEventTest(1);
   pColl->AddEx(1,hc);
   TRY_TEST(pTestEvents->PassedEventTest(),true);

   // Move a HorzCurve... Event should fire
   pTestEvents->InitEventTest(1);
   hc->put_Radius(150);
   TRY_TEST(pTestEvents->PassedEventTest(),true);

   // Remove a HorzCurve
   pTestEvents->InitEventTest(1);
   pColl->Remove(1);
   TRY_TEST(pTestEvents->PassedEventTest(),true);

//   // Change HorzCurve references
//   pTestEvents->InitEventTest(2);
//   pColl->putref_Item(2,p4);
//   TRY_TEST(pTestEvents->PassedEventTest(),true);

   // Clear
   pTestEvents->InitEventTest(-1);
   pColl->Clear();
   TRY_TEST(pTestEvents->PassedEventTest(),true);

   TRY_TEST(AtlUnadvise(pColl,IID_IHorzCurveCollectionEvents,dwCookie),S_OK);
   pTestEvents->Release();

   //
   // Test ISupportErrorInfo
   //
   CComQIPtr<ISupportErrorInfo> eInfo(pColl);
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IHorzCurveCollection ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

   // Test IObjectSafety
   TRY_TEST( TestIObjectSafety(CLSID_HorzCurveCollection,IID_IHorzCurveCollection,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
   TRY_TEST( TestIObjectSafety(CLSID_HorzCurveCollection,IID_IStructuredStorage2,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
}

STDMETHODIMP CTestHorzCurveCollection::OnHorzCurveChanged(CogoElementKey key,IHorzCurve* hc)
{
//   MessageBox(NULL,"HorzCurveChanged","Event",MB_OK);
   if ( key == m_expectedKey )
      Pass();

   return S_OK;
}

STDMETHODIMP CTestHorzCurveCollection::OnHorzCurveAdded(CogoElementKey key,IHorzCurve* hc)
{
//   MessageBox(NULL,"HorzCurveAdded","Event",MB_OK);
   if ( key == m_expectedKey )
      Pass();

   return S_OK;
}

STDMETHODIMP CTestHorzCurveCollection::OnHorzCurveRemoved(CogoElementKey key)
{
//   MessageBox(NULL,"HorzCurveRemoved","Event",MB_OK);
   if ( key == m_expectedKey )
      Pass();

   return S_OK;
}

STDMETHODIMP CTestHorzCurveCollection::OnHorzCurvesCleared()
{
//   MessageBox(NULL,"HorzCurveCleared","Event",MB_OK);
   Pass();
   return S_OK;
}
