///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
///////////////////////////////////////////////////////////////////////
// TestPOI.cpp
//
// Ported from F:\ARP\WBFL\Fem2d\Test\TestPOI.cpp
#include "pch.h"

namespace Fem2dUnitTests
{

TEST_CLASS(TestPOI)
{
public:
   TEST_METHOD(BasicPOIOperations)
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

      // create some members
      CComPtr<IFem2dMemberCollection> pMembers;
      ASSERT_HR(pmodel->get_Members(&pMembers));

      CComPtr<IFem2dMember> pMember0, pMember3, pMember4;
      ASSERT_MC(fixture, pMembers->Create(0, 0, 2, 100, 105, &pMember0));
      ASSERT_MC(fixture, pMembers->Create(3, 2, 5, 110, 115, &pMember3));
      ASSERT_MC(fixture, pMembers->Create(4, 54, 5, 110, 115, &pMember4)); // joint doesn't exist

      // create some pois
      CComPtr<IFem2dPOICollection> pPOIs;
      ASSERT_HR(pmodel->get_POIs(&pPOIs));

      CComPtr<IFem2dPOI> pPOI0, pPOI3, pPOI4;
      ASSERT_HR(pPOIs->Create(0, 1, -.5, &pPOI0));
      ASSERT_HR(pPOIs->Create(3, 4, 1.2, &pPOI3));
      ASSERT_EQ(pPOIs->Create(3, 4, 1.2, &pPOI4), FEM2D_E_POI_WITH_ID_ALREADY_EXISTS);
      ASSERT_EQ(pPOIs->Create(4, 4, -12.0, &pPOI4), FEM2D_E_INVALID_POI_LOCATION);

      PoiIDType id;
      MemberIDType mid;
      ASSERT_HR(pPOI0->get_ID(&id));
      ASSERT_EQ(id, 0);
      ASSERT_HR(pPOI3->get_ID(&id));
      ASSERT_EQ(id, 3);
      ASSERT_HR(pPOI0->get_MemberID(&mid));
      ASSERT_EQ(mid, 1);
      ASSERT_HR(pPOI3->get_MemberID(&mid));
      ASSERT_EQ(mid, 4);

      ASSERT_HR(pPOI3->put_MemberID(33));
      ASSERT_HR(pPOI3->get_MemberID(&mid));
      ASSERT_EQ(mid, 33);

      Float64 loc;
      ASSERT_HR(pPOI0->get_Location(&loc));
      ASSERT_EQ(loc, -0.5);
      ASSERT_HR(pPOI3->get_Location(&loc));
      ASSERT_EQ(loc, 1.2);

      ASSERT_HR(pPOI3->put_Location(23.3));
      ASSERT_HR(pPOI3->get_Location(&loc));
      ASSERT_EQ(loc, 23.3);

      ASSERT_HR(pPOI3->put_Location(-1.0));
      ASSERT_EQ(pPOI3->put_Location(-1.01), FEM2D_E_INVALID_POI_LOCATION);
   }
};
} // namespace Fem2dUnitTests
