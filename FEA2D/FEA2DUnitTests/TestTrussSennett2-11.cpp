///////////////////////////////////////////////////////////////////////
// FEA2D - Two-dimensional Finite Element Analysis Engine
// Copyright � 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
///////////////////////////////////////////////////////////////////////
// TestTrussSennett2-11.cpp
//
// Mirrors Fem2d\Fem2dUnitTests\TestTrussSennett2-11.cpp.
#include "pch.h"

namespace FEA2DUnitTests
{

// Problem taken from "Matrix Analysis of Structures", Robert F. Sennett,
// 1994, Chapter 2, Problem 11 - strange looking, symmetrical triangular
// truss with a non-symmetric load.
TEST_CLASS(TestTrussSennett2_11)
{
public:
   TEST_METHOD(SymmetricTriangularTruss_NonSymmetricLoad)
   {
      Model model;
      model.CreateJoint(1, 0.0, 0.0);
      Joint& pJoint2 = model.CreateJoint(2, 20.0 * 12.0, 40.0 * 12.0);
      Joint& pJoint3 = model.CreateJoint(3, 40.0 * 12.0, 0.0);
      Joint& pJoint4 = model.CreateJoint(4, 20.0 * 12.0, 15.0 * 12.0);

      model.FindJoint(1)->Support();
      pJoint2.Support();
      pJoint2.ReleaseDof(JointReleaseType::Fx);
      pJoint2.ReleaseDof(JointReleaseType::Fy);
      pJoint3.Support();
      pJoint3.ReleaseDof(JointReleaseType::Fx);
      pJoint4.Support();
      pJoint4.ReleaseDof(JointReleaseType::Fx);
      pJoint4.ReleaseDof(JointReleaseType::Fy);

      Float64 E = 29.0e06;
      Float64 EA135 = E * 4.0;
      Float64 EA246 = E * 2.0;
      Float64 EI = 1.0e29; // dummy since all members are pinned
      Member& pMember1 = model.CreateMember(1, 1, 2, EA135, EI);
      Member& pMember2 = model.CreateMember(2, 1, 4, EA246, EI);
      Member& pMember3 = model.CreateMember(3, 1, 3, EA135, EI);
      Member& pMember4 = model.CreateMember(4, 2, 4, EA246, EI);
      Member& pMember5 = model.CreateMember(5, 2, 3, EA135, EI);
      Member& pMember6 = model.CreateMember(6, 4, 3, EA246, EI);

      // pin 'em
      for (Member* mbr : { &pMember1, &pMember2, &pMember3, &pMember4, &pMember5, &pMember6 })
      {
         mbr->ReleaseEnd(MemberEndType::Start, MemberReleaseType::Mz);
         mbr->ReleaseEnd(MemberEndType::End, MemberReleaseType::Mz);
      }

      Loading& pLoading = model.CreateLoading(0);
      pLoading.CreateJointLoad(0, 2, -50000.0, -25000.0, 0.0);


      Float64 dx, dy, rz;
      model.ComputeJointDeflections(0, 1, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0)); ASSERT_TRUE(IsEqual(dy, 0.0)); ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputeJointDeflections(0, 2, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, -0.611438)); ASSERT_TRUE(IsEqual(dy, -0.0367688)); ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputeJointDeflections(0, 3, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, -.0662892)); ASSERT_TRUE(IsEqual(dy, 0.0)); ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputeJointDeflections(0, 4, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, -0.0331446)); ASSERT_TRUE(IsEqual(dy, -0.0028779)); ASSERT_TRUE(IsEqual(rz, 0.0));

      Float64 sfx, sfy, smz, efx, efy, emz;
      model.ComputeMemberForces(0, 1, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 66214.3, 0.1)); ASSERT_TRUE(IsEqual(efx, -66214.3, 0.1));
      model.ComputeMemberForces(0, 2, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 5460.2, 0.1)); ASSERT_TRUE(IsEqual(efx, -5460.2, 0.1));
      model.ComputeMemberForces(0, 3, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 16019.9, 0.1)); ASSERT_TRUE(IsEqual(efx, -16019.9, 0.1));
      model.ComputeMemberForces(0, 4, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 6552.2, 0.1)); ASSERT_TRUE(IsEqual(efx, -6552.2, 0.1));
      model.ComputeMemberForces(0, 5, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, -45589.0, 0.1)); ASSERT_TRUE(IsEqual(efx, 45589.0, 0.1));
      model.ComputeMemberForces(0, 6, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 5460.2, 0.1)); ASSERT_TRUE(IsEqual(efx, -5460.2, 0.1));

      Float64 fx, fy, mz;
      model.ComputeReactions(0, 1, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 50000.0, 0.1)); ASSERT_TRUE(IsEqual(fy, 62500.0, 0.1)); ASSERT_TRUE(IsEqual(mz, 0.0, 0.1));
      model.ComputeReactions(0, 3, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0, 0.1)); ASSERT_TRUE(IsEqual(fy, -37500.0, 0.1)); ASSERT_TRUE(IsEqual(mz, 0.0, 0.1));
   }
};
} // namespace FEA2DUnitTests
