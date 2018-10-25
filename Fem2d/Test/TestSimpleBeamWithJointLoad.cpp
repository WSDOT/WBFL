///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2018  Washington State Department of Transportation
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
// TestSimpleBeamWithJointLoad.cpp: implementation of the CTestSimpleBeamWithJointLoad class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestSimpleBeamWithJointLoad.h"
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


CTestSimpleBeamWithJointLoad::CTestSimpleBeamWithJointLoad()
{

}

CTestSimpleBeamWithJointLoad::~CTestSimpleBeamWithJointLoad()
{

}

void CTestSimpleBeamWithJointLoad::Test()
{

// create a model   
/*////////////////////////////////////////////////////

                         | P=4 at L/2
                         V
           0=============0===============0
           A                             O

       L = 8           Mc = PL/4 = 8
       EA = 3.0        Dc = PL^3/48EI = 
       EI = 7.0

*/////////////////////////////////////////////////
   CComPtr<IFem2dModel> pmodel;
   pmodel = CreateModel();
   ATLASSERT(pmodel);

   // create joints
   CComPtr<IFem2dJointCollection> pJoints;
   TRY_TEST_HR(pmodel->get_Joints(&pJoints));

   CComPtr<IFem2dJoint> pJoint0,pJoint4,pJoint8;
   TRY_TEST_MC(pJoints->Create(0,  0.0,  0.0, &pJoint0));
   TRY_TEST_MC(pJoints->Create(4,  4.0,  0.0, &pJoint4));
   TRY_TEST_MC(pJoints->Create(8,  8.0,  0.0, &pJoint8));

   // boundary conditions
   TRY_TEST_MC(pJoint0->Support());
   TRY_TEST_MC(pJoint0->ReleaseDof(jrtMz));
   TRY_TEST_MC(pJoint8->Support());
   TRY_TEST_MC(pJoint8->ReleaseDof(jrtFx));
   TRY_TEST_MC(pJoint8->ReleaseDof(jrtMz));

   // create members
   CComPtr<IFem2dMemberCollection> pMembers;
   TRY_TEST_HR(pmodel->get_Members(&pMembers));

   CComPtr<IFem2dMember> pMember1,pMember2;
   TRY_TEST_MC(pMembers->Create(1,  0,  4, 3.0, 7.0, &pMember1));
   TRY_TEST_MC(pMembers->Create(2,  4,  8, 3.0, 7.0, &pMember2));

   // create load case and apply point load to joint
   CComPtr<IFem2dLoadingCollection> pLoadings;
   TRY_TEST_HR(pmodel->get_Loadings(&pLoadings));
   CComPtr<IFem2dLoading> pLoading;
   TRY_TEST_LC(pLoadings->Create(0, &pLoading));
   CComPtr<IFem2dJointLoadCollection> pJointLoads;
   TRY_TEST_HR(pLoading->get_JointLoads(&pJointLoads));

   CComPtr<IFem2dJointLoad> pJointLoad;
   TRY_TEST_LC(pJointLoads->Create(0, 4, 0.0, -4.0, 0.0, &pJointLoad));

   // now let's add some POI's at 1/4 points in member 1
   // these results are pre-calculated
   CComPtr<IFem2dPOICollection> pPOIs;
   TRY_TEST_HR(pmodel->get_POIs(&pPOIs));

   CComPtr<IFem2dPOI> pPOI10,pPOI15,pPOI12,pPOILost;
   TRY_TEST_HR(pPOIs->Create(10,  1,  0.0, &pPOI10));
   TRY_TEST_HR(pPOIs->Create(15,  1,  -.5, &pPOI15));
   TRY_TEST_HR(pPOIs->Create(12,  1,  -1.0, &pPOI12));
   TRY_TEST_HR(pPOIs->Create(13,  5,  -1.0, &pPOILost)); // member doesn't exist

   // get results interface
   CComQIPtr<IFem2dModelResults> presults(pmodel);
   CComQIPtr<IFem2dModelResultsEx> presultsex(pmodel);


   PoiIDType id;
   TRY_TEST_HR(pPOIs->Remove(13, atID, &id));
   TRY_TEST( id, 13 );

   // get joint Deflections
   Float64 dx, dy, rz;
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 0, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, -2.2857142857143) );
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 4, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, -6.0952380952381));
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 8, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 2.2857142857143) );

   // test error handling
   TRY_TEST(presults->ComputeJointDeflections(1, 8, &dx, &dy, &rz),FEM2D_E_LOADING_NOT_FOUND);
   TRY_TEST(presults->ComputeJointDeflections(0,11, &dx, &dy, &rz),FEM2D_E_JOINT_NOT_FOUND);

   // get member end forces
   Float64 sfx, sfy, smz, efx, efy, emz;
   TRY_TEST_HR(presults->ComputeMemberForces(0, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx, 0.0) );
   TRY_TEST_B( IsEqual(sfy, 2.0));
   TRY_TEST_B( IsEqual(smz, 0.0));
   TRY_TEST_B( IsEqual(efx, 0.0));
   TRY_TEST_B( IsEqual(efy, -2.0));
   TRY_TEST_B( IsEqual(emz, 8.0));
   TRY_TEST_HR(presults->ComputeMemberForces(0, 2, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,  0.0) );
   TRY_TEST_B( IsEqual(sfy, -2.0));
   TRY_TEST_B( IsEqual(smz, -8.0));
   TRY_TEST_B( IsEqual(efx,  0.0));
   TRY_TEST_B( IsEqual(efy,  2.0));
   TRY_TEST_B( IsEqual(emz,  0.0));

   TRY_TEST_HR(presultsex->ComputeMemberForcesEx(0, 1, lotGlobal, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx, 0.0) );
   TRY_TEST_B( IsEqual(sfy, 2.0));
   TRY_TEST_B( IsEqual(smz, 0.0));
   TRY_TEST_B( IsEqual(efx, 0.0));
   TRY_TEST_B( IsEqual(efy, -2.0));
   TRY_TEST_B( IsEqual(emz, 8.0));
   TRY_TEST_HR(presultsex->ComputeMemberForcesEx(0, 2, lotGlobal, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,  0.0) );
   TRY_TEST_B( IsEqual(sfy, -2.0));
   TRY_TEST_B( IsEqual(smz, -8.0));
   TRY_TEST_B( IsEqual(efx,  0.0));
   TRY_TEST_B( IsEqual(efy,  2.0));
   TRY_TEST_B( IsEqual(emz,  0.0));


   // load case doesn't exist
   TRY_TEST(presults->ComputeMemberForces(1, 2, &sfx, &sfy, &smz, &efx, &efy, &emz),FEM2D_E_LOADING_NOT_FOUND);
   TRY_TEST(presults->ComputeMemberForces(0, 4, &sfx, &sfy, &smz, &efx, &efy, &emz),FEM2D_E_MEMBER_NOT_FOUND);
   TRY_TEST(presultsex->ComputeMemberForcesEx(1, 2, lotGlobal, &sfx, &sfy, &smz, &efx, &efy, &emz),FEM2D_E_LOADING_NOT_FOUND);
   TRY_TEST(presultsex->ComputeMemberForcesEx(0, 4, lotMember, &sfx, &sfy, &smz, &efx, &efy, &emz),FEM2D_E_MEMBER_NOT_FOUND);

   Float64 fx, fy, mz;
   TRY_TEST_HR(presults->ComputeReactions(0, 0, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  2.0));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputeReactions(0, 4, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputeReactions(0, 8, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  2.0));
   TRY_TEST_B( IsEqual(mz,  0.0));

   TRY_TEST(presults->ComputeReactions(1, 8, &fx, &fy, &mz),FEM2D_E_LOADING_NOT_FOUND);
   TRY_TEST(presults->ComputeReactions(0, 12, &fx, &fy, &mz),FEM2D_E_JOINT_NOT_FOUND);

   // get member Deflections
   Float64 sdx, sdy, srz, edx, edy, erz;
   TRY_TEST_HR(presults->ComputeMemberDeflections(0, 1, &sdx, &sdy, &srz, &edx, &edy, &erz));
   TRY_TEST_B( IsEqual(sdx,   0.0) );
   TRY_TEST_B( IsEqual(sdy,   0.0));
   TRY_TEST_B( IsEqual(srz, -2.2857142857143));
   TRY_TEST_B( IsEqual(edx,   0.0));
   TRY_TEST_B( IsEqual(edy, -6.0952380952381));
   TRY_TEST_B( IsEqual(erz,   0.0));
   TRY_TEST_HR(presults->ComputeMemberDeflections(0, 2, &sdx, &sdy, &srz, &edx, &edy, &erz));
   TRY_TEST_B( IsEqual(sdx,   0.0) );
   TRY_TEST_B( IsEqual(sdy, -6.0952380952381));
   TRY_TEST_B( IsEqual(srz,   0.0));
   TRY_TEST_B( IsEqual(edx,   0.0));
   TRY_TEST_B( IsEqual(edy,   0.0));
   TRY_TEST_B( IsEqual(erz,   2.2857142857143));

   TRY_TEST(presults->ComputeMemberDeflections(1, 2, &sdx, &sdy, &srz, &edx, &edy, &erz),FEM2D_E_LOADING_NOT_FOUND);
   TRY_TEST(presults->ComputeMemberDeflections(0,21, &sdx, &sdy, &srz, &edx, &edy, &erz),FEM2D_E_MEMBER_NOT_FOUND);

   // now let's add some POI's at 1/4 points of member 2
   // these results are calculated on the fly
   CComPtr<IFem2dPOI> pPOI20,pPOI25,pPOI22;
   TRY_TEST_HR(pPOIs->Create(20,  2,  0.0, &pPOI20));
   TRY_TEST_HR(pPOIs->Create(25,  2,  2.0, &pPOI25));
   TRY_TEST_HR(pPOIs->Create(22,  2,  4.0, &pPOI22));

   // poi that doesn't exist
   TRY_TEST(presults->ComputePOIDeflections(0, 13, lotMember, &dx, &dy, &rz),FEM2D_E_POI_NOT_FOUND);
 
   // look at Deflections
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 10, lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, -2.2857142857143) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 15, lotMember,  &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, -4.1904761904762));
   TRY_TEST_B( IsEqual(rz, -1.71428) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 12, lotMember,  &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, -6.0952380952381));
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 20, lotMember,  &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, -6.0952380952381));
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 25, lotMember,  &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, -4.1904761904762));
   TRY_TEST_B( IsEqual(rz, 1.71428) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 22, lotMember,  &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 2.2857142857143) );

   TRY_TEST_HR(presults->ComputePOIDeflections(0, 10, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, -2.2857142857143) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 15, lotGlobal,  &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, -4.1904761904762));
   TRY_TEST_B( IsEqual(rz, -1.71428) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 12, lotGlobal,  &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, -6.0952380952381));
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 20, lotGlobal,  &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, -6.0952380952381));
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 25, lotGlobal,  &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, -4.1904761904762));
   TRY_TEST_B( IsEqual(rz, 1.71428) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 22, lotGlobal,  &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 2.2857142857143) );


   TRY_TEST(presults->ComputePOIDeflections(10, 22,  lotMember, &dx, &dy, &rz),FEM2D_E_LOADING_NOT_FOUND);
   TRY_TEST(presults->ComputePOIDeflections(0, 32,  lotMember, &dx, &dy, &rz),FEM2D_E_POI_NOT_FOUND);

   // next look at poi foces at both faces and orientations
   TRY_TEST_HR(presults->ComputePOIForces(0, 10, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -2.0));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 10, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  2.0));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 10, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  -2.0));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 10, mftRight, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  2.0));
   TRY_TEST_B( IsEqual(mz,  0.0));

   TRY_TEST_HR(presults->ComputePOIForces(0, 15, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  -2.0));
   TRY_TEST_B( IsEqual(mz,  4.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 15, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  2.0));
   TRY_TEST_B( IsEqual(mz,  -4.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 15, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  -2.0));
   TRY_TEST_B( IsEqual(mz,  4.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 15, mftRight, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  2.0));
   TRY_TEST_B( IsEqual(mz,  -4.0));

   TRY_TEST_HR(presults->ComputePOIForces(0, 12, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  -2.0));
   TRY_TEST_B( IsEqual(mz,  8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 12, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  2.0));
   TRY_TEST_B( IsEqual(mz,  -8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 12, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  -2.0));
   TRY_TEST_B( IsEqual(mz,  8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 12, mftRight, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  2.0));
   TRY_TEST_B( IsEqual(mz,  -8.0));

   TRY_TEST_HR(presults->ComputePOIForces(0, 20, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  2.0));
   TRY_TEST_B( IsEqual(mz,  8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 20, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  -2.0));
   TRY_TEST_B( IsEqual(mz,  -8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 20, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  2.0));
   TRY_TEST_B( IsEqual(mz,  8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 20, mftRight, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  -2.0));
   TRY_TEST_B( IsEqual(mz,  -8.0));

   TRY_TEST_HR(presults->ComputePOIForces(0, 25, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  2.0));
   TRY_TEST_B( IsEqual(mz,  4.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 25, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  -2.0));
   TRY_TEST_B( IsEqual(mz,  -4.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 25, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  2.0));
   TRY_TEST_B( IsEqual(mz,  4.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 25, mftRight, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  -2.0));
   TRY_TEST_B( IsEqual(mz,  -4.0));

   TRY_TEST(presults->ComputePOIForces(10, 25, mftRight, lotMember, &fx, &fy, &mz),FEM2D_E_LOADING_NOT_FOUND);
   TRY_TEST(presults->ComputePOIForces(0 , 32, mftRight, lotMember, &fx, &fy, &mz),FEM2D_E_POI_NOT_FOUND);


//////////////////////////////////////////////////////////////////////////////////
// ================================================================================
// add a new load case with a horizontal load at the middle
   // create load case and apply point load with magnitude of 2.0 to joint
   CComPtr<IFem2dLoading> pLoading2;
   TRY_TEST_LC(pLoadings->Create(2, &pLoading2));
   CComPtr<IFem2dJointLoadCollection> pJointLoads2;
   TRY_TEST_HR(pLoading2->get_JointLoads(&pJointLoads2));

   CComPtr<IFem2dJointLoad> pJointLoad2;
   TRY_TEST_LC(pJointLoads2->Create(0, 4, 2.0, 0.0, 0.0, &pJointLoad2));

   // get joint Deflections
   TRY_TEST_HR(presults->ComputeJointDeflections(2, 0, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputeJointDeflections(2, 4, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 2.6666667) );
   TRY_TEST_B( IsEqual(dy, 0.0));
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputeJointDeflections(2, 8, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 2.6666667) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 0.0) );

   // get member end forces
   TRY_TEST_HR(presults->ComputeMemberForces(2, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,-2.0) );
   TRY_TEST_B( IsEqual(sfy, 0.0));
   TRY_TEST_B( IsEqual(smz, 0.0));
   TRY_TEST_B( IsEqual(efx, 2.0));
   TRY_TEST_B( IsEqual(efy, 0.0));
   TRY_TEST_B( IsEqual(emz, 0.0));
   TRY_TEST_HR(presults->ComputeMemberForces(2, 2, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,  0.0) );
   TRY_TEST_B( IsEqual(sfy,  0.0));
   TRY_TEST_B( IsEqual(smz,  0.0));
   TRY_TEST_B( IsEqual(efx,  0.0));
   TRY_TEST_B( IsEqual(efy,  0.0));
   TRY_TEST_B( IsEqual(emz,  0.0));

   TRY_TEST_HR(presultsex->ComputeMemberForcesEx(2, 1, lotGlobal, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,-2.0) );
   TRY_TEST_B( IsEqual(sfy, 0.0));
   TRY_TEST_B( IsEqual(smz, 0.0));
   TRY_TEST_B( IsEqual(efx, 2.0));
   TRY_TEST_B( IsEqual(efy, 0.0));
   TRY_TEST_B( IsEqual(emz, 0.0));
   TRY_TEST_HR(presultsex->ComputeMemberForcesEx(2, 2, lotGlobal, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,  0.0) );
   TRY_TEST_B( IsEqual(sfy,  0.0));
   TRY_TEST_B( IsEqual(smz,  0.0));
   TRY_TEST_B( IsEqual(efx,  0.0));
   TRY_TEST_B( IsEqual(efy,  0.0));
   TRY_TEST_B( IsEqual(emz,  0.0));

   TRY_TEST_HR(presults->ComputeReactions(2, 0, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx, -2.0));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputeReactions(2, 4, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputeReactions(2, 8, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));

   // get member end displ
   TRY_TEST_HR(presults->ComputeMemberDeflections(2, 1, &sdx, &sdy, &srz, &edx, &edy, &erz));
   TRY_TEST_B( IsEqual(sdx,   0.0) );
   TRY_TEST_B( IsEqual(sdy,   0.0));
   TRY_TEST_B( IsEqual(srz,   0.0));
   TRY_TEST_B( IsEqual(edx,   2.6666667));
   TRY_TEST_B( IsEqual(edy,   0.0));
   TRY_TEST_B( IsEqual(erz,   0.0));
   TRY_TEST_HR(presults->ComputeMemberDeflections(2, 2, &sdx, &sdy, &srz, &edx, &edy, &erz));
   TRY_TEST_B( IsEqual(sdx,   2.6666667) );
   TRY_TEST_B( IsEqual(sdy,   0.0));
   TRY_TEST_B( IsEqual(srz,   0.0));
   TRY_TEST_B( IsEqual(edx,   2.6666667));
   TRY_TEST_B( IsEqual(edy,   0.0));
   TRY_TEST_B( IsEqual(erz,   0.0));

   // At POI's
   // look at Deflections
   TRY_TEST_HR(presults->ComputePOIDeflections(2, 10,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDeflections(2, 15,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 1.333333) );
   TRY_TEST_B( IsEqual(dy, 0.0));
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDeflections(2, 12,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 2.6666667) );
   TRY_TEST_B( IsEqual(dy, 0.0));
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDeflections(2, 20,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 2.6666667) );
   TRY_TEST_B( IsEqual(dy, 0.0));
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDeflections(2, 25,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 2.6666667) );
   TRY_TEST_B( IsEqual(dy, 0.0));
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDeflections(2, 22,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 2.6666667) );
   TRY_TEST_B( IsEqual(dy, 0.0));
   TRY_TEST_B( IsEqual(rz, 0.0) );

   TRY_TEST_HR(presults->ComputePOIDeflections(2, 10,  lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDeflections(2, 15,  lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 1.333333) );
   TRY_TEST_B( IsEqual(dy, 0.0));
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDeflections(2, 12,  lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 2.6666667) );
   TRY_TEST_B( IsEqual(dy, 0.0));
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDeflections(2, 20,  lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 2.6666667) );
   TRY_TEST_B( IsEqual(dy, 0.0));
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDeflections(2, 25,  lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 2.6666667) );
   TRY_TEST_B( IsEqual(dy, 0.0));
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDeflections(2, 22,  lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 2.6666667) );
   TRY_TEST_B( IsEqual(dy, 0.0));
   TRY_TEST_B( IsEqual(rz, 0.0) );


   // next look at poi forces at both faces and orientations
   TRY_TEST_HR(presults->ComputePOIForces(2, 10, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  2.0));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(2, 10, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx, -2.0));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(2, 10, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  2.0));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(2, 10, mftRight, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx, -2.0));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));

   TRY_TEST_HR(presults->ComputePOIForces(2, 15, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  2.0));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(2, 15, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx, -2.0));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(2, 15, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  2.0));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(2, 15, mftRight, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx, -2.0));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));

   TRY_TEST_HR(presults->ComputePOIForces(2, 12, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  2.0));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(2, 12, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx, -2.0));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(2, 12, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  2.0));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(2, 12, mftRight, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx, -2.0));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));

   TRY_TEST_HR(presults->ComputePOIForces(2, 20, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(2, 20, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(2, 20, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(2, 20, mftRight, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));

   TRY_TEST_HR(presults->ComputePOIForces(2, 25, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(2, 25, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(2, 25, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(2, 25, mftRight, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));

//////////////////////////////////////////////////////////////////////////////////
// ================================================================================
// next let's rotate the model 45 degrees clockwise
   TRY_TEST_MC(pJoint4->put_X(2.8284271));
   TRY_TEST_MC(pJoint4->put_Y(2.8284271));
   TRY_TEST_MC(pJoint8->put_X(5.6568542));
   TRY_TEST_MC(pJoint8->put_Y(5.6568542));

   // don't allow end joint to translate
   TRY_TEST_MC(pJoint8->Support());
   TRY_TEST_MC(pJoint8->ReleaseDof(jrtMz));

   Float64 l;
   pMember1->get_Length(&l);
   TRY_TEST_B(IsEqual(l, 4.0));
   pMember2->get_Length(&l);
   TRY_TEST_B(IsEqual(l, 4.0));

   // change orientation of point load to be normal to rotated structure
   TRY_TEST_LC(pJointLoad->put_Fx(2.8284271));
   TRY_TEST_LC(pJointLoad->put_Fy(-2.8284271));

   // get joint Deflections
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 0, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, -2.2857142857143) );
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 4, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  4.30998419) );
   TRY_TEST_B( IsEqual(dy, -4.30998419));
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 8, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 2.2857142857143) );

   // get member end forces
   TRY_TEST_HR(presults->ComputeMemberForces(0, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx, 0.0) );
   TRY_TEST_B( IsEqual(sfy, 2.0));
   TRY_TEST_B( IsEqual(smz, 0.0));
   TRY_TEST_B( IsEqual(efx, 0.0));
   TRY_TEST_B( IsEqual(efy, -2.0));
   TRY_TEST_B( IsEqual(emz, 8.0));
   TRY_TEST_HR(presults->ComputeMemberForces(0, 2, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,  0.0) );
   TRY_TEST_B( IsEqual(sfy, -2.0));
   TRY_TEST_B( IsEqual(smz, -8.0));
   TRY_TEST_B( IsEqual(efx,  0.0));
   TRY_TEST_B( IsEqual(efy,  2.0));
   TRY_TEST_B( IsEqual(emz,  0.0));

   TRY_TEST_HR(presultsex->ComputeMemberForcesEx(0, 1, lotMember, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx, 0.0) );
   TRY_TEST_B( IsEqual(sfy, 2.0));
   TRY_TEST_B( IsEqual(smz, 0.0));
   TRY_TEST_B( IsEqual(efx, 0.0));
   TRY_TEST_B( IsEqual(efy, -2.0));
   TRY_TEST_B( IsEqual(emz, 8.0));
   TRY_TEST_HR(presultsex->ComputeMemberForcesEx(0, 2, lotMember, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,  0.0) );
   TRY_TEST_B( IsEqual(sfy, -2.0));
   TRY_TEST_B( IsEqual(smz, -8.0));
   TRY_TEST_B( IsEqual(efx,  0.0));
   TRY_TEST_B( IsEqual(efy,  2.0));
   TRY_TEST_B( IsEqual(emz,  0.0));

   TRY_TEST_HR(presultsex->ComputeMemberForcesEx(0, 1, lotGlobal, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx, -1.41421356));
   TRY_TEST_B( IsEqual(sfy,  1.41421356));
   TRY_TEST_B( IsEqual(smz,  0.0));
   TRY_TEST_B( IsEqual(efx,  1.41421355));
   TRY_TEST_B( IsEqual(efy, -1.41421355));
   TRY_TEST_B( IsEqual(emz, 8.0));
   TRY_TEST_HR(presultsex->ComputeMemberForcesEx(0, 2, lotGlobal, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,  1.41421355) );
   TRY_TEST_B( IsEqual(sfy, -1.41421355));
   TRY_TEST_B( IsEqual(smz, -8.0));
   TRY_TEST_B( IsEqual(efx,  -1.41421356));
   TRY_TEST_B( IsEqual(efy,  1.41421356));
   TRY_TEST_B( IsEqual(emz,  0.0));

   TRY_TEST_HR(presults->ComputeReactions(0, 0, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  -1.41421356));
   TRY_TEST_B( IsEqual(fy,  1.41421356));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputeReactions(0, 4, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputeReactions(0, 8, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  -1.41421356));
   TRY_TEST_B( IsEqual(fy,  1.41421356));
   TRY_TEST_B( IsEqual(mz,  0.0));

   TRY_TEST(presults->ComputeReactions(1, 8, &fx, &fy, &mz),FEM2D_E_LOADING_NOT_FOUND);
   TRY_TEST(presults->ComputeReactions(0, 12, &fx, &fy, &mz),FEM2D_E_JOINT_NOT_FOUND);

   // get merber end forces
   TRY_TEST_HR(presults->ComputeMemberDeflections(0, 1, &sdx, &sdy, &srz, &edx, &edy, &erz));
   TRY_TEST_B( IsEqual(sdx,   0.0) );
   TRY_TEST_B( IsEqual(sdy,   0.0));
   TRY_TEST_B( IsEqual(srz, -2.2857142857143));
   TRY_TEST_B( IsEqual(edx,   0.0));
   TRY_TEST_B( IsEqual(edy, -6.0952380952381));
   TRY_TEST_B( IsEqual(erz,   0.0));
   TRY_TEST_HR(presults->ComputeMemberDeflections(0, 2, &sdx, &sdy, &srz, &edx, &edy, &erz));
   TRY_TEST_B( IsEqual(sdx,   0.0) );
   TRY_TEST_B( IsEqual(sdy, -6.0952380952381));
   TRY_TEST_B( IsEqual(srz,   0.0));
   TRY_TEST_B( IsEqual(edx,   0.0));
   TRY_TEST_B( IsEqual(edy,   0.0));
   TRY_TEST_B( IsEqual(erz,   2.2857142857143));

   // look at Deflections
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 10,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, -2.2857142857143) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 15,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, -4.1904761904762));
   TRY_TEST_B( IsEqual(rz, -1.71428) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 12,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, -6.0952380952381));
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 20,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, -6.0952380952381));
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 25,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, -4.1904761904762));
   TRY_TEST_B( IsEqual(rz, 1.71428) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 22,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 2.2857142857143) );

   TRY_TEST_HR(presults->ComputePOIDeflections(0, 10,  lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, -2.2857142857143) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 15,  lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  2.9631141) );
   TRY_TEST_B( IsEqual(dy, -2.9631141));
   TRY_TEST_B( IsEqual(rz, -1.71428) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 12,  lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  4.3099842) );
   TRY_TEST_B( IsEqual(dy, -4.3099842));
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 20,  lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  4.3099842) );
   TRY_TEST_B( IsEqual(dy, -4.3099842));
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 25,  lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  2.9631141) );
   TRY_TEST_B( IsEqual(dy, -2.9631141));
   TRY_TEST_B( IsEqual(rz, 1.71428) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 22,  lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 2.2857142857143) );


   // next look at poi foces at both faces and orientations
   TRY_TEST_HR(presults->ComputePOIForces(0, 10, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  1.41421355));
   TRY_TEST_B( IsEqual(fy, -1.41421355));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 10, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx, -1.41421355));
   TRY_TEST_B( IsEqual(fy,  1.41421355));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 10, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -2.0));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 10, mftRight, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  2.0));
   TRY_TEST_B( IsEqual(mz,  0.0));

   TRY_TEST_HR(presults->ComputePOIForces(0, 15, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   1.41421355));
   TRY_TEST_B( IsEqual(fy,  -1.41421355));
   TRY_TEST_B( IsEqual(mz,   4.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 15, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  -1.41421355));
   TRY_TEST_B( IsEqual(fy,   1.41421355));
   TRY_TEST_B( IsEqual(mz,  -4.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 15, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -2.0));
   TRY_TEST_B( IsEqual(mz,  4.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 15, mftRight, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  2.0));
   TRY_TEST_B( IsEqual(mz, -4.0));

   TRY_TEST_HR(presults->ComputePOIForces(0, 12, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   1.41421355));
   TRY_TEST_B( IsEqual(fy,  -1.41421355));
   TRY_TEST_B( IsEqual(mz,   8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 12, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  -1.41421355));
   TRY_TEST_B( IsEqual(fy,   1.41421355));
   TRY_TEST_B( IsEqual(mz,  -8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 12, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -2.0));
   TRY_TEST_B( IsEqual(mz,  8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 12, mftRight, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  2.0));
   TRY_TEST_B( IsEqual(mz, -8.0));

   TRY_TEST_HR(presults->ComputePOIForces(0, 20, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx, -1.41421355));
   TRY_TEST_B( IsEqual(fy,  1.41421355));
   TRY_TEST_B( IsEqual(mz,  8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 20, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   1.41421355));
   TRY_TEST_B( IsEqual(fy,  -1.41421355));
   TRY_TEST_B( IsEqual(mz,  -8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 20, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  2.0));
   TRY_TEST_B( IsEqual(mz,  8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 20, mftRight, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   0.0));
   TRY_TEST_B( IsEqual(fy,  -2.0));
   TRY_TEST_B( IsEqual(mz,  -8.0));

   TRY_TEST_HR(presults->ComputePOIForces(0, 25, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  -1.41421355));
   TRY_TEST_B( IsEqual(fy,   1.41421355));
   TRY_TEST_B( IsEqual(mz,   4.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 25, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   1.41421355));
   TRY_TEST_B( IsEqual(fy,  -1.41421355));
   TRY_TEST_B( IsEqual(mz,  -4.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 25, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  2.0));
   TRY_TEST_B( IsEqual(mz,  4.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 25, mftRight, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  -2.0));
   TRY_TEST_B( IsEqual(mz,  -4.0));

   // call second function created due to compiler limits
   Test2(pmodel, pJoint0, pJoint4, pJoint8, pMember1, pMember2, pJointLoad,
         presults, presultsex);


}