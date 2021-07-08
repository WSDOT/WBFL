///////////////////////////////////////////////////////////////////////
// COGOTest - Test Driver for Coordinate Geometry Library
// Copyright © 1999-2021  Washington State Department of Transportation
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

// TestPathElement.cpp: implementation of the CTestPathElement class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestPathElement.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestPathElement::CTestPathElement()
{

}

void CTestPathElement::Test()
{
   CComPtr<IPathElement> pPathElement;
   TRY_TEST(pPathElement.CoCreateInstance(CLSID_PathElement),S_OK);

   CComPtr<IPoint2d> point;
   point.CoCreateInstance(CLSID_Point2d);

   TRY_TEST(pPathElement->putref_Value(nullptr),E_INVALIDARG);
   TRY_TEST(pPathElement->putref_Value(point), S_OK );

   PathElementType type;
   TRY_TEST(pPathElement->get_Type(nullptr),E_POINTER);
   TRY_TEST(pPathElement->get_Type(&type),S_OK);
   TRY_TEST(type,petPoint);

   CComPtr<ICompoundCurve> hc;
   hc.CoCreateInstance(CLSID_CompoundCurve);
   TRY_TEST(pPathElement->putref_Value(hc),S_OK );
   TRY_TEST(pPathElement->get_Type(&type),S_OK);
   TRY_TEST(type,petCompoundCurve);

   CComPtr<ILineSegment2d> ls;
   ls.CoCreateInstance(CLSID_LineSegment2d);
   TRY_TEST(pPathElement->putref_Value(ls),S_OK );
   TRY_TEST(pPathElement->get_Type(&type),S_OK);
   TRY_TEST(type,petLineSegment);

   // try some IUnknown that aren't the right kind of object
   CComPtr<IProfilePoint> pnt;
   pnt.CoCreateInstance(CLSID_ProfilePoint);
   TRY_TEST(pPathElement->putref_Value(pnt),E_INVALIDARG);
   TRY_TEST(pPathElement->putref_Value(pPathElement),E_INVALIDARG);

   CComPtr<IUnknown> disp;
   TRY_TEST(pPathElement->get_Value(nullptr),E_POINTER);
   TRY_TEST(pPathElement->get_Value(&disp),S_OK);

   // Test Events
   CComObject<CTestPathElement>* pTestPathElement;
   CComObject<CTestPathElement>::CreateInstance(&pTestPathElement);
   pTestPathElement->AddRef();

   DWORD dwCookie;
   CComPtr<IUnknown> punk(pTestPathElement);
   TRY_TEST(AtlAdvise(pPathElement,punk,IID_IPathElementEvents,&dwCookie),S_OK);

   pTestPathElement->InitEventTest();
   pPathElement->putref_Value(hc);
   TRY_TEST(pTestPathElement->PassedEventTest(), true );

   pTestPathElement->InitEventTest();
   hc->put_Radius(500);
   TRY_TEST(pTestPathElement->PassedEventTest(), true );

   pTestPathElement->InitEventTest();
   pPathElement->putref_Value(point);
   TRY_TEST(pTestPathElement->PassedEventTest(), true );

   pTestPathElement->InitEventTest();
   point->Move(50,50);
   TRY_TEST(pTestPathElement->PassedEventTest(), true );

   pTestPathElement->InitEventTest();
   pPathElement->putref_Value(ls);
   TRY_TEST(pTestPathElement->PassedEventTest(), true );

   pTestPathElement->InitEventTest();
   ls->Offset(50,50);
   TRY_TEST(pTestPathElement->PassedEventTest(), true );


   TRY_TEST(AtlUnadvise(pPathElement,IID_IPathElementEvents,dwCookie),S_OK);
   pTestPathElement->Release();

   // Test ISupportErrorInfo
   CComQIPtr<ISupportErrorInfo> eInfo(pPathElement);
   TRY_TEST( eInfo != nullptr, true );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IPathElement ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

   // Test IObjectSafety
   TRY_TEST( TestIObjectSafety(CLSID_PathElement,IID_IPathElement,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
   TRY_TEST( TestIObjectSafety(CLSID_PathElement,IID_IStructuredStorage2,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
}

STDMETHODIMP CTestPathElement::OnPathElementChanged(IPathElement* pp)
{
//   ::MessageBox(nullptr,"OnPathElementChanged","Event",MB_OK);
   Pass();
   return S_OK;
}
