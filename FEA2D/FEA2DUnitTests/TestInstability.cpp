///////////////////////////////////////////////////////////////////////
// FEA2D - Two-dimensional Finite Element Analysis Engine
// Copyright � 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
///////////////////////////////////////////////////////////////////////
// TestInstability.cpp
//
// Mirrors Fem2d\Fem2dUnitTests\TestInstability.cpp - verifies that
// singular/unstable models throw a well-defined XFEA2D rather than
// crashing or returning garbage. Analyze() isn't part of the public
// interface (see the design note on Model::EnsureAnalyzed() in
// FEA2D\Model.cpp) - every query transparently analyzes on demand, so the
// factoring/back-substitution failures are asserted against a query
// method instead.
#include "pch.h"

namespace FEA2DUnitTests
{

TEST_CLASS(TestInstability)
{
public:
   TEST_METHOD(SingularModelsReturnWellDefinedErrors)
   {
      /*////////////////////////////////////////////////////
              1              2             3
              o--------------o-------------o
              ^       1             1      ^
      *////////////////////////////////////////////////////

      Model model;
      Joint& pJoint1 = model.CreateJoint(1, 0.0, 0.0);
      model.CreateJoint(2, 0.0, 10.0);
      Joint& pJoint3 = model.CreateJoint(3, 0.0, 20.0);

      Float64 E = 29000;
      Float64 A = 10;
      Float64 I = 250;
      Member& pMember1 = model.CreateMember(1, 1, 2, E * A, E * I);
      Member& pMember2 = model.CreateMember(2, 2, 3, E * A, E * I);

      Loading& pLoading0 = model.CreateLoading(0);
      pLoading0.CreateDistributedLoad(1, 1, LoadDirection::Fy, 0.0, -1.0, -0.5, -1.0, LoadOrientation::Member);

      Float64 dx, dy, rz;

      // no boundary conditions - we're flying through space
      ASSERT_THROWS(model.ComputeJointDeflections(0, 2, &dx, &dy, &rz), ReasonCode::MatrixFactoring);

      // support end, should now be cantilever - ok
      pJoint1.Support();
      model.ComputeJointDeflections(0, 2, &dx, &dy, &rz);

      // now a floppy cantilever
      pJoint1.ReleaseDof(JointReleaseType::Mz);
      ASSERT_THROWS(model.ComputeJointDeflections(0, 2, &dx, &dy, &rz), ReasonCode::MatrixBackSubstitution);

      // now pin-pin
      pJoint3.Support();
      pJoint3.ReleaseDof(JointReleaseType::Mz);
      model.ComputeJointDeflections(0, 2, &dx, &dy, &rz);

      // put a hinge in the end of member 1
      pMember1.ReleaseEnd(MemberEndType::End, MemberReleaseType::Mz);
      ASSERT_THROWS(model.ComputeJointDeflections(0, 2, &dx, &dy, &rz), ReasonCode::MatrixBackSubstitution);

      pMember1.ReleaseEnd(MemberEndType::End, MemberReleaseType::None);
      model.ComputeJointDeflections(0, 2, &dx, &dy, &rz);

      // pin at a released dof
      pMember1.ReleaseEnd(MemberEndType::Start, MemberReleaseType::Mz);
      ASSERT_THROWS(model.ComputeJointDeflections(0, 2, &dx, &dy, &rz), ReasonCode::MatrixFactoring);

      // pin at start of member 2
      pMember1.ReleaseEnd(MemberEndType::Start, MemberReleaseType::None);
      pMember2.ReleaseEnd(MemberEndType::Start, MemberReleaseType::Mz);
      ASSERT_THROWS(model.ComputeJointDeflections(0, 2, &dx, &dy, &rz), ReasonCode::MatrixBackSubstitution);
   }
};
} // namespace FEA2DUnitTests
