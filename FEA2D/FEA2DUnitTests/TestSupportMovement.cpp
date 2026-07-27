///////////////////////////////////////////////////////////////////////
// FEA2D - Two-dimensional Finite Element Analysis Engine
// Copyright � 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
///////////////////////////////////////////////////////////////////////
// TestSupportMovement.cpp
//
// Mirrors Fem2d\Fem2dUnitTests\TestSupportMovement.cpp.
#include "pch.h"

namespace FEA2DUnitTests
{

TEST_CLASS(TestSupportMovement)
{
public:
   // Problem taken from "Matrix Analysis of Structures", Robert F. Sennett,
   // 1994, Chapter 1, Example 1.6 - two-node bar with end support settlement.
   TEST_METHOD(BarTwoMembers_EndSupportSettlement)
   {
      Model model;
      model.CreateJoint(1, 0.0, 0.0);
      model.CreateJoint(2, 1.0, 0.0);
      Joint& pJoint3 = model.CreateJoint(3, 2.0, 0.0);

      model.FindJoint(1)->Support();
      pJoint3.Support();

      Float64 EA1 = 5800.0;
      Float64 EA2 = 2900.0;
      Float64 EI = EA1; // whatever
      model.CreateMember(1, 1, 2, EA1, EI);
      model.CreateMember(2, 2, 3, EA2, EI);

      Loading& pLoading = model.CreateLoading(0);

      // apply 25k load to joint 2
      pLoading.CreateJointLoad(0, 2, 25.0, 0.0, 0.0);

      // apply settlement load of -0.000862 to joint 3
      pLoading.CreateJointDisplacement(0, 3, -0.00086208, 0.0, 0.0);

      Float64 dx, dy, rz;
      model.ComputeJointDeflections(0, 1, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0)); ASSERT_TRUE(IsEqual(dy, 0.0)); ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputeJointDeflections(0, 2, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0025862132183908)); ASSERT_TRUE(IsEqual(dy, 0.0)); ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputeJointDeflections(0, 3, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, -0.00086208)); ASSERT_TRUE(IsEqual(dy, 0.0)); ASSERT_TRUE(IsEqual(rz, 0.0));

      Float64 sfx, sfy, smz, efx, efy, emz;
      model.ComputeMemberForces(0, 1, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, -15.0, 0.1)); ASSERT_TRUE(IsEqual(efx, 15.0, 0.1));
      model.ComputeMemberForces(0, 2, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 10.0, 0.1)); ASSERT_TRUE(IsEqual(efx, -10.0, 0.1));

      Float64 fx, fy, mz;
      model.ComputeReactions(0, 1, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -15.0, 0.1)); ASSERT_TRUE(IsEqual(fy, 0.0, 0.1)); ASSERT_TRUE(IsEqual(mz, 0.0, 0.1));
      model.ComputeReactions(0, 2, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0, 0.1)); ASSERT_TRUE(IsEqual(fy, 0.0, 0.1)); ASSERT_TRUE(IsEqual(mz, 0.0, 0.1));
      model.ComputeReactions(0, 3, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -10.0, 0.1)); ASSERT_TRUE(IsEqual(fy, 0.0, 0.1)); ASSERT_TRUE(IsEqual(mz, 0.0, 0.1));
   }

   // Problem taken from "Matrix Analysis of Structures", Robert F. Sennett,
   // 1994, Chapter 3, Example 3.6 - two-span beam with mid-span support settlement.
   TEST_METHOD(TwoSpanBeam_MidspanSettlementAndRotation)
   {
      Model model;
      model.CreateJoint(1, 0.0, 0.0);
      Joint& pJoint2 = model.CreateJoint(2, 10.0 * 12.0, 0.0);
      Joint& pJoint3 = model.CreateJoint(3, 20.0 * 12.0, 0.0);

      model.FindJoint(1)->Support();
      pJoint2.Support();
      pJoint2.ReleaseDof(JointReleaseType::Fx);
      pJoint2.ReleaseDof(JointReleaseType::Mz);
      pJoint3.Support();
      pJoint3.ReleaseDof(JointReleaseType::Fx);
      pJoint3.ReleaseDof(JointReleaseType::Mz);

      Float64 EI = 2.90e06;
      Float64 EA = EI; // whatever
      model.CreateMember(1, 1, 2, EA, EI);
      model.CreateMember(2, 2, 3, EA, EI);

      Loading& pLoading = model.CreateLoading(0);
      pLoading.CreateJointDisplacement(0, 2, 0.0, -0.25, 0.0);

      Float64 dx, dy, rz;
      model.ComputeJointDeflections(0, 1, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0)); ASSERT_TRUE(IsEqual(dy, 0.0)); ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputeJointDeflections(0, 2, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0)); ASSERT_TRUE(IsEqual(dy, -0.25)); ASSERT_TRUE(IsEqual(rz, -0.000892857));
      model.ComputeJointDeflections(0, 3, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0)); ASSERT_TRUE(IsEqual(dy, 0.0)); ASSERT_TRUE(IsEqual(rz, 0.00357142));

      Float64 sfx, sfy, smz, efx, efy, emz;
      model.ComputeMemberForces(0, 1, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfy, 3.955853174)); ASSERT_TRUE(IsEqual(smz, 258.9285714));
      ASSERT_TRUE(IsEqual(efy, -3.9558531746)); ASSERT_TRUE(IsEqual(emz, 215.77380952));
      model.ComputeMemberForces(0, 2, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfy, -1.79811507936)); ASSERT_TRUE(IsEqual(smz, -215.77380952381));
      ASSERT_TRUE(IsEqual(efy, 1.79811507936)); ASSERT_TRUE(IsEqual(emz, 0.0));

      Float64 fx, fy, mz;
      model.ComputeReactions(0, 1, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fy, 3.95585317)); ASSERT_TRUE(IsEqual(mz, 258.92857142));
      model.ComputeReactions(0, 2, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fy, -5.75396825)); ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputeReactions(0, 3, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fy, 1.79811507936)); ASSERT_TRUE(IsEqual(mz, 0.0));

      //////////////////////////////////////////////////////////////
      // next let's try a joint rotation - first free up the model and
      // remove the existing load
      pJoint2.Free();
      pJoint3.Support();
      ASSERT_TRUE(pLoading.RemoveJointDisplacement(0));

      // add a rotation of 0.1 at joint 3
      pLoading.CreateJointDisplacement(0, 3, 0.0, 0.0, 0.1);

      model.ComputeJointDeflections(0, 1, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0)); ASSERT_TRUE(IsEqual(dy, 0.0)); ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputeJointDeflections(0, 2, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0)); ASSERT_TRUE(IsEqual(dy, -3.0)); ASSERT_TRUE(IsEqual(rz, -0.025));
      model.ComputeJointDeflections(0, 3, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0)); ASSERT_TRUE(IsEqual(dy, 0.0)); ASSERT_TRUE(IsEqual(rz, 0.1));

      model.ComputeMemberForces(0, 1, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfy, 30.208333)); ASSERT_TRUE(IsEqual(smz, 2416.666667));
      ASSERT_TRUE(IsEqual(efy, -30.208333)); ASSERT_TRUE(IsEqual(emz, 1208.33333));
      model.ComputeMemberForces(0, 2, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfy, 30.208333)); ASSERT_TRUE(IsEqual(smz, -1208.33333));
      ASSERT_TRUE(IsEqual(efy, -30.208333)); ASSERT_TRUE(IsEqual(emz, 4833.333333));

      model.ComputeReactions(0, 1, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fy, 30.208333)); ASSERT_TRUE(IsEqual(mz, 2416.666667));
      model.ComputeReactions(0, 2, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fy, 0.0)); ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputeReactions(0, 3, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fy, -30.208333)); ASSERT_TRUE(IsEqual(mz, 4833.333333));
   }

   // Problem taken from "Matrix Analysis of Structures", Robert F. Sennett,
   // 1994, Chapter 2, Example 2.3 - simple truss with support settlement at
   // two joints.
   TEST_METHOD(Truss_SennettExample2_3_SupportSettlement)
   {
      Model model;
      model.CreateJoint(1, 0.0, 0.0);
      Joint& pJoint2 = model.CreateJoint(2, 10.0 * 12.0, 10.0 * 12.0);
      Joint& pJoint3 = model.CreateJoint(3, 20.0 * 12.0, 10.0 * 12.0);
      Joint& pJoint4 = model.CreateJoint(4, 30.0 * 12.0, 0.0);

      model.FindJoint(1)->Support();
      pJoint2.Support();
      pJoint2.ReleaseDof(JointReleaseType::Fx);
      pJoint2.ReleaseDof(JointReleaseType::Fy);
      pJoint3.Support();
      pJoint3.ReleaseDof(JointReleaseType::Fx);
      pJoint3.ReleaseDof(JointReleaseType::Fy);
      pJoint4.Support();

      Float64 E = 29.0e06;
      Float64 EA = E * 2.0;
      Float64 EI = 1.0e29; // dummy since all members are pinned
      Member& pMember1 = model.CreateMember(1, 1, 2, EA, EI);
      Member& pMember2 = model.CreateMember(2, 2, 3, EA, EI);
      Member& pMember3 = model.CreateMember(3, 3, 4, EA, EI);
      Member& pMember4 = model.CreateMember(4, 1, 3, EA, EI);
      Member& pMember5 = model.CreateMember(5, 2, 4, EA, EI);

      // pin 'em
      for (Member* mbr : { &pMember1, &pMember2, &pMember3, &pMember4, &pMember5 })
      {
         mbr->ReleaseEnd(MemberEndType::Start, MemberReleaseType::Mz);
         mbr->ReleaseEnd(MemberEndType::End, MemberReleaseType::Mz);
      }

      Loading& pLoading = model.CreateLoading(0);
      pLoading.CreateJointLoad(0, 2, 0.0, -30000.0, 0.0);

      // another joint load applied at a fixity to make sure reactions are added correctly
      pLoading.CreateJointLoad(4, 4, 0.0, -20000.0, 0.0);

      // apply joint deflections at joints 1 and 4
      pLoading.CreateJointDisplacement(1, 1, 0.0, -0.60, 0.0);
      JointDisplacement& pJointDisp4 = pLoading.CreateJointDisplacement(4, 4, -0.3, 0.0, 0.0);

      ASSERT_EQ(pJointDisp4.GetLoadingID(), 0);

      // apply deflection to a free dof - should error until removed
      pLoading.CreateJointDisplacement(5, 2, -0.3, 0.0, 0.0);

      Float64 dx, dy, rz;
      ASSERT_THROWS(model.ComputeJointDeflections(0, 1, &dx, &dy, &rz), ReasonCode::JointDispToFixedDofOnly);
      ASSERT_TRUE(pLoading.RemoveJointDisplacement(5));

      model.ComputeJointDeflections(0, 1, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0)); ASSERT_TRUE(IsEqual(dy, -0.6)); ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputeJointDeflections(0, 2, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, -0.33847916063898)); ASSERT_TRUE(IsEqual(dy, -0.36436867720659)); ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputeJointDeflections(0, 3, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, -0.32342783496097)); ASSERT_TRUE(IsEqual(dy, -0.0092373090239415)); ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputeJointDeflections(0, 4, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, -0.3)); ASSERT_TRUE(IsEqual(dy, -0.0)); ASSERT_TRUE(IsEqual(rz, 0.0));

      Float64 sfx, sfy, smz, efx, efy, emz;
      model.ComputeMemberForces(0, 1, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 24854.89414)); ASSERT_TRUE(IsEqual(efx, -24854.89414));
      model.ComputeMemberForces(0, 4, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 5422.32129)); ASSERT_TRUE(IsEqual(efx, -5422.32129));

      Float64 fx, fy, mz;
      model.ComputeReactions(0, 1, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 22424.9358)); ASSERT_TRUE(IsEqual(fy, 20000.0000)); ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputeReactions(0, 4, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -22424.9358)); ASSERT_TRUE(IsEqual(fy, 30000.0000)); // has point load added in
      ASSERT_TRUE(IsEqual(mz, 0.0));
   }
};
} // namespace FEA2DUnitTests
