///////////////////////////////////////////////////////////////////////
// FEA2D - Two-dimensional Finite Element Analysis Engine
// Copyright � 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
///////////////////////////////////////////////////////////////////////
// TestModelResultsConsistency.cpp
//
// Adapted from Fem2d\Fem2dUnitTests\TestModelResultsConsistency.cpp. That
// test cross-checked three redundant legacy COM result interfaces
// (IFem2dModelResults/Ex/ForScriptingClients) against each other; FEA2D's
// Model has a single ComputeMemberForces(..., orientation, ...) signature
// instead - the facade is what fans this one surface out to the three
// legacy interfaces, so there's nothing to cross-check between interfaces
// here.
// What's still genuinely worth covering: that the orientation parameter on
// a rotated member actually takes effect (member-basis and global-basis
// results must differ) and matches the exact values independently
// verified via the real legacy COM engine.
#include "pch.h"

namespace FEA2DUnitTests
{

TEST_CLASS(TestModelResultsConsistency)
{
public:
   TEST_METHOD(MemberOrientation_DiffersFromGlobal_OnRotatedModel)
   {
      // Same pin-pin beam as TestSimpleBeamWithPointLoad, rotated 45 degrees
      Model model;
      Joint& pJoint0 = model.CreateJoint(0, 0.0, 0.0);
      Joint& pJoint8 = model.CreateJoint(8, 5.6568542, 5.6568542); // 8 @ 45 deg

      pJoint0.Support();
      pJoint0.ReleaseDof(JointReleaseType::Mz);
      pJoint8.Support();
      pJoint8.ReleaseDof(JointReleaseType::Mz);

      model.CreateMember(1, 0, 8, 3.0, 7.0);

      Loading& pLoading = model.CreateLoading(0);
      // load normal to the rotated structure, applied in global coordinates
      pLoading.CreatePointLoad(0, 1, 4.0, 2.8284271, -2.8284271, 0.0, LoadOrientation::Global);


      Float64 sfx, sfy, smz, efx, efy, emz;
      model.ComputeMemberForces(0, 1, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 2.0));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 2.0));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      Float64 glsfx, glsfy, glsmz, glefx, glefy, glemz;
      model.ComputeMemberForces(0, 1, LoadOrientation::Global, &glsfx, &glsfy, &glsmz, &glefx, &glefy, &glemz);
      ASSERT_TRUE(IsEqual(glsfx, -1.41421356));
      ASSERT_TRUE(IsEqual(glsfy, 1.41421356));
      Assert::IsFalse(IsEqual(sfx, glsfx), L"member-basis and global-basis forces should differ on a rotated member");
   }
};
} // namespace FEA2DUnitTests
