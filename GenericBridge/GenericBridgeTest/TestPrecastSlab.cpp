///////////////////////////////////////////////////////////////////////
// GenericBridgeTest - Test driver for generic bridge library
// Copyright © 1999-2019  Washington State Department of Transportation
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
   TRY_TEST(slab->get_PanelDepth(nullptr),E_POINTER);
   TRY_TEST(slab->get_PanelDepth(&value),S_OK);
   TRY_TEST(IsZero(value),true);

   TRY_TEST(slab->get_CastDepth(nullptr),E_POINTER);
   TRY_TEST(slab->get_CastDepth(&value),S_OK);
   TRY_TEST(IsZero(value),true);

   TRY_TEST(slab->get_OverhangDepth(qcbLeft,nullptr),E_POINTER);
   TRY_TEST(slab->get_OverhangDepth(qcbLeft, &value),S_OK);
   TRY_TEST(IsZero(value),true);

   DeckOverhangTaper taper;
   TRY_TEST(slab->get_OverhangTaper(qcbLeft, nullptr),E_POINTER);
   TRY_TEST(slab->get_OverhangTaper(qcbLeft, &taper),S_OK);
   TRY_TEST(taper,dotNone);


   CComQIPtr<IBridgeDeck> deck(slab);
   TRY_TEST(deck != nullptr,true);
   CComPtr<IDeckBoundary> deckBoundary;
   TRY_TEST(deck->get_DeckBoundary(nullptr),E_POINTER);
   TRY_TEST(deck->get_DeckBoundary(&deckBoundary),S_OK);

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
