///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
///////////////////////////////////////////////////////////////////////
// TestJoint.cpp
//
// Ported from F:\ARP\WBFL\Fem2d\Test\TestJoint.cpp (legacy WBFLTest.h harness)
// to MSVC CppUnitTestFramework, talking to WBFLFem2d.dll purely through its
// public COM interfaces (see Fem2dTestUtil.h).
#include "pch.h"

namespace Fem2dUnitTests
{

TEST_CLASS(TestJoint)
{
public:
   TEST_METHOD(BasicJointOperations)
   {
      Fem2dModelFixture fixture;
      CComPtr<IFem2dModel>& pmodel = fixture.Model;

      CComPtr<IFem2dJointCollection> pJoints;
      ASSERT_HR(pmodel->get_Joints(&pJoints));

      CComPtr<IFem2dJoint> pJoint0, pJoint2, pJoint4, pJoint5, ptj;
      ASSERT_MC(fixture, pJoints->Create(0, 2, 3, &pJoint0));
      ASSERT_MC(fixture, pJoints->Create(2, 22, 32, &pJoint2));
      ASSERT_MC(fixture, pJoints->Create(4, 44, 34, &pJoint4));
      ASSERT_MC(fixture, pJoints->Create(5, 55, 35, &pJoint5));
      ASSERT_EQ(pJoints->Create(5, 55, 35, &ptj), FEM2D_E_JOINT_WITH_ID_ALREADY_EXISTS);

      // grab a joint by id and check its data
      CComPtr<IFem2dJoint> pj2r;
      ASSERT_HR(pJoints->Find(2, &pj2r));
      LoadIDType id;
      Float64 x, y;
      ASSERT_HR(pj2r->get_ID(&id));
      ASSERT_HR(pj2r->get_X(&x));
      ASSERT_HR(pj2r->get_Y(&y));
      ASSERT_EQ(id, 2);
      ASSERT_EQ(x, 22);
      ASSERT_EQ(y, 32);

      ASSERT_MC(fixture, pj2r->put_X(200.));
      ASSERT_MC(fixture, pj2r->put_Y(300.));
      ASSERT_HR(pj2r->get_X(&x));
      ASSERT_HR(pj2r->get_Y(&y));
      ASSERT_EQ(x, 200);
      ASSERT_EQ(y, 300);

      pj2r = 0;

      ASSERT_HR(pJoints->Find(5, &pj2r));
      ASSERT_HR(pj2r->get_ID(&id));
      ASSERT_HR(pj2r->get_X(&x));
      ASSERT_HR(pj2r->get_Y(&y));
      ASSERT_EQ(id, 5);
      ASSERT_EQ(x, 55);
      ASSERT_EQ(y, 35);

      IndexType cnt;
      ASSERT_HR(pJoints->get_Count(&cnt));
      ASSERT_EQ(cnt, 4);

      // create some members and connect them to joints
      CComPtr<IFem2dMemberCollection> pMembers;
      ASSERT_HR(pmodel->get_Members(&pMembers));

      CComPtr<IFem2dMember> pMember0, pMember1, pMember2, pMember3, pMember7;
      ASSERT_MC(fixture, pMembers->Create(0, 0, 2, 100, 105, &pMember0));
      ASSERT_MC(fixture, pMembers->Create(1, 0, 4, 110, 115, &pMember1));
      ASSERT_MC(fixture, pMembers->Create(2, 5, 4, 110, 115, &pMember2));
      ASSERT_MC(fixture, pMembers->Create(3, 5, 2, 110, 115, &pMember3));
      ASSERT_MC(fixture, pMembers->Create(7, 5, 0, 110, 115, &pMember7));

      // look at members connected to joint 0
      CComPtr<IIDArray> pMbrIds;
      ASSERT_HR(pJoint0->get_Members(&pMbrIds));
      ASSERT_HR(pMbrIds->get_Count(&cnt));
      ASSERT_EQ(cnt, 3);

      MemberIDType mbID;
      ASSERT_HR(pMbrIds->get_Item(0, &mbID));
      ASSERT_EQ(mbID, 0);
      ASSERT_HR(pMbrIds->get_Item(1, &mbID));
      ASSERT_EQ(mbID, 1);
      ASSERT_HR(pMbrIds->get_Item(2, &mbID));
      ASSERT_EQ(mbID, 7);
      ASSERT_EQ(pMbrIds->get_Item(3, &mbID), E_INVALIDARG);

      JointIDType jntID;
      ASSERT_MC(fixture, pJoints->Remove(2, atID, &jntID));
      ASSERT_EQ(jntID, 2);
      ASSERT_MC(fixture, pJoints->Remove(1, atIndex, &jntID));
      ASSERT_EQ(jntID, 4);

      ASSERT_HR(pJoints->get_Count(&cnt));
      ASSERT_EQ(cnt, 2);

      CComPtr<IFem2dEnumJoint> penum;
      ASSERT_HR(pJoints->get__EnumElements(&penum));

      IFem2dJoint* pj;
      unsigned long num_fetched = 0;
      long i = 0;
      ASSERT_HR(penum->Next(1, &pj, &num_fetched));
      while (num_fetched == 1)
      {
         ASSERT_HR(pj->get_ID(&id));
         ASSERT_HR(pj->get_X(&x));
         ASSERT_HR(pj->get_Y(&y));

         if (i == 0)
         {
            ASSERT_EQ(id, 0);
            ASSERT_EQ(x, 2);
            ASSERT_EQ(y, 3);
         }
         else if (i == 1)
         {
            ASSERT_EQ(id, 5);
            ASSERT_EQ(x, 55);
            ASSERT_EQ(y, 35);
         }

         pj->Release();
         ASSERT_EQ(FAILED(penum->Next(1, &pj, &num_fetched)), FALSE);
         i++;
      }

      ASSERT_EQ(i, 2);

      CComPtr<IFem2dJoint> psj;
      ASSERT_EQ(pJoints->get_Item(2, &psj), E_INVALIDARG);

      pj = 0;
      ASSERT_HR(pJoints->get_Item(0, &psj));
      ASSERT_HR(psj->get_ID(&id));
      ASSERT_EQ(id, 0);

      // test releases on joints
      VARIANT_BOOL st;
      ASSERT_HR(psj->IsSupport(&st));
      ASSERT_EQ(st, VARIANT_FALSE);
      ASSERT_HR(psj->IsDofReleased(jrtNone, &st));
      ASSERT_EQ(st, VARIANT_FALSE);
      ASSERT_HR(psj->IsDofReleased(jrtFx, &st));
      ASSERT_EQ(st, VARIANT_TRUE);
      ASSERT_HR(psj->IsDofReleased(jrtFy, &st));
      ASSERT_EQ(st, VARIANT_TRUE);
      ASSERT_HR(psj->IsDofReleased(jrtMz, &st));
      ASSERT_EQ(st, VARIANT_TRUE);
      ASSERT_HR(psj->IsDofReleased(jrtAll, &st));
      ASSERT_EQ(st, VARIANT_TRUE);
      ASSERT_HR(psj->IsDofSupported(jrtNone, &st));
      ASSERT_EQ(st, VARIANT_TRUE);
      ASSERT_HR(psj->IsDofSupported(jrtFx, &st));
      ASSERT_EQ(st, VARIANT_FALSE);
      ASSERT_HR(psj->IsDofSupported(jrtFy, &st));
      ASSERT_EQ(st, VARIANT_FALSE);
      ASSERT_HR(psj->IsDofSupported(jrtMz, &st));
      ASSERT_EQ(st, VARIANT_FALSE);
      ASSERT_HR(psj->IsDofSupported(jrtAll, &st));
      ASSERT_EQ(st, VARIANT_FALSE);

      ASSERT_HR(psj->Support());
      ASSERT_HR(psj->IsSupport(&st));
      ASSERT_EQ(st, VARIANT_TRUE);
      ASSERT_HR(psj->IsDofReleased(jrtNone, &st));
      ASSERT_EQ(st, VARIANT_TRUE);
      ASSERT_HR(psj->IsDofReleased(jrtFx, &st));
      ASSERT_EQ(st, VARIANT_FALSE);
      ASSERT_HR(psj->IsDofReleased(jrtFy, &st));
      ASSERT_EQ(st, VARIANT_FALSE);
      ASSERT_HR(psj->IsDofReleased(jrtMz, &st));
      ASSERT_EQ(st, VARIANT_FALSE);
      ASSERT_HR(psj->IsDofReleased(jrtAll, &st));
      ASSERT_EQ(st, VARIANT_FALSE);
      ASSERT_HR(psj->IsDofSupported(jrtNone, &st));
      ASSERT_EQ(st, VARIANT_FALSE);
      ASSERT_HR(psj->IsDofSupported(jrtFx, &st));
      ASSERT_EQ(st, VARIANT_TRUE);
      ASSERT_HR(psj->IsDofSupported(jrtFy, &st));
      ASSERT_EQ(st, VARIANT_TRUE);
      ASSERT_HR(psj->IsDofSupported(jrtMz, &st));
      ASSERT_EQ(st, VARIANT_TRUE);
      ASSERT_HR(psj->IsDofSupported(jrtAll, &st));
      ASSERT_EQ(st, VARIANT_TRUE);

      ASSERT_HR(psj->ReleaseDof(jrtFx));
      ASSERT_HR(psj->IsSupport(&st));
      ASSERT_EQ(st, VARIANT_TRUE);
      ASSERT_HR(psj->IsDofReleased(jrtNone, &st));
      ASSERT_EQ(st, VARIANT_FALSE);
      ASSERT_HR(psj->IsDofReleased(jrtFx, &st));
      ASSERT_EQ(st, VARIANT_TRUE);
      ASSERT_HR(psj->IsDofReleased(jrtFy, &st));
      ASSERT_EQ(st, VARIANT_FALSE);
      ASSERT_HR(psj->IsDofReleased(jrtMz, &st));
      ASSERT_EQ(st, VARIANT_FALSE);
      ASSERT_HR(psj->IsDofReleased(jrtAll, &st));
      ASSERT_EQ(st, VARIANT_FALSE);
      ASSERT_HR(psj->IsDofSupported(jrtNone, &st));
      ASSERT_EQ(st, VARIANT_FALSE);
      ASSERT_HR(psj->IsDofSupported(jrtFx, &st));
      ASSERT_EQ(st, VARIANT_FALSE);
      ASSERT_HR(psj->IsDofSupported(jrtFy, &st));
      ASSERT_EQ(st, VARIANT_TRUE);
      ASSERT_HR(psj->IsDofSupported(jrtMz, &st));
      ASSERT_EQ(st, VARIANT_TRUE);
      ASSERT_HR(psj->IsDofSupported(jrtAll, &st));
      ASSERT_EQ(st, VARIANT_FALSE);

      ASSERT_MC(fixture, psj->ReleaseDof(jrtFy));
      ASSERT_HR(psj->IsSupport(&st));
      ASSERT_EQ(st, VARIANT_TRUE);
      ASSERT_HR(psj->IsDofReleased(jrtNone, &st));
      ASSERT_EQ(st, VARIANT_FALSE);
      ASSERT_HR(psj->IsDofReleased(jrtFx, &st));
      ASSERT_EQ(st, VARIANT_TRUE);
      ASSERT_HR(psj->IsDofReleased(jrtFy, &st));
      ASSERT_EQ(st, VARIANT_TRUE);
      ASSERT_HR(psj->IsDofReleased(jrtMz, &st));
      ASSERT_EQ(st, VARIANT_FALSE);
      ASSERT_HR(psj->IsDofReleased(jrtAll, &st));
      ASSERT_EQ(st, VARIANT_FALSE);
      ASSERT_HR(psj->IsDofSupported(jrtNone, &st));
      ASSERT_EQ(st, VARIANT_FALSE);
      ASSERT_HR(psj->IsDofSupported(jrtFx, &st));
      ASSERT_EQ(st, VARIANT_FALSE);
      ASSERT_HR(psj->IsDofSupported(jrtFy, &st));
      ASSERT_EQ(st, VARIANT_FALSE);
      ASSERT_HR(psj->IsDofSupported(jrtMz, &st));
      ASSERT_EQ(st, VARIANT_TRUE);
      ASSERT_HR(psj->IsDofSupported(jrtAll, &st));
      ASSERT_EQ(st, VARIANT_FALSE);

      ASSERT_MC(fixture, psj->ReleaseDof(jrtMz));
      ASSERT_HR(psj->IsSupport(&st));
      ASSERT_EQ(st, VARIANT_FALSE);
      ASSERT_HR(psj->IsDofReleased(jrtNone, &st));
      ASSERT_EQ(st, VARIANT_FALSE);
      ASSERT_HR(psj->IsDofReleased(jrtFx, &st));
      ASSERT_EQ(st, VARIANT_TRUE);
      ASSERT_HR(psj->IsDofReleased(jrtFy, &st));
      ASSERT_EQ(st, VARIANT_TRUE);
      ASSERT_HR(psj->IsDofReleased(jrtMz, &st));
      ASSERT_EQ(st, VARIANT_TRUE);
      ASSERT_HR(psj->IsDofReleased(jrtAll, &st));
      ASSERT_EQ(st, VARIANT_TRUE);
      ASSERT_HR(psj->IsDofSupported(jrtNone, &st));
      ASSERT_EQ(st, VARIANT_TRUE);
      ASSERT_HR(psj->IsDofSupported(jrtFx, &st));
      ASSERT_EQ(st, VARIANT_FALSE);
      ASSERT_HR(psj->IsDofSupported(jrtFy, &st));
      ASSERT_EQ(st, VARIANT_FALSE);
      ASSERT_HR(psj->IsDofSupported(jrtMz, &st));
      ASSERT_EQ(st, VARIANT_FALSE);
      ASSERT_HR(psj->IsDofSupported(jrtAll, &st));
      ASSERT_EQ(st, VARIANT_FALSE);

      ASSERT_MC(fixture, psj->Support());
      ASSERT_MC(fixture, psj->Free());
      ASSERT_HR(psj->IsSupport(&st));
      ASSERT_EQ(st, VARIANT_FALSE);
      ASSERT_HR(psj->IsDofReleased(jrtNone, &st));
      ASSERT_EQ(st, VARIANT_FALSE);
      ASSERT_HR(psj->IsDofReleased(jrtFx, &st));
      ASSERT_EQ(st, VARIANT_TRUE);
      ASSERT_HR(psj->IsDofReleased(jrtFy, &st));
      ASSERT_EQ(st, VARIANT_TRUE);
      ASSERT_HR(psj->IsDofReleased(jrtMz, &st));
      ASSERT_EQ(st, VARIANT_TRUE);
      ASSERT_HR(psj->IsDofReleased(jrtAll, &st));
      ASSERT_EQ(st, VARIANT_TRUE);
      ASSERT_HR(psj->IsDofSupported(jrtNone, &st));
      ASSERT_EQ(st, VARIANT_TRUE);
      ASSERT_HR(psj->IsDofSupported(jrtFx, &st));
      ASSERT_EQ(st, VARIANT_FALSE);
      ASSERT_HR(psj->IsDofSupported(jrtFy, &st));
      ASSERT_EQ(st, VARIANT_FALSE);
      ASSERT_HR(psj->IsDofSupported(jrtMz, &st));
      ASSERT_EQ(st, VARIANT_FALSE);
      ASSERT_HR(psj->IsDofSupported(jrtAll, &st));
      ASSERT_EQ(st, VARIANT_FALSE);

      // test enum nonsense that can come out of vb: bit-flag combinations formed
      // by addition rather than the named jrtAll/jrtNone constants
      ASSERT_HR(psj->Support());
      ASSERT_HR(psj->ReleaseDof((Fem2dJointReleaseType)(jrtFx + jrtMz)));
      ASSERT_HR(psj->IsSupport(&st));
      ASSERT_EQ(st, VARIANT_TRUE);
      ASSERT_HR(psj->IsDofReleased(jrtNone, &st));
      ASSERT_EQ(st, VARIANT_FALSE);
      ASSERT_HR(psj->IsDofReleased(jrtFx, &st));
      ASSERT_EQ(st, VARIANT_TRUE);
      ASSERT_HR(psj->IsDofReleased(jrtFy, &st));
      ASSERT_EQ(st, VARIANT_FALSE);
      ASSERT_HR(psj->IsDofReleased(jrtMz, &st));
      ASSERT_EQ(st, VARIANT_TRUE);
      ASSERT_HR(psj->IsDofReleased(jrtAll, &st));
      ASSERT_EQ(st, VARIANT_FALSE);
      ASSERT_HR(psj->IsDofSupported(jrtNone, &st));
      ASSERT_EQ(st, VARIANT_FALSE);
      ASSERT_HR(psj->IsDofSupported(jrtFx, &st));
      ASSERT_EQ(st, VARIANT_FALSE);
      ASSERT_HR(psj->IsDofSupported(jrtFy, &st));
      ASSERT_EQ(st, VARIANT_TRUE);
      ASSERT_HR(psj->IsDofSupported(jrtMz, &st));
      ASSERT_EQ(st, VARIANT_FALSE);
      ASSERT_HR(psj->IsDofSupported(jrtAll, &st));
      ASSERT_EQ(st, VARIANT_FALSE);

      ASSERT_HR(psj->Support());
      ASSERT_HR(psj->ReleaseDof((Fem2dJointReleaseType)(jrtFx + jrtFy + jrtMz)));
      ASSERT_HR(psj->IsSupport(&st));
      ASSERT_EQ(st, VARIANT_FALSE);
      ASSERT_HR(psj->IsDofReleased(jrtNone, &st));
      ASSERT_EQ(st, VARIANT_FALSE);
      ASSERT_HR(psj->IsDofReleased(jrtFx, &st));
      ASSERT_EQ(st, VARIANT_TRUE);
      ASSERT_HR(psj->IsDofReleased(jrtFy, &st));
      ASSERT_EQ(st, VARIANT_TRUE);
      ASSERT_HR(psj->IsDofReleased(jrtMz, &st));
      ASSERT_EQ(st, VARIANT_TRUE);
      ASSERT_HR(psj->IsDofReleased(jrtAll, &st));
      ASSERT_EQ(st, VARIANT_TRUE);
      ASSERT_HR(psj->IsDofSupported(jrtNone, &st));
      ASSERT_EQ(st, VARIANT_TRUE);
      ASSERT_HR(psj->IsDofSupported(jrtFx, &st));
      ASSERT_EQ(st, VARIANT_FALSE);
      ASSERT_HR(psj->IsDofSupported(jrtFy, &st));
      ASSERT_EQ(st, VARIANT_FALSE);
      ASSERT_HR(psj->IsDofSupported(jrtMz, &st));
      ASSERT_EQ(st, VARIANT_FALSE);
      ASSERT_HR(psj->IsDofSupported(jrtAll, &st));
      ASSERT_EQ(st, VARIANT_FALSE);
   }
};
} // namespace Fem2dUnitTests
