#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::LRFD;

namespace LrfdUnitTests
{
	TEST_CLASS(TestRebar)
	{
	public:
		
		TEST_METHOD(MaxBurstingStress)
		{
			LRFDAutoVersion av;
			LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::FirstEdition1994);
			Float64 fy = WBFL::Units::ConvertToSysUnits(60.0, WBFL::Units::Measure::KSI);
			Assert::AreEqual(fy, Rebar::GetMaxBurstingStress(fy));

			LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::FirstEditionWith1996Interims);
			LRFDVersionMgr::SetUnits(LRFDVersionMgr::Units::US);
			Assert::AreEqual(WBFL::Units::ConvertToSysUnits(20.0, WBFL::Units::Measure::KSI), Rebar::GetMaxBurstingStress(fy));
			Assert::AreEqual(fy/10, Rebar::GetMaxBurstingStress(fy/10));

			LRFDVersionMgr::SetUnits(LRFDVersionMgr::Units::SI);
			Assert::AreEqual(WBFL::Units::ConvertToSysUnits(140, WBFL::Units::Measure::MPa), Rebar::GetMaxBurstingStress(fy));
			Assert::AreEqual(fy / 10, Rebar::GetMaxBurstingStress(fy / 10));
		}

		TEST_METHOD(BurstingZoneLength)
		{
			LRFDAutoVersion av;
			LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::FirstEdition1994);
			Assert::AreEqual(4.0, Rebar::GetBurstingZoneLength(16.0)); // h/4

			LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::FirstEditionWith1996Interims);
			Assert::AreEqual(5.0, Rebar::GetBurstingZoneLength(25.0)); // h/5

			LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::SecondEditionWith2001Interims);
			Assert::AreEqual(5.0, Rebar::GetBurstingZoneLength(25.0)); // h/5

			LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::SecondEditionWith2002Interims);
			Assert::AreEqual(4.0, Rebar::GetBurstingZoneLength(16.0)); // h/4

			LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::LastVersion);
			Assert::AreEqual(4.0, Rebar::GetBurstingZoneLength(16.0)); // h/4
		}

		TEST_METHOD(MinConfinementBarSize)
		{
			Assert::IsTrue(WBFL::Materials::Rebar::Size::bs3 == Rebar::GetMinConfinementBarSize());
		}

		TEST_METHOD(MaxConfinmentBarSpacing)
		{
			LRFDAutoVersion av;
			LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::FirstEdition1994);

			LRFDVersionMgr::SetUnits(LRFDVersionMgr::Units::US);
			Assert::AreEqual(WBFL::Units::ConvertToSysUnits(6.0, WBFL::Units::Measure::Inch), Rebar::GetMaxConfinementBarSpacing());

			LRFDVersionMgr::SetUnits(LRFDVersionMgr::Units::SI);
			Assert::AreEqual(WBFL::Units::ConvertToSysUnits(150.0, WBFL::Units::Measure::Millimeter), Rebar::GetMaxConfinementBarSpacing());
		}

		TEST_METHOD(MinConfinementAvS)
		{
			LRFDAutoVersion av;
			LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::FirstEdition1994);

			LRFDVersionMgr::SetUnits(LRFDVersionMgr::Units::US);
			Assert::AreEqual(0.00046566666666666675, Rebar::GetMinConfinementAvS());

			LRFDVersionMgr::SetUnits(LRFDVersionMgr::Units::SI);
			Assert::AreEqual(0.00047311733333333338, Rebar::GetMinConfinementAvS());
		}

		TEST_METHOD(AvOverSMin)
		{
			LRFDAutoVersion av;
			LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::FirstEdition1994);

			Float64 fc = WBFL::Units::ConvertToSysUnits(5.0, WBFL::Units::Measure::KSI);
			Float64 fy = WBFL::Units::ConvertToSysUnits(60.0, WBFL::Units::Measure::KSI);
			Float64 bv = WBFL::Units::ConvertToSysUnits(6.0, WBFL::Units::Measure::Inch);

			LRFDVersionMgr::SetUnits(LRFDVersionMgr::Units::US);
			Assert::AreEqual(0.00017947576014604313, Rebar::GetAvOverSMin(fc, bv, fy));

			LRFDVersionMgr::SetUnits(LRFDVersionMgr::Units::SI);
			Assert::AreEqual(0.00017953011939713382, Rebar::GetAvOverSMin(fc, bv, fy));
		}

		TEST_METHOD(MaxStirrupSpacing)
		{
			LRFDAutoVersion av;
			LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::FirstEdition1994);

			Float64 sUnderLimit, sOverLimit;
			LRFDVersionMgr::SetUnits(LRFDVersionMgr::Units::US);
			Rebar::GetMaxStirrupSpacing(&sUnderLimit, &sOverLimit);
			Assert::AreEqual(WBFL::Units::ConvertToSysUnits(24.0, WBFL::Units::Measure::Inch), sUnderLimit);
			Assert::AreEqual(WBFL::Units::ConvertToSysUnits(12.0, WBFL::Units::Measure::Inch), sOverLimit);

			LRFDVersionMgr::SetUnits(LRFDVersionMgr::Units::SI);
			Rebar::GetMaxStirrupSpacing(&sUnderLimit, &sOverLimit);
			Assert::AreEqual(WBFL::Units::ConvertToSysUnits(600.0, WBFL::Units::Measure::Millimeter), sUnderLimit);
			Assert::AreEqual(WBFL::Units::ConvertToSysUnits(300.0, WBFL::Units::Measure::Millimeter), sOverLimit);
		}

		TEST_METHOD(TensileDevelopmentLength)
		{
			LRFDAutoVersion av;
			LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::FirstEdition1994);

			Float64 fc = WBFL::Units::ConvertToSysUnits(7.5, WBFL::Units::Measure::KSI);

			auto rebar_pool = RebarPool::GetInstance();

			std::vector<const WBFL::Materials::Rebar*> bars;
			bars.push_back(rebar_pool->GetRebar(WBFL::Materials::Rebar::Type::A615, WBFL::Materials::Rebar::Grade::Grade60, WBFL::Materials::Rebar::Size::bs3));
			bars.push_back(rebar_pool->GetRebar(WBFL::Materials::Rebar::Type::A615, WBFL::Materials::Rebar::Grade::Grade60, WBFL::Materials::Rebar::Size::bs4));
			bars.push_back(rebar_pool->GetRebar(WBFL::Materials::Rebar::Type::A615, WBFL::Materials::Rebar::Grade::Grade60, WBFL::Materials::Rebar::Size::bs5));
			bars.push_back(rebar_pool->GetRebar(WBFL::Materials::Rebar::Type::A615, WBFL::Materials::Rebar::Grade::Grade60, WBFL::Materials::Rebar::Size::bs6));
			bars.push_back(rebar_pool->GetRebar(WBFL::Materials::Rebar::Type::A615, WBFL::Materials::Rebar::Grade::Grade60, WBFL::Materials::Rebar::Size::bs7));
			bars.push_back(rebar_pool->GetRebar(WBFL::Materials::Rebar::Type::A615, WBFL::Materials::Rebar::Grade::Grade60, WBFL::Materials::Rebar::Size::bs8));
			bars.push_back(rebar_pool->GetRebar(WBFL::Materials::Rebar::Type::A615, WBFL::Materials::Rebar::Grade::Grade60, WBFL::Materials::Rebar::Size::bs9));
			bars.push_back(rebar_pool->GetRebar(WBFL::Materials::Rebar::Type::A615, WBFL::Materials::Rebar::Grade::Grade60, WBFL::Materials::Rebar::Size::bs10));
			bars.push_back(rebar_pool->GetRebar(WBFL::Materials::Rebar::Type::A615, WBFL::Materials::Rebar::Grade::Grade60, WBFL::Materials::Rebar::Size::bs11));
			bars.push_back(rebar_pool->GetRebar(WBFL::Materials::Rebar::Type::A615, WBFL::Materials::Rebar::Grade::Grade60, WBFL::Materials::Rebar::Size::bs14));
			bars.push_back(rebar_pool->GetRebar(WBFL::Materials::Rebar::Type::A615, WBFL::Materials::Rebar::Grade::Grade60, WBFL::Materials::Rebar::Size::bs18));

			LRFDVersionMgr::SetUnits(LRFDVersionMgr::Units::US);

			std::vector<Float64> us_results
			{
				0.30479999999999996,
				0.30479999999999996,
				0.38100000000000001,
				0.45720000000000000,
				0.53340000000000010,
				0.60959999999999992,
				0.69560764803156094,
				0.88342171300008232,
				1.0851479309292351,
				1.5025125197481717,
				1.9477014144883706
			};
			Assert::AreEqual(bars.size(), us_results.size());

			auto bar_iter = bars.begin();
			auto bar_end = bars.end();
			auto results_iter = us_results.begin();
			for (; bar_iter != bar_end; bar_iter++, results_iter++)
			{
				Assert::AreEqual(*results_iter, Rebar::GetTensileDevelopmentLength(*(*bar_iter), fc), 0.00001);
			}


			LRFDVersionMgr::SetUnits(LRFDVersionMgr::Units::SI);
			std::vector<Float64> si_results
			{
				0.30499999999999999,
				0.31522830344373237,
				0.39403537930466553,
				0.47284245516559859,
				0.55164953102653169,
				0.63045660688746474,
				0.74229671574243961,
				0.94271682899289844,
				1.1579828765582056,
				1.4382027631565029,
				1.9559557578928441
			};
			Assert::AreEqual(bars.size(), si_results.size());

			std::vector<Float64> values;
			bar_iter = bars.begin();
			results_iter = si_results.begin();
			for (; bar_iter != bar_end; bar_iter++, results_iter++)
			{
				Assert::AreEqual(*results_iter, Rebar::GetTensileDevelopmentLength(*(*bar_iter), fc), 0.00001);
			}
		}

		TEST_METHOD(HookExtension)
		{
			WBFL::Units::AutoSystem au;
			WBFL::Units::System::SetLengthUnit(WBFL::Units::Measure::Inch);

			Assert::AreEqual(0.0, Rebar::GetHookExtension(WBFL::Materials::Rebar::Size::bs3, 0.375, Rebar::Usage::Longitudinal, Rebar::Hook::hookNone));
			Assert::AreEqual(4.5, Rebar::GetHookExtension(WBFL::Materials::Rebar::Size::bs3, 0.375, Rebar::Usage::Longitudinal, Rebar::Hook::hook90));
			Assert::AreEqual(2.5, Rebar::GetHookExtension(WBFL::Materials::Rebar::Size::bs3, 0.375, Rebar::Usage::Longitudinal, Rebar::Hook::hook180));
			Assert::AreEqual(4.0, Rebar::GetHookExtension(WBFL::Materials::Rebar::Size::bs8, 1.000, Rebar::Usage::Longitudinal, Rebar::Hook::hook180));
			Assert::ExpectException<std::invalid_argument>([](){ Rebar::GetHookExtension(WBFL::Materials::Rebar::Size::bs3, 0.375, Rebar::Usage::Longitudinal, Rebar::Hook::hook135); });

			Assert::AreEqual(3.75, Rebar::GetHookExtension(WBFL::Materials::Rebar::Size::bs5, 0.625, Rebar::Usage::Transverse, Rebar::Hook::hook90));
			Assert::AreEqual(9.0, Rebar::GetHookExtension(WBFL::Materials::Rebar::Size::bs6, 0.750, Rebar::Usage::Transverse, Rebar::Hook::hook90));
			Assert::AreEqual(12.0, Rebar::GetHookExtension(WBFL::Materials::Rebar::Size::bs8, 1.000, Rebar::Usage::Transverse, Rebar::Hook::hook90));
			Assert::ExpectException<std::invalid_argument>([]() { Rebar::GetHookExtension(WBFL::Materials::Rebar::Size::bs9, 1.128, Rebar::Usage::Transverse, Rebar::Hook::hook90); });
			Assert::AreEqual(2.25, Rebar::GetHookExtension(WBFL::Materials::Rebar::Size::bs3, 0.375, Rebar::Usage::Transverse, Rebar::Hook::hook135));
			Assert::AreEqual(6.0, Rebar::GetHookExtension(WBFL::Materials::Rebar::Size::bs8, 1.000, Rebar::Usage::Transverse, Rebar::Hook::hook135));
			Assert::ExpectException<std::invalid_argument>([]() { Rebar::GetHookExtension(WBFL::Materials::Rebar::Size::bs9, 1.128, Rebar::Usage::Transverse, Rebar::Hook::hook135); });
			Assert::ExpectException<std::invalid_argument>([]() { Rebar::GetHookExtension(WBFL::Materials::Rebar::Size::bs3, 0.375, Rebar::Usage::Transverse, Rebar::Hook::hook180); });

			Assert::AreEqual(3.00, Rebar::GetHookExtension(WBFL::Materials::Rebar::Size::bs3, 0.375, Rebar::Usage::Seismic, Rebar::Hook::hook135));
			Assert::AreEqual(3.75, Rebar::GetHookExtension(WBFL::Materials::Rebar::Size::bs5, 0.625, Rebar::Usage::Seismic, Rebar::Hook::hook135));
			Assert::ExpectException<std::invalid_argument>([]() { Rebar::GetHookExtension(WBFL::Materials::Rebar::Size::bs3, 0.375, Rebar::Usage::Seismic, Rebar::Hook::hook90); });
			Assert::ExpectException<std::invalid_argument>([]() { Rebar::GetHookExtension(WBFL::Materials::Rebar::Size::bs3, 0.375, Rebar::Usage::Seismic, Rebar::Hook::hook180); });
		}

		TEST_METHOD(BendDiameter)
		{
			Assert::AreEqual(6.0, Rebar::GetBendDiameter(WBFL::Materials::Rebar::Size::bs3, 0.0, Rebar::Usage::Longitudinal, true));
			Assert::AreEqual(6.0, Rebar::GetBendDiameter(WBFL::Materials::Rebar::Size::bs4, 0.0, Rebar::Usage::Longitudinal, true));
			Assert::AreEqual(6.0, Rebar::GetBendDiameter(WBFL::Materials::Rebar::Size::bs5, 0.0, Rebar::Usage::Longitudinal, true));

			Assert::AreEqual(6.0, Rebar::GetBendDiameter(WBFL::Materials::Rebar::Size::bs6, 0.0, Rebar::Usage::Longitudinal, true));
			Assert::AreEqual(6.0, Rebar::GetBendDiameter(WBFL::Materials::Rebar::Size::bs7, 0.0, Rebar::Usage::Longitudinal, true));
			Assert::AreEqual(6.0, Rebar::GetBendDiameter(WBFL::Materials::Rebar::Size::bs8, 0.0, Rebar::Usage::Longitudinal, true));

			Assert::AreEqual(8.0, Rebar::GetBendDiameter(WBFL::Materials::Rebar::Size::bs9, 0.0, Rebar::Usage::Longitudinal, true));
			Assert::AreEqual(8.0, Rebar::GetBendDiameter(WBFL::Materials::Rebar::Size::bs10, 0.0, Rebar::Usage::Longitudinal, true));
			Assert::AreEqual(8.0, Rebar::GetBendDiameter(WBFL::Materials::Rebar::Size::bs11, 0.0, Rebar::Usage::Longitudinal, true));

			Assert::AreEqual(10.0, Rebar::GetBendDiameter(WBFL::Materials::Rebar::Size::bs14, 0.0, Rebar::Usage::Longitudinal, true));
			Assert::AreEqual(10.0, Rebar::GetBendDiameter(WBFL::Materials::Rebar::Size::bs18, 0.0, Rebar::Usage::Longitudinal, true));

			Assert::AreEqual(4.0, Rebar::GetBendDiameter(WBFL::Materials::Rebar::Size::bs3, 0.0, Rebar::Usage::Transverse, true));
			Assert::AreEqual(4.0, Rebar::GetBendDiameter(WBFL::Materials::Rebar::Size::bs4, 0.0, Rebar::Usage::Transverse, true));
			Assert::AreEqual(4.0, Rebar::GetBendDiameter(WBFL::Materials::Rebar::Size::bs5, 0.0, Rebar::Usage::Transverse, true));

			Assert::AreEqual(4.0, Rebar::GetBendDiameter(WBFL::Materials::Rebar::Size::bs3, 0.0, Rebar::Usage::Seismic, true));
			Assert::AreEqual(4.0, Rebar::GetBendDiameter(WBFL::Materials::Rebar::Size::bs4, 0.0, Rebar::Usage::Seismic, true));
			Assert::AreEqual(4.0, Rebar::GetBendDiameter(WBFL::Materials::Rebar::Size::bs5, 0.0, Rebar::Usage::Seismic, true));
		}

		TEST_METHOD(CompressionControlledStrainLimit)
		{
			Assert::AreEqual(0.002, Rebar::GetCompressionControlledStrainLimit(WBFL::Materials::Rebar::Grade::Grade40));
			Assert::AreEqual(0.002, Rebar::GetCompressionControlledStrainLimit(WBFL::Materials::Rebar::Grade::Grade60));
			Assert::AreEqual(0.00275, Rebar::GetCompressionControlledStrainLimit(WBFL::Materials::Rebar::Grade::Grade75));
			Assert::AreEqual(0.003, Rebar::GetCompressionControlledStrainLimit(WBFL::Materials::Rebar::Grade::Grade80));
			Assert::AreEqual(0.004, Rebar::GetCompressionControlledStrainLimit(WBFL::Materials::Rebar::Grade::Grade100));
			Assert::AreEqual(0.004, Rebar::GetCompressionControlledStrainLimit(WBFL::Materials::Rebar::Grade::Grade120));
		}

		TEST_METHOD(TensionControlledStrainLimit)
		{
			Assert::AreEqual(0.005, Rebar::GetTensionControlledStrainLimit(WBFL::Materials::Rebar::Grade::Grade40));
			Assert::AreEqual(0.005, Rebar::GetTensionControlledStrainLimit(WBFL::Materials::Rebar::Grade::Grade60));
			Assert::AreEqual(0.005, Rebar::GetTensionControlledStrainLimit(WBFL::Materials::Rebar::Grade::Grade75));
			Assert::AreEqual(0.0056, Rebar::GetTensionControlledStrainLimit(WBFL::Materials::Rebar::Grade::Grade80));
			Assert::AreEqual(0.008, Rebar::GetTensionControlledStrainLimit(WBFL::Materials::Rebar::Grade::Grade100));
			Assert::AreEqual(0.008, Rebar::GetTensionControlledStrainLimit(WBFL::Materials::Rebar::Grade::Grade120));
		}

		TEST_METHOD(RebarDevelopmentLengthDetails)
		{
			WBFL::Units::AutoSystem au;
			WBFL::Units::System::SetMassUnit(WBFL::Units::Measure::_12KSlug);
			WBFL::Units::System::SetLengthUnit(WBFL::Units::Measure::Inch);

			auto density = WBFL::Units::ConvertToSysUnits(0.155, WBFL::Units::Measure::KipPerFeet3);

			// Standard bar
			auto details = Rebar::GetRebarDevelopmentLengthDetails(WBFL::Materials::Rebar::Size::bs3, 0.11, 0.375, 60, WBFL::Materials::ConcreteType::Normal, 7.5, false, 0.2, density, false, false, true);
			Assert::AreEqual(0.11, details.Ab);
			Assert::AreEqual(0.375, details.db);
			Assert::AreEqual(60.0, details.fy);
			Assert::AreEqual(7.5, details.fc);
			Assert::AreEqual(1.0, details.lambdaRl);
			Assert::AreEqual(1.0, details.lambdaLw);
			Assert::AreEqual(1.0, details.lambdaCf);
			Assert::AreEqual(1.0, details.factor);
			Assert::IsFalse(details.bRlCfLimit);
			Assert::AreEqual(19.718012070156814, details.ldb1);
			Assert::AreEqual(0.0, details.ldb2);
			Assert::AreEqual(19.718012070156814, details.ldb);
			Assert::AreEqual(19.718012070156814, details.ld);


			// Epoxy coated, meeting cover
			details = Rebar::GetRebarDevelopmentLengthDetails(WBFL::Materials::Rebar::Size::bs3, 0.11, 0.375, 60, WBFL::Materials::ConcreteType::Normal, 7.5, false, 0.2, density, false, true, true);
			Assert::AreEqual(1.0, details.lambdaRl);
			Assert::AreEqual(1.0, details.lambdaLw);
			Assert::AreEqual(1.2, details.lambdaCf);
			Assert::AreEqual(1.2, details.factor);
			Assert::IsFalse(details.bRlCfLimit);
			Assert::AreEqual(19.718012070156814, details.ldb1);
			Assert::AreEqual(0.0, details.ldb2);
			Assert::AreEqual(19.718012070156814, details.ldb);
			Assert::AreEqual(23.661614484188174, details.ld);

			// Epoxy coated, not meeting cover
			details = Rebar::GetRebarDevelopmentLengthDetails(WBFL::Materials::Rebar::Size::bs3, 0.11, 0.375, 60, WBFL::Materials::ConcreteType::Normal, 7.5, false, 0.2, density, false, true, false);
			Assert::AreEqual(1.0, details.lambdaRl);
			Assert::AreEqual(1.0, details.lambdaLw);
			Assert::AreEqual(1.5, details.lambdaCf);
			Assert::AreEqual(1.5, details.factor);
			Assert::IsFalse(details.bRlCfLimit);
			Assert::AreEqual(19.718012070156814, details.ldb1);
			Assert::AreEqual(0.0, details.ldb2);
			Assert::AreEqual(19.718012070156814, details.ldb);
			Assert::AreEqual(29.577018105235219, details.ld);

			// top bar
			details = Rebar::GetRebarDevelopmentLengthDetails(WBFL::Materials::Rebar::Size::bs3, 0.11, 0.375, 60, WBFL::Materials::ConcreteType::Normal, 7.5, false, 0.2, density, true, false, true);
			Assert::AreEqual(1.3, details.lambdaRl);
			Assert::AreEqual(1.0, details.lambdaLw);
			Assert::AreEqual(1.0, details.lambdaCf);
			Assert::AreEqual(1.3, details.factor);
			Assert::IsFalse(details.bRlCfLimit);
			Assert::AreEqual(19.718012070156814, details.ldb1);
			Assert::AreEqual(0.0, details.ldb2);
			Assert::AreEqual(19.718012070156814, details.ldb);
			Assert::AreEqual(25.633415691203858, details.ld);

			// not top bar, fc > 10
			details = Rebar::GetRebarDevelopmentLengthDetails(WBFL::Materials::Rebar::Size::bs3, 0.11, 0.375, 60, WBFL::Materials::ConcreteType::Normal, 15.0, false, 0.2, density, false, false, true);
			Assert::AreEqual(15.0, details.fc);
			Assert::AreEqual(1.3, details.lambdaRl);
			Assert::AreEqual(1.0, details.lambdaLw);
			Assert::AreEqual(1.0, details.lambdaCf);
			Assert::AreEqual(1.3, details.factor);
			Assert::IsFalse(details.bRlCfLimit);
			Assert::AreEqual(13.942740046326076, details.ldb1);
			Assert::AreEqual(0.0, details.ldb2);
			Assert::AreEqual(13.942740046326076, details.ldb);
			Assert::AreEqual(18.125562060223899, details.ld);
		}
	};
}
