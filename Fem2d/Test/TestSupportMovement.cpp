///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
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
// TestSupportMovement.cpp: implementation of the CTestSupportMovement class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestSupportMovement.h"
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


CTestSupportMovement::CTestSupportMovement()
{

}

CTestSupportMovement::~CTestSupportMovement()
{

}

void CTestSupportMovement::Test()
{
   TestBar();
   TestBeam();
   TestTruss();
}

void CTestSupportMovement::TestTruss()
{
// create a model
/*////////////////////////////////////////////////////

  Problem taken from "Matrix Analysis of Structures"
                      Robert F. Sennett, 1994
                      Chapter 2, Example 2.3

   simple truss with support settlement at two joints

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
   CComPtr<IFem2dJointLoadCollection> pJointLoads;
   TRY_TEST_HR(pLoading->get_JointLoads(&pJointLoads));

   CComPtr<IFem2dJointLoad> pJointLoad;
   TRY_TEST_LC(pJointLoads->Create(0, 2, 0.0, -30000.0, 0.0, &pJointLoad));

   // create another joint load to apply at a fixity to make sure reactions are added correctly
   CComPtr<IFem2dJointLoad> pJointLoad4;
   TRY_TEST_LC(pJointLoads->Create(4, 4, 0.0, -20000.0, 0.0, &pJointLoad4));


   // apply joint Deflections at joints 1 and 4
   CComPtr<IFem2dJointDeflectionCollection> pJointDeflections;
   TRY_TEST_HR(pLoading->get_JointDeflections(&pJointDeflections));
   CComPtr<IFem2dJointDeflection> pJointDeflection1;
   TRY_TEST_LC(pJointDeflections->Create(1, 1, 0.0, -0.60, 0.0, &pJointDeflection1));
   CComPtr<IFem2dJointDeflection> pJointDeflection4;
   TRY_TEST_LC(pJointDeflections->Create(4, 4, -0.3, 0.0, 0.0, &pJointDeflection4));

   // test get_Loading
   LoadCaseIDType ld;
   TRY_TEST_HR(pJointDeflection4->get_Loading(&ld));
   TRY_TEST(ld, 0);

   // apply Deflection to free dof
   CComPtr<IFem2dJointDeflection> pJointDeflection5;
   TRY_TEST_LC(pJointDeflections->Create(5, 2, -0.3, 0.0, 0.0, &pJointDeflection5));

   // get results interface
   CComQIPtr<IFem2dModelResults> presults(pmodel);

   Float64 dx, dy, rz;
   TRY_TEST(presults->ComputeJointDeflections(0, 1, &dx, &dy, &rz),FEM2D_E_JOINT_DISP_TO_FIXED_DOF_ONLY);
   LoadIDType id;
   TRY_TEST_LC(pJointDeflections->Remove(5, atID,&id));
   TRY_TEST(id, 5);

   // get joint Deflections
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 1, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );    // u1
   TRY_TEST_B( IsEqual(dy,-0.6) );    // u2
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 2, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,-0.33847916063898) ); // u3
   TRY_TEST_B( IsEqual(dy,-0.36436867720659) ); // u4
   TRY_TEST_B( IsEqual(rz, 0.0));
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 3, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,-0.32342783496097) );  // u5
   TRY_TEST_B( IsEqual(dy,-0.0092373090239415) );    // u6
   TRY_TEST_B( IsEqual(rz, 0.0));
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 4, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,-0.3) ); // u7
   TRY_TEST_B( IsEqual(dy,-0.0) ); // u8
   TRY_TEST_B( IsEqual(rz, 0.0));

   // get member end forces
   Float64 sfx, sfy, smz, efx, efy, emz;
   TRY_TEST_HR(presults->ComputeMemberForces(0, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx, 24854.89414));
   TRY_TEST_B( IsEqual(sfy,     0.0));
   TRY_TEST_B( IsEqual(smz,     0.0));
   TRY_TEST_B( IsEqual(efx,-24854.89414));
   TRY_TEST_B( IsEqual(efy,     0.0));
   TRY_TEST_B( IsEqual(emz,     0.0));
   TRY_TEST_HR(presults->ComputeMemberForces(0, 4, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,  5422.32129) );
   TRY_TEST_B( IsEqual(sfy,     0.0));
   TRY_TEST_B( IsEqual(smz,     0.0));
   TRY_TEST_B( IsEqual(efx, -5422.32129));
   TRY_TEST_B( IsEqual(efy,     0.0));
   TRY_TEST_B( IsEqual(emz,     0.0));

   Float64 fx, fy, mz;
   TRY_TEST_HR(presults->ComputeReactions(0, 1, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  22424.9358));
   TRY_TEST_B( IsEqual(fy,  20000.0000));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputeReactions(0, 4, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx, -22424.9358));
   TRY_TEST_B( IsEqual(fy,  30000.0000)); // has point load added in
   TRY_TEST_B( IsEqual(mz,  0.0));

   ReleaseModel(pmodel);
}

void CTestSupportMovement::TestBar()
{
// create a model
/*////////////////////////////////////////////////////

  Problem taken from "Matrix Analysis of Structures"
                      Robert F. Sennett, 1994
                      Chapter 1, Example 1.6

   Two-node bar with end support settlement

*/////////////////////////////////////////////////
   CComPtr<IFem2dModel> pmodel;
   pmodel = CreateModel();
   ATLASSERT(pmodel);

   // create joints
   CComPtr<IFem2dJointCollection> pJoints;
   TRY_TEST_HR(pmodel->get_Joints(&pJoints));

   CComPtr<IFem2dJoint> pJoint1,pJoint2,pJoint3;
   TRY_TEST_MC(pJoints->Create(1,  0.0,  0.0,      &pJoint1));
   TRY_TEST_MC(pJoints->Create(2,  1.0,  0.0,      &pJoint2));
   TRY_TEST_MC(pJoints->Create(3,  2.0,  0.0,      &pJoint3));

   // boundary conditions
   TRY_TEST_MC(pJoint1->Support());
   TRY_TEST_MC(pJoint3->Support());

   // create members
   CComPtr<IFem2dMemberCollection> pMembers;
   TRY_TEST_HR(pmodel->get_Members(&pMembers));

   Float64 EA1 = 5800.0;
   Float64 EA2 = 2900.0;
   Float64 EI = EA1; // whatever
   CComPtr<IFem2dMember> pMember1,pMember2;
   TRY_TEST_MC(pMembers->Create(1,  1,  2, EA1, EI, &pMember1));
   TRY_TEST_MC(pMembers->Create(2,  2,  3, EA2, EI, &pMember2));

   // create load case
   CComPtr<IFem2dLoadingCollection> pLoadings;
   TRY_TEST_HR(pmodel->get_Loadings(&pLoadings));
   CComPtr<IFem2dLoading> pLoading;
   TRY_TEST_LC(pLoadings->Create(0, &pLoading));

   // apply 25k load to joint 2
   CComPtr<IFem2dJointLoadCollection> pJointLoads;
   TRY_TEST_HR(pLoading->get_JointLoads(&pJointLoads));
   CComPtr<IFem2dJointLoad> pJointLoad;
   TRY_TEST_LC(pJointLoads->Create(0, 2, 25.0, 0.0, 0.0, &pJointLoad));

   // apply settlement load of -0.000862 to joint 3
   CComPtr<IFem2dJointDeflectionCollection> pJointDeflections;
   TRY_TEST_HR(pLoading->get_JointDeflections(&pJointDeflections));

   CComPtr<IFem2dJointDeflection> pJointDeflection;
   TRY_TEST_LC(pJointDeflections->Create(0, 3, -0.00086208, 0.0, 0.0, &pJointDeflection));

   // get results interface
   CComQIPtr<IFem2dModelResults> presults(pmodel);

   // get joint Deflections
   Float64 dx, dy, rz;
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 1, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) ); 
   TRY_TEST_B( IsEqual(dy, 0.0) ); 
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 2, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  0.0025862132183908) );
   TRY_TEST_B( IsEqual(dy,  0.0) );
   TRY_TEST_B( IsEqual(rz,  0.0));
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 3, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, -0.00086208) );
   TRY_TEST_B( IsEqual(dy,  0.0 ));
   TRY_TEST_B( IsEqual(rz,  0.0));

   // get member end forces
   Float64 sfx, sfy, smz, efx, efy, emz;
   TRY_TEST_HR(presults->ComputeMemberForces(0, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx, -15.0,0.1));
   TRY_TEST_B( IsEqual(sfy,   0.0,0.1));
   TRY_TEST_B( IsEqual(smz,   0.0,0.1));
   TRY_TEST_B( IsEqual(efx,  15.0,0.1));
   TRY_TEST_B( IsEqual(efy,   0.0,0.1));
   TRY_TEST_B( IsEqual(emz,   0.0,0.1));
   TRY_TEST_HR(presults->ComputeMemberForces(0, 2, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,  10.0,0.1));
   TRY_TEST_B( IsEqual(sfy,   0.0,0.1));
   TRY_TEST_B( IsEqual(smz,   0.0,0.1));
   TRY_TEST_B( IsEqual(efx, -10.0,0.1));
   TRY_TEST_B( IsEqual(efy,   0.0,0.1));
   TRY_TEST_B( IsEqual(emz,   0.0,0.1));

   Float64 fx, fy, mz;
   TRY_TEST_HR(presults->ComputeReactions(0, 1, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  -15.0,0.1));
   TRY_TEST_B( IsEqual(fy,    0.0,0.1));
   TRY_TEST_B( IsEqual(mz,    0.0,0.1));
   TRY_TEST_HR(presults->ComputeReactions(0, 2, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,    0.0,0.1));
   TRY_TEST_B( IsEqual(fy,    0.0,0.1));
   TRY_TEST_B( IsEqual(mz  ,  0.0,0.1));
   TRY_TEST_HR(presults->ComputeReactions(0, 3, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  -10.0,0.1));
   TRY_TEST_B( IsEqual(fy,    0.0,0.1));
   TRY_TEST_B( IsEqual(mz,    0.0,0.1));

   ReleaseModel(pmodel);
}


void CTestSupportMovement::TestBeam()
{
// create a model
/*////////////////////////////////////////////////////

  Problem taken from "Matrix Analysis of Structures"
                      Robert F. Sennett, 1994
                      Chapter 3, Example 3.6

   Two-span beam with mid-span support settlement

*/////////////////////////////////////////////////
   CComPtr<IFem2dModel> pmodel;
   pmodel = CreateModel();
   ATLASSERT(pmodel);

   // create joints
   CComPtr<IFem2dJointCollection> pJoints;
   TRY_TEST_HR(pmodel->get_Joints(&pJoints));

   CComPtr<IFem2dJoint> pJoint1,pJoint2,pJoint3;
   TRY_TEST_MC(pJoints->Create(1,  0.0,       0.0,      &pJoint1));
   TRY_TEST_MC(pJoints->Create(2, 10.0*12.0,  0.0,      &pJoint2));
   TRY_TEST_MC(pJoints->Create(3, 20.0*12.0,  0.0,      &pJoint3));

   // boundary conditions
   TRY_TEST_MC(pJoint1->Support());
   TRY_TEST_MC(pJoint2->Support());
   TRY_TEST_MC(pJoint2->ReleaseDof(jrtFx));
   TRY_TEST_MC(pJoint2->ReleaseDof(jrtMz));
   TRY_TEST_MC(pJoint3->Support());
   TRY_TEST_MC(pJoint3->ReleaseDof(jrtFx));
   TRY_TEST_MC(pJoint3->ReleaseDof(jrtMz));

   // create members
   CComPtr<IFem2dMemberCollection> pMembers;
   TRY_TEST_HR(pmodel->get_Members(&pMembers));

   Float64 EI = 2.90e06;;
   Float64 EA = EI; // whatever
   CComPtr<IFem2dMember> pMember1,pMember2;
   TRY_TEST_MC(pMembers->Create(1,  1,  2, EA, EI, &pMember1));
   TRY_TEST_MC(pMembers->Create(2,  2,  3, EA, EI, &pMember2));

   // create load case and apply support Deflection to joint 2
   CComPtr<IFem2dLoadingCollection> pLoadings;
   TRY_TEST_HR(pmodel->get_Loadings(&pLoadings));
   CComPtr<IFem2dLoading> pLoading;
   TRY_TEST_LC(pLoadings->Create(0, &pLoading));
   CComPtr<IFem2dJointDeflectionCollection> pJointDeflections;
   TRY_TEST_HR(pLoading->get_JointDeflections(&pJointDeflections));
   CComPtr<IFem2dJointDeflection> pJointDeflection;
   TRY_TEST_LC(pJointDeflections->Create(0, 2, 0.0, -0.25, 0.0, &pJointDeflection));

   // get results interface
   CComQIPtr<IFem2dModelResults> presults(pmodel);

   // get joint Deflections
   Float64 dx, dy, rz;
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 1, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );       // u1
   TRY_TEST_B( IsEqual(dy, 0.0) );       // u2
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 2, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  0.0) ); // u3
   TRY_TEST_B( IsEqual(dy,-0.25) ); // u4
   TRY_TEST_B( IsEqual(rz, -0.000892857));
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 3, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );  // u5
   TRY_TEST_B( IsEqual(dy, 0.0) );    // u6
   TRY_TEST_B( IsEqual(rz, 0.00357142));

   // get member end forces
   Float64 sfx, sfy, smz, efx, efy, emz;
   TRY_TEST_HR(presults->ComputeMemberForces(0, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,   0.0));
   TRY_TEST_B( IsEqual(sfy,   3.955853174));
   TRY_TEST_B( IsEqual(smz, 258.9285714));
   TRY_TEST_B( IsEqual(efx,   0.0));
   TRY_TEST_B( IsEqual(efy,  -3.9558531746));
   TRY_TEST_B( IsEqual(emz, 215.77380952));
   TRY_TEST_HR(presults->ComputeMemberForces(0, 2, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,     0.0));
   TRY_TEST_B( IsEqual(sfy,  -1.79811507936));
   TRY_TEST_B( IsEqual(smz,-215.77380952381));
   TRY_TEST_B( IsEqual(efx,   0.0));
   TRY_TEST_B( IsEqual(efy,   1.79811507936));
   TRY_TEST_B( IsEqual(emz,   0.0));

   Float64 fx, fy, mz;
   TRY_TEST_HR(presults->ComputeReactions(0, 1, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   0.0));
   TRY_TEST_B( IsEqual(fy,   3.95585317));
   TRY_TEST_B( IsEqual(mz, 258.92857142));
   TRY_TEST_HR(presults->ComputeReactions(0, 2, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -5.75396825));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputeReactions(0, 3, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  1.79811507936));
   TRY_TEST_B( IsEqual(mz,  0.0));

   //////////////////////////////////////////////////////////////
   // next let's try a joint rotation
   // first free up model and remove existing loads
   TRY_TEST_MC(pJoint2->Free());
   TRY_TEST_MC(pJoint3->Support());
   LoadIDType id;
   TRY_TEST_LC(pJointDeflections->Remove(0,atID,&id));
   TRY_TEST(id, 0);

   // add a rotation of 0.1 at joint 3
   CComPtr<IFem2dJointDeflection> pJointDeflection2;
   TRY_TEST_LC(pJointDeflections->Create(0, 3, 0.0, 0.0, 0.1, &pJointDeflection2));

   // get joint Deflections
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 1, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 2, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy,-3.0) );
   TRY_TEST_B( IsEqual(rz,-0.025));
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 3, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 0.1));

   // get member end forces
   TRY_TEST_HR(presults->ComputeMemberForces(0, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,    0.0));
   TRY_TEST_B( IsEqual(sfy,   30.208333));
   TRY_TEST_B( IsEqual(smz, 2416.666667));
   TRY_TEST_B( IsEqual(efx,    0.0));
   TRY_TEST_B( IsEqual(efy,  -30.208333 ));
   TRY_TEST_B( IsEqual(emz, 1208.33333));
   TRY_TEST_HR(presults->ComputeMemberForces(0, 2, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,    0.0));
   TRY_TEST_B( IsEqual(sfy,   30.208333));
   TRY_TEST_B( IsEqual(smz,-1208.33333));
   TRY_TEST_B( IsEqual(efx,    0.0));
   TRY_TEST_B( IsEqual(efy,  -30.208333));
   TRY_TEST_B( IsEqual(emz, 4833.333333));

   TRY_TEST_HR(presults->ComputeReactions(0, 1, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   0.0));
   TRY_TEST_B( IsEqual(fy,   30.208333));
   TRY_TEST_B( IsEqual(mz, 2416.666667));
   TRY_TEST_HR(presults->ComputeReactions(0, 2, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputeReactions(0, 3, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,    0.0));
   TRY_TEST_B( IsEqual(fy,  -30.208333));
   TRY_TEST_B( IsEqual(mz, 4833.333333));

   ReleaseModel(pmodel);
}




