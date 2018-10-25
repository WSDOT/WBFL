///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2011  Washington State Department of Transportation
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
// TestISupportErrorInfo.cpp: implementation of the CTestISupportErrorInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestISupportErrorInfo.h"
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


CTestISupportErrorInfo::CTestISupportErrorInfo()
{

}

CTestISupportErrorInfo::~CTestISupportErrorInfo()
{

}

// a macro for testing
#define TEST_EI(ptrnam, mypthing, myiid) \
   CComQIPtr<ISupportErrorInfo>  ptrnam(mypthing); \
   TRY_TEST( ptrnam != 0, true ); \
   TRY_TEST( ptrnam->InterfaceSupportsErrorInfo( myiid ), S_OK ); \
   TRY_TEST( ptrnam->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE ); \
   ptrnam.Release();



void CTestISupportErrorInfo::Test() 
{

/*////////////////////////////////////////////////////

*/////////////////////////////////////////////////

   CComPtr<IFem2dModel> pmodel;
   pmodel = CreateModel();
   ATLASSERT(pmodel);

   // the model
   TEST_EI(pSEIFem2dModel, pmodel, IID_IFem2dModel);

   // joints
   CComPtr<IFem2dJointCollection> pJoints;
   TRY_TEST_HR(pmodel->get_Joints(&pJoints));
   CComPtr<IFem2dJoint> pJoint1,pJoint2;
   TRY_TEST_MC(pJoints->Create(1,  0.0,   0.0, &pJoint1));
   TRY_TEST_MC(pJoints->Create(2,  0.0,  24.0, &pJoint2));

   TEST_EI(pSEIFem2dJoint, pJoint1, IID_IFem2dJoint);
   TEST_EI(pSEIFem2dJoints, pJoints, IID_IFem2dJointCollection);

   // members
   CComPtr<IFem2dMemberCollection> pMembers;
   TRY_TEST_HR(pmodel->get_Members(&pMembers));

   Float64 E=3.0;
   Float64 A=5.0;
   Float64 I=7.0;
   CComPtr<IFem2dMember> pMember1;
   TRY_TEST_MC(pMembers->Create(1,  1,  2, E*A, E*I, &pMember1));

   TEST_EI(pSEIFem2dMember, pMember1, IID_IFem2dMember);
   TEST_EI(pSEIFem2dMembers, pMembers, IID_IFem2dMemberCollection);

   // loadings
   CComPtr<IFem2dLoadingCollection> pLoadings;
   TRY_TEST_HR(pmodel->get_Loadings(&pLoadings));
   CComPtr<IFem2dLoading> pLoading1;
   TRY_TEST_LC(pLoadings->Create(1, &pLoading1));

   TEST_EI(pSEIFem2dLoading, pLoading1, IID_IFem2dLoading);
   TEST_EI(pSEIFem2dLoadings, pLoadings, IID_IFem2dLoadingCollection);

   // distributed loads
   CComPtr<IFem2dDistributedLoadCollection> pDistributedLoads;
   TRY_TEST_HR(pLoading1->get_DistributedLoads(&pDistributedLoads));
   CComPtr<IFem2dDistributedLoad> pDistributedLoad1;
   TRY_TEST_LC(pDistributedLoads->Create(1, 3, loadDirFy, -0.1, -0.7, -2.0, 0.0, lotMember, &pDistributedLoad1));

   TEST_EI(pSEIFem2dDistributedLoad, pDistributedLoad1, IID_IFem2dDistributedLoad);
   TEST_EI(pSEIFem2dDistributedLoads, pDistributedLoads, IID_IFem2dDistributedLoadCollection);

   // joint loads
   CComPtr<IFem2dJointLoadCollection> pJointLoads;
   TRY_TEST_HR(pLoading1->get_JointLoads(&pJointLoads));
   CComPtr<IFem2dJointLoad> pJointLoad;
   TRY_TEST_LC(pJointLoads->Create(1, 3, 12.0, 0.0, 0.0, &pJointLoad));

   TEST_EI(pSEIFem2dJointLoad, pJointLoad, IID_IFem2dJointLoad);
   TEST_EI(pSEIFem2dJointLoads, pJointLoads, IID_IFem2dJointLoadCollection);

   // point loads
   CComPtr<IFem2dPointLoadCollection> pPointLoads;
   TRY_TEST_HR(pLoading1->get_PointLoads(&pPointLoads));
   CComPtr<IFem2dPointLoad> pPointLoad;
   TRY_TEST_LC(pPointLoads->Create(1, 1, -0.6, 4.0, -3.0, 0.0, lotMember, &pPointLoad));

   TEST_EI(pSEIFem2dPointLoad, pPointLoad, IID_IFem2dPointLoad);
   TEST_EI(pSEIFem2dPointLoads, pPointLoads, IID_IFem2dPointLoadCollection);

   // member strain
   CComPtr<IFem2dMemberStrainCollection> pMemberStrains;
   TRY_TEST_HR(pLoading1->get_MemberStrains(&pMemberStrains));
   CComPtr<IFem2dMemberStrain> pMemberStrain;
   TRY_TEST_LC(pMemberStrains->Create(1, 7, 0.05, 0.0, &pMemberStrain));

   TEST_EI(pSEIFem2dMemberStrain, pMemberStrain, IID_IFem2dMemberStrain);
   TEST_EI(pSEIFem2dMemberStrains, pMemberStrains, IID_IFem2dMemberStrainCollection);

   // support displacement 
   CComPtr<IFem2dJointDisplacementCollection> pJointDisplacements;
   TRY_TEST_HR(pLoading1->get_JointDisplacements(&pJointDisplacements));
   CComPtr<IFem2dJointDisplacement> pJointDisplacement;
   TRY_TEST_LC(pJointDisplacements->Create(1, 4, 0.4, -0.6, 0.0, &pJointDisplacement));

   TEST_EI(pSEIFem2dJointDisplacement, pJointDisplacement, IID_IFem2dJointDisplacement);
   TEST_EI(pSEIFem2dJointDisplacements, pJointDisplacements, IID_IFem2dJointDisplacementCollection);

   //  POI's 
   CComPtr<IFem2dPOICollection> pPOIs;
   TRY_TEST_HR(pmodel->get_POIs(&pPOIs));
   CComPtr<IFem2dPOI> pPOI;
   TRY_TEST_HR(pPOIs->Create(35,    3,  -0.5,  &pPOI));

   TEST_EI(pSEIFem2dPOI, pPOI, IID_IFem2dPOI);
   TEST_EI(pSEIFem2dPOIs, pPOIs, IID_IFem2dPOICollection);

   ReleaseModel(pmodel);
}