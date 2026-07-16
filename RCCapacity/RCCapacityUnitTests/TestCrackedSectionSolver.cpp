#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RCCapacityUnitTest
{
	TEST_CLASS(TestCrackedSectionSolver)
	{
	public:

      // See the CrackedSectionAnalysis.xlsx spreadsheet (in the legacy RCCapacityTest project
      // directory) for "hand" calculation validation of results.

		TEST_METHOD(TestRectangularBeam)
		{
         CComPtr<IUnitServer> unit_server;
         unit_server.CoCreateInstance(CLSID_UnitServer);

         // base units of kip and ksi
         unit_server->SetSystemUnits(CComBSTR("12kslug"), CComBSTR("in"), CComBSTR("sec"), CComBSTR("F"), CComBSTR("deg"));

         // Get a general section
         CComPtr<IGeneralSection> section;
         Assert::AreEqual(S_OK, section.CoCreateInstance(CLSID_GeneralSection));

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
         hookPt->Move(0, H / 2);

         // 4 - #10 rebar @ 2" from bottom
         Float64 radius = sqrt(1.27 / M_PI);
         CComPtr<ICircle> bar1;
         bar1.CoCreateInstance(CLSID_Circle);
         bar1->put_Radius(radius);
         CComPtr<IPoint2d> center;
         bar1->get_Center(&center);
         center->Move(0, 2);

         CComPtr<ICircle> bar2;
         bar2.CoCreateInstance(CLSID_Circle);
         bar2->put_Radius(radius);
         center.Release();
         bar2->get_Center(&center);
         center->Move(0, 2);

         CComPtr<ICircle> bar3;
         bar3.CoCreateInstance(CLSID_Circle);
         bar3->put_Radius(radius);
         center.Release();
         bar3->get_Center(&center);
         center->Move(0, 2);

         CComPtr<ICircle> bar4;
         bar4.CoCreateInstance(CLSID_Circle);
         bar4->put_Radius(radius);
         center.Release();
         bar4->get_Center(&center);
         center->Move(0, 2);

         CComQIPtr<IShape> shape1(beam);
         CComQIPtr<IShape> shape2(bar1);
         CComQIPtr<IShape> shape3(bar2);
         CComQIPtr<IShape> shape4(bar3);
         CComQIPtr<IShape> shape5(bar4);

         CComQIPtr<IStressStrain> material1(concrete);
         CComQIPtr<IStressStrain> material2(rebar);

         section->AddShape(CComBSTR("Beam"), shape1, material1, nullptr, nullptr, 1.0, VARIANT_TRUE); // beam
         section->AddShape(CComBSTR("Bar 1"), shape2, material2, nullptr, nullptr, 1.0, VARIANT_FALSE); // bar 1
         section->AddShape(CComBSTR("Bar 2"), shape3, material2, nullptr, nullptr, 1.0, VARIANT_FALSE); // bar 2
         section->AddShape(CComBSTR("Bar 3"), shape4, material2, nullptr, nullptr, 1.0, VARIANT_FALSE); // bar 3
         section->AddShape(CComBSTR("Bar 4"), shape5, material2, nullptr, nullptr, 1.0, VARIANT_FALSE); // bar 4

         CComPtr<ICrackedSectionSolver> solver;
         Assert::AreEqual(S_OK, solver.CoCreateInstance(CLSID_CrackedSectionSolver));

         solver->put_Slices(10);
         solver->put_CGTolerance(0.001);
         solver->putref_Section(section);

         CComPtr<ICrackedSectionSolution> solution;
         Assert::IsTrue(SUCCEEDED(solver->Solve(0, &solution)));

         CComPtr<IPoint2d> pntCG;
         solution->get_CG(&pntCG);

         Float64 y;
         pntCG->get_Y(&y);
         Assert::IsTrue(IsEqual(y, 81.755394));

         CComPtr<IElasticProperties> props;
         solution->get_ElasticProperties(&props);
         pntCG.Release();
         props->get_Centroid(&pntCG);
         pntCG->get_Y(&y);
         Assert::IsTrue(IsEqual(y, 81.755394));

         Float64 value;
         props->get_EA(&value);
         Assert::IsTrue(IsEqual(value, 1435324.2471274068));

         props->get_EIxx(&value);
         Assert::IsTrue(IsEqual(value, 1080016839.2639580));
      }

		TEST_METHOD(TestTeeBeam1)
		{
         // Tee beam with neutral axis in deck
         CComPtr<IUnitServer> unit_server;
         unit_server.CoCreateInstance(CLSID_UnitServer);

         unit_server->SetSystemUnits(CComBSTR("12kslug"), CComBSTR("in"), CComBSTR("sec"), CComBSTR("F"), CComBSTR("deg"));

         CComPtr<IGeneralSection> section;
         Assert::AreEqual(S_OK, section.CoCreateInstance(CLSID_GeneralSection));

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

         CComPtr<IRebarModel> rebar;
         rebar.CoCreateInstance(CLSID_RebarModel);
         rebar->Init(60., 29000., 0.11);

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
         posBeam->get_LocatorPoint(lpBottomCenter, &pntBC);
         pntBC->Move(0, 0);
         posBeam->put_LocatorPoint(lpBottomCenter, pntBC);

         // move bottom center of slab to top center of beam
         CComPtr<IPoint2d> pntTC;
         posBeam->get_LocatorPoint(lpTopCenter, &pntTC);

         CComQIPtr<IXYPosition> posSlab(slab);
         posSlab->put_LocatorPoint(lpBottomCenter, pntTC);

         // #10 rebar @ 2" from bottom
         Float64 radius = sqrt(1.27 / M_PI);
         CComPtr<ICircle> bar1;
         bar1.CoCreateInstance(CLSID_Circle);
         bar1->put_Radius(radius);
         CComPtr<IPoint2d> center;
         bar1->get_Center(&center);
         center->Move(0, 2);

         CComQIPtr<IShape> shape1(slab);
         CComQIPtr<IShape> shape2(beam);
         CComQIPtr<IShape> shape3(bar1);

         CComQIPtr<IStressStrain> material1(slab_concrete);
         CComQIPtr<IStressStrain> material2(beam_concrete);
         CComQIPtr<IStressStrain> material3(rebar);

         section->AddShape(CComBSTR("Slab"), shape1, material1, nullptr, nullptr, 1.0, VARIANT_FALSE); // slab
         section->AddShape(CComBSTR("Beam"), shape2, material2, nullptr, nullptr, 1.0, VARIANT_TRUE); // beam
         section->AddShape(CComBSTR("Rebar"), shape3, material3, nullptr, nullptr, 1.0, VARIANT_FALSE); // rebar

         CComPtr<ICrackedSectionSolver> solver;
         Assert::AreEqual(S_OK, solver.CoCreateInstance(CLSID_CrackedSectionSolver));

         solver->put_Slices(10);
         solver->put_CGTolerance(0.001);
         solver->putref_Section(section);

         CComPtr<ICrackedSectionSolution> solution;
         Assert::IsTrue(SUCCEEDED(solver->Solve(0, &solution)));

         CComPtr<IPoint2d> pntCG;
         solution->get_CG(&pntCG);

         Float64 y;
         pntCG->get_Y(&y);
         Assert::IsTrue(IsEqual(y, 101.425427));

         CComPtr<IElasticProperties> props;
         solution->get_ElasticProperties(&props);
         pntCG.Release();
         props->get_Centroid(&pntCG);
         pntCG->get_Y(&y);
         Assert::IsTrue(IsEqual(y, 101.425427));

         Float64 value;
         props->get_EA(&value);
         Assert::IsTrue(IsEqual(value, 1150707.9739471173));

         props->get_EIxx(&value);
         Assert::IsTrue(IsEqual(value, 380133591.91453171));
      }

		TEST_METHOD(TestTeeBeam2)
		{
         // Tee beam with neutral axis in beam
         CComPtr<IUnitServer> unit_server;
         unit_server.CoCreateInstance(CLSID_UnitServer);

         unit_server->SetSystemUnits(CComBSTR("12kslug"), CComBSTR("in"), CComBSTR("sec"), CComBSTR("F"), CComBSTR("deg"));

         CComPtr<IGeneralSection> section;
         Assert::AreEqual(S_OK, section.CoCreateInstance(CLSID_GeneralSection));

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

         CComPtr<IRebarModel> rebar;
         rebar.CoCreateInstance(CLSID_RebarModel);
         rebar->Init(60., 29000., 0.11);

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
         posBeam->get_LocatorPoint(lpBottomCenter, &pntBC);
         pntBC->Move(0, 0);
         posBeam->put_LocatorPoint(lpBottomCenter, pntBC);

         // move bottom center of slab to top center of beam
         CComPtr<IPoint2d> pntTC;
         posBeam->get_LocatorPoint(lpTopCenter, &pntTC);

         CComQIPtr<IXYPosition> posSlab(slab);
         posSlab->put_LocatorPoint(lpBottomCenter, pntTC);

         // 100 - #10 rebar @ 2" from bottom
         Float64 radius = sqrt(100 * 1.27 / M_PI);
         CComPtr<ICircle> bar1;
         bar1.CoCreateInstance(CLSID_Circle);
         bar1->put_Radius(radius);
         CComPtr<IPoint2d> center;
         bar1->get_Center(&center);
         center->Move(0, 2);

         CComQIPtr<IShape> shape1(slab);
         CComQIPtr<IShape> shape2(beam);
         CComQIPtr<IShape> shape3(bar1);

         CComQIPtr<IStressStrain> material1(slab_concrete);
         CComQIPtr<IStressStrain> material2(beam_concrete);
         CComQIPtr<IStressStrain> material3(rebar);

         section->AddShape(CComBSTR("Slab"), shape1, material1, nullptr, nullptr, 1.0, VARIANT_FALSE); // slab
         section->AddShape(CComBSTR("Beam"), shape2, material2, nullptr, nullptr, 1.0, VARIANT_TRUE); // beam
         section->AddShape(CComBSTR("Rebar"), shape3, material3, nullptr, nullptr, 1.0, VARIANT_FALSE); // rebar

         CComPtr<ICrackedSectionSolver> solver;
         Assert::AreEqual(S_OK, solver.CoCreateInstance(CLSID_CrackedSectionSolver));

         solver->put_Slices(10);
         solver->put_CGTolerance(0.001);
         solver->putref_Section(section);

         CComPtr<ICrackedSectionSolution> solution;
         Assert::IsTrue(SUCCEEDED(solver->Solve(0, &solution)));

         CComPtr<IPoint2d> pntCG;
         solution->get_CG(&pntCG);

         Float64 y;
         pntCG->get_Y(&y);
         Assert::IsTrue(IsEqual(y, 52.15599));

         CComPtr<IElasticProperties> props;
         solution->get_ElasticProperties(&props);
         pntCG.Release();
         props->get_Centroid(&pntCG);
         pntCG->get_Y(&y);
         Assert::IsTrue(IsEqual(y, 52.15599));

         Float64 value;
         props->get_EA(&value);
         Assert::IsTrue(IsEqual(value, 9822852.5720759369));

         props->get_EIxx(&value);
         Assert::IsTrue(IsEqual(value, 16603253157.345383));
      }

		TEST_METHOD(TestTeeBeam3)
		{
         // Tee beam with neutral axis in beam
         //
         // This scenario places the tension reinforcement near the TOP of the section (a
         // hogging/negative-moment configuration), so Solve() is called with naAngle = M_PI to
         // rotate the section 180 degrees before slicing, matching this solver's bottom-tension
         // convention. Parity case: see
         // WBFL\RCSection\RCSectionUnitTests\TestCrackedSectionSolver.cpp::TestTeeBeam3, which
         // solves the same geometry at naAngle = M_PI and produces matching results.
         CComPtr<IUnitServer> unit_server;
         unit_server.CoCreateInstance(CLSID_UnitServer);

         unit_server->SetSystemUnits(CComBSTR("12kslug"), CComBSTR("in"), CComBSTR("sec"), CComBSTR("F"), CComBSTR("deg"));

         CComPtr<IGeneralSection> section;
         Assert::AreEqual(S_OK, section.CoCreateInstance(CLSID_GeneralSection));

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

         CComPtr<IRebarModel> rebar;
         rebar.CoCreateInstance(CLSID_RebarModel);
         rebar->Init(60., 29000., 0.11);

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
         posBeam->get_LocatorPoint(lpBottomCenter, &pntBC);
         pntBC->Move(0, 0);
         posBeam->put_LocatorPoint(lpBottomCenter, pntBC);

         // move bottom center of slab to top center of beam
         CComPtr<IPoint2d> pntTC;
         posBeam->get_LocatorPoint(lpTopCenter, &pntTC);

         CComQIPtr<IXYPosition> posSlab(slab);
         posSlab->put_LocatorPoint(lpBottomCenter, pntTC);

         pntTC.Release();
         posSlab->get_LocatorPoint(lpTopCenter, &pntTC);

         // 2 - #10 rebar @ 2" from top
         Float64 radius = sqrt(2 * 1.27 / M_PI);
         CComPtr<ICircle> bar1;
         bar1.CoCreateInstance(CLSID_Circle);
         bar1->put_Radius(radius);
         CComPtr<IPoint2d> center;
         bar1->get_Center(&center);
         Float64 Y;
         pntTC->get_Y(&Y);
         center->Move(0, Y - 2);

         CComQIPtr<IShape> shape1(slab);
         CComQIPtr<IShape> shape2(beam);
         CComQIPtr<IShape> shape3(bar1);

         CComQIPtr<IStressStrain> material1(slab_concrete);
         CComQIPtr<IStressStrain> material2(beam_concrete);
         CComQIPtr<IStressStrain> material3(rebar);

         section->AddShape(CComBSTR("Slab"), shape1, material1, nullptr, nullptr, 1.0, VARIANT_FALSE); // slab
         section->AddShape(CComBSTR("Beam"), shape2, material2, nullptr, nullptr, 1.0, VARIANT_TRUE); // beam
         section->AddShape(CComBSTR("Rebar"), shape3, material3, nullptr, nullptr, 1.0, VARIANT_FALSE); // rebar

         CComPtr<ICrackedSectionSolver> solver;
         Assert::AreEqual(S_OK, solver.CoCreateInstance(CLSID_CrackedSectionSolver));

         solver->put_Slices(10);
         solver->put_CGTolerance(0.001);
         solver->putref_Section(section);

         CComPtr<ICrackedSectionSolution> solution;
         Assert::IsTrue(SUCCEEDED(solver->Solve(M_PI, &solution)));

         CComPtr<IPoint2d> pntCG;
         solution->get_CG(&pntCG);

         Float64 y;
         pntCG->get_Y(&y);
         Assert::IsTrue(IsEqual(y, -11.781458));

         CComPtr<IElasticProperties> props;
         solution->get_ElasticProperties(&props);
         pntCG.Release();
         props->get_Centroid(&pntCG);
         pntCG->get_Y(&y);
         Assert::IsTrue(IsEqual(y, -11.781458));

         Float64 value;
         props->get_EA(&value);
         Assert::IsTrue(IsEqual(value, 1251805.8138490969));

         props->get_EIxx(&value);
         Assert::IsTrue(IsEqual(value, 708414513.80776465));
      }
	};
}
