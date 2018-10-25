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

// Testpier.cpp: implementation of the CTestPier class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Testpier.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestPier::CTestPier()
{

}

CTestPier::~CTestPier()
{

}

void CTestPier::Test()
{
   // Create a default bridge
   CComPtr<IGenericBridge> bridge;
   bridge.CoCreateInstance(CLSID_GenericBridge);

   bridge->InsertSpanAndPier(0, 100.00, qcbAfter, qcbRight);

   CComPtr<IPierCollection> piers;
   bridge->get_Piers(&piers);

   CComPtr<IPier> pier;
   piers->get_Item(0,&pier);

   TRY_TEST(pier != NULL, true);

   // Test default values
   CComPtr<IStation> objStation;
   TRY_TEST(pier->get_Station(NULL),E_POINTER);
   TRY_TEST(pier->get_Station(&objStation),S_OK);

   Float64 station;
   objStation->get_Value(&station);
   TRY_TEST(IsEqual(station,0.0),true);

   CComPtr<IStation> objNewStation;
   objNewStation.CoCreateInstance(CLSID_Station);
   objNewStation->put_Value(10.0);
   TRY_TEST(pier->putref_Station(NULL),E_INVALIDARG);
   TRY_TEST(pier->putref_Station(objNewStation),S_OK);

   CComBSTR bstrOrientation;
   TRY_TEST(pier->get_Orientation(NULL),E_POINTER);
   TRY_TEST(pier->get_Orientation(&bstrOrientation),S_OK);
   TRY_TEST(bstrOrientation == CComBSTR("Normal"),true);

   CComPtr<ILongitudinalPierDescription> lpd;
   TRY_TEST(pier->get_LongitudinalPierDescription(NULL),E_POINTER);
   TRY_TEST(pier->get_LongitudinalPierDescription(&lpd),S_OK);
   TRY_TEST(lpd != NULL,true);

   CComPtr<ITransversePierDescription> tpd;
   TRY_TEST(pier->get_TransversePierDescription(NULL),E_POINTER);
   TRY_TEST(pier->get_TransversePierDescription(&tpd),S_OK);
   TRY_TEST(tpd == NULL,true);
   
   TRY_TEST(pier->CreateTransversePierDescription(),S_OK);
   TRY_TEST(pier->get_TransversePierDescription(&tpd),S_OK);
   TRY_TEST(tpd != NULL,true);

   TRY_TEST(pier->RemoveTransversePierDescription(),S_OK);
   TRY_TEST(tpd != NULL,true);
   tpd.Release();
   TRY_TEST(pier->get_TransversePierDescription(&tpd),S_OK);
   TRY_TEST(tpd == NULL,true);


   CComPtr<IDirection> objDirection;
   CComPtr<IAngle> objAngle;
   TRY_TEST(pier->put_Orientation(CComBSTR("XYZ")),E_INVALIDARG);
   TRY_TEST(pier->put_Orientation(CComBSTR("N 45 E")),S_OK);
   TRY_TEST(pier->get_Direction(NULL),E_POINTER);
   TRY_TEST(pier->get_Direction(&objDirection),S_OK);
   Float64 value;
   objDirection->get_Value(&value);
   TRY_TEST(IsEqual(value,M_PI/4),true);

   TRY_TEST(pier->get_SkewAngle(NULL),E_POINTER);
   TRY_TEST(pier->get_SkewAngle(&objAngle),S_OK);
   objAngle->get_Value(&value);
   TRY_TEST(IsEqual(value,-M_PI/4),true);

   TRY_TEST(pier->put_Orientation(CComBSTR("45 L")),S_OK);
   objDirection.Release();
   objAngle.Release();
   TRY_TEST(pier->get_Direction(&objDirection),S_OK);
   objDirection->get_Value(&value);
   TRY_TEST(IsEqual(value,3*M_PI/4),true);
   TRY_TEST(pier->get_SkewAngle(&objAngle),S_OK);
   objAngle->get_Value(&value);
   TRY_TEST(IsEqual(value,M_PI/4),true);

   TRY_TEST(pier->put_Orientation(CComBSTR("N")),S_OK);
   objDirection.Release();
   objAngle.Release();
   TRY_TEST(pier->get_Direction(&objDirection),S_OK);
   objDirection->get_Value(&value);
   TRY_TEST(IsEqual(value,PI_OVER_2),true);
   TRY_TEST(pier->get_SkewAngle(&objAngle),S_OK);
   objAngle->get_Value(&value);
   TRY_TEST(IsEqual(value,0.0),true);

   ///////////////////////////////////////
   // Test Set with event sink
   CComObject<CTestPier>* pTest;
   CComObject<CTestPier>::CreateInstance(&pTest);
   pTest->AddRef();
   
   DWORD dwCookie;
   CComPtr<IUnknown> punk(pTest);
   TRY_TEST(AtlAdvise(pier,punk,IID_IPierEvents,&dwCookie),S_OK);

   ///////////////////////////////////////
   // Test Set with events

   pTest->InitEventTest();
   pier->put_Orientation(CComBSTR("N 45 W"));
   objDirection.Release();
   pier->get_Direction(&objDirection);
   objDirection->get_Value(&value);
   TRY_TEST(IsEqual(value,3*M_PI/4),true);
   TRY_TEST(pTest->PassedEventTest(), true );

   objStation.Release();
   pier->get_Station(&objStation);
   objStation->put_Value(10.0);
   pTest->InitEventTest();
   objStation->put_Value(20.0);
   TRY_TEST(pTest->PassedEventTest(), true );

//   pier->put_AlignmentOffset(10.0);
//   pTest->InitEventTest();
//   pier->put_AlignmentOffset(5);
//   TRY_TEST(pTest->PassedEventTest(), true );
//
//   objNewStation.Release();
//   objNewStation.CoCreateInstance(CLSID_Station);
//   objNewStation->put_Value(15);
//   pTest->InitEventTest();
//   pier->putref_Station(objNewStation);
//   objStation.Release();
//   pier->get_Station(&objStation);
//   TRY_TEST(objNewStation.IsEqualObject(objStation),true);
//   TRY_TEST(pTest->PassedEventTest(), true );

   // bubbled events
   lpd.Release();
   pier->get_LongitudinalPierDescription(&lpd);

   CComPtr<IPrismaticSegment> newSegment;
   newSegment.CoCreateInstance(CLSID_PrismaticSegment);
   lpd->AddSegment(newSegment);
   
   CComPtr<ISegment> segment;
   lpd->get_Segment(0,&segment);

//   CComPtr<ISegmentCrossSection> section;
//   segment->get_CrossSection(&section);
//
//   CComPtr<IStressPointCollection> stressPoints;
//   section->get_StressPoints(&stressPoints);
//
//   pTest->InitEventTest();
//   stressPoints->Add();
//   TRY_TEST(pTest->PassedEventTest(), true );
//
//   CComPtr<IStressPoint> sp;
//   stressPoints->get_Item(0,&sp);
//   pTest->InitEventTest();
//   sp->put_Sa(10.0);
//   TRY_TEST(pTest->PassedEventTest(), true );
//
//   pTest->InitEventTest();
//   section->put_Area(10.0);
//   TRY_TEST(pTest->PassedEventTest(), true );

   pTest->InitEventTest();
   segment->put_Length(15.0);
   TRY_TEST(pTest->PassedEventTest(), true );

   // Done with events
   TRY_TEST(AtlUnadvise(pier,IID_IPierEvents,dwCookie),S_OK);
   pTest->Release();

   ///////////////////////////////////////
   // Test Error Info
   CComQIPtr<ISupportErrorInfo> eInfo(pier);
   TRY_TEST( eInfo != 0, true );

   // Interfaces that should be supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IPier ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );

   // Interface that is not supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

   // Test IObjectSafety
   TRY_TEST( TestIObjectSafety(pier,IID_IPier,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
   TRY_TEST( TestIObjectSafety(pier,IID_IStructuredStorage2,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
}


STDMETHODIMP CTestPier::OnPierChanged(IPier* pier)
{
   Pass();
   return S_OK;
}