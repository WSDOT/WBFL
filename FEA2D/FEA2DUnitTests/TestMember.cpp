///////////////////////////////////////////////////////////////////////
// FEA2D - Two-dimensional Finite Element Analysis Engine
// Copyright � 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
///////////////////////////////////////////////////////////////////////
// TestMember.cpp
//
// Mirrors Fem2d\Fem2dUnitTests\TestMember.cpp, calling WBFL::FEA2D::Model
// directly instead of through COM.
#include "pch.h"

namespace FEA2DUnitTests
{

TEST_CLASS(TestMember)
{
public:
   TEST_METHOD(BasicMemberOperations)
   {
      Model model;
      Float64 dx, dy, rz;

      // some error checking - CheckModel() runs at the top of every query
      // (via EnsureAnalyzed()), before any of the query's own arguments -
      // even nonexistent ids like these - are looked up
      ASSERT_THROWS(model.ComputeJointDeflections(0, 0, &dx, &dy, &rz), ReasonCode::ModelHasNoJoints);

      model.CreateJoint(0, 2, 3);
      model.CreateJoint(2, 22, 32);
      model.CreateJoint(4, 44, 34);
      model.CreateJoint(5, 55, 35);
      model.CreateJoint(6, 55, 35); // same loc as joint 5

      ASSERT_THROWS(model.ComputeJointDeflections(0, 0, &dx, &dy, &rz), ReasonCode::ModelHasNoMembers);

      Member& pMember0 = model.CreateMember(0, 0, 2, 100, 105);
      Member& pMember3 = model.CreateMember(3, 2, 5, 110, 115);
      ASSERT_THROWS(model.CreateMember(3, 2, 5, 110, 115), ReasonCode::MemberWithIdAlreadyExists);
      Member& pMember4 = model.CreateMember(4, 54, 5, 110, 115); // joint doesn't exist - allowed at create time
      ASSERT_THROWS(model.CreateMember(7, 4, 4, 120, 125), ReasonCode::MemberHasSameJoints);
      Member& pMember5 = model.CreateMember(5, 5, 6, 110, 115); // zero length - allowed at create time

      ASSERT_EQ(pMember3.GetID(), 3);
      ASSERT_TRUE(IsEqual(pMember3.GetLength(), sqrt(1098.)));

      ASSERT_THROWS(pMember5.GetLength(), ReasonCode::ZeroLengthMember);
      ASSERT_THROWS(pMember4.GetLength(), ReasonCode::MemberJointNotExists);

      ASSERT_EQ(pMember0.GetStartJoint(), 0);
      ASSERT_EQ(pMember0.GetEndJoint(), 2);

      pMember0.SetStartJoint(3);
      pMember0.SetEndJoint(0);
      ASSERT_EQ(pMember0.GetStartJoint(), 3);
      ASSERT_EQ(pMember0.GetEndJoint(), 0);

      ASSERT_EQ(pMember0.GetEA(), 100);
      ASSERT_EQ(pMember0.GetEI(), 105);

      pMember0.SetEA(3);
      pMember0.SetEI(4);
      ASSERT_EQ(pMember0.GetEA(), 3);
      ASSERT_EQ(pMember0.GetEI(), 4);

      ASSERT_THROWS(pMember0.SetEA(-2.0), ReasonCode::StiffnessMustBePositive);
      ASSERT_THROWS(pMember0.SetEI(-2.0), ReasonCode::StiffnessMustBePositive);
      ASSERT_EQ(pMember0.GetEA(), 3);
      ASSERT_EQ(pMember0.GetEI(), 4);

      // members start life without any end releases
      ASSERT_FALSE(pMember0.IsReleased(MemberEndType::Start, MemberReleaseType::Mz));
      ASSERT_FALSE(pMember0.IsReleased(MemberEndType::Start, MemberReleaseType::Fx));
      ASSERT_TRUE(pMember0.IsReleased(MemberEndType::Start, MemberReleaseType::None));
      ASSERT_FALSE(pMember0.IsReleased(MemberEndType::End, MemberReleaseType::Mz));
      ASSERT_FALSE(pMember0.IsReleased(MemberEndType::End, MemberReleaseType::Fx));
      ASSERT_TRUE(pMember0.IsReleased(MemberEndType::End, MemberReleaseType::None));

      pMember0.ReleaseEnd(MemberEndType::Start, MemberReleaseType::Mz);
      ASSERT_TRUE(pMember0.IsReleased(MemberEndType::Start, MemberReleaseType::Mz));
      ASSERT_FALSE(pMember0.IsReleased(MemberEndType::Start, MemberReleaseType::Fx));
      ASSERT_FALSE(pMember0.IsReleased(MemberEndType::Start, MemberReleaseType::None));
      pMember0.ReleaseEnd(MemberEndType::End, MemberReleaseType::Mz);
      ASSERT_TRUE(pMember0.IsReleased(MemberEndType::End, MemberReleaseType::Mz));
      ASSERT_FALSE(pMember0.IsReleased(MemberEndType::End, MemberReleaseType::Fx));
      ASSERT_FALSE(pMember0.IsReleased(MemberEndType::End, MemberReleaseType::None));

      pMember0.ReleaseEnd(MemberEndType::Start, MemberReleaseType::None);
      pMember0.ReleaseEnd(MemberEndType::End, MemberReleaseType::None);
      pMember0.ReleaseEnd(MemberEndType::Start, MemberReleaseType::Fx);
      ASSERT_TRUE(pMember0.IsReleased(MemberEndType::Start, MemberReleaseType::Fx));
      ASSERT_FALSE(pMember0.IsReleased(MemberEndType::Start, MemberReleaseType::Mz));
      ASSERT_FALSE(pMember0.IsReleased(MemberEndType::Start, MemberReleaseType::None));
      pMember0.ReleaseEnd(MemberEndType::End, MemberReleaseType::Fx);
      ASSERT_TRUE(pMember0.IsReleased(MemberEndType::End, MemberReleaseType::Fx));
      ASSERT_FALSE(pMember0.IsReleased(MemberEndType::End, MemberReleaseType::Mz));
      ASSERT_FALSE(pMember0.IsReleased(MemberEndType::End, MemberReleaseType::None));

      pMember0.ReleaseEnd(MemberEndType::Start, MemberReleaseType::None);
      pMember0.ReleaseEnd(MemberEndType::End, MemberReleaseType::None);
      ASSERT_FALSE(pMember0.IsReleased(MemberEndType::Start, MemberReleaseType::Mz));
      ASSERT_FALSE(pMember0.IsReleased(MemberEndType::End, MemberReleaseType::Mz));
   }
};
} // namespace FEA2DUnitTests
