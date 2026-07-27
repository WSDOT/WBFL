///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
///////////////////////////////////////////////////////////////////////
// TestSupportMovement.cpp
//
// Ported from F:\ARP\WBFL\Fem2d\Test\TestSupportMovement.cpp
#include "pch.h"

namespace Fem2dUnitTests
{

TEST_CLASS(TestSupportMovement)
{
public:
   // Problem taken from "Matrix Analysis of Structures", Robert F. Sennett,
   // 1994, Chapter 1, Example 1.6 - two-node bar with end support settlement.
   TEST_METHOD(BarTwoMembers_EndSupportSettlement)
   {
      Fem2dModelFixture fixture;
      CComPtr<IFem2dModel>& pmodel = fixture.Model;

      CComPtr<IFem2dJointCollection> pJoints;
      ASSERT_HR(pmodel->get_Joints(&pJoints));

      CComPtr<IFem2dJoint> pJoint1, pJoint2, pJoint3;
      ASSERT_MC(fixture, pJoints->Create(1, 0.0, 0.0, &pJoint1));
      ASSERT_MC(fixture, pJoints->Create(2, 1.0, 0.0, &pJoint2));
      ASSERT_MC(fixture, pJoints->Create(3, 2.0, 0.0, &pJoint3));

      ASSERT_MC(fixture, pJoint1->Support());
      ASSERT_MC(fixture, pJoint3->Support());

      CComPtr<IFem2dMemberCollection> pMembers;
      ASSERT_HR(pmodel->get_Members(&pMembers));

      Float64 EA1 = 5800.0;
      Float64 EA2 = 2900.0;
      Float64 EI = EA1; // whatever
      CComPtr<IFem2dMember> pMember1, pMember2;
      ASSERT_MC(fixture, pMembers->Create(1, 1, 2, EA1, EI, &pMember1));
      ASSERT_MC(fixture, pMembers->Create(2, 2, 3, EA2, EI, &pMember2));

      CComPtr<IFem2dLoadingCollection> pLoadings;
      ASSERT_HR(pmodel->get_Loadings(&pLoadings));
      CComPtr<IFem2dLoading> pLoading;
      ASSERT_LC(fixture, pLoadings->Create(0, &pLoading));

      // apply 25k load to joint 2
      CComPtr<IFem2dJointLoadCollection> pJointLoads;
      ASSERT_HR(pLoading->get_JointLoads(&pJointLoads));
      CComPtr<IFem2dJointLoad> pJointLoad;
      ASSERT_LC(fixture, pJointLoads->Create(0, 2, 25.0, 0.0, 0.0, &pJointLoad));

      // apply settlement load of -0.000862 to joint 3
      CComPtr<IFem2dJointDeflectionCollection> pJointDeflections;
      ASSERT_HR(pLoading->get_JointDeflections(&pJointDeflections));

      CComPtr<IFem2dJointDeflection> pJointDeflection;
      ASSERT_LC(fixture, pJointDeflections->Create(0, 3, -0.00086208, 0.0, 0.0, &pJointDeflection));

      CComQIPtr<IFem2dModelResults> presults(pmodel);

      Float64 dx, dy, rz;
      ASSERT_HR(presults->ComputeJointDeflections(0, 1, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputeJointDeflections(0, 2, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0025862132183908));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputeJointDeflections(0, 3, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, -0.00086208));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      Float64 sfx, sfy, smz, efx, efy, emz;
      ASSERT_HR(presults->ComputeMemberForces(0, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, -15.0, 0.1));
      ASSERT_TRUE(IsEqual(sfy, 0.0, 0.1));
      ASSERT_TRUE(IsEqual(smz, 0.0, 0.1));
      ASSERT_TRUE(IsEqual(efx, 15.0, 0.1));
      ASSERT_TRUE(IsEqual(efy, 0.0, 0.1));
      ASSERT_TRUE(IsEqual(emz, 0.0, 0.1));
      ASSERT_HR(presults->ComputeMemberForces(0, 2, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 10.0, 0.1));
      ASSERT_TRUE(IsEqual(sfy, 0.0, 0.1));
      ASSERT_TRUE(IsEqual(smz, 0.0, 0.1));
      ASSERT_TRUE(IsEqual(efx, -10.0, 0.1));
      ASSERT_TRUE(IsEqual(efy, 0.0, 0.1));
      ASSERT_TRUE(IsEqual(emz, 0.0, 0.1));

      Float64 fx, fy, mz;
      ASSERT_HR(presults->ComputeReactions(0, 1, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -15.0, 0.1));
      ASSERT_TRUE(IsEqual(fy, 0.0, 0.1));
      ASSERT_TRUE(IsEqual(mz, 0.0, 0.1));
      ASSERT_HR(presults->ComputeReactions(0, 2, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0, 0.1));
      ASSERT_TRUE(IsEqual(fy, 0.0, 0.1));
      ASSERT_TRUE(IsEqual(mz, 0.0, 0.1));
      ASSERT_HR(presults->ComputeReactions(0, 3, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -10.0, 0.1));
      ASSERT_TRUE(IsEqual(fy, 0.0, 0.1));
      ASSERT_TRUE(IsEqual(mz, 0.0, 0.1));
   }

   // Problem taken from "Matrix Analysis of Structures", Robert F. Sennett,
   // 1994, Chapter 3, Example 3.6 - two-span beam with mid-span support settlement.
   TEST_METHOD(TwoSpanBeam_MidspanSettlementAndRotation)
   {
      Fem2dModelFixture fixture;
      CComPtr<IFem2dModel>& pmodel = fixture.Model;

      CComPtr<IFem2dJointCollection> pJoints;
      ASSERT_HR(pmodel->get_Joints(&pJoints));

      CComPtr<IFem2dJoint> pJoint1, pJoint2, pJoint3;
      ASSERT_MC(fixture, pJoints->Create(1, 0.0, 0.0, &pJoint1));
      ASSERT_MC(fixture, pJoints->Create(2, 10.0 * 12.0, 0.0, &pJoint2));
      ASSERT_MC(fixture, pJoints->Create(3, 20.0 * 12.0, 0.0, &pJoint3));

      ASSERT_MC(fixture, pJoint1->Support());
      ASSERT_MC(fixture, pJoint2->Support());
      ASSERT_MC(fixture, pJoint2->ReleaseDof(jrtFx));
      ASSERT_MC(fixture, pJoint2->ReleaseDof(jrtMz));
      ASSERT_MC(fixture, pJoint3->Support());
      ASSERT_MC(fixture, pJoint3->ReleaseDof(jrtFx));
      ASSERT_MC(fixture, pJoint3->ReleaseDof(jrtMz));

      CComPtr<IFem2dMemberCollection> pMembers;
      ASSERT_HR(pmodel->get_Members(&pMembers));

      Float64 EI = 2.90e06;
      Float64 EA = EI; // whatever
      CComPtr<IFem2dMember> pMember1, pMember2;
      ASSERT_MC(fixture, pMembers->Create(1, 1, 2, EA, EI, &pMember1));
      ASSERT_MC(fixture, pMembers->Create(2, 2, 3, EA, EI, &pMember2));

      CComPtr<IFem2dLoadingCollection> pLoadings;
      ASSERT_HR(pmodel->get_Loadings(&pLoadings));
      CComPtr<IFem2dLoading> pLoading;
      ASSERT_LC(fixture, pLoadings->Create(0, &pLoading));
      CComPtr<IFem2dJointDeflectionCollection> pJointDeflections;
      ASSERT_HR(pLoading->get_JointDeflections(&pJointDeflections));
      CComPtr<IFem2dJointDeflection> pJointDeflection;
      ASSERT_LC(fixture, pJointDeflections->Create(0, 2, 0.0, -0.25, 0.0, &pJointDeflection));

      CComQIPtr<IFem2dModelResults> presults(pmodel);

      Float64 dx, dy, rz;
      ASSERT_HR(presults->ComputeJointDeflections(0, 1, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputeJointDeflections(0, 2, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -0.25));
      ASSERT_TRUE(IsEqual(rz, -0.000892857));
      ASSERT_HR(presults->ComputeJointDeflections(0, 3, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.00357142));

      Float64 sfx, sfy, smz, efx, efy, emz;
      ASSERT_HR(presults->ComputeMemberForces(0, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 3.955853174));
      ASSERT_TRUE(IsEqual(smz, 258.9285714));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, -3.9558531746));
      ASSERT_TRUE(IsEqual(emz, 215.77380952));
      ASSERT_HR(presults->ComputeMemberForces(0, 2, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, -1.79811507936));
      ASSERT_TRUE(IsEqual(smz, -215.77380952381));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 1.79811507936));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      Float64 fx, fy, mz;
      ASSERT_HR(presults->ComputeReactions(0, 1, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 3.95585317));
      ASSERT_TRUE(IsEqual(mz, 258.92857142));
      ASSERT_HR(presults->ComputeReactions(0, 2, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -5.75396825));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputeReactions(0, 3, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 1.79811507936));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      //////////////////////////////////////////////////////////////
      // next let's try a joint rotation - first free up the model and
      // remove the existing load
      ASSERT_MC(fixture, pJoint2->Free());
      ASSERT_MC(fixture, pJoint3->Support());
      LoadIDType id;
      ASSERT_LC(fixture, pJointDeflections->Remove(0, atID, &id));
      ASSERT_EQ(id, 0);

      // add a rotation of 0.1 at joint 3
      CComPtr<IFem2dJointDeflection> pJointDeflection2;
      ASSERT_LC(fixture, pJointDeflections->Create(0, 3, 0.0, 0.0, 0.1, &pJointDeflection2));

      ASSERT_HR(presults->ComputeJointDeflections(0, 1, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputeJointDeflections(0, 2, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -3.0));
      ASSERT_TRUE(IsEqual(rz, -0.025));
      ASSERT_HR(presults->ComputeJointDeflections(0, 3, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.1));

      ASSERT_HR(presults->ComputeMemberForces(0, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 30.208333));
      ASSERT_TRUE(IsEqual(smz, 2416.666667));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, -30.208333));
      ASSERT_TRUE(IsEqual(emz, 1208.33333));
      ASSERT_HR(presults->ComputeMemberForces(0, 2, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 30.208333));
      ASSERT_TRUE(IsEqual(smz, -1208.33333));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, -30.208333));
      ASSERT_TRUE(IsEqual(emz, 4833.333333));

      ASSERT_HR(presults->ComputeReactions(0, 1, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 30.208333));
      ASSERT_TRUE(IsEqual(mz, 2416.666667));
      ASSERT_HR(presults->ComputeReactions(0, 2, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputeReactions(0, 3, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -30.208333));
      ASSERT_TRUE(IsEqual(mz, 4833.333333));
   }

   // Problem taken from "Matrix Analysis of Structures", Robert F. Sennett,
   // 1994, Chapter 2, Example 2.3 - simple truss with support settlement at
   // two joints.
   TEST_METHOD(Truss_SennettExample2_3_SupportSettlement)
   {
      Fem2dModelFixture fixture;
      CComPtr<IFem2dModel>& pmodel = fixture.Model;

      CComPtr<IFem2dJointCollection> pJoints;
      ASSERT_HR(pmodel->get_Joints(&pJoints));

      CComPtr<IFem2dJoint> pJoint1, pJoint2, pJoint3, pJoint4;
      ASSERT_MC(fixture, pJoints->Create(1, 0.0, 0.0, &pJoint1));
      ASSERT_MC(fixture, pJoints->Create(2, 10.0 * 12.0, 10.0 * 12.0, &pJoint2));
      ASSERT_MC(fixture, pJoints->Create(3, 20.0 * 12.0, 10.0 * 12.0, &pJoint3));
      ASSERT_MC(fixture, pJoints->Create(4, 30.0 * 12.0, 0.0, &pJoint4));

      ASSERT_MC(fixture, pJoint1->Support());
      ASSERT_MC(fixture, pJoint2->Support());
      ASSERT_MC(fixture, pJoint2->ReleaseDof(jrtFx));
      ASSERT_MC(fixture, pJoint2->ReleaseDof(jrtFy));
      ASSERT_MC(fixture, pJoint3->Support());
      ASSERT_MC(fixture, pJoint3->ReleaseDof(jrtFx));
      ASSERT_MC(fixture, pJoint3->ReleaseDof(jrtFy));
      ASSERT_MC(fixture, pJoint4->Support());

      CComPtr<IFem2dMemberCollection> pMembers;
      ASSERT_HR(pmodel->get_Members(&pMembers));

      Float64 E = 29.0e06;
      Float64 EA = E * 2.0;
      Float64 EI = 1.0e29; // dummy since all members are pinned
      CComPtr<IFem2dMember> pMember1, pMember2, pMember3, pMember4, pMember5;
      ASSERT_MC(fixture, pMembers->Create(1, 1, 2, EA, EI, &pMember1));
      ASSERT_MC(fixture, pMembers->Create(2, 2, 3, EA, EI, &pMember2));
      ASSERT_MC(fixture, pMembers->Create(3, 3, 4, EA, EI, &pMember3));
      ASSERT_MC(fixture, pMembers->Create(4, 1, 3, EA, EI, &pMember4));
      ASSERT_MC(fixture, pMembers->Create(5, 2, 4, EA, EI, &pMember5));

      // pin 'em
      ASSERT_MC(fixture, pMember1->ReleaseEnd(metStart, mbrReleaseMz));
      ASSERT_MC(fixture, pMember1->ReleaseEnd(metEnd, mbrReleaseMz));
      ASSERT_MC(fixture, pMember2->ReleaseEnd(metStart, mbrReleaseMz));
      ASSERT_MC(fixture, pMember2->ReleaseEnd(metEnd, mbrReleaseMz));
      ASSERT_MC(fixture, pMember3->ReleaseEnd(metStart, mbrReleaseMz));
      ASSERT_MC(fixture, pMember3->ReleaseEnd(metEnd, mbrReleaseMz));
      ASSERT_MC(fixture, pMember4->ReleaseEnd(metStart, mbrReleaseMz));
      ASSERT_MC(fixture, pMember4->ReleaseEnd(metEnd, mbrReleaseMz));
      ASSERT_MC(fixture, pMember5->ReleaseEnd(metStart, mbrReleaseMz));
      ASSERT_MC(fixture, pMember5->ReleaseEnd(metEnd, mbrReleaseMz));

      CComPtr<IFem2dLoadingCollection> pLoadings;
      ASSERT_HR(pmodel->get_Loadings(&pLoadings));
      CComPtr<IFem2dLoading> pLoading;
      ASSERT_LC(fixture, pLoadings->Create(0, &pLoading));
      CComPtr<IFem2dJointLoadCollection> pJointLoads;
      ASSERT_HR(pLoading->get_JointLoads(&pJointLoads));

      CComPtr<IFem2dJointLoad> pJointLoad;
      ASSERT_LC(fixture, pJointLoads->Create(0, 2, 0.0, -30000.0, 0.0, &pJointLoad));

      // another joint load applied at a fixity to make sure reactions are added correctly
      CComPtr<IFem2dJointLoad> pJointLoad4;
      ASSERT_LC(fixture, pJointLoads->Create(4, 4, 0.0, -20000.0, 0.0, &pJointLoad4));

      // apply joint deflections at joints 1 and 4
      CComPtr<IFem2dJointDeflectionCollection> pJointDeflections;
      ASSERT_HR(pLoading->get_JointDeflections(&pJointDeflections));
      CComPtr<IFem2dJointDeflection> pJointDeflection1;
      ASSERT_LC(fixture, pJointDeflections->Create(1, 1, 0.0, -0.60, 0.0, &pJointDeflection1));
      CComPtr<IFem2dJointDeflection> pJointDeflection4;
      ASSERT_LC(fixture, pJointDeflections->Create(4, 4, -0.3, 0.0, 0.0, &pJointDeflection4));

      LoadCaseIDType ld;
      ASSERT_HR(pJointDeflection4->get_Loading(&ld));
      ASSERT_EQ(ld, 0);

      // apply deflection to a free dof - should error until removed
      CComPtr<IFem2dJointDeflection> pJointDeflection5;
      ASSERT_LC(fixture, pJointDeflections->Create(5, 2, -0.3, 0.0, 0.0, &pJointDeflection5));

      CComQIPtr<IFem2dModelResults> presults(pmodel);

      Float64 dx, dy, rz;
      ASSERT_EQ(presults->ComputeJointDeflections(0, 1, &dx, &dy, &rz), FEM2D_E_JOINT_DISP_TO_FIXED_DOF_ONLY);
      LoadIDType id;
      ASSERT_LC(fixture, pJointDeflections->Remove(5, atID, &id));
      ASSERT_EQ(id, 5);

      ASSERT_HR(presults->ComputeJointDeflections(0, 1, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -0.6));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputeJointDeflections(0, 2, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, -0.33847916063898));
      ASSERT_TRUE(IsEqual(dy, -0.36436867720659));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputeJointDeflections(0, 3, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, -0.32342783496097));
      ASSERT_TRUE(IsEqual(dy, -0.0092373090239415));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputeJointDeflections(0, 4, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, -0.3));
      ASSERT_TRUE(IsEqual(dy, -0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      Float64 sfx, sfy, smz, efx, efy, emz;
      ASSERT_HR(presults->ComputeMemberForces(0, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 24854.89414));
      ASSERT_TRUE(IsEqual(sfy, 0.0));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, -24854.89414));
      ASSERT_TRUE(IsEqual(efy, 0.0));
      ASSERT_TRUE(IsEqual(emz, 0.0));
      ASSERT_HR(presults->ComputeMemberForces(0, 4, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 5422.32129));
      ASSERT_TRUE(IsEqual(sfy, 0.0));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, -5422.32129));
      ASSERT_TRUE(IsEqual(efy, 0.0));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      Float64 fx, fy, mz;
      ASSERT_HR(presults->ComputeReactions(0, 1, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 22424.9358));
      ASSERT_TRUE(IsEqual(fy, 20000.0000));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputeReactions(0, 4, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -22424.9358));
      ASSERT_TRUE(IsEqual(fy, 30000.0000)); // has point load added in
      ASSERT_TRUE(IsEqual(mz, 0.0));
   }
};
} // namespace Fem2dUnitTests
