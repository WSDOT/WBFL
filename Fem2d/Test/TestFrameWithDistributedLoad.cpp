///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2023  Washington State Department of Transportation
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
// TestFrameWithDistributedLoad.cpp: implementation of the CTestFrameWithDistributedLoad class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestFrameWithDistributedLoad.h"
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



CTestFrameWithDistributedLoad::CTestFrameWithDistributedLoad()
{

}

CTestFrameWithDistributedLoad::~CTestFrameWithDistributedLoad()
{

}

void CTestFrameWithDistributedLoad::Test() 
{

/*////////////////////////////////////////////////////
               w
          ============ 3
                     /o
                   /  |
                 /    |
               /      |
             /        |
           /          |
         2o-----------o4
          |           |
          |           |
          |           |  
          |           |
         1o           o5
         ===         ===

  frame with trapezoidal load
  made up and verified using DrFrame

*/////////////////////////////////////////////////
   CComPtr<IFem2dModel> pmodel;
   pmodel = CreateModel();
   ATLASSERT(pmodel);

   // create joints
   CComPtr<IFem2dJointCollection> pJoints;
   TRY_TEST_HR(pmodel->get_Joints(&pJoints));

   CComPtr<IFem2dJoint> pJoint1,pJoint2,pJoint3,pJoint4,pJoint5;
   TRY_TEST_MC(pJoints->Create(1,  0.0,   0.0, &pJoint1));
   TRY_TEST_MC(pJoints->Create(2,  0.0, 144.0, &pJoint2));
   TRY_TEST_MC(pJoints->Create(3,144.0, 288.0, &pJoint3));
   TRY_TEST_MC(pJoints->Create(4,144.0, 144.0, &pJoint4));
   TRY_TEST_MC(pJoints->Create(5,144.0,   0.0, &pJoint5));

   // boundary conditions
   TRY_TEST_MC(pJoint1->Support());
   TRY_TEST_MC(pJoint5->Support());
   TRY_TEST_MC(pJoint1->ReleaseDof(jrtMz));
   TRY_TEST_MC(pJoint5->ReleaseDof(jrtMz));

   // create members
   CComPtr<IFem2dMemberCollection> pMembers;
   TRY_TEST_HR(pmodel->get_Members(&pMembers));

   Float64 E=29000;
   Float64 A=10;
   Float64 I=250;
   CComPtr<IFem2dMember> pMember1, pMember2, pMember3, pMember4, pMember5;
   TRY_TEST_MC(pMembers->Create(1,  1,  2, E*A, E*I, &pMember1));
   TRY_TEST_MC(pMembers->Create(2,  2,  3, E*A, E*I, &pMember2));
   TRY_TEST_MC(pMembers->Create(3,  3,  4, E*A, E*I, &pMember3));
   TRY_TEST_MC(pMembers->Create(4,  2,  4, E*A, E*I, &pMember4));
   TRY_TEST_MC(pMembers->Create(5,  4,  5, E*A, E*I, &pMember5));

   // create load case and apply Distributed load to members
   CComPtr<IFem2dLoadingCollection> pLoadings;
   TRY_TEST_HR(pmodel->get_Loadings(&pLoadings));
   CComPtr<IFem2dLoading> pLoading0;
   TRY_TEST_LC(pLoadings->Create(0, &pLoading0));
   CComPtr<IFem2dDistributedLoadCollection> pDistributedLoads;
   TRY_TEST_HR(pLoading0->get_DistributedLoads(&pDistributedLoads));
   CComPtr<IFem2dDistributedLoad> pDistributedLoad;
   TRY_TEST_LC(pDistributedLoads->Create(1, 2, loadDirFy, 0.0, -1.0, -0.5, -1.0, lotMember, &pDistributedLoad));
   TRY_TEST_LC(pDistributedLoad->put_Orientation(lotGlobal)); // apply in global coords

   // now let's add some POI's 
   CComPtr<IFem2dPOICollection> pPOIs;
   TRY_TEST_HR(pmodel->get_POIs(&pPOIs));

   CComPtr<IFem2dPOI> pPOI22;
   TRY_TEST_HR(pPOIs->Create(22,  2,  -0.5,  &pPOI22));

   // get results interfaces
   CComQIPtr<IFem2dModelResults> presults(pmodel);

   // get joint Deflections
   Float64 dx, dy, rz;
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 1, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 2, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  0.47518504376467) );
   TRY_TEST_B( IsEqual(dy, -0.033707048769389) );
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 3, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  0.50069452024221) );
   TRY_TEST_B( IsEqual(dy, -0.077478110675579) );
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 4, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.48025051552884) );
   TRY_TEST_B( IsEqual(dy, -0.042133810961736) );

   // get member end forces
   Float64 sfx, sfy, smz, efx, efy, emz;
   TRY_TEST_HR(presults->ComputeMemberForces(0, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx, 67.882250993909) );
   TRY_TEST_B( IsEqual(sfy, -2.1305089245136));
   TRY_TEST_B( IsEqual(smz, 0.0));
   TRY_TEST_B( IsEqual(efx, -67.882250993909));
   TRY_TEST_B( IsEqual(efy, 2.1305089245136));
   TRY_TEST_B( IsEqual(emz, -306.79328512995));
   TRY_TEST_HR(presults->ComputeMemberForces(0, 2, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,    66.388401994131) );
   TRY_TEST_B( IsEqual(sfy,    48.948594378857));
   TRY_TEST_B( IsEqual(smz,  1494.0302142683));
   TRY_TEST_B( IsEqual(efx,    41.611598005869));
   TRY_TEST_B( IsEqual(efy,    59.051405621143));
   TRY_TEST_B( IsEqual(emz, -1300.8520491173));
   TRY_TEST_HR(presults->ComputeMemberForces(0, 3, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,   71.179492479266) );
   TRY_TEST_B( IsEqual(sfy,   12.331806227349));
   TRY_TEST_B( IsEqual(smz, 1300.8520491173));
   TRY_TEST_B( IsEqual(efx,  -71.179492479266));
   TRY_TEST_B( IsEqual(efy,  -12.331806227349));
   TRY_TEST_B( IsEqual(emz,  474.92804762087));

   Float64 fx, fy, mz;
   TRY_TEST_HR(presults->ComputeReactions(0, 1, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   2.1305089245136));
   TRY_TEST_B( IsEqual(fy,  67.882250993909));
   TRY_TEST_B( IsEqual(mz,   0.0));
   TRY_TEST_HR(presults->ComputeReactions(0, 5, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  -2.1305089245135));
   TRY_TEST_B( IsEqual(fy,  84.852813742386));
   TRY_TEST_B( IsEqual(mz,   0.0));

   // look at  poi Deflections
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 22, lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  0.29623553109350) ); // close, but  not exact to drframe
   TRY_TEST_B( IsEqual(dy, -1.0232793921774));
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 22, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  0.93303795012174) );
   TRY_TEST_B( IsEqual(dy, -0.51409764439251));

   // next look at poi forces
   TRY_TEST_HR(presults->ComputePOIForces(0, 22, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx, -21.388401994131));
   TRY_TEST_B( IsEqual(fy,-3.9485943788572));
   TRY_TEST_B( IsEqual(mz,  1351.7900335605));

   // add a new loading with a horizontally applied load
   CComPtr<IFem2dLoading> pLoading1;
   TRY_TEST_HR(pLoadings->Create(1, &pLoading1));
   CComPtr<IFem2dDistributedLoadCollection> pDistributedLoads1;
   TRY_TEST_HR(pLoading1->get_DistributedLoads(&pDistributedLoads1));
   CComPtr<IFem2dDistributedLoad> pDistributedLoad1;
   TRY_TEST_LC(pDistributedLoads1->Create(1, 2, loadDirFx, 0.0, -1.0, -0.5, -1.0, lotMember, &pDistributedLoad1));
   TRY_TEST_LC(pDistributedLoad1->put_Orientation(lotGlobal)); // apply in global coords

   // don't compute all values as above
   TRY_TEST_HR(presults->ComputeReactions(1, 1, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   73.282046829267));
   TRY_TEST_B( IsEqual(fy,  237.58787847868));
   TRY_TEST_B( IsEqual(mz,   0.0));
   TRY_TEST_HR(presults->ComputeReactions(1, 5, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  79.453017907024));
   TRY_TEST_B( IsEqual(fy,  -237.58787847868));
   TRY_TEST_B( IsEqual(mz,   0.0));

   // member forces
   TRY_TEST_HR(presults->ComputeMemberForces(1, 2, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,    196.34212817867) );
   TRY_TEST_B( IsEqual(sfy,    -33.642294746207));
   TRY_TEST_B( IsEqual(smz, 1417.8934017460));
   TRY_TEST_B( IsEqual(efx,    -88.342128178674));
   TRY_TEST_B( IsEqual(efy,    -74.357705253793));
   TRY_TEST_B( IsEqual(emz, 1506.0066534574));

   // next look at poi forces
   TRY_TEST_HR(presults->ComputePOIForces(1, 22, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx, -151.34212817867));
   TRY_TEST_B( IsEqual(fy,-11.357705253793));
   TRY_TEST_B( IsEqual(mz,-2705.1745393975));

   // next try global projected load in Y
   CComPtr<IFem2dLoading> pLoading2;
   TRY_TEST_LC(pLoadings->Create(2, &pLoading2));
   CComPtr<IFem2dDistributedLoadCollection> pDistributedLoads2;
   TRY_TEST_HR(pLoading2->get_DistributedLoads(&pDistributedLoads2));
   CComPtr<IFem2dDistributedLoad> pDistributedLoad2;
   TRY_TEST_LC(pDistributedLoads2->Create(1, 2, loadDirFy, 0.0, -1.0, -0.5, -1.0, lotMember, &pDistributedLoad2));
   TRY_TEST_LC(pDistributedLoad2->put_Orientation(lotGlobalProjected)); // apply in global coords

   TRY_TEST_HR(presults->ComputeReactions(2, 1, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   1.5064973079020));
   TRY_TEST_B( IsEqual(fy,  48.000000000000));
   TRY_TEST_B( IsEqual(mz,   0.0));
   TRY_TEST_HR(presults->ComputeReactions(2, 5, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  -1.5064973079019));
   TRY_TEST_B( IsEqual(fy,   60.000000000000));
   TRY_TEST_B( IsEqual(mz,   0.0));

   // member forces
   TRY_TEST_HR(presults->ComputeMemberForces(2, 2, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,    46.943689242188) );
   TRY_TEST_B( IsEqual(sfy,    34.611883014840));
   TRY_TEST_B( IsEqual(smz, 1056.4388958067));
   TRY_TEST_B( IsEqual(efx,    29.423843125959));
   TRY_TEST_B( IsEqual(efy,    41.755649353307));
   TRY_TEST_B( IsEqual(emz, -919.84130525128));

   // next look at poi forces
   TRY_TEST_HR(presults->ComputePOIForces(2, 22, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx, -15.123884088794));
   TRY_TEST_B( IsEqual(fy,-2.7920778614451));
   TRY_TEST_B( IsEqual(mz,  955.85989947101));

   // next try global projected load in X
   CComPtr<IFem2dLoading> pLoading3;
   TRY_TEST_LC(pLoadings->Create(3, &pLoading3));
   CComPtr<IFem2dDistributedLoadCollection> pDistributedLoads3;
   TRY_TEST_HR(pLoading3->get_DistributedLoads(&pDistributedLoads3));
   CComPtr<IFem2dDistributedLoad> pDistributedLoad3;
   TRY_TEST_LC(pDistributedLoads3->Create(1, 2, loadDirFx, 0.0, -1.0, -0.5, -1.0, lotMember, &pDistributedLoad3));
   TRY_TEST_LC(pDistributedLoad3->put_Orientation(lotGlobalProjected)); // apply in global coords

   TRY_TEST_HR(presults->ComputeReactions(3, 1, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   51.818232252205));
   TRY_TEST_B( IsEqual(fy,  168.00000000000));
   TRY_TEST_B( IsEqual(mz,   0.0));
   TRY_TEST_HR(presults->ComputeReactions(3, 5, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   56.181767747793));
   TRY_TEST_B( IsEqual(fy, -168.00000000000));
   TRY_TEST_B( IsEqual(mz,   0.0));

   // member forces
   TRY_TEST_HR(presults->ComputeMemberForces(3, 2, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,   138.83485026774) );
   TRY_TEST_B( IsEqual(sfy,    -23.788694749719));
   TRY_TEST_B( IsEqual(smz, 1002.6020393742));
   TRY_TEST_B( IsEqual(efx,   -62.467317899593));
   TRY_TEST_B( IsEqual(efy,   -52.578837618428));
   TRY_TEST_B( IsEqual(emz, 1064.9075171718));

   // next look at poi forces
   TRY_TEST_HR(presults->ComputePOIForces(3, 22, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx, -107.01504511435));
   TRY_TEST_B( IsEqual(fy,-8.0311104036752));
   TRY_TEST_B( IsEqual(mz,-1912.8472611011));

   ReleaseModel(pmodel);
}