///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
///////////////////////////////////////////////////////////////////////
// TestFrameWithReleases.cpp
//
// Ported from F:\ARP\WBFL\Fem2d\Test\TestFrameWithReleases.cpp. The legacy
// file left most POI-level deflection/force assertions commented out
// (evidently disabled during development) for the cantilever sub-test; only
// the active (uncompiled-out) assertions are ported here to preserve
// behavior exactly.
#include "pch.h"

namespace Fem2dUnitTests
{

TEST_CLASS(TestFrameWithReleases)
{
public:
   TEST_METHOD(SimpleCantilever_ThreeLoadCases_SupportConfigVariants)
   {
      Fem2dModelFixture fixture;
      CComPtr<IFem2dModel>& pmodel = fixture.Model;

      CComPtr<IFem2dJointCollection> pJoints;
      ASSERT_HR(pmodel->get_Joints(&pJoints));

      CComPtr<IFem2dJoint> pJoint1, pJoint2;
      ASSERT_MC(fixture, pJoints->Create(1, 0.0, 0.0, &pJoint1));
      ASSERT_MC(fixture, pJoints->Create(2, 10.0, 0.0, &pJoint2));

      // boundary conditions (free-fixed)
      ASSERT_MC(fixture, pJoint2->Support());

      CComPtr<IFem2dMemberCollection> pMembers;
      ASSERT_HR(pmodel->get_Members(&pMembers));

      Float64 EA = 100;
      Float64 EI = 10000;
      CComPtr<IFem2dMember> pMember1;
      ASSERT_MC(fixture, pMembers->Create(1, 1, 2, EA, EI, &pMember1));

      CComPtr<IFem2dPOICollection> pPOIs;
      ASSERT_HR(pmodel->get_POIs(&pPOIs));

      CComPtr<IFem2dPOI> pPOI200, pPOI201, pPOI202, pPOI203, pPOI204;
      ASSERT_HR(pPOIs->Create(200, 1, 0.00, &pPOI200));
      ASSERT_HR(pPOIs->Create(201, 1, -0.25, &pPOI201));
      ASSERT_HR(pPOIs->Create(202, 1, -0.50, &pPOI202));
      ASSERT_HR(pPOIs->Create(203, 1, -0.75, &pPOI203));
      ASSERT_HR(pPOIs->Create(204, 1, -1.00, &pPOI204));

      // Create load cases with various member loads on member 1.
      CComPtr<IFem2dLoadingCollection> pLoadings;
      ASSERT_HR(pmodel->get_Loadings(&pLoadings));

      // load case 0: vertical point load at the center of member 1
      CComPtr<IFem2dLoading> pLoading0;
      ASSERT_LC(fixture, pLoadings->Create(0, &pLoading0));
      CComPtr<IFem2dPointLoadCollection> pPointLoads;
      ASSERT_HR(pLoading0->get_PointLoads(&pPointLoads));
      CComPtr<IFem2dPointLoad> pPointLoad;
      ASSERT_LC(fixture, pPointLoads->Create(1, 1, -0.5, 0.0, -10.0, 0.0, lotGlobal, &pPointLoad));

      // load case 1: uniform axial strain along member 1
      CComPtr<IFem2dLoading> pLoading1;
      ASSERT_LC(fixture, pLoadings->Create(1, &pLoading1));
      CComPtr<IFem2dMemberStrainCollection> pMemberStrains;
      ASSERT_HR(pLoading1->get_MemberStrains(&pMemberStrains));
      CComPtr<IFem2dMemberStrain> pStrainLoad;
      ASSERT_LC(fixture, pMemberStrains->Create(1, 1, 0.0, -1.0, 2, 0, &pStrainLoad));

      pMemberStrains.Release();
      pStrainLoad.Release();

      // load case 2: uniform curvature along member 1
      CComPtr<IFem2dLoading> pLoading2;
      ASSERT_LC(fixture, pLoadings->Create(2, &pLoading2));
      ASSERT_HR(pLoading2->get_MemberStrains(&pMemberStrains));
      ASSERT_LC(fixture, pMemberStrains->Create(1, 1, 0.0, -1.0, 0, 1, &pStrainLoad));

      CComQIPtr<IFem2dModelResults> presults(pmodel);

      //////////////////////////////////
      LoadCaseIDType lc = 0;

      Float64 dx, dy, rz;
      ASSERT_HR(presults->ComputeJointDeflections(lc, 1, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, -0.1041667));
      ASSERT_TRUE(IsEqual(rz, 0.01250));
      ASSERT_HR(presults->ComputeJointDeflections(lc, 2, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      // axial strain load case
      lc = 1;
      ASSERT_HR(presults->ComputeJointDeflections(lc, 1, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, -20.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputeJointDeflections(lc, 2, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      // curvature load case
      lc = 2;
      ASSERT_HR(presults->ComputeJointDeflections(lc, 1, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 50.0));
      ASSERT_TRUE(IsEqual(rz, -10.0));
      ASSERT_HR(presults->ComputeJointDeflections(lc, 2, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      //////////////////////////////////
      // place a hinge support at joint 1 (Pinned-Fixed)
      ASSERT_MC(fixture, pJoint1->Support());
      pJoint1->ReleaseDof(jrtMz);

      lc = 0;
      ASSERT_HR(presults->ComputeJointDeflections(lc, 1, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -0.003125));
      ASSERT_HR(presults->ComputeJointDeflections(lc, 2, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      lc = 1;
      ASSERT_HR(presults->ComputeJointDeflections(lc, 1, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputeJointDeflections(lc, 2, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      lc = 2;
      ASSERT_HR(presults->ComputeJointDeflections(lc, 1, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, -2.5));
      ASSERT_HR(presults->ComputeJointDeflections(lc, 2, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      ////////////////////////////////
      // make the beam fixed-fixed with a member end release at the start of
      // member 1. Same as the pin-fixed beam, except joint 1 deflections
      // are now zero.
      pJoint1->Support();
      pMember1->ReleaseEnd(metStart, mbrReleaseMz);

      lc = 0;
      ASSERT_HR(presults->ComputeJointDeflections(lc, 1, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputeJointDeflections(lc, 2, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      lc = 1;
      ASSERT_HR(presults->ComputeJointDeflections(lc, 1, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputeJointDeflections(lc, 2, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      lc = 2;
      ASSERT_HR(presults->ComputeJointDeflections(lc, 1, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputeJointDeflections(lc, 2, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      ////////////////////////////////
      // make the beam fixed-fixed with a member end release at the end of
      // member 1 (fix-pin beam)
      pMember1->ReleaseEnd(metStart, mbrReleaseNone);
      pMember1->ReleaseEnd(metEnd, mbrReleaseMz);

      lc = 0;
      ASSERT_HR(presults->ComputeJointDeflections(lc, 1, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputeJointDeflections(lc, 2, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      lc = 1;
      ASSERT_HR(presults->ComputeJointDeflections(lc, 1, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputeJointDeflections(lc, 2, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));

      lc = 2;
      ASSERT_HR(presults->ComputeJointDeflections(lc, 1, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
      ASSERT_HR(presults->ComputeJointDeflections(lc, 2, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.0));
      ASSERT_TRUE(IsEqual(dy, 0.0));
      ASSERT_TRUE(IsEqual(rz, 0.0));
   }

   // Portal frame with end releases on member 2 and joint loads causing
   // sidesway; made up and verified using WinStrudl (input/output files are
   // in F:\ARP\WBFL\Fem2d\Test\Supporting Documents\WinStrudl\Releases.*).
   //             w
   //        ============ 3
   //                   /o
   //                 /  |
   //           m2  /    |      <- various loads and release conditions on m2
   //             /      | m3
   //           /        |
   //         2o         o4
   //          |         |
   //          |         |
   //          | m1      | m4
   //          |         |
   //         1o         o5
   //         ===       ===
   TEST_METHOD(PortalFrameWithReleases_WinStrudlVerified)
   {
      Fem2dModelFixture fixture;
      CComPtr<IFem2dModel>& pmodel = fixture.Model;

      CComPtr<IFem2dJointCollection> pJoints;
      ASSERT_HR(pmodel->get_Joints(&pJoints));

      CComPtr<IFem2dJoint> pJoint1, pJoint2, pJoint3, pJoint4, pJoint5;
      ASSERT_MC(fixture, pJoints->Create(1, 0.0, 0.0, &pJoint1));
      ASSERT_MC(fixture, pJoints->Create(2, 0.0, 10.0, &pJoint2));
      ASSERT_MC(fixture, pJoints->Create(3, 10.0, 20.0, &pJoint3));
      ASSERT_MC(fixture, pJoints->Create(4, 10.0, 10.0, &pJoint4));
      ASSERT_MC(fixture, pJoints->Create(5, 10.0, 0.0, &pJoint5));

      ASSERT_MC(fixture, pJoint1->Support());
      ASSERT_MC(fixture, pJoint5->Support());

      CComPtr<IFem2dMemberCollection> pMembers;
      ASSERT_HR(pmodel->get_Members(&pMembers));

      Float64 EA = 100;
      Float64 EI = 10000;
      CComPtr<IFem2dMember> pMember1, pMember2, pMember3, pMember4;
      ASSERT_MC(fixture, pMembers->Create(1, 1, 2, EA, EI, &pMember1));
      ASSERT_MC(fixture, pMembers->Create(2, 2, 3, EA, EI, &pMember2));
      ASSERT_MC(fixture, pMembers->Create(3, 3, 4, EA, EI, &pMember3));
      ASSERT_MC(fixture, pMembers->Create(4, 4, 5, EA, EI, &pMember4));

      CComPtr<IFem2dPOICollection> pPOIs;
      ASSERT_HR(pmodel->get_POIs(&pPOIs));

      CComPtr<IFem2dPOI> pPOI200, pPOI201, pPOI202, pPOI203, pPOI204;
      ASSERT_HR(pPOIs->Create(200, 2, 0.00, &pPOI200));
      ASSERT_HR(pPOIs->Create(201, 2, -0.25, &pPOI201));
      ASSERT_HR(pPOIs->Create(202, 2, -0.50, &pPOI202));
      ASSERT_HR(pPOIs->Create(203, 2, -0.75, &pPOI203));
      ASSERT_HR(pPOIs->Create(204, 2, -1.00, &pPOI204));

      // Create load cases with various member loads on member 2. Also, all
      // load cases have a joint load on Joint 2 to cause sidesway of the frame.
      CComPtr<IFem2dLoadingCollection> pLoadings;
      ASSERT_HR(pmodel->get_Loadings(&pLoadings));

      // load case 0: vertical point load at the center of member 2
      CComPtr<IFem2dLoading> pLoading0;
      ASSERT_LC(fixture, pLoadings->Create(0, &pLoading0));
      CComPtr<IFem2dPointLoadCollection> pPointLoads;
      ASSERT_HR(pLoading0->get_PointLoads(&pPointLoads));
      CComPtr<IFem2dPointLoad> pPointLoad;
      ASSERT_LC(fixture, pPointLoads->Create(1, 2, -0.5, 0.0, -10.0, 0.0, lotGlobal, &pPointLoad));

      CComPtr<IFem2dJointLoadCollection> pJointLoads;
      ASSERT_HR(pLoading0->get_JointLoads(&pJointLoads));
      CComPtr<IFem2dJointLoad> pJointLoad;
      ASSERT_LC(fixture, pJointLoads->Create(1, 2, 10.0, 0.0, 0.0, &pJointLoad));

      // load case 1: uniform distributed load along member 2
      CComPtr<IFem2dLoading> pLoading1;
      ASSERT_LC(fixture, pLoadings->Create(1, &pLoading1));
      CComPtr<IFem2dDistributedLoadCollection> pDistributedLoads;
      ASSERT_HR(pLoading1->get_DistributedLoads(&pDistributedLoads));
      CComPtr<IFem2dDistributedLoad> pDistributedLoad;
      ASSERT_LC(fixture, pDistributedLoads->Create(1, 2, loadDirFy, 0.0, -1.0, -1.0, -1.0, lotMember, &pDistributedLoad));

      pJointLoads.Release();
      ASSERT_HR(pLoading1->get_JointLoads(&pJointLoads));
      pJointLoad.Release();
      ASSERT_LC(fixture, pJointLoads->Create(1, 2, 10.0, 0.0, 0.0, &pJointLoad));

      // load case 2: temperature strain load along member 2
      CComPtr<IFem2dLoading> pLoading2;
      ASSERT_LC(fixture, pLoadings->Create(2, &pLoading2));
      CComPtr<IFem2dMemberStrainCollection> pMemberStrains;
      ASSERT_HR(pLoading2->get_MemberStrains(&pMemberStrains));
      CComPtr<IFem2dMemberStrain> pStrainLoad;
      ASSERT_LC(fixture, pMemberStrains->Create(1, 2, 0.0, -1.0, 2, 1, &pStrainLoad));

      pJointLoads.Release();
      ASSERT_HR(pLoading2->get_JointLoads(&pJointLoads));
      pJointLoad.Release();
      ASSERT_LC(fixture, pJointLoads->Create(1, 2, 10.0, 0.0, 0.0, &pJointLoad));

      CComQIPtr<IFem2dModelResults> presults(pmodel);

      ////////////////////////////////
      // place a hinge at the start of member 2 (Pin-Fix)
      pMember2->ReleaseEnd(metStart, mbrReleaseMz);
      LoadCaseIDType lc = 0;

      Float64 dx, dy, rz;
      ASSERT_HR(presults->ComputeJointDeflections(lc, 2, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.27095097726495));
      ASSERT_TRUE(IsEqual(dy, -0.55948045530510));
      ASSERT_TRUE(IsEqual(rz, -0.040642646589743));
      ASSERT_HR(presults->ComputeJointDeflections(lc, 3, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.24372562274697));
      ASSERT_TRUE(IsEqual(dy, -0.88103908938980));
      ASSERT_TRUE(IsEqual(rz, -0.011896091061020));

      ASSERT_HR(presults->ComputePOIDeflections(lc, 200, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.27095097726495));
      ASSERT_TRUE(IsEqual(dy, -0.55948045530510));
      ASSERT_TRUE(IsEqual(rz, -0.020546367819410));
      ASSERT_HR(presults->ComputePOIDeflections(lc, 201, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.18895930338732));
      ASSERT_TRUE(IsEqual(dy, -0.74146147387478));
      ASSERT_TRUE(IsEqual(rz, -0.018900871176406));
      ASSERT_HR(presults->ComputePOIDeflections(lc, 202, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.098740146294668));
      ASSERT_TRUE(IsEqual(dy, -0.91521500922943));
      ASSERT_TRUE(IsEqual(rz, -0.013964381247396));
      ASSERT_HR(presults->ComputePOIDeflections(lc, 203, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.17252556588730));
      ASSERT_TRUE(IsEqual(dy, -0.89941973067610));
      ASSERT_TRUE(IsEqual(rz, -0.010156315414796));
      ASSERT_HR(presults->ComputePOIDeflections(lc, 204, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.24372562274697));
      ASSERT_TRUE(IsEqual(dy, -0.88103908938980));
      ASSERT_TRUE(IsEqual(rz, -0.011896091061020));

      Float64 fx, fy, mz;
      ASSERT_HR(presults->ComputePOIForces(lc, 200, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -5.2794538489462));
      ASSERT_TRUE(IsEqual(fy, -2.6327946288053));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(lc, 202, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -5.2794538489462));
      ASSERT_TRUE(IsEqual(fy, -2.6327946288053));
      ASSERT_TRUE(IsEqual(mz, 18.616669354998));
      ASSERT_HR(presults->ComputePOIForces(lc, 204, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 1.7916139629193));
      ASSERT_TRUE(IsEqual(fy, 4.4382731830602));
      ASSERT_TRUE(IsEqual(mz, -12.766661290005));

      // distributed load case
      lc = 1;
      ASSERT_HR(presults->ComputeJointDeflections(lc, 2, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.45266417074768));
      ASSERT_TRUE(IsEqual(dy, -0.39458259696851));
      ASSERT_TRUE(IsEqual(rz, -0.067899625612152));
      ASSERT_HR(presults->ComputeJointDeflections(lc, 3, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 1.2171701857750));
      ASSERT_TRUE(IsEqual(dy, -1.2108348060630));
      ASSERT_TRUE(IsEqual(rz, -0.078916519393703));

      ASSERT_HR(presults->ComputePOIDeflections(lc, 200, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.45266417074768));
      ASSERT_TRUE(IsEqual(dy, -0.39458259696851));
      ASSERT_TRUE(IsEqual(rz, -0.084991163622169));
      ASSERT_HR(presults->ComputePOIDeflections(lc, 201, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.65636254192269));
      ASSERT_TRUE(IsEqual(dy, -0.61121751666031));
      ASSERT_TRUE(IsEqual(rz, -0.082401789666682));
      ASSERT_HR(presults->ComputePOIDeflections(lc, 202, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.84987617918428));
      ASSERT_TRUE(IsEqual(dy, -0.81766770243869));
      ASSERT_TRUE(IsEqual(rz, -0.077579946055165));
      ASSERT_HR(presults->ComputePOIDeflections(lc, 203, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 1.0331481801204));
      ASSERT_TRUE(IsEqual(dy, -1.0138762518916));
      ASSERT_TRUE(IsEqual(rz, -0.074945050170033));
      ASSERT_HR(presults->ComputePOIDeflections(lc, 204, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 1.2171701857750));
      ASSERT_TRUE(IsEqual(dy, -1.2108348060630));
      ASSERT_TRUE(IsEqual(rz, -0.078916519393703));

      ASSERT_HR(presults->ComputePOIForces(lc, 200, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -0.25873097033570));
      ASSERT_TRUE(IsEqual(fy, -5.3215096307570));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(lc, 202, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -0.25873097033570));
      ASSERT_TRUE(IsEqual(fy, 1.7495581811085));
      ASSERT_TRUE(IsEqual(mz, 12.628755460578));
      ASSERT_HR(presults->ComputePOIForces(lc, 204, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -0.25873097033570));
      ASSERT_TRUE(IsEqual(fy, 8.8206259929739));
      ASSERT_TRUE(IsEqual(mz, -24.742489078844));

      // strain load case
      lc = 2;
      ASSERT_HR(presults->ComputeJointDeflections(lc, 2, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, -13.952250159469));
      ASSERT_TRUE(IsEqual(dy, 9.8425183846726));
      ASSERT_TRUE(IsEqual(rz, 2.0928375239203));
      ASSERT_HR(presults->ComputeJointDeflections(lc, 3, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 8.8861302162586));
      ASSERT_TRUE(IsEqual(dy, -19.685036769345));
      ASSERT_TRUE(IsEqual(rz, 1.9685036769345));

      ASSERT_HR(presults->ComputePOIDeflections(lc, 200, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, -13.952250159469));
      ASSERT_TRUE(IsEqual(dy, 9.8425183846726));
      ASSERT_TRUE(IsEqual(rz, -8.4472309091309));
      ASSERT_HR(presults->ComputePOIDeflections(lc, 201, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 2.1043462710348));
      ASSERT_TRUE(IsEqual(dy, -7.8863717404034));
      ASSERT_TRUE(IsEqual(rz, -5.1445970680522));
      ASSERT_HR(presults->ComputePOIDeflections(lc, 202, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 10.486608260977));
      ASSERT_TRUE(IsEqual(dy, -17.940927424918));
      ASSERT_TRUE(IsEqual(rz, -2.3077633566818));
      ASSERT_HR(presults->ComputePOIDeflections(lc, 203, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 12.359036134628));
      ASSERT_TRUE(IsEqual(dy, -21.485648993142));
      ASSERT_TRUE(IsEqual(rz, 0.063270224980469));
      ASSERT_HR(presults->ComputePOIDeflections(lc, 204, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 8.8861302162586));
      ASSERT_TRUE(IsEqual(dy, -19.685036769345));
      ASSERT_TRUE(IsEqual(rz, 1.9685036769345));

      ASSERT_HR(presults->ComputePOIForces(lc, 200, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -233.445873891450));
      ASSERT_TRUE(IsEqual(fy, 372.64010376656));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(lc, 202, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -233.44587389145));
      ASSERT_TRUE(IsEqual(fy, 372.64010376656));
      ASSERT_TRUE(IsEqual(mz, -2634.9634431539));
      ASSERT_HR(presults->ComputePOIForces(lc, 204, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -233.44587389145));
      ASSERT_TRUE(IsEqual(fy, 372.64010376656));
      ASSERT_TRUE(IsEqual(mz, -5269.9268863078));

      ////////////////////////////////
      // now place a hinge at the end of member 2 (pin-pin)
      pMember2->ReleaseEnd(metEnd, mbrReleaseMz);

      lc = 0;
      ASSERT_HR(presults->ComputeJointDeflections(lc, 2, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.30186931671375));
      ASSERT_TRUE(IsEqual(dy, -0.59439204985874));
      ASSERT_TRUE(IsEqual(rz, -0.045280397507063));
      ASSERT_HR(presults->ComputeJointDeflections(lc, 3, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.25171213295665));
      ASSERT_TRUE(IsEqual(dy, -0.81121590028251));
      ASSERT_TRUE(IsEqual(rz, -0.018878409971749));

      ASSERT_HR(presults->ComputePOIDeflections(lc, 200, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.30186931671375));
      ASSERT_TRUE(IsEqual(dy, -0.59439204985874));
      ASSERT_TRUE(IsEqual(rz, -0.017172168098165));
      ASSERT_HR(presults->ComputePOIDeflections(lc, 201, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.22119733612890));
      ASSERT_TRUE(IsEqual(dy, -0.75724202311574));
      ASSERT_TRUE(IsEqual(rz, -0.014962459406957));
      ASSERT_HR(presults->ComputePOIDeflections(lc, 202, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.12947681208800));
      ASSERT_TRUE(IsEqual(dy, -0.90904345291670));
      ASSERT_TRUE(IsEqual(rz, -0.0083333333333333));
      ASSERT_HR(presults->ComputePOIDeflections(lc, 203, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.19611874425035));
      ASSERT_TRUE(IsEqual(dy, -0.86565394832763));
      ASSERT_TRUE(IsEqual(rz, -0.0017042072597094));
      ASSERT_HR(presults->ComputePOIDeflections(lc, 204, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.25171213295665));
      ASSERT_TRUE(IsEqual(dy, -0.81121590028251));
      ASSERT_TRUE(IsEqual(rz, 0.00050550143149));

      ASSERT_HR(presults->ComputePOIForces(lc, 200, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -4.8704390768371));
      ASSERT_TRUE(IsEqual(fy, -3.5355339059327));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(lc, 202, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -4.8704390768371));
      ASSERT_TRUE(IsEqual(fy, -3.5355339059327));
      ASSERT_TRUE(IsEqual(mz, 25.000000000000));
      ASSERT_HR(presults->ComputePOIForces(lc, 204, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 2.2006287350284));
      ASSERT_TRUE(IsEqual(fy, 3.5355339059327));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      // distributed load case
      lc = 1;
      ASSERT_HR(presults->ComputeJointDeflections(lc, 2, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.51258560664783));
      ASSERT_TRUE(IsEqual(dy, -0.46224318005650));
      ASSERT_TRUE(IsEqual(rz, -0.076887840997175));
      ASSERT_HR(presults->ComputeJointDeflections(lc, 3, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 1.2326484801507));
      ASSERT_TRUE(IsEqual(dy, -1.0755136398870));
      ASSERT_TRUE(IsEqual(rz, -0.092448636011300));

      ASSERT_HR(presults->ComputePOIDeflections(lc, 200, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.51258560664783));
      ASSERT_TRUE(IsEqual(dy, -0.46224318005650));
      ASSERT_TRUE(IsEqual(rz, -0.078451779686442));
      ASSERT_HR(presults->ComputePOIDeflections(lc, 201, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.71884161573164));
      ASSERT_TRUE(IsEqual(dy, -0.64180108572222));
      ASSERT_TRUE(IsEqual(rz, -0.074768931867762));
      ASSERT_HR(presults->ComputePOIDeflections(lc, 202, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.90944552158605));
      ASSERT_TRUE(IsEqual(dy, -0.80570688815855));
      ASSERT_TRUE(IsEqual(rz, -0.066666666666666));
      ASSERT_HR(presults->ComputePOIDeflections(lc, 203, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 1.0788730524831));
      ASSERT_TRUE(IsEqual(dy, -0.94843631563747));
      ASSERT_TRUE(IsEqual(rz, -0.058564401465571));
      ASSERT_HR(presults->ComputePOIDeflections(lc, 204, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 1.2326484801507));
      ASSERT_TRUE(IsEqual(dy, -1.0755136398870));
      ASSERT_TRUE(IsEqual(rz, -0.054881553646891));

      ASSERT_HR(presults->ComputePOIForces(lc, 200, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.53396206836173));
      ASSERT_TRUE(IsEqual(fy, -7.0710678118655));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(lc, 202, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.53396206836173));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 25.0000000));
      ASSERT_HR(presults->ComputePOIForces(lc, 204, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.53396206836173));
      ASSERT_TRUE(IsEqual(fy, 7.0710678118655));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      // strain load case
      lc = 2;
      ASSERT_HR(presults->ComputeJointDeflections(lc, 2, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, -1.1895250710544));
      ASSERT_TRUE(IsEqual(dy, -4.5685752131632));
      ASSERT_TRUE(IsEqual(rz, 0.17842876065816));
      ASSERT_HR(presults->ComputeJointDeflections(lc, 3, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 12.182867235102));
      ASSERT_TRUE(IsEqual(dy, 9.1371504263265));
      ASSERT_TRUE(IsEqual(rz, -0.91371504263264));

      ASSERT_HR(presults->ComputePOIDeflections(lc, 200, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, -1.1895250710544));
      ASSERT_TRUE(IsEqual(dy, -4.5685752131632));
      ASSERT_TRUE(IsEqual(rz, -7.0544011451988));
      ASSERT_HR(presults->ComputePOIDeflections(lc, 201, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 15.411825152732));
      ASSERT_TRUE(IsEqual(dy, -14.400395950539));
      ASSERT_TRUE(IsEqual(rz, -3.5188672392661));
      ASSERT_HR(presults->ComputePOIDeflections(lc, 202, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 23.174340611687));
      ASSERT_TRUE(IsEqual(dy, -15.393381923082));
      ASSERT_TRUE(IsEqual(rz, 0.016666666666668));
      ASSERT_HR(presults->ComputePOIDeflections(lc, 203, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 22.098021305811));
      ASSERT_TRUE(IsEqual(dy, -7.5475331307937));
      ASSERT_TRUE(IsEqual(rz, 3.5522005725994));
      ASSERT_HR(presults->ComputePOIDeflections(lc, 204, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 12.182867235102));
      ASSERT_TRUE(IsEqual(dy, 9.1371504263265));
      ASSERT_TRUE(IsEqual(rz, 7.0877344785321));

      ASSERT_HR(presults->ComputePOIForces(lc, 200, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -64.609410271770));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(lc, 202, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -64.609410271770));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));
      ASSERT_HR(presults->ComputePOIForces(lc, 204, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -64.609410271770));
      ASSERT_TRUE(IsEqual(fy, 0.0));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      ////////////////////////////////
      // now fix the start of member 2 (fix-pin)
      pMember2->ReleaseEnd(metStart, mbrReleaseNone);

      lc = 0;
      ASSERT_HR(presults->ComputeJointDeflections(lc, 2, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.24898601337127));
      ASSERT_TRUE(IsEqual(dy, -0.54895017991052));
      ASSERT_TRUE(IsEqual(rz, -0.035306984205934));
      ASSERT_HR(presults->ComputeJointDeflections(lc, 3, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.34823171173542));
      ASSERT_TRUE(IsEqual(dy, -0.90209964017896));
      ASSERT_TRUE(IsEqual(rz, -0.026117378380157));

      ASSERT_HR(presults->ComputePOIDeflections(lc, 200, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.24898601337127));
      ASSERT_TRUE(IsEqual(dy, -0.54895017991052));
      ASSERT_TRUE(IsEqual(rz, -0.035306984205934));
      ASSERT_HR(presults->ComputePOIDeflections(lc, 201, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.21197852063696));
      ASSERT_TRUE(IsEqual(dy, -0.75219532294892));
      ASSERT_TRUE(IsEqual(rz, -0.030571768586635));
      ASSERT_HR(presults->ComputePOIDeflections(lc, 202, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.15851068388641));
      ASSERT_TRUE(IsEqual(dy, -0.93898012197108));
      ASSERT_TRUE(IsEqual(rz, -0.022138708992946));
      ASSERT_HR(presults->ComputePOIDeflections(lc, 203, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.25979743629897));
      ASSERT_TRUE(IsEqual(dy, -0.92696611956307));
      ASSERT_TRUE(IsEqual(rz, -0.014427222807283));
      ASSERT_HR(presults->ComputePOIDeflections(lc, 204, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.34823171173542));
      ASSERT_TRUE(IsEqual(dy, -0.90209964017896));
      ASSERT_TRUE(IsEqual(rz, -0.011856727412062));

      ASSERT_HR(presults->ComputePOIForces(lc, 200, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -4.8050527154542));
      ASSERT_TRUE(IsEqual(fy, -2.9582751795118));
      ASSERT_TRUE(IsEqual(mz, 8.1636711990265));
      ASSERT_HR(presults->ComputePOIForces(lc, 202, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -4.8050527154542));
      ASSERT_TRUE(IsEqual(fy, -2.9582751795118));
      ASSERT_TRUE(IsEqual(mz, 29.081835599513));
      ASSERT_HR(presults->ComputePOIForces(lc, 204, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 2.2660150964113));
      ASSERT_TRUE(IsEqual(fy, 4.1127926323536));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      // distributed load case
      lc = 1;
      ASSERT_HR(presults->ComputeJointDeflections(lc, 2, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.51552802763460));
      ASSERT_TRUE(IsEqual(dy, -0.46477156053507));
      ASSERT_TRUE(IsEqual(rz, -0.077442760579578));
      ASSERT_HR(presults->ComputeJointDeflections(lc, 3, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 1.2272781417587));
      ASSERT_TRUE(IsEqual(dy, -1.0704568789299));
      ASSERT_TRUE(IsEqual(rz, -0.092045860631905));

      ASSERT_HR(presults->ComputePOIDeflections(lc, 200, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.51552802763460));
      ASSERT_TRUE(IsEqual(dy, -0.46477156053507));
      ASSERT_TRUE(IsEqual(rz, -0.077442760579578));
      ASSERT_HR(presults->ComputePOIDeflections(lc, 201, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.71935454957771));
      ASSERT_TRUE(IsEqual(dy, -0.64208188354585));
      ASSERT_TRUE(IsEqual(rz, -0.073900431679305));
      ASSERT_HR(presults->ComputePOIDeflections(lc, 202, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 0.90783008025945));
      ASSERT_TRUE(IsEqual(dy, -0.80404121529524));
      ASSERT_TRUE(IsEqual(rz, -0.065898537134214));
      ASSERT_HR(presults->ComputePOIDeflections(lc, 203, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 1.0753299772958));
      ASSERT_TRUE(IsEqual(dy, -0.94502491339924));
      ASSERT_TRUE(IsEqual(rz, -0.057856494326720));
      ASSERT_HR(presults->ComputePOIDeflections(lc, 204, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 1.2272781417587));
      ASSERT_TRUE(IsEqual(dy, -1.0704568789299));
      ASSERT_TRUE(IsEqual(rz, -0.054193720639241));

      ASSERT_HR(presults->ComputePOIForces(lc, 200, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.53032397864682));
      ASSERT_TRUE(IsEqual(fy, -7.1031864217869));
      ASSERT_TRUE(IsEqual(mz, -0.45422573755482));
      ASSERT_HR(presults->ComputePOIForces(lc, 202, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.53032397864682));
      ASSERT_TRUE(IsEqual(fy, -0.032118609921449));
      ASSERT_TRUE(IsEqual(mz, 24.772887131223));
      ASSERT_HR(presults->ComputePOIForces(lc, 204, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, 0.53032397864682));
      ASSERT_TRUE(IsEqual(fy, 7.0389492019440));
      ASSERT_TRUE(IsEqual(mz, 0.0));

      // strain load case
      lc = 2;
      ASSERT_HR(presults->ComputeJointDeflections(lc, 2, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 12.418444764815));
      ASSERT_TRUE(IsEqual(dy, -16.261710029957));
      ASSERT_TRUE(IsEqual(rz, -2.3879371579663));
      ASSERT_HR(presults->ComputeJointDeflections(lc, 3, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, -12.653620532812));
      ASSERT_TRUE(IsEqual(dy, 32.523420059913));
      ASSERT_TRUE(IsEqual(rz, 0.94902153996093));

      ASSERT_HR(presults->ComputePOIDeflections(lc, 200, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 12.418444764815));
      ASSERT_TRUE(IsEqual(dy, -16.261710029957));
      ASSERT_TRUE(IsEqual(rz, -2.3879371579663));
      ASSERT_HR(presults->ComputePOIDeflections(lc, 201, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 17.784017417734));
      ASSERT_TRUE(IsEqual(dy, -15.699016484814));
      ASSERT_TRUE(IsEqual(rz, 0.49773147999734));
      ASSERT_HR(presults->ComputePOIDeflections(lc, 202, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 15.703323737182));
      ASSERT_TRUE(IsEqual(dy, -7.6900566062025));
      ASSERT_TRUE(IsEqual(rz, 3.5690759088093));
      ASSERT_HR(presults->ComputePOIDeflections(lc, 203, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, 5.7121742460405));
      ASSERT_TRUE(IsEqual(dy, 8.2293590829997));
      ASSERT_TRUE(IsEqual(rz, 6.8260961284696));
      ASSERT_HR(presults->ComputePOIDeflections(lc, 204, lotGlobal, &dx, &dy, &rz));
      ASSERT_TRUE(IsEqual(dx, -12.653620532812));
      ASSERT_TRUE(IsEqual(dy, 32.523420059913));
      ASSERT_TRUE(IsEqual(rz, 10.268792138978));

      ASSERT_HR(presults->ComputePOIForces(lc, 200, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -81.434676038792));
      ASSERT_TRUE(IsEqual(fy, -148.54063267864));
      ASSERT_TRUE(IsEqual(mz, -2100.6817729761));
      ASSERT_HR(presults->ComputePOIForces(lc, 202, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -81.434676038792));
      ASSERT_TRUE(IsEqual(fy, -148.54063267864));
      ASSERT_TRUE(IsEqual(mz, -1050.3408864881));
      ASSERT_HR(presults->ComputePOIForces(lc, 204, mftLeft, lotMember, &fx, &fy, &mz));
      ASSERT_TRUE(IsEqual(fx, -81.434676038792));
      ASSERT_TRUE(IsEqual(fy, -148.54063267864));
      ASSERT_TRUE(IsEqual(mz, 0.0));
   }
};
} // namespace Fem2dUnitTests
