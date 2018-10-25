///////////////////////////////////////////////////////////////////////
// GenericBridgeTest - Test driver for generic bridge library
// Copyright © 1999-2011  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Library Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// TestBridgeDeck.cpp: implementation of the CTestBridgeDeck class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestBridgeDeck.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestBridgeDeck::CTestBridgeDeck()
{

}

CTestBridgeDeck::~CTestBridgeDeck()
{

}

void CTestBridgeDeck::Test(IUnknown* pUnk)
{
   CComQIPtr<IBridgeDeck> deck(pUnk);
   TRY_TEST(deck != NULL,true);

   // Test default values
   VARIANT_BOOL bComposite;
   TRY_TEST(deck->get_Composite(NULL),E_POINTER);
   TRY_TEST(deck->get_Composite(&bComposite),S_OK);
   TRY_TEST(bComposite,VARIANT_TRUE);

   CComBSTR bstrStage;
   TRY_TEST(deck->get_CompositeStage(NULL),E_POINTER);
   TRY_TEST(deck->get_CompositeStage(&bstrStage),S_OK);
   TRY_TEST(bstrStage.Length(),0);

   bstrStage.Empty();
   TRY_TEST(deck->get_ConstructionStage(NULL),E_POINTER);
   TRY_TEST(deck->get_ConstructionStage(&bstrStage),S_OK);
   TRY_TEST(bstrStage.Length(),0);

   CComPtr<IMaterial> material;
   TRY_TEST(deck->get_Material(NULL),E_POINTER);
   TRY_TEST(deck->get_Material(&material),S_OK);
   TRY_TEST(material != NULL,true);

   Float64 value;
   TRY_TEST(deck->get_WearingSurfaceDensity(NULL),E_POINTER);
   TRY_TEST(deck->get_WearingSurfaceDensity(&value),S_OK);
   TRY_TEST(value,0.0);

   TRY_TEST(deck->get_WearingSurfaceDepth(NULL),E_POINTER);
   TRY_TEST(deck->get_WearingSurfaceDepth(&value),S_OK);
   TRY_TEST(value,0.0);

   // Manipulate values while testing for event handling
   CComObject<CTestBridgeDeck>* pTestBridgeDeck;
   CComObject<CTestBridgeDeck>::CreateInstance(&pTestBridgeDeck);
   pTestBridgeDeck->AddRef();
   
   DWORD dwCookie;
   CComPtr<IUnknown> punk(pTestBridgeDeck);
   TRY_TEST(AtlAdvise(deck,punk,IID_IBridgeDeckEvents,&dwCookie),S_OK);

   pTestBridgeDeck->InitEventTest();
   deck->put_Composite(VARIANT_TRUE);
   TRY_TEST(pTestBridgeDeck->PassedEventTest(), false );

   pTestBridgeDeck->InitEventTest();
   deck->put_Composite(VARIANT_FALSE);
   TRY_TEST(pTestBridgeDeck->PassedEventTest(), true );

   deck->get_Composite(&bComposite);
   TRY_TEST(bComposite,VARIANT_FALSE);
   
   pTestBridgeDeck->InitEventTest();
   TRY_TEST(deck->put_CompositeStage(NULL),E_INVALIDARG);
   TRY_TEST(deck->put_CompositeStage(CComBSTR()),E_INVALIDARG);
   TRY_TEST(pTestBridgeDeck->PassedEventTest(), false );

   pTestBridgeDeck->InitEventTest();
   TRY_TEST(deck->put_CompositeStage(CComBSTR("Stage 2")),S_OK);
   TRY_TEST(pTestBridgeDeck->PassedEventTest(), true );

   bstrStage.Empty();
   deck->get_CompositeStage(&bstrStage);
   TRY_TEST(bstrStage,CComBSTR("Stage 2"));

   pTestBridgeDeck->InitEventTest();
   TRY_TEST(deck->put_ConstructionStage(CComBSTR("Stage 2")),S_OK);
   TRY_TEST(pTestBridgeDeck->PassedEventTest(), true );

   bstrStage.Empty();
   deck->get_ConstructionStage(&bstrStage);
   TRY_TEST(bstrStage,CComBSTR("Stage 2"));

   pTestBridgeDeck->InitEventTest();
   TRY_TEST(deck->put_WearingSurfaceDensity(-10),E_INVALIDARG);
   TRY_TEST(deck->put_WearingSurfaceDensity(0),S_OK);
   TRY_TEST(pTestBridgeDeck->PassedEventTest(), false );

   pTestBridgeDeck->InitEventTest();
   TRY_TEST(deck->put_WearingSurfaceDensity(150),S_OK);
   TRY_TEST(pTestBridgeDeck->PassedEventTest(), true );

   deck->get_WearingSurfaceDensity(&value);
   TRY_TEST(IsEqual(value,150.),true);

   pTestBridgeDeck->InitEventTest();
   TRY_TEST(deck->put_WearingSurfaceDepth(-10),E_INVALIDARG);
   TRY_TEST(deck->put_WearingSurfaceDepth(0),S_OK);
   TRY_TEST(pTestBridgeDeck->PassedEventTest(), false );

   pTestBridgeDeck->InitEventTest();
   TRY_TEST(deck->put_WearingSurfaceDepth(150),S_OK);
   TRY_TEST(pTestBridgeDeck->PassedEventTest(), true );

   deck->get_WearingSurfaceDepth(&value);
   TRY_TEST(IsEqual(value,150.),true);

   CComPtr<IMaterial> material2;
   material2.CoCreateInstance(CLSID_Material);

   pTestBridgeDeck->InitEventTest();
   TRY_TEST(deck->put_Material(NULL),E_INVALIDARG);
   TRY_TEST(deck->put_Material(material2),S_OK);
   TRY_TEST(pTestBridgeDeck->PassedEventTest(), true );

   CComPtr<IMaterial> testmat;
   deck->get_Material(&testmat);
   TRY_TEST(testmat.IsEqualObject(material2),false);

   testmat.Release();
   deck->get_Material(&testmat);
   TRY_TEST(testmat.IsEqualObject(material),false);

   // Done with events
   TRY_TEST(AtlUnadvise(deck,IID_IBridgeDeckEvents,dwCookie),S_OK);
   pTestBridgeDeck->Release();

   ///////////////////////////////////////
   // Test Error Info
   CComQIPtr<ISupportErrorInfo> eInfo(deck);
   TRY_TEST( eInfo != 0, true );

   // Interfaces that should be supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IBridgeDeck ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );

   // Interface that is not supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

   // Test IObjectSafety
   TRY_TEST( TestIObjectSafety(deck,IID_IBridgeDeck,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
   TRY_TEST( TestIObjectSafety(deck,IID_IStructuredStorage2,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
}


STDMETHODIMP CTestBridgeDeck::OnBridgeDeckChanged(IBridgeDeck* pDeck)
{
   Pass();
   return S_OK;
}