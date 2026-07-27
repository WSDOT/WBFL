///////////////////////////////////////////////////////////////////////
// FEA2D - Two-dimensional Finite Element Analysis Engine
// Copyright � 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
///////////////////////////////////////////////////////////////////////
// TestJointLoad.cpp
//
// Mirrors Fem2d\Fem2dUnitTests\TestJointLoad.cpp. Omits that file's
// COM-reference-counting section (dropping parent CComPtrs must not
// invalidate a still-held child pointer) - not applicable here, since
// JointLoad* is a raw non-owning pointer into Loading's own storage, not
// a ref-counted COM object.
#include "pch.h"

namespace FEA2DUnitTests
{

TEST_CLASS(TestJointLoad)
{
public:
   TEST_METHOD(BasicJointLoadOperations)
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

      JointLoad& pJointLoad0 = pLoading0.CreateJointLoad(0, 0, 23.2, 42.3, 52.3);
      ASSERT_THROWS(pLoading0.CreateJointLoad(0, 0, 0, 0, 0), ReasonCode::JointLoadWithIdAlreadyExists);
      JointLoad& pJointLoad3 = pLoading0.CreateJointLoad(3, 5, 33, 44, 55);

      ASSERT_EQ(pJointLoad3.GetID(), 3);
      ASSERT_EQ(pJointLoad3.GetJointID(), 5);

      pJointLoad3.SetJointID(42);
      ASSERT_EQ(pJointLoad3.GetJointID(), 42);

      ASSERT_EQ(pJointLoad3.GetFx(), 33);
      ASSERT_EQ(pJointLoad3.GetFy(), 44);
      ASSERT_EQ(pJointLoad3.GetMz(), 55);

      pJointLoad3.SetFx(-11);
      pJointLoad3.SetFy(-12);
      pJointLoad3.SetMz(-13);
      ASSERT_EQ(pJointLoad3.GetFx(), -11);
      ASSERT_EQ(pJointLoad3.GetFy(), -12);
      ASSERT_EQ(pJointLoad3.GetMz(), -13);

      Float64 fx, fy, mz;
      pJointLoad3.GetForce(&fx, &fy, &mz);
      ASSERT_EQ(fx, -11); ASSERT_EQ(fy, -12); ASSERT_EQ(mz, -13);

      pJointLoad3.SetForce(22, 23, 24);
      pJointLoad3.GetForce(&fx, &fy, &mz);
      ASSERT_EQ(fx, 22); ASSERT_EQ(fy, 23); ASSERT_EQ(mz, 24);

      ASSERT_EQ(pJointLoad3.GetLoadingID(), 0);
      ASSERT_EQ(pJointLoad0.GetLoadingID(), 0);
   }
};
} // namespace FEA2DUnitTests
