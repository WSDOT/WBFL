///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2010  Washington State Department of Transportation
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
// TestJointDisplacement.cpp: implementation of the CTestJointDisplacement class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestJointDisplacement.h"
#include <iostream> 

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CTestJointDisplacement::CTestJointDisplacement()
{

}

CTestJointDisplacement::~CTestJointDisplacement()
{

}

void CTestJointDisplacement::Test()
{
   // create a model
   CComPtr<IFem2dModel> pmodel;
   pmodel = CreateModel();
   ATLASSERT(pmodel);

   CComPtr<IFem2dJointCollection> pJoints;
   TRY_TEST_HR(pmodel->get_Joints(&pJoints));

   CComPtr<IFem2dJoint> pJoint0,pJoint2,pJoint4,pJoint5;
   TRY_TEST_MC(pJoints->Create(0,  2,  3, &pJoint0));
   TRY_TEST_MC(pJoints->Create(2, 22, 32, &pJoint2));
   TRY_TEST_MC(pJoints->Create(4, 44, 34, &pJoint4));
   TRY_TEST_MC(pJoints->Create(5, 55, 35, &pJoint5));

   CComPtr<IFem2dMemberCollection> pMembers;
   TRY_TEST_HR(pmodel->get_Members(&pMembers));

   CComPtr<IFem2dMember> pMember0,pMember3, pMember4,pMember7,ptj;
   TRY_TEST_MC(pMembers->Create(0,  0,  2, 100, 105, &pMember0));
   TRY_TEST_MC(pMembers->Create(3,  2,  5, 110, 115, &pMember3));

   CComPtr<IFem2dLoadingCollection> pLoadings;
   TRY_TEST_HR(pmodel->get_Loadings(&pLoadings));

   CComPtr<IFem2dLoading> pLoading0,pLoading3,pl;
   TRY_TEST_LC(pLoadings->Create(0, &pLoading0));
   TRY_TEST(pLoadings->Create(0, &pl),FEM2D_E_LOADING_WITH_ID_ALREADY_EXISTS);
   TRY_TEST_LC(pLoadings->Create(3, &pLoading3));

   CComPtr<IFem2dJointDisplacementCollection> pJointDisplacements;
   TRY_TEST_HR(pLoading0->get_JointDisplacements(&pJointDisplacements));

   CComPtr<IFem2dJointDisplacement> pJointDisplacement0,pJointDisplacement3,pjl;
   TRY_TEST_LC(pJointDisplacements->Create(0, 0, 23.2, 42.3, 52.3, &pJointDisplacement0));
   TRY_TEST(pJointDisplacements->Create(0, 0, 0, 0, 0, &pjl),FEM2D_E_JOINT_DISP_WITH_ID_ALREADY_EXISTS);
   TRY_TEST_LC(pJointDisplacements->Create(3, 5, 33, 44, 55, &pJointDisplacement3));

   LoadIDType loadID;
   TRY_TEST_HR(pJointDisplacement3->get_ID(&loadID));
   TRY_TEST(loadID, 3);

   JointIDType jntID;
   TRY_TEST_HR(pJointDisplacement3->get_JointID(&jntID));
   TRY_TEST(jntID, 5);

   TRY_TEST_LC(pJointDisplacement3->put_JointID(42));
   TRY_TEST_HR(pJointDisplacement3->get_JointID(&jntID));
   TRY_TEST(jntID, 42);

   Float64 dx, dy, rz;
   TRY_TEST_HR(pJointDisplacement3->get_Dx(&dx));
   TRY_TEST_HR(pJointDisplacement3->get_Dy(&dy));
   TRY_TEST_HR(pJointDisplacement3->get_Rz(&rz));
   TRY_TEST(dx, 33);
   TRY_TEST(dy, 44);
   TRY_TEST(rz, 55);

   TRY_TEST_LC(pJointDisplacement3->put_Dx(-11));
   TRY_TEST_LC(pJointDisplacement3->put_Dy(-12));
   TRY_TEST_LC(pJointDisplacement3->put_Rz(-13));
   TRY_TEST_HR(pJointDisplacement3->get_Dx(&dx));
   TRY_TEST_HR(pJointDisplacement3->get_Dy(&dy));
   TRY_TEST_HR(pJointDisplacement3->get_Rz(&rz));
   TRY_TEST(dx, -11);
   TRY_TEST(dy, -12);
   TRY_TEST(rz, -13);

   TRY_TEST_HR(pJointDisplacement3->GetDisplacement(&dx, &dy, &rz));
   TRY_TEST(dx, -11);
   TRY_TEST(dy, -12);
   TRY_TEST(rz, -13);

   TRY_TEST_LC(pJointDisplacement3->SetDisplacement(22, 23, 24));
   TRY_TEST_HR(pJointDisplacement3->GetDisplacement(&dx, &dy, &rz));
   TRY_TEST(dx, 22 );
   TRY_TEST(dy, 23 );
   TRY_TEST(rz, 24 );

   // play some games with the reference counter
   pLoading0 = 0;
   pJointDisplacements = 0;
   ReleaseModel(pmodel);
   pmodel = 0;

   TRY_TEST_HR(pJointDisplacement3->get_Dx(&dx));
   TRY_TEST_HR(pJointDisplacement3->get_Dy(&dy));
   TRY_TEST_HR(pJointDisplacement3->get_Rz(&rz));
   TRY_TEST(dx, 22 );
   TRY_TEST(dy, 23 );
   TRY_TEST(rz, 24 );

}
