///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
///////////////////////////////////////////////////////////////////////
// TestISupportErrorInfo.cpp
//
// Ported from F:\ARP\WBFL\Fem2d\Test\TestISupportErrorInfo.cpp
#include "pch.h"

namespace Fem2dUnitTests
{

namespace
{
   void CheckSupportErrorInfo(IUnknown* pThing, REFIID myiid)
   {
      CComQIPtr<ISupportErrorInfo> ptrnam(pThing);
      Assert::IsTrue(ptrnam != nullptr, L"QueryInterface(ISupportErrorInfo) failed");
      ASSERT_EQ(ptrnam->InterfaceSupportsErrorInfo(myiid), S_OK);
      ASSERT_EQ(ptrnam->InterfaceSupportsErrorInfo(IID_ISupportErrorInfo), S_FALSE);
   }
}

TEST_CLASS(TestISupportErrorInfo)
{
public:
   TEST_METHOD(EveryInterfaceSupportsErrorInfo)
   {
      Fem2dModelFixture fixture;
      CComPtr<IFem2dModel>& pmodel = fixture.Model;

      // the model
      CheckSupportErrorInfo(pmodel, IID_IFem2dModel);

      // joints
      CComPtr<IFem2dJointCollection> pJoints;
      ASSERT_HR(pmodel->get_Joints(&pJoints));
      CComPtr<IFem2dJoint> pJoint1, pJoint2;
      ASSERT_MC(fixture, pJoints->Create(1, 0.0, 0.0, &pJoint1));
      ASSERT_MC(fixture, pJoints->Create(2, 0.0, 24.0, &pJoint2));

      CheckSupportErrorInfo(pJoint1, IID_IFem2dJoint);
      CheckSupportErrorInfo(pJoints, IID_IFem2dJointCollection);

      // members
      CComPtr<IFem2dMemberCollection> pMembers;
      ASSERT_HR(pmodel->get_Members(&pMembers));

      Float64 E = 3.0;
      Float64 A = 5.0;
      Float64 I = 7.0;
      CComPtr<IFem2dMember> pMember1;
      ASSERT_MC(fixture, pMembers->Create(1, 1, 2, E * A, E * I, &pMember1));

      CheckSupportErrorInfo(pMember1, IID_IFem2dMember);
      CheckSupportErrorInfo(pMembers, IID_IFem2dMemberCollection);

      // loadings
      CComPtr<IFem2dLoadingCollection> pLoadings;
      ASSERT_HR(pmodel->get_Loadings(&pLoadings));
      CComPtr<IFem2dLoading> pLoading1;
      ASSERT_LC(fixture, pLoadings->Create(1, &pLoading1));

      CheckSupportErrorInfo(pLoading1, IID_IFem2dLoading);
      CheckSupportErrorInfo(pLoadings, IID_IFem2dLoadingCollection);

      // distributed loads
      CComPtr<IFem2dDistributedLoadCollection> pDistributedLoads;
      ASSERT_HR(pLoading1->get_DistributedLoads(&pDistributedLoads));
      CComPtr<IFem2dDistributedLoad> pDistributedLoad1;
      ASSERT_LC(fixture, pDistributedLoads->Create(1, 3, loadDirFy, -0.1, -0.7, -2.0, 0.0, lotMember, &pDistributedLoad1));

      CheckSupportErrorInfo(pDistributedLoad1, IID_IFem2dDistributedLoad);
      CheckSupportErrorInfo(pDistributedLoads, IID_IFem2dDistributedLoadCollection);

      // joint loads
      CComPtr<IFem2dJointLoadCollection> pJointLoads;
      ASSERT_HR(pLoading1->get_JointLoads(&pJointLoads));
      CComPtr<IFem2dJointLoad> pJointLoad;
      ASSERT_LC(fixture, pJointLoads->Create(1, 3, 12.0, 0.0, 0.0, &pJointLoad));

      CheckSupportErrorInfo(pJointLoad, IID_IFem2dJointLoad);
      CheckSupportErrorInfo(pJointLoads, IID_IFem2dJointLoadCollection);

      // point loads
      CComPtr<IFem2dPointLoadCollection> pPointLoads;
      ASSERT_HR(pLoading1->get_PointLoads(&pPointLoads));
      CComPtr<IFem2dPointLoad> pPointLoad;
      ASSERT_LC(fixture, pPointLoads->Create(1, 1, -0.6, 4.0, -3.0, 0.0, lotMember, &pPointLoad));

      CheckSupportErrorInfo(pPointLoad, IID_IFem2dPointLoad);
      CheckSupportErrorInfo(pPointLoads, IID_IFem2dPointLoadCollection);

      // member strain
      CComPtr<IFem2dMemberStrainCollection> pMemberStrains;
      ASSERT_HR(pLoading1->get_MemberStrains(&pMemberStrains));
      CComPtr<IFem2dMemberStrain> pMemberStrain;
      ASSERT_LC(fixture, pMemberStrains->Create(1, 7, 0.0, -1.0, 0.05, 0.0, &pMemberStrain));

      CheckSupportErrorInfo(pMemberStrain, IID_IFem2dMemberStrain);
      CheckSupportErrorInfo(pMemberStrains, IID_IFem2dMemberStrainCollection);

      // support deflection
      CComPtr<IFem2dJointDeflectionCollection> pJointDeflections;
      ASSERT_HR(pLoading1->get_JointDeflections(&pJointDeflections));
      CComPtr<IFem2dJointDeflection> pJointDeflection;
      ASSERT_LC(fixture, pJointDeflections->Create(1, 4, 0.4, -0.6, 0.0, &pJointDeflection));

      CheckSupportErrorInfo(pJointDeflection, IID_IFem2dJointDeflection);
      CheckSupportErrorInfo(pJointDeflections, IID_IFem2dJointDeflectionCollection);

      // POI's
      CComPtr<IFem2dPOICollection> pPOIs;
      ASSERT_HR(pmodel->get_POIs(&pPOIs));
      CComPtr<IFem2dPOI> pPOI;
      ASSERT_HR(pPOIs->Create(35, 3, -0.5, &pPOI));

      CheckSupportErrorInfo(pPOI, IID_IFem2dPOI);
      CheckSupportErrorInfo(pPOIs, IID_IFem2dPOICollection);
   }
};
} // namespace Fem2dUnitTests
