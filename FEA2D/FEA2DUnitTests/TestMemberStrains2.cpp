///////////////////////////////////////////////////////////////////////
// FEA2D - Two-dimensional Finite Element Analysis Engine
// Copyright � 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
///////////////////////////////////////////////////////////////////////
// TestMemberStrains2.cpp
//
// Mirrors Fem2d\Fem2dUnitTests\TestMemberStrains2.cpp
#include "pch.h"

namespace FEA2DUnitTests
{

TEST_CLASS(TestMemberStrains2)
{
public:
   // Problem taken from "Matrix Analysis of Structures", Robert F. Sennett,
   // 1994, Chapter 2, Example 2.6 - simple truss with temperature load
   // applied to the top member.
   TEST_METHOD(Truss_SennettExample2_6)
   {
      Model model;
      model.CreateJoint(1, 0.0, 0.0);
      Joint& pJoint2 = model.CreateJoint(2, 10.0 * 12.0, 10.0 * 12.0);
      Joint& pJoint3 = model.CreateJoint(3, 20.0 * 12.0, 10.0 * 12.0);
      model.CreateJoint(4, 30.0 * 12.0, 0.0);

      model.FindJoint(1)->Support();
      pJoint2.Support();
      pJoint2.ReleaseDof(JointReleaseType::Fx);
      pJoint2.ReleaseDof(JointReleaseType::Fy);
      pJoint3.Support();
      pJoint3.ReleaseDof(JointReleaseType::Fx);
      pJoint3.ReleaseDof(JointReleaseType::Fy);
      model.FindJoint(4)->Support();

      Float64 E = 29.0e06;
      Float64 EA = E * 2.0;
      Float64 EI = 1.0e29; // dummy since all members are pinned
      Member& pMember1 = model.CreateMember(1, 1, 2, EA, EI);
      Member& pMember2 = model.CreateMember(2, 2, 3, EA, EI);
      Member& pMember3 = model.CreateMember(3, 3, 4, EA, EI);
      Member& pMember4 = model.CreateMember(4, 1, 3, EA, EI);
      Member& pMember5 = model.CreateMember(5, 2, 4, EA, EI);

      // pin 'em
      pMember1.ReleaseEnd(MemberEndType::Start, MemberReleaseType::Mz);
      pMember1.ReleaseEnd(MemberEndType::End, MemberReleaseType::Mz);
      pMember2.ReleaseEnd(MemberEndType::Start, MemberReleaseType::Mz);
      pMember2.ReleaseEnd(MemberEndType::End, MemberReleaseType::Mz);
      pMember3.ReleaseEnd(MemberEndType::Start, MemberReleaseType::Mz);
      pMember3.ReleaseEnd(MemberEndType::End, MemberReleaseType::Mz);
      pMember4.ReleaseEnd(MemberEndType::Start, MemberReleaseType::Mz);
      pMember4.ReleaseEnd(MemberEndType::End, MemberReleaseType::Mz);
      pMember5.ReleaseEnd(MemberEndType::Start, MemberReleaseType::Mz);
      pMember5.ReleaseEnd(MemberEndType::End, MemberReleaseType::Mz);

      Loading& pLoading = model.CreateLoading(0);

      Float64 strain = -40.0 * 6.5e-6;
      pLoading.CreateMemberStrain(0, 2, 0.0, -1.0, strain, 0.0);


      Float64 dx, dy, rz;
      model.ComputeJointDeflections(0, 1, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputeJointDeflections(0, 2, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.011807202783764));
      ASSERT_TRUE(IsEqual(dy, -0.004655435767055));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputeJointDeflections(0, 3, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, -0.011807202783764));
      ASSERT_TRUE(IsEqual(dy, -0.004655435767055));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputeJointDeflections(0, 4, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, -0.0));
      ASSERT_TRUE(IsEqual(dy, -0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      Float64 sfx, sfy, smz, efx, efy, emz;
      model.ComputeMemberForces(0, 2, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, -3666.37064));
      ASSERT_TRUE(IsEqual(sfy, 0.0));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 3666.37064));
      ASSERT_TRUE(IsEqual(efy, 0.0));
      ASSERT_TRUE(IsEqual(emz, 0.0));
      model.ComputeMemberForces(0, 4, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 2732.7513290));
      ASSERT_TRUE(IsEqual(sfy, 0.0));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, -2732.7513290));
      ASSERT_TRUE(IsEqual(efy, 0.0));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      Float64 fx, fy, mz;
      model.ComputeReactions(0, 1, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 1222.1235474538));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputeReactions(0, 4, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -1222.1235474538));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
   }

   // Verified using GT-Strudl - output file is TempLoads.gto (see
   // Fem2d\Test\ for the original fixture).
   TEST_METHOD(StrudlBeam_FourSpans_MultipleLoadCases)
   {
      Model model;
      model.CreateJoint(1, 0.0, 0.0);
      model.CreateJoint(2, 25.0, 0.0);
      model.CreateJoint(3, 50.0, 0.0);
      model.CreateJoint(4, 75.0, 0.0);
      model.CreateJoint(5, 100.0, 0.0);

      model.FindJoint(1)->Support();
      model.FindJoint(5)->Support();

      Float64 E = 100.0;
      Float64 A = 100.0;
      Float64 I = 833.333;
      Float64 EA = E * A;
      Float64 EI = E * I;

      model.CreateMember(1, 1, 2, EA, EI);
      model.CreateMember(2, 2, 3, EA, EI);
      model.CreateMember(3, 3, 4, EA, EI);
      model.CreateMember(4, 4, 5, EA, EI);

      // put pois at quarter points on members 1 and 3
      model.CreatePOI(1000, 1, 0.00);
      model.CreatePOI(1025, 1, -0.25);
      model.CreatePOI(1050, 1, -0.50);
      model.CreatePOI(1075, 1, -0.75);
      model.CreatePOI(1100, 1, -1.00);

      model.CreatePOI(3000, 3, 0.00);
      model.CreatePOI(3025, 3, -0.25);
      model.CreatePOI(3050, 3, -0.50);
      model.CreatePOI(3075, 3, -0.75);
      model.CreatePOI(3100, 3, -1.00);

      // coeff of thermal expansion = 1.0, delta T = 800.0 degrees, section depth = 10.0
      Float64 strain = 0.1 * 800.0 / 10.0;

      // loading 1 - all members loaded
      Loading& pLoading1 = model.CreateLoading(1);
      pLoading1.CreateMemberStrain(1, 1, 0.0, -1.0, 0.0, strain);
      pLoading1.CreateMemberStrain(2, 2, 0.0, -1.0, 0.0, strain);
      pLoading1.CreateMemberStrain(3, 3, 0.0, -1.0, 0.0, strain);
      pLoading1.CreateMemberStrain(4, 4, 0.0, -1.0, 0.0, strain);

      // loading 2 - members 1 and 3 loaded
      Loading& pLoading2 = model.CreateLoading(2);
      pLoading2.CreateMemberStrain(1, 1, 0.0, -1.0, 0.0, strain);
      pLoading2.CreateMemberStrain(3, 3, 0.0, -1.0, 0.0, strain);

      // loading 3 - members 2 and 4 loaded
      Loading& pLoading3 = model.CreateLoading(3);
      pLoading3.CreateMemberStrain(2, 2, 0.0, -1.0, 0.0, strain);
      pLoading3.CreateMemberStrain(4, 4, 0.0, -1.0, 0.0, strain);

      // loading 4 - member 1 loaded only
      Loading& pLoading4 = model.CreateLoading(4);
      pLoading4.CreateMemberStrain(1, 1, 0.0, -1.0, 0.0, strain);

      // loading 5 - member 4 loaded only
      Loading& pLoading5 = model.CreateLoading(5);
      pLoading5.CreateMemberStrain(1, 4, 0.0, -1.0, 0.0, strain);


      // results for loading 1
      LoadCaseIDType lc = 1;
      Float64 dx, dy, rz;
      model.ComputeJointDeflections(lc, 1, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputeJointDeflections(lc, 2, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputeJointDeflections(lc, 3, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputeJointDeflections(lc, 4, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputeJointDeflections(lc, 5, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      Float64 sfx, sfy, smz, efx, efy, emz;
      model.ComputeMemberForces(lc, 1, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 0.0));
      ASSERT_TRUE(IsEqual(smz, 666666.40));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 0.0));
      ASSERT_TRUE(IsEqual(emz, -666666.40));
      model.ComputeMemberForces(lc, 2, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 0.0));
      ASSERT_TRUE(IsEqual(smz, 666666.40));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 0.0));
      ASSERT_TRUE(IsEqual(emz, -666666.40));
      model.ComputeMemberForces(lc, 3, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 0.0));
      ASSERT_TRUE(IsEqual(smz, 666666.40));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 0.0));
      ASSERT_TRUE(IsEqual(emz, -666666.40));
      model.ComputeMemberForces(lc, 4, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 0.0));
      ASSERT_TRUE(IsEqual(smz, 666666.40));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 0.0));
      ASSERT_TRUE(IsEqual(emz, -666666.40));

      Float64 fx, fy, mz;
      model.ComputeReactions(lc, 1, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 666666.40));
      model.ComputeReactions(lc, 2, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputeReactions(lc, 3, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputeReactions(lc, 4, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputeReactions(lc, 5, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, -666666.40));

      model.ComputePOIDeflections(lc, 1000, LoadOrientation::Global, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputePOIDeflections(lc, 1050, LoadOrientation::Global, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputePOIDeflections(lc, 1100, LoadOrientation::Global, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      model.ComputePOIForces(lc, 1100, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, -666666.40));
      model.ComputePOIForces(lc, 1100, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 666666.40));
      model.ComputePOIForces(lc, 1075, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, -666666.40));
      model.ComputePOIForces(lc, 1075, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 666666.40));

      // results for loading 2
      lc = 2;
      model.ComputeJointDeflections(lc, 1, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputeJointDeflections(lc, 2, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 468.7500000));
      ASSERT_TRUE(IsEqual(rz, 43.75));
      model.ComputeJointDeflections(lc, 3, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -75.0));
      model.ComputeJointDeflections(lc, 4, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -468.7500000));
      ASSERT_TRUE(IsEqual(rz, 43.75));
      model.ComputeJointDeflections(lc, 5, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      model.ComputeMemberForces(lc, 1, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 4999.99800));
      ASSERT_TRUE(IsEqual(smz, 583333.09999));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, -4999.99800));
      ASSERT_TRUE(IsEqual(emz, -458333.15000));
      model.ComputeMemberForces(lc, 2, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 4999.99800));
      ASSERT_TRUE(IsEqual(smz, 458333.15000));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, -4999.99800));
      ASSERT_TRUE(IsEqual(emz, -333333.20000));
      model.ComputeMemberForces(lc, 3, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 4999.99800));
      ASSERT_TRUE(IsEqual(smz, 333333.20000));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, -4999.99800));
      ASSERT_TRUE(IsEqual(emz, -208333.24999));
      model.ComputeMemberForces(lc, 4, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 4999.9980));
      ASSERT_TRUE(IsEqual(smz, 208333.24999));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, -4999.99800));
      ASSERT_TRUE(IsEqual(emz, -83333.30000));

      model.ComputeReactions(lc, 1, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 4999.99800));
      ASSERT_TRUE(IsEqual(mz, 583333.09999));
      model.ComputeReactions(lc, 2, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputeReactions(lc, 3, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputeReactions(lc, 4, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputeReactions(lc, 5, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -4999.99800));
      ASSERT_TRUE(IsEqual(mz, -83333.30000));

      model.ComputePOIDeflections(lc, 1000, LoadOrientation::Global, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputePOIDeflections(lc, 1050, LoadOrientation::Global, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 97.656250000000));
      ASSERT_TRUE(IsEqual(rz, 17.187500000000));
      model.ComputePOIDeflections(lc, 1100, LoadOrientation::Global, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 468.7500000));
      ASSERT_TRUE(IsEqual(rz, 43.75));

      model.ComputePOIForces(lc, 1100, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -4999.99800));
      ASSERT_TRUE(IsEqual(mz, -458333.15000));
      model.ComputePOIForces(lc, 1100, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 4999.99800));
      ASSERT_TRUE(IsEqual(mz, 458333.15000));
      model.ComputePOIForces(lc, 1075, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -4999.99800));
      ASSERT_TRUE(IsEqual(mz, -489583.13750));
      model.ComputePOIForces(lc, 1075, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 4999.99800));
      ASSERT_TRUE(IsEqual(mz, 489583.1375));

      // results for loading 5
      lc = 5;
      model.ComputeJointDeflections(lc, 1, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputeJointDeflections(lc, 2, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 546.8750000));
      ASSERT_TRUE(IsEqual(rz, 34.375));
      model.ComputeJointDeflections(lc, 3, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 1250.0));
      ASSERT_TRUE(IsEqual(rz, 12.50));
      model.ComputeJointDeflections(lc, 4, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 703.125));
      ASSERT_TRUE(IsEqual(rz, -65.625));
      model.ComputeJointDeflections(lc, 5, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      model.ComputeMemberForces(lc, 1, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, -7499.99700));
      ASSERT_TRUE(IsEqual(smz, -208333.25000));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 7499.99700));
      ASSERT_TRUE(IsEqual(emz, 20833.32500));
      model.ComputeMemberForces(lc, 2, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, -7499.99700));
      ASSERT_TRUE(IsEqual(smz, -20833.32500));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 7499.99700));
      ASSERT_TRUE(IsEqual(emz, -166666.60000));
      model.ComputeMemberForces(lc, 3, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, -7499.99700));
      ASSERT_TRUE(IsEqual(smz, 166666.60000));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 7499.99700));
      ASSERT_TRUE(IsEqual(emz, -354166.52500));
      model.ComputeMemberForces(lc, 4, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, -7499.99700));
      ASSERT_TRUE(IsEqual(smz, 354166.52500));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 7499.99700));
      ASSERT_TRUE(IsEqual(emz, -541666.45000));

      model.ComputeReactions(lc, 1, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -7499.99700));
      ASSERT_TRUE(IsEqual(mz, -208333.25000));
      model.ComputeReactions(lc, 2, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputeReactions(lc, 3, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputeReactions(lc, 4, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputeReactions(lc, 5, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 7499.99700));
      ASSERT_TRUE(IsEqual(mz, -541666.45000));

      model.ComputePOIDeflections(lc, 1000, LoadOrientation::Global, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputePOIDeflections(lc, 1050, LoadOrientation::Global, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 166.01562500000));
      ASSERT_TRUE(IsEqual(rz, 24.218750000000));
      model.ComputePOIDeflections(lc, 1100, LoadOrientation::Global, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 546.8750000));
      ASSERT_TRUE(IsEqual(rz, 34.375));

      model.ComputePOIForces(lc, 1100, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 7499.99700));
      ASSERT_TRUE(IsEqual(mz, 20833.32500));
      model.ComputePOIForces(lc, 1100, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -7499.99700));
      ASSERT_TRUE(IsEqual(mz, -20833.32500));
      model.ComputePOIForces(lc, 1075, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 7499.99700));
      ASSERT_TRUE(IsEqual(mz, 67708.30625));
      model.ComputePOIForces(lc, 1075, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -7499.99700));
      ASSERT_TRUE(IsEqual(mz, -67708.30625));
   }

   // Differs from StrudlBeam_FourSpans_MultipleLoadCases in that only one
   // member is used (verified against the same GT-Strudl TempLoads.gto).
   TEST_METHOD(StrudlBeam_SingleMember)
   {
      Model model;
      model.CreateJoint(1, 0.0, 0.0);
      model.CreateJoint(2, 100.0, 0.0);

      model.FindJoint(1)->Support();
      model.FindJoint(2)->Support();

      Float64 E = 100.0;
      Float64 A = 100.0;
      Float64 I = 833.333;
      Float64 EA = E * A;
      Float64 EI = E * I;

      Member& pMember1 = model.CreateMember(1, 1, 2, EA, EI);

      // put pois at 1/16 points on quarter points 1 and 3
      model.CreatePOI(1000, 1, 0.00);
      model.CreatePOI(1025, 1, -0.0625);
      model.CreatePOI(1050, 1, -0.1250);
      model.CreatePOI(1075, 1, -0.1875);
      model.CreatePOI(1100, 1, -0.25);

      model.CreatePOI(3000, 1, -0.50 - 0.00);
      model.CreatePOI(3025, 1, -0.50 - 0.0625);
      model.CreatePOI(3050, 1, -0.50 - 0.1250);
      model.CreatePOI(3075, 1, -0.50 - 0.1875);
      model.CreatePOI(3100, 1, -0.50 - 0.25);

      // coeff of thermal expansion = 1.0, delta T = 800.0 degrees, section depth = 10.0
      Float64 strain = 0.1 * 800.0 / 10.0;

      // can only model loading 1 since we only have a single member
      Loading& pLoading1 = model.CreateLoading(1);
      pLoading1.CreateMemberStrain(1, 1, 0.0, -1.0, 0.0, strain);


      LoadCaseIDType lc = 1;
      Float64 dx, dy, rz;
      model.ComputeJointDeflections(lc, 1, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputeJointDeflections(lc, 2, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      Float64 sfx, sfy, smz, efx, efy, emz;
      model.ComputeMemberForces(lc, 1, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 0.0));
      ASSERT_TRUE(IsEqual(smz, 666666.40));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 0.0));
      ASSERT_TRUE(IsEqual(emz, -666666.40));

      Float64 fx, fy, mz;
      model.ComputeReactions(lc, 1, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 666666.40));
      model.ComputeReactions(lc, 2, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, -666666.40));

      model.ComputePOIDeflections(lc, 1000, LoadOrientation::Global, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputePOIDeflections(lc, 1100, LoadOrientation::Global, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputePOIDeflections(lc, 3000, LoadOrientation::Global, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputePOIDeflections(lc, 3100, LoadOrientation::Global, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      model.ComputePOIForces(lc, 1100, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, -666666.40));
      model.ComputePOIForces(lc, 1100, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 666666.40));
      model.ComputePOIForces(lc, 1075, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, -666666.40));
      model.ComputePOIForces(lc, 1075, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 666666.40));
      model.ComputePOIForces(lc, 3000, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, -666666.40));
      model.ComputePOIForces(lc, 3000, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 666666.40));

      //////////////////////////////////////////////////////////////
      // release the starting end of the beam
      pMember1.ReleaseEnd(MemberEndType::Start, MemberReleaseType::Mz);


      model.ComputeJointDeflections(lc, 1, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputeJointDeflections(lc, 2, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      model.ComputeMemberForces(lc, 1, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, -9999.99600));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 9999.99600));
      ASSERT_TRUE(IsEqual(emz, -999999.60000));

      model.ComputeReactions(lc, 1, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -9999.99600));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputeReactions(lc, 2, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 9999.99600));
      ASSERT_TRUE(IsEqual(mz, -999999.6000));

      model.ComputePOIDeflections(lc, 1000, LoadOrientation::Global, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -200.0));
      model.ComputePOIDeflections(lc, 1100, LoadOrientation::Global, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -2812.5));
      ASSERT_TRUE(IsEqual(rz, -37.50));

      model.ComputePOIDeflections(lc, 3000, LoadOrientation::Global, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -2500.0));
      ASSERT_TRUE(IsEqual(rz, 50.0));
      model.ComputePOIDeflections(lc, 3100, LoadOrientation::Global, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -937.5000));
      ASSERT_TRUE(IsEqual(rz, 62.50));

      model.ComputePOIForces(lc, 1000, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 9999.99600));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputePOIForces(lc, 1100, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 9999.99600));
      ASSERT_TRUE(IsEqual(mz, -249999.90000));
      model.ComputePOIForces(lc, 1100, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -9999.99600));
      ASSERT_TRUE(IsEqual(mz, 249999.90000));
      model.ComputePOIForces(lc, 1075, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 9999.99600));
      ASSERT_TRUE(IsEqual(mz, -187499.925));
      model.ComputePOIForces(lc, 1075, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -9999.99600));
      ASSERT_TRUE(IsEqual(mz, 187499.925));
      model.ComputePOIForces(lc, 3000, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 9999.99600));
      ASSERT_TRUE(IsEqual(mz, -499999.8));
      model.ComputePOIForces(lc, 3000, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -9999.99600));
      ASSERT_TRUE(IsEqual(mz, 499999.8));
      model.ComputePOIForces(lc, 3050, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -9999.99600));
      ASSERT_TRUE(IsEqual(mz, 624999.75000));
      model.ComputePOIForces(lc, 3075, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -9999.99600));
      ASSERT_TRUE(IsEqual(mz, 687499.72500));
   }

   // Problem taken from "Matrix Analysis of Structures", Robert F. Sennett,
   // 1994, Chapter 3, Example 3.5 - half portal frame with temperature strain loads.
   TEST_METHOD(HalfPortalFrame_SennettExample3_5)
   {
      Model model;
      model.CreateJoint(1, 0.0, 0.0);
      model.CreateJoint(2, 0.0, 12.0 * 12.0);
      model.CreateJoint(3, 7.0 * 12.0, 12.0 * 12.0);

      model.FindJoint(1)->Support();
      model.FindJoint(3)->Support();

      Float64 E = 30.0e06;
      Float64 A = 20.0;
      Float64 I = 100.0;
      Float64 EA = E * A;
      Float64 EI = E * I;
      model.CreateMember(1, 1, 2, EA, EI);
      model.CreateMember(2, 2, 3, EA, EI);

      // apply both axial and curvature strains to member 2: net temperature
      // rise of 35 deg, differential temperature of 70 deg (hotter on top),
      // section depth = 10
      Float64 saxial = 6.5e-06 * 35.0;
      Float64 scurv = -6.5e-06 * 70.0 / 10.0;
      Loading& pLoading = model.CreateLoading(0);
      pLoading.CreateMemberStrain(1, 2, 0.0, -1.0, saxial, scurv);


      Float64 dx, dy, rz;
      model.ComputeJointDeflections(0, 1, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputeJointDeflections(0, 2, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, -0.019160498123460));
      ASSERT_TRUE(IsEqual(dy, -0.00041133776877044));
      ASSERT_TRUE(IsEqual(rz, 0.00068164544539101));
      model.ComputeJointDeflections(0, 3, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      Float64 sfx, sfy, smz, efx, efy, emz;
      model.ComputeMemberForces(0, 1, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 1713.90736));
      ASSERT_TRUE(IsEqual(sfy, 360.70088));
      ASSERT_TRUE(IsEqual(smz, 11769.51671));
      ASSERT_TRUE(IsEqual(efx, -1713.90736));
      ASSERT_TRUE(IsEqual(efy, -360.70088));
      ASSERT_TRUE(IsEqual(emz, 40171.41027));
      model.ComputeMemberForces(0, 2, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, -360.70088));
      ASSERT_TRUE(IsEqual(sfy, 1713.90736));
      ASSERT_TRUE(IsEqual(smz, -40171.41027));
      ASSERT_TRUE(IsEqual(efx, 360.70088));
      ASSERT_TRUE(IsEqual(efy, -1713.90736));
      ASSERT_TRUE(IsEqual(emz, 184139.62934));

      Float64 fx, fy, mz;
      model.ComputeReactions(0, 1, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -360.700881));
      ASSERT_TRUE(IsEqual(fy, 1713.907369));
      ASSERT_TRUE(IsEqual(mz, 11769.516714));
      model.ComputeReactions(0, 2, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputeReactions(0, 3, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 360.7008818));
      ASSERT_TRUE(IsEqual(fy, -1713.9073698));
      ASSERT_TRUE(IsEqual(mz, 184139.6293422));
   }
};
} // namespace FEA2DUnitTests
