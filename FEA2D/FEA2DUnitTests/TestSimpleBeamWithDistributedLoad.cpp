///////////////////////////////////////////////////////////////////////
// FEA2D - Two-dimensional Finite Element Analysis Engine
// Copyright � 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
///////////////////////////////////////////////////////////////////////
// TestSimpleBeamWithDistributedLoad.cpp
//
// Mirrors Fem2d\Fem2dUnitTests\TestSimpleBeamWithDistributedLoad.cpp
#include "pch.h"

namespace FEA2DUnitTests
{

TEST_CLASS(TestSimpleBeamWithDistributedLoad)
{
public:
   TEST_METHOD(FixedFixedBeam_TrapezoidalLoad_EndReleaseVariants)
   {
      /*////////////////////////////////////////////////////
                     |||||||||||
                  |||||||||||||||
           ]      vvvvvvvvvvvvv          [
           ]=============================[  // fixed ends
           ]                             [
             L = 8, EA = 3.0, EI = 7.0
             a = 2.5, b = 5.0, Wa = 2, Wb = -4
      *////////////////////////////////////////////////////
      Model model;
      model.CreateJoint(0, 0.0, 0.0);
      model.CreateJoint(8, 8.0, 0.0);

      model.FindJoint(0)->Support();
      model.FindJoint(8)->Support();

      Member& pMember1 = model.CreateMember(1, 0, 8, 3.0, 7.0);

      Loading& pLoading = model.CreateLoading(0);
      pLoading.CreateDistributedLoad(0, 1, LoadDirection::Fy, 2.5, 5.0, 2.0, 4.0, LoadOrientation::Member);

      model.CreatePOI(10, 1, 0.0);
      model.CreatePOI(15, 1, -.25);
      model.CreatePOI(12, 1, -0.5);


      Float64 dx, dy, rz;
      model.ComputeJointDeflections(0, 0, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputeJointDeflections(0, 8, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      Float64 sfx, sfy, smz, efx, efy, emz;
      model.ComputeMemberForces(0, 1, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, -3.898925));
      ASSERT_TRUE(IsEqual(smz, -7.438151));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, -3.601074));
      ASSERT_TRUE(IsEqual(emz, 7.080078));

      Float64 fx, fy, mz;
      model.ComputeReactions(0, 0, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -3.89892));
      ASSERT_TRUE(IsEqual(mz, -7.43815));
      model.ComputeReactions(0, 8, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -3.601074));
      ASSERT_TRUE(IsEqual(mz, 7.080078));

      Float64 sdx, sdy, srz, edx, edy, erz;
      model.ComputeMemberDeflections(0, 1, &sdx, &sdy, &srz, &edx, &edy, &erz);
      ASSERT_TRUE(IsEqual(sdx, 0.0));
      ASSERT_TRUE(IsEqual(sdy, 0.0));
      ASSERT_TRUE(IsEqual(srz, 0.0));
      ASSERT_TRUE(IsEqual(edx, 0.0));
      ASSERT_TRUE(IsEqual(edy, 0.0));
      ASSERT_TRUE(IsEqual(erz, 0.0));

      model.CreatePOI(20, 1, 4.0);
      model.CreatePOI(25, 1, 6.0);
      model.CreatePOI(22, 1, 8.0);

      model.ComputePOIDeflections(0, 10, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputePOIDeflections(0, 15, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 1.382533));
      ASSERT_TRUE(IsEqual(rz, 1.011207));
      model.ComputePOIDeflections(0, 12, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 2.627023809));
      ASSERT_TRUE(IsEqual(rz, -0.020721726));
      model.ComputePOIDeflections(0, 20, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 2.627023809));
      ASSERT_TRUE(IsEqual(rz, -0.020721726));
      model.ComputePOIDeflections(0, 25, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 1.3369605));
      ASSERT_TRUE(IsEqual(rz, -0.9940011));
      model.ComputePOIDeflections(0, 22, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      model.ComputePOIForces(0, 10, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 3.8989257));
      ASSERT_TRUE(IsEqual(mz, 7.4381510));
      model.ComputePOIForces(0, 10, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -3.8989257));
      ASSERT_TRUE(IsEqual(mz, -7.4381510));

      model.ComputePOIForces(0, 15, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 3.8989257));
      ASSERT_TRUE(IsEqual(mz, -0.3597005));
      model.ComputePOIForces(0, 15, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -3.8989257));
      ASSERT_TRUE(IsEqual(mz, 0.3597005));

      model.ComputePOIForces(0, 12, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -0.00107422));
      ASSERT_TRUE(IsEqual(mz, -5.457552));
      model.ComputePOIForces(0, 12, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.00107422));
      ASSERT_TRUE(IsEqual(mz, 5.457552));

      model.ComputePOIForces(0, 20, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -0.00107422));
      ASSERT_TRUE(IsEqual(mz, -5.457552));
      model.ComputePOIForces(0, 20, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.00107422));
      ASSERT_TRUE(IsEqual(mz, 5.457552));

      model.ComputePOIForces(0, 25, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -3.601074));
      ASSERT_TRUE(IsEqual(mz, -0.122070));
      model.ComputePOIForces(0, 25, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 3.601074));
      ASSERT_TRUE(IsEqual(mz, 0.122070));

      model.ComputePOIForces(0, 22, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -3.601074));
      ASSERT_TRUE(IsEqual(mz, 7.080078));
      model.ComputePOIForces(0, 22, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 3.601074));
      ASSERT_TRUE(IsEqual(mz, -7.080078));

      ///////////////////////////////////////////////
      // try a pin-fix orientation
      pMember1.ReleaseEnd(MemberEndType::Start, MemberReleaseType::Mz);


      model.ComputeJointDeflections(0, 0, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputeJointDeflections(0, 8, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      model.ComputeMemberForces(0, 1, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, -2.5042724));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, -4.9957275));
      ASSERT_TRUE(IsEqual(emz, 10.7991536));

      model.ComputeReactions(0, 0, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.50427246));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputeReactions(0, 8, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -4.9957275));
      ASSERT_TRUE(IsEqual(mz, 10.7991536));

      model.ComputeMemberDeflections(0, 1, &sdx, &sdy, &srz, &edx, &edy, &erz);
      ASSERT_TRUE(IsEqual(sdx, 0.0));
      ASSERT_TRUE(IsEqual(sdy, 0.0));
      ASSERT_TRUE(IsEqual(srz, 2.125186));
      ASSERT_TRUE(IsEqual(edx, 0.0));
      ASSERT_TRUE(IsEqual(edy, 0.0));
      ASSERT_TRUE(IsEqual(erz, 0.0));

      model.ComputePOIDeflections(0, 10, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 2.12518601));
      model.ComputePOIDeflections(0, 15, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 3.77336774));
      ASSERT_TRUE(IsEqual(rz, 1.40967959));
      model.ComputePOIDeflections(0, 12, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 4.75220982));
      ASSERT_TRUE(IsEqual(rz, -0.55201822));
      model.ComputePOIDeflections(0, 20, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 4.75220982));
      ASSERT_TRUE(IsEqual(rz, -0.55201822));
      model.ComputePOIDeflections(0, 25, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 2.133905));
      ASSERT_TRUE(IsEqual(rz, -1.658121));
      model.ComputePOIDeflections(0, 22, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      model.ComputePOIForces(0, 10, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.5042724609375));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputePOIForces(0, 10, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.5042724609375));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      model.ComputePOIForces(0, 15, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.5042724609375));
      ASSERT_TRUE(IsEqual(mz, -5.0085449218750));
      model.ComputePOIForces(0, 15, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.5042724609375));
      ASSERT_TRUE(IsEqual(mz, 5.0085449218750));

      model.ComputePOIForces(0, 12, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -1.3957275390625));
      ASSERT_TRUE(IsEqual(mz, -7.3170898437500));
      model.ComputePOIForces(0, 12, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 1.3957275390625));
      ASSERT_TRUE(IsEqual(mz, 7.3170898437500));

      model.ComputePOIForces(0, 20, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -1.3957275390625));
      ASSERT_TRUE(IsEqual(mz, -7.3170898437500));
      model.ComputePOIForces(0, 20, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 1.3957275390625));
      ASSERT_TRUE(IsEqual(mz, 7.3170898437500));

      model.ComputePOIForces(0, 25, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -4.9957275390625));
      ASSERT_TRUE(IsEqual(mz, 0.80769856770834));
      model.ComputePOIForces(0, 25, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 4.9957275390625));
      ASSERT_TRUE(IsEqual(mz, -0.80769856770834));

      model.ComputePOIForces(0, 22, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -4.9957275));
      ASSERT_TRUE(IsEqual(mz, 10.7991536));
      model.ComputePOIForces(0, 22, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 4.9957275));
      ASSERT_TRUE(IsEqual(mz, -10.7991536));

      ///////////////////////////////////////////////
      // try a pin-pin orientation
      pMember1.ReleaseEnd(MemberEndType::End, MemberReleaseType::Mz);


      model.ComputeJointDeflections(0, 0, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputeJointDeflections(0, 8, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      model.ComputeMemberForces(0, 1, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, -3.85416667));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, -3.6458333));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      model.ComputeReactions(0, 0, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -3.85416667));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputeReactions(0, 8, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -3.64583333));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      model.ComputeMemberDeflections(0, 1, &sdx, &sdy, &srz, &edx, &edy, &erz);
      ASSERT_TRUE(IsEqual(sdx, 0.0));
      ASSERT_TRUE(IsEqual(sdy, 0.0));
      ASSERT_TRUE(IsEqual(srz, 4.18216765));
      ASSERT_TRUE(IsEqual(edx, 0.0));
      ASSERT_TRUE(IsEqual(edy, 0.0));
      ASSERT_TRUE(IsEqual(erz, -4.11396329));

      model.ComputePOIDeflections(0, 10, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 4.182167658));
      model.ComputePOIDeflections(0, 15, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 7.63020833));
      ASSERT_TRUE(IsEqual(rz, 3.08097718));
      model.ComputePOIDeflections(0, 12, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 10.9231547));
      ASSERT_TRUE(IsEqual(rz, -0.0377728));
      model.ComputePOIDeflections(0, 20, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 10.92315));
      ASSERT_TRUE(IsEqual(rz, -0.037772817));
      model.ComputePOIDeflections(0, 25, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 7.5334821428571));
      ASSERT_TRUE(IsEqual(rz, -3.0722966269841));
      model.ComputePOIDeflections(0, 22, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -4.11396329));

      model.ComputePOIForces(0, 10, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 3.8541666666667));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputePOIForces(0, 10, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -3.8541666666667));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      model.ComputePOIForces(0, 15, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 3.8541666666667));
      ASSERT_TRUE(IsEqual(mz, -7.7083333333333));
      model.ComputePOIForces(0, 15, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -3.8541666666667));
      ASSERT_TRUE(IsEqual(mz, 7.7083333333333));

      model.ComputePOIForces(0, 12, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -0.045833333333333));
      ASSERT_TRUE(IsEqual(mz, -12.716666666667));
      model.ComputePOIForces(0, 12, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.045833333333333));
      ASSERT_TRUE(IsEqual(mz, 12.716666666667));

      model.ComputePOIForces(0, 20, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -0.045833333333333));
      ASSERT_TRUE(IsEqual(mz, -12.716666666667));
      model.ComputePOIForces(0, 20, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.045833333333333));
      ASSERT_TRUE(IsEqual(mz, 12.716666666667));

      model.ComputePOIForces(0, 25, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -3.6458333333333));
      ASSERT_TRUE(IsEqual(mz, -7.2916666666667));
      model.ComputePOIForces(0, 25, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 3.645833333333));
      ASSERT_TRUE(IsEqual(mz, 7.2916666666667));

      model.ComputePOIForces(0, 22, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -3.6458333333333));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputePOIForces(0, 22, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 3.6458333333333));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      ///////////////////////////////////////////////
      // try a fix-pin orientation
      pMember1.ReleaseEnd(MemberEndType::Start, MemberReleaseType::None);
      pMember1.ReleaseEnd(MemberEndType::End, MemberReleaseType::Mz);


      model.ComputeJointDeflections(0, 0, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputeJointDeflections(0, 8, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      model.ComputeMemberForces(0, 1, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, -5.2264404));
      ASSERT_TRUE(IsEqual(smz, -10.978190));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, -2.273559));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      model.ComputeReactions(0, 0, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -5.2264404));
      ASSERT_TRUE(IsEqual(mz, -10.978190));
      model.ComputeReactions(0, 8, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.273559));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      model.ComputeMemberDeflections(0, 1, &sdx, &sdy, &srz, &edx, &edy, &erz);
      ASSERT_TRUE(IsEqual(sdx, 0.0));
      ASSERT_TRUE(IsEqual(sdy, 0.0));
      ASSERT_TRUE(IsEqual(srz, 0.0));
      ASSERT_TRUE(IsEqual(edx, 0.0));
      ASSERT_TRUE(IsEqual(edy, 0.0));
      ASSERT_TRUE(IsEqual(erz, -2.0228794642857));

      model.ComputePOIDeflections(0, 10, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputePOIDeflections(0, 15, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 2.14111));
      ASSERT_TRUE(IsEqual(rz, 1.64335));
      model.ComputePOIDeflections(0, 12, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 4.6499032));
      ASSERT_TRUE(IsEqual(rz, 0.4849981));
      model.ComputePOIDeflections(0, 20, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 4.6499032));
      ASSERT_TRUE(IsEqual(rz, 0.4849981));
      model.ComputePOIDeflections(0, 25, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 3.61269996));
      ASSERT_TRUE(IsEqual(rz, -1.37329101));
      model.ComputePOIDeflections(0, 22, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -2.02287946));

      model.ComputePOIForces(0, 10, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 5.2264404296875));
      ASSERT_TRUE(IsEqual(mz, 10.978190104167));
      model.ComputePOIForces(0, 10, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -5.2264404296875));
      ASSERT_TRUE(IsEqual(mz, -10.978190104167));
      model.ComputePOIForces(0, 15, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 5.2264404296875));
      ASSERT_TRUE(IsEqual(mz, 0.52530924479167));
      model.ComputePOIForces(0, 15, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -5.2264404296875));
      ASSERT_TRUE(IsEqual(mz, -0.52530924479167));
      model.ComputePOIForces(0, 12, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 1.326440429));
      ASSERT_TRUE(IsEqual(mz, -7.227571614));
      model.ComputePOIForces(0, 12, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -1.326440429));
      ASSERT_TRUE(IsEqual(mz, 7.227571614));
      model.ComputePOIForces(0, 20, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 1.326440429));
      ASSERT_TRUE(IsEqual(mz, -7.227571614));
      model.ComputePOIForces(0, 20, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -1.326440429));
      ASSERT_TRUE(IsEqual(mz, 7.227571614));
      model.ComputePOIForces(0, 25, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.27355957));
      ASSERT_TRUE(IsEqual(mz, -4.54711914));
      model.ComputePOIForces(0, 25, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.27355957));
      ASSERT_TRUE(IsEqual(mz, 4.54711914));
      model.ComputePOIForces(0, 22, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.27355957));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputePOIForces(0, 22, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.27355957));
      ASSERT_TRUE(IsEqual(mz, 0.0));
   }

   // Three-span beam with trapezoidal distributed loads plus a point load on
   // the third span; made up and verified using DrBeam.
   //        1                       2                 3
   //  ========================================================
   //  ^     16              ^       14           ^     10    ^
   //  1                     2                     3           4
   TEST_METHOD(ThreeSpanBeam_TrapezoidalLoadsAndPointLoad_DrBeamVerified)
   {
      Model model;
      Joint& pJoint1 = model.CreateJoint(1, 0.0, 0.0);
      Joint& pJoint2 = model.CreateJoint(2, 16.0, 0.0);
      Joint& pJoint3 = model.CreateJoint(3, 30.0, 0.0);
      Joint& pJoint4 = model.CreateJoint(4, 40.0, 0.0);

      pJoint1.Support();
      pJoint2.Support();
      pJoint3.Support();
      pJoint4.Support();
      pJoint1.ReleaseDof(JointReleaseType::Mz);
      pJoint2.ReleaseDof(JointReleaseType::Mz);
      pJoint3.ReleaseDof(JointReleaseType::Mz);
      pJoint4.ReleaseDof(JointReleaseType::Mz);

      model.CreateMember(1, 1, 2, 3.0, 7.0);
      model.CreateMember(2, 2, 3, 3.0, 7.0);
      model.CreateMember(3, 3, 4, 3.0, 7.0);

      Loading& pLoading = model.CreateLoading(0);
      pLoading.CreateDistributedLoad(1, 1, LoadDirection::Fy, 4.0, -1.0, -18.0, -6.0, LoadOrientation::Member);
      pLoading.CreateDistributedLoad(2, 2, LoadDirection::Fy, 0.0, 6.0, -6.0, 0.0, LoadOrientation::Member);

      // put a point load at 4 into member 3
      pLoading.CreatePointLoad(0, 3, 4.0, 0.0, -21.0, 0.0, LoadOrientation::Member);

      // POI's at 1/4 points in members 1 and 2
      model.CreatePOI(10, 1, 0.0);
      model.CreatePOI(11, 1, -0.25);
      model.CreatePOI(12, 1, -0.5);
      model.CreatePOI(13, 1, -0.75);
      model.CreatePOI(14, 1, -1.0);

      model.CreatePOI(20, 2, 0.0);
      model.CreatePOI(21, 2, -0.25);
      model.CreatePOI(22, 2, -0.5);
      model.CreatePOI(23, 2, -0.75);
      model.CreatePOI(24, 2, -1.0);

      // mid point of member 3
      model.CreatePOI(32, 3, -0.5);


      Float64 dx, dy, rz;
      model.ComputeJointDeflections(0, 1, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -183.75544));
      model.ComputeJointDeflections(0, 2, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 111.39659965));
      model.ComputeJointDeflections(0, 3, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -35.60633839));
      model.ComputeJointDeflections(0, 4, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 25.003169));

      Float64 sfx, sfy, smz, efx, efy, emz;
      model.ComputeMemberForces(0, 1, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 49.8911273));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 94.1088726));
      ASSERT_TRUE(IsEqual(emz, -209.741962955));
      model.ComputeMemberForces(0, 2, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 32.871090969));
      ASSERT_TRUE(IsEqual(smz, 209.74196295508));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, -14.87109097));
      ASSERT_TRUE(IsEqual(emz, 34.45331062));
      model.ComputeMemberForces(0, 3, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 9.154668937));
      ASSERT_TRUE(IsEqual(smz, -34.45331062));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 11.845331062));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      Float64 fx, fy, mz;
      model.ComputeReactions(0, 1, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 49.8911273));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputeReactions(0, 2, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 126.9799636));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputeReactions(0, 3, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -5.716422032));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputeReactions(0, 4, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 11.845331062380));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      Float64 sdx, sdy, srz, edx, edy, erz;
      model.ComputeMemberDeflections(0, 1, &sdx, &sdy, &srz, &edx, &edy, &erz);
      ASSERT_TRUE(IsEqual(sdx, 0.0));
      ASSERT_TRUE(IsEqual(sdy, 0.0));
      ASSERT_TRUE(IsEqual(srz, -183.755443));
      ASSERT_TRUE(IsEqual(edx, 0.0));
      ASSERT_TRUE(IsEqual(edy, 0.0));
      ASSERT_TRUE(IsEqual(erz, 111.39659965327));

      model.ComputeMemberDeflections(0, 2, &sdx, &sdy, &srz, &edx, &edy, &erz);
      ASSERT_TRUE(IsEqual(sdx, 0.0));
      ASSERT_TRUE(IsEqual(sdy, 0.0));
      ASSERT_TRUE(IsEqual(srz, 111.39659965327));
      ASSERT_TRUE(IsEqual(edx, 0.0));
      ASSERT_TRUE(IsEqual(edy, 0.0));
      ASSERT_TRUE(IsEqual(erz, -35.606338392287));

      model.ComputeMemberDeflections(0, 3, &sdx, &sdy, &srz, &edx, &edy, &erz);
      ASSERT_TRUE(IsEqual(sdx, 0.0));
      ASSERT_TRUE(IsEqual(sdy, 0.0));
      ASSERT_TRUE(IsEqual(srz, -35.606338392));
      ASSERT_TRUE(IsEqual(edx, 0.0));
      ASSERT_TRUE(IsEqual(edy, 0.0));
      ASSERT_TRUE(IsEqual(erz, 25.0031692));

      model.ComputePOIDeflections(0, 10, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -183.75544268378));
      model.ComputePOIDeflections(0, 11, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -658.99719577846));
      ASSERT_TRUE(IsEqual(rz, -126.73701146629));
      model.ComputePOIDeflections(0, 12, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -888.05646562649));
      ASSERT_TRUE(IsEqual(rz, 18.413520281436));
      model.ComputePOIDeflections(0, 13, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -552.24940742318));
      ASSERT_TRUE(IsEqual(rz, 134.36281922605));
      model.ComputePOIDeflections(0, 14, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 111.39659965327));
      model.ComputePOIDeflections(0, 20, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 111.39659965327));
      model.ComputePOIDeflections(0, 21, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 235.18567198256));
      ASSERT_TRUE(IsEqual(rz, 30.056051941082));
      model.ComputePOIDeflections(0, 22, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 248.38371300830));
      ASSERT_TRUE(IsEqual(rz, -18.010830621369));
      model.ComputePOIDeflections(0, 23, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 139.58792580370));
      ASSERT_TRUE(IsEqual(rz, -39.820789105508));
      model.ComputePOIDeflections(0, 24, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -35.606338392287));
      model.ComputePOIDeflections(0, 32, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -89.761884485538));
      ASSERT_TRUE(IsEqual(rz, 3.8507922990358));

      model.ComputePOIForces(0, 10, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -49.891127315308));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputePOIForces(0, 11, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -49.891127315308));
      ASSERT_TRUE(IsEqual(mz, 199.56450926123));
      model.ComputePOIForces(0, 12, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 14.108872684692));
      ASSERT_TRUE(IsEqual(mz, 265.79568518913));
      model.ComputePOIForces(0, 13, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 62.108872684692));
      ASSERT_TRUE(IsEqual(mz, 108.02686111703));
      model.ComputePOIForces(0, 14, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 94.108872684692));
      ASSERT_TRUE(IsEqual(mz, -209.74196295508));
      model.ComputePOIForces(0, 14, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -94.108872684692));
      ASSERT_TRUE(IsEqual(mz, 209.74196295508));
      model.ComputePOIForces(0, 20, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -32.871090969920));
      ASSERT_TRUE(IsEqual(mz, -209.74196295508));
      model.ComputePOIForces(0, 21, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -17.996090969920));
      ASSERT_TRUE(IsEqual(mz, -124.29731122702));
      model.ComputePOIForces(0, 22, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -14.871090));
      ASSERT_TRUE(IsEqual(mz, -69.644326));
      model.ComputePOIForces(0, 32, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 11.845331));
      ASSERT_TRUE(IsEqual(mz, 59.226655));
   }

   // Like the fixed-fixed test above, but shorter and exercising a
   // zero-length distributed load (via a live property change) that then
   // gets grown into a genuine trapezoidal load with swapped start/end
   // values.
   TEST_METHOD(FixedFixedBeam_ZeroLengthLoadThenTrapezoidal)
   {
      Model model;
      model.CreateJoint(0, 0.0, 0.0);
      model.CreateJoint(8, 8.0, 0.0);

      model.FindJoint(0)->Support();
      model.FindJoint(8)->Support();

      model.CreateMember(1, 0, 8, 3.0, 7.0);

      Loading& pLoading = model.CreateLoading(0);

      // load with zero length
      DistributedLoad& pDistributedLoad = pLoading.CreateDistributedLoad(0, 1, LoadDirection::Fy, 2.5, 2.5, 0.0, 0.0, LoadOrientation::Member);

      model.CreatePOI(10, 1, 0.0);
      model.CreatePOI(15, 1, -.25);
      model.CreatePOI(12, 1, -0.5);


      Float64 fx, fy, mz;
      // should be zero since there are no forces
      model.ComputeReactions(0, 0, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      // now put values into the load and carry on with the test except swap
      // end and start values
      pDistributedLoad.SetStartLocation(5.0);
      pDistributedLoad.SetWStart(4.0);
      pDistributedLoad.SetWEnd(2.0);


      Float64 dx, dy, rz;
      model.ComputeJointDeflections(0, 0, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputeJointDeflections(0, 8, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      Float64 sfx, sfy, smz, efx, efy, emz;
      model.ComputeMemberForces(0, 1, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, -3.898925));
      ASSERT_TRUE(IsEqual(smz, -7.438151));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, -3.601074));
      ASSERT_TRUE(IsEqual(emz, 7.080078));

      model.ComputeReactions(0, 0, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -3.89892));
      ASSERT_TRUE(IsEqual(mz, -7.43815));
      model.ComputeReactions(0, 8, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -3.601074));
      ASSERT_TRUE(IsEqual(mz, 7.080078));

      Float64 sdx, sdy, srz, edx, edy, erz;
      model.ComputeMemberDeflections(0, 1, &sdx, &sdy, &srz, &edx, &edy, &erz);
      ASSERT_TRUE(IsEqual(sdx, 0.0));
      ASSERT_TRUE(IsEqual(sdy, 0.0));
      ASSERT_TRUE(IsEqual(srz, 0.0));
      ASSERT_TRUE(IsEqual(edx, 0.0));
      ASSERT_TRUE(IsEqual(edy, 0.0));
      ASSERT_TRUE(IsEqual(erz, 0.0));

      model.CreatePOI(20, 1, 4.0);
      model.CreatePOI(25, 1, 6.0);
      model.CreatePOI(22, 1, 8.0);

      model.ComputePOIDeflections(0, 10, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputePOIDeflections(0, 15, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 1.382533));
      ASSERT_TRUE(IsEqual(rz, 1.011207));
      model.ComputePOIDeflections(0, 12, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 2.627023809));
      ASSERT_TRUE(IsEqual(rz, -0.020721726));
      model.ComputePOIDeflections(0, 20, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 2.627023809));
      ASSERT_TRUE(IsEqual(rz, -0.020721726));
      model.ComputePOIDeflections(0, 25, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 1.3369605));
      ASSERT_TRUE(IsEqual(rz, -0.9940011));
      model.ComputePOIDeflections(0, 22, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      model.ComputePOIForces(0, 10, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 3.8989257));
      ASSERT_TRUE(IsEqual(mz, 7.4381510));
      model.ComputePOIForces(0, 10, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -3.8989257));
      ASSERT_TRUE(IsEqual(mz, -7.4381510));

      model.ComputePOIForces(0, 15, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 3.8989257));
      ASSERT_TRUE(IsEqual(mz, -0.3597005));
      model.ComputePOIForces(0, 15, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -3.8989257));
      ASSERT_TRUE(IsEqual(mz, 0.3597005));

      model.ComputePOIForces(0, 12, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -0.00107422));
      ASSERT_TRUE(IsEqual(mz, -5.457552));
      model.ComputePOIForces(0, 12, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.00107422));
      ASSERT_TRUE(IsEqual(mz, 5.457552));

      model.ComputePOIForces(0, 20, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -0.00107422));
      ASSERT_TRUE(IsEqual(mz, -5.457552));
      model.ComputePOIForces(0, 20, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.00107422));
      ASSERT_TRUE(IsEqual(mz, 5.457552));

      model.ComputePOIForces(0, 25, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -3.601074));
      ASSERT_TRUE(IsEqual(mz, -0.122070));
      model.ComputePOIForces(0, 25, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 3.601074));
      ASSERT_TRUE(IsEqual(mz, 0.122070));

      model.ComputePOIForces(0, 22, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -3.601074));
      ASSERT_TRUE(IsEqual(mz, 7.080078));
      model.ComputePOIForces(0, 22, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 3.601074));
      ASSERT_TRUE(IsEqual(mz, -7.080078));
   }
};
} // namespace FEA2DUnitTests
