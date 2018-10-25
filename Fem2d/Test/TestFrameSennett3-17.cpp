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
// TestFrameSennett3_17.cpp: implementation of the CTestFrameSennett3_17 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestFrameSennett3-17.h"
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


CTestFrameSennett3_17::CTestFrameSennett3_17()
{

}

CTestFrameSennett3_17::~CTestFrameSennett3_17()
{

}

void CTestFrameSennett3_17::Test()
{
// create a model
/*////////////////////////////////////////////////////

  Problem taken from "Matrix Analysis of Structures"
                      Robert F. Sennett, 1994
                      Chapter 3, Problem 17

   Bent frame with right leg shorter than left. 

*/////////////////////////////////////////////////
   CComPtr<IFem2dModel> pmodel;
   pmodel = CreateModel();
   ATLASSERT(pmodel);

   // create joints
   CComPtr<IFem2dJointCollection> pJoints;
   TRY_TEST_HR(pmodel->get_Joints(&pJoints));

   CComPtr<IFem2dJoint> pJoint1,pJoint2,pJoint3,pJoint4;
   TRY_TEST_MC(pJoints->Create(1,  0.0,       0.0,      &pJoint1));
   TRY_TEST_MC(pJoints->Create(2,  0.0,      20.0*12.0, &pJoint2));
   TRY_TEST_MC(pJoints->Create(3, 20.0*12.0, 20.0*12.0, &pJoint3));
   TRY_TEST_MC(pJoints->Create(4, 20.0*12.0, 10.0*12.0, &pJoint4));

   // boundary conditions
   TRY_TEST_MC(pJoint1->Support());
   TRY_TEST_MC(pJoint1->ReleaseDof(jrtMz));
   TRY_TEST_MC(pJoint4->Support());
   TRY_TEST_MC(pJoint4->ReleaseDof(jrtMz));

   // create members
   CComPtr<IFem2dMemberCollection> pMembers;
   TRY_TEST_HR(pmodel->get_Members(&pMembers));

   Float64 E = 29.0e06;;
   Float64 EA1 = E *  20.0;
   Float64 EI1 = E * 200.0;
   Float64 EA2 = E *  30.0;
   Float64 EI2 = E * 300.0;
   Float64 EA3 = E *  10.0;
   Float64 EI3 = E * 100.0;
   CComPtr<IFem2dMember> pMember1,pMember2,pMember3;
   TRY_TEST_MC(pMembers->Create(1,  1,  2, EA1, EI1, &pMember1));
   TRY_TEST_MC(pMembers->Create(2,  2,  3, EA2, EI2, &pMember2));
   TRY_TEST_MC(pMembers->Create(3,  3,  4, EA3, EI3, &pMember3));

   // create load case and apply point load to joint
   CComPtr<IFem2dLoadingCollection> pLoadings;
   TRY_TEST_HR(pmodel->get_Loadings(&pLoadings));
   CComPtr<IFem2dLoading> pLoading;
   TRY_TEST_LC(pLoadings->Create(0, &pLoading));
   CComPtr<IFem2dJointLoadCollection> pJointLoads;
   TRY_TEST_HR(pLoading->get_JointLoads(&pJointLoads));

   CComPtr<IFem2dJointLoad> pJointLoad;
   TRY_TEST_LC(pJointLoads->Create(0, 2, 20000.0, 0.0, 0.0, &pJointLoad));


   // get results interface
   CComQIPtr<IFem2dModelResults> presults(pmodel);

   // get joint displacements
   Float64 dx, dy, rz;
   TRY_TEST_HR(presults->ComputeJointDisplacements(0, 1, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );         // u1
   TRY_TEST_B( IsEqual(dy, 0.0) );         // u2
   TRY_TEST_B( IsEqual(rz, -.026293438));  // u3
   TRY_TEST_HR(presults->ComputeJointDisplacements(0, 2, &dx, &dy, &rz));
// TRY_TEST_B( IsEqual(dx,         ) );     // u4
   TRY_TEST_B( IsEqual(dy, 0.005136639 ) ); // u5
// TRY_TEST_B( IsEqual(rz,    ));           // u6
   TRY_TEST_HR(presults->ComputeJointDisplacements(0, 3, &dx, &dy, &rz));
// TRY_TEST_B( IsEqual(dx,         ) );     // u7
   TRY_TEST_B( IsEqual(dy, -.005136639));   // u8
// TRY_TEST_B( IsEqual(rz,    ));           // u9
   TRY_TEST_HR(presults->ComputeJointDisplacements(0, 4, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0      ) );    // u10
   TRY_TEST_B( IsEqual(dy, 0.0      ) );    // u11
   TRY_TEST_B( IsEqual(rz, -0.0491296) );   // u12

   // get member end forces
   Float64 sfx, sfy, smz, efx, efy, emz;
   TRY_TEST_HR(presults->ComputeMemberForces(0, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx, -12413.545,0.001));
// TRY_TEST_B( IsEqual(sfy,        ));
// TRY_TEST_B( IsEqual(smz,        ));
// TRY_TEST_B( IsEqual(efx,        ));
   TRY_TEST_B( IsEqual(efy, -4827.09,0.001));
   TRY_TEST_B( IsEqual(emz, 1158501.813,0.001));
   TRY_TEST_HR(presults->ComputeMemberForces(0, 2, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,  15172.909,0.001));
// TRY_TEST_B( IsEqual(sfy,        ));
   TRY_TEST_B( IsEqual(smz, -1158501.813,0.001));
// TRY_TEST_B( IsEqual(efx,        ));
// TRY_TEST_B( IsEqual(efy,        ));
   TRY_TEST_B( IsEqual(emz, -1820749.093,0.001));
   TRY_TEST_HR(presults->ComputeMemberForces(0, 3, &sfx, &sfy, &smz, &efx, &efy, &emz));
// TRY_TEST_B( IsEqual(sfx,        ) );
// TRY_TEST_B( IsEqual(sfy,        ));
   TRY_TEST_B( IsEqual(smz,  1820749.093,0.001));
// TRY_TEST_B( IsEqual(efx,        ));
   TRY_TEST_B( IsEqual(efy,  -15172.909,0.001));
// TRY_TEST_B( IsEqual(emz,      ));


   Float64 fx, fy, mz;
   TRY_TEST_HR(presults->ComputeReactions(0, 1, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  -4827.090,0.001));
   TRY_TEST_B( IsEqual(fy, -12413.545,0.001));
   TRY_TEST_B( IsEqual(mz,      0.0,0.001));
   TRY_TEST_HR(presults->ComputeReactions(0, 4, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  -15172.909,0.001));
   TRY_TEST_B( IsEqual(fy,   12413.545,0.001));
   TRY_TEST_B( IsEqual(mz,       0.0,0.001));

   TRY_TEST_HR(pmodel->Clear());
   ReleaseModel(pmodel);
}



