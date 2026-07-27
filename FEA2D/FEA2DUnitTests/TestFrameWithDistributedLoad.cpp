///////////////////////////////////////////////////////////////////////
// FEA2D - Two-dimensional Finite Element Analysis Engine
// Copyright � 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
///////////////////////////////////////////////////////////////////////
// TestFrameWithDistributedLoad.cpp
//
// Ported from Fem2d\Fem2dUnitTests\TestFrameWithDistributedLoad.cpp
//
//              w
//         ============ 3
//                    /o
//                  /  |
//                /    |
//              /      |
//            /        |
//          /          |
//        2o-----------o4
//         |           |
//         |           |
//         |           |
//         |           |
//        1o           o5
//        ===         ===
//
// Frame with trapezoidal load, made up and verified using DrFrame.
#include "pch.h"

namespace FEA2DUnitTests
{

TEST_CLASS(TestFrameWithDistributedLoad)
{
public:
   TEST_METHOD(SlopedFrame_TrapezoidalLoad_OrientationVariants)
   {
      Model model;
      model.CreateJoint(1, 0.0, 0.0);
      model.CreateJoint(2, 0.0, 144.0);
      model.CreateJoint(3, 144.0, 288.0);
      model.CreateJoint(4, 144.0, 144.0);
      model.CreateJoint(5, 144.0, 0.0);

      Joint* pJoint1 = model.FindJoint(1);

      Joint* pJoint5 = model.FindJoint(5);

      pJoint1->Support();
      pJoint5->Support();
      pJoint1->ReleaseDof(JointReleaseType::Mz);
      pJoint5->ReleaseDof(JointReleaseType::Mz);

      Float64 E = 29000;
      Float64 A = 10;
      Float64 I = 250;
      model.CreateMember(1, 1, 2, E * A, E * I);
      model.CreateMember(2, 2, 3, E * A, E * I);
      model.CreateMember(3, 3, 4, E * A, E * I);
      model.CreateMember(4, 2, 4, E * A, E * I);
      model.CreateMember(5, 4, 5, E * A, E * I);

      Loading& pLoading0 = model.CreateLoading(0);
      DistributedLoad& pDistributedLoad = pLoading0.CreateDistributedLoad(1, 2, LoadDirection::Fy, 0.0, -1.0, -0.5, -1.0, LoadOrientation::Member);
      pDistributedLoad.SetOrientation(LoadOrientation::Global); // apply in global coords

      model.CreatePOI(22, 2, -0.5);


      Float64 dx, dy, rz;
      model.ComputeJointDeflections(0, 1, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      model.ComputeJointDeflections(0, 2, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.47518504376467));
      ASSERT_TRUE(IsEqual(dy, -0.033707048769389));
      model.ComputeJointDeflections(0, 3, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.50069452024221));
      ASSERT_TRUE(IsEqual(dy, -0.077478110675579));
      model.ComputeJointDeflections(0, 4, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.48025051552884));
      ASSERT_TRUE(IsEqual(dy, -0.042133810961736));

      Float64 sfx, sfy, smz, efx, efy, emz;
      model.ComputeMemberForces(0, 1, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 67.882250993909));
      ASSERT_TRUE(IsEqual(sfy, -2.1305089245136));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, -67.882250993909));
      ASSERT_TRUE(IsEqual(efy, 2.1305089245136));
      ASSERT_TRUE(IsEqual(emz, -306.79328512995));
      model.ComputeMemberForces(0, 2, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 66.388401994131));
      ASSERT_TRUE(IsEqual(sfy, 48.948594378857));
      ASSERT_TRUE(IsEqual(smz, 1494.0302142683));
      ASSERT_TRUE(IsEqual(efx, 41.611598005869));
      ASSERT_TRUE(IsEqual(efy, 59.051405621143));
      ASSERT_TRUE(IsEqual(emz, -1300.8520491173));
      model.ComputeMemberForces(0, 3, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 71.179492479266));
      ASSERT_TRUE(IsEqual(sfy, 12.331806227349));
      ASSERT_TRUE(IsEqual(smz, 1300.8520491173));
      ASSERT_TRUE(IsEqual(efx, -71.179492479266));
      ASSERT_TRUE(IsEqual(efy, -12.331806227349));
      ASSERT_TRUE(IsEqual(emz, 474.92804762087));

      Float64 fx, fy, mz;
      model.ComputeReactions(0, 1, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 2.1305089245136));
      ASSERT_TRUE(IsEqual(fy, 67.882250993909));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputeReactions(0, 5, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -2.1305089245135));
      ASSERT_TRUE(IsEqual(fy, 84.852813742386));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      model.ComputePOIDeflections(0, 22, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.29623553109350)); // close, but not exact to drframe
      ASSERT_TRUE(IsEqual(dy, -1.0232793921774));
      model.ComputePOIDeflections(0, 22, LoadOrientation::Global, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.93303795012174));
      ASSERT_TRUE(IsEqual(dy, -0.51409764439251));

      model.ComputePOIForces(0, 22, MemberFaceType::Left, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -21.388401994131));
      ASSERT_TRUE(IsEqual(fy, -3.9485943788572));
      ASSERT_TRUE(IsEqual(mz, 1351.7900335605));

      // add a new loading with a horizontally applied load
      Loading& pLoading1 = model.CreateLoading(1);
      DistributedLoad& pDistributedLoad1 = pLoading1.CreateDistributedLoad(1, 2, LoadDirection::Fx, 0.0, -1.0, -0.5, -1.0, LoadOrientation::Member);
      pDistributedLoad1.SetOrientation(LoadOrientation::Global); // apply in global coords


      model.ComputeReactions(1, 1, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 73.282046829267));
      ASSERT_TRUE(IsEqual(fy, 237.58787847868));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputeReactions(1, 5, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 79.453017907024));
      ASSERT_TRUE(IsEqual(fy, -237.58787847868));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      model.ComputeMemberForces(1, 2, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 196.34212817867));
      ASSERT_TRUE(IsEqual(sfy, -33.642294746207));
      ASSERT_TRUE(IsEqual(smz, 1417.8934017460));
      ASSERT_TRUE(IsEqual(efx, -88.342128178674));
      ASSERT_TRUE(IsEqual(efy, -74.357705253793));
      ASSERT_TRUE(IsEqual(emz, 1506.0066534574));

      model.ComputePOIForces(1, 22, MemberFaceType::Left, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -151.34212817867));
      ASSERT_TRUE(IsEqual(fy, -11.357705253793));
      ASSERT_TRUE(IsEqual(mz, -2705.1745393975));

      // next try global projected load in Y
      Loading& pLoading2 = model.CreateLoading(2);
      DistributedLoad& pDistributedLoad2 = pLoading2.CreateDistributedLoad(1, 2, LoadDirection::Fy, 0.0, -1.0, -0.5, -1.0, LoadOrientation::Member);
      pDistributedLoad2.SetOrientation(LoadOrientation::GlobalProjected); // apply in global coords


      model.ComputeReactions(2, 1, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 1.5064973079020));
      ASSERT_TRUE(IsEqual(fy, 48.000000000000));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputeReactions(2, 5, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -1.5064973079019));
      ASSERT_TRUE(IsEqual(fy, 60.000000000000));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      model.ComputeMemberForces(2, 2, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 46.943689242188));
      ASSERT_TRUE(IsEqual(sfy, 34.611883014840));
      ASSERT_TRUE(IsEqual(smz, 1056.4388958067));
      ASSERT_TRUE(IsEqual(efx, 29.423843125959));
      ASSERT_TRUE(IsEqual(efy, 41.755649353307));
      ASSERT_TRUE(IsEqual(emz, -919.84130525128));

      model.ComputePOIForces(2, 22, MemberFaceType::Left, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -15.123884088794));
      ASSERT_TRUE(IsEqual(fy, -2.7920778614451));
      ASSERT_TRUE(IsEqual(mz, 955.85989947101));

      // next try global projected load in X
      Loading& pLoading3 = model.CreateLoading(3);
      DistributedLoad& pDistributedLoad3 = pLoading3.CreateDistributedLoad(1, 2, LoadDirection::Fx, 0.0, -1.0, -0.5, -1.0, LoadOrientation::Member);
      pDistributedLoad3.SetOrientation(LoadOrientation::GlobalProjected); // apply in global coords


      model.ComputeReactions(3, 1, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 51.818232252205));
      ASSERT_TRUE(IsEqual(fy, 168.00000000000));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputeReactions(3, 5, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 56.181767747793));
      ASSERT_TRUE(IsEqual(fy, -168.00000000000));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      model.ComputeMemberForces(3, 2, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, 138.83485026774));
      ASSERT_TRUE(IsEqual(sfy, -23.788694749719));
      ASSERT_TRUE(IsEqual(smz, 1002.6020393742));
      ASSERT_TRUE(IsEqual(efx, -62.467317899593));
      ASSERT_TRUE(IsEqual(efy, -52.578837618428));
      ASSERT_TRUE(IsEqual(emz, 1064.9075171718));

      model.ComputePOIForces(3, 22, MemberFaceType::Left, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -107.01504511435));
      ASSERT_TRUE(IsEqual(fy, -8.0311104036752));
      ASSERT_TRUE(IsEqual(mz, -1912.8472611011));
   }
};
} // namespace FEA2DUnitTests
