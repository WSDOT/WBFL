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

// TestMaterial.cpp: implementation of the CTestMaterial class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestMaterial.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestMaterial::CTestMaterial()
{

}

CTestMaterial::~CTestMaterial()
{

}

void CTestMaterial::Test()
{
   HRESULT hr;
   CComPtr<IMaterial> material;
   hr = material.CoCreateInstance(CLSID_Material);
   TRY_TEST(hr,S_OK);

   ///////////////////////////////////////
   // Test simple set/get
   Float64 value;
   TRY_TEST(material->put_E(-12.2),E_INVALIDARG);
   TRY_TEST(material->put_E(0),E_INVALIDARG);
   TRY_TEST(material->put_E(100),S_OK);
   TRY_TEST(material->get_E(NULL),E_POINTER);;
   TRY_TEST(material->get_E(&value),S_OK);;
   TRY_TEST(IsEqual(value,100.0),true);

   TRY_TEST(material->put_Density(-12.2),S_OK);
   TRY_TEST(material->put_Density(0),S_OK);
   TRY_TEST(material->put_Density(100),S_OK);
   TRY_TEST(material->get_Density(NULL),E_POINTER);;
   TRY_TEST(material->get_Density(&value),S_OK);;
   TRY_TEST(IsEqual(value,100.0),true);

   ///////////////////////////////////////
   // Test Set with event sink
   CComObject<CTestMaterial>* pTestMaterial;
   CComObject<CTestMaterial>::CreateInstance(&pTestMaterial);
   pTestMaterial->AddRef();
   
   DWORD dwCookie;
   CComPtr<IUnknown> punk(pTestMaterial);
   TRY_TEST(AtlAdvise(material,punk,IID_IMaterialEvents,&dwCookie),S_OK);

   pTestMaterial->InitEventTest();
   material->put_E(5);
   TRY_TEST(pTestMaterial->PassedEventTest(), true );

   pTestMaterial->InitEventTest();
   material->put_E(5); // setting same value should not cause an event
   TRY_TEST(pTestMaterial->PassedEventTest(), false );

   pTestMaterial->InitEventTest();
   material->put_Density(7);
   TRY_TEST(pTestMaterial->PassedEventTest(), true );

   pTestMaterial->InitEventTest();
   material->put_Density(7); // setting same value should not cause an event
   TRY_TEST(pTestMaterial->PassedEventTest(), false );

   ///////////////////////////////////////
   // Test Set with events
   pTestMaterial->InitEventTest();
   TRY_TEST(material->put_E(50.0),S_OK);
   material->get_E(&value);
   TRY_TEST(IsEqual(value,50.0),true);
   TRY_TEST(pTestMaterial->PassedEventTest(), true );

   pTestMaterial->InitEventTest();
   TRY_TEST(material->put_Density(150.0),S_OK);
   material->get_Density(&value);
   TRY_TEST(IsEqual(value,150.0),true);
   TRY_TEST(pTestMaterial->PassedEventTest(), true );

   // Done with events
   TRY_TEST(AtlUnadvise(material,IID_IMaterialEvents,dwCookie),S_OK);
   pTestMaterial->Release();

   ///////////////////////////////////////
   // Test Error Info
   CComQIPtr<ISupportErrorInfo> eInfo(material);
   TRY_TEST( eInfo != 0, true );

   // Interfaces that should be supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IMaterial ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );

   // Interface that is not supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

   // Test IObjectSafety
   TRY_TEST( TestIObjectSafety(material,IID_IMaterial,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
   TRY_TEST( TestIObjectSafety(material,IID_IStructuredStorage2,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
}


STDMETHODIMP CTestMaterial::OnMaterialChanged(IMaterial* sp)
{
   Pass();
   return S_OK;
}