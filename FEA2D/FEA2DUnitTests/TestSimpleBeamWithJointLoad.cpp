///////////////////////////////////////////////////////////////////////
// FEA2D - Two-dimensional Finite Element Analysis Engine
// Copyright � 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
///////////////////////////////////////////////////////////////////////
// TestSimpleBeamWithJointLoad.cpp
//
// Mirrors Fem2d\Fem2dUnitTests\TestSimpleBeamWithJointLoad.cpp and
// TestSimpleBeamWithJointLoad2.cpp (the legacy harness split this into two
// files/functions purely due to old compiler function-size limits; merged
// back into a single TEST_METHOD here since that limit no longer applies).
// The legacy file's three result interfaces (IFem2dModelResults/Ex) are
// unified into one Model::ComputeMemberForces(lc, mbrId, orientation, ...)
// signature here - calls that used the plain (member-orientation) overload
// pass LoadOrientation::Member explicitly, and ComputeMemberForcesEx calls
// just pass whatever orientation was requested.
#include "pch.h"

namespace FEA2DUnitTests
{

TEST_CLASS(TestSimpleBeamWithJointLoad)
{
public:
   TEST_METHOD(SimpleBeamWithMidspanJointLoad_Rotations)
   {
      /*////////////////////////////////////////////////////
                               | P=4 at L/2
                               V
                 0=============0===============0
                 A                             O
             L = 8           Mc = PL/4 = 8
             EA = 3.0        Dc = PL^3/48EI =
             EI = 7.0
      *////////////////////////////////////////////////////
      Model model;
      model.CreateJoint(0, 0.0, 0.0);
      Joint& pJoint4 = model.CreateJoint(4, 4.0, 0.0);
      Joint& pJoint8 = model.CreateJoint(8, 8.0, 0.0);

      Joint* pJoint0 = model.FindJoint(0);

      pJoint0->Support();
      pJoint0->ReleaseDof(JointReleaseType::Mz);
      pJoint8.Support();
      pJoint8.ReleaseDof(JointReleaseType::Fx);
      pJoint8.ReleaseDof(JointReleaseType::Mz);

      Member& pMember1 = model.CreateMember(1, 0, 4, 3.0, 7.0);
      Member& pMember2 = model.CreateMember(2, 4, 8, 3.0, 7.0);

      Loading& pLoading = model.CreateLoading(0);
      JointLoad& pJointLoad = pLoading.CreateJointLoad(0, 4, 0.0, -4.0, 0.0);

      // POI's at 1/4 points in member 1 - these results are pre-calculated
      model.CreatePOI(10, 1, 0.0);
      model.CreatePOI(15, 1, -.5);
      model.CreatePOI(12, 1, -1.0);
      model.CreatePOI(13, 5, -1.0); // member doesn't exist

      ASSERT_TRUE(model.RemovePOI(13));


      Float64 dx, dy, rz;
      model.ComputeJointDeflections(0, 0, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -2.2857142857143));
      model.ComputeJointDeflections(0, 4, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -6.0952380952381));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputeJointDeflections(0, 8, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 2.2857142857143));

      // test error handling
      ASSERT_THROWS(model.ComputeJointDeflections(1, 8, &dx, &dy, &rz), ReasonCode::LoadingNotFound);
      ASSERT_THROWS(model.ComputeJointDeflections(0, 11, &dx, &dy, &rz), ReasonCode::JointNotFound);

      Float64 sfx, sfy, smz, efx, efy, emz;
      model.ComputeMemberForces(0, 1, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 2.0));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, -2.0));
      ASSERT_TRUE(IsEqual(emz, 8.0));
      model.ComputeMemberForces(0, 2, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, -2.0));
      ASSERT_TRUE(IsEqual(smz, -8.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 2.0));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      model.ComputeMemberForces(0, 1, LoadOrientation::Global, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 2.0));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, -2.0));
      ASSERT_TRUE(IsEqual(emz, 8.0));
      model.ComputeMemberForces(0, 2, LoadOrientation::Global, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, -2.0));
      ASSERT_TRUE(IsEqual(smz, -8.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 2.0));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      // load case doesn't exist
      ASSERT_THROWS(model.ComputeMemberForces(1, 2, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz), ReasonCode::LoadingNotFound);
      ASSERT_THROWS(model.ComputeMemberForces(0, 4, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz), ReasonCode::MemberNotFound);
      ASSERT_THROWS(model.ComputeMemberForces(1, 2, LoadOrientation::Global, &sfx, &sfy, &smz, &efx, &efy, &emz), ReasonCode::LoadingNotFound);
      ASSERT_THROWS(model.ComputeMemberForces(0, 4, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz), ReasonCode::MemberNotFound);

      Float64 fx, fy, mz;
      model.ComputeReactions(0, 0, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputeReactions(0, 4, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputeReactions(0, 8, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      ASSERT_THROWS(model.ComputeReactions(1, 8, &fx, &fy, &mz), ReasonCode::LoadingNotFound);
      ASSERT_THROWS(model.ComputeReactions(0, 12, &fx, &fy, &mz), ReasonCode::JointNotFound);

      Float64 sdx, sdy, srz, edx, edy, erz;
      model.ComputeMemberDeflections(0, 1, &sdx, &sdy, &srz, &edx, &edy, &erz);
      ASSERT_TRUE(IsEqual(sdx, 0.0));
      ASSERT_TRUE(IsEqual(sdy, 0.0));
      ASSERT_TRUE(IsEqual(srz, -2.2857142857143));
      ASSERT_TRUE(IsEqual(edx, 0.0));
      ASSERT_TRUE(IsEqual(edy, -6.0952380952381));
      ASSERT_TRUE(IsEqual(erz, 0.0));
      model.ComputeMemberDeflections(0, 2, &sdx, &sdy, &srz, &edx, &edy, &erz);
      ASSERT_TRUE(IsEqual(sdx, 0.0));
      ASSERT_TRUE(IsEqual(sdy, -6.0952380952381));
      ASSERT_TRUE(IsEqual(srz, 0.0));
      ASSERT_TRUE(IsEqual(edx, 0.0));
      ASSERT_TRUE(IsEqual(edy, 0.0));
      ASSERT_TRUE(IsEqual(erz, 2.2857142857143));

      ASSERT_THROWS(model.ComputeMemberDeflections(1, 2, &sdx, &sdy, &srz, &edx, &edy, &erz), ReasonCode::LoadingNotFound);
      ASSERT_THROWS(model.ComputeMemberDeflections(0, 21, &sdx, &sdy, &srz, &edx, &edy, &erz), ReasonCode::MemberNotFound);

      // POI's at 1/4 points of member 2 - these results are calculated on the fly
      model.CreatePOI(20, 2, 0.0);
      model.CreatePOI(25, 2, 2.0);
      model.CreatePOI(22, 2, 4.0);

      // poi that doesn't exist
      ASSERT_THROWS(model.ComputePOIDeflections(0, 13, LoadOrientation::Member, &dx, &dy, &rz), ReasonCode::PoiNotFound);

      model.ComputePOIDeflections(0, 10, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -2.2857142857143));
      model.ComputePOIDeflections(0, 15, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -4.1904761904762));
      ASSERT_TRUE(IsEqual(rz, -12.0 / 7.0));
      model.ComputePOIDeflections(0, 12, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -6.0952380952381));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputePOIDeflections(0, 20, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -6.0952380952381));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputePOIDeflections(0, 25, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -4.1904761904762));
      ASSERT_TRUE(IsEqual(rz, 12.0 / 7.0));
      model.ComputePOIDeflections(0, 22, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 2.2857142857143));

      model.ComputePOIDeflections(0, 10, LoadOrientation::Global, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -2.2857142857143));
      model.ComputePOIDeflections(0, 15, LoadOrientation::Global, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -4.1904761904762));
      ASSERT_TRUE(IsEqual(rz, -12.0 / 7.0));
      model.ComputePOIDeflections(0, 12, LoadOrientation::Global, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -6.0952380952381));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputePOIDeflections(0, 20, LoadOrientation::Global, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -6.0952380952381));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputePOIDeflections(0, 25, LoadOrientation::Global, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -4.1904761904762));
      ASSERT_TRUE(IsEqual(rz, 12.0 / 7.0));
      model.ComputePOIDeflections(0, 22, LoadOrientation::Global, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 2.2857142857143));

      ASSERT_THROWS(model.ComputePOIDeflections(10, 22, LoadOrientation::Member, &dx, &dy, &rz), ReasonCode::LoadingNotFound);
      ASSERT_THROWS(model.ComputePOIDeflections(0, 32, LoadOrientation::Member, &dx, &dy, &rz), ReasonCode::PoiNotFound);

      model.ComputePOIForces(0, 10, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputePOIForces(0, 10, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputePOIForces(0, 10, MemberFaceType::Left, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputePOIForces(0, 10, MemberFaceType::Right, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      model.ComputePOIForces(0, 15, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, 4.0));
      model.ComputePOIForces(0, 15, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, -4.0));
      model.ComputePOIForces(0, 15, MemberFaceType::Left, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, 4.0));
      model.ComputePOIForces(0, 15, MemberFaceType::Right, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, -4.0));

      model.ComputePOIForces(0, 12, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, 8.0));
      model.ComputePOIForces(0, 12, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, -8.0));
      model.ComputePOIForces(0, 12, MemberFaceType::Left, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, 8.0));
      model.ComputePOIForces(0, 12, MemberFaceType::Right, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, -8.0));

      model.ComputePOIForces(0, 20, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, 8.0));
      model.ComputePOIForces(0, 20, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, -8.0));
      model.ComputePOIForces(0, 20, MemberFaceType::Left, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, 8.0));
      model.ComputePOIForces(0, 20, MemberFaceType::Right, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, -8.0));

      model.ComputePOIForces(0, 25, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, 4.0));
      model.ComputePOIForces(0, 25, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, -4.0));
      model.ComputePOIForces(0, 25, MemberFaceType::Left, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, 4.0));
      model.ComputePOIForces(0, 25, MemberFaceType::Right, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, -4.0));

      ASSERT_THROWS(model.ComputePOIForces(10, 25, MemberFaceType::Right, LoadOrientation::Member, &fx, &fy, &mz), ReasonCode::LoadingNotFound);
      ASSERT_THROWS(model.ComputePOIForces(0, 32, MemberFaceType::Right, LoadOrientation::Member, &fx, &fy, &mz), ReasonCode::PoiNotFound);

      //////////////////////////////////////////////////////////////////////////////////
      // add a new load case with a horizontal load at the middle
      Loading& pLoading2 = model.CreateLoading(2);
      pLoading2.CreateJointLoad(0, 4, 2.0, 0.0, 0.0);


      model.ComputeJointDeflections(2, 0, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputeJointDeflections(2, 4, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 2.6666667));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputeJointDeflections(2, 8, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 2.6666667));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      model.ComputeMemberForces(2, 1, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, -2.0));
      ASSERT_TRUE(IsEqual(sfy, 0.0));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 2.0));
      ASSERT_TRUE(IsEqual(efy, 0.0));
      ASSERT_TRUE(IsEqual(emz, 0.0));
      model.ComputeMemberForces(2, 2, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 0.0));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 0.0));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      model.ComputeMemberForces(2, 1, LoadOrientation::Global, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, -2.0));
      ASSERT_TRUE(IsEqual(sfy, 0.0));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 2.0));
      ASSERT_TRUE(IsEqual(efy, 0.0));
      ASSERT_TRUE(IsEqual(emz, 0.0));
      model.ComputeMemberForces(2, 2, LoadOrientation::Global, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 0.0));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 0.0));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      model.ComputeReactions(2, 0, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -2.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputeReactions(2, 4, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputeReactions(2, 8, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      model.ComputeMemberDeflections(2, 1, &sdx, &sdy, &srz, &edx, &edy, &erz);
      ASSERT_TRUE(IsEqual(sdx, 0.0));
      ASSERT_TRUE(IsEqual(sdy, 0.0));
      ASSERT_TRUE(IsEqual(srz, 0.0));
      ASSERT_TRUE(IsEqual(edx, 2.6666667));
      ASSERT_TRUE(IsEqual(edy, 0.0));
      ASSERT_TRUE(IsEqual(erz, 0.0));
      model.ComputeMemberDeflections(2, 2, &sdx, &sdy, &srz, &edx, &edy, &erz);
      ASSERT_TRUE(IsEqual(sdx, 2.6666667));
      ASSERT_TRUE(IsEqual(sdy, 0.0));
      ASSERT_TRUE(IsEqual(srz, 0.0));
      ASSERT_TRUE(IsEqual(edx, 2.6666667));
      ASSERT_TRUE(IsEqual(edy, 0.0));
      ASSERT_TRUE(IsEqual(erz, 0.0));

      model.ComputePOIDeflections(2, 10, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputePOIDeflections(2, 15, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 1.333333));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputePOIDeflections(2, 12, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 2.6666667));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputePOIDeflections(2, 20, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 2.6666667));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputePOIDeflections(2, 25, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 2.6666667));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputePOIDeflections(2, 22, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 2.6666667));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      model.ComputePOIDeflections(2, 10, LoadOrientation::Global, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputePOIDeflections(2, 15, LoadOrientation::Global, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 1.333333));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputePOIDeflections(2, 12, LoadOrientation::Global, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 2.6666667));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputePOIDeflections(2, 20, LoadOrientation::Global, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 2.6666667));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputePOIDeflections(2, 25, LoadOrientation::Global, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 2.6666667));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputePOIDeflections(2, 22, LoadOrientation::Global, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 2.6666667));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      model.ComputePOIForces(2, 10, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 2.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputePOIForces(2, 10, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -2.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputePOIForces(2, 10, MemberFaceType::Left, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 2.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputePOIForces(2, 10, MemberFaceType::Right, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -2.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      model.ComputePOIForces(2, 15, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 2.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputePOIForces(2, 15, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -2.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputePOIForces(2, 15, MemberFaceType::Left, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 2.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputePOIForces(2, 15, MemberFaceType::Right, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -2.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      model.ComputePOIForces(2, 12, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 2.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputePOIForces(2, 12, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -2.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputePOIForces(2, 12, MemberFaceType::Left, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 2.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputePOIForces(2, 12, MemberFaceType::Right, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -2.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      model.ComputePOIForces(2, 20, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputePOIForces(2, 20, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputePOIForces(2, 20, MemberFaceType::Left, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputePOIForces(2, 20, MemberFaceType::Right, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      model.ComputePOIForces(2, 25, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputePOIForces(2, 25, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputePOIForces(2, 25, MemberFaceType::Left, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputePOIForces(2, 25, MemberFaceType::Right, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      //////////////////////////////////////////////////////////////////////////////////
      // next let's rotate the model 45 degrees clockwise
      pJoint4.SetX(2.8284271);
      pJoint4.SetY(2.8284271);
      pJoint8.SetX(5.6568542);
      pJoint8.SetY(5.6568542);

      // don't allow end joint to translate
      pJoint8.Support();
      pJoint8.ReleaseDof(JointReleaseType::Mz);

      ASSERT_TRUE(IsEqual(pMember1.GetLength(), 4.0));
      ASSERT_TRUE(IsEqual(pMember2.GetLength(), 4.0));

      // change orientation of point load to be normal to rotated structure
      pJointLoad.SetFx(2.8284271);
      pJointLoad.SetFy(-2.8284271);


      model.ComputeJointDeflections(0, 0, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -2.2857142857143));
      model.ComputeJointDeflections(0, 4, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 4.30998419));
      ASSERT_TRUE(IsEqual(dy, -4.30998419));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputeJointDeflections(0, 8, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 2.2857142857143));

      model.ComputeMemberForces(0, 1, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 2.0));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, -2.0));
      ASSERT_TRUE(IsEqual(emz, 8.0));
      model.ComputeMemberForces(0, 2, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, -2.0));
      ASSERT_TRUE(IsEqual(smz, -8.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 2.0));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      model.ComputeMemberForces(0, 1, LoadOrientation::Global, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, -1.41421356));
      ASSERT_TRUE(IsEqual(sfy, 1.41421356));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 1.41421355));
      ASSERT_TRUE(IsEqual(efy, -1.41421355));
      ASSERT_TRUE(IsEqual(emz, 8.0));
      model.ComputeMemberForces(0, 2, LoadOrientation::Global, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 1.41421355));
      ASSERT_TRUE(IsEqual(sfy, -1.41421355));
      ASSERT_TRUE(IsEqual(smz, -8.0));
      ASSERT_TRUE(IsEqual(efx, -1.41421356));
      ASSERT_TRUE(IsEqual(efy, 1.41421356));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      model.ComputeReactions(0, 0, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -1.41421356));
      ASSERT_TRUE(IsEqual(fy, 1.41421356));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputeReactions(0, 4, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputeReactions(0, 8, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -1.41421356));
      ASSERT_TRUE(IsEqual(fy, 1.41421356));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      ASSERT_THROWS(model.ComputeReactions(1, 8, &fx, &fy, &mz), ReasonCode::LoadingNotFound);
      ASSERT_THROWS(model.ComputeReactions(0, 12, &fx, &fy, &mz), ReasonCode::JointNotFound);

      model.ComputeMemberDeflections(0, 1, &sdx, &sdy, &srz, &edx, &edy, &erz);
      ASSERT_TRUE(IsEqual(sdx, 0.0));
      ASSERT_TRUE(IsEqual(sdy, 0.0));
      ASSERT_TRUE(IsEqual(srz, -2.2857142857143));
      ASSERT_TRUE(IsEqual(edx, 0.0));
      ASSERT_TRUE(IsEqual(edy, -6.0952380952381));
      ASSERT_TRUE(IsEqual(erz, 0.0));
      model.ComputeMemberDeflections(0, 2, &sdx, &sdy, &srz, &edx, &edy, &erz);
      ASSERT_TRUE(IsEqual(sdx, 0.0));
      ASSERT_TRUE(IsEqual(sdy, -6.0952380952381));
      ASSERT_TRUE(IsEqual(srz, 0.0));
      ASSERT_TRUE(IsEqual(edx, 0.0));
      ASSERT_TRUE(IsEqual(edy, 0.0));
      ASSERT_TRUE(IsEqual(erz, 2.2857142857143));

      model.ComputePOIDeflections(0, 10, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -2.2857142857143));
      model.ComputePOIDeflections(0, 15, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -4.1904761904762));
      ASSERT_TRUE(IsEqual(rz, -12.0 / 7.0));
      model.ComputePOIDeflections(0, 12, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -6.0952380952381));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputePOIDeflections(0, 20, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -6.0952380952381));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputePOIDeflections(0, 25, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -4.1904761904762));
      ASSERT_TRUE(IsEqual(rz, 12.0 / 7.0));
      model.ComputePOIDeflections(0, 22, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 2.2857142857143));

      model.ComputePOIDeflections(0, 10, LoadOrientation::Global, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -2.2857142857143));
      model.ComputePOIDeflections(0, 15, LoadOrientation::Global, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 2.9631141));
      ASSERT_TRUE(IsEqual(dy, -2.9631141));
      ASSERT_TRUE(IsEqual(rz, -12.0 / 7.0));
      model.ComputePOIDeflections(0, 12, LoadOrientation::Global, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 4.3099842));
      ASSERT_TRUE(IsEqual(dy, -4.3099842));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputePOIDeflections(0, 20, LoadOrientation::Global, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 4.3099842));
      ASSERT_TRUE(IsEqual(dy, -4.3099842));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputePOIDeflections(0, 25, LoadOrientation::Global, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 2.9631141));
      ASSERT_TRUE(IsEqual(dy, -2.9631141));
      ASSERT_TRUE(IsEqual(rz, 12.0 / 7.0));
      model.ComputePOIDeflections(0, 22, LoadOrientation::Global, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 2.2857142857143));

      model.ComputePOIForces(0, 10, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 1.41421355));
      ASSERT_TRUE(IsEqual(fy, -1.41421355));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputePOIForces(0, 10, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputePOIForces(0, 10, MemberFaceType::Left, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputePOIForces(0, 10, MemberFaceType::Right, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      model.ComputePOIForces(0, 15, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 1.41421355));
      ASSERT_TRUE(IsEqual(fy, -1.41421355));
      ASSERT_TRUE(IsEqual(mz, 4.0));
      model.ComputePOIForces(0, 15, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, -4.0));
      model.ComputePOIForces(0, 15, MemberFaceType::Left, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, 4.0));
      model.ComputePOIForces(0, 15, MemberFaceType::Right, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, -4.0));

      model.ComputePOIForces(0, 12, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 1.41421355));
      ASSERT_TRUE(IsEqual(fy, -1.41421355));
      ASSERT_TRUE(IsEqual(mz, 8.0));
      model.ComputePOIForces(0, 12, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, -8.0));
      model.ComputePOIForces(0, 12, MemberFaceType::Left, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, 8.0));
      model.ComputePOIForces(0, 12, MemberFaceType::Right, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, -8.0));

      model.ComputePOIForces(0, 20, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, 8.0));
      model.ComputePOIForces(0, 20, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 1.41421355));
      ASSERT_TRUE(IsEqual(fy, -1.41421355));
      ASSERT_TRUE(IsEqual(mz, -8.0));
      model.ComputePOIForces(0, 20, MemberFaceType::Left, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, 8.0));
      model.ComputePOIForces(0, 20, MemberFaceType::Right, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, -8.0));

      model.ComputePOIForces(0, 25, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, 4.0));
      model.ComputePOIForces(0, 25, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 1.41421355));
      ASSERT_TRUE(IsEqual(fy, -1.41421355));
      ASSERT_TRUE(IsEqual(mz, -4.0));
      model.ComputePOIForces(0, 25, MemberFaceType::Left, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, 4.0));
      model.ComputePOIForces(0, 25, MemberFaceType::Right, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, -4.0));

      //////////////////////////////////////////////////////////////////////////////////
      // next let's rotate the model 135 degrees clockwise
      pJoint4.SetX(-2.8284271);
      pJoint4.SetY(2.8284271);
      pJoint8.SetX(-5.6568542);
      pJoint8.SetY(5.6568542);

      ASSERT_TRUE(IsEqual(pMember1.GetLength(), 4.0));
      ASSERT_TRUE(IsEqual(pMember2.GetLength(), 4.0));

      pJointLoad.SetFx(2.8284271);
      pJointLoad.SetFy(2.8284271);


      model.ComputeJointDeflections(0, 0, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -2.2857142857143));
      model.ComputeJointDeflections(0, 4, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 4.30998419));
      ASSERT_TRUE(IsEqual(dy, 4.30998419));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputeJointDeflections(0, 8, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 2.2857142857143));

      model.ComputeMemberForces(0, 1, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 2.0));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, -2.0));
      ASSERT_TRUE(IsEqual(emz, 8.0));
      model.ComputeMemberForces(0, 2, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, -2.0));
      ASSERT_TRUE(IsEqual(smz, -8.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 2.0));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      model.ComputeMemberForces(0, 1, LoadOrientation::Global, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, -1.41421356));
      ASSERT_TRUE(IsEqual(sfy, -1.41421356));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 1.41421355));
      ASSERT_TRUE(IsEqual(efy, 1.41421355));
      ASSERT_TRUE(IsEqual(emz, 8.0));
      model.ComputeMemberForces(0, 2, LoadOrientation::Global, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 1.41421355));
      ASSERT_TRUE(IsEqual(sfy, 1.41421355));
      ASSERT_TRUE(IsEqual(smz, -8.0));
      ASSERT_TRUE(IsEqual(efx, -1.41421356));
      ASSERT_TRUE(IsEqual(efy, -1.41421356));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      model.ComputeReactions(0, 0, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -1.41421356));
      ASSERT_TRUE(IsEqual(fy, -1.41421356));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputeReactions(0, 4, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputeReactions(0, 8, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -1.41421356));
      ASSERT_TRUE(IsEqual(fy, -1.41421356));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      model.ComputeMemberDeflections(0, 1, &sdx, &sdy, &srz, &edx, &edy, &erz);
      ASSERT_TRUE(IsEqual(sdx, 0.0));
      ASSERT_TRUE(IsEqual(sdy, 0.0));
      ASSERT_TRUE(IsEqual(srz, -2.2857142857143));
      ASSERT_TRUE(IsEqual(edx, 0.0));
      ASSERT_TRUE(IsEqual(edy, -6.0952380952381));
      ASSERT_TRUE(IsEqual(erz, 0.0));
      model.ComputeMemberDeflections(0, 2, &sdx, &sdy, &srz, &edx, &edy, &erz);
      ASSERT_TRUE(IsEqual(sdx, 0.0));
      ASSERT_TRUE(IsEqual(sdy, -6.0952380952381));
      ASSERT_TRUE(IsEqual(srz, 0.0));
      ASSERT_TRUE(IsEqual(edx, 0.0));
      ASSERT_TRUE(IsEqual(edy, 0.0));
      ASSERT_TRUE(IsEqual(erz, 2.2857142857143));

      model.ComputePOIDeflections(0, 10, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -2.2857142857143));
      model.ComputePOIDeflections(0, 15, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -4.1904761904762));
      ASSERT_TRUE(IsEqual(rz, -12.0 / 7.0));
      model.ComputePOIDeflections(0, 12, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -6.0952380952381));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputePOIDeflections(0, 20, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -6.0952380952381));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputePOIDeflections(0, 25, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -4.1904761904762));
      ASSERT_TRUE(IsEqual(rz, 12.0 / 7.0));
      model.ComputePOIDeflections(0, 22, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 2.2857142857143));

      model.ComputePOIDeflections(0, 10, LoadOrientation::Global, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -2.2857142857143));
      model.ComputePOIDeflections(0, 15, LoadOrientation::Global, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 2.9631141));
      ASSERT_TRUE(IsEqual(dy, 2.9631141));
      ASSERT_TRUE(IsEqual(rz, -12.0 / 7.0));
      model.ComputePOIDeflections(0, 12, LoadOrientation::Global, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 4.3099842));
      ASSERT_TRUE(IsEqual(dy, 4.3099842));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputePOIDeflections(0, 20, LoadOrientation::Global, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 4.3099842));
      ASSERT_TRUE(IsEqual(dy, 4.3099842));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputePOIDeflections(0, 25, LoadOrientation::Global, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 2.9631141));
      ASSERT_TRUE(IsEqual(dy, 2.9631141));
      ASSERT_TRUE(IsEqual(rz, 12.0 / 7.0));
      model.ComputePOIDeflections(0, 22, LoadOrientation::Global, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 2.2857142857143));

      model.ComputePOIForces(0, 10, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputePOIForces(0, 10, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, -1.41421355));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputePOIForces(0, 10, MemberFaceType::Left, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputePOIForces(0, 10, MemberFaceType::Right, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      model.ComputePOIForces(0, 15, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, 4.0));
      model.ComputePOIForces(0, 15, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, -1.41421355));
      ASSERT_TRUE(IsEqual(mz, -4.0));
      model.ComputePOIForces(0, 15, MemberFaceType::Left, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, 4.0));
      model.ComputePOIForces(0, 15, MemberFaceType::Right, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, -4.0));

      model.ComputePOIForces(0, 12, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, 8.0));
      model.ComputePOIForces(0, 12, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, -1.41421355));
      ASSERT_TRUE(IsEqual(mz, -8.0));
      model.ComputePOIForces(0, 12, MemberFaceType::Left, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, 8.0));
      model.ComputePOIForces(0, 12, MemberFaceType::Right, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, -8.0));

      model.ComputePOIForces(0, 20, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, -1.41421355));
      ASSERT_TRUE(IsEqual(mz, 8.0));
      model.ComputePOIForces(0, 20, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, -8.0));
      model.ComputePOIForces(0, 20, MemberFaceType::Left, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, 8.0));
      model.ComputePOIForces(0, 20, MemberFaceType::Right, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, -8.0));

      model.ComputePOIForces(0, 25, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, -1.41421355));
      ASSERT_TRUE(IsEqual(mz, 4.0));
      model.ComputePOIForces(0, 25, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, -4.0));
      model.ComputePOIForces(0, 25, MemberFaceType::Left, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, 4.0));
      model.ComputePOIForces(0, 25, MemberFaceType::Right, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, -4.0));

      //////////////////////////////////////////////////////////////////////////////////
      // Rotate the model 225 degrees clockwise
      pJoint4.SetX(-2.8284271);
      pJoint4.SetY(-2.8284271);
      pJoint8.SetX(-5.6568542);
      pJoint8.SetY(-5.6568542);

      ASSERT_TRUE(IsEqual(pMember1.GetLength(), 4.0));
      ASSERT_TRUE(IsEqual(pMember2.GetLength(), 4.0));

      pJointLoad.SetFx(-2.8284271);
      pJointLoad.SetFy(2.8284271);


      model.ComputeJointDeflections(0, 0, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -2.2857142857143));
      model.ComputeJointDeflections(0, 4, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, -4.30998419));
      ASSERT_TRUE(IsEqual(dy, 4.30998419));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputeJointDeflections(0, 8, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 2.2857142857143));

      model.ComputeMemberForces(0, 1, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 2.0));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, -2.0));
      ASSERT_TRUE(IsEqual(emz, 8.0));
      model.ComputeMemberForces(0, 2, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, -2.0));
      ASSERT_TRUE(IsEqual(smz, -8.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 2.0));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      model.ComputeMemberForces(0, 1, LoadOrientation::Global, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 1.41421356));
      ASSERT_TRUE(IsEqual(sfy, -1.41421356));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, -1.41421355));
      ASSERT_TRUE(IsEqual(efy, 1.41421355));
      ASSERT_TRUE(IsEqual(emz, 8.0));
      model.ComputeMemberForces(0, 2, LoadOrientation::Global, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, -1.41421355));
      ASSERT_TRUE(IsEqual(sfy, 1.41421355));
      ASSERT_TRUE(IsEqual(smz, -8.0));
      ASSERT_TRUE(IsEqual(efx, 1.41421356));
      ASSERT_TRUE(IsEqual(efy, -1.41421356));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      model.ComputeReactions(0, 0, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 1.41421356));
      ASSERT_TRUE(IsEqual(fy, -1.41421356));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputeReactions(0, 4, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputeReactions(0, 8, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 1.41421356));
      ASSERT_TRUE(IsEqual(fy, -1.41421356));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      model.ComputeMemberDeflections(0, 1, &sdx, &sdy, &srz, &edx, &edy, &erz);
      ASSERT_TRUE(IsEqual(sdx, 0.0));
      ASSERT_TRUE(IsEqual(sdy, 0.0));
      ASSERT_TRUE(IsEqual(srz, -2.2857142857143));
      ASSERT_TRUE(IsEqual(edx, 0.0));
      ASSERT_TRUE(IsEqual(edy, -6.0952380952381));
      ASSERT_TRUE(IsEqual(erz, 0.0));
      model.ComputeMemberDeflections(0, 2, &sdx, &sdy, &srz, &edx, &edy, &erz);
      ASSERT_TRUE(IsEqual(sdx, 0.0));
      ASSERT_TRUE(IsEqual(sdy, -6.0952380952381));
      ASSERT_TRUE(IsEqual(srz, 0.0));
      ASSERT_TRUE(IsEqual(edx, 0.0));
      ASSERT_TRUE(IsEqual(edy, 0.0));
      ASSERT_TRUE(IsEqual(erz, 2.2857142857143));

      model.ComputePOIDeflections(0, 10, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -2.2857142857143));
      model.ComputePOIDeflections(0, 15, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -4.1904761904762));
      ASSERT_TRUE(IsEqual(rz, -12.0 / 7.0));
      model.ComputePOIDeflections(0, 12, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -6.0952380952381));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputePOIDeflections(0, 20, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -6.0952380952381));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputePOIDeflections(0, 25, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -4.1904761904762));
      ASSERT_TRUE(IsEqual(rz, 12.0 / 7.0));
      model.ComputePOIDeflections(0, 22, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 2.2857142857143));

      model.ComputePOIDeflections(0, 10, LoadOrientation::Global, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -2.2857142857143));
      model.ComputePOIDeflections(0, 15, LoadOrientation::Global, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, -2.9631141));
      ASSERT_TRUE(IsEqual(dy, 2.9631141));
      ASSERT_TRUE(IsEqual(rz, -12.0 / 7.0));
      model.ComputePOIDeflections(0, 12, LoadOrientation::Global, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, -4.3099842));
      ASSERT_TRUE(IsEqual(dy, 4.3099842));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputePOIDeflections(0, 20, LoadOrientation::Global, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, -4.3099842));
      ASSERT_TRUE(IsEqual(dy, 4.3099842));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputePOIDeflections(0, 25, LoadOrientation::Global, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, -2.9631141));
      ASSERT_TRUE(IsEqual(dy, 2.9631141));
      ASSERT_TRUE(IsEqual(rz, 12.0 / 7.0));
      model.ComputePOIDeflections(0, 22, LoadOrientation::Global, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 2.2857142857143));

      model.ComputePOIForces(0, 10, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputePOIForces(0, 10, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 1.41421355));
      ASSERT_TRUE(IsEqual(fy, -1.41421355));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputePOIForces(0, 10, MemberFaceType::Left, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputePOIForces(0, 10, MemberFaceType::Right, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      model.ComputePOIForces(0, 15, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, 4.0));
      model.ComputePOIForces(0, 15, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 1.41421355));
      ASSERT_TRUE(IsEqual(fy, -1.41421355));
      ASSERT_TRUE(IsEqual(mz, -4.0));
      model.ComputePOIForces(0, 15, MemberFaceType::Left, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, 4.0));
      model.ComputePOIForces(0, 15, MemberFaceType::Right, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, -4.0));

      model.ComputePOIForces(0, 12, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, 8.0));
      model.ComputePOIForces(0, 12, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 1.41421355));
      ASSERT_TRUE(IsEqual(fy, -1.41421355));
      ASSERT_TRUE(IsEqual(mz, -8.0));
      model.ComputePOIForces(0, 12, MemberFaceType::Left, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, 8.0));
      model.ComputePOIForces(0, 12, MemberFaceType::Right, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, -8.0));

      model.ComputePOIForces(0, 20, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 1.41421355));
      ASSERT_TRUE(IsEqual(fy, -1.41421355));
      ASSERT_TRUE(IsEqual(mz, 8.0));
      model.ComputePOIForces(0, 20, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, -8.0));
      model.ComputePOIForces(0, 20, MemberFaceType::Left, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, 8.0));
      model.ComputePOIForces(0, 20, MemberFaceType::Right, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, -8.0));

      model.ComputePOIForces(0, 25, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 1.41421355));
      ASSERT_TRUE(IsEqual(fy, -1.41421355));
      ASSERT_TRUE(IsEqual(mz, 4.0));
      model.ComputePOIForces(0, 25, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, -4.0));
      model.ComputePOIForces(0, 25, MemberFaceType::Left, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, 4.0));
      model.ComputePOIForces(0, 25, MemberFaceType::Right, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, -4.0));

      //////////////////////////////////////////////////////////////////////////////////
      // Rotate the model -45 degrees clockwise
      pJoint4.SetX(2.8284271);
      pJoint4.SetY(-2.8284271);
      pJoint8.SetX(5.6568542);
      pJoint8.SetY(-5.6568542);

      ASSERT_TRUE(IsEqual(pMember1.GetLength(), 4.0));
      ASSERT_TRUE(IsEqual(pMember2.GetLength(), 4.0));

      pJointLoad.SetFx(-2.8284271);
      pJointLoad.SetFy(-2.8284271);


      model.ComputeJointDeflections(0, 0, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -2.2857142857143));
      model.ComputeJointDeflections(0, 4, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, -4.30998419));
      ASSERT_TRUE(IsEqual(dy, -4.30998419));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputeJointDeflections(0, 8, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 2.2857142857143));

      model.ComputeMemberForces(0, 1, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 2.0));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, -2.0));
      ASSERT_TRUE(IsEqual(emz, 8.0));
      model.ComputeMemberForces(0, 2, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, -2.0));
      ASSERT_TRUE(IsEqual(smz, -8.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 2.0));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      model.ComputeMemberForces(0, 1, LoadOrientation::Global, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 1.41421356));
      ASSERT_TRUE(IsEqual(sfy, 1.41421356));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, -1.41421355));
      ASSERT_TRUE(IsEqual(efy, -1.41421355));
      ASSERT_TRUE(IsEqual(emz, 8.0));
      model.ComputeMemberForces(0, 2, LoadOrientation::Global, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, -1.41421355));
      ASSERT_TRUE(IsEqual(sfy, -1.41421355));
      ASSERT_TRUE(IsEqual(smz, -8.0));
      ASSERT_TRUE(IsEqual(efx, 1.41421356));
      ASSERT_TRUE(IsEqual(efy, 1.41421356));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      model.ComputeReactions(0, 0, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 1.41421356));
      ASSERT_TRUE(IsEqual(fy, 1.41421356));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputeReactions(0, 4, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputeReactions(0, 8, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 1.41421356));
      ASSERT_TRUE(IsEqual(fy, 1.41421356));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      model.ComputeMemberDeflections(0, 1, &sdx, &sdy, &srz, &edx, &edy, &erz);
      ASSERT_TRUE(IsEqual(sdx, 0.0));
      ASSERT_TRUE(IsEqual(sdy, 0.0));
      ASSERT_TRUE(IsEqual(srz, -2.2857142857143));
      ASSERT_TRUE(IsEqual(edx, 0.0));
      ASSERT_TRUE(IsEqual(edy, -6.0952380952381));
      ASSERT_TRUE(IsEqual(erz, 0.0));
      model.ComputeMemberDeflections(0, 2, &sdx, &sdy, &srz, &edx, &edy, &erz);
      ASSERT_TRUE(IsEqual(sdx, 0.0));
      ASSERT_TRUE(IsEqual(sdy, -6.0952380952381));
      ASSERT_TRUE(IsEqual(srz, 0.0));
      ASSERT_TRUE(IsEqual(edx, 0.0));
      ASSERT_TRUE(IsEqual(edy, 0.0));
      ASSERT_TRUE(IsEqual(erz, 2.2857142857143));

      model.ComputePOIDeflections(0, 10, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -2.2857142857143));
      model.ComputePOIDeflections(0, 15, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -4.1904761904762));
      ASSERT_TRUE(IsEqual(rz, -12.0 / 7.0));
      model.ComputePOIDeflections(0, 12, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -6.0952380952381));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputePOIDeflections(0, 20, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -6.0952380952381));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputePOIDeflections(0, 25, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -4.1904761904762));
      ASSERT_TRUE(IsEqual(rz, 12.0 / 7.0));
      model.ComputePOIDeflections(0, 22, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 2.2857142857143));

      model.ComputePOIDeflections(0, 10, LoadOrientation::Global, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -2.2857142857143));
      model.ComputePOIDeflections(0, 15, LoadOrientation::Global, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, -2.9631141));
      ASSERT_TRUE(IsEqual(dy, -2.9631141));
      ASSERT_TRUE(IsEqual(rz, -12.0 / 7.0));
      model.ComputePOIDeflections(0, 12, LoadOrientation::Global, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, -4.3099842));
      ASSERT_TRUE(IsEqual(dy, -4.3099842));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputePOIDeflections(0, 20, LoadOrientation::Global, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, -4.3099842));
      ASSERT_TRUE(IsEqual(dy, -4.3099842));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputePOIDeflections(0, 25, LoadOrientation::Global, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, -2.9631141));
      ASSERT_TRUE(IsEqual(dy, -2.9631141));
      ASSERT_TRUE(IsEqual(rz, 12.0 / 7.0));
      model.ComputePOIDeflections(0, 22, LoadOrientation::Global, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 2.2857142857143));

      model.ComputePOIForces(0, 10, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, -1.41421355));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputePOIForces(0, 10, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputePOIForces(0, 10, MemberFaceType::Left, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputePOIForces(0, 10, MemberFaceType::Right, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      model.ComputePOIForces(0, 15, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, -1.41421355));
      ASSERT_TRUE(IsEqual(mz, 4.0));
      model.ComputePOIForces(0, 15, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, -4.0));
      model.ComputePOIForces(0, 15, MemberFaceType::Left, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, 4.0));
      model.ComputePOIForces(0, 15, MemberFaceType::Right, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, -4.0));

      model.ComputePOIForces(0, 12, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, -1.41421355));
      ASSERT_TRUE(IsEqual(mz, 8.0));
      model.ComputePOIForces(0, 12, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, -8.0));
      model.ComputePOIForces(0, 12, MemberFaceType::Left, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, 8.0));
      model.ComputePOIForces(0, 12, MemberFaceType::Right, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, -8.0));

      model.ComputePOIForces(0, 20, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, 8.0));
      model.ComputePOIForces(0, 20, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, -1.41421355));
      ASSERT_TRUE(IsEqual(mz, -8.0));
      model.ComputePOIForces(0, 20, MemberFaceType::Left, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, 8.0));
      model.ComputePOIForces(0, 20, MemberFaceType::Right, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, -8.0));

      model.ComputePOIForces(0, 25, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, 4.0));
      model.ComputePOIForces(0, 25, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, -1.41421355));
      ASSERT_TRUE(IsEqual(mz, -4.0));
      model.ComputePOIForces(0, 25, MemberFaceType::Left, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, 4.0));
      model.ComputePOIForces(0, 25, MemberFaceType::Right, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, -4.0));
   }
};
} // namespace FEA2DUnitTests
