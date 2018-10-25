///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2015  Washington State Department of Transportation
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
// TestTrussSennett2_11.cpp: implementation of the CTestTrussSennett2_11 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestTrussSennett2-11.h"
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


CTestTrussSennett2_11::CTestTrussSennett2_11()
{

}

CTestTrussSennett2_11::~CTestTrussSennett2_11()
{ 

}

void CTestTrussSennett2_11::Test()
{
// create a model
/*////////////////////////////////////////////////////

  Problem taken from "Matrix Analysis of Structures"
                      Robert F. Sennett, 1994
                      Chapter 2, Problem 11

   Strange looking, symmetrical triangular truss with non-symmetric load

*/////////////////////////////////////////////////
   CComPtr<IFem2dModel> pmodel;
   pmodel = CreateModel();
   ATLASSERT(pmodel);

   // create joints
   CComPtr<IFem2dJointCollection> pJoints;
   TRY_TEST_HR(pmodel->get_Joints(&pJoints));

   CComPtr<IFem2dJoint> pJoint1,pJoint2,pJoint3,pJoint4;
   TRY_TEST_MC(pJoints->Create(1,  0.0,       0.0,      &pJoint1));
   TRY_TEST_MC(pJoints->Create(2, 20.0*12.0, 40.0*12.0, &pJoint2));
   TRY_TEST_MC(pJoints->Create(3, 40.0*12.0,  0.0,      &pJoint3));
   TRY_TEST_MC(pJoints->Create(4, 20.0*12.0, 15.0*12.0, &pJoint4));

   // boundary conditions
   TRY_TEST_MC(pJoint1->Support());
   TRY_TEST_MC(pJoint2->Support());
   TRY_TEST_MC(pJoint2->ReleaseDof(jrtFx));
   TRY_TEST_MC(pJoint2->ReleaseDof(jrtFy));
   TRY_TEST_MC(pJoint3->Support());
   TRY_TEST_MC(pJoint3->ReleaseDof(jrtFx));
   TRY_TEST_MC(pJoint4->Support());
   TRY_TEST_MC(pJoint4->ReleaseDof(jrtFx));
   TRY_TEST_MC(pJoint4->ReleaseDof(jrtFy));

   // create members
   CComPtr<IFem2dMemberCollection> pMembers;
   TRY_TEST_HR(pmodel->get_Members(&pMembers));

   Float64 E = 29.0e06;;
   Float64 EA135 = E * 4.0;
   Float64 EA246 = E * 2.0;
   Float64 EI = 1.0e29; // dummy since all members are pinned
   CComPtr<IFem2dMember> pMember1,pMember2,pMember3,pMember4,pMember5,pMember6;
   TRY_TEST_MC(pMembers->Create(1,  1,  2, EA135, EI, &pMember1));
   TRY_TEST_MC(pMembers->Create(2,  1,  4, EA246, EI, &pMember2));
   TRY_TEST_MC(pMembers->Create(3,  1,  3, EA135, EI, &pMember3));
   TRY_TEST_MC(pMembers->Create(4,  2,  4, EA246, EI, &pMember4));
   TRY_TEST_MC(pMembers->Create(5,  2,  3, EA135, EI, &pMember5));
   TRY_TEST_MC(pMembers->Create(6,  4,  3, EA246, EI, &pMember6));

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
   TRY_TEST_MC(pMember6->ReleaseEnd(metStart, mbrReleaseMz));
   TRY_TEST_MC(pMember6->ReleaseEnd(metEnd,   mbrReleaseMz));

   // create load case and apply point load to joint
   CComPtr<IFem2dLoadingCollection> pLoadings;
   TRY_TEST_HR(pmodel->get_Loadings(&pLoadings));
   CComPtr<IFem2dLoading> pLoading;
   TRY_TEST_LC(pLoadings->Create(0, &pLoading));
   CComPtr<IFem2dJointLoadCollection> pJointLoads;
   TRY_TEST_HR(pLoading->get_JointLoads(&pJointLoads));

   CComPtr<IFem2dJointLoad> pJointLoad;
   TRY_TEST_LC(pJointLoads->Create(0, 2, -50000.0, -25000.0, 0.0, &pJointLoad));

   // get results interface
   CComQIPtr<IFem2dModelResults> presults(pmodel);

   // get joint Deflections
   Float64 dx, dy, rz;
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 1, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );    // u1
   TRY_TEST_B( IsEqual(dy, 0.0) );    // u2
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 2, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,-0.611438) ); // u3
   TRY_TEST_B( IsEqual(dy,-0.0367688) ); // u4
   TRY_TEST_B( IsEqual(rz, 0.0));
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 3, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,-.0662892) );  // u5
   TRY_TEST_B( IsEqual(dy, 0.0) );    // u6
   TRY_TEST_B( IsEqual(rz, 0.0));
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 4, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,-0.0331446) ); // u7
   TRY_TEST_B( IsEqual(dy,-0.0028779) ); // u8
   TRY_TEST_B( IsEqual(rz, 0.0));

   // get member end forces
   Float64 sfx, sfy, smz, efx, efy, emz;
   TRY_TEST_HR(presults->ComputeMemberForces(0, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx, 66214.3,0.1));
   TRY_TEST_B( IsEqual(sfy,     0.0,0.1));
   TRY_TEST_B( IsEqual(smz,     0.0,0.1));
   TRY_TEST_B( IsEqual(efx,-66214.3,0.1));
   TRY_TEST_B( IsEqual(efy,     0.0,0.1));
   TRY_TEST_B( IsEqual(emz,     0.0,0.1));
   TRY_TEST_HR(presults->ComputeMemberForces(0, 2, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,  5460.2,0.1));
   TRY_TEST_B( IsEqual(sfy,     0.0,0.1));
   TRY_TEST_B( IsEqual(smz,     0.0,0.1));
   TRY_TEST_B( IsEqual(efx, -5460.2,0.1));
   TRY_TEST_B( IsEqual(efy,     0.0,0.1));
   TRY_TEST_B( IsEqual(emz,     0.0,0.1));
   TRY_TEST_HR(presults->ComputeMemberForces(0, 3, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx, 16019.9,0.1));
   TRY_TEST_B( IsEqual(sfy,     0.0,0.1));
   TRY_TEST_B( IsEqual(smz,     0.0,0.1));
   TRY_TEST_B( IsEqual(efx,-16019.9,0.1));
   TRY_TEST_B( IsEqual(efy,     0.0,0.1));
   TRY_TEST_B( IsEqual(emz,     0.0,0.1));
   TRY_TEST_HR(presults->ComputeMemberForces(0, 4, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,  6552.2,0.1));
   TRY_TEST_B( IsEqual(sfy,     0.0,0.1));
   TRY_TEST_B( IsEqual(smz,     0.0,0.1));
   TRY_TEST_B( IsEqual(efx, -6552.2,0.1));
   TRY_TEST_B( IsEqual(efy,     0.0,0.1));
   TRY_TEST_B( IsEqual(emz,     0.0,0.1));
   TRY_TEST_HR(presults->ComputeMemberForces(0, 5, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,-45589.0,0.1));
   TRY_TEST_B( IsEqual(sfy,     0.0,0.1));
   TRY_TEST_B( IsEqual(smz,     0.0,0.1));
   TRY_TEST_B( IsEqual(efx, 45589.0,0.1));
   TRY_TEST_B( IsEqual(efy,     0.0,0.1));
   TRY_TEST_B( IsEqual(emz,     0.0,0.1));
   TRY_TEST_HR(presults->ComputeMemberForces(0, 6, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,  5460.2,0.1));
   TRY_TEST_B( IsEqual(sfy,     0.0,0.1));
   TRY_TEST_B( IsEqual(smz,     0.0,0.1));
   TRY_TEST_B( IsEqual(efx, -5460.2,0.1));
   TRY_TEST_B( IsEqual(efy,     0.0,0.1));
   TRY_TEST_B( IsEqual(emz,     0.0,0.1));


   Float64 fx, fy, mz;
   TRY_TEST_HR(presults->ComputeReactions(0, 1, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  50000.0,0.1));
   TRY_TEST_B( IsEqual(fy,  62500.0,0.1));
   TRY_TEST_B( IsEqual(mz,  0.0,0.1));
   TRY_TEST_HR(presults->ComputeReactions(0, 3, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0,0.1));
   TRY_TEST_B( IsEqual(fy,  -37500.0,0.1));
   TRY_TEST_B( IsEqual(mz,  0.0,0.1));

   ReleaseModel(pmodel);
}



