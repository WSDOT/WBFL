///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
///////////////////////////////////////////////////////////////////////
// TestInstability.cpp
//
// Ported from F:\ARP\WBFL\Fem2d\Test\TestInstability.cpp - verifies that
// singular/unstable models produce well-defined error HRESULTs rather than
// crashing or returning garbage.
#include "pch.h"

namespace Fem2dUnitTests
{

TEST_CLASS(TestInstability)
{
public:
   TEST_METHOD(SingularModelsReturnWellDefinedErrors)
   {
      /*////////////////////////////////////////////////////
              1              2             3
              o--------------o-------------o
              ^       1             1      ^
      *////////////////////////////////////////////////////

      Fem2dModelFixture fixture;
      CComPtr<IFem2dModel>& pmodel = fixture.Model;

      CComPtr<IFem2dJointCollection> pJoints;
      ASSERT_HR(pmodel->get_Joints(&pJoints));

      CComPtr<IFem2dJoint> pJoint1, pJoint2, pJoint3;
      ASSERT_MC(fixture, pJoints->Create(1, 0.0, 0.0, &pJoint1));
      ASSERT_MC(fixture, pJoints->Create(2, 0.0, 10.0, &pJoint2));
      ASSERT_MC(fixture, pJoints->Create(3, 0.0, 20.0, &pJoint3));

      CComQIPtr<IFem2dModelResults> presults(pmodel);

      CComPtr<IFem2dMemberCollection> pMembers;
      ASSERT_HR(pmodel->get_Members(&pMembers));

      Float64 E = 29000;
      Float64 A = 10;
      Float64 I = 250;
      CComPtr<IFem2dMember> pMember1, pMember2;
      ASSERT_MC(fixture, pMembers->Create(1, 1, 2, E * A, E * I, &pMember1));
      ASSERT_MC(fixture, pMembers->Create(2, 2, 3, E * A, E * I, &pMember2));

      CComPtr<IFem2dLoadingCollection> pLoadings;
      ASSERT_HR(pmodel->get_Loadings(&pLoadings));
      CComPtr<IFem2dLoading> pLoading0;
      ASSERT_LC(fixture, pLoadings->Create(0, &pLoading0));
      CComPtr<IFem2dDistributedLoadCollection> pDistributedLoads;
      ASSERT_HR(pLoading0->get_DistributedLoads(&pDistributedLoads));
      CComPtr<IFem2dDistributedLoad> pDistributedLoad;
      ASSERT_LC(fixture, pDistributedLoads->Create(1, 1, loadDirFy, 0.0, -1.0, -0.5, -1.0, lotMember, &pDistributedLoad));

      // no boundary conditions - we're flying through space
      Float64 dx, dy, rz;
      ASSERT_EQ(presults->ComputeJointDeflections(0, 2, &dx, &dy, &rz), FEM2D_E_MATRIX_FACTORING);

      // support end, should now be cantilever - ok
      ASSERT_MC(fixture, pJoint1->Support());
      ASSERT_HR(presults->ComputeJointDeflections(0, 2, &dx, &dy, &rz));

      // now a floppy cantilever
      ASSERT_MC(fixture, pJoint1->ReleaseDof(jrtMz));
      ASSERT_EQ(presults->ComputeJointDeflections(0, 2, &dx, &dy, &rz), FEM2D_E_MATRIX_BACK_SUBSTITUTION);

      // now pin-pin
      ASSERT_MC(fixture, pJoint3->Support());
      ASSERT_MC(fixture, pJoint3->ReleaseDof(jrtMz));
      ASSERT_HR(presults->ComputeJointDeflections(0, 2, &dx, &dy, &rz));

      // put a hinge in the end of member 1
      ASSERT_MC(fixture, pMember1->ReleaseEnd(metEnd, mbrReleaseMz));
      ASSERT_EQ(presults->ComputeJointDeflections(0, 2, &dx, &dy, &rz), FEM2D_E_MATRIX_BACK_SUBSTITUTION);

      ASSERT_MC(fixture, pMember1->ReleaseEnd(metEnd, mbrReleaseNone));
      ASSERT_HR(presults->ComputeJointDeflections(0, 2, &dx, &dy, &rz));

      // pin at a released dof
      ASSERT_MC(fixture, pMember1->ReleaseEnd(metStart, mbrReleaseMz));
      ASSERT_EQ(presults->ComputeJointDeflections(0, 2, &dx, &dy, &rz), FEM2D_E_MATRIX_FACTORING);

      // pin at start of member 2
      ASSERT_MC(fixture, pMember1->ReleaseEnd(metStart, mbrReleaseNone));
      ASSERT_MC(fixture, pMember2->ReleaseEnd(metStart, mbrReleaseMz));
      ASSERT_EQ(presults->ComputeJointDeflections(0, 2, &dx, &dy, &rz), FEM2D_E_MATRIX_BACK_SUBSTITUTION);
   }
};
} // namespace Fem2dUnitTests
