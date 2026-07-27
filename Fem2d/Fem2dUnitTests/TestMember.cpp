///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
///////////////////////////////////////////////////////////////////////
// TestMember.cpp
//
// Ported from F:\ARP\WBFL\Fem2d\Test\TestMember.cpp
#include "pch.h"

namespace Fem2dUnitTests
{

TEST_CLASS(TestMember)
{
public:
   TEST_METHOD(BasicMemberOperations)
   {
      Fem2dModelFixture fixture;
      CComPtr<IFem2dModel>& pmodel = fixture.Model;

      CComQIPtr<IFem2dModelResults> presults(pmodel);

      // some error checking
      Float64 dx, dy, rz;
      ASSERT_EQ(presults->ComputeJointDeflections(0, 0, &dx, &dy, &rz), FEM2D_E_MODEL_HAS_NO_JOINTS);

      CComPtr<IFem2dJointCollection> pJoints;
      ASSERT_HR(pmodel->get_Joints(&pJoints));

      CComPtr<IFem2dJoint> pJoint0, pJoint2, pJoint4, pJoint5, pJoint6;
      ASSERT_MC(fixture, pJoints->Create(0, 2, 3, &pJoint0));
      ASSERT_MC(fixture, pJoints->Create(2, 22, 32, &pJoint2));
      ASSERT_MC(fixture, pJoints->Create(4, 44, 34, &pJoint4));
      ASSERT_MC(fixture, pJoints->Create(5, 55, 35, &pJoint5));
      ASSERT_MC(fixture, pJoints->Create(6, 55, 35, &pJoint6)); // same loc as joint 5

      ASSERT_EQ(presults->ComputeJointDeflections(0, 0, &dx, &dy, &rz), FEM2D_E_MODEL_HAS_NO_MEMBERS);

      CComPtr<IFem2dMemberCollection> pMembers;
      ASSERT_HR(pmodel->get_Members(&pMembers));

      CComPtr<IFem2dMember> pMember0, pMember3, pMember4, pMember5, pMember7, ptj;
      ASSERT_MC(fixture, pMembers->Create(0, 0, 2, 100, 105, &pMember0));
      ASSERT_MC(fixture, pMembers->Create(3, 2, 5, 110, 115, &pMember3));
      ASSERT_EQ(pMembers->Create(3, 2, 5, 110, 115, &ptj), FEM2D_E_MEMBER_WITH_ID_ALREADY_EXISTS);
      ASSERT_MC(fixture, pMembers->Create(4, 54, 5, 110, 115, &pMember4)); // joint doesn't exist
      ASSERT_EQ(pMembers->Create(7, 4, 4, 120, 125, &pMember7), FEM2D_E_MEMBER_HAS_SAME_JOINTS);
      ASSERT_MC(fixture, pMembers->Create(5, 5, 6, 110, 115, &pMember5)); // zero length

      MemberIDType id;
      ASSERT_HR(pMember3->get_ID(&id));
      ASSERT_EQ(id, 3);

      Float64 len;
      ASSERT_HR(pMember3->get_Length(&len));
      ASSERT_EQ(len, sqrt(1098.));

      ASSERT_EQ(pMember5->get_Length(&len), FEM2D_E_ZERO_LENGTH_MEMBER);

      ASSERT_EQ(pMember4->get_Length(&len), FEM2D_E_MEMBER_JOINT_NOT_EXISTS);

      JointIDType startJoint, endJoint;
      ASSERT_HR(pMember0->get_StartJoint(&startJoint));
      ASSERT_HR(pMember0->get_EndJoint(&endJoint));
      ASSERT_EQ(startJoint, 0);
      ASSERT_EQ(endJoint, 2);

      ASSERT_MC(fixture, pMember0->put_StartJoint(3));
      ASSERT_MC(fixture, pMember0->put_EndJoint(0));
      ASSERT_HR(pMember0->get_StartJoint(&startJoint));
      ASSERT_HR(pMember0->get_EndJoint(&endJoint));
      ASSERT_EQ(startJoint, 3);
      ASSERT_EQ(endJoint, 0);

      Float64 EA, EI;
      ASSERT_HR(pMember0->get_EA(&EA));
      ASSERT_HR(pMember0->get_EI(&EI));
      ASSERT_EQ(EA, 100);
      ASSERT_EQ(EI, 105);

      ASSERT_MC(fixture, pMember0->put_EA(3));
      ASSERT_MC(fixture, pMember0->put_EI(4));
      ASSERT_HR(pMember0->get_EA(&EA));
      ASSERT_HR(pMember0->get_EI(&EI));
      ASSERT_EQ(EA, 3);
      ASSERT_EQ(EI, 4);

      ASSERT_EQ(pMember0->put_EA(-2.0), FEM2D_E_STIFFNESS_MUST_BE_POSITIVE);
      ASSERT_EQ(pMember0->put_EI(-2.0), FEM2D_E_STIFFNESS_MUST_BE_POSITIVE);
      ASSERT_HR(pMember0->get_EA(&EA));
      ASSERT_HR(pMember0->get_EI(&EI));
      ASSERT_EQ(EA, 3);
      ASSERT_EQ(EI, 4);

      VARIANT_BOOL rel;
      // members start life without any end releases
      ASSERT_HR(pMember0->IsReleased(metStart, mbrReleaseMz, &rel));
      ASSERT_EQ(rel, VARIANT_FALSE);
      ASSERT_HR(pMember0->IsReleased(metStart, mbrReleaseFx, &rel));
      ASSERT_EQ(rel, VARIANT_FALSE);
      ASSERT_HR(pMember0->IsReleased(metStart, mbrReleaseNone, &rel));
      ASSERT_EQ(rel, VARIANT_TRUE);
      ASSERT_HR(pMember0->IsReleased(metEnd, mbrReleaseMz, &rel));
      ASSERT_EQ(rel, VARIANT_FALSE);
      ASSERT_HR(pMember0->IsReleased(metEnd, mbrReleaseFx, &rel));
      ASSERT_EQ(rel, VARIANT_FALSE);
      ASSERT_HR(pMember0->IsReleased(metEnd, mbrReleaseNone, &rel));
      ASSERT_EQ(rel, VARIANT_TRUE);

      ASSERT_MC(fixture, pMember0->ReleaseEnd(metStart, mbrReleaseMz));
      ASSERT_HR(pMember0->IsReleased(metStart, mbrReleaseMz, &rel));
      ASSERT_EQ(rel, VARIANT_TRUE);
      ASSERT_HR(pMember0->IsReleased(metStart, mbrReleaseFx, &rel));
      ASSERT_EQ(rel, VARIANT_FALSE);
      ASSERT_HR(pMember0->IsReleased(metStart, mbrReleaseNone, &rel));
      ASSERT_EQ(rel, VARIANT_FALSE);
      ASSERT_MC(fixture, pMember0->ReleaseEnd(metEnd, mbrReleaseMz));
      ASSERT_HR(pMember0->IsReleased(metEnd, mbrReleaseMz, &rel));
      ASSERT_EQ(rel, VARIANT_TRUE);
      ASSERT_HR(pMember0->IsReleased(metEnd, mbrReleaseFx, &rel));
      ASSERT_EQ(rel, VARIANT_FALSE);
      ASSERT_HR(pMember0->IsReleased(metEnd, mbrReleaseNone, &rel));
      ASSERT_EQ(rel, VARIANT_FALSE);

      ASSERT_MC(fixture, pMember0->ReleaseEnd(metStart, mbrReleaseNone));
      ASSERT_MC(fixture, pMember0->ReleaseEnd(metEnd, mbrReleaseNone));
      ASSERT_MC(fixture, pMember0->ReleaseEnd(metStart, mbrReleaseFx));
      ASSERT_HR(pMember0->IsReleased(metStart, mbrReleaseFx, &rel));
      ASSERT_EQ(rel, VARIANT_TRUE);
      ASSERT_HR(pMember0->IsReleased(metStart, mbrReleaseMz, &rel));
      ASSERT_EQ(rel, VARIANT_FALSE);
      ASSERT_HR(pMember0->IsReleased(metStart, mbrReleaseNone, &rel));
      ASSERT_EQ(rel, VARIANT_FALSE);
      ASSERT_MC(fixture, pMember0->ReleaseEnd(metEnd, mbrReleaseFx));
      ASSERT_HR(pMember0->IsReleased(metEnd, mbrReleaseFx, &rel));
      ASSERT_EQ(rel, VARIANT_TRUE);
      ASSERT_HR(pMember0->IsReleased(metEnd, mbrReleaseMz, &rel));
      ASSERT_EQ(rel, VARIANT_FALSE);
      ASSERT_HR(pMember0->IsReleased(metEnd, mbrReleaseNone, &rel));
      ASSERT_EQ(rel, VARIANT_FALSE);

      ASSERT_MC(fixture, pMember0->ReleaseEnd(metStart, mbrReleaseNone));
      ASSERT_MC(fixture, pMember0->ReleaseEnd(metEnd, mbrReleaseNone));
      ASSERT_HR(pMember0->IsReleased(metStart, mbrReleaseMz, &rel));
      ASSERT_EQ(rel, VARIANT_FALSE);
      ASSERT_HR(pMember0->IsReleased(metEnd, mbrReleaseMz, &rel));
      ASSERT_EQ(rel, VARIANT_FALSE);
   }
};
} // namespace Fem2dUnitTests
