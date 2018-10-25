///////////////////////////////////////////////////////////////////////
// RCCapacity Test - Test driver for RCCapacity library
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

// RCBeam2Test.cpp: implementation of the CRCBeam2Test class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RCBeam2Test.h"
#include "GeneralTests.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRCBeam2Test::CRCBeam2Test()
{

}

CRCBeam2Test::~CRCBeam2Test()
{

}

void CRCBeam2Test::Test()
{
   CComPtr<IRCBeam2> beam;
   TRY_TEST(beam.CoCreateInstance(CLSID_RCBeam2),S_OK);

   Float64 val;
   Float64 val1,val2,val3;
   CollectionIndexType count;
   TRY_TEST(beam->AddRebarLayer(-10,10,1.0),E_INVALIDARG);
   TRY_TEST(beam->AddRebarLayer(10,-10,1.0),E_INVALIDARG);
   TRY_TEST(beam->AddRebarLayer(10, 10,-1.0),E_INVALIDARG);
   TRY_TEST(beam->AddRebarLayer(40,40,2.0),E_INVALIDARG);
   TRY_TEST(beam->AddRebarLayer(10,10,1.0),S_OK);
   TRY_TEST(beam->AddRebarLayer(20,20,0.5),S_OK);
   TRY_TEST(beam->AddRebarLayer(30,30,0.0),S_OK);
   TRY_TEST(beam->get_RebarLayerCount(NULL),E_POINTER);
   TRY_TEST(beam->get_RebarLayerCount(&count),S_OK);
   TRY_TEST(count,3);
   TRY_TEST(beam->get_RebarLayerDepth(-1,&val),E_INVALIDARG);
   TRY_TEST(beam->get_RebarLayerDepth(0,NULL),E_POINTER);
   TRY_TEST(beam->get_RebarLayerDepth(0,&val),S_OK);
   TRY_TEST(IsEqual(val,10.0),true);
   TRY_TEST(beam->get_RebarLayerSteel(-1,&val),E_INVALIDARG);
   TRY_TEST(beam->get_RebarLayerSteel(10,&val),E_INVALIDARG);
   TRY_TEST(beam->get_RebarLayerSteel(0,NULL),E_POINTER);
   TRY_TEST(beam->get_RebarLayerSteel(0,&val),S_OK);
   TRY_TEST(IsEqual(val,10.0),true);
   TRY_TEST(beam->get_RebarLayerDevFactor(-1,&val),E_INVALIDARG);
   TRY_TEST(beam->get_RebarLayerDevFactor(10,&val),E_INVALIDARG);
   TRY_TEST(beam->get_RebarLayerDevFactor(0,NULL),E_POINTER);
   TRY_TEST(beam->get_RebarLayerDevFactor(0,&val),S_OK);
   TRY_TEST(IsEqual(val,1.0),true);
   TRY_TEST(beam->GetRebarLayer(-1,&val1,&val2,&val3),E_INVALIDARG);
   TRY_TEST(beam->GetRebarLayer(10,&val1,&val2,&val3),E_INVALIDARG);
   TRY_TEST(beam->GetRebarLayer(1,NULL,&val2,&val3),E_POINTER);
   TRY_TEST(beam->GetRebarLayer(1,&val1,NULL,&val3),E_POINTER);
   TRY_TEST(beam->GetRebarLayer(1,&val1,&val2,NULL),E_POINTER);
   TRY_TEST(beam->GetRebarLayer(1,&val1,&val2,&val3),S_OK);
   TRY_TEST(IsEqual(val1,20.0),true);
   TRY_TEST(IsEqual(val2,20.0),true);
   TRY_TEST(IsEqual(val3, 0.5),true);
   TRY_TEST(beam->RemoveRebarLayer(-1),E_INVALIDARG);
   TRY_TEST(beam->RemoveRebarLayer(10),E_INVALIDARG);
   TRY_TEST(beam->RemoveRebarLayer(1),S_OK);
   TRY_TEST(beam->get_RebarLayerCount(&count),S_OK);
   TRY_TEST(count,2);
   TRY_TEST(beam->ClearRebarLayers(),S_OK);
   TRY_TEST(beam->get_RebarLayerCount(&count),S_OK);
   TRY_TEST(count,0);

   TRY_TEST(beam->AddStrandLayer(-10,10,1.0),E_INVALIDARG);
   TRY_TEST(beam->AddStrandLayer(10,-10,1.0),E_INVALIDARG);
   TRY_TEST(beam->AddStrandLayer(10, 10,-1.0),E_INVALIDARG);
   TRY_TEST(beam->AddStrandLayer(40,40,2.0),E_INVALIDARG);
   TRY_TEST(beam->AddStrandLayer(10,10,1.0),S_OK);
   TRY_TEST(beam->AddStrandLayer(20,20,0.5),S_OK);
   TRY_TEST(beam->AddStrandLayer(30,30,0.0),S_OK);
   TRY_TEST(beam->get_StrandLayerCount(NULL),E_POINTER);
   TRY_TEST(beam->get_StrandLayerCount(&count),S_OK);
   TRY_TEST(count,3);
   TRY_TEST(beam->get_StrandLayerDepth(-1,&val),E_INVALIDARG);
   TRY_TEST(beam->get_StrandLayerDepth(0,NULL),E_POINTER);
   TRY_TEST(beam->get_StrandLayerDepth(0,&val),S_OK);
   TRY_TEST(IsEqual(val,10.0),true);
   TRY_TEST(beam->get_StrandLayerSteel(-1,&val),E_INVALIDARG);
   TRY_TEST(beam->get_StrandLayerSteel(10,&val),E_INVALIDARG);
   TRY_TEST(beam->get_StrandLayerSteel(0,NULL),E_POINTER);
   TRY_TEST(beam->get_StrandLayerSteel(0,&val),S_OK);
   TRY_TEST(IsEqual(val,10.0),true);
   TRY_TEST(beam->get_StrandLayerDevFactor(-1,&val),E_INVALIDARG);
   TRY_TEST(beam->get_StrandLayerDevFactor(10,&val),E_INVALIDARG);
   TRY_TEST(beam->get_StrandLayerDevFactor(0,NULL),E_POINTER);
   TRY_TEST(beam->get_StrandLayerDevFactor(0,&val),S_OK);
   TRY_TEST(IsEqual(val,1.0),true);
   TRY_TEST(beam->GetStrandLayer(-1,&val1,&val2,&val3),E_INVALIDARG);
   TRY_TEST(beam->GetStrandLayer(10,&val1,&val2,&val3),E_INVALIDARG);
   TRY_TEST(beam->GetStrandLayer(1,NULL,&val2,&val3),E_POINTER);
   TRY_TEST(beam->GetStrandLayer(1,&val1,NULL,&val3),E_POINTER);
   TRY_TEST(beam->GetStrandLayer(1,&val1,&val2,NULL),E_POINTER);
   TRY_TEST(beam->GetStrandLayer(1,&val1,&val2,&val3),S_OK);
   TRY_TEST(IsEqual(val1,20.0),true);
   TRY_TEST(IsEqual(val2,20.0),true);
   TRY_TEST(IsEqual(val3, 0.5),true);
   TRY_TEST(beam->RemoveStrandLayer(-1),E_INVALIDARG);
   TRY_TEST(beam->RemoveStrandLayer(10),E_INVALIDARG);
   TRY_TEST(beam->RemoveStrandLayer(1),S_OK);
   TRY_TEST(beam->get_StrandLayerCount(&count),S_OK);
   TRY_TEST(count,2);
   TRY_TEST(beam->ClearStrandLayers(),S_OK);
   TRY_TEST(beam->get_StrandLayerCount(&count),S_OK);
   TRY_TEST(count,0);

   TRY_TEST(beam->put_b(-10),E_INVALIDARG);
   TRY_TEST(beam->put_b(10), S_OK);
   TRY_TEST(beam->get_b(NULL), E_POINTER);
   TRY_TEST(beam->get_b(&val), S_OK);
   TRY_TEST( IsEqual(val,10.0), true );

   TRY_TEST(beam->put_bw(-10),E_INVALIDARG);
   TRY_TEST(beam->put_bw(10), S_OK);
   TRY_TEST(beam->get_bw(NULL), E_POINTER);
   TRY_TEST(beam->get_bw(&val), S_OK);
   TRY_TEST( IsEqual(val,10.0), true );

   TRY_TEST(beam->put_h(-10),E_INVALIDARG);
   TRY_TEST(beam->put_h(10), S_OK);
   TRY_TEST(beam->get_h(NULL), E_POINTER);
   TRY_TEST(beam->get_h(&val), S_OK);
   TRY_TEST( IsEqual(val,10.0), true );

   TRY_TEST(beam->put_hf(-10),E_INVALIDARG);
   TRY_TEST(beam->put_hf(10), S_OK);
   TRY_TEST(beam->get_hf(NULL), E_POINTER);
   TRY_TEST(beam->get_hf(&val), S_OK);
   TRY_TEST( IsEqual(val,10.0), true );

   TRY_TEST(beam->put_Eps(-10),E_INVALIDARG);
   TRY_TEST(beam->put_Eps(0),E_INVALIDARG);
   TRY_TEST(beam->put_Eps(10), S_OK);
   TRY_TEST(beam->get_Eps(NULL), E_POINTER);
   TRY_TEST(beam->get_Eps(&val), S_OK);
   TRY_TEST( IsEqual(val,10.0), true );

   TRY_TEST(beam->put_Es(-10),E_INVALIDARG);
   TRY_TEST(beam->put_Es(0),E_INVALIDARG);
   TRY_TEST(beam->put_Es(10), S_OK);
   TRY_TEST(beam->get_Es(NULL), E_POINTER);
   TRY_TEST(beam->get_Es(&val), S_OK);
   TRY_TEST( IsEqual(val,10.0), true );

   TRY_TEST(beam->put_FcBeam(-10),E_INVALIDARG);
   TRY_TEST(beam->put_FcBeam(0),E_INVALIDARG);
   TRY_TEST(beam->put_FcBeam(10), S_OK);
   TRY_TEST(beam->get_FcBeam(NULL), E_POINTER);
   TRY_TEST(beam->get_FcBeam(&val), S_OK);
   TRY_TEST( IsEqual(val,10.0), true );

   TRY_TEST(beam->put_FcSlab(-10),E_INVALIDARG);
   TRY_TEST(beam->put_FcSlab(0),E_INVALIDARG);
   TRY_TEST(beam->put_FcSlab(10), S_OK);
   TRY_TEST(beam->get_FcSlab(NULL), E_POINTER);
   TRY_TEST(beam->get_FcSlab(&val), S_OK);
   TRY_TEST( IsEqual(val,10.0), true );

   TRY_TEST(beam->put_fpe(-10),E_INVALIDARG);
   TRY_TEST(beam->put_fpe(10), S_OK);
   TRY_TEST(beam->get_fpe(NULL), E_POINTER);
   TRY_TEST(beam->get_fpe(&val), S_OK);
   TRY_TEST( IsEqual(val,10.0), true );

   TRY_TEST(beam->put_fpu(-10),E_INVALIDARG);
   TRY_TEST(beam->put_fpu(10), S_OK);
   TRY_TEST(beam->get_fpu(NULL), E_POINTER);
   TRY_TEST(beam->get_fpu(&val), S_OK);
   TRY_TEST( IsEqual(val,10.0), true );

   TRY_TEST(beam->put_fpy(-10),E_INVALIDARG);
   TRY_TEST(beam->put_fpy(10), S_OK);
   TRY_TEST(beam->get_fpy(NULL), E_POINTER);
   TRY_TEST(beam->get_fpy(&val), S_OK);
   TRY_TEST( IsEqual(val,10.0), true );

   TRY_TEST(beam->put_fy(-10),E_INVALIDARG);
   TRY_TEST(beam->put_fy(10), S_OK);
   TRY_TEST(beam->get_fy(NULL), E_POINTER);
   TRY_TEST(beam->get_fy(&val), S_OK);
   TRY_TEST( IsEqual(val,10.0), true );

   TestISupportUnitServer(beam);

   CComQIPtr<ISupportErrorInfo> eInfo(beam);
   TRY_TEST( eInfo != NULL, true);
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo(IID_IRCBeam2),            S_OK);
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo(IID_IStructuredStorage2), S_OK);
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo(IID_ISupportErrorInfo),   S_FALSE);
}
