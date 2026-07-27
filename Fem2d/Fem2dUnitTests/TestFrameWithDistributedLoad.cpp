///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
///////////////////////////////////////////////////////////////////////
// TestFrameWithDistributedLoad.cpp
//
// Ported from F:\ARP\WBFL\Fem2d\Test\TestFrameWithDistributedLoad.cpp
//
//              w
//         ============ 3
//                    /o
//                  /  |
//                /    |
//              /      |
//            /        |
//          /          |
//        2o-----------o4
//         |           |
//         |           |
//         |           |
//         |           |
//        1o           o5
//        ===         ===
//
// Frame with trapezoidal load, made up and verified using DrFrame.
#include "pch.h"

namespace Fem2dUnitTests
{

TEST_CLASS(TestFrameWithDistributedLoad)
{
public:
   TEST_METHOD(SlopedFrame_TrapezoidalLoad_OrientationVariants)
   {
      Fem2dModelFixture fixture;
      CComPtr<IFem2dModel>& pmodel = fixture.Model;

      CComPtr<IFem2dJointCollection> pJoints;
      ASSERT_HR(pmodel->get_Joints(&pJoints));

      CComPtr<IFem2dJoint> pJoint1, pJoint2, pJoint3, pJoint4, pJoint5;
      ASSERT_MC(fixture, pJoints->Create(1, 0.0, 0.0, &pJoint1));
      ASSERT_MC(fixture, pJoints->Create(2, 0.0, 144.0, &pJoint2));
      ASSERT_MC(fixture, pJoints->Create(3, 144.0, 288.0, &pJoint3));
      ASSERT_MC(fixture, pJoints->Create(4, 144.0, 144.0, &pJoint4));
      ASSERT_MC(fixture, pJoints->Create(5, 144.0, 0.0, &pJoint5));

      ASSERT_MC(fixture, pJoint1->Support());
      ASSERT_MC(fixture, pJoint5->Support());
      ASSERT_MC(fixture, pJoint1->ReleaseDof(jrtMz));
      ASSERT_MC(fixture, pJoint5->ReleaseDof(jrtMz));

      CComPtr<IFem2dMemberCollection> pMembers;
      ASSERT_HR(pmodel->get_Members(&pMembers));

      Float64 E = 29000;
      Float64 A = 10;
      Float64 I = 250;
      CComPtr<IFem2dMember> pMember1, pMember2, pMember3, pMember4, pMember5;
      ASSERT_MC(fixture, pMembers->Create(1, 1, 2, E * A, E * I, &pMember1));
      ASSERT_MC(fixture, pMembers->Create(2, 2, 3, E * A, E * I, &pMember2));
      ASSERT_MC(fixture, pMembers->Create(3, 3, 4, E * A, E * I, &pMember3));
      ASSERT_MC(fixture, pMembers->Create(4, 2, 4, E * A, E * I, &pMember4));
      ASSERT_MC(fixture, pMembers->Create(5, 4, 5, E * A, E * I, &pMember5));

      CComPtr<IFem2dLoadingCollection> pLoadings;
      ASSERT_HR(pmodel->get_Loadings(&pLoadings));
      CComPtr<IFem2dLoading> pLoading0;
      ASSERT_LC(fixture, pLoadings->Create(0, &pLoading0));
      CComPtr<IFem2dDistributedLoadCollection> pDistributedLoads;
      ASSERT_HR(pLoading0->get_DistributedLoads(&pDistributedLoads));
      CComPtr<IFem2dDistributedLoad> pDistributedLoad;
      ASSERT_LC(fixture, pDistributedLoads->Create(1, 2, loadDirFy, 0.0, -1.0, -0.5, -1.0, lotMember, &pDistributedLoad));
      ASSERT_LC(fixture, pDistributedLoad->put_Orientation(lotGlobal)); // apply in global coords

      CComPtr<IFem2dPOICollection> pPOIs;
      ASSERT_HR(pmodel->get_POIs(&pPOIs));

      CComPtr<IFem2dPOI> pPOI22;
      ASSERT_HR(pPOIs->Create(22, 2, -0.5, &pPOI22));

      CComQIPtr<IFem2dModelResults> presults(pmodel);

      Float64 dx, dy, rz;
      ASSERT_HR(presults->ComputeJointDeflections(0, 1, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_HR(presults->ComputeJointDeflections(0, 2, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.47518504376467));
      ASSERT_TRUE(IsEqual(dy, -0.033707048769389));
      ASSERT_HR(presults->ComputeJointDeflections(0, 3, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.50069452024221));
      ASSERT_TRUE(IsEqual(dy, -0.077478110675579));
      ASSERT_HR(presults->ComputeJointDeflections(0, 4, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.48025051552884));
      ASSERT_TRUE(IsEqual(dy, -0.042133810961736));

      Float64 sfx, sfy, smz, efx, efy, emz;
      ASSERT_HR(presults->ComputeMemberForces(0, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 67.882250993909));
      ASSERT_TRUE(IsEqual(sfy, -2.1305089245136));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, -67.882250993909));
      ASSERT_TRUE(IsEqual(efy, 2.1305089245136));
      ASSERT_TRUE(IsEqual(emz, -306.79328512995));
      ASSERT_HR(presults->ComputeMemberForces(0, 2, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 66.388401994131));
      ASSERT_TRUE(IsEqual(sfy, 48.948594378857));
      ASSERT_TRUE(IsEqual(smz, 1494.0302142683));
      ASSERT_TRUE(IsEqual(efx, 41.611598005869));
      ASSERT_TRUE(IsEqual(efy, 59.051405621143));
      ASSERT_TRUE(IsEqual(emz, -1300.8520491173));
      ASSERT_HR(presults->ComputeMemberForces(0, 3, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 71.179492479266));
      ASSERT_TRUE(IsEqual(sfy, 12.331806227349));
      ASSERT_TRUE(IsEqual(smz, 1300.8520491173));
      ASSERT_TRUE(IsEqual(efx, -71.179492479266));
      ASSERT_TRUE(IsEqual(efy, -12.331806227349));
      ASSERT_TRUE(IsEqual(emz, 474.92804762087));

      Float64 fx, fy, mz;
      ASSERT_HR(presults->ComputeReactions(0, 1, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 2.1305089245136));
      ASSERT_TRUE(IsEqual(fy, 67.882250993909));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputeReactions(0, 5, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -2.1305089245135));
      ASSERT_TRUE(IsEqual(fy, 84.852813742386));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      ASSERT_HR(presults->ComputePOIDeflections(0, 22, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.29623553109350)); // close, but not exact to drframe
      ASSERT_TRUE(IsEqual(dy, -1.0232793921774));
      ASSERT_HR(presults->ComputePOIDeflections(0, 22, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.93303795012174));
      ASSERT_TRUE(IsEqual(dy, -0.51409764439251));

      ASSERT_HR(presults->ComputePOIForces(0, 22, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -21.388401994131));
      ASSERT_TRUE(IsEqual(fy, -3.9485943788572));
      ASSERT_TRUE(IsEqual(mz, 1351.7900335605));

      // add a new loading with a horizontally applied load
      CComPtr<IFem2dLoading> pLoading1;
      ASSERT_HR(pLoadings->Create(1, &pLoading1));
      CComPtr<IFem2dDistributedLoadCollection> pDistributedLoads1;
      ASSERT_HR(pLoading1->get_DistributedLoads(&pDistributedLoads1));
      CComPtr<IFem2dDistributedLoad> pDistributedLoad1;
      ASSERT_LC(fixture, pDistributedLoads1->Create(1, 2, loadDirFx, 0.0, -1.0, -0.5, -1.0, lotMember, &pDistributedLoad1));
      ASSERT_LC(fixture, pDistributedLoad1->put_Orientation(lotGlobal)); // apply in global coords

      ASSERT_HR(presults->ComputeReactions(1, 1, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 73.282046829267));
      ASSERT_TRUE(IsEqual(fy, 237.58787847868));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputeReactions(1, 5, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 79.453017907024));
      ASSERT_TRUE(IsEqual(fy, -237.58787847868));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      ASSERT_HR(presults->ComputeMemberForces(1, 2, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 196.34212817867));
      ASSERT_TRUE(IsEqual(sfy, -33.642294746207));
      ASSERT_TRUE(IsEqual(smz, 1417.8934017460));
      ASSERT_TRUE(IsEqual(efx, -88.342128178674));
      ASSERT_TRUE(IsEqual(efy, -74.357705253793));
      ASSERT_TRUE(IsEqual(emz, 1506.0066534574));

      ASSERT_HR(presults->ComputePOIForces(1, 22, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -151.34212817867));
      ASSERT_TRUE(IsEqual(fy, -11.357705253793));
      ASSERT_TRUE(IsEqual(mz, -2705.1745393975));

      // next try global projected load in Y
      CComPtr<IFem2dLoading> pLoading2;
      ASSERT_LC(fixture, pLoadings->Create(2, &pLoading2));
      CComPtr<IFem2dDistributedLoadCollection> pDistributedLoads2;
      ASSERT_HR(pLoading2->get_DistributedLoads(&pDistributedLoads2));
      CComPtr<IFem2dDistributedLoad> pDistributedLoad2;
      ASSERT_LC(fixture, pDistributedLoads2->Create(1, 2, loadDirFy, 0.0, -1.0, -0.5, -1.0, lotMember, &pDistributedLoad2));
      ASSERT_LC(fixture, pDistributedLoad2->put_Orientation(lotGlobalProjected)); // apply in global coords

      ASSERT_HR(presults->ComputeReactions(2, 1, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 1.5064973079020));
      ASSERT_TRUE(IsEqual(fy, 48.000000000000));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputeReactions(2, 5, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -1.5064973079019));
      ASSERT_TRUE(IsEqual(fy, 60.000000000000));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      ASSERT_HR(presults->ComputeMemberForces(2, 2, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 46.943689242188));
      ASSERT_TRUE(IsEqual(sfy, 34.611883014840));
      ASSERT_TRUE(IsEqual(smz, 1056.4388958067));
      ASSERT_TRUE(IsEqual(efx, 29.423843125959));
      ASSERT_TRUE(IsEqual(efy, 41.755649353307));
      ASSERT_TRUE(IsEqual(emz, -919.84130525128));

      ASSERT_HR(presults->ComputePOIForces(2, 22, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -15.123884088794));
      ASSERT_TRUE(IsEqual(fy, -2.7920778614451));
      ASSERT_TRUE(IsEqual(mz, 955.85989947101));

      // next try global projected load in X
      CComPtr<IFem2dLoading> pLoading3;
      ASSERT_LC(fixture, pLoadings->Create(3, &pLoading3));
      CComPtr<IFem2dDistributedLoadCollection> pDistributedLoads3;
      ASSERT_HR(pLoading3->get_DistributedLoads(&pDistributedLoads3));
      CComPtr<IFem2dDistributedLoad> pDistributedLoad3;
      ASSERT_LC(fixture, pDistributedLoads3->Create(1, 2, loadDirFx, 0.0, -1.0, -0.5, -1.0, lotMember, &pDistributedLoad3));
      ASSERT_LC(fixture, pDistributedLoad3->put_Orientation(lotGlobalProjected)); // apply in global coords

      ASSERT_HR(presults->ComputeReactions(3, 1, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 51.818232252205));
      ASSERT_TRUE(IsEqual(fy, 168.00000000000));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputeReactions(3, 5, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 56.181767747793));
      ASSERT_TRUE(IsEqual(fy, -168.00000000000));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      ASSERT_HR(presults->ComputeMemberForces(3, 2, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 138.83485026774));
      ASSERT_TRUE(IsEqual(sfy, -23.788694749719));
      ASSERT_TRUE(IsEqual(smz, 1002.6020393742));
      ASSERT_TRUE(IsEqual(efx, -62.467317899593));
      ASSERT_TRUE(IsEqual(efy, -52.578837618428));
      ASSERT_TRUE(IsEqual(emz, 1064.9075171718));

      ASSERT_HR(presults->ComputePOIForces(3, 22, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -107.01504511435));
      ASSERT_TRUE(IsEqual(fy, -8.0311104036752));
      ASSERT_TRUE(IsEqual(mz, -1912.8472611011));
   }
};
} // namespace Fem2dUnitTests
