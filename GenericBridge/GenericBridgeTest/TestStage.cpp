///////////////////////////////////////////////////////////////////////
// GenericBridgeTest - Test driver for generic bridge library
// Copyright © 1999-2016  Washington State Department of Transportation
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

// TestStage.cpp: implementation of the CTestStage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestStage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestStage::CTestStage()
{

}

CTestStage::~CTestStage()
{

}

void CTestStage::Test()
{
   // Create a default bridge
   CComPtr<IGenericBridge> bridge;
   bridge.CoCreateInstance(CLSID_GenericBridge);

   CComPtr<IStageCollection> stages;
   bridge->get_Stages(&stages);

   stages->CreateStage(CComBSTR("Stage 1"),CComBSTR(""));
   stages->CreateStage(CComBSTR("Stage 2"),CComBSTR(""));

   CComPtr<IStage> stage;
   stages->get_Item(0,&stage);

   CComBSTR bstrValue;
   TRY_TEST(stage->get_Name(NULL),E_POINTER);
   TRY_TEST(stage->get_Name(&bstrValue),S_OK);
   TRY_TEST(bstrValue == CComBSTR("Stage 1"),true);

   ///////////////////////////////////////
   // Test with event sink
   CComObject<CTestStage>* pTest;
   CComObject<CTestStage>::CreateInstance(&pTest);
   pTest->AddRef();
   
   DWORD dwCookie;
   CComPtr<IUnknown> punk(pTest);
   TRY_TEST(AtlAdvise(stage,punk,IID_IStageEvents,&dwCookie),S_OK);

   ///////////////////////////////////////
   // Test Set with events
   pTest->InitEventTest();
   TRY_TEST(stage->put_Name(NULL),E_INVALIDARG);
   TRY_TEST(stage->put_Name(CComBSTR("Stage 2")),GB_E_DUPLICATENAME);
   TRY_TEST(stage->put_Name(CComBSTR("First Stage")),S_OK);
   bstrValue.Empty();
   stage->get_Name(&bstrValue);
   TRY_TEST(bstrValue == CComBSTR("First Stage"),true);
   TRY_TEST(pTest->PassedEventTest(), true);

   pTest->InitEventTest();
   TRY_TEST(stage->put_Description(CComBSTR("First Stage")),S_OK);
   bstrValue.Empty();
   stage->get_Description(&bstrValue);
   TRY_TEST(bstrValue == CComBSTR("First Stage"),true);
   TRY_TEST(pTest->PassedEventTest(), true);

   // Done with events
   TRY_TEST(AtlUnadvise(stage,IID_IStageEvents,dwCookie),S_OK);
   pTest->Release();

   ///////////////////////////////////////
   // Test Error Info
   CComQIPtr<ISupportErrorInfo> eInfo(stage);
   TRY_TEST( eInfo != 0, true );

   // Interfaces that should be supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStage ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );

   // Interface that is not supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

   // Test IObjectSafety
   TRY_TEST( TestIObjectSafety(stage,IID_IStage,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
   TRY_TEST( TestIObjectSafety(stage,IID_IStructuredStorage2,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
}

STDMETHODIMP CTestStage::OnNameChanged(BSTR bstrOldName, IStage* stage)
{
   Pass();
   return S_OK;
}

STDMETHODIMP CTestStage::OnDescriptionChanged(IStage* stage)
{
   Pass();
   return S_OK;
}
