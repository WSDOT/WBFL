///////////////////////////////////////////////////////////////////////
// COGOTest - Test Driver for Coordinate Geometry Library
// Copyright © 1999-2015  Washington State Department of Transportation
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

// TestProfileElement.cpp: implementation of the CTestProfileElement class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestProfileElement.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestProfileElement::CTestProfileElement()
{

}

void CTestProfileElement::Test()
{
   CComPtr<IProfileElement> pProfileElement;
   TRY_TEST(pProfileElement.CoCreateInstance(CLSID_ProfileElement),S_OK);

   CComPtr<IProfilePoint> point;
   point.CoCreateInstance(CLSID_ProfilePoint);

   TRY_TEST(pProfileElement->putref_Value(NULL),E_INVALIDARG);
   TRY_TEST(pProfileElement->putref_Value(point), S_OK );

   ProfileElementType type;
   TRY_TEST(pProfileElement->get_Type(NULL),E_POINTER);
   TRY_TEST(pProfileElement->get_Type(&type),S_OK);
   TRY_TEST(type,pePoint);

   CComPtr<IVertCurve> vc;
   vc.CoCreateInstance(CLSID_VertCurve);
   TRY_TEST(pProfileElement->putref_Value(vc),S_OK );
   TRY_TEST(pProfileElement->get_Type(&type),S_OK);
   TRY_TEST(type,peVertCurve);

   // try some IDispatch that aren't the right kind of object
   CComPtr<IPoint2d> pnt;
   pnt.CoCreateInstance(CLSID_Point2d);
   TRY_TEST(pProfileElement->putref_Value(pnt),E_INVALIDARG);
   TRY_TEST(pProfileElement->putref_Value(pProfileElement),E_INVALIDARG);

   CComPtr<IUnknown> disp;
   TRY_TEST(pProfileElement->get_Value(NULL),E_POINTER);
   TRY_TEST(pProfileElement->get_Value(&disp),S_OK);

   // Test Events
   CComObject<CTestProfileElement>* pTestProfileElement;
   CComObject<CTestProfileElement>::CreateInstance(&pTestProfileElement);
   pTestProfileElement->AddRef();

   DWORD dwCookie;
   CComPtr<IUnknown> punk(pTestProfileElement);
   TRY_TEST(AtlAdvise(pProfileElement,punk,IID_IProfileElementEvents,&dwCookie),S_OK);

   pTestProfileElement->InitEventTest();
   pProfileElement->putref_Value(vc);
   TRY_TEST(pTestProfileElement->PassedEventTest(), true );

   pTestProfileElement->InitEventTest();
   vc->putref_PBG(point);
   TRY_TEST(pTestProfileElement->PassedEventTest(), true );

   pTestProfileElement->InitEventTest();
   pProfileElement->putref_Value(point);
   TRY_TEST(pTestProfileElement->PassedEventTest(), true );

   pTestProfileElement->InitEventTest();
   point->put_Elevation(50);
   TRY_TEST(pTestProfileElement->PassedEventTest(), true );


   TRY_TEST(AtlUnadvise(pProfileElement,IID_IProfileElementEvents,dwCookie),S_OK);
   pTestProfileElement->Release();

   // Test ISupportErrorInfo
   CComQIPtr<ISupportErrorInfo> eInfo(pProfileElement);
   TRY_TEST( eInfo != NULL, true );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IProfileElement ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

   // Test IObjectSafety
   TRY_TEST( TestIObjectSafety(CLSID_ProfileElement,IID_IProfileElement,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
   TRY_TEST( TestIObjectSafety(CLSID_ProfileElement,IID_IStructuredStorage2,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
}

STDMETHODIMP CTestProfileElement::OnProfileElementChanged(IProfileElement* pp)
{
//   ::MessageBox(NULL,"OnProfileElementChanged","Event",MB_OK);
   Pass();
   return S_OK;
}
