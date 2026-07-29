///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright � 1999-2026  Washington State Department of Transportation
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

// TestCompositeShapeItem.cpp
//
// Ported from F:\ARP\WBFL\Geometry\GeometryTest\TestCompositeShapeItem.cpp
// (legacy WBFLTest.h harness) to MSVC CppUnitTestFramework, talking to
// WBFLGeometry.dll purely through its public COM interfaces (see
// GeometryTestUtil.h).
#include "pch.h"

namespace GeometryUnitTests
{

TEST_CLASS(TestCompositeShapeItem)
{
public:
   TEST_METHOD(BasicOperations)
   {
         CComPtr<ICompositeShapeItem> item;
         ASSERT_EQ(item.CoCreateInstance(CLSID_CompositeShapeItem),S_OK);

         // Check default values
         VARIANT_BOOL bVoid;
         CComPtr<IShape> shape;

         ASSERT_EQ(item->get_Shape(nullptr),E_POINTER);
         ASSERT_EQ(item->get_Shape(&shape),S_OK);
         ASSERT_EQ(shape == 0,true);

         ASSERT_EQ(item->get_Void(nullptr),E_POINTER);
         ASSERT_EQ(item->get_Void(&bVoid),S_OK);
         ASSERT_EQ(bVoid,VARIANT_FALSE);


         ///////////////////////////////////////
         // Test ISupportErrorInfo
         CComPtr<ISupportErrorInfo> eInfo;
         ASSERT_EQ( eInfo.CoCreateInstance( CLSID_CompositeShapeItem ), S_OK );
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_ICompositeShapeItem ), S_OK );
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

         //////////////////////////////////////////////////////////////
         // Test IObjectSafety
         CComPtr<IObjectSafety> pObjSafety;
         ASSERT_EQ(pObjSafety.CoCreateInstance(CLSID_CompositeShapeItem), S_OK);
         DWORD dwDesiredOptions = INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA;
         DWORD dwSupportedOptions, dwEnabledOptions;
         pObjSafety->GetInterfaceSafetyOptions(IID_ICompositeShapeItem,&dwSupportedOptions,&dwEnabledOptions);
         ASSERT_EQ( dwSupportedOptions, dwDesiredOptions );
   }
};
} // namespace GeometryUnitTests