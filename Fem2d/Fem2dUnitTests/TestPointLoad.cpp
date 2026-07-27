///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
///////////////////////////////////////////////////////////////////////
// TestPointLoad.cpp
//
// Ported from F:\ARP\WBFL\Fem2d\Test\TestPointLoad.cpp
#include "pch.h"

namespace Fem2dUnitTests
{

TEST_CLASS(TestPointLoad)
{
public:
   TEST_METHOD(BasicPointLoadOperations)
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

      CComPtr<IFem2dPointLoadCollection> pPointLoads;
      ASSERT_HR(pLoading0->get_PointLoads(&pPointLoads));

      CComPtr<IFem2dPointLoad> pPointLoad0, pPointLoad3, pPl;
      ASSERT_LC(fixture, pPointLoads->Create(0, 0, 0.0, 23.2, 42.3, 52.3, lotMember, &pPointLoad0));
      ASSERT_EQ(pPointLoads->Create(0, 0, 0, 0, 0, 0, lotMember, &pPl), FEM2D_E_POINT_LOAD_WITH_ID_ALREADY_EXISTS);
      ASSERT_LC(fixture, pPointLoads->Create(3, 5, 1.0, 33.0, 44.0, 55.0, lotMember, &pPointLoad3));

      IndexType num;
      ASSERT_HR(pPointLoads->get_Count(&num));
      ASSERT_EQ(num, 2);

      LoadIDType loadID;
      ASSERT_HR(pPointLoad3->get_ID(&loadID));
      ASSERT_EQ(loadID, 3);

      MemberIDType mbrID;
      ASSERT_HR(pPointLoad3->get_MemberID(&mbrID));
      ASSERT_EQ(mbrID, 5);

      ASSERT_LC(fixture, pPointLoad3->put_MemberID(42));
      ASSERT_HR(pPointLoad3->get_MemberID(&mbrID));
      ASSERT_EQ(mbrID, 42);

      Fem2dLoadOrientation orientation;
      ASSERT_HR(pPointLoad3->get_Orientation(&orientation));
      ASSERT_EQ(orientation, lotMember);
      ASSERT_LC(fixture, pPointLoad3->put_Orientation(lotGlobal));
      ASSERT_HR(pPointLoad3->get_Orientation(&orientation));
      ASSERT_EQ(orientation, lotGlobal);

      Float64 loc;
      ASSERT_HR(pPointLoad3->get_Location(&loc));
      ASSERT_EQ(loc, 1.0);
      ASSERT_LC(fixture, pPointLoad3->put_Location(-.4));
      ASSERT_HR(pPointLoad3->get_Location(&loc));
      ASSERT_EQ(loc, -.4);
      ASSERT_EQ(pPointLoad3->put_Location(-4), FEM2D_E_INVALID_POINT_LOAD_LOCATION);

      Float64 fx, fy, mz;
      ASSERT_HR(pPointLoad3->get_Fx(&fx));
      ASSERT_HR(pPointLoad3->get_Fy(&fy));
      ASSERT_HR(pPointLoad3->get_Mz(&mz));
      ASSERT_EQ(fx, 33);
      ASSERT_EQ(fy, 44);
      ASSERT_EQ(mz, 55);

      ASSERT_LC(fixture, pPointLoad3->put_Fx(-11));
      ASSERT_LC(fixture, pPointLoad3->put_Fy(-12));
      ASSERT_LC(fixture, pPointLoad3->put_Mz(-13));
      ASSERT_HR(pPointLoad3->get_Fx(&fx));
      ASSERT_HR(pPointLoad3->get_Fy(&fy));
      ASSERT_HR(pPointLoad3->get_Mz(&mz));
      ASSERT_EQ(fx, -11);
      ASSERT_EQ(fy, -12);
      ASSERT_EQ(mz, -13);

      ASSERT_HR(pPointLoad3->GetForce(&fx, &fy, &mz));
      ASSERT_EQ(fx, -11);
      ASSERT_EQ(fy, -12);
      ASSERT_EQ(mz, -13);

      ASSERT_HR(pPointLoad3->SetForce(22, 23, 24));
      ASSERT_HR(pPointLoad3->GetForce(&fx, &fy, &mz));
      ASSERT_EQ(fx, 22);
      ASSERT_EQ(fy, 23);
      ASSERT_EQ(mz, 24);

      // play some games with the reference counter
      pLoading0 = 0;

      ASSERT_HR(pPointLoad3->get_Fx(&fx));
      ASSERT_HR(pPointLoad3->get_Fy(&fy));
      ASSERT_HR(pPointLoad3->get_Mz(&mz));
      ASSERT_EQ(fx, 22);
      ASSERT_EQ(fy, 23);
      ASSERT_EQ(mz, 24);

      ASSERT_EQ(pPointLoads->Remove(5, atID, &loadID), E_INVALIDARG);
      ASSERT_LC(fixture, pPointLoads->Remove(3, atID, &loadID));
      ASSERT_HR(pPointLoads->get_Count(&num));
      ASSERT_EQ(num, 1);

      pPointLoads = 0;

      LoadCaseIDType ld;
      ASSERT_HR(pPointLoad3->get_Loading(&ld));
      ASSERT_EQ(ld, 0);
   }
};
} // namespace Fem2dUnitTests
