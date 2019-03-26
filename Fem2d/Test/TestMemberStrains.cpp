///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2019  Washington State Department of Transportation
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
// TestMemberStrains.cpp: implementation of the CTestMemberStrains class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestMemberStrains.h"
#include <MathEx.h>
#include <iostream> 

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction 
//////////////////////////////////////////////////////////////////////



CTestMemberStrains::CTestMemberStrains()
{

}

CTestMemberStrains::~CTestMemberStrains()
{

}

void CTestMemberStrains::Test()
{

   TestGeneral();
   Test1Bar();
   TestBar();
   TestBeam();
   TestBeam2();
}

void CTestMemberStrains::TestGeneral()
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
   TRY_TEST_HR(pLoadings->Create(2, &pLoading0));
   TRY_TEST(pLoadings->Create(2, &pl),FEM2D_E_LOADING_WITH_ID_ALREADY_EXISTS);
   TRY_TEST_HR(pLoadings->Create(3, &pLoading3));

   CComPtr<IFem2dMemberStrainCollection> pMemberStrains;
   TRY_TEST_HR(pLoading0->get_MemberStrains(&pMemberStrains));

   CComPtr<IFem2dMemberStrain> pMemberStrain0,pMemberStrain3,pPl;
   TRY_TEST_HR(pMemberStrains->Create(0, 0, 0.0, -1.0, 42.3, 52.3, &pMemberStrain0));
   TRY_TEST(pMemberStrains->Create(0, 0, 0, 0.0, -1.0, 0, &pPl),FEM2D_E_MEMBER_STRAIN_WITH_ID_ALREADY_EXISTS);
   TRY_TEST_HR(pMemberStrains->Create(3, 5, 0.0, -1.0, 33.0, 44.0, &pMemberStrain3));

   CollectionIndexType num;
   TRY_TEST_HR(pMemberStrains->get_Count(&num));
   TRY_TEST(num, 2);

   LoadIDType loadID;
   TRY_TEST_HR(pMemberStrain3->get_ID(&loadID));
   TRY_TEST(loadID, 3);

   MemberIDType mbrID;
   TRY_TEST_HR(pMemberStrain3->get_MemberID(&mbrID));
   TRY_TEST(mbrID, 5);

   TRY_TEST_HR(pMemberStrain3->put_MemberID(42));
   TRY_TEST_HR(pMemberStrain3->get_MemberID(&mbrID));
   TRY_TEST(mbrID, 42);

   Float64 ax, cx;
   TRY_TEST_HR(pMemberStrain3->get_AxialStrain(&ax));
   TRY_TEST_HR(pMemberStrain3->get_CurvatureStrain(&cx));
   TRY_TEST(ax, 33);
   TRY_TEST(cx, 44);

   TRY_TEST_HR(pMemberStrain3->put_AxialStrain(-11));
   TRY_TEST_HR(pMemberStrain3->put_CurvatureStrain(-12));
   TRY_TEST_HR(pMemberStrain3->get_AxialStrain(&ax));
   TRY_TEST_HR(pMemberStrain3->get_CurvatureStrain(&cx));
   TRY_TEST(ax, -11);
   TRY_TEST(cx, -12);

   // play some games with the reference counter
   pLoading0 = 0;
   ReleaseModel(pmodel);
   pmodel = 0;

   TRY_TEST_HR(pMemberStrain3->get_AxialStrain(&ax));
   TRY_TEST_HR(pMemberStrain3->get_CurvatureStrain(&cx));
   TRY_TEST(ax, -11);
   TRY_TEST(cx, -12);

   TRY_TEST(pMemberStrains->Remove(5,atID,&loadID),E_INVALIDARG);
   TRY_TEST_HR(pMemberStrains->Remove(3,atID,&loadID));
   TRY_TEST_HR(pMemberStrains->get_Count(&num));
   TRY_TEST(num, 1);

   pMemberStrains = 0;

   LoadCaseIDType ld;
   TRY_TEST_HR(pMemberStrain3->get_Loading(&ld));
   TRY_TEST(ld, 2);

}


void CTestMemberStrains::Test1Bar()
{
// create a model
   CComPtr<IFem2dModel> pmodel;
   pmodel = CreateModel();
   ATLASSERT(pmodel);

   // create joints
   CComPtr<IFem2dJointCollection> pJoints;
   TRY_TEST_HR(pmodel->get_Joints(&pJoints));

   CComPtr<IFem2dJoint> pJoint1,pJoint2,pJoint3;
   TRY_TEST_HR(pJoints->Create(1,   0.0,  0.0,      &pJoint1));
   TRY_TEST_HR(pJoints->Create(2,  10.0,  0.0,      &pJoint2));

   // let's start off by letting right end fly in the breeze and apply
   // strain load - member forces should be zero, but we should have 
   // non-zero Deflections
   // boundary conditions - leave right end free for now
   TRY_TEST_HR(pJoint1->Support());

   // create members
   CComPtr<IFem2dMemberCollection> pMembers;
   TRY_TEST_HR(pmodel->get_Members(&pMembers));

   Float64 E  =  29.0e06;
   Float64 EA =  2.0*E;
   Float64 EI = EA; // whatever
   CComPtr<IFem2dMember> pMember1,pMember2;
   TRY_TEST_HR(pMembers->Create(1,  1,  2, EA, EI, &pMember1));

   // put a single poi at mid-span
   CComPtr<IFem2dPOICollection> pPOIs;
   TRY_TEST_HR(pmodel->get_POIs(&pPOIs));
   CComPtr<IFem2dPOI> pPOI1;
   TRY_TEST_HR(pPOIs->Create(1,  1,  -.5, &pPOI1));

   // create load case
   CComPtr<IFem2dLoadingCollection> pLoadings;
   TRY_TEST_HR(pmodel->get_Loadings(&pLoadings));
   CComPtr<IFem2dLoading> pLoading;
   TRY_TEST_HR(pLoadings->Create(0, &pLoading));

   // apply member strain to member 2, first compute strain
   CComPtr<IFem2dMemberStrainCollection> pMemberStrains;
   TRY_TEST_HR(pLoading->get_MemberStrains(&pMemberStrains));

   CComPtr<IFem2dMemberStrain> pMemberStrain;
   Float64 strain = 0.002;
   TRY_TEST_HR(pMemberStrains->Create(0, 1, 0.0, -1.0, strain, 0.0, &pMemberStrain));

   // get results interface
   CComQIPtr<IFem2dModelResults> presults(pmodel);

   // get joint Deflections
   Float64 dx, dy, rz;
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 1, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) ); 
   TRY_TEST_B( IsEqual(dy, 0.0) ); 
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 2, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  0.02) );
   TRY_TEST_B( IsEqual(dy,  0.0) );
   TRY_TEST_B( IsEqual(rz,  0.0));

   // get member end forces
   Float64 sfx, sfy, smz, efx, efy, emz;
   TRY_TEST_HR(presults->ComputeMemberForces(0, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,   0.0));
   TRY_TEST_B( IsEqual(sfy,   0.0));
   TRY_TEST_B( IsEqual(smz,   0.0));
   TRY_TEST_B( IsEqual(efx,   0.0));
   TRY_TEST_B( IsEqual(efy,   0.0));
   TRY_TEST_B( IsEqual(emz,   0.0));

   Float64 fx, fy, mz;
   TRY_TEST_HR(presults->ComputeReactions(0, 1, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,    0.0));
   TRY_TEST_B( IsEqual(fy,    0.0));
   TRY_TEST_B( IsEqual(mz,    0.0));
   TRY_TEST_HR(presults->ComputeReactions(0, 2, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,    0.0));
   TRY_TEST_B( IsEqual(fy,    0.0));
   TRY_TEST_B( IsEqual(mz  ,  0.0));

   // poi results
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 1, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.01) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 0.0) );

   TRY_TEST_HR(presults->ComputePOIForces(0, 1, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));

   // now let's fix the other end
   TRY_TEST_HR(pJoint2->Support());

   // get joint Deflections
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 1, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) ); 
   TRY_TEST_B( IsEqual(dy, 0.0) ); 
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 2, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  0.0) );
   TRY_TEST_B( IsEqual(dy,  0.0) );
   TRY_TEST_B( IsEqual(rz,  0.0));

   // get member end forces
   TRY_TEST_HR(presults->ComputeMemberForces(0, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,   116000.0));
   TRY_TEST_B( IsEqual(sfy,        0.0));
   TRY_TEST_B( IsEqual(smz,        0.0));
   TRY_TEST_B( IsEqual(efx,  -116000.0));
   TRY_TEST_B( IsEqual(efy,        0.0));
   TRY_TEST_B( IsEqual(emz,        0.0));

   TRY_TEST_HR(presults->ComputeReactions(0, 1, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  116000.0));
   TRY_TEST_B( IsEqual(fy,    0.0));
   TRY_TEST_B( IsEqual(mz,    0.0));
   TRY_TEST_HR(presults->ComputeReactions(0, 2, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx, -116000.0));
   TRY_TEST_B( IsEqual(fy,       0.0));
   TRY_TEST_B( IsEqual(mz  ,     0.0));

   // poi results
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 1, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 0.0) );

   TRY_TEST_HR(presults->ComputePOIForces(0, 1, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  -116000.0));
   TRY_TEST_B( IsEqual(fy,        0.0));
   TRY_TEST_B( IsEqual(mz,        0.0));

   ReleaseModel(pmodel);
}



void CTestMemberStrains::TestBar()
{
// create a model
/*////////////////////////////////////////////////////

  Problem taken from "Matrix Analysis of Structures"
                      Robert F. Sennett, 1994
                      Chapter 1, Example 1.5

   Two-node bar with applied member strain

*/////////////////////////////////////////////////
   CComPtr<IFem2dModel> pmodel;
   pmodel = CreateModel();
   ATLASSERT(pmodel);

   // create joints
   CComPtr<IFem2dJointCollection> pJoints;
   TRY_TEST_HR(pmodel->get_Joints(&pJoints));

   CComPtr<IFem2dJoint> pJoint1,pJoint2,pJoint3;
   TRY_TEST_HR(pJoints->Create(1,   0.0,  0.0,      &pJoint1));
   TRY_TEST_HR(pJoints->Create(2,  10.0,  0.0,      &pJoint2));
   TRY_TEST_HR(pJoints->Create(3,  25.0,  0.0,      &pJoint3));

   // let's start off by letting right end fly in the breeze and apply
   // strain load - member forces should be zero, but we should have 
   // non-zero Deflections
   // boundary conditions - leave right end free for now
   TRY_TEST_HR(pJoint1->Support());

   // create members
   CComPtr<IFem2dMemberCollection> pMembers;
   TRY_TEST_HR(pmodel->get_Members(&pMembers));

   Float64 E  =  29.0e06;
   Float64 EA =  2.0*E;
   Float64 EI = EA; // whatever
   CComPtr<IFem2dMember> pMember1,pMember2;
   TRY_TEST_HR(pMembers->Create(1,  1,  2, EA, EI, &pMember1));
   TRY_TEST_HR(pMembers->Create(2,  2,  3, EA, EI, &pMember2));

   // create load case
   CComPtr<IFem2dLoadingCollection> pLoadings;
   TRY_TEST_HR(pmodel->get_Loadings(&pLoadings));
   CComPtr<IFem2dLoading> pLoading;
   TRY_TEST_HR(pLoadings->Create(0, &pLoading));

   // apply member strain to member 2, first compute strain
   Float64 strain = 60.0 * 6.5e-06;
   CComPtr<IFem2dMemberStrainCollection> pMemberStrains;
   TRY_TEST_HR(pLoading->get_MemberStrains(&pMemberStrains));

   CComPtr<IFem2dMemberStrain> pMemberStrain;
   TRY_TEST_HR(pMemberStrains->Create(0, 2, 0.0, -1.0, strain, 0.0, &pMemberStrain));

   // get results interface
   CComQIPtr<IFem2dModelResults> presults(pmodel);

   // get joint Deflections
   Float64 dx, dy, rz;
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 1, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) ); 
   TRY_TEST_B( IsEqual(dy, 0.0) ); 
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 2, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  0.0) );
   TRY_TEST_B( IsEqual(dy,  0.0) );
   TRY_TEST_B( IsEqual(rz,  0.0));
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 3, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  0.00585) );
   TRY_TEST_B( IsEqual(dy,  0.0));
   TRY_TEST_B( IsEqual(rz,  0.0));

   // get member end forces
   Float64 sfx, sfy, smz, efx, efy, emz;
   TRY_TEST_HR(presults->ComputeMemberForces(0, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,   0.0));
   TRY_TEST_B( IsEqual(sfy,   0.0));
   TRY_TEST_B( IsEqual(smz,   0.0));
   TRY_TEST_B( IsEqual(efx,   0.0));
   TRY_TEST_B( IsEqual(efy,   0.0));
   TRY_TEST_B( IsEqual(emz,   0.0));
   TRY_TEST_HR(presults->ComputeMemberForces(0, 2, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,   0.0));
   TRY_TEST_B( IsEqual(sfy,   0.0 ));
   TRY_TEST_B( IsEqual(smz,   0.0));
   TRY_TEST_B( IsEqual(efx,   0.0));
   TRY_TEST_B( IsEqual(efy,   0.0));
   TRY_TEST_B( IsEqual(emz,   0.0));

   Float64 fx, fy, mz;
   TRY_TEST_HR(presults->ComputeReactions(0, 1, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,    0.0));
   TRY_TEST_B( IsEqual(fy,    0.0));
   TRY_TEST_B( IsEqual(mz,    0.0));
   TRY_TEST_HR(presults->ComputeReactions(0, 2, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,    0.0));
   TRY_TEST_B( IsEqual(fy,    0.0));
   TRY_TEST_B( IsEqual(mz  ,  0.0));
   TRY_TEST_HR(presults->ComputeReactions(0, 3, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,    0.0));
   TRY_TEST_B( IsEqual(fy,    0.0));
   TRY_TEST_B( IsEqual(mz,    0.0));

   // now let's set up book problem. first boundary conditions
   TRY_TEST_HR(pJoint3->Support());

   // apply 10k load to joint 2
   CComPtr<IFem2dJointLoadCollection> pJointLoads;
   TRY_TEST_HR(pLoading->get_JointLoads(&pJointLoads));
   CComPtr<IFem2dJointLoad> pJointLoad;
   TRY_TEST_HR(pJointLoads->Create(0, 2, 10000.0, 0.0, 0.0, &pJointLoad));

   // get joint Deflections
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 1, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) ); 
   TRY_TEST_B( IsEqual(dy, 0.0) ); 
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 2, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, -0.001305517241) );
   TRY_TEST_B( IsEqual(dy,  0.0) );
   TRY_TEST_B( IsEqual(rz,  0.0));
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 3, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  0.0) );
   TRY_TEST_B( IsEqual(dy,  0.0));
   TRY_TEST_B( IsEqual(rz,  0.0));

   // get member end forces
   TRY_TEST_HR(presults->ComputeMemberForces(0, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,   7572.0));
   TRY_TEST_B( IsEqual(sfy,   0.0));
   TRY_TEST_B( IsEqual(smz,   0.0));
   TRY_TEST_B( IsEqual(efx,  -7572.0));
   TRY_TEST_B( IsEqual(efy,   0.0));
   TRY_TEST_B( IsEqual(emz,   0.0));
   TRY_TEST_HR(presults->ComputeMemberForces(0, 2, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,  17572.0));
   TRY_TEST_B( IsEqual(sfy,   0.0 ));
   TRY_TEST_B( IsEqual(smz,   0.0));
   TRY_TEST_B( IsEqual(efx, -17572.0));
   TRY_TEST_B( IsEqual(efy,   0.0));
   TRY_TEST_B( IsEqual(emz,   0.0));

   TRY_TEST_HR(presults->ComputeReactions(0, 1, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  7572.0));
   TRY_TEST_B( IsEqual(fy,    0.0));
   TRY_TEST_B( IsEqual(mz,    0.0));
   TRY_TEST_HR(presults->ComputeReactions(0, 2, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,    0.0));
   TRY_TEST_B( IsEqual(fy,    0.0));
   TRY_TEST_B( IsEqual(mz  ,  0.0));
   TRY_TEST_HR(presults->ComputeReactions(0, 3, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  -17572.0));
   TRY_TEST_B( IsEqual(fy,    0.0));
   TRY_TEST_B( IsEqual(mz,    0.0));

   ReleaseModel(pmodel);
}



void CTestMemberStrains::TestBeam()
{

//////////////////////////////////////////////

//   beam with strain loads

////////////////////////////////////////////////

   CComPtr<IFem2dModel> pmodel;
   pmodel = CreateModel();
   ATLASSERT(pmodel);

   // create joints
   CComPtr<IFem2dJointCollection> pJoints;
   TRY_TEST_HR(pmodel->get_Joints(&pJoints));

   CComPtr<IFem2dJoint> pJoint1,pJoint2;
   TRY_TEST_HR(pJoints->Create(1,  0.0,  0.0,  &pJoint1));
   TRY_TEST_HR(pJoints->Create(2, 10.0,  0.0,  &pJoint2));

   // boundary conditions
   // start off with end 2 free
   TRY_TEST_HR(pJoint1->Support());

   // create members
   CComPtr<IFem2dMemberCollection> pMembers;
   TRY_TEST_HR(pmodel->get_Members(&pMembers));

   Float64 EI = 2.90e06;;
   Float64 EA = EI; // whatever
   CComPtr<IFem2dMember> pMember1,pMember2;
   TRY_TEST_HR(pMembers->Create(1,  1,  2, EA, EI, &pMember1));

   // put a single poi at mid-span
   CComPtr<IFem2dPOICollection> pPOIs;
   TRY_TEST_HR(pmodel->get_POIs(&pPOIs));
   CComPtr<IFem2dPOI> pPOI1;
   TRY_TEST_HR(pPOIs->Create(1,  1,  -.5, &pPOI1));

   // create load case and member curvature of 0.002 length/radian
   CComPtr<IFem2dLoadingCollection> pLoadings;
   TRY_TEST_HR(pmodel->get_Loadings(&pLoadings));
   CComPtr<IFem2dLoading> pLoading;
   TRY_TEST_HR(pLoadings->Create(0, &pLoading));
   CComPtr<IFem2dMemberStrainCollection> pMemberStrains;
   TRY_TEST_HR(pLoading->get_MemberStrains(&pMemberStrains));
   CComPtr<IFem2dMemberStrain> pMemberStrain;
   TRY_TEST_HR(pMemberStrains->Create(0, 1, 0.0, -1.0, 0.0, 0.002, &pMemberStrain));

   // get results interface
   CComQIPtr<IFem2dModelResults> presults(pmodel);

   // get joint Deflections
   Float64 dx, dy, rz;
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 1, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );       // u1
   TRY_TEST_B( IsEqual(dy, 0.0) );       // u2
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 2, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) ); // u3
   TRY_TEST_B( IsEqual(dy, 0.1) ); // u4
   TRY_TEST_B( IsEqual(rz, 0.02));

   // get member end forces
   Float64 sfx, sfy, smz, efx, efy, emz;
   TRY_TEST_HR(presults->ComputeMemberForces(0, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,   0.0));
   TRY_TEST_B( IsEqual(sfy,   0.0));
   TRY_TEST_B( IsEqual(smz,   0.0));
   TRY_TEST_B( IsEqual(efx,   0.0));
   TRY_TEST_B( IsEqual(efy,   0.0));
   TRY_TEST_B( IsEqual(emz,   0.0));

   // reactions
   Float64 fx, fy, mz;
   TRY_TEST_HR(presults->ComputeReactions(0, 1, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   0.0));
   TRY_TEST_B( IsEqual(fy,   0.0));
   TRY_TEST_B( IsEqual(mz,   0.0));
   TRY_TEST_HR(presults->ComputeReactions(0, 2, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   0.0));
   TRY_TEST_B( IsEqual(fy,   0.0));
   TRY_TEST_B( IsEqual(mz,   0.0));

   // poi results
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 1, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.025) );
   TRY_TEST_B( IsEqual(rz, 0.01) );

   TRY_TEST_HR(presults->ComputePOIForces(0, 1, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));


   ////////////////////////////////////////////
   // now let's pin both ends
   TRY_TEST_HR(pJoint1->ReleaseDof(jrtMz));
   TRY_TEST_HR(pJoint2->Support());
   TRY_TEST_HR(pJoint2->ReleaseDof(jrtMz));

   TRY_TEST_HR(presults->ComputeJointDeflections(0, 1, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) ); 
   TRY_TEST_B( IsEqual(dy, 0.0) ); 
   TRY_TEST_B( IsEqual(rz,-0.01) );
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 2, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 0.01));

   // get member end forces
   TRY_TEST_HR(presults->ComputeMemberForces(0, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,   0.0));
   TRY_TEST_B( IsEqual(sfy,   0.0));
   TRY_TEST_B( IsEqual(smz,   0.0));
   TRY_TEST_B( IsEqual(efx,   0.0));
   TRY_TEST_B( IsEqual(efy,   0.0));
   TRY_TEST_B( IsEqual(emz,   0.0));

   TRY_TEST_HR(presults->ComputeReactions(0, 1, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   0.0));
   TRY_TEST_B( IsEqual(fy,   0.0));
   TRY_TEST_B( IsEqual(mz,   0.0));
   TRY_TEST_HR(presults->ComputeReactions(0, 2, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   0.0));
   TRY_TEST_B( IsEqual(fy,   0.0));
   TRY_TEST_B( IsEqual(mz,   0.0));

   // poi results
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 1, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, -0.025) );
   TRY_TEST_B( IsEqual(rz, 0.0) );

   TRY_TEST_HR(presults->ComputePOIForces(0, 1, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));


   ////////////////////////////////////////////
   // now let's fix both ends
   TRY_TEST_HR(pJoint1->Support());
   TRY_TEST_HR(pJoint2->Support());

   TRY_TEST_HR(presults->ComputeJointDeflections(0, 1, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) ); 
   TRY_TEST_B( IsEqual(dy, 0.0) ); 
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 2, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 0.0));

   // get member end forces
   TRY_TEST_HR(presults->ComputeMemberForces(0, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,    0.0));
   TRY_TEST_B( IsEqual(sfy,    0.0));
   TRY_TEST_B( IsEqual(smz, 5800.0));
   TRY_TEST_B( IsEqual(efx,    0.0));
   TRY_TEST_B( IsEqual(efy,    0.0));
   TRY_TEST_B( IsEqual(emz,-5800.0));

   TRY_TEST_HR(presults->ComputeReactions(0, 1, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,    0.0));
   TRY_TEST_B( IsEqual(fy,    0.0));
   TRY_TEST_B( IsEqual(mz, 5800.0));
   TRY_TEST_HR(presults->ComputeReactions(0, 2, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,    0.0));
   TRY_TEST_B( IsEqual(fy,    0.0));
   TRY_TEST_B( IsEqual(mz,-5800.0));

   // poi results
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 1, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 0.0) );

   TRY_TEST_HR(presults->ComputePOIForces(0, 1, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,    0.0));
   TRY_TEST_B( IsEqual(fy,    0.0));
   TRY_TEST_B( IsEqual(mz,-5800.0));

   TRY_TEST_HR(presults->ComputePOIForces(0, 1, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,    0.0));
   TRY_TEST_B( IsEqual(fy,    0.0));
   TRY_TEST_B( IsEqual(mz, 5800.0));

   ReleaseModel(pmodel);
}

void CTestMemberStrains::TestBeam2()
{

//////////////////////////////////////////////

//   beam with strain loads

////////////////////////////////////////////////

   CComPtr<IFem2dModel> pmodel;
   pmodel = CreateModel();
   ATLASSERT(pmodel);

   // create joints
   CComPtr<IFem2dJointCollection> pJoints;
   TRY_TEST_HR(pmodel->get_Joints(&pJoints));

   CComPtr<IFem2dJoint> pJoint1,pJoint2, pJoint3;
   TRY_TEST_HR(pJoints->Create(1,  0.0,  0.0,  &pJoint1));
   TRY_TEST_HR(pJoints->Create(2,  5.0,  0.0,  &pJoint2));
   TRY_TEST_HR(pJoints->Create(3, 10.0,  0.0,  &pJoint3));

   // boundary conditions
   // start off with end 2 free
   TRY_TEST_HR(pJoint1->Support());

   // create members
   CComPtr<IFem2dMemberCollection> pMembers;
   TRY_TEST_HR(pmodel->get_Members(&pMembers));

   Float64 EI = 2.90e06;;
   Float64 EA = EI; // whatever
   CComPtr<IFem2dMember> pMember1,pMember2;
   TRY_TEST_HR(pMembers->Create(1,  1,  2, EA, EI, &pMember1));
   TRY_TEST_HR(pMembers->Create(2,  2,  3, EA, EI, &pMember2));

   // put a single poi at mid-span
   CComPtr<IFem2dPOICollection> pPOIs;
   TRY_TEST_HR(pmodel->get_POIs(&pPOIs));
   CComPtr<IFem2dPOI> pPOI1;
   TRY_TEST_HR(pPOIs->Create(1,  1,  -1.0, &pPOI1));

   // create load case and member rotational strain of 0.002
   CComPtr<IFem2dLoadingCollection> pLoadings;
   TRY_TEST_HR(pmodel->get_Loadings(&pLoadings));
   CComPtr<IFem2dLoading> pLoading;
   TRY_TEST_HR(pLoadings->Create(0, &pLoading));
   CComPtr<IFem2dMemberStrainCollection> pMemberStrains;
   TRY_TEST_HR(pLoading->get_MemberStrains(&pMemberStrains));
   CComPtr<IFem2dMemberStrain> pMemberStrain1, pMemberStrain2;
   TRY_TEST_HR(pMemberStrains->Create(1, 1, 0.0, -1.0, 0.0, 0.002, &pMemberStrain1));
   TRY_TEST_HR(pMemberStrains->Create(2, 2, 0.0, -1.0, 0.0, 0.002, &pMemberStrain2));

   // get results interface
   CComQIPtr<IFem2dModelResults> presults(pmodel);

   // get joint Deflections
   Float64 dx, dy, rz;
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 1, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );       // u1
   TRY_TEST_B( IsEqual(dy, 0.0) );       // u2
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 2, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.025) );
   TRY_TEST_B( IsEqual(rz, 0.01) );
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 3, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) ); // u3
   TRY_TEST_B( IsEqual(dy, 0.1) ); // u4
   TRY_TEST_B( IsEqual(rz, 0.02));

   // get member end forces
   Float64 sfx, sfy, smz, efx, efy, emz;
   TRY_TEST_HR(presults->ComputeMemberForces(0, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,   0.0));
   TRY_TEST_B( IsEqual(sfy,   0.0));
   TRY_TEST_B( IsEqual(smz,   0.0));
   TRY_TEST_B( IsEqual(efx,   0.0));
   TRY_TEST_B( IsEqual(efy,   0.0));
   TRY_TEST_B( IsEqual(emz,   0.0));
   TRY_TEST_HR(presults->ComputeMemberForces(0, 2, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,   0.0));
   TRY_TEST_B( IsEqual(sfy,   0.0));
   TRY_TEST_B( IsEqual(smz,   0.0));
   TRY_TEST_B( IsEqual(efx,   0.0));
   TRY_TEST_B( IsEqual(efy,   0.0));
   TRY_TEST_B( IsEqual(emz,   0.0));

   // reactions
   Float64 fx, fy, mz;
   TRY_TEST_HR(presults->ComputeReactions(0, 1, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   0.0));
   TRY_TEST_B( IsEqual(fy,   0.0));
   TRY_TEST_B( IsEqual(mz,   0.0));
   TRY_TEST_HR(presults->ComputeReactions(0, 2, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   0.0));
   TRY_TEST_B( IsEqual(fy,   0.0));
   TRY_TEST_B( IsEqual(mz,   0.0));
   TRY_TEST_HR(presults->ComputeReactions(0, 3, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   0.0));
   TRY_TEST_B( IsEqual(fy,   0.0));
   TRY_TEST_B( IsEqual(mz,   0.0));

   // poi results
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 1, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.025) );
   TRY_TEST_B( IsEqual(rz, 0.01) );

   TRY_TEST_HR(presults->ComputePOIForces(0, 1, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));


   ////////////////////////////////////////////
   // now let's pin both ends
   TRY_TEST_HR(pJoint1->ReleaseDof(jrtMz));
   TRY_TEST_HR(pJoint3->Support());
   TRY_TEST_HR(pJoint3->ReleaseDof(jrtMz));

   TRY_TEST_HR(presults->ComputeJointDeflections(0, 1, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) ); 
   TRY_TEST_B( IsEqual(dy, 0.0) ); 
   TRY_TEST_B( IsEqual(rz,-0.01) );
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 2, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  0.0) ); 
   TRY_TEST_B( IsEqual(dy, -0.025) ); 
   TRY_TEST_B( IsEqual(rz,  0.0) );
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 3, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 0.01));

   // get member end forces
   TRY_TEST_HR(presults->ComputeMemberForces(0, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,   0.0));
   TRY_TEST_B( IsEqual(sfy,   0.0));
   TRY_TEST_B( IsEqual(smz,   0.0));
   TRY_TEST_B( IsEqual(efx,   0.0));
   TRY_TEST_B( IsEqual(efy,   0.0));
   TRY_TEST_B( IsEqual(emz,   0.0));
   TRY_TEST_HR(presults->ComputeMemberForces(0, 2, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,   0.0));
   TRY_TEST_B( IsEqual(sfy,   0.0));
   TRY_TEST_B( IsEqual(smz,   0.0));
   TRY_TEST_B( IsEqual(efx,   0.0));
   TRY_TEST_B( IsEqual(efy,   0.0));
   TRY_TEST_B( IsEqual(emz,   0.0));

   TRY_TEST_HR(presults->ComputeReactions(0, 1, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   0.0));
   TRY_TEST_B( IsEqual(fy,   0.0));
   TRY_TEST_B( IsEqual(mz,   0.0));
   TRY_TEST_HR(presults->ComputeReactions(0, 3, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   0.0));
   TRY_TEST_B( IsEqual(fy,   0.0));
   TRY_TEST_B( IsEqual(mz,   0.0));

   // poi results
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 1, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy,-0.025) );
   TRY_TEST_B( IsEqual(rz, 0.0) );

   TRY_TEST_HR(presults->ComputePOIForces(0, 1, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));

   ////////////////////////////////////////////
   // now let's fix both ends
   TRY_TEST_HR(pJoint1->Support());
   TRY_TEST_HR(pJoint3->Support());

   TRY_TEST_HR(presults->ComputeJointDeflections(0, 1, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) ); 
   TRY_TEST_B( IsEqual(dy, 0.0) ); 
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 2, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 0.0));
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 3, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 0.0));

   // get member end forces
   TRY_TEST_HR(presults->ComputeMemberForces(0, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,    0.0));
   TRY_TEST_B( IsEqual(sfy,    0.0));
   TRY_TEST_B( IsEqual(smz, 5800.0));
   TRY_TEST_B( IsEqual(efx,    0.0));
   TRY_TEST_B( IsEqual(efy,    0.0));
   TRY_TEST_B( IsEqual(emz,-5800.0));
   TRY_TEST_HR(presults->ComputeMemberForces(0, 2, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,    0.0));
   TRY_TEST_B( IsEqual(sfy,    0.0));
   TRY_TEST_B( IsEqual(smz, 5800.0));
   TRY_TEST_B( IsEqual(efx,    0.0));
   TRY_TEST_B( IsEqual(efy,    0.0));
   TRY_TEST_B( IsEqual(emz,-5800.0));

   TRY_TEST_HR(presults->ComputeReactions(0, 1, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,    0.0));
   TRY_TEST_B( IsEqual(fy,    0.0));
   TRY_TEST_B( IsEqual(mz, 5800.0));
   TRY_TEST_HR(presults->ComputeReactions(0, 2, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,    0.0));
   TRY_TEST_B( IsEqual(fy,    0.0));
   TRY_TEST_B( IsEqual(mz,    0.0));
   TRY_TEST_HR(presults->ComputeReactions(0, 3, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,    0.0));
   TRY_TEST_B( IsEqual(fy,    0.0));
   TRY_TEST_B( IsEqual(mz,-5800.0));

   // poi results
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 1, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 0.0) );

   TRY_TEST_HR(presults->ComputePOIForces(0, 1, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,    0.0));
   TRY_TEST_B( IsEqual(fy,    0.0));
   TRY_TEST_B( IsEqual(mz, -5800.0));

   TRY_TEST_HR(presults->ComputePOIForces(0, 1, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,    0.0));
   TRY_TEST_B( IsEqual(fy,    0.0));
   TRY_TEST_B( IsEqual(mz,  5800.0));

   ReleaseModel(pmodel);
}



