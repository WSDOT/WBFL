///////////////////////////////////////////////////////////////////////
// FEA2D - Two-dimensional Finite Element Analysis Engine
// Copyright � 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
///////////////////////////////////////////////////////////////////////
// TestBarWithDistributedLoad.cpp
//
// Ported from Fem2d\Fem2dUnitTests\TestBarWithDistributedLoad.cpp
#include "pch.h"

namespace FEA2DUnitTests
{

TEST_CLASS(TestBarWithDistributedLoad)
{
public:
   TEST_METHOD(AxialTrapezoidalLoad_CantileverThenFixFix)
   {
      /*////////////////////////////////////////////////////
                           ---------->
                        ------------->
                 ]    --------------->
                 ]=============================
                 ]
             L = 8
             EA = 3.0
             EI = 7.0
             a = 2.5
             b = 5.0
             Wa = 2
             Wb = -4
      *////////////////////////////////////////////////////
      Model model;
      model.CreateJoint(0, 0.0, 0.0);
      Joint& pJoint8 = model.CreateJoint(8, 8.0, 0.0);

      model.FindJoint(0)->Support();

      model.CreateMember(1, 0, 8, 3.0, 7.0);

      Loading& pLoading = model.CreateLoading(0);
      pLoading.CreateDistributedLoad(0, 1, LoadDirection::Fx, 2.5, 5.0, 2.0, 4.0, LoadOrientation::Member);

      model.CreatePOI(10, 1, 0.0);
      model.CreatePOI(15, 1, -.25);
      model.CreatePOI(12, 1, -0.5);


      Float64 dx, dy, rz;
      model.ComputeJointDeflections(0, 0, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputeJointDeflections(0, 8, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 9.7222222));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      Float64 sfx, sfy, smz, efx, efy, emz;
      model.ComputeMemberForces(0, 1, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, -7.5));
      ASSERT_TRUE(IsEqual(sfy, 0.0));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 0.0));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      Float64 fx, fy, mz;
      model.ComputeReactions(0, 0, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -7.5));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputeReactions(0, 8, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      Float64 sdx, sdy, srz, edx, edy, erz;
      model.ComputeMemberDeflections(0, 1, &sdx, &sdy, &srz, &edx, &edy, &erz);
      ASSERT_TRUE(IsEqual(sdx, 0.0));
      ASSERT_TRUE(IsEqual(sdy, 0.0));
      ASSERT_TRUE(IsEqual(srz, 0.0));
      ASSERT_TRUE(IsEqual(edx, 9.7222222));
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
      ASSERT_TRUE(IsEqual(dx, 5.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputePOIDeflections(0, 12, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 9.1));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputePOIDeflections(0, 20, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 9.1));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputePOIDeflections(0, 25, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 9.7222222));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputePOIDeflections(0, 22, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 9.7222222));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      model.ComputePOIForces(0, 10, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 7.5));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputePOIForces(0, 10, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -7.5));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      model.ComputePOIForces(0, 15, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 7.5));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputePOIForces(0, 15, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -7.5));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      model.ComputePOIForces(0, 12, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 3.6));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputePOIForces(0, 12, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -3.6));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      model.ComputePOIForces(0, 20, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 3.6));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputePOIForces(0, 20, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -3.6));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      model.ComputePOIForces(0, 25, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputePOIForces(0, 25, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      model.ComputePOIForces(0, 22, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputePOIForces(0, 22, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      ///////////////////////////////////////////////
      // try a fix-fix orientation
      pJoint8.Support();


      model.ComputeJointDeflections(0, 0, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputeJointDeflections(0, 8, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      model.ComputeMemberForces(0, 1, LoadOrientation::Member, &sfx, &sfy, &smz, &efx, &efy, &emz);
      ASSERT_TRUE(IsEqual(sfx, -3.85416667));
      ASSERT_TRUE(IsEqual(sfy, 0.0));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, -3.645833333));
      ASSERT_TRUE(IsEqual(efy, 0.0));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      model.ComputeReactions(0, 0, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -3.85416667));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputeReactions(0, 8, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -3.645833333));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      model.ComputeMemberDeflections(0, 1, &sdx, &sdy, &srz, &edx, &edy, &erz);
      ASSERT_TRUE(IsEqual(sdx, 0.0));
      ASSERT_TRUE(IsEqual(sdy, 0.0));
      ASSERT_TRUE(IsEqual(srz, 0.0));
      ASSERT_TRUE(IsEqual(edx, 0.0));
      ASSERT_TRUE(IsEqual(edy, 0.0));
      ASSERT_TRUE(IsEqual(erz, 0.0));

      model.ComputePOIDeflections(0, 10, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputePOIDeflections(0, 15, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 2.56944444));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputePOIDeflections(0, 12, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 4.238888889));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputePOIDeflections(0, 20, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 4.238888889));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputePOIDeflections(0, 25, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 2.430555556));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      model.ComputePOIDeflections(0, 22, LoadOrientation::Member, &dx, &dy, &rz);
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      model.ComputePOIForces(0, 10, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 3.85416667));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputePOIForces(0, 10, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -3.85416667));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      model.ComputePOIForces(0, 15, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 3.85416667));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputePOIForces(0, 15, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -3.85416667));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      model.ComputePOIForces(0, 12, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -0.04583333));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputePOIForces(0, 12, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.04583333));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      model.ComputePOIForces(0, 20, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -0.04583333));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputePOIForces(0, 20, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 0.04583333));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      model.ComputePOIForces(0, 25, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -3.6458333333333));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputePOIForces(0, 25, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 3.6458333333333));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      model.ComputePOIForces(0, 22, MemberFaceType::Left, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, -3.6458333333333));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      model.ComputePOIForces(0, 22, MemberFaceType::Right, LoadOrientation::Global, &fx, &fy, &mz);
      ASSERT_TRUE(IsEqual(fx, 3.6458333333333));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
   }
};
} // namespace FEA2DUnitTests
