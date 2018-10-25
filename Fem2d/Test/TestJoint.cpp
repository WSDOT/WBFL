///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2016  Washington State Department of Transportation
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
// TestJoint.cpp: implementation of the CTestJoint class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestJoint.h"
#include <iostream> 

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestJoint::CTestJoint()
{

}

CTestJoint::~CTestJoint()
{

}

void CTestJoint::Test()
{
   // fire up the model and create some joints
   CComPtr<IFem2dModel> pmodel;
   pmodel = CreateModel();

   CComPtr<IFem2dJointCollection> pJoints;
   TRY_TEST_HR(pmodel->get_Joints(&pJoints));

   CComPtr<IFem2dJoint> pJoint0,pJoint2,pJoint4,pJoint5,ptj;
   TRY_TEST_MC(pJoints->Create(0,  2,  3, &pJoint0));
   TRY_TEST_MC(pJoints->Create(2, 22, 32, &pJoint2));
   TRY_TEST_MC(pJoints->Create(4, 44, 34, &pJoint4));
   TRY_TEST_MC(pJoints->Create(5, 55, 35, &pJoint5));
   TRY_TEST(pJoints->Create(5, 55, 35, &ptj),FEM2D_E_JOINT_WITH_ID_ALREADY_EXISTS);

   // grab a joint by id and check its data
   CComPtr<IFem2dJoint> pj2r;
   TRY_TEST_HR(pJoints->Find(2, &pj2r));
   LoadIDType id;
   Float64 x,y;
   TRY_TEST_HR(pj2r->get_ID(&id));
   TRY_TEST_HR(pj2r->get_X(&x));
   TRY_TEST_HR(pj2r->get_Y(&y));
   TRY_TEST(id, 2);
   TRY_TEST(x, 22);
   TRY_TEST(y, 32);


   TRY_TEST_MC(pj2r->put_X(200.));
   TRY_TEST_MC(pj2r->put_Y(300.));
   TRY_TEST_HR(pj2r->get_X(&x)); 
   TRY_TEST_HR(pj2r->get_Y(&y));
   TRY_TEST(x, 200);
   TRY_TEST(y, 300);

   pj2r = 0;

   TRY_TEST_HR(pJoints->Find(5,&pj2r));
   TRY_TEST_HR(pj2r->get_ID(&id));
   TRY_TEST_HR(pj2r->get_X(&x));
   TRY_TEST_HR(pj2r->get_Y(&y));
   TRY_TEST(id, 5);
   TRY_TEST(x, 55);
   TRY_TEST(y, 35);

   CollectionIndexType cnt;
   TRY_TEST_HR(pJoints->get_Count(&cnt));
   TRY_TEST(cnt,4);

   // create some members and connect them to joints
   CComPtr<IFem2dMemberCollection> pMembers;
   TRY_TEST_HR(pmodel->get_Members(&pMembers));

   CComPtr<IFem2dMember> pMember0,pMember1, pMember2, pMember3, pMember7;
   TRY_TEST_MC(pMembers->Create(0, 0,  2, 100, 105, &pMember0));
   TRY_TEST_MC(pMembers->Create(1, 0,  4, 110, 115, &pMember1));
   TRY_TEST_MC(pMembers->Create(2, 5,  4, 110, 115, &pMember2));
   TRY_TEST_MC(pMembers->Create(3, 5,  2, 110, 115, &pMember3));
   TRY_TEST_MC(pMembers->Create(7, 5,  0, 110, 115, &pMember7));

   // look at members connected to joint 0
   CComPtr<IIDArray> pMbrIds;
   TRY_TEST_HR(pJoint0->get_Members(&pMbrIds));
   TRY_TEST_HR(pMbrIds->get_Count(&cnt));
   TRY_TEST(cnt,3);

   MemberIDType mbID;
   TRY_TEST_HR(pMbrIds->get_Item(0, &mbID));
   TRY_TEST(mbID,0);
   TRY_TEST_HR(pMbrIds->get_Item(1, &mbID));
   TRY_TEST(mbID,1);
   TRY_TEST_HR(pMbrIds->get_Item(2, &mbID));
   TRY_TEST(mbID,7);
   TRY_TEST(pMbrIds->get_Item(3, &mbID), E_INVALIDARG );

   JointIDType jntID;
   TRY_TEST_MC(pJoints->Remove(2, atID,&jntID));
   TRY_TEST(jntID, 2);
   TRY_TEST_MC(pJoints->Remove(1, atIndex,&jntID));
   TRY_TEST(jntID, 4);

   TRY_TEST_HR(pJoints->get_Count(&cnt));
   TRY_TEST(cnt,2);

   CComPtr<IFem2dEnumJoint> penum;
   TRY_TEST_HR(pJoints->get__EnumElements(&penum));

   IFem2dJoint* pj;
   unsigned long num_fetched=0;
   long i=0;
   TRY_TEST_HR(penum->Next(1, &pj, &num_fetched));
   while (num_fetched==1)
   {
      TRY_TEST_HR(pj->get_ID(&id));
      TRY_TEST_HR(pj->get_X(&x));
      TRY_TEST_HR(pj->get_Y(&y));

      if (i==0)
      {
         TRY_TEST(id, 0);
         TRY_TEST(x, 2);
         TRY_TEST(y, 3);
      }
      else if (i==1)
      {
         TRY_TEST(id, 5);
         TRY_TEST(x, 55);
         TRY_TEST(y, 35);
      }

      pj->Release();
      TRY_TEST(FAILED(penum->Next(1, &pj, &num_fetched)),FALSE);
      i++;
   }

   TRY_TEST(i,2);

   CComPtr<IFem2dJoint> psj;
   TRY_TEST(pJoints->get_Item(2,&psj), E_INVALIDARG);

   pj = 0;
   TRY_TEST_HR(pJoints->get_Item(0,&psj));
   TRY_TEST_HR(psj->get_ID(&id));
   TRY_TEST(id, 0);

   // test releases on joints
   VARIANT_BOOL st;
   TRY_TEST_HR(psj->IsSupport(&st));
   TRY_TEST(st, VARIANT_FALSE);
   TRY_TEST_HR(psj->IsDofReleased(jrtNone, &st));
   TRY_TEST(st, VARIANT_FALSE);
   TRY_TEST_HR(psj->IsDofReleased(jrtFx, &st));
   TRY_TEST(st, VARIANT_TRUE);
   TRY_TEST_HR(psj->IsDofReleased(jrtFy, &st));
   TRY_TEST(st, VARIANT_TRUE);
   TRY_TEST_HR(psj->IsDofReleased(jrtMz, &st));
   TRY_TEST(st, VARIANT_TRUE);
   TRY_TEST_HR(psj->IsDofReleased(jrtAll, &st));
   TRY_TEST(st, VARIANT_TRUE);
   TRY_TEST_HR(psj->IsDofSupported(jrtNone, &st));
   TRY_TEST(st, VARIANT_TRUE);
   TRY_TEST_HR(psj->IsDofSupported(jrtFx, &st));
   TRY_TEST(st, VARIANT_FALSE);
   TRY_TEST_HR(psj->IsDofSupported(jrtFy, &st));
   TRY_TEST(st, VARIANT_FALSE);
   TRY_TEST_HR(psj->IsDofSupported(jrtMz, &st));
   TRY_TEST(st, VARIANT_FALSE);
   TRY_TEST_HR(psj->IsDofSupported(jrtAll, &st));
   TRY_TEST(st, VARIANT_FALSE);


   TRY_TEST_HR(psj->Support()); 
   TRY_TEST_HR(psj->IsSupport(&st));
   TRY_TEST(st, VARIANT_TRUE);
   TRY_TEST_HR(psj->IsDofReleased(jrtNone, &st));
   TRY_TEST(st, VARIANT_TRUE);
   TRY_TEST_HR(psj->IsDofReleased(jrtFx, &st));
   TRY_TEST(st, VARIANT_FALSE);
   TRY_TEST_HR(psj->IsDofReleased(jrtFy, &st));
   TRY_TEST(st, VARIANT_FALSE);
   TRY_TEST_HR(psj->IsDofReleased(jrtMz, &st));
   TRY_TEST(st, VARIANT_FALSE);
   TRY_TEST_HR(psj->IsDofReleased(jrtAll, &st));
   TRY_TEST(st, VARIANT_FALSE);
   TRY_TEST_HR(psj->IsDofSupported(jrtNone, &st));
   TRY_TEST(st, VARIANT_FALSE);
   TRY_TEST_HR(psj->IsDofSupported(jrtFx, &st));
   TRY_TEST(st, VARIANT_TRUE);
   TRY_TEST_HR(psj->IsDofSupported(jrtFy, &st));
   TRY_TEST(st, VARIANT_TRUE);
   TRY_TEST_HR(psj->IsDofSupported(jrtMz, &st));
   TRY_TEST(st, VARIANT_TRUE);
   TRY_TEST_HR(psj->IsDofSupported(jrtAll, &st));
   TRY_TEST(st, VARIANT_TRUE);


   TRY_TEST_HR(psj->ReleaseDof(jrtFx));
   TRY_TEST_HR(psj->IsSupport(&st));
   TRY_TEST(st, VARIANT_TRUE);
   TRY_TEST_HR(psj->IsDofReleased(jrtNone, &st));
   TRY_TEST(st, VARIANT_FALSE);
   TRY_TEST_HR(psj->IsDofReleased(jrtFx, &st));
   TRY_TEST(st, VARIANT_TRUE);
   TRY_TEST_HR(psj->IsDofReleased(jrtFy, &st));
   TRY_TEST(st, VARIANT_FALSE);
   TRY_TEST_HR(psj->IsDofReleased(jrtMz, &st));
   TRY_TEST(st, VARIANT_FALSE);
   TRY_TEST_HR(psj->IsDofReleased(jrtAll, &st));
   TRY_TEST(st, VARIANT_FALSE);
   TRY_TEST_HR(psj->IsDofSupported(jrtNone, &st));
   TRY_TEST(st, VARIANT_FALSE);
   TRY_TEST_HR(psj->IsDofSupported(jrtFx, &st));
   TRY_TEST(st, VARIANT_FALSE);
   TRY_TEST_HR(psj->IsDofSupported(jrtFy, &st));
   TRY_TEST(st, VARIANT_TRUE);
   TRY_TEST_HR(psj->IsDofSupported(jrtMz, &st));
   TRY_TEST(st, VARIANT_TRUE);
   TRY_TEST_HR(psj->IsDofSupported(jrtAll, &st));
   TRY_TEST(st, VARIANT_FALSE);


   TRY_TEST_MC(psj->ReleaseDof(jrtFy));
   TRY_TEST_HR(psj->IsSupport(&st));
   TRY_TEST(st, VARIANT_TRUE);
   TRY_TEST_HR(psj->IsDofReleased(jrtNone, &st));
   TRY_TEST(st, VARIANT_FALSE);
   TRY_TEST_HR(psj->IsDofReleased(jrtFx, &st));
   TRY_TEST(st, VARIANT_TRUE);
   TRY_TEST_HR(psj->IsDofReleased(jrtFy, &st));
   TRY_TEST(st, VARIANT_TRUE);
   TRY_TEST_HR(psj->IsDofReleased(jrtMz, &st));
   TRY_TEST(st, VARIANT_FALSE);
   TRY_TEST_HR(psj->IsDofReleased(jrtAll, &st));
   TRY_TEST(st, VARIANT_FALSE);
   TRY_TEST_HR(psj->IsDofSupported(jrtNone, &st));
   TRY_TEST(st, VARIANT_FALSE);
   TRY_TEST_HR(psj->IsDofSupported(jrtFx, &st));
   TRY_TEST(st, VARIANT_FALSE);
   TRY_TEST_HR(psj->IsDofSupported(jrtFy, &st));
   TRY_TEST(st, VARIANT_FALSE);
   TRY_TEST_HR(psj->IsDofSupported(jrtMz, &st));
   TRY_TEST(st, VARIANT_TRUE);
   TRY_TEST_HR(psj->IsDofSupported(jrtAll, &st));
   TRY_TEST(st, VARIANT_FALSE);

   TRY_TEST_MC(psj->ReleaseDof(jrtMz));
   TRY_TEST_HR(psj->IsSupport(&st));
   TRY_TEST(st, VARIANT_FALSE);
   TRY_TEST_HR(psj->IsDofReleased(jrtNone, &st));
   TRY_TEST(st, VARIANT_FALSE);
   TRY_TEST_HR(psj->IsDofReleased(jrtFx, &st));
   TRY_TEST(st, VARIANT_TRUE);
   TRY_TEST_HR(psj->IsDofReleased(jrtFy, &st));
   TRY_TEST(st, VARIANT_TRUE);
   TRY_TEST_HR(psj->IsDofReleased(jrtMz, &st));
   TRY_TEST(st, VARIANT_TRUE);
   TRY_TEST_HR(psj->IsDofReleased(jrtAll, &st));
   TRY_TEST(st, VARIANT_TRUE);
   TRY_TEST_HR(psj->IsDofSupported(jrtNone, &st));
   TRY_TEST(st, VARIANT_TRUE);
   TRY_TEST_HR(psj->IsDofSupported(jrtFx, &st));
   TRY_TEST(st, VARIANT_FALSE);
   TRY_TEST_HR(psj->IsDofSupported(jrtFy, &st));
   TRY_TEST(st, VARIANT_FALSE);
   TRY_TEST_HR(psj->IsDofSupported(jrtMz, &st));
   TRY_TEST(st, VARIANT_FALSE);
   TRY_TEST_HR(psj->IsDofSupported(jrtAll, &st));
   TRY_TEST(st, VARIANT_FALSE);


   TRY_TEST_MC(psj->Support());
   TRY_TEST_MC(psj->Free());
   TRY_TEST_HR(psj->IsSupport(&st));
   TRY_TEST(st, VARIANT_FALSE);
   TRY_TEST_HR(psj->IsDofReleased(jrtNone, &st));
   TRY_TEST(st, VARIANT_FALSE);
   TRY_TEST_HR(psj->IsDofReleased(jrtFx, &st));
   TRY_TEST(st, VARIANT_TRUE);
   TRY_TEST_HR(psj->IsDofReleased(jrtFy, &st));
   TRY_TEST(st, VARIANT_TRUE);
   TRY_TEST_HR(psj->IsDofReleased(jrtMz, &st));
   TRY_TEST(st, VARIANT_TRUE);
   TRY_TEST_HR(psj->IsDofReleased(jrtAll, &st));
   TRY_TEST(st, VARIANT_TRUE);
   TRY_TEST_HR(psj->IsDofSupported(jrtNone, &st));
   TRY_TEST(st, VARIANT_TRUE);
   TRY_TEST_HR(psj->IsDofSupported(jrtFx, &st));
   TRY_TEST(st, VARIANT_FALSE);
   TRY_TEST_HR(psj->IsDofSupported(jrtFy, &st));
   TRY_TEST(st, VARIANT_FALSE);
   TRY_TEST_HR(psj->IsDofSupported(jrtMz, &st));
   TRY_TEST(st, VARIANT_FALSE);
   TRY_TEST_HR(psj->IsDofSupported(jrtAll, &st));
   TRY_TEST(st, VARIANT_FALSE);


   // set the model's pointer to zero to make sure memory counting is working
   ReleaseModel(pmodel);
   pmodel=0;

   // test enum nonsense that can come out of vb
   TRY_TEST_HR(psj->Support());
   TRY_TEST_HR(psj->ReleaseDof((Fem2dJointReleaseType)(jrtFx+jrtMz)));
   TRY_TEST_HR(psj->IsSupport(&st));
   TRY_TEST(st, VARIANT_TRUE);
   TRY_TEST_HR(psj->IsDofReleased(jrtNone, &st));
   TRY_TEST(st, VARIANT_FALSE);
   TRY_TEST_HR(psj->IsDofReleased(jrtFx, &st));
   TRY_TEST(st, VARIANT_TRUE);
   TRY_TEST_HR(psj->IsDofReleased(jrtFy, &st));
   TRY_TEST(st, VARIANT_FALSE);
   TRY_TEST_HR(psj->IsDofReleased(jrtMz, &st));
   TRY_TEST(st, VARIANT_TRUE);
   TRY_TEST_HR(psj->IsDofReleased(jrtAll, &st));
   TRY_TEST(st, VARIANT_FALSE);
   TRY_TEST_HR(psj->IsDofSupported(jrtNone, &st));
   TRY_TEST(st, VARIANT_FALSE);
   TRY_TEST_HR(psj->IsDofSupported(jrtFx, &st));
   TRY_TEST(st, VARIANT_FALSE);
   TRY_TEST_HR(psj->IsDofSupported(jrtFy, &st));
   TRY_TEST(st, VARIANT_TRUE);
   TRY_TEST_HR(psj->IsDofSupported(jrtMz, &st));
   TRY_TEST(st, VARIANT_FALSE);
   TRY_TEST_HR(psj->IsDofSupported(jrtAll, &st));
   TRY_TEST(st, VARIANT_FALSE);


   TRY_TEST_HR(psj->Support());
   TRY_TEST_HR(psj->ReleaseDof((Fem2dJointReleaseType)(jrtFx+jrtFy+jrtMz)));
   TRY_TEST_HR(psj->IsSupport(&st));
   TRY_TEST(st, VARIANT_FALSE);
   TRY_TEST_HR(psj->IsDofReleased(jrtNone, &st));
   TRY_TEST(st, VARIANT_FALSE);
   TRY_TEST_HR(psj->IsDofReleased(jrtFx, &st));
   TRY_TEST(st, VARIANT_TRUE);
   TRY_TEST_HR(psj->IsDofReleased(jrtFy, &st));
   TRY_TEST(st, VARIANT_TRUE);
   TRY_TEST_HR(psj->IsDofReleased(jrtMz, &st));
   TRY_TEST(st, VARIANT_TRUE);
   TRY_TEST_HR(psj->IsDofReleased(jrtAll, &st));
   TRY_TEST(st, VARIANT_TRUE);
   TRY_TEST_HR(psj->IsDofSupported(jrtNone, &st));
   TRY_TEST(st, VARIANT_TRUE);
   TRY_TEST_HR(psj->IsDofSupported(jrtFx, &st));
   TRY_TEST(st, VARIANT_FALSE);
   TRY_TEST_HR(psj->IsDofSupported(jrtFy, &st));
   TRY_TEST(st, VARIANT_FALSE);
   TRY_TEST_HR(psj->IsDofSupported(jrtMz, &st));
   TRY_TEST(st, VARIANT_FALSE);
   TRY_TEST_HR(psj->IsDofSupported(jrtAll, &st));
   TRY_TEST(st, VARIANT_FALSE);
}
