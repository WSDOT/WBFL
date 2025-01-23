///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2025  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Library Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////
// TestPointerFail.cpp: implementation of the CTestPointerFail class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestPointerFail.h"
#include <MathEx.h>
#include <iostream> 
#include <WBFLCore.h>
#include <COMDEF.H>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CTestPointerFail::CTestPointerFail()
{

}

CTestPointerFail::~CTestPointerFail()
{

}


void CTestPointerFail::Test() 
{

/*////////////////////////////////////////////////////

  test for null pointers

*/////////////////////////////////////////////////

   CComPtr<IFem2dModel> pmodel;
   pmodel = CreateModel();
   ATLASSERT(pmodel);

   /////////////////////////////////////////////
   // Joints
   // null test pointers
   TRY_TEST(pmodel->get_Joints(nullptr),E_POINTER);

   // joints
   CComPtr<IFem2dJointCollection> pJoints;
   TRY_TEST_HR(pmodel->get_Joints(&pJoints));

   CComPtr<IFem2dJoint> pJoint;
   TRY_TEST_MC(pJoints->Create(1,  0.0,   0.0, &pJoint));

   TRY_TEST(pJoints->Create(1,  0.0,   0.0, nullptr),E_POINTER);
   TRY_TEST(pJoints->get_Item(0, nullptr),E_POINTER);
   TRY_TEST(pJoints->Find(0, nullptr),E_POINTER);
   TRY_TEST(pJoints->get__EnumElements(nullptr),E_POINTER);

   // joint
   TRY_TEST(pJoint->get_ID(nullptr),E_POINTER);
   TRY_TEST(pJoint->get_X(nullptr),E_POINTER);
   TRY_TEST(pJoint->get_Y(nullptr),E_POINTER);

   TRY_TEST(pJoint->IsDofReleased(jrtNone, nullptr),E_POINTER);
   TRY_TEST(pJoint->IsSupport(nullptr),E_POINTER);

   /////////////////////////////////////////////
   // Members
   // null test pointers

   TRY_TEST(pmodel->get_Members(nullptr),E_POINTER);

   // Members
   CComPtr<IFem2dMemberCollection> pMembers;
   TRY_TEST_HR(pmodel->get_Members(&pMembers));

   CComPtr<IFem2dMember> pMember;
   TRY_TEST_MC(pMembers->Create(1, 1, 2, 0.0, 0.0, &pMember));

   TRY_TEST(pMembers->Create(1, 1, 2, 0.0, 0.0, nullptr),E_POINTER);
   TRY_TEST(pMembers->get_Item(0, nullptr),E_POINTER);
   TRY_TEST(pMembers->Find(0, nullptr),E_POINTER);
   TRY_TEST(pMembers->get__EnumElements(nullptr),E_POINTER);

   // Member
   TRY_TEST(pMember->get_ID(nullptr),E_POINTER);
   TRY_TEST(pMember->get_StartJoint(nullptr),E_POINTER);
   TRY_TEST(pMember->get_EndJoint(nullptr),E_POINTER);
   TRY_TEST(pMember->get_EA(nullptr),E_POINTER);
   TRY_TEST(pMember->get_EI(nullptr),E_POINTER);
   TRY_TEST(pMember->get_Length(nullptr),E_POINTER);
   TRY_TEST(pMember->IsReleased(metStart, mbrReleaseMz, nullptr),E_POINTER);

   /////////////////////////////////////////////
   // POIs
   // null test pointers
   TRY_TEST(pmodel->get_POIs(nullptr),E_POINTER);

   // POIs
   CComPtr<IFem2dPOICollection> pPOIs;
   TRY_TEST_HR(pmodel->get_POIs(&pPOIs));

   CComPtr<IFem2dPOI> pPOI;
   TRY_TEST_HR(pPOIs->Create(1, 2, 0.0, &pPOI));

   TRY_TEST(pPOIs->Create(1, 1, 0.0, nullptr),E_POINTER);
   TRY_TEST(pPOIs->get_Item(0, nullptr),E_POINTER);
   TRY_TEST(pPOIs->Find(0, nullptr),E_POINTER);
   TRY_TEST(pPOIs->get__EnumElements(nullptr),E_POINTER);

   // POI
   TRY_TEST(pPOI->get_ID(nullptr),E_POINTER);
   TRY_TEST(pPOI->get_MemberID(nullptr),E_POINTER);
   TRY_TEST(pPOI->get_Location(nullptr),E_POINTER);

   /////////////////////////////////////////////
   // Loadings
   // null test Loadingnters
   IFem2dLoadingCollection** ppNullLoadingColl = 0;
   IFem2dEnumLoading** ppNullLoadingEnum = 0;
   IFem2dLoading* pNullLoading = 0;
   IFem2dLoading** ppNullLoading = 0;

   TRY_TEST(pmodel->get_Loadings(ppNullLoadingColl),E_POINTER);

   // Loadings
   CComPtr<IFem2dLoadingCollection> pLoadings;
   TRY_TEST_HR(pmodel->get_Loadings(&pLoadings));

   CComPtr<IFem2dLoading> pLoading;
   TRY_TEST_LC(pLoadings->Create(1, &pLoading));

   TRY_TEST(pLoadings->Create(1, ppNullLoading),E_POINTER);
   TRY_TEST(pLoadings->get_Item(0, ppNullLoading),E_POINTER);
   TRY_TEST(pLoadings->Find(0, ppNullLoading),E_POINTER);
   TRY_TEST(pLoadings->get__EnumElements(ppNullLoadingEnum),E_POINTER);

   // Loading
   TRY_TEST(pLoading->get_ID(nullptr),E_POINTER);
   TRY_TEST(pLoading->get_JointLoads(nullptr),E_POINTER);
   TRY_TEST(pLoading->get_DistributedLoads(nullptr),E_POINTER);
   TRY_TEST(pLoading->get_JointDeflections(nullptr),E_POINTER);
   TRY_TEST(pLoading->get_PointLoads(nullptr),E_POINTER);
   TRY_TEST(pLoading->get_MemberStrains(nullptr),E_POINTER);

   /////////////////////////////////////////////
   // JointLoads
   // null test pointers
   // JointLoads
   CComPtr<IFem2dJointLoadCollection> pJointLoads;
   TRY_TEST_HR(pLoading->get_JointLoads(&pJointLoads));

   CComPtr<IFem2dJointLoad> pJointLoad;
   TRY_TEST_LC(pJointLoads->Create(1, 1, 0.0, 0.0, 0.0, &pJointLoad));

   TRY_TEST(pJointLoads->Create(1, 1, 0.0, 0.0, 0.0, nullptr),E_POINTER);
   TRY_TEST(pJointLoads->get_Item(0, nullptr),E_POINTER);
   TRY_TEST(pJointLoads->Find(0, nullptr),E_POINTER);
   TRY_TEST(pJointLoads->get__EnumElements(nullptr),E_POINTER);

   // JointLoad
   TRY_TEST(pJointLoad->get_ID(nullptr),E_POINTER);
   TRY_TEST(pJointLoad->get_JointID(nullptr),E_POINTER);
   TRY_TEST(pJointLoad->get_Fx(nullptr),E_POINTER);
   TRY_TEST(pJointLoad->get_Fy(nullptr),E_POINTER);
   TRY_TEST(pJointLoad->get_Mz(nullptr),E_POINTER);
   TRY_TEST(pJointLoad->GetForce(nullptr,nullptr,nullptr),E_POINTER);
   TRY_TEST(pJointLoad->get_Loading(nullptr),E_POINTER);

   /////////////////////////////////////////////
   // JointDeflections
   // null test pointers
   IFem2dEnumJointDeflection** ppNullJointDeflectionEnum = 0;
   IFem2dJointDeflection* pNullJointDeflection = 0;
   IFem2dJointDeflection** ppNullJointDeflection = 0;

   // JointDeflections
   CComPtr<IFem2dJointDeflectionCollection> pJointDeflections;
   TRY_TEST_HR(pLoading->get_JointDeflections(&pJointDeflections));

   CComPtr<IFem2dJointDeflection> pJointDeflection;
   TRY_TEST_LC(pJointDeflections->Create(1, 1, 0.0, 0.0, 0.0, &pJointDeflection));

   TRY_TEST(pJointDeflections->Create(1, 1, 0.0, 0.0, 0.0, nullptr),E_POINTER);
   TRY_TEST(pJointDeflections->get_Item(0, nullptr),E_POINTER);
   TRY_TEST(pJointDeflections->Find(0, nullptr),E_POINTER);
   TRY_TEST(pJointDeflections->get__EnumElements(nullptr),E_POINTER);

   // JointDeflection
   TRY_TEST(pJointDeflection->get_ID(nullptr),E_POINTER);
   TRY_TEST(pJointDeflection->get_JointID(nullptr),E_POINTER);
   TRY_TEST(pJointDeflection->get_Dx(nullptr),E_POINTER);
   TRY_TEST(pJointDeflection->get_Dy(nullptr),E_POINTER);
   TRY_TEST(pJointDeflection->get_Rz(nullptr),E_POINTER);
   TRY_TEST(pJointDeflection->GetDeflection(nullptr,nullptr,nullptr),E_POINTER);
   TRY_TEST(pJointDeflection->get_Loading(nullptr),E_POINTER);

   /////////////////////////////////////////////
   // PointLoads
   // null test pointers
   // PointLoads
   CComPtr<IFem2dPointLoadCollection> pPointLoads;
   TRY_TEST_HR(pLoading->get_PointLoads(&pPointLoads));

   CComPtr<IFem2dPointLoad> pPointLoad;
   TRY_TEST_LC(pPointLoads->Create(1, 1, 0.0, 0.0, 0.0, 0.0, lotMember, &pPointLoad));

   TRY_TEST(pPointLoads->Create(1, 1, 0.0, 0.0, 0.0, 0.0, lotMember, nullptr),E_POINTER);
   TRY_TEST(pPointLoads->get_Item(0, nullptr),E_POINTER);
   TRY_TEST(pPointLoads->Find(0, nullptr),E_POINTER);
   TRY_TEST(pPointLoads->get__EnumElements(nullptr),E_POINTER);

   // PointLoad
   TRY_TEST(pPointLoad->get_ID(nullptr),E_POINTER);
   TRY_TEST(pPointLoad->get_MemberID(nullptr),E_POINTER);
   TRY_TEST(pPointLoad->get_Fx(nullptr),E_POINTER);
   TRY_TEST(pPointLoad->get_Fy(nullptr),E_POINTER);
   TRY_TEST(pPointLoad->get_Mz(nullptr),E_POINTER);
   TRY_TEST(pPointLoad->get_Location(nullptr),E_POINTER);
   TRY_TEST(pPointLoad->get_Orientation(nullptr),E_POINTER);
   TRY_TEST(pPointLoad->GetForce(nullptr,nullptr,nullptr),E_POINTER);
   TRY_TEST(pPointLoad->get_Loading(nullptr),E_POINTER);

   /////////////////////////////////////////////
   // DistributedLoads
   // null test pointers

   // DistributedLoads
   CComPtr<IFem2dDistributedLoadCollection> pDistributedLoads;
   TRY_TEST_HR(pLoading->get_DistributedLoads(&pDistributedLoads));

   CComPtr<IFem2dDistributedLoad> pDistributedLoad;
   TRY_TEST_LC(pDistributedLoads->Create(1, 1, loadDirFy, 0.0, 0.0, 0.0, 0.0, lotMember, &pDistributedLoad));

   TRY_TEST(pDistributedLoads->Create(1, 1, loadDirFy, 0.0, 0.0, 0.0, 0.0, lotMember, nullptr),E_POINTER);
   TRY_TEST(pDistributedLoads->get_Item(0, nullptr),E_POINTER);
   TRY_TEST(pDistributedLoads->Find(0, nullptr),E_POINTER);
   TRY_TEST(pDistributedLoads->get__EnumElements(nullptr),E_POINTER);

   // DistributedLoad
   TRY_TEST(pDistributedLoad->get_ID(nullptr),E_POINTER);
   TRY_TEST(pDistributedLoad->get_MemberID(nullptr),E_POINTER);
   TRY_TEST(pDistributedLoad->get_Orientation(nullptr),E_POINTER);
   TRY_TEST(pDistributedLoad->get_Direction(nullptr),E_POINTER);
   TRY_TEST(pDistributedLoad->get_WStart(nullptr),E_POINTER);
   TRY_TEST(pDistributedLoad->get_WEnd(nullptr),E_POINTER);
   TRY_TEST(pDistributedLoad->get_StartLocation(nullptr),E_POINTER);
   TRY_TEST(pDistributedLoad->get_EndLocation(nullptr),E_POINTER);
   TRY_TEST(pDistributedLoad->get_Loading(nullptr),E_POINTER);

   /////////////////////////////////////////////
   // MemberStrains
   // null test pointers

   // MemberStrains
   CComPtr<IFem2dMemberStrainCollection> pMemberStrains;
   TRY_TEST_HR(pLoading->get_MemberStrains(&pMemberStrains));

   CComPtr<IFem2dMemberStrain> pMemberStrain;
   TRY_TEST_HR(pMemberStrains->Create(1, 1, 0.0, -1.0, 0.0, 0.0, &pMemberStrain));

   TRY_TEST(pMemberStrains->Create(1, 1, 0.0, -1.0, 0.0, 0.0, nullptr),E_POINTER);
   TRY_TEST(pMemberStrains->get_Item(0, nullptr),E_POINTER);
   TRY_TEST(pMemberStrains->Find(0, nullptr),E_POINTER);
   TRY_TEST(pMemberStrains->get__EnumElements(nullptr),E_POINTER);

   // MemberStrain
   TRY_TEST(pMemberStrain->get_ID(nullptr),E_POINTER);
   TRY_TEST(pMemberStrain->get_MemberID(nullptr),E_POINTER);
   TRY_TEST(pMemberStrain->get_AxialStrain(nullptr),E_POINTER);
   TRY_TEST(pMemberStrain->get_CurvatureStrain(nullptr),E_POINTER);
   TRY_TEST(pMemberStrain->get_StartLocation(nullptr),E_POINTER);
   TRY_TEST(pMemberStrain->get_EndLocation(nullptr),E_POINTER);
   TRY_TEST(pMemberStrain->get_Loading(nullptr),E_POINTER);

   // get results interface
   CComQIPtr<IFem2dModelResults> presults(pmodel);

   TRY_TEST(presults->ComputeJointDeflections(0, 4, nullptr, nullptr, nullptr),E_POINTER);
   TRY_TEST(presults->ComputeMemberDeflections(0, 1, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr),E_POINTER);
   TRY_TEST(presults->ComputePOIDeflections(2, 10,  lotGlobal, nullptr, nullptr, nullptr),E_POINTER);
   TRY_TEST(presults->ComputeReactions(0, 3, nullptr, nullptr, nullptr),E_POINTER);
   TRY_TEST(presults->ComputeMemberForces(0, 6, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr),E_POINTER);
   TRY_TEST(presults->ComputePOIForces(0, 14, mftRight, lotGlobal, nullptr, nullptr, nullptr),E_POINTER);

   ReleaseModel(pmodel);
}