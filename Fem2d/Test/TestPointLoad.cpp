///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
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
// TestPointLoad.cpp: implementation of the CTestPointLoad class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestPointLoad.h"
#include <iostream> 

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CTestPointLoad::CTestPointLoad()
{

}

CTestPointLoad::~CTestPointLoad()
{

}

void CTestPointLoad::Test()
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

   CComPtr<IFem2dPointLoadCollection> pPointLoads;
   TRY_TEST_HR(pLoading0->get_PointLoads(&pPointLoads));

   CComPtr<IFem2dPointLoad> pPointLoad0,pPointLoad3,pPl;
   TRY_TEST_LC(pPointLoads->Create(0, 0, 0.0, 23.2, 42.3, 52.3, lotMember, &pPointLoad0));
   TRY_TEST(pPointLoads->Create(0, 0, 0, 0, 0, 0, lotMember, &pPl),FEM2D_E_POINT_LOAD_WITH_ID_ALREADY_EXISTS);
   TRY_TEST_LC(pPointLoads->Create(3, 5, 1.0, 33.0, 44.0, 55.0, lotMember, &pPointLoad3));

   CollectionIndexType num;
   TRY_TEST_HR(pPointLoads->get_Count(&num));
   TRY_TEST(num, 2);

   LoadIDType loadID;
   TRY_TEST_HR(pPointLoad3->get_ID(&loadID));
   TRY_TEST(loadID, 3);

   MemberIDType mbrID;
   TRY_TEST_HR(pPointLoad3->get_MemberID(&mbrID));
   TRY_TEST(mbrID, 5);

   TRY_TEST_LC(pPointLoad3->put_MemberID(42));
   TRY_TEST_HR(pPointLoad3->get_MemberID(&mbrID));
   TRY_TEST(mbrID, 42);

   Fem2dLoadOrientation or;
   TRY_TEST_HR(pPointLoad3->get_Orientation(&or));
   TRY_TEST(or, lotMember);
   TRY_TEST_LC(pPointLoad3->put_Orientation(lotGlobal));
   TRY_TEST_HR(pPointLoad3->get_Orientation(&or));
   TRY_TEST(or, lotGlobal);

   Float64 loc;
   TRY_TEST_HR(pPointLoad3->get_Location(&loc));
   TRY_TEST(loc, 1.0);
   TRY_TEST_LC(pPointLoad3->put_Location(-.4));
   TRY_TEST_HR(pPointLoad3->get_Location(&loc));
   TRY_TEST(loc, -.4);
   TRY_TEST(pPointLoad3->put_Location(-4),FEM2D_E_INVALID_POINT_LOAD_LOCATION);

   Float64 fx, fy, mz;
   TRY_TEST_HR(pPointLoad3->get_Fx(&fx));
   TRY_TEST_HR(pPointLoad3->get_Fy(&fy));
   TRY_TEST_HR(pPointLoad3->get_Mz(&mz));
   TRY_TEST(fx, 33);
   TRY_TEST(fy, 44);
   TRY_TEST(mz, 55);

   TRY_TEST_LC(pPointLoad3->put_Fx(-11));
   TRY_TEST_LC(pPointLoad3->put_Fy(-12));
   TRY_TEST_LC(pPointLoad3->put_Mz(-13));
   TRY_TEST_HR(pPointLoad3->get_Fx(&fx));
   TRY_TEST_HR(pPointLoad3->get_Fy(&fy));
   TRY_TEST_HR(pPointLoad3->get_Mz(&mz));
   TRY_TEST(fx, -11);
   TRY_TEST(fy, -12);
   TRY_TEST(mz, -13);

   TRY_TEST_HR(pPointLoad3->GetForce(&fx, &fy, &mz));
   TRY_TEST(fx, -11);
   TRY_TEST(fy, -12);
   TRY_TEST(mz, -13);

   TRY_TEST_HR(pPointLoad3->SetForce(22, 23, 24));
   TRY_TEST_HR(pPointLoad3->GetForce(&fx, &fy, &mz));
   TRY_TEST(fx, 22 );
   TRY_TEST(fy, 23 );
   TRY_TEST(mz, 24 );

   // play some games with the reference counter
   pLoading0 = 0;

   TRY_TEST_HR(pPointLoad3->get_Fx(&fx));
   TRY_TEST_HR(pPointLoad3->get_Fy(&fy));
   TRY_TEST_HR(pPointLoad3->get_Mz(&mz));
   TRY_TEST(fx, 22 );
   TRY_TEST(fy, 23 );
   TRY_TEST(mz, 24 );

   TRY_TEST(pPointLoads->Remove(5,atID,&loadID),E_INVALIDARG);
   TRY_TEST_LC(pPointLoads->Remove(3,atID,&loadID));
   TRY_TEST_HR(pPointLoads->get_Count(&num));
   TRY_TEST(num, 1);

   ReleaseModel(pmodel);
   pmodel = 0;
   pPointLoads = 0;

   LoadCaseIDType ld;
   TRY_TEST_HR(pPointLoad3->get_Loading(&ld));
   TRY_TEST(ld, 0);

}
