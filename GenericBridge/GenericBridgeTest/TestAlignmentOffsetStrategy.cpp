///////////////////////////////////////////////////////////////////////
// GenericBridgeTest - Test driver for generic bridge library
// Copyright © 1999-2018  Washington State Department of Transportation
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

// TestAlignmentOffsetStrategy.cpp: implementation of the CTestAlignmentOffsetStrategy class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestAlignmentOffsetStrategy.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestAlignmentOffsetStrategy::CTestAlignmentOffsetStrategy()
{

}

CTestAlignmentOffsetStrategy::~CTestAlignmentOffsetStrategy()
{

}

void CTestAlignmentOffsetStrategy::Test()
{
   HRESULT hr;
   CComPtr<IAlignmentOffsetStrategy> strategy;
   hr = strategy.CoCreateInstance(CLSID_AlignmentOffsetStrategy);
   TRY_TEST(hr,S_OK);
/*
   //////////////////////
   // Test default values
   Float64 value;
   TRY_TEST(strategy->get_Overhang(nullptr),E_POINTER);
   TRY_TEST(strategy->get_Overhang(&value),S_OK);
   TRY_TEST(IsZero(value),true);

   ///////////////////////////////////////
   // Test Set with event sink
   CComObject<CTestConstantOverhangStrategy>* pTestConstantOverhangStrategy;
   CComObject<CTestConstantOverhangStrategy>::CreateInstance(&pTestConstantOverhangStrategy);
   
   DWORD dwCookie;
   CComPtr<IUnknown> punk(pTestConstantOverhangStrategy);
   TRY_TEST(AtlAdvise(strategy,punk,IID_IDeckOverhangStrategyEvents,&dwCookie),S_OK);

   CComPtr<IWBFLTransactionMgr> txnMgr;
   txnMgr.CoCreateInstance(CLSID_TransactionMgr);

   CComQIPtr<IWBFLSupportTransactions> supTxns(strategy);
   TRY_TEST(supTxns != nullptr,true);
   TRY_TEST(supTxns->putref_TransactionMgr(txnMgr),S_OK);

   pTestConstantOverhangStrategy->InitEventTest();
   TRY_TEST(strategy->put_Overhang(0),S_OK);
   TRY_TEST(pTestConstantOverhangStrategy->PassedEventTest(), false );

   pTestConstantOverhangStrategy->InitEventTest();
   TRY_TEST(strategy->put_Overhang(10),S_OK);
   TRY_TEST(pTestConstantOverhangStrategy->PassedEventTest(), true );

   strategy->get_Overhang(&value);
   TRY_TEST(IsEqual(value,10.0),true);

   pTestConstantOverhangStrategy->InitEventTest();
   TRY_TEST(strategy->put_Overhang(-10),S_OK);
   TRY_TEST(pTestConstantOverhangStrategy->PassedEventTest(), true );

   strategy->get_Overhang(&value);
   TRY_TEST(IsEqual(value,-10.0),true);

   pTestConstantOverhangStrategy->InitEventTest();
   txnMgr->Undo();
   TRY_TEST(pTestConstantOverhangStrategy->PassedEventTest(), true );

   strategy->get_Overhang(&value);
   TRY_TEST(IsEqual(value,10.0),true);

   pTestConstantOverhangStrategy->InitEventTest();
   txnMgr->Undo();
   TRY_TEST(pTestConstantOverhangStrategy->PassedEventTest(), true );

   strategy->get_Overhang(&value);
   TRY_TEST(IsEqual(value,0.0),true);
*/
   ///////////////////////////////////////
   // Test Error Info
   CComQIPtr<ISupportErrorInfo> eInfo(strategy);
   TRY_TEST( eInfo != 0, true );

   // Interfaces that should be supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IAlignmentOffsetStrategy ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );

   // Interface that is not supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

   // Test IObjectSafety
   TRY_TEST( TestIObjectSafety(strategy,IID_IAlignmentOffsetStrategy,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
   TRY_TEST( TestIObjectSafety(strategy,IID_IStructuredStorage2,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
}
