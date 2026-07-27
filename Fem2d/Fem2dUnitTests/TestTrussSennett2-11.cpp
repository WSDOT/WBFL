///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
///////////////////////////////////////////////////////////////////////
// TestTrussSennett2-11.cpp
//
// Ported from F:\ARP\WBFL\Fem2d\Test\TestTrussSennett2-11.cpp
#include "pch.h"

namespace Fem2dUnitTests
{

// Problem taken from "Matrix Analysis of Structures", Robert F. Sennett,
// 1994, Chapter 2, Problem 11 - strange looking, symmetrical triangular
// truss with a non-symmetric load.
TEST_CLASS(TestTrussSennett2_11)
{
public:
   TEST_METHOD(SymmetricTriangularTruss_NonSymmetricLoad)
   {
      Fem2dModelFixture fixture;
      CComPtr<IFem2dModel>& pmodel = fixture.Model;

      CComPtr<IFem2dJointCollection> pJoints;
      ASSERT_HR(pmodel->get_Joints(&pJoints));

      CComPtr<IFem2dJoint> pJoint1, pJoint2, pJoint3, pJoint4;
      ASSERT_MC(fixture, pJoints->Create(1, 0.0, 0.0, &pJoint1));
      ASSERT_MC(fixture, pJoints->Create(2, 20.0 * 12.0, 40.0 * 12.0, &pJoint2));
      ASSERT_MC(fixture, pJoints->Create(3, 40.0 * 12.0, 0.0, &pJoint3));
      ASSERT_MC(fixture, pJoints->Create(4, 20.0 * 12.0, 15.0 * 12.0, &pJoint4));

      ASSERT_MC(fixture, pJoint1->Support());
      ASSERT_MC(fixture, pJoint2->Support());
      ASSERT_MC(fixture, pJoint2->ReleaseDof(jrtFx));
      ASSERT_MC(fixture, pJoint2->ReleaseDof(jrtFy));
      ASSERT_MC(fixture, pJoint3->Support());
      ASSERT_MC(fixture, pJoint3->ReleaseDof(jrtFx));
      ASSERT_MC(fixture, pJoint4->Support());
      ASSERT_MC(fixture, pJoint4->ReleaseDof(jrtFx));
      ASSERT_MC(fixture, pJoint4->ReleaseDof(jrtFy));

      CComPtr<IFem2dMemberCollection> pMembers;
      ASSERT_HR(pmodel->get_Members(&pMembers));

      Float64 E = 29.0e06;
      Float64 EA135 = E * 4.0;
      Float64 EA246 = E * 2.0;
      Float64 EI = 1.0e29; // dummy since all members are pinned
      CComPtr<IFem2dMember> pMember1, pMember2, pMember3, pMember4, pMember5, pMember6;
      ASSERT_MC(fixture, pMembers->Create(1, 1, 2, EA135, EI, &pMember1));
      ASSERT_MC(fixture, pMembers->Create(2, 1, 4, EA246, EI, &pMember2));
      ASSERT_MC(fixture, pMembers->Create(3, 1, 3, EA135, EI, &pMember3));
      ASSERT_MC(fixture, pMembers->Create(4, 2, 4, EA246, EI, &pMember4));
      ASSERT_MC(fixture, pMembers->Create(5, 2, 3, EA135, EI, &pMember5));
      ASSERT_MC(fixture, pMembers->Create(6, 4, 3, EA246, EI, &pMember6));

      // pin 'em
      ASSERT_MC(fixture, pMember1->ReleaseEnd(metStart, mbrReleaseMz));
      ASSERT_MC(fixture, pMember1->ReleaseEnd(metEnd, mbrReleaseMz));
      ASSERT_MC(fixture, pMember2->ReleaseEnd(metStart, mbrReleaseMz));
      ASSERT_MC(fixture, pMember2->ReleaseEnd(metEnd, mbrReleaseMz));
      ASSERT_MC(fixture, pMember3->ReleaseEnd(metStart, mbrReleaseMz));
      ASSERT_MC(fixture, pMember3->ReleaseEnd(metEnd, mbrReleaseMz));
      ASSERT_MC(fixture, pMember4->ReleaseEnd(metStart, mbrReleaseMz));
      ASSERT_MC(fixture, pMember4->ReleaseEnd(metEnd, mbrReleaseMz));
      ASSERT_MC(fixture, pMember5->ReleaseEnd(metStart, mbrReleaseMz));
      ASSERT_MC(fixture, pMember5->ReleaseEnd(metEnd, mbrReleaseMz));
      ASSERT_MC(fixture, pMember6->ReleaseEnd(metStart, mbrReleaseMz));
      ASSERT_MC(fixture, pMember6->ReleaseEnd(metEnd, mbrReleaseMz));

      CComPtr<IFem2dLoadingCollection> pLoadings;
      ASSERT_HR(pmodel->get_Loadings(&pLoadings));
      CComPtr<IFem2dLoading> pLoading;
      ASSERT_LC(fixture, pLoadings->Create(0, &pLoading));
      CComPtr<IFem2dJointLoadCollection> pJointLoads;
      ASSERT_HR(pLoading->get_JointLoads(&pJointLoads));

      CComPtr<IFem2dJointLoad> pJointLoad;
      ASSERT_LC(fixture, pJointLoads->Create(0, 2, -50000.0, -25000.0, 0.0, &pJointLoad));

      CComQIPtr<IFem2dModelResults> presults(pmodel);

      Float64 dx, dy, rz;
      ASSERT_HR(presults->ComputeJointDeflections(0, 1, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputeJointDeflections(0, 2, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, -0.611438));
      ASSERT_TRUE(IsEqual(dy, -0.0367688));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputeJointDeflections(0, 3, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, -.0662892));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputeJointDeflections(0, 4, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, -0.0331446));
      ASSERT_TRUE(IsEqual(dy, -0.0028779));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      Float64 sfx, sfy, smz, efx, efy, emz;
      ASSERT_HR(presults->ComputeMemberForces(0, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 66214.3, 0.1));
      ASSERT_TRUE(IsEqual(sfy, 0.0, 0.1));
      ASSERT_TRUE(IsEqual(smz, 0.0, 0.1));
      ASSERT_TRUE(IsEqual(efx, -66214.3, 0.1));
      ASSERT_TRUE(IsEqual(efy, 0.0, 0.1));
      ASSERT_TRUE(IsEqual(emz, 0.0, 0.1));
      ASSERT_HR(presults->ComputeMemberForces(0, 2, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 5460.2, 0.1));
      ASSERT_TRUE(IsEqual(sfy, 0.0, 0.1));
      ASSERT_TRUE(IsEqual(smz, 0.0, 0.1));
      ASSERT_TRUE(IsEqual(efx, -5460.2, 0.1));
      ASSERT_TRUE(IsEqual(efy, 0.0, 0.1));
      ASSERT_TRUE(IsEqual(emz, 0.0, 0.1));
      ASSERT_HR(presults->ComputeMemberForces(0, 3, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 16019.9, 0.1));
      ASSERT_TRUE(IsEqual(sfy, 0.0, 0.1));
      ASSERT_TRUE(IsEqual(smz, 0.0, 0.1));
      ASSERT_TRUE(IsEqual(efx, -16019.9, 0.1));
      ASSERT_TRUE(IsEqual(efy, 0.0, 0.1));
      ASSERT_TRUE(IsEqual(emz, 0.0, 0.1));
      ASSERT_HR(presults->ComputeMemberForces(0, 4, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 6552.2, 0.1));
      ASSERT_TRUE(IsEqual(sfy, 0.0, 0.1));
      ASSERT_TRUE(IsEqual(smz, 0.0, 0.1));
      ASSERT_TRUE(IsEqual(efx, -6552.2, 0.1));
      ASSERT_TRUE(IsEqual(efy, 0.0, 0.1));
      ASSERT_TRUE(IsEqual(emz, 0.0, 0.1));
      ASSERT_HR(presults->ComputeMemberForces(0, 5, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, -45589.0, 0.1));
      ASSERT_TRUE(IsEqual(sfy, 0.0, 0.1));
      ASSERT_TRUE(IsEqual(smz, 0.0, 0.1));
      ASSERT_TRUE(IsEqual(efx, 45589.0, 0.1));
      ASSERT_TRUE(IsEqual(efy, 0.0, 0.1));
      ASSERT_TRUE(IsEqual(emz, 0.0, 0.1));
      ASSERT_HR(presults->ComputeMemberForces(0, 6, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 5460.2, 0.1));
      ASSERT_TRUE(IsEqual(sfy, 0.0, 0.1));
      ASSERT_TRUE(IsEqual(smz, 0.0, 0.1));
      ASSERT_TRUE(IsEqual(efx, -5460.2, 0.1));
      ASSERT_TRUE(IsEqual(efy, 0.0, 0.1));
      ASSERT_TRUE(IsEqual(emz, 0.0, 0.1));

      Float64 fx, fy, mz;
      ASSERT_HR(presults->ComputeReactions(0, 1, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 50000.0, 0.1));
      ASSERT_TRUE(IsEqual(fy, 62500.0, 0.1));
      ASSERT_TRUE(IsEqual(mz, 0.0, 0.1));
      ASSERT_HR(presults->ComputeReactions(0, 3, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0, 0.1));
      ASSERT_TRUE(IsEqual(fy, -37500.0, 0.1));
      ASSERT_TRUE(IsEqual(mz, 0.0, 0.1));
   }
};
} // namespace Fem2dUnitTests
