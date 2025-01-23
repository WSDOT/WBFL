///////////////////////////////////////////////////////////////////////
// RCCapacity Test - Test driver for RCCapacity library
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

// GeneralSectionSolverTest.cpp: implementation of the CGeneralSectionSolverTest class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GeneralSectionSolverTest.h"
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

CGeneralSectionSolverTest::CGeneralSectionSolverTest()
{

}

CGeneralSectionSolverTest::~CGeneralSectionSolverTest()
{

}

void CGeneralSectionSolverTest::Test()
{
   CHRException hr;

   CComPtr<IUnitServer> unit_server;
   unit_server.CoCreateInstance(CLSID_UnitServer);
   
   // base units of kip and ksi
   hr = unit_server->SetSystemUnits(CComBSTR("12kslug"),CComBSTR("in"),CComBSTR("sec"),CComBSTR("F"),CComBSTR("deg"));

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
   bar1->put_Radius(0.37424);
   CComPtr<IPoint2d> center;
   bar1->get_Center(&center);
   center->Move(22,46);

   CComPtr<ICircle> bar2;
   bar2.CoCreateInstance(CLSID_Circle);
   bar2->put_Radius(0.37424);
   center.Release();
   bar2->get_Center(&center);
   center->Move(-22,46);

   CComPtr<ICircle> bar3;
   bar3.CoCreateInstance(CLSID_Circle);
   bar3->put_Radius(0.37424);
   center.Release();
   bar3->get_Center(&center);
   center->Move(-22,-46);

   CComPtr<ICircle> bar4;
   bar4.CoCreateInstance(CLSID_Circle);
   bar4->put_Radius(0.37424);
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

   section->AddShape(CComBSTR("Beam"), shape1, material1, nullptr, nullptr, 1.0, VARIANT_TRUE); // beam
   section->AddShape(CComBSTR("Bar 1"), shape2, material2, material1, nullptr, 1.0, VARIANT_FALSE); // bar 1
   section->AddShape(CComBSTR("Bar 2"), shape3, material2, material1, nullptr, 1.0, VARIANT_FALSE); // bar 2
   section->AddShape(CComBSTR("Bar 3"), shape4, material2, material1, nullptr, 1.0, VARIANT_FALSE); // bar 3
   section->AddShape(CComBSTR("Bar 4"), shape5, material2, material1, nullptr, 1.0, VARIANT_FALSE); // bar 4


   // setup the stress plan
   CComPtr<IPoint3d> p1, p2, p3;
   p1.CoCreateInstance(CLSID_Point3d);
   p2.CoCreateInstance(CLSID_Point3d);
   p3.CoCreateInstance(CLSID_Point3d);

   // neutral axis
   p1->Move(-1000,0,0);
   p2->Move( 1000,0,0);

   // rotation of section
   p3->Move(0,48,-0.003); // -0.003 at top face of beam

   CComPtr<IPlane3d> strainPlane;
   strainPlane.CoCreateInstance(CLSID_Plane3d);
   strainPlane->ThroughPoints(p1,p2,p3);



   CComPtr<IGeneralSectionSolver> solver;
   TRY_TEST(solver.CoCreateInstance(CLSID_GeneralSectionSolver), S_OK);

   solver->put_Slices(10);
   solver->putref_Section(section);

   CComPtr<IGeneralSectionSolution> solution;
   solver->Solve(strainPlane,&solution);

   Float64 value;
   solution->get_Fz(&value);
   TRY_TEST(IsEqual(value, -6989.5380720604908),true);
   solution->get_Mx(&value);
   TRY_TEST(IsEqual(value, -199028.63168431941), true);
   solution->get_My(&value);
   TRY_TEST(IsEqual(value, 0.0), true);
   solution->get_CompressionResultant(&value);
   TRY_TEST(IsEqual(value, -7042.3377809023850), true);
   solution->get_TensionResultant(&value);
   TRY_TEST(IsEqual(value, 52.799708841892233), true);

#pragma Reminder("************ Finish GeneralSectionSolver tests ****************")

//   CComQIPtr<ISupportErrorInfo> eInfo(ss);
//   TRY_TEST( eInfo != nullptr, true);
//   TRY_TEST( eInfo->InterfaceSupportsErrorInfo(IID_IUnconfinedConcrete), S_OK);
//   TRY_TEST( eInfo->InterfaceSupportsErrorInfo(IID_IStressStrain),       S_OK);
//   TRY_TEST( eInfo->InterfaceSupportsErrorInfo(IID_IStructuredStorage2), S_OK);
//   TRY_TEST( eInfo->InterfaceSupportsErrorInfo(IID_ISupportErrorInfo),   S_FALSE);
}
