///////////////////////////////////////////////////////////////////////
// COGOTest - Test Driver for Coordinate Geometry Library
// Copyright © 1999-2010  Washington State Department of Transportation
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

// TestCrossSection.cpp: implementation of the CTestCrossSection class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestCrossSection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestCrossSection::CTestCrossSection()
{

}

void CTestCrossSection::Test()
{
   CComPtr<ICrossSection> pCrossSection;
   TRY_TEST(pCrossSection.CoCreateInstance(CLSID_CrossSection),S_OK);

   Float64 val;

   // Test initial values... should all be zero
   TRY_TEST(pCrossSection->get_Station(NULL),E_POINTER);
   TRY_TEST(pCrossSection->get_CrownPointOffset(NULL),E_POINTER);
   TRY_TEST(pCrossSection->get_LeftCrownSlope(NULL),E_POINTER);
   TRY_TEST(pCrossSection->get_RightCrownSlope(NULL),E_POINTER);

   CComPtr<IStation> station;
   TRY_TEST(pCrossSection->get_Station(&station),S_OK);
   station->get_Value(&val);
   TRY_TEST(IsZero(val),true);

   TRY_TEST(pCrossSection->get_CrownPointOffset(&val),S_OK);
   TRY_TEST(IsZero(val),true);

   TRY_TEST(pCrossSection->get_LeftCrownSlope(&val),S_OK);
   TRY_TEST(IsZero(val),true);

   TRY_TEST(pCrossSection->get_RightCrownSlope(&val),S_OK);
   TRY_TEST(IsZero(val),true);


   // Test Events
   CComObject<CTestCrossSection>* pTestCrossSection;
   CComObject<CTestCrossSection>::CreateInstance(&pTestCrossSection);
   pTestCrossSection->AddRef();

   DWORD dwCookie;
   CComPtr<IUnknown> punk(pTestCrossSection);
   TRY_TEST(AtlAdvise(pCrossSection,punk,IID_ICrossSectionEvents,&dwCookie),S_OK);

   pTestCrossSection->InitEventTest();
   pCrossSection->put_Station(CComVariant(5));
   TRY_TEST(pTestCrossSection->PassedEventTest(), true );

   pTestCrossSection->InitEventTest();
   pCrossSection->put_CrownPointOffset(5);
   TRY_TEST(pTestCrossSection->PassedEventTest(), true );

   pTestCrossSection->InitEventTest();
   pCrossSection->put_LeftCrownSlope(5);
   TRY_TEST(pTestCrossSection->PassedEventTest(), true );

   pTestCrossSection->InitEventTest();
   pCrossSection->put_RightCrownSlope(5);
   TRY_TEST(pTestCrossSection->PassedEventTest(), true );

   TRY_TEST(AtlUnadvise(pCrossSection,IID_ICrossSectionEvents,dwCookie),S_OK);
   pTestCrossSection->Release();

   // Test ISupportErrorInfo
   CComQIPtr<ISupportErrorInfo> eInfo(pCrossSection);
   TRY_TEST( eInfo != NULL, true );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ICrossSection ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

   // Test IObjectSafety
   TRY_TEST( TestIObjectSafety(CLSID_CrossSection,IID_ICrossSection,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
   TRY_TEST( TestIObjectSafety(CLSID_CrossSection,IID_IStructuredStorage2,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
}

STDMETHODIMP CTestCrossSection::OnCrossSectionChanged(ICrossSection* CrossSection)
{
//   ::MessageBox(NULL,"OnCrossSectionChanged","Event",MB_OK);
   Pass();
   return S_OK;
}

STDMETHODIMP CTestCrossSection::OnCrossSectionMoved(ICrossSection* CrossSection)
{
//   ::MessageBox(NULL,"OnCrossSectionMoved","Event",MB_OK);
   Pass();
   return S_OK;
}