///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
///////////////////////////////////////////////////////////////////////
// TestSimpleBeamWithJointLoad.cpp
//
// Ported from F:\ARP\WBFL\Fem2d\Test\TestSimpleBeamWithJointLoad.cpp and
// TestSimpleBeamWithJointLoad2.cpp (the legacy harness split this into two
// files/functions purely due to old compiler function-size limits; merged
// back into a single TEST_METHOD here since that limit no longer applies).
#include "pch.h"

namespace Fem2dUnitTests
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
      Fem2dModelFixture fixture;
      CComPtr<IFem2dModel>& pmodel = fixture.Model;

      CComPtr<IFem2dJointCollection> pJoints;
      ASSERT_HR(pmodel->get_Joints(&pJoints));

      CComPtr<IFem2dJoint> pJoint0, pJoint4, pJoint8;
      ASSERT_MC(fixture, pJoints->Create(0, 0.0, 0.0, &pJoint0));
      ASSERT_MC(fixture, pJoints->Create(4, 4.0, 0.0, &pJoint4));
      ASSERT_MC(fixture, pJoints->Create(8, 8.0, 0.0, &pJoint8));

      ASSERT_MC(fixture, pJoint0->Support());
      ASSERT_MC(fixture, pJoint0->ReleaseDof(jrtMz));
      ASSERT_MC(fixture, pJoint8->Support());
      ASSERT_MC(fixture, pJoint8->ReleaseDof(jrtFx));
      ASSERT_MC(fixture, pJoint8->ReleaseDof(jrtMz));

      CComPtr<IFem2dMemberCollection> pMembers;
      ASSERT_HR(pmodel->get_Members(&pMembers));

      CComPtr<IFem2dMember> pMember1, pMember2;
      ASSERT_MC(fixture, pMembers->Create(1, 0, 4, 3.0, 7.0, &pMember1));
      ASSERT_MC(fixture, pMembers->Create(2, 4, 8, 3.0, 7.0, &pMember2));

      CComPtr<IFem2dLoadingCollection> pLoadings;
      ASSERT_HR(pmodel->get_Loadings(&pLoadings));
      CComPtr<IFem2dLoading> pLoading;
      ASSERT_LC(fixture, pLoadings->Create(0, &pLoading));
      CComPtr<IFem2dJointLoadCollection> pJointLoads;
      ASSERT_HR(pLoading->get_JointLoads(&pJointLoads));

      CComPtr<IFem2dJointLoad> pJointLoad;
      ASSERT_LC(fixture, pJointLoads->Create(0, 4, 0.0, -4.0, 0.0, &pJointLoad));

      // POI's at 1/4 points in member 1 - these results are pre-calculated
      CComPtr<IFem2dPOICollection> pPOIs;
      ASSERT_HR(pmodel->get_POIs(&pPOIs));

      CComPtr<IFem2dPOI> pPOI10, pPOI15, pPOI12, pPOILost;
      ASSERT_HR(pPOIs->Create(10, 1, 0.0, &pPOI10));
      ASSERT_HR(pPOIs->Create(15, 1, -.5, &pPOI15));
      ASSERT_HR(pPOIs->Create(12, 1, -1.0, &pPOI12));
      ASSERT_HR(pPOIs->Create(13, 5, -1.0, &pPOILost)); // member doesn't exist

      CComQIPtr<IFem2dModelResults> presults(pmodel);
      CComQIPtr<IFem2dModelResultsEx> presultsex(pmodel);

      PoiIDType id;
      ASSERT_HR(pPOIs->Remove(13, atID, &id));
      ASSERT_EQ(id, 13);

      Float64 dx, dy, rz;
      ASSERT_HR(presults->ComputeJointDeflections(0, 0, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -2.2857142857143));
      ASSERT_HR(presults->ComputeJointDeflections(0, 4, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -6.0952380952381));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputeJointDeflections(0, 8, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 2.2857142857143));

      // test error handling
      ASSERT_EQ(presults->ComputeJointDeflections(1, 8, &dx, &dy, &rz), FEM2D_E_LOADING_NOT_FOUND);
      ASSERT_EQ(presults->ComputeJointDeflections(0, 11, &dx, &dy, &rz), FEM2D_E_JOINT_NOT_FOUND);

      Float64 sfx, sfy, smz, efx, efy, emz;
      ASSERT_HR(presults->ComputeMemberForces(0, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 2.0));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, -2.0));
      ASSERT_TRUE(IsEqual(emz, 8.0));
      ASSERT_HR(presults->ComputeMemberForces(0, 2, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, -2.0));
      ASSERT_TRUE(IsEqual(smz, -8.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 2.0));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      ASSERT_HR(presultsex->ComputeMemberForcesEx(0, 1, lotGlobal, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 2.0));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, -2.0));
      ASSERT_TRUE(IsEqual(emz, 8.0));
      ASSERT_HR(presultsex->ComputeMemberForcesEx(0, 2, lotGlobal, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, -2.0));
      ASSERT_TRUE(IsEqual(smz, -8.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 2.0));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      // load case doesn't exist
      ASSERT_EQ(presults->ComputeMemberForces(1, 2, &sfx, &sfy, &smz, &efx, &efy, &emz), FEM2D_E_LOADING_NOT_FOUND);
      ASSERT_EQ(presults->ComputeMemberForces(0, 4, &sfx, &sfy, &smz, &efx, &efy, &emz), FEM2D_E_MEMBER_NOT_FOUND);
      ASSERT_EQ(presultsex->ComputeMemberForcesEx(1, 2, lotGlobal, &sfx, &sfy, &smz, &efx, &efy, &emz), FEM2D_E_LOADING_NOT_FOUND);
      ASSERT_EQ(presultsex->ComputeMemberForcesEx(0, 4, lotMember, &sfx, &sfy, &smz, &efx, &efy, &emz), FEM2D_E_MEMBER_NOT_FOUND);

      Float64 fx, fy, mz;
      ASSERT_HR(presults->ComputeReactions(0, 0, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputeReactions(0, 4, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputeReactions(0, 8, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      ASSERT_EQ(presults->ComputeReactions(1, 8, &fx, &fy, &mz), FEM2D_E_LOADING_NOT_FOUND);
      ASSERT_EQ(presults->ComputeReactions(0, 12, &fx, &fy, &mz), FEM2D_E_JOINT_NOT_FOUND);

      Float64 sdx, sdy, srz, edx, edy, erz;
      ASSERT_HR(presults->ComputeMemberDeflections(0, 1, &sdx, &sdy, &srz, &edx, &edy, &erz));
      ASSERT_TRUE(IsEqual(sdx, 0.0));
      ASSERT_TRUE(IsEqual(sdy, 0.0));
      ASSERT_TRUE(IsEqual(srz, -2.2857142857143));
      ASSERT_TRUE(IsEqual(edx, 0.0));
      ASSERT_TRUE(IsEqual(edy, -6.0952380952381));
      ASSERT_TRUE(IsEqual(erz, 0.0));
      ASSERT_HR(presults->ComputeMemberDeflections(0, 2, &sdx, &sdy, &srz, &edx, &edy, &erz));
      ASSERT_TRUE(IsEqual(sdx, 0.0));
      ASSERT_TRUE(IsEqual(sdy, -6.0952380952381));
      ASSERT_TRUE(IsEqual(srz, 0.0));
      ASSERT_TRUE(IsEqual(edx, 0.0));
      ASSERT_TRUE(IsEqual(edy, 0.0));
      ASSERT_TRUE(IsEqual(erz, 2.2857142857143));

      ASSERT_EQ(presults->ComputeMemberDeflections(1, 2, &sdx, &sdy, &srz, &edx, &edy, &erz), FEM2D_E_LOADING_NOT_FOUND);
      ASSERT_EQ(presults->ComputeMemberDeflections(0, 21, &sdx, &sdy, &srz, &edx, &edy, &erz), FEM2D_E_MEMBER_NOT_FOUND);

      // POI's at 1/4 points of member 2 - these results are calculated on the fly
      CComPtr<IFem2dPOI> pPOI20, pPOI25, pPOI22;
      ASSERT_HR(pPOIs->Create(20, 2, 0.0, &pPOI20));
      ASSERT_HR(pPOIs->Create(25, 2, 2.0, &pPOI25));
      ASSERT_HR(pPOIs->Create(22, 2, 4.0, &pPOI22));

      // poi that doesn't exist
      ASSERT_EQ(presults->ComputePOIDeflections(0, 13, lotMember, &dx, &dy, &rz), FEM2D_E_POI_NOT_FOUND);

      ASSERT_HR(presults->ComputePOIDeflections(0, 10, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -2.2857142857143));
      ASSERT_HR(presults->ComputePOIDeflections(0, 15, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -4.1904761904762));
      ASSERT_TRUE(IsEqual(rz, -1.71428));
      ASSERT_HR(presults->ComputePOIDeflections(0, 12, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -6.0952380952381));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(0, 20, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -6.0952380952381));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(0, 25, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -4.1904761904762));
      ASSERT_TRUE(IsEqual(rz, 1.71428));
      ASSERT_HR(presults->ComputePOIDeflections(0, 22, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 2.2857142857143));

      ASSERT_HR(presults->ComputePOIDeflections(0, 10, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -2.2857142857143));
      ASSERT_HR(presults->ComputePOIDeflections(0, 15, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -4.1904761904762));
      ASSERT_TRUE(IsEqual(rz, -1.71428));
      ASSERT_HR(presults->ComputePOIDeflections(0, 12, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -6.0952380952381));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(0, 20, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -6.0952380952381));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(0, 25, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -4.1904761904762));
      ASSERT_TRUE(IsEqual(rz, 1.71428));
      ASSERT_HR(presults->ComputePOIDeflections(0, 22, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 2.2857142857143));

      ASSERT_EQ(presults->ComputePOIDeflections(10, 22, lotMember, &dx, &dy, &rz), FEM2D_E_LOADING_NOT_FOUND);
      ASSERT_EQ(presults->ComputePOIDeflections(0, 32, lotMember, &dx, &dy, &rz), FEM2D_E_POI_NOT_FOUND);

      ASSERT_HR(presults->ComputePOIForces(0, 10, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(0, 10, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(0, 10, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(0, 10, mftRight, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      ASSERT_HR(presults->ComputePOIForces(0, 15, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, 4.0));
      ASSERT_HR(presults->ComputePOIForces(0, 15, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, -4.0));
      ASSERT_HR(presults->ComputePOIForces(0, 15, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, 4.0));
      ASSERT_HR(presults->ComputePOIForces(0, 15, mftRight, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, -4.0));

      ASSERT_HR(presults->ComputePOIForces(0, 12, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, 8.0));
      ASSERT_HR(presults->ComputePOIForces(0, 12, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, -8.0));
      ASSERT_HR(presults->ComputePOIForces(0, 12, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, 8.0));
      ASSERT_HR(presults->ComputePOIForces(0, 12, mftRight, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, -8.0));

      ASSERT_HR(presults->ComputePOIForces(0, 20, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, 8.0));
      ASSERT_HR(presults->ComputePOIForces(0, 20, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, -8.0));
      ASSERT_HR(presults->ComputePOIForces(0, 20, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, 8.0));
      ASSERT_HR(presults->ComputePOIForces(0, 20, mftRight, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, -8.0));

      ASSERT_HR(presults->ComputePOIForces(0, 25, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, 4.0));
      ASSERT_HR(presults->ComputePOIForces(0, 25, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, -4.0));
      ASSERT_HR(presults->ComputePOIForces(0, 25, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, 4.0));
      ASSERT_HR(presults->ComputePOIForces(0, 25, mftRight, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, -4.0));

      ASSERT_EQ(presults->ComputePOIForces(10, 25, mftRight, lotMember, &fx, &fy, &mz), FEM2D_E_LOADING_NOT_FOUND);
      ASSERT_EQ(presults->ComputePOIForces(0, 32, mftRight, lotMember, &fx, &fy, &mz), FEM2D_E_POI_NOT_FOUND);

      //////////////////////////////////////////////////////////////////////////////////
      // add a new load case with a horizontal load at the middle
      CComPtr<IFem2dLoading> pLoading2;
      ASSERT_LC(fixture, pLoadings->Create(2, &pLoading2));
      CComPtr<IFem2dJointLoadCollection> pJointLoads2;
      ASSERT_HR(pLoading2->get_JointLoads(&pJointLoads2));

      CComPtr<IFem2dJointLoad> pJointLoad2;
      ASSERT_LC(fixture, pJointLoads2->Create(0, 4, 2.0, 0.0, 0.0, &pJointLoad2));

      ASSERT_HR(presults->ComputeJointDeflections(2, 0, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputeJointDeflections(2, 4, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 2.6666667));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputeJointDeflections(2, 8, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 2.6666667));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      ASSERT_HR(presults->ComputeMemberForces(2, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, -2.0));
      ASSERT_TRUE(IsEqual(sfy, 0.0));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 2.0));
      ASSERT_TRUE(IsEqual(efy, 0.0));
      ASSERT_TRUE(IsEqual(emz, 0.0));
      ASSERT_HR(presults->ComputeMemberForces(2, 2, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 0.0));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 0.0));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      ASSERT_HR(presultsex->ComputeMemberForcesEx(2, 1, lotGlobal, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, -2.0));
      ASSERT_TRUE(IsEqual(sfy, 0.0));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 2.0));
      ASSERT_TRUE(IsEqual(efy, 0.0));
      ASSERT_TRUE(IsEqual(emz, 0.0));
      ASSERT_HR(presultsex->ComputeMemberForcesEx(2, 2, lotGlobal, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 0.0));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 0.0));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      ASSERT_HR(presults->ComputeReactions(2, 0, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -2.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputeReactions(2, 4, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputeReactions(2, 8, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      ASSERT_HR(presults->ComputeMemberDeflections(2, 1, &sdx, &sdy, &srz, &edx, &edy, &erz));
      ASSERT_TRUE(IsEqual(sdx, 0.0));
      ASSERT_TRUE(IsEqual(sdy, 0.0));
      ASSERT_TRUE(IsEqual(srz, 0.0));
      ASSERT_TRUE(IsEqual(edx, 2.6666667));
      ASSERT_TRUE(IsEqual(edy, 0.0));
      ASSERT_TRUE(IsEqual(erz, 0.0));
      ASSERT_HR(presults->ComputeMemberDeflections(2, 2, &sdx, &sdy, &srz, &edx, &edy, &erz));
      ASSERT_TRUE(IsEqual(sdx, 2.6666667));
      ASSERT_TRUE(IsEqual(sdy, 0.0));
      ASSERT_TRUE(IsEqual(srz, 0.0));
      ASSERT_TRUE(IsEqual(edx, 2.6666667));
      ASSERT_TRUE(IsEqual(edy, 0.0));
      ASSERT_TRUE(IsEqual(erz, 0.0));

      ASSERT_HR(presults->ComputePOIDeflections(2, 10, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(2, 15, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 1.333333));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(2, 12, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 2.6666667));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(2, 20, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 2.6666667));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(2, 25, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 2.6666667));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(2, 22, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 2.6666667));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      ASSERT_HR(presults->ComputePOIDeflections(2, 10, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(2, 15, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 1.333333));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(2, 12, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 2.6666667));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(2, 20, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 2.6666667));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(2, 25, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 2.6666667));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(2, 22, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 2.6666667));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      ASSERT_HR(presults->ComputePOIForces(2, 10, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 2.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(2, 10, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -2.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(2, 10, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 2.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(2, 10, mftRight, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -2.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      ASSERT_HR(presults->ComputePOIForces(2, 15, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 2.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(2, 15, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -2.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(2, 15, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 2.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(2, 15, mftRight, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -2.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      ASSERT_HR(presults->ComputePOIForces(2, 12, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 2.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(2, 12, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -2.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(2, 12, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 2.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(2, 12, mftRight, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -2.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      ASSERT_HR(presults->ComputePOIForces(2, 20, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(2, 20, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(2, 20, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(2, 20, mftRight, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      ASSERT_HR(presults->ComputePOIForces(2, 25, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(2, 25, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(2, 25, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(2, 25, mftRight, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      //////////////////////////////////////////////////////////////////////////////////
      // next let's rotate the model 45 degrees clockwise
      ASSERT_MC(fixture, pJoint4->put_X(2.8284271));
      ASSERT_MC(fixture, pJoint4->put_Y(2.8284271));
      ASSERT_MC(fixture, pJoint8->put_X(5.6568542));
      ASSERT_MC(fixture, pJoint8->put_Y(5.6568542));

      // don't allow end joint to translate
      ASSERT_MC(fixture, pJoint8->Support());
      ASSERT_MC(fixture, pJoint8->ReleaseDof(jrtMz));

      Float64 l;
      pMember1->get_Length(&l);
      ASSERT_TRUE(IsEqual(l, 4.0));
      pMember2->get_Length(&l);
      ASSERT_TRUE(IsEqual(l, 4.0));

      // change orientation of point load to be normal to rotated structure
      ASSERT_LC(fixture, pJointLoad->put_Fx(2.8284271));
      ASSERT_LC(fixture, pJointLoad->put_Fy(-2.8284271));

      ASSERT_HR(presults->ComputeJointDeflections(0, 0, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -2.2857142857143));
      ASSERT_HR(presults->ComputeJointDeflections(0, 4, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 4.30998419));
      ASSERT_TRUE(IsEqual(dy, -4.30998419));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputeJointDeflections(0, 8, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 2.2857142857143));

      ASSERT_HR(presults->ComputeMemberForces(0, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 2.0));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, -2.0));
      ASSERT_TRUE(IsEqual(emz, 8.0));
      ASSERT_HR(presults->ComputeMemberForces(0, 2, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, -2.0));
      ASSERT_TRUE(IsEqual(smz, -8.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 2.0));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      ASSERT_HR(presultsex->ComputeMemberForcesEx(0, 1, lotMember, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 2.0));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, -2.0));
      ASSERT_TRUE(IsEqual(emz, 8.0));
      ASSERT_HR(presultsex->ComputeMemberForcesEx(0, 2, lotMember, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, -2.0));
      ASSERT_TRUE(IsEqual(smz, -8.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 2.0));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      ASSERT_HR(presultsex->ComputeMemberForcesEx(0, 1, lotGlobal, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, -1.41421356));
      ASSERT_TRUE(IsEqual(sfy, 1.41421356));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 1.41421355));
      ASSERT_TRUE(IsEqual(efy, -1.41421355));
      ASSERT_TRUE(IsEqual(emz, 8.0));
      ASSERT_HR(presultsex->ComputeMemberForcesEx(0, 2, lotGlobal, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 1.41421355));
      ASSERT_TRUE(IsEqual(sfy, -1.41421355));
      ASSERT_TRUE(IsEqual(smz, -8.0));
      ASSERT_TRUE(IsEqual(efx, -1.41421356));
      ASSERT_TRUE(IsEqual(efy, 1.41421356));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      ASSERT_HR(presults->ComputeReactions(0, 0, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -1.41421356));
      ASSERT_TRUE(IsEqual(fy, 1.41421356));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputeReactions(0, 4, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputeReactions(0, 8, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -1.41421356));
      ASSERT_TRUE(IsEqual(fy, 1.41421356));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      ASSERT_EQ(presults->ComputeReactions(1, 8, &fx, &fy, &mz), FEM2D_E_LOADING_NOT_FOUND);
      ASSERT_EQ(presults->ComputeReactions(0, 12, &fx, &fy, &mz), FEM2D_E_JOINT_NOT_FOUND);

      ASSERT_HR(presults->ComputeMemberDeflections(0, 1, &sdx, &sdy, &srz, &edx, &edy, &erz));
      ASSERT_TRUE(IsEqual(sdx, 0.0));
      ASSERT_TRUE(IsEqual(sdy, 0.0));
      ASSERT_TRUE(IsEqual(srz, -2.2857142857143));
      ASSERT_TRUE(IsEqual(edx, 0.0));
      ASSERT_TRUE(IsEqual(edy, -6.0952380952381));
      ASSERT_TRUE(IsEqual(erz, 0.0));
      ASSERT_HR(presults->ComputeMemberDeflections(0, 2, &sdx, &sdy, &srz, &edx, &edy, &erz));
      ASSERT_TRUE(IsEqual(sdx, 0.0));
      ASSERT_TRUE(IsEqual(sdy, -6.0952380952381));
      ASSERT_TRUE(IsEqual(srz, 0.0));
      ASSERT_TRUE(IsEqual(edx, 0.0));
      ASSERT_TRUE(IsEqual(edy, 0.0));
      ASSERT_TRUE(IsEqual(erz, 2.2857142857143));

      ASSERT_HR(presults->ComputePOIDeflections(0, 10, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -2.2857142857143));
      ASSERT_HR(presults->ComputePOIDeflections(0, 15, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -4.1904761904762));
      ASSERT_TRUE(IsEqual(rz, -1.71428));
      ASSERT_HR(presults->ComputePOIDeflections(0, 12, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -6.0952380952381));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(0, 20, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -6.0952380952381));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(0, 25, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -4.1904761904762));
      ASSERT_TRUE(IsEqual(rz, 1.71428));
      ASSERT_HR(presults->ComputePOIDeflections(0, 22, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 2.2857142857143));

      ASSERT_HR(presults->ComputePOIDeflections(0, 10, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -2.2857142857143));
      ASSERT_HR(presults->ComputePOIDeflections(0, 15, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 2.9631141));
      ASSERT_TRUE(IsEqual(dy, -2.9631141));
      ASSERT_TRUE(IsEqual(rz, -1.71428));
      ASSERT_HR(presults->ComputePOIDeflections(0, 12, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 4.3099842));
      ASSERT_TRUE(IsEqual(dy, -4.3099842));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(0, 20, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 4.3099842));
      ASSERT_TRUE(IsEqual(dy, -4.3099842));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(0, 25, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 2.9631141));
      ASSERT_TRUE(IsEqual(dy, -2.9631141));
      ASSERT_TRUE(IsEqual(rz, 1.71428));
      ASSERT_HR(presults->ComputePOIDeflections(0, 22, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 2.2857142857143));

      ASSERT_HR(presults->ComputePOIForces(0, 10, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 1.41421355));
      ASSERT_TRUE(IsEqual(fy, -1.41421355));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(0, 10, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(0, 10, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(0, 10, mftRight, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      ASSERT_HR(presults->ComputePOIForces(0, 15, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 1.41421355));
      ASSERT_TRUE(IsEqual(fy, -1.41421355));
      ASSERT_TRUE(IsEqual(mz, 4.0));
      ASSERT_HR(presults->ComputePOIForces(0, 15, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, -4.0));
      ASSERT_HR(presults->ComputePOIForces(0, 15, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, 4.0));
      ASSERT_HR(presults->ComputePOIForces(0, 15, mftRight, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, -4.0));

      ASSERT_HR(presults->ComputePOIForces(0, 12, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 1.41421355));
      ASSERT_TRUE(IsEqual(fy, -1.41421355));
      ASSERT_TRUE(IsEqual(mz, 8.0));
      ASSERT_HR(presults->ComputePOIForces(0, 12, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, -8.0));
      ASSERT_HR(presults->ComputePOIForces(0, 12, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, 8.0));
      ASSERT_HR(presults->ComputePOIForces(0, 12, mftRight, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, -8.0));

      ASSERT_HR(presults->ComputePOIForces(0, 20, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, 8.0));
      ASSERT_HR(presults->ComputePOIForces(0, 20, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 1.41421355));
      ASSERT_TRUE(IsEqual(fy, -1.41421355));
      ASSERT_TRUE(IsEqual(mz, -8.0));
      ASSERT_HR(presults->ComputePOIForces(0, 20, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, 8.0));
      ASSERT_HR(presults->ComputePOIForces(0, 20, mftRight, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, -8.0));

      ASSERT_HR(presults->ComputePOIForces(0, 25, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, 4.0));
      ASSERT_HR(presults->ComputePOIForces(0, 25, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 1.41421355));
      ASSERT_TRUE(IsEqual(fy, -1.41421355));
      ASSERT_TRUE(IsEqual(mz, -4.0));
      ASSERT_HR(presults->ComputePOIForces(0, 25, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, 4.0));
      ASSERT_HR(presults->ComputePOIForces(0, 25, mftRight, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, -4.0));

      //////////////////////////////////////////////////////////////////////////////////
      // next let's rotate the model 135 degrees clockwise
      ASSERT_MC(fixture, pJoint4->put_X(-2.8284271));
      ASSERT_HR(pJoint4->put_Y(2.8284271));
      ASSERT_MC(fixture, pJoint8->put_X(-5.6568542));
      ASSERT_HR(pJoint8->put_Y(5.6568542));

      pMember1->get_Length(&l);
      ASSERT_TRUE(IsEqual(l, 4.0));
      pMember2->get_Length(&l);
      ASSERT_TRUE(IsEqual(l, 4.0));

      ASSERT_HR(pJointLoad->put_Fx(2.8284271));
      ASSERT_LC(fixture, pJointLoad->put_Fy(2.8284271));

      ASSERT_HR(presults->ComputeJointDeflections(0, 0, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -2.2857142857143));
      ASSERT_HR(presults->ComputeJointDeflections(0, 4, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 4.30998419));
      ASSERT_TRUE(IsEqual(dy, 4.30998419));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputeJointDeflections(0, 8, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 2.2857142857143));

      ASSERT_HR(presults->ComputeMemberForces(0, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 2.0));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, -2.0));
      ASSERT_TRUE(IsEqual(emz, 8.0));
      ASSERT_HR(presults->ComputeMemberForces(0, 2, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, -2.0));
      ASSERT_TRUE(IsEqual(smz, -8.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 2.0));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      ASSERT_HR(presultsex->ComputeMemberForcesEx(0, 1, lotMember, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 2.0));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, -2.0));
      ASSERT_TRUE(IsEqual(emz, 8.0));
      ASSERT_HR(presultsex->ComputeMemberForcesEx(0, 2, lotMember, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, -2.0));
      ASSERT_TRUE(IsEqual(smz, -8.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 2.0));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      ASSERT_HR(presultsex->ComputeMemberForcesEx(0, 1, lotGlobal, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, -1.41421356));
      ASSERT_TRUE(IsEqual(sfy, -1.41421356));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 1.41421355));
      ASSERT_TRUE(IsEqual(efy, 1.41421355));
      ASSERT_TRUE(IsEqual(emz, 8.0));
      ASSERT_HR(presultsex->ComputeMemberForcesEx(0, 2, lotGlobal, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 1.41421355));
      ASSERT_TRUE(IsEqual(sfy, 1.41421355));
      ASSERT_TRUE(IsEqual(smz, -8.0));
      ASSERT_TRUE(IsEqual(efx, -1.41421356));
      ASSERT_TRUE(IsEqual(efy, -1.41421356));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      ASSERT_HR(presults->ComputeReactions(0, 0, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -1.41421356));
      ASSERT_TRUE(IsEqual(fy, -1.41421356));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputeReactions(0, 4, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputeReactions(0, 8, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -1.41421356));
      ASSERT_TRUE(IsEqual(fy, -1.41421356));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      ASSERT_HR(presults->ComputeMemberDeflections(0, 1, &sdx, &sdy, &srz, &edx, &edy, &erz));
      ASSERT_TRUE(IsEqual(sdx, 0.0));
      ASSERT_TRUE(IsEqual(sdy, 0.0));
      ASSERT_TRUE(IsEqual(srz, -2.2857142857143));
      ASSERT_TRUE(IsEqual(edx, 0.0));
      ASSERT_TRUE(IsEqual(edy, -6.0952380952381));
      ASSERT_TRUE(IsEqual(erz, 0.0));
      ASSERT_HR(presults->ComputeMemberDeflections(0, 2, &sdx, &sdy, &srz, &edx, &edy, &erz));
      ASSERT_TRUE(IsEqual(sdx, 0.0));
      ASSERT_TRUE(IsEqual(sdy, -6.0952380952381));
      ASSERT_TRUE(IsEqual(srz, 0.0));
      ASSERT_TRUE(IsEqual(edx, 0.0));
      ASSERT_TRUE(IsEqual(edy, 0.0));
      ASSERT_TRUE(IsEqual(erz, 2.2857142857143));

      ASSERT_HR(presults->ComputePOIDeflections(0, 10, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -2.2857142857143));
      ASSERT_HR(presults->ComputePOIDeflections(0, 15, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -4.1904761904762));
      ASSERT_TRUE(IsEqual(rz, -1.71428));
      ASSERT_HR(presults->ComputePOIDeflections(0, 12, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -6.0952380952381));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(0, 20, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -6.0952380952381));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(0, 25, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -4.1904761904762));
      ASSERT_TRUE(IsEqual(rz, 1.71428));
      ASSERT_HR(presults->ComputePOIDeflections(0, 22, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 2.2857142857143));

      ASSERT_HR(presults->ComputePOIDeflections(0, 10, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -2.2857142857143));
      ASSERT_HR(presults->ComputePOIDeflections(0, 15, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 2.9631141));
      ASSERT_TRUE(IsEqual(dy, 2.9631141));
      ASSERT_TRUE(IsEqual(rz, -1.71428));
      ASSERT_HR(presults->ComputePOIDeflections(0, 12, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 4.3099842));
      ASSERT_TRUE(IsEqual(dy, 4.3099842));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(0, 20, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 4.3099842));
      ASSERT_TRUE(IsEqual(dy, 4.3099842));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(0, 25, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 2.9631141));
      ASSERT_TRUE(IsEqual(dy, 2.9631141));
      ASSERT_TRUE(IsEqual(rz, 1.71428));
      ASSERT_HR(presults->ComputePOIDeflections(0, 22, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 2.2857142857143));

      ASSERT_HR(presults->ComputePOIForces(0, 10, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(0, 10, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, -1.41421355));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(0, 10, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(0, 10, mftRight, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      ASSERT_HR(presults->ComputePOIForces(0, 15, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, 4.0));
      ASSERT_HR(presults->ComputePOIForces(0, 15, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, -1.41421355));
      ASSERT_TRUE(IsEqual(mz, -4.0));
      ASSERT_HR(presults->ComputePOIForces(0, 15, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, 4.0));
      ASSERT_HR(presults->ComputePOIForces(0, 15, mftRight, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, -4.0));

      ASSERT_HR(presults->ComputePOIForces(0, 12, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, 8.0));
      ASSERT_HR(presults->ComputePOIForces(0, 12, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, -1.41421355));
      ASSERT_TRUE(IsEqual(mz, -8.0));
      ASSERT_HR(presults->ComputePOIForces(0, 12, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, 8.0));
      ASSERT_HR(presults->ComputePOIForces(0, 12, mftRight, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, -8.0));

      ASSERT_HR(presults->ComputePOIForces(0, 20, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, -1.41421355));
      ASSERT_TRUE(IsEqual(mz, 8.0));
      ASSERT_HR(presults->ComputePOIForces(0, 20, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, -8.0));
      ASSERT_HR(presults->ComputePOIForces(0, 20, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, 8.0));
      ASSERT_HR(presults->ComputePOIForces(0, 20, mftRight, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, -8.0));

      ASSERT_HR(presults->ComputePOIForces(0, 25, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, -1.41421355));
      ASSERT_TRUE(IsEqual(mz, 4.0));
      ASSERT_HR(presults->ComputePOIForces(0, 25, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, -4.0));
      ASSERT_HR(presults->ComputePOIForces(0, 25, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, 4.0));
      ASSERT_HR(presults->ComputePOIForces(0, 25, mftRight, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, -4.0));

      //////////////////////////////////////////////////////////////////////////////////
      // Rotate the model 225 degrees clockwise
      ASSERT_HR(pJoint4->put_X(-2.8284271));
      ASSERT_MC(fixture, pJoint4->put_Y(-2.8284271));
      ASSERT_HR(pJoint8->put_X(-5.6568542));
      ASSERT_MC(fixture, pJoint8->put_Y(-5.6568542));

      pMember1->get_Length(&l);
      ASSERT_TRUE(IsEqual(l, 4.0));
      pMember2->get_Length(&l);
      ASSERT_TRUE(IsEqual(l, 4.0));

      ASSERT_LC(fixture, pJointLoad->put_Fx(-2.8284271));
      ASSERT_HR(pJointLoad->put_Fy(2.8284271));

      ASSERT_HR(presults->ComputeJointDeflections(0, 0, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -2.2857142857143));
      ASSERT_HR(presults->ComputeJointDeflections(0, 4, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, -4.30998419));
      ASSERT_TRUE(IsEqual(dy, 4.30998419));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputeJointDeflections(0, 8, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 2.2857142857143));

      ASSERT_HR(presults->ComputeMemberForces(0, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 2.0));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, -2.0));
      ASSERT_TRUE(IsEqual(emz, 8.0));
      ASSERT_HR(presults->ComputeMemberForces(0, 2, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, -2.0));
      ASSERT_TRUE(IsEqual(smz, -8.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 2.0));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      ASSERT_HR(presultsex->ComputeMemberForcesEx(0, 1, lotMember, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 2.0));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, -2.0));
      ASSERT_TRUE(IsEqual(emz, 8.0));
      ASSERT_HR(presultsex->ComputeMemberForcesEx(0, 2, lotMember, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, -2.0));
      ASSERT_TRUE(IsEqual(smz, -8.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 2.0));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      ASSERT_HR(presultsex->ComputeMemberForcesEx(0, 1, lotGlobal, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 1.41421356));
      ASSERT_TRUE(IsEqual(sfy, -1.41421356));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, -1.41421355));
      ASSERT_TRUE(IsEqual(efy, 1.41421355));
      ASSERT_TRUE(IsEqual(emz, 8.0));
      ASSERT_HR(presultsex->ComputeMemberForcesEx(0, 2, lotGlobal, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, -1.41421355));
      ASSERT_TRUE(IsEqual(sfy, 1.41421355));
      ASSERT_TRUE(IsEqual(smz, -8.0));
      ASSERT_TRUE(IsEqual(efx, 1.41421356));
      ASSERT_TRUE(IsEqual(efy, -1.41421356));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      ASSERT_HR(presults->ComputeReactions(0, 0, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 1.41421356));
      ASSERT_TRUE(IsEqual(fy, -1.41421356));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputeReactions(0, 4, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputeReactions(0, 8, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 1.41421356));
      ASSERT_TRUE(IsEqual(fy, -1.41421356));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      ASSERT_HR(presults->ComputeMemberDeflections(0, 1, &sdx, &sdy, &srz, &edx, &edy, &erz));
      ASSERT_TRUE(IsEqual(sdx, 0.0));
      ASSERT_TRUE(IsEqual(sdy, 0.0));
      ASSERT_TRUE(IsEqual(srz, -2.2857142857143));
      ASSERT_TRUE(IsEqual(edx, 0.0));
      ASSERT_TRUE(IsEqual(edy, -6.0952380952381));
      ASSERT_TRUE(IsEqual(erz, 0.0));
      ASSERT_HR(presults->ComputeMemberDeflections(0, 2, &sdx, &sdy, &srz, &edx, &edy, &erz));
      ASSERT_TRUE(IsEqual(sdx, 0.0));
      ASSERT_TRUE(IsEqual(sdy, -6.0952380952381));
      ASSERT_TRUE(IsEqual(srz, 0.0));
      ASSERT_TRUE(IsEqual(edx, 0.0));
      ASSERT_TRUE(IsEqual(edy, 0.0));
      ASSERT_TRUE(IsEqual(erz, 2.2857142857143));

      ASSERT_HR(presults->ComputePOIDeflections(0, 10, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -2.2857142857143));
      ASSERT_HR(presults->ComputePOIDeflections(0, 15, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -4.1904761904762));
      ASSERT_TRUE(IsEqual(rz, -1.71428));
      ASSERT_HR(presults->ComputePOIDeflections(0, 12, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -6.0952380952381));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(0, 20, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -6.0952380952381));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(0, 25, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -4.1904761904762));
      ASSERT_TRUE(IsEqual(rz, 1.71428));
      ASSERT_HR(presults->ComputePOIDeflections(0, 22, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 2.2857142857143));

      ASSERT_HR(presults->ComputePOIDeflections(0, 10, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -2.2857142857143));
      ASSERT_HR(presults->ComputePOIDeflections(0, 15, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, -2.9631141));
      ASSERT_TRUE(IsEqual(dy, 2.9631141));
      ASSERT_TRUE(IsEqual(rz, -1.71428));
      ASSERT_HR(presults->ComputePOIDeflections(0, 12, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, -4.3099842));
      ASSERT_TRUE(IsEqual(dy, 4.3099842));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(0, 20, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, -4.3099842));
      ASSERT_TRUE(IsEqual(dy, 4.3099842));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(0, 25, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, -2.9631141));
      ASSERT_TRUE(IsEqual(dy, 2.9631141));
      ASSERT_TRUE(IsEqual(rz, 1.71428));
      ASSERT_HR(presults->ComputePOIDeflections(0, 22, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 2.2857142857143));

      ASSERT_HR(presults->ComputePOIForces(0, 10, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(0, 10, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 1.41421355));
      ASSERT_TRUE(IsEqual(fy, -1.41421355));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(0, 10, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(0, 10, mftRight, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      ASSERT_HR(presults->ComputePOIForces(0, 15, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, 4.0));
      ASSERT_HR(presults->ComputePOIForces(0, 15, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 1.41421355));
      ASSERT_TRUE(IsEqual(fy, -1.41421355));
      ASSERT_TRUE(IsEqual(mz, -4.0));
      ASSERT_HR(presults->ComputePOIForces(0, 15, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, 4.0));
      ASSERT_HR(presults->ComputePOIForces(0, 15, mftRight, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, -4.0));

      ASSERT_HR(presults->ComputePOIForces(0, 12, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, 8.0));
      ASSERT_HR(presults->ComputePOIForces(0, 12, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 1.41421355));
      ASSERT_TRUE(IsEqual(fy, -1.41421355));
      ASSERT_TRUE(IsEqual(mz, -8.0));
      ASSERT_HR(presults->ComputePOIForces(0, 12, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, 8.0));
      ASSERT_HR(presults->ComputePOIForces(0, 12, mftRight, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, -8.0));

      ASSERT_HR(presults->ComputePOIForces(0, 20, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 1.41421355));
      ASSERT_TRUE(IsEqual(fy, -1.41421355));
      ASSERT_TRUE(IsEqual(mz, 8.0));
      ASSERT_HR(presults->ComputePOIForces(0, 20, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, -8.0));
      ASSERT_HR(presults->ComputePOIForces(0, 20, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, 8.0));
      ASSERT_HR(presults->ComputePOIForces(0, 20, mftRight, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, -8.0));

      ASSERT_HR(presults->ComputePOIForces(0, 25, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 1.41421355));
      ASSERT_TRUE(IsEqual(fy, -1.41421355));
      ASSERT_TRUE(IsEqual(mz, 4.0));
      ASSERT_HR(presults->ComputePOIForces(0, 25, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, -4.0));
      ASSERT_HR(presults->ComputePOIForces(0, 25, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, 4.0));
      ASSERT_HR(presults->ComputePOIForces(0, 25, mftRight, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, -4.0));

      //////////////////////////////////////////////////////////////////////////////////
      // Rotate the model -45 degrees clockwise
      ASSERT_MC(fixture, pJoint4->put_X(2.8284271));
      ASSERT_HR(pJoint4->put_Y(-2.8284271));
      ASSERT_MC(fixture, pJoint8->put_X(5.6568542));
      ASSERT_HR(pJoint8->put_Y(-5.6568542));

      pMember1->get_Length(&l);
      ASSERT_TRUE(IsEqual(l, 4.0));
      pMember2->get_Length(&l);
      ASSERT_TRUE(IsEqual(l, 4.0));

      ASSERT_HR(pJointLoad->put_Fx(-2.8284271));
      ASSERT_LC(fixture, pJointLoad->put_Fy(-2.8284271));

      ASSERT_HR(presults->ComputeJointDeflections(0, 0, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -2.2857142857143));
      ASSERT_HR(presults->ComputeJointDeflections(0, 4, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, -4.30998419));
      ASSERT_TRUE(IsEqual(dy, -4.30998419));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputeJointDeflections(0, 8, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 2.2857142857143));

      ASSERT_HR(presults->ComputeMemberForces(0, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 2.0));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, -2.0));
      ASSERT_TRUE(IsEqual(emz, 8.0));
      ASSERT_HR(presults->ComputeMemberForces(0, 2, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, -2.0));
      ASSERT_TRUE(IsEqual(smz, -8.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 2.0));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      ASSERT_HR(presultsex->ComputeMemberForcesEx(0, 1, lotMember, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 2.0));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, -2.0));
      ASSERT_TRUE(IsEqual(emz, 8.0));
      ASSERT_HR(presultsex->ComputeMemberForcesEx(0, 2, lotMember, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, -2.0));
      ASSERT_TRUE(IsEqual(smz, -8.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 2.0));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      ASSERT_HR(presultsex->ComputeMemberForcesEx(0, 1, lotGlobal, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 1.41421356));
      ASSERT_TRUE(IsEqual(sfy, 1.41421356));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, -1.41421355));
      ASSERT_TRUE(IsEqual(efy, -1.41421355));
      ASSERT_TRUE(IsEqual(emz, 8.0));
      ASSERT_HR(presultsex->ComputeMemberForcesEx(0, 2, lotGlobal, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, -1.41421355));
      ASSERT_TRUE(IsEqual(sfy, -1.41421355));
      ASSERT_TRUE(IsEqual(smz, -8.0));
      ASSERT_TRUE(IsEqual(efx, 1.41421356));
      ASSERT_TRUE(IsEqual(efy, 1.41421356));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      ASSERT_HR(presults->ComputeReactions(0, 0, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 1.41421356));
      ASSERT_TRUE(IsEqual(fy, 1.41421356));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputeReactions(0, 4, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputeReactions(0, 8, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 1.41421356));
      ASSERT_TRUE(IsEqual(fy, 1.41421356));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      ASSERT_HR(presults->ComputeMemberDeflections(0, 1, &sdx, &sdy, &srz, &edx, &edy, &erz));
      ASSERT_TRUE(IsEqual(sdx, 0.0));
      ASSERT_TRUE(IsEqual(sdy, 0.0));
      ASSERT_TRUE(IsEqual(srz, -2.2857142857143));
      ASSERT_TRUE(IsEqual(edx, 0.0));
      ASSERT_TRUE(IsEqual(edy, -6.0952380952381));
      ASSERT_TRUE(IsEqual(erz, 0.0));
      ASSERT_HR(presults->ComputeMemberDeflections(0, 2, &sdx, &sdy, &srz, &edx, &edy, &erz));
      ASSERT_TRUE(IsEqual(sdx, 0.0));
      ASSERT_TRUE(IsEqual(sdy, -6.0952380952381));
      ASSERT_TRUE(IsEqual(srz, 0.0));
      ASSERT_TRUE(IsEqual(edx, 0.0));
      ASSERT_TRUE(IsEqual(edy, 0.0));
      ASSERT_TRUE(IsEqual(erz, 2.2857142857143));

      ASSERT_HR(presults->ComputePOIDeflections(0, 10, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -2.2857142857143));
      ASSERT_HR(presults->ComputePOIDeflections(0, 15, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -4.1904761904762));
      ASSERT_TRUE(IsEqual(rz, -1.71428));
      ASSERT_HR(presults->ComputePOIDeflections(0, 12, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -6.0952380952381));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(0, 20, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -6.0952380952381));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(0, 25, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -4.1904761904762));
      ASSERT_TRUE(IsEqual(rz, 1.71428));
      ASSERT_HR(presults->ComputePOIDeflections(0, 22, lotMember, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 2.2857142857143));

      ASSERT_HR(presults->ComputePOIDeflections(0, 10, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -2.2857142857143));
      ASSERT_HR(presults->ComputePOIDeflections(0, 15, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, -2.9631141));
      ASSERT_TRUE(IsEqual(dy, -2.9631141));
      ASSERT_TRUE(IsEqual(rz, -1.71428));
      ASSERT_HR(presults->ComputePOIDeflections(0, 12, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, -4.3099842));
      ASSERT_TRUE(IsEqual(dy, -4.3099842));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(0, 20, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, -4.3099842));
      ASSERT_TRUE(IsEqual(dy, -4.3099842));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(0, 25, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, -2.9631141));
      ASSERT_TRUE(IsEqual(dy, -2.9631141));
      ASSERT_TRUE(IsEqual(rz, 1.71428));
      ASSERT_HR(presults->ComputePOIDeflections(0, 22, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 2.2857142857143));

      ASSERT_HR(presults->ComputePOIForces(0, 10, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, -1.41421355));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(0, 10, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(0, 10, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(0, 10, mftRight, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      ASSERT_HR(presults->ComputePOIForces(0, 15, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, -1.41421355));
      ASSERT_TRUE(IsEqual(mz, 4.0));
      ASSERT_HR(presults->ComputePOIForces(0, 15, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, -4.0));
      ASSERT_HR(presults->ComputePOIForces(0, 15, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, 4.0));
      ASSERT_HR(presults->ComputePOIForces(0, 15, mftRight, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, -4.0));

      ASSERT_HR(presults->ComputePOIForces(0, 12, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, -1.41421355));
      ASSERT_TRUE(IsEqual(mz, 8.0));
      ASSERT_HR(presults->ComputePOIForces(0, 12, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, -8.0));
      ASSERT_HR(presults->ComputePOIForces(0, 12, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, 8.0));
      ASSERT_HR(presults->ComputePOIForces(0, 12, mftRight, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, -8.0));

      ASSERT_HR(presults->ComputePOIForces(0, 20, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, 8.0));
      ASSERT_HR(presults->ComputePOIForces(0, 20, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, -1.41421355));
      ASSERT_TRUE(IsEqual(mz, -8.0));
      ASSERT_HR(presults->ComputePOIForces(0, 20, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, 8.0));
      ASSERT_HR(presults->ComputePOIForces(0, 20, mftRight, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, -8.0));

      ASSERT_HR(presults->ComputePOIForces(0, 25, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, 4.0));
      ASSERT_HR(presults->ComputePOIForces(0, 25, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, -1.41421355));
      ASSERT_TRUE(IsEqual(mz, -4.0));
      ASSERT_HR(presults->ComputePOIForces(0, 25, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, 4.0));
      ASSERT_HR(presults->ComputePOIForces(0, 25, mftRight, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, -4.0));
   }
};
} // namespace Fem2dUnitTests
