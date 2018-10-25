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

// CrackedSectionSolverTest.cpp: implementation of the CCrackedSectionSolverTest class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CrackedSectionSolverTest.h"
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

CCrackedSectionSolverTest::CCrackedSectionSolverTest()
{

}

CCrackedSectionSolverTest::~CCrackedSectionSolverTest()
{

}

void CCrackedSectionSolverTest::Test()
{
   // See the CrackedSectionAnalysis.xlsx spreadsheet for
   // "hand" calculation validation of results
   TestRectangularBeam();
   TestTeeBeam1();
   TestTeeBeam2();
   TestTeeBeam3();
}

void CCrackedSectionSolverTest::TestRectangularBeam()
{
   CHRException hr;

   CComPtr<IUnitServer> unit_server;
   unit_server.CoCreateInstance(CLSID_UnitServer);
   
   // base units of kip and ksi
   hr = unit_server->SetBaseUnits(CComBSTR("12kslug"),CComBSTR("in"),CComBSTR("sec"),CComBSTR("F"),CComBSTR("deg"));
   unitSysUnitsMgr::SetMassUnit(unitMeasure::_12KSlug);
   unitSysUnitsMgr::SetLengthUnit(unitMeasure::Inch);
   unitSysUnitsMgr::SetTimeUnit(unitMeasure::Second);

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
   Float64 H = 100;
   Float64 W = 20;
   CComPtr<IRectangle> beam;
   beam.CoCreateInstance(CLSID_Rect);
   beam->put_Height(H);
   beam->put_Width(W);

   // move bottom center to (0,0)
   CComPtr<IPoint2d> hookPt;
   beam->get_HookPoint(&hookPt);
   hookPt->Move(0,H/2);

   // 4 - #10 rebar @ 2" from bottom
   Float64 radius = sqrt(1.27/M_PI);
   CComPtr<ICircle> bar1;
   bar1.CoCreateInstance(CLSID_Circle);
   bar1->put_Radius(radius);
   CComPtr<IPoint2d> center;
   bar1->get_Center(&center);
   center->Move(0,2);

   CComPtr<ICircle> bar2;
   bar2.CoCreateInstance(CLSID_Circle);
   bar2->put_Radius(radius);
   center.Release();
   bar2->get_Center(&center);
   center->Move(0,2);

   CComPtr<ICircle> bar3;
   bar3.CoCreateInstance(CLSID_Circle);
   bar3->put_Radius(radius);
   center.Release();
   bar3->get_Center(&center);
   center->Move(0,2);

   CComPtr<ICircle> bar4;
   bar4.CoCreateInstance(CLSID_Circle);
   bar4->put_Radius(radius);
   center.Release();
   bar4->get_Center(&center);
   center->Move(0,2);

   CComQIPtr<IShape> shape1(beam);
   CComQIPtr<IShape> shape2(bar1);
   CComQIPtr<IShape> shape3(bar2);
   CComQIPtr<IShape> shape4(bar3);
   CComQIPtr<IShape> shape5(bar4);

   CComQIPtr<IStressStrain> material1(concrete);
   CComQIPtr<IStressStrain> material2(rebar);

   section->AddShape(shape1,material1,nullptr,0); // beam
   section->AddShape(shape2,material2,nullptr,0); // bar 1
   section->AddShape(shape3,material2,nullptr,0); // bar 2
   section->AddShape(shape4,material2,nullptr,0); // bar 3
   section->AddShape(shape5,material2,nullptr,0); // bar 4


   CComPtr<ICrackedSectionSolver> solver;
   TRY_TEST(solver.CoCreateInstance(CLSID_CrackedSectionSolver),S_OK);

   solver->put_Slices(10);
   //solver->put_SliceGrowthFactor(3);
   solver->put_CGTolerance(0.001);
   solver->putref_Section(section);

   CComPtr<ICrackedSectionSolution> solution;
   TRY_TEST( SUCCEEDED(solver->Solve(0,&solution)), true);

   CComPtr<IPoint2d> pntCG;
   solution->get_CG(&pntCG);

   Float64 y;
   pntCG->get_Y(&y);
   TRY_TEST(IsEqual(y,81.755394),true);
}

void CCrackedSectionSolverTest::TestTeeBeam1()
{
   // Tee beam with neutral axis in deck
   CHRException hr;

   CComPtr<IUnitServer> unit_server;
   unit_server.CoCreateInstance(CLSID_UnitServer);
   
   // base units of kip and ksi
   hr = unit_server->SetBaseUnits(CComBSTR("12kslug"),CComBSTR("in"),CComBSTR("sec"),CComBSTR("F"),CComBSTR("deg"));
   unitSysUnitsMgr::SetMassUnit(unitMeasure::_12KSlug);
   unitSysUnitsMgr::SetLengthUnit(unitMeasure::Inch);
   unitSysUnitsMgr::SetTimeUnit(unitMeasure::Second);

   // Get a general section
   CComPtr<IGeneralSection> section;
   TRY_TEST(section.CoCreateInstance(CLSID_GeneralSection), S_OK);

   //
   // materials
   //
 
   // concrete
   CComPtr<IUnconfinedConcrete> slab_concrete;
   slab_concrete.CoCreateInstance(CLSID_UnconfinedConcrete);
   CComQIPtr<ISupportUnitServer> sus_slab(slab_concrete);
   sus_slab->putref_UnitServer(unit_server);
   slab_concrete->put_fc(4.0); // 4 KSI concrete

   CComPtr<IUnconfinedConcrete> beam_concrete;
   beam_concrete.CoCreateInstance(CLSID_UnconfinedConcrete);
   CComQIPtr<ISupportUnitServer> sus_beam(beam_concrete);
   sus_beam->putref_UnitServer(unit_server);
   beam_concrete->put_fc(10.0); // 10 KSI concrete

   // rebar
   CComPtr<IRebarModel> rebar;
   rebar.CoCreateInstance(CLSID_RebarModel);
   rebar->Init(60.,29000., 0.11);

   //
   // shapes
   //

   // slab
   Float64 Wtf = 48;
   Float64 Ttf = 8;
   CComPtr<IRectangle> slab;
   slab.CoCreateInstance(CLSID_Rect);
   slab->put_Height(Ttf);
   slab->put_Width(Wtf);

   // main beam
   Float64 H = 100;
   Float64 W = 20;
   CComPtr<IRectangle> beam;
   beam.CoCreateInstance(CLSID_Rect);
   beam->put_Height(H);
   beam->put_Width(W);

   // move bottom center of beam to (0,0)
   CComQIPtr<IXYPosition> posBeam(beam);
   CComPtr<IPoint2d> pntBC;
   posBeam->get_LocatorPoint(lpBottomCenter,&pntBC);
   pntBC->Move(0,0);
   posBeam->put_LocatorPoint(lpBottomCenter,pntBC);

   // move bottom center of slab to top center of beam
   CComPtr<IPoint2d> pntTC;
   posBeam->get_LocatorPoint(lpTopCenter,&pntTC);

   CComQIPtr<IXYPosition> posSlab(slab);
   posSlab->put_LocatorPoint(lpBottomCenter,pntTC);

   // #10 rebar @ 2" from bottom
   Float64 radius = sqrt(1.27/M_PI);
   CComPtr<ICircle> bar1;
   bar1.CoCreateInstance(CLSID_Circle);
   bar1->put_Radius(radius);
   CComPtr<IPoint2d> center;
   bar1->get_Center(&center);
   center->Move(0,2);

   CComQIPtr<IShape> shape1(slab);
   CComQIPtr<IShape> shape2(beam);
   CComQIPtr<IShape> shape3(bar1);

   CComQIPtr<IStressStrain> material1(slab_concrete);
   CComQIPtr<IStressStrain> material2(beam_concrete);
   CComQIPtr<IStressStrain> material3(rebar);

   section->AddShape(shape1,material1,nullptr,0); // slab
   section->AddShape(shape2,material2,nullptr,0); // beam
   section->AddShape(shape3,material3,nullptr,0); // rebar

   CComPtr<ICrackedSectionSolver> solver;
   TRY_TEST(solver.CoCreateInstance(CLSID_CrackedSectionSolver),S_OK);

   solver->put_Slices(10);
   //solver->put_SliceGrowthFactor(3);
   solver->put_CGTolerance(0.001);
   solver->putref_Section(section);

   CComPtr<ICrackedSectionSolution> solution;
   TRY_TEST( SUCCEEDED(solver->Solve(0,&solution)), true);

   CComPtr<IPoint2d> pntCG;
   solution->get_CG(&pntCG);

   Float64 y;
   pntCG->get_Y(&y);
   TRY_TEST(IsEqual(y,101.425427),true);
}

void CCrackedSectionSolverTest::TestTeeBeam2()
{
   // Tee beam with neutral axis in beam
   CHRException hr;

   CComPtr<IUnitServer> unit_server;
   unit_server.CoCreateInstance(CLSID_UnitServer);
   
   // base units of kip and ksi
   hr = unit_server->SetBaseUnits(CComBSTR("12kslug"),CComBSTR("in"),CComBSTR("sec"),CComBSTR("F"),CComBSTR("deg"));
   unitSysUnitsMgr::SetMassUnit(unitMeasure::_12KSlug);
   unitSysUnitsMgr::SetLengthUnit(unitMeasure::Inch);
   unitSysUnitsMgr::SetTimeUnit(unitMeasure::Second);

   // Get a general section
   CComPtr<IGeneralSection> section;
   TRY_TEST(section.CoCreateInstance(CLSID_GeneralSection), S_OK);

   //
   // materials
   //
 
   // concrete
   CComPtr<IUnconfinedConcrete> slab_concrete;
   slab_concrete.CoCreateInstance(CLSID_UnconfinedConcrete);
   CComQIPtr<ISupportUnitServer> sus_slab(slab_concrete);
   sus_slab->putref_UnitServer(unit_server);
   slab_concrete->put_fc(4.0); // 4 KSI concrete

   CComPtr<IUnconfinedConcrete> beam_concrete;
   beam_concrete.CoCreateInstance(CLSID_UnconfinedConcrete);
   CComQIPtr<ISupportUnitServer> sus_beam(beam_concrete);
   sus_beam->putref_UnitServer(unit_server);
   beam_concrete->put_fc(10.0); // 10 KSI concrete

   // rebar
   CComPtr<IRebarModel> rebar;
   rebar.CoCreateInstance(CLSID_RebarModel);
   rebar->Init(60.,29000., 0.11);

   //
   // shapes
   //

   // slab
   Float64 Wtf = 48;
   Float64 Ttf = 8;
   CComPtr<IRectangle> slab;
   slab.CoCreateInstance(CLSID_Rect);
   slab->put_Height(Ttf);
   slab->put_Width(Wtf);

   // main beam
   Float64 H = 100;
   Float64 W = 20;
   CComPtr<IRectangle> beam;
   beam.CoCreateInstance(CLSID_Rect);
   beam->put_Height(H);
   beam->put_Width(W);

   // move bottom center of beam to (0,0)
   CComQIPtr<IXYPosition> posBeam(beam);
   CComPtr<IPoint2d> pntBC;
   posBeam->get_LocatorPoint(lpBottomCenter,&pntBC);
   pntBC->Move(0,0);
   posBeam->put_LocatorPoint(lpBottomCenter,pntBC);

   // move bottom center of slab to top center of beam
   CComPtr<IPoint2d> pntTC;
   posBeam->get_LocatorPoint(lpTopCenter,&pntTC);

   CComQIPtr<IXYPosition> posSlab(slab);
   posSlab->put_LocatorPoint(lpBottomCenter,pntTC);

   // 100 - #10 rebar @ 2" from bottom
   Float64 radius = sqrt(100*1.27/M_PI);
   CComPtr<ICircle> bar1;
   bar1.CoCreateInstance(CLSID_Circle);
   bar1->put_Radius(radius);
   CComPtr<IPoint2d> center;
   bar1->get_Center(&center);
   center->Move(0,2);

   CComQIPtr<IShape> shape1(slab);
   CComQIPtr<IShape> shape2(beam);
   CComQIPtr<IShape> shape3(bar1);

   CComQIPtr<IStressStrain> material1(slab_concrete);
   CComQIPtr<IStressStrain> material2(beam_concrete);
   CComQIPtr<IStressStrain> material3(rebar);

   section->AddShape(shape1,material1,nullptr,0); // slab
   section->AddShape(shape2,material2,nullptr,0); // beam
   section->AddShape(shape3,material3,nullptr,0); // rebar

   CComPtr<ICrackedSectionSolver> solver;
   TRY_TEST(solver.CoCreateInstance(CLSID_CrackedSectionSolver),S_OK);

   solver->put_Slices(10);
   //solver->put_SliceGrowthFactor(3);
   solver->put_CGTolerance(0.001);
   solver->putref_Section(section);

   CComPtr<ICrackedSectionSolution> solution;
   TRY_TEST( SUCCEEDED(solver->Solve(0,&solution)), true);

   CComPtr<IPoint2d> pntCG;
   solution->get_CG(&pntCG);

   Float64 y;
   pntCG->get_Y(&y);
   TRY_TEST(IsEqual(y,52.15599),true);
}

void CCrackedSectionSolverTest::TestTeeBeam3()
{
   // Tee beam with neutral axis in beam
   CHRException hr;

   CComPtr<IUnitServer> unit_server;
   unit_server.CoCreateInstance(CLSID_UnitServer);
   
   // base units of kip and ksi
   hr = unit_server->SetBaseUnits(CComBSTR("12kslug"),CComBSTR("in"),CComBSTR("sec"),CComBSTR("F"),CComBSTR("deg"));
   unitSysUnitsMgr::SetMassUnit(unitMeasure::_12KSlug);
   unitSysUnitsMgr::SetLengthUnit(unitMeasure::Inch);
   unitSysUnitsMgr::SetTimeUnit(unitMeasure::Second);

   // Get a general section
   CComPtr<IGeneralSection> section;
   TRY_TEST(section.CoCreateInstance(CLSID_GeneralSection), S_OK);

   //
   // materials
   //
 
   // concrete
   CComPtr<IUnconfinedConcrete> slab_concrete;
   slab_concrete.CoCreateInstance(CLSID_UnconfinedConcrete);
   CComQIPtr<ISupportUnitServer> sus_slab(slab_concrete);
   sus_slab->putref_UnitServer(unit_server);
   slab_concrete->put_fc(4.0); // 4 KSI concrete

   CComPtr<IUnconfinedConcrete> beam_concrete;
   beam_concrete.CoCreateInstance(CLSID_UnconfinedConcrete);
   CComQIPtr<ISupportUnitServer> sus_beam(beam_concrete);
   sus_beam->putref_UnitServer(unit_server);
   beam_concrete->put_fc(10.0); // 10 KSI concrete

   // rebar
   CComPtr<IRebarModel> rebar;
   rebar.CoCreateInstance(CLSID_RebarModel);
   rebar->Init(60.,29000., 0.11);

   //
   // shapes
   //

   // slab
   Float64 Wtf = 48;
   Float64 Ttf = 8;
   CComPtr<IRectangle> slab;
   slab.CoCreateInstance(CLSID_Rect);
   slab->put_Height(Ttf);
   slab->put_Width(Wtf);

   // main beam
   Float64 H = 100;
   Float64 W = 20;
   CComPtr<IRectangle> beam;
   beam.CoCreateInstance(CLSID_Rect);
   beam->put_Height(H);
   beam->put_Width(W);

   // move bottom center of beam to (0,0)
   CComQIPtr<IXYPosition> posBeam(beam);
   CComPtr<IPoint2d> pntBC;
   posBeam->get_LocatorPoint(lpBottomCenter,&pntBC);
   pntBC->Move(0,0);
   posBeam->put_LocatorPoint(lpBottomCenter,pntBC);

   // move bottom center of slab to top center of beam
   CComPtr<IPoint2d> pntTC;
   posBeam->get_LocatorPoint(lpTopCenter,&pntTC);

   CComQIPtr<IXYPosition> posSlab(slab);
   posSlab->put_LocatorPoint(lpBottomCenter,pntTC);

   pntTC.Release();
   posSlab->get_LocatorPoint(lpTopCenter,&pntTC);

   // 2 - #10 rebar @ 2" from top
   Float64 radius = sqrt(2*1.27/M_PI);
   CComPtr<ICircle> bar1;
   bar1.CoCreateInstance(CLSID_Circle);
   bar1->put_Radius(radius);
   CComPtr<IPoint2d> center;
   bar1->get_Center(&center);
   Float64 Y;
   pntTC->get_Y(&Y);
   center->Move(0,Y-2);

   CComQIPtr<IShape> shape1(slab);
   CComQIPtr<IShape> shape2(beam);
   CComQIPtr<IShape> shape3(bar1);

   CComQIPtr<IStressStrain> material1(slab_concrete);
   CComQIPtr<IStressStrain> material2(beam_concrete);
   CComQIPtr<IStressStrain> material3(rebar);

   section->AddShape(shape1,material1,nullptr,0); // slab
   section->AddShape(shape2,material2,nullptr,0); // beam
   section->AddShape(shape3,material3,nullptr,0); // rebar

   CComPtr<ICrackedSectionSolver> solver;
   TRY_TEST(solver.CoCreateInstance(CLSID_CrackedSectionSolver),S_OK);

   solver->put_Slices(10);
   //solver->put_SliceGrowthFactor(3);
   solver->put_CGTolerance(0.001);
   solver->putref_Section(section);

   CComPtr<ICrackedSectionSolution> solution;
   TRY_TEST( SUCCEEDED(solver->Solve(M_PI,&solution)), true);

   CComPtr<IPoint2d> pntCG;
   solution->get_CG(&pntCG);

   Float64 y;
   pntCG->get_Y(&y);
   TRY_TEST(IsEqual(y,-11.781458),true);
}
