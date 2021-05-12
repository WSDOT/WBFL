///////////////////////////////////////////////////////////////////////
// GenericBridgeTest - Test driver for generic bridge library
// Copyright © 1999-2021  Washington State Department of Transportation
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

// TestOverlaySlab.cpp: implementation of the CTestOverlaySlab class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestOverlaySlab.h"
#include "TestBridgeDeck.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestOverlaySlab::CTestOverlaySlab()
{

}

CTestOverlaySlab::~CTestOverlaySlab()
{

}

void CTestOverlaySlab::Test()
{
   HRESULT hr;
   CComPtr<IOverlaySlab> slab;
   hr = slab.CoCreateInstance(CLSID_OverlaySlab);
   TRY_TEST(hr,S_OK);

   CTestBridgeDeck::Test(slab);

   //////////////////////
   // Test default values
   Float64 value;
   TRY_TEST(slab->get_GrossDepth(nullptr),E_POINTER);
   TRY_TEST(slab->get_GrossDepth(&value),S_OK);
   TRY_TEST(IsZero(value),true);

   CComPtr<IMaterial> material;
   TRY_TEST(slab->get_Material(nullptr), E_POINTER);
   TRY_TEST(slab->get_Material(&material), S_OK);
   TRY_TEST(material != nullptr, true);

   ///////////////////////////////////////
   // Test Error Info
   CComQIPtr<ISupportErrorInfo> eInfo(slab);
   TRY_TEST( eInfo != 0, true );

   // Interfaces that should be supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IOverlaySlab ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );

   // Interface that is not supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

   // Test IObjectSafety
   TRY_TEST( TestIObjectSafety(slab,IID_IOverlaySlab,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
   TRY_TEST( TestIObjectSafety(slab,IID_IStructuredStorage2,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
}
