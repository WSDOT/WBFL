///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 2001  Washington State Department of Transportation
//                   Bridge and Structures Office
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
// TestDistributedLoad.cpp: implementation of the CTestDistributedLoad class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestDistributedLoad.h"
#include <iostream> 

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestDistributedLoad::CTestDistributedLoad()
{

}

CTestDistributedLoad::~CTestDistributedLoad()
{

}

void CTestDistributedLoad::Test()
{
   // create a model
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

   CComPtr<IFem2dMemberCollection> pMembers;
   TRY_TEST_HR(pmodel->get_Members(&pMembers));

   CComPtr<IFem2dMember> pMember0,pMember3, pMember4,pMember7,ptj;
   TRY_TEST_MC(pMembers->Create(0,  0,  2, 100, 105, &pMember0));
   TRY_TEST_MC(pMembers->Create(3,  2,  5, 110, 115, &pMember3));

   CComPtr<IFem2dLoadingCollection> pLoadings;
   TRY_TEST_HR(pmodel->get_Loadings(&pLoadings));

   CComPtr<IFem2dLoading> pLoading0,pLoading3,pl;
   TRY_TEST_LC(pLoadings->Create(0, &pLoading0));
   TRY_TEST(pLoadings->Create(0, &pl),FEM2D_E_LOADING_WITH_ID_ALREADY_EXISTS);
   TRY_TEST_LC(pLoadings->Create(3, &pLoading3));

   CComPtr<IFem2dDistributedLoadCollection> pDistributedLoads;
   TRY_TEST_HR(pLoading0->get_DistributedLoads(&pDistributedLoads));

   CComPtr<IFem2dDistributedLoad> pDistributedLoad0,pDistributedLoad3,pPl;
   TRY_TEST_LC(pDistributedLoads->Create(0, 0, loadDirFy, 0.0, 23.2, 42.3, 52.3, lotMember, &pDistributedLoad0));
   TRY_TEST(pDistributedLoads->Create(0, 0, loadDirFx, 0, 0, 0, 0, lotMember, &pPl),FEM2D_E_DIST_LOAD_WITH_ID_ALREADY_EXISTS);
   TRY_TEST_LC(pDistributedLoads->Create(3, 5, loadDirFy, 1.0, 33.0, 44.0, 55.0, lotMember, &pDistributedLoad3));

   LoadIDType loadID;
   TRY_TEST_HR(pDistributedLoad3->get_ID(&loadID));
   TRY_TEST(loadID, 3);

   MemberIDType mbrID;
   TRY_TEST_HR(pDistributedLoad3->get_MemberID(&mbrID));
   TRY_TEST(mbrID, 5);

   TRY_TEST_LC(pDistributedLoad3->put_MemberID(42));
   TRY_TEST_HR(pDistributedLoad3->get_MemberID(&mbrID));
   TRY_TEST(mbrID, 42);

   Fem2dLoadOrientation or;
   TRY_TEST_HR(pDistributedLoad3->get_Orientation(&or));
   TRY_TEST(or, lotMember);
   TRY_TEST_LC(pDistributedLoad3->put_Orientation(lotGlobal));
   TRY_TEST_HR(pDistributedLoad3->get_Orientation(&or));
   TRY_TEST(or, lotGlobal);

   Fem2dLoadDirection dir;
   TRY_TEST_HR(pDistributedLoad3->get_Direction(&dir));
   TRY_TEST(dir, loadDirFy);
   TRY_TEST_LC(pDistributedLoad3->put_Direction(loadDirFx));
   TRY_TEST_HR(pDistributedLoad3->get_Direction(&dir));
   TRY_TEST(dir, loadDirFx);

   Float64 loc;
   TRY_TEST_HR(pDistributedLoad3->get_StartLocation(&loc));
   TRY_TEST(loc, 1.0);
   TRY_TEST_LC(pDistributedLoad3->put_StartLocation(-.45));
   TRY_TEST_HR(pDistributedLoad3->get_StartLocation(&loc));
   TRY_TEST(loc, -.45);
   TRY_TEST(pDistributedLoad3->put_StartLocation(-4),FEM2D_E_INVALID_DIST_LOAD_LOCATION);

   TRY_TEST_HR(pDistributedLoad3->get_EndLocation(&loc));
   TRY_TEST(loc, 33.0);
   TRY_TEST_LC(pDistributedLoad3->put_EndLocation(-.65));
   TRY_TEST_HR(pDistributedLoad3->get_EndLocation(&loc));
   TRY_TEST(loc, -.65);
   TRY_TEST(pDistributedLoad3->put_EndLocation(-4),FEM2D_E_INVALID_DIST_LOAD_LOCATION);

   Float64 w;
   TRY_TEST_HR(pDistributedLoad3->get_WStart(&w));
   TRY_TEST(w, 44.0);
   TRY_TEST_LC(pDistributedLoad3->put_WStart(-.45));
   TRY_TEST_HR(pDistributedLoad3->get_WStart(&w));
   TRY_TEST(w, -.45);

   TRY_TEST_HR(pDistributedLoad3->get_WEnd(&w));
   TRY_TEST(w, 55.0);
   TRY_TEST_LC(pDistributedLoad3->put_WEnd(-1.45));
   TRY_TEST_HR(pDistributedLoad3->get_WEnd(&w));
   TRY_TEST(w, -1.45);

   LoadCaseIDType ld;
   TRY_TEST_HR(pDistributedLoad3->get_Loading(&ld));
   TRY_TEST(ld, 0);

   ReleaseModel(pmodel);
}
