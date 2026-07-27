///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
///////////////////////////////////////////////////////////////////////
// TestJointLoad.cpp
//
// Ported from F:\ARP\WBFL\Fem2d\Test\TestJointLoad.cpp
#include "pch.h"

namespace Fem2dUnitTests
{

TEST_CLASS(TestJointLoad)
{
public:
   TEST_METHOD(BasicJointLoadOperations)
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

      CComPtr<IFem2dJointLoadCollection> pJointLoads;
      ASSERT_HR(pLoading0->get_JointLoads(&pJointLoads));

      CComPtr<IFem2dJointLoad> pJointLoad0, pJointLoad3, pjl;
      ASSERT_LC(fixture, pJointLoads->Create(0, 0, 23.2, 42.3, 52.3, &pJointLoad0));
      ASSERT_EQ(pJointLoads->Create(0, 0, 0, 0, 0, &pjl), FEM2D_E_JOINT_LOAD_WITH_ID_ALREADY_EXISTS);
      ASSERT_LC(fixture, pJointLoads->Create(3, 5, 33, 44, 55, &pJointLoad3));

      LoadIDType loadID;
      ASSERT_HR(pJointLoad3->get_ID(&loadID));
      ASSERT_EQ(loadID, 3);

      JointIDType jntID;
      ASSERT_HR(pJointLoad3->get_JointID(&jntID));
      ASSERT_EQ(jntID, 5);

      ASSERT_HR(pJointLoad3->put_JointID(42));
      ASSERT_HR(pJointLoad3->get_JointID(&jntID));
      ASSERT_EQ(jntID, 42);

      Float64 fx, fy, mz;
      ASSERT_HR(pJointLoad3->get_Fx(&fx));
      ASSERT_HR(pJointLoad3->get_Fy(&fy));
      ASSERT_HR(pJointLoad3->get_Mz(&mz));
      ASSERT_EQ(fx, 33);
      ASSERT_EQ(fy, 44);
      ASSERT_EQ(mz, 55);

      ASSERT_LC(fixture, pJointLoad3->put_Fx(-11));
      ASSERT_LC(fixture, pJointLoad3->put_Fy(-12));
      ASSERT_LC(fixture, pJointLoad3->put_Mz(-13));
      ASSERT_HR(pJointLoad3->get_Fx(&fx));
      ASSERT_HR(pJointLoad3->get_Fy(&fy));
      ASSERT_HR(pJointLoad3->get_Mz(&mz));
      ASSERT_EQ(fx, -11);
      ASSERT_EQ(fy, -12);
      ASSERT_EQ(mz, -13);

      ASSERT_HR(pJointLoad3->GetForce(&fx, &fy, &mz));
      ASSERT_EQ(fx, -11);
      ASSERT_EQ(fy, -12);
      ASSERT_EQ(mz, -13);

      ASSERT_LC(fixture, pJointLoad3->SetForce(22, 23, 24));
      ASSERT_HR(pJointLoad3->GetForce(&fx, &fy, &mz));
      ASSERT_EQ(fx, 22);
      ASSERT_EQ(fy, 23);
      ASSERT_EQ(mz, 24);

      // play some games with the reference counter - dropping the parent
      // pointers must not invalidate the still-held pJointLoad3
      pLoading0 = 0;
      pJointLoads = 0;

      ASSERT_HR(pJointLoad3->get_Fx(&fx));
      ASSERT_HR(pJointLoad3->get_Fy(&fy));
      ASSERT_HR(pJointLoad3->get_Mz(&mz));
      ASSERT_EQ(fx, 22);
      ASSERT_EQ(fy, 23);
      ASSERT_EQ(mz, 24);

      LoadCaseIDType ld;
      ASSERT_HR(pJointLoad3->get_Loading(&ld));
      ASSERT_EQ(ld, 0);
   }
};
} // namespace Fem2dUnitTests
