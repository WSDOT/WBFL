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
// TestSimpleBeamWithPointLoad.cpp: implementation of the CTestSimpleBeamWithPointLoad class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestSimpleBeamWithPointLoad.h"
#include <MathEx.h>
#include <iostream> 

#include <WBFLCore.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CTestSimpleBeamWithPointLoad::CTestSimpleBeamWithPointLoad()
{

}

CTestSimpleBeamWithPointLoad::~CTestSimpleBeamWithPointLoad()
{

}
void CTestSimpleBeamWithPointLoad::Test()
{
   Test1(); 
   Test2();
}

void CTestSimpleBeamWithPointLoad::Test1()
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
   pmodel= CreateModel();
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
   TRY_TEST_MC(pJoint8->ReleaseDof(jrtFx));
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

   // now let's add some POI's at 1/4 points in member 1
   // these results are pre-calculated
   CComPtr<IFem2dPOICollection> pPOIs;
   TRY_TEST_HR(pmodel->get_POIs(&pPOIs));

   CComPtr<IFem2dPOI> pPOI10,pPOI15,pPOI12;
   TRY_TEST_HR(pPOIs->Create(10,  1,  0.0, &pPOI10));
   TRY_TEST_HR(pPOIs->Create(15,  1,  -.25, &pPOI15));
   TRY_TEST_HR(pPOIs->Create(12,  1,  -0.5, &pPOI12));

   // set scope to release file after save
   {    
      // save model off to a file
      CComPtr<IStructuredSave2> psave;
      TRY_TEST_HR(psave.CoCreateInstance(CLSID_StructuredSave2));
      ATLASSERT(psave);

      TRY_TEST_HR(psave->Open(CComBSTR("TestSimpleBeamWithPointLoad.xml")));

      IStructuredStorage2* pstor;
      TRY_TEST_HR(pmodel->QueryInterface(&pstor));
      TRY_TEST_HR(pstor->Save(psave));
      TRY_TEST_HR(psave->Close());
      pstor->Release();
   }


   // get results interface
   CComQIPtr<IFem2dModelResults>   presults(pmodel);
   CComQIPtr<IFem2dModelResultsEx> presultsex(pmodel);

   // get joint Deflections
   Float64 dx, dy, rz;
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

   TRY_TEST_HR(presultsex->ComputeMemberForcesEx(0, 1, lotGlobal, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx, 0.0) );
   TRY_TEST_B( IsEqual(sfy, 2.0));
   TRY_TEST_B( IsEqual(smz, 0.0));
   TRY_TEST_B( IsEqual(efx, 0.0));
   TRY_TEST_B( IsEqual(efy, 2.0));
   TRY_TEST_B( IsEqual(emz, 0.0));

   TRY_TEST_HR(presultsex->ComputeMemberForcesEx(0, 1, lotMember, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx, 0.0) );
   TRY_TEST_B( IsEqual(sfy, 2.0));
   TRY_TEST_B( IsEqual(smz, 0.0));
   TRY_TEST_B( IsEqual(efx, 0.0));
   TRY_TEST_B( IsEqual(efy, 2.0));
   TRY_TEST_B( IsEqual(emz, 0.0));

   Float64 fx, fy, mz;
   TRY_TEST_HR(presults->ComputeReactions(0, 0, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  2.0));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputeReactions(0, 8, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  2.0));
   TRY_TEST_B( IsEqual(mz,  0.0));

   // get member end Deflections
   Float64 sdx, sdy, srz, edx, edy, erz;
   TRY_TEST_HR(presults->ComputeMemberDeflections(0, 1, &sdx, &sdy, &srz, &edx, &edy, &erz));
   TRY_TEST_B( IsEqual(sdx,   0.0) );
   TRY_TEST_B( IsEqual(sdy,   0.0));
   TRY_TEST_B( IsEqual(srz, -2.2857142857143));
   TRY_TEST_B( IsEqual(edx,   0.0));
   TRY_TEST_B( IsEqual(edy,   0.0));
   TRY_TEST_B( IsEqual(erz,   2.2857142857143));

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

   TRY_TEST_HR(presults->ComputePOIDeflections(0, 10, lotGlobalProjected, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, -2.2857142857143) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 15, lotGlobalProjected,  &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, -4.1904761904762));
   TRY_TEST_B( IsEqual(rz, -1.71428) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 12, lotGlobalProjected,  &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, -6.0952380952381));
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 20, lotGlobalProjected,  &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, -6.0952380952381));
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 25, lotGlobalProjected,  &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, -4.1904761904762));
   TRY_TEST_B( IsEqual(rz, 1.71428) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 22, lotGlobalProjected,  &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 2.2857142857143) );

   // next look at poi forces at both faces and orientations
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
   TRY_TEST_B( IsEqual(fy, -2.0));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 10, mftRight, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  2.0));
   TRY_TEST_B( IsEqual(mz,  0.0));

   TRY_TEST_HR(presults->ComputePOIForces(0, 15, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -2.0));
   TRY_TEST_B( IsEqual(mz,  4.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 15, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  2.0));
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
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -2.0));
   TRY_TEST_B( IsEqual(mz,  8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 12, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -2.0));
   TRY_TEST_B( IsEqual(mz, -8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 12, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -2.0));
   TRY_TEST_B( IsEqual(mz,  8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 12, mftRight, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -2.0));
   TRY_TEST_B( IsEqual(mz, -8.0));

   TRY_TEST_HR(presults->ComputePOIForces(0, 12, mftLeft, lotGlobalProjected, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -2.0));
   TRY_TEST_B( IsEqual(mz,  8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 12, mftRight, lotGlobalProjected, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -2.0));
   TRY_TEST_B( IsEqual(mz, -8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 12, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -2.0));
   TRY_TEST_B( IsEqual(mz,  8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 12, mftRight, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -2.0));
   TRY_TEST_B( IsEqual(mz, -8.0));


   TRY_TEST_HR(presults->ComputePOIForces(0, 20, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -2.0));
   TRY_TEST_B( IsEqual(mz,  8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 20, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -2.0));
   TRY_TEST_B( IsEqual(mz, -8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 20, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -2.0));
   TRY_TEST_B( IsEqual(mz,  8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 20, mftRight, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -2.0));
   TRY_TEST_B( IsEqual(mz, -8.0));

   TRY_TEST_HR(presults->ComputePOIForces(0, 25, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  2.0));
   TRY_TEST_B( IsEqual(mz,  4.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 25, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy, -2.0));
   TRY_TEST_B( IsEqual(mz, -4.0));
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
// add a new load case with a horizontal load at the middle
   // create load case and apply point load with magnitude of 2.0 to joint
   CComPtr<IFem2dLoading> pLoading2;
   TRY_TEST_LC(pLoadings->Create(2, &pLoading2));
   CComPtr<IFem2dPointLoadCollection> pPointLoads2;
   TRY_TEST_HR(pLoading2->get_PointLoads(&pPointLoads2));

   CComPtr<IFem2dPointLoad> pPointLoad2;
   TRY_TEST_LC(pPointLoads2->Create(0, 1, 4.0, 2.0, 0.0, 0.0, lotGlobal, &pPointLoad2));

   // get joint Deflections
   TRY_TEST_HR(presults->ComputeJointDeflections(2, 0, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
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
   TRY_TEST_B( IsEqual(efx, 0.0));
   TRY_TEST_B( IsEqual(efy, 0.0));
   TRY_TEST_B( IsEqual(emz, 0.0));

   TRY_TEST_HR(presultsex->ComputeMemberForcesEx(2, 1, lotGlobal, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,-2.0) );
   TRY_TEST_B( IsEqual(sfy, 0.0));
   TRY_TEST_B( IsEqual(smz, 0.0));
   TRY_TEST_B( IsEqual(efx, 0.0));
   TRY_TEST_B( IsEqual(efy, 0.0));
   TRY_TEST_B( IsEqual(emz, 0.0));

   TRY_TEST_HR(presultsex->ComputeMemberForcesEx(2, 1, lotMember, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,-2.0) );
   TRY_TEST_B( IsEqual(sfy, 0.0));
   TRY_TEST_B( IsEqual(smz, 0.0));
   TRY_TEST_B( IsEqual(efx, 0.0));
   TRY_TEST_B( IsEqual(efy, 0.0));
   TRY_TEST_B( IsEqual(emz, 0.0));

   TRY_TEST_HR(presults->ComputeReactions(2, 0, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx, -2.0));
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

   // At POI's
   // look at Deflections
   TRY_TEST_HR(presults->ComputePOIDeflections(2, 10, lotMember,  &dx, &dy, &rz));
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
   TRY_TEST_HR(presults->ComputePOIDeflections(2, 20, lotMember,  &dx, &dy, &rz));
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

   TRY_TEST_HR(presults->ComputePOIDeflections(2, 10,  lotGlobalProjected, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDeflections(2, 15,  lotGlobalProjected, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 1.333333) );
   TRY_TEST_B( IsEqual(dy, 0.0));
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDeflections(2, 12,  lotGlobalProjected, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 2.6666667) );
   TRY_TEST_B( IsEqual(dy, 0.0));
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDeflections(2, 20,  lotGlobalProjected, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 2.6666667) );
   TRY_TEST_B( IsEqual(dy, 0.0));
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDeflections(2, 25,  lotGlobalProjected, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 2.6666667) );
   TRY_TEST_B( IsEqual(dy, 0.0));
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDeflections(2, 22,  lotGlobalProjected, &dx, &dy, &rz));
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
   TRY_TEST_HR(presults->ComputePOIForces(2, 10, mftLeft, lotGlobalProjected, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  2.0));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(2, 10, mftRight, lotGlobalProjected, &fx, &fy, &mz));
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
   TRY_TEST_HR(presults->ComputePOIForces(2, 15, mftLeft, lotGlobalProjected, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  2.0));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(2, 15, mftRight, lotGlobalProjected, &fx, &fy, &mz));
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
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(2, 12, mftLeft, lotGlobalProjected, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  2.0));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(2, 12, mftRight, lotGlobalProjected, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(2, 12, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  2.0));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(2, 12, mftRight, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));

   TRY_TEST_HR(presults->ComputePOIForces(2, 20, mftLeft, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  2.0));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(2, 20, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(2, 20, mftLeft, lotGlobalProjected, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  2.0));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(2, 20, mftRight, lotGlobalProjected, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(2, 20, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  2.0));
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
   TRY_TEST_HR(presults->ComputePOIForces(2, 25, mftLeft, lotGlobalProjected, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.0));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(2, 25, mftRight, lotGlobalProjected, &fx, &fy, &mz));
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
   TRY_TEST_MC(pJoint8->put_X(5.6568542));
   TRY_TEST_MC(pJoint8->put_Y(5.6568542));

   // don't allow end joint to translate
   TRY_TEST_MC(pJoint8->Support());
   TRY_TEST_MC(pJoint8->ReleaseDof(jrtMz));

   Float64 l;
   pMember1->get_Length(&l);
   TRY_TEST_B(IsEqual(l, 8.0));

   // change orientation of point load to be normal to rotated structure
   TRY_TEST_LC(pPointLoad->put_Fx(2.8284271));
   TRY_TEST_LC(pPointLoad->put_Fy(-2.8284271));

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

   TRY_TEST_HR(presultsex->ComputeMemberForcesEx(0, 1, lotGlobal, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx,  -1.41421356));
   TRY_TEST_B( IsEqual(sfy,  1.41421356));
   TRY_TEST_B( IsEqual(smz,  0.0));
   TRY_TEST_B( IsEqual(efx,  -1.41421356));
   TRY_TEST_B( IsEqual(efy,  1.41421356));
   TRY_TEST_B( IsEqual(emz,  0.0));

   TRY_TEST_HR(presultsex->ComputeMemberForcesEx(0, 1, lotMember, &sfx, &sfy, &smz, &efx, &efy, &emz));
   TRY_TEST_B( IsEqual(sfx, 0.0) );
   TRY_TEST_B( IsEqual(sfy, 2.0));
   TRY_TEST_B( IsEqual(smz, 0.0));
   TRY_TEST_B( IsEqual(efx, 0.0));
   TRY_TEST_B( IsEqual(efy, 2.0));
   TRY_TEST_B( IsEqual(emz, 0.0));

   TRY_TEST_HR(presults->ComputeReactions(0, 0, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  -1.41421356));
   TRY_TEST_B( IsEqual(fy,  1.41421356));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputeReactions(0, 8, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  -1.41421356));
   TRY_TEST_B( IsEqual(fy,  1.41421356));
   TRY_TEST_B( IsEqual(mz,  0.0));

   TRY_TEST_HR(presults->ComputeMemberDeflections(0, 1, &sdx, &sdy, &srz, &edx, &edy, &erz));
   TRY_TEST_B( IsEqual(sdx,   0.0) );
   TRY_TEST_B( IsEqual(sdy,   0.0));
   TRY_TEST_B( IsEqual(srz, -2.2857142857143));
   TRY_TEST_B( IsEqual(edx,   0.0));
   TRY_TEST_B( IsEqual(edy,   0.0));
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

   TRY_TEST_HR(presults->ComputePOIDeflections(0, 10,  lotGlobalProjected, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 0.0) );
   TRY_TEST_B( IsEqual(dy, 0.0) );
   TRY_TEST_B( IsEqual(rz, -2.2857142857143) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 15,  lotGlobalProjected, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  2.9631141) );
   TRY_TEST_B( IsEqual(dy, -2.9631141));
   TRY_TEST_B( IsEqual(rz, -1.71428) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 12,  lotGlobalProjected, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  4.3099842) );
   TRY_TEST_B( IsEqual(dy, -4.3099842));
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 20,  lotGlobalProjected, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  4.3099842) );
   TRY_TEST_B( IsEqual(dy, -4.3099842));
   TRY_TEST_B( IsEqual(rz, 0.0) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 25,  lotGlobalProjected, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  2.9631141) );
   TRY_TEST_B( IsEqual(dy, -2.9631141));
   TRY_TEST_B( IsEqual(rz, 1.71428) );
   TRY_TEST_HR(presults->ComputePOIDeflections(0, 22,  lotGlobalProjected, &dx, &dy, &rz));
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
   TRY_TEST_HR(presults->ComputePOIForces(0, 10, mftLeft, lotGlobalProjected, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  1.41421355));
   TRY_TEST_B( IsEqual(fy, -1.41421355));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 10, mftRight, lotGlobalProjected, &fx, &fy, &mz));
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
   TRY_TEST_HR(presults->ComputePOIForces(0, 15, mftLeft, lotGlobalProjected, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   1.41421355));
   TRY_TEST_B( IsEqual(fy,  -1.41421355));
   TRY_TEST_B( IsEqual(mz,   4.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 15, mftRight, lotGlobalProjected, &fx, &fy, &mz));
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
   TRY_TEST_HR(presults->ComputePOIForces(0, 12, mftLeft, lotGlobalProjected, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   1.41421355));
   TRY_TEST_B( IsEqual(fy,  -1.41421355));
   TRY_TEST_B( IsEqual(mz,   8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 12, mftRight, lotGlobalProjected, &fx, &fy, &mz));
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
   TRY_TEST_B( IsEqual(fx,  1.41421355));
   TRY_TEST_B( IsEqual(fy, -1.41421355));
   TRY_TEST_B( IsEqual(mz,  8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 20, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   1.41421355));
   TRY_TEST_B( IsEqual(fy,  -1.41421355));
   TRY_TEST_B( IsEqual(mz,  -8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 20, mftLeft, lotGlobalProjected, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  1.41421355));
   TRY_TEST_B( IsEqual(fy, -1.41421355));
   TRY_TEST_B( IsEqual(mz,  8.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 20, mftRight, lotGlobalProjected, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   1.41421355));
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
   TRY_TEST_B( IsEqual(fx,  -1.41421355));
   TRY_TEST_B( IsEqual(fy,   1.41421355));
   TRY_TEST_B( IsEqual(mz,   4.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 25, mftRight, lotGlobal, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   1.41421355));
   TRY_TEST_B( IsEqual(fy,  -1.41421355));
   TRY_TEST_B( IsEqual(mz,  -4.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 25, mftLeft, lotGlobalProjected, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  -1.41421355));
   TRY_TEST_B( IsEqual(fy,   1.41421355));
   TRY_TEST_B( IsEqual(mz,   4.0));
   TRY_TEST_HR(presults->ComputePOIForces(0, 25, mftRight, lotGlobalProjected, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   1.41421355));
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
