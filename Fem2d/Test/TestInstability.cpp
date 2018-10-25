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
// TestInstability.cpp: implementation of the CTestInstability class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestInstability.h"
#include <MathEx.h>
#include <iostream> 

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestInstability::CTestInstability()
{

}

CTestInstability::~CTestInstability()
{

}

void CTestInstability::Test() 
{

/*////////////////////////////////////////////////////
 
 
 
 
 

        1              2             3
        o--------------o-------------o
        ^       1             1      ^

 

*/////////////////////////////////////////////////
   CComPtr<IFem2dModel> pmodel;
   pmodel = CreateModel();
   ATLASSERT(pmodel);

   // create joints
   CComPtr<IFem2dJointCollection> pJoints;
   TRY_TEST_HR(pmodel->get_Joints(&pJoints));

   CComPtr<IFem2dJoint> pJoint1,pJoint2,pJoint3;
   TRY_TEST_MC(pJoints->Create(1,  0.0,   0.0, &pJoint1));
   TRY_TEST_MC(pJoints->Create(2,  0.0,  10.0, &pJoint2));
   TRY_TEST_MC(pJoints->Create(3,  0.0,  20.0, &pJoint3));

   // get results interface
   CComQIPtr<IFem2dModelResults> presults(pmodel);


   // create members
   CComPtr<IFem2dMemberCollection> pMembers;
   TRY_TEST_HR(pmodel->get_Members(&pMembers));

   Float64 E=29000;
   Float64 A=10;
   Float64 I=250;
   CComPtr<IFem2dMember> pMember1, pMember2;
   TRY_TEST_MC(pMembers->Create(1,  1,  2, E*A, E*I, &pMember1));
   TRY_TEST_MC(pMembers->Create(2,  2,  3, E*A, E*I, &pMember2));

   // create load case and apply Distributed load to members
   CComPtr<IFem2dLoadingCollection> pLoadings;
   TRY_TEST_HR(pmodel->get_Loadings(&pLoadings));
   CComPtr<IFem2dLoading> pLoading0;
   TRY_TEST_LC(pLoadings->Create(0, &pLoading0));
   CComPtr<IFem2dDistributedLoadCollection> pDistributedLoads;
   TRY_TEST_HR(pLoading0->get_DistributedLoads(&pDistributedLoads));
   CComPtr<IFem2dDistributedLoad> pDistributedLoad;
   TRY_TEST_LC(pDistributedLoads->Create(1, 1, loadDirFy, 0.0, -1.0, -0.5, -1.0, lotMember, &pDistributedLoad));

   // no boundary conditions - we're flying through space
   // get joint displacements
   Float64 dx, dy, rz;
   TRY_TEST(presults->ComputeJointDisplacements(0, 2, &dx, &dy, &rz), FEM2D_E_MATRIX_FACTORING);

   // support end, should now be cantilever - ok
   TRY_TEST_MC(pJoint1->Support());
   TRY_TEST_HR(presults->ComputeJointDisplacements(0, 2, &dx, &dy, &rz));

   // now a floppy cantilever
   TRY_TEST_MC(pJoint1->ReleaseDof(jrtMz));
   TRY_TEST(presults->ComputeJointDisplacements(0, 2, &dx, &dy, &rz), FEM2D_E_MATRIX_BACK_SUBSTITUTION);

   // now pin-pin
   TRY_TEST_MC(pJoint3->Support());
   TRY_TEST_MC(pJoint3->ReleaseDof(jrtMz));
   TRY_TEST_HR(presults->ComputeJointDisplacements(0, 2, &dx, &dy, &rz));

   // put a hinge in the end of member 1
   TRY_TEST_MC(pMember1->ReleaseEnd(metEnd, mbrReleaseMz));
   TRY_TEST(presults->ComputeJointDisplacements(0, 2, &dx, &dy, &rz), FEM2D_E_MATRIX_BACK_SUBSTITUTION);

   TRY_TEST_MC(pMember1->ReleaseEnd(metEnd, mbrReleaseNone));
   TRY_TEST_HR(presults->ComputeJointDisplacements(0, 2, &dx, &dy, &rz));

   // pin at a released dof
   TRY_TEST_MC(pMember1->ReleaseEnd(metStart, mbrReleaseMz));
   TRY_TEST(presults->ComputeJointDisplacements(0, 2, &dx, &dy, &rz), FEM2D_E_MATRIX_FACTORING);

   // pin at start of member 2
   TRY_TEST_MC(pMember1->ReleaseEnd(metStart, mbrReleaseNone));
   TRY_TEST_MC(pMember2->ReleaseEnd(metStart, mbrReleaseMz));
   TRY_TEST(presults->ComputeJointDisplacements(0, 2, &dx, &dy, &rz), FEM2D_E_MATRIX_BACK_SUBSTITUTION);

   ReleaseModel(pmodel);
}