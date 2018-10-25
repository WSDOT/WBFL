///////////////////////////////////////////////////////////////////////
// RCCapacity Test - Test driver for RCCapacity library
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

// SolverTest.cpp: implementation of the CSolverTest class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SolverTest.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSolverTest::CSolverTest()
{

}

CSolverTest::~CSolverTest()
{

}

void CSolverTest::Test()
{
   CSolverTest::Test1();
   CSolverTest::Test2();
}

void CSolverTest::Test1()
{
   CHRException hr;

   CComPtr<IRCBeam> beam;
   hr = beam.CoCreateInstance(CLSID_RCBeam);

   CComQIPtr<ISupportUnitServer> sus(beam);
   CComPtr<IUnitServer> unitServer;
   hr = sus->get_UnitServer(&unitServer);

   CComPtr<IUnitConvert> convert;
   hr = unitServer->get_UnitConvert(&convert);

   Float64 Aps = 4.0; // in^2
   hr = convert->ConvertToBaseUnits(Aps,CComBSTR("in^2"),&Aps);
   hr = beam->put_Aps(Aps);


   CComPtr<IRCSolution> solution;

   CComPtr<INLSolver> nlSolver;
   hr = nlSolver.CoCreateInstance(CLSID_NLSolver);
   hr = nlSolver->Solve(beam,&solution);
   CheckSolution(solution,0.12497372600349774,7677643.9373881808,4804079.3449505707,0,0.052849056589320931,0,4804079.3444824815,1861584469.1559,VARIANT_FALSE);

   solution.Release();

   CComPtr<IPCISolver> pciSolver;
   hr = pciSolver.CoCreateInstance(CLSID_PCISolver);
   hr = pciSolver->Solve(beam,&solution);
   CheckSolution(solution,0.13183391003435302,7662365.2579992665,4804079.3444734057,0.0,0.056029411764600030,0.0,4804079.3444824815,1861584469.1559000,VARIANT_FALSE);

   solution.Release();

   CComPtr<ILRFDSolver> lrfdSolver;
   hr = lrfdSolver.CoCreateInstance(CLSID_LRFDSolver);
   hr = lrfdSolver->Solve(beam,&solution);
   CheckSolution(solution,0.12895079406405,7500552.4763888,4699017.4686854,0,0.054804087477219,0,4699017.4686854,1820872910.8614,VARIANT_FALSE);

   solution.Release();

   CComPtr<ILRFDSolver2> lrfdSolver2;
   hr = lrfdSolver2.CoCreateInstance(CLSID_LRFDSolver2);
   hr = lrfdSolver2->Solve(beam,&solution);
   CheckSolution(solution,0.12928927678176022,7519562.9114392512,4711351.9115628917,0,0.054947942632248094,0,4711351.9115664093,1825652517.0370178,VARIANT_FALSE);

   solution.Release();

   CComPtr<ILFDSolver> lfdSolver;
   hr = lfdSolver.CoCreateInstance(CLSID_LFDSolver);
   hr = lfdSolver->Solve(beam,&solution);
   CheckSolution(solution,0.12932846921042,7521763.8732139,4712780.0990217,0,0.054964599414426,0,4712780.0990217,1826205940.7828,VARIANT_FALSE);

   solution.Release();

   CComPtr<IMixedSolver> mixedSolver;
   hr = mixedSolver.CoCreateInstance(CLSID_MixedSolver);
   hr = mixedSolver->Solve(beam,&solution);
   CheckSolution(solution,0.12895079406405,7500552.4763888,4699017.4686854,0,0.054804087477219,0,4699017.4686854,1820872910.8614,VARIANT_FALSE);

   hr = convert->ConvertToBaseUnits(8.0,CComBSTR("in^2"),&Aps);
   hr = beam->put_Aps(Aps);

   solution.Release();
   hr = nlSolver->Solve(beam,&solution);
   CheckSolution(solution,0.58342741152486988,13412665.600382978,6864785.9459429123,1947480.2789649768,0.078479091530920808,0.30688052599000359,8812266.2247003336,1707379995.7956812,VARIANT_FALSE);

   solution.Release();
   hr = pciSolver->Solve(beam,&solution);
   CheckSolution(solution,0.61594128172794,13176985.396502,6533547.9084962,2180934.7612839,0.076200000000000,0.32681818517927,8714482.6697877,1688434394.1402,VARIANT_FALSE);

   solution.Release();
   hr = lrfdSolver->Solve(beam,&solution);
   CheckSolution(solution,0.96812146197817,10860413.604265,-1.0000000000000,-1.0000000000000,-1.0000000000000,-1.0000000000000,-1.0000000000000,1555935065.2764,VARIANT_TRUE);

   solution.Release();
   hr = lfdSolver->Solve(beam,&solution);
   CheckSolution(solution,1.0715173871518,12275155.400631,-1.0000000000000,-1.0000000000000,-1.0000000000000,-1.0000000000000,-1.0000000000000,1790827412.4097,VARIANT_TRUE);

   solution.Release();
   hr = mixedSolver->Solve(beam,&solution);
   CheckSolution(solution,0.77559535769964,12275155.400631,-1.0000000000000,-1.0000000000000,-1.0000000000000,-1.0000000000000,-1.0000000000000,1616718232.7973,VARIANT_TRUE);

   hr = beam->put_Aps(0.0); // No reinforcement, no capacity

   solution.Release();
   hr = nlSolver->Solve(beam,&solution);
   CheckSolution(solution,0,0,0,0,0,0,0,0,VARIANT_FALSE);

   solution.Release();
   hr = pciSolver->Solve(beam,&solution);
   CheckSolution(solution,0,0,0,0,0,0,0,0,VARIANT_FALSE);

   solution.Release();
   hr = lrfdSolver->Solve(beam,&solution);
   CheckSolution(solution,0,0,0,0,0,0,0,0,VARIANT_FALSE);

   solution.Release();
   hr = lfdSolver->Solve(beam,&solution);
   CheckSolution(solution,0,0,0,0,0,0,0,0,VARIANT_FALSE);

   solution.Release();
   hr = mixedSolver->Solve(beam,&solution);
   CheckSolution(solution,0,0,0,0,0,0,0,0,VARIANT_FALSE);
}

void CSolverTest::Test2()
{
   CHRException hr;

   CComPtr<IRCBeam2Ex> beam;
   hr = beam.CoCreateInstance(CLSID_RCBeam2Ex);

   CComQIPtr<ISupportUnitServer> sus(beam);
   CComPtr<IUnitServer> unitServer;
   hr = sus->get_UnitServer(&unitServer);

   CComPtr<IUnitConvert> convert;
   hr = unitServer->get_UnitConvert(&convert);

   Float64 b = 72;
   hr = convert->ConvertToBaseUnits(b,CComBSTR("in"),&b);
   beam->put_b(b);

   Float64 hf = 6;
   hr = convert->ConvertToBaseUnits(hf,CComBSTR("in"),&hf);
   beam->put_hf(hf);

   CComPtr<IPrecastBeam> beamShape;
   hr = beamShape.CoCreateInstance(CLSID_PrecastBeam);

   // WSDOT W74G girder
   Float64 W1 = 16.5;
   Float64 W2 = 2;
   Float64 W3 = 9.5;
   Float64 W4 = 0;
   Float64 D1 = 2.875;
   Float64 D2 = 2.625;
   Float64 D3 = 2;
   Float64 D4 = 6;
   Float64 D5 = 3;
   Float64 D6 = 0;
   Float64 D7 = 73.5 - 2.875 - 2.625 - 6 - 3;
   Float64 T1 = 6;
   Float64 T2 = 6;
   hr = convert->ConvertToBaseUnits(W1,CComBSTR("in"),&W1);
   hr = convert->ConvertToBaseUnits(W2,CComBSTR("in"),&W2);
   hr = convert->ConvertToBaseUnits(W3,CComBSTR("in"),&W3);
   hr = convert->ConvertToBaseUnits(W4,CComBSTR("in"),&W4);
   hr = convert->ConvertToBaseUnits(D1,CComBSTR("in"),&D1);
   hr = convert->ConvertToBaseUnits(D2,CComBSTR("in"),&D2);
   hr = convert->ConvertToBaseUnits(D3,CComBSTR("in"),&D3);
   hr = convert->ConvertToBaseUnits(D4,CComBSTR("in"),&D4);
   hr = convert->ConvertToBaseUnits(D5,CComBSTR("in"),&D5);
   hr = convert->ConvertToBaseUnits(D6,CComBSTR("in"),&D6);
   hr = convert->ConvertToBaseUnits(D7,CComBSTR("in"),&D7);
   hr = convert->ConvertToBaseUnits(T1,CComBSTR("in"),&T1);
   hr = convert->ConvertToBaseUnits(T2,CComBSTR("in"),&T2);
   hr = beamShape->put_W1(W1);
   hr = beamShape->put_W2(W2);
   hr = beamShape->put_W3(W3);
   hr = beamShape->put_W4(W4);
   hr = beamShape->put_D1(D1);
   hr = beamShape->put_D2(D2);
   hr = beamShape->put_D3(D3);
   hr = beamShape->put_D4(D4);
   hr = beamShape->put_D5(D5);
   hr = beamShape->put_D6(D6);
   hr = beamShape->put_D7(D7);
   hr = beamShape->put_T1(T1);
   hr = beamShape->put_T2(T2);

   CComQIPtr<IShape> shape(beamShape);
   hr = beam->putref_Beam(shape);

   // add some prestress and mild rebar
   Float64 dps, Aps;
   dps = 73.5 - 2;
   hr = convert->ConvertToBaseUnits(dps,CComBSTR("in"),&dps);
   Aps = 10*2.16;
   hr = convert->ConvertToBaseUnits(Aps,CComBSTR("in^2"),&Aps);

   hr = beam->AddStrandLayer(dps,Aps,1.0);
   hr = beam->AddStrandLayer(dps,Aps,0.2);

   Float64 ds, As;
   ds = 73.5 - 4;
   hr = convert->ConvertToBaseUnits(ds,CComBSTR("in"),&ds);
   As = 4*0.31;
   hr = convert->ConvertToBaseUnits(As,CComBSTR("in^2"),&As);
   
   hr = beam->AddRebarLayer(ds,As,1.0);
   hr = beam->AddRebarLayer(ds,As,0.2);

   CComPtr<IRCSolutionEx> solution;

   CComPtr<IRCSolver2Ex> nlSolver;
   hr = nlSolver.CoCreateInstance(CLSID_NLSolver);
   hr = nlSolver->Solve(beam,&solution);
   CheckSolution(solution,1.8631927943059585,26615481.212655202,6414478.5690013198,12749930.641357977,0.077026214806171112,0.60372728156028699,19164409.209383119);
 
   solution.Release();

   CComPtr<IRCSolver2Ex> pciSolver;
   hr = pciSolver.CoCreateInstance(CLSID_PCISolver);
   hr = pciSolver->Solve(beam,&solution);
   CheckSolution(solution,1.9105838018870374,26559874.054724388,6533547.9084961740,12413253.267700991,0.076199999999999990,0.59253303508414268,18946801.176202841);

   // No reinforcement, no capacity
   hr = beam->ClearRebarLayers();
   hr = beam->ClearStrandLayers();
 
   solution.Release();

   hr = nlSolver->Solve(beam,&solution);
   CheckSolution(solution,0,0,0,0,0,0,0);

   solution.Release();
   
   hr = pciSolver->Solve(beam,&solution);
   CheckSolution(solution,0,0,0,0,0,0,0);

   // Strands not developed, no capacity
   hr = beam->AddStrandLayer(dps,Aps,0.0);
   hr = beam->AddRebarLayer(ds,As,0.0);

   solution.Release();

   hr = nlSolver->Solve(beam,&solution);
   CheckSolution(solution,0,0,0,0,0,0,0);

   solution.Release();

   hr = pciSolver->Solve(beam,&solution);
   CheckSolution(solution,0,0,0,0,0,0,0);
}

void CSolverTest::CheckSolution(IRCSolution* pSolution,Float64 c,Float64 Mn,Float64 Cflange,Float64 Cweb,Float64 Yflange,Float64 Yweb,Float64 T, Float64 fps,VARIANT_BOOL bIsOverReinforced)
{
   Float64 val;

   pSolution->get_NeutralAxisDepth(&val);
   TRY_TEST( IsEqual(val,c,0.01), true );

   pSolution->get_Mn(&val);
   TRY_TEST( IsEqual(val,Mn,0.01), true );
   
   pSolution->get_Cflange(&val);
   TRY_TEST( IsEqual(val,Cflange,0.01), true);

   pSolution->get_Cweb(&val);
   TRY_TEST( IsEqual(val,Cweb,0.01), true);

   pSolution->get_Yflange(&val);
   TRY_TEST( IsEqual(val,Yflange,0.01), true );

   pSolution->get_Yweb(&val);
   TRY_TEST( IsEqual(val,Yweb,0.01), true );

   pSolution->get_T(&val);
   TRY_TEST( IsEqual(val,T,0.01), true );

   pSolution->get_fps(&val);
   TRY_TEST( IsEqual(val,fps,0.02), true );

   VARIANT_BOOL bVal;
   pSolution->get_IsOverReinforced(&bVal);
   TRY_TEST( bVal, bIsOverReinforced);
}

void CSolverTest::CheckSolution(IRCSolutionEx* pSolution,Float64 c,Float64 Mn,Float64 Cflange,Float64 Cweb,Float64 Yflange,Float64 Yweb,Float64 T)
{
   Float64 val;

   pSolution->get_NeutralAxisDepth(&val);
   TRY_TEST( IsEqual(val,c,0.01), true );

   pSolution->get_Mn(&val);
   TRY_TEST( IsEqual(val,Mn,0.01), true );

   pSolution->get_Cflange(&val);
   TRY_TEST( IsEqual(val,Cflange,0.01), true);

   pSolution->get_Cweb(&val);
   TRY_TEST( IsEqual(val,Cweb,0.01), true);

   pSolution->get_Yflange(&val);
   TRY_TEST( IsEqual(val,Yflange,0.01), true );

   pSolution->get_Yweb(&val);
   TRY_TEST( IsEqual(val,Yweb,0.01), true );

   pSolution->get_T(&val);
   TRY_TEST( IsEqual(val,T,0.01), true );
}
