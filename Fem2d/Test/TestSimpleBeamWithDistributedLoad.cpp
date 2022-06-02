///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2022  Washington State Department of Transportation
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
// TestSimpleBeamWithDistributedLoad.cpp: implementation of the CTestSimpleBeamWithDistributedLoad class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestSimpleBeamWithDistributedLoad.h"
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



CTestSimpleBeamWithDistributedLoad::CTestSimpleBeamWithDistributedLoad()
{

}

CTestSimpleBeamWithDistributedLoad::~CTestSimpleBeamWithDistributedLoad()
{

}

void CTestSimpleBeamWithDistributedLoad::Test() 
{
   Test1();
   Test2();
   Test3();
}

void CTestSimpleBeamWithDistributedLoad::Test1() 
{

/*////////////////////////////////////////////////////
                          
                     |||||||||| 
                  |||||||||||||
           ]      vvvvvvvvvvvvv          [
           ]=============================[  // fixed ends
           ]                             [

       L = 8           Mc = PL/4 = 8
       EA = 3.0        Dc = PL^3/48EI = 
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
   TRY_TEST_MC(pJoint8->Support());

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
   TRY_TEST_LC(pDistributedLoads->Create(0, 1, loadDirFy, 2.5, 5.0, 2.0, 4.0, lotMember, &pDistributedLoad));

   // now let's add some POI's at 1/4 points in member 1
   CComPtr<IFem2dPOICollection> pPOIs;
   TRY_TEST_HR(pmodel->get_POIs(&pPOIs));

   CComPtr<IFem2dPOI> pPOI10,pPOI15,pPOI12;
   TRY_TEST_HR(pPOIs->Create(10,  1,  0.0, &pPOI10));
   TRY_TEST_HR(pPOIs->Create(15,  1,  -.25, &pPOI15));
   TRY_TEST_HR(pPOIs->Create(12,  1,  -0.5, &pPOI12));

   // get results interface
   CComQIPtr<IFem2dModelResults> presults(pmodel); 

   // get joint Deflections
   Float64 dx, dy, rz;
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 0, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 8, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 0.0) );

   // get member end forces
   Float64 sfx, sfy, smz, efx, efy, emz;
   TRY_TEST_HR(presults->ComputeMemberForces(0, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx, 0.0) );
   TRY_TEST_B( IsEqual(sfy, -3.898925));
   TRY_TEST_B( IsEqual(smz, -7.438151));
   TRY_TEST_B( IsEqual(efx, 0.0));
   TRY_TEST_B( IsEqual(efy, -3.601074));
   TRY_TEST_B( IsEqual(emz,  7.080078));

   Float64 fx, fy, mz;
   TRY_TEST_HR(presults->ComputeReactions(0, 0, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  -3.89892));
   TRY_TEST_B( IsEqual(mz,  -7.43815));
   TRY_TEST_HR(presults->ComputeReactions(0, 8, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  -3.601074));
   TRY_TEST_B( IsEqual(mz,   7.080078));

   // get member end Deflections
   Float64 sdx, sdy, srz, edx, edy, erz;
   TRY_TEST_HR(presults->ComputeMemberDeflections(0, 1, &sdx, &sdy, &srz, &edx, &edy, &erz));
   TRY_TEST_B( IsEqual(sdx,   0.0) );
   TRY_TEST_B( IsEqual(sdy,   0.0));
   TRY_TEST_B( IsEqual(srz,   0.0));
   TRY_TEST_B( IsEqual(edx,   0.0));
   TRY_TEST_B( IsEqual(edy,   0.0));
   TRY_TEST_B( IsEqual(erz,   0.0));

   // now let's add some POI's at 1/4 points of on second half
   // these results are calculated on the fly
   CComPtr<IFem2dPOI> pPOI20,pPOI25,pPOI22;
   TRY_TEST_HR(pPOIs->Create(20,  1,  4.0, &pPOI20));
   TRY_TEST_HR(pPOIs->Create(25,  1,  6.0, &pPOI25));
   TRY_TEST_HR(pPOIs->Create(22,  1,  8.0, &pPOI22));

   // look at Deflections
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 10,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 15,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 1.382533));
   TRY_TEST_B( IsEqual(rz, 1.011207) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 12,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy,  2.627023809));
   TRY_TEST_B( IsEqual(rz, -0.020721726) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 20,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy,  2.627023809));
   TRY_TEST_B( IsEqual(rz, -0.020721726) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 25,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy,  1.3369605));
   TRY_TEST_B( IsEqual(rz, -0.9940011) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 22,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 0.0));

   // next look at poi forces
   TRY_TEST_HR(presults->ComputePOIForces(0, 10, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  3.8989257));
   TRY_TEST_B( IsEqual(mz,  7.4381510));
   TRY_TEST_HR(presults->ComputePOIForces(0, 10, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -3.8989257));
   TRY_TEST_B( IsEqual(mz, -7.4381510));

   TRY_TEST_HR(presults->ComputePOIForces(0, 15, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  3.8989257));
   TRY_TEST_B( IsEqual(mz, -0.3597005));
   TRY_TEST_HR(presults->ComputePOIForces(0, 15, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -3.8989257));
   TRY_TEST_B( IsEqual(mz,  0.3597005));

   TRY_TEST_HR(presults->ComputePOIForces(0, 12, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -0.00107422));
   TRY_TEST_B( IsEqual(mz, -5.457552));
   TRY_TEST_HR(presults->ComputePOIForces(0, 12, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, 0.00107422));
   TRY_TEST_B( IsEqual(mz, 5.457552));

   TRY_TEST_HR(presults->ComputePOIForces(0, 20, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,-0.00107422));
   TRY_TEST_B( IsEqual(mz,-5.457552));
   TRY_TEST_HR(presults->ComputePOIForces(0, 20, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, 0.00107422));
   TRY_TEST_B( IsEqual(mz, 5.457552));

   TRY_TEST_HR(presults->ComputePOIForces(0, 25, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,-3.601074));
   TRY_TEST_B( IsEqual(mz,-0.122070));
   TRY_TEST_HR(presults->ComputePOIForces(0, 25, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  3.601074));
   TRY_TEST_B( IsEqual(mz,  0.122070));

   TRY_TEST_HR(presults->ComputePOIForces(0, 22, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -3.601074));
   TRY_TEST_B( IsEqual(mz,  7.080078));
   TRY_TEST_HR(presults->ComputePOIForces(0, 22, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  3.601074));
   TRY_TEST_B( IsEqual(mz, -7.080078));

///////////////////////////////////////////////
///===========================================
   // try a pin-fix orientation
   TRY_TEST_MC(pMember1->ReleaseEnd(metStart, mbrReleaseMz));

   TRY_TEST_HR(presults->ComputeJointDeflections(0, 0, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 8, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 0.0) );

   // get member end forces
   TRY_TEST_HR(presults->ComputeMemberForces(0, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx, 0.0) );
   TRY_TEST_B( IsEqual(sfy,-2.5042724));
   TRY_TEST_B( IsEqual(smz, 0.0));
   TRY_TEST_B( IsEqual(efx, 0.0));
   TRY_TEST_B( IsEqual(efy,-4.9957275));
   TRY_TEST_B( IsEqual(emz, 10.7991536));

   TRY_TEST_HR(presults->ComputeReactions(0, 0, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -2.50427246));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputeReactions(0, 8, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -4.9957275));
   TRY_TEST_B( IsEqual(mz,   10.7991536));

   // get member end Deflections
   TRY_TEST_HR(presults->ComputeMemberDeflections(0, 1, &sdx, &sdy, &srz, &edx, &edy, &erz));
   TRY_TEST_B( IsEqual(sdx,   0.0) );
   TRY_TEST_B( IsEqual(sdy,   0.0));
   TRY_TEST_B( IsEqual(srz,   2.125186));
   TRY_TEST_B( IsEqual(edx,   0.0));
   TRY_TEST_B( IsEqual(edy,   0.0));
   TRY_TEST_B( IsEqual(erz,   0.0));

   // look at Deflections
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 10,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz,  2.12518601) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 15,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 3.77336774));
   TRY_TEST_B( IsEqual(rz, 1.40967959));
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 12,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  0.0) );
   TRY_TEST_B( IsEqual(dy,  4.75220982));
   TRY_TEST_B( IsEqual(rz,-0.55201822));
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 20,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy,  4.75220982));
   TRY_TEST_B( IsEqual(rz, -0.55201822));
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 25,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy,  2.133905));
   TRY_TEST_B( IsEqual(rz, -1.658121) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 22,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 0.0));

   // next look at poi forces
   TRY_TEST_HR(presults->ComputePOIForces(0, 10, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  2.5042724609375));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 10, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -2.5042724609375));
   TRY_TEST_B( IsEqual(mz,  0.0));

   TRY_TEST_HR(presults->ComputePOIForces(0, 15, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  2.5042724609375));
   TRY_TEST_B( IsEqual(mz, -5.0085449218750));
   TRY_TEST_HR(presults->ComputePOIForces(0, 15, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -2.5042724609375));
   TRY_TEST_B( IsEqual(mz,  5.0085449218750));

   TRY_TEST_HR(presults->ComputePOIForces(0, 12, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -1.3957275390625));
   TRY_TEST_B( IsEqual(mz, -7.3170898437500));
   TRY_TEST_HR(presults->ComputePOIForces(0, 12, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  1.3957275390625));
   TRY_TEST_B( IsEqual(mz,  7.3170898437500));

   TRY_TEST_HR(presults->ComputePOIForces(0, 20, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -1.3957275390625));
   TRY_TEST_B( IsEqual(mz, -7.3170898437500));
   TRY_TEST_HR(presults->ComputePOIForces(0, 20, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  1.3957275390625));
   TRY_TEST_B( IsEqual(mz,  7.3170898437500));

   TRY_TEST_HR(presults->ComputePOIForces(0, 25, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -4.9957275390625));
   TRY_TEST_B( IsEqual(mz,  0.80769856770834));
   TRY_TEST_HR(presults->ComputePOIForces(0, 25, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  4.9957275390625));
   TRY_TEST_B( IsEqual(mz, -0.80769856770834));

   TRY_TEST_HR(presults->ComputePOIForces(0, 22, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -4.9957275));
   TRY_TEST_B( IsEqual(mz, 10.7991536));
   TRY_TEST_HR(presults->ComputePOIForces(0, 22, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  4.9957275));
   TRY_TEST_B( IsEqual(mz,-10.7991536));

///////////////////////////////////////////////
///===========================================
   // try a pin-pin orientation
   TRY_TEST_MC(pMember1->ReleaseEnd(metEnd, mbrReleaseMz));

   TRY_TEST_HR(presults->ComputeJointDeflections(0, 0, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 8, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 0.0) );

   // get member end forces
   TRY_TEST_HR(presults->ComputeMemberForces(0, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx, 0.0) );
   TRY_TEST_B( IsEqual(sfy, -3.85416667));
   TRY_TEST_B( IsEqual(smz, 0.0));
   TRY_TEST_B( IsEqual(efx, 0.0));
   TRY_TEST_B( IsEqual(efy, -3.6458333));
   TRY_TEST_B( IsEqual(emz, 0.0));

   TRY_TEST_HR(presults->ComputeReactions(0, 0, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  -3.85416667));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputeReactions(0, 8, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  -3.64583333));
   TRY_TEST_B( IsEqual(mz,  0.0));

   // get member end Deflections
   TRY_TEST_HR(presults->ComputeMemberDeflections(0, 1, &sdx, &sdy, &srz, &edx, &edy, &erz));
   TRY_TEST_B( IsEqual(sdx,   0.0) );
   TRY_TEST_B( IsEqual(sdy,   0.0));
   TRY_TEST_B( IsEqual(srz,  4.18216765));
   TRY_TEST_B( IsEqual(edx,   0.0));
   TRY_TEST_B( IsEqual(edy,   0.0));
   TRY_TEST_B( IsEqual(erz, -4.11396329));

   // look at Deflections
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 10,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 4.182167658) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 15,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy,7.63020833));
   TRY_TEST_B( IsEqual(rz,3.08097718));
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 12,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  0.0) );
   TRY_TEST_B( IsEqual(dy, 10.9231547));
   TRY_TEST_B( IsEqual(rz, -0.0377728));
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 20,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  0.0) );
   TRY_TEST_B( IsEqual(dy, 10.92315));
   TRY_TEST_B( IsEqual(rz, -0.037772817));
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 25,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  0.0) );
   TRY_TEST_B( IsEqual(dy,  7.5334821428571));
   TRY_TEST_B( IsEqual(rz, -3.0722966269841));
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 22,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, -4.11396329));

   // next look at poi forces
   TRY_TEST_HR(presults->ComputePOIForces(0, 10, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  3.8541666666667));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 10, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -3.8541666666667));
   TRY_TEST_B( IsEqual(mz,  0.0));

   TRY_TEST_HR(presults->ComputePOIForces(0, 15, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  3.8541666666667));
   TRY_TEST_B( IsEqual(mz, -7.7083333333333));
   TRY_TEST_HR(presults->ComputePOIForces(0, 15, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -3.8541666666667));
   TRY_TEST_B( IsEqual(mz,  7.7083333333333));

   TRY_TEST_HR(presults->ComputePOIForces(0, 12, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -0.045833333333333));
   TRY_TEST_B( IsEqual(mz, -12.716666666667));
   TRY_TEST_HR(presults->ComputePOIForces(0, 12, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  0.045833333333333));
   TRY_TEST_B( IsEqual(mz,  12.716666666667));

   TRY_TEST_HR(presults->ComputePOIForces(0, 20, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -0.045833333333333));
   TRY_TEST_B( IsEqual(mz, -12.716666666667));
   TRY_TEST_HR(presults->ComputePOIForces(0, 20, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  0.045833333333333));
   TRY_TEST_B( IsEqual(mz,  12.716666666667));

   TRY_TEST_HR(presults->ComputePOIForces(0, 25, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -3.6458333333333));
   TRY_TEST_B( IsEqual(mz, -7.2916666666667));
   TRY_TEST_HR(presults->ComputePOIForces(0, 25, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  3.645833333333));
   TRY_TEST_B( IsEqual(mz,  7.2916666666667));

   TRY_TEST_HR(presults->ComputePOIForces(0, 22, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -3.6458333333333));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 22, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  3.6458333333333));
   TRY_TEST_B( IsEqual(mz,  0.0));


///////////////////////////////////////////////
///===========================================
   // try a fix-pin orientation
   TRY_TEST_MC(pMember1->ReleaseEnd(metStart, mbrReleaseNone));
   TRY_TEST_MC(pMember1->ReleaseEnd(metEnd  , mbrReleaseMz));

   TRY_TEST_HR(presults->ComputeJointDeflections(0, 0, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 8, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 0.0) );

   // get member end forces
   TRY_TEST_HR(presults->ComputeMemberForces(0, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx, 0.0) );
   TRY_TEST_B( IsEqual(sfy, -5.2264404));
   TRY_TEST_B( IsEqual(smz, -10.978190));
   TRY_TEST_B( IsEqual(efx, 0.0));
   TRY_TEST_B( IsEqual(efy, -2.273559));
   TRY_TEST_B( IsEqual(emz, 0.0));

   TRY_TEST_HR(presults->ComputeReactions(0, 0, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -5.2264404));
   TRY_TEST_B( IsEqual(mz, -10.978190));
   TRY_TEST_HR(presults->ComputeReactions(0, 8, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -2.273559));
   TRY_TEST_B( IsEqual(mz,  0.0));

   // get member end Deflections
   TRY_TEST_HR(presults->ComputeMemberDeflections(0, 1, &sdx, &sdy, &srz, &edx, &edy, &erz));
   TRY_TEST_B( IsEqual(sdx,   0.0) );
   TRY_TEST_B( IsEqual(sdy,   0.0));
   TRY_TEST_B( IsEqual(srz,   0.0));
   TRY_TEST_B( IsEqual(edx,   0.0));
   TRY_TEST_B( IsEqual(edy,   0.0));
   TRY_TEST_B( IsEqual(erz,   -2.0228794642857));

   // look at Deflections
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 10,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 15,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 2.14111));
   TRY_TEST_B( IsEqual(rz, 1.64335) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 12,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy,4.6499032));
   TRY_TEST_B( IsEqual(rz,0.4849981) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 20,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy,4.6499032));
   TRY_TEST_B( IsEqual(rz,0.4849981) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 25,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 3.61269996));
   TRY_TEST_B( IsEqual(rz,-1.37329101));
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 22,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz,-2.02287946));

   // next look at poi forces
   TRY_TEST_HR(presults->ComputePOIForces(0, 10, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  5.2264404296875));
   TRY_TEST_B( IsEqual(mz, 10.978190104167));
   TRY_TEST_HR(presults->ComputePOIForces(0, 10, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -5.2264404296875));
   TRY_TEST_B( IsEqual(mz,-10.978190104167));
   TRY_TEST_HR(presults->ComputePOIForces(0, 15, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  5.2264404296875));
   TRY_TEST_B( IsEqual(mz,  0.52530924479167));
   TRY_TEST_HR(presults->ComputePOIForces(0, 15, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -5.2264404296875));
   TRY_TEST_B( IsEqual(mz, -0.52530924479167));
   TRY_TEST_HR(presults->ComputePOIForces(0, 12, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  1.326440429));
   TRY_TEST_B( IsEqual(mz, -7.227571614));
   TRY_TEST_HR(presults->ComputePOIForces(0, 12, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -1.326440429));
   TRY_TEST_B( IsEqual(mz,  7.227571614));
   TRY_TEST_HR(presults->ComputePOIForces(0, 20, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  1.326440429));
   TRY_TEST_B( IsEqual(mz, -7.227571614));
   TRY_TEST_HR(presults->ComputePOIForces(0, 20, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -1.326440429));
   TRY_TEST_B( IsEqual(mz,  7.227571614));
   TRY_TEST_HR(presults->ComputePOIForces(0, 25, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -2.27355957));
   TRY_TEST_B( IsEqual(mz, -4.54711914));
   TRY_TEST_HR(presults->ComputePOIForces(0, 25, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  2.27355957));
   TRY_TEST_B( IsEqual(mz,  4.54711914));
   TRY_TEST_HR(presults->ComputePOIForces(0, 22, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -2.27355957));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 22, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  2.27355957));
   TRY_TEST_B( IsEqual(mz,  0.0));

   ReleaseModel(pmodel);
}


void CTestSimpleBeamWithDistributedLoad::Test2() 
{

/*////////////////////////////////////////////////////
                          
  three-span beam with trapezoidal load
  made up and verified using DrBeam

          1                       2                 3
  ========================================================
  ^      16             ^        14           ^     10   ^ 
  1                     2                     3          4

*/////////////////////////////////////////////////
   CComPtr<IFem2dModel> pmodel;
   pmodel = CreateModel();
   ATLASSERT(pmodel);

   // create joints
   CComPtr<IFem2dJointCollection> pJoints;
   TRY_TEST_HR(pmodel->get_Joints(&pJoints));

   CComPtr<IFem2dJoint> pJoint1,pJoint2,pJoint3,pJoint4;
   TRY_TEST_MC(pJoints->Create(1,  0.0,  0.0, &pJoint1));
   TRY_TEST_MC(pJoints->Create(2, 16.0,  0.0, &pJoint2));
   TRY_TEST_MC(pJoints->Create(3, 30.0,  0.0, &pJoint3));
   TRY_TEST_MC(pJoints->Create(4, 40.0,  0.0, &pJoint4));

   // boundary conditions
   TRY_TEST_MC(pJoint1->Support());
   TRY_TEST_MC(pJoint2->Support());
   TRY_TEST_MC(pJoint3->Support());
   TRY_TEST_MC(pJoint4->Support());
   TRY_TEST_MC(pJoint1->ReleaseDof(jrtMz));
   TRY_TEST_MC(pJoint2->ReleaseDof(jrtMz));
   TRY_TEST_MC(pJoint3->ReleaseDof(jrtMz));
   TRY_TEST_MC(pJoint4->ReleaseDof(jrtMz));

   // create members
   CComPtr<IFem2dMemberCollection> pMembers;
   TRY_TEST_HR(pmodel->get_Members(&pMembers));

   CComPtr<IFem2dMember> pMember1, pMember2, pMember3;
   TRY_TEST_MC(pMembers->Create(1,  1,  2, 3.0, 7.0, &pMember1));
   TRY_TEST_MC(pMembers->Create(2,  2,  3, 3.0, 7.0, &pMember2));
   TRY_TEST_MC(pMembers->Create(3,  3,  4, 3.0, 7.0, &pMember3));

   // create load case and apply Distributed load to members
   CComPtr<IFem2dLoadingCollection> pLoadings;
   TRY_TEST_HR(pmodel->get_Loadings(&pLoadings));
   CComPtr<IFem2dLoading> pLoading;
   TRY_TEST_LC(pLoadings->Create(0, &pLoading));
   CComPtr<IFem2dDistributedLoadCollection> pDistributedLoads;
   TRY_TEST_HR(pLoading->get_DistributedLoads(&pDistributedLoads));
   CComPtr<IFem2dDistributedLoad> pDistributedLoad1, pDistributedLoad2;
   TRY_TEST_LC(pDistributedLoads->Create(1, 1, loadDirFy, 4.0, -1.0, -18.0, -6.0, lotMember, &pDistributedLoad1));
   TRY_TEST_LC(pDistributedLoads->Create(2, 2, loadDirFy, 0.0,  6.0,  -6.0,  0.0, lotMember, &pDistributedLoad2));

   // put a point load at 4 into member 3
   CComPtr<IFem2dPointLoadCollection> pPointLoads;
   TRY_TEST_HR(pLoading->get_PointLoads(&pPointLoads));
   CComPtr<IFem2dPointLoad> pPointLoad;
   TRY_TEST_LC(pPointLoads->Create(0, 3, 4.0, 0.0, -21.0, 0.0, lotMember, &pPointLoad));

   // now let's add some POI's at 1/4 points in members 1 and 2
   CComPtr<IFem2dPOICollection> pPOIs;
   TRY_TEST_HR(pmodel->get_POIs(&pPOIs));

   CComPtr<IFem2dPOI> pPOI10,pPOI11,pPOI12,pPOI13, pPOI14;
   TRY_TEST_HR(pPOIs->Create(10,  1,   0.0,  &pPOI10));
   TRY_TEST_HR(pPOIs->Create(11,  1,  -0.25, &pPOI11));
   TRY_TEST_HR(pPOIs->Create(12,  1,  -0.5,  &pPOI12));
   TRY_TEST_HR(pPOIs->Create(13,  1,  -0.75, &pPOI13));
   TRY_TEST_HR(pPOIs->Create(14,  1,  -1.0,  &pPOI14));

   CComPtr<IFem2dPOI> pPOI20,pPOI21,pPOI22,pPOI23, pPOI24;
   TRY_TEST_HR(pPOIs->Create(20,  2,   0.0,  &pPOI20));
   TRY_TEST_HR(pPOIs->Create(21,  2,  -0.25, &pPOI21));
   TRY_TEST_HR(pPOIs->Create(22,  2,  -0.5,  &pPOI22));
   TRY_TEST_HR(pPOIs->Create(23,  2,  -0.75, &pPOI23));
   TRY_TEST_HR(pPOIs->Create(24,  2,  -1.0,  &pPOI24));

   // mid point of member 3
   CComPtr<IFem2dPOI> pPOI32;
   TRY_TEST_HR(pPOIs->Create(32,  3,  -0.5,  &pPOI32));

   // get results interface
   CComQIPtr<IFem2dModelResults> presults(pmodel);

   // get joint Deflections
   Float64 dx, dy, rz;
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 1, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, -183.75544) );
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 2, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 111.39659965) );
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 3, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, -35.60633839) );
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 4, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 25.003169) );

   // get member end forces
   Float64 sfx, sfy, smz, efx, efy, emz;
   TRY_TEST_HR(presults->ComputeMemberForces(0, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx, 0.0) );
   TRY_TEST_B( IsEqual(sfy, 49.8911273));
   TRY_TEST_B( IsEqual(smz, 0.0));
   TRY_TEST_B( IsEqual(efx, 0.0));
   TRY_TEST_B( IsEqual(efy, 94.1088726));
   TRY_TEST_B( IsEqual(emz, -209.741962955));
   TRY_TEST_HR(presults->ComputeMemberForces(0, 2, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,   0.0) );
   TRY_TEST_B( IsEqual(sfy,  32.871090969));
   TRY_TEST_B( IsEqual(smz, 209.74196295508));
   TRY_TEST_B( IsEqual(efx, 0.0));
   TRY_TEST_B( IsEqual(efy, -14.87109097));
   TRY_TEST_B( IsEqual(emz, 34.45331062));
   TRY_TEST_HR(presults->ComputeMemberForces(0, 3, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,   0.0) );
   TRY_TEST_B( IsEqual(sfy,   9.154668937));
   TRY_TEST_B( IsEqual(smz, -34.45331062));
   TRY_TEST_B( IsEqual(efx,   0.0));
   TRY_TEST_B( IsEqual(efy,  11.845331062));
   TRY_TEST_B( IsEqual(emz,   0.0));

   Float64 fx, fy, mz;
   TRY_TEST_HR(presults->ComputeReactions(0, 1, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   0.0));
   TRY_TEST_B( IsEqual(fy,  49.8911273));
   TRY_TEST_B( IsEqual(mz,   0.0));
   TRY_TEST_HR(presults->ComputeReactions(0, 2, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   0.0));
   TRY_TEST_B( IsEqual(fy, 126.9799636));
   TRY_TEST_B( IsEqual(mz,   0.0));
   TRY_TEST_HR(presults->ComputeReactions(0, 3, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -5.716422032));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputeReactions(0, 4, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   0.0));
   TRY_TEST_B( IsEqual(fy,  11.845331062380));
   TRY_TEST_B( IsEqual(mz,   0.0));

   // get member end Deflections
   Float64 sdx, sdy, srz, edx, edy, erz;
   TRY_TEST_HR(presults->ComputeMemberDeflections(0, 1, &sdx, &sdy, &srz, &edx, &edy, &erz));
   TRY_TEST_B( IsEqual(sdx,   0.0) );
   TRY_TEST_B( IsEqual(sdy,   0.0));
   TRY_TEST_B( IsEqual(srz,-183.755443));
   TRY_TEST_B( IsEqual(edx,   0.0));
   TRY_TEST_B( IsEqual(edy,   0.0));
   TRY_TEST_B( IsEqual(erz, 111.39659965327));

   TRY_TEST_HR(presults->ComputeMemberDeflections(0, 2, &sdx, &sdy, &srz, &edx, &edy, &erz));
   TRY_TEST_B( IsEqual(sdx,   0.0) );
   TRY_TEST_B( IsEqual(sdy,   0.0));
   TRY_TEST_B( IsEqual(srz, 111.39659965327));
   TRY_TEST_B( IsEqual(edx,   0.0));
   TRY_TEST_B( IsEqual(edy,   0.0));
   TRY_TEST_B( IsEqual(erz, -35.606338392287));

   TRY_TEST_HR(presults->ComputeMemberDeflections(0, 3, &sdx, &sdy, &srz, &edx, &edy, &erz));
   TRY_TEST_B( IsEqual(sdx,   0.0) );
   TRY_TEST_B( IsEqual(sdy,   0.0));
   TRY_TEST_B( IsEqual(srz, -35.606338392));
   TRY_TEST_B( IsEqual(edx,   0.0));
   TRY_TEST_B( IsEqual(edy,   0.0));
   TRY_TEST_B( IsEqual(erz,  25.0031692));

   // look at  poi Deflections
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 10,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, -183.75544268378) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 11,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,    0.0) );
   TRY_TEST_B( IsEqual(dy, -658.99719577846));
   TRY_TEST_B( IsEqual(rz, -126.73701146629) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 12,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, -888.05646562649));
   TRY_TEST_B( IsEqual(rz, 18.413520281436) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 13,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, -552.24940742318));
   TRY_TEST_B( IsEqual(rz, 134.36281922605) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 14,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0));
   TRY_TEST_B( IsEqual(rz, 111.39659965327) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 20,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0));
   TRY_TEST_B( IsEqual(rz, 111.39659965327) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 21,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 235.18567198256));
   TRY_TEST_B( IsEqual(rz, 30.056051941082) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 22,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 248.38371300830));
   TRY_TEST_B( IsEqual(rz, -18.010830621369) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 23,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,   0.0) );
   TRY_TEST_B( IsEqual(dy, 139.58792580370));
   TRY_TEST_B( IsEqual(rz, -39.820789105508) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 24,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, -35.606338392287));
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 32,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,   0.0) );
   TRY_TEST_B( IsEqual(dy, -89.761884485538));
   TRY_TEST_B( IsEqual(rz,   3.8507922990358) );

   // next look at poi forces
   TRY_TEST_HR(presults->ComputePOIForces(0, 10, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,-49.891127315308));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 11, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,    0.0));
   TRY_TEST_B( IsEqual(fy,  -49.891127315308));
   TRY_TEST_B( IsEqual(mz,  199.56450926123));
   TRY_TEST_HR(presults->ComputePOIForces(0, 12, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,    0.0));
   TRY_TEST_B( IsEqual(fy,   14.108872684692));
   TRY_TEST_B( IsEqual(mz,  265.79568518913));
   TRY_TEST_HR(presults->ComputePOIForces(0, 13, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,    0.0));
   TRY_TEST_B( IsEqual(fy,   62.108872684692));
   TRY_TEST_B( IsEqual(mz,  108.02686111703));
   TRY_TEST_HR(presults->ComputePOIForces(0, 14, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  94.108872684692));
   TRY_TEST_B( IsEqual(mz,-209.74196295508));
   TRY_TEST_HR(presults->ComputePOIForces(0, 14, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -94.108872684692));
   TRY_TEST_B( IsEqual(mz, 209.74196295508));
   TRY_TEST_HR(presults->ComputePOIForces(0, 20, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,-32.871090969920));
   TRY_TEST_B( IsEqual(mz,-209.74196295508));
   TRY_TEST_HR(presults->ComputePOIForces(0, 21, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   0.0));
   TRY_TEST_B( IsEqual(fy, -17.996090969920));
   TRY_TEST_B( IsEqual(mz, -124.29731122702));
   TRY_TEST_HR(presults->ComputePOIForces(0, 22, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -14.871090));
   TRY_TEST_B( IsEqual(mz, -69.644326));
   TRY_TEST_HR(presults->ComputePOIForces(0, 32, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, 11.845331));
   TRY_TEST_B( IsEqual(mz, 59.226655));

   ReleaseModel(pmodel);
}

void CTestSimpleBeamWithDistributedLoad::Test3() 
{

/*////////////////////////////////////////////////////
                     
  Like Test1, but shorter and with some curves                       

                     |||||||||| 
                  |||||||||||||
           ]      vvvvvvvvvvvvv          [
           ]=============================[  // fixed ends
           ]                             [

       L = 8           Mc = PL/4 = 8
       EA = 3.0        Dc = PL^3/48EI = 
       EI = 7.0
       a = 2.5
       b = 5.0
       Wa = 2
       Wb = -4

*/////////////////////////////////////////////////
   CComPtr<IFem2dModel> pmodel;
   pmodel=CreateModel();
   ATLASSERT(pmodel);

   // create joints
   CComPtr<IFem2dJointCollection> pJoints;
   TRY_TEST_HR(pmodel->get_Joints(&pJoints));

   CComPtr<IFem2dJoint> pJoint0,pJoint8;
   TRY_TEST_MC(pJoints->Create(0,  0.0,  0.0, &pJoint0));
   TRY_TEST_MC(pJoints->Create(8,  8.0,  0.0, &pJoint8));

   // boundary conditions
   TRY_TEST_MC(pJoint0->Support());
   TRY_TEST_MC(pJoint8->Support());

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

   // load with zero length
   TRY_TEST_LC(pDistributedLoads->Create(0, 1, loadDirFy, 2.5, 2.5, 0.0, 0.0, lotMember, &pDistributedLoad));

   // now let's add some POI's at 1/4 points in member 1
   CComPtr<IFem2dPOICollection> pPOIs;
   TRY_TEST_HR(pmodel->get_POIs(&pPOIs));

   CComPtr<IFem2dPOI> pPOI10,pPOI15,pPOI12;
   TRY_TEST_HR(pPOIs->Create(10,  1,  0.0, &pPOI10));
   TRY_TEST_HR(pPOIs->Create(15,  1,  -.25, &pPOI15));
   TRY_TEST_HR(pPOIs->Create(12,  1,  -0.5, &pPOI12));

   // get results interface
   CComQIPtr<IFem2dModelResults> presults(pmodel);

   Float64 fx, fy, mz;
   // should be zero since there are no forces
   TRY_TEST_HR(presults->ComputeReactions(0, 0, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));

   // now put values into the load and carry on with the test except swap end
   // and start values
   TRY_TEST_LC(pDistributedLoad->put_StartLocation(5.0));
   TRY_TEST_LC(pDistributedLoad->put_WStart(4.0));
   TRY_TEST_LC(pDistributedLoad->put_WEnd(2.0));

   // get joint Deflections
   Float64 dx, dy, rz;
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 0, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 8, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 0.0) );

   // get member end forces
   Float64 sfx, sfy, smz, efx, efy, emz;
   TRY_TEST_HR(presults->ComputeMemberForces(0, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx, 0.0) );
   TRY_TEST_B( IsEqual(sfy, -3.898925));
   TRY_TEST_B( IsEqual(smz, -7.438151));
   TRY_TEST_B( IsEqual(efx, 0.0));
   TRY_TEST_B( IsEqual(efy, -3.601074));
   TRY_TEST_B( IsEqual(emz,  7.080078));

   TRY_TEST_HR(presults->ComputeReactions(0, 0, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  -3.89892));
   TRY_TEST_B( IsEqual(mz,  -7.43815));
   TRY_TEST_HR(presults->ComputeReactions(0, 8, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  -3.601074));
   TRY_TEST_B( IsEqual(mz,   7.080078));

   // get member end Deflections
   Float64 sdx, sdy, srz, edx, edy, erz;
   TRY_TEST_HR(presults->ComputeMemberDeflections(0, 1, &sdx, &sdy, &srz, &edx, &edy, &erz));
   TRY_TEST_B( IsEqual(sdx,   0.0) );
   TRY_TEST_B( IsEqual(sdy,   0.0));
   TRY_TEST_B( IsEqual(srz,   0.0));
   TRY_TEST_B( IsEqual(edx,   0.0));
   TRY_TEST_B( IsEqual(edy,   0.0));
   TRY_TEST_B( IsEqual(erz,   0.0));

   // now let's add some POI's at 1/4 points of on second half
   // these results are calculated on the fly
   CComPtr<IFem2dPOI> pPOI20,pPOI25,pPOI22;
   TRY_TEST_HR(pPOIs->Create(20,  1,  4.0, &pPOI20));
   TRY_TEST_HR(pPOIs->Create(25,  1,  6.0, &pPOI25));
   TRY_TEST_HR(pPOIs->Create(22,  1,  8.0, &pPOI22));

   // look at Deflections
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 10,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 15,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 1.382533));
   TRY_TEST_B( IsEqual(rz, 1.011207) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 12,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy,  2.627023809));
   TRY_TEST_B( IsEqual(rz, -0.020721726) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 20,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy,  2.627023809));
   TRY_TEST_B( IsEqual(rz, -0.020721726) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 25,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy,  1.3369605));
   TRY_TEST_B( IsEqual(rz, -0.9940011) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 22,  lotMember, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 0.0));

   // next look at poi forces
   TRY_TEST_HR(presults->ComputePOIForces(0, 10, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  3.8989257));
   TRY_TEST_B( IsEqual(mz,  7.4381510));
   TRY_TEST_HR(presults->ComputePOIForces(0, 10, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -3.8989257));
   TRY_TEST_B( IsEqual(mz, -7.4381510));

   TRY_TEST_HR(presults->ComputePOIForces(0, 15, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  3.8989257));
   TRY_TEST_B( IsEqual(mz, -0.3597005));
   TRY_TEST_HR(presults->ComputePOIForces(0, 15, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -3.8989257));
   TRY_TEST_B( IsEqual(mz,  0.3597005));

   TRY_TEST_HR(presults->ComputePOIForces(0, 12, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,-0.00107422));
   TRY_TEST_B( IsEqual(mz,-5.457552));
   TRY_TEST_HR(presults->ComputePOIForces(0, 12, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, 0.00107422));
   TRY_TEST_B( IsEqual(mz, 5.457552));

   TRY_TEST_HR(presults->ComputePOIForces(0, 20, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,-0.00107422));
   TRY_TEST_B( IsEqual(mz,-5.457552));
   TRY_TEST_HR(presults->ComputePOIForces(0, 20, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, 0.00107422));
   TRY_TEST_B( IsEqual(mz, 5.457552));

   TRY_TEST_HR(presults->ComputePOIForces(0, 25, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,-3.601074));
   TRY_TEST_B( IsEqual(mz,-0.122070));
   TRY_TEST_HR(presults->ComputePOIForces(0, 25, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  3.601074));
   TRY_TEST_B( IsEqual(mz,  0.122070));

   TRY_TEST_HR(presults->ComputePOIForces(0, 22, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -3.601074));
   TRY_TEST_B( IsEqual(mz,  7.080078));
   TRY_TEST_HR(presults->ComputePOIForces(0, 22, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  3.601074));
   TRY_TEST_B( IsEqual(mz, -7.080078));

   ReleaseModel(pmodel);
}

