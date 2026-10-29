///////////////////////////////////////////////////////////////////////
// GenericBridgeTest - Test driver for generic bridge library
// Copyright © 1999-2026  Washington State Department of Transportation
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

// TestCrossBeam.cpp: implementation of the CTestCrossBeam class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestCrossBeam.h"
#include <PointDefinedArc.h>
#include <limits>


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestCrossBeam::CTestCrossBeam()
{

}

CTestCrossBeam::~CTestCrossBeam()
{

}

void CTestCrossBeam::Test()
{
   // Point-defined transitions: independent expected ordinates and invalid geometry.
   WBFL::Geometry::PointDefinedArc arc;
   TRY_TEST(arc.Initialize(0,0,10,0,10,true),true);
   TRY_TEST(IsEqual(arc.Evaluate(5),10-std::sqrt(75.0)),true);
   TRY_TEST(IsEqual(arc.Evaluate(0),0.0),true);
   TRY_TEST(IsEqual(arc.Evaluate(10),0.0),true);
   TRY_TEST(arc.IsBelowLine(0,2,10,2),true);
   TRY_TEST(arc.IsBelowLine(0,1,10,1),false);
   TRY_TEST(arc.Initialize(0,0,10,0,10,false),true);
   TRY_TEST(IsEqual(arc.Evaluate(5),std::sqrt(75.0)-10),true);
   TRY_TEST(arc.Initialize(0,0,10,0,5,true),true);
   TRY_TEST(IsEqual(arc.Evaluate(5),5.0),true);
   TRY_TEST(arc.Initialize(0,0,10,0,4.99,true),false);
   TRY_TEST(arc.Initialize(0,0,0,1,10,true),false);
   TRY_TEST(arc.Initialize(10,0,0,0,10,true),false);
   TRY_TEST(arc.Initialize(0,0,10,10,8,true),false); // minor arc turns back in X
   TRY_TEST(arc.Initialize(0,0,10,0,std::numeric_limits<double>::infinity(),true),false);
   TRY_TEST(arc.Initialize(0,0,10,0,1e12,true),true);
   TRY_TEST(std::abs(arc.Evaluate(5)-1.25e-11)<1e-20,true);
   TRY_TEST(arc.Initialize(0,-3,10,-1,20,true),true);
   double previous = 0;
   for (int sample = 1; sample <= 100; ++sample)
   {
      double x,y;
      arc.PointAtFraction(double(sample)/100,x,y);
      TRY_TEST(x>previous,true);
      TRY_TEST(std::abs(y-arc.Evaluate(x))<1e-10,true);
      previous=x;
   }

   //// Create a default bridge
   //CComPtr<IGenericBridge> bridge;
   //bridge.CoCreateInstance(CLSID_GenericBridge);

   //bridge->InsertSpanAndPier(0, 10.00, qcbAfter, qcbRight);

   //CComPtr<IPierCollection> piers;
   //bridge->get_Piers(&piers);

   //CComPtr<IPier> pier;
   //piers->get_Item(0,&pier);

   //CComPtr<ITransversePierDescription> tpd;
   //pier->CreateTransversePierDescription();
   //pier->get_TransversePierDescription(&tpd);

   //CComPtr<ICrossBeam> crossBeam;
   //TRY_TEST(tpd->get_CrossBeam(nullptr),E_POINTER);
   //TRY_TEST(tpd->get_CrossBeam(&crossBeam),S_OK);
   //TRY_TEST(crossBeam != nullptr,true);

   //Float64 length;
   //TRY_TEST(crossBeam->get_Length(nullptr),E_POINTER);
   //TRY_TEST(crossBeam->get_Length(&length),S_OK);
   //TRY_TEST(IsEqual(length,0.0),true);

   //IndexType count;
   //TRY_TEST(crossBeam->get_SegmentCount(nullptr),E_POINTER);
   //TRY_TEST(crossBeam->get_SegmentCount(&count),S_OK);
   //TRY_TEST(count,0);

   //VARIANT_BOOL bFractional;
   //TRY_TEST(crossBeam->get_Fractional(nullptr),E_POINTER);
   //TRY_TEST(crossBeam->get_Fractional(&bFractional),S_OK);
   //TRY_TEST(bFractional,VARIANT_FALSE);

   //VARIANT_BOOL bSymmetrical;
   //TRY_TEST(crossBeam->get_Symmetrical(nullptr),E_POINTER);
   //TRY_TEST(crossBeam->get_Symmetrical(&bSymmetrical),S_OK);
   //TRY_TEST(bSymmetrical,VARIANT_FALSE);

   /////////////////////////////////////////
   //// Test Error Info
   //CComQIPtr<ISupportErrorInfo> eInfo(crossBeam);
   //TRY_TEST( eInfo != 0, true );

   //// Interfaces that should be supported
   //TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ICrossBeam ), S_OK );
   //TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );

   //// Interface that is not supported
   //TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

   //// Test IObjectSafety
   //TRY_TEST( TestIObjectSafety(crossBeam,IID_ICrossBeam,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
   //TRY_TEST( TestIObjectSafety(crossBeam,IID_IStructuredStorage2,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
}
