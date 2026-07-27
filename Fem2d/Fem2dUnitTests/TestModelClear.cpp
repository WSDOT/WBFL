///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
///////////////////////////////////////////////////////////////////////
// TestModelClear.cpp
//
// New coverage: IFem2dModel::ForceEquilibriumTolerance /
// MomentEquilibriumTolerance get/put round-trip, and IFem2dModel::Clear()
// - verifies all four collections (Joints, Members, Loadings, POIs) are
// emptied and that the model remains fully usable (can be rebuilt and
// analyzed) afterward, rather than left in some half-reset state.
//
// Note: deliberately does NOT attempt to trigger CModel::CheckEquilibrium's
// failure path (e.g. via an artificially tight tolerance) - that code path
// hits ATLASSERT(false) before throwing, which would abort a Debug test run.
#include "pch.h"

namespace Fem2dUnitTests
{

TEST_CLASS(TestModelClear)
{
public:
   TEST_METHOD(EquilibriumTolerance_RoundTrip)
   {
      Fem2dModelFixture fixture;
      CComPtr<IFem2dModel>& pmodel = fixture.Model;

      ASSERT_HR(pmodel->put_ForceEquilibriumTolerance(0.001));
      ASSERT_HR(pmodel->put_MomentEquilibriumTolerance(0.002));

      Float64 forceTol, momentTol;
      ASSERT_HR(pmodel->get_ForceEquilibriumTolerance(&forceTol));
      ASSERT_HR(pmodel->get_MomentEquilibriumTolerance(&momentTol));
      ASSERT_TRUE(IsEqual(forceTol, 0.001));
      ASSERT_TRUE(IsEqual(momentTol, 0.002));

      // change and re-verify, to be sure put isn't a no-op
      ASSERT_HR(pmodel->put_ForceEquilibriumTolerance(0.5));
      ASSERT_HR(pmodel->get_ForceEquilibriumTolerance(&forceTol));
      ASSERT_TRUE(IsEqual(forceTol, 0.5));
   }

   TEST_METHOD(Clear_EmptiesAllCollectionsAndModelRemainsUsable)
   {
      Fem2dModelFixture fixture;
      CComPtr<IFem2dModel>& pmodel = fixture.Model;

      CComPtr<IFem2dJointCollection> pJoints;
      ASSERT_HR(pmodel->get_Joints(&pJoints));
      CComPtr<IFem2dJoint> pJoint1, pJoint2;
      ASSERT_MC(fixture, pJoints->Create(1, 0.0, 0.0, &pJoint1));
      ASSERT_MC(fixture, pJoints->Create(2, 10.0, 0.0, &pJoint2));
      ASSERT_MC(fixture, pJoint1->Support());
      ASSERT_MC(fixture, pJoint2->Support());

      CComPtr<IFem2dMemberCollection> pMembers;
      ASSERT_HR(pmodel->get_Members(&pMembers));
      CComPtr<IFem2dMember> pMember1;
      ASSERT_MC(fixture, pMembers->Create(1, 1, 2, 100.0, 100.0, &pMember1));

      CComPtr<IFem2dLoadingCollection> pLoadings;
      ASSERT_HR(pmodel->get_Loadings(&pLoadings));
      CComPtr<IFem2dLoading> pLoading;
      ASSERT_LC(fixture, pLoadings->Create(0, &pLoading));
      CComPtr<IFem2dPointLoadCollection> pPointLoads;
      ASSERT_HR(pLoading->get_PointLoads(&pPointLoads));
      CComPtr<IFem2dPointLoad> pPointLoad;
      ASSERT_LC(fixture, pPointLoads->Create(0, 1, 4.0, 0.0, -1.0, 0.0, lotGlobal, &pPointLoad));

      CComPtr<IFem2dPOICollection> pPOIs;
      ASSERT_HR(pmodel->get_POIs(&pPOIs));
      CComPtr<IFem2dPOI> pPOI;
      ASSERT_HR(pPOIs->Create(1, 1, 5.0, &pPOI));

      IndexType count;
      ASSERT_HR(pJoints->get_Count(&count));
      ASSERT_EQ(count, 2);
      ASSERT_HR(pMembers->get_Count(&count));
      ASSERT_EQ(count, 1);
      ASSERT_HR(pLoadings->get_Count(&count));
      ASSERT_EQ(count, 1);
      ASSERT_HR(pPOIs->get_Count(&count));
      ASSERT_EQ(count, 1);

      ASSERT_HR(pmodel->Clear());

      ASSERT_HR(pJoints->get_Count(&count));
      ASSERT_EQ(count, 0);
      ASSERT_HR(pMembers->get_Count(&count));
      ASSERT_EQ(count, 0);
      ASSERT_HR(pLoadings->get_Count(&count));
      ASSERT_EQ(count, 0);
      ASSERT_HR(pPOIs->get_Count(&count));
      ASSERT_EQ(count, 0);

      // model must remain usable after Clear() - rebuild a minimal stable
      // cantilever and confirm it still analyzes correctly
      CComPtr<IFem2dJoint> pNewJoint1, pNewJoint2;
      ASSERT_MC(fixture, pJoints->Create(1, 0.0, 0.0, &pNewJoint1));
      ASSERT_MC(fixture, pJoints->Create(2, 10.0, 0.0, &pNewJoint2));
      ASSERT_MC(fixture, pNewJoint1->Support());

      CComPtr<IFem2dMember> pNewMember1;
      ASSERT_MC(fixture, pMembers->Create(1, 1, 2, 100.0, 100.0, &pNewMember1));

      CComPtr<IFem2dLoading> pNewLoading;
      ASSERT_LC(fixture, pLoadings->Create(0, &pNewLoading));
      CComPtr<IFem2dJointLoadCollection> pJointLoads;
      ASSERT_HR(pNewLoading->get_JointLoads(&pJointLoads));
      CComPtr<IFem2dJointLoad> pJointLoad;
      ASSERT_LC(fixture, pJointLoads->Create(0, 2, 0.0, -10.0, 0.0, &pJointLoad));

      CComQIPtr<IFem2dModelResults> presults(pmodel);
      Float64 rx, ry, rz;
      ASSERT_HR(presults->ComputeReactions(0, 1, &rx, &ry, &rz));
      ASSERT_TRUE(IsEqual(ry, 10.0));
   }
};
} // namespace Fem2dUnitTests
