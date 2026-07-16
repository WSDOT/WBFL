#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace
{
   void CheckSolution(IRCSolution* pSolution, Float64 c, Float64 Mn, Float64 Cflange, Float64 Cweb, Float64 Yflange, Float64 Yweb, Float64 T, Float64 fps, VARIANT_BOOL bIsOverReinforced)
   {
      Float64 val;

      pSolution->get_NeutralAxisDepth(&val);
      Assert::IsTrue(IsEqual(val, c, 0.01));

      pSolution->get_Mn(&val);
      Assert::IsTrue(IsEqual(val, Mn, 0.01));

      pSolution->get_Cflange(&val);
      Assert::IsTrue(IsEqual(val, Cflange, 0.01));

      pSolution->get_Cweb(&val);
      Assert::IsTrue(IsEqual(val, Cweb, 0.01));

      pSolution->get_Yflange(&val);
      Assert::IsTrue(IsEqual(val, Yflange, 0.01));

      pSolution->get_Yweb(&val);
      Assert::IsTrue(IsEqual(val, Yweb, 0.01));

      pSolution->get_T(&val);
      Assert::IsTrue(IsEqual(val, T, 0.01));

      pSolution->get_fps(&val);
      Assert::IsTrue(IsEqual(val, fps, 0.02));

      VARIANT_BOOL bVal;
      pSolution->get_IsOverReinforced(&bVal);
      Assert::AreEqual((int)bIsOverReinforced, (int)bVal);
   }

   void CheckSolution(IRCSolutionEx* pSolution, Float64 c, Float64 Mn, Float64 Cflange, Float64 Cweb, Float64 Yflange, Float64 Yweb, Float64 T)
   {
      Float64 val;

      pSolution->get_NeutralAxisDepth(&val);
      Assert::IsTrue(IsEqual(val, c, 0.01));

      pSolution->get_Mn(&val);
      Assert::IsTrue(IsEqual(val, Mn, 0.01));

      pSolution->get_Cflange(&val);
      Assert::IsTrue(IsEqual(val, Cflange, 0.01));

      pSolution->get_Cweb(&val);
      Assert::IsTrue(IsEqual(val, Cweb, 0.01));

      pSolution->get_Yflange(&val);
      Assert::IsTrue(IsEqual(val, Yflange, 0.01));

      pSolution->get_Yweb(&val);
      Assert::IsTrue(IsEqual(val, Yweb, 0.01));

      pSolution->get_T(&val);
      Assert::IsTrue(IsEqual(val, T, 0.01));
   }
}

namespace RCCapacityUnitTest
{
	TEST_CLASS(TestSolver)
	{
	public:

		TEST_METHOD(Test1)
		{
         CComPtr<IRCBeam> beam;
         beam.CoCreateInstance(CLSID_RCBeam);

         CComQIPtr<ISupportUnitServer> sus(beam);
         CComPtr<IUnitServer> unitServer;
         sus->get_UnitServer(&unitServer);

         CComPtr<IUnitConvert> convert;
         unitServer->get_UnitConvert(&convert);

         Float64 Aps = 4.0; // in^2
         convert->ConvertToBaseUnits(Aps, CComBSTR("in^2"), &Aps);
         beam->put_Aps(Aps);

         CComPtr<IRCSolution> solution;

         CComPtr<INLSolver> nlSolver;
         nlSolver.CoCreateInstance(CLSID_NLSolver);
         nlSolver->Solve(beam, &solution);
         CheckSolution(solution, 0.12497372600349774, 7677643.9373881808, 4804079.3449505707, 0, 0.052849056589320931, 0, 4804079.3444824815, 1861584469.1559, VARIANT_FALSE);

         solution.Release();

         CComPtr<IPCISolver> pciSolver;
         pciSolver.CoCreateInstance(CLSID_PCISolver);
         pciSolver->Solve(beam, &solution);
         CheckSolution(solution, 0.13183391003435302, 7662365.2579992665, 4804079.3444734057, 0.0, 0.056029411764600030, 0.0, 4804079.3444824815, 1861584469.1559000, VARIANT_FALSE);

         solution.Release();

         CComPtr<ILRFDSolver> lrfdSolver;
         lrfdSolver.CoCreateInstance(CLSID_LRFDSolver);
         lrfdSolver->Solve(beam, &solution);
         CheckSolution(solution, 0.12895079406405, 7500552.4763888, 4699017.4686854, 0, 0.054804087477219, 0, 4699017.4686854, 1820872910.8614, VARIANT_FALSE);

         solution.Release();

         CComPtr<ILRFDSolver2> lrfdSolver2;
         lrfdSolver2.CoCreateInstance(CLSID_LRFDSolver2);
         lrfdSolver2->Solve(beam, &solution);
         CheckSolution(solution, 0.12928927678176022, 7519562.9114392512, 4711351.9115628917, 0, 0.054947942632248094, 0, 4711351.9115664093, 1825652517.0370178, VARIANT_FALSE);

         solution.Release();

         CComPtr<ILFDSolver> lfdSolver;
         lfdSolver.CoCreateInstance(CLSID_LFDSolver);
         lfdSolver->Solve(beam, &solution);
         CheckSolution(solution, 0.12932846921042, 7521763.8732139, 4712780.0990217, 0, 0.054964599414426, 0, 4712780.0990217, 1826205940.7828, VARIANT_FALSE);

         solution.Release();

         CComPtr<IMixedSolver> mixedSolver;
         mixedSolver.CoCreateInstance(CLSID_MixedSolver);
         mixedSolver->Solve(beam, &solution);
         CheckSolution(solution, 0.12895079406405, 7500552.4763888, 4699017.4686854, 0, 0.054804087477219, 0, 4699017.4686854, 1820872910.8614, VARIANT_FALSE);

         convert->ConvertToBaseUnits(8.0, CComBSTR("in^2"), &Aps);
         beam->put_Aps(Aps);

         solution.Release();
         nlSolver->Solve(beam, &solution);
         CheckSolution(solution, 0.58342741152486988, 13412665.600382978, 6864785.9459429123, 1947480.2789649768, 0.078479091530920808, 0.30688052599000359, 8812266.2247003336, 1707379995.7956812, VARIANT_FALSE);

         solution.Release();
         pciSolver->Solve(beam, &solution);
         CheckSolution(solution, 0.61594128172794, 13176985.396502, 6533547.9084962, 2180934.7612839, 0.076200000000000, 0.32681818517927, 8714482.6697877, 1688434394.1402, VARIANT_FALSE);

         solution.Release();
         lrfdSolver->Solve(beam, &solution);
         CheckSolution(solution, 0.96812146197817, 10860413.604265, -1.0000000000000, -1.0000000000000, -1.0000000000000, -1.0000000000000, -1.0000000000000, 1555935065.2764, VARIANT_TRUE);

         solution.Release();
         lfdSolver->Solve(beam, &solution);
         CheckSolution(solution, 1.0715173871518, 12275155.400631, -1.0000000000000, -1.0000000000000, -1.0000000000000, -1.0000000000000, -1.0000000000000, 1790827412.4097, VARIANT_TRUE);

         solution.Release();
         mixedSolver->Solve(beam, &solution);
         CheckSolution(solution, 0.77559535769964, 12275155.400631, -1.0000000000000, -1.0000000000000, -1.0000000000000, -1.0000000000000, -1.0000000000000, 1616718232.7973, VARIANT_TRUE);

         beam->put_Aps(0.0); // No reinforcement, no capacity

         solution.Release();
         nlSolver->Solve(beam, &solution);
         CheckSolution(solution, 0, 0, 0, 0, 0, 0, 0, 0, VARIANT_FALSE);

         solution.Release();
         pciSolver->Solve(beam, &solution);
         CheckSolution(solution, 0, 0, 0, 0, 0, 0, 0, 0, VARIANT_FALSE);

         solution.Release();
         lrfdSolver->Solve(beam, &solution);
         CheckSolution(solution, 0, 0, 0, 0, 0, 0, 0, 0, VARIANT_FALSE);

         solution.Release();
         lfdSolver->Solve(beam, &solution);
         CheckSolution(solution, 0, 0, 0, 0, 0, 0, 0, 0, VARIANT_FALSE);

         solution.Release();
         mixedSolver->Solve(beam, &solution);
         CheckSolution(solution, 0, 0, 0, 0, 0, 0, 0, 0, VARIANT_FALSE);
      }

		TEST_METHOD(Test2)
		{
         CComPtr<IRCBeam2Ex> beam;
         beam.CoCreateInstance(CLSID_RCBeam2Ex);

         CComQIPtr<ISupportUnitServer> sus(beam);
         CComPtr<IUnitServer> unitServer;
         sus->get_UnitServer(&unitServer);

         CComPtr<IUnitConvert> convert;
         unitServer->get_UnitConvert(&convert);

         Float64 b = 72;
         convert->ConvertToBaseUnits(b, CComBSTR("in"), &b);
         beam->put_b(b);

         Float64 hf = 6;
         convert->ConvertToBaseUnits(hf, CComBSTR("in"), &hf);
         beam->put_hf(hf);

         CComPtr<IPrecastBeam> beamShape;
         beamShape.CoCreateInstance(CLSID_PrecastBeam);

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
         convert->ConvertToBaseUnits(W1, CComBSTR("in"), &W1);
         convert->ConvertToBaseUnits(W2, CComBSTR("in"), &W2);
         convert->ConvertToBaseUnits(W3, CComBSTR("in"), &W3);
         convert->ConvertToBaseUnits(W4, CComBSTR("in"), &W4);
         convert->ConvertToBaseUnits(D1, CComBSTR("in"), &D1);
         convert->ConvertToBaseUnits(D2, CComBSTR("in"), &D2);
         convert->ConvertToBaseUnits(D3, CComBSTR("in"), &D3);
         convert->ConvertToBaseUnits(D4, CComBSTR("in"), &D4);
         convert->ConvertToBaseUnits(D5, CComBSTR("in"), &D5);
         convert->ConvertToBaseUnits(D6, CComBSTR("in"), &D6);
         convert->ConvertToBaseUnits(D7, CComBSTR("in"), &D7);
         convert->ConvertToBaseUnits(T1, CComBSTR("in"), &T1);
         convert->ConvertToBaseUnits(T2, CComBSTR("in"), &T2);
         beamShape->put_W1(W1);
         beamShape->put_W2(W2);
         beamShape->put_W3(W3);
         beamShape->put_W4(W4);
         beamShape->put_D1(D1);
         beamShape->put_D2(D2);
         beamShape->put_D3(D3);
         beamShape->put_D4(D4);
         beamShape->put_D5(D5);
         beamShape->put_D6(D6);
         beamShape->put_D7(D7);
         beamShape->put_T1(T1);
         beamShape->put_T2(T2);

         CComQIPtr<IShape> shape(beamShape);
         beam->putref_Beam(shape);

         // add some prestress and mild rebar
         Float64 dps, Aps;
         dps = 73.5 - 2;
         convert->ConvertToBaseUnits(dps, CComBSTR("in"), &dps);
         Aps = 10 * 2.16;
         convert->ConvertToBaseUnits(Aps, CComBSTR("in^2"), &Aps);

         beam->AddStrandLayer(dps, Aps, 1.0);
         beam->AddStrandLayer(dps, Aps, 0.2);

         Float64 ds, As;
         ds = 73.5 - 4;
         convert->ConvertToBaseUnits(ds, CComBSTR("in"), &ds);
         As = 4 * 0.31;
         convert->ConvertToBaseUnits(As, CComBSTR("in^2"), &As);

         beam->AddRebarLayer(ds, As, 1.0);
         beam->AddRebarLayer(ds, As, 0.2);

         CComPtr<IRCSolutionEx> solution;

         CComPtr<IRCSolver2Ex> nlSolver;
         nlSolver.CoCreateInstance(CLSID_NLSolver);
         nlSolver->Solve(beam, &solution);
         CheckSolution(solution, 1.8631927943059585, 26615481.212655202, 6414478.5690013198, 12749930.641357977, 0.077026214806171112, 0.60372728156028699, 19164409.209383119);

         solution.Release();

         CComPtr<IRCSolver2Ex> pciSolver;
         pciSolver.CoCreateInstance(CLSID_PCISolver);
         pciSolver->Solve(beam, &solution);
         CheckSolution(solution, 1.9105838018870374, 26559874.054724388, 6533547.9084961740, 12413253.267700991, 0.076199999999999990, 0.59253303508414268, 18946801.176202841);

         // No reinforcement, no capacity
         beam->ClearRebarLayers();
         beam->ClearStrandLayers();

         solution.Release();

         nlSolver->Solve(beam, &solution);
         CheckSolution(solution, 0, 0, 0, 0, 0, 0, 0);

         solution.Release();

         pciSolver->Solve(beam, &solution);
         CheckSolution(solution, 0, 0, 0, 0, 0, 0, 0);

         // Strands not developed, no capacity
         beam->AddStrandLayer(dps, Aps, 0.0);
         beam->AddRebarLayer(ds, As, 0.0);

         solution.Release();

         nlSolver->Solve(beam, &solution);
         CheckSolution(solution, 0, 0, 0, 0, 0, 0, 0);

         solution.Release();

         pciSolver->Solve(beam, &solution);
         CheckSolution(solution, 0, 0, 0, 0, 0, 0, 0);
      }
	};
}
