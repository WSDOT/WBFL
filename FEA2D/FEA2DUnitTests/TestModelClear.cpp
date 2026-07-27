///////////////////////////////////////////////////////////////////////
// FEA2D - Two-dimensional Finite Element Analysis Engine
// Copyright � 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
///////////////////////////////////////////////////////////////////////
// TestModelClear.cpp
//
// Mirrors Fem2d\Fem2dUnitTests\TestModelClear.cpp.
#include "pch.h"

namespace FEA2DUnitTests
{

TEST_CLASS(TestModelClear)
{
public:
   TEST_METHOD(EquilibriumTolerance_RoundTrip)
   {
      Model model;

      model.SetForceEquilibriumTolerance(0.001);
      model.SetMomentEquilibriumTolerance(0.002);

      ASSERT_TRUE(IsEqual(model.GetForceEquilibriumTolerance(), 0.001));
      ASSERT_TRUE(IsEqual(model.GetMomentEquilibriumTolerance(), 0.002));

      // change and re-verify, to be sure Set isn't a no-op
      model.SetForceEquilibriumTolerance(0.5);
      ASSERT_TRUE(IsEqual(model.GetForceEquilibriumTolerance(), 0.5));
   }

   TEST_METHOD(Clear_EmptiesAllCollectionsAndModelRemainsUsable)
   {
      Model model;
      Joint& pJoint1 = model.CreateJoint(1, 0.0, 0.0);
      Joint& pJoint2 = model.CreateJoint(2, 10.0, 0.0);
      pJoint1.Support();
      pJoint2.Support();

      model.CreateMember(1, 1, 2, 100.0, 100.0);

      Loading& pLoading = model.CreateLoading(0);
      pLoading.CreatePointLoad(0, 1, 4.0, 0.0, -1.0, 0.0, LoadOrientation::Global);

      model.CreatePOI(1, 1, 5.0);

      ASSERT_EQ(model.GetJointCount(), 2u);
      ASSERT_EQ(model.GetMemberCount(), 1u);
      ASSERT_EQ(model.GetLoadingCount(), 1u);
      ASSERT_EQ(model.GetPOICount(), 1u);

      model.Clear();

      ASSERT_EQ(model.GetJointCount(), 0u);
      ASSERT_EQ(model.GetMemberCount(), 0u);
      ASSERT_EQ(model.GetLoadingCount(), 0u);
      ASSERT_EQ(model.GetPOICount(), 0u);

      // model must remain usable after Clear() - rebuild a minimal stable
      // cantilever and confirm it still analyzes correctly
      Joint& pNewJoint1 = model.CreateJoint(1, 0.0, 0.0);
      model.CreateJoint(2, 10.0, 0.0);
      pNewJoint1.Support();

      model.CreateMember(1, 1, 2, 100.0, 100.0);

      Loading& pNewLoading = model.CreateLoading(0);
      pNewLoading.CreateJointLoad(0, 2, 0.0, -10.0, 0.0);

      Float64 rx, ry, rz;
      model.ComputeReactions(0, 1, &rx, &ry, &rz);
      ASSERT_TRUE(IsEqual(ry, 10.0));
   }
};
} // namespace FEA2DUnitTests
