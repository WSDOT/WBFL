///////////////////////////////////////////////////////////////////////
// GenericBridgeTest - Test driver for generic bridge library
// Copyright © 1999-2010  Washington State Department of Transportation
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

// TestStageCollection.cpp: implementation of the CTestStageCollection class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestStageCollection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestStageCollection::CTestStageCollection()
{

}

CTestStageCollection::~CTestStageCollection()
{

}

void CTestStageCollection::Test()
{
   // Create a default bridge
   CComPtr<IGenericBridge> bridge;
   bridge.CoCreateInstance(CLSID_GenericBridge);

   CComPtr<IStageCollection> stages;
   bridge->get_Stages(&stages);

   TRY_TEST(stages != NULL,true);

   CollectionIndexType count;
   TRY_TEST(stages->get_Count(NULL),E_POINTER);
   TRY_TEST(stages->get_Count(&count),S_OK);
   TRY_TEST(count,0);

   TRY_TEST(stages->CreateStage(CComBSTR(""),CComBSTR("")),E_INVALIDARG);
   TRY_TEST(stages->CreateStage(CComBSTR("Stage 1"),CComBSTR("")),S_OK);
   TRY_TEST(stages->CreateStage(CComBSTR("Stage 2"),CComBSTR("")),S_OK);

   stages->get_Count(&count);
   TRY_TEST(count,2);

   TRY_TEST(stages->CreateStageAt(CComBSTR("Stage 2"),CComBSTR(""),0),GB_E_DUPLICATENAME);
   TRY_TEST(stages->CreateStageAt(CComBSTR(""),CComBSTR(""),0),E_INVALIDARG);
   TRY_TEST(stages->CreateStageAt(CComBSTR("Stage 0"),CComBSTR(""),0),S_OK);

   stages->get_Count(&count);
   TRY_TEST(count,3);

   CComPtr<IEnumStages> enumStages;
   CComPtr<IStage> stage;
   long i = 0;

   TRY_TEST(stages->get__EnumStages(NULL),E_POINTER);
   TRY_TEST(stages->get__EnumStages(&enumStages),S_OK);
   while ( enumStages->Next(1,&stage,NULL) != S_FALSE )
   {
      CComBSTR bstrName;
      stage->get_Name(&bstrName);
      std::_tstring strName = _T("Stage ");
      strName += '0' + (char)i++;
      TRY_TEST(bstrName == CComBSTR(strName.c_str()),true);
      
      stage.Release();
   }

   stage.Release();
   TRY_TEST(stages->Find(CComBSTR("NotValidStage"),&stage),GB_E_STAGE_NOT_FOUND);
   TRY_TEST(stages->Find(CComBSTR("Stage 1"),NULL),E_POINTER);
   TRY_TEST(stages->Find(CComBSTR("Stage 1"),&stage),S_OK);

   stage.Release();
   TRY_TEST(stages->get_Item(0,NULL),E_POINTER);
   TRY_TEST(stages->get_Item(-1,&stage),E_INVALIDARG);
   TRY_TEST(stages->get_Item(10,&stage),E_INVALIDARG);
   TRY_TEST(stages->get_Item(0,&stage),S_OK);

   long cmp;
   TRY_TEST(stages->Compare(CComBSTR("Stage 2"),CComBSTR("Stage 0"),NULL),E_POINTER);
   TRY_TEST(stages->Compare(NULL,CComBSTR("Stage 0"),&cmp),E_INVALIDARG);
   TRY_TEST(stages->Compare(CComBSTR("Stage 0"),NULL,&cmp),E_INVALIDARG);
   TRY_TEST(stages->Compare(CComBSTR("Stage 2"),CComBSTR("Stage 0"),&cmp),S_OK);
   TRY_TEST(cmp == 1,true);
   TRY_TEST(stages->Compare(CComBSTR("Stage 0"),CComBSTR("Stage 2"),&cmp),S_OK);
   TRY_TEST(cmp == -1,true);
   TRY_TEST(stages->Compare(CComBSTR("Stage 1"),CComBSTR("Stage 1"),&cmp),S_OK);
   TRY_TEST(cmp == 0,true);
   TRY_TEST(stages->Compare(CComBSTR("Blue"),CComBSTR("Stage 2"),&cmp),S_FALSE);
   TRY_TEST(cmp == 0,true);
   TRY_TEST(stages->Compare(CComBSTR("Stage 2"),CComBSTR("Blue"),&cmp),S_FALSE);
   TRY_TEST(cmp == 0,true);

   ///////////////////////////////////////
   // Test with event sink
   CComObject<CTestStageCollection>* pTest;
   CComObject<CTestStageCollection>::CreateInstance(&pTest);
   pTest->AddRef();
   
   DWORD dwCookie;
   CComPtr<IUnknown> punk(pTest);
   TRY_TEST(AtlAdvise(stages,punk,IID_IStageCollectionEvents,&dwCookie),S_OK);

   ///////////////////////////////////////
   // Test with events
   pTest->InitEventTest();
   stages->CreateStage(CComBSTR("Stage 3"),CComBSTR(""));
   stages->get_Count(&count);
   TRY_TEST(count,4);
   TRY_TEST(pTest->PassedEventTest(), true);

   pTest->InitEventTest();
   TRY_TEST(stages->MoveStage(-1,2),E_INVALIDARG);
   TRY_TEST(stages->MoveStage(100,2),E_INVALIDARG);
   TRY_TEST(stages->MoveStage(0,-1),E_INVALIDARG);
   TRY_TEST(stages->MoveStage(0,100),E_INVALIDARG);
   TRY_TEST(stages->MoveStage(0,2),S_OK);
   stage.Release();
   stages->get_Item(0,&stage);

   CComBSTR bstrName;
   stage->get_Name(&bstrName);
   TRY_TEST(bstrName == CComBSTR("Stage 1"),true);
   
   stage.Release();
   bstrName.Empty();
   stages->get_Item(2,&stage);
   stage->get_Name(&bstrName);
   TRY_TEST(bstrName == CComBSTR("Stage 0"),true);
   TRY_TEST(pTest->PassedEventTest(), true);

   pTest->InitEventTest();
   TRY_TEST(stages->RemoveByIndex(-1),E_INVALIDARG);
   TRY_TEST(stages->RemoveByIndex(100),E_INVALIDARG);
   TRY_TEST(stages->RemoveByIndex(0),S_OK);
   stages->get_Count(&count);
   TRY_TEST(count,3);
   TRY_TEST(pTest->PassedEventTest(), true);

   pTest->InitEventTest();
   TRY_TEST(stages->RemoveByName(NULL),GB_E_STAGE_NOT_FOUND);
   TRY_TEST(stages->RemoveByName(CComBSTR("NotValidStage")),GB_E_STAGE_NOT_FOUND);
   TRY_TEST(stages->RemoveByName(CComBSTR("Stage 0")),S_OK);
   stages->get_Count(&count);
   TRY_TEST(count,2);
   TRY_TEST(pTest->PassedEventTest(), true);

   // bubbled events
   stage.Release();
   stages->get_Item(0,&stage);

   pTest->InitEventTest();
   stage->put_Name(CComBSTR("First Stage"));
   TRY_TEST(pTest->PassedEventTest(), true);

   pTest->InitEventTest();
   stage->put_Description(CComBSTR("It all begins here"));
   TRY_TEST(pTest->PassedEventTest(), true);

   // Done with events
   TRY_TEST(AtlUnadvise(stages,IID_IStageCollectionEvents,dwCookie),S_OK);
   pTest->Release();

   ///////////////////////////////////////
   // Test Error Info
   CComQIPtr<ISupportErrorInfo> eInfo(stages);
   TRY_TEST( eInfo != 0, true );

   // Interfaces that should be supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStageCollection ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );

   // Interface that is not supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

   // Test IObjectSafety
   TRY_TEST( TestIObjectSafety(stages,IID_IStageCollection,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
   TRY_TEST( TestIObjectSafety(stages,IID_IStructuredStorage2,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
}

STDMETHODIMP CTestStageCollection::OnStageRenamed(BSTR bstrOldName,IStage* stage)
{
   Pass();
   return S_OK;
}

STDMETHODIMP CTestStageCollection::OnStageDescriptionChanged(IStage* stage)
{
   Pass();
   return S_OK;
}

STDMETHODIMP CTestStageCollection::OnStageAdded(CollectionIndexType idx)
{
   Pass();
   return S_OK;
}

STDMETHODIMP CTestStageCollection::OnStageRemoved(CollectionIndexType idx,BSTR name)
{
   Pass();
   return S_OK;
}

STDMETHODIMP CTestStageCollection::OnStageMoved(BSTR name,CollectionIndexType from,CollectionIndexType to)
{
   Pass();
   return S_OK;
}
