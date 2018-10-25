///////////////////////////////////////////////////////////////////////
// GenericBridgeTest - Test driver for generic bridge library
// Copyright © 1999-2014, Washington State Department of Transportation, All Rights Reserved
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

// TestPrecastSlab.cpp: implementation of the CTestPrecastSlab class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestPrecastSlab.h"
#include "TestBridgeDeck.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestPrecastSlab::CTestPrecastSlab()
{

}

CTestPrecastSlab::~CTestPrecastSlab()
{

}

void CTestPrecastSlab::Test()
{
   HRESULT hr;
   CComPtr<IPrecastSlab> slab;
   hr = slab.CoCreateInstance(CLSID_PrecastSlab);
   TRY_TEST(hr,S_OK);

   CTestBridgeDeck::Test(slab);

   //////////////////////
   // Test default values
   Float64 value;
   TRY_TEST(slab->get_Fillet(NULL),E_POINTER);
   TRY_TEST(slab->get_Fillet(&value),S_OK);
   TRY_TEST(IsZero(value),true);

   TRY_TEST(slab->get_PanelDepth(NULL),E_POINTER);
   TRY_TEST(slab->get_PanelDepth(&value),S_OK);
   TRY_TEST(IsZero(value),true);

   TRY_TEST(slab->get_CastDepth(NULL),E_POINTER);
   TRY_TEST(slab->get_CastDepth(&value),S_OK);
   TRY_TEST(IsZero(value),true);

   TRY_TEST(slab->get_OverhangDepth(NULL),E_POINTER);
   TRY_TEST(slab->get_OverhangDepth(&value),S_OK);
   TRY_TEST(IsZero(value),true);

   DeckOverhangTaper taper;
   TRY_TEST(slab->get_OverhangTaper(NULL),E_POINTER);
   TRY_TEST(slab->get_OverhangTaper(&taper),S_OK);
   TRY_TEST(taper,dotNone);

   CComPtr<IPath> path;
   TRY_TEST(slab->get_LeftOverhangPath(NULL),E_POINTER);
   TRY_TEST(slab->get_LeftOverhangPath(&path),E_FAIL);
   TRY_TEST(path == NULL,true);

   path.Release();
   TRY_TEST(slab->get_RightOverhangPath(NULL),E_POINTER);
   TRY_TEST(slab->get_RightOverhangPath(&path),E_FAIL);
   TRY_TEST(path == NULL,true);

   CComBSTR bstrStage;
   TRY_TEST(slab->get_CastingStage(NULL),E_POINTER);
   TRY_TEST(slab->get_CastingStage(&bstrStage),S_OK);
   TRY_TEST(bstrStage.Length(),0);

   ///////////////////////////////////////
   // Test Set with event sink
   CComObject<CTestPrecastSlab>* pTestPrecastSlab;
   CComObject<CTestPrecastSlab>::CreateInstance(&pTestPrecastSlab);
   pTestPrecastSlab->AddRef();
   
   DWORD dwCookie;
   CComPtr<IUnknown> punk(pTestPrecastSlab);
   TRY_TEST(AtlAdvise(slab,punk,IID_IBridgeDeckEvents,&dwCookie),S_OK);

   pTestPrecastSlab->InitEventTest();
   TRY_TEST(slab->put_Fillet(-10),E_INVALIDARG);
   TRY_TEST(slab->put_Fillet(0),S_OK);
   TRY_TEST(pTestPrecastSlab->PassedEventTest(), false );

   pTestPrecastSlab->InitEventTest();
   TRY_TEST(slab->put_Fillet(10),S_OK);
   TRY_TEST(pTestPrecastSlab->PassedEventTest(), true );

   slab->get_Fillet(&value);
   TRY_TEST(IsEqual(value,10.0),true);
  
   pTestPrecastSlab->InitEventTest();
   TRY_TEST(slab->put_CastDepth(-10),E_INVALIDARG);
   TRY_TEST(slab->put_CastDepth(0),S_OK);
   TRY_TEST(pTestPrecastSlab->PassedEventTest(), false );
  
   pTestPrecastSlab->InitEventTest();
   TRY_TEST(slab->put_PanelDepth(-10),E_INVALIDARG);
   TRY_TEST(slab->put_PanelDepth(0),S_OK);
   TRY_TEST(pTestPrecastSlab->PassedEventTest(), false );

   pTestPrecastSlab->InitEventTest();
   TRY_TEST(slab->put_PanelDepth(10),S_OK);
   TRY_TEST(pTestPrecastSlab->PassedEventTest(), true );

   slab->get_PanelDepth(&value);
   TRY_TEST(IsEqual(value,10.0),true);

   pTestPrecastSlab->InitEventTest();
   TRY_TEST(slab->put_CastDepth(10),S_OK);
   TRY_TEST(pTestPrecastSlab->PassedEventTest(), true );

   slab->get_CastDepth(&value);
   TRY_TEST(IsEqual(value,10.0),true);
  
   pTestPrecastSlab->InitEventTest();
   TRY_TEST(slab->put_OverhangDepth(-10),E_INVALIDARG);
   TRY_TEST(slab->put_OverhangDepth(0),S_OK);
   TRY_TEST(pTestPrecastSlab->PassedEventTest(), false );

   pTestPrecastSlab->InitEventTest();
   TRY_TEST(slab->put_OverhangDepth(10),S_OK);
   TRY_TEST(pTestPrecastSlab->PassedEventTest(), true );

   slab->get_OverhangDepth(&value);
   TRY_TEST(IsEqual(value,10.0),true);
  
   pTestPrecastSlab->InitEventTest();
   TRY_TEST(slab->put_OverhangTaper((DeckOverhangTaper)-10),E_INVALIDARG);
   TRY_TEST(slab->put_OverhangTaper(dotNone),S_OK);
   TRY_TEST(pTestPrecastSlab->PassedEventTest(), false );

   pTestPrecastSlab->InitEventTest();
   TRY_TEST(slab->put_OverhangTaper(dotTopTopFlange),S_OK);
   TRY_TEST(pTestPrecastSlab->PassedEventTest(), true );

   slab->get_OverhangTaper(&taper);
   TRY_TEST(taper,dotTopTopFlange);

   // Testing interaction with edge of deck path
   // default is NULL, so this shouldn't cause an event
   pTestPrecastSlab->InitEventTest();
   TRY_TEST(slab->putref_LeftOverhangPathStrategy(NULL),S_OK);
   TRY_TEST(pTestPrecastSlab->PassedEventTest(), false );

   // add the strategy
   CComPtr<IAlignment> alignment;
   alignment.CoCreateInstance(CLSID_Alignment);
   CComPtr<IAlignmentOffsetStrategy> left_strategy;
   left_strategy.CoCreateInstance(CLSID_AlignmentOffsetStrategy);
   left_strategy->putref_Alignment(alignment);

   CComQIPtr<IOverhangPathStrategy> strategy(left_strategy);
   pTestPrecastSlab->InitEventTest();
   TRY_TEST(slab->putref_LeftOverhangPathStrategy(strategy),S_OK);
   TRY_TEST(pTestPrecastSlab->PassedEventTest(), true );

   // add it again.. no event because there is no actual change
   pTestPrecastSlab->InitEventTest();
   TRY_TEST(slab->putref_LeftOverhangPathStrategy(strategy),S_OK);
   TRY_TEST(pTestPrecastSlab->PassedEventTest(), false );

   // change value, expecting event
   pTestPrecastSlab->InitEventTest();
   left_strategy->put_Offset(-10);
   TRY_TEST(pTestPrecastSlab->PassedEventTest(), true );

   // default is NULL, so this shouldn't cause an event
   CComPtr<IAlignmentOffsetStrategy> right_strategy;
   right_strategy.CoCreateInstance(CLSID_AlignmentOffsetStrategy);
   right_strategy->putref_Alignment(alignment);

   pTestPrecastSlab->InitEventTest();
   TRY_TEST(slab->putref_RightOverhangPathStrategy(NULL),S_OK);
   TRY_TEST(pTestPrecastSlab->PassedEventTest(), false );

   // add the strategy
   strategy.Release();
   right_strategy.QueryInterface(&strategy);
   pTestPrecastSlab->InitEventTest();
   TRY_TEST(slab->putref_RightOverhangPathStrategy(strategy),S_OK);
   TRY_TEST(pTestPrecastSlab->PassedEventTest(), true );

   // add it again.. no event because there is no actual change
   pTestPrecastSlab->InitEventTest();
   TRY_TEST(slab->putref_RightOverhangPathStrategy(strategy),S_OK);
   TRY_TEST(pTestPrecastSlab->PassedEventTest(), false );

   // change value, expecting event
   pTestPrecastSlab->InitEventTest();
   right_strategy->put_Offset(-10);
   TRY_TEST(pTestPrecastSlab->PassedEventTest(), true );


   // Test stage related events
   pTestPrecastSlab->InitEventTest();
   TRY_TEST(slab->put_CastingStage(NULL),E_INVALIDARG);
   TRY_TEST(slab->put_CastingStage(CComBSTR()),E_INVALIDARG);
   TRY_TEST(pTestPrecastSlab->PassedEventTest(), false );

   pTestPrecastSlab->InitEventTest();
   TRY_TEST(slab->put_CastingStage(CComBSTR("Stage 2")),S_OK);
   TRY_TEST(pTestPrecastSlab->PassedEventTest(), true );

   bstrStage.Empty();
   slab->get_CastingStage(&bstrStage);
   TRY_TEST(bstrStage,CComBSTR("Stage 2"));

   // Done with events
   TRY_TEST(AtlUnadvise(slab,IID_IBridgeDeckEvents,dwCookie),S_OK);
   pTestPrecastSlab->Release();

   ///////////////////////////////////////
   // Test Error Info
   CComQIPtr<ISupportErrorInfo> eInfo(slab);
   TRY_TEST( eInfo != 0, true );

   // Interfaces that should be supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IPrecastSlab ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );

   // Interface that is not supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

   // Test IObjectSafety
   TRY_TEST( TestIObjectSafety(slab,IID_IPrecastSlab,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
   TRY_TEST( TestIObjectSafety(slab,IID_IStructuredStorage2,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
}


STDMETHODIMP CTestPrecastSlab::OnBridgeDeckChanged(IBridgeDeck* pDeck)
{
   Pass();
   return S_OK;
}