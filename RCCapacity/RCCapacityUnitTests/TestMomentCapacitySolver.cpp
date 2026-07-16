#include "pch.h"
#include "CppUnitTest.h"
#include <Units\Units.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RCCapacityUnitTest
{
	TEST_CLASS(TestMomentCapacitySolver)
	{
	public:

		TEST_METHOD(Test)
		{
         // Restores the process-wide unit system on scope exit, so this test doesn't leak global
         // state into other test DLLs when several native test assemblies run in the same host
         // process (see WBFL::Units::AutoSystem doc comment).
         WBFL::Units::AutoSystem as;

         CComPtr<IUnitServer> unit_server;
         unit_server.CoCreateInstance(CLSID_UnitServer);

         // base units of kip and ksi
         unit_server->SetSystemUnits(CComBSTR("12kslug"), CComBSTR("in"), CComBSTR("sec"), CComBSTR("F"), CComBSTR("deg"));
         WBFL::Units::System::SetMassUnit(WBFL::Units::Measure::_12KSlug);
         WBFL::Units::System::SetLengthUnit(WBFL::Units::Measure::Inch);
         WBFL::Units::System::SetTimeUnit(WBFL::Units::Measure::Second);

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
         Float64 H = 4 * 12;
         Float64 W = 2 * 12;
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
         center->Move(W / 2 - 2, H / 2 - 2);

         CComPtr<IGenericShape> bar2;
         bar2.CoCreateInstance(CLSID_GenericShape);
         bar2->put_Area(Ab);
         center.Release();
         bar2->get_Centroid(&center);
         center->Move(-(W / 2 - 2), H / 2 - 2);

         CComPtr<IGenericShape> bar3;
         bar3.CoCreateInstance(CLSID_GenericShape);
         bar3->put_Area(Ab);
         center.Release();
         bar3->get_Centroid(&center);
         center->Move(-(W / 2 - 2), -(H / 2 - 2));

         CComPtr<IGenericShape> bar4;
         bar4.CoCreateInstance(CLSID_GenericShape);
         bar4->put_Area(Ab);
         center.Release();
         bar4->get_Centroid(&center);
         center->Move(W / 2 - 2, -(H / 2 - 2));

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

         CComPtr<IMomentCapacitySolver> solver;
         Assert::AreEqual(S_OK, solver.CoCreateInstance(CLSID_MomentCapacitySolver));

         solver->put_Slices(10);
         solver->put_SliceGrowthFactor(3);
         solver->put_AxialTolerance(0.001);
         solver->putref_Section(section);

         CComPtr<IMomentCapacitySolution> solution;
         Assert::IsTrue(SUCCEEDED(solver->Solve(0.00, 0.00, -0.003, 0.0, smFixedCompressionStrain, &solution))); // compression top, use angle = 0

         Float64 Fz, Mx, My;
         solution->get_Fz(&Fz);
         solution->get_Mx(&Mx);
         solution->get_My(&My);

         Assert::IsTrue(IsZero(Fz, 0.001));
         Assert::IsTrue(IsEqual(Mx, -6888.22801));
         Assert::IsTrue(IsZero(My));

         Float64 c;
         solution->get_DepthToNeutralAxis(&c);
         Assert::IsTrue(IsEqual(c, 1.852083));

         Float64 dc;
         solution->get_DepthToCompressionResultant(&dc);
         Assert::IsTrue(IsEqual(dc, 0.926042));

         Float64 de;
         solution->get_DepthToTensionResultant(&de);
         Assert::IsTrue(IsEqual(de, 41.433434));

         Float64 moment_arm;
         solution->get_MomentArm(&moment_arm);
         Assert::IsTrue(IsEqual(moment_arm, de - dc));

         Float64 k;
         solution->get_Curvature(&k);
         Assert::IsTrue(IsEqual(k, 0.00161979));

         CComPtr<IPlane3d> strainPlane;
         solution->get_IncrementalStrainPlane(&strainPlane);

         Float64 ec;
         strainPlane->GetZ(0.00, H / 2, &ec);
         Assert::IsTrue(IsEqual(ec, -0.003));

         solution.Release();

         Assert::IsTrue(SUCCEEDED(solver->Solve(0.00, M_PI, -0.003, 0.0, smFixedCompressionStrain, &solution))); //compression bottom, use angle = M_PI

         solution->get_Fz(&Fz);
         solution->get_Mx(&Mx);
         solution->get_My(&My);
         strainPlane.Release();
         solution->get_IncrementalStrainPlane(&strainPlane);

         Assert::IsTrue(IsZero(Fz, 0.001));
         Assert::IsTrue(IsEqual(Mx, 6888.22801));
         Assert::IsTrue(IsZero(My));

         solution->get_DepthToNeutralAxis(&c);
         Assert::IsTrue(IsEqual(c, 1.852083));

         solution->get_DepthToCompressionResultant(&dc);
         Assert::IsTrue(IsEqual(dc, 0.926042));

         solution->get_DepthToTensionResultant(&de);
         Assert::IsTrue(IsEqual(de, 41.433434));

         solution->get_MomentArm(&moment_arm);
         Assert::IsTrue(IsEqual(moment_arm, de - dc));

         solution->get_Curvature(&k);
         Assert::IsTrue(IsEqual(k, -0.00161979));

         strainPlane->GetZ(0.00, -H / 2, &ec);
         Assert::IsTrue(IsEqual(ec, -0.003));

         solution.Release();

         Assert::IsTrue(SUCCEEDED(solver->Solve(0.00, PI_OVER_2, -0.003, 0.0, smFixedCompressionStrain, &solution))); //compression left, use angle = PI_OVER_2

         solution->get_Fz(&Fz);
         solution->get_Mx(&Mx);
         solution->get_My(&My);
         strainPlane.Release();
         solution->get_IncrementalStrainPlane(&strainPlane);

         Assert::IsTrue(IsZero(Fz, 0.001));
         Assert::IsTrue(IsZero(Mx));
         Assert::IsTrue(IsEqual(My, -3374.92488));

         solution->get_DepthToNeutralAxis(&c);
         Assert::IsTrue(IsEqual(c, 1.438523));

         solution->get_DepthToCompressionResultant(&dc);
         Assert::IsTrue(IsEqual(dc, 0.630138));

         solution->get_DepthToTensionResultant(&de);
         Assert::IsTrue(IsEqual(de, 14.77174));

         solution->get_MomentArm(&moment_arm);
         Assert::IsTrue(IsEqual(moment_arm, de - dc));

         solution->get_Curvature(&k);
         Assert::IsTrue(IsEqual(k, 0.00208547));

         strainPlane->GetZ(-W / 2, 0.00, &ec);
         Assert::IsTrue(IsEqual(ec, -0.003));

         solution.Release();

         Assert::IsTrue(SUCCEEDED(solver->Solve(0.00, 3 * PI_OVER_2, -0.003, 0.0, smFixedCompressionStrain, &solution))); //compression right, use angle = 3*PI_OVER_2

         solution->get_Fz(&Fz);
         solution->get_Mx(&Mx);
         solution->get_My(&My);
         strainPlane.Release();
         solution->get_IncrementalStrainPlane(&strainPlane);

         Assert::IsTrue(IsZero(Fz, 0.001));
         Assert::IsTrue(IsZero(Mx));
         Assert::IsTrue(IsEqual(My, 3374.92488));

         solution->get_DepthToNeutralAxis(&c);
         Assert::IsTrue(IsEqual(c, 1.438523));

         solution->get_DepthToCompressionResultant(&dc);
         Assert::IsTrue(IsEqual(dc, 0.630138));

         solution->get_DepthToTensionResultant(&de);
         Assert::IsTrue(IsEqual(de, 14.77174));

         solution->get_MomentArm(&moment_arm);
         Assert::IsTrue(IsEqual(moment_arm, de - dc));

         solution->get_Curvature(&k);
         Assert::IsTrue(IsEqual(k, -0.00208547));

         strainPlane->GetZ(W / 2, 0.00, &ec);
         Assert::IsTrue(IsEqual(ec, -0.003));

         // make bar3 and bar4 be unbonded for 5 ft
         CComQIPtr<IUnitConvert> convert(unit_server);
         Float64 Le;
         convert->ConvertToBaseUnits(5.0, CComBSTR("ft"), &Le);
         section->put_ElongationLength(3, Le);
         section->put_ElongationLength(4, Le);
         solution.Release();
         Assert::IsTrue(SUCCEEDED(solver->Solve(0.00, M_PI, -0.003, 0.0, smFixedCompressionStrain, &solution))); // compression bottom, use angle = M_PI

         solution->get_Fz(&Fz);
         solution->get_Mx(&Mx);
         solution->get_My(&My);
         strainPlane.Release();
         solution->get_IncrementalStrainPlane(&strainPlane);

         Assert::IsTrue(IsZero(Fz, 0.001));
         Assert::IsTrue(IsEqual(Mx, 6884.17511, 0.0001));
         Assert::IsTrue(IsZero(My));

         solution->get_DepthToNeutralAxis(&c);
         Assert::IsTrue(IsEqual(c, 1.667856));

         solution->get_DepthToCompressionResultant(&dc);
         Assert::IsTrue(IsEqual(dc, 0.83393));

         solution->get_DepthToTensionResultant(&de);
         Assert::IsTrue(IsEqual(de, 45.78926));

         solution->get_MomentArm(&moment_arm);
         Assert::IsTrue(IsEqual(moment_arm, de - dc));

         solution->get_Curvature(&k);
         Assert::IsTrue(IsEqual(k, -0.0017987));

         strainPlane->GetZ(0.00, -H / 2, &ec);
         Assert::IsTrue(IsEqual(ec, -0.003));
      }
	};
}
