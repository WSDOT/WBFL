///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
///////////////////////////////////////////////////////////////////////
// TestModelEvents.cpp
//
// New coverage: dedicated tests for IFem2dModelEvents connection-point
// firing semantics. The legacy Fem2d\Test suite only exercised this
// implicitly (every mutating call was wrapped in TRY_TEST_MC/TRY_TEST_LC,
// which is what Fem2dModelFixture's ASSERT_MC/ASSERT_LC continue to do for
// every other test file in this suite); this file instead tests the
// Advise/Unadvise mechanics directly - multiple simultaneous sinks,
// Unadvise actually stopping notifications, and read-only calls NOT firing
// events - since this is the mechanism VBA/Excel automation clients would
// use to react to model changes.
#include "pch.h"

namespace Fem2dUnitTests
{

TEST_CLASS(TestModelEvents)
{
public:
   TEST_METHOD(MultipleSinks_AllReceiveNotifications)
   {
      Fem2dModelFixture fixture;
      CComPtr<IFem2dModel>& pmodel = fixture.Model;

      // advise a second, independent sink
      CComObject<CFem2dTestEventSink>* pSink2 = nullptr;
      ASSERT_HR(CComObject<CFem2dTestEventSink>::CreateInstance(&pSink2));
      pSink2->AddRef();
      DWORD dwCookie2 = 0;
      ASSERT_HR(AtlAdvise(pmodel, pSink2, IID_IFem2dModelEvents, &dwCookie2));

      CComPtr<IFem2dJointCollection> pJoints;
      ASSERT_HR(pmodel->get_Joints(&pJoints));
      CComPtr<IFem2dJoint> pJoint1;
      ASSERT_MC(fixture, pJoints->Create(1, 0.0, 0.0, &pJoint1));
      Assert::IsTrue(pSink2->PassedModelChangedTest(), L"second sink did not receive OnModelChanged");

      ASSERT_HR(AtlUnadvise(pmodel, IID_IFem2dModelEvents, dwCookie2));
      pSink2->Release();
   }

   TEST_METHOD(Unadvise_StopsNotifications)
   {
      Fem2dModelFixture fixture;
      CComPtr<IFem2dModel>& pmodel = fixture.Model;

      CComObject<CFem2dTestEventSink>* pSink2 = nullptr;
      ASSERT_HR(CComObject<CFem2dTestEventSink>::CreateInstance(&pSink2));
      pSink2->AddRef();
      DWORD dwCookie2 = 0;
      ASSERT_HR(AtlAdvise(pmodel, pSink2, IID_IFem2dModelEvents, &dwCookie2));
      ASSERT_HR(AtlUnadvise(pmodel, IID_IFem2dModelEvents, dwCookie2));

      CComPtr<IFem2dJointCollection> pJoints;
      ASSERT_HR(pmodel->get_Joints(&pJoints));
      CComPtr<IFem2dJoint> pJoint1;
      // fixture's own sink still receives the event...
      ASSERT_MC(fixture, pJoints->Create(1, 0.0, 0.0, &pJoint1));
      // ...but the unadvised sink must not
      Assert::IsFalse(pSink2->PassedModelChangedTest(), L"unadvised sink still received OnModelChanged");

      pSink2->Release();
   }

   TEST_METHOD(ReadOnlyQueries_DoNotFireEvents)
   {
      Fem2dModelFixture fixture;
      CComPtr<IFem2dModel>& pmodel = fixture.Model;

      CComPtr<IFem2dJointCollection> pJoints;
      ASSERT_HR(pmodel->get_Joints(&pJoints));
      CComPtr<IFem2dJoint> pJoint1, pJoint2;
      ASSERT_MC(fixture, pJoints->Create(1, 0.0, 0.0, &pJoint1));
      ASSERT_MC(fixture, pJoints->Create(2, 10.0, 0.0, &pJoint2));
      ASSERT_MC(fixture, pJoint1->Support());

      CComPtr<IFem2dMemberCollection> pMembers;
      ASSERT_HR(pmodel->get_Members(&pMembers));
      CComPtr<IFem2dMember> pMember1;
      ASSERT_MC(fixture, pMembers->Create(1, 1, 2, 100.0, 100.0, &pMember1));

      CComPtr<IFem2dLoadingCollection> pLoadings;
      ASSERT_HR(pmodel->get_Loadings(&pLoadings));
      CComPtr<IFem2dLoading> pLoading;
      ASSERT_LC(fixture, pLoadings->Create(0, &pLoading));

      // drain any pending change flags from setup above, then perform a
      // batch of pure read-only calls and confirm neither event fires
      fixture.PassedModelChangedTest();
      fixture.PassedLoadingChangedTest();

      Float64 x, y;
      ASSERT_HR(pJoint1->get_X(&x));
      ASSERT_HR(pJoint1->get_Y(&y));
      VARIANT_BOOL isSupport;
      ASSERT_HR(pJoint1->IsSupport(&isSupport));
      IndexType count;
      ASSERT_HR(pJoints->get_Count(&count));
      Float64 len;
      ASSERT_HR(pMember1->get_Length(&len));

      CComQIPtr<IFem2dModelResults> presults(pmodel);
      Float64 dx, dy, rz;
      ASSERT_HR(presults->ComputeJointDeflections(0, 1, &dx, &dy, &rz));

      Assert::IsFalse(fixture.PassedModelChangedTest(), L"read-only calls must not fire OnModelChanged");
      Assert::IsFalse(fixture.PassedLoadingChangedTest(), L"read-only calls must not fire OnLoadingChanged");
   }

   TEST_METHOD(LoadingChanged_FiresOnlyForLoadMutations)
   {
      Fem2dModelFixture fixture;
      CComPtr<IFem2dModel>& pmodel = fixture.Model;

      CComPtr<IFem2dJointCollection> pJoints;
      ASSERT_HR(pmodel->get_Joints(&pJoints));
      CComPtr<IFem2dJoint> pJoint1;
      ASSERT_MC(fixture, pJoints->Create(1, 0.0, 0.0, &pJoint1));

      CComPtr<IFem2dLoadingCollection> pLoadings;
      ASSERT_HR(pmodel->get_Loadings(&pLoadings));
      CComPtr<IFem2dLoading> pLoading;
      // creating a loading fires OnLoadingChanged, not OnModelChanged
      ASSERT_LC(fixture, pLoadings->Create(0, &pLoading));
      Assert::IsFalse(fixture.PassedModelChangedTest(), L"creating a loading must not fire OnModelChanged");

      // creating a joint fires OnModelChanged, not OnLoadingChanged
      CComPtr<IFem2dJoint> pJoint2;
      ASSERT_MC(fixture, pJoints->Create(2, 10.0, 0.0, &pJoint2));
      Assert::IsFalse(fixture.PassedLoadingChangedTest(), L"creating a joint must not fire OnLoadingChanged");
   }
};
} // namespace Fem2dUnitTests
