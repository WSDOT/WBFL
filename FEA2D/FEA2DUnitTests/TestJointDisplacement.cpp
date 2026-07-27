///////////////////////////////////////////////////////////////////////
// FEA2D - Two-dimensional Finite Element Analysis Engine
// Copyright � 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
///////////////////////////////////////////////////////////////////////
// TestJointDisplacement.cpp
//
// Mirrors Fem2d\Fem2dUnitTests\TestJointDisplacement.cpp. Omits the COM
// reference-counting section - see the note in TestJointLoad.cpp.
#include "pch.h"

namespace FEA2DUnitTests
{

TEST_CLASS(TestJointDisplacement)
{
public:
   TEST_METHOD(BasicJointDeflectionOperations)
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

      JointDisplacement& pJointDisp0 = pLoading0.CreateJointDisplacement(0, 0, 23.2, 42.3, 52.3);
      ASSERT_THROWS(pLoading0.CreateJointDisplacement(0, 0, 0, 0, 0), ReasonCode::JointDispWithIdAlreadyExists);
      JointDisplacement& pJointDisp3 = pLoading0.CreateJointDisplacement(3, 5, 33, 44, 55);

      ASSERT_EQ(pJointDisp3.GetID(), 3);
      ASSERT_EQ(pJointDisp3.GetJointID(), 5);

      pJointDisp3.SetJointID(42);
      ASSERT_EQ(pJointDisp3.GetJointID(), 42);

      ASSERT_EQ(pJointDisp3.GetDx(), 33);
      ASSERT_EQ(pJointDisp3.GetDy(), 44);
      ASSERT_EQ(pJointDisp3.GetRz(), 55);

      pJointDisp3.SetDx(-11);
      pJointDisp3.SetDy(-12);
      pJointDisp3.SetRz(-13);
      ASSERT_EQ(pJointDisp3.GetDx(), -11);
      ASSERT_EQ(pJointDisp3.GetDy(), -12);
      ASSERT_EQ(pJointDisp3.GetRz(), -13);

      Float64 dx, dy, rz;
      pJointDisp3.GetDeflection(&dx, &dy, &rz);
      ASSERT_EQ(dx, -11); ASSERT_EQ(dy, -12); ASSERT_EQ(rz, -13);

      pJointDisp3.SetDeflection(22, 23, 24);
      pJointDisp3.GetDeflection(&dx, &dy, &rz);
      ASSERT_EQ(dx, 22); ASSERT_EQ(dy, 23); ASSERT_EQ(rz, 24);

      ASSERT_EQ(pJointDisp0.GetLoadingID(), 0);
   }
};
} // namespace FEA2DUnitTests
