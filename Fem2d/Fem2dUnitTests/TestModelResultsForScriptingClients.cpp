///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
///////////////////////////////////////////////////////////////////////
// TestModelResultsForScriptingClients.cpp
//
// New coverage (not present in the legacy Fem2d\Test suite): dedicated
// tests for IFem2dModelResultsForScriptingClients - the VARIANT/single-value
// -friendly result interface intended for VBA/Excel automation clients,
// which is the primary reason the FEM2D COM facade is being retained (see
// the plan). Every value is cross-checked against the fixed-signature
// IFem2dModelResults interface computed on the identical model, so any
// future divergence between the two result surfaces is caught immediately.
#include "pch.h"

namespace Fem2dUnitTests
{

TEST_CLASS(TestModelResultsForScriptingClients)
{
public:
   TEST_METHOD(ScriptingResults_MatchFixedSignatureResults)
   {
      // Same simple pin-pin beam with midspan point load used elsewhere
      // (F:\ARP\WBFL\Fem2d\Test\TestSimpleBeamWithPointLoad.cpp Test1, before
      // rotation) - its expected values are already independently verified
      // by TestSimpleBeamWithPointLoad::MidspanPointLoad_PinPin_Rotations.
      Fem2dModelFixture fixture;
      CComPtr<IFem2dModel>& pmodel = fixture.Model;

      CComPtr<IFem2dJointCollection> pJoints;
      ASSERT_HR(pmodel->get_Joints(&pJoints));

      CComPtr<IFem2dJoint> pJoint0, pJoint8;
      ASSERT_MC(fixture, pJoints->Create(0, 0.0, 0.0, &pJoint0));
      ASSERT_MC(fixture, pJoints->Create(8, 8.0, 0.0, &pJoint8));

      ASSERT_MC(fixture, pJoint0->Support());
      ASSERT_MC(fixture, pJoint0->ReleaseDof(jrtMz));
      ASSERT_MC(fixture, pJoint8->Support());
      ASSERT_MC(fixture, pJoint8->ReleaseDof(jrtFx));
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
      ASSERT_LC(fixture, pPointLoads->Create(0, 1, 4.0, 0.0, -4.0, 0.0, lotGlobal, &pPointLoad));

      CComPtr<IFem2dPOICollection> pPOIs;
      ASSERT_HR(pmodel->get_POIs(&pPOIs));
      CComPtr<IFem2dPOI> pPOI15;
      ASSERT_HR(pPOIs->Create(15, 1, -.25, &pPOI15));

      CComQIPtr<IFem2dModelResults> presults(pmodel);
      CComPtr<IFem2dModelResultsForScriptingClients> pscripting;
      ASSERT_HR(pmodel->get_Results(&pscripting));

      // joint deflections
      Float64 dx, dy, rz;
      ASSERT_HR(presults->ComputeJointDeflections(0, 0, &dx, &dy, &rz));
      Float64 sdx, sdy, srz;
      ASSERT_HR(pscripting->ComputeJointDeflections(0, 0, jdofDx, &sdx));
      ASSERT_HR(pscripting->ComputeJointDeflections(0, 0, jdofDy, &sdy));
      ASSERT_HR(pscripting->ComputeJointDeflections(0, 0, jdofRz, &srz));
      ASSERT_TRUE(IsEqual(dx, sdx));
      ASSERT_TRUE(IsEqual(dy, sdy));
      ASSERT_TRUE(IsEqual(rz, srz));
      ASSERT_TRUE(IsEqual(rz, -2.2857142857143));

      ASSERT_HR(presults->ComputeJointDeflections(0, 8, &dx, &dy, &rz));
      ASSERT_HR(pscripting->ComputeJointDeflections(0, 8, jdofDx, &sdx));
      ASSERT_HR(pscripting->ComputeJointDeflections(0, 8, jdofDy, &sdy));
      ASSERT_HR(pscripting->ComputeJointDeflections(0, 8, jdofRz, &srz));
      ASSERT_TRUE(IsEqual(dx, sdx));
      ASSERT_TRUE(IsEqual(dy, sdy));
      ASSERT_TRUE(IsEqual(rz, srz));
      ASSERT_TRUE(IsEqual(rz, 2.2857142857143));

      // reactions
      Float64 fx, fy, mz;
      ASSERT_HR(presults->ComputeReactions(0, 0, &fx, &fy, &mz));
      Float64 sfx, sfy, smz;
      ASSERT_HR(pscripting->ComputeReactions(0, 0, jdofDx, &sfx));
      ASSERT_HR(pscripting->ComputeReactions(0, 0, jdofDy, &sfy));
      ASSERT_HR(pscripting->ComputeReactions(0, 0, jdofRz, &smz));
      ASSERT_TRUE(IsEqual(fx, sfx));
      ASSERT_TRUE(IsEqual(fy, sfy));
      ASSERT_TRUE(IsEqual(mz, smz));
      ASSERT_TRUE(IsEqual(fy, 2.0));

      // member forces
      Float64 mfsfx, mfsfy, mfsmz, mfefx, mfefy, mfemz;
      ASSERT_HR(presults->ComputeMemberForces(0, 1, &mfsfx, &mfsfy, &mfsmz, &mfefx, &mfefy, &mfemz));
      Float64 s_mfsfx, s_mfsfy, s_mfsmz, s_mfefx, s_mfefy, s_mfemz;
      ASSERT_HR(pscripting->ComputeMemberForces(0, 1, mdofDxStart, &s_mfsfx));
      ASSERT_HR(pscripting->ComputeMemberForces(0, 1, mdofDyStart, &s_mfsfy));
      ASSERT_HR(pscripting->ComputeMemberForces(0, 1, mdofRzStart, &s_mfsmz));
      ASSERT_HR(pscripting->ComputeMemberForces(0, 1, mdofDxEnd, &s_mfefx));
      ASSERT_HR(pscripting->ComputeMemberForces(0, 1, mdofDyEnd, &s_mfefy));
      ASSERT_HR(pscripting->ComputeMemberForces(0, 1, mdofRzEnd, &s_mfemz));
      ASSERT_TRUE(IsEqual(mfsfx, s_mfsfx));
      ASSERT_TRUE(IsEqual(mfsfy, s_mfsfy));
      ASSERT_TRUE(IsEqual(mfsmz, s_mfsmz));
      ASSERT_TRUE(IsEqual(mfefx, s_mfefx));
      ASSERT_TRUE(IsEqual(mfefy, s_mfefy));
      ASSERT_TRUE(IsEqual(mfemz, s_mfemz));
      ASSERT_TRUE(IsEqual(mfsfy, 2.0));

      // member deflections
      Float64 mdsdx, mdsdy, mdsrz, mdedx, mdedy, mderz;
      ASSERT_HR(presults->ComputeMemberDeflections(0, 1, &mdsdx, &mdsdy, &mdsrz, &mdedx, &mdedy, &mderz));
      Float64 s_mdsdx, s_mdsdy, s_mdsrz, s_mdedx, s_mdedy, s_mderz;
      ASSERT_HR(pscripting->ComputeMemberDeflections(0, 1, mdofDxStart, &s_mdsdx));
      ASSERT_HR(pscripting->ComputeMemberDeflections(0, 1, mdofDyStart, &s_mdsdy));
      ASSERT_HR(pscripting->ComputeMemberDeflections(0, 1, mdofRzStart, &s_mdsrz));
      ASSERT_HR(pscripting->ComputeMemberDeflections(0, 1, mdofDxEnd, &s_mdedx));
      ASSERT_HR(pscripting->ComputeMemberDeflections(0, 1, mdofDyEnd, &s_mdedy));
      ASSERT_HR(pscripting->ComputeMemberDeflections(0, 1, mdofRzEnd, &s_mderz));
      ASSERT_TRUE(IsEqual(mdsdx, s_mdsdx));
      ASSERT_TRUE(IsEqual(mdsdy, s_mdsdy));
      ASSERT_TRUE(IsEqual(mdsrz, s_mdsrz));
      ASSERT_TRUE(IsEqual(mdedx, s_mdedx));
      ASSERT_TRUE(IsEqual(mdedy, s_mdedy));
      ASSERT_TRUE(IsEqual(mderz, s_mderz));

      // POI deflections
      ASSERT_HR(presults->ComputePOIDeflections(0, 15, lotGlobal, &dx, &dy, &rz));
      ASSERT_HR(pscripting->ComputePOIDeflections(0, 15, lotGlobal, jdofDx, &sdx));
      ASSERT_HR(pscripting->ComputePOIDeflections(0, 15, lotGlobal, jdofDy, &sdy));
      ASSERT_HR(pscripting->ComputePOIDeflections(0, 15, lotGlobal, jdofRz, &srz));
      ASSERT_TRUE(IsEqual(dx, sdx));
      ASSERT_TRUE(IsEqual(dy, sdy));
      ASSERT_TRUE(IsEqual(rz, srz));
      ASSERT_TRUE(IsEqual(dy, -4.1904761904762));

      // POI forces (both faces)
      ASSERT_HR(presults->ComputePOIForces(0, 15, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_HR(pscripting->ComputePOIForces(0, 15, mftLeft, lotGlobal, jdofDx, &sfx));
      ASSERT_HR(pscripting->ComputePOIForces(0, 15, mftLeft, lotGlobal, jdofDy, &sfy));
      ASSERT_HR(pscripting->ComputePOIForces(0, 15, mftLeft, lotGlobal, jdofRz, &smz));
      ASSERT_TRUE(IsEqual(fx, sfx));
      ASSERT_TRUE(IsEqual(fy, sfy));
      ASSERT_TRUE(IsEqual(mz, smz));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, 4.0));

      ASSERT_HR(presults->ComputePOIForces(0, 15, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_HR(pscripting->ComputePOIForces(0, 15, mftRight, lotGlobal, jdofDx, &sfx));
      ASSERT_HR(pscripting->ComputePOIForces(0, 15, mftRight, lotGlobal, jdofDy, &sfy));
      ASSERT_HR(pscripting->ComputePOIForces(0, 15, mftRight, lotGlobal, jdofRz, &smz));
      ASSERT_TRUE(IsEqual(fx, sfx));
      ASSERT_TRUE(IsEqual(fy, sfy));
      ASSERT_TRUE(IsEqual(mz, smz));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, -4.0));
   }

   TEST_METHOD(ScriptingResults_ErrorPathsMatchFixedSignature)
   {
      Fem2dModelFixture fixture;
      CComPtr<IFem2dModel>& pmodel = fixture.Model;

      CComPtr<IFem2dModelResultsForScriptingClients> pscripting;
      ASSERT_HR(pmodel->get_Results(&pscripting));

      // no joints/members exist yet - should surface the same errors as the
      // fixed-signature interface
      Float64 val;
      ASSERT_EQ(pscripting->ComputeJointDeflections(0, 0, jdofDx, &val), FEM2D_E_MODEL_HAS_NO_JOINTS);

      CComPtr<IFem2dJointCollection> pJoints;
      ASSERT_HR(pmodel->get_Joints(&pJoints));
      CComPtr<IFem2dJoint> pJoint1, pJoint2;
      // model requires >= 2 joints before it will even report a missing
      // member, so create a second joint to isolate the no-members case
      ASSERT_MC(fixture, pJoints->Create(1, 0.0, 0.0, &pJoint1));
      ASSERT_MC(fixture, pJoints->Create(2, 10.0, 0.0, &pJoint2));

      ASSERT_EQ(pscripting->ComputeJointDeflections(0, 0, jdofDx, &val), FEM2D_E_MODEL_HAS_NO_MEMBERS);

      // give the model a member and enough support to be stable so the
      // remaining checks (joint-not-found, null out-param) are isolated
      // from the has-no-members/instability failure paths
      ASSERT_MC(fixture, pJoint1->Support());
      CComPtr<IFem2dMemberCollection> pMembers;
      ASSERT_HR(pmodel->get_Members(&pMembers));
      CComPtr<IFem2dMember> pMember1;
      ASSERT_MC(fixture, pMembers->Create(1, 1, 2, 100.0, 100.0, &pMember1));

      ASSERT_EQ(pscripting->ComputeJointDeflections(0, 99, jdofDx, &val), FEM2D_E_JOINT_NOT_FOUND);

      // null out-param
      ASSERT_EQ(pscripting->ComputeJointDeflections(0, 1, jdofDx, nullptr), E_POINTER);
   }
};
} // namespace Fem2dUnitTests
