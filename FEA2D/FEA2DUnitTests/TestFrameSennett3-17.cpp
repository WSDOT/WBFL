///////////////////////////////////////////////////////////////////////
// FEA2D - Two-dimensional Finite Element Analysis Engine
// Copyright � 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
///////////////////////////////////////////////////////////////////////
// TestFrameSennett3-17.cpp
//
// Mirrors Fem2d\Fem2dUnitTests\TestFrameSennett3-17.cpp.
#include "pch.h"

namespace FEA2DUnitTests
{

// Problem taken from "Matrix Analysis of Structures", Robert F. Sennett,
// 1994, Chapter 3, Problem 17 - bent frame with right leg shorter than left.
TEST_CLASS(TestFrameSennett3_17)
{
public:
   TEST_METHOD(BentFrame_UnequalLegLengths)
   {
      Model model;
      Joint& pJoint1 = model.CreateJoint(1, 0.0, 0.0);
      model.CreateJoint(2, 0.0, 20.0 * 12.0);
      model.CreateJoint(3, 20.0 * 12.0, 20.0 * 12.0);
      Joint& pJoint4 = model.CreateJoint(4, 20.0 * 12.0, 10.0 * 12.0);

      pJoint1.Support();
      pJoint1.ReleaseDof(JointReleaseType::Mz);
      pJoint4.Support();
      pJoint4.ReleaseDof(JointReleaseType::Mz);

      Float64 E = 29.0e06;
      Float64 EA1 = E * 20.0;
      Float64 EI1 = E * 200.0;
      Float64 EA2 = E * 30.0;
      Float64 EI2 = E * 300.0;
      Float64 EA3 = E * 10.0;
      Float64 EI3 = E * 100.0;
      model.CreateMember(1, 1, 2, EA1, EI1);
      model.CreateMember(2, 2, 3, EA2, EI2);
      model.CreateMember(3, 3, 4, EA3, EI3);

      Loading& pLoading = model.CreateLoading(0);
      pLoading.CreateJointLoad(0, 2, 20000.0, 0.0, 0.0);


      // get joint deflections (only the values the legacy test left
      // uncommented are asserted here)
      Float64 dx, dy, rz;
      model.ComputeJointDeflections(0, 1, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -.026293438));
      model.ComputeJointDeflections(0, 2, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dy, 0.005136639));
      model.ComputeJointDeflections(0, 3, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dy, -.005136639));
      model.ComputeJointDeflections(0, 4, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -0.0491296));

      Float64 sfx, sfy, smz, efx, efy, emz;
      model.ComputeMemberForces(0, 1, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, -12413.545, 0.001));
      ASSERT_TRUE(IsEqual(efy, -4827.09, 0.001));
      ASSERT_TRUE(IsEqual(emz, 1158501.813, 0.001));
      model.ComputeMemberForces(0, 2, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 15172.909, 0.001));
      ASSERT_TRUE(IsEqual(smz, -1158501.813, 0.001));
      ASSERT_TRUE(IsEqual(emz, -1820749.093, 0.001));
      model.ComputeMemberForces(0, 3, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(smz, 1820749.093, 0.001));
      ASSERT_TRUE(IsEqual(efy, -15172.909, 0.001));

      Float64 fx, fy, mz;
      model.ComputeReactions(0, 1, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -4827.090, 0.001));
      ASSERT_TRUE(IsEqual(fy, -12413.545, 0.001));
      ASSERT_TRUE(IsEqual(mz, 0.0, 0.001));
      model.ComputeReactions(0, 4, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -15172.909, 0.001));
      ASSERT_TRUE(IsEqual(fy, 12413.545, 0.001));
      ASSERT_TRUE(IsEqual(mz, 0.0, 0.001));

      model.Clear();
   }
};
} // namespace FEA2DUnitTests
