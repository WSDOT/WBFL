///////////////////////////////////////////////////////////////////////
// FEA2D - Two-dimensional Finite Element Analysis Engine
// Copyright � 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
///////////////////////////////////////////////////////////////////////
// TestAxialLoads.cpp
//
// Ported from Fem2d\Fem2dUnitTests\TestAxialLoads.cpp
//
//              w
//         ============ 3
//                    /o
//                  /  |
//                /    |
//              /      |
//            /        |
//          /          |
//        2o           |
//         |           |
//         |           |
//         |           |
//         |           |
//        1o           o4
//        ===         ===
//
// Frame with axial (member-length-direction) trapezoidal loads, made up and
// verified using DrFrame.
#include "pch.h"

namespace FEA2DUnitTests
{

TEST_CLASS(TestAxialLoads)
{
public:
   TEST_METHOD(AngledFrame_AxialTrapezoidalLoadsOnTwoMembers)
   {
      Model model;
      model.CreateJoint(1, 0.0, 0.0);
      model.CreateJoint(2, 0.0, 10.0);
      model.CreateJoint(3, 10.0, 15.0);
      model.CreateJoint(4, 10.0, 0.0);

      model.FindJoint(1)->Support();
      model.FindJoint(4)->Support();

      Float64 E = 100;
      Float64 A = 100;
      Float64 I = 833.333;
      model.CreateMember(1, 1, 2, E * A, E * I);
      model.CreateMember(2, 2, 3, E * A, E * I);
      model.CreateMember(3, 3, 4, E * A, E * I);

      // loading 1: load on member 2
      Loading& pLoading1 = model.CreateLoading(1);
      pLoading1.CreateDistributedLoad(1, 2, LoadDirection::Fx, -0.2, -0.8, 100.0, 50.0, LoadOrientation::Member);

      // loading 2: load on member 1
      Loading& pLoading2 = model.CreateLoading(2);
      pLoading2.CreateDistributedLoad(1, 1, LoadDirection::Fx, -0.2, -0.8, 100.0, 50.0, LoadOrientation::Member);

      // POI's at internal quarter points on all three members
      model.CreatePOI(11, 1, -0.25);
      model.CreatePOI(12, 1, -0.5);
      model.CreatePOI(13, 1, -0.75);

      model.CreatePOI(21, 2, -0.25);
      model.CreatePOI(22, 2, -0.5);
      model.CreatePOI(23, 2, -0.75);

      model.CreatePOI(31, 3, -0.25);
      model.CreatePOI(32, 3, -0.5);
      model.CreatePOI(33, 3, -0.75);


      // reactions - loading 1
      Float64 fx, fy, mz;
      model.ComputeReactions(1, 1, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -292.44212116202));
      ASSERT_TRUE(IsEqual(fy, -313.06901466568));
      ASSERT_TRUE(IsEqual(mz, 2060.6614437544));
      model.ComputeReactions(1, 4, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -157.55787883798));
      ASSERT_TRUE(IsEqual(fy, 88.069014665680));
      ASSERT_TRUE(IsEqual(mz, 1558.6484095887));

      // reactions - loading 2
      model.ComputeReactions(2, 1, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 2.7877082281446));
      ASSERT_TRUE(IsEqual(fy, -430.80005048334));
      ASSERT_TRUE(IsEqual(mz, 85.977787618096));
      model.ComputeReactions(2, 4, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -2.7877082281446));
      ASSERT_TRUE(IsEqual(fy, -19.199949516660));
      ASSERT_TRUE(IsEqual(mz, 106.02170754850));

      // joint deflections - loading 1
      Float64 dx, dy, rz;
      model.ComputeJointDeflections(1, 2, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.65151288453378));
      ASSERT_TRUE(IsEqual(dy, 0.31306901466568));
      ASSERT_TRUE(IsEqual(rz, -0.071814129278972));
      model.ComputeJointDeflections(1, 3, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 1.0406600870525));
      ASSERT_TRUE(IsEqual(dy, -0.13210352199852));
      ASSERT_TRUE(IsEqual(rz, -0.067853604436147));

      // joint deflections - loading 2
      model.ComputeJointDeflections(2, 2, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.057162111891991));
      ASSERT_TRUE(IsEqual(dy, 0.19080005048334));
      ASSERT_TRUE(IsEqual(rz, -0.011989964247044));
      model.ComputeJointDeflections(2, 3, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.12431232437543));
      ASSERT_TRUE(IsEqual(dy, 0.028799924274989));
      ASSERT_TRUE(IsEqual(rz, -0.015320507378938));

      // POI forces - loading 1
      model.ComputePOIForces(1, 11, MemberFaceType::Left, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 313.06901466568));
      ASSERT_TRUE(IsEqual(fy, -292.44212116202));
      ASSERT_TRUE(IsEqual(mz, -1329.5561408494));
      model.ComputePOIForces(1, 12, MemberFaceType::Left, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 313.06901466568));
      ASSERT_TRUE(IsEqual(fy, -292.44212116202));
      ASSERT_TRUE(IsEqual(mz, -598.45083794433));
      model.ComputePOIForces(1, 13, MemberFaceType::Left, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 313.06901466568));
      ASSERT_TRUE(IsEqual(fy, -292.44212116202));
      ASSERT_TRUE(IsEqual(mz, 132.65446496072));
      model.ComputePOIForces(1, 21, MemberFaceType::Left, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 346.83982395006));
      ASSERT_TRUE(IsEqual(fy, 149.23334689603));
      ASSERT_TRUE(IsEqual(mz, 446.63988265411));
      model.ComputePOIForces(1, 22, MemberFaceType::Left, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 108.09298260243));
      ASSERT_TRUE(IsEqual(fy, 149.23334689603));
      ASSERT_TRUE(IsEqual(mz, 29.519997442435));
      model.ComputePOIForces(1, 23, MemberFaceType::Left, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -72.422921831151));
      ASSERT_TRUE(IsEqual(fy, 149.23334689603));
      ASSERT_TRUE(IsEqual(mz, -387.59988776924));
      model.ComputePOIForces(1, 32, MemberFaceType::Left, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -88.069014665680));
      ASSERT_TRUE(IsEqual(fy, -157.55787883798));
      ASSERT_TRUE(IsEqual(mz, 376.96431830392));

      // POI forces - loading 2
      model.ComputePOIForces(2, 11, MemberFaceType::Left, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 381.84171715001));
      ASSERT_TRUE(IsEqual(fy, 2.7877082281446));
      ASSERT_TRUE(IsEqual(mz, -92.947058188457));
      model.ComputePOIForces(2, 12, MemberFaceType::Left, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 168.30005048334));
      ASSERT_TRUE(IsEqual(fy, 2.7877082281446));
      ASSERT_TRUE(IsEqual(mz, -99.916328758819));
      model.ComputePOIForces(2, 13, MemberFaceType::Left, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 6.8417171500071));
      ASSERT_TRUE(IsEqual(fy, 2.7877082281446));
      ASSERT_TRUE(IsEqual(mz, -106.88559932918));
      model.ComputePOIForces(2, 21, MemberFaceType::Left, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -11.079880496590));
      ASSERT_TRUE(IsEqual(fy, -15.926255893613));
      ASSERT_TRUE(IsEqual(mz, -69.339631393074));
      model.ComputePOIForces(2, 22, MemberFaceType::Left, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -11.079880496590));
      ASSERT_TRUE(IsEqual(fy, -15.926255893613));
      ASSERT_TRUE(IsEqual(mz, -24.824392886605));
      model.ComputePOIForces(2, 23, MemberFaceType::Left, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -11.079880496590));
      ASSERT_TRUE(IsEqual(fy, -15.926255893613));
      ASSERT_TRUE(IsEqual(mz, 19.690845619863));
      model.ComputePOIForces(2, 32, MemberFaceType::Left, LoadOrientation::Member, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 19.199949516660));
      ASSERT_TRUE(IsEqual(fy, -2.7877082281446));
      ASSERT_TRUE(IsEqual(mz, 85.113895837416));
   }
};
} // namespace FEA2DUnitTests
