///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
///////////////////////////////////////////////////////////////////////
// TestDistributedLoad.cpp
//
// Ported from F:\ARP\WBFL\Fem2d\Test\TestDistributedLoad.cpp
#include "pch.h"

namespace Fem2dUnitTests
{

TEST_CLASS(TestDistributedLoad)
{
public:
   TEST_METHOD(BasicDistributedLoadOperations)
   {
      Fem2dModelFixture fixture;
      CComPtr<IFem2dModel>& pmodel = fixture.Model;

      CComPtr<IFem2dJointCollection> pJoints;
      ASSERT_HR(pmodel->get_Joints(&pJoints));

      CComPtr<IFem2dJoint> pJoint0, pJoint2, pJoint4, pJoint5;
      ASSERT_MC(fixture, pJoints->Create(0, 2, 3, &pJoint0));
      ASSERT_MC(fixture, pJoints->Create(2, 22, 32, &pJoint2));
      ASSERT_MC(fixture, pJoints->Create(4, 44, 34, &pJoint4));
      ASSERT_MC(fixture, pJoints->Create(5, 55, 35, &pJoint5));

      CComPtr<IFem2dMemberCollection> pMembers;
      ASSERT_HR(pmodel->get_Members(&pMembers));

      CComPtr<IFem2dMember> pMember0, pMember3, pMember4, pMember7, ptj;
      ASSERT_MC(fixture, pMembers->Create(0, 0, 2, 100, 105, &pMember0));
      ASSERT_MC(fixture, pMembers->Create(3, 2, 5, 110, 115, &pMember3));

      CComPtr<IFem2dLoadingCollection> pLoadings;
      ASSERT_HR(pmodel->get_Loadings(&pLoadings));

      CComPtr<IFem2dLoading> pLoading0, pLoading3, pl;
      ASSERT_LC(fixture, pLoadings->Create(0, &pLoading0));
      ASSERT_EQ(pLoadings->Create(0, &pl), FEM2D_E_LOADING_WITH_ID_ALREADY_EXISTS);
      ASSERT_LC(fixture, pLoadings->Create(3, &pLoading3));

      CComPtr<IFem2dDistributedLoadCollection> pDistributedLoads;
      ASSERT_HR(pLoading0->get_DistributedLoads(&pDistributedLoads));

      CComPtr<IFem2dDistributedLoad> pDistributedLoad0, pDistributedLoad3, pPl;
      ASSERT_LC(fixture, pDistributedLoads->Create(0, 0, loadDirFy, 0.0, 23.2, 42.3, 52.3, lotMember, &pDistributedLoad0));
      ASSERT_EQ(pDistributedLoads->Create(0, 0, loadDirFx, 0, 0, 0, 0, lotMember, &pPl), FEM2D_E_DIST_LOAD_WITH_ID_ALREADY_EXISTS);
      ASSERT_LC(fixture, pDistributedLoads->Create(3, 5, loadDirFy, 1.0, 33.0, 44.0, 55.0, lotMember, &pDistributedLoad3));

      LoadIDType loadID;
      ASSERT_HR(pDistributedLoad3->get_ID(&loadID));
      ASSERT_EQ(loadID, 3);

      MemberIDType mbrID;
      ASSERT_HR(pDistributedLoad3->get_MemberID(&mbrID));
      ASSERT_EQ(mbrID, 5);

      ASSERT_LC(fixture, pDistributedLoad3->put_MemberID(42));
      ASSERT_HR(pDistributedLoad3->get_MemberID(&mbrID));
      ASSERT_EQ(mbrID, 42);

      Fem2dLoadOrientation orientation;
      ASSERT_HR(pDistributedLoad3->get_Orientation(&orientation));
      ASSERT_EQ(orientation, lotMember);
      ASSERT_LC(fixture, pDistributedLoad3->put_Orientation(lotGlobal));
      ASSERT_HR(pDistributedLoad3->get_Orientation(&orientation));
      ASSERT_EQ(orientation, lotGlobal);

      Fem2dLoadDirection dir;
      ASSERT_HR(pDistributedLoad3->get_Direction(&dir));
      ASSERT_EQ(dir, loadDirFy);
      ASSERT_LC(fixture, pDistributedLoad3->put_Direction(loadDirFx));
      ASSERT_HR(pDistributedLoad3->get_Direction(&dir));
      ASSERT_EQ(dir, loadDirFx);

      Float64 loc;
      ASSERT_HR(pDistributedLoad3->get_StartLocation(&loc));
      ASSERT_EQ(loc, 1.0);
      ASSERT_LC(fixture, pDistributedLoad3->put_StartLocation(-.45));
      ASSERT_HR(pDistributedLoad3->get_StartLocation(&loc));
      ASSERT_EQ(loc, -.45);
      ASSERT_EQ(pDistributedLoad3->put_StartLocation(-4), FEM2D_E_INVALID_DIST_LOAD_LOCATION);

      ASSERT_HR(pDistributedLoad3->get_EndLocation(&loc));
      ASSERT_EQ(loc, 33.0);
      ASSERT_LC(fixture, pDistributedLoad3->put_EndLocation(-.65));
      ASSERT_HR(pDistributedLoad3->get_EndLocation(&loc));
      ASSERT_EQ(loc, -.65);
      ASSERT_EQ(pDistributedLoad3->put_EndLocation(-4), FEM2D_E_INVALID_DIST_LOAD_LOCATION);

      Float64 w;
      ASSERT_HR(pDistributedLoad3->get_WStart(&w));
      ASSERT_EQ(w, 44.0);
      ASSERT_LC(fixture, pDistributedLoad3->put_WStart(-.45));
      ASSERT_HR(pDistributedLoad3->get_WStart(&w));
      ASSERT_EQ(w, -.45);

      ASSERT_HR(pDistributedLoad3->get_WEnd(&w));
      ASSERT_EQ(w, 55.0);
      ASSERT_LC(fixture, pDistributedLoad3->put_WEnd(-1.45));
      ASSERT_HR(pDistributedLoad3->get_WEnd(&w));
      ASSERT_EQ(w, -1.45);

      LoadCaseIDType ld;
      ASSERT_HR(pDistributedLoad3->get_Loading(&ld));
      ASSERT_EQ(ld, 0);
   }
};
} // namespace Fem2dUnitTests
