///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2017  Washington State Department of Transportation
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
// TestAxialLoads.cpp: implementation of the CTestAxialLoads class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestAxialLoads.h"
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


CTestAxialLoads::CTestAxialLoads()
{

}

CTestAxialLoads::~CTestAxialLoads()
{

}

void CTestAxialLoads::Test() 
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
         2o           |
          |           |
          |           |
          |           |  
          |           |
         1o           o4
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

   CComPtr<IFem2dJoint> pJoint1,pJoint2,pJoint3,pJoint4;
   TRY_TEST_MC(pJoints->Create(1,  0.0,   0.0, &pJoint1));
   TRY_TEST_MC(pJoints->Create(2,  0.0,  10.0, &pJoint2));
   TRY_TEST_MC(pJoints->Create(3, 10.0,  15.0, &pJoint3));
   TRY_TEST_MC(pJoints->Create(4, 10.0,   0.0, &pJoint4));

   // boundary conditions
   TRY_TEST_MC(pJoint1->Support());
   TRY_TEST_MC(pJoint4->Support());

   // create members
   CComPtr<IFem2dMemberCollection> pMembers;
   TRY_TEST_HR(pmodel->get_Members(&pMembers));

   Float64 E=100;
   Float64 A=100;
   Float64 I=833.333;
   CComPtr<IFem2dMember> pMember1, pMember2, pMember3;
   TRY_TEST_MC(pMembers->Create(1,  1,  2, E*A, E*I, &pMember1));
   TRY_TEST_MC(pMembers->Create(2,  2,  3, E*A, E*I, &pMember2));
   TRY_TEST_MC(pMembers->Create(3,  3,  4, E*A, E*I, &pMember3));

   // create load cases and apply Distributed loads to members
   CComPtr<IFem2dLoadingCollection> pLoadings;
   TRY_TEST_HR(pmodel->get_Loadings(&pLoadings));

   // first is load on member 2
   CComPtr<IFem2dLoading> pLoading1;
   TRY_TEST_LC(pLoadings->Create(1, &pLoading1));
   CComPtr<IFem2dDistributedLoadCollection> pDistributedLoads1;
   TRY_TEST_HR(pLoading1->get_DistributedLoads(&pDistributedLoads1));
   CComPtr<IFem2dDistributedLoad> pDistributedLoad1;
   TRY_TEST_LC(pDistributedLoads1->Create(1, 2, loadDirFx, -0.2, -0.8, 100.0, 50.0, lotMember, &pDistributedLoad1));

   CComPtr<IFem2dLoading> pLoading2;
   TRY_TEST_LC(pLoadings->Create(2, &pLoading2));
   CComPtr<IFem2dDistributedLoadCollection> pDistributedLoads2;
   TRY_TEST_HR(pLoading2->get_DistributedLoads(&pDistributedLoads2));
   CComPtr<IFem2dDistributedLoad> pDistributedLoad2;
   TRY_TEST_LC(pDistributedLoads2->Create(1, 1, loadDirFx, -0.2, -0.8, 100.0, 50.0, lotMember, &pDistributedLoad2));

   // now let's add some POI's at internal quarter points on elements
   CComPtr<IFem2dPOICollection> pPOIs;
   TRY_TEST_HR(pmodel->get_POIs(&pPOIs));

   CComPtr<IFem2dPOI> pPOI11,pPOI12,pPOI13;
   TRY_TEST_HR(pPOIs->Create(11,  1,  -0.25,  &pPOI11));
   TRY_TEST_HR(pPOIs->Create(12,  1,  -0.5,  &pPOI12));
   TRY_TEST_HR(pPOIs->Create(13,  1,  -0.75,  &pPOI13));

   CComPtr<IFem2dPOI> pPOI21,pPOI22,pPOI23;
   TRY_TEST_HR(pPOIs->Create(21,  2,  -0.25,  &pPOI21));
   TRY_TEST_HR(pPOIs->Create(22,  2,  -0.5,   &pPOI22));
   TRY_TEST_HR(pPOIs->Create(23,  2,  -0.75,  &pPOI23));

   CComPtr<IFem2dPOI> pPOI31,pPOI32,pPOI33;
   TRY_TEST_HR(pPOIs->Create(31,  3,  -0.25,  &pPOI31));
   TRY_TEST_HR(pPOIs->Create(32,  3,  -0.5,   &pPOI32));
   TRY_TEST_HR(pPOIs->Create(33,  3,  -0.75,  &pPOI33));

   // get results interface
   CComQIPtr<IFem2dModelResults> presults(pmodel);

   // reactions - loading 1
   Float64 fx, fy, mz;
   TRY_TEST_HR(presults->ComputeReactions(1, 1, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   -292.44212116202));
   TRY_TEST_B( IsEqual(fy,  -313.06901466568));
   TRY_TEST_B( IsEqual(mz,   2060.6614437544));
   TRY_TEST_HR(presults->ComputeReactions(1, 4, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  -157.55787883798));
   TRY_TEST_B( IsEqual(fy,  88.069014665680));
   TRY_TEST_B( IsEqual(mz,  1558.6484095887));

   // reactions - loading 2
   TRY_TEST_HR(presults->ComputeReactions(2, 1, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,     2.7877082281446));
   TRY_TEST_B( IsEqual(fy,  -430.80005048334));
   TRY_TEST_B( IsEqual(mz,    85.977787618096));
   TRY_TEST_HR(presults->ComputeReactions(2, 4, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  -2.7877082281446));
   TRY_TEST_B( IsEqual(fy,  -19.199949516660));
   TRY_TEST_B( IsEqual(mz,  106.02170754850));

   // get joint Deflections - L1
   Float64 dx, dy, rz;
   TRY_TEST_HR(presults->ComputeJointDeflections(1, 2, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  0.65151288453378) );
   TRY_TEST_B( IsEqual(dy, 0.31306901466568) );
   TRY_TEST_B( IsEqual(rz, -0.071814129278972) );
   TRY_TEST_HR(presults->ComputeJointDeflections(1, 3, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  1.0406600870525) );
   TRY_TEST_B( IsEqual(dy, -0.13210352199852) );
   TRY_TEST_B( IsEqual(rz, -0.067853604436147) );

   // get joint Deflections - L2
   TRY_TEST_HR(presults->ComputeJointDeflections(2, 2, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  0.057162111891991) );
   TRY_TEST_B( IsEqual(dy, 0.19080005048334) );
   TRY_TEST_B( IsEqual(rz, -0.011989964247044) );
   TRY_TEST_HR(presults->ComputeJointDeflections(2, 3, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.12431232437543) );
   TRY_TEST_B( IsEqual(dy, 0.028799924274989) );
   TRY_TEST_B( IsEqual(rz, -0.015320507378938) );

   // next look at poi forces - L1
   TRY_TEST_HR(presults->ComputePOIForces(1, 11, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  313.06901466568));
   TRY_TEST_B( IsEqual(fy, -292.44212116202));
   TRY_TEST_B( IsEqual(mz, -1329.5561408494));
   TRY_TEST_HR(presults->ComputePOIForces(1, 12, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  313.06901466568));
   TRY_TEST_B( IsEqual(fy, -292.44212116202));
   TRY_TEST_B( IsEqual(mz, -598.45083794433));
   TRY_TEST_HR(presults->ComputePOIForces(1, 13, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx, 313.06901466568));
   TRY_TEST_B( IsEqual(fy, -292.44212116202));
   TRY_TEST_B( IsEqual(mz, 132.65446496072));
   TRY_TEST_HR(presults->ComputePOIForces(1, 21, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  346.83982395006));
   TRY_TEST_B( IsEqual(fy, 149.23334689603));
   TRY_TEST_B( IsEqual(mz, 446.63988265411));
   TRY_TEST_HR(presults->ComputePOIForces(1, 22, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  108.09298260243));
   TRY_TEST_B( IsEqual(fy, 149.23334689603));
   TRY_TEST_B( IsEqual(mz, 29.519997442435));
   TRY_TEST_HR(presults->ComputePOIForces(1, 23, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx, -72.422921831151));
   TRY_TEST_B( IsEqual(fy, 149.23334689603));
   TRY_TEST_B( IsEqual(mz, -387.59988776924));
   TRY_TEST_HR(presults->ComputePOIForces(1, 32, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   -88.069014665680));
   TRY_TEST_B( IsEqual(fy,  -157.55787883798));
   TRY_TEST_B( IsEqual(mz, 376.96431830392));

   // next look at poi forces - L2
   TRY_TEST_HR(presults->ComputePOIForces(2, 11, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  381.84171715001));
   TRY_TEST_B( IsEqual(fy, 2.7877082281446));
   TRY_TEST_B( IsEqual(mz, -92.947058188457));
   TRY_TEST_HR(presults->ComputePOIForces(2, 12, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  168.30005048334));
   TRY_TEST_B( IsEqual(fy, 2.7877082281446));
   TRY_TEST_B( IsEqual(mz, -99.916328758819));
   TRY_TEST_HR(presults->ComputePOIForces(2, 13, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  6.8417171500071));
   TRY_TEST_B( IsEqual(fy, 2.7877082281446));
   TRY_TEST_B( IsEqual(mz, -106.88559932918));
   TRY_TEST_HR(presults->ComputePOIForces(2, 21, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  -11.079880496590));
   TRY_TEST_B( IsEqual(fy,  -15.926255893613));
   TRY_TEST_B( IsEqual(mz,  -69.339631393074));
   TRY_TEST_HR(presults->ComputePOIForces(2, 22, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  -11.079880496590));
   TRY_TEST_B( IsEqual(fy,  -15.926255893613));
   TRY_TEST_B( IsEqual(mz,  -24.824392886605));
   TRY_TEST_HR(presults->ComputePOIForces(2, 23, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  -11.079880496590));
   TRY_TEST_B( IsEqual(fy, -15.926255893613));
   TRY_TEST_B( IsEqual(mz, 19.690845619863));
   TRY_TEST_HR(presults->ComputePOIForces(2, 32, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  19.199949516660));
   TRY_TEST_B( IsEqual(fy, -2.7877082281446));
   TRY_TEST_B( IsEqual(mz, 85.113895837416));

   ReleaseModel(pmodel);
}