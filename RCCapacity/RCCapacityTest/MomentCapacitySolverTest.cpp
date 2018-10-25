///////////////////////////////////////////////////////////////////////
// RCCapacity Test - Test driver for RCCapacity library
// Copyright © 2009  Washington State Department of Transportation
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

// MomentCapacitySolverTest.cpp: implementation of the CMomentCapacitySolverTest class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MomentCapacitySolverTest.h"
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

CMomentCapacitySolverTest::CMomentCapacitySolverTest()
{

}

CMomentCapacitySolverTest::~CMomentCapacitySolverTest()
{

}

void CMomentCapacitySolverTest::Test()
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
   Float64 H = 4*12;
   Float64 W = 2*12;
   CComPtr<IRectangle> beam;
   beam.CoCreateInstance(CLSID_Rect);
   beam->put_Height(H);
   beam->put_Width(W);

   // #10 rebar
   Float64 radius = sqrt(1.27/M_PI);
   CComPtr<ICircle> bar1;
   bar1.CoCreateInstance(CLSID_Circle);
   bar1->put_Radius(radius);
   CComPtr<IPoint2d> center;
   bar1->get_Center(&center);
   center->Move(W/2-2,H/2-2);

   CComPtr<ICircle> bar2;
   bar2.CoCreateInstance(CLSID_Circle);
   bar2->put_Radius(radius);
   center.Release();
   bar2->get_Center(&center);
   center->Move(-(W/2-2),H/2-2);

   CComPtr<ICircle> bar3;
   bar3.CoCreateInstance(CLSID_Circle);
   bar3->put_Radius(radius);
   center.Release();
   bar3->get_Center(&center);
   center->Move(-(W/2-2),-(H/2-2));

   CComPtr<ICircle> bar4;
   bar4.CoCreateInstance(CLSID_Circle);
   bar4->put_Radius(radius);
   center.Release();
   bar4->get_Center(&center);
   center->Move(W/2-2,-(H/2-2));

   CComQIPtr<IShape> shape1(beam);
   CComQIPtr<IShape> shape2(bar1);
   CComQIPtr<IShape> shape3(bar2);
   CComQIPtr<IShape> shape4(bar3);
   CComQIPtr<IShape> shape5(bar4);

   CComQIPtr<IStressStrain> material1(concrete);
   CComQIPtr<IStressStrain> material2(rebar);

   section->AddShape(shape1,material1,NULL,0); // beam
   section->AddShape(shape2,material2,NULL,0); // bar 1
   section->AddShape(shape3,material2,NULL,0); // bar 2
   section->AddShape(shape4,material2,NULL,0); // bar 3
   section->AddShape(shape5,material2,NULL,0); // bar 4


   CComPtr<IMomentCapacitySolver> solver;
   TRY_TEST(solver.CoCreateInstance(CLSID_MomentCapacitySolver),S_OK);

   solver->put_Slices(10);
   solver->put_SliceGrowthFactor(3);
   solver->put_AxialTolerance(0.001);
   solver->putref_Section(section);

   CComPtr<IMomentCapacitySolution> solution;
   Float64 Fz,Mx,My;
   CComPtr<IPlane3d> strainPlane;
   TRY_TEST( SUCCEEDED(solver->Solve(0.00,0.00,-0.003,smFixedCompressiveStrain,&solution)), true);

   solution->get_Fz(&Fz);
   solution->get_Mx(&Mx);
   solution->get_My(&My);
   solution->get_StrainPlane(&strainPlane);

   TRY_TEST( IsZero(Fz,0.001), true );
   TRY_TEST( IsEqual(Mx,-6898.02750), true );
   TRY_TEST( IsZero(My), true);

   Float64 ec;
   strainPlane->GetZ(0.00,H/2,&ec);
   TRY_TEST(IsEqual(ec,-0.003),true);

   solution.Release();
   TRY_TEST( SUCCEEDED(solver->Solve(0.00,M_PI,-0.003,smFixedCompressiveStrain,&solution)), true);

   solution->get_Fz(&Fz);
   solution->get_Mx(&Mx);
   solution->get_My(&My);
   strainPlane.Release();
   solution->get_StrainPlane(&strainPlane);


   TRY_TEST( IsZero(Fz,0.001), true );
   TRY_TEST( IsEqual(Mx, 6898.02750), true );
   TRY_TEST( IsZero(My), true);

   strainPlane->GetZ(0.00,-H/2,&ec);
   TRY_TEST(IsEqual(ec,-0.003),true);

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
