///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
///////////////////////////////////////////////////////////////////////
// TestSimpleBeamWithPointLoad2.cpp
//
// Ported from F:\ARP\WBFL\Fem2d\Test\TestSimpleBeamWithPointLoad2.cpp
#include "pch.h"

namespace Fem2dUnitTests
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
      Fem2dModelFixture fixture;
      CComPtr<IFem2dModel>& pmodel = fixture.Model;

      CComPtr<IFem2dJointCollection> pJoints;
      ASSERT_HR(pmodel->get_Joints(&pJoints));

      CComPtr<IFem2dJoint> pJoint0, pJoint8;
      ASSERT_MC(fixture, pJoints->Create(0, 0.0, 0.0, &pJoint0));
      ASSERT_MC(fixture, pJoints->Create(8, 8.0, 0.0, &pJoint8));

      ASSERT_MC(fixture, pJoint0->Support());
      ASSERT_MC(fixture, pJoint8->Support());

      CComPtr<IFem2dMemberCollection> pMembers;
      ASSERT_HR(pmodel->get_Members(&pMembers));

      CComPtr<IFem2dMember> pMember1;
      ASSERT_MC(fixture, pMembers->Create(1, 0, 8, 3.0, 7.0, &pMember1));

      CComPtr<IFem2dLoadingCollection> pLoadings;
      ASSERT_HR(pmodel->get_Loadings(&pLoadings));
      CComPtr<IFem2dLoading> pLoading;
      ASSERT_LC(fixture, pLoadings->Create(0, &pLoading));
      CComPtr<IFem2dPointLoadCollection> pPointLoads;
      ASSERT_HR(pLoading->get_PointLoads(&pPointLoads));
      CComPtr<IFem2dPointLoad> pPointLoad;
      ASSERT_LC(fixture, pPointLoads->Create(0, 1, 4.0, 0.0, -4.0, 0.0, lotMember, &pPointLoad));

      // second loading using a point moment
      CComPtr<IFem2dLoading> pLoading2;
      ASSERT_LC(fixture, pLoadings->Create(2, &pLoading2));
      CComPtr<IFem2dPointLoadCollection> pPointLoads2;
      ASSERT_HR(pLoading2->get_PointLoads(&pPointLoads2));
      CComPtr<IFem2dPointLoad> pPointLoad2;
      ASSERT_LC(fixture, pPointLoads2->Create(0, 1, 4.0, 0.0, 0.0, 3.0, lotMember, &pPointLoad2));

      // POI's at 1/4 points in member 1 - pre-calculated
      CComPtr<IFem2dPOICollection> pPOIs;
      ASSERT_HR(pmodel->get_POIs(&pPOIs));

      CComPtr<IFem2dPOI> pPOI10, pPOI15, pPOI12;
      ASSERT_HR(pPOIs->Create(10, 1, 0.0, &pPOI10));
      ASSERT_HR(pPOIs->Create(15, 1, -.25, &pPOI15));
      ASSERT_HR(pPOIs->Create(12, 1, -0.5, &pPOI12));

      CComQIPtr<IFem2dModelResults> presults(pmodel);

      Float64 dx, dy, rz;
      ASSERT_HR(presults->ComputeJointDeflections(0, 0, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputeJointDeflections(0, 8, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      ASSERT_HR(presults->ComputeJointDeflections(2, 0, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputeJointDeflections(2, 8, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      Float64 sfx, sfy, smz, efx, efy, emz;
      ASSERT_HR(presults->ComputeMemberForces(0, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 2.0));
      ASSERT_TRUE(IsEqual(smz, 4.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 2.0));
      ASSERT_TRUE(IsEqual(emz, -4.0));

      ASSERT_HR(presults->ComputeMemberForces(2, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 0.5625));
      ASSERT_TRUE(IsEqual(smz, 0.75));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, -0.5625));
      ASSERT_TRUE(IsEqual(emz, 0.75));

      Float64 fx, fy, mz;
      ASSERT_HR(presults->ComputeReactions(0, 0, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, 4.0));
      ASSERT_HR(presults->ComputeReactions(0, 8, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, -4.0));

      ASSERT_HR(presults->ComputeReactions(2, 0, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.5625));
      ASSERT_TRUE(IsEqual(mz, 0.75));
      ASSERT_HR(presults->ComputeReactions(2, 8, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -0.5625));
      ASSERT_TRUE(IsEqual(mz, 0.75));

      Float64 sdx, sdy, srz, edx, edy, erz;
      ASSERT_HR(presults->ComputeMemberDeflections(0, 1, &sdx, &sdy, &srz, &edx, &edy, &erz));
      ASSERT_TRUE(IsEqual(sdx, 0.0));
      ASSERT_TRUE(IsEqual(sdy, 0.0));
      ASSERT_TRUE(IsEqual(srz, 0.0));
      ASSERT_TRUE(IsEqual(edx, 0.0));
      ASSERT_TRUE(IsEqual(edy, 0.0));
      ASSERT_TRUE(IsEqual(erz, 0.0));

      ASSERT_HR(presults->ComputeMemberDeflections(2, 1, &sdx, &sdy, &srz, &edx, &edy, &erz));
      ASSERT_TRUE(IsEqual(sdx, 0.0));
      ASSERT_TRUE(IsEqual(sdy, 0.0));
      ASSERT_TRUE(IsEqual(srz, 0.0));
      ASSERT_TRUE(IsEqual(edx, 0.0));
      ASSERT_TRUE(IsEqual(edy, 0.0));
      ASSERT_TRUE(IsEqual(erz, 0.0));

      // POI's at 1/4 points of second half - calculated on the fly
      CComPtr<IFem2dPOI> pPOI20, pPOI25, pPOI22;
      ASSERT_HR(pPOIs->Create(20, 1, 4.0, &pPOI20));
      ASSERT_HR(pPOIs->Create(25, 1, 6.0, &pPOI25));
      ASSERT_HR(pPOIs->Create(22, 1, 8.0, &pPOI22));

      ASSERT_HR(presults->ComputePOIDeflections(0, 10, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(0, 15, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -0.76190476190476));
      ASSERT_TRUE(IsEqual(rz, -0.57142857142857));
      ASSERT_HR(presults->ComputePOIDeflections(0, 12, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -1.5238095238095));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(0, 20, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -1.5238095238095));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(0, 25, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -0.76190476190476));
      ASSERT_TRUE(IsEqual(rz, 0.57142857142857));
      ASSERT_HR(presults->ComputePOIDeflections(0, 22, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      ASSERT_HR(presults->ComputePOIDeflections(2, 10, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(2, 15, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -0.10714285714286));
      ASSERT_TRUE(IsEqual(rz, -0.053571428571429));
      ASSERT_HR(presults->ComputePOIDeflections(2, 12, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.21428571428571));
      ASSERT_HR(presults->ComputePOIDeflections(2, 20, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.21428571428571));
      ASSERT_HR(presults->ComputePOIDeflections(2, 25, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.10714285714286));
      ASSERT_TRUE(IsEqual(rz, -0.053571428571429));
      ASSERT_HR(presults->ComputePOIDeflections(2, 22, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      ASSERT_HR(presults->ComputePOIForces(0, 10, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, -4.0));
      ASSERT_HR(presults->ComputePOIForces(0, 10, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, 4.0));

      ASSERT_HR(presults->ComputePOIForces(0, 15, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(0, 15, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      ASSERT_HR(presults->ComputePOIForces(0, 12, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, 4.0));
      ASSERT_HR(presults->ComputePOIForces(0, 12, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, -4.0));

      ASSERT_HR(presults->ComputePOIForces(0, 20, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, 4.0));
      ASSERT_HR(presults->ComputePOIForces(0, 20, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, -4.0));

      ASSERT_HR(presults->ComputePOIForces(0, 25, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(0, 25, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      ASSERT_HR(presults->ComputePOIForces(0, 22, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, -4.0));
      ASSERT_HR(presults->ComputePOIForces(0, 22, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, 4.0));

      ASSERT_HR(presults->ComputePOIForces(2, 10, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -0.5625));
      ASSERT_TRUE(IsEqual(mz, -0.75));
      ASSERT_HR(presults->ComputePOIForces(2, 10, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.5625));
      ASSERT_TRUE(IsEqual(mz, 0.75));

      ASSERT_HR(presults->ComputePOIForces(2, 15, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -0.5625));
      ASSERT_TRUE(IsEqual(mz, 0.375));
      ASSERT_HR(presults->ComputePOIForces(2, 15, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.5625));
      ASSERT_TRUE(IsEqual(mz, -0.375));

      ASSERT_HR(presults->ComputePOIForces(2, 12, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -0.5625));
      ASSERT_TRUE(IsEqual(mz, 1.5));
      ASSERT_HR(presults->ComputePOIForces(2, 12, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.5625));
      ASSERT_TRUE(IsEqual(mz, 1.5));

      ASSERT_HR(presults->ComputePOIForces(2, 20, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -0.5625));
      ASSERT_TRUE(IsEqual(mz, 1.5));
      ASSERT_HR(presults->ComputePOIForces(2, 20, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.5625));
      ASSERT_TRUE(IsEqual(mz, 1.5));

      ASSERT_HR(presults->ComputePOIForces(2, 25, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -0.5625));
      ASSERT_TRUE(IsEqual(mz, -0.375));
      ASSERT_HR(presults->ComputePOIForces(2, 25, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.5625));
      ASSERT_TRUE(IsEqual(mz, 0.375));

      ASSERT_HR(presults->ComputePOIForces(2, 22, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -0.5625));
      ASSERT_TRUE(IsEqual(mz, 0.75));
      ASSERT_HR(presults->ComputePOIForces(2, 22, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.5625));
      ASSERT_TRUE(IsEqual(mz, -0.75));

      ///////////////////////////////////////////////
      // try a pin-fix orientation
      ASSERT_MC(fixture, pMember1->ReleaseEnd(metStart, mbrReleaseMz));

      ASSERT_HR(presults->ComputeJointDeflections(0, 0, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputeJointDeflections(0, 8, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      ASSERT_HR(presults->ComputeJointDeflections(2, 0, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputeJointDeflections(2, 8, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      ASSERT_HR(presults->ComputeMemberForces(0, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 1.25));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 2.75));
      ASSERT_TRUE(IsEqual(emz, -6.0));

      ASSERT_HR(presults->ComputeMemberForces(2, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 0.42187500000000));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, -0.42187500000000));
      ASSERT_TRUE(IsEqual(emz, 0.37500000000000));

      ASSERT_HR(presults->ComputeReactions(0, 0, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 1.25));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputeReactions(0, 8, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.75));
      ASSERT_TRUE(IsEqual(mz, -6.0));

      ASSERT_HR(presults->ComputeReactions(2, 0, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.421875));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputeReactions(2, 8, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -0.421875));
      ASSERT_TRUE(IsEqual(mz, 0.375));

      ASSERT_HR(presults->ComputeMemberDeflections(0, 1, &sdx, &sdy, &srz, &edx, &edy, &erz));
      ASSERT_TRUE(IsEqual(sdx, 0.0));
      ASSERT_TRUE(IsEqual(sdy, 0.0));
      ASSERT_TRUE(IsEqual(srz, -1.1428571428571));
      ASSERT_TRUE(IsEqual(edx, 0.0));
      ASSERT_TRUE(IsEqual(edy, 0.0));
      ASSERT_TRUE(IsEqual(erz, 0.0));

      ASSERT_HR(presults->ComputeMemberDeflections(2, 1, &sdx, &sdy, &srz, &edx, &edy, &erz));
      ASSERT_TRUE(IsEqual(sdx, 0.0));
      ASSERT_TRUE(IsEqual(sdy, 0.0));
      ASSERT_TRUE(IsEqual(srz, -0.21428571428571));
      ASSERT_TRUE(IsEqual(edx, 0.0));
      ASSERT_TRUE(IsEqual(edy, 0.0));
      ASSERT_TRUE(IsEqual(erz, 0.0));

      ASSERT_HR(presults->ComputePOIDeflections(0, 10, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -1.1428571428571));
      ASSERT_HR(presults->ComputePOIDeflections(0, 15, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -2.047619047));
      ASSERT_TRUE(IsEqual(rz, -0.785714285));
      ASSERT_HR(presults->ComputePOIDeflections(0, 12, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -2.66667));
      ASSERT_TRUE(IsEqual(rz, 0.2857142857));
      ASSERT_HR(presults->ComputePOIDeflections(0, 20, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -2.66667));
      ASSERT_TRUE(IsEqual(rz, 0.2857142857));
      ASSERT_HR(presults->ComputePOIDeflections(0, 25, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -1.1904761904762));
      ASSERT_TRUE(IsEqual(rz, 0.92857142857143));
      ASSERT_HR(presults->ComputePOIDeflections(0, 22, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      ASSERT_HR(presults->ComputePOIDeflections(2, 10, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -0.21428571428571));
      ASSERT_HR(presults->ComputePOIDeflections(2, 15, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -0.34821428571429));
      ASSERT_TRUE(IsEqual(rz, -0.093750000000000));
      ASSERT_HR(presults->ComputePOIDeflections(2, 12, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -0.21428571428571));
      ASSERT_TRUE(IsEqual(rz, 0.26785714285714));
      ASSERT_HR(presults->ComputePOIDeflections(2, 20, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -0.21428571428571));
      ASSERT_TRUE(IsEqual(rz, 0.26785714285714));
      ASSERT_HR(presults->ComputePOIDeflections(2, 25, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.026785714285714));
      ASSERT_TRUE(IsEqual(rz, 0.013392857142857));
      ASSERT_HR(presults->ComputePOIDeflections(2, 22, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      ASSERT_HR(presults->ComputePOIForces(0, 10, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -1.25));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(0, 10, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 1.25));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      ASSERT_HR(presults->ComputePOIForces(0, 15, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -1.25));
      ASSERT_TRUE(IsEqual(mz, 2.5));
      ASSERT_HR(presults->ComputePOIForces(0, 15, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 1.25));
      ASSERT_TRUE(IsEqual(mz, -2.5));

      ASSERT_HR(presults->ComputePOIForces(0, 12, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -1.25));
      ASSERT_TRUE(IsEqual(mz, 5.0));
      ASSERT_HR(presults->ComputePOIForces(0, 12, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.75));
      ASSERT_TRUE(IsEqual(mz, -5.0));

      ASSERT_HR(presults->ComputePOIForces(0, 20, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -1.25));
      ASSERT_TRUE(IsEqual(mz, 5.0));
      ASSERT_HR(presults->ComputePOIForces(0, 20, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.75));
      ASSERT_TRUE(IsEqual(mz, -5.0));

      ASSERT_HR(presults->ComputePOIForces(0, 25, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.75));
      ASSERT_TRUE(IsEqual(mz, -0.5));
      ASSERT_HR(presults->ComputePOIForces(0, 25, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.75));
      ASSERT_TRUE(IsEqual(mz, 0.5));

      ASSERT_HR(presults->ComputePOIForces(0, 22, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.75));
      ASSERT_TRUE(IsEqual(mz, -6.0));
      ASSERT_HR(presults->ComputePOIForces(0, 22, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.75));
      ASSERT_TRUE(IsEqual(mz, 6.0));

      ASSERT_HR(presults->ComputePOIForces(2, 10, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -0.421875));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(2, 10, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.421875));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      ASSERT_HR(presults->ComputePOIForces(2, 15, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -0.421875));
      ASSERT_TRUE(IsEqual(mz, 0.84375000000000));
      ASSERT_HR(presults->ComputePOIForces(2, 15, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.421875));
      ASSERT_TRUE(IsEqual(mz, -0.84375000000000));

      ASSERT_HR(presults->ComputePOIForces(2, 12, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -0.421875));
      ASSERT_TRUE(IsEqual(mz, 1.6875000000000));
      ASSERT_HR(presults->ComputePOIForces(2, 12, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.421875));
      ASSERT_TRUE(IsEqual(mz, 1.3125000000000));

      ASSERT_HR(presults->ComputePOIForces(2, 20, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -0.421875));
      ASSERT_TRUE(IsEqual(mz, 1.6875000000000));
      ASSERT_HR(presults->ComputePOIForces(2, 20, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.421875));
      ASSERT_TRUE(IsEqual(mz, 1.3125000000000));

      ASSERT_HR(presults->ComputePOIForces(2, 25, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -0.421875));
      ASSERT_TRUE(IsEqual(mz, -0.46875000000000));
      ASSERT_HR(presults->ComputePOIForces(2, 25, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.421875));
      ASSERT_TRUE(IsEqual(mz, 0.46875000000000));

      ASSERT_HR(presults->ComputePOIForces(2, 22, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -0.421875));
      ASSERT_TRUE(IsEqual(mz, 0.375000000000000));
      ASSERT_HR(presults->ComputePOIForces(2, 22, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.421875));
      ASSERT_TRUE(IsEqual(mz, -0.37500000000000));

      ///////////////////////////////////////////////
      // try a fix-pin orientation
      ASSERT_MC(fixture, pMember1->ReleaseEnd(metStart, mbrReleaseNone));
      ASSERT_MC(fixture, pMember1->ReleaseEnd(metEnd, mbrReleaseMz));

      ASSERT_HR(presults->ComputeJointDeflections(0, 0, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputeJointDeflections(0, 8, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      ASSERT_HR(presults->ComputeJointDeflections(2, 0, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputeJointDeflections(2, 8, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      ASSERT_HR(presults->ComputeMemberForces(0, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 2.75));
      ASSERT_TRUE(IsEqual(smz, 6.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 1.25));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      ASSERT_HR(presults->ComputeMemberForces(2, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 0.421875));
      ASSERT_TRUE(IsEqual(smz, 0.375));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, -0.421875));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      ASSERT_HR(presults->ComputeReactions(0, 0, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.75));
      ASSERT_TRUE(IsEqual(mz, 6.0));
      ASSERT_HR(presults->ComputeReactions(0, 8, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 1.25));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      ASSERT_HR(presults->ComputeReactions(2, 0, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.421875));
      ASSERT_TRUE(IsEqual(mz, 0.375));
      ASSERT_HR(presults->ComputeReactions(2, 8, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -0.421875));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      ASSERT_HR(presults->ComputeMemberDeflections(0, 1, &sdx, &sdy, &srz, &edx, &edy, &erz));
      ASSERT_TRUE(IsEqual(sdx, 0.0));
      ASSERT_TRUE(IsEqual(sdy, 0.0));
      ASSERT_TRUE(IsEqual(srz, 0.0));
      ASSERT_TRUE(IsEqual(edx, 0.0));
      ASSERT_TRUE(IsEqual(edy, 0.0));
      ASSERT_TRUE(IsEqual(erz, 1.1428571428571));

      ASSERT_HR(presults->ComputeMemberDeflections(2, 1, &sdx, &sdy, &srz, &edx, &edy, &erz));
      ASSERT_TRUE(IsEqual(sdx, 0.0));
      ASSERT_TRUE(IsEqual(sdy, 0.0));
      ASSERT_TRUE(IsEqual(srz, 0.0));
      ASSERT_TRUE(IsEqual(edx, 0.0));
      ASSERT_TRUE(IsEqual(edy, 0.0));
      ASSERT_TRUE(IsEqual(erz, -0.21428571428571));

      ASSERT_HR(presults->ComputePOIDeflections(0, 10, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(0, 15, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -1.1904761904762));
      ASSERT_TRUE(IsEqual(rz, -0.92857142857143));
      ASSERT_HR(presults->ComputePOIDeflections(0, 12, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -2.66667));
      ASSERT_TRUE(IsEqual(rz, -0.2857142857));
      ASSERT_HR(presults->ComputePOIDeflections(0, 20, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -2.66667));
      ASSERT_TRUE(IsEqual(rz, -0.2857142857));
      ASSERT_HR(presults->ComputePOIDeflections(0, 25, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -2.047619047));
      ASSERT_TRUE(IsEqual(rz, 0.785714285));
      ASSERT_HR(presults->ComputePOIDeflections(0, 22, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 1.1428571428571));

      ASSERT_HR(presults->ComputePOIDeflections(2, 10, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(2, 15, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -0.026785714285714));
      ASSERT_TRUE(IsEqual(rz, 0.013392857142857));
      ASSERT_HR(presults->ComputePOIDeflections(2, 12, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.21428571428571));
      ASSERT_TRUE(IsEqual(rz, 0.26785714285714));
      ASSERT_HR(presults->ComputePOIDeflections(2, 20, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.21428571428571));
      ASSERT_TRUE(IsEqual(rz, 0.26785714285714));
      ASSERT_HR(presults->ComputePOIDeflections(2, 25, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.34821428571429));
      ASSERT_TRUE(IsEqual(rz, -0.093750000000000));
      ASSERT_HR(presults->ComputePOIDeflections(2, 22, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -0.21428571428571));

      ASSERT_HR(presults->ComputePOIForces(0, 10, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.75));
      ASSERT_TRUE(IsEqual(mz, -6.0));
      ASSERT_HR(presults->ComputePOIForces(0, 10, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.75));
      ASSERT_TRUE(IsEqual(mz, 6.0));
      ASSERT_HR(presults->ComputePOIForces(0, 15, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.75));
      ASSERT_TRUE(IsEqual(mz, -0.5));
      ASSERT_HR(presults->ComputePOIForces(0, 15, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.75));
      ASSERT_TRUE(IsEqual(mz, 0.5));
      ASSERT_HR(presults->ComputePOIForces(0, 12, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.75));
      ASSERT_TRUE(IsEqual(mz, 5.0));
      ASSERT_HR(presults->ComputePOIForces(0, 12, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -1.25));
      ASSERT_TRUE(IsEqual(mz, -5.0));
      ASSERT_HR(presults->ComputePOIForces(0, 20, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.75));
      ASSERT_TRUE(IsEqual(mz, 5.0));
      ASSERT_HR(presults->ComputePOIForces(0, 20, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -1.25));
      ASSERT_TRUE(IsEqual(mz, -5.0));
      ASSERT_HR(presults->ComputePOIForces(0, 25, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 1.25));
      ASSERT_TRUE(IsEqual(mz, 2.5));
      ASSERT_HR(presults->ComputePOIForces(0, 25, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -1.25));
      ASSERT_TRUE(IsEqual(mz, -2.5));
      ASSERT_HR(presults->ComputePOIForces(0, 22, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 1.25));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(0, 22, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -1.25));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      ASSERT_HR(presults->ComputePOIForces(2, 10, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -0.421875));
      ASSERT_TRUE(IsEqual(mz, -0.375));
      ASSERT_HR(presults->ComputePOIForces(2, 10, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.421875));
      ASSERT_TRUE(IsEqual(mz, 0.375));
      ASSERT_HR(presults->ComputePOIForces(2, 15, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -0.421875));
      ASSERT_TRUE(IsEqual(mz, 0.46875));
      ASSERT_HR(presults->ComputePOIForces(2, 15, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.421875));
      ASSERT_TRUE(IsEqual(mz, -0.46875));
      ASSERT_HR(presults->ComputePOIForces(2, 12, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -0.421875));
      ASSERT_TRUE(IsEqual(mz, 1.3125));
      ASSERT_HR(presults->ComputePOIForces(2, 12, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.421875));
      ASSERT_TRUE(IsEqual(mz, 1.6875));
      ASSERT_HR(presults->ComputePOIForces(2, 20, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -0.421875));
      ASSERT_TRUE(IsEqual(mz, 1.3125));
      ASSERT_HR(presults->ComputePOIForces(2, 20, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.421875));
      ASSERT_TRUE(IsEqual(mz, 1.6875));
      ASSERT_HR(presults->ComputePOIForces(2, 25, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -0.421875));
      ASSERT_TRUE(IsEqual(mz, -0.84375000000000));
      ASSERT_HR(presults->ComputePOIForces(2, 25, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.421875));
      ASSERT_TRUE(IsEqual(mz, 0.84375000000000));
      ASSERT_HR(presults->ComputePOIForces(2, 22, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -0.421875));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(2, 22, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.421875));
      ASSERT_TRUE(IsEqual(mz, 0.0));
   }
};
} // namespace Fem2dUnitTests
