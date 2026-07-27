///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
///////////////////////////////////////////////////////////////////////
// TestJointDisplacement.cpp
//
// Ported from F:\ARP\WBFL\Fem2d\Test\TestJointDisplacement.cpp. Note the COM
// interface itself is named IFem2dJointDeflection (a prescribed support
// settlement load) even though the file/coclass is called "JointDisplacement" -
// this is a pre-existing naming quirk in the IDL, preserved here verbatim.
#include "pch.h"

namespace Fem2dUnitTests
{

TEST_CLASS(TestJointDisplacement)
{
public:
   TEST_METHOD(BasicJointDeflectionOperations)
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

      CComPtr<IFem2dJointDeflectionCollection> pJointDeflections;
      ASSERT_HR(pLoading0->get_JointDeflections(&pJointDeflections));

      CComPtr<IFem2dJointDeflection> pJointDeflection0, pJointDeflection3, pjl;
      ASSERT_LC(fixture, pJointDeflections->Create(0, 0, 23.2, 42.3, 52.3, &pJointDeflection0));
      ASSERT_EQ(pJointDeflections->Create(0, 0, 0, 0, 0, &pjl), FEM2D_E_JOINT_DISP_WITH_ID_ALREADY_EXISTS);
      ASSERT_LC(fixture, pJointDeflections->Create(3, 5, 33, 44, 55, &pJointDeflection3));

      LoadIDType loadID;
      ASSERT_HR(pJointDeflection3->get_ID(&loadID));
      ASSERT_EQ(loadID, 3);

      JointIDType jntID;
      ASSERT_HR(pJointDeflection3->get_JointID(&jntID));
      ASSERT_EQ(jntID, 5);

      ASSERT_LC(fixture, pJointDeflection3->put_JointID(42));
      ASSERT_HR(pJointDeflection3->get_JointID(&jntID));
      ASSERT_EQ(jntID, 42);

      Float64 dx, dy, rz;
      ASSERT_HR(pJointDeflection3->get_Dx(&dx));
      ASSERT_HR(pJointDeflection3->get_Dy(&dy));
      ASSERT_HR(pJointDeflection3->get_Rz(&rz));
      ASSERT_EQ(dx, 33);
      ASSERT_EQ(dy, 44);
      ASSERT_EQ(rz, 55);

      ASSERT_LC(fixture, pJointDeflection3->put_Dx(-11));
      ASSERT_LC(fixture, pJointDeflection3->put_Dy(-12));
      ASSERT_LC(fixture, pJointDeflection3->put_Rz(-13));
      ASSERT_HR(pJointDeflection3->get_Dx(&dx));
      ASSERT_HR(pJointDeflection3->get_Dy(&dy));
      ASSERT_HR(pJointDeflection3->get_Rz(&rz));
      ASSERT_EQ(dx, -11);
      ASSERT_EQ(dy, -12);
      ASSERT_EQ(rz, -13);

      ASSERT_HR(pJointDeflection3->GetDeflection(&dx, &dy, &rz));
      ASSERT_EQ(dx, -11);
      ASSERT_EQ(dy, -12);
      ASSERT_EQ(rz, -13);

      ASSERT_LC(fixture, pJointDeflection3->SetDeflection(22, 23, 24));
      ASSERT_HR(pJointDeflection3->GetDeflection(&dx, &dy, &rz));
      ASSERT_EQ(dx, 22);
      ASSERT_EQ(dy, 23);
      ASSERT_EQ(rz, 24);

      // play some games with the reference counter
      pLoading0 = 0;
      pJointDeflections = 0;

      ASSERT_HR(pJointDeflection3->get_Dx(&dx));
      ASSERT_HR(pJointDeflection3->get_Dy(&dy));
      ASSERT_HR(pJointDeflection3->get_Rz(&rz));
      ASSERT_EQ(dx, 22);
      ASSERT_EQ(dy, 23);
      ASSERT_EQ(rz, 24);
   }
};
} // namespace Fem2dUnitTests
