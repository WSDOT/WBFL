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

void DumpSolution(IMomentCapacitySolution* solution)
{
   USES_CONVERSION;
   CComPtr<IGeneralSectionSolution> general_solution;
   solution->get_GeneralSectionSolution(&general_solution);
   IndexType nSlices;
   general_solution->get_SliceCount(&nSlices);
   std::cout << "Material, Top, Bottom, Area, Ycg, strain, stress, force, moment" << std::endl;
   for (IndexType sliceIdx = 0; sliceIdx < nSlices; sliceIdx++)
   {
      CComPtr<IGeneralSectionSlice> slice;
      general_solution->get_Slice(sliceIdx, &slice);
      Float64 area;
      CComPtr<IPoint2d> cg;
      Float64 strain;
      Float64 fgStress;
      slice->get_Area(&area);
      slice->get_CG(&cg);
      slice->get_Strain(&strain);
      slice->get_ForegroundStress(&fgStress);

      CComPtr<IStressStrain> ss;
      slice->get_ForegroundMaterial(&ss);
      CComBSTR bstrName;
      ss->get_Name(&bstrName);

      Float64 y;
      cg->get_Y(&y);

      CComPtr<IShape> shape;
      slice->get_Shape(&shape);
      CComPtr<IRect2d> rect;
      shape->get_BoundingBox(&rect);
      Float64 top, bottom;
      rect->get_Top(&top);
      rect->get_Bottom(&bottom);

      std::cout << OLE2A(bstrName) << ", " << top << ", " << bottom << ", " << area << ", " << y << ", " << strain << ", " << fgStress << ", " << area*fgStress << ", " << area*fgStress*y << std::endl;
   }
}

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

   section->AddShape(shape1,material1,nullptr,0, 1.0); // beam
   section->AddShape(shape2,material2,nullptr,0, 1.0); // bar 1
   section->AddShape(shape3,material2,nullptr,0, 1.0); // bar 2
   section->AddShape(shape4,material2,nullptr,0, 1.0); // bar 3
   section->AddShape(shape5,material2,nullptr,0, 1.0); // bar 4


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
   TRY_TEST( IsEqual(Mx, -30283.5931, 0.0001), true );
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
   TRY_TEST(IsEqual(Mx, -7176.3798, 0.0001), true); 
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
   TRY_TEST(IsEqual(Mx, -7176.3798, 0.0001), true);
   TRY_TEST(IsZero(My), true);

   strainPlane->GetZ(0.00, H / 2, &ec);
   TRY_TEST(IsEqual(ec, -0.0035), true);

   // compute curvature
   k = ec / (H / 2);
   TRY_TEST(IsEqual(k, -0.0035 / (H / 2)), true);
}

void CUHPCMomentCapacityTest::Test2()
{
   // Source: FHWA UHPC design example (Graybeal, et.al.)

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
   CComPtr<IRectangle> layer1;
   layer1.CoCreateInstance(CLSID_Rect);
   layer1->put_Height(0.7); // 0.7" diameter strand
   layer1->put_Width(13 * 0.294 / 0.7); // 13-0.7" diameter strands, Area = (13*0.294), Equivalent width rectangle, W = Area/Height
   position.Release();
   layer1->get_XYPosition(&position);
   CComPtr<IPoint2d> pnt1;
   pnt1.CoCreateInstance(CLSID_Point2d);
   pnt1->Move(0.0, -54 + 2); // 54" down from top + up 2" per layer to the center of layer
   position->put_LocatorPoint(lpCenterCenter, pnt1);
   CComQIPtr<IShape> layer1_shape(layer1);

   CComPtr<IRectangle> layer2;
   layer2.CoCreateInstance(CLSID_Rect);
   layer2->put_Height(0.7); // 0.7" diameter strand
   layer2->put_Width(13 * 0.294 / 0.7); // 13-0.7" diameter strands, Area = (13*0.294), Equivalent width rectangle, W = Area/Height
   position.Release();
   layer2->get_XYPosition(&position);
   CComPtr<IPoint2d> pnt2;
   pnt2.CoCreateInstance(CLSID_Point2d);
   pnt2->Move(0.0, -54 + 4); // 54" down from top + up 2" per layer to the center of layer
   position->put_LocatorPoint(lpCenterCenter, pnt2);
   CComQIPtr<IShape> layer2_shape(layer2);

   CComPtr<IRectangle> layer3;
   layer3.CoCreateInstance(CLSID_Rect);
   layer3->put_Height(0.7); // 0.7" diameter strand
   layer3->put_Width(13 * 0.294 / 0.7); // 13-0.7" diameter strands, Area = (13*0.294), Equivalent width rectangle, W = Area/Height
   position.Release();
   layer3->get_XYPosition(&position);
   CComPtr<IPoint2d> pnt3;
   pnt3.CoCreateInstance(CLSID_Point2d);
   pnt3->Move(0.0, -54 + 6); // 54" down from top + up 2" per layer to the center of layer
   position->put_LocatorPoint(lpCenterCenter, pnt3);
   CComQIPtr<IShape> layer3_shape(layer3);

   CComPtr<IRectangle> layer4;
   layer4.CoCreateInstance(CLSID_Rect);
   layer4->put_Height(0.7); // 0.7" diameter strand
   layer4->put_Width(9 * 0.294 / 0.7); // 9-0.7" diameter strands, Area = (9*0.294), Equivalent width rectangle, W = Area/Height
   position.Release();
   layer4->get_XYPosition(&position);
   CComPtr<IPoint2d> pnt4;
   pnt4.CoCreateInstance(CLSID_Point2d);
   pnt4->Move(0.0, -54 + 8); // 54" down from top + up 2" per layer to the center of layer
   position->put_LocatorPoint(lpCenterCenter, pnt4);
   CComQIPtr<IShape> layer4_shape(layer4);

   CComPtr<IRectangle> layer5;
   layer5.CoCreateInstance(CLSID_Rect);
   layer5->put_Height(0.7); // 0.7" diameter strand
   layer5->put_Width(5 * 0.294 / 0.7); // 5-0.7" diameter strands, Area = (5*0.294), Equivalent width rectangle, W = Area/Height
   position.Release();
   layer5->get_XYPosition(&position);
   CComPtr<IPoint2d> pnt5;
   pnt5.CoCreateInstance(CLSID_Point2d);
   pnt5->Move(0.0, -54 + 10); // 54" down from top + up 2" per layer to the center of layer
   position->put_LocatorPoint(lpCenterCenter, pnt5);
   CComQIPtr<IShape> layer5_shape(layer5);

   CComPtr<IRectangle> layer6;
   layer6.CoCreateInstance(CLSID_Rect);
   layer6->put_Height(0.7); // 0.7" diameter strand
   layer6->put_Width(1 * 0.294 / 0.7); // 1-0.7" diameter strands, Area = (1*0.294), Equivalent width rectangle, W = Area/Height
   position.Release();
   layer6->get_XYPosition(&position);
   CComPtr<IPoint2d> pnt6;
   pnt6.CoCreateInstance(CLSID_Point2d);
   pnt6->Move(0.0, -54 + 12); // 54" down from top + up 2" per layer to the center of layer
   position->put_LocatorPoint(lpCenterCenter, pnt6);
   CComQIPtr<IShape> layer6_shape(layer6);

   CComPtr<IRectangle> layer7; // top strands
   layer7.CoCreateInstance(CLSID_Rect);
   layer7->put_Height(0.7); // 0.7" diameter strand
   layer7->put_Width(2 * 0.294 / 0.7); // 2-0.7" diameter strands, Area = (2*0.294), Equivalent width rectangle, W = Area/Height
   position.Release();
   layer7->get_XYPosition(&position);
   CComPtr<IPoint2d> pnt7;
   pnt7.CoCreateInstance(CLSID_Point2d);
   pnt7->Move(0.0, -2); // Down 2" from top
   position->put_LocatorPoint(lpCenterCenter, pnt7);
   CComQIPtr<IShape> layer7_shape(layer7);

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
   Float64 ei = (1-0.28)*202.5 / 28500; // initial strain in strand at time of ultimate (assumes 28% prestress loss)

   // Get a general section
   CComPtr<IGeneralSection> section;
   TRY_TEST(section.CoCreateInstance(CLSID_GeneralSection), S_OK);

   section->AddShape(deck_shape, ss_deck_concrete, nullptr, 0, 1.0);
   section->AddShape(haunch_shape, ss_deck_concrete, nullptr, 0, 1.0);
   section->AddShape(beam_shape, ss_girder_concrete, nullptr, 0, 1.0);
   section->AddShape(layer1_shape, ss_strand, nullptr, ei, 1.0);
   section->AddShape(layer2_shape, ss_strand, nullptr, ei, 1.0);
   section->AddShape(layer3_shape, ss_strand, nullptr, ei, 1.0);
   section->AddShape(layer4_shape, ss_strand, nullptr, ei, 1.0);
   section->AddShape(layer5_shape, ss_strand, nullptr, ei, 1.0);
   section->AddShape(layer6_shape, ss_strand, nullptr, ei, 1.0);
   section->AddShape(layer7_shape, ss_strand, nullptr, ei, 1.0);


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
   //DumpSolution(solution);

   Float64 Fz, Mx, My;
   CComPtr<IPlane3d> strainPlane;
   solution->get_Fz(&Fz);
   solution->get_Mx(&Mx);
   solution->get_My(&My);
   solution->get_StrainPlane(&strainPlane);

   TRY_TEST(IsZero(Fz, 0.001), true);
   TRY_TEST(IsEqual(Mx, -179588.7248, 0.0001), true); //-164292.0 from FHWA example slides
   TRY_TEST(IsZero(My), true);
   Float64 Msl = -Mx;

   Float64 ec;
   strainPlane->GetZ(0.00, Y, &ec);
   TRY_TEST(IsEqual(ec, esl-ei), true);

   Float64 Yna;
   strainPlane->GetY(0.0, 0.0, &Yna); // location of neutral axis below top of girder

   strainPlane->GetZ(0.00, -54, &ec); // strain at bottom of girder
   Float64 Ysl = ec/(54+Yna); // curvature
   TRY_TEST(IsEqual(Ysl, 0.00004974, 0.00000001), true); // 0.0000545 from FHWA example slides

   // Nominal moment capacity at crack localization, Ml and Yl
   solution.Release();
   TRY_TEST(SUCCEEDED(solver->Solve(0.00, 0.00, 0.0045, 0.0, smFixedTensionStrain, &solution)), true);
   //std::cout << "Nominal moment at crack localization, Ml" << std::endl;
   //DumpSolution(solution);

   strainPlane.Release();
   solution->get_Fz(&Fz);
   solution->get_Mx(&Mx);
   solution->get_My(&My);
   solution->get_StrainPlane(&strainPlane);

   TRY_TEST(IsZero(Fz, 0.001), true);
   TRY_TEST(IsEqual(Mx, -217001.2506, 0.0001), true); // -215664.0 from FHWA example slides
   TRY_TEST(IsZero(My), true);
   Float64 Ml = -Mx;

   strainPlane->GetZ(0.00, -h, &ec);
   TRY_TEST(IsEqual(ec, 0.0045), true);

   strainPlane->GetY(0.0, 0.0, &Yna); // location of neutral axis below top of girder
   Float64 Yl = ec/(54+Yna);
   TRY_TEST(IsEqual(Yl, 0.000101739, 0.00000001), true); // 0.0001167 from FHWN example slides

   // Nominal moment capacity at compression strain limit in UHPC section, Mc, Yc
   // fixed strain at top of girder (not top of section/top of deck)
   solution.Release();
   TRY_TEST(solver->Solve(0.00, 0.00, -0.0035, 0.0, smFixedStrain, &solution), RC_E_MATERIALFAILURE);  // strain in deck concrete exceeds crushing limit of -0.003
   //std::cout << "Nominal moment at compression strain limit in UHPC section, Mc" << std::endl;
   //DumpSolution(solution);

   strainPlane.Release();
   solution->get_Fz(&Fz);
   solution->get_Mx(&Mx);
   solution->get_My(&My);
   solution->get_StrainPlane(&strainPlane);

   TRY_TEST(IsZero(Fz, 0.001), true);
   TRY_TEST(IsEqual(Mx, -199994.7691, 0.0001), true);
   TRY_TEST(IsZero(My), true);
   Float64 Mc = -Mx;

   strainPlane->GetZ(0.00, 10.00, &ec); // strain at top of deck
   TRY_TEST(IsEqual(ec, -0.00585), true);

   strainPlane->GetZ(0.00, -h, &ec); // strain at bottom of beam
   TRY_TEST(IsEqual(ec, 0.00915), true);

   strainPlane->GetZ(0.00, 0.00, &ec);
   TRY_TEST(IsEqual(ec, -0.0035), true);

   strainPlane->GetY(0.0, 0.0, &Yna); // location of neutral axis
   Float64 Yc = ec / Yna;
   TRY_TEST(IsEqual(Yc, 0.000234168, 0.000000001), true);

   // Nominal moment capacity at compression strain limit in deck, Md, Yd
   solution.Release();
   TRY_TEST(SUCCEEDED(solver->Solve(0.00, 0.00, -0.003, 0.0, smFixedCompressionStrain, &solution)), true);
   //std::cout << "Nominal moment at compression strain limit in deck, Md" << std::endl;
   //DumpSolution(solution);

   strainPlane.Release();
   solution->get_Fz(&Fz);
   solution->get_Mx(&Mx);
   solution->get_My(&My);
   solution->get_StrainPlane(&strainPlane);

   TRY_TEST(IsZero(Fz, 0.001), true);
   TRY_TEST(IsEqual(Mx, -215727.6056, 0.0001), true);
   TRY_TEST(IsZero(My), true);
   Float64 Md = -Mx;

   strainPlane->GetZ(0.00, 10.0, &ec);
   TRY_TEST(IsEqual(ec, -0.003), true);

   strainPlane->GetY(0.0, 0.0, &Yna); // location of neutral axis
   Float64 Yd = ec /(Yna - 10);
   TRY_TEST(IsEqual(Yd, 0.000172448, 0.000000001), true);

   // Nominal moment capacity at maximum usable strain of reinforcement, Mt, Yt
   solution.Release();
   TRY_TEST(solver->Solve(0.00, 0.00, 0.035 - ei, Y, smFixedStrain, &solution), RC_E_MATERIALFAILURE); // strain exceeds crushing strain of UHPC
   //std::cout << "Nominal moment at maximum usable strain in reinforcement, Mt" << std::endl;
   //DumpSolution(solution);

   strainPlane.Release();
   solution->get_Fz(&Fz);
   solution->get_Mx(&Mx);
   solution->get_My(&My);
   solution->get_StrainPlane(&strainPlane);

   TRY_TEST(IsZero(Fz, 0.001), true);
   TRY_TEST(IsEqual(Mx, -16889.8559, 0.0001), true);
   TRY_TEST(IsZero(My), true);
   Float64 Mt = -Mx;

   strainPlane->GetZ(0.00, Y, &ec);
   TRY_TEST(IsEqual(ec, 0.035 - ei), true);

   strainPlane->GetY(0.0, 0.0, &Yna); // location of neutral axis
   Float64 Yt = ec /(Yna - Y);
   TRY_TEST(IsEqual(Yt, 0.010211144, 0.000000001), true);

   // Ductility ratio
   IndexType i = MinIndex(fabs(Yl), fabs(Yc), fabs(Yd), fabs(Yt)); // want least curvature
   Float64 Mn = (i == 0 ? Ml : i == 1 ? Mc : i == 2 ? Md : Mt);
   Float64 Yn = (i == 0 ? Yl : i == 1 ? Yc : i == 2 ? Yd : Yt);
   Float64 mu = Yn / Ysl;
   TRY_TEST(IsEqual(mu, 2.0453, 0.0001),true); // 2.14 from FHWA example slids

   Float64 phi = 0.75 + 0.15*(mu - 1.0) / (3.0 - 1.0);
   phi = ::ForceIntoRange(0.75, phi, 0.90);
   TRY_TEST(IsEqual(phi, 0.8284, 0.0001), true);
   //Float64 Mr = phi*Mn;
}