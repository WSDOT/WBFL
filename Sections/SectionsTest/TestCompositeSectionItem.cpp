///////////////////////////////////////////////////////////////////////
// Sections Test - Test driver for Sections library
// Copyright © 1999-2016  Washington State Department of Transportation
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

// TestCompositeSectionItem.cpp: implementation of the CTestCompositeSectionItem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestCompositeSectionItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestCompositeSectionItem::CTestCompositeSectionItem()
{

}

CTestCompositeSectionItem::~CTestCompositeSectionItem()
{

}

void CTestCompositeSectionItem::Test()
{
   CComPtr<ICompositeSectionItem> item;
   TRY_TEST(item.CoCreateInstance(CLSID_CompositeSectionItem),S_OK);

   // Check default values
   Float64 density, E;
   VARIANT_BOOL bStructural, bVoid;
   CComPtr<IShape> shape;

   TRY_TEST(item->get_Density(NULL),E_POINTER);
   TRY_TEST(item->get_Density(&density),S_OK);
   TRY_TEST(IsEqual(density,1.0),true);

   TRY_TEST(item->get_E(NULL),E_POINTER);
   TRY_TEST(item->get_E(&E),S_OK);
   TRY_TEST(IsEqual(E,1.0),true);

   TRY_TEST(item->get_Shape(NULL),E_POINTER);
   TRY_TEST(item->get_Shape(&shape),S_OK);
   TRY_TEST(shape == 0,true);

   TRY_TEST(item->get_Structural(NULL),E_POINTER);
   TRY_TEST(item->get_Structural(&bStructural),S_OK);
   TRY_TEST(bStructural,VARIANT_TRUE);

   TRY_TEST(item->get_Void(NULL),E_POINTER);
   TRY_TEST(item->get_Void(&bVoid),S_OK);
   TRY_TEST(bVoid,VARIANT_FALSE);

   // Test for bad input values
   TRY_TEST(item->put_Density(-1),E_INVALIDARG);
   TRY_TEST(item->put_Density(0),E_INVALIDARG);
   TRY_TEST(item->put_E(-1),E_INVALIDARG);
   TRY_TEST(item->put_E(0),E_INVALIDARG);


   ///////////////////////////////////////
   // Test ISupportErrorInfo
   CComPtr<ISupportErrorInfo> eInfo;
   TRY_TEST( eInfo.CoCreateInstance( CLSID_CompositeSectionItem ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ICompositeSectionItem ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

   //////////////////////////////////////////////////////////////
   // Test IObjectSafety
   CComPtr<IObjectSafety> pObjSafety;
   TRY_TEST(pObjSafety.CoCreateInstance(CLSID_CompositeSectionItem), S_OK);
   DWORD dwDesiredOptions = INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA;
   DWORD dwSupportedOptions, dwEnabledOptions;
   pObjSafety->GetInterfaceSafetyOptions(IID_ICompositeSectionItem,&dwSupportedOptions,&dwEnabledOptions);
   TRY_TEST( dwSupportedOptions, dwDesiredOptions );
   pObjSafety->GetInterfaceSafetyOptions(IID_IStructuredStorage2,&dwSupportedOptions,&dwEnabledOptions);
   TRY_TEST( dwSupportedOptions, dwDesiredOptions );
}
