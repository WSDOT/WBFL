///////////////////////////////////////////////////////////////////////
// COGOTest - Test Driver for Coordinate Geometry Library
// Copyright © 1999-2011  Washington State Department of Transportation
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

// TestProfilePoint.cpp: implementation of the CTestProfilePoint class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestProfilePoint.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestProfilePoint::CTestProfilePoint()
{

}

void CTestProfilePoint::Test()
{
   CComPtr<IProfilePoint> pProfilePoint;
   TRY_TEST(pProfilePoint.CoCreateInstance(CLSID_ProfilePoint),S_OK);

   Float64 sta1,elev1;
   Float64 sta = 10.0;
   Float64 elev = 20.0;

   // Test Properties
   TRY_TEST( pProfilePoint->put_Station(CComVariant(sta)), S_OK );

   CComPtr<IStation> station;
   TRY_TEST( pProfilePoint->get_Station(&station), S_OK);
   station->get_Value(&sta1);
   TRY_TEST( IsEqual(sta,sta1),true );

   TRY_TEST( pProfilePoint->put_Elevation(elev), S_OK );
   TRY_TEST( pProfilePoint->get_Elevation(&elev1), S_OK);
   TRY_TEST( IsEqual(elev,elev1),true );

   TRY_TEST( pProfilePoint->get_Station(NULL), E_POINTER );
   TRY_TEST( pProfilePoint->get_Elevation(NULL), E_POINTER );

   // Test Events
   CComObject<CTestProfilePoint>* pTestProfilePoint;
   CComObject<CTestProfilePoint>::CreateInstance(&pTestProfilePoint);
   pTestProfilePoint->AddRef();

   DWORD dwCookie;
   CComPtr<IUnknown> punk(pTestProfilePoint);
   TRY_TEST(AtlAdvise(pProfilePoint,punk,IID_IProfilePointEvents,&dwCookie),S_OK);

   pTestProfilePoint->InitEventTest();
   pProfilePoint->put_Station(CComVariant(5));
   TRY_TEST(pTestProfilePoint->PassedEventTest(), true );

   pTestProfilePoint->InitEventTest();
   pProfilePoint->put_Elevation(5);
   TRY_TEST(pTestProfilePoint->PassedEventTest(), true );

   TRY_TEST(AtlUnadvise(pProfilePoint,IID_IProfilePointEvents,dwCookie),S_OK);
   pTestProfilePoint->Release();

   // Test ISupportErrorInfo
   CComQIPtr<ISupportErrorInfo> eInfo(pProfilePoint);
   TRY_TEST( eInfo != NULL, true );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IProfilePoint ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

   // Test IObjectSafety
   TRY_TEST( TestIObjectSafety(CLSID_ProfilePoint,IID_IProfilePoint,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
   TRY_TEST( TestIObjectSafety(CLSID_ProfilePoint,IID_IStructuredStorage2,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
}

STDMETHODIMP CTestProfilePoint::OnProfilePointChanged(IProfilePoint* pp)
{
//   ::MessageBox(NULL,"OnProfilePointChanged","Event",MB_OK);
   Pass();
   return S_OK;
}
