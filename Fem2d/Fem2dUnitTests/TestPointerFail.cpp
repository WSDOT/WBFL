///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
///////////////////////////////////////////////////////////////////////
// TestPointerFail.cpp
//
// Ported from F:\ARP\WBFL\Fem2d\Test\TestPointerFail.cpp - verifies that every
// out-param on the COM surface returns E_POINTER when passed nullptr.
#include "pch.h"

namespace Fem2dUnitTests
{

TEST_CLASS(TestPointerFail)
{
public:
   TEST_METHOD(NullOutParamsReturnEPointer)
   {
      Fem2dModelFixture fixture;
      CComPtr<IFem2dModel>& pmodel = fixture.Model;

      /////////////////////////////////////////////
      // Joints
      ASSERT_EQ(pmodel->get_Joints(nullptr), E_POINTER);

      CComPtr<IFem2dJointCollection> pJoints;
      ASSERT_HR(pmodel->get_Joints(&pJoints));

      CComPtr<IFem2dJoint> pJoint;
      ASSERT_MC(fixture, pJoints->Create(1, 0.0, 0.0, &pJoint));

      ASSERT_EQ(pJoints->Create(1, 0.0, 0.0, nullptr), E_POINTER);
      ASSERT_EQ(pJoints->get_Item(0, nullptr), E_POINTER);
      ASSERT_EQ(pJoints->Find(0, nullptr), E_POINTER);
      ASSERT_EQ(pJoints->get__EnumElements(nullptr), E_POINTER);

      ASSERT_EQ(pJoint->get_ID(nullptr), E_POINTER);
      ASSERT_EQ(pJoint->get_X(nullptr), E_POINTER);
      ASSERT_EQ(pJoint->get_Y(nullptr), E_POINTER);

      ASSERT_EQ(pJoint->IsDofReleased(jrtNone, nullptr), E_POINTER);
      ASSERT_EQ(pJoint->IsSupport(nullptr), E_POINTER);

      /////////////////////////////////////////////
      // Members
      ASSERT_EQ(pmodel->get_Members(nullptr), E_POINTER);

      CComPtr<IFem2dMemberCollection> pMembers;
      ASSERT_HR(pmodel->get_Members(&pMembers));

      CComPtr<IFem2dMember> pMember;
      ASSERT_MC(fixture, pMembers->Create(1, 1, 2, 0.0, 0.0, &pMember));

      ASSERT_EQ(pMembers->Create(1, 1, 2, 0.0, 0.0, nullptr), E_POINTER);
      ASSERT_EQ(pMembers->get_Item(0, nullptr), E_POINTER);
      ASSERT_EQ(pMembers->Find(0, nullptr), E_POINTER);
      ASSERT_EQ(pMembers->get__EnumElements(nullptr), E_POINTER);

      ASSERT_EQ(pMember->get_ID(nullptr), E_POINTER);
      ASSERT_EQ(pMember->get_StartJoint(nullptr), E_POINTER);
      ASSERT_EQ(pMember->get_EndJoint(nullptr), E_POINTER);
      ASSERT_EQ(pMember->get_EA(nullptr), E_POINTER);
      ASSERT_EQ(pMember->get_EI(nullptr), E_POINTER);
      ASSERT_EQ(pMember->get_Length(nullptr), E_POINTER);
      ASSERT_EQ(pMember->IsReleased(metStart, mbrReleaseMz, nullptr), E_POINTER);

      /////////////////////////////////////////////
      // POIs
      ASSERT_EQ(pmodel->get_POIs(nullptr), E_POINTER);

      CComPtr<IFem2dPOICollection> pPOIs;
      ASSERT_HR(pmodel->get_POIs(&pPOIs));

      CComPtr<IFem2dPOI> pPOI;
      ASSERT_HR(pPOIs->Create(1, 2, 0.0, &pPOI));

      ASSERT_EQ(pPOIs->Create(1, 1, 0.0, nullptr), E_POINTER);
      ASSERT_EQ(pPOIs->get_Item(0, nullptr), E_POINTER);
      ASSERT_EQ(pPOIs->Find(0, nullptr), E_POINTER);
      ASSERT_EQ(pPOIs->get__EnumElements(nullptr), E_POINTER);

      ASSERT_EQ(pPOI->get_ID(nullptr), E_POINTER);
      ASSERT_EQ(pPOI->get_MemberID(nullptr), E_POINTER);
      ASSERT_EQ(pPOI->get_Location(nullptr), E_POINTER);

      /////////////////////////////////////////////
      // Loadings
      IFem2dLoadingCollection** ppNullLoadingColl = 0;
      IFem2dEnumLoading** ppNullLoadingEnum = 0;
      IFem2dLoading** ppNullLoading = 0;

      ASSERT_EQ(pmodel->get_Loadings(ppNullLoadingColl), E_POINTER);

      CComPtr<IFem2dLoadingCollection> pLoadings;
      ASSERT_HR(pmodel->get_Loadings(&pLoadings));

      CComPtr<IFem2dLoading> pLoading;
      ASSERT_LC(fixture, pLoadings->Create(1, &pLoading));

      ASSERT_EQ(pLoadings->Create(1, ppNullLoading), E_POINTER);
      ASSERT_EQ(pLoadings->get_Item(0, ppNullLoading), E_POINTER);
      ASSERT_EQ(pLoadings->Find(0, ppNullLoading), E_POINTER);
      ASSERT_EQ(pLoadings->get__EnumElements(ppNullLoadingEnum), E_POINTER);

      ASSERT_EQ(pLoading->get_ID(nullptr), E_POINTER);
      ASSERT_EQ(pLoading->get_JointLoads(nullptr), E_POINTER);
      ASSERT_EQ(pLoading->get_DistributedLoads(nullptr), E_POINTER);
      ASSERT_EQ(pLoading->get_JointDeflections(nullptr), E_POINTER);
      ASSERT_EQ(pLoading->get_PointLoads(nullptr), E_POINTER);
      ASSERT_EQ(pLoading->get_MemberStrains(nullptr), E_POINTER);

      /////////////////////////////////////////////
      // JointLoads
      CComPtr<IFem2dJointLoadCollection> pJointLoads;
      ASSERT_HR(pLoading->get_JointLoads(&pJointLoads));

      CComPtr<IFem2dJointLoad> pJointLoad;
      ASSERT_LC(fixture, pJointLoads->Create(1, 1, 0.0, 0.0, 0.0, &pJointLoad));

      ASSERT_EQ(pJointLoads->Create(1, 1, 0.0, 0.0, 0.0, nullptr), E_POINTER);
      ASSERT_EQ(pJointLoads->get_Item(0, nullptr), E_POINTER);
      ASSERT_EQ(pJointLoads->Find(0, nullptr), E_POINTER);
      ASSERT_EQ(pJointLoads->get__EnumElements(nullptr), E_POINTER);

      ASSERT_EQ(pJointLoad->get_ID(nullptr), E_POINTER);
      ASSERT_EQ(pJointLoad->get_JointID(nullptr), E_POINTER);
      ASSERT_EQ(pJointLoad->get_Fx(nullptr), E_POINTER);
      ASSERT_EQ(pJointLoad->get_Fy(nullptr), E_POINTER);
      ASSERT_EQ(pJointLoad->get_Mz(nullptr), E_POINTER);
      ASSERT_EQ(pJointLoad->GetForce(nullptr, nullptr, nullptr), E_POINTER);
      ASSERT_EQ(pJointLoad->get_Loading(nullptr), E_POINTER);

      /////////////////////////////////////////////
      // JointDeflections
      IFem2dEnumJointDeflection** ppNullJointDeflectionEnum = 0;
      IFem2dJointDeflection** ppNullJointDeflection = 0;

      CComPtr<IFem2dJointDeflectionCollection> pJointDeflections;
      ASSERT_HR(pLoading->get_JointDeflections(&pJointDeflections));

      CComPtr<IFem2dJointDeflection> pJointDeflection;
      ASSERT_LC(fixture, pJointDeflections->Create(1, 1, 0.0, 0.0, 0.0, &pJointDeflection));

      ASSERT_EQ(pJointDeflections->Create(1, 1, 0.0, 0.0, 0.0, nullptr), E_POINTER);
      ASSERT_EQ(pJointDeflections->get_Item(0, nullptr), E_POINTER);
      ASSERT_EQ(pJointDeflections->Find(0, nullptr), E_POINTER);
      ASSERT_EQ(pJointDeflections->get__EnumElements(nullptr), E_POINTER);

      ASSERT_EQ(pJointDeflection->get_ID(nullptr), E_POINTER);
      ASSERT_EQ(pJointDeflection->get_JointID(nullptr), E_POINTER);
      ASSERT_EQ(pJointDeflection->get_Dx(nullptr), E_POINTER);
      ASSERT_EQ(pJointDeflection->get_Dy(nullptr), E_POINTER);
      ASSERT_EQ(pJointDeflection->get_Rz(nullptr), E_POINTER);
      ASSERT_EQ(pJointDeflection->GetDeflection(nullptr, nullptr, nullptr), E_POINTER);
      ASSERT_EQ(pJointDeflection->get_Loading(nullptr), E_POINTER);

      /////////////////////////////////////////////
      // PointLoads
      CComPtr<IFem2dPointLoadCollection> pPointLoads;
      ASSERT_HR(pLoading->get_PointLoads(&pPointLoads));

      CComPtr<IFem2dPointLoad> pPointLoad;
      ASSERT_LC(fixture, pPointLoads->Create(1, 1, 0.0, 0.0, 0.0, 0.0, lotMember, &pPointLoad));

      ASSERT_EQ(pPointLoads->Create(1, 1, 0.0, 0.0, 0.0, 0.0, lotMember, nullptr), E_POINTER);
      ASSERT_EQ(pPointLoads->get_Item(0, nullptr), E_POINTER);
      ASSERT_EQ(pPointLoads->Find(0, nullptr), E_POINTER);
      ASSERT_EQ(pPointLoads->get__EnumElements(nullptr), E_POINTER);

      ASSERT_EQ(pPointLoad->get_ID(nullptr), E_POINTER);
      ASSERT_EQ(pPointLoad->get_MemberID(nullptr), E_POINTER);
      ASSERT_EQ(pPointLoad->get_Fx(nullptr), E_POINTER);
      ASSERT_EQ(pPointLoad->get_Fy(nullptr), E_POINTER);
      ASSERT_EQ(pPointLoad->get_Mz(nullptr), E_POINTER);
      ASSERT_EQ(pPointLoad->get_Location(nullptr), E_POINTER);
      ASSERT_EQ(pPointLoad->get_Orientation(nullptr), E_POINTER);
      ASSERT_EQ(pPointLoad->GetForce(nullptr, nullptr, nullptr), E_POINTER);
      ASSERT_EQ(pPointLoad->get_Loading(nullptr), E_POINTER);

      /////////////////////////////////////////////
      // DistributedLoads
      CComPtr<IFem2dDistributedLoadCollection> pDistributedLoads;
      ASSERT_HR(pLoading->get_DistributedLoads(&pDistributedLoads));

      CComPtr<IFem2dDistributedLoad> pDistributedLoad;
      ASSERT_LC(fixture, pDistributedLoads->Create(1, 1, loadDirFy, 0.0, 0.0, 0.0, 0.0, lotMember, &pDistributedLoad));

      ASSERT_EQ(pDistributedLoads->Create(1, 1, loadDirFy, 0.0, 0.0, 0.0, 0.0, lotMember, nullptr), E_POINTER);
      ASSERT_EQ(pDistributedLoads->get_Item(0, nullptr), E_POINTER);
      ASSERT_EQ(pDistributedLoads->Find(0, nullptr), E_POINTER);
      ASSERT_EQ(pDistributedLoads->get__EnumElements(nullptr), E_POINTER);

      ASSERT_EQ(pDistributedLoad->get_ID(nullptr), E_POINTER);
      ASSERT_EQ(pDistributedLoad->get_MemberID(nullptr), E_POINTER);
      ASSERT_EQ(pDistributedLoad->get_Orientation(nullptr), E_POINTER);
      ASSERT_EQ(pDistributedLoad->get_Direction(nullptr), E_POINTER);
      ASSERT_EQ(pDistributedLoad->get_WStart(nullptr), E_POINTER);
      ASSERT_EQ(pDistributedLoad->get_WEnd(nullptr), E_POINTER);
      ASSERT_EQ(pDistributedLoad->get_StartLocation(nullptr), E_POINTER);
      ASSERT_EQ(pDistributedLoad->get_EndLocation(nullptr), E_POINTER);
      ASSERT_EQ(pDistributedLoad->get_Loading(nullptr), E_POINTER);

      /////////////////////////////////////////////
      // MemberStrains
      CComPtr<IFem2dMemberStrainCollection> pMemberStrains;
      ASSERT_HR(pLoading->get_MemberStrains(&pMemberStrains));

      CComPtr<IFem2dMemberStrain> pMemberStrain;
      ASSERT_HR(pMemberStrains->Create(1, 1, 0.0, -1.0, 0.0, 0.0, &pMemberStrain));

      ASSERT_EQ(pMemberStrains->Create(1, 1, 0.0, -1.0, 0.0, 0.0, nullptr), E_POINTER);
      ASSERT_EQ(pMemberStrains->get_Item(0, nullptr), E_POINTER);
      ASSERT_EQ(pMemberStrains->Find(0, nullptr), E_POINTER);
      ASSERT_EQ(pMemberStrains->get__EnumElements(nullptr), E_POINTER);

      ASSERT_EQ(pMemberStrain->get_ID(nullptr), E_POINTER);
      ASSERT_EQ(pMemberStrain->get_MemberID(nullptr), E_POINTER);
      ASSERT_EQ(pMemberStrain->get_AxialStrain(nullptr), E_POINTER);
      ASSERT_EQ(pMemberStrain->get_CurvatureStrain(nullptr), E_POINTER);
      ASSERT_EQ(pMemberStrain->get_StartLocation(nullptr), E_POINTER);
      ASSERT_EQ(pMemberStrain->get_EndLocation(nullptr), E_POINTER);
      ASSERT_EQ(pMemberStrain->get_Loading(nullptr), E_POINTER);

      // get results interface
      CComQIPtr<IFem2dModelResults> presults(pmodel);

      ASSERT_EQ(presults->ComputeJointDeflections(0, 4, nullptr, nullptr, nullptr), E_POINTER);
      ASSERT_EQ(presults->ComputeMemberDeflections(0, 1, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr), E_POINTER);
      ASSERT_EQ(presults->ComputePOIDeflections(2, 10, lotGlobal, nullptr, nullptr, nullptr), E_POINTER);
      ASSERT_EQ(presults->ComputeReactions(0, 3, nullptr, nullptr, nullptr), E_POINTER);
      ASSERT_EQ(presults->ComputeMemberForces(0, 6, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr), E_POINTER);
      ASSERT_EQ(presults->ComputePOIForces(0, 14, mftRight, lotGlobal, nullptr, nullptr, nullptr), E_POINTER);
   }
};
} // namespace Fem2dUnitTests
