///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
///////////////////////////////////////////////////////////////////////
// TestMemberStrains2.cpp
//
// Ported from F:\ARP\WBFL\Fem2d\Test\TestMemberStrains2.cpp
#include "pch.h"

namespace Fem2dUnitTests
{

TEST_CLASS(TestMemberStrains2)
{
public:
   // Problem taken from "Matrix Analysis of Structures", Robert F. Sennett,
   // 1994, Chapter 2, Example 2.6 - simple truss with temperature load
   // applied to the top member.
   TEST_METHOD(Truss_SennettExample2_6)
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
      CComPtr<IFem2dMemberStrainCollection> pMemberStrains;
      ASSERT_HR(pLoading->get_MemberStrains(&pMemberStrains));

      Float64 strain = -40.0 * 6.5e-6;
      CComPtr<IFem2dMemberStrain> pMemberStrain;
      ASSERT_LC(fixture, pMemberStrains->Create(0, 2, 0.0, -1.0, strain, 0.0, &pMemberStrain));

      CComQIPtr<IFem2dModelResults> presults(pmodel);

      Float64 dx, dy, rz;
      ASSERT_HR(presults->ComputeJointDeflections(0, 1, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputeJointDeflections(0, 2, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.011807202783764));
      ASSERT_TRUE(IsEqual(dy, -0.004655435767055));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputeJointDeflections(0, 3, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, -0.011807202783764));
      ASSERT_TRUE(IsEqual(dy, -0.004655435767055));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputeJointDeflections(0, 4, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, -0.0));
      ASSERT_TRUE(IsEqual(dy, -0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      Float64 sfx, sfy, smz, efx, efy, emz;
      ASSERT_HR(presults->ComputeMemberForces(0, 2, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, -3666.37064));
      ASSERT_TRUE(IsEqual(sfy, 0.0));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 3666.37064));
      ASSERT_TRUE(IsEqual(efy, 0.0));
      ASSERT_TRUE(IsEqual(emz, 0.0));
      ASSERT_HR(presults->ComputeMemberForces(0, 4, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 2732.7513290));
      ASSERT_TRUE(IsEqual(sfy, 0.0));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, -2732.7513290));
      ASSERT_TRUE(IsEqual(efy, 0.0));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      Float64 fx, fy, mz;
      ASSERT_HR(presults->ComputeReactions(0, 1, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 1222.1235474538));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputeReactions(0, 4, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -1222.1235474538));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
   }

   // Verified using GT-Strudl - output file is TempLoads.gto (see
   // F:\ARP\WBFL\Fem2d\Test\ for the original fixture).
   TEST_METHOD(StrudlBeam_FourSpans_MultipleLoadCases)
   {
      Fem2dModelFixture fixture;
      CComPtr<IFem2dModel>& pmodel = fixture.Model;

      CComPtr<IFem2dJointCollection> pJoints;
      ASSERT_HR(pmodel->get_Joints(&pJoints));

      CComPtr<IFem2dJoint> pJoint1, pJoint2, pJoint3, pJoint4, pJoint5;
      ASSERT_MC(fixture, pJoints->Create(1, 0.0, 0.0, &pJoint1));
      ASSERT_MC(fixture, pJoints->Create(2, 25.0, 0.0, &pJoint2));
      ASSERT_MC(fixture, pJoints->Create(3, 50.0, 0.0, &pJoint3));
      ASSERT_MC(fixture, pJoints->Create(4, 75.0, 0.0, &pJoint4));
      ASSERT_MC(fixture, pJoints->Create(5, 100.0, 0.0, &pJoint5));

      ASSERT_MC(fixture, pJoint1->Support());
      ASSERT_MC(fixture, pJoint5->Support());

      Float64 E = 100.0;
      Float64 A = 100.0;
      Float64 I = 833.333;
      Float64 EA = E * A;
      Float64 EI = E * I;

      CComPtr<IFem2dMemberCollection> pMembers;
      ASSERT_HR(pmodel->get_Members(&pMembers));
      CComPtr<IFem2dMember> pMember1, pMember2, pMember3, pMember4;
      ASSERT_MC(fixture, pMembers->Create(1, 1, 2, EA, EI, &pMember1));
      ASSERT_MC(fixture, pMembers->Create(2, 2, 3, EA, EI, &pMember2));
      ASSERT_MC(fixture, pMembers->Create(3, 3, 4, EA, EI, &pMember3));
      ASSERT_MC(fixture, pMembers->Create(4, 4, 5, EA, EI, &pMember4));

      // put pois at quarter points on members 1 and 3
      CComPtr<IFem2dPOICollection> pPOIs;
      ASSERT_HR(pmodel->get_POIs(&pPOIs));
      CComPtr<IFem2dPOI> pPOI1_000, pPOI1_025, pPOI1_050, pPOI1_075, pPOI1_100;
      ASSERT_HR(pPOIs->Create(1000, 1, 0.00, &pPOI1_000));
      ASSERT_HR(pPOIs->Create(1025, 1, -0.25, &pPOI1_025));
      ASSERT_HR(pPOIs->Create(1050, 1, -0.50, &pPOI1_050));
      ASSERT_HR(pPOIs->Create(1075, 1, -0.75, &pPOI1_075));
      ASSERT_HR(pPOIs->Create(1100, 1, -1.00, &pPOI1_100));

      CComPtr<IFem2dPOI> pPOI3_000, pPOI3_025, pPOI3_050, pPOI3_075, pPOI3_100;
      ASSERT_HR(pPOIs->Create(3000, 3, 0.00, &pPOI3_000));
      ASSERT_HR(pPOIs->Create(3025, 3, -0.25, &pPOI3_025));
      ASSERT_HR(pPOIs->Create(3050, 3, -0.50, &pPOI3_050));
      ASSERT_HR(pPOIs->Create(3075, 3, -0.75, &pPOI3_075));
      ASSERT_HR(pPOIs->Create(3100, 3, -1.00, &pPOI3_100));

      // coeff of thermal expansion = 1.0, delta T = 800.0 degrees, section depth = 10.0
      Float64 strain = 0.1 * 800.0 / 10.0;

      CComPtr<IFem2dLoadingCollection> pLoadings;
      ASSERT_HR(pmodel->get_Loadings(&pLoadings));
      CComPtr<IFem2dLoading> pLoading1, pLoading2, pLoading3, pLoading4, pLoading5;

      // loading 1 - all members loaded
      ASSERT_HR(pLoadings->Create(1, &pLoading1));
      CComPtr<IFem2dMemberStrainCollection> pMemberStrains;
      ASSERT_HR(pLoading1->get_MemberStrains(&pMemberStrains));
      CComPtr<IFem2dMemberStrain> pMemberStrain1, pMemberStrain2, pMemberStrain3, pMemberStrain4;
      ASSERT_LC(fixture, pMemberStrains->Create(1, 1, 0.0, -1.0, 0.0, strain, &pMemberStrain1));
      ASSERT_LC(fixture, pMemberStrains->Create(2, 2, 0.0, -1.0, 0.0, strain, &pMemberStrain2));
      ASSERT_LC(fixture, pMemberStrains->Create(3, 3, 0.0, -1.0, 0.0, strain, &pMemberStrain3));
      ASSERT_LC(fixture, pMemberStrains->Create(4, 4, 0.0, -1.0, 0.0, strain, &pMemberStrain4));

      // loading 2 - members 1 and 3 loaded
      ASSERT_HR(pLoadings->Create(2, &pLoading2));
      pMemberStrains = 0;
      ASSERT_HR(pLoading2->get_MemberStrains(&pMemberStrains));
      pMemberStrain1 = pMemberStrain2 = pMemberStrain3 = pMemberStrain4 = 0;
      ASSERT_LC(fixture, pMemberStrains->Create(1, 1, 0.0, -1.0, 0.0, strain, &pMemberStrain1));
      ASSERT_LC(fixture, pMemberStrains->Create(3, 3, 0.0, -1.0, 0.0, strain, &pMemberStrain3));

      // loading 3 - members 2 and 4 loaded
      ASSERT_HR(pLoadings->Create(3, &pLoading3));
      pMemberStrains = 0;
      ASSERT_HR(pLoading3->get_MemberStrains(&pMemberStrains));
      pMemberStrain1 = pMemberStrain2 = pMemberStrain3 = pMemberStrain4 = 0;
      ASSERT_LC(fixture, pMemberStrains->Create(2, 2, 0.0, -1.0, 0.0, strain, &pMemberStrain2));
      ASSERT_LC(fixture, pMemberStrains->Create(4, 4, 0.0, -1.0, 0.0, strain, &pMemberStrain4));

      // loading 4 - member 1 loaded only
      ASSERT_HR(pLoadings->Create(4, &pLoading4));
      pMemberStrains = 0;
      ASSERT_HR(pLoading4->get_MemberStrains(&pMemberStrains));
      pMemberStrain1 = pMemberStrain2 = pMemberStrain3 = pMemberStrain4 = 0;
      ASSERT_LC(fixture, pMemberStrains->Create(1, 1, 0.0, -1.0, 0.0, strain, &pMemberStrain1));

      // loading 5 - member 4 loaded only
      ASSERT_LC(fixture, pLoadings->Create(5, &pLoading5));
      pMemberStrains = 0;
      ASSERT_HR(pLoading5->get_MemberStrains(&pMemberStrains));
      pMemberStrain1 = pMemberStrain2 = pMemberStrain3 = pMemberStrain4 = 0;
      ASSERT_LC(fixture, pMemberStrains->Create(1, 4, 0.0, -1.0, 0.0, strain, &pMemberStrain4));

      CComQIPtr<IFem2dModelResults> presults(pmodel);

      // results for loading 1
      LoadCaseIDType lc = 1;
      Float64 dx, dy, rz;
      ASSERT_HR(presults->ComputeJointDeflections(lc, 1, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputeJointDeflections(lc, 2, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputeJointDeflections(lc, 3, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputeJointDeflections(lc, 4, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputeJointDeflections(lc, 5, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      Float64 sfx, sfy, smz, efx, efy, emz;
      ASSERT_HR(presults->ComputeMemberForces(lc, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 0.0));
      ASSERT_TRUE(IsEqual(smz, 666666.40));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 0.0));
      ASSERT_TRUE(IsEqual(emz, -666666.40));
      ASSERT_HR(presults->ComputeMemberForces(lc, 2, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 0.0));
      ASSERT_TRUE(IsEqual(smz, 666666.40));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 0.0));
      ASSERT_TRUE(IsEqual(emz, -666666.40));
      ASSERT_HR(presults->ComputeMemberForces(lc, 3, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 0.0));
      ASSERT_TRUE(IsEqual(smz, 666666.40));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 0.0));
      ASSERT_TRUE(IsEqual(emz, -666666.40));
      ASSERT_HR(presults->ComputeMemberForces(lc, 4, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 0.0));
      ASSERT_TRUE(IsEqual(smz, 666666.40));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 0.0));
      ASSERT_TRUE(IsEqual(emz, -666666.40));

      Float64 fx, fy, mz;
      ASSERT_HR(presults->ComputeReactions(lc, 1, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 666666.40));
      ASSERT_HR(presults->ComputeReactions(lc, 2, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputeReactions(lc, 3, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputeReactions(lc, 4, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputeReactions(lc, 5, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, -666666.40));

      ASSERT_HR(presults->ComputePOIDeflections(lc, 1000, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(lc, 1050, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(lc, 1100, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      ASSERT_HR(presults->ComputePOIForces(lc, 1100, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, -666666.40));
      ASSERT_HR(presults->ComputePOIForces(lc, 1100, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 666666.40));
      ASSERT_HR(presults->ComputePOIForces(lc, 1075, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, -666666.40));
      ASSERT_HR(presults->ComputePOIForces(lc, 1075, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 666666.40));

      // results for loading 2
      lc = 2;
      ASSERT_HR(presults->ComputeJointDeflections(lc, 1, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputeJointDeflections(lc, 2, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 468.7500000));
      ASSERT_TRUE(IsEqual(rz, 43.75));
      ASSERT_HR(presults->ComputeJointDeflections(lc, 3, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -75.0));
      ASSERT_HR(presults->ComputeJointDeflections(lc, 4, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -468.7500000));
      ASSERT_TRUE(IsEqual(rz, 43.75));
      ASSERT_HR(presults->ComputeJointDeflections(lc, 5, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      ASSERT_HR(presults->ComputeMemberForces(lc, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 4999.99800));
      ASSERT_TRUE(IsEqual(smz, 583333.09999));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, -4999.99800));
      ASSERT_TRUE(IsEqual(emz, -458333.15000));
      ASSERT_HR(presults->ComputeMemberForces(lc, 2, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 4999.99800));
      ASSERT_TRUE(IsEqual(smz, 458333.15000));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, -4999.99800));
      ASSERT_TRUE(IsEqual(emz, -333333.20000));
      ASSERT_HR(presults->ComputeMemberForces(lc, 3, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 4999.99800));
      ASSERT_TRUE(IsEqual(smz, 333333.20000));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, -4999.99800));
      ASSERT_TRUE(IsEqual(emz, -208333.24999));
      ASSERT_HR(presults->ComputeMemberForces(lc, 4, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 4999.9980));
      ASSERT_TRUE(IsEqual(smz, 208333.24999));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, -4999.99800));
      ASSERT_TRUE(IsEqual(emz, -83333.30000));

      ASSERT_HR(presults->ComputeReactions(lc, 1, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 4999.99800));
      ASSERT_TRUE(IsEqual(mz, 583333.09999));
      ASSERT_HR(presults->ComputeReactions(lc, 2, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputeReactions(lc, 3, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputeReactions(lc, 4, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputeReactions(lc, 5, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -4999.99800));
      ASSERT_TRUE(IsEqual(mz, -83333.30000));

      ASSERT_HR(presults->ComputePOIDeflections(lc, 1000, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(lc, 1050, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 97.656250000000));
      ASSERT_TRUE(IsEqual(rz, 17.187500000000));
      ASSERT_HR(presults->ComputePOIDeflections(lc, 1100, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 468.7500000));
      ASSERT_TRUE(IsEqual(rz, 43.75));

      ASSERT_HR(presults->ComputePOIForces(lc, 1100, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -4999.99800));
      ASSERT_TRUE(IsEqual(mz, -458333.15000));
      ASSERT_HR(presults->ComputePOIForces(lc, 1100, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 4999.99800));
      ASSERT_TRUE(IsEqual(mz, 458333.15000));
      ASSERT_HR(presults->ComputePOIForces(lc, 1075, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -4999.99800));
      ASSERT_TRUE(IsEqual(mz, -489583.13750));
      ASSERT_HR(presults->ComputePOIForces(lc, 1075, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 4999.99800));
      ASSERT_TRUE(IsEqual(mz, 489583.1375));

      // results for loading 5
      lc = 5;
      ASSERT_HR(presults->ComputeJointDeflections(lc, 1, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputeJointDeflections(lc, 2, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 546.8750000));
      ASSERT_TRUE(IsEqual(rz, 34.375));
      ASSERT_HR(presults->ComputeJointDeflections(lc, 3, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 1250.0));
      ASSERT_TRUE(IsEqual(rz, 12.50));
      ASSERT_HR(presults->ComputeJointDeflections(lc, 4, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 703.125));
      ASSERT_TRUE(IsEqual(rz, -65.625));
      ASSERT_HR(presults->ComputeJointDeflections(lc, 5, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      ASSERT_HR(presults->ComputeMemberForces(lc, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, -7499.99700));
      ASSERT_TRUE(IsEqual(smz, -208333.25000));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 7499.99700));
      ASSERT_TRUE(IsEqual(emz, 20833.32500));
      ASSERT_HR(presults->ComputeMemberForces(lc, 2, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, -7499.99700));
      ASSERT_TRUE(IsEqual(smz, -20833.32500));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 7499.99700));
      ASSERT_TRUE(IsEqual(emz, -166666.60000));
      ASSERT_HR(presults->ComputeMemberForces(lc, 3, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, -7499.99700));
      ASSERT_TRUE(IsEqual(smz, 166666.60000));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 7499.99700));
      ASSERT_TRUE(IsEqual(emz, -354166.52500));
      ASSERT_HR(presults->ComputeMemberForces(lc, 4, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, -7499.99700));
      ASSERT_TRUE(IsEqual(smz, 354166.52500));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 7499.99700));
      ASSERT_TRUE(IsEqual(emz, -541666.45000));

      ASSERT_HR(presults->ComputeReactions(lc, 1, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -7499.99700));
      ASSERT_TRUE(IsEqual(mz, -208333.25000));
      ASSERT_HR(presults->ComputeReactions(lc, 2, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputeReactions(lc, 3, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputeReactions(lc, 4, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputeReactions(lc, 5, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 7499.99700));
      ASSERT_TRUE(IsEqual(mz, -541666.45000));

      ASSERT_HR(presults->ComputePOIDeflections(lc, 1000, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(lc, 1050, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 166.01562500000));
      ASSERT_TRUE(IsEqual(rz, 24.218750000000));
      ASSERT_HR(presults->ComputePOIDeflections(lc, 1100, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 546.8750000));
      ASSERT_TRUE(IsEqual(rz, 34.375));

      ASSERT_HR(presults->ComputePOIForces(lc, 1100, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 7499.99700));
      ASSERT_TRUE(IsEqual(mz, 20833.32500));
      ASSERT_HR(presults->ComputePOIForces(lc, 1100, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -7499.99700));
      ASSERT_TRUE(IsEqual(mz, -20833.32500));
      ASSERT_HR(presults->ComputePOIForces(lc, 1075, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 7499.99700));
      ASSERT_TRUE(IsEqual(mz, 67708.30625));
      ASSERT_HR(presults->ComputePOIForces(lc, 1075, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -7499.99700));
      ASSERT_TRUE(IsEqual(mz, -67708.30625));
   }

   // Differs from StrudlBeam_FourSpans_MultipleLoadCases in that only one
   // member is used (verified against the same GT-Strudl TempLoads.gto).
   TEST_METHOD(StrudlBeam_SingleMember)
   {
      Fem2dModelFixture fixture;
      CComPtr<IFem2dModel>& pmodel = fixture.Model;

      CComPtr<IFem2dJointCollection> pJoints;
      ASSERT_HR(pmodel->get_Joints(&pJoints));

      CComPtr<IFem2dJoint> pJoint1, pJoint2;
      ASSERT_MC(fixture, pJoints->Create(1, 0.0, 0.0, &pJoint1));
      ASSERT_MC(fixture, pJoints->Create(2, 100.0, 0.0, &pJoint2));

      ASSERT_MC(fixture, pJoint1->Support());
      ASSERT_MC(fixture, pJoint2->Support());

      Float64 E = 100.0;
      Float64 A = 100.0;
      Float64 I = 833.333;
      Float64 EA = E * A;
      Float64 EI = E * I;

      CComPtr<IFem2dMemberCollection> pMembers;
      ASSERT_HR(pmodel->get_Members(&pMembers));
      CComPtr<IFem2dMember> pMember1;
      ASSERT_MC(fixture, pMembers->Create(1, 1, 2, EA, EI, &pMember1));

      // put pois at 1/16 points on quarter points 1 and 3
      CComPtr<IFem2dPOICollection> pPOIs;
      ASSERT_HR(pmodel->get_POIs(&pPOIs));
      CComPtr<IFem2dPOI> pPOI1_000, pPOI1_025, pPOI1_050, pPOI1_075, pPOI1_100;
      ASSERT_HR(pPOIs->Create(1000, 1, 0.00, &pPOI1_000));
      ASSERT_HR(pPOIs->Create(1025, 1, -0.0625, &pPOI1_025));
      ASSERT_HR(pPOIs->Create(1050, 1, -0.1250, &pPOI1_050));
      ASSERT_HR(pPOIs->Create(1075, 1, -0.1875, &pPOI1_075));
      ASSERT_HR(pPOIs->Create(1100, 1, -0.25, &pPOI1_100));

      CComPtr<IFem2dPOI> pPOI3_000, pPOI3_025, pPOI3_050, pPOI3_075, pPOI3_100;
      ASSERT_HR(pPOIs->Create(3000, 1, -0.50 - 0.00, &pPOI3_000));
      ASSERT_HR(pPOIs->Create(3025, 1, -0.50 - 0.0625, &pPOI3_025));
      ASSERT_HR(pPOIs->Create(3050, 1, -0.50 - 0.1250, &pPOI3_050));
      ASSERT_HR(pPOIs->Create(3075, 1, -0.50 - 0.1875, &pPOI3_075));
      ASSERT_HR(pPOIs->Create(3100, 1, -0.50 - 0.25, &pPOI3_100));

      // coeff of thermal expansion = 1.0, delta T = 800.0 degrees, section depth = 10.0
      Float64 strain = 0.1 * 800.0 / 10.0;

      CComPtr<IFem2dLoadingCollection> pLoadings;
      ASSERT_HR(pmodel->get_Loadings(&pLoadings));
      CComPtr<IFem2dLoading> pLoading1;

      // can only model loading 1 since we only have a single member
      ASSERT_LC(fixture, pLoadings->Create(1, &pLoading1));
      CComPtr<IFem2dMemberStrainCollection> pMemberStrains;
      ASSERT_HR(pLoading1->get_MemberStrains(&pMemberStrains));
      CComPtr<IFem2dMemberStrain> pMemberStrain1;
      ASSERT_LC(fixture, pMemberStrains->Create(1, 1, 0.0, -1.0, 0.0, strain, &pMemberStrain1));

      CComQIPtr<IFem2dModelResults> presults(pmodel);

      LoadCaseIDType lc = 1;
      Float64 dx, dy, rz;
      ASSERT_HR(presults->ComputeJointDeflections(lc, 1, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputeJointDeflections(lc, 2, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      Float64 sfx, sfy, smz, efx, efy, emz;
      ASSERT_HR(presults->ComputeMemberForces(lc, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 0.0));
      ASSERT_TRUE(IsEqual(smz, 666666.40));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 0.0));
      ASSERT_TRUE(IsEqual(emz, -666666.40));

      Float64 fx, fy, mz;
      ASSERT_HR(presults->ComputeReactions(lc, 1, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 666666.40));
      ASSERT_HR(presults->ComputeReactions(lc, 2, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, -666666.40));

      ASSERT_HR(presults->ComputePOIDeflections(lc, 1000, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(lc, 1100, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(lc, 3000, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(lc, 3100, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      ASSERT_HR(presults->ComputePOIForces(lc, 1100, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, -666666.40));
      ASSERT_HR(presults->ComputePOIForces(lc, 1100, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 666666.40));
      ASSERT_HR(presults->ComputePOIForces(lc, 1075, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, -666666.40));
      ASSERT_HR(presults->ComputePOIForces(lc, 1075, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 666666.40));
      ASSERT_HR(presults->ComputePOIForces(lc, 3000, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, -666666.40));
      ASSERT_HR(presults->ComputePOIForces(lc, 3000, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 666666.40));

      //////////////////////////////////////////////////////////////
      // release the starting end of the beam
      ASSERT_MC(fixture, pMember1->ReleaseEnd(metStart, mbrReleaseMz));
      ASSERT_HR(presults->ComputeJointDeflections(lc, 1, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputeJointDeflections(lc, 2, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      ASSERT_HR(presults->ComputeMemberForces(lc, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, -9999.99600));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 9999.99600));
      ASSERT_TRUE(IsEqual(emz, -999999.60000));

      ASSERT_HR(presults->ComputeReactions(lc, 1, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -9999.99600));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputeReactions(lc, 2, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 9999.99600));
      ASSERT_TRUE(IsEqual(mz, -999999.6000));

      ASSERT_HR(presults->ComputePOIDeflections(lc, 1000, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -200.0));
      ASSERT_HR(presults->ComputePOIDeflections(lc, 1100, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -2812.5));
      ASSERT_TRUE(IsEqual(rz, -37.50));

      ASSERT_HR(presults->ComputePOIDeflections(lc, 3000, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -2500.0));
      ASSERT_TRUE(IsEqual(rz, 50.0));
      ASSERT_HR(presults->ComputePOIDeflections(lc, 3100, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -937.5000));
      ASSERT_TRUE(IsEqual(rz, 62.50));

      ASSERT_HR(presults->ComputePOIForces(lc, 1000, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 9999.99600));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(lc, 1100, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 9999.99600));
      ASSERT_TRUE(IsEqual(mz, -249999.90000));
      ASSERT_HR(presults->ComputePOIForces(lc, 1100, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -9999.99600));
      ASSERT_TRUE(IsEqual(mz, 249999.90000));
      ASSERT_HR(presults->ComputePOIForces(lc, 1075, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 9999.99600));
      ASSERT_TRUE(IsEqual(mz, -187499.925));
      ASSERT_HR(presults->ComputePOIForces(lc, 1075, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -9999.99600));
      ASSERT_TRUE(IsEqual(mz, 187499.925));
      ASSERT_HR(presults->ComputePOIForces(lc, 3000, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 9999.99600));
      ASSERT_TRUE(IsEqual(mz, -499999.8));
      ASSERT_HR(presults->ComputePOIForces(lc, 3000, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -9999.99600));
      ASSERT_TRUE(IsEqual(mz, 499999.8));
      ASSERT_HR(presults->ComputePOIForces(lc, 3050, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -9999.99600));
      ASSERT_TRUE(IsEqual(mz, 624999.75000));
      ASSERT_HR(presults->ComputePOIForces(lc, 3075, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -9999.99600));
      ASSERT_TRUE(IsEqual(mz, 687499.72500));
   }

   // Problem taken from "Matrix Analysis of Structures", Robert F. Sennett,
   // 1994, Chapter 3, Example 3.5 - half portal frame with temperature strain loads.
   TEST_METHOD(HalfPortalFrame_SennettExample3_5)
   {
      Fem2dModelFixture fixture;
      CComPtr<IFem2dModel>& pmodel = fixture.Model;

      CComPtr<IFem2dJointCollection> pJoints;
      ASSERT_HR(pmodel->get_Joints(&pJoints));

      CComPtr<IFem2dJoint> pJoint1, pJoint2, pJoint3;
      ASSERT_MC(fixture, pJoints->Create(1, 0.0, 0.0, &pJoint1));
      ASSERT_MC(fixture, pJoints->Create(2, 0.0, 12.0 * 12.0, &pJoint2));
      ASSERT_MC(fixture, pJoints->Create(3, 7.0 * 12.0, 12.0 * 12.0, &pJoint3));

      ASSERT_MC(fixture, pJoint1->Support());
      ASSERT_MC(fixture, pJoint3->Support());

      CComPtr<IFem2dMemberCollection> pMembers;
      ASSERT_HR(pmodel->get_Members(&pMembers));

      Float64 E = 30.0e06;
      Float64 A = 20.0;
      Float64 I = 100.0;
      Float64 EA = E * A;
      Float64 EI = E * I;
      CComPtr<IFem2dMember> pMember1, pMember2;
      ASSERT_MC(fixture, pMembers->Create(1, 1, 2, EA, EI, &pMember1));
      ASSERT_MC(fixture, pMembers->Create(2, 2, 3, EA, EI, &pMember2));

      // apply both axial and curvature strains to member 2: net temperature
      // rise of 35 deg, differential temperature of 70 deg (hotter on top),
      // section depth = 10
      Float64 saxial = 6.5e-06 * 35.0;
      Float64 scurv = -6.5e-06 * 70.0 / 10.0;
      CComPtr<IFem2dLoadingCollection> pLoadings;
      ASSERT_HR(pmodel->get_Loadings(&pLoadings));
      CComPtr<IFem2dLoading> pLoading;
      ASSERT_LC(fixture, pLoadings->Create(0, &pLoading));
      CComPtr<IFem2dMemberStrainCollection> pMemberStrains;
      ASSERT_HR(pLoading->get_MemberStrains(&pMemberStrains));
      CComPtr<IFem2dMemberStrain> pMemberStrain2;
      ASSERT_LC(fixture, pMemberStrains->Create(1, 2, 0.0, -1.0, saxial, scurv, &pMemberStrain2));

      CComQIPtr<IFem2dModelResults> presults(pmodel);

      Float64 dx, dy, rz;
      ASSERT_HR(presults->ComputeJointDeflections(0, 1, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputeJointDeflections(0, 2, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, -0.019160498123460));
      ASSERT_TRUE(IsEqual(dy, -0.00041133776877044));
      ASSERT_TRUE(IsEqual(rz, 0.00068164544539101));
      ASSERT_HR(presults->ComputeJointDeflections(0, 3, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      Float64 sfx, sfy, smz, efx, efy, emz;
      ASSERT_HR(presults->ComputeMemberForces(0, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 1713.90736));
      ASSERT_TRUE(IsEqual(sfy, 360.70088));
      ASSERT_TRUE(IsEqual(smz, 11769.51671));
      ASSERT_TRUE(IsEqual(efx, -1713.90736));
      ASSERT_TRUE(IsEqual(efy, -360.70088));
      ASSERT_TRUE(IsEqual(emz, 40171.41027));
      ASSERT_HR(presults->ComputeMemberForces(0, 2, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, -360.70088));
      ASSERT_TRUE(IsEqual(sfy, 1713.90736));
      ASSERT_TRUE(IsEqual(smz, -40171.41027));
      ASSERT_TRUE(IsEqual(efx, 360.70088));
      ASSERT_TRUE(IsEqual(efy, -1713.90736));
      ASSERT_TRUE(IsEqual(emz, 184139.62934));

      Float64 fx, fy, mz;
      ASSERT_HR(presults->ComputeReactions(0, 1, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -360.700881));
      ASSERT_TRUE(IsEqual(fy, 1713.907369));
      ASSERT_TRUE(IsEqual(mz, 11769.516714));
      ASSERT_HR(presults->ComputeReactions(0, 2, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputeReactions(0, 3, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 360.7008818));
      ASSERT_TRUE(IsEqual(fy, -1713.9073698));
      ASSERT_TRUE(IsEqual(mz, 184139.6293422));
   }
};
} // namespace Fem2dUnitTests
