///////////////////////////////////////////////////////////////////////
// RCCapacity Test - Test driver for RCCapacity library
// Copyright © 1999-2024  Washington State Department of Transportation
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

// MomentCapacitySolverTest.cpp: implementation of the CMomentCapacitySolverTest class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MomentCapacitySolverTest.h"
#include "GeneralTests.h"
#include <WBFLUnitServer.h>
#include <Units\Units.h>

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
   hr = unit_server->SetSystemUnits(CComBSTR("12kslug"),CComBSTR("in"),CComBSTR("sec"),CComBSTR("F"),CComBSTR("deg"));
   WBFL::Units::System::SetMassUnit(WBFL::Units::Measure::_12KSlug);
   WBFL::Units::System::SetLengthUnit(WBFL::Units::Measure::Inch);
   WBFL::Units::System::SetTimeUnit(WBFL::Units::Measure::Second);

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
   Float64 Ab = 1.27;
   CComPtr<IPoint2d> center;

   CComPtr<IGenericShape> bar1;
   bar1.CoCreateInstance(CLSID_GenericShape);
   bar1->put_Area(Ab);
   center.Release();
   bar1->get_Centroid(&center);
   center->Move(W/2-2,H/2-2);

   CComPtr<IGenericShape> bar2;
   bar2.CoCreateInstance(CLSID_GenericShape);
   bar2->put_Area(Ab);
   center.Release();
   bar2->get_Centroid(&center);
   center->Move(-(W/2-2),H/2-2);

   CComPtr<IGenericShape> bar3;
   bar3.CoCreateInstance(CLSID_GenericShape);
   bar3->put_Area(Ab);
   center.Release();
   bar3->get_Centroid(&center);
   center->Move(-(W/2-2),-(H/2-2));

   CComPtr<IGenericShape> bar4;
   bar4.CoCreateInstance(CLSID_GenericShape);
   bar4->put_Area(Ab);
   center.Release();
   bar4->get_Centroid(&center);
   center->Move(W/2-2,-(H/2-2));

   CComQIPtr<IShape> shape1(beam);
   CComQIPtr<IShape> shape2(bar1);
   CComQIPtr<IShape> shape3(bar2);
   CComQIPtr<IShape> shape4(bar3);
   CComQIPtr<IShape> shape5(bar4);

   CComQIPtr<IStressStrain> material1(concrete);
   CComQIPtr<IStressStrain> material2(rebar);

   section->AddShape(CComBSTR("Beam"),shape1, material1, nullptr, nullptr, 1.0, VARIANT_TRUE); // beam
   section->AddShape(CComBSTR("Bar 1"), shape2,material2,nullptr, nullptr, 1.0, VARIANT_FALSE); // bar 1
   section->AddShape(CComBSTR("Bar 2"), shape3,material2,nullptr, nullptr, 1.0, VARIANT_FALSE); // bar 2
   section->AddShape(CComBSTR("Bar 3"), shape4,material2,nullptr, nullptr, 1.0, VARIANT_FALSE); // bar 3
   section->AddShape(CComBSTR("Bar 4"), shape5,material2,nullptr, nullptr, 1.0, VARIANT_FALSE); // bar 4


   CComPtr<IMomentCapacitySolver> solver;
   TRY_TEST(solver.CoCreateInstance(CLSID_MomentCapacitySolver),S_OK);

   solver->put_Slices(10);
   solver->put_SliceGrowthFactor(3);
   solver->put_AxialTolerance(0.001);
   solver->putref_Section(section);

   CComPtr<IMomentCapacitySolution> solution;
   TRY_TEST( SUCCEEDED(solver->Solve(0.00,0.00,-0.003,0.0,smFixedCompressionStrain,&solution)), true); // compression top, use angle = 0

   Float64 Fz, Mx, My;
   solution->get_Fz(&Fz);
   solution->get_Mx(&Mx);
   solution->get_My(&My);

   TRY_TEST( IsZero(Fz,0.001), true );
   TRY_TEST( IsEqual(Mx,-6888.22801), true );
   TRY_TEST( IsZero(My), true);

   Float64 c;
   solution->get_DepthToNeutralAxis(&c);
   TRY_TEST(IsEqual(c, 1.852083), true);

   Float64 dc;
   solution->get_DepthToCompressionResultant(&dc);
   TRY_TEST(IsEqual(dc, 0.926042), true);

   Float64 de;
   solution->get_DepthToTensionResultant(&de);
   TRY_TEST(IsEqual(de, 41.433434),true);

   Float64 moment_arm;
   solution->get_MomentArm(&moment_arm);
   TRY_TEST(IsEqual(moment_arm, de - dc), true);

   Float64 k;
   solution->get_Curvature(&k);
   TRY_TEST(IsEqual(k, 0.00161979), true);

   CComPtr<IPlane3d> strainPlane;
   solution->get_IncrementalStrainPlane(&strainPlane);

   Float64 ec;
   strainPlane->GetZ(0.00,H/2,&ec);
   TRY_TEST(IsEqual(ec,-0.003),true);

   solution.Release();

   TRY_TEST( SUCCEEDED(solver->Solve(0.00,M_PI,-0.003, 0.0,smFixedCompressionStrain,&solution)), true); //compression bottom, use angle = M_PI

   solution->get_Fz(&Fz);
   solution->get_Mx(&Mx);
   solution->get_My(&My);
   strainPlane.Release();
   solution->get_IncrementalStrainPlane(&strainPlane);


   TRY_TEST( IsZero(Fz,0.001), true );
   TRY_TEST( IsEqual(Mx, 6888.22801), true );
   TRY_TEST( IsZero(My), true);

   solution->get_DepthToNeutralAxis(&c);
   TRY_TEST(IsEqual(c, 1.852083), true);

   solution->get_DepthToCompressionResultant(&dc);
   TRY_TEST(IsEqual(dc, 0.926042), true);

   solution->get_DepthToTensionResultant(&de);
   TRY_TEST(IsEqual(de, 41.433434), true);

   solution->get_MomentArm(&moment_arm);
   TRY_TEST(IsEqual(moment_arm, de - dc), true);

   solution->get_Curvature(&k);
   TRY_TEST(IsEqual(k, -0.00161979), true);

   strainPlane->GetZ(0.00,-H/2,&ec);
   TRY_TEST(IsEqual(ec,-0.003),true);

   solution.Release();

   TRY_TEST(SUCCEEDED(solver->Solve(0.00, PI_OVER_2, -0.003, 0.0, smFixedCompressionStrain, &solution)), true); //compression left, use angle = PI_OVER_2

   solution->get_Fz(&Fz);
   solution->get_Mx(&Mx);
   solution->get_My(&My);
   strainPlane.Release();
   solution->get_IncrementalStrainPlane(&strainPlane);

   TRY_TEST(IsZero(Fz, 0.001), true);
   TRY_TEST(IsZero(Mx), true);
   TRY_TEST(IsEqual(My, -3374.92488), true);

   solution->get_DepthToNeutralAxis(&c);
   TRY_TEST(IsEqual(c, 1.438523), true);

   solution->get_DepthToCompressionResultant(&dc);
   TRY_TEST(IsEqual(dc, 0.630138), true);

   solution->get_DepthToTensionResultant(&de);
   TRY_TEST(IsEqual(de, 14.77174), true);

   solution->get_MomentArm(&moment_arm);
   TRY_TEST(IsEqual(moment_arm, de - dc), true);

   solution->get_Curvature(&k);
   TRY_TEST(IsEqual(k, 0.00208547), true);

   strainPlane->GetZ(-W / 2, 0.00, &ec);
   TRY_TEST(IsEqual(ec, -0.003), true);

   solution.Release();

   TRY_TEST(SUCCEEDED(solver->Solve(0.00, 3*PI_OVER_2, -0.003, 0.0, smFixedCompressionStrain, &solution)), true); //compression right, use angle = 3*PI_OVER_2

   solution->get_Fz(&Fz);
   solution->get_Mx(&Mx);
   solution->get_My(&My);
   strainPlane.Release();
   solution->get_IncrementalStrainPlane(&strainPlane);

   TRY_TEST(IsZero(Fz, 0.001), true);
   TRY_TEST(IsZero(Mx), true);
   TRY_TEST(IsEqual(My, 3374.92488), true);

   solution->get_DepthToNeutralAxis(&c);
   TRY_TEST(IsEqual(c, 1.438523), true);

   solution->get_DepthToCompressionResultant(&dc);
   TRY_TEST(IsEqual(dc, 0.630138), true);

   solution->get_DepthToTensionResultant(&de);
   TRY_TEST(IsEqual(de, 14.77174), true);

   solution->get_MomentArm(&moment_arm);
   TRY_TEST(IsEqual(moment_arm, de - dc), true);

   solution->get_Curvature(&k);
   TRY_TEST(IsEqual(k, -0.00208547), true);

   strainPlane->GetZ(W / 2, 0.00, &ec);
   TRY_TEST(IsEqual(ec, -0.003), true);

   // make bar3 and bar4 be unbonded for 5 ft
   CComQIPtr<IUnitConvert> convert(unit_server);
   Float64 Le;
   convert->ConvertToBaseUnits(5.0, CComBSTR("ft"), &Le);
   section->put_ElongationLength(3, Le);
   section->put_ElongationLength(4, Le);
   solution.Release();
   TRY_TEST(SUCCEEDED(solver->Solve(0.00, M_PI, -0.003, 0.0, smFixedCompressionStrain, &solution)), true); // compression bottom, use angle = M_PI

   solution->get_Fz(&Fz);
   solution->get_Mx(&Mx);
   solution->get_My(&My);
   strainPlane.Release();
   solution->get_IncrementalStrainPlane(&strainPlane);


   TRY_TEST(IsZero(Fz, 0.001), true);
   TRY_TEST(IsEqual(Mx, 6884.17511, 0.0001), true);
   TRY_TEST(IsZero(My), true);

   solution->get_DepthToNeutralAxis(&c);
   TRY_TEST(IsEqual(c, 1.667856), true);

   solution->get_DepthToCompressionResultant(&dc);
   TRY_TEST(IsEqual(dc, 0.83393), true);

   solution->get_DepthToTensionResultant(&de);
   TRY_TEST(IsEqual(de, 45.78926), true);

   solution->get_MomentArm(&moment_arm);
   TRY_TEST(IsEqual(moment_arm, de - dc), true);

   solution->get_Curvature(&k);
   TRY_TEST(IsEqual(k, -0.0017987), true);

   strainPlane->GetZ(0.00, -H / 2, &ec);
   TRY_TEST(IsEqual(ec, -0.003), true);
}
