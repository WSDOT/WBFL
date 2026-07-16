#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RCCapacityUnitTest
{
	TEST_CLASS(TestGeneralSectionSolver)
	{
	public:

		TEST_METHOD(Test)
		{
         CComPtr<IUnitServer> unit_server;
         unit_server.CoCreateInstance(CLSID_UnitServer);

         // base units of kip and ksi
         unit_server->SetSystemUnits(CComBSTR("12kslug"), CComBSTR("in"), CComBSTR("sec"), CComBSTR("F"), CComBSTR("deg"));

         // Get a general section
         CComPtr<IGeneralSection> section;
         Assert::AreEqual(S_OK, section.CoCreateInstance(CLSID_GeneralSection));

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
         bar1->put_Radius(0.37424);
         CComPtr<IPoint2d> center;
         bar1->get_Center(&center);
         center->Move(22, 46);

         CComPtr<ICircle> bar2;
         bar2.CoCreateInstance(CLSID_Circle);
         bar2->put_Radius(0.37424);
         center.Release();
         bar2->get_Center(&center);
         center->Move(-22, 46);

         CComPtr<ICircle> bar3;
         bar3.CoCreateInstance(CLSID_Circle);
         bar3->put_Radius(0.37424);
         center.Release();
         bar3->get_Center(&center);
         center->Move(-22, -46);

         CComPtr<ICircle> bar4;
         bar4.CoCreateInstance(CLSID_Circle);
         bar4->put_Radius(0.37424);
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

         // setup the stress plan
         CComPtr<IPoint3d> p1, p2, p3;
         p1.CoCreateInstance(CLSID_Point3d);
         p2.CoCreateInstance(CLSID_Point3d);
         p3.CoCreateInstance(CLSID_Point3d);

         // neutral axis
         p1->Move(-1000, 0, 0);
         p2->Move(1000, 0, 0);

         // rotation of section
         p3->Move(0, 48, -0.003); // -0.003 at top face of beam

         CComPtr<IPlane3d> strainPlane;
         strainPlane.CoCreateInstance(CLSID_Plane3d);
         strainPlane->ThroughPoints(p1, p2, p3);

         CComPtr<IGeneralSectionSolver> solver;
         Assert::AreEqual(S_OK, solver.CoCreateInstance(CLSID_GeneralSectionSolver));

         solver->put_Slices(10);
         solver->putref_Section(section);

         CComPtr<IGeneralSectionSolution> solution;
         solver->Solve(strainPlane, &solution);

         Float64 value;
         solution->get_Fz(&value);
         Assert::IsTrue(IsEqual(value, -6989.5380720604908));
         solution->get_Mx(&value);
         Assert::IsTrue(IsEqual(value, -199028.63168431941));
         solution->get_My(&value);
         Assert::IsTrue(IsEqual(value, 0.0));
         solution->get_CompressionResultant(&value);
         Assert::IsTrue(IsEqual(value, -7042.3377809023850));
         solution->get_TensionResultant(&value);
         Assert::IsTrue(IsEqual(value, 52.799708841892233));

         // NOTE: ported as-is from the legacy console-app test (RCCapacityTest\GeneralSectionSolverTest.cpp),
         // which itself flagged this suite as incomplete (single scenario, no error-info checks).
         // Filling this gap is tracked as follow-up work (see the test-strengthening plan), not part
         // of this mechanical port.
         //CComQIPtr<ISupportErrorInfo> eInfo(ss);
         //Assert::IsTrue(eInfo != nullptr);
         //Assert::AreEqual(S_OK, eInfo->InterfaceSupportsErrorInfo(IID_IUnconfinedConcrete));
         //Assert::AreEqual(S_OK, eInfo->InterfaceSupportsErrorInfo(IID_IStressStrain));
         //Assert::AreEqual(S_OK, eInfo->InterfaceSupportsErrorInfo(IID_IStructuredStorage2));
         //Assert::AreEqual(S_FALSE, eInfo->InterfaceSupportsErrorInfo(IID_ISupportErrorInfo));
      }
	};
}
