///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 2001  Washington State Department of Transportation
//                   Bridge and Structures Office
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
// TestMember.cpp: implementation of the CTestMember class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestMember.h"
#include <iostream> 

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestMember::CTestMember()
{

}

CTestMember::~CTestMember()
{

}

void CTestMember::Test()
{
   // fire up the model and create some joints
   CComPtr<IFem2dModel> pmodel;
   pmodel = CreateModel();
   ATLASSERT(pmodel);

   // get results interface
   CComQIPtr<IFem2dModelResults> presults(pmodel);

   // some error checking
   Float64 dx, dy, rz;
   TRY_TEST(presults->ComputeJointDisplacements(0, 0, &dx, &dy, &rz),FEM2D_E_MODEL_HAS_NO_JOINTS);

   CComPtr<IFem2dJointCollection> pJoints;
   TRY_TEST_HR(pmodel->get_Joints(&pJoints));

   CComPtr<IFem2dJoint> pJoint0,pJoint2,pJoint4,pJoint5,pJoint6;
   TRY_TEST_MC(pJoints->Create(0,  2,  3, &pJoint0));
   TRY_TEST_MC(pJoints->Create(2, 22, 32, &pJoint2));
   TRY_TEST_MC(pJoints->Create(4, 44, 34, &pJoint4));
   TRY_TEST_MC(pJoints->Create(5, 55, 35, &pJoint5));
   TRY_TEST_MC(pJoints->Create(6, 55, 35, &pJoint6)); // same loc as joint 5

   TRY_TEST(presults->ComputeJointDisplacements(0, 0, &dx, &dy, &rz),FEM2D_E_MODEL_HAS_NO_MEMBERS);

   CComPtr<IFem2dMemberCollection> pMembers;
   TRY_TEST_HR(pmodel->get_Members(&pMembers));

   CComPtr<IFem2dMember> pMember0,pMember3, pMember4, pMember5, pMember7,ptj;
   TRY_TEST_MC(pMembers->Create(0,  0,  2, 100, 105, &pMember0));
   TRY_TEST_MC(pMembers->Create(3,  2,  5, 110, 115, &pMember3));
   TRY_TEST(pMembers->Create(3,  2,  5, 110, 115, &ptj),FEM2D_E_MEMBER_WITH_ID_ALREADY_EXISTS);
   TRY_TEST_MC(pMembers->Create(4, 54,  5, 110, 115, &pMember4)); // joint doesn't exist
   TRY_TEST(pMembers->Create(7,  4,  4, 120, 125, &pMember7), FEM2D_E_MEMBER_HAS_SAME_JOINTS );
   TRY_TEST_MC(pMembers->Create(5, 5, 6, 110, 115, &pMember5)); // zero length

   MemberIDType id;
   TRY_TEST_HR(pMember3->get_ID(&id));
   TRY_TEST(id, 3);

   Float64 len;
   TRY_TEST_HR(pMember3->get_Length(&len));
   TRY_TEST(len,sqrt(1098.));

   TRY_TEST(pMember5->get_Length(&len),FEM2D_E_ZERO_LENGTH_MEMBER);

   TRY_TEST(pMember4->get_Length(&len), FEM2D_E_MEMBER_JOINT_NOT_EXISTS);

   JointIDType startJoint, endJoint;
   TRY_TEST_HR(pMember0->get_StartJoint(&startJoint));
   TRY_TEST_HR(pMember0->get_EndJoint(&endJoint));
   TRY_TEST(startJoint, 0);
   TRY_TEST(endJoint, 2);

   TRY_TEST_MC(pMember0->put_StartJoint(3));
   TRY_TEST_MC(pMember0->put_EndJoint(0));
   TRY_TEST_HR(pMember0->get_StartJoint(&startJoint));
   TRY_TEST_HR(pMember0->get_EndJoint(&endJoint));
   TRY_TEST(startJoint, 3);
   TRY_TEST(endJoint, 0);

   Float64 EA, EI;
   TRY_TEST_HR(pMember0->get_EA(&EA));
   TRY_TEST_HR(pMember0->get_EI(&EI));
   TRY_TEST(EA, 100);
   TRY_TEST(EI, 105);

   TRY_TEST_MC(pMember0->put_EA(3));
   TRY_TEST_MC(pMember0->put_EI(4));
   TRY_TEST_HR(pMember0->get_EA(&EA));
   TRY_TEST_HR(pMember0->get_EI(&EI));
   TRY_TEST(EA, 3);
   TRY_TEST(EI, 4);

   TRY_TEST(pMember0->put_EA(-2.0),FEM2D_E_STIFFNESS_MUST_BE_POSITIVE);
   TRY_TEST(pMember0->put_EI(-2.0),FEM2D_E_STIFFNESS_MUST_BE_POSITIVE);
   TRY_TEST_HR(pMember0->get_EA(&EA));
   TRY_TEST_HR(pMember0->get_EI(&EI));
   TRY_TEST(EA, 3);
   TRY_TEST(EI, 4);

   VARIANT_BOOL rel;
   TRY_TEST_HR(pMember0->IsReleased(metStart, &rel));
   TRY_TEST(rel, VARIANT_FALSE);
   TRY_TEST_HR(pMember0->IsReleased(metEnd, &rel));
   TRY_TEST(rel, VARIANT_FALSE);

   TRY_TEST_MC(pMember0->ReleaseEnd(metStart, mbrReleaseMz));
   TRY_TEST_HR(pMember0->IsReleased(metStart, &rel));
   TRY_TEST(rel, VARIANT_TRUE);
   TRY_TEST_MC(pMember0->ReleaseEnd(metEnd, mbrReleaseMz));
   TRY_TEST_HR(pMember0->IsReleased(metEnd, &rel));
   TRY_TEST(rel, VARIANT_TRUE);

   TRY_TEST_MC(pMember0->ReleaseEnd(metStart, mbrReleaseNone));
   TRY_TEST_MC(pMember0->ReleaseEnd(metEnd, mbrReleaseNone));
   TRY_TEST_HR(pMember0->IsReleased(metStart, &rel));
   TRY_TEST(rel, VARIANT_FALSE);
   TRY_TEST_HR(pMember0->IsReleased(metEnd, &rel));
   TRY_TEST(rel, VARIANT_FALSE);

   ReleaseModel(pmodel);
}
