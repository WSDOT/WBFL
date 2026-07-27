///////////////////////////////////////////////////////////////////////
// FEA2D - Two-dimensional Finite Element Analysis Engine
// Copyright � 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
///////////////////////////////////////////////////////////////////////
// TestSimpleBeamWithPointLoad.cpp
//
// Mirrors Fem2d\Fem2dUnitTests\TestSimpleBeamWithPointLoad.cpp.
#include "pch.h"

namespace FEA2DUnitTests
{

TEST_CLASS(TestSimpleBeamWithPointLoad)
{
public:
   TEST_METHOD(MidspanPointLoad_PinPin_Rotations)
   {
      /*////////////////////////////////////////////////////
                               | P=4 at L/2
                               V
                 0=============================0
                 A                             O
             L = 8           Mc = PL/4 = 8
             EA = 3.0        Dc = PL^3/48EI =
             EI = 7.0
      *////////////////////////////////////////////////////
      Model model;
      model.CreateJoint(0, 0.0, 0.0);
      model.CreateJoint(8, 8.0, 0.0);

      Joint* pJoint0 = model.FindJoint(0);

      Joint* pJoint8 = model.FindJoint(8);

      pJoint0->Support();
      pJoint0->ReleaseDof(JointReleaseType::Mz);
      pJoint8->Support();
      pJoint8->ReleaseDof(JointReleaseType::Fx);
      pJoint8->ReleaseDof(JointReleaseType::Mz);

      model.CreateMember(1, 0, 8, 3.0, 7.0);

      Loading& pLoading = model.CreateLoading(0);
      pLoading.CreatePointLoad(0, 1, 4.0, 0.0, -4.0, 0.0, LoadOrientation::Global);

      // POI's at 1/4 points in member 1 - these results are pre-calculated
      model.CreatePOI(10, 1, 0.0);
      model.CreatePOI(15, 1, -.25);
      model.CreatePOI(12, 1, -0.5);


      Float64 dx, dy, rz;
      model.ComputeJointDeflections(0, 0, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -2.2857142857143));
      model.ComputeJointDeflections(0, 8, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 2.2857142857143));

      Float64 sfx, sfy, smz, efx, efy, emz;
      model.ComputeMemberForces(0, 1, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 2.0));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 2.0));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      model.ComputeMemberForces(0, 1, LoadOrientation::Global, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 2.0));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 2.0));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      Float64 fx, fy, mz;
      model.ComputeReactions(0, 0, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputeReactions(0, 8, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      Float64 sdx, sdy, srz, edx, edy, erz;
      model.ComputeMemberDeflections(0, 1, &sdx, &sdy, &srz, &edx, &edy, &erz);
      ASSERT_TRUE(IsEqual(sdx, 0.0));
      ASSERT_TRUE(IsEqual(sdy, 0.0));
      ASSERT_TRUE(IsEqual(srz, -2.2857142857143));
      ASSERT_TRUE(IsEqual(edx, 0.0));
      ASSERT_TRUE(IsEqual(edy, 0.0));
      ASSERT_TRUE(IsEqual(erz, 2.2857142857143));

      // POI's at 1/4 points of second half - calculated on the fly
      model.CreatePOI(20, 1, 4.0);
      model.CreatePOI(25, 1, 6.0);
      model.CreatePOI(22, 1, 8.0);

      model.ComputePOIDeflections(0, 10, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0)); ASSERT_TRUE(IsEqual(dy, 0.0)); ASSERT_TRUE(IsEqual(rz, -2.2857142857143));
      model.ComputePOIDeflections(0, 15, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0)); ASSERT_TRUE(IsEqual(dy, -4.1904761904762)); ASSERT_TRUE(IsEqual(rz, -12.0 / 7.0));
      model.ComputePOIDeflections(0, 12, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0)); ASSERT_TRUE(IsEqual(dy, -6.0952380952381)); ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputePOIDeflections(0, 20, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0)); ASSERT_TRUE(IsEqual(dy, -6.0952380952381)); ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputePOIDeflections(0, 25, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0)); ASSERT_TRUE(IsEqual(dy, -4.1904761904762)); ASSERT_TRUE(IsEqual(rz, 12.0 / 7.0));
      model.ComputePOIDeflections(0, 22, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0)); ASSERT_TRUE(IsEqual(dy, 0.0)); ASSERT_TRUE(IsEqual(rz, 2.2857142857143));

      // same POIs, global orientation - member is horizontal, so global == member here
      model.ComputePOIDeflections(0, 15, LoadOrientation::Global, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dy, -4.1904761904762));
      model.ComputePOIDeflections(0, 15, LoadOrientation::GlobalProjected, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dy, -4.1904761904762));

      model.ComputePOIForces(0, 10, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0)); ASSERT_TRUE(IsEqual(fy, -2.0)); ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputePOIForces(0, 10, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0)); ASSERT_TRUE(IsEqual(fy, 2.0)); ASSERT_TRUE(IsEqual(mz, 0.0));

      model.ComputePOIForces(0, 15, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0)); ASSERT_TRUE(IsEqual(fy, -2.0)); ASSERT_TRUE(IsEqual(mz, 4.0));
      model.ComputePOIForces(0, 15, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0)); ASSERT_TRUE(IsEqual(fy, 2.0)); ASSERT_TRUE(IsEqual(mz, -4.0));

      model.ComputePOIForces(0, 12, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0)); ASSERT_TRUE(IsEqual(fy, -2.0)); ASSERT_TRUE(IsEqual(mz, 8.0));
      model.ComputePOIForces(0, 12, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0)); ASSERT_TRUE(IsEqual(fy, -2.0)); ASSERT_TRUE(IsEqual(mz, -8.0));

      model.ComputePOIForces(0, 25, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0)); ASSERT_TRUE(IsEqual(fy, 2.0)); ASSERT_TRUE(IsEqual(mz, 4.0));
      model.ComputePOIForces(0, 25, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0)); ASSERT_TRUE(IsEqual(fy, -2.0)); ASSERT_TRUE(IsEqual(mz, -4.0));

      //////////////////////////////////////////////////////////////////////////////////
      // add a new load case with a horizontal load at the middle
      Loading& pLoading2 = model.CreateLoading(2);
      pLoading2.CreatePointLoad(0, 1, 4.0, 2.0, 0.0, 0.0, LoadOrientation::Global);


      model.ComputeJointDeflections(2, 0, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0)); ASSERT_TRUE(IsEqual(dy, 0.0)); ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputeJointDeflections(2, 8, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 2.6666667)); ASSERT_TRUE(IsEqual(dy, 0.0)); ASSERT_TRUE(IsEqual(rz, 0.0));

      model.ComputeMemberForces(2, 1, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, -2.0)); ASSERT_TRUE(IsEqual(sfy, 0.0)); ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 0.0)); ASSERT_TRUE(IsEqual(efy, 0.0)); ASSERT_TRUE(IsEqual(emz, 0.0));

      model.ComputeReactions(2, 0, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -2.0)); ASSERT_TRUE(IsEqual(fy, 0.0)); ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputeReactions(2, 8, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0)); ASSERT_TRUE(IsEqual(fy, 0.0)); ASSERT_TRUE(IsEqual(mz, 0.0));

      model.ComputeMemberDeflections(2, 1, &sdx, &sdy, &srz, &edx, &edy, &erz);
      ASSERT_TRUE(IsEqual(sdx, 0.0)); ASSERT_TRUE(IsEqual(sdy, 0.0)); ASSERT_TRUE(IsEqual(srz, 0.0));
      ASSERT_TRUE(IsEqual(edx, 2.6666667)); ASSERT_TRUE(IsEqual(edy, 0.0)); ASSERT_TRUE(IsEqual(erz, 0.0));

      model.ComputePOIForces(2, 10, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 2.0)); ASSERT_TRUE(IsEqual(fy, 0.0)); ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputePOIForces(2, 10, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -2.0)); ASSERT_TRUE(IsEqual(fy, 0.0)); ASSERT_TRUE(IsEqual(mz, 0.0));
   }

   TEST_METHOD(SameBeamLoadedInLocalMemberCoords_RotationsAt135And225)
   {
      // Same 8'-span pin-pin beam with the midspan point load specified in
      // *member* coordinates (LoadOrientation::Member), so results should
      // stay constant while the model is rotated in global space - unlike
      // the global-coordinate load case above.
      Model model;
      model.CreateJoint(0, 0.0, 0.0);
      model.CreateJoint(8, 8.0, 0.0);

      Joint* pJoint0 = model.FindJoint(0);

      Joint* pJoint8 = model.FindJoint(8);

      pJoint0->Support();
      pJoint0->ReleaseDof(JointReleaseType::Mz);
      pJoint8->Support();
      pJoint8->ReleaseDof(JointReleaseType::Mz);

      Member& pMember1 = model.CreateMember(1, 0, 8, 3.0, 7.0);

      Loading& pLoading = model.CreateLoading(0);
      PointLoad& pPointLoad = pLoading.CreatePointLoad(0, 1, 4.0, 0.0, -4.0, 0.0, LoadOrientation::Global);
      // use local member coord's
      pPointLoad.SetOrientation(LoadOrientation::Member);

      model.CreatePOI(10, 1, 0.0);
      model.CreatePOI(15, 1, -.25);
      model.CreatePOI(12, 1, -0.5);
      model.CreatePOI(20, 1, 4.0);
      model.CreatePOI(25, 1, 6.0);
      model.CreatePOI(22, 1, 8.0);

      //////////////////////////////////////////////////////////////////////////////////
      // rotate the model 135 degrees clockwise - since orientation is local,
      // no need to change the load to be normal to the rotated structure
      pJoint8->SetX(-5.6568542);
      pJoint8->SetY(5.6568542);

      ASSERT_TRUE(IsEqual(pMember1.GetLength(), 8.0));


      Float64 dx, dy, rz;
      model.ComputeJointDeflections(0, 0, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -2.2857142857143));
      model.ComputeJointDeflections(0, 8, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 2.2857142857143));

      Float64 sfx, sfy, smz, efx, efy, emz;
      model.ComputeMemberForces(0, 1, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 2.0));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 2.0));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      Float64 fx, fy, mz;
      model.ComputeReactions(0, 0, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -1.41421356));
      ASSERT_TRUE(IsEqual(fy, -1.41421356));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputeReactions(0, 8, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -1.41421356));
      ASSERT_TRUE(IsEqual(fy, -1.41421356));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      Float64 sdx, sdy, srz, edx, edy, erz;
      model.ComputeMemberDeflections(0, 1, &sdx, &sdy, &srz, &edx, &edy, &erz);
      ASSERT_TRUE(IsEqual(sdx, 0.0));
      ASSERT_TRUE(IsEqual(sdy, 0.0));
      ASSERT_TRUE(IsEqual(srz, -2.2857142857143));
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
      model.ComputePOIDeflections(0, 10, LoadOrientation::GlobalProjected, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -2.2857142857143));
      model.ComputePOIDeflections(0, 15, LoadOrientation::GlobalProjected, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 2.9631141));
      ASSERT_TRUE(IsEqual(dy, 2.9631141));
      ASSERT_TRUE(IsEqual(rz, -12.0 / 7.0));
      model.ComputePOIDeflections(0, 12, LoadOrientation::GlobalProjected, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 4.3099842));
      ASSERT_TRUE(IsEqual(dy, 4.3099842));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputePOIDeflections(0, 20, LoadOrientation::GlobalProjected, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 4.3099842));
      ASSERT_TRUE(IsEqual(dy, 4.3099842));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputePOIDeflections(0, 25, LoadOrientation::GlobalProjected, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 2.9631141));
      ASSERT_TRUE(IsEqual(dy, 2.9631141));
      ASSERT_TRUE(IsEqual(rz, 12.0 / 7.0));
      model.ComputePOIDeflections(0, 22, LoadOrientation::GlobalProjected, &dx, &dy, &rz);
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
      model.ComputePOIForces(0, 10, MemberFaceType::Left, LoadOrientation::GlobalProjected, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputePOIForces(0, 10, MemberFaceType::Right, LoadOrientation::GlobalProjected, &fx, &fy, &mz);
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
      model.ComputePOIForces(0, 15, MemberFaceType::Left, LoadOrientation::GlobalProjected, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, 4.0));
      model.ComputePOIForces(0, 15, MemberFaceType::Right, LoadOrientation::GlobalProjected, &fx, &fy, &mz);
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
      model.ComputePOIForces(0, 12, MemberFaceType::Left, LoadOrientation::GlobalProjected, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, 8.0));
      model.ComputePOIForces(0, 12, MemberFaceType::Right, LoadOrientation::GlobalProjected, &fx, &fy, &mz);
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
      ASSERT_TRUE(IsEqual(fx, 1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, 8.0));
      model.ComputePOIForces(0, 20, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, -8.0));
      model.ComputePOIForces(0, 20, MemberFaceType::Left, LoadOrientation::GlobalProjected, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, 8.0));
      model.ComputePOIForces(0, 20, MemberFaceType::Right, LoadOrientation::GlobalProjected, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, -8.0));
      model.ComputePOIForces(0, 20, MemberFaceType::Left, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
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
      model.ComputePOIForces(0, 25, MemberFaceType::Left, LoadOrientation::GlobalProjected, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, -1.41421355));
      ASSERT_TRUE(IsEqual(mz, 4.0));
      model.ComputePOIForces(0, 25, MemberFaceType::Right, LoadOrientation::GlobalProjected, &fx, &fy, &mz);
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
      pJoint8->SetX(-5.6568542);
      pJoint8->SetY(-5.6568542);

      ASSERT_TRUE(IsEqual(pMember1.GetLength(), 8.0));


      model.ComputeJointDeflections(0, 0, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -2.2857142857143));
      model.ComputeJointDeflections(0, 8, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 2.2857142857143));

      model.ComputeMemberForces(0, 1, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 2.0));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 2.0));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      model.ComputeReactions(0, 0, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 1.41421356));
      ASSERT_TRUE(IsEqual(fy, -1.41421356));
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

      model.ComputePOIDeflections(0, 10, LoadOrientation::GlobalProjected, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -2.2857142857143));
      model.ComputePOIDeflections(0, 15, LoadOrientation::GlobalProjected, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, -2.9631141));
      ASSERT_TRUE(IsEqual(dy, 2.9631141));
      ASSERT_TRUE(IsEqual(rz, -12.0 / 7.0));
      model.ComputePOIDeflections(0, 22, LoadOrientation::GlobalProjected, &dx, &dy, &rz);
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
      model.ComputePOIForces(0, 10, MemberFaceType::Left, LoadOrientation::GlobalProjected, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputePOIForces(0, 10, MemberFaceType::Right, LoadOrientation::GlobalProjected, &fx, &fy, &mz);
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
      model.ComputePOIForces(0, 15, MemberFaceType::Left, LoadOrientation::GlobalProjected, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, 4.0));
      model.ComputePOIForces(0, 15, MemberFaceType::Right, LoadOrientation::GlobalProjected, &fx, &fy, &mz);
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
      model.ComputePOIForces(0, 12, MemberFaceType::Left, LoadOrientation::GlobalProjected, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, 8.0));
      model.ComputePOIForces(0, 12, MemberFaceType::Right, LoadOrientation::GlobalProjected, &fx, &fy, &mz);
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
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, 8.0));
      model.ComputePOIForces(0, 20, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, -8.0));
      model.ComputePOIForces(0, 20, MemberFaceType::Left, LoadOrientation::GlobalProjected, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, 8.0));
      model.ComputePOIForces(0, 20, MemberFaceType::Right, LoadOrientation::GlobalProjected, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, -8.0));
      model.ComputePOIForces(0, 20, MemberFaceType::Left, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
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
      pJoint8->SetX(5.6568542);
      pJoint8->SetY(-5.6568542);

      ASSERT_TRUE(IsEqual(pMember1.GetLength(), 8.0));


      model.ComputeJointDeflections(0, 0, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -2.2857142857143));
      model.ComputeJointDeflections(0, 8, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 2.2857142857143));

      model.ComputeMemberForces(0, 1, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 2.0));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 2.0));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      model.ComputeReactions(0, 0, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 1.41421356));
      ASSERT_TRUE(IsEqual(fy, 1.41421356));
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

      model.ComputePOIDeflections(0, 10, LoadOrientation::GlobalProjected, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -2.2857142857143));
      model.ComputePOIDeflections(0, 15, LoadOrientation::GlobalProjected, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, -2.9631141));
      ASSERT_TRUE(IsEqual(dy, -2.9631141));
      ASSERT_TRUE(IsEqual(rz, -12.0 / 7.0));
      model.ComputePOIDeflections(0, 22, LoadOrientation::GlobalProjected, &dx, &dy, &rz);
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
      model.ComputePOIForces(0, 10, MemberFaceType::Left, LoadOrientation::GlobalProjected, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, -1.41421355));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputePOIForces(0, 10, MemberFaceType::Right, LoadOrientation::GlobalProjected, &fx, &fy, &mz);
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
      model.ComputePOIForces(0, 15, MemberFaceType::Left, LoadOrientation::GlobalProjected, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, -1.41421355));
      ASSERT_TRUE(IsEqual(mz, 4.0));
      model.ComputePOIForces(0, 15, MemberFaceType::Right, LoadOrientation::GlobalProjected, &fx, &fy, &mz);
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
      model.ComputePOIForces(0, 12, MemberFaceType::Left, LoadOrientation::GlobalProjected, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, -1.41421355));
      ASSERT_TRUE(IsEqual(mz, 8.0));
      model.ComputePOIForces(0, 12, MemberFaceType::Right, LoadOrientation::GlobalProjected, &fx, &fy, &mz);
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
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, -1.41421355));
      ASSERT_TRUE(IsEqual(mz, 8.0));
      model.ComputePOIForces(0, 20, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, -1.41421355));
      ASSERT_TRUE(IsEqual(mz, -8.0));
      model.ComputePOIForces(0, 20, MemberFaceType::Left, LoadOrientation::GlobalProjected, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, -1.41421355));
      ASSERT_TRUE(IsEqual(mz, 8.0));
      model.ComputePOIForces(0, 20, MemberFaceType::Right, LoadOrientation::GlobalProjected, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, -1.41421355));
      ASSERT_TRUE(IsEqual(mz, -8.0));
      model.ComputePOIForces(0, 20, MemberFaceType::Left, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
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
      model.ComputePOIForces(0, 25, MemberFaceType::Left, LoadOrientation::GlobalProjected, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, 4.0));
      model.ComputePOIForces(0, 25, MemberFaceType::Right, LoadOrientation::GlobalProjected, &fx, &fy, &mz);
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
