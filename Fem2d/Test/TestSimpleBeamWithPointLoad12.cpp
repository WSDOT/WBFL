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
// TestSimpleBeamWithPointLoad.cpp: implementation of the CTestSimpleBeamWithPointLoad class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestSimpleBeamWithPointLoad.h"
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


// had to break file into two parts due to compiler limit

void CTestSimpleBeamWithPointLoad::Test2()
{
// create a model
/*////////////////////////////////////////////////////

                         | P=4 at L/2
                         V
           0=============================0
           A                             O

       L = 8           Mc = PL/4 = 8
       EA = 3.0        Dc = PL^3/48EI = 
       EI = 7.0

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
   TRY_TEST_MC(pJoint0->ReleaseDof(jrtMz));
   TRY_TEST_MC(pJoint8->Support());
   TRY_TEST_MC(pJoint8->ReleaseDof(jrtMz));

   // create members
   CComPtr<IFem2dMemberCollection> pMembers;
   TRY_TEST_HR(pmodel->get_Members(&pMembers));

   CComPtr<IFem2dMember> pMember1;
   TRY_TEST_MC(pMembers->Create(1,  0,  8, 3.0, 7.0, &pMember1));

   // create load case and apply point load to joint
   CComPtr<IFem2dLoadingCollection> pLoadings;
   TRY_TEST_HR(pmodel->get_Loadings(&pLoadings));
   CComPtr<IFem2dLoading> pLoading;
   TRY_TEST_LC(pLoadings->Create(0, &pLoading));
   CComPtr<IFem2dPointLoadCollection> pPointLoads;
   TRY_TEST_HR(pLoading->get_PointLoads(&pPointLoads));

   CComPtr<IFem2dPointLoad> pPointLoad;
   TRY_TEST_LC(pPointLoads->Create(0, 1, 4.0, 0.0, -4.0, 0.0, lotGlobal, &pPointLoad));
   // use local member coord's
   TRY_TEST_LC(pPointLoad->put_Orientation(lotMember));

   // add some POI's at 1/4 points in member 1
   CComPtr<IFem2dPOICollection> pPOIs;
   TRY_TEST_HR(pmodel->get_POIs(&pPOIs));

   CComPtr<IFem2dPOI> pPOI10,pPOI15,pPOI12;
   TRY_TEST_HR(pPOIs->Create(10,  1,  0.0, &pPOI10));
   TRY_TEST_HR(pPOIs->Create(15,  1,  -.25, &pPOI15));
   TRY_TEST_HR(pPOIs->Create(12,  1,  -0.5, &pPOI12));
   CComPtr<IFem2dPOI> pPOI20,pPOI25,pPOI22;
   TRY_TEST_HR(pPOIs->Create(20,  1,  4.0, &pPOI20));
   TRY_TEST_HR(pPOIs->Create(25,  1,  6.0, &pPOI25));
   TRY_TEST_HR(pPOIs->Create(22,  1,  8.0, &pPOI22));

//////////////////////////////////////////////////////////////////////////////////
// ================================================================================
// rotate the model 135 degrees clockwise
// since orientation is local, don't need to change to be normal to rotated structure
   TRY_TEST_MC(pJoint8->put_X(-5.6568542));
   TRY_TEST_MC(pJoint8->put_Y(5.6568542));

   Float64 l;
   pMember1->get_Length(&l);
   TRY_TEST_B(IsEqual(l, 8.0));

   // get results interface
   CComQIPtr<IFem2dModelResults> presults(pmodel);

   Float64 dx, dy, rz;
   // get joint Deflections
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 0, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) ); 
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, -2.2857142857143) );
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 8, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 2.2857142857143) );

   // get member end forces
   Float64 sfx, sfy, smz, efx, efy, emz;
   TRY_TEST_HR(presults->ComputeMemberForces(0, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx, 0.0) );
   TRY_TEST_B( IsEqual(sfy, 2.0));
   TRY_TEST_B( IsEqual(smz, 0.0));
   TRY_TEST_B( IsEqual(efx, 0.0));
   TRY_TEST_B( IsEqual(efy, 2.0));
   TRY_TEST_B( IsEqual(emz, 0.0));

   Float64 fx, fy, mz;
   TRY_TEST_HR(presults->ComputeReactions(0, 0, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  -1.41421356));
   TRY_TEST_B( IsEqual(fy,  -1.41421356));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputeReactions(0, 8, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  -1.41421356));
   TRY_TEST_B( IsEqual(fy,  -1.41421356));
   TRY_TEST_B( IsEqual(mz,  0.0));

   // get merber end forces
   Float64 sdx, sdy, srz, edx, edy, erz;
   TRY_TEST_HR(presults->ComputeMemberDeflections(0, 1, &sdx, &sdy, &srz, &edx, &edy, &erz));
   TRY_TEST_B( IsEqual(sdx,   0.0) );
   TRY_TEST_B( IsEqual(sdy,   0.0));
   TRY_TEST_B( IsEqual(srz, -2.2857142857143));
   TRY_TEST_B( IsEqual(edx,   0.0));
   TRY_TEST_B( IsEqual(edy, 0.0));
   TRY_TEST_B( IsEqual(erz,  2.2857142857143));

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
   TRY_TEST_B( IsEqual(dx, 2.9631141) );
   TRY_TEST_B( IsEqual(dy, 2.9631141));
   TRY_TEST_B( IsEqual(rz, -1.71428) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 12,  lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 4.3099842) );
   TRY_TEST_B( IsEqual(dy, 4.3099842));
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 20,  lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 4.3099842) );
   TRY_TEST_B( IsEqual(dy, 4.3099842));
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 25,  lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 2.9631141) );
   TRY_TEST_B( IsEqual(dy, 2.9631141));
   TRY_TEST_B( IsEqual(rz, 1.71428) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 22,  lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 2.2857142857143) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 10,  lotGlobalProjected, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, -2.2857142857143) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 15,  lotGlobalProjected, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 2.9631141) );
   TRY_TEST_B( IsEqual(dy, 2.9631141));
   TRY_TEST_B( IsEqual(rz, -1.71428) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 12,  lotGlobalProjected, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 4.3099842) );
   TRY_TEST_B( IsEqual(dy, 4.3099842));
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 20,  lotGlobalProjected, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 4.3099842) );
   TRY_TEST_B( IsEqual(dy, 4.3099842));
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 25,  lotGlobalProjected, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 2.9631141) );
   TRY_TEST_B( IsEqual(dy, 2.9631141));
   TRY_TEST_B( IsEqual(rz, 1.71428) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 22,  lotGlobalProjected, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 2.2857142857143) );

   // next look at poi forces at both faces and orientations
   TRY_TEST_HR(presults->ComputePOIForces(0, 10, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  1.41421355));
   TRY_TEST_B( IsEqual(fy,  1.41421355));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 10, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx, -1.41421355));
   TRY_TEST_B( IsEqual(fy, -1.41421355));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 10, mftLeft, lotGlobalProjected, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  1.41421355));
   TRY_TEST_B( IsEqual(fy,  1.41421355));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 10, mftRight, lotGlobalProjected, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx, -1.41421355));
   TRY_TEST_B( IsEqual(fy, -1.41421355));
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
   TRY_TEST_B( IsEqual(fy,   1.41421355));
   TRY_TEST_B( IsEqual(mz,   4.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 15, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  -1.41421355));
   TRY_TEST_B( IsEqual(fy,  -1.41421355));
   TRY_TEST_B( IsEqual(mz,  -4.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 15, mftLeft, lotGlobalProjected, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   1.41421355));
   TRY_TEST_B( IsEqual(fy,   1.41421355));
   TRY_TEST_B( IsEqual(mz,   4.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 15, mftRight, lotGlobalProjected, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  -1.41421355));
   TRY_TEST_B( IsEqual(fy,  -1.41421355));
   TRY_TEST_B( IsEqual(mz,  -4.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 15, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   0.0));
   TRY_TEST_B( IsEqual(fy,  -2.0));
   TRY_TEST_B( IsEqual(mz,   4.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 15, mftRight, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  2.0));
   TRY_TEST_B( IsEqual(mz, -4.0));

   TRY_TEST_HR(presults->ComputePOIForces(0, 12, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   1.41421355));
   TRY_TEST_B( IsEqual(fy,   1.41421355));
   TRY_TEST_B( IsEqual(mz,   8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 12, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  -1.41421355));
   TRY_TEST_B( IsEqual(fy,  -1.41421355));
   TRY_TEST_B( IsEqual(mz,  -8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 12, mftLeft, lotGlobalProjected, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   1.41421355));
   TRY_TEST_B( IsEqual(fy,   1.41421355));
   TRY_TEST_B( IsEqual(mz,   8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 12, mftRight, lotGlobalProjected, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  -1.41421355));
   TRY_TEST_B( IsEqual(fy,  -1.41421355));
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
   TRY_TEST_B( IsEqual(fx,  1.41421355));
   TRY_TEST_B( IsEqual(fy,  1.41421355));
   TRY_TEST_B( IsEqual(mz,  8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 20, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   1.41421355));
   TRY_TEST_B( IsEqual(fy,   1.41421355));
   TRY_TEST_B( IsEqual(mz,  -8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 20, mftLeft, lotGlobalProjected, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  1.41421355));
   TRY_TEST_B( IsEqual(fy,  1.41421355));
   TRY_TEST_B( IsEqual(mz,  8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 20, mftRight, lotGlobalProjected, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   1.41421355));
   TRY_TEST_B( IsEqual(fy,   1.41421355));
   TRY_TEST_B( IsEqual(mz,  -8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 20, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -2.0));
   TRY_TEST_B( IsEqual(mz,  8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 20, mftRight, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   0.0));
   TRY_TEST_B( IsEqual(fy,  -2.0));
   TRY_TEST_B( IsEqual(mz,  -8.0));

   TRY_TEST_HR(presults->ComputePOIForces(0, 25, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  -1.41421355));
   TRY_TEST_B( IsEqual(fy,  -1.41421355));
   TRY_TEST_B( IsEqual(mz,   4.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 25, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   1.41421355));
   TRY_TEST_B( IsEqual(fy,   1.41421355));
   TRY_TEST_B( IsEqual(mz,  -4.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 25, mftLeft, lotGlobalProjected, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  -1.41421355));
   TRY_TEST_B( IsEqual(fy,  -1.41421355));
   TRY_TEST_B( IsEqual(mz,   4.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 25, mftRight, lotGlobalProjected, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   1.41421355));
   TRY_TEST_B( IsEqual(fy,   1.41421355));
   TRY_TEST_B( IsEqual(mz,  -4.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 25, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  2.0));
   TRY_TEST_B( IsEqual(mz,  4.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 25, mftRight, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -2.0));
   TRY_TEST_B( IsEqual(mz, -4.0));

//////////////////////////////////////////////////////////////////////////////////
// ================================================================================
// Rotate the model 225 degrees clockwise
   TRY_TEST_HR(pJoint8->put_X(-5.6568542));
   TRY_TEST_MC(pJoint8->put_Y(-5.6568542));

   pMember1->get_Length(&l);
   TRY_TEST_B(IsEqual(l, 8.0));


   // get joint Deflections
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 0, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, -2.2857142857143) );
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
   TRY_TEST_B( IsEqual(efy, 2.0));
   TRY_TEST_B( IsEqual(emz, 0.0));

   TRY_TEST_HR(presults->ComputeReactions(0, 0, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   1.41421356));
   TRY_TEST_B( IsEqual(fy,  -1.41421356));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputeReactions(0, 8, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   1.41421356));
   TRY_TEST_B( IsEqual(fy,  -1.41421356));
   TRY_TEST_B( IsEqual(mz,  0.0));

   // get merber end forces
   TRY_TEST_HR(presults->ComputeMemberDeflections(0, 1, &sdx, &sdy, &srz, &edx, &edy, &erz));
   TRY_TEST_B( IsEqual(sdx,   0.0) );
   TRY_TEST_B( IsEqual(sdy,   0.0));
   TRY_TEST_B( IsEqual(srz,  -2.2857142857143));
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
   TRY_TEST_B( IsEqual(dx,-2.9631141) );
   TRY_TEST_B( IsEqual(dy, 2.9631141));
   TRY_TEST_B( IsEqual(rz, -1.71428) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 12,  lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,-4.3099842) );
   TRY_TEST_B( IsEqual(dy, 4.3099842));
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 20,  lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,-4.3099842) );
   TRY_TEST_B( IsEqual(dy, 4.3099842));
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 25,  lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,-2.9631141) );
   TRY_TEST_B( IsEqual(dy, 2.9631141));
   TRY_TEST_B( IsEqual(rz, 1.71428) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 22,  lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 2.2857142857143) );

   TRY_TEST_HR(presults->ComputePOIDeflections(0, 10,  lotGlobalProjected, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, -2.2857142857143) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 15,  lotGlobalProjected, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,-2.9631141) );
   TRY_TEST_B( IsEqual(dy, 2.9631141));
   TRY_TEST_B( IsEqual(rz, -1.71428) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 12,  lotGlobalProjected, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,-4.3099842) );
   TRY_TEST_B( IsEqual(dy, 4.3099842));
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 20,  lotGlobalProjected, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,-4.3099842) );
   TRY_TEST_B( IsEqual(dy, 4.3099842));
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 25,  lotGlobalProjected, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,-2.9631141) );
   TRY_TEST_B( IsEqual(dy, 2.9631141));
   TRY_TEST_B( IsEqual(rz, 1.71428) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 22,  lotGlobalProjected, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 2.2857142857143) );

   // next look at poi forces at both faces and orientations
   TRY_TEST_HR(presults->ComputePOIForces(0, 10, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx, -1.41421355));
   TRY_TEST_B( IsEqual(fy,  1.41421355));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 10, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  1.41421355));
   TRY_TEST_B( IsEqual(fy, -1.41421355));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 10, mftLeft, lotGlobalProjected, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx, -1.41421355));
   TRY_TEST_B( IsEqual(fy,  1.41421355));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 10, mftRight, lotGlobalProjected, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  1.41421355));
   TRY_TEST_B( IsEqual(fy, -1.41421355));
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
   TRY_TEST_B( IsEqual(fx,  -1.41421355));
   TRY_TEST_B( IsEqual(fy,   1.41421355));
   TRY_TEST_B( IsEqual(mz,   4.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 15, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   1.41421355));
   TRY_TEST_B( IsEqual(fy,  -1.41421355));
   TRY_TEST_B( IsEqual(mz,  -4.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 15, mftLeft, lotGlobalProjected, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  -1.41421355));
   TRY_TEST_B( IsEqual(fy,   1.41421355));
   TRY_TEST_B( IsEqual(mz,   4.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 15, mftRight, lotGlobalProjected, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   1.41421355));
   TRY_TEST_B( IsEqual(fy,  -1.41421355));
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
   TRY_TEST_B( IsEqual(fx,  -1.41421355));
   TRY_TEST_B( IsEqual(fy,   1.41421355));
   TRY_TEST_B( IsEqual(mz,   8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 12, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   1.41421355));
   TRY_TEST_B( IsEqual(fy,  -1.41421355));
   TRY_TEST_B( IsEqual(mz,  -8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 12, mftLeft, lotGlobalProjected, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  -1.41421355));
   TRY_TEST_B( IsEqual(fy,   1.41421355));
   TRY_TEST_B( IsEqual(mz,   8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 12, mftRight, lotGlobalProjected, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   1.41421355));
   TRY_TEST_B( IsEqual(fy,  -1.41421355));
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
   TRY_TEST_B( IsEqual(fx,  -1.41421355));
   TRY_TEST_B( IsEqual(fy,   1.41421355));
   TRY_TEST_B( IsEqual(mz,  -8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 20, mftLeft, lotGlobalProjected, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx, -1.41421355));
   TRY_TEST_B( IsEqual(fy,  1.41421355));
   TRY_TEST_B( IsEqual(mz,  8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 20, mftRight, lotGlobalProjected, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  -1.41421355));
   TRY_TEST_B( IsEqual(fy,   1.41421355));
   TRY_TEST_B( IsEqual(mz,  -8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 20, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -2.0));
   TRY_TEST_B( IsEqual(mz,  8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 20, mftRight, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   0.0));
   TRY_TEST_B( IsEqual(fy,  -2.0));
   TRY_TEST_B( IsEqual(mz,  -8.0));

   TRY_TEST_HR(presults->ComputePOIForces(0, 25, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   1.41421355));
   TRY_TEST_B( IsEqual(fy,  -1.41421355));
   TRY_TEST_B( IsEqual(mz,   4.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 25, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  -1.41421355));
   TRY_TEST_B( IsEqual(fy,   1.41421355));
   TRY_TEST_B( IsEqual(mz,  -4.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 25, mftLeft, lotGlobalProjected, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   1.41421355));
   TRY_TEST_B( IsEqual(fy,  -1.41421355));
   TRY_TEST_B( IsEqual(mz,   4.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 25, mftRight, lotGlobalProjected, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  -1.41421355));
   TRY_TEST_B( IsEqual(fy,   1.41421355));
   TRY_TEST_B( IsEqual(mz,  -4.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 25, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  2.0));
   TRY_TEST_B( IsEqual(mz,  4.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 25, mftRight, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   0.0));
   TRY_TEST_B( IsEqual(fy,  -2.0));
   TRY_TEST_B( IsEqual(mz,  -4.0));

//////////////////////////////////////////////////////////////////////////////////
// ================================================================================
// Rotate the model -45 degrees clockwise
   TRY_TEST_MC(pJoint8->put_X(5.6568542));
   TRY_TEST_HR(pJoint8->put_Y(-5.6568542));

   pMember1->get_Length(&l);
   TRY_TEST_B(IsEqual(l, 8.0));


   // get joint Deflections
   TRY_TEST_HR(presults->ComputeJointDeflections(0, 0, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, -2.2857142857143) );
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
   TRY_TEST_B( IsEqual(efy, 2.0));
   TRY_TEST_B( IsEqual(emz, 0.0));

   TRY_TEST_HR(presults->ComputeReactions(0, 0, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  1.41421356));
   TRY_TEST_B( IsEqual(fy,  1.41421356));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputeReactions(0, 8, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  1.41421356));
   TRY_TEST_B( IsEqual(fy,  1.41421356));
   TRY_TEST_B( IsEqual(mz,  0.0));

   // get merber end forces
   TRY_TEST_HR(presults->ComputeMemberDeflections(0, 1, &sdx, &sdy, &srz, &edx, &edy, &erz));
   TRY_TEST_B( IsEqual(sdx,   0.0) );
   TRY_TEST_B( IsEqual(sdy,   0.0));
   TRY_TEST_B( IsEqual(srz,  -2.2857142857143));
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
   TRY_TEST_B( IsEqual(dx,-2.9631141) );
   TRY_TEST_B( IsEqual(dy,-2.9631141));
   TRY_TEST_B( IsEqual(rz, -1.71428) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 12,  lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,-4.3099842) );
   TRY_TEST_B( IsEqual(dy,-4.3099842));
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 20,  lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,-4.3099842) );
   TRY_TEST_B( IsEqual(dy,-4.3099842));
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 25,  lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,-2.9631141) );
   TRY_TEST_B( IsEqual(dy,-2.9631141));
   TRY_TEST_B( IsEqual(rz, 1.71428) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 22,  lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 2.2857142857143) );

   TRY_TEST_HR(presults->ComputePOIDeflections(0, 10,  lotGlobalProjected, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, -2.2857142857143) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 15,  lotGlobalProjected, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,-2.9631141) );
   TRY_TEST_B( IsEqual(dy,-2.9631141));
   TRY_TEST_B( IsEqual(rz, -1.71428) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 12,  lotGlobalProjected, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,-4.3099842) );
   TRY_TEST_B( IsEqual(dy,-4.3099842));
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 20,  lotGlobalProjected, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,-4.3099842) );
   TRY_TEST_B( IsEqual(dy,-4.3099842));
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 25,  lotGlobalProjected, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,-2.9631141) );
   TRY_TEST_B( IsEqual(dy,-2.9631141));
   TRY_TEST_B( IsEqual(rz, 1.71428) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 22,  lotGlobalProjected, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 2.2857142857143) );

   // next look at poi forces at both faces and orientations
   TRY_TEST_HR(presults->ComputePOIForces(0, 10, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx, -1.41421355));
   TRY_TEST_B( IsEqual(fy, -1.41421355));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 10, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  1.41421355));
   TRY_TEST_B( IsEqual(fy,  1.41421355));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 10, mftLeft, lotGlobalProjected, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx, -1.41421355));
   TRY_TEST_B( IsEqual(fy, -1.41421355));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 10, mftRight, lotGlobalProjected, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  1.41421355));
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
   TRY_TEST_B( IsEqual(fx, -1.41421355));
   TRY_TEST_B( IsEqual(fy, -1.41421355));
   TRY_TEST_B( IsEqual(mz,  4.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 15, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  1.41421355));
   TRY_TEST_B( IsEqual(fy,  1.41421355));
   TRY_TEST_B( IsEqual(mz, -4.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 15, mftLeft, lotGlobalProjected, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx, -1.41421355));
   TRY_TEST_B( IsEqual(fy, -1.41421355));
   TRY_TEST_B( IsEqual(mz,  4.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 15, mftRight, lotGlobalProjected, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  1.41421355));
   TRY_TEST_B( IsEqual(fy,  1.41421355));
   TRY_TEST_B( IsEqual(mz, -4.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 15, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -2.0));
   TRY_TEST_B( IsEqual(mz,  4.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 15, mftRight, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  2.0));
   TRY_TEST_B( IsEqual(mz, -4.0));

   TRY_TEST_HR(presults->ComputePOIForces(0, 12, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  -1.41421355));
   TRY_TEST_B( IsEqual(fy,  -1.41421355));
   TRY_TEST_B( IsEqual(mz,   8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 12, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   1.41421355));
   TRY_TEST_B( IsEqual(fy,   1.41421355));
   TRY_TEST_B( IsEqual(mz,  -8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 12, mftLeft, lotGlobalProjected, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  -1.41421355));
   TRY_TEST_B( IsEqual(fy,  -1.41421355));
   TRY_TEST_B( IsEqual(mz,   8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 12, mftRight, lotGlobalProjected, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   1.41421355));
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
   TRY_TEST_B( IsEqual(fy, -1.41421355));
   TRY_TEST_B( IsEqual(mz,  8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 20, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  -1.41421355));
   TRY_TEST_B( IsEqual(fy,  -1.41421355));
   TRY_TEST_B( IsEqual(mz,  -8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 20, mftLeft, lotGlobalProjected, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx, -1.41421355));
   TRY_TEST_B( IsEqual(fy, -1.41421355));
   TRY_TEST_B( IsEqual(mz,  8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 20, mftRight, lotGlobalProjected, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  -1.41421355));
   TRY_TEST_B( IsEqual(fy,  -1.41421355));
   TRY_TEST_B( IsEqual(mz,  -8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 20, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -2.0));
   TRY_TEST_B( IsEqual(mz,  8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 20, mftRight, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   0.0));
   TRY_TEST_B( IsEqual(fy,  -2.0));
   TRY_TEST_B( IsEqual(mz,  -8.0));

   TRY_TEST_HR(presults->ComputePOIForces(0, 25, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   1.41421355));
   TRY_TEST_B( IsEqual(fy,   1.41421355));
   TRY_TEST_B( IsEqual(mz,   4.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 25, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  -1.41421355));
   TRY_TEST_B( IsEqual(fy,  -1.41421355));
   TRY_TEST_B( IsEqual(mz,  -4.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 25, mftLeft, lotGlobalProjected, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   1.41421355));
   TRY_TEST_B( IsEqual(fy,   1.41421355));
   TRY_TEST_B( IsEqual(mz,   4.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 25, mftRight, lotGlobalProjected, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  -1.41421355));
   TRY_TEST_B( IsEqual(fy,  -1.41421355));
   TRY_TEST_B( IsEqual(mz,  -4.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 25, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  2.0));
   TRY_TEST_B( IsEqual(mz,  4.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 25, mftRight, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -2.0));
   TRY_TEST_B( IsEqual(mz, -4.0));

   ReleaseModel(pmodel);
}


