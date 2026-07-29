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

// TestSize2d.cpp
//
// Ported from F:\ARP\WBFL\Geometry\GeometryTest\TestSize2d.cpp (legacy
// WBFLTest.h harness) to MSVC CppUnitTestFramework, talking to
// WBFLGeometry.dll purely through its public COM interfaces (see
// GeometryTestUtil.h).
#include "pch.h"

namespace GeometryUnitTests
{

TEST_CLASS(TestSize2d)
{
public:
   TEST_METHOD(BasicOperations)
   {
         CComPtr<ISize2d> pSize;
         ASSERT_EQ(pSize.CoCreateInstance(CLSID_Size2d),S_OK);

         // Test Properties
         Float64 dx, dy;
         Float64 dx1, dy1;
         dx = -10.0;
         dy = -20.0;
         ASSERT_EQ(pSize->put_Dx(dx),S_OK);
         ASSERT_EQ(pSize->get_Dx(nullptr),E_POINTER);
         ASSERT_EQ(pSize->get_Dx(&dx1),S_OK);
         ASSERT_EQ(IsEqual(dx,dx1),true);
         ASSERT_EQ(pSize->put_Dy(dy),S_OK);
         ASSERT_EQ(pSize->get_Dy(nullptr),E_POINTER);
         ASSERT_EQ(pSize->get_Dy(&dy1),S_OK);
         ASSERT_EQ(IsEqual(dy,dy1),true);

         // Test Magnitude
         Float64 target = sqrt(dx*dx + dy*dy);
         Float64 mag;
         ASSERT_EQ(pSize->get_Magnitude(nullptr),E_POINTER);
         ASSERT_EQ(pSize->get_Magnitude(&mag),S_OK);
         ASSERT_EQ(IsEqual(mag,target),true);

         // Test Scale
         Float64 scale = 15.0;
         ASSERT_EQ(pSize->Scale(scale),S_OK);
         ASSERT_EQ(pSize->get_Dx(&dx1),S_OK);
         ASSERT_EQ(IsEqual(dx*scale,dx1),true);
         ASSERT_EQ(pSize->get_Dy(&dy1),S_OK);
         ASSERT_EQ(IsEqual(dy*scale,dy1),true);
   }

   TEST_METHOD(SupportsErrorInfo)
   {
         CComPtr<ISupportErrorInfo> eInfo;
         ASSERT_EQ( eInfo.CoCreateInstance( CLSID_Size2d ), S_OK );
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_ISize2d ), S_OK );
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );
   }
};
} // namespace GeometryUnitTests