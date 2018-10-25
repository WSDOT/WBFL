///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2017  Washington State Department of Transportation
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

// TestSize3d.cpp: implementation of the CTestSize3d class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestSize3d.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestSize3d::CTestSize3d()
{

}

CTestSize3d::~CTestSize3d()
{

}

void CTestSize3d::Test()
{
   CComPtr<ISize3d> pSize;
   TRY_TEST(pSize.CoCreateInstance(CLSID_Size3d),S_OK);

   // Test Properties
   Float64 dx, dy, dz;
   Float64 dx1, dy1, dz1;
   dx = -10.0;
   dy = -20.0;
   dz = -30.0;
   TRY_TEST(pSize->put_Dx(dx),S_OK);
   TRY_TEST(pSize->get_Dx(NULL),E_POINTER);
   TRY_TEST(pSize->get_Dx(&dx1),S_OK);
   TRY_TEST(IsEqual(dx,dx1),true);

   TRY_TEST(pSize->put_Dy(dy),S_OK);
   TRY_TEST(pSize->get_Dy(NULL),E_POINTER);
   TRY_TEST(pSize->get_Dy(&dy1),S_OK);
   TRY_TEST(IsEqual(dy,dy1),true);

   TRY_TEST(pSize->put_Dz(dz),S_OK);
   TRY_TEST(pSize->get_Dz(NULL),E_POINTER);
   TRY_TEST(pSize->get_Dz(&dz1),S_OK);
   TRY_TEST(IsEqual(dz,dz1),true);

   // Test Magnitude
   Float64 target = sqrt(dx*dx + dy*dy + dz*dz);
   Float64 mag;
   TRY_TEST(pSize->get_Magnitude(NULL),E_POINTER);
   TRY_TEST(pSize->get_Magnitude(&mag),S_OK);
   TRY_TEST(IsEqual(mag,target),true);

   // Test Scale
   Float64 scale = 15.0;
   TRY_TEST(pSize->Scale(scale),S_OK);

   TRY_TEST(pSize->get_Dx(&dx1),S_OK);
   TRY_TEST(IsEqual(dx*scale,dx1),true);

   TRY_TEST(pSize->get_Dy(&dy1),S_OK);
   TRY_TEST(IsEqual(dy*scale,dy1),true);

   TRY_TEST(pSize->get_Dz(&dz1),S_OK);
   TRY_TEST(IsEqual(dz*scale,dz1),true);

   TestISupportErrorInfo();
}

void CTestSize3d::TestISupportErrorInfo()
{
   CComPtr<ISupportErrorInfo> eInfo;
   TRY_TEST( eInfo.CoCreateInstance( CLSID_Size3d ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISize3d ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );
}
