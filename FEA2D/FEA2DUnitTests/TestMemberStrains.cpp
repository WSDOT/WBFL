///////////////////////////////////////////////////////////////////////
// FEA2D - Two-dimensional Finite Element Analysis Engine
// Copyright � 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
///////////////////////////////////////////////////////////////////////
// TestMemberStrains.cpp
//
// Mirrors Fem2d\Fem2dUnitTests\TestMemberStrains.cpp.
#include "pch.h"

namespace FEA2DUnitTests
{

TEST_CLASS(TestMemberStrains)
{
public:
   TEST_METHOD(General)
   {
      Model model;
      model.CreateJoint(0, 2, 3);
      model.CreateJoint(2, 22, 32);
      model.CreateJoint(4, 44, 34);
      model.CreateJoint(5, 55, 35);

      model.CreateMember(0, 0, 2, 100, 105);
      model.CreateMember(3, 2, 5, 110, 115);

      Loading& pLoading0 = model.CreateLoading(2);
      ASSERT_THROWS(model.CreateLoading(2), ReasonCode::LoadingWithIdAlreadyExists);
      model.CreateLoading(3);

      pLoading0.CreateMemberStrain(0, 0, 0.0, -1.0, 42.3, 52.3);
      ASSERT_THROWS(pLoading0.CreateMemberStrain(0, 0, 0.0, -1.0, 0, 0), ReasonCode::MemberStrainWithIdAlreadyExists);
      MemberStrain& pMemberStrain3 = pLoading0.CreateMemberStrain(3, 5, 0.0, -1.0, 33.0, 44.0);

      ASSERT_EQ(pLoading0.GetMemberStrainCount(), 2u);

      ASSERT_EQ(pMemberStrain3.GetID(), 3);
      ASSERT_EQ(pMemberStrain3.GetMemberID(), 5);

      pMemberStrain3.SetMemberID(42);
      ASSERT_EQ(pMemberStrain3.GetMemberID(), 42);

      ASSERT_EQ(pMemberStrain3.GetAxialStrain(), 33);
      ASSERT_EQ(pMemberStrain3.GetCurvatureStrain(), 44);

      pMemberStrain3.SetAxialStrain(-11);
      pMemberStrain3.SetCurvatureStrain(-12);
      ASSERT_EQ(pMemberStrain3.GetAxialStrain(), -11);
      ASSERT_EQ(pMemberStrain3.GetCurvatureStrain(), -12);

      ASSERT_FALSE(pLoading0.RemoveMemberStrain(5));
      ASSERT_TRUE(pLoading0.RemoveMemberStrain(3));
      ASSERT_EQ(pLoading0.GetMemberStrainCount(), 1u);
   }

   TEST_METHOD(BarTwoMembers_SennettExample1_5)
   {
      // Problem taken from "Matrix Analysis of Structures", Robert F. Sennett,
      // 1994, Chapter 1, Example 1.5 - two-node bar with applied member strain.
      Model model;
      model.CreateJoint(1, 0.0, 0.0);
      model.CreateJoint(2, 10.0, 0.0);
      Joint& pJoint3 = model.CreateJoint(3, 25.0, 0.0);

      model.FindJoint(1)->Support();

      Float64 E = 29.0e06;
      Float64 EA = 2.0 * E;
      Float64 EI = EA; // whatever
      model.CreateMember(1, 1, 2, EA, EI);
      model.CreateMember(2, 2, 3, EA, EI);

      Loading& pLoading = model.CreateLoading(0);

      Float64 strain = 60.0 * 6.5e-06;
      pLoading.CreateMemberStrain(0, 2, 0.0, -1.0, strain, 0.0);


      Float64 dx, dy, rz;
      model.ComputeJointDeflections(0, 1, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0)); ASSERT_TRUE(IsEqual(dy, 0.0)); ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputeJointDeflections(0, 2, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0)); ASSERT_TRUE(IsEqual(dy, 0.0)); ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputeJointDeflections(0, 3, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.00585)); ASSERT_TRUE(IsEqual(dy, 0.0)); ASSERT_TRUE(IsEqual(rz, 0.0));

      Float64 sfx, sfy, smz, efx, efy, emz;
      model.ComputeMemberForces(0, 1, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 0.0)); ASSERT_TRUE(IsEqual(sfy, 0.0)); ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 0.0)); ASSERT_TRUE(IsEqual(efy, 0.0)); ASSERT_TRUE(IsEqual(emz, 0.0));
      model.ComputeMemberForces(0, 2, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 0.0)); ASSERT_TRUE(IsEqual(sfy, 0.0)); ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 0.0)); ASSERT_TRUE(IsEqual(efy, 0.0)); ASSERT_TRUE(IsEqual(emz, 0.0));

      Float64 fx, fy, mz;
      model.ComputeReactions(0, 1, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0)); ASSERT_TRUE(IsEqual(fy, 0.0)); ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputeReactions(0, 2, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0)); ASSERT_TRUE(IsEqual(fy, 0.0)); ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputeReactions(0, 3, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0)); ASSERT_TRUE(IsEqual(fy, 0.0)); ASSERT_TRUE(IsEqual(mz, 0.0));

      // now let's set up book problem, first boundary conditions
      pJoint3.Support();

      // apply 10k load to joint 2
      pLoading.CreateJointLoad(0, 2, 10000.0, 0.0, 0.0);

      // the model was mutated (new joint load) since the results above were
      // queried - this confirms no stale state survives into these queries
      model.ComputeJointDeflections(0, 1, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0)); ASSERT_TRUE(IsEqual(dy, 0.0)); ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputeJointDeflections(0, 2, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, -0.001305517241)); ASSERT_TRUE(IsEqual(dy, 0.0)); ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputeJointDeflections(0, 3, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0)); ASSERT_TRUE(IsEqual(dy, 0.0)); ASSERT_TRUE(IsEqual(rz, 0.0));

      model.ComputeMemberForces(0, 1, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 7572.0)); ASSERT_TRUE(IsEqual(sfy, 0.0)); ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, -7572.0)); ASSERT_TRUE(IsEqual(efy, 0.0)); ASSERT_TRUE(IsEqual(emz, 0.0));
      model.ComputeMemberForces(0, 2, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 17572.0)); ASSERT_TRUE(IsEqual(sfy, 0.0)); ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, -17572.0)); ASSERT_TRUE(IsEqual(efy, 0.0)); ASSERT_TRUE(IsEqual(emz, 0.0));

      model.ComputeReactions(0, 1, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 7572.0)); ASSERT_TRUE(IsEqual(fy, 0.0)); ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputeReactions(0, 2, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0)); ASSERT_TRUE(IsEqual(fy, 0.0)); ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputeReactions(0, 3, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -17572.0)); ASSERT_TRUE(IsEqual(fy, 0.0)); ASSERT_TRUE(IsEqual(mz, 0.0));
   }

   TEST_METHOD(BarOneMember_FreeThenFixedEnd)
   {
      Model model;
      model.CreateJoint(1, 0.0, 0.0);
      Joint& pJoint2 = model.CreateJoint(2, 10.0, 0.0);

      // let's start off by letting right end fly in the breeze and apply
      // strain load - member forces should be zero, but we should have
      // non-zero deflections
      model.FindJoint(1)->Support();

      Float64 E = 29.0e06;
      Float64 EA = 2.0 * E;
      Float64 EI = EA; // whatever
      model.CreateMember(1, 1, 2, EA, EI);

      // put a single poi at mid-span
      model.CreatePOI(1, 1, -.5);

      // create load case
      Loading& pLoading = model.CreateLoading(0);

      // apply member strain to member, first compute strain
      Float64 strain = 0.002;
      pLoading.CreateMemberStrain(0, 1, 0.0, -1.0, strain, 0.0);


      // get joint deflections
      Float64 dx, dy, rz;
      model.ComputeJointDeflections(0, 1, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputeJointDeflections(0, 2, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.02));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      // get member end forces
      Float64 sfx, sfy, smz, efx, efy, emz;
      model.ComputeMemberForces(0, 1, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 0.0));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 0.0));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      Float64 fx, fy, mz;
      model.ComputeReactions(0, 1, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputeReactions(0, 2, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      // poi results
      model.ComputePOIDeflections(0, 1, LoadOrientation::Global, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.01));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      model.ComputePOIForces(0, 1, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      // now let's fix the other end
      pJoint2.Support();


      // get joint deflections
      model.ComputeJointDeflections(0, 1, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputeJointDeflections(0, 2, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      // get member end forces
      model.ComputeMemberForces(0, 1, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 116000.0));
      ASSERT_TRUE(IsEqual(sfy, 0.0));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, -116000.0));
      ASSERT_TRUE(IsEqual(efy, 0.0));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      model.ComputeReactions(0, 1, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 116000.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputeReactions(0, 2, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -116000.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      // poi results
      model.ComputePOIDeflections(0, 1, LoadOrientation::Global, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      model.ComputePOIForces(0, 1, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -116000.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
   }

   TEST_METHOD(BeamOneSpan_CurvatureStrain)
   {
      Model model;
      Joint& pJoint1 = model.CreateJoint(1, 0.0, 0.0);
      Joint& pJoint2 = model.CreateJoint(2, 10.0, 0.0);

      // boundary conditions - start off with end 2 free
      pJoint1.Support();

      Float64 EI = 2.90e06;
      Float64 EA = EI; // whatever
      model.CreateMember(1, 1, 2, EA, EI);

      // put a single poi at mid-span
      model.CreatePOI(1, 1, -.5);

      // create load case and member curvature of 0.002 length/radian
      Loading& pLoading = model.CreateLoading(0);
      pLoading.CreateMemberStrain(0, 1, 0.0, -1.0, 0.0, 0.002);


      Float64 dx, dy, rz;
      model.ComputeJointDeflections(0, 1, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputeJointDeflections(0, 2, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.1));
      ASSERT_TRUE(IsEqual(rz, 0.02));

      Float64 sfx, sfy, smz, efx, efy, emz;
      model.ComputeMemberForces(0, 1, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 0.0));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 0.0));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      Float64 fx, fy, mz;
      model.ComputeReactions(0, 1, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputeReactions(0, 2, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      model.ComputePOIDeflections(0, 1, LoadOrientation::Global, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.025));
      ASSERT_TRUE(IsEqual(rz, 0.01));

      model.ComputePOIForces(0, 1, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      ////////////////////////////////////////////
      // now let's pin both ends
      pJoint1.ReleaseDof(JointReleaseType::Mz);
      pJoint2.Support();
      pJoint2.ReleaseDof(JointReleaseType::Mz);


      model.ComputeJointDeflections(0, 1, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -0.01));
      model.ComputeJointDeflections(0, 2, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.01));

      model.ComputeMemberForces(0, 1, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 0.0));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 0.0));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      model.ComputeReactions(0, 1, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputeReactions(0, 2, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      model.ComputePOIDeflections(0, 1, LoadOrientation::Global, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -0.025));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      model.ComputePOIForces(0, 1, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      ////////////////////////////////////////////
      // now let's fix both ends
      pJoint1.Support();
      pJoint2.Support();


      model.ComputeJointDeflections(0, 1, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputeJointDeflections(0, 2, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      model.ComputeMemberForces(0, 1, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 0.0));
      ASSERT_TRUE(IsEqual(smz, 5800.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 0.0));
      ASSERT_TRUE(IsEqual(emz, -5800.0));

      model.ComputeReactions(0, 1, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 5800.0));
      model.ComputeReactions(0, 2, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, -5800.0));

      model.ComputePOIDeflections(0, 1, LoadOrientation::Global, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      model.ComputePOIForces(0, 1, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, -5800.0));

      model.ComputePOIForces(0, 1, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 5800.0));
   }

   TEST_METHOD(BeamTwoSpans_CurvatureStrainBothMembers)
   {
      Model model;
      Joint& pJoint1 = model.CreateJoint(1, 0.0, 0.0);
      model.CreateJoint(2, 5.0, 0.0);
      Joint& pJoint3 = model.CreateJoint(3, 10.0, 0.0);

      pJoint1.Support();

      Float64 EI = 2.90e06;
      Float64 EA = EI; // whatever
      model.CreateMember(1, 1, 2, EA, EI);
      model.CreateMember(2, 2, 3, EA, EI);

      model.CreatePOI(1, 1, -1.0);

      // create load case and member rotational strain of 0.002
      Loading& pLoading = model.CreateLoading(0);
      pLoading.CreateMemberStrain(1, 1, 0.0, -1.0, 0.0, 0.002);
      pLoading.CreateMemberStrain(2, 2, 0.0, -1.0, 0.0, 0.002);


      Float64 dx, dy, rz;
      model.ComputeJointDeflections(0, 1, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputeJointDeflections(0, 2, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.025));
      ASSERT_TRUE(IsEqual(rz, 0.01));
      model.ComputeJointDeflections(0, 3, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.1));
      ASSERT_TRUE(IsEqual(rz, 0.02));

      Float64 sfx, sfy, smz, efx, efy, emz;
      model.ComputeMemberForces(0, 1, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 0.0));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 0.0));
      ASSERT_TRUE(IsEqual(emz, 0.0));
      model.ComputeMemberForces(0, 2, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 0.0));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 0.0));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      Float64 fx, fy, mz;
      model.ComputeReactions(0, 1, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputeReactions(0, 2, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputeReactions(0, 3, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      model.ComputePOIDeflections(0, 1, LoadOrientation::Global, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.025));
      ASSERT_TRUE(IsEqual(rz, 0.01));

      model.ComputePOIForces(0, 1, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      ////////////////////////////////////////////
      // now let's pin both ends
      pJoint1.ReleaseDof(JointReleaseType::Mz);
      pJoint3.Support();
      pJoint3.ReleaseDof(JointReleaseType::Mz);


      model.ComputeJointDeflections(0, 1, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -0.01));
      model.ComputeJointDeflections(0, 2, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -0.025));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputeJointDeflections(0, 3, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.01));

      model.ComputeMemberForces(0, 1, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 0.0));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 0.0));
      ASSERT_TRUE(IsEqual(emz, 0.0));
      model.ComputeMemberForces(0, 2, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 0.0));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 0.0));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      model.ComputeReactions(0, 1, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputeReactions(0, 3, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      model.ComputePOIDeflections(0, 1, LoadOrientation::Global, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -0.025));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      model.ComputePOIForces(0, 1, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      ////////////////////////////////////////////
      // now let's fix both ends
      pJoint1.Support();
      pJoint3.Support();


      model.ComputeJointDeflections(0, 1, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputeJointDeflections(0, 2, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputeJointDeflections(0, 3, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      model.ComputeMemberForces(0, 1, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 0.0));
      ASSERT_TRUE(IsEqual(smz, 5800.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 0.0));
      ASSERT_TRUE(IsEqual(emz, -5800.0));
      model.ComputeMemberForces(0, 2, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 0.0));
      ASSERT_TRUE(IsEqual(smz, 5800.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 0.0));
      ASSERT_TRUE(IsEqual(emz, -5800.0));

      model.ComputeReactions(0, 1, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 5800.0));
      model.ComputeReactions(0, 2, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputeReactions(0, 3, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, -5800.0));

      model.ComputePOIDeflections(0, 1, LoadOrientation::Global, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      model.ComputePOIForces(0, 1, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, -5800.0));

      model.ComputePOIForces(0, 1, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 5800.0));
   }
};
} // namespace FEA2DUnitTests
