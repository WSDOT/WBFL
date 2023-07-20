#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::LRFD;
using namespace WBFL::Materials;

namespace LrfdUnitTests
{
	TEST_CLASS(TestLRFDConcrete)
	{
	public:
		
		TEST_METHOD(Test)
		{
			// US units
			WBFL::Units::AutoSystem au;
			WBFL::Units::System::SetMassUnit(WBFL::Units::Measure::_12KSlug);
			WBFL::Units::System::SetLengthUnit(WBFL::Units::Measure::Inch);
			WBFL::Units::System::SetAngleUnit(WBFL::Units::Measure::Radian);

			auto fci = WBFL::Units::ConvertToSysUnits(5.0, WBFL::Units::Measure::KSI);
			auto fc  = WBFL::Units::ConvertToSysUnits(7.0, WBFL::Units::Measure::KSI);
			auto density = WBFL::Units::ConvertToSysUnits(0.160, WBFL::Units::Measure::KipPerFeet3);
			auto wDensity = WBFL::Units::ConvertToSysUnits(0.165, WBFL::Units::Measure::KipPerFeet3);
			auto Eci = WBFL::Units::ConvertToSysUnits(4000.0, WBFL::Units::Measure::KSI);
			auto Ec = WBFL::Units::ConvertToSysUnits(4600.0, WBFL::Units::Measure::KSI);
			auto frShear = WBFL::Units::ConvertToSysUnits(0.650, WBFL::Units::Measure::KSI);
			auto frFlexure = WBFL::Units::ConvertToSysUnits(0.700, WBFL::Units::Measure::KSI);

			SimpleConcrete initial(_T("Initial"), fci, density, wDensity, Eci, frShear, frFlexure);
			SimpleConcrete final(_T("Final"), fc, density, wDensity, Ec, frShear, frFlexure);
			SimpleConcrete final90(_T("Final90"), 1.5*fc, density, wDensity, Ec, frShear, frFlexure);

			LRFDConcrete concrete(initial, final, 1, 28);
			concrete.SetVSRatio(WBFL::Units::ConvertToSysUnits(3.5, WBFL::Units::Measure::Inch));

			Assert::IsFalse(concrete.Use90DayStrength());
			Assert::AreEqual(1.0, concrete.GetLambda());

			// PCI UHPC Default parameters
			Assert::AreEqual(0.0, concrete.GetFirstCrackingStrength());
			Assert::AreEqual(0.0, concrete.GetPostCrackingTensileStrength());
			Assert::AreEqual(0.0, concrete.GetAutogenousShrinkage());

			concrete.SetFirstCrackingStrength(1.0);
			concrete.SetPostCrackingTensileStrength(1.0);
			concrete.SetAutogenousShrinkage(1.0);

			Assert::AreEqual(1.0, concrete.GetFirstCrackingStrength());
			Assert::AreEqual(1.0, concrete.GetPostCrackingTensileStrength());
			Assert::AreEqual(1.0, concrete.GetAutogenousShrinkage());

			// UHPC Default parameters
			Assert::AreEqual(0.85, concrete.GetCompressionResponseReductionFactor());
			Assert::AreEqual(0.0, concrete.GetElasticTensileStrainLimit());
			Assert::AreEqual(0.0, concrete.GetInitialEffectiveCrackingStrength());
			Assert::AreEqual(0.0, concrete.GetDesignEffectiveCrackingStrength());
			Assert::AreEqual(0.0, concrete.GetCrackLocalizationStrength());
			Assert::AreEqual(0.0, concrete.GetCrackLocalizationStrain());
			Assert::AreEqual(1.0, concrete.GetFiberOrientationReductionFactor());
			Assert::AreEqual(-0.0012934782608695656, concrete.GetElasticCompressiveStrainLimit());
			bool bIsExperimental;
			Assert::AreEqual(-0.0035, concrete.GetCompressiveStrainLimit(&bIsExperimental));
			Assert::IsFalse(bIsExperimental);

			concrete.SetCompressionResponseReductionFactor(2.0);
			concrete.SetElasticTensileStrainLimit(2.0);
			concrete.SetInitialEffectiveCrackingStrength(2.0);
			concrete.SetDesignEffectiveCrackingStrength(2.0);
			concrete.SetCrackLocalizationStrength(2.0);
			concrete.SetCrackLocalizationStrain(2.0);
			concrete.SetFiberOrientationReductionFactor(2.0);

			Assert::AreEqual(2.0, concrete.GetCompressionResponseReductionFactor());
			Assert::AreEqual(2.0, concrete.GetElasticTensileStrainLimit());
			Assert::AreEqual(2.0, concrete.GetInitialEffectiveCrackingStrength());
			Assert::AreEqual(2.0, concrete.GetDesignEffectiveCrackingStrength());
			Assert::AreEqual(2.0, concrete.GetCrackLocalizationStrength());
			Assert::AreEqual(2.0, concrete.GetCrackLocalizationStrain());
			Assert::AreEqual(2.0, concrete.GetFiberOrientationReductionFactor());

			// Time dependent values
			Assert::AreEqual(0.0, concrete.GetFc(0), 0.00001);
			Assert::AreEqual(5.0, concrete.GetFc(1), 0.00001);
			Assert::AreEqual(5.0, concrete.GetFc(10), 0.00001);
			Assert::AreEqual(7.0, concrete.GetFc(28), 0.00001);
			Assert::AreEqual(7.0, concrete.GetFc(56), 0.00001);
			Assert::AreEqual(7.0, concrete.GetFc(90), 0.00001);

			Assert::AreEqual(0.0, concrete.GetEc(0), 0.00001);
			Assert::AreEqual(4000.0, concrete.GetEc(1), 0.00001);
			Assert::AreEqual(4000.0, concrete.GetEc(10), 0.00001);
			Assert::AreEqual(4600.0, concrete.GetEc(28), 0.00001);
			Assert::AreEqual(4600.0, concrete.GetEc(56), 0.00001);
			Assert::AreEqual(4600.0, concrete.GetEc(90), 0.00001);

			Assert::AreEqual(0.0, concrete.GetShearFr(0), 0.00001);
			Assert::AreEqual(0.65, concrete.GetShearFr(1), 0.00001);
			Assert::AreEqual(0.65, concrete.GetShearFr(10), 0.00001);
			Assert::AreEqual(0.65, concrete.GetShearFr(28), 0.00001);
			Assert::AreEqual(0.65, concrete.GetShearFr(56), 0.00001);
			Assert::AreEqual(0.65, concrete.GetShearFr(90), 0.00001);

			Assert::AreEqual(0.0, concrete.GetFlexureFr(0), 0.00001);
			Assert::AreEqual(0.7, concrete.GetFlexureFr(1), 0.00001);
			Assert::AreEqual(0.7, concrete.GetFlexureFr(10), 0.00001);
			Assert::AreEqual(0.7, concrete.GetFlexureFr(28), 0.00001);
			Assert::AreEqual(0.7, concrete.GetFlexureFr(56), 0.00001);
			Assert::AreEqual(0.7, concrete.GetFlexureFr(90), 0.00001);

			// Creep and shrinkage changed in 2005 and 2015
			// Test pre2005, 2005-pre 2015, and 2015 and later
			{
				LRFDAutoVersion av;
				LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::ThirdEdition2004);
				Assert::AreEqual(0.0, concrete.GetFreeShrinkageStrain(0), 0.00001);
				Assert::AreEqual(0.0, concrete.GetFreeShrinkageStrain(1), 0.00001);
				Assert::AreEqual(-0.00025227462944248081, concrete.GetFreeShrinkageStrain(10), 0.00001);
				Assert::AreEqual(-0.00047885039311730153, concrete.GetFreeShrinkageStrain(28), 0.00001);
				Assert::AreEqual(-0.00061586148454004404, concrete.GetFreeShrinkageStrain(56), 0.00001);
				Assert::AreEqual(-0.00068595311232926926, concrete.GetFreeShrinkageStrain(90), 0.00001);

				Assert::AreEqual(0.0, concrete.GetCreepCoefficient(0, 0), 0.00001);
				Assert::AreEqual(0.0, concrete.GetCreepCoefficient(1, 1), 0.00001);
				Assert::AreEqual(0.35149906089825150, concrete.GetCreepCoefficient(10, 1), 0.00001);
				Assert::AreEqual(0.61296524339706626, concrete.GetCreepCoefficient(28, 1), 0.00001);
				Assert::AreEqual(0.86287074235688677, concrete.GetCreepCoefficient(56, 1), 0.00001);
				Assert::AreEqual(1.0654700927529588, concrete.GetCreepCoefficient(90, 1), 0.00001);
			}

			{
				LRFDAutoVersion av;
				LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::SeventhEdition2014);
				Assert::AreEqual(0.0, concrete.GetFreeShrinkageStrain(0), 0.00001);
				Assert::AreEqual(0.0, concrete.GetFreeShrinkageStrain(1), 0.00001);
				Assert::AreEqual(-0.00010368000000000000, concrete.GetFreeShrinkageStrain(10), 0.00001);
				Assert::AreEqual(-0.00022870588235294117, concrete.GetFreeShrinkageStrain(28), 0.00001);
				Assert::AreEqual(-0.00032999999999999994, concrete.GetFreeShrinkageStrain(56), 0.00001);
				Assert::AreEqual(-0.00039433846153846157, concrete.GetFreeShrinkageStrain(90), 0.00001);

				Assert::AreEqual(0.0, concrete.GetCreepCoefficient(0, 0), 0.00001);
				Assert::AreEqual(0.0, concrete.GetCreepCoefficient(1, 1), 0.00001);
				Assert::AreEqual(0.35339999999999999, concrete.GetCreepCoefficient(10, 1), 0.00001);
				Assert::AreEqual(0.77955882352941175, concrete.GetCreepCoefficient(28, 1), 0.00001);
				Assert::AreEqual(1.1248263888888888, concrete.GetCreepCoefficient(56, 1), 0.00001);
				Assert::AreEqual(1.3441282051282051, concrete.GetCreepCoefficient(90, 1), 0.00001);
			}


			{
				LRFDAutoVersion av;
				LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::SeventhEditionWith2015Interims);
				Assert::AreEqual(0.0, concrete.GetFreeShrinkageStrain(0), 0.00001);
				Assert::AreEqual(0.0, concrete.GetFreeShrinkageStrain(1), 0.00001);
				Assert::AreEqual(-0.00010936708860759493, concrete.GetFreeShrinkageStrain(10), 0.00001);
				Assert::AreEqual(-0.00023779816513761466, concrete.GetFreeShrinkageStrain(28), 0.00001);
				Assert::AreEqual(-0.00033918629550321202, concrete.GetFreeShrinkageStrain(56), 0.00001);
				Assert::AreEqual(-0.00040238618524332813, concrete.GetFreeShrinkageStrain(90), 0.00001);

				Assert::AreEqual(0.0, concrete.GetCreepCoefficient(0, 0), 0.00001);
				Assert::AreEqual(0.0, concrete.GetCreepCoefficient(1, 1), 0.00001);
				Assert::AreEqual(0.37278481012658232, concrete.GetCreepCoefficient(10, 1), 0.00001);
				Assert::AreEqual(0.81055045871559628, concrete.GetCreepCoefficient(28, 1), 0.00001);
				Assert::AreEqual(1.1561384725196289, concrete.GetCreepCoefficient(56, 1), 0.00001);
				Assert::AreEqual(1.3715593929879646, concrete.GetCreepCoefficient(90, 1), 0.00001);
			}

			concrete.Use90DayStrength(final90);
			Assert::IsTrue(concrete.Use90DayStrength());
			Assert::AreEqual(7.0, concrete.GetFc(90), 0.00001);
			Assert::AreEqual(10.5, concrete.GetFc(91), 0.00001);
			Assert::AreEqual(4600.0, concrete.GetEc(91), 0.00001);
			Assert::AreEqual(0.65, concrete.GetShearFr(91), 0.00001);
			Assert::AreEqual(0.7, concrete.GetFlexureFr(91), 0.00001);
			Assert::AreEqual(-0.00040373831775700935, concrete.GetFreeShrinkageStrain(91), 0.00001);
			Assert::AreEqual(1.3761682242990654, concrete.GetCreepCoefficient(91, 1), 0.00001);
		}
	};
}
