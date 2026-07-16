#include "pch.h"
#include "CppUnitTest.h"
#include <Units\Units.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace
{
   Float64 GetStrain(CComPtr<IPlane3d>& plane1, CComPtr<IPlane3d>& plane2, Float64 X, Float64 Y)
   {
      Float64 e1, e2;
      plane1->GetZ(X, Y, &e1);
      plane2->GetZ(X, Y, &e2);
      return e1 + e2;
   }
}

namespace RCCapacityUnitTest
{
	TEST_CLASS(TestUHPCMomentCapacity)
	{
	public:

      // Test1: generic rectangular UHPC beam scenario.
      //
      // Test2/Test3 source: "Design Example of a UHPC Girder Bridge with a Conventional Concrete
      // Deck" (Graybeal, et al.), presented April 5, 2021 to AASHTO T-10.
      //
      // Test4 source: "Analysis of a Rectangular Mild Steel Reinforced UHPC Beam", FHWA,
      // Graybeal, et al.

		TEST_METHOD(Test1)
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

         CComPtr<IPlane3d> strainPlane;
         section->get_InitialStrain(0, &strainPlane);

         // Use strain compatibility analysis to determine moment capacity at the onset of the crack localization strain
         CComPtr<IMomentCapacitySolution> solution;
         Float64 Fz, Mx, My;
         CComPtr<IPlane3d> incrementalStrainPlane;
         Assert::IsTrue(SUCCEEDED(solver->Solve(0.00, 0.00, 0.0045, 0.0, smFixedTensionStrain, &solution))); // compression top, use angle = 0

         solution->get_Fz(&Fz);
         solution->get_Mx(&Mx);
         solution->get_My(&My);
         solution->get_IncrementalStrainPlane(&incrementalStrainPlane);

         Assert::IsTrue(IsZero(Fz, 0.001));
         Assert::IsTrue(IsEqual(Mx, -34044.067077037682));
         Assert::IsTrue(IsZero(My));

         Float64 ec = GetStrain(strainPlane, incrementalStrainPlane, 0.00, -H / 2);
         Assert::IsTrue(IsEqual(ec, 0.0045));

         // compute curvature
         Float64 k = ec / (H / 2);
         Assert::IsTrue(IsEqual(k, 0.0045 / (H / 2)));

         // Solve again but this time set the strain at the bottom
         solution.Release();
         incrementalStrainPlane.Release();
         Assert::IsTrue(SUCCEEDED(solver->Solve(0.00, 0.00, 0.0045, -H / 2, smFixedStrain, &solution))); // compression top, use angle = 0

         solution->get_Fz(&Fz);
         solution->get_Mx(&Mx);
         solution->get_My(&My);
         solution->get_IncrementalStrainPlane(&incrementalStrainPlane);

         Assert::IsTrue(IsZero(Fz, 0.001));
         Assert::IsTrue(IsEqual(Mx, -34044.067077037682));
         Assert::IsTrue(IsZero(My));

         ec = GetStrain(strainPlane, incrementalStrainPlane, 0.00, -H / 2);
         Assert::IsTrue(IsEqual(ec, 0.0045));

         // compute curvature
         k = ec / (H / 2);
         Assert::IsTrue(IsEqual(k, 0.0045 / (H / 2)));

         // Solve for concrete crushing
         // this example will have tension strains the rebar that exceed the fracture limit)
         solution.Release();
         incrementalStrainPlane.Release();
         Assert::AreEqual(RC_E_MATERIALFAILURE, solver->Solve(0.00, 0.00, -0.0035, 0, smFixedCompressionStrain, &solution)); // compression top, use angle = 0

         solution->get_Fz(&Fz);
         solution->get_Mx(&Mx);
         solution->get_My(&My);
         solution->get_IncrementalStrainPlane(&incrementalStrainPlane);

         Assert::IsTrue(IsZero(Fz, 0.001));
         Assert::IsTrue(IsEqual(Mx, -7179.6800558279974));
         Assert::IsTrue(IsZero(My));

         ec = GetStrain(strainPlane, incrementalStrainPlane, 0.00, H / 2);
         Assert::IsTrue(IsEqual(ec, -0.0035));

         // compute curvature
         k = ec / (H / 2);
         Assert::IsTrue(IsEqual(k, -0.0035 / (H / 2)));

         // Solve again but this time set the strain at the top
         // this example will have tension strains the rebar that exceed the fracture limit)
         solution.Release();
         incrementalStrainPlane.Release();
         Assert::AreEqual(RC_E_MATERIALFAILURE, solver->Solve(0.00, 0.00, -0.0035, H / 2, smFixedStrain, &solution)); // compression top, use angle = 0

         solution->get_Fz(&Fz);
         solution->get_Mx(&Mx);
         solution->get_My(&My);
         solution->get_IncrementalStrainPlane(&incrementalStrainPlane);

         Assert::IsTrue(IsZero(Fz, 0.001));
         Assert::IsTrue(IsEqual(Mx, -7179.6800558279974));
         Assert::IsTrue(IsZero(My));

         ec = GetStrain(strainPlane, incrementalStrainPlane, 0.00, H / 2);
         Assert::IsTrue(IsEqual(ec, -0.0035));

         // compute curvature
         k = ec / (H / 2);
         Assert::IsTrue(IsEqual(k, -0.0035 / (H / 2)));
      }

		TEST_METHOD(Test2)
		{
         WBFL::Units::AutoSystem as;

         CComPtr<IUnitServer> unit_server;
         unit_server.CoCreateInstance(CLSID_UnitServer);
         unit_server->SetSystemUnits(CComBSTR("12kslug"), CComBSTR("in"), CComBSTR("sec"), CComBSTR("F"), CComBSTR("deg"));
         WBFL::Units::System::SetMassUnit(WBFL::Units::Measure::_12KSlug);
         WBFL::Units::System::SetLengthUnit(WBFL::Units::Measure::Inch);
         WBFL::Units::System::SetTimeUnit(WBFL::Units::Measure::Second);

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
         beam->put_T(3.5);
         beam->put_W1(21);
         beam->put_W2(27);

         Float64 h;
         beam->get_Height(&h);

         CComPtr<IPoint2d> origin;
         origin.CoCreateInstance(CLSID_Point2d);

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
         pnt1->Move(0.0, -54 + 2);
         layer1->putref_Centroid(pnt1);
         CComQIPtr<IShape> layer1_shape(layer1);

         CComPtr<IGenericShape> layer2;
         layer2.CoCreateInstance(CLSID_GenericShape);
         layer2->put_Area(13 * 0.294);
         CComPtr<IPoint2d> pnt2;
         pnt2.CoCreateInstance(CLSID_Point2d);
         pnt2->Move(0.0, -54 + 4);
         layer2->putref_Centroid(pnt2);
         CComQIPtr<IShape> layer2_shape(layer2);

         CComPtr<IGenericShape> layer3;
         layer3.CoCreateInstance(CLSID_GenericShape);
         layer3->put_Area(13 * 0.294);
         CComPtr<IPoint2d> pnt3;
         pnt3.CoCreateInstance(CLSID_Point2d);
         pnt3->Move(0.0, -54 + 6);
         layer3->putref_Centroid(pnt3);
         CComQIPtr<IShape> layer3_shape(layer3);

         CComPtr<IGenericShape> layer4;
         layer4.CoCreateInstance(CLSID_GenericShape);
         layer4->put_Area(9 * 0.294);
         CComPtr<IPoint2d> pnt4;
         pnt4.CoCreateInstance(CLSID_Point2d);
         pnt4->Move(0.0, -54 + 8);
         layer4->putref_Centroid(pnt4);
         CComQIPtr<IShape> layer4_shape(layer4);

         CComPtr<IGenericShape> layer5;
         layer5.CoCreateInstance(CLSID_GenericShape);
         layer5->put_Area(5 * 0.294);
         CComPtr<IPoint2d> pnt5;
         pnt5.CoCreateInstance(CLSID_Point2d);
         pnt5->Move(0.0, -54 + 10);
         layer5->putref_Centroid(pnt5);
         CComQIPtr<IShape> layer5_shape(layer5);

         CComPtr<IGenericShape> layer6;
         layer6.CoCreateInstance(CLSID_GenericShape);
         layer6->put_Area(1 * 0.294);
         CComPtr<IPoint2d> pnt6;
         pnt6.CoCreateInstance(CLSID_Point2d);
         pnt6->Move(0.0, -54 + 12);
         layer6->putref_Centroid(pnt6);
         CComQIPtr<IShape> layer6_shape(layer6);

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
         Assert::AreEqual(S_OK, section.CoCreateInstance(CLSID_GeneralSection));

         section->AddShape(CComBSTR("Deck"), deck_shape, ss_deck_concrete, nullptr, nullptr, 1.0, VARIANT_FALSE);
         section->AddShape(CComBSTR("Haunch"), haunch_shape, ss_deck_concrete, nullptr, nullptr, 1.0, VARIANT_FALSE);
         section->AddShape(CComBSTR("Girder"), beam_shape, ss_girder_concrete, nullptr, nullptr, 1.0, VARIANT_TRUE);
         section->AddShape(CComBSTR("Strand Layer 1"), layer1_shape, ss_strand, nullptr, initialStrain, 1.0, VARIANT_FALSE);
         section->AddShape(CComBSTR("Strand Layer 2"), layer2_shape, ss_strand, nullptr, initialStrain, 1.0, VARIANT_FALSE);
         section->AddShape(CComBSTR("Strand Layer 3"), layer3_shape, ss_strand, nullptr, initialStrain, 1.0, VARIANT_FALSE);
         section->AddShape(CComBSTR("Strand Layer 4"), layer4_shape, ss_strand, nullptr, initialStrain, 1.0, VARIANT_FALSE);
         section->AddShape(CComBSTR("Strand Layer 5"), layer5_shape, ss_strand, nullptr, initialStrain, 1.0, VARIANT_FALSE);
         section->AddShape(CComBSTR("Strand Layer 6"), layer6_shape, ss_strand, nullptr, initialStrain, 1.0, VARIANT_FALSE);

         CComPtr<IMomentCapacitySolver> solver;
         Assert::AreEqual(S_OK, solver.CoCreateInstance(CLSID_MomentCapacitySolver));

         solver->put_Slices(50);
         solver->put_SliceGrowthFactor(1);
         solver->put_AxialTolerance(0.0001);
         solver->putref_Section(section);

         // Compute nominal capacity when the stress in the bottom layer of reinforcement is equal to 0.80fy
         // Msl and Ysl
         Float64 fu = 270;
         Float64 fy = 0.9 * fu;
         Float64 esl = 0.8 * fy / 27931;
         position.Release();
         layer1->get_XYPosition(&position);
         CComPtr<IPoint2d> center;
         position->get_LocatorPoint(lpCenterCenter, &center);
         Float64 Y;
         center->get_Y(&Y);

         CComPtr<IMomentCapacitySolution> solution;
         Assert::IsTrue(SUCCEEDED(solver->Solve(0.00, 0.00, esl - ei, Y, smFixedStrain, &solution)));

         Float64 Fz, Mx, My;
         CComPtr<IPlane3d> strainPlane;
         solution->get_Fz(&Fz);
         solution->get_Mx(&Mx);
         solution->get_My(&My);
         solution->get_IncrementalStrainPlane(&strainPlane);

         Assert::IsTrue(IsZero(Fz, 0.001));
         Assert::IsTrue(IsEqual(Mx, -181098.57017320214)); //-164292.0 (13691 k-ft) from FHWA example slides
         Assert::IsTrue(IsZero(My));
         Float64 Msl = -Mx;

         Float64 ec;
         strainPlane->GetZ(0.00, Y, &ec);
         Assert::IsTrue(IsEqual(ec, esl - ei));

         Float64 Yna;
         strainPlane->GetY(0.0, 0.0, &Yna); // location of neutral axis below top of girder
         Assert::IsTrue(IsEqual(Yna, -20.888677550628323)); // 40.7-10" = 30.7" from top of girder from FHWN example slides

         strainPlane->GetZ(0.00, -54, &ec); // strain at bottom of girder
         Float64 Ysl = ec / (54 + Yna); // curvature
         Assert::IsTrue(IsEqual(Ysl, 3.6270706495074442e-05)); // 0.0000545 from FHWA example slides

         // Nominal moment capacity at crack localization, Ml and Yl
         solution.Release();
         Assert::IsTrue(SUCCEEDED(solver->Solve(0.00, 0.00, 0.0045, 0.0, smFixedTensionStrain, &solution)));

         strainPlane.Release();
         solution->get_Fz(&Fz);
         solution->get_Mx(&Mx);
         solution->get_My(&My);
         solution->get_IncrementalStrainPlane(&strainPlane);

         Assert::IsTrue(IsZero(Fz, 0.001));
         Assert::IsTrue(IsEqual(Mx, -225562.34822251741)); // -215664.0 (17972 k-ft) from FHWA example slides
         Assert::IsTrue(IsZero(My));
         Float64 Ml = -Mx;

         strainPlane->GetZ(0.00, -h, &ec);
         Assert::IsTrue(IsEqual(ec, 0.0045));

         strainPlane->GetY(0.0, 0.0, &Yna); // location of neutral axis below top of girder
         Assert::IsTrue(IsEqual(Yna, -10.377082883243821)); // 25.5-10" = 15.5" from top of girder from FHWN example slides

         Float64 Yl = ec / (54 + Yna);
         Assert::IsTrue(IsEqual(Yl, 0.00010315678770302790)); // 0.0001167 from FHWN example slides

         // Nominal moment capacity at compression strain limit in UHPC section, Mc, Yc
         // fixed strain at top of girder (not top of section/top of deck)
         solution.Release();
         Assert::AreEqual(RC_E_MATERIALFAILURE, solver->Solve(0.00, 0.00, -0.0035, 0.0, smFixedStrain, &solution)); // strain in deck concrete exceeds crushing limit of -0.003

         strainPlane.Release();
         solution->get_Fz(&Fz);
         solution->get_Mx(&Mx);
         solution->get_My(&My);
         solution->get_IncrementalStrainPlane(&strainPlane);

         Assert::IsTrue(IsZero(Fz, 0.001));
         Assert::IsTrue(IsEqual(Mx, -223570.08762778813));
         Assert::IsTrue(IsZero(My));
         Float64 Mc = -Mx;

         strainPlane->GetZ(0.00, 10.00, &ec); // strain at top of deck
         Assert::IsTrue(IsEqual(ec, -0.010052730543170255));

         strainPlane->GetZ(0.00, -h, &ec); // strain at bottom of beam
         Assert::IsTrue(IsEqual(ec, 0.031884744933119380));

         strainPlane->GetZ(0.00, 0.00, &ec);
         Assert::IsTrue(IsEqual(ec, -0.0035));

         strainPlane->GetY(0.0, 0.0, &Yna); // location of neutral axis
         Assert::IsTrue(IsEqual(Yna, -5.3412847925632487));

         Float64 Yc = ec / Yna;
         Assert::IsTrue(IsEqual(Yc, 0.00065527305431702554));

         // Nominal moment capacity at compression strain limit in deck, Md, Yd
         solution.Release();
         Assert::AreEqual(S_OK, solver->Solve(0.00, 0.00, -0.003, 0.0, smFixedCompressionStrain, &solution));

         strainPlane.Release();
         solution->get_Fz(&Fz);
         solution->get_Mx(&Mx);
         solution->get_My(&My);
         solution->get_IncrementalStrainPlane(&strainPlane);

         Assert::IsTrue(IsZero(Fz, 0.001));
         Assert::IsTrue(IsEqual(Mx, -217497.65849270608));
         Assert::IsTrue(IsZero(My));
         Float64 Md = -Mx;

         strainPlane->GetZ(0.00, 10.0, &ec);
         Assert::IsTrue(IsEqual(ec, -0.003));

         strainPlane->GetY(0.0, 0.0, &Yna); // location of neutral axis
         Assert::IsTrue(IsEqual(Yna, -7.1902952786824184));

         Float64 Yd = ec / (Yna - 10);
         Assert::IsTrue(IsEqual(Yd, 0.00017451707206683523));

         // Nominal moment capacity at maximum usable strain of reinforcement, Mt, Yt
         solution.Release();
         Assert::AreEqual(RC_E_MATERIALFAILURE, solver->Solve(0.00, 0.00, 0.035 - ei, Y, smFixedStrain, &solution)); // strain exceeds crushing strain of UHPC

         strainPlane.Release();
         solution->get_Fz(&Fz);
         solution->get_Mx(&Mx);
         solution->get_My(&My);
         solution->get_IncrementalStrainPlane(&strainPlane);

         Assert::IsTrue(IsZero(Fz, 0.001));
         Assert::IsTrue(IsEqual(Mx, -223602.40886393379));
         Assert::IsTrue(IsZero(My));
         Float64 Mt = -Mx;

         strainPlane->GetZ(0.00, Y, &ec);
         Assert::IsTrue(IsEqual(ec, 0.035 - ei));

         strainPlane->GetY(0.0, 0.0, &Yna); // location of neutral axis
         Assert::IsTrue(IsEqual(Yna, -5.4497666416267565));

         Float64 Yt = ec / (Yna - Y);
         Assert::IsTrue(IsEqual(Yt, 0.00062660096305156118));

         // Ductility ratio
         IndexType i = MinIndex(fabs(Yl), fabs(Yc), fabs(Yd), fabs(Yt)); // want least curvature
         Float64 Mn = (i == 0 ? Ml : i == 1 ? Mc : i == 2 ? Md : Mt);
         Float64 Yn = (i == 0 ? Yl : i == 1 ? Yc : i == 2 ? Yd : Yt);
         Float64 mu = Yn / Ysl;
         Assert::IsTrue(IsEqual(mu, 2.8440799110719439)); // 2.14 from FHWA example slides

         Float64 phi = 0.75 + 0.15 * (mu - 1.0) / (3.0 - 1.0);
         phi = ::ForceIntoRange(0.75, phi, 0.90);
         Assert::IsTrue(IsEqual(phi, 0.88830599333039584)); // 0.83 from FHWA example slides
      }

		TEST_METHOD(Test3)
		{
         WBFL::Units::AutoSystem as;

         CComPtr<IUnitServer> unit_server;
         unit_server.CoCreateInstance(CLSID_UnitServer);
         unit_server->SetSystemUnits(CComBSTR("12kslug"), CComBSTR("in"), CComBSTR("sec"), CComBSTR("F"), CComBSTR("deg"));
         WBFL::Units::System::SetMassUnit(WBFL::Units::Measure::_12KSlug);
         WBFL::Units::System::SetLengthUnit(WBFL::Units::Measure::Inch);
         WBFL::Units::System::SetTimeUnit(WBFL::Units::Measure::Second);

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
         beam->put_T(3.5);
         beam->put_W1(21);
         beam->put_W2(27);

         Float64 h;
         beam->get_Height(&h);

         CComPtr<IPoint2d> origin;
         origin.CoCreateInstance(CLSID_Point2d);

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
         pnt1->Move(0.0, -h + 2);
         layer1->putref_Centroid(pnt1);
         CComQIPtr<IShape> layer1_shape(layer1);

         CComPtr<IGenericShape> layer2;
         layer2.CoCreateInstance(CLSID_GenericShape);
         layer2->put_Area(13 * 0.294);
         CComPtr<IPoint2d> pnt2;
         pnt2.CoCreateInstance(CLSID_Point2d);
         pnt2->Move(0.0, -h + 4);
         layer2->putref_Centroid(pnt2);
         CComQIPtr<IShape> layer2_shape(layer2);

         CComPtr<IGenericShape> layer3;
         layer3.CoCreateInstance(CLSID_GenericShape);
         layer3->put_Area(13 * 0.294);
         CComPtr<IPoint2d> pnt3;
         pnt3.CoCreateInstance(CLSID_Point2d);
         pnt3->Move(0.0, -h + 6);
         layer3->putref_Centroid(pnt3);
         CComQIPtr<IShape> layer3_shape(layer3);

         CComPtr<IGenericShape> layer4;
         layer4.CoCreateInstance(CLSID_GenericShape);
         layer4->put_Area(9 * 0.294);
         CComPtr<IPoint2d> pnt4;
         pnt4.CoCreateInstance(CLSID_Point2d);
         pnt4->Move(0.0, -h + 8);
         layer4->putref_Centroid(pnt4);
         CComQIPtr<IShape> layer4_shape(layer4);

         CComPtr<IGenericShape> layer5;
         layer5.CoCreateInstance(CLSID_GenericShape);
         layer5->put_Area(5 * 0.294);
         CComPtr<IPoint2d> pnt5;
         pnt5.CoCreateInstance(CLSID_Point2d);
         pnt5->Move(0.0, -h + 10);
         layer5->putref_Centroid(pnt5);
         CComQIPtr<IShape> layer5_shape(layer5);

         CComPtr<IGenericShape> layer6;
         layer6.CoCreateInstance(CLSID_GenericShape);
         layer6->put_Area(1 * 0.294);
         CComPtr<IPoint2d> pnt6;
         pnt6.CoCreateInstance(CLSID_Point2d);
         pnt6->Move(0.0, -h + 12);
         layer6->putref_Centroid(pnt6);
         CComQIPtr<IShape> layer6_shape(layer6);

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
         p3->Move(0, 10, -1.33 / 3950); // 1.33 ksi compression at top of deck at Service III (see slide 33)
         p1->Move(-10000, 0, -0.88 / 3950); // 0.88 ksi compression bottom of deck at Service III (see slide 33)
         p2->Move(10000, 0, -0.88 / 3950);
         deck_initial_strain->ThroughPoints(p1, p2, p3);

         // Girder
         CComPtr<IPlane3d> girder_initial_strain;
         girder_initial_strain.CoCreateInstance(CLSID_Plane3d);
         p1.Release(); p2.Release(); p3.Release();
         p1.CoCreateInstance(CLSID_Point3d);
         p2.CoCreateInstance(CLSID_Point3d);
         p3.CoCreateInstance(CLSID_Point3d);
         p1->Move(-10000, 0, -11.02 / 6933); // 11.02 ksi compression at top of girder at Service III (see slide 33)
         p2->Move(10000, 0, -11.02 / 6933);
         p3->Move(0, -h, 0.99 / 6933); // 0.99 ksi tension at bottom of girder at Service III (see slide 33)
         girder_initial_strain->ThroughPoints(p1, p2, p3);

         Float64 ei = 166.2 / 28500; // fps = 166.2 ksi at Service III (see slide 33)
         CComPtr<IPlane3d> strand_initial_strain;
         strand_initial_strain.CoCreateInstance(CLSID_Plane3d);
         strand_initial_strain->ThroughAltitude(ei);

         // Get a general section
         CComPtr<IGeneralSection> section;
         Assert::AreEqual(S_OK, section.CoCreateInstance(CLSID_GeneralSection));

         section->AddShape(CComBSTR("Deck"), deck_shape, ss_deck_concrete, nullptr, deck_initial_strain, 1.0, VARIANT_FALSE);
         section->AddShape(CComBSTR("Haunch"), haunch_shape, ss_deck_concrete, nullptr, deck_initial_strain, 1.0, VARIANT_FALSE);
         section->AddShape(CComBSTR("Girder"), beam_shape, ss_girder_concrete, nullptr, girder_initial_strain, 1.0, VARIANT_TRUE);
         section->AddShape(CComBSTR("Strand Layer 1"), layer1_shape, ss_strand, nullptr, strand_initial_strain, 1.0, VARIANT_FALSE);
         section->AddShape(CComBSTR("Strand Layer 2"), layer2_shape, ss_strand, nullptr, strand_initial_strain, 1.0, VARIANT_FALSE);
         section->AddShape(CComBSTR("Strand Layer 3"), layer3_shape, ss_strand, nullptr, strand_initial_strain, 1.0, VARIANT_FALSE);
         section->AddShape(CComBSTR("Strand Layer 4"), layer4_shape, ss_strand, nullptr, strand_initial_strain, 1.0, VARIANT_FALSE);
         section->AddShape(CComBSTR("Strand Layer 5"), layer5_shape, ss_strand, nullptr, strand_initial_strain, 1.0, VARIANT_FALSE);
         section->AddShape(CComBSTR("Strand Layer 6"), layer6_shape, ss_strand, nullptr, strand_initial_strain, 1.0, VARIANT_FALSE);

         CComPtr<IMomentCapacitySolver> solver;
         Assert::AreEqual(S_OK, solver.CoCreateInstance(CLSID_MomentCapacitySolver));

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
         Assert::IsTrue(SUCCEEDED(solver->Solve(0.00, 0.00, esl - ei, Y, smFixedStrain, &solution)));

         Float64 Fz, Mx, My;
         CComPtr<IPlane3d> strainPlane;
         solution->get_Fz(&Fz);
         solution->get_Mx(&Mx);
         solution->get_My(&My);
         solution->get_IncrementalStrainPlane(&strainPlane);

         Assert::IsTrue(IsZero(Fz, 0.001));
         Assert::IsTrue(IsEqual(Mx, -164299.60969484772)); //-164292.0 = 13691 k-ft from FHWA example slides
         Assert::IsTrue(IsZero(My));
         Float64 Msl = -Mx;

         Float64 ec = GetStrain(strainPlane, girder_initial_strain, 0.00, Y);
         Float64 _ec;
         girder_initial_strain->GetZ(0, Y, &_ec); // initial strain in girder concrete
         Assert::IsTrue(IsEqual(ec - _ec, esl - ei));

         CComPtr<IGeneralSectionSolution> general_solution;
         solution->get_GeneralSectionSolution(&general_solution);
         CComPtr<IUnkArray> slices;
         general_solution->FindSlices(3, &slices); // shape 3 is the lowest strand
         IndexType nSlices;
         slices->get_Count(&nSlices);
         Assert::AreEqual((IndexType)1, nSlices);
         CComPtr<IUnknown> punk;
         slices->get_Item(0, &punk);
         CComQIPtr<IGeneralSectionSlice> slice(punk);
         slice->get_TotalStrain(&ec);
         Assert::IsTrue(IsEqual(ec, esl));

         Float64 c;
         solution->get_DepthToNeutralAxis(&c); // location of neutral axis below top of girder
         Assert::IsTrue(IsEqual(c, 41.946997318037461)); // 40.7" from top of girder from FHWA example slides

         ec = GetStrain(strainPlane, girder_initial_strain, 0.00, -h); // strain at bottom of girder
         Assert::IsTrue(IsEqual(ec, 0.0011746386224908293)); // 0.00127 from FHWA example slides

         Float64 Ysl;
         solution->get_Curvature(&Ysl);
         Assert::IsTrue(IsEqual(Ysl, 5.3264339529218973e-05)); // 0.0000545 from FHWA example slides

         // Nominal moment capacity at crack localization, Ml and Yl (slide 51)
         solution.Release();
         Assert::IsTrue(SUCCEEDED(solver->Solve(0.00, 0.00, 0.0045 - 0.99 / 6933, 0.0, smFixedTensionStrain, &solution)));

         strainPlane.Release();
         solution->get_Fz(&Fz);
         solution->get_Mx(&Mx);
         solution->get_My(&My);
         solution->get_IncrementalStrainPlane(&strainPlane);

         Assert::IsTrue(IsZero(Fz, 0.001));
         Assert::IsTrue(IsEqual(Mx, -218718.17250680181)); // -215664.0 = 17972 k-ft from FHWA example slides
         Assert::IsTrue(IsZero(My));
         Float64 Ml = -Mx;

         ec = GetStrain(strainPlane, girder_initial_strain, 0.00, -h);
         Assert::IsTrue(IsEqual(ec, 0.0045));

         solution->get_DepthToNeutralAxis(&c); // location of neutral axis below top of girder
         Assert::IsTrue(IsEqual(c, 25.742792233456491)); // 25.5" from top of girder from FHWA example slides

         Float64 Yl;
         solution->get_Curvature(&Yl);
         Assert::IsTrue(IsEqual(Yl, 0.00011762489378368373)); // 0.0001167 from FHWN example slides

         // Nominal moment capacity at compression strain limit in UHPC section, Mc, Yc
         // fixed strain at top of girder (not top of section/top of deck)
         // this case not in FHWA example
         solution.Release();
         Assert::AreEqual(RC_E_MATERIALFAILURE, solver->Solve(0.00, 0.00, -0.0035 + 11.02 / 6933, 0.0, smFixedStrain, &solution)); // strain in deck concrete exceeds crushing limit of -0.003

         strainPlane.Release();
         solution->get_Fz(&Fz);
         solution->get_Mx(&Mx);
         solution->get_My(&My);
         solution->get_IncrementalStrainPlane(&strainPlane);

         Assert::IsTrue(IsZero(Fz, 0.001));
         Assert::IsTrue(IsEqual(Mx, -223615.85443648885));
         Assert::IsTrue(IsZero(My));
         Float64 Mc = -Mx;

         ec = GetStrain(strainPlane, girder_initial_strain, 0.00, 10.00); // strain at top of deck
         Assert::IsTrue(IsEqual(ec, -0.010120459978493181));

         ec = GetStrain(strainPlane, girder_initial_strain, 0.00, -h); // strain at bottom of beam
         Assert::IsTrue(IsEqual(ec, 0.032250483883863174));

         ec = GetStrain(strainPlane, girder_initial_strain, 0.00, 0.00);
         Assert::IsTrue(IsEqual(ec, -0.0035));

         solution->get_DepthToNeutralAxis(&c); // location of neutral axis
         Assert::IsTrue(IsEqual(c, 15.286641730891638));

         Float64 Yc;
         solution->get_Curvature(&Yc);
         Assert::IsTrue(IsEqual(Yc, 0.00066204599784931793));

         // Nominal moment capacity at compression strain limit in deck, Md, Yd
         // this case not in FHWA example
         solution.Release();
         Assert::AreEqual(S_OK, solver->Solve(0.00, 0.00, -0.003 + 1.33 / 3950, 0.0, smFixedCompressionStrain, &solution));

         strainPlane.Release();
         solution->get_Fz(&Fz);
         solution->get_Mx(&Mx);
         solution->get_My(&My);
         solution->get_IncrementalStrainPlane(&strainPlane);

         Assert::IsTrue(IsZero(Fz, 0.001));
         Assert::IsTrue(IsEqual(Mx, -220305.78201001100));
         Assert::IsTrue(IsZero(My));
         Float64 Md = -Mx;

         ec = GetStrain(strainPlane, girder_initial_strain, 0.00, 10.0); // this is at top of deck, using girder strain plane
         girder_initial_strain->GetZ(0, 10.0, &_ec); // initial strain in girder concrete
         ec -= _ec; // remove effect of girder initial strain
         deck_initial_strain->GetZ(0, 10., &_ec);
         ec += _ec; // add effect of deck initial strain
         Assert::IsTrue(IsEqual(ec, -0.003));

         solution->get_DepthToNeutralAxis(&c); // location of neutral axis
         Assert::IsTrue(IsEqual(c, 16.568688039937388));

         Float64 Yd;
         solution->get_Curvature(&Yd);
         Assert::IsTrue(IsEqual(Yd, 0.00027603790721190372));

         // Nominal moment capacity at maximum usable strain of reinforcement, Mt, Yt
         // this case not in FHWA example
         solution.Release();
         Assert::AreEqual(RC_E_MATERIALFAILURE, solver->Solve(0.00, 0.00, 0.035 - ei, Y, smFixedStrain, &solution)); // strain exceeds crushing strain of UHPC

         strainPlane.Release();
         solution->get_Fz(&Fz);
         solution->get_Mx(&Mx);
         solution->get_My(&My);
         solution->get_IncrementalStrainPlane(&strainPlane);

         Assert::IsTrue(IsZero(Fz, 0.001));
         Assert::IsTrue(IsEqual(Mx, -223660.09719678111));
         Assert::IsTrue(IsZero(My));
         Float64 Mt = -Mx;

         ec = GetStrain(strainPlane, girder_initial_strain, 0.00, Y); // strain in girder concrete
         girder_initial_strain->GetZ(0, Y, &_ec); // initial strain in girder concrete
         Assert::IsTrue(IsEqual(ec - _ec, 0.035 - ei));

         general_solution.Release();
         solution->get_GeneralSectionSolution(&general_solution);
         slices.Release();
         general_solution->FindSlices(3, &slices); // shape 3 is the lowest strand
         slices->get_Count(&nSlices);
         Assert::AreEqual((IndexType)1, nSlices);
         punk.Release();
         slices->get_Item(0, &punk);
         slice.Release();
         punk.QueryInterface(&slice);
         slice->get_TotalStrain(&ec);
         Assert::IsTrue(IsEqual(ec, 0.035));

         solution->get_DepthToNeutralAxis(&c); // location of neutral axis
         Assert::IsTrue(IsEqual(c, 15.402116635752412));

         Float64 Yt;
         solution->get_Curvature(&Yt);
         Assert::IsTrue(IsEqual(Yt, 0.00062764776423929549));

         // Ductility ratio
         IndexType i = MinIndex(fabs(Yl), fabs(Yc), fabs(Yd), fabs(Yt)); // want least curvature
         Float64 Mn = (i == 0 ? Ml : i == 1 ? Mc : i == 2 ? Md : Mt);
         Float64 Yn = (i == 0 ? Yl : i == 1 ? Yc : i == 2 ? Yd : Yt);
         Float64 mu = Yn / Ysl;
         Assert::IsTrue(IsEqual(mu, 2.2083235204514042)); // 2.14 from FHWA example slides

         Float64 phi = 0.75 + 0.15 * (mu - 1.0) / (3.0 - 1.0);
         phi = ::ForceIntoRange(0.75, phi, 0.90);
         Assert::IsTrue(IsEqual(phi, 0.84062426403385526)); // 0.83 from FHWA example
      }

		TEST_METHOD(Test4)
		{
         // Test cases from "Analysis of a Rectangular Mild Steel Reinforced UHPC Beam", FHWA, Graybeal, et. al.

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
         CComPtr<IUHPConcrete> concrete;
         concrete.CoCreateInstance(CLSID_UHPConcrete);
         CComQIPtr<ISupportUnitServer> sus(concrete);
         sus->putref_UnitServer(unit_server);
         Float64 ecu = -0.0035;
         Float64 etcr = 0.000147;
         Float64 etloc = 0.003;
         Float64 esl = 0.00166;
         Float64 esy = 0.00207;
         Float64 esu = 0.09;
         concrete->put_fc(22.0); // 22 KSI concrete
         concrete->put_ecu(ecu);
         concrete->put_ftcr(1.2);
         concrete->put_ftloc(1.2);
         concrete->put_etloc(etloc);

         // rebar
         CComPtr<IRebarModel> rebar;
         rebar.CoCreateInstance(CLSID_RebarModel);
         rebar->Init(60., 29000., 0.09);

         // main beam
         Float64 H = WBFL::Units::ConvertToSysUnits(24, WBFL::Units::Measure::Inch);
         Float64 W = WBFL::Units::ConvertToSysUnits(12, WBFL::Units::Measure::Inch);
         CComPtr<IRectangle> beam;
         beam.CoCreateInstance(CLSID_Rect);
         beam->put_Height(H);
         beam->put_Width(W);

         // #11 rebar
         Float64 Ab = 1.56;
         Float64 Db = H / 2 - WBFL::Units::ConvertToSysUnits(21.795, WBFL::Units::Measure::Inch);
         CComPtr<IPoint2d> center;

         CComPtr<IGenericShape> bar1;
         bar1.CoCreateInstance(CLSID_GenericShape);
         bar1->put_Area(Ab);
         center.Release();
         bar1->get_Centroid(&center);
         center->Move(W / 2 - 2, Db);

         CComPtr<IGenericShape> bar2;
         bar2.CoCreateInstance(CLSID_GenericShape);
         bar2->put_Area(Ab);
         center.Release();
         bar2->get_Centroid(&center);
         center->Move(0, Db);

         CComPtr<IGenericShape> bar3;
         bar3.CoCreateInstance(CLSID_GenericShape);
         bar3->put_Area(Ab);
         center.Release();
         bar3->get_Centroid(&center);
         center->Move(-(W / 2 - 2), Db);

         CComQIPtr<IShape> shape1(beam);
         CComQIPtr<IShape> shape2(bar1);
         CComQIPtr<IShape> shape3(bar2);
         CComQIPtr<IShape> shape4(bar3);

         CComQIPtr<IStressStrain> material1(concrete);
         CComQIPtr<IStressStrain> material2(rebar);

         section->AddShape(CComBSTR("Beam"), shape1, material1, nullptr, nullptr, 1.0, VARIANT_TRUE); // beam
         section->AddShape(CComBSTR("Bar 1"), shape2, material2, nullptr, nullptr, 1.0, VARIANT_FALSE); // bar 1
         section->AddShape(CComBSTR("Bar 2"), shape3, material2, nullptr, nullptr, 1.0, VARIANT_FALSE); // bar 2
         section->AddShape(CComBSTR("Bar 3"), shape4, material2, nullptr, nullptr, 1.0, VARIANT_FALSE); // bar 3

         CComPtr<IMomentCapacitySolver> solver;
         Assert::AreEqual(S_OK, solver.CoCreateInstance(CLSID_MomentCapacitySolver));

         solver->put_Slices(100);
         solver->put_SliceGrowthFactor(0);
         solver->put_AxialTolerance(0.001);
         solver->putref_Section(section);

         CComPtr<IPlane3d> strainPlane;
         section->get_InitialStrain(0, &strainPlane);

         // First crack in UHPC
         CComPtr<IMomentCapacitySolution> solution;
         Float64 Fz, Mx, My;
         CComPtr<IPlane3d> incrementalStrainPlane;
         Assert::IsTrue(SUCCEEDED(solver->Solve(0.00, 0.00, etcr, -H / 2, smFixedStrain, &solution)));

         solution->get_Fz(&Fz);
         solution->get_Mx(&Mx);
         solution->get_My(&My);

         Mx = WBFL::Units::ConvertFromSysUnits(Mx, WBFL::Units::Measure::KipFeet);

         Assert::IsTrue(IsZero(Fz, 0.001));
         Assert::IsTrue(IsEqual(Mx, -116.3116654));
         Assert::IsTrue(IsZero(My));

         Float64 c;
         solution->get_DepthToNeutralAxis(&c);
         Assert::IsTrue(IsEqual(c, 12.623387));

         Float64 dc;
         solution->get_DepthToCompressionResultant(&dc);
         Assert::IsTrue(IsEqual(dc, 4.2100597));

         Float64 de;
         solution->get_DepthToTensionResultant(&de);
         Assert::IsTrue(IsEqual(de, 20.5051832));

         Float64 moment_arm;
         solution->get_MomentArm(&moment_arm);
         Assert::IsTrue(IsEqual(moment_arm, de - dc));

         Float64 k;
         solution->get_Curvature(&k);
         Assert::IsTrue(IsEqual(k, 0.0000129212444, 0.00000001));

         incrementalStrainPlane.Release();
         solution->get_IncrementalStrainPlane(&incrementalStrainPlane);
         Float64 ec;
         incrementalStrainPlane->GetZ(0.0, -H / 2, &ec);
         Assert::IsTrue(IsEqual(ec, etcr));

         // Steel Service
         solution.Release();
         Assert::IsTrue(SUCCEEDED(solver->Solve(0.00, 0.00, esl, Db, smFixedStrain, &solution)));

         solution->get_Fz(&Fz);
         solution->get_Mx(&Mx);
         solution->get_My(&My);

         Mx = WBFL::Units::ConvertFromSysUnits(Mx, WBFL::Units::Measure::KipFeet);

         Assert::IsTrue(IsEqual(Mx, -591.34970272877001));
         Assert::IsTrue(IsZero(My));
         Assert::IsTrue(IsZero(Fz, 0.001));

         solution->get_DepthToNeutralAxis(&c);
         Assert::IsTrue(IsEqual(c, 8.9626174836075307));

         solution->get_DepthToCompressionResultant(&dc);
         Assert::IsTrue(IsEqual(dc, 2.9910195801700095));

         solution->get_DepthToTensionResultant(&de);
         Assert::IsTrue(IsEqual(de, 19.406907222621740));

         solution->get_MomentArm(&moment_arm);
         Assert::IsTrue(IsEqual(moment_arm, de - dc));

         solution->get_Curvature(&k);
         Assert::IsTrue(IsEqual(k, 0.00012936023360272077));

         incrementalStrainPlane.Release();
         solution->get_IncrementalStrainPlane(&incrementalStrainPlane);
         incrementalStrainPlane->GetZ(0.0, Db, &ec);
         Assert::IsTrue(IsEqual(ec, esl));

         // Steel Yield
         solution.Release();
         Assert::IsTrue(SUCCEEDED(solver->Solve(0.00, 0.00, esy, Db, smFixedStrain, &solution)));

         solution->get_Fz(&Fz);
         solution->get_Mx(&Mx);
         solution->get_My(&My);

         Mx = WBFL::Units::ConvertFromSysUnits(Mx, WBFL::Units::Measure::KipFeet);

         Assert::IsTrue(IsZero(Fz, 0.001));
         Assert::IsTrue(IsEqual(Mx, -685.64719986516229));
         Assert::IsTrue(IsZero(My));

         solution->get_DepthToNeutralAxis(&c);
         Assert::IsTrue(IsEqual(c, 8.6738076792667496));

         solution->get_DepthToCompressionResultant(&dc);
         Assert::IsTrue(IsEqual(dc, 2.8949297089456589));

         solution->get_DepthToTensionResultant(&de);
         Assert::IsTrue(IsEqual(de, 19.558750550402124));

         solution->get_MomentArm(&moment_arm);
         Assert::IsTrue(IsEqual(moment_arm, de - dc));

         solution->get_Curvature(&k);
         Assert::IsTrue(IsEqual(k, 0.00015776005330926540));

         incrementalStrainPlane.Release();
         solution->get_IncrementalStrainPlane(&incrementalStrainPlane);
         incrementalStrainPlane->GetZ(0.0, Db, &ec);
         Assert::IsTrue(IsEqual(ec, esy));

         // UHPC Localization
         solution.Release();
         Assert::IsTrue(SUCCEEDED(solver->Solve(0.00, 0.00, etloc, -H / 2, smFixedStrain, &solution)));

         solution->get_Fz(&Fz);
         solution->get_Mx(&Mx);
         solution->get_My(&My);

         Mx = WBFL::Units::ConvertFromSysUnits(Mx, WBFL::Units::Measure::KipFeet);

         Assert::IsTrue(IsZero(Fz, 0.001));
         Assert::IsTrue(IsEqual(Mx, -699.68265568280799));
         Assert::IsTrue(IsZero(My));

         solution->get_DepthToNeutralAxis(&c);
         Assert::IsTrue(IsEqual(c, 8.0319504415745406));

         solution->get_DepthToCompressionResultant(&dc);
         Assert::IsTrue(IsEqual(dc, 2.6812903791657474));

         solution->get_DepthToTensionResultant(&de);
         Assert::IsTrue(IsEqual(de, 19.333818953013445));

         solution->get_MomentArm(&moment_arm);
         Assert::IsTrue(IsEqual(moment_arm, de - dc));

         solution->get_Curvature(&k);
         Assert::IsTrue(IsEqual(k, 0.00018787516841197826));

         incrementalStrainPlane.Release();
         solution->get_IncrementalStrainPlane(&incrementalStrainPlane);
         incrementalStrainPlane->GetZ(0.0, -H / 2, &ec);
         Assert::IsTrue(IsEqual(ec, etloc));

         // Compression crushing of UHPC
         solution.Release();
         Assert::IsTrue(SUCCEEDED(solver->Solve(0.00, 0.00, ecu, 0.0, smFixedCompressionStrain, &solution)));

         solution->get_Fz(&Fz);
         solution->get_Mx(&Mx);
         solution->get_My(&My);

         Mx = WBFL::Units::ConvertFromSysUnits(Mx, WBFL::Units::Measure::KipFeet);

         Assert::IsTrue(IsZero(Fz, 0.001));
         Assert::IsTrue(IsEqual(Mx, -496.99875340434454));
         Assert::IsTrue(IsZero(My));

         solution->get_DepthToNeutralAxis(&c);
         Assert::IsTrue(IsEqual(c, 2.2295543700228020));

         solution->get_DepthToCompressionResultant(&dc);
         Assert::IsTrue(IsEqual(dc, 0.78735338433768653));

         solution->get_DepthToTensionResultant(&de);
         Assert::IsTrue(IsEqual(de, 20.175863643178488));

         solution->get_MomentArm(&moment_arm);
         Assert::IsTrue(IsEqual(moment_arm, de - dc));

         solution->get_Curvature(&k);
         Assert::IsTrue(IsEqual(k, 0.0015698204300638840));

         incrementalStrainPlane.Release();
         solution->get_IncrementalStrainPlane(&incrementalStrainPlane);
         incrementalStrainPlane->GetZ(0.0, H / 2, &ec);
         Assert::IsTrue(IsEqual(ec, ecu));
      }
	};
}
