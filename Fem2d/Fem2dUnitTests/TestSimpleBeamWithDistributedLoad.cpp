///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
///////////////////////////////////////////////////////////////////////
// TestSimpleBeamWithDistributedLoad.cpp
//
// Ported from F:\ARP\WBFL\Fem2d\Test\TestSimpleBeamWithDistributedLoad.cpp
#include "pch.h"

namespace Fem2dUnitTests
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
      CComPtr<IFem2dDistributedLoadCollection> pDistributedLoads;
      ASSERT_HR(pLoading->get_DistributedLoads(&pDistributedLoads));
      CComPtr<IFem2dDistributedLoad> pDistributedLoad;
      ASSERT_LC(fixture, pDistributedLoads->Create(0, 1, loadDirFy, 2.5, 5.0, 2.0, 4.0, lotMember, &pDistributedLoad));

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

      Float64 sfx, sfy, smz, efx, efy, emz;
      ASSERT_HR(presults->ComputeMemberForces(0, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, -3.898925));
      ASSERT_TRUE(IsEqual(smz, -7.438151));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, -3.601074));
      ASSERT_TRUE(IsEqual(emz, 7.080078));

      Float64 fx, fy, mz;
      ASSERT_HR(presults->ComputeReactions(0, 0, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -3.89892));
      ASSERT_TRUE(IsEqual(mz, -7.43815));
      ASSERT_HR(presults->ComputeReactions(0, 8, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -3.601074));
      ASSERT_TRUE(IsEqual(mz, 7.080078));

      Float64 sdx, sdy, srz, edx, edy, erz;
      ASSERT_HR(presults->ComputeMemberDeflections(0, 1, &sdx, &sdy, &srz, &edx, &edy, &erz));
      ASSERT_TRUE(IsEqual(sdx, 0.0));
      ASSERT_TRUE(IsEqual(sdy, 0.0));
      ASSERT_TRUE(IsEqual(srz, 0.0));
      ASSERT_TRUE(IsEqual(edx, 0.0));
      ASSERT_TRUE(IsEqual(edy, 0.0));
      ASSERT_TRUE(IsEqual(erz, 0.0));

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
      ASSERT_TRUE(IsEqual(dy, 1.382533));
      ASSERT_TRUE(IsEqual(rz, 1.011207));
      ASSERT_HR(presults->ComputePOIDeflections(0, 12, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 2.627023809));
      ASSERT_TRUE(IsEqual(rz, -0.020721726));
      ASSERT_HR(presults->ComputePOIDeflections(0, 20, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 2.627023809));
      ASSERT_TRUE(IsEqual(rz, -0.020721726));
      ASSERT_HR(presults->ComputePOIDeflections(0, 25, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 1.3369605));
      ASSERT_TRUE(IsEqual(rz, -0.9940011));
      ASSERT_HR(presults->ComputePOIDeflections(0, 22, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      ASSERT_HR(presults->ComputePOIForces(0, 10, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 3.8989257));
      ASSERT_TRUE(IsEqual(mz, 7.4381510));
      ASSERT_HR(presults->ComputePOIForces(0, 10, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -3.8989257));
      ASSERT_TRUE(IsEqual(mz, -7.4381510));

      ASSERT_HR(presults->ComputePOIForces(0, 15, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 3.8989257));
      ASSERT_TRUE(IsEqual(mz, -0.3597005));
      ASSERT_HR(presults->ComputePOIForces(0, 15, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -3.8989257));
      ASSERT_TRUE(IsEqual(mz, 0.3597005));

      ASSERT_HR(presults->ComputePOIForces(0, 12, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -0.00107422));
      ASSERT_TRUE(IsEqual(mz, -5.457552));
      ASSERT_HR(presults->ComputePOIForces(0, 12, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.00107422));
      ASSERT_TRUE(IsEqual(mz, 5.457552));

      ASSERT_HR(presults->ComputePOIForces(0, 20, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -0.00107422));
      ASSERT_TRUE(IsEqual(mz, -5.457552));
      ASSERT_HR(presults->ComputePOIForces(0, 20, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.00107422));
      ASSERT_TRUE(IsEqual(mz, 5.457552));

      ASSERT_HR(presults->ComputePOIForces(0, 25, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -3.601074));
      ASSERT_TRUE(IsEqual(mz, -0.122070));
      ASSERT_HR(presults->ComputePOIForces(0, 25, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 3.601074));
      ASSERT_TRUE(IsEqual(mz, 0.122070));

      ASSERT_HR(presults->ComputePOIForces(0, 22, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -3.601074));
      ASSERT_TRUE(IsEqual(mz, 7.080078));
      ASSERT_HR(presults->ComputePOIForces(0, 22, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 3.601074));
      ASSERT_TRUE(IsEqual(mz, -7.080078));

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

      ASSERT_HR(presults->ComputeMemberForces(0, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, -2.5042724));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, -4.9957275));
      ASSERT_TRUE(IsEqual(emz, 10.7991536));

      ASSERT_HR(presults->ComputeReactions(0, 0, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.50427246));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputeReactions(0, 8, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -4.9957275));
      ASSERT_TRUE(IsEqual(mz, 10.7991536));

      ASSERT_HR(presults->ComputeMemberDeflections(0, 1, &sdx, &sdy, &srz, &edx, &edy, &erz));
      ASSERT_TRUE(IsEqual(sdx, 0.0));
      ASSERT_TRUE(IsEqual(sdy, 0.0));
      ASSERT_TRUE(IsEqual(srz, 2.125186));
      ASSERT_TRUE(IsEqual(edx, 0.0));
      ASSERT_TRUE(IsEqual(edy, 0.0));
      ASSERT_TRUE(IsEqual(erz, 0.0));

      ASSERT_HR(presults->ComputePOIDeflections(0, 10, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 2.12518601));
      ASSERT_HR(presults->ComputePOIDeflections(0, 15, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 3.77336774));
      ASSERT_TRUE(IsEqual(rz, 1.40967959));
      ASSERT_HR(presults->ComputePOIDeflections(0, 12, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 4.75220982));
      ASSERT_TRUE(IsEqual(rz, -0.55201822));
      ASSERT_HR(presults->ComputePOIDeflections(0, 20, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 4.75220982));
      ASSERT_TRUE(IsEqual(rz, -0.55201822));
      ASSERT_HR(presults->ComputePOIDeflections(0, 25, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 2.133905));
      ASSERT_TRUE(IsEqual(rz, -1.658121));
      ASSERT_HR(presults->ComputePOIDeflections(0, 22, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      ASSERT_HR(presults->ComputePOIForces(0, 10, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.5042724609375));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(0, 10, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.5042724609375));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      ASSERT_HR(presults->ComputePOIForces(0, 15, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.5042724609375));
      ASSERT_TRUE(IsEqual(mz, -5.0085449218750));
      ASSERT_HR(presults->ComputePOIForces(0, 15, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.5042724609375));
      ASSERT_TRUE(IsEqual(mz, 5.0085449218750));

      ASSERT_HR(presults->ComputePOIForces(0, 12, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -1.3957275390625));
      ASSERT_TRUE(IsEqual(mz, -7.3170898437500));
      ASSERT_HR(presults->ComputePOIForces(0, 12, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 1.3957275390625));
      ASSERT_TRUE(IsEqual(mz, 7.3170898437500));

      ASSERT_HR(presults->ComputePOIForces(0, 20, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -1.3957275390625));
      ASSERT_TRUE(IsEqual(mz, -7.3170898437500));
      ASSERT_HR(presults->ComputePOIForces(0, 20, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 1.3957275390625));
      ASSERT_TRUE(IsEqual(mz, 7.3170898437500));

      ASSERT_HR(presults->ComputePOIForces(0, 25, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -4.9957275390625));
      ASSERT_TRUE(IsEqual(mz, 0.80769856770834));
      ASSERT_HR(presults->ComputePOIForces(0, 25, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 4.9957275390625));
      ASSERT_TRUE(IsEqual(mz, -0.80769856770834));

      ASSERT_HR(presults->ComputePOIForces(0, 22, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -4.9957275));
      ASSERT_TRUE(IsEqual(mz, 10.7991536));
      ASSERT_HR(presults->ComputePOIForces(0, 22, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 4.9957275));
      ASSERT_TRUE(IsEqual(mz, -10.7991536));

      ///////////////////////////////////////////////
      // try a pin-pin orientation
      ASSERT_MC(fixture, pMember1->ReleaseEnd(metEnd, mbrReleaseMz));

      ASSERT_HR(presults->ComputeJointDeflections(0, 0, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputeJointDeflections(0, 8, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      ASSERT_HR(presults->ComputeMemberForces(0, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, -3.85416667));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, -3.6458333));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      ASSERT_HR(presults->ComputeReactions(0, 0, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -3.85416667));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputeReactions(0, 8, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -3.64583333));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      ASSERT_HR(presults->ComputeMemberDeflections(0, 1, &sdx, &sdy, &srz, &edx, &edy, &erz));
      ASSERT_TRUE(IsEqual(sdx, 0.0));
      ASSERT_TRUE(IsEqual(sdy, 0.0));
      ASSERT_TRUE(IsEqual(srz, 4.18216765));
      ASSERT_TRUE(IsEqual(edx, 0.0));
      ASSERT_TRUE(IsEqual(edy, 0.0));
      ASSERT_TRUE(IsEqual(erz, -4.11396329));

      ASSERT_HR(presults->ComputePOIDeflections(0, 10, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 4.182167658));
      ASSERT_HR(presults->ComputePOIDeflections(0, 15, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 7.63020833));
      ASSERT_TRUE(IsEqual(rz, 3.08097718));
      ASSERT_HR(presults->ComputePOIDeflections(0, 12, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 10.9231547));
      ASSERT_TRUE(IsEqual(rz, -0.0377728));
      ASSERT_HR(presults->ComputePOIDeflections(0, 20, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 10.92315));
      ASSERT_TRUE(IsEqual(rz, -0.037772817));
      ASSERT_HR(presults->ComputePOIDeflections(0, 25, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 7.5334821428571));
      ASSERT_TRUE(IsEqual(rz, -3.0722966269841));
      ASSERT_HR(presults->ComputePOIDeflections(0, 22, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -4.11396329));

      ASSERT_HR(presults->ComputePOIForces(0, 10, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 3.8541666666667));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(0, 10, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -3.8541666666667));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      ASSERT_HR(presults->ComputePOIForces(0, 15, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 3.8541666666667));
      ASSERT_TRUE(IsEqual(mz, -7.7083333333333));
      ASSERT_HR(presults->ComputePOIForces(0, 15, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -3.8541666666667));
      ASSERT_TRUE(IsEqual(mz, 7.7083333333333));

      ASSERT_HR(presults->ComputePOIForces(0, 12, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -0.045833333333333));
      ASSERT_TRUE(IsEqual(mz, -12.716666666667));
      ASSERT_HR(presults->ComputePOIForces(0, 12, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.045833333333333));
      ASSERT_TRUE(IsEqual(mz, 12.716666666667));

      ASSERT_HR(presults->ComputePOIForces(0, 20, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -0.045833333333333));
      ASSERT_TRUE(IsEqual(mz, -12.716666666667));
      ASSERT_HR(presults->ComputePOIForces(0, 20, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.045833333333333));
      ASSERT_TRUE(IsEqual(mz, 12.716666666667));

      ASSERT_HR(presults->ComputePOIForces(0, 25, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -3.6458333333333));
      ASSERT_TRUE(IsEqual(mz, -7.2916666666667));
      ASSERT_HR(presults->ComputePOIForces(0, 25, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 3.645833333333));
      ASSERT_TRUE(IsEqual(mz, 7.2916666666667));

      ASSERT_HR(presults->ComputePOIForces(0, 22, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -3.6458333333333));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(0, 22, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 3.6458333333333));
      ASSERT_TRUE(IsEqual(mz, 0.0));

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

      ASSERT_HR(presults->ComputeMemberForces(0, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, -5.2264404));
      ASSERT_TRUE(IsEqual(smz, -10.978190));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, -2.273559));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      ASSERT_HR(presults->ComputeReactions(0, 0, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -5.2264404));
      ASSERT_TRUE(IsEqual(mz, -10.978190));
      ASSERT_HR(presults->ComputeReactions(0, 8, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.273559));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      ASSERT_HR(presults->ComputeMemberDeflections(0, 1, &sdx, &sdy, &srz, &edx, &edy, &erz));
      ASSERT_TRUE(IsEqual(sdx, 0.0));
      ASSERT_TRUE(IsEqual(sdy, 0.0));
      ASSERT_TRUE(IsEqual(srz, 0.0));
      ASSERT_TRUE(IsEqual(edx, 0.0));
      ASSERT_TRUE(IsEqual(edy, 0.0));
      ASSERT_TRUE(IsEqual(erz, -2.0228794642857));

      ASSERT_HR(presults->ComputePOIDeflections(0, 10, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(0, 15, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 2.14111));
      ASSERT_TRUE(IsEqual(rz, 1.64335));
      ASSERT_HR(presults->ComputePOIDeflections(0, 12, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 4.6499032));
      ASSERT_TRUE(IsEqual(rz, 0.4849981));
      ASSERT_HR(presults->ComputePOIDeflections(0, 20, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 4.6499032));
      ASSERT_TRUE(IsEqual(rz, 0.4849981));
      ASSERT_HR(presults->ComputePOIDeflections(0, 25, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 3.61269996));
      ASSERT_TRUE(IsEqual(rz, -1.37329101));
      ASSERT_HR(presults->ComputePOIDeflections(0, 22, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -2.02287946));

      ASSERT_HR(presults->ComputePOIForces(0, 10, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 5.2264404296875));
      ASSERT_TRUE(IsEqual(mz, 10.978190104167));
      ASSERT_HR(presults->ComputePOIForces(0, 10, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -5.2264404296875));
      ASSERT_TRUE(IsEqual(mz, -10.978190104167));
      ASSERT_HR(presults->ComputePOIForces(0, 15, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 5.2264404296875));
      ASSERT_TRUE(IsEqual(mz, 0.52530924479167));
      ASSERT_HR(presults->ComputePOIForces(0, 15, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -5.2264404296875));
      ASSERT_TRUE(IsEqual(mz, -0.52530924479167));
      ASSERT_HR(presults->ComputePOIForces(0, 12, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 1.326440429));
      ASSERT_TRUE(IsEqual(mz, -7.227571614));
      ASSERT_HR(presults->ComputePOIForces(0, 12, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -1.326440429));
      ASSERT_TRUE(IsEqual(mz, 7.227571614));
      ASSERT_HR(presults->ComputePOIForces(0, 20, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 1.326440429));
      ASSERT_TRUE(IsEqual(mz, -7.227571614));
      ASSERT_HR(presults->ComputePOIForces(0, 20, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -1.326440429));
      ASSERT_TRUE(IsEqual(mz, 7.227571614));
      ASSERT_HR(presults->ComputePOIForces(0, 25, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.27355957));
      ASSERT_TRUE(IsEqual(mz, -4.54711914));
      ASSERT_HR(presults->ComputePOIForces(0, 25, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.27355957));
      ASSERT_TRUE(IsEqual(mz, 4.54711914));
      ASSERT_HR(presults->ComputePOIForces(0, 22, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.27355957));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(0, 22, mftRight, lotGlobal, &fx, &fy, &mz));
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
      Fem2dModelFixture fixture;
      CComPtr<IFem2dModel>& pmodel = fixture.Model;

      CComPtr<IFem2dJointCollection> pJoints;
      ASSERT_HR(pmodel->get_Joints(&pJoints));

      CComPtr<IFem2dJoint> pJoint1, pJoint2, pJoint3, pJoint4;
      ASSERT_MC(fixture, pJoints->Create(1, 0.0, 0.0, &pJoint1));
      ASSERT_MC(fixture, pJoints->Create(2, 16.0, 0.0, &pJoint2));
      ASSERT_MC(fixture, pJoints->Create(3, 30.0, 0.0, &pJoint3));
      ASSERT_MC(fixture, pJoints->Create(4, 40.0, 0.0, &pJoint4));

      ASSERT_MC(fixture, pJoint1->Support());
      ASSERT_MC(fixture, pJoint2->Support());
      ASSERT_MC(fixture, pJoint3->Support());
      ASSERT_MC(fixture, pJoint4->Support());
      ASSERT_MC(fixture, pJoint1->ReleaseDof(jrtMz));
      ASSERT_MC(fixture, pJoint2->ReleaseDof(jrtMz));
      ASSERT_MC(fixture, pJoint3->ReleaseDof(jrtMz));
      ASSERT_MC(fixture, pJoint4->ReleaseDof(jrtMz));

      CComPtr<IFem2dMemberCollection> pMembers;
      ASSERT_HR(pmodel->get_Members(&pMembers));

      CComPtr<IFem2dMember> pMember1, pMember2, pMember3;
      ASSERT_MC(fixture, pMembers->Create(1, 1, 2, 3.0, 7.0, &pMember1));
      ASSERT_MC(fixture, pMembers->Create(2, 2, 3, 3.0, 7.0, &pMember2));
      ASSERT_MC(fixture, pMembers->Create(3, 3, 4, 3.0, 7.0, &pMember3));

      CComPtr<IFem2dLoadingCollection> pLoadings;
      ASSERT_HR(pmodel->get_Loadings(&pLoadings));
      CComPtr<IFem2dLoading> pLoading;
      ASSERT_LC(fixture, pLoadings->Create(0, &pLoading));
      CComPtr<IFem2dDistributedLoadCollection> pDistributedLoads;
      ASSERT_HR(pLoading->get_DistributedLoads(&pDistributedLoads));
      CComPtr<IFem2dDistributedLoad> pDistributedLoad1, pDistributedLoad2;
      ASSERT_LC(fixture, pDistributedLoads->Create(1, 1, loadDirFy, 4.0, -1.0, -18.0, -6.0, lotMember, &pDistributedLoad1));
      ASSERT_LC(fixture, pDistributedLoads->Create(2, 2, loadDirFy, 0.0, 6.0, -6.0, 0.0, lotMember, &pDistributedLoad2));

      // put a point load at 4 into member 3
      CComPtr<IFem2dPointLoadCollection> pPointLoads;
      ASSERT_HR(pLoading->get_PointLoads(&pPointLoads));
      CComPtr<IFem2dPointLoad> pPointLoad;
      ASSERT_LC(fixture, pPointLoads->Create(0, 3, 4.0, 0.0, -21.0, 0.0, lotMember, &pPointLoad));

      // POI's at 1/4 points in members 1 and 2
      CComPtr<IFem2dPOICollection> pPOIs;
      ASSERT_HR(pmodel->get_POIs(&pPOIs));

      CComPtr<IFem2dPOI> pPOI10, pPOI11, pPOI12, pPOI13, pPOI14;
      ASSERT_HR(pPOIs->Create(10, 1, 0.0, &pPOI10));
      ASSERT_HR(pPOIs->Create(11, 1, -0.25, &pPOI11));
      ASSERT_HR(pPOIs->Create(12, 1, -0.5, &pPOI12));
      ASSERT_HR(pPOIs->Create(13, 1, -0.75, &pPOI13));
      ASSERT_HR(pPOIs->Create(14, 1, -1.0, &pPOI14));

      CComPtr<IFem2dPOI> pPOI20, pPOI21, pPOI22, pPOI23, pPOI24;
      ASSERT_HR(pPOIs->Create(20, 2, 0.0, &pPOI20));
      ASSERT_HR(pPOIs->Create(21, 2, -0.25, &pPOI21));
      ASSERT_HR(pPOIs->Create(22, 2, -0.5, &pPOI22));
      ASSERT_HR(pPOIs->Create(23, 2, -0.75, &pPOI23));
      ASSERT_HR(pPOIs->Create(24, 2, -1.0, &pPOI24));

      // mid point of member 3
      CComPtr<IFem2dPOI> pPOI32;
      ASSERT_HR(pPOIs->Create(32, 3, -0.5, &pPOI32));

      CComQIPtr<IFem2dModelResults> presults(pmodel);

      Float64 dx, dy, rz;
      ASSERT_HR(presults->ComputeJointDeflections(0, 1, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -183.75544));
      ASSERT_HR(presults->ComputeJointDeflections(0, 2, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 111.39659965));
      ASSERT_HR(presults->ComputeJointDeflections(0, 3, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -35.60633839));
      ASSERT_HR(presults->ComputeJointDeflections(0, 4, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 25.003169));

      Float64 sfx, sfy, smz, efx, efy, emz;
      ASSERT_HR(presults->ComputeMemberForces(0, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 49.8911273));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 94.1088726));
      ASSERT_TRUE(IsEqual(emz, -209.741962955));
      ASSERT_HR(presults->ComputeMemberForces(0, 2, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 32.871090969));
      ASSERT_TRUE(IsEqual(smz, 209.74196295508));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, -14.87109097));
      ASSERT_TRUE(IsEqual(emz, 34.45331062));
      ASSERT_HR(presults->ComputeMemberForces(0, 3, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 9.154668937));
      ASSERT_TRUE(IsEqual(smz, -34.45331062));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 11.845331062));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      Float64 fx, fy, mz;
      ASSERT_HR(presults->ComputeReactions(0, 1, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 49.8911273));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputeReactions(0, 2, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 126.9799636));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputeReactions(0, 3, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -5.716422032));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputeReactions(0, 4, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 11.845331062380));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      Float64 sdx, sdy, srz, edx, edy, erz;
      ASSERT_HR(presults->ComputeMemberDeflections(0, 1, &sdx, &sdy, &srz, &edx, &edy, &erz));
      ASSERT_TRUE(IsEqual(sdx, 0.0));
      ASSERT_TRUE(IsEqual(sdy, 0.0));
      ASSERT_TRUE(IsEqual(srz, -183.755443));
      ASSERT_TRUE(IsEqual(edx, 0.0));
      ASSERT_TRUE(IsEqual(edy, 0.0));
      ASSERT_TRUE(IsEqual(erz, 111.39659965327));

      ASSERT_HR(presults->ComputeMemberDeflections(0, 2, &sdx, &sdy, &srz, &edx, &edy, &erz));
      ASSERT_TRUE(IsEqual(sdx, 0.0));
      ASSERT_TRUE(IsEqual(sdy, 0.0));
      ASSERT_TRUE(IsEqual(srz, 111.39659965327));
      ASSERT_TRUE(IsEqual(edx, 0.0));
      ASSERT_TRUE(IsEqual(edy, 0.0));
      ASSERT_TRUE(IsEqual(erz, -35.606338392287));

      ASSERT_HR(presults->ComputeMemberDeflections(0, 3, &sdx, &sdy, &srz, &edx, &edy, &erz));
      ASSERT_TRUE(IsEqual(sdx, 0.0));
      ASSERT_TRUE(IsEqual(sdy, 0.0));
      ASSERT_TRUE(IsEqual(srz, -35.606338392));
      ASSERT_TRUE(IsEqual(edx, 0.0));
      ASSERT_TRUE(IsEqual(edy, 0.0));
      ASSERT_TRUE(IsEqual(erz, 25.0031692));

      ASSERT_HR(presults->ComputePOIDeflections(0, 10, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -183.75544268378));
      ASSERT_HR(presults->ComputePOIDeflections(0, 11, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -658.99719577846));
      ASSERT_TRUE(IsEqual(rz, -126.73701146629));
      ASSERT_HR(presults->ComputePOIDeflections(0, 12, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -888.05646562649));
      ASSERT_TRUE(IsEqual(rz, 18.413520281436));
      ASSERT_HR(presults->ComputePOIDeflections(0, 13, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -552.24940742318));
      ASSERT_TRUE(IsEqual(rz, 134.36281922605));
      ASSERT_HR(presults->ComputePOIDeflections(0, 14, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 111.39659965327));
      ASSERT_HR(presults->ComputePOIDeflections(0, 20, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 111.39659965327));
      ASSERT_HR(presults->ComputePOIDeflections(0, 21, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 235.18567198256));
      ASSERT_TRUE(IsEqual(rz, 30.056051941082));
      ASSERT_HR(presults->ComputePOIDeflections(0, 22, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 248.38371300830));
      ASSERT_TRUE(IsEqual(rz, -18.010830621369));
      ASSERT_HR(presults->ComputePOIDeflections(0, 23, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 139.58792580370));
      ASSERT_TRUE(IsEqual(rz, -39.820789105508));
      ASSERT_HR(presults->ComputePOIDeflections(0, 24, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -35.606338392287));
      ASSERT_HR(presults->ComputePOIDeflections(0, 32, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -89.761884485538));
      ASSERT_TRUE(IsEqual(rz, 3.8507922990358));

      ASSERT_HR(presults->ComputePOIForces(0, 10, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -49.891127315308));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(0, 11, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -49.891127315308));
      ASSERT_TRUE(IsEqual(mz, 199.56450926123));
      ASSERT_HR(presults->ComputePOIForces(0, 12, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 14.108872684692));
      ASSERT_TRUE(IsEqual(mz, 265.79568518913));
      ASSERT_HR(presults->ComputePOIForces(0, 13, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 62.108872684692));
      ASSERT_TRUE(IsEqual(mz, 108.02686111703));
      ASSERT_HR(presults->ComputePOIForces(0, 14, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 94.108872684692));
      ASSERT_TRUE(IsEqual(mz, -209.74196295508));
      ASSERT_HR(presults->ComputePOIForces(0, 14, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -94.108872684692));
      ASSERT_TRUE(IsEqual(mz, 209.74196295508));
      ASSERT_HR(presults->ComputePOIForces(0, 20, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -32.871090969920));
      ASSERT_TRUE(IsEqual(mz, -209.74196295508));
      ASSERT_HR(presults->ComputePOIForces(0, 21, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -17.996090969920));
      ASSERT_TRUE(IsEqual(mz, -124.29731122702));
      ASSERT_HR(presults->ComputePOIForces(0, 22, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -14.871090));
      ASSERT_TRUE(IsEqual(mz, -69.644326));
      ASSERT_HR(presults->ComputePOIForces(0, 32, mftLeft, lotGlobal, &fx, &fy, &mz));
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
      CComPtr<IFem2dDistributedLoadCollection> pDistributedLoads;
      ASSERT_HR(pLoading->get_DistributedLoads(&pDistributedLoads));
      CComPtr<IFem2dDistributedLoad> pDistributedLoad;

      // load with zero length
      ASSERT_LC(fixture, pDistributedLoads->Create(0, 1, loadDirFy, 2.5, 2.5, 0.0, 0.0, lotMember, &pDistributedLoad));

      CComPtr<IFem2dPOICollection> pPOIs;
      ASSERT_HR(pmodel->get_POIs(&pPOIs));

      CComPtr<IFem2dPOI> pPOI10, pPOI15, pPOI12;
      ASSERT_HR(pPOIs->Create(10, 1, 0.0, &pPOI10));
      ASSERT_HR(pPOIs->Create(15, 1, -.25, &pPOI15));
      ASSERT_HR(pPOIs->Create(12, 1, -0.5, &pPOI12));

      CComQIPtr<IFem2dModelResults> presults(pmodel);

      Float64 fx, fy, mz;
      // should be zero since there are no forces
      ASSERT_HR(presults->ComputeReactions(0, 0, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      // now put values into the load and carry on with the test except swap
      // end and start values
      ASSERT_LC(fixture, pDistributedLoad->put_StartLocation(5.0));
      ASSERT_LC(fixture, pDistributedLoad->put_WStart(4.0));
      ASSERT_LC(fixture, pDistributedLoad->put_WEnd(2.0));

      Float64 dx, dy, rz;
      ASSERT_HR(presults->ComputeJointDeflections(0, 0, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputeJointDeflections(0, 8, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      Float64 sfx, sfy, smz, efx, efy, emz;
      ASSERT_HR(presults->ComputeMemberForces(0, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, -3.898925));
      ASSERT_TRUE(IsEqual(smz, -7.438151));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, -3.601074));
      ASSERT_TRUE(IsEqual(emz, 7.080078));

      ASSERT_HR(presults->ComputeReactions(0, 0, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -3.89892));
      ASSERT_TRUE(IsEqual(mz, -7.43815));
      ASSERT_HR(presults->ComputeReactions(0, 8, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -3.601074));
      ASSERT_TRUE(IsEqual(mz, 7.080078));

      Float64 sdx, sdy, srz, edx, edy, erz;
      ASSERT_HR(presults->ComputeMemberDeflections(0, 1, &sdx, &sdy, &srz, &edx, &edy, &erz));
      ASSERT_TRUE(IsEqual(sdx, 0.0));
      ASSERT_TRUE(IsEqual(sdy, 0.0));
      ASSERT_TRUE(IsEqual(srz, 0.0));
      ASSERT_TRUE(IsEqual(edx, 0.0));
      ASSERT_TRUE(IsEqual(edy, 0.0));
      ASSERT_TRUE(IsEqual(erz, 0.0));

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
      ASSERT_TRUE(IsEqual(dy, 1.382533));
      ASSERT_TRUE(IsEqual(rz, 1.011207));
      ASSERT_HR(presults->ComputePOIDeflections(0, 12, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 2.627023809));
      ASSERT_TRUE(IsEqual(rz, -0.020721726));
      ASSERT_HR(presults->ComputePOIDeflections(0, 20, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 2.627023809));
      ASSERT_TRUE(IsEqual(rz, -0.020721726));
      ASSERT_HR(presults->ComputePOIDeflections(0, 25, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 1.3369605));
      ASSERT_TRUE(IsEqual(rz, -0.9940011));
      ASSERT_HR(presults->ComputePOIDeflections(0, 22, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      ASSERT_HR(presults->ComputePOIForces(0, 10, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 3.8989257));
      ASSERT_TRUE(IsEqual(mz, 7.4381510));
      ASSERT_HR(presults->ComputePOIForces(0, 10, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -3.8989257));
      ASSERT_TRUE(IsEqual(mz, -7.4381510));

      ASSERT_HR(presults->ComputePOIForces(0, 15, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 3.8989257));
      ASSERT_TRUE(IsEqual(mz, -0.3597005));
      ASSERT_HR(presults->ComputePOIForces(0, 15, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -3.8989257));
      ASSERT_TRUE(IsEqual(mz, 0.3597005));

      ASSERT_HR(presults->ComputePOIForces(0, 12, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -0.00107422));
      ASSERT_TRUE(IsEqual(mz, -5.457552));
      ASSERT_HR(presults->ComputePOIForces(0, 12, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.00107422));
      ASSERT_TRUE(IsEqual(mz, 5.457552));

      ASSERT_HR(presults->ComputePOIForces(0, 20, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -0.00107422));
      ASSERT_TRUE(IsEqual(mz, -5.457552));
      ASSERT_HR(presults->ComputePOIForces(0, 20, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.00107422));
      ASSERT_TRUE(IsEqual(mz, 5.457552));

      ASSERT_HR(presults->ComputePOIForces(0, 25, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -3.601074));
      ASSERT_TRUE(IsEqual(mz, -0.122070));
      ASSERT_HR(presults->ComputePOIForces(0, 25, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 3.601074));
      ASSERT_TRUE(IsEqual(mz, 0.122070));

      ASSERT_HR(presults->ComputePOIForces(0, 22, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -3.601074));
      ASSERT_TRUE(IsEqual(mz, 7.080078));
      ASSERT_HR(presults->ComputePOIForces(0, 22, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 3.601074));
      ASSERT_TRUE(IsEqual(mz, -7.080078));
   }
};
} // namespace Fem2dUnitTests
