///////////////////////////////////////////////////////////////////////
// FEA2D - Two-dimensional Finite Element Analysis Engine
// Copyright � 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
///////////////////////////////////////////////////////////////////////
// TestSimpleBeamWithPointLoad2.cpp
//
// Mirrors Fem2d\Fem2dUnitTests\TestSimpleBeamWithPointLoad2.cpp
#include "pch.h"

namespace FEA2DUnitTests
{

TEST_CLASS(TestSimpleBeamWithPointLoad2)
{
public:
   TEST_METHOD(FixedFixedBeam_MidspanPointLoadAndMoment_EndReleaseVariants)
   {
      /*////////////////////////////////////////////////////
                               | P=4 at L/2
                 ]             V               [
                 ]=============================[  // fixed ends
                 ]                             [
             L = 8           Mc = PL/4 = 8
             EA = 3.0        Dc = PL^3/48EI =
             EI = 7.0
      *////////////////////////////////////////////////////
      Model model;
      model.CreateJoint(0, 0.0, 0.0);
      model.CreateJoint(8, 8.0, 0.0);

      model.FindJoint(0)->Support();
      model.FindJoint(8)->Support();

      Member& pMember1 = model.CreateMember(1, 0, 8, 3.0, 7.0);

      Loading& pLoading = model.CreateLoading(0);
      pLoading.CreatePointLoad(0, 1, 4.0, 0.0, -4.0, 0.0, LoadOrientation::Member);

      // second loading using a point moment
      Loading& pLoading2 = model.CreateLoading(2);
      pLoading2.CreatePointLoad(0, 1, 4.0, 0.0, 0.0, 3.0, LoadOrientation::Member);

      // POI's at 1/4 points in member 1 - pre-calculated
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

      model.ComputeJointDeflections(2, 0, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputeJointDeflections(2, 8, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      Float64 sfx, sfy, smz, efx, efy, emz;
      model.ComputeMemberForces(0, 1, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 2.0));
      ASSERT_TRUE(IsEqual(smz, 4.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 2.0));
      ASSERT_TRUE(IsEqual(emz, -4.0));

      model.ComputeMemberForces(2, 1, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 0.5625));
      ASSERT_TRUE(IsEqual(smz, 0.75));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, -0.5625));
      ASSERT_TRUE(IsEqual(emz, 0.75));

      Float64 fx, fy, mz;
      model.ComputeReactions(0, 0, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, 4.0));
      model.ComputeReactions(0, 8, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, -4.0));

      model.ComputeReactions(2, 0, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.5625));
      ASSERT_TRUE(IsEqual(mz, 0.75));
      model.ComputeReactions(2, 8, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -0.5625));
      ASSERT_TRUE(IsEqual(mz, 0.75));

      Float64 sdx, sdy, srz, edx, edy, erz;
      model.ComputeMemberDeflections(0, 1, &sdx, &sdy, &srz, &edx, &edy, &erz);
      ASSERT_TRUE(IsEqual(sdx, 0.0));
      ASSERT_TRUE(IsEqual(sdy, 0.0));
      ASSERT_TRUE(IsEqual(srz, 0.0));
      ASSERT_TRUE(IsEqual(edx, 0.0));
      ASSERT_TRUE(IsEqual(edy, 0.0));
      ASSERT_TRUE(IsEqual(erz, 0.0));

      model.ComputeMemberDeflections(2, 1, &sdx, &sdy, &srz, &edx, &edy, &erz);
      ASSERT_TRUE(IsEqual(sdx, 0.0));
      ASSERT_TRUE(IsEqual(sdy, 0.0));
      ASSERT_TRUE(IsEqual(srz, 0.0));
      ASSERT_TRUE(IsEqual(edx, 0.0));
      ASSERT_TRUE(IsEqual(edy, 0.0));
      ASSERT_TRUE(IsEqual(erz, 0.0));

      // POI's at 1/4 points of second half - calculated on the fly
      model.CreatePOI(20, 1, 4.0);
      model.CreatePOI(25, 1, 6.0);
      model.CreatePOI(22, 1, 8.0);

      model.ComputePOIDeflections(0, 10, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputePOIDeflections(0, 15, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -0.76190476190476));
      ASSERT_TRUE(IsEqual(rz, -0.57142857142857));
      model.ComputePOIDeflections(0, 12, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -1.5238095238095));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputePOIDeflections(0, 20, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -1.5238095238095));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputePOIDeflections(0, 25, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -0.76190476190476));
      ASSERT_TRUE(IsEqual(rz, 0.57142857142857));
      model.ComputePOIDeflections(0, 22, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      model.ComputePOIDeflections(2, 10, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputePOIDeflections(2, 15, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -0.10714285714286));
      ASSERT_TRUE(IsEqual(rz, -0.053571428571429));
      model.ComputePOIDeflections(2, 12, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.21428571428571));
      model.ComputePOIDeflections(2, 20, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.21428571428571));
      model.ComputePOIDeflections(2, 25, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.10714285714286));
      ASSERT_TRUE(IsEqual(rz, -0.053571428571429));
      model.ComputePOIDeflections(2, 22, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      model.ComputePOIForces(0, 10, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, -4.0));
      model.ComputePOIForces(0, 10, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, 4.0));

      model.ComputePOIForces(0, 15, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputePOIForces(0, 15, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      model.ComputePOIForces(0, 12, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, 4.0));
      model.ComputePOIForces(0, 12, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, -4.0));

      model.ComputePOIForces(0, 20, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, 4.0));
      model.ComputePOIForces(0, 20, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, -4.0));

      model.ComputePOIForces(0, 25, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputePOIForces(0, 25, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      model.ComputePOIForces(0, 22, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, -4.0));
      model.ComputePOIForces(0, 22, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, 4.0));

      model.ComputePOIForces(2, 10, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -0.5625));
      ASSERT_TRUE(IsEqual(mz, -0.75));
      model.ComputePOIForces(2, 10, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.5625));
      ASSERT_TRUE(IsEqual(mz, 0.75));

      model.ComputePOIForces(2, 15, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -0.5625));
      ASSERT_TRUE(IsEqual(mz, 0.375));
      model.ComputePOIForces(2, 15, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.5625));
      ASSERT_TRUE(IsEqual(mz, -0.375));

      model.ComputePOIForces(2, 12, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -0.5625));
      ASSERT_TRUE(IsEqual(mz, 1.5));
      model.ComputePOIForces(2, 12, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.5625));
      ASSERT_TRUE(IsEqual(mz, 1.5));

      model.ComputePOIForces(2, 20, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -0.5625));
      ASSERT_TRUE(IsEqual(mz, 1.5));
      model.ComputePOIForces(2, 20, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.5625));
      ASSERT_TRUE(IsEqual(mz, 1.5));

      model.ComputePOIForces(2, 25, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -0.5625));
      ASSERT_TRUE(IsEqual(mz, -0.375));
      model.ComputePOIForces(2, 25, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.5625));
      ASSERT_TRUE(IsEqual(mz, 0.375));

      model.ComputePOIForces(2, 22, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -0.5625));
      ASSERT_TRUE(IsEqual(mz, 0.75));
      model.ComputePOIForces(2, 22, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.5625));
      ASSERT_TRUE(IsEqual(mz, -0.75));

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

      model.ComputeJointDeflections(2, 0, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputeJointDeflections(2, 8, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      model.ComputeMemberForces(0, 1, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 1.25));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 2.75));
      ASSERT_TRUE(IsEqual(emz, -6.0));

      model.ComputeMemberForces(2, 1, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 0.42187500000000));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, -0.42187500000000));
      ASSERT_TRUE(IsEqual(emz, 0.37500000000000));

      model.ComputeReactions(0, 0, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 1.25));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputeReactions(0, 8, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.75));
      ASSERT_TRUE(IsEqual(mz, -6.0));

      model.ComputeReactions(2, 0, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.421875));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputeReactions(2, 8, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -0.421875));
      ASSERT_TRUE(IsEqual(mz, 0.375));

      model.ComputeMemberDeflections(0, 1, &sdx, &sdy, &srz, &edx, &edy, &erz);
      ASSERT_TRUE(IsEqual(sdx, 0.0));
      ASSERT_TRUE(IsEqual(sdy, 0.0));
      ASSERT_TRUE(IsEqual(srz, -1.1428571428571));
      ASSERT_TRUE(IsEqual(edx, 0.0));
      ASSERT_TRUE(IsEqual(edy, 0.0));
      ASSERT_TRUE(IsEqual(erz, 0.0));

      model.ComputeMemberDeflections(2, 1, &sdx, &sdy, &srz, &edx, &edy, &erz);
      ASSERT_TRUE(IsEqual(sdx, 0.0));
      ASSERT_TRUE(IsEqual(sdy, 0.0));
      ASSERT_TRUE(IsEqual(srz, -0.21428571428571));
      ASSERT_TRUE(IsEqual(edx, 0.0));
      ASSERT_TRUE(IsEqual(edy, 0.0));
      ASSERT_TRUE(IsEqual(erz, 0.0));

      model.ComputePOIDeflections(0, 10, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -1.1428571428571));
      model.ComputePOIDeflections(0, 15, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -2.047619047));
      ASSERT_TRUE(IsEqual(rz, -0.785714285));
      model.ComputePOIDeflections(0, 12, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -2.66667));
      ASSERT_TRUE(IsEqual(rz, 0.2857142857));
      model.ComputePOIDeflections(0, 20, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -2.66667));
      ASSERT_TRUE(IsEqual(rz, 0.2857142857));
      model.ComputePOIDeflections(0, 25, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -1.1904761904762));
      ASSERT_TRUE(IsEqual(rz, 0.92857142857143));
      model.ComputePOIDeflections(0, 22, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      model.ComputePOIDeflections(2, 10, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -0.21428571428571));
      model.ComputePOIDeflections(2, 15, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -0.34821428571429));
      ASSERT_TRUE(IsEqual(rz, -0.093750000000000));
      model.ComputePOIDeflections(2, 12, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -0.21428571428571));
      ASSERT_TRUE(IsEqual(rz, 0.26785714285714));
      model.ComputePOIDeflections(2, 20, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -0.21428571428571));
      ASSERT_TRUE(IsEqual(rz, 0.26785714285714));
      model.ComputePOIDeflections(2, 25, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.026785714285714));
      ASSERT_TRUE(IsEqual(rz, 0.013392857142857));
      model.ComputePOIDeflections(2, 22, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      model.ComputePOIForces(0, 10, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -1.25));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputePOIForces(0, 10, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 1.25));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      model.ComputePOIForces(0, 15, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -1.25));
      ASSERT_TRUE(IsEqual(mz, 2.5));
      model.ComputePOIForces(0, 15, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 1.25));
      ASSERT_TRUE(IsEqual(mz, -2.5));

      model.ComputePOIForces(0, 12, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -1.25));
      ASSERT_TRUE(IsEqual(mz, 5.0));
      model.ComputePOIForces(0, 12, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.75));
      ASSERT_TRUE(IsEqual(mz, -5.0));

      model.ComputePOIForces(0, 20, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -1.25));
      ASSERT_TRUE(IsEqual(mz, 5.0));
      model.ComputePOIForces(0, 20, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.75));
      ASSERT_TRUE(IsEqual(mz, -5.0));

      model.ComputePOIForces(0, 25, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.75));
      ASSERT_TRUE(IsEqual(mz, -0.5));
      model.ComputePOIForces(0, 25, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.75));
      ASSERT_TRUE(IsEqual(mz, 0.5));

      model.ComputePOIForces(0, 22, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.75));
      ASSERT_TRUE(IsEqual(mz, -6.0));
      model.ComputePOIForces(0, 22, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.75));
      ASSERT_TRUE(IsEqual(mz, 6.0));

      model.ComputePOIForces(2, 10, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -0.421875));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputePOIForces(2, 10, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.421875));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      model.ComputePOIForces(2, 15, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -0.421875));
      ASSERT_TRUE(IsEqual(mz, 0.84375000000000));
      model.ComputePOIForces(2, 15, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.421875));
      ASSERT_TRUE(IsEqual(mz, -0.84375000000000));

      model.ComputePOIForces(2, 12, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -0.421875));
      ASSERT_TRUE(IsEqual(mz, 1.6875000000000));
      model.ComputePOIForces(2, 12, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.421875));
      ASSERT_TRUE(IsEqual(mz, 1.3125000000000));

      model.ComputePOIForces(2, 20, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -0.421875));
      ASSERT_TRUE(IsEqual(mz, 1.6875000000000));
      model.ComputePOIForces(2, 20, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.421875));
      ASSERT_TRUE(IsEqual(mz, 1.3125000000000));

      model.ComputePOIForces(2, 25, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -0.421875));
      ASSERT_TRUE(IsEqual(mz, -0.46875000000000));
      model.ComputePOIForces(2, 25, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.421875));
      ASSERT_TRUE(IsEqual(mz, 0.46875000000000));

      model.ComputePOIForces(2, 22, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -0.421875));
      ASSERT_TRUE(IsEqual(mz, 0.375000000000000));
      model.ComputePOIForces(2, 22, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.421875));
      ASSERT_TRUE(IsEqual(mz, -0.37500000000000));

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

      model.ComputeJointDeflections(2, 0, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputeJointDeflections(2, 8, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      model.ComputeMemberForces(0, 1, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 2.75));
      ASSERT_TRUE(IsEqual(smz, 6.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 1.25));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      model.ComputeMemberForces(2, 1, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 0.421875));
      ASSERT_TRUE(IsEqual(smz, 0.375));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, -0.421875));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      model.ComputeReactions(0, 0, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.75));
      ASSERT_TRUE(IsEqual(mz, 6.0));
      model.ComputeReactions(0, 8, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 1.25));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      model.ComputeReactions(2, 0, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.421875));
      ASSERT_TRUE(IsEqual(mz, 0.375));
      model.ComputeReactions(2, 8, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -0.421875));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      model.ComputeMemberDeflections(0, 1, &sdx, &sdy, &srz, &edx, &edy, &erz);
      ASSERT_TRUE(IsEqual(sdx, 0.0));
      ASSERT_TRUE(IsEqual(sdy, 0.0));
      ASSERT_TRUE(IsEqual(srz, 0.0));
      ASSERT_TRUE(IsEqual(edx, 0.0));
      ASSERT_TRUE(IsEqual(edy, 0.0));
      ASSERT_TRUE(IsEqual(erz, 1.1428571428571));

      model.ComputeMemberDeflections(2, 1, &sdx, &sdy, &srz, &edx, &edy, &erz);
      ASSERT_TRUE(IsEqual(sdx, 0.0));
      ASSERT_TRUE(IsEqual(sdy, 0.0));
      ASSERT_TRUE(IsEqual(srz, 0.0));
      ASSERT_TRUE(IsEqual(edx, 0.0));
      ASSERT_TRUE(IsEqual(edy, 0.0));
      ASSERT_TRUE(IsEqual(erz, -0.21428571428571));

      model.ComputePOIDeflections(0, 10, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputePOIDeflections(0, 15, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -1.1904761904762));
      ASSERT_TRUE(IsEqual(rz, -0.92857142857143));
      model.ComputePOIDeflections(0, 12, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -2.66667));
      ASSERT_TRUE(IsEqual(rz, -0.2857142857));
      model.ComputePOIDeflections(0, 20, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -2.66667));
      ASSERT_TRUE(IsEqual(rz, -0.2857142857));
      model.ComputePOIDeflections(0, 25, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -2.047619047));
      ASSERT_TRUE(IsEqual(rz, 0.785714285));
      model.ComputePOIDeflections(0, 22, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 1.1428571428571));

      model.ComputePOIDeflections(2, 10, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputePOIDeflections(2, 15, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -0.026785714285714));
      ASSERT_TRUE(IsEqual(rz, 0.013392857142857));
      model.ComputePOIDeflections(2, 12, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.21428571428571));
      ASSERT_TRUE(IsEqual(rz, 0.26785714285714));
      model.ComputePOIDeflections(2, 20, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.21428571428571));
      ASSERT_TRUE(IsEqual(rz, 0.26785714285714));
      model.ComputePOIDeflections(2, 25, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.34821428571429));
      ASSERT_TRUE(IsEqual(rz, -0.093750000000000));
      model.ComputePOIDeflections(2, 22, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -0.21428571428571));

      model.ComputePOIForces(0, 10, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.75));
      ASSERT_TRUE(IsEqual(mz, -6.0));
      model.ComputePOIForces(0, 10, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.75));
      ASSERT_TRUE(IsEqual(mz, 6.0));
      model.ComputePOIForces(0, 15, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.75));
      ASSERT_TRUE(IsEqual(mz, -0.5));
      model.ComputePOIForces(0, 15, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.75));
      ASSERT_TRUE(IsEqual(mz, 0.5));
      model.ComputePOIForces(0, 12, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.75));
      ASSERT_TRUE(IsEqual(mz, 5.0));
      model.ComputePOIForces(0, 12, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -1.25));
      ASSERT_TRUE(IsEqual(mz, -5.0));
      model.ComputePOIForces(0, 20, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.75));
      ASSERT_TRUE(IsEqual(mz, 5.0));
      model.ComputePOIForces(0, 20, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -1.25));
      ASSERT_TRUE(IsEqual(mz, -5.0));
      model.ComputePOIForces(0, 25, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 1.25));
      ASSERT_TRUE(IsEqual(mz, 2.5));
      model.ComputePOIForces(0, 25, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -1.25));
      ASSERT_TRUE(IsEqual(mz, -2.5));
      model.ComputePOIForces(0, 22, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 1.25));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputePOIForces(0, 22, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -1.25));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      model.ComputePOIForces(2, 10, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -0.421875));
      ASSERT_TRUE(IsEqual(mz, -0.375));
      model.ComputePOIForces(2, 10, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.421875));
      ASSERT_TRUE(IsEqual(mz, 0.375));
      model.ComputePOIForces(2, 15, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -0.421875));
      ASSERT_TRUE(IsEqual(mz, 0.46875));
      model.ComputePOIForces(2, 15, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.421875));
      ASSERT_TRUE(IsEqual(mz, -0.46875));
      model.ComputePOIForces(2, 12, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -0.421875));
      ASSERT_TRUE(IsEqual(mz, 1.3125));
      model.ComputePOIForces(2, 12, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.421875));
      ASSERT_TRUE(IsEqual(mz, 1.6875));
      model.ComputePOIForces(2, 20, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -0.421875));
      ASSERT_TRUE(IsEqual(mz, 1.3125));
      model.ComputePOIForces(2, 20, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.421875));
      ASSERT_TRUE(IsEqual(mz, 1.6875));
      model.ComputePOIForces(2, 25, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -0.421875));
      ASSERT_TRUE(IsEqual(mz, -0.84375000000000));
      model.ComputePOIForces(2, 25, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.421875));
      ASSERT_TRUE(IsEqual(mz, 0.84375000000000));
      model.ComputePOIForces(2, 22, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -0.421875));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputePOIForces(2, 22, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.421875));
      ASSERT_TRUE(IsEqual(mz, 0.0));
   }
};
} // namespace FEA2DUnitTests
