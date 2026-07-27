///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
///////////////////////////////////////////////////////////////////////
// TestBarWithDistributedLoad.cpp
//
// Ported from F:\ARP\WBFL\Fem2d\Test\TestBarWithDistributedLoad.cpp
#include "pch.h"

namespace Fem2dUnitTests
{

TEST_CLASS(TestBarWithDistributedLoad)
{
public:
   TEST_METHOD(AxialTrapezoidalLoad_CantileverThenFixFix)
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
      *////////////////////////////////////////////////////
      Fem2dModelFixture fixture;
      CComPtr<IFem2dModel>& pmodel = fixture.Model;

      CComPtr<IFem2dJointCollection> pJoints;
      ASSERT_HR(pmodel->get_Joints(&pJoints));

      CComPtr<IFem2dJoint> pJoint0, pJoint8;
      ASSERT_MC(fixture, pJoints->Create(0, 0.0, 0.0, &pJoint0));
      ASSERT_MC(fixture, pJoints->Create(8, 8.0, 0.0, &pJoint8));

      ASSERT_MC(fixture, pJoint0->Support());

      CComPtr<IFem2dMemberCollection> pMembers;
      ASSERT_HR(pmodel->get_Members(&pMembers));

      CComPtr<IFem2dMember> pMember1;
      ASSERT_MC(fixture, pMembers->Create(1, 0, 8, 3.0, 7.0, &pMember1));

      CComPtr<IFem2dLoadingCollection> pLoadings;
      ASSERT_HR(pmodel->get_Loadings(&pLoadings));
      CComPtr<IFem2dLoading> pLoading;
      ASSERT_LC(fixture, pLoadings->Create(0, &pLoading));
      CComPtr<IFem2dDistributedLoadCollection> pDistributedLoads;
      ASSERT_HR(pLoading->get_DistributedLoads(&pDistributedLoads));
      CComPtr<IFem2dDistributedLoad> pDistributedLoad;
      ASSERT_LC(fixture, pDistributedLoads->Create(0, 1, loadDirFx, 2.5, 5.0, 2.0, 4.0, lotMember, &pDistributedLoad));

      CComPtr<IFem2dPOICollection> pPOIs;
      ASSERT_HR(pmodel->get_POIs(&pPOIs));

      CComPtr<IFem2dPOI> pPOI10, pPOI15, pPOI12;
      ASSERT_HR(pPOIs->Create(10, 1, 0.0, &pPOI10));
      ASSERT_HR(pPOIs->Create(15, 1, -.25, &pPOI15));
      ASSERT_HR(pPOIs->Create(12, 1, -0.5, &pPOI12));

      CComQIPtr<IFem2dModelResults> presults(pmodel);

      Float64 dx, dy, rz;
      ASSERT_HR(presults->ComputeJointDeflections(0, 0, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputeJointDeflections(0, 8, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 9.7222222));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      Float64 sfx, sfy, smz, efx, efy, emz;
      ASSERT_HR(presults->ComputeMemberForces(0, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, -7.5));
      ASSERT_TRUE(IsEqual(sfy, 0.0));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 0.0));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      Float64 fx, fy, mz;
      ASSERT_HR(presults->ComputeReactions(0, 0, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -7.5));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputeReactions(0, 8, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      Float64 sdx, sdy, srz, edx, edy, erz;
      ASSERT_HR(presults->ComputeMemberDeflections(0, 1, &sdx, &sdy, &srz, &edx, &edy, &erz));
      ASSERT_TRUE(IsEqual(sdx, 0.0));
      ASSERT_TRUE(IsEqual(sdy, 0.0));
      ASSERT_TRUE(IsEqual(srz, 0.0));
      ASSERT_TRUE(IsEqual(edx, 9.7222222));
      ASSERT_TRUE(IsEqual(edy, 0.0));
      ASSERT_TRUE(IsEqual(erz, 0.0));

      CComPtr<IFem2dPOI> pPOI20, pPOI25, pPOI22;
      ASSERT_HR(pPOIs->Create(20, 1, 4.0, &pPOI20));
      ASSERT_HR(pPOIs->Create(25, 1, 6.0, &pPOI25));
      ASSERT_HR(pPOIs->Create(22, 1, 8.0, &pPOI22));

      ASSERT_HR(presults->ComputePOIDeflections(0, 10, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(0, 15, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 5.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(0, 12, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 9.1));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(0, 20, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 9.1));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(0, 25, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 9.7222222));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(0, 22, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 9.7222222));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      ASSERT_HR(presults->ComputePOIForces(0, 10, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 7.5));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(0, 10, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -7.5));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      ASSERT_HR(presults->ComputePOIForces(0, 15, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 7.5));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(0, 15, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -7.5));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      ASSERT_HR(presults->ComputePOIForces(0, 12, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 3.6));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(0, 12, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -3.6));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      ASSERT_HR(presults->ComputePOIForces(0, 20, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 3.6));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(0, 20, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -3.6));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      ASSERT_HR(presults->ComputePOIForces(0, 25, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(0, 25, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      ASSERT_HR(presults->ComputePOIForces(0, 22, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(0, 22, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      ///////////////////////////////////////////////
      // try a fix-fix orientation
      ASSERT_MC(fixture, pJoint8->Support());

      ASSERT_HR(presults->ComputeJointDeflections(0, 0, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputeJointDeflections(0, 8, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      ASSERT_HR(presults->ComputeMemberForces(0, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, -3.85416667));
      ASSERT_TRUE(IsEqual(sfy, 0.0));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, -3.645833333));
      ASSERT_TRUE(IsEqual(efy, 0.0));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      ASSERT_HR(presults->ComputeReactions(0, 0, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -3.85416667));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputeReactions(0, 8, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -3.645833333));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      ASSERT_HR(presults->ComputeMemberDeflections(0, 1, &sdx, &sdy, &srz, &edx, &edy, &erz));
      ASSERT_TRUE(IsEqual(sdx, 0.0));
      ASSERT_TRUE(IsEqual(sdy, 0.0));
      ASSERT_TRUE(IsEqual(srz, 0.0));
      ASSERT_TRUE(IsEqual(edx, 0.0));
      ASSERT_TRUE(IsEqual(edy, 0.0));
      ASSERT_TRUE(IsEqual(erz, 0.0));

      ASSERT_HR(presults->ComputePOIDeflections(0, 10, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(0, 15, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 2.56944444));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(0, 12, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 4.238888889));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(0, 20, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 4.238888889));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(0, 25, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 2.430555556));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(0, 22, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      ASSERT_HR(presults->ComputePOIForces(0, 10, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 3.85416667));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(0, 10, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -3.85416667));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      ASSERT_HR(presults->ComputePOIForces(0, 15, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 3.85416667));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(0, 15, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -3.85416667));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      ASSERT_HR(presults->ComputePOIForces(0, 12, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -0.04583333));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(0, 12, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.04583333));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      ASSERT_HR(presults->ComputePOIForces(0, 20, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -0.04583333));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(0, 20, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.04583333));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      ASSERT_HR(presults->ComputePOIForces(0, 25, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -3.6458333333333));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(0, 25, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 3.6458333333333));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      ASSERT_HR(presults->ComputePOIForces(0, 22, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -3.6458333333333));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(0, 22, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 3.6458333333333));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
   }
};
} // namespace Fem2dUnitTests
