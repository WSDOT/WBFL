///////////////////////////////////////////////////////////////////////
// FEA2D - Two-dimensional Finite Element Analysis Engine
// Copyright � 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
///////////////////////////////////////////////////////////////////////
// TestPointLoad.cpp
//
// Mirrors Fem2d\Fem2dUnitTests\TestPointLoad.cpp. Omits the COM
// reference-counting section - see the note in TestJointLoad.cpp.
#include "pch.h"

namespace FEA2DUnitTests
{

TEST_CLASS(TestPointLoad)
{
public:
   TEST_METHOD(BasicPointLoadOperations)
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

      pLoading0.CreatePointLoad(0, 0, 0.0, 23.2, 42.3, 52.3, LoadOrientation::Member);
      ASSERT_THROWS(pLoading0.CreatePointLoad(0, 0, 0, 0, 0, 0, LoadOrientation::Member), ReasonCode::PointLoadWithIdAlreadyExists);
      PointLoad& pPointLoad3 = pLoading0.CreatePointLoad(3, 5, 1.0, 33.0, 44.0, 55.0, LoadOrientation::Member);

      ASSERT_EQ(pLoading0.GetPointLoadCount(), 2u);

      ASSERT_EQ(pPointLoad3.GetID(), 3);
      ASSERT_EQ(pPointLoad3.GetMemberID(), 5);

      pPointLoad3.SetMemberID(42);
      ASSERT_EQ(pPointLoad3.GetMemberID(), 42);

      ASSERT_TRUE(pPointLoad3.GetOrientation() == LoadOrientation::Member);
      pPointLoad3.SetOrientation(LoadOrientation::Global);
      ASSERT_TRUE(pPointLoad3.GetOrientation() == LoadOrientation::Global);

      ASSERT_EQ(pPointLoad3.GetLocation(), 1.0);
      pPointLoad3.SetLocation(-.4);
      ASSERT_EQ(pPointLoad3.GetLocation(), -.4);
      ASSERT_THROWS(pPointLoad3.SetLocation(-4), ReasonCode::InvalidPointLoadLocation);

      ASSERT_EQ(pPointLoad3.GetFx(), 33);
      ASSERT_EQ(pPointLoad3.GetFy(), 44);
      ASSERT_EQ(pPointLoad3.GetMz(), 55);

      pPointLoad3.SetFx(-11);
      pPointLoad3.SetFy(-12);
      pPointLoad3.SetMz(-13);
      ASSERT_EQ(pPointLoad3.GetFx(), -11);
      ASSERT_EQ(pPointLoad3.GetFy(), -12);
      ASSERT_EQ(pPointLoad3.GetMz(), -13);

      Float64 fx, fy, mz;
      pPointLoad3.GetForce(&fx, &fy, &mz);
      ASSERT_EQ(fx, -11); ASSERT_EQ(fy, -12); ASSERT_EQ(mz, -13);

      pPointLoad3.SetForce(22, 23, 24);
      pPointLoad3.GetForce(&fx, &fy, &mz);
      ASSERT_EQ(fx, 22); ASSERT_EQ(fy, 23); ASSERT_EQ(mz, 24);

      ASSERT_FALSE(pLoading0.RemovePointLoad(5));
      ASSERT_TRUE(pLoading0.RemovePointLoad(3));
      ASSERT_EQ(pLoading0.GetPointLoadCount(), 1u);
   }
};
} // namespace FEA2DUnitTests
