///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
///////////////////////////////////////////////////////////////////////
// TestFrameSennett3-17.cpp
//
// Ported from F:\ARP\WBFL\Fem2d\Test\TestFrameSennett3-17.cpp
#include "pch.h"

namespace Fem2dUnitTests
{

// Problem taken from "Matrix Analysis of Structures", Robert F. Sennett,
// 1994, Chapter 3, Problem 17 - bent frame with right leg shorter than left.
TEST_CLASS(TestFrameSennett3_17)
{
public:
   TEST_METHOD(BentFrame_UnequalLegLengths)
   {
      Fem2dModelFixture fixture;
      CComPtr<IFem2dModel>& pmodel = fixture.Model;

      CComPtr<IFem2dJointCollection> pJoints;
      ASSERT_HR(pmodel->get_Joints(&pJoints));

      CComPtr<IFem2dJoint> pJoint1, pJoint2, pJoint3, pJoint4;
      ASSERT_MC(fixture, pJoints->Create(1, 0.0, 0.0, &pJoint1));
      ASSERT_MC(fixture, pJoints->Create(2, 0.0, 20.0 * 12.0, &pJoint2));
      ASSERT_MC(fixture, pJoints->Create(3, 20.0 * 12.0, 20.0 * 12.0, &pJoint3));
      ASSERT_MC(fixture, pJoints->Create(4, 20.0 * 12.0, 10.0 * 12.0, &pJoint4));

      ASSERT_MC(fixture, pJoint1->Support());
      ASSERT_MC(fixture, pJoint1->ReleaseDof(jrtMz));
      ASSERT_MC(fixture, pJoint4->Support());
      ASSERT_MC(fixture, pJoint4->ReleaseDof(jrtMz));

      CComPtr<IFem2dMemberCollection> pMembers;
      ASSERT_HR(pmodel->get_Members(&pMembers));

      Float64 E = 29.0e06;
      Float64 EA1 = E * 20.0;
      Float64 EI1 = E * 200.0;
      Float64 EA2 = E * 30.0;
      Float64 EI2 = E * 300.0;
      Float64 EA3 = E * 10.0;
      Float64 EI3 = E * 100.0;
      CComPtr<IFem2dMember> pMember1, pMember2, pMember3;
      ASSERT_MC(fixture, pMembers->Create(1, 1, 2, EA1, EI1, &pMember1));
      ASSERT_MC(fixture, pMembers->Create(2, 2, 3, EA2, EI2, &pMember2));
      ASSERT_MC(fixture, pMembers->Create(3, 3, 4, EA3, EI3, &pMember3));

      CComPtr<IFem2dLoadingCollection> pLoadings;
      ASSERT_HR(pmodel->get_Loadings(&pLoadings));
      CComPtr<IFem2dLoading> pLoading;
      ASSERT_LC(fixture, pLoadings->Create(0, &pLoading));
      CComPtr<IFem2dJointLoadCollection> pJointLoads;
      ASSERT_HR(pLoading->get_JointLoads(&pJointLoads));

      CComPtr<IFem2dJointLoad> pJointLoad;
      ASSERT_LC(fixture, pJointLoads->Create(0, 2, 20000.0, 0.0, 0.0, &pJointLoad));

      CComQIPtr<IFem2dModelResults> presults(pmodel);

      // get joint deflections (only the values the legacy test left
      // uncommented are asserted here)
      Float64 dx, dy, rz;
      ASSERT_HR(presults->ComputeJointDeflections(0, 1, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -.026293438));
      ASSERT_HR(presults->ComputeJointDeflections(0, 2, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dy, 0.005136639));
      ASSERT_HR(presults->ComputeJointDeflections(0, 3, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dy, -.005136639));
      ASSERT_HR(presults->ComputeJointDeflections(0, 4, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -0.0491296));

      Float64 sfx, sfy, smz, efx, efy, emz;
      ASSERT_HR(presults->ComputeMemberForces(0, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, -12413.545, 0.001));
      ASSERT_TRUE(IsEqual(efy, -4827.09, 0.001));
      ASSERT_TRUE(IsEqual(emz, 1158501.813, 0.001));
      ASSERT_HR(presults->ComputeMemberForces(0, 2, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 15172.909, 0.001));
      ASSERT_TRUE(IsEqual(smz, -1158501.813, 0.001));
      ASSERT_TRUE(IsEqual(emz, -1820749.093, 0.001));
      ASSERT_HR(presults->ComputeMemberForces(0, 3, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(smz, 1820749.093, 0.001));
      ASSERT_TRUE(IsEqual(efy, -15172.909, 0.001));

      Float64 fx, fy, mz;
      ASSERT_HR(presults->ComputeReactions(0, 1, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -4827.090, 0.001));
      ASSERT_TRUE(IsEqual(fy, -12413.545, 0.001));
      ASSERT_TRUE(IsEqual(mz, 0.0, 0.001));
      ASSERT_HR(presults->ComputeReactions(0, 4, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -15172.909, 0.001));
      ASSERT_TRUE(IsEqual(fy, 12413.545, 0.001));
      ASSERT_TRUE(IsEqual(mz, 0.0, 0.001));

      ASSERT_HR(pmodel->Clear());
   }
};
} // namespace Fem2dUnitTests
