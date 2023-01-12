///////////////////////////////////////////////////////////////////////
// GenericBridgeTest - Test driver for generic bridge library
// Copyright © 1999-2023  Washington State Department of Transportation
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

// TestTransversePierDescription.cpp: implementation of the CTestTransversePierDescription class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestTransversePierDescription.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestTransversePierDescription::CTestTransversePierDescription()
{

}

CTestTransversePierDescription::~CTestTransversePierDescription()
{

}

void CTestTransversePierDescription::Test()
{
   //// Create a default bridge
   //CComPtr<IGenericBridge> bridge;
   //bridge.CoCreateInstance(CLSID_GenericBridge);

   //bridge->InsertSpanAndPier(0, 10.00, qcbAfter, qcbRight);

   //CComPtr<IPierCollection> piers;
   //bridge->get_Piers(&piers);

   //CComPtr<IPier> pier;
   //piers->get_Item(0,&pier);

   //pier->CreateTransversePierDescription();

   //CComPtr<ITransversePierDescription> tpd;
   //pier->get_TransversePierDescription(&tpd);

   //TRY_TEST(tpd != nullptr, true);

   //// Verify default values
   //CComPtr<IPier> parentPier;
   //TRY_TEST(tpd->get_Pier(nullptr),E_POINTER);
   //TRY_TEST(tpd->get_Pier(&parentPier),S_OK);
   //TRY_TEST(pier.IsEqualObject(parentPier),true);

   //CComPtr<IColumnSpacing> columnSpacing;
   //TRY_TEST(tpd->get_ColumnSpacing(nullptr),E_POINTER);
   //TRY_TEST(tpd->get_ColumnSpacing(&columnSpacing),S_OK);

   //CComPtr<ICrossBeam> crossBeam;
   //TRY_TEST(tpd->get_CrossBeam(nullptr),E_POINTER);
   //TRY_TEST(tpd->get_CrossBeam(&crossBeam),S_OK);

   //CComPtr<IColumn> column;
   //TRY_TEST(tpd->get_Column(-1,&column),E_INVALIDARG);
   //TRY_TEST(tpd->get_Column(10,&column),E_INVALIDARG);
   //TRY_TEST(tpd->get_Column(0,nullptr),E_POINTER);
   //TRY_TEST(tpd->get_Column(0,&column),S_OK);


   /////////////////////////////////////////
   //// Test Error Info
   //CComQIPtr<ISupportErrorInfo> eInfo(tpd);
   //TRY_TEST( eInfo != 0, true );

   //// Interfaces that should be supported
   //TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ITransversePierDescription ), S_OK );
   //TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );

   //// Interface that is not supported
   //TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

   //// Test IObjectSafety
   //TRY_TEST( TestIObjectSafety(tpd,IID_ITransversePierDescription,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
   //TRY_TEST( TestIObjectSafety(tpd,IID_IStructuredStorage2,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
}
