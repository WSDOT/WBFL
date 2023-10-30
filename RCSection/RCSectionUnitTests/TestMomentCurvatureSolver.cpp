#include "pch.h"
#include "CppUnitTest.h"
#include <GeomModel/GeomModel.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::RCSection;

namespace RCSectionUnitTest
{
	TEST_CLASS(TestMomentCurvatureSolver)
	{
	public:
		
		TEST_METHOD(Test)
		{
         // base units of kip and ksi
         WBFL::Units::AutoSystem au;
         WBFL::Units::System::SetSystemUnits(WBFL::Units::Measure::_12KSlug, WBFL::Units::Measure::Inch, WBFL::Units::Measure::Second, WBFL::Units::Measure::Fahrenheit, WBFL::Units::Measure::Degree);

         std::shared_ptr<GeneralSection> section(std::make_shared<GeneralSection>());

         //
         // materials
         //

         // concrete
         std::shared_ptr<WBFL::Materials::UnconfinedConcreteModel> concrete(std::make_shared<WBFL::Materials::UnconfinedConcreteModel>(_T("Concrete"), 4.0));

         // rebar
         std::shared_ptr<WBFL::Materials::RebarModel> rebar(std::make_shared<WBFL::Materials::RebarModel>(_T("Rebar"), 60.0, 29000.0, 0.11));

         //
         // shapes
         //

         // main beam
         Float64 H = WBFL::Units::ConvertToSysUnits(8, WBFL::Units::Measure::Feet);
         Float64 W = WBFL::Units::ConvertToSysUnits(4, WBFL::Units::Measure::Feet);
         WBFL::Geometry::Rectangle beam;
         beam.SetHeight(H);
         beam.SetWidth(W);

         // #6 rebar
         Float64 radius = 0.74848;
         WBFL::Geometry::Circle bar1(WBFL::Geometry::Point2d((W / 2 - 2), (H / 2 - 2)), radius);
         WBFL::Geometry::Circle bar2(WBFL::Geometry::Point2d(-(W / 2 - 2), (H / 2 - 2)), radius);
         WBFL::Geometry::Circle bar3(WBFL::Geometry::Point2d(-(W / 2 - 2), -(H / 2 - 2)), radius);
         WBFL::Geometry::Circle bar4(WBFL::Geometry::Point2d((W / 2 - 2), -(H / 2 - 2)), radius);

         section->AddShape(_T("Beam"), beam, concrete, nullptr, nullptr, 1.0, true);
         section->AddShape(_T("Bar 1"), bar1, rebar, concrete, nullptr, 1.0);
         section->AddShape(_T("Bar 2"), bar2, rebar, concrete, nullptr, 1.0);
         section->AddShape(_T("Bar 3"), bar3, rebar, concrete, nullptr, 1.0);
         section->AddShape(_T("Bar 4"), bar4, rebar, concrete, nullptr, 1.0);

         MomentCurvatureSolver solver;
         solver.SetSlices(20);
         solver.SetSection(section);

         auto solution = solver.Solve(-200.0, 0.0);

         auto nPoints = solution->GetPointCount();
         Assert::IsTrue(nPoints == 123);

         auto [Mmax, k] = solution->GetPeakCapacity();
         Assert::IsTrue(IsEqual(Mmax, 28986.080336362313));
         Assert::IsTrue(IsEqual(k, 0.0011981250000000024));

         static std::pair<Float64, Float64> datum[] =
         {
            {0, 2.13162820728e-13},
            {1e-05, 15291.7475619},
            {2e-05, 23162.3803357},
            {3e-05, 27718.2460862},
            {4e-05, 27915.354183},
            {5e-05, 28038.6806102},
            {6e-05, 28156.274736},
            {7e-05, 28240.4124038},
            {8e-05, 28302.5339456},
            {9e-05, 28349.3674535},
            {0.0001, 28385.1200555},
            {0.00011, 28412.6094338},
            {0.00012, 28433.7572551},
            {0.00013, 28450.0214192},
            {0.00014, 28462.1571104},
            {0.00015, 28471.1707009},
            {0.00016, 28477.5559778},
            {0.00017, 28481.7884476},
            {0.00018, 28484.146586},
            {0.00019, 28484.9923949},
            {0.0002, 28506.5370903},
            {0.00021, 28526.8725706},
            {0.00022, 28545.7080272},
            {0.00023, 28563.2181486},
            {0.00024, 28579.5473007},
            {0.00025, 28594.8199758},
            {0.00026, 28609.1465573},
            {0.00027, 28622.6107216},
            {0.00028, 28635.3014704},
            {0.00029, 28647.6279896},
            {0.0003, 28658.631236},
            {0.00031, 28669.3868436},
            {0.00032, 28679.6032257},
            {0.00033, 28689.7518031},
            {0.00034, 28698.5869135},
            {0.00035, 28707.5937386},
            {0.00036, 28715.8767259},
            {0.00037, 28723.962842},
            {0.00038, 28731.7131763},
            {0.00039, 28739.1482273},
            {0.0004, 28746.2860414},
            {0.00041, 28753.1473515},
            {0.00042, 28759.7519422},
            {0.00043, 28766.1157481},
            {0.00044, 28772.2526775},
            {0.00045, 28778.1757827},
            {0.00046, 28783.8973446},
            {0.00047, 28789.4287062},
            {0.00048, 28794.8661617},
            {0.00049, 28799.9619363},
            {0.0005, 28804.982489},
            {0.00051, 28809.8502016},
            {0.00052, 28814.5732906},
            {0.00053, 28819.1578046},
            {0.00054, 28823.6115283},
            {0.00055, 28827.9403382},
            {0.00056, 28832.1500549},
            {0.00057, 28836.246124},
            {0.00058, 28840.4617597},
            {0.00059, 28844.117943},
            {0.0006, 28847.9018083},
            {0.00061, 28851.5911295},
            {0.00062, 28855.1892873},
            {0.00063, 28858.9741513},
            {0.00064, 28862.1422702},
            {0.00065, 28865.5802447},
            {0.00066, 28868.9750769},
            {0.00067, 28872.3205366},
            {0.00068, 28875.619536},
            {0.00069, 28879.0206804},
            {0.0007, 28882.2675629},
            {0.00071, 28885.1291417},
            {0.00072, 28888.3871151},
            {0.00073, 28891.189583},
            {0.00074, 28894.1367738},
            {0.00075, 28897.0305359},
            {0.00076, 28899.8716634},
            {0.00077, 28902.6602427},
            {0.00078, 28905.3976812},
            {0.00079, 28908.0853168},
            {0.0008, 28910.7244961},
            {0.00081, 28913.3164802},
            {0.00082, 28915.8709538},
            {0.00083, 28918.3638546},
            {0.00084, 28920.8211536},
            {0.00085, 28923.2345019},
            {0.00086, 28925.6057224},
            {0.00087, 28927.9356245},
            {0.00088, 28930.2696054},
            {0.00089, 28932.4752253},
            {0.0009, 28934.6867695},
            {0.00091, 28936.8630689},
            {0.00092, 28938.9976724},
            {0.00093, 28941.1010358},
            {0.00094, 28943.1704034},
            {0.00095, 28945.2053605},
            {0.00096, 28947.1930321},
            {0.00097, 28949.3244258},
            {0.00098, 28951.0869791},
            {0.00099, 28952.9856009},
            {0.001, 28954.8526639},
            {0.00101, 28956.6887784},
            {0.00102, 28958.494503},
            {0.00103, 28960.2674407},
            {0.00104, 28962.0094008},
            {0.00105, 28963.7346424},
            {0.00106, 28965.4240526},
            {0.00107, 28967.0855521},
            {0.00108, 28968.719469},
            {0.00109, 28970.3267356},
            {0.0011, 28971.9072529},
            {0.00111, 28973.4615875},
            {0.00112, 28974.990123},
            {0.00113, 28976.4932165},
            {0.00114, 28977.830385},
            {0.00115, 28979.4242542},
            {0.00116, 28980.852868},
            {0.00117, 28982.2573112},
            {0.00118, 28983.6381943},
            {0.00119, 28984.7605452},
            {0.001195, 28985.6646742},
            {0.0011975, 28985.9973843},
            {0.001198125, 28986.0803364}
         };

         for (IndexType i = 0; i < nPoints; i++)
         {
            Float64 M = solution->GetMoment(i);
            Float64 k = solution->GetCurvature(i);
            //std::cout.precision(12);
            //std::cout << "{" << k << ", " << M << "}," << std::endl;
            Assert::IsTrue(IsEqual(datum[i].first, k));
            Assert::IsTrue(IsEqual(datum[i].second, M));
         }
      }
	};
}
