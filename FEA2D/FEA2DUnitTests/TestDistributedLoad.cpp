///////////////////////////////////////////////////////////////////////
// FEA2D - Two-dimensional Finite Element Analysis Engine
// Copyright � 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
///////////////////////////////////////////////////////////////////////
// TestDistributedLoad.cpp
//
// Mirrors Fem2d\Fem2dUnitTests\TestDistributedLoad.cpp.
#include "pch.h"

namespace FEA2DUnitTests
{

TEST_CLASS(TestDistributedLoad)
{
public:
   TEST_METHOD(BasicDistributedLoadOperations)
   {
      Model model;
      model.CreateJoint(0, 2, 3);
      model.CreateJoint(2, 22, 32);
      model.CreateJoint(4, 44, 34);
      model.CreateJoint(5, 55, 35);

      model.CreateMember(0, 0, 2, 100, 105);
      model.CreateMember(3, 2, 5, 110, 115);

      Loading& pLoading0 = model.CreateLoading(0);
      ASSERT_THROWS(model.CreateLoading(0), ReasonCode::LoadingWithIdAlreadyExists);
      model.CreateLoading(3);

      pLoading0.CreateDistributedLoad(0, 0, LoadDirection::Fy, 0.0, 23.2, 42.3, 52.3, LoadOrientation::Member);
      ASSERT_THROWS(pLoading0.CreateDistributedLoad(0, 0, LoadDirection::Fx, 0, 0, 0, 0, LoadOrientation::Member), ReasonCode::DistLoadWithIdAlreadyExists);
      DistributedLoad& pDistLoad3 = pLoading0.CreateDistributedLoad(3, 5, LoadDirection::Fy, 1.0, 33.0, 44.0, 55.0, LoadOrientation::Member);

      ASSERT_EQ(pDistLoad3.GetID(), 3);
      ASSERT_EQ(pDistLoad3.GetMemberID(), 5);

      pDistLoad3.SetMemberID(42);
      ASSERT_EQ(pDistLoad3.GetMemberID(), 42);

      ASSERT_TRUE(pDistLoad3.GetOrientation() == LoadOrientation::Member);
      pDistLoad3.SetOrientation(LoadOrientation::Global);
      ASSERT_TRUE(pDistLoad3.GetOrientation() == LoadOrientation::Global);

      ASSERT_TRUE(pDistLoad3.GetDirection() == LoadDirection::Fy);
      pDistLoad3.SetDirection(LoadDirection::Fx);
      ASSERT_TRUE(pDistLoad3.GetDirection() == LoadDirection::Fx);

      ASSERT_EQ(pDistLoad3.GetStartLocation(), 1.0);
      pDistLoad3.SetStartLocation(-.45);
      ASSERT_EQ(pDistLoad3.GetStartLocation(), -.45);
      ASSERT_THROWS(pDistLoad3.SetStartLocation(-4), ReasonCode::InvalidDistLoadLocation);

      ASSERT_EQ(pDistLoad3.GetEndLocation(), 33.0);
      pDistLoad3.SetEndLocation(-.65);
      ASSERT_EQ(pDistLoad3.GetEndLocation(), -.65);
      ASSERT_THROWS(pDistLoad3.SetEndLocation(-4), ReasonCode::InvalidDistLoadLocation);

      ASSERT_EQ(pDistLoad3.GetWStart(), 44.0);
      pDistLoad3.SetWStart(-.45);
      ASSERT_EQ(pDistLoad3.GetWStart(), -.45);

      ASSERT_EQ(pDistLoad3.GetWEnd(), 55.0);
      pDistLoad3.SetWEnd(-1.45);
      ASSERT_EQ(pDistLoad3.GetWEnd(), -1.45);

      ASSERT_EQ(pDistLoad3.GetLoadingID(), 0);
   }
};
} // namespace FEA2DUnitTests
