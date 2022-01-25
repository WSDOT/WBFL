///////////////////////////////////////////////////////////////////////
// RCCapacity Test - Test driver for RCCapacity library
// Copyright © 1999-2021  Washington State Department of Transportation
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

// UHPCMomentCapacityTest.cpp: implementation of the CUHPCMomentCapacityTest class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UHPCMomentCapacityTest.h"
#include "GeneralTests.h"
#include <WBFLUnitServer.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CUHPCMomentCapacityTest::CUHPCMomentCapacityTest()
{

}

CUHPCMomentCapacityTest::~CUHPCMomentCapacityTest()
{

}

void CUHPCMomentCapacityTest::Test()
{
   Test1();
   Test2();
   Test3();
}

void CUHPCMomentCapacityTest::Test1()
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
   CComPtr<IUHPConcrete> concrete;
   concrete.CoCreateInstance(CLSID_UHPConcrete);
   CComQIPtr<ISupportUnitServer> sus(concrete);
   sus->putref_UnitServer(unit_server);
   concrete->put_fc(22.0); // 22 KSI concrete
   concrete->put_ecu(-0.0035);
   concrete->put_ftcr(1.2);
   concrete->put_ftloc(1.2);
   concrete->put_etloc(0.0045);

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

   section->AddShape(CComBSTR("Beam"),  shape1, material1, nullptr, nullptr, 1.0, VARIANT_TRUE); // beam
   section->AddShape(CComBSTR("Bar 1"), shape2, material2, nullptr, nullptr, 1.0, VARIANT_FALSE); // bar 1
   section->AddShape(CComBSTR("Bar 2"), shape3, material2, nullptr, nullptr, 1.0, VARIANT_FALSE); // bar 2
   section->AddShape(CComBSTR("Bar 3"), shape4, material2, nullptr, nullptr, 1.0, VARIANT_FALSE); // bar 3
   section->AddShape(CComBSTR("Bar 4"), shape5, material2, nullptr, nullptr, 1.0, VARIANT_FALSE); // bar 4


   CComPtr<IMomentCapacitySolver> solver;
   TRY_TEST(solver.CoCreateInstance(CLSID_MomentCapacitySolver),S_OK);

   solver->put_Slices(10);
   solver->put_SliceGrowthFactor(3);
   solver->put_AxialTolerance(0.001);
   solver->putref_Section(section);

   // Use strain compatibility analysis to determine moment capacity at the onset of the crack localization strain
   CComPtr<IMomentCapacitySolution> solution;
   Float64 Fz,Mx,My;
   CComPtr<IPlane3d> strainPlane;
   TRY_TEST( SUCCEEDED(solver->Solve(0.00,0.00,0.0045, 0.0,smFixedTensionStrain,&solution)), true); // compression top, use angle = 0

   solution->get_Fz(&Fz);
   solution->get_Mx(&Mx);
   solution->get_My(&My);
   solution->get_StrainPlane(&strainPlane);

   TRY_TEST( IsZero(Fz,0.001), true );
   TRY_TEST( IsEqual(Mx, -30283.59705), true );
   TRY_TEST( IsZero(My), true);

   Float64 ec;
   strainPlane->GetZ(0.00,-H/2,&ec);
   TRY_TEST(IsEqual(ec,0.0045),true);

   // compute curvature
   Float64 k = ec / (H / 2);
   TRY_TEST(IsEqual(k, 0.0045 / (H / 2)), true);

   // Solve again but this time set the strain at the bottom
   solution.Release();
   strainPlane.Release();
   TRY_TEST(SUCCEEDED(solver->Solve(0.00, 0.00, 0.0045, -H/2, smFixedStrain, &solution)), true); // compression top, use angle = 0

   solution->get_Fz(&Fz);
   solution->get_Mx(&Mx);
   solution->get_My(&My);
   solution->get_StrainPlane(&strainPlane);

   TRY_TEST(IsZero(Fz, 0.001), true);
   TRY_TEST(IsEqual(Mx, -30283.5931, 0.0001), true);
   TRY_TEST(IsZero(My), true);

   strainPlane->GetZ(0.00, -H / 2, &ec);
   TRY_TEST(IsEqual(ec, 0.0045), true);

   // compute curvature
   k = ec / (H / 2);
   TRY_TEST(IsEqual(k, 0.0045/(H/2)), true);

   // Solve for concrete crushing
   // this example will have tension strains the the rebar that exceed the fracture limit)
   solution.Release();
   strainPlane.Release();
   TRY_TEST(solver->Solve(0.00, 0.00, -0.0035, 0, smFixedCompressionStrain, &solution), RC_E_MATERIALFAILURE); // compression top, use angle = 0

   solution->get_Fz(&Fz);
   solution->get_Mx(&Mx);
   solution->get_My(&My);
   solution->get_StrainPlane(&strainPlane);

   TRY_TEST(IsZero(Fz, 0.001), true);
   TRY_TEST(IsEqual(Mx, -33164.46646), true); 
   TRY_TEST(IsZero(My), true);

   strainPlane->GetZ(0.00, H / 2, &ec);
   TRY_TEST(IsEqual(ec, -0.0035), true);

   // compute curvature
   k = ec / (H / 2);
   TRY_TEST(IsEqual(k, -0.0035/(H/2)), true);

   // Solve again but this time set the strain at the top
   // this example will have tension strains the the rebar that exceed the fracture limit)
   solution.Release();
   strainPlane.Release();
   TRY_TEST(solver->Solve(0.00, 0.00, -0.0035, H / 2, smFixedStrain, &solution), RC_E_MATERIALFAILURE); // compression top, use angle = 0

   solution->get_Fz(&Fz);
   solution->get_Mx(&Mx);
   solution->get_My(&My);
   solution->get_StrainPlane(&strainPlane);

   TRY_TEST(IsZero(Fz, 0.001), true);
   TRY_TEST(IsEqual(Mx, -33164.46646), true);
   TRY_TEST(IsZero(My), true);

   strainPlane->GetZ(0.00, H / 2, &ec);
   TRY_TEST(IsEqual(ec, -0.0035), true);

   // compute curvature
   k = ec / (H / 2);
   TRY_TEST(IsEqual(k, -0.0035 / (H / 2)), true);
}

void CUHPCMomentCapacityTest::Test2()
{
   // Source: Design Example of a UHPC Girder Bridge with a Conventional Concrete Deck (Graybeal, et.al.)
   // Presented April 5, 2021 to AASHTO T-10

   CHRException hr;

   // base units of kip and ksi
   CComPtr<IUnitServer> unit_server;
   unit_server.CoCreateInstance(CLSID_UnitServer);
   hr = unit_server->SetBaseUnits(CComBSTR("12kslug"), CComBSTR("in"), CComBSTR("sec"), CComBSTR("F"), CComBSTR("deg"));

   // modified MN54 cross section
   CComPtr<INUBeam> beam;
   beam.CoCreateInstance(CLSID_NUBeam);
   beam->put_D1(3.8125);
   beam->put_D2(1.6875);
   beam->put_D3(35.5);
   beam->put_D4(5.5);
   beam->put_D5(7.5);
   beam->put_R1(8);
   beam->put_R2(8);
   beam->put_R3(0);
   beam->put_R4(2);
   beam->put_T(3.5/*6.5*/);
   beam->put_W1(21/*34*/);
   beam->put_W2(27/*30*/);
   //beam->put_C1(0.75);

   Float64 h;
   beam->get_Height(&h);

   CComPtr<IPoint2d> origin;
   origin.CoCreateInstance(CLSID_Point2d);
   //origin->Move(0, 0); // default is at (0,0) so no need to actually move the point

   // put top center of beam at origin
   CComQIPtr<IXYPosition> position(beam);
   position->put_LocatorPoint(lpTopCenter, origin);

   CComQIPtr<IShape> beam_shape(beam);

   // haunch
   CComPtr<IRectangle> haunch;
   haunch.CoCreateInstance(CLSID_Rect);
   haunch->put_Height(1.5);
   haunch->put_Width(21);
   position.Release();
   haunch->get_XYPosition(&position);
   position->put_LocatorPoint(lpBottomCenter, origin);

   CComPtr<IPoint2d> topHaunch;
   position->get_LocatorPoint(lpTopCenter, &topHaunch);

   CComQIPtr<IShape> haunch_shape(haunch);

   // deck
   CComPtr<IRectangle> deck;
   deck.CoCreateInstance(CLSID_Rect);
   deck->put_Height(8.5);
   deck->put_Width(108);
   position.Release();
   deck->get_XYPosition(&position);
   position->put_LocatorPoint(lpBottomCenter, topHaunch);

   CComQIPtr<IShape> deck_shape(deck);

   // strands
   CComPtr<IGenericShape> layer1;
   layer1.CoCreateInstance(CLSID_GenericShape);
   layer1->put_Area(13 * 0.294);
   CComPtr<IPoint2d> pnt1;
   pnt1.CoCreateInstance(CLSID_Point2d);
   pnt1->Move(0.0, -54 + 2); // 54" down from top + up 2" per layer to the center of layer
   layer1->putref_Centroid(pnt1);
   CComQIPtr<IShape> layer1_shape(layer1);

   CComPtr<IGenericShape> layer2;
   layer2.CoCreateInstance(CLSID_GenericShape);
   layer2->put_Area(13 * 0.294);
   CComPtr<IPoint2d> pnt2;
   pnt2.CoCreateInstance(CLSID_Point2d);
   pnt2->Move(0.0, -54 + 4); // 54" down from top + up 2" per layer to the center of layer
   layer2->putref_Centroid(pnt2);
   CComQIPtr<IShape> layer2_shape(layer2);

   CComPtr<IGenericShape> layer3;
   layer3.CoCreateInstance(CLSID_GenericShape);
   layer3->put_Area(13 * 0.294);
   CComPtr<IPoint2d> pnt3;
   pnt3.CoCreateInstance(CLSID_Point2d);
   pnt3->Move(0.0, -54 + 6); // 54" down from top + up 2" per layer to the center of layer
   layer3->putref_Centroid(pnt3);
   CComQIPtr<IShape> layer3_shape(layer3);

   CComPtr<IGenericShape> layer4;
   layer4.CoCreateInstance(CLSID_GenericShape);
   layer4->put_Area(9 * 0.294);
   CComPtr<IPoint2d> pnt4;
   pnt4.CoCreateInstance(CLSID_Point2d);
   pnt4->Move(0.0, -54 + 8); // 54" down from top + up 2" per layer to the center of layer
   layer4->putref_Centroid(pnt4);
   CComQIPtr<IShape> layer4_shape(layer4);

   CComPtr<IGenericShape> layer5;
   layer5.CoCreateInstance(CLSID_GenericShape);
   layer5->put_Area(5 * 0.294);
   CComPtr<IPoint2d> pnt5;
   pnt5.CoCreateInstance(CLSID_Point2d);
   pnt5->Move(0.0, -54 + 10); // 54" down from top + up 2" per layer to the center of layer
   layer5->putref_Centroid(pnt5);
   CComQIPtr<IShape> layer5_shape(layer5);

   CComPtr<IGenericShape> layer6;
   layer6.CoCreateInstance(CLSID_GenericShape);
   layer6->put_Area(1 * 0.294);
   CComPtr<IPoint2d> pnt6;
   pnt6.CoCreateInstance(CLSID_Point2d);
   pnt6->Move(0.0, -54 + 12); // 54" down from top + up 2" per layer to the center of layer
   layer6->putref_Centroid(pnt6);
   CComQIPtr<IShape> layer6_shape(layer6);

   //CComPtr<IGenericShape> layer7;
   //layer7.CoCreateInstance(CLSID_GenericShape);
   //layer7->put_Area(2 * 0.294);
   //CComPtr<IPoint2d> pnt7;
   //pnt7.CoCreateInstance(CLSID_Point2d);
   //pnt7->Move(0.0, -2); // 2" down from top
   //layer7->putref_Centroid(pnt7);
   //CComQIPtr<IShape> layer7_shape(layer7);

   //
   // materials
   //

   // deck
   CComPtr<IUnconfinedConcrete> deck_concrete;
   deck_concrete.CoCreateInstance(CLSID_UnconfinedConcrete);
   CComQIPtr<ISupportUnitServer> sus(deck_concrete);
   sus->putref_UnitServer(unit_server);
   deck_concrete->put_fc(4.0); // 4 KSI concrete
   CComQIPtr<IStressStrain> ss_deck_concrete(deck_concrete);

   // girder
   CComPtr<IUHPConcrete> girder_concrete;
   girder_concrete.CoCreateInstance(CLSID_UHPConcrete);
   sus.Release();
   girder_concrete.QueryInterface(&sus);
   sus->putref_UnitServer(unit_server);
   girder_concrete->put_fc(22.0); // 22 KSI concrete
   girder_concrete->put_ecu(-0.0035);
   girder_concrete->put_ftcr(1.2);
   girder_concrete->put_ftloc(1.2);
   girder_concrete->put_etloc(0.0045);
   CComQIPtr<IStressStrain> ss_girder_concrete(girder_concrete);

   // strand
   CComPtr<IPowerFormula> strand;
   strand.CoCreateInstance(CLSID_PSPowerFormula);
   strand->put_Grade(sgtGrade270);
   strand->put_ProductionMethod(pmtLowRelaxation);

   sus.Release();
   strand.QueryInterface(&sus);
   sus->putref_UnitServer(unit_server);

   CComQIPtr<IStressStrain> ss_strand(strand);
   Float64 ei = 166.2 / 28500; // fps = 166.2 ksi at Service III
   CComPtr<IPlane3d> initialStrain;
   initialStrain.CoCreateInstance(CLSID_Plane3d);
   initialStrain->ThroughAltitude(ei);

   // Get a general section
   CComPtr<IGeneralSection> section;
   TRY_TEST(section.CoCreateInstance(CLSID_GeneralSection), S_OK);

   section->AddShape(CComBSTR("Deck"),deck_shape, ss_deck_concrete, nullptr, nullptr, 1.0, VARIANT_FALSE);
   section->AddShape(CComBSTR("Haunch"),haunch_shape, ss_deck_concrete, nullptr, nullptr, 1.0, VARIANT_FALSE);
   section->AddShape(CComBSTR("Girder"),beam_shape, ss_girder_concrete, nullptr, nullptr, 1.0, VARIANT_TRUE);
   section->AddShape(CComBSTR("Strand Layer 1"), layer1_shape, ss_strand, nullptr, initialStrain, 1.0, VARIANT_FALSE);
   section->AddShape(CComBSTR("Strand Layer 2"), layer2_shape, ss_strand, nullptr, initialStrain, 1.0, VARIANT_FALSE);
   section->AddShape(CComBSTR("Strand Layer 3"), layer3_shape, ss_strand, nullptr, initialStrain, 1.0, VARIANT_FALSE);
   section->AddShape(CComBSTR("Strand Layer 4"), layer4_shape, ss_strand, nullptr, initialStrain, 1.0, VARIANT_FALSE);
   section->AddShape(CComBSTR("Strand Layer 5"), layer5_shape, ss_strand, nullptr, initialStrain, 1.0, VARIANT_FALSE);
   section->AddShape(CComBSTR("Strand Layer 6"), layer6_shape, ss_strand, nullptr, initialStrain, 1.0, VARIANT_FALSE);
   //section->AddShape(CComBSTR("Strand Layer 7"), layer7_shape, ss_strand, nullptr, initialStrain, 1.0, VARIANT_FALSE);


   CComPtr<IMomentCapacitySolver> solver;
   TRY_TEST(solver.CoCreateInstance(CLSID_MomentCapacitySolver), S_OK);

   solver->put_Slices(50);
   solver->put_SliceGrowthFactor(1);
   solver->put_AxialTolerance(0.0001);
   solver->putref_Section(section);

   // Compute nominal capacity when the stress in the bottom layer of reinforcement is equal to 0.80fy
   // Msl and Ysl
   Float64 fu = 270;
   Float64 fy = 0.9*fu;
   Float64 esl = 0.8*fy / 27931;// 28500;
   position.Release();
   layer1->get_XYPosition(&position);
   CComPtr<IPoint2d> center;
   position->get_LocatorPoint(lpCenterCenter, &center);
   Float64 Y;
   center->get_Y(&Y);

   CComPtr<IMomentCapacitySolution> solution;
   TRY_TEST(SUCCEEDED(solver->Solve(0.00, 0.00, esl-ei, Y, smFixedStrain, &solution)), true);
   //std::cout << "Nominal moment when stress in bottom layer of strand is equal to 0.80fy, Msl" << std::endl;
   //DumpSolution(section,solution);

   Float64 Fz, Mx, My;
   CComPtr<IPlane3d> strainPlane;
   solution->get_Fz(&Fz);
   solution->get_Mx(&Mx);
   solution->get_My(&My);
   solution->get_StrainPlane(&strainPlane);

   TRY_TEST(IsZero(Fz, 0.001), true);
   TRY_TEST(IsEqual(Mx, -178123.6634, 0.0001), true); //-164292.0 (13691 k-ft) from FHWA example slides
   TRY_TEST(IsZero(My), true);
   Float64 Msl = -Mx;

   Float64 ec;
   strainPlane->GetZ(0.00, Y, &ec);
   TRY_TEST(IsEqual(ec, esl-ei), true);

   Float64 Yna;
   strainPlane->GetY(0.0, 0.0, &Yna); // location of neutral axis below top of girder
   TRY_TEST(IsEqual(Yna, -20.58941), true); // 40.7-10" = 30.7" from top of girder from FHWN example slides

   strainPlane->GetZ(0.00, -54, &ec); // strain at bottom of girder
   Float64 Ysl = ec/(54+Yna); // curvature
   TRY_TEST(IsEqual(Ysl, .000035925, 0.00000001), true); // 0.0000545 from FHWA example slides

   // Nominal moment capacity at crack localization, Ml and Yl
   solution.Release();
   TRY_TEST(SUCCEEDED(solver->Solve(0.00, 0.00, 0.0045, 0.0, smFixedTensionStrain, &solution)), true);
   //std::cout << "Nominal moment at crack localization, Ml" << std::endl;
   //DumpSolution(section,solution);

   strainPlane.Release();
   solution->get_Fz(&Fz);
   solution->get_Mx(&Mx);
   solution->get_My(&My);
   solution->get_StrainPlane(&strainPlane);

   TRY_TEST(IsZero(Fz, 0.001), true);
   TRY_TEST(IsEqual(Mx, -222618.3053, 0.0001), true); // -215664.0 (17972 k-ft) from FHWA example slides
   TRY_TEST(IsZero(My), true);
   Float64 Ml = -Mx;

   strainPlane->GetZ(0.00, -h, &ec);
   TRY_TEST(IsEqual(ec, 0.0045), true);

   strainPlane->GetY(0.0, 0.0, &Yna); // location of neutral axis below top of girder
   TRY_TEST(IsEqual(Yna, -10.00682), true); // 25.5-10" = 15.5" from top of girder from FHWN example slides

   Float64 Yl = ec/(54+Yna);
   TRY_TEST(IsEqual(Yl, 0.0001022885, 0.00000001), true); // 0.0001167 from FHWN example slides

   // Nominal moment capacity at compression strain limit in UHPC section, Mc, Yc
   // fixed strain at top of girder (not top of section/top of deck)
   solution.Release();
   TRY_TEST(solver->Solve(0.00, 0.00, -0.0035, 0.0, smFixedStrain, &solution), RC_E_MATERIALFAILURE);  // strain in deck concrete exceeds crushing limit of -0.003
   //std::cout << "Nominal moment at compression strain limit in UHPC section, Mc" << std::endl;
   //DumpSolution(section,solution);

   strainPlane.Release();
   solution->get_Fz(&Fz);
   solution->get_Mx(&Mx);
   solution->get_My(&My);
   solution->get_StrainPlane(&strainPlane);

   TRY_TEST(IsZero(Fz, 0.001), true);
   TRY_TEST(IsEqual(Mx, -212455.97339), true);
   TRY_TEST(IsZero(My), true);
   Float64 Mc = -Mx;

   strainPlane->GetZ(0.00, 10.00, &ec); // strain at top of deck
   TRY_TEST(IsEqual(ec, -0.005491), true);

   strainPlane->GetZ(0.00, -h, &ec); // strain at bottom of beam
   TRY_TEST(IsEqual(ec, 0.0072523), true);

   strainPlane->GetZ(0.00, 0.00, &ec);
   TRY_TEST(IsEqual(ec, -0.0035), true);

   strainPlane->GetY(0.0, 0.0, &Yna); // location of neutral axis
   TRY_TEST(IsEqual(Yna, -17.57766), true); 

   Float64 Yc = ec / Yna;
   TRY_TEST(IsEqual(Yc, 0.0001991163, 0.000000001), true);

   // Nominal moment capacity at compression strain limit in deck, Md, Yd
   solution.Release();
   TRY_TEST(solver->Solve(0.00, 0.00, -0.003, 0.0, smFixedCompressionStrain, &solution), RC_E_MATERIALFAILURE); // exceeds tensile capacity of UHPC
   //std::cout << "Nominal moment at compression strain limit in deck, Md" << std::endl;
   //DumpSolution(section,solution);

   strainPlane.Release();
   solution->get_Fz(&Fz);
   solution->get_Mx(&Mx);
   solution->get_My(&My);
   solution->get_StrainPlane(&strainPlane);

   TRY_TEST(IsZero(Fz, 0.001), true);
   TRY_TEST(IsEqual(Mx, -228894.0802, 0.0001), true);
   TRY_TEST(IsZero(My), true);
   Float64 Md = -Mx;

   strainPlane->GetZ(0.00, 10.0, &ec);
   TRY_TEST(IsEqual(ec, -0.003), true);

   strainPlane->GetY(0.0, 0.0, &Yna); // location of neutral axis
   TRY_TEST(IsEqual(Yna, -9.73137), true);

   Float64 Yd = ec /(Yna - 10);
   TRY_TEST(IsEqual(Yd, 0.000152042, 0.000000001), true);

   // Nominal moment capacity at maximum usable strain of reinforcement, Mt, Yt
   solution.Release();
   TRY_TEST(solver->Solve(0.00, 0.00, 0.035 - ei, Y, smFixedStrain, &solution), RC_E_MATERIALFAILURE); // strain exceeds crushing strain of UHPC
   //std::cout << "Nominal moment at maximum usable strain in reinforcement, Mt" << std::endl;
   //DumpSolution(section,solution);

   strainPlane.Release();
   solution->get_Fz(&Fz);
   solution->get_Mx(&Mx);
   solution->get_My(&My);
   solution->get_StrainPlane(&strainPlane);

   TRY_TEST(IsZero(Fz, 0.001), true);
   TRY_TEST(IsEqual(Mx, -160306.7804, 0.0001), true);
   TRY_TEST(IsZero(My), true);
   Float64 Mt = -Mx;

   strainPlane->GetZ(0.00, Y, &ec);
   TRY_TEST(IsEqual(ec, 0.035 - ei), true);

   strainPlane->GetY(0.0, 0.0, &Yna); // location of neutral axis
   TRY_TEST(IsEqual(Yna, -40.37118), true);

   Float64 Yt = ec /(Yna - Y);
   TRY_TEST(IsEqual(Yt, 0.00250828766, 0.000000001), true);

   // Ductility ratio
   IndexType i = MinIndex(fabs(Yl), fabs(Yc), fabs(Yd), fabs(Yt)); // want least curvature
   Float64 Mn = (i == 0 ? Ml : i == 1 ? Mc : i == 2 ? Md : Mt);
   Float64 Yn = (i == 0 ? Yl : i == 1 ? Yc : i == 2 ? Yd : Yt);
   Float64 mu = Yn / Ysl;
   TRY_TEST(IsEqual(mu, 2.8473, 0.0001),true); // 2.14 from FHWA example slides

   Float64 phi = 0.75 + 0.15*(mu - 1.0) / (3.0 - 1.0);
   phi = ::ForceIntoRange(0.75, phi, 0.90);
   TRY_TEST(IsEqual(phi, 0.8885, 0.0001), true); // 0.83 from FHWA example slides
   //Float64 Mr = phi*Mn;
}

void CUHPCMomentCapacityTest::Test3()
{
   // Source: Design Example of a UHPC Girder Bridge with a Conventional Concrete Deck (Graybeal, et.al.)
   // Presented April 5, 2021 to AASHTO T-10

   CHRException hr;

   // base units of kip and ksi
   CComPtr<IUnitServer> unit_server;
   unit_server.CoCreateInstance(CLSID_UnitServer);
   hr = unit_server->SetBaseUnits(CComBSTR("12kslug"), CComBSTR("in"), CComBSTR("sec"), CComBSTR("F"), CComBSTR("deg"));

   // modified MN54 cross section
   CComPtr<INUBeam> beam;
   beam.CoCreateInstance(CLSID_NUBeam);
   beam->put_D1(3.8125);
   beam->put_D2(1.6875);
   beam->put_D3(35.5);
   beam->put_D4(5.5);
   beam->put_D5(7.5);
   beam->put_R1(8);
   beam->put_R2(8);
   beam->put_R3(0);
   beam->put_R4(2);
   beam->put_T(3.5/*6.5*/);
   beam->put_W1(21/*34*/);
   beam->put_W2(27/*30*/);
   //beam->put_C1(0.75);

   Float64 h;
   beam->get_Height(&h);

   CComPtr<IPoint2d> origin;
   origin.CoCreateInstance(CLSID_Point2d);
   //origin->Move(0, 0); // default is at (0,0) so no need to actually move the point

   // put top center of beam at origin
   CComQIPtr<IXYPosition> position(beam);
   position->put_LocatorPoint(lpTopCenter, origin);

   CComQIPtr<IShape> beam_shape(beam);

   // haunch
   CComPtr<IRectangle> haunch;
   haunch.CoCreateInstance(CLSID_Rect);
   haunch->put_Height(1.5);
   haunch->put_Width(21);
   position.Release();
   haunch->get_XYPosition(&position);
   position->put_LocatorPoint(lpBottomCenter, origin);

   CComPtr<IPoint2d> topHaunch;
   position->get_LocatorPoint(lpTopCenter, &topHaunch);

   CComQIPtr<IShape> haunch_shape(haunch);

   // deck
   CComPtr<IRectangle> deck;
   deck.CoCreateInstance(CLSID_Rect);
   deck->put_Height(8.5);
   deck->put_Width(108);
   position.Release();
   deck->get_XYPosition(&position);
   position->put_LocatorPoint(lpBottomCenter, topHaunch);

   CComQIPtr<IShape> deck_shape(deck);

   // strands
   CComPtr<IGenericShape> layer1;
   layer1.CoCreateInstance(CLSID_GenericShape);
   layer1->put_Area(13 * 0.294);
   CComPtr<IPoint2d> pnt1;
   pnt1.CoCreateInstance(CLSID_Point2d);
   pnt1->Move(0.0, -h + 2); // 54" down from top + up 2" per layer to the center of layer
   layer1->putref_Centroid(pnt1);
   CComQIPtr<IShape> layer1_shape(layer1);

   CComPtr<IGenericShape> layer2;
   layer2.CoCreateInstance(CLSID_GenericShape);
   layer2->put_Area(13 * 0.294);
   CComPtr<IPoint2d> pnt2;
   pnt2.CoCreateInstance(CLSID_Point2d);
   pnt2->Move(0.0, -h + 4); // 54" down from top + up 2" per layer to the center of layer
   layer2->putref_Centroid(pnt2);
   CComQIPtr<IShape> layer2_shape(layer2);

   CComPtr<IGenericShape> layer3;
   layer3.CoCreateInstance(CLSID_GenericShape);
   layer3->put_Area(13 * 0.294);
   CComPtr<IPoint2d> pnt3;
   pnt3.CoCreateInstance(CLSID_Point2d);
   pnt3->Move(0.0, -h + 6); // 54" down from top + up 2" per layer to the center of layer
   layer3->putref_Centroid(pnt3);
   CComQIPtr<IShape> layer3_shape(layer3);

   CComPtr<IGenericShape> layer4;
   layer4.CoCreateInstance(CLSID_GenericShape);
   layer4->put_Area(9 * 0.294);
   CComPtr<IPoint2d> pnt4;
   pnt4.CoCreateInstance(CLSID_Point2d);
   pnt4->Move(0.0, -h + 8); // 54" down from top + up 2" per layer to the center of layer
   layer4->putref_Centroid(pnt4);
   CComQIPtr<IShape> layer4_shape(layer4);

   CComPtr<IGenericShape> layer5;
   layer5.CoCreateInstance(CLSID_GenericShape);
   layer5->put_Area(5 * 0.294);
   CComPtr<IPoint2d> pnt5;
   pnt5.CoCreateInstance(CLSID_Point2d);
   pnt5->Move(0.0, -h + 10); // 54" down from top + up 2" per layer to the center of layer
   layer5->putref_Centroid(pnt5);
   CComQIPtr<IShape> layer5_shape(layer5);

   CComPtr<IGenericShape> layer6;
   layer6.CoCreateInstance(CLSID_GenericShape);
   layer6->put_Area(1 * 0.294);
   CComPtr<IPoint2d> pnt6;
   pnt6.CoCreateInstance(CLSID_Point2d);
   pnt6->Move(0.0, -h + 12); // 54" down from top + up 2" per layer to the center of layer
   layer6->putref_Centroid(pnt6);
   CComQIPtr<IShape> layer6_shape(layer6);

   // This reinforcement neglected in capacity analysis
   //CComPtr<IGenericShape> layer7;
   //layer7.CoCreateInstance(CLSID_GenericShape);
   //layer7->put_Area(2 * 0.294);
   //CComPtr<IPoint2d> pnt7;
   //pnt7.CoCreateInstance(CLSID_Point2d);
   //pnt7->Move(0.0, -2); // 2" down from top
   //layer7->putref_Centroid(pnt7);
   //CComQIPtr<IShape> layer7_shape(layer7);

   //
   // materials
   //

   // deck
   CComPtr<IUnconfinedConcrete> deck_concrete;
   deck_concrete.CoCreateInstance(CLSID_UnconfinedConcrete);
   CComQIPtr<ISupportUnitServer> sus(deck_concrete);
   sus->putref_UnitServer(unit_server);
   deck_concrete->put_fc(4.0); // 4 KSI concrete
   CComQIPtr<IStressStrain> ss_deck_concrete(deck_concrete);

   // girder
   CComPtr<IUHPConcrete> girder_concrete;
   girder_concrete.CoCreateInstance(CLSID_UHPConcrete);
   sus.Release();
   girder_concrete.QueryInterface(&sus);
   sus->putref_UnitServer(unit_server);
   girder_concrete->put_fc(22.0); // 22 KSI concrete
   girder_concrete->put_ecu(-0.0035);
   girder_concrete->put_ftcr(1.2);
   girder_concrete->put_ftloc(1.2);
   girder_concrete->put_etloc(0.0045);
   CComQIPtr<IStressStrain> ss_girder_concrete(girder_concrete);

   // strand
   CComPtr<IPowerFormula> strand;
   strand.CoCreateInstance(CLSID_PSPowerFormula);
   strand->put_Grade(sgtGrade270);
   strand->put_ProductionMethod(pmtLowRelaxation);

   sus.Release();
   strand.QueryInterface(&sus);
   sus->putref_UnitServer(unit_server);
   CComQIPtr<IStressStrain> ss_strand(strand);

   // Initial Strains
   CComPtr<IPoint3d> p1, p2, p3; // use three points to define a plane

   // Deck
   CComPtr<IPlane3d> deck_initial_strain;
   deck_initial_strain.CoCreateInstance(CLSID_Plane3d);
   p1.CoCreateInstance(CLSID_Point3d);
   p2.CoCreateInstance(CLSID_Point3d);
   p3.CoCreateInstance(CLSID_Point3d);
   // 4 ksi conventional concrete, E = 2500*f'c^0.33 = 3950 ksi
   p3->Move(0, 10, -1.33/3950); // 1.33 ksi compression at top of deck at Service III (see slide 33)
   p1->Move(-10000, 0, -0.88/3950); // 0.88 ksi compression bottom of deck at Service III (see slide 33)
   p2->Move(10000, 0, -0.88 / 3950);
   deck_initial_strain->ThroughPoints(p1, p2, p3);

   // Girder
   CComPtr<IPlane3d> girder_initial_strain;
   girder_initial_strain.CoCreateInstance(CLSID_Plane3d);
   p1.Release(); p2.Release(); p3.Release();
   p1.CoCreateInstance(CLSID_Point3d);
   p2.CoCreateInstance(CLSID_Point3d);
   p3.CoCreateInstance(CLSID_Point3d);
   p1->Move(-10000, 0, -11.02/6933); // 11.02 ksi compression at top of girder at Service III (see slide 33)
   p2->Move(10000, 0, -11.02 / 6933);
   p3->Move(0, -h, 0.99/6933); // 0.99 ksi tension at bottom of girder at Service III (see slide 33)
   girder_initial_strain->ThroughPoints(p1, p2, p3);

   Float64 ei = 166.2 / 28500; // fps = 166.2 ksi at Service III (see slide 33)
   CComPtr<IPlane3d> strand_initial_strain;
   strand_initial_strain.CoCreateInstance(CLSID_Plane3d);
   strand_initial_strain->ThroughAltitude(ei);

   // Get a general section
   CComPtr<IGeneralSection> section;
   TRY_TEST(section.CoCreateInstance(CLSID_GeneralSection), S_OK);

   section->AddShape(CComBSTR("Deck"), deck_shape, ss_deck_concrete, nullptr, deck_initial_strain, 1.0, VARIANT_FALSE);
   section->AddShape(CComBSTR("Haunch"), haunch_shape, ss_deck_concrete, nullptr, deck_initial_strain, 1.0, VARIANT_FALSE);
   section->AddShape(CComBSTR("Girder"), beam_shape, ss_girder_concrete, nullptr, girder_initial_strain, 1.0, VARIANT_TRUE);
   section->AddShape(CComBSTR("Strand Layer 1"), layer1_shape, ss_strand, nullptr, strand_initial_strain, 1.0, VARIANT_FALSE);
   section->AddShape(CComBSTR("Strand Layer 2"), layer2_shape, ss_strand, nullptr, strand_initial_strain, 1.0, VARIANT_FALSE);
   section->AddShape(CComBSTR("Strand Layer 3"), layer3_shape, ss_strand, nullptr, strand_initial_strain, 1.0, VARIANT_FALSE);
   section->AddShape(CComBSTR("Strand Layer 4"), layer4_shape, ss_strand, nullptr, strand_initial_strain, 1.0, VARIANT_FALSE);
   section->AddShape(CComBSTR("Strand Layer 5"), layer5_shape, ss_strand, nullptr, strand_initial_strain, 1.0, VARIANT_FALSE);
   section->AddShape(CComBSTR("Strand Layer 6"), layer6_shape, ss_strand, nullptr, strand_initial_strain, 1.0, VARIANT_FALSE);
   //section->AddShape(CComBSTR("Strand Layer 7"), layer7_shape, ss_strand, nullptr, strand_initial_strain, 1.0, VARIANT_FALSE);


   CComPtr<IMomentCapacitySolver> solver;
   TRY_TEST(solver.CoCreateInstance(CLSID_MomentCapacitySolver), S_OK);

   solver->put_Slices(50);
   solver->put_SliceGrowthFactor(1);
   solver->put_AxialTolerance(0.0001);
   solver->putref_Section(section);

   // Compute nominal capacity when the stress in the bottom layer of reinforcement is equal to 0.80fy (slide 50)
   // Msl and Ysl
   Float64 fu = 270;
   Float64 fy = 0.9 * fu;
   Float64 esl = 0.8 * fy / 28500;
   position.Release();
   layer1->get_XYPosition(&position);
   CComPtr<IPoint2d> center;
   position->get_LocatorPoint(lpCenterCenter, &center);
   Float64 Y;
   center->get_Y(&Y);

   CComPtr<IMomentCapacitySolution> solution;
   TRY_TEST(SUCCEEDED(solver->Solve(0.00, 0.00, esl - ei, Y, smFixedStrain, &solution)), true);
   //std::cout << "Nominal moment when stress in bottom layer of strand is equal to 0.80fy, Msl" << std::endl;
   //DumpSolution(section,solution);

   Float64 Fz, Mx, My;
   CComPtr<IPlane3d> strainPlane;
   solution->get_Fz(&Fz);
   solution->get_Mx(&Mx);
   solution->get_My(&My);
   solution->get_StrainPlane(&strainPlane);

   TRY_TEST(IsZero(Fz, 0.001), true);
   TRY_TEST(IsEqual(Mx, -161496.2591 /*13458 k-ft*/, 0.0001), true); //-164292.0 = 13691 k-ft from FHWA example slides
   TRY_TEST(IsZero(My), true);
   Float64 Msl = -Mx;

   Float64 ec;
   strainPlane->GetZ(0.00, Y, &ec); // strain in girder concrete
   Float64 _ec;
   girder_initial_strain->GetZ(0, Y, &_ec); // initial strain in girder concrete
   TRY_TEST(IsEqual(ec - _ec, esl - ei), true);

   CComPtr<IGeneralSectionSolution> general_solution;
   solution->get_GeneralSectionSolution(&general_solution);
   CComPtr<IUnkArray> slices;
   general_solution->FindSlices(3, &slices); // shape 3 is the lowest strand
   IndexType nSlices;
   slices->get_Count(&nSlices);
   TRY_TEST(nSlices, 1);
   CComPtr<IUnknown> punk;
   slices->get_Item(0, &punk);
   CComQIPtr<IGeneralSectionSlice> slice(punk);
   slice->get_TotalStrain(&ec);
   TRY_TEST(IsEqual(ec, esl), true);

   Float64 Yna;
   strainPlane->GetY(0.0, 0.0, &Yna); // location of neutral axis below top of girder
   TRY_TEST(IsEqual(Yna, -31.85653), true); // 40.7-10" = 30.7" from top of girder from FHWN example slides

   strainPlane->GetZ(0.00, -h, &ec); // strain at bottom of girder
   TRY_TEST(IsEqual(ec, 0.00117416, 0.00000001), true); // 0.00127 from FHWA example slides

   Float64 Ysl = ec / (h + Yna); // curvature
   TRY_TEST(IsEqual(Ysl, 0.00005302513, 0.00000001), true); // 0.0000545 from FHWA example slides

   // Nominal moment capacity at crack localization, Ml and Yl (slide 51)
   solution.Release();
   TRY_TEST(SUCCEEDED(solver->Solve(0.00, 0.00, 0.0045 - 0.99 / 6933, 0.0, smFixedTensionStrain, &solution)), true);
   //std::cout << "Nominal moment at crack localization, Ml" << std::endl;
   //DumpSolution(section, solution);

   strainPlane.Release();
   solution->get_Fz(&Fz);
   solution->get_Mx(&Mx);
   solution->get_My(&My);
   solution->get_StrainPlane(&strainPlane);

   TRY_TEST(IsZero(Fz, 0.001), true);
   TRY_TEST(IsEqual(Mx, -215602.84328 /*17966.9 k-ft*/), true); // -215664.0 = 17972 k-ft from FHWA example slides
   TRY_TEST(IsZero(My), true);
   Float64 Ml = -Mx;

   strainPlane->GetZ(0.00, -h, &ec);
   TRY_TEST(IsEqual(ec, 0.0045), true);

   strainPlane->GetY(0.0, 0.0, &Yna); // location of neutral axis below top of girder
   TRY_TEST(IsEqual(Yna, -15.61227), true); // 25.5-10" = 15.5" from top of girder from FHWN example slides

   Float64 Yl = ec / (h + Yna);
   TRY_TEST(IsEqual(Yl, 0.00011722496, 0.00000001), true); // 0.0001167 from FHWN example slides

   // Nominal moment capacity at compression strain limit in UHPC section, Mc, Yc
   // fixed strain at top of girder (not top of section/top of deck)
   // this case not in FHWA example
   solution.Release();
   TRY_TEST(solver->Solve(0.00, 0.00, -0.0035 + 11.02 / 6933, 0.0, smFixedStrain, &solution), RC_E_MATERIALFAILURE);  // strain in deck concrete exceeds crushing limit of -0.003
   //std::cout << "Nominal moment at compression strain limit in UHPC section, Mc" << std::endl;
   //DumpSolution(section,solution);

   strainPlane.Release();
   solution->get_Fz(&Fz);
   solution->get_Mx(&Mx);
   solution->get_My(&My);
   solution->get_StrainPlane(&strainPlane);

   TRY_TEST(IsZero(Fz, 0.001), true);
   TRY_TEST(IsEqual(Mx, -225237.6749, 0.0001), true);
   TRY_TEST(IsZero(My), true);
   Float64 Mc = -Mx;

   strainPlane->GetZ(0.00, 10.00, &ec); // strain at top of deck
   TRY_TEST(IsEqual(ec, -0.006621228), true);

   strainPlane->GetZ(0.00, -h, &ec); // strain at bottom of beam
   TRY_TEST(IsEqual(ec, 0.01335463), true);

   strainPlane->GetZ(0.00, 0.00, &ec);
   TRY_TEST(IsEqual(ec, -0.0035), true);

   strainPlane->GetY(0.0, 0.0, &Yna); // location of neutral axis
   TRY_TEST(IsEqual(Yna, -11.213537), true);

   Float64 Yc = ec / Yna;
   TRY_TEST(IsEqual(Yc, 0.000312123, 0.000000001), true);

   // Nominal moment capacity at compression strain limit in deck, Md, Yd
   // this case not in FHWA example
   solution.Release();
   TRY_TEST(solver->Solve(0.00, 0.00, -0.003 + 1.33 / 3950, 0.0, smFixedCompressionStrain, &solution), RC_E_MATERIALFAILURE); // exceeds tensile capacity of UHPC
   //std::cout << "Nominal moment at compression strain limit in deck, Md" << std::endl;
   //DumpSolution(section,solution);

   strainPlane.Release();
   solution->get_Fz(&Fz);
   solution->get_Mx(&Mx);
   solution->get_My(&My);
   solution->get_StrainPlane(&strainPlane);

   TRY_TEST(IsZero(Fz, 0.001), true);
   TRY_TEST(IsEqual(Mx, -234918.2945, 0.0001), true);
   TRY_TEST(IsZero(My), true);
   Float64 Md = -Mx;

   strainPlane->GetZ(0.00, 10.0, &ec); // this is at top of deck, using girder strain plane
   girder_initial_strain->GetZ(0, 10.0, &_ec); // initial strain in girder concrete
   ec -= _ec; // remove effect of girder initial strain
   deck_initial_strain->GetZ(0, 10., &_ec);
   ec += _ec; // add effect of deck initial strain
   TRY_TEST(IsEqual(ec, -0.003), true);


   strainPlane->GetY(0.0, 0.0, &Yna); // location of neutral axis
   TRY_TEST(IsEqual(Yna, -8.029146), true);

   Float64 Yd = ec / (Yna - 10);
   TRY_TEST(IsEqual(Yd, 0.000166397, 0.000000001), true);

   // Nominal moment capacity at maximum usable strain of reinforcement, Mt, Yt
   // this case not in FHWA example
   solution.Release();
   TRY_TEST(solver->Solve(0.00, 0.00, 0.035 - ei, Y, smFixedStrain, &solution), RC_E_MATERIALFAILURE); // strain exceeds crushing strain of UHPC
   //std::cout << "Nominal moment at maximum usable strain in reinforcement, Mt" << std::endl;
   //DumpSolution(section,solution);

   strainPlane.Release();
   solution->get_Fz(&Fz);
   solution->get_Mx(&Mx);
   solution->get_My(&My);
   solution->get_StrainPlane(&strainPlane);

   TRY_TEST(IsZero(Fz, 0.001), true);
   TRY_TEST(IsEqual(Mx, -160319.2836, 0.0001), true);
   TRY_TEST(IsZero(My), true);
   Float64 Mt = -Mx;

   strainPlane->GetZ(0.00, Y, &ec); // strain in girder concrete
   girder_initial_strain->GetZ(0, Y, &_ec); // initial strain in girder concrete
   TRY_TEST(IsEqual(ec - _ec, 0.035 - ei), true);

   general_solution.Release();
   solution->get_GeneralSectionSolution(&general_solution);
   slices.Release();
   general_solution->FindSlices(3, &slices); // shape 3 is the lowest strand
   slices->get_Count(&nSlices);
   TRY_TEST(nSlices, 1);
   punk.Release();
   slices->get_Item(0, &punk);
   slice.Release();
   punk.QueryInterface(&slice);
   slice->get_TotalStrain(&ec);
   TRY_TEST(IsEqual(ec, 0.035), true);

   strainPlane->GetY(0.0, 0.0, &Yna); // location of neutral axis
   TRY_TEST(IsEqual(Yna, -40.39915), true);

   Float64 Yt = ec / (Yna - Y);
   TRY_TEST(IsEqual(Yt, 0.003017021, 0.000000001), true);

   // Ductility ratio
   IndexType i = MinIndex(fabs(Yl), fabs(Yc), fabs(Yd), fabs(Yt)); // want least curvature
   Float64 Mn = (i == 0 ? Ml : i == 1 ? Mc : i == 2 ? Md : Mt);
   Float64 Yn = (i == 0 ? Yl : i == 1 ? Yc : i == 2 ? Yd : Yt);
   Float64 mu = Yn / Ysl;
   TRY_TEST(IsEqual(mu, 2.2107, 0.0001), true); // 2.14 from FHWA example slides

   Float64 phi = 0.75 + 0.15 * (mu - 1.0) / (3.0 - 1.0);
   phi = ::ForceIntoRange(0.75, phi, 0.90);
   TRY_TEST(IsEqual(phi, 0.8408, 0.0001), true); // 0.83 from FHWA example
   //Float64 Mr = phi*Mn;
}