///////////////////////////////////////////////////////////////////////
// RCCapacity Test - Test driver for RCCapacity library
// Copyright © 1999-2017  Washington State Department of Transportation
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

// MomentCurvatureSolverTest.cpp: implementation of the CMomentCurvatureSolverTest class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MomentCurvatureSolverTest.h"
#include "GeneralTests.h"
#include <WBFLUnitServer.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMomentCurvatureSolverTest::CMomentCurvatureSolverTest()
{

}

CMomentCurvatureSolverTest::~CMomentCurvatureSolverTest()
{

}

void CMomentCurvatureSolverTest::Test()
{
   CHRException hr;

   CComPtr<IUnitServer> unit_server;
   unit_server.CoCreateInstance(CLSID_UnitServer);
   
   // base units of kip and ksi
   hr = unit_server->SetBaseUnits(CComBSTR("12kslug"),CComBSTR("in"),CComBSTR("sec"),CComBSTR("F"),CComBSTR("deg"));

   // Get a general section
   CComPtr<IGeneralSection> section;
   TRY_TEST(section.CoCreateInstance(CLSID_GeneralSection), S_OK);

   //
   // materials
   //
 
   // concrete
   CComPtr<IUnconfinedConcrete> concrete;
   concrete.CoCreateInstance(CLSID_UnconfinedConcrete);
   CComQIPtr<ISupportUnitServer> sus(concrete);
   sus->putref_UnitServer(unit_server);
   concrete->put_fc(4.0); // 4 KSI concrete

   // rebar
   CComPtr<IRebarModel> rebar;
   rebar.CoCreateInstance(CLSID_RebarModel);
   rebar->Init(60.,29000., 0.11);

   //
   // shapes
   //

   // main beam
   CComPtr<IRectangle> beam;
   beam.CoCreateInstance(CLSID_Rect);
   beam->put_Height(8*12);
   beam->put_Width(4*12);

   // #6 rebar
   CComPtr<ICircle> bar1;
   bar1.CoCreateInstance(CLSID_Circle);
   bar1->put_Radius(0.74848);
   CComPtr<IPoint2d> center;
   bar1->get_Center(&center);
   center->Move(22,46);

   CComPtr<ICircle> bar2;
   bar2.CoCreateInstance(CLSID_Circle);
   bar2->put_Radius(0.74848);
   center.Release();
   bar2->get_Center(&center);
   center->Move(-22,46);

   CComPtr<ICircle> bar3;
   bar3.CoCreateInstance(CLSID_Circle);
   bar3->put_Radius(0.74848);
   center.Release();
   bar3->get_Center(&center);
   center->Move(-22,-46);

   CComPtr<ICircle> bar4;
   bar4.CoCreateInstance(CLSID_Circle);
   bar4->put_Radius(0.74848);
   center.Release();
   bar4->get_Center(&center);
   center->Move( 22,-46);

   CComQIPtr<IShape> shape1(beam);
   CComQIPtr<IShape> shape2(bar1);
   CComQIPtr<IShape> shape3(bar2);
   CComQIPtr<IShape> shape4(bar3);
   CComQIPtr<IShape> shape5(bar4);

   CComQIPtr<IStressStrain> material1(concrete);
   CComQIPtr<IStressStrain> material2(rebar);

   section->AddShape(shape1,material1,NULL,0);
   section->AddShape(shape2,material2,material1,0);
   section->AddShape(shape3,material2,material1,0);
   section->AddShape(shape4,material2,material1,0);
   section->AddShape(shape5,material2,material1,0);


   CComPtr<IMomentCurvatureSolver> solver;
   TRY_TEST(solver.CoCreateInstance(CLSID_MomentCurvatureSolver),S_OK);

   CComPtr<IMomentCurvatureSolution> solution;
   solver->putref_Section(section);
   solver->put_Slices(20);
   solver->Solve(-200,0.00,&solution);

//   TestISupportUnitServer(concrete);
//
//   CComQIPtr<IStressStrain> ss(concrete);
//   TRY_TEST( ss != NULL, true );
//
//   TRY_TEST( ss->ComputeStress(0.00764,NULL), E_POINTER);
//   TRY_TEST( ss->ComputeStress(0.00764,&val), S_OK );
//   TRY_TEST( IsEqual(val,0.00), true );
//   TRY_TEST( ss->ComputeStress(-0.00764,&val), S_OK );
//   TRY_TEST( IsEqual(val,0.00), true );
//   TRY_TEST( ss->ComputeStress(-0.00245,&val), S_OK );
//   TRY_TEST( IsEqual(val,-86277115.), true );
//
//   CComQIPtr<ISupportErrorInfo> eInfo(ss);
//   TRY_TEST( eInfo != NULL, true);
//   TRY_TEST( eInfo->InterfaceSupportsErrorInfo(IID_IUnconfinedConcrete), S_OK);
//   TRY_TEST( eInfo->InterfaceSupportsErrorInfo(IID_IStressStrain),       S_OK);
//   TRY_TEST( eInfo->InterfaceSupportsErrorInfo(IID_IStructuredStorage2), S_OK);
//   TRY_TEST( eInfo->InterfaceSupportsErrorInfo(IID_ISupportErrorInfo),   S_FALSE);
}
