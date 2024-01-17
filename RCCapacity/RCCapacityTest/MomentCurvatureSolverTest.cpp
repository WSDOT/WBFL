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
   hr = unit_server->SetSystemUnits(CComBSTR("12kslug"), CComBSTR("in"), CComBSTR("sec"), CComBSTR("F"), CComBSTR("deg"));

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
   rebar->Init(60., 29000., 0.11);

   //
   // shapes
   //

   // main beam
   CComPtr<IRectangle> beam;
   beam.CoCreateInstance(CLSID_Rect);
   beam->put_Height(8 * 12);
   beam->put_Width(4 * 12);

   // #6 rebar
   CComPtr<ICircle> bar1;
   bar1.CoCreateInstance(CLSID_Circle);
   bar1->put_Radius(0.74848);
   CComPtr<IPoint2d> center;
   bar1->get_Center(&center);
   center->Move(22, 46);

   CComPtr<ICircle> bar2;
   bar2.CoCreateInstance(CLSID_Circle);
   bar2->put_Radius(0.74848);
   center.Release();
   bar2->get_Center(&center);
   center->Move(-22, 46);

   CComPtr<ICircle> bar3;
   bar3.CoCreateInstance(CLSID_Circle);
   bar3->put_Radius(0.74848);
   center.Release();
   bar3->get_Center(&center);
   center->Move(-22, -46);

   CComPtr<ICircle> bar4;
   bar4.CoCreateInstance(CLSID_Circle);
   bar4->put_Radius(0.74848);
   center.Release();
   bar4->get_Center(&center);
   center->Move(22, -46);

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


   CComPtr<IMomentCurvatureSolver> solver;
   TRY_TEST(solver.CoCreateInstance(CLSID_MomentCurvatureSolver), S_OK);

   CComPtr<IMomentCurvatureSolution> solution;
   solver->putref_Section(section);
   solver->put_Slices(20);
   solver->Solve(-200, 0.00, &solution);

   IndexType nPoints;
   solution->get_PointCount(&nPoints);
   TRY_TEST(nPoints, 123);

   Float64 Mmax, k;
   solution->PeakCapacity(&Mmax, &k);
   TRY_TEST(IsEqual(Mmax, 28986.080336362313), true);
   TRY_TEST(IsEqual(k, 0.0011981250000000024), true);

   static std::pair<Float64, Float64> datum[] = 
   {
      {0, 2.060573934e-13},
      {1e-05, 15291.74756},
      {2e-05, 23162.38034},
      {3e-05, 27718.24609},
      {4e-05, 27915.35418},
      {5e-05, 28038.68061},
      {6e-05, 28156.27474},
      {7e-05, 28240.4124},
      {8e-05, 28302.53395},
      {9e-05, 28349.36745},
      {0.0001, 28385.12006},
      {0.00011, 28412.60943},
      {0.00012, 28433.75726},
      {0.00013, 28450.02142},
      {0.00014, 28462.15711},
      {0.00015, 28471.1707},
      {0.00016, 28477.55598},
      {0.00017, 28481.78845},
      {0.00018, 28484.14659},
      {0.00019, 28484.99239},
      {0.0002, 28506.53709},
      {0.00021, 28526.87257},
      {0.00022, 28545.70803},
      {0.00023, 28563.21815},
      {0.00024, 28579.5473},
      {0.00025, 28594.81998},
      {0.00026, 28609.14656},
      {0.00027, 28622.61072},
      {0.00028, 28635.30147},
      {0.00029, 28647.62799},
      {0.0003, 28658.63124},
      {0.00031, 28669.38684},
      {0.00032, 28679.60323},
      {0.00033, 28689.7518},
      {0.00034, 28698.58691},
      {0.00035, 28707.59374},
      {0.00036, 28715.87673},
      {0.00037, 28723.96284},
      {0.00038, 28731.71318},
      {0.00039, 28739.14823},
      {0.0004, 28746.28604},
      {0.00041, 28753.14735},
      {0.00042, 28759.75194},
      {0.00043, 28766.11575},
      {0.00044, 28772.25268},
      {0.00045, 28778.17578},
      {0.00046, 28783.89734},
      {0.00047, 28789.42871},
      {0.00048, 28794.86616},
      {0.00049, 28799.96194},
      {0.0005, 28804.98249},
      {0.00051, 28809.8502},
      {0.00052, 28814.57329},
      {0.00053, 28819.1578},
      {0.00054, 28823.61153},
      {0.00055, 28827.94034},
      {0.00056, 28832.15005},
      {0.00057, 28836.24612},
      {0.00058, 28840.46176},
      {0.00059, 28844.11794},
      {0.0006, 28847.90181},
      {0.00061, 28851.59113},
      {0.00062, 28855.18929},
      {0.00063, 28858.97415},
      {0.00064, 28862.14227},
      {0.00065, 28865.58024},
      {0.00066, 28868.97508},
      {0.00067, 28872.32054},
      {0.00068, 28875.61954},
      {0.00069, 28879.02068},
      {0.0007, 28882.26756},
      {0.00071, 28885.12914},
      {0.00072, 28888.38712},
      {0.00073, 28891.18958},
      {0.00074, 28894.13677},
      {0.00075, 28897.03054},
      {0.00076, 28899.87166},
      {0.00077, 28902.66024},
      {0.00078, 28905.39768},
      {0.00079, 28908.08532},
      {0.0008, 28910.7245},
      {0.00081, 28913.31648},
      {0.00082, 28915.87095},
      {0.00083, 28918.36385},
      {0.00084, 28920.82115},
      {0.00085, 28923.2345},
      {0.00086, 28925.60572},
      {0.00087, 28927.93562},
      {0.00088, 28930.26961},
      {0.00089, 28932.47523},
      {0.0009, 28934.68677},
      {0.00091, 28936.86307},
      {0.00092, 28938.99767},
      {0.00093, 28941.10104},
      {0.00094, 28943.1704},
      {0.00095, 28945.20536},
      {0.00096, 28947.19303},
      {0.00097, 28949.32443},
      {0.00098, 28951.08698},
      {0.00099, 28952.9856},
      {0.001, 28954.85266},
      {0.00101, 28956.68878},
      {0.00102, 28958.4945},
      {0.00103, 28960.26744},
      {0.00104, 28962.0094},
      {0.00105, 28963.73464},
      {0.00106, 28965.42405},
      {0.00107, 28967.08555},
      {0.00108, 28968.71947},
      {0.00109, 28970.32674},
      {0.0011, 28971.90725},
      {0.00111, 28973.46159},
      {0.00112, 28974.99012},
      {0.00113, 28976.49322},
      {0.00114, 28977.83039},
      {0.00115, 28979.42425},
      {0.00116, 28980.85287},
      {0.00117, 28982.25731},
      {0.00118, 28983.63819},
      {0.00119, 28984.76055},
      {0.001195, 28985.66467},
      {0.0011975, 28985.99738},
      {0.001198125, 28986.08034}
   };

   for (IndexType i = 0; i < nPoints; i++)
   {
      Float64 M, k;
      solution->get_Moment(i, &M);
      solution->get_Curvature(i, &k);
      //std::cout.precision(10);
      //std::cout << "{" << k << ", " << M << "}," << std::endl;
      TRY_TEST(IsEqual(datum[i].first, k), true);
      TRY_TEST(IsEqual(datum[i].second, M), true);
   }
}
