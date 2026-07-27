///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
///////////////////////////////////////////////////////////////////////
// TestModelResultsConsistency.cpp
//
// New coverage: cross-checks that IFem2dModelResults, IFem2dModelResultsEx,
// and IFem2dModelResultsForScriptingClients agree with each other on a
// non-trivial (rotated) model. IFem2dModelResults::ComputeMemberForces has
// no orientation parameter; per the rotation cases already verified in
// TestSimpleBeamWithPointLoad, it reports results in *member* coordinates -
// i.e. it must always equal ComputeMemberForcesEx(..., lotMember, ...), and
// (for a rotated member) must differ from ComputeMemberForcesEx(...,
// lotGlobal, ...). This is exactly the kind of triple-redundant surface
// that regresses silently if a future facade rewrite wires one interface's
// dispatch incorrectly.
#include "pch.h"

namespace Fem2dUnitTests
{

TEST_CLASS(TestModelResultsConsistency)
{
public:
   TEST_METHOD(FixedInterface_MatchesExAtMemberOrientation_RotatedModel)
   {
      // Same pin-pin beam as TestSimpleBeamWithPointLoad, rotated 45 degrees
      // clockwise - see
      // TestSimpleBeamWithPointLoad::MidspanPointLoad_PinPin_Rotations for
      // the independently-verified source of these expected values.
      Fem2dModelFixture fixture;
      CComPtr<IFem2dModel>& pmodel = fixture.Model;

      CComPtr<IFem2dJointCollection> pJoints;
      ASSERT_HR(pmodel->get_Joints(&pJoints));

      CComPtr<IFem2dJoint> pJoint0, pJoint8;
      ASSERT_MC(fixture, pJoints->Create(0, 0.0, 0.0, &pJoint0));
      ASSERT_MC(fixture, pJoints->Create(8, 5.6568542, 5.6568542, &pJoint8)); // 8 @ 45 deg

      ASSERT_MC(fixture, pJoint0->Support());
      ASSERT_MC(fixture, pJoint0->ReleaseDof(jrtMz));
      ASSERT_MC(fixture, pJoint8->Support());
      ASSERT_MC(fixture, pJoint8->ReleaseDof(jrtMz));

      CComPtr<IFem2dMemberCollection> pMembers;
      ASSERT_HR(pmodel->get_Members(&pMembers));
      CComPtr<IFem2dMember> pMember1;
      ASSERT_MC(fixture, pMembers->Create(1, 0, 8, 3.0, 7.0, &pMember1));

      CComPtr<IFem2dLoadingCollection> pLoadings;
      ASSERT_HR(pmodel->get_Loadings(&pLoadings));
      CComPtr<IFem2dLoading> pLoading;
      ASSERT_LC(fixture, pLoadings->Create(0, &pLoading));
      CComPtr<IFem2dPointLoadCollection> pPointLoads;
      ASSERT_HR(pLoading->get_PointLoads(&pPointLoads));
      CComPtr<IFem2dPointLoad> pPointLoad;
      // load normal to the rotated structure, applied in global coordinates
      ASSERT_LC(fixture, pPointLoads->Create(0, 1, 4.0, 2.8284271, -2.8284271, 0.0, lotGlobal, &pPointLoad));

      CComQIPtr<IFem2dModelResults> presults(pmodel);
      CComQIPtr<IFem2dModelResultsEx> presultsex(pmodel);
      CComPtr<IFem2dModelResultsForScriptingClients> pscripting;
      ASSERT_HR(pmodel->get_Results(&pscripting));

      Float64 sfx, sfy, smz, efx, efy, emz;
      ASSERT_HR(presults->ComputeMemberForces(0, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 2.0));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 2.0));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      // must match Ex(lotMember) exactly
      Float64 exsfx, exsfy, exsmz, exefx, exefy, exemz;
      ASSERT_HR(presultsex->ComputeMemberForcesEx(0, 1, lotMember, &exsfx, &exsfy, &exsmz, &exefx, &exefy, &exemz));
      ASSERT_TRUE(IsEqual(sfx, exsfx));
      ASSERT_TRUE(IsEqual(sfy, exsfy));
      ASSERT_TRUE(IsEqual(smz, exsmz));
      ASSERT_TRUE(IsEqual(efx, exefx));
      ASSERT_TRUE(IsEqual(efy, exefy));
      ASSERT_TRUE(IsEqual(emz, exemz));

      // must differ from Ex(lotGlobal) on this rotated member - proves the
      // orientation parameter is genuinely taking effect, not a no-op
      Float64 glsfx, glsfy, glsmz, glefx, glefy, glemz;
      ASSERT_HR(presultsex->ComputeMemberForcesEx(0, 1, lotGlobal, &glsfx, &glsfy, &glsmz, &glefx, &glefy, &glemz));
      ASSERT_TRUE(IsEqual(glsfx, -1.41421356));
      ASSERT_TRUE(IsEqual(glsfy, 1.41421356));
      Assert::IsFalse(IsEqual(sfx, glsfx), L"member-basis and global-basis forces should differ on a rotated member");

      // the scripting-client interface (no orientation parameter) must
      // match the member-basis (fixed-signature) results too
      Float64 s_sfx, s_sfy, s_smz, s_efx, s_efy, s_emz;
      ASSERT_HR(pscripting->ComputeMemberForces(0, 1, mdofDxStart, &s_sfx));
      ASSERT_HR(pscripting->ComputeMemberForces(0, 1, mdofDyStart, &s_sfy));
      ASSERT_HR(pscripting->ComputeMemberForces(0, 1, mdofRzStart, &s_smz));
      ASSERT_HR(pscripting->ComputeMemberForces(0, 1, mdofDxEnd, &s_efx));
      ASSERT_HR(pscripting->ComputeMemberForces(0, 1, mdofDyEnd, &s_efy));
      ASSERT_HR(pscripting->ComputeMemberForces(0, 1, mdofRzEnd, &s_emz));
      ASSERT_TRUE(IsEqual(sfx, s_sfx));
      ASSERT_TRUE(IsEqual(sfy, s_sfy));
      ASSERT_TRUE(IsEqual(smz, s_smz));
      ASSERT_TRUE(IsEqual(efx, s_efx));
      ASSERT_TRUE(IsEqual(efy, s_efy));
      ASSERT_TRUE(IsEqual(emz, s_emz));
   }
};
} // namespace Fem2dUnitTests
