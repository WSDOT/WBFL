#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::LRFD;

namespace LrfdUnitTests
{
	TEST_CLASS(TestShear)
	{
	public:
		
		TEST_METHOD(ShearStress)
		{
			BDSAutoVersion av;
			BDSManager::SetEdition(BDSManager::Edition::ThirdEditionWith2006Interims); // changed in 2007
			Assert::AreEqual(0.29320987654320985, Shear::ComputeShearStress(100, 90, 0.9, 6, 12), 0.001);
			Assert::AreEqual(-1.0956790123456788, Shear::ComputeShearStress(10, 90, 0.9, 6, 12), 0.001);

			BDSManager::SetEdition(BDSManager::Edition::FourthEdition2007);
			Assert::AreEqual(0.29320987654320985, Shear::ComputeShearStress(100, 90, 0.9, 6, 12), 0.001);
			Assert::AreEqual(1.0956790123456788, Shear::ComputeShearStress(10, 90, 0.9, 6, 12), 0.001);
		}

		TEST_METHOD(VciVcw)
		{
			// US units
			WBFL::Units::AutoSystem au;
			WBFL::Units::System::SetMassUnit(WBFL::Units::Measure::_12KSlug);
			WBFL::Units::System::SetLengthUnit(WBFL::Units::Measure::Inch);
			WBFL::Units::System::SetAngleUnit(WBFL::Units::Measure::Radian);

			BDSAutoVersion av;

			ShearData data;
			// This method is only valid between 3rd Edition 2006 and was removed in 8th Edition 2017
			BDSManager::SetEdition(BDSManager::Edition::ThirdEditionWith2006Interims);
			Assert::ExpectException<XCodeVersion>([&]() {Shear::ComputeVciVcw(&data); });

			BDSManager::SetEdition(BDSManager::Edition::EighthEdition2017);
			Assert::ExpectException<XCodeVersion>([&]() {Shear::ComputeVciVcw(&data); });

			BDSManager::SetEdition(BDSManager::Edition::FourthEdition2007);

			data.Mu = 500;
			data.Nu = 100;
			data.Vu = 50;
			data.phi = 0.85;
			data.Vp = 20;
			data.dv = 48;
			data.bv = 6;
			data.Es = 28000;
			data.As = 1.25;
			data.Eps = 28500;
			data.Aps = 6.27;
			data.EptSegment = 28500;
			data.AptSegment = 1.29;
			data.EptGirder = 28500;
			data.AptGirder = 1.88;
			data.Ec = 4000;
			data.Ac = 500;
			data.fpops = 200;
			data.fpoptSegment = 200;
			data.fpoptGirder = 200;
			data.fc = 7;
			data.Vd = 45;
			data.Vi = 65;
			data.Mcre = 235;
			data.fpc = 0.55;
			data.lambda = 1.0;

			Shear::ComputeVciVcw(&data);

			Assert::AreEqual(45.718582655252860, data.VciMin, 0.0001);
			Assert::AreEqual(90.789527551750950, data.VciCalc, 0.0001);
			Assert::AreEqual(90.789527551750950, data.Vci, 0.0001);
			Assert::AreEqual(113.23858265524154, data.Vcw, 0.0001);
		}

		TEST_METHOD(BetaTheta_Details)
		{
			// US units
			WBFL::Units::AutoSystem au;
			WBFL::Units::System::SetMassUnit(WBFL::Units::Measure::_12KSlug);
			WBFL::Units::System::SetLengthUnit(WBFL::Units::Measure::Inch);
			WBFL::Units::System::SetAngleUnit(WBFL::Units::Measure::Radian);

			BDSAutoVersion av;

			ShearData data;
			data.Mu = 500;
			data.Nu = 100;
			data.Vu = 50;
			data.phi = 0.85;
			data.Vp = 20;
			data.dv = 48;
			data.bv = 6;
			data.Es = 28000;
			data.As = 1.25;
			data.Eps = 28500;
			data.Aps = 6.27;
			data.EptSegment = 28500;
			data.AptSegment = 1.29;
			data.EptGirder = 28500;
			data.AptGirder = 1.88;
			data.Ec = 4000;
			data.Ac = 500;
			data.fpops = 200;
			data.fpoptSegment = 200;
			data.fpoptGirder = 200;
			data.fc = 7;
			data.Vd = 45;
			data.Vi = 65;
			data.Mcre = 235;
			data.fpc = 0.55;
			data.lambda = 1.0;
			data.fy = 60.0;
			data.AvS = 0.9;
			data.sx = 2;
			data.ag = 0.1;

			Shear::ComputeThetaAndBeta(&data, Shear::Method::Tables);
			Assert::AreEqual(6.32, data.Beta);
			Assert::AreEqual(0.38920842319377003, data.Theta);
			Assert::AreEqual((Int16)1, data.BetaTheta_tbl);
			Assert::AreEqual(0.019257703081232497, data.vufc);
			Assert::AreEqual(0.075, data.vufc_tbl, 0.001);
			Assert::AreEqual(0.0, data.ex);
			Assert::AreEqual(-0.0002, data.ex_tbl);
			Assert::AreEqual(-1.0, data.Fe);


			Shear::ComputeThetaAndBeta(&data, Shear::Method::Equations);
			Assert::AreEqual(6.8571428571428577, data.Beta);
			Assert::AreEqual(0.48171087354924003, data.Theta);
			Assert::AreEqual((Int16)1, data.BetaTheta_tbl);
			Assert::AreEqual(0.019257703081232497, data.vufc);
			Assert::AreEqual(-1.0, data.vufc_tbl, 0.001);
			Assert::AreEqual(-0.0004, data.ex);
			Assert::AreEqual(-0.0002, data.ex_tbl);
			Assert::AreEqual(-1.0, data.Fe);
		}


		TEST_METHOD(BetaTheta_WSDOT)
		{
			// LRFD Shear 2001 Interims, modified by WSDOT Design Memo 7-2001... Dated June 18, 2001

			// US units
			WBFL::Units::AutoSystem au;
			WBFL::Units::System::SetMassUnit(WBFL::Units::Measure::_12KSlug);
			WBFL::Units::System::SetLengthUnit(WBFL::Units::Measure::Inch);
			WBFL::Units::System::SetAngleUnit(WBFL::Units::Measure::Radian);

			BDSAutoVersion av;

			ShearData data;
			data.Mu = 500;
			data.Nu = 100;
			data.Vu = 50;
			data.phi = 0.85;
			data.Vp = 20;
			data.dv = 48;
			data.bv = 6;
			data.Es = 28000;
			data.As = 1.25;
			data.Eps = 28500;
			data.Aps = 6.27;
			data.EptSegment = 28500;
			data.AptSegment = 1.29;
			data.EptGirder = 28500;
			data.AptGirder = 1.88;
			data.Ec = 4000;
			data.Ac = 500;
			data.fpops = 200;
			data.fpoptSegment = 200;
			data.fpoptGirder = 200;
			data.fc = 7;
			data.Vd = 45;
			data.Vi = 65;
			data.Mcre = 235;
			data.fpc = 0.55;
			data.lambda = 1.0;
			data.fy = 60.0;
			data.AvS = 0.9;
			data.sx = 2;
			data.ag = 0.1;

			WsdotShear::ComputeThetaAndBeta(&data, true);
			Assert::AreEqual(6.32, data.Beta);
			Assert::AreEqual(0.38920842319377003, data.Theta);
			Assert::AreEqual((Int16)0, data.BetaTheta_tbl);
			Assert::AreEqual(0.019257703081232497, data.vufc);
			Assert::AreEqual(0.075, data.vufc_tbl, 0.001);
			Assert::AreEqual(-0.00039009377730710691, data.ex);
			Assert::AreEqual(-0.0002, data.ex_tbl);
			Assert::AreEqual(-1.0, data.Fe);


			WsdotShear::ComputeThetaAndBeta(&data, false);
			Assert::AreEqual(6.32, data.Beta);
			Assert::AreEqual(0.38920842319377003, data.Theta);
			Assert::AreEqual((Int16)0, data.BetaTheta_tbl);
			Assert::AreEqual(0.019257703081232497, data.vufc);
			Assert::AreEqual(0.075, data.vufc_tbl, 0.001);
			Assert::AreEqual(-0.00039009377730710691, data.ex);
			Assert::AreEqual(-0.0002, data.ex_tbl);
			Assert::AreEqual(-1.0, data.Fe);
		}

		TEST_METHOD(BetaTheta_AllSpecs)
		{
			// US units
			WBFL::Units::AutoSystem au;
			WBFL::Units::System::SetMassUnit(WBFL::Units::Measure::_12KSlug);
			WBFL::Units::System::SetLengthUnit(WBFL::Units::Measure::Inch);
			WBFL::Units::System::SetAngleUnit(WBFL::Units::Measure::Radian);

			BDSAutoVersion av;

			ShearData data;
			data.Mu = 500;
			data.Nu = 100;
			data.Vu = 50;
			data.phi = 0.85;
			data.Vp = 20;
			data.dv = 48;
			data.bv = 6;
			data.Es = 28000;
			data.As = 1.25;
			data.Eps = 28500;
			data.Aps = 6.27;
			data.EptSegment = 28500;
			data.AptSegment = 1.29;
			data.EptGirder = 28500;
			data.AptGirder = 1.88;
			data.Ec = 4000;
			data.Ac = 500;
			data.fpops = 200;
			data.fpoptSegment = 200;
			data.fpoptGirder = 200;
			data.fc = 7;
			data.Vd = 45;
			data.Vi = 65;
			data.Mcre = 235;
			data.fpc = 0.55;
			data.lambda = 1.0;
			data.fy = 60.0;
			data.AvS = 0.9;
			data.sx = 2;
			data.ag = 0.1;

			std::vector<BDSManager::Edition> specs
			{
				BDSManager::Edition::FirstEdition1994,
				BDSManager::Edition::FirstEditionWith1997Interims,
				BDSManager::Edition::SecondEditionWith1999Interims,
				BDSManager::Edition::SecondEditionWith2000Interims,
				BDSManager::Edition::SecondEditionWith2002Interims,
				BDSManager::Edition::SecondEditionWith2003Interims,
				BDSManager::Edition::ThirdEditionWith2005Interims,
				BDSManager::Edition::FourthEditionWith2008Interims,
			};

			std::vector<std::pair<Float64, Float64>> expected_tables
			{
				{ 6.78, 0.47123889803730001 }, // 1st Edition 1994
				{ 6.78, 0.47123889803730001 }, // 1st Edition 1997
				{ 6.78, 0.47123889803730001 }, // 2nd Edition 1999
				{ 6.32, 0.38920842319377003 }, // 2nd Edition 2000
				{ 6.32, 0.38920842319377003 }, // 2nd Edition 2002
				{ 6.32, 0.38920842319377003 }, // 2nd Edition 2003
				{ 6.32, 0.38920842319377003 }, // 3rd Edition 2005
				{ 6.32, 0.38920842319377003 }, // 4th Edition 2008
			};

			std::vector<std::pair<Float64, Float64>> expected_equations
			{
				{ -1.0, -1.0 },// 1st Edition 1994
				{ -1.0, -1.0 },// 1st Edition 1997
				{ -1.0, -1.0 },// 2nd Edition 1999
				{ -1.0, -1.0 },// 2nd Edition 2000
				{ -1.0, -1.0 },// 2nd Edition 2002
				{ -1.0, -1.0 },// 2nd Edition 2003
				{ -1.0, -1.0 },// 3rd Edition 2005
				{ 6.8571428571428577, 0.48171087354924003 },// 4th Edition 2008
			};

			int i = 0;
			for(const auto& spec : specs)
			{
				BDSManager::SetEdition(spec);

				Shear::ComputeThetaAndBeta(&data, Shear::Method::Tables);
				Assert::AreEqual(expected_tables[i].first, data.Beta, 0.0001);
				Assert::AreEqual(expected_tables[i].second, data.Theta, 0.0001);

				if (BDSManager::Edition::FourthEditionWith2008Interims <= BDSManager::GetEdition())
				{
					// equations where introduced in 2008 interims to the 4th edition
					Shear::ComputeThetaAndBeta(&data, Shear::Method::Equations);
					Assert::AreEqual(expected_equations[i].first, data.Beta, 0.0001);
					Assert::AreEqual(expected_equations[i].second, data.Theta, 0.0001);
				}

				i++;
			}
		}
	};
}
