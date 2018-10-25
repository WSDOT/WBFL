///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
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
// TestPOI.cpp: implementation of the CTestPOI class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestPOI.h"
#include <iostream> 

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CTestPOI::CTestPOI()
{

}

CTestPOI::~CTestPOI()
{

}

void CTestPOI::Test()
{
   // fire up the model and create some joints
   CComPtr<IFem2dModel> pmodel;
   pmodel = CreateModel();
   ATLASSERT(pmodel);

   CComPtr<IFem2dJointCollection> pJoints;
   TRY_TEST_HR(pmodel->get_Joints(&pJoints));

   CComPtr<IFem2dJoint> pJoint0,pJoint2,pJoint4,pJoint5;
   TRY_TEST_MC(pJoints->Create(0,  2,  3, &pJoint0));
   TRY_TEST_MC(pJoints->Create(2, 22, 32, &pJoint2));
   TRY_TEST_MC(pJoints->Create(4, 44, 34, &pJoint4));
   TRY_TEST_MC(pJoints->Create(5, 55, 35, &pJoint5));

   // create some members
   CComPtr<IFem2dMemberCollection> pMembers;
   TRY_TEST_HR(pmodel->get_Members(&pMembers));

   CComPtr<IFem2dMember> pMember0,pMember3, pMember4;
   TRY_TEST_MC(pMembers->Create(0,  0,  2, 100, 105, &pMember0));
   TRY_TEST_MC(pMembers->Create(3,  2,  5, 110, 115, &pMember3));
   TRY_TEST_MC(pMembers->Create(4, 54,  5, 110, 115, &pMember4)); // joint doesn't exist

   // create some pois
   CComPtr<IFem2dPOICollection> pPOIs;
   TRY_TEST_HR(pmodel->get_POIs(&pPOIs));

   CComPtr<IFem2dPOI> pPOI0,pPOI3, pPOI4;
   TRY_TEST_HR(pPOIs->Create(0,  1,  -.5, &pPOI0));
   TRY_TEST_HR(pPOIs->Create(3,  4,  1.2, &pPOI3));
   TRY_TEST(pPOIs->Create(3,  4,  1.2, &pPOI4),FEM2D_E_POI_WITH_ID_ALREADY_EXISTS);
   TRY_TEST(pPOIs->Create(4,  4,  -12.0, &pPOI4),FEM2D_E_INVALID_POI_LOCATION); 

   PoiIDType id;
   MemberIDType mid;
   TRY_TEST_HR(pPOI0->get_ID(&id));
   TRY_TEST(id, 0);
   TRY_TEST_HR(pPOI3->get_ID(&id));
   TRY_TEST(id, 3);
   TRY_TEST_HR(pPOI0->get_MemberID(&mid));
   TRY_TEST(mid, 1);
   TRY_TEST_HR(pPOI3->get_MemberID(&mid));
   TRY_TEST(mid, 4);

   TRY_TEST_HR(pPOI3->put_MemberID(33));
   TRY_TEST_HR(pPOI3->get_MemberID(&mid));
   TRY_TEST(mid, 33);

   Float64 loc;
   TRY_TEST_HR(pPOI0->get_Location(&loc));
   TRY_TEST(loc, -0.5);
   TRY_TEST_HR(pPOI3->get_Location(&loc));
   TRY_TEST(loc, 1.2);

   TRY_TEST_HR(pPOI3->put_Location(23.3));
   TRY_TEST_HR(pPOI3->get_Location(&loc));
   TRY_TEST(loc, 23.3);

   TRY_TEST_HR(pPOI3->put_Location(-1.0));
   TRY_TEST(pPOI3->put_Location(-1.01),FEM2D_E_INVALID_POI_LOCATION);

   ReleaseModel(pmodel);
}
