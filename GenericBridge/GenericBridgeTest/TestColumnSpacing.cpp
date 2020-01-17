///////////////////////////////////////////////////////////////////////
// GenericBridgeTest - Test driver for generic bridge library
// Copyright © 1999-2020  Washington State Department of Transportation
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

// TestColumnSpacing.cpp: implementation of the CTestColumnSpacing class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestColumnSpacing.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestColumnSpacing::CTestColumnSpacing()
{

}

CTestColumnSpacing::~CTestColumnSpacing()
{

}

void CTestColumnSpacing::Test()
{
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

   //CComPtr<IColumnSpacing> spacing;
   //tpd->get_ColumnSpacing(&spacing);

   //TRY_TEST(spacing != nullptr,true);

   //// Test default values
   //ColumnIndexType nColumns;
   //TRY_TEST(spacing->get_ColumnCount(nullptr),E_POINTER);
   //TRY_TEST(spacing->get_ColumnCount(&nColumns),S_OK);
   //TRY_TEST(nColumns,1);

   //Float64 space;
   //TRY_TEST(spacing->get_Spacing(0,nullptr),E_POINTER);
   //TRY_TEST(spacing->get_Spacing(100,&space),S_OK); // S_OK because spacing is uniform
   //TRY_TEST(spacing->get_Spacing(0,&space),S_OK);
   //TRY_TEST(IsEqual(space,1.0),true);
   //TRY_TEST(spacing->get_Spacing(0,&space),S_OK);
   //TRY_TEST(IsEqual(space,1.0),true);

   //Float64 overhang;
   //TRY_TEST(spacing->get_Overhang(qcbLeft,nullptr),E_POINTER);
   //TRY_TEST(spacing->get_Overhang(qcbLeft,&overhang),S_OK);
   //TRY_TEST(IsEqual(overhang,0.0),true);
   //TRY_TEST(spacing->get_Overhang(qcbRight,&overhang),S_OK);
   //TRY_TEST(IsEqual(overhang,0.0),true);

   //CComPtr<IColumn> column;
   //TRY_TEST(spacing->get_Column(0,nullptr),E_POINTER);
   //TRY_TEST(spacing->get_Column(-1,&column),E_INVALIDARG);
   //TRY_TEST(spacing->get_Column(100,&column),E_INVALIDARG);
   //TRY_TEST(spacing->get_Column(0,&column),S_OK);
   //TRY_TEST(column != nullptr, true);

   //VARIANT_BOOL bUniform;
   //TRY_TEST(spacing->get_Uniform(nullptr),E_POINTER);
   //TRY_TEST(spacing->get_Uniform(&bUniform),S_OK);
   //TRY_TEST(bUniform,VARIANT_TRUE);

   //// Test Methods
   //TRY_TEST(spacing->Add(0),S_OK);
   //TRY_TEST(spacing->Add(2),S_OK);
   //TRY_TEST(spacing->get_ColumnCount(&nColumns),S_OK);
   //TRY_TEST(nColumns,3);

   //// Non-uniform spacing
   //// 10' 5'
   //spacing->put_Uniform(VARIANT_FALSE);
   //spacing->put_Spacing(0,10.0);
   //spacing->put_Spacing(1, 5.0);

   //// Insert
   //TRY_TEST(spacing->Insert(100,1),GB_E_SPACEINDEX);
   //TRY_TEST(spacing->Insert(0,0), E_INVALIDARG);
   //TRY_TEST(spacing->Insert(0,1), S_OK);
   //TRY_TEST(spacing->Insert(3,1), S_OK);

   //spacing->get_ColumnCount(&nColumns);
   //TRY_TEST(nColumns,5);

   //spacing->get_Spacing(0,&space);
   //TRY_TEST(IsEqual(space,10.0),true);

   //spacing->get_Spacing(1,&space);
   //TRY_TEST(IsEqual(space,10.0),true);

   //spacing->get_Spacing(2,&space);
   //TRY_TEST(IsEqual(space,5.0),true);

   //spacing->get_Spacing(3,&space);
   //TRY_TEST(IsEqual(space,5.0),true);

   //spacing->get_Spacing(4,&space);
   //TRY_TEST(IsEqual(space,5.0),true);

   //TRY_TEST(spacing->Insert(3,2), S_OK);

   //spacing->get_ColumnCount(&nColumns);
   //TRY_TEST(nColumns,7);

   //spacing->get_Spacing(0,&space);
   //TRY_TEST(IsEqual(space,10.0),true);

   //spacing->get_Spacing(1,&space);
   //TRY_TEST(IsEqual(space,10.0),true);

   //spacing->get_Spacing(2,&space);
   //TRY_TEST(IsEqual(space,5.0),true);

   //spacing->get_Spacing(3,&space);
   //TRY_TEST(IsEqual(space,5.0),true);

   //spacing->get_Spacing(4,&space);
   //TRY_TEST(IsEqual(space,5.0),true);

   //spacing->get_Spacing(5,&space);
   //TRY_TEST(IsEqual(space,5.0),true);

   //spacing->get_Spacing(6,&space);
   //TRY_TEST(IsEqual(space,5.0),true);

   //TRY_TEST(spacing->put_Spacing(10,25.0),GB_E_SPACEINDEX);
   //TRY_TEST(spacing->put_Spacing(4,-1.0),GB_E_SPACING);
   //TRY_TEST(spacing->put_Spacing(4,25.0),S_OK);

   //// Remove
   //TRY_TEST(spacing->Remove(100,1),GB_E_SPACEINDEX);
   //TRY_TEST(spacing->Remove(1,0),E_INVALIDARG);
   //TRY_TEST(spacing->Remove(1,500),GB_E_LESS_THAN_MIN_COLUMNS);

   //TRY_TEST(spacing->Remove(4,2),S_OK); // Remove the 2 exterior girder lines that were inserted above

   //spacing->get_ColumnCount(&nColumns);
   //TRY_TEST(nColumns,5);

   //spacing->get_Spacing(0,&space);
   //TRY_TEST(IsEqual(space,10.0),true);

   //spacing->get_Spacing(1,&space);
   //TRY_TEST(IsEqual(space,10.0),true);

   //spacing->get_Spacing(2,&space);
   //TRY_TEST(IsEqual(space,5.0),true);

   //spacing->get_Spacing(3,&space);
   //TRY_TEST(IsEqual(space,5.0),true);

   //spacing->get_Spacing(4,&space);
   //TRY_TEST(IsEqual(space,5.0),true);

   //spacing->get_Spacing(5,&space);
   //TRY_TEST(IsEqual(space,5.0),true);

   //TRY_TEST(spacing->Remove(0,1), S_OK); // Remove the interior girder line that was added above

   //spacing->get_ColumnCount(&nColumns);
   //TRY_TEST(nColumns,4);

   //spacing->get_Spacing(0,&space);
   //TRY_TEST(IsEqual(space,10.0),true);

   //spacing->get_Spacing(1,&space);
   //TRY_TEST(IsEqual(space,5.0),true);

   //spacing->get_Spacing(2,&space);
   //TRY_TEST(IsEqual(space,5.0),true);

   //spacing->get_Spacing(3,&space);
   //TRY_TEST(IsEqual(space,5.0),true);

   /////////////////////////////////////////
   //// Test Error Info
   //CComQIPtr<ISupportErrorInfo> eInfo(spacing);
   //TRY_TEST( eInfo != 0, true );

   //// Interfaces that should be supported
   //TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IColumnSpacing ), S_OK );
   //TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );

   //// Interface that is not supported
   //TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

   //// Test IObjectSafety
   //TRY_TEST( TestIObjectSafety(spacing,IID_IColumnSpacing,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
   //TRY_TEST( TestIObjectSafety(spacing,IID_IStructuredStorage2,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
}
