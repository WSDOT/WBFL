///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2019  Washington State Department of Transportation
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
// TestPersistence.cpp: implementation of the CTestPersistence class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestPersistence.h"
#include <MathEx.h>
#include <iostream>
#include <WBFLCore.h>
#include <COMDEF.H>
#include "WbflTools_i.c"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CTestPersistence::CTestPersistence()
{

}

CTestPersistence::~CTestPersistence()
{

}

// create a struct for results comparison
struct TpComp
{
   // a struct to save saved and loaded results
   struct DualVal
   {
      Float64 xs, ys, zs; // saved 
      Float64 xl, yl, zl; // loaded
      DualVal(): xs(0.0), ys(0.0), zs(0.), xl(0.0), yl(0.0), zl(0.0) {;}
      void SetSaved(Float64 x, Float64 y, Float64 z)
      {
         xs = x;
         ys = y;
         zs = z;
      }
      void SetLoaded(Float64 x, Float64 y, Float64 z)
      {
         xl = x;
         yl = y;
         zl = z;
      }
      bool Equal() {return xs==xl && ys==yl && zs==zl;}
   };

   DualVal R_1;
   DualVal R_4;

   DualVal PD_35;
   DualVal PF_35;
   DualVal PD_1025;
   DualVal PF_1025;

   bool Equal()
   {
      return R_1.Equal() && R_4.Equal() && PD_35.Equal() && PF_35.Equal() && PD_1025.Equal() && PF_1025.Equal();
   }
};

void CTestPersistence::Test() 
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
   CComPtr<IFem2dJoint> pJoint6,pJoint7,pJoint8,pJoint9;
   TRY_TEST_MC(pJoints->Create(1,  0.0,   0.0, &pJoint1));
   TRY_TEST_MC(pJoints->Create(2,  0.0,  24.0, &pJoint2));
   TRY_TEST_MC(pJoints->Create(3,  0.0,  36.0, &pJoint3));
   TRY_TEST_MC(pJoints->Create(4, 24.0,   0.0, &pJoint4));
   TRY_TEST_MC(pJoints->Create(5, 24.0,  24.0, &pJoint5));
   TRY_TEST_MC(pJoints->Create(6, 24.0,  36.0, &pJoint6));
   TRY_TEST_MC(pJoints->Create(7, 24.0,  56.0, &pJoint7));
   TRY_TEST_MC(pJoints->Create(8, 48.0,   0.0, &pJoint8));
   TRY_TEST_MC(pJoints->Create(9, 48.0,  24.0, &pJoint9));

   // boundary conditions
   TRY_TEST_MC(pJoint1->Support());
   TRY_TEST_MC(pJoint4->Support());
   TRY_TEST_MC(pJoint4->ReleaseDof(jrtMz));
   TRY_TEST_MC(pJoint8->Support());
   TRY_TEST_MC(pJoint8->ReleaseDof(jrtMz));

   // create members
   CComPtr<IFem2dMemberCollection> pMembers;
   TRY_TEST_HR(pmodel->get_Members(&pMembers));

   Float64 E=3.0;
   Float64 A=5.0;
   Float64 I=7.0;
   CComPtr<IFem2dMember> pMember1, pMember2, pMember3, pMember4, pMember5;
   CComPtr<IFem2dMember> pMember6, pMember7, pMember8, pMember9, pMember10, pMember11;
   TRY_TEST_MC(pMembers->Create(1,  1,  2, E*A, E*I, &pMember1));
   TRY_TEST_MC(pMembers->Create(2,  2,  3, E*A, E*I, &pMember2));
   TRY_TEST_MC(pMembers->Create(3,  3,  7, E*A, E*I, &pMember3));
   TRY_TEST_MC(pMembers->Create(4,  3,  6, E*A, E*I, &pMember4));
   TRY_TEST_MC(pMembers->Create(5,  2,  5, E*A, E*I, &pMember5));
   TRY_TEST_MC(pMembers->Create(6,  6,  7, E*A, E*I, &pMember6));
   TRY_TEST_MC(pMembers->Create(7,  5,  6, E*A, E*I, &pMember7));
   TRY_TEST_MC(pMembers->Create(8,  7,  9, E*A, E*I, &pMember8));
   TRY_TEST_MC(pMembers->Create(9,  5,  9, E*A, E*I, &pMember9));
   TRY_TEST_MC(pMembers->Create(10, 4,  5, E*A, E*I, &pMember10));
   TRY_TEST_MC(pMembers->Create(11, 8,  9, E*A, E*I, &pMember11));

   // release member ends
   TRY_TEST_MC(pMember5->ReleaseEnd(metStart, mbrReleaseMz));
   TRY_TEST_MC(pMember9->ReleaseEnd(metEnd,   mbrReleaseMz));

   // create load case and apply loads
   CComPtr<IFem2dLoadingCollection> pLoadings;
   TRY_TEST_HR(pmodel->get_Loadings(&pLoadings));
   CComPtr<IFem2dLoading> pLoading1;
   TRY_TEST_LC(pLoadings->Create(1, &pLoading1));

   // distributed loads
   CComPtr<IFem2dDistributedLoadCollection> pDistributedLoads;
   TRY_TEST_HR(pLoading1->get_DistributedLoads(&pDistributedLoads));
   CComPtr<IFem2dDistributedLoad> pDistributedLoad1, pDistributedLoad2;
   TRY_TEST_LC(pDistributedLoads->Create(1, 3, loadDirFy, -0.1, -0.7, -2.0, 0.0, lotMember, &pDistributedLoad1));
   TRY_TEST_LC(pDistributedLoad1->put_Orientation(lotGlobalProjected)); // apply in global coords
   TRY_TEST_LC(pDistributedLoads->Create(2, 8, loadDirFy, -0.2, -0.6, -3.0, 0.0, lotMember, &pDistributedLoad2));

   // joint loads
   CComPtr<IFem2dJointLoadCollection> pJointLoads;
   TRY_TEST_HR(pLoading1->get_JointLoads(&pJointLoads));
   CComPtr<IFem2dJointLoad> pJointLoad;
   TRY_TEST_LC(pJointLoads->Create(1, 3, 12.0, 0.0, 0.0, &pJointLoad));

   // put a point load at member 1
   CComPtr<IFem2dPointLoadCollection> pPointLoads;
   TRY_TEST_HR(pLoading1->get_PointLoads(&pPointLoads));
   CComPtr<IFem2dPointLoad> pPointLoad;
   TRY_TEST_LC(pPointLoads->Create(1, 1, -0.6, 4.0, -3.0, 0.0, lotMember, &pPointLoad));

   // member strain
   CComPtr<IFem2dMemberStrainCollection> pMemberStrains;
   TRY_TEST_HR(pLoading1->get_MemberStrains(&pMemberStrains));
   CComPtr<IFem2dMemberStrain> pMemberStrain;
   TRY_TEST_LC(pMemberStrains->Create(1, 7, 0.0, -1.0, 0.05, 0.0, &pMemberStrain));

   // Loading 2 - support Deflection case
   CComPtr<IFem2dLoading> pLoading2;
   TRY_TEST_LC(pLoadings->Create(2, &pLoading2));

   CComPtr<IFem2dJointDeflectionCollection> pJointDeflections;
   TRY_TEST_HR(pLoading2->get_JointDeflections(&pJointDeflections));
   CComPtr<IFem2dJointDeflection> pJointDeflection;
   TRY_TEST_LC(pJointDeflections->Create(1, 4, 0.4, -0.6, 0.0, &pJointDeflection));

   // now let's add some POI's 
   CComPtr<IFem2dPOICollection> pPOIs;
   TRY_TEST_HR(pmodel->get_POIs(&pPOIs));
   CComPtr<IFem2dPOI> pPOI35, pPOI1025;
   TRY_TEST_HR(pPOIs->Create(35,    3,  -0.5,  &pPOI35));
   TRY_TEST_HR(pPOIs->Create(1025, 10,  -0.25,  &pPOI1025));

   // set scope to release file after save
   {    
      // save model off to a file
      CComPtr<IStructuredSave2> psave;
      TRY_TEST_HR(psave.CoCreateInstance(CLSID_StructuredSave2));
      ATLASSERT(psave);

      TRY_TEST_HR(psave->Open(CComBSTR("Fem2dTest.xml")));

      IStructuredStorage2* pstor;
      TRY_TEST_HR(pmodel->QueryInterface(&pstor));
      TRY_TEST_HR(pstor->Save(psave));
      TRY_TEST_HR(psave->Close());
      pstor->Release();
   }

   // a place to store results from saved model
   TpComp cmp1, cmp2;

   // get results interface
   CComQIPtr<IFem2dModelResults> presults(pmodel);

   // loading 1
   Float64 fx, fy, mz;
   TRY_TEST_HR(presults->ComputeReactions(1, 1, &fx, &fy, &mz));
   cmp1.R_1.SetSaved(fx,fy,mz);

   TRY_TEST_HR(presults->ComputeReactions(1, 4, &fx, &fy, &mz));
   cmp1.R_4.SetSaved(fx,fy,mz);

   // look at  poi Deflections
   Float64 dx, dy, rz;
   TRY_TEST_HR(presults->ComputePOIDeflections(2, 35, lotGlobal, &dx, &dy, &rz));
   cmp1.PD_35.SetSaved(dx,dy,rz);
   TRY_TEST_HR(presults->ComputePOIDeflections(2, 1025, lotGlobal, &dx, &dy, &rz));
   cmp1.PD_1025.SetSaved(dx,dy,rz);

   // next look at poi forces
   TRY_TEST_HR(presults->ComputePOIForces(2, 35, mftLeft, lotMember, &fx, &fy, &mz));
   cmp1.PF_35.SetSaved(fx,fy,mz);
   TRY_TEST_HR(presults->ComputePOIForces(2, 1025, mftLeft, lotMember, &fx, &fy, &mz));
   cmp1.PF_1025.SetSaved(fx,fy,mz);

   // loading 2
   TRY_TEST_HR(presults->ComputeReactions(2, 1, &fx, &fy, &mz));
   cmp2.R_1.SetSaved(fx,fy,mz);

   TRY_TEST_HR(presults->ComputeReactions(2, 4, &fx, &fy, &mz));
   cmp2.R_4.SetSaved(fx,fy,mz);

   // look at  poi Deflections
   TRY_TEST_HR(presults->ComputePOIDeflections(2, 35, lotGlobal, &dx, &dy, &rz));
   cmp2.PD_35.SetSaved(dx,dy,rz);
   TRY_TEST_HR(presults->ComputePOIDeflections(2, 1025, lotGlobal, &dx, &dy, &rz));
   cmp2.PD_1025.SetSaved(dx,dy,rz);

   // next look at poi forces
   TRY_TEST_HR(presults->ComputePOIForces(2, 35, mftLeft, lotMember, &fx, &fy, &mz));
   cmp2.PF_35.SetSaved(fx,fy,mz);
   TRY_TEST_HR(presults->ComputePOIForces(2, 1025, mftLeft, lotMember, &fx, &fy, &mz));
   cmp2.PF_1025.SetSaved(fx,fy,mz);

   // now clear the model out and reload it
   pmodel->Clear();
 
   CComPtr<IStructuredLoad2> pload;
   TRY_TEST_HR(pload.CoCreateInstance(CLSID_StructuredLoad2));
   ATLASSERT(pload);

   TRY_TEST_HR(pload->Open(CComBSTR("Fem2dTest.xml")));

   IStructuredStorage2* pstor;
   TRY_TEST_HR(pmodel->get_StructuredStorage(&pstor));
   TRY_TEST_HR(pstor->Load(pload));
   pstor->Release();

    // loading 1
   TRY_TEST_HR(presults->ComputeReactions(1, 1, &fx, &fy, &mz));
   cmp1.R_1.SetLoaded(fx,fy,mz);

   TRY_TEST_HR(presults->ComputeReactions(1, 4, &fx, &fy, &mz));
   cmp1.R_4.SetLoaded(fx,fy,mz);

   // look at  poi Deflections
   TRY_TEST_HR(presults->ComputePOIDeflections(2, 35, lotGlobal, &dx, &dy, &rz));
   cmp1.PD_35.SetLoaded(dx,dy,rz);
   TRY_TEST_HR(presults->ComputePOIDeflections(2, 1025, lotGlobal, &dx, &dy, &rz));
   cmp1.PD_1025.SetLoaded(dx,dy,rz);

   // next look at poi forces
   TRY_TEST_HR(presults->ComputePOIForces(2, 35, mftLeft, lotMember, &fx, &fy, &mz));
   cmp1.PF_35.SetLoaded(fx,fy,mz);
   TRY_TEST_HR(presults->ComputePOIForces(2, 1025, mftLeft, lotMember, &fx, &fy, &mz));
   cmp1.PF_1025.SetLoaded(fx,fy,mz);

   // loading 2
   TRY_TEST_HR(presults->ComputeReactions(2, 1, &fx, &fy, &mz));
   cmp2.R_1.SetLoaded(fx,fy,mz);

   TRY_TEST_HR(presults->ComputeReactions(2, 4, &fx, &fy, &mz));
   cmp2.R_4.SetLoaded(fx,fy,mz);

   // look at  poi Deflections
   TRY_TEST_HR(presults->ComputePOIDeflections(2, 35, lotGlobal, &dx, &dy, &rz));
   cmp2.PD_35.SetLoaded(dx,dy,rz);
   TRY_TEST_HR(presults->ComputePOIDeflections(2, 1025, lotGlobal, &dx, &dy, &rz));
   cmp2.PD_1025.SetLoaded(dx,dy,rz);

   // next look at poi forces
   TRY_TEST_HR(presults->ComputePOIForces(2, 35, mftLeft, lotMember, &fx, &fy, &mz));
   cmp2.PF_35.SetLoaded(fx,fy,mz);
   TRY_TEST_HR(presults->ComputePOIForces(2, 1025, mftLeft, lotMember, &fx, &fy, &mz));
   cmp2.PF_1025.SetLoaded(fx,fy,mz);
   
   // this compares all results calculated
   TRY_TEST(cmp1.Equal(),true);
   TRY_TEST(cmp2.Equal(),true);

   ReleaseModel(pmodel);
}