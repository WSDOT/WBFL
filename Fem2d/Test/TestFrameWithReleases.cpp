///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 2001  Washington State Department of Transportation
//                   Bridge and Structures Office
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
// TestFrameWithReleases.cpp: implementation of the CTestFrameWithReleases class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestFrameWithReleases.h"
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



CTestFrameWithReleases::CTestFrameWithReleases()
{

}

CTestFrameWithReleases::~CTestFrameWithReleases()
{

}

void CTestFrameWithReleases::Test() 
{

/*////////////////////////////////////////////////////
               w
          ============ 3
                     /o
                   /  |
             m2  /    |      <-various loads and release conditions on m2
               /      | m3     
             /        |
           /          |
         2o           o4
          |           |
          |           | m4
          | m1        |  
          |           |
         1o           o5
         ===         ===

  Made up and verified using WinStrudl. Input and output files are in the 
  WinStrudl directory and called Releases.*

*/////////////////////////////////////////////////
   CComPtr<IFem2dModel> pmodel;
   pmodel = CreateModel();
   ATLASSERT(pmodel);

   // create joints
   CComPtr<IFem2dJointCollection> pJoints;
   TRY_TEST_HR(pmodel->get_Joints(&pJoints));

   CComPtr<IFem2dJoint> pJoint1,pJoint2,pJoint3,pJoint4,pJoint5;
   TRY_TEST_MC(pJoints->Create(1,  0.0,   0.0, &pJoint1));
   TRY_TEST_MC(pJoints->Create(2,  0.0,  10.0, &pJoint2));
   TRY_TEST_MC(pJoints->Create(3, 10.0,  20.0, &pJoint3));
   TRY_TEST_MC(pJoints->Create(4, 10.0,  10.0, &pJoint4));
   TRY_TEST_MC(pJoints->Create(5, 10.0,   0.0, &pJoint5));

   // boundary conditions
   TRY_TEST_MC(pJoint1->Support());
   TRY_TEST_MC(pJoint5->Support());

   // create members
   CComPtr<IFem2dMemberCollection> pMembers;
   TRY_TEST_HR(pmodel->get_Members(&pMembers));

   Float64 EA=100;
   Float64 EI=10000;
   CComPtr<IFem2dMember> pMember1, pMember2, pMember3, pMember4;
   TRY_TEST_MC(pMembers->Create(1,  1,  2, EA, EI, &pMember1));
   TRY_TEST_MC(pMembers->Create(2,  2,  3, EA, EI, &pMember2));
   TRY_TEST_MC(pMembers->Create(3,  3,  4, EA, EI, &pMember3));
   TRY_TEST_MC(pMembers->Create(4,  4,  5, EA, EI, &pMember4));

   // add some POI's 
   CComPtr<IFem2dPOICollection> pPOIs;
   TRY_TEST_HR(pmodel->get_POIs(&pPOIs));

   CComPtr<IFem2dPOI> pPOI200, pPOI201, pPOI202, pPOI203, pPOI204;
   TRY_TEST_HR(pPOIs->Create(200,  2,  0.00,  &pPOI200));
   TRY_TEST_HR(pPOIs->Create(201,  2, -0.25,  &pPOI201));
   TRY_TEST_HR(pPOIs->Create(202,  2, -0.50,  &pPOI202));
   TRY_TEST_HR(pPOIs->Create(203,  2, -0.75,  &pPOI203));
   TRY_TEST_HR(pPOIs->Create(204,  2, -1.00,  &pPOI204));

   // Create load cases with various member loads on member 2.
   // Also, all load cases will have a joint load on Joint 2 to cause sidesway of the frame
   CComPtr<IFem2dLoadingCollection> pLoadings;
   TRY_TEST_HR(pmodel->get_Loadings(&pLoadings));

   // load case 0
   // vertical point load at the center of member 2
   CComPtr<IFem2dLoading> pLoading0;
   TRY_TEST_LC(pLoadings->Create(0, &pLoading0));
   CComPtr<IFem2dPointLoadCollection> pPointLoads;
   TRY_TEST_HR(pLoading0->get_PointLoads(&pPointLoads));
   CComPtr<IFem2dPointLoad> pPointLoad;
   TRY_TEST_LC(pPointLoads->Create(1, 2, -0.5, 0.0, -10.0, 0.0, lotGlobal, &pPointLoad));

   CComPtr<IFem2dJointLoadCollection> pJointLoads;
   TRY_TEST_HR(pLoading0->get_JointLoads(&pJointLoads));
   CComPtr<IFem2dJointLoad> pJointLoad;
   TRY_TEST_LC(pJointLoads->Create(1, 2, 10.0, 0.0, 0.0, &pJointLoad));

   // load case 1
   // uniform distributed load along member 2
   CComPtr<IFem2dLoading> pLoading1;
   TRY_TEST_LC(pLoadings->Create(1, &pLoading1));
   CComPtr<IFem2dDistributedLoadCollection> pDistributedLoads;
   TRY_TEST_HR(pLoading1->get_DistributedLoads(&pDistributedLoads));
   CComPtr<IFem2dDistributedLoad> pDistributedLoad;
   TRY_TEST_LC(pDistributedLoads->Create(1, 2, loadDirFy, 0.0, -1.0, -1.0, -1.0, lotMember, &pDistributedLoad));

   pJointLoads.Release();
   TRY_TEST_HR(pLoading1->get_JointLoads(&pJointLoads));
   pJointLoad.Release();
   TRY_TEST_LC(pJointLoads->Create(1, 2, 10.0, 0.0, 0.0, &pJointLoad));

   // load case 2
   // temperature strain load along member 2
   CComPtr<IFem2dLoading> pLoading2;
   TRY_TEST_LC(pLoadings->Create(2, &pLoading2));
   CComPtr<IFem2dMemberStrainCollection> pMemberStrains;
   TRY_TEST_HR(pLoading2->get_MemberStrains(&pMemberStrains));
   CComPtr<IFem2dMemberStrain> pStrainLoad;
   TRY_TEST_LC(pMemberStrains->Create(1, 2, 2, 1, &pStrainLoad));

   pJointLoads.Release();
   TRY_TEST_HR(pLoading2->get_JointLoads(&pJointLoads));
   pJointLoad.Release();
   TRY_TEST_LC(pJointLoads->Create(1, 2, 10.0, 0.0, 0.0, &pJointLoad));

   // get results interface
   CComQIPtr<IFem2dModelResults> presults(pmodel);

   ////////////////////////////////
   // place a hinge at the start of member 2
   pMember2->ReleaseEnd(metStart, mbrReleaseMz);
   long lc=0;

   Float64 dx, dy, rz;
   TRY_TEST_HR(presults->ComputeJointDisplacements(lc, 2, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  0.27095097726495) );
   TRY_TEST_B( IsEqual(dy, -0.55948045530510) );
   TRY_TEST_B( IsEqual(rz, -0.040642646589743) );
   TRY_TEST_HR(presults->ComputeJointDisplacements(lc, 3, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  0.24372562274697) );
   TRY_TEST_B( IsEqual(dy, -0.88103908938980) );
   TRY_TEST_B( IsEqual(rz, -0.011896091061020) );

   TRY_TEST_HR(presults->ComputePOIDisplacements(lc, 200, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  0.27095097726495) );
   TRY_TEST_B( IsEqual(dy, -0.55948045530510) );
   TRY_TEST_B( IsEqual(rz, -0.020546367819410) );
   TRY_TEST_HR(presults->ComputePOIDisplacements(lc, 201, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  0.18895930338732) );
   TRY_TEST_B( IsEqual(dy, -0.74146147387478) );
   TRY_TEST_B( IsEqual(rz, -0.018900871176406) );
   TRY_TEST_HR(presults->ComputePOIDisplacements(lc, 202, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  0.098740146294668) );
   TRY_TEST_B( IsEqual(dy, -0.91521500922943) );
   TRY_TEST_B( IsEqual(rz, -0.013964381247396) );
   TRY_TEST_HR(presults->ComputePOIDisplacements(lc, 203, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  0.17252556588730) );
   TRY_TEST_B( IsEqual(dy, -0.89941973067610) );
   TRY_TEST_B( IsEqual(rz, -0.010156315414796) );
   TRY_TEST_HR(presults->ComputePOIDisplacements(lc, 204, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  0.24372562274697) );
   TRY_TEST_B( IsEqual(dy, -0.88103908938980) );
   TRY_TEST_B( IsEqual(rz, -0.011896091061020) );

   Float64 fx, fy, mz;
   TRY_TEST_HR(presults->ComputePOIForces(lc, 200, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx, -5.2794538489462));
   TRY_TEST_B( IsEqual(fy, -2.6327946288053));
   TRY_TEST_B( IsEqual(mz, 0.0));
   TRY_TEST_HR(presults->ComputePOIForces(lc, 202, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  -5.2794538489462));
   TRY_TEST_B( IsEqual(fy,  -2.6327946288053));
   TRY_TEST_B( IsEqual(mz,  18.616669354998));
   TRY_TEST_HR(presults->ComputePOIForces(lc, 204, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  1.7916139629193));
   TRY_TEST_B( IsEqual(fy,  4.4382731830602));
   TRY_TEST_B( IsEqual(mz,-12.766661290005));

   // distributed load case
   lc = 1;
   TRY_TEST_HR(presults->ComputeJointDisplacements(lc, 2, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  0.45266417074768) );
   TRY_TEST_B( IsEqual(dy, -0.39458259696851) );
   TRY_TEST_B( IsEqual(rz, -0.067899625612152) );
   TRY_TEST_HR(presults->ComputeJointDisplacements(lc, 3, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  1.2171701857750) );
   TRY_TEST_B( IsEqual(dy, -1.2108348060630) );
   TRY_TEST_B( IsEqual(rz, -0.078916519393703) );

   TRY_TEST_HR(presults->ComputePOIDisplacements(lc, 200, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  0.45266417074768) );
   TRY_TEST_B( IsEqual(dy, -0.39458259696851) );
   TRY_TEST_B( IsEqual(rz, -0.084991163622169) );
   TRY_TEST_HR(presults->ComputePOIDisplacements(lc, 201, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  0.65636254192269) );
   TRY_TEST_B( IsEqual(dy, -0.61121751666031) );
   TRY_TEST_B( IsEqual(rz, -0.082401789666682) );
   TRY_TEST_HR(presults->ComputePOIDisplacements(lc, 202, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  0.84987617918428) );
   TRY_TEST_B( IsEqual(dy, -0.81766770243869) );
   TRY_TEST_B( IsEqual(rz, -0.077579946055165) );
   TRY_TEST_HR(presults->ComputePOIDisplacements(lc, 203, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  1.0331481801204) );
   TRY_TEST_B( IsEqual(dy, -1.0138762518916) );
   TRY_TEST_B( IsEqual(rz, -0.074945050170033) );
   TRY_TEST_HR(presults->ComputePOIDisplacements(lc, 204, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  1.2171701857750) );
   TRY_TEST_B( IsEqual(dy, -1.2108348060630) );
   TRY_TEST_B( IsEqual(rz, -0.078916519393703) );

   TRY_TEST_HR(presults->ComputePOIForces(lc, 200, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx, -0.25873097033570));
   TRY_TEST_B( IsEqual(fy, -5.3215096307570));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(lc, 202, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  -0.25873097033570));
   TRY_TEST_B( IsEqual(fy,  1.7495581811085));
   TRY_TEST_B( IsEqual(mz,  12.628755460578));
   TRY_TEST_HR(presults->ComputePOIForces(lc, 204, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  -0.25873097033570));
   TRY_TEST_B( IsEqual(fy,   8.8206259929739));
   TRY_TEST_B( IsEqual(mz, -24.742489078844));
   
   // strains load case
   lc = 2;
   TRY_TEST_HR(presults->ComputeJointDisplacements(lc, 2, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, -13.952250159469) );
   TRY_TEST_B( IsEqual(dy,   9.8425183846726) );
   TRY_TEST_B( IsEqual(rz,   2.0928375239203) );
   TRY_TEST_HR(presults->ComputeJointDisplacements(lc, 3, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,   8.8861302162586) );
   TRY_TEST_B( IsEqual(dy, -19.685036769345) );
   TRY_TEST_B( IsEqual(rz,   1.9685036769345) );

   TRY_TEST_HR(presults->ComputePOIDisplacements(lc, 200, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, -13.952250159469) );
   TRY_TEST_B( IsEqual(dy,   9.8425183846726) );
   TRY_TEST_B( IsEqual(rz,  -8.4472309091309) );
   TRY_TEST_HR(presults->ComputePOIDisplacements(lc, 201, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  2.1043462710348) );
   TRY_TEST_B( IsEqual(dy, -7.8863717404034) );
   TRY_TEST_B( IsEqual(rz, -5.1445970680522) );
   TRY_TEST_HR(presults->ComputePOIDisplacements(lc, 202, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  10.486608260977) );
   TRY_TEST_B( IsEqual(dy, -17.940927424918) );
   TRY_TEST_B( IsEqual(rz,  -2.3077633566818) );
   TRY_TEST_HR(presults->ComputePOIDisplacements(lc, 203, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  12.359036134628) );
   TRY_TEST_B( IsEqual(dy, -21.485648993142) );
   TRY_TEST_B( IsEqual(rz,   0.063270224980469) );
   TRY_TEST_HR(presults->ComputePOIDisplacements(lc, 204, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,   8.8861302162586) );
   TRY_TEST_B( IsEqual(dy, -19.685036769345) );
   TRY_TEST_B( IsEqual(rz,   1.9685036769345) );

   TRY_TEST_HR(presults->ComputePOIForces(lc, 200, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx, -233.445873891450));
   TRY_TEST_B( IsEqual(fy, 372.64010376656));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(lc, 202, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  -233.44587389145));
   TRY_TEST_B( IsEqual(fy,   372.64010376656));
   TRY_TEST_B( IsEqual(mz, -2634.9634431539));
   TRY_TEST_HR(presults->ComputePOIForces(lc, 204, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  -233.44587389145));
   TRY_TEST_B( IsEqual(fy,   372.64010376656));
   TRY_TEST_B( IsEqual(mz, -5269.9268863078));


   ////////////////////////////////
   // now place a hinge at the end of member 2 to make pin-pin
   pMember2->ReleaseEnd(metEnd, mbrReleaseMz);

   // point loads
   lc=0;

   TRY_TEST_HR(presults->ComputeJointDisplacements(lc, 2, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  0.30186931671375) );
   TRY_TEST_B( IsEqual(dy, -0.59439204985874) );
   TRY_TEST_B( IsEqual(rz, -0.045280397507063) );
   TRY_TEST_HR(presults->ComputeJointDisplacements(lc, 3, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  0.25171213295665) );
   TRY_TEST_B( IsEqual(dy, -0.81121590028251) );
   TRY_TEST_B( IsEqual(rz, -0.018878409971749) );

   TRY_TEST_HR(presults->ComputePOIDisplacements(lc, 200, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  0.30186931671375) );
   TRY_TEST_B( IsEqual(dy, -0.59439204985874) );
   TRY_TEST_B( IsEqual(rz, -0.017172168098165) );
   TRY_TEST_HR(presults->ComputePOIDisplacements(lc, 201, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  0.22119733612890) );
   TRY_TEST_B( IsEqual(dy, -0.75724202311574) );
   TRY_TEST_B( IsEqual(rz, -0.014962459406957) );
   TRY_TEST_HR(presults->ComputePOIDisplacements(lc, 202, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  0.12947681208800) );
   TRY_TEST_B( IsEqual(dy, -0.90904345291670) );
   TRY_TEST_B( IsEqual(rz, -0.0083333333333333) );
   TRY_TEST_HR(presults->ComputePOIDisplacements(lc, 203, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  0.19611874425035) );
   TRY_TEST_B( IsEqual(dy, -0.86565394832763) );
   TRY_TEST_B( IsEqual(rz, -0.0017042072597094) );
   TRY_TEST_HR(presults->ComputePOIDisplacements(lc, 204, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  0.25171213295665) );
   TRY_TEST_B( IsEqual(dy, -0.81121590028251) );
   TRY_TEST_B( IsEqual(rz, 0.00050550143149) );

   TRY_TEST_HR(presults->ComputePOIForces(lc, 200, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx, -4.8704390768371));
   TRY_TEST_B( IsEqual(fy, -3.5355339059327));
   TRY_TEST_B( IsEqual(mz, 0.0));
   TRY_TEST_HR(presults->ComputePOIForces(lc, 202, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  -4.8704390768371));
   TRY_TEST_B( IsEqual(fy,  -3.5355339059327));
   TRY_TEST_B( IsEqual(mz,  25.000000000000));
   TRY_TEST_HR(presults->ComputePOIForces(lc, 204, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  2.2006287350284));
   TRY_TEST_B( IsEqual(fy,  3.5355339059327));
   TRY_TEST_B( IsEqual(mz,  0.0));

   // distributed load case
   lc = 1;
   TRY_TEST_HR(presults->ComputeJointDisplacements(lc, 2, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  0.51258560664783) );
   TRY_TEST_B( IsEqual(dy, -0.46224318005650) );
   TRY_TEST_B( IsEqual(rz, -0.076887840997175) );
   TRY_TEST_HR(presults->ComputeJointDisplacements(lc, 3, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  1.2326484801507) );
   TRY_TEST_B( IsEqual(dy, -1.0755136398870) );
   TRY_TEST_B( IsEqual(rz, -0.092448636011300) );

   TRY_TEST_HR(presults->ComputePOIDisplacements(lc, 200, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  0.51258560664783) );
   TRY_TEST_B( IsEqual(dy, -0.46224318005650) );
   TRY_TEST_B( IsEqual(rz, -0.078451779686442) );
   TRY_TEST_HR(presults->ComputePOIDisplacements(lc, 201, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  0.71884161573164) );
   TRY_TEST_B( IsEqual(dy, -0.64180108572222) );
   TRY_TEST_B( IsEqual(rz, -0.074768931867762) );
   TRY_TEST_HR(presults->ComputePOIDisplacements(lc, 202, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  0.90944552158605) );
   TRY_TEST_B( IsEqual(dy, -0.80570688815855) );
   TRY_TEST_B( IsEqual(rz, -0.066666666666666) );
   TRY_TEST_HR(presults->ComputePOIDisplacements(lc, 203, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  1.0788730524831) );
   TRY_TEST_B( IsEqual(dy, -0.94843631563747) );
   TRY_TEST_B( IsEqual(rz, -0.058564401465571) );
   TRY_TEST_HR(presults->ComputePOIDisplacements(lc, 204, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  1.2326484801507) );
   TRY_TEST_B( IsEqual(dy, -1.0755136398870) );
   TRY_TEST_B( IsEqual(rz, -0.054881553646891) );

   TRY_TEST_HR(presults->ComputePOIForces(lc, 200, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx, 0.53396206836173));
   TRY_TEST_B( IsEqual(fy, -7.0710678118655));
   TRY_TEST_B( IsEqual(mz,  0.0));
   TRY_TEST_HR(presults->ComputePOIForces(lc, 202, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.53396206836173));
   TRY_TEST_B( IsEqual(fy,  0.0));
   TRY_TEST_B( IsEqual(mz,  25.0000000));
   TRY_TEST_HR(presults->ComputePOIForces(lc, 204, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.53396206836173));
   TRY_TEST_B( IsEqual(fy,  7.0710678118655));
   TRY_TEST_B( IsEqual(mz,  0.0));
   
   // strains load case
   lc = 2;
   TRY_TEST_HR(presults->ComputeJointDisplacements(lc, 2, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, -1.1895250710544) );
   TRY_TEST_B( IsEqual(dy, -4.5685752131632) );
   TRY_TEST_B( IsEqual(rz,  0.17842876065816) );
   TRY_TEST_HR(presults->ComputeJointDisplacements(lc, 3, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  12.182867235102) );
   TRY_TEST_B( IsEqual(dy,  9.1371504263265) );
   TRY_TEST_B( IsEqual(rz, -0.91371504263264) );

   TRY_TEST_HR(presults->ComputePOIDisplacements(lc, 200, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  -1.1895250710544) );
   TRY_TEST_B( IsEqual(dy,  -4.5685752131632) );
   TRY_TEST_B( IsEqual(rz,  -7.0544011451988) );
   TRY_TEST_HR(presults->ComputePOIDisplacements(lc, 201, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  15.411825152732) );
   TRY_TEST_B( IsEqual(dy, -14.400395950539) );
   TRY_TEST_B( IsEqual(rz, -3.5188672392661) );
   TRY_TEST_HR(presults->ComputePOIDisplacements(lc, 202, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  23.174340611687) );
   TRY_TEST_B( IsEqual(dy, -15.393381923082) );
   TRY_TEST_B( IsEqual(rz,   0.016666666666668) );
   TRY_TEST_HR(presults->ComputePOIDisplacements(lc, 203, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  22.098021305811) );
   TRY_TEST_B( IsEqual(dy,  -7.5475331307937) );
   TRY_TEST_B( IsEqual(rz,   3.5522005725994) );
   TRY_TEST_HR(presults->ComputePOIDisplacements(lc, 204, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  12.182867235102) );
   TRY_TEST_B( IsEqual(dy,   9.1371504263265) );
   TRY_TEST_B( IsEqual(rz,   7.0877344785321) );

   TRY_TEST_HR(presults->ComputePOIForces(lc, 200, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx, -64.609410271770));
   TRY_TEST_B( IsEqual(fy,   0.0));
   TRY_TEST_B( IsEqual(mz,   0.0));
   TRY_TEST_HR(presults->ComputePOIForces(lc, 202, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx, -64.609410271770));
   TRY_TEST_B( IsEqual(fy,   0.0));
   TRY_TEST_B( IsEqual(mz,   0.0));
   TRY_TEST_HR(presults->ComputePOIForces(lc, 204, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx, -64.609410271770));
   TRY_TEST_B( IsEqual(fy,   0.0));
   TRY_TEST_B( IsEqual(mz,   0.0));

   ////////////////////////////////
   // now fix the start of member 2 to make fix-pin
   pMember2->ReleaseEnd(metStart, mbrReleaseNone);

   // point loads
   lc=0;

   TRY_TEST_HR(presults->ComputeJointDisplacements(lc, 2, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  0.24898601337127) );
   TRY_TEST_B( IsEqual(dy, -0.54895017991052) );
   TRY_TEST_B( IsEqual(rz, -0.035306984205934) );
   TRY_TEST_HR(presults->ComputeJointDisplacements(lc, 3, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  0.34823171173542) );
   TRY_TEST_B( IsEqual(dy, -0.90209964017896) );
   TRY_TEST_B( IsEqual(rz, -0.026117378380157) );

   TRY_TEST_HR(presults->ComputePOIDisplacements(lc, 200, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  0.24898601337127) );
   TRY_TEST_B( IsEqual(dy, -0.54895017991052) );
   TRY_TEST_B( IsEqual(rz, -0.035306984205934) );
   TRY_TEST_HR(presults->ComputePOIDisplacements(lc, 201, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  0.21197852063696) );
   TRY_TEST_B( IsEqual(dy, -0.75219532294892) );
   TRY_TEST_B( IsEqual(rz, -0.030571768586635) );
   TRY_TEST_HR(presults->ComputePOIDisplacements(lc, 202, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  0.15851068388641) );
   TRY_TEST_B( IsEqual(dy, -0.93898012197108) );
   TRY_TEST_B( IsEqual(rz, -0.022138708992946) );
   TRY_TEST_HR(presults->ComputePOIDisplacements(lc, 203, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  0.25979743629897) );
   TRY_TEST_B( IsEqual(dy, -0.92696611956307) );
   TRY_TEST_B( IsEqual(rz, -0.014427222807283) );
   TRY_TEST_HR(presults->ComputePOIDisplacements(lc, 204, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  0.34823171173542) );
   TRY_TEST_B( IsEqual(dy, -0.90209964017896) );
   TRY_TEST_B( IsEqual(rz, -0.011856727412062) );

   TRY_TEST_HR(presults->ComputePOIForces(lc, 200, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx, -4.8050527154542));
   TRY_TEST_B( IsEqual(fy, -2.9582751795118));
   TRY_TEST_B( IsEqual(mz,  8.1636711990265));
   TRY_TEST_HR(presults->ComputePOIForces(lc, 202, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  -4.8050527154542));
   TRY_TEST_B( IsEqual(fy,  -2.9582751795118));
   TRY_TEST_B( IsEqual(mz,  29.081835599513));
   TRY_TEST_HR(presults->ComputePOIForces(lc, 204, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  2.2660150964113));
   TRY_TEST_B( IsEqual(fy,  4.1127926323536));
   TRY_TEST_B( IsEqual(mz,  0.0));

   // distributed load case
   lc = 1;
   TRY_TEST_HR(presults->ComputeJointDisplacements(lc, 2, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  0.51552802763460) );
   TRY_TEST_B( IsEqual(dy, -0.46477156053507) );
   TRY_TEST_B( IsEqual(rz, -0.077442760579578) );
   TRY_TEST_HR(presults->ComputeJointDisplacements(lc, 3, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  1.2272781417587) );
   TRY_TEST_B( IsEqual(dy, -1.0704568789299) );
   TRY_TEST_B( IsEqual(rz, -0.092045860631905) );

   TRY_TEST_HR(presults->ComputePOIDisplacements(lc, 200, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  0.51552802763460) );
   TRY_TEST_B( IsEqual(dy, -0.46477156053507) );
   TRY_TEST_B( IsEqual(rz, -0.077442760579578) );
   TRY_TEST_HR(presults->ComputePOIDisplacements(lc, 201, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  0.71935454957771) );
   TRY_TEST_B( IsEqual(dy, -0.64208188354585) );
   TRY_TEST_B( IsEqual(rz, -0.073900431679305) );
   TRY_TEST_HR(presults->ComputePOIDisplacements(lc, 202, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  0.90783008025945) );
   TRY_TEST_B( IsEqual(dy, -0.80404121529524) );
   TRY_TEST_B( IsEqual(rz, -0.065898537134214) );
   TRY_TEST_HR(presults->ComputePOIDisplacements(lc, 203, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  1.0753299772958) );
   TRY_TEST_B( IsEqual(dy, -0.94502491339924) );
   TRY_TEST_B( IsEqual(rz, -0.057856494326720) );
   TRY_TEST_HR(presults->ComputePOIDisplacements(lc, 204, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  1.2272781417587) );
   TRY_TEST_B( IsEqual(dy, -1.0704568789299) );
   TRY_TEST_B( IsEqual(rz, -0.054193720639241) );

   TRY_TEST_HR(presults->ComputePOIForces(lc, 200, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx, 0.53032397864682));
   TRY_TEST_B( IsEqual(fy, -7.1031864217869));
   TRY_TEST_B( IsEqual(mz,  -0.45422573755482));
   TRY_TEST_HR(presults->ComputePOIForces(lc, 202, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.53032397864682));
   TRY_TEST_B( IsEqual(fy,  -0.032118609921449));
   TRY_TEST_B( IsEqual(mz,  24.772887131223));
   TRY_TEST_HR(presults->ComputePOIForces(lc, 204, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  0.53032397864682));
   TRY_TEST_B( IsEqual(fy,  7.0389492019440));
   TRY_TEST_B( IsEqual(mz,  0.0));
   
   // strains load case
   lc = 2;
   TRY_TEST_HR(presults->ComputeJointDisplacements(lc, 2, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 12.418444764815) );
   TRY_TEST_B( IsEqual(dy, -16.261710029957) );
   TRY_TEST_B( IsEqual(rz,  -2.3879371579663) );
   TRY_TEST_HR(presults->ComputeJointDisplacements(lc, 3, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  -12.653620532812) );
   TRY_TEST_B( IsEqual(dy ,  32.523420059913) );
   TRY_TEST_B( IsEqual(rz,    0.94902153996093) );

   TRY_TEST_HR(presults->ComputePOIDisplacements(lc, 200, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx, 12.418444764815) );
   TRY_TEST_B( IsEqual(dy, -16.261710029957) );
   TRY_TEST_B( IsEqual(rz,  -2.3879371579663) );
   TRY_TEST_HR(presults->ComputePOIDisplacements(lc, 201, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  17.784017417734) );
   TRY_TEST_B( IsEqual(dy, -15.699016484814) );
   TRY_TEST_B( IsEqual(rz, 0.49773147999734) );
   TRY_TEST_HR(presults->ComputePOIDisplacements(lc, 202, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  15.703323737182) );
   TRY_TEST_B( IsEqual(dy,  -7.6900566062025) );
   TRY_TEST_B( IsEqual(rz,   3.5690759088093) );
   TRY_TEST_HR(presults->ComputePOIDisplacements(lc, 203, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  5.7121742460405) );
   TRY_TEST_B( IsEqual(dy,  8.2293590829997) );
   TRY_TEST_B( IsEqual(rz,  6.8260961284696) );
   TRY_TEST_HR(presults->ComputePOIDisplacements(lc, 204, lotGlobal, &dx, &dy, &rz));
   TRY_TEST_B( IsEqual(dx,  -12.653620532812) );
   TRY_TEST_B( IsEqual(dy,   32.523420059913) );
   TRY_TEST_B( IsEqual(rz,   10.268792138978) );

   TRY_TEST_HR(presults->ComputePOIForces(lc, 200, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,   -81.434676038792));
   TRY_TEST_B( IsEqual(fy,  -148.54063267864));
   TRY_TEST_B( IsEqual(mz, -2100.6817729761));
   TRY_TEST_HR(presults->ComputePOIForces(lc, 202, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,    -81.434676038792));
   TRY_TEST_B( IsEqual(fy,   -148.54063267864));
   TRY_TEST_B( IsEqual(mz,  -1050.3408864881));
   TRY_TEST_HR(presults->ComputePOIForces(lc, 204, mftLeft, lotMember, &fx, &fy, &mz));
   TRY_TEST_B( IsEqual(fx,  -81.434676038792));
   TRY_TEST_B( IsEqual(fy, -148.54063267864));
   TRY_TEST_B( IsEqual(mz,    0.0));


   ReleaseModel(pmodel);
}