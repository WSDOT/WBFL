///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
///////////////////////////////////////////////////////////////////////
// TestAxialLoads.cpp
//
// Ported from F:\ARP\WBFL\Fem2d\Test\TestAxialLoads.cpp
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

namespace Fem2dUnitTests
{

TEST_CLASS(TestAxialLoads)
{
public:
   TEST_METHOD(AngledFrame_AxialTrapezoidalLoadsOnTwoMembers)
   {
      Fem2dModelFixture fixture;
      CComPtr<IFem2dModel>& pmodel = fixture.Model;

      CComPtr<IFem2dJointCollection> pJoints;
      ASSERT_HR(pmodel->get_Joints(&pJoints));

      CComPtr<IFem2dJoint> pJoint1, pJoint2, pJoint3, pJoint4;
      ASSERT_MC(fixture, pJoints->Create(1, 0.0, 0.0, &pJoint1));
      ASSERT_MC(fixture, pJoints->Create(2, 0.0, 10.0, &pJoint2));
      ASSERT_MC(fixture, pJoints->Create(3, 10.0, 15.0, &pJoint3));
      ASSERT_MC(fixture, pJoints->Create(4, 10.0, 0.0, &pJoint4));

      ASSERT_MC(fixture, pJoint1->Support());
      ASSERT_MC(fixture, pJoint4->Support());

      CComPtr<IFem2dMemberCollection> pMembers;
      ASSERT_HR(pmodel->get_Members(&pMembers));

      Float64 E = 100;
      Float64 A = 100;
      Float64 I = 833.333;
      CComPtr<IFem2dMember> pMember1, pMember2, pMember3;
      ASSERT_MC(fixture, pMembers->Create(1, 1, 2, E * A, E * I, &pMember1));
      ASSERT_MC(fixture, pMembers->Create(2, 2, 3, E * A, E * I, &pMember2));
      ASSERT_MC(fixture, pMembers->Create(3, 3, 4, E * A, E * I, &pMember3));

      CComPtr<IFem2dLoadingCollection> pLoadings;
      ASSERT_HR(pmodel->get_Loadings(&pLoadings));

      // loading 1: load on member 2
      CComPtr<IFem2dLoading> pLoading1;
      ASSERT_LC(fixture, pLoadings->Create(1, &pLoading1));
      CComPtr<IFem2dDistributedLoadCollection> pDistributedLoads1;
      ASSERT_HR(pLoading1->get_DistributedLoads(&pDistributedLoads1));
      CComPtr<IFem2dDistributedLoad> pDistributedLoad1;
      ASSERT_LC(fixture, pDistributedLoads1->Create(1, 2, loadDirFx, -0.2, -0.8, 100.0, 50.0, lotMember, &pDistributedLoad1));

      // loading 2: load on member 1
      CComPtr<IFem2dLoading> pLoading2;
      ASSERT_LC(fixture, pLoadings->Create(2, &pLoading2));
      CComPtr<IFem2dDistributedLoadCollection> pDistributedLoads2;
      ASSERT_HR(pLoading2->get_DistributedLoads(&pDistributedLoads2));
      CComPtr<IFem2dDistributedLoad> pDistributedLoad2;
      ASSERT_LC(fixture, pDistributedLoads2->Create(1, 1, loadDirFx, -0.2, -0.8, 100.0, 50.0, lotMember, &pDistributedLoad2));

      // POI's at internal quarter points on all three members
      CComPtr<IFem2dPOICollection> pPOIs;
      ASSERT_HR(pmodel->get_POIs(&pPOIs));

      CComPtr<IFem2dPOI> pPOI11, pPOI12, pPOI13;
      ASSERT_HR(pPOIs->Create(11, 1, -0.25, &pPOI11));
      ASSERT_HR(pPOIs->Create(12, 1, -0.5, &pPOI12));
      ASSERT_HR(pPOIs->Create(13, 1, -0.75, &pPOI13));

      CComPtr<IFem2dPOI> pPOI21, pPOI22, pPOI23;
      ASSERT_HR(pPOIs->Create(21, 2, -0.25, &pPOI21));
      ASSERT_HR(pPOIs->Create(22, 2, -0.5, &pPOI22));
      ASSERT_HR(pPOIs->Create(23, 2, -0.75, &pPOI23));

      CComPtr<IFem2dPOI> pPOI31, pPOI32, pPOI33;
      ASSERT_HR(pPOIs->Create(31, 3, -0.25, &pPOI31));
      ASSERT_HR(pPOIs->Create(32, 3, -0.5, &pPOI32));
      ASSERT_HR(pPOIs->Create(33, 3, -0.75, &pPOI33));

      CComQIPtr<IFem2dModelResults> presults(pmodel);

      // reactions - loading 1
      Float64 fx, fy, mz;
      ASSERT_HR(presults->ComputeReactions(1, 1, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -292.44212116202));
      ASSERT_TRUE(IsEqual(fy, -313.06901466568));
      ASSERT_TRUE(IsEqual(mz, 2060.6614437544));
      ASSERT_HR(presults->ComputeReactions(1, 4, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -157.55787883798));
      ASSERT_TRUE(IsEqual(fy, 88.069014665680));
      ASSERT_TRUE(IsEqual(mz, 1558.6484095887));

      // reactions - loading 2
      ASSERT_HR(presults->ComputeReactions(2, 1, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 2.7877082281446));
      ASSERT_TRUE(IsEqual(fy, -430.80005048334));
      ASSERT_TRUE(IsEqual(mz, 85.977787618096));
      ASSERT_HR(presults->ComputeReactions(2, 4, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -2.7877082281446));
      ASSERT_TRUE(IsEqual(fy, -19.199949516660));
      ASSERT_TRUE(IsEqual(mz, 106.02170754850));

      // joint deflections - loading 1
      Float64 dx, dy, rz;
      ASSERT_HR(presults->ComputeJointDeflections(1, 2, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.65151288453378));
      ASSERT_TRUE(IsEqual(dy, 0.31306901466568));
      ASSERT_TRUE(IsEqual(rz, -0.071814129278972));
      ASSERT_HR(presults->ComputeJointDeflections(1, 3, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 1.0406600870525));
      ASSERT_TRUE(IsEqual(dy, -0.13210352199852));
      ASSERT_TRUE(IsEqual(rz, -0.067853604436147));

      // joint deflections - loading 2
      ASSERT_HR(presults->ComputeJointDeflections(2, 2, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.057162111891991));
      ASSERT_TRUE(IsEqual(dy, 0.19080005048334));
      ASSERT_TRUE(IsEqual(rz, -0.011989964247044));
      ASSERT_HR(presults->ComputeJointDeflections(2, 3, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.12431232437543));
      ASSERT_TRUE(IsEqual(dy, 0.028799924274989));
      ASSERT_TRUE(IsEqual(rz, -0.015320507378938));

      // POI forces - loading 1
      ASSERT_HR(presults->ComputePOIForces(1, 11, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 313.06901466568));
      ASSERT_TRUE(IsEqual(fy, -292.44212116202));
      ASSERT_TRUE(IsEqual(mz, -1329.5561408494));
      ASSERT_HR(presults->ComputePOIForces(1, 12, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 313.06901466568));
      ASSERT_TRUE(IsEqual(fy, -292.44212116202));
      ASSERT_TRUE(IsEqual(mz, -598.45083794433));
      ASSERT_HR(presults->ComputePOIForces(1, 13, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 313.06901466568));
      ASSERT_TRUE(IsEqual(fy, -292.44212116202));
      ASSERT_TRUE(IsEqual(mz, 132.65446496072));
      ASSERT_HR(presults->ComputePOIForces(1, 21, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 346.83982395006));
      ASSERT_TRUE(IsEqual(fy, 149.23334689603));
      ASSERT_TRUE(IsEqual(mz, 446.63988265411));
      ASSERT_HR(presults->ComputePOIForces(1, 22, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 108.09298260243));
      ASSERT_TRUE(IsEqual(fy, 149.23334689603));
      ASSERT_TRUE(IsEqual(mz, 29.519997442435));
      ASSERT_HR(presults->ComputePOIForces(1, 23, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -72.422921831151));
      ASSERT_TRUE(IsEqual(fy, 149.23334689603));
      ASSERT_TRUE(IsEqual(mz, -387.59988776924));
      ASSERT_HR(presults->ComputePOIForces(1, 32, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -88.069014665680));
      ASSERT_TRUE(IsEqual(fy, -157.55787883798));
      ASSERT_TRUE(IsEqual(mz, 376.96431830392));

      // POI forces - loading 2
      ASSERT_HR(presults->ComputePOIForces(2, 11, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 381.84171715001));
      ASSERT_TRUE(IsEqual(fy, 2.7877082281446));
      ASSERT_TRUE(IsEqual(mz, -92.947058188457));
      ASSERT_HR(presults->ComputePOIForces(2, 12, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 168.30005048334));
      ASSERT_TRUE(IsEqual(fy, 2.7877082281446));
      ASSERT_TRUE(IsEqual(mz, -99.916328758819));
      ASSERT_HR(presults->ComputePOIForces(2, 13, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 6.8417171500071));
      ASSERT_TRUE(IsEqual(fy, 2.7877082281446));
      ASSERT_TRUE(IsEqual(mz, -106.88559932918));
      ASSERT_HR(presults->ComputePOIForces(2, 21, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -11.079880496590));
      ASSERT_TRUE(IsEqual(fy, -15.926255893613));
      ASSERT_TRUE(IsEqual(mz, -69.339631393074));
      ASSERT_HR(presults->ComputePOIForces(2, 22, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -11.079880496590));
      ASSERT_TRUE(IsEqual(fy, -15.926255893613));
      ASSERT_TRUE(IsEqual(mz, -24.824392886605));
      ASSERT_HR(presults->ComputePOIForces(2, 23, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -11.079880496590));
      ASSERT_TRUE(IsEqual(fy, -15.926255893613));
      ASSERT_TRUE(IsEqual(mz, 19.690845619863));
      ASSERT_HR(presults->ComputePOIForces(2, 32, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 19.199949516660));
      ASSERT_TRUE(IsEqual(fy, -2.7877082281446));
      ASSERT_TRUE(IsEqual(mz, 85.113895837416));
   }
};
} // namespace Fem2dUnitTests
