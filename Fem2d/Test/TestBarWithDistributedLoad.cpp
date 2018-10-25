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
// TestBarWithDistributedLoad.cpp: implementation of the CTestBarWithDistributedLoad class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestBarWithDistributedLoad.h"
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


CTestBarWithDistributedLoad::CTestBarWithDistributedLoad()
{

}

CTestBarWithDistributedLoad::~CTestBarWithDistributedLoad()
{

}


void CTestBarWithDistributedLoad::Test() 
{

/*////////////////////////////////////////////////////
                          
                     ----------> 
                  ------------->
           ]    --------------->         
           ]=============================
           ]                             

       L = 8           
       EA = 3.0        
       EI = 7.0
       a = 2.5
       b = 5.0
       Wa = 2
       Wb = -4

*/////////////////////////////////////////////////
   CComPtr<IFem2dModel> pmodel;
   pmodel = CreateModel();
   ATLASSERT(pmodel);

   // create joints
   CComPtr<IFem2dJointCollection> pJoints;
   TRY_TEST_HR(pmodel->get_Joints(&pJoints));

   CComPtr<IFem2dJoint> pJoint0,pJoint8;
   TRY_TEST_MC(pJoints->Create(0,  0.0,  0.0, &pJoint0));
   TRY_TEST_MC(pJoints->Create(8,  8.0,  0.0, &pJoint8));

   // boundary conditions
   TRY_TEST_MC(pJoint0->Support());

   // create members
   CComPtr<IFem2dMemberCollection> pMembers;
   TRY_TEST_HR(pmodel->get_Members(&pMembers));

   CComPtr<IFem2dMember> pMember1;
   TRY_TEST_MC(pMembers->Create(1,  0,  8, 3.0, 7.0, &pMember1));

   // create load case and apply Distributed load to joint
   CComPtr<IFem2dLoadingCollection> pLoadings;
   TRY_TEST_HR(pmodel->get_Loadings(&pLoadings));
   CComPtr<IFem2dLoading> pLoading;
   TRY_TEST_LC(pLoadings->Create(0, &pLoading));
   CComPtr<IFem2dDistributedLoadCollection> pDistributedLoads;
   TRY_TEST_HR(pLoading->get_DistributedLoads(&pDistributedLoads));
   CComPtr<IFem2dDistributedLoad> pDistributedLoad;
   TRY_TEST_LC(pDistributedLoads->Create(0, 1, loadDirFx, 2.5, 5.0, 2.0, 4.0, lotMember, &pDistributedLoad));

   // now let's add some POI's at 1/4 points in member 1
   CComPtr<IFem2dPOICollection> pPOIs;
   TRY_TEST_HR(pmodel->get_POIs(&pPOIs));

   CComPtr<IFem2dPOI> pPOI10,pPOI15,pPOI12;
   TRY_TEST_HR(pPOIs->Create(10,  1,  0.0, &pPOI10));
   TRY_TEST_HR(pPOIs->Create(15,  1,  -.25, &pPOI15));
   TRY_TEST_HR(pPOIs->Create(12,  1,  -0.5, &pPOI12));


   // get results interface
   CComQIPtr<IFem2dModelResults> presults(pmodel);

   // get joint displacements
   Float64 dx, dy, rz;
   TRY_TEST_HR(presults->ComputeJointDisplacements(0, 0, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputeJointDisplacements(0, 8, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 9.7222222) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 0.0) );

   // get member end forces
   Float64 sfx, sfy, smz, efx, efy, emz;
   TRY_TEST_HR(presults->ComputeMemberForces(0, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx, -7.5) );
   TRY_TEST_B( IsEqual(sfy,  0.0));
   TRY_TEST_B( IsEqual(smz,  0.0));
   TRY_TEST_B( IsEqual(efx,  0.0));
   TRY_TEST_B( IsEqual(efy,  0.0));
   TRY_TEST_B( IsEqual(emz,  0.0));

   Float64 fx, fy, mz;
   TRY_TEST_HR(presults->ComputeReactions(0, 0, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  -7.5));
   TRY_TEST_B( IsEqual(fy,   0.0));
   TRY_TEST_B( IsEqual(mz,   0.0));
   TRY_TEST_HR(presults->ComputeReactions(0, 8, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));

   // get member end displacements
   Float64 sdx, sdy, srz, edx, edy, erz;
   TRY_TEST_HR(presults->ComputeMemberDisplacements(0, 1, &sdx, &sdy, &srz, &edx, &edy, &erz));
   TRY_TEST_B( IsEqual(sdx,   0.0) );
   TRY_TEST_B( IsEqual(sdy,   0.0));
   TRY_TEST_B( IsEqual(srz,   0.0));
   TRY_TEST_B( IsEqual(edx,   9.7222222));
   TRY_TEST_B( IsEqual(edy,   0.0));
   TRY_TEST_B( IsEqual(erz,   0.0));

   // now let's add some POI's at 1/4 points of on second half
   // these results are calculated on the fly
   CComPtr<IFem2dPOI> pPOI20,pPOI25,pPOI22;
   TRY_TEST_HR(pPOIs->Create(20,  1,  4.0, &pPOI20));
   TRY_TEST_HR(pPOIs->Create(25,  1,  6.0, &pPOI25));
   TRY_TEST_HR(pPOIs->Create(22,  1,  8.0, &pPOI22));

   // look at displacements
   TRY_TEST_HR(presults->ComputePOIDisplacements(0, 10,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDisplacements(0, 15,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 5.0) );
   TRY_TEST_B( IsEqual(dy, 0.0));
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDisplacements(0, 12,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 9.1) );
   TRY_TEST_B( IsEqual(dy, 0.0));
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDisplacements(0, 20,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 9.1) );
   TRY_TEST_B( IsEqual(dy, 0.0));
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDisplacements(0, 25,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 9.7222222) );
   TRY_TEST_B( IsEqual(dy, 0.0));
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDisplacements(0, 22,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 9.7222222) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 0.0));

   // next look at poi forces
   TRY_TEST_HR(presults->ComputePOIForces(0, 10, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  7.5));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 10, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx, -7.5));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));

   TRY_TEST_HR(presults->ComputePOIForces(0, 15, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  7.5));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 15, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx, -7.5));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));

   TRY_TEST_HR(presults->ComputePOIForces(0, 12, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  3.6));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 12, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx, -3.6));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));

   TRY_TEST_HR(presults->ComputePOIForces(0, 20, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  3.6));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 20, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx, -3.6));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));

   TRY_TEST_HR(presults->ComputePOIForces(0, 25, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 25, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));

   TRY_TEST_HR(presults->ComputePOIForces(0, 22, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 22, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));

///////////////////////////////////////////////
///===========================================
   // try a fix-fix orientation
   TRY_TEST_MC(pJoint8->Support());

   TRY_TEST_HR(presults->ComputeJointDisplacements(0, 0, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputeJointDisplacements(0, 8, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 0.0) );

   // get member end forces
   TRY_TEST_HR(presults->ComputeMemberForces(0, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx, -3.85416667) );
   TRY_TEST_B( IsEqual(sfy, 0.0));
   TRY_TEST_B( IsEqual(smz, 0.0));
   TRY_TEST_B( IsEqual(efx,-3.645833333));
   TRY_TEST_B( IsEqual(efy, 0.0));
   TRY_TEST_B( IsEqual(emz, 0.0));

   TRY_TEST_HR(presults->ComputeReactions(0, 0, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  -3.85416667));
   TRY_TEST_B( IsEqual(fy,   0.0));
   TRY_TEST_B( IsEqual(mz,   0.0));
   TRY_TEST_HR(presults->ComputeReactions(0, 8, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  -3.645833333));
   TRY_TEST_B( IsEqual(fy,   0.0));
   TRY_TEST_B( IsEqual(mz,   0.0));

   // get member end displacements
   TRY_TEST_HR(presults->ComputeMemberDisplacements(0, 1, &sdx, &sdy, &srz, &edx, &edy, &erz));
   TRY_TEST_B( IsEqual(sdx,   0.0) );
   TRY_TEST_B( IsEqual(sdy,   0.0));
   TRY_TEST_B( IsEqual(srz,   0.0));
   TRY_TEST_B( IsEqual(edx,   0.0));
   TRY_TEST_B( IsEqual(edy,   0.0));
   TRY_TEST_B( IsEqual(erz,   0.0));

   // look at displacements
   TRY_TEST_HR(presults->ComputePOIDisplacements(0, 10,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDisplacements(0, 15,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 2.56944444) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDisplacements(0, 12,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 4.238888889) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDisplacements(0, 20,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 4.238888889) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDisplacements(0, 25,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 2.430555556) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDisplacements(0, 22,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 0.0));

   // next look at poi forces
   TRY_TEST_HR(presults->ComputePOIForces(0, 10, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  3.85416667));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 10, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx, -3.85416667));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));

   TRY_TEST_HR(presults->ComputePOIForces(0, 15, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  3.85416667));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 15, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx, -3.85416667));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));

   TRY_TEST_HR(presults->ComputePOIForces(0, 12, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx, -0.04583333));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 12, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.04583333));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));

   TRY_TEST_HR(presults->ComputePOIForces(0, 20, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx, -0.04583333));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 20, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.04583333));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));

   TRY_TEST_HR(presults->ComputePOIForces(0, 25, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx, -3.6458333333333));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 25, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  3.6458333333333));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));

   TRY_TEST_HR(presults->ComputePOIForces(0, 22, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx, -3.6458333333333));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 22, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  3.6458333333333));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));

   ReleaseModel(pmodel);
}
