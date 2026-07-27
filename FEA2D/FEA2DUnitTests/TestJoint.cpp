///////////////////////////////////////////////////////////////////////
// FEA2D - Two-dimensional Finite Element Analysis Engine
// Copyright � 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
///////////////////////////////////////////////////////////////////////
// TestJoint.cpp
//
// Mirrors Fem2d\Fem2dUnitTests\TestJoint.cpp, calling WBFL::FEA2D::Model
// directly instead of through COM.
#include "pch.h"

namespace FEA2DUnitTests
{

TEST_CLASS(TestJoint)
{
public:
   TEST_METHOD(BasicJointOperations)
   {
      Model model;

      Joint& pJoint0 = model.CreateJoint(0, 2, 3);
      model.CreateJoint(2, 22, 32);
      model.CreateJoint(4, 44, 34);
      model.CreateJoint(5, 55, 35);
      ASSERT_THROWS(model.CreateJoint(5, 55, 35), ReasonCode::JointWithIdAlreadyExists);

      // grab a joint by id and check its data
      Joint* pj2r = model.FindJoint(2);

      ASSERT_TRUE(pj2r != nullptr);
      ASSERT_EQ(pj2r->GetID(), 2);
      ASSERT_EQ(pj2r->GetX(), 22);
      ASSERT_EQ(pj2r->GetY(), 32);

      pj2r->SetX(200.);
      pj2r->SetY(300.);
      ASSERT_EQ(pj2r->GetX(), 200);
      ASSERT_EQ(pj2r->GetY(), 300);

      Joint* pj5r = model.FindJoint(5);

      ASSERT_TRUE(pj5r != nullptr);
      ASSERT_EQ(pj5r->GetID(), 5);
      ASSERT_EQ(pj5r->GetX(), 55);
      ASSERT_EQ(pj5r->GetY(), 35);

      ASSERT_EQ(model.GetJointCount(), 4);

      // create some members and connect them to joints
      model.CreateMember(0, 0, 2, 100, 105);
      model.CreateMember(1, 0, 4, 110, 115);
      model.CreateMember(2, 5, 4, 110, 115);
      model.CreateMember(3, 5, 2, 110, 115);
      model.CreateMember(7, 5, 0, 110, 115);

      // look at members connected to joint 0
      auto attached = model.GetAttachedMembers(0);
      ASSERT_EQ(attached.size(), 3u);
      ASSERT_EQ(attached[0], 0);
      ASSERT_EQ(attached[1], 1);
      ASSERT_EQ(attached[2], 7);

      // remove joint 2 (by ID), then remove whatever is now at index 1 (joint 4)
      ASSERT_TRUE(model.RemoveJoint(2));
      JointIDType idAtIndex1 = model.FindJointByIndex(1)->GetID();
      ASSERT_EQ(idAtIndex1, 4);
      ASSERT_TRUE(model.RemoveJoint(idAtIndex1));

      ASSERT_EQ(model.GetJointCount(), 2u);

      // remaining joints, in sorted-ID order: 0, 5
      Joint* p0 = model.FindJointByIndex(0);

      Joint* p1 = model.FindJointByIndex(1);

      ASSERT_TRUE(p0 != nullptr && p1 != nullptr);
      ASSERT_EQ(p0->GetID(), 0); ASSERT_EQ(p0->GetX(), 2); ASSERT_EQ(p0->GetY(), 3);
      ASSERT_EQ(p1->GetID(), 5); ASSERT_EQ(p1->GetX(), 55); ASSERT_EQ(p1->GetY(), 35);

      ASSERT_TRUE(model.FindJointByIndex(2) == nullptr);

      Joint* psj = model.FindJointByIndex(0);

      ASSERT_TRUE(psj != nullptr);
      ASSERT_EQ(psj->GetID(), 0);

      // test releases on joints
      ASSERT_FALSE(psj->IsSupport());
      ASSERT_FALSE(psj->IsDofReleased(JointReleaseType::None));
      ASSERT_TRUE(psj->IsDofReleased(JointReleaseType::Fx));
      ASSERT_TRUE(psj->IsDofReleased(JointReleaseType::Fy));
      ASSERT_TRUE(psj->IsDofReleased(JointReleaseType::Mz));
      ASSERT_TRUE(psj->IsDofReleased(JointReleaseType::All));
      ASSERT_TRUE(psj->IsDofSupported(JointReleaseType::None));
      ASSERT_FALSE(psj->IsDofSupported(JointReleaseType::Fx));
      ASSERT_FALSE(psj->IsDofSupported(JointReleaseType::Fy));
      ASSERT_FALSE(psj->IsDofSupported(JointReleaseType::Mz));
      ASSERT_FALSE(psj->IsDofSupported(JointReleaseType::All));

      psj->Support();
      ASSERT_TRUE(psj->IsSupport());
      ASSERT_TRUE(psj->IsDofReleased(JointReleaseType::None));
      ASSERT_FALSE(psj->IsDofReleased(JointReleaseType::Fx));
      ASSERT_FALSE(psj->IsDofReleased(JointReleaseType::Fy));
      ASSERT_FALSE(psj->IsDofReleased(JointReleaseType::Mz));
      ASSERT_FALSE(psj->IsDofReleased(JointReleaseType::All));
      ASSERT_FALSE(psj->IsDofSupported(JointReleaseType::None));
      ASSERT_TRUE(psj->IsDofSupported(JointReleaseType::Fx));
      ASSERT_TRUE(psj->IsDofSupported(JointReleaseType::Fy));
      ASSERT_TRUE(psj->IsDofSupported(JointReleaseType::Mz));
      ASSERT_TRUE(psj->IsDofSupported(JointReleaseType::All));

      psj->ReleaseDof(JointReleaseType::Fx);
      ASSERT_TRUE(psj->IsSupport());
      ASSERT_FALSE(psj->IsDofReleased(JointReleaseType::None));
      ASSERT_TRUE(psj->IsDofReleased(JointReleaseType::Fx));
      ASSERT_FALSE(psj->IsDofReleased(JointReleaseType::Fy));
      ASSERT_FALSE(psj->IsDofReleased(JointReleaseType::Mz));
      ASSERT_FALSE(psj->IsDofReleased(JointReleaseType::All));
      ASSERT_FALSE(psj->IsDofSupported(JointReleaseType::None));
      ASSERT_FALSE(psj->IsDofSupported(JointReleaseType::Fx));
      ASSERT_TRUE(psj->IsDofSupported(JointReleaseType::Fy));
      ASSERT_TRUE(psj->IsDofSupported(JointReleaseType::Mz));
      ASSERT_FALSE(psj->IsDofSupported(JointReleaseType::All));

      psj->ReleaseDof(JointReleaseType::Fy);
      ASSERT_TRUE(psj->IsSupport());
      ASSERT_FALSE(psj->IsDofReleased(JointReleaseType::None));
      ASSERT_TRUE(psj->IsDofReleased(JointReleaseType::Fx));
      ASSERT_TRUE(psj->IsDofReleased(JointReleaseType::Fy));
      ASSERT_FALSE(psj->IsDofReleased(JointReleaseType::Mz));
      ASSERT_FALSE(psj->IsDofReleased(JointReleaseType::All));
      ASSERT_FALSE(psj->IsDofSupported(JointReleaseType::None));
      ASSERT_FALSE(psj->IsDofSupported(JointReleaseType::Fx));
      ASSERT_FALSE(psj->IsDofSupported(JointReleaseType::Fy));
      ASSERT_TRUE(psj->IsDofSupported(JointReleaseType::Mz));
      ASSERT_FALSE(psj->IsDofSupported(JointReleaseType::All));

      psj->ReleaseDof(JointReleaseType::Mz);
      ASSERT_FALSE(psj->IsSupport());
      ASSERT_FALSE(psj->IsDofReleased(JointReleaseType::None));
      ASSERT_TRUE(psj->IsDofReleased(JointReleaseType::Fx));
      ASSERT_TRUE(psj->IsDofReleased(JointReleaseType::Fy));
      ASSERT_TRUE(psj->IsDofReleased(JointReleaseType::Mz));
      ASSERT_TRUE(psj->IsDofReleased(JointReleaseType::All));
      ASSERT_TRUE(psj->IsDofSupported(JointReleaseType::None));
      ASSERT_FALSE(psj->IsDofSupported(JointReleaseType::Fx));
      ASSERT_FALSE(psj->IsDofSupported(JointReleaseType::Fy));
      ASSERT_FALSE(psj->IsDofSupported(JointReleaseType::Mz));
      ASSERT_FALSE(psj->IsDofSupported(JointReleaseType::All));

      psj->Support();
      psj->Free();
      ASSERT_FALSE(psj->IsSupport());
      ASSERT_FALSE(psj->IsDofReleased(JointReleaseType::None));
      ASSERT_TRUE(psj->IsDofReleased(JointReleaseType::Fx));
      ASSERT_TRUE(psj->IsDofReleased(JointReleaseType::Fy));
      ASSERT_TRUE(psj->IsDofReleased(JointReleaseType::Mz));
      ASSERT_TRUE(psj->IsDofReleased(JointReleaseType::All));
      ASSERT_TRUE(psj->IsDofSupported(JointReleaseType::None));
      ASSERT_FALSE(psj->IsDofSupported(JointReleaseType::Fx));
      ASSERT_FALSE(psj->IsDofSupported(JointReleaseType::Fy));
      ASSERT_FALSE(psj->IsDofSupported(JointReleaseType::Mz));
      ASSERT_FALSE(psj->IsDofSupported(JointReleaseType::All));

      // test bit-flag combinations formed by addition rather than the
      // named Fx/Fy/Mz/All constants (mirrors legacy VB-callers-can-do-this coverage)
      psj->Support();
      psj->ReleaseDof(static_cast<JointReleaseType>((long)JointReleaseType::Fx + (long)JointReleaseType::Mz));
      ASSERT_TRUE(psj->IsSupport());
      ASSERT_FALSE(psj->IsDofReleased(JointReleaseType::None));
      ASSERT_TRUE(psj->IsDofReleased(JointReleaseType::Fx));
      ASSERT_FALSE(psj->IsDofReleased(JointReleaseType::Fy));
      ASSERT_TRUE(psj->IsDofReleased(JointReleaseType::Mz));
      ASSERT_FALSE(psj->IsDofReleased(JointReleaseType::All));
      ASSERT_FALSE(psj->IsDofSupported(JointReleaseType::None));
      ASSERT_FALSE(psj->IsDofSupported(JointReleaseType::Fx));
      ASSERT_TRUE(psj->IsDofSupported(JointReleaseType::Fy));
      ASSERT_FALSE(psj->IsDofSupported(JointReleaseType::Mz));
      ASSERT_FALSE(psj->IsDofSupported(JointReleaseType::All));

      psj->Support();
      psj->ReleaseDof(static_cast<JointReleaseType>((long)JointReleaseType::Fx + (long)JointReleaseType::Fy + (long)JointReleaseType::Mz));
      ASSERT_FALSE(psj->IsSupport());
      ASSERT_FALSE(psj->IsDofReleased(JointReleaseType::None));
      ASSERT_TRUE(psj->IsDofReleased(JointReleaseType::Fx));
      ASSERT_TRUE(psj->IsDofReleased(JointReleaseType::Fy));
      ASSERT_TRUE(psj->IsDofReleased(JointReleaseType::Mz));
      ASSERT_TRUE(psj->IsDofReleased(JointReleaseType::All));
      ASSERT_TRUE(psj->IsDofSupported(JointReleaseType::None));
      ASSERT_FALSE(psj->IsDofSupported(JointReleaseType::Fx));
      ASSERT_FALSE(psj->IsDofSupported(JointReleaseType::Fy));
      ASSERT_FALSE(psj->IsDofSupported(JointReleaseType::Mz));
      ASSERT_FALSE(psj->IsDofSupported(JointReleaseType::All));
   }
};
} // namespace FEA2DUnitTests
