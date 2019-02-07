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
// TestMemberStrains.cpp: implementation of the CTestMemberStrains2 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestMemberStrains2.h"
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



CTestMemberStrains2::CTestMemberStrains2()
{

}

CTestMemberStrains2::~CTestMemberStrains2()
{

}

void CTestMemberStrains2::Test()
{

   TestTruss();
   TestFrame();

   TestStrudlBeam();
   TestStrudlBeam2();
}


void CTestMemberStrains2::TestTruss()
{
// create a model
/*////////////////////////////////////////////////////

  Problem taken from "Matrix Analysis of Structures"
                      Robert F. Sennett, 1994
                      Chapter 2, Example 2.6

   simple truss with temperature load applied to top member

*/////////////////////////////////////////////////

   CComPtr<IFem2dModel> pmodel;
   pmodel = CreateModel();
   ATLASSERT(pmodel);

   // create joints
   CComPtr<IFem2dJointCollection> pJoints;
   TRY_TEST_HR(pmodel->get_Joints(&pJoints));

   CComPtr<IFem2dJoint> pJoint1,pJoint2,pJoint3,pJoint4;
   TRY_TEST_MC(pJoints->Create(1,  0.0,       0.0,      &pJoint1));
   TRY_TEST_MC(pJoints->Create(2, 10.0*12.0, 10.0*12.0, &pJoint2));
   TRY_TEST_MC(pJoints->Create(3, 20.0*12.0, 10.0*12.0, &pJoint3));
   TRY_TEST_MC(pJoints->Create(4, 30.0*12.0,  0.0,      &pJoint4));

   // boundary conditions
   TRY_TEST_MC(pJoint1->Support());
   TRY_TEST_MC(pJoint2->Support());
   TRY_TEST_MC(pJoint2->ReleaseDof(jrtFx));
   TRY_TEST_MC(pJoint2->ReleaseDof(jrtFy));
   TRY_TEST_MC(pJoint3->Support());
   TRY_TEST_MC(pJoint3->ReleaseDof(jrtFx));
   TRY_TEST_MC(pJoint3->ReleaseDof(jrtFy));
   TRY_TEST_MC(pJoint4->Support());

   // create members
   CComPtr<IFem2dMemberCollection> pMembers;
   TRY_TEST_HR(pmodel->get_Members(&pMembers));

   Float64 E = 29.0e06;;
   Float64 EA = E * 2.0;
   Float64 EI = 1.0e29; // dummy since all members are pinned
   CComPtr<IFem2dMember> pMember1,pMember2,pMember3,pMember4,pMember5;
   TRY_TEST_MC(pMembers->Create(1,  1,  2, EA, EI, &pMember1));
   TRY_TEST_MC(pMembers->Create(2,  2,  3, EA, EI, &pMember2));
   TRY_TEST_MC(pMembers->Create(3,  3,  4, EA, EI, &pMember3));
   TRY_TEST_MC(pMembers->Create(4,  1,  3, EA, EI, &pMember4));
   TRY_TEST_MC(pMembers->Create(5,  2,  4, EA, EI, &pMember5));

   // pin 'em
   TRY_TEST_MC(pMember1->ReleaseEnd(metStart, mbrReleaseMz));
   TRY_TEST_MC(pMember1->ReleaseEnd(metEnd,   mbrReleaseMz));
   TRY_TEST_MC(pMember2->ReleaseEnd(metStart, mbrReleaseMz));
   TRY_TEST_MC(pMember2->ReleaseEnd(metEnd,   mbrReleaseMz));
   TRY_TEST_MC(pMember3->ReleaseEnd(metStart, mbrReleaseMz));
   TRY_TEST_MC(pMember3->ReleaseEnd(metEnd,   mbrReleaseMz));
   TRY_TEST_MC(pMember4->ReleaseEnd(metStart, mbrReleaseMz));
   TRY_TEST_MC(pMember4->ReleaseEnd(metEnd,   mbrReleaseMz));
   TRY_TEST_MC(pMember5->ReleaseEnd(metStart, mbrReleaseMz));
   TRY_TEST_MC(pMember5->ReleaseEnd(metEnd,   mbrReleaseMz));

   // create load case and apply point load to joint
   CComPtr<IFem2dLoadingCollection> pLoadings;
   TRY_TEST_HR(pmodel->get_Loadings(&pLoadings));
   CComPtr<IFem2dLoading> pLoading;
   TRY_TEST_LC(pLoadings->Create(0, &pLoading));
   CComPtr<IFem2dMemberStrainCollection> pMemberStrains;
   TRY_TEST_HR(pLoading->get_MemberStrains(&pMemberStrains));

   Float64 strain = -40.0 * 6.5e-6;
   CComPtr<IFem2dMemberStrain> pMemberStrain;
   TRY_TEST_LC(pMemberStrains->Create(0, 2, 0.0, -1.0, strain, 0.0, &pMemberStrain));

   // get results interface
   CComQIPtr<IFem2dModelResults> presults(pmodel);

   // get joint Deflections
   Float64 dx, dy, rz;
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 1, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );    // u1
   TRY_TEST_B( IsEqual(dy, 0.0) );    // u2
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 2, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.011807202783764 ) ); // u3
   TRY_TEST_B( IsEqual(dy,-0.004655435767055 ) ); // u4
   TRY_TEST_B( IsEqual(rz, 0.0));
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 3, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,-0.011807202783764) );   // u5
   TRY_TEST_B( IsEqual(dy,-0.004655435767055) );   // u6
   TRY_TEST_B( IsEqual(rz, 0.0));
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 4, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,-0.0) ); // u7
   TRY_TEST_B( IsEqual(dy,-0.0) ); // u8
   TRY_TEST_B( IsEqual(rz, 0.0));

   // get member end forces
   Float64 sfx, sfy, smz, efx, efy, emz;
   TRY_TEST_HR(presults->ComputeMemberForces(0, 2, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx, -3666.37064));
   TRY_TEST_B( IsEqual(sfy,     0.0));
   TRY_TEST_B( IsEqual(smz,     0.0));
   TRY_TEST_B( IsEqual(efx,  3666.37064));
   TRY_TEST_B( IsEqual(efy,     0.0));
   TRY_TEST_B( IsEqual(emz,     0.0));
   TRY_TEST_HR(presults->ComputeMemberForces(0, 4, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,  2732.7513290) );
   TRY_TEST_B( IsEqual(sfy,     0.0));
   TRY_TEST_B( IsEqual(smz,     0.0));
   TRY_TEST_B( IsEqual(efx, -2732.7513290));
   TRY_TEST_B( IsEqual(efy,     0.0));
   TRY_TEST_B( IsEqual(emz,     0.0));

   Float64 fx, fy, mz;
   TRY_TEST_HR(presults->ComputeReactions(0, 1, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx, 1222.1235474538));
   TRY_TEST_B( IsEqual(fy,    0.0));
   TRY_TEST_B( IsEqual(mz,    0.0));
   TRY_TEST_HR(presults->ComputeReactions(0, 4, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,-1222.1235474538));
   TRY_TEST_B( IsEqual(fy,    0.0)); // has point load added in
   TRY_TEST_B( IsEqual(mz,    0.0));

   ReleaseModel(pmodel);
}


void CTestMemberStrains2::TestStrudlBeam()
{

//////////////////////////////////////////////

//   beam with strain loads
//   Verified using GT-Strudl - output file is TempLoads.gto

////////////////////////////////////////////////

   CComPtr<IFem2dModel> pmodel;
   pmodel = CreateModel();
   ATLASSERT(pmodel);

   // create joints
   CComPtr<IFem2dJointCollection> pJoints;
   TRY_TEST_HR(pmodel->get_Joints(&pJoints));

   CComPtr<IFem2dJoint> pJoint1,pJoint2, pJoint3, pJoint4, pJoint5;
   TRY_TEST_MC(pJoints->Create(1,  0.0,  0.0,  &pJoint1));
   TRY_TEST_MC(pJoints->Create(2, 25.0,  0.0,  &pJoint2));
   TRY_TEST_MC(pJoints->Create(3, 50.0,  0.0,  &pJoint3));
   TRY_TEST_MC(pJoints->Create(4, 75.0,  0.0,  &pJoint4));
   TRY_TEST_MC(pJoints->Create(5,100.0,  0.0,  &pJoint5));

   // boundary conditions
   TRY_TEST_MC(pJoint1->Support());
   TRY_TEST_MC(pJoint5->Support());

   // create members
   Float64 E = 100.0;
   Float64 A = 100.0;
   Float64 I = 833.333;
   Float64 EA = E*A;
   Float64 EI = E*I;

   CComPtr<IFem2dMemberCollection> pMembers;
   TRY_TEST_HR(pmodel->get_Members(&pMembers));
   CComPtr<IFem2dMember> pMember1,pMember2,pMember3,pMember4;
   TRY_TEST_MC(pMembers->Create(1,  1,  2, EA, EI, &pMember1));
   TRY_TEST_MC(pMembers->Create(2,  2,  3, EA, EI, &pMember2));
   TRY_TEST_MC(pMembers->Create(3,  3,  4, EA, EI, &pMember3));
   TRY_TEST_MC(pMembers->Create(4,  4,  5, EA, EI, &pMember4));

   // put a pois at quarter points on members 1 and 3
   CComPtr<IFem2dPOICollection> pPOIs;
   TRY_TEST_HR(pmodel->get_POIs(&pPOIs));
   CComPtr<IFem2dPOI> pPOI1_000,pPOI1_025,pPOI1_050,pPOI1_075,pPOI1_100;
   TRY_TEST_HR(pPOIs->Create(1000,  1,  0.00, &pPOI1_000));
   TRY_TEST_HR(pPOIs->Create(1025,  1, -0.25, &pPOI1_025));
   TRY_TEST_HR(pPOIs->Create(1050,  1, -0.50, &pPOI1_050));
   TRY_TEST_HR(pPOIs->Create(1075,  1, -0.75, &pPOI1_075));
   TRY_TEST_HR(pPOIs->Create(1100,  1, -1.00, &pPOI1_100));

   CComPtr<IFem2dPOI> pPOI3_000,pPOI3_025,pPOI3_050,pPOI3_075,pPOI3_100;
   TRY_TEST_HR(pPOIs->Create(3000,  3,  0.00, &pPOI3_000));
   TRY_TEST_HR(pPOIs->Create(3025,  3, -0.25, &pPOI3_025));
   TRY_TEST_HR(pPOIs->Create(3050,  3, -0.50, &pPOI3_050));
   TRY_TEST_HR(pPOIs->Create(3075,  3, -0.75, &pPOI3_075));
   TRY_TEST_HR(pPOIs->Create(3100,  3, -1.00, &pPOI3_100));

   // create load cases and member strains
   // coeff of thermal expansion = 1.0
   // delta T = 800.0 degrees
   // section depth = 10.0
   Float64 strain = 0.1 * 800.0 / 10.0;

   CComPtr<IFem2dLoadingCollection> pLoadings;
   TRY_TEST_HR(pmodel->get_Loadings(&pLoadings));
   CComPtr<IFem2dLoading> pLoading1,pLoading2,pLoading3,pLoading4,pLoading5;

   // loading 1 - all members loaded
   TRY_TEST_HR(pLoadings->Create(1, &pLoading1));
   CComPtr<IFem2dMemberStrainCollection> pMemberStrains;
   TRY_TEST_HR(pLoading1->get_MemberStrains(&pMemberStrains));
   CComPtr<IFem2dMemberStrain> pMemberStrain1, pMemberStrain2, pMemberStrain3, pMemberStrain4;
   TRY_TEST_LC(pMemberStrains->Create(1, 1, 0.0, -1.0, 0.0, strain, &pMemberStrain1));
   TRY_TEST_LC(pMemberStrains->Create(2, 2, 0.0, -1.0, 0.0, strain, &pMemberStrain2));
   TRY_TEST_LC(pMemberStrains->Create(3, 3, 0.0, -1.0, 0.0, strain, &pMemberStrain3));
   TRY_TEST_LC(pMemberStrains->Create(4, 4, 0.0, -1.0, 0.0, strain, &pMemberStrain4));

   // loading 2 - all members 1 and 3 loaded
   TRY_TEST_HR(pLoadings->Create(2, &pLoading2));
   pMemberStrains = 0;
   TRY_TEST_HR(pLoading2->get_MemberStrains(&pMemberStrains));
   pMemberStrain1 = pMemberStrain2 = pMemberStrain3 = pMemberStrain4 = 0;
   TRY_TEST_LC(pMemberStrains->Create(1, 1, 0.0, -1.0, 0.0, strain, &pMemberStrain1));
   TRY_TEST_LC(pMemberStrains->Create(3, 3, 0.0, -1.0, 0.0, strain, &pMemberStrain3));

   // loading 3 - all members 2 and 4 loaded
   TRY_TEST_HR(pLoadings->Create(3, &pLoading3));
   pMemberStrains = 0;
   TRY_TEST_HR(pLoading3->get_MemberStrains(&pMemberStrains));
   pMemberStrain1 = pMemberStrain2 = pMemberStrain3 = pMemberStrain4 = 0;
   TRY_TEST_LC(pMemberStrains->Create(2, 2, 0.0, -1.0, 0.0, strain, &pMemberStrain2));
   TRY_TEST_LC(pMemberStrains->Create(4, 4, 0.0, -1.0, 0.0, strain, &pMemberStrain4));

   // loading 4 - members 1 loaded only
   TRY_TEST_HR(pLoadings->Create(4, &pLoading4));
   pMemberStrains = 0;
   TRY_TEST_HR(pLoading4->get_MemberStrains(&pMemberStrains));
   pMemberStrain1 = pMemberStrain2 = pMemberStrain3 = pMemberStrain4 = 0;
   TRY_TEST_LC(pMemberStrains->Create(1, 1, 0.0, -1.0, 0.0, strain, &pMemberStrain1));

   // loading 5 - members 4 loaded only
   TRY_TEST_LC(pLoadings->Create(5, &pLoading5));
   pMemberStrains = 0;
   TRY_TEST_HR(pLoading5->get_MemberStrains(&pMemberStrains));
   pMemberStrain1 = pMemberStrain2 = pMemberStrain3 = pMemberStrain4 = 0;
   TRY_TEST_LC(pMemberStrains->Create(1, 4, 0.0, -1.0, 0.0, strain, &pMemberStrain4));

   // get results interface
   CComQIPtr<IFem2dModelResults> presults(pmodel);

   // results for loading 1
   LoadCaseIDType lc = 1;
   // get joint Deflections
   Float64 dx, dy, rz;
   TRY_TEST_HR(presults->ComputeJointDeflections(lc, 1, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) ); 
   TRY_TEST_B( IsEqual(dy, 0.0) ); 
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputeJointDeflections(lc, 2, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) ); 
   TRY_TEST_B( IsEqual(dy, 0.0) ); 
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputeJointDeflections(lc, 3, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) ); 
   TRY_TEST_B( IsEqual(dy, 0.0) ); 
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputeJointDeflections(lc, 4, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) ); 
   TRY_TEST_B( IsEqual(dy, 0.0) ); 
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputeJointDeflections(lc, 5, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) ); 
   TRY_TEST_B( IsEqual(dy, 0.0) ); 
   TRY_TEST_B( IsEqual(rz, 0.0) );

   // get member end forces
   Float64 sfx, sfy, smz, efx, efy, emz;
   TRY_TEST_HR(presults->ComputeMemberForces(lc, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,   0.0));
   TRY_TEST_B( IsEqual(sfy,   0.0));
   TRY_TEST_B( IsEqual(smz,  666666.40));
   TRY_TEST_B( IsEqual(efx,   0.0));
   TRY_TEST_B( IsEqual(efy,   0.0));
   TRY_TEST_B( IsEqual(emz, -666666.40));
   TRY_TEST_HR(presults->ComputeMemberForces(lc, 2, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,   0.0));
   TRY_TEST_B( IsEqual(sfy,   0.0));
   TRY_TEST_B( IsEqual(smz,  666666.40));
   TRY_TEST_B( IsEqual(efx,   0.0));
   TRY_TEST_B( IsEqual(efy,   0.0));
   TRY_TEST_B( IsEqual(emz, -666666.40));
   TRY_TEST_HR(presults->ComputeMemberForces(lc, 3, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,   0.0));
   TRY_TEST_B( IsEqual(sfy,   0.0));
   TRY_TEST_B( IsEqual(smz,  666666.40));
   TRY_TEST_B( IsEqual(efx,   0.0));
   TRY_TEST_B( IsEqual(efy,   0.0));
   TRY_TEST_B( IsEqual(emz, -666666.40));
   TRY_TEST_HR(presults->ComputeMemberForces(lc, 4, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,   0.0));
   TRY_TEST_B( IsEqual(sfy,   0.0));
   TRY_TEST_B( IsEqual(smz,  666666.40));
   TRY_TEST_B( IsEqual(efx,   0.0));
   TRY_TEST_B( IsEqual(efy,   0.0));
   TRY_TEST_B( IsEqual(emz, -666666.40));

   // reactions
   Float64 fx, fy, mz;
   TRY_TEST_HR(presults->ComputeReactions(lc, 1, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   0.0));
   TRY_TEST_B( IsEqual(fy,   0.0));
   TRY_TEST_B( IsEqual(mz,   666666.40));
   TRY_TEST_HR(presults->ComputeReactions(lc, 2, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   0.0));
   TRY_TEST_B( IsEqual(fy,   0.0));
   TRY_TEST_B( IsEqual(mz,   0.0));
   TRY_TEST_HR(presults->ComputeReactions(lc, 3, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   0.0));
   TRY_TEST_B( IsEqual(fy,   0.0));
   TRY_TEST_B( IsEqual(mz,   0.0));
   TRY_TEST_HR(presults->ComputeReactions(lc, 4, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   0.0));
   TRY_TEST_B( IsEqual(fy,   0.0));
   TRY_TEST_B( IsEqual(mz,   0.0));
   TRY_TEST_HR(presults->ComputeReactions(lc, 5, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   0.0));
   TRY_TEST_B( IsEqual(fy,   0.0));
   TRY_TEST_B( IsEqual(mz,  -666666.40));

   // poi results
   TRY_TEST_HR(presults->ComputePOIDeflections(lc, 1000, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDeflections(lc, 1050, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDeflections(lc, 1100, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 0.0) );

   TRY_TEST_HR(presults->ComputePOIForces(lc, 1100, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz, -666666.40));
   TRY_TEST_HR(presults->ComputePOIForces(lc, 1100, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  666666.40));
   TRY_TEST_HR(presults->ComputePOIForces(lc, 1075, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz, -666666.40));
   TRY_TEST_HR(presults->ComputePOIForces(lc, 1075, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  666666.40));

   // results for loading 2
   lc = 2;
   // get joint Deflections
   TRY_TEST_HR(presults->ComputeJointDeflections(lc, 1, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) ); 
   TRY_TEST_B( IsEqual(dy, 0.0) ); 
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputeJointDeflections(lc, 2, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) ); 
   TRY_TEST_B( IsEqual(dy, 468.7500000) ); 
   TRY_TEST_B( IsEqual(rz, 43.75) );
   TRY_TEST_HR(presults->ComputeJointDeflections(lc, 3, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) ); 
   TRY_TEST_B( IsEqual(dy, 0.0) ); 
   TRY_TEST_B( IsEqual(rz,-75.0) );
   TRY_TEST_HR(presults->ComputeJointDeflections(lc, 4, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) ); 
   TRY_TEST_B( IsEqual(dy,-468.7500000) ); 
   TRY_TEST_B( IsEqual(rz, 43.75) );
   TRY_TEST_HR(presults->ComputeJointDeflections(lc, 5, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) ); 
   TRY_TEST_B( IsEqual(dy, 0.0) ); 
   TRY_TEST_B( IsEqual(rz, 0.0) );

   // get member end forces
   TRY_TEST_HR(presults->ComputeMemberForces(lc, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,   0.0));
   TRY_TEST_B( IsEqual(sfy,  4999.99800));
   TRY_TEST_B( IsEqual(smz,  583333.09999));
   TRY_TEST_B( IsEqual(efx,   0.0));
   TRY_TEST_B( IsEqual(efy, -4999.99800));
   TRY_TEST_B( IsEqual(emz, -458333.15000));
   TRY_TEST_HR(presults->ComputeMemberForces(lc, 2, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,   0.0));
   TRY_TEST_B( IsEqual(sfy,  4999.99800));
   TRY_TEST_B( IsEqual(smz, 458333.15000));
   TRY_TEST_B( IsEqual(efx,   0.0));
   TRY_TEST_B( IsEqual(efy, -4999.99800));
   TRY_TEST_B( IsEqual(emz, -333333.20000));
   TRY_TEST_HR(presults->ComputeMemberForces(lc, 3, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,   0.0));
   TRY_TEST_B( IsEqual(sfy,  4999.99800));
   TRY_TEST_B( IsEqual(smz, 333333.20000));
   TRY_TEST_B( IsEqual(efx,   0.0));
   TRY_TEST_B( IsEqual(efy, -4999.99800));
   TRY_TEST_B( IsEqual(emz, -208333.24999));
   TRY_TEST_HR(presults->ComputeMemberForces(lc, 4, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,   0.0));
   TRY_TEST_B( IsEqual(sfy,  4999.9980));
   TRY_TEST_B( IsEqual(smz, 208333.24999));
   TRY_TEST_B( IsEqual(efx,   0.0));
   TRY_TEST_B( IsEqual(efy, -4999.99800));
   TRY_TEST_B( IsEqual(emz, -83333.30000));

   // reactions
   TRY_TEST_HR(presults->ComputeReactions(lc, 1, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   0.0));
   TRY_TEST_B( IsEqual(fy,  4999.99800));
   TRY_TEST_B( IsEqual(mz,  583333.09999));
   TRY_TEST_HR(presults->ComputeReactions(lc, 2, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   0.0));
   TRY_TEST_B( IsEqual(fy,   0.0));
   TRY_TEST_B( IsEqual(mz,   0.0));
   TRY_TEST_HR(presults->ComputeReactions(lc, 3, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   0.0));
   TRY_TEST_B( IsEqual(fy,   0.0));
   TRY_TEST_B( IsEqual(mz,   0.0));
   TRY_TEST_HR(presults->ComputeReactions(lc, 4, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   0.0));
   TRY_TEST_B( IsEqual(fy,   0.0));
   TRY_TEST_B( IsEqual(mz,   0.0));
   TRY_TEST_HR(presults->ComputeReactions(lc, 5, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   0.0));
   TRY_TEST_B( IsEqual(fy,-4999.99800));
   TRY_TEST_B( IsEqual(mz,-83333.30000));

   // poi results
   TRY_TEST_HR(presults->ComputePOIDeflections(lc, 1000, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDeflections(lc, 1050, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy,  97.656250000000) );
   TRY_TEST_B( IsEqual(rz,  17.187500000000) );
   TRY_TEST_HR(presults->ComputePOIDeflections(lc, 1100, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 468.7500000) ); 
   TRY_TEST_B( IsEqual(rz, 43.75) );

   TRY_TEST_HR(presults->ComputePOIForces(lc, 1100, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -4999.99800));
   TRY_TEST_B( IsEqual(mz, -458333.15000));
   TRY_TEST_HR(presults->ComputePOIForces(lc, 1100, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  4999.99800));
   TRY_TEST_B( IsEqual(mz,  458333.15000));
   TRY_TEST_HR(presults->ComputePOIForces(lc, 1075, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -4999.99800));
   TRY_TEST_B( IsEqual(mz, -489583.13750 ));
   TRY_TEST_HR(presults->ComputePOIForces(lc, 1075, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  4999.99800));
   TRY_TEST_B( IsEqual(mz,  489583.1375 ));

   // results for loading 5
   lc = 5;
   // get joint Deflections
   TRY_TEST_HR(presults->ComputeJointDeflections(lc, 1, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) ); 
   TRY_TEST_B( IsEqual(dy, 0.0) ); 
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputeJointDeflections(lc, 2, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) ); 
   TRY_TEST_B( IsEqual(dy, 546.8750000) ); 
   TRY_TEST_B( IsEqual(rz, 34.375) );
   TRY_TEST_HR(presults->ComputeJointDeflections(lc, 3, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) ); 
   TRY_TEST_B( IsEqual(dy,  1250.0) ); 
   TRY_TEST_B( IsEqual(rz,  12.50) );
   TRY_TEST_HR(presults->ComputeJointDeflections(lc, 4, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) ); 
   TRY_TEST_B( IsEqual(dy, 703.125) ); 
   TRY_TEST_B( IsEqual(rz,-65.625) );
   TRY_TEST_HR(presults->ComputeJointDeflections(lc, 5, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) ); 
   TRY_TEST_B( IsEqual(dy, 0.0) ); 
   TRY_TEST_B( IsEqual(rz, 0.0) );

   // get member end forces
   TRY_TEST_HR(presults->ComputeMemberForces(lc, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,   0.0));
   TRY_TEST_B( IsEqual(sfy, -7499.99700));
   TRY_TEST_B( IsEqual(smz, -208333.25000));
   TRY_TEST_B( IsEqual(efx,   0.0));
   TRY_TEST_B( IsEqual(efy,  7499.99700));
   TRY_TEST_B( IsEqual(emz,  20833.32500));
   TRY_TEST_HR(presults->ComputeMemberForces(lc, 2, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,   0.0));
   TRY_TEST_B( IsEqual(sfy, -7499.99700));
   TRY_TEST_B( IsEqual(smz,-20833.32500));
   TRY_TEST_B( IsEqual(efx,   0.0));
   TRY_TEST_B( IsEqual(efy,  7499.99700));
   TRY_TEST_B( IsEqual(emz, -166666.60000));
   TRY_TEST_HR(presults->ComputeMemberForces(lc, 3, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,   0.0));
   TRY_TEST_B( IsEqual(sfy, -7499.99700));
   TRY_TEST_B( IsEqual(smz, 166666.60000));
   TRY_TEST_B( IsEqual(efx,   0.0));
   TRY_TEST_B( IsEqual(efy,  7499.99700));
   TRY_TEST_B( IsEqual(emz, -354166.52500));
   TRY_TEST_HR(presults->ComputeMemberForces(lc, 4, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,   0.0));
   TRY_TEST_B( IsEqual(sfy, -7499.99700));
   TRY_TEST_B( IsEqual(smz, 354166.52500));
   TRY_TEST_B( IsEqual(efx,   0.0));
   TRY_TEST_B( IsEqual(efy,  7499.99700));
   TRY_TEST_B( IsEqual(emz, -541666.45000));

   // reactions
   TRY_TEST_HR(presults->ComputeReactions(lc, 1, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   0.0));
   TRY_TEST_B( IsEqual(fy, -7499.99700));
   TRY_TEST_B( IsEqual(mz, -208333.25000));
   TRY_TEST_HR(presults->ComputeReactions(lc, 2, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   0.0));
   TRY_TEST_B( IsEqual(fy,   0.0));
   TRY_TEST_B( IsEqual(mz,   0.0));
   TRY_TEST_HR(presults->ComputeReactions(lc, 3, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   0.0));
   TRY_TEST_B( IsEqual(fy,   0.0));
   TRY_TEST_B( IsEqual(mz,   0.0));
   TRY_TEST_HR(presults->ComputeReactions(lc, 4, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   0.0));
   TRY_TEST_B( IsEqual(fy,   0.0));
   TRY_TEST_B( IsEqual(mz,   0.0));
   TRY_TEST_HR(presults->ComputeReactions(lc, 5, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   0.0));
   TRY_TEST_B( IsEqual(fy, 7499.99700));
   TRY_TEST_B( IsEqual(mz,-541666.45000));

   // poi results
   TRY_TEST_HR(presults->ComputePOIDeflections(lc, 1000, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDeflections(lc, 1050, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy,  166.01562500000) );
   TRY_TEST_B( IsEqual(rz,  24.218750000000) );
   TRY_TEST_HR(presults->ComputePOIDeflections(lc, 1100, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 546.8750000) ); 
   TRY_TEST_B( IsEqual(rz, 34.375) );

   TRY_TEST_HR(presults->ComputePOIForces(lc, 1100, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  7499.99700));
   TRY_TEST_B( IsEqual(mz,  20833.32500));
   TRY_TEST_HR(presults->ComputePOIForces(lc, 1100, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -7499.99700));
   TRY_TEST_B( IsEqual(mz, -20833.32500));
   TRY_TEST_HR(presults->ComputePOIForces(lc, 1075, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  7499.99700));
   TRY_TEST_B( IsEqual(mz,  67708.30625 ));
   TRY_TEST_HR(presults->ComputePOIForces(lc, 1075, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -7499.99700));
   TRY_TEST_B( IsEqual(mz, -67708.30625));


   ReleaseModel(pmodel);

}

void CTestMemberStrains2::TestStrudlBeam2()
{

//////////////////////////////////////////////

//   beam with strain loads
//   Verified using GT-Strudl - output file is TempLoads.gto

// this problem differs from the strudl file in that only one member
// is used.

////////////////////////////////////////////////

   CComPtr<IFem2dModel> pmodel;
   pmodel = CreateModel();
   ATLASSERT(pmodel);

   // create joints
   CComPtr<IFem2dJointCollection> pJoints;
   TRY_TEST_HR(pmodel->get_Joints(&pJoints));

   CComPtr<IFem2dJoint> pJoint1,pJoint2;
   TRY_TEST_MC(pJoints->Create(1,  0.0,  0.0,  &pJoint1));
   TRY_TEST_MC(pJoints->Create(2,100.0,  0.0,  &pJoint2));

   // boundary conditions
   TRY_TEST_MC(pJoint1->Support());
   TRY_TEST_MC(pJoint2->Support());

   // create members
   Float64 E = 100.0;
   Float64 A = 100.0;
   Float64 I = 833.333;
   Float64 EA = E*A;
   Float64 EI = E*I;

   CComPtr<IFem2dMemberCollection> pMembers;
   TRY_TEST_HR(pmodel->get_Members(&pMembers));
   CComPtr<IFem2dMember> pMember1;
   TRY_TEST_MC(pMembers->Create(1,  1,  2, EA, EI, &pMember1));

   // put a pois at 1/16 points on quarter points 1 and 3
   CComPtr<IFem2dPOICollection> pPOIs;
   TRY_TEST_HR(pmodel->get_POIs(&pPOIs));
   CComPtr<IFem2dPOI> pPOI1_000,pPOI1_025,pPOI1_050,pPOI1_075,pPOI1_100;
   TRY_TEST_HR(pPOIs->Create(1000,  1,  0.00, &pPOI1_000));
   TRY_TEST_HR(pPOIs->Create(1025,  1, -0.0625, &pPOI1_025));
   TRY_TEST_HR(pPOIs->Create(1050,  1, -0.1250, &pPOI1_050));
   TRY_TEST_HR(pPOIs->Create(1075,  1, -0.1875, &pPOI1_075));
   TRY_TEST_HR(pPOIs->Create(1100,  1, -0.25, &pPOI1_100));

   CComPtr<IFem2dPOI> pPOI3_000,pPOI3_025,pPOI3_050,pPOI3_075,pPOI3_100;
   TRY_TEST_HR(pPOIs->Create(3000,  1, -0.50-0.00,   &pPOI3_000));
   TRY_TEST_HR(pPOIs->Create(3025,  1, -0.50-0.0625, &pPOI3_025));
   TRY_TEST_HR(pPOIs->Create(3050,  1, -0.50-0.1250, &pPOI3_050));
   TRY_TEST_HR(pPOIs->Create(3075,  1, -0.50-0.1875, &pPOI3_075));
   TRY_TEST_HR(pPOIs->Create(3100,  1, -0.50-0.25,   &pPOI3_100));

   // create load cases and member strains
   // coeff of thermal expansion = 1.0
   // delta T = 800.0 degrees
   // section depth = 10.0
   Float64 strain =  0.1 * 800.0 / 10.0;

   CComPtr<IFem2dLoadingCollection> pLoadings;
   TRY_TEST_HR(pmodel->get_Loadings(&pLoadings));
   CComPtr<IFem2dLoading> pLoading1,pLoading2,pLoading3,pLoading4,pLoading5;

   // can only model loading 1 since we only have a single member
   // loading 1 - all members loaded
   TRY_TEST_LC(pLoadings->Create(1, &pLoading1));
   CComPtr<IFem2dMemberStrainCollection> pMemberStrains;
   TRY_TEST_HR(pLoading1->get_MemberStrains(&pMemberStrains));
   CComPtr<IFem2dMemberStrain> pMemberStrain1, pMemberStrain2, pMemberStrain3, pMemberStrain4;
   TRY_TEST_LC(pMemberStrains->Create(1, 1, 0.0, -1.0, 0.0, strain, &pMemberStrain1));

   // get results interface
   CComQIPtr<IFem2dModelResults> presults(pmodel);

   // results for loading 1
   LoadCaseIDType lc = 1;
   // get joint Deflections
   Float64 dx, dy, rz;
   TRY_TEST_HR(presults->ComputeJointDeflections(lc, 1, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) ); 
   TRY_TEST_B( IsEqual(dy, 0.0) ); 
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputeJointDeflections(lc, 2, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) ); 
   TRY_TEST_B( IsEqual(dy, 0.0) ); 
   TRY_TEST_B( IsEqual(rz, 0.0) );

   // get member end forces
   Float64 sfx, sfy, smz, efx, efy, emz;
   TRY_TEST_HR(presults->ComputeMemberForces(lc, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,   0.0));
   TRY_TEST_B( IsEqual(sfy,   0.0));
   TRY_TEST_B( IsEqual(smz,  666666.40));
   TRY_TEST_B( IsEqual(efx,   0.0));
   TRY_TEST_B( IsEqual(efy,   0.0));
   TRY_TEST_B( IsEqual(emz, -666666.40));

   // reactions
   Float64 fx, fy, mz;
   TRY_TEST_HR(presults->ComputeReactions(lc, 1, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   0.0));
   TRY_TEST_B( IsEqual(fy,   0.0));
   TRY_TEST_B( IsEqual(mz,   666666.40));
   TRY_TEST_HR(presults->ComputeReactions(lc, 2, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   0.0));
   TRY_TEST_B( IsEqual(fy,   0.0));
   TRY_TEST_B( IsEqual(mz,  -666666.40));

   // poi results
   TRY_TEST_HR(presults->ComputePOIDeflections(lc, 1000, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDeflections(lc, 1100, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDeflections(lc, 3000, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDeflections(lc, 3100, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 0.0) );

   TRY_TEST_HR(presults->ComputePOIForces(lc, 1100, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz, -666666.40));
   TRY_TEST_HR(presults->ComputePOIForces(lc, 1100, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  666666.40));
   TRY_TEST_HR(presults->ComputePOIForces(lc, 1075, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz, -666666.40));
   TRY_TEST_HR(presults->ComputePOIForces(lc, 1075, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  666666.40));
   TRY_TEST_HR(presults->ComputePOIForces(lc, 3000, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz, -666666.40));
   TRY_TEST_HR(presults->ComputePOIForces(lc, 3000, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  666666.40));

//////////////////////////////////////////////////////////////
   // release the starting end of the beam
   TRY_TEST_MC(pMember1->ReleaseEnd(metStart, mbrReleaseMz));
   TRY_TEST_HR(presults->ComputeJointDeflections(lc, 1, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) ); 
   TRY_TEST_B( IsEqual(dy, 0.0) ); 
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputeJointDeflections(lc, 2, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) ); 
   TRY_TEST_B( IsEqual(dy, 0.0) ); 
   TRY_TEST_B( IsEqual(rz, 0.0) );

   // get member end forces
   TRY_TEST_HR(presults->ComputeMemberForces(lc, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,   0.0));
   TRY_TEST_B( IsEqual(sfy,-9999.99600));
   TRY_TEST_B( IsEqual(smz,   0.0));
   TRY_TEST_B( IsEqual(efx,   0.0));
   TRY_TEST_B( IsEqual(efy, 9999.99600));
   TRY_TEST_B( IsEqual(emz,-999999.60000));

   // reactions
   TRY_TEST_HR(presults->ComputeReactions(lc, 1, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   0.0));
   TRY_TEST_B( IsEqual(fy,  -9999.99600));
   TRY_TEST_B( IsEqual(mz,   0.0));
   TRY_TEST_HR(presults->ComputeReactions(lc, 2, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   0.0));
   TRY_TEST_B( IsEqual(fy,   9999.99600));
   TRY_TEST_B( IsEqual(mz,  -999999.6000));

   // poi results
   TRY_TEST_HR(presults->ComputePOIDeflections(lc, 1000, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz,-200.0) );
   TRY_TEST_HR(presults->ComputePOIDeflections(lc, 1100, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy,-2812.5) );
   TRY_TEST_B( IsEqual(rz,-37.50) );

   TRY_TEST_HR(presults->ComputePOIDeflections(lc, 3000, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy,-2500.0) );
   TRY_TEST_B( IsEqual(rz,  50.0) );
   TRY_TEST_HR(presults->ComputePOIDeflections(lc, 3100, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy,-937.5000) );
   TRY_TEST_B( IsEqual(rz,  62.50) );

   TRY_TEST_HR(presults->ComputePOIForces(lc, 1000, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  9999.99600));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(lc, 1100, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  9999.99600));
   TRY_TEST_B( IsEqual(mz, -249999.90000));
   TRY_TEST_HR(presults->ComputePOIForces(lc, 1100, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -9999.99600));
   TRY_TEST_B( IsEqual(mz,  249999.90000));
   TRY_TEST_HR(presults->ComputePOIForces(lc, 1075, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  9999.99600));
   TRY_TEST_B( IsEqual(mz, -187499.925));
   TRY_TEST_HR(presults->ComputePOIForces(lc, 1075, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -9999.99600));
   TRY_TEST_B( IsEqual(mz,  187499.925));
   TRY_TEST_HR(presults->ComputePOIForces(lc, 3000, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  9999.99600));
   TRY_TEST_B( IsEqual(mz, -499999.8));
   TRY_TEST_HR(presults->ComputePOIForces(lc, 3000, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -9999.99600));
   TRY_TEST_B( IsEqual(mz,  499999.8));
   TRY_TEST_HR(presults->ComputePOIForces(lc, 3050, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -9999.99600));
   TRY_TEST_B( IsEqual(mz,  624999.75000));
   TRY_TEST_HR(presults->ComputePOIForces(lc, 3075, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -9999.99600));
   TRY_TEST_B( IsEqual(mz,  687499.72500));


   ReleaseModel(pmodel);
}


void CTestMemberStrains2::TestFrame()
{
/*
//////////////////////////////////////////////

  Problem taken from "Matrix Analysis of Structures"
                      Robert F. Sennett, 1994
                      Chapter 3, Example 3.5

  Half portal frame with temperature strain loads

////////////////////////////////////////////////
*/
   CComPtr<IFem2dModel> pmodel;
   pmodel = CreateModel();
   ATLASSERT(pmodel);

   // create joints
   CComPtr<IFem2dJointCollection> pJoints;
   TRY_TEST_HR(pmodel->get_Joints(&pJoints));

   CComPtr<IFem2dJoint> pJoint1,pJoint2, pJoint3;
   TRY_TEST_MC(pJoints->Create(1,  0.0,       0.0,       &pJoint1));
   TRY_TEST_MC(pJoints->Create(2,  0.0,      12.0*12.0,  &pJoint2));
   TRY_TEST_MC(pJoints->Create(3,  7.0*12.0, 12.0*12.0,  &pJoint3));

   // boundary conditions
   TRY_TEST_MC(pJoint1->Support());
   TRY_TEST_MC(pJoint3->Support());

   // create members
   CComPtr<IFem2dMemberCollection> pMembers;
   TRY_TEST_HR(pmodel->get_Members(&pMembers));

   Float64 E = 30.0e06;
   Float64 A = 20.0;
   Float64 I = 100.0;
   Float64 EA = E*A;
   Float64 EI = E*I;
   CComPtr<IFem2dMember> pMember1,pMember2;
   TRY_TEST_MC(pMembers->Create(1,  1,  2, EA, EI, &pMember1));
   TRY_TEST_MC(pMembers->Create(2,  2,  3, EA, EI, &pMember2));


   // create load case and apply both axial and curvature strains to member 2
   // net temperature rise of 35 deg
   // differential temperature of 70 deg (hotter on top)
   // section depth = 10
   Float64  saxial =  6.5e-06*35.0;
   Float64  scurv  = -6.5e-06*70.0/10.0;
   CComPtr<IFem2dLoadingCollection> pLoadings;
   TRY_TEST_HR(pmodel->get_Loadings(&pLoadings));
   CComPtr<IFem2dLoading> pLoading;
   TRY_TEST_LC(pLoadings->Create(0, &pLoading));
   CComPtr<IFem2dMemberStrainCollection> pMemberStrains;
   TRY_TEST_HR(pLoading->get_MemberStrains(&pMemberStrains));
   CComPtr<IFem2dMemberStrain> pMemberStrain2;
   TRY_TEST_LC(pMemberStrains->Create(1, 2, 0.0, -1.0, saxial, scurv, &pMemberStrain2));

   // get results interface
   CComQIPtr<IFem2dModelResults> presults(pmodel);

   // get joint Deflections
   Float64 dx, dy, rz;
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 1, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );     
   TRY_TEST_B( IsEqual(dy, 0.0) );     
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 2, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, -0.019160498123460) );
   TRY_TEST_B( IsEqual(dy, -0.00041133776877044) );
   TRY_TEST_B( IsEqual(rz,  0.00068164544539101) );
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 3, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 0.0));

   // get member end forces
   Float64 sfx, sfy, smz, efx, efy, emz;
   TRY_TEST_HR(presults->ComputeMemberForces(0, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,    1713.90736));
   TRY_TEST_B( IsEqual(sfy,     360.70088));
   TRY_TEST_B( IsEqual(smz,   11769.51671));
   TRY_TEST_B( IsEqual(efx,   -1713.90736));
   TRY_TEST_B( IsEqual(efy,    -360.70088));
   TRY_TEST_B( IsEqual(emz,   40171.41027));
   TRY_TEST_HR(presults->ComputeMemberForces(0, 2, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,    -360.70088));
   TRY_TEST_B( IsEqual(sfy,    1713.90736));
   TRY_TEST_B( IsEqual(smz,  -40171.41027));
   TRY_TEST_B( IsEqual(efx,     360.70088));
   TRY_TEST_B( IsEqual(efy,   -1713.90736));
   TRY_TEST_B( IsEqual(emz,  184139.62934));

   // reactions
   Float64 fx, fy, mz;
   TRY_TEST_HR(presults->ComputeReactions(0, 1, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,     -360.700881));
   TRY_TEST_B( IsEqual(fy,     1713.907369));
   TRY_TEST_B( IsEqual(mz,    11769.516714));
   TRY_TEST_HR(presults->ComputeReactions(0, 2, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   0.0));
   TRY_TEST_B( IsEqual(fy,   0.0));
   TRY_TEST_B( IsEqual(mz,   0.0));
   TRY_TEST_HR(presults->ComputeReactions(0, 3, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,      360.7008818));
   TRY_TEST_B( IsEqual(fy,    -1713.9073698));
   TRY_TEST_B( IsEqual(mz,   184139.6293422));

   ReleaseModel(pmodel);
}







