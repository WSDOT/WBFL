///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
///////////////////////////////////////////////////////////////////////
// TestSimpleBeamWithPointLoad.cpp
//
// Ported from F:\ARP\WBFL\Fem2d\Test\TestSimpleBeamWithPointLoad.cpp (Test1)
// and TestSimpleBeamWithPointLoad12.cpp (Test2) - merged into a single
// TEST_METHOD since the legacy split was purely due to old compiler
// function-size limits.
#include "pch.h"

namespace Fem2dUnitTests
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
      Fem2dModelFixture fixture;
      CComPtr<IFem2dModel>& pmodel = fixture.Model;

      CComPtr<IFem2dJointCollection> pJoints;
      ASSERT_HR(pmodel->get_Joints(&pJoints));

      CComPtr<IFem2dJoint> pJoint0, pJoint8;
      ASSERT_MC(fixture, pJoints->Create(0, 0.0, 0.0, &pJoint0));
      ASSERT_MC(fixture, pJoints->Create(8, 8.0, 0.0, &pJoint8));

      ASSERT_MC(fixture, pJoint0->Support());
      ASSERT_MC(fixture, pJoint0->ReleaseDof(jrtMz));
      ASSERT_MC(fixture, pJoint8->Support());
      ASSERT_MC(fixture, pJoint8->ReleaseDof(jrtFx));
      ASSERT_MC(fixture, pJoint8->ReleaseDof(jrtMz));

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
      ASSERT_LC(fixture, pPointLoads->Create(0, 1, 4.0, 0.0, -4.0, 0.0, lotGlobal, &pPointLoad));

      // POI's at 1/4 points in member 1 - these results are pre-calculated
      CComPtr<IFem2dPOICollection> pPOIs;
      ASSERT_HR(pmodel->get_POIs(&pPOIs));

      CComPtr<IFem2dPOI> pPOI10, pPOI15, pPOI12;
      ASSERT_HR(pPOIs->Create(10, 1, 0.0, &pPOI10));
      ASSERT_HR(pPOIs->Create(15, 1, -.25, &pPOI15));
      ASSERT_HR(pPOIs->Create(12, 1, -0.5, &pPOI12));

      {
         // save model off to a file (also exercised by TestPersistence, but
         // this matches the original test's coverage of the save-path here)
         CComPtr<IStructuredSave2> psave;
         ASSERT_HR(psave.CoCreateInstance(CLSID_StructuredSave2));
         Assert::IsTrue(psave != nullptr);

         ASSERT_HR(psave->Open(CComBSTR("TestSimpleBeamWithPointLoad.xml")));

         IStructuredStorage2* pstor;
         ASSERT_HR(pmodel->QueryInterface(&pstor));
         ASSERT_HR(pstor->Save(psave));
         ASSERT_HR(psave->Close());
         pstor->Release();
      }

      CComQIPtr<IFem2dModelResults> presults(pmodel);
      CComQIPtr<IFem2dModelResultsEx> presultsex(pmodel);

      Float64 dx, dy, rz;
      ASSERT_HR(presults->ComputeJointDeflections(0, 0, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -2.2857142857143));
      ASSERT_HR(presults->ComputeJointDeflections(0, 8, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 2.2857142857143));

      Float64 sfx, sfy, smz, efx, efy, emz;
      ASSERT_HR(presults->ComputeMemberForces(0, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 2.0));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 2.0));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      ASSERT_HR(presultsex->ComputeMemberForcesEx(0, 1, lotGlobal, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 2.0));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 2.0));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      ASSERT_HR(presultsex->ComputeMemberForcesEx(0, 1, lotMember, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 2.0));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 2.0));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      Float64 fx, fy, mz;
      ASSERT_HR(presults->ComputeReactions(0, 0, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputeReactions(0, 8, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 2.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      Float64 sdx, sdy, srz, edx, edy, erz;
      ASSERT_HR(presults->ComputeMemberDeflections(0, 1, &sdx, &sdy, &srz, &edx, &edy, &erz));
      ASSERT_TRUE(IsEqual(sdx, 0.0));
      ASSERT_TRUE(IsEqual(sdy, 0.0));
      ASSERT_TRUE(IsEqual(srz, -2.2857142857143));
      ASSERT_TRUE(IsEqual(edx, 0.0));
      ASSERT_TRUE(IsEqual(edy, 0.0));
      ASSERT_TRUE(IsEqual(erz, 2.2857142857143));

      // POI's at 1/4 points of second half - calculated on the fly
      CComPtr<IFem2dPOI> pPOI20, pPOI25, pPOI22;
      ASSERT_HR(pPOIs->Create(20, 1, 4.0, &pPOI20));
      ASSERT_HR(pPOIs->Create(25, 1, 6.0, &pPOI25));
      ASSERT_HR(pPOIs->Create(22, 1, 8.0, &pPOI22));

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

      ASSERT_HR(presults->ComputePOIDeflections(0, 10, lotGlobalProjected, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -2.2857142857143));
      ASSERT_HR(presults->ComputePOIDeflections(0, 15, lotGlobalProjected, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -4.1904761904762));
      ASSERT_TRUE(IsEqual(rz, -1.71428));
      ASSERT_HR(presults->ComputePOIDeflections(0, 12, lotGlobalProjected, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -6.0952380952381));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(0, 20, lotGlobalProjected, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -6.0952380952381));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(0, 25, lotGlobalProjected, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -4.1904761904762));
      ASSERT_TRUE(IsEqual(rz, 1.71428));
      ASSERT_HR(presults->ComputePOIDeflections(0, 22, lotGlobalProjected, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 2.2857142857143));

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
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, -8.0));
      ASSERT_HR(presults->ComputePOIForces(0, 12, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, 8.0));
      ASSERT_HR(presults->ComputePOIForces(0, 12, mftRight, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, -8.0));

      ASSERT_HR(presults->ComputePOIForces(0, 20, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, 8.0));
      ASSERT_HR(presults->ComputePOIForces(0, 20, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
      ASSERT_TRUE(IsEqual(mz, -8.0));
      ASSERT_HR(presults->ComputePOIForces(0, 20, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
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

      //////////////////////////////////////////////////////////////////////////////////
      // add a new load case with a horizontal load at the middle
      CComPtr<IFem2dLoading> pLoading2;
      ASSERT_LC(fixture, pLoadings->Create(2, &pLoading2));
      CComPtr<IFem2dPointLoadCollection> pPointLoads2;
      ASSERT_HR(pLoading2->get_PointLoads(&pPointLoads2));

      CComPtr<IFem2dPointLoad> pPointLoad2;
      ASSERT_LC(fixture, pPointLoads2->Create(0, 1, 4.0, 2.0, 0.0, 0.0, lotGlobal, &pPointLoad2));

      ASSERT_HR(presults->ComputeJointDeflections(2, 0, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
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
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 0.0));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      ASSERT_HR(presultsex->ComputeMemberForcesEx(2, 1, lotGlobal, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, -2.0));
      ASSERT_TRUE(IsEqual(sfy, 0.0));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 0.0));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      ASSERT_HR(presultsex->ComputeMemberForcesEx(2, 1, lotMember, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, -2.0));
      ASSERT_TRUE(IsEqual(sfy, 0.0));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 0.0));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      ASSERT_HR(presults->ComputeReactions(2, 0, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -2.0));
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

      ASSERT_HR(presults->ComputePOIDeflections(2, 10, lotGlobalProjected, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(2, 15, lotGlobalProjected, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 1.333333));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(2, 12, lotGlobalProjected, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 2.6666667));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(2, 20, lotGlobalProjected, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 2.6666667));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(2, 25, lotGlobalProjected, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 2.6666667));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(2, 22, lotGlobalProjected, &dx, &dy, &rz));
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
      ASSERT_HR(presults->ComputePOIForces(2, 10, mftLeft, lotGlobalProjected, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 2.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(2, 10, mftRight, lotGlobalProjected, &fx, &fy, &mz));
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
      ASSERT_HR(presults->ComputePOIForces(2, 15, mftLeft, lotGlobalProjected, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 2.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(2, 15, mftRight, lotGlobalProjected, &fx, &fy, &mz));
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
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(2, 12, mftLeft, lotGlobalProjected, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 2.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(2, 12, mftRight, lotGlobalProjected, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(2, 12, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 2.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(2, 12, mftRight, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      ASSERT_HR(presults->ComputePOIForces(2, 20, mftLeft, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 2.0));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(2, 20, mftRight, lotGlobal, &fx, &fy, &mz));
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

      //////////////////////////////////////////////////////////////////////////////////
      // next let's rotate the model 45 degrees clockwise
      ASSERT_MC(fixture, pJoint8->put_X(5.6568542));
      ASSERT_MC(fixture, pJoint8->put_Y(5.6568542));

      // don't allow end joint to translate
      ASSERT_MC(fixture, pJoint8->Support());
      ASSERT_MC(fixture, pJoint8->ReleaseDof(jrtMz));

      Float64 l;
      pMember1->get_Length(&l);
      ASSERT_TRUE(IsEqual(l, 8.0));

      // change orientation of point load to be normal to rotated structure
      ASSERT_LC(fixture, pPointLoad->put_Fx(2.8284271));
      ASSERT_LC(fixture, pPointLoad->put_Fy(-2.8284271));

      ASSERT_HR(presults->ComputeJointDeflections(0, 0, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -2.2857142857143));
      ASSERT_HR(presults->ComputeJointDeflections(0, 8, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 2.2857142857143));

      ASSERT_HR(presults->ComputeMemberForces(0, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 2.0));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 2.0));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      ASSERT_HR(presultsex->ComputeMemberForcesEx(0, 1, lotGlobal, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, -1.41421356));
      ASSERT_TRUE(IsEqual(sfy, 1.41421356));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, -1.41421356));
      ASSERT_TRUE(IsEqual(efy, 1.41421356));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      ASSERT_HR(presultsex->ComputeMemberForcesEx(0, 1, lotMember, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 2.0));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 2.0));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      ASSERT_HR(presults->ComputeReactions(0, 0, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -1.41421356));
      ASSERT_TRUE(IsEqual(fy, 1.41421356));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputeReactions(0, 8, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -1.41421356));
      ASSERT_TRUE(IsEqual(fy, 1.41421356));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      ASSERT_HR(presults->ComputeMemberDeflections(0, 1, &sdx, &sdy, &srz, &edx, &edy, &erz));
      ASSERT_TRUE(IsEqual(sdx, 0.0));
      ASSERT_TRUE(IsEqual(sdy, 0.0));
      ASSERT_TRUE(IsEqual(srz, -2.2857142857143));
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

      ASSERT_HR(presults->ComputePOIDeflections(0, 10, lotGlobalProjected, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -2.2857142857143));
      ASSERT_HR(presults->ComputePOIDeflections(0, 15, lotGlobalProjected, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 2.9631141));
      ASSERT_TRUE(IsEqual(dy, -2.9631141));
      ASSERT_TRUE(IsEqual(rz, -1.71428));
      ASSERT_HR(presults->ComputePOIDeflections(0, 12, lotGlobalProjected, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 4.3099842));
      ASSERT_TRUE(IsEqual(dy, -4.3099842));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(0, 20, lotGlobalProjected, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 4.3099842));
      ASSERT_TRUE(IsEqual(dy, -4.3099842));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(0, 25, lotGlobalProjected, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 2.9631141));
      ASSERT_TRUE(IsEqual(dy, -2.9631141));
      ASSERT_TRUE(IsEqual(rz, 1.71428));
      ASSERT_HR(presults->ComputePOIDeflections(0, 22, lotGlobalProjected, &dx, &dy, &rz));
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
      ASSERT_HR(presults->ComputePOIForces(0, 10, mftLeft, lotGlobalProjected, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 1.41421355));
      ASSERT_TRUE(IsEqual(fy, -1.41421355));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(0, 10, mftRight, lotGlobalProjected, &fx, &fy, &mz));
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
      ASSERT_HR(presults->ComputePOIForces(0, 15, mftLeft, lotGlobalProjected, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 1.41421355));
      ASSERT_TRUE(IsEqual(fy, -1.41421355));
      ASSERT_TRUE(IsEqual(mz, 4.0));
      ASSERT_HR(presults->ComputePOIForces(0, 15, mftRight, lotGlobalProjected, &fx, &fy, &mz));
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
      ASSERT_HR(presults->ComputePOIForces(0, 12, mftLeft, lotGlobalProjected, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 1.41421355));
      ASSERT_TRUE(IsEqual(fy, -1.41421355));
      ASSERT_TRUE(IsEqual(mz, 8.0));
      ASSERT_HR(presults->ComputePOIForces(0, 12, mftRight, lotGlobalProjected, &fx, &fy, &mz));
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
      ASSERT_TRUE(IsEqual(fx, 1.41421355));
      ASSERT_TRUE(IsEqual(fy, -1.41421355));
      ASSERT_TRUE(IsEqual(mz, 8.0));
      ASSERT_HR(presults->ComputePOIForces(0, 20, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 1.41421355));
      ASSERT_TRUE(IsEqual(fy, -1.41421355));
      ASSERT_TRUE(IsEqual(mz, -8.0));
      ASSERT_HR(presults->ComputePOIForces(0, 20, mftLeft, lotGlobalProjected, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 1.41421355));
      ASSERT_TRUE(IsEqual(fy, -1.41421355));
      ASSERT_TRUE(IsEqual(mz, 8.0));
      ASSERT_HR(presults->ComputePOIForces(0, 20, mftRight, lotGlobalProjected, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 1.41421355));
      ASSERT_TRUE(IsEqual(fy, -1.41421355));
      ASSERT_TRUE(IsEqual(mz, -8.0));
      ASSERT_HR(presults->ComputePOIForces(0, 20, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
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
      ASSERT_HR(presults->ComputePOIForces(0, 25, mftLeft, lotGlobalProjected, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, 4.0));
      ASSERT_HR(presults->ComputePOIForces(0, 25, mftRight, lotGlobalProjected, &fx, &fy, &mz));
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
   }

   TEST_METHOD(SameBeamLoadedInLocalMemberCoords_RotationsAt135And225)
   {
      // Same 8'-span pin-pin beam with the midspan point load specified in
      // *member* coordinates (put_Orientation(lotMember)), so results should
      // stay constant while the model is rotated in global space - unlike
      // the global-coordinate load case above (Fem2d\Test\TestSimpleBeamWithPointLoad12.cpp).
      Fem2dModelFixture fixture;
      CComPtr<IFem2dModel>& pmodel = fixture.Model;

      CComPtr<IFem2dJointCollection> pJoints;
      ASSERT_HR(pmodel->get_Joints(&pJoints));

      CComPtr<IFem2dJoint> pJoint0, pJoint8;
      ASSERT_MC(fixture, pJoints->Create(0, 0.0, 0.0, &pJoint0));
      ASSERT_MC(fixture, pJoints->Create(8, 8.0, 0.0, &pJoint8));

      ASSERT_MC(fixture, pJoint0->Support());
      ASSERT_MC(fixture, pJoint0->ReleaseDof(jrtMz));
      ASSERT_MC(fixture, pJoint8->Support());
      ASSERT_MC(fixture, pJoint8->ReleaseDof(jrtMz));

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
      ASSERT_LC(fixture, pPointLoads->Create(0, 1, 4.0, 0.0, -4.0, 0.0, lotGlobal, &pPointLoad));
      // use local member coord's
      ASSERT_LC(fixture, pPointLoad->put_Orientation(lotMember));

      CComPtr<IFem2dPOICollection> pPOIs;
      ASSERT_HR(pmodel->get_POIs(&pPOIs));

      CComPtr<IFem2dPOI> pPOI10, pPOI15, pPOI12;
      ASSERT_HR(pPOIs->Create(10, 1, 0.0, &pPOI10));
      ASSERT_HR(pPOIs->Create(15, 1, -.25, &pPOI15));
      ASSERT_HR(pPOIs->Create(12, 1, -0.5, &pPOI12));
      CComPtr<IFem2dPOI> pPOI20, pPOI25, pPOI22;
      ASSERT_HR(pPOIs->Create(20, 1, 4.0, &pPOI20));
      ASSERT_HR(pPOIs->Create(25, 1, 6.0, &pPOI25));
      ASSERT_HR(pPOIs->Create(22, 1, 8.0, &pPOI22));

      //////////////////////////////////////////////////////////////////////////////////
      // rotate the model 135 degrees clockwise - since orientation is local,
      // no need to change the load to be normal to the rotated structure
      ASSERT_MC(fixture, pJoint8->put_X(-5.6568542));
      ASSERT_MC(fixture, pJoint8->put_Y(5.6568542));

      Float64 l;
      pMember1->get_Length(&l);
      ASSERT_TRUE(IsEqual(l, 8.0));

      CComQIPtr<IFem2dModelResults> presults(pmodel);

      Float64 dx, dy, rz;
      ASSERT_HR(presults->ComputeJointDeflections(0, 0, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -2.2857142857143));
      ASSERT_HR(presults->ComputeJointDeflections(0, 8, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 2.2857142857143));

      Float64 sfx, sfy, smz, efx, efy, emz;
      ASSERT_HR(presults->ComputeMemberForces(0, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 2.0));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 2.0));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      Float64 fx, fy, mz;
      ASSERT_HR(presults->ComputeReactions(0, 0, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -1.41421356));
      ASSERT_TRUE(IsEqual(fy, -1.41421356));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputeReactions(0, 8, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -1.41421356));
      ASSERT_TRUE(IsEqual(fy, -1.41421356));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      Float64 sdx, sdy, srz, edx, edy, erz;
      ASSERT_HR(presults->ComputeMemberDeflections(0, 1, &sdx, &sdy, &srz, &edx, &edy, &erz));
      ASSERT_TRUE(IsEqual(sdx, 0.0));
      ASSERT_TRUE(IsEqual(sdy, 0.0));
      ASSERT_TRUE(IsEqual(srz, -2.2857142857143));
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
      ASSERT_HR(presults->ComputePOIDeflections(0, 10, lotGlobalProjected, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -2.2857142857143));
      ASSERT_HR(presults->ComputePOIDeflections(0, 15, lotGlobalProjected, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 2.9631141));
      ASSERT_TRUE(IsEqual(dy, 2.9631141));
      ASSERT_TRUE(IsEqual(rz, -1.71428));
      ASSERT_HR(presults->ComputePOIDeflections(0, 12, lotGlobalProjected, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 4.3099842));
      ASSERT_TRUE(IsEqual(dy, 4.3099842));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(0, 20, lotGlobalProjected, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 4.3099842));
      ASSERT_TRUE(IsEqual(dy, 4.3099842));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputePOIDeflections(0, 25, lotGlobalProjected, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 2.9631141));
      ASSERT_TRUE(IsEqual(dy, 2.9631141));
      ASSERT_TRUE(IsEqual(rz, 1.71428));
      ASSERT_HR(presults->ComputePOIDeflections(0, 22, lotGlobalProjected, &dx, &dy, &rz));
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
      ASSERT_HR(presults->ComputePOIForces(0, 10, mftLeft, lotGlobalProjected, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(0, 10, mftRight, lotGlobalProjected, &fx, &fy, &mz));
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
      ASSERT_HR(presults->ComputePOIForces(0, 15, mftLeft, lotGlobalProjected, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, 4.0));
      ASSERT_HR(presults->ComputePOIForces(0, 15, mftRight, lotGlobalProjected, &fx, &fy, &mz));
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
      ASSERT_HR(presults->ComputePOIForces(0, 12, mftLeft, lotGlobalProjected, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, 8.0));
      ASSERT_HR(presults->ComputePOIForces(0, 12, mftRight, lotGlobalProjected, &fx, &fy, &mz));
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
      ASSERT_TRUE(IsEqual(fx, 1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, 8.0));
      ASSERT_HR(presults->ComputePOIForces(0, 20, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, -8.0));
      ASSERT_HR(presults->ComputePOIForces(0, 20, mftLeft, lotGlobalProjected, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, 8.0));
      ASSERT_HR(presults->ComputePOIForces(0, 20, mftRight, lotGlobalProjected, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, -8.0));
      ASSERT_HR(presults->ComputePOIForces(0, 20, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
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
      ASSERT_HR(presults->ComputePOIForces(0, 25, mftLeft, lotGlobalProjected, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, -1.41421355));
      ASSERT_TRUE(IsEqual(mz, 4.0));
      ASSERT_HR(presults->ComputePOIForces(0, 25, mftRight, lotGlobalProjected, &fx, &fy, &mz));
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
      ASSERT_HR(pJoint8->put_X(-5.6568542));
      ASSERT_MC(fixture, pJoint8->put_Y(-5.6568542));

      pMember1->get_Length(&l);
      ASSERT_TRUE(IsEqual(l, 8.0));

      ASSERT_HR(presults->ComputeJointDeflections(0, 0, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -2.2857142857143));
      ASSERT_HR(presults->ComputeJointDeflections(0, 8, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 2.2857142857143));

      ASSERT_HR(presults->ComputeMemberForces(0, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 2.0));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 2.0));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      ASSERT_HR(presults->ComputeReactions(0, 0, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 1.41421356));
      ASSERT_TRUE(IsEqual(fy, -1.41421356));
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

      ASSERT_HR(presults->ComputePOIDeflections(0, 10, lotGlobalProjected, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -2.2857142857143));
      ASSERT_HR(presults->ComputePOIDeflections(0, 15, lotGlobalProjected, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, -2.9631141));
      ASSERT_TRUE(IsEqual(dy, 2.9631141));
      ASSERT_TRUE(IsEqual(rz, -1.71428));
      ASSERT_HR(presults->ComputePOIDeflections(0, 22, lotGlobalProjected, &dx, &dy, &rz));
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
      ASSERT_HR(presults->ComputePOIForces(0, 10, mftLeft, lotGlobalProjected, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(0, 10, mftRight, lotGlobalProjected, &fx, &fy, &mz));
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
      ASSERT_HR(presults->ComputePOIForces(0, 15, mftLeft, lotGlobalProjected, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, 4.0));
      ASSERT_HR(presults->ComputePOIForces(0, 15, mftRight, lotGlobalProjected, &fx, &fy, &mz));
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
      ASSERT_HR(presults->ComputePOIForces(0, 12, mftLeft, lotGlobalProjected, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, 8.0));
      ASSERT_HR(presults->ComputePOIForces(0, 12, mftRight, lotGlobalProjected, &fx, &fy, &mz));
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
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, 8.0));
      ASSERT_HR(presults->ComputePOIForces(0, 20, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, -8.0));
      ASSERT_HR(presults->ComputePOIForces(0, 20, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
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
      ASSERT_MC(fixture, pJoint8->put_X(5.6568542));
      ASSERT_HR(pJoint8->put_Y(-5.6568542));

      pMember1->get_Length(&l);
      ASSERT_TRUE(IsEqual(l, 8.0));

      ASSERT_HR(presults->ComputeJointDeflections(0, 0, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -2.2857142857143));
      ASSERT_HR(presults->ComputeJointDeflections(0, 8, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 2.2857142857143));

      ASSERT_HR(presults->ComputeMemberForces(0, 1, &sfx, &sfy, &smz, &efx, &efy, &emz));
      ASSERT_TRUE(IsEqual(sfx, 0.0));
      ASSERT_TRUE(IsEqual(sfy, 2.0));
      ASSERT_TRUE(IsEqual(smz, 0.0));
      ASSERT_TRUE(IsEqual(efx, 0.0));
      ASSERT_TRUE(IsEqual(efy, 2.0));
      ASSERT_TRUE(IsEqual(emz, 0.0));

      ASSERT_HR(presults->ComputeReactions(0, 0, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 1.41421356));
      ASSERT_TRUE(IsEqual(fy, 1.41421356));
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

      ASSERT_HR(presults->ComputePOIDeflections(0, 10, lotGlobalProjected, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -2.2857142857143));
      ASSERT_HR(presults->ComputePOIDeflections(0, 15, lotGlobalProjected, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, -2.9631141));
      ASSERT_TRUE(IsEqual(dy, -2.9631141));
      ASSERT_TRUE(IsEqual(rz, -1.71428));
      ASSERT_HR(presults->ComputePOIDeflections(0, 22, lotGlobalProjected, &dx, &dy, &rz));
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
      ASSERT_HR(presults->ComputePOIForces(0, 10, mftLeft, lotGlobalProjected, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, -1.41421355));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(0, 10, mftRight, lotGlobalProjected, &fx, &fy, &mz));
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
      ASSERT_HR(presults->ComputePOIForces(0, 15, mftLeft, lotGlobalProjected, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, -1.41421355));
      ASSERT_TRUE(IsEqual(mz, 4.0));
      ASSERT_HR(presults->ComputePOIForces(0, 15, mftRight, lotGlobalProjected, &fx, &fy, &mz));
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
      ASSERT_HR(presults->ComputePOIForces(0, 12, mftLeft, lotGlobalProjected, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, -1.41421355));
      ASSERT_TRUE(IsEqual(mz, 8.0));
      ASSERT_HR(presults->ComputePOIForces(0, 12, mftRight, lotGlobalProjected, &fx, &fy, &mz));
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
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, -1.41421355));
      ASSERT_TRUE(IsEqual(mz, 8.0));
      ASSERT_HR(presults->ComputePOIForces(0, 20, mftRight, lotGlobal, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, -1.41421355));
      ASSERT_TRUE(IsEqual(mz, -8.0));
      ASSERT_HR(presults->ComputePOIForces(0, 20, mftLeft, lotGlobalProjected, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, -1.41421355));
      ASSERT_TRUE(IsEqual(mz, 8.0));
      ASSERT_HR(presults->ComputePOIForces(0, 20, mftRight, lotGlobalProjected, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -1.41421355));
      ASSERT_TRUE(IsEqual(fy, -1.41421355));
      ASSERT_TRUE(IsEqual(mz, -8.0));
      ASSERT_HR(presults->ComputePOIForces(0, 20, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.0));
      ASSERT_TRUE(IsEqual(fy, -2.0));
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
      ASSERT_HR(presults->ComputePOIForces(0, 25, mftLeft, lotGlobalProjected, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 1.41421355));
      ASSERT_TRUE(IsEqual(fy, 1.41421355));
      ASSERT_TRUE(IsEqual(mz, 4.0));
      ASSERT_HR(presults->ComputePOIForces(0, 25, mftRight, lotGlobalProjected, &fx, &fy, &mz));
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
